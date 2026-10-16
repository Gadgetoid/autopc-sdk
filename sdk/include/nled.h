/*++

Copyright (c) 1994 - 1997 Microsoft Corporation


File Name:	nled.h

Abstract:   Notification LED interface.

Notes:

The notification LED is distinguished from other LED's which may be on the system
in that it can be on or blinking even if the rest of the system is powered down.  This
implies a certain level of hardware support for this functionality.

--*/
#ifndef __NLED_H__
#define __NLED_H__

#ifdef __cplusplus
extern "C" {
#endif


//
// NLedDriverGetDeviceInfo query definitions
//

#define NLED_COUNT_INFO_ID	0


struct NLED_COUNT_INFO
	{
	UINT	cLeds;
	};


#define NLED_SUPPORTS_INFO_ID	1


struct NLED_SUPPORTS_INFO
	{
	UINT	LedNum;
	LONG	lCycleAdjust;
	BOOL	fAdjustTotalCycleTime;
	BOOL	fAdjustOnTime;
	BOOL	fAdjustOffTime;
	BOOL	fMetaCycleOn;
	BOOL	fMetaCycleOff;
	};



#define NLED_SETTINGS_INFO_ID	2


struct NLED_SETTINGS_INFO
	{
	UINT	LedNum;
	INT		OffOnBlink;
	LONG	TotalCycleTime;
    LONG	OnTime;
    LONG	OffTime;
    INT		MetaCycleOn;
    INT		MetaCycleOff;
	};


#ifdef __cplusplus
}
#endif



#endif

