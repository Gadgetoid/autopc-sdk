//--------------------------------------------------------------------------------------------
//
//	Copyright (c) Microsoft Corporation, 1997 All Rights Reserved
//
//	Description:
//		AutoPC Simple Form and Control Interfaces
//
//	History: 
//		Umesh Madan	umeshm@microsoft.com	02/28/97 Created
//
//--------------------------------------------------------------------------------------------

#ifndef _ASFC_H
#define _ASFC_H

//--------------------------------------------------------------------------------------------
//
// Includes
//
//--------------------------------------------------------------------------------------------
#include <olectl.h>
#include <apcmsg.h>
#include <apcspch.h>
#include <asdisp.h>

//--------------------------------------------------------------------------------------------
//
// Messages
//
//--------------------------------------------------------------------------------------------
// The forms manager uses range 0xbf00 to 0xbf7f for APC forms manager messages

#define WM_FMBASE            APC_FRM_START      //==0xbf00 from apcmsg.h

/*++
    WM_QUERYKEYUSAGE
    =============================

    wParam - not used
    lParam - IQueryKeyUsage pointer
           - Message handlers call FlagKeysUsed( QKU_VK_*) of all keys used

    Note -  a WM_QUERYKEYUSAGE notification is sent by 
            the nav control to find out what kays are valid to hit
            
            electrical power is removed, Only when it is restored
           
--*/

#define	    WM_QUERYKEYUSAGE			(WM_FMBASE + 0)

// wParam
// lParam  - Call FlagKeysUsed the below params or'ed together

// Query Key Usage
#define QKU_VK_LEFT       0x0001
#define QKU_VK_UP         0x0002
#define QKU_VK_RIGHT      0x0004
#define QKU_VK_DOWN       0x0008
#define QKU_VK_RETURN     0x0010

/*++
    WM_NOTIFYAPPALERT
    =================

    wParam - TRUE if alert was raised, FALSE if cleared
    lParam - rsvd - 0

    Posted to the application when an alert is signalled or cleared 
    for the Application name matching the RegisterStartedApplication name
--*/

#define	    WM_NOTIFYAPPALERT			(WM_FMBASE + 1)
//--------------------------------------------------------------------------------------------
//
// Macros
//
//--------------------------------------------------------------------------------------------
#ifdef __ASFCDLL

#ifndef ASFCAPI
#define ASFCAPI			__declspec(dllexport) HRESULT __stdcall
#endif

#else

#ifndef ASFCAPI
#define ASFCAPI			__declspec(dllimport) HRESULT __stdcall
#endif

#endif

//--------------------------------------------------------------------------------------------
//
// APIs
//
//--------------------------------------------------------------------------------------------
STDAPI ASFCCreateFont(FONTDESC *pfd, REFIID riid, PVOID *pvFont);

//--------------------------------------------------------------------------------------------
//
// Declarations
//
//--------------------------------------------------------------------------------------------
DECLARE_INTERFACE(IASControl);
DECLARE_INTERFACE(IASForm);
DECLARE_INTERFACE(IASActiveForms);
DECLARE_INTERFACE(IfmManage);
DECLARE_INTERFACE(IfmSystem);
DECLARE_INTERFACE(IfmCollection);
DECLARE_INTERFACE(IfmStorage);

DECLARE_INTERFACE(IASClassMsgSink);
DECLARE_INTERFACE(IASEventSink);
DECLARE_INTERFACE(IASSystemEventSink);
DECLARE_INTERFACE(IFMDraw);
DECLARE_INTERFACE(IASGUIDefaults);

//--------------------------------------------------------------------------------------------
//
// Guids
// Each object is listed along with it's interfaces
//
//--------------------------------------------------------------------------------------------
//
// The base Control Objeds and interfaces. 
//
// {6D318C40-9343-11d0-B512-00A024A652FA}
DEFINE_GUID(IID_ASCONTROL, 
0x6d318c40, 0x9343, 0x11d0, 0xb5, 0x12, 0x0, 0xa0, 0x24, 0xa6, 0x52, 0xfa);
// {6D318C41-9343-11d0-B512-00A024A652FA}
DEFINE_GUID(IID_ASCLASSMSGSINK, 
0x6d318c41, 0x9343, 0x11d0, 0xb5, 0x12, 0x0, 0xa0, 0x24, 0xa6, 0x52, 0xfa);
// {6D318C42-9343-11d0-B512-00A024A652FA}
DEFINE_GUID(IID_ASEVENTSINK, 
0x6d318c42, 0x9343, 0x11d0, 0xb5, 0x12, 0x0, 0xa0, 0x24, 0xa6, 0x52, 0xfa);
//
// A standard form Object
//
// {37C23051-997F-11d0-88DC-0000F80401D1}
DEFINE_GUID(CLSID_ASFORM, 
0x37c23051, 0x997f, 0x11d0, 0x88, 0xdc, 0x0, 0x0, 0xf8, 0x4, 0x1, 0xd1);

// IASForm is exposed by all forms
// {6D318C43-9343-11d0-B512-00A024A652FA}
DEFINE_GUID(IID_ASFORM, 
0x6d318c43, 0x9343, 0x11d0, 0xb5, 0x12, 0x0, 0xa0, 0x24, 0xa6, 0x52, 0xfa);

// An additional interface on the form for IconTray application icons
// {8A822EFE-628B-11d1-9B28-0000F8757D96}
DEFINE_GUID(IID_ASICONTRAY,
0x8a822efe, 0x628b, 0x11d1, 0x9b, 0x28, 0x0, 0x0, 0xf8, 0x75, 0x7d, 0x96);

// {D7971260-933B-11d0-B512-00A024A652FA}
// Form manager device context interface
DEFINE_GUID(IID_FMDRAW, 
0xd7971260, 0x933b, 0x11d0, 0xb5, 0x12, 0x0, 0xa0, 0x24, 0xa6, 0x52, 0xfa);

//
// Forms Manager
//
// {196F4760-5F84-11d1-9B27-0000F8757D96}
DEFINE_GUID(CLSID_FMMANAGE, 
0x196f4760, 0x5f84, 0x11d1, 0x9b, 0x27, 0x0, 0x0, 0xf8, 0x75, 0x7d, 0x96);

// {1FB926E1-A17C-11d0-88E0-0000F80401D1}
DEFINE_GUID(IID_FMMANAGE, 
0x1fb926e1, 0xa17c, 0x11d0, 0x88, 0xe0, 0x0, 0x0, 0xf8, 0x4, 0x1, 0xd1);

// {0C435CA0-A17A-11d0-88E0-0000F80401D1}
DEFINE_GUID(IID_ASACTIVEFORMS, 
0xc435ca0, 0xa17a, 0x11d0, 0x88, 0xe0, 0x0, 0x0, 0xf8, 0x4, 0x1, 0xd1);

// {565910F0-E7F8-11d0-A4EE-00A0C90565FB}
DEFINE_GUID(IID_FMSYSTEM, 
0x565910f0, 0xe7f8, 0x11d0, 0xa4, 0xee, 0x0, 0xa0, 0xc9, 0x5, 0x65, 0xfb);

// {945AEDA0-F410-11d0-88F5-0000F80401D1}
DEFINE_GUID(CLSID_FMCOLLECTION, 
0x945aeda0, 0xf410, 0x11d0, 0x88, 0xf5, 0x0, 0x0, 0xf8, 0x4, 0x1, 0xd1);
// {945AEDA1-F410-11d0-88F5-0000F80401D1}
DEFINE_GUID(IID_FMCOLLECTION, 
0x945aeda1, 0xf410, 0x11d0, 0x88, 0xf5, 0x0, 0x0, 0xf8, 0x4, 0x1, 0xd1);


// {C9CA6540-FEEF-11d0-A4EE-00A0C90565FB}
DEFINE_GUID(CLSID_FMSTORAGE, 
0xc9ca6540, 0xfeef, 0x11d0, 0xa4, 0xee, 0x0, 0xa0, 0xc9, 0x5, 0x65, 0xfb);

// {C9CA6541-FEEF-11d0-A4EE-00A0C90565FB}
DEFINE_GUID(IID_FMSTORAGE, 
0xc9ca6541, 0xfeef, 0x11d0, 0xa4, 0xee, 0x0, 0xa0, 0xc9, 0x5, 0x65, 0xfb);

// {4943B42D-F5BF-11d1-8233-0000F87A587C}
DEFINE_GUID( IID_IASUSERNAVARROWS, 
0x4943b42d, 0xf5bf, 0x11d1, 0x82, 0x33, 0x0, 0x0, 0xf8, 0x7a, 0x58, 0x7c);

// {E80BCC9F-F645-11d1-8233-0000F87A587C}
DEFINE_GUID( IID_IASTITLEBAR, 
0xe80bcc9f, 0xf645, 0x11d1, 0x82, 0x33, 0x0, 0x0, 0xf8, 0x7a, 0x58, 0x7c);


//--------------------------------------------------------------------------------------------
//
// Constants and flags
//
//--------------------------------------------------------------------------------------------

// Applications using the Forms Manager May utilize the WM_ACTIVATEAPP which will be sent
// on the Application Message Sink


#ifndef WM_ACTIVATEAPP
#define WM_ACTIVATEAPP  0x001c
#endif

// A WM_SPCH_RECOG message that is passed down the message sink chain and not handled by the
// any message sink generates a WM_COMMAND on the foreground form event sink with:
//
// uMsg == WM_COMMAND
// LOWORD( wParam) == FormId, HIWORD(wParam) == SPCHN_CMDRECOG
// lParam == Speech command Id.

#define SPCHN_CMDRECOG  0xe00e

// A WM_SPCH_FEEDBANCK message that is passed down the message sink chain and not handled by the
// any message sink generates a WM_COMMAND on the foreground form event sink with:
//
// uMsg == WM_COMMAND
// HIWORD(wParam) == SPCHN_FEEDBACK
// LOWORD(wParam) - Current Feedback level
// HIWORD(lParam) - Speech Feedback initiation reason - See  SFR_???? values in apcspch.h
// LOWORD(lParam) - Reason specific information 

#define SPCHN_FEEDBACK  0xe00f

// On APC the WM_ACTIVATEAPP wParam has a flag indicating that the App was activated by speech

#define ACTIVATEAPP_FLG_BYSPEECH    0x00010000

#ifndef SC_SCREENSAVE
#define SC_SCREENSAVE   0xF140
#endif

// Base control property flags. Used to provide quick acess to a control's standard boolean
// properties
//
#define ASFC_CTRL_VISIBLE		0x0001			// bit 0 control is visible
#define ASFC_CTRL_ENABLE		0x0002			// bit 1 control is enabled
#define ASFC_CTRL_OPAQUE		0x0004			// bit 2 control is opaque
#define ASFC_CTRL_BORDER		0x0008			// bit 3 control has a border
#define ASFC_CTRL_DEFERDRAW     0x0010          // bit 4 control defers drawing until this bit is cleared

// [RO]
#define ASFC_CTRL_HASUI         0x0020          // bit 5 control has UI - [RO]
#define ASFC_CTRL_TABSTOP		0x0040			// bit 6 control is a tab stop

// Speech
#define ASFC_CTRL_SPEECHENABLED 0x0080          // bit 7 control is speech enabled



//
// Controls and forms can have IDs. The following IDs are reserved
//
#define ASFC_ID_NONE 0x0000
#define ASFC_ID_MIN  0x0000
#define ASFC_ID_MAX  0x7fff

//	APC Defines for message boxes

//    Message box flags
#define	FMMB_FLG_BEEP		    0x0001
#define FMMB_FLG_TTS		    0x0002
#define FMMB_FLG_HTML           0x0004
#define FMMB_FLG_FILENAME       0x0008
#define FMMB_FLG_AUTODISMISS    0x0010
#define FMMB_FLG_OUTOFSTORAGE   0x0020

// APC defines for SetAppAlertState AlertAction

#define FMAA_ACTION_CLEAR            0
#define FMAA_ACTION_RAISE_VALUE      1
#define FMAA_ACTION_CLEAR_MASK       2
#define FMAA_ACTION_RAISE_MASK       3

//    Message box icons (specific to APC)
// must be in range 0x50 - 0xf0
#define MB_APC_ICONCHECK     0x00000050L

//    Message box buttons (specific to APC)
// must be in range 0x6 - 0xf
#define MB_NOBUTTONS         0x00000006L

// APC Defines for help
#define APCHELP_INDEX  1
#define APCHELP_TOPIC  2

// Flags for MoveAppToForeground

#define ASFC_APPSTYLEFLG_POPUP      0x0001

//--------------------------------------------------------------------------------------------
//
// Conatants
//
//--------------------------------------------------------------------------------------------
#define	ASFC_DISPLAY_MAXWIDTH				256
#define	ASFC_DISPLAY_MAXHEIGHT				64

//--------------------------------------------------------------------------------------------
//
// Macros for examining the the Form Context handle returned from 
// IFmManage - GetFormsContextHandle. 
// The Macros should be used rather than testing the values explicitly.
//
//--------------------------------------------------------------------------------------------

#define	FC_WINDOWSDISPLAY	0xfffffffe
#define	FC_MAINFACEPLATE	0xfffffffd

#define	IS_FCH_DRIVERDISPLAY(hFC)		(hFC == FC_WINDOWSDISPLAY || \
												hFC == FC_MAINFACEPLATE)

#define	IS_FCH_MASTERFACEPLATE(hFC)		(hFC == FC_MAINFACEPLATE)										

#define IS_FCH_SECONDARYDISPLAY(hFC) 	(!IS_FCH_DRIVERDISPLAY(hFC))

#define	IS_FCH_WINDOWDISPLAY( hFC) 		( hFC == FC_WINDOWSDISPLAY)	

//--------------------------------------------------------------------------------------------
//
// Errors
//
//--------------------------------------------------------------------------------------------
#define ASFC_ERROR(e)	MAKE_SCODE(SEVERITY_ERROR, FACILITY_ITF, 0x6000 + e)

#define ASFC_E_SYSTEM           ASFC_ERROR(0x0001)      // system error
#define ASFC_E_VERSION          ASFC_ERROR(0x0002)      // wrong version of asfc.dll
#define ASFC_E_BADID            ASFC_ERROR(0x0003)      // bad control/form id provided to a method  
#define ASFC_E_IDEXISTS         ASFC_ERROR(0x0004)      // id already exists
#define ASFC_E_WRONGTHREAD      ASFC_ERROR(0x0005)      // Method is only available to owner thread

#define ASFC_E_CTRL_CLOSED      ASFC_ERROR(0x0010)      // control has been closed. 
#define ASFC_E_CTRL_NOTINIT     ASFC_ERROR(0x0011)      // control has not been initialized
#define ASFC_E_CTRL_NOTSTARTED  ASFC_ERROR(0x0012)      // control has not been started
#define ASFC_E_CTRL_NOFOCUS     ASFC_ERROR(0x0013)      // no current focus
#define ASFC_E_CTRL_NOSUCH      ASFC_ERROR(0x0014)      // not a control we know about
#define ASFC_E_CTRL_INVALID     ASFC_ERROR(0x0015)      // control does not support all interfaces
#define ASFC_E_CTRL_NOPARENT    ASFC_ERROR(0x0016)      // control does not have a form parent

#define ASFC_E_FORM_EMPTY       ASFC_ERROR(0x0040)      // no controls on this form
#define ASFC_E_FORM_BADDC       ASFC_ERROR(0x00041)     // an HDC that was recognized

#define ASFC_E_NOMENU           ASFC_ERROR(0x0060)

#define ASFC_E_FM_NOSUCH         ASFC_ERROR(0x0070);    // no such forms manager
#define ASFC_E_FM_NOFMS         ASFC_ERROR(0x0071);     // no forms managers allocated

//--------------------------------------------------------------------------------------------
//
// APIs
//
//--------------------------------------------------------------------------------------------
STDAPI InitASFormsManager(void);
STDAPI UnInitASFormsManager(void);

//--------------------------------------------------------------------------------------------
//
// Interfaces
//
//--------------------------------------------------------------------------------------------
//
// Interface for drawing
//
#undef	INTERFACE
#define	INTERFACE

DECLARE_INTERFACE_(IFMDraw, IDispatch)
	{
	STDMETHOD(GetDC) (THIS_ OLE_HANDLE *phDC) PURE;
	STDMETHOD(Commit) (THIS_ OLE_HANDLE hDC) PURE;
	STDMETHOD(ClipAndCommit) (THIS_ OLE_HANDLE hDC, OLE_HANDLE hrgnClip) PURE;
	STDMETHOD(ReleaseDC) (THIS_ OLE_HANDLE hDC) PURE;
    STDMETHOD(GetDeviceCaps) (THIS_ long index, long *plValue) PURE;
	};

//
// Event firing
//
#undef	INTERFACE
#define	INTERFACE

DECLARE_INTERFACE_(IASEventSink, IDispatch)
	{
	STDMETHOD(ReceiveMsg) (THIS_ long uMsg, long wParam, long lParam) PURE;
	};


//
// Class Msg Sink
//
#undef	INTERFACE
#define	INTERFACE

DECLARE_INTERFACE_(IASClassMsgSink, IDispatch)
	{
	//
	// Lifetime
	//
	STDMETHOD(HandleStart) (THIS_ IDispatch *pdispControl) PURE;
	STDMETHOD(HandleClose) (THIS_ IDispatch *pdispControl) PURE;
	//
	// Messages
	//
	STDMETHOD(HandleDraw) (THIS_ IDispatch *pdispControl, OLE_HANDLE hDC) PURE;
	STDMETHOD(HandleMessage) (THIS_ IDispatch *pdispControl, long uMsg, long wParam, long lParam) PURE;
	STDMETHOD(HandleKeyPress) (THIS_ IDispatch *pdispControl, long lKeyPress) PURE;
	//
	// Focus
	//
	STDMETHOD(HandleGotFocus) (THIS_ IDispatch *pdispControl) PURE;
	STDMETHOD(HandleLostFocus) (THIS_ IDispatch *pdispControl) PURE;
	};

//
// All AutoPC Simple controls MUST implement this interface
//
#undef	INTERFACE
#define	INTERFACE

DECLARE_INTERFACE_(IASControl, IDispatch)
	{
	//
	// Lifetime
	//
	STDMETHOD(Init) (THIS_ short wID, IDispatch *pdispParent, IDispatch *pdispEventSink) PURE;
    STDMETHOD(Start) (THIS) PURE;
	STDMETHOD(Close) (THIS) PURE;
    STDMETHOD(IsStarted) (THIS) PURE;
	//
	// Messages
	//
	STDMETHOD(Draw) (THIS_ OLE_HANDLE hDC) PURE;
	STDMETHOD(Redraw) (THIS) PURE;
	STDMETHOD(ReceiveMsg) (THIS_ long uMsg, long wParam, long lParam) PURE;
	STDMETHOD(KeyPress) (THIS_ long lKeyPress) PURE;
	//
	// Focus
	//
	STDMETHOD(GotFocus) (THIS) PURE;
	STDMETHOD(LostFocus) (THIS) PURE;
    //
    // Bounds
    //
	STDMETHOD(GetBounds) (THIS_ long *plLeft, long *plTop, long *plWidth, long *plHeight) PURE;
	STDMETHOD(SetBounds) (THIS_ long lLeft, long lTop, long lWidth, long lHeight) PURE;
    //
    // Hit Testing
    //
    STDMETHOD(HitTest) (THIS_ long lx, long ly) PURE;
	//
	// Other methods
	//
	STDMETHOD(GetCommonBoolProperties) (THIS_ short *pwProps) PURE;
	STDMETHOD(PutCommonBoolProperties) (THIS_ short wProps) PURE;
	//
	// Properties
	//
    //
    // Identification
    //
	STDMETHOD(get_ID) (THIS_ short *pwID) PURE;
    STDMETHOD(get_CLSID) (THIS_ BSTR *pbstrCLSID) PURE;
	//
	// Pointers
	//
	STDMETHOD(get_ClassMsgSink) (THIS_ IDispatch **ppdispSink) PURE;
	STDMETHOD(put_ClassMsgSink) (THIS_ IDispatch *pdispSink) PURE;	
	STDMETHOD(get_Parent) (THIS_ IDispatch **ppdispParent) PURE;
	STDMETHOD(put_Parent) (THIS_ IDispatch *pdispParent) PURE;	
	STDMETHOD(get_EventSink) (THIS_ IDispatch **ppdispSink) PURE;
	STDMETHOD(put_EventSink) (THIS_ IDispatch *pdispSink) PURE;	
	STDMETHOD(get_Delegate) (THIS_ IDispatch **ppdispDelegate) PURE;
	STDMETHOD(put_Delegate) (THIS_ IDispatch *pdispDelegate) PURE;	
	//
	// Boolean
	//
	STDMETHOD(get_Visible) (THIS_ BOOL *pfVisible) PURE;
	STDMETHOD(put_Visible) (THIS_ BOOL fVisible) PURE;
	STDMETHOD(get_Enable) (THIS_ BOOL *pfEnable) PURE;
	STDMETHOD(put_Enable) (THIS_ BOOL fEnable) PURE;
	STDMETHOD(get_Opaque) (THIS_ BOOL *pfOpaque) PURE;
	STDMETHOD(put_Opaque) (THIS_ BOOL fOpaque) PURE;
	STDMETHOD(get_Border) (THIS_ BOOL *pfBorder) PURE;
	STDMETHOD(put_Border) (THIS_ BOOL fBorder) PURE;
    STDMETHOD(get_DeferDraw) (THIS_ BOOL *pfDeferDraw) PURE;
    STDMETHOD(put_DeferDraw) (THIS_ BOOL fDeferDraw) PURE;

	STDMETHOD(get_TabStop) (THIS_ BOOL *pfTabStop) PURE; // RO
   	STDMETHOD(get_HasUI) (THIS_ BOOL *pfHasUI) PURE;     // RO
	//
	// Fonts and Colors
	//
    STDMETHOD(put_Color) (THIS_ int nColorIndex, OLE_COLOR clr) PURE;
    STDMETHOD(get_Color) (THIS_ int nColorIndex, OLE_COLOR* pclr) PURE;
	STDMETHOD(get_ForeColor) (THIS_ OLE_COLOR *pclr) PURE;
	STDMETHOD(put_ForeColor) (THIS_ OLE_COLOR clr) PURE;
	STDMETHOD(get_BackColor) (THIS_ OLE_COLOR *pclr) PURE;
	STDMETHOD(put_BackColor) (THIS_ OLE_COLOR clr) PURE;
    STDMETHOD(get_Font) (THIS_ IFontDisp **ppFontDisp) PURE;
    STDMETHOD(put_Font) (THIS_ IFontDisp *pFontDisp) PURE;
    STDMETHOD(get_BackgroundBrush) (THIS_ OLE_HANDLE *phBrush) PURE;
    STDMETHOD(put_BackgroundBrush) (THIS_ OLE_HANDLE hBrush) PURE;
	//
	// Dimensions
	//
	STDMETHOD(get_Left) (THIS_ long *px) PURE;
	STDMETHOD(put_Left) (THIS_ long x) PURE;
	STDMETHOD(get_Width) (THIS_ long *pdx) PURE;
	STDMETHOD(put_Width) (THIS_ long dx) PURE;
	STDMETHOD(get_Top) (THIS_ long *py) PURE;
	STDMETHOD(put_Top) (THIS_ long y) PURE;
	STDMETHOD(get_Height) (THIS_ long *pdy) PURE;
	STDMETHOD(put_Height) (THIS_ long dy) PURE;
	//
	// Strings
	//
	STDMETHOD(get_Caption) (THIS_ BSTR *pbstrCaption) PURE;
	STDMETHOD(put_Caption) (THIS_ BSTR bstrCaption) PURE;
    // 
    // Others
    //
	STDMETHOD(get_UserData) (THIS_ long *plData) PURE;
	STDMETHOD(put_UserData) (THIS_ long lData) PURE;	

    // Natural Size,  the size that a control would like to be
    STDMETHOD(get_NaturalSize) (THIS_ long *plWidth, long *plHeight) PURE;

    // speech feedback
    STDMETHOD(Speak)(THIS_ DWORD dwSpeechContext, DWORD dwMode, DWORD dwReserved )  PURE;
	};

#undef	INTERFACE
#define	INTERFACE

// Titlebar interface
DECLARE_INTERFACE_(IASTitlebar, IASControl)
{
    STDMETHOD(get_SubCaption) (THIS_ BSTR *pbstrSubCaption) PURE;
    STDMETHOD(put_SubCaption) (THIS_ BSTR bstrSubCaption) PURE;
    
    STDMETHOD(get_Icon)(THIS_ OLE_HANDLE *phIcon) PURE;
    STDMETHOD(put_Icon)(THIS_ OLE_HANDLE hIcon) PURE;
    
    STDMETHOD(put_StatusImageList)(THIS_ OLE_HANDLE hbmImage, OLE_HANDLE hbmImageMask, long cxImage, long cyImage) PURE;
    STDMETHOD(get_StatusImageList)(THIS_ OLE_HANDLE *phbmImage, OLE_HANDLE *phbmImageMask, long *pcxImage, long *pcyImage) PURE;
    
    STDMETHOD(put_StatusFlags) (THIS_ long lStatusFlags) PURE;
    STDMETHOD(get_StatusFlags) (THIS_ long *plStatusFlags) PURE;

    STDMETHOD(put_MaxTitleWidth) (THIS_ long lMaxTitleWidth) PURE;
    STDMETHOD(get_MaxTitleWidth) (THIS_ long *plMaxTitleWidth) PURE;
};



#undef	INTERFACE
#define	INTERFACE

// Navigation Arrows interface
DECLARE_INTERFACE_(IASUserNavArrows, IASControl)
{
    STDMETHOD(get_NavState) (THIS_ long *plNavState) PURE;
    STDMETHOD(put_NavState) (THIS_ long lNavState) PURE;
    STDMETHOD(QueryFormForNavState)( THIS) PURE;
};	



#undef	INTERFACE
#define	INTERFACE

// Query Key Usage interface
DECLARE_INTERFACE_(IQueryKeyUsage, IUnknown)
{
    STDMETHOD(FlagKeysUsed) (THIS_ long lKeysUsed, long lKeysEaten) PURE;
};	



#undef	INTERFACE
#define	INTERFACE

//
// AutoPC Simple Forms must implement this interface
// A Form is ALSO a control and inherits from IASControl
//
DECLARE_INTERFACE_(IASForm, IASControl)
	{
    // Unitialize
	STDMETHOD(Uninitialize) (THIS) PURE;
	//
	// Add, remove, count controls
	//
	STDMETHOD(get_Count) (THIS_ long *pcItems) PURE;
	STDMETHOD(Item) (THIS_ VARIANT index, IDispatch **ppdisp) PURE;
    STDMETHOD(ItemFromID) (THIS_ short wID, IDispatch **ppdisp) PURE;

	STDMETHOD(Add) (THIS_ IDispatch *pdispControl, short wID) PURE;
	STDMETHOD(Remove) (THIS_ IDispatch *pdispControl) PURE;
    STDMETHOD(RemoveAtIndex) (THIS_ long index) PURE;
    STDMETHOD(RemoveByID) (THIS_ short wID) PURE;
	STDMETHOD(RemoveAll) (THIS) PURE;

    STDMETHOD(IsControlOnForm) (THIS_ IDispatch *pdispControl) PURE;
	//
	// Draw everything that is in the update region
	//
	STDMETHOD(Update) (THIS) PURE;
	STDMETHOD(GetIFMDraw) (THIS_ IDispatch **ppdispFMDraw, long lxLeft, long lyTop, long lxWidth, long lyHeight) PURE;

    // Speech Initialization paramenters required by Ctrls

    STDMETHOD(GetSpeechInitInfo) (THIS_ OLE_HANDLE * phWnd, long * pThreadId) PURE;    

	//
	// Invalidation. Invalidate the given area in the form
	//
	STDMETHOD(Invalidate) (THIS_ long lxLeft, long lyTop, long lxWidth, long lyHeight) PURE;
    STDMETHOD(InvalidateAll) (THIS) PURE;
	//
	// Change focus
	//
    STDMETHOD(GetFocus) (THIS_ IDispatch **ppdispControl) PURE;
    STDMETHOD(SetFocus) (THIS_ IDispatch *pdispControl) PURE;
	STDMETHOD(SetFocusNext) (THIS) PURE;
	STDMETHOD(SetFocusPrev) (THIS) PURE;
    STDMETHOD(SetZOrder) (THIS_ IDispatch *pdispControl, IDispatch *pdispControlAfter) PURE;
    //
    // Timers
    //
    STDMETHOD(SetTimer) (THIS_ IDispatch *pdispControl, UINT dMilliSecs, long *pTimerID) PURE;
    STDMETHOD(KillTimer) (THIS_ long idTimer) PURE;
    //
    // Voice Menu
    //
    STDMETHOD(get_VoiceMenu) (THIS_ IUnknown **ppUnknownVoiceMenu) PURE;
	STDMETHOD(put_VoiceMenu) (THIS_ IUnknown *pUnknownVoiceMenu) PURE;

	//
	// Form specific properties
	//

    STDMETHOD(get_WaitStatus) (THIS_ BOOL *pfWaitStatus) PURE;
    STDMETHOD(put_WaitStatus) (THIS_ BOOL fWaitStatus) PURE;	

    STDMETHOD(get_IconTrayVisible) (THIS_ BOOL *pfVisible) PURE;
    STDMETHOD(put_IconTrayVisible) (THIS_ BOOL fVisible) PURE;
    
	//
	// Speech
	//
	STDMETHOD(get_Speech)(THIS_ IAPCSpeech** ppSpeech) PURE;

    // User Navigation Arrows Control
    STDMETHOD(get_NavArrows)(THIS_ IASUserNavArrows** ppNavArrows) PURE;
    
    // Title Bar Control
    STDMETHOD(get_Titlebar)(THIS_ IASTitlebar** ppTitlebar) PURE;

    // context sensitive help
    STDMETHOD(put_HelpContext)(THIS_ BSTR bstrHelpFile, BSTR bstrHelpTopic) PURE;    
    STDMETHOD(get_HelpContext)(THIS_ BSTR *pbstrHelpFile, BSTR *pbstrHelpTopic) PURE;    
	};

// The Form Icon Tray interface
//
DECLARE_INTERFACE_(IASIconTray, IDispatch)
    {
	STDMETHOD(GetBounds) (THIS_ long *plLeft, long *plTop, long *plWidth, long *plHeight) PURE;
	STDMETHOD(SetBounds) (THIS_ long lLeft, long lTop, long lWidth, long lHeight) PURE;
	STDMETHOD(get_Count) (THIS_ long *pcItems) PURE;
    STDMETHOD(Add) (THIS_ OLE_HANDLE hIcon, short wID) PURE;
    STDMETHOD(InsertAt) (THIS_ long index, OLE_HANDLE hIcon, short wID) PURE;
    STDMETHOD(RemoveAtIndex) (THIS_ long index) PURE;
    STDMETHOD(RemoveByID) (THIS_ short wID) PURE;       
    };	


//
// A collection of Active ASForms
//
#undef  INTERFACE
#define INTERFACE

DECLARE_INTERFACE_(IASActiveForms, IDispatch)
    {
	//
	// Collection methods
	//
	STDMETHOD(get_Count) (THIS_ long *pcItems) PURE;
	STDMETHOD(Item) (THIS_ VARIANT index, IDispatch **ppdisp) PURE;
    STDMETHOD(ItemFromID) (THIS_ short wID, IDispatch **ppdisp) PURE;
	//
	// Change focus (which form in the collection has focus)
	//
    STDMETHOD(GetFocus) (THIS_ IDispatch **ppdispForm) PURE;
    STDMETHOD(SetFocus) (THIS_ IDispatch *pdispForm) PURE;
    };

//
// The Forms Manager Manage interface
//
#undef  INTERFACE
#define INTERFACE

DECLARE_INTERFACE_(IfmManage, IDispatch)
    {
    //
    // Start or Stop Forms
    //
    STDMETHOD(Start) (THIS_ IDispatch *pdispForm) PURE;
	STDMETHOD(Stop) (THIS_ IDispatch *pdispForm) PURE;
    STDMETHOD(StopAll) (THIS) PURE;
    //
    // Focus
    //
    STDMETHOD(MoveToForeground) ( THIS_ BOOL fThis, LONG * pZOrder) PURE;
    STDMETHOD(RestoreZOrder) (THIS_ LONG ZOrder) PURE;
    STDMETHOD (MoveAppToForeground)( THIS_ LONG ProcId, LONG * pZOrder, LONG Flags) PURE;
    STDMETHOD (RestoreAppZOrder)( THIS_ LONG ZOrder) PURE;
	//
    // Management Interfaces
    //
	STDMETHOD (GetFormsContextHandle)( THIS_ OLE_HANDLE * phFC) PURE;
    STDMETHOD (RegisterStartedApplication)( THIS_ OLE_HANDLE hFC, BSTR bstrAppName, LONG AppMsgID, LONG Flags) PURE;
    STDMETHOD (DeregisterStartedApplication)( THIS_ OLE_HANDLE hFC, BSTR bstrAppName) PURE;
          
    STDMETHOD (SetAppAlertState)( THIS_ OLE_HANDLE hFC, BOOL fCurrentUser, BSTR bstrAppName, 
                                  BSTR bstrAlertName, LONG AlertAction, LONG AlertVal) PURE;
    STDMETHOD (GetAppAlertState)( THIS_ OLE_HANDLE hFC, BOOL fCurrentUser, BSTR bstrAppName, 
                                  BSTR bstrAlertName, BOOL * fAlert, LONG * pAlertVal) PURE;
	// Load Form from RC file
	STDMETHOD(LoadFormResource) (THIS_ OLE_HANDLE,LONG wRsrcID,IDispatch **ppForm,IDispatch *pDispSink) PURE;
	// Load Menu from RC file
	STDMETHOD(LoadMenuResource) (THIS_ OLE_HANDLE,LONG wRsrcID,IDispatch **ppMenu) PURE;
    
    //
	// Register & query Msg & event sinks
    //
	STDMETHOD(get_Parent) (THIS_ IDispatch **ppdispParent) PURE;
	STDMETHOD(get_ClassMsgSink) (THIS_ IDispatch **ppdispSink) PURE;
	STDMETHOD(put_ClassMsgSink) (THIS_ IDispatch *pdispSink) PURE;	
	STDMETHOD(get_EventSink) (THIS_ IDispatch **ppdispSink) PURE;
	STDMETHOD(put_EventSink) (THIS_ IDispatch *pdispSink) PURE;	

	STDMETHOD(PostMsg)(THIS_ long uMsg, long wParam, long lParam) PURE;
	STDMETHOD(SendMsg)(THIS_ long uMsg, long wParam, long lParam) PURE;
	
	STDMETHOD(PostMessageToApp)(THIS_ long uMsg, long wParam, long lParam) PURE;
    STDMETHOD(CloseAppByName)(THIS_ BSTR bstrAppName, BOOL fTerminate) PURE;

    // App Data
    STDMETHOD(get_AppName) (THIS_ BSTR *pbstrAppName) PURE;
    STDMETHOD(put_AppName) (THIS_ BSTR bstrAppName) PURE;
    
    STDMETHOD(get_AppSmallIcon) (THIS_ OLE_HANDLE *phSmallIcon) PURE;
    STDMETHOD(put_AppSmallIcon) (THIS_ OLE_HANDLE hSmallIcon) PURE;

    // Application global help file
    STDMETHOD(put_HelpContext)(THIS_ BSTR bstrHelpFile, BSTR bstrHelpTopic) PURE;    
    STDMETHOD(get_HelpContext)(THIS_ BSTR *pbstrHelpFile, BSTR *pbstrHelpTopic) PURE;    
    
    //
    // Menus
    //
    STDMETHOD(put_Menu) (THIS_ IDispatch *pdispMenu, short wID) PURE;
    STDMETHOD(get_Menu) (THIS_ IDispatch **ppdispMenu) PURE;
    
    STDMETHOD(get_MenuVisible) (THIS_ BOOL *pfVisible) PURE;
    STDMETHOD(put_MenuVisible) (THIS_ BOOL fVisible) PURE;

    STDMETHOD(get_MenuTitlebar) (THIS_ IASTitlebar **ppTitlebar) PURE;
    
	//
	// MessageBox
	//
	STDMETHOD(fmMessageBox) (THIS_ BSTR bstrMsg, BSTR bstrCaption, LONG uType, LONG Flags, LONG * pRes) PURE;
	STDMETHOD(fmStopMessageBox) (THIS) PURE;
	//
	// Help
	//
	STDMETHOD(fmStartHelp) (THIS_ BSTR bstrFileName, DWORD dwFlags=APCHELP_INDEX, DWORD dwTopicID=0) PURE;
	STDMETHOD(fmStopHelp) (THIS) PURE;

	//
	// Speech
	//
	STDMETHOD(get_Speech)(THIS_ IAPCSpeech** ppSpeech) PURE;
	//STDMETHOD(put_Speech)(THIS_ IAPCSpeech* pSpeech) PURE;

    // Login

    STDMETHOD(fmVerifyLoginState)(THIS_ BSTR bstrTitle, BOOL fDoLogin, BOOL fKeepFocusOnFail, BOOL *pfLoggedIn) PURE;
	
	};


//
// The Forms Manager Information interface
//
DECLARE_INTERFACE_(IfmSystem, IDispatch)
    {
    STDMETHOD(GetFormDisplayCaps) (THIS_ OLE_HANDLE hFC, LONG nIndex, LONG * pRetInfo) PURE;
    STDMETHOD(CreateFMCompatibleBitmap) (THIS_ OLE_HANDLE hFC, OLE_HANDLE *phBmp, LONG width, LONG  height) PURE;
	STDMETHOD(GetFMSystemFont) (THIS_ OLE_HANDLE hFC, BOOL fSmall, IDispatch **ppdispFont) PURE;    
	STDMETHOD(CreateFMCompatibleDC) (THIS_ OLE_HANDLE hFC, OLE_HANDLE *phDC) PURE;
    };

//
// A Collection of Forms Managers
// 
DECLARE_INTERFACE_(IfmCollection, IDispatch)
    {
	STDMETHOD(get_Count) (THIS_ long *pcItems) PURE;
	STDMETHOD(Item) (THIS_ VARIANT index, IDispatch **ppdisp) PURE;
	//
	// Change focus (which forms manager in the collection has focus)
	//
    STDMETHOD(GetFocus) (THIS_ IDispatch **ppdispfmManage) PURE;
    STDMETHOD(SetFocus) (THIS_ IDispatch *pdispfmManage) PURE;
    };

//
// The Forms Managers Storage interface
// 
DECLARE_INTERFACE_(IfmStorage, IDispatch)
    {
	STDMETHOD(LoadForm) (THIS_ BSTR, IDispatch **ppdisp, IDispatch *pdisp) PURE;
	STDMETHOD(StoreForm) (THIS_ BSTR, IDispatch *ppdisp, BOOL *) PURE;
	STDMETHOD(DeleteForm) (THIS_ BSTR) PURE;


    };

#endif

