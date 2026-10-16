/* Safe proof of concept: registers with the Forms Manager so the shell keeps
   it running, draws a message to the AutoPC faceplate for a minute and exits.
   It only writes to the screen; it reads and changes nothing on the device. */
#include "autopc.h"
#include "autopc_app.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previous, LPWSTR command_line, int show) {
    BOOL registered = autopc_register_app(instance);
    int i;
    if (!registered && autopc_detach(instance, command_line)) return 0;
    autopc_init();
    for (i = 0; i < 120; i++) {
        autopc_print(registered ? L"Hello from homebrew!" : L"Hello (detached)");
        Sleep(500);
    }
    autopc_unregister_app();
    return 0;
}
