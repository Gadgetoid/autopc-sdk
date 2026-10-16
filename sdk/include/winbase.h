
/*++

Copyright (c) 1995 - 1997 Microsoft Corporation

Module Name: winbase.h

Purpose:This header file declares the Base APIs.

--*/

#ifndef __WINBASE_H__
#define __WINBASE_H__

//
// Define API decoration for direct importing of DLL references.
//

#if !defined(_ADVAPI32_)
#define WINADVAPI  DECLSPEC_IMPORT
#else
#define WINADVAPI
#endif

#if !defined(_KERNEL32_)
#define WINBASEAPI DECLSPEC_IMPORT
#else
#define WINBASEAPI
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <windef.h>

#define INVALID_HANDLE_VALUE (HANDLE)-1
#define INVALID_FILE_SIZE (DWORD)0xFFFFFFFF

#define FILE_BEGIN           0
#define FILE_CURRENT         1
#define FILE_END             2
//
//  File System time stamps are represented with the following structure:
//

/**
 * This structure is a 64-bit value representing the number of 100-nanosecond intervals since
 * January 1, 1601.
 *
 * The FILETIME data structure is used in the time conversion functions between MS-DOS and Win32.
 */
typedef struct _FILETIME {
    /**
     * Specifies the low 32 bits of the Win32 date/time value.
     */
    DWORD dwLowDateTime;
    /**
     * Specifies the upper 32 bits of the Win32 date/time value.
     */
    DWORD dwHighDateTime;
} FILETIME, *PFILETIME, *LPFILETIME;

/**
 * This structure represents a date and time using individual members for the month, day, year,
 * weekday, hour, minute, second, and millisecond.
 *
 * It is not recommended that you add and subtract values from the SYSTEMTIME structure to obtain
 * relative times. Instead, you should
 *
 * Convert the SYSTEMTIME structure to a FILETIME structure.
 *
 * Copy the resulting FILETIME structure to a ULARGE_INTEGER structure.
 *
 * Use normal 64-bit arithmetic on the ULARGE_INTEGER value.
 */
typedef struct _SYSTEMTIME {
    /**
     * Specifies the current year.
     */
    WORD wYear;
    /**
     * Specifies the current month; January = 1, February = 2, and so on.
     */
    WORD wMonth;
    /**
     * Specifies the current day of the week; Sunday = 0, Monday = 1, and so on.
     */
    WORD wDayOfWeek;
    /**
     * Specifies the current day of the month.
     */
    WORD wDay;
    /**
     * Specifies the current hour.
     */
    WORD wHour;
    /**
     * Specifies the current minute.
     */
    WORD wMinute;
    /**
     * Specifies the current second.
     */
    WORD wSecond;
    /**
     * Specifies the current millisecond.
     */
    WORD wMilliseconds;
} SYSTEMTIME, *LPSYSTEMTIME;

#ifdef MIPS_R4000 /* or above */

/**
 * This function both increments (increases by one) the value of the specified 32-bit variable and
 * checks the resulting value. InterlockedIncrement prevents more than one thread from using the
 * InterlockedDecrement or InterlockedIncrement function to access the same variable simultaneously.
 *
 * @param lpAddend [in] Pointer to the LONG variable to increment.
 *
 * @return The return value is the resulting incremented value.
 *
 * The functions InterlockedIncrement, InterlockedCompareExchange, InterlockedDecrement,
 * InterlockedExchange, and InterlockedExchangeAdd provide a simple mechanism for synchronizing
 * access to a variable that is shared by multiple threads. The threads of different processes can
 * use this mechanism if the variable is in shared memory.
 *
 * The variable pointed to by the lpAddend parameter must be aligned on a 32-bit boundary.
 */
#define InterlockedIncrement _InterlockedIncrement
/**
 * This function both decrements (decreases by one) the value of the specified 32-bit variable and
 * checks the resulting value. InterlockedDecrement prevents more than one thread from using the
 * InterlockedDecrement or InterlockedIncrement function to access the same variable simultaneously.
 *
 * @param lpAddend [in] Pointer to the 32-bit variable to decrement.
 *
 * @return The return value is the resulting decremented value.
 *
 * The functions InterlockedDecrement, InterlockedCompareExchange, InterlockedExchange,
 * InterlockedExchangeAdd, and InterlockedIncrement provide a simple mechanism for synchronizing
 * access to a variable that is shared by multiple threads. The threads of different processes can
 * use this mechanism if the variable is in shared memory.
 *
 * The variable pointed to by the lpAddend parameter must be aligned on a 32-bit boundary.
 */
#define InterlockedDecrement _InterlockedDecrement
/**
 * This function atomically exchanges a pair of 32-bit values.
 *
 * @param Target [in] Pointer to the LONG value to exchange. The function sets this LONG value to
 *   Value, and returns its prior value.
 * @param Value [in] Specifies a new value for the LONG value pointed to by Target.
 *
 * @return The prior value of the LONG value pointed to by Target indicates success.
 *
 * The functions InterlockedExchange, InterlockedCompareExchange, InterlockedDecrement,
 * InterlockedExchangeAdd, and InterlockedIncrement provide a simple mechanism for synchronizing
 * access to a variable that is shared by multiple threads. The threads of different processes can
 * use this mechanism if the variable is in shared memory.
 *
 * The variable pointed to by the Target parameter must be aligned on a 32-bit boundary; otherwise,
 * this function will fail on multiprocessor x86 systems.
 */
#define InterlockedExchange _InterlockedExchange

/**
 * This function both increments (increases by one) the value of the specified 32-bit variable and
 * checks the resulting value. InterlockedIncrement prevents more than one thread from using the
 * InterlockedDecrement or InterlockedIncrement function to access the same variable simultaneously.
 *
 * @param lpAddend [in] Pointer to the LONG variable to increment.
 *
 * @return The return value is the resulting incremented value.
 *
 * The functions InterlockedIncrement, InterlockedCompareExchange, InterlockedDecrement,
 * InterlockedExchange, and InterlockedExchangeAdd provide a simple mechanism for synchronizing
 * access to a variable that is shared by multiple threads. The threads of different processes can
 * use this mechanism if the variable is in shared memory.
 *
 * The variable pointed to by the lpAddend parameter must be aligned on a 32-bit boundary.
 */
LONG
WINAPI
InterlockedIncrement(
    LPLONG lpAddend
    );

/**
 * This function both decrements (decreases by one) the value of the specified 32-bit variable and
 * checks the resulting value. InterlockedDecrement prevents more than one thread from using the
 * InterlockedDecrement or InterlockedIncrement function to access the same variable simultaneously.
 *
 * @param lpAddend [in] Pointer to the 32-bit variable to decrement.
 *
 * @return The return value is the resulting decremented value.
 *
 * The functions InterlockedDecrement, InterlockedCompareExchange, InterlockedExchange,
 * InterlockedExchangeAdd, and InterlockedIncrement provide a simple mechanism for synchronizing
 * access to a variable that is shared by multiple threads. The threads of different processes can
 * use this mechanism if the variable is in shared memory.
 *
 * The variable pointed to by the lpAddend parameter must be aligned on a 32-bit boundary.
 */
LONG
WINAPI
InterlockedDecrement(
    LPLONG lpAddend
    );

/**
 * This function atomically exchanges a pair of 32-bit values.
 *
 * @param Target [in] Pointer to the LONG value to exchange. The function sets this LONG value to
 *   Value, and returns its prior value.
 * @param Value [in] Specifies a new value for the LONG value pointed to by Target.
 *
 * @return The prior value of the LONG value pointed to by Target indicates success.
 *
 * The functions InterlockedExchange, InterlockedCompareExchange, InterlockedDecrement,
 * InterlockedExchangeAdd, and InterlockedIncrement provide a simple mechanism for synchronizing
 * access to a variable that is shared by multiple threads. The threads of different processes can
 * use this mechanism if the variable is in shared memory.
 *
 * The variable pointed to by the Target parameter must be aligned on a 32-bit boundary; otherwise,
 * this function will fail on multiprocessor x86 systems.
 */
LONG
WINAPI
InterlockedExchange(
    LPLONG Target,
    LONG Value
    );

#pragma intrinsic(_InterlockedIncrement)
#pragma intrinsic(_InterlockedDecrement)
#pragma intrinsic(_InterlockedExchange)

#elif (defined(PPC) && _MSC_VER >= 1000) && !defined(RC_INVOKED)

/**
 * This function both increments (increases by one) the value of the specified 32-bit variable and
 * checks the resulting value. InterlockedIncrement prevents more than one thread from using the
 * InterlockedDecrement or InterlockedIncrement function to access the same variable simultaneously.
 *
 * @param lpAddend [in] Pointer to the LONG variable to increment.
 *
 * @return The return value is the resulting incremented value.
 *
 * The functions InterlockedIncrement, InterlockedCompareExchange, InterlockedDecrement,
 * InterlockedExchange, and InterlockedExchangeAdd provide a simple mechanism for synchronizing
 * access to a variable that is shared by multiple threads. The threads of different processes can
 * use this mechanism if the variable is in shared memory.
 *
 * The variable pointed to by the lpAddend parameter must be aligned on a 32-bit boundary.
 */
#define InterlockedIncrement _InterlockedIncrement
/**
 * This function both decrements (decreases by one) the value of the specified 32-bit variable and
 * checks the resulting value. InterlockedDecrement prevents more than one thread from using the
 * InterlockedDecrement or InterlockedIncrement function to access the same variable simultaneously.
 *
 * @param lpAddend [in] Pointer to the 32-bit variable to decrement.
 *
 * @return The return value is the resulting decremented value.
 *
 * The functions InterlockedDecrement, InterlockedCompareExchange, InterlockedExchange,
 * InterlockedExchangeAdd, and InterlockedIncrement provide a simple mechanism for synchronizing
 * access to a variable that is shared by multiple threads. The threads of different processes can
 * use this mechanism if the variable is in shared memory.
 *
 * The variable pointed to by the lpAddend parameter must be aligned on a 32-bit boundary.
 */
#define InterlockedDecrement _InterlockedDecrement
/**
 * This function atomically exchanges a pair of 32-bit values.
 *
 * @param Target [in] Pointer to the LONG value to exchange. The function sets this LONG value to
 *   Value, and returns its prior value.
 * @param Value [in] Specifies a new value for the LONG value pointed to by Target.
 *
 * @return The prior value of the LONG value pointed to by Target indicates success.
 *
 * The functions InterlockedExchange, InterlockedCompareExchange, InterlockedDecrement,
 * InterlockedExchangeAdd, and InterlockedIncrement provide a simple mechanism for synchronizing
 * access to a variable that is shared by multiple threads. The threads of different processes can
 * use this mechanism if the variable is in shared memory.
 *
 * The variable pointed to by the Target parameter must be aligned on a 32-bit boundary; otherwise,
 * this function will fail on multiprocessor x86 systems.
 */
#define InterlockedExchange _InterlockedExchange
#define InterlockedExchangeAdd _InterlockedExchangeAdd
#define InterlockedCompareExchange _InterlockedCompareExchange

/**
 * This function both increments (increases by one) the value of the specified 32-bit variable and
 * checks the resulting value. InterlockedIncrement prevents more than one thread from using the
 * InterlockedDecrement or InterlockedIncrement function to access the same variable simultaneously.
 *
 * @param lpAddend [in] Pointer to the LONG variable to increment.
 *
 * @return The return value is the resulting incremented value.
 *
 * The functions InterlockedIncrement, InterlockedCompareExchange, InterlockedDecrement,
 * InterlockedExchange, and InterlockedExchangeAdd provide a simple mechanism for synchronizing
 * access to a variable that is shared by multiple threads. The threads of different processes can
 * use this mechanism if the variable is in shared memory.
 *
 * The variable pointed to by the lpAddend parameter must be aligned on a 32-bit boundary.
 */
LONG
WINAPI
InterlockedIncrement(
    LPLONG lpAddend
    );

/**
 * This function both decrements (decreases by one) the value of the specified 32-bit variable and
 * checks the resulting value. InterlockedDecrement prevents more than one thread from using the
 * InterlockedDecrement or InterlockedIncrement function to access the same variable simultaneously.
 *
 * @param lpAddend [in] Pointer to the 32-bit variable to decrement.
 *
 * @return The return value is the resulting decremented value.
 *
 * The functions InterlockedDecrement, InterlockedCompareExchange, InterlockedExchange,
 * InterlockedExchangeAdd, and InterlockedIncrement provide a simple mechanism for synchronizing
 * access to a variable that is shared by multiple threads. The threads of different processes can
 * use this mechanism if the variable is in shared memory.
 *
 * The variable pointed to by the lpAddend parameter must be aligned on a 32-bit boundary.
 */
LONG
WINAPI
InterlockedDecrement(
    LPLONG lpAddend
    );

/**
 * This function atomically exchanges a pair of 32-bit values.
 *
 * @param Target [in] Pointer to the LONG value to exchange. The function sets this LONG value to
 *   Value, and returns its prior value.
 * @param Value [in] Specifies a new value for the LONG value pointed to by Target.
 *
 * @return The prior value of the LONG value pointed to by Target indicates success.
 *
 * The functions InterlockedExchange, InterlockedCompareExchange, InterlockedDecrement,
 * InterlockedExchangeAdd, and InterlockedIncrement provide a simple mechanism for synchronizing
 * access to a variable that is shared by multiple threads. The threads of different processes can
 * use this mechanism if the variable is in shared memory.
 *
 * The variable pointed to by the Target parameter must be aligned on a 32-bit boundary; otherwise,
 * this function will fail on multiprocessor x86 systems.
 */
LONG
WINAPI
InterlockedExchange(
    LPLONG Target,
    LONG Value
    );

PVOID
WINAPI
InterlockedCompareExchange (
    PVOID *Destination,
    PVOID Exchange,
    PVOID Comperand
    );

LONG
WINAPI
InterlockedExchangeAdd(
    LPLONG Addend,
    LONG Value
    );

/**
 * This function is an interlocked function that performs a conditional setting of a variable.
 *
 * @param Target [in] Pointer to the LONG variable to check and set.
 * @param OldValue [in] Specifies the value to check against.
 * @param NewValue [in] Specifies the value to set to conditionally.
 *
 * @return The value pointed to by Target at the time of the call-that is, the old value-indicates
 *   success.
 *
 * The InterlockedTestExchange function is an interlocked function-in other words, it can be
 * considered atomic. It checks to see if the value pointed to by Target is equal to OldValue. If
 * so, it sets Target to NewValue. Since InterlockedTestExchange returns the "old" value pointed to
 * by Target, if the return value is OldValue, then InterlockedTestExchange succeeded and set the
 * value pointed to by Target to NewValue. Otherwise, it failed.
 */
#define InterlockedTestExchange(Target, oldValue, newValue) \
    ((long)InterlockedCompareExchange((PVOID*)(Target), (PVOID)(newValue), (PVOID)(oldValue)))

#pragma intrinsic(_InterlockedIncrement)
#pragma intrinsic(_InterlockedDecrement)
#pragma intrinsic(_InterlockedExchange)
#pragma intrinsic(_InterlockedCompareExchange)
#pragma intrinsic(_InterlockedExchangeAdd)

#elif defined(x86) || defined(_X86_)

#pragma warning(disable:4035)               // re-enable below

  /**
   * This function both increments (increases by one) the value of the specified 32-bit variable and
   * checks the resulting value. InterlockedIncrement prevents more than one thread from using the
   * InterlockedDecrement or InterlockedIncrement function to access the same variable simultaneously.
   *
   * @param lpAddend [in] Pointer to the LONG variable to increment.
   *
   * @return The return value is the resulting incremented value.
   *
   * The functions InterlockedIncrement, InterlockedCompareExchange, InterlockedDecrement,
   * InterlockedExchange, and InterlockedExchangeAdd provide a simple mechanism for synchronizing
   * access to a variable that is shared by multiple threads. The threads of different processes can
   * use this mechanism if the variable is in shared memory.
   *
   * The variable pointed to by the lpAddend parameter must be aligned on a 32-bit boundary.
   */
  __inline
  LONG
  WINAPI
  InterlockedIncrement(
      IN PLONG Addend
      )
  {
      __asm {
          mov     eax, 1
          mov     ecx, Addend
          xadd    [ecx], eax
          inc     eax
      }
  }

  /**
   * This function both decrements (decreases by one) the value of the specified 32-bit variable and
   * checks the resulting value. InterlockedDecrement prevents more than one thread from using the
   * InterlockedDecrement or InterlockedIncrement function to access the same variable simultaneously.
   *
   * @param lpAddend [in] Pointer to the 32-bit variable to decrement.
   *
   * @return The return value is the resulting decremented value.
   *
   * The functions InterlockedDecrement, InterlockedCompareExchange, InterlockedExchange,
   * InterlockedExchangeAdd, and InterlockedIncrement provide a simple mechanism for synchronizing
   * access to a variable that is shared by multiple threads. The threads of different processes can
   * use this mechanism if the variable is in shared memory.
   *
   * The variable pointed to by the lpAddend parameter must be aligned on a 32-bit boundary.
   */
  __inline
  LONG
  WINAPI
  InterlockedDecrement(
      IN PLONG Addend
      )
  {
      __asm {
          mov     eax, -1
          mov     ecx, Addend
          xadd    [ecx], eax
          dec     eax
      }
  }

  /**
   * This function atomically exchanges a pair of 32-bit values.
   *
   * @param Target [in] Pointer to the LONG value to exchange. The function sets this LONG value to
   *   Value, and returns its prior value.
   * @param Value [in] Specifies a new value for the LONG value pointed to by Target.
   *
   * @return The prior value of the LONG value pointed to by Target indicates success.
   *
   * The functions InterlockedExchange, InterlockedCompareExchange, InterlockedDecrement,
   * InterlockedExchangeAdd, and InterlockedIncrement provide a simple mechanism for synchronizing
   * access to a variable that is shared by multiple threads. The threads of different processes can
   * use this mechanism if the variable is in shared memory.
   *
   * The variable pointed to by the Target parameter must be aligned on a 32-bit boundary; otherwise,
   * this function will fail on multiprocessor x86 systems.
   */
  __inline
  LONG
  WINAPI
  InterlockedExchange(
      IN OUT PLONG Target,
      IN LONG Value
      )
  {
      __asm {
          mov     eax, Value
          mov     ecx, Target
          xchg 	[ecx], eax
      }
  }

  
  /**
   * This function is an interlocked function that performs a conditional setting of a variable.
   *
   * @param Target [in] Pointer to the LONG variable to check and set.
   * @param OldValue [in] Specifies the value to check against.
   * @param NewValue [in] Specifies the value to set to conditionally.
   *
   * @return The value pointed to by Target at the time of the call-that is, the old value-indicates
   *   success.
   *
   * The InterlockedTestExchange function is an interlocked function-in other words, it can be
   * considered atomic. It checks to see if the value pointed to by Target is equal to OldValue. If
   * so, it sets Target to NewValue. Since InterlockedTestExchange returns the "old" value pointed to
   * by Target, if the return value is OldValue, then InterlockedTestExchange succeeded and set the
   * value pointed to by Target to NewValue. Otherwise, it failed.
   */
  __inline
  LONG
  WINAPI
  InterlockedTestExchange(
  	LPLONG Target,
  	LONG oldValue,
  	LONG newValue
  	)
  {
      __asm {
          mov     eax, oldValue
          mov     ecx, Target
          mov     edx, newValue
          cmpxchg [ecx], edx
      }
  }

#pragma warning(default:4035)

#else

/**
 * This function both increments (increases by one) the value of the specified 32-bit variable and
 * checks the resulting value. InterlockedIncrement prevents more than one thread from using the
 * InterlockedDecrement or InterlockedIncrement function to access the same variable simultaneously.
 *
 * @param lpAddend [in] Pointer to the LONG variable to increment.
 *
 * @return The return value is the resulting incremented value.
 *
 * The functions InterlockedIncrement, InterlockedCompareExchange, InterlockedDecrement,
 * InterlockedExchange, and InterlockedExchangeAdd provide a simple mechanism for synchronizing
 * access to a variable that is shared by multiple threads. The threads of different processes can
 * use this mechanism if the variable is in shared memory.
 *
 * The variable pointed to by the lpAddend parameter must be aligned on a 32-bit boundary.
 */
LONG
WINAPI
InterlockedIncrement(
    LPLONG lpAddend
    );


/**
 * This function both decrements (decreases by one) the value of the specified 32-bit variable and
 * checks the resulting value. InterlockedDecrement prevents more than one thread from using the
 * InterlockedDecrement or InterlockedIncrement function to access the same variable simultaneously.
 *
 * @param lpAddend [in] Pointer to the 32-bit variable to decrement.
 *
 * @return The return value is the resulting decremented value.
 *
 * The functions InterlockedDecrement, InterlockedCompareExchange, InterlockedExchange,
 * InterlockedExchangeAdd, and InterlockedIncrement provide a simple mechanism for synchronizing
 * access to a variable that is shared by multiple threads. The threads of different processes can
 * use this mechanism if the variable is in shared memory.
 *
 * The variable pointed to by the lpAddend parameter must be aligned on a 32-bit boundary.
 */
LONG
WINAPI
InterlockedDecrement(
    LPLONG lpAddend
    );


/**
 * This function atomically exchanges a pair of 32-bit values.
 *
 * @param Target [in] Pointer to the LONG value to exchange. The function sets this LONG value to
 *   Value, and returns its prior value.
 * @param Value [in] Specifies a new value for the LONG value pointed to by Target.
 *
 * @return The prior value of the LONG value pointed to by Target indicates success.
 *
 * The functions InterlockedExchange, InterlockedCompareExchange, InterlockedDecrement,
 * InterlockedExchangeAdd, and InterlockedIncrement provide a simple mechanism for synchronizing
 * access to a variable that is shared by multiple threads. The threads of different processes can
 * use this mechanism if the variable is in shared memory.
 *
 * The variable pointed to by the Target parameter must be aligned on a 32-bit boundary; otherwise,
 * this function will fail on multiprocessor x86 systems.
 */
LONG
WINAPI
InterlockedExchange(
    LPLONG Target,
    LONG Value
    );

/**
 * This function is an interlocked function that performs a conditional setting of a variable.
 *
 * @param Target [in] Pointer to the LONG variable to check and set.
 * @param OldValue [in] Specifies the value to check against.
 * @param NewValue [in] Specifies the value to set to conditionally.
 *
 * @return The value pointed to by Target at the time of the call-that is, the old value-indicates
 *   success.
 *
 * The InterlockedTestExchange function is an interlocked function-in other words, it can be
 * considered atomic. It checks to see if the value pointed to by Target is equal to OldValue. If
 * so, it sets Target to NewValue. Since InterlockedTestExchange returns the "old" value pointed to
 * by Target, if the return value is OldValue, then InterlockedTestExchange succeeded and set the
 * value pointed to by Target to NewValue. Otherwise, it failed.
 */
LONG
WINAPI
InterlockedTestExchange(
	LPLONG Target,
	LONG oldValue,
	LONG newValue
	);

#endif

/**
 * This function generates a random number.
 *
 * @return A randomly generated DWORD.
 */
DWORD
WINAPI
Random();


/**
 * This function is called by the system as the initial entry point for WindowsCE-based
 * applications.
 *
 * @param hInstance [in] Handle to the current instance of the application.
 * @param hPrevInstance [in] Handle to the previous instance of the application. For a Win32-based
 *   application, this parameter is always NULL. If you need to detect whether another instance
 *   already exists, create a uniquely named mutex using the CreateMutex function. CreateMutex will
 *   succeed even if the mutex already exists, but the GetLastError function will return
 *   ERROR_ALREADY_EXISTS. This indicates that another instance of your application exists, because it
 *   created the mutex first.
 * @param lpCmdLine [in] Pointer to a null-terminated string that specifies the command line for the
 *   application, excluding the program name.
 * @param nCmdShow [in] Specifies how the window is to be shown. This parameter can be one of the
 *   following values: Value Description SW_HIDE Hides the window and activates another window.
 *   SW_SHOW Activates a window and displays it in its current size and position. SW_SHOWNA Displays a
 *   window in its current state. The active window remains active. SW_SHOWNOACTIVATE Displays a
 *   window in its most recent size and position. The active window remains active. SW_SHOWNORMAL
 *   Activates and displays a window. If the window is minimized or maximized, the system restores it
 *   to its original size and position (same as SW_RESTORE).
 *
 * @return The exit value contained in that message's wParam parameter indicates success, and that
 *   the function terminates when it receives a WM_QUIT message. Zero indicates that the function
 *   terminates before entering the message loop.
 *
 * Your WinMain should initialize the application, display its main window, and enter a message
 * retrieval-and-dispatch loop that is the top-level control structure for the remainder of the
 * application's execution. Terminate the message loop when it receives a WM_QUIT message. At that
 * point, your WinMain should exit the application, returning the value passed in the WM_QUIT
 * message's wParam parameter. If WM_QUIT was received as a result of calling PostQuitMessage, the
 * value of wParam is the value of the PostQuitMessage function's nExitCode parameter.
 */
int
WINAPI
WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
#ifdef UNDER_CE
    LPWSTR lpCmdLine,
#else
    LPSTR lpCmdLine,
#endif
    int nShowCmd
    );

/**
 * This function compares two 64-bit file times.
 *
 * @param lpFileTime1 [in] Long pointer to a FILETIME structure that specifies the first 64-bit file
 *   time.
 * @param lpFileTime2 [in] Long pointer to a FILETIME structure that specifies the second 64-bit
 *   file time.
 *
 * @return -1 indicates that the first file time is less than the second file time. 0 indicates that
 *   the first file time is equal to the second file time. +1 indicates that the first file time is
 *   greater than the second file time.
 */
LONG WINAPI CompareFileTime(const FILETIME *lpft1, const FILETIME *lpft2);
/**
 * This function converts a 64-bit file time to system time format.
 *
 * @param lpFileTime [in] Pointer to a FILETIME structure containing the file time to convert to
 *   system date and time format. The FileTimeToSystemTime function only works with FILETIME values
 *   that are less than 0x8000000000000000. The function fails with values equal to or greater than
 *   that.
 * @param lpSystemTime [out] Pointer to a SYSTEMTIME structure to receive the converted file time.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * As noted above, the function fails for FILETIME values that are equal to or greater than
 * 0x8000000000000000.
 */
BOOL WINAPI FileTimeToSystemTime(const FILETIME *lpft, LPSYSTEMTIME lpst);
/**
 * This function converts a system time to a file time.
 *
 * @param lpSystemTime [in] Pointer to a SYSTEMTIME structure that contains the time to be
 *   converted. The wDayOfWeek member of the SYSTEMTIME structure is ignored.
 * @param lpFileTime [out] Pointer to a FILETIME structure to receive the converted system time.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 */
BOOL WINAPI SystemTimeToFileTime(const SYSTEMTIME *lpst, LPFILETIME lpft);
/**
 * This function converts a file time based on the Coordinated Universal Time (UTC) to a local file
 * time.
 *
 * @param lpFileTime [in] Pointer to a FILETIME structure containing the UTC-based file time to be
 *   converted into a local file time.
 * @param lpLocalFileTime [out] Pointer to a FILETIME structure to receive the converted local file
 *   time. This parameter cannot be the same as the lpFileTime parameter.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * FileTimeToLocalFileTime uses the current settings for the time zone and daylight saving time.
 * Therefore, if it is daylight saving time, this function will take daylight saving time into
 * account, even if the time you are converting is in standard time.
 */
BOOL WINAPI FileTimeToLocalFileTime(const FILETIME *lpft, LPFILETIME lpftLocal);
/**
 * This function converts a local file time to a file time based on the Coordinated Universal Time
 * (UTC).
 *
 * @param lpLocalFileTime [in] Pointer to a FILETIME structure that specifies the local file time to
 *   be converted into a UTC-based file time.
 * @param lpFileTime [out] Pointer to a FILETIME structure to receive the converted UTC-based file
 *   time. This parameter cannot be the same as the lpLocalFileTime parameter.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * LocalFileTimeToFileTime uses the current settings for the time zone and daylight saving time.
 * Therefore, if it is daylight saving time, this function will take daylight saving time into
 * account, even if the time you are converting is in standard time.
 */
BOOL WINAPI LocalFileTimeToFileTime(const FILETIME *lpftLocal, LPFILETIME lpft);

/* Taken from NT's process.h */
/**
 * This function is an optional method of entry into a dynamic-link library (DLL). If the function
 * is used, it is called by the system when processes and threads are initialized and terminated, or
 * upon calls to the LoadLibrary and FreeLibrary functions.
 *
 * @param hinstDLL Handle to the DLL. The value is the base address of the DLL. The HINSTANCE of a
 *   DLL is the same as the HMODULE of the DLL, so hinstDLL can be used in subsequent calls to the
 *   GetModuleFileName function and other functions that require a module handle.
 * @param dwReason Specifies a flag indicating why the DLL entry-point function is being called.
 *   This parameter can be one of the following values: Value Description DLL_PROCESS_ATTACH Indicates
 *   that the DLL is being loaded into the virtual address space of the current process as a result of
 *   the process starting up or as a result of a call to LoadLibrary. DLLs can use this opportunity to
 *   initialize any instance data or to use the TlsAlloc function to allocate a thread local storage
 *   (TLS) index. DLL_THREAD_ATTACH Indicates that the current process is creating a new thread. When
 *   this occurs, the system calls the entry-point function of all DLLs currently attached to the
 *   process. The call is made in the context of the new thread. DLLs can use this opportunity to
 *   initialize a TLS slot for the thread. A thread calling the DLL entry-point function with
 *   DLL_PROCESS_ATTACH does not call the DLL entry-point function with DLL_THREAD_ATTACH. Note that
 *   the entry-point of a DLL function is called with this value only by threads created after the DLL
 *   is loaded by the process. When a DLL is loaded using LoadLibrary, existing threads do not call
 *   the entry-point function of the newly loaded DLL. DLL_THREAD_DETACH Indicates that a thread is
 *   exiting cleanly. If the DLL has stored a pointer to allocated memory in a TLS slot, it uses this
 *   opportunity to free the memory. The system calls the entry-point function of all currently loaded
 *   DLLs with this value. The call is made in the context of the exiting thread. DLL_PROCESS_DETACH
 *   Indicates that the DLL is being unloaded from the virtual address space of the calling process as
 *   a result of either a process exit or a call to FreeLibrary. The DLL can use this opportunity to
 *   call the TlsFree function to free any TLS indices allocated by using TlsAlloc and to free any
 *   thread local data.
 * @param lpvReserved Specifies further aspects of DLL initialization and cleanup. If dwReason is
 *   DLL_PROCESS_ATTACH, lpvReserved is NULL for dynamic loads and non-NULL for static loads. If
 *   dwReason is DLL_PROCESS_DETACH, lpvReserved is NULL if DllMain has been called by using
 *   FreeLibrary and non-NULL if DllMain has been called during process termination.
 *
 * @return When the system calls the DllMain function with the DLL_PROCESS_ATTACH value, the
 *   function returns TRUE if it succeeds or FALSE if initialization fails. If the return value is
 *   FALSE when DllMain is called because the process uses the LoadLibrary function, LoadLibrary
 *   returns NULL. If the return value is FALSE when DllMain is called during process initialization,
 *   the process terminates with an error. To get extended error information, call GetLastError. When
 *   the system calls the DllMain function with any value other than DLL_PROCESS_ATTACH, the return
 *   value is ignored.
 *
 * During initial process startup or after a call to LoadLibrary, the system scans the list of
 * loaded DLLs for the process. For each DLL that has not already been called with the
 * DLL_PROCESS_ATTACH value, the system calls the entry-point function of the DLL. This call is made
 * in the context of the thread that caused the process address space to change, such as the primary
 * thread of the process or the thread that called LoadLibrary.
 *
 * There are cases in which the entry-point function is called for a terminating thread even if the
 * DLL never attached to the thread - for example, the entry-point function was never called with
 * the DLL_THREAD_ATTACH value in the context of the thread in either of these two situations:
 *
 * The thread was the initial thread in the process, so the system called the entry-point function
 * with the DLL_PROCESS_ATTACH value.
 *
 * The thread was already running when a call to the LoadLibrary function was made, so the system
 * never called the entry-point function for it.
 *
 * When a DLL is unloaded from a process as a result of process termination or as a result of a call
 * to FreeLibrary, the system does not call the entry-point function of the DLL with the
 * DLL_THREAD_DETACH value for the individual threads of the process. The DLL is only given
 * DLL_PROCESS_DETACH notification. DLLs can take this opportunity to clean up all resources for all
 * threads known to the DLL.
 *
 * On attach, the body of your DLL entry-point function should perform only simple initialization
 * tasks, such as setting up thread local storage (TLS), creating synchronization objects, and
 * opening files. You must not call LoadLibrary in the entry-point function, because you may create
 * dependency loops in the DLL load order. This can result in a DLL being used before the system has
 * executed its initialization code. Similarly, you must not call the FreeLibrary function in the
 * entry-point function on detach, because this can result in a DLL being used after the system has
 * executed its termination code.
 *
 * Calling Win32 functions other than TLS, object-creation, and file functions may result in
 * problems that are difficult to diagnose. For example, calling User, Shell, COM, and Windows
 * Sockets functions (or any functions that call these functions) can cause access violation errors,
 * because their DLLs call LoadLibrary to load other system components. While it is acceptable to
 * create synchronization objects in DllMain, you should not perform synchronization in DllMain (or
 * a function called by DllMain) because all calls to DllMain are serialized. Waiting on
 * synchronization objects in DllMain can cause a deadlock.
 *
 * To provide more complex initialization, create an initialization routine for the DLL. You can
 * require applications to call the initialization routine before calling any other routines in the
 * DLL. Otherwise, you can have the initialization routine create a named mutex, and have each
 * routine in the DLL call the initialization routine if the mutex does not exist.
 */
BOOL
WINAPI
DllMain (
    HANDLE hinstDLL,
    DWORD dwReason,
    LPVOID lpvReserved
    );

#ifdef UNDER_CE
/**
 * This function returns the address of the specified exported dynamic-link library (DLL) function.
 *
 * @param hModule Handle to the DLL module that contains the function. The LoadLibrary or
 *   GetModuleHandle function returns this handle.
 * @param lpProcName Pointer to a null-terminated string containing the function name, or specifies
 *   the function's ordinal value. If this parameter is an ordinal value, it must be in the low-order
 *   word; the high-order word must be zero. The lpProcName parameter must be in Unicode.
 *
 * @return The address of the DLL's exported function indicates success. NULL indicates failure. To
 *   get extended error information, call GetLastError. When using GetProcAddress to obtain the
 *   address of the InitSecurityInterface function, use SECURITY_ENTRYPOINT for the lpProcName
 *   parameter.
 *
 * The GetProcAddress function is used to retrieve addresses of exported functions in DLLs.
 *
 * The spelling and case of the function name pointed to by lpProcName must be identical to that in
 * the EXPORTS statement of the source DLL's module-definition (.DEF) file. The exported names of
 * Win32 APIs may differ from the names you use when calling these functions in your code. This
 * difference is hidden by macros used in the SDK header files.
 *
 * The lpProcName parameter can identify the DLL function by specifying an ordinal value associated
 * with the function in the EXPORTS statement. GetProcAddress verifies that the specified ordinal is
 * in the range 1 through the highest ordinal value exported in the .DEF file. The function then
 * uses the ordinal as an index to read the function's address from a function table. If the .DEF
 * file does not number the functions consecutively from 1 to N (where N is the number of exported
 * functions), an error can occur where GetProcAddress returns an invalid, non-NULL address, even
 * though there is no function with the specified ordinal.
 *
 * In cases where the function may not exist, the function should be specified by name rather than
 * by ordinal value.
 */
#define GetProcAddress GetProcAddressW

/**
 * This function returns the address of the specified exported dynamic-link library (DLL) function.
 *
 * @param hModule Handle to the DLL module that contains the function. The LoadLibrary or
 *   GetModuleHandle function returns this handle.
 * @param lpProcName Pointer to a null-terminated string containing the function name, or specifies
 *   the function's ordinal value. If this parameter is an ordinal value, it must be in the low-order
 *   word; the high-order word must be zero. The lpProcName parameter must be in Unicode.
 *
 * @return The address of the DLL's exported function indicates success. NULL indicates failure. To
 *   get extended error information, call GetLastError. When using GetProcAddress to obtain the
 *   address of the InitSecurityInterface function, use SECURITY_ENTRYPOINT for the lpProcName
 *   parameter.
 *
 * The GetProcAddress function is used to retrieve addresses of exported functions in DLLs.
 *
 * The spelling and case of the function name pointed to by lpProcName must be identical to that in
 * the EXPORTS statement of the source DLL's module-definition (.DEF) file. The exported names of
 * Win32 APIs may differ from the names you use when calling these functions in your code. This
 * difference is hidden by macros used in the SDK header files.
 *
 * The lpProcName parameter can identify the DLL function by specifying an ordinal value associated
 * with the function in the EXPORTS statement. GetProcAddress verifies that the specified ordinal is
 * in the range 1 through the highest ordinal value exported in the .DEF file. The function then
 * uses the ordinal as an index to read the function's address from a function table. If the .DEF
 * file does not number the functions consecutively from 1 to N (where N is the number of exported
 * functions), an error can occur where GetProcAddress returns an invalid, non-NULL address, even
 * though there is no function with the specified ordinal.
 *
 * In cases where the function may not exist, the function should be specified by name rather than
 * by ordinal value.
 */
WINBASEAPI
FARPROC
WINAPI
GetProcAddressW(
    HMODULE hModule,
    LPCWSTR lpProcName
    );

#else

/**
 * This function returns the address of the specified exported dynamic-link library (DLL) function.
 *
 * @param hModule Handle to the DLL module that contains the function. The LoadLibrary or
 *   GetModuleHandle function returns this handle.
 * @param lpProcName Pointer to a null-terminated string containing the function name, or specifies
 *   the function's ordinal value. If this parameter is an ordinal value, it must be in the low-order
 *   word; the high-order word must be zero. The lpProcName parameter must be in Unicode.
 *
 * @return The address of the DLL's exported function indicates success. NULL indicates failure. To
 *   get extended error information, call GetLastError. When using GetProcAddress to obtain the
 *   address of the InitSecurityInterface function, use SECURITY_ENTRYPOINT for the lpProcName
 *   parameter.
 *
 * The GetProcAddress function is used to retrieve addresses of exported functions in DLLs.
 *
 * The spelling and case of the function name pointed to by lpProcName must be identical to that in
 * the EXPORTS statement of the source DLL's module-definition (.DEF) file. The exported names of
 * Win32 APIs may differ from the names you use when calling these functions in your code. This
 * difference is hidden by macros used in the SDK header files.
 *
 * The lpProcName parameter can identify the DLL function by specifying an ordinal value associated
 * with the function in the EXPORTS statement. GetProcAddress verifies that the specified ordinal is
 * in the range 1 through the highest ordinal value exported in the .DEF file. The function then
 * uses the ordinal as an index to read the function's address from a function table. If the .DEF
 * file does not number the functions consecutively from 1 to N (where N is the number of exported
 * functions), an error can occur where GetProcAddress returns an invalid, non-NULL address, even
 * though there is no function with the specified ordinal.
 *
 * In cases where the function may not exist, the function should be specified by name rather than
 * by ordinal value.
 */
WINBASEAPI
FARPROC
WINAPI
GetProcAddress(
    HMODULE hModule,
    LPCSTR lpProcName
    );

#endif

/**
 * This function retrieves the current local date and time.
 *
 * @param lpSystemTime [out] Pointer to a SYSTEMTIME structure to receive the current local date and
 *   time.
 *
 * @return None.
 */
VOID
WINAPI
GetLocalTime (
    LPSYSTEMTIME lpSystemTime
    );

/**
 * This function retrieves the current system date and time. The system time is expressed in
 * Coordinated Universal Time (UTC).
 *
 * @param lpSystemTime [out] Pointer to a SYSTEMTIME structure to receive the current system date
 *   and time.
 *
 * @return None.
 */
VOID
WINAPI
GetSystemTime (
    LPSYSTEMTIME lpSystemTime
    );

/**
 * This structure specifies information specific to the time zone.
 */
typedef struct _TIME_ZONE_INFORMATION {
    /**
     * Specifies the current bias, in minutes, for local time translation on this computer. The bias is
     * the difference, in minutes, between Coordinated Universal Time (UTC) and local time. All
     * translations between UTC and local time are based on the following formula:
     *
     *     UTC = local time + bias
     *
     * This member is required.
     */
    LONG Bias;
    /**
     * Specifies a null-terminated string associated with standard time on this operating system. For
     * example, this member could contain "EST" to indicate Eastern Standard Time. This string is not
     * used by the operating system, so anything stored there by using the SetTimeZoneInformation
     * function is returned unchanged by the GetTimeZoneInformation function. This string can be empty.
     */
    WCHAR StandardName[ 32 ];
    /**
     * Specifies a SYSTEMTIME structure that contains a date and local time when the transition from
     * daylight time to standard time occurs on this operating system. If this date is not specified,
     * the wMonth member in the SYSTEMTIME structure must be zero. If this date is specified, the
     * DaylightDate value in the TIME_ZONE_INFORMATION structure must also be specified.
     *
     * This member supports two date formats. Absolute format specifies an exact date and time when
     * standard time begins. In this form, the wYear, wMonth, wDay, wHour, wMinute, wSecond, and
     * wMilliseconds members of the SYSTEMTIME structure are used to specify an exact date.
     *
     * Day-in-month format is specified by setting the wYear member to zero, setting the wDayOfWeek
     * member to an appropriate weekday, and using a wDay value in the range 1 through 5 to select the
     * correct day in the month. Using this notation, the first Sunday in April can be specified, as can
     * the last Thursday in October (5 is equal to "the last").
     */
    SYSTEMTIME StandardDate;
    /**
     * Specifies a bias value to be used during local time translations that occur during standard time.
     * This member is ignored if a value for the StandardDate member is not supplied.
     *
     * This value is added to the value of the Bias member to form the bias used during standard time.
     * In most time zones, the value of this member is zero.
     */
    LONG StandardBias;
    /**
     * Specifies a null-terminated string associated with daylight time on this operating system. For
     * example, this member could contain "PDT" to indicate Pacific Daylight Time. This string is not
     * used by the operating system, so anything stored there by using the SetTimeZoneInformation
     * function is returned unchanged by the GetTimeZoneInformation function. This string can be empty.
     */
    WCHAR DaylightName[ 32 ];
    /**
     * Specifies a SYSTEMTIME structure that contains a date and local time when the transition from
     * standard time to daylight time occurs on this operating system. If this date is not specified,
     * the wMonth member in the SYSTEMTIME structure must be zero. If this date is specified, the
     * StandardDate value in the TIME_ZONE_INFORMATION structure must also be specified. This member
     * supports the absolute and day-in-month time formats described for the StandardDate member.
     */
    SYSTEMTIME DaylightDate;
    /**
     * Specifies a bias value to be used during local time translations that occur during daylight time.
     * This member is ignored if a value for the DaylightDate member is not supplied.
     *
     * This value is added to the value of the Bias member to form the bias used during daylight time.
     * In most time zones, the value of this member is -60.
     */
    LONG DaylightBias;
} TIME_ZONE_INFORMATION, *LPTIME_ZONE_INFORMATION;

/**
 * This function retrieves the current time-zone parameters. These parameters control the
 * translations between Coordinated Universal Time (UTC) and local time.
 *
 * @param lpTimeZoneInformation [out] Pointer to a TIME_ZONE_INFORMATION structure to receive the
 *   current time-zone parameters.
 *
 * @return If the function succeeds, the return value is one of the following values: -
 *   TIME_ZONE_ID_UNKNOWN: The system cannot determine the current time zone. This error is also
 *   returned if you call the SetTimeZoneInformation function and supply the bias values but no
 *   transition dates. This value is returned if daylight savings time is not used in the current time
 *   zone, because there are no transition dates. - TIME_ZONE_ID_STANDARD: The system is operating in
 *   the range covered by the StandardDate member of the TIME_ZONE_INFORMATION structure. -
 *   TIME_ZONE_ID_DAYLIGHT: The system is operating in the range covered by the DaylightDate member of
 *   the TIME_ZONE_INFORMATION structure. If the function fails, the return value is
 *   TIME_ZONE_ID_INVALID. To get extended error information, call GetLastError. Prior to Windows
 *   version 2.10, a known problem caused this function to always return TIME_ZONE_ID_UNKNOWN.
 *
 * All translations between UTC time and local time are based on the following formula:
 *
 *     UTC = local time + bias
 *
 * The bias is the difference, in minutes, between UTC time and local time.
 */
DWORD
WINAPI
GetTimeZoneInformation (
    LPTIME_ZONE_INFORMATION lpTimeZoneInformation
    );

/**
 * This function sets the current local time and date.
 *
 * @param lpSystemTime [in] Pointer to a SYSTEMTIME structure that contains the current local date
 *   and time. The wDayOfWeek member of the SYSTEMTIME structure is ignored.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 */
BOOL
WINAPI
SetLocalTime (
    CONST SYSTEMTIME *lpSystemTime
    );

/**
 * This function sets the current system time and date. The system time is expressed in Coordinated
 * Universal Time (UTC).
 *
 * @param lpSystemTime [in] Pointer to a SYSTEMTIME structure that contains the current system date
 *   and time. The wDayOfWeek member of the SYSTEMTIME structure is ignored.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 */
BOOL
WINAPI
SetSystemTime (
    CONST SYSTEMTIME *lpSystemTime
    );

/**
 * This function sets the current state of daylight savings time.
 *
 * @param dst Integer that indicates whether or not day light savings time is in effect. A value of
 *   1 indicates that daylight savings time is in effect; a value of 0 indicates that standard time is
 *   in effect.
 *
 * @return None.
 *
 * Windows CE does not automatically correct the time to account for daylight savings time. To
 * enable Windows CE to correctly calculate the time, call this function with dst set to 1 when
 * daylight savings time begins; call it with dst set to 0 when it ends.
 */
void
WINAPI
SetDaylightTime (
	DWORD dst
	);

/**
 * This function sets the current time-zone parameters. These parameters control translations from
 * Coordinated Universal Time (UTC) to local time.
 *
 * @param lpTimeZoneInformation [in] Pointer to a TIME_ZONE_INFORMATION structure that contains the
 *   time-zone parameters to set.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * All translations between UTC and local time are based on the following formula:
 *
 *     UTC = local time + bias
 *
 * The bias is the difference, in minutes, between UTC and local time.
 */
BOOL
WINAPI
SetTimeZoneInformation (
    CONST TIME_ZONE_INFORMATION *lpTimeZoneInformation
    );

WINBASEAPI
LPSTR
WINAPI
lstrcatA(
    LPSTR lpString1,
    LPCSTR lpString2
    );

#define lstrcatW wcscat
#ifdef UNICODE
#define lstrcat lstrcatW
#else
#define lstrcat lstrcatA
#endif

WINBASEAPI
int
WINAPI
lstrcmpA(
    LPCSTR lpString1,
    LPCSTR lpString2
    );
WINBASEAPI
int
WINAPI
lstrcmpW(
    LPCWSTR lpString1,
    LPCWSTR lpString2
    );
#ifdef UNICODE
#define lstrcmp  lstrcmpW
#else
#define lstrcmp  lstrcmpA
#endif // !UNICODE

WINBASEAPI
int
WINAPI
lstrcmpiA(
    LPCSTR lpString1,
    LPCSTR lpString2
    );
WINBASEAPI
int
WINAPI
lstrcmpiW(
    LPCWSTR lpString1,
    LPCWSTR lpString2
    );
#ifdef UNICODE
#define lstrcmpi  lstrcmpiW
#else
#define lstrcmpi  lstrcmpiA
#endif // !UNICODE

WINBASEAPI
LPSTR
WINAPI
lstrcpyA(
    LPSTR lpString1,
    LPCSTR lpString2
    );
#define lstrcpyW wcscpy
#ifdef UNICODE
#define lstrcpy lstrcpyW
#else
#define lstrcpy lstrcpyA
#endif

WINBASEAPI
int
WINAPI
lstrlenA(
    LPCSTR lpString
    );
#define lstrlenW wcslen
#ifdef UNICODE
#define lstrlen lstrlenW
#else
#define lstrlen lstrlenA
#endif

/**
 * This function converts uppercase characters in a buffer to lowercase characters. The function
 * converts the characters in place.
 *
 * @param lpsz [in] Pointer to a buffer that contains one or more characters to process.
 * @param cchLength [in] Specifies the size, in characters, of the buffer pointed to by lpsz. The
 *   function examines each character, and converts uppercase characters to lowercase characters. The
 *   function examines the number of bytes or characters indicated by cchLength, even if one or more
 *   characters are null characters.
 *
 * @return The number of characters processed indicates success. For example, if CharLowerBuff("Acme
 *   of Operating Systems", 10) succeeds, the return value is 10.
 *
 * The function makes the conversion based on the information associated with the user's default
 * locale, which is the locale selected by the user at setup or by using the Control Panel. Windows
 * CE does not have language drivers.
 *
 * Windows CE supports only the Unicode version of this function.
 */
DWORD
WINAPI
CharLowerBuffA (
    LPSTR lpsz,
    DWORD cchLength
    );
/**
 * This function converts uppercase characters in a buffer to lowercase characters. The function
 * converts the characters in place.
 *
 * @param lpsz [in] Pointer to a buffer that contains one or more characters to process.
 * @param cchLength [in] Specifies the size, in characters, of the buffer pointed to by lpsz. The
 *   function examines each character, and converts uppercase characters to lowercase characters. The
 *   function examines the number of bytes or characters indicated by cchLength, even if one or more
 *   characters are null characters.
 *
 * @return The number of characters processed indicates success. For example, if CharLowerBuff("Acme
 *   of Operating Systems", 10) succeeds, the return value is 10.
 *
 * The function makes the conversion based on the information associated with the user's default
 * locale, which is the locale selected by the user at setup or by using the Control Panel. Windows
 * CE does not have language drivers.
 *
 * Windows CE supports only the Unicode version of this function.
 */
DWORD
WINAPI
CharLowerBuffW (
    LPWSTR lpsz,
    DWORD cchLength
    );
#ifdef UNICODE
/**
 * This function converts uppercase characters in a buffer to lowercase characters. The function
 * converts the characters in place.
 *
 * @param lpsz [in] Pointer to a buffer that contains one or more characters to process.
 * @param cchLength [in] Specifies the size, in characters, of the buffer pointed to by lpsz. The
 *   function examines each character, and converts uppercase characters to lowercase characters. The
 *   function examines the number of bytes or characters indicated by cchLength, even if one or more
 *   characters are null characters.
 *
 * @return The number of characters processed indicates success. For example, if CharLowerBuff("Acme
 *   of Operating Systems", 10) succeeds, the return value is 10.
 *
 * The function makes the conversion based on the information associated with the user's default
 * locale, which is the locale selected by the user at setup or by using the Control Panel. Windows
 * CE does not have language drivers.
 *
 * Windows CE supports only the Unicode version of this function.
 */
#define CharLowerBuff CharLowerBuffW
#else
/**
 * This function converts uppercase characters in a buffer to lowercase characters. The function
 * converts the characters in place.
 *
 * @param lpsz [in] Pointer to a buffer that contains one or more characters to process.
 * @param cchLength [in] Specifies the size, in characters, of the buffer pointed to by lpsz. The
 *   function examines each character, and converts uppercase characters to lowercase characters. The
 *   function examines the number of bytes or characters indicated by cchLength, even if one or more
 *   characters are null characters.
 *
 * @return The number of characters processed indicates success. For example, if CharLowerBuff("Acme
 *   of Operating Systems", 10) succeeds, the return value is 10.
 *
 * The function makes the conversion based on the information associated with the user's default
 * locale, which is the locale selected by the user at setup or by using the Control Panel. Windows
 * CE does not have language drivers.
 *
 * Windows CE supports only the Unicode version of this function.
 */
#define CharLowerBuff CharLowerBuffA
#endif

/**
 * This function converts lowercase characters in a buffer to uppercase characters. The function
 * converts the characters in place.
 *
 * @param lpsz [in] Pointer to a buffer that contains one or more characters to process.
 * @param cchLength [in] Specifies the size, in characters, of the buffer pointed to by lpsz. The
 *   function examines each character, and converts lowercase characters to uppercase characters. The
 *   function examines the number of characters indicated by cchLength, even if one or more characters
 *   are null characters.
 *
 * @return The number of characters processed indicates success. For example, if
 *   CharUpperBuff("Zenith of API Sets", 10) succeeds, the return value is 10.
 *
 * The function makes the conversion based on the information associated with the user's default
 * locale, which is the locale selected by the user at setup or by using the Control Panel. Windows
 * CE does not have language drivers.
 *
 * Windows CE supports only the Unicode version of this function.
 */
DWORD
WINAPI
CharUpperBuffA (
    LPSTR lpsz,
    DWORD cchLength
    );
/**
 * This function converts lowercase characters in a buffer to uppercase characters. The function
 * converts the characters in place.
 *
 * @param lpsz [in] Pointer to a buffer that contains one or more characters to process.
 * @param cchLength [in] Specifies the size, in characters, of the buffer pointed to by lpsz. The
 *   function examines each character, and converts lowercase characters to uppercase characters. The
 *   function examines the number of characters indicated by cchLength, even if one or more characters
 *   are null characters.
 *
 * @return The number of characters processed indicates success. For example, if
 *   CharUpperBuff("Zenith of API Sets", 10) succeeds, the return value is 10.
 *
 * The function makes the conversion based on the information associated with the user's default
 * locale, which is the locale selected by the user at setup or by using the Control Panel. Windows
 * CE does not have language drivers.
 *
 * Windows CE supports only the Unicode version of this function.
 */
DWORD
WINAPI
CharUpperBuffW (
    LPWSTR lpsz,
    DWORD cchLength
    );
#ifdef UNICODE
/**
 * This function converts lowercase characters in a buffer to uppercase characters. The function
 * converts the characters in place.
 *
 * @param lpsz [in] Pointer to a buffer that contains one or more characters to process.
 * @param cchLength [in] Specifies the size, in characters, of the buffer pointed to by lpsz. The
 *   function examines each character, and converts lowercase characters to uppercase characters. The
 *   function examines the number of characters indicated by cchLength, even if one or more characters
 *   are null characters.
 *
 * @return The number of characters processed indicates success. For example, if
 *   CharUpperBuff("Zenith of API Sets", 10) succeeds, the return value is 10.
 *
 * The function makes the conversion based on the information associated with the user's default
 * locale, which is the locale selected by the user at setup or by using the Control Panel. Windows
 * CE does not have language drivers.
 *
 * Windows CE supports only the Unicode version of this function.
 */
#define CharUpperBuff CharUpperBuffW
#else
/**
 * This function converts lowercase characters in a buffer to uppercase characters. The function
 * converts the characters in place.
 *
 * @param lpsz [in] Pointer to a buffer that contains one or more characters to process.
 * @param cchLength [in] Specifies the size, in characters, of the buffer pointed to by lpsz. The
 *   function examines each character, and converts lowercase characters to uppercase characters. The
 *   function examines the number of characters indicated by cchLength, even if one or more characters
 *   are null characters.
 *
 * @return The number of characters processed indicates success. For example, if
 *   CharUpperBuff("Zenith of API Sets", 10) succeeds, the return value is 10.
 *
 * The function makes the conversion based on the information associated with the user's default
 * locale, which is the locale selected by the user at setup or by using the Control Panel. Windows
 * CE does not have language drivers.
 *
 * Windows CE supports only the Unicode version of this function.
 */
#define CharUpperBuff CharUpperBuffA
#endif

/**
 * This function converts a character string or a single character to lowercase. If the operand is a
 * character string, the function converts the characters in place.
 *
 * @param lpsz [in] Pointer to a null-terminated string or specifies a single character. If the
 *   high-order word of this parameter is zero, the low-order word must contain a single character to
 *   be converted.
 *
 * @return A pointer to the converted string indicates that the operand is a character string. Since
 *   the string is converted in place, the return value is equal to lpsz. A 32-bit value whose
 *   high-order word is zero and low-order word contains the converted character indicates that the
 *   operand is a single character. There is no indication of success or failure. Failure is rare.
 *   There is no extended error information for this function; do not call GetLastError.
 *
 * The function makes the conversion based on the information associated with the user's default
 * locale, which is the locale selected by the user at setup or by using the Control Panel. Windows
 * CE does not have language drivers.
 *
 * Windows CE supports only the Unicode version of this function.
 */
LPSTR WINAPI CharLowerA(LPSTR lpsz);
/**
 * This function converts a character string or a single character to lowercase. If the operand is a
 * character string, the function converts the characters in place.
 *
 * @param lpsz [in] Pointer to a null-terminated string or specifies a single character. If the
 *   high-order word of this parameter is zero, the low-order word must contain a single character to
 *   be converted.
 *
 * @return A pointer to the converted string indicates that the operand is a character string. Since
 *   the string is converted in place, the return value is equal to lpsz. A 32-bit value whose
 *   high-order word is zero and low-order word contains the converted character indicates that the
 *   operand is a single character. There is no indication of success or failure. Failure is rare.
 *   There is no extended error information for this function; do not call GetLastError.
 *
 * The function makes the conversion based on the information associated with the user's default
 * locale, which is the locale selected by the user at setup or by using the Control Panel. Windows
 * CE does not have language drivers.
 *
 * Windows CE supports only the Unicode version of this function.
 */
LPWSTR WINAPI CharLowerW(LPWSTR lpsz);

#ifdef UNICODE
/**
 * This function converts a character string or a single character to lowercase. If the operand is a
 * character string, the function converts the characters in place.
 *
 * @param lpsz [in] Pointer to a null-terminated string or specifies a single character. If the
 *   high-order word of this parameter is zero, the low-order word must contain a single character to
 *   be converted.
 *
 * @return A pointer to the converted string indicates that the operand is a character string. Since
 *   the string is converted in place, the return value is equal to lpsz. A 32-bit value whose
 *   high-order word is zero and low-order word contains the converted character indicates that the
 *   operand is a single character. There is no indication of success or failure. Failure is rare.
 *   There is no extended error information for this function; do not call GetLastError.
 *
 * The function makes the conversion based on the information associated with the user's default
 * locale, which is the locale selected by the user at setup or by using the Control Panel. Windows
 * CE does not have language drivers.
 *
 * Windows CE supports only the Unicode version of this function.
 */
#define CharLower CharLowerW
#else
/**
 * This function converts a character string or a single character to lowercase. If the operand is a
 * character string, the function converts the characters in place.
 *
 * @param lpsz [in] Pointer to a null-terminated string or specifies a single character. If the
 *   high-order word of this parameter is zero, the low-order word must contain a single character to
 *   be converted.
 *
 * @return A pointer to the converted string indicates that the operand is a character string. Since
 *   the string is converted in place, the return value is equal to lpsz. A 32-bit value whose
 *   high-order word is zero and low-order word contains the converted character indicates that the
 *   operand is a single character. There is no indication of success or failure. Failure is rare.
 *   There is no extended error information for this function; do not call GetLastError.
 *
 * The function makes the conversion based on the information associated with the user's default
 * locale, which is the locale selected by the user at setup or by using the Control Panel. Windows
 * CE does not have language drivers.
 *
 * Windows CE supports only the Unicode version of this function.
 */
#define CharLower CharLowerA
#endif

/**
 * This function converts a character string or a single character to uppercase. If the operand is a
 * character string, the function converts the characters in place.
 *
 * @param lpsz [in] Pointer to a null-terminated string or specifies a single character. If the
 *   high-order word of this parameter is zero, the low-order word must contain a single character to
 *   be converted.
 *
 * @return A pointer to the converted string indicates that the operand is a character string. Since
 *   the string is converted in place, the return value is equal to lpsz. A 32-bit value whose
 *   high-order word is zero and low-order word contains the converted character indicates that the
 *   operand is a single character. There is no indication of success or failure. Failure is rare.
 *   There is no extended error information for this function; do not call GetLastError.
 *
 * The function makes the conversion based on the information associated with the user's default
 * locale, which is the locale selected by the user at setup or by using the Control Panel. Windows
 * CE does not have language drivers.
 *
 * Windows CE supports only the Unicode version of this function.
 */
LPSTR WINAPI CharUpperA(LPSTR lpsz);
/**
 * This function converts a character string or a single character to uppercase. If the operand is a
 * character string, the function converts the characters in place.
 *
 * @param lpsz [in] Pointer to a null-terminated string or specifies a single character. If the
 *   high-order word of this parameter is zero, the low-order word must contain a single character to
 *   be converted.
 *
 * @return A pointer to the converted string indicates that the operand is a character string. Since
 *   the string is converted in place, the return value is equal to lpsz. A 32-bit value whose
 *   high-order word is zero and low-order word contains the converted character indicates that the
 *   operand is a single character. There is no indication of success or failure. Failure is rare.
 *   There is no extended error information for this function; do not call GetLastError.
 *
 * The function makes the conversion based on the information associated with the user's default
 * locale, which is the locale selected by the user at setup or by using the Control Panel. Windows
 * CE does not have language drivers.
 *
 * Windows CE supports only the Unicode version of this function.
 */
LPWSTR WINAPI CharUpperW(LPWSTR lpsz);

#ifdef UNICODE
/**
 * This function converts a character string or a single character to uppercase. If the operand is a
 * character string, the function converts the characters in place.
 *
 * @param lpsz [in] Pointer to a null-terminated string or specifies a single character. If the
 *   high-order word of this parameter is zero, the low-order word must contain a single character to
 *   be converted.
 *
 * @return A pointer to the converted string indicates that the operand is a character string. Since
 *   the string is converted in place, the return value is equal to lpsz. A 32-bit value whose
 *   high-order word is zero and low-order word contains the converted character indicates that the
 *   operand is a single character. There is no indication of success or failure. Failure is rare.
 *   There is no extended error information for this function; do not call GetLastError.
 *
 * The function makes the conversion based on the information associated with the user's default
 * locale, which is the locale selected by the user at setup or by using the Control Panel. Windows
 * CE does not have language drivers.
 *
 * Windows CE supports only the Unicode version of this function.
 */
#define CharUpper CharUpperW
#else
/**
 * This function converts a character string or a single character to uppercase. If the operand is a
 * character string, the function converts the characters in place.
 *
 * @param lpsz [in] Pointer to a null-terminated string or specifies a single character. If the
 *   high-order word of this parameter is zero, the low-order word must contain a single character to
 *   be converted.
 *
 * @return A pointer to the converted string indicates that the operand is a character string. Since
 *   the string is converted in place, the return value is equal to lpsz. A 32-bit value whose
 *   high-order word is zero and low-order word contains the converted character indicates that the
 *   operand is a single character. There is no indication of success or failure. Failure is rare.
 *   There is no extended error information for this function; do not call GetLastError.
 *
 * The function makes the conversion based on the information associated with the user's default
 * locale, which is the locale selected by the user at setup or by using the Control Panel. Windows
 * CE does not have language drivers.
 *
 * Windows CE supports only the Unicode version of this function.
 */
#define CharUpper CharUpperA
#endif

/**
 * This function returns a pointer to the preceding character in a string.
 *
 * @param lpszStart [in] Pointer to the beginning of the null-terminated string.
 * @param lpszCurrent [in] Pointer to a character in a null-terminated string.
 *
 * @return A pointer to the preceding character in the string, or to the first character in the
 *   string if the lpszCurrent parameter equals the lpszStart parameter, indicates success.
 */
LPSTR
WINAPI
CharPrevA(
    LPCSTR lpszStart,
    LPCSTR lpszCurrent);

/**
 * This function returns a pointer to the preceding character in a string.
 *
 * @param lpszStart [in] Pointer to the beginning of the null-terminated string.
 * @param lpszCurrent [in] Pointer to a character in a null-terminated string.
 *
 * @return A pointer to the preceding character in the string, or to the first character in the
 *   string if the lpszCurrent parameter equals the lpszStart parameter, indicates success.
 */
LPWSTR
WINAPI
CharPrevW(
    LPCWSTR lpszStart,
    LPCWSTR lpszCurrent);

#ifdef UNICODE
/**
 * This function returns a pointer to the preceding character in a string.
 *
 * @param lpszStart [in] Pointer to the beginning of the null-terminated string.
 * @param lpszCurrent [in] Pointer to a character in a null-terminated string.
 *
 * @return A pointer to the preceding character in the string, or to the first character in the
 *   string if the lpszCurrent parameter equals the lpszStart parameter, indicates success.
 */
#define CharPrev  CharPrevW
#else
/**
 * This function returns a pointer to the preceding character in a string.
 *
 * @param lpszStart [in] Pointer to the beginning of the null-terminated string.
 * @param lpszCurrent [in] Pointer to a character in a null-terminated string.
 *
 * @return A pointer to the preceding character in the string, or to the first character in the
 *   string if the lpszCurrent parameter equals the lpszStart parameter, indicates success.
 */
#define CharPrev  CharPrevA
#endif // !UNICODE

/**
 * This function returns a pointer to the next character in a string.
 *
 * @param lpsz [in] Pointer to a character in a null-terminated string.
 *
 * @return A pointer to the next character in the string, or to the terminating null character if at
 *   the end of the string, indicates success. If lpsz points to the terminating null character, the
 *   return value is equal to lpsz.
 */
LPSTR
WINAPI
CharNextA(
    LPCSTR lpsz);

/**
 * This function returns a pointer to the next character in a string.
 *
 * @param lpsz [in] Pointer to a character in a null-terminated string.
 *
 * @return A pointer to the next character in the string, or to the terminating null character if at
 *   the end of the string, indicates success. If lpsz points to the terminating null character, the
 *   return value is equal to lpsz.
 */
LPWSTR
WINAPI
CharNextW(
    LPCWSTR lpsz);

#ifdef UNICODE
/**
 * This function returns a pointer to the next character in a string.
 *
 * @param lpsz [in] Pointer to a character in a null-terminated string.
 *
 * @return A pointer to the next character in the string, or to the terminating null character if at
 *   the end of the string, indicates success. If lpsz points to the terminating null character, the
 *   return value is equal to lpsz.
 */
#define CharNext  CharNextW
#else
/**
 * This function returns a pointer to the next character in a string.
 *
 * @param lpsz [in] Pointer to a character in a null-terminated string.
 *
 * @return A pointer to the next character in the string, or to the terminating null character if at
 *   the end of the string, indicates success. If lpsz points to the terminating null character, the
 *   return value is equal to lpsz.
 */
#define CharNext  CharNextA
#endif // !UNICODE



#define IsCharAlphaA isalpha
#define IsCharAlphaW iswalpha
#ifdef UNICODE
/**
 * This function determines whether a character is an alphabetic character. This determination is
 * based on the semantics of the language selected by the user during setup or by using Control
 * Panel.
 *
 * @param ch [in] Specifies the character to be tested.
 *
 * @return Nonzero indicates that the character is alphabetic. Zero indicates that the character is
 *   not alphabetic. To get extended error information, call GetLastError.
 *
 * Windows CE supports only the Unicode version of this function.
 */
#define IsCharAlpha IsCharAlphaW
#else
/**
 * This function determines whether a character is an alphabetic character. This determination is
 * based on the semantics of the language selected by the user during setup or by using Control
 * Panel.
 *
 * @param ch [in] Specifies the character to be tested.
 *
 * @return Nonzero indicates that the character is alphabetic. Zero indicates that the character is
 *   not alphabetic. To get extended error information, call GetLastError.
 *
 * Windows CE supports only the Unicode version of this function.
 */
#define IsCharAlpha IsCharAlphaA
#endif


#define IsCharAlphaNumericA isalnum
#define IsCharAlphaNumericW iswalnum
#ifdef UNICODE
/**
 * This function determines whether a character is either an alphabetic or a numeric character. This
 * determination is based on the semantics of the language selected by the user during setup or by
 * using Control Panel.
 *
 * @param ch [in] Specifies the character to be tested.
 *
 * @return Nonzero indicates that the character is alphanumeric. Zero indicates that the character
 *   is not alphanumeric. To get extended error information, call GetLastError.
 *
 * Windows CE supports only the Unicode version of this function.
 */
#define IsCharAlphaNumeric IsCharAlphaNumericW
#else
/**
 * This function determines whether a character is either an alphabetic or a numeric character. This
 * determination is based on the semantics of the language selected by the user during setup or by
 * using Control Panel.
 *
 * @param ch [in] Specifies the character to be tested.
 *
 * @return Nonzero indicates that the character is alphanumeric. Zero indicates that the character
 *   is not alphanumeric. To get extended error information, call GetLastError.
 *
 * Windows CE supports only the Unicode version of this function.
 */
#define IsCharAlphaNumeric IsCharAlphaNumericA
#endif

#define IsCharLowerA islower
#define IsCharLowerW iswlower
#ifdef UNICODE
/**
 * This function determines whether a character is lowercase. This determination is based on the
 * semantics of the language selected by the user during setup or by using Control Panel.
 *
 * @param ch [in] Specifies the character to be tested.
 *
 * @return Nonzero indicates that the character is lowercase. Zero indicates that the character is
 *   not lowercase. To get extended error information, call GetLastError.
 *
 * Windows CE supports only the Unicode version of this function.
 */
#define IsCharLower IsCharLowerW
#else
/**
 * This function determines whether a character is lowercase. This determination is based on the
 * semantics of the language selected by the user during setup or by using Control Panel.
 *
 * @param ch [in] Specifies the character to be tested.
 *
 * @return Nonzero indicates that the character is lowercase. Zero indicates that the character is
 *   not lowercase. To get extended error information, call GetLastError.
 *
 * Windows CE supports only the Unicode version of this function.
 */
#define IsCharLower IsCharLowerA
#endif

#define IsCharUpperA isupper
#define IsCharUpperW iswupper
#ifdef UNICODE
/**
 * This function determines whether a character is uppercase. This determination is based on the
 * semantics of the language selected by the user during setup or by using Control Panel.
 *
 * @param ch [in] Specifies the character to be tested.
 *
 * @return Nonzero indicates that the character is uppercase. Zero indicates that the character is
 *   not uppercase. To get extended error information, call GetLastError.
 *
 * Windows CE supports only the Unicode version of this function.
 */
#define IsCharUpper IsCharUpperW
#else
/**
 * This function determines whether a character is uppercase. This determination is based on the
 * semantics of the language selected by the user during setup or by using Control Panel.
 *
 * @param ch [in] Specifies the character to be tested.
 *
 * @return Nonzero indicates that the character is uppercase. Zero indicates that the character is
 *   not uppercase. To get extended error information, call GetLastError.
 *
 * Windows CE supports only the Unicode version of this function.
 */
#define IsCharUpper IsCharUpperA
#endif

#include <stdarg.h>

/**
 * This function formats and stores a series of characters and values in a buffer. Any arguments are
 * converted and copied to the output buffer according to the corresponding format specification in
 * the format string. The wsprintf function appends a terminating null character to the characters
 * it writes, but the return value does not include the terminating null character in its character
 * count.
 *
 * @param lpOut [out] Pointer to a buffer to receive the formatted output. The maximum size of the
 *   buffer is 1024 bytes.
 * @param lpFmt [in] Pointer to a null-terminated string that contains the format-control
 *   specifications. In addition to ordinary ASCII characters, a format specification for each
 *   argument appears in this string. For more information about the format specification, see the
 *   Remarks section.
 * @param ... [in] Specifies one or more optional arguments. The number and type of argument
 *   parameters depend on the corresponding format-control specifications in the lpFmt parameter.
 *
 * @return The number of characters stored in the output buffer, not counting the terminating null
 *   character, indicates success. A value less than the length of the format-control string indicates
 *   failure. To get extended error information, call GetLastError.
 *
 * Windows CE supports only the Unicode version of wsprintf.
 *
 * The format-control string contains format specifications that determine the output format for the
 * arguments following the lpFmt parameter. Format specifications, discussed below, always begin
 * with a percent sign (%). If a percent sign is followed by a character that has no meaning as a
 * format field, the character is not formatted (for example, %% produces a single percent-sign
 * character).
 *
 * The format-control string is read from left to right. When the first format specification (if
 * any) is encountered, it causes the value of the first argument after the format-control string to
 * be converted and copied to the output buffer according to the format specification. The second
 * format specification causes the second argument to be converted and copied, and so on. If there
 * are more arguments than format specifications, the extra arguments are ignored. If there are not
 * enough arguments for all of the format specifications, the results are undefined.
 *
 * A format specification has the following form:
 *
 * %[-][#][0][width][.precision]type
 *
 * Each field is a single character or a number signifying a particular format option. The type
 * characters that appear after the last optional format field determine whether the associated
 * argument is interpreted as a character, a string, or a number. The simplest format specification
 * contains only the percent sign and a type character (for example, %s). The optional fields
 * control other aspects of the formatting. Following are the optional and required fields and their
 * meanings:
 *
 * Field Description - Pad the output with blanks or zeros to the right to fill the field width,
 * justifying output to the left. If this field is omitted, the output is padded to the left,
 * justifying it to the right. # Prefix hexadecimal values with 0x (lowercase) or 0X (uppercase). 0
 * Pad the output value with zeros to fill the field width. If this field is omitted, the output
 * value is padded with blank spaces. width Copy the specified minimum number of characters to the
 * output buffer. The width field is a nonnegative integer. The width specification never causes a
 * value to be truncated; if the number of characters in the output value is greater than the
 * specified width, or if the width field is not present, all characters of the value are printed,
 * subject to the precision specification. .precision For numbers, copy the specified minimum number
 * of digits to the output buffer. If the number of digits in the argument is less than the
 * specified precision, the output value is padded on the left with zeros. The value is not
 * truncated when the number of digits exceeds the specified precision. If the specified precision
 * is 0 or omitted entirely, or if the period (.) appears without a number following it, the
 * precision is set to 1. For strings, copy the specified maximum number of characters to the output
 * buffer. type Output the corresponding argument as a character, a string, or a number. This field
 * can be any of the following character sequences: Sequence Insert c A single character. This
 * sequence is interpreted as type WCHAR. C A single character. This sequence is interpreted as type
 * CHAR. d A signed decimal integer argument. This sequence is equivalent to the i sequence. hc, hC
 * A single character. The wsprintf function ignores character arguments with a numeric value of
 * zero. This sequence is always interpreted as type CHAR, even when the calling application uses
 * the #define UNICODE compile flag. hd A signed short integer argument. hs, hS A string. This
 * sequence is always interpreted as type LPSTR, even when the calling application uses the #define
 * UNICODE compile flag. hu An unsigned short integer argument. i A signed decimal integer. This
 * sequence is equivalent to the d sequence. lc, lC A single character. The wsprintf function
 * ignores character arguments with a numeric value of zero. This sequence is always interpreted as
 * type WCHAR, even when the calling application does not use the #define UNICODE compile flag. ld A
 * long signed decimal integer. This sequence is equivalent to the li sequence. li A long signed
 * decimal integer. This sequence is equivalent to the ld sequence. ls, lS A string. This sequence
 * is always interpreted as type LPWSTR, even when the calling application does not use the #define
 * UNICODE compile flag. This sequence is equivalent to the ws sequence. lu A long unsigned integer.
 * lx, lX A long unsigned hexadecimal integer in lowercase or uppercase. s A string. This sequence
 * is interpreted as type LPWSTR. S A string. This sequence is interpreted as type LPSTR. u An
 * unsigned integer argument. x, X An unsigned hexadecimal integer in lowercase or uppercase.
 *
 * Unlike other Win32 functions, wsprintf uses the C calling convention (_cdecl), rather than the
 * Pascal calling convention. As a result, it is the responsibility of the calling process to pop
 * arguments off the stack, and arguments are pushed on the stack from right to left. In C-language
 * modules, the C compiler performs this task.
 */
int
WINAPIV
wsprintfA (
    LPSTR lpBuffer,
    LPCSTR lpFormat,
    ...
    );
/**
 * This function formats and stores a series of characters and values in a buffer. Any arguments are
 * converted and copied to the output buffer according to the corresponding format specification in
 * the format string. The wsprintf function appends a terminating null character to the characters
 * it writes, but the return value does not include the terminating null character in its character
 * count.
 *
 * @param lpOut [out] Pointer to a buffer to receive the formatted output. The maximum size of the
 *   buffer is 1024 bytes.
 * @param lpFmt [in] Pointer to a null-terminated string that contains the format-control
 *   specifications. In addition to ordinary ASCII characters, a format specification for each
 *   argument appears in this string. For more information about the format specification, see the
 *   Remarks section.
 * @param ... [in] Specifies one or more optional arguments. The number and type of argument
 *   parameters depend on the corresponding format-control specifications in the lpFmt parameter.
 *
 * @return The number of characters stored in the output buffer, not counting the terminating null
 *   character, indicates success. A value less than the length of the format-control string indicates
 *   failure. To get extended error information, call GetLastError.
 *
 * Windows CE supports only the Unicode version of wsprintf.
 *
 * The format-control string contains format specifications that determine the output format for the
 * arguments following the lpFmt parameter. Format specifications, discussed below, always begin
 * with a percent sign (%). If a percent sign is followed by a character that has no meaning as a
 * format field, the character is not formatted (for example, %% produces a single percent-sign
 * character).
 *
 * The format-control string is read from left to right. When the first format specification (if
 * any) is encountered, it causes the value of the first argument after the format-control string to
 * be converted and copied to the output buffer according to the format specification. The second
 * format specification causes the second argument to be converted and copied, and so on. If there
 * are more arguments than format specifications, the extra arguments are ignored. If there are not
 * enough arguments for all of the format specifications, the results are undefined.
 *
 * A format specification has the following form:
 *
 * %[-][#][0][width][.precision]type
 *
 * Each field is a single character or a number signifying a particular format option. The type
 * characters that appear after the last optional format field determine whether the associated
 * argument is interpreted as a character, a string, or a number. The simplest format specification
 * contains only the percent sign and a type character (for example, %s). The optional fields
 * control other aspects of the formatting. Following are the optional and required fields and their
 * meanings:
 *
 * Field Description - Pad the output with blanks or zeros to the right to fill the field width,
 * justifying output to the left. If this field is omitted, the output is padded to the left,
 * justifying it to the right. # Prefix hexadecimal values with 0x (lowercase) or 0X (uppercase). 0
 * Pad the output value with zeros to fill the field width. If this field is omitted, the output
 * value is padded with blank spaces. width Copy the specified minimum number of characters to the
 * output buffer. The width field is a nonnegative integer. The width specification never causes a
 * value to be truncated; if the number of characters in the output value is greater than the
 * specified width, or if the width field is not present, all characters of the value are printed,
 * subject to the precision specification. .precision For numbers, copy the specified minimum number
 * of digits to the output buffer. If the number of digits in the argument is less than the
 * specified precision, the output value is padded on the left with zeros. The value is not
 * truncated when the number of digits exceeds the specified precision. If the specified precision
 * is 0 or omitted entirely, or if the period (.) appears without a number following it, the
 * precision is set to 1. For strings, copy the specified maximum number of characters to the output
 * buffer. type Output the corresponding argument as a character, a string, or a number. This field
 * can be any of the following character sequences: Sequence Insert c A single character. This
 * sequence is interpreted as type WCHAR. C A single character. This sequence is interpreted as type
 * CHAR. d A signed decimal integer argument. This sequence is equivalent to the i sequence. hc, hC
 * A single character. The wsprintf function ignores character arguments with a numeric value of
 * zero. This sequence is always interpreted as type CHAR, even when the calling application uses
 * the #define UNICODE compile flag. hd A signed short integer argument. hs, hS A string. This
 * sequence is always interpreted as type LPSTR, even when the calling application uses the #define
 * UNICODE compile flag. hu An unsigned short integer argument. i A signed decimal integer. This
 * sequence is equivalent to the d sequence. lc, lC A single character. The wsprintf function
 * ignores character arguments with a numeric value of zero. This sequence is always interpreted as
 * type WCHAR, even when the calling application does not use the #define UNICODE compile flag. ld A
 * long signed decimal integer. This sequence is equivalent to the li sequence. li A long signed
 * decimal integer. This sequence is equivalent to the ld sequence. ls, lS A string. This sequence
 * is always interpreted as type LPWSTR, even when the calling application does not use the #define
 * UNICODE compile flag. This sequence is equivalent to the ws sequence. lu A long unsigned integer.
 * lx, lX A long unsigned hexadecimal integer in lowercase or uppercase. s A string. This sequence
 * is interpreted as type LPWSTR. S A string. This sequence is interpreted as type LPSTR. u An
 * unsigned integer argument. x, X An unsigned hexadecimal integer in lowercase or uppercase.
 *
 * Unlike other Win32 functions, wsprintf uses the C calling convention (_cdecl), rather than the
 * Pascal calling convention. As a result, it is the responsibility of the calling process to pop
 * arguments off the stack, and arguments are pushed on the stack from right to left. In C-language
 * modules, the C compiler performs this task.
 */
int
WINAPIV
wsprintfW (
    LPWSTR lpBuffer,
    LPCWSTR lpFormat,
    ...
    );
#ifdef UNICODE
/**
 * This function formats and stores a series of characters and values in a buffer. Any arguments are
 * converted and copied to the output buffer according to the corresponding format specification in
 * the format string. The wsprintf function appends a terminating null character to the characters
 * it writes, but the return value does not include the terminating null character in its character
 * count.
 *
 * @param lpOut [out] Pointer to a buffer to receive the formatted output. The maximum size of the
 *   buffer is 1024 bytes.
 * @param lpFmt [in] Pointer to a null-terminated string that contains the format-control
 *   specifications. In addition to ordinary ASCII characters, a format specification for each
 *   argument appears in this string. For more information about the format specification, see the
 *   Remarks section.
 * @param ... [in] Specifies one or more optional arguments. The number and type of argument
 *   parameters depend on the corresponding format-control specifications in the lpFmt parameter.
 *
 * @return The number of characters stored in the output buffer, not counting the terminating null
 *   character, indicates success. A value less than the length of the format-control string indicates
 *   failure. To get extended error information, call GetLastError.
 *
 * Windows CE supports only the Unicode version of wsprintf.
 *
 * The format-control string contains format specifications that determine the output format for the
 * arguments following the lpFmt parameter. Format specifications, discussed below, always begin
 * with a percent sign (%). If a percent sign is followed by a character that has no meaning as a
 * format field, the character is not formatted (for example, %% produces a single percent-sign
 * character).
 *
 * The format-control string is read from left to right. When the first format specification (if
 * any) is encountered, it causes the value of the first argument after the format-control string to
 * be converted and copied to the output buffer according to the format specification. The second
 * format specification causes the second argument to be converted and copied, and so on. If there
 * are more arguments than format specifications, the extra arguments are ignored. If there are not
 * enough arguments for all of the format specifications, the results are undefined.
 *
 * A format specification has the following form:
 *
 * %[-][#][0][width][.precision]type
 *
 * Each field is a single character or a number signifying a particular format option. The type
 * characters that appear after the last optional format field determine whether the associated
 * argument is interpreted as a character, a string, or a number. The simplest format specification
 * contains only the percent sign and a type character (for example, %s). The optional fields
 * control other aspects of the formatting. Following are the optional and required fields and their
 * meanings:
 *
 * Field Description - Pad the output with blanks or zeros to the right to fill the field width,
 * justifying output to the left. If this field is omitted, the output is padded to the left,
 * justifying it to the right. # Prefix hexadecimal values with 0x (lowercase) or 0X (uppercase). 0
 * Pad the output value with zeros to fill the field width. If this field is omitted, the output
 * value is padded with blank spaces. width Copy the specified minimum number of characters to the
 * output buffer. The width field is a nonnegative integer. The width specification never causes a
 * value to be truncated; if the number of characters in the output value is greater than the
 * specified width, or if the width field is not present, all characters of the value are printed,
 * subject to the precision specification. .precision For numbers, copy the specified minimum number
 * of digits to the output buffer. If the number of digits in the argument is less than the
 * specified precision, the output value is padded on the left with zeros. The value is not
 * truncated when the number of digits exceeds the specified precision. If the specified precision
 * is 0 or omitted entirely, or if the period (.) appears without a number following it, the
 * precision is set to 1. For strings, copy the specified maximum number of characters to the output
 * buffer. type Output the corresponding argument as a character, a string, or a number. This field
 * can be any of the following character sequences: Sequence Insert c A single character. This
 * sequence is interpreted as type WCHAR. C A single character. This sequence is interpreted as type
 * CHAR. d A signed decimal integer argument. This sequence is equivalent to the i sequence. hc, hC
 * A single character. The wsprintf function ignores character arguments with a numeric value of
 * zero. This sequence is always interpreted as type CHAR, even when the calling application uses
 * the #define UNICODE compile flag. hd A signed short integer argument. hs, hS A string. This
 * sequence is always interpreted as type LPSTR, even when the calling application uses the #define
 * UNICODE compile flag. hu An unsigned short integer argument. i A signed decimal integer. This
 * sequence is equivalent to the d sequence. lc, lC A single character. The wsprintf function
 * ignores character arguments with a numeric value of zero. This sequence is always interpreted as
 * type WCHAR, even when the calling application does not use the #define UNICODE compile flag. ld A
 * long signed decimal integer. This sequence is equivalent to the li sequence. li A long signed
 * decimal integer. This sequence is equivalent to the ld sequence. ls, lS A string. This sequence
 * is always interpreted as type LPWSTR, even when the calling application does not use the #define
 * UNICODE compile flag. This sequence is equivalent to the ws sequence. lu A long unsigned integer.
 * lx, lX A long unsigned hexadecimal integer in lowercase or uppercase. s A string. This sequence
 * is interpreted as type LPWSTR. S A string. This sequence is interpreted as type LPSTR. u An
 * unsigned integer argument. x, X An unsigned hexadecimal integer in lowercase or uppercase.
 *
 * Unlike other Win32 functions, wsprintf uses the C calling convention (_cdecl), rather than the
 * Pascal calling convention. As a result, it is the responsibility of the calling process to pop
 * arguments off the stack, and arguments are pushed on the stack from right to left. In C-language
 * modules, the C compiler performs this task.
 */
#define wsprintf wsprintfW
#else
/**
 * This function formats and stores a series of characters and values in a buffer. Any arguments are
 * converted and copied to the output buffer according to the corresponding format specification in
 * the format string. The wsprintf function appends a terminating null character to the characters
 * it writes, but the return value does not include the terminating null character in its character
 * count.
 *
 * @param lpOut [out] Pointer to a buffer to receive the formatted output. The maximum size of the
 *   buffer is 1024 bytes.
 * @param lpFmt [in] Pointer to a null-terminated string that contains the format-control
 *   specifications. In addition to ordinary ASCII characters, a format specification for each
 *   argument appears in this string. For more information about the format specification, see the
 *   Remarks section.
 * @param ... [in] Specifies one or more optional arguments. The number and type of argument
 *   parameters depend on the corresponding format-control specifications in the lpFmt parameter.
 *
 * @return The number of characters stored in the output buffer, not counting the terminating null
 *   character, indicates success. A value less than the length of the format-control string indicates
 *   failure. To get extended error information, call GetLastError.
 *
 * Windows CE supports only the Unicode version of wsprintf.
 *
 * The format-control string contains format specifications that determine the output format for the
 * arguments following the lpFmt parameter. Format specifications, discussed below, always begin
 * with a percent sign (%). If a percent sign is followed by a character that has no meaning as a
 * format field, the character is not formatted (for example, %% produces a single percent-sign
 * character).
 *
 * The format-control string is read from left to right. When the first format specification (if
 * any) is encountered, it causes the value of the first argument after the format-control string to
 * be converted and copied to the output buffer according to the format specification. The second
 * format specification causes the second argument to be converted and copied, and so on. If there
 * are more arguments than format specifications, the extra arguments are ignored. If there are not
 * enough arguments for all of the format specifications, the results are undefined.
 *
 * A format specification has the following form:
 *
 * %[-][#][0][width][.precision]type
 *
 * Each field is a single character or a number signifying a particular format option. The type
 * characters that appear after the last optional format field determine whether the associated
 * argument is interpreted as a character, a string, or a number. The simplest format specification
 * contains only the percent sign and a type character (for example, %s). The optional fields
 * control other aspects of the formatting. Following are the optional and required fields and their
 * meanings:
 *
 * Field Description - Pad the output with blanks or zeros to the right to fill the field width,
 * justifying output to the left. If this field is omitted, the output is padded to the left,
 * justifying it to the right. # Prefix hexadecimal values with 0x (lowercase) or 0X (uppercase). 0
 * Pad the output value with zeros to fill the field width. If this field is omitted, the output
 * value is padded with blank spaces. width Copy the specified minimum number of characters to the
 * output buffer. The width field is a nonnegative integer. The width specification never causes a
 * value to be truncated; if the number of characters in the output value is greater than the
 * specified width, or if the width field is not present, all characters of the value are printed,
 * subject to the precision specification. .precision For numbers, copy the specified minimum number
 * of digits to the output buffer. If the number of digits in the argument is less than the
 * specified precision, the output value is padded on the left with zeros. The value is not
 * truncated when the number of digits exceeds the specified precision. If the specified precision
 * is 0 or omitted entirely, or if the period (.) appears without a number following it, the
 * precision is set to 1. For strings, copy the specified maximum number of characters to the output
 * buffer. type Output the corresponding argument as a character, a string, or a number. This field
 * can be any of the following character sequences: Sequence Insert c A single character. This
 * sequence is interpreted as type WCHAR. C A single character. This sequence is interpreted as type
 * CHAR. d A signed decimal integer argument. This sequence is equivalent to the i sequence. hc, hC
 * A single character. The wsprintf function ignores character arguments with a numeric value of
 * zero. This sequence is always interpreted as type CHAR, even when the calling application uses
 * the #define UNICODE compile flag. hd A signed short integer argument. hs, hS A string. This
 * sequence is always interpreted as type LPSTR, even when the calling application uses the #define
 * UNICODE compile flag. hu An unsigned short integer argument. i A signed decimal integer. This
 * sequence is equivalent to the d sequence. lc, lC A single character. The wsprintf function
 * ignores character arguments with a numeric value of zero. This sequence is always interpreted as
 * type WCHAR, even when the calling application does not use the #define UNICODE compile flag. ld A
 * long signed decimal integer. This sequence is equivalent to the li sequence. li A long signed
 * decimal integer. This sequence is equivalent to the ld sequence. ls, lS A string. This sequence
 * is always interpreted as type LPWSTR, even when the calling application does not use the #define
 * UNICODE compile flag. This sequence is equivalent to the ws sequence. lu A long unsigned integer.
 * lx, lX A long unsigned hexadecimal integer in lowercase or uppercase. s A string. This sequence
 * is interpreted as type LPWSTR. S A string. This sequence is interpreted as type LPSTR. u An
 * unsigned integer argument. x, X An unsigned hexadecimal integer in lowercase or uppercase.
 *
 * Unlike other Win32 functions, wsprintf uses the C calling convention (_cdecl), rather than the
 * Pascal calling convention. As a result, it is the responsibility of the calling process to pop
 * arguments off the stack, and arguments are pushed on the stack from right to left. In C-language
 * modules, the C compiler performs this task.
 */
#define wsprintf wsprintfA
#endif

/**
 * This function formats and stores a series of characters and values in a buffer. The items pointed
 * to by the argument list are converted and copied to an output buffer according to the
 * corresponding format specification in the format-control string. The function appends a
 * terminating null character to the characters it writes, but the return value does not include the
 * terminating null character in its character count.
 *
 * @param lpOutput [out] Pointer to a buffer to receive the formatted output.
 * @param lpFormat [in] Pointer to a null-terminated string that contains the format-control
 *   specifications. In addition to ordinary ASCII characters, a format specification for each
 *   argument appears in this string. For more information about the format specification, see
 *   wsprintf.
 * @param arglist [in] Variable argument list; each element of the list specifies an argument for
 *   the format-control string. The number, type, and interpretation of the arguments depend on the
 *   corresponding format-control specifications in the lpFmt parameter.
 *
 * @return The number of characters stored in the buffer, not counting the terminating null
 *   character, indicates success. A value less than the length of the format-control string indicates
 *   failure. To get extended error information, call GetLastError.
 *
 * Windows CE supports only the Unicode version of wvsprintf.
 *
 * The function copies the format-control string into the output buffer character by character,
 * starting with the first character in the string. When it encounters a format specification in the
 * string, the function retrieves the value of the next available argument (starting with the first
 * argument in the list), converts that value into the specified format, and copies the result to
 * the output buffer. The function continues to copy characters and expand format specifications in
 * this way until it reaches the end of the format-control string. If there are more arguments than
 * format specifications, the extra arguments are ignored. If there are not enough arguments for all
 * of the format specifications, the results are undefined.
 */
int
WINAPI
wvsprintfA (
    LPSTR,
    LPCSTR,
    va_list ArgList
    );

/**
 * This function formats and stores a series of characters and values in a buffer. The items pointed
 * to by the argument list are converted and copied to an output buffer according to the
 * corresponding format specification in the format-control string. The function appends a
 * terminating null character to the characters it writes, but the return value does not include the
 * terminating null character in its character count.
 *
 * @param lpOutput [out] Pointer to a buffer to receive the formatted output.
 * @param lpFormat [in] Pointer to a null-terminated string that contains the format-control
 *   specifications. In addition to ordinary ASCII characters, a format specification for each
 *   argument appears in this string. For more information about the format specification, see
 *   wsprintf.
 * @param arglist [in] Variable argument list; each element of the list specifies an argument for
 *   the format-control string. The number, type, and interpretation of the arguments depend on the
 *   corresponding format-control specifications in the lpFmt parameter.
 *
 * @return The number of characters stored in the buffer, not counting the terminating null
 *   character, indicates success. A value less than the length of the format-control string indicates
 *   failure. To get extended error information, call GetLastError.
 *
 * Windows CE supports only the Unicode version of wvsprintf.
 *
 * The function copies the format-control string into the output buffer character by character,
 * starting with the first character in the string. When it encounters a format specification in the
 * string, the function retrieves the value of the next available argument (starting with the first
 * argument in the list), converts that value into the specified format, and copies the result to
 * the output buffer. The function continues to copy characters and expand format specifications in
 * this way until it reaches the end of the format-control string. If there are more arguments than
 * format specifications, the extra arguments are ignored. If there are not enough arguments for all
 * of the format specifications, the results are undefined.
 */
int
WINAPI
wvsprintfW (
    LPWSTR,
    LPCWSTR,
    va_list ArgList
    );
#ifdef UNICODE
/**
 * This function formats and stores a series of characters and values in a buffer. The items pointed
 * to by the argument list are converted and copied to an output buffer according to the
 * corresponding format specification in the format-control string. The function appends a
 * terminating null character to the characters it writes, but the return value does not include the
 * terminating null character in its character count.
 *
 * @param lpOutput [out] Pointer to a buffer to receive the formatted output.
 * @param lpFormat [in] Pointer to a null-terminated string that contains the format-control
 *   specifications. In addition to ordinary ASCII characters, a format specification for each
 *   argument appears in this string. For more information about the format specification, see
 *   wsprintf.
 * @param arglist [in] Variable argument list; each element of the list specifies an argument for
 *   the format-control string. The number, type, and interpretation of the arguments depend on the
 *   corresponding format-control specifications in the lpFmt parameter.
 *
 * @return The number of characters stored in the buffer, not counting the terminating null
 *   character, indicates success. A value less than the length of the format-control string indicates
 *   failure. To get extended error information, call GetLastError.
 *
 * Windows CE supports only the Unicode version of wvsprintf.
 *
 * The function copies the format-control string into the output buffer character by character,
 * starting with the first character in the string. When it encounters a format specification in the
 * string, the function retrieves the value of the next available argument (starting with the first
 * argument in the list), converts that value into the specified format, and copies the result to
 * the output buffer. The function continues to copy characters and expand format specifications in
 * this way until it reaches the end of the format-control string. If there are more arguments than
 * format specifications, the extra arguments are ignored. If there are not enough arguments for all
 * of the format specifications, the results are undefined.
 */
#define wvsprintf wvsprintfW
#else
/**
 * This function formats and stores a series of characters and values in a buffer. The items pointed
 * to by the argument list are converted and copied to an output buffer according to the
 * corresponding format specification in the format-control string. The function appends a
 * terminating null character to the characters it writes, but the return value does not include the
 * terminating null character in its character count.
 *
 * @param lpOutput [out] Pointer to a buffer to receive the formatted output.
 * @param lpFormat [in] Pointer to a null-terminated string that contains the format-control
 *   specifications. In addition to ordinary ASCII characters, a format specification for each
 *   argument appears in this string. For more information about the format specification, see
 *   wsprintf.
 * @param arglist [in] Variable argument list; each element of the list specifies an argument for
 *   the format-control string. The number, type, and interpretation of the arguments depend on the
 *   corresponding format-control specifications in the lpFmt parameter.
 *
 * @return The number of characters stored in the buffer, not counting the terminating null
 *   character, indicates success. A value less than the length of the format-control string indicates
 *   failure. To get extended error information, call GetLastError.
 *
 * Windows CE supports only the Unicode version of wvsprintf.
 *
 * The function copies the format-control string into the output buffer character by character,
 * starting with the first character in the string. When it encounters a format specification in the
 * string, the function retrieves the value of the next available argument (starting with the first
 * argument in the list), converts that value into the specified format, and copies the result to
 * the output buffer. The function continues to copy characters and expand format specifications in
 * this way until it reaches the end of the format-control string. If there are more arguments than
 * format specifications, the extra arguments are ignored. If there are not enough arguments for all
 * of the format specifications, the results are undefined.
 */
#define wvsprintf wvsprintfA
#endif

// @CESYSGEN IF COREDLL_LMEM

/* Why does Win32 not use the LSB flag ? */
#define LMEM_FIXED          0x0000
#define LMEM_MOVEABLE       0x0002
#define LMEM_NOCOMPACT      0x0010       /**** Used for Moveable Memory  ***/
#define LMEM_NODISCARD      0x0020       /**** Ignored *****/
#define LMEM_ZEROINIT       0x0040
#define LMEM_MODIFY         0x0080       /*** Used only in LocalReAlloc() **/
#define LMEM_DISCARDABLE    0x0F00       /**** Ignored ****/
#define LMEM_VALID_FLAGS    0x0F72
#define LMEM_INVALID_HANDLE 0x8000

#define LHND                (LMEM_MOVEABLE | LMEM_ZEROINIT)
#define LPTR                (LMEM_FIXED | LMEM_ZEROINIT)

#define NONZEROLHND         (LMEM_MOVEABLE)
#define NONZEROLPTR         (LMEM_FIXED)

/* Flags returned by LocalFlags (in addition to LMEM_DISCARDABLE) */
#define LMEM_DISCARDED      0x4000
#define LMEM_LOCKCOUNT      0x00FF

// @CESYSGEN ENDIF

/**
 * This structure contains information about current memory availability. The GlobalMemoryStatus
 * function uses this structure.
 */
typedef struct _MEMORYSTATUS {
    /**
     * Specifies the size, in bytes, of the MEMORYSTATUS data structure. You do not need to set this
     * member before calling the GlobalMemoryStatus function; the function sets it.
     */
    DWORD dwLength;
    /**
     * Specifies a number between 0 and 100 that gives a general idea of current memory utilization, in
     * which 0 indicates no memory use and 100 indicates full memory use.
     */
    DWORD dwMemoryLoad;
    /**
     * Indicates the total number of bytes of physical memory.
     */
    DWORD dwTotalPhys;
    /**
     * Indicates the number of bytes of physical memory available.
     */
    DWORD dwAvailPhys;
    /**
     * Indicates the total number of bytes that can be stored in the paging file. Note that this number
     * does not represent the actual physical size of the paging file on disk.
     */
    DWORD dwTotalPageFile;
    /**
     * Indicates the number of bytes available in the paging file.
     */
    DWORD dwAvailPageFile;
    /**
     * Indicates the total number of bytes that can be described in the user mode portion of the virtual
     * address space of the calling process.
     */
    DWORD dwTotalVirtual;
    /**
     * Indicates the number of bytes of unreserved and uncommitted memory in the user mode portion of
     * the virtual address space of the calling process.
     */
    DWORD dwAvailVirtual;
} MEMORYSTATUS, *LPMEMORYSTATUS;

/**
 * This function gets information on the physical and virtual memory of the system.
 *
 * @param lpBuffer [out] Pointer to a MEMORYSTATUS structure. The GlobalMemoryStatus function stores
 *   information about current memory availability into this structure.
 *
 * @return None.
 *
 * You can use the GlobalMemoryStatus function to determine how much memory your application can
 * allocate without severely impacting other applications.
 *
 * The information returned by the GlobalMemoryStatus function is volatile. There is no guarantee
 * that two sequential calls to this function will return the same information.
 */
VOID
WINAPI
GlobalMemoryStatus(
    LPMEMORYSTATUS lpBuffer
    );

// @CESYSGEN IF COREDLL_LMEM

#define LocalLock(X) ((LPVOID)X)
#define LocalUnlock(X) (0)
#define LocalHandle(X) ((HLOCAL)X)
#define LocalFlags(X) (0)

/**
 * This function allocates the specified number of bytes from the heap. In the linear Windows CE API
 * environment, there is no difference between the local heap and the global heap.
 *
 * @param uFlags [in] Specifies how to allocate memory. If zero is specified, the default is the
 *   LMEM_FIXED flag. This parameter is one of the following flags: Value Description LMEM_FIXED
 *   Allocates fixed memory. The return value is a pointer to the memory object. LPTR Combines the
 *   LMEM_FIXED and LMEM_ZEROINIT flags. LMEM_ZEROINIT Initializes memory contents to zero.
 * @param uBytes [in] Specifies the number of bytes to allocate.
 *
 * @return A handle to the newly allocated memory object indicates success. NULL indicates failure.
 *   To get extended error information, call GetLastError.
 *
 * If the heap does not contain sufficient free space to satisfy the request, LocalAlloc returns
 * NULL. Because NULL is used to indicate an error, virtual address zero is never allocated. It is,
 * therefore, easy to detect the use of a NULL pointer.
 *
 * If this function succeeds, it allocates at least the amount requested. If the amount allocated is
 * greater than the amount requested, the process can use the entire amount. To determine the actual
 * number of bytes allocated, use the LocalSize function.
 *
 * To free the memory, use the LocalFree function.
 *
 * For Windows CE version 1.0 and 1.01, the local heap for each process cannot exceed 1 MB. However,
 * a process can create multiple heaps using the HeapCreate function and each of these heaps can be
 * up to 1 MB.
 */
HLOCAL
WINAPI
LocalAlloc (
    UINT fuFlags,
    UINT cbBytes
    );

/**
 * This function frees the specified local memory object and invalidates its handle.
 *
 * @param hMem Handle to the local memory object. This handle is returned by either the LocalAlloc
 *   or LocalReAlloc function.
 *
 * @return NULL indicates success. A handle to the local memory object indicates failure. To get
 *   extended error information, call GetLastError.
 *
 * If the process tries to examine or modify the memory after it has been freed, heap corruption may
 * occur or an access violation exception (EXCEPTION_ACCESS_VIOLATION) may be generated.
 *
 * If the hMem parameter is NULL, LocalFree ignores the parameter and returns NULL.
 *
 * The LocalFree function will free a locked memory object. A locked memory object has a lock count
 * greater than zero.
 *
 * If an application is running under a debug version of the system, LocalFree issues a message that
 * tells you that a locked object is being freed. If you are debugging the application, LocalFree
 * enters a breakpoint just before freeing a locked object. This allows you to verify the intended
 * behavior, then continue execution.
 */
HLOCAL
WINAPI
LocalFree (
    HLOCAL hMem
    );

/**
 * This function changes the size or the attributes of a specified local memory object. The size can
 * increase or decrease.
 *
 * @param hMem [in] Handle to the local memory object to be reallocated. This handle is returned by
 *   either the LocalAlloc or LocalReAlloc function.
 * @param uBytes [in] New size, in bytes, of the memory block. If uFlags specifies the LMEM_MODIFY
 *   flag, this parameter is ignored.
 * @param uFlags [in] Flag that specifies how to reallocate the local memory object. If the
 *   LMEM_MODIFY flag is specified, this parameter modifies the attributes of the memory object, and
 *   the uBytes parameter is ignored. Otherwise, this parameter controls the reallocation of the
 *   memory object. The LMEM_MODIFY flag can be combined with the following flag: Value Description
 *   LMEM_MOVEABLE You cannot combine LMEM_MOVEABLE with LMEM_MODIFY to change a fixed memory object
 *   into a movable one. If you do so, the function returns an error. If this parameter does not
 *   specify LMEM_MODIFY, this parameter can be any combination of the following flags: Value
 *   Description LMEM_MOVEABLE In Windows CE, this flag enables the memory allocation to move if it
 *   can not be allocated in place. LMEM_ZEROINIT Causes the additional memory contents to be
 *   initialized to zero if the memory object is growing in size.
 *
 * @return A handle to the reallocated memory object indicates success. NULL indicates failure. To
 *   get extended error information, call GetLastError.
 *
 * If LocalReAlloc fails, the original memory is not freed, and the original handle and pointer are
 * still valid.
 *
 * If LocalReAlloc reallocates a movable object, the return value is a handle to the memory object.
 *
 * If LocalReAlloc reallocates a fixed object, the value of the handle returned is the address of
 * the first byte of the memory block. To access the memory, a process can simply cast the return
 * value to a pointer.
 */
HLOCAL
WINAPI
LocalReAlloc (
    HLOCAL hMem,
    UINT cbBytes,
    UINT fuFlags
    );

/**
 * This function returns the current size, in bytes, of the specified local memory object.
 *
 * @param hMem [in] Handle to the local memory object. This handle is returned by the LocalAlloc or
 *   LocalReAlloc function.
 *
 * @return The size, in bytes, of the specified local memory object indicates success. Zero
 *   indicates that the specified handle is not valid or if the object has been discarded. To get
 *   extended error information, call GetLastError.
 *
 * The size of a memory block may be larger than the size requested when the memory was allocated.
 */
UINT
WINAPI
LocalSize (
    HLOCAL hMem
    );

// @CESYSGEN ENDIF

/**
 * This function reserves or commits a region of pages in the virtual address space of the calling
 * process. Memory allocated by VirtualAlloc is automatically initialized to zero.
 *
 * @param lpAddress Long pointer to the desired starting address of the region to allocate. If the
 *   memory is being reserved, the specified address is rounded down to the next 64-kilobyte boundary.
 *   If the memory is already reserved and is being committed, the address is rounded down to the next
 *   page boundary. To determine the size of a page on the host computer, use the GetSystemInfo
 *   function. If this parameter is NULL, the system determines where to allocate the region.
 * @param dwSize Specifies the size, in bytes, of the region. If the lpAddress parameter is NULL,
 *   this value is rounded up to the next page boundary. Otherwise, the allocated pages include all
 *   pages containing one or more bytes in the range from lpAddress to (lpAddress+dwSize). This means
 *   that a 2-byte range straddling a page boundary causes both pages to be included in the allocated
 *   region.
 * @param flAllocationType Specifies the type of allocation. You can specify any combination of the
 *   following flags: Value Description MEM_COMMIT Allocates physical storage in memory or in the
 *   paging file on disk for the specified region of pages. An attempt to commit an already committed
 *   page will not cause the function to fail. This means that a range of committed or decommitted
 *   pages can be committed without having to worry about a failure. MEM_RESERVE Reserves a range of
 *   the process's virtual address space without allocating any physical storage. The reserved range
 *   cannot be used by any other allocation operations (the malloc function, the LocalAlloc function,
 *   and so on) until it is released. Reserved pages can be committed in subsequent calls to the
 *   VirtualAlloc function. MEM_RESET Not supported. MEM_TOP_DOWN Allocates memory at the highest
 *   possible address.
 * @param flProtect Specifies the type of access protection. If the pages are being committed, any
 *   one of the following flags can be specified, along with the PAGE_GUARD and PAGE_NOCACHE
 *   protection modifier flags, as desired: Value Description PAGE_READONLY Enables read access to the
 *   committed region of pages. An attempt to write to the committed region results in an access
 *   violation. If the system differentiates between read-only access and execute access, an attempt
 *   to execute code in the committed region results in an access violation. PAGE_READWRITE Enables
 *   both read and write access to the committed region of pages. PAGE_EXECUTE Enables execute access
 *   to the committed region of pages. An attempt to read or write to the committed region results in
 *   an access violation. PAGE_EXECUTE_READ Enables execute and read access to the committed region of
 *   pages. An attempt to write to the committed region results in an access violation.
 *   PAGE_EXECUTE_READWRITE Enables execute, read, and write access to the committed region of pages.
 *   PAGE_GUARD Pages in the region become guard pages. Any attempt to read from or write to a guard
 *   page causes the system to raise a STATUS_GUARD_PAGE exception and turn off the guard page status.
 *   Guard pages thus act as a one-shot access alarm. The PAGE_GUARD flag is a page protection
 *   modifier. An application uses it with one of the other page protection flags, with one exception:
 *   It cannot be used with PAGE_NOACCESS. When an access attempt leads the system to turn off guard
 *   page status, the underlying page protection takes over. If a guard page exception occurs during a
 *   system service, the service typically returns a failure status indicator. PAGE_NOACCESS Disables
 *   all access to the committed region of pages. An attempt to read from, write to, or execute in the
 *   committed region results in an access violation exception, called a general protection (GP)
 *   fault. PAGE_NOCACHE Allows no caching of the committed regions of pages. The hardware attributes
 *   for the physical memory should be specified as "no cache." This is not recommended for general
 *   usage. It is useful for device drivers; for example, mapping a video frame buffer with no
 *   caching. This flag is a page protection modifier, only valid when used with one of the page
 *   protections other than PAGE_NOACCESS.
 *
 * @return The base address of the allocated region of pages indicates success. NULL indicates
 *   failure. To get extended error information, call GetLastError.
 *
 * The following flProtect flags are not supported:
 *
 * PAGE_WRITECOPY
 *
 * PAGE_EXECUTE_WRITECOPY
 *
 * VirtualAlloc can perform the following operations:
 *
 * Commit a region of pages reserved by a previous call to the VirtualAlloc function.
 *
 * Reserve a region of free pages.
 *
 * Reserve and commit a region of free pages.
 *
 * You can use VirtualAlloc to reserve a block of pages and then make additional calls to
 * VirtualAlloc to commit individual pages from the reserved block. This enables a process to
 * reserve a range of its virtual address space without consuming physical storage until it is
 * needed.
 *
 * Each page in the process's virtual address space is in one of three states:
 *
 * - Free: The page is not committed or reserved and is not accessible to the process. VirtualAlloc
 * can reserve, or simultaneously reserve and commit, a free page.
 *
 * - Reserved: The range of addresses cannot be used by other allocation functions, but the page is
 * not accessible and has no physical storage associated with it. VirtualAlloc can commit a reserved
 * page, but it cannot reserve it a second time. The VirtualFree function can release a reserved
 * page, making it a free page.
 *
 * - Committed: Physical storage is allocated for the page, and access is controlled by a protection
 * code. The system initializes and loads each committed page into physical memory only at the first
 * attempt to read or write to that page. When the process terminates, the system releases the
 * storage for committed pages. VirtualAlloc can commit an already committed page. This means that
 * you can commit a range of pages, regardless of whether they have already been committed, and the
 * function will not fail. VirtualFree can decommit a committed page, releasing the page's storage,
 * or it can simultaneously decommit and release a committed page.
 *
 * If the lpAddress parameter is not NULL, the function uses the lpAddress and dwSize parameters to
 * compute the region of pages to be allocated. The current state of the entire range of pages must
 * be compatible with the type of allocation specified by the flAllocationType parameter. Otherwise,
 * the function fails and none of the pages are allocated. This compatibility requirement does not
 * preclude committing an already committed page; see the preceding list.
 */
LPVOID
WINAPI
VirtualAlloc(
    LPVOID lpAddress,
    DWORD dwSize,
    DWORD flAllocationType,
    DWORD flProtect
    );

/**
 * This function releases or decommits (or both) a region of pages within the virtual address space
 * of the calling process.
 *
 * @param lpAddress Pointer to the base address of the region of pages to be freed. If the
 *   dwFreeType parameter includes the MEM_RELEASE flag, this parameter must be the base address
 *   returned by the VirtualAlloc function when the region of pages was reserved.
 * @param dwSize Specifies the size, in bytes, of the region to be freed. If the dwFreeType
 *   parameter includes the MEM_RELEASE flag, this parameter must be zero. Otherwise, the region of
 *   affected pages includes all pages containing one or more bytes in the range from the lpAddress
 *   parameter to (lpAddress+dwSize). This means that a 2-byte range straddling a page boundary causes
 *   both pages to be freed.
 * @param dwFreeType Specifies the type of free operation. One, but not both, of the following flags
 *   can be specified: Value Description MEM_DECOMMIT Decommits the specified region of committed
 *   pages. An attempt to decommit an uncommitted page will not cause the function to fail. This means
 *   that a range of committed or uncommitted pages can be decommitted without having to worry about a
 *   failure. MEM_RELEASE Releases the specified region of reserved pages. If this flag is specified,
 *   the dwSize parameter must be zero, or the function fails.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * VirtualFree can perform one of the following operations:
 *
 * Decommit a region of committed or uncommitted pages.
 *
 * Release a region of reserved pages.
 *
 * Decommit and release a region of committed or uncommitted pages.
 *
 * To release a region of pages, the entire range of pages must be in the same state (all reserved
 * or all committed) and the entire region originally reserved by the VirtualAlloc function must be
 * released at the same time. If only part of the pages in the original reserved region are
 * committed, you must first call VirtualFree to decommit the committed pages and then call
 * VirtualFree again to release the entire block.
 *
 * Pages that have been released are free pages available for subsequent allocation operations.
 * Attempting to read from or write to a free page results in an access violation exception.
 *
 * VirtualFree can decommit an uncommitted page; this means that a range of committed or uncommitted
 * pages can be decommitted without having to worry about a failure. Decommitting a page releases
 * its physical storage, either in memory or in the paging file on disk. If a page is decommitted
 * but not released, its state changes to reserved, and it can be committed again by a subsequent
 * call to VirtualAlloc. Attempting to read from or write to a reserved page results in an access
 * violation exception.
 *
 * The current state of the entire range of pages must be compatible with the type of free operation
 * specified by the dwFreeType parameter. Otherwise, the function fails and no pages are released or
 * decommitted.
 */
BOOL
WINAPI
VirtualFree(
    LPVOID lpAddress,
    DWORD dwSize,
    DWORD dwFreeType
    );

/**
 * This function changes the access protection on a region of committed pages in the virtual address
 * space of the calling process.
 *
 * @param lpAddress Pointer to the base address of the region of pages whose access protection
 *   attributes are to be changed. All pages in the specified region must have been allocated in a
 *   single call to the VirtualAlloc function. The pages cannot span adjacent regions that were
 *   allocated by separate calls to VirtualAlloc.
 * @param dwSize Specifies the size, in bytes, of the region whose access protection attributes are
 *   to be changed. The region of affected pages includes all pages containing one or more bytes in
 *   the range from the lpAddress parameter to (lpAddress+dwSize). This means that a 2-byte range
 *   straddling a page boundary causes the protection attributes of both pages to be changed.
 * @param flNewProtect Specifies the new access protection. You can specify any one of the following
 *   flags, along with the PAGE_GUARD and PAGE_NOCACHE protection modifier flags, as necessary: Value
 *   Description PAGE_READONLY Enables read access to the committed region of pages. An attempt to
 *   write to the committed region results in an access violation. If the system differentiates
 *   between read-only access and execute access, an attempt to execute code in the committed region
 *   results in an access violation. PAGE_READWRITE Enables both read and write access to the
 *   committed region of pages. PAGE_WRITECOPY Gives copy-on-write access to the committed region of
 *   pages. PAGE_EXECUTE Enables execute access to the committed region of pages. An attempt to read
 *   or write to the committed region results in an access violation. PAGE_EXECUTE_READ Enables
 *   execute and read access to the committed region of pages. An attempt to write to the committed
 *   region results in an access violation. PAGE_EXECUTE_READWRITE Enables execute, read, and write
 *   access to the committed region of pages. PAGE_EXECUTE_WRITECOPY Enables execute, read, and write
 *   access to the committed region of pages. The pages are shared read-on-write and copy-on-write.
 *   PAGE_GUARD Pages in the region become guard pages. Any attempt to access a guard page causes the
 *   system to raise a STATUS_GUARD_PAGE exception and turn off the guard page status. Guard pages
 *   thus act as a one-shot access alarm. The PAGE_GUARD flag is a page protection modifier. An
 *   application uses it with one of the other page protection flags, with one exception: it cannot be
 *   used with PAGE_NOACCESS. When an access attempt leads the system to turn off guard page status,
 *   the underlying page protection takes over. If a guard page exception occurs during a system
 *   service, the service typically returns a failure status indicator. PAGE_NOACCESS Disables all
 *   access to the committed region of pages. An attempt to read from, write to, or execute in the
 *   committed region results in an access violation exception, called a general protection (GP)
 *   fault. PAGE_NOCACHE Allows no caching of the committed regions of pages. The hardware attributes
 *   for the physical memory should be specified as "no cache." This is not recommended for general
 *   usage. It is useful for device drivers; for example, mapping a video frame buffer with no
 *   caching. This flag is a page protection modifier, only valid when used with one of the page
 *   protections other than PAGE_NOACCESS.
 * @param lpflOldProtect Long pointer to a variable that the function sets to the previous access
 *   protection value of the first page in the specified region of pages. If this parameter is NULL or
 *   does not point to a valid variable, the function fails.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * The following flProtect flags are not supported:
 *
 * PAGE_WRITECOPY
 *
 * PAGE_EXECUTE_WRITECOPY
 *
 * You can set the access protection value on committed pages only. If the state of any page in the
 * specified region is not committed, the function fails and returns without modifying the access
 * protection of any pages in the specified region.
 *
 * The VirtualProtect function changes the access protection of memory in the calling process, and
 * the VirtualProtectEx function changes the access protection of memory in a specified process.
 */
BOOL
WINAPI
VirtualProtect(
    LPVOID lpAddress,
    DWORD dwSize,
    DWORD flNewProtect,
    PDWORD lpflOldProtect
    );

/**
 * This function provides information about a range of pages in the virtual address space of the
 * calling process.
 *
 * @param lpAddress Pointer to the base address of the region of pages to be queried. This value is
 *   rounded down to the next page boundary. To determine the size of a page on the host computer, use
 *   the GetSystemInfo function.
 * @param lpBuffer Pointer to a MEMORY_BASIC_INFORMATION structure in which information about the
 *   specified page range is returned.
 * @param dwLength Specifies the size, in bytes, of the buffer pointed to by the lpBuffer parameter.
 *
 * @return The actual number of bytes returned in the information buffer indicates success.
 *
 * VirtualQuery provides information about a region of consecutive pages beginning at a specified
 * address that share the following attributes:
 *
 * The state of all pages is the same with the MEM_COMMIT, MEM_RESERVE, MEM_FREE, MEM_PRIVATE,
 * MEM_MAPPED, or MEM_IMAGE flag.
 *
 * If the initial page is not free, all pages in the region are part of the same initial allocation
 * of pages reserved by a call to the VirtualAlloc function.
 *
 * The access of all pages is the same with the PAGE_READONLY, PAGE_READWRITE, PAGE_NOACCESS,
 * PAGE_WRITECOPY, PAGE_EXECUTE, PAGE_EXECUTE_READ, PAGE_EXECUTE_READWRITE, PAGE_EXECUTE_WRITECOPY,
 * PAGE_GUARD, or PAGE_NOCACHE flag.
 *
 * The function determines the attributes of the first page in the region and then scans subsequent
 * pages until it scans the entire range of pages or until it encounters a page with a nonmatching
 * set of attributes. The function returns the attributes and the size, in bytes, of the region of
 * pages with matching attributes. For example, if there is a 20 megabyte (MB) region of free
 * memory, and VirtualQuery is called on a page that is 10 MB into the region, the function will
 * obtain a state of MEM_FREE and a size of 10 MB.
 *
 * This function reports on a region of pages in the memory of the calling process, and the
 * VirtualQueryEx function reports on a region of pages in the memory of a specified process.
 */
DWORD
WINAPI
VirtualQuery(
    LPCVOID lpAddress,
    PMEMORY_BASIC_INFORMATION lpBuffer,
    DWORD dwLength
    );

// @CESYSGEN IF COREDLL_LMEM

/**
 * This function obtains a handle to the heap of the calling process. This handle can then be used
 * in calls to the HeapAlloc, HeapReAlloc, HeapFree, and HeapSize functions.
 *
 * @return A handle to the calling process's heap indicates success. NULL indicates failure. To get
 *   extended error information, call GetLastError.
 *
 * The GetProcessHeap function allows you to allocate memory from the process heap without having to
 * first create a heap with the HeapCreate function, as shown in this example:
 *
 *     HeapAlloc(GetProcessHeap(), 0, dwBytes);
 *
 * Note The handle obtained by calling this function should not be used in calls to the HeapDestroy
 * function.
 */
HANDLE WINAPI GetProcessHeap(VOID);

/**
 * This function creates a heap object that is private to the calling process. This reserves a
 * contiguous block of the process's virtual address space and allocates physical storage for a
 * specified initial portion of this block.
 *
 * @param flOptions [in] Specifies optional attributes for the new heap. These flags will affect
 *   subsequent access to the new heap through calls to the heap functions (HeapAlloc, HeapFree,
 *   HeapReAlloc, and HeapSize). You can specify the following flag: Value Description
 *   HEAP_NO_SERIALIZE Specifies that mutual exclusion will not be used when the heap functions
 *   allocate and free memory from this heap. The default, when the HEAP_NO_SERIALIZE flag is not
 *   specified, is to serialize access to the heap. Serialization of heap access allows two or more
 *   threads to simultaneously allocate and free memory from the same heap.
 * @param dwInitialSize [in] Specifies the initial size, in bytes, of the heap. This value
 *   determines the initial amount of physical storage that is allocated for the heap. The value is
 *   rounded up to the next page boundary. To determine the size of a page on the host computer, use
 *   the GetSystemInfo function.
 * @param dwMaximumSize Unsupported.
 *
 * @return A handle to the newly created heap indicates success. NULL indicates failure. To get
 *   extended error information, call GetLastError.
 *
 * The HeapCreate function creates a private heap object from which the calling process can allocate
 * memory blocks by using the HeapAlloc function. The initial size determines the number of
 * committed pages that are initially allocated for the heap. These pages create a block in the
 * process's virtual address space into which the heap can grow. If requests by HeapAlloc exceed the
 * current size of committed pages, additional pages are automatically committed from this reserved
 * space, assuming that the physical storage is available.
 *
 * The memory of a private heap object is accessible only to the process that created it. If a
 * dynamic-link library (DLL) creates a private heap, the heap is created in the address space of
 * the process that called the DLL, and it is accessible only to that process.
 *
 * The system uses memory from the private heap to store heap support structures, so not all of the
 * specified heap size is available to the process. For example, if the HeapAlloc function requests
 * 64 kilobytes (K) from a heap with a maximum size of 64K, the request may fail because of system
 * overhead.
 *
 * If the HEAP_NO_SERIALIZE flag is not specified (the simple default), the heap will serialize
 * access within the calling process. Serialization ensures mutual exclusion when two or more
 * threads attempt to simultaneously allocate or free blocks from the same heap. There is a small
 * performance cost to serialization, but it must be used whenever multiple threads allocate and
 * free memory from the same heap.
 *
 * Setting the HEAP_NO_SERIALIZE flag eliminates mutual exclusion on the heap. Without
 * serialization, two or more threads that use the same heap handle might attempt to allocate or
 * free memory simultaneously, likely causing corruption in the heap. The HEAP_NO_SERIALIZE flag
 * can, therefore, be safely used only in the following situations:
 *
 * The process has only one thread.
 *
 * The process has multiple threads, but only one thread calls the heap functions for a specific
 * heap.
 *
 * The process has multiple threads, and the application provides its own mechanism for mutual
 * exclusion to a specific heap.
 */
HANDLE
WINAPI
HeapCreate(
    DWORD flOptions,
    DWORD dwInitialSize,
    DWORD dwMaximumSize
    );

/**
 * This function destroys the specified heap object.
 *
 * @param hHeap [in] Handle to the heap to be destroyed. This parameter should be a heap handle
 *   returned by the HeapCreate function. Do not use the handle to the process heap returned by the
 *   GetProcessHeap function.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * Processes can call HeapDestroy without first calling the HeapFree function to free memory
 * allocated from the heap.
 */
BOOL
WINAPI
HeapDestroy(
    HANDLE hHeap
    );

/**
 * This function allocates a block of memory from a heap. The allocated memory is not movable.
 *
 * @param hHeap [in] Handle to the heap from which the memory will be allocated. This parameter is a
 *   handle returned by the HeapCreate or GetProcessHeap function.
 * @param dwFlags [in] Specifies several controllable aspects of heap allocation. Specifying any of
 *   these flags will override the corresponding flag specified when the heap was created with
 *   HeapCreate. You can specify one or more of the following flags: Value Description
 *   HEAP_NO_SERIALIZE Specifies that mutual exclusion will not be used while the HeapAlloc function
 *   is accessing the heap. This flag should not be specified when accessing the process heap. The
 *   system may create additional threads within the application's process that simultaneously access
 *   the process heap. HEAP_ZERO_MEMORY Specifies that the allocated memory will be initialized to
 *   zero. Otherwise, the memory is not initialized to zero.
 * @param dwBytes [in] Specifies the number of bytes to be allocated. If the heap specified by the
 *   hHeap parameter is a "nongrowable" heap, dwBytes must be less than 0x7FFF8. You create a
 *   nongrowable heap by calling the HeapCreate function with a nonzero value.
 *
 * @return A pointer to the allocated memory block indicates success. NULL indicates failure. If the
 *   function fails, it does not call SetLastError. An application cannot call GetLastError for
 *   extended error information.
 *
 * If HeapAlloc succeeds, it allocates at least the amount of memory requested. If the actual amount
 * allocated is greater than the amount requested, the process can use the entire amount. To
 * determine the actual size of the allocated block, use the HeapSize function.
 *
 * To free a block of memory allocated by HeapAlloc, use the HeapFree function.
 *
 * Memory allocated by HeapAlloc is not movable. Since the memory is not movable, it is possible for
 * the heap to become fragmented.
 *
 * Serialization ensures mutual exclusion when two or more threads attempt to simultaneously
 * allocate or free blocks from the same heap. There is a small performance cost to serialization,
 * but it must be used whenever multiple threads allocate and free memory from the same heap.
 * Setting the HEAP_NO_SERIALIZE flag eliminates mutual exclusion on the heap. Without
 * serialization, two or more threads that use the same heap handle might attempt to allocate or
 * free memory simultaneously, likely causing corruption in the heap. The HEAP_NO_SERIALIZE flag
 * can, therefore, be safely used only in the following situations:
 *
 * The process has only one thread.
 *
 * The process has multiple threads, but only one thread calls the heap functions for a specific
 * heap.
 *
 * The process has multiple threads, and the application provides its own mechanism for mutual
 * exclusion to a specific heap.
 */
LPVOID
WINAPI
HeapAlloc(
    HANDLE hHeap,
    DWORD dwFlags,
    DWORD dwBytes
    );

/**
 * This function reallocates a block of memory from a heap. The allocated memory is not movable.
 *
 * @param hHeap [in] Heap from which the memory will be reallocated. This is a handle returned by
 *   the HeapCreate or GetProcessHeap function.
 * @param dwFlags [in] Specifies several controllable aspects of heap reallocation. Specifying any
 *   of these flags overrides the corresponding flag specified in the flOptions parameter when the
 *   heap was created by using the HeapCreate function. You can specify one or more of the following
 *   flags: Value Description HEAP_NO_SERIALIZE Specifies that mutual exclusion is not used while
 *   HeapReAlloc is accessing the heap. This flag should not be specified when accessing the process
 *   heap. The system may create additional threads within the application's process that
 *   simultaneously access the process heap. HEAP_REALLOC_IN_PLACE_ONLY Specifies that there can be no
 *   movement when reallocating a memory block to a larger size. If this flag is not specified and the
 *   reallocation request is for a larger size, the function may move the block to a new location. If
 *   this flag is specified and the block cannot be enlarged without moving, the function fails,
 *   leaving the original memory block unchanged. HEAP_ZERO_MEMORY If the reallocation request is for
 *   a larger size, this flag specifies that the additional region of memory beyond the original size
 *   be initialized to zero. The contents of the memory block up to its original size are unaffected.
 * @param lpMem [in] Pointer to the block of memory that the function reallocates. This pointer is
 *   returned by an earlier call to the HeapAlloc or HeapReAlloc function.
 * @param dwBytes [in] Specifies the new size of the memory block, in bytes. A memory block's size
 *   can be increased or decreased by using this function.
 *
 * @return If the function fails, it calls SetLastError. An application can call GetLastError for
 *   extended error information.
 *
 * If HeapReAlloc succeeds, it allocates at least the amount of memory requested. If the actual
 * amount allocated is greater than the amount requested, the process can use the entire amount. To
 * determine the actual size of the reallocated block, use the HeapSize function.
 *
 * If HeapReAlloc fails, the original memory is not freed, and the original handle and pointer are
 * still valid.
 *
 * To free a block of memory allocated by HeapReAlloc, use the HeapFree function.
 *
 * Serialization ensures mutual exclusion when two or more threads attempt to simultaneously
 * allocate or free blocks from the same heap. There is a small performance cost to serialization,
 * but it must be used whenever multiple threads allocate and free memory from the same heap.
 * Setting the HEAP_NO_SERIALIZE flag eliminates mutual exclusion on the heap. Without
 * serialization, two or more threads that use the same heap handle might attempt to allocate or
 * free memory simultaneously, likely causing corruption in the heap. The HEAP_NO_SERIALIZE flag
 * can, therefore, be safely used only in the following situations:
 *
 * The process has only one thread.
 *
 * The process has multiple threads, but only one thread calls the heap functions for a specific
 * heap.
 *
 * The process has multiple threads, and the application provides its own mechanism for mutual
 * exclusion to a specific heap.
 */
LPVOID
WINAPI
HeapReAlloc(
    HANDLE hHeap,
    DWORD dwFlags,
    LPVOID lpMem,
    DWORD dwBytes
    );

/**
 * This function frees a memory block allocated from a heap by the HeapAlloc or HeapReAlloc
 * function.
 *
 * @param hHeap [in] Handle to the heap whose memory block the function frees. This parameter is a
 *   handle returned by the HeapCreate or GetProcessHeap function.
 * @param dwFlags [in] Specifies several controllable aspects of freeing a memory block. Only one
 *   flag is currently defined; however, all other flag values are reserved for future use. Specifying
 *   this flag will override the corresponding flag specified in the flOptions parameter when the heap
 *   was created by using the HeapCreate function: Value Description HEAP_NO_SERIALIZE Specifies that
 *   mutual exclusion will not be used while HeapFree is accessing the heap. This flag should not be
 *   specified when accessing the process heap. The system may create additional threads within the
 *   application's process that simultaneously access the process heap.
 * @param lpMem [in] Pointer to the memory block to free. This pointer is returned by the HeapAlloc
 *   or HeapReAlloc function.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * Serialization ensures mutual exclusion when two or more threads attempt to simultaneously
 * allocate or free blocks from the same heap. There is a small performance cost to serialization,
 * but it must be used whenever multiple threads allocate and free memory from the same heap.
 * Setting the HEAP_NO_SERIALIZE flag eliminates mutual exclusion on the heap. Without
 * serialization, two or more threads that use the same heap handle might attempt to allocate or
 * free memory simultaneously, likely causing corruption in the heap. The HEAP_NO_SERIALIZE flag
 * can, therefore, be safely used only in the following situations:
 *
 * The process has only one thread.
 *
 * The process has multiple threads, but only one thread calls the heap functions for a specific
 * heap.
 *
 * The process has multiple threads, and the application provides its own mechanism for mutual
 * exclusion to a specific heap.
 */
BOOL
WINAPI
HeapFree(
    HANDLE hHeap,
    DWORD dwFlags,
    LPVOID lpMem
    );

/**
 * This function returns the size, in bytes, of a memory block allocated from a heap by the
 * HeapAlloc or HeapReAlloc function.
 *
 * @param hHeap [in] Handle to the heap in which the memory block resides. This handle is returned
 *   by the HeapCreate or GetProcessHeap function.
 * @param dwFlags [in] Specifies several controllable aspects of accessing the memory block. Only
 *   one flag is currently defined; however, all other flag values are reserved for future use.
 *   Specifying this flag will override the corresponding flag specified in the flOptions parameter
 *   when the heap was created by using the HeapCreate function: Value Description HEAP_NO_SERIALIZE
 *   Specifies that mutual exclusion will not be used while HeapSize is accessing the heap. This flag
 *   should not be specified when accessing the process heap. The system may create additional threads
 *   within the application's process that simultaneously access the process heap.
 * @param lpmem [in] Pointer to the memory block whose size the function will obtain. This is a
 *   pointer returned by the HeapAlloc or HeapReAlloc function.
 *
 * @return The size, in bytes, of the allocated memory block indicates success. 0xFFFFFFFF indicates
 *   failure. The function does not call SetLastError. An application cannot call GetLastError for
 *   extended error information.
 *
 * Serialization ensures mutual exclusion when two or more threads attempt to simultaneously
 * allocate or free blocks from the same heap. There is a small performance cost to serialization,
 * but it must be used whenever multiple threads allocate and free memory from the same heap.
 * Setting the HEAP_NO_SERIALIZE flag eliminates mutual exclusion on the heap. Without
 * serialization, two or more threads that use the same heap handle might attempt to allocate or
 * free memory simultaneously, likely causing corruption in the heap. The HEAP_NO_SERIALIZE flag
 * can, therefore, be safely used only in the following situations:
 *
 * The process has only one thread.
 *
 * The process has multiple threads, but only one thread calls the heap functions for a specific
 * heap.
 *
 * The process has multiple threads, and the application provides its own mechanism for mutual
 * exclusion to a specific heap.
 */
DWORD
WINAPI
HeapSize(
    HANDLE hHeap,
    DWORD dwFlags,
    LPCVOID lpMem
    );

BOOL
WINAPI
HeapValidate(
    HANDLE hHeap,
    DWORD dwFlags,
    LPCVOID lpMem
    );

// @CESYSGEN ENDIF

/**
 * This function sends a string to the debugger for the current application.
 *
 * @param lpOutputString Pointer to the null-terminated string to be displayed.
 *
 * @return None.
 *
 * Windows CE supports only the Unicode version of this function.
 *
 * If the application has no debugger, the system debugger displays the string. If the application
 * has no debugger and the system debugger is not active, OutputDebugString does nothing.
 */
VOID
WINAPI
OutputDebugStringA(
    LPCSTR lpOutputString
    );

/**
 * This function sends a string to the debugger for the current application.
 *
 * @param lpOutputString Pointer to the null-terminated string to be displayed.
 *
 * @return None.
 *
 * Windows CE supports only the Unicode version of this function.
 *
 * If the application has no debugger, the system debugger displays the string. If the application
 * has no debugger and the system debugger is not active, OutputDebugString does nothing.
 */
VOID
WINAPI
OutputDebugStringW(
    LPCWSTR lpOutputString
    );
#ifdef UNICODE
/**
 * This function sends a string to the debugger for the current application.
 *
 * @param lpOutputString Pointer to the null-terminated string to be displayed.
 *
 * @return None.
 *
 * Windows CE supports only the Unicode version of this function.
 *
 * If the application has no debugger, the system debugger displays the string. If the application
 * has no debugger and the system debugger is not active, OutputDebugString does nothing.
 */
#define OutputDebugString  OutputDebugStringW
#else
/**
 * This function sends a string to the debugger for the current application.
 *
 * @param lpOutputString Pointer to the null-terminated string to be displayed.
 *
 * @return None.
 *
 * Windows CE supports only the Unicode version of this function.
 *
 * If the application has no debugger, the system debugger displays the string. If the application
 * has no debugger and the system debugger is not active, OutputDebugString does nothing.
 */
#define OutputDebugString  OutputDebugStringA
#endif // !UNICODE

VOID SignalStarted(DWORD dw);

/**
 * This function retrieves the current value of the high-resolution performance counter if one is
 * provided by the OEM.
 *
 * @param lpPerformanceCount Pointer to a variable that the function sets, in counts, to the current
 *   performance-counter value. If the installed hardware does not support a high-resolution
 *   performance counter, this parameter can be to zero.
 *
 * @return Nonzero indicates that the installed hardware supports a high-resolution performance
 *   counter. Zero indicates that the installed hardware does not support a high-resolution
 *   performance counter.
 */
BOOL
WINAPI
QueryPerformanceCounter(
    LARGE_INTEGER *lpPerformanceCount
    );

/**
 * This function retrieves the frequency of the high-resolution performance counter if one is
 * provided by the OEM.
 *
 * @param lpFrequency Pointer to a variable that the function sets, in counts per second, to the
 *   current performance-counter frequency. If the installed hardware does not support a
 *   high-resolution performance counter, this parameter can be to zero.
 *
 * @return Nonzero indicates that the installed hardware supports a high-resolution performance
 *   counter. Zero indicates that the installed hardware does not support a high-resolution
 *   performance counter.
 */
BOOL
WINAPI
QueryPerformanceFrequency(
    LARGE_INTEGER *lpFrequency
    );

#define VER_PLATFORM_WIN32s             0
#define VER_PLATFORM_WIN32_WINDOWS      1
#define VER_PLATFORM_WIN32_NT           2
#define VER_PLATFORM_WIN32_HH           3
#define VER_PLATFORM_WIN32_CE           3

/**
 * This structure contains operating system version information. The information includes major and
 * minor version numbers, a build number, a platform identifier, and descriptive text about the
 * operating system. This structure is used with the GetVersionEx function.
 */
typedef struct _OSVERSIONINFO{
    /**
     * Specifies the size, in bytes, of this data structure. Set this member to sizeof(OSVERSIONINFO)
     * before calling the GetVersionEx function.
     */
    DWORD dwOSVersionInfoSize;
    /**
     * Identifies the major version number of the operating system. For example, for Windows CE version
     * 2.10, the major version number is 2.
     */
    DWORD dwMajorVersion;
    /**
     * Identifies the minor version number of the operating system. For example, for Windows CE version
     * 2.10, the minor version number is 1.
     */
    DWORD dwMinorVersion;
    /**
     * Identifies the build number of the operating system or is set to 0.
     */
    DWORD dwBuildNumber;
    /**
     * Identifies the operating system platform. This member can be one of the following values:
     *
     * - VER_PLATFORM_WIN32s: Win32s on Windows 3.1.
     *
     * - VER_PLATFORM_WIN32_WINDOWS: Win32 on Windows 95 or Windows 98. For Windows 95, dwMinorVersion
     * is zero. For Windows 98, dwMinorVersion is greater than zero.
     *
     * - VER_PLATFORM_WIN32_NT: Win32 on Windows NT.
     *
     * - VER_PLATFORM_WIN32_CE: Win32 on Windows CE.
     */
    DWORD dwPlatformId;
    /**
     * Null-terminated string that provides arbitrary additional information about the operating system.
     */
    WCHAR szCSDVersion[ 128 ];
} OSVERSIONINFO, *LPOSVERSIONINFO;

/**
 * This function obtains extended information about the version of the operating system that is
 * currently running. A remote application interface (RAPI) version of this function exists, and it
 * is named CeGetVersionEx
 *
 * @param lpVersionInformation [out] Pointer to an OSVERSIONINFO data structure that the function
 *   fills with operating system version information. Before calling the GetVersionEx function, set
 *   the dwOSVersionInfoSize member of the OSVERSIONINFO data structure to sizeof(OSVERSIONINFO).
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError. The function fails if you specify an invalid value for the dwOSVersionInfoSize
 *   member of the OSVERSIONINFO.
 *
 * When using the GetVersionEx function to determine whether your application is running on a
 * particular version of the operating system, check for version numbers that are greater than or
 * equal to the desired version numbers. This ensures that the test succeeds for later versions of
 * the operating system. For example, if your application requires Windows 98, use the following
 * test:
 *
 *     GetVersionEx (&osvi);
 *     bIsWindows98orLater =
 *        (osvi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) &&
 *        ( (osvi.dwMajorVersion > 4) ||
 *        ( (osvi.dwMajorVersion == 4) && (osvi.dwMinorVersion > 0) ) );
 *
 * Identifying the current operating system is usually not the best way to determine whether a
 * particular operating system feature is present. This is because the operating system may have had
 * new features added in a redistributable DLL. Rather than using GetVersionEx to determine the
 * operating system platform or version number, test for the presence of the feature itself.
 *
 * To determine the best way to test for a feature, refer to the documentation for the feature of
 * interest. The following list discusses some common techniques for feature detection:
 *
 * You can test for the presence of the functions associated with a feature. To test for the
 * presence of a function in a system DLL, call the LoadLibrary function to load the DLL. Then call
 * the GetProcAddress function to determine whether the function of interest is present in the DLL.
 * Use the pointer returned by GetProcAddress to call the function. Note that even if the function
 * is present, it may be a stub that just returns an error code such as ERROR_CALL_NOT_IMPLEMENTED.
 *
 * You can determine the presence of some features by using the GetSystemMetrics function. For
 * example, you can detect multiple display monitors by calling GetSystemMetrics(SM_CMONITORS).
 *
 * There are several versions of the redistributable DLLs that implement shell and common control
 * features.
 *
 * The value of the dwPlatformID member of the OSVERSIONINFO structure will be
 * VER_PLATFORM_WIN32_CE.
 *
 * When writing applications for Windows CE 2.01 running on a Japanese H/PC, be aware that the
 * toolbar indicates that the version is 2.0.
 *
 * For the Auto PC version 1.0, GetLastError returns of the following error values:
 *
 * - ERROR_INVALID_HANDLE: The supplied pointer is NULL.
 *
 * - ERROR_INVALID_DATA
 *
 * The structure is not properly initialized; the size is set incorrectly.
 */
BOOL
WINAPI 
GetVersionEx(
	LPOSVERSIONINFO lpver
	);

/**
 * This structure contains information about the current computer system. This includes the
 * processor type, page size, original equipment manufacturer (OEM) identifier, and other such
 * information.
 */
typedef struct _SYSTEM_INFO {
    union {
        /**
         * An obsolete member that is not used by Windows CE.
         */
        DWORD dwOemId;          // Obsolete field...do not use
        struct {
            /**
             * Specifies the system's processor architecture. It is no longer relevant. Use the
             * wProcessorArchitecture, wProcessorLevel, and wProcessorRevision members to determine the type of
             * processor.
             *
             * PROCESSOR_ARCHITECTURE_INTEL
             *
             * PROCESSOR_ARCHITECTURE_MIPS
             *
             * PROCESSOR_ARCHITECTURE_ALPHA
             *
             * PROCESSOR_ARCHITECTURE_PPC
             *
             * PROCESSOR_ARCHITECTURE_UNKNOWN
             */
            WORD wProcessorArchitecture;
            WORD wReserved;
        };
    };
    /**
     * Specifies the page size and the granularity of page protection and commitment. This is the page
     * size used by the VirtualAlloc function.
     */
    DWORD dwPageSize;
    /**
     * Pointer to the lowest memory address accessible to applications and dynamic-link libraries
     * (DLLs).
     */
    LPVOID lpMinimumApplicationAddress;
    /**
     * Pointer to the highest memory address accessible to applications and DLLs.
     */
    LPVOID lpMaximumApplicationAddress;
    /**
     * Specifies a mask representing the set of processors configured into the system. Bit 0 is
     * processor 0; bit 31 is processor 31.
     */
    DWORD dwActiveProcessorMask;
    /**
     * Specifies the number of processors in the system.
     */
    DWORD dwNumberOfProcessors;
    /**
     * Specifies the type of processor in the system. This member is no longer relevant. Use the
     * wProcessorArchitecture, wProcessorLevel, and wProcessorRevision members to determine the type of
     * processor.
     *
     * This member is one of the following values:
     *
     * PROCESSOR_INTEL_386
     *
     * PROCESSOR_INTEL_486
     *
     * PROCESSOR_INTEL_PENTIUM
     *
     * PROCESSOR_INTEL_486
     *
     * PROCESSOR_MIPS_R3000
     *
     * PROCESSOR_MIPS_R4000
     *
     * PROCESSOR_HITACHI_SH3
     *
     * PROCESSOR_HITACHI_SH4
     *
     * PROCESSOR_PPC_403
     *
     * PROCESSOR_PPC_821
     *
     * PROCESSOR_STRONGARM
     *
     * PROCESSOR_ARM720
     */
    DWORD dwProcessorType;
    /**
     * Specifies the granularity with which virtual memory is allocated. For example, a VirtualAlloc
     * request to allocate 1 byte will reserve an address space of dwAllocationGranularity bytes. This
     * value was hard coded as 64K in the past, but other hardware architectures may require different
     * values.
     */
    DWORD dwAllocationGranularity;
    /**
     * Specifies the system's architecture-dependent processor level.
     *
     * If wProcessorArchitecture is PROCESSOR_ARCHITECTURE_INTEL, wProcessorLevel can be one of the
     * following values:
     *
     * - 4: Intel 80486
     *
     * - 5: Pentium If wProcessorArchitecture is PROCESSOR_ARCHITECTURE_MIPS, wProcessorLevel is of the
     * form 00XX, where XX is an 8-bit implementation number (bits 8-15 of the PRId register). The
     * member can be the following value:
     *
     * - 3: MIPS R3000
     *
     * - 0004: MIPS R4000 If wProcessorArchitecture is PROCESSOR_ARCHITECTURE_PPC, wProcessorLevel is of
     * the form XXXX, where XXXXis a 16-bit processor version number (the high-order 16 bits of the
     * Processor Version Register).
     */
    WORD wProcessorLevel;
    /**
     * Specifies an architecture-dependent processor revision. The following table shows how the
     * revision value is assembled for each type of processor architecture.
     *
     * - Intel 80386 or 80486: A value of the form xxyz. If xx is equal to 0xFF, y - 0xA is the model
     * number, and z is the stepping identifier. For example, an Intel 80486-D0 system returns 0xFFD0.
     * If xx is not equal to 0xFF, xx + 'A' is the stepping letter and yz is the minor stepping.
     *
     * - Intel Pentium, Cyrix, or NextGen 586: A value of the form xxyy, where xx is the model number
     * and yy is the stepping. For example, a value of 0x0201 indicates Model 2, Stepping 1.
     *
     * - MIPS: A value of the form 00xx, where xx is the 8-bit revision number of the processor (the
     * low-order 8 bits of the PRId register).
     *
     * - ALPHA: A value of the form xxyy, where xxyy is the low-order 16 bits of the processor revision
     * number from the firmware. Display this value as follows: Model 'A'+xx, Pass yy
     *
     * - PPC: A value of the form xxyy, where xxyy is the low-order 16 bits of the Processor Version
     * Register. Display this value as a fixed point number: xx.yy
     */
    WORD wProcessorRevision;
} SYSTEM_INFO, *LPSYSTEM_INFO;

/**
 * This function maps the specified .DLL file into the address space of the calling process.
 *
 * @param lpLibFileName Pointer to a null-terminated string that names the .DLL file. The name
 *   specified is the filename of the module and is not related to the name stored in the library
 *   module itself, as specified by the LIBRARY keyword in the module-definition (.DEF) file. If the
 *   string specifies a path but the file does not exist in the specified directory, the function
 *   fails. When specifying a path, be sure to use backslashes (\), not forward slashes (/). If the
 *   string does not specify a path, the function uses a standard search strategy to find the file.
 *   See the Remarks for more information.
 *
 * @return A handle to the module indicates success. NULL indicates failure. To get extended error
 *   information, call GetLastError.
 *
 * LoadLibrary can be used to map a DLL module and return a handle that can be used in
 * GetProcAddress to get the address of a DLL function. Do not use LoadLibrary to load or "run" a
 * .exe file.
 *
 * If the module is a DLL not already mapped for the calling process, the system calls the DLL's
 * DllMain function with the DLL_PROCESS_ATTACH value. In Windows CE, a DLL is loaded once, but then
 * it is mapped into each processes address space when a process implicitly or explicitly loads the
 * library with the LoadLibrary function. When Windows CE loads a DLL, all path information is
 * ignored when determining if the DLL is already loaded. This means that a DLL with the same name
 * but a different path can only be loaded once. In addition, a module ending with the extension
 * ".CPL" is treated as if the extension if ".DLL".
 *
 * It is not safe to call LoadLibrary from DllMain.
 *
 * Module handles are not global or inheritable. A call to LoadLibrary by one process does not
 * produce a handle that another process can use-for example, in calling GetProcAddress. The other
 * process must make its own call to LoadLibrary for the module before calling GetProcAddress.
 *
 * If no filename extension is specified in the lpLibFileName parameter, the default library
 * extension .DLL is appended. However, the filename string can include a trailing point character
 * (.) to indicate that the module name has no extension.
 *
 * When no path is specified, the function searches for loaded modules whose base name matches the
 * base name of the module to be loaded. If the name matches, the load succeeds. Otherwise, the
 * function searches for the file in the following sequence:
 *
 * The absolute path specified by the lpLibFileName parameter
 *
 * ROM for statically-linked .DDL files
 *
 * The .EXE launch directory
 *
 * The windows (\windows) directory
 *
 * The root (\) directory
 *
 * An OEM-dependent directory
 *
 * The OEM-defined shell (\ppshell) directory-Embedded Toolkit users only
 *
 * Windows CE versions 1.0 through 2.01 search the following path for the module:
 *
 * The root directory of the PC Card RAM expansion card, if one exists.
 *
 * The windows directory (\Windows).
 *
 * The root directory (\).
 */
HINSTANCE
WINAPI
LoadLibraryA(
    LPCSTR lpLibFileName
    );

/**
 * This function maps the specified .DLL file into the address space of the calling process.
 *
 * @param lpLibFileName Pointer to a null-terminated string that names the .DLL file. The name
 *   specified is the filename of the module and is not related to the name stored in the library
 *   module itself, as specified by the LIBRARY keyword in the module-definition (.DEF) file. If the
 *   string specifies a path but the file does not exist in the specified directory, the function
 *   fails. When specifying a path, be sure to use backslashes (\), not forward slashes (/). If the
 *   string does not specify a path, the function uses a standard search strategy to find the file.
 *   See the Remarks for more information.
 *
 * @return A handle to the module indicates success. NULL indicates failure. To get extended error
 *   information, call GetLastError.
 *
 * LoadLibrary can be used to map a DLL module and return a handle that can be used in
 * GetProcAddress to get the address of a DLL function. Do not use LoadLibrary to load or "run" a
 * .exe file.
 *
 * If the module is a DLL not already mapped for the calling process, the system calls the DLL's
 * DllMain function with the DLL_PROCESS_ATTACH value. In Windows CE, a DLL is loaded once, but then
 * it is mapped into each processes address space when a process implicitly or explicitly loads the
 * library with the LoadLibrary function. When Windows CE loads a DLL, all path information is
 * ignored when determining if the DLL is already loaded. This means that a DLL with the same name
 * but a different path can only be loaded once. In addition, a module ending with the extension
 * ".CPL" is treated as if the extension if ".DLL".
 *
 * It is not safe to call LoadLibrary from DllMain.
 *
 * Module handles are not global or inheritable. A call to LoadLibrary by one process does not
 * produce a handle that another process can use-for example, in calling GetProcAddress. The other
 * process must make its own call to LoadLibrary for the module before calling GetProcAddress.
 *
 * If no filename extension is specified in the lpLibFileName parameter, the default library
 * extension .DLL is appended. However, the filename string can include a trailing point character
 * (.) to indicate that the module name has no extension.
 *
 * When no path is specified, the function searches for loaded modules whose base name matches the
 * base name of the module to be loaded. If the name matches, the load succeeds. Otherwise, the
 * function searches for the file in the following sequence:
 *
 * The absolute path specified by the lpLibFileName parameter
 *
 * ROM for statically-linked .DDL files
 *
 * The .EXE launch directory
 *
 * The windows (\windows) directory
 *
 * The root (\) directory
 *
 * An OEM-dependent directory
 *
 * The OEM-defined shell (\ppshell) directory-Embedded Toolkit users only
 *
 * Windows CE versions 1.0 through 2.01 search the following path for the module:
 *
 * The root directory of the PC Card RAM expansion card, if one exists.
 *
 * The windows directory (\Windows).
 *
 * The root directory (\).
 */
HINSTANCE
WINAPI
LoadLibraryW(
    LPCWSTR lpLibFileName
    );
#ifdef UNICODE
/**
 * This function maps the specified .DLL file into the address space of the calling process.
 *
 * @param lpLibFileName Pointer to a null-terminated string that names the .DLL file. The name
 *   specified is the filename of the module and is not related to the name stored in the library
 *   module itself, as specified by the LIBRARY keyword in the module-definition (.DEF) file. If the
 *   string specifies a path but the file does not exist in the specified directory, the function
 *   fails. When specifying a path, be sure to use backslashes (\), not forward slashes (/). If the
 *   string does not specify a path, the function uses a standard search strategy to find the file.
 *   See the Remarks for more information.
 *
 * @return A handle to the module indicates success. NULL indicates failure. To get extended error
 *   information, call GetLastError.
 *
 * LoadLibrary can be used to map a DLL module and return a handle that can be used in
 * GetProcAddress to get the address of a DLL function. Do not use LoadLibrary to load or "run" a
 * .exe file.
 *
 * If the module is a DLL not already mapped for the calling process, the system calls the DLL's
 * DllMain function with the DLL_PROCESS_ATTACH value. In Windows CE, a DLL is loaded once, but then
 * it is mapped into each processes address space when a process implicitly or explicitly loads the
 * library with the LoadLibrary function. When Windows CE loads a DLL, all path information is
 * ignored when determining if the DLL is already loaded. This means that a DLL with the same name
 * but a different path can only be loaded once. In addition, a module ending with the extension
 * ".CPL" is treated as if the extension if ".DLL".
 *
 * It is not safe to call LoadLibrary from DllMain.
 *
 * Module handles are not global or inheritable. A call to LoadLibrary by one process does not
 * produce a handle that another process can use-for example, in calling GetProcAddress. The other
 * process must make its own call to LoadLibrary for the module before calling GetProcAddress.
 *
 * If no filename extension is specified in the lpLibFileName parameter, the default library
 * extension .DLL is appended. However, the filename string can include a trailing point character
 * (.) to indicate that the module name has no extension.
 *
 * When no path is specified, the function searches for loaded modules whose base name matches the
 * base name of the module to be loaded. If the name matches, the load succeeds. Otherwise, the
 * function searches for the file in the following sequence:
 *
 * The absolute path specified by the lpLibFileName parameter
 *
 * ROM for statically-linked .DDL files
 *
 * The .EXE launch directory
 *
 * The windows (\windows) directory
 *
 * The root (\) directory
 *
 * An OEM-dependent directory
 *
 * The OEM-defined shell (\ppshell) directory-Embedded Toolkit users only
 *
 * Windows CE versions 1.0 through 2.01 search the following path for the module:
 *
 * The root directory of the PC Card RAM expansion card, if one exists.
 *
 * The windows directory (\Windows).
 *
 * The root directory (\).
 */
#define LoadLibrary  LoadLibraryW
#else
/**
 * This function maps the specified .DLL file into the address space of the calling process.
 *
 * @param lpLibFileName Pointer to a null-terminated string that names the .DLL file. The name
 *   specified is the filename of the module and is not related to the name stored in the library
 *   module itself, as specified by the LIBRARY keyword in the module-definition (.DEF) file. If the
 *   string specifies a path but the file does not exist in the specified directory, the function
 *   fails. When specifying a path, be sure to use backslashes (\), not forward slashes (/). If the
 *   string does not specify a path, the function uses a standard search strategy to find the file.
 *   See the Remarks for more information.
 *
 * @return A handle to the module indicates success. NULL indicates failure. To get extended error
 *   information, call GetLastError.
 *
 * LoadLibrary can be used to map a DLL module and return a handle that can be used in
 * GetProcAddress to get the address of a DLL function. Do not use LoadLibrary to load or "run" a
 * .exe file.
 *
 * If the module is a DLL not already mapped for the calling process, the system calls the DLL's
 * DllMain function with the DLL_PROCESS_ATTACH value. In Windows CE, a DLL is loaded once, but then
 * it is mapped into each processes address space when a process implicitly or explicitly loads the
 * library with the LoadLibrary function. When Windows CE loads a DLL, all path information is
 * ignored when determining if the DLL is already loaded. This means that a DLL with the same name
 * but a different path can only be loaded once. In addition, a module ending with the extension
 * ".CPL" is treated as if the extension if ".DLL".
 *
 * It is not safe to call LoadLibrary from DllMain.
 *
 * Module handles are not global or inheritable. A call to LoadLibrary by one process does not
 * produce a handle that another process can use-for example, in calling GetProcAddress. The other
 * process must make its own call to LoadLibrary for the module before calling GetProcAddress.
 *
 * If no filename extension is specified in the lpLibFileName parameter, the default library
 * extension .DLL is appended. However, the filename string can include a trailing point character
 * (.) to indicate that the module name has no extension.
 *
 * When no path is specified, the function searches for loaded modules whose base name matches the
 * base name of the module to be loaded. If the name matches, the load succeeds. Otherwise, the
 * function searches for the file in the following sequence:
 *
 * The absolute path specified by the lpLibFileName parameter
 *
 * ROM for statically-linked .DDL files
 *
 * The .EXE launch directory
 *
 * The windows (\windows) directory
 *
 * The root (\) directory
 *
 * An OEM-dependent directory
 *
 * The OEM-defined shell (\ppshell) directory-Embedded Toolkit users only
 *
 * Windows CE versions 1.0 through 2.01 search the following path for the module:
 *
 * The root directory of the PC Card RAM expansion card, if one exists.
 *
 * The windows directory (\Windows).
 *
 * The root directory (\).
 */
#define LoadLibrary  LoadLibraryA
#endif // !UNICODE

/**
 * This function gets a module file name.
 *
 * @param hModule [in] Handle to the module whose executable filename is being requested. If this
 *   parameter is NULL, GetModuleFileName returns the path for the file used to create the calling
 *   process.
 * @param lpFilename [out] Pointer to a buffer that is filled in with the path and file name of the
 *   given module.
 * @param nSize [in] Specifies the length, in characters, of the lpFilename buffer. If the length of
 *   the path and file name exceeds this limit, the string is truncated.
 *
 * @return The length, in characters, of the string copied to the buffer indicates success. Zero
 *   indicates failure. To get extended error information, call GetLastError.
 *
 * In Windows CE, a DLL is loaded from only one location by the system.
 */
WINBASEAPI
DWORD
WINAPI
GetModuleFileNameA(
    HMODULE hModule,
    LPSTR lpFilename,
    DWORD nSize
    );
/**
 * This function gets a module file name.
 *
 * @param hModule [in] Handle to the module whose executable filename is being requested. If this
 *   parameter is NULL, GetModuleFileName returns the path for the file used to create the calling
 *   process.
 * @param lpFilename [out] Pointer to a buffer that is filled in with the path and file name of the
 *   given module.
 * @param nSize [in] Specifies the length, in characters, of the lpFilename buffer. If the length of
 *   the path and file name exceeds this limit, the string is truncated.
 *
 * @return The length, in characters, of the string copied to the buffer indicates success. Zero
 *   indicates failure. To get extended error information, call GetLastError.
 *
 * In Windows CE, a DLL is loaded from only one location by the system.
 */
WINBASEAPI
DWORD
WINAPI
GetModuleFileNameW(
    HMODULE hModule,
    LPWSTR lpFilename,
    DWORD nSize
    );
#ifdef UNICODE
/**
 * This function gets a module file name.
 *
 * @param hModule [in] Handle to the module whose executable filename is being requested. If this
 *   parameter is NULL, GetModuleFileName returns the path for the file used to create the calling
 *   process.
 * @param lpFilename [out] Pointer to a buffer that is filled in with the path and file name of the
 *   given module.
 * @param nSize [in] Specifies the length, in characters, of the lpFilename buffer. If the length of
 *   the path and file name exceeds this limit, the string is truncated.
 *
 * @return The length, in characters, of the string copied to the buffer indicates success. Zero
 *   indicates failure. To get extended error information, call GetLastError.
 *
 * In Windows CE, a DLL is loaded from only one location by the system.
 */
#define GetModuleFileName  GetModuleFileNameW
#else
/**
 * This function gets a module file name.
 *
 * @param hModule [in] Handle to the module whose executable filename is being requested. If this
 *   parameter is NULL, GetModuleFileName returns the path for the file used to create the calling
 *   process.
 * @param lpFilename [out] Pointer to a buffer that is filled in with the path and file name of the
 *   given module.
 * @param nSize [in] Specifies the length, in characters, of the lpFilename buffer. If the length of
 *   the path and file name exceeds this limit, the string is truncated.
 *
 * @return The length, in characters, of the string copied to the buffer indicates success. Zero
 *   indicates failure. To get extended error information, call GetLastError.
 *
 * In Windows CE, a DLL is loaded from only one location by the system.
 */
#define GetModuleFileName  GetModuleFileNameA
#endif // !UNICODE

#define PAGE_NOACCESS          0x01
#define PAGE_READONLY          0x02
#define PAGE_READWRITE         0x04
#define PAGE_WRITECOPY         0x08
#define PAGE_EXECUTE           0x10
#define PAGE_EXECUTE_READ      0x20
#define PAGE_EXECUTE_READWRITE 0x40
#define PAGE_EXECUTE_WRITECOPY 0x80
#define PAGE_GUARD            0x100
#define PAGE_NOCACHE          0x200
#define MEM_COMMIT           0x1000
#define MEM_RESERVE          0x2000
#define MEM_DECOMMIT         0x4000
#define MEM_RELEASE          0x8000
#define MEM_FREE            0x10000
#define MEM_PRIVATE         0x20000
#define MEM_MAPPED          0x40000
#define MEM_TOP_DOWN       0x100000
#define MEM_AUTO_COMMIT    0x200000

//
//  File structures
//

/**
 * This structure contains data used in asynchronous I/O.
 */
typedef struct _OVERLAPPED {
    /**
     * Reserved for operating system use
     */
    DWORD   Internal;
    /**
     * Reserved for operating system use
     */
    DWORD   InternalHigh;
    /**
     * Specifies a file position at which to start the transfer. The file position is a byte offset from
     * the start of the file.
     */
    DWORD   Offset;
    /**
     * Specifies the high word of the byte offset at which to start the transfer. This member is ignored
     * when reading from or writing to named pipes and communications devices.
     */
    DWORD   OffsetHigh;
    /**
     * Handle to an event set to the signaled state when the transfer has been completed.
     */
    HANDLE  hEvent;
} OVERLAPPED, *LPOVERLAPPED;

typedef struct _SECURITY_ATTRIBUTES {
    DWORD nLength;
    LPVOID lpSecurityDescriptor;
    BOOL bInheritHandle;
} SECURITY_ATTRIBUTES, *PSECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;

typedef DWORD (WINAPI *LPTHREAD_START_ROUTINE)(LPVOID pvarg);

typedef LPTHREAD_START_ROUTINE PTHREAD_START_ROUTINE;

#define DEBUG_PROCESS               0x00000001
#define DEBUG_ONLY_THIS_PROCESS     0x00000002

#define THREAD_PRIORITY_TIME_CRITICAL   0
#define THREAD_PRIORITY_HIGHEST         1
#define THREAD_PRIORITY_ABOVE_NORMAL    2
#define THREAD_PRIORITY_NORMAL          3
#define THREAD_PRIORITY_BELOW_NORMAL    4
#define THREAD_PRIORITY_LOWEST          5
#define THREAD_PRIORITY_ABOVE_IDLE      6
#define THREAD_PRIORITY_IDLE            7

#define THREAD_PRIORITY_ERROR_RETURN    (MAXLONG)

#define EXCEPTION_DEBUG_EVENT       1
#define CREATE_THREAD_DEBUG_EVENT   2
#define CREATE_PROCESS_DEBUG_EVENT  3
#define EXIT_THREAD_DEBUG_EVENT     4
#define EXIT_PROCESS_DEBUG_EVENT    5
#define LOAD_DLL_DEBUG_EVENT        6
#define UNLOAD_DLL_DEBUG_EVENT      7
#define OUTPUT_DEBUG_STRING_EVENT   8
#define RIP_EVENT                   9

/**
 * This structure contains exception information that can be used by a debugger.
 */
typedef struct _EXCEPTION_DEBUG_INFO {
    /**
     * Contains an EXCEPTION_RECORD structure with information specific to the exception. This includes
     * the exception code, flags, address, a pointer to a related exception, extra parameters, and so
     * on.
     */
    EXCEPTION_RECORD ExceptionRecord;
    /**
     * Indicates whether the debugger has previously encountered the exception specified by the
     * ExceptionRecord member. If the dwFirstChance member is nonzero, this is the first time the
     * debugger has encountered the exception. Debuggers typically handle breakpoint and single-step
     * exceptions when they are first encountered. If this member is zero, the debugger has previously
     * encountered the exception. This occurs only if, during the search for structured exception
     * handlers, either no handler was found or the exception was continued.
     */
    DWORD dwFirstChance;
} EXCEPTION_DEBUG_INFO, *LPEXCEPTION_DEBUG_INFO;

/**
 * This structure contains thread-creation information that can be used by a debugger.
 */
typedef struct _CREATE_THREAD_DEBUG_INFO {
    /**
     * Handle to the thread whose creation caused the debugging event. If this member is NULL, the
     * handle is not valid. Otherwise, the debugger has THREAD_GET_CONTEXT, THREAD_SET_CONTEXT, and
     * THREAD_SUSPEND_RESUME access to the thread, allowing the debugger to read from and write to the
     * registers of the thread and control execution of the thread.
     */
    HANDLE hThread;
    /**
     * Pointer to a block of data. At offset 0x2C into this block is another pointer, called
     * ThreadLocalStoragePointer, that points to an array of per-module thread local storage blocks.
     * This gives a debugger access to per-thread data in the threads of the process being debugged
     * using the same algorithms that a compiler would use.
     */
    LPVOID lpThreadLocalBase;
    /**
     * Pointer to the starting address of the thread. This value may only be an approximation of the
     * thread's starting address, because any application with appropriate access to the thread can
     * change the thread's context by using the SetThreadContext function.
     */
    LPTHREAD_START_ROUTINE lpStartAddress;
} CREATE_THREAD_DEBUG_INFO, *LPCREATE_THREAD_DEBUG_INFO;

/**
 * This structure contains process creation information that can be used by a debugger.
 *
 * The lpImageName member is a pointer into the address space of the process that is being debugged.
 * To retrieve the actual image name, use the ReadProcessMemory function in the following manner.
 *
 *     ReadProcessMemory( hProcess, lpImageName, lpBuffer, nSize,
 *        &NumberOfBytesRead );
 *
 * For the DebugActiveProcess function, if the dwDebugEventCode member of the DEBUG_EVENT structure
 * has a value of CREATE_PROCESS_DEBUG_EVENT or CREATE_THREAD_DEBUG_EVENT, the lpStartAddress member
 * is NULL.
 *
 * The lpThreadLocalBase member points directly to the Thread Local Storage (TLS) data block of the
 * process that is being debugged. To obtain the TLS data for a slot, call the ReadProcessMemory
 * function and pass the following calculated value for the lpBaseAddress parameter:
 * lpThreadLocalBase+4*<slot number>.
 */
typedef struct _CREATE_PROCESS_DEBUG_INFO {
    /**
     * Handle to the process's image file. In Windows CE, this member is always NULL.
     */
    HANDLE hFile;
    /**
     * Handle to the process. If this member is NULL, the handle is not valid. Otherwise, the debugger
     * can use the member to read from and write to the process's memory.
     */
    HANDLE hProcess;
    /**
     * Handle to the initial thread of the process identified by the hProcess member. If hThread is
     * NULL, the handle is not valid. Otherwise, the debugger has THREAD_GET_CONTEXT,
     * THREAD_SET_CONTEXT, and THREAD_SUSPEND_RESUME access to the thread, allowing the debugger to read
     * from and write to the registers of the thread and to control execution of the thread.
     */
    HANDLE hThread;
    /**
     * Pointer to the base address of the executable image that the process is running.
     */
    LPVOID lpBaseOfImage;
    /**
     * Specifies the offset to the debugging information in the file identified by the hFile member.
     * This member is always set to zero.
     */
    DWORD dwDebugInfoFileOffset;
    /**
     * Specifies the size, in bytes, of the debugging information in the file. This member is always set
     * to zero.
     */
    DWORD nDebugInfoSize;
    /**
     * Pointer to a block of data. At offset 0x2C into this block is another pointer, called
     * ThreadLocalStoragePointer, that points to an array of per-module thread local storage blocks.
     * This gives a debugger access to per-thread data in the threads of the process being debugged
     * using the same algorithms that a compiler would use.
     */
    LPVOID lpThreadLocalBase;
    /**
     * Pointer to the starting address of the thread. This value may only be an approximation of the
     * thread's starting address, because any application with appropriate access to the thread can
     * change the thread's context by using the SetThreadContext function.
     */
    LPTHREAD_START_ROUTINE lpStartAddress;
    /**
     * Pointer to the file name associated with the hFile member. This member may be NULL, or it may
     * contain the address of a string pointer in the address space of the process being debugged. That
     * address may, in turn, either be NULL or point to the actual filename. If fUnicode is a nonzero
     * value, the name string is Unicode; otherwise, it is ANSI.
     *
     * This member is strictly optional. Debuggers must be prepared to handle the case where lpImageName
     * is NULL or *lpImageName (in the address space of the process being debugged) is NULL.
     * Specifically, the system does not provide an image name for a create process event, and will not
     * likely pass an image name for the first DLL event. The system also does not provide this
     * information in the case of debug events that originate from a call to the DebugActiveProcess
     * function.
     */
    LPVOID lpImageName;
    /**
     * Indicates whether a file name specified by the lpImageName member is Unicode or ANSI. A nonzero
     * value indicates Unicode; zero indicates ANSI.
     */
    WORD fUnicode;
} CREATE_PROCESS_DEBUG_INFO, *LPCREATE_PROCESS_DEBUG_INFO;

/**
 * This structure contains an exiting thread's exit code.
 */
typedef struct _EXIT_THREAD_DEBUG_INFO {
    /**
     * Specifies the exit code for the thread.
     */
    DWORD dwExitCode;
} EXIT_THREAD_DEBUG_INFO, *LPEXIT_THREAD_DEBUG_INFO;

/**
 * This structure contains an exiting process's exit code.
 */
typedef struct _EXIT_PROCESS_DEBUG_INFO {
    /**
     * Specifies the exit code for the process.
     */
    DWORD dwExitCode;
} EXIT_PROCESS_DEBUG_INFO, *LPEXIT_PROCESS_DEBUG_INFO;

/**
 * This structure contains information about a dynamic-link library (DLL) that has just been loaded.
 */
typedef struct _LOAD_DLL_DEBUG_INFO {
    /**
     * Ignored. Set to NULL.
     */
    HANDLE hFile;
    /**
     * Long pointer to the base address of the DLL in the address space of the process loading the DLL.
     */
    LPVOID lpBaseOfDll;
    /**
     * Ignored. Must be 0.
     */
    DWORD dwDebugInfoFileOffset;
    /**
     * Ignored. Must be 0.
     */
    DWORD nDebugInfoSize;
    /**
     * Long pointer to the address space of the process that is being debugged. Use the
     * ReadProcessMemory function to retrieve the actual image name.
     *
     * This member is strictly optional. Debuggers must be prepared to handle the case where lpImageName
     * is NULL or *lpImageName (in the address space of the process being debugged) is NULL.
     * Specifically, the system will never provide an image name for a create process event, and it will
     * not likely pass an image name for the first DLL event. The system will also never provide this
     * information in the case of debugging events that originate from a call to the DebugActiveProcess
     * function.
     */
    LPVOID lpImageName;
    /**
     * Indicates whether a filename specified by lpImageName is Unicode or ANSI. A nonzero value for
     * this member indicates Unicode; zero indicates ANSI.
     */
    WORD fUnicode;
} LOAD_DLL_DEBUG_INFO, *LPLOAD_DLL_DEBUG_INFO;

/**
 * This structure contains information about a dynamic-link library (DLL) that has just been
 * unloaded.
 */
typedef struct _UNLOAD_DLL_DEBUG_INFO {
    /**
     * Long pointer to the base address of the DLL in the address space of the process unloading the
     * DLL.
     */
    LPVOID lpBaseOfDll;
} UNLOAD_DLL_DEBUG_INFO, *LPUNLOAD_DLL_DEBUG_INFO;

/**
 * This structure contains the address, format, and length, in bytes, of a debugging string.
 */
typedef struct _OUTPUT_DEBUG_STRING_INFO {
    /**
     * Pointer to the debugging string in the calling process's address space. The debugger can use the
     * ReadProcessMemory function to retrieve the value of the string.
     */
    LPSTR lpDebugStringData;
    /**
     * Specifies the format of the debugging string. If this member is zero, the debugging string is
     * 8-bit ASCII; if it is nonzero, the string is 16-bit Unicode(TM).
     */
    WORD fUnicode;
    /**
     * Specifies the length, in bytes, of the debugging string. The length includes the string's
     * terminating null character.
     */
    WORD nDebugStringLength;
} OUTPUT_DEBUG_STRING_INFO, *LPOUTPUT_DEBUG_STRING_INFO;

typedef struct _RIP_INFO {
    DWORD dwError;
    DWORD dwType;
} RIP_INFO, *LPRIP_INFO;

/**
 * This structure describes a debugging event.
 *
 * If the WaitForDebugEvent function succeeds, it fills in the members of a DEBUG_EVENT structure.
 */
typedef struct _DEBUG_EVENT {
    /**
     * Specifies a debugging event code that identifies the type of debugging event. It is one of the
     * following values: Value Description EXCEPTION_DEBUG_EVENT Reports an exception debugging event.
     * The value of u.Exception specifies an EXCEPTION_DEBUG_INFO structure. CREATE_THREAD_DEBUG_EVENT
     * Reports a create-thread debugging event. The value of u.CreateThread specifies a
     * CREATE_THREAD_DEBUG_INFO structure. CREATE_PROCESS_DEBUG_EVENT Reports a create-process debugging
     * event. The value of u.CreateProcessInfo specifies a CREATE_PROCESS_DEBUG_INFO structure.
     * EXIT_THREAD_DEBUG_EVENT Reports an exit-thread debugging event. The value of u.ExitThread
     * specifies an EXIT_THREAD_DEBUG_INFO structure. EXIT_PROCESS_DEBUG_EVENT Reports an exit-process
     * debugging event. The value of u.ExitProcess specifies an EXIT_PROCESS_DEBUG_INFO structure.
     * LOAD_DLL_DEBUG_EVENT Reports a load-dynamic-link-library (DLL) debugging event. The value of
     * u.LoadDll specifies a LOAD_DLL_DEBUG_INFO structure. UNLOAD_DLL_DEBUG_EVENT Reports an unload-DLL
     * debugging event. The value of u.UnloadDll specifies an UNLOAD_DLL_DEBUG_INFO structure.
     * OUTPUT_DEBUG_STRING_EVENT Reports an output-debugging-string debugging event. The value of
     * u.DebugString specifies an OUTPUT_DEBUG_STRING_INFO structure.
     */
    DWORD dwDebugEventCode;
    /**
     * Specifies the identifier of the process in which the debugging event occurred. A debugger uses
     * this value to locate the debugger's per-process structure. These values are not necessarily small
     * integers that can be used as table indices.
     */
    DWORD dwProcessId;
    /**
     * Specifies the identifier of the thread in which the debugging event occurred. A debugger uses
     * this value to locate the debugger's per-thread structure. These values are not necessarily small
     * integers that can be used as table indices.
     */
    DWORD dwThreadId;
    union {
        EXCEPTION_DEBUG_INFO Exception;
        CREATE_THREAD_DEBUG_INFO CreateThread;
        CREATE_PROCESS_DEBUG_INFO CreateProcessInfo;
        EXIT_THREAD_DEBUG_INFO ExitThread;
        EXIT_PROCESS_DEBUG_INFO ExitProcess;
        LOAD_DLL_DEBUG_INFO LoadDll;
        UNLOAD_DLL_DEBUG_INFO UnloadDll;
        OUTPUT_DEBUG_STRING_INFO DebugString;
        RIP_INFO RipInfo;
    /**
     * Specifies additional information relating to the debugging event. This union takes on the type
     * and value appropriate to the type of debugging event, as described in the dwDebugEventCode
     * member.
     */
    } u;
} DEBUG_EVENT, *LPDEBUG_EVENT;
#define WAIT_OBJECT_0   	0x00000000L
#define WAIT_ABANDONED  	0x00000080L
#define WAIT_ABANDONED_0	0x00000080L
#define WAIT_TIMEOUT    	0x00000102L
#define WAIT_FAILED         0xffffffffL
#define INFINITE            0xffffffffL

typedef PCONTEXT LPCONTEXT;

#ifdef UNDER_NT
typedef struct _RTL_CRITICAL_SECTION_DEBUG {
    WORD   Type;
    WORD   CreatorBackTraceIndex;
    struct _RTL_CRITICAL_SECTION *CriticalSection;
    LIST_ENTRY ProcessLocksList;
    DWORD EntryCount;
    DWORD ContentionCount;
    DWORD Spare[ 2 ];
} RTL_CRITICAL_SECTION_DEBUG, *PRTL_CRITICAL_SECTION_DEBUG;

typedef struct _RTL_CRITICAL_SECTION {
    PRTL_CRITICAL_SECTION_DEBUG DebugInfo;

    //
    //  The following three fields control entering and exiting the critical
    //  section for the resource
    //

    LONG LockCount;
    LONG RecursionCount;
    HANDLE OwningThread;        // from the thread's ClientId->UniqueThread
    HANDLE LockSemaphore;
    DWORD Reserved;
} RTL_CRITICAL_SECTION, *PRTL_CRITICAL_SECTION;

typedef RTL_CRITICAL_SECTION CRITICAL_SECTION;
typedef PRTL_CRITICAL_SECTION PCRITICAL_SECTION;
typedef PRTL_CRITICAL_SECTION LPCRITICAL_SECTION;

#else

typedef struct CRITICAL_SECTION {
    unsigned int LockCount;         /* Nesting count on critical section */
    HANDLE OwnerThread;         	/* Handle of owner thread */
    HANDLE hCrit;					/* Handle to this critical section */
    DWORD needtrap;					/* Trap in when freeing critical section */
    DWORD dwReserved;				/* currently unused */
} CRITICAL_SECTION, *LPCRITICAL_SECTION;
#endif

/**
 * This function waits for ownership of the specified critical section object. The function returns
 * when the calling thread is granted ownership.
 *
 * @param lpCriticalSection [in] Pointer to the critical section object.
 *
 * @return None.
 *
 * The threads of a single process can use a critical section object for mutual-exclusion
 * synchronization. The process is responsible for allocating the memory used by a critical section
 * object, which it can do by declaring a variable of type CRITICAL_SECTION. Before using a critical
 * section, some thread of the process must call the InitializeCriticalSection to initialize the
 * object.
 *
 * To enable mutually exclusive access to a shared resource, each thread calls the
 * EnterCriticalSection function to request ownership of the critical section before executing any
 * section of code that accesses the protected resource. EnterCriticalSection blocks until the
 * thread can take ownership of the critical section. When it has finished executing the protected
 * code, the thread uses the LeaveCriticalSection function to relinquish ownership, enabling another
 * thread to become owner and access the protected resource. The thread must call
 * LeaveCriticalSection once for each time that it entered the critical section. The thread enters
 * the critical section each time EnterCriticalSection succeeds.
 *
 * After a thread has ownership of a critical section, it can make additional calls to
 * EnterCriticalSection without blocking its execution. This prevents a thread from deadlocking
 * itself while waiting for a critical section that it already owns.
 *
 * Any thread of the process can use the DeleteCriticalSection function to release the system
 * resources that were allocated when the critical section object was initialized. After this
 * function has been called, the critical section object can no longer be used for synchronization.
 *
 * If a thread terminates while it has ownership of a critical section, the state of the critical
 * section is undefined.
 *
 * If a critical section is deleted while it is still owned, the state of the threads waiting for
 * ownership of the deleted critical section is undefined.
 */
VOID
WINAPI
EnterCriticalSection (
    LPCRITICAL_SECTION pcsCriticalSection
    );

/**
 * This function releases ownership of the specified critical section object.
 *
 * @param lpCriticalSection [in] Pointer to the critical section object.
 *
 * @return None.
 *
 * The threads of a single process can use a critical-section object for mutual-exclusion
 * synchronization. The process is responsible for allocating the memory used by a critical-section
 * object, which it can do by declaring a variable of type CRITICAL_SECTION. Before using a critical
 * section, some thread of the process must call the InitializeCriticalSection function to
 * initialize the object.
 *
 * A thread uses the EnterCriticalSection function to acquire ownership of a critical section
 * object. To release its ownership, the thread must call LeaveCriticalSection once for each time
 * that it entered the critical section.
 *
 * If a thread calls LeaveCriticalSection when it does not have ownership of the specified critical
 * section object, an error occurs that may cause another thread using EnterCriticalSection to wait
 * indefinitely.
 *
 * Any thread of the process can use the DeleteCriticalSection function to release the system
 * resources that were allocated when the critical section object was initialized. After this
 * function has been called, the critical section object can no longer be used for synchronization.
 */
VOID
WINAPI
LeaveCriticalSection (
    LPCRITICAL_SECTION pcsCriticalSection
    );

/**
 * This function initializes a critical section object.
 *
 * @param lpCriticalSection [in] Pointer to the critical section object.
 *
 * @return None.
 *
 * The threads of a single process can use a critical section object for mutual-exclusion
 * synchronization. There is no guarantee about the order in which threads will obtain ownership of
 * the critical section, however, the system will be fair to all threads.
 *
 * The process is responsible for allocating the memory used by a critical section object, which it
 * can do by declaring a variable of type CRITICAL_SECTION. Before using a critical section, some
 * thread of the process must call the InitializeCriticalSection function to initialize the object.
 *
 * Once a critical section object has been initialized, the threads of the process can specify the
 * object in the EnterCriticalSection or LeaveCriticalSection function to provide mutually exclusive
 * access to a shared resource. For similar synchronization between the threads of different
 * processes, use a mutex object.
 *
 * A critical section object cannot be moved or copied. The process must also not modify the object,
 * but must treat it as logically opaque. Use only the critical section functions provided by the
 * Win32 API to manage critical section objects.
 *
 * In low memory situations, InitializeCriticalSection can raise a STATUS_NO_MEMORY exception.
 */
VOID
WINAPI
InitializeCriticalSection (
    LPCRITICAL_SECTION pcsCriticalSection
    );

/**
 * This function releases all resources used by an unowned critical section object.
 *
 * @param lpCriticalSection [in] Pointer to the critical section object.
 *
 * @return None.
 *
 * Deleting a critical section object releases all system resources used by the object. Once
 * deleted, the critical section object cannot be specified in the EnterCriticalSection,
 * TryEnterCriticalSection, or LeaveCriticalSection function.
 *
 * If a critical section is deleted while it is still owned, the state of the threads waiting for
 * ownership of the deleted critical section is undefined.
 */
VOID
WINAPI
DeleteCriticalSection (
    LPCRITICAL_SECTION pcsCriticalSection
    );

/**
 * This function waits for a debugging event to occur in a process being debugged.
 *
 * @param lpDebugEvent Pointer to a DEBUG_EVENT structure that is filled with information about the
 *   debugging event.
 * @param dwMilliseconds Specifies the number of milliseconds to wait for a debugging event. If this
 *   parameter is zero, the function tests for a debugging event and returns immediately. If the
 *   parameter is INFINITE, the function does not return until a debugging event has occurred.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * Only the thread that created the process being debugged can call WaitForDebugEvent.
 */
BOOL
WINAPI
WaitForDebugEvent(
    LPDEBUG_EVENT lpDebugEvent,
    DWORD dwMilliseconds
    );

/**
 * This function enables a debugger to continue a thread that previously reported a debugging event.
 *
 * @param dwProcessId Specifies the handle to the process to continue.
 * @param dwThreadId Specifies the handle to the thread to continue. The combination of process
 *   identifier and thread identifier must identify a thread that has previously reported a debugging
 *   event.
 * @param dwContinueStatus Specifies how to continue the thread that reported the debugging event.
 *   If the DBG_CONTINUE flag is specified for this parameter and the thread specified by the
 *   dwThreadId parameter previously reported an EXCEPTION_DEBUG_EVENT debugging event, the function
 *   stops all exception processing and continues the thread. For any other debugging event, this flag
 *   simply continues the thread. If the DBG_EXCEPTION_NOT_HANDLED flag is specified for this
 *   parameter and the thread specified by dwThreadId previously reported an EXCEPTION_DEBUG_EVENT
 *   debugging event, the function continues exception processing. If this is a first-chance exception
 *   event, the search and dispatch logic of the structured exception handler is used; otherwise, the
 *   process is terminated. For any other debugging event, this flag simply continues the thread.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * Only the thread that created dwProcessId with the CreateProcess function can call
 * ContinueDebugEvent.
 *
 * After the ContinueDebugEvent function succeeds, the specified thread continues. Depending on the
 * debugging event previously reported by the thread, different actions occur. If the continued
 * thread previously reported an EXIT_THREAD_DEBUG_EVENT debugging event, ContinueDebugEvent closes
 * the handle the debugger has to the thread. If the continued thread previously reported an
 * EXIT_PROCESS_DEBUG_EVENT debugging event, ContinueDebugEvent closes the handles the debugger has
 * to the process and to the thread.
 */
BOOL
WINAPI
ContinueDebugEvent(
    DWORD dwProcessId,
    DWORD dwThreadId,
    DWORD dwContinueStatus
    );

/**
 * This function allows a debugger to attach to an active process and then debug it.
 *
 * @param dwProcessId Specifies the identifier for the process to be debugged. The debugger gets
 *   debugging access to the process as if it created the process with the DEBUG_ONLY_THIS_PROCESS
 *   flag. See the Remarks section for more details.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * After a successful return from DebugActiveProcess, when the debugger is waiting for debug events
 * using the WaitForDebugEvent function, the system sends a CREATE_PROCESS_DEBUG_EVENT debugging
 * event that identifies the primary thread handle that is currently part of the process. The system
 * sends an individual CREATE_THREAD_DEBUG_EVENT debugging event for each of the secondary thread
 * handles that are currently part of the process. All of these handles have permission (that is,
 * access rights) for getting and setting thread contexts using the GetThreadContext and
 * SetThreadContext functions.
 *
 * For both the CREATE_PROCESS_DEBUG_EVENT and CREATE_THREAD_DEBUG_EVENT debugging events, the
 * lpStartAddress member of the CREATE_PROCESS_DEBUG_INFO structure is NULL.
 *
 * Close each of these thread handles using the CloseHandle function.
 *
 * No initial debug breakpoint is set when DebugActiveProcess successfully attaches.
 *
 * Windows CE versions 2.0 and later provide built in support for Just-In-Time (JIT) debugging. A
 * JIT debugger is registered by placing the name of your debugger in the string registry value
 * JITDebugger located at HKEY_LOCAL_MACHINE\Debug. To enable JIT, you must perform a warm reset on
 * the Windows CE target platform after the above value is added to the registry. When your debugger
 * is invoked by JIT, the process identifier of the debugee is passed on the command line. The
 * Windows CE JIT is a First-Chance exception handler and not a Second-Chance exception handler
 * which is available on Windows NT.
 *
 * The debugger must have appropriate access to the target process; it must be able to open the
 * process for PROCESS_ALL_ACCESS access. On Windows CE, the debugger has appropriate access if the
 * process identifier is valid.
 *
 * After the system checks the process identifier and determines that a valid debugging attachment
 * is being made, the function returns TRUE. The debugger is then expected to wait for debugging
 * events by using the WaitForDebugEvent function. The system suspends all threads in the process
 * and sends the debugger events representing the current state of the process.
 *
 * For each dynamic-link library (DLL) currently loaded into the address space of the target
 * process, the system sends a LOAD_DLL_DEBUG_EVENT debugging event. The system arranges for the
 * first thread in the process to execute a breakpoint instruction after it resumes. Continuing this
 * thread causes it to return to whatever it was doing before the debugger was attached.
 *
 * After all of this has been done, the system resumes all threads in the process. When the first
 * thread in the process resumes, it executes a breakpoint instruction that causes an
 * EXCEPTION_DEBUG_EVENT debugging event to be sent to the debugger. All future debugging events are
 * sent to the debugger by using the normal mechanism and rules.
 */
BOOL
WINAPI
DebugActiveProcess(
    DWORD dwProcessId
    );

/**
 * This function maps a view of a file into the address space of the calling process.
 *
 * @param hFileMappingObject Handle to an open handle of a file-mapping object. The
 *   CreateFileMapping function returns this handle.
 * @param dwDesiredAccess Specifies the type of access to the file view and, therefore, the
 *   protection of the pages mapped by the file. This parameter can be one of the following values:
 *   Value Description FILE_MAP_WRITE Read-write access. The hFileMappingObject parameter must have
 *   been created with PAGE_READWRITE protection. A read-write view of the file is mapped.
 *   FILE_MAP_READ Read-only access. The hFileMappingObject parameter must have been created with
 *   PAGE_READWRITE or PAGE_READONLY protection. A read-only view of the file is mapped.
 *   FILE_MAP_ALL_ACCESS Same as FILE_MAP_WRITE. FILE_MAP_COPY Copy on write access. If you create the
 *   map with PAGE_WRITECOPY and the view with FILE_MAP_COPY, you will receive a view to file. If you
 *   write to it, the pages are automatically swappable and the modifications you make will not go to
 *   the original data file. Windows 95: You must pass PAGE_WRITECOPY to CreateFileMapping; otherwise,
 *   an error will be returned. Windows NT: There is no restriction as to how the hFileMappingObject
 *   parameter must be created. Copy on write is valid for any type of view.
 * @param dwFileOffsetHigh Specifies the high-order 32 bits of the file offset where mapping is to
 *   begin.
 * @param dwFileOffsetLow Specifies the low-order 32 bits of the file offset where mapping is to
 *   begin. The combination of the high and low offsets must specify an offset within the file that
 *   matches the system's memory allocation granularity, or the function fails. That is, the offset
 *   must be a multiple of the allocation granularity. Use the GetSystemInfo function, which fills in
 *   the members of a SYSTEM_INFO structure, to obtain the system's memory allocation granularity.
 * @param dwNumberOfBytesToMap Specifies the number of bytes of the file to map. If
 *   dwNumberOfBytesToMap is zero, the entire file is mapped.
 *
 * @return The starting address of the mapped view indicates success. NULL indicates failure. To get
 *   extended error information, call GetLastError.
 *
 * The 64 KB alignment is not required for the dwFileOffsetLow parameter.
 *
 * Mapping a file makes the specified portion of the file visible in the address space of the
 * calling process.
 *
 * Multiple views of a file (or a file-mapping object and its mapped file) are said to be "coherent"
 * if they contain identical data at a specified time. This occurs if the file views are derived
 * from the same file-mapping object. A process can duplicate a file-mapping object handle into
 * another process by using the DuplicateHandle function, or another process can open a file-mapping
 * object by name by using the OpenFileMapping function.
 *
 * A mapped view of a file is not guaranteed to be coherent with a file being accessed by the
 * ReadFile or WriteFile function.
 *
 * Windows 95: MapViewOfFile may require the swapfile to grow. If the swapfile cannot grow, the
 * function fails.
 *
 * Windows NT: If the file-mapping object is backed by the paging file (handle = 0xFFFFFFFF), the
 * paging file must be large enough to hold the entire mapping. If it is not, MapViewOfFile fails.
 *
 * Note To guard against an access violation, use structured exception handling to protect any code
 * that writes to or reads from a memory mapped view.
 */
LPVOID
WINAPI
MapViewOfFile(
    HANDLE hFileMappingObject,
    DWORD dwDesiredAccess,
    DWORD dwFileOffsetHigh,
    DWORD dwFileOffsetLow,
    DWORD dwNumberOfBytesToMap
    );

/**
 * This function unmaps a mapped view of a file from the calling process's address space.
 *
 * @param lpBaseAddress Pointer to the base address of the mapped view of a file that is to be
 *   unmapped. This value must be identical to the value returned by a previous call to the
 *   MapViewOfFile function.
 *
 * @return Nonzero indicates success. All dirty pages within the specified range are written
 *   "lazily" to disk. Zero indicates failure. To get extended error information, call GetLastError.
 *
 * Although an application may close the file handle used to create a file mapping object, the
 * system holds the corresponding file open until the last view of the file is unmapped.
 */
BOOL
WINAPI
UnmapViewOfFile(
    LPCVOID lpBaseAddress
    );

/**
 * This function writes to the disk a byte range within a mapped view of a file.
 *
 * @param lpBaseAddress Pointer to the base address of the byte range to be flushed to the disk
 *   representation of the mapped file.
 * @param dwNumberOfBytesToFlush Specifies the number of bytes to flush. This parameter cannot be
 *   set to zero.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * Flushing a range of a mapped view causes any dirty pages within that range to be written to the
 * disk. Dirty pages are those whose contents have changed since the file view was mapped.
 *
 * When flushing a memory-mapped file over a network, FlushViewOfFile guarantees that the data has
 * been written from the local computer, but not that the data resides on the remote computer. The
 * server can cache the data on the remote side. Therefore, FlushViewOfFile can return before the
 * data has been physically written to disk. However, you can cause FlushViewOfFile to return only
 * when the physical write is complete by specifying the FILE_FLAG_WRITE_THROUGH flag when you open
 * the file with the CreateFile function.
 */
WINBASEAPI
BOOL
WINAPI
FlushViewOfFile(
    LPCVOID lpBaseAddress,
    DWORD dwNumberOfBytesToFlush
    );

/**
 * This function creates a named or unnamed file-mapping object for the specified file.
 *
 * @param hFile Handle to the file from which to create a mapping object. The file must be opened
 *   with an access mode compatible with the protection flags specified by the flProtect parameter. It
 *   is recommended, though not required, that files you intend to map be opened for exclusive access.
 *   If hFile is (HANDLE)0xFFFFFFFF, the calling process must also specify a mapping object size in
 *   the dwMaximumSizeHigh and dwMaximumSizeLow parameters. The function creates a file-mapping object
 *   of the specified size backed by physical memory rather than by a named file in the file system.
 *   The file-mapping object can be shared by name. In Windows CE, memory utilized for the mapping
 *   object is not part of the 32 MB virtual process space.
 * @param lpFileMappingAttributes Ignored. Must be NULL.
 * @param flProtect Specifies the protection desired for the file view, when the file is mapped.
 *   This parameter can be one of the following values: Value Description PAGE_READONLY Gives
 *   read-only access to the committed region of pages. An attempt to write to or execute the
 *   committed region results in an access violation. The file specified by the hFile parameter must
 *   have been created with GENERIC_READ access. You cannot specify PAGE_READONLY without a file
 *   handle. PAGE_READWRITE Gives read-write access to the committed region of pages. The file
 *   specified by hFile must have been created with GENERIC_READ and GENERIC_WRITE access.
 *   PAGE_WRITECOPY Not supported. In addition, an application can specify certain section attributes
 *   by combining (using the bitwise OR operator) one or more of the following section attribute
 *   values with one of the preceding page protection values: Value Description SEC_COMMIT Allocates
 *   physical storage in memory or in the paging file on disk for all pages of a section. This is the
 *   default setting. SEC_IMAGE Not supported. SEC_NOCACHE Not supported. SEC_RESERVE Not supported.
 * @param dwMaximumSizeHigh Specifies the high-order 32 bits of the maximum size of the file-mapping
 *   object.
 * @param dwMaximumSizeLow Specifies the low-order 32 bits of the maximum size of the file-mapping
 *   object. If this parameter and dwMaximumSizeHig are zero, the maximum size of the file-mapping
 *   object is equal to the current size of the file identified by hFile.
 * @param lpName Long pointer to a null-terminated string specifying the name of the mapping object.
 *   The name can contain any character except the backslash character (\). If this parameter matches
 *   the name of an existing named mapping object, the function requests access to the mapping object
 *   with the protection specified by flProtect. If this parameter is NULL, the mapping object is
 *   created without a name. If lpName matches the name of an existing event, semaphore, mutex,
 *   waitable timer, or job, the function fails and the GetLastError function returns
 *   ERROR_INVALID_HANDLE. This occurs because these objects share the same name space.
 *
 * @return A handle to the file-mapping object indicates success. If the object existed before the
 *   function call, the function returns a handle to the existing object - with its current size, not
 *   the specified size - and GetLastError returns ERROR_ALREADY_EXISTS. NULL indicates failure. To
 *   get extended error information, call GetLastError.
 *
 * If you call CreateFileMapping with a handle from CreateFileForMapping and it fails for any
 * reason, the handle is closed.
 *
 * This function will not work on a Windows CE-based platform that does not support Page-In.
 *
 * After a file-mapping object has been created, the size of the file must not exceed the size of
 * the file-mapping object; if it does, not all of the file's contents will be available for
 * sharing.
 *
 * If an application specifies a size for the file-mapping object that is larger than the size of
 * the actual named file on disk, the file on disk is grown to match the specified size of the
 * file-mapping object. If the file cannot be grown, this results in a failure to create the
 * file-mapping object. GetLastError will return ERROR_DISK_FULL.
 *
 * The handle that CreateFileMapping returns has full access to the new file-mapping object. It can
 * be used with any function that requires a handle to a file-mapping object. File-mapping objects
 * can be shared through process creation.
 *
 * File handles that have been used to create file-mapping objects must not be used in subsequent
 * calls to file I/O functions, such as ReadFile and WriteFile. In general, if a file handle has
 * been used in a successful call to the CreateFileMapping function, do not use that handle unless
 * you first close the corresponding file-mapping object.
 *
 * Creating a file-mapping object creates the potential for mapping a view of the file but does not
 * map the view. The MapViewOfFile function maps a view of a file into the address space of a
 * process.
 *
 * With one important exception, file views derived from a single file-mapping object are coherent,
 * or identical, at a given time. If multiple processes have handles of the same file-mapping
 * object, they see a coherent view of the data when they map a view of the file.
 *
 * The exception has to do with remote files. Although CreateFileMapping works with remote files, it
 * does not keep them coherent. For example, if two computers both map a file as writeable, and both
 * change the same page, each computer will only see its own writes to the page. When the data gets
 * updated on the disk, it is not merged.
 *
 * A mapped file and a file accessed by means of the input and output (I/O) functions (ReadFile and
 * WriteFile) are not necessarily coherent.
 *
 * To fully close a file mapping object, an application must unmap all mapped views of the file
 * mapping object by calling UnmapViewOfFile, and close the file mapping object handle by calling
 * CloseHandle. The order in which these functions are called does not matter. The call to
 * UnmapViewOfFile is necessary because mapped views of a file mapping object maintain internal open
 * handles to the object, and a file mapping object will not close until all open handles to it are
 * closed.
 *
 * Note To guard against an access violation, use structured exception handling to protect any code
 * that writes to or reads from a memory mapped view.
 */
WINBASEAPI
HANDLE
WINAPI
CreateFileMappingA(
    HANDLE hFile,
    LPSECURITY_ATTRIBUTES lpFileMappingAttributes,
    DWORD flProtect,
    DWORD dwMaximumSizeHigh,
    DWORD dwMaximumSizeLow,
    LPCSTR lpName
    );

/**
 * This function creates a named or unnamed file-mapping object for the specified file.
 *
 * @param hFile Handle to the file from which to create a mapping object. The file must be opened
 *   with an access mode compatible with the protection flags specified by the flProtect parameter. It
 *   is recommended, though not required, that files you intend to map be opened for exclusive access.
 *   If hFile is (HANDLE)0xFFFFFFFF, the calling process must also specify a mapping object size in
 *   the dwMaximumSizeHigh and dwMaximumSizeLow parameters. The function creates a file-mapping object
 *   of the specified size backed by physical memory rather than by a named file in the file system.
 *   The file-mapping object can be shared by name. In Windows CE, memory utilized for the mapping
 *   object is not part of the 32 MB virtual process space.
 * @param lpFileMappingAttributes Ignored. Must be NULL.
 * @param flProtect Specifies the protection desired for the file view, when the file is mapped.
 *   This parameter can be one of the following values: Value Description PAGE_READONLY Gives
 *   read-only access to the committed region of pages. An attempt to write to or execute the
 *   committed region results in an access violation. The file specified by the hFile parameter must
 *   have been created with GENERIC_READ access. You cannot specify PAGE_READONLY without a file
 *   handle. PAGE_READWRITE Gives read-write access to the committed region of pages. The file
 *   specified by hFile must have been created with GENERIC_READ and GENERIC_WRITE access.
 *   PAGE_WRITECOPY Not supported. In addition, an application can specify certain section attributes
 *   by combining (using the bitwise OR operator) one or more of the following section attribute
 *   values with one of the preceding page protection values: Value Description SEC_COMMIT Allocates
 *   physical storage in memory or in the paging file on disk for all pages of a section. This is the
 *   default setting. SEC_IMAGE Not supported. SEC_NOCACHE Not supported. SEC_RESERVE Not supported.
 * @param dwMaximumSizeHigh Specifies the high-order 32 bits of the maximum size of the file-mapping
 *   object.
 * @param dwMaximumSizeLow Specifies the low-order 32 bits of the maximum size of the file-mapping
 *   object. If this parameter and dwMaximumSizeHig are zero, the maximum size of the file-mapping
 *   object is equal to the current size of the file identified by hFile.
 * @param lpName Long pointer to a null-terminated string specifying the name of the mapping object.
 *   The name can contain any character except the backslash character (\). If this parameter matches
 *   the name of an existing named mapping object, the function requests access to the mapping object
 *   with the protection specified by flProtect. If this parameter is NULL, the mapping object is
 *   created without a name. If lpName matches the name of an existing event, semaphore, mutex,
 *   waitable timer, or job, the function fails and the GetLastError function returns
 *   ERROR_INVALID_HANDLE. This occurs because these objects share the same name space.
 *
 * @return A handle to the file-mapping object indicates success. If the object existed before the
 *   function call, the function returns a handle to the existing object - with its current size, not
 *   the specified size - and GetLastError returns ERROR_ALREADY_EXISTS. NULL indicates failure. To
 *   get extended error information, call GetLastError.
 *
 * If you call CreateFileMapping with a handle from CreateFileForMapping and it fails for any
 * reason, the handle is closed.
 *
 * This function will not work on a Windows CE-based platform that does not support Page-In.
 *
 * After a file-mapping object has been created, the size of the file must not exceed the size of
 * the file-mapping object; if it does, not all of the file's contents will be available for
 * sharing.
 *
 * If an application specifies a size for the file-mapping object that is larger than the size of
 * the actual named file on disk, the file on disk is grown to match the specified size of the
 * file-mapping object. If the file cannot be grown, this results in a failure to create the
 * file-mapping object. GetLastError will return ERROR_DISK_FULL.
 *
 * The handle that CreateFileMapping returns has full access to the new file-mapping object. It can
 * be used with any function that requires a handle to a file-mapping object. File-mapping objects
 * can be shared through process creation.
 *
 * File handles that have been used to create file-mapping objects must not be used in subsequent
 * calls to file I/O functions, such as ReadFile and WriteFile. In general, if a file handle has
 * been used in a successful call to the CreateFileMapping function, do not use that handle unless
 * you first close the corresponding file-mapping object.
 *
 * Creating a file-mapping object creates the potential for mapping a view of the file but does not
 * map the view. The MapViewOfFile function maps a view of a file into the address space of a
 * process.
 *
 * With one important exception, file views derived from a single file-mapping object are coherent,
 * or identical, at a given time. If multiple processes have handles of the same file-mapping
 * object, they see a coherent view of the data when they map a view of the file.
 *
 * The exception has to do with remote files. Although CreateFileMapping works with remote files, it
 * does not keep them coherent. For example, if two computers both map a file as writeable, and both
 * change the same page, each computer will only see its own writes to the page. When the data gets
 * updated on the disk, it is not merged.
 *
 * A mapped file and a file accessed by means of the input and output (I/O) functions (ReadFile and
 * WriteFile) are not necessarily coherent.
 *
 * To fully close a file mapping object, an application must unmap all mapped views of the file
 * mapping object by calling UnmapViewOfFile, and close the file mapping object handle by calling
 * CloseHandle. The order in which these functions are called does not matter. The call to
 * UnmapViewOfFile is necessary because mapped views of a file mapping object maintain internal open
 * handles to the object, and a file mapping object will not close until all open handles to it are
 * closed.
 *
 * Note To guard against an access violation, use structured exception handling to protect any code
 * that writes to or reads from a memory mapped view.
 */
WINBASEAPI
HANDLE
WINAPI
CreateFileMappingW(
    HANDLE hFile,
    LPSECURITY_ATTRIBUTES lpFileMappingAttributes,
    DWORD flProtect,
    DWORD dwMaximumSizeHigh,
    DWORD dwMaximumSizeLow,
    LPCWSTR lpName
    );

#ifdef UNICODE
/**
 * This function creates a named or unnamed file-mapping object for the specified file.
 *
 * @param hFile Handle to the file from which to create a mapping object. The file must be opened
 *   with an access mode compatible with the protection flags specified by the flProtect parameter. It
 *   is recommended, though not required, that files you intend to map be opened for exclusive access.
 *   If hFile is (HANDLE)0xFFFFFFFF, the calling process must also specify a mapping object size in
 *   the dwMaximumSizeHigh and dwMaximumSizeLow parameters. The function creates a file-mapping object
 *   of the specified size backed by physical memory rather than by a named file in the file system.
 *   The file-mapping object can be shared by name. In Windows CE, memory utilized for the mapping
 *   object is not part of the 32 MB virtual process space.
 * @param lpFileMappingAttributes Ignored. Must be NULL.
 * @param flProtect Specifies the protection desired for the file view, when the file is mapped.
 *   This parameter can be one of the following values: Value Description PAGE_READONLY Gives
 *   read-only access to the committed region of pages. An attempt to write to or execute the
 *   committed region results in an access violation. The file specified by the hFile parameter must
 *   have been created with GENERIC_READ access. You cannot specify PAGE_READONLY without a file
 *   handle. PAGE_READWRITE Gives read-write access to the committed region of pages. The file
 *   specified by hFile must have been created with GENERIC_READ and GENERIC_WRITE access.
 *   PAGE_WRITECOPY Not supported. In addition, an application can specify certain section attributes
 *   by combining (using the bitwise OR operator) one or more of the following section attribute
 *   values with one of the preceding page protection values: Value Description SEC_COMMIT Allocates
 *   physical storage in memory or in the paging file on disk for all pages of a section. This is the
 *   default setting. SEC_IMAGE Not supported. SEC_NOCACHE Not supported. SEC_RESERVE Not supported.
 * @param dwMaximumSizeHigh Specifies the high-order 32 bits of the maximum size of the file-mapping
 *   object.
 * @param dwMaximumSizeLow Specifies the low-order 32 bits of the maximum size of the file-mapping
 *   object. If this parameter and dwMaximumSizeHig are zero, the maximum size of the file-mapping
 *   object is equal to the current size of the file identified by hFile.
 * @param lpName Long pointer to a null-terminated string specifying the name of the mapping object.
 *   The name can contain any character except the backslash character (\). If this parameter matches
 *   the name of an existing named mapping object, the function requests access to the mapping object
 *   with the protection specified by flProtect. If this parameter is NULL, the mapping object is
 *   created without a name. If lpName matches the name of an existing event, semaphore, mutex,
 *   waitable timer, or job, the function fails and the GetLastError function returns
 *   ERROR_INVALID_HANDLE. This occurs because these objects share the same name space.
 *
 * @return A handle to the file-mapping object indicates success. If the object existed before the
 *   function call, the function returns a handle to the existing object - with its current size, not
 *   the specified size - and GetLastError returns ERROR_ALREADY_EXISTS. NULL indicates failure. To
 *   get extended error information, call GetLastError.
 *
 * If you call CreateFileMapping with a handle from CreateFileForMapping and it fails for any
 * reason, the handle is closed.
 *
 * This function will not work on a Windows CE-based platform that does not support Page-In.
 *
 * After a file-mapping object has been created, the size of the file must not exceed the size of
 * the file-mapping object; if it does, not all of the file's contents will be available for
 * sharing.
 *
 * If an application specifies a size for the file-mapping object that is larger than the size of
 * the actual named file on disk, the file on disk is grown to match the specified size of the
 * file-mapping object. If the file cannot be grown, this results in a failure to create the
 * file-mapping object. GetLastError will return ERROR_DISK_FULL.
 *
 * The handle that CreateFileMapping returns has full access to the new file-mapping object. It can
 * be used with any function that requires a handle to a file-mapping object. File-mapping objects
 * can be shared through process creation.
 *
 * File handles that have been used to create file-mapping objects must not be used in subsequent
 * calls to file I/O functions, such as ReadFile and WriteFile. In general, if a file handle has
 * been used in a successful call to the CreateFileMapping function, do not use that handle unless
 * you first close the corresponding file-mapping object.
 *
 * Creating a file-mapping object creates the potential for mapping a view of the file but does not
 * map the view. The MapViewOfFile function maps a view of a file into the address space of a
 * process.
 *
 * With one important exception, file views derived from a single file-mapping object are coherent,
 * or identical, at a given time. If multiple processes have handles of the same file-mapping
 * object, they see a coherent view of the data when they map a view of the file.
 *
 * The exception has to do with remote files. Although CreateFileMapping works with remote files, it
 * does not keep them coherent. For example, if two computers both map a file as writeable, and both
 * change the same page, each computer will only see its own writes to the page. When the data gets
 * updated on the disk, it is not merged.
 *
 * A mapped file and a file accessed by means of the input and output (I/O) functions (ReadFile and
 * WriteFile) are not necessarily coherent.
 *
 * To fully close a file mapping object, an application must unmap all mapped views of the file
 * mapping object by calling UnmapViewOfFile, and close the file mapping object handle by calling
 * CloseHandle. The order in which these functions are called does not matter. The call to
 * UnmapViewOfFile is necessary because mapped views of a file mapping object maintain internal open
 * handles to the object, and a file mapping object will not close until all open handles to it are
 * closed.
 *
 * Note To guard against an access violation, use structured exception handling to protect any code
 * that writes to or reads from a memory mapped view.
 */
#define CreateFileMapping  CreateFileMappingW
#else
/**
 * This function creates a named or unnamed file-mapping object for the specified file.
 *
 * @param hFile Handle to the file from which to create a mapping object. The file must be opened
 *   with an access mode compatible with the protection flags specified by the flProtect parameter. It
 *   is recommended, though not required, that files you intend to map be opened for exclusive access.
 *   If hFile is (HANDLE)0xFFFFFFFF, the calling process must also specify a mapping object size in
 *   the dwMaximumSizeHigh and dwMaximumSizeLow parameters. The function creates a file-mapping object
 *   of the specified size backed by physical memory rather than by a named file in the file system.
 *   The file-mapping object can be shared by name. In Windows CE, memory utilized for the mapping
 *   object is not part of the 32 MB virtual process space.
 * @param lpFileMappingAttributes Ignored. Must be NULL.
 * @param flProtect Specifies the protection desired for the file view, when the file is mapped.
 *   This parameter can be one of the following values: Value Description PAGE_READONLY Gives
 *   read-only access to the committed region of pages. An attempt to write to or execute the
 *   committed region results in an access violation. The file specified by the hFile parameter must
 *   have been created with GENERIC_READ access. You cannot specify PAGE_READONLY without a file
 *   handle. PAGE_READWRITE Gives read-write access to the committed region of pages. The file
 *   specified by hFile must have been created with GENERIC_READ and GENERIC_WRITE access.
 *   PAGE_WRITECOPY Not supported. In addition, an application can specify certain section attributes
 *   by combining (using the bitwise OR operator) one or more of the following section attribute
 *   values with one of the preceding page protection values: Value Description SEC_COMMIT Allocates
 *   physical storage in memory or in the paging file on disk for all pages of a section. This is the
 *   default setting. SEC_IMAGE Not supported. SEC_NOCACHE Not supported. SEC_RESERVE Not supported.
 * @param dwMaximumSizeHigh Specifies the high-order 32 bits of the maximum size of the file-mapping
 *   object.
 * @param dwMaximumSizeLow Specifies the low-order 32 bits of the maximum size of the file-mapping
 *   object. If this parameter and dwMaximumSizeHig are zero, the maximum size of the file-mapping
 *   object is equal to the current size of the file identified by hFile.
 * @param lpName Long pointer to a null-terminated string specifying the name of the mapping object.
 *   The name can contain any character except the backslash character (\). If this parameter matches
 *   the name of an existing named mapping object, the function requests access to the mapping object
 *   with the protection specified by flProtect. If this parameter is NULL, the mapping object is
 *   created without a name. If lpName matches the name of an existing event, semaphore, mutex,
 *   waitable timer, or job, the function fails and the GetLastError function returns
 *   ERROR_INVALID_HANDLE. This occurs because these objects share the same name space.
 *
 * @return A handle to the file-mapping object indicates success. If the object existed before the
 *   function call, the function returns a handle to the existing object - with its current size, not
 *   the specified size - and GetLastError returns ERROR_ALREADY_EXISTS. NULL indicates failure. To
 *   get extended error information, call GetLastError.
 *
 * If you call CreateFileMapping with a handle from CreateFileForMapping and it fails for any
 * reason, the handle is closed.
 *
 * This function will not work on a Windows CE-based platform that does not support Page-In.
 *
 * After a file-mapping object has been created, the size of the file must not exceed the size of
 * the file-mapping object; if it does, not all of the file's contents will be available for
 * sharing.
 *
 * If an application specifies a size for the file-mapping object that is larger than the size of
 * the actual named file on disk, the file on disk is grown to match the specified size of the
 * file-mapping object. If the file cannot be grown, this results in a failure to create the
 * file-mapping object. GetLastError will return ERROR_DISK_FULL.
 *
 * The handle that CreateFileMapping returns has full access to the new file-mapping object. It can
 * be used with any function that requires a handle to a file-mapping object. File-mapping objects
 * can be shared through process creation.
 *
 * File handles that have been used to create file-mapping objects must not be used in subsequent
 * calls to file I/O functions, such as ReadFile and WriteFile. In general, if a file handle has
 * been used in a successful call to the CreateFileMapping function, do not use that handle unless
 * you first close the corresponding file-mapping object.
 *
 * Creating a file-mapping object creates the potential for mapping a view of the file but does not
 * map the view. The MapViewOfFile function maps a view of a file into the address space of a
 * process.
 *
 * With one important exception, file views derived from a single file-mapping object are coherent,
 * or identical, at a given time. If multiple processes have handles of the same file-mapping
 * object, they see a coherent view of the data when they map a view of the file.
 *
 * The exception has to do with remote files. Although CreateFileMapping works with remote files, it
 * does not keep them coherent. For example, if two computers both map a file as writeable, and both
 * change the same page, each computer will only see its own writes to the page. When the data gets
 * updated on the disk, it is not merged.
 *
 * A mapped file and a file accessed by means of the input and output (I/O) functions (ReadFile and
 * WriteFile) are not necessarily coherent.
 *
 * To fully close a file mapping object, an application must unmap all mapped views of the file
 * mapping object by calling UnmapViewOfFile, and close the file mapping object handle by calling
 * CloseHandle. The order in which these functions are called does not matter. The call to
 * UnmapViewOfFile is necessary because mapped views of a file mapping object maintain internal open
 * handles to the object, and a file mapping object will not close until all open handles to it are
 * closed.
 *
 * Note To guard against an access violation, use structured exception handling to protect any code
 * that writes to or reads from a memory mapped view.
 */
#define CreateFileMapping  CreateFileMappingA
#endif // !UNICODE

/**
 * This function creates a file that can be used for memory mapping.
 *
 * @param lpFileName Pointer to a null-terminated string that specifies the name of the file that is
 *   to be created and used as a file-mapping object. The maximum length is MAX_PATH characters.
 * @param dwDesiredAccess Specifies the type of access. An application can obtain read-only access
 *   to files, or query device attributes. You can use the following flag constants to build a value
 *   for this parameter. Value Description 0 Allows an application to query device attributes without
 *   actually accessing the device. GENERIC_READ Specifies read access to the file. Data can be read
 *   from the file and the file pointer can be moved. GENERIC_WRITE For Windows CE versions 2.10 and
 *   later, this flag specifies write access to the file.
 * @param dwShareMode Specifies how this file can be shared. This parameter must be some combination
 *   of the following values: Value Description 0 Prevents the file from being shared. FILE_SHARE_READ
 *   Other open operations can be performed on the file for read access. If CreateFile is opening the
 *   client end of a mailslot, this flag is specified. FILE_SHARE_WRITE Other open operations can be
 *   performed on the file for write access.
 * @param lpSecurityAttributes Not used; set to NULL.
 * @param dwCreationDisposition This parameter is one of the following values: Value Description
 *   CREATE_NEW Creates a new file. The function fails if the specified file already exists.
 *   CREATE_ALWAYS Creates a new file. The function overwrites the file if it exists. OPEN_EXISTING
 *   Opens the file. The function fails if the file does not exist. OPEN_ALWAYS Opens the file, if it
 *   exists. If the file does not exist, the function creates the file as if dwCreationDistribution
 *   were CREATE_NEW. TRUNCATE_EXISTING Opens the file. Once opened, the file is truncated so that its
 *   size is zero bytes. The calling process must open the file with at least GENERIC_WRITE access.
 *   The function fails if the file does not exist.
 * @param dwFlagsAndAttributes Specifies the file attributes and flags for the file. Any combination
 *   of the following attributes is acceptable, except all other file attributes override
 *   FILE_ATTRIBUTE_NORMAL. Value Description FILE_ATTRIBUTE_ARCHIVE The file is an archive file.
 *   Applications use this attribute to mark files for backup or removal. FILE_ATTRIBUTE_COMPRESSED
 *   The file or directory is compressed. For a file, this means that all of the data in the file is
 *   compressed. For a directory, this means that compression is the default for newly created files
 *   and subdirectories. FILE_ATTRIBUTE_NORMAL The file has no other attributes set. This attribute is
 *   valid only if used alone. FILE_ATTRIBUTE_HIDDEN The file is hidden. It is not to be included in
 *   an ordinary directory listing. FILE_ATTRIBUTE_READONLY The file is read only. Applications can
 *   read the file but cannot write to it or delete it. FILE_ATTRIBUTE_SYSTEM The file is part of or
 *   is used exclusively by the operating system. Any combination of the following flags is
 *   acceptable: Value Description FILE_FLAG_WRITE_THROUGH Instructs the operating system to write
 *   through any intermediate cache and go directly to the file. The operating system can still cache
 *   write operations, but cannot lazily flush them. FILE_FLAG_RANDOM_ACCESS Indicates that the file
 *   is accessed randomly. Windows uses this flag to optimize file caching. Specifying this flag can
 *   increase performance for applications that read large files using sequential access. Performance
 *   gains can be even more noticeable for applications that read large files mostly sequentially, but
 *   occasionally skip over small ranges of bytes.
 * @param hTemplateFile Not used; ignored.
 *
 * @return An open handle to the specified file-mapping object indicates success. If the specified
 *   object exists before the function call and dwCreationDistribution is CREATE_ALWAYS or
 *   OPEN_ALWAYS, a call to GetLastError returns ERROR_ALREADY_EXISTS, even though the function has
 *   succeeded. If the file-mapping object does not exist before the call, GetLastError returns zero.
 *   INVALID_HANDLE_VALUE indicates failure. To get extended error information, call GetLastError.
 *
 * The CreateFileForMapping function is a special version of CreateFile that is designed for
 * file-mapping objects. It performs a callback into the kernel's address space so that the
 * specified file is created by the kernel. This ensures that the file is available to processes
 * other than the creating process.
 *
 * The handle returned from CreateFileForMapping is used as the hFile parameter in a subsequent call
 * to CreateFileMapping, as shown in the following psuedo-code:
 *
 *     // psuedocode fragment to show call sequence, use of the handle
 *     HANDLE hFile;
 *     hFile = CreateFileForMapping(...);
 *     CreateFileMapping(hFile, ...);
 *
 * If your process exits without having called CreateFileMapping, the handle returned by
 * CreateFileForMapping is automatically closed.
 */
WINBASEAPI
HANDLE
WINAPI
CreateFileForMapping(LPCTSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes,
	HANDLE hTemplateFile);

LPVOID MapUncompressedFileW(LPCWSTR pFileName, LPDWORD pLen);

#ifdef UNICODE
#define MapUncompressedFile  MapUncompressedFileW
#else
#define MapUncompressedFile  MapUncompressedFileA
#endif // !UNICODE

WINBASEAPI
DWORD
WINAPI
GetTempPathA(
    DWORD nBufferLength,
    LPSTR lpBuffer
    );

WINBASEAPI
DWORD
WINAPI
GetTempPathW(
    DWORD nBufferLength,
    LPWSTR lpBuffer
    );

#ifdef UNICODE
#define GetTempPath  GetTempPathW
#else
#define GetTempPath  GetTempPathA
#endif // !UNICODE

#define TLS_MINIMUM_AVAILABLE   64

#define CREATE_SUSPENDED 4

/**
 * This function creates a thread to execute within the address space of the calling process.
 *
 * @param lpThreadAttributes Ignored. Must be NULL.
 * @param dwStackSize Ignored. The default stack size for a thread is determined by the linker
 *   setting /STACK.
 * @param lpStartAddress Long pointer to the application-defined function of type
 *   LPTHREAD_START_ROUTINE to be executed by the thread and represents the starting address of the
 *   thread. For more information on the thread function, see ThreadProc.
 * @param lpParameter Long pointer to a single 32-bit parameter value passed to the thread.
 * @param dwCreationFlags Specifies flags that control the creation of the thread. Value Description
 *   CREATE_SUSPENDED The thread is created in a suspended state, and will not run until the
 *   ResumeThread function is called. 0 The thread runs immediately after creation.
 * @param lpThreadId Long pointer to a 32-bit variable that receives the thread identifier. If this
 *   parameter is NULL, the thread identifier is not returned.
 *
 * @return A handle to the new thread indicates success. NULL indicates failure. To get extended
 *   error information, call GetLastError.
 *
 * The number of threads a process can create is limited by the available virtual memory. The number
 * of threads that can be created depends on the default stack size. If every thread has one
 * megabyte of stack space., you can create at most 32 threads. If you reduce the default stack
 * size, you can create more threads. However, your application will have better performance if you
 * create one thread per processor and build queues of requests for which the application maintains
 * the context information. A thread would process all requests in a queue before processing
 * requests in the next queue.
 *
 * The new thread handle is created with THREAD_ALL_ACCESS to the new thread. The handle can be used
 * in any function that requires a thread object handle.
 *
 * The thread execution begins at the function specified by the lpStartAddress parameter. If this
 * function returns, the DWORD return value is used to terminate the thread in an implicit call to
 * the ExitThread function. Use the GetExitCodeThread function to get the thread's return value.
 *
 * The CreateThread function may succeed even if lpStartAddress points to data, code, or is not
 * accessible. If the start address is invalid when the thread runs, an exception occurs, and the
 * thread terminates. Thread termination due to a invalid start address is handled as an error exit
 * for the thread's process. This behavior is similar to the asynchronous nature of CreateProcess,
 * where the process is created even if it refers to invalid or missing dynamic-link libraries
 * (DLLs).
 *
 * The thread is created with a thread priority of THREAD_PRIORITY_NORMAL. Use the GetThreadPriority
 * and SetThreadPriority functions to get and set the priority value of a thread.
 *
 * When a thread terminates, the thread object attains a signaled state, satisfying any threads that
 * were waiting on the object.
 *
 * The thread object remains in the system until the thread has terminated and all handles to it
 * have been closed through a call to CloseHandle.
 *
 * The ExitThread function, CreateThread function, and a process that is starting (as the result of
 * a call by CreateProcess) are serialized between each other within a process. Only one of these
 * events can happen in an address space at a time. This means that the following restrictions hold:
 *
 * During process startup and DLL initialization routines, new threads can be created, but they do
 * not begin execution until DLL initialization is done for the process.
 *
 * Only one thread in a process can be in a DLL initialization or detach routine at a time.
 */
HANDLE
WINAPI
CreateThread (
    LPSECURITY_ATTRIBUTES lpsa,
    DWORD   cbStack,
    LPTHREAD_START_ROUTINE lpStartAddr,
    LPVOID lpvThreadParam,
    DWORD fdwCreate,
    LPDWORD lpIDThread
    );

/**
 * This function ends a thread.
 *
 * @param dwExitCode [in] Specifies the exit code for the calling thread. Use the GetExitCodeThread
 *   function to retrieve a thread's exit code.
 *
 * @return None.
 *
 * ExitThread is the preferred method of exiting a thread. When this function is called (either
 * explicitly or by returning from a thread procedure), the current thread's stack is deallocated
 * and the thread terminates. The entry-point function of all attached dynamic-link libraries (DLLs)
 * is invoked with a value indicating that the thread is detaching from the DLL.
 *
 * If the thread is the last thread in the process when this function is called, the thread's
 * process is also terminated.
 *
 * If the primary thread calls the ExitThread function, the application exits.
 *
 * The state of the thread object becomes signaled, releasing any other threads that had been
 * waiting for the thread to terminate. The thread's termination status changes from STILL_ACTIVE to
 * the value of the dwExitCode parameter.
 *
 * Terminating a thread does not necessarily remove the thread object from the operating system. A
 * thread object is deleted when the last handle to the thread is closed.
 *
 * The ExitThread and CreateThread functions, as well as a process that is starting as the result of
 * a CreateProcess call, are serialized between each other within a process. Only one of these
 * events can happen in an address space at a time. This means the following restrictions hold:
 *
 * During process startup and DLL initialization routines, new threads can be created, but they do
 * not begin execution until DLL initialization is done for the process.
 *
 * Only one thread in a process can be in a DLL initialization or detach routine at a time.
 */
VOID
WINAPI
ExitThread (
    DWORD   dwExitCode
    );

/**
 * This function stops the specified thread.
 *
 * @param hThread Handle to the thread to terminate.
 * @param dwExitCode Specifies the exit code for the thread. Use the GetExitCodeThread function to
 *   retrieve a thread's exit value.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * TerminateThread is used to cause a thread to exit. When this occurs, the target thread has no
 * chance to execute any user-mode code and its initial stack is not deallocated. DLLs attached to
 * the thread are not notified that the thread is terminating.
 *
 * This function reduces memory leaks by clearing the stack before exiting. It also terminates the
 * thread process only if the thread in question is the main or primary thread.
 *
 * TerminateThread is a dangerous function that should only be used in the most extreme cases. You
 * should call TerminateThread only if you know exactly what the target thread is doing, and you
 * control all of the code that the target thread could possibly be running at the time of the
 * termination. For example, TerminateThread can result in the following problems:
 *
 * If the target thread owns a critical section, the critical section will not be released.
 *
 * If the target thread is executing certain kernel32 calls when it is terminated, the kernel32
 * state for the thread's process could be inconsistent.
 *
 * If the target thread is manipulating the global state of a shared DLL, the state of the DLL could
 * be destroyed, affecting other users of the DLL.
 *
 * A thread cannot protect itself against TerminateThread, other than by controlling access to its
 * handles. The thread handle returned by the CreateThread and CreateProcess functions has
 * THREAD_TERMINATE access, so any caller holding one of these handles can terminate your thread.
 *
 * If the target thread is the last thread of a process when this function is called, the thread's
 * process is also terminated.
 *
 * The state of the thread object becomes signaled, releasing any other threads that had been
 * waiting for the thread to terminate. The thread's termination status changes from STILL_ACTIVE to
 * the value of the dwExitCode parameter.
 *
 * Terminating a thread does not necessarily remove the thread object from the system. A thread
 * object is deleted when the last thread handle is closed.
 */
BOOL
WINAPI
TerminateThread(
    HANDLE hThread,
    DWORD dwExitCode
    );
    
#define STILL_ACTIVE 0x00000103

/**
 * This function retrieves the value in the calling thread's thread local storage (TLS) slot for a
 * specified TLS index. Each thread of a process has its own slot for each TLS index.
 *
 * @param dwTlsIndex [in] Specifies a TLS index that was allocated by the TlsAlloc function.
 *
 * @return The value stored in the calling thread's TLS slot associated with the specified index
 *   indicates success. Zero indicates failure. To get extended error information, call GetLastError.
 *   The data stored in a TLS slot can have a value of zero. In this case, the return value is zero
 *   and GetLastError returns NO_ERROR.
 *
 * TLS indexes are typically allocated by the TlsAlloc function during process or DLL
 * initialization. Once allocated, each thread of the process can use a TLS index to access its own
 * TLS storage slot for that index. The storage slot for each thread is initialized to NULL. A
 * thread specifies a TLS index in a call to TlsSetValue, to store a value in its slot. The thread
 * specifies the same index in a subsequent call to TlsGetValue, to retrieve the stored value.
 *
 * TlsSetValue and TlsGetValue were implemented with speed as the primary goal. These functions
 * perform minimal parameter validation and error checking. In particular, this function succeeds if
 * dwTlsIndex is in the range 0 through (TLS_MINIMUM_AVAILABLE - 1). It is up to the programmer to
 * ensure that the index is valid.
 *
 * Win32 functions that return indications of failure call SetLastError when they fail. They
 * generally do not call SetLastError when they succeed. The TlsGetValue function is an exception to
 * this general rule. The TlsGetValue function calls SetLastError to clear a thread's last error
 * when it succeeds. That allows checking for the error-free retrieval of NULL values.
 */
LPVOID
WINAPI
TlsGetValue (
    DWORD dwTlsIndex
    );

/**
 * This function stores a value in the calling thread's thread local storage (TLS) slot for a
 * specified TLS index. Each thread of a process has its own slot for each TLS index.
 *
 * @param dwTlsIndex [in] Specifies a TLS index that was allocated by the TlsAlloc function.
 * @param lpTlsValue [in] Pointer to the value to be stored in the calling thread's TLS slot
 *   specified by dwTlsIndex.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * TLS indexes are typically allocated by the TlsAlloc function during process or DLL
 * initialization. Once allocated, each thread of the process can use a TLS index to access its own
 * TLS storage slot for that index. The storage slot for each thread is initialized to NULL. A
 * thread specifies a TLS index in a call to TlsSetValue to store a value in its slot. The thread
 * specifies the same index in a subsequent call to TlsGetValue to retrieve the stored value.
 *
 * TlsSetValue and TlsGetValue were implemented with speed as the primary goal. These functions
 * perform minimal parameter validation and error checking. In particular, this function succeeds if
 * dwTlsIndex is in the range 0 through (TLS_MINIMUM_AVAILABLE - 1). It is up to the programmer to
 * ensure that the index is valid.
 */
BOOL
WINAPI
TlsSetValue (
    DWORD dwTlsIndex,
    LPVOID lpvTlsValue
    );


/**
 * This structure is filled in by the CreateProcess function with information about a newly created
 * process and its primary thread.
 */
typedef struct _PROCESS_INFORMATION {
    /**
     * Returns a handle to the newly created process. The handle is used to specify the process in all
     * functions that perform operations on the process object.
     */
    HANDLE  hProcess;
    /**
     * Returns a handle to the primary thread of the newly created process. The handle is used to
     * specify the thread in all functions that perform operations on the thread object.
     */
    HANDLE  hThread;
    /**
     * Returns a global process identifier that can be used to identify a process. The value is valid
     * from the time the process is created until the time the process is terminated.
     */
    DWORD   dwProcessId;
    /**
     * Returns a global thread identifier that can be used to identify a thread. The value is valid from
     * the time the thread is created until the time the thread is terminated.
     */
    DWORD   dwThreadId;
} PROCESS_INFORMATION, *LPPROCESS_INFORMATION;

typedef struct _STARTUPINFOA {
    DWORD   cb;
    LPSTR   lpReserved;
    LPSTR   lpDesktop;
    LPSTR   lpTitle;
    DWORD   dwX;
    DWORD   dwY;
    DWORD   dwXSize;
    DWORD   dwYSize;
    DWORD   dwXCountChars;
    DWORD   dwYCountChars;
    DWORD   dwFillAttribute;
    DWORD   dwFlags;
    WORD    wShowWindow;
    WORD    cbReserved2;
    LPBYTE  lpReserved2;
    HANDLE  hStdInput;
    HANDLE  hStdOutput;
    HANDLE  hStdError;
} STARTUPINFOA, *LPSTARTUPINFOA;

typedef struct _STARTUPINFOW {
    DWORD   cb;
    LPWSTR  lpReserved;
    LPWSTR  lpDesktop;
    LPWSTR  lpTitle;
    DWORD   dwX;
    DWORD   dwY;
    DWORD   dwXSize;
    DWORD   dwYSize;
    DWORD   dwXCountChars;
    DWORD   dwYCountChars;
    DWORD   dwFillAttribute;
    DWORD   dwFlags;
    WORD    wShowWindow;
    WORD    cbReserved2;
    LPBYTE  lpReserved2;
    HANDLE  hStdInput;
    HANDLE  hStdOutput;
    HANDLE  hStdError;
} STARTUPINFOW, *LPSTARTUPINFOW;

#ifdef UNICODE
typedef STARTUPINFOW STARTUPINFO;
typedef LPSTARTUPINFOW LPSTARTUPINFO;
#else
typedef STARTUPINFOA STARTUPINFO;
typedef LPSTARTUPINFOA LPSTARTUPINFO;
#endif // UNICODE

/**
 * This function is used to run a new program. It creates a new process and its primary thread. The
 * new process executes the specified executable file.
 *
 * @param lpApplicationName Pointer to a null-terminated string that specifies the module to
 *   execute. The string can specify the full path and filename of the module to execute or it can
 *   specify a partial name. In the case of a partial name, the function uses the current drive and
 *   current directory to complete the specification. The lpApplicationName parameter must be non-NULL
 *   and must include the module name.
 * @param lpCommandLine Pointer to a null-terminated string that specifies the command line to
 *   execute. The system adds a null character to the command line, trimming the string if necessary,
 *   to indicate which file was actually used. The lpCommandLine parameter can be NULL. In that case,
 *   the function uses the string pointed to by lpApplicationName as the command line. If both
 *   lpApplicationName and lpCommandLine are non-NULL, *lpApplicationName specifies the module to
 *   execute, and *lpCommandLine specifies the command line. C runtime processes can use the argc and
 *   argv arguments. If the filename does not contain an extension, .EXE is assumed. If the filename
 *   ends in a period (.) with no extension, or the filename contains a path, .EXE is not appended.
 *   Windows CE versions 2.10 and later search the directories indicated by the lpApplicationName
 *   parameter in the following order: The windows (\windows) directory The root (\) directory of the
 *   device An OEM-dependent directory The OEM-defined shell (\ceshell) directory - Embedded Toolkit
 *   users only Windows CE versions 1.0 through 2.01 search the directories indicated by the
 *   lpApplicationName parameter in the following order: The root of the PC Card, if it exists The
 *   windows (\windows) directory The root (\ ) directory of the device
 * @param lpProcessAttributes Not supported; set to NULL.
 * @param lpThreadAttributes Not supported; set to NULL.
 * @param bInheritHandles Not supported; set to NULL.
 * @param dwCreationFlags Specifies additional flags that control the priority class and the
 *   creation of the process. The following creation flags can be specified in any combination, except
 *   as noted: Value Description CREATE_DEFAULT_ERROR_MODE Not supported. CREATE_NEW_CONSOLE The new
 *   process has a new console, instead of inheriting the parent's console. This flag cannot be used
 *   with the DETACHED_PROCESS flag. CREATE_NEW_PROCESS_GROUP Not supported. CREATE_SEPARATE_WOW_VDM
 *   Not supported. CREATE_SHARED_WOW_VDM Not supported. CREATE_SUSPENDED The primary thread of the
 *   new process is created in a suspended state, and does not run until the ResumeThread function is
 *   called. CREATE_UNICODE_ENVIRONMENT Not supported. DEBUG_PROCESS If this flag is set, the calling
 *   process is treated as a debugger, and the new process is a process being debugged. Child
 *   processes of the new process are also debugged. The system notifies the debugger of all debug
 *   events that occur in the process being debugged. If you create a process with this flag set, only
 *   the calling thread (the thread that called CreateProcess) can call the WaitForDebugEvent
 *   function. DEBUG_ONLY_THIS_PROCESS If this flag is set, the calling process is treated as a
 *   debugger, and the new process is a process being debugged. No child processes of the new process
 *   are debugged. The system notifies the debugger of all debug events that occur in the process
 *   being debugged. DETACHED_PROCESS Not supported. Windows CE does not support the concept of a
 *   priority class. The priority of a thread is the only parameter that determines a threads
 *   scheduling priority. For Windows CE version 1.0 and 1.01, the dwCreationFlags parameter only
 *   supports the following values: CREATE_SUSPENDED and zero.
 * @param lpEnvironment Not supported; set to NULL.
 * @param lpCurrentDirectory Not supported; set to NULL.
 * @param lpStartupInfo Not supported; set to NULL.
 * @param lpProcessInformation Pointer to a PROCESS_INFORMATION structure that receives
 *   identification information about the new process.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * The CreateProcess function is used to run a new program. In addition to creating a process,
 * CreateProcess also creates a thread object. The thread is created with an initial stack whose
 * size is described in the image header of the specified program's executable file. The thread
 * begins execution at the image's entry point.
 *
 * The new process and the new thread handles are created with full access rights. For either
 * handle, the handle can be used in any function that requires an object handle to that type.
 *
 * The process is assigned a 32-bit process identifier. The identifier is valid until the process
 * terminates. It can be used to identify the process, or specified in the OpenProcess function to
 * open a handle to the process. The initial thread in the process is also assigned a 32-bit thread
 * identifier. The identifier is valid until the thread terminates and can be used to uniquely
 * identify the thread within the system. These identifiers are returned in the PROCESS_INFORMATION
 * structure.
 *
 * When specifying an application name in the lpApplicationName string, it doesn't matter whether
 * the application name includes the filename extension.
 *
 * ExitThread, CreateThread, and a process that is starting (as the result of a call by
 * CreateProcess) are serialized between each other within a process. Only one of these events can
 * happen in an address space at a time. This means the following restrictions hold:
 *
 * During process startup and DLL initialization routines, new threads can be created, but they do
 * not begin execution until DLL initialization is done for the process.
 *
 * Only one thread in a process can be in a DLL initialization or detach routine at a time.
 *
 * The created process remains in the system until all threads within the process have terminated
 * and all handles to the process and any of its threads have been closed through calls to
 * CloseHandle. The handles for both the process and the main thread must be closed through calls to
 * CloseHandle. If these handles are not needed, it is best to close them immediately after the
 * process is created.
 *
 * When the last thread in a process terminates, the following events occur:
 *
 * All objects opened by the process are implicitly closed.
 *
 * The process's termination status (which is returned by GetExitCodeProcess) changes from its
 * initial value of STILL_ACTIVE to the termination status of the last thread to terminate.
 *
 * The thread object of the main thread is set to the signaled state, satisfying any threads that
 * were waiting on the object.
 *
 * The process object is set to the signaled state, satisfying any threads that were waiting on the
 * object.
 *
 * The handle returned by the CreateProcess function has PROCESS_ALL_ACCESS access to the process
 * object.
 */
BOOL
WINAPI
CreateProcessA (
    LPCSTR pszImageName,
    LPCSTR pszCmdLine,
    LPSECURITY_ATTRIBUTES psaProcess,
    LPSECURITY_ATTRIBUTES psaThread,
    BOOL fInheritHandles,
    DWORD fdwCreate,
    LPVOID pvEnvironment,
    LPSTR pszCurDir,
    LPSTARTUPINFO psiStartInfo,
    LPPROCESS_INFORMATION pProcInfo
    );
/**
 * This function is used to run a new program. It creates a new process and its primary thread. The
 * new process executes the specified executable file.
 *
 * @param lpApplicationName Pointer to a null-terminated string that specifies the module to
 *   execute. The string can specify the full path and filename of the module to execute or it can
 *   specify a partial name. In the case of a partial name, the function uses the current drive and
 *   current directory to complete the specification. The lpApplicationName parameter must be non-NULL
 *   and must include the module name.
 * @param lpCommandLine Pointer to a null-terminated string that specifies the command line to
 *   execute. The system adds a null character to the command line, trimming the string if necessary,
 *   to indicate which file was actually used. The lpCommandLine parameter can be NULL. In that case,
 *   the function uses the string pointed to by lpApplicationName as the command line. If both
 *   lpApplicationName and lpCommandLine are non-NULL, *lpApplicationName specifies the module to
 *   execute, and *lpCommandLine specifies the command line. C runtime processes can use the argc and
 *   argv arguments. If the filename does not contain an extension, .EXE is assumed. If the filename
 *   ends in a period (.) with no extension, or the filename contains a path, .EXE is not appended.
 *   Windows CE versions 2.10 and later search the directories indicated by the lpApplicationName
 *   parameter in the following order: The windows (\windows) directory The root (\) directory of the
 *   device An OEM-dependent directory The OEM-defined shell (\ceshell) directory - Embedded Toolkit
 *   users only Windows CE versions 1.0 through 2.01 search the directories indicated by the
 *   lpApplicationName parameter in the following order: The root of the PC Card, if it exists The
 *   windows (\windows) directory The root (\ ) directory of the device
 * @param lpProcessAttributes Not supported; set to NULL.
 * @param lpThreadAttributes Not supported; set to NULL.
 * @param bInheritHandles Not supported; set to NULL.
 * @param dwCreationFlags Specifies additional flags that control the priority class and the
 *   creation of the process. The following creation flags can be specified in any combination, except
 *   as noted: Value Description CREATE_DEFAULT_ERROR_MODE Not supported. CREATE_NEW_CONSOLE The new
 *   process has a new console, instead of inheriting the parent's console. This flag cannot be used
 *   with the DETACHED_PROCESS flag. CREATE_NEW_PROCESS_GROUP Not supported. CREATE_SEPARATE_WOW_VDM
 *   Not supported. CREATE_SHARED_WOW_VDM Not supported. CREATE_SUSPENDED The primary thread of the
 *   new process is created in a suspended state, and does not run until the ResumeThread function is
 *   called. CREATE_UNICODE_ENVIRONMENT Not supported. DEBUG_PROCESS If this flag is set, the calling
 *   process is treated as a debugger, and the new process is a process being debugged. Child
 *   processes of the new process are also debugged. The system notifies the debugger of all debug
 *   events that occur in the process being debugged. If you create a process with this flag set, only
 *   the calling thread (the thread that called CreateProcess) can call the WaitForDebugEvent
 *   function. DEBUG_ONLY_THIS_PROCESS If this flag is set, the calling process is treated as a
 *   debugger, and the new process is a process being debugged. No child processes of the new process
 *   are debugged. The system notifies the debugger of all debug events that occur in the process
 *   being debugged. DETACHED_PROCESS Not supported. Windows CE does not support the concept of a
 *   priority class. The priority of a thread is the only parameter that determines a threads
 *   scheduling priority. For Windows CE version 1.0 and 1.01, the dwCreationFlags parameter only
 *   supports the following values: CREATE_SUSPENDED and zero.
 * @param lpEnvironment Not supported; set to NULL.
 * @param lpCurrentDirectory Not supported; set to NULL.
 * @param lpStartupInfo Not supported; set to NULL.
 * @param lpProcessInformation Pointer to a PROCESS_INFORMATION structure that receives
 *   identification information about the new process.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * The CreateProcess function is used to run a new program. In addition to creating a process,
 * CreateProcess also creates a thread object. The thread is created with an initial stack whose
 * size is described in the image header of the specified program's executable file. The thread
 * begins execution at the image's entry point.
 *
 * The new process and the new thread handles are created with full access rights. For either
 * handle, the handle can be used in any function that requires an object handle to that type.
 *
 * The process is assigned a 32-bit process identifier. The identifier is valid until the process
 * terminates. It can be used to identify the process, or specified in the OpenProcess function to
 * open a handle to the process. The initial thread in the process is also assigned a 32-bit thread
 * identifier. The identifier is valid until the thread terminates and can be used to uniquely
 * identify the thread within the system. These identifiers are returned in the PROCESS_INFORMATION
 * structure.
 *
 * When specifying an application name in the lpApplicationName string, it doesn't matter whether
 * the application name includes the filename extension.
 *
 * ExitThread, CreateThread, and a process that is starting (as the result of a call by
 * CreateProcess) are serialized between each other within a process. Only one of these events can
 * happen in an address space at a time. This means the following restrictions hold:
 *
 * During process startup and DLL initialization routines, new threads can be created, but they do
 * not begin execution until DLL initialization is done for the process.
 *
 * Only one thread in a process can be in a DLL initialization or detach routine at a time.
 *
 * The created process remains in the system until all threads within the process have terminated
 * and all handles to the process and any of its threads have been closed through calls to
 * CloseHandle. The handles for both the process and the main thread must be closed through calls to
 * CloseHandle. If these handles are not needed, it is best to close them immediately after the
 * process is created.
 *
 * When the last thread in a process terminates, the following events occur:
 *
 * All objects opened by the process are implicitly closed.
 *
 * The process's termination status (which is returned by GetExitCodeProcess) changes from its
 * initial value of STILL_ACTIVE to the termination status of the last thread to terminate.
 *
 * The thread object of the main thread is set to the signaled state, satisfying any threads that
 * were waiting on the object.
 *
 * The process object is set to the signaled state, satisfying any threads that were waiting on the
 * object.
 *
 * The handle returned by the CreateProcess function has PROCESS_ALL_ACCESS access to the process
 * object.
 */
BOOL
WINAPI
CreateProcessW (
    LPCWSTR pszImageName,
    LPCWSTR pszCmdLine,
    LPSECURITY_ATTRIBUTES psaProcess,
    LPSECURITY_ATTRIBUTES psaThread,
    BOOL fInheritHandles,
    DWORD fdwCreate,
    LPVOID pvEnvironment,
    LPWSTR pszCurDir,
    LPSTARTUPINFO psiStartInfo,
    LPPROCESS_INFORMATION pProcInfo
    );
#ifdef UNICODE
/**
 * This function is used to run a new program. It creates a new process and its primary thread. The
 * new process executes the specified executable file.
 *
 * @param lpApplicationName Pointer to a null-terminated string that specifies the module to
 *   execute. The string can specify the full path and filename of the module to execute or it can
 *   specify a partial name. In the case of a partial name, the function uses the current drive and
 *   current directory to complete the specification. The lpApplicationName parameter must be non-NULL
 *   and must include the module name.
 * @param lpCommandLine Pointer to a null-terminated string that specifies the command line to
 *   execute. The system adds a null character to the command line, trimming the string if necessary,
 *   to indicate which file was actually used. The lpCommandLine parameter can be NULL. In that case,
 *   the function uses the string pointed to by lpApplicationName as the command line. If both
 *   lpApplicationName and lpCommandLine are non-NULL, *lpApplicationName specifies the module to
 *   execute, and *lpCommandLine specifies the command line. C runtime processes can use the argc and
 *   argv arguments. If the filename does not contain an extension, .EXE is assumed. If the filename
 *   ends in a period (.) with no extension, or the filename contains a path, .EXE is not appended.
 *   Windows CE versions 2.10 and later search the directories indicated by the lpApplicationName
 *   parameter in the following order: The windows (\windows) directory The root (\) directory of the
 *   device An OEM-dependent directory The OEM-defined shell (\ceshell) directory - Embedded Toolkit
 *   users only Windows CE versions 1.0 through 2.01 search the directories indicated by the
 *   lpApplicationName parameter in the following order: The root of the PC Card, if it exists The
 *   windows (\windows) directory The root (\ ) directory of the device
 * @param lpProcessAttributes Not supported; set to NULL.
 * @param lpThreadAttributes Not supported; set to NULL.
 * @param bInheritHandles Not supported; set to NULL.
 * @param dwCreationFlags Specifies additional flags that control the priority class and the
 *   creation of the process. The following creation flags can be specified in any combination, except
 *   as noted: Value Description CREATE_DEFAULT_ERROR_MODE Not supported. CREATE_NEW_CONSOLE The new
 *   process has a new console, instead of inheriting the parent's console. This flag cannot be used
 *   with the DETACHED_PROCESS flag. CREATE_NEW_PROCESS_GROUP Not supported. CREATE_SEPARATE_WOW_VDM
 *   Not supported. CREATE_SHARED_WOW_VDM Not supported. CREATE_SUSPENDED The primary thread of the
 *   new process is created in a suspended state, and does not run until the ResumeThread function is
 *   called. CREATE_UNICODE_ENVIRONMENT Not supported. DEBUG_PROCESS If this flag is set, the calling
 *   process is treated as a debugger, and the new process is a process being debugged. Child
 *   processes of the new process are also debugged. The system notifies the debugger of all debug
 *   events that occur in the process being debugged. If you create a process with this flag set, only
 *   the calling thread (the thread that called CreateProcess) can call the WaitForDebugEvent
 *   function. DEBUG_ONLY_THIS_PROCESS If this flag is set, the calling process is treated as a
 *   debugger, and the new process is a process being debugged. No child processes of the new process
 *   are debugged. The system notifies the debugger of all debug events that occur in the process
 *   being debugged. DETACHED_PROCESS Not supported. Windows CE does not support the concept of a
 *   priority class. The priority of a thread is the only parameter that determines a threads
 *   scheduling priority. For Windows CE version 1.0 and 1.01, the dwCreationFlags parameter only
 *   supports the following values: CREATE_SUSPENDED and zero.
 * @param lpEnvironment Not supported; set to NULL.
 * @param lpCurrentDirectory Not supported; set to NULL.
 * @param lpStartupInfo Not supported; set to NULL.
 * @param lpProcessInformation Pointer to a PROCESS_INFORMATION structure that receives
 *   identification information about the new process.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * The CreateProcess function is used to run a new program. In addition to creating a process,
 * CreateProcess also creates a thread object. The thread is created with an initial stack whose
 * size is described in the image header of the specified program's executable file. The thread
 * begins execution at the image's entry point.
 *
 * The new process and the new thread handles are created with full access rights. For either
 * handle, the handle can be used in any function that requires an object handle to that type.
 *
 * The process is assigned a 32-bit process identifier. The identifier is valid until the process
 * terminates. It can be used to identify the process, or specified in the OpenProcess function to
 * open a handle to the process. The initial thread in the process is also assigned a 32-bit thread
 * identifier. The identifier is valid until the thread terminates and can be used to uniquely
 * identify the thread within the system. These identifiers are returned in the PROCESS_INFORMATION
 * structure.
 *
 * When specifying an application name in the lpApplicationName string, it doesn't matter whether
 * the application name includes the filename extension.
 *
 * ExitThread, CreateThread, and a process that is starting (as the result of a call by
 * CreateProcess) are serialized between each other within a process. Only one of these events can
 * happen in an address space at a time. This means the following restrictions hold:
 *
 * During process startup and DLL initialization routines, new threads can be created, but they do
 * not begin execution until DLL initialization is done for the process.
 *
 * Only one thread in a process can be in a DLL initialization or detach routine at a time.
 *
 * The created process remains in the system until all threads within the process have terminated
 * and all handles to the process and any of its threads have been closed through calls to
 * CloseHandle. The handles for both the process and the main thread must be closed through calls to
 * CloseHandle. If these handles are not needed, it is best to close them immediately after the
 * process is created.
 *
 * When the last thread in a process terminates, the following events occur:
 *
 * All objects opened by the process are implicitly closed.
 *
 * The process's termination status (which is returned by GetExitCodeProcess) changes from its
 * initial value of STILL_ACTIVE to the termination status of the last thread to terminate.
 *
 * The thread object of the main thread is set to the signaled state, satisfying any threads that
 * were waiting on the object.
 *
 * The process object is set to the signaled state, satisfying any threads that were waiting on the
 * object.
 *
 * The handle returned by the CreateProcess function has PROCESS_ALL_ACCESS access to the process
 * object.
 */
#define CreateProcess CreateProcessW
#else
/**
 * This function is used to run a new program. It creates a new process and its primary thread. The
 * new process executes the specified executable file.
 *
 * @param lpApplicationName Pointer to a null-terminated string that specifies the module to
 *   execute. The string can specify the full path and filename of the module to execute or it can
 *   specify a partial name. In the case of a partial name, the function uses the current drive and
 *   current directory to complete the specification. The lpApplicationName parameter must be non-NULL
 *   and must include the module name.
 * @param lpCommandLine Pointer to a null-terminated string that specifies the command line to
 *   execute. The system adds a null character to the command line, trimming the string if necessary,
 *   to indicate which file was actually used. The lpCommandLine parameter can be NULL. In that case,
 *   the function uses the string pointed to by lpApplicationName as the command line. If both
 *   lpApplicationName and lpCommandLine are non-NULL, *lpApplicationName specifies the module to
 *   execute, and *lpCommandLine specifies the command line. C runtime processes can use the argc and
 *   argv arguments. If the filename does not contain an extension, .EXE is assumed. If the filename
 *   ends in a period (.) with no extension, or the filename contains a path, .EXE is not appended.
 *   Windows CE versions 2.10 and later search the directories indicated by the lpApplicationName
 *   parameter in the following order: The windows (\windows) directory The root (\) directory of the
 *   device An OEM-dependent directory The OEM-defined shell (\ceshell) directory - Embedded Toolkit
 *   users only Windows CE versions 1.0 through 2.01 search the directories indicated by the
 *   lpApplicationName parameter in the following order: The root of the PC Card, if it exists The
 *   windows (\windows) directory The root (\ ) directory of the device
 * @param lpProcessAttributes Not supported; set to NULL.
 * @param lpThreadAttributes Not supported; set to NULL.
 * @param bInheritHandles Not supported; set to NULL.
 * @param dwCreationFlags Specifies additional flags that control the priority class and the
 *   creation of the process. The following creation flags can be specified in any combination, except
 *   as noted: Value Description CREATE_DEFAULT_ERROR_MODE Not supported. CREATE_NEW_CONSOLE The new
 *   process has a new console, instead of inheriting the parent's console. This flag cannot be used
 *   with the DETACHED_PROCESS flag. CREATE_NEW_PROCESS_GROUP Not supported. CREATE_SEPARATE_WOW_VDM
 *   Not supported. CREATE_SHARED_WOW_VDM Not supported. CREATE_SUSPENDED The primary thread of the
 *   new process is created in a suspended state, and does not run until the ResumeThread function is
 *   called. CREATE_UNICODE_ENVIRONMENT Not supported. DEBUG_PROCESS If this flag is set, the calling
 *   process is treated as a debugger, and the new process is a process being debugged. Child
 *   processes of the new process are also debugged. The system notifies the debugger of all debug
 *   events that occur in the process being debugged. If you create a process with this flag set, only
 *   the calling thread (the thread that called CreateProcess) can call the WaitForDebugEvent
 *   function. DEBUG_ONLY_THIS_PROCESS If this flag is set, the calling process is treated as a
 *   debugger, and the new process is a process being debugged. No child processes of the new process
 *   are debugged. The system notifies the debugger of all debug events that occur in the process
 *   being debugged. DETACHED_PROCESS Not supported. Windows CE does not support the concept of a
 *   priority class. The priority of a thread is the only parameter that determines a threads
 *   scheduling priority. For Windows CE version 1.0 and 1.01, the dwCreationFlags parameter only
 *   supports the following values: CREATE_SUSPENDED and zero.
 * @param lpEnvironment Not supported; set to NULL.
 * @param lpCurrentDirectory Not supported; set to NULL.
 * @param lpStartupInfo Not supported; set to NULL.
 * @param lpProcessInformation Pointer to a PROCESS_INFORMATION structure that receives
 *   identification information about the new process.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * The CreateProcess function is used to run a new program. In addition to creating a process,
 * CreateProcess also creates a thread object. The thread is created with an initial stack whose
 * size is described in the image header of the specified program's executable file. The thread
 * begins execution at the image's entry point.
 *
 * The new process and the new thread handles are created with full access rights. For either
 * handle, the handle can be used in any function that requires an object handle to that type.
 *
 * The process is assigned a 32-bit process identifier. The identifier is valid until the process
 * terminates. It can be used to identify the process, or specified in the OpenProcess function to
 * open a handle to the process. The initial thread in the process is also assigned a 32-bit thread
 * identifier. The identifier is valid until the thread terminates and can be used to uniquely
 * identify the thread within the system. These identifiers are returned in the PROCESS_INFORMATION
 * structure.
 *
 * When specifying an application name in the lpApplicationName string, it doesn't matter whether
 * the application name includes the filename extension.
 *
 * ExitThread, CreateThread, and a process that is starting (as the result of a call by
 * CreateProcess) are serialized between each other within a process. Only one of these events can
 * happen in an address space at a time. This means the following restrictions hold:
 *
 * During process startup and DLL initialization routines, new threads can be created, but they do
 * not begin execution until DLL initialization is done for the process.
 *
 * Only one thread in a process can be in a DLL initialization or detach routine at a time.
 *
 * The created process remains in the system until all threads within the process have terminated
 * and all handles to the process and any of its threads have been closed through calls to
 * CloseHandle. The handles for both the process and the main thread must be closed through calls to
 * CloseHandle. If these handles are not needed, it is best to close them immediately after the
 * process is created.
 *
 * When the last thread in a process terminates, the following events occur:
 *
 * All objects opened by the process are implicitly closed.
 *
 * The process's termination status (which is returned by GetExitCodeProcess) changes from its
 * initial value of STILL_ACTIVE to the termination status of the last thread to terminate.
 *
 * The thread object of the main thread is set to the signaled state, satisfying any threads that
 * were waiting on the object.
 *
 * The process object is set to the signaled state, satisfying any threads that were waiting on the
 * object.
 *
 * The handle returned by the CreateProcess function has PROCESS_ALL_ACCESS access to the process
 * object.
 */
#define CreateProcess CreateProcessA
#endif

WINBASEAPI
DWORD
WINAPI
GetProcessVersion(
    DWORD ProcessId
    );

#include <winerror.h>

//
//  These are the generic rights.
//

#define GENERIC_READ                     (0x80000000L)
#define GENERIC_WRITE                    (0x40000000L)
#define GENERIC_EXECUTE                  (0x20000000L)
#define GENERIC_ALL                      (0x10000000L)

#define FILE_SHARE_READ                 0x00000001
#define FILE_SHARE_WRITE                0x00000002

//
// File creation flags must start at the high end since they
// are combined with the attributes
//

#define FILE_FLAG_WRITE_THROUGH         0x80000000
#define FILE_FLAG_OVERLAPPED            0x40000000
#define FILE_FLAG_NO_BUFFERING          0x20000000
#define FILE_FLAG_RANDOM_ACCESS         0x10000000
#define FILE_FLAG_SEQUENTIAL_SCAN       0x08000000
#define FILE_FLAG_DELETE_ON_CLOSE       0x04000000
#define FILE_FLAG_BACKUP_SEMANTICS      0x02000000
#define FILE_FLAG_POSIX_SEMANTICS       0x01000000

#define CREATE_NEW          1
#define CREATE_ALWAYS       2
#define OPEN_EXISTING       3
#define OPEN_ALWAYS         4
#define TRUNCATE_EXISTING   5
#define OPEN_FOR_LOADER		6

// Windows CE File API definitions copied from NT's winbase.h

/**
 * This structure describes a file found by the FindFirstFile or FindNextFile function.
 *
 * If a file has a long file name, the complete name appears in the cFileName member, and the 8.3
 * format truncated version of the name appears in the cAlternateFileName member. Otherwise,
 * cAlternateFileName is empty. As an alternative, you can use the GetShortPathName function to find
 * the 8.3 format version of a file name.
 */
typedef struct _WIN32_FIND_DATAA {
    /**
     * Specifies the file attributes of the file found. It can be one or more of the following values:
     *
     * - FILE_ATTRIBUTE_ARCHIVE: The file or directory is an archive file or directory. Applications use
     * this attribute to mark files for backup or removal.
     *
     * - FILE_ATTRIBUTE_COMPRESSED: The file or directory is compressed. For a file, this means that all
     * of the data in the file is compressed. For a directory, this means that compression is the
     * default for newly created files and subdirectories.
     *
     * - FILE_ATTRIBUTE_DIRECTORY: The handle identifies a directory.
     *
     * - FILE_ATTRIBUTE_ENCRYPTED: The file or directory is encrypted. For a file, this means that all
     * data streams are encrypted. For a directory, this means that encryption is the default for newly
     * created files and subdirectories.
     *
     * - FILE_ATTRIBUTE_HIDDEN: The file or directory is hidden. It is not included in an ordinary
     * directory listing.
     *
     * - FILE_ATTRIBUTE_INROM: This file is an operating system file stored in ROM. These files are
     * read-only; they cannot be modified.
     *
     * - FILE_ATTRIBUTE_NORMAL: The file or directory has no other attributes set. This attribute is
     * valid only if used alone.
     *
     * - FILE_ATTRIBUTE_OFFLINE: The file data is not immediately available. Indicates that the file
     * data has been physically moved to offline storage.
     *
     * - FILE_ATTRIBUTE_READONLY: The file or directory is read-only. Applications can read the file but
     * cannot write to it or delete it. In the case of a directory, applications cannot delete it.
     *
     * - FILE_ATTRIBUTE_REPARSE_POINT: The file has an associated reparse point.
     *
     * - FILE_ATTRIBUTE_ROMMODULE: This file is an operating system file stored in ROM and executed
     * directly from ROM, rather than being first copied to RAM. The CreateFile function cannot be used
     * to access this file, instead the LoadLibrary and CreateProcess functions must be used.
     *
     * - FILE_ATTRIBUTE_ROMSTATICREF: The file is a DLL module that has a static reference from at least
     * one other file that is in the modules section of the image. A file having this attribute can not
     * replace the functionality of the DLL with a RAM copy of the same DLL. A file having this
     * attribute must also have the FILE_ATTRIBUTE_INROM and FILE_ATTRIBUTE_ROMMODULE attributes.
     *
     * - FILE_ATTRIBUTE_SPARSE_FILE: The file is a sparse file.
     *
     * - FILE_ATTRIBUTE_SYSTEM: The file or directory is part of the operating system or is used
     * exclusively by the operating system.
     *
     * - FILE_ATTRIBUTE_TEMPORARY: The file is being used for temporary storage. File systems attempt to
     * keep all of the data in memory for quicker access, rather than flushing it back to mass storage.
     * A temporary file should be deleted by the application as soon as it is no longer needed.
     */
    DWORD dwFileAttributes;
    /**
     * Specifies a FILETIME structure containing the time the file was created. FindFirstFile and
     * FindNextFile report file times in Coordinated Universal Time (UTC) format. These functions set
     * the FILETIME members to zero if the file system containing the file does not support this time
     * member. You can use the FileTimeToLocalFileTime function to convert from UTC to local time, and
     * then use the FileTimeToSystemTime function to convert the local time to a SYSTEMTIME structure
     * containing individual members for the month, day, year, weekday, hour, minute, second, and
     * millisecond.
     */
    FILETIME ftCreationTime;
    /**
     * Specifies a FILETIME structure containing the time that the file was last accessed. The time is
     * in UTC format; the FILETIME members are zero if the file system does not support this time
     * member.
     */
    FILETIME ftLastAccessTime;
    /**
     * Specifies a FILETIME structure containing the time that the file was last written to. The time is
     * in UTC format; the FILETIME members are zero if the file system does not support this time
     * member.
     */
    FILETIME ftLastWriteTime;
    /**
     * Specifies the high-order DWORD value of the file size, in bytes. This value is zero unless the
     * file size is greater than MAXDWORD. The size of the file is equal to (nFileSizeHigh * MAXDWORD) +
     * nFileSizeLow.
     */
    DWORD nFileSizeHigh;
    /**
     * Specifies the low-order DWORD value of the file size, in bytes.
     */
    DWORD nFileSizeLow;
    DWORD dwReserved0;
    DWORD dwReserved1;
    /**
     * Null-terminated string that is the name of the file.
     */
    CHAR  cFileName[ MAX_PATH ];
    CHAR  cAlternateFileName[ 14 ];
} WIN32_FIND_DATAA, *PWIN32_FIND_DATAA, *LPWIN32_FIND_DATAA;

/**
 * This structure describes a file found by the FindFirstFile or FindNextFile function.
 *
 * If a file has a long file name, the complete name appears in the cFileName member, and the 8.3
 * format truncated version of the name appears in the cAlternateFileName member. Otherwise,
 * cAlternateFileName is empty. As an alternative, you can use the GetShortPathName function to find
 * the 8.3 format version of a file name.
 */
typedef struct _WIN32_FIND_DATAW {
    /**
     * Specifies the file attributes of the file found. It can be one or more of the following values:
     *
     * - FILE_ATTRIBUTE_ARCHIVE: The file or directory is an archive file or directory. Applications use
     * this attribute to mark files for backup or removal.
     *
     * - FILE_ATTRIBUTE_COMPRESSED: The file or directory is compressed. For a file, this means that all
     * of the data in the file is compressed. For a directory, this means that compression is the
     * default for newly created files and subdirectories.
     *
     * - FILE_ATTRIBUTE_DIRECTORY: The handle identifies a directory.
     *
     * - FILE_ATTRIBUTE_ENCRYPTED: The file or directory is encrypted. For a file, this means that all
     * data streams are encrypted. For a directory, this means that encryption is the default for newly
     * created files and subdirectories.
     *
     * - FILE_ATTRIBUTE_HIDDEN: The file or directory is hidden. It is not included in an ordinary
     * directory listing.
     *
     * - FILE_ATTRIBUTE_INROM: This file is an operating system file stored in ROM. These files are
     * read-only; they cannot be modified.
     *
     * - FILE_ATTRIBUTE_NORMAL: The file or directory has no other attributes set. This attribute is
     * valid only if used alone.
     *
     * - FILE_ATTRIBUTE_OFFLINE: The file data is not immediately available. Indicates that the file
     * data has been physically moved to offline storage.
     *
     * - FILE_ATTRIBUTE_READONLY: The file or directory is read-only. Applications can read the file but
     * cannot write to it or delete it. In the case of a directory, applications cannot delete it.
     *
     * - FILE_ATTRIBUTE_REPARSE_POINT: The file has an associated reparse point.
     *
     * - FILE_ATTRIBUTE_ROMMODULE: This file is an operating system file stored in ROM and executed
     * directly from ROM, rather than being first copied to RAM. The CreateFile function cannot be used
     * to access this file, instead the LoadLibrary and CreateProcess functions must be used.
     *
     * - FILE_ATTRIBUTE_ROMSTATICREF: The file is a DLL module that has a static reference from at least
     * one other file that is in the modules section of the image. A file having this attribute can not
     * replace the functionality of the DLL with a RAM copy of the same DLL. A file having this
     * attribute must also have the FILE_ATTRIBUTE_INROM and FILE_ATTRIBUTE_ROMMODULE attributes.
     *
     * - FILE_ATTRIBUTE_SPARSE_FILE: The file is a sparse file.
     *
     * - FILE_ATTRIBUTE_SYSTEM: The file or directory is part of the operating system or is used
     * exclusively by the operating system.
     *
     * - FILE_ATTRIBUTE_TEMPORARY: The file is being used for temporary storage. File systems attempt to
     * keep all of the data in memory for quicker access, rather than flushing it back to mass storage.
     * A temporary file should be deleted by the application as soon as it is no longer needed.
     */
    DWORD dwFileAttributes;
    /**
     * Specifies a FILETIME structure containing the time the file was created. FindFirstFile and
     * FindNextFile report file times in Coordinated Universal Time (UTC) format. These functions set
     * the FILETIME members to zero if the file system containing the file does not support this time
     * member. You can use the FileTimeToLocalFileTime function to convert from UTC to local time, and
     * then use the FileTimeToSystemTime function to convert the local time to a SYSTEMTIME structure
     * containing individual members for the month, day, year, weekday, hour, minute, second, and
     * millisecond.
     */
    FILETIME ftCreationTime;
    /**
     * Specifies a FILETIME structure containing the time that the file was last accessed. The time is
     * in UTC format; the FILETIME members are zero if the file system does not support this time
     * member.
     */
    FILETIME ftLastAccessTime;
    /**
     * Specifies a FILETIME structure containing the time that the file was last written to. The time is
     * in UTC format; the FILETIME members are zero if the file system does not support this time
     * member.
     */
    FILETIME ftLastWriteTime;
    /**
     * Specifies the high-order DWORD value of the file size, in bytes. This value is zero unless the
     * file size is greater than MAXDWORD. The size of the file is equal to (nFileSizeHigh * MAXDWORD) +
     * nFileSizeLow.
     */
    DWORD nFileSizeHigh;
    /**
     * Specifies the low-order DWORD value of the file size, in bytes.
     */
    DWORD nFileSizeLow;
    /**
     * Specifies the object identifier of the file.
     */
    DWORD dwOID;
    /**
     * Null-terminated string that is the name of the file.
     */
    WCHAR cFileName[ MAX_PATH ];
} WIN32_FIND_DATAW, *PWIN32_FIND_DATAW, *LPWIN32_FIND_DATAW;
#ifdef UNICODE
typedef WIN32_FIND_DATAW WIN32_FIND_DATA;
typedef PWIN32_FIND_DATAW PWIN32_FIND_DATA;
typedef LPWIN32_FIND_DATAW LPWIN32_FIND_DATA;
#else
typedef WIN32_FIND_DATAA WIN32_FIND_DATA;
typedef PWIN32_FIND_DATAA PWIN32_FIND_DATA;
typedef LPWIN32_FIND_DATAA LPWIN32_FIND_DATA;
#endif // UNICODE

/**
 * This function returns the calling thread's last-error code value. A remote application interface
 * (RAPI) version of this function exists, and it is named CeGetLastError.
 *
 * @return The calling thread's last-error code value indicates success. Functions set this value by
 *   calling the SetLastError function. The Return Value section of each reference page notes the
 *   conditions under which the function sets the last-error code.
 *
 * You should call the GetLastError function immediately when a function's return value indicates
 * that such a call will return useful data. That is because some functions call SetLastError(0)
 * when they succeed, wiping out the error code set by the most recently failed function.
 *
 * Most functions in the Win32 API that set the thread's last error code value set it when they
 * fail; a few functions set it when they succeed. Function failure is typically indicated by a
 * return value error code such as FALSE, NULL, 0xFFFFFFFF, or -1. Some functions call SetLastError
 * under conditions of success; those cases are noted in each function's reference page.
 *
 * Error codes are 32-bit values (bit 31 is the most significant bit). Bit 29 is reserved for
 * application-defined error codes; no system error code has this bit set. If you are defining an
 * error code for your application, set this bit to one. That indicates that the error code has been
 * defined by an application, and ensures that your error code does not conflict with any error
 * codes defined by the system.
 *
 * To obtain an error string for system error codes, use the FormatMessage function. For a complete
 * list of error codes, see Error Values or the SDK header file WINERROR.H.
 */
WINBASEAPI
DWORD
WINAPI
GetLastError(
    VOID
    );

/**
 * This function retrieves the number of milliseconds that have elapsed since Windows CE was
 * started.
 *
 * @return The number of milliseconds that have elapsed since the system was started indicates
 *   success.
 *
 * The the resolution of the system timer is based on the OEMs setting. Check with the OEM for
 * details.
 *
 * The elapsed time is stored as a DWORD value. Therefore, the time will wrap around to zero if the
 * system is run continuously for 49.7 days.
 */
WINBASEAPI
DWORD
WINAPI
GetTickCount(
    VOID
    );

// @CESYSGEN IF COREDLL_FMTMSG

/**
 * This function formats a message string.
 *
 * @param dwFlags [in] Specifies aspects of the formatting process and how to interpret the lpSource
 *   parameter. The low-order byte of dwFlags specifies how the function handles line breaks in the
 *   output buffer. The low-order byte can also specify the maximum width of a formatted output line.
 *   This parameter can be a combination of the following bit flags: Value Description
 *   FORMAT_MESSAGE_ALLOCATE_BUFFER Specifies that the lpBuffer parameter is a pointer to a PVOID
 *   pointer, and that the nSize parameter specifies the minimum number of bytes (ANSI version) or
 *   characters (Unicode version) to allocate for an output message buffer. The function allocates a
 *   buffer large enough to hold the formatted message, and places a pointer to the allocated buffer
 *   at the address specified by lpBuffer. The caller should use the LocalFree function to free the
 *   buffer when it is no longer needed. FORMAT_MESSAGE_IGNORE_INSERTS Specifies that insert sequences
 *   in the message definition are to be ignored and passed through to the output buffer unchanged.
 *   This flag is useful for fetching a message for later formatting. If this flag is set, the
 *   Arguments parameter is ignored. FORMAT_MESSAGE_FROM_STRING Specifies that lpSource is a pointer
 *   to a null-terminated message definition. The message definition may contain insert sequences,
 *   just as the message text in a message table resource may. Cannot be used with
 *   FORMAT_MESSAGE_FROM_HMODULE or FORMAT_MESSAGE_FROM_SYSTEM. FORMAT_MESSAGE_FROM_HMODULE Specifies
 *   that lpSource is a module handle containing the message-table resource(s) to search. If this
 *   lpSource handle is NULL, the current process's application image file will be searched. Cannot be
 *   used with FORMAT_MESSAGE_FROM_STRING. FORMAT_MESSAGE_FROM_SYSTEM Specifies that the function
 *   should search the system message-table resource(s) for the requested message. If this flag is
 *   specified with FORMAT_MESSAGE_FROM_HMODULE, the function searches the system message table if the
 *   message is not found in the module specified by lpSource. Cannot be used with
 *   FORMAT_MESSAGE_FROM_STRING. If this flag is specified, an application can pass the result of the
 *   GetLastError function to retrieve the message text for a system-defined error. Not all Windows
 *   CE-based devices will contain the system message-table resources. This is a selectable part of
 *   the Windows CE operating system and is often removed to conserve space.
 *   FORMAT_MESSAGE_ARGUMENT_ARRAY Specifies that the Arguments parameter is not a va_list structure,
 *   but instead is just a pointer to an array of 32-bit values that represent the arguments. The
 *   low-order byte of dwFlags can specify the maximum width of a formatted output line. Use the
 *   FORMAT_MESSAGE_MAX_WIDTH_MASK constant and bitwise Boolean operations to set and retrieve this
 *   maximum width value. The following list shows how FormatMessage interprets the value of the
 *   low-order byte. Value Description 0 There are no output line width restrictions. The function
 *   stores line breaks that are in the message definition text into the output buffer. A nonzero
 *   value other than FORMAT_MESSAGE_MAX_WIDTH_MASK The nonzero value is the maximum number of
 *   characters in an output line. The function ignores regular line breaks in the message definition
 *   text. The function never splits a string delimited by white space across a line break. The
 *   function stores hard-coded line breaks in the message definition text into the output buffer.
 *   Hard-coded line breaks are coded with the %n escape sequence. FORMAT_MESSAGE_MAX_WIDTH_MASK The
 *   function ignores regular line breaks in the message definition text. The function stores
 *   hard-coded line breaks in the message definition text into the output buffer. The function
 *   generates no new line breaks.
 * @param lpSource [in] Pointer to the location of the message definition. The type of this
 *   parameter depends upon the settings in the dwFlags parameter. Value Description
 *   FORMAT_MESSAGE_FROM_HMODULE The lpSource parameter is an hModule of the module that contains the
 *   message table to search. FORMAT_MESSAGE_FROM_STRING The lpSource parameter is an LPTSTR that
 *   points to unformatted message text. It will be scanned for inserts and formatted accordingly. If
 *   neither of these flags is set in dwFlags, then lpSource is ignored.
 * @param dwMessageId [in] Specifies the 32-bit message identifier for the requested message. This
 *   parameter is ignored if dwFlags includes FORMAT_MESSAGE_FROM_STRING.
 * @param dwLanguageId [in] Not supported.
 * @param lpBuffer [out] Pointer to a buffer for the formatted (and null-terminated) message. If
 *   dwFlags includes FORMAT_MESSAGE_ALLOCATE_BUFFER, the function allocates a buffer using the
 *   LocalAlloc function, and places the pointer to the buffer at the address specified in lpBuffer.
 * @param nSize [in] If the FORMAT_MESSAGE_ALLOCATE_BUFFER flag is not set, this parameter specifies
 *   the maximum number of characters that can be stored in the output buffer. If
 *   FORMAT_MESSAGE_ALLOCATE_BUFFER is set, this parameter specifies the minimum number of bytes or
 *   characters to allocate for an output buffer.
 * @param Arguments [in] Pointer to an array of 32-bit values that are used as insert values in the
 *   formatted message. A %1 in the format string indicates the first value in the Arguments array; a
 *   %2 indicates the second argument; and so on. The interpretation of each 32-bit value depends on
 *   the formatting information associated with the insert in the message definition. The default is
 *   to treat each value as a pointer to a null-terminated string. By default, the Arguments parameter
 *   is of type va_list*, which is a language- and implementation-specific data type for describing a
 *   variable number of arguments. If you do not have a pointer of type va_list*, then specify the
 *   FORMAT_MESSAGE_ARGUMENT_ARRAY flag and pass a pointer to an array of 32-bit values; those values
 *   are input to the message formatted as the insert values. Each insert must have a corresponding
 *   element in the array.
 *
 * @return The number of characters stored in the output buffer, excluding the terminating null
 *   character, indicates success. Zero indicates failure. To get extended error information, call
 *   GetLastError.
 *
 * This function requires a message definition as input. The message definition can come from a
 * buffer passed into the function. It can come from a message table resource in an already loaded
 * module. Or the caller can ask the function to search the system's message table resources for the
 * message definition. FormatMessage finds the message definition in a message table resource based
 * on a message identifier. FormatMessage copies the formatted message text to an output buffer,
 * processing any embedded insert sequences if requested.
 *
 * The FormatMessage function can be used to obtain error message strings for the system error codes
 * returned by GetLastError, as shown in the following sample code.
 *
 *     LPVOID lpMsgBuf;
 *     FormatMessage(
 *         FORMAT_MESSAGE_ALLOCATE_BUFFER |
 *         FORMAT_MESSAGE_FROM_SYSTEM |
 *         FORMAT_MESSAGE_IGNORE_INSERTS,
 *         NULL,
 *         GetLastError(),
 *         0, // Default language
 *         (LPTSTR) &lpMsgBuf,
 *         0,
 *         NULL
 *     );
 *     // Process any inserts in lpMsgBuf.
 *     // ...
 *     // Display the string.
 *     MessageBox( NULL, (LPCTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION );
 *     // Free the buffer.
 *     LocalFree( lpMsgBuf );
 *
 * Within the message text, several escape sequences are supported for dynamically formatting the
 * message. These escape sequences and their meanings are shown in the following list. All escape
 * sequences start with the percent character (%).
 *
 * - %0: Terminates a message text line without a trailing newline character. This escape sequence
 * can be used to build up long lines or to terminate the message itself without a trailing newline
 * character. It is useful for prompt messages.
 *
 * - %n!printf format string!: Identifies an insert. The value of n can be in the range 1 through
 * 99. The printf format string (which must be bracketed by exclamation marks) is optional and
 * defaults to !s! if not specified. The printf format string can contain the * specifier for either
 * the precision or the width component. If * is specified for one component, the FormatMessage
 * function uses insert %n+1; it uses %n+2 if * is specified for both components. Floating-point
 * printf format specifiers-e, E, f, and g-are not supported. The workaround is to to use the
 * sprintf function to format the floating-point number into a temporary buffer, then use that
 * buffer as the insert string.
 *
 * Any other nondigit character following a percent character is formatted in the output message
 * without the percent character. Following are some examples:
 *
 * Format string Resulting output %% A single percent sign in the formatted message text. %n A hard
 * line break when the format string occurs at the end of a line. This format string is useful when
 * FormatMessage is supplying regular line breaks so the message fits in a certain width. %space A
 * space in the formatted message text. This format string can be used to ensure the appropriate
 * number of trailing spaces in a message text line. %. A single period in the formatted message
 * text. This format string can be used to include a single period at the beginning of a line
 * without terminating the message text definition. %! A single exclamation point in the formatted
 * message text. This format string can be used to include an exclamation point immediately after an
 * insert without its being mistaken for the beginning of a printf format string.
 */
WINBASEAPI
DWORD
WINAPI
FormatMessageA(
    DWORD dwFlags,
    LPCVOID lpSource,
    DWORD dwMessageId,
    DWORD dwLanguageId,
    LPSTR lpBuffer,
    DWORD nSize,
    va_list *Arguments
    );

#ifndef COREDLL
WINBASEAPI
#endif
/**
 * This function formats a message string.
 *
 * @param dwFlags [in] Specifies aspects of the formatting process and how to interpret the lpSource
 *   parameter. The low-order byte of dwFlags specifies how the function handles line breaks in the
 *   output buffer. The low-order byte can also specify the maximum width of a formatted output line.
 *   This parameter can be a combination of the following bit flags: Value Description
 *   FORMAT_MESSAGE_ALLOCATE_BUFFER Specifies that the lpBuffer parameter is a pointer to a PVOID
 *   pointer, and that the nSize parameter specifies the minimum number of bytes (ANSI version) or
 *   characters (Unicode version) to allocate for an output message buffer. The function allocates a
 *   buffer large enough to hold the formatted message, and places a pointer to the allocated buffer
 *   at the address specified by lpBuffer. The caller should use the LocalFree function to free the
 *   buffer when it is no longer needed. FORMAT_MESSAGE_IGNORE_INSERTS Specifies that insert sequences
 *   in the message definition are to be ignored and passed through to the output buffer unchanged.
 *   This flag is useful for fetching a message for later formatting. If this flag is set, the
 *   Arguments parameter is ignored. FORMAT_MESSAGE_FROM_STRING Specifies that lpSource is a pointer
 *   to a null-terminated message definition. The message definition may contain insert sequences,
 *   just as the message text in a message table resource may. Cannot be used with
 *   FORMAT_MESSAGE_FROM_HMODULE or FORMAT_MESSAGE_FROM_SYSTEM. FORMAT_MESSAGE_FROM_HMODULE Specifies
 *   that lpSource is a module handle containing the message-table resource(s) to search. If this
 *   lpSource handle is NULL, the current process's application image file will be searched. Cannot be
 *   used with FORMAT_MESSAGE_FROM_STRING. FORMAT_MESSAGE_FROM_SYSTEM Specifies that the function
 *   should search the system message-table resource(s) for the requested message. If this flag is
 *   specified with FORMAT_MESSAGE_FROM_HMODULE, the function searches the system message table if the
 *   message is not found in the module specified by lpSource. Cannot be used with
 *   FORMAT_MESSAGE_FROM_STRING. If this flag is specified, an application can pass the result of the
 *   GetLastError function to retrieve the message text for a system-defined error. Not all Windows
 *   CE-based devices will contain the system message-table resources. This is a selectable part of
 *   the Windows CE operating system and is often removed to conserve space.
 *   FORMAT_MESSAGE_ARGUMENT_ARRAY Specifies that the Arguments parameter is not a va_list structure,
 *   but instead is just a pointer to an array of 32-bit values that represent the arguments. The
 *   low-order byte of dwFlags can specify the maximum width of a formatted output line. Use the
 *   FORMAT_MESSAGE_MAX_WIDTH_MASK constant and bitwise Boolean operations to set and retrieve this
 *   maximum width value. The following list shows how FormatMessage interprets the value of the
 *   low-order byte. Value Description 0 There are no output line width restrictions. The function
 *   stores line breaks that are in the message definition text into the output buffer. A nonzero
 *   value other than FORMAT_MESSAGE_MAX_WIDTH_MASK The nonzero value is the maximum number of
 *   characters in an output line. The function ignores regular line breaks in the message definition
 *   text. The function never splits a string delimited by white space across a line break. The
 *   function stores hard-coded line breaks in the message definition text into the output buffer.
 *   Hard-coded line breaks are coded with the %n escape sequence. FORMAT_MESSAGE_MAX_WIDTH_MASK The
 *   function ignores regular line breaks in the message definition text. The function stores
 *   hard-coded line breaks in the message definition text into the output buffer. The function
 *   generates no new line breaks.
 * @param lpSource [in] Pointer to the location of the message definition. The type of this
 *   parameter depends upon the settings in the dwFlags parameter. Value Description
 *   FORMAT_MESSAGE_FROM_HMODULE The lpSource parameter is an hModule of the module that contains the
 *   message table to search. FORMAT_MESSAGE_FROM_STRING The lpSource parameter is an LPTSTR that
 *   points to unformatted message text. It will be scanned for inserts and formatted accordingly. If
 *   neither of these flags is set in dwFlags, then lpSource is ignored.
 * @param dwMessageId [in] Specifies the 32-bit message identifier for the requested message. This
 *   parameter is ignored if dwFlags includes FORMAT_MESSAGE_FROM_STRING.
 * @param dwLanguageId [in] Not supported.
 * @param lpBuffer [out] Pointer to a buffer for the formatted (and null-terminated) message. If
 *   dwFlags includes FORMAT_MESSAGE_ALLOCATE_BUFFER, the function allocates a buffer using the
 *   LocalAlloc function, and places the pointer to the buffer at the address specified in lpBuffer.
 * @param nSize [in] If the FORMAT_MESSAGE_ALLOCATE_BUFFER flag is not set, this parameter specifies
 *   the maximum number of characters that can be stored in the output buffer. If
 *   FORMAT_MESSAGE_ALLOCATE_BUFFER is set, this parameter specifies the minimum number of bytes or
 *   characters to allocate for an output buffer.
 * @param Arguments [in] Pointer to an array of 32-bit values that are used as insert values in the
 *   formatted message. A %1 in the format string indicates the first value in the Arguments array; a
 *   %2 indicates the second argument; and so on. The interpretation of each 32-bit value depends on
 *   the formatting information associated with the insert in the message definition. The default is
 *   to treat each value as a pointer to a null-terminated string. By default, the Arguments parameter
 *   is of type va_list*, which is a language- and implementation-specific data type for describing a
 *   variable number of arguments. If you do not have a pointer of type va_list*, then specify the
 *   FORMAT_MESSAGE_ARGUMENT_ARRAY flag and pass a pointer to an array of 32-bit values; those values
 *   are input to the message formatted as the insert values. Each insert must have a corresponding
 *   element in the array.
 *
 * @return The number of characters stored in the output buffer, excluding the terminating null
 *   character, indicates success. Zero indicates failure. To get extended error information, call
 *   GetLastError.
 *
 * This function requires a message definition as input. The message definition can come from a
 * buffer passed into the function. It can come from a message table resource in an already loaded
 * module. Or the caller can ask the function to search the system's message table resources for the
 * message definition. FormatMessage finds the message definition in a message table resource based
 * on a message identifier. FormatMessage copies the formatted message text to an output buffer,
 * processing any embedded insert sequences if requested.
 *
 * The FormatMessage function can be used to obtain error message strings for the system error codes
 * returned by GetLastError, as shown in the following sample code.
 *
 *     LPVOID lpMsgBuf;
 *     FormatMessage(
 *         FORMAT_MESSAGE_ALLOCATE_BUFFER |
 *         FORMAT_MESSAGE_FROM_SYSTEM |
 *         FORMAT_MESSAGE_IGNORE_INSERTS,
 *         NULL,
 *         GetLastError(),
 *         0, // Default language
 *         (LPTSTR) &lpMsgBuf,
 *         0,
 *         NULL
 *     );
 *     // Process any inserts in lpMsgBuf.
 *     // ...
 *     // Display the string.
 *     MessageBox( NULL, (LPCTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION );
 *     // Free the buffer.
 *     LocalFree( lpMsgBuf );
 *
 * Within the message text, several escape sequences are supported for dynamically formatting the
 * message. These escape sequences and their meanings are shown in the following list. All escape
 * sequences start with the percent character (%).
 *
 * - %0: Terminates a message text line without a trailing newline character. This escape sequence
 * can be used to build up long lines or to terminate the message itself without a trailing newline
 * character. It is useful for prompt messages.
 *
 * - %n!printf format string!: Identifies an insert. The value of n can be in the range 1 through
 * 99. The printf format string (which must be bracketed by exclamation marks) is optional and
 * defaults to !s! if not specified. The printf format string can contain the * specifier for either
 * the precision or the width component. If * is specified for one component, the FormatMessage
 * function uses insert %n+1; it uses %n+2 if * is specified for both components. Floating-point
 * printf format specifiers-e, E, f, and g-are not supported. The workaround is to to use the
 * sprintf function to format the floating-point number into a temporary buffer, then use that
 * buffer as the insert string.
 *
 * Any other nondigit character following a percent character is formatted in the output message
 * without the percent character. Following are some examples:
 *
 * Format string Resulting output %% A single percent sign in the formatted message text. %n A hard
 * line break when the format string occurs at the end of a line. This format string is useful when
 * FormatMessage is supplying regular line breaks so the message fits in a certain width. %space A
 * space in the formatted message text. This format string can be used to ensure the appropriate
 * number of trailing spaces in a message text line. %. A single period in the formatted message
 * text. This format string can be used to include a single period at the beginning of a line
 * without terminating the message text definition. %! A single exclamation point in the formatted
 * message text. This format string can be used to include an exclamation point immediately after an
 * insert without its being mistaken for the beginning of a printf format string.
 */
DWORD
WINAPI
FormatMessageW(
    DWORD dwFlags,
    LPCVOID lpSource,
    DWORD dwMessageId,
    DWORD dwLanguageId,
    LPWSTR lpBuffer,
    DWORD nSize,
    va_list *Arguments
    );

#ifdef UNICODE
/**
 * This function formats a message string.
 *
 * @param dwFlags [in] Specifies aspects of the formatting process and how to interpret the lpSource
 *   parameter. The low-order byte of dwFlags specifies how the function handles line breaks in the
 *   output buffer. The low-order byte can also specify the maximum width of a formatted output line.
 *   This parameter can be a combination of the following bit flags: Value Description
 *   FORMAT_MESSAGE_ALLOCATE_BUFFER Specifies that the lpBuffer parameter is a pointer to a PVOID
 *   pointer, and that the nSize parameter specifies the minimum number of bytes (ANSI version) or
 *   characters (Unicode version) to allocate for an output message buffer. The function allocates a
 *   buffer large enough to hold the formatted message, and places a pointer to the allocated buffer
 *   at the address specified by lpBuffer. The caller should use the LocalFree function to free the
 *   buffer when it is no longer needed. FORMAT_MESSAGE_IGNORE_INSERTS Specifies that insert sequences
 *   in the message definition are to be ignored and passed through to the output buffer unchanged.
 *   This flag is useful for fetching a message for later formatting. If this flag is set, the
 *   Arguments parameter is ignored. FORMAT_MESSAGE_FROM_STRING Specifies that lpSource is a pointer
 *   to a null-terminated message definition. The message definition may contain insert sequences,
 *   just as the message text in a message table resource may. Cannot be used with
 *   FORMAT_MESSAGE_FROM_HMODULE or FORMAT_MESSAGE_FROM_SYSTEM. FORMAT_MESSAGE_FROM_HMODULE Specifies
 *   that lpSource is a module handle containing the message-table resource(s) to search. If this
 *   lpSource handle is NULL, the current process's application image file will be searched. Cannot be
 *   used with FORMAT_MESSAGE_FROM_STRING. FORMAT_MESSAGE_FROM_SYSTEM Specifies that the function
 *   should search the system message-table resource(s) for the requested message. If this flag is
 *   specified with FORMAT_MESSAGE_FROM_HMODULE, the function searches the system message table if the
 *   message is not found in the module specified by lpSource. Cannot be used with
 *   FORMAT_MESSAGE_FROM_STRING. If this flag is specified, an application can pass the result of the
 *   GetLastError function to retrieve the message text for a system-defined error. Not all Windows
 *   CE-based devices will contain the system message-table resources. This is a selectable part of
 *   the Windows CE operating system and is often removed to conserve space.
 *   FORMAT_MESSAGE_ARGUMENT_ARRAY Specifies that the Arguments parameter is not a va_list structure,
 *   but instead is just a pointer to an array of 32-bit values that represent the arguments. The
 *   low-order byte of dwFlags can specify the maximum width of a formatted output line. Use the
 *   FORMAT_MESSAGE_MAX_WIDTH_MASK constant and bitwise Boolean operations to set and retrieve this
 *   maximum width value. The following list shows how FormatMessage interprets the value of the
 *   low-order byte. Value Description 0 There are no output line width restrictions. The function
 *   stores line breaks that are in the message definition text into the output buffer. A nonzero
 *   value other than FORMAT_MESSAGE_MAX_WIDTH_MASK The nonzero value is the maximum number of
 *   characters in an output line. The function ignores regular line breaks in the message definition
 *   text. The function never splits a string delimited by white space across a line break. The
 *   function stores hard-coded line breaks in the message definition text into the output buffer.
 *   Hard-coded line breaks are coded with the %n escape sequence. FORMAT_MESSAGE_MAX_WIDTH_MASK The
 *   function ignores regular line breaks in the message definition text. The function stores
 *   hard-coded line breaks in the message definition text into the output buffer. The function
 *   generates no new line breaks.
 * @param lpSource [in] Pointer to the location of the message definition. The type of this
 *   parameter depends upon the settings in the dwFlags parameter. Value Description
 *   FORMAT_MESSAGE_FROM_HMODULE The lpSource parameter is an hModule of the module that contains the
 *   message table to search. FORMAT_MESSAGE_FROM_STRING The lpSource parameter is an LPTSTR that
 *   points to unformatted message text. It will be scanned for inserts and formatted accordingly. If
 *   neither of these flags is set in dwFlags, then lpSource is ignored.
 * @param dwMessageId [in] Specifies the 32-bit message identifier for the requested message. This
 *   parameter is ignored if dwFlags includes FORMAT_MESSAGE_FROM_STRING.
 * @param dwLanguageId [in] Not supported.
 * @param lpBuffer [out] Pointer to a buffer for the formatted (and null-terminated) message. If
 *   dwFlags includes FORMAT_MESSAGE_ALLOCATE_BUFFER, the function allocates a buffer using the
 *   LocalAlloc function, and places the pointer to the buffer at the address specified in lpBuffer.
 * @param nSize [in] If the FORMAT_MESSAGE_ALLOCATE_BUFFER flag is not set, this parameter specifies
 *   the maximum number of characters that can be stored in the output buffer. If
 *   FORMAT_MESSAGE_ALLOCATE_BUFFER is set, this parameter specifies the minimum number of bytes or
 *   characters to allocate for an output buffer.
 * @param Arguments [in] Pointer to an array of 32-bit values that are used as insert values in the
 *   formatted message. A %1 in the format string indicates the first value in the Arguments array; a
 *   %2 indicates the second argument; and so on. The interpretation of each 32-bit value depends on
 *   the formatting information associated with the insert in the message definition. The default is
 *   to treat each value as a pointer to a null-terminated string. By default, the Arguments parameter
 *   is of type va_list*, which is a language- and implementation-specific data type for describing a
 *   variable number of arguments. If you do not have a pointer of type va_list*, then specify the
 *   FORMAT_MESSAGE_ARGUMENT_ARRAY flag and pass a pointer to an array of 32-bit values; those values
 *   are input to the message formatted as the insert values. Each insert must have a corresponding
 *   element in the array.
 *
 * @return The number of characters stored in the output buffer, excluding the terminating null
 *   character, indicates success. Zero indicates failure. To get extended error information, call
 *   GetLastError.
 *
 * This function requires a message definition as input. The message definition can come from a
 * buffer passed into the function. It can come from a message table resource in an already loaded
 * module. Or the caller can ask the function to search the system's message table resources for the
 * message definition. FormatMessage finds the message definition in a message table resource based
 * on a message identifier. FormatMessage copies the formatted message text to an output buffer,
 * processing any embedded insert sequences if requested.
 *
 * The FormatMessage function can be used to obtain error message strings for the system error codes
 * returned by GetLastError, as shown in the following sample code.
 *
 *     LPVOID lpMsgBuf;
 *     FormatMessage(
 *         FORMAT_MESSAGE_ALLOCATE_BUFFER |
 *         FORMAT_MESSAGE_FROM_SYSTEM |
 *         FORMAT_MESSAGE_IGNORE_INSERTS,
 *         NULL,
 *         GetLastError(),
 *         0, // Default language
 *         (LPTSTR) &lpMsgBuf,
 *         0,
 *         NULL
 *     );
 *     // Process any inserts in lpMsgBuf.
 *     // ...
 *     // Display the string.
 *     MessageBox( NULL, (LPCTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION );
 *     // Free the buffer.
 *     LocalFree( lpMsgBuf );
 *
 * Within the message text, several escape sequences are supported for dynamically formatting the
 * message. These escape sequences and their meanings are shown in the following list. All escape
 * sequences start with the percent character (%).
 *
 * - %0: Terminates a message text line without a trailing newline character. This escape sequence
 * can be used to build up long lines or to terminate the message itself without a trailing newline
 * character. It is useful for prompt messages.
 *
 * - %n!printf format string!: Identifies an insert. The value of n can be in the range 1 through
 * 99. The printf format string (which must be bracketed by exclamation marks) is optional and
 * defaults to !s! if not specified. The printf format string can contain the * specifier for either
 * the precision or the width component. If * is specified for one component, the FormatMessage
 * function uses insert %n+1; it uses %n+2 if * is specified for both components. Floating-point
 * printf format specifiers-e, E, f, and g-are not supported. The workaround is to to use the
 * sprintf function to format the floating-point number into a temporary buffer, then use that
 * buffer as the insert string.
 *
 * Any other nondigit character following a percent character is formatted in the output message
 * without the percent character. Following are some examples:
 *
 * Format string Resulting output %% A single percent sign in the formatted message text. %n A hard
 * line break when the format string occurs at the end of a line. This format string is useful when
 * FormatMessage is supplying regular line breaks so the message fits in a certain width. %space A
 * space in the formatted message text. This format string can be used to ensure the appropriate
 * number of trailing spaces in a message text line. %. A single period in the formatted message
 * text. This format string can be used to include a single period at the beginning of a line
 * without terminating the message text definition. %! A single exclamation point in the formatted
 * message text. This format string can be used to include an exclamation point immediately after an
 * insert without its being mistaken for the beginning of a printf format string.
 */
#define FormatMessage  FormatMessageW
#else
/**
 * This function formats a message string.
 *
 * @param dwFlags [in] Specifies aspects of the formatting process and how to interpret the lpSource
 *   parameter. The low-order byte of dwFlags specifies how the function handles line breaks in the
 *   output buffer. The low-order byte can also specify the maximum width of a formatted output line.
 *   This parameter can be a combination of the following bit flags: Value Description
 *   FORMAT_MESSAGE_ALLOCATE_BUFFER Specifies that the lpBuffer parameter is a pointer to a PVOID
 *   pointer, and that the nSize parameter specifies the minimum number of bytes (ANSI version) or
 *   characters (Unicode version) to allocate for an output message buffer. The function allocates a
 *   buffer large enough to hold the formatted message, and places a pointer to the allocated buffer
 *   at the address specified by lpBuffer. The caller should use the LocalFree function to free the
 *   buffer when it is no longer needed. FORMAT_MESSAGE_IGNORE_INSERTS Specifies that insert sequences
 *   in the message definition are to be ignored and passed through to the output buffer unchanged.
 *   This flag is useful for fetching a message for later formatting. If this flag is set, the
 *   Arguments parameter is ignored. FORMAT_MESSAGE_FROM_STRING Specifies that lpSource is a pointer
 *   to a null-terminated message definition. The message definition may contain insert sequences,
 *   just as the message text in a message table resource may. Cannot be used with
 *   FORMAT_MESSAGE_FROM_HMODULE or FORMAT_MESSAGE_FROM_SYSTEM. FORMAT_MESSAGE_FROM_HMODULE Specifies
 *   that lpSource is a module handle containing the message-table resource(s) to search. If this
 *   lpSource handle is NULL, the current process's application image file will be searched. Cannot be
 *   used with FORMAT_MESSAGE_FROM_STRING. FORMAT_MESSAGE_FROM_SYSTEM Specifies that the function
 *   should search the system message-table resource(s) for the requested message. If this flag is
 *   specified with FORMAT_MESSAGE_FROM_HMODULE, the function searches the system message table if the
 *   message is not found in the module specified by lpSource. Cannot be used with
 *   FORMAT_MESSAGE_FROM_STRING. If this flag is specified, an application can pass the result of the
 *   GetLastError function to retrieve the message text for a system-defined error. Not all Windows
 *   CE-based devices will contain the system message-table resources. This is a selectable part of
 *   the Windows CE operating system and is often removed to conserve space.
 *   FORMAT_MESSAGE_ARGUMENT_ARRAY Specifies that the Arguments parameter is not a va_list structure,
 *   but instead is just a pointer to an array of 32-bit values that represent the arguments. The
 *   low-order byte of dwFlags can specify the maximum width of a formatted output line. Use the
 *   FORMAT_MESSAGE_MAX_WIDTH_MASK constant and bitwise Boolean operations to set and retrieve this
 *   maximum width value. The following list shows how FormatMessage interprets the value of the
 *   low-order byte. Value Description 0 There are no output line width restrictions. The function
 *   stores line breaks that are in the message definition text into the output buffer. A nonzero
 *   value other than FORMAT_MESSAGE_MAX_WIDTH_MASK The nonzero value is the maximum number of
 *   characters in an output line. The function ignores regular line breaks in the message definition
 *   text. The function never splits a string delimited by white space across a line break. The
 *   function stores hard-coded line breaks in the message definition text into the output buffer.
 *   Hard-coded line breaks are coded with the %n escape sequence. FORMAT_MESSAGE_MAX_WIDTH_MASK The
 *   function ignores regular line breaks in the message definition text. The function stores
 *   hard-coded line breaks in the message definition text into the output buffer. The function
 *   generates no new line breaks.
 * @param lpSource [in] Pointer to the location of the message definition. The type of this
 *   parameter depends upon the settings in the dwFlags parameter. Value Description
 *   FORMAT_MESSAGE_FROM_HMODULE The lpSource parameter is an hModule of the module that contains the
 *   message table to search. FORMAT_MESSAGE_FROM_STRING The lpSource parameter is an LPTSTR that
 *   points to unformatted message text. It will be scanned for inserts and formatted accordingly. If
 *   neither of these flags is set in dwFlags, then lpSource is ignored.
 * @param dwMessageId [in] Specifies the 32-bit message identifier for the requested message. This
 *   parameter is ignored if dwFlags includes FORMAT_MESSAGE_FROM_STRING.
 * @param dwLanguageId [in] Not supported.
 * @param lpBuffer [out] Pointer to a buffer for the formatted (and null-terminated) message. If
 *   dwFlags includes FORMAT_MESSAGE_ALLOCATE_BUFFER, the function allocates a buffer using the
 *   LocalAlloc function, and places the pointer to the buffer at the address specified in lpBuffer.
 * @param nSize [in] If the FORMAT_MESSAGE_ALLOCATE_BUFFER flag is not set, this parameter specifies
 *   the maximum number of characters that can be stored in the output buffer. If
 *   FORMAT_MESSAGE_ALLOCATE_BUFFER is set, this parameter specifies the minimum number of bytes or
 *   characters to allocate for an output buffer.
 * @param Arguments [in] Pointer to an array of 32-bit values that are used as insert values in the
 *   formatted message. A %1 in the format string indicates the first value in the Arguments array; a
 *   %2 indicates the second argument; and so on. The interpretation of each 32-bit value depends on
 *   the formatting information associated with the insert in the message definition. The default is
 *   to treat each value as a pointer to a null-terminated string. By default, the Arguments parameter
 *   is of type va_list*, which is a language- and implementation-specific data type for describing a
 *   variable number of arguments. If you do not have a pointer of type va_list*, then specify the
 *   FORMAT_MESSAGE_ARGUMENT_ARRAY flag and pass a pointer to an array of 32-bit values; those values
 *   are input to the message formatted as the insert values. Each insert must have a corresponding
 *   element in the array.
 *
 * @return The number of characters stored in the output buffer, excluding the terminating null
 *   character, indicates success. Zero indicates failure. To get extended error information, call
 *   GetLastError.
 *
 * This function requires a message definition as input. The message definition can come from a
 * buffer passed into the function. It can come from a message table resource in an already loaded
 * module. Or the caller can ask the function to search the system's message table resources for the
 * message definition. FormatMessage finds the message definition in a message table resource based
 * on a message identifier. FormatMessage copies the formatted message text to an output buffer,
 * processing any embedded insert sequences if requested.
 *
 * The FormatMessage function can be used to obtain error message strings for the system error codes
 * returned by GetLastError, as shown in the following sample code.
 *
 *     LPVOID lpMsgBuf;
 *     FormatMessage(
 *         FORMAT_MESSAGE_ALLOCATE_BUFFER |
 *         FORMAT_MESSAGE_FROM_SYSTEM |
 *         FORMAT_MESSAGE_IGNORE_INSERTS,
 *         NULL,
 *         GetLastError(),
 *         0, // Default language
 *         (LPTSTR) &lpMsgBuf,
 *         0,
 *         NULL
 *     );
 *     // Process any inserts in lpMsgBuf.
 *     // ...
 *     // Display the string.
 *     MessageBox( NULL, (LPCTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION );
 *     // Free the buffer.
 *     LocalFree( lpMsgBuf );
 *
 * Within the message text, several escape sequences are supported for dynamically formatting the
 * message. These escape sequences and their meanings are shown in the following list. All escape
 * sequences start with the percent character (%).
 *
 * - %0: Terminates a message text line without a trailing newline character. This escape sequence
 * can be used to build up long lines or to terminate the message itself without a trailing newline
 * character. It is useful for prompt messages.
 *
 * - %n!printf format string!: Identifies an insert. The value of n can be in the range 1 through
 * 99. The printf format string (which must be bracketed by exclamation marks) is optional and
 * defaults to !s! if not specified. The printf format string can contain the * specifier for either
 * the precision or the width component. If * is specified for one component, the FormatMessage
 * function uses insert %n+1; it uses %n+2 if * is specified for both components. Floating-point
 * printf format specifiers-e, E, f, and g-are not supported. The workaround is to to use the
 * sprintf function to format the floating-point number into a temporary buffer, then use that
 * buffer as the insert string.
 *
 * Any other nondigit character following a percent character is formatted in the output message
 * without the percent character. Following are some examples:
 *
 * Format string Resulting output %% A single percent sign in the formatted message text. %n A hard
 * line break when the format string occurs at the end of a line. This format string is useful when
 * FormatMessage is supplying regular line breaks so the message fits in a certain width. %space A
 * space in the formatted message text. This format string can be used to ensure the appropriate
 * number of trailing spaces in a message text line. %. A single period in the formatted message
 * text. This format string can be used to include a single period at the beginning of a line
 * without terminating the message text definition. %! A single exclamation point in the formatted
 * message text. This format string can be used to include an exclamation point immediately after an
 * insert without its being mistaken for the beginning of a printf format string.
 */
#define FormatMessage  FormatMessageA
#endif // !UNICODE

// @CESYSGEN ENDIF

#define FORMAT_MESSAGE_ALLOCATE_BUFFER 0x00000100
#define FORMAT_MESSAGE_IGNORE_INSERTS  0x00000200
#define FORMAT_MESSAGE_FROM_STRING     0x00000400
#define FORMAT_MESSAGE_FROM_HMODULE    0x00000800
#define FORMAT_MESSAGE_FROM_SYSTEM     0x00001000
#define FORMAT_MESSAGE_ARGUMENT_ARRAY  0x00002000
#define FORMAT_MESSAGE_MAX_WIDTH_MASK  0x000000FF

/**
 * This function closes an open object handle. A remote application interface (RAPI) version of this
 * function exists, named CeCloseHandle.
 *
 * @param hObject Handle to an open object.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * The CloseHandle function closes handles to the following objects:
 *
 * Communications device Mutex Database Process Event Socket File Thread
 *
 * CloseHandle invalidates the specified object handle, decrements the object's handle count, and
 * performs object retention checks. After the last handle to an object is closed, the object is
 * removed from the system.
 *
 * Closing a thread handle does not terminate the associated thread. To remove a thread object, you
 * must terminate the thread, then close all handles to the thread.
 *
 * Use CloseHandle to close handles returned by calls to the CreateFile function. Use FindClose to
 * close handles returned by calls to the FindFirstFile function.
 */
WINBASEAPI
BOOL
WINAPI
CloseHandle(
    HANDLE hObject
    );

/**
 * This function loads the specified resource into global memory.
 *
 * @param hModule Handle to the module whose executable file contains the resource. If hModule is
 *   NULL, the system loads the resource from the module that was used to create the current process.
 *   In Windows CE versions 1.0 and 1.01, setting this parameter to NULL is not supported.
 * @param hResInfo Handle to the resource to be loaded. This handle must be created by using the
 *   FindResource function.
 *
 * @return A handle to the data associated with the resource indicates success. NULL indicates
 *   failure. To get extended error information, call GetLastError.
 *
 * The return type of LoadResource is HGLOBAL for backward compatibility, not because the function
 * returns a handle to a global memory block.
 *
 * When you are finished using a bitmap, cursor, icon, or menu, you can release its associated
 * memory by calling one of the functions in the following table.
 *
 * Resource Release function Bitmap DeleteObject Cursor DestroyCursor Icon DestroyIcon Menu
 * DestroyMenu
 *
 * The system automatically deletes these resources when the process that loaded them terminates,
 * however, calling the appropriate function saves memory and decreases the size of the process's
 * working set.
 *
 * Accelerator tables are an exception. They remain in memory until the process terminates.
 */
WINBASEAPI
HGLOBAL
WINAPI
LoadResource(
    HMODULE hModule,
    HRSRC hResInfo
    );

/**
 * This function returns the size, in bytes, of the specified resource.
 *
 * @param hModule Handle to the module whose executable file contains the resource.
 * @param hResInfo Handle to the resource. This handle must be created by using the FindResource
 *   function.
 *
 * @return The number of bytes in the resource indicates success. Zero indicates failure. To get
 *   extended error information, call GetLastError.
 */
WINBASEAPI
DWORD
WINAPI
SizeofResource(
    HMODULE hModule,
    HRSRC hResInfo
    );

/**
 * This function determines the location of a resource with the specified type and name in the
 * specified module.
 *
 * @param hModule Handle to the module whose executable file contains the resource. In Windows CE,
 *   this can not be set to NULL.
 * @param lpName Pointer to the name of the resource. For more information, see the Remarks section.
 * @param lpType Pointer to the resource type. For more information, see the Remarks section. For
 *   standard resource types, this parameter can be one of the following values: Value Description
 *   RT_ACCELERATOR Accelerator table RT_BITMAP Bitmap resource RT_CURSOR Hardware-dependent cursor
 *   resource RT_DIALOG Dialog box RT_FONT Font resource RT_FONTDIR Font directory resource
 *   RT_GROUP_CURSOR Hardware-independent cursor resource RT_GROUP_ICON Hardware-independent icon
 *   resource RT_HTML HTML document RT_ICON Hardware-dependent icon resource RT_MENU Menu resource
 *   RT_MESSAGETABLE Message-table entry RT_RCDATA Application-defined resource (raw data) RT_STRING
 *   String-table entry RT_VERSION Version resource
 *
 * @return A handle to the specified resource's info block indicates success. To obtain a handle to
 *   the resource, pass this handle to the LoadResource function. NULL indicates failure. To get
 *   extended error information, call GetLastError.
 *
 * If the high-order word of the lpName or lpType parameter is zero, the low-order word specifies
 * the integer identifier of the name or type of the given resource. Otherwise, those parameters are
 * long pointers to null-terminated strings. If the first character of the string is a pound sign
 * (#), the remaining characters represent a decimal number that specifies the integer identifier of
 * the resource's name or type. For example, the string "#258" represents the integer identifier
 * 258.
 *
 * The lpName parameter does not support the resource ID zero-that is, FindResource(h, 0 ,t) will
 * not work as expected.
 *
 * An application should reduce the amount of memory required for the resources by referring to them
 * by integer identifier instead of by name.
 *
 * When you are finished using an accelerator table, bitmap, cursor, icon, or menu, you can release
 * its associated memory by calling one of the functions in the following table.
 *
 * Resource Release function Accelerator table DestroyAcceleratorTable Bitmap DeleteObject Cursor
 * DestroyCursor Icon DestroyIcon Menu DestroyMenu
 *
 * The system automatically deletes these resources when the process that created them terminates,
 * however, calling the appropriate function saves memory and decreases the size of the process's
 * working set.
 *
 * An application can use FindResource to find any type of resource, but this function should be
 * used only if the application must access the binary resource data when making subsequent calls to
 * LoadLibrary.
 *
 * To use a resource immediately, an application should use one of the following resource-specific
 * functions to find and load the resources in one call:
 *
 * Function Description FormatMessage Loads and formats a message-table entry. LoadAccelerators
 * Loads an accelerator table. LoadBitmap Loads a bitmap resource. LoadCursor Loads a cursor
 * resource. LoadIcon Loads an icon resource. LoadMenu Loads a menu resource. LoadString Loads a
 * string-table entry.
 *
 * For example, an application can use the LoadIcon function to load an icon for display on the
 * screen. However, the application should use FindResource and LoadResource if it is loading the
 * icon to copy its data to another application.
 *
 * String resources are stored in sections of up to 16 strings per section. The strings in each
 * section are stored as a sequence of counted (not null-terminated) Unicode strings. The LoadString
 * function will extract the string resource from its corresponding section.
 */
WINBASEAPI
HRSRC
WINAPI
FindResourceA(
    HMODULE hModule,
    LPCSTR lpName,
    LPCSTR lpType
    );

/**
 * This function determines the location of a resource with the specified type and name in the
 * specified module.
 *
 * @param hModule Handle to the module whose executable file contains the resource. In Windows CE,
 *   this can not be set to NULL.
 * @param lpName Pointer to the name of the resource. For more information, see the Remarks section.
 * @param lpType Pointer to the resource type. For more information, see the Remarks section. For
 *   standard resource types, this parameter can be one of the following values: Value Description
 *   RT_ACCELERATOR Accelerator table RT_BITMAP Bitmap resource RT_CURSOR Hardware-dependent cursor
 *   resource RT_DIALOG Dialog box RT_FONT Font resource RT_FONTDIR Font directory resource
 *   RT_GROUP_CURSOR Hardware-independent cursor resource RT_GROUP_ICON Hardware-independent icon
 *   resource RT_HTML HTML document RT_ICON Hardware-dependent icon resource RT_MENU Menu resource
 *   RT_MESSAGETABLE Message-table entry RT_RCDATA Application-defined resource (raw data) RT_STRING
 *   String-table entry RT_VERSION Version resource
 *
 * @return A handle to the specified resource's info block indicates success. To obtain a handle to
 *   the resource, pass this handle to the LoadResource function. NULL indicates failure. To get
 *   extended error information, call GetLastError.
 *
 * If the high-order word of the lpName or lpType parameter is zero, the low-order word specifies
 * the integer identifier of the name or type of the given resource. Otherwise, those parameters are
 * long pointers to null-terminated strings. If the first character of the string is a pound sign
 * (#), the remaining characters represent a decimal number that specifies the integer identifier of
 * the resource's name or type. For example, the string "#258" represents the integer identifier
 * 258.
 *
 * The lpName parameter does not support the resource ID zero-that is, FindResource(h, 0 ,t) will
 * not work as expected.
 *
 * An application should reduce the amount of memory required for the resources by referring to them
 * by integer identifier instead of by name.
 *
 * When you are finished using an accelerator table, bitmap, cursor, icon, or menu, you can release
 * its associated memory by calling one of the functions in the following table.
 *
 * Resource Release function Accelerator table DestroyAcceleratorTable Bitmap DeleteObject Cursor
 * DestroyCursor Icon DestroyIcon Menu DestroyMenu
 *
 * The system automatically deletes these resources when the process that created them terminates,
 * however, calling the appropriate function saves memory and decreases the size of the process's
 * working set.
 *
 * An application can use FindResource to find any type of resource, but this function should be
 * used only if the application must access the binary resource data when making subsequent calls to
 * LoadLibrary.
 *
 * To use a resource immediately, an application should use one of the following resource-specific
 * functions to find and load the resources in one call:
 *
 * Function Description FormatMessage Loads and formats a message-table entry. LoadAccelerators
 * Loads an accelerator table. LoadBitmap Loads a bitmap resource. LoadCursor Loads a cursor
 * resource. LoadIcon Loads an icon resource. LoadMenu Loads a menu resource. LoadString Loads a
 * string-table entry.
 *
 * For example, an application can use the LoadIcon function to load an icon for display on the
 * screen. However, the application should use FindResource and LoadResource if it is loading the
 * icon to copy its data to another application.
 *
 * String resources are stored in sections of up to 16 strings per section. The strings in each
 * section are stored as a sequence of counted (not null-terminated) Unicode strings. The LoadString
 * function will extract the string resource from its corresponding section.
 */
WINBASEAPI
HRSRC
WINAPI
FindResourceW(
    HMODULE hModule,
    LPCWSTR lpName,
    LPCWSTR lpType
    );

#ifdef UNICODE
/**
 * This function determines the location of a resource with the specified type and name in the
 * specified module.
 *
 * @param hModule Handle to the module whose executable file contains the resource. In Windows CE,
 *   this can not be set to NULL.
 * @param lpName Pointer to the name of the resource. For more information, see the Remarks section.
 * @param lpType Pointer to the resource type. For more information, see the Remarks section. For
 *   standard resource types, this parameter can be one of the following values: Value Description
 *   RT_ACCELERATOR Accelerator table RT_BITMAP Bitmap resource RT_CURSOR Hardware-dependent cursor
 *   resource RT_DIALOG Dialog box RT_FONT Font resource RT_FONTDIR Font directory resource
 *   RT_GROUP_CURSOR Hardware-independent cursor resource RT_GROUP_ICON Hardware-independent icon
 *   resource RT_HTML HTML document RT_ICON Hardware-dependent icon resource RT_MENU Menu resource
 *   RT_MESSAGETABLE Message-table entry RT_RCDATA Application-defined resource (raw data) RT_STRING
 *   String-table entry RT_VERSION Version resource
 *
 * @return A handle to the specified resource's info block indicates success. To obtain a handle to
 *   the resource, pass this handle to the LoadResource function. NULL indicates failure. To get
 *   extended error information, call GetLastError.
 *
 * If the high-order word of the lpName or lpType parameter is zero, the low-order word specifies
 * the integer identifier of the name or type of the given resource. Otherwise, those parameters are
 * long pointers to null-terminated strings. If the first character of the string is a pound sign
 * (#), the remaining characters represent a decimal number that specifies the integer identifier of
 * the resource's name or type. For example, the string "#258" represents the integer identifier
 * 258.
 *
 * The lpName parameter does not support the resource ID zero-that is, FindResource(h, 0 ,t) will
 * not work as expected.
 *
 * An application should reduce the amount of memory required for the resources by referring to them
 * by integer identifier instead of by name.
 *
 * When you are finished using an accelerator table, bitmap, cursor, icon, or menu, you can release
 * its associated memory by calling one of the functions in the following table.
 *
 * Resource Release function Accelerator table DestroyAcceleratorTable Bitmap DeleteObject Cursor
 * DestroyCursor Icon DestroyIcon Menu DestroyMenu
 *
 * The system automatically deletes these resources when the process that created them terminates,
 * however, calling the appropriate function saves memory and decreases the size of the process's
 * working set.
 *
 * An application can use FindResource to find any type of resource, but this function should be
 * used only if the application must access the binary resource data when making subsequent calls to
 * LoadLibrary.
 *
 * To use a resource immediately, an application should use one of the following resource-specific
 * functions to find and load the resources in one call:
 *
 * Function Description FormatMessage Loads and formats a message-table entry. LoadAccelerators
 * Loads an accelerator table. LoadBitmap Loads a bitmap resource. LoadCursor Loads a cursor
 * resource. LoadIcon Loads an icon resource. LoadMenu Loads a menu resource. LoadString Loads a
 * string-table entry.
 *
 * For example, an application can use the LoadIcon function to load an icon for display on the
 * screen. However, the application should use FindResource and LoadResource if it is loading the
 * icon to copy its data to another application.
 *
 * String resources are stored in sections of up to 16 strings per section. The strings in each
 * section are stored as a sequence of counted (not null-terminated) Unicode strings. The LoadString
 * function will extract the string resource from its corresponding section.
 */
#define FindResource  FindResourceW
#else
/**
 * This function determines the location of a resource with the specified type and name in the
 * specified module.
 *
 * @param hModule Handle to the module whose executable file contains the resource. In Windows CE,
 *   this can not be set to NULL.
 * @param lpName Pointer to the name of the resource. For more information, see the Remarks section.
 * @param lpType Pointer to the resource type. For more information, see the Remarks section. For
 *   standard resource types, this parameter can be one of the following values: Value Description
 *   RT_ACCELERATOR Accelerator table RT_BITMAP Bitmap resource RT_CURSOR Hardware-dependent cursor
 *   resource RT_DIALOG Dialog box RT_FONT Font resource RT_FONTDIR Font directory resource
 *   RT_GROUP_CURSOR Hardware-independent cursor resource RT_GROUP_ICON Hardware-independent icon
 *   resource RT_HTML HTML document RT_ICON Hardware-dependent icon resource RT_MENU Menu resource
 *   RT_MESSAGETABLE Message-table entry RT_RCDATA Application-defined resource (raw data) RT_STRING
 *   String-table entry RT_VERSION Version resource
 *
 * @return A handle to the specified resource's info block indicates success. To obtain a handle to
 *   the resource, pass this handle to the LoadResource function. NULL indicates failure. To get
 *   extended error information, call GetLastError.
 *
 * If the high-order word of the lpName or lpType parameter is zero, the low-order word specifies
 * the integer identifier of the name or type of the given resource. Otherwise, those parameters are
 * long pointers to null-terminated strings. If the first character of the string is a pound sign
 * (#), the remaining characters represent a decimal number that specifies the integer identifier of
 * the resource's name or type. For example, the string "#258" represents the integer identifier
 * 258.
 *
 * The lpName parameter does not support the resource ID zero-that is, FindResource(h, 0 ,t) will
 * not work as expected.
 *
 * An application should reduce the amount of memory required for the resources by referring to them
 * by integer identifier instead of by name.
 *
 * When you are finished using an accelerator table, bitmap, cursor, icon, or menu, you can release
 * its associated memory by calling one of the functions in the following table.
 *
 * Resource Release function Accelerator table DestroyAcceleratorTable Bitmap DeleteObject Cursor
 * DestroyCursor Icon DestroyIcon Menu DestroyMenu
 *
 * The system automatically deletes these resources when the process that created them terminates,
 * however, calling the appropriate function saves memory and decreases the size of the process's
 * working set.
 *
 * An application can use FindResource to find any type of resource, but this function should be
 * used only if the application must access the binary resource data when making subsequent calls to
 * LoadLibrary.
 *
 * To use a resource immediately, an application should use one of the following resource-specific
 * functions to find and load the resources in one call:
 *
 * Function Description FormatMessage Loads and formats a message-table entry. LoadAccelerators
 * Loads an accelerator table. LoadBitmap Loads a bitmap resource. LoadCursor Loads a cursor
 * resource. LoadIcon Loads an icon resource. LoadMenu Loads a menu resource. LoadString Loads a
 * string-table entry.
 *
 * For example, an application can use the LoadIcon function to load an icon for display on the
 * screen. However, the application should use FindResource and LoadResource if it is loading the
 * icon to copy its data to another application.
 *
 * String resources are stored in sections of up to 16 strings per section. The strings in each
 * section are stored as a sequence of counted (not null-terminated) Unicode strings. The LoadString
 * function will extract the string resource from its corresponding section.
 */
#define FindResource  FindResourceA
#endif  // !UNICODE

/**
 * This function terminates the specified process and all of its threads.
 *
 * @param hProcess Handle to the process to terminate.
 * @param uExitCode Specifies the exit code for the process and for all threads terminated as a
 *   result of this call. Use the GetExitCodeProcess function to retrieve the process's exit value.
 *   Use the GetExitCodeThread function to retrieve a thread's exit value.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * The TerminateProcess function is used to unconditionally cause a process to exit. Use it only in
 * extreme circumstances. The state of global data maintained by dynamic-link libraries (DLLs) may
 * be compromised if TerminateProcess.
 *
 * TerminateProcess causes all threads within a process to terminate, and causes a process to exit,
 * but DLLs attached to the process are not notified that the process is terminating.
 *
 * Terminating a process causes the following:
 *
 * All of the object handles opened by the process are closed.
 *
 * All of the threads in the process terminate their execution.
 *
 * The state of the process object becomes signaled, satisfying any threads that had been waiting
 * for the process to terminate.
 *
 * The states of all threads of the process become signaled, satisfying any threads that had been
 * waiting for the threads to terminate.
 *
 * The termination status of the process changes from STILL_ACTIVE to the exit value of the process.
 *
 * Terminating a process does not cause child processes to be terminated.
 *
 * Terminating a process does not necessarily remove the process object from the system. A process
 * object is deleted when the last handle to the process is closed.
 *
 * For Windows CE version 1.0, the uExitCode parameter is ignored because process exit codes are not
 * supported.
 */
WINBASEAPI
BOOL
WINAPI
TerminateProcess(
    HANDLE hProcess,
    DWORD uExitCode
    );

/**
 * This function flushes the instruction cache for the specified process.
 *
 * @param hProcess Handle to the process that has an instruction cache to flush.
 * @param lpBaseAddress Unsupported; set to NULL.
 * @param dwSize Unsupported; set to NULL.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 */
BOOL
WINAPI
FlushInstructionCache(
    HANDLE hProcess,
    LPCVOID lpBaseAddress,
    DWORD dwSize
    );

/**
 * This function reads memory in a specified process. The entire area to be read must be accessible,
 * or the operation fails.
 *
 * @param hProcess Handle to the process whose memory is being read. In Windows CE, any call to
 *   OpenProcess will return a process handle with the proper access rights.
 * @param lpBaseAddress Pointer to the base address in the specified process to be read. Before any
 *   data transfer occurs, the system verifies that all data in the base address and memory of the
 *   specified size is accessible for read access. If this is the case, the function proceeds;
 *   otherwise, the function fails.
 * @param lpBuffer Pointer to a buffer that receives the contents from the address space of the
 *   specified process.
 * @param nSize Specifies the requested number of bytes to read from the specified process.
 * @param lpNumberOfBytesRead Pointer to the actual number of bytes transferred into the specified
 *   buffer. If lpNumberOfBytesRead is NULL, the parameter is ignored.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError. The function fails if the requested read operation crosses into an area of the
 *   process that is inaccessible.
 *
 * ReadProcessMemory copies the data in the specified address range from the address space of the
 * specified process into the specified buffer of the current process. The process whose address
 * space is read is typically, but not necessarily, being debugged.
 *
 * The entire area to be read must be accessible. If it is not, the function fails as noted
 * previously.
 */
BOOL
WINAPI
ReadProcessMemory(
    HANDLE hProcess,
    LPCVOID lpBaseAddress,
    LPVOID lpBuffer,
    DWORD nSize,
    LPDWORD lpNumberOfBytesRead
    );

/**
 * This function writes memory in a specified process. The entire area to be written to must be
 * accessible, or the operation fails.
 *
 * @param hProcess Handle returned from the OpenProcess function that provided full access to the
 *   process.
 * @param lpBaseAddress Pointer to the base address in the specified process to be written to.
 *   Before any data transfer occurs, the system verifies that all data in the base address and memory
 *   of the specified size is accessible for write access. If this is the case, the function proceeds;
 *   otherwise, the function fails.
 * @param lpBuffer Pointer to the buffer that supplies data to be written into the address space of
 *   the specified process.
 * @param nSize Specifies the requested number of bytes to write into the specified process.
 * @param lpNumberOfBytesWritten Pointer to the actual number of bytes transferred into the
 *   specified process. This parameter is optional. If lpNumberOfBytesWritten is NULL, the parameter
 *   is ignored.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError. The function fails if the requested write operation crosses into an area of
 *   the process that is inaccessible.
 *
 * WriteProcessMemory copies the data from the specified buffer in the current process to the
 * address range of the specified process. The process whose address space is being written to is
 * typically, but not necessarily, being debugged.
 *
 * The entire area to be written to must be accessible. If it is not, the function fails as noted
 * previously.
 */
BOOL
WINAPI
WriteProcessMemory(
    HANDLE hProcess,
    LPVOID lpBaseAddress,
    LPVOID lpBuffer,
    DWORD nSize,
    LPDWORD lpNumberOfBytesWritten
    );

/**
 * This function returns a handle to an existing process object.
 *
 * @param dwDesiredAccess Not supported; set to zero.
 * @param bInheritHandle Not supported; set to FALSE.
 * @param dwProcessId Specifies the process identifier of the process to open.
 *
 * @return An open handle to the specified process indicates success. NULL indicates failure. To get
 *   extended error information, call GetLastError.
 *
 * The handle returned by the OpenProcess function can be used in any function that requires a
 * handle to a process, such as the wait functions, provided the appropriate access rights were
 * requested.
 *
 * When you are finished with the handle, be sure to close it using the CloseHandle function.
 */
HANDLE
WINAPI
OpenProcess(
	DWORD fdwAccess,
	BOOL fInherit,
	DWORD IDProcess
	);

/**
 * This function retrieves the context of the specified thread.
 *
 * @param hThread Handle to the thread whose context is to be retrieved.
 * @param lpContext Pointer to the CONTEXT structure that receives the appropriate context of the
 *   specified thread. The value of the ContextFlags member of this structure specifies which portions
 *   of a thread's context are retrieved. The CONTEXT structure is highly computer specific.
 *   Currently, there are CONTEXT structures defined for Intel, MIPS, Alpha, ARM, SHx, and PowerPC
 *   processors. Refer to the header file WINNT.H for definitions of these structures.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * The GetThreadContext function is used to retrieve the context of the specified thread. The
 * function allows a selective context to be retrieved based on the value of the ContextFlags member
 * of the CONTEXT structure. The thread handle identified by the hThread parameter is typically
 * being debugged, but the function can also operate when it is not being debugged.
 *
 * You cannot get a valid context for a running thread. Use the SuspendThread function to suspend
 * the thread before calling GetThreadContext.
 */
WINBASEAPI
BOOL
WINAPI
GetThreadContext(
    HANDLE hThread,
    LPCONTEXT lpContext
    );

/**
 * This function sets the context in the specified thread.
 *
 * @param hThread Handle to the thread whose context is to be set.
 * @param lpContext Pointer to the CONTEXT structure that contains the context to be set in the
 *   specified thread. The value of the ContextFlags member of this structure specifies which portions
 *   of a thread's context to set. Some values in the CONTEXT structure that cannot be specified are
 *   silently set to the correct value. This includes bits in the CPU status register that specify the
 *   privileged processor mode, global enabling bits in the debugging register, and other states that
 *   must be controlled by the operating system.
 *
 * @return Nonzero indicates that the context was set. Zero indicates failure. To get extended error
 *   information, call GetLastError.
 *
 * The function allows the selective context to be set based on the value of the ContextFlags member
 * of the context structure. The thread handle identified by the hThread parameter is typically
 * being debugged, but the function can also operate even when it is not being debugged.
 *
 * Do not try to set the context for a running thread; the results are unpredictable. Use the
 * SuspendThread function to suspend the thread before calling SetThreadContext.
 */
WINBASEAPI
BOOL
WINAPI
SetThreadContext(
    HANDLE hThread,
    CONST CONTEXT *lpContext
    );

/**
 * This function suspends the specified thread.
 *
 * @param hThread Handle to the thread.
 *
 * @return The thread's previous suspend count indicates success. 0xFFFFFFFF indicates failure. To
 *   get extended error information, call GetLastError.
 *
 * If the function succeeds, execution of the specified thread is suspended and the thread's suspend
 * count is incremented.
 *
 * Suspending a thread causes the thread to stop executing user-mode (application) code.
 *
 * If the thread is making a kernel call, SuspendThread fails. An application may need to repeat the
 * SuspendThread several times for it to succeed.
 *
 * Each thread has a suspend count (with a maximum value of MAXIMUM_SUSPEND_COUNT). If the suspend
 * count is greater than zero, the thread is suspended; otherwise, the thread is not suspended and
 * is eligible for execution. Calling SuspendThread causes the target thread's suspend count to be
 * incremented. Attempting to increment past the maximum suspend count causes an error without
 * incrementing the count.
 *
 * The ResumeThread function decrements the suspend count of a suspended thread.
 */
WINBASEAPI
DWORD
WINAPI
SuspendThread(
    HANDLE hThread
    );
/**
 * This function decrements a thread's suspend count. When the suspend count is decremented to zero,
 * the execution of the thread is resumed.
 *
 * @param hThread Specifies a handle for the thread to be restarted.
 *
 * @return The thread's previous suspend count indicates success. 0xFFFFFFFF indicates failure. To
 *   get extended error information, call GetLastError.
 *
 * The ResumeThread function checks the suspend count of the subject thread. If the suspend count is
 * 0, the thread is not currently suspended. Otherwise, the subject thread's suspend count is
 * decremented. If the resulting value is 0, then the execution of the subject thread is resumed.
 *
 * If the return value is 0, the specified thread was not suspended. If the return value is 1, the
 * specified thread was suspended but was restarted. If the return value is greater than 1, the
 * specified thread is still suspended.
 *
 * Note that while reporting debug events, all threads within the reporting process are frozen.
 * Debuggers are expected to use the SuspendThread and ResumeThread functions to limit the set of
 * threads that can execute within a process. By suspending all threads in a process except for the
 * one reporting a debug event, it is possible to "single step" a single thread. The other threads
 * are not released by a continue operation if they are suspended.
 */
WINBASEAPI
DWORD
WINAPI
ResumeThread(
    HANDLE hThread
    );

/**
 * This function returns the priority value for the specified thread.
 *
 * @param hThread Handle to the thread.
 *
 * @return The thread's priority level indicates success. THREAD_PRIORITY_ERROR_RETURN indicates
 *   failure. To get extended error information, call GetLastError. The thread's priority level is one
 *   of the values described in the following list. - THREAD_PRIORITY_TIME_CRITICAL: Indicates 3
 *   points above normal priority. - THREAD_PRIORITY_HIGHEST Indicates 2 points above normal priority.
 *   - THREAD_PRIORITY_ABOVE_NORMAL: Indicates 1 point above normal priority. THREAD_PRIORITY_NORMAL
 *   Indicates normal priority. - THREAD_PRIORITY_BELOW_NORMAL: Indicates 1 point below normal
 *   priority. THREAD_PRIORITY_LOWEST Indicates 2 points below normal priority.
 *   THREAD_PRIORITY_ABOVE_IDLE Indicates 3 points below normal priority. - THREAD_PRIORITY_IDLE:
 *   Indicates 4 points below normal priority.
 *
 * Windows CE does not support priority classes. The order in which threads are scheduled is
 * determined only by their thread priorities.
 *
 * When manipulating priorities, ensure that a high-priority thread does not consume all of the
 * available CPU time. A thread with a priority level of THREAD_PRIORITY_TIME_CRITICAL will execute
 * until it explicitly yields processing to other threads.
 *
 * If a THREAD_PRIORITY_TIME_CRITICAL priority level running no other THREAD_PRIORITY_TIME_CRITICAL
 * priority level thread will run until the first thread yields. The system will still be able to
 * service IRQs and ISRs but will not be able to schedule any ISTs.
 *
 * Threads are scheduled in a round-robin fashion at each priority level, and only when there are no
 * executable threads at a higher level will scheduling of threads at a lower level take place
 */
WINBASEAPI
int
WINAPI
GetThreadPriority(
    HANDLE hThread
    );


/**
 * This function sets the priority value for the specified thread.
 *
 * @param hThread Handle to the thread whose priority value is to be set.
 * @param nPriority Specifies the priority value for the thread. This parameter can be one of the
 *   following values: Value Description THREAD_PRIORITY_TIME_CRITICAL Indicates 3 points above normal
 *   priority. THREAD_PRIORITY_HIGHEST Indicates 2 points above normal priority.
 *   THREAD_PRIORITY_ABOVE_NORMAL Indicates 1 point above normal priority. THREAD_PRIORITY_NORMAL
 *   Indicates normal priority. THREAD_PRIORITY_BELOW_NORMAL Indicates 1 point below normal priority.
 *   THREAD_PRIORITY_LOWEST Indicates 2 points below normal priority. THREAD_PRIORITY_ABOVE_IDLE
 *   Indicates 3 points below normal priority. THREAD_PRIORITY_IDLE Indicates 4 points below normal
 *   priority.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * Windows CE does not support priority classes. The order in which threads are scheduled is
 * determined only by their thread priorities.
 *
 * Threads are scheduled in a round-robin fashion at each priority level, and only when there are no
 * executable threads at a higher level does scheduling of threads at a lower level take place.
 *
 * The SetThreadPriority function enables setting the base priority level of a thread without
 * consideration of priority classes.
 *
 * All threads initially start at THREAD_PRIORITY_NORMAL. Use the GetThreadPriority function to get
 * the priority value of a thread.
 *
 * Use thread priority values to differentiate the relative priorities of the tasks of a process.
 * For example, a thread that handles input for a window could have a higher priority level than a
 * thread that performs intensive calculations for the CPU.
 *
 * When manipulating priorities, ensure that a high-priority thread does not consume all of the
 * available CPU time. A thread with a priority level of THREAD_PRIORITY_TIME_CRITICAL will execute
 * until it explicitly yields processing to other threads. Processing of these threads is not
 * yielded to other threads with the THREAD_PRIORITY_TIME_CRITICAL priority level. Such a thread can
 * interfere with the normal operation of the operating system if the thread does not explicitly
 * yield processing quickly.
 */
WINBASEAPI
BOOL
WINAPI
SetThreadPriority(
    HANDLE hThread,
    int nPriority
    );

/**
 * This function sets the last-error code for the calling thread.
 *
 * @param dwErrCode Specifies the last-error code for the thread.
 *
 * @return None.
 *
 * Error codes are 32-bit values (bit 31 is the most significant bit). Bit 29 is reserved for
 * application-defined error codes; no system error code has this bit set. If you are defining an
 * error code for your application, set this bit to indicate that the error code has been defined by
 * your application and to ensure that your error code does not conflict with any system-defined
 * error codes.
 *
 * This function is intended primarily for dynamic-link libraries (DLLs). Calling this function
 * after an error occurs lets the DLL emulate the behavior of a Win32 function.
 *
 * Most Win32 functions call SetLastError when they fail. Function failure is typically indicated by
 * a return value error code such as FALSE, NULL, 0xFFFFFFFF, or -1. Some functions call
 * SetLastError under conditions of success; those cases are noted in each function's reference
 * page.
 *
 * Applications can retrieve the value saved by this function by using the GetLastError function.
 * The use of GetLastError is optional; an application can call it to find out the specific reason
 * for a function failure.
 *
 * The last-error code is kept in thread local storage so that multiple threads do not overwrite
 * each other's values.
 */
WINBASEAPI
VOID
WINAPI
SetLastError(
    DWORD dwErrCode
    );

// @CESYSGEN IF FILESYS_FSMAIN

/**
 * This function obtains information about the amount of space available on a disk volume: the total
 * amount of space, the total amount of free space, and the total amount of free space available to
 * the user associated with the calling thread.
 *
 * @param lpDirectoryName [in] Pointer to a null-terminated string that specifies a directory on the
 *   disk of interest. This string can be a UNC name. If this parameter is a UNC name, you must follow
 *   it with an additional backslash. For example, you would specify \\MyServer\MyShare as
 *   \\MyServer\MyShare\. If lpDirectoryName is NULL, the GetDiskFreeSpaceEx function obtains
 *   information about the object store. Note that lpDirectoryName does not have to specify the root
 *   directory on a disk. The function accepts any directory on the disk.
 * @param lpFreeBytesAvailableToCaller [out] Pointer to a variable to receive the total number of
 *   free bytes on the disk that are available to the user associated with the calling thread.
 * @param lpTotalNumberOfBytes [out] Pointer to a variable to receive the total number of bytes on
 *   the disk that are available to the user associated with the calling thread.
 * @param lpTotalNumberOfFreeBytes [out] Pointer to a variable to receive the total number of free
 *   bytes on the disk. This parameter can be NULL.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * Note that the values obtained by this function are of type ULARGE_INTEGER. Be careful not to
 * truncate these values to 32 bits.
 */
BOOL GetDiskFreeSpaceExA(LPCSTR lpDirectoryName, PULARGE_INTEGER lpFreeBytesAvailableToCaller,
    PULARGE_INTEGER lpTotalNumberOfBytes, PULARGE_INTEGER lpTotalNumberOfFreeBytes);

/**
 * This function obtains information about the amount of space available on a disk volume: the total
 * amount of space, the total amount of free space, and the total amount of free space available to
 * the user associated with the calling thread.
 *
 * @param lpDirectoryName [in] Pointer to a null-terminated string that specifies a directory on the
 *   disk of interest. This string can be a UNC name. If this parameter is a UNC name, you must follow
 *   it with an additional backslash. For example, you would specify \\MyServer\MyShare as
 *   \\MyServer\MyShare\. If lpDirectoryName is NULL, the GetDiskFreeSpaceEx function obtains
 *   information about the object store. Note that lpDirectoryName does not have to specify the root
 *   directory on a disk. The function accepts any directory on the disk.
 * @param lpFreeBytesAvailableToCaller [out] Pointer to a variable to receive the total number of
 *   free bytes on the disk that are available to the user associated with the calling thread.
 * @param lpTotalNumberOfBytes [out] Pointer to a variable to receive the total number of bytes on
 *   the disk that are available to the user associated with the calling thread.
 * @param lpTotalNumberOfFreeBytes [out] Pointer to a variable to receive the total number of free
 *   bytes on the disk. This parameter can be NULL.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * Note that the values obtained by this function are of type ULARGE_INTEGER. Be careful not to
 * truncate these values to 32 bits.
 */
BOOL GetDiskFreeSpaceExW(LPCWSTR lpDirectoryName, PULARGE_INTEGER lpFreeBytesAvailableToCaller,
    PULARGE_INTEGER lpTotalNumberOfBytes, PULARGE_INTEGER lpTotalNumberOfFreeBytes);

#ifdef UNICODE
/**
 * This function obtains information about the amount of space available on a disk volume: the total
 * amount of space, the total amount of free space, and the total amount of free space available to
 * the user associated with the calling thread.
 *
 * @param lpDirectoryName [in] Pointer to a null-terminated string that specifies a directory on the
 *   disk of interest. This string can be a UNC name. If this parameter is a UNC name, you must follow
 *   it with an additional backslash. For example, you would specify \\MyServer\MyShare as
 *   \\MyServer\MyShare\. If lpDirectoryName is NULL, the GetDiskFreeSpaceEx function obtains
 *   information about the object store. Note that lpDirectoryName does not have to specify the root
 *   directory on a disk. The function accepts any directory on the disk.
 * @param lpFreeBytesAvailableToCaller [out] Pointer to a variable to receive the total number of
 *   free bytes on the disk that are available to the user associated with the calling thread.
 * @param lpTotalNumberOfBytes [out] Pointer to a variable to receive the total number of bytes on
 *   the disk that are available to the user associated with the calling thread.
 * @param lpTotalNumberOfFreeBytes [out] Pointer to a variable to receive the total number of free
 *   bytes on the disk. This parameter can be NULL.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * Note that the values obtained by this function are of type ULARGE_INTEGER. Be careful not to
 * truncate these values to 32 bits.
 */
#define GetDiskFreeSpaceEx  GetDiskFreeSpaceExW
#else
/**
 * This function obtains information about the amount of space available on a disk volume: the total
 * amount of space, the total amount of free space, and the total amount of free space available to
 * the user associated with the calling thread.
 *
 * @param lpDirectoryName [in] Pointer to a null-terminated string that specifies a directory on the
 *   disk of interest. This string can be a UNC name. If this parameter is a UNC name, you must follow
 *   it with an additional backslash. For example, you would specify \\MyServer\MyShare as
 *   \\MyServer\MyShare\. If lpDirectoryName is NULL, the GetDiskFreeSpaceEx function obtains
 *   information about the object store. Note that lpDirectoryName does not have to specify the root
 *   directory on a disk. The function accepts any directory on the disk.
 * @param lpFreeBytesAvailableToCaller [out] Pointer to a variable to receive the total number of
 *   free bytes on the disk that are available to the user associated with the calling thread.
 * @param lpTotalNumberOfBytes [out] Pointer to a variable to receive the total number of bytes on
 *   the disk that are available to the user associated with the calling thread.
 * @param lpTotalNumberOfFreeBytes [out] Pointer to a variable to receive the total number of free
 *   bytes on the disk. This parameter can be NULL.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * Note that the values obtained by this function are of type ULARGE_INTEGER. Be careful not to
 * truncate these values to 32 bits.
 */
#define GetDiskFreeSpaceEx  GetDiskFreeSpaceExA
#endif // !UNICODE

/**
 * This function creates, opens, or truncates a file, communications resource, disk device, or
 * console. It returns a handle that can be used to access the object. It can also open and return a
 * handle to a directory.
 *
 * @param lpFileName [in] Pointer to a null-terminated string that specifies the name of the object
 *   (file, communications resource, disk device, console, or directory) to create or open. If
 *   *lpFileName is a path, there is a default string size limit of MAX_PATH characters. This limit is
 *   related to how the CreateFile function parses paths. When lpFileName points to a communications
 *   resource to open, you must include a colon after the name. For example, specify "COM1:" to open
 *   that port.
 * @param dwDesiredAccess [in] Specifies the type of access to the object. An application can obtain
 *   read access, write access, read-write access, or device query access. This parameter can be any
 *   combination of the following values. Value Description 0 Specifies device query access to the
 *   object. An application can query device attributes without accessing the device. GENERIC_READ
 *   Specifies read access to the object. Data can be read from the file and the file pointer can be
 *   moved. Combine with GENERIC_WRITE for read-write access. GENERIC_WRITE Specifies write access to
 *   the object. Data can be written to the file and the file pointer can be moved. Combine with
 *   GENERIC_READ for read-write access.
 * @param dwShareMode [in] Specifies how the object can be shared. If dwShareMode is 0, the object
 *   cannot be shared. Subsequent open operations on the object will fail, until the handle is closed.
 *   To share the object, use a combination of one or more of the following values: Value Description
 *   FILE_SHARE_READ Subsequent open operations on the object will succeed only if read access is
 *   requested. FILE_SHARE_WRITE Subsequent open operations on the object will succeed only if write
 *   access is requested.
 * @param lpSecurityAttributes [in] Ignored; set to NULL.
 * @param dwCreationDisposition [in] Specifies which action to take on files that exist, and which
 *   action to take when files do not exist. For more information about this parameter, see the
 *   Remarks section. This parameter must be one of the following values: Value Description CREATE_NEW
 *   Creates a new file. The function fails if the specified file already exists. CREATE_ALWAYS
 *   Creates a new file. If the file exists, the function overwrites the file and clears the existing
 *   attributes. OPEN_EXISTING Opens the file. The function fails if the file does not exist. See the
 *   Remarks section for a discussion of why you should use the OPEN_EXISTING flag if you are using
 *   the CreateFile function for devices, including the console. OPEN_ALWAYS Opens the file, if it
 *   exists. If the file does not exist, the function creates the file as if dwCreationDisposition
 *   were CREATE_NEW. TRUNCATE_EXISTING Opens the file. Once opened, the file is truncated so that its
 *   size is zero bytes. The calling process must open the file with at least GENERIC_WRITE access.
 *   The function fails if the file does not exist.
 * @param dwFlagsAndAttributes [in] Specifies the file attributes and flags for the file. Any
 *   combination of the following attributes is acceptable for the dwFlagsAndAttributes parameter,
 *   except all other file attributes override FILE_ATTRIBUTE_NORMAL. Value Description
 *   FILE_ATTRIBUTE_ARCHIVE The file should be archived. Applications use this attribute to mark files
 *   for backup or removal. FILE_ATTRIBUTE_HIDDEN The file is hidden. It is not to be included in an
 *   ordinary directory listing. FILE_ATTRIBUTE_NORMAL The file has no other attributes set. This
 *   attribute is valid only if used alone. FILE_ATTRIBUTE_READONLY The file is read only.
 *   Applications can read the file but cannot write to it or delete it. FILE_ATTRIBUTE_SYSTEM The
 *   file is part of or is used exclusively by the operating system. FILE_ATTRIBUTE_TEMPORARY Not
 *   supported. Any combination of the following flags is acceptable for the dwFlagsAndAttributes
 *   parameter. Value Description FILE_FLAG_WRITE_THROUGH Instructs the system to write through any
 *   intermediate cache and go directly to disk. The system can still cache write operations, but
 *   cannot lazily flush them. FILE_FLAG_OVERLAPPED This flag is not supported; however, multiple
 *   reads/writes pending on a device at a time are allowed. FILE_FLAG_RANDOM_ACCESS Indicates that
 *   the file is accessed randomly. The system can use this as a hint to optimize file caching.
 *   FILE_FLAG_SEQUENTIAL_SCAN Indicates that the file is to be accessed sequentially from beginning
 *   to end. The system can use this as a hint to optimize file caching. If an application moves the
 *   file pointer for random access, optimum caching may not occur; however, correct operation is
 *   still guaranteed. Specifying this flag can increase performance for applications that read large
 *   files using sequential access. Performance gains can be even more noticeable for applications
 *   that read large files mostly sequentially, but occasionally skip over small ranges of bytes.
 * @param hTemplateFile [in] Ignored; as a result, CreateFile does not copy the extended attributes
 *   to the new file.
 *
 * @return An open handle to the specified file indicates success. If the specified file exists
 *   before the function call and dwCreationDisposition is CREATE_ALWAYS or OPEN_ALWAYS, a call to
 *   GetLastError returns ERROR_ALREADY_EXISTS, even though the function has succeeded. If the file
 *   does not exist before the call, GetLastError returns zero. INVALID_HANDLE_VALUE indicates
 *   failure. To get extended error information, call GetLastError.
 *
 * Use the CloseHandle function to close an object handle returned by CreateFile.
 *
 * As noted above, specifying zero for dwDesiredAccess allows an application to query device
 * attributes without actually accessing the device. This type of querying is useful, for example,
 * if an application wants to determine the size of a floppy disk drive and the formats it supports
 * without having a floppy in the drive.
 *
 * Files
 *
 * When creating a new file, the CreateFile function performs the following actions:
 *
 * Combines the file attributes and flags specified by dwFlagsAndAttributes with
 * FILE_ATTRIBUTE_ARCHIVE.
 *
 * Sets the file length to zero.
 *
 * When opening an existing file, CreateFile performs the following actions:
 *
 * Combines the file flags specified by dwFlagsAndAttributes with existing file attributes.
 * CreateFile ignores the file attributes specified by dwFlagsAndAttributes.
 *
 * Sets the file length according to the value of dwCreationDisposition.
 *
 * To store the maximum number of files on PC Card storage devices, limit file names to eight
 * uppercase characters and file extensions to three uppercase characters. Also, do not allow
 * non-OEM characters in file names. File names that do not conform to these limits require more
 * than one physical directory entry on a PC Card.
 *
 * Communications Resources
 *
 * The CreateFile function can create a handle to a communications resource. By setting the
 * dwCreationDisposition parameter to OPEN_EXISTING, read, write, or read-write access can be
 * specified.
 *
 * Directories
 *
 * An application cannot create a directory with CreateFile; it must call CreateDirectory to create
 * a directory.
 *
 * Some file systems, such as NTFS, support compression or encryption for individual files and
 * directories. On volumes formatted for such a file system, a new directory inherits the
 * compression and encryption attributes of its parent directory.
 */
WINBASEAPI
HANDLE
WINAPI
CreateFileA(
    LPCSTR lpFileName,
    DWORD dwDesiredAccess,
    DWORD dwShareMode,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    DWORD dwCreationDisposition,
    DWORD dwFlagsAndAttributes,
    HANDLE hTemplateFile
    );
    
/**
 * This function creates, opens, or truncates a file, communications resource, disk device, or
 * console. It returns a handle that can be used to access the object. It can also open and return a
 * handle to a directory.
 *
 * @param lpFileName [in] Pointer to a null-terminated string that specifies the name of the object
 *   (file, communications resource, disk device, console, or directory) to create or open. If
 *   *lpFileName is a path, there is a default string size limit of MAX_PATH characters. This limit is
 *   related to how the CreateFile function parses paths. When lpFileName points to a communications
 *   resource to open, you must include a colon after the name. For example, specify "COM1:" to open
 *   that port.
 * @param dwDesiredAccess [in] Specifies the type of access to the object. An application can obtain
 *   read access, write access, read-write access, or device query access. This parameter can be any
 *   combination of the following values. Value Description 0 Specifies device query access to the
 *   object. An application can query device attributes without accessing the device. GENERIC_READ
 *   Specifies read access to the object. Data can be read from the file and the file pointer can be
 *   moved. Combine with GENERIC_WRITE for read-write access. GENERIC_WRITE Specifies write access to
 *   the object. Data can be written to the file and the file pointer can be moved. Combine with
 *   GENERIC_READ for read-write access.
 * @param dwShareMode [in] Specifies how the object can be shared. If dwShareMode is 0, the object
 *   cannot be shared. Subsequent open operations on the object will fail, until the handle is closed.
 *   To share the object, use a combination of one or more of the following values: Value Description
 *   FILE_SHARE_READ Subsequent open operations on the object will succeed only if read access is
 *   requested. FILE_SHARE_WRITE Subsequent open operations on the object will succeed only if write
 *   access is requested.
 * @param lpSecurityAttributes [in] Ignored; set to NULL.
 * @param dwCreationDisposition [in] Specifies which action to take on files that exist, and which
 *   action to take when files do not exist. For more information about this parameter, see the
 *   Remarks section. This parameter must be one of the following values: Value Description CREATE_NEW
 *   Creates a new file. The function fails if the specified file already exists. CREATE_ALWAYS
 *   Creates a new file. If the file exists, the function overwrites the file and clears the existing
 *   attributes. OPEN_EXISTING Opens the file. The function fails if the file does not exist. See the
 *   Remarks section for a discussion of why you should use the OPEN_EXISTING flag if you are using
 *   the CreateFile function for devices, including the console. OPEN_ALWAYS Opens the file, if it
 *   exists. If the file does not exist, the function creates the file as if dwCreationDisposition
 *   were CREATE_NEW. TRUNCATE_EXISTING Opens the file. Once opened, the file is truncated so that its
 *   size is zero bytes. The calling process must open the file with at least GENERIC_WRITE access.
 *   The function fails if the file does not exist.
 * @param dwFlagsAndAttributes [in] Specifies the file attributes and flags for the file. Any
 *   combination of the following attributes is acceptable for the dwFlagsAndAttributes parameter,
 *   except all other file attributes override FILE_ATTRIBUTE_NORMAL. Value Description
 *   FILE_ATTRIBUTE_ARCHIVE The file should be archived. Applications use this attribute to mark files
 *   for backup or removal. FILE_ATTRIBUTE_HIDDEN The file is hidden. It is not to be included in an
 *   ordinary directory listing. FILE_ATTRIBUTE_NORMAL The file has no other attributes set. This
 *   attribute is valid only if used alone. FILE_ATTRIBUTE_READONLY The file is read only.
 *   Applications can read the file but cannot write to it or delete it. FILE_ATTRIBUTE_SYSTEM The
 *   file is part of or is used exclusively by the operating system. FILE_ATTRIBUTE_TEMPORARY Not
 *   supported. Any combination of the following flags is acceptable for the dwFlagsAndAttributes
 *   parameter. Value Description FILE_FLAG_WRITE_THROUGH Instructs the system to write through any
 *   intermediate cache and go directly to disk. The system can still cache write operations, but
 *   cannot lazily flush them. FILE_FLAG_OVERLAPPED This flag is not supported; however, multiple
 *   reads/writes pending on a device at a time are allowed. FILE_FLAG_RANDOM_ACCESS Indicates that
 *   the file is accessed randomly. The system can use this as a hint to optimize file caching.
 *   FILE_FLAG_SEQUENTIAL_SCAN Indicates that the file is to be accessed sequentially from beginning
 *   to end. The system can use this as a hint to optimize file caching. If an application moves the
 *   file pointer for random access, optimum caching may not occur; however, correct operation is
 *   still guaranteed. Specifying this flag can increase performance for applications that read large
 *   files using sequential access. Performance gains can be even more noticeable for applications
 *   that read large files mostly sequentially, but occasionally skip over small ranges of bytes.
 * @param hTemplateFile [in] Ignored; as a result, CreateFile does not copy the extended attributes
 *   to the new file.
 *
 * @return An open handle to the specified file indicates success. If the specified file exists
 *   before the function call and dwCreationDisposition is CREATE_ALWAYS or OPEN_ALWAYS, a call to
 *   GetLastError returns ERROR_ALREADY_EXISTS, even though the function has succeeded. If the file
 *   does not exist before the call, GetLastError returns zero. INVALID_HANDLE_VALUE indicates
 *   failure. To get extended error information, call GetLastError.
 *
 * Use the CloseHandle function to close an object handle returned by CreateFile.
 *
 * As noted above, specifying zero for dwDesiredAccess allows an application to query device
 * attributes without actually accessing the device. This type of querying is useful, for example,
 * if an application wants to determine the size of a floppy disk drive and the formats it supports
 * without having a floppy in the drive.
 *
 * Files
 *
 * When creating a new file, the CreateFile function performs the following actions:
 *
 * Combines the file attributes and flags specified by dwFlagsAndAttributes with
 * FILE_ATTRIBUTE_ARCHIVE.
 *
 * Sets the file length to zero.
 *
 * When opening an existing file, CreateFile performs the following actions:
 *
 * Combines the file flags specified by dwFlagsAndAttributes with existing file attributes.
 * CreateFile ignores the file attributes specified by dwFlagsAndAttributes.
 *
 * Sets the file length according to the value of dwCreationDisposition.
 *
 * To store the maximum number of files on PC Card storage devices, limit file names to eight
 * uppercase characters and file extensions to three uppercase characters. Also, do not allow
 * non-OEM characters in file names. File names that do not conform to these limits require more
 * than one physical directory entry on a PC Card.
 *
 * Communications Resources
 *
 * The CreateFile function can create a handle to a communications resource. By setting the
 * dwCreationDisposition parameter to OPEN_EXISTING, read, write, or read-write access can be
 * specified.
 *
 * Directories
 *
 * An application cannot create a directory with CreateFile; it must call CreateDirectory to create
 * a directory.
 *
 * Some file systems, such as NTFS, support compression or encryption for individual files and
 * directories. On volumes formatted for such a file system, a new directory inherits the
 * compression and encryption attributes of its parent directory.
 */
WINBASEAPI
HANDLE
WINAPI
CreateFileW(
    LPCWSTR lpFileName,
    DWORD dwDesiredAccess,
    DWORD dwShareMode,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    DWORD dwCreationDisposition,
    DWORD dwFlagsAndAttributes,
    HANDLE hTemplateFile
    );
#ifdef UNICODE
/**
 * This function creates, opens, or truncates a file, communications resource, disk device, or
 * console. It returns a handle that can be used to access the object. It can also open and return a
 * handle to a directory.
 *
 * @param lpFileName [in] Pointer to a null-terminated string that specifies the name of the object
 *   (file, communications resource, disk device, console, or directory) to create or open. If
 *   *lpFileName is a path, there is a default string size limit of MAX_PATH characters. This limit is
 *   related to how the CreateFile function parses paths. When lpFileName points to a communications
 *   resource to open, you must include a colon after the name. For example, specify "COM1:" to open
 *   that port.
 * @param dwDesiredAccess [in] Specifies the type of access to the object. An application can obtain
 *   read access, write access, read-write access, or device query access. This parameter can be any
 *   combination of the following values. Value Description 0 Specifies device query access to the
 *   object. An application can query device attributes without accessing the device. GENERIC_READ
 *   Specifies read access to the object. Data can be read from the file and the file pointer can be
 *   moved. Combine with GENERIC_WRITE for read-write access. GENERIC_WRITE Specifies write access to
 *   the object. Data can be written to the file and the file pointer can be moved. Combine with
 *   GENERIC_READ for read-write access.
 * @param dwShareMode [in] Specifies how the object can be shared. If dwShareMode is 0, the object
 *   cannot be shared. Subsequent open operations on the object will fail, until the handle is closed.
 *   To share the object, use a combination of one or more of the following values: Value Description
 *   FILE_SHARE_READ Subsequent open operations on the object will succeed only if read access is
 *   requested. FILE_SHARE_WRITE Subsequent open operations on the object will succeed only if write
 *   access is requested.
 * @param lpSecurityAttributes [in] Ignored; set to NULL.
 * @param dwCreationDisposition [in] Specifies which action to take on files that exist, and which
 *   action to take when files do not exist. For more information about this parameter, see the
 *   Remarks section. This parameter must be one of the following values: Value Description CREATE_NEW
 *   Creates a new file. The function fails if the specified file already exists. CREATE_ALWAYS
 *   Creates a new file. If the file exists, the function overwrites the file and clears the existing
 *   attributes. OPEN_EXISTING Opens the file. The function fails if the file does not exist. See the
 *   Remarks section for a discussion of why you should use the OPEN_EXISTING flag if you are using
 *   the CreateFile function for devices, including the console. OPEN_ALWAYS Opens the file, if it
 *   exists. If the file does not exist, the function creates the file as if dwCreationDisposition
 *   were CREATE_NEW. TRUNCATE_EXISTING Opens the file. Once opened, the file is truncated so that its
 *   size is zero bytes. The calling process must open the file with at least GENERIC_WRITE access.
 *   The function fails if the file does not exist.
 * @param dwFlagsAndAttributes [in] Specifies the file attributes and flags for the file. Any
 *   combination of the following attributes is acceptable for the dwFlagsAndAttributes parameter,
 *   except all other file attributes override FILE_ATTRIBUTE_NORMAL. Value Description
 *   FILE_ATTRIBUTE_ARCHIVE The file should be archived. Applications use this attribute to mark files
 *   for backup or removal. FILE_ATTRIBUTE_HIDDEN The file is hidden. It is not to be included in an
 *   ordinary directory listing. FILE_ATTRIBUTE_NORMAL The file has no other attributes set. This
 *   attribute is valid only if used alone. FILE_ATTRIBUTE_READONLY The file is read only.
 *   Applications can read the file but cannot write to it or delete it. FILE_ATTRIBUTE_SYSTEM The
 *   file is part of or is used exclusively by the operating system. FILE_ATTRIBUTE_TEMPORARY Not
 *   supported. Any combination of the following flags is acceptable for the dwFlagsAndAttributes
 *   parameter. Value Description FILE_FLAG_WRITE_THROUGH Instructs the system to write through any
 *   intermediate cache and go directly to disk. The system can still cache write operations, but
 *   cannot lazily flush them. FILE_FLAG_OVERLAPPED This flag is not supported; however, multiple
 *   reads/writes pending on a device at a time are allowed. FILE_FLAG_RANDOM_ACCESS Indicates that
 *   the file is accessed randomly. The system can use this as a hint to optimize file caching.
 *   FILE_FLAG_SEQUENTIAL_SCAN Indicates that the file is to be accessed sequentially from beginning
 *   to end. The system can use this as a hint to optimize file caching. If an application moves the
 *   file pointer for random access, optimum caching may not occur; however, correct operation is
 *   still guaranteed. Specifying this flag can increase performance for applications that read large
 *   files using sequential access. Performance gains can be even more noticeable for applications
 *   that read large files mostly sequentially, but occasionally skip over small ranges of bytes.
 * @param hTemplateFile [in] Ignored; as a result, CreateFile does not copy the extended attributes
 *   to the new file.
 *
 * @return An open handle to the specified file indicates success. If the specified file exists
 *   before the function call and dwCreationDisposition is CREATE_ALWAYS or OPEN_ALWAYS, a call to
 *   GetLastError returns ERROR_ALREADY_EXISTS, even though the function has succeeded. If the file
 *   does not exist before the call, GetLastError returns zero. INVALID_HANDLE_VALUE indicates
 *   failure. To get extended error information, call GetLastError.
 *
 * Use the CloseHandle function to close an object handle returned by CreateFile.
 *
 * As noted above, specifying zero for dwDesiredAccess allows an application to query device
 * attributes without actually accessing the device. This type of querying is useful, for example,
 * if an application wants to determine the size of a floppy disk drive and the formats it supports
 * without having a floppy in the drive.
 *
 * Files
 *
 * When creating a new file, the CreateFile function performs the following actions:
 *
 * Combines the file attributes and flags specified by dwFlagsAndAttributes with
 * FILE_ATTRIBUTE_ARCHIVE.
 *
 * Sets the file length to zero.
 *
 * When opening an existing file, CreateFile performs the following actions:
 *
 * Combines the file flags specified by dwFlagsAndAttributes with existing file attributes.
 * CreateFile ignores the file attributes specified by dwFlagsAndAttributes.
 *
 * Sets the file length according to the value of dwCreationDisposition.
 *
 * To store the maximum number of files on PC Card storage devices, limit file names to eight
 * uppercase characters and file extensions to three uppercase characters. Also, do not allow
 * non-OEM characters in file names. File names that do not conform to these limits require more
 * than one physical directory entry on a PC Card.
 *
 * Communications Resources
 *
 * The CreateFile function can create a handle to a communications resource. By setting the
 * dwCreationDisposition parameter to OPEN_EXISTING, read, write, or read-write access can be
 * specified.
 *
 * Directories
 *
 * An application cannot create a directory with CreateFile; it must call CreateDirectory to create
 * a directory.
 *
 * Some file systems, such as NTFS, support compression or encryption for individual files and
 * directories. On volumes formatted for such a file system, a new directory inherits the
 * compression and encryption attributes of its parent directory.
 */
#define CreateFile  CreateFileW
#else
/**
 * This function creates, opens, or truncates a file, communications resource, disk device, or
 * console. It returns a handle that can be used to access the object. It can also open and return a
 * handle to a directory.
 *
 * @param lpFileName [in] Pointer to a null-terminated string that specifies the name of the object
 *   (file, communications resource, disk device, console, or directory) to create or open. If
 *   *lpFileName is a path, there is a default string size limit of MAX_PATH characters. This limit is
 *   related to how the CreateFile function parses paths. When lpFileName points to a communications
 *   resource to open, you must include a colon after the name. For example, specify "COM1:" to open
 *   that port.
 * @param dwDesiredAccess [in] Specifies the type of access to the object. An application can obtain
 *   read access, write access, read-write access, or device query access. This parameter can be any
 *   combination of the following values. Value Description 0 Specifies device query access to the
 *   object. An application can query device attributes without accessing the device. GENERIC_READ
 *   Specifies read access to the object. Data can be read from the file and the file pointer can be
 *   moved. Combine with GENERIC_WRITE for read-write access. GENERIC_WRITE Specifies write access to
 *   the object. Data can be written to the file and the file pointer can be moved. Combine with
 *   GENERIC_READ for read-write access.
 * @param dwShareMode [in] Specifies how the object can be shared. If dwShareMode is 0, the object
 *   cannot be shared. Subsequent open operations on the object will fail, until the handle is closed.
 *   To share the object, use a combination of one or more of the following values: Value Description
 *   FILE_SHARE_READ Subsequent open operations on the object will succeed only if read access is
 *   requested. FILE_SHARE_WRITE Subsequent open operations on the object will succeed only if write
 *   access is requested.
 * @param lpSecurityAttributes [in] Ignored; set to NULL.
 * @param dwCreationDisposition [in] Specifies which action to take on files that exist, and which
 *   action to take when files do not exist. For more information about this parameter, see the
 *   Remarks section. This parameter must be one of the following values: Value Description CREATE_NEW
 *   Creates a new file. The function fails if the specified file already exists. CREATE_ALWAYS
 *   Creates a new file. If the file exists, the function overwrites the file and clears the existing
 *   attributes. OPEN_EXISTING Opens the file. The function fails if the file does not exist. See the
 *   Remarks section for a discussion of why you should use the OPEN_EXISTING flag if you are using
 *   the CreateFile function for devices, including the console. OPEN_ALWAYS Opens the file, if it
 *   exists. If the file does not exist, the function creates the file as if dwCreationDisposition
 *   were CREATE_NEW. TRUNCATE_EXISTING Opens the file. Once opened, the file is truncated so that its
 *   size is zero bytes. The calling process must open the file with at least GENERIC_WRITE access.
 *   The function fails if the file does not exist.
 * @param dwFlagsAndAttributes [in] Specifies the file attributes and flags for the file. Any
 *   combination of the following attributes is acceptable for the dwFlagsAndAttributes parameter,
 *   except all other file attributes override FILE_ATTRIBUTE_NORMAL. Value Description
 *   FILE_ATTRIBUTE_ARCHIVE The file should be archived. Applications use this attribute to mark files
 *   for backup or removal. FILE_ATTRIBUTE_HIDDEN The file is hidden. It is not to be included in an
 *   ordinary directory listing. FILE_ATTRIBUTE_NORMAL The file has no other attributes set. This
 *   attribute is valid only if used alone. FILE_ATTRIBUTE_READONLY The file is read only.
 *   Applications can read the file but cannot write to it or delete it. FILE_ATTRIBUTE_SYSTEM The
 *   file is part of or is used exclusively by the operating system. FILE_ATTRIBUTE_TEMPORARY Not
 *   supported. Any combination of the following flags is acceptable for the dwFlagsAndAttributes
 *   parameter. Value Description FILE_FLAG_WRITE_THROUGH Instructs the system to write through any
 *   intermediate cache and go directly to disk. The system can still cache write operations, but
 *   cannot lazily flush them. FILE_FLAG_OVERLAPPED This flag is not supported; however, multiple
 *   reads/writes pending on a device at a time are allowed. FILE_FLAG_RANDOM_ACCESS Indicates that
 *   the file is accessed randomly. The system can use this as a hint to optimize file caching.
 *   FILE_FLAG_SEQUENTIAL_SCAN Indicates that the file is to be accessed sequentially from beginning
 *   to end. The system can use this as a hint to optimize file caching. If an application moves the
 *   file pointer for random access, optimum caching may not occur; however, correct operation is
 *   still guaranteed. Specifying this flag can increase performance for applications that read large
 *   files using sequential access. Performance gains can be even more noticeable for applications
 *   that read large files mostly sequentially, but occasionally skip over small ranges of bytes.
 * @param hTemplateFile [in] Ignored; as a result, CreateFile does not copy the extended attributes
 *   to the new file.
 *
 * @return An open handle to the specified file indicates success. If the specified file exists
 *   before the function call and dwCreationDisposition is CREATE_ALWAYS or OPEN_ALWAYS, a call to
 *   GetLastError returns ERROR_ALREADY_EXISTS, even though the function has succeeded. If the file
 *   does not exist before the call, GetLastError returns zero. INVALID_HANDLE_VALUE indicates
 *   failure. To get extended error information, call GetLastError.
 *
 * Use the CloseHandle function to close an object handle returned by CreateFile.
 *
 * As noted above, specifying zero for dwDesiredAccess allows an application to query device
 * attributes without actually accessing the device. This type of querying is useful, for example,
 * if an application wants to determine the size of a floppy disk drive and the formats it supports
 * without having a floppy in the drive.
 *
 * Files
 *
 * When creating a new file, the CreateFile function performs the following actions:
 *
 * Combines the file attributes and flags specified by dwFlagsAndAttributes with
 * FILE_ATTRIBUTE_ARCHIVE.
 *
 * Sets the file length to zero.
 *
 * When opening an existing file, CreateFile performs the following actions:
 *
 * Combines the file flags specified by dwFlagsAndAttributes with existing file attributes.
 * CreateFile ignores the file attributes specified by dwFlagsAndAttributes.
 *
 * Sets the file length according to the value of dwCreationDisposition.
 *
 * To store the maximum number of files on PC Card storage devices, limit file names to eight
 * uppercase characters and file extensions to three uppercase characters. Also, do not allow
 * non-OEM characters in file names. File names that do not conform to these limits require more
 * than one physical directory entry on a PC Card.
 *
 * Communications Resources
 *
 * The CreateFile function can create a handle to a communications resource. By setting the
 * dwCreationDisposition parameter to OPEN_EXISTING, read, write, or read-write access can be
 * specified.
 *
 * Directories
 *
 * An application cannot create a directory with CreateFile; it must call CreateDirectory to create
 * a directory.
 *
 * Some file systems, such as NTFS, support compression or encryption for individual files and
 * directories. On volumes formatted for such a file system, a new directory inherits the
 * compression and encryption attributes of its parent directory.
 */
#define CreateFile  CreateFileA
#endif // !UNICODE

/**
 * This function deletes an existing file from a file system. A remote application interface (RAPI)
 * version of this function exists, and it is named CeDeleteFile.
 *
 * @param lpFileName [in] Pointer to a null-terminated string that specifies the file to be deleted.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * If an application attempts to delete a file that does not exist, the DeleteFile function fails.
 *
 * The DeleteFile function fails if an application attempts to delete a file that is open for normal
 * I/O or as a memory-mapped file.
 *
 * To close an open file, use the CloseHandle function.
 */
WINBASEAPI
BOOL
WINAPI
DeleteFileA(
    LPCSTR lpFileName
    );
/**
 * This function deletes an existing file from a file system. A remote application interface (RAPI)
 * version of this function exists, and it is named CeDeleteFile.
 *
 * @param lpFileName [in] Pointer to a null-terminated string that specifies the file to be deleted.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * If an application attempts to delete a file that does not exist, the DeleteFile function fails.
 *
 * The DeleteFile function fails if an application attempts to delete a file that is open for normal
 * I/O or as a memory-mapped file.
 *
 * To close an open file, use the CloseHandle function.
 */
WINBASEAPI
BOOL
WINAPI
DeleteFileW(
    LPCWSTR lpFileName
    );
#ifdef UNICODE
/**
 * This function deletes an existing file from a file system. A remote application interface (RAPI)
 * version of this function exists, and it is named CeDeleteFile.
 *
 * @param lpFileName [in] Pointer to a null-terminated string that specifies the file to be deleted.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * If an application attempts to delete a file that does not exist, the DeleteFile function fails.
 *
 * The DeleteFile function fails if an application attempts to delete a file that is open for normal
 * I/O or as a memory-mapped file.
 *
 * To close an open file, use the CloseHandle function.
 */
#define DeleteFile  DeleteFileW
#else
/**
 * This function deletes an existing file from a file system. A remote application interface (RAPI)
 * version of this function exists, and it is named CeDeleteFile.
 *
 * @param lpFileName [in] Pointer to a null-terminated string that specifies the file to be deleted.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * If an application attempts to delete a file that does not exist, the DeleteFile function fails.
 *
 * The DeleteFile function fails if an application attempts to delete a file that is open for normal
 * I/O or as a memory-mapped file.
 *
 * To close an open file, use the CloseHandle function.
 */
#define DeleteFile  DeleteFileA
#endif // !UNICODE

/**
 * This function deletes the source file (lpszSourFile) after it copies the content of the source
 * file to the destination file (lpszDestFile).
 *
 * @param lpszDestFile [in] Pointer to the null-terminated string that contains the path to the
 *   destination file, and cannot be NULL.
 * @param lpszSourFile [in] Pointer to the null-terminated string that contains the path to the
 *   source file, and cannot be NULL.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError.
 *
 * The DeleteAndRenameFile function works for the object store RAM-based file system only.
 */
WINBASEAPI
BOOL
WINAPI
DeleteAndRenameFile(
    LPCWSTR lpOldFileName,
    LPCWSTR lpNewFileName
    );

/**
 * This function searches a directory for a file whose name matches the specified file name.
 * FindFirstFile examines subdirectory names as well as file names.
 *
 * @param lpFileName [in] Pointer to a null-terminated string that specifies a valid directory or
 *   path and filename, which can contain wildcard characters (* and ?). There is a default string
 *   size limit for paths of MAX_PATH characters. This limit is related to how the FindFirstFile
 *   function parses paths.
 * @param lpFindFileData [out] Pointer to the WIN32_FIND_DATA structure that receives information
 *   about the found file or subdirectory.
 *
 * @return A search handle, used in a subsequent call to FindNextFile or FindClose, indicates
 *   success. INVALID_HANDLE_VALUE indicates failure. To get extended error information, call
 *   GetLastError.
 *
 * The FindFirstFile function opens a search handle and returns information about the first file
 * whose name matches the specified pattern. Once the search handle is established, you can use the
 * FindNextFile function to search for other files that match the same pattern. When the search
 * handle is no longer needed, close it by using the FindClose function.
 *
 * This function searches for files by name only; it cannot be used for attribute-based searches.
 */
WINBASEAPI
HANDLE
WINAPI
FindFirstFileA(
    LPCSTR lpFileName,
    LPWIN32_FIND_DATAA lpFindFileData
    );

/**
 * This function searches a directory for a file whose name matches the specified file name.
 * FindFirstFile examines subdirectory names as well as file names.
 *
 * @param lpFileName [in] Pointer to a null-terminated string that specifies a valid directory or
 *   path and filename, which can contain wildcard characters (* and ?). There is a default string
 *   size limit for paths of MAX_PATH characters. This limit is related to how the FindFirstFile
 *   function parses paths.
 * @param lpFindFileData [out] Pointer to the WIN32_FIND_DATA structure that receives information
 *   about the found file or subdirectory.
 *
 * @return A search handle, used in a subsequent call to FindNextFile or FindClose, indicates
 *   success. INVALID_HANDLE_VALUE indicates failure. To get extended error information, call
 *   GetLastError.
 *
 * The FindFirstFile function opens a search handle and returns information about the first file
 * whose name matches the specified pattern. Once the search handle is established, you can use the
 * FindNextFile function to search for other files that match the same pattern. When the search
 * handle is no longer needed, close it by using the FindClose function.
 *
 * This function searches for files by name only; it cannot be used for attribute-based searches.
 */
WINBASEAPI
HANDLE
WINAPI
FindFirstFileW(
    LPCWSTR lpFileName,
    LPWIN32_FIND_DATAW lpFindFileData
    );
#ifdef UNICODE
/**
 * This function searches a directory for a file whose name matches the specified file name.
 * FindFirstFile examines subdirectory names as well as file names.
 *
 * @param lpFileName [in] Pointer to a null-terminated string that specifies a valid directory or
 *   path and filename, which can contain wildcard characters (* and ?). There is a default string
 *   size limit for paths of MAX_PATH characters. This limit is related to how the FindFirstFile
 *   function parses paths.
 * @param lpFindFileData [out] Pointer to the WIN32_FIND_DATA structure that receives information
 *   about the found file or subdirectory.
 *
 * @return A search handle, used in a subsequent call to FindNextFile or FindClose, indicates
 *   success. INVALID_HANDLE_VALUE indicates failure. To get extended error information, call
 *   GetLastError.
 *
 * The FindFirstFile function opens a search handle and returns information about the first file
 * whose name matches the specified pattern. Once the search handle is established, you can use the
 * FindNextFile function to search for other files that match the same pattern. When the search
 * handle is no longer needed, close it by using the FindClose function.
 *
 * This function searches for files by name only; it cannot be used for attribute-based searches.
 */
#define FindFirstFile  FindFirstFileW
#else
/**
 * This function searches a directory for a file whose name matches the specified file name.
 * FindFirstFile examines subdirectory names as well as file names.
 *
 * @param lpFileName [in] Pointer to a null-terminated string that specifies a valid directory or
 *   path and filename, which can contain wildcard characters (* and ?). There is a default string
 *   size limit for paths of MAX_PATH characters. This limit is related to how the FindFirstFile
 *   function parses paths.
 * @param lpFindFileData [out] Pointer to the WIN32_FIND_DATA structure that receives information
 *   about the found file or subdirectory.
 *
 * @return A search handle, used in a subsequent call to FindNextFile or FindClose, indicates
 *   success. INVALID_HANDLE_VALUE indicates failure. To get extended error information, call
 *   GetLastError.
 *
 * The FindFirstFile function opens a search handle and returns information about the first file
 * whose name matches the specified pattern. Once the search handle is established, you can use the
 * FindNextFile function to search for other files that match the same pattern. When the search
 * handle is no longer needed, close it by using the FindClose function.
 *
 * This function searches for files by name only; it cannot be used for attribute-based searches.
 */
#define FindFirstFile  FindFirstFileA
#endif // !UNICODE

/**
 * This function continues a file search from a previous call to the FindFirstFile function.
 *
 * @param hFindFile [in] Search handle returned by a previous call to the FindFirstFile function.
 * @param lpFindFileData [out] Pointer to the WIN32_FIND_DATA structure that receives information
 *   about the found file or subdirectory. The structure can be used in subsequent calls to
 *   FindNextFile to refer to the found file or directory.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError. If no matching files can be found, the GetLastError function returns
 *   ERROR_NO_MORE_FILES.
 *
 * The FindNextFile function searches for files by name only; it cannot be used for attribute-based
 * searches.
 */
WINBASEAPI
BOOL
WINAPI
FindNextFileA(
    HANDLE hFindFile,
    LPWIN32_FIND_DATAA lpFindFileData
    );

/**
 * This function continues a file search from a previous call to the FindFirstFile function.
 *
 * @param hFindFile [in] Search handle returned by a previous call to the FindFirstFile function.
 * @param lpFindFileData [out] Pointer to the WIN32_FIND_DATA structure that receives information
 *   about the found file or subdirectory. The structure can be used in subsequent calls to
 *   FindNextFile to refer to the found file or directory.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError. If no matching files can be found, the GetLastError function returns
 *   ERROR_NO_MORE_FILES.
 *
 * The FindNextFile function searches for files by name only; it cannot be used for attribute-based
 * searches.
 */
WINBASEAPI
BOOL
WINAPI
FindNextFileW(
    HANDLE hFindFile,
    LPWIN32_FIND_DATAW lpFindFileData
    );
#ifdef UNICODE
/**
 * This function continues a file search from a previous call to the FindFirstFile function.
 *
 * @param hFindFile [in] Search handle returned by a previous call to the FindFirstFile function.
 * @param lpFindFileData [out] Pointer to the WIN32_FIND_DATA structure that receives information
 *   about the found file or subdirectory. The structure can be used in subsequent calls to
 *   FindNextFile to refer to the found file or directory.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError. If no matching files can be found, the GetLastError function returns
 *   ERROR_NO_MORE_FILES.
 *
 * The FindNextFile function searches for files by name only; it cannot be used for attribute-based
 * searches.
 */
#define FindNextFile  FindNextFileW
#else
/**
 * This function continues a file search from a previous call to the FindFirstFile function.
 *
 * @param hFindFile [in] Search handle returned by a previous call to the FindFirstFile function.
 * @param lpFindFileData [out] Pointer to the WIN32_FIND_DATA structure that receives information
 *   about the found file or subdirectory. The structure can be used in subsequent calls to
 *   FindNextFile to refer to the found file or directory.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError. If no matching files can be found, the GetLastError function returns
 *   ERROR_NO_MORE_FILES.
 *
 * The FindNextFile function searches for files by name only; it cannot be used for attribute-based
 * searches.
 */
#define FindNextFile  FindNextFileA
#endif // !UNICODE

/**
 * This function copies an existing file to a new file. A remote application interface (RAPI)
 * version of this function exists, named CeCopyFile.
 *
 * @param lpExistingFileName [in] Long pointer to a null-terminated string that specifies the name
 *   of an existing file.
 * @param lpNewFileName [in] Long pointer to a null-terminated string that specifies the name of the
 *   new file.
 * @param bFailIfExists [in] Boolean that specifies how this operation is to proceed if a file of
 *   the same name as that specified by lpNewFileName already exists. If this parameter is TRUE and
 *   the new file already exists, the function fails. If this parameter is FALSE and the new file
 *   already exists, the function overwrites the existing file and succeeds.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * Security attributes for the existing file are not copied to the new file.
 *
 * File attributes for the existing file are copied to the new file. For example, if an existing
 * file has the FILE_ATTRIBUTE_READONLY file attribute, a copy created through a call to CopyFile
 * will also have the FILE_ATTRIBUTE_READONLY file attribute. For more information about file
 * attributes, see CreateFile.
 *
 * To store the maximum number of files on PC Card storage devices, limit file names to eight
 * uppercase characters and file extensions to three uppercase characters. Also, do not allow
 * non-OEM characters in file names. File names that do not conform to these limits require more
 * than one physical directory entry on a PC Card.
 */
WINBASEAPI
BOOL
WINAPI
CopyFileA(
    LPCSTR lpExistingFileName,
    LPCSTR lpNewFileName,
    BOOL bFailIfExists
    );
/**
 * This function copies an existing file to a new file. A remote application interface (RAPI)
 * version of this function exists, named CeCopyFile.
 *
 * @param lpExistingFileName [in] Long pointer to a null-terminated string that specifies the name
 *   of an existing file.
 * @param lpNewFileName [in] Long pointer to a null-terminated string that specifies the name of the
 *   new file.
 * @param bFailIfExists [in] Boolean that specifies how this operation is to proceed if a file of
 *   the same name as that specified by lpNewFileName already exists. If this parameter is TRUE and
 *   the new file already exists, the function fails. If this parameter is FALSE and the new file
 *   already exists, the function overwrites the existing file and succeeds.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * Security attributes for the existing file are not copied to the new file.
 *
 * File attributes for the existing file are copied to the new file. For example, if an existing
 * file has the FILE_ATTRIBUTE_READONLY file attribute, a copy created through a call to CopyFile
 * will also have the FILE_ATTRIBUTE_READONLY file attribute. For more information about file
 * attributes, see CreateFile.
 *
 * To store the maximum number of files on PC Card storage devices, limit file names to eight
 * uppercase characters and file extensions to three uppercase characters. Also, do not allow
 * non-OEM characters in file names. File names that do not conform to these limits require more
 * than one physical directory entry on a PC Card.
 */
WINBASEAPI
BOOL
WINAPI
CopyFileW(
    LPCWSTR lpExistingFileName,
    LPCWSTR lpNewFileName,
    BOOL bFailIfExists
    );
#ifdef UNICODE
/**
 * This function copies an existing file to a new file. A remote application interface (RAPI)
 * version of this function exists, named CeCopyFile.
 *
 * @param lpExistingFileName [in] Long pointer to a null-terminated string that specifies the name
 *   of an existing file.
 * @param lpNewFileName [in] Long pointer to a null-terminated string that specifies the name of the
 *   new file.
 * @param bFailIfExists [in] Boolean that specifies how this operation is to proceed if a file of
 *   the same name as that specified by lpNewFileName already exists. If this parameter is TRUE and
 *   the new file already exists, the function fails. If this parameter is FALSE and the new file
 *   already exists, the function overwrites the existing file and succeeds.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * Security attributes for the existing file are not copied to the new file.
 *
 * File attributes for the existing file are copied to the new file. For example, if an existing
 * file has the FILE_ATTRIBUTE_READONLY file attribute, a copy created through a call to CopyFile
 * will also have the FILE_ATTRIBUTE_READONLY file attribute. For more information about file
 * attributes, see CreateFile.
 *
 * To store the maximum number of files on PC Card storage devices, limit file names to eight
 * uppercase characters and file extensions to three uppercase characters. Also, do not allow
 * non-OEM characters in file names. File names that do not conform to these limits require more
 * than one physical directory entry on a PC Card.
 */
#define CopyFile  CopyFileW
#else
/**
 * This function copies an existing file to a new file. A remote application interface (RAPI)
 * version of this function exists, named CeCopyFile.
 *
 * @param lpExistingFileName [in] Long pointer to a null-terminated string that specifies the name
 *   of an existing file.
 * @param lpNewFileName [in] Long pointer to a null-terminated string that specifies the name of the
 *   new file.
 * @param bFailIfExists [in] Boolean that specifies how this operation is to proceed if a file of
 *   the same name as that specified by lpNewFileName already exists. If this parameter is TRUE and
 *   the new file already exists, the function fails. If this parameter is FALSE and the new file
 *   already exists, the function overwrites the existing file and succeeds.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * Security attributes for the existing file are not copied to the new file.
 *
 * File attributes for the existing file are copied to the new file. For example, if an existing
 * file has the FILE_ATTRIBUTE_READONLY file attribute, a copy created through a call to CopyFile
 * will also have the FILE_ATTRIBUTE_READONLY file attribute. For more information about file
 * attributes, see CreateFile.
 *
 * To store the maximum number of files on PC Card storage devices, limit file names to eight
 * uppercase characters and file extensions to three uppercase characters. Also, do not allow
 * non-OEM characters in file names. File names that do not conform to these limits require more
 * than one physical directory entry on a PC Card.
 */
#define CopyFile  CopyFileA
#endif // !UNICODE

/**
 * This function renames an existing file or a directory-including all its children.
 *
 * @param lpExistingFileName [in] Pointer to a null-terminated string that names an existing file or
 *   directory.
 * @param lpNewFileName [in] Pointer to a null-terminated string that specifies the new name of a
 *   file or directory. The new name must not already exist. A new file may be on a different file
 *   system or drive. A new directory must be on the same drive.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * The MoveFile function will move (rename) either a file or a directory (including all its
 * children) either in the same directory or across directories. The one caveat is that the MoveFile
 * function will fail on directory moves when the destination is on a different volume.
 */
WINBASEAPI
BOOL
WINAPI
MoveFileA(
    LPCSTR lpExistingFileName,
    LPCSTR lpNewFileName
    );
/**
 * This function renames an existing file or a directory-including all its children.
 *
 * @param lpExistingFileName [in] Pointer to a null-terminated string that names an existing file or
 *   directory.
 * @param lpNewFileName [in] Pointer to a null-terminated string that specifies the new name of a
 *   file or directory. The new name must not already exist. A new file may be on a different file
 *   system or drive. A new directory must be on the same drive.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * The MoveFile function will move (rename) either a file or a directory (including all its
 * children) either in the same directory or across directories. The one caveat is that the MoveFile
 * function will fail on directory moves when the destination is on a different volume.
 */
WINBASEAPI
BOOL
WINAPI
MoveFileW(
    LPCWSTR lpExistingFileName,
    LPCWSTR lpNewFileName
    );
#ifdef UNICODE
/**
 * This function renames an existing file or a directory-including all its children.
 *
 * @param lpExistingFileName [in] Pointer to a null-terminated string that names an existing file or
 *   directory.
 * @param lpNewFileName [in] Pointer to a null-terminated string that specifies the new name of a
 *   file or directory. The new name must not already exist. A new file may be on a different file
 *   system or drive. A new directory must be on the same drive.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * The MoveFile function will move (rename) either a file or a directory (including all its
 * children) either in the same directory or across directories. The one caveat is that the MoveFile
 * function will fail on directory moves when the destination is on a different volume.
 */
#define MoveFile  MoveFileW
#else
/**
 * This function renames an existing file or a directory-including all its children.
 *
 * @param lpExistingFileName [in] Pointer to a null-terminated string that names an existing file or
 *   directory.
 * @param lpNewFileName [in] Pointer to a null-terminated string that specifies the new name of a
 *   file or directory. The new name must not already exist. A new file may be on a different file
 *   system or drive. A new directory must be on the same drive.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * The MoveFile function will move (rename) either a file or a directory (including all its
 * children) either in the same directory or across directories. The one caveat is that the MoveFile
 * function will fail on directory moves when the destination is on a different volume.
 */
#define MoveFile  MoveFileA
#endif // !UNICODE


/**
 * This function creates a new directory. If the underlying file system supports security on files
 * and directories, the function applies a specified security descriptor to the new directory.
 *
 * @param lpPathName [in] Long pointer to a null-terminated string that specifies the path of the
 *   directory to be created. There is a default string size limit for paths of MAX_PATH characters.
 *   This limit is related to how the CreateDirectory function parses paths.
 * @param lpSecurityAttributes [in] Ignored; set to NULL.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * Some file systems, such as NTFS, support compression or encryption for individual files and
 * directories. On volumes formatted for such a file system, a new directory inherits the
 * compression and encryption attributes of its parent directory.
 */
WINBASEAPI
BOOL
WINAPI
CreateDirectoryA(
    LPCSTR lpPathName,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes
    );
/**
 * This function creates a new directory. If the underlying file system supports security on files
 * and directories, the function applies a specified security descriptor to the new directory.
 *
 * @param lpPathName [in] Long pointer to a null-terminated string that specifies the path of the
 *   directory to be created. There is a default string size limit for paths of MAX_PATH characters.
 *   This limit is related to how the CreateDirectory function parses paths.
 * @param lpSecurityAttributes [in] Ignored; set to NULL.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * Some file systems, such as NTFS, support compression or encryption for individual files and
 * directories. On volumes formatted for such a file system, a new directory inherits the
 * compression and encryption attributes of its parent directory.
 */
WINBASEAPI
BOOL
WINAPI
CreateDirectoryW(
    LPCWSTR lpPathName,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes
    );
#ifdef UNICODE
/**
 * This function creates a new directory. If the underlying file system supports security on files
 * and directories, the function applies a specified security descriptor to the new directory.
 *
 * @param lpPathName [in] Long pointer to a null-terminated string that specifies the path of the
 *   directory to be created. There is a default string size limit for paths of MAX_PATH characters.
 *   This limit is related to how the CreateDirectory function parses paths.
 * @param lpSecurityAttributes [in] Ignored; set to NULL.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * Some file systems, such as NTFS, support compression or encryption for individual files and
 * directories. On volumes formatted for such a file system, a new directory inherits the
 * compression and encryption attributes of its parent directory.
 */
#define CreateDirectory  CreateDirectoryW
#else
/**
 * This function creates a new directory. If the underlying file system supports security on files
 * and directories, the function applies a specified security descriptor to the new directory.
 *
 * @param lpPathName [in] Long pointer to a null-terminated string that specifies the path of the
 *   directory to be created. There is a default string size limit for paths of MAX_PATH characters.
 *   This limit is related to how the CreateDirectory function parses paths.
 * @param lpSecurityAttributes [in] Ignored; set to NULL.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * Some file systems, such as NTFS, support compression or encryption for individual files and
 * directories. On volumes formatted for such a file system, a new directory inherits the
 * compression and encryption attributes of its parent directory.
 */
#define CreateDirectory  CreateDirectoryA
#endif // !UNICODE

/**
 * This function deletes an existing empty directory. A remote application interface (RAPI) version
 * of this function exists, and it is called CeRemoveDirectory.
 *
 * @param lpPathName [in] Pointer to a null-terminated string that specifies the path of the
 *   directory to be removed. The path must specify an empty directory, and the calling process must
 *   have delete access to the directory.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 */
WINBASEAPI
BOOL
WINAPI
RemoveDirectoryA(
    LPCSTR lpPathName
    );
/**
 * This function deletes an existing empty directory. A remote application interface (RAPI) version
 * of this function exists, and it is called CeRemoveDirectory.
 *
 * @param lpPathName [in] Pointer to a null-terminated string that specifies the path of the
 *   directory to be removed. The path must specify an empty directory, and the calling process must
 *   have delete access to the directory.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 */
WINBASEAPI
BOOL
WINAPI
RemoveDirectoryW(
    LPCWSTR lpPathName
    );
#ifdef UNICODE
/**
 * This function deletes an existing empty directory. A remote application interface (RAPI) version
 * of this function exists, and it is called CeRemoveDirectory.
 *
 * @param lpPathName [in] Pointer to a null-terminated string that specifies the path of the
 *   directory to be removed. The path must specify an empty directory, and the calling process must
 *   have delete access to the directory.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 */
#define RemoveDirectory  RemoveDirectoryW
#else
/**
 * This function deletes an existing empty directory. A remote application interface (RAPI) version
 * of this function exists, and it is called CeRemoveDirectory.
 *
 * @param lpPathName [in] Pointer to a null-terminated string that specifies the path of the
 *   directory to be removed. The path must specify an empty directory, and the calling process must
 *   have delete access to the directory.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 */
#define RemoveDirectory  RemoveDirectoryA
#endif // !UNICODE

/**
 * This function writes data to a file. WriteFile starts writing data to the file at the position
 * indicated by the file pointer. After the write operation has been completed, the file pointer is
 * adjusted by the number of bytes actually written.
 *
 * @param hFile [in] Handle to the file to be written to. The file handle must have been created
 *   with GENERIC_WRITE access to the file.
 * @param lpBuffer [in] Pointer to the buffer containing the data to be written to the file.
 * @param nNumberOfBytesToWrite [in] Number of bytes to write to the file. A value of zero specifies
 *   a null write operation. A null write operation does not write any bytes but does cause the time
 *   stamp to change. WriteFile does not truncate or extend the file. To truncate or extend a file,
 *   use the SetEndOfFile function. Named pipe write operations across a network are limited to 65,535
 *   bytes.
 * @param lpNumberOfBytesWritten [out] Pointer to the number of bytes written by this function call.
 *   WriteFile sets this value to zero before doing any work or error checking.
 * @param lpOverlapped [in] Unsupported; set to NULL.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * If part of the file is locked by another process and the write operation overlaps the locked
 * portion, this function fails.
 *
 * Accessing the output buffer while a write operation is using the buffer may lead to corruption of
 * the data written from that buffer. Applications must not read from, write to, reallocate, or free
 * the output buffer that a write operation is using until the write operation completes.
 */
WINBASEAPI
BOOL
WINAPI
WriteFile(
    HANDLE hFile,
    LPCVOID lpBuffer,
    DWORD nNumberOfBytesToWrite,
    LPDWORD lpNumberOfBytesWritten,
    LPOVERLAPPED lpOverlapped
    );

/**
 * This function reads data from a file, starting at the position indicated by the file pointer.
 * After the read operation has been completed, the file pointer is adjusted by the number of bytes
 * actually read.
 *
 * @param hFile [in] Handle to the file to be read. The file handle must have been created with
 *   GENERIC_READ access to the file. This parameter cannot be a socket handle.
 * @param lpBuffer [out] Pointer to the buffer that receives the data read from the file.
 * @param nNumberOfBytesToRead [in] Number of bytes to be read from the file.
 * @param lpNumberOfBytesRead [out] Pointer to the number of bytes read. ReadFile sets this value to
 *   zero before doing any work or error checking.
 * @param lpOverlapped [in] Unsupported; set to NULL.
 *
 * @return The ReadFile function returns when one of the following is true: the number of bytes
 *   requested has been read or an error occurs. Nonzero indicates success. If the return value is
 *   nonzero and the number of bytes read is zero, the file pointer was beyond the current end of the
 *   file at the time of the read operation. Zero indicates failure. To get extended error
 *   information, call GetLastError.
 *
 * If part of the file is locked by another process and the read operation overlaps the locked
 * portion, this function fails.
 *
 * Accessing the input buffer while a read operation is using the buffer may lead to corruption of
 * the data read into that buffer. Applications must not read from, write to, reallocate, or free
 * the input buffer that a read operation is using until the read operation completes.
 *
 * When reading from a communications device, the behavior of ReadFile is governed by the current
 * communication time-outs as set and retrieved using the SetCommTimeouts and GetCommTimeouts
 * functions. Unpredictable results can occur if you fail to set the time-out values. For more
 * information about communication time-outs, see COMMTIMEOUTS.
 *
 * The ReadFile function may fail and return ERROR_INVALID_USER_BUFFER or ERROR_NOT_ENOUGH_MEMORY
 * whenever there are too many outstanding asynchronous I/O requests.
 *
 * When a synchronous read operation reaches the end of a file, ReadFile returns TRUE and sets
 * *lpNumberOfBytesRead to zero. Windows CE does not support asynchronous read operations on files.
 * The following sample code tests for end-of-file for a synchronous read operation:
 *
 *     // Attempt a synchronous read operation.
 *     bResult = ReadFile(hFile, &inBuffer, nBytesToRead, &nBytesRead, NULL) ;
 *     // Check for end of file.
 *     if (bResult &&  nBytesRead == 0, )
 *     {
 *         // we're at the end of the file
 *     }
 */
WINBASEAPI
BOOL
WINAPI
ReadFile(
    HANDLE hFile,
    LPVOID lpBuffer,
    DWORD nNumberOfBytesToRead,
    LPDWORD lpNumberOfBytesRead,
    LPOVERLAPPED lpOverlapped
    );

/**
 * This function clears the buffers for the specified file and causes all buffered data to be
 * written to the file.
 *
 * @param hFile [in] Handle to an open file. The function flushes this file's buffers. The file
 *   handle must have GENERIC_WRITE access to the file. If hFile is a handle to a communications
 *   device, the function only flushes the transmit buffer. If hFile is a handle to the server end of
 *   a named pipe, the function does not return until the client has read all buffered data from the
 *   pipe.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * The WriteFile function typically writes data to an internal buffer that the operating system
 * writes to disk on a regular basis. The FlushFileBuffers function writes all of the buffered
 * information for the specified file to disk.
 */
WINBASEAPI BOOL WINAPI FlushFileBuffers (HANDLE hFile);
/**
 * This function retrieves the date and time that a file was created, last accessed, and last
 * modified. A remote application interface (RAPI) version of this function exists, and it is named
 * CeGetFileTime.
 *
 * @param hFile [in] Handle to the files for which to get dates and times. The file handle must have
 *   been created with GENERIC_READ access to the file.
 * @param lpCreationTime [out] Pointer to a FILETIME structure to receive the date and time the file
 *   was created. This parameter can be NULL if the application does not require this information.
 * @param lpLastAccessTime [out] Pointer to a FILETIME structure to receive the date and time the
 *   file was last accessed. The last access time includes the last time the file was written to, read
 *   from, or, in the case of executable files, run. This parameter can be NULL if the application
 *   does not require this information.
 * @param lpLastWriteTime [out] Pointer to a FILETIME structure to receive the date and time the
 *   file was last written to. This parameter can be NULL if the application does not require this
 *   information.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * The FAT and NTFS file systems support the file creation, last access, and last write time values.
 * The Windows CE object store returns the same time for all three parameters. In general, file
 * system drivers will vary how they support this function.
 *
 * The precision of the time for a file in a FAT file system is one second. The time precision for
 * files in other file systems, such as those connected through a network or installed on a
 * peripheral device, depends on the file system but may also be limited by the remote device.
 */
WINBASEAPI BOOL WINAPI GetFileTime (HANDLE hFile, LPFILETIME lpCreation, LPFILETIME lpLastAccess, LPFILETIME lpLastWrite);
/**
 * This function sets the date and time that a file was created, last accessed, or last modified. A
 * remote application interface (RAPI) version of this function exists, and it is called
 * CeSetFileTime.
 *
 * @param hFile [in] Handle to the file for which to set the dates and times. The file handle must
 *   have been created with GENERIC_WRITE access to the file.
 * @param lpCreationTime [in] Pointer to a FILETIME structure that contains the date and time the
 *   file was created. This parameter can be NULL if the application does not need to set this
 *   information.
 * @param lpLastAccessTime [in] Pointer to a FILETIME structure that contains the date and time the
 *   file was last accessed. The last access time includes the last time the file was written to, read
 *   from, or (in the case of executable files) run. This parameter can be NULL if the application
 *   does not need to set this information.
 * @param lpLastWriteTime [in] Pointer to a FILETIME structure that contains the date and time the
 *   file was last written to. This parameter can be NULL if the application does not want to set this
 *   information.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * Not all file systems support all file time parameters. The Windows CE object store stores only
 * one file time and it can be set by any one of the three parameters.
 */
WINBASEAPI BOOL WINAPI SetFileTime (HANDLE hFile, CONST FILETIME *lpCreation, CONST FILETIME *lpLastAccess, CONST FILETIME *lpLastWrite);
/**
 * This function moves the end-of-file position for the specified file to the current position of
 * the file pointer. A remote application interface (RAPI) version of this function exists, and it
 * is called CeSetEndOfFile.
 *
 * @param hFile [in] Handle to the file to have its EOF position moved. The file handle must have
 *   been created with GENERIC_WRITE access to the file.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * This function can be used to truncate or extend a file. If the file is extended, the contents of
 * the file between the old EOF position and the new position are not defined.
 *
 * If you called CreateFileMapping to create a file-mapping object for hFile, you must first call
 * UnmapViewOfFile to unmap all views and call CloseHandle to close the file-mapping object before
 * you can call SetEndOfFile.
 */
WINBASEAPI BOOL WINAPI SetEndOfFile (HANDLE hFile);
/**
 * This function sends a control code directly to a specified device driver, causing the
 * corresponding device to perform the specified operation.
 *
 * @param hDevice [in] Handle to the device that is to perform the operation. Call the CreateFile
 *   function to obtain a device handle.
 * @param dwIoControlCode [in] Specifies the control code for the operation. This value identifies
 *   the specific operation to be performed and the type of device on which the operation is to be
 *   performed. No specific values are defined for the dwIoControlCode parameter. However, the writer
 *   of a custom device driver can define IOCTL_XXXX control codes, per the CTL_CODE macro. These
 *   control codes can then be advertised, and an application can use these control codes with
 *   DeviceIoControl to perform the driver-specific functions.
 * @param lpInBuffer [in] Long pointer to a buffer that contains the data required to perform the
 *   operation. This parameter can be NULL if the dwIoControlCode parameter specifies an operation
 *   that does not require input data.
 * @param nInBufferSize [in] Size, in bytes, of the buffer pointed to by lpInBuffer.
 * @param lpOutBuffer [out] Long pointer to a buffer that receives the operation's output data. This
 *   parameter can be NULL if the dwIoControlCode parameter specifies an operation that does not
 *   produce output data.
 * @param nOutBufferSize [in] Size, in bytes, of the buffer pointed to by lpOutBuffer.
 * @param lpBytesReturned [out] Long pointer to a variable that receives the size, in bytes, of the
 *   data stored into the buffer pointed to by lpOutBuffer. The lpBytesReturned parameter cannot be
 *   NULL. Even when an operation produces no output data, and lpOutBuffer can be NULL, the
 *   DeviceIoControl function makes use of the variable pointed to by lpBytesReturned. After such an
 *   operation, the value of the variable is without meaning.
 * @param lpOverlapped [in] Ignored; set to NULL.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 */
WINBASEAPI BOOL WINAPI DeviceIoControl (HANDLE hDevice, DWORD dwIoControlCode, LPVOID lpInBuf, DWORD nInBufSize, LPVOID lpOutBuf, DWORD nOutBufSize, LPDWORD lpBytesReturned, LPOVERLAPPED lpOverlapped);
/**
 * This function sets the attributes of a file. A remote application interface (RAPI) version of
 * this function exists, and it is called CeSetFileAttributes.
 *
 * @param lpFileName [in] Pointer to a string that specifies the name of the file whose attributes
 *   are to be set. There is a default string size limit for paths of MAX_PATH characters. This limit
 *   is related to how the SetFileAttributes function parses paths.
 * @param dwFileAttributes [in] Specifies the file attributes to set for the file. This parameter
 *   can be a combination of the following values. However, all other values override
 *   FILE_ATTRIBUTE_NORMAL. Value Description FILE_ATTRIBUTE_ARCHIVE The file is an archive file.
 *   Applications use this attribute to mark files for backup or removal. FILE_ATTRIBUTE_HIDDEN The
 *   file is hidden. It is not included in an ordinary directory listing. FILE_ATTRIBUTE_NORMAL The
 *   file has no other attributes set. This attribute is valid only if used alone.
 *   FILE_ATTRIBUTE_OFFLINE The data of the file is not immediately available. Indicates that the file
 *   data has been physically moved to offline storage. FILE_ATTRIBUTE_READONLY The file is read-only.
 *   Applications can read the file but cannot write to it or delete it. FILE_ATTRIBUTE_SYSTEM The
 *   file is part of the operating system or is used exclusively by it. FILE_ATTRIBUTE_TEMPORARY The
 *   file is being used for temporary storage. File systems attempt to keep all of the data in memory
 *   for quicker access rather than flushing the data back to mass storage. A temporary file should be
 *   deleted by the application as soon as it is no longer needed.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * The following table describes how to set the attributes that cannot be set using
 * SetFileAttributes.
 *
 * Attribute How to Set FILE_ATTRIBUTE_COMPRESSED To set a file's compression state, use the
 * DeviceIoControl function with the FSCTL_SET_COMPRESSION operation. FILE_ATTRIBUTE_DIRECTORY Files
 * cannot be converted into directories. To create a directory, use the CreateDirectory function.
 * FILE_ATTRIBUTE_REPARSE_POINT To associate a reparse point with a file, use the DeviceIoControl
 * function with the FSCTL_SET_REPARSE_POINT operation. FILE_ATTRIBUTE_SPARSE_FILE To set a file's
 * sparse attribute, use the DeviceIoControl function with the FSCTL_SET_SPARSE operation.
 * FILE_ATTRIBUTE_SYSTEM This attribute cannot be set.
 *
 * Not all file systems support all attributes.
 */
#define SetFileAttributes SetFileAttributesW
/**
 * This function sets the attributes of a file. A remote application interface (RAPI) version of
 * this function exists, and it is called CeSetFileAttributes.
 *
 * @param lpFileName [in] Pointer to a string that specifies the name of the file whose attributes
 *   are to be set. There is a default string size limit for paths of MAX_PATH characters. This limit
 *   is related to how the SetFileAttributes function parses paths.
 * @param dwFileAttributes [in] Specifies the file attributes to set for the file. This parameter
 *   can be a combination of the following values. However, all other values override
 *   FILE_ATTRIBUTE_NORMAL. Value Description FILE_ATTRIBUTE_ARCHIVE The file is an archive file.
 *   Applications use this attribute to mark files for backup or removal. FILE_ATTRIBUTE_HIDDEN The
 *   file is hidden. It is not included in an ordinary directory listing. FILE_ATTRIBUTE_NORMAL The
 *   file has no other attributes set. This attribute is valid only if used alone.
 *   FILE_ATTRIBUTE_OFFLINE The data of the file is not immediately available. Indicates that the file
 *   data has been physically moved to offline storage. FILE_ATTRIBUTE_READONLY The file is read-only.
 *   Applications can read the file but cannot write to it or delete it. FILE_ATTRIBUTE_SYSTEM The
 *   file is part of the operating system or is used exclusively by it. FILE_ATTRIBUTE_TEMPORARY The
 *   file is being used for temporary storage. File systems attempt to keep all of the data in memory
 *   for quicker access rather than flushing the data back to mass storage. A temporary file should be
 *   deleted by the application as soon as it is no longer needed.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * The following table describes how to set the attributes that cannot be set using
 * SetFileAttributes.
 *
 * Attribute How to Set FILE_ATTRIBUTE_COMPRESSED To set a file's compression state, use the
 * DeviceIoControl function with the FSCTL_SET_COMPRESSION operation. FILE_ATTRIBUTE_DIRECTORY Files
 * cannot be converted into directories. To create a directory, use the CreateDirectory function.
 * FILE_ATTRIBUTE_REPARSE_POINT To associate a reparse point with a file, use the DeviceIoControl
 * function with the FSCTL_SET_REPARSE_POINT operation. FILE_ATTRIBUTE_SPARSE_FILE To set a file's
 * sparse attribute, use the DeviceIoControl function with the FSCTL_SET_SPARSE operation.
 * FILE_ATTRIBUTE_SYSTEM This attribute cannot be set.
 *
 * Not all file systems support all attributes.
 */
WINBASEAPI BOOL WINAPI SetFileAttributesW (LPCWSTR lpszName, DWORD dwAttributes);

/**
 * This function moves the file pointer of an open file. A remote application interface (RAPI)
 * version of this function exists, and it is called CeSetFilePointer.
 *
 * @param hFile [in] Handle to the file whose file pointer is to be moved. The file handle must have
 *   been created with GENERIC_READ or GENERIC_WRITE access to the file.
 * @param lDistanceToMove Low-order 32 bits of a signed value that specifies the number of bytes to
 *   move the file pointer. If lpDistanceToMoveHigh is not NULL, lpDistanceToMoveHigh and
 *   lDistanceToMove form a single 64-bit signed value that specifies the distance to move. If
 *   lpDistanceToMoveHigh is NULL, lDistanceToMove is a 32-bit signed value. A positive value for
 *   lDistanceToMove moves the file pointer forward in the file, and a negative value moves the file
 *   pointer backward.
 * @param lpDistanceToMoveHigh [in] Pointer to the high-order 32 bits of the signed 64-bit distance
 *   to move. If you do not need the high-order 32 bits, this pointer can be NULL. When non-NULL, this
 *   parameter also receives the high-order DWORD of the new value of the file pointer. For more
 *   information, see the Remarks section later in this topic.
 * @param dwMoveMethod [in] Specifies the starting point for the file pointer move. This parameter
 *   can be one of the following values. Value Description FILE_BEGIN The starting point is zero or
 *   the beginning of the file. FILE_CURRENT The starting point is the current value of the file
 *   pointer. FILE_END The starting point is the current end-of-file position.
 *
 * @return The low-order DWORD of the new file pointer indicates success and that
 *   lpDistanceToMoveHigh is NULL. If lpDistanceToMoveHigh is not NULL, the function returns the low
 *   order DWORD of the new file pointer, and puts the high-order DWORD of the new file pointer into
 *   the LONG pointed to by that parameter. If the function fails and lpDistanceToMoveHigh is NULL,
 *   the return value is 0xFFFFFFFF. To get extended error information, call GetLastError. If the
 *   function fails, and lpDistanceToMoveHigh is non-NULL, the return value is 0xFFFFFFFF. However,
 *   because 0xFFFFFFFF is a valid value for the low-order DWORD of the new file pointer, you must
 *   check GetLastError to determine whether an error occurred. If an error occurred, GetLastError
 *   returns a value other than NO_ERROR. For a code example that illustrates this point, see the
 *   Remarks section later in this topic. If the new file pointer would have been a negative value,
 *   the function fails, the file pointer is not moved, and the code returned by GetLastError is
 *   ERROR_NEGATIVE_SEEK.
 *
 * You cannot use the SetFilePointer function with a handle to a nonseeking such as communications
 * device.
 *
 * You can use the SetFilePointer function to query the current file pointer position. To do this,
 * specify a move method of FILE_CURRENT and a distance of zero.
 *
 * You should be careful when setting the file pointer in a multithreaded application. For example,
 * an application whose threads share a file handle, update the file pointer, and read from the file
 * must protect this sequence by using a critical section object or mutex object. For more
 * information about these objects, see Working with Processes and Threads.
 *
 * It is not an error to set the file pointer to a position beyond the end of the file. The size of
 * the file does not increase until you call the SetEndOfFile or WriteFile function. A write
 * operation increases the size of the file to the file pointer position plus the size of the buffer
 * written, leaving the intervening bytes uninitialized.
 *
 * If the return value is 0xFFFFFFFF and if lpDistanceToMoveHigh is non-NULL, an application must
 * call GetLastError to determine whether the function has succeeded or failed. The following sample
 * code illustrates this point:
 *
 *     //
 *     // Case One: calling the function with lpDistanceToMoveHigh == NULL
 *
 *     // Try to move hFile's file pointer some distance
 *     dwPtr = SetFilePointer (hFile, lDistance, NULL, FILE_BEGIN) ;
 *
 *     if (dwPtr == 0xFFFFFFFF) // Test for failure
 *     {
 *      // Obtain the error code
 *      dwError = GetLastError() ;
 *
 *      // Deal with failure
 *      // . . .
 *
 *     } // End of error handler
 *
 *
 *     //
 *     // Case Two: calling the function with lpDistanceToMoveHigh != NULL
 *
 *     // Try to move hFile's file pointer some huge distance
 *     dwPtrLow = SetFilePointer (hFile, lDistLow, & lDistHigh, FILE_BEGIN) ;
 *
 *     // Test for failure
 *     if (dwPtrLow == 0xFFFFFFFF && (dwError = GetLastError()) != NO_ERROR )
 *     {
 *      // Deal with failure
 *      // . . .
 *
 *     } // End of error handler
 *
 * The parameter lpDistanceToMoveHigh is used to manipulate huge files. If it is set to NULL, then
 * lDistanceToMove has a maximum value of 2^31-2, or 2 gigabytes less two. This is because all file
 * pointer values are signed values. Therefore if there is even a small chance that the file will
 * grow to that size, you should treat the file as a huge file and work with 64-bit file pointers.
 *
 * If lpDistanceToMoveHigh is not NULL, then lpDistanceToMoveHigh and lDistanceToMove form a single
 * 64-bit signed value. The lDistanceToMove parameter is treated as the low-order 32 bits of the
 * value, and lpDistanceToMoveHigh as the upper 32 bits. Thus, lpDistanceToMoveHigh is a sign
 * extension of lDistanceToMove.
 *
 * To move the file pointer from 0 to 2 gigabytes, lpDistanceToMoveHigh can be either NULL or a sign
 * extension of lDistanceToMove. To move the pointer more than 2 gigabytes, use lpDistanceToMoveHigh
 * and lDistanceToMove as a single 64-bit quantity. For example, to move in the range from 2
 * gigabytes to 4 gigabytes, set the contents of lpDistanceToMoveHigh to zero, or to -1 for a
 * negative sign extension of lDistanceToMove.
 *
 * To work with 64-bit file pointers, you can declare a LONG, treat it as the upper half of the
 * 64-bit file pointer, and pass its address in lpDistanceToMoveHigh. This means you have to treat
 * two different variables as a logical unit, which is error-prone. The problems can be ameliorated
 * by using the LARGE_INTEGER structure to create a 64-bit value and passing the two 32-bit values
 * by means of the appropriate elements of the union.
 *
 * It is conceptually simpler and better design to use a function to hide the interface to
 * SetFilePointer. To do so, use something like this:
 *
 *     __int64 myFileSeek (HANDLE hf, __int64 distance, DWORD MoveMethod)
 *     {
 *      LARGE_INTEGER li;
 *
 *      li.QuadPart = distance;
 *
 *      li.LowPart = SetFilePointer (hf, li.LowPart, &li.HighPart, MoveMethod);
 *
 *      if (li.LowPart == 0xFFFFFFFF && GetLastError() != NO_ERROR)
 *      {
 *      li.QuadPart = -1;
 *      }
 *
 *      return li.QuadPart;
 *     }
 *
 * You can use SetFilePointer to determine the length of a file. To do this, use FILE_END for
 * dwMoveMethod and seek to location zero. The file offset returned is the length of the file.
 * However, this practice can have unintended side effects, such as failure to save the current file
 * pointer so that the program can return to that location. It is simpler and safer to use
 * GetFileSize instead.
 */
WINBASEAPI
DWORD
WINAPI
SetFilePointer(
    HANDLE hFile,
    LONG lDistanceToMove,
    PLONG lpDistanceToMoveHigh,
    DWORD dwMoveMethod
    );

/**
 * This function closes the specified search handle. The FindFirstFile and FindNextFile functions
 * use the search handle to locate files with names that match a specified name.
 *
 * @param hFindFile [in] Search handle. This handle must have been previously opened by the
 *   FindFirstFile function.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * After the FindClose function is called, the handle specified by the hFindFile parameter cannot be
 * used in subsequent calls to either the FindNextFile or FindClose function.
 */
WINBASEAPI
BOOL
WINAPI
FindClose(
    HANDLE hFindFile
    );


/**
 * This function retrieves the size, in bytes, of the specified file. A remote application interface
 * (RAPI) version of this function exists, and it is named CeGetFileSize.
 *
 * @param hFile [in] Open handle of the file whose size is being returned. The handle must have been
 *   created with either GENERIC_READ or GENERIC_WRITE access to the file.
 * @param lpFileSizeHigh [out] Pointer to the variable where the high-order word of the file size is
 *   returned. This parameter can be NULL if the application does not require the high-order word.
 *
 * @return The low-order DWORD of the file size indicates success. If lpFileSizeHigh is non-NULL,
 *   the function puts the high-order DWORD of the file size into the variable pointed to by that
 *   parameter. If lpFileSizeHigh is NULL, 0xFFFFFFFF indicates failure. To get extended error
 *   information, call GetLastError. If lpFileSizeHigh is non-NULL, 0xFFFFFFFF indicates failure and
 *   GetLastError returns a value other than NO_ERROR.
 *
 * Note that if the return value is 0xFFFFFFFF and lpFileSizeHigh is non-NULL, an application must
 * call GetLastError to determine whether the function has succeeded or failed. The following sample
 * code illustrates this point:
 *
 *     //
 *     // Case One: calling the function with
 *     //           lpFileSizeHigh == NULL
 *
 *     // Try to obtain hFile's size
 *     dwSize = GetFileSize (hFile, NULL) ;
 *
 *     // If we failed ...
 *     if (dwSize == 0xFFFFFFFF) {
 *
 *         // Obtain the error code.
 *         dwError = GetLastError() ;
 *
 *         // Deal with that failure.
 *         .
 *         .
 *         .
 *
 *         } // End of error handler
 *
 *
 *     //
 *     // Case Two: calling the function with
 *     //           lpFileSizeHigh != NULL
 *
 *     // Try to obtain hFile's huge size.
 *     dwSizeLow = GetFileSize (hFile, & dwSizeHigh) ;
 *
 *     // If we failed ...
 *     if (dwSizeLow == 0xFFFFFFFF
 *         &&
 *         (dwError = GetLastError()) != NO_ERROR ){
 *
 *         // Deal with that failure.
 *         .
 *         .
 *         .
 *
 *         } // End of error handler.
 */
WINBASEAPI
DWORD
WINAPI
GetFileSize(
    HANDLE hFile,
    LPDWORD lpFileSizeHigh
    );

/**
 * This function returns attributes for a specified file or directory. A remote application
 * interface (RAPI) version of this function exists, and it is named CeGetFileAttributes.
 *
 * @param lpFileName [in] Pointer to a null-terminated string that specifies the name of a file or
 *   directory. There is a default string size limit for paths of MAX_PATH characters. This limit is
 *   related to how the GetFileAttributes function parses paths.
 *
 * @return The attributes of the specified file or directory, returned in a DWORD, indicates
 *   success. 0xFFFFFFFF indicates failure. To get extended error information, call GetLastError. The
 *   attributes returned upon success can be one or more of the following values: -
 *   FILE_ATTRIBUTE_ARCHIVE: The file or directory is an archive file or directory. Applications use
 *   this attribute to mark files for backup or removal. - FILE_ATTRIBUTE_COMPRESSED: The file or
 *   directory is compressed. For a file, this means that all of the data in the file is compressed.
 *   For a directory, this means that compression is the default for newly created files and
 *   subdirectories. - FILE_ATTRIBUTE_DIRECTORY: The handle identifies a directory. -
 *   FILE_ATTRIBUTE_ENCRYPTED: The file or directory is encrypted. For a file, this means that all
 *   data streams are encrypted. For a directory, this means that encryption is the default for newly
 *   created files and subdirectories. - FILE_ATTRIBUTE_HIDDEN: The file or directory is hidden. It is
 *   not included in an ordinary directory listing. - FILE_ATTRIBUTE_INROM: This file is an operating
 *   system file stored in ROM. These files are read-only; they cannot be modified. -
 *   FILE_ATTRIBUTE_NORMAL: The file or directory has no other attributes set. This attribute is valid
 *   only if used alone. - FILE_ATTRIBUTE_OFFLINE: The data of the file is not immediately available.
 *   Indicates that the file data has been physically moved to offline storage. -
 *   FILE_ATTRIBUTE_READONLY: The file or directory is read-only. Applications can read the file but
 *   cannot write to it or delete it. In the case of a directory, applications cannot delete it. -
 *   FILE_ATTRIBUTE_REPARSE_POINT: The file has an associated reparse point. -
 *   FILE_ATTRIBUTE_ROMMODULE: This file is an operating system file stored in ROM and executed
 *   directly from ROM, rather than being first copied to RAM. The CreateFile function cannot be used
 *   to access this file, instead the LoadLibrary and CreateProcess functions must be used. -
 *   FILE_ATTRIBUTE_ROMSTATICREF: The file is a DLL module that has a static reference from at least
 *   one other file that is in the modules section of the image. A file having this attribute can not
 *   replace the functionality of the DLL with a RAM copy of the same DLL. A file having this
 *   attribute must also have the FILE_ATTRIBUTE_INROM and FILE_ATTRIBUTE_ROMMODULE attributes. -
 *   FILE_ATTRIBUTE_SPARSE_FILE: The file is a sparse file. - FILE_ATTRIBUTE_SYSTEM: The file or
 *   directory is part of, or is used exclusively by, the operating system. -
 *   FILE_ATTRIBUTE_TEMPORARY: The file is being used for temporary storage. File systems attempt to
 *   keep all of the data in memory for quicker access rather than flushing the data back to mass
 *   storage. A temporary file should be deleted by the application as soon as it is no longer needed.
 *   - FILE_ATTRIBUTE_ROMSTATICREF: The DLL module is statically linked to other modules in ROM. The
 *   functionality of this DLL cannot be replaced by a module with the same name that is in a
 *   different location.
 */
WINBASEAPI
DWORD
WINAPI
GetFileAttributesA(
    LPCSTR lpFileName
    );
/**
 * This function returns attributes for a specified file or directory. A remote application
 * interface (RAPI) version of this function exists, and it is named CeGetFileAttributes.
 *
 * @param lpFileName [in] Pointer to a null-terminated string that specifies the name of a file or
 *   directory. There is a default string size limit for paths of MAX_PATH characters. This limit is
 *   related to how the GetFileAttributes function parses paths.
 *
 * @return The attributes of the specified file or directory, returned in a DWORD, indicates
 *   success. 0xFFFFFFFF indicates failure. To get extended error information, call GetLastError. The
 *   attributes returned upon success can be one or more of the following values: -
 *   FILE_ATTRIBUTE_ARCHIVE: The file or directory is an archive file or directory. Applications use
 *   this attribute to mark files for backup or removal. - FILE_ATTRIBUTE_COMPRESSED: The file or
 *   directory is compressed. For a file, this means that all of the data in the file is compressed.
 *   For a directory, this means that compression is the default for newly created files and
 *   subdirectories. - FILE_ATTRIBUTE_DIRECTORY: The handle identifies a directory. -
 *   FILE_ATTRIBUTE_ENCRYPTED: The file or directory is encrypted. For a file, this means that all
 *   data streams are encrypted. For a directory, this means that encryption is the default for newly
 *   created files and subdirectories. - FILE_ATTRIBUTE_HIDDEN: The file or directory is hidden. It is
 *   not included in an ordinary directory listing. - FILE_ATTRIBUTE_INROM: This file is an operating
 *   system file stored in ROM. These files are read-only; they cannot be modified. -
 *   FILE_ATTRIBUTE_NORMAL: The file or directory has no other attributes set. This attribute is valid
 *   only if used alone. - FILE_ATTRIBUTE_OFFLINE: The data of the file is not immediately available.
 *   Indicates that the file data has been physically moved to offline storage. -
 *   FILE_ATTRIBUTE_READONLY: The file or directory is read-only. Applications can read the file but
 *   cannot write to it or delete it. In the case of a directory, applications cannot delete it. -
 *   FILE_ATTRIBUTE_REPARSE_POINT: The file has an associated reparse point. -
 *   FILE_ATTRIBUTE_ROMMODULE: This file is an operating system file stored in ROM and executed
 *   directly from ROM, rather than being first copied to RAM. The CreateFile function cannot be used
 *   to access this file, instead the LoadLibrary and CreateProcess functions must be used. -
 *   FILE_ATTRIBUTE_ROMSTATICREF: The file is a DLL module that has a static reference from at least
 *   one other file that is in the modules section of the image. A file having this attribute can not
 *   replace the functionality of the DLL with a RAM copy of the same DLL. A file having this
 *   attribute must also have the FILE_ATTRIBUTE_INROM and FILE_ATTRIBUTE_ROMMODULE attributes. -
 *   FILE_ATTRIBUTE_SPARSE_FILE: The file is a sparse file. - FILE_ATTRIBUTE_SYSTEM: The file or
 *   directory is part of, or is used exclusively by, the operating system. -
 *   FILE_ATTRIBUTE_TEMPORARY: The file is being used for temporary storage. File systems attempt to
 *   keep all of the data in memory for quicker access rather than flushing the data back to mass
 *   storage. A temporary file should be deleted by the application as soon as it is no longer needed.
 *   - FILE_ATTRIBUTE_ROMSTATICREF: The DLL module is statically linked to other modules in ROM. The
 *   functionality of this DLL cannot be replaced by a module with the same name that is in a
 *   different location.
 */
WINBASEAPI
DWORD
WINAPI
GetFileAttributesW(
    LPCWSTR lpFileName
    );
#ifdef UNICODE
/**
 * This function returns attributes for a specified file or directory. A remote application
 * interface (RAPI) version of this function exists, and it is named CeGetFileAttributes.
 *
 * @param lpFileName [in] Pointer to a null-terminated string that specifies the name of a file or
 *   directory. There is a default string size limit for paths of MAX_PATH characters. This limit is
 *   related to how the GetFileAttributes function parses paths.
 *
 * @return The attributes of the specified file or directory, returned in a DWORD, indicates
 *   success. 0xFFFFFFFF indicates failure. To get extended error information, call GetLastError. The
 *   attributes returned upon success can be one or more of the following values: -
 *   FILE_ATTRIBUTE_ARCHIVE: The file or directory is an archive file or directory. Applications use
 *   this attribute to mark files for backup or removal. - FILE_ATTRIBUTE_COMPRESSED: The file or
 *   directory is compressed. For a file, this means that all of the data in the file is compressed.
 *   For a directory, this means that compression is the default for newly created files and
 *   subdirectories. - FILE_ATTRIBUTE_DIRECTORY: The handle identifies a directory. -
 *   FILE_ATTRIBUTE_ENCRYPTED: The file or directory is encrypted. For a file, this means that all
 *   data streams are encrypted. For a directory, this means that encryption is the default for newly
 *   created files and subdirectories. - FILE_ATTRIBUTE_HIDDEN: The file or directory is hidden. It is
 *   not included in an ordinary directory listing. - FILE_ATTRIBUTE_INROM: This file is an operating
 *   system file stored in ROM. These files are read-only; they cannot be modified. -
 *   FILE_ATTRIBUTE_NORMAL: The file or directory has no other attributes set. This attribute is valid
 *   only if used alone. - FILE_ATTRIBUTE_OFFLINE: The data of the file is not immediately available.
 *   Indicates that the file data has been physically moved to offline storage. -
 *   FILE_ATTRIBUTE_READONLY: The file or directory is read-only. Applications can read the file but
 *   cannot write to it or delete it. In the case of a directory, applications cannot delete it. -
 *   FILE_ATTRIBUTE_REPARSE_POINT: The file has an associated reparse point. -
 *   FILE_ATTRIBUTE_ROMMODULE: This file is an operating system file stored in ROM and executed
 *   directly from ROM, rather than being first copied to RAM. The CreateFile function cannot be used
 *   to access this file, instead the LoadLibrary and CreateProcess functions must be used. -
 *   FILE_ATTRIBUTE_ROMSTATICREF: The file is a DLL module that has a static reference from at least
 *   one other file that is in the modules section of the image. A file having this attribute can not
 *   replace the functionality of the DLL with a RAM copy of the same DLL. A file having this
 *   attribute must also have the FILE_ATTRIBUTE_INROM and FILE_ATTRIBUTE_ROMMODULE attributes. -
 *   FILE_ATTRIBUTE_SPARSE_FILE: The file is a sparse file. - FILE_ATTRIBUTE_SYSTEM: The file or
 *   directory is part of, or is used exclusively by, the operating system. -
 *   FILE_ATTRIBUTE_TEMPORARY: The file is being used for temporary storage. File systems attempt to
 *   keep all of the data in memory for quicker access rather than flushing the data back to mass
 *   storage. A temporary file should be deleted by the application as soon as it is no longer needed.
 *   - FILE_ATTRIBUTE_ROMSTATICREF: The DLL module is statically linked to other modules in ROM. The
 *   functionality of this DLL cannot be replaced by a module with the same name that is in a
 *   different location.
 */
#define GetFileAttributes  GetFileAttributesW
#else
/**
 * This function returns attributes for a specified file or directory. A remote application
 * interface (RAPI) version of this function exists, and it is named CeGetFileAttributes.
 *
 * @param lpFileName [in] Pointer to a null-terminated string that specifies the name of a file or
 *   directory. There is a default string size limit for paths of MAX_PATH characters. This limit is
 *   related to how the GetFileAttributes function parses paths.
 *
 * @return The attributes of the specified file or directory, returned in a DWORD, indicates
 *   success. 0xFFFFFFFF indicates failure. To get extended error information, call GetLastError. The
 *   attributes returned upon success can be one or more of the following values: -
 *   FILE_ATTRIBUTE_ARCHIVE: The file or directory is an archive file or directory. Applications use
 *   this attribute to mark files for backup or removal. - FILE_ATTRIBUTE_COMPRESSED: The file or
 *   directory is compressed. For a file, this means that all of the data in the file is compressed.
 *   For a directory, this means that compression is the default for newly created files and
 *   subdirectories. - FILE_ATTRIBUTE_DIRECTORY: The handle identifies a directory. -
 *   FILE_ATTRIBUTE_ENCRYPTED: The file or directory is encrypted. For a file, this means that all
 *   data streams are encrypted. For a directory, this means that encryption is the default for newly
 *   created files and subdirectories. - FILE_ATTRIBUTE_HIDDEN: The file or directory is hidden. It is
 *   not included in an ordinary directory listing. - FILE_ATTRIBUTE_INROM: This file is an operating
 *   system file stored in ROM. These files are read-only; they cannot be modified. -
 *   FILE_ATTRIBUTE_NORMAL: The file or directory has no other attributes set. This attribute is valid
 *   only if used alone. - FILE_ATTRIBUTE_OFFLINE: The data of the file is not immediately available.
 *   Indicates that the file data has been physically moved to offline storage. -
 *   FILE_ATTRIBUTE_READONLY: The file or directory is read-only. Applications can read the file but
 *   cannot write to it or delete it. In the case of a directory, applications cannot delete it. -
 *   FILE_ATTRIBUTE_REPARSE_POINT: The file has an associated reparse point. -
 *   FILE_ATTRIBUTE_ROMMODULE: This file is an operating system file stored in ROM and executed
 *   directly from ROM, rather than being first copied to RAM. The CreateFile function cannot be used
 *   to access this file, instead the LoadLibrary and CreateProcess functions must be used. -
 *   FILE_ATTRIBUTE_ROMSTATICREF: The file is a DLL module that has a static reference from at least
 *   one other file that is in the modules section of the image. A file having this attribute can not
 *   replace the functionality of the DLL with a RAM copy of the same DLL. A file having this
 *   attribute must also have the FILE_ATTRIBUTE_INROM and FILE_ATTRIBUTE_ROMMODULE attributes. -
 *   FILE_ATTRIBUTE_SPARSE_FILE: The file is a sparse file. - FILE_ATTRIBUTE_SYSTEM: The file or
 *   directory is part of, or is used exclusively by, the operating system. -
 *   FILE_ATTRIBUTE_TEMPORARY: The file is being used for temporary storage. File systems attempt to
 *   keep all of the data in memory for quicker access rather than flushing the data back to mass
 *   storage. A temporary file should be deleted by the application as soon as it is no longer needed.
 *   - FILE_ATTRIBUTE_ROMSTATICREF: The DLL module is statically linked to other modules in ROM. The
 *   functionality of this DLL cannot be replaced by a module with the same name that is in a
 *   different location.
 */
#define GetFileAttributes  GetFileAttributesA
#endif // !UNICODE

/**
 * This structure contains information retrieved by the GetFileInformationByHandle function.
 */
typedef struct _BY_HANDLE_FILE_INFORMATION {
    /**
     * Specifies file attributes. It can be one or more of the following values: Value Description
     * FILE_ATTRIBUTE_ARCHIVE The file or directory is an archive file. Applications use this attribute
     * to mark files for backup or removal. FILE_ATTRIBUTE_COMPRESSED The file or directory is
     * compressed. For a file, this means that all of the data in the file is compressed. For a
     * directory, this means that compression is the default for newly created files and subdirectories.
     * FILE_ATTRIBUTE_DIRECTORY The handle identifies a directory. FILE_ATTRIBUTE_ENCRYPTED The file or
     * directory is encrypted. For a file, this means that all of the data streams are encrypted. For a
     * directory, this means that encryption is the default for newly created files and directories.
     * FILE_ATTRIBUTE_HIDDEN The file or directory is hidden. It is not included in an ordinary
     * directory listing. FILE_ATTRIBUTE_INROM This file is an operating system file stored in ROM.
     * These files are read-only; they cannot be modified. FILE_ATTRIBUTE_NORMAL The file has no other
     * attributes. This attribute is valid only if used alone. FILE_ATTRIBUTE_OFFLINE The file data is
     * not immediately available. Indicates that the file data has been physically moved to offline
     * storage. FILE_ATTRIBUTE_READONLY The file or directory is read-only. Applications can read the
     * file but cannot write to it or delete it. In the case of a directory, applications cannot delete
     * it. FILE_ATTRIBUTE_REPARSE_POINT The file has an associated reparse point.
     * FILE_ATTRIBUTE_ROMMODULE This file is an operating system file stored in ROM, designed to execute
     * in place. In other words, code from this file is executed directly from ROM, rather than being
     * first copied to RAM. The CreateFile function cannot be used to access this file, instead the
     * LoadLibrary and CreateProcess functions must be used. FILE_ATTRIBUTE_ROMSTATICREF The DLL module
     * is statically linked to another module in the ROM file system. This prevents the DLL module from
     * being replaced by a RAM version of the DLL. FILE_ATTRIBUTE_SPARSE_FILE The file is a sparse file.
     * FILE_ATTRIBUTE_SYSTEM The file or directory is part of the operating system or is used
     * exclusively by the operating system. FILE_ATTRIBUTE_TEMPORARY The file is being used for
     * temporary storage. File systems attempt to keep all the data in memory for quicker access, rather
     * than flushing the data back to mass storage. A temporary file should be deleted by the
     * application as soon as it is no longer needed.
     */
    DWORD dwFileAttributes;
    /**
     * Specifies the time the file was created. If the underlying file system does not support this time
     * member, ftCreationTime is zero.
     */
    FILETIME ftCreationTime;
    /**
     * Specifies the time the file was last accessed. If the underlying file system does not support
     * this time member, ftLastAccessTime is zero.
     */
    FILETIME ftLastAccessTime;
    /**
     * Specifies the last time the file was written to.
     */
    FILETIME ftLastWriteTime;
    /**
     * Specifies the serial number of the volume that contains the file.
     */
    DWORD dwVolumeSerialNumber;
    /**
     * Specifies the high-order word of the file size.
     */
    DWORD nFileSizeHigh;
    /**
     * Specifies the low-order word of the file size.
     */
    DWORD nFileSizeLow;
    /**
     * Specifies the number of links to this file. For the FAT file system this member is always 1. For
     * NTFS, it may be more than 1.
     */
    DWORD nNumberOfLinks;
    /**
     * Specifies the high-order word of a unique identifier associated with the file.
     */
    DWORD nFileIndexHigh;
    /**
     * Specifies the low-order word of a unique identifier associated with the file. This identifier and
     * the volume serial number uniquely identify a file. This number may change when the system is
     * restarted or when the file is opened. After a process opens a file, the identifier is constant
     * until the file is closed. An application can use this identifier and the volume serial number to
     * determine whether two handles refer to the same file.
     */
    DWORD nFileIndexLow;
	DWORD dwOID;
} BY_HANDLE_FILE_INFORMATION, *PBY_HANDLE_FILE_INFORMATION, *LPBY_HANDLE_FILE_INFORMATION;

/**
 * This function retrieves information about the specified file.
 *
 * @param hFile [in] Handle to the file that you want to obtain information about. This handle
 *   should not be a pipe handle. The GetFileInformationByHandle function does not work with pipe
 *   handles.
 * @param lpFileInformation [out] Pointer to a BY_HANDLE_FILE_INFORMATION structure that receives
 *   the file information. The structure can be used in subsequent calls to GetFileInformationByHandle
 *   to refer to the information about the file.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * Depending on the underlying network components of the operating system and the type of server
 * connected to, the GetFileInformationByHandle function may fail, return partial information, or
 * full information for the specified file. In general, you should not use
 * GetFileInformationByHandle unless your application is intended to be run on a limited set of
 * operating system configurations.
 */
WINBASEAPI
BOOL
WINAPI
GetFileInformationByHandle(
    HANDLE hFile,
    LPBY_HANDLE_FILE_INFORMATION lpFileInformation
	);

// @CESYSGEN ENDIF

/**
 * This function suspends the execution of the current thread for a specified interval.
 *
 * @param dwMilliseconds Specifies the time, in milliseconds, for which to suspend execution. A
 *   value of zero causes the thread to relinquish the remainder of its time slice to any other thread
 *   of equal priority that is ready to run. If there are no other threads of equal priority ready to
 *   run, the function returns immediately, and the thread continues execution. A value of INFINITE
 *   causes an infinite delay.
 *
 * @return None.
 *
 * A thread can relinquish the remainder of its time slice by calling this function with a sleep
 * time of zero milliseconds.
 *
 * You have to be careful when using Sleep and code that directly or indirectly creates windows. If
 * a thread creates any windows, it must process messages. Message broadcasts are sent to all
 * windows in the system. If you have a thread that uses Sleep with infinite delay, the system will
 * deadlock. Two examples of code that indirectly creates windows are DDE and COM CoInitialize.
 * Therefore, if you have a thread that creates windows, use MsgWaitForMultipleObjects or
 * MsgWaitForMultipleObjectsEx, rather than Sleep.
 */
WINBASEAPI
VOID
WINAPI
Sleep(
    DWORD dwMilliseconds
    );

/**
 * This function creates a named or unnamed mutex object.
 *
 * @param lpMutexAttributes Ignored. Must be NULL.
 * @param bInitialOwner Boolean that specifies the initial owner of the mutex object. If this value
 *   is TRUE and the caller created the mutex, the calling thread obtains ownership of the mutex
 *   object. Otherwise, the calling thread does not obtain ownership of the mutex. To determine if the
 *   caller created the mutex, see the Return Values section.
 * @param lpName Long pointer to a null-terminated string specifying the name of the mutex object.
 *   The name is limited to MAX_PATH characters and can contain any character except the backslash
 *   path-separator character (\). Name comparison is case sensitive. If lpName matches the name of an
 *   existing named mutex object, the bInitialOwner parameter is ignored because it has already been
 *   set by the creating process. If lpName is NULL, the mutex object is created without a name. If
 *   lpName matches the name of an existing event, semaphore, waitable timer, job, or file-mapping
 *   object, the function fails and the GetLastError function returns ERROR_INVALID_HANDLE. This
 *   occurs because these objects share the same name space.
 *
 * @return A handle to the mutex object indicates success. If the named mutex object existed before
 *   the function call, the function returns a handle to the existing object and GetLastError returns
 *   ERROR_ALREADY_EXISTS. Otherwise, the caller created the mutex. NULL indicates failure. To get
 *   extended error information, call GetLastError.
 *
 * The handle returned by CreateMutex has MUTEX_ALL_ACCESS access to the new mutex object and can be
 * used in any function that requires a handle to a mutex object.
 *
 * Any thread of the calling process can specify the mutex-object handle in a call to one of the
 * wait functions. The single-object wait functions return when the state of the specified object is
 * signaled. The multiple-object wait functions can be instructed to return either when any one or
 * when all of the specified objects are signaled. When a wait function returns, the waiting thread
 * is released to continue its execution.
 *
 * The state of a mutex object is signaled when it is not owned by any thread. The creating thread
 * can use the bInitialOwner flag to request immediate ownership of the mutex. Otherwise, a thread
 * must use one of the wait functions to request ownership. When the mutex's state is signaled, one
 * waiting thread is granted ownership, the mutex's state changes to nonsignaled, and the wait
 * function returns. Only one thread can own a mutex at any given time. The owning thread uses the
 * ReleaseMutex function to release its ownership.
 *
 * The thread that owns a mutex can specify the same mutex in repeated wait function calls without
 * blocking its execution. Typically, you would not wait repeatedly for the same mutex, but this
 * mechanism prevents a thread from deadlocking itself while waiting for a mutex that it already
 * owns. However, to release its ownership, the thread must call ReleaseMutex once for each time
 * that the mutex satisfied a wait.
 *
 * Two or more processes can call CreateMutex to create the same named mutex. The first process
 * actually creates the mutex, and subsequent processes open a handle to the existing mutex. This
 * enables multiple processes to get handles of the same mutex, while relieving the user of the
 * responsibility of ensuring that the creating process is started first. When using this technique,
 * you should set the bInitialOwner flag to FALSE; otherwise, it can be difficult to be certain
 * which process has initial ownership.
 *
 * Multiple processes can have handles of the same mutex object, enabling use of the object for
 * interprocess synchronization. The following object-sharing mechanism is available: A process can
 * specify the name of a mutex object in a call to the CreateMutex function.
 *
 * Use the CloseHandle function to close the handle. The system closes the handle automatically when
 * the process terminates. The mutex object is destroyed when its last handle has been closed.
 */
WINBASEAPI
HANDLE
WINAPI
CreateMutexA(
	LPSECURITY_ATTRIBUTES lpsa,
	BOOL bInitialOwner,
	LPCSTR lpName);

/**
 * This function creates a named or unnamed mutex object.
 *
 * @param lpMutexAttributes Ignored. Must be NULL.
 * @param bInitialOwner Boolean that specifies the initial owner of the mutex object. If this value
 *   is TRUE and the caller created the mutex, the calling thread obtains ownership of the mutex
 *   object. Otherwise, the calling thread does not obtain ownership of the mutex. To determine if the
 *   caller created the mutex, see the Return Values section.
 * @param lpName Long pointer to a null-terminated string specifying the name of the mutex object.
 *   The name is limited to MAX_PATH characters and can contain any character except the backslash
 *   path-separator character (\). Name comparison is case sensitive. If lpName matches the name of an
 *   existing named mutex object, the bInitialOwner parameter is ignored because it has already been
 *   set by the creating process. If lpName is NULL, the mutex object is created without a name. If
 *   lpName matches the name of an existing event, semaphore, waitable timer, job, or file-mapping
 *   object, the function fails and the GetLastError function returns ERROR_INVALID_HANDLE. This
 *   occurs because these objects share the same name space.
 *
 * @return A handle to the mutex object indicates success. If the named mutex object existed before
 *   the function call, the function returns a handle to the existing object and GetLastError returns
 *   ERROR_ALREADY_EXISTS. Otherwise, the caller created the mutex. NULL indicates failure. To get
 *   extended error information, call GetLastError.
 *
 * The handle returned by CreateMutex has MUTEX_ALL_ACCESS access to the new mutex object and can be
 * used in any function that requires a handle to a mutex object.
 *
 * Any thread of the calling process can specify the mutex-object handle in a call to one of the
 * wait functions. The single-object wait functions return when the state of the specified object is
 * signaled. The multiple-object wait functions can be instructed to return either when any one or
 * when all of the specified objects are signaled. When a wait function returns, the waiting thread
 * is released to continue its execution.
 *
 * The state of a mutex object is signaled when it is not owned by any thread. The creating thread
 * can use the bInitialOwner flag to request immediate ownership of the mutex. Otherwise, a thread
 * must use one of the wait functions to request ownership. When the mutex's state is signaled, one
 * waiting thread is granted ownership, the mutex's state changes to nonsignaled, and the wait
 * function returns. Only one thread can own a mutex at any given time. The owning thread uses the
 * ReleaseMutex function to release its ownership.
 *
 * The thread that owns a mutex can specify the same mutex in repeated wait function calls without
 * blocking its execution. Typically, you would not wait repeatedly for the same mutex, but this
 * mechanism prevents a thread from deadlocking itself while waiting for a mutex that it already
 * owns. However, to release its ownership, the thread must call ReleaseMutex once for each time
 * that the mutex satisfied a wait.
 *
 * Two or more processes can call CreateMutex to create the same named mutex. The first process
 * actually creates the mutex, and subsequent processes open a handle to the existing mutex. This
 * enables multiple processes to get handles of the same mutex, while relieving the user of the
 * responsibility of ensuring that the creating process is started first. When using this technique,
 * you should set the bInitialOwner flag to FALSE; otherwise, it can be difficult to be certain
 * which process has initial ownership.
 *
 * Multiple processes can have handles of the same mutex object, enabling use of the object for
 * interprocess synchronization. The following object-sharing mechanism is available: A process can
 * specify the name of a mutex object in a call to the CreateMutex function.
 *
 * Use the CloseHandle function to close the handle. The system closes the handle automatically when
 * the process terminates. The mutex object is destroyed when its last handle has been closed.
 */
WINBASEAPI
HANDLE
WINAPI
CreateMutexW(
	LPSECURITY_ATTRIBUTES lpsa,
	BOOL bInitialOwner,
	LPCWSTR lpName);

#ifdef UNICODE
/**
 * This function creates a named or unnamed mutex object.
 *
 * @param lpMutexAttributes Ignored. Must be NULL.
 * @param bInitialOwner Boolean that specifies the initial owner of the mutex object. If this value
 *   is TRUE and the caller created the mutex, the calling thread obtains ownership of the mutex
 *   object. Otherwise, the calling thread does not obtain ownership of the mutex. To determine if the
 *   caller created the mutex, see the Return Values section.
 * @param lpName Long pointer to a null-terminated string specifying the name of the mutex object.
 *   The name is limited to MAX_PATH characters and can contain any character except the backslash
 *   path-separator character (\). Name comparison is case sensitive. If lpName matches the name of an
 *   existing named mutex object, the bInitialOwner parameter is ignored because it has already been
 *   set by the creating process. If lpName is NULL, the mutex object is created without a name. If
 *   lpName matches the name of an existing event, semaphore, waitable timer, job, or file-mapping
 *   object, the function fails and the GetLastError function returns ERROR_INVALID_HANDLE. This
 *   occurs because these objects share the same name space.
 *
 * @return A handle to the mutex object indicates success. If the named mutex object existed before
 *   the function call, the function returns a handle to the existing object and GetLastError returns
 *   ERROR_ALREADY_EXISTS. Otherwise, the caller created the mutex. NULL indicates failure. To get
 *   extended error information, call GetLastError.
 *
 * The handle returned by CreateMutex has MUTEX_ALL_ACCESS access to the new mutex object and can be
 * used in any function that requires a handle to a mutex object.
 *
 * Any thread of the calling process can specify the mutex-object handle in a call to one of the
 * wait functions. The single-object wait functions return when the state of the specified object is
 * signaled. The multiple-object wait functions can be instructed to return either when any one or
 * when all of the specified objects are signaled. When a wait function returns, the waiting thread
 * is released to continue its execution.
 *
 * The state of a mutex object is signaled when it is not owned by any thread. The creating thread
 * can use the bInitialOwner flag to request immediate ownership of the mutex. Otherwise, a thread
 * must use one of the wait functions to request ownership. When the mutex's state is signaled, one
 * waiting thread is granted ownership, the mutex's state changes to nonsignaled, and the wait
 * function returns. Only one thread can own a mutex at any given time. The owning thread uses the
 * ReleaseMutex function to release its ownership.
 *
 * The thread that owns a mutex can specify the same mutex in repeated wait function calls without
 * blocking its execution. Typically, you would not wait repeatedly for the same mutex, but this
 * mechanism prevents a thread from deadlocking itself while waiting for a mutex that it already
 * owns. However, to release its ownership, the thread must call ReleaseMutex once for each time
 * that the mutex satisfied a wait.
 *
 * Two or more processes can call CreateMutex to create the same named mutex. The first process
 * actually creates the mutex, and subsequent processes open a handle to the existing mutex. This
 * enables multiple processes to get handles of the same mutex, while relieving the user of the
 * responsibility of ensuring that the creating process is started first. When using this technique,
 * you should set the bInitialOwner flag to FALSE; otherwise, it can be difficult to be certain
 * which process has initial ownership.
 *
 * Multiple processes can have handles of the same mutex object, enabling use of the object for
 * interprocess synchronization. The following object-sharing mechanism is available: A process can
 * specify the name of a mutex object in a call to the CreateMutex function.
 *
 * Use the CloseHandle function to close the handle. The system closes the handle automatically when
 * the process terminates. The mutex object is destroyed when its last handle has been closed.
 */
#define CreateMutex  CreateMutexW
#else
/**
 * This function creates a named or unnamed mutex object.
 *
 * @param lpMutexAttributes Ignored. Must be NULL.
 * @param bInitialOwner Boolean that specifies the initial owner of the mutex object. If this value
 *   is TRUE and the caller created the mutex, the calling thread obtains ownership of the mutex
 *   object. Otherwise, the calling thread does not obtain ownership of the mutex. To determine if the
 *   caller created the mutex, see the Return Values section.
 * @param lpName Long pointer to a null-terminated string specifying the name of the mutex object.
 *   The name is limited to MAX_PATH characters and can contain any character except the backslash
 *   path-separator character (\). Name comparison is case sensitive. If lpName matches the name of an
 *   existing named mutex object, the bInitialOwner parameter is ignored because it has already been
 *   set by the creating process. If lpName is NULL, the mutex object is created without a name. If
 *   lpName matches the name of an existing event, semaphore, waitable timer, job, or file-mapping
 *   object, the function fails and the GetLastError function returns ERROR_INVALID_HANDLE. This
 *   occurs because these objects share the same name space.
 *
 * @return A handle to the mutex object indicates success. If the named mutex object existed before
 *   the function call, the function returns a handle to the existing object and GetLastError returns
 *   ERROR_ALREADY_EXISTS. Otherwise, the caller created the mutex. NULL indicates failure. To get
 *   extended error information, call GetLastError.
 *
 * The handle returned by CreateMutex has MUTEX_ALL_ACCESS access to the new mutex object and can be
 * used in any function that requires a handle to a mutex object.
 *
 * Any thread of the calling process can specify the mutex-object handle in a call to one of the
 * wait functions. The single-object wait functions return when the state of the specified object is
 * signaled. The multiple-object wait functions can be instructed to return either when any one or
 * when all of the specified objects are signaled. When a wait function returns, the waiting thread
 * is released to continue its execution.
 *
 * The state of a mutex object is signaled when it is not owned by any thread. The creating thread
 * can use the bInitialOwner flag to request immediate ownership of the mutex. Otherwise, a thread
 * must use one of the wait functions to request ownership. When the mutex's state is signaled, one
 * waiting thread is granted ownership, the mutex's state changes to nonsignaled, and the wait
 * function returns. Only one thread can own a mutex at any given time. The owning thread uses the
 * ReleaseMutex function to release its ownership.
 *
 * The thread that owns a mutex can specify the same mutex in repeated wait function calls without
 * blocking its execution. Typically, you would not wait repeatedly for the same mutex, but this
 * mechanism prevents a thread from deadlocking itself while waiting for a mutex that it already
 * owns. However, to release its ownership, the thread must call ReleaseMutex once for each time
 * that the mutex satisfied a wait.
 *
 * Two or more processes can call CreateMutex to create the same named mutex. The first process
 * actually creates the mutex, and subsequent processes open a handle to the existing mutex. This
 * enables multiple processes to get handles of the same mutex, while relieving the user of the
 * responsibility of ensuring that the creating process is started first. When using this technique,
 * you should set the bInitialOwner flag to FALSE; otherwise, it can be difficult to be certain
 * which process has initial ownership.
 *
 * Multiple processes can have handles of the same mutex object, enabling use of the object for
 * interprocess synchronization. The following object-sharing mechanism is available: A process can
 * specify the name of a mutex object in a call to the CreateMutex function.
 *
 * Use the CloseHandle function to close the handle. The system closes the handle automatically when
 * the process terminates. The mutex object is destroyed when its last handle has been closed.
 */
#define CreateMutex  CreateMutexA
#endif // !UNICODE

/**
 * This function creates a named or an unnamed event object.
 *
 * @param lpEventAttributes Ignored. Must be NULL.
 * @param bManualReset Boolean that specifies whether a manual-reset or auto-reset event object is
 *   created. If TRUE, then you must use the ResetEvent function to manually reset the state to
 *   nonsignaled. If FALSE, the system automatically resets the state to nonsignaled after a single
 *   waiting thread has been released.
 * @param bInitialState Boolean that specifies the initial state of the event object. If TRUE, the
 *   initial state is signaled; otherwise, it is nonsignaled.
 * @param lpName Pointer to a null-terminated string that specifies the name of the event object.
 *   The name is limited to MAX_PATH characters and can contain any character except the backslash
 *   path-separator character (\). Name comparison is case sensitive. If lpName matches the name of an
 *   existing named event object, the bManualReset and bInitialState parameters are ignored because
 *   they have already been set by the creating process. If lpName is NULL, the event object is
 *   created without a name. If lpName matches the name of an existing semaphore, mutex, waitable
 *   timer, job, or file-mapping object, the function fails and the GetLastError function returns
 *   ERROR_INVALID_HANDLE. This occurs because these objects share the same name space.
 *
 * @return A handle to the event object indicates success. If the named event object existed before
 *   the function call, the function returns a handle to the existing object and GetLastError returns
 *   ERROR_ALREADY_EXISTS. NULL indicates failure. To get extended error information, call
 *   GetLastError.
 *
 * The handle returned by CreateEvent has EVENT_ALL_ACCESS access to the new event object and can be
 * used in any function that requires a handle to an event object.
 *
 * Any thread of the calling process can specify the event-object handle in a call to one of the
 * wait functions. The single-object wait functions return when the state of the specified object is
 * signaled. The multiple-object wait functions can be instructed to return either when any one of
 * the specified objects are signaled. When a wait function returns, the waiting thread is released
 * to continue its execution.
 *
 * The initial state of the event object is specified by the bInitialState parameter. Use the
 * SetEvent function to set the state of an event object to signaled. Use the ResetEvent function to
 * reset the state of an event object to nonsignaled.
 *
 * When the state of a manual-reset event object is signaled, it remains signaled until it is
 * explicitly reset to nonsignaled by the ResetEvent function. Any number of waiting threads, or
 * threads that subsequently begin wait operations for the specified event object, can be released
 * while the object's state is signaled.
 *
 * When the state of an auto-reset event object is signaled, it remains signaled until a single
 * waiting thread is released; the system then automatically resets the state to nonsignaled. If no
 * threads are waiting, the event object's state remains signaled.
 *
 * Multiple processes can have handles of the same event object, enabling use of the object for
 * interprocess synchronization. The following object-sharing mechanism is available: a process can
 * specify the name of an event object in a call to the CreateEvent function.
 *
 * Use the CloseHandle function to close the handle. The system closes the handle automatically when
 * the process terminates. The event object is destroyed when its last handle has been closed.
 */
WINBASEAPI
HANDLE
WINAPI
CreateEventA(
    LPSECURITY_ATTRIBUTES lpEventAttributes,
    BOOL bManualReset,
    BOOL bInitialState,
    LPCSTR lpName
    );

/**
 * This function creates a named or an unnamed event object.
 *
 * @param lpEventAttributes Ignored. Must be NULL.
 * @param bManualReset Boolean that specifies whether a manual-reset or auto-reset event object is
 *   created. If TRUE, then you must use the ResetEvent function to manually reset the state to
 *   nonsignaled. If FALSE, the system automatically resets the state to nonsignaled after a single
 *   waiting thread has been released.
 * @param bInitialState Boolean that specifies the initial state of the event object. If TRUE, the
 *   initial state is signaled; otherwise, it is nonsignaled.
 * @param lpName Pointer to a null-terminated string that specifies the name of the event object.
 *   The name is limited to MAX_PATH characters and can contain any character except the backslash
 *   path-separator character (\). Name comparison is case sensitive. If lpName matches the name of an
 *   existing named event object, the bManualReset and bInitialState parameters are ignored because
 *   they have already been set by the creating process. If lpName is NULL, the event object is
 *   created without a name. If lpName matches the name of an existing semaphore, mutex, waitable
 *   timer, job, or file-mapping object, the function fails and the GetLastError function returns
 *   ERROR_INVALID_HANDLE. This occurs because these objects share the same name space.
 *
 * @return A handle to the event object indicates success. If the named event object existed before
 *   the function call, the function returns a handle to the existing object and GetLastError returns
 *   ERROR_ALREADY_EXISTS. NULL indicates failure. To get extended error information, call
 *   GetLastError.
 *
 * The handle returned by CreateEvent has EVENT_ALL_ACCESS access to the new event object and can be
 * used in any function that requires a handle to an event object.
 *
 * Any thread of the calling process can specify the event-object handle in a call to one of the
 * wait functions. The single-object wait functions return when the state of the specified object is
 * signaled. The multiple-object wait functions can be instructed to return either when any one of
 * the specified objects are signaled. When a wait function returns, the waiting thread is released
 * to continue its execution.
 *
 * The initial state of the event object is specified by the bInitialState parameter. Use the
 * SetEvent function to set the state of an event object to signaled. Use the ResetEvent function to
 * reset the state of an event object to nonsignaled.
 *
 * When the state of a manual-reset event object is signaled, it remains signaled until it is
 * explicitly reset to nonsignaled by the ResetEvent function. Any number of waiting threads, or
 * threads that subsequently begin wait operations for the specified event object, can be released
 * while the object's state is signaled.
 *
 * When the state of an auto-reset event object is signaled, it remains signaled until a single
 * waiting thread is released; the system then automatically resets the state to nonsignaled. If no
 * threads are waiting, the event object's state remains signaled.
 *
 * Multiple processes can have handles of the same event object, enabling use of the object for
 * interprocess synchronization. The following object-sharing mechanism is available: a process can
 * specify the name of an event object in a call to the CreateEvent function.
 *
 * Use the CloseHandle function to close the handle. The system closes the handle automatically when
 * the process terminates. The event object is destroyed when its last handle has been closed.
 */
WINBASEAPI
HANDLE
WINAPI
CreateEventW(
    LPSECURITY_ATTRIBUTES lpEventAttributes,
    BOOL bManualReset,
    BOOL bInitialState,
    LPCWSTR lpName
    );
#ifdef UNICODE
/**
 * This function creates a named or an unnamed event object.
 *
 * @param lpEventAttributes Ignored. Must be NULL.
 * @param bManualReset Boolean that specifies whether a manual-reset or auto-reset event object is
 *   created. If TRUE, then you must use the ResetEvent function to manually reset the state to
 *   nonsignaled. If FALSE, the system automatically resets the state to nonsignaled after a single
 *   waiting thread has been released.
 * @param bInitialState Boolean that specifies the initial state of the event object. If TRUE, the
 *   initial state is signaled; otherwise, it is nonsignaled.
 * @param lpName Pointer to a null-terminated string that specifies the name of the event object.
 *   The name is limited to MAX_PATH characters and can contain any character except the backslash
 *   path-separator character (\). Name comparison is case sensitive. If lpName matches the name of an
 *   existing named event object, the bManualReset and bInitialState parameters are ignored because
 *   they have already been set by the creating process. If lpName is NULL, the event object is
 *   created without a name. If lpName matches the name of an existing semaphore, mutex, waitable
 *   timer, job, or file-mapping object, the function fails and the GetLastError function returns
 *   ERROR_INVALID_HANDLE. This occurs because these objects share the same name space.
 *
 * @return A handle to the event object indicates success. If the named event object existed before
 *   the function call, the function returns a handle to the existing object and GetLastError returns
 *   ERROR_ALREADY_EXISTS. NULL indicates failure. To get extended error information, call
 *   GetLastError.
 *
 * The handle returned by CreateEvent has EVENT_ALL_ACCESS access to the new event object and can be
 * used in any function that requires a handle to an event object.
 *
 * Any thread of the calling process can specify the event-object handle in a call to one of the
 * wait functions. The single-object wait functions return when the state of the specified object is
 * signaled. The multiple-object wait functions can be instructed to return either when any one of
 * the specified objects are signaled. When a wait function returns, the waiting thread is released
 * to continue its execution.
 *
 * The initial state of the event object is specified by the bInitialState parameter. Use the
 * SetEvent function to set the state of an event object to signaled. Use the ResetEvent function to
 * reset the state of an event object to nonsignaled.
 *
 * When the state of a manual-reset event object is signaled, it remains signaled until it is
 * explicitly reset to nonsignaled by the ResetEvent function. Any number of waiting threads, or
 * threads that subsequently begin wait operations for the specified event object, can be released
 * while the object's state is signaled.
 *
 * When the state of an auto-reset event object is signaled, it remains signaled until a single
 * waiting thread is released; the system then automatically resets the state to nonsignaled. If no
 * threads are waiting, the event object's state remains signaled.
 *
 * Multiple processes can have handles of the same event object, enabling use of the object for
 * interprocess synchronization. The following object-sharing mechanism is available: a process can
 * specify the name of an event object in a call to the CreateEvent function.
 *
 * Use the CloseHandle function to close the handle. The system closes the handle automatically when
 * the process terminates. The event object is destroyed when its last handle has been closed.
 */
#define CreateEvent  CreateEventW
#else
/**
 * This function creates a named or an unnamed event object.
 *
 * @param lpEventAttributes Ignored. Must be NULL.
 * @param bManualReset Boolean that specifies whether a manual-reset or auto-reset event object is
 *   created. If TRUE, then you must use the ResetEvent function to manually reset the state to
 *   nonsignaled. If FALSE, the system automatically resets the state to nonsignaled after a single
 *   waiting thread has been released.
 * @param bInitialState Boolean that specifies the initial state of the event object. If TRUE, the
 *   initial state is signaled; otherwise, it is nonsignaled.
 * @param lpName Pointer to a null-terminated string that specifies the name of the event object.
 *   The name is limited to MAX_PATH characters and can contain any character except the backslash
 *   path-separator character (\). Name comparison is case sensitive. If lpName matches the name of an
 *   existing named event object, the bManualReset and bInitialState parameters are ignored because
 *   they have already been set by the creating process. If lpName is NULL, the event object is
 *   created without a name. If lpName matches the name of an existing semaphore, mutex, waitable
 *   timer, job, or file-mapping object, the function fails and the GetLastError function returns
 *   ERROR_INVALID_HANDLE. This occurs because these objects share the same name space.
 *
 * @return A handle to the event object indicates success. If the named event object existed before
 *   the function call, the function returns a handle to the existing object and GetLastError returns
 *   ERROR_ALREADY_EXISTS. NULL indicates failure. To get extended error information, call
 *   GetLastError.
 *
 * The handle returned by CreateEvent has EVENT_ALL_ACCESS access to the new event object and can be
 * used in any function that requires a handle to an event object.
 *
 * Any thread of the calling process can specify the event-object handle in a call to one of the
 * wait functions. The single-object wait functions return when the state of the specified object is
 * signaled. The multiple-object wait functions can be instructed to return either when any one of
 * the specified objects are signaled. When a wait function returns, the waiting thread is released
 * to continue its execution.
 *
 * The initial state of the event object is specified by the bInitialState parameter. Use the
 * SetEvent function to set the state of an event object to signaled. Use the ResetEvent function to
 * reset the state of an event object to nonsignaled.
 *
 * When the state of a manual-reset event object is signaled, it remains signaled until it is
 * explicitly reset to nonsignaled by the ResetEvent function. Any number of waiting threads, or
 * threads that subsequently begin wait operations for the specified event object, can be released
 * while the object's state is signaled.
 *
 * When the state of an auto-reset event object is signaled, it remains signaled until a single
 * waiting thread is released; the system then automatically resets the state to nonsignaled. If no
 * threads are waiting, the event object's state remains signaled.
 *
 * Multiple processes can have handles of the same event object, enabling use of the object for
 * interprocess synchronization. The following object-sharing mechanism is available: a process can
 * specify the name of an event object in a call to the CreateEvent function.
 *
 * Use the CloseHandle function to close the handle. The system closes the handle automatically when
 * the process terminates. The event object is destroyed when its last handle has been closed.
 */
#define CreateEvent  CreateEventA
#endif // !UNICODE

/**
 * This function releases ownership of the specified mutex object.
 *
 * @param hMutex [in] Handle to the mutex object. The CreateMutex function returns this handle.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * The ReleaseMutex function fails if the calling thread does not own the mutex object.
 *
 * A thread gets ownership of a mutex by specifying a handle to the mutex in one of the wait
 * functions. The thread that creates a mutex object can also get immediate ownership without using
 * one of the wait functions. When the owning thread no longer needs to own the mutex object, it
 * calls the ReleaseMutex function.
 *
 * While a thread has ownership of a mutex, it can specify the same mutex in additional
 * wait-function calls without blocking its execution. This prevents a thread from deadlocking
 * itself while waiting for a mutex that it already owns. However, to release its ownership, the
 * thread must call ReleaseMutex once for each time that the mutex satisfied a wait.
 */
WINBASEAPI
BOOL
WINAPI
ReleaseMutex(
    HANDLE hMutex
    );

/**
 * This function returns when the specified object is in the signaled state or when the time-out
 * interval elapses.
 *
 * @param hHandle Handle to the object. For a list of the object types whose handles can be
 *   specified, see the following Remarks section.
 * @param dwMilliseconds Specifies the time-out interval, in milliseconds. The function returns if
 *   the interval elapses, even if the object's state is nonsignaled. If dwMilliseconds is zero, the
 *   function tests the object's state and returns immediately. If dwMilliseconds is INFINITE, the
 *   function's time-out interval never elapses.
 *
 * @return If the function succeeds, the return value indicates the event that caused the function
 *   to return. This value can be one of the following. Value Description WAIT_ABANDONED The specified
 *   object is a mutex object that was not released by the thread that owned the mutex object before
 *   the owning thread terminated. Ownership of the mutex object is granted to the calling thread, and
 *   the mutex is set to nonsignaled. WAIT_OBJECT_0 The state of the specified object is signaled.
 *   WAIT_TIMEOUT The time-out interval elapsed, and the object's state is nonsignaled. WAIT_FAILED
 *   indicates failure. Waiting on an invalid handle causes WaitForSingleObject to return WAIT_FAILED.
 *   To get extended error information, call GetLastError.
 *
 * Windows CE does not support waiting for semaphores, change notification objects, input, and
 * timers.
 *
 * For Windows CE versions 1.0 and 1.01, this function cannot wait on process or thread handles.
 *
 * The WaitForSingleObject function checks the current state of the specified object. If the
 * object's state is nonsignaled, the calling thread enters an efficient wait state. The thread
 * consumes very little processor time while waiting for the object state to become signaled or the
 * time-out interval to elapse.
 *
 * Before returning, a wait function modifies the state of some types of synchronization objects.
 * Modification occurs only for the object whose signaled state caused the function to return. For
 * example, the count of a semaphore object is decreased by one.
 *
 * The WaitForSingleObject function can wait for the following objects:
 *
 * Event
 *
 * Mutex
 *
 * Process
 *
 * Thread
 *
 * Use caution when calling the wait functions and code that directly or indirectly creates windows.
 * If a thread creates any windows, it must process messages. Message broadcasts are sent to all
 * windows in the system. A thread that uses a wait function with no time-out interval may cause the
 * system to become deadlocked. Two examples of code that indirectly creates windows are DDE and COM
 * CoInitialize. Therefore, if you have a thread that creates windows, use MsgWaitForMultipleObjects
 * or MsgWaitForMultipleObjectsEx, rather than WaitForSingleObject.
 */
WINBASEAPI
DWORD
WINAPI
WaitForSingleObject(
    HANDLE hHandle,
    DWORD dwMilliseconds
    );

/**
 * This function returns when one of the following occurs:
 *
 * @param nCount Specifies the number of object handles in the array pointed to by lpHandles. The
 *   maximum number of object handles is MAXIMUM_WAIT_OBJECTS.
 * @param lpHandles Pointer to an array of object handles. For a list of the object types whose
 *   handles can be specified, see the following Remarks section. The array can contain handles of
 *   objects of different types.
 * @param fWaitAll Specifies the wait type. This parameter must be set to FALSE. This causes
 *   function to return when the state of any one of the objects set to is signaled. The return value
 *   indicates the object whose state caused the function to return.
 * @param dwMilliseconds Specifies the time-out interval, in milliseconds. The function returns if
 *   the interval elapses, even if the conditions specified by the bWaitAll parameter are not met. If
 *   dwMilliseconds is zero, the function tests the states of the specified objects and returns
 *   immediately. If dwMilliseconds is INFINITE, the function's time-out interval never elapses.
 *
 * @return If the function succeeds, the return value indicates the event that caused the function
 *   to return. This value can be one of the following. - WAIT_OBJECT_0 to (WAIT_OBJECT_0 + nCount
 *   -1): The return value minus WAIT_OBJECT_0 indicates the lpHandles array index of the object that
 *   satisfied the wait. If more than one object became signaled during the call, this is the array
 *   index of the signaled object with the smallest index value of all the signaled objects. -
 *   WAIT_ABANDONED_0 to (WAIT_ABANDONED_0 + nCount -1): The return value minus WAIT_ABANDONED_0
 *   indicates the lpHandles array index of an abandoned mutex object that satisfied the wait. -
 *   WAIT_TIMEOUT: The time-out interval elapsed and the condition specified by the fWaitAll parameter
 *   are not satisfied. WAIT_FAILED indicates failure. To get extended error information, call
 *   GetLastError.
 *
 * Windows CE does not support waiting for semaphores, change notification objects, input, and
 * timers.
 *
 * For Windows CE versions 1.0 and 1.01, this function cannot wait on process or thread handles.
 *
 * The WaitForMultipleObjects function determines whether the wait criteria have been met. If the
 * criteria have not been met, the calling thread enters an efficient wait state, consuming very
 * little processor time while waiting for the criteria to be met.
 *
 * Before returning, a wait function modifies the state of some types of synchronization objects.
 * Modification occurs only for the object or objects whose signaled state caused the function to
 * return. When fWaitAll is FALSE, and multiple objects are in the signaled state, the function
 * chooses one of the objects to satisfy the wait; the states of the objects not selected are
 * unaffected.
 *
 * The WaitForMultipleObjects function can specify handles of any of the following object types in
 * the lpHandles array:
 *
 * Event
 *
 * Mutex
 *
 * Process
 *
 * Thread
 *
 * Use caution when calling the wait functions and code that directly or indirectly creates windows.
 * If a thread creates any windows, it must process messages. Message broadcasts are sent to all
 * windows in the system. A thread that uses a wait function with no time-out interval may cause the
 * system to become deadlocked. Two examples of code that indirectly creates windows are DDE and COM
 * CoInitialize. Therefore, if you have a thread that creates windows, use MsgWaitForMultipleObjects
 * or MsgWaitForMultipleObjectsEx, rather than WaitForMultipleObjects.
 */
WINBASEAPI
DWORD
WINAPI
WaitForMultipleObjects(
	DWORD cObjects,
	CONST HANDLE *lphObjects,
	BOOL fWaitAll,
	DWORD dwTimeout
	);

/**
 * This function retrieves the termination status of the specified thread.
 *
 * @param hThread Handle to the thread.
 * @param lpExitCode Pointer to a 32-bit variable to receive the thread termination status.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * If the specified thread has not terminated, the termination status returned is STILL_ACTIVE. If
 * the thread has terminated, the termination status returned may be one of the following:
 *
 * The exit value specified in the ExitThread or TerminateThread function.
 *
 * The return value from the thread function.
 *
 * The exit value of the thread's process.
 */
WINBASEAPI
BOOL
WINAPI
GetExitCodeThread(
    HANDLE hThread,
    LPDWORD lpExitCode
    );

/**
 * This function retrieves the termination status of the specified process.
 *
 * @param hProcess Handle to the process.
 * @param lpExitCode Pointer to a 32-bit variable to receive the process termination status.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * If the specified process has not terminated, the termination status returned is STILL_ACTIVE. If
 * the process has terminated, the termination status returned may be one of the following:
 *
 * The exit value specified in the ExitProcess or TerminateProcess function.
 *
 * The return value from the main or WinMain function of the process.
 *
 * The exception value for an unhandled exception that caused the process to terminate.
 */
WINBASEAPI
BOOL
WINAPI
GetExitCodeProcess(
    HANDLE hProcess,
    LPDWORD lpExitCode
    );

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
DWORD
WINAPI
TlsAlloc(
    VOID
    );

/**
 * This function determines whether the calling process has read access to the memory at the
 * specified address.
 *
 * @param lpfn Pointer to an address in memory.
 *
 * @return Zero indicates that the calling process has read access to the specified memory. Nonzero
 *   indicates that the calling process does not have read access to the specified memory. To get
 *   extended error information, call GetLastError. If the application is compiled as a debugging
 *   version, and the process does not have read access to all bytes in the specified memory range,
 *   the function causes an assertion and breaks into the debugger. Leaving the debugger, the function
 *   continues as usual, and returns a nonzero value This behavior is by design, as a debugging aid.
 *
 * IsBadCodePtr checks the read access only at the specified address and does not guarantee read
 * access to a range of memory.
 *
 * In a preemptive multitasking environment, it is possible for some other thread to change the
 * process's access to the memory being tested. Even when the function indicates that the process
 * has read access to the specified memory, you should use structured exception handling when
 * attempting to access the memory. Use of structured exception handling enables the system to
 * notify the process if an access violation exception occurs, giving the process an opportunity to
 * handle the exception.
 */
WINBASEAPI
BOOL
WINAPI
IsBadCodePtr(
    FARPROC lpfn
    );

/**
 * This function verifies that the calling process has read access to the specified range of memory.
 *
 * @param lp Pointer to the first byte of the memory block.
 * @param ucb Specifies the size, in bytes, of the memory block. If this parameter is zero, the
 *   return value is zero.
 *
 * @return Zero indicates that the calling process has read access to all bytes in the specified
 *   memory range. Nonzero indicates that the calling process does not have read access to all bytes
 *   in the specified memory range. If the application is compiled as a debugging version, and the
 *   process does not have read access to all bytes in the specified memory range, the function causes
 *   an assertion and breaks into the debugger. Leaving the debugger, the function continues as usual,
 *   and returns a nonzero value This behavior is by design, as a debugging aid.
 *
 * If the calling process has read access to some, but not all, of the bytes in the specified memory
 * range, the return value is nonzero.
 *
 * In a preemptive multitasking environment, it is possible for some other thread to change the
 * process's access to the memory being tested. Even when the function indicates that the process
 * has read access to the specified memory, you should use structured exception handling when
 * attempting to access the memory. Use of structured exception handling enables the system to
 * notify the process if an access violation exception occurs, giving the process an opportunity to
 * handle the exception.
 */
WINBASEAPI
BOOL
WINAPI
IsBadReadPtr(
    CONST VOID *lp,
    UINT ucb
    );

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
BOOL
WINAPI
TlsFree(
    DWORD dwTlsIndex
    );

/**
 * This function verifies that the calling process has write access to the specified range of
 * memory.
 *
 * @param lp Pointer to the first byte of the memory block.
 * @param ucb Specifies the size, in bytes, of the memory block. If this parameter is zero, the
 *   return value is zero.
 *
 * @return Zero indicates that the calling process has write access to all bytes in the specified
 *   memory range. Nonzero indicates that the calling process does not have write access to all bytes
 *   in the specified memory range. If the application is compiled as a debugging version, and the
 *   process does not have write access to all bytes in the specified memory range, the function
 *   causes an assertion and breaks into the debugger. Leaving the debugger, the function continues as
 *   usual, and returns a nonzero value This behavior is by design, as a debugging aid.
 *
 * If the calling process has write access to some, but not all, of the bytes in the specified
 * memory range, the return value is nonzero.
 *
 * In a preemptive multitasking environment, it is possible for some other thread to change the
 * process's access to the memory being tested. Even when the function indicates that the process
 * has write access to the specified memory, you should use structured exception handling when
 * attempting to access the memory. Use of structured exception handling enables the system to
 * notify the process if an access violation exception occurs, giving the process an opportunity to
 * handle the exception.
 */
WINBASEAPI
BOOL
WINAPI
IsBadWritePtr(
    LPVOID lp,
    UINT ucb
	);

/**
 * This function returns information about the current system. A remote application interface (RAPI)
 * version of this function exists, and it is named CeGetSystemInfo.
 *
 * @param lpSystemInfo Pointer to a SYSTEM_INFO structure to be filled in by this function.
 *
 * @return None.
 */
WINBASEAPI
VOID
WINAPI
GetSystemInfo(
    LPSYSTEM_INFO lpSystemInfo
    );

/**
 * This function raises an exception in the calling thread.
 *
 * @param dwExceptionCode Specifies the application-defined exception code of the exception being
 *   raised. The filter expression and exception-handler block of an exception handler can use the
 *   GetExceptionCode function to retrieve this value. Note that the system will clear bit 28 of
 *   dwExceptionCode. This bit is a reserved exception bit, used by the system for its own purposes.
 *   For example, after calling the RaiseException function with a dwExceptionCode value of
 *   0xFFFFFFFF, the system displays a message indicating that the exception number is 0xEFFFFFFF.
 * @param dwExceptionFlags Specifies the exception flags. This can be either zero to indicate a
 *   continuable exception, or EXCEPTION_NONCONTINUABLE to indicate a noncontinuable exception. Any
 *   attempt to continue execution after a noncontinuable exception causes the
 *   EXCEPTION_NONCONTINUABLE_EXCEPTION exception.
 * @param nNumberOfArguments Specifies the number of arguments in the lpArguments array. This value
 *   must not exceed EXCEPTION_MAXIMUM_PARAMETERS. This parameter is ignored if lpArguments is NULL.
 * @param lpArguments Long pointer to an array of 32-bit arguments. This parameter can be NULL.
 *   These arguments can contain any application-defined data that needs to be passed to the filter
 *   expression of the exception handler.
 *
 * @return None.
 *
 * The RaiseException function enables a process to use structured exception handling to handle
 * private, software-generated, application-defined exceptions.
 *
 * Raising an exception causes the exception dispatcher to go through the following search for an
 * exception handler:
 *
 * The system first attempts to notify the process's debugger, if any.
 *
 * If the process is not being debugged, or if the associated debugger does not handle the
 * exception, the system attempts to locate a frame-based exception handler by searching the stack
 * frames of the thread in which the exception occurred. The system searches the current stack frame
 * first, then proceeds backward through preceding stack frames.
 *
 * If no frame-based handler can be found, or no frame-based handler handles the exception, the
 * system makes a second attempt to notify the process's debugger.
 *
 * If the process is not being debugged, or if the associated debugger does not handle the
 * exception, the system provides default handling based on the exception type.
 *
 * The values specified in the dwExceptionCode, dwExceptionFlags, nNumberOfArguments, and
 * lpArguments parameters can be retrieved in the filter expression of a try-except frame-based
 * exception handler by calling the GetExceptionInformation function. A debugger can retrieve these
 * values by calling the WaitForDebugEvent function.
 */
WINBASEAPI
VOID
WINAPI
RaiseException(
    DWORD dwExceptionCode,
    DWORD dwExceptionFlags,
    DWORD nNumberOfArguments,
    CONST DWORD *lpArguments
    );

/**
 * This function decrements the reference count of the loaded dynamic-link library (DLL) module.
 * When the reference count reaches zero, the module is unmapped from the address space of the
 * calling process and the handle is no longer valid.
 *
 * @param hLibModule Handle to the loaded library module. The LoadLibrary or GetModuleHandle
 *   function returns this handle.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * Each process maintains a reference count for each loaded library module. This reference count is
 * incremented each time LoadLibrary is called and is decremented each time FreeLibrary is called. A
 * DLL module loaded at process initialization due to load-time dynamic linking has a reference
 * count of one. This count is incremented if the same module is loaded by a call to LoadLibrary.
 *
 * Before unmapping a library module, the system enables the DLL to detach from the process by
 * calling the DLL's DllMain function, if it has one, with the DLL_PROCESS_DETACH value. Doing so
 * gives the DLL an opportunity to clean up resources allocated on behalf of the current process.
 * After the entry-point function returns, the library module is removed from the address space of
 * the current process.
 *
 * It is not safe to call FreeLibrary from DllMain. For more information, see the Remarks section in
 * DllMain.
 *
 * Calling FreeLibrary does not affect other processes using the same library module.
 */
WINBASEAPI
BOOL
WINAPI
FreeLibrary(
    HMODULE hLibModule
    );

#include <windbase.h>

#include <dbgapi.h>

#ifdef UNDER_CE
#include <kfuncs.h>
#ifdef WINCEOEM
#include <pwinbase.h>
#endif
#endif

#define FILE_MAP_WRITE      SECTION_MAP_WRITE
#define FILE_MAP_READ       SECTION_MAP_READ
#define FILE_MAP_ALL_ACCESS SECTION_ALL_ACCESS

// @CESYSGEN IF COREDLL_SERDEV

//
// Serial provider type.
//

#define SP_SERIALCOMM    ((DWORD)0x00000001)

//
// Provider SubTypes
//

#define PST_UNSPECIFIED      ((DWORD)0x00000000)
#define PST_RS232            ((DWORD)0x00000001)
#define PST_PARALLELPORT     ((DWORD)0x00000002)
#define PST_RS422            ((DWORD)0x00000003)
#define PST_RS423            ((DWORD)0x00000004)
#define PST_RS449            ((DWORD)0x00000005)
#define PST_MODEM            ((DWORD)0x00000006)
#define PST_FAX              ((DWORD)0x00000021)
#define PST_SCANNER          ((DWORD)0x00000022)
#define PST_NETWORK_BRIDGE   ((DWORD)0x00000100)
#define PST_LAT              ((DWORD)0x00000101)
#define PST_TCPIP_TELNET     ((DWORD)0x00000102)
#define PST_X25              ((DWORD)0x00000103)


//
// Provider capabilities flags.
//

#define PCF_DTRDSR        ((DWORD)0x0001)
#define PCF_RTSCTS        ((DWORD)0x0002)
#define PCF_RLSD          ((DWORD)0x0004)
#define PCF_PARITY_CHECK  ((DWORD)0x0008)
#define PCF_XONXOFF       ((DWORD)0x0010)
#define PCF_SETXCHAR      ((DWORD)0x0020)
#define PCF_TOTALTIMEOUTS ((DWORD)0x0040)
#define PCF_INTTIMEOUTS   ((DWORD)0x0080)
#define PCF_SPECIALCHARS  ((DWORD)0x0100)
#define PCF_16BITMODE     ((DWORD)0x0200)

//
// Comm provider settable parameters.
//

#define SP_PARITY         ((DWORD)0x0001)
#define SP_BAUD           ((DWORD)0x0002)
#define SP_DATABITS       ((DWORD)0x0004)
#define SP_STOPBITS       ((DWORD)0x0008)
#define SP_HANDSHAKING    ((DWORD)0x0010)
#define SP_PARITY_CHECK   ((DWORD)0x0020)
#define SP_RLSD           ((DWORD)0x0040)

//
// Settable baud rates in the provider.
//

#define BAUD_075          ((DWORD)0x00000001)
#define BAUD_110          ((DWORD)0x00000002)
#define BAUD_134_5        ((DWORD)0x00000004)
#define BAUD_150          ((DWORD)0x00000008)
#define BAUD_300          ((DWORD)0x00000010)
#define BAUD_600          ((DWORD)0x00000020)
#define BAUD_1200         ((DWORD)0x00000040)
#define BAUD_1800         ((DWORD)0x00000080)
#define BAUD_2400         ((DWORD)0x00000100)
#define BAUD_4800         ((DWORD)0x00000200)
#define BAUD_7200         ((DWORD)0x00000400)
#define BAUD_9600         ((DWORD)0x00000800)
#define BAUD_14400        ((DWORD)0x00001000)
#define BAUD_19200        ((DWORD)0x00002000)
#define BAUD_38400        ((DWORD)0x00004000)
#define BAUD_56K          ((DWORD)0x00008000)
#define BAUD_128K         ((DWORD)0x00010000)
#define BAUD_115200       ((DWORD)0x00020000)
#define BAUD_57600        ((DWORD)0x00040000)
#define BAUD_USER         ((DWORD)0x10000000)

//
// Settable Data Bits
//

#define DATABITS_5        ((WORD)0x0001)
#define DATABITS_6        ((WORD)0x0002)
#define DATABITS_7        ((WORD)0x0004)
#define DATABITS_8        ((WORD)0x0008)
#define DATABITS_16       ((WORD)0x0010)
#define DATABITS_16X      ((WORD)0x0020)

//
// Settable Stop and Parity bits.
//

#define STOPBITS_10       ((WORD)0x0001)
#define STOPBITS_15       ((WORD)0x0002)
#define STOPBITS_20       ((WORD)0x0004)
#define PARITY_NONE       ((WORD)0x0100)
#define PARITY_ODD        ((WORD)0x0200)
#define PARITY_EVEN       ((WORD)0x0400)
#define PARITY_MARK       ((WORD)0x0800)
#define PARITY_SPACE      ((WORD)0x1000)

/**
 * This structure is used by the GetCommProperties function to return specific communication support
 * driver data.
 *
 * The contents of the dwProvSpec1, dwProvSpec2, and wcProvChar members depend on the provider
 * subtype; this is specified by the dwProvSubType member.
 *
 * If the provider subtype is PST_MODEM, these members are used as follows:
 *
 * Value Description dwProvSpec1 Not used dwProvSpec2 Not used wcProvChar Contains a MODEMDEVCAPS
 * structure
 */
typedef struct _COMMPROP {
    /**
     * Specifies the size, in bytes, of the entire data packet, regardless of the amount of data
     * requested.
     */
    WORD wPacketLength;
    /**
     * Specifies the version of the structure.
     */
    WORD wPacketVersion;
    /**
     * Specifies a bitmask indicating which services are implemented by this provider. The SP_SERIALCOMM
     * value is always specified for communications providers, including modem providers.
     */
    DWORD dwServiceMask;
    /**
     * Reserved; do not use.
     */
    DWORD dwReserved1;
    /**
     * Specifies the maximum size, in bytes, of the driver's internal output buffer. A value of zero
     * indicates that no maximum value is imposed by the serial provider.
     */
    DWORD dwMaxTxQueue;
    /**
     * Specifies the maximum size, in bytes, of the driver's internal input buffer. A value of zero
     * indicates that no maximum value is imposed by the serial provider.
     */
    DWORD dwMaxRxQueue;
    /**
     * Specifies the maximum acceptable baud rate, in bits per second (bps). It is one of the following
     * values: Value Description BAUD_075 75 bps BAUD_110 110 bps BAUD_134_5 134.5 bps BAUD_150 150 bps
     * BAUD_300 300 bps BAUD_600 600 bps BAUD_1200 1200 bps BAUD_1800 1800 bps BAUD_2400 2400 bps
     * BAUD_4800 4800 bps BAUD_7200 7200 bps BAUD_9600 9600 bps BAUD_14400 14400 bps BAUD_19200 19200
     * bps BAUD_38400 38400 bps BAUD_56K 56K bps BAUD_57600 57600 bps BAUD_115200 115200 bps BAUD_128K
     * 128K bps BAUD_USER Programmable baud rates available
     */
    DWORD dwMaxBaud;
    /**
     * Specifies the specific communications provider type. It is one of the following values: Value
     * Description PST_FAX FAX device PST_LAT LAT protocol PST_MODEM Modem device PST_NETWORK_BRIDGE
     * Unspecified network bridge PST_PARALLELPORT Parallel port PST_RS232 RS-232 serial port PST_RS422
     * RS-422 port PST_RS423 RS-423 port PST_RS449 RS-449 port PST_SCANNER Scanner device
     * PST_TCPIP_TELNET TCP/IP Telnet(R) protocol PST_UNSPECIFIED Unspecified PST_X25 X.25 standards
     */
    DWORD dwProvSubType;
    /**
     * Indicates the capabilities offered by the provider. It is one of the following values: Value
     * Description PCF_16BITMODE Special 16-bit mode is supported. PCF_DTRDSR DTR (Data Terminal Ready)
     * and DSR (Data Set Ready) are supported. PCF_INTTIMEOUTS Interval time-outs are supported.
     * PCF_PARITY_CHECK Parity checking is supported. PCF_RLSD RLSD (Receive Line Signal Detect) is
     * supported. PCF_RTSCTS RTS (Request to Send) and CTS (Clear to Send) are supported. PCF_SETXCHAR
     * XON and XOFF are supported. PCF_SPECIALCHARS Special character support is provided.
     * PCF_TOTALTIMEOUTS Total, elapsed, time-outs are supported. PCF_XONXOFF XON and XOFF flow control
     * are supported.
     */
    DWORD dwProvCapabilities;
    /**
     * Indicates the communication parameter that can be changed. It is one of the following values:
     * Value Description SP_BAUD Baud rate SP_DATABITS Data bits SP_HANDSHAKING Handshaking (flow
     * control) SP_PARITY Parity SP_PARITY_CHECK Parity checking SP_RLSD Receive Line Signal Detect
     * SP_STOPBITS Stop bits
     */
    DWORD dwSettableParams;
    /**
     * Indicates the baud rates that can be used. For values, see the dwMaxBaud member.
     */
    DWORD dwSettableBaud;
    /**
     * Indicates the number of data bits that can be set. It is one of the following values: Value
     * Description DATABITS_5 5 data bits DATABITS_6 6 data bits DATABITS_7 7 data bits DATABITS_8 8
     * data bits DATABITS_16 16 data bits DATABITS_16X Special wide path through serial hardware lines
     */
    WORD wSettableData;
    /**
     * Indicates the stop bit and parity settings that can be selected. It is one of the following
     * values: Value Description PARITY_EVEN Even parity PARITY_MARK Mark parity PARITY_NONE No parity
     * PARITY_ODD Odd parity PARITY_SPACE Space parity STOPBITS_10 1 stop bit STOPBITS_15 1.5 stop bits
     * STOPBITS_20 2 stop bits
     */
    WORD wSettableStopParity;
    /**
     * Specifies the size, in bytes, of the driver's internal output buffer. A value of zero indicates
     * that the value is unavailable.
     */
    DWORD dwCurrentTxQueue;
    /**
     * Specifies the size, in bytes, of the driver's internal input buffer. A value of zero indicates
     * that the value is unavailable.
     */
    DWORD dwCurrentRxQueue;
    /**
     * Specifies provider-specific data. Applications should ignore this member unless specific data
     * about the data format required by the provider is available.
     *
     * Set this member to COMMPROP_INITIALIZED before calling the GetCommProperties function to indicate
     * that the wPacketLength member is already valid.
     */
    DWORD dwProvSpec1;
    /**
     * Specifies provider-specific data. Applications should ignore this member unless specific data
     * about the data format required by the provider is available.
     */
    DWORD dwProvSpec2;
    /**
     * Specifies provider-specific data. Applications should ignore this member unless specific data
     * about the data format required by the provider is available.
     */
    WCHAR wcProvChar[1];
} COMMPROP,*LPCOMMPROP;

//
// Set dwProvSpec1 to COMMPROP_INITIALIZED to indicate that wPacketLength
// is valid before a call to GetCommProperties().
//
#define COMMPROP_INITIALIZED ((DWORD)0xE73CF52E)

/**
 * This structure contains communication device data. This structure is filled by the ClearCommError
 * function.
 */
typedef struct _COMSTAT {
    /**
     * Specifies if the transmission is waiting to receive the CTS (Clear to Send) signal. If this
     * member is TRUE, the transmission is waiting.
     */
    DWORD fCtsHold : 1;
    /**
     * Specifies if the transmission is waiting to receive the DSR (Data Set Ready) signal. If this
     * member is TRUE, the transmission is waiting.
     */
    DWORD fDsrHold : 1;
    /**
     * Specifies if the transmission is waiting to receive the RLSD (Receive Line Signal Detect) signal.
     * If this member is TRUE, the transmission is waiting.
     */
    DWORD fRlsdHold : 1;
    /**
     * Specifies if the transmission is waiting because the XOFF character was received. If this member
     * is TRUE, the transmission is waiting.
     */
    DWORD fXoffHold : 1;
    /**
     * Specifies if the transmission is waiting because the XOFF character was transmitted. If this
     * member is TRUE, the transmission is waiting. Transmission halts when the XOFF character is
     * transmitted to a system that takes the next character as XON, regardless of the actual character.
     */
    DWORD fXoffSent : 1;
    /**
     * Specifies if the End of File (EOF) character has been received. If this member is TRUE, the EOF
     * character has been received.
     */
    DWORD fEof : 1;
    /**
     * If this member is TRUE, there is a character queued for transmission that has come to the
     * communication device by way of the TransmitCommChar function. The communication device transmits
     * such a character ahead of other characters in the device's output buffer.
     */
    DWORD fTxim : 1;
    /**
     * Reserved; do not use.
     */
    DWORD fReserved : 25;
    /**
     * Specifies the number of bytes received by the serial provider, but not yet read by a ReadFile
     * operation.
     */
    DWORD cbInQue;
    /**
     * Specifies the number of bytes of user data remaining to be transmitted for all write operations.
     * This value will be zero for a nonoverlapped write.
     */
    DWORD cbOutQue;
} COMSTAT, *LPCOMSTAT;

//
// DTR Control Flow Values.
//
#define DTR_CONTROL_DISABLE    0x00
#define DTR_CONTROL_ENABLE     0x01
#define DTR_CONTROL_HANDSHAKE  0x02

//
// RTS Control Flow Values
//
#define RTS_CONTROL_DISABLE    0x00
#define RTS_CONTROL_ENABLE     0x01
#define RTS_CONTROL_HANDSHAKE  0x02
#define RTS_CONTROL_TOGGLE     0x03

/**
 * This structure defines the control setting for a serial communications device.
 *
 * For device driver developers: the COM_Open function in the sample serial port MDD driver does not
 * support the fErrorChar, fNull, and fAbortOnChar members of the DCB structure. You are expected to
 * add support for this functionality in your PDD layer, if appropriate for your serial port
 * hardware.
 *
 * The sample serial port MDD driver is found in Public\Common\Oak\Drivers\Serial.
 */
typedef struct _DCB {
    /**
     * Specifies the DCB structure length, in bytes.
     */
    DWORD DCBlength;      /* sizeof(DCB)                     */
    /**
     * Specifies the baud rate at which the communication device operates. It is an actual baud rate
     * value, or one of the following baud rate indexes: CBR_110 CBR_19200 CBR_300 CBR_38400 CBR_600
     * CBR_56000 CBR_1200 CBR_57600 CBR_2400 CBR_115200 CBR_4800 CBR_128000 CBR_9600 CBR_256000
     * CBR_14400
     */
    DWORD BaudRate;       /* Baudrate at which running       */
    /**
     * Specifies if binary mode is enabled. The Win32 API does not support nonbinary mode transfers, so
     * this member must be TRUE. Using FALSE will not work.
     */
    DWORD fBinary: 1;     /* Binary Mode (skip EOF check)    */
    /**
     * Specifies if parity checking is enabled. If this member is TRUE, parity checking is performed and
     * errors are reported.
     */
    DWORD fParity: 1;     /* Enable parity checking          */
    /**
     * Specifies if the CTS (clear-to-send) signal is monitored for output flow control. If this member
     * is TRUE and CTS is turned off, output is suspended until CTS is sent again.
     */
    DWORD fOutxCtsFlow:1; /* CTS handshaking on output       */
    /**
     * Specifies if the DSR (data-set-ready) signal is monitored for output flow control. If this member
     * is TRUE and DSR is turned off, output is suspended until DSR is sent again.
     */
    DWORD fOutxDsrFlow:1; /* DSR handshaking on output       */
    /**
     * Specifies the DTR (data-terminal-ready) flow control. This member can be one of the following
     * values: Value Description DTR_CONTROL_DISABLE Disables the DTR line when the device is opened and
     * leaves it disabled. DTR_CONTROL_ENABLE Enables the DTR line when the device is opened and leaves
     * it on. DTR_CONTROL_HANDSHAKE Enables DTR handshaking. If handshaking is enabled, it is an error
     * for the application to adjust the line by using the EscapeCommFunction function.
     */
    DWORD fDtrControl:2;  /* DTR Flow control                */
    /**
     * Specifies if the communications driver is sensitive to the state of the DSR signal. If this
     * member is TRUE, the driver ignores any bytes received, unless the DSR modem input line is high.
     */
    DWORD fDsrSensitivity:1; /* DSR Sensitivity              */
    /**
     * Specifies if transmission stops when the input buffer is full and the driver has transmitted the
     * XoffChar character. If this member is TRUE, transmission continues after the input buffer has
     * come within XoffLim bytes of being full and the driver has transmitted the XoffChar character to
     * stop receiving bytes. If this member is FALSE, transmission does not continue until the input
     * buffer is within XonLim bytes of being empty and the driver has transmitted the XonChar character
     * to resume reception.
     */
    DWORD fTXContinueOnXoff: 1; /* Continue TX when Xoff sent */
    /**
     * Specifies if XON/XOFF flow control is used during transmission. If this member is TRUE,
     * transmission stops when the XoffChar character is received and starts again when the XonChar
     * character is received.
     */
    DWORD fOutX: 1;       /* Enable output X-ON/X-OFF        */
    /**
     * Specifies if XON/XOFF flow control is used during reception. If this member is TRUE, the XoffChar
     * character is sent when the input buffer comes within XoffLim bytes of being full, and the XonChar
     * character is sent when the input buffer comes within XonLim bytes of being empty.
     */
    DWORD fInX: 1;        /* Enable input X-ON/X-OFF         */
    /**
     * Specifies if bytes received with parity errors are replaced with the character specified by the
     * ErrorChar member. If this member is TRUE and the fParity member is TRUE, replacement occurs.
     */
    DWORD fErrorChar: 1;  /* Enable Err Replacement          */
    /**
     * Specifies if null bytes are discarded. If this member is TRUE, null bytes are discarded when
     * received.
     */
    DWORD fNull: 1;       /* Enable Null stripping           */
    /**
     * Specifies the RTS (request-to-send) flow control. If this value is zero, the default is
     * RTS_CONTROL_HANDSHAKE. This member can be one of the following values: Value Description
     * RTS_CONTROL_DISABLE Disables the RTS line when the device is opened and leaves it disabled.
     * RTS_CONTROL_ENABLE Enables the RTS line when the device is opened and leaves it on.
     * RTS_CONTROL_HANDSHAKE Enables RTS handshaking. The driver raises the RTS line when the
     * "type-ahead" (input) buffer is less than one-half full and lowers the RTS line when the buffer is
     * more than three-quarters full. If handshaking is enabled, it is an error for the application to
     * adjust the line by using the EscapeCommFunction function. RTS_CONTROL_TOGGLE Specifies that the
     * RTS line will be high if bytes are available for transmission. After all buffered bytes have been
     * sent, the RTS line will be low.
     */
    DWORD fRtsControl:2;  /* Rts Flow control                */
    /**
     * Specifies if read and write operations are terminated if an error occurs. If this member is TRUE,
     * the driver terminates all read and write operations with an error status if an error occurs. The
     * driver will not accept any further communications operations until the application has
     * acknowledged the error by calling the ClearCommError function.
     */
    DWORD fAbortOnError:1; /* Abort all reads and writes on Error */
    /**
     * Reserved; do not use.
     */
    DWORD fDummy2:17;     /* Reserved                        */
    /**
     * Not used; set to zero.
     */
    WORD wReserved;       /* Not currently used              */
    /**
     * Specifies the minimum number of bytes accepted in the input buffer before the XON character is
     * sent.
     */
    WORD XonLim;          /* Transmit X-ON threshold         */
    /**
     * Specifies the maximum number of bytes accepted in the input buffer before the XOFF character is
     * sent. The maximum number of bytes accepted is calculated by subtracting this value from the size,
     * in bytes, of the input buffer.
     */
    WORD XoffLim;         /* Transmit X-OFF threshold        */
    /**
     * Specifies the number of bits in the bytes transmitted and received.
     */
    BYTE ByteSize;        /* Number of bits/byte, 4-8        */
    /**
     * Specifies the parity scheme to be used. It is one of the following values: Value Description
     * EVENPARITY Even MARKPARITY Mark NOPARITY No parity ODDPARITY Odd SPACEPARITY Space
     */
    BYTE Parity;          /* 0-4=None,Odd,Even,Mark,Space    */
    /**
     * Specifies the number of stop bits to be used. It is one of the following values: Value
     * Description ONESTOPBIT 1 stop bit ONE5STOPBITS 1.5 stop bits TWOSTOPBITS 2 stop bits
     */
    BYTE StopBits;        /* 0,1,2 = 1, 1.5, 2               */
    /**
     * Specifies the value of the XON character for both transmission and reception.
     */
    char XonChar;         /* Tx and Rx X-ON character        */
    /**
     * Specifies the value of the XOFF character for both transmission and reception.
     */
    char XoffChar;        /* Tx and Rx X-OFF character       */
    /**
     * Specifies the value of the character used to replace bytes received with a parity error.
     */
    char ErrorChar;       /* Error replacement char          */
    /**
     * Specifies the value of the character used to signal the end of data.
     */
    char EofChar;         /* End of Input character          */
    /**
     * Specifies the value of the character used to signal an event.
     */
    char EvtChar;         /* Received Event character        */
    /**
     * Reserved; do not use.
     */
    WORD wReserved1;      /* Fill for now.                   */
} DCB, *LPDCB;

/**
 * This structure is used in the SetCommTimeouts and GetCommTimeouts functions to set and query the
 * time-out parameters for a communication device. The parameters determine the behavior of the
 * ReadFile and WriteFile function operations on the device.
 *
 * If an application sets ReadIntervalTimeout and ReadTotalTimeoutMultiplier to MAXDWORD and sets
 * ReadTotalTimeoutConstant to a value greater than zero and less than MAXDWORD, one of the
 * following occurs when the ReadFile function is called:
 *
 * If there are any characters in the input buffer, ReadFile returns immediately with the characters
 * in the buffer.
 *
 * If there are no characters in the input buffer, ReadFile waits until a character arrives and then
 * returns immediately.
 *
 * If no characters arrive within the time specified by ReadTotalTimeoutConstant, ReadFile times
 * out.
 */
typedef struct _COMMTIMEOUTS {
    /**
     * Specifies the maximum acceptable time, in milliseconds, to elapse between the arrival of two
     * characters on the communication line. During a ReadFile operation, the time period begins when
     * the first character is received. If the interval between the arrival of any two characters
     * exceeds this amount, the ReadFile operation is completed and any buffered data is returned. A
     * value of zero indicates that interval time-outs are not used.
     */
    DWORD ReadIntervalTimeout;          /* Maximum time between read chars. */
    /**
     * Specifies the multiplier, in milliseconds, used to calculate the total time-out period for read
     * operations. For each read operation, this value is multiplied by the requested number of bytes to
     * be read.
     */
    DWORD ReadTotalTimeoutMultiplier;   /* Multiplier of characters.        */
    /**
     * Specifies the constant, in milliseconds, used to calculate the total time-out period for read
     * operations. For each read operation, this value is added to the product of the
     * ReadTotalTimeoutMultiplier member and the requested number of bytes.
     *
     * A value of zero for both the ReadTotalTimeoutMultiplier and ReadTotalTimeoutConstant members
     * indicates that total time-outs are not used for read operations.
     */
    DWORD ReadTotalTimeoutConstant;     /* Constant in milliseconds.        */
    /**
     * Specifies the multiplier, in milliseconds, used to calculate the total time-out period for write
     * operations. For each write operation, this value is multiplied by the number of bytes to be
     * written.
     */
    DWORD WriteTotalTimeoutMultiplier;  /* Multiplier of characters.        */
    /**
     * Specifies the constant, in milliseconds, used to calculate the total time-out period for write
     * operations. For each write operation, this value is added to the product of the
     * WriteTotalTimeoutMultiplier member and the number of bytes to be written.
     *
     * A value of zero for both the WriteTotalTimeoutMultiplier and WriteTotalTimeoutConstant members
     * indicates that total time-outs are not used for write operations.
     */
    DWORD WriteTotalTimeoutConstant;    /* Constant in milliseconds.        */
} COMMTIMEOUTS,*LPCOMMTIMEOUTS;

typedef struct _COMMCONFIG {
    DWORD dwSize;               /* Size of the entire struct */
    WORD wVersion;              /* version of the structure */
    WORD wReserved;             /* alignment */
    DCB dcb;                    /* device control block */
    DWORD dwProviderSubType;    /* ordinal value for identifying
                                   provider-defined data structure format*/
    DWORD dwProviderOffset;     /* Specifies the offset of provider specific
                                   data field in bytes from the start */
    DWORD dwProviderSize;       /* size of the provider-specific data field */
    WCHAR wcProviderData[1];    /* provider-specific data */
} COMMCONFIG,*LPCOMMCONFIG;

#define NOPARITY            0
#define ODDPARITY           1
#define EVENPARITY          2
#define MARKPARITY          3
#define SPACEPARITY         4

#define ONESTOPBIT          0
#define ONE5STOPBITS        1
#define TWOSTOPBITS         2

#define IGNORE              0       // Ignore signal

//
// Basud rates at which the communication device operates
//

#define CBR_110             110
#define CBR_300             300
#define CBR_600             600
#define CBR_1200            1200
#define CBR_2400            2400
#define CBR_4800            4800
#define CBR_9600            9600
#define CBR_14400           14400
#define CBR_19200           19200
#define CBR_38400           38400
#define CBR_56000           56000
#define CBR_57600           57600
#define CBR_115200          115200
#define CBR_128000          128000
#define CBR_256000          256000

//
// Error Flags
//

#define CE_RXOVER           0x0001  // Receive Queue overflow
#define CE_OVERRUN          0x0002  // Receive Overrun Error
#define CE_RXPARITY         0x0004  // Receive Parity Error
#define CE_FRAME            0x0008  // Receive Framing error
#define CE_BREAK            0x0010  // Break Detected
#define CE_TXFULL           0x0100  // TX Queue is full
#define CE_PTO              0x0200  // LPTx Timeout
#define CE_IOE              0x0400  // LPTx I/O Error
#define CE_DNS              0x0800  // LPTx Device not selected
#define CE_OOP              0x1000  // LPTx Out-Of-Paper
#define CE_MODE             0x8000  // Requested mode unsupported

#define IE_BADID            (-1)    // Invalid or unsupported id
#define IE_OPEN             (-2)    // Device Already Open
#define IE_NOPEN            (-3)    // Device Not Open
#define IE_MEMORY           (-4)    // Unable to allocate queues
#define IE_DEFAULT          (-5)    // Error in default parameters
#define IE_HARDWARE         (-10)   // Hardware Not Present
#define IE_BYTESIZE         (-11)   // Illegal Byte Size
#define IE_BAUDRATE         (-12)   // Unsupported BaudRate

//
// Events
//

#define EV_RXCHAR           0x0001  // Any Character received
#define EV_RXFLAG           0x0002  // Received certain character
#define EV_TXEMPTY          0x0004  // Transmitt Queue Empty
#define EV_CTS              0x0008  // CTS changed state
#define EV_DSR              0x0010  // DSR changed state
#define EV_RLSD             0x0020  // RLSD changed state
#define EV_BREAK            0x0040  // BREAK received
#define EV_ERR              0x0080  // Line status error occurred
#define EV_RING             0x0100  // Ring signal detected
#define EV_PERR             0x0200  // Printer error occured
#define EV_RX80FULL         0x0400  // Receive buffer is 80 percent full
#define EV_EVENT1           0x0800  // Provider specific event 1
#define EV_EVENT2           0x1000  // Provider specific event 2
#define EV_POWER			0x2000  // WINCE Power event.

//
// Escape Functions
//

#define SETXOFF             1       // Simulate XOFF received
#define SETXON              2       // Simulate XON received
#define SETRTS              3       // Set RTS high
#define CLRRTS              4       // Set RTS low
#define SETDTR              5       // Set DTR high
#define CLRDTR              6       // Set DTR low
// Gap for NT code RESETDEV, not supported on CE
#define SETBREAK            8       // Set the device break line.
#define CLRBREAK            9       // Clear the device break line.
#define SETIR               10      // Clear the device break line.
#define CLRIR               11      // Clear the device break line.

//
// PURGE function flags.
//
#define PURGE_TXABORT       0x0001  // Kill the pending/current writes to the comm port.
#define PURGE_RXABORT       0x0002  // Kill the pending/current reads to the comm port.
#define PURGE_TXCLEAR       0x0004  // Kill the transmit queue if there.
#define PURGE_RXCLEAR       0x0008  // Kill the typeahead buffer if there.

#define LPTx                0x80    // Set if ID is for LPT device

//
// Modem Status Flags
//
#define MS_CTS_ON           ((DWORD)0x0010)
#define MS_DSR_ON           ((DWORD)0x0020)
#define MS_RING_ON          ((DWORD)0x0040)
#define MS_RLSD_ON          ((DWORD)0x0080)

/**
 * This function restores character transmission for a specified communications device and places
 * the transmission line in a nonbreak state.
 *
 * @param hFile [in] Handle to the communications device. The CreateFile function returns this
 *   handle.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * A communications device is placed in a break state by the SetCommBreak or EscapeCommFunction
 * function. Character transmission is then suspended until the break state is cleared by calling
 * ClearCommBreak.
 */
BOOL
WINAPI
ClearCommBreak(
    HANDLE hFile
    );


/**
 * This function retrieves information about a communications error and reports the current status
 * of a communications device. The function is called when a communications error occurs, and it
 * clears the error flag of the device to enable additional input and output (I/O) operations.
 *
 * @param hFile [in] Handle to the communications device. The CreateFile function returns this
 *   handle.
 * @param lpErrors [out] Long pointer to a 32-bit variable to be filled with a mask indicating the
 *   type of error. This parameter can be one or more of the following error codes: Error code
 *   Description CE_BREAK The hardware detected a break condition. CE_FRAME The hardware detected a
 *   framing error. CE_IOE An I/O error occurred during communications with the device. CE_MODE The
 *   requested mode is not supported, or the hFile parameter is invalid. If this value is specified,
 *   it is the only valid error. CE_OVERRUN A character-buffer overrun has occurred. The next
 *   character is lost. CE_RXOVER An input buffer overflow has occurred. There is either no room in
 *   the input buffer, or a character was received after the end-of-file (EOF) character. CE_RXPARITY
 *   The hardware detected a parity error. CE_TXFULL The application tried to transmit a character,
 *   but the output buffer was full.
 * @param lpStat [out] Long pointer to a COMSTAT structure in which the device's status information
 *   is returned. If lpStat is NULL, no status information is returned.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * If a communications port has been set up with a TRUE value for the fAbortOnError member of the
 * setup DCB structure, the communications software will terminate all read and write operations on
 * the communications port when a communications error occurs. No new read or write operations will
 * be accepted until the application acknowledges the communications error by calling the
 * ClearCommError function.
 *
 * The ClearCommError function fills the status buffer pointed to by the lpStat parameter with the
 * current status of the communications device specified by the hFile parameter.
 *
 * Windows CE does not support the CE_DNS, CE_OPP, and CE_PTO error codes.
 */
BOOL
WINAPI
ClearCommError(
    HANDLE hFile,
    LPDWORD lpErrors,
    LPCOMSTAT lpStat
    );


/**
 * This function initializes the communications parameters for a specified communications device.
 *
 * @param hFile [in] Handle to the communications device. The CreateFile function returns this
 *   handle.
 * @param dwInQueue [in] Specifies the recommended size, in bytes, of the device's internal input
 *   buffer.
 * @param dwOutQueue [in] Specifies the recommended size, in bytes, of the device's internal output
 *   buffer.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * After a process uses the CreateFile function to open a handle to a communications device, it can
 * call SetupComm to set the communications parameters for the device. If it does not set them, the
 * device uses the default parameters when the first call to another communications function occurs.
 *
 * The dwInQueue and dwOutQueue parameters specify the recommended sizes for the internal buffers
 * used by the driver for the specified device. For example, YMODEM protocol packets are slightly
 * larger than 1024 bytes. Therefore, a recommended buffer size might be 1200 bytes for YMODEM
 * communications.
 *
 * The device driver receives the recommended buffer sizes, but is free to use any input and output
 * (I/O) buffering scheme, as long as it provides reasonable performance and data is not lost due to
 * overrun (except under extreme circumstances). For example, the function can succeed even though
 * the driver does not allocate a buffer, as long as some other portion of the system provides
 * equivalent functionality.
 */
BOOL
WINAPI
SetupComm(
    HANDLE hFile,
    DWORD dwInQueue,
    DWORD dwOutQueue
    );


/**
 * This function directs a specified communication device to perform an extended function.
 *
 * @param hFile [in] Handle to the communication device. The CreateFile function returns this
 *   handle.
 * @param dwFunc [in] Specifies the extended function code to perform. It can be one of the
 *   following values: Value Description SETIR Sets the serial port to infrared (IR) mode. CLRIR Sets
 *   port to normal serial mode. CLRDTR Clears the DTR (Data Terminal Ready) signal. CLRRTS Clears the
 *   RTS (Request To Send) signal. SETDTR Sends the DTR (Data Terminal Ready) signal. SETRTS Sends the
 *   RTS (Request To Send) signal. SETXOFF Causes transmission to act as if an XOFF character has been
 *   received. SETXON Causes transmission to act as if an XON character has been received. SETBREAK
 *   Suspends character transmission and places the transmission line in a break state until the
 *   ClearCommBreak function is called (or EscapeCommFunction is called with the CLRBREAK extended
 *   function code). The SETBREAK extended function code is identical to the SetCommBreak function.
 *   This extended function does not flush data that has not been transmitted. CLRBREAK Restores
 *   character transmission and places the transmission line in a nonbreak state. The CLRBREAK
 *   extended function code is identical to the ClearCommBreak function.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error data, call
 *   GetLastError.
 */
BOOL
WINAPI
EscapeCommFunction(
    HANDLE hFile,
    DWORD dwFunc
    );


/**
 * This function retrieves the event mask value for a specified communication device.
 *
 * @param hFile [in] Handle to the communication device. The CreateFile function returns this
 *   handle.
 * @param lpEvtMask [out] Long pointer to the 32-bit variable to be filled with a mask of events
 *   currently enabled. This parameter can be one or more of the following values: Value Description
 *   EV_BREAK A break was detected on input. EV_CTS The CTS (Clear To Send) signal changed state.
 *   EV_DSR The DSR (Data Set Ready) signal changed state. EV_ERR A line-status error occurred.
 *   Line-status errors are CE_FRAME, CE_OVERRUN, and CE_RXPARITY. EV_RING A ring indicator was
 *   detected. EV_RLSD The RLSD (Receive Line Signal Detect) signal changed state. EV_RXCHAR A
 *   character was received and placed in the input buffer. EV_RXFLAG The event character was received
 *   and placed in the input buffer. The event character is specified in the device's DCB structure,
 *   which is applied to a serial port by using the SetCommState function. EV_TXEMPTY The last
 *   character in the output buffer was sent.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error data, call
 *   GetLastError.
 *
 * The GetCommMask function uses a 32-bit mask variable to indicate the set of events that can be
 * monitored for a particular communication resource. A handle to the communication resource can be
 * specified in a call to the WaitCommEvent function, which waits for an event to occur. To modify
 * the event mask of a communication resource, use the SetCommMask function.
 */
BOOL
WINAPI
GetCommMask(
    HANDLE hFile,
    LPDWORD lpEvtMask
    );


/**
 * This function fills a buffer with communication properties data for a specified communication
 * device.
 *
 * @param hFile [in] Handle to the communication device. The CreateFile function returns this
 *   handle.
 * @param lpCommProp [out] Long pointer to a COMMPROP structure in which the communication
 *   properties data is returned. This data can be used in subsequent calls to the SetCommState,
 *   SetCommTimeouts, or SetupComm function to configure the communication device.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error data, call
 *   GetLastError.
 *
 * GetCommProperties returns data from a device driver about the configuration settings supported by
 * the driver.
 */
BOOL
WINAPI
GetCommProperties(
    HANDLE hFile,
    LPCOMMPROP lpCommProp
    );


/**
 * This function retrieves modem control-register values.
 *
 * @param hFile [in] Handle to the communication device. The CreateFile function returns this
 *   handle.
 * @param lpModemStat [out] Long pointer to a 32-bit variable that specifies the current state of
 *   the modem control-register values. This parameter can be a combination of the following values:
 *   Value Description MS_CTS_ON The CTS (Clear To Send) signal is on. MS_DSR_ON The DSR (Data Set
 *   Ready) signal is on. MS_RING_ON The ring indicator signal is on. MS_RLSD_ON The RLSD (Receive
 *   Line Signal Detect) signal is on.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error data, call
 *   GetLastError.
 *
 * The GetCommModemStatus function is useful when using the WaitCommEvent function to monitor the
 * CTS, DSR, DSR, or ring indicator signals. To detect when these signals change state, use
 * WaitCommEvent and then use GetCommModemStatus to determine the state after a change occurs.
 *
 * The function fails if the hardware does not support the control-register values.
 */
BOOL
WINAPI
GetCommModemStatus(
    HANDLE hFile,
    LPDWORD lpModemStat
    );


/**
 * This function fills in a device-control block (a DCB structure) with the current control settings
 * for a specified communication device.
 *
 * @param hFile [in] Handle to the communication device. The CreateFile function returns this
 *   handle.
 * @param lpDCB [out] Long pointer to the DCB structure in which the control settings data is
 *   returned.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error data, call
 *   GetLastError.
 */
BOOL
WINAPI
GetCommState(
    HANDLE hFile,
    LPDCB lpDCB
    );


/**
 * This function retrieves the time-out parameters for all read and write operations on a specified
 * communication device.
 *
 * @param hFile [in] Handle to the communication device. The CreateFile function returns this
 *   handle.
 * @param lpCommTimeouts [out] Long pointer to a COMMTIMEOUTS structure in which the time-out data
 *   is returned.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error data, call
 *   GetLastError.
 *
 * For more information about time-out values for communication devices, see the SetCommTimeouts
 * function.
 */
BOOL
WINAPI
GetCommTimeouts(
    HANDLE hFile,
    LPCOMMTIMEOUTS lpCommTimeouts
    );


/**
 * This function can discard all characters from the output or input buffer of a specified
 * communications resource. It can also terminate pending read or write operations on the resource.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * If a thread uses PurgeComm to flush an output buffer, the deleted characters are not transmitted.
 * To empty the output buffer while ensuring that the contents are transmitted, call the
 * FlushFileBuffers function (a synchronous operation). Note, however, that FlushFileBuffers is
 * subject to flow control but not to write time-outs, and it will not return until all pending
 * write operations have been transmitted.
 */
BOOL
WINAPI
PurgeComm(
    HANDLE hFile,
    DWORD dwFlags
    );


/**
 * This function suspends character transmission for a specified communications device and places
 * the transmission line in a break state until the ClearCommBreak function is called.
 *
 * @param hFile [in] Handle to the communications device. The CreateFile function returns this
 *   handle.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 */
BOOL
WINAPI
SetCommBreak(
    HANDLE hFile
    );


/**
 * This function specifies a set of events to be monitored for a communications device.
 *
 * @param hFile [in] Handle to the communications device. The CreateFile function returns this
 *   handle.
 * @param dwEvtMask [in] Specifies the events to be enabled. A value of zero disables all events.
 *   This parameter can be a combination of the following values: Value Description EV_BREAK A break
 *   was detected on input. EV_CTS The CTS (clear-to-send) signal changed state. EV_DSR The DSR
 *   (data-set-ready) signal changed state. EV_ERR A line-status error occurred. Line-status errors
 *   are CE_FRAME, CE_OVERRUN, and CE_RXPARITY. EV_RING A ring indicator was detected. EV_RLSD The
 *   RLSD (receive-line-signal-detect) signal changed state. EV_RXCHAR A character was received and
 *   placed in the input buffer. EV_RXFLAG The event character was received and placed in the input
 *   buffer. The event character is specified in the device's DCB structure, which is applied to a
 *   serial port by using the SetCommState function. EV_TXEMPTY The last character in the output
 *   buffer was sent.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * The SetCommMask function specifies the set of events that can be monitored for a particular
 * communications resource. A handle to the communications resource can be specified in a call to
 * the WaitCommEvent function, which waits for one of the events to occur. To get the current event
 * mask of a communications resource, use the GetCommMask function.
 */
BOOL
WINAPI
SetCommMask(
    HANDLE hFile,
    DWORD dwEvtMask
    );


/**
 * This function configures a communications device according to the specifications in a
 * device-control block (a DCB structure). The function reinitializes all hardware and control
 * settings, but it does not empty output or input queues.
 *
 * @param hFile [in] Handle to the communications device. The CreateFile function returns this
 *   handle.
 * @param lpDCB [in] Long pointer to a DCB structure containing the configuration information for
 *   the specified communications device.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * The SetCommState function uses a DCB structure to specify the desired configuration. The
 * GetCommState function returns the current configuration.
 *
 * To set only a few members of the DCB structure, you should modify a DCB structure that has been
 * filled in by a call to GetCommState. This ensures that the other members of the DCB structure
 * have appropriate values.
 *
 * The SetCommState function fails if the XonChar member of the DCB structure is equal to the
 * XoffChar member.
 */
BOOL
WINAPI
SetCommState(
    HANDLE hFile,
    LPDCB lpDCB
    );


/**
 * This function sets the time-out parameters for all read and write operations on a specified
 * communications device.
 *
 * @param hFile [in] Handle to the communications device. The CreateFile function returns this
 *   handle.
 * @param lpCommTimeouts [in] Long pointer to a COMMTIMEOUTS structure that contains the new
 *   time-out values.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 */
BOOL
WINAPI
SetCommTimeouts(
    HANDLE hFile,
    LPCOMMTIMEOUTS lpCommTimeouts
    );


/**
 * This function transmits a specified character ahead of any pending data in the output buffer of
 * the specified communications device.
 *
 * @param hFile [in] Handle to the communications device. The CreateFile function returns this
 *   handle.
 * @param cChar [in] Specifies the character to be transmitted.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * The TransmitCommChar function is useful for sending an interrupt character (such as a CTRL+C) to
 * a host system.
 *
 * If the device is not transmitting, TransmitCommChar cannot be called repeatedly. Once
 * TransmitCommChar places a character in the output buffer, the character must be transmitted
 * before the function can be called again. If the previous character has not yet been sent,
 * TransmitCommChar returns an error.
 */
BOOL
WINAPI
TransmitCommChar(
    HANDLE hFile,
    char cChar
    );


/**
 * This function waits for an event to occur for a specified communications device. The set of
 * events that are monitored by WaitCommEvent is contained in the event mask associated with the
 * device handle.
 *
 * @param hFile [in] Handle to the communications device. The CreateFile function returns this
 *   handle.
 * @param lpEvtMask [out] Long pointer to a 32-bit variable that receives a mask indicating the
 *   events that occurred. If an error occurs, the value is zero; otherwise, it is one or more of the
 *   following values: Value Description EV_BREAK A break was detected on input. EV_CTS The CTS
 *   (clear-to-send) signal changed state. EV_DSR The DSR (data-set-ready) signal changed state.
 *   EV_ERR A line-status error occurred. Line-status errors are CE_FRAME, CE_OVERRUN, and
 *   CE_RXPARITY. EV_POWER Power event, which is generated whenever the device is powered on. EV_RING
 *   A ring indicator was detected. EV_RLSD The RLSD (receive-line-signal-detect) signal changed
 *   state. EV_RXCHAR A character was received and placed in the input buffer. EV_RXFLAG The event
 *   character was received and placed in the input buffer. The event character is specified in the
 *   device's DCB structure, which is applied to a serial port by using the SetCommState function.
 *   EV_TXEMPTY The last character in the output buffer was sent.
 * @param lpOverlapped [in] Ignored; set to NULL.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * The WaitCommEvent function monitors a set of events for a specified communications resource. To
 * set and query the current event mask of a communications resource, use the SetCommMask and
 * GetCommMask functions. When a communications event that is set by SetCommMask occurs,
 * WaitCommEvent returns.
 */
BOOL
WINAPI
WaitCommEvent(
    HANDLE hFile,
    LPDWORD lpEvtMask,
    LPOVERLAPPED lpOverlapped
    );

// End if IF COREDLL_SERDEV
// @CESYSGEN ENDIF

// @CESYSGEN IF GWES_GETPOWER
//
// Power Management APIs
//

#define AC_LINE_OFFLINE                 0x00
#define AC_LINE_ONLINE                  0x01
#define AC_LINE_BACKUP_POWER            0x02
#define AC_LINE_UNKNOWN                 0xFF

#define BATTERY_FLAG_HIGH               0x01
#define BATTERY_FLAG_LOW                0x02
#define BATTERY_FLAG_CRITICAL           0x04
#define BATTERY_FLAG_CHARGING           0x08
#define BATTERY_FLAG_NO_BATTERY         0x80
#define BATTERY_FLAG_UNKNOWN            0xFF

#define BATTERY_PERCENTAGE_UNKNOWN      0xFF

#define BATTERY_LIFE_UNKNOWN        0xFFFFFFFF

/**
 * This structure contains information about the power status of the system.
 */
typedef struct _SYSTEM_POWER_STATUS_EX {
    /**
     * AC power status. It is one of the following values:
     *
     * - 0: Offline
     *
     * - 1: Online
     *
     * - 255: Unknown status
     *
     * All other values are reserved.
     */
    BYTE ACLineStatus;
    /**
     * Battery charge status. It can be a combination of the following values:
     *
     * - 1: High
     *
     * - 2: Low
     *
     * - 4: Critical
     *
     * - 8: Charging
     *
     * - 128: No system battery
     *
     * - 255: Unknown status
     *
     * All other values are reserved.
     */
    BYTE BatteryFlag;
    /**
     * Percentage of full battery charge remaining. This member can be a value in the range 0 to 100, or
     * 255 if status is unknown. All other values are reserved.
     */
    BYTE BatteryLifePercent;
    /**
     * Reserved; set to zero.
     */
    BYTE Reserved1;
    /**
     * Number of seconds of battery life remaining, or 0xFFFFFFFF if remaining seconds are unknown.
     */
    DWORD BatteryLifeTime;
    /**
     * Number of seconds of battery life when at full charge, or 0xFFFFFFFF if full lifetime is unknown.
     */
    DWORD BatteryFullLifeTime;
    /**
     * Reserved; set to zero.
     */
    BYTE Reserved2;
    /**
     * Backup battery charge status. It is one of the following values: BATTERY_FLAG_HIGH
     * BATTERY_FLAG_CRITICAL BATTERY_FLAG_CHARGING BATTERY_FLAG_NO_BATTERY BATTERY_FLAG_UNKNOWN
     * BATTERY_FLAG_LOW
     */
    BYTE BackupBatteryFlag;
    /**
     * Percentage of full backup battery charge remaining. Must be in the range 0 to 100, or
     * BATTERY_PERCENTAGE_UNKNOWN.
     */
    BYTE BackupBatteryLifePercent;
    /**
     * Reserved; set to zero
     */
    BYTE Reserved3;
    /**
     * Number of seconds of backup battery life remaining, or BATTERY_LIFE_UNKNOWN if remaining seconds
     * are unknown.
     */
    DWORD BackupBatteryLifeTime;
    /**
     * Number of seconds of backup battery life when at full charge, or BATTERY_LIFE_UNKNOWN if full
     * lifetime is unknown.
     */
    DWORD BackupBatteryFullLifeTime;
}   SYSTEM_POWER_STATUS_EX, *PSYSTEM_POWER_STATUS_EX, *LPSYSTEM_POWER_STATUS_EX;

/**
 * This function retrieves the power status of the system. The status indicates whether the system
 * is running on AC or DC power, whether or not the batteries are currently charging, and the
 * remaining life of main and backup batteries. The RAPI version is CeGetSystemPowerStatusEx for
 * versions 2.0 and later.
 *
 * @param pstatus [out] Pointer to the SYSTEM_POWER_STATUS_EX structure receiving the power status
 *   information.
 * @param fUpdate [in] If this Boolean is set to TRUE, GetSystemPowerStatusEx gets the latest
 *   information from the device driver, otherwise it retrieves cached information that may be
 *   out-of-date by several seconds.
 *
 * @return This function returns TRUE if successful; otherwise, it returns FALSE.
 *
 * The GetSystemPowerStatusEx function is not supported for emulation.
 *
 * When working with RAPI for Windows CE versions 1.0 and 1.01, use the PegGetSystemPowerStatusEx
 * function.
 */
BOOL
WINAPI
GetSystemPowerStatusEx(
    PSYSTEM_POWER_STATUS_EX pSystemPowerStatusEx,
	BOOL fUpdate
    );


void
WINAPI
BatteryNotifyOfTimeChange(
	BOOL fForward,
	FILETIME *pftDelta
	);
// @CESYSGEN ENDIF

// @CESYSGEN IF FILESYS_FSPASS
/**
 * This function compares a specified string to the system password. A remote application interface
 * (RAPI) version of this function exists, named CeCheckPassword.
 *
 * @param lpszPassword Pointer to a wide character string to compare with the system password.
 *
 * @return TRUE indicates that lpszPassword matches the system password. FALSE indicates failure.
 */
BOOL CheckPassword (LPWSTR lpszPassword);
// @CESYSGEN ENDIF

/**
 * This function registers a new device.
 *
 * @param lpszType Long pointer to the null-terminated string that contains the device identifier
 *   prefix (for example COM, DEV, PGR); must be 3 characters long.
 * @param dwIndex Specifies the device identifier index; must be a number from 0 through 9. For
 *   example, the index value for COM2 would be 2.
 * @param lpszLib Long pointer to the null-terminated string that contain that device driver DLL
 *   module name.
 * @param dwInfo Specifies instance information.
 *
 * @return A handle to a device indicates success. Zero indicates failure. This is passed to the
 *   following functions that are exported by the client driver: PRE_Open, PRE_Deinit, PRE_PowerUp,
 *   and PRE_PowerDown. For stream-based devices, the drivers are DLL files. Each driver is
 *   initialized by a call to the RegisterDevice function (performed by the server process). The
 *   IpszLib parameter is used to open the device. The IpszType parameter is a three character string
 *   which is used to identify the function entry points in the DLL, so that multiple devices can
 *   exist in one DLL. The lpszLib parameter is the name of the DLL that contains the entry points.
 *   Finally dwInfo is passed in to the initialization routine. So, for example, if there were two
 *   serial ports on a device, and Comm.dll was the DLL implementing the serial driver, it would
 *   likely present the following initialization calls:
 *
 * The DeregisterDevice function can be used if a device is removed from the system or is being shut
 * down. An example would be:
 *
 *     DeregisterDevice(h1);
 *
 * where h1 was returned from a call to RegisterDevice.
 */
HANDLE RegisterDevice (LPCWSTR lpszName, DWORD index, LPCWSTR lpszLib, DWORD dwInfo);
/**
 * This function deregisters a registered device.
 *
 * @param hDevice Handle to a registered device returned from RegisterDevice.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * The DeregisterDevice function can be used if a device is removed from the system or is being shut
 * down. An example would be:
 *
 *     DeregisterDevice(h1);
 *
 * where h1 was returned from a call to RegisterDevice.
 */
BOOL DeregisterDevice (HANDLE hDevice);
/**
 * This function is called by a device driver to load its associated file system driver (FSD).
 *
 * @param hDevice Handle to a registered device, obtained when a block device driver is called with
 *   the IOCTL DISK_IOCTL_INITIALIZED.
 * @param lpFSDName Pointer to the name of the FSD to load.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * LoadFSD is typically called by a block device driver to load a file system driver. For example,
 * the block device driver Atadisk.dll loads the file system driver Fatfs.dll.
 */
BOOL LoadFSD (HANDLE hDevice, LPCWSTR lpFSDName);

#include <winnls.h>

#ifdef __cplusplus
}
#endif

#ifdef WINCEOEM
#include <pwinbase.h>	// internal defines
#ifdef WINCEMACRO
#include <mwinbase.h>
#endif
#endif


#endif /* __WINBASE_H__ */
