/* Minimal AutoPC (Clarion 310C, Windows CE 2.0 SH3) homebrew API.
   Binds to the device's own coredll at runtime, so it reaches APIs the
   velo-toolchain import set does not expose (e.g. the faceplate GDI driver). */
#ifndef AUTOPC_H
#define AUTOPC_H

#include <windows.h>

/* Call once before anything else. */
void autopc_init(void);

/* Faceplate display (256 x 64). */
void autopc_clear(void);
void autopc_print(const WCHAR *text);   /* one centred line */

/* Storage card. The card mounts a moment after launch, so this retries. */
HANDLE autopc_card_create(const WCHAR *leaf);   /* \Storage Card\<leaf> for writing */

#endif
