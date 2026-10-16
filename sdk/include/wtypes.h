//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//  Copyright (C) Microsoft Corporation, 1992 - 1997.
//
//--------------------------------------------------------------------------

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.00.44 */
/* at Fri Jul 12 18:09:25 1996
 */
/* Compiler settings for wtypes.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )
#include "rpc.h"
#include "rpcndr.h"

#ifndef __wtypes_h__
#define __wtypes_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/****************************************
 * Generated header for interface: __MIDL__intf_0000
 * at Fri Jul 12 18:09:25 1996
 * using MIDL 3.00.44
 ****************************************/
/* [local] */ 



extern RPC_IF_HANDLE __MIDL__intf_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL__intf_0000_v0_0_s_ifspec;

#ifndef __IWinTypes_INTERFACE_DEFINED__
#define __IWinTypes_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IWinTypes
 * at Fri Jul 12 18:09:25 1996
 * using MIDL 3.00.44
 ****************************************/
/* [auto_handle][unique][version][uuid] */ 


typedef struct  tagRemHGLOBAL
    {
    long fNullHGlobal;
    unsigned long cbData;
    /* [size_is] */ byte data[ 1 ];
    }	RemHGLOBAL;

typedef struct  tagRemHMETAFILEPICT
    {
    long mm;
    long xExt;
    long yExt;
    unsigned long cbData;
    /* [size_is] */ byte data[ 1 ];
    }	RemHMETAFILEPICT;

typedef struct  tagRemHENHMETAFILE
    {
    unsigned long cbData;
    /* [size_is] */ byte data[ 1 ];
    }	RemHENHMETAFILE;

typedef struct  tagRemHBITMAP
    {
    unsigned long cbData;
    /* [size_is] */ byte data[ 1 ];
    }	RemHBITMAP;

typedef struct  tagRemHPALETTE
    {
    unsigned long cbData;
    /* [size_is] */ byte data[ 1 ];
    }	RemHPALETTE;

typedef struct  tagRemBRUSH
    {
    unsigned long cbData;
    /* [size_is] */ byte data[ 1 ];
    }	RemHBRUSH;

#if !defined(_WIN32) && !defined(_MPPC_)
// The following code is for Win16 only
#ifndef WINAPI          // If not included with 3.1 headers...
#define FAR             _far
#define PASCAL          _pascal
#define CDECL           _cdecl
#define VOID            void
#define WINAPI      FAR PASCAL
#define CALLBACK    FAR PASCAL
#ifndef FALSE
#define FALSE 0
#define TRUE 1
#endif // !FALSE
#ifndef _BYTE_DEFINED
#define _BYTE_DEFINED
typedef unsigned char BYTE;

#endif // !_BYTE_DEFINED
#ifndef _WORD_DEFINED
#define _WORD_DEFINED
typedef unsigned short WORD;

#endif // !_WORD_DEFINED
typedef unsigned int UINT;

typedef int INT;

typedef long BOOL;

#ifndef _LONG_DEFINED
#define _LONG_DEFINED
typedef long LONG;

#endif // !_LONG_DEFINED
#ifndef _WPARAM_DEFINED
#define _WPARAM_DEFINED
typedef UINT WPARAM;

#endif // _WPARAM_DEFINED
#ifndef _DWORD_DEFINED
#define _DWORD_DEFINED
typedef unsigned long DWORD;

#endif // !_DWORD_DEFINED
#ifndef _LPARAM_DEFINED
#define _LPARAM_DEFINED
typedef LONG LPARAM;

#endif // !_LPARAM_DEFINED
#ifndef _LRESULT_DEFINED
#define _LRESULT_DEFINED
typedef LONG LRESULT;

#endif // !_LRESULT_DEFINED
typedef void __RPC_FAR *HANDLE;

typedef void __RPC_FAR *HMODULE;

typedef void __RPC_FAR *HINSTANCE;

typedef void __RPC_FAR *HRGN;

typedef void __RPC_FAR *HTASK;

typedef void __RPC_FAR *HKEY;

typedef void __RPC_FAR *HDESK;

typedef void __RPC_FAR *HMF;

typedef void __RPC_FAR *HEMF;

typedef void __RPC_FAR *HPEN;

typedef void __RPC_FAR *HRSRC;

typedef void __RPC_FAR *HSTR;

typedef void __RPC_FAR *HWINSTA;

typedef void __RPC_FAR *HKL;

typedef void __RPC_FAR *HGDIOBJ;

typedef HANDLE HDWP;

#ifndef _HFILE_DEFINED
#define _HFILE_DEFINED
typedef INT HFILE;

#endif // !_HFILE_DEFINED
#ifndef _LPWORD_DEFINED
#define _LPWORD_DEFINED
typedef WORD __RPC_FAR *LPWORD;

#endif // !_LPWORD_DEFINED
#ifndef _LPDWORD_DEFINED
#define _LPDWORD_DEFINED
typedef DWORD __RPC_FAR *LPDWORD;

#endif // !_LPDWORD_DEFINED
typedef char CHAR;

typedef /* [string] */ CHAR __RPC_FAR *LPSTR;

typedef /* [string] */ const CHAR __RPC_FAR *LPCSTR;

#ifndef _WCHAR_DEFINED
#define _WCHAR_DEFINED
typedef wchar_t WCHAR;

typedef WCHAR TCHAR;

#endif // !_WCHAR_DEFINED
typedef /* [string] */ WCHAR __RPC_FAR *LPWSTR;

typedef /* [string] */ TCHAR __RPC_FAR *LPTSTR;

typedef /* [string] */ const WCHAR __RPC_FAR *LPCWSTR;

typedef /* [string] */ const TCHAR __RPC_FAR *LPCTSTR;

/**
 * This structure specifies the color and usage of a logical palette entry. A logical palette is
 * defined by a LOGPALETTE structure.
 *
 * Window CE ignores the peFlags member. It should be initialized to 0.
 */
typedef struct  tagPALETTEENTRY
    {
    /**
     * Specifies a red intensity value for the palette entry.
     */
    BYTE peRed;
    /**
     * Specifies a green intensity value for the palette entry.
     */
    BYTE peGreen;
    /**
     * Specifies a blue intensity value for the palette entry.
     */
    BYTE peBlue;
    /**
     * Specifies how the palette entry is to be used. The peFlags member may be set to NULL or one of
     * the following values: Value Description PC_EXPLICIT Specifies that the low-order word of the
     * logical palette entry designates a hardware palette index. This flag allows the application to
     * show the contents of the display device palette. PC_NOCOLLAPSE Specifies that the color be placed
     * in an unused entry in the system palette instead of being matched to an existing color in the
     * system palette. If there are no unused entries in the system palette, the color is matched
     * normally. Once this color is in the system palette, colors in other logical palettes can be
     * matched to this color. PC_RESERVED Specifies that the logical palette entry be used for palette
     * animation. This flag prevents other windows from matching colors to the palette entry since the
     * color frequently changes. If an unused system-palette entry is available, the color is placed in
     * that entry. Otherwise, the color is not available for animation.
     */
    BYTE peFlags;
    }	PALETTEENTRY;

typedef struct tagPALETTEENTRY __RPC_FAR *PPALETTEENTRY;

typedef struct tagPALETTEENTRY __RPC_FAR *LPPALETTEENTRY;

#if 0
/**
 * This structure defines a logical color palette.
 *
 * The colors in the palette-entry table should appear in order of importance because entries
 * earlier in the logical palette are most likely to be placed in the system palette.
 */
typedef struct  tagLOGPALETTE
    {
    /**
     * Specifies the version number of the system.
     */
    WORD palVersion;
    /**
     * Specifies the number of entries in the logical color palette.
     */
    WORD palNumEntries;
    /**
     * Specifies an array of PALETTEENTRY structures that define the color and usage of each entry in
     * the logical palette.
     */
    /* [size_is] */ PALETTEENTRY palPalEntry[ 1 ];
    }	LOGPALETTE;

typedef struct tagLOGPALETTE __RPC_FAR *PLOGPALETTE;

typedef struct tagLOGPALETTE __RPC_FAR *LPLOGPALETTE;

#else
/**
 * This structure defines a logical color palette.
 *
 * The colors in the palette-entry table should appear in order of importance because entries
 * earlier in the logical palette are most likely to be placed in the system palette.
 */
typedef struct tagLOGPALETTE {
    /**
     * Specifies the version number of the system.
     */
    WORD        palVersion;
    /**
     * Specifies the number of entries in the logical color palette.
     */
    WORD        palNumEntries;
    /**
     * Specifies an array of PALETTEENTRY structures that define the color and usage of each entry in
     * the logical palette.
     */
    PALETTEENTRY        palPalEntry[1];
} LOGPALETTE, *PLOGPALETTE, *LPLOGPALETTE;
#endif
#ifndef _COLORREF_DEFINED
#define _COLORREF_DEFINED
typedef DWORD COLORREF;

#endif // !_COLORREF_DEFINED
#ifndef _LPCOLORREF_DEFINED
#define _LPCOLORREF_DEFINED
typedef DWORD __RPC_FAR *LPCOLORREF;

#endif // !_LPCOLORREF_DEFINED
typedef HANDLE __RPC_FAR *LPHANDLE;

typedef struct  _RECTL
    {
    LONG left;
    LONG top;
    LONG right;
    LONG bottom;
    }	RECTL;

typedef struct _RECTL __RPC_FAR *PRECTL;

typedef struct _RECTL __RPC_FAR *LPRECTL;

/**
 * This structure defines the x- and y-coordinates of a point.
 */
typedef struct  tagPOINT
    {
    /**
     * Specifies the x-coordinate of the point.
     */
    LONG x;
    /**
     * Specifies the y-coordinate of the point.
     */
    LONG y;
    }	POINT;

typedef struct tagPOINT __RPC_FAR *PPOINT;

typedef struct tagPOINT __RPC_FAR *LPPOINT;

typedef struct  _POINTL
    {
    LONG x;
    LONG y;
    }	POINTL;

typedef struct _POINTL __RPC_FAR *PPOINTL;

#ifndef WIN16
/**
 * This structure specifies the width and height of a rectangle.
 *
 * The rectangle dimensions stored in this structure may correspond to viewport extents, window
 * extents, text extents, bitmap dimensions, or the aspect-ratio filter for some extended functions.
 */
typedef struct  tagSIZE
    {
    /**
     * Specifies the rectangle's width.
     */
    LONG cx;
    /**
     * Specifies the rectangle's height.
     */
    LONG cy;
    }	SIZE;

typedef struct tagSIZE __RPC_FAR *PSIZE;

typedef struct tagSIZE __RPC_FAR *LPSIZE;

#else // WIN16
/**
 * This structure specifies the width and height of a rectangle.
 *
 * The rectangle dimensions stored in this structure may correspond to viewport extents, window
 * extents, text extents, bitmap dimensions, or the aspect-ratio filter for some extended functions.
 */
typedef struct tagSIZE
{
    /**
     * Specifies the rectangle's width.
     */
    INT cx;
    /**
     * Specifies the rectangle's height.
     */
    INT cy;
} SIZE, *PSIZE, *LPSIZE;
#endif // WIN16
typedef struct  tagSIZEL
    {
    LONG cx;
    LONG cy;
    }	SIZEL;

typedef struct tagSIZEL __RPC_FAR *PSIZEL;

typedef struct tagSIZEL __RPC_FAR *LPSIZEL;

#endif  //WINAPI
#endif  //!WIN32 && !MPPC
#if defined(_WIN32) && !defined(OLE2ANSI)
typedef WCHAR OLECHAR;

typedef /* [string] */ OLECHAR __RPC_FAR *LPOLESTR;

typedef /* [string] */ const OLECHAR __RPC_FAR *LPCOLESTR;

#define OLESTR(str) L##str

#else

typedef char      OLECHAR;
typedef LPSTR     LPOLESTR;
typedef LPCSTR    LPCOLESTR;
#define OLESTR(str) str
#endif
#ifndef _WINDEF_
typedef const RECTL __RPC_FAR *LPCRECTL;

typedef void __RPC_FAR *PVOID;

typedef void __RPC_FAR *LPVOID;

typedef float FLOAT;

/**
 * This structure defines the coordinates of the upper-left and lower-right corners of a rectangle.
 *
 * When RECT is passed to the FillRect function, the rectangle is filled up to, but not including,
 * the right column and bottom row of pixels. This structure is identical to the RECTL structure.
 */
typedef struct  tagRECT
    {
    /**
     * Specifies the x-coordinate of the upper-left corner of the rectangle.
     */
    LONG left;
    /**
     * Specifies the y-coordinate of the upper-left corner of the rectangle.
     */
    LONG top;
    /**
     * Specifies the x-coordinate of the lower-right corner of the rectangle.
     */
    LONG right;
    /**
     * Specifies the y-coordinate of the lower-right corner of the rectangle.
     */
    LONG bottom;
    }	RECT;

typedef struct tagRECT __RPC_FAR *PRECT;

typedef struct tagRECT __RPC_FAR *LPRECT;

typedef const RECT __RPC_FAR *LPCRECT;

#endif  //_WINDEF_
typedef unsigned char UCHAR;

typedef short SHORT;

typedef unsigned short USHORT;

typedef DWORD ULONG;

typedef double DOUBLE;

#ifndef _DWORDLONG_
typedef MIDL_uhyper DWORDLONG;

typedef DWORDLONG __RPC_FAR *PDWORDLONG;

#endif // !_DWORDLONG_
#ifndef _ULONGLONG_
typedef hyper LONGLONG;

typedef MIDL_uhyper ULONGLONG;

typedef LONGLONG __RPC_FAR *PLONGLONG;

typedef ULONGLONG __RPC_FAR *PULONGLONG;

#endif // _ULONGLONG_
#if 0
typedef struct  _LARGE_INTEGER
    {
    LONGLONG QuadPart;
    }	LARGE_INTEGER;

typedef LARGE_INTEGER __RPC_FAR *PLARGE_INTEGER;

/**
 * This union provides a 64-bit data type which is accessible as two DWORDs or as a single
 * DWORDLONG.
 *
 * The ULARGE_INTEGER structure is actually a union. If your compiler has built-in support for
 * 64-bit integers, use the QuadPart member to store the 64-bit integer. Otherwise, use the LowPart
 * and HighPart members to store the 64-bit integer.
 */
typedef struct  _ULARGE_INTEGER
    {
    /**
     * Specifies a 64-bit unsigned integer.
     */
    ULONGLONG QuadPart;
    }	ULARGE_INTEGER;

#endif // 0
#ifndef _WINBASE_
#ifndef _FILETIME_
#define _FILETIME_
/**
 * This structure is a 64-bit value representing the number of 100-nanosecond intervals since
 * January 1, 1601.
 *
 * The FILETIME data structure is used in the time conversion functions between MS-DOS and Win32.
 */
typedef struct  _FILETIME
    {
    /**
     * Specifies the low 32 bits of the Win32 date/time value.
     */
    DWORD dwLowDateTime;
    /**
     * Specifies the upper 32 bits of the Win32 date/time value.
     */
    DWORD dwHighDateTime;
    }	FILETIME;

typedef struct _FILETIME __RPC_FAR *PFILETIME;

typedef struct _FILETIME __RPC_FAR *LPFILETIME;

#endif // !_FILETIME
#ifndef _SYSTEMTIME_
#define _SYSTEMTIME_
/**
 * This structure represents a date and time using individual members for the month, day, year,
 * weekday, hour, minute, second, and millisecond.
 *
 * It is not recommended that you add and subtract values from the SYSTEMTIME structure to obtain
 * relative times. Instead, you should
 *
 * Convert the SYSTEMTIME structure to a FILETIME structure.
 *
 * Copy the resulting FILETIME structure to a ULARGE_INTEGER structure.
 *
 * Use normal 64-bit arithmetic on the ULARGE_INTEGER value.
 */
typedef struct  _SYSTEMTIME
    {
    /**
     * Specifies the current year.
     */
    WORD wYear;
    /**
     * Specifies the current month; January = 1, February = 2, and so on.
     */
    WORD wMonth;
    /**
     * Specifies the current day of the week; Sunday = 0, Monday = 1, and so on.
     */
    WORD wDayOfWeek;
    /**
     * Specifies the current day of the month.
     */
    WORD wDay;
    /**
     * Specifies the current hour.
     */
    WORD wHour;
    /**
     * Specifies the current minute.
     */
    WORD wMinute;
    /**
     * Specifies the current second.
     */
    WORD wSecond;
    /**
     * Specifies the current millisecond.
     */
    WORD wMilliseconds;
    }	SYSTEMTIME;

typedef struct _SYSTEMTIME __RPC_FAR *PSYSTEMTIME;

typedef struct _SYSTEMTIME __RPC_FAR *LPSYSTEMTIME;

#endif // !_SYSTEMTIME
#ifndef _SECURITY_ATTRIBUTES_
#define _SECURITY_ATTRIBUTES_
typedef struct  _SECURITY_ATTRIBUTES
    {
    DWORD nLength;
    /* [size_is] */ LPVOID lpSecurityDescriptor;
    BOOL bInheritHandle;
    }	SECURITY_ATTRIBUTES;

typedef struct _SECURITY_ATTRIBUTES __RPC_FAR *PSECURITY_ATTRIBUTES;

typedef struct _SECURITY_ATTRIBUTES __RPC_FAR *LPSECURITY_ATTRIBUTES;

#endif // !_SECURITY_ATTRIBUTES_
#ifndef SECURITY_DESCRIPTOR_REVISION
typedef USHORT SECURITY_DESCRIPTOR_CONTROL;

typedef USHORT __RPC_FAR *PSECURITY_DESCRIPTOR_CONTROL;

typedef PVOID PSID;

typedef struct  _ACL
    {
    UCHAR AclRevision;
    UCHAR Sbz1;
    USHORT AclSize;
    USHORT AceCount;
    USHORT Sbz2;
    }	ACL;

typedef ACL __RPC_FAR *PACL;

typedef struct  _SECURITY_DESCRIPTOR
    {
    UCHAR Revision;
    UCHAR Sbz1;
    SECURITY_DESCRIPTOR_CONTROL Control;
    PSID Owner;
    PSID Group;
    PACL Sacl;
    PACL Dacl;
    }	SECURITY_DESCRIPTOR;

typedef struct _SECURITY_DESCRIPTOR __RPC_FAR *PISECURITY_DESCRIPTOR;

#endif // !SECURITY_DESCRIPTOR_REVISION
#endif //_WINBASE_
typedef struct  _COAUTHIDENTITY
    {
    /* [size_is] */ USHORT __RPC_FAR *User;
    ULONG UserLength;
    /* [size_is] */ USHORT __RPC_FAR *Domain;
    ULONG DomainLength;
    /* [size_is] */ USHORT __RPC_FAR *Password;
    ULONG PasswordLength;
    ULONG Flags;
    }	COAUTHIDENTITY;

/**
 * This structure is used to determine the authentication settings.
 *
 * A pointer to a COAUTHINFO structure is a member of the COSERVERINFO structure. The COAUTHINFO
 * structure provides security information to object creation functions across the network. The
 * values of the COAUTHINFO structure determine the authentication settings used while making a
 * remote activation request from the client machine to the server machine.
 *
 * If pAuthInfo in COSERVERINFO is set to NULL, NTLMSSP with the identity of the actual client will
 * be used. However, a non-NULL COAUTHINFO structure can be specified for pAuthInfo to meet any one
 * of the following special needs:
 *
 * To specify a different client identity for machine remote activations. The specified identity
 * will be used for the launch permission check on the server rather than the real client identity.
 *
 * To specify that Kerberos, rather than NTLMSSP, is used for machine remote activation. A
 * nondefault client identity may or may not be specified.
 *
 * To request unsecure activation.
 *
 * To specify a proprietary authentication service.
 *
 * Specifying a COAUTHINFO structure allows DCOM activations to work correctly with security
 * providers other than NTLMSSP. You can also specify additional security information used during
 * remote activations for interoperability with alternate implementations of DCOM.
 *
 * For more information on the uses of COAUTHINFO, see COSERVERINFO.
 */
typedef struct  _COAUTHINFO
    {
    /**
     * [in] Specifies a single DWORD value from the list of RPC_C_AUTHN_xxx constants indicating the
     * authentication service to use. It may be RPC_C_AUTHN_NONE if no authentication is required.
     * RPC_C_AUTHN_WINNT is the default and RPC_C_AUTHN_GSS_KERBEROS is also supported.
     */
    DWORD dwAuthnSvc;
    /**
     * [in] Specifies a single DWORD value from the list of RPC_C_AUTHZ_xxx constants indicating the
     * authorization service to use. If you are using the NT authentication service, use
     * RPC_C_AUTHZ_NONE.
     */
    DWORD dwAuthzSvc;
    /**
     * Pointer to a character string that indicates the server principal name to use with the
     * authentication service. If you are using RPC_C_AUTHN_WINNT, the principal name must be NULL.
     */
    LPWSTR pwszServerPrincName;
    /**
     * [in] Specifies a single DWORD value from the list of RPC_C_AUTHN_LEVEL_xxx constants indicating
     * the authentication level to use.
     */
    DWORD dwAuthnLevel;
    /**
     * [in] Specifies the impersonation level to be used. This value must be
     * RPC_C_IMP_LEVEL_IMPERSONATE.
     */
    DWORD dwImpersonationLevel;
    /**
     * Pointer to a COAUTHIDENTITY structure that establishes a nondefault client identity. If NULL, the
     * actual identity of the client is used. Values of structure members are authentication-service
     * specific. This value must be NULL if dwAuthnSvc is not NTLMSSP or Kerberos. The form of the
     * COAUTHIDENTITY structure is identical to that of the Windows NT SEC_WINNT_AUTH_IDENTITY
     * structure.
     */
    COAUTHIDENTITY __RPC_FAR *pAuthIdentityData;
    /**
     * [in] Specifies a DWORD defining flags that indicate the further capabilities of this proxy.
     * Currently, this value must be EOAC_NONE.
     */
    DWORD dwCapabilities;
    }	COAUTHINFO;

/**
 * This structure is used to identify a remote machine resource to the new or enhanced activation
 * functions.
 *
 * The COSERVERINFO structure is used primarily to identify a remote system in object creation
 * functions. Machine resources are named using the naming scheme of the network transport. By
 * default, all UNC and DNS names names are allowed.
 *
 * If pAuthInfo is set to NULL, NTLMSSP with the identity of the actual client will be used. To meet
 * any one of the needs in the following list, pAuthInfo can be set to point to a non-NULL
 * COAUTHINFO structure:
 *
 * To specify a different client identity for machine remote activations. The specified identity
 * will be used for the launch permission check on the server rather than the real client identity.
 *
 * To specify that Kerberos, rather than NTLMSSP, is used for machine remote activation. A
 * nondefault client identity may or may not be specified.
 *
 * To request unsecure activation.
 *
 * To specify a proprietary authentication service.
 *
 * If pAuthInfo is not NULL, those values will be used to specify the authentication settings for
 * the remote call. These settings will be passed to RpcBindingSetAuthInfoEx.
 *
 * If the pAuthInfo member is not specified, any values in the AppID section of the registry will be
 * used to override the following default authentication settings:
 *
 * - dwAuthnSvc: RPC_C_AUTHN_WINNT
 *
 * - dwAuthzSvc: RPC_C_AUTHZ_NONE
 *
 * - pszServerPrincName: NULL
 *
 * - dwAuthnLevel: RPC_C_AUTHN_LEVEL_CONNECT
 *
 * - dwImpersonationLevel: RPC_C_IMP_LEVEL_IMPERSONATE
 *
 * - pvAuthIdentityData: NULL
 *
 * - dwCapabilities: RPC_C_QOS_CAPABILITIES_DEFAULT
 */
typedef struct  _COSERVERINFO
    {
    /**
     * Reserved for future use; set to zero.
     */
    DWORD dwReserved1;
    /**
     * Pointer to the name of the machine to be used.
     */
    LPWSTR pwszName;
    /**
     * Set to a pointer to a COAUTHINFO structure to override the default activation security for
     * machine remote activations. Otherwise, set to NULL to indicate that default values should be
     * used. For more information, see the Remarks section.
     */
    COAUTHINFO __RPC_FAR *pAuthInfo;
    /**
     * Reserved for future use; set to zero.
     */
    DWORD dwReserved2;
    }	COSERVERINFO;

typedef LONG SCODE;

#ifndef _HRESULT_DEFINED
#define _HRESULT_DEFINED
typedef LONG HRESULT;

#endif // !_HRESULT_DEFINED
typedef SCODE __RPC_FAR *PSCODE;

#ifndef GUID_DEFINED
#define GUID_DEFINED
typedef struct  _GUID
    {
    DWORD Data1;
    WORD Data2;
    WORD Data3;
    BYTE Data4[ 8 ];
    }	GUID;

#endif // !GUID_DEFINED
#if !defined( __LPGUID_DEFINED__ )
#define __LPGUID_DEFINED__
typedef GUID __RPC_FAR *LPGUID;

#endif // !__LPGUID_DEFINED__
#ifndef __OBJECTID_DEFINED
#define __OBJECTID_DEFINED
#define _OBJECTID_DEFINED
typedef struct  _OBJECTID
    {
    GUID Lineage;
    unsigned long Uniquifier;
    }	OBJECTID;

#endif // !_OBJECTID_DEFINED
#if !defined( __IID_DEFINED__ )
#define __IID_DEFINED__
typedef GUID IID;

typedef IID __RPC_FAR *LPIID;

#define IID_NULL            GUID_NULL
#define IsEqualIID(riid1, riid2) IsEqualGUID(riid1, riid2)
typedef GUID CLSID;

typedef CLSID __RPC_FAR *LPCLSID;

#define CLSID_NULL          GUID_NULL
#define IsEqualCLSID(rclsid1, rclsid2) IsEqualGUID(rclsid1, rclsid2)
typedef GUID FMTID;

typedef FMTID __RPC_FAR *LPFMTID;

#define FMTID_NULL          GUID_NULL
#define IsEqualFMTID(rfmtid1, rfmtid2) IsEqualGUID(rfmtid1, rfmtid2)
#if 0
typedef GUID __RPC_FAR *REFGUID;

typedef IID __RPC_FAR *REFIID;

typedef CLSID __RPC_FAR *REFCLSID;

typedef FMTID __RPC_FAR *REFFMTID;

#endif // 0
#if defined(__cplusplus)
#ifndef _REFGUID_DEFINED
#define _REFGUID_DEFINED
#define REFGUID             const GUID &
#endif // !_REFGUID_DEFINED
#ifndef _REFIID_DEFINED
#define _REFIID_DEFINED
#define REFIID              const IID &
#endif // !_REFIID_DEFINED
#ifndef _REFCLSID_DEFINED
#define _REFCLSID_DEFINED
#define REFCLSID            const CLSID &
#endif // !_REFCLSID_DEFINED
#ifndef _REFFMTID_DEFINED
#define _REFFMTID_DEFINED
#define REFFMTID            const FMTID &
#endif // !_REFFMTID_DEFINED
#else // !__cplusplus
#ifndef _REFGUID_DEFINED
#define _REFGUID_DEFINED
#define REFGUID             const GUID * const
#endif // !_REFGUID_DEFINED
#ifndef _REFIID_DEFINED
#define _REFIID_DEFINED
#define REFIID              const IID * const
#endif // !_REFIID_DEFINED
#ifndef _REFCLSID_DEFINED
#define _REFCLSID_DEFINED
#define REFCLSID            const CLSID * const
#endif // !_REFCLSID_DEFINED
#ifndef _REFFMTID_DEFINED
#define _REFFMTID_DEFINED
#define REFFMTID            const FMTID * const
#endif // !_REFFMTID_DEFINED
#endif // !__cplusplus
#endif // !__IID_DEFINED__
typedef 
enum tagMEMCTX
    {	MEMCTX_TASK	= 1,
	MEMCTX_SHARED	= 2,
	MEMCTX_MACSYSTEM	= 3,
	MEMCTX_UNKNOWN	= -1,
	MEMCTX_SAME	= -2
    }	MEMCTX;

#ifndef _ROTFLAGS_DEFINED
#define _ROTFLAGS_DEFINED
#define ROTFLAGS_REGISTRATIONKEEPSALIVE 0x1
#define ROTFLAGS_ALLOWANYCLIENT 0x2
#endif // !_ROTFLAGS_DEFINED
#ifndef _ROT_COMPARE_MAX_DEFINED
#define _ROT_COMPARE_MAX_DEFINED
#define ROT_COMPARE_MAX 2048
#endif // !_ROT_COMPARE_MAX_DEFINED
typedef 
enum tagCLSCTX
    {	CLSCTX_INPROC_SERVER	= 0x1,
	CLSCTX_INPROC_HANDLER	= 0x2,
	CLSCTX_LOCAL_SERVER	= 0x4,
	CLSCTX_INPROC_SERVER16	= 0x8,
	CLSCTX_REMOTE_SERVER	= 0x10,
	CLSCTX_INPROC_HANDLER16	= 0x20,
	CLSCTX_INPROC_SERVERX86	= 0x40,
	CLSCTX_INPROC_HANDLERX86	= 0x80
    }	CLSCTX;

typedef 
enum tagMSHLFLAGS
    {	MSHLFLAGS_NORMAL	= 0,
	MSHLFLAGS_TABLESTRONG	= 1,
	MSHLFLAGS_TABLEWEAK	= 2,
	MSHLFLAGS_NOPING	= 4
    }	MSHLFLAGS;

typedef 
enum tagMSHCTX
    {	MSHCTX_LOCAL	= 0,
	MSHCTX_NOSHAREDMEM	= 1,
	MSHCTX_DIFFERENTMACHINE	= 2,
	MSHCTX_INPROC	= 3
    }	MSHCTX;

typedef 
enum tagDVASPECT
    {	DVASPECT_CONTENT	= 1,
	DVASPECT_THUMBNAIL	= 2,
	DVASPECT_ICON	= 4,
	DVASPECT_DOCPRINT	= 8
    }	DVASPECT;

typedef 
enum tagSTGC
    {	STGC_DEFAULT	= 0,
	STGC_OVERWRITE	= 1,
	STGC_ONLYIFCURRENT	= 2,
	STGC_DANGEROUSLYCOMMITMERELYTODISKCACHE	= 4
    }	STGC;

typedef 
enum tagSTGMOVE
    {	STGMOVE_MOVE	= 0,
	STGMOVE_COPY	= 1,
	STGMOVE_SHALLOWCOPY	= 2
    }	STGMOVE;

typedef 
enum tagSTATFLAG
    {	STATFLAG_DEFAULT	= 0,
	STATFLAG_NONAME	= 1,
	STATFLAG_NOOPEN	= 2
    }	STATFLAG;

typedef /* [context_handle] */ void __RPC_FAR *HCONTEXT;

#ifndef _LCID_DEFINED
#define _LCID_DEFINED
typedef DWORD LCID;

#endif // !_LCID_DEFINED
typedef struct  _BYTE_BLOB
    {
    unsigned long clSize;
    /* [size_is] */ byte abData[ 1 ];
    }	BYTE_BLOB;

typedef /* [unique] */ BYTE_BLOB __RPC_FAR *UP_BYTE_BLOB;

typedef struct  _WORD_BLOB
    {
    unsigned long clSize;
    /* [size_is] */ unsigned short asData[ 1 ];
    }	WORD_BLOB;

typedef /* [unique] */ WORD_BLOB __RPC_FAR *UP_WORD_BLOB;

typedef struct  _DWORD_BLOB
    {
    unsigned long clSize;
    /* [size_is] */ unsigned long alData[ 1 ];
    }	DWORD_BLOB;

typedef /* [unique] */ DWORD_BLOB __RPC_FAR *UP_DWORD_BLOB;

typedef struct  _FLAGGED_BYTE_BLOB
    {
    unsigned long fFlags;
    unsigned long clSize;
    /* [size_is] */ byte abData[ 1 ];
    }	FLAGGED_BYTE_BLOB;

typedef /* [unique] */ FLAGGED_BYTE_BLOB __RPC_FAR *UP_FLAGGED_BYTE_BLOB;

typedef struct  _FLAGGED_WORD_BLOB
    {
    unsigned long fFlags;
    unsigned long clSize;
    /* [size_is] */ unsigned short asData[ 1 ];
    }	FLAGGED_WORD_BLOB;

typedef /* [unique] */ FLAGGED_WORD_BLOB __RPC_FAR *UP_FLAGGED_WORD_BLOB;

typedef struct  _BYTE_SIZEDARR
    {
    unsigned long clSize;
    /* [size_is] */ byte __RPC_FAR *pData;
    }	BYTE_SIZEDARR;

typedef struct  _SHORT_SIZEDARR
    {
    unsigned long clSize;
    /* [size_is] */ unsigned short __RPC_FAR *pData;
    }	WORD_SIZEDARR;

typedef struct  _LONG_SIZEDARR
    {
    unsigned long clSize;
    /* [size_is] */ unsigned long __RPC_FAR *pData;
    }	DWORD_SIZEDARR;

typedef struct  _HYPER_SIZEDARR
    {
    unsigned long clSize;
    /* [size_is] */ hyper __RPC_FAR *pData;
    }	HYPER_SIZEDARR;

#define	WDT_INPROC_CALL	( 0x48746457 )

#define	WDT_REMOTE_CALL	( 0x52746457 )

typedef struct  _userCLIPFORMAT
    {
    long fContext;
    /* [switch_is] */ /* [switch_type] */ union __MIDL_IWinTypes_0001
        {
        /* [case()] */ DWORD dwValue;
        /* [case()][string] */ wchar_t __RPC_FAR *pwszName;
        }	u;
    }	userCLIPFORMAT;

typedef /* [unique] */ userCLIPFORMAT __RPC_FAR *wireCLIPFORMAT;

typedef /* [wire_marshal] */ WORD CLIPFORMAT;

typedef struct  _GDI_NONREMOTE
    {
    long fContext;
    /* [switch_is] */ /* [switch_type] */ union __MIDL_IWinTypes_0002
        {
        /* [case()] */ long hInproc;
        /* [case()] */ DWORD_BLOB __RPC_FAR *hRemote;
        }	u;
    }	GDI_NONREMOTE;

typedef struct  _userHGLOBAL
    {
    long fContext;
    /* [switch_is] */ /* [switch_type] */ union __MIDL_IWinTypes_0003
        {
        /* [case()] */ long hInproc;
        /* [case()] */ FLAGGED_BYTE_BLOB __RPC_FAR *hRemote;
        /* [default] */ long hGlobal;
        }	u;
    }	userHGLOBAL;

typedef /* [unique] */ userHGLOBAL __RPC_FAR *wireHGLOBAL;

typedef struct  _userHMETAFILE
    {
    long fContext;
    /* [switch_is] */ /* [switch_type] */ union __MIDL_IWinTypes_0004
        {
        /* [case()] */ long hInproc;
        /* [case()] */ BYTE_BLOB __RPC_FAR *hRemote;
        /* [default] */ long hGlobal;
        }	u;
    }	userHMETAFILE;

typedef struct  _remoteMETAFILEPICT
    {
    long mm;
    long xExt;
    long yExt;
    userHMETAFILE __RPC_FAR *hMF;
    }	remoteMETAFILEPICT;

typedef struct  _userHMETAFILEPICT
    {
    long fContext;
    /* [switch_is] */ /* [switch_type] */ union __MIDL_IWinTypes_0005
        {
        /* [case()] */ long hInproc;
        /* [case()] */ remoteMETAFILEPICT __RPC_FAR *hRemote;
        /* [default] */ long hGlobal;
        }	u;
    }	userHMETAFILEPICT;

typedef struct  _userHENHMETAFILE
    {
    long fContext;
    /* [switch_is] */ /* [switch_type] */ union __MIDL_IWinTypes_0006
        {
        /* [case()] */ long hInproc;
        /* [case()] */ BYTE_BLOB __RPC_FAR *hRemote;
        /* [default] */ long hGlobal;
        }	u;
    }	userHENHMETAFILE;

typedef struct  _userBITMAP
    {
    LONG bmType;
    LONG bmWidth;
    LONG bmHeight;
    LONG bmWidthBytes;
    WORD bmPlanes;
    WORD bmBitsPixel;
    ULONG cbSize;
    /* [size_is] */ byte pBuffer[ 1 ];
    }	userBITMAP;

typedef struct  _userHBITMAP
    {
    long fContext;
    /* [switch_is] */ /* [switch_type] */ union __MIDL_IWinTypes_0007
        {
        /* [case()] */ long hInproc;
        /* [case()] */ userBITMAP __RPC_FAR *hRemote;
        /* [default] */ long hGlobal;
        }	u;
    }	userHBITMAP;

typedef struct  tagrpcLOGPALETTE
    {
    WORD palVersion;
    WORD palNumEntries;
    /* [size_is] */ PALETTEENTRY palPalEntry[ 1 ];
    }	rpcLOGPALETTE;

typedef struct  _userHPALETTE
    {
    long fContext;
    /* [switch_is] */ /* [switch_type] */ union __MIDL_IWinTypes_0008
        {
        /* [case()] */ long hInproc;
        /* [case()] */ rpcLOGPALETTE __RPC_FAR *hRemote;
        /* [default] */ long hGlobal;
        }	u;
    }	userHPALETTE;

typedef struct  _RemotableHandle
    {
    long fContext;
    /* [switch_is] */ /* [switch_type] */ union __MIDL_IWinTypes_0009
        {
        /* [case()] */ long hInproc;
        /* [case()] */ long hRemote;
        }	u;
    }	RemotableHandle;

typedef /* [unique] */ RemotableHandle __RPC_FAR *wireHWND;

typedef /* [unique] */ RemotableHandle __RPC_FAR *wireHMENU;

typedef /* [unique] */ RemotableHandle __RPC_FAR *wireHACCEL;

typedef /* [unique] */ RemotableHandle __RPC_FAR *wireHBRUSH;

typedef /* [unique] */ RemotableHandle __RPC_FAR *wireHFONT;

typedef /* [unique] */ RemotableHandle __RPC_FAR *wireHDC;

typedef /* [unique] */ RemotableHandle __RPC_FAR *wireHICON;

#if 0
typedef /* [wire_marshal] */ void __RPC_FAR *HWND;

typedef /* [wire_marshal] */ void __RPC_FAR *HMENU;

typedef /* [wire_marshal] */ void __RPC_FAR *HACCEL;

typedef /* [wire_marshal] */ void __RPC_FAR *HBRUSH;

typedef /* [wire_marshal] */ void __RPC_FAR *HFONT;

typedef /* [wire_marshal] */ void __RPC_FAR *HDC;

typedef /* [wire_marshal] */ void __RPC_FAR *HICON;

#ifndef _HCURSOR_DEFINED
#define _HCURSOR_DEFINED
typedef HICON HCURSOR;

#endif // !_HCURSOR_DEFINED
/* tagTEXTMETRICW was copied from wingdi.h for MIDL */
/**
 * This structure contains basic information about a physical font.
 */
typedef struct  tagTEXTMETRICW
    {
    /**
     * Specifies the height (ascent + descent) of characters.
     */
    LONG tmHeight;
    /**
     * Specifies the ascent (units above the base line) of characters.
     */
    LONG tmAscent;
    /**
     * Specifies the descent (units below the base line) of characters.
     */
    LONG tmDescent;
    /**
     * Specifies the amount of leading (space) inside the bounds set by the tmHeight member. Accent
     * marks and other diacritical characters may occur in this area. The designer may set this member
     * to zero.
     */
    LONG tmInternalLeading;
    /**
     * Specifies the amount of extra leading (space) that the application adds between rows. Since this
     * area is outside the font, it contains no marks and is not altered by text output calls in either
     * OPAQUE or TRANSPARENT mode. The designer may set this member to zero.
     */
    LONG tmExternalLeading;
    /**
     * Specifies the average width of characters in the font (generally defined as the width of the
     * letter x). This value does not include the overhang required for bold or italic characters.
     */
    LONG tmAveCharWidth;
    /**
     * Specifies the width of the widest character in the font.
     */
    LONG tmMaxCharWidth;
    /**
     * Specifies the weight of the font.
     */
    LONG tmWeight;
    /**
     * Specifies the extra width per string that may be added to some synthesized fonts. When
     * synthesizing some attributes, such as bold or italic, graphics device interface (GDI) or a device
     * may have to add width to a string on both a per-character and per-string basis. For example, GDI
     * makes a string bold by expanding the spacing of each character and overstriking by an offset
     * value; it italicizes a font by shearing the string. In either case, there is an overhang past the
     * basic string. For bold strings, the overhang is the distance by which the overstrike is offset.
     * For italic strings, the overhang is the amount the top of the font is sheared past the bottom of
     * the font.
     *
     * The tmOverhang member enables the application to determine how much of the character width
     * returned by a GetTextExtentPoint32 function call on a single character is the actual character
     * width and how much is the per-string extra width. The actual width is the extent minus the
     * overhang.
     */
    LONG tmOverhang;
    /**
     * Specifies the horizontal aspect of the device for which the font was designed.
     */
    LONG tmDigitizedAspectX;
    /**
     * Specifies the vertical aspect of the device for which the font was designed. The ratio of the
     * tmDigitizedAspectX and tmDigitizedAspectY members is the aspect ratio of the device for which the
     * font was designed.
     */
    LONG tmDigitizedAspectY;
    /**
     * Specifies the value of the first character defined in the font.
     */
    WCHAR tmFirstChar;
    /**
     * Specifies the value of the last character defined in the font.
     */
    WCHAR tmLastChar;
    /**
     * Specifies the value of the character to be substituted for characters not in the font.
     */
    WCHAR tmDefaultChar;
    /**
     * Specifies the value of the character that will be used to define word breaks for text
     * justification.
     */
    WCHAR tmBreakChar;
    /**
     * Specifies an italic font if it is nonzero.
     */
    BYTE tmItalic;
    /**
     * Specifies an underlined font if it is nonzero.
     */
    BYTE tmUnderlined;
    /**
     * Specifies a strikeout font if it is nonzero.
     */
    BYTE tmStruckOut;
    /**
     * Specifies information about the pitch, the technology, and the family of a physical font.
     *
     * The four low-order bits of this member specify information about the pitch and the technology of
     * the font. A constant is defined for each of the four bits: Value Description TMPF_FIXED_PITCH If
     * this bit is set the font is a variable pitch font. If this bit is clear the font is a fixed pitch
     * font. Note that those meanings are the opposite of what the constant name implies. TMPF_VECTOR If
     * this bit is set, the font is a vector font. TMPF_TRUETYPE If this bit is set, the font is a
     * TrueType font. TMPF_DEVICE If this bit is set, the font is a device font.
     *
     * An application should carefully test for qualities encoded in these low-order bits, making no
     * arbitrary assumptions. For example, besides having their own bits set, TrueType and PostScript
     * fonts set the TMPF_VECTOR bit. A monospace bitmap font has all of these low-order bits clear; a
     * proportional bitmap font sets the TMPF_FIXED_PITCH bit. A Postscript printer device font sets the
     * TMPF_DEVICE, TMPF_VECTOR, and TMPF_FIXED_PITCH bits.
     *
     * The four high-order bits of tmPitchAndFamily designate the font's font family. An application can
     * use the value 0xF0 and the bitwise AND operator to mask out the four low-order bits of
     * tmPitchAndFamily, thus obtaining a value that can be directly compared with font family names to
     * find an identical match. For information about font families, see the description of the LOGFONT
     * structure.
     */
    BYTE tmPitchAndFamily;
    /**
     * Specifies the character set of the font. The character set is one of the following values:
     * ANSI_CHARSET DEFAULT_CHARSET SYMBOL_CHARSET SHIFTJIS_CHARSET HANGUL_CHARSET GB2312_CHARSET
     * CHINESEBIG5_CHARSET OEM_CHARSET JOHAB_CHARSET HEBREW_CHARSET ARABIC_CHARSET GREEK_CHARSET
     * TURKISH_CHARSET VIETNAMESE_CHARSET THAI_CHARSET EASTEUROPE_CHARSET RUSSIAN_CHARSET MAC_CHARSET
     * BALTIC_CHARSET
     */
    BYTE tmCharSet;
    }	TEXTMETRICW;

#endif //0
#ifndef _WIN32           // The following code is for Win16 only
#ifndef WINAPI          // If not included with 3.1 headers...
/**
 * This structure contains message information from a thread's message queue.
 *
 * On Windows CE-based devices that use a stylus and touch screen instead of a mouse, the pt member
 * contains the coordinates of the last position touched on the screen, rather than the coordinates
 * of the current cursor position.
 *
 * If you need mouse cursor support in your application, use the Windows CE Iconcurs component
 * rather than the Windows CE Icon component and the Windows CE Mcursor component rather than the
 * Windows CE Cursor component.
 */
typedef struct  tagMSG
    {
    /**
     * Handle to the window whose window procedure receives the message.
     */
    HWND hwnd;
    /**
     * Specifies the message identifier.
     */
    UINT message;
    /**
     * Specifies additional information about the message. The exact meaning depends on the value of the
     * message member.
     */
    WPARAM wParam;
    /**
     * Specifies additional information about the message. The exact meaning depends on the value of the
     * message member.
     */
    LPARAM lParam;
    /**
     * Specifies the time at which the message was posted.
     */
    DWORD time;
    /**
     * Specifies the cursor position, in screen coordinates, when the message was posted.
     */
    POINT pt;
    }	MSG;

typedef struct tagMSG __RPC_FAR *PMSG;

typedef struct tagMSG __RPC_FAR *NPMSG;

typedef struct tagMSG __RPC_FAR *LPMSG;

#endif // _WIN32
#endif // WINAPI
typedef /* [unique] */ userHBITMAP __RPC_FAR *wireHBITMAP;

typedef /* [unique] */ userHPALETTE __RPC_FAR *wireHPALETTE;

typedef /* [unique] */ userHENHMETAFILE __RPC_FAR *wireHENHMETAFILE;

typedef /* [unique] */ userHMETAFILE __RPC_FAR *wireHMETAFILE;

typedef /* [unique] */ userHMETAFILEPICT __RPC_FAR *wireHMETAFILEPICT;

#if 0
typedef /* [wire_marshal] */ void __RPC_FAR *HGLOBAL;

typedef HGLOBAL HLOCAL;

typedef /* [wire_marshal] */ void __RPC_FAR *HBITMAP;

typedef /* [wire_marshal] */ void __RPC_FAR *HPALETTE;

typedef /* [wire_marshal] */ void __RPC_FAR *HENHMETAFILE;

typedef /* [wire_marshal] */ void __RPC_FAR *HMETAFILE;

#endif //0
typedef /* [wire_marshal] */ void __RPC_FAR *HMETAFILEPICT;



extern RPC_IF_HANDLE IWinTypes_v0_1_c_ifspec;
extern RPC_IF_HANDLE IWinTypes_v0_1_s_ifspec;
#endif /* __IWinTypes_INTERFACE_DEFINED__ */

/****************************************
 * Generated header for interface: __MIDL__intf_0001
 * at Fri Jul 12 18:09:25 1996
 * using MIDL 3.00.44
 ****************************************/
/* [local] */ 


typedef double DATE;

#ifndef _tagCY_DEFINED
#define _tagCY_DEFINED
#define _CY_DEFINED
#if 0
/* the following isn't the real definition of CY, but it is */
/* what RPC knows how to remote */
typedef struct  tagCY
    {
    LONGLONG int64;
    }	CY;

#else /* 0 */
/* real definition that makes the C++ compiler happy */
typedef union tagCY {
    struct {
#ifdef _MAC
        long      Hi;
        long Lo;
#else
        unsigned long Lo;
        long      Hi;
#endif
    };
    LONGLONG int64;
} CY;
#endif /* 0 */
#endif /* _tagCY_DEFINED */
#if 0 /* _tagDEC_DEFINED */
/* The following isn't the real definition of Decimal type, */
/* but it is what RPC knows how to remote */
typedef struct  tagDEC
    {
    USHORT wReserved;
    BYTE scale;
    BYTE sign;
    ULONG Hi32;
    ULONGLONG Lo64;
    }	DECIMAL;

#else /* _tagDEC_DEFINED */
/* real definition that makes the C++ compiler happy */
typedef struct tagDEC {
    USHORT wReserved;
    union {
        struct {
            BYTE scale;
            BYTE sign;
        };
        USHORT signscale;
    };
    ULONG Hi32;
    union {
        struct {
#ifdef _MAC
            ULONG Mid32;
            ULONG Lo32;
#else
            ULONG Lo32;
            ULONG Mid32;
#endif
        };
        ULONGLONG Lo64;
    };
} DECIMAL;
#define DECIMAL_NEG ((BYTE)0x80)
#define DECIMAL_SETZERO(dec) \
        {(dec).Lo64 = 0; (dec).Hi32 = 0; (dec).signscale = 0;}
#endif /* _tagDEC_DEFINED */
typedef /* [unique] */ FLAGGED_WORD_BLOB __RPC_FAR *wireBSTR;

typedef /* [wire_marshal] */ OLECHAR __RPC_FAR *BSTR;

typedef BSTR __RPC_FAR *LPBSTR;

/* 0 == FALSE, -1 == TRUE */
typedef short VARIANT_BOOL;

#if !__STDC__ && (_MSC_VER <= 1000)
/* For backward compatibility */
typedef VARIANT_BOOL _VARIANT_BOOL;

#else
/* ANSI C/C++ reserve bool as keyword */
#define _VARIANT_BOOL    /##/
#endif
typedef boolean BOOLEAN;

#define VARIANT_TRUE ((VARIANT_BOOL)0xffff)
#define VARIANT_FALSE ((VARIANT_BOOL)0)
#ifndef _tagBLOB_DEFINED
#define _tagBLOB_DEFINED
#define _BLOB_DEFINED
#define _LPBLOB_DEFINED
typedef struct  tagBLOB
    {
    ULONG cbSize;
    /* [size_is] */ BYTE __RPC_FAR *pBlobData;
    }	BLOB;

typedef struct tagBLOB __RPC_FAR *LPBLOB;

#endif
typedef struct  tagCLIPDATA
    {
    ULONG cbSize;
    long ulClipFmt;
    /* [size_is] */ BYTE __RPC_FAR *pClipData;
    }	CLIPDATA;

// Macro to calculate the size of the above pClipData
#define CBPCLIPDATA(clipdata)    ( (clipdata).cbSize - sizeof((clipdata).ulClipFmt) )
typedef unsigned short VARTYPE;

/*
 * VARENUM usage key,
 *
 * * [V] - may appear in a VARIANT
 * * [T] - may appear in a TYPEDESC
 * * [P] - may appear in an OLE property set
 * * [S] - may appear in a Safe Array
 *
 *
 *  VT_EMPTY            [V]   [P]     nothing
 *  VT_NULL             [V]   [P]     SQL style Null
 *  VT_I2               [V][T][P][S]  2 byte signed int
 *  VT_I4               [V][T][P][S]  4 byte signed int
 *  VT_R4               [V][T][P][S]  4 byte real
 *  VT_R8               [V][T][P][S]  8 byte real
 *  VT_CY               [V][T][P][S]  currency
 *  VT_DATE             [V][T][P][S]  date
 *  VT_BSTR             [V][T][P][S]  OLE Automation string
 *  VT_DISPATCH         [V][T][P][S]  IDispatch *
 *  VT_ERROR            [V][T]   [S]  SCODE
 *  VT_BOOL             [V][T][P][S]  True=-1, False=0
 *  VT_VARIANT          [V][T][P][S]  VARIANT *
 *  VT_UNKNOWN          [V][T]   [S]  IUnknown *
 *  VT_DECIMAL          [V][T]   [S]  16 byte fixed point
 *  VT_I1                  [T]        signed char
 *  VT_UI1              [V][T][P][S]  unsigned char
 *  VT_UI2                 [T][P]     unsigned short
 *  VT_UI4                 [T][P]     unsigned short
 *  VT_I8                  [T][P]     signed 64-bit int
 *  VT_UI8                 [T][P]     unsigned 64-bit int
 *  VT_INT                 [T]        signed machine int
 *  VT_UINT                [T]        unsigned machine int
 *  VT_VOID                [T]        C style void
 *  VT_HRESULT             [T]        Standard return type
 *  VT_PTR                 [T]        pointer type
 *  VT_SAFEARRAY           [T]        (use VT_ARRAY in VARIANT)
 *  VT_CARRAY              [T]        C style array
 *  VT_USERDEFINED         [T]        user defined type
 *  VT_LPSTR               [T][P]     null terminated string
 *  VT_LPWSTR              [T][P]     wide null terminated string
 *  VT_FILETIME               [P]     FILETIME
 *  VT_BLOB                   [P]     Length prefixed bytes
 *  VT_STREAM                 [P]     Name of the stream follows
 *  VT_STORAGE                [P]     Name of the storage follows
 *  VT_STREAMED_OBJECT        [P]     Stream contains an object
 *  VT_STORED_OBJECT          [P]     Storage contains an object
 *  VT_BLOB_OBJECT            [P]     Blob contains an object
 *  VT_CF                     [P]     Clipboard format
 *  VT_CLSID                  [P]     A Class ID
 *  VT_VECTOR                 [P]     simple counted array
 *  VT_ARRAY            [V]           SAFEARRAY*
 *  VT_BYREF            [V]           void* for local use
 */

enum VARENUM
    {	VT_EMPTY	= 0,
	VT_NULL	= 1,
	VT_I2	= 2,
	VT_I4	= 3,
	VT_R4	= 4,
	VT_R8	= 5,
	VT_CY	= 6,
	VT_DATE	= 7,
	VT_BSTR	= 8,
	VT_DISPATCH	= 9,
	VT_ERROR	= 10,
	VT_BOOL	= 11,
	VT_VARIANT	= 12,
	VT_UNKNOWN	= 13,
	VT_DECIMAL	= 14,
	VT_I1	= 16,
	VT_UI1	= 17,
	VT_UI2	= 18,
	VT_UI4	= 19,
	VT_I8	= 20,
	VT_UI8	= 21,
	VT_INT	= 22,
	VT_UINT	= 23,
	VT_VOID	= 24,
	VT_HRESULT	= 25,
	VT_PTR	= 26,
	VT_SAFEARRAY	= 27,
	VT_CARRAY	= 28,
	VT_USERDEFINED	= 29,
	VT_LPSTR	= 30,
	VT_LPWSTR	= 31,
	VT_FILETIME	= 64,
	VT_BLOB	= 65,
	VT_STREAM	= 66,
	VT_STORAGE	= 67,
	VT_STREAMED_OBJECT	= 68,
	VT_STORED_OBJECT	= 69,
	VT_BLOB_OBJECT	= 70,
	VT_CF	= 71,
	VT_CLSID	= 72,
	VT_VECTOR	= 0x1000,
	VT_ARRAY	= 0x2000,
	VT_BYREF	= 0x4000,
	VT_RESERVED	= 0x8000,
	VT_ILLEGAL	= 0xffff,
	VT_ILLEGALMASKED	= 0xfff,
	VT_TYPEMASK	= 0xfff
    };
typedef ULONG PROPID;



extern RPC_IF_HANDLE __MIDL__intf_0001_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL__intf_0001_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
