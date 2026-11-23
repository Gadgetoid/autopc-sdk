import os
import pathlib
import struct
import subprocess
import sys
import tempfile
import unittest

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import cei
import ceipack
import ceitree
import checkcei

PE_OFFSET = 0x40
PROGRAM_SIZE = 0x200
EPOCH = "946684800"
JOYRIDE_CEU = b"TargetInformation 67 Platform All MinROMVersion    2    0 Language All MachineType  332 "
AUTOPC_CEU = b"TargetInformation 67 Platform All MinROMVersion    1    0 Language All MachineType  418 "
MANIFEST = """
[package]
name = "Hello World"
version = "1.2"
target = "%s"

[[file]]
source = "hello.exe"
shortcut = "Hello World"

[[file]]
source = "help.html"
replace = "always"

[menu]
name = "Hello World"
"""


def program():
    data = bytearray(PROGRAM_SIZE)
    data[:2] = b"MZ"
    data[0x3C:0x40] = PE_OFFSET.to_bytes(4, "little")
    data[PE_OFFSET:PE_OFFSET + 4] = b"PE\0\0"
    return bytes(data)


def find(package, *path):
    for node_path, node in ceitree.walk(package.nodes):
        if node_path == path:
            return node
    raise KeyError(path)


class CeipackTest(unittest.TestCase):
    def setUp(self):
        self.folder = tempfile.TemporaryDirectory()
        self.saved_epoch = os.environ.get("SOURCE_DATE_EPOCH")
        os.environ["SOURCE_DATE_EPOCH"] = EPOCH
        pathlib.Path(self.path("hello.exe")).write_bytes(program())
        pathlib.Path(self.path("help.html")).write_bytes(b"<p>help</p>")

    def tearDown(self):
        if self.saved_epoch is None:
            del os.environ["SOURCE_DATE_EPOCH"]
        else:
            os.environ["SOURCE_DATE_EPOCH"] = self.saved_epoch
        self.folder.cleanup()

    def path(self, name):
        return os.path.join(self.folder.name, name)

    def pack(self, manifest, name="package.toml"):
        pathlib.Path(self.path(name)).write_text(manifest)
        output = self.path(name + ".cei")
        result = subprocess.run([sys.executable, os.path.join(ROOT, "tools", "ceipack.py"), self.path(name), output],
                                capture_output=True, text=True, env=dict(os.environ))
        self.assertEqual(result.returncode, 0, result.stderr + result.stdout)
        data = pathlib.Path(output).read_bytes()
        return data, ceitree.parse(data)

    def test_joyride_package(self):
        data, package = self.pack(MANIFEST % "joyride")
        self.assertEqual(package.fields, [8, 1, 1, 1, 2, 2, 0, 332, "All", "All", 0, 131072, 13050851, 0, 0])
        self.assertEqual(package.entry_numbers, 3)
        self.assertEqual(checkcei.problems(data, "x86"), [])
        self.assertTrue(checkcei.problems(data, "sh3"))
        self.assertEqual(find(package, "WCE Device Files", "Windows", "Migrate", "HelloWorld.CEU").data, JOYRIDE_CEU)

    def test_310c_package(self):
        data, package = self.pack(MANIFEST % "310c")
        self.assertEqual(package.fields, [7, 1, 1, 1, 2, 1, 0, 418, "All", "All", 0, 131072, 13050830])
        self.assertEqual(package.entry_numbers, 2)
        self.assertEqual(checkcei.problems(data, "sh3"), [])
        self.assertTrue(checkcei.problems(data, "x86"))
        self.assertEqual(find(package, "WCE Device Files", "Windows", "Migrate", "HelloWorld.CEU").data, AUTOPC_CEU)

    def test_skeleton(self):
        _, package = self.pack(MANIFEST % "joyride")
        self.assertEqual([node.name for node in package.nodes],
                         ["Custom Setup DLLs", "Databases", "Speech Training", "Registry", "WCE Device Files"])
        self.assertEqual([node.name for node in find(package, "WCE Device Files").children],
                         ["Program Files", "Windows", "Temp", "My Documents"])

    def test_program(self):
        _, package = self.pack(MANIFEST % "joyride")
        node = find(package, "WCE Device Files", "Program Files", "Hello World", "hello.exe")
        self.assertEqual(node.info.flags, (0, 1, 0, 0, 0, 1))
        self.assertEqual(node.info.shortcut, "Hello World")
        self.assertEqual(node.info.version, (1, 2))
        self.assertEqual(node.info.times[0], (2000, 1, 6, 1, 0, 0, 0, 0))
        version = PE_OFFSET + ceipack.OPTIONAL_HEADER + ceipack.IMAGE_VERSION
        self.assertEqual(struct.unpack_from("<HH", node.data, version), (1, 2))
        checksum = PE_OFFSET + ceipack.OPTIONAL_HEADER + ceipack.CHECKSUM
        self.assertEqual(struct.unpack_from("<I", node.data, checksum)[0], ceipack.pe_checksum(node.data, checksum))

    def test_data_file(self):
        _, package = self.pack(MANIFEST % "joyride")
        node = find(package, "WCE Device Files", "Program Files", "Hello World", "help.html")
        self.assertEqual(node.info.flags, (0, 0, 1, 0, 0, 0))
        self.assertEqual(node.info.version, (1, 2))
        self.assertIsNone(node.info.shortcut)

    def test_menu(self):
        _, package = self.pack(MANIFEST % "joyride")
        key = find(package, "Registry", "HKEY_LOCAL_MACHINE", "SOFTWARE", "FMAppConfiguration", "Hello World")
        self.assertEqual([(node.name, node.value) for node in key.children], [("AppName", "Hello World"), ("Order", 100)])

    def test_registry_values(self):
        manifest = MANIFEST % "joyride" + """
[[registry]]
key = 'HKEY_CURRENT_USER\\Software\\Hello'
dynamic = true
values = { Name = "two words", Count = 7, Data = { binary = "01,ff" }, List = { multi = ["a", "b"] }, Kept = { string = "x", leave_existing = true } }
"""
        data, package = self.pack(manifest)
        key = find(package, "Registry", "HKEY_CURRENT_USER", "Software", "Hello")
        values = {node.name: node for node in key.children}
        self.assertEqual(values["Name"].value, "two words")
        self.assertEqual(values["Count"].value_type, ceitree.REG_DWORD)
        self.assertEqual(values["Data"].value, b"\x01\xff")
        self.assertEqual(values["List"].value, "a\0b\0\0".encode("utf-16-le"))
        self.assertEqual(values["Kept"].value_flags, 1)
        self.assertEqual(checkcei.problems(data, "x86"), [])
        ceu = find(package, "WCE Device Files", "Windows", "Migrate", "HelloWorld.CEU").data
        self.assertEqual(ceu, JOYRIDE_CEU + b"Registry 33 HKEY_CURRENT_USER\\Software\\Hello ")

    def test_dynamic_folder(self):
        manifest = MANIFEST % "joyride" + """
[[folder]]
path = '\\My Documents\\Hello World'
dynamic = true
"""
        _, package = self.pack(manifest)
        ceu = find(package, "WCE Device Files", "Windows", "Migrate", "HelloWorld.CEU").data
        self.assertEqual(ceu, JOYRIDE_CEU + b"WCE|BDevice|BFiles 27 My|BDocuments\\Hello|BWorld ")

    def test_template_and_database(self):
        pathlib.Path(self.path("hello.six")).write_bytes(b"template")
        manifest = MANIFEST % "joyride" + """
[[template]]
source = "hello.six"

[[database]]
name = "Hello DB"
create = true
keys = [1, 2]
"""
        data, package = self.pack(manifest)
        template = find(package, "Speech Training", "Templates", "hello.six")
        self.assertEqual(template.kind, ceitree.TEMPLATE)
        self.assertEqual(template.children[0].data, b"template")
        self.assertEqual(find(package, "Databases", "Hello DB").database, (1, 0, 1, 2, 0, 0))
        self.assertEqual(checkcei.problems(data, "x86"), [])

    def test_checksums_verify(self):
        data, _ = self.pack(MANIFEST % "joyride")
        self.assertEqual(cei.checksum_problems(cei.parse(data)[1]), [])

    def test_round_trip(self):
        data, package = self.pack(MANIFEST % "joyride")
        self.assertEqual(ceitree.serialize(package), data)

    def test_reproducible(self):
        first, _ = self.pack(MANIFEST % "joyride", "first.toml")
        second, _ = self.pack(MANIFEST % "joyride", "second.toml")
        self.assertEqual(first, second)

    def test_unpack_and_repack(self):
        data, _ = self.pack(MANIFEST % "310c")
        pathlib.Path(self.path("in.cei")).write_bytes(data)
        unpacked = self.path("unpacked")
        result = subprocess.run([sys.executable, os.path.join(ROOT, "tools", "ceiunpack.py"), self.path("in.cei"), unpacked],
                                capture_output=True, text=True)
        self.assertEqual(result.returncode, 0, result.stderr)
        package, _ = ceipack.build(os.path.join(unpacked, "package.toml"))
        self.assertEqual(ceitree.serialize(package), data)

    def test_stale_checksums_survive_unpacking(self):
        data, package = self.pack(MANIFEST % "joyride")
        find(package, "WCE Device Files", "Program Files", "Hello World", "help.html").checksums = (1, 2)
        stale = ceitree.serialize(package)
        pathlib.Path(self.path("stale.cei")).write_bytes(stale)
        unpacked = self.path("stale")
        subprocess.run([sys.executable, os.path.join(ROOT, "tools", "ceiunpack.py"), self.path("stale.cei"), unpacked], check=True,
                       capture_output=True)
        rebuilt, _ = ceipack.build(os.path.join(unpacked, "package.toml"))
        self.assertEqual(ceitree.serialize(rebuilt), stale)


class EscapeTest(unittest.TestCase):
    def test_escapes(self):
        self.assertEqual(ceitree.escape("a b\tc"), "a|Bb|Tc")
        self.assertEqual(ceitree.escape(""), "|Z")
        self.assertEqual(ceitree.escape(None), "-")

    def test_bar_is_refused(self):
        with self.assertRaises(ValueError):
            ceitree.escape("a|b")

    def test_long_text_is_refused(self):
        with self.assertRaises(ValueError):
            ceitree.escape("x" * 0x104)


if __name__ == "__main__":
    unittest.main()
