/* Safe proof of concept: a Forms Manager app that shows a message on the
   AutoPC faceplate until Esc. It only draws; it reads and changes nothing on
   the device. */
#include "autopc.h"
#include "autopc_app.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previous, LPWSTR command_line, int show) {
    if (!autopc_app_start(instance, 0, 0)) return 1;
    autopc_init();
    while (autopc_app_running()) {
        HDC dc = autopc_app_begin_draw();
        autopc_print(dc, L"Hello from homebrew!");
        autopc_app_end_draw(dc);
        Sleep(200);
    }
    autopc_app_stop();
    return 0;
}
