//* ****************************************************************************
//* High level AutoPC Simple Speech Interface 
//* ****************************************************************************
#ifndef _IAPCSPCH_H_
#define _IAPCSPCH_H_

#include <apcmsg.h>
#include <speech.h>

#ifdef INITGUID
#include <initguid.h>
#endif

// APCSPCH related window messages in 0xBE80 - 0xBEBF range
#define WM_SPCH_RECOG               (APC_SPCH_START+0x10)
#define WM_SPCH_NOTIFY              (APC_SPCH_START+0x11)
#define WM_SPCH_SNDDONE             (APC_SPCH_START+0x12)
#define WM_SPCH_FEEDBACK            (APC_SPCH_START+0x13)

// STRUCTURES 
typedef UINT	GRAMMARID;

//* ****************************************************************************
// Defines
//* ****************************************************************************

//	flags passed to SetSpeakContextRule
#define APCSPCH_TN_ADDR_CTX	        0x1000

#define APCSPCH_TN_SPELLING_CTX	    0x2000
#define APCSPCH_TN_PHONE_CTX	    0x3000

#define APCSPCH_TN_WORD             0x0001


//  flags passed to CreateSpkContext
// 0 is reserved
#define APCSPCH_TN_CONTEXT_NEW      0x0001
#define APCSPCH_TN_CONTEXT_COPY     0x0002
#define APCSPCH_TN_CONTEXT_EXTEND   0x0003

//	flags passed to CreateVMenu and AddVMenuCommand
#define APCSPCH_VM_USEEXISTING      0x0100
//	flags passed to AddVMenuCommand only
#define APCSPCH_VM_NOFEEDBACK		0x00001000

//	flags passed to SpeakEx
#define APCSPCH_SP_BACKGROUND       0x0008

//	speaking mode returned by QuerySpeakingMode
//	0 means no TTS or wave file
#define APCSPCH_SP_TTS				1
#define APCSPCH_SP_WAVEFILE			2

//	feedback level returned by QueryFeedbackLevel function
#define APCSPCH_FB_MORE				0x100
#define APCSPCH_FB_LESS				0x200
#define APCSPCH_FB_NONE				0x300

//	flags passed to VoiceHelpStart
#define APCSPCH_VH_LONGHELP			1
#define APCSPCH_VH_SHORTHELP		2
#define APCSPCH_VH_LISTGLOBAL		4

// Infomation delivered with WM_SPCH_FEEDBACK message
//
// HIWORD(wParam) - Rsvd
// LOWORD(wParam) - Current Feedback level
// HIWORD(lParam) - Speech Feedback initiation reason
// LOWORD(lParam) - Reason specific information
//
// Reason defines for HIWORD(lParam)

#define SFR_WAKEUPWORD      1
#define SFR_PTT             2
#define SFR_READ            3

//* ****************************************************************************
//* New COM Simple Speech Interface
//* ****************************************************************************
DECLARE_INTERFACE(IAPCSpeech);

#undef	INTERFACE
#define	INTERFACE   IAPCSpeech

// {ebc930f0-d912-11d0-90c2-00aa00c0837c}
// Apollo simple speech interface
DEFINE_GUID(IID_IAPCSPEECH, 
0xEBC930F0, 0xD912, 0x11D0, 0x90, 0xC2, 0x00, 0xaA, 0x00, 0xC0, 0x83, 0x7C);


DECLARE_INTERFACE_(IAPCSpeech,IUnknown)
{
    // IUnknown members
    STDMETHOD(QueryInterface)       (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    STDMETHOD(CreateVMenu)          (THIS_ PIVOICECMDW, PVCMDNAME, HINSTANCE, DWORD, LPVOID, DWORD, PIVCMDMENUW*) PURE;
	STDMETHOD(AddVMenuCommand)      (THIS_ PIVCMDMENUW, LPTSTR, UINT, DWORD, DWORD) PURE;
	STDMETHOD(AddVMenuCommandsFromResource)( THIS_ PIVCMDMENUW pVMenu, HINSTANCE hinst,PCWSTR pszMenuName, DWORD  dwMenuState, DWORD dwFlag) PURE;

	STDMETHOD(Train)                (THIS_ LPCWSTR, DWORD, LPCWSTR, DWORD, DWORD=0, DWORD=0) PURE;

    STDMETHOD(QuerySpeakingMode)    (THIS_ DWORD*) PURE;
	STDMETHOD(PlaySound)			(THIS_ LPCWSTR, HMODULE, DWORD, DWORD) PURE;
    STDMETHOD(Speak)                (THIS_ WCHAR*, DWORD) PURE;
    STDMETHOD(SpeakEx)              (THIS_ DWORD, WCHAR*, DWORD, DWORD, PVOID) PURE;
    STDMETHOD(SpeakTime)            (THIS_ WCHAR* pszSpeak, SYSTEMTIME *systime, DWORD dwID, DWORD dwFlags) PURE;
    STDMETHOD(CreateSpkContext)     (THIS_ IAPCSpeech*, DWORD,DWORD,PDWORD) PURE;
    STDMETHOD(DestroySpkContext)    (THIS_ DWORD,DWORD) PURE;
    STDMETHOD(SetSpkContextRule)    (THIS_ DWORD,DWORD,LPCTSTR,LPCTSTR,LPVOID) PURE;

    STDMETHOD(VoiceHelpStart)       (THIS_ DWORD) PURE;
    STDMETHOD(VoiceHelpStop)        (THIS_ DWORD) PURE;
    
    STDMETHOD(AttribSet)            (THIS_ DWORD,DWORD) PURE;
    STDMETHOD(AttribGet)            (THIS_ DWORD,PDWORD) PURE;

    STDMETHOD(QuerySpeechInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD(SetMsgOptions)        (THIS_ DWORD,DWORD,DWORD) PURE;

    STDMETHOD(QueryFeedbackLevel)   (THIS_ PDWORD,PDWORD,PDWORD,DWORD) PURE;
};

#define CAPCSpeech	IAPCSpeech

//	function
IAPCSpeech* CreateAPCSpeech(DWORD dwThreadID,DWORD dwReserved);


#endif // _IAPCSPCH_H
