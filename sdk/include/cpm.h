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
/**
 * This function registers a critical process.
 *
 * @param dwProcessId [in] Specifies the process identifier.
 * @param dwNotifyInterval [in] Specifies how often, in milliseconds, the application should notify
 *   the critical process monitor that it is still functioning.
 * @param dwRecoverFlags [in] Specifies what kind of actions the critical process monitor should
 *   take to recover the process. It is the following flag. - CPM_RELAUNCH: The critical process needs
 *   to relaunch the process if the process is not responding.
 * @param pCommandLine [in] Pointer to the command line Unicode string that launches the process.
 * @param pfnCPMCallBack [in] Pointer to a callback function within the calling process.
 * @param dwRecoverFailFlags [in] Specifies that actions should be taken if recovery failed. It is
 *   the following flag. - CPM_RELAUNCH_FAIL_OK: No action is taken.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * Only a process that is essential for the proper operation of the Auto PC should call this
 * function. The process must call CPMNotify at a rate at least as frequent as the notification
 * interval that the process passes to CPMRegister. The process must also define the callback
 * function that the process registers by calling CPMRegister,
 */
BOOL CPMRegister(
    IN DWORD dwProcessId,                         // process Id
    IN DWORD dwNotifyInterval,                    // the time interval of two notifies to CPM, in unit of milliseconds
    IN DWORD dwRecoverFlags,                      // recover option
    IN WCHAR *pCommandLine,                       // NULL terminated string (unicode) to relaunch the app (required if relaunch wanted)
    IN PCPMCallback pfnCPMCallBack,               // the call back function pointer(optional)
    IN DWORD dwRecoverFailFlags);                 // how to handle relaunch failure

/**
 * This function unregisters a process with the Critical Process Manager.
 *
 * @param dwProcessId [in] Specifies the process identifier.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * A process that registers with the critical process monitor by calling CPMRegister should call
 * CPMUnRegister when the process is no longer critical to the proper operation of the Auto PC.
 */
BOOL CPMUnRegister(IN DWORD dwProcessId);         // Unregister with CPM
/**
 * This function notifies the critical process monitor that the process is still functioning
 * normally.
 *
 * @param dwProcessID [in] Specifies the process identifier.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * CPMNotify must be called by the process at a rate at least as frequent as the notification
 * interval that was registered with CPMRegister. If the critical process monitor does not receive a
 * notification within the registered time limit, the critical process monitor assumes that the
 * process has encountered a fault condition and takes the appropriate action, according to the
 * monitoring option that the process registered. The only monitoring option currently available is
 * CPM_RELAUNCH.
 */
BOOL CPMNotify(IN DWORD dwProcessId);             // say hello to CPM

#ifdef __cplusplus
}
#endif

#endif // _CPM_H_
