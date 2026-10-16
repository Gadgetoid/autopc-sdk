# AutoPC SDK

An open homebrew toolchain for the Clarion AutoPC 310C (Microsoft Auto PC,
Windows CE 2.0, Hitachi SH3). Built on [velo-toolchain]. Edit a demo, push, and
CI builds a real SH3 `.exe` for the device - no Microsoft tools, no Wine.

## What's here
- `include/autopc_app.h`, `src/autopc_app.c` - the app itself: a Forms Manager
  form that makes the program the foreground app, delivers the faceplate keys
  (Esc quits) and gives it a device context to draw into. See
  [docs/apps.md](docs/apps.md).
- `include/autopc.h`, `src/autopc.c` - drawing helpers for that device context
  and storage card files, bound from the device's own `coredll` at runtime so
  they reach APIs velo-toolchain doesn't expose.
- `examples/hello` - the safe proof of concept: shows a message on the faceplate
  until Esc. It only writes to the screen; it reads and changes nothing.
- `examples/stonks` - a second screen-only demo.
- `examples/visualiser` - a 32-bar spectrum analyser with peaks for the CD Player:
  start a CD, leave the player (it keeps playing), open Visualiser. It reads
  the CD audio ring in the faceplate's memory; Esc exits. See
  [docs/apps.md](docs/apps.md#cd-audio).
- `sdk/` - Microsoft's Auto PC SDK headers, and `autopc_add_sdk_executable` in
  `CMakeLists.txt` to build programs against them as the SDK's samples were. See
  [sdk/README.md](sdk/README.md).
- `tools/splice.py` - wrap a built `.exe` into a `BurnOS.bin` to run it (below).

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

## Running on a device
The demos only draw to the faceplate - they read and change nothing.

**Native install (the goal, how AutoPC homebrew shipped in 2000).** Put two
files on the root of a CompactFlash card: `AUTORUN.INF` and `<app>.cei`. Insert
the card; the AutoPC shell auto-runs the installer. `AUTORUN.INF` is:

```
[AutoPC.shx]
Title=My App Install
Item1=My App 1.0
Open1=myapp.cei
```

A `.cei` is a custom AutoPC installer package (not a cab): a header line, then
NUL-separated ASCII records describing a folder/file tree with install hooks,
then the files embedded as size-framed blobs. `tools/cei.py` parses and rebuilds
a `.cei` byte-for-byte; `tools/mkcei.py` swaps your program into a template
`.cei`. With `musicplayer.cei` as the template this is tested on a real unit:

```sh
python3 tools/mkcei.py musicplayer.cei build/hello.exe hello.cei \
  --minimal --name hello.exe --package Hello --menu Hello
```

`--menu` adds the program to the shell's app menu. The installer asks you to
voice-train the program's name, its shell voice command (Esc skips it), then
restarts the AutoPC. A program needs icon resource 1 and string resource 1 (its shell name)
for its shortcut: see `assets/autopc.ico` and `examples/hello/hello.rc`.

**Alternative (RAM-only).** `splice.py` wraps a built `.exe` into a
`BurnOS.bin`; load that the way the official firmware update did (CF autorun via
`osupnobr.exe`, or parallel-port PPFS). It runs from RAM and touches nothing on
the device. Verified end to end in an SH3 Windows CE emulator. The update
image has no Forms Manager, so `autopc_app_start` fails there; this suits
programs that don't need the Forms Manager, such as the dumpers.

[velo-toolchain]: https://github.com/gadgetoid/velo-toolchain
