# Writing AutoPC apps

Findings from the Auto PC SDK (DevCon 99, build 8498 RC2) and from the Clarion 310C's resident OS (Auto PC 1.00.8348).

## Staying alive: register with the Forms Manager

The shell (`apcshell.exe`) keeps a list of programs it launches. Once 15 seconds, plus 5 seconds per program on the list, have passed, it calls `TerminateProcess` on any still running that the Forms Manager does not know about. On the device this shows as "Please wait" and then a return to the menu.

A program stays off that list by registering with the Forms Manager, as the SDK samples do:

```c
#include "autopc_app.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previous, LPWSTR command_line, int show) {
    BOOL registered = autopc_register_app(instance);
    if (!registered && autopc_detach(instance, command_line)) return 0;
    /* ... */
    autopc_unregister_app();
    return 0;
}
```

`autopc_register_app` registers under the program's string resource 1, the same name as its shell shortcut. It initialises COM, calls `InitASFormsManager`, creates `IfmManage` and calls `RegisterStartedApplication(FC_MAINFACEPLATE, name)` and `MoveAppToForeground`. `autopc_unregister_app` undoes it; call it before exiting.

`autopc_detach` is the fallback where there is no Forms Manager (`asfc.dll`), as under the BurnOS update image: it relaunches the program with `/child` and returns TRUE, so the first instance exits and the second is not on the shell's list.

| | Value (from `asfc.h`) |
|---|---|
| `CLSID_FMMANAGE` | `{196F4760-5F84-11D1-9B27-0000F8757D96}` |
| `IID_FMMANAGE` | `{1FB926E1-A17C-11D0-88E0-0000F80401D1}` |
| `FC_MAINFACEPLATE` | `0xFFFFFFFD` |
| `IfmManage` slots | 7 `Start`, 12 `MoveAppToForeground`, 15 `RegisterStartedApplication`, 16 `DeregisterStartedApplication` |

A full Auto PC app also creates a form (`CLSID_ASFORM` `{37C23051-997F-11D0-88DC-0000F80401D1}`, `IID_ASFORM` `{6D318C43-9343-11D0-B512-00A024A652FA}`), calls `IfmManage::Start` on it and makes it visible, with an `IASEventSink` for `WM_COMMAND`. See the SDK's `Win32_Samples/win32/hello/hello.cpp`.

## Appearing in the shell menu

Built-in apps have `HKLM\SOFTWARE\FMAppConfiguration\<name>` with `AppName` (string) and `Order` (DWORD), optionally `LaunchPhrase` and `AutoLaunch`, plus a shortcut in `\Windows\Shell Applications\`. A `.cei` without the registry key installs but only shows in the uninstaller.

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
