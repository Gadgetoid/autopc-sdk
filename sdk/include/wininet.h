/*++

Copyright (c) 1995-1997  Microsoft Corporation

Module Name:

    wininet.h

Abstract:

    Contains manifests, macros, types and prototypes for Microsoft Windows
    Internet Extensions

--*/

#if !defined(_WININET_)
#define _WININET_

/*
 * Set up Structure Packing to be 4 bytes
 * for all wininet structures
 */

#pragma pack(push, wininet, 4)

#if defined(__cplusplus)
extern "C" {
#endif

#if !defined(_WINX32_)
#define INTERNETAPI DECLSPEC_IMPORT
#else
#define INTERNETAPI
#endif

//
// internet types
//

typedef LPVOID HINTERNET;
typedef HINTERNET * LPHINTERNET;

typedef WORD INTERNET_PORT;
typedef INTERNET_PORT * LPINTERNET_PORT;

//
// Internet APIs
//

//
// manifests
//

#define INTERNET_INVALID_PORT_NUMBER    0           // use the protocol-specific default

#define INTERNET_DEFAULT_FTP_PORT       21          // default for FTP servers
#define INTERNET_DEFAULT_GOPHER_PORT    70          //    "     "  gopher "
#define INTERNET_DEFAULT_HTTP_PORT      80          //    "     "  HTTP   "
#define INTERNET_DEFAULT_HTTPS_PORT     443         //    "     "  HTTPS  "
#define INTERNET_DEFAULT_SOCKS_PORT     1080        // default for SOCKS firewall servers.

#define MAX_CACHE_ENTRY_INFO_SIZE       4096

//
// maximum field lengths (arbitrary)
//

#define INTERNET_MAX_HOST_NAME_LENGTH   256
#define INTERNET_MAX_USER_NAME_LENGTH   128
#define INTERNET_MAX_PASSWORD_LENGTH    128
#define INTERNET_MAX_PORT_NUMBER_LENGTH 5           // INTERNET_PORT is unsigned short
#define INTERNET_MAX_PORT_NUMBER_VALUE  65535       // maximum unsigned short value
#define INTERNET_MAX_PATH_LENGTH        2048
#define INTERNET_MAX_PROTOCOL_NAME      "gopher"    // longest protocol name
#define INTERNET_MAX_URL_LENGTH         ((sizeof(INTERNET_MAX_PROTOCOL_NAME) - 1) \
                                        + sizeof("://") \
                                        + INTERNET_MAX_PATH_LENGTH)

//
// values returned by InternetQueryOption() with INTERNET_OPTION_KEEP_CONNECTION:
//

#define INTERNET_KEEP_ALIVE_UNKNOWN     ((DWORD)-1)
#define INTERNET_KEEP_ALIVE_ENABLED     1
#define INTERNET_KEEP_ALIVE_DISABLED    0

//
// flags returned by InternetQueryOption() with INTERNET_OPTION_REQUEST_FLAGS
//

#define INTERNET_REQFLAG_FROM_CACHE     0x00000001
#define INTERNET_REQFLAG_ASYNC          0x00000002

//
// flags common to open functions (not InternetOpen()):
//

#define INTERNET_FLAG_RELOAD            0x80000000  // retrieve the original item

//
// flags for InternetOpenUrl():
//

#define INTERNET_FLAG_RAW_DATA          0x40000000  // receive the item as raw data
#define INTERNET_FLAG_EXISTING_CONNECT  0x20000000  // do not create new connection object

//
// flags for InternetOpen():
//

#define INTERNET_FLAG_ASYNC             0x10000000  // this request is asynchronous (where supported)

//
// protocol-specific flags:
//

#define INTERNET_FLAG_PASSIVE           0x08000000  // used for FTP connections

//
// additional cache flags
//

#define INTERNET_FLAG_NO_CACHE_WRITE    0x04000000  // don't write this item to the cache
#define INTERNET_FLAG_DONT_CACHE        INTERNET_FLAG_NO_CACHE_WRITE

#define INTERNET_FLAG_MAKE_PERSISTENT   0x02000000  // make this item persistent in cache

#define INTERNET_FLAG_OFFLINE           0x01000000  // use offline semantics

//
// additional flags
//

#define INTERNET_FLAG_SECURE            0x00800000  // use PCT/SSL if applicable (HTTP)

#define INTERNET_FLAG_KEEP_CONNECTION   0x00400000  // use keep-alive semantics

#define INTERNET_FLAG_NO_AUTO_REDIRECT  0x00200000  // don't handle redirections automatically

#define INTERNET_FLAG_READ_PREFETCH     0x00100000  // do background read prefetch

#define INTERNET_FLAG_NO_COOKIES        0x00080000  // no automatic cookie handling

#define INTERNET_FLAG_NO_AUTH           0x00040000  // no automatic authentication handling

//
// Security Ignore Flags, Allow HttpOpenRequest to overide
//  Secure Channel (SSL/PCT) failures of the following types.
//

#define INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP   0x00008000 // ex: https:// to http://

#define INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTPS  0x00004000 // ex: http:// to https://

#define INTERNET_FLAG_IGNORE_CERT_DATE_INVALID  0x00002000 // expired X509 Cert.

#define INTERNET_FLAG_IGNORE_CERT_CN_INVALID    0x00001000 // bad common name in X509 Cert.

//more caching flags
#define INTERNET_FLAG_MUST_CACHE_REQUEST        0x00000010 // fails if unable to cache request
#define INTERNET_FLAG_RESYNCHRONIZE             0x00000800 // asking wininet to update an item if it is newer
#define INTERNET_FLAG_HYPERLINK                 0x00000400 // asking wininet to
                                                           //do hyperlinking semantic which works right for scripts
#define INTERNET_FLAG_NO_UI                     0x00000200

//
// flags for FTP
//

#define INTERNET_FLAG_TRANSFER_ASCII    FTP_TRANSFER_TYPE_ASCII
#define INTERNET_FLAG_TRANSFER_BINARY   FTP_TRANSFER_TYPE_BINARY

//
// flags field masks
//

#define SECURITY_INTERNET_MASK  (INTERNET_FLAG_IGNORE_CERT_CN_INVALID    |  \
                                 INTERNET_FLAG_IGNORE_CERT_DATE_INVALID  |  \
                                 INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTPS  |  \
                                 INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP   )

#define SECURITY_SET_MASK       SECURITY_INTERNET_MASK

#define INTERNET_FLAGS_MASK     (INTERNET_FLAG_RELOAD               \
                                | INTERNET_FLAG_RAW_DATA            \
                                | INTERNET_FLAG_EXISTING_CONNECT    \
                                | INTERNET_FLAG_ASYNC               \
                                | INTERNET_FLAG_PASSIVE             \
                                | INTERNET_FLAG_NO_CACHE_WRITE      \
                                | INTERNET_FLAG_MAKE_PERSISTENT     \
                                | INTERNET_FLAG_OFFLINE             \
                                | INTERNET_FLAG_SECURE              \
                                | INTERNET_FLAG_KEEP_CONNECTION     \
                                | INTERNET_FLAG_NO_AUTO_REDIRECT    \
                                | INTERNET_FLAG_READ_PREFETCH       \
                                | INTERNET_FLAG_NO_COOKIES          \
                                | INTERNET_FLAG_NO_AUTH             \
                                | SECURITY_INTERNET_MASK            \
                                | INTERNET_FLAG_TRANSFER_ASCII      \
                                | INTERNET_FLAG_TRANSFER_BINARY     \
                                | INTERNET_FLAG_RESYNCHRONIZE       \
                                | INTERNET_FLAG_MUST_CACHE_REQUEST  \
                                | INTERNET_FLAG_HYPERLINK           \
                                | INTERNET_FLAG_NO_UI               \
                                )

#define INTERNET_OPTIONS_MASK   (~INTERNET_FLAGS_MASK)

//
// INTERNET_NO_CALLBACK - if this value is presented as the dwContext parameter
// then no call-backs will be made for that API
//

#define INTERNET_NO_CALLBACK            0

//
// structures/types
//

//
// INTERNET_SCHEME - enumerated URL scheme type
//

typedef enum {
    INTERNET_SCHEME_PARTIAL = -2,
    INTERNET_SCHEME_UNKNOWN = -1,
    INTERNET_SCHEME_DEFAULT = 0,
    INTERNET_SCHEME_FTP,
    INTERNET_SCHEME_GOPHER,
    INTERNET_SCHEME_HTTP,
    INTERNET_SCHEME_HTTPS,
    INTERNET_SCHEME_FILE,
    INTERNET_SCHEME_NEWS,
    INTERNET_SCHEME_MAILTO,
    INTERNET_SCHEME_SOCKS,
    INTERNET_SCHEME_FIRST = INTERNET_SCHEME_FTP,
    INTERNET_SCHEME_LAST = INTERNET_SCHEME_SOCKS
} INTERNET_SCHEME, * LPINTERNET_SCHEME;

//
// INTERNET_ASYNC_RESULT - this structure is returned to the application via
// the callback with INTERNET_STATUS_REQUEST_COMPLETE. It is not sufficient to
// just return the result of the async operation. If the API failed then the
// app cannot call GetLastError() because the thread context will be incorrect.
// Both the value returned by the async API and any resultant error code are
// made available. The app need not check dwError if dwResult indicates that
// the API succeeded (in this case dwError will be ERROR_SUCCESS)
//

typedef struct {

    //
    // dwResult - the HINTERNET, DWORD or BOOL return code from an async API
    //

    DWORD dwResult;

    //
    // dwError - the error code if the API failed
    //

    DWORD dwError;
} INTERNET_ASYNC_RESULT, * LPINTERNET_ASYNC_RESULT;

//
// INTERNET_PREFETCH_STATUS -
//

typedef struct {

    //
    // dwStatus - status of download. See INTERNET_PREFETCH_ flags
    //

    DWORD dwStatus;

    //
    // dwSize - size of file downloaded so far
    //

    DWORD dwSize;
} INTERNET_PREFETCH_STATUS, * LPINTERNET_PREFETCH_STATUS;

//
// INTERNET_PREFETCH_STATUS - dwStatus values
//

#define INTERNET_PREFETCH_PROGRESS  0
#define INTERNET_PREFETCH_COMPLETE  1
#define INTERNET_PREFETCH_ABORTED   2

//
// INTERNET_PROXY_INFO - structure supplied with INTERNET_OPTION_PROXY to get/
// set proxy information on a InternetOpen() handle
//

typedef struct {

    //
    // dwAccessType - INTERNET_OPEN_TYPE_DIRECT, INTERNET_OPEN_TYPE_PROXY, or
    // INTERNET_OPEN_TYPE_PRECONFIG (set only)
    //

    DWORD dwAccessType;

    //
    // lpszProxy - proxy server list
    //

    LPCSTR lpszProxy;

    //
    // lpszProxyBypass - proxy bypass list
    //

    LPCSTR lpszProxyBypass;
} INTERNET_PROXY_INFOA, * LPINTERNET_PROXY_INFOA;

typedef struct {

    //
    // dwAccessType - INTERNET_OPEN_TYPE_DIRECT, INTERNET_OPEN_TYPE_PROXY, or
    // INTERNET_OPEN_TYPE_PRECONFIG (set only)
    //

    DWORD dwAccessType;

    //
    // lpszProxy - proxy server list
    //

    LPCWSTR lpszProxy;

    //
    // lpszProxyBypass - proxy bypass list
    //

    LPCWSTR lpszProxyBypass;
} INTERNET_PROXY_INFOW, * LPINTERNET_PROXY_INFOW;

#ifdef UNICODE
typedef INTERNET_PROXY_INFOW INTERNET_PROXY_INFO;
typedef LPINTERNET_PROXY_INFOW LPINTERNET_PROXY_INFO;
#else
typedef INTERNET_PROXY_INFOA INTERNET_PROXY_INFO;
typedef LPINTERNET_PROXY_INFOA LPINTERNET_PROXY_INFO;
#endif // UNICODE

//
// INTERNET_VERSION_INFO - version information returned via
// InternetQueryOption(..., INTERNET_OPTION_VERSION, ...)
//

typedef struct {
    DWORD dwMajorVersion;
    DWORD dwMinorVersion;
} INTERNET_VERSION_INFO, * LPINTERNET_VERSION_INFO;

//
// URL_COMPONENTS - the constituent parts of an URL. Used in InternetCrackUrl()
// and InternetCreateUrl()
//
// For InternetCrackUrl(), if a pointer field and its corresponding length field
// are both 0 then that component is not returned; If the pointer field is NULL
// but the length field is not zero, then both the pointer and length fields are
// returned; if both pointer and corresponding length fields are non-zero then
// the pointer field points to a buffer where the component is copied. The
// component may be un-escaped, depending on dwFlags
//
// For InternetCreateUrl(), the pointer fields should be NULL if the component
// is not required. If the corresponding length field is zero then the pointer
// field is the address of a zero-terminated string. If the length field is not
// zero then it is the string length of the corresponding pointer field
//

typedef struct {
    DWORD   dwStructSize;       // size of this structure. Used in version check
    LPSTR   lpszScheme;         // pointer to scheme name
    DWORD   dwSchemeLength;     // length of scheme name
    INTERNET_SCHEME nScheme;    // enumerated scheme type (if known)
    LPSTR   lpszHostName;       // pointer to host name
    DWORD   dwHostNameLength;   // length of host name
    INTERNET_PORT nPort;        // converted port number
    LPSTR   lpszUserName;       // pointer to user name
    DWORD   dwUserNameLength;   // length of user name
    LPSTR   lpszPassword;       // pointer to password
    DWORD   dwPasswordLength;   // length of password
    LPSTR   lpszUrlPath;        // pointer to URL-path
    DWORD   dwUrlPathLength;    // length of URL-path
    LPSTR   lpszExtraInfo;      // pointer to extra information (e.g. ?foo or #foo)
    DWORD   dwExtraInfoLength;  // length of extra information
} URL_COMPONENTSA, * LPURL_COMPONENTSA;
typedef struct {
    DWORD   dwStructSize;       // size of this structure. Used in version check
    LPWSTR  lpszScheme;         // pointer to scheme name
    DWORD   dwSchemeLength;     // length of scheme name
    INTERNET_SCHEME nScheme;    // enumerated scheme type (if known)
    LPWSTR  lpszHostName;       // pointer to host name
    DWORD   dwHostNameLength;   // length of host name
    INTERNET_PORT nPort;        // converted port number
    LPWSTR  lpszUserName;       // pointer to user name
    DWORD   dwUserNameLength;   // length of user name
    LPWSTR  lpszPassword;       // pointer to password
    DWORD   dwPasswordLength;   // length of password
    LPWSTR  lpszUrlPath;        // pointer to URL-path
    DWORD   dwUrlPathLength;    // length of URL-path
    LPWSTR  lpszExtraInfo;      // pointer to extra information (e.g. ?foo or #foo)
    DWORD   dwExtraInfoLength;  // length of extra information
} URL_COMPONENTSW, * LPURL_COMPONENTSW;
#ifdef UNICODE
typedef URL_COMPONENTSW URL_COMPONENTS;
typedef LPURL_COMPONENTSW LPURL_COMPONENTS;
#else
typedef URL_COMPONENTSA URL_COMPONENTS;
typedef LPURL_COMPONENTSA LPURL_COMPONENTS;
#endif // UNICODE

//
// INTERNET_CERTIFICATE_INFO lpBuffer - contains the certificate returned from
// the server
//

typedef struct {

    //
    // ftExpiry - date the certificate expires.
    //

    FILETIME ftExpiry;

    //
    // ftStart - date the certificate becomes valid.
    //

    FILETIME ftStart;

    //
    // lpszSubjectInfo - the name of organization, site, and server
    //   the cert. was issued for.
    //

    LPWSTR lpszSubjectInfo;

    //
    // lpszIssuerInfo - the name of orgainzation, site, and server
    //   the cert was issues by.
    //

    LPWSTR lpszIssuerInfo;

    //
    // lpszProtocolName - the name of the protocol used to provide the secure
    //   connection.
    //

    LPWSTR lpszProtocolName;

    //
    // lpszSignatureAlgName - the name of the algorithm used for signing
    //  the certificate.
    //

    LPWSTR lpszSignatureAlgName;

    //
    // lpszEncryptionAlgName - the name of the algorithm used for
    //  doing encryption over the secure channel (SSL/PCT) connection.
    //

    LPWSTR lpszEncryptionAlgName;

    //
    // dwKeySize - size of the key.
    //

    DWORD dwKeySize;

} INTERNET_CERTIFICATE_INFOW, * LPINTERNET_CERTIFICATE_INFOW;

typedef struct {

    //
    // ftExpiry - date the certificate expires.
    //

    FILETIME ftExpiry;

    //
    // ftStart - date the certificate becomes valid.
    //

    FILETIME ftStart;

    //
    // lpszSubjectInfo - the name of organization, site, and server
    //   the cert. was issued for.
    //

    LPSTR lpszSubjectInfo;

    //
    // lpszIssuerInfo - the name of orgainzation, site, and server
    //   the cert was issues by.
    //

    LPSTR lpszIssuerInfo;

    //
    // lpszProtocolName - the name of the protocol used to provide the secure
    //   connection.
    //

    LPSTR lpszProtocolName;

    //
    // lpszSignatureAlgName - the name of the algorithm used for signing
    //  the certificate.
    //

    LPSTR lpszSignatureAlgName;

    //
    // lpszEncryptionAlgName - the name of the algorithm used for
    //  doing encryption over the secure channel (SSL/PCT) connection.
    //

    LPSTR lpszEncryptionAlgName;

    //
    // dwKeySize - size of the key.
    //

    DWORD dwKeySize;

} INTERNET_CERTIFICATE_INFOA, * LPINTERNET_CERTIFICATE_INFOA;

#ifdef UNICODE
    typedef INTERNET_CERTIFICATE_INFOW INTERNET_CERTIFICATE_INFO;
    typedef LPINTERNET_CERTIFICATE_INFOW LPINTERNET_CERTIFICATE_INFO;
#else
    typedef INTERNET_CERTIFICATE_INFOA INTERNET_CERTIFICATE_INFO;
    typedef LPINTERNET_CERTIFICATE_INFOA LPINTERNET_CERTIFICATE_INFO;
#endif //UNICODE

//
// prototypes
//

/**
 * This function formats a date and time according to the specified RFC format - as specified in the
 * Hypertext Transfer Protocol (HTTP) Specification 1.0.
 *
 * @param pst Pointer to a SYSTEMTIME structure that contains the date and time to format.
 * @param dwRFC Specifies the RFC format used. Currently, the only valid format is
 *   INTERNET_RFC1123_FORMAT.
 * @param lpszTime Long pointer to a buffer that receives the null-terminated string that contains
 *   the formatted date and time. The buffer should be of size INTERNET_RFC1123_BUFSIZE.
 * @param cbTime Size, in bytes, of the lpszTime buffer.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError.
 *
 * The cbTime parameter refers to the count of characters.
 */
INTERNETAPI
BOOL
WINAPI
InternetTimeFromSystemTimeA(
    IN  CONST SYSTEMTIME *pst,  // input GMT time
    IN  DWORD dwRFC,            // RFC format
    OUT LPSTR lpszTime,         // output string buffer
    IN  DWORD cbTime            // output buffer size
    );
/**
 * This function formats a date and time according to the specified RFC format - as specified in the
 * Hypertext Transfer Protocol (HTTP) Specification 1.0.
 *
 * @param pst Pointer to a SYSTEMTIME structure that contains the date and time to format.
 * @param dwRFC Specifies the RFC format used. Currently, the only valid format is
 *   INTERNET_RFC1123_FORMAT.
 * @param lpszTime Long pointer to a buffer that receives the null-terminated string that contains
 *   the formatted date and time. The buffer should be of size INTERNET_RFC1123_BUFSIZE.
 * @param cbTime Size, in bytes, of the lpszTime buffer.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError.
 *
 * The cbTime parameter refers to the count of characters.
 */
INTERNETAPI
BOOL
WINAPI
InternetTimeFromSystemTimeW(
    IN  CONST SYSTEMTIME *pst,  // input GMT time
    IN  DWORD dwRFC,            // RFC format
    OUT LPWSTR lpszTime,        // output string buffer
    IN  DWORD cbTime            // output buffer size
    );
#ifdef UNICODE
/**
 * This function formats a date and time according to the specified RFC format - as specified in the
 * Hypertext Transfer Protocol (HTTP) Specification 1.0.
 *
 * @param pst Pointer to a SYSTEMTIME structure that contains the date and time to format.
 * @param dwRFC Specifies the RFC format used. Currently, the only valid format is
 *   INTERNET_RFC1123_FORMAT.
 * @param lpszTime Long pointer to a buffer that receives the null-terminated string that contains
 *   the formatted date and time. The buffer should be of size INTERNET_RFC1123_BUFSIZE.
 * @param cbTime Size, in bytes, of the lpszTime buffer.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError.
 *
 * The cbTime parameter refers to the count of characters.
 */
#define InternetTimeFromSystemTime	InternetTimeFromSystemTimeW
#else
/**
 * This function formats a date and time according to the specified RFC format - as specified in the
 * Hypertext Transfer Protocol (HTTP) Specification 1.0.
 *
 * @param pst Pointer to a SYSTEMTIME structure that contains the date and time to format.
 * @param dwRFC Specifies the RFC format used. Currently, the only valid format is
 *   INTERNET_RFC1123_FORMAT.
 * @param lpszTime Long pointer to a buffer that receives the null-terminated string that contains
 *   the formatted date and time. The buffer should be of size INTERNET_RFC1123_BUFSIZE.
 * @param cbTime Size, in bytes, of the lpszTime buffer.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError.
 *
 * The cbTime parameter refers to the count of characters.
 */
#define InternetTimeFromSystemTime	InternetTimeFromSystemTimeA
#endif // !UNICODE


//
// constants for InternetTimeFromSystemTime
//

#define INTERNET_RFC1123_FORMAT     0
#define INTERNET_RFC1123_BUFSIZE   30

/**
 * This function takes an HTTP time/date string and converts it to a SYSTEMTIME structure.
 *
 * @param lpszTime Long pointer to a null-terminated date/time string to convert.
 * @param pst Pointer to the converted time.
 * @param dwReserved Reserved; set to zero.
 *
 * @return TRUE indicates that the string was converted. FALSE indicates failure. To get extended
 *   error information, call GetLastError.
 */
INTERNETAPI
BOOL
WINAPI
InternetTimeToSystemTimeA(
    IN  LPCSTR lpszTime,         // NULL terminated string
    OUT SYSTEMTIME *pst,         // output in GMT time
    IN  DWORD dwReserved
    );

/**
 * This function takes an HTTP time/date string and converts it to a SYSTEMTIME structure.
 *
 * @param lpszTime Long pointer to a null-terminated date/time string to convert.
 * @param pst Pointer to the converted time.
 * @param dwReserved Reserved; set to zero.
 *
 * @return TRUE indicates that the string was converted. FALSE indicates failure. To get extended
 *   error information, call GetLastError.
 */
INTERNETAPI
BOOL
WINAPI
InternetTimeToSystemTimeW(
    IN  LPCWSTR lpszTime,         // NULL terminated string
    OUT SYSTEMTIME *pst,         // output in GMT time
    IN  DWORD dwReserved
    );

#ifdef UNICODE
/**
 * This function takes an HTTP time/date string and converts it to a SYSTEMTIME structure.
 *
 * @param lpszTime Long pointer to a null-terminated date/time string to convert.
 * @param pst Pointer to the converted time.
 * @param dwReserved Reserved; set to zero.
 *
 * @return TRUE indicates that the string was converted. FALSE indicates failure. To get extended
 *   error information, call GetLastError.
 */
#define InternetTimeToSystemTime	InternetTimeToSystemTimeW
#else
/**
 * This function takes an HTTP time/date string and converts it to a SYSTEMTIME structure.
 *
 * @param lpszTime Long pointer to a null-terminated date/time string to convert.
 * @param pst Pointer to the converted time.
 * @param dwReserved Reserved; set to zero.
 *
 * @return TRUE indicates that the string was converted. FALSE indicates failure. To get extended
 *   error information, call GetLastError.
 */
#define InternetTimeToSystemTime	InternetTimeToSystemTimeA
#endif // !UNICODE

INTERNETAPI
BOOL
WINAPI
InternetDebugGetLocalTime(
    OUT SYSTEMTIME * pstLocalTime,
    OUT DWORD      * pdwReserved
);

/**
 * This function cracks a URL into its component parts.
 *
 * @param lpszUrl Long pointer to a null-terminated string that contains the canonical URL to crack.
 * @param dwUrlLength Specifies the length of the lpszUrl string, or zero if lpszUrl is an ASCIIZ
 *   string.
 * @param dwFlags Specifies the operation. It is one of the following values: Value Description
 *   ICU_DECODE Converts encoded characters back to their normal form. This can be used only if the
 *   user provides buffers in the URL_COMPONENTS structure to copy the components into. ICU_ESCAPE
 *   Converts all escape sequences (%xx) to their corresponding characters. This can be used only if
 *   the user provides buffers in the URL_COMPONENTS structure to copy the components into.
 * @param lpUrlComponents Long pointer to a URL_COMPONENTS structure that receives the URL
 *   components.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError.
 *
 * Always directly call the ANSI version of this function, InternetCrackUrlA.
 *
 * The required components are indicated by members of the URL_COMPONENTS structure. Each component
 * has a pointer to the value and has a member that stores the length of the stored value. If both
 * the value and the length for a component are equal to zero, that component is not returned. If
 * the pointer to the value of the component is NULL and the value of its corresponding length
 * member is nonzero, the address of the first character of the corresponding component in the
 * lpszUrl string is stored in the pointer, and the length of the component is stored in the length
 * member.
 *
 * If the pointer contains the address of the user-supplied buffer, the length member must contain
 * the size of the buffer. InternetCrackUrl copies the component into the buffer, and the length
 * member is set to the length of the copied component, minus 1 for the trailing string terminator.
 *
 * For InternetCrackUrl to work properly, the size of the URL_COMPONENTS structure must be stored in
 * the dwStructSize member.
 */
INTERNETAPI
BOOL
WINAPI
InternetCrackUrlA(
    IN LPCSTR lpszUrl,
    IN DWORD dwUrlLength,
    IN DWORD dwFlags,
    IN OUT LPURL_COMPONENTSA lpUrlComponents
    );
/**
 * This function cracks a URL into its component parts.
 *
 * @param lpszUrl Long pointer to a null-terminated string that contains the canonical URL to crack.
 * @param dwUrlLength Specifies the length of the lpszUrl string, or zero if lpszUrl is an ASCIIZ
 *   string.
 * @param dwFlags Specifies the operation. It is one of the following values: Value Description
 *   ICU_DECODE Converts encoded characters back to their normal form. This can be used only if the
 *   user provides buffers in the URL_COMPONENTS structure to copy the components into. ICU_ESCAPE
 *   Converts all escape sequences (%xx) to their corresponding characters. This can be used only if
 *   the user provides buffers in the URL_COMPONENTS structure to copy the components into.
 * @param lpUrlComponents Long pointer to a URL_COMPONENTS structure that receives the URL
 *   components.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError.
 *
 * Always directly call the ANSI version of this function, InternetCrackUrlA.
 *
 * The required components are indicated by members of the URL_COMPONENTS structure. Each component
 * has a pointer to the value and has a member that stores the length of the stored value. If both
 * the value and the length for a component are equal to zero, that component is not returned. If
 * the pointer to the value of the component is NULL and the value of its corresponding length
 * member is nonzero, the address of the first character of the corresponding component in the
 * lpszUrl string is stored in the pointer, and the length of the component is stored in the length
 * member.
 *
 * If the pointer contains the address of the user-supplied buffer, the length member must contain
 * the size of the buffer. InternetCrackUrl copies the component into the buffer, and the length
 * member is set to the length of the copied component, minus 1 for the trailing string terminator.
 *
 * For InternetCrackUrl to work properly, the size of the URL_COMPONENTS structure must be stored in
 * the dwStructSize member.
 */
INTERNETAPI
BOOL
WINAPI
InternetCrackUrlW(
    IN LPCWSTR lpszUrl,
    IN DWORD dwUrlLength,
    IN DWORD dwFlags,
    IN OUT LPURL_COMPONENTSW lpUrlComponents
    );
#ifdef UNICODE
/**
 * This function cracks a URL into its component parts.
 *
 * @param lpszUrl Long pointer to a null-terminated string that contains the canonical URL to crack.
 * @param dwUrlLength Specifies the length of the lpszUrl string, or zero if lpszUrl is an ASCIIZ
 *   string.
 * @param dwFlags Specifies the operation. It is one of the following values: Value Description
 *   ICU_DECODE Converts encoded characters back to their normal form. This can be used only if the
 *   user provides buffers in the URL_COMPONENTS structure to copy the components into. ICU_ESCAPE
 *   Converts all escape sequences (%xx) to their corresponding characters. This can be used only if
 *   the user provides buffers in the URL_COMPONENTS structure to copy the components into.
 * @param lpUrlComponents Long pointer to a URL_COMPONENTS structure that receives the URL
 *   components.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError.
 *
 * Always directly call the ANSI version of this function, InternetCrackUrlA.
 *
 * The required components are indicated by members of the URL_COMPONENTS structure. Each component
 * has a pointer to the value and has a member that stores the length of the stored value. If both
 * the value and the length for a component are equal to zero, that component is not returned. If
 * the pointer to the value of the component is NULL and the value of its corresponding length
 * member is nonzero, the address of the first character of the corresponding component in the
 * lpszUrl string is stored in the pointer, and the length of the component is stored in the length
 * member.
 *
 * If the pointer contains the address of the user-supplied buffer, the length member must contain
 * the size of the buffer. InternetCrackUrl copies the component into the buffer, and the length
 * member is set to the length of the copied component, minus 1 for the trailing string terminator.
 *
 * For InternetCrackUrl to work properly, the size of the URL_COMPONENTS structure must be stored in
 * the dwStructSize member.
 */
#define InternetCrackUrl  InternetCrackUrlW
#else
/**
 * This function cracks a URL into its component parts.
 *
 * @param lpszUrl Long pointer to a null-terminated string that contains the canonical URL to crack.
 * @param dwUrlLength Specifies the length of the lpszUrl string, or zero if lpszUrl is an ASCIIZ
 *   string.
 * @param dwFlags Specifies the operation. It is one of the following values: Value Description
 *   ICU_DECODE Converts encoded characters back to their normal form. This can be used only if the
 *   user provides buffers in the URL_COMPONENTS structure to copy the components into. ICU_ESCAPE
 *   Converts all escape sequences (%xx) to their corresponding characters. This can be used only if
 *   the user provides buffers in the URL_COMPONENTS structure to copy the components into.
 * @param lpUrlComponents Long pointer to a URL_COMPONENTS structure that receives the URL
 *   components.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError.
 *
 * Always directly call the ANSI version of this function, InternetCrackUrlA.
 *
 * The required components are indicated by members of the URL_COMPONENTS structure. Each component
 * has a pointer to the value and has a member that stores the length of the stored value. If both
 * the value and the length for a component are equal to zero, that component is not returned. If
 * the pointer to the value of the component is NULL and the value of its corresponding length
 * member is nonzero, the address of the first character of the corresponding component in the
 * lpszUrl string is stored in the pointer, and the length of the component is stored in the length
 * member.
 *
 * If the pointer contains the address of the user-supplied buffer, the length member must contain
 * the size of the buffer. InternetCrackUrl copies the component into the buffer, and the length
 * member is set to the length of the copied component, minus 1 for the trailing string terminator.
 *
 * For InternetCrackUrl to work properly, the size of the URL_COMPONENTS structure must be stored in
 * the dwStructSize member.
 */
#define InternetCrackUrl  InternetCrackUrlA
#endif // !UNICODE

/**
 * This function creates a URL from its component parts.
 *
 * @param lpUrlComponents Long pointer to a URL_COMPONENTS structure that contains the components
 *   from which to create the URL.
 * @param dwFlags Specifies the operation of this function. It can be a combination of these values:
 *   Value Description ICU_ESCAPE Converts all escape sequences (%xx) to their corresponding
 *   characters. ICU_USERNAME When adding the user name, uses the name that was specified at logon
 *   time.
 * @param lpszUrl Long pointer to a buffer that receives the null-terminated string that contains
 *   the URL.
 * @param lpdwUrlLength Long pointer to the length, in bytes, of the lpszUrl buffer. When the
 *   function returns, this parameter receives the length, in bytes, of the URL string, minus 1 for
 *   the terminating character. If GetLastError returns ERROR_INSUFFICIENT_BUFFER, this parameter
 *   receives the number of bytes required to hold the created URL.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError.
 */
INTERNETAPI
BOOL
WINAPI
InternetCreateUrlA(
    IN LPURL_COMPONENTSA lpUrlComponents,
    IN DWORD dwFlags,
    OUT LPSTR lpszUrl,
    IN OUT LPDWORD lpdwUrlLength
    );
/**
 * This function creates a URL from its component parts.
 *
 * @param lpUrlComponents Long pointer to a URL_COMPONENTS structure that contains the components
 *   from which to create the URL.
 * @param dwFlags Specifies the operation of this function. It can be a combination of these values:
 *   Value Description ICU_ESCAPE Converts all escape sequences (%xx) to their corresponding
 *   characters. ICU_USERNAME When adding the user name, uses the name that was specified at logon
 *   time.
 * @param lpszUrl Long pointer to a buffer that receives the null-terminated string that contains
 *   the URL.
 * @param lpdwUrlLength Long pointer to the length, in bytes, of the lpszUrl buffer. When the
 *   function returns, this parameter receives the length, in bytes, of the URL string, minus 1 for
 *   the terminating character. If GetLastError returns ERROR_INSUFFICIENT_BUFFER, this parameter
 *   receives the number of bytes required to hold the created URL.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError.
 */
INTERNETAPI
BOOL
WINAPI
InternetCreateUrlW(
    IN LPURL_COMPONENTSW lpUrlComponents,
    IN DWORD dwFlags,
    OUT LPWSTR lpszUrl,
    IN OUT LPDWORD lpdwUrlLength
    );
#ifdef UNICODE
/**
 * This function creates a URL from its component parts.
 *
 * @param lpUrlComponents Long pointer to a URL_COMPONENTS structure that contains the components
 *   from which to create the URL.
 * @param dwFlags Specifies the operation of this function. It can be a combination of these values:
 *   Value Description ICU_ESCAPE Converts all escape sequences (%xx) to their corresponding
 *   characters. ICU_USERNAME When adding the user name, uses the name that was specified at logon
 *   time.
 * @param lpszUrl Long pointer to a buffer that receives the null-terminated string that contains
 *   the URL.
 * @param lpdwUrlLength Long pointer to the length, in bytes, of the lpszUrl buffer. When the
 *   function returns, this parameter receives the length, in bytes, of the URL string, minus 1 for
 *   the terminating character. If GetLastError returns ERROR_INSUFFICIENT_BUFFER, this parameter
 *   receives the number of bytes required to hold the created URL.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError.
 */
#define InternetCreateUrl  InternetCreateUrlW
#else
/**
 * This function creates a URL from its component parts.
 *
 * @param lpUrlComponents Long pointer to a URL_COMPONENTS structure that contains the components
 *   from which to create the URL.
 * @param dwFlags Specifies the operation of this function. It can be a combination of these values:
 *   Value Description ICU_ESCAPE Converts all escape sequences (%xx) to their corresponding
 *   characters. ICU_USERNAME When adding the user name, uses the name that was specified at logon
 *   time.
 * @param lpszUrl Long pointer to a buffer that receives the null-terminated string that contains
 *   the URL.
 * @param lpdwUrlLength Long pointer to the length, in bytes, of the lpszUrl buffer. When the
 *   function returns, this parameter receives the length, in bytes, of the URL string, minus 1 for
 *   the terminating character. If GetLastError returns ERROR_INSUFFICIENT_BUFFER, this parameter
 *   receives the number of bytes required to hold the created URL.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError.
 */
#define InternetCreateUrl  InternetCreateUrlA
#endif // !UNICODE

/**
 * This function converts a URL to a canonical form, including conversion of unsafe characters into
 * escape sequences.
 *
 * @param lpszUrl Long pointer to the null-terminated string that contains the input URL to
 *   canonicalize.
 * @param lpszBuffer Long pointer to the buffer that receives the null-terminated string that
 *   contains the resulting canonicalized URL.
 * @param lpdwBufferLength Long pointer to the length, in bytes, of the lpszBuffer buffer. If the
 *   function succeeds, this parameter receives the length of the lpszBuffer buffer-the length does
 *   not include the terminating null. If the function fails, this parameter receives the required
 *   length, in bytes, of the lpszBuffer buffer-the required length includes the terminating null.
 * @param dwFlags Specifies control canonicalization. Can be one of the following values: Value
 *   Description ICU_BROWSER_MODE Does not encode or decode characters after "#" or "?", and does not
 *   remove trailing white space after "?". If this value is not specified, the entire URL is encoded,
 *   and trailing white space is removed. ICU_DECODE Converts all %XX sequences to characters,
 *   including escape sequences, before the URL is parsed. ICU_ENCODE_SPACES_ONLY Encodes spaces only.
 *   ICU_NO_ENCODE Does not convert unsafe characters to escape sequences. ICU_NO_META Does not remove
 *   meta sequences (such as "." and "..") from the URL. If no flags are specified (dwFlags = 0), the
 *   function converts all unsafe characters and meta sequences (such as \.,\ .., and \...) to escape
 *   sequences.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError. Possible error values for GetLastError are described in the following table. Value
 *   Meaning ERROR_BAD_PATHNAME The URL could not be canonicalized. ERROR_INSUFFICIENT_BUFFER
 *   Canonicalized URL is too large to fit in the buffer provided. The *lpdwBufferLength parameter is
 *   set to the size, in bytes, of the buffer required to hold the resultant, canonicalized URL.
 *   ERROR_INTERNET_INVALID_URL The format of the URL is invalid. ERROR_INVALID_PARAMETER Bad string,
 *   buffer, buffer size, or flags parameter.
 *
 * InternetCanonicalizeUrl always encodes by default, even if the ICU_DECODE flag has been
 * specified. To decode without re-encoding, use ICU_DECODE | ICU_NO_ENCODE. If the ICU_DECODE flag
 * is used without ICU_NO_ENCODE, the URL is decoded before being parsed; unsafe characters then are
 * re-encoded after parsing. This function will handle arbitrary protocol schemes, but to do so it
 * must make inferences from the unsafe character set.
 *
 * The application calling InternetCanonicalizeUrl should track the usage of this function on a
 * particular URL. If unsafe characters in a URL have been converted to escape sequences, using
 * InternetCanonicalizeUrl again on the URL (with no flags) will cause the escape sequences to be
 * converted to another escape sequence. For example, a blank space in a URL would be converted to
 * the escape sequence "%20". Calling InternetCanonicalizeUrl again on the URL would cause the
 * escape sequence "%20" to be converted to the escape sequence "%2520", because the "%" sign is an
 * unsafe character that is reserved for escape sequences and is replaced by the function with the
 * escape sequence "%25".
 */
INTERNETAPI
BOOL
WINAPI
InternetCanonicalizeUrlA(
    IN LPCSTR lpszUrl,
    OUT LPSTR lpszBuffer,
    IN OUT LPDWORD lpdwBufferLength,
    IN DWORD dwFlags
    );
/**
 * This function converts a URL to a canonical form, including conversion of unsafe characters into
 * escape sequences.
 *
 * @param lpszUrl Long pointer to the null-terminated string that contains the input URL to
 *   canonicalize.
 * @param lpszBuffer Long pointer to the buffer that receives the null-terminated string that
 *   contains the resulting canonicalized URL.
 * @param lpdwBufferLength Long pointer to the length, in bytes, of the lpszBuffer buffer. If the
 *   function succeeds, this parameter receives the length of the lpszBuffer buffer-the length does
 *   not include the terminating null. If the function fails, this parameter receives the required
 *   length, in bytes, of the lpszBuffer buffer-the required length includes the terminating null.
 * @param dwFlags Specifies control canonicalization. Can be one of the following values: Value
 *   Description ICU_BROWSER_MODE Does not encode or decode characters after "#" or "?", and does not
 *   remove trailing white space after "?". If this value is not specified, the entire URL is encoded,
 *   and trailing white space is removed. ICU_DECODE Converts all %XX sequences to characters,
 *   including escape sequences, before the URL is parsed. ICU_ENCODE_SPACES_ONLY Encodes spaces only.
 *   ICU_NO_ENCODE Does not convert unsafe characters to escape sequences. ICU_NO_META Does not remove
 *   meta sequences (such as "." and "..") from the URL. If no flags are specified (dwFlags = 0), the
 *   function converts all unsafe characters and meta sequences (such as \.,\ .., and \...) to escape
 *   sequences.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError. Possible error values for GetLastError are described in the following table. Value
 *   Meaning ERROR_BAD_PATHNAME The URL could not be canonicalized. ERROR_INSUFFICIENT_BUFFER
 *   Canonicalized URL is too large to fit in the buffer provided. The *lpdwBufferLength parameter is
 *   set to the size, in bytes, of the buffer required to hold the resultant, canonicalized URL.
 *   ERROR_INTERNET_INVALID_URL The format of the URL is invalid. ERROR_INVALID_PARAMETER Bad string,
 *   buffer, buffer size, or flags parameter.
 *
 * InternetCanonicalizeUrl always encodes by default, even if the ICU_DECODE flag has been
 * specified. To decode without re-encoding, use ICU_DECODE | ICU_NO_ENCODE. If the ICU_DECODE flag
 * is used without ICU_NO_ENCODE, the URL is decoded before being parsed; unsafe characters then are
 * re-encoded after parsing. This function will handle arbitrary protocol schemes, but to do so it
 * must make inferences from the unsafe character set.
 *
 * The application calling InternetCanonicalizeUrl should track the usage of this function on a
 * particular URL. If unsafe characters in a URL have been converted to escape sequences, using
 * InternetCanonicalizeUrl again on the URL (with no flags) will cause the escape sequences to be
 * converted to another escape sequence. For example, a blank space in a URL would be converted to
 * the escape sequence "%20". Calling InternetCanonicalizeUrl again on the URL would cause the
 * escape sequence "%20" to be converted to the escape sequence "%2520", because the "%" sign is an
 * unsafe character that is reserved for escape sequences and is replaced by the function with the
 * escape sequence "%25".
 */
INTERNETAPI
BOOL
WINAPI
InternetCanonicalizeUrlW(
    IN LPCWSTR lpszUrl,
    OUT LPWSTR lpszBuffer,
    IN OUT LPDWORD lpdwBufferLength,
    IN DWORD dwFlags
    );
#ifdef UNICODE
/**
 * This function converts a URL to a canonical form, including conversion of unsafe characters into
 * escape sequences.
 *
 * @param lpszUrl Long pointer to the null-terminated string that contains the input URL to
 *   canonicalize.
 * @param lpszBuffer Long pointer to the buffer that receives the null-terminated string that
 *   contains the resulting canonicalized URL.
 * @param lpdwBufferLength Long pointer to the length, in bytes, of the lpszBuffer buffer. If the
 *   function succeeds, this parameter receives the length of the lpszBuffer buffer-the length does
 *   not include the terminating null. If the function fails, this parameter receives the required
 *   length, in bytes, of the lpszBuffer buffer-the required length includes the terminating null.
 * @param dwFlags Specifies control canonicalization. Can be one of the following values: Value
 *   Description ICU_BROWSER_MODE Does not encode or decode characters after "#" or "?", and does not
 *   remove trailing white space after "?". If this value is not specified, the entire URL is encoded,
 *   and trailing white space is removed. ICU_DECODE Converts all %XX sequences to characters,
 *   including escape sequences, before the URL is parsed. ICU_ENCODE_SPACES_ONLY Encodes spaces only.
 *   ICU_NO_ENCODE Does not convert unsafe characters to escape sequences. ICU_NO_META Does not remove
 *   meta sequences (such as "." and "..") from the URL. If no flags are specified (dwFlags = 0), the
 *   function converts all unsafe characters and meta sequences (such as \.,\ .., and \...) to escape
 *   sequences.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError. Possible error values for GetLastError are described in the following table. Value
 *   Meaning ERROR_BAD_PATHNAME The URL could not be canonicalized. ERROR_INSUFFICIENT_BUFFER
 *   Canonicalized URL is too large to fit in the buffer provided. The *lpdwBufferLength parameter is
 *   set to the size, in bytes, of the buffer required to hold the resultant, canonicalized URL.
 *   ERROR_INTERNET_INVALID_URL The format of the URL is invalid. ERROR_INVALID_PARAMETER Bad string,
 *   buffer, buffer size, or flags parameter.
 *
 * InternetCanonicalizeUrl always encodes by default, even if the ICU_DECODE flag has been
 * specified. To decode without re-encoding, use ICU_DECODE | ICU_NO_ENCODE. If the ICU_DECODE flag
 * is used without ICU_NO_ENCODE, the URL is decoded before being parsed; unsafe characters then are
 * re-encoded after parsing. This function will handle arbitrary protocol schemes, but to do so it
 * must make inferences from the unsafe character set.
 *
 * The application calling InternetCanonicalizeUrl should track the usage of this function on a
 * particular URL. If unsafe characters in a URL have been converted to escape sequences, using
 * InternetCanonicalizeUrl again on the URL (with no flags) will cause the escape sequences to be
 * converted to another escape sequence. For example, a blank space in a URL would be converted to
 * the escape sequence "%20". Calling InternetCanonicalizeUrl again on the URL would cause the
 * escape sequence "%20" to be converted to the escape sequence "%2520", because the "%" sign is an
 * unsafe character that is reserved for escape sequences and is replaced by the function with the
 * escape sequence "%25".
 */
#define InternetCanonicalizeUrl  InternetCanonicalizeUrlW
#else
/**
 * This function converts a URL to a canonical form, including conversion of unsafe characters into
 * escape sequences.
 *
 * @param lpszUrl Long pointer to the null-terminated string that contains the input URL to
 *   canonicalize.
 * @param lpszBuffer Long pointer to the buffer that receives the null-terminated string that
 *   contains the resulting canonicalized URL.
 * @param lpdwBufferLength Long pointer to the length, in bytes, of the lpszBuffer buffer. If the
 *   function succeeds, this parameter receives the length of the lpszBuffer buffer-the length does
 *   not include the terminating null. If the function fails, this parameter receives the required
 *   length, in bytes, of the lpszBuffer buffer-the required length includes the terminating null.
 * @param dwFlags Specifies control canonicalization. Can be one of the following values: Value
 *   Description ICU_BROWSER_MODE Does not encode or decode characters after "#" or "?", and does not
 *   remove trailing white space after "?". If this value is not specified, the entire URL is encoded,
 *   and trailing white space is removed. ICU_DECODE Converts all %XX sequences to characters,
 *   including escape sequences, before the URL is parsed. ICU_ENCODE_SPACES_ONLY Encodes spaces only.
 *   ICU_NO_ENCODE Does not convert unsafe characters to escape sequences. ICU_NO_META Does not remove
 *   meta sequences (such as "." and "..") from the URL. If no flags are specified (dwFlags = 0), the
 *   function converts all unsafe characters and meta sequences (such as \.,\ .., and \...) to escape
 *   sequences.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError. Possible error values for GetLastError are described in the following table. Value
 *   Meaning ERROR_BAD_PATHNAME The URL could not be canonicalized. ERROR_INSUFFICIENT_BUFFER
 *   Canonicalized URL is too large to fit in the buffer provided. The *lpdwBufferLength parameter is
 *   set to the size, in bytes, of the buffer required to hold the resultant, canonicalized URL.
 *   ERROR_INTERNET_INVALID_URL The format of the URL is invalid. ERROR_INVALID_PARAMETER Bad string,
 *   buffer, buffer size, or flags parameter.
 *
 * InternetCanonicalizeUrl always encodes by default, even if the ICU_DECODE flag has been
 * specified. To decode without re-encoding, use ICU_DECODE | ICU_NO_ENCODE. If the ICU_DECODE flag
 * is used without ICU_NO_ENCODE, the URL is decoded before being parsed; unsafe characters then are
 * re-encoded after parsing. This function will handle arbitrary protocol schemes, but to do so it
 * must make inferences from the unsafe character set.
 *
 * The application calling InternetCanonicalizeUrl should track the usage of this function on a
 * particular URL. If unsafe characters in a URL have been converted to escape sequences, using
 * InternetCanonicalizeUrl again on the URL (with no flags) will cause the escape sequences to be
 * converted to another escape sequence. For example, a blank space in a URL would be converted to
 * the escape sequence "%20". Calling InternetCanonicalizeUrl again on the URL would cause the
 * escape sequence "%20" to be converted to the escape sequence "%2520", because the "%" sign is an
 * unsafe character that is reserved for escape sequences and is replaced by the function with the
 * escape sequence "%25".
 */
#define InternetCanonicalizeUrl  InternetCanonicalizeUrlA
#endif // !UNICODE

/**
 * This function combines a base and relative URL into a single URL. The resultant URL is
 * canonicalized.
 *
 * @param lpszBaseUrl Long pointer to the null-terminated string that contains the base URL to be
 *   combined.
 * @param lpszRelativeUrl Long pointer to the null-terminated string that contains the relative URL
 *   to be combined.
 * @param lpszBuffer Long pointer to a buffer that receives the null-terminated string that contains
 *   the resulting URL.
 * @param lpdwBufferLength Long pointer to the size, in bytes, of the lpszBuffer buffer. If the
 *   function succeeds, this parameter receives the length, in characters, of the resultant combined
 *   URL-the length does not include the terminating null character. If the function fails, this
 *   parameter receives the length, in bytes, of the required buffer-the length includes the
 *   terminating null character.
 * @param dwFlags Specifies the operation of the function. It is one of the following values: Value
 *   Description ICU_BROWSER_MODE Does not encode or decode characters after "#" or "?", and does not
 *   remove trailing white space after "?". If this value is not specified, the entire URL is encoded
 *   and trailing white space is removed. ICU_DECODE Converts all %XX sequences to characters,
 *   including escape sequences, before the URL is parsed. ICU_ENCODE_SPACES_ONLY Encodes spaces only.
 *   ICU_NO_ENCODE Does not convert unsafe characters to escape sequences. ICU_NO_META Does not remove
 *   meta sequences (such as "." and "..") from the URL.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError. Possible error values for GetLastError are described in the following table. Value
 *   Description ERROR_BAD_PATHNAME The URLs could not be combined. ERROR_INSUFFICIENT_BUFFER The
 *   buffer supplied to the function was insufficient or NULL. The DWORD indicated by the
 *   lpdwBufferLength parameter will contain the number of bytes required to hold the resultant,
 *   combined URL. ERROR_INTERNET_INVALID_URL The format of the URL is invalid.
 *   ERROR_INVALID_PARAMETER Bad string, buffer, buffer size, or flags parameter.
 */
INTERNETAPI
BOOL
WINAPI
InternetCombineUrlA(
    IN LPCSTR lpszBaseUrl,
    IN LPCSTR lpszRelativeUrl,
    OUT LPSTR lpszBuffer,
    IN OUT LPDWORD lpdwBufferLength,
    IN DWORD dwFlags
    );
/**
 * This function combines a base and relative URL into a single URL. The resultant URL is
 * canonicalized.
 *
 * @param lpszBaseUrl Long pointer to the null-terminated string that contains the base URL to be
 *   combined.
 * @param lpszRelativeUrl Long pointer to the null-terminated string that contains the relative URL
 *   to be combined.
 * @param lpszBuffer Long pointer to a buffer that receives the null-terminated string that contains
 *   the resulting URL.
 * @param lpdwBufferLength Long pointer to the size, in bytes, of the lpszBuffer buffer. If the
 *   function succeeds, this parameter receives the length, in characters, of the resultant combined
 *   URL-the length does not include the terminating null character. If the function fails, this
 *   parameter receives the length, in bytes, of the required buffer-the length includes the
 *   terminating null character.
 * @param dwFlags Specifies the operation of the function. It is one of the following values: Value
 *   Description ICU_BROWSER_MODE Does not encode or decode characters after "#" or "?", and does not
 *   remove trailing white space after "?". If this value is not specified, the entire URL is encoded
 *   and trailing white space is removed. ICU_DECODE Converts all %XX sequences to characters,
 *   including escape sequences, before the URL is parsed. ICU_ENCODE_SPACES_ONLY Encodes spaces only.
 *   ICU_NO_ENCODE Does not convert unsafe characters to escape sequences. ICU_NO_META Does not remove
 *   meta sequences (such as "." and "..") from the URL.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError. Possible error values for GetLastError are described in the following table. Value
 *   Description ERROR_BAD_PATHNAME The URLs could not be combined. ERROR_INSUFFICIENT_BUFFER The
 *   buffer supplied to the function was insufficient or NULL. The DWORD indicated by the
 *   lpdwBufferLength parameter will contain the number of bytes required to hold the resultant,
 *   combined URL. ERROR_INTERNET_INVALID_URL The format of the URL is invalid.
 *   ERROR_INVALID_PARAMETER Bad string, buffer, buffer size, or flags parameter.
 */
INTERNETAPI
BOOL
WINAPI
InternetCombineUrlW(
    IN LPCWSTR lpszBaseUrl,
    IN LPCWSTR lpszRelativeUrl,
    OUT LPWSTR lpszBuffer,
    IN OUT LPDWORD lpdwBufferLength,
    IN DWORD dwFlags
    );
#ifdef UNICODE
/**
 * This function combines a base and relative URL into a single URL. The resultant URL is
 * canonicalized.
 *
 * @param lpszBaseUrl Long pointer to the null-terminated string that contains the base URL to be
 *   combined.
 * @param lpszRelativeUrl Long pointer to the null-terminated string that contains the relative URL
 *   to be combined.
 * @param lpszBuffer Long pointer to a buffer that receives the null-terminated string that contains
 *   the resulting URL.
 * @param lpdwBufferLength Long pointer to the size, in bytes, of the lpszBuffer buffer. If the
 *   function succeeds, this parameter receives the length, in characters, of the resultant combined
 *   URL-the length does not include the terminating null character. If the function fails, this
 *   parameter receives the length, in bytes, of the required buffer-the length includes the
 *   terminating null character.
 * @param dwFlags Specifies the operation of the function. It is one of the following values: Value
 *   Description ICU_BROWSER_MODE Does not encode or decode characters after "#" or "?", and does not
 *   remove trailing white space after "?". If this value is not specified, the entire URL is encoded
 *   and trailing white space is removed. ICU_DECODE Converts all %XX sequences to characters,
 *   including escape sequences, before the URL is parsed. ICU_ENCODE_SPACES_ONLY Encodes spaces only.
 *   ICU_NO_ENCODE Does not convert unsafe characters to escape sequences. ICU_NO_META Does not remove
 *   meta sequences (such as "." and "..") from the URL.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError. Possible error values for GetLastError are described in the following table. Value
 *   Description ERROR_BAD_PATHNAME The URLs could not be combined. ERROR_INSUFFICIENT_BUFFER The
 *   buffer supplied to the function was insufficient or NULL. The DWORD indicated by the
 *   lpdwBufferLength parameter will contain the number of bytes required to hold the resultant,
 *   combined URL. ERROR_INTERNET_INVALID_URL The format of the URL is invalid.
 *   ERROR_INVALID_PARAMETER Bad string, buffer, buffer size, or flags parameter.
 */
#define InternetCombineUrl  InternetCombineUrlW
#else
/**
 * This function combines a base and relative URL into a single URL. The resultant URL is
 * canonicalized.
 *
 * @param lpszBaseUrl Long pointer to the null-terminated string that contains the base URL to be
 *   combined.
 * @param lpszRelativeUrl Long pointer to the null-terminated string that contains the relative URL
 *   to be combined.
 * @param lpszBuffer Long pointer to a buffer that receives the null-terminated string that contains
 *   the resulting URL.
 * @param lpdwBufferLength Long pointer to the size, in bytes, of the lpszBuffer buffer. If the
 *   function succeeds, this parameter receives the length, in characters, of the resultant combined
 *   URL-the length does not include the terminating null character. If the function fails, this
 *   parameter receives the length, in bytes, of the required buffer-the length includes the
 *   terminating null character.
 * @param dwFlags Specifies the operation of the function. It is one of the following values: Value
 *   Description ICU_BROWSER_MODE Does not encode or decode characters after "#" or "?", and does not
 *   remove trailing white space after "?". If this value is not specified, the entire URL is encoded
 *   and trailing white space is removed. ICU_DECODE Converts all %XX sequences to characters,
 *   including escape sequences, before the URL is parsed. ICU_ENCODE_SPACES_ONLY Encodes spaces only.
 *   ICU_NO_ENCODE Does not convert unsafe characters to escape sequences. ICU_NO_META Does not remove
 *   meta sequences (such as "." and "..") from the URL.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError. Possible error values for GetLastError are described in the following table. Value
 *   Description ERROR_BAD_PATHNAME The URLs could not be combined. ERROR_INSUFFICIENT_BUFFER The
 *   buffer supplied to the function was insufficient or NULL. The DWORD indicated by the
 *   lpdwBufferLength parameter will contain the number of bytes required to hold the resultant,
 *   combined URL. ERROR_INTERNET_INVALID_URL The format of the URL is invalid.
 *   ERROR_INVALID_PARAMETER Bad string, buffer, buffer size, or flags parameter.
 */
#define InternetCombineUrl  InternetCombineUrlA
#endif // !UNICODE

//
// flags for InternetCrackUrl() and InternetCreateUrl()
//

#define ICU_ESCAPE      0x80000000  // (un)escape URL characters
#define ICU_USERNAME    0x40000000  // use internal username & password

//
// flags for InternetCanonicalizeUrl() and InternetCombineUrl()
//

#define ICU_NO_ENCODE   0x20000000  // Don't convert unsafe characters to escape sequence
#define ICU_DECODE      0x10000000  // Convert %XX escape sequences to characters
#define ICU_NO_META     0x08000000  // Don't convert .. etc. meta path sequences
#define ICU_ENCODE_SPACES_ONLY 0x04000000  // Encode spaces only
#define ICU_BROWSER_MODE 0x02000000 // Special encode/decode rules for browser

/**
 * This function initializes an application's use of the Windows CE Internet functions.
 *
 * @param lpszAgent Long pointer to a null-terminated string that contains the name of the
 *   application or entity calling the Internet functions (for example, Microsoft Internet Explorer).
 *   This name is used as the user agent in the HTTP protocol.
 * @param dwAccessType Specifies the type of access required. It is one of the following values:
 *   Value Description INTERNET_OPEN_TYPE_DIRECT Resolves all host names locally.
 *   INTERNET_OPEN_TYPE_PRECONFIG Retrieves the proxy or direct configuration from the registry.
 *   INTERNET_OPEN_TYPE_PRECONFIG_WITH_NO_AUTOPROXY Retrieves the proxy or direct configuration from
 *   the registry and prevents the use of a startup JScript or Internet Setup (INS) file.
 *   INTERNET_OPEN_TYPE_PROXY Passes requests to the proxy unless a proxy bypass list is supplied and
 *   the name to be resolved bypasses the proxy. In this case, the function uses
 *   INTERNET_OPEN_TYPE_DIRECT.
 * @param lpszProxyName Long pointer to a null-terminated string that contains the name of the proxy
 *   server (or servers) to use if proxy access was specified. If this parameter is NULL, the function
 *   reads proxy information from the registry. Do not use an empty string, because InternetOpen will
 *   use it as the proxy name. The Win32 Internet functions only recognize CERN type proxies (HTTP
 *   only) and the TIS FTP gateway (FTP only). If Microsoft Internet Explorer is installed, the Win32
 *   Internet functions also support SOCKS proxies. FTP requests can be made through a CERN type proxy
 *   either by changing them to an HTTP request or by using InternetOpenUrl.
 * @param lpszProxyBypass Long pointer to a null-terminated string that contains an optional list of
 *   host names or IP addresses, or both, that should not be routed through the proxy. The list can
 *   contain wildcards. Do not use an empty string, because InternetOpen will use it as the proxy
 *   bypass list. If this parameter specifies the "<local>" macro as the only entry, the function
 *   bypasses any host name that does not contain a period. If this parameter is NULL, the function
 *   reads the bypass list from the registry.
 * @param dwFlags Specifies various options affecting the behavior of the function. It can be a
 *   combination of these values: INTERNET_FLAG_ASYNC INTERNET_FLAG_FROM_CACHE INTERNET_FLAG_OFFLINE
 *
 * @return A valid handle, which the application passes on to subsequent Win32 Internet functions,
 *   indicates success. NULL indicates failure. To get extended error information, call GetLastError.
 *
 * InternetOpen is the first Win32 Internet function called by an application. It tells the Internet
 * DLL to initialize internal data structures and prepare for future calls from the application.
 * When the application finishes using the Internet functions, it should call InternetCloseHandle to
 * free the handle and any associated resources.
 *
 * The application can make any number of calls to InternetOpen, although a single call is normally
 * sufficient. The application might need to have separate behaviors defined for each InternetOpen
 * instance, such as different proxy servers configured for each.
 */
INTERNETAPI
HINTERNET
WINAPI
InternetOpenA(
    IN LPCSTR lpszAgent,
    IN DWORD dwAccessType,
    IN LPCSTR lpszProxy OPTIONAL,
    IN LPCSTR lpszProxyBypass OPTIONAL,
    IN DWORD dwFlags
    );
/**
 * This function initializes an application's use of the Windows CE Internet functions.
 *
 * @param lpszAgent Long pointer to a null-terminated string that contains the name of the
 *   application or entity calling the Internet functions (for example, Microsoft Internet Explorer).
 *   This name is used as the user agent in the HTTP protocol.
 * @param dwAccessType Specifies the type of access required. It is one of the following values:
 *   Value Description INTERNET_OPEN_TYPE_DIRECT Resolves all host names locally.
 *   INTERNET_OPEN_TYPE_PRECONFIG Retrieves the proxy or direct configuration from the registry.
 *   INTERNET_OPEN_TYPE_PRECONFIG_WITH_NO_AUTOPROXY Retrieves the proxy or direct configuration from
 *   the registry and prevents the use of a startup JScript or Internet Setup (INS) file.
 *   INTERNET_OPEN_TYPE_PROXY Passes requests to the proxy unless a proxy bypass list is supplied and
 *   the name to be resolved bypasses the proxy. In this case, the function uses
 *   INTERNET_OPEN_TYPE_DIRECT.
 * @param lpszProxyName Long pointer to a null-terminated string that contains the name of the proxy
 *   server (or servers) to use if proxy access was specified. If this parameter is NULL, the function
 *   reads proxy information from the registry. Do not use an empty string, because InternetOpen will
 *   use it as the proxy name. The Win32 Internet functions only recognize CERN type proxies (HTTP
 *   only) and the TIS FTP gateway (FTP only). If Microsoft Internet Explorer is installed, the Win32
 *   Internet functions also support SOCKS proxies. FTP requests can be made through a CERN type proxy
 *   either by changing them to an HTTP request or by using InternetOpenUrl.
 * @param lpszProxyBypass Long pointer to a null-terminated string that contains an optional list of
 *   host names or IP addresses, or both, that should not be routed through the proxy. The list can
 *   contain wildcards. Do not use an empty string, because InternetOpen will use it as the proxy
 *   bypass list. If this parameter specifies the "<local>" macro as the only entry, the function
 *   bypasses any host name that does not contain a period. If this parameter is NULL, the function
 *   reads the bypass list from the registry.
 * @param dwFlags Specifies various options affecting the behavior of the function. It can be a
 *   combination of these values: INTERNET_FLAG_ASYNC INTERNET_FLAG_FROM_CACHE INTERNET_FLAG_OFFLINE
 *
 * @return A valid handle, which the application passes on to subsequent Win32 Internet functions,
 *   indicates success. NULL indicates failure. To get extended error information, call GetLastError.
 *
 * InternetOpen is the first Win32 Internet function called by an application. It tells the Internet
 * DLL to initialize internal data structures and prepare for future calls from the application.
 * When the application finishes using the Internet functions, it should call InternetCloseHandle to
 * free the handle and any associated resources.
 *
 * The application can make any number of calls to InternetOpen, although a single call is normally
 * sufficient. The application might need to have separate behaviors defined for each InternetOpen
 * instance, such as different proxy servers configured for each.
 */
INTERNETAPI
HINTERNET
WINAPI
InternetOpenW(
    IN LPCWSTR lpszAgent,
    IN DWORD dwAccessType,
    IN LPCWSTR lpszProxy OPTIONAL,
    IN LPCWSTR lpszProxyBypass OPTIONAL,
    IN DWORD dwFlags
    );
#ifdef UNICODE
/**
 * This function initializes an application's use of the Windows CE Internet functions.
 *
 * @param lpszAgent Long pointer to a null-terminated string that contains the name of the
 *   application or entity calling the Internet functions (for example, Microsoft Internet Explorer).
 *   This name is used as the user agent in the HTTP protocol.
 * @param dwAccessType Specifies the type of access required. It is one of the following values:
 *   Value Description INTERNET_OPEN_TYPE_DIRECT Resolves all host names locally.
 *   INTERNET_OPEN_TYPE_PRECONFIG Retrieves the proxy or direct configuration from the registry.
 *   INTERNET_OPEN_TYPE_PRECONFIG_WITH_NO_AUTOPROXY Retrieves the proxy or direct configuration from
 *   the registry and prevents the use of a startup JScript or Internet Setup (INS) file.
 *   INTERNET_OPEN_TYPE_PROXY Passes requests to the proxy unless a proxy bypass list is supplied and
 *   the name to be resolved bypasses the proxy. In this case, the function uses
 *   INTERNET_OPEN_TYPE_DIRECT.
 * @param lpszProxyName Long pointer to a null-terminated string that contains the name of the proxy
 *   server (or servers) to use if proxy access was specified. If this parameter is NULL, the function
 *   reads proxy information from the registry. Do not use an empty string, because InternetOpen will
 *   use it as the proxy name. The Win32 Internet functions only recognize CERN type proxies (HTTP
 *   only) and the TIS FTP gateway (FTP only). If Microsoft Internet Explorer is installed, the Win32
 *   Internet functions also support SOCKS proxies. FTP requests can be made through a CERN type proxy
 *   either by changing them to an HTTP request or by using InternetOpenUrl.
 * @param lpszProxyBypass Long pointer to a null-terminated string that contains an optional list of
 *   host names or IP addresses, or both, that should not be routed through the proxy. The list can
 *   contain wildcards. Do not use an empty string, because InternetOpen will use it as the proxy
 *   bypass list. If this parameter specifies the "<local>" macro as the only entry, the function
 *   bypasses any host name that does not contain a period. If this parameter is NULL, the function
 *   reads the bypass list from the registry.
 * @param dwFlags Specifies various options affecting the behavior of the function. It can be a
 *   combination of these values: INTERNET_FLAG_ASYNC INTERNET_FLAG_FROM_CACHE INTERNET_FLAG_OFFLINE
 *
 * @return A valid handle, which the application passes on to subsequent Win32 Internet functions,
 *   indicates success. NULL indicates failure. To get extended error information, call GetLastError.
 *
 * InternetOpen is the first Win32 Internet function called by an application. It tells the Internet
 * DLL to initialize internal data structures and prepare for future calls from the application.
 * When the application finishes using the Internet functions, it should call InternetCloseHandle to
 * free the handle and any associated resources.
 *
 * The application can make any number of calls to InternetOpen, although a single call is normally
 * sufficient. The application might need to have separate behaviors defined for each InternetOpen
 * instance, such as different proxy servers configured for each.
 */
#define InternetOpen  InternetOpenW
#else
/**
 * This function initializes an application's use of the Windows CE Internet functions.
 *
 * @param lpszAgent Long pointer to a null-terminated string that contains the name of the
 *   application or entity calling the Internet functions (for example, Microsoft Internet Explorer).
 *   This name is used as the user agent in the HTTP protocol.
 * @param dwAccessType Specifies the type of access required. It is one of the following values:
 *   Value Description INTERNET_OPEN_TYPE_DIRECT Resolves all host names locally.
 *   INTERNET_OPEN_TYPE_PRECONFIG Retrieves the proxy or direct configuration from the registry.
 *   INTERNET_OPEN_TYPE_PRECONFIG_WITH_NO_AUTOPROXY Retrieves the proxy or direct configuration from
 *   the registry and prevents the use of a startup JScript or Internet Setup (INS) file.
 *   INTERNET_OPEN_TYPE_PROXY Passes requests to the proxy unless a proxy bypass list is supplied and
 *   the name to be resolved bypasses the proxy. In this case, the function uses
 *   INTERNET_OPEN_TYPE_DIRECT.
 * @param lpszProxyName Long pointer to a null-terminated string that contains the name of the proxy
 *   server (or servers) to use if proxy access was specified. If this parameter is NULL, the function
 *   reads proxy information from the registry. Do not use an empty string, because InternetOpen will
 *   use it as the proxy name. The Win32 Internet functions only recognize CERN type proxies (HTTP
 *   only) and the TIS FTP gateway (FTP only). If Microsoft Internet Explorer is installed, the Win32
 *   Internet functions also support SOCKS proxies. FTP requests can be made through a CERN type proxy
 *   either by changing them to an HTTP request or by using InternetOpenUrl.
 * @param lpszProxyBypass Long pointer to a null-terminated string that contains an optional list of
 *   host names or IP addresses, or both, that should not be routed through the proxy. The list can
 *   contain wildcards. Do not use an empty string, because InternetOpen will use it as the proxy
 *   bypass list. If this parameter specifies the "<local>" macro as the only entry, the function
 *   bypasses any host name that does not contain a period. If this parameter is NULL, the function
 *   reads the bypass list from the registry.
 * @param dwFlags Specifies various options affecting the behavior of the function. It can be a
 *   combination of these values: INTERNET_FLAG_ASYNC INTERNET_FLAG_FROM_CACHE INTERNET_FLAG_OFFLINE
 *
 * @return A valid handle, which the application passes on to subsequent Win32 Internet functions,
 *   indicates success. NULL indicates failure. To get extended error information, call GetLastError.
 *
 * InternetOpen is the first Win32 Internet function called by an application. It tells the Internet
 * DLL to initialize internal data structures and prepare for future calls from the application.
 * When the application finishes using the Internet functions, it should call InternetCloseHandle to
 * free the handle and any associated resources.
 *
 * The application can make any number of calls to InternetOpen, although a single call is normally
 * sufficient. The application might need to have separate behaviors defined for each InternetOpen
 * instance, such as different proxy servers configured for each.
 */
#define InternetOpen  InternetOpenA
#endif // !UNICODE

//
// access types for InternetOpen()
//

#define INTERNET_OPEN_TYPE_PRECONFIG    0   // use registry configuration
#define INTERNET_OPEN_TYPE_DIRECT       1   // direct to net
#define INTERNET_OPEN_TYPE_PROXY        3   // via named proxy

#define PRE_CONFIG_INTERNET_ACCESS  INTERNET_OPEN_TYPE_PRECONFIG
#define LOCAL_INTERNET_ACCESS       INTERNET_OPEN_TYPE_DIRECT
#define GATEWAY_INTERNET_ACCESS     2   // Internet via gateway
#define CERN_PROXY_INTERNET_ACCESS  INTERNET_OPEN_TYPE_PROXY

/**
 * This function closes a single Internet handle or a subtree of Internet handles.
 *
 * @param hInternet Valid Internet handle to be closed.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError.
 *
 * The function terminates any pending operations on the handle and discards any outstanding data.
 * If a thread is blocking a call to Wininet.dll, another thread in the application can call
 * InternetCloseHandle on the Internet handle being used by the first thread to cancel the operation
 * and unblock the first thread.
 *
 * If there is a status callback registered for the handle being closed and the handle was created
 * with a non-NULL context value, an INTERNET_STATUS_HANDLE_CLOSING callback will be made. This
 * indication will be the last callback made from a handle and indicates that the handle is being
 * destroyed.
 *
 * If asynchronous requests are pending for the handle or any of its child handles, the handle
 * cannot be closed immediately, but it will be invalidated. Any new requests attempted using the
 * handle will return with an ERROR_INVALID_HANDLE notification. The asynchronous requests will
 * complete with INTERNET_STATUS_REQUEST_COMPLETE. Applications must be prepared to receive any
 * INTERNET_STATUS_REQUEST_COMPLETE indications on the handle before the final
 * INTERNET_STATUS_HANDLE_CLOSING indication is made, which indicates that the handle is completely
 * closed.
 *
 * An application can call GetLastError to determine if requests are pending. If GetLastError
 * returns ERROR_IO_PENDING, there were outstanding requests when the handle was closed.
 */
INTERNETAPI
BOOL
WINAPI
InternetCloseHandle(
    IN HINTERNET hInternet
    );

/**
 * This function opens an FTP or HTTP session for a specified site.
 *
 * @param hInternet Handle to the current Internet session. The handle must have been returned by a
 *   previous call to InternetOpen.
 * @param lpszServerName Long pointer to a null-terminated string that contains the host name of an
 *   Internet server. Alternately, the string can contain the IP number of the site in ASCII
 *   dotted-decimal format (for example, 11.0.1.45).
 * @param nServerPort Number of the TCP/IP port on the server to connect to. It is one of the
 *   following values. These flags set only the port that will be used. The service is set by the
 *   value of dwService. Value Description INTERNET_DEFAULT_FTP_PORT Uses the default port for FTP
 *   servers (port 21). INTERNET_DEFAULT_HTTP_PORT Uses the default port for HTTP servers (port 80).
 *   INTERNET_DEFAULT_HTTPS_PORT Uses the default port for HTTPS servers (port 443).
 *   INTERNET_DEFAULT_SOCKS_PORT Uses the default port for SOCKS firewall servers (port 1080).
 *   INTERNET_INVALID_PORT_NUMBER Uses the default port for the service specified by dwService.
 * @param lpszUserName Long pointer to a null-terminated string that contains the name of the user
 *   to log on. If this parameter is NULL, the function uses an appropriate default, except for HTTP;
 *   a NULL parameter in HTTP causes the server to return an error. For the FTP protocol, the default
 *   is "anonymous".
 * @param lpszPassword Long pointer to a null-terminated string that contains the password to use to
 *   log on. If both lpszPassword and lpszUserName are NULL, the function uses the default "anonymous"
 *   password. In the case of FTP, the default password is the user's e-mail name. If lpszPassword is
 *   NULL, but lpszUserName is not NULL, the function uses a blank password. The behavior for the four
 *   possible settings of lpszUserName and lpszPassword is described in the following table.
 *   lpszUserName lpszPassword User name sent to FTP server Password sent to FTP server NULL NULL
 *   "anonymous" User's e-mail name Non-NULL string NULL lpszUserName "" NULL Non-NULL string ERROR
 *   ERROR Non-NULL string Non-NULL string lpszUserName lpszPassword
 * @param dwService Specifies the type of service to access. It is one of the following values:
 *   Value Description INTERNET_SERVICE_FTP FTP service. INTERNET_SERVICE_HTTP HTTP service.
 * @param dwFlags Flags specific to the service used. When the value of dwService is
 *   INTERNET_SERVICE_FTP, INTERNET_FLAG_PASSIVE causes the application to use passive FTP semantics.
 * @param dwContext Specifies the application-defined value that is used to identify the application
 *   context for the returned handle in callbacks.
 *
 * @return A valid handle to the FTP or HTTP session if the connection indicates success. NULL
 *   indicates failure. To get extended error information, call GetLastError. An application can also
 *   use InternetGetLastResponseInfo to determine why access to the service was denied.
 *
 * The InternetConnect function is required before communicating with any Internet service.
 *
 * Having a connect function for all protocols, even those that do not use persistent connections,
 * lets an application communicate common information about several requests by using a single
 * function call. In addition, this allows for future versions of Internet protocols that do not
 * require a connection to be established for every client request.
 *
 * For FTP sites, InternetConnect actually establishes a connection with the server.
 *
 * For maximum efficiency, applications using the HTTP protocols should try to minimize calls to
 * InternetConnect and avoid calling this function for every transaction requested by the user. One
 * way to accomplish this is to keep a small cache of handles returned from InternetConnect; when
 * the user makes a request to a previously accessed server, that session handle is still available.
 *
 * An application that needs to display multiline text information sent by an FTP server can use
 * InternetGetLastResponseInfo to retrieve the text.
 *
 * For FTP connections, if lpszUsername is NULL, InternetConnect sends the string "anonymous" as the
 * user name. If lpszPassword is NULL, InternetConnect attempts to use the user's e-mail name as the
 * password.
 *
 * To close the handle returned from InternetConnect, the application should call
 * InternetCloseHandle. This function disconnects the client from the server and frees all resources
 * associated with the connection.
 */
INTERNETAPI
HINTERNET
WINAPI
InternetConnectA(
    IN HINTERNET hInternet,
    IN LPCSTR lpszServerName,
    IN INTERNET_PORT nServerPort,
    IN LPCSTR lpszUserName OPTIONAL,
    IN LPCSTR lpszPassword OPTIONAL,
    IN DWORD dwService,
    IN DWORD dwFlags,
    IN DWORD dwContext
    );
/**
 * This function opens an FTP or HTTP session for a specified site.
 *
 * @param hInternet Handle to the current Internet session. The handle must have been returned by a
 *   previous call to InternetOpen.
 * @param lpszServerName Long pointer to a null-terminated string that contains the host name of an
 *   Internet server. Alternately, the string can contain the IP number of the site in ASCII
 *   dotted-decimal format (for example, 11.0.1.45).
 * @param nServerPort Number of the TCP/IP port on the server to connect to. It is one of the
 *   following values. These flags set only the port that will be used. The service is set by the
 *   value of dwService. Value Description INTERNET_DEFAULT_FTP_PORT Uses the default port for FTP
 *   servers (port 21). INTERNET_DEFAULT_HTTP_PORT Uses the default port for HTTP servers (port 80).
 *   INTERNET_DEFAULT_HTTPS_PORT Uses the default port for HTTPS servers (port 443).
 *   INTERNET_DEFAULT_SOCKS_PORT Uses the default port for SOCKS firewall servers (port 1080).
 *   INTERNET_INVALID_PORT_NUMBER Uses the default port for the service specified by dwService.
 * @param lpszUserName Long pointer to a null-terminated string that contains the name of the user
 *   to log on. If this parameter is NULL, the function uses an appropriate default, except for HTTP;
 *   a NULL parameter in HTTP causes the server to return an error. For the FTP protocol, the default
 *   is "anonymous".
 * @param lpszPassword Long pointer to a null-terminated string that contains the password to use to
 *   log on. If both lpszPassword and lpszUserName are NULL, the function uses the default "anonymous"
 *   password. In the case of FTP, the default password is the user's e-mail name. If lpszPassword is
 *   NULL, but lpszUserName is not NULL, the function uses a blank password. The behavior for the four
 *   possible settings of lpszUserName and lpszPassword is described in the following table.
 *   lpszUserName lpszPassword User name sent to FTP server Password sent to FTP server NULL NULL
 *   "anonymous" User's e-mail name Non-NULL string NULL lpszUserName "" NULL Non-NULL string ERROR
 *   ERROR Non-NULL string Non-NULL string lpszUserName lpszPassword
 * @param dwService Specifies the type of service to access. It is one of the following values:
 *   Value Description INTERNET_SERVICE_FTP FTP service. INTERNET_SERVICE_HTTP HTTP service.
 * @param dwFlags Flags specific to the service used. When the value of dwService is
 *   INTERNET_SERVICE_FTP, INTERNET_FLAG_PASSIVE causes the application to use passive FTP semantics.
 * @param dwContext Specifies the application-defined value that is used to identify the application
 *   context for the returned handle in callbacks.
 *
 * @return A valid handle to the FTP or HTTP session if the connection indicates success. NULL
 *   indicates failure. To get extended error information, call GetLastError. An application can also
 *   use InternetGetLastResponseInfo to determine why access to the service was denied.
 *
 * The InternetConnect function is required before communicating with any Internet service.
 *
 * Having a connect function for all protocols, even those that do not use persistent connections,
 * lets an application communicate common information about several requests by using a single
 * function call. In addition, this allows for future versions of Internet protocols that do not
 * require a connection to be established for every client request.
 *
 * For FTP sites, InternetConnect actually establishes a connection with the server.
 *
 * For maximum efficiency, applications using the HTTP protocols should try to minimize calls to
 * InternetConnect and avoid calling this function for every transaction requested by the user. One
 * way to accomplish this is to keep a small cache of handles returned from InternetConnect; when
 * the user makes a request to a previously accessed server, that session handle is still available.
 *
 * An application that needs to display multiline text information sent by an FTP server can use
 * InternetGetLastResponseInfo to retrieve the text.
 *
 * For FTP connections, if lpszUsername is NULL, InternetConnect sends the string "anonymous" as the
 * user name. If lpszPassword is NULL, InternetConnect attempts to use the user's e-mail name as the
 * password.
 *
 * To close the handle returned from InternetConnect, the application should call
 * InternetCloseHandle. This function disconnects the client from the server and frees all resources
 * associated with the connection.
 */
INTERNETAPI
HINTERNET
WINAPI
InternetConnectW(
    IN HINTERNET hInternet,
    IN LPCWSTR lpszServerName,
    IN INTERNET_PORT nServerPort,
    IN LPCWSTR lpszUserName OPTIONAL,
    IN LPCWSTR lpszPassword OPTIONAL,
    IN DWORD dwService,
    IN DWORD dwFlags,
    IN DWORD dwContext
    );
#ifdef UNICODE
/**
 * This function opens an FTP or HTTP session for a specified site.
 *
 * @param hInternet Handle to the current Internet session. The handle must have been returned by a
 *   previous call to InternetOpen.
 * @param lpszServerName Long pointer to a null-terminated string that contains the host name of an
 *   Internet server. Alternately, the string can contain the IP number of the site in ASCII
 *   dotted-decimal format (for example, 11.0.1.45).
 * @param nServerPort Number of the TCP/IP port on the server to connect to. It is one of the
 *   following values. These flags set only the port that will be used. The service is set by the
 *   value of dwService. Value Description INTERNET_DEFAULT_FTP_PORT Uses the default port for FTP
 *   servers (port 21). INTERNET_DEFAULT_HTTP_PORT Uses the default port for HTTP servers (port 80).
 *   INTERNET_DEFAULT_HTTPS_PORT Uses the default port for HTTPS servers (port 443).
 *   INTERNET_DEFAULT_SOCKS_PORT Uses the default port for SOCKS firewall servers (port 1080).
 *   INTERNET_INVALID_PORT_NUMBER Uses the default port for the service specified by dwService.
 * @param lpszUserName Long pointer to a null-terminated string that contains the name of the user
 *   to log on. If this parameter is NULL, the function uses an appropriate default, except for HTTP;
 *   a NULL parameter in HTTP causes the server to return an error. For the FTP protocol, the default
 *   is "anonymous".
 * @param lpszPassword Long pointer to a null-terminated string that contains the password to use to
 *   log on. If both lpszPassword and lpszUserName are NULL, the function uses the default "anonymous"
 *   password. In the case of FTP, the default password is the user's e-mail name. If lpszPassword is
 *   NULL, but lpszUserName is not NULL, the function uses a blank password. The behavior for the four
 *   possible settings of lpszUserName and lpszPassword is described in the following table.
 *   lpszUserName lpszPassword User name sent to FTP server Password sent to FTP server NULL NULL
 *   "anonymous" User's e-mail name Non-NULL string NULL lpszUserName "" NULL Non-NULL string ERROR
 *   ERROR Non-NULL string Non-NULL string lpszUserName lpszPassword
 * @param dwService Specifies the type of service to access. It is one of the following values:
 *   Value Description INTERNET_SERVICE_FTP FTP service. INTERNET_SERVICE_HTTP HTTP service.
 * @param dwFlags Flags specific to the service used. When the value of dwService is
 *   INTERNET_SERVICE_FTP, INTERNET_FLAG_PASSIVE causes the application to use passive FTP semantics.
 * @param dwContext Specifies the application-defined value that is used to identify the application
 *   context for the returned handle in callbacks.
 *
 * @return A valid handle to the FTP or HTTP session if the connection indicates success. NULL
 *   indicates failure. To get extended error information, call GetLastError. An application can also
 *   use InternetGetLastResponseInfo to determine why access to the service was denied.
 *
 * The InternetConnect function is required before communicating with any Internet service.
 *
 * Having a connect function for all protocols, even those that do not use persistent connections,
 * lets an application communicate common information about several requests by using a single
 * function call. In addition, this allows for future versions of Internet protocols that do not
 * require a connection to be established for every client request.
 *
 * For FTP sites, InternetConnect actually establishes a connection with the server.
 *
 * For maximum efficiency, applications using the HTTP protocols should try to minimize calls to
 * InternetConnect and avoid calling this function for every transaction requested by the user. One
 * way to accomplish this is to keep a small cache of handles returned from InternetConnect; when
 * the user makes a request to a previously accessed server, that session handle is still available.
 *
 * An application that needs to display multiline text information sent by an FTP server can use
 * InternetGetLastResponseInfo to retrieve the text.
 *
 * For FTP connections, if lpszUsername is NULL, InternetConnect sends the string "anonymous" as the
 * user name. If lpszPassword is NULL, InternetConnect attempts to use the user's e-mail name as the
 * password.
 *
 * To close the handle returned from InternetConnect, the application should call
 * InternetCloseHandle. This function disconnects the client from the server and frees all resources
 * associated with the connection.
 */
#define InternetConnect  InternetConnectW
#else
/**
 * This function opens an FTP or HTTP session for a specified site.
 *
 * @param hInternet Handle to the current Internet session. The handle must have been returned by a
 *   previous call to InternetOpen.
 * @param lpszServerName Long pointer to a null-terminated string that contains the host name of an
 *   Internet server. Alternately, the string can contain the IP number of the site in ASCII
 *   dotted-decimal format (for example, 11.0.1.45).
 * @param nServerPort Number of the TCP/IP port on the server to connect to. It is one of the
 *   following values. These flags set only the port that will be used. The service is set by the
 *   value of dwService. Value Description INTERNET_DEFAULT_FTP_PORT Uses the default port for FTP
 *   servers (port 21). INTERNET_DEFAULT_HTTP_PORT Uses the default port for HTTP servers (port 80).
 *   INTERNET_DEFAULT_HTTPS_PORT Uses the default port for HTTPS servers (port 443).
 *   INTERNET_DEFAULT_SOCKS_PORT Uses the default port for SOCKS firewall servers (port 1080).
 *   INTERNET_INVALID_PORT_NUMBER Uses the default port for the service specified by dwService.
 * @param lpszUserName Long pointer to a null-terminated string that contains the name of the user
 *   to log on. If this parameter is NULL, the function uses an appropriate default, except for HTTP;
 *   a NULL parameter in HTTP causes the server to return an error. For the FTP protocol, the default
 *   is "anonymous".
 * @param lpszPassword Long pointer to a null-terminated string that contains the password to use to
 *   log on. If both lpszPassword and lpszUserName are NULL, the function uses the default "anonymous"
 *   password. In the case of FTP, the default password is the user's e-mail name. If lpszPassword is
 *   NULL, but lpszUserName is not NULL, the function uses a blank password. The behavior for the four
 *   possible settings of lpszUserName and lpszPassword is described in the following table.
 *   lpszUserName lpszPassword User name sent to FTP server Password sent to FTP server NULL NULL
 *   "anonymous" User's e-mail name Non-NULL string NULL lpszUserName "" NULL Non-NULL string ERROR
 *   ERROR Non-NULL string Non-NULL string lpszUserName lpszPassword
 * @param dwService Specifies the type of service to access. It is one of the following values:
 *   Value Description INTERNET_SERVICE_FTP FTP service. INTERNET_SERVICE_HTTP HTTP service.
 * @param dwFlags Flags specific to the service used. When the value of dwService is
 *   INTERNET_SERVICE_FTP, INTERNET_FLAG_PASSIVE causes the application to use passive FTP semantics.
 * @param dwContext Specifies the application-defined value that is used to identify the application
 *   context for the returned handle in callbacks.
 *
 * @return A valid handle to the FTP or HTTP session if the connection indicates success. NULL
 *   indicates failure. To get extended error information, call GetLastError. An application can also
 *   use InternetGetLastResponseInfo to determine why access to the service was denied.
 *
 * The InternetConnect function is required before communicating with any Internet service.
 *
 * Having a connect function for all protocols, even those that do not use persistent connections,
 * lets an application communicate common information about several requests by using a single
 * function call. In addition, this allows for future versions of Internet protocols that do not
 * require a connection to be established for every client request.
 *
 * For FTP sites, InternetConnect actually establishes a connection with the server.
 *
 * For maximum efficiency, applications using the HTTP protocols should try to minimize calls to
 * InternetConnect and avoid calling this function for every transaction requested by the user. One
 * way to accomplish this is to keep a small cache of handles returned from InternetConnect; when
 * the user makes a request to a previously accessed server, that session handle is still available.
 *
 * An application that needs to display multiline text information sent by an FTP server can use
 * InternetGetLastResponseInfo to retrieve the text.
 *
 * For FTP connections, if lpszUsername is NULL, InternetConnect sends the string "anonymous" as the
 * user name. If lpszPassword is NULL, InternetConnect attempts to use the user's e-mail name as the
 * password.
 *
 * To close the handle returned from InternetConnect, the application should call
 * InternetCloseHandle. This function disconnects the client from the server and frees all resources
 * associated with the connection.
 */
#define InternetConnect  InternetConnectA
#endif // !UNICODE

//
// service types for InternetConnect()
//

#define INTERNET_SERVICE_FTP    1
#define INTERNET_SERVICE_HTTP   3

/**
 * This function begins reading a complete FTP or HTTP Universal Resource Locator (URL). For a
 * relative URL and a base URL separated by blank spaces, InternetCanonicalizeUrl must be invoked
 * first.
 *
 * @param hInternetSession Handle to the current Internet session. The handle must have been
 *   returned by a previous call to InternetOpen.
 * @param lpszUrl Long pointer to a null-terminated string that contains the URL to begin reading.
 *   Only URLs beginning with ftp:, http:, or https: are supported.
 * @param lpszHeaders Long pointer to a null-terminated string that contains the headers to be sent
 *   to the HTTP server. (For more information, see the description of the lpszHeaders parameter in
 *   the HttpSendRequest function.)
 * @param dwHeadersLength Specifies the length, in characters, of the additional headers. If this
 *   parameter is -1L and lpszHeaders is not NULL, lpszHeaders is assumed to be zero-terminated
 *   (ASCIIZ) and the length is calculated.
 * @param dwFlags Specifies a bitmask of action flags. It is one of the following values: Value
 *   Description INTERNET_FLAG_DONT_CACHE Does not cache the data, either locally or in any gateways.
 *   Identical to the preferred value INTERNET_FLAG_NO_CACHE_WRITE. INTERNET_FLAG_EXISTING_CONNECT If
 *   possible, reuses the existing connections to the server for new requests generated by
 *   InternetOpenUrl instead of creating a new session for each request. This flag is useful only for
 *   FTP connections, since FTP is the only protocol that typically performs multiple operations
 *   during the same session. The Win32 Internet API caches a single connection handle for each
 *   HINTERNET handle generated by InternetOpen. INTERNET_FLAG-HYPERLINK Forces a reload if there was
 *   no Expires time and no Last-Modified time returned from the server when determining whether to
 *   reload the item from the network. INTERNET_FLAG_IGNORE_CERT_CN_INVALID Disables Win32 Internet
 *   function checking of SSL/PCT-based certificates that are returned from the server against the
 *   host name given in the request. Win32 Internet functions use a simple check against certificates
 *   by comparing for matching host names and simple wildcarding rules for HTTP requests.
 *   INTERNET_FLAG_IGNORE_CERT_DATE_INVALID Disables Win32 Internet function checking of SSL/PCT-based
 *   certificates for proper validity dates for HTTP requests. INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP
 *   Disables the ability of the Win32 Internet functions to detect this special type of redirect.
 *   When this flag is used, Win32 Internet functions transparently allow redirects from HTTPS to HTTP
 *   URLs. INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTPS Disables the ability of the Win32 Internet functions
 *   to detect this special type of redirect. When this flag is used, Win32 Internet functions
 *   transparently allow redirects from HTTP to HTTPS URLs. INTERNET_FLAG_KEEP_CONNECTION Uses
 *   keep-alive semantics, if available, for the connection for HTTP requests. This flag is required
 *   for Microsoft Network (MSN), NT LAN Manager (NTLM), and other types of authentication.
 *   INTERNET_FLAG_MAKE_PERSISTENT No longer supported. INTERNET_FLAG_MUST_CACHE_REQUEST Causes a
 *   temporary file to be created if the file cannot be cached. Identical to the preferred value
 *   INTERNET_FLAG_NEED_FILE. INTERNET_FLAG_NEED_FILE Causes a temporary file to be created if the
 *   file cannot be cached. INTERNET_FLAG_NO_AUTH Does not attempt authentication automatically for
 *   HTTP requests. INTERNET_FLAG_NO_AUTO_REDIRECT Does not automatically handle redirection for HTTP
 *   requests only. INTERNET_FLAG_NO_CACHE_WRITE Does not cache the data, either locally or in any
 *   gateways. INTERNET_FLAG_NO_COOKIES Does not automatically add cookie headers to requests, and
 *   does not automatically add returned cookies to the cookie database for HTTP requests.
 *   INTERNET_FLAG_NO_UI Disables the cookie dialog box. INTERNET_FLAG_PASSIVE Uses passive FTP
 *   semantics for FTP files and directories. INTERNET_FLAG_RAW_DATA Returns the data as a
 *   WIN32_FIND_DATA structure when retrieving FTP directory information. If this flag is not
 *   specified or if the call was made through a CERN proxy, InternetOpenUrl returns an HTML version
 *   of the directory. INTERNET_FLAG_PRAGMA_NOCACHE Forces the request to be resolved by the origin
 *   server, even if a cached copy exists on the proxy. INTERNET_FLAG_READ_PREFETCH This flag is
 *   currently disabled. INTERNET_FLAG_RELOAD Gets the data from the wire even if it is locally
 *   cached. INTERNET_FLAG_RESYNCHRONIZE Reloads HTTP resources if the resource has been modified
 *   since the last time it was downloaded. All FTP resources are reloaded. INTERNET_FLAG_SECURE
 *   Requests secure transactions on the wire with SSL or PCT. This flag applies to HTTP requests
 *   only.
 * @param dwContext Application-defined value that is passed, along with the returned handle, to any
 *   callback functions.
 *
 * @return A valid handle to the FTP or HTTP URL indicates that the connection is successfully
 *   established. NULL indicates that the connection fails. To get extended error information, call
 *   GetLastError. To determine why access to the service was denied, call
 *   InternetGetLastResponseInfo.
 *
 * This is a general function that an application can use to retrieve data over any of the protocols
 * that the Win32 Internet functions support. This function is particularly useful when the
 * application does not need to access the particulars of a protocol, but only requires the data
 * corresponding to a URL. The InternetOpenUrl function parses the URL string, establishes a
 * connection to the server, and prepares to download the data identified by the URL. The
 * application can then use InternetReadFile (for files) or InternetFindNextFile (for directories)
 * to retrieve the URL data. It is not necessary to call InternetConnect before InternetOpenUrl.
 *
 * Use InternetCloseHandle to close the handle returned from InternetOpenUrl. However, note that
 * closing the handle before all the URL data has been read results in the connection being
 * terminated.
 */
INTERNETAPI
HINTERNET
WINAPI
InternetOpenUrlA(
    IN HINTERNET hInternet,
    IN LPCSTR lpszUrl,
    IN LPCSTR lpszHeaders OPTIONAL,
    IN DWORD dwHeadersLength,
    IN DWORD dwFlags,
    IN DWORD dwContext
    );
/**
 * This function begins reading a complete FTP or HTTP Universal Resource Locator (URL). For a
 * relative URL and a base URL separated by blank spaces, InternetCanonicalizeUrl must be invoked
 * first.
 *
 * @param hInternetSession Handle to the current Internet session. The handle must have been
 *   returned by a previous call to InternetOpen.
 * @param lpszUrl Long pointer to a null-terminated string that contains the URL to begin reading.
 *   Only URLs beginning with ftp:, http:, or https: are supported.
 * @param lpszHeaders Long pointer to a null-terminated string that contains the headers to be sent
 *   to the HTTP server. (For more information, see the description of the lpszHeaders parameter in
 *   the HttpSendRequest function.)
 * @param dwHeadersLength Specifies the length, in characters, of the additional headers. If this
 *   parameter is -1L and lpszHeaders is not NULL, lpszHeaders is assumed to be zero-terminated
 *   (ASCIIZ) and the length is calculated.
 * @param dwFlags Specifies a bitmask of action flags. It is one of the following values: Value
 *   Description INTERNET_FLAG_DONT_CACHE Does not cache the data, either locally or in any gateways.
 *   Identical to the preferred value INTERNET_FLAG_NO_CACHE_WRITE. INTERNET_FLAG_EXISTING_CONNECT If
 *   possible, reuses the existing connections to the server for new requests generated by
 *   InternetOpenUrl instead of creating a new session for each request. This flag is useful only for
 *   FTP connections, since FTP is the only protocol that typically performs multiple operations
 *   during the same session. The Win32 Internet API caches a single connection handle for each
 *   HINTERNET handle generated by InternetOpen. INTERNET_FLAG-HYPERLINK Forces a reload if there was
 *   no Expires time and no Last-Modified time returned from the server when determining whether to
 *   reload the item from the network. INTERNET_FLAG_IGNORE_CERT_CN_INVALID Disables Win32 Internet
 *   function checking of SSL/PCT-based certificates that are returned from the server against the
 *   host name given in the request. Win32 Internet functions use a simple check against certificates
 *   by comparing for matching host names and simple wildcarding rules for HTTP requests.
 *   INTERNET_FLAG_IGNORE_CERT_DATE_INVALID Disables Win32 Internet function checking of SSL/PCT-based
 *   certificates for proper validity dates for HTTP requests. INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP
 *   Disables the ability of the Win32 Internet functions to detect this special type of redirect.
 *   When this flag is used, Win32 Internet functions transparently allow redirects from HTTPS to HTTP
 *   URLs. INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTPS Disables the ability of the Win32 Internet functions
 *   to detect this special type of redirect. When this flag is used, Win32 Internet functions
 *   transparently allow redirects from HTTP to HTTPS URLs. INTERNET_FLAG_KEEP_CONNECTION Uses
 *   keep-alive semantics, if available, for the connection for HTTP requests. This flag is required
 *   for Microsoft Network (MSN), NT LAN Manager (NTLM), and other types of authentication.
 *   INTERNET_FLAG_MAKE_PERSISTENT No longer supported. INTERNET_FLAG_MUST_CACHE_REQUEST Causes a
 *   temporary file to be created if the file cannot be cached. Identical to the preferred value
 *   INTERNET_FLAG_NEED_FILE. INTERNET_FLAG_NEED_FILE Causes a temporary file to be created if the
 *   file cannot be cached. INTERNET_FLAG_NO_AUTH Does not attempt authentication automatically for
 *   HTTP requests. INTERNET_FLAG_NO_AUTO_REDIRECT Does not automatically handle redirection for HTTP
 *   requests only. INTERNET_FLAG_NO_CACHE_WRITE Does not cache the data, either locally or in any
 *   gateways. INTERNET_FLAG_NO_COOKIES Does not automatically add cookie headers to requests, and
 *   does not automatically add returned cookies to the cookie database for HTTP requests.
 *   INTERNET_FLAG_NO_UI Disables the cookie dialog box. INTERNET_FLAG_PASSIVE Uses passive FTP
 *   semantics for FTP files and directories. INTERNET_FLAG_RAW_DATA Returns the data as a
 *   WIN32_FIND_DATA structure when retrieving FTP directory information. If this flag is not
 *   specified or if the call was made through a CERN proxy, InternetOpenUrl returns an HTML version
 *   of the directory. INTERNET_FLAG_PRAGMA_NOCACHE Forces the request to be resolved by the origin
 *   server, even if a cached copy exists on the proxy. INTERNET_FLAG_READ_PREFETCH This flag is
 *   currently disabled. INTERNET_FLAG_RELOAD Gets the data from the wire even if it is locally
 *   cached. INTERNET_FLAG_RESYNCHRONIZE Reloads HTTP resources if the resource has been modified
 *   since the last time it was downloaded. All FTP resources are reloaded. INTERNET_FLAG_SECURE
 *   Requests secure transactions on the wire with SSL or PCT. This flag applies to HTTP requests
 *   only.
 * @param dwContext Application-defined value that is passed, along with the returned handle, to any
 *   callback functions.
 *
 * @return A valid handle to the FTP or HTTP URL indicates that the connection is successfully
 *   established. NULL indicates that the connection fails. To get extended error information, call
 *   GetLastError. To determine why access to the service was denied, call
 *   InternetGetLastResponseInfo.
 *
 * This is a general function that an application can use to retrieve data over any of the protocols
 * that the Win32 Internet functions support. This function is particularly useful when the
 * application does not need to access the particulars of a protocol, but only requires the data
 * corresponding to a URL. The InternetOpenUrl function parses the URL string, establishes a
 * connection to the server, and prepares to download the data identified by the URL. The
 * application can then use InternetReadFile (for files) or InternetFindNextFile (for directories)
 * to retrieve the URL data. It is not necessary to call InternetConnect before InternetOpenUrl.
 *
 * Use InternetCloseHandle to close the handle returned from InternetOpenUrl. However, note that
 * closing the handle before all the URL data has been read results in the connection being
 * terminated.
 */
INTERNETAPI
HINTERNET
WINAPI
InternetOpenUrlW(
    IN HINTERNET hInternet,
    IN LPCWSTR lpszUrl,
    IN LPCWSTR lpszHeaders OPTIONAL,
    IN DWORD dwHeadersLength,
    IN DWORD dwFlags,
    IN DWORD dwContext
    );
#ifdef UNICODE
/**
 * This function begins reading a complete FTP or HTTP Universal Resource Locator (URL). For a
 * relative URL and a base URL separated by blank spaces, InternetCanonicalizeUrl must be invoked
 * first.
 *
 * @param hInternetSession Handle to the current Internet session. The handle must have been
 *   returned by a previous call to InternetOpen.
 * @param lpszUrl Long pointer to a null-terminated string that contains the URL to begin reading.
 *   Only URLs beginning with ftp:, http:, or https: are supported.
 * @param lpszHeaders Long pointer to a null-terminated string that contains the headers to be sent
 *   to the HTTP server. (For more information, see the description of the lpszHeaders parameter in
 *   the HttpSendRequest function.)
 * @param dwHeadersLength Specifies the length, in characters, of the additional headers. If this
 *   parameter is -1L and lpszHeaders is not NULL, lpszHeaders is assumed to be zero-terminated
 *   (ASCIIZ) and the length is calculated.
 * @param dwFlags Specifies a bitmask of action flags. It is one of the following values: Value
 *   Description INTERNET_FLAG_DONT_CACHE Does not cache the data, either locally or in any gateways.
 *   Identical to the preferred value INTERNET_FLAG_NO_CACHE_WRITE. INTERNET_FLAG_EXISTING_CONNECT If
 *   possible, reuses the existing connections to the server for new requests generated by
 *   InternetOpenUrl instead of creating a new session for each request. This flag is useful only for
 *   FTP connections, since FTP is the only protocol that typically performs multiple operations
 *   during the same session. The Win32 Internet API caches a single connection handle for each
 *   HINTERNET handle generated by InternetOpen. INTERNET_FLAG-HYPERLINK Forces a reload if there was
 *   no Expires time and no Last-Modified time returned from the server when determining whether to
 *   reload the item from the network. INTERNET_FLAG_IGNORE_CERT_CN_INVALID Disables Win32 Internet
 *   function checking of SSL/PCT-based certificates that are returned from the server against the
 *   host name given in the request. Win32 Internet functions use a simple check against certificates
 *   by comparing for matching host names and simple wildcarding rules for HTTP requests.
 *   INTERNET_FLAG_IGNORE_CERT_DATE_INVALID Disables Win32 Internet function checking of SSL/PCT-based
 *   certificates for proper validity dates for HTTP requests. INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP
 *   Disables the ability of the Win32 Internet functions to detect this special type of redirect.
 *   When this flag is used, Win32 Internet functions transparently allow redirects from HTTPS to HTTP
 *   URLs. INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTPS Disables the ability of the Win32 Internet functions
 *   to detect this special type of redirect. When this flag is used, Win32 Internet functions
 *   transparently allow redirects from HTTP to HTTPS URLs. INTERNET_FLAG_KEEP_CONNECTION Uses
 *   keep-alive semantics, if available, for the connection for HTTP requests. This flag is required
 *   for Microsoft Network (MSN), NT LAN Manager (NTLM), and other types of authentication.
 *   INTERNET_FLAG_MAKE_PERSISTENT No longer supported. INTERNET_FLAG_MUST_CACHE_REQUEST Causes a
 *   temporary file to be created if the file cannot be cached. Identical to the preferred value
 *   INTERNET_FLAG_NEED_FILE. INTERNET_FLAG_NEED_FILE Causes a temporary file to be created if the
 *   file cannot be cached. INTERNET_FLAG_NO_AUTH Does not attempt authentication automatically for
 *   HTTP requests. INTERNET_FLAG_NO_AUTO_REDIRECT Does not automatically handle redirection for HTTP
 *   requests only. INTERNET_FLAG_NO_CACHE_WRITE Does not cache the data, either locally or in any
 *   gateways. INTERNET_FLAG_NO_COOKIES Does not automatically add cookie headers to requests, and
 *   does not automatically add returned cookies to the cookie database for HTTP requests.
 *   INTERNET_FLAG_NO_UI Disables the cookie dialog box. INTERNET_FLAG_PASSIVE Uses passive FTP
 *   semantics for FTP files and directories. INTERNET_FLAG_RAW_DATA Returns the data as a
 *   WIN32_FIND_DATA structure when retrieving FTP directory information. If this flag is not
 *   specified or if the call was made through a CERN proxy, InternetOpenUrl returns an HTML version
 *   of the directory. INTERNET_FLAG_PRAGMA_NOCACHE Forces the request to be resolved by the origin
 *   server, even if a cached copy exists on the proxy. INTERNET_FLAG_READ_PREFETCH This flag is
 *   currently disabled. INTERNET_FLAG_RELOAD Gets the data from the wire even if it is locally
 *   cached. INTERNET_FLAG_RESYNCHRONIZE Reloads HTTP resources if the resource has been modified
 *   since the last time it was downloaded. All FTP resources are reloaded. INTERNET_FLAG_SECURE
 *   Requests secure transactions on the wire with SSL or PCT. This flag applies to HTTP requests
 *   only.
 * @param dwContext Application-defined value that is passed, along with the returned handle, to any
 *   callback functions.
 *
 * @return A valid handle to the FTP or HTTP URL indicates that the connection is successfully
 *   established. NULL indicates that the connection fails. To get extended error information, call
 *   GetLastError. To determine why access to the service was denied, call
 *   InternetGetLastResponseInfo.
 *
 * This is a general function that an application can use to retrieve data over any of the protocols
 * that the Win32 Internet functions support. This function is particularly useful when the
 * application does not need to access the particulars of a protocol, but only requires the data
 * corresponding to a URL. The InternetOpenUrl function parses the URL string, establishes a
 * connection to the server, and prepares to download the data identified by the URL. The
 * application can then use InternetReadFile (for files) or InternetFindNextFile (for directories)
 * to retrieve the URL data. It is not necessary to call InternetConnect before InternetOpenUrl.
 *
 * Use InternetCloseHandle to close the handle returned from InternetOpenUrl. However, note that
 * closing the handle before all the URL data has been read results in the connection being
 * terminated.
 */
#define InternetOpenUrl  InternetOpenUrlW
#else
/**
 * This function begins reading a complete FTP or HTTP Universal Resource Locator (URL). For a
 * relative URL and a base URL separated by blank spaces, InternetCanonicalizeUrl must be invoked
 * first.
 *
 * @param hInternetSession Handle to the current Internet session. The handle must have been
 *   returned by a previous call to InternetOpen.
 * @param lpszUrl Long pointer to a null-terminated string that contains the URL to begin reading.
 *   Only URLs beginning with ftp:, http:, or https: are supported.
 * @param lpszHeaders Long pointer to a null-terminated string that contains the headers to be sent
 *   to the HTTP server. (For more information, see the description of the lpszHeaders parameter in
 *   the HttpSendRequest function.)
 * @param dwHeadersLength Specifies the length, in characters, of the additional headers. If this
 *   parameter is -1L and lpszHeaders is not NULL, lpszHeaders is assumed to be zero-terminated
 *   (ASCIIZ) and the length is calculated.
 * @param dwFlags Specifies a bitmask of action flags. It is one of the following values: Value
 *   Description INTERNET_FLAG_DONT_CACHE Does not cache the data, either locally or in any gateways.
 *   Identical to the preferred value INTERNET_FLAG_NO_CACHE_WRITE. INTERNET_FLAG_EXISTING_CONNECT If
 *   possible, reuses the existing connections to the server for new requests generated by
 *   InternetOpenUrl instead of creating a new session for each request. This flag is useful only for
 *   FTP connections, since FTP is the only protocol that typically performs multiple operations
 *   during the same session. The Win32 Internet API caches a single connection handle for each
 *   HINTERNET handle generated by InternetOpen. INTERNET_FLAG-HYPERLINK Forces a reload if there was
 *   no Expires time and no Last-Modified time returned from the server when determining whether to
 *   reload the item from the network. INTERNET_FLAG_IGNORE_CERT_CN_INVALID Disables Win32 Internet
 *   function checking of SSL/PCT-based certificates that are returned from the server against the
 *   host name given in the request. Win32 Internet functions use a simple check against certificates
 *   by comparing for matching host names and simple wildcarding rules for HTTP requests.
 *   INTERNET_FLAG_IGNORE_CERT_DATE_INVALID Disables Win32 Internet function checking of SSL/PCT-based
 *   certificates for proper validity dates for HTTP requests. INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP
 *   Disables the ability of the Win32 Internet functions to detect this special type of redirect.
 *   When this flag is used, Win32 Internet functions transparently allow redirects from HTTPS to HTTP
 *   URLs. INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTPS Disables the ability of the Win32 Internet functions
 *   to detect this special type of redirect. When this flag is used, Win32 Internet functions
 *   transparently allow redirects from HTTP to HTTPS URLs. INTERNET_FLAG_KEEP_CONNECTION Uses
 *   keep-alive semantics, if available, for the connection for HTTP requests. This flag is required
 *   for Microsoft Network (MSN), NT LAN Manager (NTLM), and other types of authentication.
 *   INTERNET_FLAG_MAKE_PERSISTENT No longer supported. INTERNET_FLAG_MUST_CACHE_REQUEST Causes a
 *   temporary file to be created if the file cannot be cached. Identical to the preferred value
 *   INTERNET_FLAG_NEED_FILE. INTERNET_FLAG_NEED_FILE Causes a temporary file to be created if the
 *   file cannot be cached. INTERNET_FLAG_NO_AUTH Does not attempt authentication automatically for
 *   HTTP requests. INTERNET_FLAG_NO_AUTO_REDIRECT Does not automatically handle redirection for HTTP
 *   requests only. INTERNET_FLAG_NO_CACHE_WRITE Does not cache the data, either locally or in any
 *   gateways. INTERNET_FLAG_NO_COOKIES Does not automatically add cookie headers to requests, and
 *   does not automatically add returned cookies to the cookie database for HTTP requests.
 *   INTERNET_FLAG_NO_UI Disables the cookie dialog box. INTERNET_FLAG_PASSIVE Uses passive FTP
 *   semantics for FTP files and directories. INTERNET_FLAG_RAW_DATA Returns the data as a
 *   WIN32_FIND_DATA structure when retrieving FTP directory information. If this flag is not
 *   specified or if the call was made through a CERN proxy, InternetOpenUrl returns an HTML version
 *   of the directory. INTERNET_FLAG_PRAGMA_NOCACHE Forces the request to be resolved by the origin
 *   server, even if a cached copy exists on the proxy. INTERNET_FLAG_READ_PREFETCH This flag is
 *   currently disabled. INTERNET_FLAG_RELOAD Gets the data from the wire even if it is locally
 *   cached. INTERNET_FLAG_RESYNCHRONIZE Reloads HTTP resources if the resource has been modified
 *   since the last time it was downloaded. All FTP resources are reloaded. INTERNET_FLAG_SECURE
 *   Requests secure transactions on the wire with SSL or PCT. This flag applies to HTTP requests
 *   only.
 * @param dwContext Application-defined value that is passed, along with the returned handle, to any
 *   callback functions.
 *
 * @return A valid handle to the FTP or HTTP URL indicates that the connection is successfully
 *   established. NULL indicates that the connection fails. To get extended error information, call
 *   GetLastError. To determine why access to the service was denied, call
 *   InternetGetLastResponseInfo.
 *
 * This is a general function that an application can use to retrieve data over any of the protocols
 * that the Win32 Internet functions support. This function is particularly useful when the
 * application does not need to access the particulars of a protocol, but only requires the data
 * corresponding to a URL. The InternetOpenUrl function parses the URL string, establishes a
 * connection to the server, and prepares to download the data identified by the URL. The
 * application can then use InternetReadFile (for files) or InternetFindNextFile (for directories)
 * to retrieve the URL data. It is not necessary to call InternetConnect before InternetOpenUrl.
 *
 * Use InternetCloseHandle to close the handle returned from InternetOpenUrl. However, note that
 * closing the handle before all the URL data has been read results in the connection being
 * terminated.
 */
#define InternetOpenUrl  InternetOpenUrlA
#endif // !UNICODE

/**
 * This function reads data from a handle opened by the FtpOpenFile, FtpFindFirstFile, or
 * HttpOpenRequest function.
 *
 * @param hFile Valid handle returned from a previous call to InternetOpenUrl, FtpOpenFile, r
 *   HttpOpenRequest.
 * @param lpBuffer Long pointer to a buffer that receives the data read.
 * @param dwNumberOfBytesToRead Specifies the number of bytes to read.
 * @param lpNumberOfBytesRead Long pointer to a variable that receives the number of bytes read.
 *   InternetReadFile sets this value to zero before doing any work or error checking.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError. An application can also use InternetGetLastResponseInfo when necessary.
 *
 * If the return value is TRUE and the number of bytes read is zero, the transfer has been completed
 * and there are no more bytes to read on the handle. This is analogous to reaching EOF in a local
 * file. Call InternetCloseHandle to free the connection to the server.
 *
 * The buffer pointed to by lpBuffer is not always filled by calls to InternetReadFile (sufficient
 * data might not have arrived from the server). When reading HTML data, for the first read posted,
 * the buffer must be large enough to hold the HTML headers. When reading HTML-encoded directory
 * entries, the buffer must be large enough to hold at least one complete entry.
 *
 * When the item being read is also being cached by a Win32 Internet function, the application must
 * ensure that a read is made for end-of-file so the cache file is committed correctly.
 *
 * This function always fulfills the user's request. If more data is requested than is available,
 * the function waits until enough data to complete the request is available. The only time that
 * less data is returned than requested is when the end of the file has been reached.
 *
 * This function can also be used to retrieve FTP directory listings as an HTML document on a handle
 * opened by InternetOpenUrl. The INTERNET_FLAG_RAW_DATA value must not have been specified in the
 * call to InternetOpenUrl.
 *
 * If the HINTERNET handle stored in hFile was created by HttpOpenRequest and sent by
 * HttpSendRequestEx, a call to HttpEndRequest must be made on the handle before InternetReadFile is
 * used.
 */
INTERNETAPI
BOOL
WINAPI
InternetReadFile(
    IN HINTERNET hFile,
    IN LPVOID lpBuffer,
    IN DWORD dwNumberOfBytesToRead,
    OUT LPDWORD lpdwNumberOfBytesRead
    );

/**
 * This function sets a file position for InternetReadFile. This is a synchronous call; however,
 * subsequent calls to InternetReadFile might block or return pending if the data is not available
 * from the cache and the server does not support random access.
 *
 * @param hFile [in] Valid HINTERNET handle returned from a previous call to InternetOpenUrl (on an
 *   HTTP or HTTPS URL) or HttpOpenRequest (using the GET or HEAD method and passed to HttpSendRequest
 *   or HttpSendRequestEx). This handle must not have been created with the INTERNET_FLAG_DONT_CACHE
 *   or INTERNET_FLAG_NO_CACHE_WRITE value set.
 * @param lDistanceToMove [in] Long integer value that contains the number of bytes to move the file
 *   pointer. A positive value moves the pointer forward in the file; a negative value moves it
 *   backward.
 * @param pReserved [in] Reserved. Must be set to NULL.
 * @param dwMoveMethod [in] Unsigned long integer value that indicates the starting point for the
 *   file pointer move. Can be one of the following values: Value Description FILE_BEGIN Starting
 *   point is zero or the beginning of the file. If FILE_BEGIN is specified, lDistanceToMove is
 *   interpreted as an unsigned location for the new file pointer. FILE_CURRENT Current value of the
 *   file pointer is the starting point. FILE_END Current end-of-file position is the starting point.
 *   This method fails if the content length is unknown.
 * @param dwContext Reserved. Must be set to zero.
 *
 * @return Returns the current file position if the function succeeds, or -1 otherwise.
 *
 * This function cannot be used once the end of file has been reached by InternetReadFile.
 *
 * For HINTERNET handles created by HttpOpenRequest and sent by HttpSendRequestEx, a call to
 * HttpEndRequest must be made on the handle before this function is used.
 *
 * This function cannot be used reliably if the content length is unknown, and with chunked
 * transfers.
 */
INTERNETAPI
DWORD
WINAPI
InternetSetFilePointer(
    IN HINTERNET hFile,
    IN LONG  lDistanceToMove,
    IN PVOID pReserved,
    IN DWORD dwMoveMethod,
    IN DWORD dwContext
    );

/**
 * This function writes data to an open Internet file.
 *
 * @param hFile [in] Valid HINTERNET handle returned from a previous call to FtpOpenFile or an
 *   HINTERNET handle sent by HttpSendRequestEx.
 * @param lpBuffer [in] Address of a buffer that contains the data to be written to the file.
 * @param dwNumberOfBytesToWrite [in] Unsigned long integer value that contains the number of bytes
 *   to write to the file.
 * @param lpdwNumberOfBytesWritten [out] Address of an unsigned long integer variable that receives
 *   the number of bytes written to the buffer. This function sets this value to zero before doing any
 *   work or error checking.
 *
 * @return Returns TRUE if successful, or FALSE otherwise.
 *
 * When the application is sending data, it must call InternetCloseHandle to end the data transfer.
 */
INTERNETAPI
BOOL
WINAPI
InternetWriteFile(
    IN HINTERNET hFile,
    IN LPCVOID lpBuffer,
    IN DWORD dwNumberOfBytesToWrite,
    OUT LPDWORD lpdwNumberOfBytesWritten
    );

/**
 * This function queries the amount of data available.
 *
 * @param hFile Valid Internet file handle, as returned by InternetOpenUrl, FtpOpenFile, or
 *   HttpOpenRequest.
 * @param lpdwNumberOfBytesAvailable Optional. Long pointer to a variable that receives the number
 *   of available bytes.
 * @param dwFlags Reserved; set to zero.
 * @param dwContext Reserved; set to zero.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError. If the function finds no matching files, GetLastError returns ERROR_NO_MORE_FILES.
 *
 * This function returns the number of bytes of data that are available to be read immediately by a
 * subsequent call to InternetReadFile. If there is currently no data available and the end of the
 * file has not been reached, the request waits until data becomes available. The amount of data
 * remaining will not be recalculated until all available data indicated by the call to
 * InternetQueryDataAvailable is read.
 *
 * For HINTERNET handles created by HttpOpenRequest and sent by HttpSendRequestEx, a call to
 * HttpEndRequest must be made on the handle before InternetQueryDataAvailable can be used.
 */
INTERNETAPI
BOOL
WINAPI
InternetQueryDataAvailable(
    IN HINTERNET hFile,
    OUT LPDWORD lpdwNumberOfBytesAvailable,
    IN DWORD dwFlags,
    IN DWORD dwContext
    );

/**
 * This function continues a file search from a previous call to FtpFindFirstFile.
 *
 * @param hFind Valid handle returned from FtpFindFirstFile or InternetOpenUrl (directories only).
 * @param lpvFindData Long void pointer to the buffer that receives information about the found file
 *   or directory. The format of the information placed in the buffer depends on the protocol in use.
 *   The FTP protocol returns a WIN32_FIND_DATA structure.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError. If the function finds no matching files, GetLastError returns ERROR_NO_MORE_FILES.
 *
 * This Windows CE Internet API supports the full features of the corresponding Win32 Internet
 * function for an internet handle returned by FtpFindFirstFile.
 */
INTERNETAPI
BOOL
WINAPI
InternetFindNextFileA(
    IN HINTERNET hFind,
    OUT LPVOID lpvFindData
    );
/**
 * This function continues a file search from a previous call to FtpFindFirstFile.
 *
 * @param hFind Valid handle returned from FtpFindFirstFile or InternetOpenUrl (directories only).
 * @param lpvFindData Long void pointer to the buffer that receives information about the found file
 *   or directory. The format of the information placed in the buffer depends on the protocol in use.
 *   The FTP protocol returns a WIN32_FIND_DATA structure.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError. If the function finds no matching files, GetLastError returns ERROR_NO_MORE_FILES.
 *
 * This Windows CE Internet API supports the full features of the corresponding Win32 Internet
 * function for an internet handle returned by FtpFindFirstFile.
 */
INTERNETAPI
BOOL
WINAPI
InternetFindNextFileW(
    IN HINTERNET hFind,
    OUT LPVOID lpvFindData
    );
#ifdef UNICODE
/**
 * This function continues a file search from a previous call to FtpFindFirstFile.
 *
 * @param hFind Valid handle returned from FtpFindFirstFile or InternetOpenUrl (directories only).
 * @param lpvFindData Long void pointer to the buffer that receives information about the found file
 *   or directory. The format of the information placed in the buffer depends on the protocol in use.
 *   The FTP protocol returns a WIN32_FIND_DATA structure.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError. If the function finds no matching files, GetLastError returns ERROR_NO_MORE_FILES.
 *
 * This Windows CE Internet API supports the full features of the corresponding Win32 Internet
 * function for an internet handle returned by FtpFindFirstFile.
 */
#define InternetFindNextFile  InternetFindNextFileW
#else
/**
 * This function continues a file search from a previous call to FtpFindFirstFile.
 *
 * @param hFind Valid handle returned from FtpFindFirstFile or InternetOpenUrl (directories only).
 * @param lpvFindData Long void pointer to the buffer that receives information about the found file
 *   or directory. The format of the information placed in the buffer depends on the protocol in use.
 *   The FTP protocol returns a WIN32_FIND_DATA structure.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError. If the function finds no matching files, GetLastError returns ERROR_NO_MORE_FILES.
 *
 * This Windows CE Internet API supports the full features of the corresponding Win32 Internet
 * function for an internet handle returned by FtpFindFirstFile.
 */
#define InternetFindNextFile  InternetFindNextFileA
#endif // !UNICODE

/**
 * This function queries an Internet option on the specified handle.
 *
 * @param hInternet Internet handle on which to query information.
 * @param dwOption Specifies the Internet option to query. Can be one of the Option Flags values.
 * @param lpBuffer Long pointer to a buffer that receives the option setting.
 * @param lpdwBufferLength Long pointer to a variable that contains the length of lpBuffer. When the
 *   function returns, the variable receives the length of the data placed into lpBuffer. If
 *   GetLastError returns ERROR_INSUFFICIENT_BUFFER, this parameter receives the number of bytes
 *   required to hold the created URL.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError.
 */
INTERNETAPI
BOOL
WINAPI
InternetQueryOptionA(
    IN HINTERNET hInternet OPTIONAL,
    IN DWORD dwOption,
    OUT LPVOID lpBuffer OPTIONAL,
    IN OUT LPDWORD lpdwBufferLength
    );
/**
 * This function queries an Internet option on the specified handle.
 *
 * @param hInternet Internet handle on which to query information.
 * @param dwOption Specifies the Internet option to query. Can be one of the Option Flags values.
 * @param lpBuffer Long pointer to a buffer that receives the option setting.
 * @param lpdwBufferLength Long pointer to a variable that contains the length of lpBuffer. When the
 *   function returns, the variable receives the length of the data placed into lpBuffer. If
 *   GetLastError returns ERROR_INSUFFICIENT_BUFFER, this parameter receives the number of bytes
 *   required to hold the created URL.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError.
 */
INTERNETAPI
BOOL
WINAPI
InternetQueryOptionW(
    IN HINTERNET hInternet OPTIONAL,
    IN DWORD dwOption,
    OUT LPVOID lpBuffer OPTIONAL,
    IN OUT LPDWORD lpdwBufferLength
    );
#ifdef UNICODE
/**
 * This function queries an Internet option on the specified handle.
 *
 * @param hInternet Internet handle on which to query information.
 * @param dwOption Specifies the Internet option to query. Can be one of the Option Flags values.
 * @param lpBuffer Long pointer to a buffer that receives the option setting.
 * @param lpdwBufferLength Long pointer to a variable that contains the length of lpBuffer. When the
 *   function returns, the variable receives the length of the data placed into lpBuffer. If
 *   GetLastError returns ERROR_INSUFFICIENT_BUFFER, this parameter receives the number of bytes
 *   required to hold the created URL.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError.
 */
#define InternetQueryOption  InternetQueryOptionW
#else
/**
 * This function queries an Internet option on the specified handle.
 *
 * @param hInternet Internet handle on which to query information.
 * @param dwOption Specifies the Internet option to query. Can be one of the Option Flags values.
 * @param lpBuffer Long pointer to a buffer that receives the option setting.
 * @param lpdwBufferLength Long pointer to a variable that contains the length of lpBuffer. When the
 *   function returns, the variable receives the length of the data placed into lpBuffer. If
 *   GetLastError returns ERROR_INSUFFICIENT_BUFFER, this parameter receives the number of bytes
 *   required to hold the created URL.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError.
 */
#define InternetQueryOption  InternetQueryOptionA
#endif // !UNICODE

/**
 * This function sets an internet option on the specified handle.
 *
 * @param hInternet Internet handle on which to set information.
 * @param dwOption Specifies the Internet option to set. Can be one of the Option Flags values.
 * @param lpBuffer Long pointer to a buffer that contains the option setting.
 * @param dwBufferLength Specifies the length of the lpBuffer buffer.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError.
 */
INTERNETAPI
BOOL
WINAPI
InternetSetOptionA(
    IN HINTERNET hInternet OPTIONAL,
    IN DWORD dwOption,
    IN LPVOID lpBuffer,
    IN DWORD dwBufferLength
    );
/**
 * This function sets an internet option on the specified handle.
 *
 * @param hInternet Internet handle on which to set information.
 * @param dwOption Specifies the Internet option to set. Can be one of the Option Flags values.
 * @param lpBuffer Long pointer to a buffer that contains the option setting.
 * @param dwBufferLength Specifies the length of the lpBuffer buffer.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError.
 */
INTERNETAPI
BOOL
WINAPI
InternetSetOptionW(
    IN HINTERNET hInternet OPTIONAL,
    IN DWORD dwOption,
    IN LPVOID lpBuffer,
    IN DWORD dwBufferLength
    );
#ifdef UNICODE
/**
 * This function sets an internet option on the specified handle.
 *
 * @param hInternet Internet handle on which to set information.
 * @param dwOption Specifies the Internet option to set. Can be one of the Option Flags values.
 * @param lpBuffer Long pointer to a buffer that contains the option setting.
 * @param dwBufferLength Specifies the length of the lpBuffer buffer.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError.
 */
#define InternetSetOption  InternetSetOptionW
#else
/**
 * This function sets an internet option on the specified handle.
 *
 * @param hInternet Internet handle on which to set information.
 * @param dwOption Specifies the Internet option to set. Can be one of the Option Flags values.
 * @param lpBuffer Long pointer to a buffer that contains the option setting.
 * @param dwBufferLength Specifies the length of the lpBuffer buffer.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError.
 */
#define InternetSetOption  InternetSetOptionA
#endif // !UNICODE

INTERNETAPI
BOOL
WINAPI
InternetSetOptionExA(
    IN HINTERNET hInternet OPTIONAL,
    IN DWORD dwOption,
    IN LPVOID lpBuffer,
    IN DWORD dwBufferLength,
    IN DWORD dwFlags
    );
INTERNETAPI
BOOL
WINAPI
InternetSetOptionExW(
    IN HINTERNET hInternet OPTIONAL,
    IN DWORD dwOption,
    IN LPVOID lpBuffer,
    IN DWORD dwBufferLength,
    IN DWORD dwFlags
    );
#ifdef UNICODE
#define InternetSetOptionEx  InternetSetOptionExW
#else
#define InternetSetOptionEx  InternetSetOptionExA
#endif // !UNICODE

//
// flags for InternetSetOptionEx()
//

#define ISO_GLOBAL      0x00000001  // modify option globally
#define ISO_REGISTRY    0x00000002  // write option to registry (where applicable)

#define ISO_VALID_FLAGS (ISO_GLOBAL | ISO_REGISTRY)

//
// options manifests for Internet{Query|Set}Option
//

#define INTERNET_OPTION_CALLBACK                1
#define INTERNET_OPTION_CONNECT_TIMEOUT         2
#define INTERNET_OPTION_CONNECT_RETRIES         3
#define INTERNET_OPTION_CONNECT_BACKOFF         4
#define INTERNET_OPTION_SEND_TIMEOUT            5
#define INTERNET_OPTION_CONTROL_SEND_TIMEOUT    INTERNET_OPTION_SEND_TIMEOUT
#define INTERNET_OPTION_RECEIVE_TIMEOUT         6
#define INTERNET_OPTION_CONTROL_RECEIVE_TIMEOUT INTERNET_OPTION_RECEIVE_TIMEOUT
#define INTERNET_OPTION_DATA_SEND_TIMEOUT       7
#define INTERNET_OPTION_DATA_RECEIVE_TIMEOUT    8
#define INTERNET_OPTION_HANDLE_TYPE             9
#define INTERNET_OPTION_CONTEXT_VALUE           10
#define INTERNET_OPTION_LISTEN_TIMEOUT          11
#define INTERNET_OPTION_READ_BUFFER_SIZE        12
#define INTERNET_OPTION_WRITE_BUFFER_SIZE       13

#define INTERNET_OPTION_ASYNC_ID                15
#define INTERNET_OPTION_ASYNC_PRIORITY          16

#define INTERNET_OPTION_PARENT_HANDLE           21
#define INTERNET_OPTION_KEEP_CONNECTION         22
#define INTERNET_OPTION_REQUEST_FLAGS           23
#define INTERNET_OPTION_EXTENDED_ERROR          24

#define INTERNET_OPTION_OFFLINE_MODE            26
#define INTERNET_OPTION_CACHE_STREAM_HANDLE     27
#define INTERNET_OPTION_USERNAME                28
#define INTERNET_OPTION_PASSWORD                29
#define INTERNET_OPTION_ASYNC                   30
#define INTERNET_OPTION_SECURITY_FLAGS          31
#define INTERNET_OPTION_SECURITY_CERTIFICATE_STRUCT    32
#define INTERNET_OPTION_DATAFILE_NAME           33
#define INTERNET_OPTION_URL                     34
#define INTERNET_OPTION_SECURITY_CERTIFICATE    35
#define INTERNET_OPTION_SECURITY_KEY_BITNESS    36
#define INTERNET_OPTION_REFRESH                 37
#define INTERNET_OPTION_PROXY                   38
#define INTERNET_OPTION_SETTINGS_CHANGED        39
#define INTERNET_OPTION_VERSION                 40
#define INTERNET_OPTION_USER_AGENT              41

#define INTERNET_FIRST_OPTION                   INTERNET_OPTION_CALLBACK
#define INTERNET_LAST_OPTION                    INTERNET_OPTION_USER_AGENT

//
// values for INTERNET_OPTION_PRIORITY
//

#define INTERNET_PRIORITY_FOREGROUND            1000

//
// handle types
//

#define INTERNET_HANDLE_TYPE_INTERNET           1
#define INTERNET_HANDLE_TYPE_CONNECT_FTP        2
#define INTERNET_HANDLE_TYPE_CONNECT_HTTP       4
#define INTERNET_HANDLE_TYPE_FTP_FIND           5
#define INTERNET_HANDLE_TYPE_FTP_FIND_HTML      6
#define INTERNET_HANDLE_TYPE_FTP_FILE           7
#define INTERNET_HANDLE_TYPE_FTP_FILE_HTML      8
#define INTERNET_HANDLE_TYPE_HTTP_REQUEST       13

//
// values for INTERNET_OPTION_SECURITY_FLAGS
//

#define SECURITY_FLAG_SECURE                    0x00000001 // can query only
#define SECURITY_FLAG_SSL                       0x00000002
#define SECURITY_FLAG_SSL3                      0x00000004
#define SECURITY_FLAG_PCT                       0x00000008
#define SECURITY_FLAG_PCT4                      0x00000010
#define SECURITY_FLAG_IETFSSL4                  0x00000020

#define SECURITY_FLAG_40BIT                     0x10000000
#define SECURITY_FLAG_128BIT                    0x20000000
#define SECURITY_FLAG_56BIT                     0x40000000
#define SECURITY_FLAG_UNKNOWNBIT                0x80000000
#define SECURITY_FLAG_NORMALBITNESS             SECURITY_FLAG_40BIT

#define SECURITY_FLAG_IGNORE_CERT_CN_INVALID    INTERNET_FLAG_IGNORE_CERT_CN_INVALID
#define SECURITY_FLAG_IGNORE_CERT_DATE_INVALID  INTERNET_FLAG_IGNORE_CERT_DATE_INVALID
#define SECURITY_FLAG_IGNORE_REDIRECT_TO_HTTPS  INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTPS
#define SECURITY_FLAG_IGNORE_REDIRECT_TO_HTTP   INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP

/**
 * This function retrieves the last Windows CE Internet function error description or server
 * response on the thread calling this function.
 *
 * @param lpdwError Long pointer to a variable that receives an error message pertaining to the
 *   operation that failed.
 * @param lpszBuffer Long pointer to a buffer that receives the null-terminated string that contains
 *   the error text.
 * @param lpdwBufferLength Long pointer to the size of the lpszBuffer buffer. When the function
 *   returns, this parameter contains the size of the string written to the buffer.
 *
 * @return TRUE indicates that the error text was successfully written to the buffer. FALSE
 *   indicates failure. To get extended error information, call GetLastError. If the buffer is too
 *   small to hold all the error text, GetLastError returns ERROR_INSUFFICIENT_BUFFER, and the
 *   lpdwBufferLength parameter contains the minimum buffer size required to return all the error
 *   text.
 *
 * The FTP protocol can return additional text information along with most errors. This extended
 * error information can be retrieved by using the InternetGetLastResponseInfo function whenever
 * GetLastError returns ERROR_INTERNET_EXTENDED_ERROR (occurring after an unsuccessful function
 * call).
 *
 * The buffer pointed to by lpszBuffer must be large enough to hold both the error string and a zero
 * terminator at the end of the string. However, note that the value returned in lpdwBufferLength
 * does not include the terminating zero.
 *
 * InternetGetLastResponseInfo can be called multiple times until another Win32 Internet function is
 * called on this thread. When another function is called, the internal buffer that is storing the
 * last response information is cleared.
 */
INTERNETAPI
BOOL
WINAPI
InternetGetLastResponseInfoA(
    OUT LPDWORD lpdwError,
    OUT LPSTR lpszBuffer OPTIONAL,
    IN OUT LPDWORD lpdwBufferLength
    );
/**
 * This function retrieves the last Windows CE Internet function error description or server
 * response on the thread calling this function.
 *
 * @param lpdwError Long pointer to a variable that receives an error message pertaining to the
 *   operation that failed.
 * @param lpszBuffer Long pointer to a buffer that receives the null-terminated string that contains
 *   the error text.
 * @param lpdwBufferLength Long pointer to the size of the lpszBuffer buffer. When the function
 *   returns, this parameter contains the size of the string written to the buffer.
 *
 * @return TRUE indicates that the error text was successfully written to the buffer. FALSE
 *   indicates failure. To get extended error information, call GetLastError. If the buffer is too
 *   small to hold all the error text, GetLastError returns ERROR_INSUFFICIENT_BUFFER, and the
 *   lpdwBufferLength parameter contains the minimum buffer size required to return all the error
 *   text.
 *
 * The FTP protocol can return additional text information along with most errors. This extended
 * error information can be retrieved by using the InternetGetLastResponseInfo function whenever
 * GetLastError returns ERROR_INTERNET_EXTENDED_ERROR (occurring after an unsuccessful function
 * call).
 *
 * The buffer pointed to by lpszBuffer must be large enough to hold both the error string and a zero
 * terminator at the end of the string. However, note that the value returned in lpdwBufferLength
 * does not include the terminating zero.
 *
 * InternetGetLastResponseInfo can be called multiple times until another Win32 Internet function is
 * called on this thread. When another function is called, the internal buffer that is storing the
 * last response information is cleared.
 */
INTERNETAPI
BOOL
WINAPI
InternetGetLastResponseInfoW(
    OUT LPDWORD lpdwError,
    OUT LPWSTR lpszBuffer OPTIONAL,
    IN OUT LPDWORD lpdwBufferLength
    );
#ifdef UNICODE
/**
 * This function retrieves the last Windows CE Internet function error description or server
 * response on the thread calling this function.
 *
 * @param lpdwError Long pointer to a variable that receives an error message pertaining to the
 *   operation that failed.
 * @param lpszBuffer Long pointer to a buffer that receives the null-terminated string that contains
 *   the error text.
 * @param lpdwBufferLength Long pointer to the size of the lpszBuffer buffer. When the function
 *   returns, this parameter contains the size of the string written to the buffer.
 *
 * @return TRUE indicates that the error text was successfully written to the buffer. FALSE
 *   indicates failure. To get extended error information, call GetLastError. If the buffer is too
 *   small to hold all the error text, GetLastError returns ERROR_INSUFFICIENT_BUFFER, and the
 *   lpdwBufferLength parameter contains the minimum buffer size required to return all the error
 *   text.
 *
 * The FTP protocol can return additional text information along with most errors. This extended
 * error information can be retrieved by using the InternetGetLastResponseInfo function whenever
 * GetLastError returns ERROR_INTERNET_EXTENDED_ERROR (occurring after an unsuccessful function
 * call).
 *
 * The buffer pointed to by lpszBuffer must be large enough to hold both the error string and a zero
 * terminator at the end of the string. However, note that the value returned in lpdwBufferLength
 * does not include the terminating zero.
 *
 * InternetGetLastResponseInfo can be called multiple times until another Win32 Internet function is
 * called on this thread. When another function is called, the internal buffer that is storing the
 * last response information is cleared.
 */
#define InternetGetLastResponseInfo  InternetGetLastResponseInfoW
#else
/**
 * This function retrieves the last Windows CE Internet function error description or server
 * response on the thread calling this function.
 *
 * @param lpdwError Long pointer to a variable that receives an error message pertaining to the
 *   operation that failed.
 * @param lpszBuffer Long pointer to a buffer that receives the null-terminated string that contains
 *   the error text.
 * @param lpdwBufferLength Long pointer to the size of the lpszBuffer buffer. When the function
 *   returns, this parameter contains the size of the string written to the buffer.
 *
 * @return TRUE indicates that the error text was successfully written to the buffer. FALSE
 *   indicates failure. To get extended error information, call GetLastError. If the buffer is too
 *   small to hold all the error text, GetLastError returns ERROR_INSUFFICIENT_BUFFER, and the
 *   lpdwBufferLength parameter contains the minimum buffer size required to return all the error
 *   text.
 *
 * The FTP protocol can return additional text information along with most errors. This extended
 * error information can be retrieved by using the InternetGetLastResponseInfo function whenever
 * GetLastError returns ERROR_INTERNET_EXTENDED_ERROR (occurring after an unsuccessful function
 * call).
 *
 * The buffer pointed to by lpszBuffer must be large enough to hold both the error string and a zero
 * terminator at the end of the string. However, note that the value returned in lpdwBufferLength
 * does not include the terminating zero.
 *
 * InternetGetLastResponseInfo can be called multiple times until another Win32 Internet function is
 * called on this thread. When another function is called, the internal buffer that is storing the
 * last response information is cleared.
 */
#define InternetGetLastResponseInfo  InternetGetLastResponseInfoA
#endif // !UNICODE

//
// callback function for InternetSetStatusCallback
//

typedef
VOID
(CALLBACK * INTERNET_STATUS_CALLBACK)(
    IN HINTERNET hInternet,
    IN DWORD dwContext,
    IN DWORD dwInternetStatus,
    IN LPVOID lpvStatusInformation OPTIONAL,
    IN DWORD dwStatusInformationLength
    );

typedef INTERNET_STATUS_CALLBACK * LPINTERNET_STATUS_CALLBACK;

/**
 * This function sets up a callback function that Windows CE Internet functions can call as progress
 * is made during an operation.
 *
 * @param hInternet Handle for which the callback is to be set.
 * @param lpfnInternetCallback Long pointer to the callback function to call when progress is made,
 *   or to return NULL to remove the existing callback function. For more information about the
 *   callback function, see INTERNET_STATUS_CALLBACK.
 *
 * @return The previously defined status callback function indicates success. NULL indicates that
 *   there was no previously defined status callback function. INTERNET_INVALID_STATUS_CALLBACK
 *   indicates that the callback function is not valid.
 *
 * Both synchronous and asynchronous functions use the callback function to indicate the progress of
 * the request, such as resolving a name, connecting to a server, and so on. The callback function
 * is required for an asynchronous operation. The asynchronous request will call back to the
 * application with INTERNET_STATUS_REQUEST_COMPLETE to indicate the request has been completed.
 *
 * A callback function can be set on any handle, and is inherited by derived handles. A callback
 * function can be changed using InternetSetStatusCallback, providing there are no pending requests
 * that need to use the previous callback value. Note, however, that changing the callback function
 * on a handle does not change the callbacks on derived handles, such as that returned by
 * InternetConnect. You must change the callback function at each level.
 *
 * Many of the Win32 Internet functions perform several operations on the network. Each operation
 * can take time to complete, and each can fail.
 *
 * It is sometimes desirable to display status information during a long-term operation. You can
 * display status information by setting up an Internet status callback function that cannot be
 * removed as long as any callbacks or any asynchronous functions are pending.
 *
 * After initiating InternetSetStatusCallback, the callback function can be accessed from within any
 * Win32 Internet function for monitoring time-intensive network operations.
 */
INTERNETAPI
INTERNET_STATUS_CALLBACK
WINAPI
InternetSetStatusCallback(
    IN HINTERNET hInternet,
    IN INTERNET_STATUS_CALLBACK lpfnInternetCallback
    );

//
// status manifests for Internet status callback
//

#define INTERNET_STATUS_RESOLVING_NAME          10
#define INTERNET_STATUS_NAME_RESOLVED           11
#define INTERNET_STATUS_CONNECTING_TO_SERVER    20
#define INTERNET_STATUS_CONNECTED_TO_SERVER     21
#define INTERNET_STATUS_SENDING_REQUEST         30
#define INTERNET_STATUS_REQUEST_SENT            31
#define INTERNET_STATUS_RECEIVING_RESPONSE      40
#define INTERNET_STATUS_RESPONSE_RECEIVED       41
#define INTERNET_STATUS_CTL_RESPONSE_RECEIVED   42
#define INTERNET_STATUS_PREFETCH                43
#define INTERNET_STATUS_CLOSING_CONNECTION      50
#define INTERNET_STATUS_CONNECTION_CLOSED       51
#define INTERNET_STATUS_HANDLE_CREATED          60
#define INTERNET_STATUS_HANDLE_CLOSING          70
#define INTERNET_STATUS_REQUEST_COMPLETE        100
#define INTERNET_STATUS_REDIRECT                110

//
// if the following value is returned by InternetSetStatusCallback, then
// probably an invalid (non-code) address was supplied for the callback
//

#define INTERNET_INVALID_STATUS_CALLBACK        ((INTERNET_STATUS_CALLBACK)(-1L))

// @CESYSGEN IF WININET_INETFTP

//
// FTP
//

//
// manifests
//

#define FTP_TRANSFER_TYPE_UNKNOWN   0x00000000
#define FTP_TRANSFER_TYPE_ASCII     0x00000001
#define FTP_TRANSFER_TYPE_BINARY    0x00000002

#define FTP_TRANSFER_TYPE_MASK      (FTP_TRANSFER_TYPE_ASCII | FTP_TRANSFER_TYPE_BINARY)

//
// prototypes
//

/**
 * This function searches the specified directory of the specified FTP session. File and directory
 * entries are returned to the application in the WIN32_FIND_DATA structure.
 *
 * @param hConnect [in] Valid handle to an FTP session returned by the InternetConnect function.
 * @param lpszSearchFile [in] Long pointer to a null-terminated string that specifies a valid
 *   directory path or file name for the FTP server file system. The string can contain wildcards, but
 *   blank spaces are not accepted. If the value of lpszSearchFile is NULL or if it is an empty
 *   string, it will find the first file in the current directory on the server.
 * @param lpFindFileData [out] Long pointer to a WIN32_FIND_DATA structure that receives data about
 *   the found file or directory.
 * @param dwFlags [in] Specifies an application-defined value that associates this search with an
 *   application. It is one of the following values: Value Description INTERNET_FLAG_DONT_CACHE Does
 *   not add the returned entity to the cache. Identical to the preferred value,
 *   INTERNET_FLAG_NO_CACHE_WRITE. INTERNET_FLAG_HYPERLINK Forces a reload if there was no Expires
 *   time and no Last-Modified time returned by the server when determining whether to reload the item
 *   from the network. INTERNET_FLAG_MUST_CACHE_REQUEST Causes a temporary file to be created if the
 *   file cannot be cached. Identical to the preferred value, INTERNET_FLAG_NEED_FILE.
 *   INTERNET_FLAG_NEED_FILE Causes a temporary file to be created if the file cannot be cached.
 *   INTERNET_FLAG_NO_CACHE_WRITE Does not add the returned entity to the cache. INTERNET_FLAG_RELOAD
 *   Forces a download of the requested file, object, or directory listing from the origin server, not
 *   from the cache. INTERNET_FLAG_RESYNCHRONIZE Causes the FTP resource to be reloaded from the
 *   server.
 * @param dwContext [in] Specifies an application-defined value that associates this search with
 *   application data. This parameter is used only if the application has already called the
 *   InternetSetStatusCallback function to set up a status callback function. All status requests are
 *   handled synchronously.
 *
 * @return A valid handle for the request if the directory enumeration was started indicates
 *   success. NULL indicates failure. To get extended error data, call GetLastError. If the function
 *   finds no matching files, GetLastError returns ERROR_NO_MORE_FILES.
 *
 * Inetftp.dll is available only for Intel x86 processors.
 *
 * This function enumerates both files and directories.
 *
 * FtpFindFirstFile is similar to the Win32 FindFirstFile function. Note, however, that only one
 * FtpFindFirstFile can occur at a time within a given FTP session. The enumerations, therefore, are
 * correlated with the FTP session handle. This is because the FTP protocol accepts only one
 * directory enumeration per session.
 *
 * After calling FtpFindFirstFile and until calling the InternetCloseHandle function, the
 * application cannot call FtpFindFirstFile again on the given FTP session handle. If a call is made
 * to FtpFindFirstFile on that handle, the function will fail with ERROR_FTP_TRANSFER_IN_PROGRESS.
 *
 * After beginning a directory enumeration with FtpFindFirstFile, the InternetFindNextFile function
 * can be used to continue the enumeration.
 *
 * InternetCloseHandle closes the handle returned by FtpFindFirstFile. If InternetCloseHandle closes
 * the handle before InternetFindNextFile fails with ERROR_NO_MORE_FILES, the directory enumeration
 * will be terminated.
 *
 * Because the FTP protocol provides no standard means of enumerating, common file data, such as
 * file creation date and time, is not always available or correct. When this happens,
 * FtpFindFirstFile and InternetFindNextFile fill in unavailable data with an estimate. For example,
 * creation and last access dates will often be the same as the file modification date.
 *
 * The application cannot call FtpFindFirstFile between calls to FtpOpenFile and
 * InternetCloseHandle.
 */
INTERNETAPI
HINTERNET
WINAPI
FtpFindFirstFileA(
    IN HINTERNET hConnect,
    IN LPCSTR lpszSearchFile OPTIONAL,
    OUT LPWIN32_FIND_DATAA lpFindFileData OPTIONAL,
    IN DWORD dwFlags,
    IN DWORD dwContext
    );
/**
 * This function searches the specified directory of the specified FTP session. File and directory
 * entries are returned to the application in the WIN32_FIND_DATA structure.
 *
 * @param hConnect [in] Valid handle to an FTP session returned by the InternetConnect function.
 * @param lpszSearchFile [in] Long pointer to a null-terminated string that specifies a valid
 *   directory path or file name for the FTP server file system. The string can contain wildcards, but
 *   blank spaces are not accepted. If the value of lpszSearchFile is NULL or if it is an empty
 *   string, it will find the first file in the current directory on the server.
 * @param lpFindFileData [out] Long pointer to a WIN32_FIND_DATA structure that receives data about
 *   the found file or directory.
 * @param dwFlags [in] Specifies an application-defined value that associates this search with an
 *   application. It is one of the following values: Value Description INTERNET_FLAG_DONT_CACHE Does
 *   not add the returned entity to the cache. Identical to the preferred value,
 *   INTERNET_FLAG_NO_CACHE_WRITE. INTERNET_FLAG_HYPERLINK Forces a reload if there was no Expires
 *   time and no Last-Modified time returned by the server when determining whether to reload the item
 *   from the network. INTERNET_FLAG_MUST_CACHE_REQUEST Causes a temporary file to be created if the
 *   file cannot be cached. Identical to the preferred value, INTERNET_FLAG_NEED_FILE.
 *   INTERNET_FLAG_NEED_FILE Causes a temporary file to be created if the file cannot be cached.
 *   INTERNET_FLAG_NO_CACHE_WRITE Does not add the returned entity to the cache. INTERNET_FLAG_RELOAD
 *   Forces a download of the requested file, object, or directory listing from the origin server, not
 *   from the cache. INTERNET_FLAG_RESYNCHRONIZE Causes the FTP resource to be reloaded from the
 *   server.
 * @param dwContext [in] Specifies an application-defined value that associates this search with
 *   application data. This parameter is used only if the application has already called the
 *   InternetSetStatusCallback function to set up a status callback function. All status requests are
 *   handled synchronously.
 *
 * @return A valid handle for the request if the directory enumeration was started indicates
 *   success. NULL indicates failure. To get extended error data, call GetLastError. If the function
 *   finds no matching files, GetLastError returns ERROR_NO_MORE_FILES.
 *
 * Inetftp.dll is available only for Intel x86 processors.
 *
 * This function enumerates both files and directories.
 *
 * FtpFindFirstFile is similar to the Win32 FindFirstFile function. Note, however, that only one
 * FtpFindFirstFile can occur at a time within a given FTP session. The enumerations, therefore, are
 * correlated with the FTP session handle. This is because the FTP protocol accepts only one
 * directory enumeration per session.
 *
 * After calling FtpFindFirstFile and until calling the InternetCloseHandle function, the
 * application cannot call FtpFindFirstFile again on the given FTP session handle. If a call is made
 * to FtpFindFirstFile on that handle, the function will fail with ERROR_FTP_TRANSFER_IN_PROGRESS.
 *
 * After beginning a directory enumeration with FtpFindFirstFile, the InternetFindNextFile function
 * can be used to continue the enumeration.
 *
 * InternetCloseHandle closes the handle returned by FtpFindFirstFile. If InternetCloseHandle closes
 * the handle before InternetFindNextFile fails with ERROR_NO_MORE_FILES, the directory enumeration
 * will be terminated.
 *
 * Because the FTP protocol provides no standard means of enumerating, common file data, such as
 * file creation date and time, is not always available or correct. When this happens,
 * FtpFindFirstFile and InternetFindNextFile fill in unavailable data with an estimate. For example,
 * creation and last access dates will often be the same as the file modification date.
 *
 * The application cannot call FtpFindFirstFile between calls to FtpOpenFile and
 * InternetCloseHandle.
 */
INTERNETAPI
HINTERNET
WINAPI
FtpFindFirstFileW(
    IN HINTERNET hConnect,
    IN LPCWSTR lpszSearchFile OPTIONAL,
    OUT LPWIN32_FIND_DATAW lpFindFileData OPTIONAL,
    IN DWORD dwFlags,
    IN DWORD dwContext
    );
#ifdef UNICODE
/**
 * This function searches the specified directory of the specified FTP session. File and directory
 * entries are returned to the application in the WIN32_FIND_DATA structure.
 *
 * @param hConnect [in] Valid handle to an FTP session returned by the InternetConnect function.
 * @param lpszSearchFile [in] Long pointer to a null-terminated string that specifies a valid
 *   directory path or file name for the FTP server file system. The string can contain wildcards, but
 *   blank spaces are not accepted. If the value of lpszSearchFile is NULL or if it is an empty
 *   string, it will find the first file in the current directory on the server.
 * @param lpFindFileData [out] Long pointer to a WIN32_FIND_DATA structure that receives data about
 *   the found file or directory.
 * @param dwFlags [in] Specifies an application-defined value that associates this search with an
 *   application. It is one of the following values: Value Description INTERNET_FLAG_DONT_CACHE Does
 *   not add the returned entity to the cache. Identical to the preferred value,
 *   INTERNET_FLAG_NO_CACHE_WRITE. INTERNET_FLAG_HYPERLINK Forces a reload if there was no Expires
 *   time and no Last-Modified time returned by the server when determining whether to reload the item
 *   from the network. INTERNET_FLAG_MUST_CACHE_REQUEST Causes a temporary file to be created if the
 *   file cannot be cached. Identical to the preferred value, INTERNET_FLAG_NEED_FILE.
 *   INTERNET_FLAG_NEED_FILE Causes a temporary file to be created if the file cannot be cached.
 *   INTERNET_FLAG_NO_CACHE_WRITE Does not add the returned entity to the cache. INTERNET_FLAG_RELOAD
 *   Forces a download of the requested file, object, or directory listing from the origin server, not
 *   from the cache. INTERNET_FLAG_RESYNCHRONIZE Causes the FTP resource to be reloaded from the
 *   server.
 * @param dwContext [in] Specifies an application-defined value that associates this search with
 *   application data. This parameter is used only if the application has already called the
 *   InternetSetStatusCallback function to set up a status callback function. All status requests are
 *   handled synchronously.
 *
 * @return A valid handle for the request if the directory enumeration was started indicates
 *   success. NULL indicates failure. To get extended error data, call GetLastError. If the function
 *   finds no matching files, GetLastError returns ERROR_NO_MORE_FILES.
 *
 * Inetftp.dll is available only for Intel x86 processors.
 *
 * This function enumerates both files and directories.
 *
 * FtpFindFirstFile is similar to the Win32 FindFirstFile function. Note, however, that only one
 * FtpFindFirstFile can occur at a time within a given FTP session. The enumerations, therefore, are
 * correlated with the FTP session handle. This is because the FTP protocol accepts only one
 * directory enumeration per session.
 *
 * After calling FtpFindFirstFile and until calling the InternetCloseHandle function, the
 * application cannot call FtpFindFirstFile again on the given FTP session handle. If a call is made
 * to FtpFindFirstFile on that handle, the function will fail with ERROR_FTP_TRANSFER_IN_PROGRESS.
 *
 * After beginning a directory enumeration with FtpFindFirstFile, the InternetFindNextFile function
 * can be used to continue the enumeration.
 *
 * InternetCloseHandle closes the handle returned by FtpFindFirstFile. If InternetCloseHandle closes
 * the handle before InternetFindNextFile fails with ERROR_NO_MORE_FILES, the directory enumeration
 * will be terminated.
 *
 * Because the FTP protocol provides no standard means of enumerating, common file data, such as
 * file creation date and time, is not always available or correct. When this happens,
 * FtpFindFirstFile and InternetFindNextFile fill in unavailable data with an estimate. For example,
 * creation and last access dates will often be the same as the file modification date.
 *
 * The application cannot call FtpFindFirstFile between calls to FtpOpenFile and
 * InternetCloseHandle.
 */
#define FtpFindFirstFile  FtpFindFirstFileW
#else
/**
 * This function searches the specified directory of the specified FTP session. File and directory
 * entries are returned to the application in the WIN32_FIND_DATA structure.
 *
 * @param hConnect [in] Valid handle to an FTP session returned by the InternetConnect function.
 * @param lpszSearchFile [in] Long pointer to a null-terminated string that specifies a valid
 *   directory path or file name for the FTP server file system. The string can contain wildcards, but
 *   blank spaces are not accepted. If the value of lpszSearchFile is NULL or if it is an empty
 *   string, it will find the first file in the current directory on the server.
 * @param lpFindFileData [out] Long pointer to a WIN32_FIND_DATA structure that receives data about
 *   the found file or directory.
 * @param dwFlags [in] Specifies an application-defined value that associates this search with an
 *   application. It is one of the following values: Value Description INTERNET_FLAG_DONT_CACHE Does
 *   not add the returned entity to the cache. Identical to the preferred value,
 *   INTERNET_FLAG_NO_CACHE_WRITE. INTERNET_FLAG_HYPERLINK Forces a reload if there was no Expires
 *   time and no Last-Modified time returned by the server when determining whether to reload the item
 *   from the network. INTERNET_FLAG_MUST_CACHE_REQUEST Causes a temporary file to be created if the
 *   file cannot be cached. Identical to the preferred value, INTERNET_FLAG_NEED_FILE.
 *   INTERNET_FLAG_NEED_FILE Causes a temporary file to be created if the file cannot be cached.
 *   INTERNET_FLAG_NO_CACHE_WRITE Does not add the returned entity to the cache. INTERNET_FLAG_RELOAD
 *   Forces a download of the requested file, object, or directory listing from the origin server, not
 *   from the cache. INTERNET_FLAG_RESYNCHRONIZE Causes the FTP resource to be reloaded from the
 *   server.
 * @param dwContext [in] Specifies an application-defined value that associates this search with
 *   application data. This parameter is used only if the application has already called the
 *   InternetSetStatusCallback function to set up a status callback function. All status requests are
 *   handled synchronously.
 *
 * @return A valid handle for the request if the directory enumeration was started indicates
 *   success. NULL indicates failure. To get extended error data, call GetLastError. If the function
 *   finds no matching files, GetLastError returns ERROR_NO_MORE_FILES.
 *
 * Inetftp.dll is available only for Intel x86 processors.
 *
 * This function enumerates both files and directories.
 *
 * FtpFindFirstFile is similar to the Win32 FindFirstFile function. Note, however, that only one
 * FtpFindFirstFile can occur at a time within a given FTP session. The enumerations, therefore, are
 * correlated with the FTP session handle. This is because the FTP protocol accepts only one
 * directory enumeration per session.
 *
 * After calling FtpFindFirstFile and until calling the InternetCloseHandle function, the
 * application cannot call FtpFindFirstFile again on the given FTP session handle. If a call is made
 * to FtpFindFirstFile on that handle, the function will fail with ERROR_FTP_TRANSFER_IN_PROGRESS.
 *
 * After beginning a directory enumeration with FtpFindFirstFile, the InternetFindNextFile function
 * can be used to continue the enumeration.
 *
 * InternetCloseHandle closes the handle returned by FtpFindFirstFile. If InternetCloseHandle closes
 * the handle before InternetFindNextFile fails with ERROR_NO_MORE_FILES, the directory enumeration
 * will be terminated.
 *
 * Because the FTP protocol provides no standard means of enumerating, common file data, such as
 * file creation date and time, is not always available or correct. When this happens,
 * FtpFindFirstFile and InternetFindNextFile fill in unavailable data with an estimate. For example,
 * creation and last access dates will often be the same as the file modification date.
 *
 * The application cannot call FtpFindFirstFile between calls to FtpOpenFile and
 * InternetCloseHandle.
 */
#define FtpFindFirstFile  FtpFindFirstFileA
#endif // !UNICODE

/**
 * This function retrieves a file from the FTP server and stores it under the specified file name,
 * creating a new local file in the process.
 *
 * @param hConnect [in] Valid handle to an FTP session.
 * @param lpszRemoteFile [in] Long pointer to a null-terminated string that contains the file name
 *   to retrieve from the remote system.
 * @param lpszNewFile [in] Long pointer to a null-terminated string that contains the file name to
 *   create on the local system.
 * @param fFailIfExists [in] Boolean that specifies if the function should proceed if a local file
 *   of the specified name already exists. If fFailIfExists is TRUE and the local file exists,
 *   FtpGetFile fails.
 * @param dwLocalFlagsAndAttributes [in] Specifies the file attributes for the new file. Can be a
 *   combination of the FILE_ATTRIBUTE_* flags used by the CreateFile function.
 * @param dwInternetFlags [in] Specifies how the function will handle the file download. The first
 *   set of flag values indicates the conditions under which the transfer occurs. These transfer type
 *   flags can be used in combination with the second set of flags that control caching. The
 *   application can select one of these transfer type values: Value Description
 *   FTP_TRANSFER_TYPE_ASCII Transfers the file using FTP ASCII, Type A, transfer method. Control and
 *   formatting data is converted to local equivalents. FTP_TRANSFER_TYPE_BINARY Transfers the file
 *   using FTP Image, Type I, transfer method. The file is transferred exactly as it exists with no
 *   changes. This is the default transfer method. FTP_TRANSFER_TYPE_UNKNOWN Defaults to
 *   FTP_TRANSFER_TYPE_BINARY. INTERNET_FLAG_TRANSFER_ASCII Transfers the file as ASCII.
 *   INTERNET_FLAG_TRANSFER_BINARY Transfers the file as binary. The following flags determine how the
 *   file caching will be done. A combination of the following flags can be used with the transfer
 *   type flag. Possible values are described in the following table. INTERNET_FLAG_DONT_CARE Does not
 *   add the returned entity to the cache. Identical to the preferred value
 *   INTERNET_FLAG_NO_CACHE_WRITE. INTERNET_FLAG_HYPERLINK Forces a reload if there was no Expires
 *   time and no Last-Modified time returned by the server when determining whether to reload the item
 *   from the network. INTERNET_FLAG_MUST_CACHE_REQUEST Causes a temporary file to be created if the
 *   file cannot be cached. Identical to the preferred value INTERNET_FLAG_NEED_FILE.
 *   INTERNET_FLAG_NEED_FILE Causes a temporary file to be created if the file cannot be cached.
 *   INTERNET_FLAG_NO_CACHE_WRITE Does not add the returned entity to the cache. INTERNET_FLAG_RELOAD
 *   Forces a download of the requested file, object, or directory listing from the origin server, not
 *   from the cache. INTERNET_FLAG_RESYNCHRONIZE Causes the FTP resource to be reloaded from the
 *   server.
 * @param dwContext [in] Specifies an application-defined value that associates this search with
 *   application data. This is used only if the application has already called
 *   InternetSetStatusCallback to set up a status callback function. All status requests are handled
 *   synchronously.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error data, call
 *   GetLastError.
 *
 * Inetftp.dll is available only for Intel x86 processors.
 *
 * FtpGetFile is a high-level routine that handles all the bookkeeping and overhead associated with
 * reading a file from an FTP server and storing it locally. An application that needs to retrieve
 * file data only or that requires close control over the file transfer should use the FtpOpenFile
 * and InternetReadFile functions.
 *
 * If the dwTransferType parameter specifies FILE_TRANSFER_TYPE_ASCII, translation of the file data
 * converts control and formatting characters to local equivalents. The default transfer is binary
 * mode, where the file is downloaded in the same format as it is stored on the server.
 *
 * Both lpszRemoteFile and lpszNewFile can be either partially or fully qualified file names
 * relative to the current directory. A backward slash (\) or forward slash (/) can be used as the
 * directory separator for either name. FtpGetFile translates the directory name separators to the
 * appropriate character before they are used.
 */
INTERNETAPI
BOOL
WINAPI
FtpGetFileA(
    IN HINTERNET hConnect,
    IN LPCSTR lpszRemoteFile,
    IN LPCSTR lpszNewFile,
    IN BOOL fFailIfExists,
    IN DWORD dwFlagsAndAttributes,
    IN DWORD dwFlags,
    IN DWORD dwContext
    );
/**
 * This function retrieves a file from the FTP server and stores it under the specified file name,
 * creating a new local file in the process.
 *
 * @param hConnect [in] Valid handle to an FTP session.
 * @param lpszRemoteFile [in] Long pointer to a null-terminated string that contains the file name
 *   to retrieve from the remote system.
 * @param lpszNewFile [in] Long pointer to a null-terminated string that contains the file name to
 *   create on the local system.
 * @param fFailIfExists [in] Boolean that specifies if the function should proceed if a local file
 *   of the specified name already exists. If fFailIfExists is TRUE and the local file exists,
 *   FtpGetFile fails.
 * @param dwLocalFlagsAndAttributes [in] Specifies the file attributes for the new file. Can be a
 *   combination of the FILE_ATTRIBUTE_* flags used by the CreateFile function.
 * @param dwInternetFlags [in] Specifies how the function will handle the file download. The first
 *   set of flag values indicates the conditions under which the transfer occurs. These transfer type
 *   flags can be used in combination with the second set of flags that control caching. The
 *   application can select one of these transfer type values: Value Description
 *   FTP_TRANSFER_TYPE_ASCII Transfers the file using FTP ASCII, Type A, transfer method. Control and
 *   formatting data is converted to local equivalents. FTP_TRANSFER_TYPE_BINARY Transfers the file
 *   using FTP Image, Type I, transfer method. The file is transferred exactly as it exists with no
 *   changes. This is the default transfer method. FTP_TRANSFER_TYPE_UNKNOWN Defaults to
 *   FTP_TRANSFER_TYPE_BINARY. INTERNET_FLAG_TRANSFER_ASCII Transfers the file as ASCII.
 *   INTERNET_FLAG_TRANSFER_BINARY Transfers the file as binary. The following flags determine how the
 *   file caching will be done. A combination of the following flags can be used with the transfer
 *   type flag. Possible values are described in the following table. INTERNET_FLAG_DONT_CARE Does not
 *   add the returned entity to the cache. Identical to the preferred value
 *   INTERNET_FLAG_NO_CACHE_WRITE. INTERNET_FLAG_HYPERLINK Forces a reload if there was no Expires
 *   time and no Last-Modified time returned by the server when determining whether to reload the item
 *   from the network. INTERNET_FLAG_MUST_CACHE_REQUEST Causes a temporary file to be created if the
 *   file cannot be cached. Identical to the preferred value INTERNET_FLAG_NEED_FILE.
 *   INTERNET_FLAG_NEED_FILE Causes a temporary file to be created if the file cannot be cached.
 *   INTERNET_FLAG_NO_CACHE_WRITE Does not add the returned entity to the cache. INTERNET_FLAG_RELOAD
 *   Forces a download of the requested file, object, or directory listing from the origin server, not
 *   from the cache. INTERNET_FLAG_RESYNCHRONIZE Causes the FTP resource to be reloaded from the
 *   server.
 * @param dwContext [in] Specifies an application-defined value that associates this search with
 *   application data. This is used only if the application has already called
 *   InternetSetStatusCallback to set up a status callback function. All status requests are handled
 *   synchronously.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error data, call
 *   GetLastError.
 *
 * Inetftp.dll is available only for Intel x86 processors.
 *
 * FtpGetFile is a high-level routine that handles all the bookkeeping and overhead associated with
 * reading a file from an FTP server and storing it locally. An application that needs to retrieve
 * file data only or that requires close control over the file transfer should use the FtpOpenFile
 * and InternetReadFile functions.
 *
 * If the dwTransferType parameter specifies FILE_TRANSFER_TYPE_ASCII, translation of the file data
 * converts control and formatting characters to local equivalents. The default transfer is binary
 * mode, where the file is downloaded in the same format as it is stored on the server.
 *
 * Both lpszRemoteFile and lpszNewFile can be either partially or fully qualified file names
 * relative to the current directory. A backward slash (\) or forward slash (/) can be used as the
 * directory separator for either name. FtpGetFile translates the directory name separators to the
 * appropriate character before they are used.
 */
INTERNETAPI
BOOL
WINAPI
FtpGetFileW(
    IN HINTERNET hConnect,
    IN LPCWSTR lpszRemoteFile,
    IN LPCWSTR lpszNewFile,
    IN BOOL fFailIfExists,
    IN DWORD dwFlagsAndAttributes,
    IN DWORD dwFlags,
    IN DWORD dwContext
    );
#ifdef UNICODE
/**
 * This function retrieves a file from the FTP server and stores it under the specified file name,
 * creating a new local file in the process.
 *
 * @param hConnect [in] Valid handle to an FTP session.
 * @param lpszRemoteFile [in] Long pointer to a null-terminated string that contains the file name
 *   to retrieve from the remote system.
 * @param lpszNewFile [in] Long pointer to a null-terminated string that contains the file name to
 *   create on the local system.
 * @param fFailIfExists [in] Boolean that specifies if the function should proceed if a local file
 *   of the specified name already exists. If fFailIfExists is TRUE and the local file exists,
 *   FtpGetFile fails.
 * @param dwLocalFlagsAndAttributes [in] Specifies the file attributes for the new file. Can be a
 *   combination of the FILE_ATTRIBUTE_* flags used by the CreateFile function.
 * @param dwInternetFlags [in] Specifies how the function will handle the file download. The first
 *   set of flag values indicates the conditions under which the transfer occurs. These transfer type
 *   flags can be used in combination with the second set of flags that control caching. The
 *   application can select one of these transfer type values: Value Description
 *   FTP_TRANSFER_TYPE_ASCII Transfers the file using FTP ASCII, Type A, transfer method. Control and
 *   formatting data is converted to local equivalents. FTP_TRANSFER_TYPE_BINARY Transfers the file
 *   using FTP Image, Type I, transfer method. The file is transferred exactly as it exists with no
 *   changes. This is the default transfer method. FTP_TRANSFER_TYPE_UNKNOWN Defaults to
 *   FTP_TRANSFER_TYPE_BINARY. INTERNET_FLAG_TRANSFER_ASCII Transfers the file as ASCII.
 *   INTERNET_FLAG_TRANSFER_BINARY Transfers the file as binary. The following flags determine how the
 *   file caching will be done. A combination of the following flags can be used with the transfer
 *   type flag. Possible values are described in the following table. INTERNET_FLAG_DONT_CARE Does not
 *   add the returned entity to the cache. Identical to the preferred value
 *   INTERNET_FLAG_NO_CACHE_WRITE. INTERNET_FLAG_HYPERLINK Forces a reload if there was no Expires
 *   time and no Last-Modified time returned by the server when determining whether to reload the item
 *   from the network. INTERNET_FLAG_MUST_CACHE_REQUEST Causes a temporary file to be created if the
 *   file cannot be cached. Identical to the preferred value INTERNET_FLAG_NEED_FILE.
 *   INTERNET_FLAG_NEED_FILE Causes a temporary file to be created if the file cannot be cached.
 *   INTERNET_FLAG_NO_CACHE_WRITE Does not add the returned entity to the cache. INTERNET_FLAG_RELOAD
 *   Forces a download of the requested file, object, or directory listing from the origin server, not
 *   from the cache. INTERNET_FLAG_RESYNCHRONIZE Causes the FTP resource to be reloaded from the
 *   server.
 * @param dwContext [in] Specifies an application-defined value that associates this search with
 *   application data. This is used only if the application has already called
 *   InternetSetStatusCallback to set up a status callback function. All status requests are handled
 *   synchronously.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error data, call
 *   GetLastError.
 *
 * Inetftp.dll is available only for Intel x86 processors.
 *
 * FtpGetFile is a high-level routine that handles all the bookkeeping and overhead associated with
 * reading a file from an FTP server and storing it locally. An application that needs to retrieve
 * file data only or that requires close control over the file transfer should use the FtpOpenFile
 * and InternetReadFile functions.
 *
 * If the dwTransferType parameter specifies FILE_TRANSFER_TYPE_ASCII, translation of the file data
 * converts control and formatting characters to local equivalents. The default transfer is binary
 * mode, where the file is downloaded in the same format as it is stored on the server.
 *
 * Both lpszRemoteFile and lpszNewFile can be either partially or fully qualified file names
 * relative to the current directory. A backward slash (\) or forward slash (/) can be used as the
 * directory separator for either name. FtpGetFile translates the directory name separators to the
 * appropriate character before they are used.
 */
#define FtpGetFile  FtpGetFileW
#else
/**
 * This function retrieves a file from the FTP server and stores it under the specified file name,
 * creating a new local file in the process.
 *
 * @param hConnect [in] Valid handle to an FTP session.
 * @param lpszRemoteFile [in] Long pointer to a null-terminated string that contains the file name
 *   to retrieve from the remote system.
 * @param lpszNewFile [in] Long pointer to a null-terminated string that contains the file name to
 *   create on the local system.
 * @param fFailIfExists [in] Boolean that specifies if the function should proceed if a local file
 *   of the specified name already exists. If fFailIfExists is TRUE and the local file exists,
 *   FtpGetFile fails.
 * @param dwLocalFlagsAndAttributes [in] Specifies the file attributes for the new file. Can be a
 *   combination of the FILE_ATTRIBUTE_* flags used by the CreateFile function.
 * @param dwInternetFlags [in] Specifies how the function will handle the file download. The first
 *   set of flag values indicates the conditions under which the transfer occurs. These transfer type
 *   flags can be used in combination with the second set of flags that control caching. The
 *   application can select one of these transfer type values: Value Description
 *   FTP_TRANSFER_TYPE_ASCII Transfers the file using FTP ASCII, Type A, transfer method. Control and
 *   formatting data is converted to local equivalents. FTP_TRANSFER_TYPE_BINARY Transfers the file
 *   using FTP Image, Type I, transfer method. The file is transferred exactly as it exists with no
 *   changes. This is the default transfer method. FTP_TRANSFER_TYPE_UNKNOWN Defaults to
 *   FTP_TRANSFER_TYPE_BINARY. INTERNET_FLAG_TRANSFER_ASCII Transfers the file as ASCII.
 *   INTERNET_FLAG_TRANSFER_BINARY Transfers the file as binary. The following flags determine how the
 *   file caching will be done. A combination of the following flags can be used with the transfer
 *   type flag. Possible values are described in the following table. INTERNET_FLAG_DONT_CARE Does not
 *   add the returned entity to the cache. Identical to the preferred value
 *   INTERNET_FLAG_NO_CACHE_WRITE. INTERNET_FLAG_HYPERLINK Forces a reload if there was no Expires
 *   time and no Last-Modified time returned by the server when determining whether to reload the item
 *   from the network. INTERNET_FLAG_MUST_CACHE_REQUEST Causes a temporary file to be created if the
 *   file cannot be cached. Identical to the preferred value INTERNET_FLAG_NEED_FILE.
 *   INTERNET_FLAG_NEED_FILE Causes a temporary file to be created if the file cannot be cached.
 *   INTERNET_FLAG_NO_CACHE_WRITE Does not add the returned entity to the cache. INTERNET_FLAG_RELOAD
 *   Forces a download of the requested file, object, or directory listing from the origin server, not
 *   from the cache. INTERNET_FLAG_RESYNCHRONIZE Causes the FTP resource to be reloaded from the
 *   server.
 * @param dwContext [in] Specifies an application-defined value that associates this search with
 *   application data. This is used only if the application has already called
 *   InternetSetStatusCallback to set up a status callback function. All status requests are handled
 *   synchronously.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error data, call
 *   GetLastError.
 *
 * Inetftp.dll is available only for Intel x86 processors.
 *
 * FtpGetFile is a high-level routine that handles all the bookkeeping and overhead associated with
 * reading a file from an FTP server and storing it locally. An application that needs to retrieve
 * file data only or that requires close control over the file transfer should use the FtpOpenFile
 * and InternetReadFile functions.
 *
 * If the dwTransferType parameter specifies FILE_TRANSFER_TYPE_ASCII, translation of the file data
 * converts control and formatting characters to local equivalents. The default transfer is binary
 * mode, where the file is downloaded in the same format as it is stored on the server.
 *
 * Both lpszRemoteFile and lpszNewFile can be either partially or fully qualified file names
 * relative to the current directory. A backward slash (\) or forward slash (/) can be used as the
 * directory separator for either name. FtpGetFile translates the directory name separators to the
 * appropriate character before they are used.
 */
#define FtpGetFile  FtpGetFileA
#endif // !UNICODE

/**
 * This function stores a file on the FTP server.
 *
 * @param hConnect [in] Valid handle to an FTP session.
 * @param lpszLocalFile [in] Long pointer to a null-terminated string that contains the file name to
 *   send from the local system.
 * @param lpszNewRemoteFile [in] Long pointer to a null-terminated string that contains the file
 *   name to create on the remote system.
 * @param dwFlags [in] Specifies the conditions under which the transfer occurs. Can be a
 *   combination of the following values: Value Description INTERNET_FLAG_DONT_CACHE Does not add the
 *   returned entity to the cache. Identical to the preferred value INTERNET_FLAG_NO_CACHE_WRITE.
 *   INTERNET_FLAG_HYPERLINK Forces a reload if there was no Expires time and no Last-Modified time
 *   returned by the server when determining whether to reload the item from the network.
 *   INTERNET_FLAG_MUST_CACHE_REQUEST Causes a temporary file to be created if the file cannot be
 *   cached. Identical to the preferred value INTERNET_FLAG_NEED_FILE. INTERNET_FLAG_NEED_FILE Causes
 *   a temporary file to be created if the file cannot be cached. INTERNET_FLAG_NO_CACHE_WRITE Does
 *   not add the returned entity to the cache. INTERNET_FLAG_RELOAD Forces a download of the requested
 *   file, object, or directory listing from the origin server, not from the cache.
 *   INTERNET_FLAG_RESYNCRONIZE Performs a conditional download of the file.
 *   INTERNET_FLAG_TRANSFER_ASCII Transfers the file as ASCII. INTERNET_FLAG_TRANSFER_BINARY Transfers
 *   the file as binary.
 * @param dwContext [in] Specifies an application-defined value that associates this search with
 *   application data. This parameter is used only if the application has already called
 *   InternetSetStatusCallback to set up a status callback. All status requests are handled
 *   synchronously.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error data, call
 *   GetLastError.
 *
 * Inetftp.dll is available only for Intel x86 processors.
 *
 * FtpPutFile is a high-level routine that handles all the bookkeeping and overhead associated with
 * reading a file locally and storing it on an FTP server. An application that needs to send file
 * data only, or that requires close control over the file transfer, should use the FtpOpenFile and
 * InternetWriteFile functions.
 *
 * If the dwTransferType parameter specifies FILE_TRANSFER_TYPE_ASCII, translation of the file data
 * converts control and formatting characters to local equivalents.
 *
 * Both lpszNewRemoteFile and lpszLocalFile can be either partially or fully qualified file names
 * relative to the current directory. A backward slash (\) or forward slash (/) can be used as the
 * directory separator for either name. FtpPutFile translates the directory name separators to the
 * appropriate character before they are used.
 */
INTERNETAPI
BOOL
WINAPI
FtpPutFileA(
    IN HINTERNET hConnect,
    IN LPCSTR lpszLocalFile,
    IN LPCSTR lpszNewRemoteFile,
    IN DWORD dwFlags,
    IN DWORD dwContext
    );
/**
 * This function stores a file on the FTP server.
 *
 * @param hConnect [in] Valid handle to an FTP session.
 * @param lpszLocalFile [in] Long pointer to a null-terminated string that contains the file name to
 *   send from the local system.
 * @param lpszNewRemoteFile [in] Long pointer to a null-terminated string that contains the file
 *   name to create on the remote system.
 * @param dwFlags [in] Specifies the conditions under which the transfer occurs. Can be a
 *   combination of the following values: Value Description INTERNET_FLAG_DONT_CACHE Does not add the
 *   returned entity to the cache. Identical to the preferred value INTERNET_FLAG_NO_CACHE_WRITE.
 *   INTERNET_FLAG_HYPERLINK Forces a reload if there was no Expires time and no Last-Modified time
 *   returned by the server when determining whether to reload the item from the network.
 *   INTERNET_FLAG_MUST_CACHE_REQUEST Causes a temporary file to be created if the file cannot be
 *   cached. Identical to the preferred value INTERNET_FLAG_NEED_FILE. INTERNET_FLAG_NEED_FILE Causes
 *   a temporary file to be created if the file cannot be cached. INTERNET_FLAG_NO_CACHE_WRITE Does
 *   not add the returned entity to the cache. INTERNET_FLAG_RELOAD Forces a download of the requested
 *   file, object, or directory listing from the origin server, not from the cache.
 *   INTERNET_FLAG_RESYNCRONIZE Performs a conditional download of the file.
 *   INTERNET_FLAG_TRANSFER_ASCII Transfers the file as ASCII. INTERNET_FLAG_TRANSFER_BINARY Transfers
 *   the file as binary.
 * @param dwContext [in] Specifies an application-defined value that associates this search with
 *   application data. This parameter is used only if the application has already called
 *   InternetSetStatusCallback to set up a status callback. All status requests are handled
 *   synchronously.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error data, call
 *   GetLastError.
 *
 * Inetftp.dll is available only for Intel x86 processors.
 *
 * FtpPutFile is a high-level routine that handles all the bookkeeping and overhead associated with
 * reading a file locally and storing it on an FTP server. An application that needs to send file
 * data only, or that requires close control over the file transfer, should use the FtpOpenFile and
 * InternetWriteFile functions.
 *
 * If the dwTransferType parameter specifies FILE_TRANSFER_TYPE_ASCII, translation of the file data
 * converts control and formatting characters to local equivalents.
 *
 * Both lpszNewRemoteFile and lpszLocalFile can be either partially or fully qualified file names
 * relative to the current directory. A backward slash (\) or forward slash (/) can be used as the
 * directory separator for either name. FtpPutFile translates the directory name separators to the
 * appropriate character before they are used.
 */
INTERNETAPI
BOOL
WINAPI
FtpPutFileW(
    IN HINTERNET hConnect,
    IN LPCWSTR lpszLocalFile,
    IN LPCWSTR lpszNewRemoteFile,
    IN DWORD dwFlags,
    IN DWORD dwContext
    );
#ifdef UNICODE
/**
 * This function stores a file on the FTP server.
 *
 * @param hConnect [in] Valid handle to an FTP session.
 * @param lpszLocalFile [in] Long pointer to a null-terminated string that contains the file name to
 *   send from the local system.
 * @param lpszNewRemoteFile [in] Long pointer to a null-terminated string that contains the file
 *   name to create on the remote system.
 * @param dwFlags [in] Specifies the conditions under which the transfer occurs. Can be a
 *   combination of the following values: Value Description INTERNET_FLAG_DONT_CACHE Does not add the
 *   returned entity to the cache. Identical to the preferred value INTERNET_FLAG_NO_CACHE_WRITE.
 *   INTERNET_FLAG_HYPERLINK Forces a reload if there was no Expires time and no Last-Modified time
 *   returned by the server when determining whether to reload the item from the network.
 *   INTERNET_FLAG_MUST_CACHE_REQUEST Causes a temporary file to be created if the file cannot be
 *   cached. Identical to the preferred value INTERNET_FLAG_NEED_FILE. INTERNET_FLAG_NEED_FILE Causes
 *   a temporary file to be created if the file cannot be cached. INTERNET_FLAG_NO_CACHE_WRITE Does
 *   not add the returned entity to the cache. INTERNET_FLAG_RELOAD Forces a download of the requested
 *   file, object, or directory listing from the origin server, not from the cache.
 *   INTERNET_FLAG_RESYNCRONIZE Performs a conditional download of the file.
 *   INTERNET_FLAG_TRANSFER_ASCII Transfers the file as ASCII. INTERNET_FLAG_TRANSFER_BINARY Transfers
 *   the file as binary.
 * @param dwContext [in] Specifies an application-defined value that associates this search with
 *   application data. This parameter is used only if the application has already called
 *   InternetSetStatusCallback to set up a status callback. All status requests are handled
 *   synchronously.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error data, call
 *   GetLastError.
 *
 * Inetftp.dll is available only for Intel x86 processors.
 *
 * FtpPutFile is a high-level routine that handles all the bookkeeping and overhead associated with
 * reading a file locally and storing it on an FTP server. An application that needs to send file
 * data only, or that requires close control over the file transfer, should use the FtpOpenFile and
 * InternetWriteFile functions.
 *
 * If the dwTransferType parameter specifies FILE_TRANSFER_TYPE_ASCII, translation of the file data
 * converts control and formatting characters to local equivalents.
 *
 * Both lpszNewRemoteFile and lpszLocalFile can be either partially or fully qualified file names
 * relative to the current directory. A backward slash (\) or forward slash (/) can be used as the
 * directory separator for either name. FtpPutFile translates the directory name separators to the
 * appropriate character before they are used.
 */
#define FtpPutFile  FtpPutFileW
#else
/**
 * This function stores a file on the FTP server.
 *
 * @param hConnect [in] Valid handle to an FTP session.
 * @param lpszLocalFile [in] Long pointer to a null-terminated string that contains the file name to
 *   send from the local system.
 * @param lpszNewRemoteFile [in] Long pointer to a null-terminated string that contains the file
 *   name to create on the remote system.
 * @param dwFlags [in] Specifies the conditions under which the transfer occurs. Can be a
 *   combination of the following values: Value Description INTERNET_FLAG_DONT_CACHE Does not add the
 *   returned entity to the cache. Identical to the preferred value INTERNET_FLAG_NO_CACHE_WRITE.
 *   INTERNET_FLAG_HYPERLINK Forces a reload if there was no Expires time and no Last-Modified time
 *   returned by the server when determining whether to reload the item from the network.
 *   INTERNET_FLAG_MUST_CACHE_REQUEST Causes a temporary file to be created if the file cannot be
 *   cached. Identical to the preferred value INTERNET_FLAG_NEED_FILE. INTERNET_FLAG_NEED_FILE Causes
 *   a temporary file to be created if the file cannot be cached. INTERNET_FLAG_NO_CACHE_WRITE Does
 *   not add the returned entity to the cache. INTERNET_FLAG_RELOAD Forces a download of the requested
 *   file, object, or directory listing from the origin server, not from the cache.
 *   INTERNET_FLAG_RESYNCRONIZE Performs a conditional download of the file.
 *   INTERNET_FLAG_TRANSFER_ASCII Transfers the file as ASCII. INTERNET_FLAG_TRANSFER_BINARY Transfers
 *   the file as binary.
 * @param dwContext [in] Specifies an application-defined value that associates this search with
 *   application data. This parameter is used only if the application has already called
 *   InternetSetStatusCallback to set up a status callback. All status requests are handled
 *   synchronously.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error data, call
 *   GetLastError.
 *
 * Inetftp.dll is available only for Intel x86 processors.
 *
 * FtpPutFile is a high-level routine that handles all the bookkeeping and overhead associated with
 * reading a file locally and storing it on an FTP server. An application that needs to send file
 * data only, or that requires close control over the file transfer, should use the FtpOpenFile and
 * InternetWriteFile functions.
 *
 * If the dwTransferType parameter specifies FILE_TRANSFER_TYPE_ASCII, translation of the file data
 * converts control and formatting characters to local equivalents.
 *
 * Both lpszNewRemoteFile and lpszLocalFile can be either partially or fully qualified file names
 * relative to the current directory. A backward slash (\) or forward slash (/) can be used as the
 * directory separator for either name. FtpPutFile translates the directory name separators to the
 * appropriate character before they are used.
 */
#define FtpPutFile  FtpPutFileA
#endif // !UNICODE

/**
 * This function deletes a file stored on the FTP server.
 *
 * @param hConnect [in] Valid handle to an FTP session. This handle must have been returned by a
 *   previous call to the InternetConnect function.
 * @param lpszFileName [in] Long pointer to a null-terminated string that contains the file name to
 *   delete on the remote system.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error data, call
 *   GetLastError.
 *
 * Inetftp.dll is available only for Intel x86 processors.
 *
 * The lpszFile parameter can be either partially or fully qualified file names relative to the
 * current directory. A backward slash (\) or forward slash (/) can be used as the directory
 * separator for either name. FtpDeleteFile translates the directory name separators to the
 * appropriate character before they are used.
 */
INTERNETAPI
BOOL
WINAPI
FtpDeleteFileA(
    IN HINTERNET hConnect,
    IN LPCSTR lpszFileName
    );
/**
 * This function deletes a file stored on the FTP server.
 *
 * @param hConnect [in] Valid handle to an FTP session. This handle must have been returned by a
 *   previous call to the InternetConnect function.
 * @param lpszFileName [in] Long pointer to a null-terminated string that contains the file name to
 *   delete on the remote system.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error data, call
 *   GetLastError.
 *
 * Inetftp.dll is available only for Intel x86 processors.
 *
 * The lpszFile parameter can be either partially or fully qualified file names relative to the
 * current directory. A backward slash (\) or forward slash (/) can be used as the directory
 * separator for either name. FtpDeleteFile translates the directory name separators to the
 * appropriate character before they are used.
 */
INTERNETAPI
BOOL
WINAPI
FtpDeleteFileW(
    IN HINTERNET hConnect,
    IN LPCWSTR lpszFileName
    );
#ifdef UNICODE
/**
 * This function deletes a file stored on the FTP server.
 *
 * @param hConnect [in] Valid handle to an FTP session. This handle must have been returned by a
 *   previous call to the InternetConnect function.
 * @param lpszFileName [in] Long pointer to a null-terminated string that contains the file name to
 *   delete on the remote system.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error data, call
 *   GetLastError.
 *
 * Inetftp.dll is available only for Intel x86 processors.
 *
 * The lpszFile parameter can be either partially or fully qualified file names relative to the
 * current directory. A backward slash (\) or forward slash (/) can be used as the directory
 * separator for either name. FtpDeleteFile translates the directory name separators to the
 * appropriate character before they are used.
 */
#define FtpDeleteFile  FtpDeleteFileW
#else
/**
 * This function deletes a file stored on the FTP server.
 *
 * @param hConnect [in] Valid handle to an FTP session. This handle must have been returned by a
 *   previous call to the InternetConnect function.
 * @param lpszFileName [in] Long pointer to a null-terminated string that contains the file name to
 *   delete on the remote system.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error data, call
 *   GetLastError.
 *
 * Inetftp.dll is available only for Intel x86 processors.
 *
 * The lpszFile parameter can be either partially or fully qualified file names relative to the
 * current directory. A backward slash (\) or forward slash (/) can be used as the directory
 * separator for either name. FtpDeleteFile translates the directory name separators to the
 * appropriate character before they are used.
 */
#define FtpDeleteFile  FtpDeleteFileA
#endif // !UNICODE

/**
 * This function renames a file stored on the FTP server.
 *
 * @param hConnect [in] Valid handle to an FTP session.
 * @param lpszExisting [in] Long pointer to a null-terminated string that contains the file name to
 *   be changed on the remote FTP server.
 * @param lpszNew [in] Long pointer to a null-terminated string that contains the new name for the
 *   remote file.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error data, call
 *   GetLastError.
 *
 * Inetftp.dll is available only for Intel x86 processors.
 *
 * The lpszExisting and lpszNew parameters can be either partially or fully qualified file names
 * relative to the current directory. A backward slash (\) or forward slash (/) can be used as the
 * directory separator for either name. FtpRenameFile translates the directory name separators to
 * the appropriate character before they are used.
 */
INTERNETAPI
BOOL
WINAPI
FtpRenameFileA(
    IN HINTERNET hConnect,
    IN LPCSTR lpszExisting,
    IN LPCSTR lpszNew
    );
/**
 * This function renames a file stored on the FTP server.
 *
 * @param hConnect [in] Valid handle to an FTP session.
 * @param lpszExisting [in] Long pointer to a null-terminated string that contains the file name to
 *   be changed on the remote FTP server.
 * @param lpszNew [in] Long pointer to a null-terminated string that contains the new name for the
 *   remote file.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error data, call
 *   GetLastError.
 *
 * Inetftp.dll is available only for Intel x86 processors.
 *
 * The lpszExisting and lpszNew parameters can be either partially or fully qualified file names
 * relative to the current directory. A backward slash (\) or forward slash (/) can be used as the
 * directory separator for either name. FtpRenameFile translates the directory name separators to
 * the appropriate character before they are used.
 */
INTERNETAPI
BOOL
WINAPI
FtpRenameFileW(
    IN HINTERNET hConnect,
    IN LPCWSTR lpszExisting,
    IN LPCWSTR lpszNew
    );
#ifdef UNICODE
/**
 * This function renames a file stored on the FTP server.
 *
 * @param hConnect [in] Valid handle to an FTP session.
 * @param lpszExisting [in] Long pointer to a null-terminated string that contains the file name to
 *   be changed on the remote FTP server.
 * @param lpszNew [in] Long pointer to a null-terminated string that contains the new name for the
 *   remote file.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error data, call
 *   GetLastError.
 *
 * Inetftp.dll is available only for Intel x86 processors.
 *
 * The lpszExisting and lpszNew parameters can be either partially or fully qualified file names
 * relative to the current directory. A backward slash (\) or forward slash (/) can be used as the
 * directory separator for either name. FtpRenameFile translates the directory name separators to
 * the appropriate character before they are used.
 */
#define FtpRenameFile  FtpRenameFileW
#else
/**
 * This function renames a file stored on the FTP server.
 *
 * @param hConnect [in] Valid handle to an FTP session.
 * @param lpszExisting [in] Long pointer to a null-terminated string that contains the file name to
 *   be changed on the remote FTP server.
 * @param lpszNew [in] Long pointer to a null-terminated string that contains the new name for the
 *   remote file.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error data, call
 *   GetLastError.
 *
 * Inetftp.dll is available only for Intel x86 processors.
 *
 * The lpszExisting and lpszNew parameters can be either partially or fully qualified file names
 * relative to the current directory. A backward slash (\) or forward slash (/) can be used as the
 * directory separator for either name. FtpRenameFile translates the directory name separators to
 * the appropriate character before they are used.
 */
#define FtpRenameFile  FtpRenameFileA
#endif // !UNICODE

/**
 * This function initiates access to a remote file for writing or reading.
 *
 * @param hConnect [in] Valid handle to an FTP session.
 * @param lpszFileName [in] Long pointer to a null-terminated string that contains the name of the
 *   file to access on the remote system.
 * @param fdwAccess [in] Value that determines how the file will be accessed. This can be
 *   GENERIC_READ or GENERIC_WRITE, but not both.
 * @param dwFlags [in] Specifies the conditions under which the transfers occur. The application
 *   should select one transfer type and flags that control file caching. The transfer type can be one
 *   of the following values: Value Description FTP_TRANSFER_TYPE_ASCII Transfers the file using FTP
 *   ASCII, Type A, transfer method. Control and formatting data is converted to local equivalents.
 *   FTP_TRANSFER_TYPE_BINARY Transfers the file using FTP Image, Type I, transfer method. The file is
 *   transferred exactly as it exists with no changes. This is the default transfer method.
 *   FTP_TRANSFER_TYPE_UNKNOWN Defaults to FTP_TRANSFER_TYPE_BINARY. INTERNET_FLAG_TRANSFER_ASCII
 *   Transfers the file as ASCII. INTERNET_FLAG_TRANSFER_BINARY Transfers the file as binary. One or
 *   more of the values described in the following table are used by an application to control file
 *   caching. INTERNET_FLAG_DONT_CACHE Does not cache the data, either locally or in gateways.
 *   Identical to the preferred value INTERNET_FLAG_NO_CACHE_WRITE. INTERNET_FLAG_HYPERLINK Forces a
 *   reload if there was no Expires time and no Last-Modified time returned by the server when
 *   determining whether to reload the item from the network. INTERNET_FLAG_MUST_CACHE_REQUEST Causes
 *   a temporary file to be created if the file cannot be cached. Identical to the preferred value
 *   INTERNET_FLAG_NEED_FILE. INTERNET_FLAG_NEED_FILE Causes a temporary file to be created if the
 *   file cannot be cached. INTERNET_FLAG_NO_CACHE_WRITE Does not cache the data, either locally or in
 *   gateways. INTERNET_FLAG_RELOAD Forces a download of the requested file, object, or directory
 *   listing from the origin server, not from the cache. INTERNET_FLAG_RESYNCHRONIZE Causes the FTP
 *   resource to be reloaded from the server.
 * @param dwContext [in] Specifies an application-defined value that associates this search with
 *   application data. This is only used if the application has already called
 *   InternetSetStatusCallback to set up a status callback function. All status requests are handled
 *   synchronously.
 *
 * @return A handle indicates success. NULL indicates failure. To get extended error data, call
 *   GetLastError.
 *
 * Inetftp.dll is available only for Intel x86 processors.
 *
 * FtpOpenFile should be used in the following situations:
 *
 * An application has data it needs to send to an FTP server to be created as a file on the FTP
 * server, but the application does not have a local file containing the data. After the file is
 * opened with FtpOpenFile, the application uses InternetWriteFile to send the FTP file data to the
 * server.
 *
 * An application needs to retrieve a file from the server into application-controlled memory,
 * instead of writing the file to disk. The application uses InternetReadFile after using
 * FtpOpenFile to open the file.
 *
 * An application needs a fine level of control over a file transfer. For example, the application
 * may need to display a progress indicator when downloading a file to indicate to the user that the
 * file transfer is, or is not, proceeding correctly.
 *
 * After calling FtpOpenFile and until calling InternetCloseHandle, all other calls to FTP functions
 * on the same FTP session handle will fail and set the error message to
 * ERROR_FTP_TRANSFER_IN_PROGRESS.
 *
 * Only one file can be open in a single FTP session. Therefore, no file handle is returned and the
 * application simply uses the FTP session handle when necessary.
 *
 * The lpszFile parameter can be either partially or fully qualified file names relative to the
 * current directory. A backward slash (\) or forward slash (/) can be used as the directory
 * separator for either name. FtpOpenFile translates the directory name separators to the
 * appropriate character before they are used.
 *
 * The InternetCloseHandle function is used to close the handle returned by FtpOpenFile. If
 * InternetCloseHandle closes the handle before all the data has been transferred, the transfer is
 * terminated.
 */
INTERNETAPI
HINTERNET
WINAPI
FtpOpenFileA(
    IN HINTERNET hConnect,
    IN LPCSTR lpszFileName,
    IN DWORD dwAccess,
    IN DWORD dwFlags,
    IN DWORD dwContext
    );
/**
 * This function initiates access to a remote file for writing or reading.
 *
 * @param hConnect [in] Valid handle to an FTP session.
 * @param lpszFileName [in] Long pointer to a null-terminated string that contains the name of the
 *   file to access on the remote system.
 * @param fdwAccess [in] Value that determines how the file will be accessed. This can be
 *   GENERIC_READ or GENERIC_WRITE, but not both.
 * @param dwFlags [in] Specifies the conditions under which the transfers occur. The application
 *   should select one transfer type and flags that control file caching. The transfer type can be one
 *   of the following values: Value Description FTP_TRANSFER_TYPE_ASCII Transfers the file using FTP
 *   ASCII, Type A, transfer method. Control and formatting data is converted to local equivalents.
 *   FTP_TRANSFER_TYPE_BINARY Transfers the file using FTP Image, Type I, transfer method. The file is
 *   transferred exactly as it exists with no changes. This is the default transfer method.
 *   FTP_TRANSFER_TYPE_UNKNOWN Defaults to FTP_TRANSFER_TYPE_BINARY. INTERNET_FLAG_TRANSFER_ASCII
 *   Transfers the file as ASCII. INTERNET_FLAG_TRANSFER_BINARY Transfers the file as binary. One or
 *   more of the values described in the following table are used by an application to control file
 *   caching. INTERNET_FLAG_DONT_CACHE Does not cache the data, either locally or in gateways.
 *   Identical to the preferred value INTERNET_FLAG_NO_CACHE_WRITE. INTERNET_FLAG_HYPERLINK Forces a
 *   reload if there was no Expires time and no Last-Modified time returned by the server when
 *   determining whether to reload the item from the network. INTERNET_FLAG_MUST_CACHE_REQUEST Causes
 *   a temporary file to be created if the file cannot be cached. Identical to the preferred value
 *   INTERNET_FLAG_NEED_FILE. INTERNET_FLAG_NEED_FILE Causes a temporary file to be created if the
 *   file cannot be cached. INTERNET_FLAG_NO_CACHE_WRITE Does not cache the data, either locally or in
 *   gateways. INTERNET_FLAG_RELOAD Forces a download of the requested file, object, or directory
 *   listing from the origin server, not from the cache. INTERNET_FLAG_RESYNCHRONIZE Causes the FTP
 *   resource to be reloaded from the server.
 * @param dwContext [in] Specifies an application-defined value that associates this search with
 *   application data. This is only used if the application has already called
 *   InternetSetStatusCallback to set up a status callback function. All status requests are handled
 *   synchronously.
 *
 * @return A handle indicates success. NULL indicates failure. To get extended error data, call
 *   GetLastError.
 *
 * Inetftp.dll is available only for Intel x86 processors.
 *
 * FtpOpenFile should be used in the following situations:
 *
 * An application has data it needs to send to an FTP server to be created as a file on the FTP
 * server, but the application does not have a local file containing the data. After the file is
 * opened with FtpOpenFile, the application uses InternetWriteFile to send the FTP file data to the
 * server.
 *
 * An application needs to retrieve a file from the server into application-controlled memory,
 * instead of writing the file to disk. The application uses InternetReadFile after using
 * FtpOpenFile to open the file.
 *
 * An application needs a fine level of control over a file transfer. For example, the application
 * may need to display a progress indicator when downloading a file to indicate to the user that the
 * file transfer is, or is not, proceeding correctly.
 *
 * After calling FtpOpenFile and until calling InternetCloseHandle, all other calls to FTP functions
 * on the same FTP session handle will fail and set the error message to
 * ERROR_FTP_TRANSFER_IN_PROGRESS.
 *
 * Only one file can be open in a single FTP session. Therefore, no file handle is returned and the
 * application simply uses the FTP session handle when necessary.
 *
 * The lpszFile parameter can be either partially or fully qualified file names relative to the
 * current directory. A backward slash (\) or forward slash (/) can be used as the directory
 * separator for either name. FtpOpenFile translates the directory name separators to the
 * appropriate character before they are used.
 *
 * The InternetCloseHandle function is used to close the handle returned by FtpOpenFile. If
 * InternetCloseHandle closes the handle before all the data has been transferred, the transfer is
 * terminated.
 */
INTERNETAPI
HINTERNET
WINAPI
FtpOpenFileW(
    IN HINTERNET hConnect,
    IN LPCWSTR lpszFileName,
    IN DWORD dwAccess,
    IN DWORD dwFlags,
    IN DWORD dwContext
    );
#ifdef UNICODE
/**
 * This function initiates access to a remote file for writing or reading.
 *
 * @param hConnect [in] Valid handle to an FTP session.
 * @param lpszFileName [in] Long pointer to a null-terminated string that contains the name of the
 *   file to access on the remote system.
 * @param fdwAccess [in] Value that determines how the file will be accessed. This can be
 *   GENERIC_READ or GENERIC_WRITE, but not both.
 * @param dwFlags [in] Specifies the conditions under which the transfers occur. The application
 *   should select one transfer type and flags that control file caching. The transfer type can be one
 *   of the following values: Value Description FTP_TRANSFER_TYPE_ASCII Transfers the file using FTP
 *   ASCII, Type A, transfer method. Control and formatting data is converted to local equivalents.
 *   FTP_TRANSFER_TYPE_BINARY Transfers the file using FTP Image, Type I, transfer method. The file is
 *   transferred exactly as it exists with no changes. This is the default transfer method.
 *   FTP_TRANSFER_TYPE_UNKNOWN Defaults to FTP_TRANSFER_TYPE_BINARY. INTERNET_FLAG_TRANSFER_ASCII
 *   Transfers the file as ASCII. INTERNET_FLAG_TRANSFER_BINARY Transfers the file as binary. One or
 *   more of the values described in the following table are used by an application to control file
 *   caching. INTERNET_FLAG_DONT_CACHE Does not cache the data, either locally or in gateways.
 *   Identical to the preferred value INTERNET_FLAG_NO_CACHE_WRITE. INTERNET_FLAG_HYPERLINK Forces a
 *   reload if there was no Expires time and no Last-Modified time returned by the server when
 *   determining whether to reload the item from the network. INTERNET_FLAG_MUST_CACHE_REQUEST Causes
 *   a temporary file to be created if the file cannot be cached. Identical to the preferred value
 *   INTERNET_FLAG_NEED_FILE. INTERNET_FLAG_NEED_FILE Causes a temporary file to be created if the
 *   file cannot be cached. INTERNET_FLAG_NO_CACHE_WRITE Does not cache the data, either locally or in
 *   gateways. INTERNET_FLAG_RELOAD Forces a download of the requested file, object, or directory
 *   listing from the origin server, not from the cache. INTERNET_FLAG_RESYNCHRONIZE Causes the FTP
 *   resource to be reloaded from the server.
 * @param dwContext [in] Specifies an application-defined value that associates this search with
 *   application data. This is only used if the application has already called
 *   InternetSetStatusCallback to set up a status callback function. All status requests are handled
 *   synchronously.
 *
 * @return A handle indicates success. NULL indicates failure. To get extended error data, call
 *   GetLastError.
 *
 * Inetftp.dll is available only for Intel x86 processors.
 *
 * FtpOpenFile should be used in the following situations:
 *
 * An application has data it needs to send to an FTP server to be created as a file on the FTP
 * server, but the application does not have a local file containing the data. After the file is
 * opened with FtpOpenFile, the application uses InternetWriteFile to send the FTP file data to the
 * server.
 *
 * An application needs to retrieve a file from the server into application-controlled memory,
 * instead of writing the file to disk. The application uses InternetReadFile after using
 * FtpOpenFile to open the file.
 *
 * An application needs a fine level of control over a file transfer. For example, the application
 * may need to display a progress indicator when downloading a file to indicate to the user that the
 * file transfer is, or is not, proceeding correctly.
 *
 * After calling FtpOpenFile and until calling InternetCloseHandle, all other calls to FTP functions
 * on the same FTP session handle will fail and set the error message to
 * ERROR_FTP_TRANSFER_IN_PROGRESS.
 *
 * Only one file can be open in a single FTP session. Therefore, no file handle is returned and the
 * application simply uses the FTP session handle when necessary.
 *
 * The lpszFile parameter can be either partially or fully qualified file names relative to the
 * current directory. A backward slash (\) or forward slash (/) can be used as the directory
 * separator for either name. FtpOpenFile translates the directory name separators to the
 * appropriate character before they are used.
 *
 * The InternetCloseHandle function is used to close the handle returned by FtpOpenFile. If
 * InternetCloseHandle closes the handle before all the data has been transferred, the transfer is
 * terminated.
 */
#define FtpOpenFile  FtpOpenFileW
#else
/**
 * This function initiates access to a remote file for writing or reading.
 *
 * @param hConnect [in] Valid handle to an FTP session.
 * @param lpszFileName [in] Long pointer to a null-terminated string that contains the name of the
 *   file to access on the remote system.
 * @param fdwAccess [in] Value that determines how the file will be accessed. This can be
 *   GENERIC_READ or GENERIC_WRITE, but not both.
 * @param dwFlags [in] Specifies the conditions under which the transfers occur. The application
 *   should select one transfer type and flags that control file caching. The transfer type can be one
 *   of the following values: Value Description FTP_TRANSFER_TYPE_ASCII Transfers the file using FTP
 *   ASCII, Type A, transfer method. Control and formatting data is converted to local equivalents.
 *   FTP_TRANSFER_TYPE_BINARY Transfers the file using FTP Image, Type I, transfer method. The file is
 *   transferred exactly as it exists with no changes. This is the default transfer method.
 *   FTP_TRANSFER_TYPE_UNKNOWN Defaults to FTP_TRANSFER_TYPE_BINARY. INTERNET_FLAG_TRANSFER_ASCII
 *   Transfers the file as ASCII. INTERNET_FLAG_TRANSFER_BINARY Transfers the file as binary. One or
 *   more of the values described in the following table are used by an application to control file
 *   caching. INTERNET_FLAG_DONT_CACHE Does not cache the data, either locally or in gateways.
 *   Identical to the preferred value INTERNET_FLAG_NO_CACHE_WRITE. INTERNET_FLAG_HYPERLINK Forces a
 *   reload if there was no Expires time and no Last-Modified time returned by the server when
 *   determining whether to reload the item from the network. INTERNET_FLAG_MUST_CACHE_REQUEST Causes
 *   a temporary file to be created if the file cannot be cached. Identical to the preferred value
 *   INTERNET_FLAG_NEED_FILE. INTERNET_FLAG_NEED_FILE Causes a temporary file to be created if the
 *   file cannot be cached. INTERNET_FLAG_NO_CACHE_WRITE Does not cache the data, either locally or in
 *   gateways. INTERNET_FLAG_RELOAD Forces a download of the requested file, object, or directory
 *   listing from the origin server, not from the cache. INTERNET_FLAG_RESYNCHRONIZE Causes the FTP
 *   resource to be reloaded from the server.
 * @param dwContext [in] Specifies an application-defined value that associates this search with
 *   application data. This is only used if the application has already called
 *   InternetSetStatusCallback to set up a status callback function. All status requests are handled
 *   synchronously.
 *
 * @return A handle indicates success. NULL indicates failure. To get extended error data, call
 *   GetLastError.
 *
 * Inetftp.dll is available only for Intel x86 processors.
 *
 * FtpOpenFile should be used in the following situations:
 *
 * An application has data it needs to send to an FTP server to be created as a file on the FTP
 * server, but the application does not have a local file containing the data. After the file is
 * opened with FtpOpenFile, the application uses InternetWriteFile to send the FTP file data to the
 * server.
 *
 * An application needs to retrieve a file from the server into application-controlled memory,
 * instead of writing the file to disk. The application uses InternetReadFile after using
 * FtpOpenFile to open the file.
 *
 * An application needs a fine level of control over a file transfer. For example, the application
 * may need to display a progress indicator when downloading a file to indicate to the user that the
 * file transfer is, or is not, proceeding correctly.
 *
 * After calling FtpOpenFile and until calling InternetCloseHandle, all other calls to FTP functions
 * on the same FTP session handle will fail and set the error message to
 * ERROR_FTP_TRANSFER_IN_PROGRESS.
 *
 * Only one file can be open in a single FTP session. Therefore, no file handle is returned and the
 * application simply uses the FTP session handle when necessary.
 *
 * The lpszFile parameter can be either partially or fully qualified file names relative to the
 * current directory. A backward slash (\) or forward slash (/) can be used as the directory
 * separator for either name. FtpOpenFile translates the directory name separators to the
 * appropriate character before they are used.
 *
 * The InternetCloseHandle function is used to close the handle returned by FtpOpenFile. If
 * InternetCloseHandle closes the handle before all the data has been transferred, the transfer is
 * terminated.
 */
#define FtpOpenFile  FtpOpenFileA
#endif // !UNICODE

/**
 * This function creates a new directory on the FTP server.
 *
 * @param hConnect [in] Valid handle to an FTP session. This handle must have been returned by a
 *   previous call to the InternetConnect function.
 * @param lpszDirectory [in] Long pointer to a null-terminated string that contains the name of the
 *   directory to create on the remote system. This can be either a fully qualified path or a name
 *   relative to the current directory.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error data, call
 *   GetLastError. If the error message indicates that the FTP server denied the request to create a
 *   directory, use the InternetGetLastResponseInfo function to determine the cause.
 *
 * Inetftp.dll is available only for Intel x86 processors.
 *
 * An application should use the FtpGetCurrentDirectory function to determine the remote site's
 * current working directory, instead of assuming that the remote system uses a hierarchical naming
 * scheme for directories.
 *
 * The lpszDirectory parameter can be either partially or fully qualified file names relative to the
 * current directory. A backward slash (\) or forward slash (/) can be used as the directory
 * separator for either name. FtpCreateDirectory translates the directory name separators to the
 * appropriate character before they are used.
 */
INTERNETAPI
BOOL
WINAPI
FtpCreateDirectoryA(
    IN HINTERNET hConnect,
    IN LPCSTR lpszDirectory
    );
/**
 * This function creates a new directory on the FTP server.
 *
 * @param hConnect [in] Valid handle to an FTP session. This handle must have been returned by a
 *   previous call to the InternetConnect function.
 * @param lpszDirectory [in] Long pointer to a null-terminated string that contains the name of the
 *   directory to create on the remote system. This can be either a fully qualified path or a name
 *   relative to the current directory.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error data, call
 *   GetLastError. If the error message indicates that the FTP server denied the request to create a
 *   directory, use the InternetGetLastResponseInfo function to determine the cause.
 *
 * Inetftp.dll is available only for Intel x86 processors.
 *
 * An application should use the FtpGetCurrentDirectory function to determine the remote site's
 * current working directory, instead of assuming that the remote system uses a hierarchical naming
 * scheme for directories.
 *
 * The lpszDirectory parameter can be either partially or fully qualified file names relative to the
 * current directory. A backward slash (\) or forward slash (/) can be used as the directory
 * separator for either name. FtpCreateDirectory translates the directory name separators to the
 * appropriate character before they are used.
 */
INTERNETAPI
BOOL
WINAPI
FtpCreateDirectoryW(
    IN HINTERNET hConnect,
    IN LPCWSTR lpszDirectory
    );
#ifdef UNICODE
/**
 * This function creates a new directory on the FTP server.
 *
 * @param hConnect [in] Valid handle to an FTP session. This handle must have been returned by a
 *   previous call to the InternetConnect function.
 * @param lpszDirectory [in] Long pointer to a null-terminated string that contains the name of the
 *   directory to create on the remote system. This can be either a fully qualified path or a name
 *   relative to the current directory.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error data, call
 *   GetLastError. If the error message indicates that the FTP server denied the request to create a
 *   directory, use the InternetGetLastResponseInfo function to determine the cause.
 *
 * Inetftp.dll is available only for Intel x86 processors.
 *
 * An application should use the FtpGetCurrentDirectory function to determine the remote site's
 * current working directory, instead of assuming that the remote system uses a hierarchical naming
 * scheme for directories.
 *
 * The lpszDirectory parameter can be either partially or fully qualified file names relative to the
 * current directory. A backward slash (\) or forward slash (/) can be used as the directory
 * separator for either name. FtpCreateDirectory translates the directory name separators to the
 * appropriate character before they are used.
 */
#define FtpCreateDirectory  FtpCreateDirectoryW
#else
/**
 * This function creates a new directory on the FTP server.
 *
 * @param hConnect [in] Valid handle to an FTP session. This handle must have been returned by a
 *   previous call to the InternetConnect function.
 * @param lpszDirectory [in] Long pointer to a null-terminated string that contains the name of the
 *   directory to create on the remote system. This can be either a fully qualified path or a name
 *   relative to the current directory.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error data, call
 *   GetLastError. If the error message indicates that the FTP server denied the request to create a
 *   directory, use the InternetGetLastResponseInfo function to determine the cause.
 *
 * Inetftp.dll is available only for Intel x86 processors.
 *
 * An application should use the FtpGetCurrentDirectory function to determine the remote site's
 * current working directory, instead of assuming that the remote system uses a hierarchical naming
 * scheme for directories.
 *
 * The lpszDirectory parameter can be either partially or fully qualified file names relative to the
 * current directory. A backward slash (\) or forward slash (/) can be used as the directory
 * separator for either name. FtpCreateDirectory translates the directory name separators to the
 * appropriate character before they are used.
 */
#define FtpCreateDirectory  FtpCreateDirectoryA
#endif // !UNICODE

/**
 * This function removes the specified directory on the FTP server.
 *
 * @param hConnect [in] Valid handle to an FTP session.
 * @param lpszDirectory [in] Long pointer to a null-terminated string that contains the name of the
 *   directory to remove on the remote system. This can be either a fully qualified path or a name
 *   relative to the current directory.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error data, call
 *   GetLastError. If the error message indicates that the FTP server denied the request to remove a
 *   directory, use InternetGetLastResponseInfo to determine the cause.
 *
 * Inetftp.dll is available only for Intel x86 processors.
 *
 * An application should use the FtpGetCurrentDirectory function to determine the remote site's
 * current working directory, instead of assuming that the remote system uses a hierarchical naming
 * scheme for directories.
 *
 * The lpszDirectory parameter can be either partially or fully qualified file names relative to the
 * current directory. A backward slash (\) or forward slash (/) can be used as the directory
 * separator for either name. FtpRemoveDirectory translates the directory name separators to the
 * appropriate character before they are used.
 */
INTERNETAPI
BOOL
WINAPI
FtpRemoveDirectoryA(
    IN HINTERNET hConnect,
    IN LPCSTR lpszDirectory
    );
/**
 * This function removes the specified directory on the FTP server.
 *
 * @param hConnect [in] Valid handle to an FTP session.
 * @param lpszDirectory [in] Long pointer to a null-terminated string that contains the name of the
 *   directory to remove on the remote system. This can be either a fully qualified path or a name
 *   relative to the current directory.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error data, call
 *   GetLastError. If the error message indicates that the FTP server denied the request to remove a
 *   directory, use InternetGetLastResponseInfo to determine the cause.
 *
 * Inetftp.dll is available only for Intel x86 processors.
 *
 * An application should use the FtpGetCurrentDirectory function to determine the remote site's
 * current working directory, instead of assuming that the remote system uses a hierarchical naming
 * scheme for directories.
 *
 * The lpszDirectory parameter can be either partially or fully qualified file names relative to the
 * current directory. A backward slash (\) or forward slash (/) can be used as the directory
 * separator for either name. FtpRemoveDirectory translates the directory name separators to the
 * appropriate character before they are used.
 */
INTERNETAPI
BOOL
WINAPI
FtpRemoveDirectoryW(
    IN HINTERNET hConnect,
    IN LPCWSTR lpszDirectory
    );
#ifdef UNICODE
/**
 * This function removes the specified directory on the FTP server.
 *
 * @param hConnect [in] Valid handle to an FTP session.
 * @param lpszDirectory [in] Long pointer to a null-terminated string that contains the name of the
 *   directory to remove on the remote system. This can be either a fully qualified path or a name
 *   relative to the current directory.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error data, call
 *   GetLastError. If the error message indicates that the FTP server denied the request to remove a
 *   directory, use InternetGetLastResponseInfo to determine the cause.
 *
 * Inetftp.dll is available only for Intel x86 processors.
 *
 * An application should use the FtpGetCurrentDirectory function to determine the remote site's
 * current working directory, instead of assuming that the remote system uses a hierarchical naming
 * scheme for directories.
 *
 * The lpszDirectory parameter can be either partially or fully qualified file names relative to the
 * current directory. A backward slash (\) or forward slash (/) can be used as the directory
 * separator for either name. FtpRemoveDirectory translates the directory name separators to the
 * appropriate character before they are used.
 */
#define FtpRemoveDirectory  FtpRemoveDirectoryW
#else
/**
 * This function removes the specified directory on the FTP server.
 *
 * @param hConnect [in] Valid handle to an FTP session.
 * @param lpszDirectory [in] Long pointer to a null-terminated string that contains the name of the
 *   directory to remove on the remote system. This can be either a fully qualified path or a name
 *   relative to the current directory.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error data, call
 *   GetLastError. If the error message indicates that the FTP server denied the request to remove a
 *   directory, use InternetGetLastResponseInfo to determine the cause.
 *
 * Inetftp.dll is available only for Intel x86 processors.
 *
 * An application should use the FtpGetCurrentDirectory function to determine the remote site's
 * current working directory, instead of assuming that the remote system uses a hierarchical naming
 * scheme for directories.
 *
 * The lpszDirectory parameter can be either partially or fully qualified file names relative to the
 * current directory. A backward slash (\) or forward slash (/) can be used as the directory
 * separator for either name. FtpRemoveDirectory translates the directory name separators to the
 * appropriate character before they are used.
 */
#define FtpRemoveDirectory  FtpRemoveDirectoryA
#endif // !UNICODE

/**
 * This function changes to a different working directory on the FTP server.
 *
 * @param hConnect [in] Valid handle to an FTP session.
 * @param lpszDirectory [in] Long pointer to a null-terminated string that contains the name of the
 *   directory to change to on the remote system. This can be either a fully qualified path or a name
 *   relative to the current directory.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error data, call
 *   GetLastError. If the error message indicates that the FTP server denied the request to remove a
 *   directory, use InternetGetLastResponseInfo to determine the cause.
 *
 * Inetftp.dll is available only for Intel x86 processors.
 *
 * An application should use the FtpGetCurrentDirectory function to determine the remote site's
 * current working directory, instead of assuming that the remote system uses a hierarchical naming
 * scheme for directories.
 *
 * The lpszDirectory parameter can be either partially or fully qualified file names relative to the
 * current directory. A backward slash (\) or forward slash (/) can be used as the directory
 * separator for either name. FtpSetCurrentDirectory translates the directory name separators to the
 * appropriate character before they are used.
 */
INTERNETAPI
BOOL
WINAPI
FtpSetCurrentDirectoryA(
    IN HINTERNET hConnect,
    IN LPCSTR lpszDirectory
    );
/**
 * This function changes to a different working directory on the FTP server.
 *
 * @param hConnect [in] Valid handle to an FTP session.
 * @param lpszDirectory [in] Long pointer to a null-terminated string that contains the name of the
 *   directory to change to on the remote system. This can be either a fully qualified path or a name
 *   relative to the current directory.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error data, call
 *   GetLastError. If the error message indicates that the FTP server denied the request to remove a
 *   directory, use InternetGetLastResponseInfo to determine the cause.
 *
 * Inetftp.dll is available only for Intel x86 processors.
 *
 * An application should use the FtpGetCurrentDirectory function to determine the remote site's
 * current working directory, instead of assuming that the remote system uses a hierarchical naming
 * scheme for directories.
 *
 * The lpszDirectory parameter can be either partially or fully qualified file names relative to the
 * current directory. A backward slash (\) or forward slash (/) can be used as the directory
 * separator for either name. FtpSetCurrentDirectory translates the directory name separators to the
 * appropriate character before they are used.
 */
INTERNETAPI
BOOL
WINAPI
FtpSetCurrentDirectoryW(
    IN HINTERNET hConnect,
    IN LPCWSTR lpszDirectory
    );
#ifdef UNICODE
/**
 * This function changes to a different working directory on the FTP server.
 *
 * @param hConnect [in] Valid handle to an FTP session.
 * @param lpszDirectory [in] Long pointer to a null-terminated string that contains the name of the
 *   directory to change to on the remote system. This can be either a fully qualified path or a name
 *   relative to the current directory.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error data, call
 *   GetLastError. If the error message indicates that the FTP server denied the request to remove a
 *   directory, use InternetGetLastResponseInfo to determine the cause.
 *
 * Inetftp.dll is available only for Intel x86 processors.
 *
 * An application should use the FtpGetCurrentDirectory function to determine the remote site's
 * current working directory, instead of assuming that the remote system uses a hierarchical naming
 * scheme for directories.
 *
 * The lpszDirectory parameter can be either partially or fully qualified file names relative to the
 * current directory. A backward slash (\) or forward slash (/) can be used as the directory
 * separator for either name. FtpSetCurrentDirectory translates the directory name separators to the
 * appropriate character before they are used.
 */
#define FtpSetCurrentDirectory  FtpSetCurrentDirectoryW
#else
/**
 * This function changes to a different working directory on the FTP server.
 *
 * @param hConnect [in] Valid handle to an FTP session.
 * @param lpszDirectory [in] Long pointer to a null-terminated string that contains the name of the
 *   directory to change to on the remote system. This can be either a fully qualified path or a name
 *   relative to the current directory.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error data, call
 *   GetLastError. If the error message indicates that the FTP server denied the request to remove a
 *   directory, use InternetGetLastResponseInfo to determine the cause.
 *
 * Inetftp.dll is available only for Intel x86 processors.
 *
 * An application should use the FtpGetCurrentDirectory function to determine the remote site's
 * current working directory, instead of assuming that the remote system uses a hierarchical naming
 * scheme for directories.
 *
 * The lpszDirectory parameter can be either partially or fully qualified file names relative to the
 * current directory. A backward slash (\) or forward slash (/) can be used as the directory
 * separator for either name. FtpSetCurrentDirectory translates the directory name separators to the
 * appropriate character before they are used.
 */
#define FtpSetCurrentDirectory  FtpSetCurrentDirectoryA
#endif // !UNICODE

/**
 * This function retrieves the current directory for the specified FTP session.
 *
 * @param hConnect [in] Valid handle to an FTP session.
 * @param lpszCurrentDirectory [out] Long pointer to a buffer that receives the null-terminated
 *   string that contains the absolute path to the current directory.
 * @param lpdwCurrentDirectory [in/out] Long pointer to a variable that specifies the buffer length,
 *   in characters, for the current directory string. The buffer length must include room for a
 *   terminating null character. Using a length of MAX_PATH is sufficient for all paths. When the
 *   function returns, the variable receives the number of characters copied into the buffer.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error data, call
 *   GetLastError.
 *
 * Inetftp.dll is available only for Intel x86 processors.
 *
 * If the lpszCurrentDirectory buffer is not large enough, lpdwCurrentDirectory receives the number
 * of bytes required to retrieve the full, current directory name.
 */
INTERNETAPI
BOOL
WINAPI
FtpGetCurrentDirectoryA(
    IN HINTERNET hConnect,
    OUT LPSTR lpszCurrentDirectory,
    IN OUT LPDWORD lpdwCurrentDirectory
    );
/**
 * This function retrieves the current directory for the specified FTP session.
 *
 * @param hConnect [in] Valid handle to an FTP session.
 * @param lpszCurrentDirectory [out] Long pointer to a buffer that receives the null-terminated
 *   string that contains the absolute path to the current directory.
 * @param lpdwCurrentDirectory [in/out] Long pointer to a variable that specifies the buffer length,
 *   in characters, for the current directory string. The buffer length must include room for a
 *   terminating null character. Using a length of MAX_PATH is sufficient for all paths. When the
 *   function returns, the variable receives the number of characters copied into the buffer.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error data, call
 *   GetLastError.
 *
 * Inetftp.dll is available only for Intel x86 processors.
 *
 * If the lpszCurrentDirectory buffer is not large enough, lpdwCurrentDirectory receives the number
 * of bytes required to retrieve the full, current directory name.
 */
INTERNETAPI
BOOL
WINAPI
FtpGetCurrentDirectoryW(
    IN HINTERNET hConnect,
    OUT LPWSTR lpszCurrentDirectory,
    IN OUT LPDWORD lpdwCurrentDirectory
    );
#ifdef UNICODE
/**
 * This function retrieves the current directory for the specified FTP session.
 *
 * @param hConnect [in] Valid handle to an FTP session.
 * @param lpszCurrentDirectory [out] Long pointer to a buffer that receives the null-terminated
 *   string that contains the absolute path to the current directory.
 * @param lpdwCurrentDirectory [in/out] Long pointer to a variable that specifies the buffer length,
 *   in characters, for the current directory string. The buffer length must include room for a
 *   terminating null character. Using a length of MAX_PATH is sufficient for all paths. When the
 *   function returns, the variable receives the number of characters copied into the buffer.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error data, call
 *   GetLastError.
 *
 * Inetftp.dll is available only for Intel x86 processors.
 *
 * If the lpszCurrentDirectory buffer is not large enough, lpdwCurrentDirectory receives the number
 * of bytes required to retrieve the full, current directory name.
 */
#define FtpGetCurrentDirectory  FtpGetCurrentDirectoryW
#else
/**
 * This function retrieves the current directory for the specified FTP session.
 *
 * @param hConnect [in] Valid handle to an FTP session.
 * @param lpszCurrentDirectory [out] Long pointer to a buffer that receives the null-terminated
 *   string that contains the absolute path to the current directory.
 * @param lpdwCurrentDirectory [in/out] Long pointer to a variable that specifies the buffer length,
 *   in characters, for the current directory string. The buffer length must include room for a
 *   terminating null character. Using a length of MAX_PATH is sufficient for all paths. When the
 *   function returns, the variable receives the number of characters copied into the buffer.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error data, call
 *   GetLastError.
 *
 * Inetftp.dll is available only for Intel x86 processors.
 *
 * If the lpszCurrentDirectory buffer is not large enough, lpdwCurrentDirectory receives the number
 * of bytes required to retrieve the full, current directory name.
 */
#define FtpGetCurrentDirectory  FtpGetCurrentDirectoryA
#endif // !UNICODE

/**
 * This function issues an arbitrary FTP command to the FTP server.
 *
 * @param hConnect [in] Valid handle for an FTP session.
 * @param fExpectResponse [in] Boolean that specifies if a data response is expected. If
 *   fExpectResponse is TRUE, a data response is expected, and the application can call the
 *   InternetReadFile function to read the response.
 * @param dwFlag [in] Specifies the conditions under which the data connection takes place. The
 *   following flags can be set: Value Description FTP_TRANSFER_TYPE_ASCII Data connection using the
 *   FTP ASCII ,Type A, transfer method. Control and formatting data is converted to local
 *   equivalents. FTP_TRANSFER_TYPE_BINARY Data connection using the FTP Image, Type I, transfer
 *   method. The file is transferred exactly as it exists with no changes. This is the default
 *   transfer method.
 * @param LpszCommand [in] Long pointer to the null-terminated string that contains an FTP command,
 *   for example, "PWD \r\n".
 * @param dwContext [in] Specifies an application-defined value that associates the FTP command in a
 *   status callback.
 *
 * Inetftp.dll is available only for Intel x86 processors.
 *
 * The dwContext parameter accepts status callbacks to the application, but all requests are handled
 * synchronously.
 */
INTERNETAPI
BOOL
WINAPI
FtpCommandA(
    IN HINTERNET hConnect,
    IN BOOL fExpectResponse,
    IN DWORD dwFlags,
    IN LPCSTR lpszCommand,
    IN DWORD dwContext
    );
/**
 * This function issues an arbitrary FTP command to the FTP server.
 *
 * @param hConnect [in] Valid handle for an FTP session.
 * @param fExpectResponse [in] Boolean that specifies if a data response is expected. If
 *   fExpectResponse is TRUE, a data response is expected, and the application can call the
 *   InternetReadFile function to read the response.
 * @param dwFlag [in] Specifies the conditions under which the data connection takes place. The
 *   following flags can be set: Value Description FTP_TRANSFER_TYPE_ASCII Data connection using the
 *   FTP ASCII ,Type A, transfer method. Control and formatting data is converted to local
 *   equivalents. FTP_TRANSFER_TYPE_BINARY Data connection using the FTP Image, Type I, transfer
 *   method. The file is transferred exactly as it exists with no changes. This is the default
 *   transfer method.
 * @param LpszCommand [in] Long pointer to the null-terminated string that contains an FTP command,
 *   for example, "PWD \r\n".
 * @param dwContext [in] Specifies an application-defined value that associates the FTP command in a
 *   status callback.
 *
 * Inetftp.dll is available only for Intel x86 processors.
 *
 * The dwContext parameter accepts status callbacks to the application, but all requests are handled
 * synchronously.
 */
INTERNETAPI
BOOL
WINAPI
FtpCommandW(
    IN HINTERNET hConnect,
    IN BOOL fExpectResponse,
    IN DWORD dwFlags,
    IN LPCWSTR lpszCommand,
    IN DWORD dwContext
    );
#ifdef UNICODE
/**
 * This function issues an arbitrary FTP command to the FTP server.
 *
 * @param hConnect [in] Valid handle for an FTP session.
 * @param fExpectResponse [in] Boolean that specifies if a data response is expected. If
 *   fExpectResponse is TRUE, a data response is expected, and the application can call the
 *   InternetReadFile function to read the response.
 * @param dwFlag [in] Specifies the conditions under which the data connection takes place. The
 *   following flags can be set: Value Description FTP_TRANSFER_TYPE_ASCII Data connection using the
 *   FTP ASCII ,Type A, transfer method. Control and formatting data is converted to local
 *   equivalents. FTP_TRANSFER_TYPE_BINARY Data connection using the FTP Image, Type I, transfer
 *   method. The file is transferred exactly as it exists with no changes. This is the default
 *   transfer method.
 * @param LpszCommand [in] Long pointer to the null-terminated string that contains an FTP command,
 *   for example, "PWD \r\n".
 * @param dwContext [in] Specifies an application-defined value that associates the FTP command in a
 *   status callback.
 *
 * Inetftp.dll is available only for Intel x86 processors.
 *
 * The dwContext parameter accepts status callbacks to the application, but all requests are handled
 * synchronously.
 */
#define FtpCommand  FtpCommandW
#else
/**
 * This function issues an arbitrary FTP command to the FTP server.
 *
 * @param hConnect [in] Valid handle for an FTP session.
 * @param fExpectResponse [in] Boolean that specifies if a data response is expected. If
 *   fExpectResponse is TRUE, a data response is expected, and the application can call the
 *   InternetReadFile function to read the response.
 * @param dwFlag [in] Specifies the conditions under which the data connection takes place. The
 *   following flags can be set: Value Description FTP_TRANSFER_TYPE_ASCII Data connection using the
 *   FTP ASCII ,Type A, transfer method. Control and formatting data is converted to local
 *   equivalents. FTP_TRANSFER_TYPE_BINARY Data connection using the FTP Image, Type I, transfer
 *   method. The file is transferred exactly as it exists with no changes. This is the default
 *   transfer method.
 * @param LpszCommand [in] Long pointer to the null-terminated string that contains an FTP command,
 *   for example, "PWD \r\n".
 * @param dwContext [in] Specifies an application-defined value that associates the FTP command in a
 *   status callback.
 *
 * Inetftp.dll is available only for Intel x86 processors.
 *
 * The dwContext parameter accepts status callbacks to the application, but all requests are handled
 * synchronously.
 */
#define FtpCommand  FtpCommandA
#endif // !UNICODE

// @CESYSGEN ENDIF

//
// HTTP
//

//
// manifests
//

//
// the default major/minor HTTP version numbers
//

#define HTTP_MAJOR_VERSION      1
#define HTTP_MINOR_VERSION      0

#define HTTP_VERSION            TEXT("HTTP/1.0")

//
// HttpQueryInfo info levels. Generally, there is one info level
// for each potential RFC822/HTTP/MIME header that an HTTP server
// may send as part of a request response.
//
// The HTTP_QUERY_RAW_HEADERS info level is provided for clients
// that choose to perform their own header parsing.
//

#define HTTP_QUERY_MIME_VERSION                 0
#define HTTP_QUERY_CONTENT_TYPE                 1
#define HTTP_QUERY_CONTENT_TRANSFER_ENCODING    2
#define HTTP_QUERY_CONTENT_ID                   3
#define HTTP_QUERY_CONTENT_DESCRIPTION          4
#define HTTP_QUERY_CONTENT_LENGTH               5
#define HTTP_QUERY_CONTENT_LANGUAGE             6
#define HTTP_QUERY_ALLOW                        7
#define HTTP_QUERY_PUBLIC                       8
#define HTTP_QUERY_DATE                         9
#define HTTP_QUERY_EXPIRES                      10
#define HTTP_QUERY_LAST_MODIFIED                11
#define HTTP_QUERY_MESSAGE_ID                   12
#define HTTP_QUERY_URI                          13
#define HTTP_QUERY_DERIVED_FROM                 14
#define HTTP_QUERY_COST                         15
#define HTTP_QUERY_LINK                         16
#define HTTP_QUERY_PRAGMA                       17
#define HTTP_QUERY_VERSION                      18  // special: part of status line
#define HTTP_QUERY_STATUS_CODE                  19  // special: part of status line
#define HTTP_QUERY_STATUS_TEXT                  20  // special: part of status line
#define HTTP_QUERY_RAW_HEADERS                  21  // special: all headers as ASCIIZ
#define HTTP_QUERY_RAW_HEADERS_CRLF             22  // special: all headers
#define HTTP_QUERY_CONNECTION                   23
#define HTTP_QUERY_ACCEPT                       24
#define HTTP_QUERY_ACCEPT_CHARSET               25
#define HTTP_QUERY_ACCEPT_ENCODING              26
#define HTTP_QUERY_ACCEPT_LANGUAGE              27
#define HTTP_QUERY_AUTHORIZATION                28
#define HTTP_QUERY_CONTENT_ENCODING             29
#define HTTP_QUERY_FORWARDED                    30
#define HTTP_QUERY_FROM                         31
#define HTTP_QUERY_IF_MODIFIED_SINCE            32
#define HTTP_QUERY_LOCATION                     33
#define HTTP_QUERY_ORIG_URI                     34
#define HTTP_QUERY_REFERER                      35
#define HTTP_QUERY_RETRY_AFTER                  36
#define HTTP_QUERY_SERVER                       37
#define HTTP_QUERY_TITLE                        38
#define HTTP_QUERY_USER_AGENT                   39
#define HTTP_QUERY_WWW_AUTHENTICATE             40
#define HTTP_QUERY_PROXY_AUTHENTICATE           41
#define HTTP_QUERY_ACCEPT_RANGES                42
#define HTTP_QUERY_SET_COOKIE                   43
#define HTTP_QUERY_COOKIE                       44
#define HTTP_QUERY_REQUEST_METHOD               45  // special: GET/POST etc.

#define HTTP_QUERY_MAX                          45

//
// HTTP_QUERY_CUSTOM - if this special value is supplied as the dwInfoLevel
// parameter of HttpQueryInfo() then the lpBuffer parameter contains the name
// of the header we are to query
//

#define HTTP_QUERY_CUSTOM                       65535

//
// HTTP_QUERY_FLAG_REQUEST_HEADERS - if this bit is set in the dwInfoLevel
// parameter of HttpQueryInfo() then the request headers will be queried for the
// request information
//

#define HTTP_QUERY_FLAG_REQUEST_HEADERS         0x80000000

//
// HTTP_QUERY_FLAG_SYSTEMTIME - if this bit is set in the dwInfoLevel parameter
// of HttpQueryInfo() AND the header being queried contains date information,
// e.g. the "Expires:" header then lpBuffer will contain a SYSTEMTIME structure
// containing the date and time information converted from the header string
//

#define HTTP_QUERY_FLAG_SYSTEMTIME              0x40000000

//
// HTTP_QUERY_FLAG_NUMBER - if this bit is set in the dwInfoLevel parameter of
// HttpQueryInfo(), then the value of the header will be converted to a number
// before being returned to the caller, if applicable
//

#define HTTP_QUERY_FLAG_NUMBER                  0x20000000

//
// HTTP_QUERY_FLAG_COALESCE - combine the values from several headers of the
// same name into the output buffer
//

#define HTTP_QUERY_FLAG_COALESCE                0x10000000

#define HTTP_QUERY_MODIFIER_FLAGS_MASK          (HTTP_QUERY_FLAG_REQUEST_HEADERS    \
                                                | HTTP_QUERY_FLAG_SYSTEMTIME        \
                                                | HTTP_QUERY_FLAG_NUMBER            \
                                                | HTTP_QUERY_FLAG_COALESCE          \
                                                )

#define HTTP_QUERY_HEADER_MASK                  (~HTTP_QUERY_MODIFIER_FLAGS_MASK)

//
// HTTP Response Status Codes:
//

#define HTTP_STATUS_OK              200     // request completed
#define HTTP_STATUS_CREATED         201     // object created, reason = new URI
#define HTTP_STATUS_ACCEPTED        202     // async completion (TBS)
#define HTTP_STATUS_PARTIAL         203     // partial completion
#define HTTP_STATUS_NO_CONTENT      204     // no info to return

#define HTTP_STATUS_AMBIGUOUS       300     // server couldn't decide what to return
#define HTTP_STATUS_MOVED           301     // object permanently moved
#define HTTP_STATUS_REDIRECT        302     // object temporarily moved
#define HTTP_STATUS_REDIRECT_METHOD 303     // redirection w/ new access method
#define HTTP_STATUS_NOT_MODIFIED    304     // if-modified-since was not modified

#define HTTP_STATUS_BAD_REQUEST     400     // invalid syntax
#define HTTP_STATUS_DENIED          401     // access denied
#define HTTP_STATUS_PAYMENT_REQ     402     // payment required
#define HTTP_STATUS_FORBIDDEN       403     // request forbidden
#define HTTP_STATUS_NOT_FOUND       404     // object not found
#define HTTP_STATUS_BAD_METHOD      405     // method is not allowed
#define HTTP_STATUS_NONE_ACCEPTABLE 406     // no response acceptable to client found
#define HTTP_STATUS_PROXY_AUTH_REQ  407     // proxy authentication required
#define HTTP_STATUS_REQUEST_TIMEOUT 408     // server timed out waiting for request
#define HTTP_STATUS_CONFLICT        409     // user should resubmit with more info
#define HTTP_STATUS_GONE            410     // the resource is no longer available
#define HTTP_STATUS_AUTH_REFUSED    411     // couldn't authorize client

#define HTTP_STATUS_SERVER_ERROR    500     // internal server error
#define HTTP_STATUS_NOT_SUPPORTED   501     // required not supported
#define HTTP_STATUS_BAD_GATEWAY     502     // error response received from gateway
#define HTTP_STATUS_SERVICE_UNAVAIL 503     // temporarily overloaded
#define HTTP_STATUS_GATEWAY_TIMEOUT 504     // timed out waiting for gateway

//
// prototypes
//

/**
 * This function opens an HTTP request handle.
 *
 * @param hHttpSession [in] Handle to an HTTP session returned by InternetConnect.
 * @param lpszVerb [in] Long pointer to a null-terminated string that contains the verb to use in
 *   the request. If this parameter is NULL, the function uses "GET" as the verb.
 * @param lpszObjectName [in] Long pointer to a null-terminated string that contains the name of the
 *   target object of the specified verb. This is generally a file name, an executable module, or a
 *   search specifier.
 * @param lpszVersion [in] Long pointer to a null-terminated string that contains the HTTP version.
 *   If this parameter is NULL, the function uses "HTTP/1.0" as the version.
 * @param lpszReferer [in] Long pointer to a null-terminated string that specifies the address (URL)
 *   of the document from which the URL in the request (lpszObjectName) was obtained. If this
 *   parameter is NULL, no "referrer" is specified.
 * @param lplpszAcceptTypes [in] Long pointer to a null-terminated array of string pointers
 *   indicating content types accepted by the client. If this parameter is NULL, no types are accepted
 *   by the client. Servers interpret a lack of accept types to indicate that the client accepts only
 *   documents of type "text/ *" (that is, only text documents, and not pictures or other binary
 *   files).
 * @param dwFlags [in] Specifies a bitmask of Internet flags. Can be any of the following values:
 *   Value Description INTERNET_FLAG_CACHE_IF_NET_FAIL Return the resource from the cache if the
 *   network request for the resource fails due to an ERROR_INTERNET_CONNECTION_RESET or
 *   ERROR_INTERNET_CANNOT_CONNECT. INTERNET_FLAG_DONT_CACHE Not supported. Data is never cached.
 *   INTERNET_FLAG_HYPERLINK Forces a reload if there was no Expires time and no Last-Modified time
 *   returned from the server when determining whether to reload the item from the network.
 *   INTERNET_FLAG_IGNORE_CERT_CN_INVALID Disables Win32 Internet function checking of SSL/PCT-based
 *   certificates that are returned from the server against the host name given in the request. Win32
 *   Internet functions use a simple check against certificates by comparing for matching host names
 *   and simple wildcarding rules. INTERNET_FLAG_IGNORE_CERT_DATE_INVALID Disables Win32 Internet
 *   function checking of SSL/PCT-based certificates for proper validity dates.
 *   INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP Disables the ability of the Win32 Internet functions to
 *   detect this special type of redirect. When this flag is used, Win32 Internet functions
 *   transparently allow redirects from HTTPS to HTTP URLs. INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTPS
 *   Disables the ability of the Win32 Internet functions to detect this special type of redirect.
 *   When this flag is used, Win32 Internet functions transparently allow redirects from HTTP to HTTPS
 *   URLs. INTERNET_FLAG_KEEP_CONNECTION Uses keep-alive semantics, if available, for the connection.
 *   This flag is required for Microsoft Network (MSN), NT LAN Manager (NTLM), and other types of
 *   authentication. INTERNET_FLAG_MAKE_PERSISTENT Not supported. INTERNET_FLAG_MUST_CACHE_REQUEST
 *   Causes a temporary file to be created if the file cannot be cached. Identical to the preferred
 *   value INTERNET_FLAG_NEED_FILE. INTERNET_FLAG_NEED_FILE Causes a temporary file to be created if
 *   the file cannot be cached. INTERNET_FLAG_NO_AUTH Does not attempt authentication automatically.
 *   INTERNET_FLAG_NO_AUTO_REDIRECT Does not automatically handle redirection in HttpSendRequest.
 *   INTERNET_FLAG_NO_CACHE_WRITE Does not add the returned entity to the cache.
 *   INTERNET_FLAG_NO_COOKIES Does not automatically add cookie headers to requests, and does not
 *   automatically add returned cookies to the cookie database. INTERNET_FLAG_NO_UI Disables the
 *   cookie dialog box. INTERNET_FLAG_PRAGMA_NOCACHE Forces the request to be resolved by the origin
 *   server, even if a cached copy exists on the proxy. INTERNET_FLAG_READ_PREFETCH This flag is
 *   currently disabled. INTERNET_FLAG_RELOAD Not supported. Data is always from the wire and caching
 *   is not supported. INTERNET_FLAG_RESYNCHRONIZE Reloads HTTP resources if the resource has been
 *   modified since the last time it was downloaded. INTERNET_FLAG_SECURE Uses SSL/PCT transaction
 *   semantics.
 * @param dwContext [in] Specifies the application-defined value that associates this operation with
 *   any application data.
 *
 * @return A valid, non-NULL HTTP request handle indicates success. NULL indicates failure. To get
 *   extended error information, call GetLastError.
 *
 * HttpOpenRequest creates a new HTTP request handle and stores the specified parameters in that
 * handle. An HTTP request handle holds a request to be sent to an HTTP server and contains all
 * RFC822/MIME/HTTP headers to be sent as part of the request.
 *
 * Use the InternetCloseHandle function to close the handle returned by HttpOpenRequest.
 * InternetCloseHandle cancels all outstanding I/O on the handle.
 *
 * The lpszReferer parameter to InternetOpen is used as the referrer for the HTTP request.
 *
 * The dwContext parameter allows for progress status callbacks to the application, but all requests
 * will be handled synchronously.
 *
 * When establishing a Secure Sockets Layer (SSL) or Private Communications Technology,
 * HttpOpenRequest uses the INTERNET_FLAG_SECURE option in addition to all other options.
 *
 * The following dwFlags values can be used in HttpOpenRequest to ignore invalid certificate errors:
 *
 * - INTERNET_FLAG_IGNORE_CERT_CN_INVALID: Ignores errors caused when the certificate host name of
 * the server does not match the host name in the request.
 *
 * - INTERNET_FLAG_IGNORE_CERT_DATE_INVALID: Ignores errors caused by an expired server certificate.
 */
INTERNETAPI
HINTERNET
WINAPI
HttpOpenRequestA(
    IN HINTERNET hConnect,
    IN LPCSTR lpszVerb,
    IN LPCSTR lpszObjectName,
    IN LPCSTR lpszVersion,
    IN LPCSTR lpszReferrer OPTIONAL,
    IN LPCSTR FAR * lplpszAcceptTypes OPTIONAL,
    IN DWORD dwFlags,
    IN DWORD dwContext
    );
/**
 * This function opens an HTTP request handle.
 *
 * @param hHttpSession [in] Handle to an HTTP session returned by InternetConnect.
 * @param lpszVerb [in] Long pointer to a null-terminated string that contains the verb to use in
 *   the request. If this parameter is NULL, the function uses "GET" as the verb.
 * @param lpszObjectName [in] Long pointer to a null-terminated string that contains the name of the
 *   target object of the specified verb. This is generally a file name, an executable module, or a
 *   search specifier.
 * @param lpszVersion [in] Long pointer to a null-terminated string that contains the HTTP version.
 *   If this parameter is NULL, the function uses "HTTP/1.0" as the version.
 * @param lpszReferer [in] Long pointer to a null-terminated string that specifies the address (URL)
 *   of the document from which the URL in the request (lpszObjectName) was obtained. If this
 *   parameter is NULL, no "referrer" is specified.
 * @param lplpszAcceptTypes [in] Long pointer to a null-terminated array of string pointers
 *   indicating content types accepted by the client. If this parameter is NULL, no types are accepted
 *   by the client. Servers interpret a lack of accept types to indicate that the client accepts only
 *   documents of type "text/ *" (that is, only text documents, and not pictures or other binary
 *   files).
 * @param dwFlags [in] Specifies a bitmask of Internet flags. Can be any of the following values:
 *   Value Description INTERNET_FLAG_CACHE_IF_NET_FAIL Return the resource from the cache if the
 *   network request for the resource fails due to an ERROR_INTERNET_CONNECTION_RESET or
 *   ERROR_INTERNET_CANNOT_CONNECT. INTERNET_FLAG_DONT_CACHE Not supported. Data is never cached.
 *   INTERNET_FLAG_HYPERLINK Forces a reload if there was no Expires time and no Last-Modified time
 *   returned from the server when determining whether to reload the item from the network.
 *   INTERNET_FLAG_IGNORE_CERT_CN_INVALID Disables Win32 Internet function checking of SSL/PCT-based
 *   certificates that are returned from the server against the host name given in the request. Win32
 *   Internet functions use a simple check against certificates by comparing for matching host names
 *   and simple wildcarding rules. INTERNET_FLAG_IGNORE_CERT_DATE_INVALID Disables Win32 Internet
 *   function checking of SSL/PCT-based certificates for proper validity dates.
 *   INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP Disables the ability of the Win32 Internet functions to
 *   detect this special type of redirect. When this flag is used, Win32 Internet functions
 *   transparently allow redirects from HTTPS to HTTP URLs. INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTPS
 *   Disables the ability of the Win32 Internet functions to detect this special type of redirect.
 *   When this flag is used, Win32 Internet functions transparently allow redirects from HTTP to HTTPS
 *   URLs. INTERNET_FLAG_KEEP_CONNECTION Uses keep-alive semantics, if available, for the connection.
 *   This flag is required for Microsoft Network (MSN), NT LAN Manager (NTLM), and other types of
 *   authentication. INTERNET_FLAG_MAKE_PERSISTENT Not supported. INTERNET_FLAG_MUST_CACHE_REQUEST
 *   Causes a temporary file to be created if the file cannot be cached. Identical to the preferred
 *   value INTERNET_FLAG_NEED_FILE. INTERNET_FLAG_NEED_FILE Causes a temporary file to be created if
 *   the file cannot be cached. INTERNET_FLAG_NO_AUTH Does not attempt authentication automatically.
 *   INTERNET_FLAG_NO_AUTO_REDIRECT Does not automatically handle redirection in HttpSendRequest.
 *   INTERNET_FLAG_NO_CACHE_WRITE Does not add the returned entity to the cache.
 *   INTERNET_FLAG_NO_COOKIES Does not automatically add cookie headers to requests, and does not
 *   automatically add returned cookies to the cookie database. INTERNET_FLAG_NO_UI Disables the
 *   cookie dialog box. INTERNET_FLAG_PRAGMA_NOCACHE Forces the request to be resolved by the origin
 *   server, even if a cached copy exists on the proxy. INTERNET_FLAG_READ_PREFETCH This flag is
 *   currently disabled. INTERNET_FLAG_RELOAD Not supported. Data is always from the wire and caching
 *   is not supported. INTERNET_FLAG_RESYNCHRONIZE Reloads HTTP resources if the resource has been
 *   modified since the last time it was downloaded. INTERNET_FLAG_SECURE Uses SSL/PCT transaction
 *   semantics.
 * @param dwContext [in] Specifies the application-defined value that associates this operation with
 *   any application data.
 *
 * @return A valid, non-NULL HTTP request handle indicates success. NULL indicates failure. To get
 *   extended error information, call GetLastError.
 *
 * HttpOpenRequest creates a new HTTP request handle and stores the specified parameters in that
 * handle. An HTTP request handle holds a request to be sent to an HTTP server and contains all
 * RFC822/MIME/HTTP headers to be sent as part of the request.
 *
 * Use the InternetCloseHandle function to close the handle returned by HttpOpenRequest.
 * InternetCloseHandle cancels all outstanding I/O on the handle.
 *
 * The lpszReferer parameter to InternetOpen is used as the referrer for the HTTP request.
 *
 * The dwContext parameter allows for progress status callbacks to the application, but all requests
 * will be handled synchronously.
 *
 * When establishing a Secure Sockets Layer (SSL) or Private Communications Technology,
 * HttpOpenRequest uses the INTERNET_FLAG_SECURE option in addition to all other options.
 *
 * The following dwFlags values can be used in HttpOpenRequest to ignore invalid certificate errors:
 *
 * - INTERNET_FLAG_IGNORE_CERT_CN_INVALID: Ignores errors caused when the certificate host name of
 * the server does not match the host name in the request.
 *
 * - INTERNET_FLAG_IGNORE_CERT_DATE_INVALID: Ignores errors caused by an expired server certificate.
 */
INTERNETAPI
HINTERNET
WINAPI
HttpOpenRequestW(
    IN HINTERNET hConnect,
    IN LPCWSTR lpszVerb,
    IN LPCWSTR lpszObjectName,
    IN LPCWSTR lpszVersion,
    IN LPCWSTR lpszReferrer OPTIONAL,
    IN LPCWSTR FAR * lplpszAcceptTypes OPTIONAL,
    IN DWORD dwFlags,
    IN DWORD dwContext
    );
#ifdef UNICODE
/**
 * This function opens an HTTP request handle.
 *
 * @param hHttpSession [in] Handle to an HTTP session returned by InternetConnect.
 * @param lpszVerb [in] Long pointer to a null-terminated string that contains the verb to use in
 *   the request. If this parameter is NULL, the function uses "GET" as the verb.
 * @param lpszObjectName [in] Long pointer to a null-terminated string that contains the name of the
 *   target object of the specified verb. This is generally a file name, an executable module, or a
 *   search specifier.
 * @param lpszVersion [in] Long pointer to a null-terminated string that contains the HTTP version.
 *   If this parameter is NULL, the function uses "HTTP/1.0" as the version.
 * @param lpszReferer [in] Long pointer to a null-terminated string that specifies the address (URL)
 *   of the document from which the URL in the request (lpszObjectName) was obtained. If this
 *   parameter is NULL, no "referrer" is specified.
 * @param lplpszAcceptTypes [in] Long pointer to a null-terminated array of string pointers
 *   indicating content types accepted by the client. If this parameter is NULL, no types are accepted
 *   by the client. Servers interpret a lack of accept types to indicate that the client accepts only
 *   documents of type "text/ *" (that is, only text documents, and not pictures or other binary
 *   files).
 * @param dwFlags [in] Specifies a bitmask of Internet flags. Can be any of the following values:
 *   Value Description INTERNET_FLAG_CACHE_IF_NET_FAIL Return the resource from the cache if the
 *   network request for the resource fails due to an ERROR_INTERNET_CONNECTION_RESET or
 *   ERROR_INTERNET_CANNOT_CONNECT. INTERNET_FLAG_DONT_CACHE Not supported. Data is never cached.
 *   INTERNET_FLAG_HYPERLINK Forces a reload if there was no Expires time and no Last-Modified time
 *   returned from the server when determining whether to reload the item from the network.
 *   INTERNET_FLAG_IGNORE_CERT_CN_INVALID Disables Win32 Internet function checking of SSL/PCT-based
 *   certificates that are returned from the server against the host name given in the request. Win32
 *   Internet functions use a simple check against certificates by comparing for matching host names
 *   and simple wildcarding rules. INTERNET_FLAG_IGNORE_CERT_DATE_INVALID Disables Win32 Internet
 *   function checking of SSL/PCT-based certificates for proper validity dates.
 *   INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP Disables the ability of the Win32 Internet functions to
 *   detect this special type of redirect. When this flag is used, Win32 Internet functions
 *   transparently allow redirects from HTTPS to HTTP URLs. INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTPS
 *   Disables the ability of the Win32 Internet functions to detect this special type of redirect.
 *   When this flag is used, Win32 Internet functions transparently allow redirects from HTTP to HTTPS
 *   URLs. INTERNET_FLAG_KEEP_CONNECTION Uses keep-alive semantics, if available, for the connection.
 *   This flag is required for Microsoft Network (MSN), NT LAN Manager (NTLM), and other types of
 *   authentication. INTERNET_FLAG_MAKE_PERSISTENT Not supported. INTERNET_FLAG_MUST_CACHE_REQUEST
 *   Causes a temporary file to be created if the file cannot be cached. Identical to the preferred
 *   value INTERNET_FLAG_NEED_FILE. INTERNET_FLAG_NEED_FILE Causes a temporary file to be created if
 *   the file cannot be cached. INTERNET_FLAG_NO_AUTH Does not attempt authentication automatically.
 *   INTERNET_FLAG_NO_AUTO_REDIRECT Does not automatically handle redirection in HttpSendRequest.
 *   INTERNET_FLAG_NO_CACHE_WRITE Does not add the returned entity to the cache.
 *   INTERNET_FLAG_NO_COOKIES Does not automatically add cookie headers to requests, and does not
 *   automatically add returned cookies to the cookie database. INTERNET_FLAG_NO_UI Disables the
 *   cookie dialog box. INTERNET_FLAG_PRAGMA_NOCACHE Forces the request to be resolved by the origin
 *   server, even if a cached copy exists on the proxy. INTERNET_FLAG_READ_PREFETCH This flag is
 *   currently disabled. INTERNET_FLAG_RELOAD Not supported. Data is always from the wire and caching
 *   is not supported. INTERNET_FLAG_RESYNCHRONIZE Reloads HTTP resources if the resource has been
 *   modified since the last time it was downloaded. INTERNET_FLAG_SECURE Uses SSL/PCT transaction
 *   semantics.
 * @param dwContext [in] Specifies the application-defined value that associates this operation with
 *   any application data.
 *
 * @return A valid, non-NULL HTTP request handle indicates success. NULL indicates failure. To get
 *   extended error information, call GetLastError.
 *
 * HttpOpenRequest creates a new HTTP request handle and stores the specified parameters in that
 * handle. An HTTP request handle holds a request to be sent to an HTTP server and contains all
 * RFC822/MIME/HTTP headers to be sent as part of the request.
 *
 * Use the InternetCloseHandle function to close the handle returned by HttpOpenRequest.
 * InternetCloseHandle cancels all outstanding I/O on the handle.
 *
 * The lpszReferer parameter to InternetOpen is used as the referrer for the HTTP request.
 *
 * The dwContext parameter allows for progress status callbacks to the application, but all requests
 * will be handled synchronously.
 *
 * When establishing a Secure Sockets Layer (SSL) or Private Communications Technology,
 * HttpOpenRequest uses the INTERNET_FLAG_SECURE option in addition to all other options.
 *
 * The following dwFlags values can be used in HttpOpenRequest to ignore invalid certificate errors:
 *
 * - INTERNET_FLAG_IGNORE_CERT_CN_INVALID: Ignores errors caused when the certificate host name of
 * the server does not match the host name in the request.
 *
 * - INTERNET_FLAG_IGNORE_CERT_DATE_INVALID: Ignores errors caused by an expired server certificate.
 */
#define HttpOpenRequest  HttpOpenRequestW
#else
/**
 * This function opens an HTTP request handle.
 *
 * @param hHttpSession [in] Handle to an HTTP session returned by InternetConnect.
 * @param lpszVerb [in] Long pointer to a null-terminated string that contains the verb to use in
 *   the request. If this parameter is NULL, the function uses "GET" as the verb.
 * @param lpszObjectName [in] Long pointer to a null-terminated string that contains the name of the
 *   target object of the specified verb. This is generally a file name, an executable module, or a
 *   search specifier.
 * @param lpszVersion [in] Long pointer to a null-terminated string that contains the HTTP version.
 *   If this parameter is NULL, the function uses "HTTP/1.0" as the version.
 * @param lpszReferer [in] Long pointer to a null-terminated string that specifies the address (URL)
 *   of the document from which the URL in the request (lpszObjectName) was obtained. If this
 *   parameter is NULL, no "referrer" is specified.
 * @param lplpszAcceptTypes [in] Long pointer to a null-terminated array of string pointers
 *   indicating content types accepted by the client. If this parameter is NULL, no types are accepted
 *   by the client. Servers interpret a lack of accept types to indicate that the client accepts only
 *   documents of type "text/ *" (that is, only text documents, and not pictures or other binary
 *   files).
 * @param dwFlags [in] Specifies a bitmask of Internet flags. Can be any of the following values:
 *   Value Description INTERNET_FLAG_CACHE_IF_NET_FAIL Return the resource from the cache if the
 *   network request for the resource fails due to an ERROR_INTERNET_CONNECTION_RESET or
 *   ERROR_INTERNET_CANNOT_CONNECT. INTERNET_FLAG_DONT_CACHE Not supported. Data is never cached.
 *   INTERNET_FLAG_HYPERLINK Forces a reload if there was no Expires time and no Last-Modified time
 *   returned from the server when determining whether to reload the item from the network.
 *   INTERNET_FLAG_IGNORE_CERT_CN_INVALID Disables Win32 Internet function checking of SSL/PCT-based
 *   certificates that are returned from the server against the host name given in the request. Win32
 *   Internet functions use a simple check against certificates by comparing for matching host names
 *   and simple wildcarding rules. INTERNET_FLAG_IGNORE_CERT_DATE_INVALID Disables Win32 Internet
 *   function checking of SSL/PCT-based certificates for proper validity dates.
 *   INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP Disables the ability of the Win32 Internet functions to
 *   detect this special type of redirect. When this flag is used, Win32 Internet functions
 *   transparently allow redirects from HTTPS to HTTP URLs. INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTPS
 *   Disables the ability of the Win32 Internet functions to detect this special type of redirect.
 *   When this flag is used, Win32 Internet functions transparently allow redirects from HTTP to HTTPS
 *   URLs. INTERNET_FLAG_KEEP_CONNECTION Uses keep-alive semantics, if available, for the connection.
 *   This flag is required for Microsoft Network (MSN), NT LAN Manager (NTLM), and other types of
 *   authentication. INTERNET_FLAG_MAKE_PERSISTENT Not supported. INTERNET_FLAG_MUST_CACHE_REQUEST
 *   Causes a temporary file to be created if the file cannot be cached. Identical to the preferred
 *   value INTERNET_FLAG_NEED_FILE. INTERNET_FLAG_NEED_FILE Causes a temporary file to be created if
 *   the file cannot be cached. INTERNET_FLAG_NO_AUTH Does not attempt authentication automatically.
 *   INTERNET_FLAG_NO_AUTO_REDIRECT Does not automatically handle redirection in HttpSendRequest.
 *   INTERNET_FLAG_NO_CACHE_WRITE Does not add the returned entity to the cache.
 *   INTERNET_FLAG_NO_COOKIES Does not automatically add cookie headers to requests, and does not
 *   automatically add returned cookies to the cookie database. INTERNET_FLAG_NO_UI Disables the
 *   cookie dialog box. INTERNET_FLAG_PRAGMA_NOCACHE Forces the request to be resolved by the origin
 *   server, even if a cached copy exists on the proxy. INTERNET_FLAG_READ_PREFETCH This flag is
 *   currently disabled. INTERNET_FLAG_RELOAD Not supported. Data is always from the wire and caching
 *   is not supported. INTERNET_FLAG_RESYNCHRONIZE Reloads HTTP resources if the resource has been
 *   modified since the last time it was downloaded. INTERNET_FLAG_SECURE Uses SSL/PCT transaction
 *   semantics.
 * @param dwContext [in] Specifies the application-defined value that associates this operation with
 *   any application data.
 *
 * @return A valid, non-NULL HTTP request handle indicates success. NULL indicates failure. To get
 *   extended error information, call GetLastError.
 *
 * HttpOpenRequest creates a new HTTP request handle and stores the specified parameters in that
 * handle. An HTTP request handle holds a request to be sent to an HTTP server and contains all
 * RFC822/MIME/HTTP headers to be sent as part of the request.
 *
 * Use the InternetCloseHandle function to close the handle returned by HttpOpenRequest.
 * InternetCloseHandle cancels all outstanding I/O on the handle.
 *
 * The lpszReferer parameter to InternetOpen is used as the referrer for the HTTP request.
 *
 * The dwContext parameter allows for progress status callbacks to the application, but all requests
 * will be handled synchronously.
 *
 * When establishing a Secure Sockets Layer (SSL) or Private Communications Technology,
 * HttpOpenRequest uses the INTERNET_FLAG_SECURE option in addition to all other options.
 *
 * The following dwFlags values can be used in HttpOpenRequest to ignore invalid certificate errors:
 *
 * - INTERNET_FLAG_IGNORE_CERT_CN_INVALID: Ignores errors caused when the certificate host name of
 * the server does not match the host name in the request.
 *
 * - INTERNET_FLAG_IGNORE_CERT_DATE_INVALID: Ignores errors caused by an expired server certificate.
 */
#define HttpOpenRequest  HttpOpenRequestA
#endif // !UNICODE

/**
 * This function adds one or more Hypertext Transfer Protocol (HTTP) request headers to the HTTP
 * request handle.
 *
 * @param hHttpRequest [in] Open HTTP request handle returned by HttpOpenRequest.
 * @param lpszHeaders [in] Long pointer to the null-terminated strings that contains headers to
 *   append to the request. Each header must be terminated by a CR/LF (carriage return/line feed)
 *   pair.
 * @param dwHeadersLength [in] Specifies the length, in characters, of lpszHeaders. If this
 *   parameter is -1L, the function assumes that lpszHeaders is zero-terminated (ASCIIZ), and the
 *   length is computed.
 * @param dwModifiers [in] Specifies the values used to modify the semantics of this function. Can
 *   be a combination of the following values: Value Description HTTP_ADDREQ_FLAG_ADD Adds the header
 *   if it does not exist. Used with HTTP_ADDREQ_FLAG_REPLACE. HTTP_ADDREQ_FLAG_ADD_IF_NEW Adds the
 *   header only if it does not already exist; otherwise, an error is returned.
 *   HTTP_ADDREQ_FLAG_COALESCE Coalesces headers of the same name.
 *   HTTP_ADDREQ_FLAG_COALESCE_WITH_COMMA Coalesces headers of the same name. For example, adding
 *   "Accept: text/ *" followed by "Accept: audio/ *" with this flag results in the formation of the
 *   single header "Accept: text/ *, audio/ *". This causes the first header found to be coalesced. It
 *   is up to the calling application to ensure a cohesive scheme with respect to coalesced/separate
 *   headers. HTTP_ADDREQ_FLAG_COALESCE_WITH_SEMICOLON Coalesces headers of the same name using a
 *   semicolon. HTTP_ADDREQ_FLAG_REPLACE Replaces or removes a header. If the header value is empty
 *   and the header is found, it is removed. If not empty, the header value is replaced.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError.
 *
 * HttpAddRequestHeaders appends additional, free-format headers to the HTTP request handle and is
 * intended for use by sophisticated clients that need detailed control over the exact request sent
 * to the HTTP server.
 *
 * Note that for basic HttpAddRequestHeaders, the application can pass in multiple headers in a
 * single buffer. If the application is trying to remove or replace a header, only one header can be
 * supplied in lpszHeaders.
 */
INTERNETAPI
BOOL
WINAPI
HttpAddRequestHeadersA(
    IN HINTERNET hRequest,
    IN LPCSTR lpszHeaders,
    IN DWORD dwHeadersLength,
    IN DWORD dwModifiers
    );
/**
 * This function adds one or more Hypertext Transfer Protocol (HTTP) request headers to the HTTP
 * request handle.
 *
 * @param hHttpRequest [in] Open HTTP request handle returned by HttpOpenRequest.
 * @param lpszHeaders [in] Long pointer to the null-terminated strings that contains headers to
 *   append to the request. Each header must be terminated by a CR/LF (carriage return/line feed)
 *   pair.
 * @param dwHeadersLength [in] Specifies the length, in characters, of lpszHeaders. If this
 *   parameter is -1L, the function assumes that lpszHeaders is zero-terminated (ASCIIZ), and the
 *   length is computed.
 * @param dwModifiers [in] Specifies the values used to modify the semantics of this function. Can
 *   be a combination of the following values: Value Description HTTP_ADDREQ_FLAG_ADD Adds the header
 *   if it does not exist. Used with HTTP_ADDREQ_FLAG_REPLACE. HTTP_ADDREQ_FLAG_ADD_IF_NEW Adds the
 *   header only if it does not already exist; otherwise, an error is returned.
 *   HTTP_ADDREQ_FLAG_COALESCE Coalesces headers of the same name.
 *   HTTP_ADDREQ_FLAG_COALESCE_WITH_COMMA Coalesces headers of the same name. For example, adding
 *   "Accept: text/ *" followed by "Accept: audio/ *" with this flag results in the formation of the
 *   single header "Accept: text/ *, audio/ *". This causes the first header found to be coalesced. It
 *   is up to the calling application to ensure a cohesive scheme with respect to coalesced/separate
 *   headers. HTTP_ADDREQ_FLAG_COALESCE_WITH_SEMICOLON Coalesces headers of the same name using a
 *   semicolon. HTTP_ADDREQ_FLAG_REPLACE Replaces or removes a header. If the header value is empty
 *   and the header is found, it is removed. If not empty, the header value is replaced.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError.
 *
 * HttpAddRequestHeaders appends additional, free-format headers to the HTTP request handle and is
 * intended for use by sophisticated clients that need detailed control over the exact request sent
 * to the HTTP server.
 *
 * Note that for basic HttpAddRequestHeaders, the application can pass in multiple headers in a
 * single buffer. If the application is trying to remove or replace a header, only one header can be
 * supplied in lpszHeaders.
 */
INTERNETAPI
BOOL
WINAPI
HttpAddRequestHeadersW(
    IN HINTERNET hRequest,
    IN LPCWSTR lpszHeaders,
    IN DWORD dwHeadersLength,
    IN DWORD dwModifiers
    );
#ifdef UNICODE
/**
 * This function adds one or more Hypertext Transfer Protocol (HTTP) request headers to the HTTP
 * request handle.
 *
 * @param hHttpRequest [in] Open HTTP request handle returned by HttpOpenRequest.
 * @param lpszHeaders [in] Long pointer to the null-terminated strings that contains headers to
 *   append to the request. Each header must be terminated by a CR/LF (carriage return/line feed)
 *   pair.
 * @param dwHeadersLength [in] Specifies the length, in characters, of lpszHeaders. If this
 *   parameter is -1L, the function assumes that lpszHeaders is zero-terminated (ASCIIZ), and the
 *   length is computed.
 * @param dwModifiers [in] Specifies the values used to modify the semantics of this function. Can
 *   be a combination of the following values: Value Description HTTP_ADDREQ_FLAG_ADD Adds the header
 *   if it does not exist. Used with HTTP_ADDREQ_FLAG_REPLACE. HTTP_ADDREQ_FLAG_ADD_IF_NEW Adds the
 *   header only if it does not already exist; otherwise, an error is returned.
 *   HTTP_ADDREQ_FLAG_COALESCE Coalesces headers of the same name.
 *   HTTP_ADDREQ_FLAG_COALESCE_WITH_COMMA Coalesces headers of the same name. For example, adding
 *   "Accept: text/ *" followed by "Accept: audio/ *" with this flag results in the formation of the
 *   single header "Accept: text/ *, audio/ *". This causes the first header found to be coalesced. It
 *   is up to the calling application to ensure a cohesive scheme with respect to coalesced/separate
 *   headers. HTTP_ADDREQ_FLAG_COALESCE_WITH_SEMICOLON Coalesces headers of the same name using a
 *   semicolon. HTTP_ADDREQ_FLAG_REPLACE Replaces or removes a header. If the header value is empty
 *   and the header is found, it is removed. If not empty, the header value is replaced.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError.
 *
 * HttpAddRequestHeaders appends additional, free-format headers to the HTTP request handle and is
 * intended for use by sophisticated clients that need detailed control over the exact request sent
 * to the HTTP server.
 *
 * Note that for basic HttpAddRequestHeaders, the application can pass in multiple headers in a
 * single buffer. If the application is trying to remove or replace a header, only one header can be
 * supplied in lpszHeaders.
 */
#define HttpAddRequestHeaders  HttpAddRequestHeadersW
#else
/**
 * This function adds one or more Hypertext Transfer Protocol (HTTP) request headers to the HTTP
 * request handle.
 *
 * @param hHttpRequest [in] Open HTTP request handle returned by HttpOpenRequest.
 * @param lpszHeaders [in] Long pointer to the null-terminated strings that contains headers to
 *   append to the request. Each header must be terminated by a CR/LF (carriage return/line feed)
 *   pair.
 * @param dwHeadersLength [in] Specifies the length, in characters, of lpszHeaders. If this
 *   parameter is -1L, the function assumes that lpszHeaders is zero-terminated (ASCIIZ), and the
 *   length is computed.
 * @param dwModifiers [in] Specifies the values used to modify the semantics of this function. Can
 *   be a combination of the following values: Value Description HTTP_ADDREQ_FLAG_ADD Adds the header
 *   if it does not exist. Used with HTTP_ADDREQ_FLAG_REPLACE. HTTP_ADDREQ_FLAG_ADD_IF_NEW Adds the
 *   header only if it does not already exist; otherwise, an error is returned.
 *   HTTP_ADDREQ_FLAG_COALESCE Coalesces headers of the same name.
 *   HTTP_ADDREQ_FLAG_COALESCE_WITH_COMMA Coalesces headers of the same name. For example, adding
 *   "Accept: text/ *" followed by "Accept: audio/ *" with this flag results in the formation of the
 *   single header "Accept: text/ *, audio/ *". This causes the first header found to be coalesced. It
 *   is up to the calling application to ensure a cohesive scheme with respect to coalesced/separate
 *   headers. HTTP_ADDREQ_FLAG_COALESCE_WITH_SEMICOLON Coalesces headers of the same name using a
 *   semicolon. HTTP_ADDREQ_FLAG_REPLACE Replaces or removes a header. If the header value is empty
 *   and the header is found, it is removed. If not empty, the header value is replaced.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError.
 *
 * HttpAddRequestHeaders appends additional, free-format headers to the HTTP request handle and is
 * intended for use by sophisticated clients that need detailed control over the exact request sent
 * to the HTTP server.
 *
 * Note that for basic HttpAddRequestHeaders, the application can pass in multiple headers in a
 * single buffer. If the application is trying to remove or replace a header, only one header can be
 * supplied in lpszHeaders.
 */
#define HttpAddRequestHeaders  HttpAddRequestHeadersA
#endif // !UNICODE

//
// values for dwModifiers parameter of HttpAddRequestHeaders()
//

#define HTTP_ADDREQ_INDEX_MASK      0x0000FFFF
#define HTTP_ADDREQ_FLAGS_MASK      0xFFFF0000

//
// HTTP_ADDREQ_FLAG_ADD_IF_NEW - the header will only be added if it doesn't
// already exist
//

#define HTTP_ADDREQ_FLAG_ADD_IF_NEW 0x10000000

//
// HTTP_ADDREQ_FLAG_ADD - if HTTP_ADDREQ_FLAG_REPLACE is set but the header is
// not found then if this flag is set, the header is added anyway, so long as
// there is a valid header-value
//

#define HTTP_ADDREQ_FLAG_ADD        0x20000000

//
// HTTP_ADDREQ_FLAG_COALESCE - coalesce headers with same name. e.g.
// "Accept: text/*" and "Accept: audio/*" with this flag results in a single
// header: "Accept: text/*, audio/*"
//

//
// HTTP_ADDREQ_FLAG_COALESCE - coalesce headers with same name. e.g.
// "Accept: text/*" and "Accept: audio/*" with this flag results in a single
// header: "Accept: text/*, audio/*"
//

#define HTTP_ADDREQ_FLAG_COALESCE_WITH_COMMA       0x40000000

#define HTTP_ADDREQ_FLAG_COALESCE_WITH_SEMICOLON   0x01000000

#define HTTP_ADDREQ_FLAG_COALESCE                  HTTP_ADDREQ_FLAG_COALESCE_WITH_COMMA

//
// HTTP_ADDREQ_FLAG_REPLACE - replaces the specified header. Only one header can
// be supplied in the buffer. If the header to be replaced is not the first
// in a list of headers with the same name, then the relative index should be
// supplied in the low 8 bits of the dwModifiers parameter. If the header-value
// part is missing, then the header is removed
//

#define HTTP_ADDREQ_FLAG_REPLACE    0x80000000

/**
 * This function sends the specified request to the HTTP server.
 *
 * @param hRequest [in] Open HTTP request handle returned by HttpOpenRequest.
 * @param lpszHeaders [in] Long pointer to null-terminated strings that contain additional headers
 *   to be appended to the request. This parameter can be NULL if there are no additional headers to
 *   append.
 * @param dwHeadersLength [in] Specifies the length, in characters, of the additional headers. If
 *   this parameter is -1L and lpszHeaders is not NULL, the function assumes that lpszHeaders is
 *   zero-terminated (ASCIIZ), and the length is calculated.
 * @param lpOptional [in] Long pointer to any optional data to send immediately after the request
 *   headers. This parameter is generally used for POST and PUT operations. The optional data can be
 *   the resource or information being posted to the server. This parameter can be NULL if there is no
 *   optional data to send.
 * @param dwOptionalLength [in] Specifies the length, in bytes, of the optional data. This parameter
 *   can be zero if there is no optional data to send.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError.
 *
 * HttpSendRequest sends the specified request to the HTTP server and allows the client to specify
 * additional headers to send along with the request.
 *
 * The function also lets the client specify optional data to send to the HTTP server immediately
 * following the request headers. This feature is generally used for "write" operations such as PUT
 * and POST. When using optional data, be aware of the following caveat: the size of the optional
 * data buffer, specified with the dwOptionalLength parameter, must be either less than 32 bytes or
 * greater than approximately 150 bytes. Otherwise, the HttpSendRequest function fails.
 *
 * Another caveat requires that the optional data buffer begin with '/r/n'. This ensures that header
 * and buffer is separated by '/r/n/r/n' as required by RFC 2068.
 *
 * After the request is sent, the status code and response headers from the HTTP server are read.
 * These headers are maintained internally and are available to client applications through the
 * HttpQueryInfo function.
 *
 * An application can use the same HTTP request handle in multiple calls to HttpSendRequest, but the
 * application must read all data returned from the previous call before calling the function again.
 */
INTERNETAPI
BOOL
WINAPI
HttpSendRequestA(
    IN HINTERNET hRequest,
    IN LPCSTR lpszHeaders OPTIONAL,
    IN DWORD dwHeadersLength,
    IN LPVOID lpOptional OPTIONAL,
    IN DWORD dwOptionalLength
    );
/**
 * This function sends the specified request to the HTTP server.
 *
 * @param hRequest [in] Open HTTP request handle returned by HttpOpenRequest.
 * @param lpszHeaders [in] Long pointer to null-terminated strings that contain additional headers
 *   to be appended to the request. This parameter can be NULL if there are no additional headers to
 *   append.
 * @param dwHeadersLength [in] Specifies the length, in characters, of the additional headers. If
 *   this parameter is -1L and lpszHeaders is not NULL, the function assumes that lpszHeaders is
 *   zero-terminated (ASCIIZ), and the length is calculated.
 * @param lpOptional [in] Long pointer to any optional data to send immediately after the request
 *   headers. This parameter is generally used for POST and PUT operations. The optional data can be
 *   the resource or information being posted to the server. This parameter can be NULL if there is no
 *   optional data to send.
 * @param dwOptionalLength [in] Specifies the length, in bytes, of the optional data. This parameter
 *   can be zero if there is no optional data to send.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError.
 *
 * HttpSendRequest sends the specified request to the HTTP server and allows the client to specify
 * additional headers to send along with the request.
 *
 * The function also lets the client specify optional data to send to the HTTP server immediately
 * following the request headers. This feature is generally used for "write" operations such as PUT
 * and POST. When using optional data, be aware of the following caveat: the size of the optional
 * data buffer, specified with the dwOptionalLength parameter, must be either less than 32 bytes or
 * greater than approximately 150 bytes. Otherwise, the HttpSendRequest function fails.
 *
 * Another caveat requires that the optional data buffer begin with '/r/n'. This ensures that header
 * and buffer is separated by '/r/n/r/n' as required by RFC 2068.
 *
 * After the request is sent, the status code and response headers from the HTTP server are read.
 * These headers are maintained internally and are available to client applications through the
 * HttpQueryInfo function.
 *
 * An application can use the same HTTP request handle in multiple calls to HttpSendRequest, but the
 * application must read all data returned from the previous call before calling the function again.
 */
INTERNETAPI
BOOL
WINAPI
HttpSendRequestW(
    IN HINTERNET hRequest,
    IN LPCWSTR lpszHeaders OPTIONAL,
    IN DWORD dwHeadersLength,
    IN LPVOID lpOptional OPTIONAL,
    IN DWORD dwOptionalLength
    );
#ifdef UNICODE
/**
 * This function sends the specified request to the HTTP server.
 *
 * @param hRequest [in] Open HTTP request handle returned by HttpOpenRequest.
 * @param lpszHeaders [in] Long pointer to null-terminated strings that contain additional headers
 *   to be appended to the request. This parameter can be NULL if there are no additional headers to
 *   append.
 * @param dwHeadersLength [in] Specifies the length, in characters, of the additional headers. If
 *   this parameter is -1L and lpszHeaders is not NULL, the function assumes that lpszHeaders is
 *   zero-terminated (ASCIIZ), and the length is calculated.
 * @param lpOptional [in] Long pointer to any optional data to send immediately after the request
 *   headers. This parameter is generally used for POST and PUT operations. The optional data can be
 *   the resource or information being posted to the server. This parameter can be NULL if there is no
 *   optional data to send.
 * @param dwOptionalLength [in] Specifies the length, in bytes, of the optional data. This parameter
 *   can be zero if there is no optional data to send.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError.
 *
 * HttpSendRequest sends the specified request to the HTTP server and allows the client to specify
 * additional headers to send along with the request.
 *
 * The function also lets the client specify optional data to send to the HTTP server immediately
 * following the request headers. This feature is generally used for "write" operations such as PUT
 * and POST. When using optional data, be aware of the following caveat: the size of the optional
 * data buffer, specified with the dwOptionalLength parameter, must be either less than 32 bytes or
 * greater than approximately 150 bytes. Otherwise, the HttpSendRequest function fails.
 *
 * Another caveat requires that the optional data buffer begin with '/r/n'. This ensures that header
 * and buffer is separated by '/r/n/r/n' as required by RFC 2068.
 *
 * After the request is sent, the status code and response headers from the HTTP server are read.
 * These headers are maintained internally and are available to client applications through the
 * HttpQueryInfo function.
 *
 * An application can use the same HTTP request handle in multiple calls to HttpSendRequest, but the
 * application must read all data returned from the previous call before calling the function again.
 */
#define HttpSendRequest  HttpSendRequestW
#else
/**
 * This function sends the specified request to the HTTP server.
 *
 * @param hRequest [in] Open HTTP request handle returned by HttpOpenRequest.
 * @param lpszHeaders [in] Long pointer to null-terminated strings that contain additional headers
 *   to be appended to the request. This parameter can be NULL if there are no additional headers to
 *   append.
 * @param dwHeadersLength [in] Specifies the length, in characters, of the additional headers. If
 *   this parameter is -1L and lpszHeaders is not NULL, the function assumes that lpszHeaders is
 *   zero-terminated (ASCIIZ), and the length is calculated.
 * @param lpOptional [in] Long pointer to any optional data to send immediately after the request
 *   headers. This parameter is generally used for POST and PUT operations. The optional data can be
 *   the resource or information being posted to the server. This parameter can be NULL if there is no
 *   optional data to send.
 * @param dwOptionalLength [in] Specifies the length, in bytes, of the optional data. This parameter
 *   can be zero if there is no optional data to send.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError.
 *
 * HttpSendRequest sends the specified request to the HTTP server and allows the client to specify
 * additional headers to send along with the request.
 *
 * The function also lets the client specify optional data to send to the HTTP server immediately
 * following the request headers. This feature is generally used for "write" operations such as PUT
 * and POST. When using optional data, be aware of the following caveat: the size of the optional
 * data buffer, specified with the dwOptionalLength parameter, must be either less than 32 bytes or
 * greater than approximately 150 bytes. Otherwise, the HttpSendRequest function fails.
 *
 * Another caveat requires that the optional data buffer begin with '/r/n'. This ensures that header
 * and buffer is separated by '/r/n/r/n' as required by RFC 2068.
 *
 * After the request is sent, the status code and response headers from the HTTP server are read.
 * These headers are maintained internally and are available to client applications through the
 * HttpQueryInfo function.
 *
 * An application can use the same HTTP request handle in multiple calls to HttpSendRequest, but the
 * application must read all data returned from the previous call before calling the function again.
 */
#define HttpSendRequest  HttpSendRequestA
#endif // !UNICODE

/**
 * This function queries for information about an HTTP request.
 *
 * @param hRequest [in] Open HTTP request handle returned by HttpOpenRequest or InternetOpenUrl.
 * @param dwInfoLevel [in] Specifies a combination of the attribute to query and the flags that
 *   modify the request. The attributes can be any of the following values: Value Description
 *   HTTP_QUERY_ACCEPT Retrieves the acceptable media types for the response.
 *   HTTP_QUERY_ACCEPT_CHARSET Retrieves the acceptable character sets for the response.
 *   HTTP_QUERY_ACCEPT_ENCODING Retrieves the acceptable content-coding values for the response.
 *   HTTP_QUERY_ACCEPT_LANGUAGE Retrieves the acceptable natural languages for the response.
 *   HTTP_QUERY_ACCEPT_RANGES Retrieves the types of range requests that are accepted for a resource.
 *   HTTP_QUERY_AGE Retrieves the Age response-header field, which contains the sender's estimate of
 *   the amount of time since the response was generated at the origin server. HTTP_QUERY_ALLOW
 *   Receives the methods supported by the server. HTTP_QUERY_AUTHORIZATION Retrieves the
 *   authorization credentials used for a request. HTTP_QUERY_CACHE_CONTROL Retrieves the cache
 *   control directives. HTTP_QUERY_CONNECTION Retrieves any options that are specified for a
 *   particular connection and must not be communicated by proxies over further connections.
 *   HTTP_QUERY_COOKIE Retrieves any cookies associated with the request. HTTP_QUERY_CONTENT_BASE
 *   Retrieves the base URI for resolving relative URLs within the entity.
 *   HTTP_QUERY_CONTENT_DESCRIPTION Obsolete. Maintained for legacy application compatibility only.
 *   HTTP_QUERY_CONTENT_DISPOSITION Obsolete. Maintained for legacy application compatibility only.
 *   HTTP_QUERY_CONTENT_ENCODING Receives any additional content codings that have been applied to the
 *   entire resource. HTTP_QUERY_CONTENT_ID Receives the content identification.
 *   HTTP_QUERY_CONTENT_LANGUAGE Receives the language that the content is in.
 *   HTTP_QUERY_CONTENT_LENGTH Receives the size of the resource, in bytes.
 *   HTTP_QUERY_CONTENT_LOCATION Retrieves the resource location for the entity enclosed in the
 *   message. HTTP_QUERY_CONTENT_MD5 Retrieves a MD5 digest of the entity-body for the purpose of
 *   providing an end-to-end message integrity check (MIC) for the entity-body.
 *   HTTP_QUERY_CONTENT_RANGE Retrieves the location in the full entity-body where the partial
 *   entity-body should be inserted and the total size of the full entity-body.
 *   HTTP_QUERY_CONTENT_TRANSFER_ENCODING Receives the additional content coding that has been applied
 *   to the resource. HTTP_QUERY_CONTENT_TYPE Receives the content type of the resource (such as
 *   text/html). HTTP_QUERY_COST No longer implemented. HTTP_QUERY_DATE Receives the date and time at
 *   which the message was originated. HTTP_QUERY_DERIVED_FROM No longer supported. HTTP_QUERY_ETAG
 *   Retrieves the entity tag for the associated entity. HTTP_QUERY_EXPIRES Receives the date and time
 *   after which the resource should be considered outdated. HTTP_QUERY_FORWARDED Obsolete. Maintained
 *   for legacy application compatibility only. HTTP_QUERY_FROM Retrieves the e-mail address for the
 *   human user who controls the requesting user agent if the From header is given. HTTP_QUERY_HOST
 *   Retrieves the Internet host and port number of the resource being requested. HTTP_QUERY_IF_MATCH
 *   Retrieves the contents of the If-Match request-header field. HTTP_QUERY_IF_MODIFIED_SINCE
 *   Retrieves the contents of the If-Modified-Since header. HTTP_QUERY_IF_NONE_MATCH Retrieves the
 *   contents of the If-None-Match request-header field. HTTP_QUERY_IF_RANGE Retrieves the contents of
 *   the If-Range request-header field. This header allows the client application to check if the
 *   entity related to a partial copy of the entity in the client application's cache has not been
 *   updated. If the entity has not been updated, send the parts that the client application is
 *   missing. If the entity has been updated, send the entire updated entity.
 *   HTTP_QUERY_IF_UNMODIFIED_SINCE Retrieves the contents of the If-Unmodified-Since request-header
 *   field. HTTP_QUERY_LINK Obsolete. Maintained for legacy application compatibility only.
 *   HTTP_QUERY_LAST_MODIFIED Receives the date and time at which the server believes the resource was
 *   last modified. HTTP_QUERY_LOCATION Retrieves the absolute URI used in a Location response-header.
 *   HTTP_QUERY_MAX Retrieves the maximum value of an HTTP_QUERY_* value. HTTP_QUERY_MAX_FORWARDS
 *   Retrieves the number of proxies or gateways that can forward the request to the next inbound
 *   server. HTTP_QUERY_MESSAGE_ID No longer implemented. HTTP_QUERY_MIME_VERSION Receives the version
 *   of the MIME protocol that was used to construct the message. HTTP_QUERY_ORIG_URI Obsolete.
 *   Maintained for legacy application compatibility only. HTTP_QUERY_PRAGMA Receives the
 *   implementation-specific directives that may apply to any recipient along the request/response
 *   chain. HTTP_QUERY_PROXY_AUTHENTICATE Retrieves the authentication scheme and realm returned by
 *   the proxy. HTTP_QUERY_PROXY_AUTHORIZATION Retrieves the header that is used to identify the user
 *   to a proxy that requires authentication. HTTP_QUERY_PUBLIC Receives methods available at this
 *   server. HTTP_QUERY_RANGE Retrieves the byte range of an entity. HTTP_QUERY_RAW_HEADERS Receives
 *   all the headers returned by the server. Each header is terminated by "\0". An additional "\0"
 *   terminates the list of headers. HTTP_QUERY_RAW_HEADERS_CRLF Receives all the headers returned by
 *   the server. Each header is separated by a carriage return/line feed (CR/LF) sequence.
 *   HTTP_QUERY_REFERER Receives the URI of the resource where the requested URI was obtained.
 *   HTTP_QUERY_REFRESH Obsolete. Maintained for legacy application compatibility only.
 *   HTTP_QUERY_REQUEST_METHOD Receives the verb that is being used in the request, typically GET or
 *   POST. HTTP_QUERY_RETRY_AFTER Retrieves the amount of time the service is expected to be
 *   unavailable. HTTP_QUERY_SERVER Retrieves information about the software used by the origin server
 *   to handle the request. HTTP_QUERY_SET_COOKIE Receives the value of the cookie set for the
 *   request. HTTP_QUERY_STATUS_CODE Receives the status code returned by the server.
 *   HTTP_QUERY_STATUS_TEXT Receives any additional text returned by the server on the response line.
 *   HTTP_QUERY_TITLE Obsolete. Maintained for legacy application compatibility only.
 *   HTTP_QUERY_TRANSFER_ENCODING Retrieves the type of transformation that has been applied to the
 *   message body so it can be safely transferred between the sender and recipient. HTTP_QUERY_UPGRADE
 *   Retrieves the additional communication protocols that are supported by the server. HTTP_QUERY_URI
 *   Receives some or all of the Uniform Resource Identifiers (URIs) by which the Request-URI resource
 *   can be identified. HTTP_QUERY_USER_AGENT Retrieves information about the user agent that made the
 *   request. HTTP_QUERY_VARY Retrieves the header that indicates that the entity was selected from a
 *   number of available representations of the response using server-driven negotiation.
 *   HTTP_QUERY_VERSION Receives the last response code returned by the server. HTTP_QUERY_VIA
 *   Retrieves the intermediate protocols and recipients between the user agent and the server on
 *   requests, and between the origin server and the client on responses. HTTP_QUERY_WARNING Retrieves
 *   additional information about the status of a response that may not be reflected by the response
 *   status code. HTTP_QUERY_WWW_AUTHENTICATE Retrieves the authentication scheme and realm returned
 *   by the server. The following modifiers can be used with the information values: Value Description
 *   HTTP_QUERY_CUSTOM Causes HttpQueryInfo to search for the header name specified in lpvBuffer and
 *   store the header information in lpvBuffer. HTTP_QUERY_FLAG_COALESCE Not supported.
 *   HTTP_QUERY_FLAG_NUMBER Returns the data as a 32-bit number for headers whose value is a number,
 *   such as the status code. HTTP_QUERY_FLAG_REQUEST_HEADERS Queries request headers only.
 *   HTTP_QUERY_FLAG_SYSTEMTIME Returns the header value as a standard Win32 SYSTEMTIME structure,
 *   which does not require the application to parse the data. Use for headers whose value is a
 *   date/time string, such as "Last-Modified-Time".
 * @param lpBuffer [in\out] Long void pointer to the buffer that receives the information.
 * @param lpdwBufferLength [in\out] Long pointer to a value that contains the length of the data
 *   buffer. When the function returns, this parameter contains the address of a value specifying the
 *   length of the information written to the buffer. When the function returns strings, the following
 *   rules apply: If the function succeeds, lpdwBufferLength specifies the length of the string, in
 *   characters, minus 1 for the terminating null. If the function fails and ERROR_INSUFFICIENT_BUFFER
 *   is returned, lpdwBufferLength specifies the number of bytes that the application must allocate to
 *   receive the string.
 * @param lpdwIndex [in\out] Long pointer to a zero-based header index used to enumerate multiple
 *   headers with the same name. When calling the function, this parameter is the index of the
 *   specified header to return. When the function returns, this parameter is the index of the next
 *   header. If the next index cannot be found, ERROR_HTTP_HEADER_NOT_FOUND is returned.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError.
 *
 * HttpQueryInfo is used to return response or request headers from an HTTP request.
 *
 * You can retrieve different types of data from HttpQueryInfo:
 *
 * strings (default)
 *
 * SYSTEMTIME (for Data: Expires:, headers)
 *
 * DWORD (for STATUS_CODE, CONTENT_LENGTH, and so on if HTTP_QUERY_INFO_NUMBER has been used)
 */
INTERNETAPI
BOOL
WINAPI
HttpQueryInfoA(
    IN HINTERNET hRequest,
    IN DWORD dwInfoLevel,
    IN OUT LPVOID lpBuffer OPTIONAL,
    IN OUT LPDWORD lpdwBufferLength,
    IN OUT LPDWORD lpdwIndex OPTIONAL
    );
/**
 * This function queries for information about an HTTP request.
 *
 * @param hRequest [in] Open HTTP request handle returned by HttpOpenRequest or InternetOpenUrl.
 * @param dwInfoLevel [in] Specifies a combination of the attribute to query and the flags that
 *   modify the request. The attributes can be any of the following values: Value Description
 *   HTTP_QUERY_ACCEPT Retrieves the acceptable media types for the response.
 *   HTTP_QUERY_ACCEPT_CHARSET Retrieves the acceptable character sets for the response.
 *   HTTP_QUERY_ACCEPT_ENCODING Retrieves the acceptable content-coding values for the response.
 *   HTTP_QUERY_ACCEPT_LANGUAGE Retrieves the acceptable natural languages for the response.
 *   HTTP_QUERY_ACCEPT_RANGES Retrieves the types of range requests that are accepted for a resource.
 *   HTTP_QUERY_AGE Retrieves the Age response-header field, which contains the sender's estimate of
 *   the amount of time since the response was generated at the origin server. HTTP_QUERY_ALLOW
 *   Receives the methods supported by the server. HTTP_QUERY_AUTHORIZATION Retrieves the
 *   authorization credentials used for a request. HTTP_QUERY_CACHE_CONTROL Retrieves the cache
 *   control directives. HTTP_QUERY_CONNECTION Retrieves any options that are specified for a
 *   particular connection and must not be communicated by proxies over further connections.
 *   HTTP_QUERY_COOKIE Retrieves any cookies associated with the request. HTTP_QUERY_CONTENT_BASE
 *   Retrieves the base URI for resolving relative URLs within the entity.
 *   HTTP_QUERY_CONTENT_DESCRIPTION Obsolete. Maintained for legacy application compatibility only.
 *   HTTP_QUERY_CONTENT_DISPOSITION Obsolete. Maintained for legacy application compatibility only.
 *   HTTP_QUERY_CONTENT_ENCODING Receives any additional content codings that have been applied to the
 *   entire resource. HTTP_QUERY_CONTENT_ID Receives the content identification.
 *   HTTP_QUERY_CONTENT_LANGUAGE Receives the language that the content is in.
 *   HTTP_QUERY_CONTENT_LENGTH Receives the size of the resource, in bytes.
 *   HTTP_QUERY_CONTENT_LOCATION Retrieves the resource location for the entity enclosed in the
 *   message. HTTP_QUERY_CONTENT_MD5 Retrieves a MD5 digest of the entity-body for the purpose of
 *   providing an end-to-end message integrity check (MIC) for the entity-body.
 *   HTTP_QUERY_CONTENT_RANGE Retrieves the location in the full entity-body where the partial
 *   entity-body should be inserted and the total size of the full entity-body.
 *   HTTP_QUERY_CONTENT_TRANSFER_ENCODING Receives the additional content coding that has been applied
 *   to the resource. HTTP_QUERY_CONTENT_TYPE Receives the content type of the resource (such as
 *   text/html). HTTP_QUERY_COST No longer implemented. HTTP_QUERY_DATE Receives the date and time at
 *   which the message was originated. HTTP_QUERY_DERIVED_FROM No longer supported. HTTP_QUERY_ETAG
 *   Retrieves the entity tag for the associated entity. HTTP_QUERY_EXPIRES Receives the date and time
 *   after which the resource should be considered outdated. HTTP_QUERY_FORWARDED Obsolete. Maintained
 *   for legacy application compatibility only. HTTP_QUERY_FROM Retrieves the e-mail address for the
 *   human user who controls the requesting user agent if the From header is given. HTTP_QUERY_HOST
 *   Retrieves the Internet host and port number of the resource being requested. HTTP_QUERY_IF_MATCH
 *   Retrieves the contents of the If-Match request-header field. HTTP_QUERY_IF_MODIFIED_SINCE
 *   Retrieves the contents of the If-Modified-Since header. HTTP_QUERY_IF_NONE_MATCH Retrieves the
 *   contents of the If-None-Match request-header field. HTTP_QUERY_IF_RANGE Retrieves the contents of
 *   the If-Range request-header field. This header allows the client application to check if the
 *   entity related to a partial copy of the entity in the client application's cache has not been
 *   updated. If the entity has not been updated, send the parts that the client application is
 *   missing. If the entity has been updated, send the entire updated entity.
 *   HTTP_QUERY_IF_UNMODIFIED_SINCE Retrieves the contents of the If-Unmodified-Since request-header
 *   field. HTTP_QUERY_LINK Obsolete. Maintained for legacy application compatibility only.
 *   HTTP_QUERY_LAST_MODIFIED Receives the date and time at which the server believes the resource was
 *   last modified. HTTP_QUERY_LOCATION Retrieves the absolute URI used in a Location response-header.
 *   HTTP_QUERY_MAX Retrieves the maximum value of an HTTP_QUERY_* value. HTTP_QUERY_MAX_FORWARDS
 *   Retrieves the number of proxies or gateways that can forward the request to the next inbound
 *   server. HTTP_QUERY_MESSAGE_ID No longer implemented. HTTP_QUERY_MIME_VERSION Receives the version
 *   of the MIME protocol that was used to construct the message. HTTP_QUERY_ORIG_URI Obsolete.
 *   Maintained for legacy application compatibility only. HTTP_QUERY_PRAGMA Receives the
 *   implementation-specific directives that may apply to any recipient along the request/response
 *   chain. HTTP_QUERY_PROXY_AUTHENTICATE Retrieves the authentication scheme and realm returned by
 *   the proxy. HTTP_QUERY_PROXY_AUTHORIZATION Retrieves the header that is used to identify the user
 *   to a proxy that requires authentication. HTTP_QUERY_PUBLIC Receives methods available at this
 *   server. HTTP_QUERY_RANGE Retrieves the byte range of an entity. HTTP_QUERY_RAW_HEADERS Receives
 *   all the headers returned by the server. Each header is terminated by "\0". An additional "\0"
 *   terminates the list of headers. HTTP_QUERY_RAW_HEADERS_CRLF Receives all the headers returned by
 *   the server. Each header is separated by a carriage return/line feed (CR/LF) sequence.
 *   HTTP_QUERY_REFERER Receives the URI of the resource where the requested URI was obtained.
 *   HTTP_QUERY_REFRESH Obsolete. Maintained for legacy application compatibility only.
 *   HTTP_QUERY_REQUEST_METHOD Receives the verb that is being used in the request, typically GET or
 *   POST. HTTP_QUERY_RETRY_AFTER Retrieves the amount of time the service is expected to be
 *   unavailable. HTTP_QUERY_SERVER Retrieves information about the software used by the origin server
 *   to handle the request. HTTP_QUERY_SET_COOKIE Receives the value of the cookie set for the
 *   request. HTTP_QUERY_STATUS_CODE Receives the status code returned by the server.
 *   HTTP_QUERY_STATUS_TEXT Receives any additional text returned by the server on the response line.
 *   HTTP_QUERY_TITLE Obsolete. Maintained for legacy application compatibility only.
 *   HTTP_QUERY_TRANSFER_ENCODING Retrieves the type of transformation that has been applied to the
 *   message body so it can be safely transferred between the sender and recipient. HTTP_QUERY_UPGRADE
 *   Retrieves the additional communication protocols that are supported by the server. HTTP_QUERY_URI
 *   Receives some or all of the Uniform Resource Identifiers (URIs) by which the Request-URI resource
 *   can be identified. HTTP_QUERY_USER_AGENT Retrieves information about the user agent that made the
 *   request. HTTP_QUERY_VARY Retrieves the header that indicates that the entity was selected from a
 *   number of available representations of the response using server-driven negotiation.
 *   HTTP_QUERY_VERSION Receives the last response code returned by the server. HTTP_QUERY_VIA
 *   Retrieves the intermediate protocols and recipients between the user agent and the server on
 *   requests, and between the origin server and the client on responses. HTTP_QUERY_WARNING Retrieves
 *   additional information about the status of a response that may not be reflected by the response
 *   status code. HTTP_QUERY_WWW_AUTHENTICATE Retrieves the authentication scheme and realm returned
 *   by the server. The following modifiers can be used with the information values: Value Description
 *   HTTP_QUERY_CUSTOM Causes HttpQueryInfo to search for the header name specified in lpvBuffer and
 *   store the header information in lpvBuffer. HTTP_QUERY_FLAG_COALESCE Not supported.
 *   HTTP_QUERY_FLAG_NUMBER Returns the data as a 32-bit number for headers whose value is a number,
 *   such as the status code. HTTP_QUERY_FLAG_REQUEST_HEADERS Queries request headers only.
 *   HTTP_QUERY_FLAG_SYSTEMTIME Returns the header value as a standard Win32 SYSTEMTIME structure,
 *   which does not require the application to parse the data. Use for headers whose value is a
 *   date/time string, such as "Last-Modified-Time".
 * @param lpBuffer [in\out] Long void pointer to the buffer that receives the information.
 * @param lpdwBufferLength [in\out] Long pointer to a value that contains the length of the data
 *   buffer. When the function returns, this parameter contains the address of a value specifying the
 *   length of the information written to the buffer. When the function returns strings, the following
 *   rules apply: If the function succeeds, lpdwBufferLength specifies the length of the string, in
 *   characters, minus 1 for the terminating null. If the function fails and ERROR_INSUFFICIENT_BUFFER
 *   is returned, lpdwBufferLength specifies the number of bytes that the application must allocate to
 *   receive the string.
 * @param lpdwIndex [in\out] Long pointer to a zero-based header index used to enumerate multiple
 *   headers with the same name. When calling the function, this parameter is the index of the
 *   specified header to return. When the function returns, this parameter is the index of the next
 *   header. If the next index cannot be found, ERROR_HTTP_HEADER_NOT_FOUND is returned.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError.
 *
 * HttpQueryInfo is used to return response or request headers from an HTTP request.
 *
 * You can retrieve different types of data from HttpQueryInfo:
 *
 * strings (default)
 *
 * SYSTEMTIME (for Data: Expires:, headers)
 *
 * DWORD (for STATUS_CODE, CONTENT_LENGTH, and so on if HTTP_QUERY_INFO_NUMBER has been used)
 */
INTERNETAPI
BOOL
WINAPI
HttpQueryInfoW(
    IN HINTERNET hRequest,
    IN DWORD dwInfoLevel,
    IN OUT LPVOID lpBuffer OPTIONAL,
    IN OUT LPDWORD lpdwBufferLength,
    IN OUT LPDWORD lpdwIndex OPTIONAL
    );
#ifdef UNICODE
/**
 * This function queries for information about an HTTP request.
 *
 * @param hRequest [in] Open HTTP request handle returned by HttpOpenRequest or InternetOpenUrl.
 * @param dwInfoLevel [in] Specifies a combination of the attribute to query and the flags that
 *   modify the request. The attributes can be any of the following values: Value Description
 *   HTTP_QUERY_ACCEPT Retrieves the acceptable media types for the response.
 *   HTTP_QUERY_ACCEPT_CHARSET Retrieves the acceptable character sets for the response.
 *   HTTP_QUERY_ACCEPT_ENCODING Retrieves the acceptable content-coding values for the response.
 *   HTTP_QUERY_ACCEPT_LANGUAGE Retrieves the acceptable natural languages for the response.
 *   HTTP_QUERY_ACCEPT_RANGES Retrieves the types of range requests that are accepted for a resource.
 *   HTTP_QUERY_AGE Retrieves the Age response-header field, which contains the sender's estimate of
 *   the amount of time since the response was generated at the origin server. HTTP_QUERY_ALLOW
 *   Receives the methods supported by the server. HTTP_QUERY_AUTHORIZATION Retrieves the
 *   authorization credentials used for a request. HTTP_QUERY_CACHE_CONTROL Retrieves the cache
 *   control directives. HTTP_QUERY_CONNECTION Retrieves any options that are specified for a
 *   particular connection and must not be communicated by proxies over further connections.
 *   HTTP_QUERY_COOKIE Retrieves any cookies associated with the request. HTTP_QUERY_CONTENT_BASE
 *   Retrieves the base URI for resolving relative URLs within the entity.
 *   HTTP_QUERY_CONTENT_DESCRIPTION Obsolete. Maintained for legacy application compatibility only.
 *   HTTP_QUERY_CONTENT_DISPOSITION Obsolete. Maintained for legacy application compatibility only.
 *   HTTP_QUERY_CONTENT_ENCODING Receives any additional content codings that have been applied to the
 *   entire resource. HTTP_QUERY_CONTENT_ID Receives the content identification.
 *   HTTP_QUERY_CONTENT_LANGUAGE Receives the language that the content is in.
 *   HTTP_QUERY_CONTENT_LENGTH Receives the size of the resource, in bytes.
 *   HTTP_QUERY_CONTENT_LOCATION Retrieves the resource location for the entity enclosed in the
 *   message. HTTP_QUERY_CONTENT_MD5 Retrieves a MD5 digest of the entity-body for the purpose of
 *   providing an end-to-end message integrity check (MIC) for the entity-body.
 *   HTTP_QUERY_CONTENT_RANGE Retrieves the location in the full entity-body where the partial
 *   entity-body should be inserted and the total size of the full entity-body.
 *   HTTP_QUERY_CONTENT_TRANSFER_ENCODING Receives the additional content coding that has been applied
 *   to the resource. HTTP_QUERY_CONTENT_TYPE Receives the content type of the resource (such as
 *   text/html). HTTP_QUERY_COST No longer implemented. HTTP_QUERY_DATE Receives the date and time at
 *   which the message was originated. HTTP_QUERY_DERIVED_FROM No longer supported. HTTP_QUERY_ETAG
 *   Retrieves the entity tag for the associated entity. HTTP_QUERY_EXPIRES Receives the date and time
 *   after which the resource should be considered outdated. HTTP_QUERY_FORWARDED Obsolete. Maintained
 *   for legacy application compatibility only. HTTP_QUERY_FROM Retrieves the e-mail address for the
 *   human user who controls the requesting user agent if the From header is given. HTTP_QUERY_HOST
 *   Retrieves the Internet host and port number of the resource being requested. HTTP_QUERY_IF_MATCH
 *   Retrieves the contents of the If-Match request-header field. HTTP_QUERY_IF_MODIFIED_SINCE
 *   Retrieves the contents of the If-Modified-Since header. HTTP_QUERY_IF_NONE_MATCH Retrieves the
 *   contents of the If-None-Match request-header field. HTTP_QUERY_IF_RANGE Retrieves the contents of
 *   the If-Range request-header field. This header allows the client application to check if the
 *   entity related to a partial copy of the entity in the client application's cache has not been
 *   updated. If the entity has not been updated, send the parts that the client application is
 *   missing. If the entity has been updated, send the entire updated entity.
 *   HTTP_QUERY_IF_UNMODIFIED_SINCE Retrieves the contents of the If-Unmodified-Since request-header
 *   field. HTTP_QUERY_LINK Obsolete. Maintained for legacy application compatibility only.
 *   HTTP_QUERY_LAST_MODIFIED Receives the date and time at which the server believes the resource was
 *   last modified. HTTP_QUERY_LOCATION Retrieves the absolute URI used in a Location response-header.
 *   HTTP_QUERY_MAX Retrieves the maximum value of an HTTP_QUERY_* value. HTTP_QUERY_MAX_FORWARDS
 *   Retrieves the number of proxies or gateways that can forward the request to the next inbound
 *   server. HTTP_QUERY_MESSAGE_ID No longer implemented. HTTP_QUERY_MIME_VERSION Receives the version
 *   of the MIME protocol that was used to construct the message. HTTP_QUERY_ORIG_URI Obsolete.
 *   Maintained for legacy application compatibility only. HTTP_QUERY_PRAGMA Receives the
 *   implementation-specific directives that may apply to any recipient along the request/response
 *   chain. HTTP_QUERY_PROXY_AUTHENTICATE Retrieves the authentication scheme and realm returned by
 *   the proxy. HTTP_QUERY_PROXY_AUTHORIZATION Retrieves the header that is used to identify the user
 *   to a proxy that requires authentication. HTTP_QUERY_PUBLIC Receives methods available at this
 *   server. HTTP_QUERY_RANGE Retrieves the byte range of an entity. HTTP_QUERY_RAW_HEADERS Receives
 *   all the headers returned by the server. Each header is terminated by "\0". An additional "\0"
 *   terminates the list of headers. HTTP_QUERY_RAW_HEADERS_CRLF Receives all the headers returned by
 *   the server. Each header is separated by a carriage return/line feed (CR/LF) sequence.
 *   HTTP_QUERY_REFERER Receives the URI of the resource where the requested URI was obtained.
 *   HTTP_QUERY_REFRESH Obsolete. Maintained for legacy application compatibility only.
 *   HTTP_QUERY_REQUEST_METHOD Receives the verb that is being used in the request, typically GET or
 *   POST. HTTP_QUERY_RETRY_AFTER Retrieves the amount of time the service is expected to be
 *   unavailable. HTTP_QUERY_SERVER Retrieves information about the software used by the origin server
 *   to handle the request. HTTP_QUERY_SET_COOKIE Receives the value of the cookie set for the
 *   request. HTTP_QUERY_STATUS_CODE Receives the status code returned by the server.
 *   HTTP_QUERY_STATUS_TEXT Receives any additional text returned by the server on the response line.
 *   HTTP_QUERY_TITLE Obsolete. Maintained for legacy application compatibility only.
 *   HTTP_QUERY_TRANSFER_ENCODING Retrieves the type of transformation that has been applied to the
 *   message body so it can be safely transferred between the sender and recipient. HTTP_QUERY_UPGRADE
 *   Retrieves the additional communication protocols that are supported by the server. HTTP_QUERY_URI
 *   Receives some or all of the Uniform Resource Identifiers (URIs) by which the Request-URI resource
 *   can be identified. HTTP_QUERY_USER_AGENT Retrieves information about the user agent that made the
 *   request. HTTP_QUERY_VARY Retrieves the header that indicates that the entity was selected from a
 *   number of available representations of the response using server-driven negotiation.
 *   HTTP_QUERY_VERSION Receives the last response code returned by the server. HTTP_QUERY_VIA
 *   Retrieves the intermediate protocols and recipients between the user agent and the server on
 *   requests, and between the origin server and the client on responses. HTTP_QUERY_WARNING Retrieves
 *   additional information about the status of a response that may not be reflected by the response
 *   status code. HTTP_QUERY_WWW_AUTHENTICATE Retrieves the authentication scheme and realm returned
 *   by the server. The following modifiers can be used with the information values: Value Description
 *   HTTP_QUERY_CUSTOM Causes HttpQueryInfo to search for the header name specified in lpvBuffer and
 *   store the header information in lpvBuffer. HTTP_QUERY_FLAG_COALESCE Not supported.
 *   HTTP_QUERY_FLAG_NUMBER Returns the data as a 32-bit number for headers whose value is a number,
 *   such as the status code. HTTP_QUERY_FLAG_REQUEST_HEADERS Queries request headers only.
 *   HTTP_QUERY_FLAG_SYSTEMTIME Returns the header value as a standard Win32 SYSTEMTIME structure,
 *   which does not require the application to parse the data. Use for headers whose value is a
 *   date/time string, such as "Last-Modified-Time".
 * @param lpBuffer [in\out] Long void pointer to the buffer that receives the information.
 * @param lpdwBufferLength [in\out] Long pointer to a value that contains the length of the data
 *   buffer. When the function returns, this parameter contains the address of a value specifying the
 *   length of the information written to the buffer. When the function returns strings, the following
 *   rules apply: If the function succeeds, lpdwBufferLength specifies the length of the string, in
 *   characters, minus 1 for the terminating null. If the function fails and ERROR_INSUFFICIENT_BUFFER
 *   is returned, lpdwBufferLength specifies the number of bytes that the application must allocate to
 *   receive the string.
 * @param lpdwIndex [in\out] Long pointer to a zero-based header index used to enumerate multiple
 *   headers with the same name. When calling the function, this parameter is the index of the
 *   specified header to return. When the function returns, this parameter is the index of the next
 *   header. If the next index cannot be found, ERROR_HTTP_HEADER_NOT_FOUND is returned.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError.
 *
 * HttpQueryInfo is used to return response or request headers from an HTTP request.
 *
 * You can retrieve different types of data from HttpQueryInfo:
 *
 * strings (default)
 *
 * SYSTEMTIME (for Data: Expires:, headers)
 *
 * DWORD (for STATUS_CODE, CONTENT_LENGTH, and so on if HTTP_QUERY_INFO_NUMBER has been used)
 */
#define HttpQueryInfo  HttpQueryInfoW
#else
/**
 * This function queries for information about an HTTP request.
 *
 * @param hRequest [in] Open HTTP request handle returned by HttpOpenRequest or InternetOpenUrl.
 * @param dwInfoLevel [in] Specifies a combination of the attribute to query and the flags that
 *   modify the request. The attributes can be any of the following values: Value Description
 *   HTTP_QUERY_ACCEPT Retrieves the acceptable media types for the response.
 *   HTTP_QUERY_ACCEPT_CHARSET Retrieves the acceptable character sets for the response.
 *   HTTP_QUERY_ACCEPT_ENCODING Retrieves the acceptable content-coding values for the response.
 *   HTTP_QUERY_ACCEPT_LANGUAGE Retrieves the acceptable natural languages for the response.
 *   HTTP_QUERY_ACCEPT_RANGES Retrieves the types of range requests that are accepted for a resource.
 *   HTTP_QUERY_AGE Retrieves the Age response-header field, which contains the sender's estimate of
 *   the amount of time since the response was generated at the origin server. HTTP_QUERY_ALLOW
 *   Receives the methods supported by the server. HTTP_QUERY_AUTHORIZATION Retrieves the
 *   authorization credentials used for a request. HTTP_QUERY_CACHE_CONTROL Retrieves the cache
 *   control directives. HTTP_QUERY_CONNECTION Retrieves any options that are specified for a
 *   particular connection and must not be communicated by proxies over further connections.
 *   HTTP_QUERY_COOKIE Retrieves any cookies associated with the request. HTTP_QUERY_CONTENT_BASE
 *   Retrieves the base URI for resolving relative URLs within the entity.
 *   HTTP_QUERY_CONTENT_DESCRIPTION Obsolete. Maintained for legacy application compatibility only.
 *   HTTP_QUERY_CONTENT_DISPOSITION Obsolete. Maintained for legacy application compatibility only.
 *   HTTP_QUERY_CONTENT_ENCODING Receives any additional content codings that have been applied to the
 *   entire resource. HTTP_QUERY_CONTENT_ID Receives the content identification.
 *   HTTP_QUERY_CONTENT_LANGUAGE Receives the language that the content is in.
 *   HTTP_QUERY_CONTENT_LENGTH Receives the size of the resource, in bytes.
 *   HTTP_QUERY_CONTENT_LOCATION Retrieves the resource location for the entity enclosed in the
 *   message. HTTP_QUERY_CONTENT_MD5 Retrieves a MD5 digest of the entity-body for the purpose of
 *   providing an end-to-end message integrity check (MIC) for the entity-body.
 *   HTTP_QUERY_CONTENT_RANGE Retrieves the location in the full entity-body where the partial
 *   entity-body should be inserted and the total size of the full entity-body.
 *   HTTP_QUERY_CONTENT_TRANSFER_ENCODING Receives the additional content coding that has been applied
 *   to the resource. HTTP_QUERY_CONTENT_TYPE Receives the content type of the resource (such as
 *   text/html). HTTP_QUERY_COST No longer implemented. HTTP_QUERY_DATE Receives the date and time at
 *   which the message was originated. HTTP_QUERY_DERIVED_FROM No longer supported. HTTP_QUERY_ETAG
 *   Retrieves the entity tag for the associated entity. HTTP_QUERY_EXPIRES Receives the date and time
 *   after which the resource should be considered outdated. HTTP_QUERY_FORWARDED Obsolete. Maintained
 *   for legacy application compatibility only. HTTP_QUERY_FROM Retrieves the e-mail address for the
 *   human user who controls the requesting user agent if the From header is given. HTTP_QUERY_HOST
 *   Retrieves the Internet host and port number of the resource being requested. HTTP_QUERY_IF_MATCH
 *   Retrieves the contents of the If-Match request-header field. HTTP_QUERY_IF_MODIFIED_SINCE
 *   Retrieves the contents of the If-Modified-Since header. HTTP_QUERY_IF_NONE_MATCH Retrieves the
 *   contents of the If-None-Match request-header field. HTTP_QUERY_IF_RANGE Retrieves the contents of
 *   the If-Range request-header field. This header allows the client application to check if the
 *   entity related to a partial copy of the entity in the client application's cache has not been
 *   updated. If the entity has not been updated, send the parts that the client application is
 *   missing. If the entity has been updated, send the entire updated entity.
 *   HTTP_QUERY_IF_UNMODIFIED_SINCE Retrieves the contents of the If-Unmodified-Since request-header
 *   field. HTTP_QUERY_LINK Obsolete. Maintained for legacy application compatibility only.
 *   HTTP_QUERY_LAST_MODIFIED Receives the date and time at which the server believes the resource was
 *   last modified. HTTP_QUERY_LOCATION Retrieves the absolute URI used in a Location response-header.
 *   HTTP_QUERY_MAX Retrieves the maximum value of an HTTP_QUERY_* value. HTTP_QUERY_MAX_FORWARDS
 *   Retrieves the number of proxies or gateways that can forward the request to the next inbound
 *   server. HTTP_QUERY_MESSAGE_ID No longer implemented. HTTP_QUERY_MIME_VERSION Receives the version
 *   of the MIME protocol that was used to construct the message. HTTP_QUERY_ORIG_URI Obsolete.
 *   Maintained for legacy application compatibility only. HTTP_QUERY_PRAGMA Receives the
 *   implementation-specific directives that may apply to any recipient along the request/response
 *   chain. HTTP_QUERY_PROXY_AUTHENTICATE Retrieves the authentication scheme and realm returned by
 *   the proxy. HTTP_QUERY_PROXY_AUTHORIZATION Retrieves the header that is used to identify the user
 *   to a proxy that requires authentication. HTTP_QUERY_PUBLIC Receives methods available at this
 *   server. HTTP_QUERY_RANGE Retrieves the byte range of an entity. HTTP_QUERY_RAW_HEADERS Receives
 *   all the headers returned by the server. Each header is terminated by "\0". An additional "\0"
 *   terminates the list of headers. HTTP_QUERY_RAW_HEADERS_CRLF Receives all the headers returned by
 *   the server. Each header is separated by a carriage return/line feed (CR/LF) sequence.
 *   HTTP_QUERY_REFERER Receives the URI of the resource where the requested URI was obtained.
 *   HTTP_QUERY_REFRESH Obsolete. Maintained for legacy application compatibility only.
 *   HTTP_QUERY_REQUEST_METHOD Receives the verb that is being used in the request, typically GET or
 *   POST. HTTP_QUERY_RETRY_AFTER Retrieves the amount of time the service is expected to be
 *   unavailable. HTTP_QUERY_SERVER Retrieves information about the software used by the origin server
 *   to handle the request. HTTP_QUERY_SET_COOKIE Receives the value of the cookie set for the
 *   request. HTTP_QUERY_STATUS_CODE Receives the status code returned by the server.
 *   HTTP_QUERY_STATUS_TEXT Receives any additional text returned by the server on the response line.
 *   HTTP_QUERY_TITLE Obsolete. Maintained for legacy application compatibility only.
 *   HTTP_QUERY_TRANSFER_ENCODING Retrieves the type of transformation that has been applied to the
 *   message body so it can be safely transferred between the sender and recipient. HTTP_QUERY_UPGRADE
 *   Retrieves the additional communication protocols that are supported by the server. HTTP_QUERY_URI
 *   Receives some or all of the Uniform Resource Identifiers (URIs) by which the Request-URI resource
 *   can be identified. HTTP_QUERY_USER_AGENT Retrieves information about the user agent that made the
 *   request. HTTP_QUERY_VARY Retrieves the header that indicates that the entity was selected from a
 *   number of available representations of the response using server-driven negotiation.
 *   HTTP_QUERY_VERSION Receives the last response code returned by the server. HTTP_QUERY_VIA
 *   Retrieves the intermediate protocols and recipients between the user agent and the server on
 *   requests, and between the origin server and the client on responses. HTTP_QUERY_WARNING Retrieves
 *   additional information about the status of a response that may not be reflected by the response
 *   status code. HTTP_QUERY_WWW_AUTHENTICATE Retrieves the authentication scheme and realm returned
 *   by the server. The following modifiers can be used with the information values: Value Description
 *   HTTP_QUERY_CUSTOM Causes HttpQueryInfo to search for the header name specified in lpvBuffer and
 *   store the header information in lpvBuffer. HTTP_QUERY_FLAG_COALESCE Not supported.
 *   HTTP_QUERY_FLAG_NUMBER Returns the data as a 32-bit number for headers whose value is a number,
 *   such as the status code. HTTP_QUERY_FLAG_REQUEST_HEADERS Queries request headers only.
 *   HTTP_QUERY_FLAG_SYSTEMTIME Returns the header value as a standard Win32 SYSTEMTIME structure,
 *   which does not require the application to parse the data. Use for headers whose value is a
 *   date/time string, such as "Last-Modified-Time".
 * @param lpBuffer [in\out] Long void pointer to the buffer that receives the information.
 * @param lpdwBufferLength [in\out] Long pointer to a value that contains the length of the data
 *   buffer. When the function returns, this parameter contains the address of a value specifying the
 *   length of the information written to the buffer. When the function returns strings, the following
 *   rules apply: If the function succeeds, lpdwBufferLength specifies the length of the string, in
 *   characters, minus 1 for the terminating null. If the function fails and ERROR_INSUFFICIENT_BUFFER
 *   is returned, lpdwBufferLength specifies the number of bytes that the application must allocate to
 *   receive the string.
 * @param lpdwIndex [in\out] Long pointer to a zero-based header index used to enumerate multiple
 *   headers with the same name. When calling the function, this parameter is the index of the
 *   specified header to return. When the function returns, this parameter is the index of the next
 *   header. If the next index cannot be found, ERROR_HTTP_HEADER_NOT_FOUND is returned.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError.
 *
 * HttpQueryInfo is used to return response or request headers from an HTTP request.
 *
 * You can retrieve different types of data from HttpQueryInfo:
 *
 * strings (default)
 *
 * SYSTEMTIME (for Data: Expires:, headers)
 *
 * DWORD (for STATUS_CODE, CONTENT_LENGTH, and so on if HTTP_QUERY_INFO_NUMBER has been used)
 */
#define HttpQueryInfo  HttpQueryInfoA
#endif // !UNICODE

//
// offline browsing
//

INTERNETAPI
DWORD
WINAPI
InternetAttemptConnect(
    DWORD dwReserved
    );

//
// Internet UI
//

//
// InternetErrorDlg - Provides UI for certain Errors.
//

#define FLAGS_ERROR_UI_FILTER_FOR_ERRORS        0x01
#define FLAGS_ERROR_UI_FLAGS_CHANGE_OPTIONS     0x02
#define FLAGS_ERROR_UI_FLAGS_GENERATE_DATA      0x04
#define FLAGS_ERROR_UI_FLAGS_NO_UI              0x08

/**
 * This function displays a dialog box for the error that is passed to it, if an appropriate dialog
 * box exists. If the FLAGS_ERROR_UI_FILTER_FOR_ERRORS flag is used, the function also checks the
 * headers for any hidden errors and displays a dialog box if needed.
 *
 * @param hWnd [in] Handle to the parent window for any needed dialog box. This parameter can be
 *   NULL if no dialog box is needed.
 * @param hRequest [in] [out] HINTERNET handle to the Internet connection used in the call to
 *   HttpSendRequest.
 * @param dwError [in] Error value for which to display a dialog box. Can be one of the following
 *   values: Value Description ERROR_INTERNET_HTTP_TO_HTTPS_ON_REDIR Notifies the user of the zone
 *   crossing to and from a secure site. ERROR_INTERNET_INCORRECT_PASSWORD Displays a dialog box for
 *   obtaining the user's name and password. (On Microsoft Windows(R) 95, the function first attempts
 *   to use any cached authentication information for the server being accessed, before displaying a
 *   dialog box.) ERROR_INTERNET_INVALID_CA Notifies the user that the Win32(R) Internet function does
 *   not recognize the certificate authority that generated the certificate for this Secure Sockets
 *   Layer (SSL) site. ERROR_INTERNET_POST_IS_NON_SECURE Displays a warning about posting data to the
 *   server through a nonsecure connection. ERROR_INTERNET_SEC_CERT_CN_INVALID Indicates that the SSL
 *   certificate Common Name (hostname field) is incorrect. Displays an Invalid SSL Common Name dialog
 *   box, and lets the user view the incorrect certificate. Also allows the user to select a
 *   certificate in response to a server request. ERROR_INTERNET_SEC_CERT_DATE_INVALID Tells the user
 *   that the SSL certificate has expired.
 * @param dwFlags [in] Unsigned long integer value that contains the action flags. Can be a
 *   combination of these values: Value Description FLAGS_ERROR_UI_FILTER_FOR_ERRORS Scans the
 *   returned headers for errors. Call after using HttpSendRequest. This option detects any hidden
 *   errors, such as an authentication error. FLAGS_ERROR_UI_FLAGS_CHANGE_OPTIONS If the function
 *   succeeds, stores the results of the dialog box in the Internet handle.
 *   FLAGS_ERROR_UI_FLAGS_GENERATE_DATA Queries the Internet handle for needed information. The
 *   function constructs the appropriate data structure for the error. (For example, for Cert CN
 *   failures, the function grabs the certificate.) FLAGS_ERROR_UI_SERIALIZE_DIALOGS Serializes
 *   authentication dialog boxes for concurrent requests on a password cache entry. The lppvData
 *   parameter should contain the address of a pointer to an INTERNET_AUTH_NOTIFY_DATA structure, and
 *   the client should implement a thread-safe, nonblocking callback function.
 * @param lppvData [in] [out] Address of a data structure. The structure can be different for each
 *   error that needs to be handled.
 *
 * @return Returns one of the following values: - ERROR_SUCCESS: The function completed
 *   successfully. - ERROR_CANCELLED: The function was cancelled by the user. -
 *   ERROR_INTERNET_FORCE_RETRY: The function needs to redo its request.
 *
 * Authentication errors are hidden, since the call to HttpSendRequest will complete successfully,
 * but the status code would indicate that the proxy or server requires authentication. The
 * FLAGS_ERROR_UI_FILTER_FOR_ERRORS flag causes the function to search the headers for status codes
 * that indicate user input is needed.
 */
INTERNETAPI
DWORD
WINAPI
InternetErrorDlg(
     IN HWND hWnd,
     IN OUT HINTERNET hRequest,
     IN DWORD dwError,
     IN DWORD dwFlags,
     IN OUT LPVOID * lppvData
     );

INTERNETAPI
DWORD
WINAPI
InternetConfirmZoneCrossing(
     IN HWND hWnd,
     IN LPSTR szUrlPrev,
     IN LPSTR szUrlNew,
     IN BOOL bPost
     );

//#if !defined(_WINERROR_)

//
// Internet API error returns
//

#define INTERNET_ERROR_BASE                     12000

#define ERROR_INTERNET_OUT_OF_HANDLES           (INTERNET_ERROR_BASE + 1)
#define ERROR_INTERNET_TIMEOUT                  (INTERNET_ERROR_BASE + 2)
#define ERROR_INTERNET_EXTENDED_ERROR           (INTERNET_ERROR_BASE + 3)
#define ERROR_INTERNET_INTERNAL_ERROR           (INTERNET_ERROR_BASE + 4)
#define ERROR_INTERNET_INVALID_URL              (INTERNET_ERROR_BASE + 5)
#define ERROR_INTERNET_UNRECOGNIZED_SCHEME      (INTERNET_ERROR_BASE + 6)
#define ERROR_INTERNET_NAME_NOT_RESOLVED        (INTERNET_ERROR_BASE + 7)
#define ERROR_INTERNET_PROTOCOL_NOT_FOUND       (INTERNET_ERROR_BASE + 8)
#define ERROR_INTERNET_INVALID_OPTION           (INTERNET_ERROR_BASE + 9)
#define ERROR_INTERNET_BAD_OPTION_LENGTH        (INTERNET_ERROR_BASE + 10)
#define ERROR_INTERNET_OPTION_NOT_SETTABLE      (INTERNET_ERROR_BASE + 11)
#define ERROR_INTERNET_SHUTDOWN                 (INTERNET_ERROR_BASE + 12)
#define ERROR_INTERNET_INCORRECT_USER_NAME      (INTERNET_ERROR_BASE + 13)
#define ERROR_INTERNET_INCORRECT_PASSWORD       (INTERNET_ERROR_BASE + 14)
#define ERROR_INTERNET_LOGIN_FAILURE            (INTERNET_ERROR_BASE + 15)
#define ERROR_INTERNET_INVALID_OPERATION        (INTERNET_ERROR_BASE + 16)
#define ERROR_INTERNET_OPERATION_CANCELLED      (INTERNET_ERROR_BASE + 17)
#define ERROR_INTERNET_INCORRECT_HANDLE_TYPE    (INTERNET_ERROR_BASE + 18)
#define ERROR_INTERNET_INCORRECT_HANDLE_STATE   (INTERNET_ERROR_BASE + 19)
#define ERROR_INTERNET_NOT_PROXY_REQUEST        (INTERNET_ERROR_BASE + 20)
#define ERROR_INTERNET_REGISTRY_VALUE_NOT_FOUND (INTERNET_ERROR_BASE + 21)
#define ERROR_INTERNET_BAD_REGISTRY_PARAMETER   (INTERNET_ERROR_BASE + 22)
#define ERROR_INTERNET_NO_DIRECT_ACCESS         (INTERNET_ERROR_BASE + 23)
#define ERROR_INTERNET_NO_CONTEXT               (INTERNET_ERROR_BASE + 24)
#define ERROR_INTERNET_NO_CALLBACK              (INTERNET_ERROR_BASE + 25)
#define ERROR_INTERNET_REQUEST_PENDING          (INTERNET_ERROR_BASE + 26)
#define ERROR_INTERNET_INCORRECT_FORMAT         (INTERNET_ERROR_BASE + 27)
#define ERROR_INTERNET_ITEM_NOT_FOUND           (INTERNET_ERROR_BASE + 28)
#define ERROR_INTERNET_CANNOT_CONNECT           (INTERNET_ERROR_BASE + 29)
#define ERROR_INTERNET_CONNECTION_ABORTED       (INTERNET_ERROR_BASE + 30)
#define ERROR_INTERNET_CONNECTION_RESET         (INTERNET_ERROR_BASE + 31)
#define ERROR_INTERNET_FORCE_RETRY              (INTERNET_ERROR_BASE + 32)
#define ERROR_INTERNET_INVALID_PROXY_REQUEST    (INTERNET_ERROR_BASE + 33)
#define ERROR_INTERNET_NEED_UI                  (INTERNET_ERROR_BASE + 34)

#define ERROR_INTERNET_HANDLE_EXISTS            (INTERNET_ERROR_BASE + 36)
#define ERROR_INTERNET_SEC_CERT_DATE_INVALID    (INTERNET_ERROR_BASE + 37)
#define ERROR_INTERNET_SEC_CERT_CN_INVALID      (INTERNET_ERROR_BASE + 38)
#define ERROR_INTERNET_HTTP_TO_HTTPS_ON_REDIR   (INTERNET_ERROR_BASE + 39)
#define ERROR_INTERNET_HTTPS_TO_HTTP_ON_REDIR   (INTERNET_ERROR_BASE + 40)
#define ERROR_INTERNET_MIXED_SECURITY           (INTERNET_ERROR_BASE + 41)
#define ERROR_INTERNET_CHG_POST_IS_NON_SECURE   (INTERNET_ERROR_BASE + 42)
#define ERROR_INTERNET_POST_IS_NON_SECURE       (INTERNET_ERROR_BASE + 43)
#define ERROR_INTERNET_CLIENT_AUTH_CERT_NEEDED  (INTERNET_ERROR_BASE + 44)
#define ERROR_INTERNET_INVALID_CA               (INTERNET_ERROR_BASE + 45)
#define ERROR_INTERNET_CLIENT_AUTH_NOT_SETUP    (INTERNET_ERROR_BASE + 46)
#define ERROR_INTERNET_ASYNC_THREAD_FAILED      (INTERNET_ERROR_BASE + 47)
#define ERROR_INTERNET_REDIRECT_SCHEME_CHANGE   (INTERNET_ERROR_BASE + 48)

//
// FTP API errors
//

#define ERROR_FTP_TRANSFER_IN_PROGRESS          (INTERNET_ERROR_BASE + 110)
#define ERROR_FTP_DROPPED                       (INTERNET_ERROR_BASE + 111)
#define ERROR_FTP_NO_PASSIVE_MODE               (INTERNET_ERROR_BASE + 112)

//
// HTTP API errors
//

#define ERROR_HTTP_HEADER_NOT_FOUND             (INTERNET_ERROR_BASE + 150)
#define ERROR_HTTP_DOWNLEVEL_SERVER             (INTERNET_ERROR_BASE + 151)
#define ERROR_HTTP_INVALID_SERVER_RESPONSE      (INTERNET_ERROR_BASE + 152)
#define ERROR_HTTP_INVALID_HEADER               (INTERNET_ERROR_BASE + 153)
#define ERROR_HTTP_INVALID_QUERY_REQUEST        (INTERNET_ERROR_BASE + 154)
#define ERROR_HTTP_HEADER_ALREADY_EXISTS        (INTERNET_ERROR_BASE + 155)
#define ERROR_HTTP_REDIRECT_FAILED              (INTERNET_ERROR_BASE + 156)
#define ERROR_HTTP_NOT_REDIRECTED               (INTERNET_ERROR_BASE + 160) 

#define ERROR_INTERNET_SECURITY_CHANNEL_ERROR   (INTERNET_ERROR_BASE + 157) 
#define ERROR_INTERNET_UNABLE_TO_CACHE_FILE     (INTERNET_ERROR_BASE + 158) 
#define ERROR_INTERNET_TCPIP_NOT_INSTALLED      (INTERNET_ERROR_BASE + 159) 

#define INTERNET_ERROR_LAST                     ERROR_INTERNET_TCPIP_NOT_INSTALLED

//#endif // !defined(_WINERROR_)

#if defined(__cplusplus)
}
#endif

/*
 * Return packing to whatever it was before we
 * entered this file
 */
#pragma pack(pop, wininet)

#endif // !defined(_WININET_)
