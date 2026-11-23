r"""Build an AutoPC .cei installer package from a TOML manifest.

    python3 ceipack.py package.toml out.cei

A manifest describes the package and what it installs; paths in it are
relative to the manifest. For the Clarion Joyride (x86, format 8) or the
Clarion AutoPC 310C (SH3, format 7):

    [package]
    name = "Hello"            # shown in Setup's Remove Programs
    version = "1.0"
    target = "joyride"        # or "310c"

    [[file]]
    source = "hello.exe"
    destination = '\Program Files\Hello'   # the default
    shortcut = "Hello"        # shell shortcut: needs icon 1 and string 1
    replace = "newer"         # or "always", "never"
    self_register = false

    [[folder]]
    path = '\My Documents\Hello'
    dynamic = true            # backed up and restored across OS updates

    [[registry]]
    key = 'HKEY_LOCAL_MACHINE\SOFTWARE\Hello'
    values = { Name = "text", Count = 1, Data = { binary = "01,ff" },
               List = { multi = ["a", "b"] }, Kept = { string = "x", leave_existing = true } }

    [menu]
    name = "Hello"            # the program's string resource 1
    order = 100

    [[template]]
    source = "hello.six"      # speaker-independent speech template

    [[database]]
    name = "Hello DB"
    create = true             # create on install as well as remove on uninstall
    create_always = false
    keys = [0, 0, 0, 0]

The package gets CEIBuild's standard tree, the .CEU migration manifest in
\Windows\Migrate, version-stamped programs and checksums. ceiunpack.py writes
a raw manifest ([package] raw = true, one [[entry]] per entry in file order)
that rebuilds a package byte for byte.

SOURCE_DATE_EPOCH, when set, is used for every file time."""
import argparse
import datetime
import os
import pathlib
import struct
import sys
import tomllib

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import ceitree
from ceitree import FOLDER, FILE, SPEECH, DATABASES, DATABASE, KEY, VALUE, GROUP, TEMPLATE, PHRASE
import checkcei

TARGETS = {
    "joyride": {"format": 8, "processor": 0x14C, "min_rom": (2, 0), "tool": (131072, 13050851), "max_rom": (0, 0), "entry_numbers": 3},
    "310c": {"format": 7, "processor": 0x1A2, "min_rom": (1, 0), "tool": (131072, 13050830), "max_rom": None, "entry_numbers": 2},
}
MACHINE_NAMES = {0x14C: "x86", 0x1A2: "sh3"}
KIND_NAMES = {FOLDER: "folder", FILE: "file", SPEECH: "speech", DATABASES: "databases", DATABASE: "database",
              KEY: "key", VALUE: "value", GROUP: "group", TEMPLATE: "template", PHRASE: "phrase"}
KINDS = {name: kind for kind, name in KIND_NAMES.items()}
REPLACE = {"newer": 0, "always": 1, "never": 2}
ALREADY_INSTALLED = 1
BOOT = 1
PLATFORM = "All"
LANGUAGE = "All"
DEVICE_FILES = "WCE Device Files"
SETUP_DLLS = "Custom Setup DLLs"
SKELETON = [
    (FOLDER, SETUP_DLLS, [(FOLDER, "Uninstall DLL", []), (FOLDER, "Install DLL", [])]),
    (DATABASES, "Databases", []),
    (SPEECH, "Speech Training", [(GROUP, "Phrases", []), (GROUP, "Templates", [])]),
    (KEY, "Registry", [(KEY, "HKEY_CURRENT_USER", []), (KEY, "HKEY_CLASSES_ROOT", []), (KEY, "HKEY_LOCAL_MACHINE", [])]),
    (FOLDER, DEVICE_FILES, [(FOLDER, "Program Files", []), (FOLDER, "Windows", [(FOLDER, "Migrate", [])]),
                            (FOLDER, "Temp", []), (FOLDER, "My Documents", [])]),
]
PE_SIGNATURE = b"PE\0\0"
OPTIONAL_HEADER = 24
IMAGE_VERSION = 44
CHECKSUM = 64
MENU_KEY = "HKEY_LOCAL_MACHINE\\SOFTWARE\\FMAppConfiguration"
MENU_ORDER = 100
CEU_SECTIONS = ((FOLDER, DEVICE_FILES), (KEY, "Registry"), (DATABASES, "Databases"))


def version_pair(text):
    major, _, minor = str(text).partition(".")
    return int(major), int(minor or 0)


def pe_header(data):
    if len(data) < 0x40 or data[:2] != b"MZ":
        return None
    offset = struct.unpack_from("<I", data, 0x3C)[0]
    if data[offset:offset + 4] != PE_SIGNATURE:
        return None
    return offset


def pe_checksum(data, checksum_offset):
    padded = data + b"\0" * (len(data) % 2)
    total = 0
    for index in range(0, len(padded), 2):
        if checksum_offset <= index < checksum_offset + 4:
            continue
        total += struct.unpack_from("<H", padded, index)[0]
        total = (total & 0xFFFF) + (total >> 16)
    return (total & 0xFFFF) + len(data)


def stamp(data, version):
    offset = pe_header(data)
    if offset is None:
        return data, version
    data = bytearray(data)
    version_offset = offset + OPTIONAL_HEADER + IMAGE_VERSION
    image_version = struct.unpack_from("<HH", data, version_offset)
    if image_version == (0, 0):
        struct.pack_into("<HH", data, version_offset, *version)
        image_version = version
    checksum_offset = offset + OPTIONAL_HEADER + CHECKSUM
    struct.pack_into("<I", data, checksum_offset, 0)
    struct.pack_into("<I", data, checksum_offset, pe_checksum(bytes(data), checksum_offset))
    return bytes(data), tuple(image_version)


def systemtime(moment):
    return (moment.year, moment.month, (moment.weekday() + 1) % 7, moment.day,
            moment.hour, moment.minute, moment.second, moment.microsecond // 1000)


def file_time(path=None):
    epoch = os.environ.get("SOURCE_DATE_EPOCH")
    if epoch:
        seconds = int(epoch)
    elif path:
        seconds = os.stat(path).st_mtime
    else:
        seconds = datetime.datetime.now().timestamp()
    return systemtime(datetime.datetime.fromtimestamp(seconds, datetime.timezone.utc))


def skeleton_nodes(layout):
    return [ceitree.Node(kind, name, info=ceitree.Info() if kind == FOLDER else None, children=skeleton_nodes(children))
            for kind, name, children in layout]


def child(parent_list, kind, name):
    for node in parent_list:
        if node.kind == kind and node.name.lower() == name.lower():
            return node
    node = ceitree.Node(kind, name, info=ceitree.Info() if kind == FOLDER else None)
    parent_list.append(node)
    return node


def folder_path(nodes, path):
    current = child(nodes, FOLDER, DEVICE_FILES)
    for name in [part for part in path.split("\\") if part]:
        current = child(current.children, FOLDER, name)
    return current


def key_path(nodes, path):
    current = child(nodes, KEY, "Registry")
    for name in [part for part in path.split("\\") if part]:
        current = child(current.children, KEY, name)
    return current


def registry_value(name, value):
    node = ceitree.Node(VALUE, name)
    if isinstance(value, dict):
        node.value_flags = 1 if value.get("leave_existing") else 0
        kinds = [kind for kind in ("string", "dword", "binary", "multi") if kind in value]
        if len(kinds) != 1:
            raise SystemExit("registry value %s needs one of string, dword, binary, multi" % name)
        kind = kinds[0]
        value = value[kind]
    else:
        kind = "dword" if isinstance(value, int) and not isinstance(value, bool) else "string"
    if kind == "string":
        node.value_type, node.value = ceitree.REG_SZ, str(value)
    elif kind == "dword":
        node.value_type, node.value = ceitree.REG_DWORD, int(value) & 0xFFFFFFFF
    elif kind == "binary":
        node.value_type, node.value = ceitree.REG_BINARY, bytes(int(token, 16) for token in str(value).split(",") if token.strip())
    else:
        node.value_type = ceitree.REG_MULTI_SZ
        node.value = ("\0".join(value) + "\0\0").encode("utf-16-le")
    return node


def file_node(name, data, version, moment, flags, shortcut):
    info = ceitree.Info(version, (moment,) * ceitree.TIMES, flags, shortcut, ".\\" + name)
    return ceitree.Node(FILE, name, info=info, data=data)


def add_file(nodes, entry, base, version):
    source = os.path.join(base, entry["source"])
    name = entry.get("name", os.path.basename(source))
    data, file_version = stamp(pathlib.Path(source).read_bytes(), version_pair(entry["version"]) if "version" in entry else version)
    if pe_header(data) is None:
        file_version = version
    replace = entry.get("replace", "newer")
    if replace not in REPLACE:
        raise SystemExit("%s: replace must be one of %s" % (name, ", ".join(REPLACE)))
    self_register = bool(entry.get("self_register"))
    is_pe = pe_header(data) is not None
    flags = (0, 1 if entry.get("shortcut") else 0, REPLACE[replace], 0, int(self_register), int(is_pe or self_register))
    folder = folder_path(nodes, entry["destination"])
    folder.children.append(file_node(name, data, file_version, file_time(source), flags, entry.get("shortcut")))


def ceu_data(package, nodes):
    fields = package.fields
    target = "Platform %s MinROMVersion %4u %4u Language %s MachineType %4u " % (fields[8], fields[5], fields[6], fields[9], fields[7])
    sections = ["TargetInformation %d %s" % (len(target), target)]
    for kind, root_name in CEU_SECTIONS:
        root = next((node for node in nodes if node.kind == kind and node.name == root_name), None)
        if root is None:
            continue
        for path, node in ceitree.walk(root.children):
            if node.dynamic:
                text = ceitree.escape("\\".join(path)) + " "
                sections.append("%s %d %s" % (ceitree.escape(root_name), len(text), text))
    return "".join(sections).encode(ceitree.TEXT)


def authored(manifest, base):
    settings = manifest["package"]
    target_name = settings.get("target", "joyride")
    if target_name not in TARGETS:
        raise SystemExit("target must be one of %s" % ", ".join(TARGETS))
    target = TARGETS[target_name]
    name = settings["name"]
    version = version_pair(settings.get("version", "1.0"))
    min_rom = version_pair(settings["min_rom"]) if "min_rom" in settings else target["min_rom"]
    fields = [target["format"], ALREADY_INSTALLED, BOOT, version[0], version[1], min_rom[0], min_rom[1],
              target["processor"], PLATFORM, LANGUAGE, 0, target["tool"][0], target["tool"][1]]
    if target["max_rom"] is not None:
        fields += list(target["max_rom"])
    package = ceitree.Package(name, settings.get("title", ""), fields, target["entry_numbers"])
    nodes = skeleton_nodes(SKELETON)
    program_folder = "\\Program Files\\" + name
    for entry in manifest.get("folder", []):
        folder_path(nodes, entry["path"]).dynamic = int(bool(entry.get("dynamic")))
    for entry in manifest.get("file", []):
        add_file(nodes, dict(entry, destination=entry.get("destination", program_folder)), base, version)
    for entry in manifest.get("registry", []):
        key = key_path(nodes, entry["key"])
        key.dynamic = int(bool(entry.get("dynamic")))
        for value_name, value in entry.get("values", {}).items():
            key.children.append(registry_value(value_name, value))
    if "menu" in manifest:
        menu = manifest["menu"]
        key = key_path(nodes, MENU_KEY + "\\" + menu["name"])
        key.children.append(registry_value("AppName", menu["name"]))
        key.children.append(registry_value("Order", int(menu.get("order", MENU_ORDER))))
        if "launch_phrase" in menu:
            key.children.append(registry_value("LaunchPhrase", menu["launch_phrase"]))
    templates = child(child(nodes, SPEECH, "Speech Training").children, GROUP, "Templates")
    for entry in manifest.get("template", []):
        source = os.path.join(base, entry["source"])
        file_name = os.path.basename(source)
        template = ceitree.Node(TEMPLATE, file_name)
        template.children.append(file_node(file_name, pathlib.Path(source).read_bytes(), version, file_time(source), (0,) * ceitree.FLAGS, None))
        templates.children.append(template)
    databases = child(nodes, DATABASES, "Databases")
    for entry in manifest.get("database", []):
        keys = list(entry.get("keys", [0, 0, 0, 0])) + [0, 0, 0, 0]
        databases.children.append(ceitree.Node(DATABASE, entry["name"], dynamic=int(bool(entry.get("dynamic"))),
                                               database=(int(bool(entry.get("create"))), int(bool(entry.get("create_always")))) + tuple(keys[:4])))
    migrate = folder_path(nodes, "\\Windows\\Migrate")
    migrate.children.append(file_node(name.replace(" ", "") + ".CEU", ceu_data(package, nodes), version, file_time(), (0,) * ceitree.FLAGS, None))
    package.nodes = nodes
    return package


def raw_node(entry, base):
    kind = KINDS[entry["kind"]]
    node = ceitree.Node(kind, entry["path"][-1], dynamic=entry.get("dynamic", 0))
    if "numbers" in entry:
        node.numbers = entry["numbers"]
    if "checksums" in entry:
        node.checksums = tuple(entry["checksums"])
    if kind in (FOLDER, FILE):
        node.info = ceitree.Info(tuple(entry.get("version", (0, 0))), tuple(tuple(time) for time in entry.get("times", ceitree.Info().times)),
                                 tuple(entry.get("flags", (0,) * ceitree.FLAGS)), entry.get("shortcut"), entry.get("origin"))
    if kind == FILE:
        node.data = pathlib.Path(os.path.join(base, entry["source"])).read_bytes()
    elif kind == DATABASE:
        node.database = tuple(entry["database"])
    elif kind == VALUE:
        node.value_type, node.value_flags = entry["type"], entry.get("flags", 0)
        value = entry["value"]
        node.value = bytes.fromhex(value) if node.value_type in (ceitree.REG_BINARY, ceitree.REG_MULTI_SZ) else value
    elif kind == TEMPLATE:
        node.number = entry.get("number", 0)
    return node


def raw(manifest, base):
    settings = manifest["package"]
    package = ceitree.Package(settings["name"], settings.get("title", ""), list(settings["fields"]), settings["entry_numbers"])
    by_path = {}
    for entry in manifest.get("entry", []):
        node = raw_node(entry, base)
        path = tuple(entry["path"])
        siblings = by_path[path[:-1]].children if len(path) > 1 else package.nodes
        siblings.append(node)
        by_path[path] = node
    return package


def build(manifest_path):
    manifest = tomllib.loads(pathlib.Path(manifest_path).read_text())
    base = os.path.dirname(os.path.abspath(manifest_path))
    if manifest["package"].get("raw"):
        return raw(manifest, base), False
    return authored(manifest, base), True


def main():
    parser = argparse.ArgumentParser(description="Build an AutoPC .cei installer package from a TOML manifest")
    parser.add_argument("manifest")
    parser.add_argument("output")
    arguments = parser.parse_args()
    package, check = build(arguments.manifest)
    data = ceitree.serialize(package)
    if check:
        problems = checkcei.problems(data, MACHINE_NAMES[package.fields[7]])
        if problems:
            raise SystemExit("\n".join("ceipack: %s" % problem for problem in problems))
    pathlib.Path(arguments.output).write_bytes(data)
    print("wrote %s: %d bytes" % (arguments.output, len(data)))


if __name__ == "__main__":
    main()
