/************************************************************************
*                                                                       *
*   commdlg.h -- This module defines the 32-Bit Common Dialog APIs      *
*                                                                       *
*   Copyright (c) 1992-1995, Microsoft Corp. All rights reserved.       *
*                                                                       *
************************************************************************/
#ifndef _INC_COMMDLG
#define _INC_COMMDLG

#include <pshpack1.h>         /* Assume byte packing throughout */

#ifdef __cplusplus
extern "C" {            /* Assume C declarations for C++ */
#endif  /* __cplusplus */

#if(WINVER >= 0x0400)
#ifdef __cplusplus

#ifndef SNDMSG
#ifndef UNDER_CE
#define SNDMSG ::SendMessage
#else  // UNDER_CE
#define SNDMSG SendMessage
#endif // !UNDER_CE
#endif // !SNDMSG

#else   // __cplusplus

#ifndef SNDMSG
#define SNDMSG SendMessage
#endif

#endif // __cplusplus 
#endif // WINVER >= 0x0400 

typedef UINT (APIENTRY *LPOFNHOOKPROC) (HWND, UINT, WPARAM, LPARAM);

/**
 * This structure contains information the operating system uses to initialize the system-defined
 * Open or Save As dialog box. After the user closes the dialog box, the system returns information
 * about the user's selection in this structure.
 */
typedef struct tagOFNA {
   /**
    * Specifies the length, in bytes, of the structure.
    */
   DWORD        lStructSize;
   /**
    * Handle to the window that owns the dialog box. This member can be any valid window handle, or it
    * can be NULL if the dialog box has no owner.
    */
   HWND         hwndOwner;
   /**
    * Not supported.
    */
   HINSTANCE    hInstance;
   /**
    * Long pointer to a buffer that contains pairs of null-terminated filter strings. The last string
    * in the buffer must be terminated by two NULL characters.
    *
    * The first string in each pair is a display string that describes the filter (for example, "Text
    * Files"), and the second string specifies the filter pattern (for example, "*.TXT"). To specify
    * multiple filter patterns for a single display string, use a semicolon to separate the patterns
    * (for example, "*.TXT;*.DOC;*.BAK"). A pattern string can be a combination of valid file name
    * characters and the asterisk (*) wildcard character. Do not include spaces in the pattern string.
    *
    * The system does not change the order of the filters. It displays them in the File Types combo box
    * in the order specified in lpstrFilter.
    *
    * If lpstrFilter is NULL, the dialog box does not display any filters.
    */
   LPCSTR       lpstrFilter;
   /**
    * Not supported.
    */
   LPSTR        lpstrCustomFilter;
   /**
    * Not supported.
    */
   DWORD        nMaxCustFilter;
   /**
    * Specifies the index of the currently selected filter in the File Types control. The buffer
    * pointed to by lpstrFilter contains pairs of strings that define the filters. The first pair of
    * strings has an index value of 1, the second pair 2, and so on. You can specify an index on input
    * to indicate the initial filter description and filter pattern for the dialog box. When the user
    * selects a file, nFilterIndex returns the index of the currently displayed filter.
    *
    * If nFilterIndex is zero, the system uses the first filter in the lpstrFilter buffer.
    */
   DWORD        nFilterIndex;
   /**
    * Long pointer to a buffer that contains a file name used to initialize the File Name edit control.
    * The first character of this buffer must be NULL if initialization is not necessary. When the
    * GetOpenFileName or GetSaveFileName function returns successfully, this buffer contains the drive
    * designator, path, file name, and extension of the selected file.
    *
    * If the buffer is too small, the function returns FALSE. In this case, the first two bytes of the
    * lpstrFile buffer contain the required size, in bytes or characters.
    */
   LPSTR        lpstrFile;
   /**
    * Specifies the size, in bytes (ANSI version) or 16-bit characters (Unicode version), of the buffer
    * pointed to by lpstrFile. The GetOpenFileName and GetSaveFileName functions return FALSE if the
    * buffer is too small to contain the file information. The buffer should be at least 256 characters
    * long.
    */
   DWORD        nMaxFile;
   /**
    * Long pointer to a buffer that receives the file name and extension (without path information) of
    * the selected file. This member can be NULL.
    */
   LPSTR        lpstrFileTitle;
   /**
    * Specifies the size, in bytes (ANSI version) or 16-bit characters (Unicode version), of the buffer
    * pointed to by lpstrFileTitle. This member is ignored if lpstrFileTitle is NULL.
    */
   DWORD        nMaxFileTitle;
   /**
    * Long pointer to a string that specifies the initial file directory. If this member is NULL, the
    * system uses the root directory.
    */
   LPCSTR       lpstrInitialDir;
   /**
    * Long pointer to a string to be placed in the title bar of the dialog box. If this member is NULL,
    * the system uses the default title (that is, Save As or Open).
    */
   LPCSTR       lpstrTitle;
   /**
    * A bitmask of flags used to initialize the dialog box. When the dialog box returns, it sets these
    * flags to indicate the user's input. This member can be a combination of the following flags:
    *
    * - OFN_ALLOWMULTISELECT: Not supported.
    *
    * - OFN_CREATEPROMPT: If the user specifies a file that does not exist, this flag causes the dialog
    * box to prompt the user for permission to create the file. If the user chooses to create the file,
    * the dialog box closes and the function returns the specified name; otherwise, the dialog box
    * remains open.
    *
    * - OFN_ENABLEHOOK: Not supported.
    *
    * - OFN_ENABLESIZING: Not supported.
    *
    * - OFN_ENABLETEMPLATE: Not supported.
    *
    * - OFN_ENABLETEMPLATEHANDLE: Not supported.
    *
    * - OFN_EXPLORER: Ignored. The Explorer user interface is always used.
    *
    * - OFN_EXTENSIONDIFFERENT: Specifies that the user typed a file name extension that differs from
    * the extension specified by lpstrDefExt. The function does not use this flag if lpstrDefExt is
    * NULL.
    *
    * - OFN_FILEMUSTEXIST: Specifies that the user can type only names of existing files in the File
    * Name entry field. If this flag is specified and the user enters an invalid name, the dialog box
    * procedure displays a warning in a message box. If this flag is specified, the OFN_PATHMUSTEXIST
    * flag is also used.
    *
    * - OFN_HIDEREADONLY: Not supported.
    *
    * - OFN_LONGNAMES: Ignored. The Explorer user interface is always used.
    *
    * - OFN_NOCHANGEDIR: Not supported.
    *
    * - OFN_NODEREFERENCELINKS: Directs the dialog box to return the path and file name of the selected
    * shortcut (.LNK) file. If this value is not given, the dialog box returns the path and file name
    * of the file referenced by the shortcut
    *
    * - OFN_NOLONGNAMES: Not supported.
    *
    * - OFN_NONETWORKBUTTON: Not supported.
    *
    * - OFN_NOREADONLYRETURN: Not supported.
    *
    * - OFN_NOTESTFILECREATE: Not supported.
    *
    * - OFN_NOVALIDATE: Ignored. A file name is always validated.
    *
    * - OFN_OVERWRITEPROMPT: Causes the Save As dialog box to generate a message box if the selected
    * file already exists. The user must confirm whether to overwrite the file.
    *
    * - OFN_PATHMUSTEXIST: Specifies that the user can type only valid paths and file names. If this
    * flag is used and the user types an invalid path and file name in the File Name entry field, the
    * dialog box function displays a warning in a message box.
    *
    * - OFN_READONLY: Not supported.
    *
    * - OFN_SHAREAWARE: Not supported.
    *
    * - OFN_SHOWHELP: Not supported.
    */
   DWORD        Flags;
   /**
    * Specifies the zero-based offset, in bytes (ANSI version) or 16-bit characters (Unicode version),
    * from the beginning of the path to the file name in the string pointed to by lpstrFile. For
    * example, if lpstrFile points to the following string, "c:\dir1\dir2\file.ext", this member
    * contains the value 13 to indicate the offset of the "file.ext" string.
    */
   WORD         nFileOffset;
   /**
    * Specifies the zero-based offset, in bytes (ANSI version) or 16-bit characters (Unicode version),
    * from the beginning of the path to the file name extension in the string pointed to by lpstrFile.
    * For example, if lpstrFile points to the following string, "c:\dir1\dir2\file.ext", this member
    * contains the value 18. If the user did not type an extension and lpstrDefExt is NULL, this member
    * specifies an offset to the terminating null character. If the user typed "." as the last
    * character in the file name, this member specifies zero.
    */
   WORD         nFileExtension;
   /**
    * Long pointer to a buffer that contains the default extension. GetOpenFileName and GetSaveFileName
    * append this extension to the file name if the user fails to type an extension. This string can be
    * any length, but only the first three characters are appended. The string should not contain a
    * period (.). If this member is NULL and the user fails to type an extension, no extension is
    * appended.
    */
   LPCSTR       lpstrDefExt;
   /**
    * Not supported.
    */
   LPARAM       lCustData;
   /**
    * Not supported.
    */
   LPOFNHOOKPROC lpfnHook;
   /**
    * Not supported.
    */
   LPCSTR       lpTemplateName;
} OPENFILENAMEA, *LPOPENFILENAMEA;
/**
 * This structure contains information the operating system uses to initialize the system-defined
 * Open or Save As dialog box. After the user closes the dialog box, the system returns information
 * about the user's selection in this structure.
 */
typedef struct tagOFNW {
   /**
    * Specifies the length, in bytes, of the structure.
    */
   DWORD        lStructSize;
   /**
    * Handle to the window that owns the dialog box. This member can be any valid window handle, or it
    * can be NULL if the dialog box has no owner.
    */
   HWND         hwndOwner;
   /**
    * Not supported.
    */
   HINSTANCE    hInstance;
   /**
    * Long pointer to a buffer that contains pairs of null-terminated filter strings. The last string
    * in the buffer must be terminated by two NULL characters.
    *
    * The first string in each pair is a display string that describes the filter (for example, "Text
    * Files"), and the second string specifies the filter pattern (for example, "*.TXT"). To specify
    * multiple filter patterns for a single display string, use a semicolon to separate the patterns
    * (for example, "*.TXT;*.DOC;*.BAK"). A pattern string can be a combination of valid file name
    * characters and the asterisk (*) wildcard character. Do not include spaces in the pattern string.
    *
    * The system does not change the order of the filters. It displays them in the File Types combo box
    * in the order specified in lpstrFilter.
    *
    * If lpstrFilter is NULL, the dialog box does not display any filters.
    */
   LPCWSTR      lpstrFilter;
   /**
    * Not supported.
    */
   LPWSTR       lpstrCustomFilter;
   /**
    * Not supported.
    */
   DWORD        nMaxCustFilter;
   /**
    * Specifies the index of the currently selected filter in the File Types control. The buffer
    * pointed to by lpstrFilter contains pairs of strings that define the filters. The first pair of
    * strings has an index value of 1, the second pair 2, and so on. You can specify an index on input
    * to indicate the initial filter description and filter pattern for the dialog box. When the user
    * selects a file, nFilterIndex returns the index of the currently displayed filter.
    *
    * If nFilterIndex is zero, the system uses the first filter in the lpstrFilter buffer.
    */
   DWORD        nFilterIndex;
   /**
    * Long pointer to a buffer that contains a file name used to initialize the File Name edit control.
    * The first character of this buffer must be NULL if initialization is not necessary. When the
    * GetOpenFileName or GetSaveFileName function returns successfully, this buffer contains the drive
    * designator, path, file name, and extension of the selected file.
    *
    * If the buffer is too small, the function returns FALSE. In this case, the first two bytes of the
    * lpstrFile buffer contain the required size, in bytes or characters.
    */
   LPWSTR       lpstrFile;
   /**
    * Specifies the size, in bytes (ANSI version) or 16-bit characters (Unicode version), of the buffer
    * pointed to by lpstrFile. The GetOpenFileName and GetSaveFileName functions return FALSE if the
    * buffer is too small to contain the file information. The buffer should be at least 256 characters
    * long.
    */
   DWORD        nMaxFile;
   /**
    * Long pointer to a buffer that receives the file name and extension (without path information) of
    * the selected file. This member can be NULL.
    */
   LPWSTR       lpstrFileTitle;
   /**
    * Specifies the size, in bytes (ANSI version) or 16-bit characters (Unicode version), of the buffer
    * pointed to by lpstrFileTitle. This member is ignored if lpstrFileTitle is NULL.
    */
   DWORD        nMaxFileTitle;
   /**
    * Long pointer to a string that specifies the initial file directory. If this member is NULL, the
    * system uses the root directory.
    */
   LPCWSTR      lpstrInitialDir;
   /**
    * Long pointer to a string to be placed in the title bar of the dialog box. If this member is NULL,
    * the system uses the default title (that is, Save As or Open).
    */
   LPCWSTR      lpstrTitle;
   /**
    * A bitmask of flags used to initialize the dialog box. When the dialog box returns, it sets these
    * flags to indicate the user's input. This member can be a combination of the following flags:
    *
    * - OFN_ALLOWMULTISELECT: Not supported.
    *
    * - OFN_CREATEPROMPT: If the user specifies a file that does not exist, this flag causes the dialog
    * box to prompt the user for permission to create the file. If the user chooses to create the file,
    * the dialog box closes and the function returns the specified name; otherwise, the dialog box
    * remains open.
    *
    * - OFN_ENABLEHOOK: Not supported.
    *
    * - OFN_ENABLESIZING: Not supported.
    *
    * - OFN_ENABLETEMPLATE: Not supported.
    *
    * - OFN_ENABLETEMPLATEHANDLE: Not supported.
    *
    * - OFN_EXPLORER: Ignored. The Explorer user interface is always used.
    *
    * - OFN_EXTENSIONDIFFERENT: Specifies that the user typed a file name extension that differs from
    * the extension specified by lpstrDefExt. The function does not use this flag if lpstrDefExt is
    * NULL.
    *
    * - OFN_FILEMUSTEXIST: Specifies that the user can type only names of existing files in the File
    * Name entry field. If this flag is specified and the user enters an invalid name, the dialog box
    * procedure displays a warning in a message box. If this flag is specified, the OFN_PATHMUSTEXIST
    * flag is also used.
    *
    * - OFN_HIDEREADONLY: Not supported.
    *
    * - OFN_LONGNAMES: Ignored. The Explorer user interface is always used.
    *
    * - OFN_NOCHANGEDIR: Not supported.
    *
    * - OFN_NODEREFERENCELINKS: Directs the dialog box to return the path and file name of the selected
    * shortcut (.LNK) file. If this value is not given, the dialog box returns the path and file name
    * of the file referenced by the shortcut
    *
    * - OFN_NOLONGNAMES: Not supported.
    *
    * - OFN_NONETWORKBUTTON: Not supported.
    *
    * - OFN_NOREADONLYRETURN: Not supported.
    *
    * - OFN_NOTESTFILECREATE: Not supported.
    *
    * - OFN_NOVALIDATE: Ignored. A file name is always validated.
    *
    * - OFN_OVERWRITEPROMPT: Causes the Save As dialog box to generate a message box if the selected
    * file already exists. The user must confirm whether to overwrite the file.
    *
    * - OFN_PATHMUSTEXIST: Specifies that the user can type only valid paths and file names. If this
    * flag is used and the user types an invalid path and file name in the File Name entry field, the
    * dialog box function displays a warning in a message box.
    *
    * - OFN_READONLY: Not supported.
    *
    * - OFN_SHAREAWARE: Not supported.
    *
    * - OFN_SHOWHELP: Not supported.
    */
   DWORD        Flags;
   /**
    * Specifies the zero-based offset, in bytes (ANSI version) or 16-bit characters (Unicode version),
    * from the beginning of the path to the file name in the string pointed to by lpstrFile. For
    * example, if lpstrFile points to the following string, "c:\dir1\dir2\file.ext", this member
    * contains the value 13 to indicate the offset of the "file.ext" string.
    */
   WORD         nFileOffset;
   /**
    * Specifies the zero-based offset, in bytes (ANSI version) or 16-bit characters (Unicode version),
    * from the beginning of the path to the file name extension in the string pointed to by lpstrFile.
    * For example, if lpstrFile points to the following string, "c:\dir1\dir2\file.ext", this member
    * contains the value 18. If the user did not type an extension and lpstrDefExt is NULL, this member
    * specifies an offset to the terminating null character. If the user typed "." as the last
    * character in the file name, this member specifies zero.
    */
   WORD         nFileExtension;
   /**
    * Long pointer to a buffer that contains the default extension. GetOpenFileName and GetSaveFileName
    * append this extension to the file name if the user fails to type an extension. This string can be
    * any length, but only the first three characters are appended. The string should not contain a
    * period (.). If this member is NULL and the user fails to type an extension, no extension is
    * appended.
    */
   LPCWSTR      lpstrDefExt;
   /**
    * Not supported.
    */
   LPARAM       lCustData;
   /**
    * Not supported.
    */
   LPOFNHOOKPROC lpfnHook;
   /**
    * Not supported.
    */
   LPCWSTR      lpTemplateName;
} OPENFILENAMEW, *LPOPENFILENAMEW;
#ifdef UNICODE
typedef OPENFILENAMEW OPENFILENAME;
typedef LPOPENFILENAMEW LPOPENFILENAME;
#else
typedef OPENFILENAMEA OPENFILENAME;
typedef LPOPENFILENAMEA LPOPENFILENAME;
#endif // UNICODE

/**
 * This function creates a system-defined dialog box that enables the user to select a file to open.
 *
 * @param lpofn [in] Long pointer to an OPENFILENAME structure that contains information used to
 *   initialize the dialog box. When GetOpenFileName returns, this structure contains information
 *   about the user's file selection.
 *
 * @return Nonzero indicates that the user specified a file name and clicked the OK button. The
 *   buffer pointed to by the lpstrFile member of the OPENFILENAME structure contains the full path
 *   and filename specified by the user. Zero indicates that the user canceled or closed the Open
 *   dialog box or that an error occurred. To get extended error information, call GetLastError.
 *   GetOpenFileName sets only the ERROR_INVALID_PARAMETER and ERROR_OUTOFMEMORY errors.
 *
 * Not all members of the OPENFILENAME structure are defined in Windows CE. For information about
 * the defined members, see the reference topic for the OPENFILENAME structure.
 *
 * On a Palm-size PC, Windows CE modifies the meaning of the following members of the OPENFILENAME
 * structure when it is passed into the GetOpenFileName function.
 *
 * - Flags: If this member is set to the OFN_PROJECT value, the GetOpenFileName function opens the
 * Folder dialog box. Otherwise, the function opens the Open dialog box.
 *
 * - lpstrFile: When GetOpenFileName returns successfully, this member is used to retrieve full path
 * of the selected file name.
 *
 * - lpstrFileTitle: When GetOpenFileName returns successfully, this member is used to retrieve the
 * the project folder name only.
 *
 * - lpstrInitialDir: Pointer to a string that receives the initial folder name, but not the full
 * path name.
 *
 * When the GetOpenFileName function is called on a Palm-size PC, Windows CE adds the following
 * prespecified undefined members:
 *
 * lpstrCustomFilter
 *
 * lpstrMaxCusFilter
 *
 * lpstrDefExtension
 *
 * lCustData
 *
 * lpfnHook
 *
 * lpstrTemplateName
 */
BOOL  APIENTRY     GetOpenFileNameA(LPOPENFILENAMEA);
/**
 * This function creates a system-defined dialog box that enables the user to select a file to open.
 *
 * @param lpofn [in] Long pointer to an OPENFILENAME structure that contains information used to
 *   initialize the dialog box. When GetOpenFileName returns, this structure contains information
 *   about the user's file selection.
 *
 * @return Nonzero indicates that the user specified a file name and clicked the OK button. The
 *   buffer pointed to by the lpstrFile member of the OPENFILENAME structure contains the full path
 *   and filename specified by the user. Zero indicates that the user canceled or closed the Open
 *   dialog box or that an error occurred. To get extended error information, call GetLastError.
 *   GetOpenFileName sets only the ERROR_INVALID_PARAMETER and ERROR_OUTOFMEMORY errors.
 *
 * Not all members of the OPENFILENAME structure are defined in Windows CE. For information about
 * the defined members, see the reference topic for the OPENFILENAME structure.
 *
 * On a Palm-size PC, Windows CE modifies the meaning of the following members of the OPENFILENAME
 * structure when it is passed into the GetOpenFileName function.
 *
 * - Flags: If this member is set to the OFN_PROJECT value, the GetOpenFileName function opens the
 * Folder dialog box. Otherwise, the function opens the Open dialog box.
 *
 * - lpstrFile: When GetOpenFileName returns successfully, this member is used to retrieve full path
 * of the selected file name.
 *
 * - lpstrFileTitle: When GetOpenFileName returns successfully, this member is used to retrieve the
 * the project folder name only.
 *
 * - lpstrInitialDir: Pointer to a string that receives the initial folder name, but not the full
 * path name.
 *
 * When the GetOpenFileName function is called on a Palm-size PC, Windows CE adds the following
 * prespecified undefined members:
 *
 * lpstrCustomFilter
 *
 * lpstrMaxCusFilter
 *
 * lpstrDefExtension
 *
 * lCustData
 *
 * lpfnHook
 *
 * lpstrTemplateName
 */
BOOL APIENTRY 	 GetOpenFileNameW ( LPOPENFILENAMEW );
/**
 * This function creates a system-defined dialog box that enables the user to select a file to save.
 *
 * @param lpofn [in] Long pointer to an OPENFILENAME structure that contains information used to
 *   initialize the dialog box. When GetSaveFileName returns, this structure contains information
 *   about the user's file selection.
 *
 * @return Nonzero indicates that the user specified a file name and clicked the OK button. The
 *   buffer pointed to by the lpstrFile member of the OPENFILENAME structure contains the full path
 *   and filename specified by the user. Zero indicates that the user canceled or closed the Save
 *   dialog box or that an error occurred. To get extended error information, call GetLastError.
 *   GetSaveFileName sets only the ERROR_INVALID_PARAMETER and ERROR_OUTOFMEMORY errors.
 *
 * Not all members of the OPENFILENAME structure are defined in Windows CE. For information about
 * the defined members, see the reference topic for the OPENFILENAME structure.
 *
 * On a Palm-size PC, Windows CE modifies the meaning of the following members of the OPENFILENAME
 * structure when it is passed into the GetOpenFileName function.
 *
 * - Flags: If this member is set to the OFN_PROJECT value, the GetOpenFileName function opens the
 * Folder dialog box. Otherwise, the function opens the Open dialog box.
 *
 * - lpstrFile: When GetOpenFileName returns successfully, this member is used to retrieve full path
 * of the selected file name.
 *
 * - lpstrFileTitle: When GetOpenFileName returns successfully, this member is used to retrieve the
 * the project folder name only.
 *
 * - lpstrInitialDir: Pointer to a string that receives the initial folder name, but not the full
 * path name.
 *
 * When the GetOpenFileName function is called on a Palm-size PC, Windows CE adds the following
 * prespecified undefined members:
 *
 * lpstrCustomFilter
 *
 * lpstrMaxCusFilter
 *
 * lpstrDefExtension
 *
 * lCustData
 *
 * lpfnHook
 *
 * lpstrTemplateName
 */
BOOL  APIENTRY     GetSaveFileNameW(LPOPENFILENAMEW);
/**
 * This function creates a system-defined dialog box that enables the user to select a file to save.
 *
 * @param lpofn [in] Long pointer to an OPENFILENAME structure that contains information used to
 *   initialize the dialog box. When GetSaveFileName returns, this structure contains information
 *   about the user's file selection.
 *
 * @return Nonzero indicates that the user specified a file name and clicked the OK button. The
 *   buffer pointed to by the lpstrFile member of the OPENFILENAME structure contains the full path
 *   and filename specified by the user. Zero indicates that the user canceled or closed the Save
 *   dialog box or that an error occurred. To get extended error information, call GetLastError.
 *   GetSaveFileName sets only the ERROR_INVALID_PARAMETER and ERROR_OUTOFMEMORY errors.
 *
 * Not all members of the OPENFILENAME structure are defined in Windows CE. For information about
 * the defined members, see the reference topic for the OPENFILENAME structure.
 *
 * On a Palm-size PC, Windows CE modifies the meaning of the following members of the OPENFILENAME
 * structure when it is passed into the GetOpenFileName function.
 *
 * - Flags: If this member is set to the OFN_PROJECT value, the GetOpenFileName function opens the
 * Folder dialog box. Otherwise, the function opens the Open dialog box.
 *
 * - lpstrFile: When GetOpenFileName returns successfully, this member is used to retrieve full path
 * of the selected file name.
 *
 * - lpstrFileTitle: When GetOpenFileName returns successfully, this member is used to retrieve the
 * the project folder name only.
 *
 * - lpstrInitialDir: Pointer to a string that receives the initial folder name, but not the full
 * path name.
 *
 * When the GetOpenFileName function is called on a Palm-size PC, Windows CE adds the following
 * prespecified undefined members:
 *
 * lpstrCustomFilter
 *
 * lpstrMaxCusFilter
 *
 * lpstrDefExtension
 *
 * lCustData
 *
 * lpfnHook
 *
 * lpstrTemplateName
 */
BOOL  APIENTRY     GetSaveFileNameA(LPOPENFILENAMEA);
#ifdef UNICODE
/**
 * This function creates a system-defined dialog box that enables the user to select a file to open.
 *
 * @param lpofn [in] Long pointer to an OPENFILENAME structure that contains information used to
 *   initialize the dialog box. When GetOpenFileName returns, this structure contains information
 *   about the user's file selection.
 *
 * @return Nonzero indicates that the user specified a file name and clicked the OK button. The
 *   buffer pointed to by the lpstrFile member of the OPENFILENAME structure contains the full path
 *   and filename specified by the user. Zero indicates that the user canceled or closed the Open
 *   dialog box or that an error occurred. To get extended error information, call GetLastError.
 *   GetOpenFileName sets only the ERROR_INVALID_PARAMETER and ERROR_OUTOFMEMORY errors.
 *
 * Not all members of the OPENFILENAME structure are defined in Windows CE. For information about
 * the defined members, see the reference topic for the OPENFILENAME structure.
 *
 * On a Palm-size PC, Windows CE modifies the meaning of the following members of the OPENFILENAME
 * structure when it is passed into the GetOpenFileName function.
 *
 * - Flags: If this member is set to the OFN_PROJECT value, the GetOpenFileName function opens the
 * Folder dialog box. Otherwise, the function opens the Open dialog box.
 *
 * - lpstrFile: When GetOpenFileName returns successfully, this member is used to retrieve full path
 * of the selected file name.
 *
 * - lpstrFileTitle: When GetOpenFileName returns successfully, this member is used to retrieve the
 * the project folder name only.
 *
 * - lpstrInitialDir: Pointer to a string that receives the initial folder name, but not the full
 * path name.
 *
 * When the GetOpenFileName function is called on a Palm-size PC, Windows CE adds the following
 * prespecified undefined members:
 *
 * lpstrCustomFilter
 *
 * lpstrMaxCusFilter
 *
 * lpstrDefExtension
 *
 * lCustData
 *
 * lpfnHook
 *
 * lpstrTemplateName
 */
#define GetOpenFileName  GetOpenFileNameW
/**
 * This function creates a system-defined dialog box that enables the user to select a file to save.
 *
 * @param lpofn [in] Long pointer to an OPENFILENAME structure that contains information used to
 *   initialize the dialog box. When GetSaveFileName returns, this structure contains information
 *   about the user's file selection.
 *
 * @return Nonzero indicates that the user specified a file name and clicked the OK button. The
 *   buffer pointed to by the lpstrFile member of the OPENFILENAME structure contains the full path
 *   and filename specified by the user. Zero indicates that the user canceled or closed the Save
 *   dialog box or that an error occurred. To get extended error information, call GetLastError.
 *   GetSaveFileName sets only the ERROR_INVALID_PARAMETER and ERROR_OUTOFMEMORY errors.
 *
 * Not all members of the OPENFILENAME structure are defined in Windows CE. For information about
 * the defined members, see the reference topic for the OPENFILENAME structure.
 *
 * On a Palm-size PC, Windows CE modifies the meaning of the following members of the OPENFILENAME
 * structure when it is passed into the GetOpenFileName function.
 *
 * - Flags: If this member is set to the OFN_PROJECT value, the GetOpenFileName function opens the
 * Folder dialog box. Otherwise, the function opens the Open dialog box.
 *
 * - lpstrFile: When GetOpenFileName returns successfully, this member is used to retrieve full path
 * of the selected file name.
 *
 * - lpstrFileTitle: When GetOpenFileName returns successfully, this member is used to retrieve the
 * the project folder name only.
 *
 * - lpstrInitialDir: Pointer to a string that receives the initial folder name, but not the full
 * path name.
 *
 * When the GetOpenFileName function is called on a Palm-size PC, Windows CE adds the following
 * prespecified undefined members:
 *
 * lpstrCustomFilter
 *
 * lpstrMaxCusFilter
 *
 * lpstrDefExtension
 *
 * lCustData
 *
 * lpfnHook
 *
 * lpstrTemplateName
 */
#define GetSaveFileName  GetSaveFileNameW
#else
/**
 * This function creates a system-defined dialog box that enables the user to select a file to save.
 *
 * @param lpofn [in] Long pointer to an OPENFILENAME structure that contains information used to
 *   initialize the dialog box. When GetSaveFileName returns, this structure contains information
 *   about the user's file selection.
 *
 * @return Nonzero indicates that the user specified a file name and clicked the OK button. The
 *   buffer pointed to by the lpstrFile member of the OPENFILENAME structure contains the full path
 *   and filename specified by the user. Zero indicates that the user canceled or closed the Save
 *   dialog box or that an error occurred. To get extended error information, call GetLastError.
 *   GetSaveFileName sets only the ERROR_INVALID_PARAMETER and ERROR_OUTOFMEMORY errors.
 *
 * Not all members of the OPENFILENAME structure are defined in Windows CE. For information about
 * the defined members, see the reference topic for the OPENFILENAME structure.
 *
 * On a Palm-size PC, Windows CE modifies the meaning of the following members of the OPENFILENAME
 * structure when it is passed into the GetOpenFileName function.
 *
 * - Flags: If this member is set to the OFN_PROJECT value, the GetOpenFileName function opens the
 * Folder dialog box. Otherwise, the function opens the Open dialog box.
 *
 * - lpstrFile: When GetOpenFileName returns successfully, this member is used to retrieve full path
 * of the selected file name.
 *
 * - lpstrFileTitle: When GetOpenFileName returns successfully, this member is used to retrieve the
 * the project folder name only.
 *
 * - lpstrInitialDir: Pointer to a string that receives the initial folder name, but not the full
 * path name.
 *
 * When the GetOpenFileName function is called on a Palm-size PC, Windows CE adds the following
 * prespecified undefined members:
 *
 * lpstrCustomFilter
 *
 * lpstrMaxCusFilter
 *
 * lpstrDefExtension
 *
 * lCustData
 *
 * lpfnHook
 *
 * lpstrTemplateName
 */
#define GetSaveFileName  GetSaveFileNameA
/**
 * This function creates a system-defined dialog box that enables the user to select a file to open.
 *
 * @param lpofn [in] Long pointer to an OPENFILENAME structure that contains information used to
 *   initialize the dialog box. When GetOpenFileName returns, this structure contains information
 *   about the user's file selection.
 *
 * @return Nonzero indicates that the user specified a file name and clicked the OK button. The
 *   buffer pointed to by the lpstrFile member of the OPENFILENAME structure contains the full path
 *   and filename specified by the user. Zero indicates that the user canceled or closed the Open
 *   dialog box or that an error occurred. To get extended error information, call GetLastError.
 *   GetOpenFileName sets only the ERROR_INVALID_PARAMETER and ERROR_OUTOFMEMORY errors.
 *
 * Not all members of the OPENFILENAME structure are defined in Windows CE. For information about
 * the defined members, see the reference topic for the OPENFILENAME structure.
 *
 * On a Palm-size PC, Windows CE modifies the meaning of the following members of the OPENFILENAME
 * structure when it is passed into the GetOpenFileName function.
 *
 * - Flags: If this member is set to the OFN_PROJECT value, the GetOpenFileName function opens the
 * Folder dialog box. Otherwise, the function opens the Open dialog box.
 *
 * - lpstrFile: When GetOpenFileName returns successfully, this member is used to retrieve full path
 * of the selected file name.
 *
 * - lpstrFileTitle: When GetOpenFileName returns successfully, this member is used to retrieve the
 * the project folder name only.
 *
 * - lpstrInitialDir: Pointer to a string that receives the initial folder name, but not the full
 * path name.
 *
 * When the GetOpenFileName function is called on a Palm-size PC, Windows CE adds the following
 * prespecified undefined members:
 *
 * lpstrCustomFilter
 *
 * lpstrMaxCusFilter
 *
 * lpstrDefExtension
 *
 * lCustData
 *
 * lpfnHook
 *
 * lpstrTemplateName
 */
#define GetOpenFileName  GetOpenFileNameA
#endif // !UNICODE

#define OFN_OVERWRITEPROMPT          0x00000002
#define OFN_HIDEREADONLY             0x00000004
#define OFN_NOCHANGEDIR              0x00000008
#define OFN_SHOWHELP                 0x00000010
#define OFN_EXTENSIONDIFFERENT       0x00000400
#define OFN_PATHMUSTEXIST            0x00000800
#define OFN_FILEMUSTEXIST            0x00001000
#define OFN_CREATEPROMPT             0x00002000
#define OFN_NOTESTFILECREATE         0x00010000
#define OFN_NONETWORKBUTTON          0x00020000
#define OFN_NOLONGNAMES              0x00040000     // force no long names for 4.x modules
#if(WINVER >= 0x0400)
#define OFN_EXPLORER                 0x00080000     // new look commdlg
#define OFN_NODEREFERENCELINKS       0x00100000
#define OFN_LONGNAMES                0x00200000     // force long names for 3.x modules
#endif /* WINVER >= 0x0400 */
#define OFN_PROJECT					 0x00400000     // If this flag is set, the GetOpenFileName API will open the Project dialog for Gryphon
#define OFN_PROPERTY				 0x00800000     // If this flag is set, the GetSaveFileName API will open the Propery dialog for Gryphon
#define OFN_SHOW_ALL                 0x01000000     // If OFN_PROJECT is set,  show the <All Folders> item

// Return values for the registered message sent to the hook function
// when a sharing violation occurs.  OFN_SHAREFALLTHROUGH allows the
// filename to be accepted, OFN_SHARENOWARN rejects the name but puts
// up no warning (returned when the app has already put up a warning
// message), and OFN_SHAREWARN puts up the default warning message
// for sharing violations.
//
// Note:  Undefined return values map to OFN_SHAREWARN, but are
//        reserved for future use.

#define OFN_SHAREFALLTHROUGH     2
#define OFN_SHARENOWARN          1
#define OFN_SHAREWARN            0

typedef UINT (APIENTRY *LPCCHOOKPROC) (HWND, UINT, WPARAM, LPARAM);

#if(WINVER >= 0x0400)
// Structure used for all OpenFileName notifications
/**
 * This structure contains information about the WM_NOTIFY message sent to a hook procedure from an
 * Explorer-style Open or Save As dialog box. The address of the OFNOTIFY structure is passed as the
 * lParam parameter of the WM_NOTIFY message.
 */
typedef struct _OFNOTIFYW
{
        /**
         * NMHDR structure. The code member of the NMHDR structure can be one of the following notification
         * codes that identify the message being sent: CDN_FILEOK, CDN_FOLDERCHANGE, CDN_HELP, CDN_INITDONE,
         * CDN_SELCHANGE, CDN_SHAREVIOLATION, CDN_TYPECHANGE.
         */
        NMHDR           hdr;
        /**
         * Long pointer to the OPENFILENAME structure that was specified when the Open or Save As dialog box
         * was created. For some of the notification messages, this structure contains additional
         * information about the event that caused the notification.
         */
        LPOPENFILENAMEW lpOFN;
        /**
         * Pointer to the null-terminated string that contains the file name for which a network sharing
         * violation has occurred. This member is valid only with the CDN_SHAREVIOLATION notification
         * message.
         */
        LPWSTR          pszFile;        // May be NULL
} OFNOTIFYW, FAR *LPOFNOTIFYW;
/**
 * This structure contains information about the WM_NOTIFY message sent to a hook procedure from an
 * Explorer-style Open or Save As dialog box. The address of the OFNOTIFY structure is passed as the
 * lParam parameter of the WM_NOTIFY message.
 */
typedef struct _OFNOTIFYA
{
        /**
         * NMHDR structure. The code member of the NMHDR structure can be one of the following notification
         * codes that identify the message being sent: CDN_FILEOK, CDN_FOLDERCHANGE, CDN_HELP, CDN_INITDONE,
         * CDN_SELCHANGE, CDN_SHAREVIOLATION, CDN_TYPECHANGE.
         */
        NMHDR           hdr;
        /**
         * Long pointer to the OPENFILENAME structure that was specified when the Open or Save As dialog box
         * was created. For some of the notification messages, this structure contains additional
         * information about the event that caused the notification.
         */
        LPOPENFILENAMEA lpOFN;
        /**
         * Pointer to the null-terminated string that contains the file name for which a network sharing
         * violation has occurred. This member is valid only with the CDN_SHAREVIOLATION notification
         * message.
         */
        LPSTR           pszFile;        // May be NULL
} OFNOTIFYA, FAR *LPOFNOTIFYA;
#ifdef UNICODE
typedef OFNOTIFYW OFNOTIFY;
typedef LPOFNOTIFYW LPOFNOTIFY;
#else
typedef OFNOTIFYA OFNOTIFY;
typedef LPOFNOTIFYA LPOFNOTIFY;
#endif // UNICODE

#define CDN_FIRST   (0U-601U)
#define CDN_LAST    (0U-699U)

// Notifications when Open or Save dialog status changes
#define CDN_INITDONE            (CDN_FIRST - 0x0000)
#define CDN_SELCHANGE           (CDN_FIRST - 0x0001)
#define CDN_FOLDERCHANGE        (CDN_FIRST - 0x0002)
#define CDN_SHAREVIOLATION      (CDN_FIRST - 0x0003)
#define CDN_HELP                (CDN_FIRST - 0x0004)
#define CDN_FILEOK              (CDN_FIRST - 0x0005)
/**
 * This notification message is sent by an Explorer-style Open or Save As common dialog box when the
 * user selects a new file type from the file types combo box. Your OFNHookProc hook procedure
 * receives this message in the form of a WM_NOTIFY message.
 *
 * @param lpon Long pointer to an OFNOTIFY structure. The OFNOTIFY structure contains an NMHDR
 *   structure whose code member indicates the CDN_TYPECHANGE notification code. The OFNOTIFY
 *   structure also contains a pointer to an OPENFILENAME structure whose nFilterIndex member
 *   indicates the one-based index of the newly selected file type filter.
 *
 * @return The return value is ignored.
 *
 * The system sends this notification only if the dialog box was created using the OFN_EXPLORER
 * value.
 */
#define CDN_TYPECHANGE          (CDN_FIRST - 0x0006)

#define CDM_FIRST       (WM_USER + 100)
#define CDM_LAST        (WM_USER + 200)

// Messages to query information from the Open or Save dialogs

// lParam = pointer to text buffer that gets filled in
// wParam = max number of characters of the text buffer (including NULL)
// return = < 0 if error; number of characters needed (including NULL)
#define CDM_GETSPEC             (CDM_FIRST + 0x0000)
#define CommDlg_OpenSave_GetSpecA(_hdlg, _psz, _cbmax) \
        (int)SNDMSG(_hdlg, CDM_GETSPEC, (WPARAM)_cbmax, (LPARAM)(LPSTR)_psz)
#define CommDlg_OpenSave_GetSpecW(_hdlg, _psz, _cbmax) \
        (int)SNDMSG(_hdlg, CDM_GETSPEC, (WPARAM)_cbmax, (LPARAM)(LPWSTR)_psz)
#ifdef UNICODE
#define CommDlg_OpenSave_GetSpec  CommDlg_OpenSave_GetSpecW
#else
#define CommDlg_OpenSave_GetSpec  CommDlg_OpenSave_GetSpecA
#endif // !UNICODE

// lParam = pointer to text buffer that gets filled in
// wParam = max number of characters of the text buffer (including NULL)
// return = < 0 if error; number of characters needed (including NULL)
#define CDM_GETFILEPATH         (CDM_FIRST + 0x0001)
#define CommDlg_OpenSave_GetFilePathA(_hdlg, _psz, _cbmax) \
        (int)SNDMSG(_hdlg, CDM_GETFILEPATH, (WPARAM)_cbmax, (LPARAM)(LPSTR)_psz)
#define CommDlg_OpenSave_GetFilePathW(_hdlg, _psz, _cbmax) \
        (int)SNDMSG(_hdlg, CDM_GETFILEPATH, (WPARAM)_cbmax, (LPARAM)(LPWSTR)_psz)
#ifdef UNICODE
#define CommDlg_OpenSave_GetFilePath  CommDlg_OpenSave_GetFilePathW
#else
#define CommDlg_OpenSave_GetFilePath  CommDlg_OpenSave_GetFilePathA
#endif // !UNICODE

// lParam = pointer to text buffer that gets filled in
// wParam = max number of characters of the text buffer (including NULL)
// return = < 0 if error; number of characters needed (including NULL)
#define CDM_GETFOLDERPATH       (CDM_FIRST + 0x0002)
#define CommDlg_OpenSave_GetFolderPathA(_hdlg, _psz, _cbmax) \
        (int)SNDMSG(_hdlg, CDM_GETFOLDERPATH, (WPARAM)_cbmax, (LPARAM)(LPSTR)_psz)
#define CommDlg_OpenSave_GetFolderPathW(_hdlg, _psz, _cbmax) \
        (int)SNDMSG(_hdlg, CDM_GETFOLDERPATH, (WPARAM)_cbmax, (LPARAM)(LPWSTR)_psz)
#ifdef UNICODE
#define CommDlg_OpenSave_GetFolderPath  CommDlg_OpenSave_GetFolderPathW
#else
#define CommDlg_OpenSave_GetFolderPath  CommDlg_OpenSave_GetFolderPathA
#endif // !UNICODE

// lParam = pointer to ITEMIDLIST buffer that gets filled in
// wParam = size of the ITEMIDLIST buffer
// return = < 0 if error; length of buffer needed
#define CDM_GETFOLDERIDLIST     (CDM_FIRST + 0x0003)
#define CommDlg_OpenSave_GetFolderIDList(_hdlg, _pidl, _cbmax) \
        (int)SNDMSG(_hdlg, CDM_GETFOLDERIDLIST, (WPARAM)_cbmax, (LPARAM)(LPVOID)_pidl)

// lParam = pointer to a string
// wParam = ID of control to change
// return = not used
#define CDM_SETCONTROLTEXT      (CDM_FIRST + 0x0004)
#define CommDlg_OpenSave_SetControlText(_hdlg, _id, _text) \
        (void)SNDMSG(_hdlg, CDM_SETCONTROLTEXT, (WPARAM)_id, (LPARAM)(LPSTR)_text)

// lParam = not used
// wParam = ID of control to change
// return = not used
#define CDM_HIDECONTROL         (CDM_FIRST + 0x0005)
#define CommDlg_OpenSave_HideControl(_hdlg, _id) \
        (void)SNDMSG(_hdlg, CDM_HIDECONTROL, (WPARAM)_id, 0)

// lParam = pointer to default extension (no dot)
// wParam = not used
// return = not used
/**
 * This message sets the default filename extension for an Explorer-style Open or Save As common
 * dialog box. The dialog box must have been created with the OFN_EXPLORER flag; otherwise, the
 * message fails.
 *
 * @param hdlg Handle to the common dialog box window to receive the message.
 * @param pszext Pointer to the null-terminated string that contains the new file name extension.
 *   Must not include a period (.).
 *
 * @return None.
 */
#define CDM_SETDEFEXT           (CDM_FIRST + 0x0006)
#define CommDlg_OpenSave_SetDefExt(_hdlg, _pszext) \
        (void)SNDMSG(_hdlg, CDM_SETDEFEXT, 0, (LPARAM)(LPSTR)_pszext)
#endif /* WINVER >= 0x0400 */

#ifdef WINCEOEM
#ifdef WINCEMACRO
#include <mcommdlg.h>
#endif
#endif

typedef UINT (APIENTRY *LPCCHOOKPROC) (HWND, UINT, WPARAM, LPARAM);

/**
 * This structure contains information the ChooseColor function uses to initialize the Color common
 * dialog box. After a user closes the dialog box, the system uses this structure to return
 * information about the user's selection.
 */
typedef struct tagCHOOSECOLOR  {
   /**
    * Specifies the length, in bytes, of the structure.
    */
   DWORD        lStructSize;
   /**
    * Handle to the window that owns the dialog box. This member can be any valid window handle, or it
    * can be NULL if the dialog box has no owner.
    */
   HWND         hwndOwner;
   /**
    * If the CC_ENABLETEMPLATEHANDLE flag is set in the Flags member, this member is the handle of a
    * memory object that contains a dialog box template. If the CC_ENABLETEMPLATE flag is set,
    * hInstance identifies a module that contains a dialog box template named by the lpTemplateName
    * member. If neither CC_ENABLETEMPLATEHANDLE nor CC_ENABLETEMPLATE is set, this member is ignored.
    */
   HINSTANCE    hInstance;
   /**
    * If the CC_RGBINIT flag is set, this member specifies the color initially selected when the dialog
    * box is created. If the specified color value is not among the available colors, the system
    * selects the nearest solid color available. If rgbResult is zero or CC_RGBINIT is not set, the
    * initially selected color is black. If the user clicks the OK button, rgbResult specifies the
    * user's color selection.
    */
   COLORREF     rgbResult;
   /**
    * Long pointer to an array of 16 COLORREF values that contain red, green, blue (RGB) values for the
    * custom color boxes in the dialog box. If the user modifies these colors, the system updates the
    * array with the new RGB values. To preserve new custom colors between calls to the ChooseColor
    * function, you should allocate static memory for the array.
    */
   COLORREF*    lpCustColors;
   /**
    * Set of bit flags used to initialize the Color common dialog box. When the dialog box returns, it
    * sets these flags to indicate the user's input. This member can be a combination of the following
    * flags: Value Description CC_ANYCOLOR Causes the dialog box to display all available colors in the
    * set of basic colors. CC_ENABLEHOOK Enables the hook procedure specified in the lpfnHook member of
    * this structure. This flag is used only to initialize the dialog box. CC_ENABLETEMPLATE Indicates
    * that the hInstance and lpTemplateName members specify a dialog box template to use in place of
    * the default template. This flag is used only to initialize the dialog box.
    * CC_ENABLETEMPLATEHANDLE Indicates that the hInstance member identifies a data block that contains
    * a preloaded dialog box template. The system ignores the lpTemplateName member if this flag is
    * specified. This flag is used only to initialize the dialog box. CC_FULLOPEN Causes the dialog box
    * to display the additional controls that allow the user to create custom colors. If this flag is
    * not set, the user must click the Define Custom Color button to display the custom color controls.
    * CC_PREVENTFULLOPEN Disables the Define Custom Colors button. CC_RGBINIT Causes the dialog box to
    * use the color specified in the rgbResult member as the initial color selection. CC_SOLIDCOLOR
    * Causes the dialog box to display only solid colors in the set of basic colors.
    */
   DWORD        Flags;
   /**
    * Specifies application-defined data that the system passes to the hook procedure identified by the
    * lpfnHook member. When the system sends the WM_INITDIALOG message to the hook procedure, the
    * message's lParam parameter is a pointer to the CHOOSECOLOR structure specified when the dialog
    * was created. The hook procedure can use this pointer to get the lCustData value.
    */
   LPARAM       lCustData;
   /**
    * Long pointer to a CCHookProc hook procedure that can process messages intended for the dialog
    * box. This member is ignored unless the CC_ENABLEHOOK flag is set in the Flags member.
    */
   LPCCHOOKPROC lpfnHook;
   /**
    * Long pointer to a null-terminated string that names the dialog box template resource in the
    * module identified by the hInstance member. This template is substituted for the standard dialog
    * box template. For numbered dialog box resources, lpTemplateName can be a value returned by the
    * MAKEINTRESOURCE macro. This member is ignored unless the CC_ENABLETEMPLATE flag is set in the
    * Flags member.
    */
   LPCTSTR      lpTemplateName;
} CHOOSECOLOR , *LPCHOOSECOLOR ;

BOOL  APIENTRY ChooseColor (LPCHOOSECOLOR );

#define CC_RGBINIT               0x00000001
#define CC_FULLOPEN              0x00000002
#define CC_PREVENTFULLOPEN       0x00000004
#define CC_ENABLEHOOK            0x00000010
#define CC_ENABLETEMPLATE        0x00000020
#define CC_ENABLETEMPLATEHANDLE  0x00000040
#if(WINVER >= 0x0400)
#define CC_SOLIDCOLOR            0x00000080
#define CC_ANYCOLOR              0x00000100
#endif /* WINVER >= 0x0400 */

/**
 * This function returns a common dialog box error value. This value indicates the most recent error
 * to occur during the execution of one of the following common dialog box functions:
 *
 * @return If the most recent call to a common dialog box function succeeded, the return value is
 *   undefined. If the common dialog box function returned FALSE because the user closed or canceled
 *   the dialog box, the return value is zero. Otherwise, the return value is a nonzero error code.
 *   For more information, see the following Remarks section.
 *
 * The CommDlgExtendedError function can return general error codes for any of the common dialog box
 * functions. In addition, there are error codes that are returned only for a specific common dialog
 * box. The error codes returned by CommDlgExtendedError are defined in the CDERR.H file.
 *
 * The following general error codes can be returned for any of the common dialog box functions:
 *
 * - CDERR_DIALOGFAILURE: The dialog box could not be created. The common dialog box function's call
 * to the DialogBox function failed. For example, this error occurs if the common dialog box call
 * specifies an invalid window handle.
 *
 * - CDERR_FINDRESFAILURE: The common dialog box function failed to find a specified resource.
 *
 * - CDERR_INITIALIZATION: The common dialog box function failed during initialization. This error
 * often occurs when sufficient memory is not available.
 *
 * - CDERR_LOADRESFAILURE: The common dialog box function failed to load a specified resource.
 *
 * - CDERR_LOADSTRFAILURE: The common dialog box function failed to load a specified string.
 *
 * - CDERR_LOCKRESFAILURE: The common dialog box function failed to lock a specified resource.
 *
 * - CDERR_MEMALLOCFAILURE: The common dialog box function was unable to allocate memory for
 * internal structures.
 *
 * - CDERR_NOHINSTANCE: The ENABLETEMPLATE flag was set in the Flags member of the initialization
 * structure for the corresponding common dialog box, but you failed to provide a corresponding
 * instance handle.
 *
 * - CDERR_NOHOOK: The ENABLEHOOK flag was set in the Flags member of the initialization structure
 * for the corresponding common dialog box, but you failed to provide a pointer to a corresponding
 * hook procedure.
 *
 * - CDERR_NOTEMPLATE: The ENABLETEMPLATE flag was set in the Flags member of the initialization
 * structure for the corresponding common dialog box, but you failed to provide a corresponding
 * template.
 *
 * - CDERR_REGISTRYFAILURE: The common dialog box function was unable to read from registry.
 *
 * - CDERR_STRUCTSIZE: The lStructSize member of the initialization structure for the corresponding
 * common dialog box is invalid. The following error codes can be returned for the PrintDlg
 * function:
 *
 * - PDERR_CREATEDCFAILURE: The call to CreateDC failed.
 *
 * - PDERR_NOPORTS: No ports are registered.
 *
 * - PDERR_NOPRINTERS: No printers are registered.
 *
 * - PDERR_PARSEFAILURE: The PrintDlg function failed to parse the strings in the [devices] section
 * of the WIN.INI file.
 *
 * - PDERR_PRINTERNOTFOUND: The [devices] section of the WIN.INI file did not contain an entry for
 * the requested printer.
 *
 * - PDERR_RETDEFFAILURE: The PD_RETURNDEFAULT flag was specified in the Flags member of the
 * PRINTDLG structure, but the hDevMode or hDevNames member was not NULL.
 *
 * - PDERR_SETUPFAILURE: The PrintDlg function failed to load the required resources. The following
 * error codes can be returned for the GetOpenFileName and GetSaveFileName functions:
 *
 * - FNERR_BUFFERTOOSMALL: The buffer pointed to by the lpstrFile member of the OPENFILENAME
 * structure is too small for the filename specified by the user. The first two bytes of the
 * lpstrFile buffer contain an integer value specifying the size, in bytes (ANSI version) or 16-bit
 * characters (Unicode version), required to receive the full name.
 *
 * - FNERR_INVALIDFILENAME: A filename is invalid.
 *
 * - FNERR_SUBCLASSFAILURE: An attempt to subclass a list box failed because sufficient memory was
 * not available.
 */
DWORD APIENTRY     CommDlgExtendedError(VOID);

typedef UINT (APIENTRY *LPPRINTHOOKPROC) (HWND, UINT, WPARAM, LPARAM);

/**
 * This structure contains information the PrintDlg function uses to initialize the Print common
 * dialog box. After a user closes the dialog box, the system uses this structure to return
 * information about the user's print option selections.
 *
 * If the application does not specify the paper orientation, the Print dialog box reads the last
 * paper orientation the user selected, which it saved to the registry. If there is no value in the
 * registry, the dialog box selects portrait as the default. The dialog box also uses the last
 * printer, port, and paper size the user selected. If these values are not in the registry, the
 * dialog box selects the first printer, first port, and a paper size that is appropriate for the
 * regional setting as the defaults.
 */
typedef struct tagPD  {
   /**
    * Specifies the structure size, in bytes.
    */
   DWORD            cbStruct;
   /**
    * Handle to the window that owns the dialog box. This member can be any valid window handle, or it
    * can be NULL if the dialog box has no owner.
    */
   HWND             hwndOwner;
   /**
    * When PrintDlg returns, hdc contains the handle to the device context of the printer.
    */
   HDC              hdc;
   /**
    * Specifies a bitmask of flags used to initialize the Print common dialog box. When the dialog box
    * returns, it sets these flags to indicate the user's input. It can be a combination of the
    * following flags:
    *
    * - PD_SELECTALLPAGES: On input, this flag causes the All radio button to be selected when the
    * dialog is created. On output, it indicates that the user selected the All radio button.
    *
    * - PD_SELECTSELECTION: On input, this flag causes the Selection radio button to be in the selected
    * state when the dialog box is created. On output, it indicates that the user selected the
    * Selection radio button. If this flag is not specified, the All radio button is selected by
    * default.
    *
    * - PD_SELECTDRAFTMODE: Indicates the user selected the Draft mode check box.
    *
    * - PD_SELECTA4: Indicates the user selected "A4" size paper.
    *
    * - PD_SELECTLETTER: Indicates the user selected letter size paper.
    *
    * - PD_SELECTINFRARED: Indicates the user selected the infrared printer port.
    *
    * - PD_SELECTSERIAL: Indicates the user selected the serial printer port.
    *
    * - PD_DISABLEPAPERSIZE: Disables paper size selection.
    *
    * - PD_DISABLEPRINTRANGE: Disables print range selection.
    *
    * - PD_DISABLEMARGINS: Disables margin selection.
    *
    * - PD_DISABLEORIENTATION: Disables page orientation selection.
    *
    * - PD_RETURNDEFAULTDC: Returns the device context (DC) of the default printer without displaying
    * the dialog.
    *
    * - PD_ENABLEPRINTHOOK: Enables the hook procedure specified in the pfnPrintHook member. This
    * enables the hook procedure for the Print dialog box.
    *
    * - PD_ENABLEPRINTTEMPLATE: Indicates that the hinst and pszPrintTemplateName members specify a
    * dialog box template to use in place of the default template for the Print dialog box.
    *
    * - PD_ENABLEPRINTTEMPLATEHANDLE: Indicates that the hglbPrintTemplateResource member identifies a
    * data block that contains a preloaded dialog box template. The system uses this template in place
    * of the default template for the Print dialog box. The system ignores the pszPrintTemplateName
    * member if this flag is specified.
    *
    * - PD_SELECTPORTRAIT: On input, this flag specifies the Print dialog box should be initialized
    * with Portrait orientation selected as the default. On output, this flag indicates that the user
    * selected Portrait orientation.
    *
    * - PD_SELECTLANDSCAPE: On input, this flag specifies the Print dialog box should be initialized
    * with Landscape orientation selected as the default. On output, this flag indicates the user
    * selected Landscape orientation.
    *
    * - PD_MARGINS: On input, this flag specifies that the rcMargin member contains initial margin
    * values. On output, it indicates that the rcMargin member contains user-specified margin values.
    * If this flag is not specified, the Print dialog box uses the default margins, which are 1 inch
    * for the top and bottom margins and 1.25 inches for the left and right margins.
    *
    * - PD_INTHOUSANDTHSOFINCHES: Indicates the unit of measure in which margins are specified. If
    * neither this flag nor the PD_INHUNDREDTHSOFMILLIMETERS flag is specified, the Print dialog box
    * uses the LOCALE_IMEASURE setting in the locale table to determine whether to use the U.S. system
    * of measurements or the metric system.
    *
    * - PD_INHUNDREDTHSOFMILLIMETERS: Indicates the unit of measure in which margins are specified. If
    * neither this flag nor the PD_INHUNDREDTHSOFMILLIMETERS flag is specified, the Print dialog box
    * uses the LOCALE_IMEASURE setting in the locale table to determine whether to use the U.S. system
    * of measurements or the metric system.
    *
    * - PD_MINMARGINS: On input, this flag specifies that the rcMinMargin member contains initial
    * minimum margin values. On output it indicates that the rcMinMargin member contains user-specified
    * minimum margin values. If the value in the rcMinMargin member is zero on output, it means the
    * user did not specify any minimum margin values.
    */
   DWORD            dwFlags;
   /**
    * Specifies the minimum allowable widths for the left, top, right, and bottom margins. The system
    * ignores this member if the PSD_MINMARGINS flag is not set. These values must be less than or
    * equal to the values specified in the rcMargin member. The PSD_INTHOUSANDTHSOFINCHES or
    * PSD_INHUNDREDTHSOFMILLIMETERS flag indicates the units of measurement.
    */
   RECT             rcMinMargin;
   /**
    * Specifies the widths of the left, top, right, and bottom margins. If you set the PSD_MARGINS
    * flag, rcMargin specifies the initial margin values. When PrintDlg returns, rcMargin contains the
    * margin widths selected by the user. The PSD_INHUNDREDTHSOFMILLIMETERS or
    * PSD_INTHOUSANDTHSOFINCHES flag indicates the units of measurement.
    */
   RECT             rcMargin;
   /**
    * Handle to the application or module instance that contains the dialog box template named by the
    * pszPrintTemplateName member. This member is only valid if the PD_ENABLEPRINTTEMPLATE or
    * PD_ENABLESETUPTEMPLATE flag is set in the dwFlags member.
    */
   HINSTANCE        hinst;
   /**
    * Specifies application-defined data that the system passes to the hook procedure identified by the
    * pfnPrintHook member. When the system sends the WM_INITDIALOG message to the hook procedure, the
    * message's lParam parameter is a pointer to the PRINTDLG structure specified when the dialog was
    * created. The hook procedure can use this pointer to get the lCustData value.
    */
   LPARAM           lCustData;
   /**
    * Pointer to a PrintHookProc hook procedure that can process messages intended for the Print dialog
    * box. This member is ignored unless the PD_ENABLEPRINTHOOK flag is set in the Flags member.
    */
   LPPRINTHOOKPROC  pfnPrintHook;
   /**
    * Pointer to a null-terminated string that names a dialog box template resource in the module
    * identified by the hinst member. This template is substituted for the standard Print dialog box
    * template. This member is ignored unless the PD_ENABLEPRINTTEMPLATE flag is set in the Flags
    * member.
    */
   LPCTSTR          pszPrintTemplateName;
   /**
    * If the PD_ENABLEPRINTTEMPLATEHANDLE flag is set in the Flags member, hglbPrintTemplateResource is
    * the handle to a memory object that contains a dialog box template. This template is substituted
    * for the standard Print dialog box template.
    */
   HGLOBAL          hglbPrintTemplateResource;
} PRINTDLG , *LPPRINTDLG ;

BOOL  APIENTRY     PrintDlg (LPPRINTDLG);

// Out only
#define PD_SELECTALLPAGES                 0x00000001
#define PD_SELECTSELECTION                0x00000002
#define PD_SELECTDRAFTMODE                0x00000008
#define PD_SELECTA4                       0x00000010
#define PD_SELECTLETTER                   0x00000020
#define PD_SELECTINFRARED                 0x00000040 
#define PD_SELECTSERIAL                   0x00000080

// In only
#define PD_DISABLEPAPERSIZE               0x00000100
#define PD_DISABLEPRINTRANGE              0x00000200
#define PD_DISABLEMARGINS                 0x00000400
#define PD_DISABLEORIENTATION             0x00000800
#define PD_RETURNDEFAULTDC                0x00002000
#define PD_ENABLEPRINTHOOK                0x00004000
#define PD_ENABLEPRINTTEMPLATE            0x00008000
#define PD_ENABLEPRINTTEMPLATEHANDLE      0x00010000
#define PD_TITLE                          0x00020000                          

// In-Out
#define PD_SELECTPORTRAIT                 0x00040000
#define PD_SELECTLANDSCAPE                0x00080000
#define PD_MARGINS                        0x00100000
#define PD_INTHOUSANDTHSOFINCHES          0x00200000
#define PD_INHUNDREDTHSOFMILLIMETERS      0x00400000
#define PD_MINMARGINS                     0x00800000

// Errors returned by CommDlgExtendedError()
#define CDERR_DIALOGFAILURE    0xFFFF
#define CDERR_STRUCTSIZE       0x0001
#define CDERR_INITIALIZATION   0x0002
#define CDERR_NOTEMPLATE       0x0003
#define CDERR_FINDRESFAILURE   0x0004
#define CDERR_LOADRESFAILURE   0x0005
#define CDERR_LOCKRESFAILURE   0x0006
#define CDERR_MEMALLOCFAILURE  0x0007
#define CDERR_NOHOOK           0x0008
#define CDERR_REGISTRYFAILURE  0x0009
#define CDERR_NOHINSTANCE      0x000A

#define PDERR_NODEFAULTPRN     0x1000
#define PDERR_PRINTERNOTFOUND  0x1001
#define PDERR_NOPORTS          0x1002
#define PDERR_NOPRINTERS       0x1003
#define PDERR_CREATEDCFAILURE  0x1004

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#include <poppack.h>
#endif  /* !_INC_COMMDLG */
