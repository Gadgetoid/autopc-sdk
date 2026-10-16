/*****************************************************************************\
*                                                                             *
* TunerAPI.h -  Tuner Application Programming Interface definitions           *
*                                                                             *
*               Version 1.00                                                  *
*                                                                             *
*               Copyright (c) 1998, Microsoft Corp.  All rights reserved      *
*                                                                             *
******************************************************************************/

#include <windows.h>

#ifndef _TunerAPI_H_
#define _TunerAPI_H_

#ifdef __cplusplus
extern "C" {
#endif



#define TC_MUTE         0x00000001		// Tuner Caps - supports MUTE function
#define TC_LOCAL        0x00000002		// Tuner Caps - supports Distance/Local

#define BC_STEREO       0x00010000		// Band Caps - supports Stereo setting
#define BC_RBDS         0x00020000		// Band Caps - supports RBDS setting
#define BC_TWOWAY       0x00040000		// Band Caps - supports TWOWAY setting
 
//
// this defines the bits for TUNERCONFIG structure
//
#define STEREO_ON       BC_STEREO       // Stereo on
#define RBDS_ON			BC_RBDS			// RBDS mode on
#define TWOWAY_ON		BC_TWOWAY		// Two way mode on
#define LOCAL_ON        TC_LOCAL        // Local mode on (vs distance mode)
#define MUTE_ON         TC_MUTE         // Tuner mute mode on
			
#define BAND_AM         0x00000001      // AM band
#define BAND_FM         0x00000002      // FM band
#define BAND_WEATHER	0x00000004		// Weather band
#define BAND_TV         0x00000008      // TV band
#define BAND_CB         0x00000010      // CB band
#define BAND_USER       0x00010000      // start of user defined band

#define FREQ_IN_HZ      1
#define FREQ_IN_KHZ     1000
#define FREQ_IN_MHZ     1000000
#define FREQ_IN_GHZ     1000000000

// Seek options
#define TUNER_SEEK_TUNEDOWN				0x0001
#define TUNER_SEEK_NO_WRAPAROUND		0x0002
#define TUNER_SEEK_NO_MUTE				0x0004

//Seek sensitivity
#define TUNER_SEEK_SENSITIVITY_NORMAL	(WORD)0
#define TUNER_SEEK_SENSITIVITY_HIGH		(WORD)1
#define TUNER_SEEK_SENSITIVITY_LOW		(WORD)2

typedef struct _TUNERDEVCAPS {    
    DWORD           dwMakerID;          // Manufacture/Model ID
    DWORD           dwDrvVer;           // Tuner Device driver version, HIWORD=Major, LOWWORD=Minor
    DWORD           dwTunerCaps;        // supported tuner features
    DWORD           dwBands;            // supported bands 
    DWORD           dwReserved1;        // reserved
    DWORD           dwReserved2;        // reserved
} TUNERDEVCAPS, *PTUNERDEVCAPS;

typedef  struct _FREQUENCY {
    DWORD           dwFreqValue;        // Frequency value
    DWORD           dwFreqUnit;         // Frequency unit
} FREQUENCY, *PFREQUENCY;

typedef struct _TUNERBANDINFO {
    DWORD           dwBandID;           // Band identifer
    FREQUENCY       RangeLow;           // Low end of the Tuner frequency range
    FREQUENCY       RangeHigh;          // High end of the Tuner frequency range
    FREQUENCY       MinTuningStep;      // Min tuning step
    DWORD           dwBandCaps;         // Band capabilities
} TUNERBANDINFO, *PTUNERBANDINFO;

typedef struct _TUNERCONFIG { 
    DWORD           dwBand;             // Band selection
    FREQUENCY       CurrentFreq;        // Current Frequency setting
    FREQUENCY       SeekStep;           // station seek step size
    FREQUENCY       RangeLow;           // Low end of the Band frequency range
    FREQUENCY       RangeHigh;          // High end of the Band frequency range
    DWORD           dwState;            // Settings
} TUNERCONFIG, *PTUNERCONFIG;

typedef struct _FIELDSTRENGTH {
    unsigned short  MaxStrength;
    unsigned short  CurrentStrength;
} FIELDSTRENGTH,*PFIELDSTRENGTH;

typedef struct _SIGNALINFO { 
    BOOL            fIsStation;         // Suggest it is tuned to a valid station
	FREQUENCY		CurrentFreq;		// Current tuned station
    FIELDSTRENGTH   FieldStrength;      // FieldStrength Level Information
    DWORD           dwMultiPath;        // MultiPath Level Information
    BOOL            fStereoPresent;     // Stereo Pilot present
    DWORD           dwReserved;         // reserved DWORD
} SIGNALINFO, *PSIGNALINFO;

typedef BOOL (*SEEK_STATUS_NOTIFY)(PSIGNALINFO);

typedef struct _TUNERSEEKINFO
{
	WORD			wSeekOptions;
	WORD			wSensitivity;
    FREQUENCY       RangeLow;           // Low end of the freq range to search
    FREQUENCY       RangeHigh;          // High end of the freq range to search
	SEEK_STATUS_NOTIFY	fnCallBack;		// call back function
	DWORD			Reserved;
}TUNERSEEKINFO, *PTUNERSEEKINFO;

//
// Tuner API functions
//

BOOL TunerQuery(
    OUT DWORD       *pdwTunerAPIVer,    // version of tuner api
    OUT DWORD       *pdwNumDevs         // number of tuner devices available
);    

BOOL TunerGetDevCaps (
    IN DWORD            dwDeviceID,     // device to be queried
    OUT PTUNERDEVCAPS   pTunerDevCaps   // pointer to TUNERDEVCAPS buffer
);

//
// return Value: the number of band information obtained
//
DWORD TunerGetBandInfo(
    IN  DWORD       dwDeviceID,         // tuner device id
    IN  DWORD       dwBands,            // a mask for interested bands
    OUT PTUNERBANDINFO   pBandInfo,     // pointer to a buffer to receive band information
    IN  DWORD       dwBufSize,          // size of the receiving buffer
    OUT DWORD       *pdwActualOutSize   // pointer to actual size of buffer with info
);

HANDLE TunerOpen(
    DWORD           dwTunerId           // specify which tuner to open
);    

BOOL TunerGetConfig(
    IN HANDLE           hTuner,         // specify tuner
    OUT PTUNERCONFIG    pTunerConfig    // address of tuner config structure
);    

BOOL TunerSetConfig(
    IN HANDLE       hTuner,             // specify which tuner to config
    IN PTUNERCONFIG pTunerConfig        // address of tuner config structure
);    

BOOL TunerGetSignalInfo(
    IN HANDLE       hTuner,             // handle of the tuner device
    OUT PSIGNALINFO pSignalInfo         // address of a tuner signal structure
);

BOOL TunerReset(
    IN HANDLE       hTuner              // handle of the tuner device
);

BOOL TunerSeekStation(
    IN HANDLE		hTuner,				// handle of the tuner device
	PTUNERSEEKINFO pTunerSeekInfo
);      

BOOL TunerCancelSeek(					// cancels the last seek operation
	IN HANDLE	hTuner
);

BOOL TunerClose(
    IN HANDLE       hTuner              // handle of the tuner device
);    

#ifdef __cplusplus
}
#endif
#endif // _TunerAPI_H_
