# Auto PC SDK headers

`include/` is the `Emulation_Include_Files` folder of Microsoft's Auto PC SDK, build 8498 RC2, from the Windows CE DevCon 99 conference CD, with documentation comments from the SDK's help added by `tools/sdkhelp.py`. It holds the Auto PC headers (`asfc.h`, `ascmnctl.h`, `apcaudio.h`, `speech.h`, ...) and the Windows CE 2.0 COM and Win32 headers they need. The `inc` folder of the SDK's samples (`AutoPC1_0_SDK_Samples`) differs only in whitespace.

`compat/stdarg.h` replaces the SDK's `stdarg.h`, which assumes the Microsoft SH compiler's stack layout, with clang's builtins.

`autopc_add_sdk_executable` in `CMakeLists.txt` builds a program against these headers as the SDK's samples were built: C++ with clang's Microsoft extensions, `_MSC_VER=1200`, `UNDER_CE=200` and `UNICODE`, the SDK's GUIDs from `src/sdk_guids.cpp` (in place of `asfcguid.lib` and `uuid.lib`) and import libraries for `asfc.dll`, `apcdll.dll` and the extra `coredll.dll` exports listed in `exports/`.

## Documentation comments

`tools/sdkhelp.py` reads the SDK's compiled help (`Online_help_files/wceapc.chm` on the same CD) and writes each page's summary, parameters, return values and remarks as a `/** */` block above the declaration it describes. Running it again replaces the blocks it wrote:

```sh
python3 tools/sdkhelp.py Online_help_files/wceapc.chm --headers sdk/include --unused
```

It needs `7zz` or `7z` to unpack `.chm` files. `autopc_add_sdk_executable` passes `-fretain-comments-from-system-headers`, so clangd shows the comments on interfaces, functions, structures, their members and messages. clang doesn't attach comments to methods declared with `STDMETHOD` inside `DECLARE_INTERFACE_`, as the class name comes from a macro argument, so method comments are only in the headers.

