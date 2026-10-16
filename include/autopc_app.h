/* AutoPC app lifetime. The shell terminates a launched program that has not
   registered with the Forms Manager within about 15 seconds; these register
   and deregister the program under its string resource 1 name, binding
   ole32, oleaut32 and asfc at runtime. autopc_detach is the fallback when the
   Forms Manager is unavailable: it relaunches the program outside the shell's
   watch. */
#ifndef AUTOPC_APP_H
#define AUTOPC_APP_H

#include <windows.h>

BOOL autopc_register_app(HINSTANCE instance);
void autopc_unregister_app(void);

BOOL autopc_detach(HINSTANCE instance, const WCHAR *command_line);

#endif
