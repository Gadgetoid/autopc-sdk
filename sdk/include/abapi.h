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
/**
 * This interface provides methods that allow an application to modify how the address book responds
 * to events .
 */
DECLARE_INTERFACE_(IVerifyContactSink, IUnknown)
{
    /**
     * This method checks whether the information stored for a contact is valid.
     *
     * @param ceoidContact Object identifier for the contact.
     * @param propidAddress Property identifier that specifies the fields from the contact's address
     *   that you want to validate. It is one of the following values. Value Description
     *   HHPR_OFFICE_ADDRESS_STREET Street address for the contact's workplace. HHPR_HOME_ADDRESS_STREET
     *   Street address for the contact's home.
     * @param pbstrExplanation Pointer to a Unicode string that receives an explanation of how the
     *   contact's information is invalid. The address book currently passes a NULL pointer for this
     *   parameter. If the application returns a pointer, the address book frees the memory for the BSTR.
     *
     * @return S_OK indicates that the information for the contact is valid. S_FALSE indicates that the
     *   information for the contact is not valid.
     */
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

/**
 * This structure contains information used by the Address Book API.
 */
typedef struct
{
    /**
     * Contact object identifier. This member is read/write.
     */
    CEOID   ceoid;      // contact ID - read/write
    /**
     * Specifies which features are enabled. This read member is one or a combination of the following
     * flags: Flag Value Description ABE_BACK 0x0001 Allows the user to return to the main view after
     * changing to another view. ABE_CARDPHONE 0x0002 Enables the card view for the phone tab.
     * ABE_CARDHOME 0x0004 Enables the card view for the home tab. ABE_CARDWORK 0x0008 Enables the card
     * view for the work tab. ABE_CARDNOTES 0x0010 Enables the card view for the notes tab. ABE_DELETE
     * 0x0020 Notifies the Address Book that the user is allowed to delete cards. ABE_DIAL 0x0040
     * Notifies the Address Book that the user is allowed to dial phone numbers from a card. ABE_EDIT
     * 0x0080 Notifies the Address Book that the user is allowed to edit, or create new cards.
     * ABE_EXITMAIN 0x4000 Notifies the Address Book that the user is allowed to exit the main form.
     * ABE_NEW 0x0100 Notifies the Address Book that the user is allowed to add cards. ABE_OPTIONMENU
     * 0x1000 Enables the Address Book option menu. ABE_PRESERVEAPPFOCUS 0x200000 Forces the Address
     * Book API to leave the application in the foreground and to exit the address book when the login
     * fails. ABE_RECEIVE 0x0200 Notifies the Address Book that the user is allowed to receive contact
     * information via the infrared port. ABE_SENDONE 0x0400 Notifies the Address Book that the user is
     * allowed to send contact information via the infrared port. ABE_SENDALL 0x0800 Notifies the
     * Address Book that the user is allowed to send all contact information via the infrared port.
     * ABE_VOICEMENU 0x2000 Allows the user to interact with the Address Book through speech. ABE_TTS
     * 0x8000 Makes the user interface (UI) behave as if it were invoked with speech commands instead of
     * the keyboard. ABE_ALL 0x0fff Combination flag that enables all address book functions.
     * ABE_CARDALL 0x001e Combination flag that enables the card view for phone, home, work, and notes
     * tabs. ABE_EDITALL 0x01a0 Combination flag that allows the user to delete, edit, or create new
     * cards. ABE_IRALL 0x0e00 Combination flag that allows the user to receive, send one, or send all
     * messages.
     */
    DWORD   dwEnabled;  // feature enable mask - combination of ABE_ constants - read
    /**
     * Specifies a DWORD that indicates the user's actions while in the card view. It is one of the
     * flags shown in the following table. This member must be zero if unused. Flag Value Description
     * ABN_RECORDS_ADDED 0x0001 The user has added records since the Address Book API started.
     * ABN_RECORDS_DELETED 0x0002 The user has deleted records since the Address Book API started.
     * ABN_EXIT_USING_VOICE 0x0004 The user exited the Address Book API by using speech commands.
     * ABN_RESORT_DB 0x0008 The user changed database fields, affecting the sort sequence.
     */
    DWORD   dwParam;    // depends on wInitView - should be zero if unused
    /**
     * Unsigned 16-bit character that indicates the initial or final view. This member is one of the
     * following values: Flag Value Description ABV_MAINVIEW 1 Displays main contacts list with tabber
     * index. Focus is set to ceoid. ABV_LOCATE 2 Displays same screen as ABV_MAINVIEW unless the user
     * has already said, "Locate." ABV_CARDPHONE 3 Displays card view at the phone tab. ABV_CARDHOME 4
     * Displays card view at the home information tab. ABV_CARDWORK 5 Displays card view at the work
     * information tab. ABV_CARDNOTES 6 Displays card view at the notes tab. This value is not currently
     * implemented. ABV_DIAL 7 Displays screen asking the user, "Dial preferred number?" If the user
     * replies, "No," then ABV_CARDPHONE is shown on the Auto PC display. ABV_RECEIVE 8 Displays the
     * infrared Receive form. The Auto PC is waiting for an infrared connection. ABV_SEND 9 Displays the
     * infrared Send form. The Auto PC attempts to send dwParam contacts starting at ceoid by means of
     * infrared.
     */
    WORD    wInitView;  // initial/final view - one of ABV_ constants - read/write
    /**
     * Unsigned 16-bit integer that indicates the field ordinal. This member is read/write.
     */
    WORD   wFieldOrd;  // field ordinal - read/write 
    /**
     * Unsigned 16-bit character that indicates the default or final view. This member uses the same
     * flags listed for the wInitView member.
     */
    WORD    wCard;      // default/final card view - one of ABV_ constants - read/write
    /**
     * Unicode string that contains the name of the Help index file. If this string or the topic is
     * NULL, use Address Book Help.
     */
    BSTR    bstrHelpIndexFile;  // help index file, if NULL  && topic NULL use AddrBook help
    /**
     * Unicode string that contains the name of the initial Help topic file. If NULL, start at index.
     */
    BSTR    bstrHelpTopicFile;  // initial help topic file, NULL == start at index 
    /**
     * Unicode string that contains the main form caption to use if ABV_MAINVIEW is shown.
     */
    BSTR    bstrMainFormCaption; // Use if ABV_MAINVIEW is shown
    /**
     * Unicode string that contains the card form caption use if ABV_CARD* is shown.
     */
    BSTR    bstrCardFormCaption; // Use if ABV_CARD* is shown
    /**
     * Unicode string that contains the name of the contact shown in the Dial dialog box.
     */
    BSTR    bstrParam1;
    /**
     * Unicode string that contains the location of the contact shown in the Dial dialog box.
     */
    BSTR    bstrParam2; 
    /**
     * Reserved for future use.
     */
    IVerifyContactSink *pVerifyListSink;        // Reserved
    /**
     * Pointer to a sink. If specified, this sink is called when the user makes a selection to determine
     * if selection should be accepted.
     */
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

/**
 * This function initializes the address book.
 *
 * @param pFrmMgr [in] Pointer to the caller's forms manager interface.
 *
 * @return NOERROR indicates success. S_FALSE indicates failure.
 *
 * You should initialize the name and icon of your application with the Forms Manager before calling
 * the Address Book API.
 *
 * The following code example shows how to use the Address Book API. The abOpen function is used to
 * open the application.
 *
 *     AbOpen(pFrmMgr);
 *     ABDIALOGIN abDl = {
 *      NULL,
 *      0,
 *      NULL,
 *      ABV_MAINVIEW,
 *      0
 *     };
 *     abDialog(&abDl);
 *     WORD wNumProp = 2;
 *     CEPROPID cepi[] = {HHPR_GIVEN_NAME, HHPR_SURNAME};
 *     PCEPROPVAL pcepv;
 *     abRead(abDl.ceoid, &wNumProp, cepi, &pcepv);
 *     abClose();
 */
HRESULT abOpen(
    IfmManage   *pFrmMgr);       // pointer to caller's Form Manager Interface - read


/*---------------------------------------
  shut down Address Book - call this last
  ---------------------------------------*/

/**
 * This function shuts down the address book.
 *
 * @return NOERROR indicates success. S_FALSE indicates failure.
 *
 * The following code example shows how to use the Address Book API. The abClose function is called
 * at the end of the example to close the address book.
 *
 *     AbOpen(pFrmMgr);
 *     ABDIALOGIN abDl = {
 *      NULL,
 *      0,
 *      NULL,
 *      ABV_MAINVIEW,
 *      0
 *     };
 *     abDialog(&abDl);
 *     WORD wNumProp = 2;
 *     CEPROPID cepi[] = {HHPR_GIVEN_NAME, HHPR_SURNAME};
 *     PCEPROPVAL pcepv;
 *     abRead(abDl.ceoid, &wNumProp, cepi, &pcepv);
 *     abClose();
 */
HRESULT abClose();


/*-------------------------------------------------------------------------------
  launch the Address Book view specified in ABINFO with specific features enabled
  -------------------------------------------------------------------------------*/

/**
 * This function launches the Address Book view specified in the ABDIALOGINFO structure.
 *
 * @param lpABInfo [in/out] Long pointer to an ABDIALOGINFO structure.
 *
 * @return One of the values described in the following table is returned. Return Code Value
 *   Description S_NO_PHONE_NUMS 0x01000001 Contact has no valid phone numbers. S_USER_NO_TO_DIAL
 *   0x01000002 User answered "No" to the question, "Dial specified phone number?" S_USER_ABORTED
 *   0x01000003 User cancelled the call. S_PHONE_ABORTED 0x01000004 Call was cancelled because of
 *   hardware problems. S_CARD_DELETED 0x01000005 User deleted the contact.
 *
 * A user cannot open the address book directly to a specified contact and delete the contact.
 *
 * The following code example shows how the Address Book main form allows the user to select a
 * contact. After the user selects a contact by pressing ENTER on the contact name on the main form,
 * another form appears that displays all of the phone numbers for the contact. When the user
 * selects one of the phone numbers and presses ENTER, abDialog returns the CEOID that contains the
 * object identifier of the contact the user selected and reads the specified name and surname from
 * the database.
 *
 *     AbOpen(pFrmMgr);
 *     ABDIALOGIN abDl = {
 *      NULL,
 *      0,
 *      NULL,
 *      ABV_MAINVIEW,
 *      0
 *     };
 *     abDialog(&abDl);
 *     WORD wNumProp = 2;
 *     CEPROPID cepi[] = {HHPR_GIVEN_NAME, HHPR_SURNAME};
 *     PCEPROPVAL pcepv;
 *     abRead(abDl.ceoid, &wNumProp, cepi, &pcepv);
 *     abClose();
 */
HRESULT abDialog(
    LPDIALOGINFO    lpABInfo);  // pointer to ABDIALOGINFO struct - read (see struct def)


/*----------------------------------------------------
  Seek to a record in the DB - See CeSeekDatabase docs
  ----------------------------------------------------*/

/**
 * This function searches for a record in the Address Book database.
 *
 * @param dwSeekType Specifies the type of seek operation to perform. It is one of the following
 *   flags: - CEDB_SEEK_CEOID: Seek until finding an object that has the object identifier specified
 *   in the dwValue parameter. This type of seek operation is very efficient. -
 *   CEDB_SEEK_VALUESMALLER: Seek until finding the largest value that is smaller than the specified
 *   value. If none of the records has a smaller value, the seek pointer is left at the end of the
 *   database and the function returns a zero. The dwValue parameter is a pointer to a CEPROPVAL
 *   structure, which contains the specified value. - CEDB_SEEK_VALUEFIRSTEQUAL: Seek until finding
 *   the first value that is equal to the specified value. If the seek operation fails, the seek
 *   pointer is left at the end of the database, and the function returns a zero. The dwValue
 *   parameter is a pointer to a CEPROPVAL structure, which contains the specified value. -
 *   CEDB_SEEK_VALUENEXTEQUAL: Starting from the current seek position, seek exactly one position
 *   forward in the sorted order and check if the next record is equal to the value specified in the
 *   dwValue parameter. If so, return the object identifier of this next record; otherwise, return a
 *   zero and leave the seek pointer at the end of the database. This operation can be used in
 *   conjunction with the CEDB_SEEK_VALUEFIRSTEQUAL operation to enumerate all records with an equal
 *   value. - CEDB_SEEK_VALUEGREATER: Seek until finding a value greater than or equal to the
 *   specified value. If all records are smaller, the seek pointer is left at the end of the database
 *   and the function returns zero. The dwValue parameter is a pointer to a CEPROPVAL structure, which
 *   contains the specified value. - CEDB_SEEK_BEGINNING: Starting from the beginning of the database,
 *   seek forward for the number of records specified in the dwValue parameter. - CEDB_SEEK_CURRENT:
 *   Seek backward or forward from the current position of the seek pointer for the number of records
 *   specified in the dwValue parameter. The function seeks forward if dwValue is a positive value, or
 *   backward if the value is negative. A forward seek operation is efficient. - CEDB_SEEK_END:
 *   Starting from the end of the database, seek backward for the number of records specified in the
 *   dwValue parameter.
 * @param dwValue Specifies the value to use for the seek operation. The value of this parameter
 *   depends on the value of dwSeekType.
 * @param pCEOid Pointer to a CEOID that receives the record object identifier.
 * @param lpdwIndex Long pointer to a DWORD that receives the ordinal from the start of the
 *   database.
 *
 * @return NOERROR indicates success. S_FALSE indicates failure.
 */
HRESULT abSeek(
    DWORD   dwSeekType,         // one of CEDB_SEEK_* constants from windbase.h
    DWORD   dwValue,            // depends on dwSeekType
    PCEOID  pCEOid,             // pointer to CEOID to receive record ID
    LPDWORD lpdwIndex);         // pointer to DWORD to receive ordinal from start of DB


/*--------------------------------------------------
  read several fields of current or specified record
  --------------------------------------------------*/

/**
 * This function reads fields of the current record.
 *
 * @param ceoid [in] Object identifier of the record or NULL for current record.
 * @param lpwNumProp [in/out] Long pointer to the number of fields requested.
 * @param rgPropID [in] Array of HHPR_* property identifiers that indicate the fields to read. The
 *   following database fields are used by the Auto PC: HHPR_ANNIVERSARY HHPR_ASSISTANT_NAME
 *   HHPR_ASSISTANT_TELEPHONE_NUMBER HHPR_BIRTHDAY HHPR_BUSINESS_FAX_NUMBER HHPR_CAR_TELEPHONE_NUMBER
 *   HHPR_CATEGORY HHPR_CHILDREN_NAME HHPR_COMPANY_NAME HHPR_DEPARTMENT_NAME HHPR_EMAIL1_EMAIL_ADDRESS
 *   HHPR_EMAIL2_EMAIL_ADDRESS HHPR_EMAIL3_EMAIL_ADDRESS HHPR_GIVEN_NAME HHPR_HOME_ADDRESS_CITY
 *   HHPR_HOME_ADDRESS_COUNTRY HHPR_HOME_ADDRESS_POSTAL_CODE HHPR_HOME_ADDRESS_STATE
 *   HHPR_HOME_ADDRESS_STREET HHPR_HOME_FAX_NUMBER HHPR_HOME_TELEPHONE_NUMBER
 *   HHPR_HOME2_TELEPHONE_NUMBER HHPR_MIDDLE_NAME HHPR_MOBILE_TELEPHONE_NUMBER
 *   HHPR_OFFICE_ADDRESS_CITY HHPR_OFFICE_ADDRESS_COUNTRY HHPR_OFFICE_ADDRESS_POSTAL_CODE
 *   HHPR_OFFICE_ADDRESS_STATE HHPR_OFFICE_ADDRESS_STREET HHPR_OFFICE_LOCATION
 *   HHPR_OFFICE_TELEPHONE_NUMBER HHPR_OFFICE2_TELEPHONE_NUMBER HHPR_PAGER_NUMBER HHPR_SPOUSE_NAME
 *   HHPR_SURNAME HHPR_TITLE HHPR_WEB_PAGE
 * @param prgCEPropVal [out] Pointer to the PCEPROPVAL structure that receives data.
 *
 * @return NOERROR indicates success. S_FALSE indicates failure.
 *
 * The following code example shows how to use the Address Book API. The abRead function is used to
 * retrieve the information from the Given Name and Surname fields of a particular record.
 *
 *     AbOpen(pFrmMgr);
 *     ABDIALOGIN abDl = {
 *      NULL,
 *      0,
 *      NULL,
 *      ABV_MAINVIEW,
 *      0
 *     };
 *     abDialog(&abDl);
 *     WORD wNumProp = 2;
 *     CEPROPID cepi[] = {HHPR_GIVEN_NAME, HHPR_SURNAME};
 *     PCEPROPVAL pcepv;
 *     abRead(abDl.ceoid, &wNumProp, cepi, &pcepv);
 *     abClose();
 */
HRESULT abRead(
    CEOID       ceoid,          // record id or NULL for current - read
    LPWORD      lpwNumProp,     // how many fields requested/read - read/write
    CEPROPID    *rgPropID,      // array of HHPR_* ids indicating fields to retrieve (see addrmapi.h) - read
    PCEPROPVAL  *prgCEPropVal); // pointer to PCEPROPVAL that receives data


/*----------------------------------------------
  write several fields of new or existing record
  ----------------------------------------------*/

/**
 * This function writes fields to a new or existing record.
 *
 * @param poid [in] Pointer to the CEOID that contains the object identifier of an existing record
 *   to modify, or NULL for a new record.
 * @param wNumProp [in] Unsigned 16-bit value that indicates the number of fields to be written.
 * @param rgCEPropVal [in] Specifies a CEPROPVAL array that contains the data to be written.
 *
 * @return NOERROR indicates success. S_FALSE indicates failure.
 */
HRESULT abWrite(
    CEOID *poid,                // *poid = NULL for new record, = existing CEOID to modify record - read/write
    WORD wNumProp,              // how many fields to be written - read
    PCEPROPVAL rgCEPropVal);    // CEPROPVAL array containing field data - read

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //_ABAPI_H
