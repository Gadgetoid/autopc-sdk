/* Minimal AutoPC (Clarion 310C, Windows CE 2.0 SH3) homebrew API. Binds to the
   device's own coredll at runtime, reaching APIs the velo-toolchain import set
   does not expose, notably the faceplate display through the FACEPLT driver. */
#ifndef AUTOPC_H
#define AUTOPC_H

#include <windows.h>

void autopc_init(void);

void autopc_clear(void);
void autopc_print(const WCHAR *text);

HANDLE autopc_card_create(const WCHAR *leaf);

#endif
