/* Declare WinMain, which the SDK's winbase.h leaves out, so editors can show its documentation. */
#include_next <winbase.h>

#ifndef AUTOPC_SDK_WINMAIN_DECLARED
#define AUTOPC_SDK_WINMAIN_DECLARED

#ifdef __cplusplus
extern "C" {
#endif

/**
 * This function is called by the system as the initial entry point for WindowsCE-based
 * applications.
 *
 * @param hInstance [in] Handle to the current instance of the application.
 * @param hPrevInstance [in] Handle to the previous instance of the application. For a Win32-based
 *   application, this parameter is always NULL. If you need to detect whether another instance
 *   already exists, create a uniquely named mutex using the CreateMutex function. CreateMutex will
 *   succeed even if the mutex already exists, but the GetLastError function will return
 *   ERROR_ALREADY_EXISTS. This indicates that another instance of your application exists, because it
 *   created the mutex first.
 * @param lpCmdLine [in] Pointer to a null-terminated string that specifies the command line for the
 *   application, excluding the program name.
 * @param nCmdShow [in] Specifies how the window is to be shown. This parameter can be one of the
 *   following values: Value Description SW_HIDE Hides the window and activates another window.
 *   SW_SHOW Activates a window and displays it in its current size and position. SW_SHOWNA Displays a
 *   window in its current state. The active window remains active. SW_SHOWNOACTIVATE Displays a
 *   window in its most recent size and position. The active window remains active. SW_SHOWNORMAL
 *   Activates and displays a window. If the window is minimized or maximized, the system restores it
 *   to its original size and position (same as SW_RESTORE).
 *
 * @return The exit value contained in that message's wParam parameter indicates success, and that
 *   the function terminates when it receives a WM_QUIT message. Zero indicates that the function
 *   terminates before entering the message loop.
 *
 * Your WinMain should initialize the application, display its main window, and enter a message
 * retrieval-and-dispatch loop that is the top-level control structure for the remainder of the
 * application's execution. Terminate the message loop when it receives a WM_QUIT message. At that
 * point, your WinMain should exit the application, returning the value passed in the WM_QUIT
 * message's wParam parameter. If WM_QUIT was received as a result of calling PostQuitMessage, the
 * value of wParam is the value of the PostQuitMessage function's nExitCode parameter.
 */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd);

#ifdef __cplusplus
}
#endif

#endif
