/* AutoPC homebrew API: runtime-bound faceplate drawing and storage-card
   helpers, resolved from the device coredll so they work under the stock OS. */
#include "autopc.h"

typedef int (WINAPI *DrawTextW_t)(HDC, const WCHAR *, int, RECT *, UINT);
typedef int (WINAPI *FillRect_t)(HDC, const RECT *, HBRUSH);
typedef COLORREF (WINAPI *SetTextColor_t)(HDC, COLORREF);
typedef int (WINAPI *SetBkMode_t)(HDC, int);
typedef HBRUSH (WINAPI *CreateSolidBrush_t)(COLORREF);

#define FACEPLATE_WIDTH  256
#define FACEPLATE_HEIGHT 64
#define TRANSPARENT_MODE 1
#define BRUSHES          16

static DrawTextW_t p_draw_text;
static FillRect_t p_fill_rect;
static SetTextColor_t p_set_text_color;
static SetBkMode_t p_set_bk_mode;
static CreateSolidBrush_t p_create_solid_brush;
static COLORREF brush_colours[BRUSHES];
static HBRUSH brushes[BRUSHES];
static int brush_count;

void autopc_init(void) {
    HINSTANCE coredll = LoadLibraryW(L"coredll.dll");
    p_draw_text = (DrawTextW_t)GetProcAddressW(coredll, L"DrawTextW");
    p_fill_rect = (FillRect_t)GetProcAddressW(coredll, L"FillRect");
    p_set_text_color = (SetTextColor_t)GetProcAddressW(coredll, L"SetTextColor");
    p_set_bk_mode = (SetBkMode_t)GetProcAddressW(coredll, L"SetBkMode");
    p_create_solid_brush = (CreateSolidBrush_t)GetProcAddressW(coredll, L"CreateSolidBrush");
}

static HBRUSH brush(COLORREF colour) {
    int i;
    for (i = 0; i < brush_count; i++) {
        if (brush_colours[i] == colour) return brushes[i];
    }
    if (!p_create_solid_brush || brush_count == BRUSHES) return 0;
    brush_colours[brush_count] = colour;
    brushes[brush_count] = p_create_solid_brush(colour);
    return brushes[brush_count++];
}

void autopc_fill(HDC dc, int left, int top, int right, int bottom, COLORREF colour) {
    RECT area;
    HBRUSH fill = brush(colour);
    if (!dc || !p_fill_rect || !fill || left >= right || top >= bottom) return;
    area.left = left;
    area.top = top;
    area.right = right;
    area.bottom = bottom;
    p_fill_rect(dc, &area, fill);
}

void autopc_clear(HDC dc) {
    autopc_fill(dc, 0, 0, FACEPLATE_WIDTH, FACEPLATE_HEIGHT, RGB(0, 0, 0));
}

void autopc_print(HDC dc, const WCHAR *text) {
    RECT area;
    if (!dc) return;
    autopc_clear(dc);
    area.left = 0;
    area.top = 0;
    area.right = FACEPLATE_WIDTH;
    area.bottom = FACEPLATE_HEIGHT;
    if (p_set_text_color) p_set_text_color(dc, RGB(255, 255, 255));
    if (p_set_bk_mode) p_set_bk_mode(dc, TRANSPARENT_MODE);
    if (p_draw_text) p_draw_text(dc, text, -1, &area, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

HANDLE autopc_card_create(const WCHAR *leaf) {
    WCHAR path[MAX_PATH];
    int attempt, length = 0;
    static const WCHAR prefix[] = L"\\Storage Card\\";
    while (prefix[length]) { path[length] = prefix[length]; length++; }
    while (*leaf && length < MAX_PATH - 1) path[length++] = *leaf++;
    path[length] = 0;
    for (attempt = 0; attempt < 60; attempt++) {
        HANDLE file = CreateFileW(path, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
        if (file != INVALID_HANDLE_VALUE) return file;
        Sleep(500);
    }
    return INVALID_HANDLE_VALUE;
}
