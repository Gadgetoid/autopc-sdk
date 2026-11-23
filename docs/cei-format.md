# The .cei package format

Auto PC software installs from a `.cei` package, which `ApcLoad.exe` (the "Auto PC Load" program) reads. Microsoft's CEIBuild wrote them. This describes the format as both read it, and `tools/ceitree.py` implements it.

Sources:
- **Installers:** the Joyride's `ApcLoad.exe` (x86) and the Clarion AutoPC 310C's (SH3), from their ROMs. Addresses below are Joyride 2.02.9386.328.
- **CEIBuild:** 1.0 (March 1999, Auto PC SDK 8498) and 2.0 (July 1999, "Auto PC Install Package Maker"), and their readme. CEIBuild and ApcLoad share one data model (`apps\setup\datamodl\model.cpp`).
- **Packages:** NavTech (format 6), the SDK's Bandit sample, MusicPlayer, and CEIBuild 1.0 and 2.0 output. `ceiunpack.py` followed by `ceipack.py` reproduces every one byte for byte.

## Layout

A package is NUL-terminated ASCII records (Windows-1252), starting with the header record. A file entry's data follows its info record directly, with no terminator. A list of entries ends with an end marker: a record that starts with two NULs (`\0\0`). The top-level list runs to the end of the file.

The installer reads at most 522 bytes per record. A longer record is only valid for a binary or multi-string registry value, which it reads in pieces split at commas.

## Text

Names and other text are escaped:

| Character | Escape |
|---|---|
| Space | `\|B` |
| Tab | `\|T` |
| Line feed | `\|N` |
| Form feed | `\|F` |
| Carriage return | `\|R` |
| (empty string) | `\|Z` |

`-` in a file info record means no string. `|` itself has no escape, so it can't appear in text, and an escaped string must be under 260 characters (CEIBuild refuses longer).

## Header

`%s %s %i %i %i %i %i %i %i %i %s %s %lx %i %i %i %i` (both programs use this string):

| Field | Meaning | Joyride (CEIBuild 2.0) | 310C (MusicPlayer) |
|---|---|---|---|
| 1 | Package name, the install and upgrade identity, shown in Remove Programs | `hello` | `MusicPlayer` |
| 2 | Title | `\|Z` | `\|Z` |
| 3 | Format | 8 | 7 |
| 4 | "Already installed" option (start an application, or uninstall) | 1 | 1 |
| 5 | Boot option (normal, or force a restart) | 1 | 1 |
| 6, 7 | Package version, major and minor | 1 0 | 1 0 |
| 8, 9 | Minimum ROM version | 2 0 | 1 0 |
| 10 | Processor (PE machine) | 332 | 418 |
| 11 | Platform | `All` | `All` |
| 12 | Language | `All` | `All` |
| 13 | Certificate length, hex | 0 | 0 |
| 14, 15 | Unused by ApcLoad, carried into the uninstall copy | 131072 13050851 | 131072 13050830 |
| 16, 17 | Maximum ROM version, 0 0 for none | 0 0 | absent |

CEIBuild 1.0 writes only the first seven fields.

What each installer accepts:

- **310C:** reads the first seven fields only (`%s %s %i %i %i %i %i`, `0x16C00`), and accepts format 6 or 7 (`0x16C2C`). It ignores the processor and the checksums.
- **Joyride** (`0x1844B`):
  - **Formats:** 6, 7 and 8.
  - **ROM version:** its own must be within fields 8-9 and 16-17.
  - **Seven-field headers:** the minimum ROM version becomes 2.0 and the processor 332 (`0x1859E`).
  - **Processor:** must be 332 or 0 (`0x18488`). For format 7 or older any nonzero processor is refused with error 0x11, "compiled for a different platform" (`0x185BB`). So a seven-field header, or MusicPlayer's 418, is refused.
  - **Language:** must be `All` or match the unit's (`0x18508`).

So format 8 with processor 332 installs only on the Joyride, and format 7 with 418 only on the 310C. Format 7 with processor 0 would install on both.

A nonzero certificate length means a certificate block follows the header. Packages built here have none, so the installer warns that the software isn't certified and installs it anyway.

## Entries

An entry starts with `%i %s %u %u %u`: type, name, and depending on the format:

| Header | Numbers after the name |
|---|---|
| Seven fields | none |
| Format 7 | two checksums |
| Format 8 | two checksums, then the dynamic-data flag |

| Type | Entry | Records after the name | Children |
|---|---|---|---|
| 1 | Folder | file info | yes |
| 2 | File | file info, then the data | no |
| 3 | Speech Training | none | yes |
| 4 | Databases | none | yes |
| 5 | Database reference | `%i %i %u %u %u %u` | no |
| 6 | Registry key | none | yes |
| 7 | Registry value | `%i %i` (type, flags), then the value | no |
| 8 | Phrases or Templates group | none | yes |
| 9 | Speech template | `%u` | yes, its `.six` file |
| 10 | (read as a leaf, not seen in packages) | none | no |

The container types are from the tree loader at `0x16DA3`.

### File info

`%hu %hu` followed by thirty `%i`, then `%s %s %u`:

| Fields | Meaning |
|---|---|
| 1, 2 | Version, major and minor. For a PE file, its image version. |
| 3-10, 11-18, 19-26 | Three SYSTEMTIMEs: year, month, day of week, day, hour, minute, second, millisecond. Creation, last access and last write. |
| 27 | Unused by the Joyride's installer, 0 |
| 28 | Shortcut: creates `\Windows\Shell Applications\<shortcut name>.lnk` (`0x15AAB`) |
| 29 | Replace: 0 if newer, 1 always, 2 never |
| 30 | Read at install (`0x15DD5`), purpose unknown; 0 in every package |
| 31 | Self-registering: with field 32 set, runs the EXE with `/REGSERVER` or calls the DLL's `DllRegisterServer` (`0x159ED`) |
| 32 | 1 on every program in the corpus; the installer sets it when field 31 is set |
| 33 | Shortcut name, or `-` |
| 34 | Source path on the build machine, or `-`. The installer doesn't use it. |
| 35 | Data length |

Folders have all zeros and `- - 0`. The setup DLL folders carry their DLL's name in field 33.

A shortcut needs the program to have icon resource 1 (32x32, 16 colours and monochrome) and string resource 1, its name in the shell.

### Registry values

| Type | Value record |
|---|---|
| 1, string | The escaped text |
| 4, DWORD | Decimal |
| 3, binary | Comma-separated hex bytes |
| 7, multi-string | Comma-separated hex bytes of the UTF-16 data |

The flag is 0 to always set the value, nonzero to leave an existing one (`0x15CB3`).

### Database references

The six numbers are, in order:
- **Create:** 1 to create the database on install, 0 for uninstall only.
- **Create always:** delete and recreate it if it exists.
- **Search keys:** four values for `CeCreateDatabase`.

## Checksums

The Joyride checks entries of types 1, 2, 5, 7 and 9 unless both checksums are 0 (`0x16CD9`). A mismatch is error 8, "The installation file is corrupted". The 310C ignores them.

Each checksum is XORed with `0x5F9A63CB` (CEIBuild's model constructor, `0x1033156`):
- **First number:** the count of bytes summed.
- **Second number:** their unsigned sum.

What's summed (`0x16A28`):

| Type | Bytes |
|---|---|
| 1, 2 | The two version words; the three SYSTEMTIMEs; fields 27-32 as dwords; the two strings; the length as a dword. For a file, also the data. |
| 5 | The six numbers as dwords |
| 7 | Type and flags as dwords, then: a DWORD's four bytes; a string's first `wcslen` bytes in UTF-16 (half its characters); a binary or multi-string value's bytes |
| 9 | Its number as a dword |

Strings are summed after unescaping, as UTF-16, and only their first `wcslen` bytes. `-` is summed as itself.

## Dynamic data

CEIBuild's "App will save dynamic data in this directory" (or registry key, or database) marks entries whose contents should be kept across an OS update. Format 8 records it as the third number. Every format also lists them in the `.CEU`.

## The .CEU migration manifest

CEIBuild adds `\Windows\Migrate\<package>.CEU`:

```
TargetInformation 67 Platform All MinROMVersion    2    0 Language All MachineType  332 WCE|BDevice|BFiles 23 Program|BFiles\Browser 
```

- **Sections:** each is a name and the length of the rest of the section, including its trailing space.
- **TargetInformation:** `Platform %s MinROMVersion %4u %4u Language %s MachineType %4u `.
- **Dynamic data:** then one section per dynamic entry: `WCE Device Files`, `Registry` or `Databases`, and the escaped path under that root.

## The tree

CEIBuild starts every package with this tree, and the installer expects it:

```
Custom Setup DLLs
  Uninstall DLL
  Install DLL
Databases
Speech Training
  Phrases
  Templates
Registry
  HKEY_CURRENT_USER
  HKEY_CLASSES_ROOT
  HKEY_LOCAL_MACHINE
WCE Device Files
  Program Files
  Windows
    Migrate
  Temp
  My Documents
```

CEIBuild's child order depends on how a package was edited; the installer doesn't care. A program appears in the shell's menu if the package creates `HKEY_LOCAL_MACHINE\SOFTWARE\FMAppConfiguration\<name>` with `AppName` `<name>` and `Order`, where `<name>` is its shortcut name.

## Not covered

- **Certificates:** blocks after the header, used for ROM replacement components.
- **Setup DLLs:** how the DLL file itself is stored under `Custom Setup DLLs`.
- **Phrases:** the format of entries under `Phrases`.
- **Header fields 14 and 15:** where CEIBuild gets their values. The installer ignores them.
