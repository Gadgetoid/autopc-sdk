/* A second demo: a mock car-stereo readout on the faceplate. Screen only. */
#include "autopc.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previous, LPWSTR command_line, int show) {
    int i;
    autopc_init();
    for (i = 0; i < 120; i++) {
        autopc_print(L"GME 420.69  STONKS  +1337%");
        Sleep(500);
    }
    return 0;
}
