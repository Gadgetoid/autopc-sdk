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

typedef struct _CEFILEINFO {
    DWORD   dwAttributes;
    CEOID     oidParent;
    WCHAR szFileName[MAX_PATH];
    FILETIME ftLastChanged;
    DWORD   dwLength;
} CEFILEINFO;

typedef struct _CEDIRINFO {
    DWORD   dwAttributes;
    CEOID  oidParent;
    WCHAR   szDirName[MAX_PATH];
} CEDIRINFO;

#define DB_CEOID_CREATED	(WM_USER + 0x1)
#define DB_CEOID_DATABASE_DELETED	(WM_USER + 0x2)
#define DB_CEOID_RECORD_DELETED	(WM_USER + 0x3)
#define DB_CEOID_FILE_DELETED	(WM_USER + 0x4)
#define DB_CEOID_DIRECTORY_DELETED	(WM_USER + 0x5)
#define DB_CEOID_CHANGED	(WM_USER + 0x6)

// flags for CeGetReplChangeMask
#define REPL_CHANGE_WILLCLEAR	0x00000001

typedef struct STORE_INFORMATION {
	DWORD dwStoreSize;
	DWORD dwFreeSize;
} STORE_INFORMATION, *LPSTORE_INFORMATION;

BOOL GetStoreInformation (LPSTORE_INFORMATION lpsi);

// @CESYSGEN ENDIF


// @CESYSGEN IF FILESYS_FSDBASE

typedef DWORD CEPROPID;
typedef CEPROPID *PCEPROPID;
#define TypeFromPropID(propid) LOWORD(propid)

typedef struct _CERECORDINFO {
    CEOID  oidParent;
} CERECORDINFO;

#define CEDB_SORT_DESCENDING         0x00000001
#define CEDB_SORT_CASEINSENSITIVE    0x00000002
#define CEDB_SORT_UNKNOWNFIRST       0x00000004
#define CEDB_SORT_GENERICORDER       0x00000008  // internally used for generic ordering
typedef struct _SORTORDERSPEC {
    CEPROPID  propid;
    DWORD   dwFlags;
} SORTORDERSPEC;

#define CEDB_MAXDBASENAMELEN 32
#define CEDB_MAXSORTORDER   4

// values for flag
#define CEDB_VALIDNAME     0x0001
#define CEDB_VALIDTYPE     0x0002
#define CEDB_VALIDSORTSPEC 0x0004
#define CEDB_VALIDMODTIME	0x0008

typedef struct _CEDBASEINFO {
    DWORD   dwFlags;
    WCHAR   szDbaseName[CEDB_MAXDBASENAMELEN];
    DWORD   dwDbaseType;
    WORD    wNumRecords;
    WORD    wNumSortOrder;
    DWORD	dwSize;
    FILETIME ftLastModified;
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


typedef struct _CEBLOB {
    DWORD           dwCount;
    LPBYTE          lpb;
} CEBLOB;

#define CEVT_I2       2
#define CEVT_UI2      18
#define CEVT_I4       3
#define CEVT_UI4      19
#define CEVT_FILETIME 64
#define CEVT_LPWSTR   31
#define CEVT_BLOB     65

typedef union _CEVALUNION {
    short           iVal;
    USHORT          uiVal;
    long            lVal;
    ULONG           ulVal;
    FILETIME        filetime;
    LPWSTR          lpwstr;
    CEBLOB         blob;
} CEVALUNION;
 
// dont define flags in low byte
#define CEDB_PROPNOTFOUND 0x0100
#define CEDB_PROPDELETE   0x0200
typedef struct _CEPROPVAL {
    CEPROPID   propid;
    WORD        wLenData;
    WORD        wFlags;
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

HANDLE CeFindFirstDatabase (DWORD dwClassID);
CEOID CeFindNextDatabase (HANDLE hEnum);
CEOID CeCreateDatabase (LPWSTR lpszname, DWORD dwClassID, WORD wNumSortOrder, SORTORDERSPEC *rgSortSpecs);
BOOL CeSetDatabaseInfo (CEOID oidDbase, CEDBASEINFO *pNewInfo);
HANDLE CeOpenDatabase (PCEOID poid, LPWSTR lpszName, CEPROPID propid, DWORD dwFlags, HWND hwndNotify);
BOOL CeDeleteDatabase (CEOID oid);
CEOID CeSeekDatabase (HANDLE hDatabase, DWORD dwSeekType, DWORD dwValue, LPDWORD lpdwIndex);
BOOL CeDeleteRecord (HANDLE hDatabase, CEOID oidRecord);
CEOID CeReadRecordProps (HANDLE hDbase, DWORD dwFlags, LPWORD lpcPropID, CEPROPID *rgPropID, LPBYTE *lplpBuffer, LPDWORD lpcbBuffer);
CEOID CeWriteRecordProps (HANDLE hDbase, CEOID oidRecord, WORD cPropID, CEPROPVAL *rgPropVal);

// @CESYSGEN ENDIF


// @CESYSGEN IF FILESYS_FSMAIN

#define OBJTYPE_INVALID     0
#define OBJTYPE_FILE        1
#define OBJTYPE_DIRECTORY   2
#define OBJTYPE_DATABASE    3
#define OBJTYPE_RECORD      4

typedef struct _CEOIDINFO {
    WORD  wObjType;             //Type of object
            //        OBJTYPE_INVALID   | There was no valid object with this CEOID
            //        OBJTYPE_FILE      | The object is a file
            //        OBJTYPE_DIRECTORY | The object is a directory
            //        OBJTYPE_DATABASE  | The object is a database
            //        OBJTYPE_RECORD    | The object is a record inside a database
    WORD   wPad;    // dword alignment            
    union {     //This is a union 
        CEFILEINFO  infFile;           //Valid for file objects
        CEDIRINFO   infDirectory;      //Valid for directory objects
// @CESYSGEN IF FILESYS_FSDBASE
        CEDBASEINFO infDatabase;       //Valid for database objects
        CERECORDINFO infRecord;        //Valid for record objects
// @CESYSGEN ENDIF
    };
} CEOIDINFO;

// Functions
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

#define DB_PEGOID_CREATED              DB_CEOID_CREATED
#define DB_PEGOID_RECORD_DELETED       DB_CEOID_RECORD_DELETED
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

