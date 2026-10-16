/*++

Copyright (c) 1998  Microsoft Corporation

Module Name: ApcMsg.h

Purpose: Master message include for AutoPC specific messages

--*/

#ifndef _APCMSG_H_
#define _APCMSG_H_

/*++

    Application Notes for AutoPC developers
    =======================================

    When programming for the Microsoft AutoPC platform based on Windows CE
    application developers must not use the message range 0xB000 through
    0xBFFF.  This range is reserved in its entirety for AutoPC specific
    messages.  This range is part of the WM_APP range in desktop Win32
    platforms.
    
    Messages that are private to a window class may be defined in the WM_USER
    range (0x0400 through 0x7FFF inclusive).
    
    Messages which are private to an application may be defined in the lower
    part of the WM_APP range (0x8000 through 0xAFFF inclusive).
    
    Messages that are to be shared between applications or processes must be
    defined using the RegisterWindowMessage() API.

--*/

#define APC_MSG_START   0xB000

// 0x000 - 0xCFF - 3328 messages available

#define APC_SYS_START   (APC_MSG_START + 0xD00)     // 256 system messages
#define APC_SYS_END     (APC_MSG_START + 0xDFF)

// 0xE00 - 0xE2F - 48 messages available

#define APC_CPL_START   (APC_MSG_START + 0xE30)     // 16 control pannel messages
#define APC_CPL_END     (APC_MSG_START + 0xE3F)

#define APC_IR_START    (APC_MSG_START + 0xE40)     // 16 Infrared messages
#define APC_IR_END      (APC_MSG_START + 0xE4F)

#define APC_COMM_START  (APC_MSG_START + 0xE50)     // 16 Comm related messages
#define APC_COMM_END    (APC_MSG_START + 0xE5F)

// e60 - e7f unsued

#define APC_SPCH_START  (APC_MSG_START + 0xE80)     // 64 Speech messages
#define APC_SPCH_END    (APC_MSG_START + 0xEBF)

#define APC_AUD_START   (APC_MSG_START + 0xEC0)     // 64 Audio messages
#define APC_AUD_END     (APC_MSG_START + 0xEFF)

#define APC_FRM_START   (APC_MSG_START + 0xF00)     // 256 Forms Manager messages
#define APC_FRM_END     (APC_MSG_START + 0xFFF)

#define APC_MSG_END     (APC_MSG_START + 0xFFF)


/*++
    AutoPC Settings changed Notifications
    =======================================

    The AutoPC provides several system components that are extensions to the
    core WinCE system. The configuration settings for these components are 
    set and read through the AutoPC APIs specific to each individual subsystem. 
    When the Control Panel modifies an APC system setting which necessitates a 
    notification for running applications it will broadcast a WM_SETTINGCHANGE
    message to all running applications.
    The wParam for the APC specific notifications will be one of the values 
    defined here. The AutoPC specific SPI_SETAPCXXXX values posted in the 
    WM_SETTINGCHANGE notification message will are not valid to pass to the 
    core WinCE SystemParametersInfo API. An application which needs to take 
    action on an APC setting change should check for the WM_SETTINGCHANGE 
    message on the application message sink and then call the appropriate 
    subsystem API directly to retrieve the new value for the setting.
    The lParam posted with an APC system WM_SETTINGCHANGE will always be NULL
    
--*/

#define SPI_SETAPCSHELL         0x000100100
#define SPI_SETAPCSCREENSAVER   0x000100102
#define SPI_SETAPCAUDIO         0x000100104
#define SPI_SETAPCLOCALE        0x000100106
#define SPI_SETAPCFEEDBACK      0x000100108
#define SPI_SETAPCGLOBALGRAMMAR 0x00010010a

/*++
    AutoPC Broadcast notification messges
    =======================================

--*/

/*++
    WM_APCSYSMSG_MEDIASTATECHANGE
    =============================
--*/

/**
 * This message is sent when the state of a media device changes.
 *
 * @param wParam The high-order word contains the media type. It is one of the following values:
 *   Media type Value APC_MEDIATYPE_CD 1 The low-order word contains the notification flags. It may be
 *   a combination of the following values: Notification flag Value APC_FLAG_MEDIAINSERT 0x0001
 *   APC_FLAG_MEDIAHASAUDIO 0x0010 APC_FLAG_MEDIAHASDATA 0x0020
 * @param lParam The high-order word contains the device generating the notification. It is one of
 *   the following values: Device generating notification Value APC_MEDIADEVICE_DASHCD 0
 *   APC_MEDIADEVICE_CHANGER1 1 APC_MEDIADEVICE_CHANGER2 2 APC_MEDIADEVICE_CHANGER3 3
 *   APC_MEDIADEVICE_CHANGER4 4 The low-order word contains device-specific information.
 */
#define     WM_APCSYSMSG_MEDIASTATECHANGE           (APC_SYS_START + 4)

// Media type - Passed in HIWORD of wParam

#define     APC_MEDIATYPE_CD            1

// Notification flags - Passed in LOWORD of wParam

#define     APC_FLG_MEDIAINSERT         0x0001
#define     APC_FLG_MEDIAHASAUDIO       0x0010
#define     APC_FLG_MEDIAHASDATA        0x0020
#define     APC_FLG_MEDIAUNKNOWN        0x0040
#define		APC_FLG_MEDIAUNDETERMINED	0x0080

// Device generating notification, passed in HIWORD of lParam. The device id
// passed is the AAM audio source of the device defined in apcaudio.h

// AAM_SRC_CD                      
// AAM_SRC_CDCHANGER               

// Device specific information passed in LOWORD of lParam

/*++
    WM_APCSYSMSG_VOLUMECHANGED
    ==========================

    wParam - Rsvd.
    lParam - Rsvd.
    
    This message currently takes no parameters. It is sent when the audio
    volume changes.
--*/

/**
 * This message is sent when the audio volume changes.
 *
 * This message does not currently take parameters.
 */
#define		WM_APCSYSMSG_VOLUMECHANGED				(APC_SYS_START + 5)

/*++
    WM_APCSYSMSG_MUTE
    =================

    wParam - Rsvd
    lParam - TRUE if the audio state is changed to be muted
--*/

/**
 * This message is sent if the audio state is changed to muted or to non-muted.
 *
 * @param wParam Reserved.
 * @param lParam Set to TRUE if the audio state is changed to muted. Set to FALSE if the audio state
 *   is changed to non-muted.
 */
#define	    WM_APCSYSMSG_MUTE						(APC_SYS_START + 6)	

/*++
    WM_APCSYSMSG_POWERSTATECHANGE
    =============================

    wParam - Power Notification type
    lParam - TRUE if the power state is changed to ON
           - FALSE if the power state is changed to OFF 

    Note -  a APC_PWRNOTIFYTYPE_ELECTRICAL notificaltion is not sent when the 
            electrical power is removed, Only when it is restored
           
--*/

/**
 * This message is sent when the power is turned off or on.
 *
 * @param wParam Specifies the power notification type. It is one of the following values: Power
 *   notification type Value APC_PWRNOTIFYTYPE_USER 1 APC_PWRNOTIFYTYPE_ELECTRICAL 2
 *   APC_PWRNOTIFYTYPE_BACKUPBATTERY_LOW 3
 * @param lParam For USER and ELECTRICAL, set to TRUE if the power state is changed to ON, or to
 *   FALSE if the power state is changed to OFF. For BATTERY_LOW, HIWORD(lParam) is FALSE if the
 *   battery is low, or TRUE if the battery is not low. LOWORD(lParam) gives the zero-based index of
 *   the battery.
 *
 * An APC_PWRNOTIFYTYPE_ELECTRICAL notification is not sent when the electrical power is removed,
 * only when it is restored.
 */
#define	    WM_APCSYSMSG_POWERSTATECHANGE			(APC_SYS_START + 7)

// wParam
#define APC_PWRNOTIFYTYPE_USER          		1
#define APC_PWRNOTIFYTYPE_ELECTRICAL			2
#define APC_PWRNOTIFYTYPE_BACKUPBATTERY_LOW		3	// lParam: HIWORD: 1-good 0-lowbattery, LOWORD: Battery index (zero based)

/*++
    WM_APCSYSMSG_BACKUPNOTIFY
    =============================

    wParam - Thread Id of the backup.exe main thread (received by app)
           - 0 when posted to backup.exe (posted by app)
    lParam - Backup transaction id

    Note -  The backup.exe broadcasts this message at the beginning of the
            backup operation.  Applications should flush their data to the
            registry/file-system/object store upon receiving this message
            to ensure that it will be preserved by the backup operation.
            Applications have 5 seconds after the issuance of this message
            to complete their save operations. Any application may request
            more time in units of 5 seconds by posting the backup thread
            this message with the wParam=0, lParam=Backup transaction id.
--*/
/**
 * This message notifies an application that it should flush all its data and prepare for backup of
 * the file system, object store and registry.
 *
 * @param wParam Specifies the thread identifier of the Backup.exe received by an application, or 0
 *   when posted by the application to Backup.exe.
 * @param lParam Specifies the backup transaction identifier.
 *
 * The Backup.exe broadcasts this message at the beginning of the backup operation. Applications
 * should flush their data to the registry, file system, or object store upon receiving this message
 * to ensure that the data is preserved by the backup operation. Applications which have opened data
 * files with the DENY_READ attribute set should close the files if the files should be backed up.
 * Applications have five seconds after this message is sent to complete their save operations. Any
 * application may request more time in units of five seconds by posting this message to the backup
 * thread by setting wParam to 0.
 *
 * If an application has a data file open, it may wish to close the file on receiving this message
 * so the file will be backed up.
 */
#define	    WM_APCSYSMSG_BACKUPNOTIFY    			(APC_SYS_START + 8)


/*++
    WM_APCSYSMSG_INSTALLNOTIFY
    =============================

    wParam - 0
    lParam - 0
    
    Note -  The ApcLoad.exe broadcasts this message at the beginning of the
            install operation.  Well behaved applications should exit in
            response to this message, treating it like a WM_CLOSE.
            Applications have 5 seconds after the issuance of this message
            to complete their shutdown operations. 
--*/
/**
 * This message is sent when an install operation begins.
 *
 * ApcLoad.exe broadcasts this message at the beginning of the install operation. An application
 * should treat this message like WM_CLOSE and exit in response to this message. An application has
 * 5 seconds after the issuance of this message to shutdown completely.
 */
#define	    WM_APCSYSMSG_INSTALLNOTIFY    			(APC_SYS_START + 9)


/*++
    WM_APCSYSMSG_ASSISTEVENT
    =============================

    Broadcast by an OEM installed driver when an Assist level event occurs.
    
    wParam - HIWORD Severity level
    wParam - LOWORD Rsvd
    lParam - Rsvd
--*/

/**
 * This message is sent when an assist level event occurs.
 *
 * @param wParam The high-order word contains the severity level for the assist event. The low-order
 *   word is reserved.
 * @param lParam Reserved.
 *
 * This message is broadcast by a driver installed by an original equipment manufacturer (OEM).
 */
#define	    WM_APCSYSMSG_ASSISTEVENT    			(APC_SYS_START + 10)

// Current defines for HIWORD( wParam)

#define     APC_ASSISTSEVERITY_CRITICAL             1
#define     APC_ASSISTSEVERITY_USER         		2

//=====================================================================
// APC Communications messages

/*++
    WM_APCCOMM_DIALSTATECHANGED
    =================

    Broadcast by internal TAPI Thread through app sink to ABAPI forms

    wParam - New dialing state
    lParam - Previous state result
--*/

/**
 * This message is sent internally to notify address book forms that the dialing state changed.
 *
 * @param wParam Specifies the new dialing state
 * @param lParam Specifies the result obtained from the previous dialing state.
 *
 * This message is broadcast through the application sink to forms managed by the address book
 * application programming interface (ABAPI) by the internal telephony API (TAPI) thread.
 */
#define	    WM_APCCOMM_DIALSTATECHANGED			(APC_COMM_START + 0)	




#endif // _APCMSG_H_

