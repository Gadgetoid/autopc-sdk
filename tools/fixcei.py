r"""Clear the checksums in an existing AutoPC .cei so the Joyride installs it.

    python3 fixcei.py browser.cei fixed.cei --machine x86

Packages from Microsoft's SDK packager, or built from a template, carry
folder, file and registry value checksums that don't match their entries,
which the Joyride's installer refuses ("The installation file is corrupted").
Everything else is copied unchanged, then the result is checked with
checkcei.py."""
import argparse
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import cei
import checkcei


def main():
    parser = argparse.ArgumentParser(description="Clear the checksums in an AutoPC .cei")
    parser.add_argument("package")
    parser.add_argument("output")
    parser.add_argument("--machine", choices=sorted(checkcei.MACHINES), required=True, help="processor of the device it's for")
    arguments = parser.parse_args()

    header, items = cei.parse(open(arguments.package, "rb").read())
    cleared = cei.clear_checksums(items)
    package = cei.build(header, cleared)
    problems = checkcei.problems(package, arguments.machine)
    if problems:
        raise SystemExit("\n".join("fixcei: %s" % problem for problem in problems))
    open(arguments.output, "wb").write(package)
    changed = sum(1 for before, after in zip(items, cleared) if before != after)
    print(f"wrote {arguments.output}: cleared {changed} entries")


main()
