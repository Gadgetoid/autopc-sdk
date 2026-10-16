# Writing AutoPC apps

Findings from the Auto PC SDK (DevCon 99, build 8498 RC2) and from the Clarion 310C's resident OS (Auto PC 1.00.8348).

## An app is a Forms Manager form

The shell (`apcshell.exe`) keeps a list of programs it launches and, once 15 seconds plus 5 seconds per program on the list have passed, ends any still running that the Forms Manager doesn't know about ("Please wait", then back to the menu). Registering with the Forms Manager without showing a form isn't enough either: the program is ended about 20 seconds later. An Auto PC program has to do what the SDK's `Win32_Samples/win32/hello` does: register, start a form and make it visible. Then it is the foreground app, other apps stop drawing, and the faceplate keys come to it.

`autopc_app` does this:

```c
#include "autopc.h"
#include "autopc_app.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previous, LPWSTR command_line, int show) {
    if (!autopc_app_start(instance, 0, 0)) return 1;
    autopc_init();
    while (autopc_app_running()) {
        HDC dc = autopc_app_begin_draw();
        autopc_print(dc, L"Hello from homebrew!");
        autopc_app_end_draw(dc);
        Sleep(200);
    }
    autopc_app_stop();
    return 0;
}
```

- `autopc_app_start(instance, on_key, context)` initialises COM and the Forms Manager, creates `IfmManage`, calls `RegisterStartedApplication(FC_MAINFACEPLATE, name)` with the program's string resource 1 (its shortcut name) and `MoveAppToForeground`, then creates a form (`CLSID_ASFORM`) with an event sink, starts it with `IfmManage::Start`, captions it and makes it visible.
- `autopc_app_running()` dispatches the thread's messages (the Forms Manager calls the event sink from them) and returns FALSE once the app should exit.
- Keys arrive at the event sink as `WM_REMOTE_KEYDOWN` (0xBD00) and `WM_REMOTE_KEYUP` (0xBD01) with the virtual key in wParam, and go to `on_key(context, key, down)`; return TRUE to take a key. Esc quits unless taken. `autopc_app_quit()` asks the app to exit.
- `autopc_app_begin_draw()` returns the form's device context from `IASForm::GetIFMDraw` and `IFMDraw::GetDC`; `autopc_app_end_draw(dc)` commits it to the faceplate. Don't open the `FACEPLT` display directly: the foreground app redraws over it.
- `autopc_app_stop()` deregisters, closes the form and uninitialises; call it before exiting.

| | Value (from `asfc.h`, `apcmsg.h`, `keypad.h`) |
|---|---|
| `CLSID_FMMANAGE` | `{196F4760-5F84-11D1-9B27-0000F8757D96}` |
| `IID_FMMANAGE` | `{1FB926E1-A17C-11D0-88E0-0000F80401D1}` |
| `CLSID_ASFORM` | `{37C23051-997F-11D0-88DC-0000F80401D1}` |
| `IID_ASFORM` | `{6D318C43-9343-11D0-B512-00A024A652FA}` |
| `IID_ASEVENTSINK` | `{6D318C42-9343-11D0-B512-00A024A652FA}` |
| `FC_MAINFACEPLATE` | `0xFFFFFFFD` |
| `WM_REMOTE_KEYDOWN`, `WM_REMOTE_KEYUP` | `0xBD00`, `0xBD01` |
| `IfmManage` slots | 7 `Start`, 12 `MoveAppToForeground`, 15 `RegisterStartedApplication`, 16 `DeregisterStartedApplication` |
| `IASForm` slots | 7 `Init`, 9 `Close`, 33 `put_Visible`, 63 `put_Caption`, 79 `GetIFMDraw` |
| `IFMDraw` slots | 7 `GetDC`, 8 `Commit`, 10 `ReleaseDC` |
| `IASEventSink` slots | 7 `ReceiveMsg` (return `S_FALSE` to pass a message on) |

The keypad driver can also send every key straight to one thread (`KPD1:` IOCTL 0x1001 with the thread ID; NULL clears it), as the OS updater and backup do, but then the shell gets no keys at all until it's released. An ordinary app shouldn't.

## Appearing in the shell menu

Built-in apps have `HKLM\SOFTWARE\FMAppConfiguration\<name>` with `AppName` (string) and `Order` (DWORD), optionally `LaunchPhrase` and `AutoLaunch`, plus a shortcut in `\Windows\Shell Applications\`. A `.cei` without the registry key installs but only shows in the uninstaller. `tools/mkcei.py --menu NAME` adds the key to the package's registry tree (type 6 records are keys, type 7 values, followed by the value type, `1 0` for a string or `4 0` for a DWORD, and the data), so the program is in the menu after the install's restart. A newly installed app appears first in the menu whatever its `Order`.

## Shortcut resources and voice training

The `.cei` file record that asks for a shell shortcut needs icon resource 1 (32x32, 16 colours and mono) and string resource 1 (the name): see `assets/autopc.ico` and `examples/hello/hello.rc`. The shortcut name is also a voice command; with no `.six` speech template for it, the installer asks the user to say it three times.

## Faceplate keys

`keypad.dll` maps the faceplate matrix (row, column) to virtual keys:

| Row | Columns 0-5 |
|---|---|
| 0 | Up, Down, Left, Right, Enter, 0x5B |
| 1 | Alt, `VK_OFF` (power), `VK_HELP`, 1, 2, 3 |
| 2 | 4, 5, 6, 7, 8, 9 |
| 3 | F1, 0, F2, F24, F5, Esc |
| 4 | F6, F7, F23, F17 |

Keys reach the shell through `APCDLL!SH_keybd_event`, or as messages `0xBD00` (down) and `0xBD01` (up) to a window registered with the keypad driver.

## Installing from a card or CD

Put `AUTORUN.INF` and the `.cei` in the root of a CompactFlash card or CD:

```
[AutoPC.shx]
Title=Visualiser Install
Item1=Visualiser 1.0
Open1=visualiser.cei
```

The installer asks whether to back up, copies the files, asks the user to say the shortcut name three times (Esc skips this, as it must in sh3-emu, which has no microphone), then restarts. An `AUTORUN.INF` item can also open an `.exe` directly, after a Security Warning, but nothing is installed and the shell's menu doesn't list it.

## Faceplate hardware from an app

`PCI.dll!GetPCIDevAddresses(vendor, device, count, windows, addresses)` maps windows of a PCI device into the calling process, as the drivers do. The faceplate is vendor `0x1398`, device `0x0003`. Each window is `{BAR config offset (0 for BAR0, 4 for BAR1), offset, size, type 0}`; the result is a virtual address per window. For BAR0 (I/O), byte, word and long accesses go to the address +0, +0x400 and +0x800. BAR1 is the faceplate's 64 KB memory.

## CD audio

When the CD Player plays, `atapipci.dll` reads each 2352-byte sector (44.1 kHz, 16-bit stereo, little-endian) into a three-sector ring in the faceplate's memory, and keeps playing when another program is in front (seen in sh3-emu, not yet on a unit). Faceplate register 0x2030 holds the ring's offset in the memory window and 0x2034 its length less 4 (both long reads of BAR0). `examples/visualiser` reads the ring this way, 256 samples at a time, for a fixed-point FFT, and draws through its form.
