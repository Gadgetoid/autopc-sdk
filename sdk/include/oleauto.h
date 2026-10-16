//+---------------------------------------------------------------------------
//
//  Microsoft Windows
//  Copyright (C) Microsoft Corporation, 1992 - 1996.
//
//  File:       oleauto.h
//
//  Contents:   Defines Ole Automation support function prototypes, constants
//
//----------------------------------------------------------------------------

#if !defined( _OLEAUTO_H_ )
#define _OLEAUTO_H_

// Set packing to 8 for ISV, and Win95 support
#ifndef RC_INVOKED
#include <pshpack8.h>
#endif // RC_INVOKED

//  Definition of the OLE Automation APIs, and macros.

#ifdef _OLEAUT32_
#define WINOLEAUTAPI        STDAPI
#define WINOLEAUTAPI_(type) STDAPI_(type)
#else
#define WINOLEAUTAPI        EXTERN_C DECLSPEC_IMPORT HRESULT STDAPICALLTYPE
#define WINOLEAUTAPI_(type) EXTERN_C DECLSPEC_IMPORT type STDAPICALLTYPE
#endif

EXTERN_C const IID IID_StdOle;

#define STDOLE_MAJORVERNUM  0x1
#define STDOLE_MINORVERNUM  0x0
#define STDOLE_LCID         0x0000

// Version # of stdole2.tlb
#define STDOLE2_MAJORVERNUM 0x2
#define STDOLE2_MINORVERNUM 0x0
#define STDOLE2_LCID        0x0000

/* if not already picked up from olenls.h */
#ifndef _LCID_DEFINED
typedef DWORD LCID;
# define _LCID_DEFINED
#endif

#ifndef BEGIN_INTERFACE
#define BEGIN_INTERFACE
#define END_INTERFACE
#endif

/* pull in the MIDL generated header */
#include <oaidl.h>


/*---------------------------------------------------------------------*/
/*                            BSTR API                                 */
/*---------------------------------------------------------------------*/

/**
 * This function allocates a new string and copies the passed string into it. SysAllocString returns
 * null if there is insufficient memory or if a null pointer is passed in.
 *
 * @param sz Null-terminated string to copy. The sz parameter must be a Unicode string in 32-bit
 *   applications, and an ANSI string in 16-bit applications.
 *
 * @return A pointer to a BSTR that contains the string indicates success. NULL indicates that
 *   insufficient memory exists or the sz parameter was NULL.
 *
 * Windows CE supports only Unicode strings.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 *
 * You can free strings created with SysAllocString using SysFreeString.
 */
WINOLEAUTAPI_(BSTR) SysAllocString(const OLECHAR *);
/**
 * This function allocates a new BSTR and copies the passed string into it, then frees the BSTR
 * referenced by pbstr, and finally resets pbstr to point to the new BSTR.
 *
 * @param pbstr Pointer to a variable that contains a BSTR.
 * @param sz Null-terminated string to copy.
 *
 * @return FALSE indicates that insufficient memory exists.
 *
 * Windows CE supports only Unicode strings.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI_(INT)  SysReAllocString(BSTR *, const OLECHAR *);
/**
 * This function allocates a new string, copies cch characters from the passed string into it, and
 * then appends a null character.
 *
 * @param pch Pointer to cch characters to copy, or NULL to keep the string uninitialized.
 * @param cch Number of characters to copy from pch. A null character is placed afterwards,
 *   allocating a total of cch+1 characters.
 *
 * @return A pointer to a copy of the string indicates success. NULL indicates that insufficient
 *   memory exists.
 *
 * If pch is NULL, a string of the requested length is allocated, but not initialized. The pch
 * string can contain embedded null characters and does not need to end with a NULL. Free the
 * returned string later with SysFreeString.
 *
 * Windows CE supports only Unicode strings.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI_(BSTR) SysAllocStringLen(const OLECHAR *, UINT);
/**
 * This function creates a new BSTR that contains a specified number of characters from an old BSTR,
 * and frees the old BSTR.
 *
 * @param pbstr Pointer to a variable that contains a BSTR.
 * @param pch Pointer to cch characters to copy, or NULL to keep the string uninitialized.
 * @param cch Number of characters to copy from pch. A null character is placed afterward,
 *   allocating a total of cch+1 characters.
 *
 * @return TRUE indicates that the string is reallocated successfully. FALSE indicates that
 *   insufficient memory exists.
 *
 * The SysReAllocStringLen function allocates a new string, copies cch characters from the passed
 * string into it, and then appends a null character. Frees the BSTR referenced currently by pbstr,
 * and resets pbstr to point to the new BSTR. If pch is NULL, a string of length cch is allocated
 * but not initialized.
 *
 * The pch string can contain embedded null characters and does not need to end with a NULL.
 *
 * Windows CE supports only Unicode strings.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI_(INT)  SysReAllocStringLen(BSTR *, const OLECHAR *, UINT);
/**
 * This function frees a string allocated previously by SysAllocString, SysAllocStringByteLen,
 * SysReAllocString, SysAllocStringLen, or SysReAllocStringLen.
 *
 * @param bstr Unicode string that was allocated previously, or NULL. If NULL, the function simply
 *   returns.
 *
 * @return None.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI_(void) SysFreeString(BSTR);
/**
 * This function returns the length of a BSTR.
 *
 * @param bstr Unicode string that was allocated previously. It cannot be NULL.
 *
 * @return The number of characters in bstr, not including a terminating null character, indicates
 *   success.
 *
 * The returned value may be different from _fstrlen(bstr) if the BSTR was allocated with
 * Sys[Re]AllocStringLen or SysAllocStringByteLen, and the passed-in characters included a null
 * character in the first cch characters. For a BSTR allocated with Sys[Re]AllocStringLen or
 * SysAllocStringByteLen, the SysStringLen function always returns the number of characters
 * specified in the cch parameter at allocation time.
 *
 * Windows CE supports only Unicode strings.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI_(UINT) SysStringLen(BSTR);

#ifdef _WIN32
/**
 * This function returns the length (in bytes) of a BSTR.
 *
 * @param bstr Unicode string that was allocated previously. It cannot be NULL.
 *
 * @return The number of bytes in bstr, not including a terminating null character, indicates
 *   success.
 *
 * The returned value may be different from fstrlen(bstr) if the BSTR was allocated with
 * Sys[Re]AllocStringLen or SysAllocStringByteLen, and the passed-in characters included a null
 * character in the first len characters. For a BSTR allocated with Sys[Re]AllocStringLen or
 * SysAllocStringByteLen, this function always returns the number of bytes specified in the len
 * parameter at allocation time.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI_(UINT) SysStringByteLen(BSTR bstr);
/**
 * This function takes an ANSI string as input, and returns a BSTR that contains an ANSI string.
 * This function does not perform any ANSI to Unicode translation.
 *
 * @param psz Null-terminated string to copy, or NULL to keep the string uninitialized.
 * @param len Number of bytes to copy from psz. A null character is placed afterwards, allocating a
 *   total of len+1 bytes. Allocates a new string of len bytes, copies len bytes from the passed
 *   string into it, and then appends a null character. Valid only for 32-bit systems.
 *
 * @return A pointer to a copy of the string indicates success. NULL inidcates that insufficient
 *   memory exists.
 *
 * This function is provided to create BSTRs that contain binary data. You can use this type of BSTR
 * only in situations where it will not be translated from ANSI to Unicode, or vice versa.
 *
 * For example, do not use these BSTRs between a 16-bit and a 32-bit application running on a 32-bit
 * Windows system. The OLE 16-bit to 32-bit (and 32-bit to 16-bit) interoperability layer will
 * translate the BSTR and corrupt the binary data. The preferred method of passing binary data is to
 * use a SAFEARRAY of VT_UI1, which will not be translated by OLE.
 *
 * If psz is NULL, a string of the requested length is allocated, but not initialized. The string
 * psz can contain embedded null characters, and does not need to end with a NULL. Free the returned
 * string later with SysFreeString.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI_(BSTR) SysAllocStringByteLen(LPCSTR psz, UINT len);
#endif

/*---------------------------------------------------------------------*/
/*                            Time API                                 */
/*---------------------------------------------------------------------*/

WINOLEAUTAPI_(INT) DosDateTimeToVariantTime(USHORT wDosDate, USHORT wDosTime, DOUBLE * pvtime);

WINOLEAUTAPI_(INT) VariantTimeToDosDateTime(DOUBLE vtime, USHORT * pwDosDate, USHORT * pwDosTime);

#ifdef _WIN32
/**
 * This function converts the variant representation of time to system-time values.
 *
 * @param lpSystemTime Long pointer to the system time.
 * @param pvtime Void pointer to the returned variant time.
 *
 * A variant time is stored as an 8-byte real value (double), representing a date between January 1,
 * 1753 and December 31, 2078, inclusive. The value 2.0 represents January 1, 1900; 3.0 represents
 * January 2, 1900, and so on. Adding 1 to the value increments the date by a day. The fractional
 * part of the value represents the time of day. Therefore, 2.5 represents noon on January 1, 1900;
 * 3.25 represents 6:00 A.M. on January 2, 1900, and so on. Negative numbers represent the dates
 * prior to December 30, 1899.
 *
 * The SYSTEMTIME structure is useful for the following reasons:
 *
 * It spans all time/date periods. MS-DOS date/time is limited to representing only those dates
 * between 1/1/1980 and 12/31/2107.
 *
 * The date/time elements are all easily accessible without needing to do any bit decoding.
 *
 * The National Data Support data and time formatting functions GetDateFormat and GetTimeFormat take
 * a SYSTEMTIME value as input. For more information, see the Win32 Programmer's Reference in the
 * Win32 SDK.
 *
 * It is the default Win32 time/date data format supported by Windows NT and Windows 95.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI_(INT) SystemTimeToVariantTime(LPSYSTEMTIME lpSystemTime, DOUBLE *pvtime);
/**
 * This function converts the variant representation of time to system time values.
 *
 * @param vtime Specifies the variant time that will be converted.
 * @param lpSystemTime Long pointer to the location where the converted time is stored.
 *
 * @return The return value obtained from the returned INT is one of the following. Value
 *   Description True Success. False Failure.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 *
 * A variant time is stored as an 8-byte real value (double), representing a date between January 1,
 * 1753 and December 31, 2078, inclusive. The value 2.0 represents January 1, 1900; 3.0 represents
 * January 2, 1900, and so on. Adding 1 to the value increments the date by a day. The fractional
 * part of the value represents the time of day. Therefore, 2.5 represents noon on January 1, 1900;
 * 3.25 represents 6:00 A.M. on January 2, 1900, and so on. Negative numbers represent the dates
 * prior to December 30, 1899.
 *
 * Using the SYSTEMTIME structure is useful because:
 *
 * It spans all time/date periods. MS-DOS date/time is limited to representing only those dates
 * between 1/1/1980 and 12/31/2107.
 *
 * The date/time elements are all easily accessible without needing to do any bit decoding.
 *
 * The National Language Support data and time formatting functions GetDateFormat and GetTimeFormat
 * take a SYSTEMTIME value as input.
 *
 * It is the default Win32 time and date data format supported by Windows NT and Windows 95.
 */
WINOLEAUTAPI_(INT) VariantTimeToSystemTime(DOUBLE vtime, LPSYSTEMTIME lpSystemTime);
#endif


/*---------------------------------------------------------------------*/
/*                          SafeArray API                              */
/*---------------------------------------------------------------------*/

/**
 * This function allocates memory for a safe array descriptor, allowing the creation of safe arrays
 * that contain elements with data types other than those provided by SafeArrayCreate.
 *
 * @param cDims Number of dimensions of the array.
 * @param ppsaOut Pointer to a location in which to store the created array descriptor.
 *
 * @return One of the values obtained from the returned HRESULT and described in the following table
 *   is returned. Value Description S_OK Success. E_INVALIDARG The psa parameter was not a valid safe
 *   array descriptor. E_UNEXPECTED The array could not be locked.
 *
 * This function allows the creation of safe arrays that contain elements with data types other than
 * those provided by SafeArrayCreate. After creating an array descriptor using
 * SafeArrayAllocDescriptor, set the element size in the array descriptor, an call
 * SafeArrayAllocData to allocate memory for the array elements. Passing into this function any
 * invalid and, under some circumstances, NULL pointers will result in unexpected termination of the
 * application.
 */
WINOLEAUTAPI SafeArrayAllocDescriptor(UINT cDims, SAFEARRAY ** ppsaOut);
/**
 * This function allocates memory for a safe array, based on a descriptor created with
 * SafeArrayAllocDescriptor.
 *
 * @param psa Pointer to an array descriptor created by SafeArrayAllocDescriptor.
 *
 * @return One of the values obtained from the returned HRESULT and described in the following table
 *   is returned. Value Description S_OK Success. E_INVALIDARG The psa parameter was not a valid safe
 *   array descriptor. E_UNEXPECTED The array could not be locked.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI SafeArrayAllocData(SAFEARRAY * psa);
/**
 * This function creates a new array descriptor, allocates and initializes the data for the array,
 * and returns a pointer to the new array descriptor.
 *
 * @param vt Base type of the array (the VARTYPE of each element of the array). The VARTYPE is
 *   restricted to a subset of the variant types. Neither the VT_ARRAY nor the VT_BYREF flag can be
 *   set. VT_EMPTY and VT_NULL are not valid base types for the array. All other types are legal.
 * @param cDims Number of dimensions in the array. The number cannot be changed after the array is
 *   created.
 * @param rgsabound Pointer to a vector of bounds (one for each dimension) to allocate for the
 *   array.
 *
 * @return A pointer to the array descriptor indicates success. NULL indicates that the array could
 *   not be created.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI_(SAFEARRAY *) SafeArrayCreate(VARTYPE vt, UINT cDims, SAFEARRAYBOUND * rgsabound);
/**
 * This function creates a one-dimensional array whose lower bound is always zero. A safe array
 * created with SafeArrayCreateVector is a fixed size, so the constant FADF_FIXEDSIZE is always set.
 *
 * @param vt Base type of the array (the VARTYPE of each element of the array). The VARTYPE is
 *   restricted to a subset of the variant types. Neither the VT_ARRAY nor the VT_BYREF flag can be
 *   set. VT_EMPTY and VT_NULL are not valid base types for the array. All other types are legal.
 * @param lLbound Lower bound for the array; can be negative.
 * @param cElements Number of elements in the array.
 *
 * @return A pointer to the array descriptor indicates success. NULL indicates that the array could
 *   not be created.
 *
 * SafeArrayCreateVector allocates a single block of memory that contains a SAFEARRAY structure for
 * a single-dimension array (24 bytes), immediately followed by the array data. All of the existing
 * safe array functions work correctly for safe arrays that are allocated with
 * SafeArrayCreateVector.
 *
 * A SafeArrayCreateVector is allocated as a single block of memory. Both the SafeArray descriptor
 * and the array data block are allocated contiguously in one allocation, which speeds up array
 * allocation. However, a user can allocate the descriptor and data area separately using the
 * SafeArrayAllocDescriptor and SafeArrayAllocData calls. Passing into this function any invalid
 * and, under some circumstances, NULL pointers will result in unexpected termination of the
 * application.
 */
WINOLEAUTAPI_(SAFEARRAY *) SafeArrayCreateVector(VARTYPE vt, LONG lLbound, ULONG cElements);
/**
 * This function copies the source array to the target array after releasing any resources in the
 * target array. This function is similar to SafeArrayCopy, except that the target array has to be
 * set up by the caller. The target is not allocated or reallocated.
 *
 * @param psaSource Pointer to the safe array to be copied.
 * @param psaTarget On exit, pointer to the array referred to by psaTarget that contains a copy of
 *   the data in psaSource.
 *
 * @return One of the values obtained from the returned HRESULT and described in the following table
 *   is returned. Value Description S_OK Success. E_INVALIDARG The psa parameter was not a valid
 *   safearray descriptor. E_OUTOFMEMORY Insufficient memory to create the copy.
 *
 * Visual Basic for Applications and Automation use the same set of rules with cases in which the
 * size or types of source and destination arrays do not match. The rules of Visual Basic are
 * described in the following comments. Passing into this function any invalid and, under some
 * circumstances, NULL pointers will result in unexpected termination of the application.
 */
WINOLEAUTAPI SafeArrayCopyData(SAFEARRAY *psaSource, SAFEARRAY *psaTarget);
/**
 * This function destroys a decriptor of a safe array.
 *
 * @param psa Pointer to a safe array descriptor.
 *
 * @return One of the values obtained from the returned HRESULT and described in the following table
 *   is returned. Value Description S_OK Success. DISP_E_ARRAYISLOCKED The array is currently locked.
 *   E_INVALIDARG The item pointed to by psa is not a safe array descriptor.
 *
 * This function is typically used to destroy the descriptor of a safe array that contains elements
 * with data types other than variants. Destroying the array descriptor does not destroy the
 * elements in the array. Before destroying the array descriptor, call SafeArrayDestroyData to free
 * the elements.
 */
WINOLEAUTAPI SafeArrayDestroyDescriptor(SAFEARRAY * psa);
/**
 * This function destroys all the data in a safe array.
 *
 * @param psa Pointer to an array descriptor.
 *
 * @return One of the values obtained from the returned HRESULT and described in the following table
 *   is returned. Value Description S_OK Success. DISP_E_ARRAYISLOCKED The array is currently locked.
 *   E_INVALIDARG The item pointed to by psa is not a safe array descriptor.
 *
 * This function is typically used when freeing safe arrays that contain elements with data types
 * other than variants. If objects are stored in the array, Release is called on each object in the
 * array.
 */
WINOLEAUTAPI SafeArrayDestroyData(SAFEARRAY * psa);
/**
 * This function destroys an existing array descriptor and all of the data in the array. If objects
 * are stored in the array, Release is called on each object in the array.
 *
 * @param psa Pointer to an array descriptor created by SafeArrayCreate.
 *
 * @return One of the values obtained from the returned HRESULT and described in the following table
 *   is returned. Value Description S_OK Success. DISP_E_ARRAYISLOCKED The array is currently locked.
 *   E_INVALIDARG The item pointed to by psa is not a safe array descriptor.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI SafeArrayDestroy(SAFEARRAY * psa);
/**
 * This function changes the right-most (least significant) bound of a safe array.
 *
 * @param psa Pointer to an array descriptor.
 * @param psaboundNew Pointer to a new safe array bound structure that contains the new array
 *   boundary. Only the least significant dimension of an array can be changed.
 *
 * @return One of the values obtained from the returned HRESULT and described in the following table
 *   is returned. Value Description S_OK Success. DISP_E_ARRAYISLOCKED The array is currently locked.
 *   E_INVALIDARG The item pointed to by psa is not a safe array descriptor.
 *
 * If you reduce the bound of an array, SafeArrayRedim deallocates the array elements outside the
 * new array boundary. If the bound of an array is increased, SafeArrayRedim allocates and
 * initializes the new array elements. The data is preserved for elements that exist in both the old
 * and new array. Passing into this function any invalid and, under some circumstances, NULL
 * pointers will result in unexpected termination of the application.
 */
WINOLEAUTAPI SafeArrayRedim(SAFEARRAY * psa, SAFEARRAYBOUND * psaboundNew);
/**
 * This function returns the number of dimensions in the array.
 *
 * @param psa Pointer to an array descriptor created by SafeArrayCreate.
 *
 * @return Returns the number of dimensions in the array.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI_(UINT) SafeArrayGetDim(SAFEARRAY * psa);
/**
 * This function retrieves the size (in bytes) of the elements of a safe array.
 *
 * @param psa Pointer to an array descriptor created by SafeArrayCreate.
 *
 * @return Returns the size (in bytes) of the elements of a safe array.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI_(UINT) SafeArrayGetElemsize(SAFEARRAY * psa);
/**
 * This function returns the upper bound for any dimension of a safe array.
 *
 * @param psa Pointer to an array descriptor created by SafeArrayCreate.
 * @param nDim Specifies the array dimension for which to get the upper bound.
 * @param plUbound Pointer to the location to return the upper bound.
 *
 * @return One of the values obtained from the returned HRESULT and described in the following table
 *   is returned. Value Description S_OK Success. DISP_E_BADINDEX The specified index is out of
 *   bounds. E_INVALIDARG One of the arguments is invalid.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI SafeArrayGetUBound(SAFEARRAY * psa, UINT nDim, LONG * plUbound);
/**
 * This function returns the lower bound for any dimension of a safe array.
 *
 * @param psa Pointer to an array descriptor created by SafeArrayCreate.
 * @param nDim Specifies the array dimension for which to get the lower bound.
 * @param plLbound Pointer to the location to return the lower bound.
 *
 * @return One of the values obtained from the returned HRESULT and described in the following table
 *   is returned. Value Description S_OK Success. DISP_E_BADINDEX The specified index is out of
 *   bounds. E_INVALIDARG One of the arguments is invalid.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI SafeArrayGetLBound(SAFEARRAY * psa, UINT nDim, LONG * plLbound);
/**
 * This function increments the lock count of an array, and places a pointer to the array data in
 * pvData of the array descriptor.
 *
 * @param psa Pointer to an array descriptor created by SafeArrayCreate.
 *
 * @return One of the values obtained from the returned HRESULT and described in the following table
 *   is returned. Value Description S_OK Success. E_INVALIDARG The psa parameter was not a valid safe
 *   array descriptor. E_UNEXPECTED The array could not be locked.
 *
 * The pointer in the array descriptor is valid until SafeArrayUnlock is called. Calls to
 * SafeArrayLock can be nested. An equal number of calls to SafeArrayUnlock are required. Passing
 * into this function any invalid and, under some circumstances, NULL pointers will result in
 * unexpected termination of the application.
 *
 * An array cannot be deleted while it is locked.
 */
WINOLEAUTAPI SafeArrayLock(SAFEARRAY * psa);
/**
 * This function decrements the lock count of an array so it can be freed or resized.
 *
 * @param psa Pointer to an array descriptor created by SafeArrayCreate.
 *
 * @return One of the values obtained from the returned HRESULT and described in the following table
 *   is returned. Value Description S_OK Success. E_INVALIDARG The psa parameter was not a valid safe
 *   array descriptor. E_UNEXPECTED The array could not be unlocked.
 *
 * This function is called after access to the data in an array is finished. Passing into this
 * function any invalid and, under some circumstances, NULL pointers will result in unexpected
 * termination of the application.
 */
WINOLEAUTAPI SafeArrayUnlock(SAFEARRAY * psa);
/**
 * This function increments the lock count of an array, and retrieves a pointer to the array data.
 *
 * @param psa [in] Pointer to an array descriptor created by SafeArrayCreate.
 * @param ppvData [in] On exit, pointer to a pointer to the array data.
 *
 * @return One of the values obtained from the returned HRESULT and described in the following table
 *   is returned. Value Description S_OK Success. E_INVALIDARG The psa parameter was not a valid safe
 *   array descriptor. E_UNEXPECTED The array could not be locked.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI SafeArrayAccessData(SAFEARRAY * psa, void HUGEP** ppvData);
/**
 * This function decrements the lock count of an array, and invalidates the pointer retrieved by
 * SafeArrayAccessData.
 *
 * @param psa Pointer to an array descriptor created by SafeArrayCreate.
 *
 * @return One of the values obtained from the returned HRESULT and described in the following table
 *   is returned. Value Description S_OK Success. E_INVALIDARG The psa parameter was not a valid safe
 *   array descriptor. E_UNEXPECTED The array could not be unlocked.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI SafeArrayUnaccessData(SAFEARRAY * psa);
/**
 * This function retrieves a single element of the array.
 *
 * @param psa Pointer to an array descriptor created by SafeArrayCreate.
 * @param rgIndices Pointer to a vector of indexes for each dimension of the array. The right-most
 *   (least significant) dimension is rgIndices[0]. The left-most dimension is stored at
 *   rgIndices[psa->cDims -1].
 * @param pv Void pointer to the location to place the element of the array.
 *
 * @return One of the values obtained from the returned HRESULT and described in the following table
 *   is returned. Value Description S_OK Success. DISP_E_BADINDEX The specified index is invalid.
 *   E_INVALIDARG One of the arguments is invalid. E_OUTOFMEMORY Memory could not be allocated for the
 *   element.
 *
 * This function calls SafeArrayLock and SafeArrayUnlock automatically, before and after retrieving
 * the element. The caller must provide a storage area of the correct size to receive the data. If
 * the data element is a string, object, or variant, the function copies the element in the correct
 * way. Passing into this function any invalid and, under some circumstances, NULL pointers will
 * result in unexpected termination of the application.
 */
WINOLEAUTAPI SafeArrayGetElement(SAFEARRAY * psa, LONG * rgIndices, void * pv);
/**
 * This function assigns a single element to the array.
 *
 * @param psa Pointer to an array descriptor created by SafeArrayCreate.
 * @param rgIndices Pointer to a vector of indexes for each dimension of the array. The right-most
 *   (least significant) dimension is rgIndices[0]. The left-most dimension is stored at
 *   rgIndices[psa->cDims -1].
 * @param pv Void pointer to the data to assign to the array. The variant types VT_DISPATCH,
 *   VT_UNKNOWN, and VT_BSTR are pointers, and do not require another level of indirection.
 *
 * @return One of the values obtained from the returned HRESULT and described in the following table
 *   is returned. Value Description S_OK Success. DISP_E_BADINDEX The specified index was invalid.
 *   E_INVALIDARG One of the arguments is invalid. E_OUTOFMEMORY Memory could not be allocated for the
 *   element.
 *
 * This function automatically calls SafeArrayLock and SafeArrayUnlock before and after assigning
 * the element. If the data element is a string, object, or variant, the function copies it
 * correctly. If the existing element is a string, object, or variant, it is cleared correctly.
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 *
 * Note Multiple locks can be on an array. Elements can be put into an array while the array is
 * locked by other operations.
 */
WINOLEAUTAPI SafeArrayPutElement(SAFEARRAY * psa, LONG * rgIndices, void * pv);
/**
 * This function creates a copy of an existing safe array.
 *
 * @param psa Pointer to an array descriptor created by SafeArrayCreate.
 * @param ppsaOut Pointer to a location in which to return the new array descriptor.
 *
 * @return One of the values obtained from the returned HRESULT and described in the following table
 *   is returned. Value Description S_OK Success. E_INVALIDARG The psa parameter was not a valid safe
 *   array descriptor. E_OUTOFMEMORY Insufficient memory to create the copy.
 *
 * SafeArrayCopy calls the string or variant manipulation functions if the array to copy contains
 * either of these data types. If the array being copied contains object references, the reference
 * counts for the objects are incremented. Passing into this function any invalid and, under some
 * circumstances, NULL pointers will result in unexpected termination of the application.
 */
WINOLEAUTAPI SafeArrayCopy(SAFEARRAY * psa, SAFEARRAY ** ppsaOut);
/**
 * This function returns a pointer to an array element.
 *
 * @param psa Pointer to an array descriptor created by SafeArrayCreate.
 * @param rgIndices Array of index values that identify an element of the array. All indexes for the
 *   element must be specified.
 * @param ppvData On return, pointer to the void pointer to the element identified by the values in
 *   rgIndices.
 *
 * @return One of the values obtained from the returned HRESULT and described in the following table
 *   is returned. Value Description S_OK Success. E_INVALIDARG The psa parameter was not a valid safe
 *   array descriptor. DISP_E_BADINDEX The specified index was invalid.
 *
 * The array should be locked before SafeArrayPtrOfIndex is called. Failing to lock the array can
 * cause unpredictable results. Passing into this function any invalid and, under some
 * circumstances, NULL pointers will result in unexpected termination of the application.
 */
WINOLEAUTAPI SafeArrayPtrOfIndex(SAFEARRAY * psa, LONG * rgIndices, void ** ppvData);


/*---------------------------------------------------------------------*/
/*                           VARIANT API                               */
/*---------------------------------------------------------------------*/

/**
 * This function initializes a variant.
 *
 * @param pvarg Pointer to the VARIANTARG that will be initialized.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 *
 * The VariantInit function initializes the VARIANTARG by setting the vt member to VT_EMPTY. Unlike
 * VariantClear, this function does not interpret the current contents of the VARIANTARG. Use
 * VariantInit to initialize new local variables of type VARIANTARG (or VARIANT).
 */
WINOLEAUTAPI_(void) VariantInit(VARIANTARG * pvarg);
/**
 * This function clears a variant.
 *
 * @param pvarg Pointer to the VARIANTARG to clear.
 *
 * @return One of the values obtained from the returned HRESULT and described in the following table
 *   is returned. Value Description S_OK Success. DISP_E_ARRAYISLOCKED The variant contains an array
 *   that is locked. DISP_E_BADVARTYPE The variant type pvarg is not a valid type of variant.
 *   E_INVALIDARG One of the arguments is invalid.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 *
 * Use this function to clear variables of type VARIANTARG (or VARIANT) before the memory that
 * contains the VARIANTARG is freed (as when a local variable goes out of scope).
 *
 * The function clears a VARIANTARG by setting the vt member to VT_EMPTY and the wReserved member to
 * 0. The current contents of the VARIANTARG are released first. If the vt member is VT_BSTR, the
 * string is freed. If the vt member is VT_DISPATCH, the object is released. If the vt member has
 * the VT_ARRAY bit set, the array is freed.
 *
 * In certain cases, it may be preferable to clear a variant in code without calling VariantClear.
 * For example, you can change the type of a VT_I4 variant to another type without calling this
 * function. However, you must call VariantClear if a VT_* type is received but cannot be handled.
 * Using VariantClear in these cases ensures that code will continue to work if Automation adds new
 * variant types in the future.
 */
WINOLEAUTAPI VariantClear(VARIANTARG * pvarg);
/**
 * This function frees the destination variant and makes a copy of the source variant.
 *
 * @param pvargDest Pointer to the VARIANTARG to receive the copy.
 * @param pvargSrc Pointer to the VARIANTARG to be copied.
 *
 * @return One of the values obtained from the returned HRESULT and described in the following table
 *   is returned. Value Description S_OK Success. DISP_E_ARRAYISLOCKED The variant contains an array
 *   that is locked. DISP_E_BADVARTYPE The source and destination have an invalid variant type
 *   (usually uninitialized). E_OUTOFMEMORY Memory could not be allocated for the copy. E_INVALIDARG
 *   One of the arguments is invalid.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 *
 * First, free any memory that is owned by pvargDest, such as VariantClear (pvargDest must point to
 * a valid initialized variant, and not simply to an uninitialized memory location). Then pvargDest
 * receives an exact copy of the contents of pvargSrc.
 *
 * If pvargSrc is a VT_BSTR, a copy of the string is made. If pvargSrc is a VT_ARRAY, the entire
 * array is copied. If pvargSrc is a VT_DISPATCH or VT_UNKNOWN, AddRef is called to increment the
 * object's reference count.
 */
WINOLEAUTAPI VariantCopy(VARIANTARG * pvargDest, VARIANTARG * pvargSrc);
/**
 * This function frees any existing content of the destination variant and makes a copy of the
 * source VARIANTARG, performing the necessary indirection if the source is specified to be
 * VT_BYREF.
 *
 * @param pvarDest Pointer to the VARIANTARG that receives the copy.
 * @param pvargSrc Pointer to the VARIANTARG that is copied.
 *
 * @return One of the values obtained from the returned HRESULT and described in the following table
 *   is returned. Value Description S_OK Success. DISP_E_ARRAYISLOCKED The variant contains an array
 *   that is locked. DISP_E_BADVARTYPE The source and destination have an invalid variant type
 *   (usually uninitialized). E_OUTOFMEMORY Memory could not be allocated for the copy. E_INVALIDARG
 *   The argument pvargSrc was VT_ARRAY.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 *
 * This function is useful when a copy of a variant is needed, and to guarantee that it is not
 * VT_BYREF, such as when handling arguments in an implementation of IDispatch::Invoke.
 *
 * For example, if the source is a (VT_BYREF | VT_I2), the destination will be a BYVAL | VT_I2. The
 * same is true for all legal VT_BYREF combinations, including VT_VARIANT.
 *
 * If pvargSrc is (VT_BYREF | VT_VARIANT), and the contained variant is VT_BYREF, the contained
 * variant is also dereferenced.
 *
 * This function frees any existing contents of pvarDest.
 */
WINOLEAUTAPI VariantCopyInd(VARIANT * pvarDest, VARIANTARG * pvargSrc);
/**
 * This function converts a variant from one type to another.
 *
 * @param pvargDest Pointer to the VarBoolFromDispto receive the coerced type. If this is the same
 *   as pvarSrc, the variant is converted in place.
 * @param pvarSrc Pointer to the source VARIANTARG to be coerced.
 * @param wFlags Flags that control the coercion. The only defined flag is VARIANT_NOVALUEPROP,
 *   which prevents the function from attempting to coerce an object to a fundamental type by getting
 *   the Value property. Applications should set this flag only if necessary, because it makes their
 *   behavior inconsistent with other applications.
 * @param vt Specifies the type to coerce to. If the return code is S_OK, the vt member of the
 *   VARIANTARG specified by *pvargDest is always the same as this value.
 *
 * @return One of the values obtained from the returned HRESULT and described in the following table
 *   is returned. Value Description S_OK Success. DISP_E_BADVARTYPE The variant type vt is not a valid
 *   type of variant. DISP_E_OVERFLOW The data pointed to by pvarSrc does not fit in the destination
 *   type. DISP_E_TYPEMISMATCH The argument could not be coerced to the specified type. E_INVALIDARG
 *   One of the arguments is invalid. E_OUTOFMEMORY Memory could not be allocated for the conversion.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 *
 * The VariantChangeType function handles coercions between the fundamental types (including
 * numeric-to-string and string-to-numeric coercions). A variant that has VT_BYREF set is coerced to
 * a value by obtaining the referenced value. An object is coerced to a value by invoking the
 * object's Value property (DISPID_VALUE).
 *
 * Typically, the implementor of IDispatch::Invoke determines which member is being accessed, and
 * then calls VariantChangeType to get the value of one or more arguments. For example, if the
 * IDispatch call specifies a SetTitle member that takes one string argument, the implementor would
 * call VariantChangeType to attempt to coerce the argument to VT_BSTR. If VariantChangeType does
 * not return an error, the argument could then be obtained directly from the bstrVal member of the
 * VARIANTARG. If VariantChangeType returns DISP_E_TYPEMISMATCH, the implementor would set *puArgErr
 * to 0 (indicating the argument in error) and return DISP_E_TYPEMISMATCH from IDispatch::Invoke.
 *
 * Arrays of one type cannot be converted to arrays of another type with this function.
 *
 * Note The type of a VARIANTARG should not be changed in the rgvarg array in place.
 */
WINOLEAUTAPI VariantChangeType(VARIANTARG * pvargDest,
                VARIANTARG * pvarSrc, USHORT wFlags, VARTYPE vt);
/**
 * This function converts a variant from one type to another, using a LCID.
 *
 * @param pvargDest Pointer to the VARIANTARG to receive the coerced type. If this is the same as
 *   pvarSrc, the variant is converted in place.
 * @param pvarSrc Pointer to the source VARIANTARG to be coerced.
 * @param lcid LCID for the variant to coerce. The LCID is useful when the type of the source or
 *   destination VARIANTARG is VT_BSTR, VT_DISPATCH, or VT_DATE.
 * @param wFlags Flags that control the coercion. The only defined flag is VARIANT_NOVALUEPROP,
 *   which prevents the function from attempting to coerce an object to a fundamental type by getting
 *   its Value property. Applications should set this flag only if necessary, because it makes their
 *   behavior inconsistent with other applications.
 * @param vt Specifies the type to coerce to. If the return code is S_OK, the vt member of the
 *   VARIANTARG specified by *pvargDest is guaranteed to be equal to this value.
 *
 * @return One of the values obtained from the returned HRESULT and described in the following table
 *   is returned. Value Description S_OK Success. DISP_E_BADVARTYPE The variant type vt is not a valid
 *   type of variant. DISP_E_OVERFLOW The data pointed to by pvarSrc does not fit in the destination
 *   type. DISP_E_TYPEMISMATCH The argument could not be coerced to the specified type. E_INVALIDARG
 *   One of the arguments is invalid. E_OUTOFMEMORY Memory could not be allocated for the conversion.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 *
 * The VariantChangeTypeEx function handles coercions between the fundamental types (including
 * numeric-to-string and string-to-numeric coercions). To change a type with the VT_BYREF flag set
 * to one without VT_BYREF, change the referenced value to VariantChangeTypeEx. To coerce objects to
 * fundamental types, obtain the value of the Value property.
 *
 * Typically, the implementor of IDispatch::Invoke determines which member is being accessed, and
 * then calls VariantChangeType to get the value of one or more arguments. For example, if the
 * IDispatch call specifies a SetTitle member that takes one string argument, the implementor would
 * call VariantChangeTypeEx to attempt to coerce the argument to VT_BSTR.
 *
 * If VariantChangeTypeEx does not return an error, the argument could then be obtained directly
 * from the bstrVal member of the VARIANTARG. If VariantChangeTypeEx returns DISP_E_TYPEMISMATCH,
 * the implementor would set *puArgErr to 0 (indicating the argument in error) and return
 * DISP_E_TYPEMISMATCH from IDispatch::Invoke.
 *
 * Arrays of one type cannot be converted to arrays of another type with this function.
 *
 * Note The type of a VARIANTARG should not be changed in the rgvarg array in place.
 */
WINOLEAUTAPI VariantChangeTypeEx(VARIANTARG * pvargDest,
                VARIANTARG * pvarSrc, LCID lcid, USHORT wFlags, VARTYPE vt);

// Flags for VariantChangeType/VariantChangeTypeEx
#define VARIANT_NOVALUEPROP 0x1
#define VARIANT_ALPHABOOL   0x2 // For VT_BOOL to VT_BSTR conversions,
                                // convert to "True"/"False" instead of
                                // "-1"/"0"
#define VARIANT_NOUSEROVERRIDE   0x4	// For conversions to/from VT_BSTR,
					// passes LOCALE_NOUSEROVERRIDE
					// to core coercion routines


/*---------------------------------------------------------------------*/
/*                Vector <-> Bstr conversion APIs                      */
/*---------------------------------------------------------------------*/

/**
 * This function returns a vector, assigning each character in the BSTR to an element of the vector.
 *
 * @param bstr Unicode string to be converted to a vector.
 * @param ppsa On exit, pointer to a one-dimensional safe array that contains the characters in the
 *   BSTR.
 *
 * @return One of the values obtained from the returned HRESULT and described in the following table
 *   is returned. Value Description S_OK Success. E_OUTOFMEMORY Out of memory. E_INVALIDARG BSTR is
 *   NULL.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VectorFromBstr (BSTR bstr, SAFEARRAY ** ppsa);
/**
 * This function returns a BSTR, assigning each element of the vector to a character in the BSTR.
 *
 * @param psa Pointer to the vector to be converted to a BSTR.
 * @param pbstr On exit, pointer to a BSTR, each character of which is assigned to an element from
 *   the vector.
 *
 * @return One of the values obtained from the returned HRESULT and described in the following table
 *   is returned. Value Description S_OK Success. E_OUTOFMEMORY Out of memory. E_INVALIDARG The psa
 *   parameter is NULL. DISP_E_TYPEMISMATCH The psa parameter is not a vector (not an array of bytes).
 */
WINOLEAUTAPI BstrFromVector (SAFEARRAY *psa, BSTR *pbstr);


/*---------------------------------------------------------------------*/
/*                     VARTYPE Coercion API                            */
/*---------------------------------------------------------------------*/

/* Note: The routines that convert *from* a string are defined
 * to take a OLECHAR* rather than a BSTR because no allocation is
 * required, and this makes the routines a bit more generic.
 * They may of course still be passed a BSTR as the strIn param.
 */

/* Any of the coersion functions that converts either from or to a string
 * takes an additional lcid and dwFlags arguments. The lcid argument allows
 * locale specific parsing to occur.  The dwFlags allow additional function
 * specific condition to occur.  All function that accept the dwFlags argument
 * can include either 0 or LOCALE_NOUSEROVERRIDE flag. In addition, the
 * VarDateFromStr functions also accepts the VAR_TIMEVALUEONLY and
 * VAR_DATEVALUEONLY flags
 */

#define VAR_TIMEVALUEONLY   ((DWORD)0x00000001)    /* return time value */
#define VAR_DATEVALUEONLY   ((DWORD)0x00000002)    /* return date value */

/**
 * This function converts variant data types to BYTE from short.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarUI1FromI2(SHORT sIn, BYTE * pbOut);
/**
 * This function converts variant data types to BYTE from long.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarUI1FromI4(LONG lIn, BYTE * pbOut);
/**
 * This function converts variant data types to BYTE from float.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarUI1FromR4(FLOAT fltIn, BYTE * pbOut);
/**
 * This function converts variant data types to BYTE from double.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarUI1FromR8(DOUBLE dblIn, BYTE * pbOut);
/**
 * This function converts variant data types to BYTE from CURRENCY.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarUI1FromCy(CY cyIn, BYTE * pbOut);
/**
 * This function converts variant data types to BYTE from DATE.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarUI1FromDate(DATE dateIn, BYTE * pbOut);
/**
 * This function converts variant data types to BYTE from BSTR.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarUI1FromStr(OLECHAR * strIn, LCID lcid, ULONG dwFlags, BYTE * pbOut);
/**
 * This function converts variant data types to BYTE from IDispatch.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarUI1FromDisp(IDispatch * pdispIn, LCID lcid, BYTE * pbOut);
/**
 * This function converts variant data types to BYTE from BOOL.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarUI1FromBool(VARIANT_BOOL boolIn, BYTE * pbOut);
/**
 * This function converts variant data types to BYTE from char.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarUI1FromI1(CHAR cIn, BYTE *pbOut);
/**
 * This function converts variant data types to BYTE from unsigned short.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarUI1FromUI2(USHORT uiIn, BYTE *pbOut);
/**
 * This function converts variant data types to BYTE from unsigned long.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarUI1FromUI4(ULONG ulIn, BYTE *pbOut);
/**
 * This function converts variant data types to BYTE from DECIMAL.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarUI1FromDec(DECIMAL *pdecIn, BYTE *pbOut);

/**
 * This function converts variant data types to short from BYTE.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarI2FromUI1(BYTE bIn, SHORT * psOut);
/**
 * This function converts variant data types to short from long.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarI2FromI4(LONG lIn, SHORT * psOut);
/**
 * This function converts variant data types to short from float.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarI2FromR4(FLOAT fltIn, SHORT * psOut);
/**
 * This function converts variant data types to short from double.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarI2FromR8(DOUBLE dblIn, SHORT * psOut);
/**
 * This function converts variant data types to short from CURRENCY.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarI2FromCy(CY cyIn, SHORT * psOut);
/**
 * This function converts variant data types to short from DATE.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarI2FromDate(DATE dateIn, SHORT * psOut);
/**
 * This function converts variant data types to short from OLECHAR.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarI2FromStr(OLECHAR * strIn, LCID lcid, ULONG dwFlags, SHORT * psOut);
/**
 * This function converts variant data types to short from IDispatch.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarI2FromDisp(IDispatch * pdispIn, LCID lcid, SHORT * psOut);
/**
 * This function converts variant data types to short from BOOL.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarI2FromBool(VARIANT_BOOL boolIn, SHORT * psOut);
/**
 * This function converts variant data types to short from CHAR.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarI2FromI1(CHAR cIn, SHORT *psOut);
/**
 * This function converts variant data types to short from unsigned short.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarI2FromUI2(USHORT uiIn, SHORT *psOut);
/**
 * This function converts variant data types to short from unsigned long.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarI2FromUI4(ULONG ulIn, SHORT *psOut);
/**
 * This function converts variant data types to Short from DECIMAL.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarI2FromDec(DECIMAL *pdecIn, SHORT *psOut);

/**
 * This function converts variant data types to long from BYTE.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarI4FromUI1(BYTE bIn, LONG * plOut);
/**
 * This function converts variant data types to long from short.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarI4FromI2(SHORT sIn, LONG * plOut);
/**
 * This function converts variant data types to long from float.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarI4FromR4(FLOAT fltIn, LONG * plOut);
/**
 * This function converts variant data types to long from double.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarI4FromR8(DOUBLE dblIn, LONG * plOut);
/**
 * This function converts variant data types to long from CURRENCY.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarI4FromCy(CY cyIn, LONG * plOut);
/**
 * This function converts variant data types to long from DATE.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarI4FromDate(DATE dateIn, LONG * plOut);
/**
 * This function converts variant data types to long from OLECHAR.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarI4FromStr(OLECHAR * strIn, LCID lcid, ULONG dwFlags, LONG * plOut);
/**
 * This function converts variant data types to long from IDispatch.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarI4FromDisp(IDispatch * pdispIn, LCID lcid, LONG * plOut);
/**
 * This function converts variant data types to long from BOOL.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarI4FromBool(VARIANT_BOOL boolIn, LONG * plOut);
/**
 * This function converts variant data types to long from CHAR.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarI4FromI1(CHAR cIn, LONG *plOut);
/**
 * This function converts variant data types to long from unsigned short.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarI4FromUI2(USHORT uiIn, LONG *plOut);
/**
 * This function converts variant data types to long from unsigned long.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarI4FromUI4(ULONG ulIn, LONG *plOut);
/**
 * This function converts variant data types to long from DECIMAL.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarI4FromDec(DECIMAL *pdecIn, LONG *plOut);
WINOLEAUTAPI VarI4FromInt(INT intIn, LONG *plOut);

/**
 * This function converts variant data types to float from BYTE.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarR4FromUI1(BYTE bIn, FLOAT * pfltOut);
/**
 * This function converts variant data types to float from short.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarR4FromI2(SHORT sIn, FLOAT * pfltOut);
/**
 * This function converts variant data types to float from long.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarR4FromI4(LONG lIn, FLOAT * pfltOut);
/**
 * This function converts variant data types to float from double.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarR4FromR8(DOUBLE dblIn, FLOAT * pfltOut);
/**
 * This function converts variant data types to float from CURRENCY.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarR4FromCy(CY cyIn, FLOAT * pfltOut);
/**
 * This function converts variant data types to float from DATE.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarR4FromDate(DATE dateIn, FLOAT * pfltOut);
/**
 * This function converts variant data types to float from OLECHAR.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarR4FromStr(OLECHAR * strIn, LCID lcid, ULONG dwFlags, FLOAT *pfltOut);
/**
 * This function converts variant data types to float from IDispatch.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarR4FromDisp(IDispatch * pdispIn, LCID lcid, FLOAT * pfltOut);
/**
 * This function converts variant data types to float from BOOL.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarR4FromBool(VARIANT_BOOL boolIn, FLOAT * pfltOut);
/**
 * This function converts variant data types to float from char.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarR4FromI1(CHAR cIn, FLOAT *pfltOut);
/**
 * This function converts variant data types to float from unsigned short.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarR4FromUI2(USHORT uiIn, FLOAT *pfltOut);
/**
 * This function converts variant data types to float from unsigned Long.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarR4FromUI4(ULONG ulIn, FLOAT *pfltOut);
/**
 * This function converts variant data types to float from DECIMAL.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarR4FromDec(DECIMAL *pdecIn, FLOAT *pfltOut);

/**
 * This function converts variant data types to double from unsigned char.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarR8FromUI1(BYTE bIn, DOUBLE * pdblOut);
/**
 * This function converts variant data types to double from short.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarR8FromI2(SHORT sIn, DOUBLE * pdblOut);
/**
 * This function converts variant data types to double from long.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarR8FromI4(LONG lIn, DOUBLE * pdblOut);
/**
 * This function converts variant data types to double from float.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarR8FromR4(FLOAT fltIn, DOUBLE * pdblOut);
/**
 * This function converts variant data types to double from CURRENCY.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarR8FromCy(CY cyIn, DOUBLE * pdblOut);
/**
 * This function converts variant data types to double from DATE.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarR8FromDate(DATE dateIn, DOUBLE * pdblOut);
/**
 * This function converts variant data types to double from OLECHAR.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarR8FromStr(OLECHAR *strIn, LCID lcid, ULONG dwFlags, DOUBLE *pdblOut);
/**
 * This function converts variant data types to double from IDispatch.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarR8FromDisp(IDispatch * pdispIn, LCID lcid, DOUBLE * pdblOut);
/**
 * This function converts variant data types to double from BOOL.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarR8FromBool(VARIANT_BOOL boolIn, DOUBLE * pdblOut);
/**
 * This function converts variant data types to double from char.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarR8FromI1(CHAR cIn, DOUBLE *pdblOut);
/**
 * This function converts variant data types to double from unsigned short.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarR8FromUI2(USHORT uiIn, DOUBLE *pdblOut);
/**
 * This function converts variant data types to double from unsigned long.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarR8FromUI4(ULONG ulIn, DOUBLE *pdblOut);
/**
 * This function converts variant data types to double from DECIMAL.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarR8FromDec(DECIMAL *pdecIn, DOUBLE *pdblOut);

/**
 * This function converts variant data types to DATE from BYTE.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarDateFromUI1(BYTE bIn, DATE * pdateOut);
/**
 * This function converts variant data types to DATE from short.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarDateFromI2(SHORT sIn, DATE * pdateOut);
/**
 * This function converts variant data types to DATE from long.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarDateFromI4(LONG lIn, DATE * pdateOut);
/**
 * This function converts variant data types to DATE from float.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarDateFromR4(FLOAT fltIn, DATE * pdateOut);
/**
 * This function converts variant data types to DATE from double.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarDateFromR8(DOUBLE dblIn, DATE * pdateOut);
/**
 * This function converts variant data types to DATE from CURRENCY.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarDateFromCy(CY cyIn, DATE * pdateOut);
/**
 * This function converts variant data types to DATE from OLECHAR.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarDateFromStr(OLECHAR *strIn, LCID lcid, ULONG dwFlags, DATE *pdateOut);
/**
 * This function converts variant data types to DATE from IDispatch.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarDateFromDisp(IDispatch * pdispIn, LCID lcid, DATE * pdateOut);
/**
 * This function converts variant data types to DATE from BOOL.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarDateFromBool(VARIANT_BOOL boolIn, DATE * pdateOut);
/**
 * This function converts variant data types to DATE from char.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarDateFromI1(CHAR cIn, DATE *pdateOut);
/**
 * This function converts variant data types to DATE from unsigned short.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarDateFromUI2(USHORT uiIn, DATE *pdateOut);
/**
 * This function converts variant data types to DATE from unsigned long.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarDateFromUI4(ULONG ulIn, DATE *pdateOut);
/**
 * This function converts variant data types to DATE from DECIMAL.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarDateFromDec(DECIMAL *pdecIn, DATE *pdateOut);

/**
 * This function converts variant data types to CURRENCY from BYTE.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarCyFromUI1(BYTE bIn, CY * pcyOut);
/**
 * This function converts variant data types to CURRENCY from short.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarCyFromI2(SHORT sIn, CY * pcyOut);
/**
 * This function converts variant data types to CURRENCY from long.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarCyFromI4(LONG lIn, CY * pcyOut);
/**
 * This function converts variant data types to CURRENCY from float.
 */
WINOLEAUTAPI VarCyFromR4(FLOAT fltIn, CY * pcyOut);
/**
 * This function converts variant data types to CURRENCY from double.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarCyFromR8(DOUBLE dblIn, CY * pcyOut);
/**
 * This function converts variant data types to CURRENCY from DATE.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarCyFromDate(DATE dateIn, CY * pcyOut);
/**
 * This function converts variant data types to CURRENCY from BSTR.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarCyFromStr(OLECHAR * strIn, LCID lcid, ULONG dwFlags, CY * pcyOut);
/**
 * This function converts variant data types to CURRENCY from IDispatch .
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarCyFromDisp(IDispatch * pdispIn, LCID lcid, CY * pcyOut);
/**
 * This function converts variant data types to CURRENCY from BOOL.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarCyFromBool(VARIANT_BOOL boolIn, CY * pcyOut);
/**
 * This function converts variant data types to CURRENCY from char.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarCyFromI1(CHAR cIn, CY *pcyOut);
/**
 * This function converts variant data types to CURRENCY from unsigned short.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarCyFromUI2(USHORT uiIn, CY *pcyOut);
/**
 * This function converts variant data types to CURRENCY from unsigned long.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarCyFromUI4(ULONG ulIn, CY *pcyOut);
/**
 * This function converts variant data types to CURRENCY from DECIMAL.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarCyFromDec(DECIMAL *pdecIn, CY *pcyOut);

/**
 * This function converts variant data types to BSTR from BYTE.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarBstrFromUI1(BYTE bVal, LCID lcid, ULONG dwFlags, BSTR * pbstrOut);
/**
 * This function converts variant data types to BSTR from short.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarBstrFromI2(SHORT iVal, LCID lcid, ULONG dwFlags, BSTR * pbstrOut);
/**
 * This function converts variant data types to BSTR from long.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarBstrFromI4(LONG lIn, LCID lcid, ULONG dwFlags, BSTR * pbstrOut);
/**
 * This function converts variant data types to BSTR from float.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarBstrFromR4(FLOAT fltIn, LCID lcid, ULONG dwFlags, BSTR * pbstrOut);
/**
 * This function converts variant data types to BSTR from double.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarBstrFromR8(DOUBLE dblIn, LCID lcid, ULONG dwFlags, BSTR * pbstrOut);
/**
 * This function converts variant data types to BSTR from CURRENCY.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarBstrFromCy(CY cyIn, LCID lcid, ULONG dwFlags, BSTR * pbstrOut);
/**
 * This function converts variant data types to BSTR from DATE.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarBstrFromDate(DATE dateIn, LCID lcid, ULONG dwFlags, BSTR * pbstrOut);
/**
 * This function converts variant data types to BSTR from IDispatch.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarBstrFromDisp(IDispatch * pdispIn, LCID lcid, ULONG dwFlags, BSTR * pbstrOut);
/**
 * This function converts variant data types to BSTR from BOOL.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarBstrFromBool(VARIANT_BOOL boolIn, LCID lcid, ULONG dwFlags, BSTR * pbstrOut);
/**
 * This function converts variant data types to BSTR from char.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarBstrFromI1(CHAR cIn, LCID lcid, ULONG dwFlags, BSTR *pbstrOut);
/**
 * This function converts variant data types to BSTR from unsigned short.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarBstrFromUI2(USHORT uiIn, LCID lcid, ULONG dwFlags, BSTR *pbstrOut);
/**
 * This function converts variant data types to BSTR from unsigned long.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarBstrFromUI4(ULONG ulIn, LCID lcid, ULONG dwFlags, BSTR *pbstrOut);
/**
 * This function converts variant data types to BSTR from DECIMAL.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarBstrFromDec(DECIMAL *pdecIn, LCID lcid, ULONG dwFlags, BSTR *pbstrOut);

/**
 * This function converts variant data types to BOOL from unsigned char.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarBoolFromUI1(BYTE bIn, VARIANT_BOOL * pboolOut);
/**
 * This function converts variant data types to BOOL from short.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarBoolFromI2(SHORT sIn, VARIANT_BOOL * pboolOut);
/**
 * This function converts variant data types to BOOL from long.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarBoolFromI4(LONG lIn, VARIANT_BOOL * pboolOut);
/**
 * This function converts variant data types to BOOL from float.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarBoolFromR4(FLOAT fltIn, VARIANT_BOOL * pboolOut);
/**
 * This function converts variant data types to BOOL from double.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarBoolFromR8(DOUBLE dblIn, VARIANT_BOOL * pboolOut);
/**
 * This function converts variant data types to BOOL from DATE.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarBoolFromDate(DATE dateIn, VARIANT_BOOL * pboolOut);
/**
 * This function converts variant data types to BOOL from CURRENCY.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarBoolFromCy(CY cyIn, VARIANT_BOOL * pboolOut);
/**
 * This function converts variant data types to BOOL from BSTR.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarBoolFromStr(OLECHAR * strIn, LCID lcid, ULONG dwFlags, VARIANT_BOOL * pboolOut);
/**
 * This function converts variant data types to BOOL from IDispatch.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarBoolFromDisp(IDispatch * pdispIn, LCID lcid, VARIANT_BOOL * pboolOut);
/**
 * This function converts variant data types to BOOL from char.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarBoolFromI1(CHAR cIn, VARIANT_BOOL *pboolOut);
/**
 * This function converts variant data types to BOOL from unsigned short.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarBoolFromUI2(USHORT uiIn, VARIANT_BOOL *pboolOut);
/**
 * This function converts variant data types to BOOL from unsigned long.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarBoolFromUI4(ULONG ulIn, VARIANT_BOOL *pboolOut);
/**
 * This function converts variant data types to BOOL from DECIMAL.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarBoolFromDec(DECIMAL *pdecIn, VARIANT_BOOL *pboolOut);

/**
 * This function converts variant data types to char from BYTE.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarI1FromUI1(BYTE bIn, CHAR *pcOut);
/**
 * This function converts variant data types to char from short.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarI1FromI2(SHORT uiIn, CHAR *pcOut);
/**
 * This function converts variant data types to char from long.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarI1FromI4(LONG lIn, CHAR *pcOut);
/**
 * This function converts variant data types to char from float.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarI1FromR4(FLOAT fltIn, CHAR *pcOut);
/**
 * This function converts variant data types to char from double.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarI1FromR8(DOUBLE dblIn, CHAR *pcOut);
/**
 * This function converts variant data types to char from DATE.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarI1FromDate(DATE dateIn, CHAR *pcOut);
/**
 * This function converts variant data types to char from CURRENCY.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarI1FromCy(CY cyIn, CHAR *pcOut);
/**
 * This function converts variant data types to char from BSTR.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarI1FromStr(OLECHAR *strIn, LCID lcid, ULONG dwFlags, CHAR *pcOut);
/**
 * This function converts variant data types to char from IDispatch.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarI1FromDisp(IDispatch *pdispIn, LCID lcid, CHAR *pcOut);
/**
 * This function converts variant data types to char from BOOL.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarI1FromBool(VARIANT_BOOL boolIn, CHAR *pcOut);
/**
 * This function converts variant data types to char from unsigned short.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarI1FromUI2(USHORT uiIn, CHAR *pcOut);
/**
 * This function converts variant data types to char from unsigned long.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarI1FromUI4(ULONG ulIn, CHAR *pcOut);
/**
 * This function converts variant data types to char from DECIMAL.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarI1FromDec(DECIMAL *pdecIn, CHAR *pcOut);

/**
 * This function converts variant data types to unsigned short from BYTE.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarUI2FromUI1(BYTE bIn, USHORT *puiOut);
/**
 * This function converts variant data types to unsigned short from short.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarUI2FromI2(SHORT uiIn, USHORT *puiOut);
/**
 * This function converts variant data types to unsigned short from long.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarUI2FromI4(LONG lIn, USHORT *puiOut);
/**
 * This function converts variant data types to unsigned short from float.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarUI2FromR4(FLOAT fltIn, USHORT *puiOut);
/**
 * This function converts variant data types to unsigned short from double.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarUI2FromR8(DOUBLE dblIn, USHORT *puiOut);
/**
 * This function converts variant data types to unsigned short from DATE.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarUI2FromDate(DATE dateIn, USHORT *puiOut);
/**
 * This function converts variant data types to unsigned short from CURRENCY.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarUI2FromCy(CY cyIn, USHORT *puiOut);
/**
 * This function converts variant data types to unsigned short from BSTR.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarUI2FromStr(OLECHAR *strIn, LCID lcid, ULONG dwFlags, USHORT *puiOut);
/**
 * This function converts variant data types to unsigned short from IDispatch.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarUI2FromDisp(IDispatch *pdispIn, LCID lcid, USHORT *puiOut);
/**
 * This function converts variant data types to unsigned short from BOOL.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarUI2FromBool(VARIANT_BOOL boolIn, USHORT *puiOut);
/**
 * This function converts variant data types to unsigned short from char.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarUI2FromI1(CHAR cIn, USHORT *puiOut);
/**
 * This function converts variant data types to unsigned short from unsigned long.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarUI2FromUI4(ULONG ulIn, USHORT *puiOut);
/**
 * This function converts variant data types to unsigned short from DECIMAL.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarUI2FromDec(DECIMAL *pdecIn, USHORT *puiOut);

/**
 * This function converts variant data types to unsigned long from BYTE.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarUI4FromUI1(BYTE bIn, ULONG *pulOut);
/**
 * This function converts variant data types to unsigned long from short.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarUI4FromI2(SHORT uiIn, ULONG *pulOut);
/**
 * This function converts variant data types to unsigned long from long.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarUI4FromI4(LONG lIn, ULONG *pulOut);
/**
 * This function converts variant data types to unsigned long from float.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarUI4FromR4(FLOAT fltIn, ULONG *pulOut);
/**
 * This function converts variant data types to unsigned long from double.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarUI4FromR8(DOUBLE dblIn, ULONG *pulOut);
/**
 * This function converts variant data types to unsigned long from DATE.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarUI4FromDate(DATE dateIn, ULONG *pulOut);
/**
 * This function converts variant data types to unsigned long from CURRENCY.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarUI4FromCy(CY cyIn, ULONG *pulOut);
/**
 * This function converts variant data types to unsigned long from BSTR.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarUI4FromStr(OLECHAR *strIn, LCID lcid, ULONG dwFlags, ULONG *pulOut);
/**
 * This function converts variant data types to unsigned long from IDispatch.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarUI4FromDisp(IDispatch *pdispIn, LCID lcid, ULONG *pulOut);
/**
 * This function converts variant data types to unsigned long from BOOL.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarUI4FromBool(VARIANT_BOOL boolIn, ULONG *pulOut);
/**
 * This function converts variant data types to unsigned long from char.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarUI4FromI1(CHAR cIn, ULONG *pulOut);
/**
 * This function converts variant data types to unsigned long from unsigned short.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarUI4FromUI2(USHORT uiIn, ULONG *pulOut);
/**
 * This function converts variant data types to unsigned long from DECIMAL.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarUI4FromDec(DECIMAL *pdecIn, ULONG *pulOut);

/**
 * This function converts variant data types to DECIMAL from BYTE.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarDecFromUI1(BYTE bIn, DECIMAL *pdecOut);
/**
 * This function converts variant data types to DECIMAL from short.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarDecFromI2(SHORT uiIn, DECIMAL *pdecOut);
/**
 * This function converts variant data types to DECIMAL from long.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarDecFromI4(LONG lIn, DECIMAL *pdecOut);
/**
 * This function converts variant data types to DECIMAL from float.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarDecFromR4(FLOAT fltIn, DECIMAL *pdecOut);
/**
 * This function converts variant data types to DECIMAL from double.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarDecFromR8(DOUBLE dblIn, DECIMAL *pdecOut);
/**
 * This function converts variant data types to DECIMAL from DATE.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarDecFromDate(DATE dateIn, DECIMAL *pdecOut);
/**
 * This function converts variant data types to DECIMAL from CURRENCY.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarDecFromCy(CY cyIn, DECIMAL *pdecOut);
/**
 * This function converts variant data types to DECIMAL from BSTR.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarDecFromStr(OLECHAR *strIn, LCID lcid, ULONG dwFlags, DECIMAL *pdecOut);
/**
 * This function converts variant data types to DECIMAL from IDispatch.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarDecFromDisp(IDispatch *pdispIn, LCID lcid, DECIMAL *pdecOut);
/**
 * This function converts variant data types to DECIMAL from BOOL.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarDecFromBool(VARIANT_BOOL boolIn, DECIMAL *pdecOut);
/**
 * This function converts variant data types to DECIMAL from char.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarDecFromI1(CHAR cIn, DECIMAL *pdecOut);
/**
 * This function converts variant data types to DECIMAL from unsigned short.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarDecFromUI2(USHORT uiIn, DECIMAL *pdecOut);
/**
 * This function converts variant data types to DECIMAL from unsigned long.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarDecFromUI4(ULONG ulIn, DECIMAL *pdecOut);

#define VarUI4FromUI4(in, pOut) (*(pOut) = (in))
#define VarI4FromI4(in, pOut)   (*(pOut) = (in))

#define VarUI1FromInt       VarUI1FromI4
#define VarUI1FromUint      VarUI1FromUI4
#define VarI2FromInt        VarI2FromI4
#define VarI2FromUint       VarI2FromUI4
#define VarI4FromInt        VarI4FromI4
#define VarI4FromUint       VarI4FromUI4
#define VarR4FromInt        VarR4FromI4
#define VarR4FromUint       VarR4FromUI4
#define VarR8FromInt        VarR8FromI4
#define VarR8FromUint       VarR8FromUI4
#define VarDateFromInt      VarDateFromI4
#define VarDateFromUint     VarDateFromUI4
#define VarCyFromInt        VarCyFromI4
#define VarCyFromUint       VarCyFromUI4
#define VarBstrFromInt      VarBstrFromI4
#define VarBstrFromUint     VarBstrFromUI4
#define VarBoolFromInt      VarBoolFromI4
#define VarBoolFromUint     VarBoolFromUI4
#define VarI1FromInt        VarI1FromI4
#define VarI1FromUint       VarI1FromUI4
#define VarUI2FromInt       VarUI2FromI4
#define VarUI2FromUint      VarUI2FromUI4
#define VarUI4FromInt       VarUI4FromI4
#define VarUI4FromUint      VarUI4FromUI4
#define VarDecFromInt       VarDecFromI4
#define VarDecFromUint      VarDecFromUI4
#define VarIntFromUI1       VarI4FromUI1
#define VarIntFromI2        VarI4FromI2
#define VarIntFromI4        VarI4FromI4
#define VarIntFromR4        VarI4FromR4
#define VarIntFromR8        VarI4FromR8
#define VarIntFromDate      VarI4FromDate
#define VarIntFromCy        VarI4FromCy
#define VarIntFromStr       VarI4FromStr
#define VarIntFromDisp      VarI4FromDisp
#define VarIntFromBool      VarI4FromBool
#define VarIntFromI1        VarI4FromI1
#define VarIntFromUI2       VarI4FromUI2
#define VarIntFromUI4       VarI4FromUI4
#define VarIntFromDec       VarI4FromDec
#define VarIntFromUint      VarI4FromUI4
#define VarUintFromUI1      VarUI4FromUI1
#define VarUintFromI2       VarUI4FromI2
#define VarUintFromI4       VarUI4FromI4
#define VarUintFromR4       VarUI4FromR4
#define VarUintFromR8       VarUI4FromR8
#define VarUintFromDate     VarUI4FromDate
#define VarUintFromCy       VarUI4FromCy
#define VarUintFromStr      VarUI4FromStr
#define VarUintFromDisp     VarUI4FromDisp
#define VarUintFromBool     VarUI4FromBool
#define VarUintFromI1       VarUI4FromI1
#define VarUintFromUI2      VarUI4FromUI2
#define VarUintFromUI4      VarUI4FromUI4
#define VarUintFromDec      VarUI4FromDec
#define VarUintFromInt      VarUI4FromI4

/* Mac Note: On the Mac, the coersion functions support the
 * Symantec C++ calling convention for float/double. To support
 * float/double arguments compiled with the MPW C compiler,
 * use the following APIs to move MPW float/double values into
 * a VARIANT.
 */

/*---------------------------------------------------------------------*/
/*            New VARIANT <-> string parsing functions                 */
/*---------------------------------------------------------------------*/

typedef struct {
    INT   cDig;
    ULONG dwInFlags;
    ULONG dwOutFlags;
    INT   cchUsed;
    INT   nBaseShift;
    INT   nPwr10;
} NUMPARSE;

/* flags used by both dwInFlags and dwOutFlags:
 */
#define NUMPRS_LEADING_WHITE    0x0001
#define NUMPRS_TRAILING_WHITE   0x0002
#define NUMPRS_LEADING_PLUS     0x0004
#define NUMPRS_TRAILING_PLUS    0x0008
#define NUMPRS_LEADING_MINUS    0x0010
#define NUMPRS_TRAILING_MINUS   0x0020
#define NUMPRS_HEX_OCT          0x0040
#define NUMPRS_PARENS           0x0080
#define NUMPRS_DECIMAL          0x0100
#define NUMPRS_THOUSANDS        0x0200
#define NUMPRS_CURRENCY         0x0400
#define NUMPRS_EXPONENT         0x0800
#define NUMPRS_USE_ALL          0x1000
#define NUMPRS_STD              0x1FFF

/* flags used by dwOutFlags only:
 */
#define NUMPRS_NEG              0x10000
#define NUMPRS_INEXACT          0x20000

/* flags used by VarNumFromParseNum to indicate acceptable result types:
 */
#define VTBIT_I1        (1 << VT_I1)
#define VTBIT_UI1       (1 << VT_UI1)
#define VTBIT_I2        (1 << VT_I2)
#define VTBIT_UI2       (1 << VT_UI2)
#define VTBIT_I4        (1 << VT_I4)
#define VTBIT_UI4       (1 << VT_UI4)
#define VTBIT_R4        (1 << VT_R4)
#define VTBIT_R8        (1 << VT_R8)
#define VTBIT_CY        (1 << VT_CY)
#define VTBIT_DECIMAL   (1 << VT_DECIMAL)


/**
 * This function parses a string and creates a type-independent description of the number it
 * represents.
 *
 * @param strIn Input string to be converted to a number.
 * @param lcid Locale identifier
 * @param pnumprs Parsed results.
 * @param dwFlags Enables the caller to control parsing, therefore defining the acceptable syntax of
 *   a number. If this field is set to zero, the input string must contain nothing but decimal digits.
 *   Setting each defined flag bit enables parsing of that syntactic feature. Standard Automation
 *   parsing (for example, as used by VarI2FromStr) has all flags set (NUMPRS_STD).
 * @param rgbDig Array filled in with the values for the digits in the range 0-7, 0-9, or 0-15,
 *   depending on whether the number is octal, decimal, or hexadecimal. All leading zeros have been
 *   stripped off. For decimal numbers, trailing zeros are also stripped off, unless the number is
 *   zero, in which case a single zero digit will be present.
 *
 * @return One of the values obtained from the returned HRESULT and described in the following table
 *   is returned. Value Description S_OK Success. E_OUTOFMEMORY Internal memory allocation failed.
 *   (Used for DBCS only to create a copy with all wide characters mapped narrow.) DISP_E_TYPEMISMATCH
 *   There is no valid number in the string, or there is no closing parenthesis to match an opening
 *   one. In the former case, cDig and cchUsed in the NUMPARSE structure will be zero. In the latter,
 *   the NUMPARSE structure and digit array are fully updated, as if the closing parenthesis was
 *   present. DISP_E_OVERFLOW For hexadecimal and octal digits, there are more digits than will fit
 *   into the array. For decimal, the exponent exceeds the maximum possible. In both cases, the
 *   NUMPARSE structure and digit array are fully updated (for decimal, the cchUsed member excludes
 *   the entire exponent).
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarParseNumFromStr(OLECHAR * strIn, LCID lcid, ULONG dwFlags,
            NUMPARSE * pnumprs, BYTE * rgbDig);

/**
 * This function converts the parsed number to a number of the VARIANT type.
 *
 * @param pnumprs Parsed results. cDig = size of rgbDic
 * @param rgbDig Contains the values of the digits. The cDig member of NUMPARSE contains the number
 *   of digits.
 * @param dwVtBits Contains one bit set for each type that is acceptable as a return value (in many
 *   cases, just one bit). The following VarNumFromParseNum flags indicate acceptable result types:
 *   VTBIT_I1 VTBIT_UI4 VTBIT_UI1 VTBIT_R4 VTBIT_I2 VTBIT_R8 VTBIT_UI2 VTBIT_CY VTBIT_I4 VTBIT_DECIMAL
 * @param pvar Pointer to the result variant.
 *
 * @return One of the values obtained from the returned HRESULT and described in the following table
 *   is returned. Value Description S_OK Success. E_OUTOFMEMORY Out of memory. DISP_E_OVERFLOW The
 *   number is too large to be represented in an allowed type. There is no error if precision is lost
 *   in the conversion. For rounding decimal numbers, the digit array must be at least one digit
 *   longer than the maximum required for data types. The maximum number of digits required for the
 *   DECIMAL data type is 29, so the digit array must have room for 30 digits. There must also be
 *   enough digits to accept the number in octal, if that parsing options is selected. (Hexadecimal
 *   and octal numbers are limited by VarNumFromParseNum to the magnitude of an unsigned long [32
 *   bits], so they need 11 octal digits.)
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarNumFromParseNum(NUMPARSE * pnumprs, BYTE * rgbDig,
            ULONG dwVtBits, VARIANT * pvar);


/*---------------------------------------------------------------------*/
/*                   New date functions                                */
/*---------------------------------------------------------------------*/

#define VAR_VALIDDATE       0x0004    /* VarDateFromUdate() only */
#define VAR_CALENDAR_HIJRI  0x0008    /* use Hijri calender */
#define VARIANT_CALENDAR_HIJRI VAR_CALENDAR_HIJRI

/* The UDATE structure is used with VarDateFromUdate() and VarUdateFromDate().
 * It represents an "unpacked date".
 */
typedef struct {
    SYSTEMTIME st;
    USHORT  wDayOfYear;
} UDATE;

/* APIs to "pack" and "unpack" dates.
 */
/**
 * This function packs a date.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarDateFromUdate(UDATE *pudateIn, ULONG dwFlags, DATE *pdateOut);

/**
 * This function unpacks a date.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI VarUdateFromDate(DATE dateIn, ULONG dwFlags, UDATE *pudateOut);

/* API to retrieve the secondary(altername) month names
   Useful for Hijri, Polish and Russian alternate month names
*/
WINOLEAUTAPI GetAltMonthNames(LCID lcid, LPOLESTR * * prgp);



/*---------------------------------------------------------------------*/
/*                 ITypeLib                                            */
/*---------------------------------------------------------------------*/

typedef ITypeLib * LPTYPELIB;


/*---------------------------------------------------------------------*/
/*                ITypeInfo                                            */
/*---------------------------------------------------------------------*/


typedef LONG DISPID;
typedef DISPID MEMBERID;

#define MEMBERID_NIL DISPID_UNKNOWN
#define ID_DEFAULTINST  -2


/* Flags for IDispatch::Invoke */
#define DISPATCH_METHOD         0x1
#define DISPATCH_PROPERTYGET    0x2
#define DISPATCH_PROPERTYPUT    0x4
#define DISPATCH_PROPERTYPUTREF 0x8

typedef ITypeInfo * LPTYPEINFO;


/*---------------------------------------------------------------------*/
/*                ITypeComp                                            */
/*---------------------------------------------------------------------*/

typedef ITypeComp * LPTYPECOMP;


/*---------------------------------------------------------------------*/
/*             ICreateTypeLib                                          */
/*---------------------------------------------------------------------*/

typedef ICreateTypeLib * LPCREATETYPELIB;

typedef ICreateTypeInfo * LPCREATETYPEINFO;

/*---------------------------------------------------------------------*/
/*             TypeInfo API                                            */
/*---------------------------------------------------------------------*/

/* compute a 16bit hash value for the given name
 */
#ifdef _WIN32
WINOLEAUTAPI_(ULONG) LHashValOfNameSysA(SYSKIND syskind, LCID lcid,
            LPCTSTR szName);
#endif

WINOLEAUTAPI_(ULONG)
LHashValOfNameSys(SYSKIND syskind, LCID lcid, const OLECHAR * szName);

#define LHashValOfName(lcid, szName) \
            LHashValOfNameSys(SYS_WIN32, lcid, szName)

#define WHashValOfLHashVal(lhashval) \
            ((USHORT) (0x0000ffff & (lhashval)))

#define IsHashValCompatible(lhashval1, lhashval2) \
            ((BOOL) ((0x00ff0000 & (lhashval1)) == (0x00ff0000 & (lhashval2))))

/* load the typelib from the file with the given filename
 */
/**
 * This function loads and registers a typelib2 type library.
 *
 * @param szFile Null-terminated string that contains the name of the file from which LoadTypeLib
 *   should attempt to load a type library.
 * @param pptlib On return, pointer to a pointer to the loaded type library.
 *
 * @return One of the values obtained from the returned HRESULT and described in the following table
 *   is returned. Value Description S_OK Success. E_OUTOFMEMORY Out of memory. E_INVALIDARG One or
 *   more of the arguments is invalid. TYPE_E_IOERROR The function could not write to the file.
 *   TYPE_E_INVALIDSTATE The type library could not be opened. TYPE_E_INVDATAREAD The function could
 *   not read from the file. TYPE_E_UNSUPFORMAT The type library has an older format.
 *   TYPE_E_UNKNOWNLCID The LCID could not be found in the OLE-supported DLLs. TYPE_E_CANTLOADLIBRARY
 *   The type library or DLL could not be loaded. Other return codes All FACILITY_STORAGE errors can
 *   be returned.
 *
 * Windows CE supports only typelib2 type libraries. The LoadTypeLib function loads type libraries
 * only from a resource, that is from DLL or EXE files. It willl not load foreign or stand-alone
 * type library files.
 *
 * The function LoadTypeLib loads a type library (usually created with MkTypLib) that is stored in
 * the specified file. If szFile specifies only a file name without any path, LoadTypeLib searches
 * for the file and proceeds as follows:
 *
 * If the file is a stand-alone type library implemented by Typelib.dll, the library is loaded
 * directly.
 *
 * If the file is a DLL or an executable file, it is loaded. By default, the type library is
 * extracted from the first resource of type ITypeLib. To load a different type of library resource,
 * append an integer index to szFile. For example:
 *
 *     LoadTypeLib("C:\MONTANA\EXE\MFA.EXE\3", pptlib)
 *
 * This statement loads the type library resource 3 from the file Mfa.exe file.
 *
 * If the file is none of the above, the file name is parsed into a moniker (an object that
 * represents a file-based link source), and then bound to the moniker. This approach allows
 * LoadTypeLib to be used on foreign type libraries, including in-memory type libraries. Foreign
 * type libraries cannot reside in a DLL or an executable file. For more information on monikers,
 * see the OLE Programmer's Reference in the Win32 SDK.
 *
 * If the type library is already loaded, LoadTypeLib increments the type library's reference count
 * and returns a pointer to the type library.
 *
 * For backward compatibility, LoadTypeLib will register the type library if the path is not
 * specified in the szFile parameter. LoadTypeLib will not register the type library if the path of
 * the type library is specified. It is recommended that RegisterTypeLib be used to register a type
 * library.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI LoadTypeLib(const OLECHAR  *szFile, ITypeLib ** pptlib);

/* Control how a type library is registered
 */
typedef enum tagREGKIND
{
    REGKIND_DEFAULT,
    REGKIND_REGISTER,
    REGKIND_NONE
} REGKIND;

WINOLEAUTAPI LoadTypeLibEx(LPCOLESTR szFile, REGKIND regkind,
            ITypeLib ** pptlib);

/* load registered typelib
 */
/**
 * This function uses registry information to load a type library.
 *
 * @param rguid Globally unique identifier (GUID) of the library being loaded.
 * @param wVerMajor Major version number of the library being loaded.
 * @param wVerMinor Minor version number of the library being loaded.
 * @param lcid National language code of the library being loaded.
 * @param pptlib On return, pointer to a pointer to the loaded type library.
 *
 * @return One of the values obtained from the returned HRESULT and described in the following table
 *   is returned. Value Description S_OK Success. E_OUTOFMEMORY Out of memory. E_INVALIDARG One or
 *   more of the arguments is invalid. TYPE_E_IOERROR The function could not read from the file.
 *   TYPE_E_INVALIDSTATE The type library could not be opened. TYPE_E_INVDATAREAD The function could
 *   not read from the file. TYPE_E_UNSUPFORMAT The type library has an older format.
 *   TYPE_E_UNKNOWNLCID The passed in LCID could not be found in the OLE-supported DLLs.
 *   TYPE_E_CANTLOADLIBRARY The type library or DLL could not be loaded. Other return codes All
 *   FACILITY_STORAGE and system registry errors can also be returned.
 *
 * Only typelib2 type library is supported and loadable from resource.
 *
 * The function LoadRegTypeLib defers to LoadTypeLib to load the file.
 *
 * LoadRegTypeLib compares the requested version numbers against those found in the system registry,
 * and takes one of the following actions:
 *
 * If one of the registered libraries exactly matches both the requested major and minor version
 * numbers, then that type library is loaded.
 *
 * If one or more registered type libraries exactly match the requested major version number, and
 * has a greater minor version number than that requested, the one with the greatest minor version
 * number is loaded.
 *
 * If none of the registered type libraries exactly match the requested major version number (or if
 * none of those that do exactly match the major version number also have a minor version number
 * greater than or equal to the requested minor version number), then LoadRegTypeLib returns an
 * error.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI LoadRegTypeLib(REFGUID rguid, WORD wVerMajor, WORD wVerMinor,
            LCID lcid, ITypeLib ** pptlib);

/* get path to registered typelib
 */
WINOLEAUTAPI QueryPathOfRegTypeLib(REFGUID guid, USHORT wMaj, USHORT wMin,
            LCID lcid, LPBSTR lpbstrPathName);

/* add typelib to registry
 */
/**
 * This function adds information about a type library to the system registry.
 *
 * @param ptlib Pointer to the type library being registered.
 * @param szFullPath Null-terminated string that contains the fully qualified path specification for
 *   the type library being registered.
 * @param szHelpDir Null-terminated string that contains the directory in which the Help file for
 *   the library being registered can be found. Can be NULL.
 *
 * @return One of the values obtained from the returned HRESULT and described in the following table
 *   is returned. Value Description S_OK Success. E_OUTOFMEMORY Out of memory. E_INVALIDARG One or
 *   more of the arguments is invalid. TYPE_E_IOERROR The function could not write to the file.
 *   TYPE_E_REGISTRYACCESS The system registration database could not be opened. TYPE_E_INVALIDSTATE
 *   The type library could not be opened.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 *
 * The function RegisterTypeLib can be used during application initialization to register the
 * application's type library correctly.
 *
 * In addition to filling in a complete registry entry under the type library key, RegisterTypeLib
 * adds entries for each of the dispinterfaces and Automation-compatible interfaces, including dual
 * interfaces. This information is required to create instances of these interfaces. Coclasses are
 * not registered (that is, RegisterTypeLib does not write any values to the CLSID key of the
 * coclass).
 */
WINOLEAUTAPI RegisterTypeLib(ITypeLib * ptlib, OLECHAR  *szFullPath,
            OLECHAR  *szHelpDir);

/* remove typelib from registry
 */

WINOLEAUTAPI UnRegisterTypeLib(REFGUID libID, WORD wVerMajor,
            WORD wVerMinor, LCID lcid, SYSKIND syskind);

WINOLEAUTAPI CreateTypeLib(SYSKIND syskind, const OLECHAR  *szFile,
            ICreateTypeLib ** ppctlib);

/**
 * This function creates a type library in the file/in-memory format that makes use of memory-mapped
 * files for 32-bit platforms. Its output parameter (ppctlib) points to a newly created object that
 * supports the ICreateTypeLib2 interface.
 *
 * Windows CE does not implement the ICreateTypeLib2::SaveAllChanges method.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI CreateTypeLib2(SYSKIND syskind, LPCOLESTR szFile,
            ICreateTypeLib2 **ppctlib);


/*---------------------------------------------------------------------*/
/*           IDispatch implementation support                          */
/*---------------------------------------------------------------------*/

typedef IDispatch * LPDISPATCH;

/**
 * This structure is used to describe a parameter accepted by a method or property.
 */
typedef struct tagPARAMDATA {
    /**
     * Null-terminated string that contains the parameter name. Names should follow standard conventions
     * for programming language access; that is, no embedded spaces or control characters, and 32 or
     * fewer characters. The name should be localized because each type description provides names for a
     * particular locale.
     */
    OLECHAR * szName;   /* parameter name */
    /**
     * The VARTYPE that will be used by the receiver. If more than one parameter type is accepted,
     * VT_VARIANT should be specified.
     */
    VARTYPE vt;         /* parameter type */
} PARAMDATA, * LPPARAMDATA;

/**
 * This structure is used to describe a method or property.
 */
typedef struct tagMETHODDATA {
    /**
     * Null-terminated string that contains the method name.
     */
    OLECHAR * szName;   /* method name */
    PARAMDATA * ppdata; /* pointer to an array of PARAMDATAs */
    /**
     * Identifier of the method, as used in IDispatch.
     */
    DISPID dispid;      /* method ID */
    /**
     * Index of the method in the VTBL of the interface. The indexes start with 0.
     */
    UINT iMeth;         /* method index */
    /**
     * Specifies the calling convention. The CDECL and Pascal calling conventions are supported by the
     * dispatch interface creation functions.
     */
    CALLCONV cc;        /* calling convention */
    /**
     * Number of arguments for the method.
     */
    UINT cArgs;         /* count of arguments */
    /**
     * Flags that indicate whether the method is used for getting or setting a property. DISPATCH_METHOD
     * indicates that this is not used for a property. DISPATCH_PROPERTYGET indicates that the method is
     * used to get a property value. DISPATCH_PROPERTYPUT indicates that the method is used to set the
     * value of a property. DISPATCH_PROPERTYPUTREF indicates that the method is used to make the
     * property refer to a passed-in object.
     */
    WORD wFlags;        /* same wFlags as on IDispatch::Invoke() */
    /**
     * Return type for the method.
     */
    VARTYPE vtReturn;
} METHODDATA, * LPMETHODDATA;

typedef struct tagINTERFACEDATA {
    METHODDATA * pmethdata;  /* pointer to an array of METHODDATAs */
    UINT cMembers;      /* count of members */
} INTERFACEDATA, * LPINTERFACEDATA;



/* Locate the parameter indicated by the given position, and
 * return it coerced to the given target VARTYPE (vtTarg).
 */
/**
 * This function retrieves a parameter from the DISPPARAMS structure, checks both named parameters
 * and positional parameters, and coerces the parameter to the specified type.
 *
 * @param pdispparams Pointer to the parameters passed to IDispatch::Invoke.
 * @param position Position of the parameter in the parameter list. DispGetParam starts at the end
 *   of the array, so if position is 0, the last parameter in the array is returned.
 * @param vtTarg Type the argument should be coerced to.
 * @param pvarResult Pointer to the variant to pass the parameter into.
 * @param puArgErr On return, pointer to the index of the argument that caused a DISP_E_TYPEMISMATCH
 *   error. This pointer is returned to Invoke to indicate the position of the argument in DISPPARAMS
 *   that caused the error.
 *
 * @return One of the values obtained from the returned HRESULT and described in the following table
 *   is returned. Value Description S_OK Success. DISP_E_BADVARTYPE The variant type vtTarg is not
 *   supported. DISP_E_OVERFLOW The retrieved parameter could not be coerced to the specified type.
 *   DISP_E_PARAMNOTFOUND The parameter indicated by position could not be found. DISP_E_TYPEMISMATCH
 *   The argument could not be coerced to the specified type. E_INVALIDARG One of the arguments was
 *   invalid. E_OUTOFMEMORY Insufficient memory to complete operation.
 *
 * The output parameter pvarResult must be a valid variant. Any existing contents are released in
 * the standard way. The contents of the variant are freed with VariantFree.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 *
 * If you have used DispGetParam to get the right side of a property put operation, the second
 * parameter should be DISPID_PROPERTYPUT. For example:
 *
 *     DispGetParam(&dispparams, DISPID_PROPERTYPUT, VT_BOOL, &varResult)
 *
 * Named parameters cannot be accessed positionally, and vice versa.
 */
WINOLEAUTAPI DispGetParam(DISPPARAMS * pdispparams, UINT position,
            VARTYPE vtTarg, VARIANT * pvarResult, UINT * puArgErr);

/* Automatic TypeInfo driven implementation of IDispatch::GetIDsOfNames()
 */
/**
 * This function uses type information to convert a set of names to DISPIDs.
 *
 * @param ptinfo Pointer to the type information for an interface. This type information is specific
 *   to one interface and language code, so it is not necessary to pass an interface identifier (IID)
 *   or LCID to this function.
 * @param rgszNames Array of name strings that can be the same array passed to DispInvoke in the
 *   DISPPARAMS structure. If cNames is greater than 1, the first name is interpreted as a method
 *   name, and subsequent names are interpreted as parameters to that method.
 * @param cNames Number of elements in rgszNames.
 * @param rgdispid Pointer to an array of DISPIDs to be filled in by this function. The first
 *   identifier corresponds to the method name. Subsequent identifiers are interpreted as parameters
 *   to the method.
 *
 * @return One of the values obtained from the returned HRESULT and described in the following table
 *   is returned. Value Description S_OK The interface is supported. E_INVALIDARG One of the arguments
 *   is invalid. DISP_E_UNKNOWNNAME One or more of the given names were not known. The returned array
 *   of DISPIDs contains DISPID_UNKNOWN for each entry that corresponds to an unknown name. Other
 *   return codes Any of the ITypeInfo::Invoke errors can also be returned.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI DispGetIDsOfNames(ITypeInfo * ptinfo, OLECHAR ** rgszNames,
            UINT cNames, DISPID * rgdispid);

/* Automatic TypeInfo driven implementation of IDispatch::Invoke()
 */
/**
 * This function automatically calls member functions on an interface, given the type information
 * for the interface.
 *
 * @param _this Pointer to an implementation of the IDispatch interface described by ptinfo.
 * @param ptinfo Pointer to the type information that describes the interface.
 * @param dispidMember Identifies the member. Use GetIDsOfNames or the object's documentation to
 *   obtain the DISPID.
 * @param wFlags Flags describing the context of the Invoke call, as follows: Value Description
 *   DISPATCH_METHOD The member is invoked as a method. If a property has the same name, both this and
 *   the DISPATCH_PROPERTYGET flag can be set. DISPATCH_PROPERTYGET The member is retrieved as a
 *   property or data member. DISPATCH_PROPERTYPUT The member is changed as a property or data member.
 *   DISPATCH_PROPERTYPUTREF The member is changed by a reference assignment, rather than a value
 *   assignment. This flag is valid only when the property accepts a reference to an object.
 * @param pparams Pointer to a structure that contains an array of arguments, an array of argument
 *   DISPIDs for named arguments, and counts for number of elements in the arrays.
 * @param pvarResult Pointer to where the result is to be stored, or NULL if the caller expects no
 *   result. This argument is ignored if DISPATCH_PROPERTYPUT or DISPATCH_PROPERTYPUTREF is specified.
 * @param pexcepinfo Pointer to a structure that contains exception information. This structure
 *   should be filled in if DISP_E_EXCEPTION is returned.
 * @param puArgErr Index within rgvarg of the first argument that has an error. Arguments are stored
 *   in pdispparams->rgvarg in reverse order, so the first argument is the one with the highest index
 *   in the array. This parameter is returned only when the resulting return value is
 *   DISP_E_TYPEMISMATCH or DISP_E_PARAMNOTFOUND.
 *
 * @return One of the values obtained from the returned HRESULT and described in the following table
 *   is returned. Value Description S_OK Success. DISP_E_BADPARAMCOUNT The number of elements provided
 *   in DISPPARAMS is different from the number of arguments accepted by the method or property.
 *   DISP_E_BADVARTYPE One of the arguments in DISPPARAMS is not a valid variant type.
 *   DISP_E_EXCEPTION The application needs to raise an exception. In this case, the structure passed
 *   in pexcepinfo should be filled in. DISP_E_MEMBERNOTFOUND The requested member does not exist.
 *   DISP_E_NONAMEDARGS This implementation of IDispatch does not support named arguments.
 *   DISP_E_OVERFLOW One of the arguments in DISPPARAMS could not be coerced to the specified type.
 *   DISP_E_PARAMNOTFOUND One of the parameter IDs does not correspond to a parameter on the method.
 *   In this case, puArgErr is set to the first argument that contains the error.
 *   DISP_E_PARAMNOTOPTIONAL A required parameter was omitted. DISP_E_TYPEMISMATCH One or more of the
 *   arguments could not be coerced. The index of the first parameter with the incorrect type within
 *   rgvarg is returned in puArgErr. E_INVALIDARG One of the arguments is invalid. E_OUTOFMEMORY
 *   Insufficient memory to complete the operation. Other return codes Any of the ITypeInfo::Invoke
 *   errors can also be returned.
 *
 * The parameter this is a pointer to an implementation of the interface that is being deferred to.
 * DispInvoke builds a stack frame, coerces parameters using standard coercion rules, pushes them on
 * the stack, and then calls the correct member function in the VTBL.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI DispInvoke(void * _this, ITypeInfo * ptinfo, DISPID dispidMember,
            WORD wFlags, DISPPARAMS * pparams, VARIANT * pvarResult,
            EXCEPINFO * pexcepinfo, UINT * puArgErr);

/* Construct a TypeInfo from an interface data description
 */
WINOLEAUTAPI CreateDispTypeInfo(INTERFACEDATA * pidata, LCID lcid,
            ITypeInfo ** pptinfo);

/* Create an instance of the standard TypeInfo driven IDispatch
 * implementation.
 */
WINOLEAUTAPI CreateStdDispatch(IUnknown * punkOuter, void * pvThis,
            ITypeInfo * ptinfo, IUnknown ** ppunkStdDisp);

/* Low-level helper for IDispatch::Invoke() provides machine independence
 * for customized Invoke().
 */
WINOLEAUTAPI DispCallFunc(void * pvInstance, ULONG oVft, CALLCONV cc,
            VARTYPE vtReturn, UINT  cActuals, VARTYPE * prgvt,
            VARIANTARG ** prgpvarg, VARIANT * pvargResult);


/*---------------------------------------------------------------------*/
/*            Active Object Registration API                           */
/*---------------------------------------------------------------------*/

/* flags for RegisterActiveObject */
#define ACTIVEOBJECT_STRONG 0x0
#define ACTIVEOBJECT_WEAK 0x1

WINOLEAUTAPI RegisterActiveObject(IUnknown * punk, REFCLSID rclsid,
            DWORD dwFlags, DWORD * pdwRegister);

WINOLEAUTAPI RevokeActiveObject(DWORD dwRegister, void * pvReserved);

WINOLEAUTAPI GetActiveObject(REFCLSID rclsid, void * pvReserved,
            IUnknown ** ppunk);

/*---------------------------------------------------------------------*/
/*                           ErrorInfo API                             */
/*---------------------------------------------------------------------*/

/**
 * This function sets the error information object for the current thread of execution.
 *
 * @param dwReserved Reserved for future use; set to zero.
 * @param perrinfo Pointer to an error object.
 *
 * @return One of the values obtained from the returned HRESULT and described in the following table
 *   is returned. Value Description S_OK Success.
 *
 * This function releases the existing error information object, if one exists, and sets the pointer
 * to perrinfo. Use this function after creating an error object that associates the object with the
 * current thread of execution.
 *
 * If the property or method that calls SetErrorInfo is called by DispInvoke, then DispInvoke will
 * fill the EXCEPINFO parameter with the values specified in the error information object.
 * DispInvoke will return DISP_E_EXCEPTION when the property or method returns a failure return
 * value for DispInvoke.
 *
 * Virtual function table (VTBL) binding controllers that do not use IDispatch::Invoke can get the
 * error information object by using GetErrorInfo. This allows an object that supports a dual
 * interface to use SetErrorInfo, regardless of whether the client uses VTBL binding or IDispatch.
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAUTAPI SetErrorInfo(ULONG dwReserved, IErrorInfo * perrinfo);
/**
 * This function obtains the error information pointer set by the previous call to SetErrorInfo in
 * the current logical thread.
 *
 * @param dwReserved Reserved for future use; set to zero.
 * @param pperrinfo Pointer to a pointer to a system-implemented generic error object.
 *
 * @return One of the values obtained from the returned HRESULT and described in the following table
 *   is returned. Value Description S_OK Success. S_FALSE There was no error object to return.
 *
 * This function returns a pointer to the most recently set IErrorInfo pointer in the current
 * logical thread. It transfers ownership of the error object to the caller, and clears the error
 * state for the thread.
 */
WINOLEAUTAPI GetErrorInfo(ULONG dwReserved, IErrorInfo ** pperrinfo);
/**
 * This function creates an instance of a generic error object.
 *
 * @param pperrinfo Pointer to a pointer to a system-implemented generic error object.
 *
 * @return One of the values obtained from the returned HRESULT and described in the following table
 *   is returned. Value Description S_OK Success. E_OUTOFMEMORY Could not create the error object.
 *
 * This function returns a pointer to a generic error object, which you can use with QueryInterface
 * on ICreateErrorInfo to set its contents. You can then pass the resulting object to SetErrorInfo.
 * The generic error object implements both ICreateErrorInfo and IErrorInfo.
 */
WINOLEAUTAPI CreateErrorInfo(ICreateErrorInfo ** pperrinfo);

/*---------------------------------------------------------------------*/
/*                           MISC API                                  */
/*---------------------------------------------------------------------*/

WINOLEAUTAPI_(ULONG) OaBuildVersion(void);

WINOLEAUTAPI_(void) ClearCustData(LPCUSTDATA pCustData);

// Declare variant access functions.

#if __STDC__ || defined(NONAMELESSUNION)
#define V_UNION(X, Y)   ((X)->n1.n2.n3.Y)
#define V_VT(X)         ((X)->n1.n2.vt)
#else
#define V_UNION(X, Y)   ((X)->Y)
#define V_VT(X)         ((X)->vt)
#endif

/* Variant access macros
 */
#define V_ISBYREF(X)     (V_VT(X)&VT_BYREF)
#define V_ISARRAY(X)     (V_VT(X)&VT_ARRAY)
#define V_ISVECTOR(X)    (V_VT(X)&VT_VECTOR)
#define V_NONE(X)        V_I2(X)

#define V_UI1(X)         V_UNION(X, bVal)
#define V_UI1REF(X)      V_UNION(X, pbVal)
#define V_I2(X)          V_UNION(X, iVal)
#define V_I2REF(X)       V_UNION(X, piVal)
#define V_I4(X)          V_UNION(X, lVal)
#define V_I4REF(X)       V_UNION(X, plVal)
#define V_R4(X)          V_UNION(X, fltVal)
#define V_R4REF(X)       V_UNION(X, pfltVal)
#define V_R8(X)          V_UNION(X, dblVal)
#define V_R8REF(X)       V_UNION(X, pdblVal)
#define V_I1(X)          V_UNION(X, cVal)
#define V_I1REF(X)       V_UNION(X, pcVal)
#define V_UI2(X)         V_UNION(X, uiVal)
#define V_UI2REF(X)      V_UNION(X, puiVal)
#define V_UI4(X)         V_UNION(X, ulVal)
#define V_UI4REF(X)      V_UNION(X, pulVal)
#define V_INT(X)         V_UNION(X, intVal)
#define V_INTREF(X)      V_UNION(X, pintVal)
#define V_UINT(X)        V_UNION(X, uintVal)
#define V_UINTREF(X)     V_UNION(X, puintVal)
#define V_CY(X)          V_UNION(X, cyVal)
#define V_CYREF(X)       V_UNION(X, pcyVal)
#define V_DATE(X)        V_UNION(X, date)
#define V_DATEREF(X)     V_UNION(X, pdate)
#define V_BSTR(X)        V_UNION(X, bstrVal)
#define V_BSTRREF(X)     V_UNION(X, pbstrVal)
#define V_DISPATCH(X)    V_UNION(X, pdispVal)
#define V_DISPATCHREF(X) V_UNION(X, ppdispVal)
#define V_ERROR(X)       V_UNION(X, scode)
#define V_ERRORREF(X)    V_UNION(X, pscode)
#define V_BOOL(X)        V_UNION(X, boolVal)
#define V_BOOLREF(X)     V_UNION(X, pboolVal)
#define V_UNKNOWN(X)     V_UNION(X, punkVal)
#define V_UNKNOWNREF(X)  V_UNION(X, ppunkVal)
#define V_VARIANTREF(X)  V_UNION(X, pvarVal)
#define V_ARRAY(X)       V_UNION(X, parray)
#define V_ARRAYREF(X)    V_UNION(X, pparray)
#define V_BYREF(X)       V_UNION(X, byref)

#define V_DECIMAL(X)     V_UNION(X, decVal)
#define V_DECIMALREF(X)  V_UNION(X, pdecVal)

#ifndef RC_INVOKED
#include <poppack.h>
#endif // RC_INVOKED

#endif     // __OLEAUTO_H__
