"""Build an AutoPC .cei installer by swapping your program into a template .cei.

A .cei is a custom AutoPC installer package; generating a valid one from scratch
needs install-time validation against the device's resident OS, which we do not
have yet. This takes a known-good .cei as a template and replaces its single
program with yours, keeping the proven structure. EXPERIMENTAL and not yet
install-tested on hardware.

    python3 mkcei.py template.cei program.exe out.cei [--minimal]

--minimal also drops the template's other embedded files, leaving the folder
tree and your program."""
import argparse
import re

import cei


def main():
    parser = argparse.ArgumentParser(description="Swap a program into a template AutoPC .cei")
    parser.add_argument("template")
    parser.add_argument("program")
    parser.add_argument("output")
    parser.add_argument("--minimal", action="store_true", help="drop the template's other files")
    arguments = parser.parse_args()

    header, items = cei.parse(open(arguments.template, "rb").read())
    program = open(arguments.program, "rb").read()

    exe = [it for it in items if it[0] == "blob" and it[1].lower().endswith(".exe")]
    if len(exe) != 1:
        raise SystemExit("template must contain exactly one .exe")
    exe_name = exe[0][1]

    keep = []
    index = 0
    while index < len(items):
        kind = items[index][0]
        if kind == "blob" and items[index][1] == exe_name:
            keep.append(("blob", exe_name, program))
            index += 1
            continue
        if arguments.minimal and kind == "blob" and items[index][1] != exe_name:
            name = items[index][1].encode()
            while keep and keep[-1][0] == "record" and (name in keep[-1][1] or keep[-1][1] in (b"0", b"")):
                keep.pop()
            index += 1
            continue
        if kind == "record":
            keep.append(("record", re.sub(rb"(\." + re.escape(b"\\") + re.escape(exe_name.encode()) + rb") \d+$",
                                           rb"\1 %d" % len(program), items[index][1])))
        else:
            keep.append(items[index])
        index += 1

    open(arguments.output, "wb").write(cei.build(header, keep))
    print(f"wrote {arguments.output}: program {exe_name} -> {len(program)} bytes")


main()
