r"""Check an AutoPC .cei package against what the device's installer accepts.

    python3 checkcei.py package.cei --machine x86

The rules come from the installers, ApcLoad.exe, of the Clarion AutoPC 310C
(sh3) and the Clarion Joyride (x86):

- The header is name, title, format and at least four more numbers. The
  310C accepts formats 6 and 7 and reads only the first 7 fields. The Joyride
  accepts 6, 7 and 8.
- The 10th header field is the processor (PE machine). The 310C doesn't read
  it. The Joyride accepts 0, or 332 only in a format 8 header: for format 7 or
  older any nonzero processor is "compiled for a different platform". A 7-field
  header has no processor, and the Joyride takes it as 332, so it refuses one.
- The 13th header field is the length of a certificate block. Packages are
  built without one, so it must be 0.
- On the Joyride, folder, file, registry value and speech template entries
  (`1 name`, `2 name`, `7 name`, `9 name`) can carry two checksums after the
  name. Unless they're absent or 0 the installer recomputes them from the
  entry and refuses a mismatch ("The installation file is corrupted"), as
  happens when a file in a package is replaced. See cei.py.
- Every file's data is as long as its record says, nothing follows the last
  file, and a .CEU's sections (`TargetInformation 67 ...`, then any
  `<name> <length> ...`) fill it exactly."""
import argparse
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import cei

MACHINES = {"sh3": 0x1A2, "x86": 0x14C}
SUPPORTED_FORMATS = {"sh3": {6, 7}, "x86": {6, 7, 8}}
LAST_FORMAT_WITHOUT_X86 = 7
HEADER_FORMAT_FIELD = 2
HEADER_MACHINE_FIELD = 9
HEADER_CERTIFICATE_FIELD = 12
MINIMUM_HEADER_FIELDS = 7
CEU_SECTION = re.compile(rb"(\S+) (\d+) ")


def allowed_machines(machine, format_number):
    if machine == "x86" and format_number <= LAST_FORMAT_WITHOUT_X86:
        return {0}
    return {0, MACHINES[machine]}


def header_problems(header, machine):
    fields = header.split(b" ")
    if len(fields) < MINIMUM_HEADER_FIELDS:
        return ["header has %d fields, the installer needs at least %d" % (len(fields), MINIMUM_HEADER_FIELDS)]
    found = []
    format_number = int(fields[HEADER_FORMAT_FIELD])
    if format_number not in SUPPORTED_FORMATS[machine]:
        found.append("header format %d, the %s installer accepts %s" % (format_number, machine, sorted(SUPPORTED_FORMATS[machine])))
    if machine == "x86" and len(fields) <= HEADER_MACHINE_FIELD:
        found.append("header has no processor field, which the x86 installer takes as 332 and refuses in a format %d header" % format_number)
    if machine == "x86" and len(fields) > HEADER_MACHINE_FIELD:
        header_machine = int(fields[HEADER_MACHINE_FIELD])
        allowed = allowed_machines(machine, format_number)
        if header_machine not in allowed:
            found.append("header processor %d in a format %d header, %s needs one of %s" % (header_machine, format_number, machine, sorted(allowed)))
    if len(fields) > HEADER_CERTIFICATE_FIELD and int(fields[HEADER_CERTIFICATE_FIELD], 16):
        found.append("header has a certificate block of %s bytes" % fields[HEADER_CERTIFICATE_FIELD].decode())
    return found


def ceu_problems(name, data):
    position = 0
    previous = None
    while position < len(data):
        section = CEU_SECTION.match(data, position)
        if not section or section.end() + int(section.group(2)) > len(data):
            if not section and previous is None:
                return ["%s has no TargetInformation" % name]
            if section:
                previous = section
            return ["%s %s says %s bytes, has %d" % (name, previous.group(1).decode("latin-1"), previous.group(2).decode(), len(data) - previous.end())]
        previous = section
        position = section.end() + int(section.group(2))
    return []


def item_problems(items, machine):
    found = []
    for index, item in enumerate(items):
        if item[0] == "tail" and item[1]:
            found.append("%d bytes after the last record" % len(item[1]))
        elif item[0] == "blob":
            declared = int(cei.FILE_RECORD.search(items[index - 1][1]).group(2))
            if len(item[2]) != declared:
                found.append("%s has %d bytes, its record says %d" % (item[1], len(item[2]), declared))
            if item[1].lower().endswith(".ceu"):
                found += ceu_problems(item[1], item[2])
    if machine == "x86":
        found += cei.checksum_problems(items)
    return found


def problems(data, machine):
    header, items = cei.parse(data)
    return header_problems(header, machine) + item_problems(items, machine)


def main():
    parser = argparse.ArgumentParser(description="Check an AutoPC .cei package against what the device's installer accepts")
    parser.add_argument("package")
    parser.add_argument("--machine", choices=sorted(MACHINES), required=True, help="processor of the device it's for")
    arguments = parser.parse_args()
    found = problems(open(arguments.package, "rb").read(), arguments.machine)
    for problem in found:
        print("%s: %s" % (arguments.package, problem))
    sys.exit(1 if found else 0)


if __name__ == "__main__":
    main()
