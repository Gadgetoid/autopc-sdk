"""Parse and rebuild a Clarion AutoPC .cei installer package.

A header, then NUL-terminated ASCII records. A record ending with
`\\<name> <size>` is a file entry: CEIBuild writes the source path relative
(`.\\hello.exe`), Microsoft's SDK packager writes it absolute. The next <size>
raw bytes after its NUL terminator are the file's data. Records can be empty
(consecutive NULs).

Folder (1), file (2), registry value (7) and speech template (9) entries can
carry two checksums after the name, then in format 8 headers one more number.
The next record describes the entry; a file's data or a registry value follows
it. The checksums are the byte count and byte sum of the entry as the installer
holds it, each XORed with KEY. 0 0, or none, skips the check.

The installer converts text to UTF-16 and sums only wcslen(text) bytes of it,
the first half of the characters, and Microsoft's CEIBuild does the same."""
import re
import struct

FILE_RECORD = re.compile(rb"\\([^ \\]+) (\d+)$")
ENTRY = re.compile(rb"^([1279]) (\S+)(?: (\d+) (\d+))?((?: \d+)?)$")
KEY = 0x5F9A63CB
ESCAPES = {"B": " ", "F": "\f", "N": "\n", "R": "\r", "T": "\t"}
FILE_INFO_FIELDS = 35
FOLDER, FILE, REGISTRY_VALUE, SPEECH_TEMPLATE = 1, 2, 7, 9
REG_SZ, REG_DWORD = 1, 4


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


def unescape(text):
    out = []
    index = 0
    while index < len(text):
        if text[index] == "|" and index + 1 < len(text):
            out.append(ESCAPES.get(text[index + 1], ""))
            index += 2
        else:
            out.append(text[index])
            index += 1
    return "".join(out)


def text_checksum(field):
    wide = unescape(field.decode("cp1252", errors="replace")).encode("utf-16-le")
    characters = len(wide) // 2
    return sum(wide[:characters]), characters


def packed_checksum(data):
    return sum(data), len(data)


def dwords(*values):
    return struct.pack("<%dI" % len(values), *(value & 0xFFFFFFFF for value in values))


def file_checksum(kind, info, data):
    fields = info.split(b" ")
    if len(fields) != FILE_INFO_FIELDS:
        return None
    numbers = [int(field) for field in fields[:32]]
    size = int(fields[34])
    parts = [packed_checksum(struct.pack("<26H", *numbers[:26])), packed_checksum(dwords(*numbers[26:32])),
             text_checksum(fields[32]), text_checksum(fields[33]), packed_checksum(dwords(size))]
    if kind == FILE:
        parts.append(packed_checksum(data[:size]))
    return parts


def registry_checksum(info, value):
    fields = info.split(b" ")
    if len(fields) != 2:
        return None
    value_type = int(fields[0])
    parts = [packed_checksum(dwords(value_type, int(fields[1])))]
    if value_type == REG_DWORD:
        parts.append(packed_checksum(dwords(int(value))))
    elif value_type == REG_SZ:
        parts.append(text_checksum(value))
    else:
        return None
    return parts



def entry_checksum(kind, info, value):
    try:
        if kind in (FOLDER, FILE):
            parts = file_checksum(kind, info, value)
        elif kind == REGISTRY_VALUE:
            parts = registry_checksum(info, value)
        else:
            parts = [packed_checksum(dwords(int(info)))]
    except ValueError:
        return None
    if parts is None:
        return None
    total = sum(part[0] for part in parts)
    count = sum(part[1] for part in parts)
    return (count ^ KEY) & 0xFFFFFFFF, (total ^ KEY) & 0xFFFFFFFF


def entries(items):
    index = 0
    while index < len(items):
        item = items[index]
        match = ENTRY.match(item[1]) if item[0] == "record" else None
        following = items[index + 1] if index + 1 < len(items) else None
        if not match or not following or following[0] != "record":
            index += 1
            continue
        kind = int(match.group(1))
        if kind in (FOLDER, FILE) and len(following[1].split(b" ")) != FILE_INFO_FIELDS:
            index += 1
            continue
        value = None
        consumed = 2
        if kind in (FILE, REGISTRY_VALUE):
            value_item = items[index + 2] if index + 2 < len(items) else None
            expected = "blob" if kind == FILE else "record"
            if not value_item or value_item[0] != expected:
                index += 1
                continue
            value = value_item[2] if kind == FILE else value_item[1]
            consumed = 3
        yield index, match, entry_checksum(kind, following[1], value)
        index += consumed


def stored_checksums(match):
    if match.group(3) is None:
        return None
    return int(match.group(3)), int(match.group(4))


def set_checksums(items):
    updated = list(items)
    for index, match, checksums in entries(items):
        if checksums is None:
            continue
        updated[index] = ("record", b"%s %s %d %d%s" % (match.group(1), match.group(2), checksums[0], checksums[1], match.group(5)))
    return updated


def checksum_problems(items):
    found = []
    for index, match, checksums in entries(items):
        stored = stored_checksums(match)
        if not stored or not any(stored):
            continue
        record = items[index][1].decode("latin-1")
        if checksums is None:
            found.append("entry %r has checksums this tool can't verify" % record)
        elif stored != checksums:
            found.append("entry %r has checksums %d %d, its contents give %d %d" % (record, stored[0], stored[1], checksums[0], checksums[1]))
    return found
