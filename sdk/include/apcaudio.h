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
#define WM_AUDSRCSELECT                 (APC_AUD_START+0x10)	//	0xBED0
#define WM_AUDSRCUNSELECT               (APC_AUD_START+0x11)	//	0xBED1
#define WM_AUDSRCREGISTER               (APC_AUD_START+0x18)	//	0xBED8
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
typedef struct{
    DWORD       m_dwID;                         //  audio source ID
    DWORD       m_dwInfo;	                    //  current audio source/device status and device dependency
    WCHAR       m_szDevDrv[AAM_SRC_DEVDRV_LEN]; //  device driver, e.g. DSP1: or WDM device driver path
    WCHAR       m_szName[AAM_SRC_NAME_LEN];     //  name or description
    DWORD       m_dwMisc;                       //  for future extension
	DWORD       m_dwReserve1;                   //  reserved, 
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
DWORD AAM_VolumeControl(DWORD dwFlag, LONG* pValue);

//	Source Control API
DWORD AAM_GetNumSources(void);
DWORD AAM_GetSourceCap(DWORD, AAM_SRCCAP*);
DWORD AAM_RegisterCallback(DWORD, BOOL);
DWORD AAM_SelectSource(DWORD);

//	SSD API
DWORD AAM_GetSSDCaps(DWORD* pdwCap);
DWORD AAM_SSDControl(DWORD dwFlag, LONG* plValue);
DWORD AAM_EnableSSD(BOOL bEnable);

//	EQ API
DWORD AAM_GetEQCaps(DWORD* pdwCap);
DWORD AAM_EQPreset(DWORD dwFlag, LONG* plValue);
DWORD AAM_EQBandControl(DWORD dwIndex, DWORD dwFlag, LONG* plValue);
DWORD AAM_FilterControl(DWORD dwFlag, DWORD* plEnable, DWORD* lpFreq);

//	Misc API
DWORD AAM_AudioIoControl(DWORD dwFlag, DWORD dwIoControlCode, LPVOID lpInBuf, DWORD nInBufSize, LPVOID lpOutBuf, DWORD nOutBufSize, LPDWORD lpBytesReturned, LPOVERLAPPED lpOverlapped);

#ifdef __cplusplus
}
#endif

#endif
