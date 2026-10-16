
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c)  1998 Microsoft Corporation

Module Name:

    ApcHal.h

    Contains the definitions for public HAL operations.

+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


#ifndef APCHAL_H
#define APCHAL_H

// These entries must be supported by AutoPC HAL's and must equate to these exact numbers
// as these constants are exported to application software that are not part of the platform
// directory.

// Each event entry is logged with a subsystem identifyer
#define LOG_SUBSYSTEM_HAL                   0x1
#define LOG_SUBSYSTEM_CPM                   0x2
#define LOG_SUBSYSTEM_OS                    0x3
#define LOG_SUBSYSTEM_SPEECH                0x4
#define LOG_SUBSYSTEM_AUDIO                 0x5
#define LOG_SUBSYSTEM_PNAPI                 0x6
#define LOG_SUBSYSTEM_VIO                   0x7
#define LOG_SUBSYSTEM_DRIVER                0x8
#define LOG_SUBSYSTEM_POWERMGMT             0x9
#define LOG_SUBSYSTEM_SHELL                 0xA
#define LOG_SUBSYSTEM_FORMMGR               0xB
#define LOG_SUBSYSTEM_WIRELESS              0xC
#define LOG_SUBSYSTEM_APPLICATION           0xD
// Entries 0 - 0x7FFF are reserved for Microsoft
// ISV's may define values in the range of 0x8000-0xFFFF
#define LOG_SUBSYSTEM_USER                  0x8000

// Each log entry needs an event classification
#define LOG_EVENT_FATAL_APPLICATION_ERROR   0x0
#define LOG_EVENT_UNHANDLED_EXCEPTION       0x1
#define LOG_EVENT_HANDLED_EXCEPTION         0x2
#define LOG_EVENT_APP_NOT_RESPONDING        0x3
#define LOG_EVENT_PSL_NOT_RESPONDING        0x4
#define LOG_EVENT_WARM_RESTART_REQUESTED    0x5
#define LOG_EVENT_WARM_RESTART_FORCED       0x6
#define LOG_EVENT_COLD_RESTART_REQUESTED    0x7
#define LOG_EVENT_COLD_RESTART_FORCED       0x8
#define LOG_EVENT_UNEXPECTED_CONDIITON      0x9
#define LOG_EVENT_HARDWARE_FAILURE          0xa
#define LOG_EVENT_MISSED_INTERRUPT          0xb
// Entries 0 - 0x7FFF are reserved for Microsoft
// ISV's may define values in the range of 0x8000-0xFFFF
#define LOG_EVENT_USER                      0xb

#define MAKELOGEVENT(subsystem, event)      ((DWORD)(subsystem << 16 | event))
#define LOGSUBSYSTEM(eventclass)            ((DWORD)((eventclass >> 16) & 0xFFFF))
#define LOGEVENT(eventclass)                ((DWORD)(eventclass & 0xFFFF))
#define WriteSystemEventLog(szMsg, cbMsg, subsystem, event) KernelIoControl(IOCTL_HAL_WRITE_LOG, szMsg, cbMsg, NULL, MAKELOGEVENT(subsystem, event), NULL)
#define ReadSystemEventLog(szOut, cbOut, pLogEntry, pcbOut) KernelIoControl(IOCTL_HAL_READ_LOG, pLogEntry, 0, szOut, cbOut, pcbOut)
#define ClearSystemEventLog() KernelIoControl(IOCTL_HAL_CLEAR_LOG, 0, 0, 0, 0, 0)
#define GetSystemEventLogInfo(pInfo) KernelIoControl(IOCTL_HAL_GET_LOG_INFO, pInfo, 0, 0, 0, 0)

// KernelIoControl(IOCTL_HAL_WRITE_LOG, szMessage, cbMessage, NULL, MAKELOGEVENT(subsystem, event), NULL);
// Writes a message to a circular log..  Max size of 2K per entry.
#define CBMSGLOGMAX                     2048
#define IOCTL_HAL_WRITE_LOG             5760    /* Write an entry to the exception log */

// Use this data structure for the IOCTL_HAL_READ_LOG IOCtl.
/**
 * This structure contains information about events whose entries have been logged.
 */
typedef struct
{
    /**
     * Control word used by log reading to maintain position information.
     */
    DWORD       LogEntry;       // Control word used by log reading to maintain position info.
    /**
     * Specifies the sequence identifier.
     */
    DWORD       dwSequenceId;   // Sequence identifier
    /**
     * Time entry was logged.
     */
    FILETIME    EntryTime;      // Time entry was logged
    /**
     * Specifies subsystem and event class information.
     */
    DWORD       dwEventClass;   // Subsystem and Event Class information
    /**
     * Boolean that is set to TRUE if there is more data to be entered, or to FALSE if none exists.
     */
    BOOL        bFinalEntryData;// Indicates if there is more data for entry

} LOGENTRYINFO, *PLOGENTRYINFO;

// KernelIoControl(IOCTL_HAL_READ_LOG, PLOGENTRYINFO, 0, szOutbuffer, cbOutbuffer, &cbDataSize)
// lpInBuf == PLOGENTRYINFO	pEntryInfo
// lpBytesReturned == pdwDataSize
// nOutBufSize == dwBufferSize
// lpOutBuf == pBuffer

#define IOCTL_HAL_READ_LOG              5761    /* Read an entry from the log */

// KernelIoControl(IOCTL_HAL_CLEAR_LOG, 0, 0, 0, 0, 0)

#define IOCTL_HAL_CLEAR_LOG             5762    /* clear the event log */

// use this structure for the IOCTL_HAL_GET_LOG_INFO 
typedef struct
{
	int iSize;				// sizeof structure (calling function fills this in)
	int iTotalLogs;			// total number of logs since last reset
	int iAvailableLogs;		// number of available logs in buffer
	int iMaxLogs;			// number of logging slots in the event log
} EVENTLOG_INFO, *PEVENTLOG_INFO;

// KernelIoControl(IOCTL_HAL_GET_LOG_INFO, PEVENTLOG_INFO, 0, 0, 0, 0)
// lpInBuf == PEVENTLOG_INFO	pLogInfo

#define IOCTL_HAL_GET_LOG_INFO          5764

// Determine what mode of operation the system is running in.
// There are special boot modes used when doing backup and restore
// or other special OEM defined states.  A value of 0 means that the system
// has normally booted.
// KernelIoControl(IOCTL_HAL_GETBOOTMODE, NULL, 0, &dwBootMode, sizeof(DWORD), NULL);

#define IOCTL_HAL_GETBOOTMODE           63      /* Obtain the mode of operationg during boot */

// Gets the physical address of the flag which contains the bootup power mode.
// KernelIoControl(IOCTL_HAL_GET_POWERMODEFLAGS_ADDRESS, NULL, 0, &dwFlags, sizeof(DWORD));
#define IOCTL_HAL_GET_POWERMODEFLAGS_ADDRESS 5765 /* Get Power mode flag address */
#define IOCTL_HAL_GET_POWERMODEFLAGS 5766 /* Get Power mode flag */
#define IOCTL_HAL_SET_POWERMODEFLAGS 5767 /* Set Power mode flag */

#endif
