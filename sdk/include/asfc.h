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

/**
 * This message is posted by a NavArrow control to determine the keys that the sink for an
 * application or a form can process.
 *
 * @param wParam Unused.
 * @param lParam Contains a pointer to an IQueryKeyUsage interface.
 */
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
/**
 * This function initializes a Forms Manager.
 *
 * @return Returns the appropriate HRESULT.
 *
 * Call this function prior to creating any forms or Forms Managers.
 */
STDAPI InitASFormsManager(void);
/**
 * This function uninitializes a Forms Manager.
 *
 * @return Returns the appropriate HRESULT.
 *
 * Call this function after objects are released and prior to exiting the application.
 */
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

#if defined(__cplusplus) && !defined(CINTERFACE)
/**
 * This interface provides indirect access to the screen device context (DC).
 *
 * The IFMDraw interface extends IDispatch. It is used by controls and forms to manage screen
 * display when simply invalidating and redrawing regions is not sufficient.
 *
 * A form receives a pointer to an IFMDraw interface when the form is created. A control must
 * request the pointer from its form. The interface provides the control with a device context (DC)
 * that the control can then use to draw to the system's offscreen bitmap. When drawing is complete,
 * one of two methods is then used to blit the bitmap to the screen.
 *
 * Drawing to the screen only takes place if a control's form has focus. If not, the control is not
 * updated. The drawing process proceeds normally-no errors are generated-but the screen is not
 * repainted.
 */
struct IFMDraw : public IDispatch
#else
DECLARE_INTERFACE_(IFMDraw, IDispatch)
#endif
	{
	/**
	 * This method gets a screen device context (DC).
	 *
	 * @param phDC Pointer to the handle to a screen DC.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * Every call to IFMDraw::GetDC must be matched by a call to IFMDraw::ReleaseDC.
	 */
	STDMETHOD(GetDC) (THIS_ OLE_HANDLE *phDC) PURE;
	/**
	 * This method blits the entire offscreen bitmap to the screen.
	 *
	 * @param hDC Handle to a device context (DC), as returned by IFMDraw::GetDC.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * The form must have focus for blitting to take place. If not, no errors are generated, but the
	 * image does not appear on the screen. This method fails if the DC passed to the method is not the
	 * one returned by a previous call to IFMDraw::GetDC. It also fails if the DC has been released by
	 * IFMDraw::ReleaseDC.
	 */
	STDMETHOD(Commit) (THIS_ OLE_HANDLE hDC) PURE;
	/**
	 * This method takes a clipping region and blits that portion of the offscreen bitmap to the screen.
	 *
	 * @param hDC Handle to the screen device context (DC), as returned by IFMDraw::GetDC.
	 * @param hRgnClip Handle to a clipping region.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * The form must have focus for blitting to take place. If not, no errors are generated, but the
	 * image does not appear on the screen. This method fails if the DC passed to the method is not the
	 * one returned by a previous call to IFMDraw::GetDC. It also fails if the DC has been released by
	 * IFMDraw::ReleaseDC.
	 */
	STDMETHOD(ClipAndCommit) (THIS_ OLE_HANDLE hDC, OLE_HANDLE hrgnClip) PURE;
	/**
	 * This method releases the device context (DC).
	 *
	 * @param hDC Handle to the DC to be released.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * This method fails if the DC is not one that was retrieved by a call to IFMDraw::GetDC. Every call
	 * to IFMDraw::GetDC must be matched by a call to IFMDraw::ReleaseDC.
	 */
	STDMETHOD(ReleaseDC) (THIS_ OLE_HANDLE hDC) PURE;
    /**
     * This method gets the capabilities of the screen device context (DC).
     *
     * @param index Specifies the index of the capability to return in plDeviceCap. It is one of the
     *   following values. - DRIVERVERSION: The device driver version. - HORZSIZE: Width of the physical
     *   screen, in millimeters. - VERTSIZE: Height of the physical screen, in millimeters. - HORZRES:
     *   Width of the screen, in pixels. - VERTRES: Height of the screen, in raster lines. - LOGPIXELSX:
     *   Number of pixels per logical inch along the width of the screen. If the device has multiple
     *   display monitors, this value is the same for all monitors. - LOGPIXELSY: Number of pixels per
     *   logical inch along the height of the screen. If the device has multiple display monitors, this
     *   value is the same for all monitors. - BITSPIXEL: Number of adjacent color bits for each pixel. -
     *   PLANES: Number of color planes. - NUMBRUSHES: Number of device-specific brushes. - NUMPENS:
     *   Number of device-specific pens. - NUMFONTS: Number of device-specific fonts. - NUMCOLORS: Number
     *   of entries in the color table for the device, if the device has a color depth of no more than 8
     *   bits per pixel. For devices with greater color depths, this method sets plDeviceCap equal to -1.
     *   - ASPECTX: Relative width of a device pixel used for line drawing. - ASPECTY: Relative height of
     *   a device pixel used for line drawing. - ASPECTXY: Diagonal width of the device pixel used for
     *   line drawing. - PDEVICESIZE: Reserved. - CLIPCAPS: Flag that indicates the clipping capabilities
     *   of the device. If the device can clip to a rectangle, this method sets plDeviceCap equal to 1.
     *   Otherwise, this method sets plDeviceCap equal to 0. - SIZEPALETTE: Number of entries in the
     *   system palette. This index is valid only if the device driver sets the RC_PALETTE bit in the
     *   RASTERCAPS index and is available only if the driver is compatible with Windows 3.1 or earlier. -
     *   NUMRESERVED: Number of reserved entries in the system palette. This index is valid only if the
     *   device driver sets the RC_PALETTE bit in the RASTERCAPS index and is available only if the driver
     *   is compatible with Windows 3.1 or earlier. - COLORRES: Actual color resolution of the device, in
     *   bits per pixel. This index is valid only if the device driver sets the RC_PALETTE bit in the
     *   RASTERCAPS index and is available only if the driver is compatible with Windows 3.1 or earlier. -
     *   RASTERCAPS: Value that indicates the raster capabilities of the device. The following table shows
     *   the possible values of plDeviceCap for this index. Value Description RC_BANDING Device requires
     *   banding support. RC_BITBLT Device is capable of transferring bitmaps. RC_BITMAP64 Device is
     *   capable of supporting bitmaps larger than 64K. RC_DI_BITMAP Device is capable of supporting the
     *   SetDIBits and GetDIBits functions. RC_DIBTODEV Device is capable of supporting the
     *   SetDIBitsToDevice function. RC_FLOODFILL Device is capable of performing flood fills.
     *   RC_GDI20_OUTPUT Device is capable of supporting features of Windows 3.1 or earlier. RC_PALETTE
     *   Device is palette-based. RC_SCALING Device is capable of scaling. RC_STRETCHBLT Device is capable
     *   of performing the StretchBlt function. RC_STRETCHDIB Device is capable of performing the
     *   StretchDIBits function. - CURVECAPS: Value that indicates the capabilities of the device for
     *   drawing curves. The following table shows the possible values of plDeviceCap for this index.
     *   Value Description CC_NONE Device does not support curves. CC_CHORD Device can draw chord arcs.
     *   CC_CIRCLES Device can draw circles. CC_ELLIPSES Device can draw ellipses. CC_INTERIORS Device can
     *   draw interiors. CC_PIE Device can draw pie wedges. CC_ROUNDRECT Device can draw rounded
     *   rectangles. CC_STYLED Device can draw styled borders. CC_WIDE Device can draw wide borders.
     *   CC_WIDESTYLED Device can draw borders that are wide and styled. - LINECAPS: Value that indicates
     *   the capabilities of the device for drawing lines. The following table shows the possible values
     *   of plDeviceCap for this index. Value Description LC_NONE Device does not support lines.
     *   LC_INTERIORS Device can draw interiors. LC_MARKER Device can draw a marker. LC_POLYLINE Device
     *   can draw a polyline. LC_POLYMARKER Device can draw multiple markers. LC_STYLED Device can draw
     *   styled lines. LC_WIDE Device can draw wide lines. LC_WIDESTYLED Device can draw lines that are
     *   wide and styled. - POLYGONALCAPS: Value that indicates the capabilities of the device for drawing
     *   polygons. The following table shows the possible values of plDeviceCap for this index. Value
     *   Description PC_NONE Device does not support polygons. PC_INTERIORS Device can draw interiors.
     *   PC_POLYGON Device can draw alternate-fill polygons. PC_RECTANGLE Device can draw rectangles.
     *   PC_SCANLINE Device can draw a single scanline. PC_STYLED Device can draw styled borders. PC_WIDE
     *   Device can draw wide borders. PC_WIDESTYLED Device can draw borders that are wide and styled.
     *   PC_WINDPOLYGON Device can draw winding-fill polygons. - TEXTCAPS: Value that indicates the text
     *   capabilities of the device. The following table shows the possible values of plDeviceCap for this
     *   index. Value Description TC_OP_CHARACTER Device is capable of character output precision.
     *   TC_OP_STROKE Device is capable of stroke output precision. TC_CP_STROKE Device is capable of
     *   stroke clip precision. TC_CR_90 Device is capable of 90-degree character rotation. TC_CR_ANY
     *   Device is capable of any character rotation. TC_SF_X_YINDEP Device can scale independently in the
     *   x- and y-directions. TC_SA_DOUBLE Device is capable of doubled character for scaling.
     *   TC_SA_INTEGER Device uses integer multiples only for character scaling. TC_SA_CONTIN Device uses
     *   any multiples for exact character scaling. TC_EA_DOUBLE Device can draw double-weight characters.
     *   TC_IA_ABLE Device can italicize. TC_UA_ABLE Device can underline. TC_SO_ABLE Device can draw
     *   strikeouts. TC_RA_ABLE Device can draw raster fonts. TC_VA_ABLE Device can draw vector fonts.
     *   TC_RESERVED Reserved; must be zero. TC_SCROLLBLT Device cannot scroll using a bit-block transfer.
     *   Note that this meaning may be the opposite of what you expect.
     * @param plDeviceCap Pointer to a long integer that receives the requested capability.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(GetDeviceCaps) (THIS_ long index, long *plValue) PURE;
	};

//
// Event firing
//
#undef	INTERFACE
#define	INTERFACE

#if defined(__cplusplus) && !defined(CINTERFACE)
/**
 * This optional interface provides a simple way for controls to fire events.
 *
 * The IASEventSink interface extends the IDispatch interface. If an application does not need to
 * receive events, this interface is unnecessary. To implement IASEventSink, create an object that
 * exposes the interface, and place a pointer to it in the IASControl EventSink property. If this
 * interface is not adequate, create a custom IConnectionPoint interface.
 */
struct IASEventSink : public IDispatch
#else
DECLARE_INTERFACE_(IASEventSink, IDispatch)
#endif
	{
	/**
	 * This method allows a control to receive a message when a message event is fired.
	 *
	 * @param uMsg Specifies the message to process.
	 * @param wParam Long integer that contains the wParam of the message.
	 * @param lParam Long integer that contains the lParam of the message.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 */
	STDMETHOD(ReceiveMsg) (THIS_ long uMsg, long wParam, long lParam) PURE;
	};


//
// Class Msg Sink
//
#undef	INTERFACE
#define	INTERFACE

#if defined(__cplusplus) && !defined(CINTERFACE)
/**
 * This interface provides methods used to subclass the messaging and drawing functions of
 * IASControl.
 *
 * The IASClassMsgSink interface extends the IDispatch interface.
 *
 * To use this sink, create an object that exposes the IASClassMsgSink interface and place a pointer
 * to it in the IASControl ClassMsgSink property. The control passes information on to the
 * appropriate IASClassMsgSink method for processing. To implement only a subset of the
 * IASClassMsgSink methods, have the remainder return S_FALSE. This indicates to the IASControl
 * method that no processing has taken place.
 */
struct IASClassMsgSink : public IDispatch
#else
DECLARE_INTERFACE_(IASClassMsgSink, IDispatch)
#endif
	{
	//
	// Lifetime
	//
	/**
	 * This method notifies the application that the control has started.
	 *
	 * @param pDispControl Pointer to the control to which this sink belongs.
	 *
	 * @return NOERROR indicates that the sink handled the message. S_FALSE indicates that the sink did
	 *   not handle the message. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * A control invokes this method when its own IASControl::Start method is invoked. A control can
	 * also use it if the control has already been started, and needs to make this sink its message
	 * sink.
	 */
	STDMETHOD(HandleStart) (THIS_ IDispatch *pdispControl) PURE;
	/**
	 * This method enables a control to notify its sink when a form closes the control.
	 *
	 * @param pdispControl Pointer to the control that is calling the method.
	 *
	 * @return NOERROR indicates that the sink handled the message to close the control. S_FALSE
	 *   indicates that the sink did not handle the message to close the control. If an error occurs, the
	 *   appropriate HRESULT value is returned.
	 *
	 * A control invokes this method when its own IASControl::Close method is invoked. This takes place
	 * when a form shuts down a control. Processing subsequently stops and any needed shutdown
	 * procedures are performed.
	 */
	STDMETHOD(HandleClose) (THIS_ IDispatch *pdispControl) PURE;
	//
	// Messages
	//
	/**
	 * This method enables a control to notify its sink when drawing takes place.
	 *
	 * @param pdispControl Pointer to the control that is calling the method.
	 * @param hDC Handle to a device context (DC).
	 *
	 * @return NOERROR indicates that the sink handled the message. S_FALSE indicates that the sink did
	 *   not handle the message. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * A control invokes this method when its own IASControl::Draw method is invoked.
	 */
	STDMETHOD(HandleDraw) (THIS_ IDispatch *pdispControl, OLE_HANDLE hDC) PURE;
	/**
	 * This method enables a control to notify its sink when a message is received.
	 *
	 * @param pdispControl Pointer to the control that is calling the method.
	 * @param uMsg Specifies the message to process.
	 * @param wParam Long integer that contains the wParam of the message.
	 * @param lParam Long integer that contains the lParam of the message.
	 *
	 * @return NOERROR indicates that the sink handled the message. S_FALSE indicates that the sink did
	 *   not handle the message. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * A control invokes this method when its own IASControl::ReceiveMsg method is invoked.
	 */
	STDMETHOD(HandleMessage) (THIS_ IDispatch *pdispControl, long uMsg, long wParam, long lParam) PURE;
	/**
	 * This method enables a control to notify its sink when a character key is pressed.
	 *
	 * @param pdispControl Pointer to the control that is calling the method.
	 * @param lKeyDown Long integer that contains the Unicode keycode.
	 *
	 * @return NOERROR indicates that the sink handled the message. S_FALSE indicates that the sink did
	 *   not handle the message. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * A control invokes this method when its own IASControl::KeyPress method is invoked.
	 *
	 * Pressing a key that does not map to a character, such as VK_LEFT, does not invoke this method.
	 */
	STDMETHOD(HandleKeyPress) (THIS_ IDispatch *pdispControl, long lKeyPress) PURE;
	//
	// Focus
	//
	/**
	 * This method enables a control to notify its sink when the control gains focus.
	 *
	 * @param pdispControl Pointer to the control that is calling the method.
	 *
	 * @return NOERROR indicates that the sink handled the message. S_FALSE indicates that the sink did
	 *   not handle the message. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * A control invokes this method when its own IASControl::GotFocus method is invoked.
	 */
	STDMETHOD(HandleGotFocus) (THIS_ IDispatch *pdispControl) PURE;
	/**
	 * This method enables a control to notify its sink when the control loses focus.
	 *
	 * @param pdispControl Pointer to the control that is calling the method.
	 *
	 * @return NOERROR indicates that the sink handled the message. S_FALSE indicates that the sink did
	 *   not handle the message. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * A control invokes this method when its own IASControl::LostFocus method is invoked.
	 */
	STDMETHOD(HandleLostFocus) (THIS_ IDispatch *pdispControl) PURE;
	};

//
// All AutoPC Simple controls MUST implement this interface
//
#undef	INTERFACE
#define	INTERFACE

#if defined(__cplusplus) && !defined(CINTERFACE)
/**
 * This interface provides methods that manage communication between a form and an individual
 * control.
 *
 * The IASControl interface extends the IDispatch interface. If an application subclasses this
 * interface by exposing an IASClassMsgSink interface, many of these methods subsequently invoke the
 * related IASClassMsgSink method. A pointer to the IASClassMsgSink interface is stored in the
 * control's ClassMsgSink property.
 *
 * Some IASClassMsgSink methods can have only a token implementation. They return S_FALSE,
 * indicating that no processing takes place. The IASControl method should be prepared to handle
 * processing in this event.
 */
struct IASControl : public IDispatch
#else
DECLARE_INTERFACE_(IASControl, IDispatch)
#endif
	{
	//
	// Lifetime
	//
	/**
	 * This method initializes a new control.
	 *
	 * @param wID Short integer that contains the identifier of the control.
	 * @param pdispParent Pointer to the object that owns the control.
	 * @param pdispEventSink Pointer to the default event sink for the control. Use NULL if the owner is
	 *   not to receive events.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * Following initialization, the control must be started with IASControl::Start before processing
	 * can start. An application does not call IASControl::Start explicitly. The parent form of the
	 * control calls IASControl::Start when the form starts, or the IASForm::Add method calls
	 * IASControl::Start internally when you add a control to a form you have already started.
	 */
	STDMETHOD(Init) (THIS_ short wID, IDispatch *pdispParent, IDispatch *pdispEventSink) PURE;
    /**
     * This method is called internally by the parent form of the control when the form starts.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     *
     * An application should not directly call this method. After a form initializes a control by
     * calling IASControl::Init, it invokes this method internally to start processing. A control should
     * not start processing until this method has been invoked. A form notifies a control to stop
     * processing with a call to IASControl::Close. If a message sink exists, the control forwards the
     * message to its IASClassMsgSink::Start method.
     */
    STDMETHOD(Start) (THIS) PURE;
	/**
	 * This method shuts down a control when it is removed from the form.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * A form invokes this method when it wishes to close a control. The control frees all resources and
	 * releases all external reference counts. You must call this method for any initialized form, even
	 * if you have not called IASControl::Start on the form
	 *
	 * If a message sink exists, this method invokes IASClassMsgSink::HandleClose.
	 */
	STDMETHOD(Close) (THIS) PURE;
    /**
     * This method checks to see if the control has been started.
     *
     * @return NOERROR indicates that the control has been started. S_FALSE indicates that the control
     *   has not been started.
     */
    STDMETHOD(IsStarted) (THIS) PURE;
	//
	// Messages
	//
	/**
	 * This method repaints the form.
	 *
	 * @param hDC Handle to a device context (DC) returned by a call to IFMDraw::GetDC.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * This method is usually invoked by the form when some portion of the form has been invalidated,
	 * and the screen needs to be repainted. When this method is invoked, it finishes any drawing
	 * necessary in the device context that the method receives. The method then returns control to the
	 * form, which handles the actual screen repainting.
	 *
	 * If a message sink exists, this method forwards the call to the IASClassMsgSink::Draw method.
	 */
	STDMETHOD(Draw) (THIS_ OLE_HANDLE hDC) PURE;
	/**
	 * This method redraws a control.
	 *
	 * @return NOERROR indicates success. S_FALSE indicates that the control did not handle the message.
	 *   If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * The IASControl::Redraw method is used to notify a form to redraw itself. It can do this by
	 * invoking one of its form's invalidation methods, or by requesting an IFMDraw interface pointer.
	 * IFMDraw enables IASControl::Redraw to handle repainting by itself.
	 */
	STDMETHOD(Redraw) (THIS) PURE;
	/**
	 * This method allows a control to receive messages.
	 *
	 * @param uMsg Specifies the message to process.
	 * @param wParam Long integer that contains the wParam of a message.
	 * @param lParam Long integer that contains the lParam of a message.
	 *
	 * @return NOERROR indicates success. S_FALSE indicates that the control did not handle the message.
	 *   If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * If a message sink exists, the control forwards the message to its IASEventSink::ReceiveMsg
	 * method. WM_CHAR messages are handled by IASControl::KeyPress.
	 */
	STDMETHOD(ReceiveMsg) (THIS_ long uMsg, long wParam, long lParam) PURE;
	/**
	 * This method handles WM_CHAR messages.
	 *
	 * @param lKeyDown Long integer that contains the Unicode keycode.
	 *
	 * @return NOERROR indicates that the control handled the message. S_FALSE indicates that the
	 *   control did not handle the message. If an error occurs, the appropriate HRESULT value is
	 *   returned.
	 *
	 * If a message sink exists, the control forwards the message to the IASClassMsgSink::KeyPress
	 * method.
	 */
	STDMETHOD(KeyPress) (THIS_ long lKeyPress) PURE;
	//
	// Focus
	//
	/**
	 * This method notifies a control that the control is gaining focus.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * If a message sink exists, the control forwards this call to the IASClassMsgSink::GotFocus method.
	 */
	STDMETHOD(GotFocus) (THIS) PURE;
	/**
	 * This method notifies a control that it is losing focus.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * If a message sink exists, the method forwards the message to its IASClassMsgSink::LostFocus
	 * method.
	 */
	STDMETHOD(LostFocus) (THIS) PURE;
    //
    // Bounds
    //
	/**
	 * This method retrieves the dimensions of a control.
	 *
	 * @param plxLeft Pointer to the long integer that contains the x-coordinate of the left edge of the
	 *   control.
	 * @param plyTop Pointer to the long integer that contains the y-coordinate of the top of the
	 *   control.
	 * @param pldxWidth Pointer to the long integer that contains the width of the control.
	 * @param pldyHeight Pointer to the long integer that contains the height of the control.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * If you implement this method, then you must implement IASControl::get_Height,
	 * IASControl::get_Top, IASControl::get_Width, and IASControl::get_Left.
	 */
	STDMETHOD(GetBounds) (THIS_ long *plLeft, long *plTop, long *plWidth, long *plHeight) PURE;
	/**
	 * This method sets the dimensions of a control.
	 *
	 * @param lxLeft Long integer that contains the x-coordinate of the left edge of the control.
	 * @param lyTop Long integer that contains the y-coordinate of the top of the control.
	 * @param ldxWidth Long integer that contains the width of the control.
	 * @param ldyHeight Long integer that contains the height of the control.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 */
	STDMETHOD(SetBounds) (THIS_ long lLeft, long lTop, long lWidth, long lHeight) PURE;
    //
    // Hit Testing
    //
    /**
     * This method tests whether coordinates fall within a control.
     *
     * @param lx Long integer that contains the x-coordinate.
     * @param ly Long integer that contains the y-coordinate.
     *
     * @return NOERROR indicates that the hit text succeeded. S_FALSE indicates that the hit test
     *   failed. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(HitTest) (THIS_ long lx, long ly) PURE;
	//
	// Other methods
	//
	/**
	 * This method returns the common Boolean properties.
	 *
	 * @param pwProps Pointer to a short integer that contains one or more of the following flags, which
	 *   indicate the status of the control's Boolean properties: - ASFC_CTRL_VISIBLE: Control is visible.
	 *   - ASFC_CTRL_ENABLE: Control is enabled. - ASFC_CTRL_OPAQUE: Control is opaque. -
	 *   ASFC_CTRL_BORDER: Control has a border. - ASFC_CTRL_DEFERDRAW: Control defers drawing until the
	 *   deferdraw bit is cleared. - ASFC_CTRL_HASUI: Control has a user interface. - ASFC_CTRL_TABSTOP:
	 *   Control is a tabstop. - ASFC_CTRL_SPEECHENABLED: Control is speech enabled.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 */
	STDMETHOD(GetCommonBoolProperties) (THIS_ short *pwProps) PURE;
	/**
	 * This method sets common Boolean properties.
	 *
	 * @param pwProps Pointer to a short integer that contains one of the following flags, which
	 *   indicate the status of a control's Boolean properties: - ASFC_CTRL_VISIBLE: Control is visible. -
	 *   ASFC_CTRL_ENABLE: Control is enabled. - ASFC_CTRL_OPAQUE: Control is opaque. - ASFC_CTRL_BORDER:
	 *   Control has a border. - ASFC_CTRL_DEFERDRAW: Control defers drawing until this bit is cleared. -
	 *   ASFC_CTRL_HASUI: Control has a user interface. - ASFC_CTRL_TABSTOP: Control is a tabstop. -
	 *   ASFC_CTRL_SPEECHENABLED: Control is speech enabled.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * This method combines the flags passed to the method in pwProps with property flags already set
	 * before the call to this method by using an OR operation.
	 */
	STDMETHOD(PutCommonBoolProperties) (THIS_ short wProps) PURE;
	//
	// Properties
	//
    //
    // Identification
    //
	/**
	 * This method retrieves the identifier of a control.
	 *
	 * @param pwID Pointer to the short integer that contains the identifier of the control.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * This method is required.
	 *
	 * An identifier is unique to a control, and does not change.
	 */
	STDMETHOD(get_ID) (THIS_ short *pwID) PURE;
    /**
     * This method gets the class identifier of the Auto PC simple form.
     *
     * @param pbstrCLSID Pointer to the Unicode string that contains the class identifier.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(get_CLSID) (THIS_ BSTR *pbstrCLSID) PURE;
	//
	// Pointers
	//
	/**
	 * This method gets a pointer to the message sink of a control.
	 *
	 * @param ppdispSink Pointer to the pointer to the control's IASClassMsgSink interface.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * This method must be implemented, but can return E_NOTIMPL.
	 */
	STDMETHOD(get_ClassMsgSink) (THIS_ IDispatch **ppdispSink) PURE;
	/**
	 * This method sets the message sink of a control.
	 *
	 * @param ppdispSink Pointer to the pointer to the control's IASClassMsgSink interface.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * This method must be implemented, but can return E_NOTIMPL.
	 */
	STDMETHOD(put_ClassMsgSink) (THIS_ IDispatch *pdispSink) PURE;	
	/**
	 * This method retrieves a pointer to the control's parent form.
	 *
	 * @param ppdispParent Pointer to the pointer to the control's parent.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * This method is required.
	 */
	STDMETHOD(get_Parent) (THIS_ IDispatch **ppdispParent) PURE;
	/**
	 * This method sets the parent of a control.
	 *
	 * @param pdispParent Pointer to the control's parent.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * An application should not call this method directly. This method is called internally when you
	 * associate a control with a form.
	 */
	STDMETHOD(put_Parent) (THIS_ IDispatch *pdispParent) PURE;	
	/**
	 * This method gets the event sink of a control.
	 *
	 * @param ppdispSink Pointer to the pointer that receives the control's IASCEventSink interface. If
	 *   the sink is not implemented, ppdispSink receives a null pointer.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * This method must be implemented, but can return E_NOTIMPL.
	 */
	STDMETHOD(get_EventSink) (THIS_ IDispatch **ppdispSink) PURE;
	/**
	 * This method sets the event sink of a control.
	 *
	 * @param pdispSink Pointer to the control's IASCEventSink interface.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * This method must be implemented, but can return E_NOTIMPL.
	 */
	STDMETHOD(put_EventSink) (THIS_ IDispatch *pdispSink) PURE;	
	/**
	 * This method retrieves the current delegate control of the current control.
	 *
	 * @param ppdispDelegate Pointer to the pointer to the IDispatch interface.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(get_Delegate) (THIS_ IDispatch **ppdispDelegate) PURE;
	/**
	 * This method specifies the delegate control that receives messages that the current control does
	 * not handle.
	 *
	 * @param pdispDelegate Pointer to the IDispatch interface.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(put_Delegate) (THIS_ IDispatch *pdispDelegate) PURE;	
	//
	// Boolean
	//
	/**
	 * This method indicates whether or not the control is visible.
	 *
	 * @param pfVisible Pointer to a Boolean that is set to TRUE if the control is visible, or to FALSE
	 *   if is hidden.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * This method is required.
	 */
	STDMETHOD(get_Visible) (THIS_ BOOL *pfVisible) PURE;
	/**
	 * This method sets whether or not the control is visible.
	 *
	 * @param fVisible Boolean that is set to TRUE if the control is visible, or to FALSE if it is
	 *   hidden.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * This method is required.
	 */
	STDMETHOD(put_Visible) (THIS_ BOOL fVisible) PURE;
	/**
	 * This method indicates whether or not the control is enabled.
	 *
	 * @param pfEnabled Pointer to a Boolean that is set to TRUE if the control is enabled, or to FALSE
	 *   if it is disabled.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * This method is required.
	 */
	STDMETHOD(get_Enable) (THIS_ BOOL *pfEnable) PURE;
	/**
	 * This method sets whether or not the control is enabled.
	 *
	 * @param fEnabled Boolean that is set to TRUE to enable the control, or to FALSE to disable it.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * This method is required.
	 */
	STDMETHOD(put_Enable) (THIS_ BOOL fEnable) PURE;
	/**
	 * This method indicates whether the control is drawn opaque or transparent.
	 *
	 * @param pfOpaque Pointer to a Boolean that is set to TRUE if the control is opaque, or to FALSE if
	 *   it is transparent.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * This method must be implemented, but can return E_NOTIMPL.
	 */
	STDMETHOD(get_Opaque) (THIS_ BOOL *pfOpaque) PURE;
	/**
	 * This method sets whether control is drawn opaque or transparent.
	 *
	 * @param fOpaque Boolean that is set to TRUE if the control is opaque, or to FALSE if it is
	 *   transparent.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * This method must be implemented, but can return E_NOTIMPL.
	 */
	STDMETHOD(put_Opaque) (THIS_ BOOL fOpaque) PURE;
	/**
	 * This method indicates whether or not the control has a border.
	 *
	 * @param pfBorder Pointer to a Boolean that is set to TRUE if the control has a border, or to FALSE
	 *   if it does not.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * This method must be implemented, but can return E_NOTIMPL.
	 */
	STDMETHOD(get_Border) (THIS_ BOOL *pfBorder) PURE;
	/**
	 * This method sets whether or not the control has a border.
	 *
	 * @param fBorder Boolean that is set to TRUE if the control has a border, or to FALSE if it does
	 *   not.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * This method must be implemented, but can return E_NOTIMPL.
	 */
	STDMETHOD(put_Border) (THIS_ BOOL fBorder) PURE;
    /**
     * This method indicates whether or not drawing has been deferred.
     *
     * @param pfDeferDraw Pointer to a Boolean that is set to TRUE if drawing has been deferred, or to
     *   FALSE if is not.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     *
     * An application can defer drawing until it is ready. If this property is TRUE for a form, drawing
     * is deferred for all controls on the form until it is set to FALSE.
     */
    STDMETHOD(get_DeferDraw) (THIS_ BOOL *pfDeferDraw) PURE;
    /**
     * This method sets whether or not drawing is deferred.
     *
     * @param fDeferDraw Boolean that is set to TRUE to defer drawing, or to FALSE otherwise.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     *
     * An application can defer drawing until it is ready. If this property is TRUE for a form, drawing
     * is deferred for all controls on the form until it is set to FALSE.
     */
    STDMETHOD(put_DeferDraw) (THIS_ BOOL fDeferDraw) PURE;

	/**
	 * This method indicates whether or not the control is a tabstop.
	 *
	 * @param pfTabStop Pointer to a Boolean that is set to TRUE if the control is a tabstop, or to
	 *   FALSE if the control is not.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * This method must be implemented, but can return E_NOTIMPL.
	 */
	STDMETHOD(get_TabStop) (THIS_ BOOL *pfTabStop) PURE; // RO
   	/**
   	 * This method indicates whether or not the control has a user interface (UI).
   	 *
   	 * @param pfHasUI Pointer to a Boolean that is set to TRUE if the control has a UI, or to FALSE if
   	 *   it does not.
   	 *
   	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
   	 *
   	 * This method is required.
   	 */
   	STDMETHOD(get_HasUI) (THIS_ BOOL *pfHasUI) PURE;     // RO
	//
	// Fonts and Colors
	//
    /**
     * This method sets a color specified by a color index.
     *
     * @param nColorIndex Color index.
     * @param clr Color to set.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(put_Color) (THIS_ int nColorIndex, OLE_COLOR clr) PURE;
    /**
     * This method gets the color that corresponds to a specified index.
     *
     * @param nColorIndex Color index.
     * @param pclr Pointer to an OLE_COLOR.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(get_Color) (THIS_ int nColorIndex, OLE_COLOR* pclr) PURE;
	/**
	 * This method gets the foreground color of a control.
	 *
	 * @param pclr Pointer to the foreground color of the control.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * This method must be implemented, but can return E_NOTIMPL.
	 */
	STDMETHOD(get_ForeColor) (THIS_ OLE_COLOR *pclr) PURE;
	/**
	 * This method sets the foreground color of the control.
	 *
	 * @param clr Foreground color of the control.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * This method must be implemented, but can return E_NOTIMPL.
	 */
	STDMETHOD(put_ForeColor) (THIS_ OLE_COLOR clr) PURE;
	/**
	 * This method retrieves the background color of the control.
	 *
	 * @param pclr Pointer to the background color of the control.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * This method must be implemented, but can return E_NOTIMPL.
	 */
	STDMETHOD(get_BackColor) (THIS_ OLE_COLOR *pclr) PURE;
	/**
	 * This method sets the background color of the control.
	 *
	 * @param clr Background color of the control.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * This method must be implemented, but can return E_NOTIMPL.
	 */
	STDMETHOD(put_BackColor) (THIS_ OLE_COLOR clr) PURE;
    /**
     * This method gets the font of a control.
     *
     * @param ppFontDisp Pointer to the pointer to the control's display font.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     *
     * This method must be implemented, but can return E_NOTIMPL.
     *
     * For Microsoft Windows CE for the Auto PC, the font size is 10000 times value of the lower 32 bits
     * of the psize variable used in the Component Object Module (COM) IFont:get_Size and IFont:put_Size
     * methods.
     */
    STDMETHOD(get_Font) (THIS_ IFontDisp **ppFontDisp) PURE;
    /**
     * This method sets the font of a control.
     *
     * @param pFontDisp Pointer to the control's display font.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     *
     * This method must be implemented, but can return E_NOTIMPL.
     *
     * For Microsoft Windows CE for the Auto PC, the font size is 10000 times value of the lower 32 bits
     * of the psize variable used in the Component Object Module (COM) IFont:get_Size and IFont:put_Size
     * methods.
     */
    STDMETHOD(put_Font) (THIS_ IFontDisp *pFontDisp) PURE;
    /**
     * This method retrieves the current background brush.
     *
     * @param phBrush Pointer to the handle to the background brush of the control.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     *
     * This method must be implemented, but can return E_NOTIMPL.
     */
    STDMETHOD(get_BackgroundBrush) (THIS_ OLE_HANDLE *phBrush) PURE;
    /**
     * This method sets the current background brush of the control.
     *
     * @param hBrush Handle to the control's background brush.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     *
     * This method is not required, and can return E_NOTIMPL.
     */
    STDMETHOD(put_BackgroundBrush) (THIS_ OLE_HANDLE hBrush) PURE;
	//
	// Dimensions
	//
	/**
	 * This method retrieves the x-coordinate of the left edge of the control.
	 *
	 * @param px Pointer to the x-coordinate of the control's left edge.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * This method must be implemented, but can return E_NOTIMPL. However, it should be fully
	 * implemented if IASControl::GetBounds is implemented.
	 */
	STDMETHOD(get_Left) (THIS_ long *px) PURE;
	/**
	 * This method sets the x-coordinate of the left edge of a control.
	 *
	 * @param x Specifies the x-coordinate of the control's left edge.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * This method must be implemented, but can return E_NOTIMPL.
	 */
	STDMETHOD(put_Left) (THIS_ long x) PURE;
	/**
	 * This method retrieves the width of a control.
	 *
	 * @param pdx Pointer to the control's width.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * This method must be implemented, but can return E_NOTIMPL. However, it should be fully
	 * implemented if IASControl::GetBounds is implemented.
	 */
	STDMETHOD(get_Width) (THIS_ long *pdx) PURE;
	/**
	 * This method sets the width of a control.
	 *
	 * @param dx Specifies the control's width.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * This method must be implemented, but can return E_NOTIMPL.
	 */
	STDMETHOD(put_Width) (THIS_ long dx) PURE;
	/**
	 * This method retrieves the y-coordinate of the top of the control.
	 *
	 * @param py Pointer to the y-coordinate of the top of the control.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * This method must be implemented, but can return E_NOTIMPL. However, it should be fully
	 * implemented if IASControl::GetBounds is implemented.
	 */
	STDMETHOD(get_Top) (THIS_ long *py) PURE;
	/**
	 * This method sets the y-coordinate of the top of the control.
	 *
	 * @param y Specifies the y-coordinate of the top of the control.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * This method must be implemented, but can return E_NOTIMPL.
	 */
	STDMETHOD(put_Top) (THIS_ long y) PURE;
	/**
	 * This method retrieves the height of a control.
	 *
	 * @param pdy Pointer to the control's height.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * This method must be implemented, but can return E_NOTIMPL. However, it should be fully
	 * implemented if IASControl::get_Bounds is implemented.
	 */
	STDMETHOD(get_Height) (THIS_ long *pdy) PURE;
	/**
	 * This method sets the height of a control.
	 *
	 * @param dy Specifies the control's height.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * This method must be implemented, but can return E_NOTIMPL.
	 */
	STDMETHOD(put_Height) (THIS_ long dy) PURE;
	//
	// Strings
	//
	/**
	 * This method gets the caption associated with a particular control.
	 *
	 * @param pbstrCaption Pointer to the Unicode string to be displayed as the caption.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * This method must be implemented, but can return E_NOTIMPL.
	 */
	STDMETHOD(get_Caption) (THIS_ BSTR *pbstrCaption) PURE;
	/**
	 * This method sets the caption associated with a particular control.
	 *
	 * @param bstrCaption Unicode string to be displayed as the caption.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * This method must be implemented, but can return E_NOTIMPL.
	 */
	STDMETHOD(put_Caption) (THIS_ BSTR bstrCaption) PURE;
    // 
    // Others
    //
	/**
	 * This method retrieves data stored by the user.
	 *
	 * @param plData Pointer to a long integer containing data that a user wants to associate with the
	 *   control.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * This method must be implemented, but can return E_NOTIMPL.
	 */
	STDMETHOD(get_UserData) (THIS_ long *plData) PURE;
	/**
	 * This method sets user-defined data.
	 *
	 * @param lData Long integer that contains data that a user wants to associate with the control.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 */
	STDMETHOD(put_UserData) (THIS_ long lData) PURE;	

    // Natural Size,  the size that a control would like to be
    /**
     * This method gets the natural size of a control.
     *
     * @param plWidth Pointer to a long integer that contains the natural width of a control.
     * @param plHeight Pointer to a long integer that contain the natural height of a control.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     *
     * The natural size of a control typically consists of the dimensions a control would need to
     * display its contents. For example, the natural size of a label control with a
     * ASFC_ALIGN_SINGLELINE format is the width required to display the control's full caption.
     */
    STDMETHOD(get_NaturalSize) (THIS_ long *plWidth, long *plHeight) PURE;

    // speech feedback
    /**
     * This method provides speech feedback.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(Speak)(THIS_ DWORD dwSpeechContext, DWORD dwMode, DWORD dwReserved )  PURE;
	};

#undef	INTERFACE
#define	INTERFACE

// Titlebar interface
#if defined(__cplusplus) && !defined(CINTERFACE)
/**
 * This interface provides methods for managing a title bar.
 *
 * The IASTitleBar interface extends the IASControl interface. The title bar has a programmatic
 * identifier equal to APC_Titlebar.
 */
struct IASTitlebar : public IASControl
#else
DECLARE_INTERFACE_(IASTitlebar, IASControl)
#endif
{
    /**
     * This method gets the title bar subcaption.
     *
     * @param pbstrSubCaption Pointer to a Unicode string that contains the title bar's subcaption.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(get_SubCaption) (THIS_ BSTR *pbstrSubCaption) PURE;
    /**
     * This method sets the title bar subcaption.
     *
     * @param bstrSubCaption Unicode string that contains the title bar's subcaption.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(put_SubCaption) (THIS_ BSTR bstrSubCaption) PURE;
    
    /**
     * This method gets the title bar icon.
     *
     * @param phIcon Pointer to the handle of the icon.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(get_Icon)(THIS_ OLE_HANDLE *phIcon) PURE;
    /**
     * This method sets the title bar icon.
     *
     * @param phIcon Pointer to the OLE_HANDLE to the icon.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     *
     * The size of the title bar icon must be 16 pixels x 16 pixels.
     */
    STDMETHOD(put_Icon)(THIS_ OLE_HANDLE hIcon) PURE;
    
    /**
     * This method sets the status of the title bar image list.
     *
     * @param hbmImage OLE_HANDLE to a bitmap image.
     * @param hbmImageMask OLE_HANDLE to a bitmap image mask.
     * @param cxImage Long integer that contains the x-coordinate of the image.
     * @param cyImage Long integer that contains the y-coordinate of the image.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(put_StatusImageList)(THIS_ OLE_HANDLE hbmImage, OLE_HANDLE hbmImageMask, long cxImage, long cyImage) PURE;
    /**
     * This method gets the status of the title bar image list.
     *
     * @param phbmImage Pointer to an OLE_HANDLE to a bitmap image.
     * @param phbmImageMask Pointer to an OLE_HANDLE to a bitmap image mask.
     * @param pcxImage Pointer to a long integer that contains the x-coordinate of the image.
     * @param pcyImage Pointer to a long integer that contains the y-coordinate of the image.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(get_StatusImageList)(THIS_ OLE_HANDLE *phbmImage, OLE_HANDLE *phbmImageMask, long *pcxImage, long *pcyImage) PURE;
    
    /**
     * This method sets the title bar status flags that control the images displayed from the image
     * list.
     *
     * @param lStatusFlags Long integer that contains the status flags. The first image is displayed if
     *   bit 0 is set. The second image is displayed if bit 1 is set.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(put_StatusFlags) (THIS_ long lStatusFlags) PURE;
    /**
     * This method gets the title bar status flags that control the images displayed from the image
     * list.
     *
     * @param plStatusFlags Pointer to a long integer that contains the status flags. The first image is
     *   displayed if bit 0 is set. The second image is displayed if bit 1 is set.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(get_StatusFlags) (THIS_ long *plStatusFlags) PURE;

    /**
     * This method sets the maximum width of title bar text.
     *
     * @param lMaxTitleWidth Long integer that contains the maximum width of the title bar title.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(put_MaxTitleWidth) (THIS_ long lMaxTitleWidth) PURE;
    /**
     * This method gets the maximum width of the title bar text.
     *
     * @param plMaxTitleWidth Pointer to a long integer that contains the maximum width allowed for the
     *   title bar.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(get_MaxTitleWidth) (THIS_ long *plMaxTitleWidth) PURE;
};



#undef	INTERFACE
#define	INTERFACE

// Navigation Arrows interface
#if defined(__cplusplus) && !defined(CINTERFACE)
/**
 * This interface provides methods for managing a navigational arrows control.
 *
 * The IASUserNavArrows interface extends the IASControl interface. The navigational arrows control
 * has a programmatic identifier equal to APC_NavArrows.
 */
struct IASUserNavArrows : public IASControl
#else
DECLARE_INTERFACE_(IASUserNavArrows, IASControl)
#endif
{
    /**
     * This method gets the state of the navigational arrows control.
     *
     * @param plNavState Pointer to a long integer that contains the state of the navigational arrows
     *   control. It is one or a combination of the following flags. Flag Value Description USER_NAV_LEFT
     *   0x0001 Control displays the left arrow. USER_NAV_UP 0x0002 Control displays the up arrow.
     *   USER_NAV_RIGHT 0x0004 Control displays the right arrow. USER_NAV_DOWN 0x0008 Control displays the
     *   down arrow. USER_NAV_ENTER 0x0010 Control displays the center dot that represents the ENTER key.
     *   USER_NAV_SMALL 0x4000 Control displays a smaller, 19 x 19 version of the navigational arrows
     *   control. USER_NAV_DISABLED 0x8000 Reserved for internal use.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(get_NavState) (THIS_ long *plNavState) PURE;
    /**
     * This method sets the state of the navigational arrows control.
     *
     * @param plNavState Long integer that contains the state of the navigational arrows control. It is
     *   one or a combination of the following flags. Flag Value Description USER_NAV_LEFT 0x0001 Displays
     *   the left arrow. USER_NAV_UP 0x0002 Displays the up arrow. USER_NAV_RIGHT 0x0004 Displays the
     *   right arrow. USER_NAV_DOWN 0x0008 Displays the down arrow. USER_NAV_ENTER 0x0010 Displays the
     *   center dot that represents the ENTER key. USER_NAV_SMALL 0x4000 Displays a smaller, 19 x 19
     *   version of the navigational arrows control. USER_NAV_DISABLED 0x8000 Reserved for internal use.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(put_NavState) (THIS_ long lNavState) PURE;
    /**
     * This method queries the form to determine the state of the navigational arrows control.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(QueryFormForNavState)( THIS) PURE;
};	



#undef	INTERFACE
#define	INTERFACE

// Query Key Usage interface
#if defined(__cplusplus) && !defined(CINTERFACE)
/**
 * This interface provides a method to determine key usage.
 */
struct IQueryKeyUsage : public IUnknown
#else
DECLARE_INTERFACE_(IQueryKeyUsage, IUnknown)
#endif
{
    /**
     * This method gets the flags of the keys used.
     *
     * @param lKeysUsed Long integer that contains the keystrokes used. It is any combination of the
     *   following flags. - QKU_VK_LEFT: The LEFT ARROW key. - QKU_VK_UP: The UP ARROW key. -
     *   QKU_VK_RIGHT: The RIGHT ARROW key. - QKU_VK_DOWN: The DOWN ARROW key. - QKU_VK_RETURN: The ENTER
     *   key.
     * @param lKeysEaten Long integer that contains the keystrokes discarded. It is any combination of
     *   the following flags. - QKU_VK_LEFT: The LEFT ARROW key. - QKU_VK_UP: The UP ARROW key. -
     *   QKU_VK_RIGHT: The RIGHT ARROW key. - QKU_VK_DOWN: The DOWN ARROW key. - QKU_VK_RETURN: The ENTER
     *   key.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     *
     * This method allows you to notify a NavArrow control that your form or application can handle
     * particular keystrokes. The NavArrow control queries the Forms Manager about such keystrokes by
     * posting a WM_QUERYKEYUSAGE message. The lparam of this message is a pointer to an IQueryKeyUsage
     * interface. The form sink or application sink that processes keystrokes should call
     * IQueryKeyUsage::FlagKeysUsed with the flags for each of the navigation keystrokes that the form
     * or application can process or discard. Discarded keystrokes are keystrokes to which the sink does
     * not respond but for which the sink will return S_FALSE, preventing other message handlers from
     * having the opportunity to process the keystroke.
     *
     * Only forms or applications that intercept arrow keystrokes or enter keystrokes need to process
     * the WM_QUERYKEYUSAGE message.
     *
     * The following code example shows how to use the WM_QUERYKEYUSAGE message and
     * IQueryKeyUsage::FlagKeysUsed method.
     *
     *     if (WM_APCSYSMSG_QUERYKEYUSAGE == uMsg)
     *     {
     *         IQueryKeyUsage *pqku = (IQueryKeyUsage*)lParam;
     *
     *         // Return the result of FlagKeyUsed as the return value for
     *         // the current method.
     *         return pqku->FlagKeysUsed((QKU_VK_LEFT | QKU_VK_RIGHT), (QKU_VK_UP | QKU_VK_DOWN));
     *     }
     */
    STDMETHOD(FlagKeysUsed) (THIS_ long lKeysUsed, long lKeysEaten) PURE;
};	



#undef	INTERFACE
#define	INTERFACE

//
// AutoPC Simple Forms must implement this interface
// A Form is ALSO a control and inherits from IASControl
//
#if defined(__cplusplus) && !defined(CINTERFACE)
/**
 * This interface provides methods for managing controls on a form.
 *
 * The IASForm interface extends the IASControl interface.
 */
struct IASForm : public IASControl
#else
DECLARE_INTERFACE_(IASForm, IASControl)
#endif
	{
    // Unitialize
	/**
	 * This method uninitializes a form that has not been started.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * While this method has the same effect as invoking IASControl::Close for the form,
	 * IASForm::Uninitialize works for forms that have not been started yet.
	 */
	STDMETHOD(Uninitialize) (THIS) PURE;
	//
	// Add, remove, count controls
	//
	/**
	 * This method gets the number of controls on a form.
	 *
	 * @param pcItems Pointer to the number of controls on the form.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 */
	STDMETHOD(get_Count) (THIS_ long *pcItems) PURE;
	/**
	 * This method gets a pointer to a control on a form.
	 *
	 * @param index Index of the control to be retrieved.
	 * @param ppdisp Pointer to the pointer to the control.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 */
	STDMETHOD(Item) (THIS_ VARIANT index, IDispatch **ppdisp) PURE;
    /**
     * This method gets a pointer to a specified control based on its identifier.
     *
     * @param ID Identifier of the control.
     * @param ppdisp Pointer to the pointer to the control.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(ItemFromID) (THIS_ short wID, IDispatch **ppdisp) PURE;

	/**
	 * This method adds a control to the form.
	 *
	 * @param pdispControl Pointer to the control to be added.
	 * @param wID Short integer that contains the identifier of the control.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 */
	STDMETHOD(Add) (THIS_ IDispatch *pdispControl, short wID) PURE;
	/**
	 * This method removes a control from a form.
	 *
	 * @param pdispControl Pointer to the control to be removed.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * IASForm::Remove calls IASControl::Close for the control being removed.
	 */
	STDMETHOD(Remove) (THIS_ IDispatch *pdispControl) PURE;
    /**
     * The IASForm::RemoveAtIndex method removes a control with a specified index from a form.
     *
     * @param index Index of a control.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     *
     * A control's index may change as controls are added or removed. Identifiers, however, do not
     * change. IASForm::RemoveAtIndex calls IASControl::Close for the control to be removed.
     */
    STDMETHOD(RemoveAtIndex) (THIS_ long index) PURE;
    /**
     * The IASForm::RemoveByID method removes a control with a specified identifier from a form.
     *
     * @param ID Identifier of a control.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     *
     * IASForm::RemoveByID calls IASControl::Close for the control to be removed.
     */
    STDMETHOD(RemoveByID) (THIS_ short wID) PURE;
	/**
	 * This method removes all controls from a form.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * IASForm::RemoveAll calls IASControl::Close for each of the controls on the form.
	 */
	STDMETHOD(RemoveAll) (THIS) PURE;

    /**
     * This method checks whether a particular control is on a form.
     *
     * @param pdispControl Pointer to the control.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument was entered.
     *   S_FALSE indicates that a particular control is not on the form.
     */
    STDMETHOD(IsControlOnForm) (THIS_ IDispatch *pdispControl) PURE;
	//
	// Draw everything that is in the update region
	//
	/**
	 * This method updates the controls that are in the update region.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * To force a redraw of one control, the IASControl::Redraw method is more efficient because it does
	 * not have to search for outdated portions of the region. IASControl::Redraw completely redraws a
	 * region, while IASControl::Update refreshes a region by searching for outdated portions of the
	 * region.
	 */
	STDMETHOD(Update) (THIS) PURE;
	/**
	 * This method retrieves a pointer to the IFMDraw interface associated with a control.
	 *
	 * @param ppdispFMDraw Pointer to the pointer to an IFMDraw interface.
	 * @param lxLeft Long integer that contains the coordinate of the left edge of the drawing
	 *   rectangle.
	 * @param lyTop Long integer that contains the coordinate of the upper edge of the drawing
	 *   rectangle.
	 * @param lxWidth Long integer that contains the width of the drawing rectangle.
	 * @param lyHeight Long integer that contains the height of the drawing rectangle.
	 *
	 * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument was used.
	 *   E_ACCESSDENIED indicates that no IFMDraw interface identifier (IID) is available. If an error
	 *   occurs, the appropriate HRESULT value is returned.
	 *
	 * You should not use this method in most applications. Use this method only when designing custom
	 * controls.
	 */
	STDMETHOD(GetIFMDraw) (THIS_ IDispatch **ppdispFMDraw, long lxLeft, long lyTop, long lxWidth, long lyHeight) PURE;

    // Speech Initialization paramenters required by Ctrls

    STDMETHOD(GetSpeechInitInfo) (THIS_ OLE_HANDLE * phWnd, long * pThreadId) PURE;    

	//
	// Invalidation. Invalidate the given area in the form
	//
	/**
	 * This method invalidates a specified rectangle.
	 *
	 * @param xLeft Specifies the x-coordinate of the left edge of the form.
	 * @param yTop Specifies the y-coordinate of the upper edge of the form.
	 * @param dxWidth Specifies the width of the form.
	 * @param dyWidth Specifies the height of the form.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * This method adds the specified rectangle to the forms update region. The update region is
	 * repainted the next time the offscreen bitmap is blitted to the screen.
	 */
	STDMETHOD(Invalidate) (THIS_ long lxLeft, long lyTop, long lxWidth, long lyHeight) PURE;
    /**
     * This method invalidates the entire form.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(InvalidateAll) (THIS) PURE;
	//
	// Change focus
	//
    /**
     * This method retrieves a pointer to the control that has the current focus.
     *
     * @param ppdispControl Pointer to the pointer to the control's IASControl interface.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(GetFocus) (THIS_ IDispatch **ppdispControl) PURE;
    /**
     * This method sets the focus to a specified control.
     *
     * @param pdispControl Pointer to the control.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     *
     * Controls that do not receive user input such as a Clock control or a Label control do not accept
     * focus.
     */
    STDMETHOD(SetFocus) (THIS_ IDispatch *pdispControl) PURE;
	/**
	 * This method sets the focus to the next control.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 */
	STDMETHOD(SetFocusNext) (THIS) PURE;
	/**
	 * This method sets the focus to the previous control.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 */
	STDMETHOD(SetFocusPrev) (THIS) PURE;
    /**
     * This method places a control in a specified position in the z-order.
     *
     * @param pdispControl Pointer to the control to be placed in the z-order.
     * @param pdispControlAfter Pointer to the control that precedes the control specified in
     *   pdispControl. If this parameter is NULL, pdispControl becomes the first control in the z-order.
     *
     * @return NOERROR indicates success. ASFC_E_CTRL_NOSUCH indicates that one of the two controls is
     *   not on the form. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(SetZOrder) (THIS_ IDispatch *pdispControl, IDispatch *pdispControlAfter) PURE;
    //
    // Timers
    //
    /**
     * This method sets a timer.
     *
     * @param pdispControl Pointer to the control the timer is associated with.
     * @param dMilliSecs Specifies, in milliseconds, the timer setting.
     * @param pTimerID Pointer to the long integer that contains the identifier of the timer.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     *
     * When the timer reaches 0, it fires a WM_TIMER message to the event sink. The control's identifier
     * is contained in the low-order word of the message's wParam.
     */
    STDMETHOD(SetTimer) (THIS_ IDispatch *pdispControl, UINT dMilliSecs, long *pTimerID) PURE;
    /**
     * This method stops-or kills-a timer.
     *
     * @param lTimerID Long integer that contains the identifier of the timer to be stopped.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     *
     * This method stops a timer started by a call to IASForm::SetTimer.
     */
    STDMETHOD(KillTimer) (THIS_ long idTimer) PURE;
    //
    // Voice Menu
    //
    /**
     * This method gets the voice menu currently associated with the form.
     *
     * @param ppUnknownVoiceMenu Pointer to the pointer to the voice menu.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     *
     * Once a voice menu is attached to a form, it is automatically activated or deactivated by the
     * Forms Manager when focus changes for the form or application. This eliminates the need for
     * applications to activate or deactivate their own voice menus when they receive a WM_ACTIVATE
     * message.
     */
    STDMETHOD(get_VoiceMenu) (THIS_ IUnknown **ppUnknownVoiceMenu) PURE;
	/**
	 * This method sets the voice menu currently associated with the form.
	 *
	 * @param pUnknownVoiceMenu Pointer to the voice menu.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * Once a voice menu is attached to a form, it is automatically activated or deactivated by the
	 * Forms Manager when focus changes for the form or application. This eliminates the need for
	 * applications to activate or deactivate their own voice menus when they receive a WM_ACTIVATE
	 * message.
	 */
	STDMETHOD(put_VoiceMenu) (THIS_ IUnknown *pUnknownVoiceMenu) PURE;

	//
	// Form specific properties
	//

    /**
     * This method gets the status of the wait cursor.
     *
     * @param pfWaitStatus Pointer to a Boolean that indicates the status of the wait cursor. TRUE
     *   indicates that the wait cursor is set. FALSE indicates that the wait cursor is not set.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     *
     * The hour glass or wait cursor shows that a process is taking place, such as copying a file. To
     * ensure that an application does not interrupt the process, check the status of the wait cursor.
     * When the wait cursor is set, a wait icon is displayed in the center of the form.
     */
    STDMETHOD(get_WaitStatus) (THIS_ BOOL *pfWaitStatus) PURE;
    /**
     * This method sets the status of the wait cursor.
     *
     * @param fWaitStatus Boolean that is set to TRUE if the wait cursor is set or to FALSE if the wait
     *   cursor is not set.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     *
     * When the wait cursor is set, a wait icon is displayed in the center of the form.
     */
    STDMETHOD(put_WaitStatus) (THIS_ BOOL fWaitStatus) PURE;	

    STDMETHOD(get_IconTrayVisible) (THIS_ BOOL *pfVisible) PURE;
    STDMETHOD(put_IconTrayVisible) (THIS_ BOOL fVisible) PURE;
    
	//
	// Speech
	//
	/**
	 * This method gets a pointer to the IAPCSpeech interface associated with a control.
	 *
	 * @param ppSpeech Pointer to the pointer to the IAPCSpeech interface.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 */
	STDMETHOD(get_Speech)(THIS_ IAPCSpeech** ppSpeech) PURE;

    // User Navigation Arrows Control
    /**
     * This method gets a pointer to a navigational arrows control.
     *
     * @param ppNavArrrows Pointer to a pointer to a NavArrows control.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(get_NavArrows)(THIS_ IASUserNavArrows** ppNavArrows) PURE;
    
    // Title Bar Control
    /**
     * This method gets a pointer to the title bar for the form.
     *
     * @param ppTitlebars Pointer to a pointer to a title bar.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(get_Titlebar)(THIS_ IASTitlebar** ppTitlebar) PURE;

    // context sensitive help
    /**
     * This method sets a specified help file.
     *
     * @param bstrHelpFiles Unicode string that contains the name of the Help index file to set.
     * @param bstrHelpTopic Unicode string that contains the name of the Help topic file to set.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(put_HelpContext)(THIS_ BSTR bstrHelpFile, BSTR bstrHelpTopic) PURE;    
    /**
     * This method gets the current help file and topic associated with the form.
     *
     * @param pbstrHelpFiles Pointer to a Unicode string that contains the name of the Help index file
     *   to retrieve.
     * @param pbstrHelpTopic Pointer to a Unicode string that contains the name of the Help topic file
     *   to retrieve.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
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

#if defined(__cplusplus) && !defined(CINTERFACE)
/**
 * This interface is exposed by the Forms Manager object , and provides methods that enable an
 * application to manage its forms.
 *
 * The IASActiveForms interface extends the IDispatch interface.
 */
struct IASActiveForms : public IDispatch
#else
DECLARE_INTERFACE_(IASActiveForms, IDispatch)
#endif
    {
	//
	// Collection methods
	//
	/**
	 * This method retrieves the number of active forms for the application.
	 *
	 * @param pcItems Pointer to the number of active forms for the application.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 */
	STDMETHOD(get_Count) (THIS_ long *pcItems) PURE;
	/**
	 * This method retrieves a pointer to an active form specified by its index.
	 *
	 * @param index Index of the form.
	 * @param ppdispForm Pointer to the pointer to the form.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * The index is not fixed, and can change as forms are added or removed. The identifier does not
	 * change.
	 */
	STDMETHOD(Item) (THIS_ VARIANT index, IDispatch **ppdisp) PURE;
    /**
     * This method retrieves a pointer to an active form specified by its identifier.
     *
     * @param wID Short integer that contains the identifier of the form.
     * @param ppdispForm Pointer to the pointer to the form.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(ItemFromID) (THIS_ short wID, IDispatch **ppdisp) PURE;
	//
	// Change focus (which form in the collection has focus)
	//
    /**
     * This method retrieves a pointer to the form that currently has the focus.
     *
     * @param ppdispForm Pointer to the pointer to the form that currently has the focus.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(GetFocus) (THIS_ IDispatch **ppdispForm) PURE;
    /**
     * This method sets the focus to a specified form.
     *
     * @param pdispForm Pointer to the pointer to the form.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(SetFocus) (THIS_ IDispatch *pdispForm) PURE;
    };

//
// The Forms Manager Manage interface
//
#undef  INTERFACE
#define INTERFACE

#if defined(__cplusplus) && !defined(CINTERFACE)
/**
 * This interface, exposed by the Forms Manager object, provides methods that are used to manage
 * forms.
 *
 * The IfmManage interface extends the IDispatch interface.
 */
struct IfmManage : public IDispatch
#else
DECLARE_INTERFACE_(IfmManage, IDispatch)
#endif
    {
    //
    // Start or Stop Forms
    //
    /**
     * This method registers a form with the Forms Manager.
     *
     * @param pdispForm Pointer to the form to be registered.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(Start) (THIS_ IDispatch *pdispForm) PURE;
	/**
	 * This method removes the registration from a form with the Forms Manager.
	 *
	 * @param pdispForm Pointer to the form from which you want to remove the registration.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 */
	STDMETHOD(Stop) (THIS_ IDispatch *pdispForm) PURE;
    /**
     * This method removes the registration from all of the forms for an application from the Forms
     * Manager.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(StopAll) (THIS) PURE;
    //
    // Focus
    //
    /**
     * This method moves the specified Forms Manager to the foreground and gives it the focus.
     *
     * @param fThis Boolean that is set to TRUE to move the specified Forms Manager to the foreground,
     *   or to FALSE to move the default Forms Manager for the application to the foreground.
     * @param pZOrder Pointer to the current z-order.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     *
     * Only complex applications that use multiple Forms Manager objects should use this method.
     * Application that use a single Forms Manager object should use IfmManage::MoveAppToForeground.
     *
     * This method only affects the z-order for a single Forms Manager. If the application does not have
     * the foreground, the change in z-order is not visible until the application is brought to the
     * foreground.
     *
     * To restore the original z-order of your Forms Manager after using this method, your application
     * should call IfmManage::RestoreZOrder with the z-order that the application received from the
     * original call to IfmManage::MoveToForeground.
     */
    STDMETHOD(MoveToForeground) ( THIS_ BOOL fThis, LONG * pZOrder) PURE;
    /**
     * This method resets the z-order for a Forms Manager to the value of the z-order before the last
     * call to IfmManage::MoveToForeground.
     *
     * @param ZOrder Set to 0 to force the Forms Manager to the background. Set to a nonzero value to
     *   restore the ZOrder to a previous value obtained from IfmManage::MoveToForeground. This parameter
     *   is ignored if the default Forms Manager has the foreground.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     *
     * After calling IfmManage::MoveToForeground, your application can restore the z-order of the
     * application by calling IfmManage::RestoreZOrder with the z-order that the application received
     * from the call to IfmManage::MoveToForeground.
     */
    STDMETHOD(RestoreZOrder) (THIS_ LONG ZOrder) PURE;
    /**
     * This method moves an application to the foreground.
     *
     * @param ProcID The process identifier of the application.
     * @param pZOrder Pointer to the current z-order of the process. It can be NULL.
     * @param Flags Currently, there is only one flag, ASFC_APPSTYLEFLG_POPUP.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument was entered.
     *   If an error occurs, the appropriate HRESULT value is returned.
     *
     * The Forms Manager maintains a z-order for active, registered processes. If you want your
     * application to present information to a user in a pop-up control, call this method with the
     * ASFC_APPSTYLEFLG_POPUP flag. The application receives the current z-order of the application, and
     * then moves to the foreground without sending a WM_APPACTIVATE message to the application that was
     * in the foreground before the call to this method. Although this method changes the foreground
     * application, this method does not change the application context in which the user works. When
     * finished with the pop-up control, your application should call IfmManage::RestoreAppZOrder with
     * the z-order that the application received from the original call to
     * IfmManage::MoveAppToForeground.
     */
    STDMETHOD (MoveAppToForeground)( THIS_ LONG ProcId, LONG * pZOrder, LONG Flags) PURE;
    /**
     * This method restores the z-order of an application.
     *
     * @param ZOrder Set to 0 to force the application to the background. Set to a nonzero value to
     *   restore the z-order of the application to a previous value obtained from a call to
     *   IfmManage::MoveAppToForeground.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     *
     * After calling IfmManage::MoveAppToForeground, your application should restore the z-order of the
     * application by calling IfmManage::RestoreAppZOrder with the z-order that the application received
     * from the call to IfmManage::MoveAppToForeground.
     */
    STDMETHOD (RestoreAppZOrder)( THIS_ LONG ZOrder) PURE;
	//
    // Management Interfaces
    //
	/**
	 * This method gets the context handle of the Forms Manager.
	 *
	 * @param phFC Pointer to the handle to the Forms Manager's context. It is FC_MAINFACEPLATE.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * Context handles are always to the faceplate screen.
	 */
	STDMETHOD (GetFormsContextHandle)( THIS_ OLE_HANDLE * phFC) PURE;
    /**
     * This method registers an application with the Forms Manager, indicating that the application has
     * started.
     *
     * @param hFC Handle to the Forms Manager's context. It is FC_MAINFACEPLATE.
     * @param bstrAppName Unicode string that contains the name of the application.
     * @param AppMsgID Message identifier to be associated with this application.
     * @param Flags Not currently implemented.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     *
     * An application needs to call this method to get the focus. This method associates a name for an
     * application with a running process. The name should correspond the name of the application in the
     * shell. While an application remains registered with the Forms Manager, the shell does not need to
     * restart the application in order to restore the focus to that application. An application that is
     * registered with the Forms Manager should call IfmManage::DeregisterStartedApplication to remove
     * the registration from the application before exiting.
     *
     * Context handles are always to the faceplate screen.
     */
    STDMETHOD (RegisterStartedApplication)( THIS_ OLE_HANDLE hFC, BSTR bstrAppName, LONG AppMsgID, LONG Flags) PURE;
    /**
     * This method removes the registration of an application from the Forms Manager.
     *
     * @param hFC Handle to Forms Manager's context. It is FC_MAINFACEPLATE.
     * @param bstrAppName Unicode string that contains the name of the application.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     *
     * An application needs to register with the Forms Manager to get the focus. An application
     * registered with the Forms Manager should call IfmManage::DeregisterStartedApplication to remove
     * the registration from the application before exiting. Once an application is no longer registered
     * with the Forms Manager, the shell needs to restart the application to restore the focus to that
     * application.
     *
     * Context handles are always to the faceplate screen.
     */
    STDMETHOD (DeregisterStartedApplication)( THIS_ OLE_HANDLE hFC, BSTR bstrAppName) PURE;
          
    /**
     * This method sets the alert state of an application.
     *
     * @param hFC Handle to the Forms Manager's context. It is FC_MAINFACEPLATE.
     * @param fCurrentUser Unsupported for this version.
     * @param bstrAppName Unicode string that contains the name of the application whose alert state has
     *   been set.
     * @param bstrAlertName Unicode string that contains the name of the type of alert.
     * @param AlertAction Long integer that contains the type of alert action. It can be one of the
     *   following values: Alert action Value FMAA_ACTION_CLEAR 0 FMAA_ACTION_RAISE_VALUE 1
     *   FMAA_ACTION_CLEAR_MASK 2 FMAA_ACTION_RAISE_MASK 3
     * @param AlertVal Long integer that contains the value of the alert. Ignored if AlertAction is
     *   FMAA_ACTION_CLEAR.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD (SetAppAlertState)( THIS_ OLE_HANDLE hFC, BOOL fCurrentUser, BSTR bstrAppName, 
                                  BSTR bstrAlertName, LONG AlertAction, LONG AlertVal) PURE;
    /**
     * This method retrieves the alert state of an application.
     *
     * @param hFC Handle to the Forms Manager's context. It is FC_MAINFACEPLATE.
     * @param fCurrentUser Unsupported in this version.
     * @param bstrAppName Unicode string that contains the name of application targeted by the alert
     *   state query.
     * @param bstrAlertName Unicode string that contains the name of the alert being queried.
     * @param pfAlert Pointer to a Boolean that indicates alert status. TRUE indicates that an alert was
     *   raised for the application. FALSE indicates that the alert was cleared.
     * @param pAlertVal Pointer to a long integer that contains the value of the alert.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD (GetAppAlertState)( THIS_ OLE_HANDLE hFC, BOOL fCurrentUser, BSTR bstrAppName, 
                                  BSTR bstrAlertName, BOOL * fAlert, LONG * pAlertVal) PURE;
	// Load Form from RC file
	/**
	 * This method loads a form from a resource file.
	 *
	 * @param hFC OLE_HANDLE to the Forms Manager context.
	 * @param wRsrcID Long integer that contains the identifier of the resource file.
	 * @param ppForm Pointer to the pointer to a form.
	 * @param pDispSink Pointer to an event sink.
	 *
	 * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument was entered.
	 *   E_ACCESSDENIED indicates that access to the resource file was denied. If an error occurs, the
	 *   appropriate HRESULT value is returned.
	 *
	 * For information about how to layout a resource, see Constraint-Based Layout and FA_* Values.For
	 * information about how to layout a resource, see Appendix F, "Constraint-Based Layout and FA_*
	 * Values."
	 */
	STDMETHOD(LoadFormResource) (THIS_ OLE_HANDLE,LONG wRsrcID,IDispatch **ppForm,IDispatch *pDispSink) PURE;
	// Load Menu from RC file
	/**
	 * This method loads a menu from a resource file.
	 *
	 * @param hFC OLE_HANDLE to the Forms Manager context.
	 * @param wRsrcID Long integer that contains the identifier of the resource file.
	 * @param ppMenu Pointer to the pointer to a menu.
	 *
	 * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument was entered.
	 *   E_ACCESSDENIED indicates that access to the resource file was denied. If an error occurs, the
	 *   appropriate HRESULT value is returned.
	 *
	 * For information about how to layout a resource, see Constraint-Based Layout and FA_* Values.For
	 * information about how to layout a resource, see Appendix F, "Constraint-Based Layout and FA_*
	 * Values."
	 */
	STDMETHOD(LoadMenuResource) (THIS_ OLE_HANDLE,LONG wRsrcID,IDispatch **ppMenu) PURE;
    
    //
	// Register & query Msg & event sinks
    //
	/**
	 * This method gets the owner of the Forms Manager.
	 *
	 * @param ppdispParent Pointer to the pointer to the Forms Manager's parent.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 */
	STDMETHOD(get_Parent) (THIS_ IDispatch **ppdispParent) PURE;
	/**
	 * This method gets a pointer to the IASClassMsgSink interface of an application.
	 *
	 * @param ppdispSink Pointer to the pointer to the application's class message sink.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 */
	STDMETHOD(get_ClassMsgSink) (THIS_ IDispatch **ppdispSink) PURE;
	/**
	 * This method registers the class message sink for an application with the Forms Manager.
	 *
	 * @param pdispSink Pointer to the application's class message sink. Set to NULL to clear the
	 *   message sink.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * The application must support a class message sink or this method fails.
	 */
	STDMETHOD(put_ClassMsgSink) (THIS_ IDispatch *pdispSink) PURE;	
	/**
	 * This method gets a pointer to the IASEEventSink interface of an application.
	 *
	 * @param ppdispSink Pointer to the pointer to the application's event sink.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 */
	STDMETHOD(get_EventSink) (THIS_ IDispatch **ppdispSink) PURE;
	/**
	 * This method registers the event sink for an application with the Forms Manager.
	 *
	 * @param pdispSink Pointer to the application's event sink. Set to NULL to clear the event sink.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * The application must support an event sink or the method fails.
	 */
	STDMETHOD(put_EventSink) (THIS_ IDispatch *pdispSink) PURE;	

	/**
	 * This method asynchronously posts a message to the message sink of an application.
	 *
	 * @param uMsg Specifies the message identifier.
	 * @param wParam Long integer that contains the wParam of the message.
	 * @param lParam Long integer that contains the lParam of the message.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * This method places the message in the message queue for the application to handle in order.
	 */
	STDMETHOD(PostMsg)(THIS_ long uMsg, long wParam, long lParam) PURE;
	/**
	 * This method synchronously sends a message to the message sink.
	 *
	 * @param uMsg Specifies the message identifier.
	 * @param wParam Long integer that contains the wParam of the message.
	 * @param lParam Long integer that contains the lParam of the message.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * Use this method to place a message at the head of the message queue.
	 */
	STDMETHOD(SendMsg)(THIS_ long uMsg, long wParam, long lParam) PURE;
	
	/**
	 * This method posts a message to a running application.
	 *
	 * @param uMsg Specifies the message identifier.
	 * @param wParam Long integer that contains the wParam of the message.
	 * @param lParam Long integer that contains the lParam of the message.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * This method provides a simple way to conduct communication between applications. To use
	 * PostMessageToApp, both applications must have the message name defined in a common header file.
	 * Both the client and server application must invoke RegisterWindowMessage to register the message
	 * name. To receive messages, the server application must call
	 * IfmManage::RegisterStartedApplication, with the message name as the third parameter. Any message
	 * with this name that is posted by the client application with PostMessageToApp is sent to the
	 * server's event sinks.
	 *
	 * If speed is important, memory-mapped files are a much faster way to implement interprocess
	 * communication.
	 */
	STDMETHOD(PostMessageToApp)(THIS_ long uMsg, long wParam, long lParam) PURE;
    /**
     * This method closes an application.
     *
     * @param bstrAppName Unicode string that contains the name of the application to shut down.
     * @param fTerminate Boolean that indicates whether to terminate the specified application. TRUE
     *   indicates that the method terminates the application. FALSE indicates that the method does not
     *   terminate the application.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     *
     * Use this method only when reinstalling the .exe file of an application. Do not use this method
     * during the normal operation of an application.
     */
    STDMETHOD(CloseAppByName)(THIS_ BSTR bstrAppName, BOOL fTerminate) PURE;

    // App Data
    /**
     * This method gets the name of the application.
     *
     * @param pbstrAppName Pointer to a Unicode string that contains the name of the application.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(get_AppName) (THIS_ BSTR *pbstrAppName) PURE;
    /**
     * This method sets the name of an application.
     *
     * @param bstrAppName Unicode string that contains the application name to set.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(put_AppName) (THIS_ BSTR bstrAppName) PURE;
    
    /**
     * This method gets the small icon for an application.
     *
     * @param phSmallIcon Pointer to the handle of an icon.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(get_AppSmallIcon) (THIS_ OLE_HANDLE *phSmallIcon) PURE;
    /**
     * This method sets the small icon for an application.
     *
     * @param hSmallIcon Handle of an icon.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(put_AppSmallIcon) (THIS_ OLE_HANDLE hSmallIcon) PURE;

    // Application global help file
    /**
     * This method sets a specified help file.
     *
     * @param bstrHelpFile Unicode string that contains the name of a Help index file.
     * @param bstrHelpTopic Unicode string that contains the name of a Help topic file.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(put_HelpContext)(THIS_ BSTR bstrHelpFile, BSTR bstrHelpTopic) PURE;    
    /**
     * This method gets the help file currently associated with the application.
     *
     * @param pbstrHelpFile Pointer a Unicode string that contains the name of a Help index file.
     * @param pbstrHelpTopic Pointer to a Unicode string that contains the name of a Help topic file.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(get_HelpContext)(THIS_ BSTR *pbstrHelpFile, BSTR *pbstrHelpTopic) PURE;    
    
    //
    // Menus
    //
    /**
     * This method places a specified control into the menu form.
     *
     * @param pdispMenu Pointer to the control to be placed in the menu form. The control must be a
     *   power list box control.
     * @param wID Short integer that contains the menu identifier.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument was entered.
     *   E_ACCESSDENIED indicates that access to the resource file was denied. If an error occurs, the
     *   appropriate HRESULT value is returned.
     *
     * There can only be one menu control on the menu form at a time. This method releases the current
     * menu control, if one is present, and replaces it with a new one.
     */
    STDMETHOD(put_Menu) (THIS_ IDispatch *pdispMenu, short wID) PURE;
    /**
     * This method gets a pointer to the control that is currently selected as the menu control for the
     * application.
     *
     * @param ppdispMenu Pointer to a pointer to a power list box control.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     *
     * The only valid control that can be set on a menu is a power list box control.
     */
    STDMETHOD(get_Menu) (THIS_ IDispatch **ppdispMenu) PURE;
    
    /**
     * This method indicates whether or not the menu is visible.
     *
     * @param pfVisible Pointer to a Boolean that is set to TRUE if the menu is visible, or to FALSE if
     *   it is hidden.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(get_MenuVisible) (THIS_ BOOL *pfVisible) PURE;
    /**
     * This method sets whether or not a menu is visible.
     *
     * @param pfVisible Pointer to a Boolean that is set to TRUE for a visible menu, or to FALSE for an
     *   invisible menu.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     *
     * This method effectively allows an application to invoke or to dismiss a menu.
     */
    STDMETHOD(put_MenuVisible) (THIS_ BOOL fVisible) PURE;

    /**
     * This method gets the title bar menu.
     *
     * @param ppTitlebar Pointer to a pointer to a title bar.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(get_MenuTitlebar) (THIS_ IASTitlebar **ppTitlebar) PURE;
    
	//
	// MessageBox
	//
	/**
	 * This method displays an application-modal message box.
	 *
	 * @param bstrMsg Unicode string that contains text of the message. The message can be a file name
	 *   if the flag FMMB_FLG_FILENAME is set in Flags, or in HTML if the flag FMMB_FLG_HTML is set in
	 *   Flags.
	 * @param bstrCaption Unicode string that contains the caption to place in the title bar of the
	 *   message box form. If bstrCaption is NULL, the application name property of the Forms Manager is
	 *   used, and the AppSmallIcon from the application is displayed for the form icon.
	 * @param uType Specifies one of the following types: MB_ABORTRETRYIGNORE MB_NOBUTTONS MB_OKCANCEL
	 *   MB_OK MB_RETRYCANCEL MB_YESNOCANCEL MB_YESNO The type flags can be combined with one of the
	 *   following optional icons: MB_APC_ICONCHECK MB_ICONASTERISK MB_ICONEXCLAMATION MB_ICONHAND
	 *   MB_ICONQUESTION
	 * @param Flags Specifies how the message box is displayed. It is any combination of the following
	 *   values: - FMMB_FLG_AUTODISMISS: Automatically dismisses the message box after a specified time. -
	 *   FMMB_FLG_TTS: Reads the message aloud using text-to-speech. - FMMB_FLG_BEEP: Plays an audible
	 *   beep when the message box appears. - FMMB_FLG_FILENAME: Specifies that bstrMsg is the name of a
	 *   file that is opened to retrieve the actual text of the message. - FMMB_FLG_HTML: Treats the
	 *   message as HTML text. - FMMB_FLG_OUTOFSTORAGE: Creates an out-of-storage message box. If this
	 *   flag is set, bstrMsg and the FMMB_FLG_FILENAME flag are ignored.
	 * @param pRes Pointer to a long integer that contains the user's response. It is one of the
	 *   following values, depending on the type of message box: IDABORT IDCANCEL IDIGNORE IDNO IDOK
	 *   IDRETRY IDYES
	 *
	 * @return S_OK indicates success. E_INVALIDARG indicates that an invalid argument was entered. If
	 *   an error occurs, the appropriate HRESULT value is returned.
	 *
	 * This method is a synchronous call that does not return until user finishes interacting with the
	 * message box.
	 *
	 * You must call this method from the thread that created the Forms Manager object. While that
	 * thread executes this method, a dispatch loop within this method calls the sinks on the Forms
	 * Manager object. If a message is posted to the thread using the thread identifier while this
	 * method executes, the message is removed from the message queue internally.
	 */
	STDMETHOD(fmMessageBox) (THIS_ BSTR bstrMsg, BSTR bstrCaption, LONG uType, LONG Flags, LONG * pRes) PURE;
	/**
	 * This method closes the message box for an application if one is currently displayed.
	 *
	 * @return S_OK indicates that the method successfully closed the message box. S_FALSE indicates
	 *   that an error occurred.
	 */
	STDMETHOD(fmStopMessageBox) (THIS) PURE;
	//
	// Help
	//
	/**
	 * This method causes the application to enter the help display mode.
	 *
	 * @param bstrFileName Unicode string that contains the name of the Help text file. If dwFlags is
	 *   not APCHELP_INDEX, bstrFieldName can be 0.
	 * @param dwFlags Specifies one of the following flags: - APCHELP_INDEX: Shows the Help index. -
	 *   APCHELP_TOPIC: Shows a Help topic.
	 * @param dwTopicID Specifies the topic file name if dwFlags is APCHELP_TOPIC. Otherwise, it is set
	 *   to 0.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * When this method is called, it hides the form's option menu.
	 */
	STDMETHOD(fmStartHelp) (THIS_ BSTR bstrFileName, DWORD dwFlags=APCHELP_INDEX, DWORD dwTopicID=0) PURE;
	/**
	 * This method closes all help message boxes.
	 *
	 * @return S_OK indicates that the method successfully stopped Help. S_FALSE indicates that an error
	 *   occurred.
	 */
	STDMETHOD(fmStopHelp) (THIS) PURE;

	//
	// Speech
	//
	/**
	 * This method gets a pointer to the IAPCSpeech interface.
	 *
	 * @param ppSpeech Pointer to the pointer to the form's speech interface.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 */
	STDMETHOD(get_Speech)(THIS_ IAPCSpeech** ppSpeech) PURE;
	//STDMETHOD(put_Speech)(THIS_ IAPCSpeech* pSpeech) PURE;

    // Login

    /**
     * This method verifies that the user has entered a password if a password is set.
     *
     * @param bstrTitle Unicode string that contains the title to display, usually the name of the
     *   application.
     * @param fDoLogin Boolean that is set to TRUE if the user is not currently logged on and needs to
     *   be logged on, or to FALSE otherwise.
     * @param fKeepFocusOnFail Boolean that indicates whether or not to keep the foreground focus if the
     *   log in fails. Set to TRUE if the current foreground focus should be kept, or to FALSE if not.
     * @param pfLoggedIn Pointer to a Boolean that is set to TRUE if the user is logged on, or to FALSE
     *   otherwise.
     *
     * @return An appropriate HRESULT value is returned.
     */
    STDMETHOD(fmVerifyLoginState)(THIS_ BSTR bstrTitle, BOOL fDoLogin, BOOL fKeepFocusOnFail, BOOL *pfLoggedIn) PURE;
	
	};


//
// The Forms Manager Information interface
//
#if defined(__cplusplus) && !defined(CINTERFACE)
/**
 * This interface is exposed by the Forms Manager and provides some system-level methods.
 *
 * The IfmSystem interface extends the IDispatch interface.
 */
struct IfmSystem : public IDispatch
#else
DECLARE_INTERFACE_(IfmSystem, IDispatch)
#endif
    {
    /**
     * This method retrieves the display capabilities.
     *
     * @param hFC Handle to the Forms Manager's context. It is FC_MAINFACEPLATE.
     * @param nIndex Specifies the index of the display capabilities item to return. See the
     *   GetDeviceCaps function for Windows-based desktop platforms for a list.
     * @param pRetInfo Pointer to the long integer used to return the display capabilities.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(GetFormDisplayCaps) (THIS_ OLE_HANDLE hFC, LONG nIndex, LONG * pRetInfo) PURE;
    /**
     * This method creates a compatible bitmap.
     *
     * @param hFC Handle to the Forms Manager's context. It is FC_MAINFACEPLATE.
     * @param phBitmap Pointer to the handle to the created bitmap.
     * @param Width Specifies the width of the bitmap.
     * @param Height Specifies the height of the bitmap.
     *
     * @return S_OK indicates success. E_OUTOFMEMORY indicates that the system is out of memory. If an
     *   error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(CreateFMCompatibleBitmap) (THIS_ OLE_HANDLE hFC, OLE_HANDLE *phBmp, LONG width, LONG  height) PURE;
	/**
	 * This method retrieves one of the two system fonts.
	 *
	 * @param hFC Handle to the Forms Manager's context. It is FC_MAINFACEPLATE.
	 * @param fSmall Boolean that is set to TRUE for the small system font, or to FALSE for the large
	 *   system font.
	 * @param ppdispFont Pointer to the pointer to the font.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 *
	 * Context handles are always to the faceplate screen.
	 *
	 * For Microsoft Windows CE for the Auto PC, the font size is 10000 times value of the lower 32 bits
	 * of the psize variable used in the Component Object Module (COM) IFont::get_Size and
	 * IFont::put_Size methods.
	 */
	STDMETHOD(GetFMSystemFont) (THIS_ OLE_HANDLE hFC, BOOL fSmall, IDispatch **ppdispFont) PURE;    
	/**
	 * This method creates a compatible device context (DC).
	 *
	 * @param hFC Handle to the Forms Manager's context. It is FC_MAINFACEPLATE.
	 * @param phDC Pointer to the handle to the created DC.
	 *
	 * @return S_OK indicates success. E_OUTOFMEMORY indicates that the system is out of memory. If an
	 *   error occurs, the appropriate HRESULT value is returned.
	 */
	STDMETHOD(CreateFMCompatibleDC) (THIS_ OLE_HANDLE hFC, OLE_HANDLE *phDC) PURE;
    };

//
// A Collection of Forms Managers
// 
#if defined(__cplusplus) && !defined(CINTERFACE)
/**
 * This interface is exposed by the Forms Manager collection object and provides methods for
 * handling multiple Forms Managers.
 *
 * The IfmCollection interface extends the IDispatch interface.
 */
struct IfmCollection : public IDispatch
#else
DECLARE_INTERFACE_(IfmCollection, IDispatch)
#endif
    {
	/**
	 * This method gets the number of Forms Managers in the collection
	 *
	 * @param pcItems Pointer to the number of Forms Managers in the collection.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 */
	STDMETHOD(get_Count) (THIS_ long *pcItems) PURE;
	/**
	 * This method gets a pointer to a specified Forms Manager.
	 *
	 * @param index Index of the specified Forms Manager.
	 * @param ppdisp Pointer to the pointer to the specified Forms Manager.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 */
	STDMETHOD(Item) (THIS_ VARIANT index, IDispatch **ppdisp) PURE;
	//
	// Change focus (which forms manager in the collection has focus)
	//
    /**
     * This method gets which Forms Manager has focus.
     *
     * @param ppdispfmManage Pointer to the pointer to the Forms Manager that currently has focus.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(GetFocus) (THIS_ IDispatch **ppdispfmManage) PURE;
    /**
     * This method sets the focus to a specified Forms Manager.
     *
     * @param pdispfmManage Pointer to the Forms Manager to receive focus.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
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

