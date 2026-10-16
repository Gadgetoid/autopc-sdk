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

typedef struct UserNotificationType {
    DWORD ActionFlags;
#define PUN_LED     1
#define PUN_VIBRATE 2
#define PUN_DIALOG  4
#define PUN_SOUND   8
#define PUN_REPEAT 16
    TCHAR *pwszDialogTitle;
    TCHAR *pwszDialogText;
    TCHAR *pwszSound;
    DWORD nMaxSound;
    DWORD dwReserved;
} CE_USER_NOTIFICATION, *PCE_USER_NOTIFICATION;

/* Declarations of User Notification APIs. */

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

HANDLE CeSetUserNotification (HANDLE hNotification, TCHAR *pwszAppName, SYSTEMTIME *lpTime, PCE_USER_NOTIFICATION lpUserNotification);

BOOL CeClearUserNotification (HANDLE hNotification);

BOOL CeRunAppAtTime (TCHAR *pwszAppName, SYSTEMTIME *lpTime);

BOOL CeRunAppAtEvent(TCHAR *pwszAppName, LONG lWhichEvent);

BOOL CeHandleAppNotifications (TCHAR *pwszAppName);

BOOL CeGetUserNotificationPreferences (HWND hWndParent, PCE_USER_NOTIFICATION lpNotification);

#ifdef __cplusplus
}
#endif  //__cplusplus

#endif /* _NOTIFY_H_ */
