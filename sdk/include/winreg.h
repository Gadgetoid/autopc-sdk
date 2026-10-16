/*++

Copyright (c) 1995 Microsoft Corporation

Module Name:

    Winreg.h

Abstract:

    This module contains the function prototypes and constant, type and
    structure definitions for the WINCE Implementeation of the Windows
    32-Bit Registry API.

--*/

#ifndef _WINREG_H_
#define _WINREG_H_



//
// Type definitions.
//

#ifdef __cplusplus
extern "C" {
#endif
//	This is going outside of CESYSGEN since a shell structure uses it.
typedef HANDLE HKEY, *PHKEY;

#ifdef __cplusplus
}
#endif



// @CESYSGEN IF FILESYS_FSREG

#ifdef __cplusplus
extern "C" {
#endif

typedef ACCESS_MASK REGSAM;

//
// Type definitions.
//


//
// Reserved Key Handles.
//

#define HKEY_CLASSES_ROOT           (( HKEY ) 0x80000000 )
#define HKEY_CURRENT_USER           (( HKEY ) 0x80000001 )
#define HKEY_LOCAL_MACHINE          (( HKEY ) 0x80000002 )
#define HKEY_USERS                  (( HKEY ) 0x80000003 )

//
// Default values for parameters that do not exist in the Win 3.1
// compatible APIs.
//

#define WIN31_CLASS                 NULL

//
// API Prototypes.
//

WINADVAPI LONG APIENTRY RegCloseKey(HKEY hKey);
WINADVAPI LONG APIENTRY RegCreateKeyExW(HKEY hKey, LPCWSTR lpSubKey, DWORD Reserved, LPWSTR lpClass, DWORD dwOptions, REGSAM samDesired, LPSECURITY_ATTRIBUTES lpSecurityAttributes, PHKEY phkResult, LPDWORD lpdwDisposition);
WINADVAPI LONG APIENTRY RegDeleteKeyW (HKEY hKey, LPCWSTR lpSubKey);
WINADVAPI LONG APIENTRY RegDeleteValueW(HKEY hKey, LPCWSTR lpValueName);
WINADVAPI LONG APIENTRY RegEnumValueW(HKEY hKey, DWORD dwIndex, LPWSTR lpValueName, LPDWORD lpcbValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData);
WINADVAPI LONG APIENTRY RegEnumKeyExW(HKEY hKey, DWORD dwIndex, LPWSTR lpName, LPDWORD lpcbName, LPDWORD lpReserved, LPWSTR lpClass, LPDWORD lpcbClass, PFILETIME lpftLastWriteTime);
WINADVAPI LONG APIENTRY RegOpenKeyExW(HKEY hKey, LPCWSTR lpSubKey, DWORD ulOptions, REGSAM samDesired, PHKEY phkResult);
WINADVAPI LONG APIENTRY RegQueryInfoKeyW (HKEY hKey, LPWSTR lpClass, LPDWORD lpcbClass, LPDWORD lpReserved, LPDWORD lpcSubKeys, LPDWORD lpcbMaxSubKeyLen, LPDWORD lpcbMaxClassLen, LPDWORD lpcValues, LPDWORD lpcbMaxValueNameLen, LPDWORD lpcbMaxValueLen, LPDWORD lpcbSecurityDescriptor, PFILETIME lpftLastWriteTime);
WINADVAPI LONG APIENTRY RegQueryValueExW (HKEY hKey, LPCWSTR lpValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData);
WINADVAPI LONG APIENTRY RegSetValueExW (HKEY hKey, LPCWSTR lpValueName, DWORD Reserved, DWORD dwType, CONST BYTE* lpData, DWORD cbData);

#ifdef UNICODE
#define RegCreateKeyEx  RegCreateKeyExW
#define RegDeleteKey  RegDeleteKeyW
#define RegDeleteValue  RegDeleteValueW
#define RegEnumValue  RegEnumValueW
#define RegEnumKeyEx  RegEnumKeyExW
#define RegOpenKeyEx  RegOpenKeyExW
#define RegQueryInfoKey  RegQueryInfoKeyW
#define RegQueryValueEx  RegQueryValueExW
#define RegSetValueEx  RegSetValueExW
#else
#define RegCreateKeyEx  RegCreateKeyExA
#define RegDeleteKey  RegDeleteKeyA
#define RegDeleteValue  RegDeleteValueA
#define RegEnumValue  RegEnumValueA
#define RegEnumKeyEx  RegEnumKeyExA
#define RegOpenKeyEx  RegOpenKeyExA
#define RegQueryInfoKey  RegQueryInfoKeyA
#define RegQueryValueEx  RegQueryValueExA
#define RegSetValueEx  RegSetValueExA
#endif

#ifdef __cplusplus
}
#endif

#ifdef WINCEOEM
#include <pwinreg.h>
#ifdef WINCEMACRO
#include <mwinreg.h>	// internal defines 
#endif
#endif

// @CESYSGEN ENDIF

#endif // _WINREG_

