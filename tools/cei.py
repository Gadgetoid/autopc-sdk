"""Parse and rebuild a Clarion AutoPC .cei installer package.

A header, then NUL-terminated ASCII records. A record ending with
`\\<name> <size>` is a file entry: CEIBuild writes the source path relative
(`.\\hello.exe`), Microsoft's SDK packager writes it absolute. The next <size>
raw bytes after its NUL terminator are the file's data. Records can be empty
(consecutive NULs).

Folder (1), file (2) and registry value (7) entries carry two checksums after
the name, then in format 8 headers one more number."""
import re

FILE_RECORD = re.compile(rb"\\([^ \\]+) (\d+)$")
CHECKSUMMED_ENTRY = re.compile(rb"^([127]) (\S+) (\d+) (\d+)((?: \d+)?)$")


def parse(data):
    header_end = data.index(b"\x00")
    header = data[:header_end]
    items = []
    pos = header_end + 1
    while pos <= len(data):
        end = data.find(b"\x00", pos)
        if end == -1:
            items.append(("tail", data[pos:]))
            break
        record = data[pos:end]
        items.append(("record", record))
        pos = end + 1
        match = FILE_RECORD.search(record)
        if match:
            size = int(match.group(2))
            items.append(("blob", match.group(1).decode("latin-1"), data[pos:pos + size]))
            pos += size
    return header, items


def build(header, items):
    out = bytearray(header)
    out += b"\x00"
    i = 0
    while i < len(items):
        kind = items[i][0]
        if kind == "record":
            out += items[i][1] + b"\x00"
            if i + 1 < len(items) and items[i + 1][0] == "blob":
                out += items[i + 1][2]
                i += 2
                continue
        elif kind == "tail":
            out += items[i][1]
        i += 1
    return bytes(out)


def entry_checksums(record):
    match = CHECKSUMMED_ENTRY.match(record)
    if not match:
        return None
    return int(match.group(3)), int(match.group(4))


def clear_checksums(items):
    cleared = []
    for item in items:
        match = CHECKSUMMED_ENTRY.match(item[1]) if item[0] == "record" else None
        if match and (int(match.group(3)) or int(match.group(4))):
            if match.group(1) in (b"1", b"2") and not match.group(5):
                item = ("record", match.group(1) + b" " + match.group(2))
            else:
                item = ("record", b"%s %s 0 0%s" % (match.group(1), match.group(2), match.group(5)))
        cleared.append(item)
    return cleared
