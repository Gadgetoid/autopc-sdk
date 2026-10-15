/* Safe proof of concept: draws a message to the AutoPC faceplate and exits.
   It only writes to the screen - it reads and changes nothing on the device. */
#include "autopc.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previous, LPWSTR command_line, int show) {
    int i;
    autopc_init();
    for (i = 0; i < 120; i++) {       /* ~60 s, redrawing so it stays on screen */
        autopc_print(L"Hello from homebrew!");
        Sleep(500);
    }
    return 0;
}
