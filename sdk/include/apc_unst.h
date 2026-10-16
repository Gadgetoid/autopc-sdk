//
// APC_UNST.H
//
// This public header file specifies function prototypes that APCLOAD.EXE will call
// in the ISV application's "UNINSTALL.DLL", as well as the supported return values.


//
// Uninstall_Init
//
// @comm    Called before the application is uninstalled
//
typedef enum
{
    codeUNINSTALL_INIT_CONTINUE = 0,    // @comm Continue with the uninstallation
    codeUNINSTALL_INIT_CANCEL           // @comm Immediately cancel the uninstallation
}
codeUNINSTALL_INIT;

codeUNINSTALL_INIT Uninstall_Init();

typedef codeUNINSTALL_INIT (*pfnUNINSTALL_INIT)( );
const WCHAR wszUNINSTALL_INIT[]  = L"Uninstall_Init";

//
// Uninstall_Exit
//
// @comm    Called after the application is uninstalled
//
typedef enum
{
    codeUNINSTALL_EXIT_DONE     = 0     // @comm Exit the uninstallation successfully
}
codeUNINSTALL_EXIT;

codeUNINSTALL_EXIT Uninstall_Exit( );

typedef codeUNINSTALL_EXIT (*pfnUNINSTALL_EXIT)( );
const WCHAR wszUNINSTALL_EXIT[]  = L"Uninstall_Exit";
