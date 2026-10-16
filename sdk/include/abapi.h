/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1997 - 1998 Microsoft Corporation

Module Name:

    abDLL.h

Abstract:

    prototypes for using exported functions from abDLL.dll

    NOTE - this represents work in progress and may dramatically
            change before the AutoPC ships

-------------------------------------------------------------------*/

#ifndef _ABAPI_H
#define _ABAPI_H


#include <windbase.h>		// WinCE DB stuff
#include <addrmapi.h>		// list of props in address book DB


#ifdef __cplusplus
extern "C" {
#endif //__cplusplus


// Auto PC internal fields - do not modify these directly
#define HHPR_PHONEORDER                         PROP_TAG(PT_UNICODE, 0x4998)  // BUGBUG: need to propogate this to oak\inc\addrmapi.h
#define HHPR_VOICETAG                           PROP_TAG(PT_UNICODE, 0x4999)  // BUGBUG: need to propogate this to oak\inc\addrmapi.h


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Here is the field list that this API uses and displays to the user.
This is an example array that you can pass to abRead().

const CEPROPID kFullProp[] =
{
    HHPR_SURNAME,                   // offset 0 - Names
    HHPR_GIVEN_NAME,
    HHPR_MIDDLE_NAME,

    HHPR_OFFICE_TELEPHONE_NUMBER,   // offset 3 - Phone Numbers
    HHPR_OFFICE2_TELEPHONE_NUMBER,
    HHPR_HOME_TELEPHONE_NUMBER,
    HHPR_HOME2_TELEPHONE_NUMBER,
    HHPR_PAGER_NUMBER,
    HHPR_MOBILE_TELEPHONE_NUMBER,
    HHPR_CAR_TELEPHONE_NUMBER,
    HHPR_ASSISTANT_TELEPHONE_NUMBER,
    HHPR_PHONEORDER,                // the preferred order for phone dialing - note this is not displayed it is used though

    HHPR_OFFICE_ADDRESS_STREET,     // offset 12 - Work address
    HHPR_OFFICE_ADDRESS_CITY,
    HHPR_OFFICE_ADDRESS_STATE,
    HHPR_OFFICE_ADDRESS_POSTAL_CODE,
    HHPR_OFFICE_ADDRESS_COUNTRY,

    HHPR_HOME_ADDRESS_STREET,       // offfset 17 - Home address
    HHPR_HOME_ADDRESS_CITY,
    HHPR_HOME_ADDRESS_STATE,
    HHPR_HOME_ADDRESS_POSTAL_CODE,
    HHPR_HOME_ADDRESS_COUNTRY,

    HHPR_BUSINESS_FAX_NUMBER,       // offset 22 - Fax Numbers
    HHPR_HOME_FAX_NUMBER,

    HHPR_EMAIL1_EMAIL_ADDRESS,      // offset 24 - Email Addresses
    HHPR_EMAIL2_EMAIL_ADDRESS,
    HHPR_EMAIL3_EMAIL_ADDRESS,

    HHPR_NOTES,                     // offset 27 - free form notes - not currently displayed

    HHPR_BIRTHDAY,                  // offset 28 - Dates
    HHPR_ANNIVERSARY,

    HHPR_WEB_PAGE,                  // offset 30 - Common work and home fields not already included above
    HHPR_CATEGORY,
    HHPR_SPOUSE_NAME,
    HHPR_CHILDREN_NAME,

    HHPR_COMPANY_NAME,              // offset 34 - Work fields not already included above
    HHPR_DEPARTMENT_NAME,
    HHPR_OFFICE_LOCATION,
    HHPR_TITLE,
    HHPR_ASSISTANT_NAME,

    HHPR_VOICETAG,                  // offset 39 - voice tag field - note not displayed - it holds the voice tag ID

    HHPR_FILEAS                     // offset 40 - the sort order of the db  last first middle - not currently displayed directly
};

-------------------------------------------------------------------*/


/*---------------------------------------------
  wInitView flags for filling the ABINFO struct
  
  defines the initial view displayed
  ---------------------------------------------*/

#define ABV_MAINVIEW	1       // main contacts list with tabber index - focus set to 'ceoid'
#define ABV_LOCATE	2       // same as ABV_MAINVIEW except as if user already said "locate"
#define ABV_CARDPHONE	3       // card view, phone tab
#define ABV_CARDHOME	4       // card view, home info tab
#define ABV_CARDWORK	5       // card view, work info tab
#define ABV_CARDNOTES	6       // card view, notes tab (currently not implemented)
#define ABV_DIAL	7       // asks user "dial preferred #?", if no then ABV_CARDPHONE shown
#define ABV_RECEIVE	8       // receive form, AutoPC waiting for Infrared connection
#define ABV_SEND	9       // send form, AutoPC attempts to send 'dwParam' contacts staring at 'ceoid' via Infrared
#define ABV_NEW 	10           // New entry wizard form


/*-------------------------------------------------
  dwEnabled flags for filling the ABINFO struct
  
  defines which features are accessible to the user
  -------------------------------------------------*/

#define ABE_BACK        0x0001   // after drilling down into i.e. card, allow to backup to main
#define ABE_CARDPHONE   0x0002   // allow display of Phone card
#define ABE_CARDHOME    0x0004   // allow display of Home card
#define ABE_CARDWORK    0x0008   // allow display of Work card
#define ABE_CARDNOTES   0x0010   // allow display of Notes card (Not Impl)
#define ABE_DELETE      0x0020   // allow Delete Command
#define ABE_DIAL        0x0040   // allow Dial Command
#define ABE_EDIT        0x0080   // allow Edit Command
#define ABE_NEW         0x0100   // allow New Command
#define ABE_RECEIVE     0x0200   // allow Recieve Command
#define ABE_SENDONE     0x0400   // allow Send One Command
#define ABE_SENDALL     0x0800   // allow Send All Command

#define ABE_OPTIONMENU  0x1000    // allows the forms to setup the forms manager menu
#define ABE_VOICEMENU   0x2000    // allows the user to interact with the address book with their voice
#define ABE_EXITMAIN    0x4000    // allows the user to exit the main view
#define ABE_TTS         0x8000    // makes the UI behave like it was invoked with speech commands instead of keyboard

#define ABE_MAINVIEW   0x10000    // reserved
#define ABE_DBEMPTY    0x20000    // reserved
#define ABE_VTMAKE     0x40000    // reserved
#define ABE_VTDEL      0x80000    // reserved
#define ABE_LOGINFAIL        0x100000    // returned in the enabled flags of the structure if the AB exited due to login failure
#define ABE_PRESERVEAPPFOCUS 0x200000    // passed in, forces ABAPI to leave app in forground and exit AB upon login failure

// common combinations of ABE_ flags

#define ABE_ALL         0x3fff      // enable everything
#define ABE_CARDALL     0x001e      // card view phone, home, work and notes tabs
#define ABE_EDITALL     0x01a0      // delete, edit, new
#define ABE_IRALL       0x0e00      // receive, sendone, sendall

// abapi notification flags returned in dwParam
#define ABN_RECORDS_ADDED     0x0001  // records have been added since entering abapi
#define ABN_RECORDS_DELETED   0x0002  // records have been deleted since entering abapi
#define ABN_EXIT_USING_VOICE  0x0004  // user exited abapi using voice
#define ABN_RESORT_DB         0x0008  // user change db fields affecting sort sequence

#ifdef INTERFACE
#undef INTERFACE
#endif

#define INTERFACE

//
// The IVerifyContactSink
//
DECLARE_INTERFACE_(IVerifyContactSink, IUnknown)
{
    STDMETHOD(IsContactValid)(THIS_ CEOID ceoidContact, PROPID propidAddress, BSTR* pbstrExplanation) PURE;
};
//  IsValidContact - returns S_OK if contact is ok, S_FALSE if not
//  ceoidContact - CE OID of the contact to validate
//  propidAddress - HHPR_OFFICE_ADDRESS_STREET or HHPR_HOME_ADDRESS_STREET
//                 Use to determine which address fields to validate

#undef  INTERFACE


/*------------------
  abDialog structure
  ------------------*/

typedef struct
{
    CEOID   ceoid;      // contact ID - read/write
    DWORD   dwEnabled;  // feature enable mask - combination of ABE_ constants - read
    DWORD   dwParam;    // depends on wInitView - should be zero if unused
    WORD    wInitView;  // initial/final view - one of ABV_ constants - read/write
    WORD   wFieldOrd;  // field ordinal - read/write 
    WORD    wCard;      // default/final card view - one of ABV_ constants - read/write
    BSTR    bstrHelpIndexFile;  // help index file, if NULL  && topic NULL use AddrBook help
    BSTR    bstrHelpTopicFile;  // initial help topic file, NULL == start at index 
    BSTR    bstrMainFormCaption; // Use if ABV_MAINVIEW is shown
    BSTR    bstrCardFormCaption; // Use if ABV_CARD* is shown
    BSTR    bstrParam1;
    BSTR    bstrParam2; 
    IVerifyContactSink *pVerifyListSink;        // Reserved
    IVerifyContactSink *pVerifySelectionSink;   // if specified, called before selection accepted
} ABDIALOGINFO, *LPDIALOGINFO;

/*
wInitView 
ABV_MAINVIEW
in:
    dwParam - ABNotify
    wCard - Def Card    
out:
    wCard - Last Card    
    
ABV_LOCATE

ABV_CARDPHONE
in:
    dwParam - ABNotify
    wCard - ABV_CARDPHONE    
out:
    wCard - Last Card    
    
ABV_CARDHOME
in:
    wCard - ABV_CARDHOME    
out:
    dwParam - ABNotify
    wCard - Last Card    
    
ABV_CARDWORK
in:
    wCard - ABV_CARDWORK    
out:
    dwParam - ABNotify
    wCard - Last Card    
    
ABV_CARDNOTES
in:
    wCard - ABV_CARDNOTES    
out:
    dwParam - ABNotify
    wCard - Last Card    
    
ABV_DIAL
in:
    dwParam - NULL or lpwsPhnNum or field id to dial      
    wFieldOrd - if dwparam == NULL, field search order to use
    bstrParam1 - record name (person name)
    bstrParam2 - Field Name (Home Phone)
    
ABV_RECEIVE
ABV_SEND
    dwParam - # to send
*/

#define DIAL_PREF_WORK    0
#define DIAL_PREF_HOME    1
#define DIAL_PREF_MOBILE  2
#define DIAL_PREF_PAGER   3
#define DIAL_PREF_USEDEFAULT   0xffff


/*---------------------
  abDialog return codes
  ---------------------*/

#define S_NO_PHONE_NUMS     0x01000001      // ABV_DIAL - contact has no valid phone numbers
#define S_USER_NO_TO_DIAL   0x01000002      // ABV_DIAL - user answered NO to dial specified phone number
#define S_USER_ABORTED      0x01000003      // ABV_DIAL - call aborted by user
#define S_PHONE_ABORTED     0x01000004      // ABV_DIAL - call aborted due to hardware problem
#define S_CARD_DELETED      0x01000005      // ABV_CARD - contact was deleted by user



/*-----------------------------------------
  initialize Address Book - call this first
  -----------------------------------------*/

HRESULT abOpen(
    IfmManage   *pFrmMgr);       // pointer to caller's Form Manager Interface - read


/*---------------------------------------
  shut down Address Book - call this last
  ---------------------------------------*/

HRESULT abClose();


/*-------------------------------------------------------------------------------
  launch the Address Book view specified in ABINFO with specific features enabled
  -------------------------------------------------------------------------------*/

HRESULT abDialog(
    LPDIALOGINFO    lpABInfo);  // pointer to ABDIALOGINFO struct - read (see struct def)


/*----------------------------------------------------
  Seek to a record in the DB - See CeSeekDatabase docs
  ----------------------------------------------------*/

HRESULT abSeek(
    DWORD   dwSeekType,         // one of CEDB_SEEK_* constants from windbase.h
    DWORD   dwValue,            // depends on dwSeekType
    PCEOID  pCEOid,             // pointer to CEOID to receive record ID
    LPDWORD lpdwIndex);         // pointer to DWORD to receive ordinal from start of DB


/*--------------------------------------------------
  read several fields of current or specified record
  --------------------------------------------------*/

HRESULT abRead(
    CEOID       ceoid,          // record id or NULL for current - read
    LPWORD      lpwNumProp,     // how many fields requested/read - read/write
    CEPROPID    *rgPropID,      // array of HHPR_* ids indicating fields to retrieve (see addrmapi.h) - read
    PCEPROPVAL  *prgCEPropVal); // pointer to PCEPROPVAL that receives data


/*----------------------------------------------
  write several fields of new or existing record
  ----------------------------------------------*/

HRESULT abWrite(
    CEOID *poid,                // *poid = NULL for new record, = existing CEOID to modify record - read/write
    WORD wNumProp,              // how many fields to be written - read
    PCEPROPVAL rgCEPropVal);    // CEPROPVAL array containing field data - read

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //_ABAPI_H
