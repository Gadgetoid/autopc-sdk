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

/**
 * This function prototype is called before the uninstallation begins. This function can be used for
 * custom operations such as closing the application if it is running.
 *
 * @param hwndParent Handle to the parent window.
 * @param pszInstallDir Null-terminated string that contains the name of the install directory of
 *   the application.
 *
 * @return - codeUNINSTALL_INIT_CONTINUE: Continue with uninstallation. - codeUNINSTALL_INIT_CANCEL:
 *   Cancel uninstallation.
 *
 * The Uninstall_Init function prototype is part of Setup.dll, an ISV-created file for custom
 * operations dealing with installation and uninstallation of applications.
 */
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

/**
 * This function prototype is called after the uninstallation completes. This function can be used
 * for custom operations such as saving database data into a file and deleting the database,
 * informing the user on where the user data files are stored, or informing the user on how to
 * reinstall the application.
 *
 * @param hwndParent Handle to the parent window.
 *
 * @return - codeUNINSTALL_EXIT_DONE: Successful uninstallation.
 *
 * The Uninstall_Exit function prototype is part of Setup.dll, an ISV-created file for custom
 * operations dealing with installation and uninstallation of applications.
 */
codeUNINSTALL_EXIT Uninstall_Exit( );

typedef codeUNINSTALL_EXIT (*pfnUNINSTALL_EXIT)( );
const WCHAR wszUNINSTALL_EXIT[]  = L"Uninstall_Exit";
