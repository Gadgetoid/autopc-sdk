/*++

Copyright (c) 1995  Microsoft Corporation

Module Name:mmsystem.h -- Include file for Multimedia API's  

 *    If defined, the following flags inhibit inclusion
 *    of the indicated items:
 *
 *      MMNOSOUND       Sound support
 *      MMNOWAVE        Waveform support
 *
 */

#ifndef _INC_MMSYSTEM
#define _INC_MMSYSTEM   // to prevent multiple inclusion of mmsystem.h

#include "pshpack1.h"   // Assume byte packing throughout

#ifdef __cplusplus
extern "C" {            // Assume C declarations for C++
#endif  // __cplusplus

/****************************************************************************

                    General constants and data types

****************************************************************************/

/* general constants */
#define MAXPNAMELEN      32     // max product name length (including NULL)
#define MAXERRORLENGTH   128    // max error text length (including final NULL)

/*
 *  Microsoft Manufacturer and Product ID's
 *
    Used with wMid and wPid fields in WAVEOUTCAPS, WAVEINCAPS,
    MIDIOUTCAPS, MIDIINCAPS, AUXCAPS, JOYCAPS structures.
 */
/*
 *  (these have been moved to
 *  MMREG.H for Windows 4.00 and above).
 */
/* manufacturer IDs */
#ifndef MM_MICROSOFT
#define MM_MICROSOFT            1        // Microsoft Corporation
#endif // MM_MICROSOFT



/* general data types */
typedef UINT    MMVERSION;      // major (high byte), minor (low byte)

typedef UINT    MMRESULT;       // error return code, 0 means no error
                                // call as if(err=xxxx(...)) Error(err); else

#define _MMRESULT_              // ??? Not needed for NT, but probably harmless.

typedef UINT       *LPUINT;


/* MMTIME data structure */
/**
 * This structure contains timing information for different types of multimedia data.
 */
typedef struct mmtime_tag
{
    /**
     * Time format. It is one of the following values: Value Description TIME_BYTES Current byte offset
     * from beginning of the file. TIME_MIDI MIDI time. TIME_MS Time in milliseconds. TIME_SAMPLES
     * Number of waveform-audio samples. TIME_SMPTE SMPTE (Society of Motion Picture and Television
     * Engineers) time. TIME_TICKS Ticks within a MIDI stream.
     */
    UINT            wType;      /* indicates the contents of the union */
    union
    {
    /**
     * Number of milliseconds. Used when wType is TIME_MS.
     */
    DWORD       ms;         /* milliseconds */
    /**
     * Number of samples. Used when wType is TIME_SAMPLES.
     */
    DWORD       sample;     /* samples */
    /**
     * Byte count. Used when wType is TIME_BYTES.
     */
    DWORD       cb;         /* byte count */
    /**
     * Ticks in MIDI stream. Used when wType is TIME_TICKS.
     */
    DWORD       ticks;      /* ticks in MIDI stream */

    /* SMPTE */
    struct
    {
        /**
         * Hours.
         */
        BYTE    hour;       /* hours */
        /**
         * Minutes.
         */
        BYTE    min;        /* minutes */
        /**
         * Seconds.
         */
        BYTE    sec;        /* seconds */
        /**
         * Frames.
         */
        BYTE    frame;      /* frames  */
        /**
         * Frames per second-24, 25, 29 (30 drop), or 30.
         */
        BYTE    fps;        /* frames per second */
        /**
         * Dummy byte for alignment.
         */
        BYTE    dummy;      /* pad */
#ifdef _WIN32
        /**
         * Padding.
         */
        BYTE    pad[2];
#endif
    /**
     * SMPTE time structure. Used when wType is TIME_SMPTE.
     */
    } smpte;

    /* MIDI */
    struct
    {
        /**
         * Song pointer position.
         */
        DWORD songptrpos;   /* song pointer position */
    /**
     * MIDI time structure. Used when wType is TIME_MIDI.
     */
    } midi;
    } u;
} MMTIME, *PMMTIME, NEAR *NPMMTIME, FAR *LPMMTIME;

/* types for wType field in MMTIME struct */
#define TIME_MS         0x0001  /* time in milliseconds */
#define TIME_SAMPLES    0x0002  /* number of wave samples */
#define TIME_BYTES      0x0004  /* current byte offset */
#define TIME_SMPTE      0x0008  /* SMPTE time */
#define TIME_MIDI       0x0010  /* MIDI time */
#define TIME_TICKS      0x0020  /* Ticks within MIDI stream */

#define MAKEFOURCC(ch0, ch1, ch2, ch3)                              \
        ((DWORD)(BYTE)(ch0) | ((DWORD)(BYTE)(ch1) << 8) |   \
        ((DWORD)(BYTE)(ch2) << 16) | ((DWORD)(BYTE)(ch3) << 24 ))

#define mmioFOURCC(ch0, ch1, ch2, ch3)  MAKEFOURCC(ch0, ch1, ch2, ch3)

/****************************************************************************

            Multimedia Extensions Window Messages

****************************************************************************/

#define MM_WOM_OPEN         0x3BB           /* waveform output */
#define MM_WOM_CLOSE        0x3BC
#define MM_WOM_DONE         0x3BD

#define MM_WIM_OPEN         0x3BE           /* waveform input */
#define MM_WIM_CLOSE        0x3BF
#define MM_WIM_DATA         0x3C0


/* these are used by msacm.h */
#define MM_STREAM_OPEN      0x3D4
#define MM_STREAM_CLOSE     0x3D5
#define MM_STREAM_DONE      0x3D6
#define MM_STREAM_ERROR     0x3D7


/****************************************************************************

        String resource number bases (internal use)

****************************************************************************/

#define MMSYSERR_BASE          0
#define WAVERR_BASE            32

/****************************************************************************

            General error return values

****************************************************************************/

/* general error return values */
#define MMSYSERR_NOERROR      0                    /* no error */
#define MMSYSERR_ERROR        (MMSYSERR_BASE + 1)  /* unspecified error */
#define MMSYSERR_BADDEVICEID  (MMSYSERR_BASE + 2)  /* device ID out of range */
#define MMSYSERR_NOTENABLED   (MMSYSERR_BASE + 3)  /* driver failed enable */
#define MMSYSERR_ALLOCATED    (MMSYSERR_BASE + 4)  /* device already allocated */
#define MMSYSERR_INVALHANDLE  (MMSYSERR_BASE + 5)  /* device handle is invalid */
#define MMSYSERR_NODRIVER     (MMSYSERR_BASE + 6)  /* no device driver present */
#define MMSYSERR_NOMEM        (MMSYSERR_BASE + 7)  /* memory allocation error */
#define MMSYSERR_NOTSUPPORTED (MMSYSERR_BASE + 8)  /* function isn't supported */
#define MMSYSERR_BADERRNUM    (MMSYSERR_BASE + 9)  /* error value out of range */
#define MMSYSERR_INVALFLAG    (MMSYSERR_BASE + 10) /* invalid flag passed */
#define MMSYSERR_INVALPARAM   (MMSYSERR_BASE + 11) /* invalid parameter passed */
#define MMSYSERR_HANDLEBUSY   (MMSYSERR_BASE + 12) /* handle being used */
                                                   /* simultaneously on another */
                                                   /* thread (eg callback) */
#define MMSYSERR_INVALIDALIAS (MMSYSERR_BASE + 13) /* specified alias not found */
#define MMSYSERR_BADDB        (MMSYSERR_BASE + 14) /* bad registry database */
#define MMSYSERR_KEYNOTFOUND  (MMSYSERR_BASE + 15) /* registry key not found */
#define MMSYSERR_READERROR    (MMSYSERR_BASE + 16) /* registry read error */
#define MMSYSERR_WRITEERROR   (MMSYSERR_BASE + 17) /* registry write error */
#define MMSYSERR_DELETEERROR  (MMSYSERR_BASE + 18) /* registry delete error */
#define MMSYSERR_VALNOTFOUND  (MMSYSERR_BASE + 19) /* registry value not found */
#define MMSYSERR_NODRIVERCB   (MMSYSERR_BASE + 20) /* driver does not call DriverCallback */
#define MMSYSERR_LASTERROR    (MMSYSERR_BASE + 20) /* last error in range */


/****************************************************************************

              Driver callback support

****************************************************************************/

/* flags used with waveOutOpen(), waveInOpen(), midiInOpen(), and */
/* midiOutOpen() to specify the type of the dwCallback parameter. */

#define CALLBACK_TYPEMASK   0x00070000l    /* callback type mask */
#define CALLBACK_NULL       0x00000000l    /* no callback */
#define CALLBACK_WINDOW     0x00010000l    /* dwCallback is a HWND */
#define CALLBACK_TASK       0x00020000l    /* dwCallback is a HTASK */
#define CALLBACK_FUNCTION   0x00030000l    /* dwCallback is a FARPROC */
#define CALLBACK_THREAD     (CALLBACK_TASK)/* thread ID replaces 16 bit task */
#define CALLBACK_EVENT      0x00050000l    /* dwCallback is an EVENT Handle */


typedef void (CALLBACK DRVCALLBACK)(HANDLE hdrvr, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);

typedef DRVCALLBACK FAR *LPDRVCALLBACK;
typedef DRVCALLBACK     *PDRVCALLBACK;


#ifndef MMNOSOUND

/**
 * This function plays a waveform sound.
 *
 * @param lpszSound Long pointer to a null-terminated string that specifies the sound to play. This
 *   parameter can be either an entry in the registry or in WIN.INI that identifies a system sound, or
 *   it can be the name of a waveform-audio file. (If the function does not find the entry, the
 *   parameter is treated as a filename.) If this parameter is NULL, any currently playing sound is
 *   stopped.
 * @param fuSound Flags for playing the sound. The following values are defined: Value Description
 *   SND_ASYNC The sound is played asynchronously and the function returns immediately after beginning
 *   the sound. To terminate an asynchronously played sound, call sndPlaySound with lpszSoundName set
 *   to NULL. SND_LOOP The sound plays repeatedly until sndPlaySound is called again with the
 *   lpszSoundName parameter set to NULL. You must also specify the SND_ASYNC flag to loop sounds.
 *   SND_MEMORY The parameter specified by lpszSoundName points to an image of a waveform sound in
 *   memory. SND_NODEFAULT If the sound cannot be found, the function returns silently without playing
 *   the default sound. SND_NOSTOP If a sound is currently playing, the function immediately returns
 *   FALSE, without playing the requested sound. SND_SYNC The sound is played synchronously and the
 *   function does not return until the sound ends.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * If the specified sound cannot be found, sndPlaySound plays the system default sound. If there is
 * no system default entry in the registry or WIN.INI file, or if the default sound cannot be found,
 * the function makes no sound and returns FALSE.
 *
 * The specified sound must fit in available physical memory and be playable by an installed
 * waveform-audio device driver. If sndPlaySound does not find the sound in the current directory,
 * the function searches for it using the standard directory-search order.
 */
BOOL APIENTRY sndPlaySoundW( LPCWSTR lpszSoundName, UINT fuSound );
#ifdef UNICODE
/**
 * This function plays a waveform sound.
 *
 * @param lpszSound Long pointer to a null-terminated string that specifies the sound to play. This
 *   parameter can be either an entry in the registry or in WIN.INI that identifies a system sound, or
 *   it can be the name of a waveform-audio file. (If the function does not find the entry, the
 *   parameter is treated as a filename.) If this parameter is NULL, any currently playing sound is
 *   stopped.
 * @param fuSound Flags for playing the sound. The following values are defined: Value Description
 *   SND_ASYNC The sound is played asynchronously and the function returns immediately after beginning
 *   the sound. To terminate an asynchronously played sound, call sndPlaySound with lpszSoundName set
 *   to NULL. SND_LOOP The sound plays repeatedly until sndPlaySound is called again with the
 *   lpszSoundName parameter set to NULL. You must also specify the SND_ASYNC flag to loop sounds.
 *   SND_MEMORY The parameter specified by lpszSoundName points to an image of a waveform sound in
 *   memory. SND_NODEFAULT If the sound cannot be found, the function returns silently without playing
 *   the default sound. SND_NOSTOP If a sound is currently playing, the function immediately returns
 *   FALSE, without playing the requested sound. SND_SYNC The sound is played synchronously and the
 *   function does not return until the sound ends.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * If the specified sound cannot be found, sndPlaySound plays the system default sound. If there is
 * no system default entry in the registry or WIN.INI file, or if the default sound cannot be found,
 * the function makes no sound and returns FALSE.
 *
 * The specified sound must fit in available physical memory and be playable by an installed
 * waveform-audio device driver. If sndPlaySound does not find the sound in the current directory,
 * the function searches for it using the standard directory-search order.
 */
#define sndPlaySound  sndPlaySoundW
#else
/**
 * This function plays a waveform sound.
 *
 * @param lpszSound Long pointer to a null-terminated string that specifies the sound to play. This
 *   parameter can be either an entry in the registry or in WIN.INI that identifies a system sound, or
 *   it can be the name of a waveform-audio file. (If the function does not find the entry, the
 *   parameter is treated as a filename.) If this parameter is NULL, any currently playing sound is
 *   stopped.
 * @param fuSound Flags for playing the sound. The following values are defined: Value Description
 *   SND_ASYNC The sound is played asynchronously and the function returns immediately after beginning
 *   the sound. To terminate an asynchronously played sound, call sndPlaySound with lpszSoundName set
 *   to NULL. SND_LOOP The sound plays repeatedly until sndPlaySound is called again with the
 *   lpszSoundName parameter set to NULL. You must also specify the SND_ASYNC flag to loop sounds.
 *   SND_MEMORY The parameter specified by lpszSoundName points to an image of a waveform sound in
 *   memory. SND_NODEFAULT If the sound cannot be found, the function returns silently without playing
 *   the default sound. SND_NOSTOP If a sound is currently playing, the function immediately returns
 *   FALSE, without playing the requested sound. SND_SYNC The sound is played synchronously and the
 *   function does not return until the sound ends.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * If the specified sound cannot be found, sndPlaySound plays the system default sound. If there is
 * no system default entry in the registry or WIN.INI file, or if the default sound cannot be found,
 * the function makes no sound and returns FALSE.
 *
 * The specified sound must fit in available physical memory and be playable by an installed
 * waveform-audio device driver. If sndPlaySound does not find the sound in the current directory,
 * the function searches for it using the standard directory-search order.
 */
#define sndPlaySound  sndPlaySoundA
#endif // !UNICODE

/**
 * The PlaySound function plays a sound specified by the specified file name, resource, or system
 * event.
 *
 * @param pszSound Pointer to a null-terminated string that specifies the sound to play. If this
 *   parameter is NULL, any currently playing waveform sound is stopped. To stop a non-waveform sound,
 *   specify SND_PURGE in the fdwSound parameter. Three flags in fdwSound (SND_ALIAS, SND_FILENAME,
 *   and SND_RESOURCE) determine whether the name is interpreted as an alias for a system event, a
 *   filename, or a resource identifier. If none of these flags are specified, PlaySound searches the
 *   registry or the WIN.INI file for an association with the specified sound name. If an association
 *   is found, the sound event is played. If no association is found in the registry, the name is
 *   interpreted as a filename.
 * @param hmod Handle to the executable file that contains the resource to be loaded. This parameter
 *   must be NULL unless SND_RESOURCE is specified in fdwSound.
 * @param fdwSound Flags for playing the sound. The following values are defined: Value Description
 *   SND_APPLICATION The sound is played using an application-specific association. SND_ALIAS The
 *   pszSound parameter is a system-event alias in the registry or the WIN.INI file. Do not use with
 *   either SND_FILENAME or SND_RESOURCE. SND_ASYNC The sound is played asynchronously and PlaySound
 *   returns immediately after beginning the sound. To terminate an asynchronously played waveform
 *   sound, call PlaySound with pszSound set to NULL. SND_FILENAME The pszSound parameter is a
 *   filename. SND_LOOP The sound plays repeatedly until PlaySound is called again with the pszSound
 *   parameter set to NULL. You must also specify the SND_ASYNC flag to indicate an asynchronous sound
 *   event. SND_MEMORY A sound event's file is loaded in RAM. The parameter specified by pszSound must
 *   point to an image of a sound in memory. SND_NODEFAULT No default sound event is used. If the
 *   sound cannot be found, PlaySound returns silently without playing the default sound. SND_NOSTOP
 *   The specified sound event will yield to another sound event that is already playing. If a sound
 *   cannot be played because the resource needed to generate that sound is busy playing another
 *   sound, the function immediately returns FALSE without playing the requested sound. If this flag
 *   is not specified, PlaySound attempts to stop the currently playing sound so that the device can
 *   be used to play the new sound. SND_NOWAIT If the driver is busy, return immediately without
 *   playing the sound. SND_RESOURCE The pszSound parameter is a resource identifier; hmod must
 *   identify the instance that contains the resource. SND_SYNC Synchronous playback of a sound event.
 *   PlaySound returns after the sound event completes.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * The sound specified by pszSound must fit into available physical memory and be playable by an
 * installed waveform-audio device driver. PlaySound searches the following directories for sound
 * files: the current directory; the Windows CE directory; the Windows CE system directory;
 * directories listed in the PATH environment variable; and the list of directories mapped in a
 * network. For more information about the directory search order, see the documentation for the
 * OpenFile function.
 *
 * If it cannot find the specified sound, PlaySound uses the default system event sound entry
 * instead. If the function can find neither the system default entry nor the default sound, it
 * makes no sound and returns FALSE.
 */
BOOL WINAPI PlaySoundA( LPCSTR pszSound, HMODULE hmod, DWORD fdwSound);
/**
 * The PlaySound function plays a sound specified by the specified file name, resource, or system
 * event.
 *
 * @param pszSound Pointer to a null-terminated string that specifies the sound to play. If this
 *   parameter is NULL, any currently playing waveform sound is stopped. To stop a non-waveform sound,
 *   specify SND_PURGE in the fdwSound parameter. Three flags in fdwSound (SND_ALIAS, SND_FILENAME,
 *   and SND_RESOURCE) determine whether the name is interpreted as an alias for a system event, a
 *   filename, or a resource identifier. If none of these flags are specified, PlaySound searches the
 *   registry or the WIN.INI file for an association with the specified sound name. If an association
 *   is found, the sound event is played. If no association is found in the registry, the name is
 *   interpreted as a filename.
 * @param hmod Handle to the executable file that contains the resource to be loaded. This parameter
 *   must be NULL unless SND_RESOURCE is specified in fdwSound.
 * @param fdwSound Flags for playing the sound. The following values are defined: Value Description
 *   SND_APPLICATION The sound is played using an application-specific association. SND_ALIAS The
 *   pszSound parameter is a system-event alias in the registry or the WIN.INI file. Do not use with
 *   either SND_FILENAME or SND_RESOURCE. SND_ASYNC The sound is played asynchronously and PlaySound
 *   returns immediately after beginning the sound. To terminate an asynchronously played waveform
 *   sound, call PlaySound with pszSound set to NULL. SND_FILENAME The pszSound parameter is a
 *   filename. SND_LOOP The sound plays repeatedly until PlaySound is called again with the pszSound
 *   parameter set to NULL. You must also specify the SND_ASYNC flag to indicate an asynchronous sound
 *   event. SND_MEMORY A sound event's file is loaded in RAM. The parameter specified by pszSound must
 *   point to an image of a sound in memory. SND_NODEFAULT No default sound event is used. If the
 *   sound cannot be found, PlaySound returns silently without playing the default sound. SND_NOSTOP
 *   The specified sound event will yield to another sound event that is already playing. If a sound
 *   cannot be played because the resource needed to generate that sound is busy playing another
 *   sound, the function immediately returns FALSE without playing the requested sound. If this flag
 *   is not specified, PlaySound attempts to stop the currently playing sound so that the device can
 *   be used to play the new sound. SND_NOWAIT If the driver is busy, return immediately without
 *   playing the sound. SND_RESOURCE The pszSound parameter is a resource identifier; hmod must
 *   identify the instance that contains the resource. SND_SYNC Synchronous playback of a sound event.
 *   PlaySound returns after the sound event completes.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * The sound specified by pszSound must fit into available physical memory and be playable by an
 * installed waveform-audio device driver. PlaySound searches the following directories for sound
 * files: the current directory; the Windows CE directory; the Windows CE system directory;
 * directories listed in the PATH environment variable; and the list of directories mapped in a
 * network. For more information about the directory search order, see the documentation for the
 * OpenFile function.
 *
 * If it cannot find the specified sound, PlaySound uses the default system event sound entry
 * instead. If the function can find neither the system default entry nor the default sound, it
 * makes no sound and returns FALSE.
 */
BOOL WINAPI PlaySoundW(LPCWSTR pszSound, HMODULE hmod, DWORD fdwSound);
#ifdef UNICODE
/**
 * The PlaySound function plays a sound specified by the specified file name, resource, or system
 * event.
 *
 * @param pszSound Pointer to a null-terminated string that specifies the sound to play. If this
 *   parameter is NULL, any currently playing waveform sound is stopped. To stop a non-waveform sound,
 *   specify SND_PURGE in the fdwSound parameter. Three flags in fdwSound (SND_ALIAS, SND_FILENAME,
 *   and SND_RESOURCE) determine whether the name is interpreted as an alias for a system event, a
 *   filename, or a resource identifier. If none of these flags are specified, PlaySound searches the
 *   registry or the WIN.INI file for an association with the specified sound name. If an association
 *   is found, the sound event is played. If no association is found in the registry, the name is
 *   interpreted as a filename.
 * @param hmod Handle to the executable file that contains the resource to be loaded. This parameter
 *   must be NULL unless SND_RESOURCE is specified in fdwSound.
 * @param fdwSound Flags for playing the sound. The following values are defined: Value Description
 *   SND_APPLICATION The sound is played using an application-specific association. SND_ALIAS The
 *   pszSound parameter is a system-event alias in the registry or the WIN.INI file. Do not use with
 *   either SND_FILENAME or SND_RESOURCE. SND_ASYNC The sound is played asynchronously and PlaySound
 *   returns immediately after beginning the sound. To terminate an asynchronously played waveform
 *   sound, call PlaySound with pszSound set to NULL. SND_FILENAME The pszSound parameter is a
 *   filename. SND_LOOP The sound plays repeatedly until PlaySound is called again with the pszSound
 *   parameter set to NULL. You must also specify the SND_ASYNC flag to indicate an asynchronous sound
 *   event. SND_MEMORY A sound event's file is loaded in RAM. The parameter specified by pszSound must
 *   point to an image of a sound in memory. SND_NODEFAULT No default sound event is used. If the
 *   sound cannot be found, PlaySound returns silently without playing the default sound. SND_NOSTOP
 *   The specified sound event will yield to another sound event that is already playing. If a sound
 *   cannot be played because the resource needed to generate that sound is busy playing another
 *   sound, the function immediately returns FALSE without playing the requested sound. If this flag
 *   is not specified, PlaySound attempts to stop the currently playing sound so that the device can
 *   be used to play the new sound. SND_NOWAIT If the driver is busy, return immediately without
 *   playing the sound. SND_RESOURCE The pszSound parameter is a resource identifier; hmod must
 *   identify the instance that contains the resource. SND_SYNC Synchronous playback of a sound event.
 *   PlaySound returns after the sound event completes.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * The sound specified by pszSound must fit into available physical memory and be playable by an
 * installed waveform-audio device driver. PlaySound searches the following directories for sound
 * files: the current directory; the Windows CE directory; the Windows CE system directory;
 * directories listed in the PATH environment variable; and the list of directories mapped in a
 * network. For more information about the directory search order, see the documentation for the
 * OpenFile function.
 *
 * If it cannot find the specified sound, PlaySound uses the default system event sound entry
 * instead. If the function can find neither the system default entry nor the default sound, it
 * makes no sound and returns FALSE.
 */
#define PlaySound  PlaySoundW
#else
/**
 * The PlaySound function plays a sound specified by the specified file name, resource, or system
 * event.
 *
 * @param pszSound Pointer to a null-terminated string that specifies the sound to play. If this
 *   parameter is NULL, any currently playing waveform sound is stopped. To stop a non-waveform sound,
 *   specify SND_PURGE in the fdwSound parameter. Three flags in fdwSound (SND_ALIAS, SND_FILENAME,
 *   and SND_RESOURCE) determine whether the name is interpreted as an alias for a system event, a
 *   filename, or a resource identifier. If none of these flags are specified, PlaySound searches the
 *   registry or the WIN.INI file for an association with the specified sound name. If an association
 *   is found, the sound event is played. If no association is found in the registry, the name is
 *   interpreted as a filename.
 * @param hmod Handle to the executable file that contains the resource to be loaded. This parameter
 *   must be NULL unless SND_RESOURCE is specified in fdwSound.
 * @param fdwSound Flags for playing the sound. The following values are defined: Value Description
 *   SND_APPLICATION The sound is played using an application-specific association. SND_ALIAS The
 *   pszSound parameter is a system-event alias in the registry or the WIN.INI file. Do not use with
 *   either SND_FILENAME or SND_RESOURCE. SND_ASYNC The sound is played asynchronously and PlaySound
 *   returns immediately after beginning the sound. To terminate an asynchronously played waveform
 *   sound, call PlaySound with pszSound set to NULL. SND_FILENAME The pszSound parameter is a
 *   filename. SND_LOOP The sound plays repeatedly until PlaySound is called again with the pszSound
 *   parameter set to NULL. You must also specify the SND_ASYNC flag to indicate an asynchronous sound
 *   event. SND_MEMORY A sound event's file is loaded in RAM. The parameter specified by pszSound must
 *   point to an image of a sound in memory. SND_NODEFAULT No default sound event is used. If the
 *   sound cannot be found, PlaySound returns silently without playing the default sound. SND_NOSTOP
 *   The specified sound event will yield to another sound event that is already playing. If a sound
 *   cannot be played because the resource needed to generate that sound is busy playing another
 *   sound, the function immediately returns FALSE without playing the requested sound. If this flag
 *   is not specified, PlaySound attempts to stop the currently playing sound so that the device can
 *   be used to play the new sound. SND_NOWAIT If the driver is busy, return immediately without
 *   playing the sound. SND_RESOURCE The pszSound parameter is a resource identifier; hmod must
 *   identify the instance that contains the resource. SND_SYNC Synchronous playback of a sound event.
 *   PlaySound returns after the sound event completes.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * The sound specified by pszSound must fit into available physical memory and be playable by an
 * installed waveform-audio device driver. PlaySound searches the following directories for sound
 * files: the current directory; the Windows CE directory; the Windows CE system directory;
 * directories listed in the PATH environment variable; and the list of directories mapped in a
 * network. For more information about the directory search order, see the documentation for the
 * OpenFile function.
 *
 * If it cannot find the specified sound, PlaySound uses the default system event sound entry
 * instead. If the function can find neither the system default entry nor the default sound, it
 * makes no sound and returns FALSE.
 */
#define PlaySound  PlaySoundA
#endif // !UNICODE



/*
 *  flag values for fuSound arguments on [snd]PlaySound
 *  or dwFlags for PlaySound
 */

/* sndAlias creates the alias identifier */
#define sndAlias( ch0, ch1 ) \
                ( SND_ALIAS_START + (DWORD)(BYTE)(ch0) | ( (DWORD)(BYTE)(ch1) << 8 ))

#define SND_ALIAS_SYSTEMASTERISK        sndAlias('S', '*')
#define SND_ALIAS_SYSTEMQUESTION        sndAlias('S', '?')
#define SND_ALIAS_SYSTEMHAND            sndAlias('S', 'H')
#define SND_ALIAS_SYSTEMEXIT            sndAlias('S', 'E')
#define SND_ALIAS_SYSTEMSTART           sndAlias('S', 'S')
#define SND_ALIAS_SYSTEMWELCOME         sndAlias('S', 'W')
#define SND_ALIAS_SYSTEMEXCLAMATION     sndAlias('S', '!')
#define SND_ALIAS_SYSTEMDEFAULT         sndAlias('S', 'D')

#define SND_ALIAS      0x00010000   // name is a WIN.INI [sounds] entry
#define SND_FILENAME   0x00020000   // name is a file name
#define SND_RESOURCE   0x00040004   // name is a resource name or atom

#define SND_SYNC       0x00000000   // play synchronously (default)
#define SND_ASYNC      0x00000001   // play asynchronously
#define SND_NODEFAULT  0x00000002   // silence not default, if sound not found
#define SND_MEMORY     0x00000004   // lpszSoundName points to a memory file
#define SND_LOOP       0x00000008   // loop the sound until next sndPlaySound
#define SND_NOSTOP     0x00000010   // don't stop any currently playing sound

#define SND_NOWAIT     0x00002000   // don't wait if the driver is busy
#define SND_VALIDFLAGS 0x0017201F   // Set of valid flag bits.  Anything outside
                                    // this range will raise an error
#define SND_RESERVED   0xFF000000   // In particular these flags are reserved
#define SND_TYPE_MASK  0x00170007
#define SND_ALIAS_ID   0x00110000   // name is a WIN.INI [sounds] entry identifier
#define SND_ALIAS_START  0      // ??? must be > 4096 to keep strings in same section of resource file






typedef HANDLE HDRVR;
typedef HANDLE          HMMIO;          // a handle to an open file


#endif  // ifndef MMNOSOUND

#ifndef MMNOWAVE
/****************************************************************************

                        Waveform audio support

****************************************************************************/

/* waveform audio error return values */
#define WAVERR_BADFORMAT      (WAVERR_BASE + 0)    // unsupported wave format
#define WAVERR_STILLPLAYING   (WAVERR_BASE + 1)    // still something playing
#define WAVERR_UNPREPARED     (WAVERR_BASE + 2)    // header not prepared
#define WAVERR_SYNC           (WAVERR_BASE + 3)    // device is synchronous
#define WAVERR_LASTERROR      (WAVERR_BASE + 3)    // last error in range

/* waveform audio data types */
DECLARE_HANDLE(HWAVE);
DECLARE_HANDLE(HWAVEIN);
DECLARE_HANDLE(HWAVEOUT);

typedef HWAVEIN FAR *LPHWAVEIN;
typedef HWAVEOUT FAR *LPHWAVEOUT;
typedef DRVCALLBACK WAVECALLBACK;
typedef WAVECALLBACK FAR *LPWAVECALLBACK;

/* wave callback messages */
#define WOM_OPEN        MM_WOM_OPEN
#define WOM_CLOSE       MM_WOM_CLOSE
#define WOM_DONE        MM_WOM_DONE
#define WIM_OPEN        MM_WIM_OPEN
#define WIM_CLOSE       MM_WIM_CLOSE
#define WIM_DATA        MM_WIM_DATA

/* device ID for wave device mapper */
/* device ID for wave device mapper */
#define WAVE_MAPPER     ((DWORD)(-1))

/* flags for dwFlags parameter in waveOutOpen() and waveInOpen() */
#define  WAVE_FORMAT_QUERY     0x00000001
#define  WAVE_ALLOWSYNC        0x00000002
#define  WAVE_MAPPED           0x00000004
#define  WAVE_FORMAT_DIRECT    0x00000008
#define  WAVE_FORMAT_DIRECT_QUERY  (WAVE_FORMAT_QUERY | WAVE_FORMAT_DIRECT)


/* general waveform format (information common to all formats) */
/* as read from a file.  See Multimedia file formats in Programmer Reference */
typedef struct {
    WORD    wFormatTag;        // format type
    WORD    nChannels;         // number of channels (i.e. mono, stereo, etc.)
    DWORD   nSamplesPerSec;    // sample rate
    DWORD   nAvgBytesPerSec;   // for buffer estimation
    WORD    nBlockAlign;       // block size of data
} WAVEFORMAT;
typedef WAVEFORMAT       *PWAVEFORMAT;
typedef WAVEFORMAT      *NPWAVEFORMAT;
typedef WAVEFORMAT      *LPWAVEFORMAT;
typedef CONST WAVEFORMAT  *LPCWAVEFORMAT;

/* flags for wFormatTag field of WAVEFORMAT */
#define WAVE_FORMAT_PCM     1  // Needed in resource files so outside #ifndef RC_INVOKED #endif



/* specific waveform format for PCM data */
typedef struct tagPCMWAVEFORMAT {
    WAVEFORMAT  wf;
    WORD        wBitsPerSample;        // corresponds to MCI_WAVE_SET_.... structure
} PCMWAVEFORMAT;
typedef PCMWAVEFORMAT       *PPCMWAVEFORMAT;
typedef PCMWAVEFORMAT      *NPPCMWAVEFORMAT;
typedef PCMWAVEFORMAT      *LPPCMWAVEFORMAT;


/* wave data block header */
/**
 * This structure defines the header used to identify a waveform-audio buffer.
 *
 * Use the WHDR_BEGINLOOP and WHDR_ENDLOOP flags in the dwFlags member to specify the beginning and
 * ending data blocks for looping. To loop on a single block, specify both flags for the same block.
 * Use the dwLoops member in the WAVEHDR structure for the first block in the loop to specify the
 * number of times to play the loop.
 *
 * The lpData, dwBufferLength, and dwFlags members must be set before calling the
 * waveInPrepareHeader or waveOutPrepareHeader function. For either function, the dwFlags member
 * must be set to zero.
 */
typedef struct wavehdr_tag {
    /**
     * Long pointer to the address of the waveform buffer.
     */
    LPSTR       lpData;                 /* pointer to locked data buffer */
    /**
     * Specifies the length, in bytes, of the buffer.
     */
    DWORD       dwBufferLength;         /* length of data buffer */
    /**
     * When the header is used in input, this member specifies how much data is in the buffer.
     */
    DWORD       dwBytesRecorded;        /* used for input only */
    /**
     * Specifies user data.
     */
    DWORD       dwUser;                 /* for client's use */
    /**
     * Specifies information about the buffer. It is one of the following flags: Value Description
     * WHDR_BEGINLOOP This buffer is the first buffer in a loop. This flag is used only with output
     * buffers. WHDR_DONE Set by the device driver to indicate that it is finished with the buffer and
     * is returning it to the application. WHDR_ENDLOOP This buffer is the last buffer in a loop. This
     * flag is used only with output buffers. WHDR_INQUEUE Set by Windows to indicate that the buffer is
     * queued for playback. WHDR_PREPARED Set by Windows to indicate that the buffer has been prepared
     * with the waveInPrepareHeader or waveOutPrepareHeader function.
     */
    DWORD       dwFlags;                /* assorted flags (see defines) */
    /**
     * Specifies the number of times to play the loop. This member is used only with output buffers.
     */
    DWORD       dwLoops;                /* loop control counter */
    struct wavehdr_tag FAR *lpNext;     /* reserved for driver */
    /**
     * Reserved.
     */
    DWORD       reserved;               /* reserved for driver */
} WAVEHDR, *PWAVEHDR, NEAR *NPWAVEHDR, FAR *LPWAVEHDR;

/* flags for dwFlags field of WAVEHDR */
#define WHDR_DONE       0x00000001  /* done bit */
#define WHDR_PREPARED   0x00000002  /* set if this header has been prepared */
#define WHDR_BEGINLOOP  0x00000004  /* loop start block */
#define WHDR_ENDLOOP    0x00000008  /* loop end block */
#define WHDR_INQUEUE    0x00000010  /* reserved for driver */

/* waveform output device capabilities structure */
/**
 * This structure describes the capabilities of a waveform-audio output device.
 *
 * If a device supports volume changes, the WAVECAPS_VOLUME flag is set for the dwSupport member. If
 * a device supports separate volume changes on the left and right channels, both the
 * WAVECAPS_VOLUME and the WAVECAPS_LRVOLUME flags are set for this member.
 */
typedef struct tagWAVEOUTCAPS {
    /**
     * Manufacturer identifier for the device driver for the device. Manufacturer identifiers are
     * defined in Manufacturer and Product Identifiers.
     */
    WORD    wMid;                  /* manufacturer ID */
    /**
     * Product identifier for the device. Product identifiers are defined in Manufacturer and Product
     * Identifiers.
     */
    WORD    wPid;                  /* product ID */
    /**
     * Version number of the device driver for the device. The high-order byte is the major version
     * number, and the low-order byte is the minor version number.
     */
    MMVERSION vDriverVersion;      /* version of the driver */
    /**
     * Null-terminated string that contains the product name.
     */
    TCHAR   szPname[MAXPNAMELEN];  /* product name (NULL terminated string) */
    /**
     * Specifies the standard formats that are supported. It is one or a combination of the following
     * flags: Flag Description WAVE_FORMAT_1M08 11.025 kHz, mono, 8-bit WAVE_FORMAT_1M16 11.025 kHz,
     * mono, 16-bit WAVE_FORMAT_1S08 11.025 kHz, stereo, 8-bit WAVE_FORMAT_1S16 11.025 kHz, stereo,
     * 16-bit WAVE_FORMAT_2M08 22.05 kHz, mono, 8-bit WAVE_FORMAT_2M16 22.05 kHz, mono, 16-bit
     * WAVE_FORMAT_2S08 22.05 kHz, stereo, 8-bit WAVE_FORMAT_2S16 22.05 kHz, stereo, 16-bit
     * WAVE_FORMAT_4M08 44.1 kHz, mono, 8-bit WAVE_FORMAT_4M16 44.1 kHz, mono, 16-bit WAVE_FORMAT_4S08
     * 44.1 kHz, stereo, 8-bit WAVE_FORMAT_4S16 44.1 kHz, stereo, 16-bit
     */
    DWORD   dwFormats;             /* formats supported */
    /**
     * Number specifying whether the device supports mono (1) or stereo (2) output.
     */
    WORD    wChannels;             /* number of sources supported */
    /**
     * Packing.
     */
    WORD    wReserved1;            /* packing */
    /**
     * Specifies the optional functionality supported by the device. It is one of the following flags:
     * Value Description WAVECAPS_LRVOLUME Supports separate left and right volume control.
     * WAVECAPS_PITCH Supports pitch control. WAVECAPS_PLAYBACKRATE Supports playback rate control.
     * WAVECAPS_SYNC The driver is synchronous and blocks while playing a buffer. WAVECAPS_VOLUME
     * Supports volume control. WAVECAPS_SAMPLEACCURATE Returns sample-accurate position information.
     */
    DWORD   dwSupport;             /* functionality supported by driver */
} WAVEOUTCAPS, *PWAVEOUTCAPS, *NPWAVEOUTCAPS, *LPWAVEOUTCAPS;


/* flags for dwSupport field of WAVEOUTCAPS */
#define WAVECAPS_PITCH          0x0001   /* supports pitch control */
#define WAVECAPS_PLAYBACKRATE   0x0002   /* supports playback rate control */
#define WAVECAPS_VOLUME         0x0004   /* supports volume control */
#define WAVECAPS_LRVOLUME       0x0008   /* separate left-right volume control */
#define WAVECAPS_SYNC           0x0010
#define WAVECAPS_SAMPLEACCURATE 0x0020
#define WAVECAPS_DIRECTSOUND    0x0040

/* waveform input device capabilities structure */
/**
 * This structure describes the capabilities of a waveform-audio input device.
 */
typedef struct tagWAVEINCAPS {
    /**
     * Manufacturer identifier for the device driver for the waveform-audio input device. Manufacturer
     * identifiers are defined in Manufacturer and Product Identifiers.
     */
    WORD    wMid;                    /* manufacturer ID */
    /**
     * Product identifier for the waveform-audio input device. Product identifiers are defined in
     * Manufacturer and Product Identifiers.
     */
    WORD    wPid;                    /* product ID */
    /**
     * Version number of the device driver for the waveform-audio input device. The high-order byte is
     * the major version number, and the low-order byte is the minor version number.
     */
    MMVERSION vDriverVersion;        /* version of the driver */
    /**
     * Null-terminated string that contains the product name.
     */
    TCHAR   szPname[MAXPNAMELEN];    /* product name (NULL terminated string) */
    /**
     * Specifies the standard formats that are supported. It is one or a combination of the following
     * flags: Flag Description WAVE_FORMAT_1M08 11.025 kHz, mono, 8-bit WAVE_FORMAT_1M16 11.025 kHz,
     * mono, 16-bit WAVE_FORMAT_1S08 11.025 kHz, stereo, 8-bit WAVE_FORMAT_1S16 11.025 kHz, stereo,
     * 16-bit WAVE_FORMAT_2M08 22.05 kHz, mono, 8-bit WAVE_FORMAT_2M16 22.05 kHz, mono, 16-bit
     * WAVE_FORMAT_2S08 22.05 kHz, stereo, 8-bit WAVE_FORMAT_2S16 22.05 kHz, stereo, 16-bit
     * WAVE_FORMAT_4M08 44.1 kHz, mono, 8-bit WAVE_FORMAT_4M16 44.1 kHz, mono, 16-bit WAVE_FORMAT_4S08
     * 44.1 kHz, stereo, 8-bit WAVE_FORMAT_4S16 44.1 kHz, stereo, 16-bit
     */
    DWORD   dwFormats;               /* formats supported */
    /**
     * Number that specifies whether the device supports mono (1) or stereo (2) input.
     */
    WORD    wChannels;               /* number of channels supported */
    /**
     * Padding.
     */
    WORD    wReserved1;              /* structure packing */
} WAVEINCAPS, *PWAVEINCAPS, *NPWAVEINCAPS, *LPWAVEINCAPS;

/* defines for dwFormat field of WAVEINCAPS and WAVEOUTCAPS */
#define WAVE_INVALIDFORMAT     0x00000000       /* invalid format */
#define WAVE_FORMAT_1M08       0x00000001       /* 11.025 kHz, Mono,   8-bit  */
#define WAVE_FORMAT_1S08       0x00000002       /* 11.025 kHz, Stereo, 8-bit  */
#define WAVE_FORMAT_1M16       0x00000004       /* 11.025 kHz, Mono,   16-bit */
#define WAVE_FORMAT_1S16       0x00000008       /* 11.025 kHz, Stereo, 16-bit */
#define WAVE_FORMAT_2M08       0x00000010       /* 22.05  kHz, Mono,   8-bit  */
#define WAVE_FORMAT_2S08       0x00000020       /* 22.05  kHz, Stereo, 8-bit  */
#define WAVE_FORMAT_2M16       0x00000040       /* 22.05  kHz, Mono,   16-bit */
#define WAVE_FORMAT_2S16       0x00000080       /* 22.05  kHz, Stereo, 16-bit */
#define WAVE_FORMAT_4M08       0x00000100       /* 44.1   kHz, Mono,   8-bit  */
#define WAVE_FORMAT_4S08       0x00000200       /* 44.1   kHz, Stereo, 8-bit  */
#define WAVE_FORMAT_4M16       0x00000400       /* 44.1   kHz, Mono,   16-bit */
#define WAVE_FORMAT_4S16       0x00000800       /* 44.1   kHz, Stereo, 16-bit */



#ifndef _WAVEFORMATEX_
#define _WAVEFORMATEX_

/*
 *  extended waveform format structure used for all non-PCM formats. this
 *  structure is common to all non-PCM formats.
 */
/**
 * This structure defines the format of waveform-audio data. Only format information common to all
 * waveform-audio data formats is included in this structure. For formats that require additional
 * information, this structure is included as the first member in another structure, along with the
 * additional information.
 *
 * An example of a format that uses extra information is the Microsoft Adaptive Delta Pulse Code
 * Modulation (MS-ADPCM) format. The wFormatTag for MS-ADPCM is WAVE_FORMAT_ADPCM. The cbSize member
 * is typically set to 32. The extra information stored for WAVE_FORMAT_ADPCM is coefficient pairs
 * required for encoding and decoding the waveform-audio data.
 */
typedef struct tWAVEFORMATEX
{
    /**
     * Waveform-audio format type. Format tags are registered with Microsoft Corporation for many
     * compression algorithms. A complete list of format tags can be found in the Mmsystem.h header
     * file.
     */
    WORD        wFormatTag;         /* format type */
    /**
     * Number of channels in the waveform-audio data. Monaural data uses one channel and stereo data
     * uses two channels.
     */
    WORD        nChannels;          /* number of channels (i.e. mono, stereo...) */
    /**
     * Sample rate, in samples per second (hertz), that each channel should be played or recorded. If
     * wFormatTag is WAVE_FORMAT_PCM, then common values for nSamplesPerSec are 8.0 kHz, 11.025 kHz,
     * 22.05 kHz, and 44.1 kHz. For non-PCM formats, this member must be computed according to the
     * manufacturer's specification of the format tag.
     */
    DWORD       nSamplesPerSec;     /* sample rate */
    /**
     * Required average data-transfer rate, in bytes per second, for the format tag. If wFormatTag is
     * WAVE_FORMAT_PCM, nAvgBytesPerSec should be equal to the product of nSamplesPerSec and
     * nBlockAlign. For non-PCM formats, this member must be computed according to the manufacturer's
     * specification of the format tag.
     *
     * Playback and record software can estimate buffer sizes by using the nAvgBytesPerSec member.
     */
    DWORD       nAvgBytesPerSec;    /* for buffer estimation */
    /**
     * Block alignment, in bytes. The block alignment is the minimum atomic unit of data for the
     * wFormatTag format type. If wFormatTag is WAVE_FORMAT_PCM, nBlockAlign should be equal to the
     * product of nChannels and wBitsPerSample divided by 8 (bits per byte). For non-PCM formats, this
     * member must be computed according to the manufacturer's specification of the format tag.
     *
     * Playback and record software must process a multiple of nBlockAlign bytes of data at a time. Data
     * written and read from a device must always start at the beginning of a block. For example, it is
     * illegal to start playback of PCM data in the middle of a sample (that is, on a non-block-aligned
     * boundary).
     */
    WORD        nBlockAlign;        /* block size of data */
    /**
     * Bits per sample for the wFormatTag format type. If wFormatTag is WAVE_FORMAT_PCM, then
     * wBitsPerSample should be equal to 8 or 16. For non-PCM formats, this member must be set according
     * to the manufacturer's specification of the format tag. Note that some compression schemes cannot
     * define a value for wBitsPerSample, so this member can be zero.
     */
    WORD        wBitsPerSample;     /* number of bits per sample of mono data */
    /**
     * Size, in bytes, of extra format information appended to the end of the WAVEFORMATEX structure.
     * This information can be used by non-PCM formats to store extra attributes for the wFormatTag. If
     * no extra information is required by the wFormatTag, this member must be set to zero. For
     * WAVE_FORMAT_PCM formats only, this member is ignored.
     */
    WORD        cbSize;             /* the count in bytes of the size of */
                    /* extra information (after cbSize) */
} WAVEFORMATEX, *PWAVEFORMATEX, NEAR *NPWAVEFORMATEX, FAR *LPWAVEFORMATEX;
typedef const WAVEFORMATEX FAR *LPCWAVEFORMATEX;

#endif /* _WAVEFORMATEX_ */


/* waveform audio function prototypes */
/**
 * This function retrieves the number of waveform output devices present in the system.
 *
 * @return The number of devices indicates success. Zero indicates that no devices are present or
 *   that an error occurred.
 */
UINT     WINAPI waveOutGetNumDevs(void);
/**
 * This function queries a specified waveform device to determine its capabilities.
 *
 * @param uDeviceID Identifier of the waveform-audio output device. It can be either a device
 *   identifier or a Handle to an open waveform-audio output device.
 * @param pwoc Pointer to a WAVEOUTCAPS structure to be filled with information about the
 *   capabilities of the device.
 * @param cbwoc Size, in bytes, of the WAVEOUTCAPS structure.
 *
 * @return One of the values described in the following table is returned. Value Description
 *   MMSYSERR_NOERROR Success. MMSYSERR_INVALHANDLE Specified device handle is invalid.
 *   MMSYSERR_NODRIVER No device driver is present. MMSYSERR_NOMEM Unable to allocate or lock memory.
 *
 * Use the waveOutGetNumDevs function to determine the number of waveform-audio output devices
 * present in the system. If the value specified by the uDeviceID parameter is a device identifier,
 * it can vary from zero to one less than the number of devices present. The WAVE_MAPPER constant
 * can also be used as a device identifier. Only cbwoc bytes (or less) of information is copied to
 * the location pointed to by pwoc. If cbwoc is zero, nothing is copied and the function returns
 * zero.
 */
MMRESULT WINAPI waveOutGetDevCaps(UINT uDeviceID, LPWAVEOUTCAPS pwoc, UINT cbwoc);
/**
 * This function queries the current volume setting of a waveform output device.
 *
 * @param hwo Handle to an open waveform-audio output device. This parameter can also be a device
 *   identifier.
 * @param pdwVolume Pointer to a variable to be filled with the current volume setting. The
 *   low-order word of this location contains the left-channel volume setting, and the high-order word
 *   contains the right-channel setting. A value of 0xFFFF represents full volume, and a value of
 *   0x0000 is silence. If a device does not support both left and right volume control, the low-order
 *   word of the specified location contains the mono volume level. The full 16-bit setting(s) set
 *   with the waveOutSetVolume function is returned, regardless of whether the device supports the
 *   full 16 bits of volume-level control.
 *
 * @return One of the values described in the following table is returned. Value Description
 *   MMSYSERR_NOERROR Success. MMSYSERR_INVALHANDLE Specified device handle is invalid.
 *   MMSYSERR_NODRIVER No device driver is present. MMSYSERR_NOMEM Unable to allocate or lock memory.
 *   MMSYSERR_NOTSUPPORTED Function is not supported.
 *
 * If a device identifier is used, then the result of the waveOutGetVolume call and the information
 * returned in pdwVolume applies to all instances of the device. If a device handle is used, then
 * the result and information returned applies only to the instance of the device referenced by the
 * device handle.
 *
 * Not all devices support volume changes. To determine whether the device supports volume control,
 * use the WAVECAPS_VOLUME flag to test the dwSupport member of the WAVEOUTCAPS structure (filled by
 * the waveOutGetDevCaps function).
 *
 * To determine whether the device supports left- and right-channel volume control, use the
 * WAVECAPS_LRVOLUME flag to test the dwSupport member of the WAVEOUTCAPS structure (filled by
 * waveOutGetDevCaps).
 *
 * Volume settings are interpreted logarithmically. This means the perceived increase in volume is
 * the same when increasing the volume level from 0x5000 to 0x6000 as it is from 0x4000 to 0x5000.
 */
MMRESULT WINAPI waveOutGetVolume(HWAVEOUT hwo, LPDWORD pdwVolume);
/**
 * This function sets the volume of a waveform output device.
 *
 * @param hwo Handle to an open waveform-audio output device. This parameter can also be a device
 *   identifier.
 * @param dwVolume Specifies a new volume setting. The low-order word contains the left-channel
 *   volume setting, and the high-order word contains the right-channel setting. A value of 0xFFFF
 *   represents full volume, and a value of 0x0000 is silence. If a device does not support both left
 *   and right volume control, the low-order word of dwVolume specifies the volume level, and the
 *   high-order word is ignored.
 *
 * @return One of the values described in the following table is returned. Value Description
 *   MMSYSERR_NOERROR Success. MMSYSERR_INVALHANDLE Specified device handle is invalid.
 *   MMSYSERR_NODRIVER No device driver is present. MMSYSERR_NOMEM Unable to allocate or lock memory.
 *   MMSYSERR_NOTSUPPORTED Function is not supported.
 *
 * If a device identifier is used, then the result of the waveOutSetVolume call applies to all
 * instances of the device. If a device handle is used, then the result applies only to the instance
 * of the device referenced by the device handle.
 *
 * Not all devices support volume changes. To determine whether the device supports volume control,
 * use the WAVECAPS_VOLUME flag to test the dwSupport member of the WAVEOUTCAPS structure (filled by
 * the waveOutGetDevCaps function). To determine whether the device supports volume control on both
 * the left and right channels, use the WAVECAPS_LRVOLUME flag.
 *
 * Most devices do not support the full 16 bits of volume-level control and will not use the
 * high-order bits of the requested volume setting. For example, for a device that supports 4 bits
 * of volume control, requested volume level values of 0x4000, 0x4FFF, and 0x43BE all produce the
 * same physical volume setting: 0x4000. The waveOutGetVolume function returns the full 16-bit
 * setting set with waveOutSetVolume.
 *
 * Volume settings are interpreted logarithmically. This means the perceived increase in volume is
 * the same when increasing the volume level from 0x5000 to 0x6000 as it is from 0x4000 to 0x5000.
 */
MMRESULT WINAPI waveOutSetVolume(HWAVEOUT hwo, DWORD dwVolume);
/**
 * This function retrieves a textual description of the error identified by the specified error
 * number.
 *
 * @param mmrError Error number.
 * @param pszText Address of a buffer to be filled with the textual error description.
 * @param cchText Size, in characters, of the buffer pointed to by pszText.
 *
 * @return One of the values described in the following table is returned. Value Description
 *   MMSYSERR_NOERROR Success. MMSYSERR_INVALHANDLE Specified device handle is invalid.
 *   MMSYSERR_NODRIVER No device driver is present. MMSYSERR_NOMEM Unable to allocate or lock memory.
 *
 * If the textual error description is longer than the specified buffer, the description is
 * truncated. The returned error string is always null-terminated. If cchText is zero, nothing is
 * copied and the function returns zero. All error descriptions are less than MAXERRORLENGTH
 * characters long.
 */
MMRESULT WINAPI waveOutGetErrorText(MMRESULT mmrError, LPTSTR pszText, UINT cchText);
/**
 * This function closes the specified waveform output device.
 *
 * @param hwo Handle to the waveform-audio output device. If the function succeeds, the handle is no
 *   longer valid after this call.
 *
 * @return One of the values described in the following table is returned. Value Description
 *   MMSYSERR_NOERROR Success. MMSYSERR_INVALHANDLE Specified device handle is invalid.
 *   MMSYSERR_NODRIVER No device driver is present. MMSYSERR_NOMEM Unable to allocate or lock memory.
 *   WAVERR_STILLPLAYING There are still buffers in the queue.
 *
 * If the device is still playing a waveform-audio file, the close operation fails. Use the
 * waveOutReset function to terminate playback before calling waveOutClose.
 */
MMRESULT WINAPI waveOutClose(HWAVEOUT hwo);
/**
 * This function prepares a waveform data block for playback.
 *
 * @param hwo Handle to the waveform-audio output device.
 * @param pwh Pointer to a WAVEHDR structure that identifies the data block to be prepared.
 * @param cbwh Size, in bytes, of the WAVEHDR structure.
 *
 * @return One of the values described in the following table is returned. Value Description
 *   MMSYSERR_NOERROR Success. MMSYSERR_INVALHANDLE Specified device handle is invalid.
 *   MMSYSERR_NODRIVER No device driver is present. MMSYSERR_NOMEM Unable to allocate or lock memory.
 *
 * The lpData, dwBufferLength, and dwFlags members of the WAVEHDR structure must be set before
 * calling this function (dwFlags must be zero).
 *
 * The dwFlags, dwBufferLength, and dwLoops members of the WAVEHDR structure can change between
 * calls to this function and the waveOutWrite function. (The only flags that can change in this
 * interval for the dwFlags member are WHDR_BEGINLOOP and WHDR_ENDLOOP.) If you change the size
 * specified by dwBufferLength before the call to waveOutWrite, the new value must be less than the
 * prepared value.
 *
 * Preparing a header that has already been prepared has no effect, and the function returns zero.
 */
MMRESULT WINAPI waveOutPrepareHeader(HWAVEOUT hwo, LPWAVEHDR pwh, UINT cbwh);
/**
 * This function cleans up the preparation performed by waveOutPrepareHeader. The function must be
 * called after the device driver is finished with a data block. You must call this function before
 * freeing the data buffer.
 *
 * @param hwo Handle to the waveform-audio output device.
 * @param pwh Pointer to a WAVEHDR structure identifying the data block to be cleaned up.
 * @param cbwh Size, in bytes, of the WAVEHDR structure.
 *
 * @return One of the values described in the following table is returned. Value Description
 *   MMSYSERR_NOERROR Success. MMSYSERR_INVALHANDLE Specified device handle is invalid.
 *   MMSYSERR_NODRIVER No device driver is present. MMSYSERR_NOMEM Unable to allocate or lock memory.
 *   WAVERR_STILLPLAYING Data block pointed to by the pwh parameter is still in the queue.
 *
 * This function complements waveOutPrepareHeader. You must call this function before freeing the
 * buffer. After passing a buffer to the device driver with the waveOutWrite function, you must wait
 * until the driver is finished with the buffer before calling waveOutUnprepareHeader.
 *
 * Unpreparing a buffer that has not been prepared has no effect, and the function returns zero.
 */
MMRESULT WINAPI waveOutUnprepareHeader(HWAVEOUT hwo, LPWAVEHDR pwh, UINT cbwh);
/**
 * This function sends a data block to the specified waveform output device.
 *
 * @param hwo Handle to the waveform-audio output device.
 * @param pwh Pointer to a WAVEHDR structure containing information about the data block.
 * @param cbwh Size, in bytes, of the WAVEHDR structure.
 *
 * @return One of the values described in the following table is returned. Value Description
 *   MMSYSERR_NOERROR Success. MMSYSERR_INVALHANDLE Specified device handle is invalid.
 *   MMSYSERR_NODRIVER No device driver is present. MMSYSERR_NOMEM Unable to allocate or lock memory.
 *   WAVERR_UNPREPARED Data block pointed to by the pwh parameter has not been prepared.
 *
 * When the buffer is finished, the WHDR_DONE bit is set in the dwFlags member of the WAVEHDR
 * structure.
 *
 * The buffer must be prepared with the waveOutPrepareHeader function before it is passed to
 * waveOutWrite. Unless the device is paused by calling the waveOutPause function, playback begins
 * when the first data block is sent to the device.
 */
MMRESULT WINAPI waveOutWrite(HWAVEOUT hwo, LPWAVEHDR pwh, UINT cbwh);
/**
 * This function pauses playback on a specified waveform output device. The current playback
 * position is saved. Use waveOutRestart to resume playback from the current playback position.
 *
 * @param hwo Handle to the waveform-audio output device.
 *
 * @return One of the values described in the following table is returned. Value Description
 *   MMSYSERR_NOERROR Success. MMSYSERR_INVALHANDLE Specified device handle is invalid.
 *   MMSYSERR_NODRIVER No device driver is present. MMSYSERR_NOMEM Unable to allocate or lock memory.
 *   MMSYSERR_NOTSUPPORTED Function is not supported.
 *
 * Calling this function when the output is already paused has no effect, and the function returns
 * zero.
 */
MMRESULT WINAPI waveOutPause(HWAVEOUT hwo);
/**
 * This function restarts a paused waveform output device.
 *
 * @param hwo Handle to the waveform-audio output device.
 *
 * @return One of the values described in the following table is returned. Value Description
 *   MMSYSERR_NOERROR Success. MMSYSERR_INVALHANDLE Specified device handle is invalid.
 *   MMSYSERR_NODRIVER No device driver is present. MMSYSERR_NOMEM Unable to allocate or lock memory.
 *   MMSYSERR_NOTSUPPORTED Function is not supported.
 *
 * Calling this function when the output is not paused has no effect, and the function returns zero.
 */
MMRESULT WINAPI waveOutRestart(HWAVEOUT hwo);
/**
 * This function stops playback on a specified waveform output device and resets the current
 * position to 0. All pending playback buffers are marked as done and returned to the application.
 *
 * @param hwo Handle to the waveform-audio output device.
 *
 * @return One of the values described in the following table is returned. Value Description
 *   MMSYSERR_NOERROR Success. MMSYSERR_INVALHANDLE Specified device handle is invalid.
 *   MMSYSERR_NODRIVER No device driver is present. MMSYSERR_NOMEM Unable to allocate or lock memory.
 *   MMSYSERR_NOTSUPPORTED Function is not supported.
 */
MMRESULT WINAPI waveOutReset(HWAVEOUT hwo);
/**
 * This function breaks a loop on a specified waveform output device and allows playback to continue
 * with the next block in the driver list.
 *
 * @param hwo Handle to the waveform-audio output device.
 *
 * @return One of the values described in the following table is returned. Value Description
 *   MMSYSERR_NOERROR Success. MMSYSERR_INVALHANDLE Specified device handle is invalid.
 *   MMSYSERR_NODRIVER No device driver is present. MMSYSERR_NOMEM Unable to allocate or lock memory.
 *
 * The blocks making up the loop are played to the end before the loop is terminated.
 *
 * Calling this function when nothing is playing or looping has no effect, and the function returns
 * zero.
 */
MMRESULT WINAPI waveOutBreakLoop(HWAVEOUT hwo);
/**
 * This function retrieves the current playback position of the specified waveform output device.
 *
 * @param hwo Handle to the waveform-audio output device.
 * @param pmmt Pointer to an MMTIME structure.
 * @param cbmmt Size, in bytes, of the MMTIME structure.
 *
 * @return One of the values described in the following table is returned. Value Description
 *   MMSYSERR_NOERROR Success. MMSYSERR_INVALHANDLE Specified device handle is invalid.
 *   MMSYSERR_NODRIVER No device driver is present. MMSYSERR_NOMEM Unable to allocate or lock memory.
 *
 * Before calling this function, set the wType member of the MMTIME structure to indicate the time
 * format you want. After calling this function, check wType to determine whether the time format is
 * supported. If the format is not supported, wType will specify an alternative format.
 *
 * The position is set to zero when the device is opened or reset.
 */
MMRESULT WINAPI waveOutGetPosition(HWAVEOUT hwo, LPMMTIME pmmt, UINT cbmmt);
/**
 * This function queries the current pitch setting of a waveform output device.
 *
 * @param hwo Handle to the waveform-audio output device.
 * @param pdwPitch Pointer to a variable to be filled with the current pitch multiplier setting. The
 *   pitch multiplier indicates the current change in pitch from the original authored setting. The
 *   pitch multiplier must be a positive value. The pitch multiplier is specified as a fixed-point
 *   value. The high-order word of the variable contains the signed integer part of the number, and
 *   the low-order word contains the fractional part. A value of 0x8000 in the low-order word
 *   represents one-half, and 0x4000 represents one-quarter. For example, the value 0x00010000
 *   specifies a multiplier of 1.0 (no pitch change), and a value of 0x000F8000 specifies a multiplier
 *   of 15.5.
 *
 * @return One of the values described in the following table is returned. Value Description
 *   MMSYSERR_NOERROR Success. MMSYSERR_INVALHANDLE Specified device handle is invalid.
 *   MMSYSERR_NODRIVER No device driver is present. MMSYSERR_NOMEM Unable to allocate or lock memory.
 *   MMSYSERR_NOTSUPPORTED Function is not supported.
 *
 * Changing the pitch does not change the playback rate, sample rate, or playback time. Not all
 * devices support pitch changes. To determine whether the device supports pitch control, use the
 * WAVECAPS_PITCH flag to test the dwSupport member of the WAVEOUTCAPS structure (filled by the
 * waveOutGetDevCaps function).
 */
MMRESULT WINAPI waveOutGetPitch(HWAVEOUT hwo, LPDWORD pdwPitch);
/**
 * This function sets the pitch of a waveform output device.
 *
 * @param hwo Handle to the waveform-audio output device.
 * @param dwPitch Specifies a new pitch multiplier setting. This setting indicates the current
 *   change in pitch from the original authored setting. The pitch multiplier must be a positive
 *   value. The pitch multiplier is specified as a fixed-point value. The high-order word contains the
 *   signed integer part of the number, and the low-order word contains the fractional part. A value
 *   of 0x8000 in the low-order word represents one-half, and 0x4000 represents one-quarter. For
 *   example, the value 0x00010000 specifies a multiplier of 1.0 (no pitch change), and a value of
 *   0x000F8000 specifies a multiplier of 15.5.
 *
 * @return One of the values described in the following table is returned. Value Description
 *   MMSYSERR_NOERROR Success. MMSYSERR_INVALHANDLE Specified device handle is invalid.
 *   MMSYSERR_NODRIVER No device driver is present. MMSYSERR_NOMEM Unable to allocate or lock memory.
 *   MMSYSERR_NOTSUPPORTED Function is not supported.
 *
 * Changing the pitch does not change the playback rate or the sample rate, nor does it change the
 * playback time. Not all devices support pitch changes. To determine whether the device supports
 * pitch control, use the WAVECAPS_PITCH flag to test the dwSupport member of the WAVEOUTCAPS
 * structure (filled by the waveOutGetDevCaps function).
 */
MMRESULT WINAPI waveOutSetPitch(HWAVEOUT hwo, DWORD dwPitch);
/**
 * This function queries the current playback rate setting of a waveform output device.
 *
 * @param hwo Handle to the waveform-audio output device.
 * @param pdwRate Pointer to a variable to be filled with the current playback rate. The playback
 *   rate setting is a multiplier indicating the current change in playback rate from the original
 *   authored setting. The playback rate multiplier must be a positive value. The rate is specified as
 *   a fixed-point value. The high-order word of the variable contains the signed integer part of the
 *   number, and the low-order word contains the fractional part. A value of 0x8000 in the low-order
 *   word represents one-half, and 0x4000 represents one-quarter. For example, the value 0x00010000
 *   specifies a multiplier of 1.0 (no playback rate change), and a value of 0x000F8000 specifies a
 *   multiplier of 15.5.
 *
 * @return One of the values described in the following table is returned. Value Description
 *   MMSYSERR_NOERROR Success. MMSYSERR_INVALHANDLE Specified device handle is invalid.
 *   MMSYSERR_NODRIVER No device driver is present. MMSYSERR_NOMEM Unable to allocate or lock memory.
 *   MMSYSERR_NOTSUPPORTED Function is not supported.
 *
 * Changing the playback rate does not change the sample rate but does change the playback time. Not
 * all devices support playback rate changes. To determine whether a device supports playback rate
 * changes, use the WAVECAPS_PLAYBACKRATE flag to test the dwSupport member of the WAVEOUTCAPS
 * structure (filled by the waveOutGetDevCaps function).
 */
MMRESULT WINAPI waveOutGetPlaybackRate(HWAVEOUT hwo, LPDWORD pdwRate);
/**
 * This function sets the playback rate of a waveform output device.
 *
 * @param hwo Handle to the waveform-audio output device.
 * @param dwRate Specifies a new playback rate setting. This setting is a multiplier indicating the
 *   current change in playback rate from the original authored setting. The playback rate multiplier
 *   must be a positive value. The rate is specified as a fixed-point value. The high-order word
 *   contains the signed integer part of the number, and the low-order word contains the fractional
 *   part. A value of 0x8000 in the low-order word represents one-half, and 0x4000 represents
 *   one-quarter. For example, the value 0x00010000 specifies a multiplier of 1.0 (no playback rate
 *   change), and a value of 0x000F8000 specifies a multiplier of 15.5.
 *
 * @return One of the values described in the following table is returned. Value Description
 *   MMSYSERR_NOERROR Success. MMSYSERR_INVALHANDLE Specified device handle is invalid.
 *   MMSYSERR_NODRIVER No device driver is present. MMSYSERR_NOMEM Unable to allocate or lock memory.
 *   MMSYSERR_NOTSUPPORTED Function is not supported.
 *
 * Changing the playback rate does not change the sample rate but does change the playback time. Not
 * all devices support playback rate changes. To determine whether a device supports playback rate
 * changes, use the WAVECAPS_PLAYBACKRATE flag to test the dwSupport member of the WAVEOUTCAPS
 * structure (filled by the waveOutGetDevCaps function).
 */
MMRESULT WINAPI waveOutSetPlaybackRate(HWAVEOUT hwo, DWORD dwRate);
/**
 * This function gets the device identifier for a waveform output device.
 *
 * @param hwo Handle to the waveform-audio output device.
 * @param puDeviceID Pointer to a variable to be filled with the device identifier.
 *
 * @return One of the values described in the following table is returned. Value Description
 *   MMSYSERR_NOERROR Success. MMSYSERR_INVALHANDLE The hwo parameter specifies an invalid handle.
 *   MMSYSERR_NODRIVER No device driver is present. MMSYSERR_NOMEM Unable to allocate or lock memory.
 */
MMRESULT WINAPI waveOutGetID(HWAVEOUT hwo, LPUINT puDeviceID);
/**
 * This function sends messages to the waveform output device drivers.
 *
 * @param hwo Handle to the waveform-audio output device.
 * @param uMsg Message to send.
 * @param dwParam1 and dwParam2 Specifies message parameters.
 *
 * @return The value returned from the driver indicates success.
 */
MMRESULT WINAPI waveOutMessage(HWAVEOUT hwo, UINT uMsg, DWORD dw1, DWORD dw2);
/**
 * This function opens a specified waveform output device for playback.
 *
 * @param phwo Address filled with a handle identifying the open waveform-audio output device. Use
 *   the handle to identify the device when calling other waveform-audio output functions. This
 *   parameter might be NULL if the WAVE_FORMAT_QUERY flag is specified for fdwOpen.
 * @param uDeviceID Identifier of the waveform-audio output device to open. It can be either a
 *   device identifier or a Handle to an open waveform-audio input device. You can use the following
 *   flag instead of a device identifier: Value Description WAVE_MAPPER The function selects a
 *   waveform-audio output device capable of playing the specified format.
 * @param pwfx Pointer to a WAVEFORMATEX structure that identifies the format of the waveform-audio
 *   data to be sent to the device. You can free this structure immediately after passing it to
 *   waveOutOpen.
 * @param dwCallback Specifies the address of a fixed callback function, an event handle, a handle
 *   to a window, or the identifier of a thread to be called during waveform-audio playback to process
 *   messages related to the progress of the playback. If no callback function is required, this value
 *   can be zero.
 * @param dwCallbackInstance Specifies user-instance data passed to the callback mechanism. This
 *   parameter is not used with the window callback mechanism.
 * @param fdwOpen Flags for opening the device. The following values are defined: Value Description
 *   CALLBACK_EVENT The dwCallback parameter is an event handle. CALLBACK_FUNCTION The dwCallback
 *   parameter is a callback procedure address. CALLBACK_NULL No callback mechanism. This is the
 *   default setting. CALLBACK_THREAD The dwCallback parameter is a thread identifier. CALLBACK_WINDOW
 *   The dwCallback parameter is a window handle. WAVE_ALLOWSYNC If this flag is specified, a
 *   synchronous waveform-audio device can be opened. If this flag is not specified while opening a
 *   synchronous driver, the device will fail to open. WAVE_FORMAT_DIRECT If this flag is specified,
 *   the ACM driver does not perform conversions on the audio data. WAVE_FORMAT_QUERY If this flag is
 *   specified, waveOutOpen queries the device to determine if it supports the specified format, but
 *   the device is not actually opened. WAVE_MAPPED If this flag is specified, the uDeviceID parameter
 *   specifies a waveform-audio device to be mapped to by the wave mapper.
 *
 * @return One of the values described in the following table is returned. Value Description
 *   MMSYSERR_NOERROR Success. MMSYSERR_INVALHANDLE Specified device handle is invalid.
 *   MMSYSERR_BADDEVICEID Specified device identifier is out of range. MMSYSERR_NODRIVER No device
 *   driver is present. MMSYSERR_NOMEM Unable to allocate or lock memory. WAVERR_BADFORMAT Attempted
 *   to open with an unsupported waveform-audio format. WAVERR_SYNC Device is synchronous but
 *   waveOutOpen was called without using the WAVE_ALLOWSYNC flag.
 *
 * Use the waveOutGetNumDevs function to determine the number of waveform-audio output devices
 * present in the system. If the value specified by the uDeviceID parameter is a device identifier,
 * it can vary from zero to one less than the number of devices present. The WAVE_MAPPER constant
 * can also be used as a device identifier.
 *
 * The structure pointed to by pwfx can be extended to include type-specific information for certain
 * data formats by using the WAVEFORMATEX structure to specify the length of the additional data.
 *
 * If you choose to have a window or thread receive callback information, the following messages are
 * sent to the window procedure function to indicate the progress of waveform-audio output:
 * MM_WOM_OPEN, MM_WOM_CLOSE, and MM_WOM_DONE.
 *
 * If you choose to have a function receive callback information, the following messages are sent to
 * the function to indicate the progress of waveform-audio output: WOM_OPEN, WOM_CLOSE, and
 * WOM_DONE.
 */
MMRESULT WINAPI waveOutOpen(LPHWAVEOUT phwo, UINT uDeviceID,
    LPCWAVEFORMATEX pwfx, DWORD dwCallback, DWORD dwInstance, DWORD fdwOpen);


/**
 * This retrieves the number of waveform input devices present in the system.
 *
 * @return The number of devices indicates success. Zero indicates that no devices are present or
 *   that an error occurred.
 */
UINT     WINAPI waveInGetNumDevs(void);
/**
 * This function retrieves the capabilities of a specified waveform-audio input device.
 *
 * @param uDeviceID Identifier of the waveform-audio output device. It can be either a device
 *   identifier or a Handle to an open waveform-audio input device.
 * @param pwic Pointer to a WAVEINCAPS structure to be filled with information about the
 *   capabilities of the device.
 * @param cbwic Size, in bytes, of the WAVEINCAPS structure.
 *
 * @return One of the values described in the following table is returned. Value Description
 *   MMSYSERR_NOERROR Success. MMSYSERR_BADDEVICEID Specified device identifier is out of range.
 *   MMSYSERR_NODRIVER No device driver is present. MMSYSERR_NOMEM Unable to allocate or lock memory.
 *
 * Use this function to determine the number of waveform-audio input devices present in the system.
 * If the value specified by the uDeviceID parameter is a device identifier, it can vary from zero
 * to one less than the number of devices present. The WAVE_MAPPER constant can also be used as a
 * device identifier. Only cbwic bytes (or less) of information is copied to the location pointed to
 * by pwic. If cbwic is zero, nothing is copied and the function returns zero.
 */
MMRESULT WINAPI waveInGetDevCaps(UINT uDeviceID, LPWAVEINCAPS pwic, UINT cbwic);
/**
 * This function retrieves a textual description of the error identified by the specified error
 * number.
 *
 * @param mmrError Error number.
 * @param pszText Address of the buffer to be filled with the textual error description.
 * @param cchText Size, in characters, of the buffer pointed to by pszText.
 *
 * @return One of the values described in the following table is returned. Value Description
 *   MMSYSERR_NOERROR Success. MMSYSERR_BADERRNUM Specified error number is out of range.
 *   MMSYSERR_NODRIVER No device driver is present. MMSYSERR_NOMEM Unable to allocate or lock memory.
 *
 * If the textual error description is longer than the specified buffer, the description is
 * truncated. The returned error string is always null-terminated. If cchText is zero, nothing is
 * copied and the function returns zero. All error descriptions are less than MAXERRORLENGTH
 * characters long.
 */
MMRESULT WINAPI waveInGetErrorText(MMRESULT mmrError, LPTSTR pszText, UINT cchText);
/**
 * This function closes the specified waveform-audio input device.
 *
 * @param hwi Handle to the waveform-audio input device. If the function succeeds, the handle is no
 *   longer valid after this call.
 *
 * @return One of the values described in the following table is returned. Value Description
 *   MMSYSERR_NOERROR Success. MMSYSERR_INVALHANDLE Specified device handle is invalid.
 *   MMSYSERR_NODRIVER No device driver is present. MMSYSERR_NOMEM Unable to allocate or lock memory.
 *   WAVERR_STILLPLAYING There are still buffers in the queue.
 *
 * If there are input buffers that have been sent with the waveInAddBuffer function and that haven't
 * been returned to the application, the close operation will fail. Call the waveInReset function to
 * mark all pending buffers as done.
 */
MMRESULT WINAPI waveInClose(HWAVEIN hwi);
/**
 * This function prepares a buffer for waveform input.
 *
 * @param hwi Handle to the waveform-audio input device.
 * @param pwh Pointer to a WAVEHDR structure that identifies the buffer to be prepared.
 * @param cbwh Size, in bytes, of the WAVEHDR structure.
 *
 * @return One of the values described in the following table is returned. Value Description
 *   MMSYSERR_NOERROR Success. MMSYSERR_INVALHANDLE Specified device handle is invalid.
 *   MMSYSERR_NODRIVER No device driver is present. MMSYSERR_NOMEM Unable to allocate or lock memory.
 *
 * The lpData, dwBufferLength, and dwFlags members of the WAVEHDR structure must be set before
 * calling this function (dwFlags must be zero).
 */
MMRESULT WINAPI waveInPrepareHeader(HWAVEIN hwi, LPWAVEHDR pwh, UINT cbwh);
/**
 * This function cleans up the preparation performed by waveInPrepareHeader. The function must be
 * called after the device driver fills a data buffer and returns it to the application. You must
 * call this function before freeing the data buffer.
 *
 * @param hwi Handle to the waveform-audio input device.
 * @param pwh Pointer to a WAVEHDR structure identifying the buffer to be cleaned up.
 * @param cbwh Size, in bytes, of the WAVEHDR structure.
 *
 * @return One of the values described in the following table is returned. Value Description
 *   MMSYSERR_NOERROR Success. MMSYSERR_INVALHANDLE Specified device handle is invalid.
 *   MMSYSERR_NODRIVER No device driver is present. MMSYSERR_NOMEM Unable to allocate or lock memory.
 *   WAVERR_STILLPLAYING Buffer pointed to by the pwh parameter is still in the queue.
 *
 * This function complements the waveInPrepareHeader function.
 *
 * You must call this function before freeing the buffer. After passing a buffer to the device
 * driver with the waveInAddBuffer function, you must wait until the driver is finished with the
 * buffer before calling waveInUnprepareHeader. Unpreparing a buffer that has not been prepared has
 * no effect, and the function returns zero.
 */
MMRESULT WINAPI waveInUnprepareHeader(HWAVEIN hwi, LPWAVEHDR pwh, UINT cbwh);
/**
 * This function sends an input buffer to the specified waveform-audio input device. When the buffer
 * is filled, the application is notified.
 *
 * @param hwi Handle to the waveform-audio input device.
 * @param pwh Pointer to a WAVEHDR structure that identifies the buffer.
 * @param cbwh Size, in bytes, of the WAVEHDR structure.
 *
 * @return One of the values described in the following table is returned. Value Description
 *   MMSYSERR_NOERROR Success. MMSYSERR_INVALHANDLE Specified device handle is invalid.
 *   MMSYSERR_NODRIVE No device driver is present. MMSYSERR_NOMEM Unable to allocate or lock memory.
 *   WAVERR_UNPREPARED Buffer pointed to by the pwh parameter has not been prepared.
 *
 * When the buffer is filled, the WHDR_DONE bit is set in the dwFlags member of the WAVEHDR
 * structure.
 *
 * The buffer must be prepared with the waveInPrepareHeader function before it is passed to this
 * function.
 */
MMRESULT WINAPI waveInAddBuffer(HWAVEIN hwi, LPWAVEHDR pwh, UINT cbwh);
/**
 * This function starts input on the specified waveform input device.
 *
 * @param hwi Handle to the waveform-audio input device.
 *
 * @return One of the values described in the following table is returned. Value Description
 *   MMSYSERR_NOERROR Success. MMSYSERR_INVALHANDLE Specified device handle is invalid.
 *   MMSYSERR_NODRIVER No device driver is present. MMSYSERR_NOMEM Unable to allocate or lock memory.
 *
 * Buffers are returned to the application when full or when the waveInReset function is called (the
 * dwBytesRecorded member in the header will contain the length of data). If there are no buffers in
 * the queue, the data is thrown away without notifying the application, and input continues.
 *
 * Calling this function when input is already started has no effect, and the function returns zero.
 */
MMRESULT WINAPI waveInStart(HWAVEIN hwi);
/**
 * This function stops waveform input.
 *
 * @param hwi Handle to the waveform-audio input device.
 *
 * @return One of the values described in the following table is returned. Value Description
 *   MMSYSERR_NOERROR Success. MMSYSERR_INVALHANDLE Specified device handle is invalid.
 *   MMSYSERR_NODRIVER No device driver is present. MMSYSERR_NOMEM Unable to allocate or lock memory.
 *
 * If there are any buffers in the queue, the current buffer will be marked as done (the
 * dwBytesRecorded member in the header will contain the length of data), but any empty buffers in
 * the queue will remain there.
 *
 * Calling this function when input is not started has no effect, and the function returns zero.
 */
MMRESULT WINAPI waveInStop(HWAVEIN hwi);
/**
 * This function stops input on a specified waveform input device and resets the current position to
 * 0. All pending buffers are marked as done and returned to the application.
 *
 * @param hwi Handle to the waveform-audio input device.
 *
 * @return One of the values described in the following table is returned. Value Description
 *   MMSYSERR_NOERROR Success. MMSYSERR_INVALHANDLE Specified device handle is invalid.
 *   MMSYSERR_NODRIVER No device driver is present. MMSYSERR_NOMEM Unable to allocate or lock memory.
 */
MMRESULT WINAPI waveInReset(HWAVEIN hwi);
/**
 * This function retrieves the current input position of the specified waveform input device.
 *
 * @param hwi Handle to the waveform-audio input device.
 * @param pmmt Pointer to an MMTIME structure.
 * @param cbmmt Size, in bytes, of the MMTIME structure.
 *
 * @return One of the values described in the following table is returned. Value Description
 *   MMSYSERR_NOERROR Success. MMSYSERR_INVALHANDLE Specified device handle is invalid.
 *   MMSYSERR_NODRIVER No device driver is present. MMSYSERR_NOMEM Unable to allocate or lock memory.
 *
 * Before calling this function, set the wType member of the MMTIME structure to indicate the time
 * format you want. After calling this function, check wType to determine whether the desired time
 * format is supported. If the format is not supported, the member will specify an alternative
 * format.
 *
 * The position is set to zero when the device is opened or reset.
 */
MMRESULT WINAPI waveInGetPosition(HWAVEIN hwi, LPMMTIME pmmt, UINT cbmmt);
/**
 * This function gets the device identifier for the specified waveform-audio input device.
 *
 * @param hwi Handle to the waveform-audio input device.
 * @param puDeviceID Pointer to a variable to be filled with the device identifier.
 *
 * @return One of the values described in the following table is returned. Value Description
 *   MMSYSERR_NOERROR Success. MMSYSERR_INVALHANDLE The hwi parameter specifies an invalid handle.
 *   MMSYSERR_NODRIVER No device driver is present. MMSYSERR_NOMEM Unable to allocate or lock memory.
 */
MMRESULT WINAPI waveInGetID(HWAVEIN hwi, LPUINT puDeviceID);
/**
 * This function sends messages to the waveform output device drivers.
 *
 * @param hwi Handle to the waveform-audio input device.
 * @param uMsg Message to send.
 * @param dwParam1 and dwParam2 Specifies message parameters.
 *
 * @return The value returned from the driver indicates success.
 */
MMRESULT WINAPI waveInMessage(HWAVEIN hwi, UINT uMsg, DWORD dw1, DWORD dw2);
/**
 * This function opens a specified waveform input device for recording.
 *
 * @param phwi Address filled with a handle identifying the open waveform-audio input device. Use
 *   this handle to identify the device when calling other waveform-audio input functions. This
 *   parameter can be NULL if WAVE_FORMAT_QUERY is specified for fdwOpen.
 * @param uDeviceID Identifier of the waveform-audio input device to open. It can be either a device
 *   identifier or a Handle to an open waveform-audio input device. You can use the following flag
 *   instead of a device identifier: Value Description WAVE_MAPPER The function selects a
 *   waveform-audio input device capable of recording in the specified format.
 * @param pwfx Pointer to a WAVEFORMATEX structure that identifies the desired format for recording
 *   waveform-audio data. You can free this structure immediately after waveInOpen returns.
 * @param dwCallback Specifies the address of a fixed callback function, an event handle, a handle
 *   to a window, or the identifier of a thread to be called during waveform-audio recording to
 *   process messages related to the progress of recording. If no callback function is required, this
 *   value can be zero.
 * @param dwCallbackInstance Specifies user-instance data passed to the callback mechanism. This
 *   parameter is not used with the window callback mechanism.
 * @param fdwOpen Flags for opening the device. The following values are defined: Value Description
 *   CALLBACK_EVENT The dwCallback parameter is an event handle. CALLBACK_FUNCTION The dwCallback
 *   parameter is a callback procedure address. CALLBACK_NULL No callback mechanism. This is the
 *   default setting. CALLBACK_THREAD The dwCallback parameter is a thread identifier. CALLBACK_WINDOW
 *   The dwCallback parameter is a window handle. WAVE_FORMAT_DIRECT If this flag is specified, the
 *   ACM driver does not perform conversions on the audio data. WAVE_FORMAT_QUERY The function queries
 *   the device to determine whether it supports the specified format, but it does not open the
 *   device. WAVE_MAPPED The uDeviceID parameter specifies a waveform-audio device to be mapped to by
 *   the wave mapper.
 *
 * @return One of the values described in the following table is returned. Value Description
 *   MMSYSERR_NOERROR Success. MMSYSERR_ALLOCATED Specified resource is already allocated.
 *   MMSYSERR_BADDEVICEID Specified device identifier is out of range. MMSYSERR_NODRIVER No device
 *   driver is present. MMSYSERR_NOMEM Unable to allocate or lock memory. WAVERR_BADFORMAT Attempted
 *   to open with an unsupported waveform-audio format.
 *
 * Use the waveInGetNumDevs function to determine the number of waveform-audio input devices present
 * on the system. The device identifier specified by uDeviceID varies from zero to one less than the
 * number of devices present. The WAVE_MAPPER constant can also be used as a device identifier.
 *
 * If you choose to have a window or thread receive callback information, the following messages are
 * sent to the window procedure or thread to indicate the progress of waveform-audio input:
 * MM_WIM_OPEN, MM_WIM_CLOSE, and MM_WIM_DATA.
 *
 * If you choose to have a function receive callback information, the following messages are sent to
 * the function to indicate the progress of waveform-audio input: WIM_OPEN, WIM_CLOSE, and WIM_DATA.
 */
MMRESULT WINAPI waveInOpen(LPHWAVEIN phwi, UINT uDeviceID,
    LPCWAVEFORMATEX pwfx, DWORD dwCallback, DWORD dwInstance, DWORD fdwOpen);



#endif  /* ifndef MMNOWAVE */



#ifdef __cplusplus
}                       // End of extern "C" {
#endif  // __cplusplus

#include "poppack.h"        /* Revert to default packing */

#endif // _INC_MMSYSTEM
