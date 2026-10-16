/* Minimal AutoPC (Clarion 310C, Windows CE 2.0 SH3) homebrew API. Binds to the
   device's own coredll at runtime, reaching APIs the velo-toolchain import set
   does not expose: drawing into a device context such as the one
   autopc_app_begin_draw gives, and storage card files. */
#ifndef AUTOPC_H
#define AUTOPC_H

#include <windows.h>

void autopc_init(void);

void autopc_clear(HDC dc);
void autopc_print(HDC dc, const WCHAR *text);
void autopc_fill(HDC dc, int left, int top, int right, int bottom, COLORREF colour);

HANDLE autopc_card_create(const WCHAR *leaf);

#endif
