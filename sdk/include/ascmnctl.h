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

DECLARE_INTERFACE_(IASLabel, IASControl)
	{
    //
    // Use these to assign a user defined image to the label. However, some controls
    // that inherit from IASLabel, may choose to ignore this property
    //
    STDMETHOD(get_Image) (THIS_ OLE_HANDLE *phImage, OLE_HANDLE *phImageMask) PURE;
    STDMETHOD(put_Image) (THIS_ OLE_HANDLE hImage, OLE_HANDLE hImageMask,
                            long x, long y, long dxWidth, long dyHeight) PURE;
	//
	// Properties
	//
	STDMETHOD(get_Format) (THIS_ UINT *pwFormat) PURE;
	STDMETHOD(put_Format) (THIS_ UINT wFormat) PURE;
    //
    // Use these to align images and captions
    //
    STDMETHOD(get_ImageAlignH) (THIS_ short *pwAlign) PURE;
    STDMETHOD(put_ImageAlignH) (THIS_ short wAlign) PURE;
    STDMETHOD(get_ImageAlignV) (THIS_ short *pwAlign) PURE;
    STDMETHOD(put_ImageAlignV) (THIS_ short wAlign) PURE;
    STDMETHOD(get_CaptionAlign) (THIS_ short *pwAlign) PURE;
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

DECLARE_INTERFACE_(IASImageMenu, IASControl)
    {
	STDMETHOD(get_Count) (THIS_ long *pcItems) PURE;
	
    STDMETHOD(get_Image) (THIS_ long index, OLE_HANDLE *phImage, OLE_HANDLE *phImageMask, 
                        BOOL *pfBitmap) PURE;
    STDMETHOD(put_Image) (THIS_ long index, OLE_HANDLE hImage, OLE_HANDLE hImageMask,  
                        BOOL fBitmap) PURE;

    STDMETHOD(get_String) (THIS_ long index, BSTR *pbstr) PURE;
    STDMETHOD(put_String) (THIS_ long index, BSTR bstr) PURE;

    STDMETHOD(get_ID) (THIS_ long index, short *pwID) PURE;
    STDMETHOD(put_ID) (THIS_ long index, short wID) PURE;

    STDMETHOD(Add) (THIS_ OLE_HANDLE hImage, OLE_HANDLE hImageMask, BSTR bstr, 
                    short wID, BOOL fBitmap) PURE;
    STDMETHOD(InsertAt) (THIS_ long index, OLE_HANDLE hImage, OLE_HANDLE hImageMask, 
                        BSTR bstr, short wID, BOOL fBitmap) PURE;
    STDMETHOD(RemoveAtIndex) (THIS_ long index) PURE;
    STDMETHOD(RemoveByID) (THIS_ short wID) PURE;

    STDMETHOD(get_FocusIndex) (THIS_ long *plIndex) PURE;
    STDMETHOD(put_FocusIndex) (THIS_ long lIndex) PURE;

    STDMETHOD(get_ItemHeight) (THIS_ long *plHeight) PURE;
    STDMETHOD(put_ItemHeight) (THIS_ long lHeight) PURE;
    STDMETHOD(get_ItemWidth) (THIS_ long *plWidth) PURE;
    STDMETHOD(put_ItemWidth) (THIS_ long lWidth) PURE;
    STDMETHOD(get_ImageHeight) (THIS_ long *plHeight) PURE;
    STDMETHOD(put_ImageHeight) (THIS_ long lHeight) PURE;
    STDMETHOD(get_ImageWidth) (THIS_ long *plWidth) PURE;
    STDMETHOD(put_ImageWidth) (THIS_ long lWidth) PURE;

    STDMETHOD(get_Horizontal) (THIS_ BOOL *pfHorizontal) PURE;
    STDMETHOD(put_Horizontal) (THIS_ BOOL fHorizontal) PURE;

    STDMETHOD(get_MenuLabel) (THIS_ IDispatch **ppdispLabel) PURE;
    STDMETHOD(put_MenuLabel) (THIS_ IDispatch *pdispLabel) PURE;

	STDMETHOD(get_FocusColor) (THIS_ OLE_COLOR *pclr) PURE;
	STDMETHOD(put_FocusColor) (THIS_ OLE_COLOR clr) PURE;

    STDMETHOD(get_CenteredFocus) (THIS_ BOOL *pfFocus) PURE;
    STDMETHOD(put_CenteredFocus) (THIS_ BOOL fFocus) PURE;

    STDMETHOD(put_Overlay)(THIS_ BOOL fFocus, THIS_ OLE_HANDLE hImage, 
                                 OLE_HANDLE hImageMask, BOOL fBitmap) PURE;

    STDMETHOD(get_Overlay)(THIS_ BOOL fFocus, THIS_ OLE_HANDLE * phImage, 
                                 OLE_HANDLE * phImageMask, BOOL * pfBitmap) PURE;  

    STDMETHOD(put_NonFocusImageColor)(THIS_ OLE_COLOR clr, BOOL fSet) PURE;
    STDMETHOD(get_NonFocusImageColor)(THIS_ OLE_COLOR * pclr, BOOL * pfSet) PURE;

    STDMETHOD(put_OverlayOffset)(THIS_ BOOL fFocus, long left, long top) PURE;
    STDMETHOD(get_OverlayOffset)(THIS_ BOOL fFocus, long * pleft, long * ptop ) PURE;
                                 
    STDMETHOD(get_MenuWrap) (THIS_ BOOL *pfWrap) PURE;
    STDMETHOD(put_MenuWrap) (THIS_ BOOL fWrap) PURE;
   };

#undef  INTERFACE
#define INTERFACE

DECLARE_INTERFACE_(IASShellMenu, IASImageMenu)
    {
    STDMETHOD(get_HotKey) (THIS_ long index, unsigned char *pbID) PURE;
    STDMETHOD(put_HotKey) (THIS_ long index, unsigned char bID) PURE;

    STDMETHOD(get_ItemFlags) (THIS_ long index, unsigned char *pbFlags) PURE;
    STDMETHOD(put_ItemFlags) (THIS_ long index, unsigned char bFlags, unsigned char bMask) PURE;

    STDMETHOD(get_LabelHeight) (THIS_ long *plHeight) PURE;
    STDMETHOD(put_LabelHeight) (THIS_ long lHeight) PURE;

	STDMETHOD(get_LabelForeColor) (THIS_ OLE_COLOR *pclr) PURE;
	STDMETHOD(put_LabelForeColor) (THIS_ OLE_COLOR clr) PURE;

	STDMETHOD(get_LabelBackColor) (THIS_ OLE_COLOR *pclr) PURE;
	STDMETHOD(put_LabelBackColor) (THIS_ OLE_COLOR clr) PURE;	
    };

#undef  INTERFACE
#define INTERFACE

DECLARE_INTERFACE_(IASProgressBar, IASControl)
    {
    STDMETHOD(get_Value) (THIS_ long *plValue) PURE;
    STDMETHOD(put_Value) (THIS_ long lValue) PURE;    
    STDMETHOD(get_Min) (THIS_ long *plMin) PURE;
    STDMETHOD(put_Min) (THIS_ long lMin) PURE;
    STDMETHOD(get_Max) (THIS_ long *plMax) PURE;
    STDMETHOD(put_Max) (THIS_ long lMax) PURE;

    STDMETHOD(get_RangeCount) (THIS_ long *plCount) PURE;
    STDMETHOD(put_RangeCount) (THIS_ long lCount) PURE;

    STDMETHOD(get_RangeValue) (THIS_ long lRangeIndex, long *plValue) PURE;
    STDMETHOD(put_RangeValue) (THIS_ long lRangeIndex, long lValue) PURE;

    STDMETHOD(get_RangeColor) (THIS_ long lRangeIndex, OLE_COLOR *pclr) PURE;
    STDMETHOD(put_RangeColor) (THIS_ long lRangeIndex, OLE_COLOR clr) PURE;

    STDMETHOD(get_Horizontal) (THIS_ BOOL *pfHorizontal) PURE;
    STDMETHOD(put_Horizontal) (THIS_ BOOL fHorizontal) PURE;

	STDMETHOD(get_Steps)(THIS_ long *plSteps) PURE;
	STDMETHOD(put_Steps)(THIS_ long lSteps) PURE;

    };

#undef  INTERFACE
#define INTERFACE

DECLARE_INTERFACE_(IASSlider, IASProgressBar)
    {     
	STDMETHOD(get_Incr) (THIS_ long *plIncr) PURE;
    STDMETHOD(put_Incr) (THIS_ long lIncr) PURE;

    STDMETHOD(get_HiliteColor) (THIS_ OLE_COLOR *pclr) PURE;
    STDMETHOD(put_HiliteColor) (THIS_ OLE_COLOR clr) PURE;
    };


#undef  INTERFACE

#define INTERFACE
DECLARE_INTERFACE_(IASVVI, IASProgressBar)
    {
    STDMETHOD(get_Mirrored) (THIS_ BOOL *pfMirrored) PURE;
    STDMETHOD(put_Mirrored) (THIS_ BOOL fMirrored) PURE;
	
    STDMETHOD(get_Inverted) (THIS_ BOOL *pfInverted) PURE;
    STDMETHOD(put_Inverted) (THIS_ BOOL fInverted) PURE;

   };
#undef  INTERFACE

#define INTERFACE

DECLARE_INTERFACE_(IASMemorySlider, IASSlider)
    {
    STDMETHOD(put_StoreUsed) (THIS_ long lStoreUsed) PURE;
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

DECLARE_INTERFACE_(IASCharSpinner, IASControl)
    {
    STDMETHOD(get_ItemHeight) (THIS_ long *plHeight) PURE;
    STDMETHOD(put_ItemHeight) (THIS_ long lHeight) PURE;
    
    STDMETHOD(get_CharSet) (THIS_ BSTR *pbstr) PURE;
    STDMETHOD(put_CharSet) (THIS_ BSTR bstr) PURE;
    
    STDMETHOD(get_CurChar) (THIS_ short *pch) PURE;
    STDMETHOD(put_CurChar) (THIS_ short ch) PURE;
    
    STDMETHOD(NextChar) (THIS) PURE;
    STDMETHOD(PrevChar) (THIS) PURE;
    
    STDMETHOD(put_SpinMode) (THIS_ short mode) PURE;
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

DECLARE_INTERFACE_(IASEditBox, IASCharSpinner)
    {
    STDMETHOD(get_ItemWidth) (THIS_ long *plWidth) PURE;
    STDMETHOD(put_ItemWidth) (THIS_ long lWidth) PURE;

    STDMETHOD(get_Text) (THIS_ BSTR *pbstr) PURE;
    STDMETHOD(put_Text) (THIS_ BSTR bstr) PURE;
    
    STDMETHOD(get_Selection) (THIS_ wchar_t *pch) PURE;
    STDMETHOD(put_Selection) (THIS_ wchar_t ch) PURE;
    STDMETHOD(get_SelectionIndex) (THIS_ short *pwich) PURE;
    STDMETHOD(put_SelectionIndex) (THIS_ short wich) PURE;

    STDMETHOD(get_NumChars) (THIS_ short *pwcch) PURE;
    STDMETHOD(get_MaxChars) (THIS_ short *pwcchMax) PURE;
    STDMETHOD(put_MaxChars) (THIS_ short wcchMax) PURE;

    STDMETHOD(get_ReadOnly) (THIS_ BOOL *pfReadOnly) PURE;
    STDMETHOD(put_ReadOnly) (THIS_ BOOL fReadOnly) PURE;

	STDMETHOD(get_Editing) (THIS_ BOOL *pfEditing) PURE;
	STDMETHOD(put_Editing) (THIS_ BOOL fEditing) PURE;

    STDMETHOD(get_TrimRight) (THIS_ BOOL *pfTrimRight) PURE;
    STDMETHOD(put_TrimRight) (THIS_ BOOL fTrimRight) PURE;

	STDMETHOD(Insert) (THIS_ short ch) PURE;
    STDMETHOD(Delete) (THIS) PURE;

   	STDMETHOD(get_TextPrivate) (THIS_ BOOL *pfTextPrivate) PURE;
	STDMETHOD(put_TextPrivate) (THIS_ BOOL fTextPrivate) PURE;
    };

//
// A Canvas. Use for free style drawing
//
#undef	INTERFACE
#define	INTERFACE

DECLARE_INTERFACE_(IASCanvas, IASControl)
    {
    STDMETHOD(GetDC) (THIS_ OLE_HANDLE *phdc, BOOL fOffScreen) PURE;
	STDMETHOD(Commit) (THIS) PURE;
	STDMETHOD(ClipAndCommit) (THIS_ OLE_HANDLE hrgnClip) PURE;
    STDMETHOD(CommitAt) (THIS_ long xDest, long yDest, long xSrc, long ySrc, long dx, long dy) PURE;
    STDMETHOD(CommitFrom) (THIS_ long xSrc, long ySrc) PURE;
    STDMETHOD(put_AutoCommit) (THIS_ BOOL fAutoCommit, long xSrc, long ySrc) PURE;
    STDMETHOD(get_AutoCommit) (THIS_ BOOL * pfAutoCommit, long * pxSrc, long * pySrc) PURE;
    };

//
// CLOCK
//
#undef	INTERFACE
#define	INTERFACE

DECLARE_INTERFACE_(IASClock, IASControl)
    {
    STDMETHOD(get_ClockFormat) (BOOL * pfTime, BSTR * pbstrFormat, LONG * pFormatFlags ) PURE;
    STDMETHOD(put_ClockFormat) ( BOOL fTime, BSTR bstrFormat, LONG FormatFlags) PURE;
    STDMETHOD(get_LabelFormat) (BOOL * pfTime, BSTR * pbstrFormat, LONG * pFormatFlags ) PURE;
    STDMETHOD(put_LabelFormat) ( BOOL fTime, BSTR bstrFormat, LONG FormatFlags) PURE;
    STDMETHOD(put_ClockLabel) (THIS_ IDispatch *pdispLabel) PURE;
    STDMETHOD(put_ClockLabel0) (THIS_ IDispatch *pdispLabel) PURE;
    };

//
// TIMER
//
#undef  INTERFACE
#define INTERFACE

DECLARE_INTERFACE_(IASTimer, IASControl)
    {
    STDMETHOD(get_Interval) (THIS_ long *plMillis) PURE;
    STDMETHOD(put_Interval) (THIS_ long lMillis) PURE;
    STDMETHOD(get_TimerEnabled) (THIS_ BOOL *pfEnabled) PURE;
    STDMETHOD(put_TimerEnabled) (THIS_ BOOL fEnable) PURE;
     };

#undef  INTERFACE
#define INTERFACE

DECLARE_INTERFACE_(IASPlayList, IASControl)
    {
    STDMETHOD(get_TrackActive) (THIS_ unsigned char biTrack) PURE;
    STDMETHOD(put_TrackActive) (THIS_ unsigned char biTrack, BOOL fActive) PURE;
    STDMETHOD(Reset) (THIS) PURE;

    STDMETHOD(get_NumTracks) (THIS_ unsigned char *pbcTracks) PURE;
    STDMETHOD(put_NumTracks) (THIS_ unsigned char bcTracks) PURE;
    
	STDMETHOD(get_BorderColor) (THIS_ OLE_COLOR *pclr) PURE;
	STDMETHOD(put_BorderColor) (THIS_ OLE_COLOR clr) PURE;
    STDMETHOD(get_HiliteBorderColor) (THIS_ OLE_COLOR *pclr) PURE;
    STDMETHOD(put_HiliteBorderColor) (THIS_ OLE_COLOR clr) PURE;    
	STDMETHOD(get_ActiveForeColor) (THIS_ OLE_COLOR *pclr) PURE;
	STDMETHOD(put_ActiveForeColor) (THIS_ OLE_COLOR clr) PURE;
	STDMETHOD(get_ActiveBackColor) (THIS_ OLE_COLOR *pclr) PURE;
	STDMETHOD(put_ActiveBackColor) (THIS_ OLE_COLOR clr) PURE;
	STDMETHOD(get_InactiveForeColor) (THIS_ OLE_COLOR *pclr) PURE;
	STDMETHOD(put_InactiveForeColor) (THIS_ OLE_COLOR clr) PURE;
	STDMETHOD(get_InactiveBackColor) (THIS_ OLE_COLOR *pclr) PURE;
	STDMETHOD(put_InactiveBackColor) (THIS_ OLE_COLOR clr) PURE;

    STDMETHOD(get_ItemHeight) (THIS_ long *plHeight) PURE;
    STDMETHOD(put_ItemHeight) (THIS_ long lHeight) PURE;
    STDMETHOD(get_ItemWidth) (THIS_ long *plWidth) PURE;
    STDMETHOD(put_ItemWidth) (THIS_ long lWidth) PURE;

    STDMETHOD(put_CurrentTrack) (THIS_ unsigned char bcTrack) PURE;
    STDMETHOD(get_CurrentTrack) (THIS_ unsigned char* pbcTrack) PURE;
    };

#undef  INTERFACE
#define INTERFACE

DECLARE_INTERFACE_(IASCrossHairs, IASControl)
    {
    STDMETHOD(get_XVal) (THIS_ short *pwVal) PURE;
    STDMETHOD(put_XVal) (THIS_ short wVal) PURE;
    STDMETHOD(get_YVal) (THIS_ short *pwVal) PURE;
    STDMETHOD(put_YVal) (THIS_ short wVal) PURE;

    STDMETHOD(get_XMinus) (THIS_ short *pwVal) PURE;
    STDMETHOD(put_XMinus) (THIS_ short wVal) PURE;
    STDMETHOD(get_XPlus) (THIS_ short *pwVal) PURE;
    STDMETHOD(put_XPlus) (THIS_ short wVal) PURE;

    STDMETHOD(get_YMinus) (THIS_ short *pwVal) PURE;
    STDMETHOD(put_YMinus) (THIS_ short wVal) PURE;
    STDMETHOD(get_YPlus) (THIS_ short *pwVal) PURE;
    STDMETHOD(put_YPlus) (THIS_ short wVal) PURE;

    STDMETHOD(get_CrossHairHilite) (THIS_ BOOL *pfHorz, BOOL *pfVert) PURE;
    STDMETHOD(put_CrossHairHilite) (THIS_ BOOL fHorz, BOOL fVert) PURE;
    
    STDMETHOD(get_CrossHairColor) (THIS_ OLE_COLOR *pclr) PURE;
    STDMETHOD(put_CrossHairColor) (THIS_ OLE_COLOR clr) PURE;
    STDMETHOD(get_CrossHairBoxColor) (THIS_ OLE_COLOR *pclr) PURE;
    STDMETHOD(put_CrossHairBoxColor) (THIS_ OLE_COLOR clr) PURE;
    STDMETHOD(get_CrossHairHiliteColor) (THIS_ OLE_COLOR *pclr) PURE;
    STDMETHOD(put_CrossHairHiliteColor) (THIS_ OLE_COLOR clr) PURE;
    STDMETHOD(get_AxisColor) (THIS_ OLE_COLOR *pclr) PURE;
    STDMETHOD(put_AxisColor) (THIS_ OLE_COLOR clr) PURE;
    };

//
// Tabber control
//
#undef  INTERFACE
#define INTERFACE

DECLARE_INTERFACE_(IASTabber, IASControl)
{
	//
	// basics
	//
    STDMETHOD(Add)				(THIS_ BSTR bstr, long lData) PURE;
    STDMETHOD(AddImage)			(THIS_ OLE_HANDLE hImage, OLE_HANDLE hImageMask,long lData) PURE;
    STDMETHOD(AddWithIndex)		(THIS_ BSTR bstr, long lData, long* lpIndex) PURE;
    STDMETHOD(InsertAt)			(THIS_ long index,BSTR bstr,  long lData) PURE;
    STDMETHOD(RemoveAt)			(THIS_ long index) PURE;
    STDMETHOD(RemoveAll)		(THIS_ ) PURE;
    STDMETHOD(SpeakFocusTab)	(THIS_ ) PURE;
	STDMETHOD(get_Count)		(THIS_ long* pcItems) PURE;
	//
	// get / set attributes / properties
	//
    STDMETHOD(get_TabStatus)            (THIS_ long	index, long *plStatus) PURE;
    STDMETHOD(put_TabStatus)            (THIS_ long	index, long lStatus) PURE;
    STDMETHOD(get_String)				(THIS_ long	index, BSTR *pbstr) PURE;
    STDMETHOD(put_String)				(THIS_ long	index, BSTR bstr) PURE;
    STDMETHOD(get_SpeechCommandId)		(THIS_ long	index, long *plSpeechId) PURE;
    STDMETHOD(put_SpeechCommandId)		(THIS_ long	index, long lSpeechId) PURE;
    STDMETHOD(get_ItemData)				(THIS_ long	index, long *plData) PURE;
    STDMETHOD(put_ItemData)				(THIS_ long	index, long lData) PURE;
    STDMETHOD(get_TabMinWidth)			(THIS_ long* lpWidth) PURE;
    STDMETHOD(put_TabMinWidth)			(THIS_ long lWidth) PURE;
    STDMETHOD(get_TabColor)				(THIS_ OLE_COLOR *pclr) PURE;
    STDMETHOD(put_TabColor)				(THIS_ OLE_COLOR clr) PURE;
    STDMETHOD(get_TabTextColor)			(THIS_ OLE_COLOR *pclr) PURE;
    STDMETHOD(put_TabTextColor)			(THIS_ OLE_COLOR clr) PURE;
    STDMETHOD(get_BorderColor)			(THIS_ OLE_COLOR *pclr) PURE;
    STDMETHOD(put_BorderColor)			(THIS_ OLE_COLOR clr) PURE;
    STDMETHOD(get_FocusIndex)			(THIS_ long *plIndex) PURE;
    STDMETHOD(put_FocusIndex)			(THIS_ long lIndex) PURE;
    STDMETHOD(get_TabFocusForeColor)	(THIS_ OLE_COLOR *pclr) PURE;
    STDMETHOD(put_TabFocusForeColor)	(THIS_ OLE_COLOR clr) PURE;
    STDMETHOD(get_TabFocusBackColor)	(THIS_ OLE_COLOR *pclr) PURE;
    STDMETHOD(put_TabFocusBackColor)	(THIS_ OLE_COLOR clr) PURE;
	STDMETHOD(get_Circular)(THIS_ BOOL* pfCircular) PURE;
	STDMETHOD(put_Circular)(THIS_ BOOL fCircular) PURE;
	STDMETHOD(get_DeferredNotification)(THIS_ BOOL* pfDeferredNotification) PURE;
	STDMETHOD(put_DeferredNotification)(THIS_ BOOL fDeferredNotification) PURE;
	STDMETHOD(get_VoiceMenu)(THIS_ IVCmdMenu** ppVoiceMenu) PURE;
	STDMETHOD(put_VoiceMenu)(THIS_ IVCmdMenu*  pVoiceMenu) PURE;
    STDMETHOD(get_VoiceMenuActivateCommand)(THIS_ BSTR *pbstrCommand) PURE;
    STDMETHOD(put_VoiceMenuActivateCommand)(THIS_ BSTR bstrCommand) PURE;

	//
	// Images
	//
    STDMETHOD(get_Image)		(THIS_ long index, OLE_HANDLE *phImage, OLE_HANDLE *phImageMask) PURE;
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
DECLARE_INTERFACE_(IASPowerListBoxItem, IDispatch)
{
	STDMETHOD(get_ItemData)(THIS_ long *plData) PURE;
	STDMETHOD(put_ItemData)(THIS_ long lData) PURE;

	STDMETHOD(get_StatusItemsMask)(THIS_ long *plMask) PURE;
	STDMETHOD(put_StatusItemsMask)(THIS_ long lMask) PURE;

	STDMETHOD(get_Caption)(THIS_ BSTR *pbstrCaption) PURE;
	STDMETHOD(put_Caption)(THIS_ BSTR bstrCaption) PURE;

	STDMETHOD(get_ItemId)(THIS_ long *plItemId) PURE;
	STDMETHOD(put_ItemId)(THIS_ long lItemId) PURE;

	STDMETHOD(get_Type)(THIS_ long *plType) PURE;

};

#undef  INTERFACE
#define INTERFACE

//
// PowerListBox command item
//
DECLARE_INTERFACE_(IASPowerListBoxCommand,IASPowerListBoxItem)
{
};

#undef  INTERFACE
#define INTERFACE

DECLARE_INTERFACE_(IASPowerListBoxEdit, IASPowerListBoxItem)
{
	STDMETHOD(get_Text)(THIS_ BSTR *pbstr) PURE;
	STDMETHOD(put_Text)(THIS_ BSTR bstr) PURE;

	STDMETHOD(get_MaxChars)(THIS_ short *wcchMax) PURE;
	STDMETHOD(put_MaxChars)(THIS_ short wcchMax) PURE;

	STDMETHOD(get_CharSet)(THIS_ BSTR *pbstr) PURE;
	STDMETHOD(put_CharSet)(THIS_ BSTR bstr) PURE;

};

#undef  INTERFACE
#define INTERFACE

DECLARE_INTERFACE_(IASPowerListBoxStringSpinner, IASPowerListBoxItem)
{
	STDMETHOD(get_Items)(THIS_ BSTR *pbstrItems) PURE;
	STDMETHOD(put_Items)(THIS_ BSTR bstrItems) PURE;

	STDMETHOD(get_Value)(THIS_ BSTR *pbstrValue) PURE;
	STDMETHOD(put_Value)(THIS_ BSTR bstrValue) PURE;

	STDMETHOD(get_FocusIndex)(THIS_ long *plFocusIndex) PURE;
	STDMETHOD(put_FocusIndex)(THIS_ long lFocusIndex) PURE;

	STDMETHOD(get_Circular)(THIS_ BOOL* pfCircular) PURE;
	STDMETHOD(put_Circular)(THIS_ BOOL fCircular) PURE;

};


#undef  INTERFACE
#define INTERFACE

DECLARE_INTERFACE_(IASPowerListBoxIntSpinner, IASPowerListBoxItem)
{
	STDMETHOD(get_Flags)(THIS_ short *pwFlags) PURE;
	STDMETHOD(put_Flags)(THIS_ short wFlags) PURE;

	STDMETHOD(get_Min)(THIS_ long *plMin) PURE;
	STDMETHOD(put_Min)(THIS_ long lMin) PURE;

	STDMETHOD(get_Max)(THIS_ long *plMax) PURE;
	STDMETHOD(put_Max)(THIS_ long lMax) PURE;

	STDMETHOD(get_Step)(THIS_ long *plStep) PURE;
	STDMETHOD(put_Step)(THIS_ long lStep) PURE;

	STDMETHOD(get_Value)(THIS_ long *plValue) PURE;
	STDMETHOD(put_Value)(THIS_ long lValue) PURE;

	STDMETHOD(get_Units)(THIS_ BSTR *pbstr) PURE;
	STDMETHOD(put_Units)(THIS_ BSTR bstr) PURE;

	STDMETHOD(get_Circular)(THIS_ BOOL* pfCircular) PURE;
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
DECLARE_INTERFACE_(IASProvidePowerListBoxCommandData, IUnknown)
{
	STDMETHOD(get_Caption)(THIS_ long lIndex, long lItemId, long lItemData, BSTR *pbstrCaption) PURE;
};


#undef  INTERFACE
#define INTERFACE

//
// The PowerListBox
//
DECLARE_INTERFACE_(IASPowerListBox, IASControl)
{
	STDMETHOD(get_Count)(THIS_ long *pcItems) PURE;

	STDMETHOD(RemoveAll)(THIS) PURE;
	STDMETHOD(Remove)(THIS_ long lItemId) PURE;
	STDMETHOD(RemoveAt)(THIS_ long lIndex) PURE;
	STDMETHOD(get_CommandPrompt)(THIS_ BSTR *pbstrCommandPrompt) PURE;
	STDMETHOD(put_CommandPrompt)(THIS_ BSTR bstrCommandPrompt) PURE;

	STDMETHOD(get_Edit)(THIS_ IDispatch **ppdispEdit) PURE;

    // the value to be display when an edit item is empty
	STDMETHOD(get_EditEmptyText)(THIS_ BSTR *pbstrEmptyText) PURE;
	STDMETHOD(put_EditEmptyText)(THIS_ BSTR bstrEmptyText) PURE;

	STDMETHOD(get_ReadOnly)(THIS_ BOOL *pfReadOnly) PURE;
	STDMETHOD(put_ReadOnly)(THIS_ BOOL fReadOnly) PURE;

	STDMETHOD(get_FocusIndex)(THIS_ long *plFocusIndex) PURE;
	STDMETHOD(put_FocusIndex)(THIS_ long lFocusIndex) PURE;

	STDMETHOD(get_TopVisibleIndex)(THIS_ long *plTopVisibleIndex) PURE;
	STDMETHOD(put_TopVisibleIndex)(THIS_ long lTopVisibleIndex) PURE;

	STDMETHOD(get_FocusId)(THIS_ long *plFocusId) PURE;
	STDMETHOD(put_FocusId)(THIS_ long lFocusId) PURE;

	STDMETHOD(get_TopVisibleId)(THIS_ long *plTopVisibleId) PURE;
	STDMETHOD(put_TopVisibleId)(THIS_ long lTopVisibleId) PURE;

	STDMETHOD(get_ItemHeight)(THIS_ long *plItemHeight) PURE;
	STDMETHOD(put_ItemHeight)(THIS_ long lItemHeight) PURE;

	STDMETHOD(get_Sorted)(THIS_ BOOL *pfSorted) PURE;
	STDMETHOD(put_Sorted)(THIS_ BOOL fSorted) PURE;

	STDMETHOD(get_SortOrder)(THIS_ BOOL *pfAscending) PURE;
	STDMETHOD(put_SortOrder)(THIS_ BOOL fAscending) PURE;

	STDMETHOD(get_CenteredFocus)(THIS_ BOOL *pfCenteredFocus) PURE;
	STDMETHOD(put_CenteredFocus)(THIS_ BOOL fCenteredFocus) PURE;

	STDMETHOD(get_ItemBorder)(THIS_ BOOL *pfItemBorder) PURE;
	STDMETHOD(put_ItemBorder)(THIS_ BOOL fItemBorder) PURE;

	STDMETHOD(get_Alignment)(THIS_ short *pwAlign) PURE;
	STDMETHOD(put_Alignment)(THIS_ short wAlign) PURE;

	STDMETHOD(get_HiliteFont)(THIS_ IFontDisp **ppFontDisp) PURE;
	STDMETHOD(put_HiliteFont)(THIS_ IFontDisp * pFontDisp) PURE;

	STDMETHOD(get_ScrollArrowsVisible)(THIS_ BOOL *pfScrollArrowsVisible) PURE;
	STDMETHOD(put_ScrollArrowsVisible)(THIS_ BOOL fScrollArrowsVisible) PURE;

	STDMETHOD(get_ItemCaptionColor)(THIS_ OLE_COLOR *pclrCaption) PURE;
	STDMETHOD(put_ItemCaptionColor)(THIS_ OLE_COLOR clrCaption) PURE;

	STDMETHOD(get_HiliteColor)(THIS_ OLE_COLOR *pclrHilite) PURE;
	STDMETHOD(put_HiliteColor)(THIS_ OLE_COLOR clrHilite) PURE;

	STDMETHOD(get_HiliteTextColor)(THIS_ OLE_COLOR *pclrHiliteText) PURE;
	STDMETHOD(put_HiliteTextColor)(THIS_ OLE_COLOR clrHiliteText) PURE;

	STDMETHOD(get_HiliteCaptionColor)(THIS_ OLE_COLOR *pclrHiliteCaption) PURE;
	STDMETHOD(put_HiliteCaptionColor)(THIS_ OLE_COLOR clrHiliteCaption) PURE;

	STDMETHOD(get_ItemBorderColor)(THIS_ OLE_COLOR *pclrItemBorder) PURE;
	STDMETHOD(put_ItemBorderColor)(THIS_ OLE_COLOR clrItemBorder) PURE;

	STDMETHOD(get_Circular)(THIS_ BOOL* pfCircular) PURE;
	STDMETHOD(put_Circular)(THIS_ BOOL fCircular) PURE;

	STDMETHOD(Add)(THIS_ long lItemId, long lType, IDispatch **ppdispItem) PURE;
	STDMETHOD(InsertAt)(THIS_ long lIndex, long lItemId, long lType, IDispatch **ppdispItem) PURE;
	STDMETHOD(ItemAt)(THIS_ long lIndex, IDispatch **ppdispItem) PURE;
	STDMETHOD(Item)(THIS_ long lItemId, IDispatch **ppdispItem) PURE;
    STDMETHOD(FindItem) (THIS_ BSTR bstr, long indexStart, long *plIndex) PURE;
    STDMETHOD(FindItemPartial) (THIS_ BSTR bstr, long indexStart, long *plIndex) PURE;
	STDMETHOD(put_StatusItemsImageList)(THIS_ OLE_HANDLE hImage, OLE_HANDLE hImageMask, short cImages) PURE;
	STDMETHOD(get_StatusItemsImageList)(THIS_ OLE_HANDLE *phImage, OLE_HANDLE *phImageMask, short *pcImages) PURE;

 	STDMETHOD(put_ShowInteractionSymbols)(THIS_ BOOL fShow) PURE;
	STDMETHOD(get_ShowInteractionSymbols)(THIS_ BOOL *pfShow) PURE;

	STDMETHOD(CreateItem)(THIS_ IASPowerListBoxItem** ppItem, long lItemID, long lCtrlType) PURE;

	STDMETHOD(put_ProvideCommandDataSink)(THIS_ IASProvidePowerListBoxCommandData *pSink) PURE;
	STDMETHOD(get_ProvideCommandDataSink)(THIS_ IASProvidePowerListBoxCommandData **ppSink) PURE;


	STDMETHOD(AddItemsFromResource)(THIS_ HINSTANCE hinst, PCWSTR pszMenuName, DWORD dwMenuState) PURE;
	
 	STDMETHOD(put_TitlebarUpdateMode)(THIS_ WORD wTitlebarUpdateMode) PURE;
	STDMETHOD(get_TitlebarUpdateMode)(THIS_ WORD *pwTitlebarUpdateMode) PURE;

	STDMETHOD(put_SpeakItemSink)(THIS_ IASPowerListSpeakItemSink *pSink) PURE;
	STDMETHOD(get_SpeakItemSink)(THIS_ IASPowerListSpeakItemSink **ppSink) PURE;

	
};

#undef  INTERFACE
#define INTERFACE

//
// The HTMLControl
//
DECLARE_INTERFACE_(IASHTMLControl, IASControl)
{
	STDMETHOD(get_HTML)(THIS_ BSTR *pbstrHTML) PURE;
	STDMETHOD(put_HTML)(THIS_ BSTR bstrHTML) PURE;

	STDMETHOD(get_Style)(THIS_ DWORD *pdwStyle) PURE;
	STDMETHOD(put_Style)(THIS_ DWORD dwStyle) PURE;

	STDMETHOD(get_HTMLNotifySink)(THIS_ IASHTMLControlNotifySink **pNotify) PURE;
	STDMETHOD(put_HTMLNotifySink)(THIS_ IASHTMLControlNotifySink *pNotify) PURE;

	// provide scrolling 
	STDMETHOD(VScroll)(THIS_ WPARAM wp) PURE;
	STDMETHOD(HScroll)(THIS_ WPARAM wp) PURE;
	STDMETHOD(JumpToAnchor)(THIS_ BSTR bstrAnchor) PURE;
	STDMETHOD(ScrollIntoView)(THIS_ DWORD dwCookie) PURE;
	STDMETHOD(get_VisibleRect)(THIS_ RECT* rcVisible) PURE;
	
	STDMETHOD(get_HighlightMode)(THIS_ long *pcMode) PURE;
	STDMETHOD(put_HighlightMode)(THIS_ long cMode) PURE;

	// notifications response handling
	STDMETHOD(ImageFail)(THIS_ DWORD dwCookie) PURE;
	STDMETHOD(put_Image)(THIS_ DWORD dwCookie, BOOL bOwnBitmap, long lOrigHeight, long lOrigWidth, OLE_HANDLE hBitmap) PURE;
	
};


#undef  INTERFACE
#define INTERFACE

//
// The HTMLControl Notify Sink
//
DECLARE_INTERFACE_(IASHTMLControlNotifySink, IDispatch)
{
	STDMETHOD(HotSpot)(THIS_ IASHTMLControl* pControl, BSTR szTarget, BSTR szData) PURE;
	STDMETHOD(InlineImage)(THIS_ IASHTMLControl* pControl, BSTR szTarget, DWORD dwCookie) PURE; 
	STDMETHOD(PlaySound)(THIS_ IASHTMLControl* pControl, BSTR szTarget, int iLoop) PURE; 
	STDMETHOD(Title)(THIS_ IASHTMLControl* pControl, BSTR szTitle) PURE; 
	STDMETHOD(Meta)(THIS_ IASHTMLControl* pControl, BSTR szHTTPEQUIV, BSTR szContent) PURE; 
};


#endif

