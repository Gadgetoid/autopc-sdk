/* Connect to a desktop computer over a Socket serial PC Card: enable direct
   connections, make sure the connection named in ControlPanel\Comm exists as a
   direct cable on the card, run repllog.exe to dial it, and show whether it is
   still running until Esc. */
#include <ras.h>
#include <string.h>

#include "autopc.h"
#include "autopc_app.h"

#define CONNECTION_DEVICE L"Socket I/O Serial"
#define MAX_CONNECTIONS   16

static void connection_settings(WCHAR *name, DWORD size) {
    HKEY key;
    wcscpy(name, L"`Serial Port @ 19200`");
    if (RegOpenKeyExW(HKEY_CURRENT_USER, L"ControlPanel\\Comm", 0, 0, &key) != ERROR_SUCCESS) return;
    DWORD type, bytes = size * sizeof(WCHAR), automatic = 1;
    RegQueryValueExW(key, L"Cnct", NULL, &type, (BYTE *)name, &bytes);
    RegSetValueExW(key, L"AutoCnct", 0, REG_DWORD, (const BYTE *)&automatic, sizeof automatic);
    RegCloseKey(key);
}

static BOOL connection_exists(const WCHAR *name) {
    RASENTRYNAME entries[MAX_CONNECTIONS];
    DWORD bytes = sizeof entries, count = 0;
    entries[0].dwSize = sizeof entries[0];
    if (RasEnumEntries(NULL, NULL, entries, &bytes, &count) != 0) return FALSE;
    for (DWORD i = 0; i < count; i++) {
        if (!wcscmp(entries[i].szEntryName, name)) return TRUE;
    }
    return FALSE;
}

static BOOL create_connection(const WCHAR *name) {
    RASENTRY entry;
    memset(&entry, 0, sizeof entry);
    entry.dwSize = sizeof entry;
    entry.dwfNetProtocols = RASNP_Ip;
    entry.dwFramingProtocol = RASFP_Ppp;
    wcscpy(entry.szDeviceType, RASDT_Direct);
    wcscpy(entry.szDeviceName, CONNECTION_DEVICE);
    return RasSetEntryProperties(NULL, (WCHAR *)name, &entry, sizeof entry, NULL, 0) == 0;
}

static BOOL start_repllog(PROCESS_INFORMATION *repllog) {
    WCHAR name[RAS_MaxEntryName + 1];
    connection_settings(name, RAS_MaxEntryName + 1);
    if (!connection_exists(name) && !create_connection(name)) return FALSE;
    return CreateProcessW(L"repllog.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, NULL, repllog);
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previous, LPWSTR command_line, int show) {
    if (!autopc_app_start(instance, 0, 0)) return 1;
    autopc_init();
    PROCESS_INFORMATION repllog;
    BOOL started = start_repllog(&repllog);
    while (autopc_app_running()) {
        BOOL connecting = started && WaitForSingleObject(repllog.hProcess, 0) == WAIT_TIMEOUT;
        HDC dc = autopc_app_begin_draw();
        autopc_clear(dc);
        autopc_print(dc, !started ? L"PC Link could not start" : connecting ? L"PC Link connecting" : L"PC Link finished");
        autopc_app_end_draw(dc);
        Sleep(200);
    }
    if (started) {
        CloseHandle(repllog.hThread);
        CloseHandle(repllog.hProcess);
    }
    autopc_app_stop();
    return 0;
}
