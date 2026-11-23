r"""Read and write AutoPC .cei installer packages as a tree of entries.

See docs/cei-format.md for the format. parse() and serialize() round-trip
packages from every CEIBuild generation byte for byte."""
import dataclasses
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import cei

FOLDER, FILE, SPEECH, DATABASES, DATABASE, KEY, VALUE, GROUP, TEMPLATE, PHRASE = 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
CONTAINERS = {FOLDER, SPEECH, DATABASES, KEY, GROUP, TEMPLATE}
LEAVES = {FILE, DATABASE, VALUE, PHRASE}
CHECKSUMMED = {FOLDER, FILE, DATABASE, VALUE, TEMPLATE}
REG_SZ, REG_BINARY, REG_DWORD, REG_MULTI_SZ = 1, 3, 4, 7
ESCAPES = {"\t": "|T", "\n": "|N", "\f": "|F", "\r": "|R", " ": "|B"}
EMPTY = "|Z"
NONE = "-"
MAXIMUM_ESCAPED = 0x103
MAXIMUM_RECORD = 0x209
SYSTEMTIME_FIELDS = 8
TIMES = 3
FLAGS = 6
SHORT_HEADER_FIELDS = 7
TEXT = "cp1252"


@dataclasses.dataclass
class Info:
    version: tuple = (0, 0)
    times: tuple = ((0,) * SYSTEMTIME_FIELDS,) * TIMES
    flags: tuple = (0,) * FLAGS
    shortcut: str = None
    origin: str = None


@dataclasses.dataclass
class Node:
    kind: int
    name: str
    dynamic: int = 0
    numbers: int = None
    checksums: tuple = None
    info: Info = None
    data: bytes = b""
    value_type: int = 0
    value_flags: int = 0
    value: object = None
    number: int = 0
    database: tuple = (0,) * 6
    children: list = dataclasses.field(default_factory=list)


@dataclasses.dataclass
class Package:
    name: str
    title: str = ""
    fields: list = dataclasses.field(default_factory=list)
    entry_numbers: int = 3
    nodes: list = dataclasses.field(default_factory=list)

    @property
    def format(self):
        return self.fields[0]


def escape(text):
    if text is None:
        return NONE
    if text == "":
        return EMPTY
    if "|" in text:
        raise ValueError("%r: the installer can't read a '|' in text" % text)
    escaped = "".join(ESCAPES.get(character, character) for character in text)
    if len(escaped) > MAXIMUM_ESCAPED:
        raise ValueError("%r is longer than the installer's %d characters" % (text, MAXIMUM_ESCAPED))
    return escaped


def unescape(field):
    text = field.decode(TEXT)
    if text == NONE:
        return None
    return cei.unescape(text)


def encode(text):
    return escape(text).encode(TEXT)


def records_of(data):
    header_end = data.index(b"\x00")
    position = header_end + 1
    records = []
    while position < len(data):
        if data.startswith(b"\x00\x00", position):
            records.append(None)
            position += 2
            continue
        end = data.index(b"\x00", position)
        records.append(data[position:end])
        position = end + 1
        match = cei.FILE_RECORD.search(records[-1])
        if match:
            size = int(match.group(2))
            records.append(data[position:position + size])
            position += size
    return data[:header_end], records


class Reader:
    def __init__(self, records, entry_numbers):
        self.records = records
        self.position = 0
        self.entry_numbers = entry_numbers

    def next(self):
        record = self.records[self.position]
        self.position += 1
        return record

    def nodes(self, root):
        found = []
        while self.position < len(self.records):
            record = self.next()
            if record is None:
                if root:
                    raise ValueError("end of list at the top level")
                return found
            found.append(self.node(record))
        if not root:
            raise ValueError("package ends inside a list")
        return found

    def node(self, record):
        fields = record.split(b" ")
        kind = int(fields[0])
        numbers = [int(field) for field in fields[2:]]
        if len(numbers) not in (0, 2, 3):
            raise ValueError("entry %r has %d numbers" % (record, len(numbers)))
        node = Node(kind, unescape(fields[1]))
        if len(numbers) != self.entry_numbers:
            node.numbers = len(numbers)
        if numbers:
            node.checksums = tuple(numbers[:2])
        if len(numbers) > 2:
            node.dynamic = numbers[2]
        if kind in (FOLDER, FILE):
            node.info, size = parse_info(self.next())
            if kind == FILE:
                node.data = self.next()
                if len(node.data) != size:
                    raise ValueError("%s is truncated" % node.name)
        elif kind == DATABASE:
            node.database = tuple(int(field) for field in self.next().split(b" "))
        elif kind == VALUE:
            node.value_type, node.value_flags = (int(field) for field in self.next().split(b" "))
            node.value = parse_value(node.value_type, self.next())
        elif kind == TEMPLATE:
            node.number = int(self.next())
        elif kind not in CONTAINERS and kind != PHRASE:
            raise ValueError("unknown entry type %d" % kind)
        if kind in CONTAINERS:
            node.children = self.nodes(False)
        return node


def parse_info(record):
    fields = record.split(b" ")
    if len(fields) != cei.FILE_INFO_FIELDS:
        raise ValueError("info record %r has %d fields" % (record, len(fields)))
    numbers = [int(field) for field in fields[:32]]
    times = tuple(tuple(numbers[2 + index * SYSTEMTIME_FIELDS:2 + (index + 1) * SYSTEMTIME_FIELDS]) for index in range(TIMES))
    info = Info((numbers[0], numbers[1]), times, tuple(numbers[26:32]), unescape(fields[32]), unescape(fields[33]))
    return info, int(fields[34])


def parse_value(value_type, record):
    if value_type == REG_DWORD:
        return int(record)
    if value_type == REG_SZ:
        return unescape(record)
    if value_type in (REG_BINARY, REG_MULTI_SZ):
        return cei.hex_bytes(record)
    raise ValueError("unknown registry value type %d" % value_type)


def parse(data):
    header, records = records_of(data)
    fields = header.split(b" ")
    package = Package(unescape(fields[0]), unescape(fields[1]))
    for field in fields[2:]:
        package.fields.append(field.decode(TEXT))
    package.fields = [int(field) if field.isdigit() else field for field in package.fields]
    package.entry_numbers = entry_numbers(records)
    package.nodes = Reader(records, package.entry_numbers).nodes(True)
    return package


def entry_numbers(records):
    counts = {}
    for record in records:
        if record and record[:2] in (b"1 ", b"6 ") and len(record.split(b" ")) - 2 in (0, 2, 3):
            count = len(record.split(b" ")) - 2
            counts[count] = counts.get(count, 0) + 1
    return max(counts, key=counts.get) if counts else 0


def info_record(info, size):
    numbers = list(info.version)
    for time in info.times:
        numbers += list(time)
    numbers += list(info.flags)
    fields = [str(number).encode() for number in numbers]
    fields += [encode(info.shortcut), encode(info.origin), str(size).encode()]
    return b" ".join(fields)


def hex_record(data):
    return b",".join(b"%x" % byte for byte in data)


def value_record(node):
    if node.value_type == REG_DWORD:
        return str(node.value).encode()
    if node.value_type == REG_SZ:
        return encode(node.value)
    if node.value_type in (REG_BINARY, REG_MULTI_SZ):
        return hex_record(node.value)
    raise ValueError("unknown registry value type %d" % node.value_type)


def body_records(node):
    if node.kind in (FOLDER, FILE):
        records = [info_record(node.info, len(node.data))]
        if node.kind == FILE:
            records.append(node.data)
        return records
    if node.kind == DATABASE:
        return [b" ".join(str(number).encode() for number in node.database)]
    if node.kind == VALUE:
        return [b"%d %d" % (node.value_type, node.value_flags), value_record(node)]
    if node.kind == TEMPLATE:
        return [str(node.number).encode()]
    return []


def checksums(node):
    if node.checksums is not None:
        return node.checksums
    if node.kind not in CHECKSUMMED:
        return 0, 0
    body = body_records(node)
    value = body[1] if node.kind in (FILE, VALUE) else None
    computed = cei.entry_checksum(node.kind, body[0], value)
    if computed is None:
        raise ValueError("can't compute checksums for %s" % node.name)
    return computed


def computed_checksums(node):
    saved = node.checksums
    node.checksums = None
    try:
        return checksums(node)
    finally:
        node.checksums = saved


def name_record(node, numbers):
    if node.numbers is not None:
        numbers = node.numbers
    record = b"%d %s" % (node.kind, encode(node.name))
    if numbers >= 2:
        record += b" %d %d" % checksums(node)
    if numbers >= 3:
        record += b" %d" % node.dynamic
    return record


def write_nodes(out, nodes, numbers):
    for node in nodes:
        out += name_record(node, numbers) + b"\x00"
        body = body_records(node)
        for index, record in enumerate(body):
            out += record
            if not (node.kind == FILE and index == 1):
                out += b"\x00"
        if node.kind in CONTAINERS:
            write_nodes(out, node.children, numbers)
            out += b"\x00\x00"


def header_record(package):
    fields = [encode(package.name), encode(package.title)]
    for field in package.fields:
        fields.append(encode(field) if isinstance(field, str) else str(field).encode())
    return b" ".join(fields)


def serialize(package):
    out = bytearray(header_record(package) + b"\x00")
    write_nodes(out, package.nodes, package.entry_numbers)
    return bytes(out)


def walk(nodes, path=()):
    for node in nodes:
        yield path + (node.name,), node
        yield from walk(node.children, path + (node.name,))
