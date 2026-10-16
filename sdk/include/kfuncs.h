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
/**
 * This function causes a breakpoint exception to occur in the current process so that the calling
 * thread can signal the debugger and force it to take some action. If the process is not being
 * debugged, the search logic of a standard exception handler is used. In most cases, this causes
 * the calling process to terminate because of an unhandled breakpoint exception.
 *
 * @return None.
 */
_inline void DebugBreak() {
	__asm("break 1");
}

#elif defined(PPC)

void __emit(unsigned const __int32);
/**
 * This function causes a breakpoint exception to occur in the current process so that the calling
 * thread can signal the debugger and force it to take some action. If the process is not being
 * debugged, the search logic of a standard exception handler is used. In most cases, this causes
 * the calling process to terminate because of an unhandled breakpoint exception.
 *
 * @return None.
 */
_inline void DebugBreak() {
	__emit(0x0FE00016);	// "twi 31,0,0x16"
}

#elif defined(x86) || defined(_X86_)

/**
 * This function causes a breakpoint exception to occur in the current process so that the calling
 * thread can signal the debugger and force it to take some action. If the process is not being
 * debugged, the search logic of a standard exception handler is used. In most cases, this causes
 * the calling process to terminate because of an unhandled breakpoint exception.
 *
 * @return None.
 */
_inline void DebugBreak() {
	__asm int 3
}

#elif defined(SHx)

extern void __asm(const char *, ...);
/**
 * This function causes a breakpoint exception to occur in the current process so that the calling
 * thread can signal the debugger and force it to take some action. If the process is not being
 * debugged, the search logic of a standard exception handler is used. In most cases, this causes
 * the calling process to terminate because of an unhandled breakpoint exception.
 *
 * @return None.
 */
#define DebugBreak() __asm("trapa #1")

#elif defined(ARM)

void __emit(unsigned const __int32);
/**
 * This function causes a breakpoint exception to occur in the current process so that the calling
 * thread can signal the debugger and force it to take some action. If the process is not being
 * debugged, the search logic of a standard exception handler is used. In most cases, this causes
 * the calling process to terminate because of an unhandled breakpoint exception.
 *
 * @return None.
 */
#define DebugBreak() __emit(0xE6000010)

#else

/**
 * This function causes a breakpoint exception to occur in the current process so that the calling
 * thread can signal the debugger and force it to take some action. If the process is not being
 * debugged, the search logic of a standard exception handler is used. In most cases, this causes
 * the calling process to terminate because of an unhandled breakpoint exception.
 *
 * @return None.
 */
extern void DebugBreak();

#endif

#define EVENT_PULSE     1
#define EVENT_RESET     2
#define EVENT_SET       3

/**
 * This function provides a single operation that sets (to signaled) the state of the specified
 * event object and then resets it (to nonsignaled) after releasing the appropriate number of
 * waiting threads.
 *
 * @param hEvent Handle to the event object. The CreateEvent function returns this handle.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * For a manual-reset event object, all waiting threads that can be released immediately are
 * released. The function then resets the event object's state to nonsignaled and returns.
 *
 * For an auto-reset event object, the function resets the state to nonsignaled and returns after
 * releasing a single waiting thread, even if multiple threads are waiting.
 *
 * If no threads are waiting, or if no thread can be released immediately, PulseEvent simply sets
 * the event object's state to nonsignaled and returns.
 *
 * Note that for a thread using the multiple-object wait functions to wait for all specified objects
 * to be signaled, PulseEvent can set the event object's state to signaled and reset it to
 * nonsignaled without causing the wait function to return. This happens if not all of the specified
 * objects are simultaneously signaled.
 */
_inline BOOL PulseEvent(HANDLE h) {
	return EventModify(h,EVENT_PULSE);
}

/**
 * This function sets the state of the specified event object to nonsignaled.
 *
 * @param hEvent Handle to the event object. The CreateEvent function returns this handle.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * ResetEvent returns FALSE if the handle to the event object is invalid.
 *
 * The state of an event object remains nonsignaled until it is explicitly set to signaled by the
 * SetEvent or PulseEvent function. This nonsignaled state blocks the execution of any threads that
 * have specified the event object in a call to one of the wait functions.
 *
 * The ResetEvent function is used primarily for manual-reset event objects, which must be set
 * explicitly to the nonsignaled state. Auto-reset event objects automatically change from signaled
 * to nonsignaled after a single waiting thread is released.
 */
_inline BOOL ResetEvent(HANDLE h) {
	return EventModify(h,EVENT_RESET);
}

/**
 * This function sets the state of the specified event object to signaled.
 *
 * @param hEvent Handle to the event object. The CreateEvent function returns this handle.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * The state of a manual-reset event object remains signaled until it is set explicitly to the
 * nonsignaled state by the ResetEvent function. Any number of waiting threads, or threads that
 * subsequently begin wait operations for the specified event object by calling one of the wait
 * functions, can be released while the object's state is signaled.
 *
 * The state of an auto-reset event object remains signaled until a single waiting thread is
 * released, at which time the system automatically sets the state to nonsignaled. If no threads are
 * waiting, the event object's state remains signaled.
 */
_inline BOOL SetEvent(HANDLE h) {
	return EventModify(h,EVENT_SET);
}

#ifdef _WIN32_WCE_EMULATION
/**
 * This function returns a pseudohandle for the current thread.
 *
 * @return A pseudohandle for the current thread indicates success.
 *
 * A pseudohandle is a special constant that is interpreted as the current thread handle. The
 * calling thread can use this handle to specify itself whenever a thread handle is required.
 *
 * This handle has the maximum possible access to the thread object.
 *
 * The function cannot be used by one thread to create a handle that can be used by other threads to
 * refer to the first thread. The handle is always interpreted as referring to the thread that is
 * using it. A thread can create a "real" handle to itself that can be used by other threads, or
 * inherited by other processes, by specifying the pseudohandle as the source handle in a call to
 * the DuplicateHandle function.
 *
 * The pseudohandle need not be closed when it is no longer needed. Calling the CloseHandle function
 * with this handle has no effect.
 */
HANDLE WINAPI GetCurrentThread(void);
/**
 * This function returns a pseudohandle for the current process.
 *
 * @return A pseudohandle to the current process indicates success.
 *
 * A pseudohandle is a special constant that is interpreted as the current process handle. The
 * calling process can use this handle to specify its own process whenever a process handle is
 * required.
 *
 * This handle has the maximum possible access to the process object. A process can also use the
 * OpenProcess function to open a real handle to itself.
 *
 * The pseudohandle need not be closed when it is no longer needed. Calling the CloseHandle function
 * with a pseudohandle has no effect.
 */
HANDLE WINAPI GetCurrentProcess(void);
/**
 * This function returns the thread identifier, which is used as a handle of the calling thread.
 *
 * @return The thread identifier of the calling thread indicates success.
 *
 * Until the thread terminates, the thread identifier uniquely identifies the thread throughout the
 * system. This identifier is also the handle of the thread.
 */
DWORD WINAPI GetCurrentThreadId(void);
/**
 * This function returns the process identifier of the calling process.
 *
 * @return The identifier of the calling process indicates success.
 *
 * Until the process terminates, the process identifier uniquely identifies the process throughout
 * the system. In Windows CE, the processor identifier returned from this function is the same as
 * the process handle.
 */
DWORD WINAPI GetCurrentProcessId(void);
#else  // _WIN32_WCE_EMULATION
/**
 * This function returns a pseudohandle for the current thread.
 *
 * @return A pseudohandle for the current thread indicates success.
 *
 * A pseudohandle is a special constant that is interpreted as the current thread handle. The
 * calling thread can use this handle to specify itself whenever a thread handle is required.
 *
 * This handle has the maximum possible access to the thread object.
 *
 * The function cannot be used by one thread to create a handle that can be used by other threads to
 * refer to the first thread. The handle is always interpreted as referring to the thread that is
 * using it. A thread can create a "real" handle to itself that can be used by other threads, or
 * inherited by other processes, by specifying the pseudohandle as the source handle in a call to
 * the DuplicateHandle function.
 *
 * The pseudohandle need not be closed when it is no longer needed. Calling the CloseHandle function
 * with this handle has no effect.
 */
_inline HANDLE GetCurrentThread(void) {
	return ((HANDLE)(SH_CURTHREAD+SYS_HANDLE_BASE));
}

/**
 * This function returns a pseudohandle for the current process.
 *
 * @return A pseudohandle to the current process indicates success.
 *
 * A pseudohandle is a special constant that is interpreted as the current process handle. The
 * calling process can use this handle to specify its own process whenever a process handle is
 * required.
 *
 * This handle has the maximum possible access to the process object. A process can also use the
 * OpenProcess function to open a real handle to itself.
 *
 * The pseudohandle need not be closed when it is no longer needed. Calling the CloseHandle function
 * with a pseudohandle has no effect.
 */
_inline HANDLE GetCurrentProcess(void) {
	return ((HANDLE)(SH_CURPROC+SYS_HANDLE_BASE));
}

/**
 * This function returns the thread identifier, which is used as a handle of the calling thread.
 *
 * @return The thread identifier of the calling thread indicates success.
 *
 * Until the thread terminates, the thread identifier uniquely identifies the thread throughout the
 * system. This identifier is also the handle of the thread.
 */
_inline DWORD GetCurrentThreadId(void) {
	return ((DWORD)(((HANDLE *)(PUserKData+SYSHANDLE_OFFSET))[SH_CURTHREAD]));
}

/**
 * This function returns the process identifier of the calling process.
 *
 * @return The identifier of the calling process indicates success.
 *
 * Until the process terminates, the process identifier uniquely identifies the process throughout
 * the system. In Windows CE, the processor identifier returned from this function is the same as
 * the process handle.
 */
_inline DWORD GetCurrentProcessId(void) {
	return ((DWORD)(((HANDLE *)(PUserKData+SYSHANDLE_OFFSET))[SH_CURPROC]));
}
#endif  // _WIN32_WCE_EMULATION

#define TLS_FUNCALLOC   0
#define TLS_FUNCFREE    1

#ifndef TlsCall
DWORD WINAPI TlsCall(DWORD p1, DWORD p2);
#endif

/**
 * This function allocates a thread local storage (TLS) index. Any thread of the process can
 * subsequently use this index to store and retrieve values that are local to the thread.
 *
 * @return A TLS index indicates success. 0xFFFFFFFF indicates failure. To get extended error
 *   information, call GetLastError.
 *
 * The threads of the process can use the TLS index in subsequent calls to the TlsFree, TlsSetValue,
 * or TlsGetValue functions.
 *
 * TLS indexes are typically allocated during process or dynamic-link library (DLL) initialization.
 * Once allocated, each thread of the process can use a TLS index to access its own TLS storage
 * slot. To store a value in its slot, a thread specifies the index in a call to TlsSetValue. The
 * thread specifies the same index in a subsequent call to TlsGetValue, to retrieve the stored
 * value.
 *
 * The constant TLS_MINIMUM_AVAILABLE defines the minimum number of TLS indexes available in each
 * process. This minimum is guaranteed to be at least 64 for all systems.
 *
 * TLS indexes are not valid across process boundaries. A DLL cannot assume that an index assigned
 * in one process is valid in another process.
 *
 * A DLL might use TlsAlloc, TlsSetValue, TlsGetValue, and TlsFree as follows:
 *
 * When a DLL attaches to a process, the DLL uses TlsAlloc to allocate a TLS index. The DLL then
 * allocates some dynamic storage and uses the TLS index in a call to TlsSetValue to store the
 * address in the TLS slot. This concludes the per-thread initialization for the initial thread of
 * the process. The TLS index is stored in a global or static variable of the DLL.
 *
 * Each time the DLL attaches to a new thread of the process, the DLL allocates some dynamic storage
 * for the new thread and uses the TLS index in a call to TlsSetValue to store the address in the
 * TLS slot. This concludes the per-thread initialization for the new thread.
 *
 * Each time an initialized thread makes a DLL call requiring the data in its dynamic storage, the
 * DLL uses the TLS index in a call to TlsGetValue to retrieve the address of the dynamic storage
 * for that thread.
 *
 * For additional information on thread local storage, see Writing Memory-Efficient Applications.
 */
_inline DWORD WINAPI TlsAlloc(void) {
	return TlsCall(TLS_FUNCALLOC, 0);
}

/**
 * This function releases a thread local storage (TLS) index, making it available for reuse.
 *
 * @param dwTlsIndex Specifies a TLS index that was allocated by the TlsAlloc function.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * If the threads of the process have allocated dynamic storage and used the TLS index to store
 * pointers to this storage, they should free the storage before calling TlsFree. The TlsFree
 * function does not free any dynamic storage that has been associated with the TLS index. It is
 * expected that DLLs call this function (if at all) only during their process detach routine.
 *
 * For a brief discussion of typical uses of the TLS functions, see the Remarks section of the
 * TlsAlloc function.
 */
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

