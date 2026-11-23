#include "autopc.h"
#include "autopc_app.h"

#define DRIVER_NAME     L"ddi_ct.dll"
#define DRIVER_PATH     L"\\Windows\\ddi_ct.dll"
#define DRIVER_SOURCE   L"\\Storage Card\\ddi_ct.dll"
#define DISPLAY_KEY     L"Drivers\\Display\\Intel"
#define SCREEN_WIDTH    320
#define SCREEN_HEIGHT   234
#define SCREEN_BPP      8
#define SCREEN_HZ       60
#define PANEL_NUMBER    5
#define BAR_COUNT       8
#define FRAME_MS        200

static const char HEX[] = "0123456789ABCDEF";
static const COLORREF BARS[BAR_COUNT] = {
    RGB(255, 255, 255), RGB(255, 255, 0), RGB(0, 255, 255), RGB(0, 255, 0),
    RGB(255, 0, 255), RGB(255, 0, 0), RGB(0, 0, 255), RGB(0, 0, 0),
};
static HANDLE log_file = INVALID_HANDLE_VALUE;
static WCHAR summary[64] = L"Starting...";

static void put(const char *text) {
    DWORD length = 0, written;
    while (text[length]) length++;
    if (log_file != INVALID_HANDLE_VALUE) {
        WriteFile(log_file, text, length, &written, 0);
        FlushFileBuffers(log_file);
    }
}

static void put_hex(DWORD value) {
    char text[9];
    int i;
    for (i = 0; i < 8; i++) text[i] = HEX[(value >> (4 * (7 - i))) & 0xF];
    text[8] = 0;
    put(text);
}

static void put_value(const char *name, DWORD value) {
    put(name);
    put(" ");
    put_hex(value);
    put("\r\n");
}

static void set_summary(const WCHAR *text) {
    int i = 0;
    while (text[i] && i < 63) {
        summary[i] = text[i];
        i++;
    }
    summary[i] = 0;
}

static void set_dword(HKEY key, const WCHAR *name, DWORD value) {
    RegSetValueExW(key, name, 0, REG_DWORD, (const BYTE *)&value, sizeof(value));
}

static void write_display_settings(void) {
    HKEY key;
    DWORD disposition;
    LONG result = RegCreateKeyExW(HKEY_LOCAL_MACHINE, DISPLAY_KEY, 0, 0, 0, 0, 0, &key, &disposition);
    put_value("registry", (DWORD)result);
    if (result != ERROR_SUCCESS) return;
    set_dword(key, L"CxScreen", SCREEN_WIDTH);
    set_dword(key, L"CyScreen", SCREEN_HEIGHT);
    set_dword(key, L"Bpp", SCREEN_BPP);
    set_dword(key, L"Frequency", SCREEN_HZ);
    set_dword(key, L"PanelNumber", PANEL_NUMBER);
    set_dword(key, L"DisplayDevice", 0);
    RegCloseKey(key);
}

static BOOL install_driver(void) {
    if (CopyFileW(DRIVER_SOURCE, DRIVER_PATH, FALSE)) {
        put("driver copied from card\r\n");
        return TRUE;
    }
    put_value("driver copy failed", GetLastError());
    return GetFileAttributesW(DRIVER_PATH) != 0xFFFFFFFF;
}

static void draw_test_card(HDC dc, int width, int height) {
    RECT area;
    int bar;
    for (bar = 0; bar < BAR_COUNT; bar++) {
        HBRUSH brush = CreateSolidBrush(BARS[bar]);
        area.left = width * bar / BAR_COUNT;
        area.right = width * (bar + 1) / BAR_COUNT;
        area.top = 0;
        area.bottom = height;
        FillRect(dc, &area, brush);
        DeleteObject(brush);
    }
    area.left = 0;
    area.right = width;
    area.top = height / 2 - 16;
    area.bottom = height / 2 + 16;
    SetBkMode(dc, OPAQUE);
    SetTextColor(dc, RGB(0, 0, 0));
    DrawTextW(dc, L"Driven from NK", -1, &area, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

static HDC open_big_screen(void) {
    HDC dc;
    log_file = autopc_card_create(L"BIGSCRN.TXT");
    put("Joyride large screen from NK\r\n");
    write_display_settings();
    if (!install_driver()) {
        set_summary(L"No ddi_ct.dll");
        return 0;
    }
    dc = CreateDCW(DRIVER_NAME, 0, 0, 0);
    put_value("dc", (DWORD)dc);
    if (!dc) {
        put_value("error", GetLastError());
        set_summary(L"CreateDC failed");
        return 0;
    }
    put_value("width", (DWORD)GetDeviceCaps(dc, HORZRES));
    put_value("height", (DWORD)GetDeviceCaps(dc, VERTRES));
    put_value("bpp", (DWORD)GetDeviceCaps(dc, BITSPIXEL));
    draw_test_card(dc, GetDeviceCaps(dc, HORZRES), GetDeviceCaps(dc, VERTRES));
    put("drawn\r\n");
    set_summary(L"Large screen on");
    return dc;
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previous, LPWSTR command_line, int show) {
    HDC big_screen = 0;
    BOOL opened = FALSE;
    if (!autopc_app_start(instance, 0, 0)) return 1;
    autopc_init();
    while (autopc_app_running()) {
        HDC dc = autopc_app_begin_draw();
        autopc_print(dc, summary);
        autopc_app_end_draw(dc);
        if (!opened) {
            big_screen = open_big_screen();
            opened = TRUE;
        }
        Sleep(FRAME_MS);
    }
    if (big_screen) DeleteDC(big_screen);
    if (log_file != INVALID_HANDLE_VALUE) CloseHandle(log_file);
    autopc_app_stop();
    return 0;
}
