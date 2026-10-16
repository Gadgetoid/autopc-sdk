/*++

Copyright (c) 1995  Microsoft Corporation

Module Name: kfuncs.h

++*/

#ifndef __KFUNCS_H__
#define __KFUNCS_H__

#define NUM_SYS_HANDLES  32

#define SYS_HANDLE_BASE	 64
#define SH_WIN32                0
#define SH_CURTHREAD            1
#define SH_CURPROC              2
#define SH_KWIN32               3       // Direct kernel win32 calls

#define SH_LAST_NOTIFY			16	// Last set notified on Thread/Process Termination
#define SH_GDI                  16
#define SH_WMGR                 17
#define SH_INIT                 18
#define SH_COMM                 19      // Communications not "COM"
#define SH_FILESYS_APIS			20      // File system APIS
#define SH_SHELL                21
#define SH_DEVMGR_APIS			22		// File system device manager
#define SH_TAPI					23
#define SH_PATCHER				24
#define SH_IMM					25
#define SH_WNET					26      // WNet APIs for network redirector

#ifdef WINCEOEM
#include <psyscall.h>    // change to include only defines required by OEMs
#endif

#if defined(ARM)
#define PUserKData ((LPBYTE)0xFFFFC800)
#else
#define PUserKData ((LPBYTE)0x00005800)
#endif
#define SYSHANDLE_OFFSET 0x004

#ifdef WINCEOEM
#include <pkfuncs.h>    // change to include only defines required by OEMs
#ifdef WINCEMACRO
#include <mkfuncs.h>
#endif
#endif

#ifndef EventModify
BOOL WINAPI EventModify(HANDLE hEvent, DWORD func);
#endif

#if defined(MIPS)

extern void __asm(char[], ...);
_inline void DebugBreak() {
	__asm("break 1");
}

#elif defined(PPC)

void __emit(unsigned const __int32);
_inline void DebugBreak() {
	__emit(0x0FE00016);	// "twi 31,0,0x16"
}

#elif defined(x86) || defined(_X86_)

_inline void DebugBreak() {
	__asm int 3
}

#elif defined(SHx)

extern void __asm(const char *, ...);
#define DebugBreak() __asm("trapa #1")

#elif defined(ARM)

void __emit(unsigned const __int32);
#define DebugBreak() __emit(0xE6000010)

#else

extern void DebugBreak();

#endif

#define EVENT_PULSE     1
#define EVENT_RESET     2
#define EVENT_SET       3

_inline BOOL PulseEvent(HANDLE h) {
	return EventModify(h,EVENT_PULSE);
}

_inline BOOL ResetEvent(HANDLE h) {
	return EventModify(h,EVENT_RESET);
}

_inline BOOL SetEvent(HANDLE h) {
	return EventModify(h,EVENT_SET);
}

#ifdef _WIN32_WCE_EMULATION
HANDLE WINAPI GetCurrentThread(void);
HANDLE WINAPI GetCurrentProcess(void);
DWORD WINAPI GetCurrentThreadId(void);
DWORD WINAPI GetCurrentProcessId(void);
#else  // _WIN32_WCE_EMULATION
_inline HANDLE GetCurrentThread(void) {
	return ((HANDLE)(SH_CURTHREAD+SYS_HANDLE_BASE));
}

_inline HANDLE GetCurrentProcess(void) {
	return ((HANDLE)(SH_CURPROC+SYS_HANDLE_BASE));
}

_inline DWORD GetCurrentThreadId(void) {
	return ((DWORD)(((HANDLE *)(PUserKData+SYSHANDLE_OFFSET))[SH_CURTHREAD]));
}

_inline DWORD GetCurrentProcessId(void) {
	return ((DWORD)(((HANDLE *)(PUserKData+SYSHANDLE_OFFSET))[SH_CURPROC]));
}
#endif  // _WIN32_WCE_EMULATION

#define TLS_FUNCALLOC   0
#define TLS_FUNCFREE    1

#ifndef TlsCall
DWORD WINAPI TlsCall(DWORD p1, DWORD p2);
#endif

_inline DWORD WINAPI TlsAlloc(void) {
	return TlsCall(TLS_FUNCALLOC, 0);
}

_inline BOOL WINAPI TlsFree(DWORD dwTlsIndex) {
	return TlsCall(TLS_FUNCFREE, dwTlsIndex);
}

#define VERIFY_READ_FLAG    0
#define VERIFY_EXECUTE_FLAG 0
#define VERIFY_WRITE_FLAG   1
#define VERIFY_KERNEL_OK    2

_inline LPVOID LockResource(HGLOBAL hResData) {
	return ((LPVOID)hResData);
}


#endif

