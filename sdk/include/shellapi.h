/*****************************************************************************\
*                                                                             *
* shellapi.h -  SHELL.DLL functions, types, and definitions                   *
*                                                                             *
* Copyright (c) 1992-1995, Microsoft Corp.  All rights reserved               *
*                                                                             *
\*****************************************************************************/

#ifndef _INC_SHELLAPI
#define _INC_SHELLAPI


//
// Define API decoration for direct importing of DLL references.
//
#ifndef WINSHELLAPI
#if !defined(_SHELL32_)
#define WINSHELLAPI DECLSPEC_IMPORT
#else
#define WINSHELLAPI
#endif
#endif // WINSHELLAPI


#include <pshpack1.h>

#ifdef __cplusplus
extern "C" {            /* Assume C declarations for C++ */
#endif  /* __cplusplus */


#define EIRESID(x) (-1 * (int)(x))

#ifndef ExtractIconExA
/**
 * This function retrieves the handle from the specified executable file or dynamic-link library
 * (DLL).
 *
 * @param lpszFile [in] Long pointer to a null-terminated string that specifies the name of an
 *   executable file, DLL, or icon file from which icons will be extracted.
 * @param nIconIndex [in] Specifies the zero-based index of the first icon to extract. For example,
 *   if this value is zero, the function extracts the first icon in the specified file. For Windows CE
 *   versions 2.10 and later, the nIconIndex parameter must be zero or -N, where N is a specified
 *   resource identifier. The nIcons parameter must be 1. For Windows CE versions 1.0 through 2.01,
 *   the function returns the total number of icons in the specified file if nIconIndex is -1 and
 *   phIconLarge and phiconSmall are both NULL. If the file is an executable file or DLL, the return
 *   value is the number of RT_GROUP_ICON resources. If the file is an .ICO file, the return value is
 *   1.
 * @param phiconLarge [out] Pointer to an array of icon handles which receives handles to the large
 *   icons extracted from the file. If this parameter is NULL, no large icons are extracted from the
 *   file.
 * @param phiconSmall [out] Pointer to an array of icon handles which receives handles to the small
 *   icons extracted from the file. If this parameter is NULL, no small icons are extracted from the
 *   file.
 * @param nIcons [in] Specifies the number of icons to extract from the file.
 *
 * @return For Windows CE versions 2.10 and later, this function returns the handle to an icon. If
 *   both phiconLarge and phiconSmall are not NULL, the return value defaults to the large icon. For
 *   Windows CE versions 1.0 through 2.01, this function returns a UINT data type. If the nIconIndex
 *   parameter is -1, the phiconLarge parameter is NULL, and the phiconSmall parameter is NULL, then
 *   the return value is the number of icons contained in the specified file. Otherwise, the return
 *   value is the number of icons successfully extracted from the file.
 *
 * You must destroy all icons extracted by ExtractIconEx by calling the DestroyIcon function.
 *
 * To retrieve the dimensions of the large and small icons, use the GetSystemMetrics function with
 * the SM_CXICON, SM_CYICON, SM_CXSMICON, and SM_CYSMICON flags.
 */
UINT WINAPI ExtractIconExA(LPCSTR lpszFile, int nIconIndex, HICON FAR *phiconLarge, HICON FAR *phiconSmall, UINT nIcons);
#endif

#ifndef ExtractIconExW
/**
 * This function retrieves the handle from the specified executable file or dynamic-link library
 * (DLL).
 *
 * @param lpszFile [in] Long pointer to a null-terminated string that specifies the name of an
 *   executable file, DLL, or icon file from which icons will be extracted.
 * @param nIconIndex [in] Specifies the zero-based index of the first icon to extract. For example,
 *   if this value is zero, the function extracts the first icon in the specified file. For Windows CE
 *   versions 2.10 and later, the nIconIndex parameter must be zero or -N, where N is a specified
 *   resource identifier. The nIcons parameter must be 1. For Windows CE versions 1.0 through 2.01,
 *   the function returns the total number of icons in the specified file if nIconIndex is -1 and
 *   phIconLarge and phiconSmall are both NULL. If the file is an executable file or DLL, the return
 *   value is the number of RT_GROUP_ICON resources. If the file is an .ICO file, the return value is
 *   1.
 * @param phiconLarge [out] Pointer to an array of icon handles which receives handles to the large
 *   icons extracted from the file. If this parameter is NULL, no large icons are extracted from the
 *   file.
 * @param phiconSmall [out] Pointer to an array of icon handles which receives handles to the small
 *   icons extracted from the file. If this parameter is NULL, no small icons are extracted from the
 *   file.
 * @param nIcons [in] Specifies the number of icons to extract from the file.
 *
 * @return For Windows CE versions 2.10 and later, this function returns the handle to an icon. If
 *   both phiconLarge and phiconSmall are not NULL, the return value defaults to the large icon. For
 *   Windows CE versions 1.0 through 2.01, this function returns a UINT data type. If the nIconIndex
 *   parameter is -1, the phiconLarge parameter is NULL, and the phiconSmall parameter is NULL, then
 *   the return value is the number of icons contained in the specified file. Otherwise, the return
 *   value is the number of icons successfully extracted from the file.
 *
 * You must destroy all icons extracted by ExtractIconEx by calling the DestroyIcon function.
 *
 * To retrieve the dimensions of the large and small icons, use the GetSystemMetrics function with
 * the SM_CXICON, SM_CYICON, SM_CXSMICON, and SM_CYSMICON flags.
 */
UINT WINAPI ExtractIconExW(LPCWSTR lpszFile, int nIconIndex, HICON FAR *phiconLarge, HICON FAR *phiconSmall, UINT nIcons);
#endif

#ifdef UNICODE
/**
 * This function retrieves the handle from the specified executable file or dynamic-link library
 * (DLL).
 *
 * @param lpszFile [in] Long pointer to a null-terminated string that specifies the name of an
 *   executable file, DLL, or icon file from which icons will be extracted.
 * @param nIconIndex [in] Specifies the zero-based index of the first icon to extract. For example,
 *   if this value is zero, the function extracts the first icon in the specified file. For Windows CE
 *   versions 2.10 and later, the nIconIndex parameter must be zero or -N, where N is a specified
 *   resource identifier. The nIcons parameter must be 1. For Windows CE versions 1.0 through 2.01,
 *   the function returns the total number of icons in the specified file if nIconIndex is -1 and
 *   phIconLarge and phiconSmall are both NULL. If the file is an executable file or DLL, the return
 *   value is the number of RT_GROUP_ICON resources. If the file is an .ICO file, the return value is
 *   1.
 * @param phiconLarge [out] Pointer to an array of icon handles which receives handles to the large
 *   icons extracted from the file. If this parameter is NULL, no large icons are extracted from the
 *   file.
 * @param phiconSmall [out] Pointer to an array of icon handles which receives handles to the small
 *   icons extracted from the file. If this parameter is NULL, no small icons are extracted from the
 *   file.
 * @param nIcons [in] Specifies the number of icons to extract from the file.
 *
 * @return For Windows CE versions 2.10 and later, this function returns the handle to an icon. If
 *   both phiconLarge and phiconSmall are not NULL, the return value defaults to the large icon. For
 *   Windows CE versions 1.0 through 2.01, this function returns a UINT data type. If the nIconIndex
 *   parameter is -1, the phiconLarge parameter is NULL, and the phiconSmall parameter is NULL, then
 *   the return value is the number of icons contained in the specified file. Otherwise, the return
 *   value is the number of icons successfully extracted from the file.
 *
 * You must destroy all icons extracted by ExtractIconEx by calling the DestroyIcon function.
 *
 * To retrieve the dimensions of the large and small icons, use the GetSystemMetrics function with
 * the SM_CXICON, SM_CYICON, SM_CXSMICON, and SM_CYSMICON flags.
 */
#define ExtractIconEx  ExtractIconExW
#else
/**
 * This function retrieves the handle from the specified executable file or dynamic-link library
 * (DLL).
 *
 * @param lpszFile [in] Long pointer to a null-terminated string that specifies the name of an
 *   executable file, DLL, or icon file from which icons will be extracted.
 * @param nIconIndex [in] Specifies the zero-based index of the first icon to extract. For example,
 *   if this value is zero, the function extracts the first icon in the specified file. For Windows CE
 *   versions 2.10 and later, the nIconIndex parameter must be zero or -N, where N is a specified
 *   resource identifier. The nIcons parameter must be 1. For Windows CE versions 1.0 through 2.01,
 *   the function returns the total number of icons in the specified file if nIconIndex is -1 and
 *   phIconLarge and phiconSmall are both NULL. If the file is an executable file or DLL, the return
 *   value is the number of RT_GROUP_ICON resources. If the file is an .ICO file, the return value is
 *   1.
 * @param phiconLarge [out] Pointer to an array of icon handles which receives handles to the large
 *   icons extracted from the file. If this parameter is NULL, no large icons are extracted from the
 *   file.
 * @param phiconSmall [out] Pointer to an array of icon handles which receives handles to the small
 *   icons extracted from the file. If this parameter is NULL, no small icons are extracted from the
 *   file.
 * @param nIcons [in] Specifies the number of icons to extract from the file.
 *
 * @return For Windows CE versions 2.10 and later, this function returns the handle to an icon. If
 *   both phiconLarge and phiconSmall are not NULL, the return value defaults to the large icon. For
 *   Windows CE versions 1.0 through 2.01, this function returns a UINT data type. If the nIconIndex
 *   parameter is -1, the phiconLarge parameter is NULL, and the phiconSmall parameter is NULL, then
 *   the return value is the number of icons contained in the specified file. Otherwise, the return
 *   value is the number of icons successfully extracted from the file.
 *
 * You must destroy all icons extracted by ExtractIconEx by calling the DestroyIcon function.
 *
 * To retrieve the dimensions of the large and small icons, use the GetSystemMetrics function with
 * the SM_CXICON, SM_CYICON, SM_CXSMICON, and SM_CYSMICON flags.
 */
#define ExtractIconEx  ExtractIconExA
#endif // !UNICODE


////
//// Shell File Operations
////

#ifndef FO_MOVE //these need to be kept in sync with the ones in shlobj.h

#define FO_MOVE           0x0001
#define FO_COPY           0x0002
#define FO_DELETE         0x0003
#define FO_RENAME         0x0004

#define FOF_MULTIDESTFILES         0x0001
#define FOF_CONFIRMMOUSE           0x0002
#define FOF_SILENT                 0x0004  // don't create progress/report
#define FOF_RENAMEONCOLLISION      0x0008
#define FOF_NOCONFIRMATION         0x0010  // Don't prompt the user.
#define FOF_WANTMAPPINGHANDLE      0x0020  // Fill in SHFILEOPSTRUCT.hNameMappings
                                      // Must be freed using SHFreeNameMappings
#define FOF_ALLOWUNDO              0x0040
#define FOF_FILESONLY              0x0080  // on *.*, do only files
#define FOF_SIMPLEPROGRESS         0x0100  // means don't show names of files
#define FOF_NOCONFIRMMKDIR         0x0200  // don't confirm making any needed dirs

typedef WORD FILEOP_FLAGS;

#define PO_DELETE       0x0013  // printer is being deleted
#define PO_RENAME       0x0014  // printer is being renamed
#define PO_PORTCHANGE   0x0020  // port this printer connected to is being changed
                                // if this id is set, the strings received by
                                // the copyhook are a doubly-null terminated
                                // list of strings.  The first is the printer
                                // name and the second is the printer port.
#define PO_REN_PORT     0x0034  // PO_RENAME and PO_PORTCHANGE at same time.

// no POF_ flags currently defined

typedef WORD PRINTEROP_FLAGS;

#endif // FO_MOVE

// implicit parameters are:
//      if pFrom or pTo are unqualified names the current directories are
//      taken from the global current drive/directory settings managed
//      by Get/SetCurrentDrive/Directory
//
//      the global confirmation settings

#ifndef UNICODE_ONLY
typedef struct _SHFILEOPSTRUCTA
{
        HWND            hwnd;
        UINT            wFunc;
        LPCSTR          pFrom;
        LPCSTR          pTo;
        FILEOP_FLAGS    fFlags;
        BOOL            fAnyOperationsAborted;
        LPVOID          hNameMappings;
        LPCSTR           lpszProgressTitle; // only used if FOF_SIMPLEPROGRESS
} SHFILEOPSTRUCTA, FAR *LPSHFILEOPSTRUCTA;
#endif //!UNICODE_ONLY
#ifndef ANSI_ONLY
typedef struct _SHFILEOPSTRUCTW
{
        HWND            hwnd;
        UINT            wFunc;
        LPCWSTR         pFrom;
        LPCWSTR         pTo;
        FILEOP_FLAGS    fFlags;
        BOOL            fAnyOperationsAborted;
        LPVOID          hNameMappings;
        LPCWSTR          lpszProgressTitle; // only used if FOF_SIMPLEPROGRESS
} SHFILEOPSTRUCTW, FAR *LPSHFILEOPSTRUCTW;
#endif //!ANSI_ONLY
#ifdef UNICODE
typedef SHFILEOPSTRUCTW SHFILEOPSTRUCT;
typedef LPSHFILEOPSTRUCTW LPSHFILEOPSTRUCT;
#else
typedef SHFILEOPSTRUCTA SHFILEOPSTRUCT;
typedef LPSHFILEOPSTRUCTA LPSHFILEOPSTRUCT;
#endif // UNICODE

#ifndef UNICODE_ONLY
WINSHELLAPI int WINAPI SHFileOperationA(LPSHFILEOPSTRUCTA lpFileOp);
#endif //!UNICODE_ONLY
#ifndef ANSI_ONLY
WINSHELLAPI int WINAPI SHFileOperationW(LPSHFILEOPSTRUCTW lpFileOp);
#endif //!ANSI_ONLY
#ifdef UNICODE
#define SHFileOperation  SHFileOperationW
#else
#define SHFileOperation  SHFileOperationA
#endif // !UNICODE


////
////  Begin ShellExecuteEx and family
////

/* regular WinExec() codes */
#define SE_ERR_FNF              2       // file not found
#define SE_ERR_PNF              3       // path not found
#define SE_ERR_ACCESSDENIED     5       // access denied
#define SE_ERR_OOM              8       // out of memory
#define SE_ERR_DLLNOTFOUND              32

/* error values for ShellExecute() beyond the regular WinExec() codes */
#define SE_ERR_SHARE                    26
#define SE_ERR_ASSOCINCOMPLETE          27
#define SE_ERR_DDETIMEOUT               28
#define SE_ERR_DDEFAIL                  29
#define SE_ERR_DDEBUSY                  30
#define SE_ERR_NOASSOC                  31

/**
 * This structure specifies an enumerated type that defines flags used with the
 * IShellFolder::EnumObjects method.
 */
typedef struct _SHELLEXECUTEINFO
{
        /**
         * Size of the structure, in bytes.
         */
        DWORD cbSize;
        /**
         * Array of flags that indicate the content and validity of the other structure members. For Windows
         * CE versions 1.0 and 1.01, fMask flags are unsupported. For Windows CE versions 2.0 and later,
         * fMask can be a combination of the following values:
         *
         * - SEE_MASK_FLAG_NO_UI: Does not display an error message box if an error occurs.
         *
         * - SEE_MASK_NOCLOSEPROCESS: Leaves the process running after the ShellExecuteEx function exits.
         * The hProcess member receives the handle to the process.
         */
        ULONG fMask;
        /**
         * Window handle to any message boxes that the system may produce while executing this function.
         */
        HWND hwnd;
        /**
         * Long pointer to a string specifying the name of a verb. The verb specifies an action for the
         * application to perform. The set of available verbs depends on the particular file or folder. It
         * includes the commands listed in the context menu and the registry. This member defaults to Open
         * if no verb is specified. The following verbs are usually valid:
         *
         * - edit: Opens an editor. If lpFile is not a document file, the function will fail.
         *
         * - explore: The function explores the folder specified by lpFile.
         *
         * - open: The function opens the file specified by the lpFile parameter. The file can be an
         * executable file or a document file. It can also be a folder.
         *
         * - print: The function prints the document file specified by lpFile. If lpFile is not a document
         * file, the function will fail.
         *
         * - properties: Displays the file or folder's properties.
         */
        LPCTSTR lpVerb;
        /**
         * Long pointer to a null-terminated string that specifies the name of the file to open or print.
         * The function can open an executable file or a document file, but it can only print a document
         * file. If the path is not included with the name, the current directory is assumed.
         */
        LPCTSTR lpFile;
        /**
         * Long pointer to a null-terminated string that contains the application parameters. The parameters
         * must be separated by spaces. To include double quotation marks, you must enclose the marks in
         * double quotation marks, as in the following code example:
         *
         *     sei.lpParameters = "An example: \"\"\"quoted text\"\"\"";
         *
         * In this case, the application receives three parameters: An, example:, and "quoted text".
         *
         * If the lpFile member specifies a document file, this member should be NULL.
         */
        LPCTSTR lpParameters;
        /**
         * Pointer to a null-terminated string that specifies the name of the working directory. If this
         * member is not specified, the current directory is used as the working directory.
         */
        LPCTSTR lpDirectory;
        /**
         * Show flags. Can be one of the SW_* values described for the ShowWindow function. If the lpFile
         * specifies an executable file, this member specifies how the application is to be shown when it is
         * opened.
         */
        int nShow;
        /**
         * Instance handle to the application that the ShellExecuteEx function started. If the function
         * fails, this member receives one of the following error values, which are less than or equal to
         * 32:
         *
         * - SE_ERR_FNF: File not found.
         *
         * - SE_ERR_PNF: Path not found.
         *
         * - SE_ERR_ACCESSDENIED: Access denied.
         *
         * - SE_ERR_OOM: Out of memory.
         *
         * - SE_ERR_DLLNOTFOUND: Dynamic-link library not found.
         *
         * - SE_ERR_SHARE: Cannot share an open file.
         *
         * - SE_ERR_ASSOCINCOMPLETE: File association information not complete.
         *
         * - SE_ERR_DDETIMEOUT: DDE operation timed out.
         *
         * - SE_ERR_DDEFAIL: DDE operation failed.
         *
         * - SE_ERR_DDEBUSY: DDE operation is busy.
         *
         * - SE_ERR_NOASSOC: File association not available.
         */
        HINSTANCE hInstApp;
        // Optional fields
        /**
         * Ignored.
         */
        LPVOID lpIDList;
        /**
         * Ignored.
         */
        LPCTSTR lpClass;
        /**
         * Ignored.
         */
        HKEY hkeyClass;
        /**
         * Ignored.
         */
        DWORD dwHotKey;
        /**
         * Ignored.
         */
        HANDLE hIcon;
        /**
         * Handle to the newly started application. This member is set on return and is always NULL if fMask
         * is not set to SEE_MASK_NOCLOSEPROCESS.
         */
        HANDLE hProcess;
} SHELLEXECUTEINFO, FAR *LPSHELLEXECUTEINFO;

/**
 * This function performs an action on a file. The file can be an executable file or a document.
 *
 * @param lpExecInfo Long pointer to a SHELLEXECUTEINFO structure that contains and receives
 *   information about the application being executed.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * If the function succeeds, it sets the hInstApp member of the SHELLEXECUTEINFO structure to the
 * instance handle to the application that the function started. If the function fails, hInstApp is
 * one of the SE_ERR_ error values indicating the cause of the failure. (An instance handle will
 * always be greater than 32 and an error value less than 32.) Note that the SE_ERR_ error values
 * are for compatibility with the ShellExecute function; use the GetLastError function to retrieve
 * error information.
 *
 * The error value returned by GetLastError corresponds to the SE_ERR_ values and is one of the
 * values described in the following table.
 *
 * Value Description ERROR_FILE_NOT_FOUND The specified file was not found. ERROR_PATH_NOT_FOUND The
 * specified path was not found. ERROR_DDE_FAIL The DDE transaction failed. ERROR_NO_ASSOCIATION
 * There is no application associated with the given file name extension. ERROR_ACCESS_DENIED Access
 * to the specified file is denied. ERROR_DLL_NOT_FOUND One of the library files necessary to run
 * the application can't be found. ERROR_CANCELLED The function prompted the user for the location
 * of the application, but the user canceled the request. ERROR_NOT_ENOUGH_MEMORY There is not
 * enough memory to perform the specified action. ERROR_SHARING_VIOLATION A sharing violation
 * occurred.
 */
WINSHELLAPI BOOL WINAPI ShellExecuteEx(LPSHELLEXECUTEINFO lpExecInfo);

////
////  End ShellExecuteEx and family
////


////
//// Tray notification definitions
////

/**
 * This structure contains information that the system needs to process taskbar status area
 * messages.
 */
typedef struct _NOTIFYICONDATAA {
        /**
         * Size of this structure, in bytes.
         */
        DWORD cbSize;
        /**
         * Handle to the window that will receive notification messages associated with an icon in the
         * taskbar status area.
         */
        HWND hWnd;
        /**
         * Application-defined identifier of the taskbar icon.
         */
        UINT uID;
        /**
         * Array of flags that indicate which of the other members contain valid data. This member can be a
         * combination of the following: Value Description NIF_ICON The hIcon member is valid. NIF_MESSAGE
         * The uCallbackMessage member is valid. NIF_TIP The szTip member is valid.
         */
        UINT uFlags;
        /**
         * Application-defined message identifier. The system uses this identifier for notification messages
         * that it sends to the window identified in hWnd. These notifications are sent when a mouse event
         * occurs in the bounding rectangle of the icon.
         */
        UINT uCallbackMessage;
        /**
         * Handle to the icon to add, modify, or delete.
         */
        HICON hIcon;
        /**
         * Null-terminated string that contains ToolTip text to display for the icon.
         */
        CHAR  szTip[64];
} NOTIFYICONDATAA, *PNOTIFYICONDATAA;

/**
 * This structure contains information that the system needs to process taskbar status area
 * messages.
 */
typedef struct _NOTIFYICONDATAW {
        /**
         * Size of this structure, in bytes.
         */
        DWORD cbSize;
        /**
         * Handle to the window that will receive notification messages associated with an icon in the
         * taskbar status area.
         */
        HWND hWnd;
        /**
         * Application-defined identifier of the taskbar icon.
         */
        UINT uID;
        /**
         * Array of flags that indicate which of the other members contain valid data. This member can be a
         * combination of the following: Value Description NIF_ICON The hIcon member is valid. NIF_MESSAGE
         * The uCallbackMessage member is valid. NIF_TIP The szTip member is valid.
         */
        UINT uFlags;
        /**
         * Application-defined message identifier. The system uses this identifier for notification messages
         * that it sends to the window identified in hWnd. These notifications are sent when a mouse event
         * occurs in the bounding rectangle of the icon.
         */
        UINT uCallbackMessage;
        /**
         * Handle to the icon to add, modify, or delete.
         */
        HICON hIcon;
        /**
         * Null-terminated string that contains ToolTip text to display for the icon.
         */
        WCHAR  szTip[64];
} NOTIFYICONDATAW, *PNOTIFYICONDATAW;
#ifdef UNICODE
typedef NOTIFYICONDATAW NOTIFYICONDATA;
typedef PNOTIFYICONDATAW PNOTIFYICONDATA;
#else
typedef NOTIFYICONDATAA NOTIFYICONDATA;
typedef PNOTIFYICONDATAA PNOTIFYICONDATA;
#endif // UNICODE


#define NIM_ADD         0x00000000
#define NIM_MODIFY      0x00000001
#define NIM_DELETE      0x00000002

#define NIF_MESSAGE     0x00000001
#define NIF_ICON        0x00000002
#define NIF_TIP         0x00000004

/**
 * This function sends a message to the system to add, modify, or delete an icon from the taskbar
 * status area.
 *
 * @param dwMessage [in] Specifies the message value to send. It is one of these values: Value
 *   Description NIM_ADD Adds an icon to the status area. NIM_DELETE Deletes an icon from the status
 *   area. NIM_MODIFY Modifies an icon in the status area.
 * @param pnid [in] Pointer to a NOTIFYICONDATA structure. The content of the structure depends on
 *   the value of dwMessage.
 *
 * @return Nonzero indicates success. Zero indicates failure.
 */
BOOL WINAPI Shell_NotifyIcon(DWORD dwMessage, PNOTIFYICONDATA lpData);

////
//// End Tray Notification Icons
////


////
//// Begin SHGetFileInfo
////

/*
 * The SHGetFileInfo API provides an easy way to get attributes
 * for a file given a pathname.
 *
 *   PARAMETERS
 *
 *     pszPath              file name to get info about
 *     dwFileAttributes     file attribs, only used with SHGFI_USEFILEATTRIBUTES
 *     psfi                 place to return file info
 *     cbFileInfo           size of structure
 *     uFlags               flags
 *
 *   RETURN
 *     TRUE if things worked
 */

#ifndef UNICODE_ONLY
/**
 * This structure contains information about a file object.
 *
 * This structure is used with the SHGetFileInfo function.
 */
typedef struct _SHFILEINFOA
{
        /**
         * Handle to the icon that represents the file.
         */
        HICON       hIcon;                      // out: icon
        /**
         * Index of the icon image within the system image list.
         */
        int         iIcon;                      // out: icon index
        /**
         * Specifies the attributes of the file object.
         */
        DWORD       dwAttributes;               // out: SFGAO_ flags
        /**
         * Null-terminated string that contains the name of the file as it appears in the Windows shell, or
         * the path and file name of the file that contains the icon representing the file.
         */
        CHAR        szDisplayName[MAX_PATH];    // out: display name (or path)
        /**
         * Null-terminated string that describes the type of file.
         */
        CHAR        szTypeName[80];             // out: type name
} SHFILEINFOA;
#endif //!UNICODE_ONLY
#ifndef ANSI_ONLY
/**
 * This structure contains information about a file object.
 *
 * This structure is used with the SHGetFileInfo function.
 */
typedef struct _SHFILEINFOW
{
        /**
         * Handle to the icon that represents the file.
         */
        HICON       hIcon;                      // out: icon
        /**
         * Index of the icon image within the system image list.
         */
        int         iIcon;                      // out: icon index
        /**
         * Specifies the attributes of the file object.
         */
        DWORD       dwAttributes;               // out: SFGAO_ flags
        /**
         * Null-terminated string that contains the name of the file as it appears in the Windows shell, or
         * the path and file name of the file that contains the icon representing the file.
         */
        WCHAR       szDisplayName[MAX_PATH];    // out: display name (or path)
        /**
         * Null-terminated string that describes the type of file.
         */
        WCHAR       szTypeName[80];             // out: type name
} SHFILEINFOW;
#endif //!ANSI_ONLY
#ifdef UNICODE
typedef SHFILEINFOW SHFILEINFO;
#else
typedef SHFILEINFOA SHFILEINFO;
#endif // UNICODE

#define SHGFI_ICON              0x000000100     // get icon
#define SHGFI_DISPLAYNAME       0x000000200     // get display name
#define SHGFI_TYPENAME          0x000000400     // get type name
#define SHGFI_ATTRIBUTES        0x000000800     // get attributes
#define SHGFI_ICONLOCATION      0x000001000     // get icon location
#define SHGFI_EXETYPE           0x000002000     // return exe type
#define SHGFI_SYSICONINDEX      0x000004000     // get system icon index
#define SHGFI_LINKOVERLAY       0x000008000     // put a link overlay on icon
#define SHGFI_SELECTED          0x000010000     // show icon in selected state
#define SHGFI_LARGEICON         0x000000000     // get large icon
#define SHGFI_SMALLICON         0x000000001     // get small icon
#define SHGFI_OPENICON          0x000000002     // get open icon
#define SHGFI_SHELLICONSIZE     0x000000004     // get shell size icon
#define SHGFI_PIDL              0x000000008     // pszPath is a pidl
#define SHGFI_USEFILEATTRIBUTES 0x000000010     // use passed dwFileAttribute

/**
 * This function retrieves information about an object in the file system, such as a file, a folder,
 * a directory, or a drive root.
 *
 * @param pszPath [in] Pointer to a buffer that contains the path and file name. Both absolute and
 *   relative paths are valid. If the uFlags parameter includes the SHGFI_PIDL flag, this parameter
 *   must be the address of an ITEMLIST (PIDL) structure that contains the list of item identifiers
 *   that uniquely identifies the file within the shell's namespace. The PIDL must be a fully
 *   qualified PIDL. Relative PIDLs are not allowed. If the uFlags parameter includes the
 *   SHGFI_USEFILEATTRIBUTES flag, this parameter does not have to be a valid file name. The function
 *   will proceed as if the file exists with the specified name and with the file attributes passed in
 *   the dwFileAttributes parameter. This allows you to obtain information about a file type by
 *   passing just the extension for pszPath and passing FILE_ATTRIBUTE_NORMAL in dwFileAttributes.
 *   This string can use either short (the 8.3 form) or long file names.
 * @param dwFileAttributes [in] Combination of one or more file attribute flags (FILE_ATTRIBUTE_*
 *   values). If uFlags does not include the SHGFI_USEFILEATTRIBUTES flag, this parameter is ignored.
 *   Windows CE supports the following additional values for the dwFileAttributes parameter: Value
 *   Description FILE_ATTRIBUTE_INROM The file is an operating system file stored in ROM. These files
 *   are read-only. FILE_ATTRIBUTE_ROMMODULE The file is an operating system file stored in ROM,
 *   designed to execute in place. In other words, code from this file is executed directly from ROM,
 *   rather than being first copied to RAM. The CreateFile function cannot be used to access this
 *   file, instead the LoadLibrary and CreateProcess functions must be used.
 * @param psfi [in] Pointer to a SHFILEINFO structure to receive the file information.
 * @param cbFileInfo [in] Size, in bytes, of the SHFILEINFO structure pointed to by the psfi
 *   parameter.
 * @param uFlags [in] Flags that specify the file information to retrieve. It can be a combination
 *   of the following values: Value Description SHGFI_ATTR_SPECIFIED Modifies SHGFI_ATTRIBUTES.
 *   Indicates that the dwAttributes member of the SHFILEINFO structure at psfi contains the specific
 *   attributes that are desired. SHGFI_ATTRIBUTES Retrieve the item attributes. The attributes are
 *   copied to the dwAttributes member of the structure specified in the psfi parameter.
 *   SHGFI_DISPLAYNAME Retrieve the display name for the file. The name is copied to the szDisplayName
 *   member of the structure specified in psfi. The returned display name uses the long file name, if
 *   there is one, rather than the 8.3 form of the file name. SHGFI_EXETYPE Retrieve the type of the
 *   executable file if pszPath identifies an executable file. This flag cannot be specified with any
 *   other flags. SHGFI_ICON Retrieve the handle to the icon that represents the file and the index of
 *   the icon within the system image list. The handle is copied to the hIcon member of the structure
 *   specified by psfi, and the index is copied to the iIcon member. The return value is the handle to
 *   the system image list. You must call the DestroyIcon function on this icon handle.
 *   SHGFI_ICONLOCATION Retrieve the name of the file that contains the icon representing the file.
 *   The name is copied to the szDisplayName member of the structure specified in psfi.
 *   SHGFI_LARGEICON Modify SHGFI_ICON, causing the function to retrieve the file's large icon.
 *   SHGFI_LINKOVERLAY Modify SHGFI_ICON, causing the function to add the link overlay to the file's
 *   icon. SHGFI_OPENICON Modify SHGFI_ICON, causing the function to retrieve the file's open icon. A
 *   container object displays an open icon to indicate that the container is open. SHGFI_PIDL
 *   Indicate that pszPath is the address of an ITEMIDLIST structure rather than a path name.
 *   SHGFI_SELECTED Modify SHGFI_ICON, causing the function to blend the file's icon with the system
 *   highlight color. SHGFI_SHELLICONSIZE Modify SHGFI_ICON, causing the function to retrieve a
 *   shell-sized icon. If this flag is not specified the function sizes the icon according to the
 *   system metric values. SHGFI_SMALLICON Modify SHGFI_ICON, causing the function to retrieve the
 *   file's small icon. SHGFI_SYSICONINDEX Retrieve the index of the icon within the system image
 *   list. The index is copied to the iIcon member of the structure specified by psfi. The return
 *   value is the handle to the system image list. SHGFI_TYPENAME Retrieve the string that describes
 *   the file's type. The string is copied to the szTypeName member of the structure specified in
 *   psfi. SHGFI_USEFILEATTRIBUTES Indicates that the function should not attempt to access the file
 *   specified by pszPath. Rather, it should act as if the file specified by pszPath exists with the
 *   file attributes passed in dwFileAttributes. This flag cannot be combined with the
 *   SHGFI_ATTRIBUTES, SHGFI_EXETYPE, or SHGFI_PIDL flags.
 *
 * @return Returns a value whose meaning depends on the uFlags parameter. If uFlags contains the
 *   SHGFI_EXETYPE flag, the return value specifies the type of the executable file. It will be one of
 *   the following values: Value Executable File Type 0 Nonexecutable file or an error condition
 *   Low-order word = NE or PE and high-order word = 3.0, 3.5, or 4.0 Windows application Low-order
 *   word = MZ and high-order word = 0 MS-DOS .exe, .com, or .bat file Low-order word = PE and
 *   high-order word = 0 Win32 console application If uFlags contains SHGFI_SYSICONINDEX, the return
 *   value is the handle to the system image list that contains the large icon images. If
 *   SHGFI_SMALLICON is included with SHGFI_SYSICONINDEX, the return value is the handle to the image
 *   list that contains the small icon images. If uFlags does not contain SHGFI_EXETYPE or
 *   SHGFI_SYSICONINDEX, the return value is nonzero if successful, or zero otherwise.
 *
 * For Windows CE versions 2.10 and later, SHGetFileInfo does not support the following values for
 * uFlags:
 *
 * SHGFI_ATTRIBUTES
 *
 * SHGFI_EXETYPE
 *
 * SHGFI_ICONLOCATION
 *
 * SHGFI_LINKOVERLAY
 *
 * SHGFI_OPENICON
 *
 * SHGFI_SELECTED
 *
 * SHGFI_SHELLICONSIZE
 *
 * Also for Windows CE versions 2.10 and later, SHGetFileInfo supports the SHGFI_PIDL flag for the
 * H/PC platform only.
 */
DWORD WINAPI SHGetFileInfo(LPCTSTR pszPath, DWORD dwFileAttributes,
						   SHFILEINFO *psfi, UINT cbFileInfo, UINT uFlags);

////
//// End SHGetFileInfo
////


//
// SHAddToRecentDocs
//
#define SHARD_PIDL	0x00000001L
#define SHARD_PATH      0x00000002L

/**
 * This function adds a document to the shell's list of recently used documents or clears all
 * documents from the list. The user gains access to the list through the Start menu of a taskbar or
 * other top-level application.
 *
 * @param uFlags [in] Flag that indicates the meaning of the pv parameter. It is one of the
 *   following values: Value Description SHARD_PATH The pv parameter contains the address of a path
 *   string. SHARD_PIDL The pv parameter contains the address of an item identifier list (PIDL) that
 *   identifies a file object. PIDLs that identify nonfile objects are not allowed.
 * @param pv [in] Void pointer to a character buffer that contains the path and file name of the
 *   document, or the address of an ITEMIDLIST structure that contains an item identifier list that
 *   uniquely identifies the document. If this parameter is NULL, the function clears all documents
 *   from the list.
 *
 * @return None.
 *
 * In Windows CE, you cannot add more than ten documents to the recently used documents list.
 */
void WINAPI SHAddToRecentDocs(UINT uFlags, LPCVOID pv);
#define SHORTCUT_OVERWRITE				0x00000001
/**
 * This function creates a shortcut. A remote application interface (RAPI) version of this function
 * exists, and it is called CeSHCreateShortcut.
 *
 * @param szShortcut Null-terminated string that contains the name of the shortcut to create.
 *   Passing a NULL value for this parameter will cause an exception
 * @param szTarget Null-terminated string that contains the target path of the shortcut. The size of
 *   the buffer is limited to 256 characters.
 */
DWORD WINAPI SHCreateShortcut(LPTSTR szShortcut, LPTSTR szTarget);
/**
 * This function retrieves the shortcut's target path. A remote application interface (RAPI) version
 * of this function exists, and it is called CeSHGetShortcutTarget.
 *
 * @param szShortcut Null-terminated string that contains the name of the shortcut to create.
 * @param szTarget Null-terminated string that gets the target path of the shortcut. The buffer must
 *   be at least cbMax characters long.
 * @param cbMax Maximum number of characters that can be copied to the buffer.
 *
 * @return True indicates success. FALSE indicates failure.
 */
BOOL WINAPI SHGetShortcutTarget(LPCTSTR szShortcut, LPTSTR szTarget, int cb);
/**
 * This function displays a system-defined dialog box notifying the user that memory is full.
 *
 * @param hwndOwner Handle to the window that owns the dialog box.
 * @param grfFlags Reserved; set to zero.
 *
 * @return None.
 */
int WINAPI SHShowOutOfMemory(HWND hwndOwner, UINT grfFlags);
/**
 * This function loads a bitmap from the specified file.
 *
 * @param szFileName Null-terminated string that contains the fully qualified path and file name
 *   that the bitmap will be loaded from.
 *
 * @return If the function succeeds, the return value is the handle to the bitmap loaded from the
 *   file, otherwise the return value is NULL.
 */
HBITMAP WINAPI SHLoadDIBitmap(LPCTSTR szFileName);

#ifndef UNDER_NT
#ifdef WINCEOEM
#ifdef WINCEMACRO
#include <mshellap.h>
#endif
#endif
#endif


#ifdef __cplusplus
}
#endif  /* __cplusplus */

#include <poppack.h>

#endif  /* _INC_SHELLAPI */
