/* A second demo: a mock car-stereo readout on the faceplate until Esc. Screen only. */
#include "autopc.h"
#include "autopc_app.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previous, LPWSTR command_line, int show) {
    if (!autopc_app_start(instance, 0, 0)) return 1;
    autopc_init();
    while (autopc_app_running()) {
        HDC dc = autopc_app_begin_draw();
        autopc_print(dc, L"GME 420.69  STONKS  +1337%");
        autopc_app_end_draw(dc);
        Sleep(200);
    }
    autopc_app_stop();
    return 0;
}
