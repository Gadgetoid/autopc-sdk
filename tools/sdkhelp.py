r"""Add the Auto PC SDK's help to its headers as documentation comments.

Reads the HTML pages of the SDK's compiled help (.chm files, unpacked with 7zz
or 7z, or folders already unpacked) and writes a /** */ block above each
declaration a page describes: interfaces and their methods, functions,
structures and their members, and #define'd messages. Editors show these in
hovers and completions.

    python3 tools/sdkhelp.py Online_help_files/wceapc.chm Online_help_files/wcesdkr.chm --headers sdk/include --headers sdk/compat

Where two help files have a page with the same name, the first one given wins.

The blocks this writes start with a line holding only /**, end with one holding
only */, and every line between starts with *, so a second run can find and
replace them rather than adding more.
Interfaces and functions the headers only declare with an A or W suffix, such
as IVoiceCmdW, get the page for the unsuffixed name.

clang doesn't attach comments to members of a class whose name comes from a
macro argument, as DECLARE_INTERFACE_ gives it. So each documented interface
gets, for C++ only, the struct line DECLARE_INTERFACE_ expands to:

    #if defined(__cplusplus) && !defined(CINTERFACE)
    struct IASLabel : public IASControl
    #else
    DECLARE_INTERFACE_(IASLabel, IASControl)
    #endif

A second run unwraps these too."""
import argparse
import html
import os
import re
import shutil
import subprocess
import sys
import tempfile
import textwrap
import unicodedata

WIDTH = 100
SECTION_PARAMETERS = ("Parameters",)
SECTION_MEMBERS = ("Members",)
SECTION_RETURNS = ("Return Values", "Return Value")
SECTION_REMARKS = ("Remarks",)
ASCII_REPLACEMENTS = {
    "‘": "'", "’": "'", "“": '"', "”": '"', "–": "-", "—": "-",
    "…": "...", " ": " ", "®": "(R)", "©": "(c)", "™": "(TM)", "°": " degrees",
    "×": "x", "•": "-",
}


def ascii_text(text):
    for original, replacement in ASCII_REPLACEMENTS.items():
        text = text.replace(original, replacement)
    text = unicodedata.normalize("NFKD", text).encode("ascii", "ignore").decode("ascii")
    return text.replace("/*", "/ *").replace("*/", "* /")


def plain(fragment):
    fragment = re.sub(r"<br\s*/?>", " ", fragment, flags=re.I)
    fragment = re.sub(r"<[^>]+>", "", fragment)
    text = ascii_text(html.unescape(fragment))
    return re.sub(r"\s+", " ", text).strip()


def preformatted(fragment):
    fragment = re.sub(r"<br\s*/?>", "\n", fragment, flags=re.I)
    fragment = re.sub(r"<[^>]+>", "", fragment)
    lines = ascii_text(html.unescape(fragment)).replace("\t", "    ").splitlines()
    while lines and not lines[0].strip():
        lines.pop(0)
    while lines and not lines[-1].strip():
        lines.pop()
    return lines


def definition_list(fragment):
    tokens = re.split(r"(<dl[^>]*>|</dl>|<dt[^>]*>|<dd[^>]*>)", fragment, flags=re.I)
    pairs = []
    depth = 0
    term = None
    current = None
    for token in tokens:
        lower = token.lower()
        if lower.startswith("<dl"):
            depth += 1
            if depth > 1 and current is not None:
                current.append(token)
            continue
        if lower == "</dl>":
            depth -= 1
            if depth >= 1 and current is not None:
                current.append(token)
            continue
        if depth == 1 and lower.startswith("<dt"):
            term = []
            current = term
            pairs.append([term, []])
            continue
        if depth == 1 and lower.startswith("<dd"):
            if pairs:
                current = pairs[-1][1]
            continue
        if current is not None:
            current.append(token)
    return [(plain("".join(name)), "".join(description)) for name, description in pairs]


def paragraphs(fragment):
    parts = []
    for piece in re.split(r"(<pre[^>]*>.*?</pre>|<dl[^>]*>.*</dl>)", fragment, flags=re.I | re.S):
        lower = piece[:4].lower()
        if lower.startswith("<pre"):
            parts.append(preformatted(piece))
        elif lower.startswith("<dl"):
            for term, description in definition_list(piece):
                text = " ".join(item for item in paragraphs(description) if isinstance(item, str))
                parts.append(f"- {term}: {text}" if text else f"- {term}")
        else:
            for paragraph in re.split(r"<p[^>]*>|</p>|<li[^>]*>", piece, flags=re.I):
                text = plain(paragraph)
                if text:
                    parts.append(text)
    return parts


def parse_page(path):
    source = open(path, encoding="cp1252", errors="replace").read()
    heading = re.search(r"<h2[^>]*>(.*?)</h2>", source, re.I | re.S)
    if not heading:
        return None
    title = plain(heading.group(1))
    body = source[heading.end():]
    body = re.split(r"</body>", body, flags=re.I)[0]
    sections = re.split(r"<h4[^>]*>(.*?)</h4>", body, flags=re.I | re.S)
    page = {"title": title, "file": os.path.basename(path), "summary": [], "parameters": [], "members": [], "returns": [], "remarks": []}
    page["summary"] = [item for item in paragraphs(sections[0]) if isinstance(item, str)][:1]
    for index in range(1, len(sections) - 1, 2):
        name = plain(sections[index])
        content = sections[index + 1]
        if name in SECTION_PARAMETERS or name in SECTION_MEMBERS:
            entries = []
            dl = re.search(r"<dl[^>]*>.*</dl>", content, re.I | re.S)
            for term, description in definition_list(dl.group(0)) if dl else []:
                entries.append((term, paragraphs(description)))
            page["parameters" if name in SECTION_PARAMETERS else "members"] = entries
        elif name in SECTION_RETURNS:
            page["returns"] = paragraphs(content)
        elif name in SECTION_REMARKS:
            page["remarks"] = paragraphs(content)
    return page


def unpack(paths, scratch):
    folders = []
    for path in paths:
        if os.path.isdir(path):
            folders.append(path)
            continue
        tool = shutil.which("7zz") or shutil.which("7z")
        if not tool:
            sys.exit("sdkhelp: unpacking .chm files needs 7zz or 7z")
        folder = os.path.join(scratch, os.path.splitext(os.path.basename(path))[0])
        subprocess.run([tool, "x", "-y", f"-o{folder}", path], check=True, stdout=subprocess.DEVNULL)
        folders.append(folder)
    return folders


def load_pages(folders):
    pages = {}
    for folder in folders:
        for root, _, files in os.walk(folder):
            for name in sorted(files):
                if not name.lower().endswith((".htm", ".html")):
                    continue
                page = parse_page(os.path.join(root, name))
                if page and re.fullmatch(r"\w+(::\w+)?", page["title"]):
                    pages.setdefault(page["title"].lower(), page)
    return pages


def wrap(text, prefix, indent):
    width = max(WIDTH - len(prefix), 40)
    lines = textwrap.wrap(text, width, break_long_words=False, break_on_hyphens=False) or [""]
    return [prefix + lines[0]] + [prefix + indent + line for line in lines[1:]]


def render_paragraphs(items, prefix, first_indent=""):
    lines = []
    for item in items:
        if lines:
            lines.append(prefix.rstrip())
        if isinstance(item, list):
            lines += [(prefix + "    " + line).rstrip() for line in item]
        else:
            lines += wrap(item, prefix + first_indent, "")
    return lines


def comment(indent, page, include_parameters=True):
    body = []
    if page["summary"]:
        body += wrap(page["summary"][0], " * ", "")
    if include_parameters and page["parameters"]:
        body.append(" *")
        for name, description in page["parameters"]:
            text = " ".join(item for item in description if isinstance(item, str))
            body += wrap(f"@param {name} {text}".rstrip(), " * ", "  ")
    if include_parameters and page["returns"]:
        body.append(" *")
        prose = [item for item in page["returns"] if isinstance(item, str)]
        body += wrap("@return " + " ".join(prose), " * ", "  ")
    if page["remarks"]:
        body.append(" *")
        body += render_paragraphs(page["remarks"], " * ")
    if not body:
        return []
    return [indent + "/**"] + [(indent + line).rstrip() for line in body] + [indent + " */"]


def member_comment(indent, description):
    body = render_paragraphs(description, " * ")
    if not body:
        return []
    return [indent + "/**"] + [(indent + line).rstrip() for line in body] + [indent + " */"]


CPLUSPLUS_ONLY = "#if defined(__cplusplus) && !defined(CINTERFACE)"
INTERFACE = re.compile(r"(\s*)DECLARE_INTERFACE(_?)\s*\(\s*(\w+)\s*(?:,\s*(\w+)\s*)?\)(.*)")


def plain_struct(line):
    match = INTERFACE.match(line)
    indent, _, name, base, rest = match.groups()
    return f"{indent}struct {name}" + (f" : public {base}" if base else "") + rest


def unwrap_interfaces(lines):
    kept = []
    index = 0
    while index < len(lines):
        window = lines[index:index + 5]
        if (len(window) == 5 and window[0] == CPLUSPLUS_ONLY and window[2] == "#else" and window[4] == "#endif"
                and INTERFACE.match(window[3]) and window[1] == plain_struct(window[3])):
            kept.append(window[3])
            index += 5
            continue
        kept.append(lines[index])
        index += 1
    return kept


def strip_generated(lines):
    kept = []
    index = 0
    while index < len(lines):
        if lines[index].strip() == "/**":
            end = index + 1
            while end < len(lines) and lines[end].strip() != "*/" and lines[end].strip().startswith("*"):
                end += 1
            if end < len(lines) and lines[end].strip() == "*/":
                index = end + 1
                continue
        kept.append(lines[index])
        index += 1
    return unwrap_interfaces(kept)


def indentation(line):
    return line[:len(line) - len(line.lstrip())]


def code_only(line):
    return re.sub(r"//.*", "", line)


def statement_start(lines, index):
    while index > 0:
        previous = code_only(lines[index - 1]).strip()
        if not previous or previous.endswith((";", "{", "}", "*/", "\\")) or previous.startswith("#"):
            break
        index -= 1
    return index


def find_page(pages, name):
    for candidate in (name, name[:-1] if name.endswith(("A", "W")) else None):
        if candidate and candidate.lower() in pages:
            return pages[candidate.lower()]
    return None


def annotate(lines, pages, used):
    insertions = {}
    depth = 0
    interface = None
    interface_depth = 0
    in_block_comment = False
    struct_starts = []
    extern_blocks = 0
    wrapped = set()
    interface_index = None

    def add(index, block, title):
        if block and index not in insertions:
            insertions[index] = block
            used.add(title)
            return True
        return False

    for index, line in enumerate(lines):
        if index and lines[index - 1].rstrip().endswith("\\"):
            continue
        code = code_only(line)
        if in_block_comment:
            if "*/" in code:
                in_block_comment = False
                code = code.split("*/", 1)[1]
            else:
                continue
        code = re.sub(r"/\*.*?\*/", "", code)
        if "/*" in code:
            in_block_comment = True
            code = code.split("/*", 1)[0]
        stripped = code.strip()

        match = re.match(r"\s*DECLARE_INTERFACE_?\s*\(\s*(\w+)", code)
        if match and not stripped.endswith(";"):
            interface = match.group(1)
            interface_depth = depth
            interface_index = index
            page = find_page(pages, interface)
            if page and add(index, comment(indentation(line), page, include_parameters=False), page["title"]):
                wrapped.add(index)
        elif interface:
            method = re.match(r"\s*STDMETHOD_?\s*\(\s*(?:[^,()]+,\s*)?(\w+)\s*\)", code)
            if method:
                for owner in (interface, interface[:-1] if interface.endswith(("A", "W")) else None):
                    page = pages.get(f"{owner}::{method.group(1)}".lower()) if owner else None
                    if page:
                        if add(index, comment(indentation(line), page), page["title"]):
                            wrapped.add(interface_index)
                        break

        define = re.match(r"\s*#\s*define\s+(\w+)", line)
        if define and not interface:
            page = pages.get(define.group(1).lower())
            if page and not page["members"]:
                add(index, comment(indentation(line), page), page["title"])

        if re.match(r"\s*typedef\s+(struct|union|enum)\b[^;]*$", code):
            struct_starts.append((index, depth))

        if depth == 0 and not interface and not stripped.startswith(("#", "typedef")) and "(" in stripped:
            call = re.search(r"\b(\w+)\s*\(", stripped)
            ends = stripped.endswith(";") or (index + 1 < len(lines) and not code_only(lines[index + 1]).strip().startswith("{"))
            if call and ends:
                for name in re.findall(r"\b(\w+)\s*\(", stripped):
                    page = find_page(pages, name)
                    if page and "::" not in page["title"] and not page["members"]:
                        start = statement_start(lines, index)
                        add(start, comment(indentation(lines[start]), page), page["title"])
                        break

        if re.match(r'\s*extern\s+"C"\s*\{', code):
            extern_blocks += 1
            code = code.replace("{", "", 1)
        elif stripped == "}" and depth == 0 and extern_blocks:
            extern_blocks -= 1
            code = ""
        if not stripped.startswith("#"):
            depth += code.count("{") - code.count("}")
        if interface and depth <= interface_depth and "}" in code:
            interface = None

        closing = re.match(r"\s*}\s*(\w+)", code)
        if closing and struct_starts:
            start, start_depth = struct_starts[-1]
            if depth == start_depth:
                struct_starts.pop()
                for name in re.findall(r"\w+", code.split("}", 1)[1].split(";")[0]):
                    page = find_page(pages, name)
                    if page and page["members"]:
                        add(start, comment(indentation(lines[start]), page), page["title"])
                        for member, description in page["members"]:
                            for member_index in range(start + 1, index):
                                member_code = code_only(lines[member_index])
                                if re.search(rf"\b{re.escape(member)}\s*((\[[^\]]*\])?\s*(:\s*\d+\s*)?;|=|,|$)", member_code):
                                    add(member_index, member_comment(indentation(lines[member_index]), description), page["title"])
                                    break
                        break
    output = []
    for index, line in enumerate(lines):
        if index in wrapped and INTERFACE.match(line):
            output += [CPLUSPLUS_ONLY] + insertions.get(index, []) + [plain_struct(line), "#else", line, "#endif"]
            continue
        output += insertions.get(index, [])
        output.append(line)
    return output, len(insertions)


def main():
    parser = argparse.ArgumentParser(description="Add the Auto PC SDK's help to its headers as documentation comments")
    parser.add_argument("help", nargs="+", help=".chm files, or folders of their unpacked pages")
    parser.add_argument("--headers", required=True, action="append", help="a folder of headers to annotate; can be given more than once")
    parser.add_argument("--unused", action="store_true", help="list the API pages no declaration matched")
    arguments = parser.parse_args()

    with tempfile.TemporaryDirectory() as scratch:
        pages = load_pages(unpack(arguments.help, scratch))
    used = set()
    total = 0
    paths = sorted(os.path.join(folder, name) for folder in arguments.headers for name in os.listdir(folder) if name.lower().endswith(".h"))
    for path in paths:
        data = open(path, "rb").read()
        newline = "\r\n" if b"\r\n" in data else "\n"
        text = data.decode("latin-1")
        lines = text.split(newline)
        trailing = lines[-1] == ""
        if trailing:
            lines.pop()
        lines = strip_generated(lines)
        output, count = annotate(lines, pages, used)
        result = newline.join(output) + (newline if trailing else "")
        if result.encode("latin-1") != data:
            open(path, "wb").write(result.encode("latin-1"))
        total += count
    api = {page["title"] for page in pages.values() if page["parameters"] or page["members"] or page["returns"] or "::" in page["title"]}
    print(f"{total} comments from {len(used)} pages, {len(used & api)} of the {len(api)} API pages")
    if arguments.unused:
        for title in sorted(set(api) - used):
            print("unused", title)


if __name__ == "__main__":
    main()
