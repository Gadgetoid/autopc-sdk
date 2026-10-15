#!/usr/bin/env python3
"""Replace osupdate.exe in a BurnOS B000FF image with our own CE2 SH3 program.

Keeps the module's name so whatever launches "osupdate.exe" runs our code instead.
The program's sections, module header and section table are appended after the
image; osupdate's table entry is repointed at them.
"""
import argparse
import struct
import sys

ADDRESS_MASK = 0x1FFFFFFF
HEADER_FIELDS = ["dllfirst", "dlllast", "physfirst", "physlast", "nummods", "ramstart", "ramfree", "ramend",
                 "copyentries", "copyoffset", "profilelen", "profileoffset", "numfiles"]
HEADER_SIZE = 0x54
MODULE_ENTRY = 32
UNIT_NAMES = ["export", "import", "resource", "exception", "security", "fixup", "debug", "description", "machine"]
E32_UNITS_OFFSET = 24
E32_SIZE = E32_UNITS_OFFSET + 8 * len(UNIT_NAMES)
O32_ENTRY = 24
SUBSYSTEM_WINDOWSCE_GUI = 9


def u32(data, offset):
    return struct.unpack_from("<I", data, offset)[0]


def read_b000ff(data):
    if data[:7] != b"B000FF\n":
        raise SystemExit("not a B000FF image")
    image_start, image_length = struct.unpack_from("<II", data, 7)
    position = 15
    image = bytearray(b"\x00" * image_length)
    entry = None
    while position + 12 <= len(data):
        address, length, checksum = struct.unpack_from("<III", data, position)
        position += 12
        if address == 0 and checksum == 0:
            entry = length
            break
        chunk = data[position:position + length]
        position += length
        image[address - image_start:address - image_start + length] = chunk
    if entry is None:
        raise SystemExit("no entry record")
    return image_start, image, entry


def write_b000ff(image_start, image, entry):
    out = bytearray(b"B000FF\n")
    out += struct.pack("<II", image_start, len(image))
    out += struct.pack("<III", image_start, len(image), sum(image) & 0xFFFFFFFF)
    out += image
    out += struct.pack("<III", 0, entry, 0)
    return bytes(out)


def find_header(image, base):
    for offset in range(0, len(image) - HEADER_SIZE, 4):
        fields = dict(zip(HEADER_FIELDS, struct.unpack_from(f"<{len(HEADER_FIELDS)}I", image, offset)))
        physfirst, physlast = fields["physfirst"] & ADDRESS_MASK, fields["physlast"] & ADDRESS_MASK
        if physfirst & 0xFFF or not physfirst < physlast or not 1 <= fields["nummods"] <= 1000:
            continue
        if not fields["ramstart"] <= fields["ramfree"] <= fields["ramend"]:
            continue
        if (base & ADDRESS_MASK) != physfirst:
            continue
        return offset, fields
    raise SystemExit("no ROM header found")


def parse_pe(data):
    pe = u32(data, 0x3C)
    if data[pe:pe + 4] != b"PE\0\0":
        raise SystemExit("not a PE")
    machine, sections = struct.unpack_from("<HH", data, pe + 4)
    optional = pe + 24
    entry = u32(data, optional + 16)
    image_base = u32(data, optional + 28)
    image_size = u32(data, optional + 56)
    directory_count = u32(data, optional + 92)
    directories = []
    for index in range(directory_count):
        directories.append(struct.unpack_from("<II", data, optional + 96 + 8 * index))
    optional_size = struct.unpack_from("<H", data, pe + 20)[0]
    table = optional + optional_size
    parsed = []
    for index in range(sections):
        base = table + 40 * index
        name = data[base:base + 8].rstrip(b"\0").decode("latin-1")
        virtual_size, rva, raw_size, raw_pointer = struct.unpack_from("<IIII", data, base + 8)
        flags = u32(data, base + 36)
        body = data[raw_pointer:raw_pointer + raw_size]
        parsed.append({"name": name, "virtual_size": virtual_size, "rva": rva, "flags": flags, "body": body})
    return {"entry": entry, "image_base": image_base, "image_size": image_size,
            "directories": directories, "sections": parsed}


def align(value, alignment=4):
    return (value + alignment - 1) // alignment * alignment


def section_offset(sections, rva):
    for section in sections:
        span = max(section["virtual_size"], len(section["body"]))
        if section["rva"] <= rva < section["rva"] + span:
            return section, rva - section["rva"]
    return None, None


def read_rva(sections, rva, length):
    section, offset = section_offset(sections, rva)
    return section["body"][offset:offset + length]


def string_at(sections, rva):
    section, offset = section_offset(sections, rva)
    end = section["body"].index(b"\0", offset)
    return section["body"][offset:end].decode("latin-1")


def parse_imports(pe):
    """Yield (dll_name, iat_rva, function_name) for every imported symbol."""
    sections = pe["sections"]
    import_rva = pe["directories"][1][0]
    if not import_rva:
        return
    descriptor = import_rva
    while True:
        original, _, _, name_rva, first_thunk = struct.unpack("<5I", read_rva(sections, descriptor, 20))
        descriptor += 20
        if original == 0 and name_rva == 0:
            break
        dll = string_at(sections, name_rva)
        thunks = original or first_thunk
        index = 0
        while True:
            value = struct.unpack("<I", read_rva(sections, thunks + 4 * index, 4))[0]
            if value == 0:
                break
            name = None if value & 0x80000000 else string_at(sections, (value & 0x7FFFFFFF) + 2)
            ordinal = value & 0xFFFF if value & 0x80000000 else None
            yield dll, first_thunk + 4 * index, name, ordinal
            index += 1


def dll_exports(data):
    pe = parse_pe(data)
    sections = pe["sections"]
    export_rva, export_size = pe["directories"][0]
    if not export_rva:
        return {}, {}
    table = read_rva(sections, export_rva, 40)
    ordinal_base = struct.unpack_from("<I", table, 16)[0]
    function_count, name_count = struct.unpack_from("<II", table, 20)
    functions_rva, names_rva, ordinals_rva = struct.unpack_from("<III", table, 28)
    by_name, by_ordinal = {}, {}
    functions = [struct.unpack("<I", read_rva(sections, functions_rva + 4 * index, 4))[0] for index in range(function_count)]
    for index in range(function_count):
        by_ordinal[ordinal_base + index] = pe["image_base"] + functions[index]
    for index in range(name_count):
        name_rva = struct.unpack("<I", read_rva(sections, names_rva + 4 * index, 4))[0]
        name = string_at(sections, name_rva)
        ordinal = struct.unpack("<H", read_rva(sections, ordinals_rva + 2 * index, 2))[0]
        by_name[name] = pe["image_base"] + functions[ordinal]
    return by_name, by_ordinal


def bind_imports(pe, modules):
    """Return {iat_rva: resolved_va} by resolving each import against a DLL in `modules`."""
    cache = {}
    bindings = {}
    for dll, iat_rva, name, ordinal in parse_imports(pe):
        key = dll.lower()
        if key not in cache:
            data = modules.get(key)
            if data is None:
                raise SystemExit(f"need {dll} to bind imports (pass its folder with --modules)")
            cache[key] = dll_exports(data)
        by_name, by_ordinal = cache[key]
        address = by_name[name] if name is not None else by_ordinal[ordinal]
        bindings[iat_rva] = address
    return bindings


def build_module(pe, place_at, bindings):
    """Lay out section bodies, o32 table and e32 header starting at virtual address place_at."""
    base = pe["image_base"]
    directories = pe["directories"]

    # CE pre-binds ROM module imports: write resolved addresses into the IAT.
    for iat_rva, address in bindings.items():
        section, offset = section_offset(pe["sections"], iat_rva)
        body = bytearray(section["body"])
        struct.pack_into("<I", body, offset, address)
        section["body"] = bytes(body)
    units = {name: (0, 0) for name in UNIT_NAMES}
    directory_unit = {"import": 1, "resource": 2, "exception": 3, "security": 4, "fixup": 5, "debug": 6, "export": 0}
    for name, index in directory_unit.items():
        if index < len(directories) and directories[index][1]:
            units[name] = directories[index]

    sections = [section for section in pe["sections"] if section["name"] != ".bss"]
    address = place_at
    blobs = []
    o32_entries = []
    for section in sections:
        stored = section["body"][:section["virtual_size"]] if section["body"] else b""
        pointer = address
        blobs.append((pointer, stored))
        address = align(pointer + len(stored))
        o32_entries.append(struct.pack("<6I", section["virtual_size"], section["rva"], len(stored),
                                       pointer, base + section["rva"], section["flags"]))

    e32_address = address
    o32_address = e32_address + E32_SIZE
    load_address = place_at

    e32 = struct.pack("<HHIIHHII", len(sections), 0x010B, pe["entry"], base, 2, 1, pe["image_size"], SUBSYSTEM_WINDOWSCE_GUI)
    for name in UNIT_NAMES:
        e32 += struct.pack("<II", *units[name])
    assert len(e32) == E32_SIZE

    region = bytearray()
    region_base = place_at

    def put(address, blob):
        start = address - region_base
        if start + len(blob) > len(region):
            region.extend(b"\x00" * (start + len(blob) - len(region)))
        region[start:start + len(blob)] = blob

    for pointer, stored in blobs:
        put(pointer, stored)
    put(e32_address, e32)
    put(o32_address, b"".join(o32_entries))
    return {"region": bytes(region), "e32": e32_address, "o32": o32_address, "load": load_address,
            "size": pe["image_size"], "end": o32_address + len(b"".join(o32_entries))}


def main():
    parser = argparse.ArgumentParser(description="Swap osupdate.exe in a BurnOS image for our program")
    parser.add_argument("burnos")
    parser.add_argument("program")
    parser.add_argument("output")
    parser.add_argument("--module", default="osupdate.exe", help="module name to replace")
    parser.add_argument("--modules", required=True, help="folder of extracted BurnOS modules, for binding imports")
    arguments = parser.parse_args()

    image_start, image, entry = read_b000ff(open(arguments.burnos, "rb").read())
    header_offset, header = find_header(image, image_start)
    header_address = image_start + header_offset

    table = header_offset + HEADER_SIZE
    target = None
    for index in range(header["nummods"]):
        position = table + MODULE_ENTRY * index
        attributes, time_low, time_high, size, name, e32, o32, load = struct.unpack_from("<8I", image, position)
        name_offset = (name & ADDRESS_MASK) - (image_start & ADDRESS_MASK)
        module_name = image[name_offset:image.index(b"\0", name_offset)].decode("latin-1")
        if module_name == arguments.module:
            target = position
            break
    if target is None:
        raise SystemExit(f"{arguments.module} not found")

    pe = parse_pe(open(arguments.program, "rb").read())

    import os
    modules = {}
    for name in os.listdir(arguments.modules):
        path = os.path.join(arguments.modules, name)
        if os.path.isfile(path):
            modules[name.lower()] = open(path, "rb").read()
    bindings = bind_imports(pe, modules)

    place_at = align(image_start + len(image), 0x1000)
    module = build_module(pe, place_at, bindings)

    new_image = bytearray(image)
    gap = place_at - (image_start + len(new_image))
    new_image.extend(b"\x00" * gap)
    new_image.extend(module["region"])

    # repoint osupdate's table entry: keep name/attributes/time, update size/e32/o32/load
    attributes, time_low, time_high, size, name, _, _, _ = struct.unpack_from("<8I", new_image, target)
    struct.pack_into("<8I", new_image, target, attributes, time_low, time_high, module["size"],
                     name, module["e32"], module["o32"], module["load"])

    # extend physlast to cover the appended module
    new_physlast = (image_start & ~ADDRESS_MASK) | ((image_start + len(new_image)) & ADDRESS_MASK)
    physlast_offset = header_offset + HEADER_FIELDS.index("physlast") * 4
    struct.pack_into("<I", new_image, physlast_offset, new_physlast)

    open(arguments.output, "wb").write(write_b000ff(image_start, bytes(new_image), entry))
    print(f"replaced {arguments.module}: module at {place_at:08X}, e32 {module['e32']:08X}, "
          f"o32 {module['o32']:08X}, image now {len(new_image)} bytes")


main()
