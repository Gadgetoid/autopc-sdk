/* AutoPC homebrew API: runtime-bound faceplate drawing and storage-card
   helpers, resolved from the device coredll so they work under the stock OS. */
#include "autopc.h"

typedef HDC (WINAPI *CreateDCW_t)(const WCHAR *, const WCHAR *, const WCHAR *, const void *);
typedef BOOL (WINAPI *DeleteDC_t)(HDC);
typedef int (WINAPI *DrawTextW_t)(HDC, const WCHAR *, int, RECT *, UINT);
typedef int (WINAPI *FillRect_t)(HDC, const RECT *, HBRUSH);
typedef COLORREF (WINAPI *SetTextColor_t)(HDC, COLORREF);
typedef int (WINAPI *SetBkMode_t)(HDC, int);
typedef HGDIOBJ (WINAPI *GetStockObject_t)(int);

#define FACEPLATE_WIDTH  256
#define FACEPLATE_HEIGHT 64
#define BLACK_BRUSH      4
#define TRANSPARENT_MODE 1

static CreateDCW_t p_create_dc;
static DeleteDC_t p_delete_dc;
static DrawTextW_t p_draw_text;
static FillRect_t p_fill_rect;
static SetTextColor_t p_set_text_color;
static SetBkMode_t p_set_bk_mode;
static GetStockObject_t p_get_stock_object;

void autopc_init(void) {
    HINSTANCE coredll = LoadLibraryW(L"coredll.dll");
    p_create_dc = (CreateDCW_t)GetProcAddressW(coredll, L"CreateDCW");
    p_delete_dc = (DeleteDC_t)GetProcAddressW(coredll, L"DeleteDC");
    p_draw_text = (DrawTextW_t)GetProcAddressW(coredll, L"DrawTextW");
    p_fill_rect = (FillRect_t)GetProcAddressW(coredll, L"FillRect");
    p_set_text_color = (SetTextColor_t)GetProcAddressW(coredll, L"SetTextColor");
    p_set_bk_mode = (SetBkMode_t)GetProcAddressW(coredll, L"SetBkMode");
    p_get_stock_object = (GetStockObject_t)GetProcAddressW(coredll, L"GetStockObject");
}

static HDC faceplate_dc(RECT *area) {
    HDC dc = p_create_dc ? p_create_dc(L"FACEPLT", 0, 0, 0) : 0;
    area->left = 0;
    area->top = 0;
    area->right = FACEPLATE_WIDTH;
    area->bottom = FACEPLATE_HEIGHT;
    return dc;
}

void autopc_clear(void) {
    RECT area;
    HDC dc = faceplate_dc(&area);
    if (!dc) return;
    if (p_fill_rect && p_get_stock_object) p_fill_rect(dc, &area, (HBRUSH)p_get_stock_object(BLACK_BRUSH));
    if (p_delete_dc) p_delete_dc(dc);
}

void autopc_print(const WCHAR *text) {
    RECT area;
    HDC dc = faceplate_dc(&area);
    if (!dc) return;
    if (p_fill_rect && p_get_stock_object) p_fill_rect(dc, &area, (HBRUSH)p_get_stock_object(BLACK_BRUSH));
    if (p_set_text_color) p_set_text_color(dc, RGB(255, 255, 255));
    if (p_set_bk_mode) p_set_bk_mode(dc, TRANSPARENT_MODE);
    if (p_draw_text) p_draw_text(dc, text, -1, &area, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    if (p_delete_dc) p_delete_dc(dc);
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
