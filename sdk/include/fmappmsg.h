//+----------------------------------------------------------------------------
// 
// File:		fmappmsg.h
//
// Copyight:	(c) 1997, Microsoft Corporation
// 				All Rights Reserved
//				Infomation Contained Herein Is Propprietary and Confidential
//
// Contents: 	Message Name and value defines
//
//-----------------------------------------------------------------------------

// This file contains the Inter-application message name and value defines that
// are used to implement the functionality of a platform conforming to the Apollo 
// guidelines.

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
// General App message definitions
//-----------------------------------------------------------------------------

// Forms manager sucondary focus messages

// Message Name

#define APC_MSGNAME_FOCUSINFO    (L"APC_APPMSG_FOCUSINFO")

// Information Ids passed in wParam

#define APC_FOCUSMSG_AUDIOOUT       1           //  lParam is FALSE when focus lost 


//-----------------------------------------------------------------------------
// Audio Application 
//-----------------------------------------------------------------------------

// Message Name 
#define APC_APPMSGNAME_AUDIO    (L"APC_AUDIOAPP_MSG")

// Command IDs, passed in wParam. 

#define APC_AUDIOAPPCMD_INVOKE      1
#define APC_AUDIOAPPCMD_VOLUMEUI    2

// Forms manager sucondary focus messages

// Command IDs, passed in wParam. 

#define APC_AUDIOAPPCMD_INVOKE      1
#define APC_AUDIOAPPCMD_VOLUMEUI    2


#ifdef __cplusplus
}
#endif

