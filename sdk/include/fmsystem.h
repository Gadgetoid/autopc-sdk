//+----------------------------------------------------------------------------
// 
// File:		fmsystem.h
//
// Copyight:	(c) 1997, Microsoft Corporation
// 				All Rights Reserved
//				Infomation Contained Herein Is Propprietary and Confidential
//
// Contents: 	FM System state definition
//
//-----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

// FMSetSystemStatus is the API for informing the Apollo UI of a system wide
// state change. This API is available to drivers and applications that need
// not have any other other exposure to the FormsManager

// The FMSetSystemStatus will initiate braodcast messages to the running
// FM apps as appropriate for the state change

HRESULT	__stdcall	FMSetSystemStatus( DWORD dwSystemStateId, DWORD	dwState);

// FMGetSystemStatus is the API for getting the state of the Forms Managers 
// internal view of the status of the system. Note this API only returns what 
// value was last given to the forms manager (via FMSetSystemStatus or some 
// other means) and does not neccessarily reflect the actual current value of the
// status in a dynamically changing environment. 

HRESULT	__stdcall	FMGetSystemStatus( DWORD dwSystemStateId, DWORD	* pdwState);

// Defines for FMSetSystemStatus dwSystemStateId

#define	FM_SYSSTATE_BACKUPBATTERY		1
#define FM_SYSSTATE_MUTE				2
#define FM_SYSSTATE_ASR					3
#define FM_SYSSTATE_DASHCD				4
#define FM_SYSSTATE_USERPOWER			5
	
#ifdef __cplusplus
}
#endif

