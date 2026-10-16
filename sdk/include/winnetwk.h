/*++

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.
Copyright (c) 1995, 1996, 1997  Microsoft Corporation

Module Name:

    winnetwk.h

Abstract:

    Standard WINNET Header File for WIN32

Notes:

        
--*/

// @CESYSGEN IF CE_MODULES_REDIR

#ifndef _WINNETWK_
#define _WINNETWK_


#ifdef __cplusplus
extern "C" {
#endif

//
// Network types
//

#define     WNNC_NET_MSNET      0x00010000
#define     WNNC_NET_LANMAN     0x00020000
#define     WNNC_NET_NETWARE    0x00030000
#define     WNNC_NET_VINES      0x00040000
#define     WNNC_NET_10NET      0x00050000
#define     WNNC_NET_LOCUS      0x00060000
#define     WNNC_NET_SUN_PC_NFS 0x00070000
#define     WNNC_NET_LANSTEP    0x00080000
#define     WNNC_NET_9TILES     0x00090000
#define     WNNC_NET_LANTASTIC  0x000A0000
#define     WNNC_NET_AS400      0x000B0000
#define     WNNC_NET_FTP_NFS    0x000C0000
#define     WNNC_NET_PATHWORKS  0x000D0000
#define     WNNC_NET_LIFENET    0x000E0000
#define     WNNC_NET_POWERLAN   0x000F0000
#define     WNNC_NET_BWNFS		0x00100000
#define     WNNC_NET_COGENT		0x00110000
#define     WNNC_NET_FARALLON	0x00120000
#define     WNNC_NET_APPLETALK	0x00130000
#define     WNNC_NET_INTERGRAPH	0x00140000


//
//  Network Resources.
//

#define RESOURCE_CONNECTED      0x00000001
#define RESOURCE_GLOBALNET      0x00000002
#define RESOURCE_REMEMBERED     0x00000003
#if(WINVER >= 0x0400)
#define RESOURCE_RECENT         0x00000004
#define RESOURCE_CONTEXT        0x00000005
#endif /* WINVER >= 0x0400 */

#define RESOURCETYPE_ANY        0x00000000
#define RESOURCETYPE_DISK       0x00000001
#define RESOURCETYPE_PRINT      0x00000002
#if(WINVER >= 0x0400)
#define RESOURCETYPE_RESERVED   0x00000008
#endif /* WINVER >= 0x0400 */
#define RESOURCETYPE_UNKNOWN    0xFFFFFFFF

#define RESOURCEUSAGE_CONNECTABLE   0x00000001
#define RESOURCEUSAGE_CONTAINER     0x00000002
#if(WINVER >= 0x0400)
#define RESOURCEUSAGE_NOLOCALDEVICE 0x00000004
#define RESOURCEUSAGE_SIBLING       0x00000008
#define RESOURCEUSAGE_ALL           (RESOURCEUSAGE_CONNECTABLE | RESOURCEUSAGE_CONTAINER)
#endif /* WINVER >= 0x0400 */
#define RESOURCEUSAGE_RESERVED      0x80000000

#define RESOURCEDISPLAYTYPE_GENERIC        0x00000000
#define RESOURCEDISPLAYTYPE_DOMAIN         0x00000001
#define RESOURCEDISPLAYTYPE_SERVER         0x00000002
#define RESOURCEDISPLAYTYPE_SHARE          0x00000003
#define RESOURCEDISPLAYTYPE_FILE           0x00000004
#define RESOURCEDISPLAYTYPE_GROUP          0x00000005
#if(WINVER >= 0x0400)
#define RESOURCEDISPLAYTYPE_NETWORK        0x00000006
#define RESOURCEDISPLAYTYPE_ROOT           0x00000007
#define RESOURCEDISPLAYTYPE_SHAREADMIN     0x00000008
#define RESOURCEDISPLAYTYPE_DIRECTORY      0x00000009
#endif /* WINVER >= 0x0400 */
#define RESOURCEDISPLAYTYPE_TREE           0x0000000A

/**
 * This structure that holds the network resource data. It is returned during enumeration of
 * resources on the network and during enumeration of currently connected resources.
 *
 * Windows CE does not support paths with the prefix of "drive letters." The lpLocalName member can
 * contain any string of up to 99 characters long. If the local name is "*", the default name is
 * constructed based on the remote name: "<share> on <server>."
 */
typedef struct  _NETRESOURCEA {
    /**
     * Specifies the scope of the enumeration. Currently, this member can be one of the following
     * values: Value Description RESOURCE_CONNECTED Currently connected resources (the dwUsage member is
     * undefined). RESOURCE_GLOBALNET Resources on the network. RESOURCE_REMEMBERED Remembered
     * (persistent) connections (dwUsage is undefined).
     */
    DWORD    dwScope;
    /**
     * Specifies a bitmask that gives the resource type. Currently, this member can be one of the
     * following values: Value Description RESOURCETYPE_ANY All resources RESOURCETYPE_DISK Disk
     * resources RESOURCETYPE_PRINT Print resources
     */
    DWORD    dwType;
    /**
     * Specifies how the network object should be displayed in a network browsing user interface.
     * Currently, this member can be the following values: Value Description RESOURCEDISPLAYTYPE_DOMAIN
     * The object should be displayed as a domain. RESOURCEDISPLAYTYPE_GENERIC The method used to
     * display the object does not matter. RESOURCEDISPLAYTYPE_SERVER The object should be displayed as
     * a server. RESOURCEDISPLAYTYPE_SHARE The object should be displayed as a share.
     */
    DWORD    dwDisplayType;
    /**
     * Specifies a bitmask that gives the resource usage. This member is defined only if dwScope is
     * RESOURCE_GLOBALNET. Currently, this member can be one of the following values: Value Description
     * RESOURCEUSAGE_CONNECTABLE This is a connectable resource; the name pointed to by the lpRemoteName
     * member can be passed to the WNetAddConnection function to make a network connection.
     * RESOURCEUSAGE_CONTAINER This is a container resource; the name pointed to by the lpRemoteName
     * member can be passed to the WNetOpenEnum function to enumerate the resources in the container.
     */
    DWORD    dwUsage;
    /**
     * Long pointer to the local name of a network resource if the dwScope member is RESOURCE_CONNECTED
     * or RESOURCE_REMEMBERED. This member is NULL if the connection does not have a local name.
     */
    LPSTR    lpLocalName;
    /**
     * Long pointer to a remote network name if the entry is a network resource.
     *
     * If the entry is a current or persistent connection, lpRemoteName points to the network name
     * associated with the name pointed to by the lpLocalName member.
     */
    LPSTR    lpRemoteName;
    /**
     * Long pointer to a provider-supplied comment.
     */
    LPSTR    lpComment ;
    /**
     * Long pointer to the name of the provider owning this resource. This member can be NULL if the
     * provider name is unknown.
     */
    LPSTR    lpProvider;
}NETRESOURCEA, *LPNETRESOURCEA;
/**
 * This structure that holds the network resource data. It is returned during enumeration of
 * resources on the network and during enumeration of currently connected resources.
 *
 * Windows CE does not support paths with the prefix of "drive letters." The lpLocalName member can
 * contain any string of up to 99 characters long. If the local name is "*", the default name is
 * constructed based on the remote name: "<share> on <server>."
 */
typedef struct  _NETRESOURCEW {
    /**
     * Specifies the scope of the enumeration. Currently, this member can be one of the following
     * values: Value Description RESOURCE_CONNECTED Currently connected resources (the dwUsage member is
     * undefined). RESOURCE_GLOBALNET Resources on the network. RESOURCE_REMEMBERED Remembered
     * (persistent) connections (dwUsage is undefined).
     */
    DWORD    dwScope;
    /**
     * Specifies a bitmask that gives the resource type. Currently, this member can be one of the
     * following values: Value Description RESOURCETYPE_ANY All resources RESOURCETYPE_DISK Disk
     * resources RESOURCETYPE_PRINT Print resources
     */
    DWORD    dwType;
    /**
     * Specifies how the network object should be displayed in a network browsing user interface.
     * Currently, this member can be the following values: Value Description RESOURCEDISPLAYTYPE_DOMAIN
     * The object should be displayed as a domain. RESOURCEDISPLAYTYPE_GENERIC The method used to
     * display the object does not matter. RESOURCEDISPLAYTYPE_SERVER The object should be displayed as
     * a server. RESOURCEDISPLAYTYPE_SHARE The object should be displayed as a share.
     */
    DWORD    dwDisplayType;
    /**
     * Specifies a bitmask that gives the resource usage. This member is defined only if dwScope is
     * RESOURCE_GLOBALNET. Currently, this member can be one of the following values: Value Description
     * RESOURCEUSAGE_CONNECTABLE This is a connectable resource; the name pointed to by the lpRemoteName
     * member can be passed to the WNetAddConnection function to make a network connection.
     * RESOURCEUSAGE_CONTAINER This is a container resource; the name pointed to by the lpRemoteName
     * member can be passed to the WNetOpenEnum function to enumerate the resources in the container.
     */
    DWORD    dwUsage;
    /**
     * Long pointer to the local name of a network resource if the dwScope member is RESOURCE_CONNECTED
     * or RESOURCE_REMEMBERED. This member is NULL if the connection does not have a local name.
     */
    LPWSTR   lpLocalName;
    /**
     * Long pointer to a remote network name if the entry is a network resource.
     *
     * If the entry is a current or persistent connection, lpRemoteName points to the network name
     * associated with the name pointed to by the lpLocalName member.
     */
    LPWSTR   lpRemoteName;
    /**
     * Long pointer to a provider-supplied comment.
     */
    LPWSTR   lpComment ;
    /**
     * Long pointer to the name of the provider owning this resource. This member can be NULL if the
     * provider name is unknown.
     */
    LPWSTR   lpProvider;
}NETRESOURCEW, *LPNETRESOURCEW;
#ifdef UNICODE
typedef NETRESOURCEW NETRESOURCE;
typedef LPNETRESOURCEW LPNETRESOURCE;
#else
typedef NETRESOURCEA NETRESOURCE;
typedef LPNETRESOURCEA LPNETRESOURCE;
#endif // UNICODE


//
//  Network Connections.
// 

#define NETPROPERTY_PERSISTENT       1

#define CONNECT_UPDATE_PROFILE      0x00000001
#define CONNECT_UPDATE_RECENT       0x00000002
#define CONNECT_TEMPORARY           0x00000004
#define CONNECT_INTERACTIVE         0x00000008
#define CONNECT_PROMPT              0x00000010
#define CONNECT_NEED_DRIVE          0x00000020
#if(WINVER >= 0x0400)
#define CONNECT_REFCOUNT            0x00000040
#define CONNECT_REDIRECT            0x00000080
#define CONNECT_LOCALDRIVE          0x00000100
#define CONNECT_CURRENT_MEDIA       0x00000200
#endif /* WINVER >= 0x0400 */

/**
 * This function makes a connection to a network resource and can specify a local name for the
 * resource.
 *
 * @param hwndOwner [in] Handle to a window that the provider of network resources can use as an
 *   owner window for dialog boxes. The hwndOwner parameter may be NULL.
 * @param lpNetResource [in] Long pointer to a NETRESOURCE data structure that specifies details of
 *   the proposed connection: information about the network resource, the local device, and the
 *   network resource provider. You must specify the following members of the NETRESOURCE structure:
 *   Value Description dwType Specifies the type of network resource to connect to. If lpLocalName
 *   points to a non-empty string, this member can be RESOURCETYPE_DISK or RESOURCETYPE_PRINT. If
 *   lpLocalName is NULL or points to an empty string, dwType can be RESOURCETYPE_DISK,
 *   RESOURCETYPE_PRINT, or RESOURCETYPE_ANY. LpLocalName Long pointer to a null-terminated string
 *   that specifies the name of a local device to be redirected, such as "MyDevice" or "LocalShare".
 *   The string is treated in a case-insensitive manner. If the string is empty or lpLocalName is
 *   NULL, the function makes a connection to the network resource without assigning a local name.
 *   LpRemoteName Long pointer to a null-terminated string that specifies the network resource to
 *   connect to. The string can be up to MAX_PATH characters in length. The string must follow the
 *   network provider's naming conventions. LpProvider Long pointer the network provider to connect
 *   to. Applications should set this to NULL because the Microsoft Windows Network is the only
 *   provider supported. The WNetAddConnection3 function ignores the other members of the NETRESOURCE
 *   structure.
 * @param lpPassword [in] Long pointer to a null-terminated string that specifies a password to be
 *   used in making the network connection. If lpPassword is NULL, the function uses the current
 *   default password associated with the user specified by lpUserName. If lpPassword points to an
 *   empty string, the function does not use a password.
 * @param lpUserName [in] Long pointer to a null-terminated string that specifies a user name to be
 *   used in making the connection. If lpUserName is NULL, the function uses the default user name.
 *   For dial-up networking connections, the default user name is the one used to establish the
 *   connection. For LAN connections, the default user name is configured in the network control
 *   panel. On systems that support a windows user interface, the user is prompted to enter logon
 *   credentials if no default credentials exist or if the logon attempt fails using the existing
 *   credentials. The lpUserName parameter is specified when users want to connect to a network
 *   resource for which they have been assigned a user name or account other than the default user
 *   name or account.
 * @param dwFlags [in] Specifies connection options. It is the following value: Value Description
 *   CONNECT_UPDATE_PROFILE The network resource connection should be remembered. If this bit flag is
 *   set, the registry will store the connection information and make it available when the system
 *   reboots. The operating system does not remember unsuccessful connections or unnamed connections.
 *   An unnamed connection occurs when lpLocalName is NULL or points to an empty string.
 *
 * @return ERROR_SUCCESS indicates success. An error value indicates failure. Returning an error
 *   value provides compatibility with the behavior of the Windows for Workgroups function
 *   WNetAddConnection. You can also call the GetLastError function to obtain the same error value.
 *   Possible GetLastError values are described in the following table. Value Description
 *   ERROR_ACCESS_DENIED Access to the network resource was denied. ERROR_ALREADY_ASSIGNED The local
 *   name specified by lpLocalName is already connected to a network resource. ERROR_BAD_DEVICE The
 *   value specified by lpLocalName is invalid. ERROR_BAD_NET_NAME The value specified by lpRemoteName
 *   is not acceptable to any network resource provider. The resource name is invalid, or the named
 *   resource cannot be located. ERROR_BUSY The router or provider is busy, possibly initializing. The
 *   caller should retry. ERROR_CANCELLED The attempt to make the connection was cancelled by the user
 *   through a dialog box from one of the network resource providers or by a called resource.
 *   ERROR_DEVICE_ALREADY_REMEMBERED An entry for the device specified in lpLocalName is already in
 *   the user profile. ERROR_INVALID_PASSWORD The specified password is invalid.
 *   ERROR_NO_NET_OR_BAD_PATH The network component has not started, or the specified name could not
 *   be handled. ERROR_NO_NETWORK There is no network present.
 *
 * Windows CE does not support the concept of drive-letters. An application can name a local
 * resource "F:", but that naming convention has no special significance. The lpLocalName field of
 * the NETRESOURCE structure can contain any string of up to 64 characters long. If the local name
 * is NULL or empty, the resource is connected without a local name. If it is "*", the default name
 * will be constructed as "<share> on <server>" extracted from the remote name of "\\server\share".
 *
 * Except for nameless connections, the connected resource will appear as a subfolder under the
 * \NETWORK directory. The subfolder is named after the lpLocalName string.
 *
 * Windows CE supports only the "Microsoft Windows Network" provider. Persistent connections are
 * stored in the registry and not automatically reconnected when the system is rebooted.
 */
DWORD APIENTRY
WNetAddConnection3A(
     HWND           hwndOwner,
     LPNETRESOURCEA lpNetResource,
     LPCSTR       lpPassword,
     LPCSTR       lpUserName,
     DWORD          dwFlags
    );
/**
 * This function makes a connection to a network resource and can specify a local name for the
 * resource.
 *
 * @param hwndOwner [in] Handle to a window that the provider of network resources can use as an
 *   owner window for dialog boxes. The hwndOwner parameter may be NULL.
 * @param lpNetResource [in] Long pointer to a NETRESOURCE data structure that specifies details of
 *   the proposed connection: information about the network resource, the local device, and the
 *   network resource provider. You must specify the following members of the NETRESOURCE structure:
 *   Value Description dwType Specifies the type of network resource to connect to. If lpLocalName
 *   points to a non-empty string, this member can be RESOURCETYPE_DISK or RESOURCETYPE_PRINT. If
 *   lpLocalName is NULL or points to an empty string, dwType can be RESOURCETYPE_DISK,
 *   RESOURCETYPE_PRINT, or RESOURCETYPE_ANY. LpLocalName Long pointer to a null-terminated string
 *   that specifies the name of a local device to be redirected, such as "MyDevice" or "LocalShare".
 *   The string is treated in a case-insensitive manner. If the string is empty or lpLocalName is
 *   NULL, the function makes a connection to the network resource without assigning a local name.
 *   LpRemoteName Long pointer to a null-terminated string that specifies the network resource to
 *   connect to. The string can be up to MAX_PATH characters in length. The string must follow the
 *   network provider's naming conventions. LpProvider Long pointer the network provider to connect
 *   to. Applications should set this to NULL because the Microsoft Windows Network is the only
 *   provider supported. The WNetAddConnection3 function ignores the other members of the NETRESOURCE
 *   structure.
 * @param lpPassword [in] Long pointer to a null-terminated string that specifies a password to be
 *   used in making the network connection. If lpPassword is NULL, the function uses the current
 *   default password associated with the user specified by lpUserName. If lpPassword points to an
 *   empty string, the function does not use a password.
 * @param lpUserName [in] Long pointer to a null-terminated string that specifies a user name to be
 *   used in making the connection. If lpUserName is NULL, the function uses the default user name.
 *   For dial-up networking connections, the default user name is the one used to establish the
 *   connection. For LAN connections, the default user name is configured in the network control
 *   panel. On systems that support a windows user interface, the user is prompted to enter logon
 *   credentials if no default credentials exist or if the logon attempt fails using the existing
 *   credentials. The lpUserName parameter is specified when users want to connect to a network
 *   resource for which they have been assigned a user name or account other than the default user
 *   name or account.
 * @param dwFlags [in] Specifies connection options. It is the following value: Value Description
 *   CONNECT_UPDATE_PROFILE The network resource connection should be remembered. If this bit flag is
 *   set, the registry will store the connection information and make it available when the system
 *   reboots. The operating system does not remember unsuccessful connections or unnamed connections.
 *   An unnamed connection occurs when lpLocalName is NULL or points to an empty string.
 *
 * @return ERROR_SUCCESS indicates success. An error value indicates failure. Returning an error
 *   value provides compatibility with the behavior of the Windows for Workgroups function
 *   WNetAddConnection. You can also call the GetLastError function to obtain the same error value.
 *   Possible GetLastError values are described in the following table. Value Description
 *   ERROR_ACCESS_DENIED Access to the network resource was denied. ERROR_ALREADY_ASSIGNED The local
 *   name specified by lpLocalName is already connected to a network resource. ERROR_BAD_DEVICE The
 *   value specified by lpLocalName is invalid. ERROR_BAD_NET_NAME The value specified by lpRemoteName
 *   is not acceptable to any network resource provider. The resource name is invalid, or the named
 *   resource cannot be located. ERROR_BUSY The router or provider is busy, possibly initializing. The
 *   caller should retry. ERROR_CANCELLED The attempt to make the connection was cancelled by the user
 *   through a dialog box from one of the network resource providers or by a called resource.
 *   ERROR_DEVICE_ALREADY_REMEMBERED An entry for the device specified in lpLocalName is already in
 *   the user profile. ERROR_INVALID_PASSWORD The specified password is invalid.
 *   ERROR_NO_NET_OR_BAD_PATH The network component has not started, or the specified name could not
 *   be handled. ERROR_NO_NETWORK There is no network present.
 *
 * Windows CE does not support the concept of drive-letters. An application can name a local
 * resource "F:", but that naming convention has no special significance. The lpLocalName field of
 * the NETRESOURCE structure can contain any string of up to 64 characters long. If the local name
 * is NULL or empty, the resource is connected without a local name. If it is "*", the default name
 * will be constructed as "<share> on <server>" extracted from the remote name of "\\server\share".
 *
 * Except for nameless connections, the connected resource will appear as a subfolder under the
 * \NETWORK directory. The subfolder is named after the lpLocalName string.
 *
 * Windows CE supports only the "Microsoft Windows Network" provider. Persistent connections are
 * stored in the registry and not automatically reconnected when the system is rebooted.
 */
DWORD APIENTRY
WNetAddConnection3W(
     HWND           hwndOwner,
     LPNETRESOURCEW lpNetResource,
     LPCWSTR       lpPassword,
     LPCWSTR       lpUserName,
     DWORD          dwFlags
    );
#ifdef UNICODE
/**
 * This function makes a connection to a network resource and can specify a local name for the
 * resource.
 *
 * @param hwndOwner [in] Handle to a window that the provider of network resources can use as an
 *   owner window for dialog boxes. The hwndOwner parameter may be NULL.
 * @param lpNetResource [in] Long pointer to a NETRESOURCE data structure that specifies details of
 *   the proposed connection: information about the network resource, the local device, and the
 *   network resource provider. You must specify the following members of the NETRESOURCE structure:
 *   Value Description dwType Specifies the type of network resource to connect to. If lpLocalName
 *   points to a non-empty string, this member can be RESOURCETYPE_DISK or RESOURCETYPE_PRINT. If
 *   lpLocalName is NULL or points to an empty string, dwType can be RESOURCETYPE_DISK,
 *   RESOURCETYPE_PRINT, or RESOURCETYPE_ANY. LpLocalName Long pointer to a null-terminated string
 *   that specifies the name of a local device to be redirected, such as "MyDevice" or "LocalShare".
 *   The string is treated in a case-insensitive manner. If the string is empty or lpLocalName is
 *   NULL, the function makes a connection to the network resource without assigning a local name.
 *   LpRemoteName Long pointer to a null-terminated string that specifies the network resource to
 *   connect to. The string can be up to MAX_PATH characters in length. The string must follow the
 *   network provider's naming conventions. LpProvider Long pointer the network provider to connect
 *   to. Applications should set this to NULL because the Microsoft Windows Network is the only
 *   provider supported. The WNetAddConnection3 function ignores the other members of the NETRESOURCE
 *   structure.
 * @param lpPassword [in] Long pointer to a null-terminated string that specifies a password to be
 *   used in making the network connection. If lpPassword is NULL, the function uses the current
 *   default password associated with the user specified by lpUserName. If lpPassword points to an
 *   empty string, the function does not use a password.
 * @param lpUserName [in] Long pointer to a null-terminated string that specifies a user name to be
 *   used in making the connection. If lpUserName is NULL, the function uses the default user name.
 *   For dial-up networking connections, the default user name is the one used to establish the
 *   connection. For LAN connections, the default user name is configured in the network control
 *   panel. On systems that support a windows user interface, the user is prompted to enter logon
 *   credentials if no default credentials exist or if the logon attempt fails using the existing
 *   credentials. The lpUserName parameter is specified when users want to connect to a network
 *   resource for which they have been assigned a user name or account other than the default user
 *   name or account.
 * @param dwFlags [in] Specifies connection options. It is the following value: Value Description
 *   CONNECT_UPDATE_PROFILE The network resource connection should be remembered. If this bit flag is
 *   set, the registry will store the connection information and make it available when the system
 *   reboots. The operating system does not remember unsuccessful connections or unnamed connections.
 *   An unnamed connection occurs when lpLocalName is NULL or points to an empty string.
 *
 * @return ERROR_SUCCESS indicates success. An error value indicates failure. Returning an error
 *   value provides compatibility with the behavior of the Windows for Workgroups function
 *   WNetAddConnection. You can also call the GetLastError function to obtain the same error value.
 *   Possible GetLastError values are described in the following table. Value Description
 *   ERROR_ACCESS_DENIED Access to the network resource was denied. ERROR_ALREADY_ASSIGNED The local
 *   name specified by lpLocalName is already connected to a network resource. ERROR_BAD_DEVICE The
 *   value specified by lpLocalName is invalid. ERROR_BAD_NET_NAME The value specified by lpRemoteName
 *   is not acceptable to any network resource provider. The resource name is invalid, or the named
 *   resource cannot be located. ERROR_BUSY The router or provider is busy, possibly initializing. The
 *   caller should retry. ERROR_CANCELLED The attempt to make the connection was cancelled by the user
 *   through a dialog box from one of the network resource providers or by a called resource.
 *   ERROR_DEVICE_ALREADY_REMEMBERED An entry for the device specified in lpLocalName is already in
 *   the user profile. ERROR_INVALID_PASSWORD The specified password is invalid.
 *   ERROR_NO_NET_OR_BAD_PATH The network component has not started, or the specified name could not
 *   be handled. ERROR_NO_NETWORK There is no network present.
 *
 * Windows CE does not support the concept of drive-letters. An application can name a local
 * resource "F:", but that naming convention has no special significance. The lpLocalName field of
 * the NETRESOURCE structure can contain any string of up to 64 characters long. If the local name
 * is NULL or empty, the resource is connected without a local name. If it is "*", the default name
 * will be constructed as "<share> on <server>" extracted from the remote name of "\\server\share".
 *
 * Except for nameless connections, the connected resource will appear as a subfolder under the
 * \NETWORK directory. The subfolder is named after the lpLocalName string.
 *
 * Windows CE supports only the "Microsoft Windows Network" provider. Persistent connections are
 * stored in the registry and not automatically reconnected when the system is rebooted.
 */
#define WNetAddConnection3  WNetAddConnection3W
#else
/**
 * This function makes a connection to a network resource and can specify a local name for the
 * resource.
 *
 * @param hwndOwner [in] Handle to a window that the provider of network resources can use as an
 *   owner window for dialog boxes. The hwndOwner parameter may be NULL.
 * @param lpNetResource [in] Long pointer to a NETRESOURCE data structure that specifies details of
 *   the proposed connection: information about the network resource, the local device, and the
 *   network resource provider. You must specify the following members of the NETRESOURCE structure:
 *   Value Description dwType Specifies the type of network resource to connect to. If lpLocalName
 *   points to a non-empty string, this member can be RESOURCETYPE_DISK or RESOURCETYPE_PRINT. If
 *   lpLocalName is NULL or points to an empty string, dwType can be RESOURCETYPE_DISK,
 *   RESOURCETYPE_PRINT, or RESOURCETYPE_ANY. LpLocalName Long pointer to a null-terminated string
 *   that specifies the name of a local device to be redirected, such as "MyDevice" or "LocalShare".
 *   The string is treated in a case-insensitive manner. If the string is empty or lpLocalName is
 *   NULL, the function makes a connection to the network resource without assigning a local name.
 *   LpRemoteName Long pointer to a null-terminated string that specifies the network resource to
 *   connect to. The string can be up to MAX_PATH characters in length. The string must follow the
 *   network provider's naming conventions. LpProvider Long pointer the network provider to connect
 *   to. Applications should set this to NULL because the Microsoft Windows Network is the only
 *   provider supported. The WNetAddConnection3 function ignores the other members of the NETRESOURCE
 *   structure.
 * @param lpPassword [in] Long pointer to a null-terminated string that specifies a password to be
 *   used in making the network connection. If lpPassword is NULL, the function uses the current
 *   default password associated with the user specified by lpUserName. If lpPassword points to an
 *   empty string, the function does not use a password.
 * @param lpUserName [in] Long pointer to a null-terminated string that specifies a user name to be
 *   used in making the connection. If lpUserName is NULL, the function uses the default user name.
 *   For dial-up networking connections, the default user name is the one used to establish the
 *   connection. For LAN connections, the default user name is configured in the network control
 *   panel. On systems that support a windows user interface, the user is prompted to enter logon
 *   credentials if no default credentials exist or if the logon attempt fails using the existing
 *   credentials. The lpUserName parameter is specified when users want to connect to a network
 *   resource for which they have been assigned a user name or account other than the default user
 *   name or account.
 * @param dwFlags [in] Specifies connection options. It is the following value: Value Description
 *   CONNECT_UPDATE_PROFILE The network resource connection should be remembered. If this bit flag is
 *   set, the registry will store the connection information and make it available when the system
 *   reboots. The operating system does not remember unsuccessful connections or unnamed connections.
 *   An unnamed connection occurs when lpLocalName is NULL or points to an empty string.
 *
 * @return ERROR_SUCCESS indicates success. An error value indicates failure. Returning an error
 *   value provides compatibility with the behavior of the Windows for Workgroups function
 *   WNetAddConnection. You can also call the GetLastError function to obtain the same error value.
 *   Possible GetLastError values are described in the following table. Value Description
 *   ERROR_ACCESS_DENIED Access to the network resource was denied. ERROR_ALREADY_ASSIGNED The local
 *   name specified by lpLocalName is already connected to a network resource. ERROR_BAD_DEVICE The
 *   value specified by lpLocalName is invalid. ERROR_BAD_NET_NAME The value specified by lpRemoteName
 *   is not acceptable to any network resource provider. The resource name is invalid, or the named
 *   resource cannot be located. ERROR_BUSY The router or provider is busy, possibly initializing. The
 *   caller should retry. ERROR_CANCELLED The attempt to make the connection was cancelled by the user
 *   through a dialog box from one of the network resource providers or by a called resource.
 *   ERROR_DEVICE_ALREADY_REMEMBERED An entry for the device specified in lpLocalName is already in
 *   the user profile. ERROR_INVALID_PASSWORD The specified password is invalid.
 *   ERROR_NO_NET_OR_BAD_PATH The network component has not started, or the specified name could not
 *   be handled. ERROR_NO_NETWORK There is no network present.
 *
 * Windows CE does not support the concept of drive-letters. An application can name a local
 * resource "F:", but that naming convention has no special significance. The lpLocalName field of
 * the NETRESOURCE structure can contain any string of up to 64 characters long. If the local name
 * is NULL or empty, the resource is connected without a local name. If it is "*", the default name
 * will be constructed as "<share> on <server>" extracted from the remote name of "\\server\share".
 *
 * Except for nameless connections, the connected resource will appear as a subfolder under the
 * \NETWORK directory. The subfolder is named after the lpLocalName string.
 *
 * Windows CE supports only the "Microsoft Windows Network" provider. Persistent connections are
 * stored in the registry and not automatically reconnected when the system is rebooted.
 */
#define WNetAddConnection3  WNetAddConnection3A
#endif // !UNICODE

/**
 * This function breaks an existing network connection.
 *
 * @param lpName [in] Long pointer to a null-terminated string that specifies the name of either the
 *   local name or the remote network resource to disconnect from. If this parameter specifies a local
 *   name, only the specified redirection is broken; otherwise, all connections to the remote network
 *   resource are broken.
 * @param dwFlags [in] Specifies a bitmask for the connection type. The following values are
 *   defined: Value Description 0 No stored information about the connection is updated.
 *   CONNECT_UPDATE_PROFILE The system is updated with the information that this is no longer a
 *   persistent connection. Disconnecting resources using remote names has no effect on persistent
 *   connections.
 * @param fForce [in] Boolean that specifies whether the disconnection should occur even if there
 *   are open files or jobs on the connection. If this parameter is FALSE, the function fails if there
 *   are open files or jobs.
 *
 * @return ERROR_SUCCESS indicates success. An error value indicates failure. To get extended error
 *   information, call GetLastError. Possible GetLastError values are described in the following
 *   table. Value Description ERROR_DEVICE_IN_USE The device is in use by an active process and cannot
 *   be disconnected. ERROR_NOT_CONNECTED The name specified by the lpName parameter is not a local or
 *   remote network resource, or the system is not currently connected to the device specified by the
 *   parameter. ERROR_OPEN_FILES There are open files, and the fForce parameter is FALSE.
 *
 * Connections are not automatically restored when the system is started.
 */
DWORD APIENTRY
WNetCancelConnection2A(
     LPCSTR lpName,
     DWORD    dwFlags,
     BOOL     fForce
    );
/**
 * This function breaks an existing network connection.
 *
 * @param lpName [in] Long pointer to a null-terminated string that specifies the name of either the
 *   local name or the remote network resource to disconnect from. If this parameter specifies a local
 *   name, only the specified redirection is broken; otherwise, all connections to the remote network
 *   resource are broken.
 * @param dwFlags [in] Specifies a bitmask for the connection type. The following values are
 *   defined: Value Description 0 No stored information about the connection is updated.
 *   CONNECT_UPDATE_PROFILE The system is updated with the information that this is no longer a
 *   persistent connection. Disconnecting resources using remote names has no effect on persistent
 *   connections.
 * @param fForce [in] Boolean that specifies whether the disconnection should occur even if there
 *   are open files or jobs on the connection. If this parameter is FALSE, the function fails if there
 *   are open files or jobs.
 *
 * @return ERROR_SUCCESS indicates success. An error value indicates failure. To get extended error
 *   information, call GetLastError. Possible GetLastError values are described in the following
 *   table. Value Description ERROR_DEVICE_IN_USE The device is in use by an active process and cannot
 *   be disconnected. ERROR_NOT_CONNECTED The name specified by the lpName parameter is not a local or
 *   remote network resource, or the system is not currently connected to the device specified by the
 *   parameter. ERROR_OPEN_FILES There are open files, and the fForce parameter is FALSE.
 *
 * Connections are not automatically restored when the system is started.
 */
DWORD APIENTRY
WNetCancelConnection2W(
     LPCWSTR lpName,
     DWORD    dwFlags,
     BOOL     fForce
    );
#ifdef UNICODE
/**
 * This function breaks an existing network connection.
 *
 * @param lpName [in] Long pointer to a null-terminated string that specifies the name of either the
 *   local name or the remote network resource to disconnect from. If this parameter specifies a local
 *   name, only the specified redirection is broken; otherwise, all connections to the remote network
 *   resource are broken.
 * @param dwFlags [in] Specifies a bitmask for the connection type. The following values are
 *   defined: Value Description 0 No stored information about the connection is updated.
 *   CONNECT_UPDATE_PROFILE The system is updated with the information that this is no longer a
 *   persistent connection. Disconnecting resources using remote names has no effect on persistent
 *   connections.
 * @param fForce [in] Boolean that specifies whether the disconnection should occur even if there
 *   are open files or jobs on the connection. If this parameter is FALSE, the function fails if there
 *   are open files or jobs.
 *
 * @return ERROR_SUCCESS indicates success. An error value indicates failure. To get extended error
 *   information, call GetLastError. Possible GetLastError values are described in the following
 *   table. Value Description ERROR_DEVICE_IN_USE The device is in use by an active process and cannot
 *   be disconnected. ERROR_NOT_CONNECTED The name specified by the lpName parameter is not a local or
 *   remote network resource, or the system is not currently connected to the device specified by the
 *   parameter. ERROR_OPEN_FILES There are open files, and the fForce parameter is FALSE.
 *
 * Connections are not automatically restored when the system is started.
 */
#define WNetCancelConnection2  WNetCancelConnection2W
#else
/**
 * This function breaks an existing network connection.
 *
 * @param lpName [in] Long pointer to a null-terminated string that specifies the name of either the
 *   local name or the remote network resource to disconnect from. If this parameter specifies a local
 *   name, only the specified redirection is broken; otherwise, all connections to the remote network
 *   resource are broken.
 * @param dwFlags [in] Specifies a bitmask for the connection type. The following values are
 *   defined: Value Description 0 No stored information about the connection is updated.
 *   CONNECT_UPDATE_PROFILE The system is updated with the information that this is no longer a
 *   persistent connection. Disconnecting resources using remote names has no effect on persistent
 *   connections.
 * @param fForce [in] Boolean that specifies whether the disconnection should occur even if there
 *   are open files or jobs on the connection. If this parameter is FALSE, the function fails if there
 *   are open files or jobs.
 *
 * @return ERROR_SUCCESS indicates success. An error value indicates failure. To get extended error
 *   information, call GetLastError. Possible GetLastError values are described in the following
 *   table. Value Description ERROR_DEVICE_IN_USE The device is in use by an active process and cannot
 *   be disconnected. ERROR_NOT_CONNECTED The name specified by the lpName parameter is not a local or
 *   remote network resource, or the system is not currently connected to the device specified by the
 *   parameter. ERROR_OPEN_FILES There are open files, and the fForce parameter is FALSE.
 *
 * Connections are not automatically restored when the system is started.
 */
#define WNetCancelConnection2  WNetCancelConnection2A
#endif // !UNICODE

/**
 * This function retrieves the remote name of the network resource associated with a local name.
 *
 * @param lpLocalName [in] Long pointer to a null-terminated string that specifies the local name of
 *   the network resource. Set up this resource with the WNetAddConnection3 function.
 * @param lpRemoteName [out] Long pointer to a buffer that receives the null-terminated remote name
 *   used to make the connection.
 * @param lpnLength [in/out] Long pointer to a variable that specifies the size, in characters, of
 *   the buffer pointed to by the lpRemoteName parameter. If the function fails because the buffer is
 *   not big enough, this parameter returns the required buffer size.
 *
 * @return ERROR_SUCCESS indicates success. An error value indicates failure. To get extended error
 *   information, call GetLastError. Possible GetLastError error values are described in the following
 *   table. Value Description ERROR_BAD_DEVICE The string pointed to by the lpLocalName parameter is
 *   invalid. ERROR_NOT_CONNECTED The network resource specified by lpLocalName is not currently
 *   connected and is not a persistent connection. ERROR_MORE_DATA The lpRemoteName buffer is too
 *   small. The lpnLength parameter points to a variable that contains the required buffer size. More
 *   entries are available with subsequent calls. ERROR_CONNECTION_UNAVAIL The network resource
 *   specified by lpLocalName is not currently connected and is a persistent connection.
 *   ERROR_NO_NETWORK No network is present. The WNetGetConnection function returns error values for
 *   compatibility with Windows for Workgroups. For compatibility with the Win32 API, the function
 *   also sets the error value returned by GetLastError.
 *
 * The WNetGetConnection function can be used to obtain information on network resources, such as
 * printers.
 */
DWORD APIENTRY
WNetGetConnectionA(
     LPCSTR lpLocalName,
     LPSTR  lpRemoteName,
     LPDWORD  lpnLength
    );
/**
 * This function retrieves the remote name of the network resource associated with a local name.
 *
 * @param lpLocalName [in] Long pointer to a null-terminated string that specifies the local name of
 *   the network resource. Set up this resource with the WNetAddConnection3 function.
 * @param lpRemoteName [out] Long pointer to a buffer that receives the null-terminated remote name
 *   used to make the connection.
 * @param lpnLength [in/out] Long pointer to a variable that specifies the size, in characters, of
 *   the buffer pointed to by the lpRemoteName parameter. If the function fails because the buffer is
 *   not big enough, this parameter returns the required buffer size.
 *
 * @return ERROR_SUCCESS indicates success. An error value indicates failure. To get extended error
 *   information, call GetLastError. Possible GetLastError error values are described in the following
 *   table. Value Description ERROR_BAD_DEVICE The string pointed to by the lpLocalName parameter is
 *   invalid. ERROR_NOT_CONNECTED The network resource specified by lpLocalName is not currently
 *   connected and is not a persistent connection. ERROR_MORE_DATA The lpRemoteName buffer is too
 *   small. The lpnLength parameter points to a variable that contains the required buffer size. More
 *   entries are available with subsequent calls. ERROR_CONNECTION_UNAVAIL The network resource
 *   specified by lpLocalName is not currently connected and is a persistent connection.
 *   ERROR_NO_NETWORK No network is present. The WNetGetConnection function returns error values for
 *   compatibility with Windows for Workgroups. For compatibility with the Win32 API, the function
 *   also sets the error value returned by GetLastError.
 *
 * The WNetGetConnection function can be used to obtain information on network resources, such as
 * printers.
 */
DWORD APIENTRY
WNetGetConnectionW(
     LPCWSTR lpLocalName,
     LPWSTR  lpRemoteName,
     LPDWORD  lpnLength
    );
#ifdef UNICODE
/**
 * This function retrieves the remote name of the network resource associated with a local name.
 *
 * @param lpLocalName [in] Long pointer to a null-terminated string that specifies the local name of
 *   the network resource. Set up this resource with the WNetAddConnection3 function.
 * @param lpRemoteName [out] Long pointer to a buffer that receives the null-terminated remote name
 *   used to make the connection.
 * @param lpnLength [in/out] Long pointer to a variable that specifies the size, in characters, of
 *   the buffer pointed to by the lpRemoteName parameter. If the function fails because the buffer is
 *   not big enough, this parameter returns the required buffer size.
 *
 * @return ERROR_SUCCESS indicates success. An error value indicates failure. To get extended error
 *   information, call GetLastError. Possible GetLastError error values are described in the following
 *   table. Value Description ERROR_BAD_DEVICE The string pointed to by the lpLocalName parameter is
 *   invalid. ERROR_NOT_CONNECTED The network resource specified by lpLocalName is not currently
 *   connected and is not a persistent connection. ERROR_MORE_DATA The lpRemoteName buffer is too
 *   small. The lpnLength parameter points to a variable that contains the required buffer size. More
 *   entries are available with subsequent calls. ERROR_CONNECTION_UNAVAIL The network resource
 *   specified by lpLocalName is not currently connected and is a persistent connection.
 *   ERROR_NO_NETWORK No network is present. The WNetGetConnection function returns error values for
 *   compatibility with Windows for Workgroups. For compatibility with the Win32 API, the function
 *   also sets the error value returned by GetLastError.
 *
 * The WNetGetConnection function can be used to obtain information on network resources, such as
 * printers.
 */
#define WNetGetConnection  WNetGetConnectionW
#else
/**
 * This function retrieves the remote name of the network resource associated with a local name.
 *
 * @param lpLocalName [in] Long pointer to a null-terminated string that specifies the local name of
 *   the network resource. Set up this resource with the WNetAddConnection3 function.
 * @param lpRemoteName [out] Long pointer to a buffer that receives the null-terminated remote name
 *   used to make the connection.
 * @param lpnLength [in/out] Long pointer to a variable that specifies the size, in characters, of
 *   the buffer pointed to by the lpRemoteName parameter. If the function fails because the buffer is
 *   not big enough, this parameter returns the required buffer size.
 *
 * @return ERROR_SUCCESS indicates success. An error value indicates failure. To get extended error
 *   information, call GetLastError. Possible GetLastError error values are described in the following
 *   table. Value Description ERROR_BAD_DEVICE The string pointed to by the lpLocalName parameter is
 *   invalid. ERROR_NOT_CONNECTED The network resource specified by lpLocalName is not currently
 *   connected and is not a persistent connection. ERROR_MORE_DATA The lpRemoteName buffer is too
 *   small. The lpnLength parameter points to a variable that contains the required buffer size. More
 *   entries are available with subsequent calls. ERROR_CONNECTION_UNAVAIL The network resource
 *   specified by lpLocalName is not currently connected and is a persistent connection.
 *   ERROR_NO_NETWORK No network is present. The WNetGetConnection function returns error values for
 *   compatibility with Windows for Workgroups. For compatibility with the Win32 API, the function
 *   also sets the error value returned by GetLastError.
 *
 * The WNetGetConnection function can be used to obtain information on network resources, such as
 * printers.
 */
#define WNetGetConnection  WNetGetConnectionA
#endif // !UNICODE


//
//  Network Connection Dialogs.
//


/**
 * This function starts a general browsing dialog box for disconnecting from network resources. It
 * lists all currently connected and remembered resources and lets the user select which one to
 * disconnect.
 *
 * @param hwnd [in] Handle to the owning window.
 * @param dwType [in] Ignored; set to zero.
 *
 * @return ERROR_SUCCESS indicates success. 0xFFFFFFFF indicates that the user canceled out of the
 *   dialog box. An error value indicates failure. To get extended error information, call
 *   GetLastError. Possible GetLastError error values are described in the following table. Value
 *   Meaning ERROR_NO_NETWORK No network is present. ERROR_NOT_ENOUGH_MEMORY There is insufficient
 *   memory to start the dialog box.
 *
 * If the user chooses OK in the dialog box, the requested network disconnection will have been made
 * when WNetDisconnectDialog returns.
 */
DWORD APIENTRY
WNetDisconnectDialog(
    HWND  hwnd,
    DWORD dwType
    );

#if(WINVER >= 0x0400)
/**
 * This structure is used in the WNetConnectionDialog1 function to specify the browsing dialog box
 * parameters.
 *
 * @return WN_SUCCESS indicates that the call is successful and displays the dialog. Typically, this
 *   function returns an error only if the dialog box could not be displayed because errors that occur
 *   after are reported directly to the user. If the call is successful, dwDevNum contains the number
 *   of devices connected to. If the user cancels the dialog box, the function returns 0xFFFFFFFF. The
 *   WN_BAD_VALUE means that CONNDLG_RO_PATH is set and lpRemoteName does not point to a remote name.
 */
typedef struct _CONNECTDLGSTRUCTA{
    /**
     * Size of this structure, in bytes.
     */
    DWORD cbStructure;       /* size of this structure in bytes */
    /**
     * Handle of the owning window.
     */
    HWND hwndOwner;          /* owner window for the dialog */
    /**
     * Long pointer to a null-terminated string that specifies the path of a network resource to connect
     * to. If the lpRemoteName member of the NETRESOURCE structure is specified, this member is entered
     * into the path field of the dialog box. All other members must be set to NULL except dwType which
     * specifies the type of resources of interest, and must be one of RESOURCETYPE_DISK.
     */
    LPNETRESOURCEA lpConnRes;/* Requested Resource info    */
    /**
     * Specifies variations in the dialog display. This member must be set to zero or the following
     * value: Value Description CONNDLG_RO_PATH Instead of enabling the user to type in a path, have a
     * read-only path already inserted. This flag should be set only if lpRemoteName is not NULL, an
     * empty string, and CONNDLG_USE_MRU is not set.
     */
    DWORD dwFlags;           /* flags (see below) */
    /**
     * If the call is successful, this member returns the number of the devices connected to. The value
     * is 1 for A:, 2 for B:, 3 for C:, and so on. If the user made a deviceless connection, the value
     * is 0xFFFFFFFF.
     */
    DWORD dwDevNum;          /* number of devices connected to */
} CONNECTDLGSTRUCTA, FAR *LPCONNECTDLGSTRUCTA;
/**
 * This structure is used in the WNetConnectionDialog1 function to specify the browsing dialog box
 * parameters.
 *
 * @return WN_SUCCESS indicates that the call is successful and displays the dialog. Typically, this
 *   function returns an error only if the dialog box could not be displayed because errors that occur
 *   after are reported directly to the user. If the call is successful, dwDevNum contains the number
 *   of devices connected to. If the user cancels the dialog box, the function returns 0xFFFFFFFF. The
 *   WN_BAD_VALUE means that CONNDLG_RO_PATH is set and lpRemoteName does not point to a remote name.
 */
typedef struct _CONNECTDLGSTRUCTW{
    /**
     * Size of this structure, in bytes.
     */
    DWORD cbStructure;       /* size of this structure in bytes */
    /**
     * Handle of the owning window.
     */
    HWND hwndOwner;          /* owner window for the dialog */
    /**
     * Long pointer to a null-terminated string that specifies the path of a network resource to connect
     * to. If the lpRemoteName member of the NETRESOURCE structure is specified, this member is entered
     * into the path field of the dialog box. All other members must be set to NULL except dwType which
     * specifies the type of resources of interest, and must be one of RESOURCETYPE_DISK.
     */
    LPNETRESOURCEW lpConnRes;/* Requested Resource info    */
    /**
     * Specifies variations in the dialog display. This member must be set to zero or the following
     * value: Value Description CONNDLG_RO_PATH Instead of enabling the user to type in a path, have a
     * read-only path already inserted. This flag should be set only if lpRemoteName is not NULL, an
     * empty string, and CONNDLG_USE_MRU is not set.
     */
    DWORD dwFlags;           /* flags (see below) */
    /**
     * If the call is successful, this member returns the number of the devices connected to. The value
     * is 1 for A:, 2 for B:, 3 for C:, and so on. If the user made a deviceless connection, the value
     * is 0xFFFFFFFF.
     */
    DWORD dwDevNum;          /* number of devices connected to */
} CONNECTDLGSTRUCTW, FAR *LPCONNECTDLGSTRUCTW;
#ifdef UNICODE
typedef CONNECTDLGSTRUCTW CONNECTDLGSTRUCT;
typedef LPCONNECTDLGSTRUCTW LPCONNECTDLGSTRUCT;
#else
typedef CONNECTDLGSTRUCTA CONNECTDLGSTRUCT;
typedef LPCONNECTDLGSTRUCTA LPCONNECTDLGSTRUCT;
#endif // UNICODE

#define CONNDLG_RO_PATH     0x00000001 /* Resource path should be read-only    */
#define CONNDLG_CONN_POINT  0x00000002 /* Netware -style movable connection point enabled */
#define CONNDLG_USE_MRU     0x00000004 /* Use MRU combobox  */
#define CONNDLG_HIDE_BOX    0x00000008 /* Hide persistent connect checkbox  */

/*
 * NOTE:  Set at most ONE of the below flags.  If neither flag is set,
 *        then the persistence is set to whatever the user chose during
 *        a previous connection
 */
#define CONNDLG_PERSIST     0x00000010 /* Force persistent connection */
#define CONNDLG_NOT_PERSIST 0x00000020 /* Force connection NOT persistent */

/**
 * This function brings up a general browsing dialog for connecting to network resources.
 *
 * @param lpConnectDlgStruct [in] Long pointer to the CONNECTDLGSTRUCT structure, which establishes
 *   the browsing dialog parameters.
 *
 * @return ERROR_SUCCESS indicates success. 0xFFFFFFFF indicates that the user canceled the dialog
 *   box. Typically, this dialog box only returns an error if the user cannot enter a dialog session.
 *   This is because errors that occur after a session are reported to the user directly. Of the
 *   possible error values, ERROR_INVALID_PARAMETER indicates one of the following: CONNDLG_RO_PATH is
 *   set and lpConnRes->lpRemoteName does not point to a remote name. Both CONNDLG_PERSIST and
 *   CONNDLG_NOT_PERSIST are set. Other possible values are described in the following table. Value
 *   Description ERROR_BAD_DEV_TYPE The lpConnRes->dwType members of CONNECTDLGSTRUCT are not set to
 *   indicate RESOURCETYPE_DISK. ERROR_BUSY The network provider is busy, and is possibly
 *   initializing. The caller should retry. ERROR_NO_NETWORK The network is not present.
 *   ERROR_NOT_ENOUGH_MEMORY There is insufficient memory to bring up the dialog box.
 *
 * The dwDevNum member of the CONNECTDLGSTRUCT structure pointed to by the lpConnectDlgStruc
 * parameter is ignored.
 *
 * The dwFlags member of the CONNECTDLGSTRUCT can be either CONNDLG_RO_PATH or 0.
 */
DWORD APIENTRY
WNetConnectionDialog1A(
    LPCONNECTDLGSTRUCTA lpConnDlgStruct
    );
/**
 * This function brings up a general browsing dialog for connecting to network resources.
 *
 * @param lpConnectDlgStruct [in] Long pointer to the CONNECTDLGSTRUCT structure, which establishes
 *   the browsing dialog parameters.
 *
 * @return ERROR_SUCCESS indicates success. 0xFFFFFFFF indicates that the user canceled the dialog
 *   box. Typically, this dialog box only returns an error if the user cannot enter a dialog session.
 *   This is because errors that occur after a session are reported to the user directly. Of the
 *   possible error values, ERROR_INVALID_PARAMETER indicates one of the following: CONNDLG_RO_PATH is
 *   set and lpConnRes->lpRemoteName does not point to a remote name. Both CONNDLG_PERSIST and
 *   CONNDLG_NOT_PERSIST are set. Other possible values are described in the following table. Value
 *   Description ERROR_BAD_DEV_TYPE The lpConnRes->dwType members of CONNECTDLGSTRUCT are not set to
 *   indicate RESOURCETYPE_DISK. ERROR_BUSY The network provider is busy, and is possibly
 *   initializing. The caller should retry. ERROR_NO_NETWORK The network is not present.
 *   ERROR_NOT_ENOUGH_MEMORY There is insufficient memory to bring up the dialog box.
 *
 * The dwDevNum member of the CONNECTDLGSTRUCT structure pointed to by the lpConnectDlgStruc
 * parameter is ignored.
 *
 * The dwFlags member of the CONNECTDLGSTRUCT can be either CONNDLG_RO_PATH or 0.
 */
DWORD APIENTRY
WNetConnectionDialog1W(
    LPCONNECTDLGSTRUCTW lpConnDlgStruct
    );
#ifdef UNICODE
/**
 * This function brings up a general browsing dialog for connecting to network resources.
 *
 * @param lpConnectDlgStruct [in] Long pointer to the CONNECTDLGSTRUCT structure, which establishes
 *   the browsing dialog parameters.
 *
 * @return ERROR_SUCCESS indicates success. 0xFFFFFFFF indicates that the user canceled the dialog
 *   box. Typically, this dialog box only returns an error if the user cannot enter a dialog session.
 *   This is because errors that occur after a session are reported to the user directly. Of the
 *   possible error values, ERROR_INVALID_PARAMETER indicates one of the following: CONNDLG_RO_PATH is
 *   set and lpConnRes->lpRemoteName does not point to a remote name. Both CONNDLG_PERSIST and
 *   CONNDLG_NOT_PERSIST are set. Other possible values are described in the following table. Value
 *   Description ERROR_BAD_DEV_TYPE The lpConnRes->dwType members of CONNECTDLGSTRUCT are not set to
 *   indicate RESOURCETYPE_DISK. ERROR_BUSY The network provider is busy, and is possibly
 *   initializing. The caller should retry. ERROR_NO_NETWORK The network is not present.
 *   ERROR_NOT_ENOUGH_MEMORY There is insufficient memory to bring up the dialog box.
 *
 * The dwDevNum member of the CONNECTDLGSTRUCT structure pointed to by the lpConnectDlgStruc
 * parameter is ignored.
 *
 * The dwFlags member of the CONNECTDLGSTRUCT can be either CONNDLG_RO_PATH or 0.
 */
#define WNetConnectionDialog1  WNetConnectionDialog1W
#else
/**
 * This function brings up a general browsing dialog for connecting to network resources.
 *
 * @param lpConnectDlgStruct [in] Long pointer to the CONNECTDLGSTRUCT structure, which establishes
 *   the browsing dialog parameters.
 *
 * @return ERROR_SUCCESS indicates success. 0xFFFFFFFF indicates that the user canceled the dialog
 *   box. Typically, this dialog box only returns an error if the user cannot enter a dialog session.
 *   This is because errors that occur after a session are reported to the user directly. Of the
 *   possible error values, ERROR_INVALID_PARAMETER indicates one of the following: CONNDLG_RO_PATH is
 *   set and lpConnRes->lpRemoteName does not point to a remote name. Both CONNDLG_PERSIST and
 *   CONNDLG_NOT_PERSIST are set. Other possible values are described in the following table. Value
 *   Description ERROR_BAD_DEV_TYPE The lpConnRes->dwType members of CONNECTDLGSTRUCT are not set to
 *   indicate RESOURCETYPE_DISK. ERROR_BUSY The network provider is busy, and is possibly
 *   initializing. The caller should retry. ERROR_NO_NETWORK The network is not present.
 *   ERROR_NOT_ENOUGH_MEMORY There is insufficient memory to bring up the dialog box.
 *
 * The dwDevNum member of the CONNECTDLGSTRUCT structure pointed to by the lpConnectDlgStruc
 * parameter is ignored.
 *
 * The dwFlags member of the CONNECTDLGSTRUCT can be either CONNDLG_RO_PATH or 0.
 */
#define WNetConnectionDialog1  WNetConnectionDialog1A
#endif // !UNICODE

/**
 * This structure is used in the WNetDisconnectDialog1 function to describe the required behavior
 * for the disconnect attempt.
 */
typedef struct _DISCDLGSTRUCTA{
    /**
     * Size, in bytes, of the DISCDLGSTRUCT structure. This structure is filled in by the caller to
     * indicate the size of the structure passed in.
     */
    DWORD           cbStructure;      /* size of this structure in bytes */
    /**
     * Handle to the owning window.
     */
    HWND            hwndOwner;        /* owner window for the dialog */
    /**
     * Long pointer to the local name that is redirected to the network resource, such as "myShare."
     */
    LPSTR           lpLocalName;      /* local device name */
    /**
     * Long pointer to the network resource to disconnect. This member can be set to NULL if lpLocalName
     * is specified. When this occurs, the connection to the resource redirected from lpLocalName is
     * disconnected.
     */
    LPSTR           lpRemoteName;     /* network resource name */
    /**
     * Must be set to the following flag: Value Description DISC_NO_FORCE If this value is not set, a
     * forced disconnect will occur-typically because the user has open files. The user will be informed
     * if there are open files to the connection and offered the option to disconnect.
     */
    DWORD           dwFlags;          /* flags */
} DISCDLGSTRUCTA, FAR *LPDISCDLGSTRUCTA;
/**
 * This structure is used in the WNetDisconnectDialog1 function to describe the required behavior
 * for the disconnect attempt.
 */
typedef struct _DISCDLGSTRUCTW{
    /**
     * Size, in bytes, of the DISCDLGSTRUCT structure. This structure is filled in by the caller to
     * indicate the size of the structure passed in.
     */
    DWORD           cbStructure;      /* size of this structure in bytes */
    /**
     * Handle to the owning window.
     */
    HWND            hwndOwner;        /* owner window for the dialog */
    /**
     * Long pointer to the local name that is redirected to the network resource, such as "myShare."
     */
    LPWSTR          lpLocalName;      /* local device name */
    /**
     * Long pointer to the network resource to disconnect. This member can be set to NULL if lpLocalName
     * is specified. When this occurs, the connection to the resource redirected from lpLocalName is
     * disconnected.
     */
    LPWSTR          lpRemoteName;     /* network resource name */
    /**
     * Must be set to the following flag: Value Description DISC_NO_FORCE If this value is not set, a
     * forced disconnect will occur-typically because the user has open files. The user will be informed
     * if there are open files to the connection and offered the option to disconnect.
     */
    DWORD           dwFlags;          /* flags */
} DISCDLGSTRUCTW, FAR *LPDISCDLGSTRUCTW;
#ifdef UNICODE
typedef DISCDLGSTRUCTW DISCDLGSTRUCT;
typedef LPDISCDLGSTRUCTW LPDISCDLGSTRUCT;
#else
typedef DISCDLGSTRUCTA DISCDLGSTRUCT;
typedef LPDISCDLGSTRUCTA LPDISCDLGSTRUCT;
#endif // UNICODE

#define DISC_UPDATE_PROFILE         0x00000001
#define DISC_NO_FORCE               0x00000040

/**
 * This function attempts to disconnect from a network. If the underlying network returns
 * ERROR_OPEN_FILES, the function prompts the user for confirmation. Users will be informed of any
 * errors.
 *
 * @param lpDiscDlgStruct [in] Long pointer to the DISCDLGSTRUCT data structure, which specifies the
 *   behavior for the disconnect attempt.
 *
 * @return ERROR_SUCCESS indicates success. An error value indicates failure. To get extended error
 *   information, call GetLastError. Possible GetLastError error values are described in the following
 *   table. Value Description ERROR_SUCCESS The connection is successfully disconnected.
 *   ERROR_CANCELLED After the user was prompted for a decision to disconnect, the user elected not to
 *   disconnect. ERROR_OPEN_FILES The function is unable to disconnect because the user is actively
 *   using the connection. ERROR_BUSY The network provider is busy, and is possibly initializing. The
 *   caller should retry. ERROR_NO_NETWORK The network is not present. ERROR_NOT_ENOUGH_MEMORY There
 *   is insufficient memory to start the dialog box.
 */
DWORD APIENTRY
WNetDisconnectDialog1A(
    LPDISCDLGSTRUCTA lpConnDlgStruct
    );
/**
 * This function attempts to disconnect from a network. If the underlying network returns
 * ERROR_OPEN_FILES, the function prompts the user for confirmation. Users will be informed of any
 * errors.
 *
 * @param lpDiscDlgStruct [in] Long pointer to the DISCDLGSTRUCT data structure, which specifies the
 *   behavior for the disconnect attempt.
 *
 * @return ERROR_SUCCESS indicates success. An error value indicates failure. To get extended error
 *   information, call GetLastError. Possible GetLastError error values are described in the following
 *   table. Value Description ERROR_SUCCESS The connection is successfully disconnected.
 *   ERROR_CANCELLED After the user was prompted for a decision to disconnect, the user elected not to
 *   disconnect. ERROR_OPEN_FILES The function is unable to disconnect because the user is actively
 *   using the connection. ERROR_BUSY The network provider is busy, and is possibly initializing. The
 *   caller should retry. ERROR_NO_NETWORK The network is not present. ERROR_NOT_ENOUGH_MEMORY There
 *   is insufficient memory to start the dialog box.
 */
DWORD APIENTRY
WNetDisconnectDialog1W(
    LPDISCDLGSTRUCTW lpConnDlgStruct
    );
#ifdef UNICODE
/**
 * This function attempts to disconnect from a network. If the underlying network returns
 * ERROR_OPEN_FILES, the function prompts the user for confirmation. Users will be informed of any
 * errors.
 *
 * @param lpDiscDlgStruct [in] Long pointer to the DISCDLGSTRUCT data structure, which specifies the
 *   behavior for the disconnect attempt.
 *
 * @return ERROR_SUCCESS indicates success. An error value indicates failure. To get extended error
 *   information, call GetLastError. Possible GetLastError error values are described in the following
 *   table. Value Description ERROR_SUCCESS The connection is successfully disconnected.
 *   ERROR_CANCELLED After the user was prompted for a decision to disconnect, the user elected not to
 *   disconnect. ERROR_OPEN_FILES The function is unable to disconnect because the user is actively
 *   using the connection. ERROR_BUSY The network provider is busy, and is possibly initializing. The
 *   caller should retry. ERROR_NO_NETWORK The network is not present. ERROR_NOT_ENOUGH_MEMORY There
 *   is insufficient memory to start the dialog box.
 */
#define WNetDisconnectDialog1  WNetDisconnectDialog1W
#else
/**
 * This function attempts to disconnect from a network. If the underlying network returns
 * ERROR_OPEN_FILES, the function prompts the user for confirmation. Users will be informed of any
 * errors.
 *
 * @param lpDiscDlgStruct [in] Long pointer to the DISCDLGSTRUCT data structure, which specifies the
 *   behavior for the disconnect attempt.
 *
 * @return ERROR_SUCCESS indicates success. An error value indicates failure. To get extended error
 *   information, call GetLastError. Possible GetLastError error values are described in the following
 *   table. Value Description ERROR_SUCCESS The connection is successfully disconnected.
 *   ERROR_CANCELLED After the user was prompted for a decision to disconnect, the user elected not to
 *   disconnect. ERROR_OPEN_FILES The function is unable to disconnect because the user is actively
 *   using the connection. ERROR_BUSY The network provider is busy, and is possibly initializing. The
 *   caller should retry. ERROR_NO_NETWORK The network is not present. ERROR_NOT_ENOUGH_MEMORY There
 *   is insufficient memory to start the dialog box.
 */
#define WNetDisconnectDialog1  WNetDisconnectDialog1A
#endif // !UNICODE
#endif /* WINVER >= 0x0400 */


//
//  Network Browsing.
//

/**
 * This function starts an enumeration of network resources or existing connections.
 *
 * @param dwScope [in] Specifies the scope of the enumeration. This parameter can be one of the
 *   following values: Value Description RESOURCE_CONNECTED All currently connected resources (the
 *   dwUsage parameter is ignored). RESOURCE_GLOBALNET All resources on the network.
 *   RESOURCE_REMEMBERED All remembered (persistent) connections (the dwUsage parameter is ignored).
 *   These connections may or may not currently be connected.
 * @param dwType [in] Specifies the resource types to enumerate. This parameter can be a combination
 *   of the following values: Value Description RESOURCETYPE_ANY All resources (this value cannot be
 *   combined with RESOURCETYPE_DISK or RESOURCETYPE_PRINT). RESOURCETYPE_DISK All disk resources.
 *   RESOURCETYPE_PRINT All print resources. If the Windows CE network client cannot distinguish
 *   between print and disk resources, it may enumerate all resources.
 * @param dwUsage [in] Specifies the resource usage to be enumerated. This parameter can be a
 *   combination of the following values: Value Description 0 All resources RESOURCEUSAGE_CONNECTABLE
 *   All connectable resources RESOURCEUSAGE_CONTAINER All container resources This parameter is
 *   ignored if the dwScope parameter is not RESOURCE_GLOBALNET.
 * @param lpNetResource [in] Long pointer to a NETRESOURCE structure specifying the container to
 *   enumerate. If an application needs to enumerate all the network resources, set the lpNetResource
 *   parameter to the topmost container, or the root, of the network. This structure can be filled in
 *   by the application or may have been returned by a call to the WNetEnumResource function. The
 *   NETRESOURCE structure must specify a container resource; that is, the RESOURCEUSAGE_CONTAINER
 *   value must be specified in the dwUsage member. To enumerate all network resources, an application
 *   can begin the enumeration by calling WNetOpenEnum with lpNetResource pointing to a NETRESOURCE
 *   structure specifying the root of the network, then using the returned handle with
 *   WNetEnumResource to enumerate resources. If one of the resources in the NETRESOURCE array
 *   returned by the WNetEnumResource function is a container resource, WNetOpenEnum can be used to
 *   open the resource for further enumeration. If the dwScope parameter is not RESOURCE_GLOBALNET,
 *   this parameter must be NULL.
 * @param lphEnum [out] Long pointer to a variable filled with an enumeration handle that can be
 *   used in a subsequent call to WNetEnumResource.
 *
 * @return ERROR_SUCCESS indicates success. An error value indicates failure. To get extended error
 *   information, call GetLastError. Possible GetLastError error values are described in the following
 *   table. Value Description ERROR_NOT_CONTAINER The lpNetResource parameter does not point to a
 *   container. ERROR_INVALID_PARAMETER Either the dwScope or dwType parameter is invalid, or there is
 *   a bad combination of parameters. ERROR_NO_NETWORK No network is present. The function returns
 *   error values for compatibility with Windows for Workgroups. For compatibility with the Win32 API,
 *   the function also sets the error value returned by GetLastError.
 *
 * The WNetOpenEnum function is used to begin enumeration of the resources in a single container.
 * The following code examples show the hierarchical structure of a Microsoft Windows Network:
 *
 *     LanMan (container, in this case the provider)
 *      ACCOUNTING (container, in this case the domain)
 *      \\ACCTSPAY (container, in this case the server)
 *      PAYFILES (disk)
 *      LASERJET (print)
 */
DWORD APIENTRY
WNetOpenEnumA(
     DWORD          dwScope,
     DWORD          dwType,
     DWORD          dwUsage,
     LPNETRESOURCEA lpNetResource,
     LPHANDLE       lphEnum
    );
/**
 * This function starts an enumeration of network resources or existing connections.
 *
 * @param dwScope [in] Specifies the scope of the enumeration. This parameter can be one of the
 *   following values: Value Description RESOURCE_CONNECTED All currently connected resources (the
 *   dwUsage parameter is ignored). RESOURCE_GLOBALNET All resources on the network.
 *   RESOURCE_REMEMBERED All remembered (persistent) connections (the dwUsage parameter is ignored).
 *   These connections may or may not currently be connected.
 * @param dwType [in] Specifies the resource types to enumerate. This parameter can be a combination
 *   of the following values: Value Description RESOURCETYPE_ANY All resources (this value cannot be
 *   combined with RESOURCETYPE_DISK or RESOURCETYPE_PRINT). RESOURCETYPE_DISK All disk resources.
 *   RESOURCETYPE_PRINT All print resources. If the Windows CE network client cannot distinguish
 *   between print and disk resources, it may enumerate all resources.
 * @param dwUsage [in] Specifies the resource usage to be enumerated. This parameter can be a
 *   combination of the following values: Value Description 0 All resources RESOURCEUSAGE_CONNECTABLE
 *   All connectable resources RESOURCEUSAGE_CONTAINER All container resources This parameter is
 *   ignored if the dwScope parameter is not RESOURCE_GLOBALNET.
 * @param lpNetResource [in] Long pointer to a NETRESOURCE structure specifying the container to
 *   enumerate. If an application needs to enumerate all the network resources, set the lpNetResource
 *   parameter to the topmost container, or the root, of the network. This structure can be filled in
 *   by the application or may have been returned by a call to the WNetEnumResource function. The
 *   NETRESOURCE structure must specify a container resource; that is, the RESOURCEUSAGE_CONTAINER
 *   value must be specified in the dwUsage member. To enumerate all network resources, an application
 *   can begin the enumeration by calling WNetOpenEnum with lpNetResource pointing to a NETRESOURCE
 *   structure specifying the root of the network, then using the returned handle with
 *   WNetEnumResource to enumerate resources. If one of the resources in the NETRESOURCE array
 *   returned by the WNetEnumResource function is a container resource, WNetOpenEnum can be used to
 *   open the resource for further enumeration. If the dwScope parameter is not RESOURCE_GLOBALNET,
 *   this parameter must be NULL.
 * @param lphEnum [out] Long pointer to a variable filled with an enumeration handle that can be
 *   used in a subsequent call to WNetEnumResource.
 *
 * @return ERROR_SUCCESS indicates success. An error value indicates failure. To get extended error
 *   information, call GetLastError. Possible GetLastError error values are described in the following
 *   table. Value Description ERROR_NOT_CONTAINER The lpNetResource parameter does not point to a
 *   container. ERROR_INVALID_PARAMETER Either the dwScope or dwType parameter is invalid, or there is
 *   a bad combination of parameters. ERROR_NO_NETWORK No network is present. The function returns
 *   error values for compatibility with Windows for Workgroups. For compatibility with the Win32 API,
 *   the function also sets the error value returned by GetLastError.
 *
 * The WNetOpenEnum function is used to begin enumeration of the resources in a single container.
 * The following code examples show the hierarchical structure of a Microsoft Windows Network:
 *
 *     LanMan (container, in this case the provider)
 *      ACCOUNTING (container, in this case the domain)
 *      \\ACCTSPAY (container, in this case the server)
 *      PAYFILES (disk)
 *      LASERJET (print)
 */
DWORD APIENTRY
WNetOpenEnumW(
     DWORD          dwScope,
     DWORD          dwType,
     DWORD          dwUsage,
     LPNETRESOURCEW lpNetResource,
     LPHANDLE       lphEnum
    );
#ifdef UNICODE
/**
 * This function starts an enumeration of network resources or existing connections.
 *
 * @param dwScope [in] Specifies the scope of the enumeration. This parameter can be one of the
 *   following values: Value Description RESOURCE_CONNECTED All currently connected resources (the
 *   dwUsage parameter is ignored). RESOURCE_GLOBALNET All resources on the network.
 *   RESOURCE_REMEMBERED All remembered (persistent) connections (the dwUsage parameter is ignored).
 *   These connections may or may not currently be connected.
 * @param dwType [in] Specifies the resource types to enumerate. This parameter can be a combination
 *   of the following values: Value Description RESOURCETYPE_ANY All resources (this value cannot be
 *   combined with RESOURCETYPE_DISK or RESOURCETYPE_PRINT). RESOURCETYPE_DISK All disk resources.
 *   RESOURCETYPE_PRINT All print resources. If the Windows CE network client cannot distinguish
 *   between print and disk resources, it may enumerate all resources.
 * @param dwUsage [in] Specifies the resource usage to be enumerated. This parameter can be a
 *   combination of the following values: Value Description 0 All resources RESOURCEUSAGE_CONNECTABLE
 *   All connectable resources RESOURCEUSAGE_CONTAINER All container resources This parameter is
 *   ignored if the dwScope parameter is not RESOURCE_GLOBALNET.
 * @param lpNetResource [in] Long pointer to a NETRESOURCE structure specifying the container to
 *   enumerate. If an application needs to enumerate all the network resources, set the lpNetResource
 *   parameter to the topmost container, or the root, of the network. This structure can be filled in
 *   by the application or may have been returned by a call to the WNetEnumResource function. The
 *   NETRESOURCE structure must specify a container resource; that is, the RESOURCEUSAGE_CONTAINER
 *   value must be specified in the dwUsage member. To enumerate all network resources, an application
 *   can begin the enumeration by calling WNetOpenEnum with lpNetResource pointing to a NETRESOURCE
 *   structure specifying the root of the network, then using the returned handle with
 *   WNetEnumResource to enumerate resources. If one of the resources in the NETRESOURCE array
 *   returned by the WNetEnumResource function is a container resource, WNetOpenEnum can be used to
 *   open the resource for further enumeration. If the dwScope parameter is not RESOURCE_GLOBALNET,
 *   this parameter must be NULL.
 * @param lphEnum [out] Long pointer to a variable filled with an enumeration handle that can be
 *   used in a subsequent call to WNetEnumResource.
 *
 * @return ERROR_SUCCESS indicates success. An error value indicates failure. To get extended error
 *   information, call GetLastError. Possible GetLastError error values are described in the following
 *   table. Value Description ERROR_NOT_CONTAINER The lpNetResource parameter does not point to a
 *   container. ERROR_INVALID_PARAMETER Either the dwScope or dwType parameter is invalid, or there is
 *   a bad combination of parameters. ERROR_NO_NETWORK No network is present. The function returns
 *   error values for compatibility with Windows for Workgroups. For compatibility with the Win32 API,
 *   the function also sets the error value returned by GetLastError.
 *
 * The WNetOpenEnum function is used to begin enumeration of the resources in a single container.
 * The following code examples show the hierarchical structure of a Microsoft Windows Network:
 *
 *     LanMan (container, in this case the provider)
 *      ACCOUNTING (container, in this case the domain)
 *      \\ACCTSPAY (container, in this case the server)
 *      PAYFILES (disk)
 *      LASERJET (print)
 */
#define WNetOpenEnum  WNetOpenEnumW
#else
/**
 * This function starts an enumeration of network resources or existing connections.
 *
 * @param dwScope [in] Specifies the scope of the enumeration. This parameter can be one of the
 *   following values: Value Description RESOURCE_CONNECTED All currently connected resources (the
 *   dwUsage parameter is ignored). RESOURCE_GLOBALNET All resources on the network.
 *   RESOURCE_REMEMBERED All remembered (persistent) connections (the dwUsage parameter is ignored).
 *   These connections may or may not currently be connected.
 * @param dwType [in] Specifies the resource types to enumerate. This parameter can be a combination
 *   of the following values: Value Description RESOURCETYPE_ANY All resources (this value cannot be
 *   combined with RESOURCETYPE_DISK or RESOURCETYPE_PRINT). RESOURCETYPE_DISK All disk resources.
 *   RESOURCETYPE_PRINT All print resources. If the Windows CE network client cannot distinguish
 *   between print and disk resources, it may enumerate all resources.
 * @param dwUsage [in] Specifies the resource usage to be enumerated. This parameter can be a
 *   combination of the following values: Value Description 0 All resources RESOURCEUSAGE_CONNECTABLE
 *   All connectable resources RESOURCEUSAGE_CONTAINER All container resources This parameter is
 *   ignored if the dwScope parameter is not RESOURCE_GLOBALNET.
 * @param lpNetResource [in] Long pointer to a NETRESOURCE structure specifying the container to
 *   enumerate. If an application needs to enumerate all the network resources, set the lpNetResource
 *   parameter to the topmost container, or the root, of the network. This structure can be filled in
 *   by the application or may have been returned by a call to the WNetEnumResource function. The
 *   NETRESOURCE structure must specify a container resource; that is, the RESOURCEUSAGE_CONTAINER
 *   value must be specified in the dwUsage member. To enumerate all network resources, an application
 *   can begin the enumeration by calling WNetOpenEnum with lpNetResource pointing to a NETRESOURCE
 *   structure specifying the root of the network, then using the returned handle with
 *   WNetEnumResource to enumerate resources. If one of the resources in the NETRESOURCE array
 *   returned by the WNetEnumResource function is a container resource, WNetOpenEnum can be used to
 *   open the resource for further enumeration. If the dwScope parameter is not RESOURCE_GLOBALNET,
 *   this parameter must be NULL.
 * @param lphEnum [out] Long pointer to a variable filled with an enumeration handle that can be
 *   used in a subsequent call to WNetEnumResource.
 *
 * @return ERROR_SUCCESS indicates success. An error value indicates failure. To get extended error
 *   information, call GetLastError. Possible GetLastError error values are described in the following
 *   table. Value Description ERROR_NOT_CONTAINER The lpNetResource parameter does not point to a
 *   container. ERROR_INVALID_PARAMETER Either the dwScope or dwType parameter is invalid, or there is
 *   a bad combination of parameters. ERROR_NO_NETWORK No network is present. The function returns
 *   error values for compatibility with Windows for Workgroups. For compatibility with the Win32 API,
 *   the function also sets the error value returned by GetLastError.
 *
 * The WNetOpenEnum function is used to begin enumeration of the resources in a single container.
 * The following code examples show the hierarchical structure of a Microsoft Windows Network:
 *
 *     LanMan (container, in this case the provider)
 *      ACCOUNTING (container, in this case the domain)
 *      \\ACCTSPAY (container, in this case the server)
 *      PAYFILES (disk)
 *      LASERJET (print)
 */
#define WNetOpenEnum  WNetOpenEnumA
#endif // !UNICODE

/**
 * This function continues a network-resource enumeration started by the WNetOpenEnum function.
 *
 * @param hEnum [in] Handle to an enumeration instance. This handle must be returned by
 *   WNetOpenEnum.
 * @param lpcCount [in/out] Long pointer to a variable specifying the number of entries requested.
 *   If the number requested is 0xFFFFFFFF, the function returns as many entries as possible. When the
 *   function finishes successfully, the variable pointed to by this parameter contains the number of
 *   entries actually read.
 * @param lpBuffer [in] Long pointer to the buffer that receives the enumeration results, which are
 *   returned as an array of NETRESOURCE structures. The buffer is valid until the next call using the
 *   handle given by the hEnum parameter. The order of NETRESOURCE structures in the array is not
 *   predictable.
 * @param lpBufferSize [in/out] Long pointer to a variable that specifies the size, in bytes, of the
 *   lpBuffer parameter. If the buffer is too small to receive even one entry, this parameter receives
 *   the required size of the buffer.
 *
 * @return ERROR_SUCCESS indicates that the enumeration succeeded, and the buffer contains the
 *   requested data. The calling application can continue to call WNetEnumResource to complete the
 *   enumeration. ERROR_NO_MORE_ITEMS indicates that there are no more entries. In this case, the
 *   buffer contents are undefined. An error value indicates failure. To get extended error
 *   information, call GetLastError. Possible GetLastError error values are described in the following
 *   table. Value Description ERROR_MORE_DATA More entries are available with subsequent calls.
 *   ERROR_INVALID_HANDLE The handle specified by the hEnum parameter is not valid. ERROR_NO_NETWORK
 *   No network is present. This condition is tested before hEnum is tested for validity. The function
 *   returns error values for compatibility with Windows for Workgroups. For compatibility with the
 *   Win32 API, the function also sets the error value returned by GetLastError.
 *
 * An application cannot set the lpBuffer parameter to NULL and retrieve the required buffer size
 * from the lpBufferSize parameter. Instead, the application should allocate a buffer of a
 * reasonable size-16 kilobytes (K) is typical-and use the value of lpBufferSize for error
 * detection.
 */
DWORD APIENTRY
WNetEnumResourceA(
     HANDLE  hEnum,
     LPDWORD lpcCount,
     LPVOID  lpBuffer,
     LPDWORD lpBufferSize
    );
/**
 * This function continues a network-resource enumeration started by the WNetOpenEnum function.
 *
 * @param hEnum [in] Handle to an enumeration instance. This handle must be returned by
 *   WNetOpenEnum.
 * @param lpcCount [in/out] Long pointer to a variable specifying the number of entries requested.
 *   If the number requested is 0xFFFFFFFF, the function returns as many entries as possible. When the
 *   function finishes successfully, the variable pointed to by this parameter contains the number of
 *   entries actually read.
 * @param lpBuffer [in] Long pointer to the buffer that receives the enumeration results, which are
 *   returned as an array of NETRESOURCE structures. The buffer is valid until the next call using the
 *   handle given by the hEnum parameter. The order of NETRESOURCE structures in the array is not
 *   predictable.
 * @param lpBufferSize [in/out] Long pointer to a variable that specifies the size, in bytes, of the
 *   lpBuffer parameter. If the buffer is too small to receive even one entry, this parameter receives
 *   the required size of the buffer.
 *
 * @return ERROR_SUCCESS indicates that the enumeration succeeded, and the buffer contains the
 *   requested data. The calling application can continue to call WNetEnumResource to complete the
 *   enumeration. ERROR_NO_MORE_ITEMS indicates that there are no more entries. In this case, the
 *   buffer contents are undefined. An error value indicates failure. To get extended error
 *   information, call GetLastError. Possible GetLastError error values are described in the following
 *   table. Value Description ERROR_MORE_DATA More entries are available with subsequent calls.
 *   ERROR_INVALID_HANDLE The handle specified by the hEnum parameter is not valid. ERROR_NO_NETWORK
 *   No network is present. This condition is tested before hEnum is tested for validity. The function
 *   returns error values for compatibility with Windows for Workgroups. For compatibility with the
 *   Win32 API, the function also sets the error value returned by GetLastError.
 *
 * An application cannot set the lpBuffer parameter to NULL and retrieve the required buffer size
 * from the lpBufferSize parameter. Instead, the application should allocate a buffer of a
 * reasonable size-16 kilobytes (K) is typical-and use the value of lpBufferSize for error
 * detection.
 */
DWORD APIENTRY
WNetEnumResourceW(
     HANDLE  hEnum,
     LPDWORD lpcCount,
     LPVOID  lpBuffer,
     LPDWORD lpBufferSize
    );
#ifdef UNICODE
/**
 * This function continues a network-resource enumeration started by the WNetOpenEnum function.
 *
 * @param hEnum [in] Handle to an enumeration instance. This handle must be returned by
 *   WNetOpenEnum.
 * @param lpcCount [in/out] Long pointer to a variable specifying the number of entries requested.
 *   If the number requested is 0xFFFFFFFF, the function returns as many entries as possible. When the
 *   function finishes successfully, the variable pointed to by this parameter contains the number of
 *   entries actually read.
 * @param lpBuffer [in] Long pointer to the buffer that receives the enumeration results, which are
 *   returned as an array of NETRESOURCE structures. The buffer is valid until the next call using the
 *   handle given by the hEnum parameter. The order of NETRESOURCE structures in the array is not
 *   predictable.
 * @param lpBufferSize [in/out] Long pointer to a variable that specifies the size, in bytes, of the
 *   lpBuffer parameter. If the buffer is too small to receive even one entry, this parameter receives
 *   the required size of the buffer.
 *
 * @return ERROR_SUCCESS indicates that the enumeration succeeded, and the buffer contains the
 *   requested data. The calling application can continue to call WNetEnumResource to complete the
 *   enumeration. ERROR_NO_MORE_ITEMS indicates that there are no more entries. In this case, the
 *   buffer contents are undefined. An error value indicates failure. To get extended error
 *   information, call GetLastError. Possible GetLastError error values are described in the following
 *   table. Value Description ERROR_MORE_DATA More entries are available with subsequent calls.
 *   ERROR_INVALID_HANDLE The handle specified by the hEnum parameter is not valid. ERROR_NO_NETWORK
 *   No network is present. This condition is tested before hEnum is tested for validity. The function
 *   returns error values for compatibility with Windows for Workgroups. For compatibility with the
 *   Win32 API, the function also sets the error value returned by GetLastError.
 *
 * An application cannot set the lpBuffer parameter to NULL and retrieve the required buffer size
 * from the lpBufferSize parameter. Instead, the application should allocate a buffer of a
 * reasonable size-16 kilobytes (K) is typical-and use the value of lpBufferSize for error
 * detection.
 */
#define WNetEnumResource  WNetEnumResourceW
#else
/**
 * This function continues a network-resource enumeration started by the WNetOpenEnum function.
 *
 * @param hEnum [in] Handle to an enumeration instance. This handle must be returned by
 *   WNetOpenEnum.
 * @param lpcCount [in/out] Long pointer to a variable specifying the number of entries requested.
 *   If the number requested is 0xFFFFFFFF, the function returns as many entries as possible. When the
 *   function finishes successfully, the variable pointed to by this parameter contains the number of
 *   entries actually read.
 * @param lpBuffer [in] Long pointer to the buffer that receives the enumeration results, which are
 *   returned as an array of NETRESOURCE structures. The buffer is valid until the next call using the
 *   handle given by the hEnum parameter. The order of NETRESOURCE structures in the array is not
 *   predictable.
 * @param lpBufferSize [in/out] Long pointer to a variable that specifies the size, in bytes, of the
 *   lpBuffer parameter. If the buffer is too small to receive even one entry, this parameter receives
 *   the required size of the buffer.
 *
 * @return ERROR_SUCCESS indicates that the enumeration succeeded, and the buffer contains the
 *   requested data. The calling application can continue to call WNetEnumResource to complete the
 *   enumeration. ERROR_NO_MORE_ITEMS indicates that there are no more entries. In this case, the
 *   buffer contents are undefined. An error value indicates failure. To get extended error
 *   information, call GetLastError. Possible GetLastError error values are described in the following
 *   table. Value Description ERROR_MORE_DATA More entries are available with subsequent calls.
 *   ERROR_INVALID_HANDLE The handle specified by the hEnum parameter is not valid. ERROR_NO_NETWORK
 *   No network is present. This condition is tested before hEnum is tested for validity. The function
 *   returns error values for compatibility with Windows for Workgroups. For compatibility with the
 *   Win32 API, the function also sets the error value returned by GetLastError.
 *
 * An application cannot set the lpBuffer parameter to NULL and retrieve the required buffer size
 * from the lpBufferSize parameter. Instead, the application should allocate a buffer of a
 * reasonable size-16 kilobytes (K) is typical-and use the value of lpBufferSize for error
 * detection.
 */
#define WNetEnumResource  WNetEnumResourceA
#endif // !UNICODE

/**
 * This function ends a network resource enumeration started by the WNetOpenEnum function.
 *
 * @param hEnum [in] Handle to an enumeration instance. This handle must be returned by the
 *   WNetOpenEnum function.
 *
 * @return ERROR_SUCCESS indicates success. An error value indicates failure. To get extended error
 *   information, call GetLastError. Possible GetLastError values are described in the following
 *   table. Value Description ERROR_NO_NETWORK A network is not present. ERROR_INVALID_HANDLE The
 *   handle specified in hEnum is not valid. The function returns error values for compatibility with
 *   Windows for Workgroups. For compatibility with Win32, the function also sets the error value
 *   returned by GetLastError.
 */
DWORD APIENTRY
WNetCloseEnum(
    HANDLE   hEnum
    );


//
//  Universal Naming.
//

#define UNIVERSAL_NAME_INFO_LEVEL   0x00000001
#define REMOTE_NAME_INFO_LEVEL      0x00000002

/**
 * This structure contains a pointer to a Universal Naming Convention (UNC) name string.
 *
 * A universal form of a path identifies a network resource in an unambiguous, computer-independent
 * manner. The path can then be passed to processes on other computers, enabling those processes to
 * obtain access to the network resource.
 *
 * Universal Naming Convention (UNC) names look like this:
 *
 * \\servername\sharename\path\file
 */
typedef struct  _UNIVERSAL_NAME_INFOA {
    /**
     * Long pointer to a zero-terminated UNC name string.
     */
    LPSTR    lpUniversalName;
}UNIVERSAL_NAME_INFOA, *LPUNIVERSAL_NAME_INFOA;
/**
 * This structure contains a pointer to a Universal Naming Convention (UNC) name string.
 *
 * A universal form of a path identifies a network resource in an unambiguous, computer-independent
 * manner. The path can then be passed to processes on other computers, enabling those processes to
 * obtain access to the network resource.
 *
 * Universal Naming Convention (UNC) names look like this:
 *
 * \\servername\sharename\path\file
 */
typedef struct  _UNIVERSAL_NAME_INFOW {
    /**
     * Long pointer to a zero-terminated UNC name string.
     */
    LPWSTR   lpUniversalName;
}UNIVERSAL_NAME_INFOW, *LPUNIVERSAL_NAME_INFOW;
#ifdef UNICODE
typedef UNIVERSAL_NAME_INFOW UNIVERSAL_NAME_INFO;
typedef LPUNIVERSAL_NAME_INFOW LPUNIVERSAL_NAME_INFO;
#else
typedef UNIVERSAL_NAME_INFOA UNIVERSAL_NAME_INFO;
typedef LPUNIVERSAL_NAME_INFOA LPUNIVERSAL_NAME_INFO;
#endif // UNICODE

/**
 * This structure contains path and name data about a network resource. The structure contains a
 * member that points to a Universal Naming Convention (UNC) name string for the resource, and two
 * members that point to additional network connection data strings.
 *
 * The REMOTE_NAME_INFO data structure contains a pointer to a Universal Naming Convention (UNC)
 * name string. UNC names look like this:
 *
 *     \\servername\sharename\path\file
 *
 * You can pass the REMOTE_NAME_INFO structure's lpConnectionName member to the WNetAddConnection2
 * function as the lpRemoteName member of the NETRESOURCE structure pointed to by lpNetResource.
 * This lets you create a local connection to a network resource. You can then append the string
 * pointed to by the lpRemainingPath member to the local device string "\network\localname", and
 * pass the resulting string to Win32 functions that use a file-based path.
 *
 * For example in the case of the UNC path \\servername\sharename\path\file, the lpConnectionName
 * member woud be set to \\servername\sharename\ and the lpRemainingPath member would be set to
 * path\file.
 */
typedef struct  _REMOTE_NAME_INFOA {
    /**
     * Long pointer to a zero-terminated UNC name string.
     */
    LPSTR    lpUniversalName;
    /**
     * Long pointer to a zero-terminated string that is the name of a network connection.
     */
    LPSTR    lpConnectionName;
    /**
     * Long pointer to a zero-terminated UNC name string.
     */
    LPSTR    lpRemainingPath;
}REMOTE_NAME_INFOA, *LPREMOTE_NAME_INFOA;
/**
 * This structure contains path and name data about a network resource. The structure contains a
 * member that points to a Universal Naming Convention (UNC) name string for the resource, and two
 * members that point to additional network connection data strings.
 *
 * The REMOTE_NAME_INFO data structure contains a pointer to a Universal Naming Convention (UNC)
 * name string. UNC names look like this:
 *
 *     \\servername\sharename\path\file
 *
 * You can pass the REMOTE_NAME_INFO structure's lpConnectionName member to the WNetAddConnection2
 * function as the lpRemoteName member of the NETRESOURCE structure pointed to by lpNetResource.
 * This lets you create a local connection to a network resource. You can then append the string
 * pointed to by the lpRemainingPath member to the local device string "\network\localname", and
 * pass the resulting string to Win32 functions that use a file-based path.
 *
 * For example in the case of the UNC path \\servername\sharename\path\file, the lpConnectionName
 * member woud be set to \\servername\sharename\ and the lpRemainingPath member would be set to
 * path\file.
 */
typedef struct  _REMOTE_NAME_INFOW {
    /**
     * Long pointer to a zero-terminated UNC name string.
     */
    LPWSTR   lpUniversalName;
    /**
     * Long pointer to a zero-terminated string that is the name of a network connection.
     */
    LPWSTR   lpConnectionName;
    /**
     * Long pointer to a zero-terminated UNC name string.
     */
    LPWSTR   lpRemainingPath;
}REMOTE_NAME_INFOW, *LPREMOTE_NAME_INFOW;
#ifdef UNICODE
typedef REMOTE_NAME_INFOW REMOTE_NAME_INFO;
typedef LPREMOTE_NAME_INFOW LPREMOTE_NAME_INFO;
#else
typedef REMOTE_NAME_INFOA REMOTE_NAME_INFO;
typedef LPREMOTE_NAME_INFOA LPREMOTE_NAME_INFO;
#endif // UNICODE

/**
 * This function maps a local path for a network resource to a data structure containing the
 * Universal Name Convention based name.
 *
 * @param lpLocalPath [in] Long pointer to a null-terminated string that is a local name for a
 *   network resource. It must point to the subfolder in the \NETWORK directory. For example, if local
 *   name "myShare" has been mapped to a network share, and the network resource of interest is a file
 *   named SAMPLE.DOC in the directory \WIN32\EXAMPLES on that share, the local path is
 *   myShare:\WIN32\EXAMPLES\SAMPLE.DOC.
 * @param dwInfoLevel [in] Specifies the type of data structure that the function will store in the
 *   buffer pointed to by lpBuffer. This parameter can be one of the following values: Value
 *   Description UNIVERSAL_NAME_INFO_LEVEL The function will store a UNIVERSAL_NAME_INFO data
 *   structure in the buffer. REMOTE_NAME_INFO_LEVEL The function will store a REMOTE_NAME_INFO data
 *   structure in the buffer. The UNIVERSAL_NAME_INFO data structure points to a Universal Naming
 *   Convention (UNC) name string. The REMOTE_NAME_INFO data structure points to a UNC name string and
 *   two additional connection information strings.
 * @param lpBuffer [out] Long pointer to a buffer that receives the type of data structure specified
 *   by the dwInfoLevel parameter.
 * @param lpBufferSize [in/out] Long pointer to a variable that specifies the size in bytes of the
 *   buffer pointed to by lpBuffer. If the function succeeds, it sets the variable pointed to by
 *   lpBufferSize to the size in bytes of the data structure stored in the buffer. If the function
 *   fails because the buffer is too small, indicated by the ERROR_MORE_DATA error value, it sets the
 *   variable pointed to by lpBufferSize to the required buffer size.
 *
 * @return ERROR_SUCCESS indicates success. An error value indicates failure. To get extended error
 *   information, call GetLastError. Possible GetLastError error values are described in the following
 *   table. Value Description ERROR_BAD_DEVICE The string pointed to by lpLocalPath is invalid.
 *   ERROR_CONNECTION_UNAVAIL There is no current connection to the remote device, but there is a
 *   remembered, or persistent, connection to it. ERROR_MORE_DATA The buffer pointed to by lpBuffer is
 *   too small. The function sets the variable pointed to by lpBufferSize to the required buffer size.
 *   More entries are available with subsequent calls. ERROR_NO_NETWORK No network present.
 *   ERROR_NOT_CONNECTED The device specified by lpLocalPath is not redirected.
 *
 * A universal form of a local path identifies a network resource in an unambiguous,
 * computer-independent manner. The name can then be passed to processes on other computers,
 * allowing those processes to obtain access to the resource.
 *
 * The WNetGetUniversalName function currently supports one universal name form: universal naming
 * convention (UNC) names, which look like the following:
 *
 *     \\servername\sharename\path\file
 *
 * Using the example from the preceding description of the lpLocalPath parameter, if the shared
 * network drive is on a server named COOLSERVER, and the share name is HOTSHARE, the UNC name for
 * the network resource whose local name is myShare:\WIN32\EXAMPLES\SAMPLE.DOC would be
 *
 *     \\coolserver\hotshare\win32\examples\sample.doc
 *
 * The UNIVERSAL_NAME_INFO data structure contains a pointer to a UNC name string. The
 * REMOTE_NAME_INFO data structure contains a pointer to a UNC name string. It also includes
 * pointers to two other useful strings. A program can pass the REMOTE_NAME_INFO structure's
 * lpszConnectionInfo member into the WNetAddConnection3 function to connect a local device to the
 * network resource, and then append the string pointed to by the lpszRemainingPath member to the
 * local device string. The resulting string can be passed to Win32 file functions.
 */
DWORD APIENTRY
WNetGetUniversalNameA(
     LPCSTR lpLocalPath,
     DWORD    dwInfoLevel,
     LPVOID   lpBuffer,
     LPDWORD  lpBufferSize
     );
/**
 * This function maps a local path for a network resource to a data structure containing the
 * Universal Name Convention based name.
 *
 * @param lpLocalPath [in] Long pointer to a null-terminated string that is a local name for a
 *   network resource. It must point to the subfolder in the \NETWORK directory. For example, if local
 *   name "myShare" has been mapped to a network share, and the network resource of interest is a file
 *   named SAMPLE.DOC in the directory \WIN32\EXAMPLES on that share, the local path is
 *   myShare:\WIN32\EXAMPLES\SAMPLE.DOC.
 * @param dwInfoLevel [in] Specifies the type of data structure that the function will store in the
 *   buffer pointed to by lpBuffer. This parameter can be one of the following values: Value
 *   Description UNIVERSAL_NAME_INFO_LEVEL The function will store a UNIVERSAL_NAME_INFO data
 *   structure in the buffer. REMOTE_NAME_INFO_LEVEL The function will store a REMOTE_NAME_INFO data
 *   structure in the buffer. The UNIVERSAL_NAME_INFO data structure points to a Universal Naming
 *   Convention (UNC) name string. The REMOTE_NAME_INFO data structure points to a UNC name string and
 *   two additional connection information strings.
 * @param lpBuffer [out] Long pointer to a buffer that receives the type of data structure specified
 *   by the dwInfoLevel parameter.
 * @param lpBufferSize [in/out] Long pointer to a variable that specifies the size in bytes of the
 *   buffer pointed to by lpBuffer. If the function succeeds, it sets the variable pointed to by
 *   lpBufferSize to the size in bytes of the data structure stored in the buffer. If the function
 *   fails because the buffer is too small, indicated by the ERROR_MORE_DATA error value, it sets the
 *   variable pointed to by lpBufferSize to the required buffer size.
 *
 * @return ERROR_SUCCESS indicates success. An error value indicates failure. To get extended error
 *   information, call GetLastError. Possible GetLastError error values are described in the following
 *   table. Value Description ERROR_BAD_DEVICE The string pointed to by lpLocalPath is invalid.
 *   ERROR_CONNECTION_UNAVAIL There is no current connection to the remote device, but there is a
 *   remembered, or persistent, connection to it. ERROR_MORE_DATA The buffer pointed to by lpBuffer is
 *   too small. The function sets the variable pointed to by lpBufferSize to the required buffer size.
 *   More entries are available with subsequent calls. ERROR_NO_NETWORK No network present.
 *   ERROR_NOT_CONNECTED The device specified by lpLocalPath is not redirected.
 *
 * A universal form of a local path identifies a network resource in an unambiguous,
 * computer-independent manner. The name can then be passed to processes on other computers,
 * allowing those processes to obtain access to the resource.
 *
 * The WNetGetUniversalName function currently supports one universal name form: universal naming
 * convention (UNC) names, which look like the following:
 *
 *     \\servername\sharename\path\file
 *
 * Using the example from the preceding description of the lpLocalPath parameter, if the shared
 * network drive is on a server named COOLSERVER, and the share name is HOTSHARE, the UNC name for
 * the network resource whose local name is myShare:\WIN32\EXAMPLES\SAMPLE.DOC would be
 *
 *     \\coolserver\hotshare\win32\examples\sample.doc
 *
 * The UNIVERSAL_NAME_INFO data structure contains a pointer to a UNC name string. The
 * REMOTE_NAME_INFO data structure contains a pointer to a UNC name string. It also includes
 * pointers to two other useful strings. A program can pass the REMOTE_NAME_INFO structure's
 * lpszConnectionInfo member into the WNetAddConnection3 function to connect a local device to the
 * network resource, and then append the string pointed to by the lpszRemainingPath member to the
 * local device string. The resulting string can be passed to Win32 file functions.
 */
DWORD APIENTRY
WNetGetUniversalNameW(
     LPCWSTR lpLocalPath,
     DWORD    dwInfoLevel,
     LPVOID   lpBuffer,
     LPDWORD  lpBufferSize
     );
#ifdef UNICODE
/**
 * This function maps a local path for a network resource to a data structure containing the
 * Universal Name Convention based name.
 *
 * @param lpLocalPath [in] Long pointer to a null-terminated string that is a local name for a
 *   network resource. It must point to the subfolder in the \NETWORK directory. For example, if local
 *   name "myShare" has been mapped to a network share, and the network resource of interest is a file
 *   named SAMPLE.DOC in the directory \WIN32\EXAMPLES on that share, the local path is
 *   myShare:\WIN32\EXAMPLES\SAMPLE.DOC.
 * @param dwInfoLevel [in] Specifies the type of data structure that the function will store in the
 *   buffer pointed to by lpBuffer. This parameter can be one of the following values: Value
 *   Description UNIVERSAL_NAME_INFO_LEVEL The function will store a UNIVERSAL_NAME_INFO data
 *   structure in the buffer. REMOTE_NAME_INFO_LEVEL The function will store a REMOTE_NAME_INFO data
 *   structure in the buffer. The UNIVERSAL_NAME_INFO data structure points to a Universal Naming
 *   Convention (UNC) name string. The REMOTE_NAME_INFO data structure points to a UNC name string and
 *   two additional connection information strings.
 * @param lpBuffer [out] Long pointer to a buffer that receives the type of data structure specified
 *   by the dwInfoLevel parameter.
 * @param lpBufferSize [in/out] Long pointer to a variable that specifies the size in bytes of the
 *   buffer pointed to by lpBuffer. If the function succeeds, it sets the variable pointed to by
 *   lpBufferSize to the size in bytes of the data structure stored in the buffer. If the function
 *   fails because the buffer is too small, indicated by the ERROR_MORE_DATA error value, it sets the
 *   variable pointed to by lpBufferSize to the required buffer size.
 *
 * @return ERROR_SUCCESS indicates success. An error value indicates failure. To get extended error
 *   information, call GetLastError. Possible GetLastError error values are described in the following
 *   table. Value Description ERROR_BAD_DEVICE The string pointed to by lpLocalPath is invalid.
 *   ERROR_CONNECTION_UNAVAIL There is no current connection to the remote device, but there is a
 *   remembered, or persistent, connection to it. ERROR_MORE_DATA The buffer pointed to by lpBuffer is
 *   too small. The function sets the variable pointed to by lpBufferSize to the required buffer size.
 *   More entries are available with subsequent calls. ERROR_NO_NETWORK No network present.
 *   ERROR_NOT_CONNECTED The device specified by lpLocalPath is not redirected.
 *
 * A universal form of a local path identifies a network resource in an unambiguous,
 * computer-independent manner. The name can then be passed to processes on other computers,
 * allowing those processes to obtain access to the resource.
 *
 * The WNetGetUniversalName function currently supports one universal name form: universal naming
 * convention (UNC) names, which look like the following:
 *
 *     \\servername\sharename\path\file
 *
 * Using the example from the preceding description of the lpLocalPath parameter, if the shared
 * network drive is on a server named COOLSERVER, and the share name is HOTSHARE, the UNC name for
 * the network resource whose local name is myShare:\WIN32\EXAMPLES\SAMPLE.DOC would be
 *
 *     \\coolserver\hotshare\win32\examples\sample.doc
 *
 * The UNIVERSAL_NAME_INFO data structure contains a pointer to a UNC name string. The
 * REMOTE_NAME_INFO data structure contains a pointer to a UNC name string. It also includes
 * pointers to two other useful strings. A program can pass the REMOTE_NAME_INFO structure's
 * lpszConnectionInfo member into the WNetAddConnection3 function to connect a local device to the
 * network resource, and then append the string pointed to by the lpszRemainingPath member to the
 * local device string. The resulting string can be passed to Win32 file functions.
 */
#define WNetGetUniversalName  WNetGetUniversalNameW
#else
/**
 * This function maps a local path for a network resource to a data structure containing the
 * Universal Name Convention based name.
 *
 * @param lpLocalPath [in] Long pointer to a null-terminated string that is a local name for a
 *   network resource. It must point to the subfolder in the \NETWORK directory. For example, if local
 *   name "myShare" has been mapped to a network share, and the network resource of interest is a file
 *   named SAMPLE.DOC in the directory \WIN32\EXAMPLES on that share, the local path is
 *   myShare:\WIN32\EXAMPLES\SAMPLE.DOC.
 * @param dwInfoLevel [in] Specifies the type of data structure that the function will store in the
 *   buffer pointed to by lpBuffer. This parameter can be one of the following values: Value
 *   Description UNIVERSAL_NAME_INFO_LEVEL The function will store a UNIVERSAL_NAME_INFO data
 *   structure in the buffer. REMOTE_NAME_INFO_LEVEL The function will store a REMOTE_NAME_INFO data
 *   structure in the buffer. The UNIVERSAL_NAME_INFO data structure points to a Universal Naming
 *   Convention (UNC) name string. The REMOTE_NAME_INFO data structure points to a UNC name string and
 *   two additional connection information strings.
 * @param lpBuffer [out] Long pointer to a buffer that receives the type of data structure specified
 *   by the dwInfoLevel parameter.
 * @param lpBufferSize [in/out] Long pointer to a variable that specifies the size in bytes of the
 *   buffer pointed to by lpBuffer. If the function succeeds, it sets the variable pointed to by
 *   lpBufferSize to the size in bytes of the data structure stored in the buffer. If the function
 *   fails because the buffer is too small, indicated by the ERROR_MORE_DATA error value, it sets the
 *   variable pointed to by lpBufferSize to the required buffer size.
 *
 * @return ERROR_SUCCESS indicates success. An error value indicates failure. To get extended error
 *   information, call GetLastError. Possible GetLastError error values are described in the following
 *   table. Value Description ERROR_BAD_DEVICE The string pointed to by lpLocalPath is invalid.
 *   ERROR_CONNECTION_UNAVAIL There is no current connection to the remote device, but there is a
 *   remembered, or persistent, connection to it. ERROR_MORE_DATA The buffer pointed to by lpBuffer is
 *   too small. The function sets the variable pointed to by lpBufferSize to the required buffer size.
 *   More entries are available with subsequent calls. ERROR_NO_NETWORK No network present.
 *   ERROR_NOT_CONNECTED The device specified by lpLocalPath is not redirected.
 *
 * A universal form of a local path identifies a network resource in an unambiguous,
 * computer-independent manner. The name can then be passed to processes on other computers,
 * allowing those processes to obtain access to the resource.
 *
 * The WNetGetUniversalName function currently supports one universal name form: universal naming
 * convention (UNC) names, which look like the following:
 *
 *     \\servername\sharename\path\file
 *
 * Using the example from the preceding description of the lpLocalPath parameter, if the shared
 * network drive is on a server named COOLSERVER, and the share name is HOTSHARE, the UNC name for
 * the network resource whose local name is myShare:\WIN32\EXAMPLES\SAMPLE.DOC would be
 *
 *     \\coolserver\hotshare\win32\examples\sample.doc
 *
 * The UNIVERSAL_NAME_INFO data structure contains a pointer to a UNC name string. The
 * REMOTE_NAME_INFO data structure contains a pointer to a UNC name string. It also includes
 * pointers to two other useful strings. A program can pass the REMOTE_NAME_INFO structure's
 * lpszConnectionInfo member into the WNetAddConnection3 function to connect a local device to the
 * network resource, and then append the string pointed to by the lpszRemainingPath member to the
 * local device string. The resulting string can be passed to Win32 file functions.
 */
#define WNetGetUniversalName  WNetGetUniversalNameA
#endif // !UNICODE

//
//  Authentication and Logon/Logoff.
//

/**
 * This function retrieves the user name used to establish a network connection.
 *
 * @param lpName [in] Long pointer to a null-terminated string that specifies either a local name
 *   that has been redirected to a network resource, or the remote name of a network resource to which
 *   a connection has been made without necessarily creating a local name.
 * @param lpUserName [out] Long pointer to a buffer that receives the null-terminated user name.
 * @param lpnLength [in/out] Long pointer to a variable that specifies the size, in characters, of
 *   the buffer pointed to by lpUserName. If the call fails because the buffer is not big enough, this
 *   variable contains the required buffer size.
 *
 * @return ERROR_SUCCESS indicates success. An error value indicates failure. To get extended error
 *   information, call GetLastError. Possible GetLastError error values are described in the following
 *   table. Value Description ERROR_NOT_CONNECTED The resource name specified by lpName is not a
 *   connected network resource. ERROR_MORE_DATA The supplied buffer is not large enough to hold the
 *   user name. ERROR_NO_NETWORK No network is present. The function returns error values for
 *   compatibility with Windows-based desktop platforms. For compatibility with the Win32 API, the
 *   function also sets the error value returned by GetLastError.
 */
DWORD APIENTRY
WNetGetUserA(
     LPCSTR  lpName,
     LPSTR   lpUserName,
     LPDWORD   lpnLength
    );
/**
 * This function retrieves the user name used to establish a network connection.
 *
 * @param lpName [in] Long pointer to a null-terminated string that specifies either a local name
 *   that has been redirected to a network resource, or the remote name of a network resource to which
 *   a connection has been made without necessarily creating a local name.
 * @param lpUserName [out] Long pointer to a buffer that receives the null-terminated user name.
 * @param lpnLength [in/out] Long pointer to a variable that specifies the size, in characters, of
 *   the buffer pointed to by lpUserName. If the call fails because the buffer is not big enough, this
 *   variable contains the required buffer size.
 *
 * @return ERROR_SUCCESS indicates success. An error value indicates failure. To get extended error
 *   information, call GetLastError. Possible GetLastError error values are described in the following
 *   table. Value Description ERROR_NOT_CONNECTED The resource name specified by lpName is not a
 *   connected network resource. ERROR_MORE_DATA The supplied buffer is not large enough to hold the
 *   user name. ERROR_NO_NETWORK No network is present. The function returns error values for
 *   compatibility with Windows-based desktop platforms. For compatibility with the Win32 API, the
 *   function also sets the error value returned by GetLastError.
 */
DWORD APIENTRY
WNetGetUserW(
     LPCWSTR  lpName,
     LPWSTR   lpUserName,
     LPDWORD   lpnLength
    );
#ifdef UNICODE
/**
 * This function retrieves the user name used to establish a network connection.
 *
 * @param lpName [in] Long pointer to a null-terminated string that specifies either a local name
 *   that has been redirected to a network resource, or the remote name of a network resource to which
 *   a connection has been made without necessarily creating a local name.
 * @param lpUserName [out] Long pointer to a buffer that receives the null-terminated user name.
 * @param lpnLength [in/out] Long pointer to a variable that specifies the size, in characters, of
 *   the buffer pointed to by lpUserName. If the call fails because the buffer is not big enough, this
 *   variable contains the required buffer size.
 *
 * @return ERROR_SUCCESS indicates success. An error value indicates failure. To get extended error
 *   information, call GetLastError. Possible GetLastError error values are described in the following
 *   table. Value Description ERROR_NOT_CONNECTED The resource name specified by lpName is not a
 *   connected network resource. ERROR_MORE_DATA The supplied buffer is not large enough to hold the
 *   user name. ERROR_NO_NETWORK No network is present. The function returns error values for
 *   compatibility with Windows-based desktop platforms. For compatibility with the Win32 API, the
 *   function also sets the error value returned by GetLastError.
 */
#define WNetGetUser  WNetGetUserW
#else
/**
 * This function retrieves the user name used to establish a network connection.
 *
 * @param lpName [in] Long pointer to a null-terminated string that specifies either a local name
 *   that has been redirected to a network resource, or the remote name of a network resource to which
 *   a connection has been made without necessarily creating a local name.
 * @param lpUserName [out] Long pointer to a buffer that receives the null-terminated user name.
 * @param lpnLength [in/out] Long pointer to a variable that specifies the size, in characters, of
 *   the buffer pointed to by lpUserName. If the call fails because the buffer is not big enough, this
 *   variable contains the required buffer size.
 *
 * @return ERROR_SUCCESS indicates success. An error value indicates failure. To get extended error
 *   information, call GetLastError. Possible GetLastError error values are described in the following
 *   table. Value Description ERROR_NOT_CONNECTED The resource name specified by lpName is not a
 *   connected network resource. ERROR_MORE_DATA The supplied buffer is not large enough to hold the
 *   user name. ERROR_NO_NETWORK No network is present. The function returns error values for
 *   compatibility with Windows-based desktop platforms. For compatibility with the Win32 API, the
 *   function also sets the error value returned by GetLastError.
 */
#define WNetGetUser  WNetGetUserA
#endif // !UNICODE


//
//  STATUS CODES
//

// General   

#define WN_SUCCESS                      NO_ERROR
#define WN_NO_ERROR                     NO_ERROR
#define WN_NOT_SUPPORTED                ERROR_NOT_SUPPORTED
#define WN_CANCEL                       ERROR_CANCELLED
#define WN_RETRY                        ERROR_RETRY
#define WN_NET_ERROR                    ERROR_UNEXP_NET_ERR
#define WN_MORE_DATA                    ERROR_MORE_DATA
#define WN_BAD_POINTER                  ERROR_INVALID_ADDRESS
#define WN_BAD_VALUE                    ERROR_INVALID_PARAMETER
#define WN_BAD_USER                     ERROR_BAD_USERNAME
#define WN_BAD_PASSWORD                 ERROR_INVALID_PASSWORD
#define WN_ACCESS_DENIED                ERROR_ACCESS_DENIED
#define WN_FUNCTION_BUSY                ERROR_BUSY
#define WN_WINDOWS_ERROR                ERROR_UNEXP_NET_ERR
#define WN_OUT_OF_MEMORY                ERROR_NOT_ENOUGH_MEMORY
#define WN_NO_NETWORK                   ERROR_NO_NETWORK
#define WN_EXTENDED_ERROR               ERROR_EXTENDED_ERROR
#define WN_BAD_LEVEL                    ERROR_INVALID_LEVEL
#define WN_BAD_HANDLE                   ERROR_INVALID_HANDLE
#if(WINVER >= 0x0400)
#define WN_NOT_INITIALIZING             ERROR_ALREADY_INITIALIZED
#define WN_NO_MORE_DEVICES              ERROR_NO_MORE_DEVICES
#endif /* WINVER >= 0x0400 */

// Connection

#define WN_NOT_CONNECTED                ERROR_NOT_CONNECTED
#define WN_OPEN_FILES                   ERROR_OPEN_FILES
#define WN_DEVICE_IN_USE                ERROR_DEVICE_IN_USE
#define WN_BAD_NETNAME                  ERROR_BAD_NET_NAME
#define WN_BAD_LOCALNAME                ERROR_BAD_DEVICE
#define WN_ALREADY_CONNECTED            ERROR_ALREADY_ASSIGNED
#define WN_DEVICE_ERROR                 ERROR_GEN_FAILURE
#define WN_CONNECTION_CLOSED            ERROR_CONNECTION_UNAVAIL
#define WN_NO_NET_OR_BAD_PATH           ERROR_NO_NET_OR_BAD_PATH
#define WN_BAD_PROVIDER                 ERROR_BAD_PROVIDER
#define WN_CANNOT_OPEN_PROFILE          ERROR_CANNOT_OPEN_PROFILE
#define WN_BAD_PROFILE                  ERROR_BAD_PROFILE
#define WN_BAD_DEV_TYPE                 ERROR_BAD_DEV_TYPE
#define WN_DEVICE_ALREADY_REMEMBERED    ERROR_DEVICE_ALREADY_REMEMBERED

// Enumeration

#define WN_NO_MORE_ENTRIES              ERROR_NO_MORE_ITEMS
#define WN_NOT_CONTAINER                ERROR_NOT_CONTAINER

#if(WINVER >= 0x0400)
// Authentication

#define WN_NOT_AUTHENTICATED            ERROR_NOT_AUTHENTICATED
#define WN_NOT_LOGGED_ON                ERROR_NOT_LOGGED_ON
#define WN_NOT_VALIDATED                ERROR_NO_LOGON_SERVERS
#endif /* WINVER >= 0x0400 */


#if defined(UNDER_CE) && defined(WINCEOEM) && defined(WINCEMACRO)
#include <mwnetfun.h>
#endif

#ifdef __cplusplus
}
#endif

#endif  // _WINNETWK_

// @CESYSGEN ENDIF
