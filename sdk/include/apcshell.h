//+----------------------------------------------------------------------------
// 
// File:		apcshell.h
//
// Copyight:	(c) 1997, Microsoft Corporation
// 				All Rights Reserved
//				Infomation Contained Herein Is Propprietary and Confidential
//
// Contents: 	APC Shell functions
//
//-----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

BOOL WINAPI SHCloseApps( DWORD dwMemSought);
int WINAPI  SHAppAlertState( BOOL fSet, BOOL fCurrentUser, const WCHAR * wcsAppName, 
                               const WCHAR * wcsAlertName, LONG * pAlertInfo, LONG * pAlertVal);
LRESULT WINAPI SH_keybd_event(BYTE Vk, BYTE Scan, DWORD dwFlags, DWORD dwExtraInfo );
LRESULT WINAPI SH_HID_Register(LPWSTR szDevice, BOOL fArrive);


// Defines for SHAppAlertState *pAlertInfo
//
// With fSet TRUE pAlertInfo is passed in as the SH_ALERTACTION_XXX Action to take
// When fSet is FALSE, *pAlertInfo is returned as the TRUE/FALSE value of the alert

#define SH_ALERTACTION_CLEAR            0
#define SH_ALERTACTION_RAISE_VALUE      1
#define SH_ALERTACTION_CLEAR_MASK       2
#define SH_ALERTACTION_RAISE_MASK       3


typedef struct tagGLOBALGRAMMARINFO
{
	LONG		gi_lStat;		    // 0 for InActive, 1 for Active, -1 for Always active
	WCHAR *	    gi_wcsPhrase;		// These pointers returned within the allocated buffer
} GLOBALGRAMMARINFO, * PGLOBALGRAMMARINFO;

LRESULT WINAPI SHGetGlobalGrammar(  LONG * plCurrentEntries,
                                    LONG * plMaxEntries,
                                    LONG * plActiveEntries,
                                    PGLOBALGRAMMARINFO * ppGGrammarInfo);

LRESULT WINAPI SHGlobalGrammarSetItemState( const WCHAR *   sPhrase, 
                                            BOOL            fActive,
                                            BOOL            fDeferRefresh);

#ifdef __cplusplus
}
#endif

