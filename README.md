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
- `examples/ctprobe` - Joyride only: lists the PCI devices and dumps the Chips
  & Technologies display controller's registers to `CTPROBE.TXT` on the card.
- `examples/bigscreen` - Joyride only: drives the large screen from the
  faceplate firmware (NK). It needs the large screen firmware's `ddi_ct.dll`,
  rebuilt with relocations, on the card, and logs to `BIGSCRN.TXT`.
- `examples/bigvis` - Joyride only: plays `MUSIC.WAV` from the card and draws a
  spectrum, scope and fire effect on the large screen. It needs `ddi_ct.dll` as
  `bigscreen` does.
- `examples/msgtest` - Joyride only: puts a test message in each of the
  Messages app's Inbox, News and Traffic folders through `msgstore.dll`.
- `examples/changerplay` - Joyride only: switches the USB CD changer to data
  mode, loads disc 5 and plays the first MP3 on it, or the first on the card if
  there's no changer. See [docs/apps.md](docs/apps.md#cd-changer-data-discs).
  It decodes with RealNetworks' Helix MP3 decoder
  (`third_party/libhelix-mp3-...`, under its RPSL/RCSL licences) through
  `src/mp3_stream.c`.
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

The build also packages programs for a card: `card/<name>/AUTORUN.INF` and
`card/<name>/<name>.cei`, ready to copy to the root of a CompactFlash card, for
the 310C from an SH3 build and for the Joyride from an x86 one.
`autopc_add_package(target "Shell Name")` in `CMakeLists.txt` packages another
program. `python3 -m unittest discover -s tests` tests the package tools.

## Installing on a device
Put two files on the root of a CompactFlash card: `AUTORUN.INF` and
`<app>.cei`. Insert the card while the unit is on; the AutoPC shell runs the
installer. `AUTORUN.INF` is:

```
[AutoPC.shx]
Title=My App Install
Item1=My App 1.0
Open1=myapp.cei
```

The section names the processor: `[AutoPC.shx]` for the 310C, `[AutoPC.X86]`
for the Joyride, which skips sections for other processors.

## Packages
A `.cei` is the Auto PC's installer package, which Microsoft's CEIBuild made.
[docs/cei-format.md](docs/cei-format.md) describes the format, from the
310C's and Joyride's installers and both CEIBuild versions. `tools/ceipack.py`
builds one from a TOML manifest, the way CEIBuild would:

```toml
[package]
name = "Hello"
version = "1.0"
target = "joyride"        # or "310c"

[[file]]
source = "hello.exe"      # installed in \Program Files\Hello
shortcut = "Hello"

[menu]
name = "Hello"
```

```sh
python3 tools/ceipack.py hello.toml hello.cei
```

The manifest can also add data files, folders, registry values, speech
templates and database references; see the top of `tools/ceipack.py`. A
`joyride` package is format 8 for x86, a `310c` one format 7 for SH3, and
neither installs on the other unit. `ceipack` checks the result with
`tools/checkcei.py`, which checks any `.cei` against what a unit's installer
accepts:

```sh
python3 tools/checkcei.py hello.cei --machine x86
```

`tools/ceiunpack.py package.cei folder` unpacks a package into a manifest and
its files, which `ceipack` rebuilds byte for byte.

Packages have no certificate, so the installer says the program isn't
certified and installs it anyway. A program in the menu needs icon resource 1
and string resource 1 (its shell name) for its shortcut: see
`assets/autopc.ico` and `examples/hello/hello.rc`. The installer asks you to
voice-train the name, its shell voice command (Esc or Back skips it), then
restarts the unit.

`tools/mkcei.py` is the older route: it swaps a program into a template `.cei`
such as MusicPlayer's.

[velo-toolchain]: https://github.com/gadgetoid/velo-toolchain
