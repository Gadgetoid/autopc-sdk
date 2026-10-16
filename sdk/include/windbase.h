/**

 Copyright (c) 1995, Microsoft Corporation

 Module: windbase.h

 Purpose: Master include file for WINCE Database APIs

**/

#ifndef __WINDBASE__
#define __WINDBASE__

// @CESYSGEN IF CE_MODULES_FILESYS

typedef DWORD CEOID;
typedef CEOID *PCEOID;

// @CESYSGEN IF FILESYS_FSMAIN

/**
 * This structure contains information about a file object.
 */
typedef struct _CEFILEINFO {
    /**
     * Specifies the attributes of the file.
     */
    DWORD   dwAttributes;
    /**
     * Object identifier of the parent directory.
     */
    CEOID     oidParent;
    /**
     * Null-terminated string that contains the name and path of the file.
     */
    WCHAR szFileName[MAX_PATH];
    /**
     * Time stamp that indicates when the contents of the file were last changed.
     */
    FILETIME ftLastChanged;
    /**
     * Specifies the length, in bytes, of the file.
     */
    DWORD   dwLength;
} CEFILEINFO;

/**
 * This structure contains information about a directory object.
 */
typedef struct _CEDIRINFO {
    /**
     * Specifies the attributes of the directory.
     */
    DWORD   dwAttributes;
    /**
     * Object identifier of the parent directory.
     */
    CEOID  oidParent;
    /**
     * Null-terminated string that contains the name and path of the directory.
     */
    WCHAR   szDirName[MAX_PATH];
} CEDIRINFO;

/**
 * This message is sent when a new object is created in the object store.
 *
 * @param oidCreated Identifier of the newly created object.
 * @param oidParent Identifier of the parent object of the newly created object.
 *
 * When writing applications for Windows CE version 1.0, use the DB_PEGOID_CREATED message.
 */
#define DB_CEOID_CREATED	(WM_USER + 0x1)
#define DB_CEOID_DATABASE_DELETED	(WM_USER + 0x2)
/**
 * This message is sent when a record has been deleted from the object store.
 *
 * @param oidDeletedRec Identifier of the record that was deleted.
 * @param oidParent Identifier of the parent object of the deleted record.
 */
#define DB_CEOID_RECORD_DELETED	(WM_USER + 0x3)
#define DB_CEOID_FILE_DELETED	(WM_USER + 0x4)
#define DB_CEOID_DIRECTORY_DELETED	(WM_USER + 0x5)
/**
 * This message is sent when an object in the object store has been modified.
 *
 * @param oidChanged Identifier of the object that was modified.
 * @param oidParent Identifier of the parent object of the modified object.
 *
 * When writing applications for Windows CE version 1.0, use the DB_PEGOID_CHANGED message.
 */
#define DB_CEOID_CHANGED	(WM_USER + 0x6)

// flags for CeGetReplChangeMask
#define REPL_CHANGE_WILLCLEAR	0x00000001

/**
 * This structure contains the size of the object store and the amount of free space currently in
 * the object store.
 */
typedef struct STORE_INFORMATION {
	/**
	 * Specifies the size, in bytes, of the object store.
	 */
	DWORD dwStoreSize;
	DWORD dwFreeSize;
} STORE_INFORMATION, *LPSTORE_INFORMATION;

/**
 * This function fills in a STORE_INFORMATION structure with the size of the object store and the
 * amount of free space currently in the object store.
 *
 * @param lpsi [out] Pointer to the STORE_INFORMATION structure to be filled in by this function.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   the GetLastError function.
 *
 * The system reserves that last 24K for high priority system operations. This function always
 * reports 24K storage memory less then what is really available.
 */
BOOL GetStoreInformation (LPSTORE_INFORMATION lpsi);

// @CESYSGEN ENDIF


// @CESYSGEN IF FILESYS_FSDBASE

typedef DWORD CEPROPID;
typedef CEPROPID *PCEPROPID;
/**
 * This macro retrieves the type identifier from a property identifier.
 *
 * @param propid Property identifier from which to retrieve the type identifier.
 *
 * The TypeFromPropID macro is defined as follows:
 *
 *     #define TypeFromPropID(propid) LOWORD(propid)
 */
#define TypeFromPropID(propid) LOWORD(propid)

/**
 * This structure contains information about a record object.
 */
typedef struct _CERECORDINFO {
    /**
     * Object identifier of the parent database.
     */
    CEOID  oidParent;
} CERECORDINFO;

#define CEDB_SORT_DESCENDING         0x00000001
#define CEDB_SORT_CASEINSENSITIVE    0x00000002
#define CEDB_SORT_UNKNOWNFIRST       0x00000004
#define CEDB_SORT_GENERICORDER       0x00000008  // internally used for generic ordering
/**
 * This structure contains information about a sort order in a database.
 *
 * The system supports only simple sorts on a primary key. Records with the same key value are be
 * sorted in arbitrary order.
 */
typedef struct _SORTORDERSPEC {
    /**
     * Identifier of the property to be sorted on. Sorts on binary properties are not allowed.
     */
    CEPROPID  propid;
    /**
     * Specifies the sort flags. It is one or a combination of the following flags:
     *
     * - CEDB_SORT_DESCENDING: The sort is done in descending order. By default, the sort is done in
     * ascending order.
     *
     * - CEDB_SORT_CASEINSENSITIVE: The sort operation is case insensitive. This value is valid only for
     * strings.
     *
     * - CEDB_SORT_UNKNOWNFIRST: Records that do not contain this property are placed before all the
     * other records. By default, such records are placed after all other records.
     *
     * - CEDB_SORT_GENERICORDER: The default sort order-ascending order, case sensitive-is used. Records
     * that do not contain the sort property are placed at the end of the list.
     */
    DWORD   dwFlags;
} SORTORDERSPEC;

#define CEDB_MAXDBASENAMELEN 32
#define CEDB_MAXSORTORDER   4

// values for flag
#define CEDB_VALIDNAME     0x0001
#define CEDB_VALIDTYPE     0x0002
#define CEDB_VALIDSORTSPEC 0x0004
#define CEDB_VALIDMODTIME	0x0008

/**
 * This structure contains information about a database object. This structure is used by the
 * CeSetDatabaseInfo and CeCreateDatabaseEx functions.
 *
 * For Windows CE versions 2.10 and later, dwFlags has additional meaning, but is still compatible
 * with previous versions. The high-order word of dwFlags specifies additional database properties.
 */
typedef struct _CEDBASEINFO {
    /**
     * The low-order word specifies the valid members of this structure. This member is one or a
     * combination of the following flags: Value Description CEDB_VALIDMODTIME The ftLastModified member
     * is valid and should be used. CEDB_VALIDNAME The szDbaseName member is valid and should be used.
     * CEDB_VALIDTYPE The dwDbaseType member is valid and should be used. CEDB_VALIDSORTSPEC The
     * rgSortSpecs member is valid and should be used. CEDB_VALIDDBFLAGS The low-order word of the
     * dwFlags member is valid and should be used.
     *
     * The high-order word specifies the associated database properties. This member is the following
     * flag: Value Description CEDB_NOCOMPRESS The database is not compressed. If this flag is used with
     * CeSetDatabaseInfoEx, a compressed database is uncompressed. If this flag is used with
     * CeCreateDatabaseEx, the database is not compressed. To compress a database, CeSetDatabaseInfoEx
     * or CeCreateDatabaseEx is called with CEDB_VALIDDBFLAGS set and the CEDB_NOCOMPRESS bit cleared.
     * By default, all databases are compressed. If you are going to change the compression, it should
     * be done at creation time.
     */
    DWORD   dwFlags;
    /**
     * Null-terminated string that contains the name of the database. The string can have up to 32
     * characters, including the terminating null character. This member must be set when used for
     * CeCreateDatabaseEx.
     */
    WCHAR   szDbaseName[CEDB_MAXDBASENAMELEN];
    /**
     * Specifies the type identifier for the database.
     */
    DWORD   dwDbaseType;
    /**
     * Returns the number of records in the database.
     */
    WORD    wNumRecords;
    /**
     * Number of sort orders active in the database. Up to four sort orders can be active at a time.
     */
    WORD    wNumSortOrder;
    /**
     * Specifies, in bytes, the size of the database.
     */
    DWORD	dwSize;
    /**
     * Returns the last time this database was modified.
     */
    FILETIME ftLastModified;
    /**
     * Array containing the sort order descriptions. Only the first n array members are valid, where n
     * is the value specified by the wNumSortOrder member. If no sort orders are specified for
     * CeCreateDatabaseEx or when CEDB_VALIDSORTSPEC is not specified, then a default sort order is
     * assigned to the database.
     */
    SORTORDERSPEC rgSortSpecs[CEDB_MAXSORTORDER];
} CEDBASEINFO;


// flags for open database - use low word
#define CEDB_AUTOINCREMENT     0x00000001

#define CEDB_SEEK_CEOID       0x00000001
#define CEDB_SEEK_BEGINNING    0x00000002
#define CEDB_SEEK_END          0x00000004
#define CEDB_SEEK_CURRENT      0x00000008
#define CEDB_SEEK_VALUESMALLER     0x00000010
#define CEDB_SEEK_VALUEFIRSTEQUAL  0x00000020
#define CEDB_SEEK_VALUEGREATER     0x00000040
#define CEDB_SEEK_VALUENEXTEQUAL   0x00000080


/**
 * This structure contains information about a Binary Large Object (BLOB)s of data in the object
 * store.
 */
typedef struct _CEBLOB {
    /**
     * Specifies the size, in bytes, of the BLOB.
     */
    DWORD           dwCount;
    /**
     * Pointer to the beginning of the BLOB.
     */
    LPBYTE          lpb;
} CEBLOB;

#define CEVT_I2       2
#define CEVT_UI2      18
#define CEVT_I4       3
#define CEVT_UI4      19
#define CEVT_FILETIME 64
#define CEVT_LPWSTR   31
#define CEVT_BLOB     65

/**
 * This union contains a value for a property.
 */
typedef union _CEVALUNION {
    /**
     * Specifies an integer.
     */
    short           iVal;
    /**
     * Specifies an unsigned integer.
     */
    USHORT          uiVal;
    /**
     * Specifies a long integer.
     */
    long            lVal;
    /**
     * Specifies an unsigned long integer.
     */
    ULONG           ulVal;
    /**
     * Specifies a FILETIME structure.
     */
    FILETIME        filetime;
    /**
     * Pointer to a null-terminated string.
     */
    LPWSTR          lpwstr;
    /**
     * Specifies a CEBLOB structure.
     */
    CEBLOB         blob;
} CEVALUNION;
 
// dont define flags in low byte
#define CEDB_PROPNOTFOUND 0x0100
#define CEDB_PROPDELETE   0x0200
/**
 * This structure contains a property value.
 */
typedef struct _CEPROPVAL {
    /**
     * Identifier of the property value. The high-order word is an application-defined identifier, and
     * the low-order word is a predefined constant value that indicates the data type of the value
     * specified by the val member. The low-order word can be one of the following values: Value
     * Description CEVT_BLOB A CEBLOB structure. CEVT_BOOL A Boolean value. CEVT_FILETIME A FILETIME
     * structure. CEVT_I2 A 16-bit signed integer. CEVT_I4 A 32-bit signed integer. CEVT_LPWSTR A
     * null-terminated string. CEVT_R8 A 64-bit signed interger. CEVT_UI2 A 16-bit unsigned integer.
     * CEVT_UI4 A 32-bit unsigned integer.
     */
    CEPROPID   propid;
    /**
     * Not used.
     */
    WORD        wLenData;
    /**
     * Special flags for the property. It is one of the following values: Value Description
     * CEDB_PROPNOTFOUND Set by the CeReadRecordProps function if the property was not found.
     * CEDB_PROPDELETE If passed to the CeWriteRecordProps function, this flag causes the property to be
     * deleted.
     */
    WORD        wFlags;
    /**
     * Actual value for simple types, or a pointer for strings or Binary Large Objects (BLOBs).
     */
    CEVALUNION val;
} CEPROPVAL;
typedef CEPROPVAL *PCEPROPVAL;

// Max record length defines
// zero is a valid length so we cant have full 4196
#define CEDB_MAXDATABLOCKSIZE 4092
#define CEDB_MAXPROPDATASIZE  ((CEDB_MAXDATABLOCKSIZE*16)-1)
// max record size is bound only by the max logging space we want to consume
// this is not explicitly checked for - if you read too much data and cause the log
// page to overflow the call will fail.
#define CEDB_MAXRECORDSIZE  (128*1024)

// flags for ReadRecord
#define CEDB_ALLOWREALLOC  0x00000001

/**
 * This function opens an enumeration context that enables an application to enumerate all databases
 * in the object store. This function is obsolete. Applications should call CeFindFirstDatabaseEx
 * instead.
 *
 * @param dwDbaseType [in] Specifies the type identifier of the databases to enumerate. If this
 *   parameter is zero, all databases are enumerated.
 *
 * @return A handle to an enumeration context indicates success. INVALID_HANDLE_VALUE indicates
 *   failure. To get extended error information within a Windows CE program, call GetLastError.
 *   GetLastError may return ERROR_OUTOFMEMORY if no memory is available to allocate a database
 *   handle.
 *
 * This function returns only the handle to a enumeration context. To begin enumerating databases,
 * an application must call the CeFindNextDatabaseEx function. When an application is done with the
 * handle to the enumeration context, an application uses CloseHandle to release the resources
 * associated with the enumeration context.
 */
HANDLE CeFindFirstDatabase (DWORD dwClassID);
/**
 * This function retrieves the next database in an enumeration context. This function is obsolete.
 * Applications should call CeFindNextDatabaseEx instead.
 *
 * @param hEnum [in] Handle to an enumeration context; this handle is returned from
 *   CeFindFirstDatabase.
 *
 * @return The object identifier of the next database to be enumerated indicates success. Zero
 *   indicates that there are no more databases are left to enumerate, or that an error occurred. To
 *   get extended error information within a Windows CE program, call GetLastError. Possible values
 *   for GetLastError include the following: - ERROR_NO_MORE_ITEMS: The object store contains no more
 *   databases to enumerate. - ERROR_INVALID_PARAMETER: The hEnum parameter specified an invalid
 *   handle.
 *
 * To find all matching databases, CeFindNextDatabase is called in a loop until 0 is returned. If a
 * database is deleted during an enumeration, CeFindNextDatabase fails and returns
 * ERROR_KEY_DELETED. If this error occurs, you must restart the enumeration with a call to
 * CeFindFirstDatabase.
 */
CEOID CeFindNextDatabase (HANDLE hEnum);
/**
 * This function creates a new database. This functions is obsolete. Applications instead should
 * call CeCreateDatabaseEx.
 *
 * @param lpszName [in] Long pointer to a null-terminated string that specifies the name for the new
 *   database. The name can have up to 32 characters, including the terminating null character. If the
 *   name is too long, it is truncated and the database is created.
 * @param dwDbaseType [in] Specifies the type identifier for the database. This is an
 *   application-defined value that can be used for any application-defined purpose. For example, an
 *   application can use the type identifier to distinguish address book data from to-do list data or
 *   use the identifier during a database enumeration sequence. See CeFindFirstDatabase for details.
 *   The type identifier is not meant to be a unique identifier for the database. The system does not
 *   use this value.
 * @param wNumSortOrder [in] Number of sort orders active in the database, with four being the
 *   maximum number. This parameter can be zero if no sort orders are active. If this value is zero,
 *   then the database engine creates a default sort order where "rgSortSpecs[0].propid = 0", and
 *   "rgSortSpecs[0].dwFlags = CEDB_SORT_GENERICORDER." This is only a placeholder and does not
 *   influence the insertion order of the records.
 * @param rgSortSpecs [in] Pointer to an array of actual sort order descriptions. The size of the
 *   array is specified by wNumSortOrder. This parameter can be NULL if wNumSortOrder is zero.
 *
 * @return The object identifier of the newly created database-not a handle to an open
 *   database-indicates success. NULL indicates failure. To get extended error information within a
 *   Windows CE program, call GetLastError. Possible values for GetLastError include the following: -
 *   ERROR_DISK_FULL: The object store does not contain enough space to create the new database. -
 *   ERROR_INVALID_PARAMETER: A parameter was invalid. - ERROR_DUP_NAME: A database already exists
 *   with the specified name.
 *
 * Because sort orders increase the system resources needed to perform each insert and delete
 * operation, keep the number of sort orders to a minimum. However, try not to specify too few sort
 * orders. If you do, you can use the CeSetDatabaseInfoEx function to change the sort order later;
 * however, this function is even more expensive in terms of system resources.
 */
CEOID CeCreateDatabase (LPWSTR lpszname, DWORD dwClassID, WORD wNumSortOrder, SORTORDERSPEC *rgSortSpecs);
/**
 * This function sets various database parameters, including the name, type, and sort-order
 * descriptions. This function is obsolete. Applications should call CeSetDataBaseInfoEx instead.
 *
 * @param oidDbase [in] Object identifier of the database for which parameters are to be set.
 * @param pNewInfo [in] Pointer to a CEDBASEINFO structure that contains new parameter information
 *   for the database. The wNumRecords member of the structure is not used.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information within
 *   a Windows CE program, call GetLastError. Possible values for GetLastError include the following:
 *   - ERROR_INVALID_PARAMETER: A parameter was invalid. - ERROR_DISK_FULL: The object store is full
 *   and any size changes required could not be accommodated. Changing sort orders can change the size
 *   of the stored records, though not by much. - ERROR_SHARING_VIOLATION: CeSetDatabaseInfo tried to
 *   remove a sort order that is being used by a currently open database.
 *
 * The CeSetDatabaseInfo function can be used to change the database parameters passed in while
 * creating the database. Note that changing the sort order of the database can take several
 * minutes. Before calling CeSetDatabaseInfo, an application should warn the user that this
 * operation can be lengthy.
 */
BOOL CeSetDatabaseInfo (CEOID oidDbase, CEDBASEINFO *pNewInfo);
/**
 * This function opens an existing database. This function is obsolete. Applications should call
 * CeOpenDatabaseEx instead.
 *
 * @param poid [in] Pointer to the object identifier of the database to be opened. To open a
 *   database by name, set the value pointed to by poid to zero to receive the object identifer of the
 *   newly opened database when a database name is specified for lpszName.
 * @param lpszName [in] Pointer to the null-terminated string that contains the name of the database
 *   to be opened. This parameter is ignored if the value pointed to by poid is nonzero.
 * @param propid [in] Property identifier of the primary key for the sort order in which the
 *   database is to be traversed. All subsequent calls to CeSeekDatabase assume this sort order. This
 *   parameter can be zero if the sort order is not important.
 * @param dwFlags [in] Specifies a bitmask of action flags. It is one of the following values: Value
 *   Description CEDB_AUTOINCREMENT Causes the current seek position to be automatically incremented
 *   with each call to the CeReadRecordProps function. 0 (ZERO) Current seek position is not
 *   incremented with each call to CeReadRecordProps.
 * @param hwndNotify [in] Handle to the window to which notification messages (DB_CEOID_*) will be
 *   posted if another thread modifies the specified database while you have it open. This parameter
 *   can be NULL if you do not need to receive notifications.
 *
 * @return The handle to the open database indicates success. INVALID_HANDLE_VALUE indicates
 *   failure. To get extended error information within a Windows CE program, call GetLastError.
 *   Possible values for GetLastError include the following: - ERROR_INVALID_PARAMETER: A parameter
 *   was invalid. - ERROR_FILE_NOT_FOUND: No database exists with the specified name. This value
 *   applies only if the value pointed to by poid was set to NULL when the function was called. -
 *   ERROR_NOT_ENOUGH_MEMORY: No memory was available to allocate a database handle.
 *
 * Use the CloseHandle function to close the handle returned by the CeOpenDatabase function.
 *
 * Unlike many other traditional databases, opening and closing a database does not imply any
 * transactioning. In other words, the database is not committed at the closing-it is committed
 * after each individual call.
 *
 * An application that opens the same database more then once and requests to be notified about
 * changes to the database will receive change notification for changes that its process has made on
 * the database. The reason is that change notification process is not done on a process level, but
 * on a per open database level.
 */
HANDLE CeOpenDatabase (PCEOID poid, LPWSTR lpszName, CEPROPID propid, DWORD dwFlags, HWND hwndNotify);
/**
 * This function removes a database from the object store. This function is obsolete. Applications
 * should call CeDeleteDatabaseEx instead.
 *
 * @param oidDbase [in] Object identifier of the database to be deleted.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information within
 *   a Windows CE-based program, call GetLastError. Possible values for GetLastError include the
 *   following: - ERROR_INVALID_PARAMETER: A parameter was invalid. - ERROR_SHARING_VIOLATION: Another
 *   thread has an open handle to the database.
 *
 * The CeDeleteDatabase function deletes a database, including all records in the database.
 */
BOOL CeDeleteDatabase (CEOID oid);
/**
 * This function seeks the specified record in an open database. A remote application interface
 * (RAPI) version of this function exists, and it is also called CeSeekDatabase.
 *
 * @param hDatabase [in] Handle to the open database in which to seek.
 * @param dwSeekType [in] Specifies the type of seek operation to perform. It is one of the
 *   following values: Value Description CEDB_SEEK_CEOID Seek until finding an object that has the
 *   specified object identifier. The dwValue parameter specifies the object identifier. This type of
 *   seek operation is very efficient. CEDB_SEEK_VALUESMALLER Seek until finding the largest value
 *   that is smaller than the specified value. If none of the records has a smaller value, the seek
 *   pointer is left at the end of the database and the function returns zero. The dwValue parameter
 *   is a pointer to a CEPROPVAL structure. CEDB_SEEK_VALUEFIRSTEQUAL Seek until finding the first
 *   value that is equal to the specified value. If the seek operation fails, the seek pointer is left
 *   pointing at the end of the database, and the function returns zero. The dwValue parameter is a
 *   pointer to a CEPROPVAL structure. CEDB_SEEK_VALUENEXTEQUAL Starting from the current seek
 *   position, seek exactly one position forward in the sorted order and check if the next record is
 *   equal in value to the specified value. If so, return the object identifier of this next record;
 *   otherwise, return zero and leave the seek pointer at the end of the database. This operation can
 *   be used in conjunction with the CEDB_SEEK_VALUEFIRSTEQUAL operation to enumerate all records with
 *   an equal value. The dwValue parameter specifies the value for which to seek.
 *   CEDB_SEEK_VALUEGREATER Seek until finding a value greater than or equal to the specified value.
 *   If all records are smaller, the seek pointer is left at the end of the database and the function
 *   returns zero. The dwValue parameter is a pointer to a CEPROPVAL structure. CEDB_SEEK_BEGINNING
 *   Seek until finding the record at the specified position from the beginning of the database. The
 *   dwValue parameter specifies the number of records to seek. CEDB_SEEK_CURRENT Seek backward or
 *   forward from the current position of the seek pointer for the specified number of records. The
 *   dwValue parameter specifies the number of records from the current position. The function seeks
 *   forward if dwValue is a positive value, or backward if it is negative. A forward seek operation
 *   is efficient. CEDB_SEEK_END Seek backward for the specified number of records from the end of the
 *   database. The dwValue parameter specifies the number of records.
 * @param dwValue [in] Specifies the value to use for the seek operation. The meaning of this
 *   parameter depends on the value of dwSeekType.
 * @param lpdwIndex [out] Pointer to a variable that receives the index from the start of the
 *   database to the beginning of the record that was found.
 *
 * @return The object identifier of the record on which the seek ends indicates success. Zero
 *   indicates failure. To get extended error information within a CE program, call GetLastError.
 *   GetLastError may return ERROR_INVALID_PARAMETER if a parameter is invalid.
 *
 * The CeSeekDatabase function always uses the current sort order as specified in the call to the
 * CeOpenDatabaseEx function. If the CEDB_AUTOINCREMENT flag was specified, an automatic seek of one
 * from the current position is done with each read operation that occurs on the database. If a
 * seeks fails then the record pointer points to the same record as before the seek operation.
 *
 * Note that a seek can only be performed on a sorted property value. After creating a database
 * (using CeCreateDatabaseEx) and opening the database (using CeOpenDatabaseEx), subsequent calls to
 * CeSeekDatabase assume the sort order that was specified in the propid parameter of the call to
 * CeOpenDatabaseEx.
 *
 * To enter negative values for the CEDB_SEEK_CURRENT case, cast a signed long. This changes the
 * effective range on the record indexes to 31 bits from 32.
 *
 * Multiple sort orders cannot be specified for a single property.
 *
 * When a CEPROPVAL structure is required to seek operation, the propid parameter must be set to the
 * PROPID of the sort order specified in the CeOpenDatabaseEx call.
 */
CEOID CeSeekDatabase (HANDLE hDatabase, DWORD dwSeekType, DWORD dwValue, LPDWORD lpdwIndex);
/**
 * This function deletes a record from a database. A remote application interface (RAPI) version of
 * this function exists, and it is also named CeDeleteRecord.
 *
 * @param hDatabase [in] Handle to the database from which the record is to be deleted. The database
 *   must be open. Open a database by calling the CeOpenDatabase function.
 * @param oidRecord [in] Object identifier of the record to be deleted; this is obtained from
 *   CeOpenDatabase.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information within
 *   a Windows CE program, call GetLastError. GetLastError and may return ERROR_INVALID_PARAMETER if
 *   the handle or object identifier is invalid.
 *
 * If the CEDB_AUTOINCREMENT flag was not specified when the database was opened, and the record
 * being deleted is the current record, the next read operation that uses the database handle will
 * fail. If the CEDB_AUTOINCREMENT flag was specified, the system automatically moves the current
 * seek pointer forward by one.
 */
BOOL CeDeleteRecord (HANDLE hDatabase, CEOID oidRecord);
/**
 * This function reads properties from the current record. This function is obsolete. Applications
 * should call CeReadRecordsPropsEx instead.
 *
 * @param hDbase [in] Handle to an open database. The database must have been opened by a previous
 *   call to the CeOpenDatabase function.
 * @param dwFlags [in] Specifies a bitmask of read flags. It is the following value: Value
 *   Description CEDB_ALLOWREALLOC The LocalAlloc function was used to allocate the buffer specified
 *   by the lplpBuffer parameter, and the server can reallocate the buffer if it is not large enough
 *   to hold the requested properties.
 * @param lpcPropID [in] Pointer to the number of property identifiers in the array specified by the
 *   rgPropID parameter. If rgPropID is NULL, this parameter receives the number of properties
 *   retrieved.
 * @param rgPropID [in] Pointer to an array of property identifiers for the properties to be
 *   retrieved. If this parameter is NULL, CeReadRecordProps retrieves all properties in the record.
 * @param lplpBuffer [out] Pointer to a long pointer to a buffer that receives the requested
 *   properties. If the dwFlags parameter includes the CEDB_ALLOWREALLOC flag, the buffer may be
 *   reallocated if necessary. If the CEDB_ALLOWREALLOC flag is specified and this parameter is NULL,
 *   the server uses the LocalAlloc function to allocate a buffer of the appropriate size in the
 *   caller's address space and returns a pointer to the buffer. Note that if the CEDB_ALLOWREALLOC
 *   flag is specified, it is possible for the value of this pointer to change even on failure. For
 *   example, the old memory might be freed and the allocation might then fail, leaving the pointer
 *   set to NULL.
 * @param lpcbBuffer [out] Pointer to a variable that contains the size, in bytes, of the buffer
 *   specified by the lplpBuffer parameter. When CeReadRecordProps returns, lpcbBuffer receives a
 *   value that indicates the actual size of the data copied to the buffer. If the buffer was too
 *   small to contain the data, this parameter can be used to calculate the amount of memory to
 *   allocate for the buffer if CEDB_ALLOWREALLOC was not specified.
 *
 * @return The object identifier of the record from which the function read indicates success. Zero
 *   indicates failure. To get extended error information within a Windows CE program, call
 *   GetLastError. Possible values for GetLastError include the following: - ERROR_INVALID_PARAMETER:
 *   A parameter was invalid. - ERROR_NO_DATA: None of the requested properties was found. The output
 *   buffer and the size are valid. - ERROR_INSUFFICIENT_BUFFER: The specified buffer was not large
 *   enough, and the reallocation failed-if the CEDB_ALLOWREALLOC flag was specified. The lpcbBuffer
 *   parameter contains the required buffer size. - ERROR_KEY_DELETED: The record that was about to be
 *   read was deleted by another thread. If the current record was reached as a result of an autoseek,
 *   this error is not returned, and the next record is returned. - ERROR_NO_MORE_ITEMS: The current
 *   seek pointer is at the end of the database.
 *
 * The CeReadRecordProps function reads the specified set of properties from the current record. If
 * the database was opened with the autoseek flag-that is, if the dwFlags parameter of
 * CeOpenDatabase was set to CEDB_AUTOINCREMENT-CeReadRecordProps increments the seek pointer by one
 * so that the next call reads the next record in the current sort order. That is, if the database
 * was opened with a sort order active, then CeReadRecordProps will return the records in sorted
 * order. If the database was not opened with a sort order active, then the order in which records
 * are returned is not predictable.
 *
 * Read all needed properties from the record in a single call. The entire record is stored in a
 * compressed format, and each time a property is read it must be decompressed. All the properties
 * are returned in a single marshalled structure, which consists of an array of CEPROPVAL
 * structures, one for each property requested-or one for each property found if the application set
 * the rgPropID parameter to NULL when calling the function.
 *
 * If a property was requested, such as strings or blobs that are packed in at the end of the array,
 * the pointers in the CEPROPVAL structures point into this marshalled structure. This means that
 * the only memory that must be freed is the original pointer to the buffer passed in to the call.
 * Even if the function fails, it may have allocated memory on the caller's behalf. Free the pointer
 * returned by this function if the pointer is not NULL.
 */
CEOID CeReadRecordProps (HANDLE hDbase, DWORD dwFlags, LPWORD lpcPropID, CEPROPID *rgPropID, LPBYTE *lplpBuffer, LPDWORD lpcbBuffer);
/**
 * This function writes a set of properties to a single record, creating the record if necessary. A
 * remote application interface (RAPI) version of this function exists, and it is also called
 * CeWriteRecordProps.
 *
 * @param hDbase [in] Handle to an open database. The database must have been opened by a previous
 *   call to the CeOpenDatabase function.
 * @param oidRecord [in] Object identifier of the record to which the specified properties are to be
 *   written. If this parameter is zero, a new record is created and filled in with the specified
 *   properties.
 * @param cPropID [in] Number of properties in the array specified by the rgPropVal parameter. The
 *   cPropID parameter must not be zero.
 * @param rgPropVal [in] Pointer to an array of CEPROPVAL structures that specify the property
 *   values to be written to the specified record.
 *
 * @return The object identifier of the record to which the properties were written indicates
 *   success. Zero indicates failure. To get extended error information when within a CE program call
 *   GetLastError. GetLastError may return one of the following values: Value Description
 *   ERROR_DISK_FULL There was not enough space in the object store to write the properties.
 *   ERROR_INVALID_PARAMETER A parameter was invalid.
 *
 * The CeWriteRecordProps function writes all the requested properties into the specified record.
 * CeWriteRecordProps does not move the seek pointer.
 *
 * To delete a property, set the CEDB_PROPDELETE flag in the appropriate property value. This allows
 * multiple deletes and changes in a single call, which is much more efficient than multiple calls.
 *
 * No memory is freed by the callee. Pointers in the CEPROPVAL structures can be anywhere in the
 * caller's address space-they can be marshalled in like the array returned by CeReadRecordProps, or
 * they can be independently allocated.
 *
 * For Windows CE versions 2.10 and later, on a mounted database volume, all write operations are
 * cached. The database subsystem periodically requests a cache flush after a series of operations.
 * If memory is low, the cache is flushed to permanent storage. Unlike a file system that can choose
 * to flush only part of the cache, on a database, all blocks are flushed.
 */
CEOID CeWriteRecordProps (HANDLE hDbase, CEOID oidRecord, WORD cPropID, CEPROPVAL *rgPropVal);

// @CESYSGEN ENDIF


// @CESYSGEN IF FILESYS_FSMAIN

#define OBJTYPE_INVALID     0
#define OBJTYPE_FILE        1
#define OBJTYPE_DIRECTORY   2
#define OBJTYPE_DATABASE    3
#define OBJTYPE_RECORD      4

/**
 * This structure contains information about an object in the object store or database volume.
 */
typedef struct _CEOIDINFO {
    /**
     * Specifies the type of the object. It is one of the following values: Value Description
     * OBJTYPE_INVALID The object store contains no valid object that has this object identifier.
     * OBJTYPE_FILE The object is a file. OBJTYPE_DIRECTORY The object is a directory. OBJTYPE_DATABASE
     * The object is a database. OBJTYPE_RECORD The object is a record inside a database.
     */
    WORD  wObjType;             //Type of object
            //        OBJTYPE_INVALID   | There was no valid object with this CEOID
            //        OBJTYPE_FILE      | The object is a file
            //        OBJTYPE_DIRECTORY | The object is a directory
            //        OBJTYPE_DATABASE  | The object is a database
            //        OBJTYPE_RECORD    | The object is a record inside a database
    /**
     * Aligns the structure on a double-word boundary.
     */
    WORD   wPad;    // dword alignment            
    union {     //This is a union 
        /**
         * CEFILEINFO structure that contains information about a file. This member is valid only if
         * wObjType is OBJTYPE_FILE.
         */
        CEFILEINFO  infFile;           //Valid for file objects
        /**
         * CEDIRINFO structure that contains information about a directory. This member is valid only if
         * wObjType is OBJTYPE_DIRECTORY.
         */
        CEDIRINFO   infDirectory;      //Valid for directory objects
// @CESYSGEN IF FILESYS_FSDBASE
        /**
         * CEDBASEINFO structure that contains information about a database. This member is valid only if
         * wObjType is OBJTYPE_DATABASE.
         */
        CEDBASEINFO infDatabase;       //Valid for database objects
        /**
         * CERECORDINFO structure that contains information about a record in a database. This member is
         * valid only if wObjType is OBJTYPE_RECORD.
         */
        CERECORDINFO infRecord;        //Valid for record objects
// @CESYSGEN ENDIF
    };
} CEOIDINFO;

// Functions
/**
 * This function retrieves information about an object in the object store. This function is
 * obsolete. Applications should call CeOidGetInfoEx instead.
 *
 * @param oid [in] Identifier of the object for which information is to be retrieved.
 * @param poidInfo [out] Pointer to a CEOIDINFO structure that contains information about the
 *   object.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError. GetLastError may return ERROR_INVALID_HANDLE if the specified object identifier is
 *   invalid.
 *
 * Use the CeOidGetInfo function to retrieve information about any object in the object store
 * database or file system.
 */
BOOL CeOidGetInfo (CEOID oid, CEOIDINFO *oidInfo);

// @CESYSGEN ENDIF

#ifdef WINCEOEM
#include <pwindbas.h>	// internal defines 
#ifdef WINCEMACRO
#include <mwindbas.h>
#endif
#endif

// @CESYSGEN ENDIF

// Rename CE Ver 1.0 names for backwards compatibility

/**
 * This message is sent when a new object is created in the object store. See DB_CEOID_CREATED.
 *
 * @param oidCreated Identifier of the newly created object.
 * @param oidParent Identifier of the parent object of the newly created object.
 */
#define DB_PEGOID_CREATED              DB_CEOID_CREATED
/**
 * This message is sent when a record has been deleted from the object store.
 *
 * @param oidDeletedRec Identifier of the record that was deleted.
 * @param oidParent Identifier of the parent object of the deleted record.
 */
#define DB_PEGOID_RECORD_DELETED       DB_CEOID_RECORD_DELETED
/**
 * This message is sent when an object in the object store has been modified. See DB_CEOID_CHANGED.
 *
 * @param oidChanged Identifier of the object that was modified.
 * @param oidParent Identifier of the parent object of the modified object.
 */
#define DB_PEGOID_CHANGED	       DB_CEOID_CHANGED
#define PEGPROPID                      CEPROPID
#define PPEGPROPID                     PCEPROPID
#define PEGOID                         CEOID
#define PPEGOID                        PCEOID
#define PEGFILEINFO                    CEFILEINFO
#define PEGDIRINFO                     CEDIRINFO
#define PEGRECORDINFO                  CERECORDINFO
#define PEGDB_SORT_DESCENDING          CEDB_SORT_DESCENDING
#define PEGDB_SORT_CASEINSENSITIVE     CEDB_SORT_CASEINSENSITIVE
#define PEGDB_SORT_UNKNOWNFIRST        CEDB_SORT_UNKNOWNFIRST
#define PEGDB_SORT_GENERICORDER        CEDB_SORT_GENERICORDER
#define PEGDB_MAXDBASENAMELEN          CEDB_MAXDBASENAMELEN
#define PEGDB_MAXSORTORDER             CEDB_MAXSORTORDER
#define PEGDB_VALIDNAME                CEDB_VALIDNAME
#define PEGDB_VALIDTYPE                CEDB_VALIDTYPE
#define PEGDB_VALIDSORTSPEC            CEDB_VALIDSORTSPEC
#define PEGDB_VALIDMODTIME	       CEDB_VALIDMODTIME
#define PEGDBASEINFO                   CEDBASEINFO
#define PEGOIDINFO                     CEOIDINFO
#define PEGDB_AUTOINCREMENT            CEDB_AUTOINCREMENT
#define PEGDB_SEEK_PEGOID              CEDB_SEEK_CEOID
#define PEGDB_SEEK_BEGINNING           CEDB_SEEK_BEGINNING
#define PEGDB_SEEK_END                 CEDB_SEEK_END
#define PEGDB_SEEK_CURRENT             CEDB_SEEK_CURRENT
#define PEGDB_SEEK_VALUESMALLER        CEDB_SEEK_VALUESMALLER
#define PEGDB_SEEK_VALUEFIRSTEQUAL     CEDB_SEEK_VALUEFIRSTEQUAL
#define PEGDB_SEEK_VALUEGREATER        CEDB_SEEK_VALUEGREATER
#define PEGDB_SEEK_VALUENEXTEQUAL      CEDB_SEEK_VALUENEXTEQUAL
#define PEGBLOB                        CEBLOB
#define PEGVT_I2                       CEVT_I2
#define PEGVT_UI2                      CEVT_UI2
#define PEGVT_I4                       CEVT_I4
#define PEGVT_UI4                      CEVT_UI4
#define PEGVT_FILETIME                 CEVT_FILETIME
#define PEGVT_LPWSTR                   CEVT_LPWSTR
#define PEGVT_BLOB                     CEVT_BLOB
#define PEGVALUNION                    CEVALUNION
#define PEGDB_PROPNOTFOUND             CEDB_PROPNOTFOUND
#define PEGDB_PROPDELETE               CEDB_PROPDELETE
#define PEGPROPVAL                     CEPROPVAL
#define PPEGPROPVAL                    PCEPROPVAL
#define PEGDB_MAXDATABLOCKSIZE         CEDB_MAXDATABLOCKSIZE
#define PEGDB_MAXPROPDATASIZE          CEDB_MAXPROPDATASIZE
#define PEGDB_MAXRECORDSIZE            CEDB_MAXRECORDSIZE
#define PEGDB_ALLOWREALLOC             CEDB_ALLOWREALLOC
#define PegOidGetInfo                  CeOidGetInfo
#define PegFindFirstDatabase           CeFindFirstDatabase
#define PegFindNextDatabase            CeFindNextDatabase
#define PegCreateDatabase              CeCreateDatabase
#define PegSetDatabaseInfo             CeSetDatabaseInfo
#define PegOpenDatabase                CeOpenDatabase
#define PegDeleteDatabase              CeDeleteDatabase
#define PegSeekDatabase                CeSeekDatabase
#define PegDeleteRecord                CeDeleteRecord
#define PegReadRecordProps             CeReadRecordProps
#define PegWriteRecordProps            CeWriteRecordProps

#endif

