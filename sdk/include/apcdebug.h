/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    ApcDebug.h

Abstract:

    Common debug header for all AutoPC applications
    Relies on WinCE debug routines

Notes:

    In your CPP file containing your WinMain or DllMain function:

	#define APCDBG_INIT "App or DLL name"
	#include <apcdebug.h>

    The APCDBG_INIT define should be a string of 31 or less chars

    In all your other CPP files:

	#include <ApcDebug.h>


    To Assert that something is true you:

	DEBUGCHK(exp)

    This will display a debug output containing the module name
    specified in APC_DBG_INIT, the file name and line number of the
    failed condition.  It will then do a hard break into the
    debugger.  You can use ASSERT(exp) but you won't get the module
    name displayed (you'll get Unknown).


    To display a debug message you:

	DEBUGMSG(zone, printf_exp)

    where zone is one of ZONE_ defines below.  Using our common
    ZONE_ defines lets us consistantly turn on and off debug output.

	ZONE_FUNCTION   entry and exit of a function

	ZONE_WARNING    	warning of something that may be a problem but
				isn't technically an error.
			NOTE: Everyone will see this output by default
	
	ZONE_ERROR      details of an error condition that shouldn't
			be happening.
			NOTE: Everyone will see this output by default

	ZONE_VERBOSE    trace output that allows a human to follow
			program flow.  Useful when single stepping is
			prohibitive due to timing related bugs, etc.

	ZONE_SPEECH	speech related trace output.  NOT errors and
			warnings (these should use ZONE_WARNING and
			ZONE_ERROR).

	ZONE_SINK	message sink trace output.  NOT errors and
			warnings (these should use ZONE_WARNING and
			ZONE_ERROR).

	ZONE_AUDIO	audio related trace output.  NOT errors and
			warnings (these should use ZONE_WARNING and
			ZONE_ERROR).

	ZONE_CONTROLS	control related trace output.  NOT errors and
			warnings (these should use ZONE_WARNING and
			ZONE_ERROR).


    By default the debug output for ZONE_WARNING and ZONE_ERROR is
    turned on.  If you want to enable debug output for a different
    set of zones at any time, you need to calculate the sum of
    2^zone# for each zone# you want turned on.  Then pass your sum
    to SETDBGZONE() like this:

	SETDBGZONE(0x6);


    If you really, really need additional ZONE_XXXXs defined you
    need to do the following in your WinMain module:

	#define APCDBG_15 "your zone name"
	#define APCDBG_14 "your zone name"
	    :
	#define APCDBG_8 "your zone name"

	#define APCDBG_INIT "App or DLL name"
	#include <ApcDebug.h>

    Start with 15 and work backwards in case we add additional
    common zones.  You will also need to add lines like the
    following to your common header so you can use your new zones:

	#define ZONE_YOURZONE   DEBUGZONE(15)

-------------------------------------------------------------------*/


#ifndef _APCDEBUG_H
#define _APCDEBUG_H

/////////////////////////////////////////////////////////
//Review: dbgapi.h doesn't get included on NT yet, remove when emulator work done
//
// The following is stolen and paraphrased in part from public\COMMON\sdk\inc\dbgapi.h
#ifndef __DBGAPI_H__
#define __DBGAPI_H__

    #ifdef __cplusplus
    extern "C" {
    #endif
    
    #ifdef DEBUG

        typedef struct _DBGPARAM {
	        WCHAR	lpszName[32];           // @field Name of module
	        WCHAR   rglpszZones[16][32];    // @field names of zones for first 16 bits
	        ULONG   ulZoneMask;             // @field Current zone Mask
        } DBGPARAM, *LPDBGPARAM;

        void NKDbgPrintfW(LPWSTR lpszFmt, ...);

        #ifdef APCDBG_INIT	// since we only do this once per app, insert the code here
            #include <stdlib.h>
            void NKDbgPrintfW(LPWSTR lpszFmt, ...)
            {
	        WCHAR szTmp[1024];
	        va_list ap;

	        va_start(ap, lpszFmt);
	        vswprintf(szTmp, lpszFmt, ap);
	        va_end(ap);
	        OutputDebugStringW(szTmp);
            }
        #endif // APCDBG_INIT

        extern  DBGPARAM    dpCurSettings;

        #define DEBUGZONE(n)  (dpCurSettings.ulZoneMask&(0x00000001<<n))

        #ifdef UNDER_CE
        #undef DEBUGMSG
        #undef DEBUGCHK
        #endif

        #define DEBUGCHK(exp)	\
           ((void)((exp)?1:(	\
               NKDbgPrintfW ( TEXT("%s: DEBUGCHK failed in file %s at line %d \r\n"),	\
                         (LPWSTR)dpCurSettings.lpszName, TEXT(__FILE__) ,__LINE__ ),	\
               DebugBreak(), 0 )))

        #define DEBUGMSG(cond,printf_exp)   \
           ((void)((cond)?(NKDbgPrintfW printf_exp),1:0))

        #define ASSERT(exp) DEBUGCHK(exp)
        #define VERIFY(exp) DEBUGCHK(exp)

        #define DEBUGREGISTER(hMod) ((void)0)

    #else // not DEBUG

        #define ASSERT(exp)	((void)0)
        #define VERIFY(exp)	(exp)
        #define DEBUGMSG(cond,printf_exp) ((void)0)
        #define DEBUGCHK(exp) ((void)0)
        #define DEBUGREGISTER(hMod) ((void)0)

    #endif // DEBUG

    #ifdef __cplusplus
    }
    #endif

#endif // __DBGAPI_H__
//
// End of NT emulator hack
/////////////////////////////////////////////////////////


#ifdef DEBUG

    /////////////////////////////////////////////////////////
    // Start of DEBUG mode defines

    #ifdef ZONE_FUNCTION
    #undef ZONE_FUNCTION
    #endif

    #ifdef ZONE_ERROR
    #undef ZONE_ERROR
    #endif

    #ifdef ZONE_SPEECH
    #undef ZONE_SPEECH
    #endif

    #define ZONE_FUNCTION   DEBUGZONE(0)
    #define ZONE_WARNING    DEBUGZONE(1)
    #define ZONE_ERROR      DEBUGZONE(2)
    #define ZONE_VERBOSE    DEBUGZONE(3)
    #define ZONE_SPEECH	DEBUGZONE(4)
    #define ZONE_SINK	DEBUGZONE(5)
    #define ZONE_AUDIO	DEBUGZONE(6)
    #define ZONE_CONTROLS	DEBUGZONE(7)


    #ifdef APCDBG_INIT

        #pragma message("APCDBG_INIT defined - initializing dpCurSettings")

        DBGPARAM dpCurSettings = {
            TEXT(APCDBG_INIT),
	        TEXT("Function"),   // ZONE_FUNCTION
	        TEXT("Warning"),    // ZONE_WARNING
	        TEXT("Error"),	    // ZONE_ERROR
	        TEXT("Verbose"),    // ZONE_VERBOSE
	        TEXT("Speech"),	    // ZONE_SPEECH
	        TEXT("Sink"),	    // ZONE_SINK
	        TEXT("Audio"),	    // ZONE_AUDIO
	        TEXT("Controls"),   // ZONE_CONTROLS

        #ifdef APCDBG_8
	        TEXT(APCDBG_8),
        #else
	        TEXT("?"),
        #endif

        #ifdef APCDBG_9
	        TEXT(APCDBG_9),
        #else
	        TEXT("?"),
        #endif

        #ifdef APCDBG_10
	        TEXT(APCDBG_10),
        #else
	        TEXT("?"),
        #endif

        #ifdef APCDBG_11
	        TEXT(APCDBG_11),
        #else
	        TEXT("?"),
        #endif

        #ifdef APCDBG_12
	        TEXT(APCDBG_12),
        #else
	        TEXT("?"),
        #endif

        #ifdef APCDBG_13
	        TEXT(APCDBG_13),
        #else
	        TEXT("?"),
        #endif

        #ifdef APCDBG_14
	        TEXT(APCDBG_14),
        #else
	        TEXT("?"),
        #endif

        #ifdef APCDBG_15
	        TEXT(APCDBG_15),
        #else
	        TEXT("?"),
        #endif


            0x00000006		// ZONE_WARNING | ZONE_ERROR
        };


    #endif // APCDEBUGINIT


    #define SETDBGZONE(z)	(dpCurSettings.ulZoneMask = z)

    #define S2WS1(str)   WCHAR S2WS1[100]; if(-1 == mbstowcs(S2WS1, (const char *)str, 100)) S2WS1[0]=0
    #define S2WS2(str)   WCHAR S2WS2[100]; if(-1 == mbstowcs(S2WS2, (const char *)str, 100)) S2WS2[0]=0
    #define S2WS3(str)   WCHAR S2WS3[100]; if(-1 == mbstowcs(S2WS3, (const char *)str, 100)) S2WS3[0]=0
    #define S2WS4(str)   WCHAR S2WS4[100]; if(-1 == mbstowcs(S2WS4, (const char *)str, 100)) S2WS4[0]=0


    // End of DEBUG mode defines
    /////////////////////////////////////////////////////////

#else // not DEBUG

    /////////////////////////////////////////////////////////
    // Start of RETAIL mode defines

    #define SETDBGZONE(z)	(0)

    #define S2WS1(str)          (0)
    #define S2WS2(str)          (0)
    #define S2WS3(str)          (0)
    #define S2WS4(str)          (0)

    // End of RETAIL mode defines
    /////////////////////////////////////////////////////////

#endif // DEBUG

#endif // _APCDEBUG_H
