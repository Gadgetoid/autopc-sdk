import os
import pathlib
import re
import subprocess
import sys
import tempfile
import unittest

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import cei
import checkcei

TEMPLATE_HEADER = b"Template |Z 7 1 1 1 0 1 0 418 All All 0 131072 13050830"
TEMPLATE_CEU = b"TargetInformation 67 Platform All MinROMVersion    1    0 Language All MachineType  418 "
TEMPLATE_EXE = b"MZ template program"
FILE_TIMES = b"2000 1 0 9 15 7 49 703 2000 1 0 9 15 51 38 243 2000 1 0 9 15 12 1 596"
PE_OFFSET = 0x40
PROGRAM_SIZE = 0x200


def template():
    items = [
        ("record", b"1 Program|BFiles 1603953561 1603953553"),
        ("record", b"1 Template 1603953561 1603953553"),
        ("record", b"2 template.exe 1603839911 1599242296"),
        ("record", b"1 0 " + FILE_TIMES + b" 0 1 1 0 0 1 Template .\\template.exe %d" % len(TEMPLATE_EXE)),
        ("blob", "template.exe", TEMPLATE_EXE),
        ("record", b""),
        ("record", b"1 Migrate 1603953561 1603953553"),
        ("record", b"2 Template.CEU 1603953521 1603946140"),
        ("record", b"1 0 " + FILE_TIMES + b" 0 0 0 0 0 0 - .\\Template.CEU %d" % len(TEMPLATE_CEU)),
        ("blob", "Template.CEU", TEMPLATE_CEU),
        ("record", b""),
        ("record", b"6 Registry 0 0"),
        ("record", b"6 HKEY_LOCAL_MACHINE 0 0"),
        ("record", b""),
        ("record", b""),
        ("tail", b""),
    ]
    return cei.build(TEMPLATE_HEADER, items)


SDK_HEADER = b"Browser |Z 8 1 1 1 0 2 0 332 All All 0 131072 13050851 0 0"
SDK_CEU = (b"TargetInformation 67 Platform All MinROMVersion    2    0 Language All MachineType  332 "
           b"WCE|BDevice|BFiles 23 Program|BFiles\\Browser ")


def sdk_package():
    items = [
        ("record", b"1 Program|BFiles 1603953561 1603953553 0"),
        ("record", b"1 Browser 1603953561 1603953553 1"),
        ("record", b"2 browser.exe 1603950444 1603590762 0"),
        ("record", b"1 0 " + FILE_TIMES + b" 0 0 0 0 0 1 Browser C:\\Windows|BCE|BTools\\WCEX86Rel\\browser.exe %d" % len(TEMPLATE_EXE)),
        ("blob", "browser.exe", TEMPLATE_EXE),
        ("record", b""),
        ("record", b"2 Browser.CEU 1603953452 1603949845 0"),
        ("record", b"1 0 " + FILE_TIMES + b" 0 0 0 0 0 0 - .\\Browser.CEU %d" % len(SDK_CEU)),
        ("blob", "Browser.CEU", SDK_CEU),
        ("record", b""),
        ("record", b"6 Registry 0 0 0"),
        ("record", b"7 Order 1603953607 1603953571 0"),
        ("record", b"4 0"),
        ("record", b"100"),
        ("tail", b""),
    ]
    return cei.build(SDK_HEADER, items)


def program():
    data = bytearray(PROGRAM_SIZE)
    data[:2] = b"MZ"
    data[0x3C:0x40] = PE_OFFSET.to_bytes(4, "little")
    data[PE_OFFSET:PE_OFFSET + 4] = b"PE\0\0"
    return bytes(data)


class MkceiTest(unittest.TestCase):
    def setUp(self):
        self.folder = tempfile.TemporaryDirectory()
        self.template = os.path.join(self.folder.name, "template.cei")
        self.program = os.path.join(self.folder.name, "hello.exe")
        pathlib.Path(self.template).write_bytes(template())
        pathlib.Path(self.program).write_bytes(program())

    def tearDown(self):
        self.folder.cleanup()

    def build(self, *options):
        output = os.path.join(self.folder.name, "hello.cei")
        result = subprocess.run([sys.executable, os.path.join(ROOT, "tools", "mkcei.py"), self.template, self.program, output,
                                 "--minimal", "--name", "hello.exe", "--package", "Hello", "--menu", "Hello", *options],
                                capture_output=True, text=True)
        self.assertEqual(result.returncode, 0, result.stderr)
        data = pathlib.Path(output).read_bytes()
        header, items = cei.parse(data)
        self.assertEqual(cei.build(header, items), data)
        return data, header, items

    def blob(self, items, name):
        return [item[2] for item in items if item[0] == "blob" and item[1] == name][0]

    def test_template_is_refused_for_x86(self):
        found = checkcei.problems(template(), "x86")
        self.assertIn("header processor 418 in a format 7 header, x86 needs one of [0]", found)
        self.assertEqual(sum("keeps a checksum" in problem for problem in found), 5)

    def test_template_passes_for_sh3(self):
        self.assertEqual(checkcei.problems(template(), "sh3"), [])

    def test_x86_package(self):
        data, header, items = self.build("--machine", "x86")
        self.assertEqual(header.split(b" ")[9], b"0")
        self.assertEqual(self.blob(items, "Hello.CEU"), TEMPLATE_CEU.replace(b"MachineType  418", b"MachineType  332"))
        self.assertEqual(checkcei.problems(data, "x86"), [])

    def test_sh3_package(self):
        data, header, items = self.build("--machine", "sh3")
        self.assertEqual(header.split(b" ")[9], b"418")
        self.assertEqual(self.blob(items, "Hello.CEU"), TEMPLATE_CEU)
        self.assertEqual(checkcei.problems(data, "sh3"), [])

    def test_checksums_are_stripped(self):
        _, _, items = self.build()
        records = [item[1] for item in items if item[0] == "record"]
        self.assertIn(b"1 Program|BFiles", records)
        self.assertIn(b"2 hello.exe", records)
        self.assertIn(b"2 Hello.CEU", records)
        self.assertIn(b"6 Registry 0 0", records)
        self.assertFalse([record for record in records if re.match(rb"^[12] \S+ \d+ \d+$", record)])

    def test_program_replaces_the_template_one(self):
        _, _, items = self.build("--machine", "x86")
        exe = self.blob(items, "hello.exe")
        self.assertEqual(len(exe), PROGRAM_SIZE)
        self.assertEqual(exe[PE_OFFSET + 24 + 44:PE_OFFSET + 24 + 48], b"\1\0\0\0")
        record = [items[index - 1][1] for index, item in enumerate(items) if item[0] == "blob" and item[1] == "hello.exe"][0]
        self.assertTrue(record.endswith(b".\\hello.exe %d" % PROGRAM_SIZE))

    def test_menu_name_with_spaces(self):
        output = os.path.join(self.folder.name, "pclink.cei")
        result = subprocess.run([sys.executable, os.path.join(ROOT, "tools", "mkcei.py"), self.template, self.program, output,
                                 "--minimal", "--name", "pclink.exe", "--package", "PCLink", "--menu", "PC Link", "--machine", "x86"],
                                capture_output=True, text=True)
        self.assertEqual(result.returncode, 0, result.stderr)
        _, items = cei.parse(pathlib.Path(output).read_bytes())
        records = [item[1] for item in items if item[0] == "record"]
        self.assertIn(b"6 PC|BLink 0 0", records)
        self.assertIn(b"PC Link", records)

    def test_package_name_with_spaces_is_refused(self):
        result = subprocess.run([sys.executable, os.path.join(ROOT, "tools", "mkcei.py"), self.template, self.program,
                                 os.path.join(self.folder.name, "pclink.cei"), "--package", "PC Link"], capture_output=True, text=True)
        self.assertNotEqual(result.returncode, 0)

    def test_menu_entry(self):
        _, _, items = self.build("--machine", "x86")
        records = [item[1] for item in items if item[0] == "record"]
        self.assertIn(b"6 FMAppConfiguration 0 0", records)
        self.assertIn(b"7 AppName 0 0", records)


class CheckceiTest(unittest.TestCase):
    def with_header(self, header):
        _, items = cei.parse(template())
        stripped = [("record", re.sub(rb"^([12] \S+) \d+ \d+$", rb"\1", item[1])) if item[0] == "record" else item for item in items]
        return cei.build(header, stripped)

    def test_x86_processor_needs_format_8(self):
        self.assertTrue(checkcei.problems(self.with_header(b"Hello |Z 7 1 1 1 0 1 0 332 All All 0 131072 13050830"), "x86"))
        self.assertEqual(checkcei.problems(self.with_header(b"Hello |Z 8 1 1 1 0 1 0 332 All All 0 131072 13050830"), "x86"), [])
        self.assertEqual(checkcei.problems(self.with_header(b"Hello |Z 7 1 1 1 0 1 0 0 All All 0 131072 13050830"), "x86"), [])

    def test_seven_field_header(self):
        self.assertEqual(checkcei.problems(self.with_header(b"Hello |Z 7 1 1 1 0"), "x86"), [])

    def test_format_out_of_range(self):
        self.assertTrue(checkcei.problems(self.with_header(b"Hello |Z 9 1 1 1 0"), "x86"))

    def test_certificate(self):
        self.assertTrue(checkcei.problems(self.with_header(b"Hello |Z 7 1 1 1 0 1 0 0 All All 40 131072 13050830"), "x86"))

    def test_ceu_length(self):
        data = self.with_header(b"Hello |Z 7 1 1 1 0 1 0 0 All All 0 131072 13050830")
        broken = data.replace(b"TargetInformation 67", b"TargetInformation 66")
        self.assertIn("Template.CEU TargetInformation says 66 bytes, has 67", checkcei.problems(broken, "x86"))


class SdkPackageTest(unittest.TestCase):
    def test_absolute_source_paths_are_files(self):
        _, items = cei.parse(sdk_package())
        self.assertEqual([(item[1], item[2]) for item in items if item[0] == "blob"],
                         [("browser.exe", TEMPLATE_EXE), ("Browser.CEU", SDK_CEU)])

    def test_checksums_are_reported(self):
        problems = checkcei.problems(sdk_package(), "x86")
        self.assertEqual(len(problems), 5)
        self.assertIn("entry '7 Order 1603953607 1603953571 0' keeps a checksum", problems)

    def test_ceu_sections(self):
        data = cei.build(*cei.parse(sdk_package()))
        cleared = cei.build(cei.parse(data)[0], cei.clear_checksums(cei.parse(data)[1]))
        self.assertEqual(checkcei.problems(cleared, "x86"), [])
        broken = cleared.replace(b"BFiles 23 ", b"BFiles 24 ")
        self.assertIn("Browser.CEU WCE|BDevice|BFiles says 24 bytes, has 23", checkcei.problems(broken, "x86"))

    def test_fixcei(self):
        with tempfile.TemporaryDirectory() as folder:
            source = os.path.join(folder, "browser.cei")
            output = os.path.join(folder, "fixed.cei")
            pathlib.Path(source).write_bytes(sdk_package())
            result = subprocess.run([sys.executable, os.path.join(ROOT, "tools", "fixcei.py"), source, output, "--machine", "x86"],
                                    capture_output=True, text=True)
            self.assertEqual(result.returncode, 0, result.stderr)
            fixed = pathlib.Path(output).read_bytes()
        _, items = cei.parse(fixed)
        records = [item[1] for item in items if item[0] == "record"]
        self.assertIn(b"1 Browser 0 0 1", records)
        self.assertIn(b"2 browser.exe 0 0 0", records)
        self.assertIn(b"7 Order 0 0 0", records)
        self.assertEqual([item[2] for item in items if item[0] == "blob"], [TEMPLATE_EXE, SDK_CEU])
        self.assertEqual(checkcei.problems(fixed, "x86"), [])


if __name__ == "__main__":
    unittest.main()
