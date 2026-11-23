r"""Unpack an AutoPC .cei installer package into a raw manifest and its files.

    python3 ceiunpack.py package.cei outdir

Writes outdir/package.toml and each file under outdir/files/, mirroring the
package's tree. `ceipack.py outdir/package.toml out.cei` rebuilds the package
byte for byte. Entry checksums are written only where the package's differ
from its contents."""
import argparse
import os
import pathlib
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import ceitree
from ceitree import FOLDER, FILE, DATABASE, VALUE, TEMPLATE
from ceipack import KIND_NAMES

FILES = "files"


def toml_string(text):
    if "'" not in text and "\n" not in text and all(ord(character) >= 0x20 for character in text):
        return "'%s'" % text
    escaped = text.replace("\\", "\\\\").replace('"', '\\"')
    escaped = "".join(character if ord(character) >= 0x20 else "\\u%04x" % ord(character) for character in escaped)
    return '"%s"' % escaped


def toml_value(value):
    if isinstance(value, bool):
        return "true" if value else "false"
    if isinstance(value, int):
        return str(value)
    if isinstance(value, str):
        return toml_string(value)
    return "[%s]" % ", ".join(toml_value(item) for item in value)


def table(lines, name, values):
    lines.append(name)
    for key, value in values:
        if value is not None:
            lines.append("%s = %s" % (key, toml_value(value)))
    lines.append("")


def safe(name):
    return "".join("_" if character in '\\/:*?"<>|' else character for character in name)


def entry_values(path, node, out_dir):
    values = [("path", list(path)), ("kind", KIND_NAMES[node.kind])]
    if node.dynamic:
        values.append(("dynamic", node.dynamic))
    if node.numbers is not None:
        values.append(("numbers", node.numbers))
    if node.checksums is not None and node.checksums != ceitree.computed_checksums(node):
        values.append(("checksums", list(node.checksums)))
    if node.kind in (FOLDER, FILE):
        info = node.info
        default = ceitree.Info()
        if info.version != default.version:
            values.append(("version", list(info.version)))
        if info.times != default.times:
            values.append(("times", [list(time) for time in info.times]))
        if info.flags != default.flags:
            values.append(("flags", list(info.flags)))
        values += [("shortcut", info.shortcut), ("origin", info.origin)]
    if node.kind == FILE:
        relative = os.path.join(FILES, *[safe(part) for part in path])
        os.makedirs(os.path.dirname(os.path.join(out_dir, relative)), exist_ok=True)
        pathlib.Path(out_dir, relative).write_bytes(node.data)
        values.append(("source", relative))
    elif node.kind == DATABASE:
        values.append(("database", list(node.database)))
    elif node.kind == VALUE:
        values += [("type", node.value_type), ("flags", node.value_flags)]
        value = node.value.hex() if isinstance(node.value, bytes) else node.value
        values.append(("value", value))
    elif node.kind == TEMPLATE:
        values.append(("number", node.number))
    return values


def unpack(data, out_dir):
    package = ceitree.parse(data)
    if ceitree.serialize(package) != data:
        raise SystemExit("this package doesn't round-trip; it isn't in a form CEIBuild writes")
    os.makedirs(out_dir, exist_ok=True)
    lines = []
    table(lines, "[package]", [("raw", True), ("name", package.name), ("title", package.title),
                               ("fields", package.fields), ("entry_numbers", package.entry_numbers)])
    for path, node in ceitree.walk(package.nodes):
        table(lines, "[[entry]]", entry_values(path, node, out_dir))
    pathlib.Path(out_dir, "package.toml").write_text("\n".join(lines))


def main():
    parser = argparse.ArgumentParser(description="Unpack an AutoPC .cei package into a raw manifest and its files")
    parser.add_argument("package")
    parser.add_argument("out_dir")
    arguments = parser.parse_args()
    unpack(pathlib.Path(arguments.package).read_bytes(), arguments.out_dir)
    print("wrote %s" % os.path.join(arguments.out_dir, "package.toml"))


if __name__ == "__main__":
    main()
