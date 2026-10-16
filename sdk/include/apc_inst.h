//
// APC_SETUP.H
//
// This public header file specifies function prototypes that APCLOAD.EXE will call
// in the ISV application's "INSTALL.DLL", as well as the supported return values.


//
// Install_Init
//
// @comm    Called before any part of the application is installed
//
typedef enum
{
    codeINSTALL_INIT_CONTINUE  = 0,     // @comm Continue with the installation
    codeINSTALL_INIT_CANCEL             // @comm Immediately cancel the installation
}
codeINSTALL_INIT;

codeINSTALL_INIT Install_Init(	BOOL	fFirstCall,		// is this the first time this function is being called?
								BOOL	fPreviouslyInstalled );

typedef codeINSTALL_INIT (*pfnINSTALL_INIT)( BOOL, BOOL );
const WCHAR wszINSTALL_INIT[]    = L"Install_Init";

//
// Install_Exit
//
// @comm    Called after the application is installed
//
typedef enum
{
    codeINSTALL_EXIT_DONE       = 0,    // @comm Exit the installation successfully
    codeINSTALL_EXIT_UNINSTALL          // @comm Uninstall the application before exiting the installation
}
codeINSTALL_EXIT;

codeINSTALL_EXIT Install_Exit(	WORD    cFailedDirs,
								WORD    cFailedFiles,
								WORD    cFailedRegKeys,
								WORD    cFailedRegVals,
								WORD    cFailedShortcuts );

typedef codeINSTALL_EXIT (*pfnINSTALL_EXIT)( WORD, WORD, WORD, WORD, WORD );
const WCHAR wszINSTALL_EXIT[]    = L"Install_Exit";

