/*++

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.
Copyright (c) 1995, 1996, 1997  Microsoft Corporation

Module Name:  

notify.h

Abstract:  

Notes: 



--*/

#ifndef _NOTIFY_H_
#define _NOTIFY_H_

/*
 * Parameters to the CeRunAppAtEvent() API.
 */

#define NOTIFICATION_EVENT_NONE                 0
#define NOTIFICATION_EVENT_TIME_CHANGE          1
#define NOTIFICATION_EVENT_SYNC_END             2
#define NOTIFICATION_EVENT_ON_AC_POWER          3
#define NOTIFICATION_EVENT_OFF_AC_POWER         4
#define NOTIFICATION_EVENT_NET_CONNECT          5
#define NOTIFICATION_EVENT_NET_DISCONNECT       6
#define NOTIFICATION_EVENT_DEVICE_CHANGE        7
#define NOTIFICATION_EVENT_IR_DISCOVERED        8
#define NOTIFICATION_EVENT_RS232_DETECTED       9
#define NOTIFICATION_EVENT_RESTORE_END         10

/*
 * String passed on the command line when an app is run as the result
 * of a call to CeRunAppAtTime().
 */

#define APP_RUN_AT_TIME                 TEXT("AppRunAtTime")

/*
 * Prefix of the command line when the user requests to run the application
 * that "owns" a notification.  It is followed by a space, and the
 * stringized version of the notification handle.
 */

#define APP_RUN_TO_HANDLE_NOTIFICATION  TEXT("AppRunToHandleNotification")

/*
 * Strings passed on the command line when an event occurs that the
 * app has requested via CeRunAppAtEvent.  Note that some of these
 * strings will be used as the command line *prefix*, since the rest
 * of the command line will be used as a parameter.
 */

#define APP_RUN_AFTER_TIME_CHANGE       TEXT("AppRunAfterTimeChange")
#define APP_RUN_AFTER_SYNC              TEXT("AppRunAfterSync")
#define APP_RUN_AT_AC_POWER_ON          TEXT("AppRunAtAcPowerOn")
#define APP_RUN_AT_AC_POWER_OFF         TEXT("AppRunAtAcPowerOff")
#define APP_RUN_AT_NET_CONNECT          TEXT("AppRunAtNetConnect")
#define APP_RUN_AT_NET_DISCONNECT       TEXT("AppRunAtNetDisconnect")
#define APP_RUN_AT_DEVICE_CHANGE        TEXT("AppRunDeviceChange")
#define APP_RUN_AT_IR_DISCOVERY         TEXT("AppRunAtIrDiscovery")
#define APP_RUN_AT_RS232_DETECT         TEXT("AppRunAtRs232Detect")
#define APP_RUN_AFTER_RESTORE           TEXT("AppRunAfterRestore")

/*
 * Strings passed on the end of the command line for the event,
 * NOTIFICATION_EVENT_DEVICE_CHANGE.  The general form will be
 * "/op devicename" for instance "/ADD COM2:"
 */
#define NOTIFY_DEVICE_ADD               TEXT("/ADD")
#define NOTIFY_DEVICE_REMOVE            TEXT("/REMOVE")

/**
 * This structure contains information used to initialize the user notifications settings dialog
 * box, and receives the user's notification preferences entered by way of the dialog box. Also used
 * when setting a user notification.
 *
 * The CE_USER_NOTIFICATION structure is passed in the CeGetUserNotificationPreferences function.
 * Initial settings are used to populate the dialog box. If the function returns TRUE, the returned
 * settings should be saved, and considered when calling CeSetUserNotification. Settings for
 * hardware not on the current device will be ignored.
 *
 * It is also used when calling CeSetUserNotification, to describe what should happen when the
 * notification time is reached.
 */
typedef struct UserNotificationType {
    /**
     * Specifies the action to take when a notification event occurs. It can be a combination of the
     * following flags: Value Description PUN_LED Flashes the LED. PUN_VIBRATE Vibrates the device.
     * PUN_DIALOG Displays the user notification dialog box. When this structure is passed to the
     * CeSetUserNotification function, the pwszDialogTitle and pwszDialogText members must provide the
     * title and text of the dialog box. PUN_SOUND Plays the sound specified by the pwszSound member.
     * When passed to PSVN, the pwszSound member must provide the name of the sound file. PUN_REPEAT
     * Repeats the pwszSound for 10-15 seconds. Only valid if PUN_SOUND is set.
     *
     * Any flag that is not valid on the current hardware platform is ignored.
     */
    DWORD ActionFlags;
#define PUN_LED     1
#define PUN_VIBRATE 2
#define PUN_DIALOG  4
#define PUN_SOUND   8
#define PUN_REPEAT 16
    /**
     * Pointer to the string that contains the title of the user notification dialog box. If this member
     * is NULL, no dialog is displayed. The CeGetUserNotificationPreferences function ignores this
     * member.
     */
    TCHAR *pwszDialogTitle;
    /**
     * Pointer to the string that contains the text of the user notification dialog box. If this member
     * is NULL, no dialog is displayed. The CeGetUserNotificationPreferences function ignores this
     * member.
     */
    TCHAR *pwszDialogText;
    /**
     * Pointer to a buffer that contains the unqualified name of a sound file to play. This member is
     * ignored if the ActionFlags member does not include the PUN_SOUND flag.
     */
    TCHAR *pwszSound;
    /**
     * Specifies the maximum length of the string that the CeGetUserNotificationPreferences function can
     * copy into the pwszSound buffer. Because the string may be a path name in a future release, the
     * buffer must be at least the length derived by the following expression: PATH_MAX * sizeof(TCHAR).
     * This member is ignored by the CeSetUserNotification function.
     */
    DWORD nMaxSound;
    /**
     * Reserved; set to zero.
     */
    DWORD dwReserved;
} CE_USER_NOTIFICATION, *PCE_USER_NOTIFICATION;

/* Declarations of User Notification APIs. */

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

/**
 * This function creates a new user notification or modifies an existing one.
 *
 * @param hNotification [in] Handle to the notification to overwrite, or zero to add a new
 *   notification.
 * @param pwszAppName [in] Pointer to a null-terminated string that specifies the name of the
 *   application that owns this notification. The system uses the application's primary icon as the
 *   taskbar annunciator for the notification. The user can start the application by selecting the
 *   annunciator.
 * @param lpTime [in] Long pointer to the SYSTEMTIME structure that specifies the time when the
 *   notification should occur.
 * @param lpUserNotification [in] Long pointer to the CE_USER_NOTIFICATION structure that describes
 *   the events that are to occur when the notification time is reached.
 *
 * @return The handle to the notification indicates success. Zero indicates failure.
 *
 * The notification occurs at the specified time, without starting the application. The application
 * can specify the notification options, including whether to light the LED, generate a sound, or
 * display a dialog box. However, an application typically uses the CeGetUserNotificationPreferences
 * function to allow the user to set the notification options.
 *
 * The user can start the owning application after the notification occurs. In this case, the system
 * starts a new instance of the application using the APP_RUN_TO_HANDLE_NOTIFICATION string as the
 * prefix of the command line and the notification handle (converted to a string) as the postfix. If
 * another instance of the application is already running, the new instance must pass a private
 * message to the old instance and then shut down.
 *
 * To delete a notification, use the handle returned by CeSetUserNotification in a call to
 * CeClearUserNotification. To overwrite a notification, use the returned handle in another call to
 * CeSetUserNotification.
 */
HANDLE CeSetUserNotification (HANDLE hNotification, TCHAR *pwszAppName, SYSTEMTIME *lpTime, PCE_USER_NOTIFICATION lpUserNotification);

/**
 * This function deletes a registered user notification that was created by a previous call to the
 * CeSetUserNotification function. CeClearUserNotification does not operate on notifications that
 * have occurred.
 *
 * @param hNotification [in] Handle to the user notification to delete.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * When writing applications for Windows CE version 1.0, use the PegClearUserNotification function.
 */
BOOL CeClearUserNotification (HANDLE hNotification);

/**
 * This function prompts the system to start running a specified application at a specified time.
 *
 * @param pwszAppName [in] Pointer to a null-terminated string that specifies the name of the
 *   application to be run.
 * @param lpTime [in] Long pointer to a SYSTEMTIME structure that specifies the time when the given
 *   application is to be run. If this parameter is NULL, the existing run request is deleted and no
 *   new request is entered. The deleted run request must have been initiated by a call to
 *   CeRunAppAtTime.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * Calling the CeRunAppAtTime function replaces any previous run request for the specified
 * application.
 *
 * The system passes the APP_RUN_AT_TIME string to the application as the command line. If an
 * instance of the application is already running, the new instance must send a private message to
 * the existing instance and then shut down.
 *
 * Use CeRunAppAtTime sparingly because automatically starting an application can confuse the user
 * and cause low-memory conditions on a machine with restricted memory. Ideally, the application
 * should be small and non-intrusive.
 */
BOOL CeRunAppAtTime (TCHAR *pwszAppName, SYSTEMTIME *lpTime);

/**
 * This function starts running an application when a specified event occurs.
 *
 * @param pwszAppName [in] Pointer to a null-terminated string that specifies the name of the
 *   application to be started.
 * @param lWhichEvent [in] Event at which the application is to be started. It is one of the
 *   following values: Value Description NOTIFICATION_EVENT_NONE No events-remove all event
 *   registrations for this application. NOTIFICATION_EVENT_SYNC_END When data synchronization
 *   finishes. NOTIFICATION_EVENT_DEVICE_CHANGE When a PC Card device is changed.
 *   NOTIFICATION_EVENT_RS232_DETECTED When an RS232 connection is made.
 *   NOTIFICATION_EVENT_TIME_CHANGE When the system time is changed. NOTIFICATION_EVENT_RESTORE_END
 *   When a full device data restore completes.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * The application is started with a system-defined command line. If there was already an instance
 * of the application running, the new instance must send a private message to the existing instance
 * and then shut down. The command line, which corresponds to the registered event, can be one of
 * the following string constants.
 *
 * Constant Value APP_RUN_AFTER_SYNC "AppRunAfterSync" APP_RUN_AT_AC_POWER_ON "AppRunAtAcPowerOn"
 * APP_RUN_AT_AC_POWER_OFF "AppRunAtAcPowerOff" APP_RUN_AT_NET_CONNECT "AppRunAtNetConnect"
 * APP_RUN_AT_NET_DISCONNECT "AppRunAtNetDisconnect" APP_RUN_AT_DEVICE_CHANGE "AppRunDeviceChange"
 * APP_RUN_AT_IR_DISCOVERY "AppRunAtIrDiscovery" APP_RUN_AT_RS232_DETECT "AppRunAtRs232Detect"
 * APP_RUN_AFTER_RESTORE "AppRunAfterRestore"
 *
 * The string values in this table are processed as command line commands. In some cases, the part
 * of the command line that follows the string is treated as a parameter.
 *
 * Use the CeRunAppAtEvent function sparingly, because automatically starting an application can
 * confuse the user and cause low-memory conditions on a machine with restricted memory. Ideally,
 * the application should be small and non-intrusive.
 *
 * The following constants are defined in the header file, but they are not supported:
 *
 * NOTIFICATION_EVENT_IR_DISCOVERED NOTIFICATION_EVENT_NET_CONNECT NOTIFICATION_EVENT_NET_DISCONNECT
 * NOTIFICATION_EVENT_OFF_AC_POWER NOTIFICATION_EVENT_ON_AC_POWER
 */
BOOL CeRunAppAtEvent(TCHAR *pwszAppName, LONG lWhichEvent);

/**
 * This function marks as "handled" all notifications previously registered by the given application
 * that have occurred. CeHandleAppNotifications turns off the sound and LED and stops vibration (if
 * they were on), and removes the taskbar annunciator.
 *
 * @param pwszAppName [in] Pointer to a null-terminated string that specifies the name of the
 *   application whose events are to be marked as "handled". This must be the name that was passed in
 *   to CeSetUserNotification as the owner of the notification.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
BOOL CeHandleAppNotifications (TCHAR *pwszAppName);

/**
 * This function queries the user for notification settings by displaying a dialog box showing
 * options that are valid for the current hardware platform.
 *
 * @return TRUE indicates success. FALSE indicates failure or that the user did not change the
 *   settings.
 *
 * If the function returns TRUE, the settings returned in the CE_USER_NOTIFICATION structure should
 * be saved and considered when calling CeSetUserNotification.
 */
BOOL CeGetUserNotificationPreferences (HWND hWndParent, PCE_USER_NOTIFICATION lpNotification);

#ifdef __cplusplus
}
#endif  //__cplusplus

#endif /* _NOTIFY_H_ */
