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

/**
 * This structure contains information about the device capabilities of a tuner.
 *
 * Use TunerQuery to determine which tuners are available. Use TunerGetDevCaps to find out what each
 * can do.
 */
typedef struct _TUNERDEVCAPS {    
    /**
     * Specifies the manufacturer identifier.
     */
    DWORD           dwMakerID;          // Manufacture/Model ID
    /**
     * Specifies the tuner device driver version. The high-order word contains the major version number,
     * and the low-order word contains the minor version number.
     */
    DWORD           dwDrvVer;           // Tuner Device driver version, HIWORD=Major, LOWWORD=Minor
    /**
     * Specifies which tuner features can be configured. It is a combination of the following flags:
     *
     * - TC_MUTE: Specifies muting.
     *
     * - TC_LOCAL: Specifies local mode versus distance mode. If this flag is not specified, then
     * distance mode is implied.
     */
    DWORD           dwTunerCaps;        // supported tuner features
    /**
     * Specifies which bands are supported. It is a combination of the following flags:
     *
     * - BAND_AM: Specifies an AM band.
     *
     * - BAND_FM: Specifies an FM band.
     *
     * - BAND_TV: Specifies a TV band.
     *
     * - BAND_CB: Specifies a CB band.
     *
     * - BAND_USER: Specifies a user-defined band.
     */
    DWORD           dwBands;            // supported bands 
    /**
     * Reserved.
     */
    DWORD           dwReserved1;        // reserved
    /**
     * Reserved.
     */
    DWORD           dwReserved2;        // reserved
} TUNERDEVCAPS, *PTUNERDEVCAPS;

/**
 * This structure describes a frequency.
 */
typedef  struct _FREQUENCY {
    /**
     * Specifies the frequency value. The units used are specified by dwFreqUnit.
     */
    DWORD           dwFreqValue;        // Frequency value
    /**
     * Specifies the frequency units. It is one of the following flags:
     *
     * - FREQ_IN_HZ: Frequency is in units of hertz.
     *
     * - FREQ_IN_KHZ: Frequency is in units of kilohertz.
     *
     * - FREQ_IN_MHZ: Frequency is in units of megahertz.
     *
     * - FREQ_IN_GHZ: Frequency is in units of gigahertz.
     */
    DWORD           dwFreqUnit;         // Frequency unit
} FREQUENCY, *PFREQUENCY;

/**
 * This structure contains information on a particular tuner band.
 */
typedef struct _TUNERBANDINFO {
    /**
     * Specifies the band identifier. It is one of the following flags:
     *
     * - BAND_AM: Specifies an AM band.
     *
     * - BAND_FM: Specifies an FM band.
     *
     * - BAND_TV: Specifies a TV band.
     *
     * - BAND_WEATHER: Specifies a weather band.
     *
     * - BAND_CB: Specifies a CB band.
     *
     * - BAND_USER: Specifies a user band. Do not use.
     */
    DWORD           dwBandID;           // Band identifer
    /**
     * Specifies a FREQUENCY structure that contains the low end of the frequency range.
     */
    FREQUENCY       RangeLow;           // Low end of the Tuner frequency range
    /**
     * Specifies a FREQUENCY structure that contains the high end of the frequency range.
     */
    FREQUENCY       RangeHigh;          // High end of the Tuner frequency range
    /**
     * Specifies a FREQUENCY structure that contains the minimum tuning step.
     */
    FREQUENCY       MinTuningStep;      // Min tuning step
    /**
     * Specifies the capabilities of a band. It is one or a combination of the following flags.
     *
     * - BC_STEREO: Supports stereo.
     *
     * - BC_RBDS: Specifies RBDS encoded.
     *
     * - BC_TWOWAY: Supports two-way.
     */
    DWORD           dwBandCaps;         // Band capabilities
} TUNERBANDINFO, *PTUNERBANDINFO;

/**
 * This structure contains information on tuner configuration.
 */
typedef struct _TUNERCONFIG { 
    /**
     * Specifies the current band selection. It is one of the following flags:
     *
     * - BAND_AM: Specifies an AM band.
     *
     * - BAND_FM: Specifies an FM band.
     *
     * - BAND_TV: Specifies a TV band.
     *
     * - BAND_WEATHER: Specifies a weather band.
     *
     * - BAND_CB: Specifies a CB band.
     *
     * - BAND_USER: Specifies a user-defined band.
     */
    DWORD           dwBand;             // Band selection
    /**
     * Specifies a FREQUENCY structure that contains the current frequency.
     */
    FREQUENCY       CurrentFreq;        // Current Frequency setting
    /**
     * Specifies the step size to be used when seeking stations. For example, the standard American FM
     * band has valid frequencies at 0.2 MHz increments, and the standard American AM band has valid
     * frequencies at 10 KHz increments.
     */
    FREQUENCY       SeekStep;           // station seek step size
    /**
     * Specifies the high end of the band frequency range.
     */
    FREQUENCY       RangeLow;           // Low end of the Band frequency range
    /**
     * Specifies the low end of the band frequency range.
     */
    FREQUENCY       RangeHigh;          // High end of the Band frequency range
    /**
     * Specifies the tuner state. It is one or a combination of the following flags:
     *
     * - STEREO_ON: Stereo is on.
     *
     * - LOCAL_ON: Local mode is on, versus distance mode.
     *
     * - MUTE_ON: Tuner muting is on.
     */
    DWORD           dwState;            // Settings
} TUNERCONFIG, *PTUNERCONFIG;

/**
 * This structure contains information on the field strength of a particular tuner and frequency.
 */
typedef struct _FIELDSTRENGTH {
    /**
     * Specifies the maximum value of the field strength.
     */
    unsigned short  MaxStrength;
    /**
     * Specifies the current value of the field strength.
     */
    unsigned short  CurrentStrength;
} FIELDSTRENGTH,*PFIELDSTRENGTH;

/**
 * This structure carries information about the signal at the chosen frequency.
 */
typedef struct _SIGNALINFO { 
    /**
     * Boolean that specifies whether the device is tuned to a valid station. TRUE means that it is a
     * valid station.
     */
    BOOL            fIsStation;         // Suggest it is tuned to a valid station
	/**
	 * Specifies the frequency of the station to which the radio is currently tuned.
	 */
	FREQUENCY		CurrentFreq;		// Current tuned station
    /**
     * FieldStrength level information.
     */
    FIELDSTRENGTH   FieldStrength;      // FieldStrength Level Information
    /**
     * Specifies the multipath level information.
     */
    DWORD           dwMultiPath;        // MultiPath Level Information
    /**
     * Boolean that specifies whether or not the signal is in stereo. TRUE indicates that the signal is
     * in stereo; FALSE indicates that the signal is in mono.
     */
    BOOL            fStereoPresent;     // Stereo Pilot present
    /**
     * Reserved DWORD.
     */
    DWORD           dwReserved;         // reserved DWORD
} SIGNALINFO, *PSIGNALINFO;

typedef BOOL (*SEEK_STATUS_NOTIFY)(PSIGNALINFO);

/**
 * This structure contains information on the frequency range to search.
 */
typedef struct _TUNERSEEKINFO
{
	/**
	 * Unsigned 16-bit integer that contains the settings of the tuner while it is in seek mode. It is
	 * one of the following values:
	 *
	 * - TUNER_SEEK_TUNEDOWN: The tuner seeks down the frequency band by repeatedly reducing the current
	 * frequency by the step size defined for the band.
	 *
	 * - TUNER_SEEK_NO_WRAPAROUND: The tuner does not wrap around to the other end of the frequency band
	 * once the tuner reaches the minimum frequency defined by RangeLow or the maximum frequency defined
	 * by RangeHigh.
	 *
	 * - TUNER_SEEK_NO_MUTE: Turns off muting while the tuner is in seek mode.
	 */
	WORD			wSeekOptions;
	/**
	 * Seeking sensitivity of tuner. It is one of the following values:
	 *
	 * - TUNER_SEEK_SENSITIVITY_NORMAL: Seeks normal sensitivity.
	 *
	 * - TUNER_SEEK_SENSITIVITY_HIGH: Seeks high sensitivity.
	 *
	 * - TUNER_SEEK_SENSITIVITY_LOW: Seeks low sensitivity.
	 */
	WORD			wSensitivity;
    /**
     * Specifies the low end of the frequency range to search.
     */
    FREQUENCY       RangeLow;           // Low end of the freq range to search
    /**
     * Specifies the high end of the frequency range to search.
     */
    FREQUENCY       RangeHigh;          // High end of the freq range to search
	/**
	 * Callback function with the following syntax:
	 *
	 *     BOOL SeekCallbackFunc( PSIGNALINFO pSigInfo)
	 *     {
	 *     ......
	 *     }
	 *
	 * This callback function can update the UI. It returns TRUE if the seek should continue, or FALSE
	 * if the seek should stop.
	 */
	SEEK_STATUS_NOTIFY	fnCallBack;		// call back function
	/**
	 * Reserved.
	 */
	DWORD			Reserved;
}TUNERSEEKINFO, *PTUNERSEEKINFO;

//
// Tuner API functions
//

/**
 * This function gets the version number and number of available tuner devices..
 *
 * @param pdwTunerAPIVer [out] Pointer to a DWORD that contains the version of the tuner API.
 * @param pdwNumDevs [out] Pointer to a DWORD that contains the number of available tuner devices.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * This function must be called before TunerOpen in order to determine what tuners are available.
 * Use TunerGetDevCaps to determine what the capabilities of these tuners are.
 */
BOOL TunerQuery(
    OUT DWORD       *pdwTunerAPIVer,    // version of tuner api
    OUT DWORD       *pdwNumDevs         // number of tuner devices available
);    

/**
 * This function gets the device capabilities of a specified tuner.
 *
 * @param dwTuner [in] Specifies the tuner device identifier. The first tuner has an identifier of
 *   1, the second has an identifier of 2, and so on.
 * @param pTunerDevCaps [out] Pointer to a TUNERDEVCAPS structure that contains information on the
 *   device capabilities.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * Use TunerQuery to determine which tuners are available. Use TunerGetDevCaps to find out what each
 * can do.
 */
BOOL TunerGetDevCaps (
    IN DWORD            dwDeviceID,     // device to be queried
    OUT PTUNERDEVCAPS   pTunerDevCaps   // pointer to TUNERDEVCAPS buffer
);

//
// return Value: the number of band information obtained
//
/**
 * This function returns information in a TUNERBANDINFO structure on the specified bands, such as
 * the type of band, its encoding, its frequency range, and the frequency tuning step between valid
 * stations.
 *
 * @param dwTuner [in] Specifies the tuner device identifier. The first tuner has an identifier of
 *   1, the second has an identifier of 2, and so on.
 * @param dwBands [in] Specifies the bands for which information is desired. Use a bitwise OR to
 *   combine one or more of the following flags: - BAND_AM: Specifies an AM band. - BAND_FM: Specifies
 *   an FM band. - BAND_TV: Specifies a TV band. - BAND_CB: Specifies a CB band. - BAND_USER:
 *   Specifies a user-defined band. - BAND_WEATHER: Specifies a weather band.
 * @param dwBandInfo [out] Specifies a pointer to an array of TUNERBANDINFO structures to be filled
 *   with band information.
 * @param dwBufSize [in] Specifies the size, in bytes, of the buffer pointed to by dwBandInfo. This
 *   should be large enough to hold the information for the number of bands requested.
 * @param pdwActualOutSize [out] Pointer to a DWORD that contains the actual number of bytes written
 *   to the dwBandInfo buffer.
 *
 * @return A positive value, which is the number of bands for which information was returned,
 *   indicates success. Zero (0) indicates failure.
 */
DWORD TunerGetBandInfo(
    IN  DWORD       dwDeviceID,         // tuner device id
    IN  DWORD       dwBands,            // a mask for interested bands
    OUT PTUNERBANDINFO   pBandInfo,     // pointer to a buffer to receive band information
    IN  DWORD       dwBufSize,          // size of the receiving buffer
    OUT DWORD       *pdwActualOutSize   // pointer to actual size of buffer with info
);

/**
 * This function returns a handle to a tuner resource.
 *
 * @param dwTuneridentifier Specifies the tuner identifier. The first tuner has an identifier of 1,
 *   the second has an identifier of 2, and so on.
 *
 * @return A valid tuner handle indicates success. INVALID_HANDLE_VALUE indicates failure.
 *
 * The handle returned by this function is used when calling other tuner functions. When a tuner is
 * opened, the system initializes and configures the device in a default state. To determine this
 * initial configuration, an application calls TunerGetConfig.
 */
HANDLE TunerOpen(
    DWORD           dwTunerId           // specify which tuner to open
);    

/**
 * This function returns the configuration of a tuner.
 *
 * @param hTuner [in] Handle to the current tuner, as returned by TunerOpen.
 * @param pTunerConfig [out] Pointer to a TUNERCONFIG structure that contains the tuner
 *   configuration.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * When a tuner is opened, the system initializes and configures the device in a default state. To
 * determine this initial configuration, an application calls TunerGetConfig, which fills a
 * TUNERCONFIG structure with the default settings. To modify these settings, change the desired
 * members of the TUNERCONFIG structure and then use the modified structure as a parameter in a
 * TunerSetConfig call.
 */
BOOL TunerGetConfig(
    IN HANDLE           hTuner,         // specify tuner
    OUT PTUNERCONFIG    pTunerConfig    // address of tuner config structure
);    

/**
 * This function sets the tuner configuration.
 *
 * @param hTuner [in] Handle to the current tuner, as returned by TunerOpen.
 * @param pTunerConfig [in] Pointer to a TUNERCONFIG structure that contains the tuner
 *   configuration.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
BOOL TunerSetConfig(
    IN HANDLE       hTuner,             // specify which tuner to config
    IN PTUNERCONFIG pTunerConfig        // address of tuner config structure
);    

/**
 * This function retrieves information on the signal of the tuned frequency.
 *
 * @param hTuner [in] Handle to the current tuner, as returned by TunerOpen.
 * @param pSignalInfo [out] Pointer to a SIGNALINFO structure that contains the signal information.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
BOOL TunerGetSignalInfo(
    IN HANDLE       hTuner,             // handle of the tuner device
    OUT PSIGNALINFO pSignalInfo         // address of a tuner signal structure
);

/**
 * This function resets the tuner to the default driver settings.
 *
 * @param hTuner [in] Handle to the current tuner, as returned by TunerOpen.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
BOOL TunerReset(
    IN HANDLE       hTuner              // handle of the tuner device
);

/**
 * This function begins seeking for a frequency with a sufficiently strong signal.
 *
 * @param hTuner [in] Handle to the current tuner, as returned by TunerOpen.
 * @param pTunerSeekInfo [in] Pointer to a TUNERSEEKINFO structure that contains information on the
 *   specified frequency search range and direction.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * The fnCallBack member of the TUNERSEEKINFO structure that you pass to this function identifies a
 * callback function. The device driver calls the callback function to inform the application of the
 * frequency that the seek operation has reached, using SIGNALINFO structure as one of the
 * parameters in the callback function. You can use this information about the frequency to update
 * the user interface (UI). Providing a pointer to this function allows the device driver to call
 * the callback function periodically during the seek operation. The frequency at which the device
 * driver calls the callback function depends on the device driver.
 *
 * The tuner stops the seek operation when the tuner finds a station with a sufficiently strong
 * signal.
 */
BOOL TunerSeekStation(
    IN HANDLE		hTuner,				// handle of the tuner device
	PTUNERSEEKINFO pTunerSeekInfo
);      

/**
 * This function cancels the last seek operation that was initiated by TunerSeekStation.
 *
 * @param hTuner [in] Handle to the current tuner, as returned by TunerOpen.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
BOOL TunerCancelSeek(					// cancels the last seek operation
	IN HANDLE	hTuner
);

/**
 * This function releases a tuner resource.
 *
 * @param hTuner [in] Handle to the current tuner, as returned by TunerOpen.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * Call this function when the tuner is no longer needed.
 */
BOOL TunerClose(
    IN HANDLE       hTuner              // handle of the tuner device
);    

#ifdef __cplusplus
}
#endif
#endif // _TunerAPI_H_
