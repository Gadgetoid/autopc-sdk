//      Copyright (c) 1995 Microsoft Corporation

#ifndef __KEYBD_H__
#define __KEYBD_H__

#ifdef __cplusplus
extern "C" {
#endif


typedef UINT32  KEY_STATE_FLAGS;

#define KeyStateToggledFlag			0x0001	//	Key is toggled.
#define KeyStateGetAsyncDownFlag	0x0002	//	Key went down since last GetAsyncKey call.
#define KeyStateReserved4			0x0004
#define KeyStateReserved8			0x0008
#define KeyStateReserved10			0x0010
#define KeyStateReserved20			0x0020
#define KeyStatePrevDownFlag		0x0040	//	Key was previously down.
#define KeyStateDownFlag			0x0080	//	Key is currently down.

#define KeyStateKeyEventFlag		0x80000000	//	Internal
#define KeyShiftAnyCtrlFlag			0x40000000  //  L or R control is down.
#define KeyShiftAnyShiftFlag		0x20000000  //  L or R shift is down.
#define KeyShiftAnyAltFlag			0x10000000  //  L or R alt is down.
#define KeyShiftCapitalFlag			0x08000000  //  VK_CAPITAL is toggled.
#define KeyShiftLeftCtrlFlag		0x04000000  //  L control is down.
#define KeyShiftLeftShiftFlag		0x02000000  //  L shift is down.
#define KeyShiftLeftAltFlag			0x01000000  //  L alt is down.
#define KeyShiftLeftWinFlag			0x00800000  //  L Win key is down.
#define KeyShiftRightCtrlFlag		0x00400000  //  R control is down.
#define KeyShiftRightShiftFlag		0x00200000  //  R shift is down.
#define KeyShiftRightAltFlag		0x00100000  //  R alt is down.
#define KeyShiftRightWinFlag		0x00080000  //  R Win key is down.
#define KeyShiftReserved40000		0x00040000  //  Reserved.
#define KeyShiftDeadFlag			0x00020000  //  Corresponding char is dead char.
#define KeyShiftNoCharacterFlag		0x00010000  //  No corresponding char.

#define	KeyShiftLanguageFlag1		0x00008000  //  Use for language specific shifts.
#define KeyShiftKeybdEventFlag		0x00004000	//	Not for external use.

#define KeyShiftUseVKNullFlag		0x00002000  //  Not for external use.
#define KeyShiftReserved1000		0x00001000  //  Reserved.
#define KeyShiftReserved800			0x00000800  //  Reserved.
#define KeyShiftReserved400			0x00000400  //  Reserved.
#define KeyShiftReserved200			0x00000200  //  Reserved.
#define KeyShiftReserved100			0x00000100  //  Reserved.

// Japanese keyboard
#define	KeyShiftKanaFlag			KeyShiftLanguageFlag1  //  Kana lock is toggled.


#define KeyStateIsDown(Flags)           (Flags&KeyStateDownFlag)
#define KeyStateIsPrevDown(Flags)       (Flags&KeyStatePrevDownFlag)
#define KeyStateIsToggled(Flags)        (Flags&KeyStateToggledFlag)
#define KeyStateIsDownTransition(Flags) ( KeyStateIsDown(Flags) && !KeyStateIsPrevDown(Flags) )


#define COUNT_VKEYS     256


typedef UINT8   KEY_STATE[COUNT_VKEYS];




//
// KeyboardDriverGetDeviceInfo query capability definitions
//

#define KBDI_VKEY_TO_UNICODE_INFO_ID	0


struct KBDI_VKEY_TO_UNICODE_INFO
	{
	UINT32  cbToUnicodeState;
	UINT32  cMaxToUnicodeCharacters;
	};


#define KBDI_AUTOREPEAT_INFO_ID	1



struct KBDI_AUTOREPEAT_INFO
	{
	INT32	CurrentInitialDelay;
	INT32	CurrentRepeatRate;
	INT32	cInitialDelaysSelectable;
	INT32	cRepeatRatesSelectable;
	};


#define KBDI_AUTOREPEAT_SELECTIONS_INFO_ID	2

// INTERNATIONAL
#define KBDI_KEYBOARD_STATUS_ID 3


#define KBDI_KEYBOARD_PRESENT	0x0001	
#define KBDI_KEYBOARD_ENABLED	0x0002
#define KBDI_KEYBOARD_ENTER_ESC	0x0004
#define KBDI_KEYBOARD_ALPHA_NUM	0x0008


// INTERNATIONAL

#ifdef __cplusplus
}
#endif



#endif


