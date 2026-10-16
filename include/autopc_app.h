/* AutoPC application lifetime: a Forms Manager form that makes the program the
   foreground app, delivers the faceplate keys, and gives it a device context
   to draw into, binding ole32, oleaut32 and asfc at runtime. Esc quits unless
   the key handler takes it. */
#ifndef AUTOPC_APP_H
#define AUTOPC_APP_H

#include <windows.h>

#define AUTOPC_SCREEN_WIDTH  256
#define AUTOPC_SCREEN_HEIGHT 64

typedef BOOL (*autopc_key_fn)(void *context, UINT key, BOOL down);

BOOL autopc_app_start(HINSTANCE instance, autopc_key_fn on_key, void *context);
BOOL autopc_app_running(void);
void autopc_app_quit(void);
HDC  autopc_app_begin_draw(void);
void autopc_app_end_draw(HDC dc);
void autopc_app_stop(void);

#endif
