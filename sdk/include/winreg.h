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

/**
 * This function releases the handle of the specified key. A remote application interface (RAPI)
 * version of this function exists, and it is called CeRegCloseKey.
 *
 * @param hKey [in] Handle to the open key to close.
 *
 * @return ERROR_SUCCESS indicates success. A nonzero error code defined in Winerror.h indicates
 *   failure. To get a generic description of the error, call FormatMessage with the
 *   FORMAT_MESSAGE_FROM_SYSTEM flag set.
 *
 * The handle for a specified key should not be used after it has been closed, because it will no
 * longer be valid. Key handles should not be left open any longer than necessary.
 *
 * The RegCloseKey function always writes information to the registry before returning, eliminating
 * the need to flush keys in the Windows CE registry.
 */
WINADVAPI LONG APIENTRY RegCloseKey(HKEY hKey);
/**
 * This function creates the specified key. If the key already exists in the registry, the function
 * opens it. A remote application interface (RAPI) version of this function exists, and it is called
 * CeRegCreateKeyEx.
 *
 * @param hKey [in] Handle to a currently open key or one of the following predefined reserved
 *   handle values: HKEY_CLASSES_ROOT HKEY_CURRENT_USER HKEY_LOCAL_MACHINE HKEY_USERS Windows CE does
 *   not support the HKEY_CURRENT_CONFIG, HKEY_PERFORMANCE_DATA, or HKEY_DYN_DATA predefined reserved
 *   handle values. The key opened or created by the RegCreateKeyEx function is a subkey of the key
 *   identified by the hKey parameter.
 * @param lpSubKey [in] Pointer to a null-terminated string specifying the name of a subkey that
 *   this function opens or creates. The subkey specified must be a subkey of the key identified by
 *   the hKey parameter. This subkey must not begin with the backslash character ('\'). This parameter
 *   cannot be NULL. In Windows CE, the maximum length of a key name is 255 characters, not including
 *   the terminating NULL character. You can also only nest 16 levels of sub-keys in Windows CE.
 * @param Reserved [in] Reserved; set to 0.
 * @param lpClass [in] Pointer to a null-terminated string that specifies the class (object type) of
 *   this key. This parameter is ignored if the key already exists. In Windows CE, the maximum length
 *   of a class string is 255 characters, not including the terminating NULL character.
 * @param dwOptions [in] Ignored; set to 0 to ensure compatibility with future versions of Windows
 *   CE.
 * @param samDesired [in] Ignored; set to 0 to ensure compatibility with future versions of Windows
 *   CE.
 * @param lpSecurityAttributes [in] Set to NULL. Windows CE automatically assigns the key a default
 *   security descriptor.
 * @param phkResult [out] Pointer to a variable that receives a handle to the opened or created key.
 *   When you no longer need the returned handle, call the RegCloseKey function to close it.
 * @param lpdwDisposition [out] Pointer to a variable that receives one of the following disposition
 *   values: Value Description REG_CREATED_NEW_KEY The key did not exist and was created.
 *   REG_OPENED_EXISTING_KEY The key existed and was simply opened without being changed.
 *
 * @return ERROR_SUCCESS indicates success. A nonzero error code defined in Winerror.h indicates
 *   failure. To get a generic description of the error, call FormatMessage with the
 *   FORMAT_MESSAGE_FROM_SYSTEM flag set.
 *
 * The key that the RegCreateKeyEx function creates has no values. An application can use the
 * RegSetValueEx function to set key values.
 *
 * The key identified by the hKey parameter must have been opened with KEY_CREATE_SUB_KEY access. To
 * open the key, use the RegCreateKeyEx or RegOpenKeyEx function.
 *
 * RegCreateKeyEx can create keys under the HKEY_LOCAL_MACHINE and HKEY_USERS registries.
 *
 * An application can use RegCreateKeyEx to temporarily lock a portion of the registry. When the
 * locking process creates a new key, it receives the disposition value REG_CREATED_NEW_KEY,
 * indicating that it "owns" the lock. Another process attempting to create the same key receives
 * the disposition value REG_OPENED_EXISTING_KEY, indicating that another process already owns the
 * lock.
 */
WINADVAPI LONG APIENTRY RegCreateKeyExW(HKEY hKey, LPCWSTR lpSubKey, DWORD Reserved, LPWSTR lpClass, DWORD dwOptions, REGSAM samDesired, LPSECURITY_ATTRIBUTES lpSecurityAttributes, PHKEY phkResult, LPDWORD lpdwDisposition);
/**
 * This function deletes a named subkey from the specified registry key. The subkey to be deleted
 * cannot have any subkeys.
 *
 * @param hKey [in] Handle to a currently open key or one of the following predefined reserved
 *   handle values: HKEY_CLASSES_ROOT HKEY_CURRENT_USER HKEY_LOCAL_MACHINE HKEY_USERS The key
 *   specified by the lpSubKey parameter must be a subkey of the key identified by hKey.
 * @param lpSubKey [in] Pointer to a null-terminated string specifying the name of the key to
 *   delete. This parameter cannot be NULL.
 *
 * @return ERROR_SUCCESS indicates success. A nonzero error code defined in Winerror.h indicates
 *   failure. To get a generic description of the error, call FormatMessage with the
 *   FORMAT_MESSAGE_FROM_SYSTEM flag set.
 *
 * If the function succeeds, RegDeleteKey removes the specified key from the registry. The entire
 * key, including all of its values, is removed. An application cannot call RegDeleteKey for a key
 * that an application currently has open.
 *
 * To open the key, use the RegCreateKeyEx or RegOpenKeyEx function.
 */
WINADVAPI LONG APIENTRY RegDeleteKeyW (HKEY hKey, LPCWSTR lpSubKey);
/**
 * This function removes a named value from the specified registry key. A remote application
 * interface (RAPI) version of this function exists, and it is called CeRegDeleteValue.
 *
 * @param hKey [in] Handle to a currently open key or any of the following predefined reserved
 *   handle values: HKEY_CLASSES_ROOT HKEY_CURRENT_USER HKEY_LOCAL_MACHINE HKEY_USERS
 * @param lpValueName [in] Pointer to a null-terminated string that names the value to remove. If
 *   this parameter is NULL or points to an empty string, the default value of the key is removed. A
 *   default value is create by calling RegCreateValueEx with a NULL or empty string value name.
 *
 * @return ERROR_SUCCESS indicates success. A nonzero error code defined in Winerror.h indicates
 *   failure. To get a generic description of the error, call FormatMessage with the
 *   FORMAT_MESSAGE_FROM_SYSTEM flag set.
 *
 * The key identified by the hKey parameter must have been opened with KEY_SET_VALUE access
 * (KEY_WRITE access includes KEY_SET_VALUE access).
 */
WINADVAPI LONG APIENTRY RegDeleteValueW(HKEY hKey, LPCWSTR lpValueName);
/**
 * This function enumerates the values for the specified open registry key. RegEnumValue copies one
 * indexed value name and data block for the key each time it is called.
 *
 * @param hKey [in] Handle to a currently open key or one of the following predefined reserved
 *   handle values: HKEY_CLASSES_ROOT HKEY_CURRENT_USER HKEY_LOCAL_MACHINE HKEY_USERS The enumerated
 *   values are associated with the key identified by hKey.
 * @param dwIndex [in] Specifies the index of the value to retrieve. This parameter should be zero
 *   for the first call to the RegEnumValue function and then be incremented for subsequent calls.
 *   Because values are not ordered, any new value will have an arbitrary index. This means that the
 *   function may return values in any order.
 * @param lpValueName [out] Pointer to a buffer that receives the name of the value, including the
 *   terminating null character.
 * @param lpcbValueName [in/out] Pointer to a variable that specifies the size, in characters, of
 *   the buffer pointed to by the lpValueName parameter. This size should include the terminating null
 *   character. When the function returns, the variable pointed to by lpcbValueName contains the
 *   number of characters stored in the buffer. The count returned does not include the terminating
 *   null character.
 * @param lpReserved [in] Reserved; set to NULL.
 * @param lpType [out] Pointer to a variable that receives the type code for the value entry. The
 *   type code can be one of the following values: Value Description REG_BINARY Binary data in any
 *   form. REG_DWORD A 32-bit number. REG_DWORD_LITTLE_ENDIAN A 32-bit number in little-endian format.
 *   This is equivalent to REG_DWORD. In little-endian format, a multi-byte value is stored in memory
 *   from the lowest byte (the "little end") to the highest byte. For example, the value 0x12345678 is
 *   stored as (0x78 0x56 0x34 0x12) in little-endian format. REG_DWORD_BIG_ENDIAN A 32-bit number in
 *   big-endian format. In big-endian format, a multi-byte value is stored in memory from the highest
 *   byte (the "big end") to the lowest byte. For example, the value 0x12345678 is stored as (0x12
 *   0x34 0x56 0x78) in big-endian format. REG_EXPAND_SZ A null-terminated string that contains
 *   unexpanded references to environment variables (for example, "%PATH%"). It will be a Unicode or
 *   ANSI string depending on whether you use the Unicode or ANSI functions. REG_LINK A Unicode
 *   symbolic link. Used internally; applications should not use this type. REG_MULTI_SZ An array of
 *   null-terminated strings, terminated by two null characters. REG_NONE No defined value type.
 *   REG_RESOURCE_LIST A device-driver resource list. REG_SZ A null-terminated string. It will be a
 *   Unicode or ANSI string, depending on whether you use the Unicode or ANSI functions. The lpType
 *   parameter can be NULL if the type code is not required.
 * @param lpData [out] Pointer to a buffer that receives the data for the value entry. This
 *   parameter can be NULL if the data is not required.
 * @param lpcbData [in/out] Pointer to a variable that specifies the size, in bytes, of the buffer
 *   pointed to by the lpData parameter. When the function returns, the variable pointed to by the
 *   lpcbData parameter contains the number of bytes stored in the buffer. This parameter can be NULL,
 *   only if lpData is NULL.
 *
 * @return ERROR_SUCCESS indicates success. A nonzero error code defined in Winerror.h indicates
 *   failure. To get a generic description of the error, call FormatMessage with the
 *   FORMAT_MESSAGE_FROM_SYSTEM flag set.
 *
 * To enumerate values, an application should initially call the RegEnumValue function with the
 * dwIndex parameter set to zero. The application should then increment dwIndex and call the
 * RegEnumValue function until there are no more values (until the function returns
 * ERROR_NO_MORE_ITEMS).
 *
 * The application can also set dwIndex to the index of the last value on the first call to the
 * function and decrement the index until the value with index 0 is enumerated. To retrieve the
 * index of the last value, use the RegQueryInfoKey function.
 *
 * While using RegEnumValue, an application should not call any registration functions that might
 * change the key being queried.
 *
 * The key identified by the hKey parameter must have been opened with KEY_QUERY_VALUE access. To
 * open the key, use the RegCreateKeyEx or RegOpenKeyEx function.
 *
 * To determine the maximum size of the name and data buffers, use the RegQueryInfoKey function.
 */
WINADVAPI LONG APIENTRY RegEnumValueW(HKEY hKey, DWORD dwIndex, LPWSTR lpValueName, LPDWORD lpcbValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData);
/**
 * This function enumerates subkeys of the specified open registry key. RegEnumKeyEx retrieves
 * information about one subkey each time it is called and it retrieves the class name of the subkey
 * and the time it was last modified.
 *
 * @param hKey [in] Handle to a currently open key or one of the following predefined reserved
 *   handle values: HKEY_CLASSES_ROOT HKEY_CURRENT_USER HKEY_LOCAL_MACHINE HKEY_USERS The enumerated
 *   keys are subkeys of the key identified by hKey.
 * @param dwIndex [in] Specifies the index of the subkey to retrieve. This parameter should be zero
 *   for the first call to the RegEnumKeyEx function and then incremented for subsequent calls.
 *   Because subkeys are not ordered, any new subkey will have an arbitrary index. This means that the
 *   function may return subkeys in any order.
 * @param lpName [out] Pointer to a buffer that receives the name of the subkey, including the
 *   terminating null character. The function copies only the name of the subkey, not the full key
 *   hierarchy, to the buffer.
 * @param lpcbName [in/out] Pointer to a variable that specifies the size, in characters, of the
 *   buffer specified by the lpName parameter. This size should include the terminating null
 *   character. When the function returns, the variable pointed to by lpcbName contains the number of
 *   characters stored in the buffer. The count returned does not include the terminating null
 *   character.
 * @param lpReserved [in] Reserved; set to NULL.
 * @param lpClass [out] Pointer to a buffer that contains the class of the enumerated subkey when
 *   the function returns. This parameter can be NULL if the class is not required.
 * @param lpcbClass [in/out] Pointer to a variable that specifies the size, in characters, of the
 *   buffer specified by the lpClass parameter. The size should include the terminating null
 *   character. When the function returns, lpcbClass contains the number of characters stored in the
 *   buffer. The count returned does not include the terminating null character. This parameter can be
 *   NULL only if lpClass is NULL.
 * @param lpftLastWriteTime [in] Ignored; set to NULL.
 *
 * @return ERROR_SUCCESS indicates success. A nonzero error code defined in Winerror.h indicates
 *   failure. To get a generic description of the error, call FormatMessage with the
 *   FORMAT_MESSAGE_FROM_SYSTEM flag set.
 *
 * To enumerate subkeys, an application should initially call the RegEnumKeyEx function with the
 * dwIndex parameter set to zero. An application should then increment the dwIndex parameter and
 * call RegEnumKeyEx until there are no more subkeys (until the function returns
 * ERROR_NO_MORE_ITEMS).
 *
 * An application can also set dwIndex to the index of the last subkey on the first call to the
 * function and decrement the index until the subkey with the index 0 is enumerated. To retrieve the
 * index of the last subkey, use the RegQueryInfoKey function.
 *
 * While an application is using the RegEnumKeyEx function, it should not make calls to any
 * registration functions that might change the key being enumerated.
 *
 * The key identified by hKey must have been opened with KEY_ENUMERATE_SUB_KEYS access (KEY_READ
 * includes KEY_ENUMERATE_SUB_KEYS). Use the RegCreateKeyEx or RegOpenKeyEx function to open the
 * key.
 */
WINADVAPI LONG APIENTRY RegEnumKeyExW(HKEY hKey, DWORD dwIndex, LPWSTR lpName, LPDWORD lpcbName, LPDWORD lpReserved, LPWSTR lpClass, LPDWORD lpcbClass, PFILETIME lpftLastWriteTime);
/**
 * This function opens the specified key.
 *
 * @param hKey [in] Handle to a currently open key or any of the following predefined reserved
 *   handle values: HKEY_CLASSES_ROOT HKEY_CURRENT_USER HKEY_LOCAL_MACHINE HKEY_USERS Windows CE does
 *   not support the HKEY_CURRENT_CONFIG, HKEY_PERFORMANCE_DATA, or HKEY_DYN_DATA predefined reserved
 *   handle values.
 * @param lpSubKey [in] Pointer to a null-terminated string containing the name of the subkey to
 *   open. If this parameter is NULL or a pointer to an empty string, the function will open a new
 *   handle to the key identified by the hKey parameter. In this case, the function will not close the
 *   handles previously opened.
 * @param ulOptions [in] Reserved; set to 0.
 * @param samDesired [in] Not supported; set to zero.
 * @param phkResult [out] Pointer to a variable that receives a handle to the opened key. When you
 *   no longer need the returned handle, call the RegCloseKey function to close it.
 *
 * @return ERROR_SUCCESS indicates success. A nonzero error code defined in Winerror.h indicates
 *   failure. To get a generic description of the error, call FormatMessage with the
 *   FORMAT_MESSAGE_FROM_SYSTEM flag set.
 *
 * Unlike the RegCreateKeyEx function, the RegOpenKeyEx function does not create the specified key
 * if the key does not exist in the registry.
 */
WINADVAPI LONG APIENTRY RegOpenKeyExW(HKEY hKey, LPCWSTR lpSubKey, DWORD ulOptions, REGSAM samDesired, PHKEY phkResult);
/**
 * This function retrieves information about a specified registry key.
 *
 * @param hKey [in] Handle to a currently open key or any of the following predefined reserved
 *   handle values: HKEY_CLASSES_ROOT HKEY_CURRENT_USER HKEY_LOCAL_MACHINE HKEY_USERS
 * @param lpClass [out] Pointer to a buffer that receives the key's class name. This parameter can
 *   be NULL.
 * @param lpcbClass [in/out] Pointer to a variable that specifies the size, in characters, of the
 *   buffer pointed to by the lpClass parameter. This size should include the terminating null
 *   character. When the function returns, this variable contains the length of the class string
 *   stored in the buffer. The count returned does not include the terminating null character. If the
 *   buffer is not big enough, the function returns ERROR_MORE_DATA, and the variable contains the
 *   size of the string, in characters, without counting the null character. If lpClass is NULL,
 *   lpcbClass can be NULL. If the lpClass parameter is a valid address, but this parameter is not,
 *   the function returns ERROR_INVALID_PARAMETER.
 * @param lpReserved [in] Reserved; set to NULL.
 * @param lpcSubKeys [out] Pointer to a variable that receives the number of subkeys contained by
 *   the specified key. This parameter can be NULL.
 * @param lpcbMaxSubKeyLen [out] Pointer to a variable that receives the length, in characters, of
 *   the key's subkey with the longest name. The count returned does not include the terminating null
 *   character. This parameter can be NULL.
 * @param lpcbMaxClassLen [out] Pointer to a variable that receives the length, in characters, of
 *   the longest string specifying a subkey class. The count returned does not include the terminating
 *   null character. This parameter can be NULL.
 * @param lpcValues [out] Pointer to a variable that receives the number of values associated with
 *   the key. This parameter can be NULL.
 * @param lpcbMaxValueNameLen [out] Pointer to a variable that receives the length, in characters,
 *   of the key's longest value name. The count returned does not include the terminating null
 *   character. This parameter can be NULL.
 * @param lpcbMaxValueLen [out] Pointer to a variable that receives the length, in bytes, of the
 *   longest data component among the values of the key. This parameter can be NULL.
 * @param lpcbSecurityDescriptor [in] Not used; set to NULL.
 * @param lpftLastWriteTime [in] Ignored; set to NULL.
 *
 * @return ERROR_SUCCESS indicates success. A nonzero error code defined in Winerror.h indicates
 *   failure. To get a generic description of the error, call FormatMessage with the
 *   FORMAT_MESSAGE_FROM_SYSTEM flag set.
 *
 * The key identified by the hKey parameter must have been opened with KEY_QUERY_VALUE access
 * (KEY_READ access includes KEY_QUERY_VALUE access).
 */
WINADVAPI LONG APIENTRY RegQueryInfoKeyW (HKEY hKey, LPWSTR lpClass, LPDWORD lpcbClass, LPDWORD lpReserved, LPDWORD lpcSubKeys, LPDWORD lpcbMaxSubKeyLen, LPDWORD lpcbMaxClassLen, LPDWORD lpcValues, LPDWORD lpcbMaxValueNameLen, LPDWORD lpcbMaxValueLen, LPDWORD lpcbSecurityDescriptor, PFILETIME lpftLastWriteTime);
/**
 * This function retrieves the type and data for a specified value name associated with an open
 * registry key.
 *
 * @param hKey [in] Handle to a currently open key or any of the following predefined reserved
 *   handle values: HKEY_CLASSES_ROOT HKEY_CURRENT_USER HKEY_LOCAL_MACHINE HKEY_USERS
 * @param lpValueName [in] Pointer to a string containing the name of the value to query. If this
 *   parameter is NULL or an empty string, the function retrieves the type and data for the key's
 *   unnamed value. A registry key does not automatically have an unnamed or default value. Unnamed
 *   values can be of any type.
 * @param lpReserved [in] Reserved; set to NULL.
 * @param lpType [out] Pointer to a variable that receives the type of data associated with the
 *   specified value. The value returned through this parameter will be one of the following: Value
 *   Description REG_BINARY Binary data in any form. REG_DWORD A 32-bit number.
 *   REG_DWORD_LITTLE_ENDIAN A 32-bit number in little-endian format. This is equivalent to REG_DWORD.
 *   In little-endian format, a multi-byte value is stored in memory from the lowest byte (the "little
 *   end") to the highest byte. For example, the value 0x12345678 is stored as (0x78 0x56 0x34 0x12)
 *   in little-endian format. REG_DWORD_BIG_ENDIAN A 32-bit number in big-endian format. In big-endian
 *   format, a multi-byte value is stored in memory from the highest byte (the "big end") to the
 *   lowest byte. For example, the value 0x12345678 is stored as (0x12 0x34 0x56 0x78) in big-endian
 *   format. REG_EXPAND_SZ A null-terminated string that contains unexpanded references to environment
 *   variables (for example, "%PATH%"). REG_LINK A Unicode symbolic link. Used internally;
 *   applications should not use this type. REG_MULTI_SZ An array of null-terminated strings,
 *   terminated by two null characters. REG_NONE No defined value type. REG_RESOURCE_LIST A
 *   device-driver resource list. REG_SZ A null-terminated string. The lpType parameter can be NULL if
 *   the type is not required.
 * @param lpData [out] Pointer to a buffer that receives the value's data. This parameter can be
 *   NULL if the data is not required.
 * @param lpcbData [in/out] Pointer to a variable that specifies the size, in bytes, of the buffer
 *   pointed to by the lpData parameter. When the function returns, this variable contains the size of
 *   the data copied to lpData. If the data has the REG_SZ, REG_MULTI_SZ or REG_EXPAND_SZ type, then
 *   lpcbData will also include the size of the terminating null character. The lpcbData parameter can
 *   be NULL only if lpData is NULL. If the buffer specified by lpData parameter is not large enough
 *   to hold the data, the function returns the value ERROR_MORE_DATA, and stores the required buffer
 *   size, in bytes, into the variable pointed to by lpcbData. If lpData is NULL, and lpcbData is
 *   non-NULL, the function returns ERROR_SUCCESS, and stores the size of the data, in bytes, in the
 *   variable pointed to by lpcbData. This lets an application determine the best way to allocate a
 *   buffer for the value's data.
 *
 * @return ERROR_SUCCESS indicates success. A nonzero error code defined in Winerror.h indicates
 *   failure. To get a generic description of the error, call FormatMessage with the
 *   FORMAT_MESSAGE_FROM_SYSTEM flag set.
 *
 * The key identified by hKey must have been opened with KEY_QUERY_VALUE access. To open the key,
 * use the RegCreateKeyEx or RegOpenKeyEx function.
 *
 * Windows CE supports only the Unicode version of this function.
 */
WINADVAPI LONG APIENTRY RegQueryValueExW (HKEY hKey, LPCWSTR lpValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData);
/**
 * This function stores data in the value field of an open registry key. It can also set additional
 * value and type information for the specified key.
 *
 * @param hKey [in] Handle to a currently open key or any of the following predefined reserved
 *   handle values: HKEY_CLASSES_ROOT HKEY_CURRENT_USER HKEY_LOCAL_MACHINE HKEY_USERS
 * @param lpValueName [in] Pointer to a string containing the name of the value to set. If a value
 *   with this name is not already present in the key, the function adds it to the key. If this
 *   parameter is NULL or an empty string, the function sets the type and data for the key's unnamed
 *   value. Registry keys do not have default values, but they can have one unnamed value, which can
 *   be of any type. The maximum length of a value name is 255, not including the terminating NULL
 *   character.
 * @param Reserved [in] Reserved; must be zero.
 * @param dwType [in] Specifies the type of information to be stored as the value's data. This
 *   parameter can be one of the following values: Value Description REG_BINARY Binary data in any
 *   form. REG_DWORD A 32-bit number. REG_DWORD_LITTLE_ENDIAN A 32-bit number in little-endian format.
 *   This is equivalent to REG_DWORD. In little-endian format, a multi-byte value is stored in memory
 *   from the lowest byte (the "little end") to the highest byte. For example, the value 0x12345678 is
 *   stored as (0x78 0x56 0x34 0x12) in little-endian format. REG_DWORD_BIG_ENDIAN A 32-bit number in
 *   big-endian format. In big-endian format, a multi-byte value is stored in memory from the highest
 *   byte (the "big end") to the lowest byte. For example, the value 0x12345678 is stored as (0x12
 *   0x34 0x56 0x78) in big-endian format. REG_EXPAND_SZ A null-terminated string that contains
 *   unexpanded references to environment variables (for example, "%PATH%"). REG_LINK A Unicode
 *   symbolic link. Used internally; applications should not use this type. REG_MULTI_SZ An array of
 *   null-terminated strings, terminated by two null characters. REG_NONE No defined value type.
 *   REG_RESOURCE_LIST A device-driver resource list. REG_SZ A null-terminated string. Do not use the
 *   REG_SZ type to store hard-coded paths to the system root directory or to the drive containing the
 *   system files. Instead, use the REG_EXPAND_SZ type with environment variables such as
 *   "%SystemRoot%". This ensures that the path will be up-to-date even if the user remaps the system
 *   drive to a different drive letter.
 * @param lpData [in] Pointer to a buffer containing the data to be stored with the specified value
 *   name.
 * @param cbData [in] Specifies the size, in bytes, of the information pointed to by the lpData
 *   parameter. If the data is of type REG_SZ, REG_EXPAND_SZ, or REG_MULTI_SZ, cbData must include the
 *   size of the terminating null character. The maximum size of data allowed in Windows CE is 4 KB.
 *
 * @return ERROR_SUCCESS indicates success. A nonzero error code defined in Winerror.h indicates
 *   failure. To get a generic description of the error, call FormatMessage with the
 *   FORMAT_MESSAGE_FROM_SYSTEM flag set.
 *
 * Value lengths are limited by available memory. Long values (more than 2048 bytes) should be
 * stored as files with the filenames stored in the registry. This helps the registry perform
 * efficiently. Application elements such as icons, bitmaps, and executable files should be stored
 * as files and not be placed in the registry.
 *
 * The key identified by the hKey parameter must have been opened with KEY_SET_VALUE access. To open
 * the key, use the RegCreateKeyEx or RegOpenKeyEx function.
 *
 * Windows CE supports only the Unicode version of this function.
 */
WINADVAPI LONG APIENTRY RegSetValueExW (HKEY hKey, LPCWSTR lpValueName, DWORD Reserved, DWORD dwType, CONST BYTE* lpData, DWORD cbData);

#ifdef UNICODE
/**
 * This function creates the specified key. If the key already exists in the registry, the function
 * opens it. A remote application interface (RAPI) version of this function exists, and it is called
 * CeRegCreateKeyEx.
 *
 * @param hKey [in] Handle to a currently open key or one of the following predefined reserved
 *   handle values: HKEY_CLASSES_ROOT HKEY_CURRENT_USER HKEY_LOCAL_MACHINE HKEY_USERS Windows CE does
 *   not support the HKEY_CURRENT_CONFIG, HKEY_PERFORMANCE_DATA, or HKEY_DYN_DATA predefined reserved
 *   handle values. The key opened or created by the RegCreateKeyEx function is a subkey of the key
 *   identified by the hKey parameter.
 * @param lpSubKey [in] Pointer to a null-terminated string specifying the name of a subkey that
 *   this function opens or creates. The subkey specified must be a subkey of the key identified by
 *   the hKey parameter. This subkey must not begin with the backslash character ('\'). This parameter
 *   cannot be NULL. In Windows CE, the maximum length of a key name is 255 characters, not including
 *   the terminating NULL character. You can also only nest 16 levels of sub-keys in Windows CE.
 * @param Reserved [in] Reserved; set to 0.
 * @param lpClass [in] Pointer to a null-terminated string that specifies the class (object type) of
 *   this key. This parameter is ignored if the key already exists. In Windows CE, the maximum length
 *   of a class string is 255 characters, not including the terminating NULL character.
 * @param dwOptions [in] Ignored; set to 0 to ensure compatibility with future versions of Windows
 *   CE.
 * @param samDesired [in] Ignored; set to 0 to ensure compatibility with future versions of Windows
 *   CE.
 * @param lpSecurityAttributes [in] Set to NULL. Windows CE automatically assigns the key a default
 *   security descriptor.
 * @param phkResult [out] Pointer to a variable that receives a handle to the opened or created key.
 *   When you no longer need the returned handle, call the RegCloseKey function to close it.
 * @param lpdwDisposition [out] Pointer to a variable that receives one of the following disposition
 *   values: Value Description REG_CREATED_NEW_KEY The key did not exist and was created.
 *   REG_OPENED_EXISTING_KEY The key existed and was simply opened without being changed.
 *
 * @return ERROR_SUCCESS indicates success. A nonzero error code defined in Winerror.h indicates
 *   failure. To get a generic description of the error, call FormatMessage with the
 *   FORMAT_MESSAGE_FROM_SYSTEM flag set.
 *
 * The key that the RegCreateKeyEx function creates has no values. An application can use the
 * RegSetValueEx function to set key values.
 *
 * The key identified by the hKey parameter must have been opened with KEY_CREATE_SUB_KEY access. To
 * open the key, use the RegCreateKeyEx or RegOpenKeyEx function.
 *
 * RegCreateKeyEx can create keys under the HKEY_LOCAL_MACHINE and HKEY_USERS registries.
 *
 * An application can use RegCreateKeyEx to temporarily lock a portion of the registry. When the
 * locking process creates a new key, it receives the disposition value REG_CREATED_NEW_KEY,
 * indicating that it "owns" the lock. Another process attempting to create the same key receives
 * the disposition value REG_OPENED_EXISTING_KEY, indicating that another process already owns the
 * lock.
 */
#define RegCreateKeyEx  RegCreateKeyExW
/**
 * This function deletes a named subkey from the specified registry key. The subkey to be deleted
 * cannot have any subkeys.
 *
 * @param hKey [in] Handle to a currently open key or one of the following predefined reserved
 *   handle values: HKEY_CLASSES_ROOT HKEY_CURRENT_USER HKEY_LOCAL_MACHINE HKEY_USERS The key
 *   specified by the lpSubKey parameter must be a subkey of the key identified by hKey.
 * @param lpSubKey [in] Pointer to a null-terminated string specifying the name of the key to
 *   delete. This parameter cannot be NULL.
 *
 * @return ERROR_SUCCESS indicates success. A nonzero error code defined in Winerror.h indicates
 *   failure. To get a generic description of the error, call FormatMessage with the
 *   FORMAT_MESSAGE_FROM_SYSTEM flag set.
 *
 * If the function succeeds, RegDeleteKey removes the specified key from the registry. The entire
 * key, including all of its values, is removed. An application cannot call RegDeleteKey for a key
 * that an application currently has open.
 *
 * To open the key, use the RegCreateKeyEx or RegOpenKeyEx function.
 */
#define RegDeleteKey  RegDeleteKeyW
/**
 * This function removes a named value from the specified registry key. A remote application
 * interface (RAPI) version of this function exists, and it is called CeRegDeleteValue.
 *
 * @param hKey [in] Handle to a currently open key or any of the following predefined reserved
 *   handle values: HKEY_CLASSES_ROOT HKEY_CURRENT_USER HKEY_LOCAL_MACHINE HKEY_USERS
 * @param lpValueName [in] Pointer to a null-terminated string that names the value to remove. If
 *   this parameter is NULL or points to an empty string, the default value of the key is removed. A
 *   default value is create by calling RegCreateValueEx with a NULL or empty string value name.
 *
 * @return ERROR_SUCCESS indicates success. A nonzero error code defined in Winerror.h indicates
 *   failure. To get a generic description of the error, call FormatMessage with the
 *   FORMAT_MESSAGE_FROM_SYSTEM flag set.
 *
 * The key identified by the hKey parameter must have been opened with KEY_SET_VALUE access
 * (KEY_WRITE access includes KEY_SET_VALUE access).
 */
#define RegDeleteValue  RegDeleteValueW
/**
 * This function enumerates the values for the specified open registry key. RegEnumValue copies one
 * indexed value name and data block for the key each time it is called.
 *
 * @param hKey [in] Handle to a currently open key or one of the following predefined reserved
 *   handle values: HKEY_CLASSES_ROOT HKEY_CURRENT_USER HKEY_LOCAL_MACHINE HKEY_USERS The enumerated
 *   values are associated with the key identified by hKey.
 * @param dwIndex [in] Specifies the index of the value to retrieve. This parameter should be zero
 *   for the first call to the RegEnumValue function and then be incremented for subsequent calls.
 *   Because values are not ordered, any new value will have an arbitrary index. This means that the
 *   function may return values in any order.
 * @param lpValueName [out] Pointer to a buffer that receives the name of the value, including the
 *   terminating null character.
 * @param lpcbValueName [in/out] Pointer to a variable that specifies the size, in characters, of
 *   the buffer pointed to by the lpValueName parameter. This size should include the terminating null
 *   character. When the function returns, the variable pointed to by lpcbValueName contains the
 *   number of characters stored in the buffer. The count returned does not include the terminating
 *   null character.
 * @param lpReserved [in] Reserved; set to NULL.
 * @param lpType [out] Pointer to a variable that receives the type code for the value entry. The
 *   type code can be one of the following values: Value Description REG_BINARY Binary data in any
 *   form. REG_DWORD A 32-bit number. REG_DWORD_LITTLE_ENDIAN A 32-bit number in little-endian format.
 *   This is equivalent to REG_DWORD. In little-endian format, a multi-byte value is stored in memory
 *   from the lowest byte (the "little end") to the highest byte. For example, the value 0x12345678 is
 *   stored as (0x78 0x56 0x34 0x12) in little-endian format. REG_DWORD_BIG_ENDIAN A 32-bit number in
 *   big-endian format. In big-endian format, a multi-byte value is stored in memory from the highest
 *   byte (the "big end") to the lowest byte. For example, the value 0x12345678 is stored as (0x12
 *   0x34 0x56 0x78) in big-endian format. REG_EXPAND_SZ A null-terminated string that contains
 *   unexpanded references to environment variables (for example, "%PATH%"). It will be a Unicode or
 *   ANSI string depending on whether you use the Unicode or ANSI functions. REG_LINK A Unicode
 *   symbolic link. Used internally; applications should not use this type. REG_MULTI_SZ An array of
 *   null-terminated strings, terminated by two null characters. REG_NONE No defined value type.
 *   REG_RESOURCE_LIST A device-driver resource list. REG_SZ A null-terminated string. It will be a
 *   Unicode or ANSI string, depending on whether you use the Unicode or ANSI functions. The lpType
 *   parameter can be NULL if the type code is not required.
 * @param lpData [out] Pointer to a buffer that receives the data for the value entry. This
 *   parameter can be NULL if the data is not required.
 * @param lpcbData [in/out] Pointer to a variable that specifies the size, in bytes, of the buffer
 *   pointed to by the lpData parameter. When the function returns, the variable pointed to by the
 *   lpcbData parameter contains the number of bytes stored in the buffer. This parameter can be NULL,
 *   only if lpData is NULL.
 *
 * @return ERROR_SUCCESS indicates success. A nonzero error code defined in Winerror.h indicates
 *   failure. To get a generic description of the error, call FormatMessage with the
 *   FORMAT_MESSAGE_FROM_SYSTEM flag set.
 *
 * To enumerate values, an application should initially call the RegEnumValue function with the
 * dwIndex parameter set to zero. The application should then increment dwIndex and call the
 * RegEnumValue function until there are no more values (until the function returns
 * ERROR_NO_MORE_ITEMS).
 *
 * The application can also set dwIndex to the index of the last value on the first call to the
 * function and decrement the index until the value with index 0 is enumerated. To retrieve the
 * index of the last value, use the RegQueryInfoKey function.
 *
 * While using RegEnumValue, an application should not call any registration functions that might
 * change the key being queried.
 *
 * The key identified by the hKey parameter must have been opened with KEY_QUERY_VALUE access. To
 * open the key, use the RegCreateKeyEx or RegOpenKeyEx function.
 *
 * To determine the maximum size of the name and data buffers, use the RegQueryInfoKey function.
 */
#define RegEnumValue  RegEnumValueW
/**
 * This function enumerates subkeys of the specified open registry key. RegEnumKeyEx retrieves
 * information about one subkey each time it is called and it retrieves the class name of the subkey
 * and the time it was last modified.
 *
 * @param hKey [in] Handle to a currently open key or one of the following predefined reserved
 *   handle values: HKEY_CLASSES_ROOT HKEY_CURRENT_USER HKEY_LOCAL_MACHINE HKEY_USERS The enumerated
 *   keys are subkeys of the key identified by hKey.
 * @param dwIndex [in] Specifies the index of the subkey to retrieve. This parameter should be zero
 *   for the first call to the RegEnumKeyEx function and then incremented for subsequent calls.
 *   Because subkeys are not ordered, any new subkey will have an arbitrary index. This means that the
 *   function may return subkeys in any order.
 * @param lpName [out] Pointer to a buffer that receives the name of the subkey, including the
 *   terminating null character. The function copies only the name of the subkey, not the full key
 *   hierarchy, to the buffer.
 * @param lpcbName [in/out] Pointer to a variable that specifies the size, in characters, of the
 *   buffer specified by the lpName parameter. This size should include the terminating null
 *   character. When the function returns, the variable pointed to by lpcbName contains the number of
 *   characters stored in the buffer. The count returned does not include the terminating null
 *   character.
 * @param lpReserved [in] Reserved; set to NULL.
 * @param lpClass [out] Pointer to a buffer that contains the class of the enumerated subkey when
 *   the function returns. This parameter can be NULL if the class is not required.
 * @param lpcbClass [in/out] Pointer to a variable that specifies the size, in characters, of the
 *   buffer specified by the lpClass parameter. The size should include the terminating null
 *   character. When the function returns, lpcbClass contains the number of characters stored in the
 *   buffer. The count returned does not include the terminating null character. This parameter can be
 *   NULL only if lpClass is NULL.
 * @param lpftLastWriteTime [in] Ignored; set to NULL.
 *
 * @return ERROR_SUCCESS indicates success. A nonzero error code defined in Winerror.h indicates
 *   failure. To get a generic description of the error, call FormatMessage with the
 *   FORMAT_MESSAGE_FROM_SYSTEM flag set.
 *
 * To enumerate subkeys, an application should initially call the RegEnumKeyEx function with the
 * dwIndex parameter set to zero. An application should then increment the dwIndex parameter and
 * call RegEnumKeyEx until there are no more subkeys (until the function returns
 * ERROR_NO_MORE_ITEMS).
 *
 * An application can also set dwIndex to the index of the last subkey on the first call to the
 * function and decrement the index until the subkey with the index 0 is enumerated. To retrieve the
 * index of the last subkey, use the RegQueryInfoKey function.
 *
 * While an application is using the RegEnumKeyEx function, it should not make calls to any
 * registration functions that might change the key being enumerated.
 *
 * The key identified by hKey must have been opened with KEY_ENUMERATE_SUB_KEYS access (KEY_READ
 * includes KEY_ENUMERATE_SUB_KEYS). Use the RegCreateKeyEx or RegOpenKeyEx function to open the
 * key.
 */
#define RegEnumKeyEx  RegEnumKeyExW
/**
 * This function opens the specified key.
 *
 * @param hKey [in] Handle to a currently open key or any of the following predefined reserved
 *   handle values: HKEY_CLASSES_ROOT HKEY_CURRENT_USER HKEY_LOCAL_MACHINE HKEY_USERS Windows CE does
 *   not support the HKEY_CURRENT_CONFIG, HKEY_PERFORMANCE_DATA, or HKEY_DYN_DATA predefined reserved
 *   handle values.
 * @param lpSubKey [in] Pointer to a null-terminated string containing the name of the subkey to
 *   open. If this parameter is NULL or a pointer to an empty string, the function will open a new
 *   handle to the key identified by the hKey parameter. In this case, the function will not close the
 *   handles previously opened.
 * @param ulOptions [in] Reserved; set to 0.
 * @param samDesired [in] Not supported; set to zero.
 * @param phkResult [out] Pointer to a variable that receives a handle to the opened key. When you
 *   no longer need the returned handle, call the RegCloseKey function to close it.
 *
 * @return ERROR_SUCCESS indicates success. A nonzero error code defined in Winerror.h indicates
 *   failure. To get a generic description of the error, call FormatMessage with the
 *   FORMAT_MESSAGE_FROM_SYSTEM flag set.
 *
 * Unlike the RegCreateKeyEx function, the RegOpenKeyEx function does not create the specified key
 * if the key does not exist in the registry.
 */
#define RegOpenKeyEx  RegOpenKeyExW
/**
 * This function retrieves information about a specified registry key.
 *
 * @param hKey [in] Handle to a currently open key or any of the following predefined reserved
 *   handle values: HKEY_CLASSES_ROOT HKEY_CURRENT_USER HKEY_LOCAL_MACHINE HKEY_USERS
 * @param lpClass [out] Pointer to a buffer that receives the key's class name. This parameter can
 *   be NULL.
 * @param lpcbClass [in/out] Pointer to a variable that specifies the size, in characters, of the
 *   buffer pointed to by the lpClass parameter. This size should include the terminating null
 *   character. When the function returns, this variable contains the length of the class string
 *   stored in the buffer. The count returned does not include the terminating null character. If the
 *   buffer is not big enough, the function returns ERROR_MORE_DATA, and the variable contains the
 *   size of the string, in characters, without counting the null character. If lpClass is NULL,
 *   lpcbClass can be NULL. If the lpClass parameter is a valid address, but this parameter is not,
 *   the function returns ERROR_INVALID_PARAMETER.
 * @param lpReserved [in] Reserved; set to NULL.
 * @param lpcSubKeys [out] Pointer to a variable that receives the number of subkeys contained by
 *   the specified key. This parameter can be NULL.
 * @param lpcbMaxSubKeyLen [out] Pointer to a variable that receives the length, in characters, of
 *   the key's subkey with the longest name. The count returned does not include the terminating null
 *   character. This parameter can be NULL.
 * @param lpcbMaxClassLen [out] Pointer to a variable that receives the length, in characters, of
 *   the longest string specifying a subkey class. The count returned does not include the terminating
 *   null character. This parameter can be NULL.
 * @param lpcValues [out] Pointer to a variable that receives the number of values associated with
 *   the key. This parameter can be NULL.
 * @param lpcbMaxValueNameLen [out] Pointer to a variable that receives the length, in characters,
 *   of the key's longest value name. The count returned does not include the terminating null
 *   character. This parameter can be NULL.
 * @param lpcbMaxValueLen [out] Pointer to a variable that receives the length, in bytes, of the
 *   longest data component among the values of the key. This parameter can be NULL.
 * @param lpcbSecurityDescriptor [in] Not used; set to NULL.
 * @param lpftLastWriteTime [in] Ignored; set to NULL.
 *
 * @return ERROR_SUCCESS indicates success. A nonzero error code defined in Winerror.h indicates
 *   failure. To get a generic description of the error, call FormatMessage with the
 *   FORMAT_MESSAGE_FROM_SYSTEM flag set.
 *
 * The key identified by the hKey parameter must have been opened with KEY_QUERY_VALUE access
 * (KEY_READ access includes KEY_QUERY_VALUE access).
 */
#define RegQueryInfoKey  RegQueryInfoKeyW
/**
 * This function retrieves the type and data for a specified value name associated with an open
 * registry key.
 *
 * @param hKey [in] Handle to a currently open key or any of the following predefined reserved
 *   handle values: HKEY_CLASSES_ROOT HKEY_CURRENT_USER HKEY_LOCAL_MACHINE HKEY_USERS
 * @param lpValueName [in] Pointer to a string containing the name of the value to query. If this
 *   parameter is NULL or an empty string, the function retrieves the type and data for the key's
 *   unnamed value. A registry key does not automatically have an unnamed or default value. Unnamed
 *   values can be of any type.
 * @param lpReserved [in] Reserved; set to NULL.
 * @param lpType [out] Pointer to a variable that receives the type of data associated with the
 *   specified value. The value returned through this parameter will be one of the following: Value
 *   Description REG_BINARY Binary data in any form. REG_DWORD A 32-bit number.
 *   REG_DWORD_LITTLE_ENDIAN A 32-bit number in little-endian format. This is equivalent to REG_DWORD.
 *   In little-endian format, a multi-byte value is stored in memory from the lowest byte (the "little
 *   end") to the highest byte. For example, the value 0x12345678 is stored as (0x78 0x56 0x34 0x12)
 *   in little-endian format. REG_DWORD_BIG_ENDIAN A 32-bit number in big-endian format. In big-endian
 *   format, a multi-byte value is stored in memory from the highest byte (the "big end") to the
 *   lowest byte. For example, the value 0x12345678 is stored as (0x12 0x34 0x56 0x78) in big-endian
 *   format. REG_EXPAND_SZ A null-terminated string that contains unexpanded references to environment
 *   variables (for example, "%PATH%"). REG_LINK A Unicode symbolic link. Used internally;
 *   applications should not use this type. REG_MULTI_SZ An array of null-terminated strings,
 *   terminated by two null characters. REG_NONE No defined value type. REG_RESOURCE_LIST A
 *   device-driver resource list. REG_SZ A null-terminated string. The lpType parameter can be NULL if
 *   the type is not required.
 * @param lpData [out] Pointer to a buffer that receives the value's data. This parameter can be
 *   NULL if the data is not required.
 * @param lpcbData [in/out] Pointer to a variable that specifies the size, in bytes, of the buffer
 *   pointed to by the lpData parameter. When the function returns, this variable contains the size of
 *   the data copied to lpData. If the data has the REG_SZ, REG_MULTI_SZ or REG_EXPAND_SZ type, then
 *   lpcbData will also include the size of the terminating null character. The lpcbData parameter can
 *   be NULL only if lpData is NULL. If the buffer specified by lpData parameter is not large enough
 *   to hold the data, the function returns the value ERROR_MORE_DATA, and stores the required buffer
 *   size, in bytes, into the variable pointed to by lpcbData. If lpData is NULL, and lpcbData is
 *   non-NULL, the function returns ERROR_SUCCESS, and stores the size of the data, in bytes, in the
 *   variable pointed to by lpcbData. This lets an application determine the best way to allocate a
 *   buffer for the value's data.
 *
 * @return ERROR_SUCCESS indicates success. A nonzero error code defined in Winerror.h indicates
 *   failure. To get a generic description of the error, call FormatMessage with the
 *   FORMAT_MESSAGE_FROM_SYSTEM flag set.
 *
 * The key identified by hKey must have been opened with KEY_QUERY_VALUE access. To open the key,
 * use the RegCreateKeyEx or RegOpenKeyEx function.
 *
 * Windows CE supports only the Unicode version of this function.
 */
#define RegQueryValueEx  RegQueryValueExW
/**
 * This function stores data in the value field of an open registry key. It can also set additional
 * value and type information for the specified key.
 *
 * @param hKey [in] Handle to a currently open key or any of the following predefined reserved
 *   handle values: HKEY_CLASSES_ROOT HKEY_CURRENT_USER HKEY_LOCAL_MACHINE HKEY_USERS
 * @param lpValueName [in] Pointer to a string containing the name of the value to set. If a value
 *   with this name is not already present in the key, the function adds it to the key. If this
 *   parameter is NULL or an empty string, the function sets the type and data for the key's unnamed
 *   value. Registry keys do not have default values, but they can have one unnamed value, which can
 *   be of any type. The maximum length of a value name is 255, not including the terminating NULL
 *   character.
 * @param Reserved [in] Reserved; must be zero.
 * @param dwType [in] Specifies the type of information to be stored as the value's data. This
 *   parameter can be one of the following values: Value Description REG_BINARY Binary data in any
 *   form. REG_DWORD A 32-bit number. REG_DWORD_LITTLE_ENDIAN A 32-bit number in little-endian format.
 *   This is equivalent to REG_DWORD. In little-endian format, a multi-byte value is stored in memory
 *   from the lowest byte (the "little end") to the highest byte. For example, the value 0x12345678 is
 *   stored as (0x78 0x56 0x34 0x12) in little-endian format. REG_DWORD_BIG_ENDIAN A 32-bit number in
 *   big-endian format. In big-endian format, a multi-byte value is stored in memory from the highest
 *   byte (the "big end") to the lowest byte. For example, the value 0x12345678 is stored as (0x12
 *   0x34 0x56 0x78) in big-endian format. REG_EXPAND_SZ A null-terminated string that contains
 *   unexpanded references to environment variables (for example, "%PATH%"). REG_LINK A Unicode
 *   symbolic link. Used internally; applications should not use this type. REG_MULTI_SZ An array of
 *   null-terminated strings, terminated by two null characters. REG_NONE No defined value type.
 *   REG_RESOURCE_LIST A device-driver resource list. REG_SZ A null-terminated string. Do not use the
 *   REG_SZ type to store hard-coded paths to the system root directory or to the drive containing the
 *   system files. Instead, use the REG_EXPAND_SZ type with environment variables such as
 *   "%SystemRoot%". This ensures that the path will be up-to-date even if the user remaps the system
 *   drive to a different drive letter.
 * @param lpData [in] Pointer to a buffer containing the data to be stored with the specified value
 *   name.
 * @param cbData [in] Specifies the size, in bytes, of the information pointed to by the lpData
 *   parameter. If the data is of type REG_SZ, REG_EXPAND_SZ, or REG_MULTI_SZ, cbData must include the
 *   size of the terminating null character. The maximum size of data allowed in Windows CE is 4 KB.
 *
 * @return ERROR_SUCCESS indicates success. A nonzero error code defined in Winerror.h indicates
 *   failure. To get a generic description of the error, call FormatMessage with the
 *   FORMAT_MESSAGE_FROM_SYSTEM flag set.
 *
 * Value lengths are limited by available memory. Long values (more than 2048 bytes) should be
 * stored as files with the filenames stored in the registry. This helps the registry perform
 * efficiently. Application elements such as icons, bitmaps, and executable files should be stored
 * as files and not be placed in the registry.
 *
 * The key identified by the hKey parameter must have been opened with KEY_SET_VALUE access. To open
 * the key, use the RegCreateKeyEx or RegOpenKeyEx function.
 *
 * Windows CE supports only the Unicode version of this function.
 */
#define RegSetValueEx  RegSetValueExW
#else
/**
 * This function creates the specified key. If the key already exists in the registry, the function
 * opens it. A remote application interface (RAPI) version of this function exists, and it is called
 * CeRegCreateKeyEx.
 *
 * @param hKey [in] Handle to a currently open key or one of the following predefined reserved
 *   handle values: HKEY_CLASSES_ROOT HKEY_CURRENT_USER HKEY_LOCAL_MACHINE HKEY_USERS Windows CE does
 *   not support the HKEY_CURRENT_CONFIG, HKEY_PERFORMANCE_DATA, or HKEY_DYN_DATA predefined reserved
 *   handle values. The key opened or created by the RegCreateKeyEx function is a subkey of the key
 *   identified by the hKey parameter.
 * @param lpSubKey [in] Pointer to a null-terminated string specifying the name of a subkey that
 *   this function opens or creates. The subkey specified must be a subkey of the key identified by
 *   the hKey parameter. This subkey must not begin with the backslash character ('\'). This parameter
 *   cannot be NULL. In Windows CE, the maximum length of a key name is 255 characters, not including
 *   the terminating NULL character. You can also only nest 16 levels of sub-keys in Windows CE.
 * @param Reserved [in] Reserved; set to 0.
 * @param lpClass [in] Pointer to a null-terminated string that specifies the class (object type) of
 *   this key. This parameter is ignored if the key already exists. In Windows CE, the maximum length
 *   of a class string is 255 characters, not including the terminating NULL character.
 * @param dwOptions [in] Ignored; set to 0 to ensure compatibility with future versions of Windows
 *   CE.
 * @param samDesired [in] Ignored; set to 0 to ensure compatibility with future versions of Windows
 *   CE.
 * @param lpSecurityAttributes [in] Set to NULL. Windows CE automatically assigns the key a default
 *   security descriptor.
 * @param phkResult [out] Pointer to a variable that receives a handle to the opened or created key.
 *   When you no longer need the returned handle, call the RegCloseKey function to close it.
 * @param lpdwDisposition [out] Pointer to a variable that receives one of the following disposition
 *   values: Value Description REG_CREATED_NEW_KEY The key did not exist and was created.
 *   REG_OPENED_EXISTING_KEY The key existed and was simply opened without being changed.
 *
 * @return ERROR_SUCCESS indicates success. A nonzero error code defined in Winerror.h indicates
 *   failure. To get a generic description of the error, call FormatMessage with the
 *   FORMAT_MESSAGE_FROM_SYSTEM flag set.
 *
 * The key that the RegCreateKeyEx function creates has no values. An application can use the
 * RegSetValueEx function to set key values.
 *
 * The key identified by the hKey parameter must have been opened with KEY_CREATE_SUB_KEY access. To
 * open the key, use the RegCreateKeyEx or RegOpenKeyEx function.
 *
 * RegCreateKeyEx can create keys under the HKEY_LOCAL_MACHINE and HKEY_USERS registries.
 *
 * An application can use RegCreateKeyEx to temporarily lock a portion of the registry. When the
 * locking process creates a new key, it receives the disposition value REG_CREATED_NEW_KEY,
 * indicating that it "owns" the lock. Another process attempting to create the same key receives
 * the disposition value REG_OPENED_EXISTING_KEY, indicating that another process already owns the
 * lock.
 */
#define RegCreateKeyEx  RegCreateKeyExA
/**
 * This function deletes a named subkey from the specified registry key. The subkey to be deleted
 * cannot have any subkeys.
 *
 * @param hKey [in] Handle to a currently open key or one of the following predefined reserved
 *   handle values: HKEY_CLASSES_ROOT HKEY_CURRENT_USER HKEY_LOCAL_MACHINE HKEY_USERS The key
 *   specified by the lpSubKey parameter must be a subkey of the key identified by hKey.
 * @param lpSubKey [in] Pointer to a null-terminated string specifying the name of the key to
 *   delete. This parameter cannot be NULL.
 *
 * @return ERROR_SUCCESS indicates success. A nonzero error code defined in Winerror.h indicates
 *   failure. To get a generic description of the error, call FormatMessage with the
 *   FORMAT_MESSAGE_FROM_SYSTEM flag set.
 *
 * If the function succeeds, RegDeleteKey removes the specified key from the registry. The entire
 * key, including all of its values, is removed. An application cannot call RegDeleteKey for a key
 * that an application currently has open.
 *
 * To open the key, use the RegCreateKeyEx or RegOpenKeyEx function.
 */
#define RegDeleteKey  RegDeleteKeyA
/**
 * This function removes a named value from the specified registry key. A remote application
 * interface (RAPI) version of this function exists, and it is called CeRegDeleteValue.
 *
 * @param hKey [in] Handle to a currently open key or any of the following predefined reserved
 *   handle values: HKEY_CLASSES_ROOT HKEY_CURRENT_USER HKEY_LOCAL_MACHINE HKEY_USERS
 * @param lpValueName [in] Pointer to a null-terminated string that names the value to remove. If
 *   this parameter is NULL or points to an empty string, the default value of the key is removed. A
 *   default value is create by calling RegCreateValueEx with a NULL or empty string value name.
 *
 * @return ERROR_SUCCESS indicates success. A nonzero error code defined in Winerror.h indicates
 *   failure. To get a generic description of the error, call FormatMessage with the
 *   FORMAT_MESSAGE_FROM_SYSTEM flag set.
 *
 * The key identified by the hKey parameter must have been opened with KEY_SET_VALUE access
 * (KEY_WRITE access includes KEY_SET_VALUE access).
 */
#define RegDeleteValue  RegDeleteValueA
/**
 * This function enumerates the values for the specified open registry key. RegEnumValue copies one
 * indexed value name and data block for the key each time it is called.
 *
 * @param hKey [in] Handle to a currently open key or one of the following predefined reserved
 *   handle values: HKEY_CLASSES_ROOT HKEY_CURRENT_USER HKEY_LOCAL_MACHINE HKEY_USERS The enumerated
 *   values are associated with the key identified by hKey.
 * @param dwIndex [in] Specifies the index of the value to retrieve. This parameter should be zero
 *   for the first call to the RegEnumValue function and then be incremented for subsequent calls.
 *   Because values are not ordered, any new value will have an arbitrary index. This means that the
 *   function may return values in any order.
 * @param lpValueName [out] Pointer to a buffer that receives the name of the value, including the
 *   terminating null character.
 * @param lpcbValueName [in/out] Pointer to a variable that specifies the size, in characters, of
 *   the buffer pointed to by the lpValueName parameter. This size should include the terminating null
 *   character. When the function returns, the variable pointed to by lpcbValueName contains the
 *   number of characters stored in the buffer. The count returned does not include the terminating
 *   null character.
 * @param lpReserved [in] Reserved; set to NULL.
 * @param lpType [out] Pointer to a variable that receives the type code for the value entry. The
 *   type code can be one of the following values: Value Description REG_BINARY Binary data in any
 *   form. REG_DWORD A 32-bit number. REG_DWORD_LITTLE_ENDIAN A 32-bit number in little-endian format.
 *   This is equivalent to REG_DWORD. In little-endian format, a multi-byte value is stored in memory
 *   from the lowest byte (the "little end") to the highest byte. For example, the value 0x12345678 is
 *   stored as (0x78 0x56 0x34 0x12) in little-endian format. REG_DWORD_BIG_ENDIAN A 32-bit number in
 *   big-endian format. In big-endian format, a multi-byte value is stored in memory from the highest
 *   byte (the "big end") to the lowest byte. For example, the value 0x12345678 is stored as (0x12
 *   0x34 0x56 0x78) in big-endian format. REG_EXPAND_SZ A null-terminated string that contains
 *   unexpanded references to environment variables (for example, "%PATH%"). It will be a Unicode or
 *   ANSI string depending on whether you use the Unicode or ANSI functions. REG_LINK A Unicode
 *   symbolic link. Used internally; applications should not use this type. REG_MULTI_SZ An array of
 *   null-terminated strings, terminated by two null characters. REG_NONE No defined value type.
 *   REG_RESOURCE_LIST A device-driver resource list. REG_SZ A null-terminated string. It will be a
 *   Unicode or ANSI string, depending on whether you use the Unicode or ANSI functions. The lpType
 *   parameter can be NULL if the type code is not required.
 * @param lpData [out] Pointer to a buffer that receives the data for the value entry. This
 *   parameter can be NULL if the data is not required.
 * @param lpcbData [in/out] Pointer to a variable that specifies the size, in bytes, of the buffer
 *   pointed to by the lpData parameter. When the function returns, the variable pointed to by the
 *   lpcbData parameter contains the number of bytes stored in the buffer. This parameter can be NULL,
 *   only if lpData is NULL.
 *
 * @return ERROR_SUCCESS indicates success. A nonzero error code defined in Winerror.h indicates
 *   failure. To get a generic description of the error, call FormatMessage with the
 *   FORMAT_MESSAGE_FROM_SYSTEM flag set.
 *
 * To enumerate values, an application should initially call the RegEnumValue function with the
 * dwIndex parameter set to zero. The application should then increment dwIndex and call the
 * RegEnumValue function until there are no more values (until the function returns
 * ERROR_NO_MORE_ITEMS).
 *
 * The application can also set dwIndex to the index of the last value on the first call to the
 * function and decrement the index until the value with index 0 is enumerated. To retrieve the
 * index of the last value, use the RegQueryInfoKey function.
 *
 * While using RegEnumValue, an application should not call any registration functions that might
 * change the key being queried.
 *
 * The key identified by the hKey parameter must have been opened with KEY_QUERY_VALUE access. To
 * open the key, use the RegCreateKeyEx or RegOpenKeyEx function.
 *
 * To determine the maximum size of the name and data buffers, use the RegQueryInfoKey function.
 */
#define RegEnumValue  RegEnumValueA
/**
 * This function enumerates subkeys of the specified open registry key. RegEnumKeyEx retrieves
 * information about one subkey each time it is called and it retrieves the class name of the subkey
 * and the time it was last modified.
 *
 * @param hKey [in] Handle to a currently open key or one of the following predefined reserved
 *   handle values: HKEY_CLASSES_ROOT HKEY_CURRENT_USER HKEY_LOCAL_MACHINE HKEY_USERS The enumerated
 *   keys are subkeys of the key identified by hKey.
 * @param dwIndex [in] Specifies the index of the subkey to retrieve. This parameter should be zero
 *   for the first call to the RegEnumKeyEx function and then incremented for subsequent calls.
 *   Because subkeys are not ordered, any new subkey will have an arbitrary index. This means that the
 *   function may return subkeys in any order.
 * @param lpName [out] Pointer to a buffer that receives the name of the subkey, including the
 *   terminating null character. The function copies only the name of the subkey, not the full key
 *   hierarchy, to the buffer.
 * @param lpcbName [in/out] Pointer to a variable that specifies the size, in characters, of the
 *   buffer specified by the lpName parameter. This size should include the terminating null
 *   character. When the function returns, the variable pointed to by lpcbName contains the number of
 *   characters stored in the buffer. The count returned does not include the terminating null
 *   character.
 * @param lpReserved [in] Reserved; set to NULL.
 * @param lpClass [out] Pointer to a buffer that contains the class of the enumerated subkey when
 *   the function returns. This parameter can be NULL if the class is not required.
 * @param lpcbClass [in/out] Pointer to a variable that specifies the size, in characters, of the
 *   buffer specified by the lpClass parameter. The size should include the terminating null
 *   character. When the function returns, lpcbClass contains the number of characters stored in the
 *   buffer. The count returned does not include the terminating null character. This parameter can be
 *   NULL only if lpClass is NULL.
 * @param lpftLastWriteTime [in] Ignored; set to NULL.
 *
 * @return ERROR_SUCCESS indicates success. A nonzero error code defined in Winerror.h indicates
 *   failure. To get a generic description of the error, call FormatMessage with the
 *   FORMAT_MESSAGE_FROM_SYSTEM flag set.
 *
 * To enumerate subkeys, an application should initially call the RegEnumKeyEx function with the
 * dwIndex parameter set to zero. An application should then increment the dwIndex parameter and
 * call RegEnumKeyEx until there are no more subkeys (until the function returns
 * ERROR_NO_MORE_ITEMS).
 *
 * An application can also set dwIndex to the index of the last subkey on the first call to the
 * function and decrement the index until the subkey with the index 0 is enumerated. To retrieve the
 * index of the last subkey, use the RegQueryInfoKey function.
 *
 * While an application is using the RegEnumKeyEx function, it should not make calls to any
 * registration functions that might change the key being enumerated.
 *
 * The key identified by hKey must have been opened with KEY_ENUMERATE_SUB_KEYS access (KEY_READ
 * includes KEY_ENUMERATE_SUB_KEYS). Use the RegCreateKeyEx or RegOpenKeyEx function to open the
 * key.
 */
#define RegEnumKeyEx  RegEnumKeyExA
/**
 * This function opens the specified key.
 *
 * @param hKey [in] Handle to a currently open key or any of the following predefined reserved
 *   handle values: HKEY_CLASSES_ROOT HKEY_CURRENT_USER HKEY_LOCAL_MACHINE HKEY_USERS Windows CE does
 *   not support the HKEY_CURRENT_CONFIG, HKEY_PERFORMANCE_DATA, or HKEY_DYN_DATA predefined reserved
 *   handle values.
 * @param lpSubKey [in] Pointer to a null-terminated string containing the name of the subkey to
 *   open. If this parameter is NULL or a pointer to an empty string, the function will open a new
 *   handle to the key identified by the hKey parameter. In this case, the function will not close the
 *   handles previously opened.
 * @param ulOptions [in] Reserved; set to 0.
 * @param samDesired [in] Not supported; set to zero.
 * @param phkResult [out] Pointer to a variable that receives a handle to the opened key. When you
 *   no longer need the returned handle, call the RegCloseKey function to close it.
 *
 * @return ERROR_SUCCESS indicates success. A nonzero error code defined in Winerror.h indicates
 *   failure. To get a generic description of the error, call FormatMessage with the
 *   FORMAT_MESSAGE_FROM_SYSTEM flag set.
 *
 * Unlike the RegCreateKeyEx function, the RegOpenKeyEx function does not create the specified key
 * if the key does not exist in the registry.
 */
#define RegOpenKeyEx  RegOpenKeyExA
/**
 * This function retrieves information about a specified registry key.
 *
 * @param hKey [in] Handle to a currently open key or any of the following predefined reserved
 *   handle values: HKEY_CLASSES_ROOT HKEY_CURRENT_USER HKEY_LOCAL_MACHINE HKEY_USERS
 * @param lpClass [out] Pointer to a buffer that receives the key's class name. This parameter can
 *   be NULL.
 * @param lpcbClass [in/out] Pointer to a variable that specifies the size, in characters, of the
 *   buffer pointed to by the lpClass parameter. This size should include the terminating null
 *   character. When the function returns, this variable contains the length of the class string
 *   stored in the buffer. The count returned does not include the terminating null character. If the
 *   buffer is not big enough, the function returns ERROR_MORE_DATA, and the variable contains the
 *   size of the string, in characters, without counting the null character. If lpClass is NULL,
 *   lpcbClass can be NULL. If the lpClass parameter is a valid address, but this parameter is not,
 *   the function returns ERROR_INVALID_PARAMETER.
 * @param lpReserved [in] Reserved; set to NULL.
 * @param lpcSubKeys [out] Pointer to a variable that receives the number of subkeys contained by
 *   the specified key. This parameter can be NULL.
 * @param lpcbMaxSubKeyLen [out] Pointer to a variable that receives the length, in characters, of
 *   the key's subkey with the longest name. The count returned does not include the terminating null
 *   character. This parameter can be NULL.
 * @param lpcbMaxClassLen [out] Pointer to a variable that receives the length, in characters, of
 *   the longest string specifying a subkey class. The count returned does not include the terminating
 *   null character. This parameter can be NULL.
 * @param lpcValues [out] Pointer to a variable that receives the number of values associated with
 *   the key. This parameter can be NULL.
 * @param lpcbMaxValueNameLen [out] Pointer to a variable that receives the length, in characters,
 *   of the key's longest value name. The count returned does not include the terminating null
 *   character. This parameter can be NULL.
 * @param lpcbMaxValueLen [out] Pointer to a variable that receives the length, in bytes, of the
 *   longest data component among the values of the key. This parameter can be NULL.
 * @param lpcbSecurityDescriptor [in] Not used; set to NULL.
 * @param lpftLastWriteTime [in] Ignored; set to NULL.
 *
 * @return ERROR_SUCCESS indicates success. A nonzero error code defined in Winerror.h indicates
 *   failure. To get a generic description of the error, call FormatMessage with the
 *   FORMAT_MESSAGE_FROM_SYSTEM flag set.
 *
 * The key identified by the hKey parameter must have been opened with KEY_QUERY_VALUE access
 * (KEY_READ access includes KEY_QUERY_VALUE access).
 */
#define RegQueryInfoKey  RegQueryInfoKeyA
/**
 * This function retrieves the type and data for a specified value name associated with an open
 * registry key.
 *
 * @param hKey [in] Handle to a currently open key or any of the following predefined reserved
 *   handle values: HKEY_CLASSES_ROOT HKEY_CURRENT_USER HKEY_LOCAL_MACHINE HKEY_USERS
 * @param lpValueName [in] Pointer to a string containing the name of the value to query. If this
 *   parameter is NULL or an empty string, the function retrieves the type and data for the key's
 *   unnamed value. A registry key does not automatically have an unnamed or default value. Unnamed
 *   values can be of any type.
 * @param lpReserved [in] Reserved; set to NULL.
 * @param lpType [out] Pointer to a variable that receives the type of data associated with the
 *   specified value. The value returned through this parameter will be one of the following: Value
 *   Description REG_BINARY Binary data in any form. REG_DWORD A 32-bit number.
 *   REG_DWORD_LITTLE_ENDIAN A 32-bit number in little-endian format. This is equivalent to REG_DWORD.
 *   In little-endian format, a multi-byte value is stored in memory from the lowest byte (the "little
 *   end") to the highest byte. For example, the value 0x12345678 is stored as (0x78 0x56 0x34 0x12)
 *   in little-endian format. REG_DWORD_BIG_ENDIAN A 32-bit number in big-endian format. In big-endian
 *   format, a multi-byte value is stored in memory from the highest byte (the "big end") to the
 *   lowest byte. For example, the value 0x12345678 is stored as (0x12 0x34 0x56 0x78) in big-endian
 *   format. REG_EXPAND_SZ A null-terminated string that contains unexpanded references to environment
 *   variables (for example, "%PATH%"). REG_LINK A Unicode symbolic link. Used internally;
 *   applications should not use this type. REG_MULTI_SZ An array of null-terminated strings,
 *   terminated by two null characters. REG_NONE No defined value type. REG_RESOURCE_LIST A
 *   device-driver resource list. REG_SZ A null-terminated string. The lpType parameter can be NULL if
 *   the type is not required.
 * @param lpData [out] Pointer to a buffer that receives the value's data. This parameter can be
 *   NULL if the data is not required.
 * @param lpcbData [in/out] Pointer to a variable that specifies the size, in bytes, of the buffer
 *   pointed to by the lpData parameter. When the function returns, this variable contains the size of
 *   the data copied to lpData. If the data has the REG_SZ, REG_MULTI_SZ or REG_EXPAND_SZ type, then
 *   lpcbData will also include the size of the terminating null character. The lpcbData parameter can
 *   be NULL only if lpData is NULL. If the buffer specified by lpData parameter is not large enough
 *   to hold the data, the function returns the value ERROR_MORE_DATA, and stores the required buffer
 *   size, in bytes, into the variable pointed to by lpcbData. If lpData is NULL, and lpcbData is
 *   non-NULL, the function returns ERROR_SUCCESS, and stores the size of the data, in bytes, in the
 *   variable pointed to by lpcbData. This lets an application determine the best way to allocate a
 *   buffer for the value's data.
 *
 * @return ERROR_SUCCESS indicates success. A nonzero error code defined in Winerror.h indicates
 *   failure. To get a generic description of the error, call FormatMessage with the
 *   FORMAT_MESSAGE_FROM_SYSTEM flag set.
 *
 * The key identified by hKey must have been opened with KEY_QUERY_VALUE access. To open the key,
 * use the RegCreateKeyEx or RegOpenKeyEx function.
 *
 * Windows CE supports only the Unicode version of this function.
 */
#define RegQueryValueEx  RegQueryValueExA
/**
 * This function stores data in the value field of an open registry key. It can also set additional
 * value and type information for the specified key.
 *
 * @param hKey [in] Handle to a currently open key or any of the following predefined reserved
 *   handle values: HKEY_CLASSES_ROOT HKEY_CURRENT_USER HKEY_LOCAL_MACHINE HKEY_USERS
 * @param lpValueName [in] Pointer to a string containing the name of the value to set. If a value
 *   with this name is not already present in the key, the function adds it to the key. If this
 *   parameter is NULL or an empty string, the function sets the type and data for the key's unnamed
 *   value. Registry keys do not have default values, but they can have one unnamed value, which can
 *   be of any type. The maximum length of a value name is 255, not including the terminating NULL
 *   character.
 * @param Reserved [in] Reserved; must be zero.
 * @param dwType [in] Specifies the type of information to be stored as the value's data. This
 *   parameter can be one of the following values: Value Description REG_BINARY Binary data in any
 *   form. REG_DWORD A 32-bit number. REG_DWORD_LITTLE_ENDIAN A 32-bit number in little-endian format.
 *   This is equivalent to REG_DWORD. In little-endian format, a multi-byte value is stored in memory
 *   from the lowest byte (the "little end") to the highest byte. For example, the value 0x12345678 is
 *   stored as (0x78 0x56 0x34 0x12) in little-endian format. REG_DWORD_BIG_ENDIAN A 32-bit number in
 *   big-endian format. In big-endian format, a multi-byte value is stored in memory from the highest
 *   byte (the "big end") to the lowest byte. For example, the value 0x12345678 is stored as (0x12
 *   0x34 0x56 0x78) in big-endian format. REG_EXPAND_SZ A null-terminated string that contains
 *   unexpanded references to environment variables (for example, "%PATH%"). REG_LINK A Unicode
 *   symbolic link. Used internally; applications should not use this type. REG_MULTI_SZ An array of
 *   null-terminated strings, terminated by two null characters. REG_NONE No defined value type.
 *   REG_RESOURCE_LIST A device-driver resource list. REG_SZ A null-terminated string. Do not use the
 *   REG_SZ type to store hard-coded paths to the system root directory or to the drive containing the
 *   system files. Instead, use the REG_EXPAND_SZ type with environment variables such as
 *   "%SystemRoot%". This ensures that the path will be up-to-date even if the user remaps the system
 *   drive to a different drive letter.
 * @param lpData [in] Pointer to a buffer containing the data to be stored with the specified value
 *   name.
 * @param cbData [in] Specifies the size, in bytes, of the information pointed to by the lpData
 *   parameter. If the data is of type REG_SZ, REG_EXPAND_SZ, or REG_MULTI_SZ, cbData must include the
 *   size of the terminating null character. The maximum size of data allowed in Windows CE is 4 KB.
 *
 * @return ERROR_SUCCESS indicates success. A nonzero error code defined in Winerror.h indicates
 *   failure. To get a generic description of the error, call FormatMessage with the
 *   FORMAT_MESSAGE_FROM_SYSTEM flag set.
 *
 * Value lengths are limited by available memory. Long values (more than 2048 bytes) should be
 * stored as files with the filenames stored in the registry. This helps the registry perform
 * efficiently. Application elements such as icons, bitmaps, and executable files should be stored
 * as files and not be placed in the registry.
 *
 * The key identified by the hKey parameter must have been opened with KEY_SET_VALUE access. To open
 * the key, use the RegCreateKeyEx or RegOpenKeyEx function.
 *
 * Windows CE supports only the Unicode version of this function.
 */
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

