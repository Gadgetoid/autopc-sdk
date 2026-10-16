/*****************************************************************************\
*                                                                             *
* CPM.h -  Critical Process Monitor                                           *
*                                                                             *
*               Version 1.00                                                  *
*                                                                             *
*               Copyright (c) 1997, Microsoft Corp.  All rights reserved      *
*                                                                             *
******************************************************************************/

#include <windows.h>

#ifndef _CPM_H_
#define _CPM_H_

// recover options
#define CPM_RELAUNCH            		0x00000001			// wants to be relaunched if process is not responding
#define CPM_SYS_REBOOT          		0x00000002			// wants the system reboot if process is not responding
#define	CPM_SYS_REBOOT_DEFERRED			0x00000004			// wants the system to reboot with the next power cycle

// relaunch fail options, this must be used with CPM_RELAUNCH.
#define CPM_RELAUNCH_FAIL_OK			0x00000000			// if relaunch fails, system takes no more action
#define CPM_RELAUNCH_FAIL_SYSREBOOT		0x00000001			// if relaunch fails, system will reboot.
#define CPM_RELAUNCH_FAIL_INCFAILCOUNT	0x00000002			// if relaunch fails, system will increment the count of failed processes

// callback command codes
#define CPM_CLEANUP						0x00000001			// before the system kills not responding process, if will try to callback

#ifdef __cplusplus
extern "C" {
#endif

// callback function
typedef void (*PCPMCallback)(DWORD dwCommand, DWORD dwCmdInfo);

// a process register with CPM to be a critical process
BOOL CPMRegister(
    IN DWORD dwProcessId,                         // process Id
    IN DWORD dwNotifyInterval,                    // the time interval of two notifies to CPM, in unit of milliseconds
    IN DWORD dwRecoverFlags,                      // recover option
    IN WCHAR *pCommandLine,                       // NULL terminated string (unicode) to relaunch the app (required if relaunch wanted)
    IN PCPMCallback pfnCPMCallBack,               // the call back function pointer(optional)
    IN DWORD dwRecoverFailFlags);                 // how to handle relaunch failure

BOOL CPMUnRegister(IN DWORD dwProcessId);         // Unregister with CPM
BOOL CPMNotify(IN DWORD dwProcessId);             // say hello to CPM

#ifdef __cplusplus
}
#endif

#endif // _CPM_H_
