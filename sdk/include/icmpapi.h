/*++

Copyright (c) 1991-1998  Microsoft Corporation

Module Name:

    icmpapi.h

Abstract:

    Declarations for the Win32 ICMP Echo request API.

--*/

#ifndef _ICMP_INCLUDED_
#define _ICMP_INCLUDED_


//
// Exported Routines.
//

//++
//
// Routine Name:
//
//     IcmpCreateFile
//
// Routine Description:
//
//     Opens a handle on which ICMP Echo Requests can be issued.
//
// Arguments:
//
//     None.
//
// Return Value:
//
//     An open file handle or INVALID_HANDLE_VALUE. Extended error information
//     is available by calling GetLastError().
//
//--

/**
 * This function creates a handle on which Internet Control Message Protocol (ICMP) requests can be
 * issued.
 *
 * @return An ICMP handle indicates success. INVALID_HANDLE_VALUE indicates failure. To get extended
 *   error information, call GetLastError.
 */
HANDLE
WINAPI
IcmpCreateFile(
    VOID
    );


//++
//
// Routine Name:
//
//     IcmpCloseHandle
//
// Routine Description:
//
//     Closes a handle opened by ICMPOpenFile.
//
// Arguments:
//
//     IcmpHandle  - The handle to close.
//
// Return Value:
//
//     TRUE if the handle was closed successfully, otherwise FALSE. Extended
//     error information is available by calling GetLastError().
//
//--

/**
 * This function closes an Internet Control Message Protocol (ICMP) handle opened by IcmpCreateFile.
 *
 * @param IcmpHandle [in] ICMP handle opened by IcmpCreateFile.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
BOOL
WINAPI
IcmpCloseHandle(
    HANDLE  IcmpHandle
    );



//++
//
// Routine Name:
//
//     IcmpSendEcho
//
// Routine Description:
//
//     Sends an ICMP Echo request and returns any replies. The
//     call returns when the timeout has expired or the reply buffer
//     is filled.
//
// Arguments:
//
//     IcmpHandle           - An open handle returned by ICMPCreateFile.
//
//     DestinationAddress   - The destination of the echo request.
//
//     RequestData          - A buffer containing the data to send in the
//                            request.
//
//     RequestSize          - The number of bytes in the request data buffer.
//
//     RequestOptions       - Pointer to the IP header options for the request.
//                            May be NULL.
//
//     ReplyBuffer          - A buffer to hold any replies to the request.
//                            On return, the buffer will contain an array of
//                            ICMP_ECHO_REPLY structures followed by the
//                            options and data for the replies. The buffer
//                            should be large enough to hold at least one
//                            ICMP_ECHO_REPLY structure plus
//                            MAX(RequestSize, 8) bytes of data since an ICMP
//                            error message contains 8 bytes of data.
//
//     ReplySize            - The size in bytes of the reply buffer.
//
//     Timeout              - The time in milliseconds to wait for replies.
//
// Return Value:
//
//     Returns the number of ICMP_ECHO_REPLY structures stored in ReplyBuffer.
//     The status of each reply is contained in the structure. If the return
//     value is zero, extended error information is available via
//     GetLastError().
//
//--

/**
 * This function sends an Internet Control Message Protocol (ICMP) echo request, and returns one or
 * more replies.
 *
 * @param IcmpHandle [in] ICMP handle opened by IcmpCreateFile.
 * @param DestinationAddress [in] Specifies the destination of the echo request.
 * @param RequestData [in] Buffer that contains the data to be sent in the request.
 * @param RequestSize [in] Number of bytes in the RequestData buffer.
 * @param RequestOptions [in] Pointer to the IP header options for the request; may be NULL.
 * @param ReplyBuffer [out] Buffer to hold any replies to the request. When the function returns,
 *   the buffer will contain one or more ICMP_ECHO_REPLY structures, followed by options and data.
 * @param ReplySize [out] Size, in bytes, of the reply buffer. The buffer must be large enough to
 *   accommodate at least one ICMP_ECHO_REPLY structure plus eight additional bytes (the size of an
 *   ICMP error message).
 * @param Timeout [in] Time, in milliseconds, to wait for replies.
 *
 * @return The number of replies received and stored in the reply buffer indicates success. Zero
 *   indicates failure. Extended error information is available through GetLastError.
 */
DWORD
WINAPI
IcmpSendEcho(
    HANDLE                   IcmpHandle,
    IPAddr                   DestinationAddress,
    LPVOID                   RequestData,
    WORD                     RequestSize,
    PIP_OPTION_INFORMATION   RequestOptions,
    LPVOID                   ReplyBuffer,
    DWORD                    ReplySize,
    DWORD                    Timeout
    );


#endif // _ICMP_INCLUDED_

