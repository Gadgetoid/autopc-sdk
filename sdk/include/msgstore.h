/*---------------------------------------------------------------------------*\
 *
 * (c) Copyright Microsoft Corp. 1996 All Rights Reserved
 *
 *  module: msgstore.h
 *  date:   960105
 *
 *  purpose: Definitions for Mail Message Store
 *
 *  notes:  Forked from \\Core1\PegApps2\src\mepapps\sdk\inc for
 *          Apollo / AutoPC development by James McGuire (a-jammcg) on 
 *          1/23/98
 *
\*---------------------------------------------------------------------------*/

#ifndef MSGSTORE_H
    #define MSGSTORE_H

    // Only include resource defs for the .RC file...
    #ifndef __MSGSTORE_RC__

        // Load all the filesystem/registry/database definitions
        #ifdef UNDER_NT // this should never be defined for the AutoPC, 
                        // even under emulation. (we use another flag)

            // Is this a REMOTE version (versus local using the SDK)?
            #ifdef MSGSTORE_RPC

                #ifndef UNDER_REPL
                    #include <rapi.h>
                #endif

            #else //MSGSTORE_RPC Under the SDK...

                // The Emulator has a conflict with _DBGPARAM definition...
                #ifdef DEBUG
                    #define DEBUG_WAS_ON
                    #undef DBGCHK
                    #undef DEBUG
                    #undef DEBUGMSG
                    #undef DEBUGCHK
                    #undef DEBUGREGISTER
                #endif //DEBUG

                #include <wceemul.h>

                #ifdef DEBUG_WAS_ON
                #undef DEBUG_WAS_ON
                #define DEBUG
                #endif //DEBUG_WAS_ON

            #endif //MSGSTORE_RPC

        #else //UNDER_NT - either the device or AutoPC

            #include <windbase.h>

        #endif //UNDER_NT

/*------------------------------------------------------------------------*/
/* Useful constants and typedefs.                                         */
/*------------------------------------------------------------------------*/

#define MAIL_VERSION    0x0200

// Mail folders
#define MAIL_FOLDER_ALL         0x000000FF  // Source (current) folder
#define MAIL_FOLDER_FIRST       0x00000000  // Start of user defined folders
#define MAIL_FOLDER_LAST        0x00000014  // End of user defined folders
                                            // could go to 0xfb, but limit to 20
#define MAIL_FOLDER_SENT        0x000000FC  // copy of sent mail
#define MAIL_FOLDER_OUTBOX      0x000000FD  // local OUTBOX (last local folder)
#define MAIL_FOLDER_INBOX       0x000000FE  // univeral INBOX
#define MAIL_FOLDER_ANY         0x000000FF  // Search for any folder
#define MAIL_FOLDER_NAMELEN     16          // Max folder name length

#define MAIL_FOLDER_TARGET      0x0000FF00  // Target folder for MAIL_COPY
#define MAIL_TARGET_SHIFT       8           // number of bits to shift


// Status flags
#define MAIL_STATUS_ALL         0xC3FF0000  // Status of this message
#define MAIL_STATUS_FREE        0x00010000  // This is a free message

//BUGBUG - AutoPC specific changes
//
// We changed this definition to clear up the semantics of deleted / ok to
// delete / locked.  We are never use the delete flag, however we are in need
// of a lock flag.
//
//#define MAIL_STATUS_DELETE    0x00020000  // Delete message
#define MAIL_STATUS_LOCKED      0x00020000  // Marked as locked

#define MAIL_STATUS_COPY        0x00040000  // Copy message to local target
#define MAIL_STATUS_MOVE        0x00080000  // Marked for copy and delete
#define MAIL_STATUS_READ        0x00100000  // Marked as read (during a MailGet)
#define MAIL_STATUS_SERVICE     0x00200000  // Inbox Message exists on a service
#define MAIL_STATUS_COMPOSED    0x00400000  // Composed locally (To: address)
#define MAIL_STATUS_REMOTE      0x00800000  // Inbox body ONLY exists on service
#define MAIL_STATUS_GC          0x01000000  // Garbage collection

#define MAIL_STATUS_NOT         0x02000000  // Look for invert of status bits (GET)
#define MAIL_STATUS_ANY         (MAIL_STATUS_NOT|MAIL_STATUS_FREE)
#define MAIL_STATUS_ALIVE       (MAIL_STATUS_ANY|MAIL_STATUS_DELETE)
#define MAIL_STATUS_LOCAL       (MAIL_STATUS_ALIVE|MAIL_STATUS_SERVICE)
#define MAIL_STATUS_BODY        (MAIL_STATUS_ALIVE|MAIL_STATUS_REMOTE)
#define MAIL_STATUS_UNREAD      (MAIL_STATUS_ALIVE|MAIL_STATUS_READ)
#define MAIL_GET_BODY           0x08000000  // Get body (during a MailGet)

// Mail message store flags:
#define MAIL_FLAGS_ALL          0xFF000000  // All defined store flags
#define MAIL_GET_FLAGS          0x10000000  // ONLY get flags field (during a get)
#define MAIL_FULL               0x20000000  // Get full body when copying
#define MAIL_STATUS_ATTACHMENTS 0x40000000  // This message has attachments
#define MAIL_STATUS_ATT_REQ     0x80000000  // Attachment marked for download

#define MAIL_UNUSED             0x00000000  // Currently unused bits

#define MAXSTRPROPLEN   (16*4092)           // Database max string length
#define MAXSTRPROPCHARS (8*4092)            // Since we use WCHARS

/**
 * This structure is used by the Mail and Transport functions to store the contents of messages
 * being sent and received.
 *
 * A mail message can be either local or linked to a service. Local messages exist only the device.
 * User-composed messages fall into this category. Service-lined messages, on the other hand, exist
 * on a service somewhere, but are referenced locally. Messages that are synchronized and retrieved
 * by means of the SMTP/POP3 transport fall into this category.
 */
typedef struct MailMsg_s {
    /**
     * Specifies an internal identification number maintained by the system. This identification number
     * is used by library routines to access messages in the message store. Applications should not
     * attempt to change the value stored in this member.
     */
    DWORD       dwMsgId;            // ID of message for retrieval (ignore on store)
    /**
     * Specifies the folder that contains the message, the status of the message, and how the message is
     * handled. These mail flags are divided into three categories: folder flags, status flags, and
     * message flags. The flags and a brief description of their meanings are listed below.
     *
     * Folder flags determine which folder to locate or store the message in. Use only one of the
     * following folder flags in combination with status and message flags: Value Description
     * MAIL_FOLDER_ALL Folder flag mask MAIL_FOLDER_FIRST Start of user-defined folders MAIL_FOLDER_LAST
     * End of user-defined folders MAIL_FOLDER_SENT Copy of sent mail MAIL_FOLDER_OUTBOX Local OUTBOX
     * (last local folder) MAIL_FOLDER_INBOX Universal INBOX MAIL_FOLDER_ANY Search for any folder
     * during "Get" MAIL_FOLDER_TARGET Target folder for MAIL_COPY
     *
     * Status flags verify the status of the message being stored or retrieved, or whether the message
     * has attachment. Status flags can be used to determine what type of messages to search for when
     * calling MailFirst and MailNext functions. These flags can be any combination of the following
     * values: Value Description MAIL_STATUS_ALL Status flag mask. MAIL_STATUS_FREE Message deleted -
     * free slot. MAIL_STATUS_DELETE Message set to be deleted. MAIL_STATUS_COPY Message set to be
     * copied to local target. MAIL_STATUS_READ Message marked as having been read. MAIL_STATUS_SERVICE
     * INBOX Message exists on a service. MAIL_STATUS_COMPOSED Set for outgoing messages (newly
     * composed, replied, or forwarded). In Windows CE version 2.0, an outgoing message can be saved and
     * later re-edited using the outgoing dialog box that includes the SEND button. MAIL_STATUS_REMOTE
     * INBOX body exists only on service. MAIL_STATUS_NOT Look for invert of status bits (GET).
     * MAIL_STATUS_ANY (MAIL_STATUS_NOT | MAIL_STATUS_FREE). MAIL_STATUS_ALIVE (MAIL_STATUS_ANY |
     * MAIL_STATUS_DELETE). MAIL_STATUS_LOCAL (MAIL_STATUS_ALIVE | MAIL_STATUS_SERVICE).
     * MAIL_STATUS_BODY (MAIL_STATUS_ALIVE | MAIL_STATUS_REMOTE). MAIL_STATUS_UNREAD (MAIL_STATUS_ALIVE
     * | MAIL_STATUS_READ). MAIL_STATUS_ATTACHMENTS The message has attachments. MAIL_STATUS_ATT_REQ The
     * message's attachment is marked for download.
     *
     * Message flags determine how the message will be handled and how much of the message is retrieved
     * on a mail get. If none of the message flags are set, all members but the body are retrieved. Of
     * the following flags, use any combination of the first two flags with one of the remaining flags.
     * Value Description MAIL_FLAGS_ALL Message flag mask. MAIL_KEEP Move from OUTBOX to FILE after
     * sent. In Windows CE version 2.0, this flag is no longer used. Instead, the client application
     * checks the current registry settings to determine whether it does or does not save a message in
     * the Sent Item folder. MAIL_GET_BODY Get body (during a MailGet). MAIL_GET_FLAGS Get only flags
     * member (during a get). MAIL_FULL Get full body when copying.
     */
    DWORD       dwFlags;            // MAIL_* flags
    /**
     * Specifies the size, in bytes, of the entire message on the service.
     */
    DWORD       dwMsgLen;           // Length of complete body (on service)
    /**
     * Specifies the size, in bytes, of the message as maintained in the message store.
     */
    WORD        wBodyLen;           // Local body length (maintained by msgstore)
    /**
     * Specifies the date and time the message was received by the service.
     */
    FILETIME    ftDate;             // time message was received
    /**
     * Null-terminated string that contains a unique identification number assigned by the service. The
     * service uses this identification number to access the desired message.
     */
    LPWSTR      szSvcId;            // Service defined ID
    /**
     * Null-terminated string that contains the name of the service. Applications can use this name to
     * link messages to a particular service.
     */
    LPWSTR      szSvcNam;           // Service name
    /**
     * Pointer to the header members. The header consists of entries made up of two members, a name and
     * an associated value. The name members are separated from the value members by a NULL character,
     * and the entries are separated from each other by a NULL character. The header string is
     * terminated with two consecutive NULL characters.
     */
    WCHAR*      pwcHeaders;         // NULL separated miscellaneous header fields
    /**
     * Null-terminated string that contains the body of the message.
     */
    LPWSTR      szBody;             // Message body
    /**
     * Object identifier. The object identifier is assigned by the system and can be used as a key for
     * storing and receiving messages. The object identifier is set when the message is inserted in the
     * message store using the MailPut function and returned in this member when the MailFirst or
     * MailNext functions are called.
     */
    CEOID       oid;                // Database object ID (leave alone!)
    /**
     * Handle to the private heap used for all storage related to this message. Any storage allocated to
     * this heap is freed when the MailFree function is called.
     */
    HANDLE      hHeap;              // Heap for all message storage
} MailMsg;

/**
 * This structure is used to describe a single attachment to a mail message.
 *
 * From the user point of view, an attachment is the file (szOriginalName) attached to the message.
 * For an application developer, however, the attachment may be conveniently viewed as consisting of
 * a header and the attached file. The header is the MailAtt data structure itself. The original
 * file name does not contain path information.
 *
 * An application developer may want to work with either local or non-local attachments. A local
 * attachment has a header and a copy (szLocalName) of the original file (szOriginalName) stored on
 * a Windows CE device. A nonlocal attachment does not store the attached file locally and is simply
 * a place-holder for the original file. For a non-local attachment, szLocalName must be set NULL
 * and ulSize specified.
 *
 * Nonlocal attachments are possible only when a message is linked to a service. For some services,
 * an attachment header can be used to make the file local on demand.
 */
typedef struct MailAtt_s {
    /**
     * Number, counting from 1, to indicate which attachment is specified.
     */
    UINT        uiAttachmentNumber; // which attachment is specified
    /**
     * This member has three bit-masks to categorize three groups of the mail attachment flags: *_ALL_*,
     * *_THIS_*, and *_NUMBER_*. Value Description ATT_ALL_FLAGS_MASK For flags that apply to all
     * attachments to the message. Currently, no such flags are defined in this category.
     * ATT_THIS_FLAGS_MASK For flags that apply only to a specified attachment. The following table
     * shows the two flags that are currently defined in the category. ATT_DISP_RETRIEVE User has
     * requested to download the non-local attachment to the message. Set only if ATT_DOWNLOADABLE is
     * set. ATT_DOWNLOADABLE The originating transport is capable of downloading the attachment
     * independently. ATT_NUMBER_MASK For number masks used to mark the number of attachment files (or
     * headers) to the mail message. Currently, no number mask is defined.
     */
    DWORD       dwFlags;            // ATT_* flags
    /**
     * Character position of the attachment in the text portion of the message. Not currently supported.
     */
    ULONG       ulCharacterPosition;// not used
    /**
     * Size of the attached file. For MailPutAttachment it must be specified for a non-local attachment
     * when szLocalName is NULL. For MailgetAttachment it is assigned to the size of the attached file
     * for either a local or a non-local attachment.
     */
    ULONG       ulSize;             // the size of the attachment, in bytes
    /**
     * Null-terminated string that contains the name of the original file of attached to the message,
     * without path information.
     */
    LPWSTR      szOriginalName;     // the original name of the file
    /**
     * Null-terminated string that contains the path name of the attached file on a Windows CE device.
     * It must be set to NULL for a nonlocal attachment.
     */
    LPWSTR      szLocalName;        // the local name of the file
} MailAtt, *lpMailAtt;

#pragma warning( disable:4200 ) // don't warn about 0-size array
/**
 * This structure is used to describe a series of mail attachments.
 */
typedef struct MailAttArray_s {
    /**
     * Specifies a bitmask of flags that apply to all of the attachments. Flags not in the
     * ATT_ALL_FALGS_MASK area are ignored. Currently, no valid flags are supported.
     */
    DWORD       dwFlags;
    /**
     * Count of attachments in the following AttArray.
     */
    UINT        uiAttCount;
    /**
     * Array of MailAtt structures. The uiAttCount member specifies the number of the elements in the
     * array.
     */
    lpMailAtt   AttArray[];   
} MailAttArray, *lpMailAttArray;

/**
 * This structure is used internally by transports to describe non-Interpersonal Message (IPM) data
 * on a message.
 */
typedef struct MailNonIpmInfo_s {
    /**
     * Null-terminated string that contains the header "Type" of the non-IPM message.
     */
    LPWSTR      szMessageClass;
    /**
     * Count of non-IPM properties in the following propArray.
     */
    UINT        uiPropCount;
    /**
     * Array of CEPROPVAL structures. The uiPropCount member specifies the number of the elements in the
     * array.
     */
    CEPROPVAL   propArray[];
} MailNonIpmInfo, *lpMailNonIpmInfo;
#pragma warning( default:4200 )


// Flags used in the MailAtt structure

#define ATT_ALL_FLAGS_MASK          0xFF000000
#define ATT_THIS_FLAGS_MASK         0x00FF0000
#define ATT_NUMBER_MASK             0x0000FFFF
#define ATT_DISP_RETRIEVE           0x00010000
#define ATT_DOWNLOADABLE            0x00020000

// Header strings used in the PROPID_ATT_STRINGS property

#define ATT_HEADER_NAME             L"A"
#define ATT_HEADER_SIZE             L"S"
#define ATT_HEADER_NAME_PREFIX      L"L"
#define ATT_HEADER_DISPOSITION      L"D"

// Per-attachment codes used in the ATT_HEADER_DISPOSITION field.

#define ATT_DISPOSITION_NONE        L' '
#define ATT_DISPOSITION_RETRIEVE    L'R'
#define ATT_DISPOSITION_DELETE      L'X'

#define MAX_ATTACHMENTS 64

/********************************************************************\
 *                                                                  *
 *  Mail Database Layout:                                           *
 *                                                                  *
 *  HEAD:       Id:UI4:0x00000000,Ver:UI2:LastID:UI4                *
 *  Msg:        Id:UI4:0xxxxxxxxx,Flags:UI4,MsgLen:UI4,BodyLen:UI2, *
 *                  Date:FT,From:WSTR,PreSubject:WSTR,                              *
 *                  Subject:WSTR,Headers:Blob,Body:LPWSTR,          *
 *                  SvcOid:UI4
 *                                                                  *
 *  Sort Fields:        From Subj Date BodyLen                      *
 *                                                                  *
 *                                                                  *
 *  Helper Database Layout:                                         *
 *                                                                  *    
 *  Folder:     FldId:UI2:0x00xx,FldNam:WSTR                        *
 *  SvcId:      SvcNam:WSTR,SvcId:WSTR,MsgId:UI4,MsgOid:UI4         *
 *                                                                  *
 *  Sort Fields:        FldId FldNam SvcId MsgId                                 *
 *                                                                  *
\********************************************************************/

#define MAIL_ID_HEAD        0x00000000

#define MAKEPROP(n,t)   ((n<<16)|CEVT_##t)
#define PROPNUM(name)       (PROPID_##name >> 16)

//
// Message database fields.
//
#define PROPID_ID           MAKEPROP(0,UI4)
#define PROPID_FLAGS        MAKEPROP(1,UI4)
#define PROPID_MSGLEN       MAKEPROP(2,UI4)
#define PROPID_BODYLEN      MAKEPROP(3,UI2)
#define PROPID_DATE         MAKEPROP(4,FILETIME)
#define PROPID_FROM         MAKEPROP(5,LPWSTR)
#define PROPID_PRESUBJECT   MAKEPROP(6,LPWSTR)
#define PROPID_SUBJECT      MAKEPROP(7,LPWSTR)
#define PROPID_HEADERS      MAKEPROP(8,BLOB)
#define PROPID_SVCOID       MAKEPROP(9,UI4)
#define PROPID_BODY         MAKEPROP(10,LPWSTR)
#define PROPID_VERSION      MAKEPROP(11,UI2)
#define PROPID_LASTID       MAKEPROP(12,UI4)

//
// Helper database fields.
//
#define PROPID_FLDID        MAKEPROP(0,UI2)
#define PROPID_FLDNAM       MAKEPROP(1,LPWSTR)
#define PROPID_SVCNAM       MAKEPROP(2,LPWSTR)
#define PROPID_SVCID        MAKEPROP(3,LPWSTR)
#define PROPID_MSGID        MAKEPROP(4,UI4)
#define PROPID_MSGOID       MAKEPROP(5,UI4)

#define PROPID_ATT_INFO     MAKEPROP(12,UI4)
#define PROPID_ATT_STRINGS  MAKEPROP(13,BLOB)

/*-----------------------------------------------------------------------*/
/* Public routines.                                                      */
/*-----------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * This function retrieves the error condition set by the last called mail function.
 *
 * @param hMail Handle to the mail context. This handle is created by the MailOpen function.
 *
 * @return The value of the last error code as an integer indicates success.
 *
 * Each call to a mail function sets an error code. The MailError function retrieves the code and
 * returns it as an integer. Negative values indicate warnings, positive values indicate errors, and
 * zero indicates MailError completed successfully. To ensure the correct error value is captured,
 * call MailError immediately after the transport function call.
 */
int    MailError(              // Get last error <0=ERR >0=WRN 0=NONE
    HANDLE          hMail);             // Mail context
    
typedef int (*PMAILERROR)(HANDLE);

/**
 * This function retrieves the last occurrence of a mail error condition, fills a text string with a
 * description of the error, and sets a pointer to the line number where the error occurred.
 *
 * @param hMail Handle to the mail context. This handle is created by the MailOpen function.
 * @param szBuffer Pointer to a wide character string array that contains a description of the error
 *   condition issued by the last called mail function.
 * @param iBufferLen Length, in characters, of the string array receiving the error description.
 * @param piSrcLine Pointer to an integer that contains the line number where the error occurred. If
 *   no errors are encountered, the value pointed to by this parameter is set to NULL.
 *
 * @return The value of the last error code as an integer indicates success.
 *
 * The MailErrorMsg function operates with the same behavior as the MailError function with the
 * exception of the additional information it provides.
 */
int     MailErrorMsg(           // Get last mail error (printable)
    HANDLE          hMail,              // Mail context
    LPWSTR          szBuf,              // Buffer to fill
    int             iBufLen,            // Length of buffer in chars
    int*            piSrcLine);         // Line where error occured (or NULL)
    
typedef int (*PMAILERRORMSG)(HANDLE,LPWSTR,int,int*);

/**
 * This function opens the message store and obtains a handle to the mail context.
 *
 * @param phNewMail Pointer to the handle created by MailOpen for identifying the mail context.
 * @param fAllowCreate If this Boolean is TRUE, MailOpen attempts to create the message store if it
 *   does not already exist. If the message store cannot be created, or if the required system message
 *   folders cannot be created, MailOpen fails. If this Boolean is FALSE and the message store does
 *   not exist, MailOpen fails.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   MailError or MailErrorMsg.
 *
 * Release the handle created by the MailOpen function with the MailClose function.
 */
BOOL    MailOpen(               // Get mail started
    HANDLE*         phMail,             // Returned handle
    BOOL            fAllowCreate);      // Allow creation of dir and db?
    
typedef BOOL (*PMAILOPEN)(HANDLE*,BOOL);

/**
 * This function attempts to open the mail database and specify a window handle to receive
 * DB_CEOID_* notifications of changes made to the database by different handles.
 *
 * @param phMail Out parameter to receive the mail handle. This handle is set even if the function
 *   fails, so that the MailError function can be called against the returned handle to obtain the
 *   specific error message.
 * @param fAllowCreate If this Boolean is TRUE, the database is created if it does not already
 *   exist. If this Boolean is FALSE, the call fails when the specified database cannot be opened.
 * @param hwndNotify Handle to the window that receives DB_CEOID_* notifications when the database
 *   is modified by handles other than the one used to open it.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
BOOL    MailOpenNotify(                 // Get mail started
    HANDLE*         phMail,             // Returned handle
    BOOL            fAllowCreate,       // Allow creation of dir and db?
    HWND            hwndNotify);        // HWND for DB notifications      
    
typedef BOOL (*PMAILOPEN)(HANDLE*,BOOL);

/**
 * This function is used to add, delete, or rename mail folders.
 *
 * @param hMail Handle to the mail context. This handle is created by the MailOpen function.
 * @param bId Unique integer from zero to 255 that identifies the mail folder. Since a system folder
 *   cannot be modified or deleted, this cannot be one of the following identifiers:
 *   MAIL_FOLDER_INBOX; MAIL_FOLDER_OUTBOX; MAIL_FOLDER_SENT.
 * @param szName Pointer to a buffer that contains a null-terminated string that identifies the name
 *   of the mail folder. If this parameter is NULL, then the folder identified by bId is deleted.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   MailError or MailErrorMsg.
 *
 * If the bId parameter identifies a folder that already exists in the message store the
 * MailPutFolder function renames the folder to the szName string. If the folder exists and szName
 * is NULL the folder is deleted. If the bId identifier is not found in the database, a folder is
 * created with the name pointed to by the szName parameter.
 */
BOOL    MailPutFolder(          // Set new folder name
    HANDLE          hMail,              // Current mail context
    BYTE            bId,                // Folder ID
    LPWSTR          szName);            // Name to set (NULL = DELETE)
    
typedef BOOL (*PMAILPUTFOLDER)(HANDLE,BYTE,LPWSTR);

/**
 * This function retrieves the name of a mail folder from the message store.
 *
 * @param hMail Handle to the mail context. This handle is created by the MailOpen function.
 * @param piId Pointer to the identification number that specifies the mail folder. The identifier,
 *   a unique integer from zero to 255, is set by the MailPutFolder function. After calling
 *   MailGetFolderName, if the folder specified by szName cannot be found, the value pointed to by
 *   piId is the identifier of the next folder found. If no folder can be found, then piId points to a
 *   negative value.
 * @param piLen Pointer to the length, in characters, of the szName buffer parameter. If the string
 *   is longer than (piLen - 1), it is truncated. After calling MailGetFolderName, the value pointed
 *   to by piLen is the actual number of characters needed for the string being passed back to szName
 *   plus a Terminating null character character.
 * @param szName Pointer to the buffer that receives the name of the mail folder that corresponds
 *   with the specified identification number.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   MailError or MailErrorMsg.
 */
BOOL    MailGetFolderName(      // Get folder name
    HANDLE          hMail,              // Current mail context
    int*            piId,               // In=Folder ID, Out=Next used ID or -1
    int*            piLen,              // In=buflen Out=needed chrs with terminator
    LPWSTR          szName);            // Buffer to fill (NULL=get length)

typedef BOOL (*PMAILGETFOLDERNAME)(HANDLE,int*,int*,LPWSTR);

/**
 * This function retrieves the identification number of a mail folder from the message store.
 *
 * @param hMail Handle to the mail context. This handle is created by the MailOpen function.
 * @param pbId If the folder name pointed to by szName exists in the message store, the value of
 *   this parameter is set to the identification number associated with the name.
 * @param szName Null-terminated string that contains the name of the mail folder being searched.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   MailError or MailErrorMsg.
 */
BOOL    MailGetFolderId(        // Get folder ID
    HANDLE          hMail,              // Current mail context
    BYTE*           pbId,               // Folder ID to return
    LPWSTR          szName);            // Name to match
    
typedef BOOL (*PMAILGETFOLDERID)(HANDLE,BYTE*,LPWSTR);

/**
 * This function creates a new mail entry in the message store.
 *
 * @param hMail Handle to the mail context. This handle is created by the MailOpen function.
 * @param pmm Pointer to the MailMsg structure that contains the information for the new entry.
 *   MailPut ignores the dwMsgID member of the MailMsg structure.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   MailError or MailErrorMsg.
 *
 * If the MailPut function is successful, the oid member of the MailMsg structure is set with a
 * unique identification number for this mail entry. The oid can be used by other mail functions to
 * reference this entry.
 *
 * MailPut is for adding new entries to the message store. To change existing entries, use the
 * MailUpdate function.
 *
 * If necessary, a caller should set the pwcHeader member of the MailMsg structure by calling the
 * MailSetField function. This ensures a proper initialization of the hHeap pointer in the MailMsg
 * structure. Otherwise, MailPut will return an error.
 */
BOOL    MailPut(                // Create a new mail entry
    HANDLE          hMail,              // Current mail context
    MailMsg*        pmm);               // Item information (dwMsgID ignored)
    
typedef BOOL (*PMAILPUT)(HANDLE,MailMsg*);

/**
 * This function adds or change an attachment to a mail message.
 *
 * @param hMail Handle to the current mail context. This handle is created by the MailOpen function.
 * @param pmm Pointer to the mail message structure to which the attachment is to be added. The
 *   message must have been written to the object store so that the oid member has been set properly.
 * @param pma Pointer to the mail attachment structure to be added to the message if the attachment
 *   identification number, uiAttachmentNumber, is greater than the current number of attachments.
 *   Otherwise it points to the new attachment to replace the existing one of the same
 *   uiAttachmentNumber value.
 *
 * @return TRUE indicates success. FALSE indicates failure. In the latter case, the caller is
 *   responsible for the disposition of the file. To get extended error information, call MailError or
 *   MailErrorMsg.
 *
 * For a local attachment, that is, when szLocalName (a member of the MailAtt structure) is set to a
 * non-NULL value, the MailPutAttachment function stores a local copy of the original file in a
 * special folder which is constructed from the registry entries for the attachment directory.
 *
 * There can be up to 64 attachments to a message. When a single file is attached more than once,
 * the MailPutAttachment function ensures that every local file has a unique path (szLocalName).
 *
 * Since a local file gets moved, the local name (szLocalName) supplied to the MailPutAttachment
 * function will be different from its counterpart retrieved from the MailGetAttachment function.
 *
 * When a user composes a message with a file attached, she may want to make a copy of the attached
 * file. In this case, the application should make a copy of the original before invoking the
 * MailPutAttachment function. It is unwise to assume that the transport service will perform such
 * an operation.
 */
BOOL    MailPutAttachment(              // Create a new mail attachment
    HANDLE          hMail,              // Current mail context
    MailMsg*        pmm,                // message the attachment is on
    MailAtt*        pma);               // Item information 
    
typedef BOOL (*PMAILPUTATTACHMENT)(HANDLE,MailMsg*,MailAtt*);

/**
 * This function deletes a mail attachment.
 *
 * @param hMail Handle to the current mail context. This handle is created by the MailOpen function.
 * @param pmm Pointer to the mail message from which the attachment is to be deleted.
 * @param pma Pointer to the mail attachment to be deleted.
 * @param fFullDelete Boolean that is set to TRUE to delete the entire attachment. Otherwise, the
 *   file is deleted, but the header remains.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   MailError or MailErrorMsg.
 */
BOOL    MailDeleteAttachment(           // Delete a mail attachment
    HANDLE          hMail,              // Current mail context
    MailMsg*        pmm,                // message the attachment is on
    MailAtt*        pma,                // Item information 
    BOOL            fFullDelete);       // Whether to delete header or not.
    
typedef BOOL (*PMAILDELETEATTACHMENT)(HANDLE,MailMsg*,MailAtt*,BOOL);

/**
 * This function retrieves a mail entry from the message store.
 *
 * @param hMail Handle to the mail context. This handle is created by the MailOpen function.
 * @param pmm Pointer to the MailMsg structure that contains the object identifier of the message to
 *   be retrieved and the flags that determine how much of the message will be retrieved. When MailGet
 *   returns, this structure contains the message retrieved from the message store. Two of the message
 *   flags determine how much of the message to retrieve. If MAIL_GET_FLAGS is set, only the flags and
 *   the object identifier are returned. Using this option does not require any memory to be allocated
 *   for the message. If the MAIL_GET_BODY flag is set, the entire message is loaded into memory. This
 *   requires the system to allocate memory from the global heap. If neither of these flags is set,
 *   all of the message except the body (that is, the header) is retrieved. Memory for this option is
 *   allocated from the private heap. To free memory allocated by this function, use the MailFree
 *   function.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   MailError or MailErrorMsg.
 *
 * The entry retrieved is based on the value of the oid member of the MailMsg structure when the
 * MailGet function is called.
 *
 * Changing the values of the MailMsg variable does not affect the message store until the message
 * is reinserted by calling the MailUpdate function.
 *
 * For more information about mail flags, see MailMsg.
 */
BOOL    MailGet(                // Get a message
    HANDLE          hMail,              // Current mail context
    MailMsg*        pmm);               // 

typedef BOOL (*PMAILGET)(HANDLE,MailMsg*);

/**
 * This function retrieves an attachment to a mail message.
 *
 * @param hMail Handle to the current mail context. This handle is created by the MailOpen function.
 * @param pmm Pointer to the mail message to which the attachment belongs.
 * @param pma Pointer to the mail attachment being requested from the message. The caller must
 *   specify the uiAttachmentNumber member to identify the attachment for retrieval. If pma is NULL,
 *   the function returns the number of attachments to the message.
 *
 * @return The number of the retrieved attachment-if one was specified-or the total count of
 *   attachments-if none was specified-indicates success. A value of -1 indicates an error.
 */
INT    MailGetAttachment(              // Get an attachment
    HANDLE          hMail,              // Current mail context
    MailMsg*        pmm,                // 
    MailAtt*        pma);               // 

typedef UINT (*PMAILGETATTACHMENT)(HANDLE,MailMsg*,MailAtt*);

/**
 * This function requests a non-local attachment to a service-linked message for download, if the
 * service allows that.
 *
 * @param hMail Handle to the current mail context. This handle is created by the MailOpen function.
 * @param pmm Pointer to the mail message to which the attachment belongs.
 * @param pma Pointer to the mail attachment being requested. The caller must specify the
 *   uiAttachment member to identify the number of the requested attachment.
 * @param bRetrieve Request to download the attachment when this flag is TRUE. Otherwise, cancel the
 *   earlier request.
 *
 * @return TRUE indicates success. FALSE indicates failure, or that the service does not allow
 *   individual download.
 *
 * If the request is successful, download will be started next time when the mail client is
 * connected to a server.
 *
 * To get extended error information, use MailError or MailErrorMsg.
 */
BOOL    MailRequestAttachment(              // Request  attachment download
    HANDLE          hMail,              // Current mail context
    MailMsg*        pmm,                // mail msg attachment is on
    MailAtt*        pma,                // attachment being requested
    BOOL            bRetrieve);         // Request retrieve, or cancel?

typedef BOOL (*PMAILREQUESTATTACHMENT)(HANDLE,MailMsg*,MailAtt*,BOOL);

/**
 * This function retrieves the object identifier of a mail entry from the message store based on the
 * value of the service identifier.
 *
 * @param hMail Handle to the mail context. This handle is created by the MailOpen function.
 * @param pmm Pointer to the MailMsg structure that contains the service name and identifier being
 *   passed in when calling MailGetSvcId. After calling MailGetSvcId, the object identifier (the oid
 *   member) and associated flags (the dwFlags member) are passed back in this structure when
 *   MailGetSvcId completes successfully.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   MailError or MailErrorMsg.
 */
BOOL MailGetSvcId(              // Get a message OID based on szSvcNam/Id
    HANDLE          hMail,              // Current mail context
    MailMsg*        pmm);               // Returns pmm->oid and flags

typedef BOOL (*PMAILGETSVCID)(HANDLE,MailMsg*);

/**
 * This function retrieves the first of a specified type of message from a folder in the message
 * store.
 *
 * @param hMail Handle to the mail context. This handle is created by the MailOpen function.
 * @param pmm Pointer to the MailMsg structure that contains the flags determining which folder the
 *   message is in, what type of message it is, and how much of the message to retrieve. The mail flag
 *   value in the dwFlags member of the structure is a combination of folder, status, and message
 *   flags. The folder flag determines which folder the entry will be retrieved from. One folder flag
 *   can be combined with any number of status flags and message flags. The status flags determine
 *   what type of message to retrieve and the message flags determine how much of the message is
 *   returned. When MailFirst returns, this structure contains the message retrieved from the message
 *   store. Two of the message flags determine how much of the message to retrieve. If MAIL_GET_FLAGS
 *   is set, only the flags and the object identifier are returned. Using this option does not require
 *   any memory to be allocated for the message. If the MAIL_GET_BODY flag is set, the entire message
 *   is loaded into memory. This requires the system to allocate memory from the global heap. If
 *   neither of these flags is set, all of the message except the body is retrieved. Memory for this
 *   option is allocated from the private heap. To free memory allocated by this function, use the
 *   MailFree function.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   MailError or MailErrorMsg.
 *
 * The MailFirst function obtains the information and fills a MailMsg structure variable with the
 * values retrieved from the message store. Changing the values in MailMsg does not affect the
 * message store until it is reinserted by a call to the MailUpdate function.
 */
BOOL    MailFirst(              // Get first mail message
    HANDLE          hMail,              // Current mail context
    MailMsg*        pmm);               // Mail message to return
    
typedef BOOL (*PMAILFIRST)(HANDLE,MailMsg*);

/**
 * After a call to MailFirst, this function retrieves the next of a specified type of mail entry
 * from the message store.
 *
 * @param hMail Handle to the mail context. This handle is created by the MailOpen function.
 * @param pmm Pointer to the MailMsg structure that contains the flags determining which folder the
 *   message is in, what type of message it is, and how much of the message to retrieve. The mail flag
 *   value in the dwFlags member of the structure is a combination of folder, status, and message
 *   flags. The folder flag determines which folder the entry will be retrieved from. One folder flag
 *   can be combined with any number of status flags and message flags. The status flags determine
 *   what type of message to retrieve, and the message flags determine how much of the message is
 *   returned. When MailNext returns, this structure contains the message retrieved from the message
 *   store. Two of the message flags determine how much of the message to retrieve. If MAIL_GET_FLAGS
 *   is set, only the flags and the object identifier are returned. Using this option does not require
 *   any memory to be allocated for the message. If the MAIL_GET_BODY flag is set, the entire message
 *   is loaded into memory. This requires the system to allocate memory from the global heap. If
 *   neither of these flags is set, all of the message except the body is retrieved. Memory for this
 *   option is allocated from the private heap. To free memory allocated by MailNext use the MailFree
 *   function.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   MailError or MailErrorMsg.
 *
 * The flags of the MailMsg structure must be set prior to each call to MailNext because each call
 * to MailFirst, MailGet, or MailNext returns the flags of the message as it is stored in the
 * database.
 *
 * Changing the values of the MailMsg variable does not affect the message store until the message
 * is reinserted by calling the MailUpdate function.
 */
BOOL    MailNext(               // Get next mail message
    HANDLE          hMail,              // Current mail context
    MailMsg*        pmm);               // Mail message to return (in=prev msg)
    
typedef BOOL (*PMAILNEXT)(HANDLE,MailMsg*);

/**
 * This function replaces an entry in the message store with updated information.
 *
 * @param hMail Handle to the mail context. This handle is created by the MailOpen function.
 * @param pmm Pointer to the MailMsg structure that contains the mail entry with the updated
 *   information.
 * @param fDoAll If this Boolean is TRUE, all members of the MailMsg structure are updated. If this
 *   Boolean is set to FALSE, only the flags are changed-that is, the dwFlags member in the MailMsg
 *   structure pointed to by pmm.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   MailError or MailErrorMsg.
 *
 * The entry being updated is based on the oid member of the MailMsg structure. If the entry does
 * not exist in the database, the MailUpdate function fails.
 */
BOOL    MailUpdate(             // Update flags from a previous get
    HANDLE          hMail,              // Current mail context
    MailMsg*        pmm,                // Message with updated flags
    BOOL            fDoAll);            // Update all other fields as well?

typedef BOOL (*PMAILUPDATE)(HANDLE,MailMsg*,BOOL);

/**
 * This function deletes a mail entry from the message store.
 *
 * @param hMail Handle to the mail context. This handle is created by the MailOpen function.
 * @param pmm Pointer to the MailMsg structure that contains the message to be deleted from the
 *   message store. The mail entry deleted is based on the value of the oid member of the structure
 *   when this function is called.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   MailError or MailErrorMsg.
 *
 * If the entry cannot be found in the message store, the MailDelete function will fail.
 */
BOOL    MailDelete(             // Remove a mail message
    HANDLE          hMail,              // Current mail context
    MailMsg*        pmm);               // Mail message to delete
    
typedef BOOL (*PMAILDELETE)(HANDLE,MailMsg*);

/**
 * This function returns storage space back to the system from a previous MailFirst, MailGet, or
 * MailNext function call.
 *
 * @param pmm Pointer to the MailMsg structure being freed.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   MailError or MailErrorMsg.
 *
 * The message flags set (in the dwFlags member of MailMsg) before a call to retrieve a message from
 * the message store determine whether the MailFree function needs to allocate memory.
 */
BOOL    MailFree(               // Give back storage from a prev Get
    MailMsg*        pmm);               // Mail message to free
    
typedef BOOL (*PMAILFREE)(MailMsg*);

/**
 * This function releases the handle to the current mail context.
 *
 * @param hMail Handle to the mail context to be released. This handle is created by the MailOpen
 *   function.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   MailError or MailErrorMsg.
 */
BOOL    MailClose(              // Delete mail context
    HANDLE          hMail);             // Current mail context

typedef BOOL (*PMAILCLOSE)(HANDLE);

// Support routines

/**
 * This function computes the number of characters in a header string.
 *
 * @param pmm Pointer to the mail message that contains the header whose length is returned.
 *
 * @return The length, in characters, of the entire header string indicates success.
 *
 * The MailHeaderLen function searches the header (that is, the pwcHeaders member) of the MailMsg
 * structure in memory. Before calling MailHeaderLen, the message must be retrieved from the message
 * store by calling MailGet, MailFirst, or MailNext.
 *
 * The pwcHeaders member of the MailMsg structure points to the message's header string. The header
 * consists of entries made up of two fields: a name, and an associated value. The name fields are
 * separated from the value fields by a NULL character, and the entries are separated from each
 * other by a NULL character. The header string is terminated with two consecutive NULL characters.
 */
DWORD   MailHeaderLen(          // Compute chars in header string
    MailMsg*        pmm);               // String of headers
    
typedef DWORD (*PMAILHEADERLEN)(MailMsg*);

/**
 * This function computes the total size of local files of attachments to a message.
 *
 * @param hMail Handle to the open mail context, as returned by the MailOpen function.
 * @param pmm Pointer to the mail message to which the attachments belong.
 *
 * @return The total size of local files of attachments to a message indicates success.
 *
 * To get extended error information, call MailError or MailErrorMsg.
 */
DWORD   MailLocalAttachmentLen(          // Compute chars in header string
    HANDLE          hMail,              // Current mail context
    MailMsg*        pmm);               // String of headers
    
typedef DWORD (*PMAILATTACHMENTLEN)(HANDLE,MailMsg*);

/**
 * This function sets a pointer to a specified field in the header string.
 *
 * @param pmm Pointer to the mail message that contains the header being searched.
 * @param szName Null-terminated string that contains the name field that is searched for in the
 *   message header (for example, "To", "From", "Cc", "Subject"). The process of searching the header
 *   for a match with the field name is not case-sensitive. Therefore, this parameter can be any
 *   combination of uppercase and lowercase letters.
 * @param fGetName Boolean that specifies which field of the entry is retrieved. If it set to TRUE,
 *   the return value points to the name field. If it is set to FALSE, the return value points to the
 *   value field-that is, the field that follows the name field.
 *
 * @return A pointer to the specified field, as specified by the fGetName parameter, indicates
 *   success.
 *
 * The MailGetField function searches the header (that is, the pwcHeaders member) of the MailMsg
 * structure in memory. Before calling MailGetField, the message must be retrieved from the message
 * store by calling MailGet, MailFirst, or MailNext.
 *
 * The pwcHeaders member of the MailMsg structure points to the message's header string. The header
 * consists of entries made up of two fields: a name, and an associated value. The name fields are
 * separated from the value fields by a NULL character, and the entries are separated from each
 * other by a NULL character. The header string is terminated with two consecutive NULL characters.
 */
LPWSTR MailGetField(            // Get one header field
    MailMsg*        pmm,                // Message to read from
    LPWSTR          szName,             // Name of field
    BOOL            fGetName);          // Get position of Key instead of val
    
typedef LPWSTR (*PMAILGETFIELD)(MailMsg*,LPWSTR,BOOL);

/**
 * This function is used to add, update, or delete fields from the message header.
 *
 * @param pmm Pointer to the mail message that contains the header entry to be changed.
 * @param szName Null-terminated string that contains the name field of the header entry to be
 *   added, deleted, or changed. When looking for a match, this parameter can be any combination of
 *   uppercase and lowercase letters because the name field is not case-sensitive.
 * @param szVal Null-terminated string that contains the new value for the field. If this parameter
 *   is NULL, the entry is deleted from the header string.
 *
 * @return TRUE indicates success. FALSE indicates failure. The function only fails for
 *   memory-related reasons.
 *
 * The MailSetField function searches the header (that is, the pwcHeaders member) of the MailMsg
 * structure in memory. Before calling MailSetField, the message must be retrieved from the message
 * store by calling MailGet, MailFirst, or MailNext.
 *
 * The pwcHeaders member of the MailMsg structure points to the message's header string. The header
 * consists of entries made up of two fields: a name, and an associated value. The name fields are
 * separated from the value fields by a NULL character, and the entries are separated from each
 * other by a NULL character. The header string is terminated with two consecutive NULL characters.
 *
 * If a matching name field is not found in the message store, the entry is added to the header. If
 * the entry name is found, the value field is changed to the new value passed in. If the value
 * field being passed in is NULL and the entry name exists in the header, the entry is deleted.
 */
BOOL MailSetField(              // Set a field (FALSE=ALLOC error)
    MailMsg*        pmm,                // Message to work with
    LPWSTR          szName,             // Name of field
    LPCWSTR         szVal);             // New value (or NULL to delete)

typedef BOOL (*PMAILSETFIELD)(MailMsg*,LPWSTR,LPCWSTR);

typedef enum {
    MAIL_SORT_FROM,
    MAIL_SORT_SUBJ,
    MAIL_SORT_DATE,
    MAIL_SORT_SIZE
} MAILSORTFIELD;

/**
 * This function sets the order in which mail messages will be retrieved by MailFirst/MailNext calls
 * on the same handle.
 *
 * @param hMail Handle to the open mail context, as returned by the MailOpen function.
 * @param iSort Specifies the field to sort by. See the MAILSORTFIELD.
 * @param fAscending If this Boolean is set to TRUE, the records are sorted in ascending order on
 *   the specified key. If this Boolean is set to FALSE, the records are sorted in descending order.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * To get extended error information, call MailError or MailErrorMsg.
 */
BOOL
MailSetSort(
    HANDLE hMail,                       // Current mail context
    MAILSORTFIELD iSort,                // new sort order
    BOOL fAscending                     // new sort direction; TRUE if ascending
    );

typedef BOOL (*PMAILSETSORT)(HANDLE, MAILSORTFIELD, BOOL);

/**
 * This structure is used to describe the order in which messages are sorted for a particular mail
 * handle.
 */
typedef struct _MAILSORTINFO {
    /**
     * Specifies the member by which the database is sorted for the specified mail handle. See the
     * MAILSORTFIELD enumeration.
     */
    MAILSORTFIELD iSort;                // sort order
    /**
     * Boolean that is set to TRUE if the records are sorted in ascending order on the specified key, or
     * to FALSE if the records are sorted in descending order.
     */
    BOOL fAscending;                    // sort direction
    /**
     * Specifies the number of messages currently in the store.
     */
    int cMsgs;                          // message count
} MAILSORTINFO, *PMAILSORTINFO;

/**
 * This function retrieves the information about the current sort order for the specified mail
 * handle.
 *
 * @param hMail Handle to the open mail context as returned by the MailOpen function.
 * @param pInfo Receives the sort information.
 *
 * @return TRUE indicates success. FALSE indicates that the mail handle is invalid.
 *
 * Before calling the MailGetSort function, call MailFirst to update the number of applicable
 * messages. To get extended error information, call MailError or MailErrorMsg.
 */
BOOL
MailGetSort(
    HANDLE hMail,                       // Current mail context
    PMAILSORTINFO pInfo                 // information structure
    );

typedef BOOL (*PMAILGETSORT)(HANDLE, MAILSORTFIELD *, BOOL *);

BOOL MailSetAttachmentOptions(              // Set a field (FALSE=ALLOC error)
    HANDLE          hMail,
    MailMsg*        pmm,                // Message to work with
    DWORD           dwFlags);
    
typedef BOOL (*PMAILSETATTACHMENTOPTIONS)(HANDLE,MailMsg*,DWORD);

//////////////////////// Emulation/RPC Support routines  ///////////////////////

LONG MailRegOpenKeyExW(         // Open a pegasus registry key
    HKEY    hKey,                       // handle of open key 
    LPCWSTR lpSubKey,                   // address of name of subkey to open 
    DWORD   ulOptions,                  // reserved 
    REGSAM  samDesired,                 // security access mask 
    PHKEY   phkResult);                 // address of handle of open key 
    
typedef LONG (*PMAILREGOPENKEYEXW)(HKEY,LPCWSTR,DWORD,REGSAM,PHKEY);

LONG MailRegEnumKeyExW(         // Retrieve one key
    HKEY    hKey,                       // handle of key to enumerate 
    DWORD   dwIndex,                    // index of subkey to enumerate 
    LPWSTR  lpName,                     // address of buffer for subkey name 
    LPDWORD lpcbName,                   // address for size of subkey buffer 
    LPDWORD lpReserved,                 // reserved 
    LPWSTR  lpClass,                    // address of buffer for class string 
    LPDWORD lpcbClass,                  // address for size of class buffer 
    PFILETIME lpftLastWriteTime);       // address for time key last written to 
    
typedef LONG (*PMAILREGENUMKEYEXW)(HKEY,DWORD,LPWSTR,LPDWORD,LPDWORD,LPWSTR,LPDWORD,PFILETIME);

LONG MailRegCloseKey(           // Close a key
    HKEY    hKey);                      // handle of key to close
    
typedef LONG (*PMAILREGCLOSEKEY)(HKEY);

#ifdef __cplusplus
};
#endif

//
// TransportEx flags.
//
#define TVEX_DISABLE_PREV    0x00000001
#define TVEX_DISABLE_NEXT    0x00000002

//
// TransportViewEx return codes.
//
#define TVEX_VIEW_CURRENT  0   // read current message
#define TVEX_VIEW_DONE     1   // no further processing
#define TVEX_VIEW_PREV     2   // display previous message
#define TVEX_VIEW_NEXT     3   // display next message
#define TVEX_VIEW_REPLY    4   // reply to current message
#define TVEX_VIEW_REPLYALL 5   // reply-all to current message
#define TVEX_VIEW_FORWARD  6   // forward current message
#define TVEX_VIEW_DELETE   7   // delete current message

#endif // !__MSGSTORE_RC__

/*-----------------------------------------------------------------------*/
/* Resources.                                                            */
/*-----------------------------------------------------------------------*/

#define MAIL_ERR_NONE           0
#define MAIL_ERR_BADPARAM       1
#define MAIL_ERR_BADHANDLE      2
#define MAIL_ERR_CANTALLOC      3
    
#define MAIL_ERR_NOSUCHDB       4
#define MAIL_ERR_CANTCREDB      5
#define MAIL_ERR_BADVER         6
#define MAIL_ERR_REOPEN         7

#define MAIL_ERR_NOHEADER       8
#define MAIL_ERR_BADHEADER      9
#define MAIL_ERR_WRITEHEADER    10
    
#define MAIL_ERR_WRITEFOLDER    11
#define MAIL_ERR_NOSUCHFOLDER   12
#define MAIL_ERR_BADFOLDER      13
    
#define MAIL_ERR_WRITEMSG       14
#define MAIL_ERR_WRITEBODY      15
#define MAIL_ERR_NOMATCH        16
#define MAIL_ERR_BADMSGID       17
#define MAIL_ERR_BADMSGREC      18
#define MAIL_ERR_BADMSGBODY     19
#define MAIL_ERR_BADOID         20
#define MAIL_ERR_UPDATEMSG      21
#define MAIL_ERR_CANTDEL        22
#define MAIL_ERR_BADHEADREC     23
#define MAIL_ERR_BADMSGHEAD     24
#define MAIL_ERR_BADPIECE       25
#define MAIL_ERR_NOHEAP         26
#define MAIL_ERR_CANTDELATT     27
#define MAIL_ERR_FOLDEREXISTS   28
#define MAIL_ERR_BADFOLDERNAME  29

#define MAIL_IDS_DBNAME         100
#define MAIL_IDS_BADPARAM       101
#define MAIL_IDS_UNKNOWN        102
#define MAIL_IDS_INBOX          103
#define MAIL_IDS_OUTBOX         104
#define MAIL_IDS_SENT           105
#define MAIL_IDS_DBNAME2        106
#define MAIL_IDS_ATT_DIRECTORY  107
#define MAIL_IDS_DELETED        108

#define MAIL_IDS_FROM           200
#define MAIL_IDS_SUBJ           201
#define MAIL_IDS_TYPE           202

#define MAIL_IDS_RE             210
#define MAIL_IDS_FW             211

#endif // MSGSTORE_H
