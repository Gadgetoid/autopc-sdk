//+----------------------------------------------------------------------------
// 
// File:        keypad.h
//
// Copyight:    (c) 1997, Microsoft Corporation
//              All Rights Reserved
//              Infomation Contained Herein Is Propprietary and Confidential
//
// Contents:    Face plate bus driver defines & function prototypes
//
//-----------------------------------------------------------------------------

#include <apcmsg.h>

#ifndef _KEYPAD_H_
#define _KEYPAD_H_

#ifdef __cplusplus
extern "C" {
#endif

// Telephony device key codes.
#define VK_STAR         VK_F1
#define VK_POUND	    VK_F2
#define VK_SENDCALL		VK_F3
#define VK_ENDCALL		VK_F4
#define VK_MUTE		    VK_F5
#define VK_VOLUMEUP		VK_F6
#define VK_VOLUMEDOWN	VK_F7
#define VK_REDIAL		VK_F8
#define VK_STORE		VK_F9
#define VK_RECALL		VK_F10
#define VK_HOLD		    VK_F11
#define VK_CONFERENCE	VK_F12
#define VK_TRANSFER		VK_F13
#define VK_HOOK			VK_F14
#define VK_CALLBACK		VK_F15
#define VK_SPEAKER		VK_F16

#define VK_SPEECH       VK_F24
#define VK_AUDIO        VK_F23
// VK_F17-VK_F24 are available for definition of other keys on a platform specific basis.
// VK_NUMPAD0 - VK_NUMPAD9 will be the digits on the telephones numeric pad


// IoControl for translating a VKEY to a UNICODE character.
// pInBuf points to the Virtual key value, nInBufSize contains the KeyState value
// pOutBuf points to a buffer to receive the unicode character. If pBytesReturned is
// not NULL then it will be filled with the count of bytes filled (the size of a unicode character)
#define KBDI_VKEYTOUNICODE      0x2000

// IoControl to Generate a pseudo keypad event such as a key down or key up.
// pInBuf points to the Virtual key value, nInBufSize contains the KeyState value
#define KBDI_SETEVENT           0x2002

// Key down/up messages from keypad driver to client application.
#define WM_REMOTE_KEYDOWN       APC_SYS_START
#define WM_REMOTE_KEYUP         APC_SYS_START+1

#ifdef __cplusplus
}
#endif

#endif // _KEYPAD_H_

