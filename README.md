# AutoPC SDK

An open homebrew toolchain for the Clarion AutoPC 310C (Microsoft Auto PC,
Windows CE 2.0, Hitachi SH3). Built on [velo-toolchain]. Edit a demo, push, and
CI builds a real SH3 `.exe` for the device - no Microsoft tools, no Wine.

## What's here
- `include/autopc.h`, `src/autopc.c` - a small helper that binds to the device's
  own `coredll` at runtime, so it reaches APIs velo-toolchain doesn't expose
  (notably the faceplate display, drawn through the `FACEPLT` GDI driver).
- `examples/hello` - the safe proof of concept: draws a message to the faceplate
  and exits. It only writes to the screen; it reads and changes nothing.
- `examples/stonks` - a second screen-only demo.
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

## Running on a device (safe)
The demos only draw to the faceplate. Two ways to run one:
1. `splice.py` it into a `BurnOS.bin` and load that the way the official
   firmware update did (CF autorun or parallel-port PPFS). Proven in emulation.
2. (coming) package it as a `.cei` the AutoPC shell installs from a card.

[velo-toolchain]: https://github.com/gadgetoid/velo-toolchain
