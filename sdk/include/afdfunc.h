/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.
Copyright (c) 1995, 1996, 1997  Microsoft Corporation

Module Name:  

afdfunc.h

Abstract:

Functions exposed from the AFD system process

Notes: 


--*/

// @CESYSGEN IF CE_MODULES_AFD

#ifndef _AFDFUNC_H_
#define _AFDFUNC_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SOCKHAND_DEFINED
DECLARE_HANDLE(SOCKHAND);
typedef SOCKHAND *PSOCKHAND;
#define SOCKHAND_DEFINED
#endif

#include "ras.h"
#include "tapi.h"

//
// Start WINCE API definitions.
//
/**
 * This function establishes a RAS connection between a RAS client and a RAS server. The connection
 * data includes callback and user authentication information.
 *
 * @param dialExtensions This parameter is ignored and should be set to NULL. On Windows CE, RasDial
 *   always uses the default behaviors for the RASDIALEXTENSIONS options.
 * @param pphoneBook This parameter is ignored and should be set to NULL. Dial-up networking stores
 *   phone-book entries in the registry rather than in a phone-book file.
 * @param rasDialParams Pointer to a RASDIALPARAMS structure that specifies calling parameters for
 *   the RAS connection. The caller must set the RASDIALPARAMS structure's dwSize member to the
 *   sizeof(RASDIALPARAMS) to identify the version of the structure being passed.
 * @param NotifierType Specifies the nature of the notifier parameterIf notifier is NULL,
 *   NotifierType is ignored. If notifier is not NULL, set NotifierType to the following value: Value
 *   Description 0xFFFFFFFF 0xFFFFFFFF The notifier parameter is a handle to a window to receive
 *   progress notification messages. In a progress notification message, wParam indicates the
 *   connection state (rasconnstate) which the RAS connection is about to enter, while lParam
 *   indicates whether or not an error occurred. The progress notification message uses the
 *   WM_RASDIALEVENT message code.
 * @param notifier Pointer to a window handle to receive RasDial event notificationsIf this
 *   parameter is not NULL, RasDial sends the window a for each RasDial event. Additionally, the
 *   RasDial call operates asynchronously: RasDial returns immediately, before the connection is
 *   established, and uses the window to communicate its progress. If notifier is NULL, the RasDial
 *   call operates synchronously: RasDial does not return until the connection attempt has completed
 *   successfully or failed. If notifier is not NULL, notifications to the window can occur at any
 *   time after the initial call to RasDial. Notifications end when one of the following events
 *   occurs: The connection is established. In other words, the RAS connection state is
 *   RASCS_Connected. The connection fails. In other words, dwError is nonzero. RasHangUp is called on
 *   the connection. The callback notifications are made in the context of a thread captured during
 *   the initial call to RasDial.
 * @param pRasConn Pointer to a variable of type HRASCONN. You must set the HRASCONN variable to
 *   NULL before calling RasDial. If RasDial succeeds, it stores a handle to the RAS connection into
 *   pRasConn.
 *
 * @return Zero indicates success. In addition, the function stores a handle to the RAS connection
 *   into the variable pointed to by pRasConn. A nonzero error value, either from the set listed in
 *   the RAS header file or ERROR_NOT_ENOUGH_MEMORY, indicates failure.
 *
 * The szCallBackNumber and szPhoneNumber members of the structure pointed to by rasDialParam are
 * not used and should be set to NULL.
 *
 * RasDial will not automatically display the logon dialog box. This is currently done through the
 * Remote Networking application. Applications are responsible for getting the information from the
 * user.
 *
 * Windows CE does not support the ERROR_CANNOT_FIND_PHONEBOOK_ENTRY return value.
 *
 * Errors that occur after the immediate return can be detected by RasGetConnectStatus. Data is
 * available until an application calls RasHangUp to hang up the connection.
 *
 * An application must eventually call RasHangUp whenever a non-NULL connection handle is stored
 * into pRasConn. This applies even if RasDial returns a nonzero (error) value.
 *
 * An application can safely call RasHangUp from a RasDial notifier handler. If this is done,
 * however, the hangup does not occur until the routine returns.
 */
DWORD RasDial (LPRASDIALEXTENSIONS dialExtensions,
	       LPTSTR phoneBookPath,
	       LPRASDIALPARAMS rasDialParam,
	       DWORD NotifierType,
	       LPVOID notifier,
	       LPHRASCONN pRasConn);
/**
 * The RasHangUp function terminates a remote access connection. The connection is specified with a
 * RAS connection handle. RasHangUp releases all RASAPI32.DLL resources associated with the handle.
 *
 * @param Session Handle to the remote access connection to terminate. This is a handle returned
 *   from a previous call to RasDial or RasEnumConnections.
 *
 * @return Zero indicates success. A nonzero error value listed in the RAS header file or
 *   ERROR_INVALID_HANDLE indicates failure.
 *
 * The connection is terminated even if the RasDial call has not yet been completed.
 *
 * After this call, the Session handle can no longer be used.
 */
DWORD RasHangup (HRASCONN Session);	// Kept for historical compatibility
/**
 * The RasHangUp function terminates a remote access connection. The connection is specified with a
 * RAS connection handle. RasHangUp releases all RASAPI32.DLL resources associated with the handle.
 *
 * @param Session Handle to the remote access connection to terminate. This is a handle returned
 *   from a previous call to RasDial or RasEnumConnections.
 *
 * @return Zero indicates success. A nonzero error value listed in the RAS header file or
 *   ERROR_INVALID_HANDLE indicates failure.
 *
 * The connection is terminated even if the RasDial call has not yet been completed.
 *
 * After this call, the Session handle can no longer be used.
 */
DWORD RasHangUp (HRASCONN Session);
/**
 * This function lists all entry names in a remote access phone book.
 *
 * @param Reserved Reserved; set to NULL.
 * @param lpszPhonebook Windows CE: This parameter is ignored. Dial-up networking stores phone-book
 *   entries in the registry rather than in a phone-book file.
 * @param lprasentryname Pointer to a buffer that receives an array of RASENTRYNAME structures, one
 *   for each phone-book entry. Before calling the function, an application must set the dwSize member
 *   of the first RASENTRYNAME structure in the buffer to sizeof(RASENTRYNAME) in order to identify
 *   the version of the structure being passed.
 * @param lpcb Pointer to a variable that that contains the size, in bytes, of the buffer specified
 *   by lprasentryname. On return, the function sets this variable to the number of bytes required to
 *   successfully complete the call.
 * @param lpcEntries Pointer to a variable that the function, if successful, sets to the number of
 *   phone-book entries written to the buffer specified by lprasentryname.
 *
 * @return Zero indicates success. A nonzero error value listed in the RAS header file,
 *   ERROR_BUFFER_TOO_SMALL, or ERROR_NOT_ENOUGH_MEMORY indicates failure.
 *
 * The following sample code enumerates the RAS phonebook entries on the current machine. The code
 * initially calls RasEnumEntries to obtain the size of the buffer to pass in. The code then calls
 * RasEnumEntries again, to enumerate the entries. Note that for both calls, the code sets the
 * dwSize member of the first RASENTRY structure in the buffer to sizeof(RASENTRY) to specify the
 * structure version.
 *
 *     lprasentryname = (LPRASENTRYNAME)LocalAlloc(GPTR,, sizeof(RASENTRYNAME));
 *     lprasentryname->dwSize = sizeof(RASENTRYNAME);
 *     if ((nRet = RasEnumEntries(NULL, NULL, lprasentryname, &cb, &cEntries))
 *         == ERROR_BUFFER_TOO_SMALL)
 *     {
 *         lprasentryname = (LPRASENTRYNAME)GlobalAlloc(GPTR, cb);
 *         lprasentryname->dwSize = sizeof(RASENTRYNAME);
 *     }
 *
 *     // Calling RasEnumEntries to enumerate the phonebook entries
 *     nRet = RasEnumEntries(NULL, NULL, lprasentryname, &cb, &cEntries);
 *
 *     if (nRet != ERROR_SUCCESS)
 *     {
 *         printf("RasEnumEntries failed: Error %d\n", nRet);
 *     }
 *     else
 *     {
 *         printf("Phone book entries in the default phonebook:\n\n");
 *         for(i=0;i < cEntries;i++)
 *         {
 *             printf("%s\n",lprasentryname->szEntryName);
 *             lprasentryname++;
 *         }
 *     }
 */
DWORD RasEnumEntries (LPWSTR Reserved,
		      LPWSTR lpszPhoneBookPath,
		      LPRASENTRYNAME lprasentryname,
		      LPDWORD lpcb,
		      LPDWORD lpcEntries);
/**
 * This function retrieves the connection information saved by the last successful call to the
 * RasDial function for a specified phone book entry.
 *
 * @param lpszPhoneBook Windows CE: This parameter is ignored and should be set to NULL. Dial-up
 *   networking stores phone-book entries in the registry rather than in a phone-book file.
 * @param lpRasDialParams Pointer to a RASDIALPARAMS structure. On input, the dwSize member must
 *   specify the size of the RASDIALPARAMS structure, and the szEntryName member must specify a valid
 *   phone-book entry. On output, the structure receives the connection parameters associated with the
 *   specified phone-book entry. Note that the szPhoneNumber member of the structure does not receive
 *   the phone number associated with the phone-book entry. To get the phone number associated with a
 *   phone-book entry, call the RasGetEntryProperties function.
 * @param lpfPassword Pointer to a flag that indicates whether the function retrieved the password
 *   associated with the user name for the phone-book entry. The function sets this flag to TRUE if
 *   the user's password was returned in the szPassword member of the RASDIALPARAMS structure pointed
 *   to by lpRasDialParams.
 *
 * @return Zero indicates success. ERROR_BUFFER_INVALID indicates that the lpRasDialParams or
 *   lpfPassword pointer is invalid, or the lpRasDialParams buffer is invalid.
 *   ERROR_CANNOT_OPEN_PHONEBOOK indicates that the phone book is corrupted or missing components.
 *   ERROR_CANNOT_FIND_PHONEBOOK_ENTRY indicates that the phone-book entry does not exist.
 */
DWORD RasGetEntryDialParams (LPWSTR lpszPhoneBook,
			     LPRASDIALPARAMS lpRasDialParams,	
			     LPBOOL lpfPassword);
/**
 * This function changes the connection information saved by the last successful call to the RasDial
 * or RasGetEntryDialParams function for a specified phone book entry.
 *
 * @param lpszPhoneBook Windows CE: This parameter is ignored and should be set to NULL. Dial-up
 *   networking stores phonebook entries in the registry rather than in a phonebook file.
 * @param lpRasDialParams Pointer to a RASDIALPARAMS structure that contains the connection
 *   parameters to be associated with the phonebook entry. RasSetEntryDialParams uses the structure's
 *   members as follows:
 * @param dwSize Specifies the sizeof(RASDIALPARAMS) to identify the version of the structure.
 * @param szEntryName Null-terminated string that identifies the phonebook entry to set parameters
 *   for.
 * @param szPhoneNumber Not used; set to NULL.
 * @param szCallbackNumber Not used; set to NULL..
 * @param szUserName Null-terminated string that contains the logon name of the user associated with
 *   this entry. If szUserName is an empty string, the user name is not changed.
 * @param szPassword Null-terminated string that contains the password for the user specified by
 *   szUserName. If szUserName is an empty string, the password is not changed. If szPassword is an
 *   empty string and fRemovePassword is FALSE, the password is set to the empty string. If
 *   fRemovePassword is TRUE, the password stored in this phonebook entry for the user specified by
 *   szUserName is removed regardless of the that contains of the szPassword string.
 * @param szDomain Null-terminated string that contains the name of the domain to log on to. If
 *   szDomain is an empty string, the domain name is not changed.
 * @param fRemovePassword Boolean value that specifies whether to remove the phonebook entry's
 *   stored password for the user specified by lpRasDialParams->szUserName. If fRemovePassword is
 *   TRUE, the password is removed.
 *
 * @return Zero indicates success. ERROR_BUFFER_INVALID indicates that the address or buffer
 *   specified by lpRasDialParams is invalid. ERROR_CANNOT_OPEN_PHONEBOOK indicates that the phonebook
 *   is corrupted or missing components. ERROR_CANNOT_FIND_PHONEBOOK_ENTRY indicates that the
 *   phonebook entry does not exist.
 *
 * The szCallBackNumber and szPhoneNumber members of lpRasDialParams are not used and should be set
 * to NULL.
 */
DWORD RasSetEntryDialParams (LPWSTR lpszPhoneBook,
			     LPRASDIALPARAMS lpRasDialParams,
			     BOOL fRemovePassword);
/**
 * This function retrieves the properties of a phone book entry.
 *
 * @param lpszPhoneBook This parameter is ignored and should be set to NULL. Phone-book entries are
 *   stored in the registry rather than in a phone-book file.
 * @param szEntry Pointer to a null-terminated string that contains an existing entry name. If you
 *   specify an empty string, "", the function returns default values in the buffers pointed to by the
 *   lpbEntry and lpb parameters.
 * @param lpbEntry Pointer to a RASENTRY structure followed by additional bytes for the alternate
 *   phone number list, if there is one. The structure receives the connection data associated with
 *   the phone-book entry specified by the szEntry parameter. Before calling the function, set the
 *   dwSize member of the structure to sizeof(RASENTRY) to identify the version of the structure. This
 *   parameter can be NULL.
 * @param lpdwEntrySize Pointer to a variable that that contains the size, in bytes, of the lpbEntry
 *   buffer. On return, the function sets this variable to the number of bytes required.
 * @param lpb Long pointer to a buffer that receives device-specific configuration information. This
 *   is opaque TAPI device configuration information that you should not manipulate directly. This
 *   parameter can be NULL. For more information about TAPI device configuration, see the
 *   lineGetDevConfig function in the Win32 Telephony (TAPI) Programmer's Reference.
 * @param lpdwSize Long pointer to a variable that that contains the size, in bytes, of the buffer
 *   specified by the lpb parameter. On return, the function sets this variable to the number of bytes
 *   required. This parameter can be NULL if the lpb parameter s NULL. To determine the required
 *   buffer size, call RasGetEntryProperties with lpb set to NULL and lpdwSize set to zero. The
 *   function returns the required buffer size in lpdwSize.
 *
 * @return Zero indicates success. ERROR_INVALID_PARAMETER indicates that the function was called
 *   with an invalid parameter. ERROR_INVALID_SIZE indicates that the value of the dwSize member of
 *   the structure specified in lpbEntry is too small. ERROR_BUFFER_INVALID indicates that the address
 *   or buffer specified by lpbEntry is invalid. ERROR_BUFFER_TOO_SMALL indicates that the buffer size
 *   indicated in lpdwEntrySize is too small. ERROR_CANNOT_OPEN_PHONEBOOK indicates that the phone
 *   book is corrupted or is missing components. ERROR_CANNOT_FIND_PHONEBOOK_ENTRY indicates that the
 *   phone-book entry does not exist.
 *
 * For Windows CE version 1.0 and 1.01, the lpb and lpdwSize parameters are ignored and should be
 * set to NULL. To retrieve device specific configuration information use the RasGetEntryDevConfig
 * function.
 *
 * For Windows CE version 2.0 and later, device configuration information can be retrieved by using
 * the lpb and lpdwSize parameters.
 *
 * Windows CE does not use the alternate phone number list.
 */
DWORD RasGetEntryProperties (LPWSTR lpszPhoneBook,
			     LPWSTR szEntry,
			     LPBYTE lpbEntry,
			     LPDWORD lpdwEntrySize,
			     LPBYTE lpb,
			     LPDWORD lpdwSize);
/**
 * This function changes the connection information for an entry in the phone book or creates a new
 * phone-book entry.
 *
 * @param lpszPhoneBook This parameter is ignored and should be set to NULL. Phonebook entries are
 *   stored in the registry rather than in a phone-book file.
 * @param szEntry Pointer to a null-terminated string that contains an entry name. If the entry name
 *   matches an existing entry, RasSetEntryProperties modifies the properties of that entry. If the
 *   entry name does not match an existing entry, RasSetEntryProperties creates a new phone-book
 *   entry. For new entries, call the RasValidateEntryName function to validate the entry name before
 *   calling RasSetEntryProperties.
 * @param lpbEntry Pointer to a RASENTRY structure that that contains the new connection data to be
 *   associated with the phone-book entry specified by the szEntry parameter. The structure might be
 *   followed by an array of null-terminated alternate phone number strings. The last string is
 *   terminated by two consecutive null characters. The dwAlternateOffset member of the RASENTRY
 *   structure that contains the offset to the first string.
 * @param dwEntrySize Specifies the size, in bytes, of the buffer specified by the lpRasEntry
 *   parameter.
 * @param lpb Pointer to a buffer that contains device-specific configuration information. This is
 *   opaque TAPI device configuration information. For more information about TAPI device
 *   configuration, see the lineGetDevConfig function in the Win32 Telephony (TAPI) Programmer's
 *   Reference.
 * @param dwSize Specifies the size, in bytes, of the lpb buffer.
 *
 * @return Zero indicates success. ERROR_BUFFER_INVALID indicates that the address or buffer
 *   specified by lpbEntry is invalid. ERROR_CANNOT_OPEN_PHONEBOOK indicates that the phone book is
 *   corrupted or missing components.
 *
 * For Windows CE version 1.0 and 1.01, the lpb and dwSize parameters are ignored and should be set
 * to NULL.
 *
 * For Windows CE version 2.0 and later, device configuration information can be set by using lpb
 * and dwSize parameters.
 *
 * Windows CE does not use the alternate phone number list.
 */
DWORD RasSetEntryProperties (LPWSTR lpszPhoneBook,		
			     LPWSTR szEntry,
			     LPBYTE lpbEntry,
			     DWORD dwEntrySize,
			     LPBYTE lpb,
			     DWORD dwSize);
/**
 * This function validates the format of a connection entry name. It must that contains at least one
 * non-white-space alpha-numeric character.
 *
 * @param lpszPhonebook This parameter is ignored and should be set to NULL. Phone-book entries are
 *   stored in the registry rather than in a phone-book file.
 * @param lpszEntry Pointer to a null-terminated string that contains an entry name. For Windows CE,
 *   the entry name must include at least one alphanumeric character and be a valid registry key name.
 *   The entry name cannot begin with a backslash ("\"). Character Description | vertical bar >
 *   greater than symbol < less than symbol ? question mark * asterisk \ backward slash / forward
 *   slash : colon
 *
 * @return Zero indicates success. ERROR_INVALID_NAME or ERROR_ALREADY_EXISTS indicates failure.
 */
DWORD RasValidateEntryName (LPWSTR lpszPhonebook,		
			    LPWSTR lpszEntry);
/**
 * This function deletes an entry from the phone book.
 *
 * @param lpszPhonebook
 * @param This parameter is ignored and should be set to NULL. Phone-book entries are stored in the
 *   registry rather than in a phone-book file.
 * @param lpszEntry Pointer to a null-terminated string that contains the name of an existing entry
 *   to be deleted.
 *
 * @return Zero indicates success. A nonzero RAS error code indicates failure.
 */
DWORD RasDeleteEntry (LPWSTR lpszPhonebook,
		      LPWSTR lpszEntry);
/**
 * This function changes the name of an entry in the phone book.
 *
 * @param lpszPhonebook This parameter is ignored and should be set to NULL. Phone-book entries are
 *   stored in the registry rather than in a phone-book file.
 * @param lpszOldEntry Pointer to a null-terminated string that contains an existing entry name.
 * @param lpszNewEntry Pointer to a null-terminated string that contains the new entry name. Before
 *   calling RasRenameEntry, call the RasValidateEntryName function to validate the new entry name.
 *
 * @return Zero indicates success. ERROR_INVALID_NAME indicates that the lpszNewEntry name is
 *   invalid. ERROR_ALREADY_EXISTS indicates that an entry with the lpszNewEntry name already exists.
 *   ERROR_CANNOT_FIND_PHONEBOOK_ENTRY indicates that the phone-book entry does not exist.
 */
DWORD RasRenameEntry (LPWSTR lpszPhonebook,
		      LPWSTR lpszOldEntry,
		      LPWSTR lpszNewEntry);
/**
 * This function lists all active RAS connections. It returns each connection's handle and phone
 * book entry name.
 *
 * @param lprasconn Long pointer to a buffer that receives an array of RASCONN structures, one for
 *   each RAS connection. Before calling the function, an application must set the dwSize member of
 *   the first RASCONN structure in the buffer to sizeof(RASCONN) in order to identify the version of
 *   the structure being passed.
 * @param lpcb Long pointer to a variable that that contains the size, in bytes, of the buffer
 *   specified by lprasconn. On return, the function sets this variable to the number of bytes
 *   required to enumerate the RAS connections.
 * @param lpcConnections Long pointer to a variable that the function sets to the number of RASCONN
 *   structures written to the buffer specified by lprasconn.
 *
 * @return Zero indicates success. A nonzero error value listed in the RAS header file,
 *   ERROR_BUFFER_TOO_SMALL, or ERROR_NOT_ENOUGH_MEMORY indicates failure.
 */
DWORD RasEnumConnections (LPRASCONN lprasconn,
			  LPDWORD lpcb,
			  LPDWORD lpcConnections);
/**
 * This function retrieves information on the current status of the specified remote access
 * connection. An application can use this call to determine when an asynchronous RasDial call has
 * completed.
 *
 * @param rasconn Handle to the remote access connection for which to retrieve the status. This
 *   handle must have been obtained from RasDial or RasEnumConnections.
 * @param lprasconnstatus Pointer to a RASCONNSTATUS structure that the function fills with status
 *   information. Before calling the function, an application must set the dwSize member of the
 *   structure to sizeof(RASCONNSTATUS) in order to identify the version of the structure being
 *   passed.
 *
 * @return Zero indicates success. A nonzero error value listed in the RAS header file,
 *   ERROR_BUFFER_TOO_SMALL, or ERROR_NOT_ENOUGH_MEMORY indicates failure.
 */
DWORD RasGetConnectStatus (HRASCONN rasconn,				
			   LPRASCONNSTATUS lprasconnstatus);
DWORD RasGetEntryDevConfig (LPCTSTR szPhonebook,
			    LPCTSTR szEntry,
			    LPDWORD pdwDeviceID,
			    LPDWORD pdwSize,
			    LPVARSTRING pDeviceConfig);
DWORD RasSetEntryDevConfig (LPCTSTR szPhonebook,
			    LPCTSTR szEntry,
			    DWORD dwDeviceID,
			    LPVARSTRING lpDeviceConfig);
			    
#ifdef __cplusplus
}
#endif

#ifdef WINCEOEM
#ifdef WINCEMACRO
#include <mafdfunc.h>	// macros
#endif
#endif

#endif  // _AFDFUNC_H_

// @CESYSGEN ENDIF
