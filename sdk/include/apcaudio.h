#ifndef _APCAUDIO_H_
#define _APCAUDIO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <apcmsg.h>

// -----------------------------------------------------------------------------
// APC audio API related Callback window messages
//	Audio Manager API window msgs in 0xBEC0 - 0xBEFF range
// -----------------------------------------------------------------------------
/**
 * This message is posted by the system to notify an application that an audio source has been
 * selected. The application must implement a callback function to receive the message.
 *
 * @param wParam Specifies the audio source identifier.
 * @param lParam Set to 0.
 */
#define WM_AUDSRCSELECT                 (APC_AUD_START+0x10)	//	0xBED0
/**
 * This message is posted by the system to notify an application that an audio source has been
 * unselected. The application must implement a callback function to receive the message.
 */
#define WM_AUDSRCUNSELECT               (APC_AUD_START+0x11)	//	0xBED1
/**
 * This message is posted by the system to notify an application that an audio source has been
 * registered. The application must implement a callback function to receive the message.
 *
 * @param wParam Specifies the audio source identifier.
 * @param lParam Set to 0.
 */
#define WM_AUDSRCREGISTER               (APC_AUD_START+0x18)	//	0xBED8
/**
 * This message is posted by the system to notify an application that an audio source has been
 * unregistered. The application must implement a callback function to receive the message.
 *
 * @param wParam Specifies the current audio source identifier.
 * @param lParam Set to 0.
 */
#define WM_AUDSRCUNREGISTER             (APC_AUD_START+0x19)	//	0xBED9

// -----------------------------------------------------------------------------
// AAM Error Handling
// -----------------------------------------------------------------------------
#define WAVERR_BASE             32
#define AAM_ERR_BASE            64
#define AAM_ERR_INVALIDPARAM    (AAM_ERR_BASE+1)
#define AAM_ERR_DEVICEBUSY      (AAM_ERR_BASE+2)
#define AAM_ERR_DEVICEFAIL      (AAM_ERR_BASE+3)
#define AAM_ERR_OUTOFMEMORY     (AAM_ERR_BASE+4)
#define AAM_ERR_ALREADYEXIST    (AAM_ERR_BASE+5)
#define AAM_ERR_NOTFOUND        (AAM_ERR_BASE+6)
#define AAM_ERR_NOTSUPPORTED    (AAM_ERR_BASE+7)
#define AAM_ERR_OUTOFRANGE      (AAM_ERR_BASE+8)

// -----------------------------------------------------------------------------
//	The following are the flags used in dwFlags of the AAM functions
// -----------------------------------------------------------------------------

//	General AAM flags
#define AAM_FLAG_GET                    0x00000000
#define AAM_FLAG_SET                    0x00000800
#define AAM_FLAG_RANGE                  0x00000400
#define AAM_FLAG_DBBASED                0x00000200
#define AAM_FLAG_CUSTOM                 0x00000100

//	Flags used for AAM_VolumeControl
#define AAM_FLAG_VOLUME_MASTER          0x00000001			
#define AAM_FLAG_VOLUME_SOURCE0         0x00000008
#define AAM_FLAG_VOLUME_SOURCE1         0x00000009
#define AAM_FLAG_MUTE_MASTER            0x00000004
#define AAM_FLAG_MUTE_SOURCE0           0x00000002
#define AAM_FLAG_MUTE_SOURCE1           0x00000003
#define AAM_FLAG_BALANCE                0x0000000A
#define AAM_FLAG_FADE                   0x0000000B
#define AAM_FLAG_CENTER                 0x0000000C
#define AAM_FLAG_WOOFER                 0x0000000D

#define AAM_FLAG_VOLUME                 AAM_FLAG_VOLUME_MASTER
#define AAM_FLAG_MUTE                   AAM_FLAG_MUTE_SOURCE0

//	Flags used for AAM_EQBandControl (mutually exclusive)
#define AAM_FLAG_GAIN					0x00000001
#define AAM_FLAG_CENTERFREQ				0x00000002
#define AAM_FLAG_BANDWIDTH				0x00000004

//	Flags used for AAM_FilterControl
#define AAM_FLAG_CROSSOVER_LPF          0x00000010
#define AAM_FLAG_CROSSOVER_HPF          0x00000020
#define AAM_FLAG_CROSSOVER              0x00000030

//	Flag for AAM_AttenuateAudio
#define AAM_FLAG_ATTENUATE_OFF          0x00000010
#define AAM_FLAG_ATTENUATE_ON           0x00000020
#define AAM_FLAG_ATTENUATE_GET          0x00000030
#define AAM_FLAG_ATTENUATE_SET          0x00000040
#define AAM_FLAG_ATTENUATE_RESET        0x00000050

//  Flag for up-sampling smoothing LPF
#define AAM_FLAG_LPF_11KHZ        		0x00000000
#define AAM_FLAG_LPF_5KHZ		        0x00000001

// -----------------------------------------------------------------------------
//	EQ specific flags
// -----------------------------------------------------------------------------
//	mask for getting the EQ Caps
#define AAM_FLAG_PRESET_MASK            0xFFFFF000
#define AAM_FLAG_NUMBAND_MASK           0x000000FF

//	simple EQ preset controls
#define AAM_FLAG_BASS					0x00001000
#define AAM_FLAG_TREBLE		            0x00002000
#define AAM_FLAG_LOUDNESS	            0x00004000
#define AAM_FLAG_MIDRANGE				0x00008000

//	Effects related EQ controls
#define AAM_FLAG_CLASSICAL				0x00010000
#define AAM_FLAG_ROCK					0x00020000
#define AAM_FLAG_POP					0x00040000
#define AAM_FLAG_JAZZ					0x00080000
#define AAM_FLAG_COUNTRY				0x00100000

//	Misc EQ related controls
#define AAM_FLAG_TTS                    0x10000000
#define AAM_FLAG_EQBYPASS               0x20000000
#define AAM_FLAG_DEEMPHASIS             0x40000000


// -----------------------------------------------------------------------------
//	SSD specific flags
// -----------------------------------------------------------------------------
//  SSD features
#define AAM_SSD_MASK                    0xFFFF
#define AAM_SSD_DISABLED                0x0000
#define AAM_SSD_PROLOGIC                0x0001
#define AAM_SSD_DOLBY                   0x0002
#define AAM_SSD_MSV1                    0x0004
#define AAM_SSD_AC3                     0x0008
#define AAM_SSD_THX                     0x0010
#define AAM_SSD_CUSTOM                  0x4000
#define AAM_SSD_DEFAULT                 0xFFFF

//	SSD Control flags
#define AAM_FLAG_SSD_TYPE               0x00000001

// -----------------------------------------------------------------------------
//	AAM_AudioIoControl specific flags
// -----------------------------------------------------------------------------
#define AAM_FLAG_IEQ                    0x00040000
#define AAM_FLAG_IVOLUME                0x00080000
#define AAM_FLAG_ISSD                   0x00100000


// -----------------------------------------------------------------------------
//	Audio source control related definitions
// -----------------------------------------------------------------------------
	
// Source control defines
#define AAM_SRC_NAME_LEN                32
#define AAM_SRC_DEVDRV_LEN              64
#define AAM_SRC_BYID                    0x00000000
#define AAM_SRC_BYINDEX                 0x80000000

#define AAM_FLAG_SELECTED				0x40000000

// Data structures
/**
 * This structure describes the audio source.
 *
 * An application can get the AAM_GetSourceCap of a particular audio source and check the m_dwinfo
 * member of that structure. If AAM_FLAG_SELECTED is set, then that audio source is active.
 */
typedef struct{
    /**
     * Audio source identifier. It is one of the following values:
     *
     * - AAM_SRC_TUNER: Specifies AM/FM tuner 1
     *
     * - AAM_SRC_TUNER2: Specifies AM/FM tuner 2
     *
     * - AAM_SRC_CD: Specifies the compact disc player
     *
     * - AAM_SRC_AUX1: Specifies auxiliary input 1
     *
     * - AAM_SRC_AUX2: Specifies auxiliary input 2
     *
     * - AAM_SRC_CDCHANGER: Specifies the compact disc changer
     *
     * These seven identifiers are predefined, but OEMs can add identifiers.
     */
    DWORD       m_dwID;                         //  audio source ID
    /**
     * Current audio source status or other information
     */
    DWORD       m_dwInfo;	                    //  current audio source/device status and device dependency
    /**
     * Null-terminated string that contains the name of the associated device driver, for example,
     * "DSP1:"
     */
    WCHAR       m_szDevDrv[AAM_SRC_DEVDRV_LEN]; //  device driver, e.g. DSP1: or WDM device driver path
    /**
     * Null-terminated string that contains that audio source name or description
     */
    WCHAR       m_szName[AAM_SRC_NAME_LEN];     //  name or description
    /**
     * Reserved for a future extension
     */
    DWORD       m_dwMisc;                       //  for future extension
	/**
	 * Reserved
	 */
	DWORD       m_dwReserve1;                   //  reserved, 
	/**
	 * Reserved
	 */
	DWORD       m_dwReserve2;                   //  reserved,
}AAM_SRCCAP;

// Audio Source IDs
//	Note: any ID that from 1 to 0xFF is the middle-node device driver
#define AAM_SRC_IDMASK                  0xFFFF

// Audio Source Type
#define AAM_SRC_TUNER_TYPE              0x0100
#define AAM_SRC_CD_TYPE                 0x0200
#define AAM_SRC_AUX_TYPE                0x0400
#define AAM_SRC_PHONE_TYPE              0x0800

// Audio Sources
#define AAM_SRC_NOSOURCE				0x0000
#define AAM_SRC_TUNER                   (AAM_SRC_TUNER_TYPE|1)
#define AAM_SRC_TUNER2                  (AAM_SRC_TUNER_TYPE|2)
#define AAM_SRC_CD                      (AAM_SRC_CD_TYPE|0x01)
#define AAM_SRC_CDCHANGER               (AAM_SRC_CD_TYPE|0x11)
#define AAM_SRC_CDCHANGER2              (AAM_SRC_CD_TYPE|0x12)
#define AAM_SRC_AUX1                    (AAM_SRC_AUX_TYPE|1)
#define AAM_SRC_AUX2                    (AAM_SRC_AUX_TYPE|2)
#define AAM_SRC_PHONE                   (AAM_SRC_PHONE_TYPE|1)

//--------------------------------------------------------------------
//	Audio Manager API functions
//--------------------------------------------------------------------

//	Volume API
/**
 * This function controls volume, balance, and fade.
 *
 * @param dwFlag Specifies a bitmask of flags. It is one of the following values: - AAM_FLAG_VOLUME:
 *   Gets or sets the master volume attenuation (0 specifies maximum gain). - AAM_FLAG_VOLUME_MASTER:
 *   Sets the master volume. - AAM_FLAG_RANGE: Gets the range of values in plValue. This option cannot
 *   be set, only retrieved. - AAM_FLAG_DBBASED: Specifies the use of decibel units rather than
 *   OEM-defined increments. - AAM_FLAG_MUTE: Gets or sets the mute status. This option is used by the
 *   system mute button.TRUE means that mute is on. The mute button mutes only background audio. -
 *   AAM_FLAG_VOLUME_SOURCE0: Indicates volume source 0, which is background music. -
 *   AAM_FLAG_VOLUME_SOURCE1: Indicates volume source 1, which is foreground text-to-speech (TTS) and
 *   event sounds. - AAM_FLAG_BALANCE: Gets or sets the attenuation of the left speakers (positive)
 *   and right (negative) speakers. - AAM_FLAG_FADE: Gets or sets the attenuation of the rear speakers
 *   (positive) and front (negative) speakers. - AAM_FLAG_CENTER: Gets or sets the attenuation level
 *   of the center speaker. - AAM_FLAG_WOOFER: Gets or sets the attenuation level of the subwoofer. To
 *   set a property, use a bitwise OR to combine the chosen flag with AAM_FLAG_SET, and set plValue to
 *   the desired value. To get a property, use a bitwise OR the flag with AAM_FLAG_GET and plValue is
 *   set to the current value.
 * @param plValue Pointer to a long integer.
 *
 * @return Zero indicates success. AAM_ERR_INVALIDPARAM indicates an invalid parameter.
 *   AAM_ERR_DEVICEFAIL indicates failure. AAM_ERR_NOTSUPPORTED indicates that the device does not
 *   support this feature.
 *
 * To get the range of values available, set the AAM_FLAG_RANGE flag. The function returns the
 * maximum and minimum volume attenuation. The high-order word has the maximum attenuation level and
 * the low-order word the maximum gain level. In the case of parameters like balance and fade, the
 * minimum value may be negative. For example, if the high-order word for balance is 0 and the
 * low-order word is 20, it means that the left speaker can be adjusted from 0 to 20, and the right
 * speaker from 0 to -20. Fade works in a similar fashion.
 */
DWORD AAM_VolumeControl(DWORD dwFlag, LONG* pValue);

//	Source Control API
/**
 * This function returns the total number of registered audio sources.
 *
 * @return The number of audio sources indicates success. Zero indicates no audio sources, which is
 *   usually an error.
 *
 * This function is a member of the audio source control API.
 */
DWORD AAM_GetNumSources(void);
/**
 * This function returns the capabilities of a specified audio source.
 *
 * @param dwIndex Specifies the index of the audio source. It is one of the following flags: Flag
 *   Value Description AAM_SRC_BYID 0x00000000 Use the audio source identifier. AAM_SRC_BYINDEX
 *   0x80000000 Specifies the source with an index ranging from 0 to GetNumSources minus 1; in other
 *   words, use the bitwise OR to combine the index with the flag.
 * @param pASC Pointer to an AAM_SRCCAP structure to hold the returned information.
 *
 * @return Zero indicates success. AAM_ERR_INVALIDPARAM indicates an invalid parameter
 *
 * This function is part of the audio source control API.
 *
 * The main use of this function is to get an audio source identifier, which the application uses to
 * select the source. An application can get the AAM_SRCCAP structure of a particular audio source
 * and check the m_dwinfo member of that structure. If AAM_FLAG_SELECTED is set, then that audio
 * source is active.
 */
DWORD AAM_GetSourceCap(DWORD, AAM_SRCCAP*);
/**
 * This function registers a callback thread to receive notification of source selection or
 * deselection.
 *
 * @param idThread Identifier of the callback thread that receives the appropriate message.
 * @param bRegister Boolean that is set to TRUE to register the callback thread, or to FALSE to
 *   deregister it.
 *
 * @return Zero indicates success. AAM_ERR_INVALIDPARAM indicates an invalid parameter
 *
 * This function is a member of the audio source control API.
 *
 * When an audio source is selected or unselected, the system posts either a WM_AUDSRCSELECT or
 * WM_AUDSRCUNSELECT message. When an audio source is registered or unregistered, the system posts
 * either a WM_AUDSRCREGISTER or WM_AUDSRCUNREGISTER message. In both cases, the wParam of the
 * message is set to the audio source identifier.
 */
DWORD AAM_RegisterCallback(DWORD, BOOL);
/**
 * This function selects an audio source to be played.
 *
 * @param dwAudioSourceID Specifies the identifier of the audio source to be played.
 *   AAM_SRC_NOSOURCE is a defined identifier that stops the current audio source.
 *
 * @return Zero indicates success. AAM_ERR_INVALIDPARAM indicates an invalid parameter.
 *
 * This function is a member of the audio source control API.
 *
 * The source identifier can be obtained from AAM_GetSourceCap. When called, AAM_SelectSource stops
 * the audio source that is currently playing, and loads the new source driver.
 *
 * An audio application must call AAM_SelectSource to select a source prior to playing it, even if
 * the application can load the device driver directly.
 */
DWORD AAM_SelectSource(DWORD);

//	SSD API
/**
 * This function tells what type of surround-sound decoding the system supports.
 *
 * @param pdwCap Pointer to a DWORD that contains information about what surround-sound decoding
 *   methods the system supports. The value returned is a combination of one or more of the following
 *   flags: AAM_SSD_AC3 AAM_SSD_DOLBY AAM_SSD_MSV1 AAM_SSD_PROLOGIC AAM_SSD_THX
 *
 * @return Zero indicates success. AAM_ERR_NOTSUPPORTED indicates that the device does not have
 *   surround sound capability.
 */
DWORD AAM_GetSSDCaps(DWORD* pdwCap);
/**
 * This function determines whether or not surround-sound decoding is enabled, and can also be used
 * to set the type of surround-sound decoding.
 *
 * @param dwFlag Specifies information concerning surround-sound decoding. If dwFlag equals
 *   AAM_FLAG_GET | AAM_FLAG_SSD_TYPE, plValue contains the surround-sound decoding type that is
 *   currently set. If dwFlag is set to AAM_FLAG_SET, plValue is a pointer to the type of surround
 *   sound decoding to set. In this case, plValue can contain any of the values returned by
 *   AAM_GetSSDCaps.
 * @param plValue Pointer to a long integer that contains the type of surround-sound decoding
 *   currently set. If plValue equals AAM_SSD_DISABLED, surround sound decoding is disabled.
 *
 * @return Zero indicates success. AAM_ERR_NOTSUPPORTED indicates failure.
 *
 * Use AAM_FLAG_GET or AAM_FLAG_SET combined with AAM_FLAG_SSD_TYPE to get or set the current SSD
 * setting.
 */
DWORD AAM_SSDControl(DWORD dwFlag, LONG* plValue);
/**
 * This function enables or disables surround-sound decoding.
 *
 * @param bEnable Boolean that is set to TRUE to enable surround-sound decoding, or to FALSE to
 *   disable it.
 *
 * @return Zero indicates success. AAM_ERR_DEVICEFAIL indicates that the device does not support
 *   surround-sound decoding.
 *
 * This function is a member of the surround-sound decoding API.
 */
DWORD AAM_EnableSSD(BOOL bEnable);

//	EQ API
/**
 * This function retrieves the capabilities of the equalizer.
 *
 * @param pdwCap Pointer to a DWORD in which the lowest byte holds the number of bands that are
 *   available. The remaining three bytes hold a combination of the following values: -
 *   AAM_FLAG_TREBLE: Support treble control. - AAM_FLAG_BASS: Support bass control. -
 *   AAM_FLAG_LOUDNESS: Support loudness control. - AAM_FLAG_EQBYPASS: Control whether the equalizer
 *   can be bypassed or not.
 *
 * @return Zero indicates success. AAM_ERR_INVALIDPARAM indicates an invalid parameter.
 *
 * This function is a member of the equalization API.
 */
DWORD AAM_GetEQCaps(DWORD* pdwCap);
/**
 * This function adjusts the built-in audio controls.
 *
 * @param dwFlag Specifies a bitmask fo flags. It is one of the following values: - AAM_FLAG_SET: If
 *   set, the function sets the EQ to the desired preset equalization. If not set, this function
 *   retrieves the current EQ settings. - AAM_FLAG_RANGE: To get the range of values that can be set,
 *   combine the selected flag with AAM_FLAG_RANGE. The function returns only a single value in
 *   plValue but the actual value is from -plValue to +plValue. However, a plValue of 1 indicates that
 *   the value of the property is binary and can only be activated (nonzero) and deactivated (0). -
 *   AAM_FLAG_TREBLE: Gets or sets the level of the treble control. - AAM_FLAG_BASS: Gets or sets the
 *   level of the bass control. - AAM_FLAG_LOUDNESS: Gets or sets the level of the loudness control
 *   (usually 0 or 1). - AAM_FLAG_EQBYPASS: Gets or sets the EQ bypass status. When activated, this
 *   bypasses the treble, bass, loudness and any other equalization controls except de-emphasis. -
 *   AAM_FLAG_DEEMPHASIS: Gets or sets the status of the de-emphasis filter. When activated, this
 *   provides compensation for compact discs recorded with pre-emphasis.
 * @param plValue Pointer to a value to get or set, depending on the dwFlag setting.
 *
 * @return Zero indicates success. AAM_ERR_INVALIDPARAM indicates an invalid parameter.
 *   AAM_ERR_DEVICEFAIL indicates failure. AAM_ERR_NOTSUPPORTED indicates that the device does not
 *   support this feature.
 *
 * To set a property combine the selected flag with AAM_FLAG_SET and set plValue to the desired
 * value. To get a property combine the selected flag with AAM_FLAG_GET and plValue will be set to
 * the current value when the call returns.
 */
DWORD AAM_EQPreset(DWORD dwFlag, LONG* plValue);
/**
 * This function controls the gain, center frequency, and bandwidth of each band.
 *
 * @param dwIndex Specifies the index of the band.
 * @param dwFlags Specifies a bitmask for flags. It is one of the following values: -
 *   AAM_FLAG_CENTERFREQ: Get or set the center frequency; in hertz. - AAM_FLAG_BANDWIDTH: Get or set
 *   the bandwidth; in hertz. - AAM_FLAG_GAIN: Get or set the gain in decibels. To set a property, use
 *   a bitwise OR to combine the chosen flag with AAM_FLAG_SET, and set pValue to the desired value.
 *   To get a property, use a bitwise OR to combine the chosen flag with AAM_FLAG_GET and pValue is
 *   set to the current value. To get the range, use a bitwise OR to combine the chosen flag with
 *   AAM_FLAG_RANGE, and pValue is set to the current value.
 * @param plValue Pointer to the value of dwFlags. When you combine the AAM_FLAG_RANGE flag with one
 *   of the flags specified in dwFlags, pValue represents the following: For center frequency or
 *   bandwidth, the high-order word contains the minimum value and the low-order word contains the
 *   maximum value. If these two values are the same, then the value cannot be changed. For gain, the
 *   high-order word has the maximum attenuation level and the low-order word has the maximum gain
 *   level. For example, if the gain can be adjusted from -16 to +16, the high-order word contains -16
 *   and the low-order word contains 16.
 *
 * @return Zero indicates success. AAM_ERR_INVALIDPARAM indicates an invalid parameter.
 *   AAM_ERR_DEVICEFAIL indicates failure. AAM_ERR_NOTSUPPORTED indicates that the device does not
 *   support this feature.
 *
 * This function is a member of the equalization API. The equalizer only supports decibel-based gain
 * units.
 */
DWORD AAM_EQBandControl(DWORD dwIndex, DWORD dwFlag, LONG* plValue);
/**
 * This function allows control of the digital crossover filter parameters.
 *
 * @param dwFlags Specifies a bitmask of flags. It is one of the following values: -
 *   AAM_FLAG_CROSSOVER_LPF: Combine with AAM_FLAG_SET to enable, disable, and set the frequency of
 *   the low-pass filter (LPF). Combine with AAM_FLAG_RANGE to get the range of LPF frequencies that
 *   may be set. - AAM_FLAG_CROSSOVER_HPF: Combine with AAM_FLAG_SET to enable, disable, and set the
 *   frequency of the high-pass filter (HPF). Combine with AAM_FLAG_RANGE to get the range of HPF
 *   frequencies that may be set. - AAM_FLAG_CROSSOVER: Combine with AAM_FLAG_SET to enable, disable,
 *   and set the frequency of crossover frequencies (LPF and HPF). Combine with AAM_FLAG_RANGE to get
 *   the range of crossover frequencies that may be set. This flag is for use in implementations that
 *   do not support separate control of the high-pass and low-pass filter. - AAM_FLAG_GET: When
 *   combined with a filter flag, retrieves the current filter settings. The enabled status of the
 *   filter is returned in plEnable and current frequency is returned in plFreq. - AAM_FLAG_RANGE:
 *   When combined with a filter flag, retrieves the range over which the frequency can be set, and
 *   indicates whether or not the filter can be enabled or disabled. The following table shows the
 *   information returned in the plEnable parameter. Low-order word High-order word Description 0 0 No
 *   such filter available Nonzero 0 Filter is available and can be enabled or disabled. Nonzero
 *   Nonzero Filter is available and is always enabled. The following table shows the information
 *   returned in the plFreq parameter. Low-order word High-order word Description Maximum adjustable
 *   frequency, in hertz. Minimum adjustable frequency, in hertz. Specifies the frequency range. -
 *   AAM__FLAG_SET: When combined with a filter flag, allows you to enable, disable, and set the
 *   frequency of the filter.
 * @param plEnable Pointer to a DWORD used to return or set whether or not the filter is enabled.
 * @param plFreq Pointer to a DWORD used to return or set the frequency.
 *
 * @return Zero indicates success. AAM_ERR_INVALIDPARAM indicates an invalid parameter.
 *   AAM_ERR_NOTSUPPORTED indicates a filter or action is not supported in a particular
 *   implementation. AAM_ERR_OUTOFRANGE indicates a requested frequency value was not in the valid
 *   range of the filter.
 *
 * Do not set both the AAM_FLAG_SET and AAM_FLAG_RANGE flags.
 */
DWORD AAM_FilterControl(DWORD dwFlag, DWORD* plEnable, DWORD* lpFreq);

//	Misc API
/**
 * This function routes the DeviceIoControl function to the appropriate device drivers.
 *
 * @param dwFlag Specifies a bitmask for flags. It is one of the following values: - AAM_FLAG_IEQ:
 *   Calls EQ-related device drivers. - AAM_FLAG_ISSD: Calls surround sound-related device drivers. -
 *   AAM_FLAG_IVOLUME: Calls volume-related device drivers.
 * @param dwIoControlCode Specifies the control code of the operation to perform.
 * @param lpInBuf Long pointer to a buffer that supplies input data to the DeviceIoControl function.
 * @param nInBufSize Size of input buffer.
 * @param lpOutBuf Long pointer to buffer that receives output data from the DeviceIoControl
 *   function.
 * @param nOutBufSize Size of output buffer.
 * @param lpBytesReturned Long pointer to the variable that receives output byte count.
 * @param lpOverLapped Long pointer to an OVERLAPPED structure.
 *
 * @return Zero indicates success. AAM_ERR_DEVICEFAIL indicates that the device failed to respond.
 *   AAM_ERR_NOTSUPPORTED indicates that no device driver is available. If the DeviceIoControl
 *   succeeds (returns non-zero), this function returns 0. If DeviceIoControl fails (returns zero),
 *   this function returns AAM_ERR_DEVICEFAIL. This function returns a flag. Based on the dwFlag
 *   value, this function routes the DeviceIoControl function to the appropriate device.
 */
DWORD AAM_AudioIoControl(DWORD dwFlag, DWORD dwIoControlCode, LPVOID lpInBuf, DWORD nInBufSize, LPVOID lpOutBuf, DWORD nOutBufSize, LPDWORD lpBytesReturned, LPOVERLAPPED lpOverlapped);

#ifdef __cplusplus
}
#endif

#endif
