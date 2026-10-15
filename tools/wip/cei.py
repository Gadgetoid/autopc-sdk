"""Parse and rebuild a Clarion AutoPC .cei installer package.

A header line, then NUL-terminated ASCII records. A record ending with
`.\\<name> <size>` is a file entry; the next <size> raw bytes after its
terminating NUL are the file's data (may contain NULs). Parsing then resumes."""
import re

FILE_RECORD = re.compile(rb"\.\\([^ \\]+) (\d+)$")


def parse(data):
    header_end = data.index(b"\x00")
    header = data[:header_end]
    items = []          # ("record", bytes) or ("blob", name, bytes)
    pos = header_end
    while pos < len(data):
        assert data[pos] == 0
        pos += 1
        if pos >= len(data):
            break
        end = data.index(b"\x00", pos)
        record = data[pos:end]
        items.append(("record", record))
        match = FILE_RECORD.search(record)
        if match:
            size = int(match.group(2))
            blob = data[end + 1:end + 1 + size]
            items.append(("blob", match.group(1).decode("latin-1"), blob))
            pos = end + 1 + size
        else:
            pos = end
    return header, items


def build(header, items):
    out = bytearray(header)
    i = 0
    while i < len(items):
        if items[i][0] == "record":
            out += b"\x00" + items[i][1]
            if i + 1 < len(items) and items[i + 1][0] == "blob":
                out += b"\x00" + items[i + 1][2]
                i += 2
                continue
        i += 1
    return bytes(out)
