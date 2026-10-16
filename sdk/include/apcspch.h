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
/**
 * This message is sent when a phrase is recognized.
 *
 * The lParam contains the command identifier of the phrase that is recognized.
 *
 * If the application called AddVMenuCommand with a user-defined DWORD, the wParam will be that
 * DWORD. Otherwise it is zero.
 */
#define WM_SPCH_RECOG               (APC_SPCH_START+0x10)
/**
 * This message notifies the application of speech related activity.
 *
 * @param wParam It is one of the following values, depending on the options that are specified in
 *   the CreateAPCSpeechObject call: - VCMDRF_CMDSTART: The engine detects the beginning of a phrase.
 *   - VCMDRF_CMDOTHER: If lParam is nonzero, a phrase is recognized in another grammar. If lParam is
 *   zero, a phrase is ended without being recognized. - VCMDRF_ATTRIBCHANGE: Speech attributes have
 *   changed. - VTXTF_SPEAKDONE: The engine stopped speaking. - VTXTF_SPEAKSTOP: The engine's
 *   text-to-speech output was stopped by an application. - VTXTF_SPEAK: The engine encountered a
 *   bookmark. The lParam is the bookmark identifier.
 *
 * An application can embed "\mrk=xx\" strings inside the text to be spoken to create a bookmark.
 * When the speech engine encounters a bookmark, a WM_SPCH_NOTIFY message with wParam equal to
 * VTXTF_SPEAK and lParam equal to the bookmark identifier is posted to the application. The
 * traditional Speak(string, ID) also works because the system adds "\mrk=ID\" before the string and
 * then sends it to the engine.
 */
#define WM_SPCH_NOTIFY              (APC_SPCH_START+0x11)
/**
 * This message notifies the application of that a sound has finished.
 */
#define WM_SPCH_SNDDONE             (APC_SPCH_START+0x12)
/**
 * This message notifies the application of speech feedback.
 *
 * @param wParam The high order word is reserved. The low order word contains a description of the
 *   amount of information and detail currently provided in the speech feedback. It is one of the
 *   following values. - APCSPCH_FB_MORE: Provides a greater amount of feedback than APCSPCH_FB_LESS,
 *   usually adding either text-to speech (TTS) feedback or prerecorded speech feedback after the
 *   speech recognition tone. This additional feedback usually consists of application-specific
 *   information or the name of the application currently in use. - APCSPCH_FB_LESS: Provides minimal
 *   feedback.
 * @param lParam The high order word contains the reason for the initiation of speech feedback. It
 *   is one of the following values. - SFR_WAKEUPWORD: Speech feedback started because the user issued
 *   the "Wake Up" command. - SFR_PTT: Speech feedback started because the user pressed the
 *   push-to-talk key. - SFR_READ: Speech feedback started because the user issued the "Read" command.
 *   The low order word contains information specific to the reason in the high order word. If the
 *   high order word is SFR_WAKEUPWORD or SFR_PTT, then the low order word indicates the wake up state
 *   that existed when the event occurred. A value of 1 indicates that speech recognition was already
 *   awake when the event occurred. A value of 0 indicates that speech recognition was asleep when the
 *   event occurred.
 */
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


/**
 * This interface is a high level Auto PC simple speech interface.
 */
DECLARE_INTERFACE_(IAPCSpeech,IUnknown)
{
    // IUnknown members
    /**
     * This method retrieves a pointer to a IAPCSpeech interface.
     *
     * @param riid [in] Specifies the interface identifier (IID) of the interface being requested.
     * @param ppvObj [out] Pointer to an interface pointer to the object on return. If the interface
     *   specified in riid is not supported by the object, ppvObject is set to NULL.
     *
     * @return An appropriate HRESULT value is returned.
     */
    STDMETHOD(QueryInterface)       (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    /**
     * This method increments the reference count for an interface on a speech object.
     *
     * @return An appropriate HRESULT value is returned.
     */
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    /**
     * This method decrements the reference count for the calling interface on a speech object.
     *
     * @return An appropriate HRESULT value is returned.
     */
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    /**
     * This method creates a voice menu.
     *
     * @param pVCmd Pointer to a voice command. This parameter should be NULL unless the application
     *   creates the voice command.
     * @param lpName Long pointer to a unique VCMDNAME data type for each Apcspch object.
     * @param hInst Handle to the application or dynamic link library instance.
     * @param dwCmdCnt DWORD that indicates the total number of items in the array pointed to by
     *   pCmdTable.
     * @param pCmdTable Pointer to an array table of resource string identifiers.
     * @param dwFlags Bitmask of flags. Set to 0 or to APCSPCH_VM_USEEXISTING. When
     *   APCSPCH_VM_USEEXISTING is set and the application finds that the menu already exists, it uses the
     *   menu stored in the storage file. You can still pass in the string table pointer, but it is
     *   ignored if the APCSPCH_VM_USEEXISTING flag is set and there are commands in the menu. If a voice
     *   menu can be loaded or activated by two processes at the same time, the menu has to be created
     *   using the APCSPCH_VM_USEEXISTING flag. If the menu is created using APCSPCH_VM_USEEXISTING flag,
     *   the calls to AddVMenuCommand must pass APCSPCH_VM_USEEXISTING.
     * @param ppVMenu Pointer to a pointer to a voice menu.
     *
     * @return An appropriate HRESULT value is returned.
     *
     * The second parameter of the CreateVMenu method is the VCMDNAME structure, which contains both the
     * application name and menu name. The application has to pass both the application
     * name-essentially, a context name-and menu name when creating a voice menu. For example, when the
     * edit control creates a menu, it can use the application name "EditCtrl," and an address book DLL
     * can use the application name "AddrBook."
     *
     * When a control or shared DLL wants to create a menu that is shared across all the instances, it
     * should use the flag APCSPCH_VM_USEEXISTING and pass in the same application name and menu name in
     * every instance of the control. However, if a control has a different voice menu in different
     * instances, it should use a unique menu name. If not, the CreateVMenu fails and returns a
     * VCMDERR_MENUEXIST error value.
     *
     * The caller is responsible for releasing the menu object by calling Release. To create a default
     * menu, pVCmd should be NULL. If the application has another voice command, it can pass it to
     * pVCmd.
     *
     * The application should call the Activate and Deactivate methods to activate or deactivate the
     * application grammar.
     */
    STDMETHOD(CreateVMenu)          (THIS_ PIVOICECMDW, PVCMDNAME, HINSTANCE, DWORD, LPVOID, DWORD, PIVCMDMENUW*) PURE;
	/**
	 * This method adds a command to the voice menu.
	 *
	 * @param pMenu Pointer to the menu to which a command is to be added.
	 * @param szCmdString Null-terminated string that contains the command that is to be added to pMenu.
	 *   The command string added to a voice menu includes three parts: command, long voice Help and short
	 *   voice Help. The three parts are separated by a tab. The following table shows possible
	 *   combinations. Command Description cmd\tlong Help\tshort Help Has both long and short voice Help.
	 *   cmd There is no long voice Help, and short voice Help is the same as command. cmd\t\tshort Help
	 *   There is no long voice Help, and short voice Help is different from command. cmd\tlong Help\t Has
	 *   long voice Help but no short voice Help. cmd\tlong Help Has long voice Help, and short voice Help
	 *   is the same as command.
	 * @param dwCmdID Specifies the command identifier that is to be added to the voice menu.
	 * @param dwFlags Specifies a bitmask for flags. It is one of the following values: -
	 *   APCSPCH_VM_USEEXISTING: If this flag is set and the command identifier already exists in the
	 *   voice menu, the command is not added. - APCSPCH_VM_NOFEEDBACK: Use this flag if the application
	 *   does not want the system to provide the regular feedback to this word
	 * @param dwVoiceCommand Application developer can associate a DWORD with the voice command. When
	 *   the command is recognized, this DWORD is notified in the wParam of WM_SPCH_RECOG. The lParam is
	 *   the command identifier.
	 *
	 * @return An appropriate HRESULT value is returned.
	 *
	 * To avoid duplicating string identifiers if your application uses speech enabled controls, use the
	 * ranges shown in the following table to assign string identifiers in resource file.
	 *
	 * String identifier Range Application 0 to 0x7FFF Speech enabled controls 0x8000 to 0xFFFF
	 *
	 * The string that is passed can be separated by a tab to include context-sensitive long voice Help
	 * and short voice Help strings. For more information, see VoiceHelpStart.
	 */
	STDMETHOD(AddVMenuCommand)      (THIS_ PIVCMDMENUW, LPTSTR, UINT, DWORD, DWORD) PURE;
	/**
	 * This method adds commands from a resource file to a voice menu.
	 *
	 * @param pVMenu Pointer to the menu to which commands are to be added.
	 * @param hinst Handle to the application instance.
	 * @param pszMenuName Pointer to the null-terminated string that contains the name of the menu.
	 * @param dwMenuState Specifies a DWORD that contains the state of the menu.
	 * @param dwFlag Specifies a DWORD that contains a flag.
	 *
	 * @return An appropriate HRESULT value is returned.
	 *
	 * Voice menus can be defined in a resource file. Each menu item has a string, an identifier, and a
	 * state. Create a voice menu with CreateVMenu passing in a null list of grammar identifiers. Then
	 * call AddVMenuCommandsFromResource, passing in your resource identifier and instance. The items
	 * are added to the existing menu, as shown in the following code example:
	 *
	 *     // Create a voice menu resource.
	 *     IDVM_ASEDIT MENUEX PRELOAD DISCARDABLE
	 *     BEGIN
	 *         MENUITEM "One\tTo enter numbers, say Zero through Nine", VC_ONE,
	 *         0, VMS_NUMBERS
	 *         MENUITEM "Two", VC_TWO, 0, VMS_NUMBERS
	 *         MENUITEM "Three", VC_THREE, 0, VMS_NUMBERS
	 *         MENUITEM "Four", VC_FOUR, 0, VMS_NUMBERS
	 *         MENUITEM "Five", VC_FIVE, 0, VMS_NUMBERS
	 *         MENUITEM "Six", VC_SIX, 0, VMS_NUMBERS
	 *         MENUITEM "Seven", VC_SEVEN, 0, VMS_NUMBERS
	 *         MENUITEM "Eight", VC_EIGHT, 0, VMS_NUMBERS
	 *         MENUITEM "Nine", VC_NINE, 0, VMS_NUMBERS
	 *         MENUITEM "Zero", VC_ZERO, 0, VMS_NUMBERS
	 *         MENUITEM "Review\tTo read what you have entered, say Review"
	 *         VC_REVIEW, 0, VMS_REVIEW
	 *         MENUITEM "Delete\tTo remove the current character, say Delete",
	 *         VC_DELETE, 0, VMS_DELETE
	 *         MENUITEM "Ok\tTo keep your changes, say Okay", VC_OK, 0, VMS_OK
	 *         MENUITEM "Cancel\tTo cancel your changes, say Cancel", VC_CANCEL, 0,
	 *         VMS_CANCEL
	 *     END
	 *     // IDVM_ASEDIT and all of the VMS_* parameters are specific to the
	 *     // application. The last flag enables the application to
	 *     // define multiple states in which the menu can be loaded. Therefore,
	 *     // one menu resource can be used to load two voice menus: one for an edit mode and one for a review mode, if both exist.
	 *
	 *     // Create an empty voice menu.
	 *     CreateVMenu(
	 *         NULL,
	 *         &vn,
	 *         m_hInst,
	 *         0,
	 *         NULL,
	 *         APCSPCH_VM_USEEXISTING,
	 *         &m_pVoiceMenuCards );
	 *
	 *     // Load in an voice command from a resource.
	 *         if (SUCCEEDED( hr))
	 *         {
	 *         hr = m_pSpeech->AddVMenuCommandsFromResource(
	 *         m_pVoiceMenuCards, m_hInst,
	 *     MAKEINTRESOURCE(IDVM_CARDS), 0, APCSPCH_VM_USEEXISTING);
	 *         }
	 *     // By loading a menu from a resource file, you can use the same voice command and corresponding identifier in several applications, even though the voice command may differ in each. For example, the word PREVIOUS can have the same identifier whether it moves you back a screen in one application and restores the former settings of another application. Loading a menu from a resource file also enables more consistent coding, and enables the voice command to behave like a keystroke rather than a custom identifier.
	 */
	STDMETHOD(AddVMenuCommandsFromResource)( THIS_ PIVCMDMENUW pVMenu, HINSTANCE hinst,PCWSTR pszMenuName, DWORD  dwMenuState, DWORD dwFlag) PURE;

	/**
	 * This method trains the application to recognize a user command, and deals with only one command
	 * at a time.
	 *
	 * @param pszTrain Pointer to the phrase to train the application to recognize. Support for a list
	 *   of words may be added in the future.
	 * @param cbTrain Byte count of pszTrain.
	 * @param pszDisplay Pointer to the null-terminated string that contains the phrase to display.
	 *   Support for a list of words will be added in the future. This parameter is optional argument and
	 *   can be NULL.
	 * @param cbDisplay Byte count of pszDisplay.
	 * @param d1 Reserved; set to 0.
	 * @param d2 Reserved; set to 0.
	 *
	 * @return S_FALSE indicates that training was canceled. This can occur if the user chooses ESCAPE
	 *   during the training or performs an action that causes the form to lose focus, such as pressing
	 *   the START button. E_FAIL indicates that training has failed. This can occur if the user does not
	 *   speak the word within the timeout period.
	 *
	 * This method results in a pop-up training form to help the user train the application to recognize
	 * a word or command. The method is blocked until the training is finished or canceled.
	 */
	STDMETHOD(Train)                (THIS_ LPCWSTR, DWORD, LPCWSTR, DWORD, DWORD=0, DWORD=0) PURE;

    /**
     * This method gets whether or not the operating system is playing a text-to-speech (TTS) phrase or
     * prerecorded speech.
     *
     * @param pdwMode Pointer to a DWORD that indicates the current mode for speech. It is one of the
     *   following values. - 0: The operating system (OS) is playing neither a TTS phrase nor prerecorded
     *   speech. - APCSPCH_SP_TTS: The OS is playing TTS. - APCSPCH_SP_WAVEFILE: The OS is playing a
     *   waveform (WAV) file containing prerecorded speech.
     *
     * @return NOERROR indicates success. VCMDERR_INVALIDPARAM indicates that pdwMode is not a valid
     *   write pointer.
     */
    STDMETHOD(QuerySpeakingMode)    (THIS_ DWORD*) PURE;
	/**
	 * This method plays a prerecorded speech sound file.
	 *
	 * @param lpcwSound Long pointer to a string that specifies the sound file to play.
	 * @param hModule Handle of the executable file that contains the resource to be loaded.
	 * @param dwSound Specifies the flag for playing the sound. The following values are defined:
	 *   SND_APPLICATION SND_NODEFAULT SND_ALIAS SND_NOSTOP SND_ALIAS_ID SND_NOWAIT SND_ASYNC SND_PURGE
	 *   SND_FILENAME SND_RESOURCE SND_LOOP SND_SYNC SND_MEMORY For more information about these flags,
	 *   see the Windows CE PlaySound function.
	 * @param dwReserved If this parameter is nonzero, the application receives a WM_SPCH_SNDDONE
	 *   message when the wave file is finished playing. If it is set to zero, no message is sent.
	 *
	 * @return An appropriate HRESULT value is returned.
	 *
	 * Always use this method to play prerecorded speech. Besides playing the sound file, this method
	 * also attenuates the music and disables speech recognition during playback. This method uses the
	 * same waveform (WAV) output device as the text-to-speech (TTS) engine. If TTS is playing,
	 * IAPCSpeech::PlaySound stops TTS. TTS also stops the Windows CE PlaySound function if that
	 * function is in progress. For event sounds, use the Windows CE sndPlaySound function, which uses a
	 * different WAV output device than IAPCSpeech::PlaySound and TTS.
	 */
	STDMETHOD(PlaySound)			(THIS_ LPCWSTR, HMODULE, DWORD, DWORD) PURE;
    /**
     * This method speaks the null-terminated string stored in pszSpeak using text-to-speech (TTS).
     *
     * @param pszSpeak Pointer to the null-terminated string that contains the text to be spoken. The
     *   length of the string must be less than 2 kilobytes (KB). Strings longer than 2 KB cause
     *   unexpected speech behavior.
     * @param wID Unsigned 16-bit integer that contains the bookmark identifier. This parameter is
     *   ignored if it is 0.
     *
     * @return An appropriate HRESULT value is returned.
     *
     * If the parameter is NULL, speech output is stopped.
     *
     * This method always uses the default speak context, which is 0.
     */
    STDMETHOD(Speak)                (THIS_ WCHAR*, DWORD) PURE;
    /**
     * This method speaks the null-terminated string stored in pszSpeak using text-to-speech (TTS).
     *
     * @param dwContext Specifies the context to use for text normalization while speaking phrase.
     * @param pszSpeak Pointer to the null-terminated string that contains the text to be spoken. The
     *   length of the string must be less than 2 kilobytes (KB). Strings longer than 2 KB cause
     *   unexpected speech behavior.
     * @param dwID Specifies the bookmark identifier. This parameter is ignored if it is 0.
     * @param dwFlag Specifies a bitmask of flags. It is one of the following values: - 0: Plays the TTS
     *   in the foreground and does not spell out words or speak individual digits. This value is the
     *   default value. - APCSPCH_SP_BACKGROUND: Plays the TTS in the background, preventing interruptions
     *   caused by normal keystrokes or by a PUSH TO TALK button. - APCSPCH_TN_SPELLING_CTX: Speaks the
     *   letters and digits in pszSpeak individually, instead of using words or using numbers larger than
     *   9.
     * @param p Reserved; set to 0.
     *
     * @return An appropriate HRESULT value is returned.
     *
     * The APCSPCH_SP_BACKGROUND flag should be used only when you are certain that you want to play the
     * TTS in the background.
     */
    STDMETHOD(SpeakEx)              (THIS_ DWORD, WCHAR*, DWORD, DWORD, PVOID) PURE;
    STDMETHOD(SpeakTime)            (THIS_ WCHAR* pszSpeak, SYSTEMTIME *systime, DWORD dwID, DWORD dwFlags) PURE;
    /**
     * This method creates a new speak context, which allows an application to do pre-text
     * normalization.
     *
     * @param pSpeech Pointer to a speech object that contains the dwContext to be copied; used only
     *   with APCSPCH_TN_CONTEXT_COPY.
     * @param dwContext Specifies the context identifier of the newly created context that is copied or
     *   extended. It is ignored if dwFlag is APCSPCH_TN_CONTEXT_NEW.
     * @param dwFlag Specifies a bitmask of flags. It is one of the following values: Flag Value
     *   Description APCSPCH_TN_CONTEXT_NEW 0x0001 Creates a new empty context. APCSPCH_TN_CONTEXT_COPY
     *   0x0002 Creates a new context based on an existing context by copying all the rules from the
     *   existing context. APCSPCH_TN_CONTEXT_EXTEND 0x0003 Extends a new context by linking it to an
     *   existing one.
     * @param pNewContext Pointer to the identifier of the newly created context if S_OK is returned.
     *
     * @return S_OK indicates success.
     *
     * An application does not need to create a new speak context in order to use text-to-speech (TTS)
     * because, by default, there is always one speak context with an identifier of 0. An application
     * can also create additional contexts and use IAPCSpeech::SpeakEx to use the new contexts.
     *
     * When APCSPCH_TN_CONTEXT_EXTEND is used, it can only extend rules of APCSPCH_TN_WORD.
     *
     * A context can only be extended once.
     */
    STDMETHOD(CreateSpkContext)     (THIS_ IAPCSpeech*, DWORD,DWORD,PDWORD) PURE;
    /**
     * This method destroys a speak context.
     *
     * @param dwContext Specifies the speech context.
     * @param dwFlag Reserved; set to 0.
     *
     * @return An appropriate HRESULT value is returned.
     */
    STDMETHOD(DestroySpkContext)    (THIS_ DWORD,DWORD) PURE;
    /**
     * This method sets a context rule used to normalize a text string before sending the string to the
     * text-to-speech (TTS) engine.
     *
     * @param dwContextID Specifies the identifier of the context that new rule belongs to.
     * @param dwFlags Specifies a bitmask for flags. It is one of the following values: -
     *   APCSPCH_TN_ADDR_CTX: Used with an address context. - APCSPCH_TN_PHONE_CTX: Used with a telephone
     *   context. When text contains three numbers and a dash, it is interpreted as a phone number. -
     *   APCSPCH_TN_SPELLING_CTX: Spells out a string letter by letter. - APCSPCH_TN_WORD: Replaces or
     *   deletes a word.
     * @param lpctStr1 Long pointer to the string to be replaced.
     * @param lpctStr2 Long pointer to the string that replaces lpctStr1. If NULL, lpctStr1 is removed.
     * @param p Reserved; set to 0.
     *
     * @return An appropriate HRESULT value is returned.
     *
     * The following can be used as delimiters for this method:
     *
     * White space
     *
     * Commas
     *
     * Periods
     *
     * Backslashes
     *
     * In an address. numbers are usually pronounced differently. For example, 98052 would be
     * "9-8-0-5-2," while 5345 would be "fifty-three forty-five." To use this special context, the
     * application can create a text-to-speech (TTS) context and pass APCSPCH_TN_ADDR_CTX as the dwFlag
     * in the SetSpkContextRule method.
     *
     * For APCSPCH_TN_PHONE_CTX, the TTS engine pronounces the pound sign (#) as "pound," and the
     * asterisk (*) as "star." The left brace, right brace, left bracket, right bracket, left
     * parenthesis, right parenthesis, comma, period, caret, and space characters result in a pause in
     * speech. The TTS engine combines multiple pauses into a single pause. The TTS engine always
     * pronounces the number 0 as "zero." The TTS engine pronounces digits and letters individually,
     * rather than stringing them together as large numbers or words.
     *
     * If APCSPCH_TN_PHONE_CTX or APCSPCH_TN_SPELLING is set, all other flags are ignored.
     *
     * APCSPCH_TN_WORD and APCSPCH_TN_ADDR_CTX can be combined.
     */
    STDMETHOD(SetSpkContextRule)    (THIS_ DWORD,DWORD,LPCTSTR,LPCTSTR,LPVOID) PURE;

    /**
     * This method is called by the shell to start voice Help.
     *
     * @param dwType Specifies a DWORD that contains the type of Help to start. It is one of the
     *   following values: - APCSPCH_VH_LONGHELP: Starts long Help after the "Help" speech command is
     *   recognized. - APCSPCH_VH_SHORTHELP: Starts short Help after the "What can I say?" speech command
     *   is recognized. - APCSPCH_VH_LISTGLOBAL: Instructs Help to list the global commands.
     *
     * @return An appropriate HRESULT value is returned.
     *
     * The application must not call VoiceHelpStart or VoiceHelpStop.
     *
     * Short Help lists all of the active speech commands by playing waveform (WAV) files that you
     * provide. The Help system can only find the WAV file if the name of the WAV file is the same as
     * the string used for the speech command. For example, short Help lists the volume command only if
     * there is a file named Volume.wav in the \Windows directory. If the appropriate file does not
     * exist, short Help does not list the command.
     *
     * The command strings the application adds to the voice menu should be used to include the long and
     * short voice Help strings, separated by tabs. The first string is the command string, the second
     * is the long voice Help string. The third string is optional, and specifies a string to use for
     * short voice Help instead of the command string.
     *
     * The following table contains possible long and short voice Help combinations.
     *
     * Command Description cmd\tlong Help\tshort Help Has both long and short Help. cmd There is no long
     * Help, and short Help is the same as command. cmd\t\tshort Help There is no long Help, and short
     * Help is different from command. cmd\tlong Help\t Has long Help but no short Help. cmd\tlong Help
     * Has long Help, and short Help is the same as command.
     */
    STDMETHOD(VoiceHelpStart)       (THIS_ DWORD) PURE;
    /**
     * This method is called by the shell to stop voice Help.
     *
     * @param dwReserved Reserved; set to 0
     *
     * @return An appropriate HRESULT value is returned.
     *
     * The application must not call VoiceHelpStart or VoiceHelpStop.
     */
    STDMETHOD(VoiceHelpStop)        (THIS_ DWORD) PURE;
    
    /**
     * This method sets or changes speech related settings.
     *
     * @param dwAttrib An application passes the IVANSAC_TTSPITCH flag to get the current text-to-speech
     *   (TTS) pitch.
     * @param dwMisc Specifies the desired pitch value.
     *
     * @return An appropriate HRESULT value is returned.
     *
     * The AttribGet and AttribSet methods are now called by the shell and the Control Panel
     * applications. Your application should not call them.
     */
    STDMETHOD(AttribSet)            (THIS_ DWORD,DWORD) PURE;
    /**
     * This method gets speech related settings.
     *
     * @param dwAttrib An application passes the IVANSAC_TTSPITCH flag to get the current text-to-speech
     *   (TTS) pitch.
     * @param pdwMisc Pointer to the DWORD that contains the desired pitch value.
     *
     * @return An appropriate HRESULT value is returned.
     *
     * The AttribGet and AttribSet methods are now called by the shell and the Control Panel
     * applications. Your application should not call them.
     */
    STDMETHOD(AttribGet)            (THIS_ DWORD,PDWORD) PURE;

    /**
     * This method queries for the voice command and voice text interfaces.
     *
     * @param riid [in] Specifies the interface identifier (IID) of the interface being requested.
     * @param ppvObj [out] Pointer to an interface pointer to the object on return. If the interface
     *   specified in riid is not supported by the object, ppvObject is set to NULL.
     *
     * @return An appropriate HRESULT value is returned.
     *
     * The application can call QuerySpeechInterface to obtain the IID_IVoiceCmd, IID_IVoiceText, and
     * other related voice command and voice text interface pointers.
     *
     * The speech object registers a notification sink; therefore, it is not necessary or possible to
     * register your own using a voice command and voice text interface pointer.
     */
    STDMETHOD(QuerySpeechInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    /**
     * This method sets options for message notifications.
     *
     * @param dwFlags Reserved; set to 0.
     * @param dwVCmdOpt Specifies options for the voice command notifications. It is one or a both of
     *   the following values: VCMDRF_CMDOTHER VCMDRF_CMDSTART
     * @param dwVCmdOpt Specifies options for the voice text notifications. It is one or a combination
     *   of the following values: VTXTF_SPEAKSTART VTXTF_SPEAKDONE
     *
     * @return An appropriate HRESULT value is returned.
     *
     * By default, the applications always receive the following speech notifications:
     *
     * WM_SPCH_RECOG, where wParam is the DWORD associated with the command and lParam is the command
     * identifier.
     *
     * WM_SPCH_SNDDONE indicates that the wave file played by sndPlaySound is done.
     *
     * WM_SPCH_NOTIFY, where wParam equals VCMDRF_ATTRIBCHANGE, VTXTF_SPEAK, or VTXT_SPEAKSTOP.
     *
     * SetMsgOptions can be used to enable an application to receive in wParam the four additional
     * WM_SPCH_NOTIFY messages set in dwVCmdOpt and dwVCmdOpt.
     *
     * Once SetMsgOptions has been called with VTXTF_SPEAKSTART, VTXTF_SPEAKSTOP, or both, it cannot be
     * called again to reset the option.
     */
    STDMETHOD(SetMsgOptions)        (THIS_ DWORD,DWORD,DWORD) PURE;

    /**
     * This method retrieves a description of the amount of information and detail provided in the
     * feedback for key response and for voice commands.
     *
     * @param pKeyFeedback Pointer to a DWORD that receives a description of the amount of information
     *   and detail provided in the feedback for key response. It is one of the following values. -
     *   APCSPCH_FB_MORE: Provides a greater amount of feedback than APCSPCH_FB_LESS, usually adding
     *   either text-to speech (TTS) feedback or prerecorded speech feedback after the speech recognition
     *   tone. This additional feedback usually consists of application-specific information or the name
     *   of the application currently in use. - APCSPCH_FB_LESS: Provides minimal feedback.
     * @param pVoiceFeedback Pointer to a DWORD that receives a description of the amount of information
     *   and detail provided in the feedback for voice commands. It is one of the following values. -
     *   APCSPCH_FB_MORE: Provides a greater amount of feedback than APCSPCH_FB_LESS, usually adding
     *   either text-to speech (TTS) feedback or prerecorded speech feedback after the speech recognition
     *   tone. This additional feedback usually consists of application-specific information or the name
     *   of the application currently in use. - APCSPCH_FB_LESS: Provides minimal feedback.
     * @param pReserved Reserved for future use; set to 0.
     * @param dwFlag Reserved for future use; set to 0.
     *
     * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
     *
     * An application does not need to call this method every time the application provides speech
     * feedback. Instead, an application should only call this method during the initialization of the
     * application. If the feedback level changes, the application receives a WM_SETTINGCHANGE message
     * that has a wParam value equal to SPI_SETAPCFEEDBACK and a lParam value equal to NULL. An
     * application should call IAPCSpeech::QueryFeedbackLevel again when the application receives this
     * WM_SETTINGCHANGE message.
     *
     * The IAPCSpeech interface always plays the feedback tone when hearing a voice command. When the
     * application receives notification of the voice command, the application should play a
     * text-to-speech (TTS) phrase or prerecorded speech if pVoiceFeedback is APCSPCH_FB_MORE.
     *
     * For version 1.0, an application usually does not need to call this method to provide appropriate
     * feedback information, because the shell and the form manager provide most of the feedback for the
     * application. Additionally, the application receives a WM_SPCH_FEEDBACK message containing the
     * feedback level in the low order word of the wParam of the message.
     */
    STDMETHOD(QueryFeedbackLevel)   (THIS_ PDWORD,PDWORD,PDWORD,DWORD) PURE;
};

#define CAPCSpeech	IAPCSpeech

//	function
IAPCSpeech* CreateAPCSpeech(DWORD dwThreadID,DWORD dwReserved);


#endif // _IAPCSPCH_H
