"""Build an AutoPC .cei installer by swapping your program into a template .cei.

A .cei is a custom AutoPC installer package. This takes a known-good .cei as a
template and replaces its single program with yours, keeping the proven
structure. Tested on hardware with musicplayer.cei as the template: the
package installs and the program runs.

    python3 mkcei.py template.cei program.exe out.cei --minimal --name app.exe --package App

--minimal drops the template's media files and speech templates but keeps
the program and the .CEU uninstall manifest. Without a speech template for the
shortcut name, the installer asks the user to voice-train it.

A program linked with image version 0.0 is stamped with the version in its file
record, as Microsoft's CEIBuild does. The template's record asks for a shell
shortcut, which needs icon resource 1 and string resource 1 in the program.

--package renames the title, program folder, shell name and .CEU, so the
package does not collide with another built from the same template."""
import argparse
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import cei


def stamp_version(program, record):
    pe = int.from_bytes(program[0x3C:0x40], "little")
    version = pe + 24 + 44
    if program[version:version + 4] != bytes(4):
        return program
    major, minor = (int(field) for field in record.split(b" ")[:2])
    return program[:version] + major.to_bytes(2, "little") + minor.to_bytes(2, "little") + program[version + 4:]


def main():
    parser = argparse.ArgumentParser(description="Swap a program into a template AutoPC .cei")
    parser.add_argument("template")
    parser.add_argument("program")
    parser.add_argument("output")
    parser.add_argument("--minimal", action="store_true", help="drop the template's other files")
    parser.add_argument("--name", help="rename the installed program (e.g. dump.exe)")
    parser.add_argument("--package", help="rename the package title, program folder, shell name and .CEU so it installs alongside others")
    arguments = parser.parse_args()

    header, items = cei.parse(open(arguments.template, "rb").read())
    program = open(arguments.program, "rb").read()

    exe = [it for it in items if it[0] == "blob" and it[1].lower().endswith(".exe")]
    if len(exe) != 1:
        raise SystemExit("template must contain exactly one .exe")
    exe_name = exe[0][1]
    exe_index = items.index(exe[0])
    program = stamp_version(program, items[exe_index - 1][1])

    keep = []
    index = 0
    while index < len(items):
        kind = items[index][0]
        if kind == "blob" and items[index][1] == exe_name:
            keep.append(("blob", exe_name, program))
            index += 1
            continue
        if arguments.minimal and kind == "blob" and items[index][1] != exe_name and not items[index][1].lower().endswith(".ceu"):
            name = items[index][1].encode()
            template_node = False
            while keep and keep[-1][0] == "record" and (name in keep[-1][1] or keep[-1][1] in (b"0", b"")):
                template_node = template_node or keep[-1][1].startswith(b"9 ")
                keep.pop()
            index += 1
            if template_node:
                index += 2
            continue
        if kind == "record":
            keep.append(("record", re.sub(rb"(\." + re.escape(b"\\") + re.escape(exe_name.encode()) + rb") \d+$",
                                           rb"\1 %d" % len(program), items[index][1])))
        else:
            keep.append(items[index])
        index += 1

    if arguments.name:
        stem = arguments.name[:-4] if arguments.name.lower().endswith(".exe") else arguments.name
        old_stem = exe_name[:-4]
        renamed = []
        for it in keep:
            if it[0] == "record":
                rec = it[1].replace(exe_name.encode(), arguments.name.encode())
                rec = rec.replace(old_stem.encode() + b" .\\", stem.encode() + b" .\\")
                renamed.append(("record", rec))
            elif it[0] == "blob" and it[1] == exe_name:
                renamed.append(("blob", arguments.name, it[2]))
            else:
                renamed.append(it)
        keep = renamed
        rest = header.split(b" ", 1)[1] if b" " in header else b""
        header = stem.capitalize().encode() + b" " + rest

    if arguments.package:
        ceu = [it for it in keep if it[0] == "blob" and it[1].lower().endswith(".ceu")]
        if len(ceu) != 1:
            raise SystemExit("template must contain exactly one .CEU to rename the package")
        old_package = ceu[0][1][:-4].encode()
        new_package = arguments.package.encode()
        renamed = []
        for it in keep:
            if it[0] == "record":
                renamed.append(("record", it[1].replace(old_package, new_package)))
            elif it[0] == "blob" and it[1] == ceu[0][1]:
                renamed.append(("blob", arguments.package + it[1][-4:], it[2]))
            else:
                renamed.append(it)
        keep = renamed
        rest = header.split(b" ", 1)[1] if b" " in header else b""
        header = new_package + b" " + rest

    open(arguments.output, "wb").write(cei.build(header, keep))
    print(f"wrote {arguments.output}: program {exe_name} -> {len(program)} bytes")


main()
