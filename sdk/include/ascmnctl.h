//--------------------------------------------------------------------------------------------
//
//	Copyright (c) Microsoft Corporation, 1997 All Rights Reserved
//
//	Description:
//		AutoPC Simple Common Controls
//
//--------------------------------------------------------------------------------------------

#ifndef _ASCMNCTL_H
#define _ASCMNCTL_H

//--------------------------------------------------------------------------------------------
//
// Includes
//
//--------------------------------------------------------------------------------------------
#include <olectl.h>
#include <asfc.h>
#include <speech.h>
#include <asstyles.h>

//--------------------------------------------------------------------------------------------
//
// Declarations
//
//--------------------------------------------------------------------------------------------
DECLARE_INTERFACE(IASLabel);
DECLARE_INTERFACE(IASButton);
DECLARE_INTERFACE(IASCheckBox);
DECLARE_INTERFACE(IASRadioButton);

DECLARE_INTERFACE(IASListBox);
DECLARE_INTERFACE(IASMenu);
DECLARE_INTERFACE(IASImageMenu);
DECLARE_INTERFACE(IASShellMenu);

DECLARE_INTERFACE(IASTextInputRange);
DECLARE_INTERFACE(IASCharSpinner);
DECLARE_INTERFACE(IASEditBox);
DECLARE_INTERFACE(IASSIP);

DECLARE_INTERFACE(IASProgressBar);
DECLARE_INTERFACE(IASSlider);
DECLARE_INTERFACE(IASVVI);
DECLARE_INTERFACE(IASMemorySlider);

DECLARE_INTERFACE(IASCanvas);

DECLARE_INTERFACE(IASTimer);
DECLARE_INTERFACE(IASPlayList);
DECLARE_INTERFACE(IASClock);

DECLARE_INTERFACE(IASCrossHairs);
DECLARE_INTERFACE(IASTabber);

DECLARE_INTERFACE(IASHTMLControlNotifySink);

// externally defined 
DECLARE_INTERFACE(IAPCSpeech);

//--------------------------------------------------------------------------------------------
//
// Guids
//
//--------------------------------------------------------------------------------------------
//
// A Label Object
//
// {37C23052-997F-11d0-88DC-0000F80401D1}
DEFINE_GUID(CLSID_ASLABEL, 
0x37c23052, 0x997f, 0x11d0, 0x88, 0xdc, 0x0, 0x0, 0xf8, 0x4, 0x1, 0xd1);
// All labels support IFMLabel
// {FF3A65A0-9661-11d0-88DB-0000F80401D1}
DEFINE_GUID(IID_ASLABEL, 
0xff3a65a0, 0x9661, 0x11d0, 0x88, 0xdb, 0x0, 0x0, 0xf8, 0x4, 0x1, 0xd1);
//
// A Button Object
//
// {B9D02950-A6FB-11d0-88E2-0000F80401D1}
DEFINE_GUID(CLSID_ASBUTTON, 
0xb9d02950, 0xa6fb, 0x11d0, 0x88, 0xe2, 0x0, 0x0, 0xf8, 0x4, 0x1, 0xd1);
// {B9D02951-A6FB-11d0-88E2-0000F80401D1}
DEFINE_GUID(IID_ASBUTTON, 
0xb9d02951, 0xa6fb, 0x11d0, 0x88, 0xe2, 0x0, 0x0, 0xf8, 0x4, 0x1, 0xd1);
//
// A CheckBox Object
//
// {5E158370-B6A6-11d0-88E5-0000F80401D1}
DEFINE_GUID(CLSID_ASCHECKBOX, 
0x5e158370, 0xb6a6, 0x11d0, 0x88, 0xe5, 0x0, 0x0, 0xf8, 0x4, 0x1, 0xd1);
// {5E158371-B6A6-11d0-88E5-0000F80401D1}
DEFINE_GUID(IID_ASCHECKBOX, 
0x5e158371, 0xb6a6, 0x11d0, 0x88, 0xe5, 0x0, 0x0, 0xf8, 0x4, 0x1, 0xd1);
//
// A RadioButton object
//
// {CB2F7CD0-B78E-11d0-88E5-0000F80401D1}
DEFINE_GUID(CLSID_ASRADIOBUTTON, 
0xcb2f7cd0, 0xb78e, 0x11d0, 0x88, 0xe5, 0x0, 0x0, 0xf8, 0x4, 0x1, 0xd1);
// {CB2F7CD1-B78E-11d0-88E5-0000F80401D1}
DEFINE_GUID(IID_ASRADIOBUTTON, 
0xcb2f7cd1, 0xb78e, 0x11d0, 0x88, 0xe5, 0x0, 0x0, 0xf8, 0x4, 0x1, 0xd1);
//
// A List Box Object
//
// {97490430-AF7F-11d0-88E4-0000F80401D1}
DEFINE_GUID(CLSID_ASLISTBOX, 
0x97490430, 0xaf7f, 0x11d0, 0x88, 0xe4, 0x0, 0x0, 0xf8, 0x4, 0x1, 0xd1);
// {97490431-AF7F-11d0-88E4-0000F80401D1}
DEFINE_GUID(IID_ASLISTBOX, 
0x97490431, 0xaf7f, 0x11d0, 0x88, 0xe4, 0x0, 0x0, 0xf8, 0x4, 0x1, 0xd1);
//
// A Menu Object
//
// {6BF5F460-B1E5-11d0-88E5-0000F80401D1}
DEFINE_GUID(CLSID_ASMENU, 
0x6bf5f460, 0xb1e5, 0x11d0, 0x88, 0xe5, 0x0, 0x0, 0xf8, 0x4, 0x1, 0xd1);
// {6BF5F461-B1E5-11d0-88E5-0000F80401D1}
DEFINE_GUID(IID_ASMENU, 
0x6bf5f461, 0xb1e5, 0x11d0, 0x88, 0xe5, 0x0, 0x0, 0xf8, 0x4, 0x1, 0xd1);
//
// A Clock Object
//
// {A388E000-A651-11d0-88E2-0000F80401D1}
DEFINE_GUID(CLSID_ASCLOCK, 
0xa388e000, 0xa651, 0x11d0, 0x88, 0xe2, 0x0, 0x0, 0xf8, 0x4, 0x1, 0xd1);
// {A388E001-A651-11d0-88E2-0000F80401D1}
DEFINE_GUID(IID_ASCLOCK, 
0xa388e001, 0xa651, 0x11d0, 0x88, 0xe2, 0x0, 0x0, 0xf8, 0x4, 0x1, 0xd1);
//
// Image List Box
//
// {AD3F85E0-C5B1-11d0-88E9-0000F80401D1}
DEFINE_GUID(CLSID_ASIMAGEMENU,
0xad3f85e0, 0xc5b1, 0x11d0, 0x88, 0xe9, 0x0, 0x0, 0xf8, 0x4, 0x1, 0xd1);
// {AD3F85E1-C5B1-11d0-88E9-0000F80401D1}
DEFINE_GUID(IID_ASIMAGEMENU, 
0xad3f85e1, 0xc5b1, 0x11d0, 0x88, 0xe9, 0x0, 0x0, 0xf8, 0x4, 0x1, 0xd1);
//
// Shell List Box
//
// {A342E850-C80B-11d0-88EA-0000F80401D1}
DEFINE_GUID(CLSID_ASSHELLMENU, 
0xa342e850, 0xc80b, 0x11d0, 0x88, 0xea, 0x0, 0x0, 0xf8, 0x4, 0x1, 0xd1);
// {A342E851-C80B-11d0-88EA-0000F80401D1}
DEFINE_GUID(IID_ASSHELLMENU, 
0xa342e851, 0xc80b, 0x11d0, 0x88, 0xea, 0x0, 0x0, 0xf8, 0x4, 0x1, 0xd1);
//
// Progress Bar
//
// {EA73ACB0-CBE7-11d0-88EA-0000F80401D1}
DEFINE_GUID(CLSID_ASPROGRESSBAR, 
0xea73acb0, 0xcbe7, 0x11d0, 0x88, 0xea, 0x0, 0x0, 0xf8, 0x4, 0x1, 0xd1);
// {EA73ACB1-CBE7-11d0-88EA-0000F80401D1}
DEFINE_GUID(IID_ASPROGRESSBAR, 
0xea73acb1, 0xcbe7, 0x11d0, 0x88, 0xea, 0x0, 0x0, 0xf8, 0x4, 0x1, 0xd1);
//
// Classic "Thumbed" Slider 
//
// {8C5E5FE0-DB7F-11d0-88EA-0000F80401D1}
DEFINE_GUID(CLSID_ASSLIDER, 
0x8c5e5fe0, 0xdb7f, 0x11d0, 0x88, 0xea, 0x0, 0x0, 0xf8, 0x4, 0x1, 0xd1);
// {8C5E5FE1-DB7F-11d0-88EA-0000F80401D1}
DEFINE_GUID(IID_ASSLIDER, 
0x8c5e5fe1, 0xdb7f, 0x11d0, 0x88, 0xea, 0x0, 0x0, 0xf8, 0x4, 0x1, 0xd1);

//
// VVI Control
//
// {25F459C7-4675-11d1-9D21-00C04FC2981B}
DEFINE_GUID(CLSID_ASVVI, 
0x25f459c7, 0x4675, 0x11d1, 0x9d, 0x21, 0x0, 0xc0, 0x4f, 0xc2, 0x98, 0x1b);
// {25F459C8-4675-11d1-9D21-00C04FC2981B}
DEFINE_GUID(IID_ASVVI, 
0x25f459c8, 0x4675, 0x11d1, 0x9d, 0x21, 0x0, 0xc0, 0x4f, 0xc2, 0x98, 0x1b);

//
// Memory Slider 
//
// {B2BF02E0-2F8C-11d1-B08B-0000F8053A78}
DEFINE_GUID(CLSID_ASMEMORYSLIDER, 
0xb2bf02e0, 0x2f8c, 0x11d1, 0xb0, 0x8b, 0x0, 0x0, 0xf8, 0x5, 0x3a, 0x78);
// {57E7BE50-2F90-11d1-B08B-0000F8053A78}
DEFINE_GUID(IID_ASMEMORYSLIDER, 
0x57e7be50, 0x2f90, 0x11d1, 0xb0, 0x8b, 0x0, 0x0, 0xf8, 0x5, 0x3a, 0x78);
//
// Play List
//
// {E50A8EF0-CCB4-11d0-88EA-0000F80401D1}
DEFINE_GUID(CLSID_ASPLAYLIST, 
0xe50a8ef0, 0xccb4, 0x11d0, 0x88, 0xea, 0x0, 0x0, 0xf8, 0x4, 0x1, 0xd1);
// {E50A8EF1-CCB4-11d0-88EA-0000F80401D1}
DEFINE_GUID(IID_ASPLAYLIST, 
0xe50a8ef1, 0xccb4, 0x11d0, 0x88, 0xea, 0x0, 0x0, 0xf8, 0x4, 0x1, 0xd1);
//
// Text Input
//
// {35F77790-E456-11d0-88F2-0000F80401D1}
DEFINE_GUID(IID_ASTEXTINPUTRANGE, 
0x35f77790, 0xe456, 0x11d0, 0x88, 0xf2, 0x0, 0x0, 0xf8, 0x4, 0x1, 0xd1);
//
// Text Spinner
//
// {52FFA520-D150-11d0-88EA-0000F80401D1}
DEFINE_GUID(CLSID_ASCHARSPINNER, 
0x52ffa520, 0xd150, 0x11d0, 0x88, 0xea, 0x0, 0x0, 0xf8, 0x4, 0x1, 0xd1);
// {52FFA521-D150-11d0-88EA-0000F80401D1}
DEFINE_GUID(IID_ASCHARSPINNER, 
0x52ffa521, 0xd150, 0x11d0, 0x88, 0xea, 0x0, 0x0, 0xf8, 0x4, 0x1, 0xd1);
//
// Edit Box
//
// {59C9ACF0-D16C-11d0-88EA-0000F80401D1}
DEFINE_GUID(CLSID_ASEDITBOX, 
0x59c9acf0, 0xd16c, 0x11d0, 0x88, 0xea, 0x0, 0x0, 0xf8, 0x4, 0x1, 0xd1);
// {59C9ACF2-D16C-11d0-88EA-0000F80401D1}
DEFINE_GUID(IID_ASEDITBOX, 
0x59c9acf2, 0xd16c, 0x11d0, 0x88, 0xea, 0x0, 0x0, 0xf8, 0x4, 0x1, 0xd1);
//
// A Soft Input Pad
//
// {7EEB06E0-E38B-11d0-88F2-0000F80401D1}
DEFINE_GUID(CLSID_ASSIP, 
0x7eeb06e0, 0xe38b, 0x11d0, 0x88, 0xf2, 0x0, 0x0, 0xf8, 0x4, 0x1, 0xd1);
// {7EEB06E1-E38B-11d0-88F2-0000F80401D1}
DEFINE_GUID(IID_ASSIP, 
0x7eeb06e1, 0xe38b, 0x11d0, 0x88, 0xf2, 0x0, 0x0, 0xf8, 0x4, 0x1, 0xd1);

//
// Canvas
//
// {BD2BB900-DD38-11d0-88EE-0000F80401D1}
DEFINE_GUID(CLSID_ASCANVAS, 
0xbd2bb900, 0xdd38, 0x11d0, 0x88, 0xee, 0x0, 0x0, 0xf8, 0x4, 0x1, 0xd1);
// {BD2BB902-DD38-11d0-88EE-0000F80401D1}
DEFINE_GUID(IID_ASCANVAS, 
0xbd2bb902, 0xdd38, 0x11d0, 0x88, 0xee, 0x0, 0x0, 0xf8, 0x4, 0x1, 0xd1);
//
// Timers
//
// {80F7B570-E130-11d0-88F2-0000F80401D1}
DEFINE_GUID(CLSID_ASTIMER, 
0x80f7b570, 0xe130, 0x11d0, 0x88, 0xf2, 0x0, 0x0, 0xf8, 0x4, 0x1, 0xd1);
// {80F7B571-E130-11d0-88F2-0000F80401D1}
DEFINE_GUID(IID_ASTIMER, 
0x80f7b571, 0xe130, 0x11d0, 0x88, 0xf2, 0x0, 0x0, 0xf8, 0x4, 0x1, 0xd1);
//
// Balance Control
//
// {660CDF60-FEDC-11d0-88F6-0000F80401D1}
DEFINE_GUID(CLSID_ASCROSSHAIRS, 
0x660cdf60, 0xfedc, 0x11d0, 0x88, 0xf6, 0x0, 0x0, 0xf8, 0x4, 0x1, 0xd1);
// {660CDF61-FEDC-11d0-88F6-0000F80401D1}
DEFINE_GUID(IID_ASCROSSHAIRS, 
0x660cdf61, 0xfedc, 0x11d0, 0x88, 0xf6, 0x0, 0x0, 0xf8, 0x4, 0x1, 0xd1);
//
// Tabber Control
//
// {2D7A1BD1-457F-11d1-A1B8-00AA00B5E9D2}
DEFINE_GUID(CLSID_ASTABBER, 
0x2d7a1bd1, 0x457f, 0x11d1, 0xa1, 0xb8, 0x0, 0xaa, 0x0, 0xb5, 0xe9, 0xd2);

// {2D7A1BD2-457F-11d1-A1B8-00AA00B5E9D2}
DEFINE_GUID(IID_ASTABBER, 
0x2d7a1bd2, 0x457f, 0x11d1, 0xa1, 0xb8, 0x0, 0xaa, 0x0, 0xb5, 0xe9, 0xd2);

//
// PowerListBox Control
//
//
// {25B16883-4CF6-11d1-AE65-EBD86EB3BE67}
DEFINE_GUID(CLSID_ASPOWERLISTBOX, 
0x25b16883, 0x4cf6, 0x11d1, 0xae, 0x65, 0xeb, 0xd8, 0x6e, 0xb3, 0xbe, 0x67);

// {25B16884-4CF6-11d1-AE65-EBD86EB3BE67}
DEFINE_GUID(IID_ASPOWERLISTBOX, 
0x25b16884, 0x4cf6, 0x11d1, 0xae, 0x65, 0xeb, 0xd8, 0x6e, 0xb3, 0xbe, 0x67);

// {25B16885-4CF6-11d1-AE65-EBD86EB3BE67}
DEFINE_GUID(IID_ASPOWERLISTBOXITEM, 
0x25b16885, 0x4cf6, 0x11d1, 0xae, 0x65, 0xeb, 0xd8, 0x6e, 0xb3, 0xbe, 0x67);

// {25B16886-4CF6-11d1-AE65-EBD86EB3BE67}
DEFINE_GUID(IID_ASPOWERLISTBOXCOMMAND, 
0x25b16886, 0x4cf6, 0x11d1, 0xae, 0x65, 0xeb, 0xd8, 0x6e, 0xb3, 0xbe, 0x67);

// {25B16887-4CF6-11d1-AE65-EBD86EB3BE67}
DEFINE_GUID(IID_ASPOWERLISTBOXEDIT, 
0x25b16887, 0x4cf6, 0x11d1, 0xae, 0x65, 0xeb, 0xd8, 0x6e, 0xb3, 0xbe, 0x67);

// {25B16888-4CF6-11d1-AE65-EBD86EB3BE67}
DEFINE_GUID(IID_ASPOWERLISTBOXSTRINGSPINNER, 
0x25b16888, 0x4cf6, 0x11d1, 0xae, 0x65, 0xeb, 0xd8, 0x6e, 0xb3, 0xbe, 0x67);

// {25B16889-4CF6-11d1-AE65-EBD86EB3BE67}
DEFINE_GUID(IID_ASPOWERLISTBOXINTSPINNER, 
0x25b16889, 0x4cf6, 0x11d1, 0xae, 0x65, 0xeb, 0xd8, 0x6e, 0xb3, 0xbe, 0x67);

// {716B788F-65DE-11d1-9D25-00C04FC2981B}
DEFINE_GUID(IID_ASPROVIDEPOWERLISTBOXCOMMANDDATA, 
0x716b788f, 0x65de, 0x11d1, 0x9d, 0x25, 0x0, 0xc0, 0x4f, 0xc2, 0x98, 0x1b);

// {7C0ED1E7-0BC9-11d2-823D-0000F87A587C}
DEFINE_GUID(IID_ASPOWERLISTSPEAKITEMSINK, 
0x7c0ed1e7, 0xbc9, 0x11d2, 0x82, 0x3d, 0x0, 0x0, 0xf8, 0x7a, 0x58, 0x7c);

// {AC3CF4AD-548F-11d1-9D22-00C04FC2981B}
DEFINE_GUID(CLSID_ASPOWERMENU, 
0xac3cf4ad, 0x548f, 0x11d1, 0x9d, 0x22, 0x0, 0xc0, 0x4f, 0xc2, 0x98, 0x1b);

// {515816E0-9EE8-11d1-ABBD-00A0C911002B}
DEFINE_GUID(CLSID_ASHTMLCONTROL, 
0x515816e0, 0x9ee8, 0x11d1, 0xab, 0xbd, 0x0, 0xa0, 0xc9, 0x11, 0x0, 0x2b);

// {515816E1-9EE8-11d1-ABBD-00A0C911002B}
DEFINE_GUID(IID_ASHTMLCONTROL, 
0x515816e1, 0x9ee8, 0x11d1, 0xab, 0xbd, 0x0, 0xa0, 0xc9, 0x11, 0x0, 0x2b);

// {515816E2-9EE8-11d1-ABBD-00A0C911002B}
DEFINE_GUID(IID_ASHTMLCONTROLNOTIFYSINK, 
0x515816e2, 0x9ee8, 0x11d1, 0xab, 0xbd, 0x0, 0xa0, 0xc9, 0x11, 0x0, 0x2b);

//--------------------------------------------------------------------------------------------
//
// DISPIDs
//
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
//
// Controls
//
//--------------------------------------------------------------------------------------------

//
// LABEL
//
#undef	INTERFACE
#define	INTERFACE

#if defined(__cplusplus) && !defined(CINTERFACE)
/**
 * This interface provides methods used to assign an image to an Auto PC simple (AS) label control.
 *
 * The IASLabel interface, which has a global unique identifier equal to IID ASLABEL, extends the
 * IASControl interface. The label control has a programmatic identifier equal to APC_Label.
 */
struct IASLabel : public IASControl
#else
DECLARE_INTERFACE_(IASLabel, IASControl)
#endif
	{
    //
    // Use these to assign a user defined image to the label. However, some controls
    // that inherit from IASLabel, may choose to ignore this property
    //
    /**
     * This method retrieves a handle to the control image and image mask, allowing a bitmap to be drawn
     * on the label control.
     *
     * @param phImage [out] Pointer to the handle to a bitmap resource, cast to an OLE_HANDLE type.
     * @param phImageMask [out] Pointer to the handle to the image mask that defines the transparent
     *   parts of the image.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     *
     * This method allows a bitmap to be drawn on the label control. The image mask is an optional
     * monochrome bitmap that defines the transparent areas in the bitmap to be displayed.
     *
     * Because of Automation, bitmapped image pointers are passed as OLE_HANDLE types. You can cast a
     * handle to and from a bitmap.
     */
    STDMETHOD(get_Image) (THIS_ OLE_HANDLE *phImage, OLE_HANDLE *phImageMask) PURE;
    /**
     * This method allows a bitmapped imaged to be drawn on the control.
     *
     * @param hImage [in] Handle to a bitmap resource, cast to an OLE_HANDLE type.
     * @param hImageMask [in] Handle to a bitmap mask resource, cast to an OLE_HANDLE type.
     * @param dx [in] Specifies the x-coordinate of the left edge of the image.
     * @param dy [in] Specifies the y-coordinate of the upper edge of the image.
     * @param dxWidth [in] Specifies the width of the image.
     * @param dyHeight [in] Specifies the height of the image.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     *
     * The image mask is an optional monochrome bitmap that specifies which areas of the image are
     * transparent. It must be the same size as the image referred to by hImage. For every black pixel
     * in the mask, the corresponding pixel from hImage is drawn. White pixels are not drawn, and define
     * transparent areas in the image. This function is similar in operation to BitBlt.
     *
     * Because of Automation, bitmapped image pointers are passed as OLE_HANDLE types. You can cast a
     * handle to and from a bitmap.
     *
     * This method automatically repaints the control with the new bitmap.
     *
     * The following code example shows how to call put_Image:
     *
     *     hBmp = LoadBitmapResource(hInst, MAKEINTRESOURCE(IDB_HOUSE));
     *     hBmpMask = LoadBitmapResource(hInst, MAKEINTRESOURCE(IDB_HOUSEMASK));
     *
     *     pLabel -> put_Image((OLE_HANDLE) hBmp, (OLE_HANDLE) hBmpMask, 0, 0, 16, 16);
     */
    STDMETHOD(put_Image) (THIS_ OLE_HANDLE hImage, OLE_HANDLE hImageMask,
                            long x, long y, long dxWidth, long dyHeight) PURE;
	//
	// Properties
	//
	/**
	 * This method retrieves the text format of the label.
	 *
	 * @param pwFormat [out] Pointer to the unsigned 16-bit value that contains text formatting. It is
	 *   one of the following values: - ASFC_ALIGN_BOTTOM: When drawing text, align it with the bottom of
	 *   the control. - ASFC_ALIGN_CENTER: When drawing text, center it. - ASFC_ALIGN_LEFT: When drawing
	 *   text, align it to the left of the control. - ASFC_ALIGN_NOCLIP: Draw text without clipping it. -
	 *   ASFC_ALIGN_RIGHT: When drawing text, align it to the right of the control. -
	 *   ASFC_ALIGN_SINGLELINE: Draw text in a single line. - ASFC_ALIGN_TOP: When drawing text, align it
	 *   with the top of the control. - ASFC_ALIGN_VCENTER: When drawing text, center it vertically. -
	 *   ASFC_ALIGN_WORDBREAK: Draw text with word breaks.
	 *
	 * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
	 *
	 * By default, text wraps to the next line on a per-word basis. All carriage returns/line feeds
	 * (CR/LFs) are acknowledged. When the text reaches the edge of the region, it is clipped, with two
	 * periods appended to indicate additional undisplayed text, for example, "You have reached the
	 * en.." If the ASFC_ALIGN_NOCLIP flag is set, text still wraps, but it is clipped at the edge of
	 * the control without the periods.
	 */
	STDMETHOD(get_Format) (THIS_ UINT *pwFormat) PURE;
	/**
	 * This method changes the text format of the label.
	 *
	 * @param wFormat [in] Unsigned 16-bit value that contains text formatting. It uses the same set of
	 *   styles available with the Windows CE DrawText function, which include the following values: -
	 *   ASFC_ALIGN_BOTTOM: When drawing text, align it with the bottom of the control. -
	 *   ASFC_ALIGN_CENTER: When drawing text, center it. - ASFC_ALIGN_LEFT: When drawing text, align it
	 *   to the left of the control. - ASFC_ALIGN_NOCLIP: Draw text without clipping it. -
	 *   ASFC_ALIGN_RIGHT: When drawing text, align it to the right of the control. -
	 *   ASFC_ALIGN_SINGLELINE: Draw text in a single line. - ASFC_ALIGN_TOP: When drawing text, align it
	 *   with the top of the control. - ASFC_ALIGN_VCENTER: When drawing text, center it vertically. -
	 *   ASFC_ALIGN_WORDBREAK: Draw text with word breaks.
	 *
	 * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
	 */
	STDMETHOD(put_Format) (THIS_ UINT wFormat) PURE;
    //
    // Use these to align images and captions
    //
    /**
     * This method gets the horizontal alignment of the image.
     *
     * @param pwAlign [out] Pointer to the unsigned 16-bit value that contains alignment information. It
     *   is one of the following values: - ASFC_IMAGE_HCENTER: Image is centered. - ASFC_IMAGE_LEFT: Image
     *   is left-aligned. - ASFC_IMAGE_RIGHT: Image is right-aligned.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     */
    STDMETHOD(get_ImageAlignH) (THIS_ short *pwAlign) PURE;
    /**
     * This method sets the horizontal alignment of the image.
     *
     * @param wAlign [in] Unsigned 16-bit value that contains alignment information. It is one of the
     *   following values: - ASFC_IMAGE_HCENTER: Image is centered. - ASFC_IMAGE_LEFT: Image is
     *   left-aligned. - ASFC_IMAGE_RIGHT: Image is right-aligned.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     */
    STDMETHOD(put_ImageAlignH) (THIS_ short wAlign) PURE;
    /**
     * This method gets the vertical alignment of the image.
     *
     * @param pwAlign [out] Pointer to the unsigned 16-bit value that contains alignment information. It
     *   is one of the following values: - ASFC_IMAGE_VCENTER: Image is centered vertically. -
     *   ASFC_IMAGE_TOP: Image is aligned with the top. - ASFC_IMAGE_BOTTOM: Image is aligned with the
     *   bottom.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     */
    STDMETHOD(get_ImageAlignV) (THIS_ short *pwAlign) PURE;
    /**
     * This method sets the vertical alignment of the image.
     *
     * @param wAlign [in] Unsigned 16-bit value that contains alignment information. It is one of the
     *   following values: - ASFC_IMAGE_VCENTER: Image is centered vertically. - ASFC_IMAGE_TOP: Image is
     *   aligned with the top. - ASFC_IMAGE_BOTTOM: Image is aligned with the bottom.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     */
    STDMETHOD(put_ImageAlignV) (THIS_ short wAlign) PURE;
    /**
     * This method gets the caption alignment.
     *
     * @param pwAlign [out] Pointer to the unsigned 16-bit value that contains alignment information. It
     *   is one of the following values: - ASFC_CAPTION_ALIGNNONE: Caption extends from the top of the
     *   control to the bottom. - ASFC_CAPTION_ALIGNTOP: Caption aligns with the top of the image. -
     *   ASFC_CAPTION_ALIGNBOTTOM: Caption aligns with the bottom of the image.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     */
    STDMETHOD(get_CaptionAlign) (THIS_ short *pwAlign) PURE;
    /**
     * This method sets the caption alignment.
     *
     * @param wAlign [in] Unsigned 16-bit value that contains alignment information. It is one of the
     *   following values: - ASFC_CAPTION_ALIGNNONE: Caption extends from the top of the control to the
     *   bottom. - ASFC_CAPTION_ALIGNTOP: Caption aligns with the top of the image. -
     *   ASFC_CAPTION_ALIGNBOTTOM: Caption aligns with the bottom of the image.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     */
    STDMETHOD(put_CaptionAlign) (THIS_ short wAlign) PURE;

	STDMETHOD(get_AutoScaleFont) (THIS_ UINT *pwMinPointSize) PURE;
	STDMETHOD(put_AutoScaleFont) (THIS_ UINT wMinPointSize) PURE;
	};

//
// BUTTON
//
#undef  INTERFACE
#define INTERFACE

DECLARE_INTERFACE_(IASButton, IASLabel)
    {
    STDMETHOD(PushButton) (THIS) PURE;
    //
    // Properties
    //
    STDMETHOD(get_Pushed) (THIS_ BOOL *pfPushed) PURE;
    STDMETHOD(put_Pushed) (THIS_ BOOL fPushed) PURE;
   
    STDMETHOD(get_Group) (THIS_ short *pwIDGroup) PURE;
    STDMETHOD(put_Group) (THIS_ short wIDGroup) PURE;
    //
    // Use these to change button behaviour
    //
    STDMETHOD(get_Type) (THIS_ short *pwType) PURE;
    STDMETHOD(put_Type) (THIS_ short wType) PURE;
    };

//
// Check Box
//
#undef  INTERFACE
#define INTERFACE

DECLARE_INTERFACE_(IASCheckBox, IASButton)
    {
    };

//
// Radio Button
//
#undef  INTERFACE
#define INTERFACE

DECLARE_INTERFACE_(IASRadioButton, IASButton)
    {
    };

//
// A ListBox of BSTRs
//
#undef  INTERFACE
#define INTERFACE

DECLARE_INTERFACE_(IASListBox, IASControl)
    {
	STDMETHOD(get_Count) (THIS_ long *pcItems) PURE;
	STDMETHOD(Item) (THIS_ long index, BSTR *pbstr) PURE;
    STDMETHOD(FindItem) (THIS_ BSTR bstr, long indexStart, long *plIndex) PURE;
    STDMETHOD(FindItemPartial) (THIS_ BSTR bstr, long indexStart, long *plIndex) PURE;
    STDMETHOD(SetItemData) (THIS_ long index, long lData) PURE;
    STDMETHOD(GetItemData) (THIS_ long index, long* plData) PURE;
    
    STDMETHOD(Add) (THIS_ BSTR bstr) PURE;
    STDMETHOD(AddWithData) (THIS_ BSTR bstr, long lData) PURE;
    STDMETHOD(InsertAt) (THIS_ long index, BSTR bstr) PURE;
    STDMETHOD(SetItem) (THIS_ long index, BSTR bstr) PURE;
    STDMETHOD(Remove) (THIS_ BSTR bstr) PURE;
    STDMETHOD(RemoveAtIndex) (THIS_ long index) PURE;
	STDMETHOD(RemoveAll) (THIS) PURE;

    STDMETHOD(get_TabStopCount) (THIS_ long *pcStops) PURE;
    STDMETHOD(put_TabStopCount) (THIS_ long cStops) PURE;
	STDMETHOD(get_TabStop) (THIS_ long index, long* pStop) PURE;
	STDMETHOD(put_TabStop) (THIS_ long index, long stop) PURE;
	STDMETHOD(get_TabStopAlignment) (THIS_ long index, short *pwAlign) PURE;
	STDMETHOD(put_TabStopAlignment) (THIS_ long index, short wAlign) PURE;
	STDMETHOD(get_TabStopForeColor) (THIS_ long index, OLE_COLOR *pclr) PURE;
	STDMETHOD(put_TabStopForeColor) (THIS_ long index, OLE_COLOR clr) PURE;
	STDMETHOD(get_TabStopBackColor) (THIS_ long index, OLE_COLOR *pclr) PURE;
	STDMETHOD(put_TabStopBackColor) (THIS_ long index, OLE_COLOR clr) PURE;


    STDMETHOD(get_FocusIndex) (THIS_ long *plIndex) PURE;
    STDMETHOD(put_FocusIndex) (THIS_ long lIndex) PURE;
    STDMETHOD(get_TopVisibleIndex) (THIS_ long *plIndex) PURE;
    STDMETHOD(put_TopVisibleIndex) (THIS_ long lIndex) PURE;
    
    STDMETHOD(get_ItemHeight) (THIS_ long *plHeight) PURE;
    STDMETHOD(put_ItemHeight) (THIS_ long lHeight) PURE;

    STDMETHOD(get_Sorted) (THIS_ BOOL *pfSorted) PURE;
    STDMETHOD(put_Sorted) (THIS_ BOOL fSorted) PURE;
    STDMETHOD(get_SortOrder) (THIS_ BOOL *pfAscending) PURE;
    STDMETHOD(put_SortOrder) (THIS_ BOOL fAscending) PURE;

    STDMETHOD(get_CenteredFocus) (THIS_ BOOL *pfFocus) PURE;
    STDMETHOD(put_CenteredFocus) (THIS_ BOOL fFocus) PURE;
    STDMETHOD(get_ItemBorder) (THIS_ BOOL *pfItemBorder) PURE;
    STDMETHOD(put_ItemBorder) (THIS_ BOOL fItemBorder) PURE;

	STDMETHOD(get_HiliteColor) (THIS_ OLE_COLOR *pclr) PURE;
	STDMETHOD(put_HiliteColor) (THIS_ OLE_COLOR clr) PURE;
	STDMETHOD(get_HiliteTextColor) (THIS_ OLE_COLOR *pclr) PURE;
	STDMETHOD(put_HiliteTextColor) (THIS_ OLE_COLOR clr) PURE;
	STDMETHOD(get_ItemBorderColor) (THIS_ OLE_COLOR *pclr) PURE;
	STDMETHOD(put_ItemBorderColor) (THIS_ OLE_COLOR clr) PURE;



    };

//
// A MENU
//
#undef  INTERFACE
#define INTERFACE

DECLARE_INTERFACE_(IASMenu, IASControl)
    {
	STDMETHOD(get_Count) (THIS_ long *pcItems) PURE;
	
    STDMETHOD(GetString) (THIS_ long index, BSTR *pbstr) PURE;
    STDMETHOD(SetString) (THIS_ long index, BSTR bstr) PURE;

    STDMETHOD(GetID) (THIS_ long index, short *pwID) PURE;
    STDMETHOD(SetID) (THIS_ long index, short wID) PURE;

    STDMETHOD(Add) (THIS_ BSTR bstr, short wID) PURE;
    STDMETHOD(InsertAt) (THIS_ long index, BSTR bstr, short wID) PURE;
    STDMETHOD(RemoveAtIndex) (THIS_ long index) PURE;
    STDMETHOD(RemoveByID) (THIS_ short wID) PURE;
    STDMETHOD(RemoveAll) (THIS_ BOOL fRedraw) PURE;

    STDMETHOD(get_FocusIndex) (THIS_ long *plIndex) PURE;
    STDMETHOD(put_FocusIndex) (THIS_ long lIndex) PURE;
    STDMETHOD(get_ItemHeight) (THIS_ long *plHeight) PURE;
    STDMETHOD(put_ItemHeight) (THIS_ long lHeight) PURE;
    };

//
// A List Box of Images
//
#undef  INTERFACE
#define INTERFACE

#if defined(__cplusplus) && !defined(CINTERFACE)
/**
 * This interface provides methods to manage a menu that uses images rather than text strings to
 * display its options.
 *
 * The IASImageMenu interface, which has a global unique identifier (GUID) equal to IID_ASIMAGEMENU,
 * extends the IASControl interface.
 *
 * When an image item is selected, a WM_COMMAND event is sent to the event sink. The high-order word
 * contains the control's identifier and the low-order word contains the item's identifier. The
 * index of the menu item is sent in the lParam. When the focus changes from one item to the next, a
 * WM_COMMAND message is fired to the event sink. The high-order word of wParam contains
 * LBN_SELCHANGE, and the low-order word contains the control's identifier.
 */
struct IASImageMenu : public IASControl
#else
DECLARE_INTERFACE_(IASImageMenu, IASControl)
#endif
    {
	/**
	 * This method gets the number of items in the menu.
	 *
	 * @param pcItems [out] Pointer to the number of items.
	 *
	 * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
	 */
	STDMETHOD(get_Count) (THIS_ long *pcItems) PURE;
	
    /**
     * This method gets the image associated with a menu item, specified by its menu index.
     *
     * @param index [in] Index of the item associated with the image.
     * @param phImage [out] Pointer to a handle to an image.
     * @param phImageMask [out] Pointer to the handle to the image mask. Masks are not needed for icons.
     * @param pfBitmap [out] Pointer to a Boolean that is set to TRUE if the image is a bitmap, or to
     *   FALSE if it is an icon.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     *
     * Images may be either bitmaps or icons. If the images are bitmaps, a mask must also be supplied.
     */
    STDMETHOD(get_Image) (THIS_ long index, OLE_HANDLE *phImage, OLE_HANDLE *phImageMask, 
                        BOOL *pfBitmap) PURE;
    /**
     * This method replaces one item image with another.
     *
     * @param index [in] Index of the item whose image is replaced.
     * @param hImage [in] Handle to the new image.
     * @param hImageMask [in] Handle to the image mask. Masks are not needed for icons.
     * @param fBitmap [in] Boolean that is set to TRUE if the image is a bitmap, or to FALSE if it is an
     *   icon.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     *   E_OUTOFMEMORY indicates that the device is out of memory.
     *
     * Images may be either bitmaps or icons. If the images are bitmaps, a mask must also be supplied.
     */
    STDMETHOD(put_Image) (THIS_ long index, OLE_HANDLE hImage, OLE_HANDLE hImageMask,  
                        BOOL fBitmap) PURE;

    /**
     * This method gets the string associated with a menu item.
     *
     * @param index [in] Index of the item associated with the image.
     * @param pbstr [out] Pointer to the Unicode string.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     *
     * The string associated with an image can be used to display text in the Auto PC label control
     * associated with the image menu.
     */
    STDMETHOD(get_String) (THIS_ long index, BSTR *pbstr) PURE;
    /**
     * This method assigns a string to an item.
     *
     * @param index [in] Index of the item.
     * @param bstr [in] Unicode string to be assigned.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     *
     * The string associated with an image can be used to display text in the Auto PC label control
     * associated with the image menu.
     */
    STDMETHOD(put_String) (THIS_ long index, BSTR bstr) PURE;

    /**
     * This method gets the identifier of a menu item, specified by its index.
     *
     * @param index [in] Index of the item.
     * @param pwID [out] Pointer to the user-defined item identifier.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     *
     * The index is based on the order in which the menu items are displayed. The identifier is assigned
     * by the user when the item is added to the menu.
     */
    STDMETHOD(get_ID) (THIS_ long index, short *pwID) PURE;
    /**
     * This method sets the identifier for a menu item.
     *
     * @param index [in] Index of the item.
     * @param wID [in] User-defined item identifier.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     */
    STDMETHOD(put_ID) (THIS_ long index, short wID) PURE;

    /**
     * This method adds an item and its associated image to the image menu.
     *
     * @param hImage [in] Handle to the image to be added to the menu.
     * @param hImageMask [in] Handle to the image mask. Masks are not needed for icons.
     * @param bstr [in] Unicode string to be associated with the image.
     * @param wID [in] User-defined item identifier.
     * @param fBitmap [in] Boolean that is set to TRUE if the image is a bitmap, or to FALSE if it is an
     *   icon.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     *   E_OUTOFMEMORY indicates that the device is out of memory.
     *
     * Images may be either bitmaps or icons. If the images are bitmaps, a mask must also be supplied.
     */
    STDMETHOD(Add) (THIS_ OLE_HANDLE hImage, OLE_HANDLE hImageMask, BSTR bstr, 
                    short wID, BOOL fBitmap) PURE;
    /**
     * This method inserts an item at a specified index.
     *
     * @param index [in] Index where the item is to be inserted.
     * @param hImage [in] Handle to the image to be added to the menu.
     * @param hImageMask [in] Handle to the image mask. Masks are not needed for icons.
     * @param bstr [in] Unicode string to be associated with the image.
     * @param wID [in] User-defined item identifier.
     * @param fBitmap [in] Boolean that is set to TRUE if the image is a bitmap, or to FALSE if it is an
     *   icon.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     *   E_OUTOFMEMORY indicates that the device is out of memory.
     *
     * Images may be either bitmaps or icons. If the images are bitmaps, a mask must also be supplied.
     */
    STDMETHOD(InsertAt) (THIS_ long index, OLE_HANDLE hImage, OLE_HANDLE hImageMask, 
                        BSTR bstr, short wID, BOOL fBitmap) PURE;
    /**
     * This method removes an item specified by its index.
     *
     * @param index [in] Index of the item to be removed.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     */
    STDMETHOD(RemoveAtIndex) (THIS_ long index) PURE;
    /**
     * This method removes an item specified by its identifier.
     *
     * @param wID [in] User-defined image identifier.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     */
    STDMETHOD(RemoveByID) (THIS_ short wID) PURE;

    /**
     * This method gets the index of the item with the focus.
     *
     * @param pIndex [out] Pointer to the index of the item that has focus.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     */
    STDMETHOD(get_FocusIndex) (THIS_ long *plIndex) PURE;
    /**
     * This method gives the focus to the item with the specified index.
     *
     * @param lIndex [in] Long integer that contains the index of the item to receive focus.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     */
    STDMETHOD(put_FocusIndex) (THIS_ long lIndex) PURE;

    /**
     * This method gets the height of an item.
     *
     * @param plHeight [out] Pointer to the long integer that contains the height of an item.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     *
     * All items must be the same height. Images are centered inside the box that constitutes the menu
     * item.
     */
    STDMETHOD(get_ItemHeight) (THIS_ long *plHeight) PURE;
    /**
     * This method sets the height of an item.
     *
     * @param lHeight [in] Long integer that contains the height of an item.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     *
     * All items must be the same height. Images are centered inside the box that constitutes the menu
     * item.
     */
    STDMETHOD(put_ItemHeight) (THIS_ long lHeight) PURE;
    /**
     * This method gets the width of an item.
     *
     * @param plWidth [out] Pointer to the long integer that contains the width of an item.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     *
     * All items must be the same size. Images are centered inside the box that constitutes the menu
     * item.
     */
    STDMETHOD(get_ItemWidth) (THIS_ long *plWidth) PURE;
    /**
     * This method sets the width of an item.
     *
     * @param lWidth [in] Long integer that contains the width of an item.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     *
     * All items must have the same width. Images are centered inside the box that constitutes the menu
     * item.
     */
    STDMETHOD(put_ItemWidth) (THIS_ long lWidth) PURE;
    /**
     * This method gets the height of an image.
     *
     * @param plHeight [out] Pointer to the long integer that contains the height of an image.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     *
     * All images in the menu must be the same height. Images are centered inside the box that
     * constitutes the menu item.
     */
    STDMETHOD(get_ImageHeight) (THIS_ long *plHeight) PURE;
    /**
     * This method sets the height of an image.
     *
     * @param lHeight [in] Long integer that contains the height of an image.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     *
     * All images in the menu must be the same height. Images are centered inside the box that
     * constitutes the menu item.
     */
    STDMETHOD(put_ImageHeight) (THIS_ long lHeight) PURE;
    /**
     * This method gets the width of an image.
     *
     * @param plWidth [out] Pointer to the long integer that contains the width of an image.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     *
     * All images in a menu must have the same width. Images are centered inside the box that
     * constitutes the menu item.
     */
    STDMETHOD(get_ImageWidth) (THIS_ long *plWidth) PURE;
    /**
     * This method sets the width of an image.
     *
     * @param lWidth [in] Long integer that contains the width of an image.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     *
     * All images in a menu must have the same width. Images are centered inside the box that
     * constitutes the menu item.
     */
    STDMETHOD(put_ImageWidth) (THIS_ long lWidth) PURE;

    /**
     * This method retrieves whether the menu scrolls horizontally or vertically.
     *
     * @param pfHorizontal [out] Pointer to a Boolean that is set to TRUE for horizontal scrolling, or
     *   to FALSE for vertical scrolling.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     */
    STDMETHOD(get_Horizontal) (THIS_ BOOL *pfHorizontal) PURE;
    /**
     * This method sets scrolling to horizontal or vertical.
     *
     * @param fHorizontal [in] Boolean that is set to TRUE for horizontal scrolling, or to FALSE for
     *   vertical scrolling
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(put_Horizontal) (THIS_ BOOL fHorizontal) PURE;

    /**
     * This method gets the Auto PC label control associated with the image menu.
     *
     * @param ppdispLabel [out] Pointer to a pointer to the label control that displays the menu's
     *   label.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     *
     * The label for the menu is displayed in a separate AS label control, which may be placed anywhere
     * on the faceplate screen.
     */
    STDMETHOD(get_MenuLabel) (THIS_ IDispatch **ppdispLabel) PURE;
    /**
     * This method specifies an Auto PC label control to be associated with the image menu.
     *
     * @param pdispLabel [in] Pointer to an AS label control to be used as the label field.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     *
     * The label is displayed in a separate AS label control, which may be placed anywhere on the
     * faceplate screen. The control must have been created prior to the invocation of this method.
     */
    STDMETHOD(put_MenuLabel) (THIS_ IDispatch *pdispLabel) PURE;

	/**
	 * This method gets the color assigned to an image that has the focus.
	 *
	 * @param pclr Pointer to the color assigned to an image with focus.
	 *
	 * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
	 *
	 * Use the GetRValue, GetGValue, and GetBValue macros to get the color components of pclr.
	 */
	STDMETHOD(get_FocusColor) (THIS_ OLE_COLOR *pclr) PURE;
	/**
	 * This method sets the color assigned to an image that has the focus.
	 *
	 * @param clr [in] Color for the focused image.
	 *
	 * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
	 *
	 * Use the RGB macro to set the components of clr before passing clr to the method.
	 */
	STDMETHOD(put_FocusColor) (THIS_ OLE_COLOR clr) PURE;

    /**
     * This method retrieves whether or not centered focus is enabled.
     *
     * @param pfFocus [out] Pointer to a Boolean that is set to TRUE if centered focus is enabled, or to
     *   FALSE if not.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     */
    STDMETHOD(get_CenteredFocus) (THIS_ BOOL *pfFocus) PURE;
    /**
     * This method sets whether or not centered focus is enabled.
     *
     * @param fFocus [in] Boolean that is set to TRUE if centered focus is to be enabled, or to FALSE if
     *   not.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     */
    STDMETHOD(put_CenteredFocus) (THIS_ BOOL fFocus) PURE;

    /**
     * This method sets an image to display over a focus item or the entire image menu.
     *
     * @param fFocus Boolean that is set to TRUE if the image has the focus, and to FALSE if the image
     *   does not have the focus.
     * @param hImage [in] Handle to the image bitmap.
     * @param hImageMask [in] Handle to the image mask. Masks are not needed for icons.
     * @param fBitmap [in] Boolean that is set to TRUE if the image is a bitmap, or to FALSE if it is an
     *   icon.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     */
    STDMETHOD(put_Overlay)(THIS_ BOOL fFocus, THIS_ OLE_HANDLE hImage, 
                                 OLE_HANDLE hImageMask, BOOL fBitmap) PURE;

    /**
     * This method gets an image to display over a focus item or the entire image menu.
     *
     * @param fFocus Boolean that is set to TRUE if the image has the focus, or to FALSE if the image
     *   does not have the focus.
     * @param phImage [out] Pointer to the handle to the image bitmap.
     * @param phImageMask [out] Pointer to the handle to the image mask. Masks are not needed for icons.
     * @param pfBitmap [out] Pointer to a Boolean that is set to TRUE if the image is a bitmap, or to
     *   FALSE if it is an icon.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     */
    STDMETHOD(get_Overlay)(THIS_ BOOL fFocus, THIS_ OLE_HANDLE * phImage, 
                                 OLE_HANDLE * phImageMask, BOOL * pfBitmap) PURE;  

    /**
     * This method sets the color for an non-focused image.
     *
     * @param clr [in] Color for the non-focused image.
     * @param fSet Boolean that is set to TRUE if the image does not have the focus, or to FALSE is the
     *   image has the focus.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     *
     * This method produces a single color version of an image for non-focused applications.
     *
     * Use the RGB macro to set the components of clr before passing clr to the method.
     */
    STDMETHOD(put_NonFocusImageColor)(THIS_ OLE_COLOR clr, BOOL fSet) PURE;
    /**
     * This method gets the color assigned to a non-focused image.
     *
     * @param pclr Pointer to the icon color.
     * @param pfSet Pointer to a Boolean that is set to TRUE if the image does not have the focus, and
     *   to FALSE if the image has the focus.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     *
     * This method retrieves single color version of non-focused images.
     *
     * Use the GetRValue, GetGValue, and GetBValue macros to get the color components of pclr.
     */
    STDMETHOD(get_NonFocusImageColor)(THIS_ OLE_COLOR * pclr, BOOL * pfSet) PURE;

    /**
     * This method sets the position of the overlay.
     *
     * @param fFocus Boolean that is set to TRUE if image has focus, or to FALSE if image does not have
     *   focus.
     * @param left [in] Specifies the x-coordinate (left edge) of the overlay.
     * @param top [in] Specifies the y-coordinate (upper edge) of the overlay.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     */
    STDMETHOD(put_OverlayOffset)(THIS_ BOOL fFocus, long left, long top) PURE;
    /**
     * This method gets pointers to the position of the overlay.
     *
     * @param fFocus Boolean that is set to TRUE if the image has the focus, or to false if the image
     *   does not have the focus.
     * @param pleft [out] Pointer to the x-coordinate of the left edge of the overlay.
     * @param ptop [out] Pointer to the y-coordinate of the upper edge of the overlay.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     */
    STDMETHOD(get_OverlayOffset)(THIS_ BOOL fFocus, long * pleft, long * ptop ) PURE;
                                 
    /**
     * This method retrieves whether or not the menu should wrap at the end of a line of text.
     *
     * @param pfWrap [out] Pointer to a Boolean that is set to TRUE if the menu should wrap, or to FALSE
     *   if the menu should not wrap.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     */
    STDMETHOD(get_MenuWrap) (THIS_ BOOL *pfWrap) PURE;
    /**
     * This method sets whether or not the menu should wrap.
     *
     * @param fWrap [in] Boolean that is set to TRUE if menu should wrap, or to FALSE if menu should not
     *   wrap.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     */
    STDMETHOD(put_MenuWrap) (THIS_ BOOL fWrap) PURE;
   };

#undef  INTERFACE
#define INTERFACE

#if defined(__cplusplus) && !defined(CINTERFACE)
/**
 * This interface provides the methods to manage a shell menu object.
 *
 * The IASShellMenu interface, which has a global unique identifier (GUID) equal to IID_ASSHELLMENU,
 * extends the IASImageMenu interface. It is used to implement the Auto PC shell user interface
 * (UI). When an item is selected from a shell menu, a WM_COMMAND event is fired to the event sink.
 * The high-order word contains the control's identifier, and the low-order word contains the item's
 * identifier. The index of the menu item is sent in lParam. When the focus changes from one item to
 * the next, a WM_COMMAND message is fired to the event sink. LBN_SELCHANGE is in the high-order
 * word of wParam, and the control's identifier is in the low-order word.
 */
struct IASShellMenu : public IASImageMenu
#else
DECLARE_INTERFACE_(IASShellMenu, IASImageMenu)
#endif
    {
    /**
     * This method gets the hot key associated with a shell menu item.
     *
     * @param index Index of the item.
     * @param pbID Pointer to the hot key code identifier. The value of the identifier is between 0 and
     *   255.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
     *   entered.
     *
     * Hot keys are numbers, entered through the keypad, that provide a direct link to a menu item. If a
     * hot key is detected, focus is set to that menu item, and a WM_COMMAND is fired to the event sink.
     */
    STDMETHOD(get_HotKey) (THIS_ long index, unsigned char *pbID) PURE;
    /**
     * This method assigns a hot key to a shell menu item.
     *
     * @param index Index of the item.
     * @param bID Hot key code identifier, a value between 0 and 255.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
     *   entered.
     *
     * Hot keys are numbers, entered through the keypad, that provide a direct link to a menu item. If a
     * hot key is detected, focus is set to that menu item, and a WM_COMMAND is fired to the event sink.
     *
     * This method assigns a hot key value to a menu item. In horizontal display, the value appears
     * above the item on the screen.
     */
    STDMETHOD(put_HotKey) (THIS_ long index, unsigned char bID) PURE;

    /**
     * This method gets the flags associated with a shell menu item.
     *
     * @param index Index of the item.
     * @param pbFlags Pointer to item flags. Currently, the only supported flag is
     *   ASFC_IMAGEMENU_OVERLAY.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
     *   entered.
     */
    STDMETHOD(get_ItemFlags) (THIS_ long index, unsigned char *pbFlags) PURE;
    /**
     * This method sets the flags for the specified item.
     *
     * @param index Index of the item.
     * @param bFlags Item flags. This flag must be ASFC_IMAGEMENU_OVERLAY.
     * @param bMask Flag mask.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
     *   entered.
     */
    STDMETHOD(put_ItemFlags) (THIS_ long index, unsigned char bFlags, unsigned char bMask) PURE;

    /**
     * This method gets the label height.
     *
     * @param plHeight Pointer to a long integer that contains the height of the label.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(get_LabelHeight) (THIS_ long *plHeight) PURE;
    /**
     * This method sets the label height.
     *
     * @param lHeight Long integer that contains the height of the label.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
     *   entered.
     */
    STDMETHOD(put_LabelHeight) (THIS_ long lHeight) PURE;

	/**
	 * This method gets the label foreground color.
	 *
	 * @param pclr Pointer to the label foreground color.
	 *
	 * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
	 *   entered.
	 *
	 * Use the GetRValue, GetGValue, and GetBValue macros to get the color components of pclr.
	 */
	STDMETHOD(get_LabelForeColor) (THIS_ OLE_COLOR *pclr) PURE;
	/**
	 * This method sets the label foreground color.
	 *
	 * @param clr Label foreground color.
	 *
	 * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
	 *   entered.
	 *
	 * Use the RGB macro to set the components of clr before passing clr to the method.
	 */
	STDMETHOD(put_LabelForeColor) (THIS_ OLE_COLOR clr) PURE;

	/**
	 * This method gets the label background color.
	 *
	 * @param pclr Pointer to the label background color.
	 *
	 * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
	 *   entered.
	 *
	 * Use the GetRValue, GetGValue, and GetBValue macros to get the color components of pclr.
	 */
	STDMETHOD(get_LabelBackColor) (THIS_ OLE_COLOR *pclr) PURE;
	/**
	 * This method sets the label background color.
	 *
	 * @param clr Label background color.
	 *
	 * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
	 *   entered.
	 *
	 * Use the RGB macro to set the components of clr before passing clr to the method.
	 */
	STDMETHOD(put_LabelBackColor) (THIS_ OLE_COLOR clr) PURE;	
    };

#undef  INTERFACE
#define INTERFACE

#if defined(__cplusplus) && !defined(CINTERFACE)
/**
 * This interface provides the methods to manage a progress bar.
 *
 * The IASProgressBar interface, which has a global unique identifier (GUID) equal to
 * IID_ASPROGRESSBAR, extends the IASControl interface. The progress bar has a programmatic
 * identifier equal to APC_Progress.
 */
struct IASProgressBar : public IASControl
#else
DECLARE_INTERFACE_(IASProgressBar, IASControl)
#endif
    {
    /**
     * This method gets the current value associated with the progress bar.
     *
     * @param plValue Pointer to a long integer that contains the current value of the progress bar.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
     *   entered.
     */
    STDMETHOD(get_Value) (THIS_ long *plValue) PURE;
    /**
     * This method sets the current value of the progress bar.
     *
     * @param lValue Long integer the specifies the current value associated with the progress bar.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
     *   entered.
     */
    STDMETHOD(put_Value) (THIS_ long lValue) PURE;    
    /**
     * This method gets the minimum value of the progress bar.
     *
     * @param plMin Pointer to a long integer that contains the minimum value of the progress bar.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
     *   entered.
     */
    STDMETHOD(get_Min) (THIS_ long *plMin) PURE;
    /**
     * This method sets the minimum value of the progress bar.
     *
     * @param lMin Long integer that specifies the minimum value of the progress bar.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
     *   entered.
     *
     * If you set the minimum value of the progress bar to a value that is greater than the current
     * maximum value of the progress bar, the maximum value of the progress bar is reset to the value
     * specified for the minimum value of the progress bar.
     */
    STDMETHOD(put_Min) (THIS_ long lMin) PURE;
    /**
     * This method gets the maximum value of the progress bar.
     *
     * @param plMax Pointer to a long integer that contains the maximum value of the progress bar.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
     *   entered.
     */
    STDMETHOD(get_Max) (THIS_ long *plMax) PURE;
    /**
     * This method sets the maximum value of the progress bar.
     *
     * @param lMax Long integer that specifies the maximum value of the progress bar.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
     *   entered.
     *
     * If you set the maximum value of the progress bar to a value that is less than the current minimum
     * value of the progress bar, the minimum value of the progress bar is reset to the value specified
     * for the maximum value of the progress bar.
     */
    STDMETHOD(put_Max) (THIS_ long lMax) PURE;

    /**
     * This method gets the current number of ranges.
     *
     * @param plCount Pointer to a long integer that contains the number of ranges that the progress bar
     *   is divided into.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
     *   entered.
     *
     * Progress bars can be broken into two or more ranges, each of a different color. For example, if a
     * progress bar can take a value between 0 and 10 and is divided into three ranges: red, green, and
     * blue, then the RangeCount property is 3, and the related properties are listed in the following
     * table.
     *
     * Index Color RangeValue Range 0 Red 0 0 - 3 1 Green 4 4 - 7 2 Blue 8 8-10
     */
    STDMETHOD(get_RangeCount) (THIS_ long *plCount) PURE;
    /**
     * This method gets the current number of ranges.
     *
     * @param lCount Long integer that specifies the number of ranges that the progress bar is divided
     *   into.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
     *   entered.
     *
     * Progress bars can be broken into two or more ranges, each of a different color. For example, if a
     * progress bar can take a value between 0 and 10 and is divided into three ranges: red, green, and
     * blue, then the RangeCount property is 3, and the related properties are listed in the following
     * table.
     *
     * Index Color RangeValue Range 0 Red 0 0 - 3 1 Green 4 4 - 7 2 Blue 8 8-10
     */
    STDMETHOD(put_RangeCount) (THIS_ long lCount) PURE;

    /**
     * This method gets the starting value for the specified range.
     *
     * @param lRangeIndex Long integer that indicates the index of the desired range.
     * @param plRangeValue Pointer to a long integer that contains the starting value for the specified
     *   range.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
     *   entered.
     *
     * Progress bars can be broken into two or more ranges, each of a different color. For example, if a
     * progress bar can take a value between 0 and 10 and is divided into three ranges: red, green, and
     * blue, then the RangeCount property is 3, and the related properties are listed in the following
     * table.
     *
     * Index Color RangeValue Range 0 Red 0 0 - 3 1 Green 4 4 - 7 2 Blue 8 8-10
     */
    STDMETHOD(get_RangeValue) (THIS_ long lRangeIndex, long *plValue) PURE;
    /**
     * This method sets the starting value for a specified range.
     *
     * @param lRangeIndex Long integer that specifies the index of the desired range.
     * @param lRangeValue Long integer that specifies the starting value for the specified range.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
     *   entered.
     *
     * Progress bars can be broken into two or more ranges, each of a different color. For example, if a
     * progress bar can take a value between 0 and 10 and is divided into three ranges: red, green, and
     * blue, then the RangeCount property is 3, and the related properties are listed in the following
     * table.
     *
     * Index Color RangeValue Range 0 Red 0 0 - 3 1 Green 4 4 - 7 2 Blue 8 8-10
     */
    STDMETHOD(put_RangeValue) (THIS_ long lRangeIndex, long lValue) PURE;

    /**
     * This method gets the color assigned to a range.
     *
     * @param lRangeIndex Long integer that indicates the index of the desired range.
     * @param pclr Pointer to the range color.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
     *   entered.
     *
     * Progress bars can be broken into two or more ranges, each of a different color. For example, if a
     * progress bar can take a value between 0 and 10 and is divided into three ranges: red, green, and
     * blue, then the RangeCount property is 3, and the related properties are listed in the following
     * table.
     *
     * Index Color RangeValue Range 0 Red 0 0 - 3 1 Green 4 4 - 7 2 Blue 8 8-10
     *
     * Use the GetRValue, GetGValue, and GetBValue macros to get the color components of pclr.
     */
    STDMETHOD(get_RangeColor) (THIS_ long lRangeIndex, OLE_COLOR *pclr) PURE;
    /**
     * This method sets the color assigned to a range.
     *
     * @param lRangeIndex Long integer that indicates the index of the desired range.
     * @param clr Range color.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
     *   entered.
     *
     * Progress bars can be broken into two or more ranges, each of a different color. For example, if a
     * progress bar can take a value between 0 and 10 and is divided into three ranges: red, green, and
     * blue, then the RangeCount property is 3, and the related properties are listed in the following
     * table.
     *
     * Index Color RangeValue Range 0 Red 0 0 - 3 1 Green 4 4 - 7 2 Blue 8 8-10
     *
     * Use the RGB macro to set the components of clr before passing clr to the method.
     */
    STDMETHOD(put_RangeColor) (THIS_ long lRangeIndex, OLE_COLOR clr) PURE;

    /**
     * This method determines whether the progress bar is horizontal or vertical. The IASProgressBar
     * interface does not implement this method; it is implemented by IASSlider, which derives from
     * IASProgressBar.
     *
     * @param pfHorizontal Pointer to a Boolean that is set to TRUE for a horizontal bar, or to FALSE
     *   for a vertical bar.
     *
     * @return NOERROR indicates success. E_NOTIMPL indicates that this interface does not implement the
     *   get_Horizontal method.
     */
    STDMETHOD(get_Horizontal) (THIS_ BOOL *pfHorizontal) PURE;
    /**
     * This method specifies whether the progress bar is horizontal or vertical. The IASProgressBar
     * interface does not implement this method; it is implemented by IASSlider, which derives from
     * IASProgressBar.
     *
     * @param fHorizontal Boolean that is set to TRUE for a horizontal bar, or to FALSE for a vertical
     *   bar.
     *
     * @return E_NOTIMPL indicates that this interface does not implement the put_Horizontal method.
     */
    STDMETHOD(put_Horizontal) (THIS_ BOOL fHorizontal) PURE;

	/**
	 * This method gets the number of divisions for the progress bar.
	 *
	 * @param plStep Pointer to a long integer that contains the step value of the progress bar.
	 *
	 * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
	 *   entered.
	 */
	STDMETHOD(get_Steps)(THIS_ long *plSteps) PURE;
	/**
	 * This method sets the number of divisions for the progress bar.
	 *
	 * @param lStep Long integer that specifies the step value of the progress bar.
	 *
	 * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
	 *   entered.
	 */
	STDMETHOD(put_Steps)(THIS_ long lSteps) PURE;

    };

#undef  INTERFACE
#define INTERFACE

#if defined(__cplusplus) && !defined(CINTERFACE)
/**
 * This interface provides the methods to manage Auto PC simple (AS) slider controls.
 *
 * The IASSlider interface, which has a global unique identifier equal to IID_ASSLIDER, extends the
 * IASProgressBar interface. The slider control has a programmatic identifier equal to APC_Slider.
 * Sliders-active controls designed to be moved by the user-are primarily managed with the methods
 * inherited from IASProgressBar. When a slider is moved, it fires either a WM_HSCROLL or WM_VSCROLL
 * command to the event sink. The WPARAM contains the control's identifier. The LPARAM contains the
 * slider value.
 */
struct IASSlider : public IASProgressBar
#else
DECLARE_INTERFACE_(IASSlider, IASProgressBar)
#endif
    {     
	/**
	 * This method gets the value in which to increment the slider.
	 *
	 * @param plIncr Pointer to a long integer that contains the increment value.
	 *
	 * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
	 *   entered.
	 */
	STDMETHOD(get_Incr) (THIS_ long *plIncr) PURE;
    /**
     * This method sets the value in which to increment the slider.
     *
     * @param lIncr Long integer that specifies the increment value.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
     *   entered.
     */
    STDMETHOD(put_Incr) (THIS_ long lIncr) PURE;

    /**
     * This method gets the highlight color.
     *
     * @param pclr Pointer to the highlight color.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
     *   entered.
     *
     * Use the GetRValue, GetGValue, and GetBValue macros to get the color components of pclr.
     */
    STDMETHOD(get_HiliteColor) (THIS_ OLE_COLOR *pclr) PURE;
    /**
     * This method sets the highlight color.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
     *   entered.
     *
     * Use the RGB macro to set the components of clr before passing clr to the method.
     */
    STDMETHOD(put_HiliteColor) (THIS_ OLE_COLOR clr) PURE;
    };


#undef  INTERFACE

#define INTERFACE
#if defined(__cplusplus) && !defined(CINTERFACE)
/**
 * This interface provides methods to manage a visual volume indicator (VVI) control.
 *
 * The IASVVI interface, which has a global unique identifier (GUID) equal to IID_ASVVI, extends the
 * IASProgressBar interface. The visual volume indicator control has a programmatic identifier equal
 * to APC_Vvi.
 */
struct IASVVI : public IASProgressBar
#else
DECLARE_INTERFACE_(IASVVI, IASProgressBar)
#endif
    {
    /**
     * This method retrieves whether or not the control is mirrored.
     *
     * @param pfMirrored Pointer to a Boolean that is set to TRUE if the control is mirrored, FALSE if
     *   not.
     *
     * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
     *
     * Progress bars such as the visual volume indicator are usually drawn from left to right with a
     * positive slope. The get_Mirrored method indicates that the control is drawn from right to left.
     */
    STDMETHOD(get_Mirrored) (THIS_ BOOL *pfMirrored) PURE;
    /**
     * This method sets whether or not the control is mirrored.
     *
     * @param fMirrored Boolean that is set to TRUE if the control is mirrored, or to FALSE if not.
     *
     * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
     *
     * Progress bars such as the visual volume indicator are usually drawn from left to right with a
     * positive slope. The put_Mirrored method causes the control to be drawn from right to left.
     */
    STDMETHOD(put_Mirrored) (THIS_ BOOL fMirrored) PURE;
	
    /**
     * This method retrieves whether the control is inverted or normal.
     *
     * @param pfInverted Pointer to a Boolean that is set to TRUE if the control is inverted, or to
     *   FALSE if the control is normal.
     *
     * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
     *
     * Progress bars such as the visual volume indicator are usually drawn from left to right with a
     * positive slope. The get_Inverted method indicates that the control is flipped upside-down.
     */
    STDMETHOD(get_Inverted) (THIS_ BOOL *pfInverted) PURE;
    /**
     * This method sets whether the control is inverted or normal.
     *
     * @param fInverted Boolean that is set to TRUE if the control is inverted, or to FALSE if not.
     *
     * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
     *
     * Progress bars such as the visual volume indicator are usually drawn from left to right with a
     * positive slope. The put_Inverted method causes the control to be flipped upside-down.
     */
    STDMETHOD(put_Inverted) (THIS_ BOOL fInverted) PURE;

   };
#undef  INTERFACE

#define INTERFACE

#if defined(__cplusplus) && !defined(CINTERFACE)
/**
 * This interface is used to manage a memory slider.
 *
 * The IASMemorySlider interface, which has a global unique identifier (GUID) equal to
 * IID_ASMEMORYSLIDER, extends the IASSlider interface. The memory slider has a programmatic
 * identifier equal to APC_MemSlider.
 */
struct IASMemorySlider : public IASSlider
#else
DECLARE_INTERFACE_(IASMemorySlider, IASSlider)
#endif
    {
    /**
     * This method sets the amount of the object store currently being used.
     *
     * @param lStoreUsed Long integer that contains the amount of RAM currently in use.
     *
     * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
     *
     * To determine the amount of the object store currently being used, call the GetStoreInformation
     * function to retrieve a STORE_INFORMATION structure. You can then use the put_StoreUsed method to
     * set the value displayed by the memory slider to value obtained from the STORE_INFORMATION
     * structure.
     */
    STDMETHOD(put_StoreUsed) (THIS_ long lStoreUsed) PURE;
    /**
     * This method sets the amount of RAM currently being used.
     *
     * @param lRamUsed Long integer that contains the amount of RAM currently in use.
     *
     * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
     *
     * To determine the amount of RAM currently being used, call the GlobalMemoryStatus function to
     * retrieve a MEMORYSTATUS structure. You can then use the put_RamUsed method to set the value
     * displayed by the memory slider to value obtained from the MEMORYSTATUS structure.
     */
    STDMETHOD(put_RamUsed)   (THIS_ long lRamUsed) PURE;
    };

#undef  INTERFACE

//
// Text Input Range
//
#define INTERFACE

DECLARE_INTERFACE_(IASTextInputRange, IASControl)
    {
    STDMETHOD(get_MinChar) (THIS_ short *pch) PURE;
    STDMETHOD(put_MinChar) (THIS_ short ch) PURE;
    STDMETHOD(get_MaxChar) (THIS_ short *pch) PURE;
    STDMETHOD(put_MaxChar) (THIS_ short ch) PURE;

    STDMETHOD(get_MinCharIgnore) (THIS_ short *pch) PURE;
    STDMETHOD(put_MinCharIgnore) (THIS_ short ch) PURE;
    STDMETHOD(get_MaxCharIgnore) (THIS_ short *pch) PURE;
    STDMETHOD(put_MaxCharIgnore) (THIS_ short ch) PURE;
    
    STDMETHOD(get_SpecialChar) (THIS_ BSTR *pbstr) PURE;
    STDMETHOD(put_SpecialChar) (THIS_ BSTR bstr) PURE;

    STDMETHOD(get_CurChar) (THIS_ short *pch) PURE;
    STDMETHOD(put_CurChar) (THIS_ short ch) PURE;
    };

//
// Text Spinner
//
#undef  INTERFACE
#define INTERFACE

#if defined(__cplusplus) && !defined(CINTERFACE)
/**
 * This interface provides the methods to manage a character spinner control.
 *
 * The IASCharSpinner interface, which has a global unique identifier (GUID) equal to
 * IID_ASCHARSPINNER, extends the IASControl interface.
 *
 * The user inputs text into an application by means of a character spinner control. A WM_COMMAND
 * message is fired to the event sink whenever the ENTER or ESCAPE is pressed. The high-order word
 * of the wParam contains an EN_CHANGE message and the low-order word contains the control's
 * identifier. The high-order word of lParam contains zero if the character has been modified, and
 * contains one if not. The low-order word of lParam contains the form's identifier.
 */
struct IASCharSpinner : public IASControl
#else
DECLARE_INTERFACE_(IASCharSpinner, IASControl)
#endif
    {
    /**
     * This method gets the item height.
     *
     * @param plHeight Pointer to a long integer that contains the height of the item.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
     *   entered.
     *
     * All items must be the same height.
     */
    STDMETHOD(get_ItemHeight) (THIS_ long *plHeight) PURE;
    /**
     * This method sets the item height.
     *
     * @param lHeight Long integer that specifies the height of the item.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
     *   entered.
     *
     * All items must be the same height.
     */
    STDMETHOD(put_ItemHeight) (THIS_ long lHeight) PURE;
    
    /**
     * This method gets the character set.
     *
     * @param pbstr Pointer to the character set.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
     *   entered.
     */
    STDMETHOD(get_CharSet) (THIS_ BSTR *pbstr) PURE;
    /**
     * This method sets the character set.
     *
     * @param bstr Character set.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
     *   entered.
     */
    STDMETHOD(put_CharSet) (THIS_ BSTR bstr) PURE;
    
    /**
     * This method gets the current character.
     *
     * @param pch Pointer to the current character.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
     *   entered.
     */
    STDMETHOD(get_CurChar) (THIS_ short *pch) PURE;
    /**
     * This method sets the current character.
     *
     * @param ch Current character.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
     *   entered.
     */
    STDMETHOD(put_CurChar) (THIS_ short ch) PURE;
    
    /**
     * This method advances the position of the spin box to the next character.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
     *   entered.
     */
    STDMETHOD(NextChar) (THIS) PURE;
    /**
     * This method retracts the position of the spin box to the previous character.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
     *   entered.
     */
    STDMETHOD(PrevChar) (THIS) PURE;
    
    /**
     * This method sets the spin mode.
     *
     * @param mode Short integer that contains the spin mode. The spin mode is one of the following
     *   values: Mode Value ASFC_CHARSPIN_SEQUENTIAL 0x1 ASFC_CHARSPIN_DIRSHIFTED 0x2
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
     *   entered.
     */
    STDMETHOD(put_SpinMode) (THIS_ short mode) PURE;
    /**
     * This method gets the spin mode.
     *
     * @param pmode Pointer to a short integer that contains the spin mode.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
     *   entered.
     */
    STDMETHOD(get_SpinMode) (THIS_ short *pmode) PURE;
    };

//
// Text SIP
//
#undef  INTERFACE
#define INTERFACE

DECLARE_INTERFACE_(IASSIP, IASTextInputRange)
    {
    STDMETHOD(get_HiliteColor) (THIS_ OLE_COLOR *pclr) PURE;
    STDMETHOD(put_HiliteColor) (THIS_ OLE_COLOR clr) PURE;    
	STDMETHOD(get_BorderColor) (THIS_ OLE_COLOR *pclr) PURE;
	STDMETHOD(put_BorderColor) (THIS_ OLE_COLOR clr) PURE;

    STDMETHOD(get_ItemHeight) (THIS_ long *plHeight) PURE;
    STDMETHOD(put_ItemHeight) (THIS_ long lHeight) PURE;
    STDMETHOD(get_ItemWidth) (THIS_ long *plWidth) PURE;
    STDMETHOD(put_ItemWidth) (THIS_ long lWidth) PURE;

    STDMETHOD(get_ClientEditBox) (THIS_ IDispatch **ppdisp) PURE;
    STDMETHOD(put_ClientEditBox) (THIS_ IDispatch *pdisp) PURE;
    };

//
// EditBox
//
#undef  INTERFACE
#define INTERFACE

#if defined(__cplusplus) && !defined(CINTERFACE)
/**
 * This interface provides the methods to manage an Auto PC simple edit box control.
 *
 * The IASEditBox interface, which has a global unique identifier (GUID) equal to IID_ASEDITBOX,
 * extends the IASCharSpinner interface. An edit control has a programmatic identifier equal to
 * APC_Edit.
 *
 * Edit mode is entered when the user presses the ENTER key, or the application invokes
 * IASEditBox::put_Editing(TRUE). When editing a particular character, the WM_COMMAND message is
 * fired to the event sink whenever when the edit mode is exited. This happens when the user presses
 * either the ENTER or ESCAPE key. The values of the wParam and lParam parameters that accompany the
 * WM_COMMAND message are described in the following table.
 *
 * Parameter Description LOWORD(wParam) Control identifier HIWORD(wParam) EN_CHANGE LOWORD(lParam)
 * Notification flags HIWORD(lParam) Form identifier
 *
 * The low-order word of lParam is one of the following notification flags:
 *
 * - ASFC_EDITNOTIFY_COMMITTED: The user exited edit mode by pressing the ENTER key.
 *
 * - ASFC_EDITNOTIFY_CHANGED: The text has changed since edit mode was entered.
 *
 * When using an edit control in a power list box, HIWORD(lParam) contains the power list box
 * identifier instead of the form's identifier.
 */
struct IASEditBox : public IASCharSpinner
#else
DECLARE_INTERFACE_(IASEditBox, IASCharSpinner)
#endif
    {
    /**
     * This method gets the width of an item.
     *
     * @param plWidth [out] Pointer to the long integer that contains the width of an item.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     *
     * When editing, text is drawn in a non-proportional font inside equally sized boxes. The box with
     * focus becomes a spin box, so the user can cycle through the available characters. This method
     * returns the width of a box.
     */
    STDMETHOD(get_ItemWidth) (THIS_ long *plWidth) PURE;
    /**
     * This method sets the width of an item.
     *
     * @param lWidth [in] Long integer that contains the width of the item.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that lWidth is less than 0.
     *
     * When editing, text is drawn in a non-proportional font inside equally sized boxes. The box with
     * focus becomes a spin box, so the user can cycle through the available characters.
     */
    STDMETHOD(put_ItemWidth) (THIS_ long lWidth) PURE;

    /**
     * This method gets a copy of the string currently in the edit box.
     *
     * @param pbstr [out] Pointer to the Unicode text string currently in the edit box.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     */
    STDMETHOD(get_Text) (THIS_ BSTR *pbstr) PURE;
    /**
     * This method replaces the current text string with another.
     *
     * @param bstr [in] Unicode string.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     */
    STDMETHOD(put_Text) (THIS_ BSTR bstr) PURE;
    
    /**
     * This method gets the currently selected character.
     *
     * @param pch [out] Pointer to the currently selected character.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     *   E_ACCESSDENIED indicates that editing mode is not enabled.
     */
    STDMETHOD(get_Selection) (THIS_ wchar_t *pch) PURE;
    /**
     * This method sets the current item to the specified character.
     *
     * @param ch [in] Character to be set.
     *
     * @return NOERROR indicated success. E_ACCESSDENIED indicates that editing mode is not enabled.
     *
     * If ch is 0, this method sets the current item equal to the first character in the character set.
     */
    STDMETHOD(put_Selection) (THIS_ wchar_t ch) PURE;
    /**
     * This method gets the index of the currently selected character.
     *
     * @param pwich [out] Pointer to the index of the character being edited.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     *   E_ACCESSDENIED indicates that editing mode is not enabled.
     */
    STDMETHOD(get_SelectionIndex) (THIS_ short *pwich) PURE;
    /**
     * This method sets the index of the currently selected item.
     *
     * @param wich [in] Index to be set for the character being edited.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     *   E_ACCESSDENIED indicates that editing mode is not enabled.
     */
    STDMETHOD(put_SelectionIndex) (THIS_ short wich) PURE;

    /**
     * This method gets the number of characters in the edit box.
     *
     * @param pwcch [out] Pointer to the number of characters in the edit box.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     */
    STDMETHOD(get_NumChars) (THIS_ short *pwcch) PURE;
    /**
     * This method gets the maximum number of characters allowed in the edit box.
     *
     * @param pwcchMax [out] Pointer to a short integer that contains the maximum number of characters
     *   in the edit box.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     */
    STDMETHOD(get_MaxChars) (THIS_ short *pwcchMax) PURE;
    /**
     * This method sets the maximum number of characters allowed in the edit box.
     *
     * @param wcchMax [in] Short integer that contains the maximum number of characters in the edit box.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument exceeds the
     *   system-defined maximum for edit boxes.
     */
    STDMETHOD(put_MaxChars) (THIS_ short wcchMax) PURE;

    /**
     * This method retrieves whether or not the edit box is read-only.
     *
     * @param pfReadOnly [out] Pointer to a Boolean set to TRUE if the edit box is read-only, or FALSE
     *   if it is available for editing.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     */
    STDMETHOD(get_ReadOnly) (THIS_ BOOL *pfReadOnly) PURE;
    /**
     * This method sets whether an edit box is read-only or not.
     *
     * @param fReadOnly [in] Boolean that is set to TRUE to define the edit box as read-only, or FALSE
     *   to make it available for editing.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(put_ReadOnly) (THIS_ BOOL fReadOnly) PURE;

	/**
	 * This method checks to see if editing is enabled.
	 *
	 * @param pfEditing [out] Pointer to a Boolean that is set to TRUE if editing is enabled, or to
	 *   FALSE if not.
	 *
	 * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
	 */
	STDMETHOD(get_Editing) (THIS_ BOOL *pfEditing) PURE;
	/**
	 * This method sets whether editing is enabled or not.
	 *
	 * @param fEditing [in] Boolean that is set to TRUE if editing is enabled, or to FALSE if not.
	 *
	 * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
	 */
	STDMETHOD(put_Editing) (THIS_ BOOL fEditing) PURE;

    /**
     * The method retrieves whether or not trailing white spaces are trimmed.
     *
     * @param pfTrimRight [out] Pointer to a Boolean that is set to TRUE if the white spaces are
     *   trimmed, or to FALSE if not.
     *
     * @return An appropriate HRESULT value is returned.
     *
     * The pfTrimRight parameter is set to TRUE by default, which indicates that trailing white spaces
     * are trimmed from the right side of a line of text in the edit box.
     */
    STDMETHOD(get_TrimRight) (THIS_ BOOL *pfTrimRight) PURE;
    /**
     * This method sets whether or not trailing white spaces are trimmed.
     *
     * @param fTrimRight [in] Boolean that is set to TRUE if the white spaces are to be trimmed, or to
     *   FALSE if not.
     *
     * @return S_FALSE indicates there is nothing more to delete.
     *
     * This property is set to TRUE by default.
     */
    STDMETHOD(put_TrimRight) (THIS_ BOOL fTrimRight) PURE;

	/**
	 * This method inserts a character to the left of the current character.
	 *
	 * @param ch [in] Character to be inserted.
	 *
	 * @return S_FALSE indicates that the maximum number of characters has been reached. E_ACCESSDENIED
	 *   indicates that editing mode is not enabled.
	 */
	STDMETHOD(Insert) (THIS_ short ch) PURE;
    /**
     * This method deletes the character currently selected for editing.
     *
     * @return NOERROR indicates success. S_FALSE indicates that there is nothing to delete.
     */
    STDMETHOD(Delete) (THIS) PURE;

   	/**
   	 * This method indicates whether the edit control displays asterisks instead of the characters that
   	 * the user enters.
   	 *
   	 * @param pfTextPrivate Pointer to a Boolean that is set to TRUE to specify that the edit control
   	 *   display asterisks instead of the actual characters that the user enters, or to FALSE to display
   	 *   the actual characters that the user enters.
   	 *
   	 * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
   	 */
   	STDMETHOD(get_TextPrivate) (THIS_ BOOL *pfTextPrivate) PURE;
	/**
	 * This method specifies whether the edit control displays asterisks instead of the characters that
	 * the user enters.
	 *
	 * @param fTextPrivate Boolean that is set to TRUE to specify that the edit control display
	 *   asterisks instead of the actual characters that the user enters, or to FALSE to display the
	 *   actual characters that the user enters.
	 *
	 * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
	 *
	 * Use this method to protect the privacy of a user when the user enters text in a password field in
	 * an edit box.
	 */
	STDMETHOD(put_TextPrivate) (THIS_ BOOL fTextPrivate) PURE;
    };

//
// A Canvas. Use for free style drawing
//
#undef	INTERFACE
#define	INTERFACE

#if defined(__cplusplus) && !defined(CINTERFACE)
/**
 * This control interface allows direct graphical device interface (GDI) access to an area on the
 * faceplate.
 *
 * The IASCanvas interface, which has a global unique identifier equal to IID_ASCANVAS, extends the
 * IASControl interface. The canvas control has a programmatic identifier equal to APC_Canvas.
 */
struct IASCanvas : public IASControl
#else
DECLARE_INTERFACE_(IASCanvas, IASControl)
#endif
    {
    /**
     * This method gets a handle to the device context for a control, or creates a compatible off-screen
     * bitmap and gets the device context of that bitmap.
     *
     * @param phdc Pointer to the handle of a device context (DC).
     * @param fOffScreen [in] Boolean that is set to TRUE to create an offscreen bitmap for the DC, or
     *   set to FALSE to get the DC of the control.
     *
     * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the device is out of memory.
     *
     * Conventional GDI drawing should be done to an offscreen bitmap. When complete, it is then
     * transferred to the screen with either IASCanvas::ClipAndCommit or IASCanvas::Commit. For
     * techniques where the bitmaps already exist, like sprite animation, the offscreen bitmap is not
     * necessary, and should not be created.
     */
    STDMETHOD(GetDC) (THIS_ OLE_HANDLE *phdc, BOOL fOffScreen) PURE;
	/**
	 * This method sends the current contents of the device context (DC) to the screen.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 */
	STDMETHOD(Commit) (THIS) PURE;
	/**
	 * This method sends the current contents of the device context (DC) to the screen while clipping
	 * against the supplied region.
	 *
	 * @param hrgnClip Handle to the clipping region.
	 *
	 * @return NOERROR indicates success. E_UNEXPECTED indicates that something unexpected happened.
	 *
	 * Use CreateRectRgn to get a handle to the intended clipping region.
	 */
	STDMETHOD(ClipAndCommit) (THIS_ OLE_HANDLE hrgnClip) PURE;
    /**
     * This method sends a selected rectangle of the current off-screen bitmap to the screen.
     *
     * @param xDest Specifies the left edge of the target rectangle.
     * @param yDest Specifies the upper edge of the target rectangle.
     * @param xSrc Specifies the left edge of the source rectangle.
     * @param ySrc Specifies the upper edge of the source rectangle.
     * @param dx Specifies the width of the source rectangle.
     * @param dy Specifies the height of the source rectangle.
     *
     * @return NOERROR indicates success. E_UNEXPECTED indicates that something unexpected happened.
     */
    STDMETHOD(CommitAt) (THIS_ long xDest, long yDest, long xSrc, long ySrc, long dx, long dy) PURE;
    /**
     * This method maps and sends the contents of an off-screen bitmap, starting at the specified
     * coordinates, to the upper-left corner of a control.
     *
     * @param xSrc [in] Specifies the left edge of the rectangle to be committed.
     * @param ySrc [in] Specifies the upper edge of the rectangle to be committed.
     *
     * @return NOERROR indicates success. E_UNEXPECTED indicates that something unexpected happened.
     *
     * The specified starting corner of the bitmap is mapped to the upper-left corner of the control. If
     * the committed portion of the bitmap is smaller than the control, the remainder of the control is
     * painted in a default color. If the committed portion of the bitmap is larger than the control,
     * the bitmap is clipped on the right and bottom sides.
     */
    STDMETHOD(CommitFrom) (THIS_ long xSrc, long ySrc) PURE;
    /**
     * This method sets the auto-commit mode for a control and sets the coordinates of the starting
     * point for an off-screen bitmap from which auto-commit blits.
     *
     * @param fAutoCommit Boolean that is set to TRUE to enable auto-commit, or to FALSE to disable it.
     *   The default setting is FALSE.
     * @param pxSrc Pointer to the starting x-coordinate of the source bitmap from which auto-commit
     *   blits.
     * @param pySrc Pointer to the starting y-coordinate of the source bitmap from which auto-commit
     *   blits.
     *
     * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the device is out of memory.
     *
     * If auto-commit is enabled, every time the screen is redrawn, the last bitmap that was set is used
     * to redraw the screen. This is useful for handling form focus changes- for example, using a timer
     * to move an application from the background to the foreground. Enabling auto-commit tells the
     * forms manager to only repaint the last bitmap that was set when the Forms Manager redraws the
     * screen.
     *
     * In general, the purpose of the Canvas control is to give the application a substantial degree of
     * control over drawing. For this reason, auto-commit is disabled by default. However, in some
     * circumstances, enabling auto-commit can simplify your application by automating the painting
     * process.
     */
    STDMETHOD(put_AutoCommit) (THIS_ BOOL fAutoCommit, long xSrc, long ySrc) PURE;
    /**
     * This method enables you to determine if the control is in the auto-commit mode and to determine
     * the coordinates of the starting point for the off-screen bitmap from which auto-commit blits.
     *
     * @param pfAutoCommit Pointer to a Boolean that is set to TRUE if auto-commit is enabled, or to
     *   FALSE if auto-commit is disabled. The default setting is FALSE.
     * @param pxSrc Pointer to the x-coordinate of the source bitmap from which auto-commit blits.
     * @param pySrc Pointer to the y-coordinate of the source bitmap from which auto-commit blits.
     *
     * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the device is out of memory.
     *
     * If auto-commit is enabled, every time the screen is redrawn, the last bitmap that was set is used
     * to redraw the screen. This is useful for handling form focus changes-for example, using a timer
     * to move an application from the background to the foreground. Enabling auto-commit tells the
     * forms manager to only repaint the last bitmap that was set when the Forms Manager redraws the
     * screen.
     *
     * In general, the purpose of the Canvas control is to give the application a substantial degree of
     * control over drawing. For this reason, auto-commit is disabled by default. However, in some
     * circumstances, enabling auto-commit can simplify your application by automating the painting
     * process.
     */
    STDMETHOD(get_AutoCommit) (THIS_ BOOL * pfAutoCommit, long * pxSrc, long * pySrc) PURE;
    };

//
// CLOCK
//
#undef	INTERFACE
#define	INTERFACE

#if defined(__cplusplus) && !defined(CINTERFACE)
/**
 * This interface provides methods to access the clock control.
 *
 * The IASClock interface, which has a global unique identifier equal to IID_ASCLOCK, extends the
 * IASControl interface.
 *
 * The clock control, which has a programmatic identifier equal to APC_Clock, can display either the
 * time or the date. The clock control has two display regions: the clock proper and a label control
 * that serves as the label. The clock control is an invisible control. The clock control displays
 * the time in the label control attached by the put_ClockLabel0 method, and displays the date in
 * the label control attached by the put_ClockLabel method.
 */
struct IASClock : public IASControl
#else
DECLARE_INTERFACE_(IASClock, IASControl)
#endif
    {
    /**
     * This method gets the time and date format for the clock display.
     *
     * @param pfTime Pointer to a Boolean that is set to TRUE for the time, or to FALSE for the date.
     * @param pbstrFormat Pointer to the Unicode string that defines the format of the time and date
     *   display. If pbstrFormat is NULL, the function uses the default format of the specified locale.
     *   Use the following elements to construct a time format string: - h: The one- or two-digit hour in
     *   12-hour format. - hh: The two-digit hour in 12-hour format. Single-digit values are preceded by a
     *   zero. - H: The one- or two-digit hour in 24-hour format. - HH: The two-digit hour in 24-hour
     *   format. Single-digit values are preceded by a zero. - m: The one- or two-digit minute. - mm: The
     *   two-digit minute. Single-digit values are preceded by a zero. - s: The one- or two-digit second.
     *   - ss: The two-digit second. Single-digit values are preceded by a zero. - t: The one-letter AM/PM
     *   abbreviation; that is, "AM" is displayed as "A." - tt: The two-letter AM/PM abbreviation; that
     *   is, "AM" is displayed as "AM." Use the following elements to construct a date format string: - d:
     *   The one- or two-digit day. - dd: The two-digit day. Single-digit values are preceded by a zero. -
     *   ddd: The three-character weekday abbreviation. The function uses the LOCALE_SABBREVDAYNAME value
     *   associated with the specified locale. - dddd: The full weekday name. The function uses the
     *   LOCALE_SDAYNAME value associated with the specified locale. - M: The one- or two-digit month
     *   number. - MM: The two-digit month number. Single-digit values are preceded by a zero. - MMM: The
     *   three-character abbreviation. The function uses the LOCALE_SABBREVMONTHNAME value associated with
     *   the specified locale. - MMMM: The full month name. The function uses the LOCALE_SMONTHNAME value
     *   associated with the specified locale. - y: The year is displayed as the last two digits, but with
     *   no leading zero for years less than 10. - yy: The last two digits of the year; that is, 1996 is
     *   displayed as "96." - yyyy: The full year; that is, 1996 is displayed as "1996." - gg: Period/era
     *   string. The function uses the CAL_SERASTRING value associated with the specified locale. This
     *   element is ignored if the date to be formatted does not have an associated era or period string.
     *   For example, to get the time display "11:29:40 PM" use the following format string: "hh':'mm':'ss
     *   tt" To get the date display "Wed, Aug 31 94" use the following format string: "ddd',' MMM dd yy"
     *   If you use spaces to separate the elements, they appear in the same location in the output
     *   string. The letters must be in uppercase or lowercase as shown, for example, "ss", not "SS." To
     *   have a character appear in the actual time string, enclose it in single quotes and it appears in
     *   the same location as it occupies in the format string.
     * @param pFormatFlags Pointer to a bitmask of flags specifying the format. The following formats
     *   are available for time display: - LOCALE_NOUSEROVERRIDE: If set, the function formats the string
     *   using the system default time format for the specified locale. If not set, the function formats
     *   the string using any user overrides to the locale's default time format. This flag cannot be set
     *   if pbstrFormat is non-NULL. - TIME_NOMINUTESORSECONDS: Do not use minutes or seconds. -
     *   TIME_NOSECONDS: Do not use seconds. - TIME_NOTIMEMARKER: Do not use a time marker. -
     *   TIME_FORCE24HOURFORMAT: Always use a 24-hour time format. The following formats are available for
     *   date display: - LOCALE_NOUSEROVERRIDE: If set, the function formats the string using the system
     *   default date format for the specified locale. If not set, the function formats the string using
     *   any user overrides to the locale's default date format. - DATE_SHORTDATE: Use the short date
     *   format. This is the default. Cannot be used with DATE_LONGDATE. - DATE_LONGDATE: Use the long
     *   date format. Cannot be used with DATE_SHORTDATE. - DATE_USE_ALT_CALENDAR: Use the alternate
     *   calendar, if one exists, to format the date string. If this flag is set, the function uses the
     *   default format for that alternate calendar, rather than using any user overrides. The user
     *   overrides are used only in the event that there is no default format for the specified alternate
     *   calendar.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     */
    STDMETHOD(get_ClockFormat) (BOOL * pfTime, BSTR * pbstrFormat, LONG * pFormatFlags ) PURE;
    /**
     * This method sets the time and date format for the clock display.
     *
     * @param fTime Boolean that is set to TRUE for the time, or to FALSE for the date.
     * @param bstrFormat Unicode string that defines the format of the time and date display. If
     *   bstrFormat is NULL, the function uses the default format of the specified locale. Use the
     *   following elements to construct a time format string: - h: The one- or two-digit hour in 12-hour
     *   format. - hh: The two-digit hour in 12-hour format. Single-digit values are preceded by a zero. -
     *   H: The one- or two-digit hour in 24-hour format. - HH: The two-digit hour in 24-hour format.
     *   Single-digit values are preceded by a zero. - m: The one- or two-digit minute. - mm: The
     *   two-digit minute. Single-digit values are preceded by a zero. - s: The one- or two-digit second.
     *   - ss: The two-digit second. Single-digit values are preceded by a zero. - t: The one-letter AM/PM
     *   abbreviation; that is, "AM" is displayed as "A." - tt: The two-letter AM/PM abbreviation. Use the
     *   following elements to construct a date format string: - d: The one- or two-digit day. - dd: The
     *   two-digit day. Single-digit values are preceded by a zero. - ddd: The three-character weekday
     *   abbreviation. The function uses the LOCALE_SABBREVDAYNAME value associated with the specified
     *   locale. - dddd: The full weekday name. The function uses the LOCALE_SDAYNAME value associated
     *   with the specified locale. - M: The one- or two-digit month number. - MM: The two-digit month
     *   number. Single-digit values are preceded by a zero. - MMM: The three-character abbreviation. The
     *   function uses the LOCALE_SABBREVMONTHNAME value associated with the specified locale. - MMMM: The
     *   full month name. The function uses the LOCALE_SMONTHNAME value associated with the specified
     *   locale. - y: The year is displayed as the last two digits, but with no leading zero for years
     *   less than 10. - yy: The last two digits of the year; that is, 1996 is displayed as "96." - yyyy:
     *   The full year; that is, 1996 is displayed as "1996." - gg: Period/era string. The function uses
     *   the CAL_SERASTRING value associated with the specified locale. This element is ignored if the
     *   date to be formatted does not have an associated era or period string. For example, to get the
     *   time display "11:29:40 PM" use the following format string: "hh':'mm':'ss tt" To get the date
     *   display "Wed, Aug 31 94" use the following format string: "ddd',' MMM dd yy" If you use spaces to
     *   separate the elements, they appear in the same location in the output string. The letters must be
     *   in uppercase or lowercase as shown, for example, "ss", not "SS." To have a character appear in
     *   the actual time string, enclose it in single quotes and it appears in the same location as it
     *   occupies in the format string.
     * @param FormatFlags Bitmask of flags specifying the format. The following formats are available
     *   for time display: - LOCALE_NOUSEROVERRIDE: If set, the function formats the string using the
     *   system default time format for the specified locale. If not set, the function formats the string
     *   using any user overrides to the locale's default time format. This flag cannot be set if
     *   bstrFormat is non-NULL. - TIME_NOMINUTESORSECONDS: Do not use minutes or seconds. -
     *   TIME_NOSECONDS: Do not use seconds. - TIME_NOTIMEMARKER: Do not use a time marker. -
     *   TIME_FORCE24HOURFORMAT: Always use a 24-hour time format. The following formats are available for
     *   date display: - LOCALE_NOUSEROVERRIDE: If set, the function formats the string using the system
     *   default date format for the specified locale. If not set, the function formats the string using
     *   any user overrides to the locale's default date format. - DATE_SHORTDATE: Use the short date
     *   format. This is the default. Cannot be used with DATE_LONGDATE. - DATE_LONGDATE: Use the long
     *   date format. Cannot be used with DATE_SHORTDATE. - DATE_USE_ALT_CALENDAR: Use the alternate
     *   calendar, if one exists, to format the date string. If this flag is set, the function uses the
     *   default format for that alternate calendar, rather than using any user overrides. The user
     *   overrides are used only in the event that there is no default format for the specified alternate
     *   calendar.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     *
     * If any format flag is used for FormatFlags, NULL must be passed to bstrFormat.
     */
    STDMETHOD(put_ClockFormat) ( BOOL fTime, BSTR bstrFormat, LONG FormatFlags) PURE;
    /**
     * This method gets the current label format.
     *
     * @param pfTime Pointer to a Boolean that is set to TRUE for the time, or to FALSE for the date.
     * @param pbstrFormat Pointer to the Unicode string that defines the format of the time and date
     *   display. If pbstrFormat is NULL, the function uses the default format of the specified locale.
     *   Use the following elements to construct a time format string: - h: The one- or two-digit hour in
     *   12-hour format. - hh: The two-digit hour in 12-hour format. Single-digit values are preceded by a
     *   zero. - H: The one- or two-digit hour in 24-hour format. - HH: The two-digit hour in 24-hour
     *   format. Single-digit values are preceded by a zero. - m: The one- or two-digit minute. - mm: The
     *   two-digit minute. Single-digit values are preceded by a zero. - s: The one- or two-digit second.
     *   - ss: The two-digit second. Single-digit values are preceded by a zero. - t: The one-letter AM/PM
     *   abbreviation; that is, "AM" is displayed as "A." - tt: The two-letter AM/PM abbreviation. Use the
     *   following elements to construct a date format string: - d: The one- or two-digit day. - dd: The
     *   two-digit day. Single-digit values are preceded by a zero. - ddd: The three-character weekday
     *   abbreviation. The function uses the LOCALE_SABBREVDAYNAME value associated with the specified
     *   locale. - dddd: The full weekday name. The function uses the LOCALE_SDAYNAME value associated
     *   with the specified locale. - M: The one- or two-digit month number. - MM: The two-digit month
     *   number. Single-digit values are preceded by a zero. - MMM: The three-character abbreviation. The
     *   function uses the LOCALE_SABBREVMONTHNAME value associated with the specified locale. - MMMM: The
     *   full month name. The function uses the LOCALE_SMONTHNAME value associated with the specified
     *   locale. - y: The year is displayed as the last two digits, but with no leading zero for years
     *   less than 10. - yy: The last two digits of the year; that is, 1996 is displayed as "96." - yyyy:
     *   The full year; that is, 1996 is displayed as "1996." - gg: Period/era string. The function uses
     *   the CAL_SERASTRING value associated with the specified locale. This element is ignored if the
     *   date to be formatted does not have an associated era or period string. For example, to get the
     *   time display "11:29:40 PM" use the following format string: "hh':'mm':'ss tt" To get the date
     *   display "Wed, Aug 31 94" use the following format string: "ddd',' MMM dd yy" If you use spaces to
     *   separate the elements, they appear in the same location in the output string. The letters must be
     *   in uppercase or lowercase as shown, for example, "ss", not "SS." To have a character appear in
     *   the actual time string, enclose it in single quotes and it appears in the same location as it
     *   occupies in the format string.
     * @param pFormatFlags Pointer to a bitmask of flags specifying the format. The following formats
     *   are available for time display: - LOCALE_NOUSEROVERRIDE: If set, the function formats the string
     *   using the system default time format for the specified locale. If not set, the function formats
     *   the string using any user overrides to the locale's default time format. This flag cannot be set
     *   if pbstrFormat is non-NULL. - TIME_NOMINUTESORSECONDS: Do not use minutes or seconds. -
     *   TIME_NOSECONDS: Do not use seconds. - TIME_NOTIMEMARKER: Do not use a time marker. -
     *   TIME_FORCE24HOURFORMAT: Always use a 24-hour time format. The following formats are available for
     *   date display: - LOCALE_NOUSEROVERRIDE: If set, the function formats the string using the system
     *   default date format for the specified locale. If not set, the function formats the string using
     *   any user overrides to the locale's default date format. - DATE_SHORTDATE: Use the short date
     *   format. This is the default. Cannot be used with DATE_LONGDATE. - DATE_LONGDATE: Use the long
     *   date format. Cannot be used with DATE_SHORTDATE. - DATE_USE_ALT_CALENDAR: Use the alternate
     *   calendar, if one exists, to format the date string. If this flag is set, the function uses the
     *   default format for that alternate calendar, rather than using any user overrides. The user
     *   overrides are used only in the event that there is no default format for the specified alternate
     *   calendar.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     */
    STDMETHOD(get_LabelFormat) (BOOL * pfTime, BSTR * pbstrFormat, LONG * pFormatFlags ) PURE;
    /**
     * This method sets the current label format.
     *
     * @param fTime Boolean that is set to TRUE for the time, or to FALSE for the date.
     * @param bstrFormat Unicode string that defines the format of the time and date display. If
     *   bstrFormat is NULL, the function uses the default format of the specified locale. Use the
     *   following elements to construct a time format string: - h: The one- or two-digit hour in 12-hour
     *   format. - hh: The two-digit hour in 12-hour format. Single-digit values are preceded by a zero. -
     *   H: The one- or two-digit hour in 24-hour format. - HH: The two-digit hour in 24-hour format.
     *   Single-digit values are preceded by a zero. - m: The one- or two-digit minute. - mm: The
     *   two-digit minute. Single-digit values are preceded by a zero. - s: The one- or two-digit second.
     *   - ss: The two-digit second. Single-digit values are preceded by a zero. - t: The one-letter AM/PM
     *   abbreviation; that is, "AM" is displayed as "A." - tt: The two-letter AM/PM abbreviation. Use the
     *   following elements to construct a date format string: - d: The one- or two-digit day. - dd: The
     *   two-digit day. Single-digit values are preceded by a zero. - ddd: The three-character weekday
     *   abbreviation. The function uses the LOCALE_SABBREVDAYNAME value associated with the specified
     *   locale. - dddd: The full weekday name. The function uses the LOCALE_SDAYNAME value associated
     *   with the specified locale. - M: The one- or two-digit month number. - MM: The two-digit month
     *   number. Single-digit values are preceded by a zero. - MMM: The three-character abbreviation. The
     *   function uses the LOCALE_SABBREVMONTHNAME value associated with the specified locale. - MMMM: The
     *   full month name. The function uses the LOCALE_SMONTHNAME value associated with the specified
     *   locale. - y: The year is displayed as the last two digits, but with no leading zero for years
     *   less than 10. - yy: The last two digits of the year; that is, 1996 is displayed as "96." - yyyy:
     *   The full year; that is, 1996 is displayed as "1996." - gg: Period/era string. The function uses
     *   the CAL_SERASTRING value associated with the specified locale. This element is ignored if the
     *   date to be formatted does not have an associated era or period string. For example, to get the
     *   time display "11:29:40 PM" use the following format string: "hh':'mm':'ss tt" To get the date
     *   display "Wed, Aug 31 94" use the following format string: "ddd',' MMM dd yy" If you use spaces to
     *   separate the elements, they appear in the same location in the output string. The letters must be
     *   in uppercase or lowercase as shown, for example, "ss", not "SS." To have a character appear in
     *   the actual time string, enclose it in single quotes and it appears in the same location as it
     *   occupies in the format string.
     * @param FormatFlags Bitmask of flags specifying the format. The following formats are available
     *   for time display: - LOCALE_NOUSEROVERRIDE: If set, the function formats the string using the
     *   system default time format for the specified locale. If not set, the function formats the string
     *   using any user overrides to the locale's default time format. This flag cannot be set if
     *   bstrFormat is non-NULL. - TIME_NOMINUTESORSECONDS: Do not use minutes or seconds. -
     *   TIME_NOSECONDS: Do not use seconds. - TIME_NOTIMEMARKER: Do not use a time marker. -
     *   TIME_FORCE24HOURFORMAT: Always use a 24-hour time format. The following formats are available for
     *   date display: - LOCALE_NOUSEROVERRIDE: If set, the function formats the string using the system
     *   default date format for the specified locale. If not set, the function formats the string using
     *   any user overrides to the locale's default date format. - DATE_SHORTDATE: Use the short date
     *   format. This is the default. Cannot be used with DATE_LONGDATE. - DATE_LONGDATE: Use the long
     *   date format. Cannot be used with DATE_SHORTDATE. - DATE_USE_ALT_CALENDAR: Use the alternate
     *   calendar, if one exists, to format the date string. If this flag is set, the function uses the
     *   default format for that alternate calendar, rather than using any user overrides. The user
     *   overrides are used only in the event that there is no default format for the specified alternate
     *   calendar.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     */
    STDMETHOD(put_LabelFormat) ( BOOL fTime, BSTR bstrFormat, LONG FormatFlags) PURE;
    /**
     * This method specifies a label control to be used as a label field; usually, the label displays
     * date information.
     *
     * @param pdispLabel Pointer to an Auto PC simple (AS) label control to be used as the label field.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     */
    STDMETHOD(put_ClockLabel) (THIS_ IDispatch *pdispLabel) PURE;
    /**
     * This method specifies a label control to be used as a label field; usually, the label displays
     * time information.
     *
     * @param pdispLabel Pointer to an Auto PC simple (AS) label control to be used as a label field.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that the argument is invalid.
     */
    STDMETHOD(put_ClockLabel0) (THIS_ IDispatch *pdispLabel) PURE;
    };

//
// TIMER
//
#undef  INTERFACE
#define INTERFACE

#if defined(__cplusplus) && !defined(CINTERFACE)
/**
 * The IASTimer interface provides methods for timing.
 *
 * The IASTimer interface, which has a global unique identifier (GUID) equal to IID_ASTIMER, extends
 * the IASControl interface. The timer is set to fire at a specified interval. When it matures, it
 * fires a WM_TIMER message to the event sink. The control's identifier is contained in the
 * low-order word of wParam, the form's identifier in the high-order word.
 */
struct IASTimer : public IASControl
#else
DECLARE_INTERFACE_(IASTimer, IASControl)
#endif
    {
    /**
     * This method gets the interval at which the current timer is triggered.
     *
     * @param plMillis Timing interval, in milliseconds.
     *
     * @return - E_OUTOFMEMORY: This value is returned if the system is out of memory.
     */
    STDMETHOD(get_Interval) (THIS_ long *plMillis) PURE;
    /**
     * This method sets a new timing interval, and restarts the timer.
     *
     * @param lMillis Long integer that specifies the new timing interval, in milliseconds.
     *
     * @return - E_OUTOFMEMORY: This value is returned if the system is out of memory.
     */
    STDMETHOD(put_Interval) (THIS_ long lMillis) PURE;
    /**
     * This method gets whether or not the timer is enabled.
     *
     * @param pfEnabled Pointer to a Boolean that is set to TRUE if a timer is enabled, or to FALSE if
     *   not.
     *
     * @return - E_OUTOFMEMORY: This value is returned if the system is out of memory.
     */
    STDMETHOD(get_TimerEnabled) (THIS_ BOOL *pfEnabled) PURE;
    /**
     * This method sets whether or not the timer is enabled.
     *
     * @param fEnabled Boolean that is set to TRUE if a timer is enabled, or to FALSE if not.
     *
     * @return - E_OUTOFMEMORY: This value is returned if the system is out of memory.
     */
    STDMETHOD(put_TimerEnabled) (THIS_ BOOL fEnable) PURE;
     };

#undef  INTERFACE
#define INTERFACE

#if defined(__cplusplus) && !defined(CINTERFACE)
/**
 * This interface provides the methods to manage a PlayList object.
 *
 * The IASPlayList interface, which has a global unique identifier equal to IID_ASPLAYLIST, extends
 * the IASControl interface. The play list object has a programmatic identifier equal to
 * APC_PlayList.
 */
struct IASPlayList : public IASControl
#else
DECLARE_INTERFACE_(IASPlayList, IASControl)
#endif
    {
    /**
     * This method gets the active track.
     *
     * @param biTrack Unsigned character that indicates the active track.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
     *   entered.
     *
     * The index of tracks in the play list begins at 1. If the index of the active track is equal to 0,
     * the play list does not indicate an active track.
     */
    STDMETHOD(get_TrackActive) (THIS_ unsigned char biTrack) PURE;
    /**
     * This method sets the active track.
     *
     * @param biTrack Unsigned character that indicates the active track.
     * @param fActive Boolean that is set to TRUE for the active track, or to FALSE for a non-active
     *   track.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
     *   entered.
     *
     * The index of tracks in the play list begins at 1. If you set the index of the active track is
     * equal to 0, the play list does not indicate an active track.
     */
    STDMETHOD(put_TrackActive) (THIS_ unsigned char biTrack, BOOL fActive) PURE;
    /**
     * This method resets the play list and turns off all active tracks.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(Reset) (THIS) PURE;

    /**
     * This method gets the number of tracks in the play list.
     *
     * @param pbcTracks Pointer to the number of tracks.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
     *   entered.
     *
     * The index of tracks in the play list begins at 1. If the number of tracks is equal to 0, the play
     * list does not contain any tracks.
     */
    STDMETHOD(get_NumTracks) (THIS_ unsigned char *pbcTracks) PURE;
    /**
     * This method sets the number of tracks in the play list.
     *
     * @param bcTracks Number of tracks in the play list.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
     *   entered-for example, if the number of tracks exceeds the maximum number allowed.
     *
     * The index of tracks in the play list begins at 1. If your application determines that no tracks
     * are available, set the number of tracks equal to 0. The maximum number of tracks available is
     * ASFC_PLAYLIST_TRACKSMAX, which is defined as 128.
     */
    STDMETHOD(put_NumTracks) (THIS_ unsigned char bcTracks) PURE;
    
	/**
	 * This method gets the border color of the play list grid lines.
	 *
	 * @param pclr Pointer to the border color.
	 *
	 * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
	 *   entered.
	 *
	 * Use the GetRValue, GetGValue, and GetBValue macros to get the color components of pclr.
	 */
	STDMETHOD(get_BorderColor) (THIS_ OLE_COLOR *pclr) PURE;
	/**
	 * This method sets the border color of the play list grid lines.
	 *
	 * @param clr New border color.
	 *
	 * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
	 *   entered.
	 *
	 * Use the RGB macro to set the components of clr before passing clr to the method.
	 */
	STDMETHOD(put_BorderColor) (THIS_ OLE_COLOR clr) PURE;
    /**
     * This method gets the highlight border color to be drawn around the current selection.
     *
     * @param pclr Pointer to the highlight border color.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
     *   entered.
     *
     * Use the GetRValue, GetGValue, and GetBValue macros to get the color components of pclr.
     */
    STDMETHOD(get_HiliteBorderColor) (THIS_ OLE_COLOR *pclr) PURE;
    /**
     * This method sets the highlight border color to be drawn around the current selection.
     *
     * @param clr Highlight border color.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
     *   entered.
     *
     * Use the RGB macro to set the components of clr before passing clr to the method.
     */
    STDMETHOD(put_HiliteBorderColor) (THIS_ OLE_COLOR clr) PURE;    
	/**
	 * This method gets the active foreground color.
	 *
	 * @param pclr Pointer to the active foreground color.
	 *
	 * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
	 *   entered.
	 *
	 * Use the GetRValue, GetGValue, and GetBValue macros to get the color components of pclr.
	 */
	STDMETHOD(get_ActiveForeColor) (THIS_ OLE_COLOR *pclr) PURE;
	/**
	 * This method sets the active foreground color.
	 *
	 * @param clr Active foreground color.
	 *
	 * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
	 *   entered.
	 *
	 * Use the RGB macro to set the components of clr before passing clr to the method.
	 */
	STDMETHOD(put_ActiveForeColor) (THIS_ OLE_COLOR clr) PURE;
	/**
	 * This method gets the active background color.
	 *
	 * @param pclr Pointer to the active background color.
	 *
	 * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
	 *   entered.
	 *
	 * Use the GetRValue, GetGValue, and GetBValue macros to get the color components of pclr.
	 */
	STDMETHOD(get_ActiveBackColor) (THIS_ OLE_COLOR *pclr) PURE;
	/**
	 * This method sets the active background color.
	 *
	 * @param clr Active background color.
	 *
	 * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
	 *   entered.
	 *
	 * Use the RGB macro to set the components of clr before passing clr to the method.
	 */
	STDMETHOD(put_ActiveBackColor) (THIS_ OLE_COLOR clr) PURE;
	/**
	 * This method gets the inactive foreground color.
	 *
	 * @param pclr Pointer to the inactive foreground color.
	 *
	 * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
	 *   entered.
	 *
	 * Use the GetRValue, GetGValue, and GetBValue macros to get the color components of pclr.
	 */
	STDMETHOD(get_InactiveForeColor) (THIS_ OLE_COLOR *pclr) PURE;
	/**
	 * This method sets the inactive foreground color.
	 *
	 * @param clr Inactive foreground color.
	 *
	 * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
	 *   entered.
	 *
	 * Use the RGB macro to set the components of clr before passing clr to the method.
	 */
	STDMETHOD(put_InactiveForeColor) (THIS_ OLE_COLOR clr) PURE;
	/**
	 * This method gets the inactive background color.
	 *
	 * @param pclr Pointer to the inactive background color.
	 *
	 * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
	 *   entered.
	 *
	 * Use the GetRValue, GetGValue, and GetBValue macros to get the color components of pclr.
	 */
	STDMETHOD(get_InactiveBackColor) (THIS_ OLE_COLOR *pclr) PURE;
	/**
	 * This method sets the inactive background color.
	 *
	 * @param clr Inactive background color.
	 *
	 * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
	 *   entered.
	 *
	 * Use the RGB macro to set the components of clr before passing clr to the method.
	 */
	STDMETHOD(put_InactiveBackColor) (THIS_ OLE_COLOR clr) PURE;

    /**
     * This method gets the item height, which is the height of an individual box in a play list.
     *
     * @param plHeight Pointer to a long integer that contains the height of the item.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
     *   entered.
     */
    STDMETHOD(get_ItemHeight) (THIS_ long *plHeight) PURE;
    /**
     * This method sets the item height, which is the height of an individual box in a play list.
     *
     * @param lHeight Long integer that specifies the height of the item.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
     *   entered.
     */
    STDMETHOD(put_ItemHeight) (THIS_ long lHeight) PURE;
    /**
     * This method gets the item width, which is the width of an individual box in a play list.
     *
     * @param plWidth Pointer to a long integer that contains the width of the item.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
     *   entered.
     */
    STDMETHOD(get_ItemWidth) (THIS_ long *plWidth) PURE;
    /**
     * The method sets the item width, which is the width of an individual box in a play list.
     *
     * @param lWidth Long integer that specifies the width of the item.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
     *   entered.
     */
    STDMETHOD(put_ItemWidth) (THIS_ long lWidth) PURE;

    /**
     * This method sets the number of the current track.
     *
     * @param bcTrack Unsigned character that contains the track number.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
     *   entered.
     *
     * The index of tracks in the play list begins at 1. If you set the index of the current track equal
     * to 0, the play list does not indicate a current track.
     */
    STDMETHOD(put_CurrentTrack) (THIS_ unsigned char bcTrack) PURE;
    /**
     * This method gets the number of the current track.
     *
     * @param pbcTrack Pointer to the current track number.
     *
     * @return NOERROR indicates success. E_INVALIDARG indicates that an invalid argument has been
     *   entered.
     *
     * The index of tracks in the play list begins at 1. If the index of the current track is equal to
     * 0, the play list does not indicate a current track.
     */
    STDMETHOD(get_CurrentTrack) (THIS_ unsigned char* pbcTrack) PURE;
    };

#undef  INTERFACE
#define INTERFACE

#if defined(__cplusplus) && !defined(CINTERFACE)
/**
 * This interface provides methods to manage a crosshairs control.
 *
 * The crosshairs control, which has a programmatic identifier equal to APC_Crosshair, works like an
 * x-y graph. Both x and y lines can be adjusted separately. There is a maximum and minimum x- and
 * y-coordinate and the position of the cross hair is specified by two values that fall in this
 * range.
 *
 * The target box stays inside the bounding rectangle at the extremes. This means that four pixels
 * must be added to the height and width. To calculate the target box, use the following equations:
 *
 * Height = 4 + (<number of vertical steps> * <pixels per step>)
 *
 * Width = 4 + (<number of horizontal steps> * <pixels per step>)
 *
 * The IASCrossHair interface, which has a global unique identifier (GUID) equal to
 * IID_ASCROSSHAIRS, inherits from IASControl.
 */
struct IASCrossHairs : public IASControl
#else
DECLARE_INTERFACE_(IASCrossHairs, IASControl)
#endif
    {
    /**
     * This method gets the current value of the x-axis.
     *
     * @param pwVal [out] Pointer to the current value of the x-axis value.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(get_XVal) (THIS_ short *pwVal) PURE;
    /**
     * This method sets the current value of the x-axis.
     *
     * @param wval [in] Current value of the x-axis.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(put_XVal) (THIS_ short wVal) PURE;
    /**
     * This method gets the current value of the y-axis.
     *
     * @param pwVal [out] Pointer to the current value of the y-axis.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(get_YVal) (THIS_ short *pwVal) PURE;
    /**
     * This method sets the current value of the y-axis.
     *
     * @param wval [in] Current value of the y-axis.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(put_YVal) (THIS_ short wVal) PURE;

    /**
     * This method gets the minimum value of the x-axis.
     *
     * @param pwVal [out] Pointer to the short integer that contains the minimum value of the x-axis.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     *
     * The minimum value of the x-axis is usually a negative number.
     */
    STDMETHOD(get_XMinus) (THIS_ short *pwVal) PURE;
    /**
     * This method sets the minimum value of the x-axis.
     *
     * @param wval [in] Minimum value of the x-axis.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(put_XMinus) (THIS_ short wVal) PURE;
    /**
     * This method gets the maximum positive value of the x-axis.
     *
     * @param pwVal [out] Pointer to the maximum positive value of the x-axis.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(get_XPlus) (THIS_ short *pwVal) PURE;
    /**
     * This method sets the maximum positive value of the x-axis.
     *
     * @param wval [in] Maximum positive value of the x-axis.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(put_XPlus) (THIS_ short wVal) PURE;

    /**
     * This method gets the minimum value of the y-axis.
     *
     * @param pwVal [out] Pointer to the minimum value of the y-axis.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     *
     * The minimum value of the y-axis is usually a negative number.
     */
    STDMETHOD(get_YMinus) (THIS_ short *pwVal) PURE;
    /**
     * This method sets the minimum value of the y-axis.
     *
     * @param wval [in] Minimum value of the y-axis.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(put_YMinus) (THIS_ short wVal) PURE;
    /**
     * This method gets the maximum positive value of the y-axis.
     *
     * @param pwVal [out] Pointer to the maximum positive value of the y-axis.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(get_YPlus) (THIS_ short *pwVal) PURE;
    /**
     * This method sets the maximum positive value of the y-axis.
     *
     * @param wval [in] Maximum positive value of the y-axis.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(put_YPlus) (THIS_ short wVal) PURE;

    /**
     * This method gets the status of the cross hair highlight.
     *
     * @param pfHorz Pointer to a Boolean that is set to TRUE if the horizontal axis of the cross hair
     *   is highlighted, or to FALSE if the horizontal axis of the cross hair is not highlighted.
     * @param pfVert Pointer to a Boolean that is set to TRUE if the vertical axis of the cross hair is
     *   highlighted, or to FALSE if the vertical axis of the cross hair is not highlighted.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(get_CrossHairHilite) (THIS_ BOOL *pfHorz, BOOL *pfVert) PURE;
    /**
     * This method sets the status of the cross hair highlight.
     *
     * @param fHorz Boolean that is set to TRUE to turn on the highlight for the horizontal axis of the
     *   cross hair, or FALSE to turn off the highlight for the horizontal axis of the crosshair.
     * @param fvert Boolean that is set to TRUE to turn on the highlight for the vertical axis of the
     *   cross hair, or FALSE to turn off the highlight for the vertical axis of the crosshair.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     */
    STDMETHOD(put_CrossHairHilite) (THIS_ BOOL fHorz, BOOL fVert) PURE;
    
    /**
     * This method gets color of both axes of the cross hair itself.
     *
     * @param pclr [out] Pointer to the cross hair color.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     *
     * Use the GetRValue, GetGValue, and GetBValue macros to get the color components of pclr.
     */
    STDMETHOD(get_CrossHairColor) (THIS_ OLE_COLOR *pclr) PURE;
    /**
     * This method sets the color of both axes of the cross hair itself.
     *
     * @param clr [in] Color of both axes of the cross hair itself.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     *
     * Use the RGB macro to set the components of clr before passing clr to the method.
     */
    STDMETHOD(put_CrossHairColor) (THIS_ OLE_COLOR clr) PURE;
    /**
     * This method gets the color of the box in the middle of the cross hair.
     *
     * @param pclr [out] Pointer to the color of the box in the middle of the cross hair.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     *
     * Use the GetRValue, GetGValue, and GetBValue macros to get the color components of pclr.
     */
    STDMETHOD(get_CrossHairBoxColor) (THIS_ OLE_COLOR *pclr) PURE;
    /**
     * This method sets the color of the box in the middle of the cross hair.
     *
     * @param clr [in] Color of the box in the middle of the cross hair.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     *
     * Use the RGB macro to set the components of clr before passing clr to the method.
     */
    STDMETHOD(put_CrossHairBoxColor) (THIS_ OLE_COLOR clr) PURE;
    /**
     * This method gets the color of the cross hair axes when the axes are highlighted.
     *
     * @param pclr [out] Pointer to the cross hair highlight color.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     *
     * Use the GetRValue, GetGValue, and GetBValue macros to get the color components of pclr.
     */
    STDMETHOD(get_CrossHairHiliteColor) (THIS_ OLE_COLOR *pclr) PURE;
    /**
     * This method sets the color of the cross hair axes when the axes are highlighted.
     *
     * @param clr [in] Color of the cross hair axes when the axes are highlighted.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     *
     * Use the RGB macro to set the components of clr before passing clr to the method.
     */
    STDMETHOD(put_CrossHairHiliteColor) (THIS_ OLE_COLOR clr) PURE;
    /**
     * This method gets the color used to draw the x-axis and the y-axis displayed in the cross hairs
     * control.
     *
     * @param pclr [out] Pointer to the color of the x-axis and the y-axis displayed in the cross hairs
     *   control.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     *
     * Use the GetRValue, GetGValue, and GetBValue macros to get the color components of pclr.
     */
    STDMETHOD(get_AxisColor) (THIS_ OLE_COLOR *pclr) PURE;
    /**
     * This method sets the color used to draw the x-axis and the y-axis displayed in the cross hairs
     * control.
     *
     * @param clr [in] Color of the x-axis and the y-axis displayed in the cross hairs control.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     *
     * Use the RGB macro to set the components of clr before passing clr to the method.
     */
    STDMETHOD(put_AxisColor) (THIS_ OLE_COLOR clr) PURE;
    };

//
// Tabber control
//
#undef  INTERFACE
#define INTERFACE

#if defined(__cplusplus) && !defined(CINTERFACE)
/**
 * This interface provides methods to manage a tabber control.
 *
 * The IASTabber interface, which has a global unique identifier (GUID) equal to IID_ASTABBER,
 * extends the IASControl interface. The tabber control has a programmatic identifier equal to
 * APC_Tab.
 */
struct IASTabber : public IASControl
#else
DECLARE_INTERFACE_(IASTabber, IASControl)
#endif
{
	//
	// basics
	//
    /**
     * This method adds a tab.
     *
     * @param bstr Unicode string to be displayed on the tab.
     * @param lData Long integer that contains data associated with the tab.
     *
     * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
     */
    STDMETHOD(Add)				(THIS_ BSTR bstr, long lData) PURE;
    /**
     * This method adds an image to the tabber control.
     *
     * @param hImage Handle to the image.
     * @param hImageMask Handle to the image list mask. The mask specifies which image in the list is
     *   displayed.
     * @param lData Long integer that contains data associated with the tab.
     *
     * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
     */
    STDMETHOD(AddImage)			(THIS_ OLE_HANDLE hImage, OLE_HANDLE hImageMask,long lData) PURE;
    /**
     * This method adds a tab with an index value.
     *
     * @param bstr Unicode string to be displayed on the tab.
     * @param lData Long integer that contains data associated with the tab.
     * @param lpIndex Long pointer to the index of the tab that the method adds.
     *
     * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
     */
    STDMETHOD(AddWithIndex)		(THIS_ BSTR bstr, long lData, long* lpIndex) PURE;
    /**
     * This method specifies where to insert a tab.
     *
     * @param index Index of the tab.
     * @param bstr Unicode string to be displayed on the tab.
     * @param lData Long integer that contains data associated with the tab.
     *
     * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
     */
    STDMETHOD(InsertAt)			(THIS_ long index,BSTR bstr,  long lData) PURE;
    /**
     * This method removes a tab specified by its index.
     *
     * @param index Index of the tab to remove.
     *
     * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
     */
    STDMETHOD(RemoveAt)			(THIS_ long index) PURE;
    /**
     * This method removes all tabs on the tabber.
     *
     * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
     */
    STDMETHOD(RemoveAll)		(THIS_ ) PURE;
    /**
     * This method specifies which tab has focus, based on speech.
     *
     * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
     */
    STDMETHOD(SpeakFocusTab)	(THIS_ ) PURE;
	/**
	 * This method retrieves the number of tabs.
	 *
	 * @param pcItems Pointer to the number of tabs.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(get_Count)		(THIS_ long* pcItems) PURE;
	//
	// get / set attributes / properties
	//
    STDMETHOD(get_TabStatus)            (THIS_ long	index, long *plStatus) PURE;
    STDMETHOD(put_TabStatus)            (THIS_ long	index, long lStatus) PURE;
    /**
     * This method gets the string associated with a specified tab.
     *
     * @param lIndex Long integer that contains the index of the tab.
     * @param pbstr Pointer to the Unicode string associated with the tab.
     *
     * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
     *
     * A copy of the string is returned. The caller is responsible for freeing the memory associated
     * with the allocated string.
     */
    STDMETHOD(get_String)				(THIS_ long	index, BSTR *pbstr) PURE;
    /**
     * This method sets the string associated with a specified tab.
     *
     * @param lIndex Long integer that contains the index of the tab.
     * @param bstr Unicode string associated with the tab.
     *
     * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
     *
     * A copy of the string is returned. The caller is responsible for freeing the memory associated
     * with the allocated string.
     */
    STDMETHOD(put_String)				(THIS_ long	index, BSTR bstr) PURE;
    /**
     * This method retrieves the speech identifier assigned to a tab.
     *
     * @param Index Index of the tab.
     * @param plSpeechId Pointer to the long integer that contains the speech identifier assigned to the
     *   tab.
     *
     * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
     */
    STDMETHOD(get_SpeechCommandId)		(THIS_ long	index, long *plSpeechId) PURE;
    /**
     * This method assigns a speech identifier to a tab.
     *
     * @param Index Index of the tab.
     * @param lSpeechId Long integer that contains the speech identifier assigned to the tab.
     *
     * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
     */
    STDMETHOD(put_SpeechCommandId)		(THIS_ long	index, long lSpeechId) PURE;
    /**
     * This method retrieves the data associated with a tab.
     *
     * @param Index Index of the tab.
     * @param plData Pointer to the long integer that contains data associated with the tab.
     *
     * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
     */
    STDMETHOD(get_ItemData)				(THIS_ long	index, long *plData) PURE;
    /**
     * This method sets the data associated with a tab.
     *
     * @param Index Index of the tab.
     * @param lData Long integer that contains the data associated with the tab.
     *
     * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
     */
    STDMETHOD(put_ItemData)				(THIS_ long	index, long lData) PURE;
    /**
     * This method retrieves the minimum width of the tab.
     *
     * @param plMinWidth Pointer to the long integer that contains the minimum width of the tab.
     *
     * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
     */
    STDMETHOD(get_TabMinWidth)			(THIS_ long* lpWidth) PURE;
    /**
     * This method sets the minimum width of the tab.
     *
     * @param lMinWidth Long integer that contains the minimum width of the tab.
     *
     * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
     */
    STDMETHOD(put_TabMinWidth)			(THIS_ long lWidth) PURE;
    /**
     * This method gets the color used for tabs.
     *
     * @param pclr Pointer to the color used for tabs.
     *
     * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
     *
     * Use the GetRValue, GetGValue, and GetBValue macros to get the color components of pclr.
     */
    STDMETHOD(get_TabColor)				(THIS_ OLE_COLOR *pclr) PURE;
    /**
     * This method sets the color used for tabs.
     *
     * @param clr Color used for tabs.
     *
     * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
     *
     * Use the RGB macro to set the components of clr before passing clr to the method.
     */
    STDMETHOD(put_TabColor)				(THIS_ OLE_COLOR clr) PURE;
    /**
     * This method retrieves the tab text color.
     *
     * @param pclr Pointer to the color used for tab text.
     *
     * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
     *
     * Use the GetRValue, GetGValue, and GetBValue macros to get the color components of pclr.
     */
    STDMETHOD(get_TabTextColor)			(THIS_ OLE_COLOR *pclr) PURE;
    /**
     * This method sets the tab text color.
     *
     * @param clr Color used for tab text.
     *
     * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
     *
     * Use the RGB macro to set the components of clr before passing clr to the method.
     */
    STDMETHOD(put_TabTextColor)			(THIS_ OLE_COLOR clr) PURE;
    /**
     * This method retrieves the border color.
     *
     * @param pclr Pointer to the border color.
     *
     * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
     *
     * Use the GetRValue, GetGValue, and GetBValue macros to get the color components of pclr.
     */
    STDMETHOD(get_BorderColor)			(THIS_ OLE_COLOR *pclr) PURE;
    /**
     * This method sets the border color.
     *
     * @param clr Border color.
     *
     * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
     *
     * Use the RGB macro to set the components of clr before passing clr to the method.
     */
    STDMETHOD(put_BorderColor)			(THIS_ OLE_COLOR clr) PURE;
    /**
     * This method retrieves the index of the tab with focus.
     *
     * @param plIndex Pointer to the long integer that contains the index of the tab with focus.
     *
     * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
     */
    STDMETHOD(get_FocusIndex)			(THIS_ long *plIndex) PURE;
    /**
     * This method sets the index of the tab with focus.
     *
     * @param lIndex Long integer that contains the index of the tab with focus.
     *
     * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
     */
    STDMETHOD(put_FocusIndex)			(THIS_ long lIndex) PURE;
    /**
     * This method retrieves the foreground color of the tab with focus.
     *
     * @param pclr Pointer to the foreground color of the tab with focus.
     *
     * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
     *
     * Use the GetRValue, GetGValue, and GetBValue macros to get the color components of pclr.
     */
    STDMETHOD(get_TabFocusForeColor)	(THIS_ OLE_COLOR *pclr) PURE;
    /**
     * This method sets the foreground color of the tab with focus.
     *
     * @param clr Foreground color of the tab with focus.
     *
     * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
     *
     * Use the RGB macro to set the components of clr before passing clr to the method.
     */
    STDMETHOD(put_TabFocusForeColor)	(THIS_ OLE_COLOR clr) PURE;
    /**
     * This method retrieves the background color of the tab with focus.
     *
     * @param pclr Pointer to the background color of the tab with focus.
     *
     * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
     *
     * Use the GetRValue, GetGValue, and GetBValue macros to get the color components of pclr.
     */
    STDMETHOD(get_TabFocusBackColor)	(THIS_ OLE_COLOR *pclr) PURE;
    /**
     * This method sets the background color of the tab with focus.
     *
     * @param clr Background color of the tab with focus.
     *
     * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
     *
     * Use the RGB macro to set the components of clr before passing clr to the method.
     */
    STDMETHOD(put_TabFocusBackColor)	(THIS_ OLE_COLOR clr) PURE;
	/**
	 * This method retrieves whether or not the tabber should wrap to the first tab once the last tab
	 * has been reached.
	 *
	 * @param pfCircular Pointer to a Boolean that is set to TRUE if tab should wrap, or to FALSE if
	 *   not.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(get_Circular)(THIS_ BOOL* pfCircular) PURE;
	/**
	 * This method sets the wrap capabilities of the tabber.
	 *
	 * @param fCircular Boolean that is set to TRUE if tabber should wrap, or to FALSE if not.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(put_Circular)(THIS_ BOOL fCircular) PURE;
	/**
	 * This method retrieves whether or not notifications are enabled for the tabber.
	 *
	 * @param pfDeferredNotification Pointer to a Boolean that is set to TRUE if notifications are
	 *   enabled, or to FALSE if not.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(get_DeferredNotification)(THIS_ BOOL* pfDeferredNotification) PURE;
	/**
	 * This method specifies whether or not notifications are enabled on a tabber.
	 *
	 * @param fDeferredNotification Boolean that is set to TRUE if notifications are enabled, or to
	 *   FALSE if not.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(put_DeferredNotification)(THIS_ BOOL fDeferredNotification) PURE;
	/**
	 * This method retrieves a voice menu for the tabber.
	 *
	 * @param ppVoiceMenu Pointer to the pointer to the voice menu.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(get_VoiceMenu)(THIS_ IVCmdMenu** ppVoiceMenu) PURE;
	/**
	 * This method sets a voice menu for the tabber.
	 *
	 * @param pVoiceMenu Pointer to the voice menu.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(put_VoiceMenu)(THIS_ IVCmdMenu*  pVoiceMenu) PURE;
    /**
     * This method retrieves a voice menu command.
     *
     * @param pbstrCommand Pointer to the Unicode string that contains the voice menu command.
     *
     * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
     */
    STDMETHOD(get_VoiceMenuActivateCommand)(THIS_ BSTR *pbstrCommand) PURE;
    /**
     * This method sets a voice menu command.
     *
     * @param bstrCommand Unicode string that specifies the voice menu command.
     *
     * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
     */
    STDMETHOD(put_VoiceMenuActivateCommand)(THIS_ BSTR bstrCommand) PURE;

	//
	// Images
	//
    /**
     * This method retrieves the image handle associated with a tab.
     *
     * @param lIndex Long integer that contains the index of the tab.
     * @param phImage Pointer to the handle to the available images.
     * @param phImageMask Pointer to the handle to the image list mask. The mask specifies which images
     *   in the list can be displayed.
     *
     * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
     */
    STDMETHOD(get_Image)		(THIS_ long index, OLE_HANDLE *phImage, OLE_HANDLE *phImageMask) PURE;
    /**
     * This method sets the image handle associated with a tab.
     *
     * @param lIndex Long integer that contains the index of the tab.
     * @param hImage Handle to the available images.
     * @param hImageMask Handle to the image list mask. The mask specifies which images in the list can
     *   be displayed.
     *
     * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
     */
    STDMETHOD(put_Image)		(THIS_ long index, OLE_HANDLE hImage, OLE_HANDLE hImageMask) PURE;
    STDMETHOD(get_HiliteImage)		(THIS_ long index, OLE_HANDLE *phImage, OLE_HANDLE *phImageMask) PURE;
    STDMETHOD(put_HiliteImage)		(THIS_ long index, OLE_HANDLE hImage, OLE_HANDLE hImageMask) PURE;

    STDMETHOD(get_SkipDisabledTabs)(THIS_ BOOL *pfSkip) PURE;
    STDMETHOD(put_SkipDisabledTabs)(THIS_ BOOL fSkip) PURE;
};



#undef  INTERFACE
#define INTERFACE

//
// PowerListBox Item
//
#if defined(__cplusplus) && !defined(CINTERFACE)
/**
 * This interface is used to manage the items that have been added to a power list box.
 *
 * The IASPowerListBoxItem interface, which has a global unique identifier (GUID) equal to
 * IID_ASPOWERLISTBOXITEM, extends the IDispatch interface.
 */
struct IASPowerListBoxItem : public IDispatch
#else
DECLARE_INTERFACE_(IASPowerListBoxItem, IDispatch)
#endif
{
	/**
	 * This method gets the data associated with the item.
	 *
	 * @param plData Pointer to the long integer that contains the data associated with the item.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(get_ItemData)(THIS_ long *plData) PURE;
	/**
	 * This method sets the data associated with the item.
	 *
	 * @param lData Long integer that contains data associated with the item.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(put_ItemData)(THIS_ long lData) PURE;

	/**
	 * This method gets the mask used to specify which status items can be displayed.
	 *
	 * @param plMask Pointer to the long integer that contains the mask that specifies which status
	 *   items can be displayed.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(get_StatusItemsMask)(THIS_ long *plMask) PURE;
	/**
	 * This method sets the mask used to specify which status items can be displayed.
	 *
	 * @param lMask Long integer that contains the mask that specifies which status items can be
	 *   displayed.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(put_StatusItemsMask)(THIS_ long lMask) PURE;

	/**
	 * This method retrieves the caption associated with a particular item.
	 *
	 * @param pbstrCaption Pointer to the Unicode string to be displayed as the caption.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(get_Caption)(THIS_ BSTR *pbstrCaption) PURE;
	/**
	 * This method sets the item caption.
	 *
	 * @param bstrCaption Unicode string to be displayed as the caption.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(put_Caption)(THIS_ BSTR bstrCaption) PURE;

	/**
	 * This method retrieves the identifier of the item.
	 *
	 * @param plItemId Pointer to the long integer that contains the identifier of the item.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(get_ItemId)(THIS_ long *plItemId) PURE;
	/**
	 * This method sets the identifier of the item.
	 *
	 * @param lItemId Long integer that contains the identifier of the item.
	 *
	 * @return An appropriate HRESULT value is returned.
	 */
	STDMETHOD(put_ItemId)(THIS_ long lItemId) PURE;

	/**
	 * This method retrieves the item type.
	 *
	 * @param plType Pointer to the long integer that contains the item type. It is one of the following
	 *   values: - ASFC_PWRLB_TYPE_COMMAND: Specifies a command. - ASFC_PWRLB_TYPE_EDIT: Specifies an edit
	 *   box. - ASFC_PWRLB_TYPE_STRINGSPINNER: Specifies a string spinner. - ASFC_PWRLB_TYPE_INTSPINNER:
	 *   Specifies an integer spinner.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(get_Type)(THIS_ long *plType) PURE;

};

#undef  INTERFACE
#define INTERFACE

//
// PowerListBox command item
//
#if defined(__cplusplus) && !defined(CINTERFACE)
/**
 * This interface is used to manage command items in a power list box.
 *
 * The IASPowerListBoxCommand interface, which has a global unique identifier (GUID) equal to
 * IID_ASPOWERLISTBOXCOMMAND, extends the IASPowerListBoxItem interface. It has no methods of its
 * own, at present. It is managed with the methods inherited from the IASPowerListBoxItem interface.
 */
struct IASPowerListBoxCommand : public IASPowerListBoxItem
#else
DECLARE_INTERFACE_(IASPowerListBoxCommand,IASPowerListBoxItem)
#endif
{
};

#undef  INTERFACE
#define INTERFACE

#if defined(__cplusplus) && !defined(CINTERFACE)
/**
 * This interface provides methods to manage a power list box edit item.
 *
 * The IASPowerListBoxEdit interface, which has a global unique identifier (GUID) equal to
 * IID_ASPOWERLISTBOXEDIT, extends the IASControl interface.
 */
struct IASPowerListBoxEdit : public IASPowerListBoxItem
#else
DECLARE_INTERFACE_(IASPowerListBoxEdit, IASPowerListBoxItem)
#endif
{
	/**
	 * This method retrieves the text in the edit control.
	 *
	 * @param pbstrText Pointer to the Unicode string that contains the edit item's text.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(get_Text)(THIS_ BSTR *pbstr) PURE;
	/**
	 * This method sets the text in the edit item.
	 *
	 * @param bstrText Unicode string that contains the edit item's text.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(put_Text)(THIS_ BSTR bstr) PURE;

	/**
	 * This method retrieves the maximum number of characters allowed for the edit item.
	 *
	 * @param wcchMax Unsigned 16-bit character that contains the maximum number of characters allowed.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(get_MaxChars)(THIS_ short *wcchMax) PURE;
	/**
	 * This method sets the maximum number of characters allowed for the edit item.
	 *
	 * @param wcchMax Maximum number of characters allowed.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(put_MaxChars)(THIS_ short wcchMax) PURE;

	/**
	 * This method retrieves a string of valid characters.
	 *
	 * @param pbstrCharSet Pointer to the Unicode string that contains the characters.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(get_CharSet)(THIS_ BSTR *pbstr) PURE;
	/**
	 * This method sets a string of valid characters.
	 *
	 * @param bstrCharSet Unicode string that contains the characters.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(put_CharSet)(THIS_ BSTR bstr) PURE;

};

#undef  INTERFACE
#define INTERFACE

#if defined(__cplusplus) && !defined(CINTERFACE)
/**
 * This interface provides methods to manage a string spinner item.
 *
 * The IASPowerListboxStringSpinner interface, which has a global unique identifier (GUID) equal to
 * IID_ASPOWERLISTBOXSTRINGSPINNER, extends the IASPowerListBox interface.
 */
struct IASPowerListBoxStringSpinner : public IASPowerListBoxItem
#else
DECLARE_INTERFACE_(IASPowerListBoxStringSpinner, IASPowerListBoxItem)
#endif
{
	/**
	 * This method gets the strings used by the string spinner.
	 *
	 * @param pbstrItems Pointer to the Unicode string that contains the strings to be displayed,
	 *   separated by a tab character.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(get_Items)(THIS_ BSTR *pbstrItems) PURE;
	/**
	 * This method sets the strings used by the string spinner.
	 *
	 * @param bstrItems Unicode string that contains the strings to be displayed, separated by a tab
	 *   character.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(put_Items)(THIS_ BSTR bstrItems) PURE;

	/**
	 * This method retrieves the string currently being displayed.
	 *
	 * @param pbstrValue Pointer to the Unicode string currently being displayed.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(get_Value)(THIS_ BSTR *pbstrValue) PURE;
	/**
	 * This method sets the string currently being displayed.
	 *
	 * @param bstrValue Unicode string to be displayed.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(put_Value)(THIS_ BSTR bstrValue) PURE;

	/**
	 * This method retrieves the index of the string with focus.
	 *
	 * @param plFocusIndex Pointer to the long integer that contains the index of the string with focus.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(get_FocusIndex)(THIS_ long *plFocusIndex) PURE;
	/**
	 * This method sets the index of the string with focus.
	 *
	 * @param lFocusIndex Long integer that contains the index of the string with focus.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(put_FocusIndex)(THIS_ long lFocusIndex) PURE;

	/**
	 * This method retrieves whether or not the control wraps when it reaches the end of the list of
	 * strings.
	 *
	 * @param pfCircular Pointer to a Boolean that is set to TRUE to enable wrapping, or to FALSE to
	 *   disable it.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 *
	 * If this property is enabled, the string spinner control wraps from the last string to the first
	 * or vice versa, depending on which direction the user is going.
	 */
	STDMETHOD(get_Circular)(THIS_ BOOL* pfCircular) PURE;
	/**
	 * This method sets whether or not the control wraps when it reaches the end of the list of strings.
	 *
	 * @param fCircular Boolean that is set to TRUE to enable wrapping, or to FALSE to disable it.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 *
	 * If this property is enabled, the string spinner control wraps from the last string to the first
	 * or vice versa, depending on which direction the user is going.
	 */
	STDMETHOD(put_Circular)(THIS_ BOOL fCircular) PURE;

};


#undef  INTERFACE
#define INTERFACE

#if defined(__cplusplus) && !defined(CINTERFACE)
/**
 * This interface provides methods to manage an integer spinner item.
 *
 * The IASPowerListBoxIntSpinner interface, which has a global unique identifier equal to
 * IID_ASPOWERLISTBOXINTSPINNER, extends the IASPowerListBoxItem interface.
 */
struct IASPowerListBoxIntSpinner : public IASPowerListBoxItem
#else
DECLARE_INTERFACE_(IASPowerListBoxIntSpinner, IASPowerListBoxItem)
#endif
{
	/**
	 * This method retrieves the integer spinner flags.
	 *
	 * @param pwFlags Pointer to the unsigned 16-bit integer that contains the following flags
	 *   associated with the integer spinner item: - ASFC_PWRLB_FLAGS_DISPLAYSIGN: Forces a leading plus
	 *   (+) sign.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(get_Flags)(THIS_ short *pwFlags) PURE;
	/**
	 * This method sets the integer spinner flags.
	 *
	 * @param wFlags Unsigned 16-bit integer that contains the following flags associated with the
	 *   integer spinner item: - ASFC_PWRLB_FLAGS_DISPLAYSIGN: Forces a leading plus (+) sign.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(put_Flags)(THIS_ short wFlags) PURE;

	/**
	 * This method retrieves the minimum value for the integer spinner item.
	 *
	 * @param plMin Pointer to the long integer that contains the minimum value for the integer spinner.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(get_Min)(THIS_ long *plMin) PURE;
	/**
	 * This method sets the minimum value for the integer spinner item.
	 *
	 * @param lMin Long integer that contains the minimum value for the integer spinner.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 *
	 * If the passed value is larger than the current maximum value, the maximum value is set to be the
	 * same as the new minimum value.
	 */
	STDMETHOD(put_Min)(THIS_ long lMin) PURE;

	/**
	 * This method retrieves the maximum value for the integer spinner item.
	 *
	 * @param plMax Pointer to the long integer that contains the maximum value for the integer spinner.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(get_Max)(THIS_ long *plMax) PURE;
	/**
	 * This method sets the maximum value for the integer spinner item.
	 *
	 * @param lMax Long integer that contains the maximum value for the integer spinner.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 *
	 * If the passed value is less than the current minimum value, the minimum value is set to be the
	 * same as the new maximum value.
	 */
	STDMETHOD(put_Max)(THIS_ long lMax) PURE;

	/**
	 * This method retrieves the step size used by the integer spinner item.
	 *
	 * @param plStep Pointer to the long integer that contains the step size used by the integer spinner
	 *   item.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(get_Step)(THIS_ long *plStep) PURE;
	/**
	 * This method sets the step size used by the integer spinner item.
	 *
	 * @param lStep Long integer that contains the step size used by the integer spinner item.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(put_Step)(THIS_ long lStep) PURE;

	/**
	 * This method gets the value currently displayed by the integer spinner item.
	 *
	 * @param plValue Pointer to the long integer that contains the value currently displayed.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(get_Value)(THIS_ long *plValue) PURE;
	/**
	 * This method sets the value currently displayed by the integer spinner item.
	 *
	 * @param lValue Long integer that contains the value to be displayed.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 *   E_INVALIDARG indicates that the value is out of range of the current maximum or minimum.
	 */
	STDMETHOD(put_Value)(THIS_ long lValue) PURE;

	/**
	 * This method gets the units used by the integer spinner item.
	 *
	 * @param pbstrUnits Pointer to the string that is displayed to indicate units, for example, "ft,"
	 *   "sec," and "%."
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(get_Units)(THIS_ BSTR *pbstr) PURE;
	/**
	 * This method sets the units used by the integer spinner item.
	 *
	 * @param bstrUnits Unicode string that is displayed to indicate units, for example, "ft," "sec,"
	 *   and "%."
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(put_Units)(THIS_ BSTR bstr) PURE;

	/**
	 * This method retrieves whether or not the control wraps when it reaches the end of the list of
	 * integers.
	 *
	 * @param pfCircular Pointer to a Boolean that is set to TRUE to enable wrapping, or to FALSE to
	 *   disable it.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 *
	 * If this property is enabled, the integer spinner control wraps from the last integer to the first
	 * or vice versa, depending on which direction the user is going.
	 *
	 * Circular is defined as follows: If a user attempts to set the spinner control to a value greater
	 * than the maximum, the value is reset to the minimum. If a user attempts to set the spinner
	 * control to a value smaller than minimum, the value is reset to the maximum.
	 */
	STDMETHOD(get_Circular)(THIS_ BOOL* pfCircular) PURE;
	/**
	 * This method sets whether or not the control wraps when it reaches the end of the list of
	 * integers.
	 *
	 * @param fCircular Boolean that is set to TRUE to enable wrapping, or to FALSE to disable it.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 *
	 * If this property is enabled, the integer spinner control wraps from the last integer to the first
	 * or vice versa, depending on which direction the user is going.
	 */
	STDMETHOD(put_Circular)(THIS_ BOOL fCircular) PURE;

};

//
//  IASProvidePowerListBoxCommandData 
//

#undef  INTERFACE
#define INTERFACE

//
// The IASPowerListSpeakItemSink
//
DECLARE_INTERFACE_(IASPowerListSpeakItemSink, IUnknown)
{
    STDMETHOD(SpeakItem)(THIS_ DWORD dwSpeechContext, DWORD dwMode, DWORD dwReserved,
                    long lIndex, long lItemId, long lItemData, 
                    BSTR bstrCaption, BSTR bstrTTSCaption, BSTR bstrValue, BSTR bstrUnits) PURE;
};


#undef  INTERFACE
#define INTERFACE

//
// The IASProvidePowerListBoxCommandData sink
//
#if defined(__cplusplus) && !defined(CINTERFACE)
/**
 * This interface defines a sink which can be implemented by the application. It allows a list box
 * to perform a callback to get the items to be displayed.
 *
 * The IASProvidePowerListBoxCommandData interface, which has a global unique identifier equal to
 * IID_ASPROVIDEPOWERLISTBOXCOMMANDDATA, extends the IUnknown interface.
 *
 * The purpose of this interface is for applications such as Contacts that either have large numbers
 * of entries, or whose entries may change frequently. To use this interface, point to it in the
 * ProvidePowerListBoxCommandData property of the form. The power list box then invokes GetCaption
 * when drawing a command item that has a Null caption.
 */
struct IASProvidePowerListBoxCommandData : public IUnknown
#else
DECLARE_INTERFACE_(IASProvidePowerListBoxCommandData, IUnknown)
#endif
{
	STDMETHOD(get_Caption)(THIS_ long lIndex, long lItemId, long lItemData, BSTR *pbstrCaption) PURE;
};


#undef  INTERFACE
#define INTERFACE

//
// The PowerListBox
//
#if defined(__cplusplus) && !defined(CINTERFACE)
/**
 * This interface provides methods to manage a power list box control.
 *
 * The IASPowerListBox interface, which has a global unique identifier (GUID) equal to
 * IID_ASPOWERLISTBOX, extends the IASControl interface. All IASControl methods are available
 * through the IASPowerListBox interface. The power list box control has a programmatic identifier
 * equal to APC_PwrListBox.
 */
struct IASPowerListBox : public IASControl
#else
DECLARE_INTERFACE_(IASPowerListBox, IASControl)
#endif
{
	/**
	 * This method gets the number of items in the power list box.
	 *
	 * @param pcItems Pointer to the number of items in the power list box.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(get_Count)(THIS_ long *pcItems) PURE;

	/**
	 * This method removes all items from the power list box.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(RemoveAll)(THIS) PURE;
	/**
	 * This method removes an item specified by its identifier.
	 *
	 * @param lItemId Long integer that contains the identifier of the item to be removed.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(Remove)(THIS_ long lItemId) PURE;
	/**
	 * This method removes an item specified by its index.
	 *
	 * @param lIndex Long integer that contains the index of the item to be removed.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(RemoveAt)(THIS_ long lIndex) PURE;
	/**
	 * This method gets the command prompt.
	 *
	 * @param pbstrCommandPrompt Pointer to the Unicode string to be used for a command prompt.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 *
	 * The command prompt is a string that is displayed in front of command items that have rows. Only
	 * one command item can have the focus at one time.
	 */
	STDMETHOD(get_CommandPrompt)(THIS_ BSTR *pbstrCommandPrompt) PURE;
	/**
	 * This method sets the command prompt.
	 *
	 * @param bstrCommandPrompt Unicode string to be used for a command prompt.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 *
	 * To create command prompts than span multiple lines, set the item height to a size large enough to
	 * accommodate all needed lines. Then set bstrCommandPrompt to the desired value, using newline
	 * characters to separate the lines.
	 */
	STDMETHOD(put_CommandPrompt)(THIS_ BSTR bstrCommandPrompt) PURE;

	/**
	 * This method enables the application to access the internal edit controls used by the power list
	 * box.
	 *
	 * @param ppdispEdit Pointer to a pointer to the IDispatch interface of the edit box.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(get_Edit)(THIS_ IDispatch **ppdispEdit) PURE;

    // the value to be display when an edit item is empty
	STDMETHOD(get_EditEmptyText)(THIS_ BSTR *pbstrEmptyText) PURE;
	STDMETHOD(put_EditEmptyText)(THIS_ BSTR bstrEmptyText) PURE;

	/**
	 * This method retrieves whether or not the power list box is read-only.
	 *
	 * @param pfReadOnly Pointer to a Boolean that is set to TRUE if the power list box is read-only, or
	 *   to FALSE if not.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(get_ReadOnly)(THIS_ BOOL *pfReadOnly) PURE;
	/**
	 * This method sets whether or not the power list box is read-only.
	 *
	 * @param fReadOnly Boolean that is set to TRUE if the power list box is read-only, or to FALSE if
	 *   not.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(put_ReadOnly)(THIS_ BOOL fReadOnly) PURE;

	/**
	 * This method gets the index of the item with focus.
	 *
	 * @param plFocusIndex Pointer to the index of the item with focus.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(get_FocusIndex)(THIS_ long *plFocusIndex) PURE;
	/**
	 * This method sets the index of the item with focus.
	 *
	 * @param lFocusIndex Long integer that contains the index of the item with focus.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(put_FocusIndex)(THIS_ long lFocusIndex) PURE;

	/**
	 * This method retrieves the index of the topmost visible item.
	 *
	 * @param plTopVisibleIndex Pointer to the long integer that contains the index of the topmost
	 *   visible item.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(get_TopVisibleIndex)(THIS_ long *plTopVisibleIndex) PURE;
	/**
	 * This method sets the index of the topmost visible item.
	 *
	 * @param lTopVisibleIndex Long integer that contains the index of the topmost visible item.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(put_TopVisibleIndex)(THIS_ long lTopVisibleIndex) PURE;

	/**
	 * This method gets the identifier of the item with focus.
	 *
	 * @param plFocusId Pointer to the long integer that contains the identifier of the item with focus.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(get_FocusId)(THIS_ long *plFocusId) PURE;
	/**
	 * This method sets the identifier of the item with focus.
	 *
	 * @param lFocusId Long integer that contains the identifier of the item with focus.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(put_FocusId)(THIS_ long lFocusId) PURE;

	/**
	 * This method retrieves the identifier of the topmost visible item.
	 *
	 * @param plTopVisibleId Pointer to the long integer that contains the identifier of the topmost
	 *   visible item.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(get_TopVisibleId)(THIS_ long *plTopVisibleId) PURE;
	/**
	 * This method sets the identifier of the topmost visible item.
	 *
	 * @param lTopVisibleId Long integer that contains the identifier of the topmost visible item.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(put_TopVisibleId)(THIS_ long lTopVisibleId) PURE;

	/**
	 * This method gets the height of the item.
	 *
	 * @param plItemHeight Pointer to the long integer that contains the height of the item.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(get_ItemHeight)(THIS_ long *plItemHeight) PURE;
	/**
	 * This method sets the height of the item.
	 *
	 * @param lItemHeight Long integer that contains the height of the item.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(put_ItemHeight)(THIS_ long lItemHeight) PURE;

	/**
	 * This method retrieves whether or not the power list box is sorted.
	 *
	 * @param pfSorted Pointer to a Boolean that is set to TRUE if the items are sorted, or to FALSE if
	 *   not.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(get_Sorted)(THIS_ BOOL *pfSorted) PURE;
	/**
	 * This method sets whether or not the power list box is sorted.
	 *
	 * @param fSorted Boolean that is set to TRUE if the items are sorted, or to FALSE if not.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(put_Sorted)(THIS_ BOOL fSorted) PURE;

	/**
	 * This method retrieves whether the list is sorted in ascending or descending order.
	 *
	 * @param pfAscending Pointer to a Boolean that is set to TRUE if sorted in ascending order, or to
	 *   FALSE if sorted in descending order.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(get_SortOrder)(THIS_ BOOL *pfAscending) PURE;
	/**
	 * This method sets whether the list is sorted in ascending or descending order.
	 *
	 * @param fAscending Boolean that is set to TRUE if sorted in ascending order, or to FALSE if sorted
	 *   in descending order.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(put_SortOrder)(THIS_ BOOL fAscending) PURE;

	/**
	 * This method retrieves whether or not the power list box has centered focus.
	 *
	 * @param pfCenteredFocus Pointer to a Boolean that is set to TRUE if centered focus is enabled, or
	 *   to FALSE if not.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(get_CenteredFocus)(THIS_ BOOL *pfCenteredFocus) PURE;
	/**
	 * This method sets whether or not the power list box has centered focus.
	 *
	 * @param fCenteredFocus Boolean that is set to TRUE if centered focus is enabled, or to FALSE if
	 *   not.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(put_CenteredFocus)(THIS_ BOOL fCenteredFocus) PURE;

	/**
	 * This method retrieves whether or not the item has a border.
	 *
	 * @param pfItemBorder Pointer to a Boolean that is set to TRUE if the item has a border, or to
	 *   FALSE if not.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(get_ItemBorder)(THIS_ BOOL *pfItemBorder) PURE;
	/**
	 * This method sets whether or not the item has a border.
	 *
	 * @param fItemBorder Boolean that is set to TRUE if the item has a border, or to FALSE if not.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(put_ItemBorder)(THIS_ BOOL fItemBorder) PURE;

	/**
	 * This method retrieves how items are aligned.
	 *
	 * @param pwAlign Pointer to an unsigned 16-bit character that contains one of the following
	 *   alignment flags: - ASFC_ALIGN_BOTTOM: Aligns text with the bottom of the control. -
	 *   ASFC_ALIGN_CENTER: Centers text. - ASFC_ALIGN_LEFT: Aligns text to the left of the control. -
	 *   ASFC_ALIGN_RIGHT: Aligns text to the right of the control. - ASFC_ALIGN_SINGLELINE: Draws text in
	 *   a single line. - ASFC_ALIGN_TOP: Aligns text with the top of the control. - ASFC_ALIGN_VCENTER:
	 *   Centers text vertically.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(get_Alignment)(THIS_ short *pwAlign) PURE;
	/**
	 * This method sets how items are aligned.
	 *
	 * @param pwAlign Pointer to an unsigned 16-bit character that contains one of the following
	 *   alignment flags: - ASFC_ALIGN_BOTTOM: Aligns text with the bottom of the control. -
	 *   ASFC_ALIGN_CENTER: Centers text. - ASFC_ALIGN_LEFT: Aligns text to the left of the control. -
	 *   ASFC_ALIGN_RIGHT: Aligns text to the right of the control. - ASFC_ALIGN_SINGLELINE: Draws text in
	 *   a single line. - ASFC_ALIGN_TOP: Aligns text with the top of the control. - ASFC_ALIGN_VCENTER:
	 *   Centers text vertically. - ASFC_ALIGN_WORDBREAK: Draws text with word breaks.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(put_Alignment)(THIS_ short wAlign) PURE;

	/**
	 * This method gets the highlight font.
	 *
	 * @param ppFontDisp Pointer to a pointer to the IFontDisp interface for the highlight font.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(get_HiliteFont)(THIS_ IFontDisp **ppFontDisp) PURE;
	/**
	 * This method sets the highlight font.
	 *
	 * @param pFontDisp Pointer to the IFontDisp interface for the highlight font.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(put_HiliteFont)(THIS_ IFontDisp * pFontDisp) PURE;

	/**
	 * This method retrieves whether or not the scroll arrows are visible.
	 *
	 * @param pfScrollArrowsVisible Pointer to a Boolean that is set to TRUE if scroll arrows are
	 *   visible, or to FALSE if not.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(get_ScrollArrowsVisible)(THIS_ BOOL *pfScrollArrowsVisible) PURE;
	/**
	 * This method sets whether or not the scroll arrows are visible.
	 *
	 * @param fScrollArrowsVisible Boolean that is set to TRUE if scroll arrows are visible, or to FALSE
	 *   if not.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(put_ScrollArrowsVisible)(THIS_ BOOL fScrollArrowsVisible) PURE;

	/**
	 * This method gets the color used for item captions.
	 *
	 * @param pclrItemCaption Pointer to the color used for item captions.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 *
	 * Use the GetRValue, GetGValue, and GetBValue macros to get the color components of
	 * pclrItemCaption.
	 */
	STDMETHOD(get_ItemCaptionColor)(THIS_ OLE_COLOR *pclrCaption) PURE;
	/**
	 * This method sets the color used for item captions.
	 *
	 * @param clrItemCaption Color used for item captions.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 *
	 * Use the RGB macro to set the components of clrItemCaption before passing clrItemCaption to the
	 * method.
	 */
	STDMETHOD(put_ItemCaptionColor)(THIS_ OLE_COLOR clrCaption) PURE;

	/**
	 * This method gets the highlight color of the power list box.
	 *
	 * @param pclrHiliteColor Pointer to the highlight color of the power list box.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 *
	 * Use the GetRValue, GetGValue, and GetBValue macros to get the color components of
	 * pclrHiliteColor.
	 */
	STDMETHOD(get_HiliteColor)(THIS_ OLE_COLOR *pclrHilite) PURE;
	/**
	 * This method sets the highlight color of the power list box.
	 *
	 * @param clrHiliteColor Highlight color of the power list box.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 *
	 * Use the RGB macro to set the components of clrHiliteColor before passing clrHiliteColor to the
	 * method.
	 */
	STDMETHOD(put_HiliteColor)(THIS_ OLE_COLOR clrHilite) PURE;

	/**
	 * This method gets the color used for highlighted text.
	 *
	 * @param pclrHiliteText Pointer to the color used for highlighted text.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 *
	 * Use the GetRValue, GetGValue, and GetBValue macros to get the color components of pclrHiliteText.
	 */
	STDMETHOD(get_HiliteTextColor)(THIS_ OLE_COLOR *pclrHiliteText) PURE;
	/**
	 * This method sets the color used for highlighted text.
	 *
	 * @param clrHiliteText Color used for highlighted text.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 *
	 * Use the RGB macro to set the components of clrHiliteText before passing clrHiliteText to the
	 * method.
	 */
	STDMETHOD(put_HiliteTextColor)(THIS_ OLE_COLOR clrHiliteText) PURE;

	/**
	 * This method gets the highlight color of the caption.
	 *
	 * @param pclrHiliteCaption Pointer to the highlight color of the caption.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 *
	 * Use the GetRValue, GetGValue, and GetBValue macros to get the color components of
	 * pclrHiliteCaption.
	 */
	STDMETHOD(get_HiliteCaptionColor)(THIS_ OLE_COLOR *pclrHiliteCaption) PURE;
	/**
	 * This method sets the highlight color of the caption.
	 *
	 * @param clrHiliteCaption Highlight color of the caption.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 *
	 * Use the RGB macro to set the components of clrHiliteCaption before passing clrHiliteCaption to
	 * the method.
	 */
	STDMETHOD(put_HiliteCaptionColor)(THIS_ OLE_COLOR clrHiliteCaption) PURE;

	/**
	 * This method retrieves the color used for item borders.
	 *
	 * @param pclrItemBorder Pointer to the color used for item borders.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 *
	 * Use the GetRValue, GetGValue, and GetBValue macros to get the color components of pclrItemBorder.
	 */
	STDMETHOD(get_ItemBorderColor)(THIS_ OLE_COLOR *pclrItemBorder) PURE;
	/**
	 * This method sets the color used for item borders.
	 *
	 * @param clrItemBorder Color used for item borders.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 *
	 * Use the RGB macro to set the components of clrItemBorder before passing clrItemBorder to the
	 * method.
	 */
	STDMETHOD(put_ItemBorderColor)(THIS_ OLE_COLOR clrItemBorder) PURE;

	/**
	 * This method retrieves whether or not the power list box should wrap around-return to the
	 * beginning-when it reaches the end of the list.
	 *
	 * @param pfCircular Pointer to a Boolean that is set to TRUE if the power list box should wrap, or
	 *   to FALSE if not. It is TRUE by default.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(get_Circular)(THIS_ BOOL* pfCircular) PURE;
	/**
	 * This method sets whether or not the power list box should wrap around -return to the
	 * beginning-when it reaches the end of the list.
	 *
	 * @param fCircular Boolean that is set to TRUE if power list box should wrap, or to FALSE if not.
	 *   It is TRUE by default.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(put_Circular)(THIS_ BOOL fCircular) PURE;

	/**
	 * This method adds a new item to a power list box.
	 *
	 * @param lItemId Long integer that contains the identifier of the item.
	 * @param lType Long integer that contains the item type. It is one of the following values: -
	 *   ASFC_PWRLB_TYPE_COMMAND: Specifies a command. - ASFC_PWRLB_TYPE_EDIT: Specifies an edit box. -
	 *   ASFC_PWRLB_TYPE_STRINGSPINNER: Specifies a string spinner. - ASFC_PWRLB_TYPE_INTSPINNER:
	 *   Specifies an integer spinner.
	 * @param ppdispItem Pointer to the pointer to item's IDispatch interface.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 *
	 * The item is added to the end of the list. To interact with the item, call QueryInterface on the
	 * IDispatch interface.
	 *
	 * It is possible to use duplicate identifiers. However, if you do so, you can no longer identify
	 * items by their identifier.
	 */
	STDMETHOD(Add)(THIS_ long lItemId, long lType, IDispatch **ppdispItem) PURE;
	/**
	 * This method inserts an item at a specified index.
	 *
	 * @param lIndex Long integer that contains the index for the new item.
	 * @param lItemId Long integer that contains the identifier of the item.
	 * @param lType Long integer that contains the item type. It is one of the following values: -
	 *   ASFC_PWRLB_TYPE_COMMAND: Specifies a command. - ASFC_PWRLB_TYPE_EDIT: Specifies an edit box. -
	 *   ASFC_PWRLB_TYPE_STRINGSPINNER: Specifies a string spinner. - ASFC_PWRLB_TYPE_INTSPINNER:
	 *   Specifies an integer spinner.
	 * @param ppdispItem Pointer to the pointer to item's IDispatch interface.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(InsertAt)(THIS_ long lIndex, long lItemId, long lType, IDispatch **ppdispItem) PURE;
	/**
	 * This method retrieves a pointer to an item specified by its index.
	 *
	 * @param lIndex Long integer that contains the index of the item.
	 * @param ppdispItem Pointer to a pointer to the item's IDispatch interface.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(ItemAt)(THIS_ long lIndex, IDispatch **ppdispItem) PURE;
	/**
	 * This method retrieves a pointer to an item specified by its identifier.
	 *
	 * @param lItemId Long integer that contains the identifier of the item.
	 * @param ppdispItem Pointer to the pointer to item's IDispatch interface.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(Item)(THIS_ long lItemId, IDispatch **ppdispItem) PURE;
    /**
     * This method finds the item that has a value that matches the value of bstr.
     *
     * @param bstr Unicode string to search for.
     * @param lIndexStart Long integer that contains the starting index.
     * @param pIndex Pointer to the index of the item that matches bstr.
     *
     * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
     *
     * If this is a sorted list box, a binary search is performed; otherwise, a linear search is
     * conducted.
     */
    STDMETHOD(FindItem) (THIS_ BSTR bstr, long indexStart, long *plIndex) PURE;
    /**
     * This method finds the item that matches the first character of the Unicode string specified in
     * bstr.
     *
     * @param bstr Unicode string to search for.
     * @param lIndexStart Long integer that contains the starting index.
     * @param pIndex Pointer to the index of the item that partially matches bstr.
     *
     * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
     */
    STDMETHOD(FindItemPartial) (THIS_ BSTR bstr, long indexStart, long *plIndex) PURE;
	/**
	 * This method specifies the list of status images.
	 *
	 * @param hImage Handle to the image list.
	 * @param hImageMask Handle to the image list mask. The mask specifies which images in the list are
	 *   displayed.
	 * @param cImages Number of images in the list
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(put_StatusItemsImageList)(THIS_ OLE_HANDLE hImage, OLE_HANDLE hImageMask, short cImages) PURE;
	/**
	 * This method specifies the list of status images.
	 *
	 * @param phImage Pointer to the handle of the image list.
	 * @param phImageMask Pointer to the handle to the image list mask. The mask specifies which images
	 *   in the list are displayed.
	 * @param pcImages Pointer to the number of images in the list
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(get_StatusItemsImageList)(THIS_ OLE_HANDLE *phImage, OLE_HANDLE *phImageMask, short *pcImages) PURE;

 	/**
 	 * This method sets whether or not the interaction symbols are shown.
 	 *
 	 * @param fShowInteractionSymbols Boolean that is set to TRUE if interaction symbols are to be
 	 *   shown, or to FALSE if not.
 	 *
 	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
 	 */
 	STDMETHOD(put_ShowInteractionSymbols)(THIS_ BOOL fShow) PURE;
	/**
	 * This method retrieves whether or not the interaction symbols are shown.
	 *
	 * @param pfShowInteractionSymbols Pointer to a Boolean that is set to TRUE if interaction symbols
	 *   are to be shown, or to FALSE if not.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(get_ShowInteractionSymbols)(THIS_ BOOL *pfShow) PURE;

	/**
	 * This method adds an item to the power list box and retrieves an interface that can be used to
	 * interact with the item.
	 *
	 * @param ppItem Pointer to a pointer to an interface, such as IASPowerListBoxEdit, that can be used
	 *   to interact with the item directly.
	 * @param lItemId Long integer that contains the identifier of the item.
	 * @param lType Long integer that contains the item type. It is one of the following values: -
	 *   ASFC_PWRLB_TYPE_COMMAND: Specifies a command. - ASFC_PWRLB_TYPE_EDIT: Specifies an edit box. -
	 *   ASFC_PWRLB_TYPE_STRINGSPINNER: Specifies a string spinner. - ASFC_PWRLB_TYPE_INTSPINNER:
	 *   Specifies an integer spinner.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 *
	 * Use this method if you need to add an item to a Power List box and then interact with it. By
	 * using CreateItem, you do not have to call QueryInterface to get the necessary interface.
	 */
	STDMETHOD(CreateItem)(THIS_ IASPowerListBoxItem** ppItem, long lItemID, long lCtrlType) PURE;

	/**
	 * This method specifies a pointer to the sink interface used to obtain null command item captions.
	 *
	 * @param pSink Pointer to the sink interface used to obtain NULL command item captions.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(put_ProvideCommandDataSink)(THIS_ IASProvidePowerListBoxCommandData *pSink) PURE;
	/**
	 * This method retrieves a pointer to the sink interface used to obtain null command item captions.
	 *
	 * @param ppSink Pointer to the pointer to the sink interface used to obtain NULL command item
	 *   captions.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(get_ProvideCommandDataSink)(THIS_ IASProvidePowerListBoxCommandData **ppSink) PURE;


	/**
	 * This method loads items from a menu resource file.
	 *
	 * @param hinst Handle to an instance.
	 * @param pszMenuName Pointer to the null-terminated string that contains the menu name.
	 * @param dwMenuState Specifies the state of the menu.
	 *
	 * @return An appropriate HRESULT value is returned.
	 *
	 * This function is additive and can be executed more than once to load multiple items.
	 */
	STDMETHOD(AddItemsFromResource)(THIS_ HINSTANCE hinst, PCWSTR pszMenuName, DWORD dwMenuState) PURE;
	
 	/**
 	 * This method sets a mode that controls how a power list box updates the title bar of a form.
 	 *
 	 * @param wTitlebarUpdateMode Specifies the mode that a power list box uses when updating the title
 	 *   bar of a form. It is any combination of the following values. - ASTUM_CAPTION: Undefined. -
 	 *   ASTUM_CAPTIONEDIT: Sets the caption of the title bar equal to the caption of a power list box
 	 *   edit item when editing that item. - ASTUM_CAPTIONMENU: Sets the caption of the title bar equal to
 	 *   the caption of the power list box when IfmManage::put_Menu is called. - ASTUM_EDITHIDENAV: Hides
 	 *   the NavArrow control when editing a power list box item. - ASTUM_STATUS: Sets the status of the
 	 *   title bar equal to the status of the current item. - ASTUM_SUBCAPTION: Sets the subcaption of the
 	 *   title bar equal to a string, for example "2 of 7," that shows the position of the power list box
 	 *
 	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
 	 */
 	STDMETHOD(put_TitlebarUpdateMode)(THIS_ WORD wTitlebarUpdateMode) PURE;
	/**
	 * This method retrieves a mode that indicates how a power list box updates the title bar of a form.
	 *
	 * @param pwTitlebarUpdateMode Pointer to a WORD that receives the mode that a power list box uses
	 *   when updating the title bar of a form. The mode is any combination of the following values. -
	 *   ASTUM_CAPTION: Undefined. - ASTUM_CAPTIONEDIT: Sets the caption of the title bar equal to the
	 *   caption of a power list box edit item when editing that item. - ASTUM_CAPTIONMENU: Sets the
	 *   caption of the title bar equal to the caption of the power list box when IfmManage::put_Menu is
	 *   called. - ASTUM_EDITHIDENAV: Hides the navigational arrows control when editing a power list box
	 *   item. - ASTUM_STATUS: Sets the status of the title bar equal to the status of the current item. -
	 *   ASTUM_SUBCAPTION: Sets the subcaption of the title bar equal to a string, for example "2 of 7,"
	 *   that shows the position of the power list box
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(get_TitlebarUpdateMode)(THIS_ WORD *pwTitlebarUpdateMode) PURE;

	STDMETHOD(put_SpeakItemSink)(THIS_ IASPowerListSpeakItemSink *pSink) PURE;
	STDMETHOD(get_SpeakItemSink)(THIS_ IASPowerListSpeakItemSink **ppSink) PURE;

	
};

#undef  INTERFACE
#define INTERFACE

//
// The HTMLControl
//
#if defined(__cplusplus) && !defined(CINTERFACE)
/**
 * This interface provides methods to manage an HTML control.
 *
 * The IASHTMLControl interface, which has a global unique identifier (GUID) equal to
 * IID_ASHTMLCONTROL, extends the IASControl interface. All IASControl methods are available through
 * IASHTMLControl. The HTML control has a programmatic identifier equal to APC_HTMLControl.
 *
 * This interface allows an application to display HTML-formatted documents. If an IAPCSpeech
 * interface is defined and registered with the control, text-to-speech can be used to read the
 * document aloud.
 */
struct IASHTMLControl : public IASControl
#else
DECLARE_INTERFACE_(IASHTMLControl, IASControl)
#endif
{
	/**
	 * This method retrieves the current HTML string.
	 *
	 * @param pbstrHTML Pointer to an HTML-formatted string.
	 *
	 * @return An appropriate HRESULT value is returned.
	 *
	 * If pbstrHTML is set, the contents of pbstrHTML are currently being displayed.
	 */
	STDMETHOD(get_HTML)(THIS_ BSTR *pbstrHTML) PURE;
	/**
	 * This method displays an HTML-formatted string.
	 *
	 * @param pbstrHTML Pointer to an HTML-formatted string.
	 *
	 * @return An appropriate HRESULT value is returned.
	 *
	 * This method is similar to IASControl::put_Caption, but is used to display HTML-formatted text.
	 * When the property is changed, the control is repainted with the new text. Use
	 * IASControl::put_Caption to display a plain text string. Appropriate HTML tags are added.
	 */
	STDMETHOD(put_HTML)(THIS_ BSTR bstrHTML) PURE;

	/**
	 * This method retrieves the style flags for the control.
	 *
	 * @param pdwStyle Pointer to the DWORD that specifies the style of the control. It is any
	 *   combination of the following flags: - ASFC_HTML_SPEAK_TITLE: Includes the title in text-to-speech
	 *   (TTS) output. - ASFC_HTML_SPEAK_BODY: Includes all body text in TTS output. -
	 *   ASFC_HTML_SHOW_HSCROLL: Displays horizontal scroll arrows, when appropriate. -
	 *   ASFC_HTML_SHOW_VSCROLL: Displays vertical scroll arrows, when appropriate. -
	 *   ASFC_HTML_SHOW_ANCHORS: Displays the anchors.
	 *
	 * @return An appropriate HRESULT value is returned.
	 */
	STDMETHOD(get_Style)(THIS_ DWORD *pdwStyle) PURE;
	/**
	 * This method sets style flags for the control.
	 *
	 * @param dwStyle Specifies the style of the control. It is any combination of the following flags:
	 *   - ASFC_HTML_SPEAK_TITLE: Includes the title in text-to-speech (TTS) output. -
	 *   ASFC_HTML_SPEAK_BODY: Includes all body text in TTS output. - ASFC_HTML_SHOW_HSCROLL: Displays
	 *   horizontal scroll arrows, when appropriate. - ASFC_HTML_SHOW_VSCROLL: Displays vertical scroll
	 *   arrows, when appropriate. - ASFC_HTML_SHOW_ANCHORS: Displays the anchors.
	 *
	 * @return An appropriate HRESULT value is returned.
	 */
	STDMETHOD(put_Style)(THIS_ DWORD dwStyle) PURE;

	/**
	 * This method retrieves a pointer to the HTML notification sink.
	 *
	 * @param ppNotify Pointer to the pointer to the control's notification sink.
	 *
	 * @return An appropriate HRESULT value is returned.
	 */
	STDMETHOD(get_HTMLNotifySink)(THIS_ IASHTMLControlNotifySink **pNotify) PURE;
	/**
	 * This method receives HTML events from the control.
	 *
	 * @param ppNotify Pointer to the pointer to the control's notification sink.
	 *
	 * @return An appropriate HRESULT value is returned.
	 *
	 * HTML events that put_HTMLNotifySink might receive include requests to load images and HTML META
	 * tags.
	 */
	STDMETHOD(put_HTMLNotifySink)(THIS_ IASHTMLControlNotifySink *pNotify) PURE;

	// provide scrolling 
	/**
	 * This method controls vertical scrolling.
	 *
	 * @param wp Specifies vertical scrolling styles. The low-order word of wp is one of the following
	 *   values: - SB_BOTTOM: Scrolls to the bottom or to the right side of the document. - SB_LINEDOWN:
	 *   Scrolls down or right one line, or approximately 16 pixels. - SB_LINEUP: Scrolls up or left one
	 *   line, or approximately 16 pixels. - SB_PAGEDOWN: Scrolls down or right one page, or the height of
	 *   the control. - SB_PAGEUP: Scrolls up or left one page, or the height of the control. -
	 *   SB_THUMBTRACK: Scrolls to an absolute vertical position in the document. The high-order word of
	 *   wp specifies the position. - SB_TOP: Scrolls to the top or left side of the document.
	 *
	 * @return An appropriate HRESULT value is returned.
	 */
	STDMETHOD(VScroll)(THIS_ WPARAM wp) PURE;
	/**
	 * This method controls horizontal scrolling.
	 *
	 * @param wp Specifies horizontal scrolling styles. The low-order word of wp is one of the following
	 *   values: - SB_BOTTOM: Scrolls to the bottom or to the right side of the document. - SB_LINEDOWN:
	 *   Scrolls down or right one line, or approximately 16 pixels. - SB_LINEUP: Scrolls up or left one
	 *   line, or approximately 16 pixels. - SB_PAGEDOWN: Scrolls down or right one page, or the height of
	 *   the control. - SB_PAGEUP: Scrolls up or left one page, or the height of the control. -
	 *   SB_THUMBTRACK: Scrolls to an absolute horizontal position in the document. The high-order word of
	 *   wp specifies the position. - SB_TOP: Scrolls to the top or left side of the document.
	 *
	 * @return An appropriate HRESULT value is returned.
	 */
	STDMETHOD(HScroll)(THIS_ WPARAM wp) PURE;
	/**
	 * This method jumps to an anchor elsewhere in the document.
	 *
	 * @param bstrAnchor HTML-formatted string that identifies the anchor.
	 *
	 * @return An appropriate HRESULT value is returned.
	 */
	STDMETHOD(JumpToAnchor)(THIS_ BSTR bstrAnchor) PURE;
	/**
	 * This method scrolls an image into view.
	 *
	 * @param dwCookie Specifies a cookie that identifies the image. It is passed to the application
	 *   through the IASHTMLControlNotifySink::InlineImage function when an image is encountered.
	 *
	 * @return An appropriate HRESULT value is returned.
	 */
	STDMETHOD(ScrollIntoView)(THIS_ DWORD dwCookie) PURE;
	/**
	 * This method retrieves a RECT structure that defines the currently visible portion of the HTML
	 * document.
	 *
	 * @param rcVisible RECT structure that defines the currently visible portion of the document.
	 *
	 * @return An appropriate HRESULT value is returned.
	 *
	 * The first two members of the rcVisible RECT structure contain the current HScroll and VScroll
	 * values, respectively. They define the upper-left corner of the visible rectangle.
	 */
	STDMETHOD(get_VisibleRect)(THIS_ RECT* rcVisible) PURE;
	
	STDMETHOD(get_HighlightMode)(THIS_ long *pcMode) PURE;
	STDMETHOD(put_HighlightMode)(THIS_ long cMode) PURE;

	// notifications response handling
	/**
	 * This method is invoked if an application is unable to load an image.
	 *
	 * @param dwCookie Specifies a cookie that identifies the image. It is passed to the application
	 *   through the IASHTMLControlNotifySink::InlineImage function when an image is encountered.
	 *
	 * @return An appropriate HRESULT value is returned.
	 *
	 * This method informs the control that it should change from displaying "is loading" to displaying
	 * "load failed."
	 */
	STDMETHOD(ImageFail)(THIS_ DWORD dwCookie) PURE;
	/**
	 * This method displays an image.
	 *
	 * @param dwCookie Specifies a cookie that identifies the image. It is passed to the application
	 *   through the IASHTMLControlNotifySink::InlineImage function when an image is encountered.
	 * @param bOwnBitmap Boolean that is set to TRUE if the bitmap is to be destroyed after use, or to
	 *   FALSE if the bitmap is to be used again.
	 * @param lOrigHeight Long integer that contains the height of the original bitmap. The displayed
	 *   height may be different.
	 * @param lOrigWidth Long integer that contains the width of the original bitmap. The displayed
	 *   width may be different.
	 * @param hBitmap Handle to the bitmap.
	 *
	 * @return An appropriate HRESULT value is returned.
	 */
	STDMETHOD(put_Image)(THIS_ DWORD dwCookie, BOOL bOwnBitmap, long lOrigHeight, long lOrigWidth, OLE_HANDLE hBitmap) PURE;
	
};


#undef  INTERFACE
#define INTERFACE

//
// The HTMLControl Notify Sink
//
#if defined(__cplusplus) && !defined(CINTERFACE)
/**
 * This interface provides methods that are used to notify applications of HTML-related events.
 *
 * The IASHTMLControlNotifySink interface, which has a global unique identifier (GUID) equal to
 * IID_ASHTMLCONTROLNOTIFYSINK, extends the IDispatch interface. To receive HTML events,
 * applications must implement an event sink according to this definition, and register it with
 * IASHTMLControl by putting a pointer to the sink in the NotifySink property.
 */
struct IASHTMLControlNotifySink : public IDispatch
#else
DECLARE_INTERFACE_(IASHTMLControlNotifySink, IDispatch)
#endif
{
	/**
	 * This method is invoked when a hot spot is encountered.
	 *
	 * @param pControl Pointer to the active HTML control.
	 * @param bstrTarget HTML-formatted target string.
	 * @param bstrData HTML-formatted data string associated with the target.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 */
	STDMETHOD(HotSpot)(THIS_ IASHTMLControl* pControl, BSTR szTarget, BSTR szData) PURE;
	/**
	 * This method is invoked when an inline image is encountered.
	 *
	 * @param pControl Pointer to the active HTML control.
	 * @param bstrTarget HTML-formatted target string.
	 * @param dwCookie Specifies a cookie that identifies the image. It is passed to the application
	 *   through the IASHTMLControlNotifySink::InlineImage function when an image is encountered.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 */
	STDMETHOD(InlineImage)(THIS_ IASHTMLControl* pControl, BSTR szTarget, DWORD dwCookie) PURE; 
	/**
	 * This method is invoked when a sound tag is encountered.
	 *
	 * @param pControl Pointer to the active HTML control.
	 * @param bstrTarget HTML-formatted target string.
	 * @param iLoop Number of repetitions.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(PlaySound)(THIS_ IASHTMLControl* pControl, BSTR szTarget, int iLoop) PURE; 
	/**
	 * This method is invoked when a title is encountered.
	 *
	 * @param pControl Pointer to the active HTML control.
	 * @param bstrTitle HTML-formatted title string.
	 *
	 * @return NOERROR indicates success. E_OUTOFMEMORY indicates that the system is out of memory.
	 */
	STDMETHOD(Title)(THIS_ IASHTMLControl* pControl, BSTR szTitle) PURE; 
	/**
	 * This method is invoked when a META tag is encountered.
	 *
	 * @param pControl Pointer to the active HTML control.
	 * @param bstrHTTPEQUIV String containing the value of the HTTP-EQUIV attribute of the META tag.
	 * @param bstrContent String containing the value of the CONTENT attribute of the META tag.
	 *
	 * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
	 */
	STDMETHOD(Meta)(THIS_ IASHTMLControl* pControl, BSTR szHTTPEQUIV, BSTR szContent) PURE; 
};


#endif

