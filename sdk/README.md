# Auto PC SDK headers

`include/` is the `Emulation_Include_Files` folder of Microsoft's Auto PC SDK, build 8498 RC2, from the Windows CE DevCon 99 conference CD, unchanged. It holds the Auto PC headers (`asfc.h`, `ascmnctl.h`, `apcaudio.h`, `speech.h`, ...) and the Windows CE 2.0 COM and Win32 headers they need. The `inc` folder of the SDK's samples (`AutoPC1_0_SDK_Samples`) differs only in whitespace.

`compat/stdarg.h` replaces the SDK's `stdarg.h`, which assumes the Microsoft SH compiler's stack layout, with clang's builtins.

`autopc_add_sdk_executable` in `CMakeLists.txt` builds a program against these headers as the SDK's samples were built: C++ with clang's Microsoft extensions, `_MSC_VER=1200`, `UNDER_CE=200` and `UNICODE`, the SDK's GUIDs from `src/sdk_guids.cpp` (in place of `asfcguid.lib` and `uuid.lib`) and import libraries for `asfc.dll`, `apcdll.dll` and the extra `coredll.dll` exports listed in `exports/`.
