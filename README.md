# AutoPC SDK

An open homebrew toolchain for the Clarion AutoPC 310C (Microsoft Auto PC,
Windows CE 2.0, Hitachi SH3) and the Clarion Joyride (Auto PC 2.0, Windows CE
2.12, x86). Built on [velo-toolchain]. Edit a demo, push, and CI builds real
SH3 and x86 `.exe`s for the devices.

## What's here
- `include/autopc_app.h`, `src/autopc_app.c` - the app itself: a Forms Manager
  form that makes the program the foreground app, delivers the faceplate keys
  (Esc quits) and gives it a device context to draw into. See
  [docs/apps.md](docs/apps.md).
- `include/autopc.h`, `src/autopc.c` - drawing helpers for that device context
  and storage card files, bound from the device's own `coredll` at runtime so
  they reach APIs velo-toolchain doesn't expose.
- `examples/hello` - shows a message on the faceplate until Esc.
- `examples/stonks` - a mock car-stereo readout on the faceplate until Esc.
- `examples/visualiser` - a 32-bar spectrum analyser with peaks for the CD Player:
  start a CD, leave the player (it keeps playing), open Visualiser. It reads
  the CD audio ring in the faceplate's memory; Esc exits. See
  [docs/apps.md](docs/apps.md#cd-audio).
- `examples/pclink` - connects to a desktop computer over a Socket serial PC
  Card: turns on direct connections, creates the `` `Serial Port @ 19200` ``
  connection on the card if it's missing, and runs `repllog.exe`, which Auto
  PC 1.0 never starts for a PC Card by itself. Esc leaves it connected.
- `sdk/` - Microsoft's Auto PC SDK headers, and `autopc_add_sdk_executable` in
  `CMakeLists.txt` to build programs against them as the SDK's samples were. See
  [sdk/README.md](sdk/README.md).

## Build
CI builds on every push (see `.github/workflows/build.yml`) and uploads the
`.exe`s as artifacts. Locally:

```sh
git submodule update --init --recursive
# one-time: fetch the SH3 LLVM for your OS from
#   https://github.com/Gadgetoid/velo-llvm-builds/releases
cmake -S . -B build \
  -DCMAKE_TOOLCHAIN_FILE=third_party/velo-toolchain/cmake/velo-ce.cmake \
  -DVELO_CE_VERSION=2 -DVELO_ARCH=sh3 -DVELO_LLVM_ROOT=/path/to/velo-llvm
cmake --build build
```

For the Joyride, build for x86 with any LLVM that has the X86 backend
(Homebrew's, Ubuntu's):

```sh
cmake -S . -B build-x86 \
  -DCMAKE_TOOLCHAIN_FILE=third_party/velo-toolchain/cmake/velo-ce.cmake \
  -DVELO_CE_VERSION=2 -DVELO_ARCH=x86
cmake --build build-x86
```

The Joyride's `asfc.dll` and `apcdll.dll` import lists are in `exports/x86`.

With `-DAUTOPC_CEI_TEMPLATE=/path/to/musicplayer.cei` the build also packages
`hello` and `stonks` for a card: `card/<name>/AUTORUN.INF` and
`card/<name>/<name>.cei`, ready to copy to the root of a CompactFlash card.
`autopc_add_package(target "Shell Name")` in `CMakeLists.txt` packages another
program. `python3 -m unittest discover -s tests` tests the package tools.

## Installing on a device
Put two files on the root of a CompactFlash card: `AUTORUN.INF` and
`<app>.cei`. Insert the card; the AutoPC shell auto-runs the installer.
`AUTORUN.INF` is:

```
[AutoPC.shx]
Title=My App Install
Item1=My App 1.0
Open1=myapp.cei
```

The section names the processor: `[AutoPC.shx]` for the 310C, `[AutoPC.X86]`
for the Joyride, which skips sections for other processors.

A `.cei` is a custom AutoPC installer package: a header line, then
NUL-separated ASCII records describing a folder/file tree with install hooks,
then the files embedded as size-framed blobs. `tools/cei.py` parses and rebuilds
a `.cei` byte-for-byte; `tools/mkcei.py` swaps your program into a template
`.cei`. With `musicplayer.cei` as the template this is tested on a real unit:

```sh
python3 tools/mkcei.py musicplayer.cei build/hello.exe hello.cei \
  --minimal --name hello.exe --package Hello --menu Hello --machine sh3
```

For the Joyride, `--machine x86`. Its installer refuses what the 310C's
accepts: a processor other than 0 in this template's header ("compiled for a
different platform"), and checksums that don't match an entry's contents ("The
installation file is corrupted"). `--machine x86` writes 0, and `mkcei` writes
checksums of the new contents. With `--machine`, `mkcei` checks the package with
`tools/checkcei.py`, which also checks any `.cei`:

```sh
python3 tools/checkcei.py hello.cei --machine x86
```

Packages have no certificate, so the Joyride says the program isn't certified
and installs it anyway.

`--menu` adds the program to the shell's app menu. The installer asks you to
voice-train the program's name, its shell voice command (Esc skips it), then
restarts the AutoPC. A program needs icon resource 1 and string resource 1 (its shell name)
for its shortcut: see `assets/autopc.ico` and `examples/hello/hello.rc`.

[velo-toolchain]: https://github.com/gadgetoid/velo-toolchain
