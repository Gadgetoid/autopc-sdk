/*****************************************************************8
Speech.H - Header file to use the Microsoft Speech APIs.

Copyright 1994, 1995 by Microsoft corporation.All rights reserved.
*/

#ifndef _SPEECH_
#define _SPEECH_

// Disable the warning for zero-length arrays in structures
#pragma warning(disable:4200)


/************************************************************************
Defines common to all of the speech APIs.
*/

// Application  Speech API   Compiler Defines                   _S_UNICODE
// -----------------------------------------------------------------------------
//   ANSI        ANSI        <none>                             undefined
//   ANSI        Unicode     _S_UNICODE                         defined
//   Unicode     ANSI        (UNICODE || _UNICODE) && _S_ANSI   undefined
//   Unicode     Unicode     (UNICODE || _UNICODE)              defined

#if (defined(UNICODE) || defined(_UNICODE)) && !defined(_S_ANSI)
#ifndef _S_UNICODE
#define _S_UNICODE
#endif
#endif

/************************************************************************
defines */
#define  SVFN_LEN    (262)
#define  LANG_LEN    (64)
#define  EI_TITLESIZE   (128)
#define  EI_DESCSIZE    (512)
#define  EI_FIXSIZE     (512)
#define  SVPI_MFGLEN    (64)
#define  SVPI_PRODLEN   (64)
#define  SVPI_COMPLEN   (64)
#define  SVPI_COPYRIGHTLEN (128)
#define  SVI_MFGLEN     (SVPI_MFGLEN)
#define  SETBIT(x)      ((DWORD)1 << (x))


// Error Macros
#define  FACILITY_SPEECH   (FACILITY_ITF)
#define  SPEECHERROR(x)    MAKE_SCODE(SEVERITY_ERROR,   FACILITY_SPEECH, (x)+0x200)
#define  AUDERROR(x)       MAKE_SCODE(SEVERITY_ERROR,   FACILITY_SPEECH, (x)+0x300)
#define  SRWARNING(x)      MAKE_SCODE(SEVERITY_SUCCESS, FACILITY_SPEECH, (x)+0x400)
#define  SRERROR(x)        MAKE_SCODE(SEVERITY_ERROR,   FACILITY_SPEECH, (x)+0x400)
#define  TTSERROR(x)       MAKE_SCODE(SEVERITY_ERROR,   FACILITY_SPEECH, (x)+0x500)
#define  VCMDERROR(x)      MAKE_SCODE(SEVERITY_ERROR,   FACILITY_SPEECH, (x)+0x600)
#define  VTXTERROR(x)      MAKE_SCODE(SEVERITY_ERROR,   FACILITY_SPEECH, (x)+0x700)
#define  LEXERROR(x)       MAKE_SCODE(SEVERITY_ERROR,   FACILITY_SPEECH, (x)+0x800)

// Audio Errors
#define  AUDERR_NONE                      S_OK                          // 0x00000000
#define  AUDERR_BADDEVICEID               AUDERROR(1)                   // 0x80040301
#define  AUDERR_NEEDWAVEFORMAT            AUDERROR(2)                   // 0x80040302
#define  AUDERR_NOTSUPPORTED              E_NOTIMPL                     // 0x80004001
#define  AUDERR_NOTENOUGHDATA             SPEECHERROR(1)                // 0x80040201
#define  AUDERR_NOTPLAYING                AUDERROR(6)                   // 0x80040306
#define  AUDERR_INVALIDPARAM              E_INVALIDARG                  // 0x80070057
#define  AUDERR_WAVEFORMATNOTSUPPORTED    SPEECHERROR(2)                // 0x80040202
#define  AUDERR_WAVEDEVICEBUSY            SPEECHERROR(3)                // 0x80040203
#define  AUDERR_WAVEDEVNOTSUPPORTED       AUDERROR(18)                  // 0x80040312
#define  AUDERR_NOTRECORDING              AUDERROR(19)                  // 0x80040313
#define  AUDERR_INVALIDFLAG               SPEECHERROR(4)                // 0x80040204
#define  AUDERR_INVALIDHANDLE             E_HANDLE                      // 0x80070006
#define  AUDERR_NODRIVER                  AUDERROR(23)                  // 0x80040317
#define  AUDERR_HANDLEBUSY                AUDERROR(24)                  // 0x80040318
#define  AUDERR_INVALIDNOTIFYSINK         AUDERROR(25)                  // 0x80040319
#define  AUDERR_WAVENOTENABLED            AUDERROR(26)                  // 0x8004031A
#define  AUDERR_ALREADYCLAIMED            AUDERROR(29)                  // 0x8004031D
#define  AUDERR_NOTCLAIMED                AUDERROR(30)                  // 0x8004031E
#define  AUDERR_STILLPLAYING              AUDERROR(31)                  // 0x8004031F
#define  AUDERR_ALREADYSTARTED            AUDERROR(32)                  // 0x80040320
#define  AUDERR_SYNCNOTALLOWED            AUDERROR(33)                  // 0x80040321

// Speech Recognition Warnings
#define  SRWARN_BAD_LIST_PRONUNCIATION    SRWARNING(1)

// Speech Recognition Errors
#define  SRERR_NONE                       S_OK                          // 0x00000000
#define  SRERR_OUTOFDISK                  SPEECHERROR(5)                // 0x80040205
#define  SRERR_NOTSUPPORTED               E_NOTIMPL                     // 0x80004001
#define  SRERR_NOTENOUGHDATA              AUDERR_NOTENOUGHDATA          // 0x80040201
#define  SRERR_VALUEOUTOFRANGE            E_UNEXPECTED                  // 0x8000FFFF
#define  SRERR_GRAMMARTOOCOMPLEX          SRERROR(6)                    // 0x80040406
#define  SRERR_GRAMMARWRONGTYPE           SRERROR(7)                    // 0x80040407
#define  SRERR_INVALIDWINDOW              OLE_E_INVALIDHWND             // 0x8004000F
#define  SRERR_INVALIDPARAM               E_INVALIDARG                  // 0x80070057
#define  SRERR_INVALIDMODE                SPEECHERROR(6)                // 0x80040206
#define  SRERR_TOOMANYGRAMMARS            SRERROR(11)                   // 0x8004040B
#define  SRERR_INVALIDLIST                SPEECHERROR(7)                // 0x80040207
#define  SRERR_WAVEDEVICEBUSY             AUDERR_WAVEDEVICEBUSY         // 0x80040203
#define  SRERR_WAVEFORMATNOTSUPPORTED     AUDERR_WAVEFORMATNOTSUPPORTED // 0x80040202
#define  SRERR_INVALIDCHAR                SPEECHERROR(8)                // 0x80040208
#define  SRERR_GRAMTOOCOMPLEX             SRERR_GRAMMARTOOCOMPLEX       // 0x80040406
#define  SRERR_GRAMTOOLARGE               SRERROR(17)                   // 0x80040411
#define  SRERR_INVALIDINTERFACE           E_NOINTERFACE                 // 0x80004002
#define  SRERR_INVALIDKEY                 SPEECHERROR(9)                // 0x80040209
#define  SRERR_INVALIDFLAG                AUDERR_INVALIDFLAG            // 0x80040204
#define  SRERR_GRAMMARERROR               SRERROR(22)                   // 0x80040416
#define  SRERR_INVALIDRULE                SRERROR(23)                   // 0x80040417
#define  SRERR_RULEALREADYACTIVE          SRERROR(24)                   // 0x80040418
#define  SRERR_RULENOTACTIVE              SRERROR(25)                   // 0x80040419
#define  SRERR_NOUSERSELECTED             SRERROR(26)                   // 0x8004041A
#define  SRERR_BAD_PRONUNCIATION          SRERROR(27)                   // 0x8004041B
#define  SRERR_DATAFILEERROR              SRERROR(28)                   // 0x8004041C
#define  SRERR_GRAMMARALREADYACTIVE       SRERROR(29)                   // 0x8004041D
#define  SRERR_GRAMMARNOTACTIVE           SRERROR(30)                   // 0x8004041E
#define  SRERR_GLOBALGRAMMARALREADYACTIVE SRERROR(31)                   // 0x8004041F
#define  SRERR_LANGUAGEMISMATCH           SRERROR(32)                   // 0x80040420
#define  SRERR_MULTIPLELANG               SRERROR(33)                   // 0x80040421
#define  SRERR_LDGRAMMARNOWORDS           SRERROR(34)                   // 0x80040422
#define  SRERR_NOLEXICON                  SRERROR(35)                   // 0x80040423
#define  SRERR_SPEAKEREXISTS              SRERROR(36)                   // 0x80040424
#define  SRERR_GRAMMARENGINEMISMATCH      SRERROR(37)                   // 0x80040425
#define  SRERR_BOOKMARKEXISTS             SRERROR(38)                   // 0x80040426
#define  SRERR_BOOKMARKDOESNOTEXIST       SRERROR(39)                   // 0x80040427
#define  SRERR_MICWIZARDCANCELED          SRERROR(0x28)                   // 0x80040428

#define SRERR_PHRASENOTFOUND    SRERROR(0x30)                   // 0x80040430
#define SRERR_TEMPLATENOTFOUND  SRERROR(0x31)                   // 0x80040431
#define SRERR_TRAININGBUSY      SRERROR(0x33)                   // 0x80040433
#define SRERR_GOBACKFAILED      SRERROR(0x34)                   // 0x80040434
#define SRERR_RECOGBUSY         SRERROR(0x35)                   // 0x80040435
#define SRERR_ENGINESPECIFIC    SRERROR(0x36)                   // 0x80040436

// Text to Speech Errors
#define  TTSERR_NONE                      S_OK                          // 0x00000000
#define  TTSERR_INVALIDINTERFACE          E_NOINTERFACE                 // 0x80004002
#define  TTSERR_OUTOFDISK                 SRERR_OUTOFDISK               // 0x80040205
#define  TTSERR_NOTSUPPORTED              E_NOTIMPL                     // 0x80004001
#define  TTSERR_VALUEOUTOFRANGE           E_UNEXPECTED                  // 0x8000FFFF
#define  TTSERR_INVALIDWINDOW             OLE_E_INVALIDHWND             // 0x8004000F
#define  TTSERR_INVALIDPARAM              E_INVALIDARG                  // 0x80070057
#define  TTSERR_INVALIDMODE               SRERR_INVALIDMODE             // 0x80040206
#define  TTSERR_INVALIDKEY                SRERR_INVALIDKEY              // 0x80040209
#define  TTSERR_WAVEFORMATNOTSUPPORTED    AUDERR_WAVEFORMATNOTSUPPORTED // 0x80040202
#define  TTSERR_INVALIDCHAR               SRERR_INVALIDCHAR             // 0x80040208
#define  TTSERR_QUEUEFULL                 SPEECHERROR(10)               // 0x8004020A
#define  TTSERR_WAVEDEVICEBUSY            AUDERR_WAVEDEVICEBUSY         // 0x80040203
#define  TTSERR_NOTPAUSED                 TTSERROR(1)                   // 0x80040501
#define  TTSERR_ALREADYPAUSED             TTSERROR(2)                   // 0x80040502


// Voice Command Errors

/*
 *  Everything worked
 */
#define  VCMDERR_NONE                     S_OK                          // 0x00000000

/*
 *  Voice Commands could not allocate memory
 */
#define  VCMDERR_OUTOFMEM                 E_OUTOFMEMORY                 // 0x8007000E

/*
 *  Voice Commands could not store/retrieve a command set from the database
 */
#define  VCMDERR_OUTOFDISK                SRERR_OUTOFDISK               // 0x80040205

/*
 *  Function not implemented
 */
#define  VCMDERR_NOTSUPPORTED             E_NOTIMPL                     // 0x80004001

/*
 *  A parameter was passed that was out of the ranged of accepted values
 */
#define  VCMDERR_VALUEOUTOFRANGE          E_UNEXPECTED                  // 0x8000FFFF

/*
 *  A menu was too complex to compile a context-free grammar
 */
#define  VCMDERR_MENUTOOCOMPLEX           VCMDERROR(0x06)               //  0x80040606

/*
 *  Language mismatch between the speech recognition mode and menu trying
 *  to create
 */
#define  VCMDERR_MENUWRONGLANGUAGE        VCMDERROR(0x07)               // 0x80040607

/*
 *  An invalid window handle was passed to Voice Commands
 */
#define  VCMDERR_INVALIDWINDOW            OLE_E_INVALIDHWND             // 0x8004000F

/*
 *  Voice Commands detected a bad function parameter
 */
#define  VCMDERR_INVALIDPARAM             E_INVALIDARG                  // 0x80070057

/*
 *  This function cannot be completed right now, usually when trying to do
 *  some operation while no speech recognition site is established
 */
#define  VCMDERR_INVALIDMODE              SRERR_INVALIDMODE             // 0x80040206

/*
 *  There are too many Voice Commands menu
 */                                                                     // 0x8004060B
#define  VCMDERR_TOOMANYMENUS             VCMDERROR(0x0B)

/*
 *  Invalid list passed to ListSet/ListGet
 */
#define  VCMDERR_INVALIDLIST              SRERR_INVALIDLIST             // 0x80040207

/*
 *  Trying to open an existing menu that is not in the Voice Commands database
 */
#define  VCMDERR_MENUDOESNOTEXIST         VCMDERROR(0x0D)               // 0x8004060D

/*
 *  The function could not be completed because the menu is actively 
 *  listening for commands
 */
#define  VCMDERR_MENUACTIVE               VCMDERROR(0x0E)               // 0x8004060E

/*
 *  No speech recognition engine is started
 */
#define  VCMDERR_NOENGINE                 VCMDERROR(0x0F)               // 0x8004060F

/*
 *  Voice Commands could not acquire a Grammar interface from the speech
 *  recognition engine
 */
#define  VCMDERR_NOGRAMMARINTERFACE       VCMDERROR(0x10)               // 0x80040610

/*
 *  Voice Commands could not acquire a Find interface from the speech
 *  recognition engine
 */
#define  VCMDERR_NOFINDINTERFACE          VCMDERROR(0x11)               // 0x80040611

/*
 *  Voice Commands could not create a speech recognition enumerator
 */
#define  VCMDERR_CANTCREATESRENUM         VCMDERROR(0x12)               // 0x80040612

/*
 *  Voice Commands could get the appropriate site information to start a
 *  speech recognition engine
 */
#define  VCMDERR_NOSITEINFO               VCMDERROR(0x13)               // 0x80040613

/*
 *  Voice Commands could not find a speech recognition engine
 */
#define  VCMDERR_SRFINDFAILED             VCMDERROR(0x14)               // 0x80040614

/*
 *  Voice Commands could not create an audio source object
 */
#define  VCMDERR_CANTCREATEAUDIODEVICE    VCMDERROR(0x15)               // 0x80040615

/*
 *  Voice Commands could not set the appropriate device number in the
 *  audio source object
 */
#define  VCMDERR_CANTSETDEVICE            VCMDERROR(0x16)               // 0x80040616

/*
 *  Voice Commands could not select a speech recognition engine. Usually the
 *  error will occur when Voice Commands has enumerated and found an
 *  appropriate speech recognition engine, then it is not able to actually
 *  select/start the engine. There are different reasons that the engine won't
 *  start, but the most common is that there is no wave in device.
 */
#define  VCMDERR_CANTSELECTENGINE         VCMDERROR(0x17)               // 0x80040617

/*
 *  Voice Commands could not create a notfication sink for engine
 *  notifications
 */
#define  VCMDERR_CANTCREATENOTIFY         VCMDERROR(0x18)               // 0x80040618

/*
 *  Voice Commands could not create internal data structures.
 */
#define  VCMDERR_CANTCREATEDATASTRUCTURES VCMDERROR(0x19)               // 0x80040619

/*
 *  Voice Commands could not initialize internal data structures
 */
#define  VCMDERR_CANTINITDATASTRUCTURES   VCMDERROR(0x1A)               // 0x8004061A

/*
 *  The menu does not have an entry in the Voice Commands cache
 */
#define  VCMDERR_NOCACHEDATA              VCMDERROR(0x1B)               // 0x8004061B

/*
 *  The menu does not have commands
 */
#define  VCMDERR_NOCOMMANDS               VCMDERROR(0x1C)               // 0x8004061C

/*
 *  Voice Commands cannot extract unique words needed for the engine grammar
 */
#define  VCMDERR_CANTXTRACTWORDS          VCMDERROR(0x1D)               // 0x8004061D

/*
 *  Voice Commands could not get the command set database name
 */
#define  VCMDERR_CANTGETDBNAME            VCMDERROR(0x1E)               // 0x8004061E

/*
 *  Voice Commands could not create a registry key
 */
#define  VCMDERR_CANTCREATEKEY            VCMDERROR(0x1F)               // 0x8004061F

/*
 *  Voice Commands could not create a new database name
 */
#define  VCMDERR_CANTCREATEDBNAME         VCMDERROR(0x20)               // 0x80040620

/*
 *  Voice Commands could not update the registry
 */
#define  VCMDERR_CANTUPDATEREGISTRY       VCMDERROR(0x21)               // 0x80040621

/*
 *  Voice Commands could not open the registry
 */
#define  VCMDERR_CANTOPENREGISTRY         VCMDERROR(0x22)               // 0x80040622

/*
 *  Voice Commands could not open the command set database
 */
#define  VCMDERR_CANTOPENDATABASE         VCMDERROR(0x23)               // 0x80040623

/*
 *  Voice Commands could not create a database storage object
 */
#define  VCMDERR_CANTCREATESTORAGE        VCMDERROR(0x24)               // 0x80040624

/*
 *  Voice Commands could not do CmdMimic
 */
#define  VCMDERR_CANNOTMIMIC              VCMDERROR(0x25)               // 0x80040625

/*
 *  A menu of this name already exist
 */
#define  VCMDERR_MENUEXIST                VCMDERROR(0x26)               // 0x80040626

/*
 *  A menu of this name is open and cannot be deleted right now
 */
#define  VCMDERR_MENUOPEN                 VCMDERROR(0x27)               // 0x80040627


// Voice Text Errors
#define  VTXTERR_NONE                     S_OK                          // 0x00000000

/*
 *  Voice Text failed to allocate memory it needed
 */
#define  VTXTERR_OUTOFMEM                 E_OUTOFMEMORY                 // 0x8007000E

/*
 *  An empty string ("") was passed to the Speak function
 */
#define  VTXTERR_EMPTYSPEAKSTRING         SPEECHERROR(0x0b)             // 0x8004020B

/*
 *  An invalid parameter was passed to a Voice Text function
 */
#define  VTXTERR_INVALIDPARAM             E_INVALIDARG                  // 0x80070057

/*
 *  The called function cannot be done at this time. This usually occurs
 *  when trying to call a function that needs a site, but no site has been
 *  registered.
 */
#define  VTXTERR_INVALIDMODE              SRERR_INVALIDMODE             // 0x80040206

/*
 *  No text-to-speech engine is started
 */
#define  VTXTERR_NOENGINE                 VTXTERROR(0x0F)               // 0x8004070F

/*
 *  Voice Text could not acquire a Find interface from the text-to-speech
 *  engine
 */
#define  VTXTERR_NOFINDINTERFACE          VTXTERROR(0x11)               // 0x80040711

/*
 *  Voice Text could not create a text-to-speech enumerator
 */
#define  VTXTERR_CANTCREATETTSENUM        VTXTERROR(0x12)               // 0x80040712

/*
 *  Voice Text could get the appropriate site information to start a
 *  text-to-speech engine
 */
#define  VTXTERR_NOSITEINFO               VTXTERROR(0x13)               // 0x80040713

/*
 *  Voice Text could not find a text-to-speech engine
 */
#define  VTXTERR_TTSFINDFAILED            VTXTERROR(0x14)               // 0x80040714

/*
 *  Voice Text could not create an audio destination object
 */
#define  VTXTERR_CANTCREATEAUDIODEVICE    VTXTERROR(0x15)               // 0x80040715

/*
 *  Voice Text could not set the appropriate device number in the
 *  audio destination object
 */
#define  VTXTERR_CANTSETDEVICE            VTXTERROR(0x16)               // 0x80040716

/*
 *  Voice Text could not select a text-to-speech engine. Usually the
 *  error will occur when Voice Text has enumerated and found an
 *  appropriate text-to-speech engine, then it is not able to actually
 *  select/start the engine.
 */
#define  VTXTERR_CANTSELECTENGINE         VTXTERROR(0x17)               // 0x80040717

/*
 *  Voice Text could not create a notfication sink for engine
 *  notifications
 */
#define  VTXTERR_CANTCREATENOTIFY         VTXTERROR(0x18)               // 0x80040718

/*
 *  Voice Text is disabled at this time
 */
#define  VTXTERR_NOTENABLED               VTXTERROR(0x19)               // 0x80040719

#define  VTXTERR_OUTOFDISK                SRERR_OUTOFDISK               // 0x80040205
#define  VTXTERR_NOTSUPPORTED             E_NOTIMPL                     // 0x80004001
#define  VTXTERR_NOTENOUGHDATA            AUDERR_NOTENOUGHDATA          // 0x80040201
#define  VTXTERR_QUEUEFULL                TTSERR_QUEUEFULL              // 0x8004020A
#define  VTXTERR_VALUEOUTOFRANGE          E_UNEXPECTED                  // 0x8000FFFF
#define  VTXTERR_INVALIDWINDOW            OLE_E_INVALIDHWND             // 0x8004000F
#define  VTXTERR_WAVEDEVICEBUSY           AUDERR_WAVEDEVICEBUSY         // 0x80040203
#define  VTXTERR_WAVEFORMATNOTSUPPORTED   AUDERR_WAVEFORMATNOTSUPPORTED // 0x80040202
#define  VTXTERR_INVALIDCHAR              SRERR_INVALIDCHAR             // 0x80040208


// ILexPronounce errors
#define  LEXERR_INVALIDTEXTCHAR           LEXERROR(0x01)                // 0x80040801
#define  LEXERR_INVALIDSENSE              LEXERROR(0x02)                // 0x80040802
#define  LEXERR_NOTINLEX                  LEXERROR(0x03)                // 0x80040803
#define  LEXERR_OUTOFDISK                 LEXERROR(0x04)                // 0x80040804
#define  LEXERR_INVALIDPRONCHAR           LEXERROR(0x05)                // 0x80040805
#define  LEXERR_ALREADYINLEX              LEXERROR(0x06)                // 0x80040806
#define  LEXERR_PRNBUFTOOSMALL            LEXERROR(0x07)                // 0x80040807
#define  LEXERR_ENGBUFTOOSMALL            LEXERROR(0x08)                // 0x80040808



/************************************************************************
typedefs */

typedef LPUNKNOWN FAR * PIUNKNOWN;

typedef struct {
   PVOID    pData;
   DWORD    dwSize;
   } SDATA, * PSDATA;



typedef struct {
   LANGID   LanguageID;
   WCHAR    szDialect[LANG_LEN];
   } LANGUAGEW, FAR * PLANGUAGEW;

typedef struct {
   LANGID   LanguageID;
   CHAR     szDialect[LANG_LEN];
   } LANGUAGEA, FAR * PLANGUAGEA;

#ifdef  _S_UNICODE
#define LANGUAGE    LANGUAGEW
#define PLANGUAGE   PLANGUAGEW
#else
#define LANGUAGE    LANGUAGEA
#define PLANGUAGE   PLANGUAGEA
#endif  // _S_UNICODE



typedef unsigned _int64 QWORD, * PQWORD;

typedef enum {
   CHARSET_TEXT           = 0,
   CHARSET_IPAPHONETIC    = 1,
   CHARSET_ENGINEPHONETIC = 2
   } VOICECHARSET;

typedef enum _VOICEPARTOFSPEECH {
   VPS_UNKNOWN = 0,
   VPS_NOUN = 1,
   VPS_VERB = 2,
   VPS_ADVERB = 3,
   VPS_ADJECTIVE = 4,
   VPS_PROPERNOUN = 5,
   VPS_PRONOUN = 6,
   VPS_CONJUNCTION = 7,
   VPS_CARDINAL = 8,
   VPS_ORDINAL = 9,
   VPS_DETERMINER = 10,
   VPS_QUANTIFIER = 11,
   VPS_PUNCTUATION = 12,
   VPS_CONTRACTION = 13,
   VPS_INTERJECTION = 14,
   VPS_ABBREVIATION = 15,
   VPS_PREPOSITION = 16
   } VOICEPARTOFSPEECH;


typedef struct {
   DWORD   dwNextPhonemeNode;
   DWORD   dwUpAlternatePhonemeNode;
   DWORD   dwDownAlternatePhonemeNode;
   DWORD   dwPreviousPhonemeNode;
   DWORD   dwWordNode;
   QWORD   qwStartTime;
   QWORD   qwEndTime;
   DWORD   dwPhonemeScore;
   WORD    wVolume;
   WORD    wPitch;
   } SRRESPHONEMENODE, *PSRRESPHONEMENODE;


/**
 * This structure provides information about a word node in a recognition/alternative graph
 * generated by a speech-recognition engine.
 */
typedef struct {
   /**
    * Specifies the node number of the node that follows next in time. For example, if the current node
    * contains "Mail," the next node would contain "To." If the next node has several alternatives,
    * this pointer should continue along the path that produces the highest path score at the final
    * node. If there is nothing left in the path, this can be NULL.
    */
   DWORD   dwNextWordNode;
   /**
    * Specifies the number of an alternative node with a higher score than that of the word in this
    * node. For example, if this node contains "Nail," the alternative node might contain "Mail." The
    * alternative nodes should be ordered according to the highest word score. If there are no more
    * alternatives, this can be NULL.
    */
   DWORD   dwUpAlternateWordNode;
   /**
    * Specifies the number of an alternative node with a lower score than that of the word in this
    * node. For example, if this node contains "Mail," the alternative node might contain "Nail." The
    * alternative nodes should be ordered according to the highest word score. If there are no more
    * alternatives, this can be NULL.
    */
   DWORD   dwDownAlternateWordNode;
   /**
    * Specifies the node number of the previous node. If there are several previous nodes, this maps
    * back along the highest path score at the final node. If there is nothing before this in the path,
    * this can be NULL.
    */
   DWORD   dwPreviousWordNode;
   /**
    * Specifies the node number of the first phoneme in the word. If an engine does not support
    * phonemes or if such a mapping is inappropriate, this should be NULL.
    */
   DWORD   dwPhonemeNode;
   /**
    * Time stamp, in bytes, when the audio for this node started. If the value is indeterminate, this
    * is zero.
    */
   QWORD   qwStartTime;
   /**
    * Time stamp, in bytes, when the audio for this node ended. If the value is indeterminate, this is
    * zero.
    */
   QWORD   qwEndTime;
   /**
    * Specifies the score for this individual word. It is valid to compare this score only against the
    * scores of this word's alternatives. Engines should make this value a linear probability if
    * possible. If an engine does not know the value, this is zero.
    */
   DWORD   dwWordScore;
   /**
    * Unsigned 16-bit integer that contains the linear volume level of the word, from 1 to 0xFFFF. If
    * the engine does not know the volume, this should be zero. Applications can use this information
    * to determine emphasis or sentence type - for example, question or command - or to do transplanted
    * prosody.
    */
   WORD      wVolume;
   /**
    * Unsigned 16-bit integer that contains the average pitch of the word in hertz. Engines that do not
    * have information about this value set it to zero. Applications can use this information to
    * determine emphasis or sentence type - for example, question or command - or to do transplanted
    * prosody.
    */
   WORD      wPitch;
   /**
    * Part of speech of the word, if known, for example, noun, verb, adverb, adjective, or conjunction.
    */
   VOICEPARTOFSPEECH   pos;
   /**
    * Specifies the unique identifier of the rule used to parse the word. This is the rule identifier
    * from the SRCFGRULE structure that defines the rule in the grammar. This member is valid only for
    * context-free grammars.
    *
    * If an imported rule was used to parse the word, dwCFGParse contains the unique rule identifier
    * from the SRCFGIMPRULE structure that defines the imported rule in the grammar. An application can
    * use this information to determine the semantics of a word and save itself the work of parsing the
    * tree. For example, suppose the context-free grammar contains the following rules:
    *
    * 1 = SEQ(Send mail to 2)
    *
    * 2 = ALT(Mike, Bob, Fred)
    *
    * If the engine recognizes "Send mail to Bob," the value of dwCFGParse would be 1 for "Send mail
    * to" and 2 for "Bob."
    */
   DWORD   dwCFGParse;
   /**
    * Specifies a cue that the engine has recognized but cannot translate into a word string. A node
    * with a cue may not have a word associated with it. An engine is not required to return cues so an
    * application should not expect them, although it should take advantage of cues that are returned.
    * This member is one of the following flags:
    *
    * - SRRESCUE_COMMA: A comma should go here.
    *
    * - SRRESCUE_DECLARATIVEBEGIN: A declarative sentence has begun. This cue must be followed by a
    * closing SRRESCUE_DECLARATIVEEND.
    *
    * - SRRESCUE_DECLARATIVEEND: A declarative sentence has ended.
    *
    * - SRRESCUE_IMPERATIVEBEGIN: An imperative sentence has begun. This cue must be followed by a
    * closing SRRESCUE_IMPERATIVEEND.
    *
    * - SRRESCUE_IMPERATIVEEND: An imperative sentence has ended.
    *
    * - SRRESCUE_INTERROGATIVEBEGIN: An interrogative sentence has begun. This cue must be followed by
    * a closing SRRESCUE_INTERROGATIVEEND.
    *
    * - SRRESCUE_INTERROGATIVEEND: An interrogative sentence has ended.
    *
    * - SRRESCUE_NOISE: A noise has occurred.
    *
    * - SRRESCUE_PAUSE: The speaker has paused.
    *
    * - SRRESCUE_SENTENCEBEGIN: A sentence has begun. This cue must be followed by a closing
    * SRRESCUE_SENTENCEEND. If the engine has identified the sentence as interrogative, declarative, or
    * imperative, it should use the more specific SRRESCUE_INTERROGATIVEBEGIN,
    * SRRESCUE_DECLARATIVEBEGIN, or SRRESCUE_IMPERATIVEBEGIN cues.
    *
    * - SRRESCUE_SENTENCEEND: A sentence has ended. If the engine has identified the sentence as
    * interrogative, declarative, or imperative, it should use the more specific
    * SRRESCUE_INTERROGATIVEEND, SRRESCUE_DECLARATIVEEND, or SRRESCUE_IMPERATIVEEND cues.
    *
    * - SRRESCUE_UM: The speaker has said a nonsense sound, such as "Um."
    *
    * - SRRESCUE_WILDCARD: This is a placeholder for a wildcard word in a context-free grammar.
    *
    * - SRRESCUE_WORD: The node contains a word.
    */
   DWORD   dwCue;
   } SRRESWORDNODE, * PSRRESWORDNODE;


/************************************************************************
interfaces */

/*
 * ILexPronounce
 */

#undef   INTERFACE
#define  INTERFACE   ILexPronounceW

DEFINE_GUID(IID_ILexPronounceW, 0x090CD9A2, 0xDA1A, 0x11CD, 0xB3, 0xCA, 0x0, 0xAA, 0x0, 0x47, 0xBA, 0x4F);

DECLARE_INTERFACE_ (ILexPronounceW, IUnknown) {

   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // LexPronounceW members
   STDMETHOD (Add)            (THIS_ VOICECHARSET, PCWSTR, PCWSTR, 
                               VOICEPARTOFSPEECH, PVOID, DWORD) PURE;
   STDMETHOD (Get)            (THIS_ VOICECHARSET, PCWSTR, WORD, PWSTR, 
                               DWORD, DWORD *, VOICEPARTOFSPEECH *, PVOID, 
                               DWORD, DWORD *) PURE;
   STDMETHOD (Remove)         (THIS_ PCWSTR, WORD) PURE;
   };

typedef ILexPronounceW FAR * PILEXPRONOUNCEW;


#undef   INTERFACE
#define  INTERFACE   ILexPronounceA

DEFINE_GUID(IID_ILexPronounceA, 0x2F26B9C0L, 0xDB31, 0x11CD, 0xB3, 0xCA, 0x00, 0xAA, 0x00, 0x47, 0xBA, 0x4F);

DECLARE_INTERFACE_ (ILexPronounceA, IUnknown) {

   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // LexPronounceA members
   STDMETHOD (Add)            (THIS_ VOICECHARSET, PCSTR, PCSTR, 
                               VOICEPARTOFSPEECH, PVOID, DWORD) PURE;
   STDMETHOD (Get)            (THIS_ VOICECHARSET, PCSTR, WORD, PSTR, 
                               DWORD, DWORD *, VOICEPARTOFSPEECH *, PVOID, 
                               DWORD, DWORD *) PURE;
   STDMETHOD (Remove)         (THIS_ PCSTR, WORD) PURE;
   };

typedef ILexPronounceA FAR * PILEXPRONOUNCEA;


#ifdef _S_UNICODE
 #define ILexPronounce        ILexPronounceW
 #define IID_ILexPronounce    IID_ILexPronounceW
 #define PILEXPRONOUNCE       PILEXPRONOUNCEW

#else
 #define ILexPronounce        ILexPronounceA
 #define IID_ILexPronounce    IID_ILexPronounceA
 #define PILEXPRONOUNCE       PILEXPRONOUNCEA

#endif   // _S_UNICODE



/************************************************************************
Audio source/destiantion API
*/

/************************************************************************
defines */

// AudioStop
#define      IANSRSN_NODATA             0
#define      IANSRSN_PRIORITY           1
#define      IANSRSN_INACTIVE           2
#define      IANSRSN_EOF                3

/************************************************************************
typedefs */

/************************************************************************
Class IDs */
// {CB96B400-C743-11cd-80E5-00AA003E4B50}
DEFINE_GUID(CLSID_MMAudioDest, 
0xcb96b400, 0xc743, 0x11cd, 0x80, 0xe5, 0x0, 0xaa, 0x0, 0x3e, 0x4b, 0x50);
// {D24FE500-C743-11cd-80E5-00AA003E4B50}
DEFINE_GUID(CLSID_MMAudioSource, 
0xd24fe500, 0xc743, 0x11cd, 0x80, 0xe5, 0x0, 0xaa, 0x0, 0x3e, 0x4b, 0x50);

/************************************************************************
interfaces */

// IAudio
#undef   INTERFACE
#define  INTERFACE   IAudio

// {F546B340-C743-11cd-80E5-00AA003E4B50}
DEFINE_GUID(IID_IAudio, 
0xf546b340, 0xc743, 0x11cd, 0x80, 0xe5, 0x0, 0xaa, 0x0, 0x3e, 0x4b, 0x50);

DECLARE_INTERFACE_ (IAudio, IUnknown) {
   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // IAudio members
   STDMETHOD (Flush)          (THIS) PURE;
   STDMETHOD (LevelGet)       (THIS_ DWORD *) PURE;
   STDMETHOD (LevelSet)       (THIS_ DWORD) PURE;
   STDMETHOD (PassNotify)     (THIS_ PVOID, IID) PURE;
   STDMETHOD (PosnGet)        (THIS_ PQWORD) PURE;
   STDMETHOD (Claim)          (THIS) PURE;
   STDMETHOD (UnClaim)        (THIS) PURE;
   STDMETHOD (Start)          (THIS) PURE;
   STDMETHOD (Stop)           (THIS) PURE;
   STDMETHOD (TotalGet)       (THIS_ PQWORD) PURE;
   STDMETHOD (ToFileTime)     (THIS_ PQWORD, FILETIME *) PURE;
   STDMETHOD (WaveFormatGet)  (THIS_ PSDATA) PURE;
   STDMETHOD (WaveFormatSet)  (THIS_ SDATA) PURE;
   };

typedef IAudio FAR * PIAUDIO;

// IAudioDest

#undef   INTERFACE
#define  INTERFACE   IAudioDest

// {2EC34DA0-C743-11cd-80E5-00AA003E4B50}
DEFINE_GUID(IID_IAudioDest, 
0x2ec34da0, 0xc743, 0x11cd, 0x80, 0xe5, 0x0, 0xaa, 0x0, 0x3e, 0x4b, 0x50);

DECLARE_INTERFACE_ (IAudioDest, IUnknown) {

   // IUnknown members
   STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // IAudioDest members
   STDMETHOD (FreeSpace)      (THIS_ DWORD *, BOOL *) PURE;
   STDMETHOD (DataSet)        (THIS_ PVOID, DWORD) PURE;
   STDMETHOD (BookMark)       (THIS_ DWORD) PURE;
   };

typedef IAudioDest FAR * PIAUDIODEST;



// IAudioDestNotifySink

#undef   INTERFACE
#define  INTERFACE   IAudioDestNotifySink

// {ACB08C00-C743-11cd-80E5-00AA003E4B50}
DEFINE_GUID(IID_IAudioDestNotifySink, 
0xacb08c00, 0xc743, 0x11cd, 0x80, 0xe5, 0x0, 0xaa, 0x0, 0x3e, 0x4b, 0x50);

DECLARE_INTERFACE_ (IAudioDestNotifySink, IUnknown) {
   // IUnknown members
   STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // IAudioDestNotifySink members
   STDMETHOD (AudioStop)      (THIS_ WORD) PURE;
   STDMETHOD (AudioStart)     (THIS) PURE;
   STDMETHOD (FreeSpace)      (THIS_ DWORD, BOOL) PURE;
   STDMETHOD (BookMark)       (THIS_ DWORD, BOOL) PURE;
   };

typedef IAudioDestNotifySink FAR * PIAUDIODESTNOTIFYSINK;


/*
// IAudioMultiMediaDevice

#undef   INTERFACE
#define  INTERFACE   IAudioMultiMediaDevice

// {B68AD320-C743-11cd-80E5-00AA003E4B50}
DEFINE_GUID(IID_IAudioMultiMediaDevice, 
0xb68ad320, 0xc743, 0x11cd, 0x80, 0xe5, 0x0, 0xaa, 0x0, 0x3e, 0x4b, 0x50);

DECLARE_INTERFACE_ (IAudioMultiMediaDevice, IUnknown) {
   // IUnknown members
   STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // IAudioMultiMediaDevice members
   STDMETHOD (CustomMessage)  (THIS_ UINT, SDATA) PURE;
   STDMETHOD (DeviceNumGet)   (THIS_ DWORD*) PURE;
   STDMETHOD (DeviceNumSet)   (THIS_ DWORD) PURE;
   };

typedef IAudioMultiMediaDevice FAR * PIAUDIOMULTIMEDIADEVICE;
*/


// IAudioSource
#undef   INTERFACE
#define  INTERFACE   IAudioSource

// {BC06A220-C743-11cd-80E5-00AA003E4B50}
DEFINE_GUID(IID_IAudioSource, 
0xbc06a220, 0xc743, 0x11cd, 0x80, 0xe5, 0x0, 0xaa, 0x0, 0x3e, 0x4b, 0x50);

DECLARE_INTERFACE_ (IAudioSource, IUnknown) {
   // IUnknown members
   STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // IAudioSource members
   STDMETHOD (DataAvailable)  (THIS_ DWORD *, BOOL *) PURE;
   STDMETHOD (DataGet)        (THIS_ PVOID, DWORD, DWORD *) PURE;
   };

typedef IAudioSource FAR * PIAUDIOSOURCE;



// IAudioSourceNotifySink
#undef   INTERFACE
#define  INTERFACE   IAudioSourceNotifySink

// {C0BD9A80-C743-11cd-80E5-00AA003E4B50}
DEFINE_GUID(IID_IAudioSourceNotifySink, 
0xc0bd9a80, 0xc743, 0x11cd, 0x80, 0xe5, 0x0, 0xaa, 0x0, 0x3e, 0x4b, 0x50);

DECLARE_INTERFACE_ (IAudioSourceNotifySink, IUnknown) {
   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // IAudioSourceNotifySink members
   STDMETHOD (AudioStop)      (THIS_ WORD) PURE;
   STDMETHOD (AudioStart)     (THIS) PURE;
   STDMETHOD (DataAvailable)  (THIS_ DWORD, BOOL) PURE;
   STDMETHOD (Overflow)       (THIS_ DWORD) PURE;
   };

typedef IAudioSourceNotifySink FAR * PIAUDIOSOURCENOTIFYSINK;

// IAudioFileNotifySink Interface
#undef   INTERFACE
#define  INTERFACE   IAudioFileNotifySink

// {492FE490-51E7-11b9-C000-FED6CBA3B1A9}
DEFINE_GUID( IID_IAudioFileNotifySink, 0x492fe490, 0x51e7, 0x11b9, 0xc0, 0x0, 0xfe, 0xd6, 0xcb, 0xa3, 0xb1, 0xa9);

DECLARE_INTERFACE_ (IAudioFileNotifySink, IUnknown) {
   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // IAudioSourceNotifySink members
   STDMETHOD (FileBegin)      (THIS_ DWORD) PURE;
   STDMETHOD (FileEnd)        (THIS_ DWORD) PURE;
   STDMETHOD (QueueEmpty)     (THIS) PURE;
   STDMETHOD (Posn)           (THIS_ QWORD, QWORD) PURE;
   };

typedef IAudioFileNotifySink FAR * PIAUDIOFILENOTIFYSINK;



// IAudioFile Interface

#undef   INTERFACE
#define  INTERFACE   IAudioFile

// {FD7C2320-3D6D-11b9-C000-FED6CBA3B1A9}
DEFINE_GUID( IID_IAudioFile, 0xfd7c2320, 0x3d6d, 0x11b9, 0xc0, 0x0, 0xfe, 0xd6, 0xcb, 0xa3, 0xb1, 0xa9);

DECLARE_INTERFACE_ (IAudioFile, IUnknown) {
   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // IAudioFile members
   STDMETHOD (Register) (THIS_ PIAUDIOFILENOTIFYSINK) PURE;
   STDMETHOD (Set) (THIS_ LPCWSTR pszFile, DWORD dwID) PURE;
   STDMETHOD (Add) (THIS_ LPCWSTR pszFile, DWORD dwID) PURE;
   STDMETHOD (Flush) (THIS) PURE;
   STDMETHOD (RealTimeSet) (THIS_ WORD wTime) PURE;
   STDMETHOD (RealTimeGet) (THIS_ WORD *pwTime) PURE;
   };

typedef IAudioFile FAR * PIAUDIOFILE;


/************************************************************************
defines */
/* SRINFO */
#define  SRMI_NAMELEN                  SVFN_LEN

#define  SRSEQUENCE_DISCRETE           (0)
#define  SRSEQUENCE_CONTINUOUS          (1)
#define  SRSEQUENCE_WORDSPOT            (2)

#define  SRGRAM_CFG                    SETBIT(0)
#define  SRGRAM_DICTATION              SETBIT(1)
#define  SRGRAM_LIMITEDDOMAIN          SETBIT(2)

#define  SRFEATURE_INDEPSPEAKER        SETBIT(0)
#define  SRFEATURE_INDEPMICROPHONE     SETBIT(1)
#define  SRFEATURE_TRAINWORD           SETBIT(2)
#define  SRFEATURE_TRAINPHONETIC       SETBIT(3)
#define  SRFEATURE_WILDCARD            SETBIT(4)
#define  SRFEATURE_ANYWORD             SETBIT(5)
#define  SRFEATURE_PCOPTIMIZED         SETBIT(6)
#define  SRFEATURE_PHONEOPTIMIZED      SETBIT(7)
#define  SRFEATURE_GRAMLIST            SETBIT(8)
#define  SRFEATURE_GRAMLINK            SETBIT(9)
#define  SRFEATURE_MULTILINGUAL        SETBIT(10)
#define  SRFEATURE_GRAMRECURSIVE       SETBIT(11)
#define  SRFEATURE_IPAUNICODE          SETBIT(12)

#define  SRI_ILEXPRONOUNCE             SETBIT(0)
#define  SRI_ISRATTRIBUTES             SETBIT(1)
#define  SRI_ISRCENTRAL                SETBIT(2)
#define  SRI_ISRDIALOGS                SETBIT(3)
#define  SRI_ISRGRAMCOMMON             SETBIT(4)
#define  SRI_ISRGRAMCFG                SETBIT(5)
#define  SRI_ISRGRAMDICTATION          SETBIT(6)
#define  SRI_ISRGRAMINSERTIONGUI       SETBIT(7)
#define  SRI_ISRESBASIC                SETBIT(8)
#define  SRI_ISRESMERGE                SETBIT(9)
#define  SRI_ISRESAUDIO                SETBIT(10)
#define  SRI_ISRESCORRECTION           SETBIT(11)
#define  SRI_ISRESEVAL                 SETBIT(12)
#define  SRI_ISRESGRAPH                SETBIT(13)
#define  SRI_ISRESMEMORY               SETBIT(14)
#define  SRI_ISRESMODIFYGUI            SETBIT(15)
#define  SRI_ISRESSPEAKER              SETBIT(16)
#define  SRI_ISRSPEAKER                SETBIT(17)


// ISRGramCommon::TrainQuery
#define   SRGRAMQ_NONE                    0
#define   SRGRAMQ_GENERALTRAIN            1
#define   SRGRAMQ_PHRASE                  2
#define   SRGRAMQ_DIALOG                  3

// ISRGramNotifySink::PhraseFinish
#define   ISRNOTEFIN_RECOGNIZED         SETBIT(0)
#define   ISRNOTEFIN_THISGRAMMAR        SETBIT(1)
#define   ISRNOTEFIN_RECOGSI            SETBIT(2)

// ISRGramNotifySink::Training
#define   SRGNSTRAIN_GENERAL            SETBIT(0)
#define   SRGNSTRAIN_GRAMMAR            SETBIT(1)
#define   SRGNSTRAIN_MICROPHONE         SETBIT(2)

// ISRNotifySink::AttribChange
#define   ISRNSAC_AUTOGAINENABLE        1
#define   ISRNSAC_THRESHOLD             2
#define   ISRNSAC_ECHO                  3
#define   ISRNSAC_ENERGYFLOOR           4
#define   ISRNSAC_MICROPHONE            5
#define   ISRNSAC_REALTIME              6
#define   ISRNSAC_SPEAKER               7
#define   ISRNSAC_TIMEOUT               8

/* Interference */
#define  SRMSGINT_NOISE                (0x0001)
#define  SRMSGINT_NOSIGNAL             (0x0002)
#define  SRMSGINT_TOOLOUD              (0x0003)
#define  SRMSGINT_TOOQUIET             (0x0004)
#define  SRMSGINT_AUDIODATA_STOPPED    (0x0005)
#define  SRMSGINT_AUDIODATA_STARTED    (0x0006)
#define  SRMSGINT_IAUDIO_STARTED       (0x0007)
#define  SRMSGINT_IAUDIO_STOPPED       (0x0008)

// Gramamr header values
#define   SRHDRTYPE_CFG                  0
#define   SRHDRTYPE_LIMITEDDOMAIN        1
#define   SRHDRTYPE_DICTATION            2

#define   SRHDRFLAG_UNICODE              SETBIT(0)  

/* SRCFGSYMBOL */
#define  SRCFG_STARTOPERATION          (1)
#define  SRCFG_ENDOPERATION            (2)
#define  SRCFG_WORD                    (3)
#define  SRCFG_RULE                    (4)
#define  SRCFG_WILDCARD                (5)
#define  SRCFG_LIST                    (6)

#define  SRCFGO_SEQUENCE               (1)
#define  SRCFGO_ALTERNATIVE            (2)
#define  SRCFGO_REPEAT                 (3)
#define  SRCFGO_OPTIONAL               (4)


// Grammar-chunk IDs
#define   SRCK_LANGUAGE                  1
#define   SRCKCFG_WORDS                  2
#define   SRCKCFG_RULES                  3
#define   SRCKCFG_EXPORTRULES            4
#define   SRCKCFG_IMPORTRULES            5
#define   SRCKCFG_LISTS                  6
#define   SRCKD_TOPIC                    7
#define   SRCKD_COMMON                   8
#define   SRCKD_GROUP                    9
#define   SRCKD_SAMPLE                   10
#define   SRCKLD_WORDS                   11
#define   SRCKLD_GROUP                   12
#define   SRCKLD_SAMPLE                  13

/* TrainQuery */
#define  SRTQEX_REQUIRED               (0x0000)
#define  SRTQEX_RECOMMENDED            (0x0001)

/* ISRResCorrection */
#define  SRCORCONFIDENCE_SOME          (0x0001)
#define  SRCORCONFIDENCE_VERY          (0x0002)

/* ISRResMemory constants */
#define  SRRESMEMKIND_AUDIO            SETBIT(0)
#define  SRRESMEMKIND_CORRECTION       SETBIT(1)
#define  SRRESMEMKIND_EVAL             SETBIT(2)
#define  SRRESMEMKIND_PHONEMEGRAPH     SETBIT(3)
#define  SRRESMEMKIND_WORDGRAPH        SETBIT(4)

// Attribute minimums and maximums
#define  SRATTR_MINAUTOGAIN               0
#define  SRATTR_MAXAUTOGAIN               100
#define  SRATTR_MINENERGYFLOOR            0
#define  SRATTR_MAXENERGYFLOOR            0xffff
#define  SRATTR_MINREALTIME               0
#define  SRATTR_MAXREALTIME               0xffffffff
#define  SRATTR_MINTHRESHOLD              0
#define  SRATTR_MAXTHRESHOLD              100
#define  SRATTR_MINTOINCOMPLETE           0
#define  SRATTR_MAXTOINCOMPLETE           0xffffffff
#define  SRATTR_MINTOCOMPLETE             0
#define  SRATTR_MAXTOCOMPLETE             0xffffffff


/************************************************************************
typedefs */

typedef struct {
   DWORD    dwSize;
   DWORD    dwUniqueID;
   BYTE     abData[0];
   } SRCFGRULE, * PSRCFGRULE;



typedef struct {
   DWORD    dwSize;
   DWORD    dwRuleNum;
   WCHAR    szString[0];
   } SRCFGIMPRULEW, * PSRCFGIMPRULEW;

typedef struct {
   DWORD    dwSize;
   DWORD    dwRuleNum;
   CHAR     szString[0];
   } SRCFGIMPRULEA, * PSRCFGIMPRULEA;

#ifdef  _S_UNICODE
#define  SRCFGIMPRULE      SRCFGIMPRULEW
#define  PSRCFGIMPRULE     PSRCFGIMPRULEW
#else
#define  SRCFGIMPRULE      SRCFGIMPRULEA
#define  PSRCFGIMPRULE     PSRCFGIMPRULEA
#endif  // _S_UNICODE



typedef struct {
   DWORD    dwSize;
   DWORD    dwRuleNum;
   WCHAR    szString[0];
   } SRCFGXRULEW, * PSRCFGXRULEW;

typedef struct {
   DWORD    dwSize;
   DWORD    dwRuleNum;
   CHAR     szString[0];
   } SRCFGXRULEA, * PSRCFGXRULEA;

#ifdef  _S_UNICODE
#define  SRCFGXRULE     SRCFGXRULEW
#define  PSRCFGXRULE    PSRCFGXRULEW
#else
#define  SRCFGXRULE     SRCFGXRULEA
#define  PSRCFGXRULE    PSRCFGXRULEA
#endif  // _S_UNICODE



typedef struct {
   DWORD    dwSize;
   DWORD    dwListNum;
   WCHAR    szString[0];
   } SRCFGLISTW, * PSRCFGLISTW;

typedef struct {
   DWORD    dwSize;
   DWORD    dwListNum;
   CHAR     szString[0];
   } SRCFGLISTA, * PSRCFGLISTA;

#ifdef  _S_UNICODE
#define  SRCFGLIST      SRCFGLISTW
#define  PSRCFGLIST     PSRCFGLISTW
#else
#define  SRCFGLIST      SRCFGLISTA
#define  PSRCFGLIST     PSRCFGLISTA
#endif  // _S_UNICODE



typedef struct {
   WORD     wType;
   WORD     wProbability;
   DWORD    dwValue;
   } SRCFGSYMBOL, * PSRCFGSYMBOL;



/**
 * This structure identifies a unique word for a grammar's vocabulary.
 */
typedef struct {
   /**
    * Specifies the size of SRWORD plus the size of szWord rounded up to the nearest multiple of 4. The
    * dwSize member must be DWORD-aligned to work on processors that require alignment, such as MIPS(R)
    * and Alpha APX(TM).
    */
   DWORD    dwSize;
   /**
    * Specifies a unique word identifier specific to this grammar. The same string can have a different
    * word identifier in different grammars or in the same grammar if the word participates in the
    * grammar in different ways. For example, the noun "project" and the verb "project" each would have
    * a unique word identifier within the same grammar.
    *
    * The application always specifies the word identifier when it loads a grammar. The application
    * cannot specify a word identifier of zero because the grammar also uses a word identifier to
    * notify the application when the corresponding word is spoken, and zero is reserved for situations
    * when the word identifier is unknown.
    */
   DWORD    dwWordNum;
   /**
    * Null-terminated string of variable size that contains alphabetic characters and intraword
    * punctuation. The NULL is sufficient to indicate the end of the string.
    *
    * In most European languages, szWord is a string such as "hello" or "car." The text should not
    * contain pronounced symbols. For example "345" is not a valid word string. The text also should
    * not have ambiguous pronunciation. For example, instead of the string "IEEE," use three words: "I"
    * "triple" and "E."
    *
    * Certain languages, such as Japanese, use two characters: a phonemic set and a symbolic set. The
    * phonemic character set should be passed in szWord. If an application is trying to associate the
    * symbolic representation of the word, it should use dwWordNum to point to the symbolic word.
    *
    * In some languages, the pronunciation cannot be easily deduced from the symbols that represent the
    * word. For example, the same sequence of Kanji characters can be pronounced differently. In these
    * languages, the phonetic character set appears first, followed by a backslash, followed by the
    * commonly displayed character set. The engine should use the text before the backslash to
    * determine the pronunciation of the word.
    */
   WCHAR    szWord[0];
   } SRWORDW, * PSRWORDW;

/**
 * This structure identifies a unique word for a grammar's vocabulary.
 */
typedef struct {
   /**
    * Specifies the size of SRWORD plus the size of szWord rounded up to the nearest multiple of 4. The
    * dwSize member must be DWORD-aligned to work on processors that require alignment, such as MIPS(R)
    * and Alpha APX(TM).
    */
   DWORD    dwSize;
   /**
    * Specifies a unique word identifier specific to this grammar. The same string can have a different
    * word identifier in different grammars or in the same grammar if the word participates in the
    * grammar in different ways. For example, the noun "project" and the verb "project" each would have
    * a unique word identifier within the same grammar.
    *
    * The application always specifies the word identifier when it loads a grammar. The application
    * cannot specify a word identifier of zero because the grammar also uses a word identifier to
    * notify the application when the corresponding word is spoken, and zero is reserved for situations
    * when the word identifier is unknown.
    */
   DWORD    dwWordNum;
   /**
    * Null-terminated string of variable size that contains alphabetic characters and intraword
    * punctuation. The NULL is sufficient to indicate the end of the string.
    *
    * In most European languages, szWord is a string such as "hello" or "car." The text should not
    * contain pronounced symbols. For example "345" is not a valid word string. The text also should
    * not have ambiguous pronunciation. For example, instead of the string "IEEE," use three words: "I"
    * "triple" and "E."
    *
    * Certain languages, such as Japanese, use two characters: a phonemic set and a symbolic set. The
    * phonemic character set should be passed in szWord. If an application is trying to associate the
    * symbolic representation of the word, it should use dwWordNum to point to the symbolic word.
    *
    * In some languages, the pronunciation cannot be easily deduced from the symbols that represent the
    * word. For example, the same sequence of Kanji characters can be pronounced differently. In these
    * languages, the phonetic character set appears first, followed by a backslash, followed by the
    * commonly displayed character set. The engine should use the text before the backslash to
    * determine the pronunciation of the word.
    */
   CHAR     szWord[0];
   } SRWORDA, * PSRWORDA;

#ifdef  _S_UNICODE
#define  SRWORD      SRWORDW
#define  PSRWORD     PSRWORDW
#else
#define  SRWORD      SRWORDA
#define  PSRWORD     PSRWORDA
#endif  // _S_UNICODE



/**
 * This structure identifies a unique phrase for a grammar's vocabulary. A phrase is an ordered
 * collection of words.
 */
typedef struct {
   /**
    * Specifies the size of SRPHRASE plus the size of data for abWords.
    */
   DWORD    dwSize;
   /**
    * Memory that contains a list of SRWORD structures, in temporal order.
    */
   BYTE     abWords[0];
   } SRPHRASEW, * PSRPHRASEW;

/**
 * This structure identifies a unique phrase for a grammar's vocabulary. A phrase is an ordered
 * collection of words.
 */
typedef struct {
   /**
    * Specifies the size of SRPHRASE plus the size of data for abWords.
    */
   DWORD    dwSize;
   /**
    * Memory that contains a list of SRWORD structures, in temporal order.
    */
   BYTE     abWords[0];
   } SRPHRASEA, * PSRPHRASEA;

#ifdef  _S_UNICODE
#define  SRPHRASE    SRPHRASEW
#define  PSRPHRASE   PSRPHRASEW
#else
#define  SRPHRASE    SRPHRASEA
#define  PSRPHRASE   PSRPHRASEA
#endif  // _S_UNICODE



typedef struct {
   DWORD      dwType;
   DWORD      dwFlags;
   } SRHEADER, *PSRHEADER;

typedef struct {
   DWORD      dwChunkID;
   DWORD      dwChunkSize;
   BYTE       avInfo[0];
   } SRCHUNK, *PSRCHUNK;



/**
 * This structure provides details about a speech-recognition mode supported by a particular engine.
 *
 * Although an engine can support both computer optimized and phone optimized voice qualities, most
 * support either one or the other.
 *
 * Some engines support recognition from several languages at a time. For more information about
 * recognizing multiple languages, see the description of the ISRCentral::GrammarLoad method.
 */
typedef struct {
   /**
    * Globally unique identifier (GUID) of the engine. It is possible for more than one mode to have
    * the same engine identifier. In this case, the engine is capable of recognizing the different
    * languages or voices of the modes.
    */
   GUID       gEngineID;
   /**
    * Null-terminates string that contains the name of the manufacturer .
    */
   WCHAR      szMfgName[SRMI_NAMELEN];
   /**
    * Null-terminated string that contains the name of the product.
    */
   WCHAR      szProductName[SRMI_NAMELEN];
   /**
    * Globally unique identifier (GUID) of the mode. These numbers are guaranteed to be unique, so it
    * is not necessary to monitor and record them. In addition, because the GUID is not stored or used
    * directly by OLE, it is not necessary to load it into the registry.
    */
   GUID       gModeID;
   /**
    * Null-terminated string that contains the name of the recognition mode.
    */
   WCHAR      szModeName[SRMI_NAMELEN];
   /**
    * Specifies the LANGUAGE structure that contains the name of the language and dialect.
    */
   LANGUAGEW  language;
   /**
    * Specifies the recognition scheme. It is one of the following flags:
    *
    * - SRSEQUENCE_CONTINUOUS: Performs continuous recognition. Given a continuous utterance with no
    * pauses between words, the engine can recognize the words that were spoken.
    *
    * - SRSEQUENCE_DISCRETE: Recognizes discrete utterances. Every word must be isolated by a pause
    * before and after the word for the engine to recognize it.
    *
    * - SRSEQUENCE_WORDSPOT: Performs word spotting, which means that a series of words may be spoken
    * in a continuous utterance, but the engine recognizes only selected words or phrases.
    *
    * - SRSEQUENCE_CONTCFGDISCDICT: Performs continuous recognition for context-free grammars. It also
    * supports discrete dictation.
    */
   DWORD      dwSequencing;
   /**
    * Specifies the maximum number of words allowed in an active vocabulary at any time.
    */
   DWORD      dwMaxWordsVocab;
   /**
    * Specifies the maximum number of words in any state of a grammar.
    */
   DWORD      dwMaxWordsState;
   /**
    * Specifies the types of grammar supported by the engine. It is a combination of the following
    * flags:
    *
    * - SRGRAM_CFG: Specified a context-free grammar.
    *
    * - SRGRAM_DICTATION: Specifies a dictation grammar.
    *
    * - SRGRAM_LIMITEDDOMAIN: Specifies a limited-domain grammar.
    */
   DWORD      dwGrammars;
   /**
    * Specifies available features. It is a combination of the following flags:
    *
    * - SRFEATURE_ANYWORD: The engine can attempt to recognize any word.
    *
    * - SRFEATURE_GRAMLINK: The engine supports automatic links between grammars.
    *
    * - SRFEATURE_GRAMLIST: The grammars support recognition lists.
    *
    * - SRFEATURE_GRAMRECURSIVE: The engine accepts recursive, context-free grammars; without this
    * flag, it cannot have recursive grammars.
    *
    * - SRFEATURE_INDEPMICROPHONE: The engine is microphone-independent, meaning that it is indifferent
    * to background noise and microphone, and does not require retraining if the microphone changes.
    *
    * - SRFEATURE_INDEPSPEAKER: The engine is speaker-independent and works well without training.
    *
    * - SRFEATURE_IPAUNICODE: The engine supports the IPA in Unicode.
    *
    * - SRFEATURE_MULTILINGUAL: The engine can recognize speech in several languages at a time. This is
    * necessary for systems that run two or more applications written for different languages.
    *
    * - SRFEATURE_PCOPTIMIZED: The voice is optimized to work over the computer, which provides better
    * sound quality.
    *
    * - SRFEATURE_PHONEOPTIMIZED: The voice is designed to work over the telephone and uses an
    * 8-kilohertz (kHz) sampling rate.
    *
    * - SRFEATURE_TRAINPHONETIC: The speaker can train the engine on a preselected set of words and
    * thereby train all of the phonemes used for recognition. This is done in general training.
    *
    * - SRFEATURE_TRAINWORD: The speaker can train the engine on individual words.
    *
    * - SRFEATURE_WILDCARD: The engine supports wildcards in context-free grammars.
    */
   DWORD      dwFeatures;
   /**
    * Specifies the interfaces that the engine supports. It is a combination of the following flags:
    *
    * - SRI_ILEXPRONOUNCE: Supports the ILexPronounce interface.
    *
    * - SRI_ISRATTRIBUTES: Supports the ISRAttributes interface.
    *
    * - SRI_ISRCENTRAL: Supports the ISRCentral interface.
    *
    * - SRI_ISRDIALOGS: Supports the ISRDialogs interface.
    *
    * - SRI_ISRGRAMCOMMON: Supports the ISRGramCommon interface.
    *
    * - SRI_ISRGRAMCFG: Supports the ISRGramCFG interface.
    *
    * - SRI_ISRGRAMDICTATION: Supports the ISRGramDictation interface.
    *
    * - SRI_ISRGRAMINSERTIONGUI: Supports the ISRGramInsertionGUI interface.
    *
    * - SRI_ISRESBASIC: Supports the ISRResBasic interface.
    *
    * - SRI_ISRESMERGE: Supports the ISRResMerge interface.
    *
    * - SRI_ISRESAUDIO: Supports the ISRResAudio interface.
    *
    * - SRI_ISRESCORRECTION: Supports the ISRResCorrection interface.
    *
    * - SRI_ISRESEVAL: Supports the ISRResEval interface.
    *
    * - SRI_ISRESGRAPH: Supports the ISRResGraph interface.
    *
    * - SRI_ISRESMEMORY: Supports the ISRResMemory interface.
    *
    * - SRI_ISRESMODIFYGUI: Supports the ISRResModifyGUI interface.
    *
    * - SRI_ISRESSPEAKER: Supports the ISRResSpeaker interface.
    *
    * - SRI_ISRSPEAKER: Supports the ISRSpeaker interface.
    *
    * - SRI_ISRESSCORES: Supports the ISRResScore interface.
    */
   DWORD      dwInterfaces;
   /**
    * Specifies features of a particular engine. These values are defined by the engine author. For
    * more information about engine features, see the documentation for the engine.
    *
    * In order to identify which engine is being used, an application can use the ITTSEnum interface to
    * enumerate the engines. Its features can then be determined.
    */
   DWORD      dwEngineFeatures;
   } SRMODEINFOW, * PSRMODEINFOW;

/**
 * This structure provides details about a speech-recognition mode supported by a particular engine.
 *
 * Although an engine can support both computer optimized and phone optimized voice qualities, most
 * support either one or the other.
 *
 * Some engines support recognition from several languages at a time. For more information about
 * recognizing multiple languages, see the description of the ISRCentral::GrammarLoad method.
 */
typedef struct {
   /**
    * Globally unique identifier (GUID) of the engine. It is possible for more than one mode to have
    * the same engine identifier. In this case, the engine is capable of recognizing the different
    * languages or voices of the modes.
    */
   GUID       gEngineID;
   /**
    * Null-terminates string that contains the name of the manufacturer .
    */
   CHAR       szMfgName[SRMI_NAMELEN];
   /**
    * Null-terminated string that contains the name of the product.
    */
   CHAR       szProductName[SRMI_NAMELEN];
   /**
    * Globally unique identifier (GUID) of the mode. These numbers are guaranteed to be unique, so it
    * is not necessary to monitor and record them. In addition, because the GUID is not stored or used
    * directly by OLE, it is not necessary to load it into the registry.
    */
   GUID       gModeID;
   /**
    * Null-terminated string that contains the name of the recognition mode.
    */
   CHAR       szModeName[SRMI_NAMELEN];
   /**
    * Specifies the LANGUAGE structure that contains the name of the language and dialect.
    */
   LANGUAGEA  language;
   /**
    * Specifies the recognition scheme. It is one of the following flags:
    *
    * - SRSEQUENCE_CONTINUOUS: Performs continuous recognition. Given a continuous utterance with no
    * pauses between words, the engine can recognize the words that were spoken.
    *
    * - SRSEQUENCE_DISCRETE: Recognizes discrete utterances. Every word must be isolated by a pause
    * before and after the word for the engine to recognize it.
    *
    * - SRSEQUENCE_WORDSPOT: Performs word spotting, which means that a series of words may be spoken
    * in a continuous utterance, but the engine recognizes only selected words or phrases.
    *
    * - SRSEQUENCE_CONTCFGDISCDICT: Performs continuous recognition for context-free grammars. It also
    * supports discrete dictation.
    */
   DWORD      dwSequencing;
   /**
    * Specifies the maximum number of words allowed in an active vocabulary at any time.
    */
   DWORD      dwMaxWordsVocab;
   /**
    * Specifies the maximum number of words in any state of a grammar.
    */
   DWORD      dwMaxWordsState;
   /**
    * Specifies the types of grammar supported by the engine. It is a combination of the following
    * flags:
    *
    * - SRGRAM_CFG: Specified a context-free grammar.
    *
    * - SRGRAM_DICTATION: Specifies a dictation grammar.
    *
    * - SRGRAM_LIMITEDDOMAIN: Specifies a limited-domain grammar.
    */
   DWORD      dwGrammars;
   /**
    * Specifies available features. It is a combination of the following flags:
    *
    * - SRFEATURE_ANYWORD: The engine can attempt to recognize any word.
    *
    * - SRFEATURE_GRAMLINK: The engine supports automatic links between grammars.
    *
    * - SRFEATURE_GRAMLIST: The grammars support recognition lists.
    *
    * - SRFEATURE_GRAMRECURSIVE: The engine accepts recursive, context-free grammars; without this
    * flag, it cannot have recursive grammars.
    *
    * - SRFEATURE_INDEPMICROPHONE: The engine is microphone-independent, meaning that it is indifferent
    * to background noise and microphone, and does not require retraining if the microphone changes.
    *
    * - SRFEATURE_INDEPSPEAKER: The engine is speaker-independent and works well without training.
    *
    * - SRFEATURE_IPAUNICODE: The engine supports the IPA in Unicode.
    *
    * - SRFEATURE_MULTILINGUAL: The engine can recognize speech in several languages at a time. This is
    * necessary for systems that run two or more applications written for different languages.
    *
    * - SRFEATURE_PCOPTIMIZED: The voice is optimized to work over the computer, which provides better
    * sound quality.
    *
    * - SRFEATURE_PHONEOPTIMIZED: The voice is designed to work over the telephone and uses an
    * 8-kilohertz (kHz) sampling rate.
    *
    * - SRFEATURE_TRAINPHONETIC: The speaker can train the engine on a preselected set of words and
    * thereby train all of the phonemes used for recognition. This is done in general training.
    *
    * - SRFEATURE_TRAINWORD: The speaker can train the engine on individual words.
    *
    * - SRFEATURE_WILDCARD: The engine supports wildcards in context-free grammars.
    */
   DWORD      dwFeatures;
   /**
    * Specifies the interfaces that the engine supports. It is a combination of the following flags:
    *
    * - SRI_ILEXPRONOUNCE: Supports the ILexPronounce interface.
    *
    * - SRI_ISRATTRIBUTES: Supports the ISRAttributes interface.
    *
    * - SRI_ISRCENTRAL: Supports the ISRCentral interface.
    *
    * - SRI_ISRDIALOGS: Supports the ISRDialogs interface.
    *
    * - SRI_ISRGRAMCOMMON: Supports the ISRGramCommon interface.
    *
    * - SRI_ISRGRAMCFG: Supports the ISRGramCFG interface.
    *
    * - SRI_ISRGRAMDICTATION: Supports the ISRGramDictation interface.
    *
    * - SRI_ISRGRAMINSERTIONGUI: Supports the ISRGramInsertionGUI interface.
    *
    * - SRI_ISRESBASIC: Supports the ISRResBasic interface.
    *
    * - SRI_ISRESMERGE: Supports the ISRResMerge interface.
    *
    * - SRI_ISRESAUDIO: Supports the ISRResAudio interface.
    *
    * - SRI_ISRESCORRECTION: Supports the ISRResCorrection interface.
    *
    * - SRI_ISRESEVAL: Supports the ISRResEval interface.
    *
    * - SRI_ISRESGRAPH: Supports the ISRResGraph interface.
    *
    * - SRI_ISRESMEMORY: Supports the ISRResMemory interface.
    *
    * - SRI_ISRESMODIFYGUI: Supports the ISRResModifyGUI interface.
    *
    * - SRI_ISRESSPEAKER: Supports the ISRResSpeaker interface.
    *
    * - SRI_ISRSPEAKER: Supports the ISRSpeaker interface.
    *
    * - SRI_ISRESSCORES: Supports the ISRResScore interface.
    */
   DWORD      dwInterfaces;
   /**
    * Specifies features of a particular engine. These values are defined by the engine author. For
    * more information about engine features, see the documentation for the engine.
    *
    * In order to identify which engine is being used, an application can use the ITTSEnum interface to
    * enumerate the engines. Its features can then be determined.
    */
   DWORD      dwEngineFeatures;
   } SRMODEINFOA, * PSRMODEINFOA;

#ifdef  _S_UNICODE
#define  SRMODEINFO     SRMODEINFOW
#define  PSRMODEINFO    PSRMODEINFOW
#else
#define  SRMODEINFO     SRMODEINFOA
#define  PSRMODEINFO    PSRMODEINFOA
#endif  // _S_UNICODE



/**
 * This structure ranks the members of the SRMODEINFO structure in the order of importance.
 *
 * Each member of the SRMODEINFORANK structure contains a priority value for the corresponding
 * feature. Values are relative to each other - that is, a higher value indicates a higher priority,
 * but the value itself is not meaningful.
 */
typedef struct {
   /**
    * Specifies the relative importance of a matching engine identifier.
    */
   DWORD      dwEngineID;
   /**
    * Specifies the relative importance of the specified manufacturer name.
    */
   DWORD      dwMfgName;
   /**
    * Specifies the relative importance of the specified product name.
    */
   DWORD      dwProductName;
   /**
    * Specifies the relative importance of a matching mode identifier.
    */
   DWORD      dwModeID;
   /**
    * Specifies the relative importance of the specified mode name.
    */
   DWORD      dwModeName;
   /**
    * Specifies the relative importance of the specified language.
    */
   DWORD      dwLanguage;
   /**
    * Specifies the relative importance of the specified dialect. This value is stored in the LANGUAGE
    * structure of the SRMODEINFO structure.
    */
   DWORD      dwDialect;
   /**
    * Specifies the relative importance of the specified sequencing type.
    */
   DWORD      dwSequencing;
   /**
    * Specifies the relative importance of the maximum vocabulary size. Modes that do not meet or
    * exceed the specified value are eliminated from consideration.
    */
   DWORD      dwMaxWordsVocab;
   /**
    * Specifies the relative importance of the maximum number of words in any state of a grammar. Modes
    * that do not meet or exceed the specified value are eliminated from consideration.
    */
   DWORD      dwMaxWordsState;
   /**
    * Specifies the relative importance of the requested grammars. Modes that do not support the
    * requested grammars are eliminated from consideration.
    */
   DWORD      dwGrammars;
   /**
    * Specifies the relative importance of the requested features. Modes that lack the features
    * requested are eliminated from consideration.
    */
   DWORD      dwFeatures;
   /**
    * Specifies the relative importance of the requested interfaces. Modes that lack the interfaces
    * requested are eliminated from consideration.
    */
   DWORD      dwInterfaces;
   /**
    * Specifies the relative importance of the requested engine features. Modes that lack the features
    * requested are eliminated from consideration.
    */
   DWORD      dwEngineFeatures;
   } SRMODEINFORANK, * PSRMODEINFORANK;



// speech recognition enumeration sharing object
typedef struct {
   QWORD        qwInstanceID;
   DWORD        dwDeviceID;
   SRMODEINFOW  srModeInfo;
} SRSHAREW, * PSRSHAREW;

typedef struct {
   QWORD        qwInstanceID;
   DWORD        dwDeviceID;
   SRMODEINFOA  srModeInfo;
} SRSHAREA, * PSRSHAREA;

#ifdef  _S_UNICODE
#define  SRSHARE    SRSHAREW
#define  PSRSHARE   PSRSHAREW
#else
#define  SRSHARE    SRSHAREA
#define  PSRSHARE   PSRSHAREA
#endif  // _S_UNICODE




// ISRCentral::GrammarLoad
typedef enum {
   SRGRMFMT_CFG = 0x0000,
   SRGRMFMT_LIMITEDDOMAIN = 0x0001,
   SRGRMFMT_DICTATION = 0x0002,
   SRGRMFMT_CFGNATIVE = 0x8000,
   SRGRMFMT_LIMITEDDOMAINNATIVE = 0x8001,
   SRGRMFMT_DICTATIONNATIVE = 0x8002,
   } SRGRMFMT, * PSRGRMFMT;

/************************************************************************
Class IDs */


// {E02D16C0-C743-11cd-80E5-00AA003E4B50}
DEFINE_GUID(CLSID_SREnumerator, 
0xe02d16c0, 0xc743, 0x11cd, 0x80, 0xe5, 0x0, 0xaa, 0x0, 0x3e, 0x4b, 0x50);


/************************************************************************
interfaces */


/*
 * ISRAttributes
 */

#undef   INTERFACE
#define  INTERFACE   ISRAttributesW

DEFINE_GUID(IID_ISRAttributesW, 0x68A33AA0L, 0x44CD, 0x101B, 0x90, 0xA8, 0x00, 0xAA, 0x00, 0x3E, 0x4B, 0x50);

DECLARE_INTERFACE_ (ISRAttributesW, IUnknown) {

   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // ISRAttributesW members
   STDMETHOD (AutoGainEnableGet) (THIS_ DWORD *) PURE;
   STDMETHOD (AutoGainEnableSet) (THIS_ DWORD) PURE;
   STDMETHOD (EchoGet)           (THIS_ BOOL *) PURE;
   STDMETHOD (EchoSet)           (THIS_ BOOL) PURE;
   STDMETHOD (EnergyFloorGet)    (THIS_ WORD *) PURE;
   STDMETHOD (EnergyFloorSet)    (THIS_ WORD) PURE;
   STDMETHOD (MicrophoneGet)     (THIS_ PWSTR, DWORD, DWORD *) PURE;
   STDMETHOD (MicrophoneSet)     (THIS_ PCWSTR) PURE;
   STDMETHOD (RealTimeGet)       (THIS_ DWORD *) PURE;
   STDMETHOD (RealTimeSet)       (THIS_ DWORD) PURE;
   STDMETHOD (SpeakerGet)        (THIS_ PWSTR, DWORD, DWORD *) PURE;
   STDMETHOD (SpeakerSet)        (THIS_ PCWSTR) PURE;
   STDMETHOD (TimeOutGet)        (THIS_ DWORD *, DWORD *) PURE;
   STDMETHOD (TimeOutSet)        (THIS_ DWORD, DWORD) PURE;
   STDMETHOD (ThresholdGet)      (THIS_ DWORD *) PURE;
   STDMETHOD (ThresholdSet)      (THIS_ DWORD) PURE;
   };

typedef ISRAttributesW FAR * PISRATTRIBUTESW;


#undef   INTERFACE
#define  INTERFACE   ISRAttributesA

DEFINE_GUID(IID_ISRAttributesA, 0x2F26B9C1L, 0xDB31, 0x11CD, 0xB3, 0xCA, 0x00, 0xAA, 0x00, 0x47, 0xBA, 0x4F);

DECLARE_INTERFACE_ (ISRAttributesA, IUnknown) {

   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // ISRAttributesA members
   STDMETHOD (AutoGainEnableGet) (THIS_ DWORD *) PURE;
   STDMETHOD (AutoGainEnableSet) (THIS_ DWORD) PURE;
   STDMETHOD (EchoGet)           (THIS_ BOOL *) PURE;
   STDMETHOD (EchoSet)           (THIS_ BOOL) PURE;
   STDMETHOD (EnergyFloorGet)    (THIS_ WORD *) PURE;
   STDMETHOD (EnergyFloorSet)    (THIS_ WORD) PURE;
   STDMETHOD (MicrophoneGet)     (THIS_ PSTR, DWORD, DWORD *) PURE;
   STDMETHOD (MicrophoneSet)     (THIS_ PCSTR) PURE;
   STDMETHOD (RealTimeGet)       (THIS_ DWORD *) PURE;
   STDMETHOD (RealTimeSet)       (THIS_ DWORD) PURE;
   STDMETHOD (SpeakerGet)        (THIS_ PSTR, DWORD, DWORD *) PURE;
   STDMETHOD (SpeakerSet)        (THIS_ PCSTR) PURE;
   STDMETHOD (TimeOutGet)        (THIS_ DWORD *, DWORD *) PURE;
   STDMETHOD (TimeOutSet)        (THIS_ DWORD, DWORD) PURE;
   STDMETHOD (ThresholdGet)      (THIS_ DWORD *) PURE;
   STDMETHOD (ThresholdSet)      (THIS_ DWORD) PURE;
   };

typedef ISRAttributesA FAR * PISRATTRIBUTESA;


#ifdef _S_UNICODE
 #define ISRAttributes        ISRAttributesW
 #define IID_ISRAttributes    IID_ISRAttributesW
 #define PISRATTRIBUTES       PISRATTRIBUTESW

#else
 #define ISRAttributes        ISRAttributesA
 #define IID_ISRAttributes    IID_ISRAttributesA
 #define PISRATTRIBUTES       PISRATTRIBUTESA

#endif // _S_UNICODE



/*
 * ISRCentral
 */

#undef   INTERFACE
#define  INTERFACE   ISRCentralW

DEFINE_GUID(IID_ISRCentralW, 0xB9BD3860L, 0x44DB, 0x101B, 0x90, 0xA8, 0x00, 0xAA, 0x00, 0x3E, 0x4B, 0x50);

DECLARE_INTERFACE_ (ISRCentralW, IUnknown) {

   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // ISRCentralW members
   STDMETHOD (ModeGet)        (THIS_ PSRMODEINFOW) PURE;
   STDMETHOD (GrammarLoad)    (THIS_ SRGRMFMT, SDATA, PVOID, IID, LPUNKNOWN *) PURE;
   STDMETHOD (Pause)          (THIS) PURE;
   STDMETHOD (PosnGet)        (THIS_ PQWORD) PURE;
   STDMETHOD (Resume)         (THIS) PURE;
   STDMETHOD (ToFileTime)     (THIS_ PQWORD, FILETIME *) PURE;
   STDMETHOD (Register)       (THIS_ PVOID, IID, DWORD*) PURE;
   STDMETHOD (UnRegister)     (THIS_ DWORD) PURE;
   };

typedef ISRCentralW FAR * PISRCENTRALW;


#undef   INTERFACE
#define  INTERFACE   ISRCentralA

DEFINE_GUID(IID_ISRCentralA, 0x2F26B9C2L, 0xDB31, 0x11CD, 0xB3, 0xCA, 0x00, 0xAA, 0x00, 0x47, 0xBA, 0x4F);

DECLARE_INTERFACE_ (ISRCentralA, IUnknown) {

   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // ISRCentralA members
   STDMETHOD (ModeGet)        (THIS_ PSRMODEINFOA) PURE;
   STDMETHOD (GrammarLoad)    (THIS_ SRGRMFMT, SDATA, PVOID, IID, LPUNKNOWN *) PURE;
   STDMETHOD (Pause)          (THIS) PURE;
   STDMETHOD (PosnGet)        (THIS_ PQWORD) PURE;
   STDMETHOD (Resume)         (THIS) PURE;
   STDMETHOD (ToFileTime)     (THIS_ PQWORD, FILETIME *) PURE;
   STDMETHOD (Register)       (THIS_ PVOID, IID, DWORD*) PURE;
   STDMETHOD (UnRegister)     (THIS_ DWORD) PURE;
   };

typedef ISRCentralA FAR * PISRCENTRALA;


#ifdef _S_UNICODE
 #define ISRCentral           ISRCentralW
 #define IID_ISRCentral       IID_ISRCentralW
 #define PISRCENTRAL          PISRCENTRALW

#else
 #define ISRCentral           ISRCentralA
 #define IID_ISRCentral       IID_ISRCentralA
 #define PISRCENTRAL          PISRCENTRALA

#endif   // _S_UNICODE



/*
 * ISRDialogs
 */

#undef   INTERFACE
#define  INTERFACE   ISRDialogsW

DEFINE_GUID(IID_ISRDialogsW, 0xBCFB4C60L, 0x44DB, 0x101B, 0x90, 0xA8, 0x00, 0xAA, 0x00, 0x3E, 0x4B, 0x50);

DECLARE_INTERFACE_ (ISRDialogsW, IUnknown) {

   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // ISRDialogsW members
   STDMETHOD (AboutDlg)       (THIS_ HWND, PCWSTR) PURE;
   STDMETHOD (GeneralDlg)     (THIS_ HWND, PCWSTR) PURE;
   STDMETHOD (LexiconDlg)     (THIS_ HWND, PCWSTR) PURE;
   STDMETHOD (TrainMicDlg)    (THIS_ HWND, PCWSTR) PURE;
   STDMETHOD (TrainGeneralDlg)(THIS_ HWND, PCWSTR) PURE;
   };

typedef ISRDialogsW FAR * PISRDIALOGSW;


#undef   INTERFACE
#define  INTERFACE   ISRDialogsA

DEFINE_GUID(IID_ISRDialogsA, 0x05EB6C60L, 0xDBAB, 0x11CD, 0xB3, 0xCA, 0x00, 0xAA, 0x00, 0x47, 0xBA, 0x4F);

DECLARE_INTERFACE_ (ISRDialogsA, IUnknown) {

   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // ISRDialogsA members
   STDMETHOD (AboutDlg)       (THIS_ HWND, PCSTR) PURE;
   STDMETHOD (GeneralDlg)     (THIS_ HWND, PCSTR) PURE;
   STDMETHOD (LexiconDlg)     (THIS_ HWND, PCSTR) PURE;
   STDMETHOD (TrainMicDlg)    (THIS_ HWND, PCSTR) PURE;
   STDMETHOD (TrainGeneralDlg)(THIS_ HWND, PCSTR) PURE;
   };

typedef ISRDialogsA FAR * PISRDIALOGSA;


#ifdef _S_UNICODE
 #define ISRDialogs        ISRDialogsW
 #define IID_ISRDialogs    IID_ISRDialogsW
 #define PISRDIALOGS       PISRDIALOGSW

#else
 #define ISRDialogs        ISRDialogsA
 #define IID_ISRDialogs    IID_ISRDialogsA
 #define PISRDIALOGS       PISRDIALOGSA

#endif



/*
 *  ISREnum
 */

#undef   INTERFACE
#define  INTERFACE   ISREnumW

DEFINE_GUID(IID_ISREnumW, 0xBFA9F1A0L, 0x44DB, 0x101B, 0x90, 0xA8, 0x00, 0xAA, 0x00, 0x3E, 0x4B, 0x50);

DECLARE_INTERFACE_ (ISREnumW, IUnknown) {
   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // ISREnumW members
   STDMETHOD (Next)           (THIS_ ULONG, PSRMODEINFOW, ULONG *) PURE;
   STDMETHOD (Skip)           (THIS_ ULONG) PURE;
   STDMETHOD (Reset)          (THIS) PURE;
   STDMETHOD (Clone)          (THIS_ ISREnumW * FAR *) PURE;
   STDMETHOD (Select)         (THIS_ GUID, PISRCENTRALW *, LPUNKNOWN) PURE;
   };

typedef ISREnumW FAR * PISRENUMW;


#undef   INTERFACE
#define  INTERFACE   ISREnumA

DEFINE_GUID(IID_ISREnumA, 0x05EB6C61L, 0xDBAB, 0x11CD, 0xB3, 0xCA, 0x00, 0xAA, 0x00, 0x47, 0xBA, 0x4F);

DECLARE_INTERFACE_ (ISREnumA, IUnknown) {

   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // ISREnumA members
   STDMETHOD (Next)           (THIS_ ULONG, PSRMODEINFOA, ULONG *) PURE;
   STDMETHOD (Skip)           (THIS_ ULONG) PURE;
   STDMETHOD (Reset)          (THIS) PURE;
   STDMETHOD (Clone)          (THIS_ ISREnumA * FAR *) PURE;
   STDMETHOD (Select)         (THIS_ GUID, PISRCENTRALA *, LPUNKNOWN) PURE;
   };

typedef ISREnumA FAR * PISRENUMA;


#ifdef _S_UNICODE
 #define ISREnum           ISREnumW
 #define IID_ISREnum       IID_ISREnumW
 #define PISRENUM          PISRENUMW

#else
 #define ISREnum           ISREnumA
 #define IID_ISREnum       IID_ISREnumA
 #define PISRENUM          PISRENUMA

#endif



/*
 * ISRFind
 */

#undef   INTERFACE
#define  INTERFACE   ISRFindW

DEFINE_GUID(IID_ISRFindW, 0xC2835060L, 0x44DB, 0x101B, 0x90, 0xA8, 0x00, 0xAA, 0x00, 0x3E, 0x4B, 0x50);

DECLARE_INTERFACE_ (ISRFindW, IUnknown) {

   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // ISRFindW members
   STDMETHOD (Find)           (THIS_ PSRMODEINFOW, PSRMODEINFORANK, PSRMODEINFOW) PURE;
   STDMETHOD (Select)         (THIS_ GUID, PISRCENTRALW *, LPUNKNOWN) PURE;
   };

typedef ISRFindW FAR * PISRFINDW;


#undef   INTERFACE
#define  INTERFACE   ISRFindA

DEFINE_GUID(IID_ISRFindA, 0x05EB6C62L, 0xDBAB, 0x11CD, 0xB3, 0xCA, 0x00, 0xAA, 0x00, 0x47, 0xBA, 0x4F);

DECLARE_INTERFACE_ (ISRFindA, IUnknown) {

   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // ISRFindA members
   STDMETHOD (Find)           (THIS_ PSRMODEINFOA, PSRMODEINFORANK, PSRMODEINFOA) PURE;
   STDMETHOD (Select)         (THIS_ GUID, PISRCENTRALA *, LPUNKNOWN) PURE;
   };

typedef ISRFindA FAR * PISRFINDA;


#ifdef _S_UNICODE
 #define ISRFind           ISRFindW
 #define IID_ISRFind       IID_ISRFindW
 #define PISRFIND          PISRFINDW

#else
 #define ISRFind           ISRFindA
 #define IID_ISRFind       IID_ISRFindA
 #define PISRFIND          PISRFINDA

#endif



/*
 * ISRGramCommon
 */

#undef   INTERFACE
#define  INTERFACE   ISRGramCommonW

DEFINE_GUID(IID_ISRGramCommonW, 0xe8c3e160, 0xc743, 0x11cd, 0x80, 0xe5, 0x0, 0xaa, 0x0, 0x3e, 0x4b, 0x50);

DECLARE_INTERFACE_ (ISRGramCommonW, IUnknown) {

   // IUnknown members
   STDMETHOD(QueryInterface)    (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)     (THIS) PURE;
   STDMETHOD_(ULONG,Release)    (THIS) PURE;

   // ISRGramCommonW members
   STDMETHOD (Activate)         (THIS_ HWND, BOOL, PCWSTR) PURE;
   STDMETHOD (Archive)          (THIS_ BOOL, PVOID, DWORD, DWORD *) PURE;
   STDMETHOD (BookMark)         (THIS_ QWORD, DWORD) PURE;
   STDMETHOD (Deactivate)       (THIS_ PCWSTR) PURE;
   STDMETHOD (DeteriorationGet) (THIS_ DWORD *, DWORD *, DWORD *) PURE;
   STDMETHOD (DeteriorationSet) (THIS_ DWORD, DWORD, DWORD) PURE;
   STDMETHOD (TrainDlg)         (THIS_ HWND, PCWSTR) PURE;
   STDMETHOD (TrainPhrase)      (THIS_ DWORD, PSDATA) PURE;
   STDMETHOD (TrainQuery)       (THIS_ DWORD *) PURE;
   };

typedef ISRGramCommonW FAR * PISRGRAMCOMMONW;


#undef   INTERFACE
#define  INTERFACE   ISRGramCommonA

DEFINE_GUID(IID_ISRGramCommonA, 0x05EB6C63L, 0xDBAB, 0x11CD, 0xB3, 0xCA, 0x00, 0xAA, 0x00, 0x47, 0xBA, 0x4F);

DECLARE_INTERFACE_ (ISRGramCommonA, IUnknown) {

   // IUnknown members
   STDMETHOD(QueryInterface)    (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)     (THIS) PURE;
   STDMETHOD_(ULONG,Release)    (THIS) PURE;

   // ISRGramCommonA members
   STDMETHOD (Activate)         (THIS_ HWND, BOOL, PCSTR) PURE;
   STDMETHOD (Archive)          (THIS_ BOOL, PVOID, DWORD, DWORD *) PURE;
   STDMETHOD (BookMark)         (THIS_ QWORD, DWORD) PURE;
   STDMETHOD (Deactivate)       (THIS_ PCSTR) PURE;
   STDMETHOD (DeteriorationGet) (THIS_ DWORD *, DWORD *, DWORD *) PURE;
   STDMETHOD (DeteriorationSet) (THIS_ DWORD, DWORD, DWORD) PURE;
   STDMETHOD (TrainDlg)         (THIS_ HWND, PCSTR) PURE;
   STDMETHOD (TrainPhrase)      (THIS_ DWORD, PSDATA) PURE;
   STDMETHOD (TrainQuery)       (THIS_ DWORD *) PURE;
   };

typedef ISRGramCommonA FAR * PISRGRAMCOMMONA;


#ifdef _S_UNICODE
 #define ISRGramCommon        ISRGramCommonW
 #define IID_ISRGramCommon    IID_ISRGramCommonW
 #define PISRGRAMCOMMON       PISRGRAMCOMMONW

#else
 #define ISRGramCommon        ISRGramCommonA
 #define IID_ISRGramCommon    IID_ISRGramCommonA
 #define PISRGRAMCOMMON       PISRGRAMCOMMONA

#endif



/*
 * ISRGramCFG
 */

#undef   INTERFACE
#define  INTERFACE   ISRGramCFGW

DEFINE_GUID(IID_ISRGramCFGW, 0xecc0b180, 0xc743, 0x11cd, 0x80, 0xe5, 0x0, 0xaa, 0x0, 0x3e, 0x4b, 0x50);

DECLARE_INTERFACE_ (ISRGramCFGW, IUnknown) {

   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // ISRGramCFGW members
   STDMETHOD (LinkQuery)      (THIS_ PCWSTR, BOOL *) PURE;
   STDMETHOD (ListAppend)     (THIS_ PCWSTR, SDATA) PURE;
   STDMETHOD (ListGet)        (THIS_ PCWSTR, PSDATA) PURE;
   STDMETHOD (ListRemove)     (THIS_ PCWSTR, SDATA) PURE;
   STDMETHOD (ListSet)        (THIS_ PCWSTR, SDATA) PURE;
   STDMETHOD (ListQuery)      (THIS_ PCWSTR, BOOL *) PURE;
   };

typedef ISRGramCFGW FAR * PISRGRAMCFGW;


#undef   INTERFACE
#define  INTERFACE   ISRGramCFGA

DEFINE_GUID(IID_ISRGramCFGA, 0x05EB6C64L, 0xDBAB, 0x11CD, 0xB3, 0xCA, 0x00, 0xAA, 0x00, 0x47, 0xBA, 0x4F);

DECLARE_INTERFACE_ (ISRGramCFGA, IUnknown) {

   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // ISRGramCFGA members
   STDMETHOD (LinkQuery)      (THIS_ PCSTR, BOOL *) PURE;
   STDMETHOD (ListAppend)     (THIS_ PCSTR, SDATA) PURE;
   STDMETHOD (ListGet)        (THIS_ PCSTR, PSDATA) PURE;
   STDMETHOD (ListRemove)     (THIS_ PCSTR, SDATA) PURE;
   STDMETHOD (ListSet)        (THIS_ PCSTR, SDATA) PURE;
   STDMETHOD (ListQuery)      (THIS_ PCSTR, BOOL *) PURE;
   };

typedef ISRGramCFGA FAR * PISRGRAMCFGA;


#ifdef _S_UNICODE
 #define ISRGramCFG        ISRGramCFGW
 #define IID_ISRGramCFG    IID_ISRGramCFGW
 #define PISRGRAMCFG       PISRGRAMCFGW

#else
 #define ISRGramCFG        ISRGramCFGA
 #define IID_ISRGramCFG    IID_ISRGramCFGA
 #define PISRGRAMCFG       PISRGRAMCFGA

#endif



/* 
 * ISRGramDictation
 */

#undef   INTERFACE
#define  INTERFACE   ISRGramDictationW

DEFINE_GUID(IID_ISRGramDictationW, 0x090CD9A3, 0xDA1A, 0x11CD, 0xB3, 0xCA, 0x0, 0xAA, 0x0, 0x47, 0xBA, 0x4F);

DECLARE_INTERFACE_ (ISRGramDictationW, IUnknown) {

   // IUnknown members
   STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // ISRGramDictationW members
   STDMETHOD (Context)        (THIS_ PCWSTR, PCWSTR) PURE;
   STDMETHOD (Hint)           (THIS_ PCWSTR) PURE;
   STDMETHOD (Words)          (THIS_ PCWSTR) PURE;
   };

typedef ISRGramDictationW FAR *PISRGRAMDICTATIONW;


#undef   INTERFACE
#define  INTERFACE   ISRGramDictationA

DEFINE_GUID(IID_ISRGramDictationA, 0x05EB6C65L, 0xDBAB, 0x11CD, 0xB3, 0xCA, 0x00, 0xAA, 0x00, 0x47, 0xBA, 0x4F);

DECLARE_INTERFACE_ (ISRGramDictationA, IUnknown) {

   // IUnknown members
   STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // ISRGramDictationA members
   STDMETHOD (Context)        (THIS_ PCSTR, PCSTR) PURE;
   STDMETHOD (Hint)           (THIS_ PCSTR) PURE;
   STDMETHOD (Words)          (THIS_ PCSTR) PURE;
   };

typedef ISRGramDictationA FAR *PISRGRAMDICTATIONA;


#ifdef _S_UNICODE
 #define ISRGramDictation        ISRGramDictationW
 #define IID_ISRGramDictation    IID_ISRGramDictationW
 #define PISRGRAMDICTATION       PISRGRAMDICTATIONW

#else
 #define ISRGramDictation        ISRGramDictationA
 #define IID_ISRGramDictation    IID_ISRGramDictationA
 #define PISRGRAMDICTATION       PISRGRAMDICTATIONA

#endif



// ISRGramInsertionGUI
// This does not need an ANSI/UNICODE interface because no characters are passed
#undef   INTERFACE
#define  INTERFACE   ISRGramInsertionGUI

// {090CD9A4-DA1A-11CD-B3CA-00AA0047BA4F}
DEFINE_GUID(IID_ISRGramInsertionGUI,
0x090CD9A4, 0xDA1A, 0x11CD, 0xB3, 0xCA, 0x0, 0xAA, 0x0, 0x47, 0xBA, 0x4F);

DECLARE_INTERFACE_ (ISRGramInsertionGUI, IUnknown) {
   // IUnknown members
   STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // ISRGramInsertionGUI members
   STDMETHOD (Hide)           (THIS) PURE;
   STDMETHOD (Move)           (THIS_ RECT) PURE;
   STDMETHOD (Show)           (THIS_ HWND) PURE;
   };

typedef ISRGramInsertionGUI FAR *PISRGRAMINSERTIONGUI;



/*
 * ISRGramNotifySink
 */

#undef   INTERFACE
#define  INTERFACE   ISRGramNotifySinkW

DEFINE_GUID(IID_ISRGramNotifySinkW,  0xf106bfa0, 0xc743, 0x11cd, 0x80, 0xe5, 0x0, 0xaa, 0x0, 0x3e, 0x4b, 0x50);

DECLARE_INTERFACE_ (ISRGramNotifySinkW, IUnknown) {
   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // ISRGramNotifySinkW members
   STDMETHOD (BookMark)       (THIS_ DWORD) PURE;
   STDMETHOD (Paused)         (THIS) PURE;
   STDMETHOD (PhraseFinish)   (THIS_ DWORD, QWORD, QWORD, PSRPHRASEW, LPUNKNOWN) PURE;
   STDMETHOD (PhraseHypothesis)(THIS_ DWORD, QWORD, QWORD, PSRPHRASEW, LPUNKNOWN) PURE;
   STDMETHOD (PhraseStart)    (THIS_ QWORD) PURE;
   STDMETHOD (ReEvaluate)     (THIS_ LPUNKNOWN) PURE;
   STDMETHOD (Training)       (THIS_ DWORD) PURE;
   STDMETHOD (UnArchive)      (THIS_ LPUNKNOWN) PURE;
   };

typedef ISRGramNotifySinkW FAR * PISRGRAMNOTIFYSINKW;


// ISRGramNotifySinkA
#undef   INTERFACE
#define  INTERFACE   ISRGramNotifySinkA

// {EFEEA350-CE5E-11cd-9D96-00AA002FC7C9}
DEFINE_GUID(IID_ISRGramNotifySinkA, 
0xefeea350, 0xce5e, 0x11cd, 0x9d, 0x96, 0x0, 0xaa, 0x0, 0x2f, 0xc7, 0xc9);

DECLARE_INTERFACE_ (ISRGramNotifySinkA, IUnknown) {
   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // ISRGramNotifySinkA members
   STDMETHOD (BookMark)       (THIS_ DWORD) PURE;
   STDMETHOD (Paused)         (THIS) PURE;
   STDMETHOD (PhraseFinish)   (THIS_ DWORD, QWORD, QWORD, PSRPHRASEA, LPUNKNOWN) PURE;
   STDMETHOD (PhraseHypothesis)(THIS_ DWORD, QWORD, QWORD, PSRPHRASEA, LPUNKNOWN) PURE;
   STDMETHOD (PhraseStart)    (THIS_ QWORD) PURE;
   STDMETHOD (ReEvaluate)     (THIS_ LPUNKNOWN) PURE;
   STDMETHOD (Training)       (THIS_ DWORD) PURE;
   STDMETHOD (UnArchive)      (THIS_ LPUNKNOWN) PURE;
   };

typedef ISRGramNotifySinkA FAR * PISRGRAMNOTIFYSINKA;


#ifdef _S_UNICODE
 #define ISRGramNotifySink       ISRGramNotifySinkW
 #define IID_ISRGramNotifySink   IID_ISRGramNotifySinkW
 #define PISRGRAMNOTIFYSINK      PISRGRAMNOTIFYSINKW

#else
 #define ISRGramNotifySink       ISRGramNotifySinkA
 #define IID_ISRGramNotifySink   IID_ISRGramNotifySinkA
 #define PISRGRAMNOTIFYSINK      PISRGRAMNOTIFYSINKA

#endif   // _S_UNICODE



// ISRNotifySink
// This does not need an ANSI/UNICODE interface because no characters are passed
#undef   INTERFACE
#define  INTERFACE   ISRNotifySink

DEFINE_GUID(IID_ISRNotifySink,
0x090CD9B0L, 0xDA1A, 0x11CD, 0xB3, 0xCA, 0x00, 0xAA, 0x00, 0x47, 0xBA, 0x4F);

DECLARE_INTERFACE_ (ISRNotifySink, IUnknown) {
   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // ISRNotifySink members
   STDMETHOD (AttribChanged)  (THIS_ DWORD) PURE;
   STDMETHOD (Interference)   (THIS_ QWORD, QWORD, DWORD) PURE;
   STDMETHOD (Sound)          (THIS_ QWORD, QWORD) PURE;
   STDMETHOD (UtteranceBegin) (THIS_ QWORD) PURE;
   STDMETHOD (UtteranceEnd)   (THIS_ QWORD, QWORD) PURE;
   STDMETHOD (VUMeter)        (THIS_ QWORD, WORD) PURE;
   };

typedef ISRNotifySink FAR *PISRNOTIFYSINK;

// Just in case anyone uses the wide/ansi versions
#define ISRNotifySinkW       ISRNotifySink
#define IID_ISRNotifySinkW   IID_ISRNotifySink
#define PISRNOTIFYSINKW      PISRNOTIFYSINK
#define ISRNotifySinkA       ISRNotifySink
#define IID_ISRNotifySinkA   IID_ISRNotifySink
#define PISRNOTIFYSINKA      PISRNOTIFYSINK


/*
 * ISRResBasic
 */

#undef   INTERFACE
#define  INTERFACE   ISRResBasicW

DEFINE_GUID(IID_ISRResBasicW, 0x090CD9A5, 0xDA1A, 0x11CD, 0xB3, 0xCA, 0x0, 0xAA, 0x0, 0x47, 0xBA, 0x4F);

DECLARE_INTERFACE_ (ISRResBasicW, IUnknown) {

   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // ISRResBasicW members
   STDMETHOD (PhraseGet)      (THIS_ DWORD, PSRPHRASEW, DWORD,  DWORD *) PURE;
   STDMETHOD (Identify)       (THIS_ GUID *) PURE;
   STDMETHOD (TimeGet)        (THIS_ PQWORD, PQWORD) PURE;
   STDMETHOD (FlagsGet)       (THIS_ DWORD, DWORD *) PURE;
   };

typedef ISRResBasicW FAR *PISRRESBASICW;


#undef   INTERFACE
#define  INTERFACE   ISRResBasicA

DEFINE_GUID(IID_ISRResBasicA, 0x05EB6C66L, 0xDBAB, 0x11CD, 0xB3, 0xCA, 0x00, 0xAA, 0x00, 0x47, 0xBA, 0x4F);

DECLARE_INTERFACE_ (ISRResBasicA, IUnknown) {

   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // ISRResBasicA members
   STDMETHOD (PhraseGet)      (THIS_ DWORD, PSRPHRASEA, DWORD,  DWORD *) PURE;
   STDMETHOD (Identify)       (THIS_ GUID *) PURE;
   STDMETHOD (TimeGet)        (THIS_ PQWORD, PQWORD) PURE;
   STDMETHOD (FlagsGet)       (THIS_ DWORD, DWORD *) PURE;
   };

typedef ISRResBasicA FAR *PISRRESBASICA;


#ifdef _S_UNICODE
 #define ISRResBasic             ISRResBasicW
 #define IID_ISRResBasic         IID_ISRResBasicW
 #define PISRRESBASIC            PISRRESBASICW

#else
 #define ISRResBasic             ISRResBasicA
 #define IID_ISRResBasic         IID_ISRResBasicA
 #define PISRRESBASIC            PISRRESBASICA

#endif   // _S_UNICODE



/*
 * ISRResMerge
 * This does not need an ANSI/UNICODE interface because no characters are passed
 */

#undef   INTERFACE
#define  INTERFACE   ISRResMerge

DEFINE_GUID(IID_ISRResMerge, 0x090CD9A6, 0xDA1A, 0x11CD, 0xB3, 0xCA, 0x0, 0xAA, 0x0, 0x47, 0xBA, 0x4F);

DECLARE_INTERFACE_ (ISRResMerge, IUnknown) {

   // IUnknown members
   STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // ISRResMerge members
   STDMETHOD (Merge)          (THIS_ LPUNKNOWN, PIUNKNOWN ) PURE;
   STDMETHOD (Split)          (THIS_ QWORD, PIUNKNOWN , PIUNKNOWN ) PURE;
   };

typedef ISRResMerge FAR *PISRRESMERGE;



/*
 * ISRResAudio
 * This does not need an ANSI/UNICODE interface because no characters are passed
 */

#undef   INTERFACE
#define  INTERFACE   ISRResAudio

DEFINE_GUID(IID_ISRResAudio, 0x090CD9A7, 0xDA1A, 0x11CD, 0xB3, 0xCA, 0x0, 0xAA, 0x0, 0x47, 0xBA, 0x4F);

DECLARE_INTERFACE_ (ISRResAudio, IUnknown) {

   // IUnknown members
   STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // ISRResAudio members
   STDMETHOD (GetWAV)         (THIS_ PSDATA) PURE;
   };

typedef ISRResAudio FAR *PISRRESAUDIO;



/*
 * ISRResCorrection
 */

#undef   INTERFACE
#define  INTERFACE   ISRResCorrectionW

DEFINE_GUID(IID_ISRResCorrectionW, 0x090CD9A8L, 0xDA1A, 0x11CD, 0xB3, 0xCA, 0x00, 0xAA, 0x00, 0x47, 0xBA, 0x4F);

DECLARE_INTERFACE_ (ISRResCorrectionW, IUnknown) {

   // IUnknown members
   STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // ISRResCorrectionW members
   STDMETHOD (Correction)         (THIS_ PSRPHRASEW, WORD) PURE;
   STDMETHOD (Validate)           (THIS_ WORD) PURE;
   };

typedef ISRResCorrectionW FAR *PISRRESCORRECTIONW;


#undef   INTERFACE
#define  INTERFACE   ISRResCorrectionA

DEFINE_GUID(IID_ISRResCorrectionA, 0x05EB6C67L, 0xDBAB, 0x11CD, 0xB3, 0xCA, 0x00, 0xAA, 0x00, 0x47, 0xBA, 0x4F);

DECLARE_INTERFACE_ (ISRResCorrectionA, IUnknown) {

   // IUnknown members
   STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // ISRResCorrectionA members
   STDMETHOD (Correction)         (THIS_ PSRPHRASEA, WORD) PURE;
   STDMETHOD (Validate)           (THIS_ WORD) PURE;
   };

typedef ISRResCorrectionA FAR *PISRRESCORRECTIONA;


#ifdef _S_UNICODE
 #define ISRResCorrection        ISRResCorrectionW
 #define IID_ISRResCorrection    IID_ISRResCorrectionW
 #define PISRRESCORRECTION       PISRRESCORRECTIONW

#else
 #define ISRResCorrection        ISRResCorrectionA
 #define IID_ISRResCorrection    IID_ISRResCorrectionA
 #define PISRRESCORRECTION       PISRRESCORRECTIONA

#endif   // _S_UNICODE



// ISRResEval
// This does not need an ANSI/UNICODE interface because no characters are passed
#undef   INTERFACE
#define  INTERFACE   ISRResEval

// {90CD9A9-DA1A-11CD-B3CA-00AA0047BA4F}
DEFINE_GUID(IID_ISRResEval,
0x090CD9A9, 0xDA1A, 0x11CD, 0xB3, 0xCA, 0x0, 0xAA, 0x0, 0x47, 0xBA, 0x4F);

DECLARE_INTERFACE_ (ISRResEval, IUnknown) {
   // IUnknown members
   STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   //  SRResEval members
   STDMETHOD (ReEvaluate)     (THIS_ BOOL *) PURE;
   };

typedef ISRResEval FAR *PISRRESEVAL;



/*
 * ISRResGraph
 */

#undef   INTERFACE
#define  INTERFACE ISRResGraphW

DEFINE_GUID(IID_ISRResGraphW, 0x090CD9AA, 0xDA1A, 0x11CD, 0xB3, 0xCA, 0x0, 0xAA, 0x0, 0x47, 0xBA, 0x4F);

DECLARE_INTERFACE_ (ISRResGraphW, IUnknown) {

   // IUnknown members
   STDMETHOD (QueryInterface)     (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)       (THIS) PURE;
   STDMETHOD_(ULONG,Release)      (THIS) PURE;

   // ISRResGraphW members         
   STDMETHOD (BestPathPhoneme)    (THIS_ DWORD, DWORD *, DWORD, DWORD *) PURE;
   STDMETHOD (BestPathWord)       (THIS_ DWORD, DWORD *, DWORD, DWORD *) PURE;
   STDMETHOD (GetPhonemeNode)     (THIS_ DWORD, PSRRESPHONEMENODE, PWCHAR, 
                                   PWCHAR) PURE;
   STDMETHOD (GetWordNode)        (THIS_ DWORD, PSRRESWORDNODE, PSRWORDW, DWORD, 
                                   DWORD *) PURE;
   STDMETHOD (PathScorePhoneme)   (THIS_ DWORD *, DWORD, LONG *) PURE;
   STDMETHOD (PathScoreWord)      (THIS_ DWORD *, DWORD, LONG *) PURE;
   };

typedef ISRResGraphW FAR *PISRRESGRAPHW;


#undef   INTERFACE
#define  INTERFACE ISRResGraphA

DEFINE_GUID(IID_ISRResGraphA, 0x05EB6C68L, 0xDBAB, 0x11CD, 0xB3, 0xCA, 0x00, 0xAA, 0x00, 0x47, 0xBA, 0x4F);

DECLARE_INTERFACE_ (ISRResGraphA, IUnknown) {

   // IUnknown members
   STDMETHOD (QueryInterface)     (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)       (THIS) PURE;
   STDMETHOD_(ULONG,Release)      (THIS) PURE;

   // ISRResGraphA members         
   STDMETHOD (BestPathPhoneme)    (THIS_ DWORD, DWORD *, DWORD, DWORD *) PURE;
   STDMETHOD (BestPathWord)       (THIS_ DWORD, DWORD *, DWORD, DWORD *) PURE;
   STDMETHOD (GetPhonemeNode)     (THIS_ DWORD, PSRRESPHONEMENODE, PWCHAR, 
                                   PCHAR) PURE;
   STDMETHOD (GetWordNode)        (THIS_ DWORD, PSRRESWORDNODE, PSRWORDA, DWORD, 
                                   DWORD *) PURE;
   STDMETHOD (PathScorePhoneme)   (THIS_ DWORD *, DWORD, LONG *) PURE;
   STDMETHOD (PathScoreWord)      (THIS_ DWORD *, DWORD, LONG *) PURE;
   };

typedef ISRResGraphA FAR *PISRRESGRAPHA;


#ifdef _S_UNICODE
 #define ISRResGraph             ISRResGraphW
 #define IID_ISRResGraph         IID_ISRResGraphW
 #define PISRRESGRAPH            PISRRESGRAPHW

#else
 #define ISRResGraph             ISRResGraphA
 #define IID_ISRResGraph         IID_ISRResGraphA
 #define PISRRESGRAPH            PISRRESGRAPHA

#endif   // _S_UNICODE



// ISRResMemory
// This does not need an ANSI/UNICODE interface because no characters are passed
#undef   INTERFACE
#define  INTERFACE   ISRResMemory

DEFINE_GUID(IID_ISRResMemory, 0x090CD9AB, 0xDA1A, 0x11CD, 0xB3, 0xCA, 0x0, 0xAA, 0x0, 0x47, 0xBA, 0x4F);

DECLARE_INTERFACE_ (ISRResMemory, IUnknown) {

   // IUnknown members
   STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // ISRResMemory members
   STDMETHOD (Free)           (THIS_ DWORD) PURE;
   STDMETHOD (Get)            (THIS_ DWORD *, DWORD *) PURE;
   STDMETHOD (LockGet)        (THIS_ BOOL *) PURE;
   STDMETHOD (LockSet)        (THIS_ BOOL) PURE;
   };

typedef ISRResMemory FAR *PISRRESMEMORY;



// ISRResModifyGUI
// This does not need an ANSI/UNICODE interface because no characters are passed
#undef   INTERFACE
#define  INTERFACE   ISRResModifyGUI

DEFINE_GUID(IID_ISRResModifyGUI, 0x090CD9AC, 0xDA1A, 0x11CD, 0xB3, 0xCA, 0x0, 0xAA, 0x0, 0x47, 0xBA, 0x4F);

DECLARE_INTERFACE_ (ISRResModifyGUI, IUnknown) {

   // IUnknown members
   STDMETHOD (QueryInterface)    (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)      (THIS) PURE;
   STDMETHOD_(ULONG,Release)     (THIS) PURE;

   // ISRResModifyGUI members
   STDMETHOD (Hide)              (THIS) PURE;
   STDMETHOD (Move)              (THIS_ RECT *) PURE;
   STDMETHOD (Show)              (THIS_ HWND) PURE;
   };

typedef ISRResModifyGUI FAR *PISRRESMODIFYGUI;



/*
 * ISRResSpeakerW
 */

#undef   INTERFACE
#define  INTERFACE   ISRResSpeakerW

DEFINE_GUID(IID_ISRResSpeakerW, 0x090CD9AD, 0xDA1A, 0x11CD, 0xB3, 0xCA, 0x0, 0xAA, 0x0, 0x47, 0xBA, 0x4F);

DECLARE_INTERFACE_ (ISRResSpeakerW, IUnknown) {

   // IUnknown members
   STDMETHOD (QueryInterface)    (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)      (THIS) PURE;
   STDMETHOD_(ULONG,Release)     (THIS) PURE;

   // ISRResSpeakerW members
   STDMETHOD (Correction)        (THIS_ PCWSTR, WORD) PURE;
   STDMETHOD (Validate)          (THIS_ WORD) PURE;
   STDMETHOD (Identify)          (THIS_ DWORD, PWSTR, DWORD, DWORD *, 
                                  LONG *) PURE;
   STDMETHOD (IdentifyForFree)   (THIS_ BOOL *) PURE;
   };

typedef ISRResSpeakerW FAR *PISRRESSPEAKERW;


#undef   INTERFACE
#define  INTERFACE   ISRResSpeakerA

DEFINE_GUID(IID_ISRResSpeakerA, 0x05EB6C69L, 0xDBAB, 0x11CD, 0xB3, 0xCA, 0x00, 0xAA, 0x00, 0x47, 0xBA, 0x4F);

DECLARE_INTERFACE_ (ISRResSpeakerA, IUnknown) {

   // IUnknown members
   STDMETHOD (QueryInterface)    (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)      (THIS) PURE;
   STDMETHOD_(ULONG,Release)     (THIS) PURE;

   // ISRResSpeakerA members
   STDMETHOD (Correction)        (THIS_ PCSTR, WORD) PURE;
   STDMETHOD (Validate)          (THIS_ WORD) PURE;
   STDMETHOD (Identify)          (THIS_ DWORD, PSTR, DWORD, DWORD *, 
                                  LONG *) PURE;
   STDMETHOD (IdentifyForFree)   (THIS_ BOOL *) PURE;
   };

typedef ISRResSpeakerA FAR *PISRRESSPEAKERA;


#ifdef _S_UNICODE
 #define ISRResSpeaker           ISRResSpeakerW
 #define IID_ISRResSpeaker       IID_ISRResSpeakerW
 #define PISRRESSPEAKER          PISRRESSPEAKERW

#else
 #define ISRResSpeaker           ISRResSpeakerA
 #define IID_ISRResSpeaker       IID_ISRResSpeakerA
 #define PISRRESSPEAKER          PISRRESSPEAKERA

#endif   // _S_UNICODE



/*
 * ISRSpeaker
 */

#undef   INTERFACE
#define  INTERFACE   ISRSpeakerW

DEFINE_GUID(IID_ISRSpeakerW, 0x090CD9AE, 0xDA1A, 0x11CD, 0xB3, 0xCA, 0x0, 0xAA, 0x0, 0x47, 0xBA, 0x4F);

DECLARE_INTERFACE_ (ISRSpeakerW, IUnknown) {

   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // ISRSpeakerW members
   STDMETHOD (Delete)         (THIS_ PCWSTR) PURE;
   STDMETHOD (Enum)           (THIS_ PWSTR *, DWORD *) PURE;
   STDMETHOD (Merge)          (THIS_ PCWSTR, PVOID, DWORD) PURE;
   STDMETHOD (New)            (THIS_ PCWSTR) PURE;
   STDMETHOD (Query)          (THIS_ PWSTR, DWORD, DWORD *) PURE;
   STDMETHOD (Read)           (THIS_ PCWSTR, PVOID *, DWORD *) PURE;
   STDMETHOD (Revert)         (THIS_ PCWSTR) PURE;
   STDMETHOD (Select)         (THIS_ PCWSTR, BOOL) PURE;
   STDMETHOD (Write)          (THIS_ PCWSTR, PVOID, DWORD) PURE;
   };

typedef ISRSpeakerW FAR *PISRSPEAKERW;


#undef   INTERFACE
#define  INTERFACE   ISRSpeakerA

DEFINE_GUID(IID_ISRSpeakerA, 0x090CD9AF, 0xDA1A, 0x11CD, 0xB3, 0xCA, 0x0, 0xAA, 0x0, 0x47, 0xBA, 0x4F);

DECLARE_INTERFACE_ (ISRSpeakerA, IUnknown) {

   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // ISRSpeakerA members
   STDMETHOD (Delete)         (THIS_ PCSTR) PURE;
   STDMETHOD (Enum)           (THIS_ PSTR *, DWORD *) PURE;
   STDMETHOD (Merge)          (THIS_ PCSTR, PVOID, DWORD) PURE;
   STDMETHOD (New)            (THIS_ PCSTR) PURE;
   STDMETHOD (Query)          (THIS_ PSTR, DWORD, DWORD *) PURE;
   STDMETHOD (Read)           (THIS_ PCSTR, PVOID *, DWORD *) PURE;
   STDMETHOD (Revert)         (THIS_ PCSTR) PURE;
   STDMETHOD (Select)         (THIS_ PCSTR, BOOL) PURE;
   STDMETHOD (Write)          (THIS_ PCSTR, PVOID, DWORD) PURE;
   };

typedef ISRSpeakerA FAR *PISRSPEAKERA;


#ifdef _S_UNICODE
 #define ISRSpeaker              ISRSpeakerW
 #define IID_ISRSpeaker          IID_ISRSpeakerW
 #define PISRSPEAKER             PISRSPEAKERW

#else
 #define ISRSpeaker              ISRSpeakerA
 #define IID_ISRSpeaker          IID_ISRSpeakerA
 #define PISRSPEAKER             PISRSPEAKERA

#endif   // _S_UNICODE


/*
ISRPhrase related definitions
*/
#define SRPHRASE_SI             (0x01000000)
#define SRPHRASE_SI_ENABLE      (0x02000000)
#define SRPHRASE_SD             (0x04000000)
#define SRPHRASE_SD_ENABLE      (0x08000000)
#define SRPHRASE_SD_ERASE       (0x10000000)
#define SRPHRASE_PERMANENT      (0x80000000)

//  TrainDone flag
#define SRTRAIN_DONE            (0x00000000)
#define SRTRAIN_FAILED          (0x00010000)
#define SRTRAIN_NEEDMORE        (0x00020000)
#define SRTRAIN_STOPPED         (0x00040000)

//  TrainControl flags
#define SRTRAIN_CANCEL          (0x00100000)
#define SRTRAIN_GOBACK          (0x00200000)
#define SRTRAIN_CONFIRM         (0x00400000)

/*
 * ISRTrainNotifySink
 */

#undef   INTERFACE
#define  INTERFACE   ISRTrainNotifySinkW

// {C29FBD90-A30D-11d0-91E1-00A0C913CAD7}
DEFINE_GUID(IID_ISRTrainNotifySinkW, 0xc29fbd90, 0xa30d, 0x11d0, 0x91, 0xe1, 0x0, 0xa0, 0xc9, 0x13, 0xca, 0xd7);

DECLARE_INTERFACE_ (ISRTrainNotifySinkW, IUnknown) {

// IUnknown members
   STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

// ISRTrainNotifySinkW members
   STDMETHOD (TrainReady)     (THIS_ DWORD) PURE;
   STDMETHOD (PhraseStart)    (THIS_ DWORD, QWORD) PURE;
   STDMETHOD (PhraseFinish)   (THIS_ DWORD, QWORD, QWORD) PURE;
   STDMETHOD (TrainDone)      (THIS_ DWORD, DWORD) PURE;
   };

typedef ISRTrainNotifySinkW FAR * PISRTRAINNOTIFYSINKW;


#ifdef _S_UNICODE
 #define ISRTrainNotifySink     ISRTrainNotifySinkW
 #define IID_ISRTrainNotifySink IID_ISRTrainNotifySinkW
 #define PISRTRAINNOTIFYSINK    PISRTRAINNOTIFYSINKW
#endif

/*
 * ISRPhrase
 */

#undef   INTERFACE
#define  INTERFACE   ISRPhraseW

// {8ECD51F0-9B5B-11d0-91D6-00A0C913CAD7}
DEFINE_GUID(IID_ISRPhraseW, 0x8ecd51f0, 0x9b5b, 0x11d0, 0x91, 0xd6, 0x0, 0xa0, 0xc9, 0x13, 0xca, 0xd7);

DECLARE_INTERFACE_ (ISRPhraseW, IUnknown) {

   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // ISRPhraseW members
   STDMETHOD (QueryPhrase)    (THIS_ PWSTR, DWORD *) PURE;
   STDMETHOD (ModifyTraining) (THIS_ PWSTR, DWORD) PURE;
   STDMETHOD (TrainPhrase)    (THIS_ PWSTR, PISRTRAINNOTIFYSINKW) PURE;
   STDMETHOD (TrainControl)   (THIS_ DWORD) PURE;
   STDMETHOD (WordsGet)       (THIS_ DWORD, PWSTR *, PDWORD) PURE;
   STDMETHOD (InstallSix)     (THIS_ LPCTSTR, PDWORD, DWORD) PURE;
   STDMETHOD (UnInstallSix)   (THIS_ DWORD, DWORD) PURE;
   };

typedef ISRPhraseW FAR *PISRPHRASEW;

#ifdef _S_UNICODE
 #define ISRPhrase              ISRPhraseW
 #define IID_ISRPhrase          IID_ISRPhraseW
 #define PISRPHRASE             PISRPHRASEW
#endif   // _S_UNICODE


#undef   INTERFACE
#define  INTERFACE   IVCmdUserWordW

// {93D03F81-A65F-11d0-91E1-00A0C913CAD7}
DEFINE_GUID(IID_IVCmdUserWordW, 0x93d03f81, 0xa65f, 0x11d0, 0x91, 0xe1, 0x0, 0xa0, 0xc9, 0x13, 0xca, 0xd7);

/**
 * This interface allows an application to enable the speaker-dependent and speaker-independent
 * templates, and to add new words to the speaker-dependent template.
 *
 * This interface is an extension of the Speech API (SAPI), added to meet the needs of the Auto PC.
 * It is designed specifically for an isolated-word recognizer. Any method call on this interface
 * affects the current speaker only.
 *
 * Templates hold information that the engine uses to recognize a phrase. There are two types of
 * templates for the Auto PC: speaker independent and speaker dependent. There is one
 * speaker-independent template for each phrase. Speaker independent recognition can only be enabled
 * or disabled. It cannot be modified by the user. Each speaker can have one speaker-dependent
 * template for each phrase. To create a speaker-dependent template, a user must train the object to
 * recognize their particular speech pattern.
 *
 * The two templates operate independently of each other. An application can enable a
 * speaker-dependent template whether or not the speaker-independent template is available. Enabling
 * both templates may achieve better recognition accuracy.
 */
DECLARE_INTERFACE_ (IVCmdUserWordW, IUnknown) {

   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // IVCmdUserWordW members
   /**
    * This method determines what kind of templates a phrase has and whether or not they are enabled.
    *
    * @param lpszPhrase Long pointer to the null-terminated string that contains the phrase of
    *   interest.
    * @param pdwValue Pointer to the bitmask of flags that indicate the training templates associated
    *   with the phrase. It is one of the following values: - SRPHRASE_SI: Specifies the speaker
    *   independent template. - SRPHRASE_SD: Specifies the speaker dependent template. -
    *   SRPHRASE_SI_ENABLE: The speaker-independent template is enabled/disabled. - SRPHRASE_SD_ENABLE:
    *   The speaker-dependent template is enabled/disabled.
    *
    * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
    */
   STDMETHOD (QueryPhrase)    (THIS_ PWSTR, DWORD *) PURE;
   /**
    * This method specifies which templates are enabled for a particular phrase.
    *
    * @param lpszPhrase Long pointer to the null-terminated string that contains the phrase of
    *   interest.
    * @param dwFlags Specifies a bitmask of flags. It is one of the following values: - SRPHRASE_SI:
    *   Specifies the speaker independent template. - SRPHRASE_SD: Specifies the speaker dependent
    *   template. - SRPHRASE_SI_ENABLE: Enables or disables a phrase on the speaker-independent template.
    *   - SRPHRASE_SD_ENABLE: Enables or disables a phrase on the speaker-dependent template. -
    *   SRPHRASE_SD_ERASE: Erases the speaker-dependent template for a phrase. - SRPHRASE_PERMANENT: When
    *   set, makes any changes permanent.
    *
    * @return - NOERROR: The method successfully specified the templates that are enabled for a
    *   particular phrase. - SRERR_PHRASENOTFOUND: The phrase was not found in either template. -
    *   SRERR_TEMPLATENOTFOUND: The template is not available.
    *
    * Templates are enabled independently of each other. Either or both may be enabled at any time.
    * When setting a flag to enable or disable a template, the corresponding flag to select the
    * template must also be set. For example, to enable the speaker-dependent template, use SRPHRASE_SD
    * | SRPHRASE_SD_ENABLE.
    */
   STDMETHOD (ModifyTraining) (THIS_ PWSTR, DWORD) PURE;
   /**
    * This method is called by the application to train a list of user-defined phrases.
    *
    * @param lpPhrases Long pointer to a null-terminated text string consisting of the phrase to be
    *   trained.
    * @param dwSize Specifies a DWORD that contains the number of bytes in the string pointed to by
    *   lpPhrases.
    * @param lpCaption Long pointer to the string that contains the title caption of the training form.
    * @param dwSizeCap Specifies a DWORD that contains the number of bytes in the caption string
    *   pointed to by lpCaption.
    * @param hHandle Reserved, must be 0.
    * @param dwFlags Reserved, must be 0.
    *
    * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
    */
   STDMETHOD (Train)          (THIS_ PCWSTR, DWORD, PCWSTR, DWORD, DWORD=0, DWORD=0) PURE;
   /**
    * This method gets the words in the installed vocabulary.
    *
    * @param dwFlags Specifies a bitmask of flags. It is one or a combination of the following flags: -
    *   SRPHRASE_SI: Returns the speaker-independent list. - SRPHRASE_SD: Returns the speaker-dependent
    *   list. If both flags are set, the combined list is returned.
    * @param pszBuf Pointer to the buffer where the phrase list is stored. The buffer contains a list
    *   of null-terminated strings. The list is terminated by two consecutive null characters.
    * @param pdwSize Pointer to the size of the buffer allocated to hold the list, in bytes. If the
    *   method returns successfully, it holds the actual number of bytes in the buffer.
    *
    * @return NOERROR indicates success. VCMDERR_VALUEOUTOFRANGE indicates that the buffer is too
    *   small. When this occurs, GetPhraseList sets pdwSize to the buffer size needed. If dwFlags is set
    *   to SRPHRASE_SI and the speech engine supports any word-for example, if the engine is a
    *   phomeme-based continuous engine-the function returns S_FALSE. If an error occurs, the appropriate
    *   HRESULT value is returned.
    *
    * If both SRPHRASE_SI and SRPHRASE_SD are set, and if a word has both speaker-independent and
    * speaker-dependent templates, the same word appears twice in the buffer.
    */
   STDMETHOD (GetPhraseList)  (THIS_ DWORD, PWSTR, PDWORD) PURE;
   /**
    * This method installs speaker-independent template extension files.
    *
    * @param lpszFile Long pointer to the null-terminated string that contains the path of the file to
    *   install.
    * @param pdwID Pointer to a DWORD that contains an identification number of the independent
    *   template to install.
    * @param dwFlag Reserved, must be 0.
    *
    * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
    *
    * This method is usually called in the Auto PC setup program.
    */
   STDMETHOD (AddSIFile)      (THIS_ LPCWSTR, PDWORD, DWORD) PURE;
   /**
    * This method removes speaker-independent template extension files.
    *
    * @param dwID Specifies a DWORD that contains an identification number of the independent template
    *   to remove.
    * @param dwFlag Reserved, must be 0.
    *
    * @return NOERROR indicates success. If an error occurs, the appropriate HRESULT value is returned.
    */
   STDMETHOD (RemoveSIFile)   (THIS_ DWORD, DWORD) PURE;
   };

typedef IVCmdUserWordW FAR *PIVCMDUSERWORDW;

#ifdef _S_UNICODE
 /**
  * This interface allows an application to enable the speaker-dependent and speaker-independent
  * templates, and to add new words to the speaker-dependent template.
  *
  * This interface is an extension of the Speech API (SAPI), added to meet the needs of the Auto PC.
  * It is designed specifically for an isolated-word recognizer. Any method call on this interface
  * affects the current speaker only.
  *
  * Templates hold information that the engine uses to recognize a phrase. There are two types of
  * templates for the Auto PC: speaker independent and speaker dependent. There is one
  * speaker-independent template for each phrase. Speaker independent recognition can only be enabled
  * or disabled. It cannot be modified by the user. Each speaker can have one speaker-dependent
  * template for each phrase. To create a speaker-dependent template, a user must train the object to
  * recognize their particular speech pattern.
  *
  * The two templates operate independently of each other. An application can enable a
  * speaker-dependent template whether or not the speaker-independent template is available. Enabling
  * both templates may achieve better recognition accuracy.
  */
 #define IVCmdUserWord          IVCmdUserWordW
 #define IID_IVCmdUserWord      IID_IVCmdUserWordW
 #define PIVCMDUSERWORD         PIVCMDUSERWORDW
#endif   // _S_UNICODE


/************************************************************************
Low-Level text-to-speech API
*/


/************************************************************************
defines */

#define  TTSI_NAMELEN                   SVFN_LEN
#define  TTSI_STYLELEN                  SVFN_LEN

#define  GENDER_NEUTRAL                 (0)
#define  GENDER_FEMALE                  (1)
#define  GENDER_MALE                    (2)

#define  TTSFEATURE_ANYWORD             SETBIT(0)
#define  TTSFEATURE_VOLUME              SETBIT(1)
#define  TTSFEATURE_SPEED               SETBIT(2)
#define  TTSFEATURE_PITCH               SETBIT(3)
#define  TTSFEATURE_TAGGED              SETBIT(4)
#define  TTSFEATURE_IPAUNICODE          SETBIT(5)
#define  TTSFEATURE_VISUAL              SETBIT(6)
#define  TTSFEATURE_WORDPOSITION        SETBIT(7)
#define  TTSFEATURE_PCOPTIMIZED         SETBIT(8)
#define  TTSFEATURE_PHONEOPTIMIZED      SETBIT(9)

#define  TTSI_ILEXPRONOUNCE             SETBIT(0)
#define  TTSI_ITTSATTRIBUTES            SETBIT(1)
#define  TTSI_ITTSCENTRAL               SETBIT(2)
#define  TTSI_ITTSDIALOGS               SETBIT(3)

#define  TTSDATAFLAG_TAGGED             SETBIT(0)

#define   TTSBNS_ABORTED                   SETBIT(0)

// ITTSNotifySink
#define   TTSNSAC_REALTIME               0
#define   TTSNSAC_PITCH                  1
#define   TTSNSAC_SPEED                  2
#define   TTSNSAC_VOLUME                 3


#define   TTSNSHINT_QUESTION             SETBIT(0)
#define   TTSNSHINT_STATEMENT            SETBIT(1)
#define   TTSNSHINT_COMMAND              SETBIT(2)
#define   TTSNSHINT_EXCLAMATION          SETBIT(3)
#define   TTSNSHINT_EMPHASIS             SETBIT(4)


// Ages
#define  TTSAGE_BABY                   1
#define  TTSAGE_TODDLER                3
#define  TTSAGE_CHILD                  6
#define  TTSAGE_ADOLESCENT             14
#define  TTSAGE_ADULT                  30
#define  TTSAGE_ELDERLY                70

// Attribute minimums and maximums
#define  TTSATTR_MINPITCH              0
#define  TTSATTR_MAXPITCH              0xffff
#define  TTSATTR_MINREALTIME           0
#define  TTSATTR_MAXREALTIME           0xffffffff
#define  TTSATTR_MINSPEED              0
#define  TTSATTR_MAXSPEED              0xffffffff
#define  TTSATTR_MINVOLUME             0
#define  TTSATTR_MAXVOLUME             0xffffffff


/************************************************************************
typedefs */

typedef struct {
   BYTE     bMouthHeigght;
   BYTE     bMouthWidth;
   BYTE     bMouthUpturn;
   BYTE     bJawOpen;
   BYTE     bTeethUpperVisible;
   BYTE     bTeethLowerVisible;
   BYTE     bTonguePosn;
   BYTE     bLipTension;
   } TTSMOUTH, *PTTSMOUTH;



/**
 * This structure provides detailed information about a text-to-speech (TTS) mode supported by a
 * particular engine.
 */
typedef struct {
   /**
    * Globally unique identifier (GUID) that identifies the engine. The GUID can be generated randomly
    * using Guidgen.exe, which is provided with the Microsoft OLE Software Development Kit (SDK). It is
    * possible for more than one mode to have the same engine identifier. In this case, the engine is
    * capable of speaking the different languages or voices of the modes.
    */
   GUID       gEngineID;
   /**
    * Null-terminated string that contains the name of the manufacturer .
    */
   WCHAR      szMfgName[TTSI_NAMELEN];
   /**
    * Null-terminated string that contains the name of the product.
    */
   WCHAR      szProductName[TTSI_NAMELEN];
   /**
    * Globally unique identifier (GUID) of the mode. These numbers are guaranteed to be unique, so it
    * is not necessary to monitor and record them. In addition, the GUID is not stored or used directly
    * by OLE, so it is not necessary to load it into the registry.
    */
   GUID       gModeID;
   /**
    * Null-terminated string that contains the name of the TTS mode.
    */
   WCHAR      szModeName[TTSI_NAMELEN];
   /**
    * Specifies the LANGUAGE structure that contains the name of the language and dialect.
    */
   LANGUAGEW  language;
   /**
    * Null-terminated string that contains the name of the voice, or NULL if the name is not important.
    */
   WCHAR      szSpeaker[TTSI_NAMELEN];
   /**
    * Null-terminated string that indicates the personality of the voice - for example, business,
    * casual, computer, excited, or singsong.
    */
   WCHAR      szStyle[TTSI_STYLELEN];
   /**
    * Specifies the gender of the voice. It is one of the following values:
    *
    * - GENDER_FEMALE: A female voice is used.
    *
    * - GENDER_MALE: A male voice is used.
    *
    * - GENDER_NEUTRAL: The voice used is not perceptibly male or female.
    */
   WORD       wGender;
   /**
    * Specifies the age of the voice. It is one of the following values, with all ages being
    * approximate:
    *
    * - TTSAGE_BABY: The voice is that of a 1-year-old.
    *
    * - TTSAGE_TODDLER: The voice is that of a 3-year-old.
    *
    * - TTSAGE_CHILD: The voice is that of a 6-year-old.
    *
    * - TTSAGE_ADOLESCENT: The voice is that of a 14-year-old.
    *
    * - TTSAGE_ADULT: The voice is that of someone between 20 and 60 years old.
    *
    * - TTSAGE_ELDERLY: The voice is that of someone over 60 years old.
    */
   WORD       wAge;
   /**
    * Specifies the TTS features that are available. It is a combination of the following flags:
    *
    * - TTSFEATURE_ANYWORD: The engine can attempt to read any word.
    *
    * - TTSFEATURE_PCOPTIMIZED: The voice is optimized to work over the computer, which provides better
    * sound quality.
    *
    * - TTSFEATURE_PHONEOPTIMIZED: The voice is designed to work over the telephone and uses an
    * 8-kilohertz (kHz) sampling rate.
    *
    * - TTSFEATURE_PITCH: The engine can adjust the pitch of the voice while the engine is speaking.
    *
    * - TTSFEATURE_SPEED: The engine can adjust the speed of the voice while the engine is speaking.
    *
    * - TTSFEATURE_TAGGED: The engine can interpret tagged text to control the voice.
    *
    * - TTSFEATURE_VISUAL: The engine can provide mouth position information for the voice.
    *
    * - TTSFEATURE_VOLUME: The engine can adjust the volume of the voice.
    *
    * - TTSFEATURE_WORDPOSITION: The engine sends notification of word position.
    */
   DWORD      dwFeatures;
   /**
    * Specifies the interfaces supported by the engine. It is a combination of the following flags:
    *
    * - TTSI_ILEXPRONOUNCE: Use the ILexPronounce interface.
    *
    * - TTSI_ITTSATTRIBUTES: Use the ITTSAttributes interface.
    *
    * - TTSI_ITTSCENTRAL: Use the ITTSCentral interface.
    *
    * - TTSI_ITTSDIALOGS: Use the ITTSDialogs interface.
    */
   DWORD      dwInterfaces;
   /**
    * Specifies features of a particular engine. These values are defined by the engine author. For
    * more information about engine features, see the documentation for the engine.
    *
    * In order to identify which engine is being used, an application can use the ITTSEnum interface to
    * enumerate the engines. Its features can then be determined.
    */
   DWORD      dwEngineFeatures;
   } TTSMODEINFOW, *PTTSMODEINFOW;

/**
 * This structure provides detailed information about a text-to-speech (TTS) mode supported by a
 * particular engine.
 */
typedef struct {
   /**
    * Globally unique identifier (GUID) that identifies the engine. The GUID can be generated randomly
    * using Guidgen.exe, which is provided with the Microsoft OLE Software Development Kit (SDK). It is
    * possible for more than one mode to have the same engine identifier. In this case, the engine is
    * capable of speaking the different languages or voices of the modes.
    */
   GUID       gEngineID;
   /**
    * Null-terminated string that contains the name of the manufacturer .
    */
   CHAR       szMfgName[TTSI_NAMELEN];
   /**
    * Null-terminated string that contains the name of the product.
    */
   CHAR       szProductName[TTSI_NAMELEN];
   /**
    * Globally unique identifier (GUID) of the mode. These numbers are guaranteed to be unique, so it
    * is not necessary to monitor and record them. In addition, the GUID is not stored or used directly
    * by OLE, so it is not necessary to load it into the registry.
    */
   GUID       gModeID;
   /**
    * Null-terminated string that contains the name of the TTS mode.
    */
   CHAR       szModeName[TTSI_NAMELEN];
   /**
    * Specifies the LANGUAGE structure that contains the name of the language and dialect.
    */
   LANGUAGEA  language;
   /**
    * Null-terminated string that contains the name of the voice, or NULL if the name is not important.
    */
   CHAR       szSpeaker[TTSI_NAMELEN];
   /**
    * Null-terminated string that indicates the personality of the voice - for example, business,
    * casual, computer, excited, or singsong.
    */
   CHAR       szStyle[TTSI_STYLELEN];
   /**
    * Specifies the gender of the voice. It is one of the following values:
    *
    * - GENDER_FEMALE: A female voice is used.
    *
    * - GENDER_MALE: A male voice is used.
    *
    * - GENDER_NEUTRAL: The voice used is not perceptibly male or female.
    */
   WORD       wGender;
   /**
    * Specifies the age of the voice. It is one of the following values, with all ages being
    * approximate:
    *
    * - TTSAGE_BABY: The voice is that of a 1-year-old.
    *
    * - TTSAGE_TODDLER: The voice is that of a 3-year-old.
    *
    * - TTSAGE_CHILD: The voice is that of a 6-year-old.
    *
    * - TTSAGE_ADOLESCENT: The voice is that of a 14-year-old.
    *
    * - TTSAGE_ADULT: The voice is that of someone between 20 and 60 years old.
    *
    * - TTSAGE_ELDERLY: The voice is that of someone over 60 years old.
    */
   WORD       wAge;
   /**
    * Specifies the TTS features that are available. It is a combination of the following flags:
    *
    * - TTSFEATURE_ANYWORD: The engine can attempt to read any word.
    *
    * - TTSFEATURE_PCOPTIMIZED: The voice is optimized to work over the computer, which provides better
    * sound quality.
    *
    * - TTSFEATURE_PHONEOPTIMIZED: The voice is designed to work over the telephone and uses an
    * 8-kilohertz (kHz) sampling rate.
    *
    * - TTSFEATURE_PITCH: The engine can adjust the pitch of the voice while the engine is speaking.
    *
    * - TTSFEATURE_SPEED: The engine can adjust the speed of the voice while the engine is speaking.
    *
    * - TTSFEATURE_TAGGED: The engine can interpret tagged text to control the voice.
    *
    * - TTSFEATURE_VISUAL: The engine can provide mouth position information for the voice.
    *
    * - TTSFEATURE_VOLUME: The engine can adjust the volume of the voice.
    *
    * - TTSFEATURE_WORDPOSITION: The engine sends notification of word position.
    */
   DWORD      dwFeatures;
   /**
    * Specifies the interfaces supported by the engine. It is a combination of the following flags:
    *
    * - TTSI_ILEXPRONOUNCE: Use the ILexPronounce interface.
    *
    * - TTSI_ITTSATTRIBUTES: Use the ITTSAttributes interface.
    *
    * - TTSI_ITTSCENTRAL: Use the ITTSCentral interface.
    *
    * - TTSI_ITTSDIALOGS: Use the ITTSDialogs interface.
    */
   DWORD      dwInterfaces;
   /**
    * Specifies features of a particular engine. These values are defined by the engine author. For
    * more information about engine features, see the documentation for the engine.
    *
    * In order to identify which engine is being used, an application can use the ITTSEnum interface to
    * enumerate the engines. Its features can then be determined.
    */
   DWORD      dwEngineFeatures;
   } TTSMODEINFOA, *PTTSMODEINFOA;

#ifdef _S_UNICODE
 #define TTSMODEINFO         TTSMODEINFOW
 #define PTTSMODEINFO        PTTSMODEINFOW

#else
 #define TTSMODEINFO         TTSMODEINFOA
 #define PTTSMODEINFO        PTTSMODEINFOA

#endif   // _S_UNICODE



/**
 * This structure ranks the members of the TTSMODEINFO structure in order of importance.
 *
 * Each member of the TTSMODEINFORANK structure contains a priority value for the corresponding
 * feature. Values are relative to each other - that is, a higher value indicates a higher priority,
 * but the value itself is not meaningful.
 */
typedef struct {
   /**
    * Specifies the relative importance of a matching engine identifier.
    */
   DWORD      dwEngineID;
   /**
    * Specifies the relative importance of the specified manufacturer name.
    */
   DWORD      dwMfgName;
   /**
    * Specifies the relative importance of the specified product name.
    */
   DWORD      dwProductName;
   /**
    * Specifies the relative importance of a matching mode identifier.
    */
   DWORD      dwModeID;
   /**
    * Specifies the relative importance of the specified mode name.
    */
   DWORD      dwModeName;
   /**
    * Specifies the relative importance of the specified language.
    */
   DWORD      dwLanguage;
   /**
    * Specifies the relative importance of the specified dialect. This value is stored in the LANGUAGE
    * structure of TTSMODEINFO.
    */
   DWORD      dwDialect;
   /**
    * Specifies the relative importance of the requested speaker.
    */
   DWORD      dwSpeaker;
   /**
    * Specifies the relative importance of the requested speaking style.
    */
   DWORD      dwStyle;
   /**
    * Specifies the relative importance of the requested gender.
    */
   DWORD      dwGender;
   /**
    * Specifies the relative importance of the requested age. The text-to-speech (TTS) mode that is
    * closest to the requested age is selected.
    */
   DWORD      dwAge;
   /**
    * Specifies the relative importance of the requested features. Modes that lack the features
    * requested are eliminated from consideration.
    */
   DWORD      dwFeatures;
   /**
    * Specifies the relative importance of the requested interfaces. Modes that lack the interfaces
    * requested are eliminated from consideration.
    */
   DWORD      dwInterfaces;
   /**
    * Specifies the relative importance of the requested engine features. Modes that lack the features
    * requested are eliminated from consideration.
    */
   DWORD      dwEngineFeatures;
   } TTSMODEINFORANK, * PTTSMODEINFORANK;

/************************************************************************
Class IDs */
// {D67C0280-C743-11cd-80E5-00AA003E4B50}
DEFINE_GUID(CLSID_TTSEnumerator, 
0xd67c0280, 0xc743, 0x11cd, 0x80, 0xe5, 0x0, 0xaa, 0x0, 0x3e, 0x4b, 0x50);

/************************************************************************
interfaces */

// ITTSAttributes

#undef   INTERFACE
#define  INTERFACE   ITTSAttributesW

DEFINE_GUID(IID_ITTSAttributesW, 0x1287A280L, 0x4A47, 0x101B, 0x93, 0x1A, 0x00, 0xAA, 0x00, 0x47, 0xBA, 0x4F);

DECLARE_INTERFACE_ (ITTSAttributesW, IUnknown) {

// IUnknown members

   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

// ITTSAttributes members

   STDMETHOD (PitchGet)       (THIS_ WORD *) PURE;
   STDMETHOD (PitchSet)       (THIS_ WORD) PURE;  
   STDMETHOD (RealTimeGet)    (THIS_ DWORD *) PURE;
   STDMETHOD (RealTimeSet)    (THIS_ DWORD) PURE;  
   STDMETHOD (SpeedGet)       (THIS_ DWORD *) PURE;
   STDMETHOD (SpeedSet)       (THIS_ DWORD) PURE;  
   STDMETHOD (VolumeGet)      (THIS_ DWORD *) PURE;
   STDMETHOD (VolumeSet)      (THIS_ DWORD) PURE;  
   };

typedef ITTSAttributesW FAR * PITTSATTRIBUTESW;


#undef   INTERFACE
#define  INTERFACE   ITTSAttributesA

DEFINE_GUID(IID_ITTSAttributesA,
0x0FD6E2A1L, 0xE77D, 0x11CD, 0xB3, 0xCA, 0x00, 0xAA, 0x00, 0x47, 0xBA, 0x4F);

DECLARE_INTERFACE_ (ITTSAttributesA, IUnknown) {

// IUnknown members

   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

// ITTSAttributes members

   STDMETHOD (PitchGet)       (THIS_ WORD *) PURE;
   STDMETHOD (PitchSet)       (THIS_ WORD) PURE;  
   STDMETHOD (RealTimeGet)    (THIS_ DWORD *) PURE;
   STDMETHOD (RealTimeSet)    (THIS_ DWORD) PURE;  
   STDMETHOD (SpeedGet)       (THIS_ DWORD *) PURE;
   STDMETHOD (SpeedSet)       (THIS_ DWORD) PURE;  
   STDMETHOD (VolumeGet)      (THIS_ DWORD *) PURE;
   STDMETHOD (VolumeSet)      (THIS_ DWORD) PURE;  
   };

typedef ITTSAttributesA FAR * PITTSATTRIBUTESA;


#ifdef _S_UNICODE
 #define ITTSAttributes          ITTSAttributesW
 #define IID_ITTSAttributes      IID_ITTSAttributesW
 #define PITTSATTRIBUTES         PITTSATTRIBUTESW

#else
 #define ITTSAttributes          ITTSAttributesA
 #define IID_ITTSAttributes      IID_ITTSAttributesA
 #define PITTSATTRIBUTES         PITTSATTRIBUTESA

#endif   // _S_UNICODE



// ITTSBufNotifySink

#undef   INTERFACE
#define  INTERFACE   ITTSBufNotifySink

// {E4963D40-C743-11cd-80E5-00AA003E4B50}
DEFINE_GUID(IID_ITTSBufNotifySink, 
0xe4963d40, 0xc743, 0x11cd, 0x80, 0xe5, 0x0, 0xaa, 0x0, 0x3e, 0x4b, 0x50);

DECLARE_INTERFACE_ (ITTSBufNotifySink, IUnknown) {

// IUnknown members

   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

// ITTSBufNotifySink members

   STDMETHOD (TextDataDone)   (THIS_ QWORD, DWORD) PURE;
   STDMETHOD (TextDataStarted)(THIS_ QWORD) PURE;
   STDMETHOD (BookMark)       (THIS_ QWORD, DWORD) PURE;  
   STDMETHOD (WordPosition)   (THIS_ QWORD, DWORD) PURE;
   };

typedef ITTSBufNotifySink FAR * PITTSBUFNOTIFYSINK;

// In case anyone uses the W or A interface
#define ITTSBufNotifySinkW          ITTSBufNotifySink
#define IID_ITTSBufNotifySinkW      IID_ITTSBufNotifySink
#define PITTSBUFNOTIFYSINKW         PITTSBUFNOTIFYSINK
#define ITTSBufNotifySinkA          ITTSBufNotifySink
#define IID_ITTSBufNotifySinkA      IID_ITTSBufNotifySink
#define PITTSBUFNOTIFYSINKA         PITTSBUFNOTIFYSINK



/*
 * ITTSCentral
 */

#undef   INTERFACE
#define  INTERFACE   ITTSCentralW

DEFINE_GUID(IID_ITTSCentralW, 0x28016060L, 0x4A47, 0x101B, 0x93, 0x1A, 0x00, 0xAA, 0x00, 0x47, 0xBA, 0x4F);

DECLARE_INTERFACE_ (ITTSCentralW, IUnknown) {

   // IUnknown members
   STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // ITTSCentralW members
   STDMETHOD (Inject)         (THIS_ PCWSTR) PURE;
   STDMETHOD (ModeGet)        (THIS_ PTTSMODEINFOW) PURE;
   STDMETHOD (Phoneme)        (THIS_ VOICECHARSET, DWORD, SDATA, PSDATA) PURE;
   STDMETHOD (PosnGet)        (THIS_ PQWORD) PURE;
   STDMETHOD (TextData)       (THIS_ VOICECHARSET, DWORD, SDATA, PVOID, IID) PURE;
   STDMETHOD (ToFileTime)     (THIS_ PQWORD, FILETIME *) PURE;
   STDMETHOD (AudioPause)     (THIS) PURE;
   STDMETHOD (AudioResume)    (THIS) PURE;
   STDMETHOD (AudioReset)     (THIS) PURE;
   STDMETHOD (Register)       (THIS_ PVOID, IID, DWORD*) PURE;
   STDMETHOD (UnRegister)     (THIS_ DWORD) PURE;
   };

typedef ITTSCentralW FAR * PITTSCENTRALW;


#undef   INTERFACE
#define  INTERFACE   ITTSCentralA

DEFINE_GUID(IID_ITTSCentralA, 0x05EB6C6AL, 0xDBAB, 0x11CD, 0xB3, 0xCA, 0x00, 0xAA, 0x00, 0x47, 0xBA, 0x4F);

DECLARE_INTERFACE_ (ITTSCentralA, IUnknown) {

   // IUnknown members
   STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // ITTSCentralA members
   STDMETHOD (Inject)         (THIS_ PCSTR) PURE;
   STDMETHOD (ModeGet)        (THIS_ PTTSMODEINFOA) PURE;
   STDMETHOD (Phoneme)        (THIS_ VOICECHARSET, DWORD, SDATA, PSDATA) PURE;
   STDMETHOD (PosnGet)        (THIS_ PQWORD) PURE;
   STDMETHOD (TextData)       (THIS_ VOICECHARSET, DWORD, SDATA, PVOID, IID) PURE;
   STDMETHOD (ToFileTime)     (THIS_ PQWORD, FILETIME *) PURE;
   STDMETHOD (AudioPause)     (THIS) PURE;
   STDMETHOD (AudioResume)    (THIS) PURE;
   STDMETHOD (AudioReset)     (THIS) PURE;
   STDMETHOD (Register)       (THIS_ PVOID, IID, DWORD*) PURE;
   STDMETHOD (UnRegister)     (THIS_ DWORD) PURE;
   };

typedef ITTSCentralA FAR * PITTSCENTRALA;


#ifdef _S_UNICODE
 #define ITTSCentral             ITTSCentralW
 #define IID_ITTSCentral         IID_ITTSCentralW
 #define PITTSCENTRAL            PITTSCENTRALW

#else
 #define ITTSCentral             ITTSCentralA
 #define IID_ITTSCentral         IID_ITTSCentralA
 #define PITTSCENTRAL            PITTSCENTRALA

#endif   // _S_UNICODE



/*
 * ITTSDialogsW
 */

#undef   INTERFACE
#define  INTERFACE   ITTSDialogsW

DEFINE_GUID(IID_ITTSDialogsW, 0x47F59D00L, 0x4A47, 0x101B, 0x93, 0x1A, 0x00, 0xAA, 0x00, 0x47, 0xBA, 0x4F);

DECLARE_INTERFACE_ (ITTSDialogsW, IUnknown) {

   // IUnknown members
   STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // ITTSDialogsW members
   STDMETHOD (AboutDlg)       (THIS_ HWND, PCWSTR) PURE;
   STDMETHOD (LexiconDlg)     (THIS_ HWND, PCWSTR) PURE;
   STDMETHOD (GeneralDlg)     (THIS_ HWND, PCWSTR) PURE;
   STDMETHOD (TranslateDlg)   (THIS_ HWND, PCWSTR) PURE;
   };

typedef ITTSDialogsW FAR * PITTSDIALOGSW;


#undef   INTERFACE
#define  INTERFACE   ITTSDialogsA

DEFINE_GUID(IID_ITTSDialogsA, 0x05EB6C6BL, 0xDBAB, 0x11CD, 0xB3, 0xCA, 0x00, 0xAA, 0x00, 0x47, 0xBA, 0x4F);

DECLARE_INTERFACE_ (ITTSDialogsA, IUnknown) {

   // IUnknown members
   STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // ITTSDialogsA members
   STDMETHOD (AboutDlg)       (THIS_ HWND, PCSTR) PURE;
   STDMETHOD (LexiconDlg)     (THIS_ HWND, PCSTR) PURE;
   STDMETHOD (GeneralDlg)     (THIS_ HWND, PCSTR) PURE;
   STDMETHOD (TranslateDlg)   (THIS_ HWND, PCSTR) PURE;
   };

typedef ITTSDialogsA FAR * PITTSDIALOGSA;


#ifdef _S_UNICODE
 #define ITTSDialogs          ITTSDialogsW
 #define IID_ITTSDialogs      IID_ITTSDialogsW
 #define PITTSDIALOGS         PITTSDIALOGSW

#else
 #define ITTSDialogs          ITTSDialogsA
 #define IID_ITTSDialogs      IID_ITTSDialogsA
 #define PITTSDIALOGS         PITTSDIALOGSA

#endif



/*
 * ITTSEnum
 */

#undef   INTERFACE
#define  INTERFACE   ITTSEnumW

DEFINE_GUID(IID_ITTSEnumW, 0x6B837B20L, 0x4A47, 0x101B, 0x93, 0x1A, 0x00, 0xAA, 0x00, 0x47, 0xBA, 0x4F);

DECLARE_INTERFACE_ (ITTSEnumW, IUnknown) {

   // IUnknown members
   STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // ITTSEnumW members
   STDMETHOD (Next)           (THIS_ ULONG, PTTSMODEINFOW, ULONG *) PURE;
   STDMETHOD (Skip)           (THIS_ ULONG) PURE;
   STDMETHOD (Reset)          (THIS) PURE;
   STDMETHOD (Clone)          (THIS_ ITTSEnumW * FAR *) PURE;
   STDMETHOD (Select)         (THIS_ GUID, PITTSCENTRALW *, LPUNKNOWN) PURE;
   };

typedef ITTSEnumW FAR * PITTSENUMW;


#undef   INTERFACE
#define  INTERFACE   ITTSEnumA

DEFINE_GUID(IID_ITTSEnumA, 0x05EB6C6DL, 0xDBAB, 0x11CD, 0xB3, 0xCA, 0x00, 0xAA, 0x00, 0x47, 0xBA, 0x4F);

DECLARE_INTERFACE_ (ITTSEnumA, IUnknown) {

   // IUnknown members
   STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // ITTSEnumA members
   STDMETHOD (Next)           (THIS_ ULONG, PTTSMODEINFOA, ULONG *) PURE;
   STDMETHOD (Skip)           (THIS_ ULONG) PURE;
   STDMETHOD (Reset)          (THIS) PURE;
   STDMETHOD (Clone)          (THIS_ ITTSEnumA * FAR *) PURE;
   STDMETHOD (Select)         (THIS_ GUID, PITTSCENTRALA *, LPUNKNOWN) PURE;
   };

typedef ITTSEnumA FAR * PITTSENUMA;


#ifdef _S_UNICODE
 #define ITTSEnum             ITTSEnumW
 #define IID_ITTSEnum         IID_ITTSEnumW
 #define PITTSENUM            PITTSENUMW

#else
 #define ITTSEnum             ITTSEnumA
 #define IID_ITTSEnum         IID_ITTSEnumA
 #define PITTSENUM            PITTSENUMA

#endif



/*
 * ITTSFind
 */

#undef   INTERFACE
#define  INTERFACE   ITTSFindW

DEFINE_GUID(IID_ITTSFindW, 0x7AA42960L, 0x4A47, 0x101B, 0x93, 0x1A, 0x00, 0xAA, 0x00, 0x47, 0xBA, 0x4F);

DECLARE_INTERFACE_ (ITTSFindW, IUnknown) {

   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // ITTSFindW members
   STDMETHOD (Find)           (THIS_ PTTSMODEINFOW, PTTSMODEINFORANK, PTTSMODEINFOW) PURE;
   STDMETHOD (Select)         (THIS_ GUID, PITTSCENTRALW *, LPUNKNOWN) PURE;
   };

typedef ITTSFindW FAR * PITTSFINDW;


#undef   INTERFACE
#define  INTERFACE   ITTSFindA

DEFINE_GUID(IID_ITTSFindA, 0x05EB6C6EL, 0xDBAB, 0x11CD, 0xB3, 0xCA, 0x00, 0xAA, 0x00, 0x47, 0xBA, 0x4F);

DECLARE_INTERFACE_ (ITTSFindA, IUnknown) {

   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // ITTSFindA members
   STDMETHOD (Find)           (THIS_ PTTSMODEINFOA, PTTSMODEINFORANK, PTTSMODEINFOA) PURE;
   STDMETHOD (Select)         (THIS_ GUID, PITTSCENTRALA *, LPUNKNOWN) PURE;
   };

typedef ITTSFindA FAR * PITTSFINDA;


#ifdef _S_UNICODE
 #define ITTSFind             ITTSFindW
 #define IID_ITTSFind         IID_ITTSFindW
 #define PITTSFIND            PITTSFINDW

#else
 #define ITTSFind             ITTSFindA
 #define IID_ITTSFind         IID_ITTSFindA
 #define PITTSFIND            PITTSFINDA

#endif



/*
 * ITTSNotifySink
 */

#undef   INTERFACE
#define  INTERFACE   ITTSNotifySinkW

DEFINE_GUID(IID_ITTSNotifySinkW, 0xC0FA8F40L, 0x4A46, 0x101B, 0x93, 0x1A, 0x00, 0xAA, 0x00, 0x47, 0xBA, 0x4F);

DECLARE_INTERFACE_ (ITTSNotifySinkW, IUnknown) {

// IUnknown members

   STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

// ITTSNotifySinkW members

   STDMETHOD (AttribChanged)  (THIS_ DWORD) PURE;
   STDMETHOD (AudioStart)     (THIS_ QWORD) PURE;
   STDMETHOD (AudioStop)      (THIS_ QWORD) PURE;
   STDMETHOD (Visual)         (THIS_ QWORD, WCHAR, WCHAR, DWORD, PTTSMOUTH) PURE;
   };

typedef ITTSNotifySinkW FAR * PITTSNOTIFYSINKW;


#undef   INTERFACE
#define  INTERFACE   ITTSNotifySinkA

DEFINE_GUID(IID_ITTSNotifySinkA, 0x05EB6C6FL, 0xDBAB, 0x11CD, 0xB3, 0xCA, 0x00, 0xAA, 0x00, 0x47, 0xBA, 0x4F);

DECLARE_INTERFACE_ (ITTSNotifySinkA, IUnknown) {

   // IUnknown members
   STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // ITTSNotifySinkA members
   STDMETHOD (AttribChanged)  (THIS_ DWORD) PURE;
   STDMETHOD (AudioStart)     (THIS_ QWORD) PURE;
   STDMETHOD (AudioStop)      (THIS_ QWORD) PURE;
   STDMETHOD (Visual)         (THIS_ QWORD, CHAR, CHAR, DWORD, PTTSMOUTH) PURE;
   };

typedef ITTSNotifySinkA FAR * PITTSNOTIFYSINKA;


#ifdef _S_UNICODE
 #define ITTSNotifySink       ITTSNotifySinkW
 #define IID_ITTSNotifySink   IID_ITTSNotifySinkW
 #define PITTSNOTIFYSINK      PITTSNOTIFYSINKW

#else
 #define ITTSNotifySink       ITTSNotifySinkA
 #define IID_ITTSNotifySink   IID_ITTSNotifySinkA
 #define PITTSNOTIFYSINK      PITTSNOTIFYSINKA

#endif



/************************************************************************
High-Level speech recognition API
*/

/************************************************************************
defines */


// VCMDNAME member lengths
#define VCMD_APPLEN             ((DWORD)32)
#define VCMD_STATELEN           VCMD_APPLEN
#define VCMD_MICLEN             VCMD_APPLEN
#define VCMD_SPEAKERLEN         VCMD_APPLEN

// dwFlags parameter of IVoiceCmd::MenuCreate
#define  VCMDMC_CREATE_TEMP     0x00000001
#define  VCMDMC_CREATE_NEW      0x00000002
#define  VCMDMC_CREATE_ALWAYS   0x00000004
#define  VCMDMC_OPEN_ALWAYS     0x00000008
#define  VCMDMC_OPEN_EXISTING   0x00000010

// dwFlags parameter of IVoiceCmd::Register
// the last four new flags are introduced to allow only notifications of CommandRecognize only
// or including CommandOther and AttribChange. This is backward compatible
#define  VCMDRF_NOMESSAGES      0
#define  VCMDRF_ALLBUTVUMETER   0x00000001
#define  VCMDRF_VUMETER         0x00000002
#define  VCMDRF_ALLMESSAGES     (VCMDRF_ALLBUTVUMETER | VCMDRF_VUMETER)

#define  VCMDRF_CMDRECOG        0x00000011
#define  VCMDRF_CMDOTHER        0x00000021
#define  VCMDRF_ATTRIBCHANGE    0x00000041
#define  VCMDRF_CMDSTART        0x00000081
#define  VCMDRF_ALLVCMDMSG      (VCMDRF_ALLMESSAGES|VCMDRF_CMDRECOG|VCMDRF_CMDOTHER|VCMDRF_ATTRIBCHANGE|VCMDRF_CMDSTART)

// dwFlags parameter of IVoiceCmd::MenuEnum
#define  VCMDEF_DATABASE        0x00000000
#define  VCMDEF_ACTIVE          0x00000001
#define  VCMDEF_SELECTED        0x00000002
#define  VCMDEF_PERMANENT       0x00000004
#define  VCMDEF_TEMPORARY       0x00000008

// dwFlags parameter of IVCmdMenu::Activate
#define  VWGFLAG_ASLEEP         0x00000001
#define  VWGFLAG_BALLOON        0x00000010

// wPriority parameter of IVCmdMenu::Activate
#define  VCMDACT_NORMAL         (0x8000)
#define  VCMDACT_LOW            (0x4000)
#define  VCMDACT_HIGH           (0xC000)

// dwFlags of the VCMDCOMMAND structure
#define  VCMDCMD_VERIFY         0x00000001
#define  VCMDCMD_DISABLED_TEMP  0x00000002
#define  VCMDCMD_DISABLED_PERM  0x00000004

// parameter to any function that processes individual commands
#define  VCMD_BY_POSITION       0x00000001
#define  VCMD_BY_IDENTIFIER     0x00000002


// values for dwAttributes field of IVCmdNotifySink::AttribChanged
#define  IVCNSAC_AUTOGAINENABLE 0x00000001
#define  IVCNSAC_ENABLED        0x00000002
#define  IVCNSAC_AWAKE          0x00000004
#define  IVCNSAC_DEVICE         0x00000008
#define  IVCNSAC_MICROPHONE     0x00000010
#define  IVCNSAC_SPEAKER        0x00000020
#define  IVCNSAC_SRMODE         0x00000040
#define  IVCNSAC_THRESHOLD      0x00000080
#define  IVCNSAC_ORIGINAPP      0x00010000

// values for dwAttributes field of IVTxtNotifySink::AttribChanged
#define  IVTNSAC_DEVICE         0x00000001
#define  IVTNSAC_ENABLED        0x00000002
#define  IVTNSAC_SPEED          0x00000004
#define  IVTNSAC_VOLUME         0x00000008
#define  IVTNSAC_TTSMODE        0x00000010

//	Apollo specific attributes
#define  IVANSAC_APOLLOCUSTOM   0xC0000000
#define  IVANSAC_NOISEFLOOR     0x00080000
#define  IVANSAC_AWAKETIMEROFF  0x00100000
#define  IVANSAC_AWAKETIMERON   0x00200000
#define  IVANSAC_AWAKETIMERCLR  0x00800000
#define  IVANSAC_AWAKETIME      0x01000000
#define  IVANSAC_TTSPITCH       0x02000000
#define  IVANSAC_VHELPSTART     0x04000000
#define  IVANSAC_VHELPSTOP      0x08000000
#define  IVANSAC_ASRPAUSE       0x10000000
#define  IVANSAC_ASRRESUME      0x20000000

 
/************************************************************************
typedefs */

// voice command structure - passed to command menu functions (IVCmdMenu)
/**
 * This structure provides information about a command in a voice menu.
 *
 * Because the items indicated by offsets into abData are DWORD-aligned, the offsets specified by
 * dwCommand, dwDescription, dwCategory, dwAction, and dwActionSize should be multiples of 4.
 */
typedef struct {
    /**
     * Specifies the size, in bytes, of the VCMDCOMMAND structure, including the amount allocated for
     * abData. The contents of abData must be DWORD-aligned, so round dwSize up to the nearest whole
     * DWORD.
     */
    DWORD   dwSize;         // size of struct including amount of abAction
    /**
     * Specifies the information about the command. It is a combination of the following flags:
     *
     * - VCMDCMD_DISABLED_PERM: The command was disabled by using the IVCmdMenu::EnableItem method so
     * that the voice commands cannot be recognized. The command is not compiled into the voice menu.
     *
     * - VCMDCMD_DISABLED_TEMP: The command was disabled by using the IVCmdMenu::SetItem method. The
     * command is still compiled into the voice menu, so it can be re-enabled without recompilation of
     * the menu.
     *
     * - VCMDCMD_VERIFY: This flag is not supported in Microsoft Windows CE for the Auto PC version 1.0.
     *
     * - VCMDCMD_CANTRENAME: This flag is not supported in Windows CE for the Auto PC version 1.0.
     */
    DWORD   dwFlags;
    /**
     * Specifies the command identifier. This member can be used to identify a command to modify, or it
     * can be used for notifications.
     */
    DWORD   dwID;           // Command ID
    /**
     * Specifies the offset from the beginning of this structure to first character of the voice command
     * string, which is Unicode.
     *
     * Within the command string, the following characters have special meaning:
     *
     * - < >: Indicates the name of a list of words or phrases that can be spoken at this point in the
     * command. For example, the command string "Send mail to <name>" contains a list called "name." To
     * add phrases to the list, use the IVCmdMenu::ListSet method.
     *
     * - { }: Reserved for future use.
     *
     * - [ ]: Reserved for future use.
     */
    DWORD   dwCommand;      // DWORD aligned offset of command string
    /**
     * Specifies the offset from the beginning of the structure to first character of a string that
     * describes the action performed by the command.
     */
    DWORD   dwDescription;  // DWORD aligned offset of description string
    /**
     * Specifies the offset from the beginning of the structure to the first character of a string that
     * indicates the category to which the command belongs.
     *
     * Commands in a voice menu should be organized in different categories to help the user browse
     * through lists of commands more easily. This is similar in concept to Windows menus, which
     * organize commands under menu names such as File, Edit, View, and so on. For best results, you
     * should use 20 or fewer categories.
     */
    DWORD   dwCategory;     // DWORD aligned offset of category string
    /**
     * Specifies the offset from the beginning of the structure to the first character of the command
     * text, which is the string that is displayed to the user when he or she requests a list of
     * available voice commands. If this member is NULL, an application uses the text pointed to by
     * dwCommand, which is the voice command string used in the application's user interface.
     *
     * Most applications written for European languages set this member to NULL, because the language
     * uses only one character set. Applications written for languages that have both a phonemic and
     * symbolic character set, such as Japanese, store the phonemic representation of the command in
     * dwCommand and the symbolic representation-which is preferred by the user-in dwCommandText.
     */
    DWORD   dwCommandText;  // DWORD aligned offset of command text string
    /**
     * Specifies the offset from the beginning of the structure to the first byte of a block of data
     * that is sent to the application when the command is spoken.
     *
     * Data passed with a command is not interpreted by voice commands; it is up to the application to
     * determine whether the data is valid and to act upon it. Always check the validity of the data,
     * because it is susceptible to being changed-accidentally or intentionally-by other applications,
     * just as other applications can change an .ini file or registry file.
     */
    DWORD   dwAction;       // DWORD aligned offset of action data
    /**
     * Specifies the number of bytes required to store the block of data indicated by dwAction.
     */
    DWORD   dwActionSize;   // size of the action data (could be string or binary)
    /**
     * Array of BYTE types that contains the command string, its description, its category, and any
     * additional data to pass to the application along with the command. Because all of the items in
     * abData are DWORD-aligned, the size of abData should be a multiple of 4. All strings should be
     * null-terminated.
     */
    BYTE    abData[1];      // command, description, category, and action data
                            // (action data is NOT interpreted by voice command)
} VCMDCOMMAND, * PVCMDCOMMAND;



// site information structure - possible parameter to IVoiceCmd::Register
/**
 * This structure provides information about the audio device, speech-recognition mode, and other
 * attributes of a voice command site.
 *
 * An application can pass a pointer to a VCSITEINFO structure with the IVoiceCmd::Register method
 * to set the audio device, speech-recognition mode, and other attributes of a voice-command site,
 * even if the site is already open.
 */
typedef struct {
    /**
     * Specifies a value from 0 to 100 that indicates the state of the automatic gain for the incoming
     * audio stream to be used by the site.
     */
    DWORD   dwAutoGainEnable;
    /**
     * Specifies the state of speech recognition. TRUE indicates that the site is awake for purposes of
     * speech-recognition; FALSE indicates that the site is asleep.
     */
    DWORD   dwAwakeState;
    /**
     * Specifies a value from 0 to 100 that indicates the recognition threshold for the
     * speech-recognition engine to be used by the site.
     */
    DWORD   dwThreshold;
    /**
     * Specifies the device identifier of the wave-in audio device to be used by the site. The device
     * identifier can be obtained by calling the waveInGetNumDevs and waveInGetDevCaps multimedia
     * functions.
     */
    DWORD   dwDevice;
    /**
     * Specifies whether or not speech recognition is enabled. TRUE indicates that speech recognition is
     * enabled for the site; FALSE indicates that speech recognition is disabled.
     */
    DWORD   dwEnable;
    /**
     * Null-terminated string that contains the name of the current microphone for the audio source to
     * be used by the site.
     */
    WCHAR   szMicrophone[VCMD_MICLEN];
    /**
     * Null-terminated string that contains the name of the current speaker for the site.
     */
    WCHAR   szSpeaker[VCMD_SPEAKERLEN];
    /**
     * Globally unique identifier (GUID) for the speech-recognition mode to be used by the site. The
     * GUID for a speech-recognition mode can be obtained by using a speech-recognition enumerator.
     */
    GUID    gModeID;
} VCSITEINFOW, *PVCSITEINFOW;

/**
 * This structure provides information about the audio device, speech-recognition mode, and other
 * attributes of a voice command site.
 *
 * An application can pass a pointer to a VCSITEINFO structure with the IVoiceCmd::Register method
 * to set the audio device, speech-recognition mode, and other attributes of a voice-command site,
 * even if the site is already open.
 */
typedef struct {
    /**
     * Specifies a value from 0 to 100 that indicates the state of the automatic gain for the incoming
     * audio stream to be used by the site.
     */
    DWORD   dwAutoGainEnable;
    /**
     * Specifies the state of speech recognition. TRUE indicates that the site is awake for purposes of
     * speech-recognition; FALSE indicates that the site is asleep.
     */
    DWORD   dwAwakeState;
    /**
     * Specifies a value from 0 to 100 that indicates the recognition threshold for the
     * speech-recognition engine to be used by the site.
     */
    DWORD   dwThreshold;
    /**
     * Specifies the device identifier of the wave-in audio device to be used by the site. The device
     * identifier can be obtained by calling the waveInGetNumDevs and waveInGetDevCaps multimedia
     * functions.
     */
    DWORD   dwDevice;
    /**
     * Specifies whether or not speech recognition is enabled. TRUE indicates that speech recognition is
     * enabled for the site; FALSE indicates that speech recognition is disabled.
     */
    DWORD   dwEnable;
    /**
     * Null-terminated string that contains the name of the current microphone for the audio source to
     * be used by the site.
     */
    CHAR    szMicrophone[VCMD_MICLEN];
    /**
     * Null-terminated string that contains the name of the current speaker for the site.
     */
    CHAR    szSpeaker[VCMD_SPEAKERLEN];
    /**
     * Globally unique identifier (GUID) for the speech-recognition mode to be used by the site. The
     * GUID for a speech-recognition mode can be obtained by using a speech-recognition enumerator.
     */
    GUID    gModeID;
} VCSITEINFOA, *PVCSITEINFOA;



// menu name structure
/**
 * This structure contains strings that uniquely identify the application and state to which a voice
 * menu belongs.
 */
typedef struct {
    /**
     * Null-terminated string that contains the name of the application-for example, "AM/FM Radio." The
     * application name must be unique among all applications registered to use voice commands on the
     * user's computer.
     */
    WCHAR   szApplication[VCMD_APPLEN]; // unique application name
    /**
     * Null-terminated string that contains the unique name of the application state in which the voice
     * command set is valid. An application state usually corresponds to an active window or dialog box
     * .
     */
    WCHAR   szState[VCMD_STATELEN];     // unique application state
} VCMDNAMEW, *PVCMDNAMEW;

/**
 * This structure contains strings that uniquely identify the application and state to which a voice
 * menu belongs.
 */
typedef struct {
    /**
     * Null-terminated string that contains the name of the application-for example, "AM/FM Radio." The
     * application name must be unique among all applications registered to use voice commands on the
     * user's computer.
     */
    CHAR    szApplication[VCMD_APPLEN]; // unique application name
    /**
     * Null-terminated string that contains the unique name of the application state in which the voice
     * command set is valid. An application state usually corresponds to an active window or dialog box
     * .
     */
    CHAR    szState[VCMD_STATELEN];     // unique application state
} VCMDNAMEA, *PVCMDNAMEA;



#ifdef  _S_UNICODE
 #define VCSITEINFO  VCSITEINFOW
 #define PVCSITEINFO PVCSITEINFOW
 #define VCMDNAME    VCMDNAMEW
 #define PVCMDNAME   PVCMDNAMEW
#else
 #define VCSITEINFO  VCSITEINFOA
 #define PVCSITEINFO PVCSITEINFOA
 #define VCMDNAME    VCMDNAMEA
 #define PVCMDNAME   PVCMDNAMEA
#endif  // _S_UNICODE

/************************************************************************
interfaces */

/*
 *  IVCmdNotifySink
 */
#undef   INTERFACE
#define  INTERFACE   IVCmdNotifySinkW

DEFINE_GUID(IID_IVCmdNotifySinkW, 0xCCFD7A60L, 0x604D, 0x101B, 0x99, 0x26, 0x00, 0xAA, 0x00, 0x3C, 0xFC, 0x2C);

/**
 * This interface must be implemented by an application in order to receive notifications from the
 * voice command object. In addition to the recognized command, an application can also be notified
 * of events such as beginning and ending of an utterance, menu activation, and the presence of
 * interference.
 */
DECLARE_INTERFACE_ (IVCmdNotifySinkW, IUnknown) {

   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // IVCmdNotifySink members

   /**
    * This method is sent by the engine when a spoken phrase is recognized as being from the
    * application's command set.
    *
    * @param dwID [in] Specifies the identifier of the command that was recognized. The command
    *   identifier is stored in the dwID member of the VCMDCOMMAND structure that defines the command.
    * @param pvCmdName [in] Void pointer to a VCMDNAME structure that contains the voice menu that has
    *   the recognized command.
    * @param dwFlags [in] Specifies a bitmask of flags. Set to VCMDCMD_VERIFY if the application should
    *   request verification from the user, or to NULL if verification is not required. To request
    *   verification, the application should display a dialog box. An application would typically require
    *   verification for a destructive or irreversible command such as "Format disk."
    * @param dwActionSize [in] Specifies the size of the data in pAction.
    * @param pAction [in] Pointer to a string that contains action data to accompany the recognized
    *   command. The action data is obtained from the VCMDCOMMAND structure for the command.
    * @param dwNumLists [in] Specifies, in bytes, the size of the list data for the command. If a
    *   command does not contain any list fields, this parameter is zero.
    * @param pszListValues [in] Pointer to a list of one or more null-terminated strings that
    *   correspond to the phrase from each list in the order that they occur in the command. For example,
    *   if the command is "Set the time to number AM or PM," this parameter points to "Ten\0PM." The last
    *   "\0" is implicit in C notation.
    * @param pszCommand [in] Pointer to the null-terminated string for the command that was recognized.
    *
    * @return The return value is ignored.
    *
    * Along with the notification, the application receives the text of the phrase and the action data
    * that was supplied by the application when it originally defined the command.
    *
    * Do not use the contents of pszCommand to identify the recognized command. Instead, use the data
    * in pAction or the identifier in dwID to determine which command was recognized.
    *
    * The notification is sent to all applications that are registered on the voice command site,
    * regardless of the what the dwFlags parameter of the IVoiceCmd::Register method was set to when
    * the application registered to use voice commands.
    *
    * If two or more global voice menus, or two or more window-specific voice menus, contain the same
    * phrase and the engine recognizes that phrase, the engine calls CommandRecognize for one menu and
    * IVCmdNotifySink::CommandOther for the other. The engine determines which notification to call for
    * each menu; an application cannot determine which notification is called.
    */
   STDMETHOD (CommandRecognize) (THIS_ DWORD, PVCMDNAMEW, DWORD, DWORD, PVOID, 
                                 DWORD, PWSTR, PWSTR) PURE;
   /**
    * This method notifies the application that the engine did not recognize a spoken phrase, or
    * recognized it as being from another application's command set.
    *
    * @param pName [in] Pointer to a VCMDNAME structure that contains the name of the voice menu that
    *   has the recognized command. If this parameter contains NULL, the command was not recognized.
    * @param pszCommand [in] Pointer to the null-terminated string for the command. If this parameter
    *   contains NULL, the command was not recognized.
    *
    * @return The return value is ignored.
    *
    * Along with the notification method, the application receives the address of the phrase.
    *
    * An application can use this notification to monitor utterances and inform the user what was
    * heard. An application should not rely on this notification for information about the recognition
    * of its own commands. Most applications ignore this notification.
    *
    * The command string contains the words actually spoken by the user. If the command contains a list
    * name, the command string may not match the words of the command. For example, the string pointed
    * to by pszCommand might be "Send mail to Fred," whereas the command string is "Send mail to name."
    *
    * The notification is sent only to applications that, when registered to use voice commands on the
    * site, did one of the following:
    *
    * Set the dwFlags parameter of the IVoiceCmd::Register method to the VCMDRF_ALLBUTVUMETER value.
    *
    * Set the VCMDRF_CMDOTHER bit.
    *
    * If two or more voice menus contain the same phrase and this phrase is recognized, it is
    * indeterminate which of the menus causes the engine to call the IVCmdNotifySink::CommandRecognize
    * notification and which causes it to call CommandOther. This happens only if the menus are all
    * global or all window-specific.
    */
   STDMETHOD (CommandOther)     (THIS_ PVCMDNAMEW, PWSTR) PURE;
   /**
    * This method is sent by the engine when a spoken phrase is detected.
    *
    * @return The return value is ignored.
    *
    * The notification is sent only to applications that, when registered to use voice commands on the
    * site, did one of the following:
    *
    * Set the dwFlags parameter of the IVoiceCmd::Register method to the VCMDRF_ALLBUTVUMETER value.
    *
    * Set the VCMDRF_CMDSTART bit.
    */
   STDMETHOD (CommandStart)     (THIS) PURE;
   STDMETHOD (MenuActivate)     (THIS_ PVCMDNAMEW, BOOL) PURE;
   STDMETHOD (UtteranceBegin)   (THIS) PURE;
   STDMETHOD (UtteranceEnd)     (THIS) PURE;
   STDMETHOD (VUMeter)          (THIS_ WORD) PURE;
   /**
    * This method notifies applications on a voice command site that a site attribute has changed.
    *
    * @param dwAttribute [in] Specifies the site attribute that was changed. It is one of the following
    *   flags: - IVCNSAC_AWAKE: Specifies the awake state. - IVCNSAC_AUTOGAINENABLE: Specifies the
    *   automatic gain. - IVCNSAC_DEVICE: Specifies a wave-in audio device. - IVCNSAC_ENABLED: Specifies
    *   the enabled state. - IVCNSAC_MICROPHONE: Current microphone. - IVCNSAC_ORIGINAPP: The application
    *   receiving this notification originated the attribute change. - IVCNSAC_SPEAKER: Specifies the
    *   name of the current speaker. - IVCNSAC_SRMODE: Specifies speech-recognition mode. -
    *   IVCNSAC_THRESHOLD: Specifies the confidence threshold.
    *
    * @return The return value is ignored.
    *
    * The notification is sent only to applications that, when registered to use voice commands on the
    * site, did one of the following:
    *
    * Set the dwFlags parameter of the IVoiceCmd::Register method to the VCMDRF_ALLBUTVUMETER value.
    *
    * Set the VCMDRF_ATTRIBCHANGE bit.
    *
    * The dwAttribute parameter includes the IVCNSAC_ORIGINAPP value only if the application sets an
    * attribute by calling the IVCmdAttributes interface's EnabledSet, AwakeStateSet, DeviceSet, or
    * SRModeSet method.
    */
   STDMETHOD (AttribChanged)    (THIS_ DWORD) PURE;
   /**
    * This method notifies the application that the engine cannot recognize speech properly for a known
    * reason.
    *
    * @param dwType [in] Specifies the type of interference. It is one of the following flags: -
    *   SRMSGINT_AUDIODATA_STARTED: The engine has resumed receiving audio data from the audio source. -
    *   SRMSGINT_AUDIODATA_STOPPED: The engine has stopped receiving audio data from the audio source. -
    *   SRMSGINT_NOISE: The background noise is too high. - SRMSGINT_NOSIGNAL: The engine cannot detect a
    *   signal, possibly because the microphone is off or unplugged. - SRMSGINT_TOOLOUD: The speaker is
    *   too loud; recognition results may be degraded. - SRMSGINT_TOOQUIET: The speaker is too quiet;
    *   recognition results may be degraded.
    *
    * @return The return value is ignored.
    *
    * The notification is sent only to applications that set the dwFlags parameter of the
    * IVoiceCmd::Register method to the VCMDRF_ALLBUTVUMETER value when the application registered to
    * use voice commands on the site.
    */
   STDMETHOD (Interference)     (THIS_ DWORD) PURE;
};

typedef IVCmdNotifySinkW FAR * PIVCMDNOTIFYSINKW;


#undef   INTERFACE
#define  INTERFACE   IVCmdNotifySinkA

// {80B25CC0-5540-11b9-C000-5611722E1D15}
DEFINE_GUID(IID_IVCmdNotifySinkA, 0x80b25cc0, 0x5540, 0x11b9, 0xc0, 0x0, 0x56, 0x11, 0x72, 0x2e, 0x1d, 0x15);

/**
 * This interface must be implemented by an application in order to receive notifications from the
 * voice command object. In addition to the recognized command, an application can also be notified
 * of events such as beginning and ending of an utterance, menu activation, and the presence of
 * interference.
 */
DECLARE_INTERFACE_ (IVCmdNotifySinkA, IUnknown) {

   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // IVCmdNotifySinkA members

   /**
    * This method is sent by the engine when a spoken phrase is recognized as being from the
    * application's command set.
    *
    * @param dwID [in] Specifies the identifier of the command that was recognized. The command
    *   identifier is stored in the dwID member of the VCMDCOMMAND structure that defines the command.
    * @param pvCmdName [in] Void pointer to a VCMDNAME structure that contains the voice menu that has
    *   the recognized command.
    * @param dwFlags [in] Specifies a bitmask of flags. Set to VCMDCMD_VERIFY if the application should
    *   request verification from the user, or to NULL if verification is not required. To request
    *   verification, the application should display a dialog box. An application would typically require
    *   verification for a destructive or irreversible command such as "Format disk."
    * @param dwActionSize [in] Specifies the size of the data in pAction.
    * @param pAction [in] Pointer to a string that contains action data to accompany the recognized
    *   command. The action data is obtained from the VCMDCOMMAND structure for the command.
    * @param dwNumLists [in] Specifies, in bytes, the size of the list data for the command. If a
    *   command does not contain any list fields, this parameter is zero.
    * @param pszListValues [in] Pointer to a list of one or more null-terminated strings that
    *   correspond to the phrase from each list in the order that they occur in the command. For example,
    *   if the command is "Set the time to number AM or PM," this parameter points to "Ten\0PM." The last
    *   "\0" is implicit in C notation.
    * @param pszCommand [in] Pointer to the null-terminated string for the command that was recognized.
    *
    * @return The return value is ignored.
    *
    * Along with the notification, the application receives the text of the phrase and the action data
    * that was supplied by the application when it originally defined the command.
    *
    * Do not use the contents of pszCommand to identify the recognized command. Instead, use the data
    * in pAction or the identifier in dwID to determine which command was recognized.
    *
    * The notification is sent to all applications that are registered on the voice command site,
    * regardless of the what the dwFlags parameter of the IVoiceCmd::Register method was set to when
    * the application registered to use voice commands.
    *
    * If two or more global voice menus, or two or more window-specific voice menus, contain the same
    * phrase and the engine recognizes that phrase, the engine calls CommandRecognize for one menu and
    * IVCmdNotifySink::CommandOther for the other. The engine determines which notification to call for
    * each menu; an application cannot determine which notification is called.
    */
   STDMETHOD (CommandRecognize) (THIS_ DWORD, PVCMDNAMEA, DWORD, DWORD, PVOID, 
                                 DWORD, PSTR, PSTR) PURE;
   /**
    * This method notifies the application that the engine did not recognize a spoken phrase, or
    * recognized it as being from another application's command set.
    *
    * @param pName [in] Pointer to a VCMDNAME structure that contains the name of the voice menu that
    *   has the recognized command. If this parameter contains NULL, the command was not recognized.
    * @param pszCommand [in] Pointer to the null-terminated string for the command. If this parameter
    *   contains NULL, the command was not recognized.
    *
    * @return The return value is ignored.
    *
    * Along with the notification method, the application receives the address of the phrase.
    *
    * An application can use this notification to monitor utterances and inform the user what was
    * heard. An application should not rely on this notification for information about the recognition
    * of its own commands. Most applications ignore this notification.
    *
    * The command string contains the words actually spoken by the user. If the command contains a list
    * name, the command string may not match the words of the command. For example, the string pointed
    * to by pszCommand might be "Send mail to Fred," whereas the command string is "Send mail to name."
    *
    * The notification is sent only to applications that, when registered to use voice commands on the
    * site, did one of the following:
    *
    * Set the dwFlags parameter of the IVoiceCmd::Register method to the VCMDRF_ALLBUTVUMETER value.
    *
    * Set the VCMDRF_CMDOTHER bit.
    *
    * If two or more voice menus contain the same phrase and this phrase is recognized, it is
    * indeterminate which of the menus causes the engine to call the IVCmdNotifySink::CommandRecognize
    * notification and which causes it to call CommandOther. This happens only if the menus are all
    * global or all window-specific.
    */
   STDMETHOD (CommandOther)     (THIS_ PVCMDNAMEA, PSTR) PURE;
   /**
    * This method is sent by the engine when a spoken phrase is detected.
    *
    * @return The return value is ignored.
    *
    * The notification is sent only to applications that, when registered to use voice commands on the
    * site, did one of the following:
    *
    * Set the dwFlags parameter of the IVoiceCmd::Register method to the VCMDRF_ALLBUTVUMETER value.
    *
    * Set the VCMDRF_CMDSTART bit.
    */
   STDMETHOD (CommandStart)     (THIS) PURE;
   STDMETHOD (MenuActivate)     (THIS_ PVCMDNAMEA, BOOL) PURE;
   STDMETHOD (UtteranceBegin)   (THIS) PURE;
   STDMETHOD (UtteranceEnd)     (THIS) PURE;
   STDMETHOD (VUMeter)          (THIS_ WORD) PURE;
   /**
    * This method notifies applications on a voice command site that a site attribute has changed.
    *
    * @param dwAttribute [in] Specifies the site attribute that was changed. It is one of the following
    *   flags: - IVCNSAC_AWAKE: Specifies the awake state. - IVCNSAC_AUTOGAINENABLE: Specifies the
    *   automatic gain. - IVCNSAC_DEVICE: Specifies a wave-in audio device. - IVCNSAC_ENABLED: Specifies
    *   the enabled state. - IVCNSAC_MICROPHONE: Current microphone. - IVCNSAC_ORIGINAPP: The application
    *   receiving this notification originated the attribute change. - IVCNSAC_SPEAKER: Specifies the
    *   name of the current speaker. - IVCNSAC_SRMODE: Specifies speech-recognition mode. -
    *   IVCNSAC_THRESHOLD: Specifies the confidence threshold.
    *
    * @return The return value is ignored.
    *
    * The notification is sent only to applications that, when registered to use voice commands on the
    * site, did one of the following:
    *
    * Set the dwFlags parameter of the IVoiceCmd::Register method to the VCMDRF_ALLBUTVUMETER value.
    *
    * Set the VCMDRF_ATTRIBCHANGE bit.
    *
    * The dwAttribute parameter includes the IVCNSAC_ORIGINAPP value only if the application sets an
    * attribute by calling the IVCmdAttributes interface's EnabledSet, AwakeStateSet, DeviceSet, or
    * SRModeSet method.
    */
   STDMETHOD (AttribChanged)    (THIS_ DWORD) PURE;
   /**
    * This method notifies the application that the engine cannot recognize speech properly for a known
    * reason.
    *
    * @param dwType [in] Specifies the type of interference. It is one of the following flags: -
    *   SRMSGINT_AUDIODATA_STARTED: The engine has resumed receiving audio data from the audio source. -
    *   SRMSGINT_AUDIODATA_STOPPED: The engine has stopped receiving audio data from the audio source. -
    *   SRMSGINT_NOISE: The background noise is too high. - SRMSGINT_NOSIGNAL: The engine cannot detect a
    *   signal, possibly because the microphone is off or unplugged. - SRMSGINT_TOOLOUD: The speaker is
    *   too loud; recognition results may be degraded. - SRMSGINT_TOOQUIET: The speaker is too quiet;
    *   recognition results may be degraded.
    *
    * @return The return value is ignored.
    *
    * The notification is sent only to applications that set the dwFlags parameter of the
    * IVoiceCmd::Register method to the VCMDRF_ALLBUTVUMETER value when the application registered to
    * use voice commands on the site.
    */
   STDMETHOD (Interference)     (THIS_ DWORD) PURE;
};

typedef IVCmdNotifySinkA FAR * PIVCMDNOTIFYSINKA;


#ifdef _S_UNICODE
 /**
  * This interface must be implemented by an application in order to receive notifications from the
  * voice command object. In addition to the recognized command, an application can also be notified
  * of events such as beginning and ending of an utterance, menu activation, and the presence of
  * interference.
  */
 #define IVCmdNotifySink        IVCmdNotifySinkW
 #define IID_IVCmdNotifySink    IID_IVCmdNotifySinkW
 #define PIVCMDNOTIFYSINK       PIVCMDNOTIFYSINKW

#else
 /**
  * This interface must be implemented by an application in order to receive notifications from the
  * voice command object. In addition to the recognized command, an application can also be notified
  * of events such as beginning and ending of an utterance, menu activation, and the presence of
  * interference.
  */
 #define IVCmdNotifySink        IVCmdNotifySinkA
 #define IID_IVCmdNotifySink    IID_IVCmdNotifySinkA
 #define PIVCMDNOTIFYSINK       PIVCMDNOTIFYSINKA

#endif // _S_UNICODE



/*
 *  IVCmdEnum
 */
#undef   INTERFACE
#define  INTERFACE   IVCmdEnumW

DEFINE_GUID(IID_IVCmdEnumW, 0xD3CC0820L, 0x604D, 0x101B, 0x99, 0x26, 0x00, 0xAA, 0x00, 0x3C, 0xFC, 0x2C);

/**
 * This interface is a standard OLE enumeration interface. Its methods are used by applications to
 * enumerate the menus stored in the voice command database
 *
 * This interface is supported by all voice command objects.
 */
DECLARE_INTERFACE_ (IVCmdEnumW, IUnknown) {
   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // IVCmdEnum members
   /**
    * This method retrieves the specified number of items in the enumeration sequence.
    *
    * @param celt [in] Number of elements to retrieve. If the number of elements requested is more than
    *   remains in the sequence, only the remaining elements are retrieved.
    * @param rgelt [out] Array that receives the elements. If an error value is returned, no entries in
    *   the array are valid.
    * @param pceltFetched [out] Pointer to a variable that receives the number of array elements
    *   actually copied to the array. This parameter cannot be NULL if celt is greater than one. If this
    *   parameter is NULL, celt must be one.
    *
    * @return - NOERROR: The method successfully retrieved the specified number of items in the
    *   enumeration sequence. - E_INVALIDARG: The argument is invalid. - E_OUTOFMEMORY: The system is out
    *   of memory. - E_UNEXPECTED: An unexpected error occurred. - S_FALSE: The method did not retrieve
    *   the specified number of items in the enumeration sequence. - S_OK: The method successfully
    *   retrieved the specified number of items in the enumeration sequence.
    */
   STDMETHOD (Next)           (THIS_ ULONG, PVCMDNAMEW, ULONG *) PURE;
   /**
    * This method skips over a specified number of elements in the enumeration sequence.
    *
    * @param celt [in] Number of elements to be skipped.
    *
    * @return - NOERROR: The method successfully skipped over the elements. - E_INVALIDARG: The
    *   argument is invalid. - E_OUTOFMEMORY: The system is out of memory. - E_UNEXPECTED: An unexpected
    *   error occurred. - S_FALSE: The method did not skip over the specified number of elements. - S_OK:
    *   The method successfully skipped over the elements.
    */
   STDMETHOD (Skip)           (THIS_ ULONG) PURE;
   /**
    * This method resets the enumeration sequence back to the beginning.
    *
    * @return - NOERROR: The method successfully reset the enumeration sequence back to the beginning.
    *   - S_FALSE: The method did not reset the enumeration sequence back to the beginning. - S_OK: The
    *   method successfully reset the enumeration sequence back to the beginning.
    */
   STDMETHOD (Reset)          (THIS) PURE;
   /**
    * This method retrieves another enumerator that contains the same enumeration state as the current
    * one.
    *
    * @param ppenum [out] Pointer to a variable that receives the cloned enumerator. The type of this
    *   parameter is the same as the enumerator name. For example, if the enumerator name is
    *   IEnumFORMATETC, this parameter is of the IEnumFORMATETC type.
    *
    * @return - NOERROR: The method successfully retrieved the enumerator. - E_INVALIDARG: The argument
    *   is invalid. - E_OUTOFMEMORY: The system is out of memory. - E_UNEXPECTED: An unexpected error
    *   occurred.
    *
    * Using Clone, it is possible to record a particular point in the enumeration sequence and then
    * return to that point at a later time. The enumerator returned is of the same interface type as
    * the one being cloned.
    */
   STDMETHOD (Clone)          (THIS_ IVCmdEnumW * FAR *) PURE;
};
typedef IVCmdEnumW FAR * PIVCMDENUMW;


#undef   INTERFACE
#define  INTERFACE   IVCmdEnumA

// {E86F9540-DCA2-11CD-A166-00AA004CD65C}
DEFINE_GUID(IID_IVCmdEnumA, 
0xE86F9540, 0xDCA2, 0x11CD, 0xA1, 0x66, 0x0, 0xAA, 0x0, 0x4C, 0xD6, 0x5C);

/**
 * This interface is a standard OLE enumeration interface. Its methods are used by applications to
 * enumerate the menus stored in the voice command database
 *
 * This interface is supported by all voice command objects.
 */
DECLARE_INTERFACE_ (IVCmdEnumA, IUnknown) {
   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // IVCmdEnum members
   /**
    * This method retrieves the specified number of items in the enumeration sequence.
    *
    * @param celt [in] Number of elements to retrieve. If the number of elements requested is more than
    *   remains in the sequence, only the remaining elements are retrieved.
    * @param rgelt [out] Array that receives the elements. If an error value is returned, no entries in
    *   the array are valid.
    * @param pceltFetched [out] Pointer to a variable that receives the number of array elements
    *   actually copied to the array. This parameter cannot be NULL if celt is greater than one. If this
    *   parameter is NULL, celt must be one.
    *
    * @return - NOERROR: The method successfully retrieved the specified number of items in the
    *   enumeration sequence. - E_INVALIDARG: The argument is invalid. - E_OUTOFMEMORY: The system is out
    *   of memory. - E_UNEXPECTED: An unexpected error occurred. - S_FALSE: The method did not retrieve
    *   the specified number of items in the enumeration sequence. - S_OK: The method successfully
    *   retrieved the specified number of items in the enumeration sequence.
    */
   STDMETHOD (Next)           (THIS_ ULONG, PVCMDNAMEA, ULONG *) PURE;
   /**
    * This method skips over a specified number of elements in the enumeration sequence.
    *
    * @param celt [in] Number of elements to be skipped.
    *
    * @return - NOERROR: The method successfully skipped over the elements. - E_INVALIDARG: The
    *   argument is invalid. - E_OUTOFMEMORY: The system is out of memory. - E_UNEXPECTED: An unexpected
    *   error occurred. - S_FALSE: The method did not skip over the specified number of elements. - S_OK:
    *   The method successfully skipped over the elements.
    */
   STDMETHOD (Skip)           (THIS_ ULONG) PURE;
   /**
    * This method resets the enumeration sequence back to the beginning.
    *
    * @return - NOERROR: The method successfully reset the enumeration sequence back to the beginning.
    *   - S_FALSE: The method did not reset the enumeration sequence back to the beginning. - S_OK: The
    *   method successfully reset the enumeration sequence back to the beginning.
    */
   STDMETHOD (Reset)          (THIS) PURE;
   /**
    * This method retrieves another enumerator that contains the same enumeration state as the current
    * one.
    *
    * @param ppenum [out] Pointer to a variable that receives the cloned enumerator. The type of this
    *   parameter is the same as the enumerator name. For example, if the enumerator name is
    *   IEnumFORMATETC, this parameter is of the IEnumFORMATETC type.
    *
    * @return - NOERROR: The method successfully retrieved the enumerator. - E_INVALIDARG: The argument
    *   is invalid. - E_OUTOFMEMORY: The system is out of memory. - E_UNEXPECTED: An unexpected error
    *   occurred.
    *
    * Using Clone, it is possible to record a particular point in the enumeration sequence and then
    * return to that point at a later time. The enumerator returned is of the same interface type as
    * the one being cloned.
    */
   STDMETHOD (Clone)          (THIS_ IVCmdEnumA * FAR *) PURE;
};
typedef IVCmdEnumA FAR * PIVCMDENUMA;


#ifdef _S_UNICODE
 /**
  * This interface is a standard OLE enumeration interface. Its methods are used by applications to
  * enumerate the menus stored in the voice command database
  *
  * This interface is supported by all voice command objects.
  */
 #define IVCmdEnum              IVCmdEnumW
 #define IID_IVCmdEnum          IID_IVCmdEnumW
 #define PIVCMDENUM             PIVCMDENUMW

#else
 /**
  * This interface is a standard OLE enumeration interface. Its methods are used by applications to
  * enumerate the menus stored in the voice command database
  *
  * This interface is supported by all voice command objects.
  */
 #define IVCmdEnum              IVCmdEnumA
 #define IID_IVCmdEnum          IID_IVCmdEnumA
 #define PIVCMDENUM             PIVCMDENUMA

#endif // _S_UNICODE


 
 
/*
 *  IEnumSRShare
 */
#undef   INTERFACE
#define  INTERFACE   IEnumSRShareW

// {E97F05C0-81B3-11ce-B763-00AA004CD65C}
DEFINE_GUID(IID_IEnumSRShareW,
0xe97f05c0, 0x81b3, 0x11ce, 0xb7, 0x63, 0x0, 0xaa, 0x0, 0x4c, 0xd6, 0x5c);

DECLARE_INTERFACE_ (IEnumSRShareW, IUnknown) {
   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // IEnumSRShare members
   STDMETHOD (Next)           (THIS_ ULONG, PSRSHAREW, ULONG *) PURE;
   STDMETHOD (Skip)           (THIS_ ULONG) PURE;
   STDMETHOD (Reset)          (THIS) PURE;
   STDMETHOD (Clone)          (THIS_ IEnumSRShareW * FAR *) PURE;
   STDMETHOD (New)            (THIS_ DWORD, GUID, PISRCENTRALW *, QWORD *) PURE;
   STDMETHOD (Share)          (THIS_ QWORD, PISRCENTRALW *) PURE;
   STDMETHOD (Detach)         (THIS_ QWORD) PURE;
};
typedef IEnumSRShareW FAR * PIENUMSRSHAREW;


#undef   INTERFACE
#define  INTERFACE   IEnumSRShareA

// {E97F05C1-81B3-11ce-B763-00AA004CD65C}
DEFINE_GUID(IID_IEnumSRShareA,
0xe97f05c1, 0x81b3, 0x11ce, 0xb7, 0x63, 0x0, 0xaa, 0x0, 0x4c, 0xd6, 0x5c);

DECLARE_INTERFACE_ (IEnumSRShareA, IUnknown) {
   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // IEnumSRShare members
   STDMETHOD (Next)           (THIS_ ULONG, PSRSHAREA, ULONG *) PURE;
   STDMETHOD (Skip)           (THIS_ ULONG) PURE;
   STDMETHOD (Reset)          (THIS) PURE;
   STDMETHOD (Clone)          (THIS_ IEnumSRShareA * FAR *) PURE;
   STDMETHOD (New)            (THIS_ DWORD, GUID, PISRCENTRALA *, QWORD *) PURE;
   STDMETHOD (Share)          (THIS_ QWORD, PISRCENTRALA *) PURE;
   STDMETHOD (Detach)         (THIS_ QWORD) PURE;
};
typedef IEnumSRShareA FAR * PIENUMSRSHAREA;


#ifdef _S_UNICODE
 #define IEnumSRShare              IEnumSRShareW
 #define IID_IEnumSRShare          IID_IEnumSRShareW
 #define PIENUMSRSHARE             PIENUMSRSHAREW

#else
 #define IEnumSRShare              IEnumSRShareA
 #define IID_IEnumSRShare          IID_IEnumSRShareA
 #define PIENUMSRSHARE             PIENUMSRSHAREA

#endif // _S_UNICODE


 
 
/*
 *  IVCmdMenu
 */
#undef   INTERFACE
#define  INTERFACE   IVCmdMenuW

DEFINE_GUID(IID_IVCmdMenuW, 0xDAC54F60L, 0x604D, 0x101B, 0x99, 0x26, 0x00, 0xAA, 0x00, 0x3C, 0xFC, 0x2C);

/**
 * This interface allows an application to manage voice command menus. It includes methods for such
 * tasks as activating and deactivating menus, and adding and deleting phrases.
 *
 * This interface is supported by all voice command objects.
 *
 * The following flags are used with the methods of the IVCmdMenu interface to identify a command in
 * a voice command menu:
 *
 * - VCMD_BY_IDENTIFIER: The dwCmdNum parameter is the identifier of the command.
 *
 * - VCMD_BY_POSITION: The dwCmdNum parameter is the position in the list of commands.
 */
DECLARE_INTERFACE_ (IVCmdMenuW, IUnknown) {
   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // IVCmdMenu members
   /**
    * This method activates a voice menu so that its commands can be recognized.
    *
    * @param hWndListening [in] Handle to the window associated with the voice menu. Whenever this
    *   window is the foreground window, the voice menu is automatically activated. Otherwise, it is
    *   deactivated. If this parameter is NULL, the voice menu is global; that is, it remains active
    *   regardless of the foreground window, until the application explicitly deactivates it. For the
    *   Auto PC, set this parameter to NULL. The application has to activate and deactivate the voice
    *   menu manually when the focus switches.
    * @param dwFlags [in] Specifies how the menu should be active. It is one of the following values: -
    *   0 or NULL: The voice menu is active only when speech recognition is awake. - VWGFLAG_ASLEEP: The
    *   menu is active only when speech recognition is asleep and is automatically deactivated when
    *   speech recognition is awake. - VWGFLAG_BALLOON: This is a balloon grammar.
    *
    * @return - NOERROR: Although this value indicates success, the voice command menu is not
    *   necessarily active. The menu is active only when speech recognition is enabled and put in the
    *   correct asleep or awake mode. - E_INVALIDARG: The argument is invalid. -
    *   VCMDERR_CANTCREATEDATASTRUCTURES: The internal data structures needed to build a grammar cannot
    *   be created. - VCMDERR_CANTINITDATASTRUCTURES: The internal data structures needed to build a
    *   grammar cannot be initialized. - VCMDERR_CANTXTRACTWORDS: The unique words needed by the engine
    *   grammar object cannot be extracted. - VCMDERR_INVALIDWINDOW: The window is invalid. -
    *   VCMDERR_MENUACTIVE: The menu is currently active and cannot be deleted. - VCMDERR_MENUTOOCOMPLEX:
    *   The menu is too complex to use. - VCMDERR_MENUWRONGLANGUAGE: The language is not supported by the
    *   speech recognition engine. - VCMDERR_NOCACHEDATA: There is no internal cache entry for this menu.
    *   - VCMDERR_NOCOMMANDS: The menu is active, but the menu does not yet contain any commands. -
    *   VCMDERR_NOENGINE: No speech recognition engine is active. - VCMDERR_NOGRAMMARINTERFACE: No engine
    *   grammar object is available. - VCMDERR_OUTOFMEM: There is no more memory. - VCMDERR_TOOMANYMENUS:
    *   There are too many active menus.
    *
    * If you set the VWGFLAG_BALLOON bit in dwFlags, this method activates the menu normally. The menu
    * is automatically deactivated, however, after the speech recognition engine recognizes a word or
    * after speech recognition enters sleep. The application does not need to deactivate the menu or
    * check for notifications from IVCmdNotifySink::CommandOther once the automatic deactivation has
    * occurred.
    *
    * Only one balloon menu may be active at any time.
    */
   STDMETHOD (Activate)       (THIS_ HWND, DWORD) PURE;
   /**
    * This method deactivates an active voice menu so that the application no longer listens for its
    * commands.
    *
    * @return NOERROR indicates success. VCMDERR_OUTOFMEM indicates that a low memory condition exists.
    *
    * After calling Deactivate, the menu remains open until it is released, so the application can
    * start listening for the menu's commands again by calling IVCmdMenu::Activate.
    */
   STDMETHOD (Deactivate)     (THIS) PURE;
   STDMETHOD (TrainMenuDlg)   (THIS_ HWND, PCWSTR) PURE;
   /**
    * This method retrieves the total number of commands on a voice menu.
    *
    * @param pdwNumCmd [out] Pointer to a DWORD that receives the number of commands.
    *
    * @return - NOERROR: The method successfully retrieved the total number of commands. -
    *   E_INVALIDARG: The argument is invalid. - VCMDERR_INVALIDCHAR: There is an invalid character in
    *   the voice menu. - VCMDERR_MENUTOOCOMPLEX: The menu is too complex to use. - VCMDERR_OUTOFMEM:
    *   There is no more memory. - VCMDERR_VALUEOUTOFRANGE: The value is out of range.
    */
   STDMETHOD (Num)            (THIS_ DWORD *) PURE;
   /**
    * This method retrieves information about one or more commands in a voice menu.
    *
    * @param dwCmdStart [in] Specifies the number of the first command to retrieve. Commands are
    *   numbered sequentially from 1 to n. If dwFlag is the VCMD_BY_IDENTIFIER value, this parameter is
    *   ignored.
    * @param dwCmdNum [in] Specifies either the number of commands to retrieve or the identifier of the
    *   commands, depending on the value of dwFlag. If the sum of dwCmdStart and dwCmdNum exceeds the
    *   total number of commands in the menu, the method returns as many commands as possible.
    * @param dwFlag [in] Specifies the nature of dwCmdNum. It is one of the following flags: -
    *   VCMD_BY_IDENTIFIER: The dwCmdNum parameter is the identifier of the command. - VCMD_BY_POSITION:
    *   The dwCmdNum parameter is the position in the list of commands.
    * @param pdData [out] Pointer to an SDATA structure that receives the address and size of a buffer.
    *   The buffer contains a list of VCMDCOMMAND structures that describe the commands retrieved.
    *   Although they vary in size depending on the command data, the structures are contiguous within
    *   the list.
    * @param pdwCmdNum [out] Pointer to a DWORD that receives the number of commands actually copied to
    *   the buffer.
    *
    * @return - NOERROR: The method successfully retrieved information about the commands. -
    *   E_INVALIDARG: The argument is invalid. - VCMDERR_INVALIDCHAR: There is an invalid character in
    *   the voice menu. - VCMDERR_MENUTOOCOMPLEX: The menu is too complex to use. - VCMDERR_OUTOFDISK: No
    *   disk space is left to write information. - VCMDERR_OUTOFMEM: There is no more memory. -
    *   VCMDERR_VALUEOUTOFRANGE: The value is out of range.
    *
    * The calling application allocates the SDATA structure and passes its address to Get. Using the
    * OLE task allocator, Get allocates memory for the returned data and sets the pData member of SDATA
    * to point to the memory. If the allocation fails, pData is set to NULL and the dwSize member is
    * set to zero. The calling application must free the memory pointed to by pData, as well as the
    * SDATA structure itself, by calling the CoTaskMemFree function.
    */
   STDMETHOD (Get)            (THIS_ DWORD, DWORD, DWORD, PSDATA, DWORD *) PURE;
   /**
    * This method sets information for one or more commands in a voice menu.
    *
    * @param dwCmdStart [in] Specifies the number of the first command to set in the voice menu.
    *   Command positions are sequential, starting with 1 for the first command on the menu. If dwFlag is
    *   the VCMD_BY_IDENTIFIER value, dwCmdStart is ignored.
    * @param dwCmdNum [in] Specifies either the number of commands to set or the identifier of the
    *   commands, depending on the value of dwFlag. If the sum of dwCmdStart and dwCmdNum exceeds the
    *   number of commands in the menu, the method sets as many commands as possible.
    * @param dwFlag [in] Specifies the nature of dwCmdNum. It is one of the following flags: -
    *   VCMD_BY_IDENTIFIER: The dwCmdNum parameter is the identifier of the command. - VCMD_BY_POSITION:
    *   The dwCmdNum parameter is the position in the list of commands.
    * @param dData [in] SDATA structure that contains a pointer to a data buffer and the size of the
    *   buffer. The data buffer contains a list of VCMDCOMMAND structures that describe the voice
    *   commands to set. Although they vary in size depending on the command data, the structures are
    *   contiguous within the list.
    *
    * @return - NOERROR: The method successfully set information for one or more commands in the voice
    *   menu. - E_INVALIDARG: The argument is invalid. - VCMDERR_INVALIDCHAR: There is an invalid
    *   character in the voice menu. - VCMDERR_MENUTOOCOMPLEX: The menu is too complex to use. -
    *   VCMDERR_OUTOFDISK: No disk space is left to write information. - VCMDERR_OUTOFMEM: There is no
    *   more memory. - VCMDERR_VALUEOUTOFRANGE: The value is out of range.
    *
    * For best results, deactivate the voice menu before calling Set. Calling Set on an active menu can
    * be fairly slow because the menu must be deactivated, recompiled, and reactivated before Set
    * returns. If the menu is already deactivated when Set is called, the menu is not recompiled until
    * the application activates it again.
    */
   STDMETHOD (Set)            (THIS_ DWORD, DWORD, DWORD, SDATA) PURE;
   /**
    * This method adds one or more commands to a voice menu. The added commands are appended to any
    * existing commands in the menu.
    *
    * @param dwCmdNum [in] Specifies the number of commands to add to the menu.
    * @param dData [in] Specifies the SDATA structure that contains a list of VCMDCOMMAND structures
    *   that describe the voice commands to be added. Although they vary in size depending on the command
    *   data, the structures are contiguous within the list.
    * @param pdwCmdStart [out] Pointer to a DWORD that receives the number of the first command added
    *   to the menu.
    *
    * @return - NOERROR: The method successfully added the commands to the voice menu. - E_INVALIDARG:
    *   The argument is invalid. - VCMDERR_INVALIDCHAR: There is an invalid character in the voice menu.
    *   - VCMDERR_MENUTOOCOMPLEX: The menu is too complex to use. - VCMDERR_OUTOFMEM: There is no more
    *   memory. - VCMDERR_VALUEOUTOFRANGE: The value is out of range.
    *
    * For Auto PC, applications should use the IAPCSpeech::AddVMenuCommand method instead, but
    * IVCmdMenu::Add is still available to Auto PC applications.
    *
    * Commands are numbered sequentially from 1 to n. New commands are added to the end of the menu, so
    * the first command added is numbered n+1.
    *
    * For best results, deactivate the voice menu before calling Add. Otherwise, the menu must be
    * deactivated, recompiled, and reactivated before Add returns. If the menu is already deactivated
    * when Add is called, the menu is not recompiled until the application activates it again.
    *
    * If a command string includes a list name, you can use IVCmdMenu::ListSet to set the phrases that
    * the user can substitute for the list name when speaking the command.
    */
   STDMETHOD (Add)            (THIS_ DWORD, SDATA, DWORD *) PURE;
   /**
    * This method removes the specified commands from the voice menu.
    *
    * @param dwCmdStart [in] Specifies the number of the first command in the menu to remove. Command
    *   positions are sequential, starting with 1 for the first command on the menu. If dwFlag is the
    *   VCMD_BY_IDENTIFIER value, dwCmdStart is ignored.
    * @param dwCmdNum [in] Number of commands to remove or the identifier of the commands, depending on
    *   the value of dwFlag. If the sum of dwCmdStart and dwCmdNum exceeds the total number of commands
    *   in the menu, the method removes as many commands as possible.
    * @param dwFlag [in] Specifies the nature of dwCmdNum. It is one of the following values: -
    *   VCMD_BY_IDENTIFIER: The dwCmdNum parameter is the identifier of the command. - VCMD_BY_POSITION:
    *   The dwCmdNum parameter is the position in the list of commands.
    *
    * @return - NOERROR: The method successfully removed the specified commands. - E_INVALIDARG: The
    *   argument is invalid. - VCMDERR_INVALIDCHAR: There is an invalid character in the voice menu. -
    *   VCMDERR_MENUTOOCOMPLEX: The menu is too complex to use. - VCMDERR_OUTOFDISK: No disk space is
    *   left to write information. - VCMDERR_OUTOFMEM: There is no more memory. -
    *   VCMDERR_VALUEOUTOFRANGE: The value is out of range.
    *
    * For best results, deactivate the voice menu before calling Remove. Otherwise, the menu must be
    * deactivated, recompiled, and reactivated before Remove returns. If the menu is already
    * deactivated when Remove is called, the menu is not recompiled until the application activates it
    * again.
    */
   STDMETHOD (Remove)         (THIS_ DWORD, DWORD, DWORD) PURE;
   /**
    * This method retrieves the phrases stored in the current list for the selected voice menu.
    *
    * @param pszList [in] Pointer to the null-terminated string that contains the name of the list,
    *   such as "name" or "weekday." The list name must appear in the command string for at least one
    *   command on the menu. The command string is stored in the dwCommand member of the VCMDCOMMAND
    *   structure that defines the command.
    * @param pdList [out] Pointer to an SDATA structure that receives the address and size of a buffer.
    *   The buffer contains a sequential list of null-terminated strings, one for each phrase in the
    *   list.
    * @param pdwListNum [out] Pointer to a DWORD that receives the number of phrases that were copied
    *   to the buffer. If the list is empty, this parameter receives zero.
    *
    * @return - NOERROR: The method successfully retrieved the phrases stored in the current list. -
    *   E_INVALIDARG: The argument is invalid. - VCMDERR_INVALIDLIST: An invalid list was passed. -
    *   VCMDERR_OUTOFMEM: There is no more memory.
    *
    * A list is associated with a menu rather than an individual command. The list must appear in at
    * least one command string, but can be used by more than one command on the menu.
    *
    * The calling application allocates the SDATA structure and passes its address to ListGet. Using
    * the OLE task allocator, ListGet allocates memory for the returned data and sets the pData member
    * of the SDATA structure to point to the memory. If the allocation fails, the pData member is set
    * to NULL and the dwSize member is set to zero. The calling application must free the memory
    * pointed to by pData, as well as the SDATA structure itself, by calling the CoTaskMemFree
    * function.
    */
   STDMETHOD (ListGet)        (THIS_ PCWSTR, PSDATA, DWORD *) PURE;
   /**
    * This method sets the phrases in a list for a voice command.
    *
    * @param pszList [in] Pointer to the null-terminated string contains the name of the list to set,
    *   such as "name" or "weekday." The list name must appear in the command string for at least one
    *   command on the menu. The command string is specified in the dwCommand member of the VCMDCOMMAND
    *   structure that defines the command.
    * @param dwListNum [in] Specifies the number of phrases in the list.
    * @param dList [in] SDATA structure that contains a pointer to a data buffer and the size of the
    *   buffer. The data buffer contains a sequential list of null-terminated strings, one for each
    *   phrase in the list.
    *
    * @return - NOERROR: The method successfully set the phrases in the list. - E_INVALIDARG: The
    *   argument is invalid. - VCMDERR_INVALIDCHAR: There is an invalid character in the voice menu. -
    *   VCMDERR_INVALIDLIST: An invalid list was passed. - VCMDERR_OUTOFMEM: There is no more memory.
    *
    * The user can speak any phrase in the list in place of the list name in the command string. A
    * command that uses a list must have the list name in brackets-for example, "Send mail to <name>."
    *
    * Calling ListSet establishes a list of phrases that can be spoken in a voice command, such as
    * "Send mail to name." Typically, the list contains information that changes dynamically at run
    * time, such as the ten people to whom the user most recently sent electronic mail. For best
    * results, a list should have fewer than 20 entries. Having more than 20 entries in a list can
    * reduce the accuracy of recognition.
    *
    * The list persists until the voice menu object is released. List entries are not automatically
    * saved to disk. To preserve the list, call the IVCmdMenu::ListGet method and take steps to store
    * the result.
    *
    * ListSet is much faster than the IVCmdMenu interface's Add, Remove, or Set methods because list
    * entries are substituted when a command is recognized and the menu is not recompiled. This means
    * that ListSet can be called on an active menu without affecting performance.
    */
   STDMETHOD (ListSet)        (THIS_ PCWSTR, DWORD, SDATA) PURE;
   /**
    * This method permanently enables or disables a menu item. When a command is disabled by using
    * EnableItem, it is not compiled into the menu.
    *
    * @param dwEnable [in] Specifies whether the command is enabled. Set to TRUE to enable the command,
    *   or to FALSE to disable it.
    * @param dwCmdNum [in] Specifies the position or identifier of the command on the menu, depending
    *   on the value of dwFlag. Command positions are sequential, starting with 1 for the first command
    *   on the menu. The command identifier is specified in the dwID member of the VCMDCOMMAND structure
    *   that defines the command.
    * @param dwFlag [in] Specifies the nature of dwCmdNum. It is one of the following flags: -
    *   VCMD_BY_IDENTIFIER: The dwCmdNum parameter is the identifier of the command. - VCMD_BY_POSITION:
    *   The dwCmdNum parameter is the position in the list of commands.
    *
    * @return - NOERROR: The method successfully and permanently enabled or disabled the menu item. -
    *   E_INVALIDARG: The argument is invalid. - VCMDERR_OUTOFMEM: There is no more memory.
    *
    * For best results, deactivate the voice menu before calling EnableItem. Otherwise, the menu must
    * be deactivated, recompiled, and reactivated before the method returns. If the menu is already
    * deactivated when EnableItem is called, the menu is not recompiled until the application activates
    * it again.
    */
   STDMETHOD (EnableItem)     (THIS_ DWORD, DWORD, DWORD) PURE;
   /**
    * This method temporarily enables or disables a command on a voice menu.
    *
    * @param dwEnable [in] Set to TRUE to enable the command, or to FALSE to disable it.
    * @param dwCmdNum [in] Specifies the position or identifier of the command on the menu, depending
    *   on the value of dwFlag. Command positions are sequential, starting with 1 for the first command
    *   on the menu.
    * @param dwFlag [in] Specifies the nature of dwCmdNum. It is one of the following flags: -
    *   VCMD_BY_IDENTIFIER: The dwCmdNum parameter is the identifier of the command. - VCMD_BY_POSITION:
    *   The dwCmdNum parameter is the position in the list of commands.
    *
    * @return - NOERROR: The method successfully enabled or disabled a command on a voice menu
    *   temporarily. - E_INVALIDARG: The argument is invalid. - VCMDERR_OUTOFMEM: There is no more
    *   memory.
    *
    * If a command is disabled by using SetItem, the voice command object sends a CommandOther
    * notification rather than a CommandRecognize notification when it recognizes the disabled command.
    *
    * SetItem is much faster than the IVCmdMenu::EnableItem method because the menu is not recompiled.
    * This means that SetItem can be called on an active menu without affecting performance.
    */
   STDMETHOD (SetItem)        (THIS_ DWORD, DWORD, DWORD) PURE;
};

typedef IVCmdMenuW FAR * PIVCMDMENUW;


#undef   INTERFACE
#define  INTERFACE   IVCmdMenuA

// {746141E0-5543-11b9-C000-5611722E1D15}
DEFINE_GUID(IID_IVCmdMenuA, 0x746141e0, 0x5543, 0x11b9, 0xc0, 0x0, 0x56, 0x11, 0x72, 0x2e, 0x1d, 0x15);

/**
 * This interface allows an application to manage voice command menus. It includes methods for such
 * tasks as activating and deactivating menus, and adding and deleting phrases.
 *
 * This interface is supported by all voice command objects.
 *
 * The following flags are used with the methods of the IVCmdMenu interface to identify a command in
 * a voice command menu:
 *
 * - VCMD_BY_IDENTIFIER: The dwCmdNum parameter is the identifier of the command.
 *
 * - VCMD_BY_POSITION: The dwCmdNum parameter is the position in the list of commands.
 */
DECLARE_INTERFACE_ (IVCmdMenuA, IUnknown) {
   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // IVCmdMenu members
   /**
    * This method activates a voice menu so that its commands can be recognized.
    *
    * @param hWndListening [in] Handle to the window associated with the voice menu. Whenever this
    *   window is the foreground window, the voice menu is automatically activated. Otherwise, it is
    *   deactivated. If this parameter is NULL, the voice menu is global; that is, it remains active
    *   regardless of the foreground window, until the application explicitly deactivates it. For the
    *   Auto PC, set this parameter to NULL. The application has to activate and deactivate the voice
    *   menu manually when the focus switches.
    * @param dwFlags [in] Specifies how the menu should be active. It is one of the following values: -
    *   0 or NULL: The voice menu is active only when speech recognition is awake. - VWGFLAG_ASLEEP: The
    *   menu is active only when speech recognition is asleep and is automatically deactivated when
    *   speech recognition is awake. - VWGFLAG_BALLOON: This is a balloon grammar.
    *
    * @return - NOERROR: Although this value indicates success, the voice command menu is not
    *   necessarily active. The menu is active only when speech recognition is enabled and put in the
    *   correct asleep or awake mode. - E_INVALIDARG: The argument is invalid. -
    *   VCMDERR_CANTCREATEDATASTRUCTURES: The internal data structures needed to build a grammar cannot
    *   be created. - VCMDERR_CANTINITDATASTRUCTURES: The internal data structures needed to build a
    *   grammar cannot be initialized. - VCMDERR_CANTXTRACTWORDS: The unique words needed by the engine
    *   grammar object cannot be extracted. - VCMDERR_INVALIDWINDOW: The window is invalid. -
    *   VCMDERR_MENUACTIVE: The menu is currently active and cannot be deleted. - VCMDERR_MENUTOOCOMPLEX:
    *   The menu is too complex to use. - VCMDERR_MENUWRONGLANGUAGE: The language is not supported by the
    *   speech recognition engine. - VCMDERR_NOCACHEDATA: There is no internal cache entry for this menu.
    *   - VCMDERR_NOCOMMANDS: The menu is active, but the menu does not yet contain any commands. -
    *   VCMDERR_NOENGINE: No speech recognition engine is active. - VCMDERR_NOGRAMMARINTERFACE: No engine
    *   grammar object is available. - VCMDERR_OUTOFMEM: There is no more memory. - VCMDERR_TOOMANYMENUS:
    *   There are too many active menus.
    *
    * If you set the VWGFLAG_BALLOON bit in dwFlags, this method activates the menu normally. The menu
    * is automatically deactivated, however, after the speech recognition engine recognizes a word or
    * after speech recognition enters sleep. The application does not need to deactivate the menu or
    * check for notifications from IVCmdNotifySink::CommandOther once the automatic deactivation has
    * occurred.
    *
    * Only one balloon menu may be active at any time.
    */
   STDMETHOD (Activate)       (THIS_ HWND, DWORD) PURE;
   /**
    * This method deactivates an active voice menu so that the application no longer listens for its
    * commands.
    *
    * @return NOERROR indicates success. VCMDERR_OUTOFMEM indicates that a low memory condition exists.
    *
    * After calling Deactivate, the menu remains open until it is released, so the application can
    * start listening for the menu's commands again by calling IVCmdMenu::Activate.
    */
   STDMETHOD (Deactivate)     (THIS) PURE;
   STDMETHOD (TrainMenuDlg)   (THIS_ HWND, PCSTR) PURE;
   /**
    * This method retrieves the total number of commands on a voice menu.
    *
    * @param pdwNumCmd [out] Pointer to a DWORD that receives the number of commands.
    *
    * @return - NOERROR: The method successfully retrieved the total number of commands. -
    *   E_INVALIDARG: The argument is invalid. - VCMDERR_INVALIDCHAR: There is an invalid character in
    *   the voice menu. - VCMDERR_MENUTOOCOMPLEX: The menu is too complex to use. - VCMDERR_OUTOFMEM:
    *   There is no more memory. - VCMDERR_VALUEOUTOFRANGE: The value is out of range.
    */
   STDMETHOD (Num)            (THIS_ DWORD *) PURE;
   /**
    * This method retrieves information about one or more commands in a voice menu.
    *
    * @param dwCmdStart [in] Specifies the number of the first command to retrieve. Commands are
    *   numbered sequentially from 1 to n. If dwFlag is the VCMD_BY_IDENTIFIER value, this parameter is
    *   ignored.
    * @param dwCmdNum [in] Specifies either the number of commands to retrieve or the identifier of the
    *   commands, depending on the value of dwFlag. If the sum of dwCmdStart and dwCmdNum exceeds the
    *   total number of commands in the menu, the method returns as many commands as possible.
    * @param dwFlag [in] Specifies the nature of dwCmdNum. It is one of the following flags: -
    *   VCMD_BY_IDENTIFIER: The dwCmdNum parameter is the identifier of the command. - VCMD_BY_POSITION:
    *   The dwCmdNum parameter is the position in the list of commands.
    * @param pdData [out] Pointer to an SDATA structure that receives the address and size of a buffer.
    *   The buffer contains a list of VCMDCOMMAND structures that describe the commands retrieved.
    *   Although they vary in size depending on the command data, the structures are contiguous within
    *   the list.
    * @param pdwCmdNum [out] Pointer to a DWORD that receives the number of commands actually copied to
    *   the buffer.
    *
    * @return - NOERROR: The method successfully retrieved information about the commands. -
    *   E_INVALIDARG: The argument is invalid. - VCMDERR_INVALIDCHAR: There is an invalid character in
    *   the voice menu. - VCMDERR_MENUTOOCOMPLEX: The menu is too complex to use. - VCMDERR_OUTOFDISK: No
    *   disk space is left to write information. - VCMDERR_OUTOFMEM: There is no more memory. -
    *   VCMDERR_VALUEOUTOFRANGE: The value is out of range.
    *
    * The calling application allocates the SDATA structure and passes its address to Get. Using the
    * OLE task allocator, Get allocates memory for the returned data and sets the pData member of SDATA
    * to point to the memory. If the allocation fails, pData is set to NULL and the dwSize member is
    * set to zero. The calling application must free the memory pointed to by pData, as well as the
    * SDATA structure itself, by calling the CoTaskMemFree function.
    */
   STDMETHOD (Get)            (THIS_ DWORD, DWORD, DWORD, PSDATA, DWORD *) PURE;
   /**
    * This method sets information for one or more commands in a voice menu.
    *
    * @param dwCmdStart [in] Specifies the number of the first command to set in the voice menu.
    *   Command positions are sequential, starting with 1 for the first command on the menu. If dwFlag is
    *   the VCMD_BY_IDENTIFIER value, dwCmdStart is ignored.
    * @param dwCmdNum [in] Specifies either the number of commands to set or the identifier of the
    *   commands, depending on the value of dwFlag. If the sum of dwCmdStart and dwCmdNum exceeds the
    *   number of commands in the menu, the method sets as many commands as possible.
    * @param dwFlag [in] Specifies the nature of dwCmdNum. It is one of the following flags: -
    *   VCMD_BY_IDENTIFIER: The dwCmdNum parameter is the identifier of the command. - VCMD_BY_POSITION:
    *   The dwCmdNum parameter is the position in the list of commands.
    * @param dData [in] SDATA structure that contains a pointer to a data buffer and the size of the
    *   buffer. The data buffer contains a list of VCMDCOMMAND structures that describe the voice
    *   commands to set. Although they vary in size depending on the command data, the structures are
    *   contiguous within the list.
    *
    * @return - NOERROR: The method successfully set information for one or more commands in the voice
    *   menu. - E_INVALIDARG: The argument is invalid. - VCMDERR_INVALIDCHAR: There is an invalid
    *   character in the voice menu. - VCMDERR_MENUTOOCOMPLEX: The menu is too complex to use. -
    *   VCMDERR_OUTOFDISK: No disk space is left to write information. - VCMDERR_OUTOFMEM: There is no
    *   more memory. - VCMDERR_VALUEOUTOFRANGE: The value is out of range.
    *
    * For best results, deactivate the voice menu before calling Set. Calling Set on an active menu can
    * be fairly slow because the menu must be deactivated, recompiled, and reactivated before Set
    * returns. If the menu is already deactivated when Set is called, the menu is not recompiled until
    * the application activates it again.
    */
   STDMETHOD (Set)            (THIS_ DWORD, DWORD, DWORD, SDATA) PURE;
   /**
    * This method adds one or more commands to a voice menu. The added commands are appended to any
    * existing commands in the menu.
    *
    * @param dwCmdNum [in] Specifies the number of commands to add to the menu.
    * @param dData [in] Specifies the SDATA structure that contains a list of VCMDCOMMAND structures
    *   that describe the voice commands to be added. Although they vary in size depending on the command
    *   data, the structures are contiguous within the list.
    * @param pdwCmdStart [out] Pointer to a DWORD that receives the number of the first command added
    *   to the menu.
    *
    * @return - NOERROR: The method successfully added the commands to the voice menu. - E_INVALIDARG:
    *   The argument is invalid. - VCMDERR_INVALIDCHAR: There is an invalid character in the voice menu.
    *   - VCMDERR_MENUTOOCOMPLEX: The menu is too complex to use. - VCMDERR_OUTOFMEM: There is no more
    *   memory. - VCMDERR_VALUEOUTOFRANGE: The value is out of range.
    *
    * For Auto PC, applications should use the IAPCSpeech::AddVMenuCommand method instead, but
    * IVCmdMenu::Add is still available to Auto PC applications.
    *
    * Commands are numbered sequentially from 1 to n. New commands are added to the end of the menu, so
    * the first command added is numbered n+1.
    *
    * For best results, deactivate the voice menu before calling Add. Otherwise, the menu must be
    * deactivated, recompiled, and reactivated before Add returns. If the menu is already deactivated
    * when Add is called, the menu is not recompiled until the application activates it again.
    *
    * If a command string includes a list name, you can use IVCmdMenu::ListSet to set the phrases that
    * the user can substitute for the list name when speaking the command.
    */
   STDMETHOD (Add)            (THIS_ DWORD, SDATA, DWORD *) PURE;
   /**
    * This method removes the specified commands from the voice menu.
    *
    * @param dwCmdStart [in] Specifies the number of the first command in the menu to remove. Command
    *   positions are sequential, starting with 1 for the first command on the menu. If dwFlag is the
    *   VCMD_BY_IDENTIFIER value, dwCmdStart is ignored.
    * @param dwCmdNum [in] Number of commands to remove or the identifier of the commands, depending on
    *   the value of dwFlag. If the sum of dwCmdStart and dwCmdNum exceeds the total number of commands
    *   in the menu, the method removes as many commands as possible.
    * @param dwFlag [in] Specifies the nature of dwCmdNum. It is one of the following values: -
    *   VCMD_BY_IDENTIFIER: The dwCmdNum parameter is the identifier of the command. - VCMD_BY_POSITION:
    *   The dwCmdNum parameter is the position in the list of commands.
    *
    * @return - NOERROR: The method successfully removed the specified commands. - E_INVALIDARG: The
    *   argument is invalid. - VCMDERR_INVALIDCHAR: There is an invalid character in the voice menu. -
    *   VCMDERR_MENUTOOCOMPLEX: The menu is too complex to use. - VCMDERR_OUTOFDISK: No disk space is
    *   left to write information. - VCMDERR_OUTOFMEM: There is no more memory. -
    *   VCMDERR_VALUEOUTOFRANGE: The value is out of range.
    *
    * For best results, deactivate the voice menu before calling Remove. Otherwise, the menu must be
    * deactivated, recompiled, and reactivated before Remove returns. If the menu is already
    * deactivated when Remove is called, the menu is not recompiled until the application activates it
    * again.
    */
   STDMETHOD (Remove)         (THIS_ DWORD, DWORD, DWORD) PURE;
   /**
    * This method retrieves the phrases stored in the current list for the selected voice menu.
    *
    * @param pszList [in] Pointer to the null-terminated string that contains the name of the list,
    *   such as "name" or "weekday." The list name must appear in the command string for at least one
    *   command on the menu. The command string is stored in the dwCommand member of the VCMDCOMMAND
    *   structure that defines the command.
    * @param pdList [out] Pointer to an SDATA structure that receives the address and size of a buffer.
    *   The buffer contains a sequential list of null-terminated strings, one for each phrase in the
    *   list.
    * @param pdwListNum [out] Pointer to a DWORD that receives the number of phrases that were copied
    *   to the buffer. If the list is empty, this parameter receives zero.
    *
    * @return - NOERROR: The method successfully retrieved the phrases stored in the current list. -
    *   E_INVALIDARG: The argument is invalid. - VCMDERR_INVALIDLIST: An invalid list was passed. -
    *   VCMDERR_OUTOFMEM: There is no more memory.
    *
    * A list is associated with a menu rather than an individual command. The list must appear in at
    * least one command string, but can be used by more than one command on the menu.
    *
    * The calling application allocates the SDATA structure and passes its address to ListGet. Using
    * the OLE task allocator, ListGet allocates memory for the returned data and sets the pData member
    * of the SDATA structure to point to the memory. If the allocation fails, the pData member is set
    * to NULL and the dwSize member is set to zero. The calling application must free the memory
    * pointed to by pData, as well as the SDATA structure itself, by calling the CoTaskMemFree
    * function.
    */
   STDMETHOD (ListGet)        (THIS_ PCSTR, PSDATA, DWORD *) PURE;
   /**
    * This method sets the phrases in a list for a voice command.
    *
    * @param pszList [in] Pointer to the null-terminated string contains the name of the list to set,
    *   such as "name" or "weekday." The list name must appear in the command string for at least one
    *   command on the menu. The command string is specified in the dwCommand member of the VCMDCOMMAND
    *   structure that defines the command.
    * @param dwListNum [in] Specifies the number of phrases in the list.
    * @param dList [in] SDATA structure that contains a pointer to a data buffer and the size of the
    *   buffer. The data buffer contains a sequential list of null-terminated strings, one for each
    *   phrase in the list.
    *
    * @return - NOERROR: The method successfully set the phrases in the list. - E_INVALIDARG: The
    *   argument is invalid. - VCMDERR_INVALIDCHAR: There is an invalid character in the voice menu. -
    *   VCMDERR_INVALIDLIST: An invalid list was passed. - VCMDERR_OUTOFMEM: There is no more memory.
    *
    * The user can speak any phrase in the list in place of the list name in the command string. A
    * command that uses a list must have the list name in brackets-for example, "Send mail to <name>."
    *
    * Calling ListSet establishes a list of phrases that can be spoken in a voice command, such as
    * "Send mail to name." Typically, the list contains information that changes dynamically at run
    * time, such as the ten people to whom the user most recently sent electronic mail. For best
    * results, a list should have fewer than 20 entries. Having more than 20 entries in a list can
    * reduce the accuracy of recognition.
    *
    * The list persists until the voice menu object is released. List entries are not automatically
    * saved to disk. To preserve the list, call the IVCmdMenu::ListGet method and take steps to store
    * the result.
    *
    * ListSet is much faster than the IVCmdMenu interface's Add, Remove, or Set methods because list
    * entries are substituted when a command is recognized and the menu is not recompiled. This means
    * that ListSet can be called on an active menu without affecting performance.
    */
   STDMETHOD (ListSet)        (THIS_ PCSTR, DWORD, SDATA) PURE;
   /**
    * This method permanently enables or disables a menu item. When a command is disabled by using
    * EnableItem, it is not compiled into the menu.
    *
    * @param dwEnable [in] Specifies whether the command is enabled. Set to TRUE to enable the command,
    *   or to FALSE to disable it.
    * @param dwCmdNum [in] Specifies the position or identifier of the command on the menu, depending
    *   on the value of dwFlag. Command positions are sequential, starting with 1 for the first command
    *   on the menu. The command identifier is specified in the dwID member of the VCMDCOMMAND structure
    *   that defines the command.
    * @param dwFlag [in] Specifies the nature of dwCmdNum. It is one of the following flags: -
    *   VCMD_BY_IDENTIFIER: The dwCmdNum parameter is the identifier of the command. - VCMD_BY_POSITION:
    *   The dwCmdNum parameter is the position in the list of commands.
    *
    * @return - NOERROR: The method successfully and permanently enabled or disabled the menu item. -
    *   E_INVALIDARG: The argument is invalid. - VCMDERR_OUTOFMEM: There is no more memory.
    *
    * For best results, deactivate the voice menu before calling EnableItem. Otherwise, the menu must
    * be deactivated, recompiled, and reactivated before the method returns. If the menu is already
    * deactivated when EnableItem is called, the menu is not recompiled until the application activates
    * it again.
    */
   STDMETHOD (EnableItem)     (THIS_ DWORD, DWORD, DWORD) PURE;
   /**
    * This method temporarily enables or disables a command on a voice menu.
    *
    * @param dwEnable [in] Set to TRUE to enable the command, or to FALSE to disable it.
    * @param dwCmdNum [in] Specifies the position or identifier of the command on the menu, depending
    *   on the value of dwFlag. Command positions are sequential, starting with 1 for the first command
    *   on the menu.
    * @param dwFlag [in] Specifies the nature of dwCmdNum. It is one of the following flags: -
    *   VCMD_BY_IDENTIFIER: The dwCmdNum parameter is the identifier of the command. - VCMD_BY_POSITION:
    *   The dwCmdNum parameter is the position in the list of commands.
    *
    * @return - NOERROR: The method successfully enabled or disabled a command on a voice menu
    *   temporarily. - E_INVALIDARG: The argument is invalid. - VCMDERR_OUTOFMEM: There is no more
    *   memory.
    *
    * If a command is disabled by using SetItem, the voice command object sends a CommandOther
    * notification rather than a CommandRecognize notification when it recognizes the disabled command.
    *
    * SetItem is much faster than the IVCmdMenu::EnableItem method because the menu is not recompiled.
    * This means that SetItem can be called on an active menu without affecting performance.
    */
   STDMETHOD (SetItem)        (THIS_ DWORD, DWORD, DWORD) PURE;
};

typedef IVCmdMenuA FAR * PIVCMDMENUA;


#ifdef _S_UNICODE
 /**
  * This interface allows an application to manage voice command menus. It includes methods for such
  * tasks as activating and deactivating menus, and adding and deleting phrases.
  *
  * This interface is supported by all voice command objects.
  *
  * The following flags are used with the methods of the IVCmdMenu interface to identify a command in
  * a voice command menu:
  *
  * - VCMD_BY_IDENTIFIER: The dwCmdNum parameter is the identifier of the command.
  *
  * - VCMD_BY_POSITION: The dwCmdNum parameter is the position in the list of commands.
  */
 #define IVCmdMenu      IVCmdMenuW
 #define IID_IVCmdMenu  IID_IVCmdMenuW
 #define PIVCMDMENU     PIVCMDMENUW

#else
 /**
  * This interface allows an application to manage voice command menus. It includes methods for such
  * tasks as activating and deactivating menus, and adding and deleting phrases.
  *
  * This interface is supported by all voice command objects.
  *
  * The following flags are used with the methods of the IVCmdMenu interface to identify a command in
  * a voice command menu:
  *
  * - VCMD_BY_IDENTIFIER: The dwCmdNum parameter is the identifier of the command.
  *
  * - VCMD_BY_POSITION: The dwCmdNum parameter is the position in the list of commands.
  */
 #define IVCmdMenu      IVCmdMenuA
 #define IID_IVCmdMenu  IID_IVCmdMenuA
 #define PIVCMDMENU     PIVCMDMENUA

#endif // _S_UNICODE



/*
 *  IVoiceCmd
 */
#undef   INTERFACE
#define  INTERFACE   IVoiceCmdW

DEFINE_GUID(IID_IVoiceCmdW, 0xE0DCC220L, 0x604D, 0x101B, 0x99, 0x26, 0x00, 0xAA, 0x00, 0x3C, 0xFC, 0x2C);

/**
 * This interface registers an application with a voice command object. It is also used for tasks
 * such as creating menus and menu enumerators.
 *
 * This interface is supported by all voice command objects.
 */
DECLARE_INTERFACE_ (IVoiceCmdW, IUnknown) {
   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // IVoiceCmd members
   /**
    * This method is called by an application to register to use voice commands on a site.
    *
    * @param pszSite Ignored, because there is only one site: "Local PC."
    * @param pNotifyInterface [in] Pointer to the notification interface that receives notifications
    *   from the voice command object. The interface identifier is specified by IIDNotifyInterface. If
    *   this parameter is NULL, no notifications are sent. Because passing the pointer to the voice
    *   command object does not transfer ownership of the notification interface, the voice command
    *   object must call the AddRef method of the notification interface before returning from the call
    *   to Register. The voice command object must also call the Release method of the notification
    *   interface when it closes. The calling application must release any reference counts it holds on
    *   the notification interface after calling Register, unless it needs the notification object to be
    *   valid when the voice command object releases it.
    * @param IIDNotifyInterface [in] Interface identifier (IID) that uniquely identifies the type of
    *   notification sink being passed to the voice command object. It must be IID_IVCmdNotifySinkW.
    * @param dwFlags [in] Specifies whether the application is to receive all notifications. It is one
    *   of the following flags: - VCMDRF_ALLBUTVUMETER: Sends all but VUMeter notifications to
    *   pNotifyInterface. - VCMDRF_NOMESSAGES: Does not send notifications. - VCMDRF_CMDOTHER: Sends
    *   CommandOther notifications to pNotifyInterface. - VCMDRF_CMDSTART: Sends CommandStart
    *   notifications to pNotifyInterface. - VCMDRF_ATTRIBCHANGE: Sends AttribChanged notifications to
    *   pNotifyInterface. - VCMDRF_CMDRECOG: Sends CommandRecognize notifications to pNotifyInterface.
    * @param pSiteInfo [in] Pointer to a VCSITEINFO structure that contains settings to apply to the
    *   site, such as the speaker, confidence threshold, and speech-recognition mode. The settings are
    *   applied even if the site is already open. If this parameter is NULL, the voice command object
    *   uses the settings from the registry. If there are no registry settings, it uses the default
    *   settings, typically those for the computer. Telephony applications pass this information to
    *   ensure that the proper settings are selected. Other applications set this parameter to NULL to
    *   leave the site settings unchanged from previous values.
    *
    * @return - NOERROR: The method successfully registered to use voice commands on a site. -
    *   E_INVALIDARG: The argument is invalid. - VCMDERR_CANTCREATEAUDIODEVICE: An audio source object
    *   cannot be created for speech recognition. - VCMDERR_CANTCREATESRENUM: A speech recognition
    *   enumerator object cannot be created. - VCMDERR_CANTSELECTENGINE: A speech recognition engine
    *   cannot be selected. - VCMDERR_CANTSETDEVICE: The device identifier cannot be set into the audio
    *   source object. - VCMDERR_INVALIDMODE: No site exists, the site does not support this attribute,
    *   or the voice command object is already registered with a site. - VCMDERR_NOFINDINTERFACE: The
    *   speech recognition enumerator interface does not have a Find interface. - VCMDERR_NOSITEINFO:
    *   Information to open this site is not available. - VCMDERR_OUTOFMEM: There is no more memory. -
    *   VCMDERR_SRFINDFAILED: The speech recognition object could not find an appropriate mode. -
    *   VCMDERR_VALUEOUTOFRANGE: The value is out of range.
    *
    * An application cannot call Register a second time for the same voice command object. If a voice
    * command object is already registered, calling Register returns an error. To change sites, the
    * application must call the CoCreateInstance function to create a new voice command object for the
    * desired site.
    */
   STDMETHOD (Register)       (THIS_ PCWSTR, PIVCMDNOTIFYSINK, GUID, DWORD,
                                     PVCSITEINFOW) PURE;
   /**
    * This method creates a voice menu enumerator to enumerate menus in the voice menu database.
    *
    * @param dwFlags [in] Specifies whether to enumerate active menus or open menus, which have voice
    *   menu objects, but may or may not be active. It is a combination of some of the following flags: -
    *   VCMDEF_ACTIVE: Enumerates only active menus. - VCMDEF_DATABASE: Enumerates all menus in the voice
    *   menu database. - VCMDEF_PERMANENT: Enumerates only permanent menus. - VCMDEF_SELECTED: Enumerates
    *   open menus, whether or not they are also active. - VCMDEF_TEMPORARY: Enumerates only temporary
    *   menus. VCMDEF_ACTIVE and VCMDEF_SELECTED are mutually exclusive, as are VCMDEF_TEMPORARY and
    *   VCMDEF_PERMANENT. If both VCMDEF_ACTIVE and VCMDEF_SELECTED are specified, the method returns an
    *   error. VCMDEF_TEMPORARY and VCMDEF_PERMANENT are ignored if neither VCMDEF_ACTIVE nor
    *   VCMDEF_SELECTED are specified. In other words, these flags do not apply if you want to enumerate
    *   the menus in the database. By definition, if a menu is active, it is selected.
    * @param pszApplicationFilter [in] Pointer to the null-terminated string that contains the name of
    *   the application whose menus are enumerated. This name is the same as that in the szApplication
    *   member of the VCMDNAME structure passed to the IVoiceCmd::MenuCreate method. If this parameter is
    *   NULL, menus for all applications, except those eliminated by dwFlags and pszStateFilter, are
    *   enumerated.
    * @param pszStateFilter [in] Pointer to a null-terminated string that contains the name of the
    *   state whose menus are enumerated. This state is the same as that in the szState member of the
    *   VCMDNAME structure passed to MenuCreate. If this parameter is NULL, menus for all applications,
    *   except those eliminated by dwFlags and pszApplicationFilter, are enumerated.
    * @param ppiVCmdEnum [out] Pointer to a variable that receives a pointer to an IVCmdEnum interface
    *   for the newly created voice menu enumerator. If an error occurs, this parameter receives NULL.
    *
    * @return - NOERROR: The method successfully created a voice menu enumerator. - E_INVALIDARG: The
    *   argument is invalid. - VCMDERR_INVALIDMODE: No site exists, the site does not support this
    *   attribute, or the voice command object is already registered with a site. -
    *   VCMDERR_MENUDOESNOTEXIST: The requested menu does not exist in the database. - VCMDERR_OUTOFMEM:
    *   There is no more memory. - VCMDERR_VALUEOUTOFRANGE: The value is out of range.
    *
    * An application can use a voice menu enumerator to find and modify unknown menus or to show menu
    * status to the user.
    *
    * The voice menu enumerator persists until all references to it are released, even if the voice
    * command object is released.
    */
   STDMETHOD (MenuEnum)       (THIS_ DWORD, PCWSTR, PCWSTR, PIVCMDENUMW *) PURE;
   /**
    * This method creates a voice menu object to represent a new or existing voice menu for an
    * application.
    *
    * @param pName [in] Pointer to a VCMDNAME structure that identifies the menu to create. The
    *   VCMDNAME structure contains an application name, such as "Radio," and a state name, such as "main
    *   form."
    * @param pLanguage [in] Pointer to a LANGUAGE structure that indicates the language to use for the
    *   menu. If this parameter is NULL, the default language for the site's speech-recognition mode is
    *   used.
    * @param dwFlags [in] Specifies how to create the menu. It is one of the following flags: -
    *   VCMDMC_CREATE_ALWAYS: Creates an empty menu with the specified name. If a menu by that name
    *   already exists in the voice menu database, it is erased. For Microsoft Windows CE for the Auto
    *   PC, the voice menu is removed from the database when the menu is released. - VCMDMC_CREATE_NEW:
    *   Creates an empty menu with the specified name. If a menu by that name already exists in the voice
    *   menu database, the method returns an error. The new menu is stored in the database when the menu
    *   object is released. - VCMDMC_CREATE_TEMP: Creates an empty menu with the specified name. If a
    *   menu by that name already exists in the voice menu database, the method returns an error. The new
    *   menu is temporary and is discarded when the menu object is released. - VCMDMC_OPEN_ALWAYS: Opens
    *   an existing menu with the specified name. If the menu does not exist, the method creates a new,
    *   empty menu. The new menu is stored in the database when the menu object is released.
    * @param ppIVCmdMenu [out] Pointer to an IVCmdMenu interface for the newly created voice menu
    *   object. The application uses the pointer to this interface to call IVCmdMenu methods on the voice
    *   menu object. If an error occurs, this parameter receives NULL.
    *
    * @return - NOERROR: The method successfully created a voice menu object. - E_INVALIDARG: The
    *   argument is invalid. - VCMDERR_CANTCREATESTORAGE: Space cannot be created in the database for the
    *   menu. - VCMDERR_MENUDOESNOTEXIST: The requested menu does not exist in the database. -
    *   VCMDERR_MENUEXIST: The requested new or temporary menu already exists in the database. -
    *   VCMDERR_OUTOFDISK: No disk space is left to write information. - VCMDERR_OUTOFMEM: There is no
    *   more memory. - VCMDERR_VALUEOUTOFRANGE: The value is out of range.
    *
    * An application can create a voice menu object by loading an existing voice menu from the voice
    * menu database or creating a new voice menu. A voice menu does not need to be stored in the
    * database; an application can create a temporary voice menu by setting dwFlags to the
    * VCMDMC_CREATE_TEMP value. A temporary voice menu persists until the menu object is released.
    *
    * An application can create more than one voice menu object to represent the same menu-either one
    * of its own menus or a menu for another application. For example, one application might do this to
    * enumerate another application's menus.
    *
    * More than one application can use the same voice menu object. For example, Application A might
    * call the IVoiceCmd::CmdMimic method on a voice menu object that represents a menu for Application
    * B, while Application B uses the same menu object to recognize commands spoken by the user.
    *
    * For the Auto PC, developers should use IApcSpeech::CreateVMenu to create a voice menu instead.
    */
   STDMETHOD (MenuCreate)     (THIS_ PVCMDNAMEW, PLANGUAGEW, DWORD,
                                     IVCmdMenuW **) PURE;
   /**
    * This method deletes a menu from the voice menu database.
    *
    * @param pName [in] Pointer to a VCMDNAME structure that identifies the menu to delete.
    *
    * @return - NOERROR: The method successfully deleted the menu. - E_INVALIDARG: The argument is
    *   invalid. - VCMDERR_MENUACTIVE: The menu is currently active and cannot be deleted. -
    *   VCMDERR_MENUDOESNOTEXIST: The requested menu does not exist in the database. - VCMDERR_MENUOPEN:
    *   The menu exists but has not been released, so it cannot be deleted. - VCMDERR_OUTOFMEM: There is
    *   no more memory.
    *
    * A menu cannot be deleted if it is currently open and the application is actively listening for
    * its commands.
    *
    * This method deletes the storage in the database for the menu, if the menu exists, and releases
    * the voice menu object that was created by the IVoiceCmd::MenuCreate method. After a menu is
    * deleted, the pointer to its IVCmdMenu interface is invalid, so set it to NULL.
    */
   STDMETHOD (MenuDelete)     (THIS_ PVCMDNAMEW) PURE;
   /**
    * This method supplies a voice-aware application with the equivalent of a spoken voice command.
    *
    * @param pMenu [in] Pointer to a VCMDNAME structure identifying the menu that contains the command
    *   to mimic.
    * @param pszCommand [in] Pointer to the null-terminated string that contains the command to mimic.
    *
    * @return - NOERROR: The method successfully supplied a voice-aware application with the equivalent
    *   of a spoken voice command. - E_INVALIDARG: The argument is invalid. - VCMDERR_CANNOTMIMIC: No
    *   command was found to match the input string. - VCMDERR_INVALIDMODE: No site exists, the site does
    *   not support this attribute, or the voice command object is already registered with a site. -
    *   VCMDERR_MENUDOESNOTEXIST: The requested menu does not exist in the database. - VCMDERR_OUTOFMEM:
    *   There is no more memory. - VCMDERR_VALUEOUTOFRANGE: The value is out of range.
    *
    * CmdMimic parses the command string and eliminates white space and punctuation, then compares the
    * result with each command on the voice menu until it finds a match. The comparison is
    * case-insensitive, and the command string can include phrases from lists. If the string matches a
    * command in the voice menu, it is recognized; otherwise, the method returns an error.
    *
    * The VCMDERR_MENUDOESNOTEXIST error is returned if the menu does not exist or is not active.
    *
    * An application can call CmdMimic to play back voice macros to another application, similar to
    * playing back keystrokes and mouse messages in Windows.
    *
    * The voice menu must be active before an application can mimic its commands.
    */
   STDMETHOD (CmdMimic)       (THIS_ PVCMDNAMEW, PCWSTR) PURE;
};

typedef IVoiceCmdW FAR * PIVOICECMDW;


#undef   INTERFACE
#define  INTERFACE   IVoiceCmdA

// {C63A2B30-5543-11b9-C000-5611722E1D15}
DEFINE_GUID(IID_IVoiceCmdA, 0xc63a2b30, 0x5543, 0x11b9, 0xc0, 0x0, 0x56, 0x11, 0x72, 0x2e, 0x1d, 0x15);

/**
 * This interface registers an application with a voice command object. It is also used for tasks
 * such as creating menus and menu enumerators.
 *
 * This interface is supported by all voice command objects.
 */
DECLARE_INTERFACE_ (IVoiceCmdA, IUnknown) {
   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // IVoiceCmd members
   /**
    * This method is called by an application to register to use voice commands on a site.
    *
    * @param pszSite Ignored, because there is only one site: "Local PC."
    * @param pNotifyInterface [in] Pointer to the notification interface that receives notifications
    *   from the voice command object. The interface identifier is specified by IIDNotifyInterface. If
    *   this parameter is NULL, no notifications are sent. Because passing the pointer to the voice
    *   command object does not transfer ownership of the notification interface, the voice command
    *   object must call the AddRef method of the notification interface before returning from the call
    *   to Register. The voice command object must also call the Release method of the notification
    *   interface when it closes. The calling application must release any reference counts it holds on
    *   the notification interface after calling Register, unless it needs the notification object to be
    *   valid when the voice command object releases it.
    * @param IIDNotifyInterface [in] Interface identifier (IID) that uniquely identifies the type of
    *   notification sink being passed to the voice command object. It must be IID_IVCmdNotifySinkW.
    * @param dwFlags [in] Specifies whether the application is to receive all notifications. It is one
    *   of the following flags: - VCMDRF_ALLBUTVUMETER: Sends all but VUMeter notifications to
    *   pNotifyInterface. - VCMDRF_NOMESSAGES: Does not send notifications. - VCMDRF_CMDOTHER: Sends
    *   CommandOther notifications to pNotifyInterface. - VCMDRF_CMDSTART: Sends CommandStart
    *   notifications to pNotifyInterface. - VCMDRF_ATTRIBCHANGE: Sends AttribChanged notifications to
    *   pNotifyInterface. - VCMDRF_CMDRECOG: Sends CommandRecognize notifications to pNotifyInterface.
    * @param pSiteInfo [in] Pointer to a VCSITEINFO structure that contains settings to apply to the
    *   site, such as the speaker, confidence threshold, and speech-recognition mode. The settings are
    *   applied even if the site is already open. If this parameter is NULL, the voice command object
    *   uses the settings from the registry. If there are no registry settings, it uses the default
    *   settings, typically those for the computer. Telephony applications pass this information to
    *   ensure that the proper settings are selected. Other applications set this parameter to NULL to
    *   leave the site settings unchanged from previous values.
    *
    * @return - NOERROR: The method successfully registered to use voice commands on a site. -
    *   E_INVALIDARG: The argument is invalid. - VCMDERR_CANTCREATEAUDIODEVICE: An audio source object
    *   cannot be created for speech recognition. - VCMDERR_CANTCREATESRENUM: A speech recognition
    *   enumerator object cannot be created. - VCMDERR_CANTSELECTENGINE: A speech recognition engine
    *   cannot be selected. - VCMDERR_CANTSETDEVICE: The device identifier cannot be set into the audio
    *   source object. - VCMDERR_INVALIDMODE: No site exists, the site does not support this attribute,
    *   or the voice command object is already registered with a site. - VCMDERR_NOFINDINTERFACE: The
    *   speech recognition enumerator interface does not have a Find interface. - VCMDERR_NOSITEINFO:
    *   Information to open this site is not available. - VCMDERR_OUTOFMEM: There is no more memory. -
    *   VCMDERR_SRFINDFAILED: The speech recognition object could not find an appropriate mode. -
    *   VCMDERR_VALUEOUTOFRANGE: The value is out of range.
    *
    * An application cannot call Register a second time for the same voice command object. If a voice
    * command object is already registered, calling Register returns an error. To change sites, the
    * application must call the CoCreateInstance function to create a new voice command object for the
    * desired site.
    */
   STDMETHOD (Register)       (THIS_ PCSTR, PIVCMDNOTIFYSINK, GUID, DWORD,
                                     PVCSITEINFOA) PURE;
   /**
    * This method creates a voice menu enumerator to enumerate menus in the voice menu database.
    *
    * @param dwFlags [in] Specifies whether to enumerate active menus or open menus, which have voice
    *   menu objects, but may or may not be active. It is a combination of some of the following flags: -
    *   VCMDEF_ACTIVE: Enumerates only active menus. - VCMDEF_DATABASE: Enumerates all menus in the voice
    *   menu database. - VCMDEF_PERMANENT: Enumerates only permanent menus. - VCMDEF_SELECTED: Enumerates
    *   open menus, whether or not they are also active. - VCMDEF_TEMPORARY: Enumerates only temporary
    *   menus. VCMDEF_ACTIVE and VCMDEF_SELECTED are mutually exclusive, as are VCMDEF_TEMPORARY and
    *   VCMDEF_PERMANENT. If both VCMDEF_ACTIVE and VCMDEF_SELECTED are specified, the method returns an
    *   error. VCMDEF_TEMPORARY and VCMDEF_PERMANENT are ignored if neither VCMDEF_ACTIVE nor
    *   VCMDEF_SELECTED are specified. In other words, these flags do not apply if you want to enumerate
    *   the menus in the database. By definition, if a menu is active, it is selected.
    * @param pszApplicationFilter [in] Pointer to the null-terminated string that contains the name of
    *   the application whose menus are enumerated. This name is the same as that in the szApplication
    *   member of the VCMDNAME structure passed to the IVoiceCmd::MenuCreate method. If this parameter is
    *   NULL, menus for all applications, except those eliminated by dwFlags and pszStateFilter, are
    *   enumerated.
    * @param pszStateFilter [in] Pointer to a null-terminated string that contains the name of the
    *   state whose menus are enumerated. This state is the same as that in the szState member of the
    *   VCMDNAME structure passed to MenuCreate. If this parameter is NULL, menus for all applications,
    *   except those eliminated by dwFlags and pszApplicationFilter, are enumerated.
    * @param ppiVCmdEnum [out] Pointer to a variable that receives a pointer to an IVCmdEnum interface
    *   for the newly created voice menu enumerator. If an error occurs, this parameter receives NULL.
    *
    * @return - NOERROR: The method successfully created a voice menu enumerator. - E_INVALIDARG: The
    *   argument is invalid. - VCMDERR_INVALIDMODE: No site exists, the site does not support this
    *   attribute, or the voice command object is already registered with a site. -
    *   VCMDERR_MENUDOESNOTEXIST: The requested menu does not exist in the database. - VCMDERR_OUTOFMEM:
    *   There is no more memory. - VCMDERR_VALUEOUTOFRANGE: The value is out of range.
    *
    * An application can use a voice menu enumerator to find and modify unknown menus or to show menu
    * status to the user.
    *
    * The voice menu enumerator persists until all references to it are released, even if the voice
    * command object is released.
    */
   STDMETHOD (MenuEnum)       (THIS_ DWORD, PCSTR, PCSTR, PIVCMDENUMA *) PURE;
   /**
    * This method creates a voice menu object to represent a new or existing voice menu for an
    * application.
    *
    * @param pName [in] Pointer to a VCMDNAME structure that identifies the menu to create. The
    *   VCMDNAME structure contains an application name, such as "Radio," and a state name, such as "main
    *   form."
    * @param pLanguage [in] Pointer to a LANGUAGE structure that indicates the language to use for the
    *   menu. If this parameter is NULL, the default language for the site's speech-recognition mode is
    *   used.
    * @param dwFlags [in] Specifies how to create the menu. It is one of the following flags: -
    *   VCMDMC_CREATE_ALWAYS: Creates an empty menu with the specified name. If a menu by that name
    *   already exists in the voice menu database, it is erased. For Microsoft Windows CE for the Auto
    *   PC, the voice menu is removed from the database when the menu is released. - VCMDMC_CREATE_NEW:
    *   Creates an empty menu with the specified name. If a menu by that name already exists in the voice
    *   menu database, the method returns an error. The new menu is stored in the database when the menu
    *   object is released. - VCMDMC_CREATE_TEMP: Creates an empty menu with the specified name. If a
    *   menu by that name already exists in the voice menu database, the method returns an error. The new
    *   menu is temporary and is discarded when the menu object is released. - VCMDMC_OPEN_ALWAYS: Opens
    *   an existing menu with the specified name. If the menu does not exist, the method creates a new,
    *   empty menu. The new menu is stored in the database when the menu object is released.
    * @param ppIVCmdMenu [out] Pointer to an IVCmdMenu interface for the newly created voice menu
    *   object. The application uses the pointer to this interface to call IVCmdMenu methods on the voice
    *   menu object. If an error occurs, this parameter receives NULL.
    *
    * @return - NOERROR: The method successfully created a voice menu object. - E_INVALIDARG: The
    *   argument is invalid. - VCMDERR_CANTCREATESTORAGE: Space cannot be created in the database for the
    *   menu. - VCMDERR_MENUDOESNOTEXIST: The requested menu does not exist in the database. -
    *   VCMDERR_MENUEXIST: The requested new or temporary menu already exists in the database. -
    *   VCMDERR_OUTOFDISK: No disk space is left to write information. - VCMDERR_OUTOFMEM: There is no
    *   more memory. - VCMDERR_VALUEOUTOFRANGE: The value is out of range.
    *
    * An application can create a voice menu object by loading an existing voice menu from the voice
    * menu database or creating a new voice menu. A voice menu does not need to be stored in the
    * database; an application can create a temporary voice menu by setting dwFlags to the
    * VCMDMC_CREATE_TEMP value. A temporary voice menu persists until the menu object is released.
    *
    * An application can create more than one voice menu object to represent the same menu-either one
    * of its own menus or a menu for another application. For example, one application might do this to
    * enumerate another application's menus.
    *
    * More than one application can use the same voice menu object. For example, Application A might
    * call the IVoiceCmd::CmdMimic method on a voice menu object that represents a menu for Application
    * B, while Application B uses the same menu object to recognize commands spoken by the user.
    *
    * For the Auto PC, developers should use IApcSpeech::CreateVMenu to create a voice menu instead.
    */
   STDMETHOD (MenuCreate)     (THIS_ PVCMDNAMEA, PLANGUAGEA, DWORD,
                                     PIVCMDMENU *) PURE;
   /**
    * This method deletes a menu from the voice menu database.
    *
    * @param pName [in] Pointer to a VCMDNAME structure that identifies the menu to delete.
    *
    * @return - NOERROR: The method successfully deleted the menu. - E_INVALIDARG: The argument is
    *   invalid. - VCMDERR_MENUACTIVE: The menu is currently active and cannot be deleted. -
    *   VCMDERR_MENUDOESNOTEXIST: The requested menu does not exist in the database. - VCMDERR_MENUOPEN:
    *   The menu exists but has not been released, so it cannot be deleted. - VCMDERR_OUTOFMEM: There is
    *   no more memory.
    *
    * A menu cannot be deleted if it is currently open and the application is actively listening for
    * its commands.
    *
    * This method deletes the storage in the database for the menu, if the menu exists, and releases
    * the voice menu object that was created by the IVoiceCmd::MenuCreate method. After a menu is
    * deleted, the pointer to its IVCmdMenu interface is invalid, so set it to NULL.
    */
   STDMETHOD (MenuDelete)     (THIS_ PVCMDNAMEA) PURE;
   /**
    * This method supplies a voice-aware application with the equivalent of a spoken voice command.
    *
    * @param pMenu [in] Pointer to a VCMDNAME structure identifying the menu that contains the command
    *   to mimic.
    * @param pszCommand [in] Pointer to the null-terminated string that contains the command to mimic.
    *
    * @return - NOERROR: The method successfully supplied a voice-aware application with the equivalent
    *   of a spoken voice command. - E_INVALIDARG: The argument is invalid. - VCMDERR_CANNOTMIMIC: No
    *   command was found to match the input string. - VCMDERR_INVALIDMODE: No site exists, the site does
    *   not support this attribute, or the voice command object is already registered with a site. -
    *   VCMDERR_MENUDOESNOTEXIST: The requested menu does not exist in the database. - VCMDERR_OUTOFMEM:
    *   There is no more memory. - VCMDERR_VALUEOUTOFRANGE: The value is out of range.
    *
    * CmdMimic parses the command string and eliminates white space and punctuation, then compares the
    * result with each command on the voice menu until it finds a match. The comparison is
    * case-insensitive, and the command string can include phrases from lists. If the string matches a
    * command in the voice menu, it is recognized; otherwise, the method returns an error.
    *
    * The VCMDERR_MENUDOESNOTEXIST error is returned if the menu does not exist or is not active.
    *
    * An application can call CmdMimic to play back voice macros to another application, similar to
    * playing back keystrokes and mouse messages in Windows.
    *
    * The voice menu must be active before an application can mimic its commands.
    */
   STDMETHOD (CmdMimic)       (THIS_ PVCMDNAMEA, PCSTR) PURE;
};

typedef IVoiceCmdA FAR * PIVOICECMDA;


#ifdef _S_UNICODE
 /**
  * This interface registers an application with a voice command object. It is also used for tasks
  * such as creating menus and menu enumerators.
  *
  * This interface is supported by all voice command objects.
  */
 #define IVoiceCmd      IVoiceCmdW
 #define IID_IVoiceCmd  IID_IVoiceCmdW
 #define PIVOICECMD     PIVOICECMDW

#else
 /**
  * This interface registers an application with a voice command object. It is also used for tasks
  * such as creating menus and menu enumerators.
  *
  * This interface is supported by all voice command objects.
  */
 #define IVoiceCmd      IVoiceCmdA
 #define IID_IVoiceCmd  IID_IVoiceCmdA
 #define PIVOICECMD     PIVOICECMDA

#endif //_S_UNICODE



/*
 *  IVCmdAttributes
 */
#undef   INTERFACE
#define  INTERFACE   IVCmdAttributesW

DEFINE_GUID(IID_IVCmdAttributesW, 0xE5F24680L, 0x6053, 0x101B, 0x99, 0x26, 0x00, 0xAA, 0x00, 0x3C, 0xFC, 0x2C);

/**
 * This interface provides methods to set various attributes of the voice command object, including
 * audio output, recognition mode, and whether or not recognition is enabled.
 *
 * This interface is supported by all voice command objects.
 */
DECLARE_INTERFACE_ (IVCmdAttributesW, IUnknown) {
   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // IVCmdAttributes members
   STDMETHOD (AutoGainEnableGet) (THIS_ DWORD *) PURE;
   STDMETHOD (AutoGainEnableSet) (THIS_ DWORD) PURE;
   /**
    * This method retrieves the awake state for a voice command site.
    *
    * @param pdwAwake [out] Pointer to a DWORD that receives the current state of speech recognition
    *   for the site. Set to TRUE if the site is awake, or to FALSE if it is asleep.
    *
    * @return - NOERROR: The method successfully retrieved the awake state for a voice command site. -
    *   E_INVALIDARG: The argument is invalid. - VCMDERR_INVALIDMODE: No site exists, the site does not
    *   support this attribute, or the voice command object is already registered with a site. -
    *   VCMDERR_OUTOFMEM: There is no more memory. - VCMDERR_VALUEOUTOFRANGE: The value is out of range.
    *
    * When the site is awake, it listens for commands from any active voice menu for the active
    * application. When the site is asleep, it listens for commands only from sleep menus-those that
    * were activated with the dwFlags parameter of the IVCmdMenu::Activate method set to
    * VWGFLAG_ASLEEP. Commands from such menus become active only when the site is asleep, and they
    * become inactive when the site is awake. A sleep menu typically contains at least a "Wake up"
    * command that resumes speech recognition.
    */
   STDMETHOD (AwakeStateGet)     (THIS_ DWORD *) PURE;
   /**
    * This method sets the awake state for a voice command site.
    *
    * @param dwAwake [in] Specifies whether the awake state of the voice command site. Set to TRUE to
    *   cause the site to wake up, or to FALSE to cause it to go to sleep.
    *
    * @return - NOERROR: The method successfully set the awake state for a voice command site. -
    *   E_INVALIDARG: The argument is invalid. - VCMDERR_INVALIDMODE: No site exists, the site does not
    *   support this attribute, or the voice command object is already registered with a site. -
    *   VCMDERR_OUTOFMEM: There is no more memory. - VCMDERR_VALUEOUTOFRANGE: The value is out of range.
    *
    * If a voice navigation application is installed on the user's computer, suspending speech
    * recognition by using AwakeStateSet typically causes the voice navigation application to activate
    * a "wake up" menu.
    *
    * Calling AwakeStateSet allows the user to temporarily suspend speech recognition for a site. For
    * example, the user might want to suspend speech recognition from the computer microphone during a
    * telephone conversation and resume recognition when the conversation is finished. The user resumes
    * recognition by speaking an appropriate command from a sleep menu-for example, "Wake up."
    *
    * The sleep state for a site is saved between uses of the site, even if the user shuts down the
    * computer in the meantime.
    *
    * If a voice navigation application is installed on the user's computer, an application may not
    * need to set the sleep state. However, it may call this method to verify that speech recognition
    * is awake. For example, if an application asks-using with voice text or text-to-speech-"Do you
    * want to print the document?" it might enable and wake up speech recognition for the site to
    * receive the user's reply. The application should then restore speech recognition to its previous
    * state.
    */
   STDMETHOD (AwakeStateSet)     (THIS_ DWORD) PURE;
   /**
    * This method gets the threshold level of the speech-recognition engine used by a voice command
    * site.
    *
    * @param pdwThreshold [out] Pointer to a DWORD that receives the threshold level.
    *
    * @return - NOERROR: The method successfully retrieved the threshold level of the
    *   speech-recognition engine. - E_INVALIDARG: The argument is invalid. - VCMDERR_INVALIDMODE: No
    *   site exists, the site does not support this attribute, or the voice command object is already
    *   registered with a site. - VCMDERR_NOTSUPPORTED: The function is not supported by the engine. -
    *   VCMDERR_OUTOFMEM: There is no more memory.
    *
    * The threshold level is a value from 0 to 100 that indicates the point below which an engine
    * rejects an utterance as unrecognized. A value of 0 indicates that the engine should match any
    * utterance to the closest phrase match. A value of 100 indicates that the engine should be
    * absolutely certain that an utterance is the recognized phrase. For example, suppose the engine is
    * expecting "What is the time?" If the threshold is 100 and the user mumbles "What'z tha time" or
    * has a cold, the command may not be recognized. However, if the threshold is too low and the user
    * says a similar-sounding phrase that is not being listened for, such as "What is mine?," the
    * engine may recognize it as "What is the time?"
    *
    * If the command spoken by the user is not close enough to what the speech-recognition engine
    * expects, the voice command object notifies the application that the command was not recognized by
    * calling IVCmdNotifySink::CommandOther with a NULL string.
    *
    * The threshold for a site is saved between uses of the site, even if the user shuts down the
    * computer in the meantime.
    */
   STDMETHOD (ThresholdGet)      (THIS_ DWORD *) PURE;
   /**
    * This method sets the threshold level for the speech-recognition engine used by a voice command
    * site.
    *
    * @param dwThreshold [in] Specifies the threshold level. An application can specify
    *   SRATTR_MINTHRESHOLD and SRATTR_MAXTHRESHOLD for minimum and maximum allowable values.
    *
    * @return - NOERROR: The method successfully set the threshold level for the speech-recognition
    *   engine. - E_INVALIDARG: The argument is invalid. - VCMDERR_INVALIDMODE: No site exists, the site
    *   does not support this attribute, or the voice command object is already registered with a site. -
    *   VCMDERR_NOTSUPPORTED: The function is not supported by the engine. - VCMDERR_OUTOFMEM: There is
    *   no more memory. - VCMDERR_VALUEOUTOFRANGE: The value is out of range.
    *
    * The threshold level is a value from 0 to 100 that indicates the point below which an utterance is
    * rejected as unrecognized. A threshold level of 0 indicates that the engine should match any
    * utterance to the closest phrase match. A value of 100 indicates that the engine should be
    * absolutely certain that an utterance is the recognized phrase. If the value is out of range for
    * the engine, an error is returned and the attribute is not changed.
    *
    * The threshold for a site is saved between uses of the site, even if the user shuts down the
    * computer in the meantime.
    *
    * If a voice navigation application is installed on the user's computer, an application may not
    * need to set the threshold.
    */
   STDMETHOD (ThresholdSet)      (THIS_ DWORD) PURE;
   STDMETHOD (DeviceGet)         (THIS_ DWORD *) PURE;
   STDMETHOD (DeviceSet)         (THIS_ DWORD) PURE;
   /**
    * This method gets whether speech recognition is enabled or disabled for a voice command site.
    *
    * @param dwEnabled [out] Specifies whether or not speech recognition is enabled. Set to TRUE if
    *   speech recognition is enabled for the site, or to FALSE if it is disabled.
    *
    * @return - NOERROR: The method successfully retrieved whether speech recognition is enabled or
    *   disabled. - E_INVALIDARG: The argument is invalid. - VCMDERR_INVALIDMODE: No site exists, the
    *   site does not support this attribute, or the voice command object is already registered with a
    *   site. - VCMDERR_OUTOFMEM: There is no more memory. - VCMDERR_VALUEOUTOFRANGE: The value is out of
    *   range.
    *
    * When speech recognition is disabled, the engine does not recognize any command from any menu,
    * whether speech recognition is awake or asleep or any menus are active. An application would use
    * the IVCmdAttributes::EnabledSet method to allow the user to turn speech recognition completely
    * off, as opposed to suspending speech recognition temporarily by putting the site to sleep.
    *
    * The enabled state for a site is saved between uses of the site, even if the user shuts down the
    * computer in the meantime.
    */
   STDMETHOD (EnabledGet)        (THIS_ DWORD *) PURE;
   /**
    * This method sets whether speech recognition is enabled or disabled for a voice command site.
    *
    * @param dwEnabled [out] Specifies whether or not speech recognition is enabled. Set to TRUE to
    *   enable speech recognition, or to FALSE to disable it.
    *
    * @return - NOERROR: The method successfully sets whether speech recognition is enabled or
    *   disabled. - E_INVALIDARG: The argument is invalid. - VCMDERR_INVALIDMODE: No site exists, the
    *   site does not support this attribute, or the voice command object is already registered with a
    *   site. - VCMDERR_OUTOFMEM: There is no more memory. - VCMDERR_VALUEOUTOFRANGE: The value is out of
    *   range.
    *
    * Calling EnabledSet allows the user to completely turn off speech recognition for a site so that
    * nothing is recognized, including commands on sleep menus. For example, the user might want to
    * disable speech recognition from the computer microphone during a meeting so that speech
    * recognition remains off, even if a particpant inadvertently speaks a command on a sleep menu.
    *
    * The enabled state for a site is saved between uses of the site, even if the user shuts down the
    * computer in the meantime.
    */
   STDMETHOD (EnabledSet)        (THIS_ DWORD) PURE;
   STDMETHOD (MicrophoneGet)     (THIS_ PWSTR, DWORD, DWORD *) PURE;
   STDMETHOD (MicrophoneSet)     (THIS_ PCWSTR) PURE;
   /**
    * This method gets the name of the current speaker for a voice command site.
    *
    * @param pszSpeaker [in/out] Pointer to a buffer that stores the null-terminated string that
    *   contains the name of the current speaker.
    * @param dwSize [in] Specifies, in bytes, the size of the buffer specified by pszSpeaker. If the
    *   buffer is too small, the member returns an error and fills pdwNeeded with the number of bytes
    *   needed to store the speaker string.
    * @param pdwNeeded [out] Pointer to a DWORD that receives the number of bytes needed for the
    *   speaker string.
    *
    * @return - NOERROR: The method successfully retrieved the name of the current speaker. -
    *   E_INVALIDARG: The argument is invalid. - VCMDERR_INVALIDMODE: No site exists, the site does not
    *   support this attribute, or the voice command object is already registered with a site. -
    *   VCMDERR_NOTSUPPORTED: The function is not supported by the engine. - VCMDERR_OUTOFMEM: There is
    *   no more memory. - VCMDERR_VALUEOUTOFRANGE: The value is out of range.
    *
    * Changing the speaker name unloads all training for the previous speaker and loads the training
    * for the new speaker. If no training exists for the new speaker, the application starts with
    * default training.
    *
    * The speaker name for a site is saved between uses of the site, even if the user shuts down the
    * computer in the meantime.
    */
   STDMETHOD (SpeakerGet)        (THIS_ PWSTR, DWORD, DWORD *) PURE;
   /**
    * This method sets the name of the current speaker for a voice command site.
    *
    * @param pszSpeaker [in] Pointer to the null-terminated string that contains the name of the
    *   speaker to set. If the speaker is unknown, this parameter can be an empty string.
    *
    * @return - NOERROR: The method successfully set the name of the current speaker . - E_INVALIDARG:
    *   The argument is invalid. - VCMDERR_INVALIDMODE: No site exists, the site does not support this
    *   attribute, or the voice command object is already registered with a site. - VCMDERR_NOTSUPPORTED:
    *   The function is not supported by the engine. - VCMDERR_OUTOFMEM: There is no more memory. -
    *   VCMDERR_VALUEOUTOFRANGE: The value is out of range.
    *
    * The speaker name for a site is saved between uses of the site, even if the user shuts down the
    * computer in the meantime.
    *
    * The speaker string is not case sensitive.
    *
    * If a voice navigation application is installed on the user's computer, an application may not
    * need to set the speaker name.
    */
   STDMETHOD (SpeakerSet)        (THIS_ PCWSTR) PURE;
   /**
    * This method gets the globally unique identifier (GUID) of the speech-recognition mode used for
    * the site.
    *
    * @param pgMode [out] Pointer to the variable that receives the GUID assigned to the
    *   speech-recognition mode.
    *
    * @return - NOERROR: The method successfully retrieved the GUID of the speech-recognition mode. -
    *   E_INVALIDARG: The argument is invalid. - VCMDERR_INVALIDMODE: No site exists, the site does not
    *   support this attribute, or the voice command object is already registered with a site. -
    *   VCMDERR_NOTSUPPORTED: The function is not supported by the engine. - VCMDERR_OUTOFMEM: There is
    *   no more memory.
    *
    * A speech-recognition engine typically provides an assortment of modes that it can use to
    * recognize speech in different languages or dialects. A voice command site uses a single
    * speech-recognition mode.
    *
    * The speech-recognition mode for a site is saved between uses of the site, even if the user shuts
    * down the computer in the meantime.
    *
    * For an Auto PC, there is usually only one speech recognition mode.
    */
   STDMETHOD (SRModeGet)         (THIS_ GUID *) PURE;
   /**
    * This method sets the speech-recognition mode used by a voice command site.
    *
    * @param gMode [in] Globally unique identifier (GUID) of the speech-recognition mode to set for the
    *   site. If the mode does not exist, an error is returned and the mode is not changed.
    *
    * @return - NOERROR: The method successfully set the speech-recognition mode. - E_INVALIDARG: The
    *   argument is invalid. - VCMDERR_INVALIDMODE: No site exists, the site does not support this
    *   attribute, or the voice command object is already registered with a site. - VCMDERR_NOTSUPPORTED:
    *   The function is not supported by the engine. - VCMDERR_OUTOFMEM: There is no more memory. -
    *   VCMDERR_VALUEOUTOFRANGE: The value is out of range.
    *
    * The speech-recognition mode for a site is saved between uses of the site, even if the user shuts
    * down the computer in the meantime.
    *
    * If a voice navigation application is installed on the user's computer, an application may not
    * need to set the speech-recognition mode.
    *
    * An application can use a speech-recognition enumerator to determine which speech-recognition
    * modes are available.
    *
    * For Auto PC, there is usually only one speech recognition mode.
    */
   STDMETHOD (SRModeSet)         (THIS_ GUID) PURE;
};

typedef IVCmdAttributesW FAR * PIVCMDATTRIBUTESW;


#undef   INTERFACE
#define  INTERFACE   IVCmdAttributesA

// {FFF5DF80-5544-11b9-C000-5611722E1D15}
DEFINE_GUID(IID_IVCmdAttributesA, 0xfff5df80, 0x5544, 0x11b9, 0xc0, 0x0, 0x56, 0x11, 0x72, 0x2e, 0x1d, 0x15);

/**
 * This interface provides methods to set various attributes of the voice command object, including
 * audio output, recognition mode, and whether or not recognition is enabled.
 *
 * This interface is supported by all voice command objects.
 */
DECLARE_INTERFACE_ (IVCmdAttributesA, IUnknown) {
   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // IVCmdAttributes members
   STDMETHOD (AutoGainEnableGet) (THIS_ DWORD *) PURE;
   STDMETHOD (AutoGainEnableSet) (THIS_ DWORD) PURE;
   /**
    * This method retrieves the awake state for a voice command site.
    *
    * @param pdwAwake [out] Pointer to a DWORD that receives the current state of speech recognition
    *   for the site. Set to TRUE if the site is awake, or to FALSE if it is asleep.
    *
    * @return - NOERROR: The method successfully retrieved the awake state for a voice command site. -
    *   E_INVALIDARG: The argument is invalid. - VCMDERR_INVALIDMODE: No site exists, the site does not
    *   support this attribute, or the voice command object is already registered with a site. -
    *   VCMDERR_OUTOFMEM: There is no more memory. - VCMDERR_VALUEOUTOFRANGE: The value is out of range.
    *
    * When the site is awake, it listens for commands from any active voice menu for the active
    * application. When the site is asleep, it listens for commands only from sleep menus-those that
    * were activated with the dwFlags parameter of the IVCmdMenu::Activate method set to
    * VWGFLAG_ASLEEP. Commands from such menus become active only when the site is asleep, and they
    * become inactive when the site is awake. A sleep menu typically contains at least a "Wake up"
    * command that resumes speech recognition.
    */
   STDMETHOD (AwakeStateGet)     (THIS_ DWORD *) PURE;
   /**
    * This method sets the awake state for a voice command site.
    *
    * @param dwAwake [in] Specifies whether the awake state of the voice command site. Set to TRUE to
    *   cause the site to wake up, or to FALSE to cause it to go to sleep.
    *
    * @return - NOERROR: The method successfully set the awake state for a voice command site. -
    *   E_INVALIDARG: The argument is invalid. - VCMDERR_INVALIDMODE: No site exists, the site does not
    *   support this attribute, or the voice command object is already registered with a site. -
    *   VCMDERR_OUTOFMEM: There is no more memory. - VCMDERR_VALUEOUTOFRANGE: The value is out of range.
    *
    * If a voice navigation application is installed on the user's computer, suspending speech
    * recognition by using AwakeStateSet typically causes the voice navigation application to activate
    * a "wake up" menu.
    *
    * Calling AwakeStateSet allows the user to temporarily suspend speech recognition for a site. For
    * example, the user might want to suspend speech recognition from the computer microphone during a
    * telephone conversation and resume recognition when the conversation is finished. The user resumes
    * recognition by speaking an appropriate command from a sleep menu-for example, "Wake up."
    *
    * The sleep state for a site is saved between uses of the site, even if the user shuts down the
    * computer in the meantime.
    *
    * If a voice navigation application is installed on the user's computer, an application may not
    * need to set the sleep state. However, it may call this method to verify that speech recognition
    * is awake. For example, if an application asks-using with voice text or text-to-speech-"Do you
    * want to print the document?" it might enable and wake up speech recognition for the site to
    * receive the user's reply. The application should then restore speech recognition to its previous
    * state.
    */
   STDMETHOD (AwakeStateSet)     (THIS_ DWORD) PURE;
   /**
    * This method gets the threshold level of the speech-recognition engine used by a voice command
    * site.
    *
    * @param pdwThreshold [out] Pointer to a DWORD that receives the threshold level.
    *
    * @return - NOERROR: The method successfully retrieved the threshold level of the
    *   speech-recognition engine. - E_INVALIDARG: The argument is invalid. - VCMDERR_INVALIDMODE: No
    *   site exists, the site does not support this attribute, or the voice command object is already
    *   registered with a site. - VCMDERR_NOTSUPPORTED: The function is not supported by the engine. -
    *   VCMDERR_OUTOFMEM: There is no more memory.
    *
    * The threshold level is a value from 0 to 100 that indicates the point below which an engine
    * rejects an utterance as unrecognized. A value of 0 indicates that the engine should match any
    * utterance to the closest phrase match. A value of 100 indicates that the engine should be
    * absolutely certain that an utterance is the recognized phrase. For example, suppose the engine is
    * expecting "What is the time?" If the threshold is 100 and the user mumbles "What'z tha time" or
    * has a cold, the command may not be recognized. However, if the threshold is too low and the user
    * says a similar-sounding phrase that is not being listened for, such as "What is mine?," the
    * engine may recognize it as "What is the time?"
    *
    * If the command spoken by the user is not close enough to what the speech-recognition engine
    * expects, the voice command object notifies the application that the command was not recognized by
    * calling IVCmdNotifySink::CommandOther with a NULL string.
    *
    * The threshold for a site is saved between uses of the site, even if the user shuts down the
    * computer in the meantime.
    */
   STDMETHOD (ThresholdGet)      (THIS_ DWORD *) PURE;
   /**
    * This method sets the threshold level for the speech-recognition engine used by a voice command
    * site.
    *
    * @param dwThreshold [in] Specifies the threshold level. An application can specify
    *   SRATTR_MINTHRESHOLD and SRATTR_MAXTHRESHOLD for minimum and maximum allowable values.
    *
    * @return - NOERROR: The method successfully set the threshold level for the speech-recognition
    *   engine. - E_INVALIDARG: The argument is invalid. - VCMDERR_INVALIDMODE: No site exists, the site
    *   does not support this attribute, or the voice command object is already registered with a site. -
    *   VCMDERR_NOTSUPPORTED: The function is not supported by the engine. - VCMDERR_OUTOFMEM: There is
    *   no more memory. - VCMDERR_VALUEOUTOFRANGE: The value is out of range.
    *
    * The threshold level is a value from 0 to 100 that indicates the point below which an utterance is
    * rejected as unrecognized. A threshold level of 0 indicates that the engine should match any
    * utterance to the closest phrase match. A value of 100 indicates that the engine should be
    * absolutely certain that an utterance is the recognized phrase. If the value is out of range for
    * the engine, an error is returned and the attribute is not changed.
    *
    * The threshold for a site is saved between uses of the site, even if the user shuts down the
    * computer in the meantime.
    *
    * If a voice navigation application is installed on the user's computer, an application may not
    * need to set the threshold.
    */
   STDMETHOD (ThresholdSet)      (THIS_ DWORD) PURE;
   STDMETHOD (DeviceGet)         (THIS_ DWORD *) PURE;
   STDMETHOD (DeviceSet)         (THIS_ DWORD) PURE;
   /**
    * This method gets whether speech recognition is enabled or disabled for a voice command site.
    *
    * @param dwEnabled [out] Specifies whether or not speech recognition is enabled. Set to TRUE if
    *   speech recognition is enabled for the site, or to FALSE if it is disabled.
    *
    * @return - NOERROR: The method successfully retrieved whether speech recognition is enabled or
    *   disabled. - E_INVALIDARG: The argument is invalid. - VCMDERR_INVALIDMODE: No site exists, the
    *   site does not support this attribute, or the voice command object is already registered with a
    *   site. - VCMDERR_OUTOFMEM: There is no more memory. - VCMDERR_VALUEOUTOFRANGE: The value is out of
    *   range.
    *
    * When speech recognition is disabled, the engine does not recognize any command from any menu,
    * whether speech recognition is awake or asleep or any menus are active. An application would use
    * the IVCmdAttributes::EnabledSet method to allow the user to turn speech recognition completely
    * off, as opposed to suspending speech recognition temporarily by putting the site to sleep.
    *
    * The enabled state for a site is saved between uses of the site, even if the user shuts down the
    * computer in the meantime.
    */
   STDMETHOD (EnabledGet)        (THIS_ DWORD *) PURE;
   /**
    * This method sets whether speech recognition is enabled or disabled for a voice command site.
    *
    * @param dwEnabled [out] Specifies whether or not speech recognition is enabled. Set to TRUE to
    *   enable speech recognition, or to FALSE to disable it.
    *
    * @return - NOERROR: The method successfully sets whether speech recognition is enabled or
    *   disabled. - E_INVALIDARG: The argument is invalid. - VCMDERR_INVALIDMODE: No site exists, the
    *   site does not support this attribute, or the voice command object is already registered with a
    *   site. - VCMDERR_OUTOFMEM: There is no more memory. - VCMDERR_VALUEOUTOFRANGE: The value is out of
    *   range.
    *
    * Calling EnabledSet allows the user to completely turn off speech recognition for a site so that
    * nothing is recognized, including commands on sleep menus. For example, the user might want to
    * disable speech recognition from the computer microphone during a meeting so that speech
    * recognition remains off, even if a particpant inadvertently speaks a command on a sleep menu.
    *
    * The enabled state for a site is saved between uses of the site, even if the user shuts down the
    * computer in the meantime.
    */
   STDMETHOD (EnabledSet)        (THIS_ DWORD) PURE;
   STDMETHOD (MicrophoneGet)     (THIS_ PSTR, DWORD, DWORD *) PURE;
   STDMETHOD (MicrophoneSet)     (THIS_ PCSTR) PURE;
   /**
    * This method gets the name of the current speaker for a voice command site.
    *
    * @param pszSpeaker [in/out] Pointer to a buffer that stores the null-terminated string that
    *   contains the name of the current speaker.
    * @param dwSize [in] Specifies, in bytes, the size of the buffer specified by pszSpeaker. If the
    *   buffer is too small, the member returns an error and fills pdwNeeded with the number of bytes
    *   needed to store the speaker string.
    * @param pdwNeeded [out] Pointer to a DWORD that receives the number of bytes needed for the
    *   speaker string.
    *
    * @return - NOERROR: The method successfully retrieved the name of the current speaker. -
    *   E_INVALIDARG: The argument is invalid. - VCMDERR_INVALIDMODE: No site exists, the site does not
    *   support this attribute, or the voice command object is already registered with a site. -
    *   VCMDERR_NOTSUPPORTED: The function is not supported by the engine. - VCMDERR_OUTOFMEM: There is
    *   no more memory. - VCMDERR_VALUEOUTOFRANGE: The value is out of range.
    *
    * Changing the speaker name unloads all training for the previous speaker and loads the training
    * for the new speaker. If no training exists for the new speaker, the application starts with
    * default training.
    *
    * The speaker name for a site is saved between uses of the site, even if the user shuts down the
    * computer in the meantime.
    */
   STDMETHOD (SpeakerGet)        (THIS_ PSTR, DWORD, DWORD *) PURE;
   /**
    * This method sets the name of the current speaker for a voice command site.
    *
    * @param pszSpeaker [in] Pointer to the null-terminated string that contains the name of the
    *   speaker to set. If the speaker is unknown, this parameter can be an empty string.
    *
    * @return - NOERROR: The method successfully set the name of the current speaker . - E_INVALIDARG:
    *   The argument is invalid. - VCMDERR_INVALIDMODE: No site exists, the site does not support this
    *   attribute, or the voice command object is already registered with a site. - VCMDERR_NOTSUPPORTED:
    *   The function is not supported by the engine. - VCMDERR_OUTOFMEM: There is no more memory. -
    *   VCMDERR_VALUEOUTOFRANGE: The value is out of range.
    *
    * The speaker name for a site is saved between uses of the site, even if the user shuts down the
    * computer in the meantime.
    *
    * The speaker string is not case sensitive.
    *
    * If a voice navigation application is installed on the user's computer, an application may not
    * need to set the speaker name.
    */
   STDMETHOD (SpeakerSet)        (THIS_ PCSTR) PURE;
   /**
    * This method gets the globally unique identifier (GUID) of the speech-recognition mode used for
    * the site.
    *
    * @param pgMode [out] Pointer to the variable that receives the GUID assigned to the
    *   speech-recognition mode.
    *
    * @return - NOERROR: The method successfully retrieved the GUID of the speech-recognition mode. -
    *   E_INVALIDARG: The argument is invalid. - VCMDERR_INVALIDMODE: No site exists, the site does not
    *   support this attribute, or the voice command object is already registered with a site. -
    *   VCMDERR_NOTSUPPORTED: The function is not supported by the engine. - VCMDERR_OUTOFMEM: There is
    *   no more memory.
    *
    * A speech-recognition engine typically provides an assortment of modes that it can use to
    * recognize speech in different languages or dialects. A voice command site uses a single
    * speech-recognition mode.
    *
    * The speech-recognition mode for a site is saved between uses of the site, even if the user shuts
    * down the computer in the meantime.
    *
    * For an Auto PC, there is usually only one speech recognition mode.
    */
   STDMETHOD (SRModeGet)         (THIS_ GUID *) PURE;
   /**
    * This method sets the speech-recognition mode used by a voice command site.
    *
    * @param gMode [in] Globally unique identifier (GUID) of the speech-recognition mode to set for the
    *   site. If the mode does not exist, an error is returned and the mode is not changed.
    *
    * @return - NOERROR: The method successfully set the speech-recognition mode. - E_INVALIDARG: The
    *   argument is invalid. - VCMDERR_INVALIDMODE: No site exists, the site does not support this
    *   attribute, or the voice command object is already registered with a site. - VCMDERR_NOTSUPPORTED:
    *   The function is not supported by the engine. - VCMDERR_OUTOFMEM: There is no more memory. -
    *   VCMDERR_VALUEOUTOFRANGE: The value is out of range.
    *
    * The speech-recognition mode for a site is saved between uses of the site, even if the user shuts
    * down the computer in the meantime.
    *
    * If a voice navigation application is installed on the user's computer, an application may not
    * need to set the speech-recognition mode.
    *
    * An application can use a speech-recognition enumerator to determine which speech-recognition
    * modes are available.
    *
    * For Auto PC, there is usually only one speech recognition mode.
    */
   STDMETHOD (SRModeSet)         (THIS_ GUID) PURE;
};

typedef IVCmdAttributesA FAR * PIVCMDATTRIBUTESA;


#ifdef _S_UNICODE
 /**
  * This interface provides methods to set various attributes of the voice command object, including
  * audio output, recognition mode, and whether or not recognition is enabled.
  *
  * This interface is supported by all voice command objects.
  */
 #define IVCmdAttributes        IVCmdAttributesW
 #define IID_IVCmdAttributes    IID_IVCmdAttributesW
 #define PIVCMDATTRIBUTES       PIVCMDATTRIBUTESW

#else
 /**
  * This interface provides methods to set various attributes of the voice command object, including
  * audio output, recognition mode, and whether or not recognition is enabled.
  *
  * This interface is supported by all voice command objects.
  */
 #define IVCmdAttributes        IVCmdAttributesA
 #define IID_IVCmdAttributes    IID_IVCmdAttributesA
 #define PIVCMDATTRIBUTES       PIVCMDATTRIBUTESA

#endif // _S_UNICODE



/*
 *  IVCmdDialog
 */
#undef   INTERFACE
#define  INTERFACE   IVCmdDialogsW

DEFINE_GUID(IID_IVCmdDialogsW, 0xEE39B8A0L, 0x6053, 0x101B, 0x99, 0x26, 0x00, 0xAA, 0x00, 0x3C, 0xFC, 0x2C);

DECLARE_INTERFACE_ (IVCmdDialogsW, IUnknown) {
   // IUnknown members
   STDMETHOD(QueryInterface)    (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)     (THIS) PURE;
   STDMETHOD_(ULONG,Release)    (THIS) PURE;

   // IVCmdDialogs members
   STDMETHOD (AboutDlg)         (THIS_ HWND, PCWSTR) PURE;
   STDMETHOD (GeneralDlg)       (THIS_ HWND, PCWSTR) PURE;
   STDMETHOD (LexiconDlg)       (THIS_ HWND, PCWSTR) PURE;
   STDMETHOD (TrainGeneralDlg)  (THIS_ HWND, PCWSTR) PURE;
   STDMETHOD (TrainMicDlg)      (THIS_ HWND, PCWSTR) PURE;
};

typedef IVCmdDialogsW FAR * PIVCMDDIALOGSW;


#undef   INTERFACE
#define  INTERFACE   IVCmdDialogsA

// {AA8FE260-5545-11b9-C000-5611722E1D15}
DEFINE_GUID(IID_IVCmdDialogsA, 0xaa8fe260, 0x5545, 0x11b9, 0xc0, 0x0, 0x56, 0x11, 0x72, 0x2e, 0x1d, 0x15);

DECLARE_INTERFACE_ (IVCmdDialogsA, IUnknown) {
   // IUnknown members
   STDMETHOD(QueryInterface)    (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)     (THIS) PURE;
   STDMETHOD_(ULONG,Release)    (THIS) PURE;

   // IVCmdDialogs members
   STDMETHOD (AboutDlg)         (THIS_ HWND, PCSTR) PURE;
   STDMETHOD (GeneralDlg)       (THIS_ HWND, PCSTR) PURE;
   STDMETHOD (LexiconDlg)       (THIS_ HWND, PCSTR) PURE;
   STDMETHOD (TrainGeneralDlg)  (THIS_ HWND, PCSTR) PURE;
   STDMETHOD (TrainMicDlg)      (THIS_ HWND, PCSTR) PURE;
};

typedef IVCmdDialogsA FAR * PIVCMDDIALOGSA;


#ifdef _S_UNICODE
 #define IVCmdDialogs       IVCmdDialogsW
 #define IID_IVCmdDialogs   IID_IVCmdDialogsW
 #define PIVCMDDIALOGS      PIVCMDDIALOGSW

#else
 #define IVCmdDialogs       IVCmdDialogsA
 #define IID_IVCmdDialogs   IID_IVCmdDialogsA
 #define PIVCMDDIALOGS      PIVCMDDIALOGSA

#endif // _S_UNICODE



/************************************************************************
class guids */

// DEFINE_GUID(CLSID_VCmd, 0x93898800L, 0x604D, 0x101B, 0x99, 0x26, 0x00, 0xAA, 0x00, 0x3C, 0xFC, 0x2C);
// {6D40D820-0BA7-11ce-A166-00AA004CD65C}
DEFINE_GUID(CLSID_VCmd, 
0x6d40d820, 0xba7, 0x11ce, 0xa1, 0x66, 0x0, 0xaa, 0x0, 0x4c, 0xd6, 0x5c);
// {89F70C30-8636-11ce-B763-00AA004CD65C}
DEFINE_GUID(CLSID_SRShare, 
0x89f70c30, 0x8636, 0x11ce, 0xb7, 0x63, 0x0, 0xaa, 0x0, 0x4c, 0xd6, 0x5c);



/************************************************************************
High-Level text-to-speech API
*/


/************************************************************************
defines */

#define  ONE                    (1)

// dwFlags parameter of IVoiceText::Register
#define  VTXTF_ALLMESSAGES      (ONE<<0)

#define  VTXTF_SPEAK            0x00001001
#define  VTXTF_SPEAKDONE        0x00002001
#define  VTXTF_SPEAKSTOP        0x00004001
#define  VTXTF_SPEAKSTART       0x00008001

/*
 *   dwFlags parameter of IVoiceText::Speak
 */

// type of speech
#define  VTXTST_STATEMENT       0x00000001
#define  VTXTST_QUESTION        0x00000002
#define  VTXTST_COMMAND         0x00000004
#define  VTXTST_WARNING         0x00000008
#define  VTXTST_READING         0x00000010
#define  VTXTST_NUMBERS         0x00000020
#define  VTXTST_SPREADSHEET     0x00000040

// priorities
#define  VTXTSP_VERYHIGH        0x00000080
#define  VTXTSP_HIGH            0x00000100
#define  VTXTSP_NORMAL          0x00000200

/************************************************************************
typedefs */

// possible parameter to IVoiceText::Register
/**
 * This structure specifies an audio device, a text-to-speech (TTS) mode, and the talking speed for
 * a voice text site, and indicates whether voice text is enabled or disabled for the voice text
 * site.
 *
 * An application can specify the address of a VTSITEINFO structure in a call to the
 * IVoiceText::Register method to set the voice, speaking speed, and other attributes of a
 * voice-text site, even if the site is already open. Telephony applications typically do this to
 * ensure that the proper information is selected for the site.
 */
typedef struct {
    /**
     * Specifies the device identifier of the WAV output audio device to be used by the site. The device
     * identifier can be obtained by calling the waveOutGetNumDevs and waveOutGetDevCaps multimedia
     * functions.
     */
    DWORD   dwDevice;
    /**
     * Specifies whether voice text is enabled. TRUE indicates that voice text is enabled for the site;
     * FALSE indicates it is disabled.
     */
    DWORD   dwEnable;
    /**
     * Specifies a baseline average talking speed, in words per minute, for the text-to-speech mode to
     * be used by the site.
     */
    DWORD   dwSpeed;
    /**
     * Globally unique identifier (GUID) of the text-to-speech mode to be used by the site. The GUID for
     * a text-to-speech mode is obtained from a text-to-speech enumerator object.
     */
    GUID    gModeID;
} VTSITEINFO, *PVTSITEINFO;


/************************************************************************
interfaces */

/*
 *  IVCmdNotifySink
 */
#undef   INTERFACE
#define  INTERFACE   IVTxtNotifySinkW

// {FD3A2430-E090-11cd-A166-00AA004CD65C}
DEFINE_GUID(IID_IVTxtNotifySinkW, 0xfd3a2430, 0xe090, 0x11cd, 0xa1, 0x66, 0x0, 0xaa, 0x0, 0x4c, 0xd6, 0x5c);

/**
 * This interface notifies an application of the status of the object.
 */
DECLARE_INTERFACE_ (IVTxtNotifySinkW, IUnknown) {

   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // IVTxtNotifySinkW members
   STDMETHOD (AttribChanged)    (THIS_ DWORD) PURE;
   STDMETHOD (Visual)           (THIS_ WCHAR, WCHAR, DWORD, PTTSMOUTH) PURE;
   STDMETHOD (Speak)            (THIS_ PWSTR, PWSTR, DWORD) PURE;
   /**
    * This method notifies all applications on a voice text site that speaking has started.
    *
    * @return The return value is ignored.
    */
   STDMETHOD (SpeakingStarted)  (THIS) PURE;
   /**
    * This method notifies all applications on a voice text site that speaking is finished and no text
    * remains in the playback queue.
    *
    * @return The return value is ignored.
    */
   STDMETHOD (SpeakingDone)     (THIS) PURE;
};

typedef IVTxtNotifySinkW FAR * PIVTXTNOTIFYSINKW;


#undef   INTERFACE
#define  INTERFACE   IVTxtNotifySinkA

// {D2C840E0-E092-11cd-A166-00AA004CD65C}
DEFINE_GUID(IID_IVTxtNotifySinkA, 0xd2c840e0, 0xe092, 0x11cd, 0xa1, 0x66, 0x0, 0xaa, 0x0, 0x4c, 0xd6, 0x5c);

/**
 * This interface notifies an application of the status of the object.
 */
DECLARE_INTERFACE_ (IVTxtNotifySinkA, IUnknown) {

   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // IVTxtNotifySinkA members
   STDMETHOD (AttribChanged)    (THIS_ DWORD) PURE;
   STDMETHOD (Visual)           (THIS_ WCHAR, CHAR, DWORD, PTTSMOUTH) PURE;
   STDMETHOD (Speak)            (THIS_ PSTR, PSTR, DWORD) PURE;
   /**
    * This method notifies all applications on a voice text site that speaking has started.
    *
    * @return The return value is ignored.
    */
   STDMETHOD (SpeakingStarted)  (THIS) PURE;
   /**
    * This method notifies all applications on a voice text site that speaking is finished and no text
    * remains in the playback queue.
    *
    * @return The return value is ignored.
    */
   STDMETHOD (SpeakingDone)     (THIS) PURE;
};

typedef IVTxtNotifySinkA FAR * PIVTXTNOTIFYSINKA;


#ifdef _S_UNICODE
 /**
  * This interface notifies an application of the status of the object.
  */
 #define IVTxtNotifySink        IVTxtNotifySinkW
 #define IID_IVTxtNotifySink    IID_IVTxtNotifySinkW
 #define PIVTXTNOTIFYSINK       PIVTXTNOTIFYSINKW

#else
 /**
  * This interface notifies an application of the status of the object.
  */
 #define IVTxtNotifySink        IVTxtNotifySinkA
 #define IID_IVTxtNotifySink    IID_IVTxtNotifySinkA
 #define PIVTXTNOTIFYSINK       PIVTXTNOTIFYSINKA

#endif // _S_UNICODE



/*
 *  IVoiceText
 */
#undef   INTERFACE
#define  INTERFACE   IVoiceTextW

// {C4FE8740-E093-11cd-A166-00AA004CD65C}
DEFINE_GUID(IID_IVoiceTextW, 0xc4fe8740, 0xe093, 0x11cd, 0xa1, 0x66, 0x0, 0xaa, 0x0, 0x4c, 0xd6, 0x5c);

/**
 * This interface registers an application to use the voice text object, and controls playback of
 * text.
 */
DECLARE_INTERFACE_ (IVoiceTextW, IUnknown) {
    // IUnknown members
    STDMETHOD(QueryInterface)   (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)    (THIS) PURE;
    STDMETHOD_(ULONG,Release)   (THIS) PURE;

    // IVoiceText members

    /**
     * This method registers an application to use voice text on a site.
     *
     * @param pszSite Ignored because there is only one site, "Local PC."
     * @param pszApplication [in] Pointer to a null-terminated string that identifies the
     *   application-for example, "Radio." An application can use this information to display the source
     *   of text. This parameter must not be NULL.
     * @param pNotifyInterface [in] Pointer to the notification interface through which the voice text
     *   object notifies the application about text-to-speech information. If this parameter is NULL, no
     *   notifications are sent. The interface identifier is specified by the IIDNotifyInterface
     *   parameter. Because passing the pointer to the voice text object does not transfer ownership of
     *   the notification interface, the voice text object must call the AddRef method of the notification
     *   interface before returning from the call to Register. The voice text object must also call the
     *   Release method of the notification interface when it closes. The calling application must release
     *   any reference counts that the application holds on the notification interface after calling
     *   Register, unless the application needs the notification object to be valid when the voice text
     *   object releases notification interface.
     * @param IIDNotifyInterface [in] Interface identifier of the interface used for notification. For
     *   Auto PC, this parameter must be IID_IVTxtNotifySinkW.
     * @param dwFlags [in] Specifies whether the application is to receive all notifications. If this
     *   parameter is the VTXTF_ALLMESSAGES value, all notifications are sent to pNotifyInterface. The
     *   application can specify which notifications to receive by passing in the combination of the
     *   following values: VTXTF_SPEAKDONE VTXTF_SPEAKSTART
     * @param pSiteInfo [in] Pointer to a VTSITEINFO structure that contains settings to apply to the
     *   site, such as the voice and talking speed. The settings are applied, even if the site is already
     *   open. If a VTSITEINFO structure is not specified, the voice text object uses the settings from
     *   the registry. If there are no registry settings, it uses the default settings, typically those
     *   for the computer. Telephony applications pass this information to ensure that the proper settings
     *   are selected. Other applications set this parameter to NULL to leave the site settings unchanged.
     *
     * @return - NOERROR: The method successfully registered an application to use voice text on a site.
     *   - VTXTERR_INVALIDPARAM: A parameter is invalid. - VTXTERR_OUTOFMEM: There is not enough memory.
     *
     * An application must call Register before it can call other methods in the IVoiceText interface.
     *
     * An application cannot call Register a second time for the same voice text object. To change
     * sites, the application must call the CoCreateInstance function to create a new voice text object
     * for the desired site.
     */
    STDMETHOD (Register)         (THIS_ PCWSTR, PCWSTR, 
                                        PIVTXTNOTIFYSINK, GUID,
                                        DWORD, PVTSITEINFO) PURE;
    /**
     * This method starts playing the specified text.
     *
     * @param pszSpeak [in] Pointer to a buffer that contains the text to speak. The text is in the form
     *   of a null-terminated string. The length of the text string must be less than 2 kilobytes (KB).
     *   Strings longer than 2 KB cause unexpected speech behavior. An application can free or modify the
     *   buffer as soon as Speak returns. The string pointed to by this parameter can contain
     *   text-to-speech control tags. In Auto PC, this string can contain the TTS tags. For more
     *   information about tags, see Text-to-Speech Tags.
     * @param dwFlags [in] Specifies priority of the text. It is one of the following values: -
     *   VTXTSP_HIGH: Play the text as soon as possible, after text that is currently being spoken but
     *   before any other text in the playback queue. - VTXTSP_NORMAL: Add the text to the end of the
     *   playback queue. This is the default priority. - VTXTSP_VERYHIGH: Play the text immediately,
     *   interrupting text that is currently being spoken, if any. The interrupted text resumes playing as
     *   soon as the very high priority text is finished, although the interrupted text may not be
     *   correctly synchronized.
     * @param pszTags [in] Ignored.
     *
     * @return - NOERROR: The method successfully started playing the specified text. -
     *   VTXTERR_INVALIDMODE: The text-to-speech mode is invalid, or the application has not been
     *   registered to use the voice text on the site. - VTXTERR_INVALIDPARAM: A parameter is invalid. -
     *   VTXTERR_NOTENABLED: Voice text is not enabled. - VTXTERR_OUTOFMEM: There is not enough memory. -
     *   VTXTERR_QUEUEFULL: The playback queue is full. - VTXTERR_WAVEDEVICEBUSY: The wave device is busy.
     *
     * If an application calls the Speak method when other text is being played, the specified text is
     * added to the end of the playback queue, unless the application specifies a higher priorityfor the
     * new text in dwFlags.
     *
     * Calling Speak affects all applications using voice text on the site, because all applications
     * share the same playback queue.
     *
     * The type of speech specified by dwFlags is communicated to the text-to-speech engine though
     * control tags. Support of most control tags is optional; the engine ignores unsupported tags.
     */
    STDMETHOD (Speak)            (THIS_ PCWSTR, DWORD, PCWSTR) PURE;
    /**
     * This method halts text that is currently being spoken and flushes all pending text from the
     * playback queue.
     *
     * @return - NOERROR: The method successfully halted the text being spoken and flushed all pending
     *   text from the playback queue. - VTXTERR_INVALIDMODE: The text-to-speech mode is invalid, or the
     *   application has not been registered to use the voice text on the site. - VTXTERR_NOTENABLED:
     *   Voice text is not enabled. - VTXTERR_OUTOFMEM: There is not enough memory.
     *
     * Calling the StopSpeaking method affects all applications using voice text on the site, because
     * all applications share the same playback queue.
     */
    STDMETHOD (StopSpeaking)     (THIS) PURE;
    STDMETHOD (AudioFastForward) (THIS) PURE;
    /**
     * This method pauses text-to-speech output for a voice text site.
     *
     * @return - NOERROR: The method successfully paused the text-to-speech output. -
     *   VTXTERR_INVALIDMODE: The text-to-speech mode is invalid, or the application has not been
     *   registered to use the voice text on the site. - VTXTERR_NOTENABLED: Voice text is not enabled. -
     *   VTXTERR_OUTOFMEM: There is not enough memory.
     *
     * When a voice text object is first created, text-to-speech output is not paused. Because pausing
     * text-to-speech output affects all applications that use voice text on the site, an application
     * should resume text-to-speech output as soon as possible by calling the IVoiceText::AudioResume
     * method.
     *
     * When output has been paused, the IVTxtAttributes::IsSpeaking method returns FALSE, even though
     * the voice text object still has data available in its queue and has not yet sent a
     * IVTxtNotifySink::SpeakingDone notification.
     *
     * No notifications are sent when audio is paused or resumed.
     */
    STDMETHOD (AudioPause)       (THIS) PURE;
    /**
     * This method resumes text-to-speech output after it has been paused by the IVoiceText::AudioPause
     * method.
     *
     * @return - NOERROR: The method successfully resumed the text-to-speech output. -
     *   VTXTERR_INVALIDMODE: The text-to-speech mode is invalid, or the application has not been
     *   registered to use the voice text on the site. - VTXTERR_NOTENABLED: Voice text is not enabled. -
     *   VTXTERR_OUTOFMEM: There is not enough memory.
     *
     * The AudioResume method affects all applications using the site.
     */
    STDMETHOD (AudioResume)      (THIS) PURE;
    STDMETHOD (AudioRewind)      (THIS) PURE;
};

typedef IVoiceTextW FAR * PIVOICETEXTW;


#undef   INTERFACE
#define  INTERFACE   IVoiceTextA

// {E1B7A180-E093-11cd-A166-00AA004CD65C}
DEFINE_GUID(IID_IVoiceTextA, 0xe1b7a180, 0xe093, 0x11cd, 0xa1, 0x66, 0x0, 0xaa, 0x0, 0x4c, 0xd6, 0x5c);

/**
 * This interface registers an application to use the voice text object, and controls playback of
 * text.
 */
DECLARE_INTERFACE_ (IVoiceTextA, IUnknown) {
   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // IVoiceText members

    /**
     * This method registers an application to use voice text on a site.
     *
     * @param pszSite Ignored because there is only one site, "Local PC."
     * @param pszApplication [in] Pointer to a null-terminated string that identifies the
     *   application-for example, "Radio." An application can use this information to display the source
     *   of text. This parameter must not be NULL.
     * @param pNotifyInterface [in] Pointer to the notification interface through which the voice text
     *   object notifies the application about text-to-speech information. If this parameter is NULL, no
     *   notifications are sent. The interface identifier is specified by the IIDNotifyInterface
     *   parameter. Because passing the pointer to the voice text object does not transfer ownership of
     *   the notification interface, the voice text object must call the AddRef method of the notification
     *   interface before returning from the call to Register. The voice text object must also call the
     *   Release method of the notification interface when it closes. The calling application must release
     *   any reference counts that the application holds on the notification interface after calling
     *   Register, unless the application needs the notification object to be valid when the voice text
     *   object releases notification interface.
     * @param IIDNotifyInterface [in] Interface identifier of the interface used for notification. For
     *   Auto PC, this parameter must be IID_IVTxtNotifySinkW.
     * @param dwFlags [in] Specifies whether the application is to receive all notifications. If this
     *   parameter is the VTXTF_ALLMESSAGES value, all notifications are sent to pNotifyInterface. The
     *   application can specify which notifications to receive by passing in the combination of the
     *   following values: VTXTF_SPEAKDONE VTXTF_SPEAKSTART
     * @param pSiteInfo [in] Pointer to a VTSITEINFO structure that contains settings to apply to the
     *   site, such as the voice and talking speed. The settings are applied, even if the site is already
     *   open. If a VTSITEINFO structure is not specified, the voice text object uses the settings from
     *   the registry. If there are no registry settings, it uses the default settings, typically those
     *   for the computer. Telephony applications pass this information to ensure that the proper settings
     *   are selected. Other applications set this parameter to NULL to leave the site settings unchanged.
     *
     * @return - NOERROR: The method successfully registered an application to use voice text on a site.
     *   - VTXTERR_INVALIDPARAM: A parameter is invalid. - VTXTERR_OUTOFMEM: There is not enough memory.
     *
     * An application must call Register before it can call other methods in the IVoiceText interface.
     *
     * An application cannot call Register a second time for the same voice text object. To change
     * sites, the application must call the CoCreateInstance function to create a new voice text object
     * for the desired site.
     */
    STDMETHOD (Register)         (THIS_ PCSTR, PCSTR, 
                                        PIVTXTNOTIFYSINK, GUID,
                                        DWORD, PVTSITEINFO) PURE;
    /**
     * This method starts playing the specified text.
     *
     * @param pszSpeak [in] Pointer to a buffer that contains the text to speak. The text is in the form
     *   of a null-terminated string. The length of the text string must be less than 2 kilobytes (KB).
     *   Strings longer than 2 KB cause unexpected speech behavior. An application can free or modify the
     *   buffer as soon as Speak returns. The string pointed to by this parameter can contain
     *   text-to-speech control tags. In Auto PC, this string can contain the TTS tags. For more
     *   information about tags, see Text-to-Speech Tags.
     * @param dwFlags [in] Specifies priority of the text. It is one of the following values: -
     *   VTXTSP_HIGH: Play the text as soon as possible, after text that is currently being spoken but
     *   before any other text in the playback queue. - VTXTSP_NORMAL: Add the text to the end of the
     *   playback queue. This is the default priority. - VTXTSP_VERYHIGH: Play the text immediately,
     *   interrupting text that is currently being spoken, if any. The interrupted text resumes playing as
     *   soon as the very high priority text is finished, although the interrupted text may not be
     *   correctly synchronized.
     * @param pszTags [in] Ignored.
     *
     * @return - NOERROR: The method successfully started playing the specified text. -
     *   VTXTERR_INVALIDMODE: The text-to-speech mode is invalid, or the application has not been
     *   registered to use the voice text on the site. - VTXTERR_INVALIDPARAM: A parameter is invalid. -
     *   VTXTERR_NOTENABLED: Voice text is not enabled. - VTXTERR_OUTOFMEM: There is not enough memory. -
     *   VTXTERR_QUEUEFULL: The playback queue is full. - VTXTERR_WAVEDEVICEBUSY: The wave device is busy.
     *
     * If an application calls the Speak method when other text is being played, the specified text is
     * added to the end of the playback queue, unless the application specifies a higher priorityfor the
     * new text in dwFlags.
     *
     * Calling Speak affects all applications using voice text on the site, because all applications
     * share the same playback queue.
     *
     * The type of speech specified by dwFlags is communicated to the text-to-speech engine though
     * control tags. Support of most control tags is optional; the engine ignores unsupported tags.
     */
    STDMETHOD (Speak)            (THIS_ PCSTR, DWORD, PCSTR) PURE;
    /**
     * This method halts text that is currently being spoken and flushes all pending text from the
     * playback queue.
     *
     * @return - NOERROR: The method successfully halted the text being spoken and flushed all pending
     *   text from the playback queue. - VTXTERR_INVALIDMODE: The text-to-speech mode is invalid, or the
     *   application has not been registered to use the voice text on the site. - VTXTERR_NOTENABLED:
     *   Voice text is not enabled. - VTXTERR_OUTOFMEM: There is not enough memory.
     *
     * Calling the StopSpeaking method affects all applications using voice text on the site, because
     * all applications share the same playback queue.
     */
    STDMETHOD (StopSpeaking)     (THIS) PURE;
    STDMETHOD (AudioFastForward) (THIS) PURE;
    /**
     * This method pauses text-to-speech output for a voice text site.
     *
     * @return - NOERROR: The method successfully paused the text-to-speech output. -
     *   VTXTERR_INVALIDMODE: The text-to-speech mode is invalid, or the application has not been
     *   registered to use the voice text on the site. - VTXTERR_NOTENABLED: Voice text is not enabled. -
     *   VTXTERR_OUTOFMEM: There is not enough memory.
     *
     * When a voice text object is first created, text-to-speech output is not paused. Because pausing
     * text-to-speech output affects all applications that use voice text on the site, an application
     * should resume text-to-speech output as soon as possible by calling the IVoiceText::AudioResume
     * method.
     *
     * When output has been paused, the IVTxtAttributes::IsSpeaking method returns FALSE, even though
     * the voice text object still has data available in its queue and has not yet sent a
     * IVTxtNotifySink::SpeakingDone notification.
     *
     * No notifications are sent when audio is paused or resumed.
     */
    STDMETHOD (AudioPause)       (THIS) PURE;
    /**
     * This method resumes text-to-speech output after it has been paused by the IVoiceText::AudioPause
     * method.
     *
     * @return - NOERROR: The method successfully resumed the text-to-speech output. -
     *   VTXTERR_INVALIDMODE: The text-to-speech mode is invalid, or the application has not been
     *   registered to use the voice text on the site. - VTXTERR_NOTENABLED: Voice text is not enabled. -
     *   VTXTERR_OUTOFMEM: There is not enough memory.
     *
     * The AudioResume method affects all applications using the site.
     */
    STDMETHOD (AudioResume)      (THIS) PURE;
    STDMETHOD (AudioRewind)      (THIS) PURE;
};

typedef IVoiceTextA FAR * PIVOICETEXTA;


#ifdef _S_UNICODE
 /**
  * This interface registers an application to use the voice text object, and controls playback of
  * text.
  */
 #define IVoiceText      IVoiceTextW
 #define IID_IVoiceText  IID_IVoiceTextW
 #define PIVOICETEXT     PIVOICETEXTW

#else
 /**
  * This interface registers an application to use the voice text object, and controls playback of
  * text.
  */
 #define IVoiceText      IVoiceTextA
 #define IID_IVoiceText  IID_IVoiceTextA
 #define PIVOICETEXT     PIVOICETEXTA

#endif //_S_UNICODE



/*
 *  IVTxtAttributes
 */
#undef   INTERFACE
#define  INTERFACE   IVTxtAttributesW

// {6A8D6140-E095-11cd-A166-00AA004CD65C}
DEFINE_GUID(IID_IVTxtAttributesW, 0x6a8d6140, 0xe095, 0x11cd, 0xa1, 0x66, 0x0, 0xaa, 0x0, 0x4c, 0xd6, 0x5c);

/**
 * This interface allows an application to control various aspects of the operation of a voice text
 * object.
 */
DECLARE_INTERFACE_ (IVTxtAttributesW, IUnknown) {
   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // IVTxtAttributes members
   STDMETHOD (DeviceGet)         (THIS_ DWORD *) PURE;
   STDMETHOD (DeviceSet)         (THIS_ DWORD) PURE;
   /**
    * This method retrieves whether voice text is enabled for a voice text site.
    *
    * @param dwEnabled [out] Specifies whether voice text is enabled. TRUE indicates that voice text is
    *   enabled for the site; FALSE indicates it is disabled.
    *
    * @return - NOERROR: The method successfully retrieved whether voice text is enabled for a voice
    *   text site. - VTXTERR_INVALIDMODE: The text-to-speech mode is invalid, or the application has not
    *   been registered to use the voice text on the site. - VTXTERR_INVALIDPARAM: A parameter is
    *   invalid. - VTXTERR_OUTOFMEM: There is not enough memory.
    *
    * If voice text is disabled, no text-to-speech is played over the site. Enabling or disabling voice
    * text for a site affects all applications using a voice text site.
    *
    * Typically, an application disables voice text because the user does not want the computer to
    * speak.
    *
    * The enabled state for a site is saved between uses of the site, even if the user shuts down the
    * computer in the meantime.
    */
   STDMETHOD (EnabledGet)        (THIS_ DWORD *) PURE;
   /**
    * This method sets whether voice text is enabled for a voice text site.
    *
    * @param dwEnabled [in] Specifies whether voice text is enabled. TRUE indicates that voice text is
    *   enabled for the site; FALSE indicates it is disabled.
    *
    * @return - NOERROR: The method successfully set whether voice text is enabled for a voice text
    *   site. - VTXTERR_INVALIDMODE: The text-to-speech mode is invalid, or the application has not been
    *   registered to use the voice text on the site. - VTXTERR_INVALIDPARAM: A parameter is invalid. -
    *   VTXTERR_OUTOFMEM: There is not enough memory.
    *
    * The enabled state for a site is saved between uses of the site, even if the user shuts down the
    * computer in the meantime.
    */
   STDMETHOD (EnabledSet)        (THIS_ DWORD) PURE;
   /**
    * This method indicates whether text is currently being spoken by a voice text site.
    *
    * @param pfSpeaking [out] Pointer to a Boolean that receives the current speaking status. The
    *   Boolean is set to TRUE if the text-to-speech engine is speaking, or to FALSE if it is silent.
    *
    * @return - NOERROR: The method successfully indicated whether text is currently being spoken by a
    *   voice text site. - VTXTERR_INVALIDMODE: The text-to-speech mode is invalid, or the application
    *   has not been registered to use the voice text on the site. - VTXTERR_INVALIDPARAM: A parameter is
    *   invalid. - VTXTERR_OUTOFMEM: There is not enough memory.
    *
    * The voice text object does not send data resulting from multiple calls to the IVoiceText::Speak
    * method directly to the text-to-speech engine. Instead, the object keeps data from each call in a
    * separate buffer so that the VTXTSP_HIGH and VTXTSP_VERYHIGH priority strings can be inserted into
    * the queue at the proper positions.
    *
    * For example, a VTXTSP_VERYHIGH priority string may interrupt a high or normal priority string.
    * The interrupted string resumes after the very high priority string has finished. As a result of
    * this implementation, IsSpeaking returns FALSE for a short time between the end of one buffer in
    * the queue and the start of the next buffer, because audio output has been temporarily suspended.
    */
   STDMETHOD (IsSpeaking)        (THIS_ BOOL *) PURE;
   /**
    * This method retrieves the current average talking speed for a voice text site, in words per
    * minute.
    *
    * @param pdwSpeed [out] Pointer to a DWORD that receives the talking speed for a voice text site.
    *
    * @return - NOERROR: The method successfully retrieved the current average talking speed for a
    *   voice text site. - VTXTERR_INVALIDMODE: The text-to-speech mode is invalid, or the application
    *   has not been registered to use the voice text on the site. - VTXTERR_INVALIDPARAM: A parameter is
    *   invalid. - VTXTERR_OUTOFMEM: There is not enough memory.
    *
    * The talking speed for a site is saved between uses of the site, even if the user shuts down the
    * computer in the meantime.
    */
   STDMETHOD (SpeedGet)          (THIS_ DWORD *) PURE;
   /**
    * This method sets the average talking speed for a voice text site, in words per minute.
    *
    * @param dwSpeed [in] Specifies the new talking speed for the site. An application can specify
    *   TTSATTR_MINSPEED or TTSATTR_MAXSPEED for the minimum or maximum allowable value, respectively.
    *
    * @return - NOERROR: The method successfully set the average talking speed for a voice text site. -
    *   VTXTERR_INVALIDPARAM: A parameter is invalid. - VTXTERR_OUTOFMEM: There is not enough memory.
    *
    * The talking speed for a site is saved between uses of the site, even if the user shuts down the
    * computer in the meantime.
    *
    * If a voice-navigation application is installed on the user's computer, an application may not
    * need to set the speed.
    */
   STDMETHOD (SpeedSet)          (THIS_ DWORD) PURE;
   /**
    * This method retrieves the globally unique identifier (GUID) of the current text-to-speech (TTS)
    * mode for a voice text site.
    *
    * @param pgVoice [out] Pointer to a variable that receives the GUID assigned to the text-to-speech
    *   mode.
    *
    * @return - NOERROR: The method successfully retrieved the GUID of the current TTS mode for a voice
    *   text site. - VTXTERR_INVALIDMODE: The text-to-speech mode is invalid, or the application has not
    *   been registered to use the voice text on the site. - VTXTERR_INVALIDPARAM: A parameter is
    *   invalid. - VTXTERR_OUTOFMEM: There is not enough memory.
    *
    * A text-to-speech engine typically provides an assortment of text-to-speech modes that can be used
    * to play speech in different voices. A voice text site uses a single text-to-speech mode,
    * represented internally by a low-level engine object.
    *
    * The text-to-speech mode for a site is saved between uses of the site, even if the user shuts down
    * the computer in the meantime.
    *
    * In Auto PC, there is usually only one TTS mode.
    */
   STDMETHOD (TTSModeGet)        (THIS_ GUID *) PURE;
   /**
    * This method sets the globally unique identifier (GUID) of the current text-to-speech (TTS) mode
    * for a voice text site.
    *
    * @param gVoice [in] GUID of the TTS mode to set for the site. If the mode does not exist, an error
    *   is returned and the mode is not changed.
    *
    * @return - NOERROR: The method successfully set the GUID of the current TTS mode for a voice text
    *   site. - VTXTERR_INVALIDMODE: The text-to-speech mode is invalid, or the application has not been
    *   registered to use the voice text on the site. - VTXTERR_INVALIDPARAM: A parameter is invalid. -
    *   VTXTERR_OUTOFMEM: There is not enough memory.
    *
    * The text-to-speech mode for a site is saved between uses of the site, even if the user shuts down
    * the computer in the meantime.
    *
    * If a voice-navigation application is installed on the user's computer, an application may not
    * need to set the mode.
    *
    * There is usually only one TTS mode.
    */
   STDMETHOD (TTSModeSet)        (THIS_ GUID) PURE;
};

typedef IVTxtAttributesW FAR * PIVTXTATTRIBUTESW;


#undef   INTERFACE
#define  INTERFACE   IVTxtAttributesA

// {8BE9CC30-E095-11cd-A166-00AA004CD65C}
DEFINE_GUID(IID_IVTxtAttributesA, 0x8be9cc30, 0xe095, 0x11cd, 0xa1, 0x66, 0x0, 0xaa, 0x0, 0x4c, 0xd6, 0x5c);

/**
 * This interface allows an application to control various aspects of the operation of a voice text
 * object.
 */
DECLARE_INTERFACE_ (IVTxtAttributesA, IUnknown) {
   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // IVTxtAttributes members
   STDMETHOD (DeviceGet)         (THIS_ DWORD *) PURE;
   STDMETHOD (DeviceSet)         (THIS_ DWORD) PURE;
   /**
    * This method retrieves whether voice text is enabled for a voice text site.
    *
    * @param dwEnabled [out] Specifies whether voice text is enabled. TRUE indicates that voice text is
    *   enabled for the site; FALSE indicates it is disabled.
    *
    * @return - NOERROR: The method successfully retrieved whether voice text is enabled for a voice
    *   text site. - VTXTERR_INVALIDMODE: The text-to-speech mode is invalid, or the application has not
    *   been registered to use the voice text on the site. - VTXTERR_INVALIDPARAM: A parameter is
    *   invalid. - VTXTERR_OUTOFMEM: There is not enough memory.
    *
    * If voice text is disabled, no text-to-speech is played over the site. Enabling or disabling voice
    * text for a site affects all applications using a voice text site.
    *
    * Typically, an application disables voice text because the user does not want the computer to
    * speak.
    *
    * The enabled state for a site is saved between uses of the site, even if the user shuts down the
    * computer in the meantime.
    */
   STDMETHOD (EnabledGet)        (THIS_ DWORD *) PURE;
   /**
    * This method sets whether voice text is enabled for a voice text site.
    *
    * @param dwEnabled [in] Specifies whether voice text is enabled. TRUE indicates that voice text is
    *   enabled for the site; FALSE indicates it is disabled.
    *
    * @return - NOERROR: The method successfully set whether voice text is enabled for a voice text
    *   site. - VTXTERR_INVALIDMODE: The text-to-speech mode is invalid, or the application has not been
    *   registered to use the voice text on the site. - VTXTERR_INVALIDPARAM: A parameter is invalid. -
    *   VTXTERR_OUTOFMEM: There is not enough memory.
    *
    * The enabled state for a site is saved between uses of the site, even if the user shuts down the
    * computer in the meantime.
    */
   STDMETHOD (EnabledSet)        (THIS_ DWORD) PURE;
   /**
    * This method indicates whether text is currently being spoken by a voice text site.
    *
    * @param pfSpeaking [out] Pointer to a Boolean that receives the current speaking status. The
    *   Boolean is set to TRUE if the text-to-speech engine is speaking, or to FALSE if it is silent.
    *
    * @return - NOERROR: The method successfully indicated whether text is currently being spoken by a
    *   voice text site. - VTXTERR_INVALIDMODE: The text-to-speech mode is invalid, or the application
    *   has not been registered to use the voice text on the site. - VTXTERR_INVALIDPARAM: A parameter is
    *   invalid. - VTXTERR_OUTOFMEM: There is not enough memory.
    *
    * The voice text object does not send data resulting from multiple calls to the IVoiceText::Speak
    * method directly to the text-to-speech engine. Instead, the object keeps data from each call in a
    * separate buffer so that the VTXTSP_HIGH and VTXTSP_VERYHIGH priority strings can be inserted into
    * the queue at the proper positions.
    *
    * For example, a VTXTSP_VERYHIGH priority string may interrupt a high or normal priority string.
    * The interrupted string resumes after the very high priority string has finished. As a result of
    * this implementation, IsSpeaking returns FALSE for a short time between the end of one buffer in
    * the queue and the start of the next buffer, because audio output has been temporarily suspended.
    */
   STDMETHOD (IsSpeaking)        (THIS_ BOOL *) PURE;
   /**
    * This method retrieves the current average talking speed for a voice text site, in words per
    * minute.
    *
    * @param pdwSpeed [out] Pointer to a DWORD that receives the talking speed for a voice text site.
    *
    * @return - NOERROR: The method successfully retrieved the current average talking speed for a
    *   voice text site. - VTXTERR_INVALIDMODE: The text-to-speech mode is invalid, or the application
    *   has not been registered to use the voice text on the site. - VTXTERR_INVALIDPARAM: A parameter is
    *   invalid. - VTXTERR_OUTOFMEM: There is not enough memory.
    *
    * The talking speed for a site is saved between uses of the site, even if the user shuts down the
    * computer in the meantime.
    */
   STDMETHOD (SpeedGet)          (THIS_ DWORD *) PURE;
   /**
    * This method sets the average talking speed for a voice text site, in words per minute.
    *
    * @param dwSpeed [in] Specifies the new talking speed for the site. An application can specify
    *   TTSATTR_MINSPEED or TTSATTR_MAXSPEED for the minimum or maximum allowable value, respectively.
    *
    * @return - NOERROR: The method successfully set the average talking speed for a voice text site. -
    *   VTXTERR_INVALIDPARAM: A parameter is invalid. - VTXTERR_OUTOFMEM: There is not enough memory.
    *
    * The talking speed for a site is saved between uses of the site, even if the user shuts down the
    * computer in the meantime.
    *
    * If a voice-navigation application is installed on the user's computer, an application may not
    * need to set the speed.
    */
   STDMETHOD (SpeedSet)          (THIS_ DWORD) PURE;
   /**
    * This method retrieves the globally unique identifier (GUID) of the current text-to-speech (TTS)
    * mode for a voice text site.
    *
    * @param pgVoice [out] Pointer to a variable that receives the GUID assigned to the text-to-speech
    *   mode.
    *
    * @return - NOERROR: The method successfully retrieved the GUID of the current TTS mode for a voice
    *   text site. - VTXTERR_INVALIDMODE: The text-to-speech mode is invalid, or the application has not
    *   been registered to use the voice text on the site. - VTXTERR_INVALIDPARAM: A parameter is
    *   invalid. - VTXTERR_OUTOFMEM: There is not enough memory.
    *
    * A text-to-speech engine typically provides an assortment of text-to-speech modes that can be used
    * to play speech in different voices. A voice text site uses a single text-to-speech mode,
    * represented internally by a low-level engine object.
    *
    * The text-to-speech mode for a site is saved between uses of the site, even if the user shuts down
    * the computer in the meantime.
    *
    * In Auto PC, there is usually only one TTS mode.
    */
   STDMETHOD (TTSModeGet)        (THIS_ GUID *) PURE;
   /**
    * This method sets the globally unique identifier (GUID) of the current text-to-speech (TTS) mode
    * for a voice text site.
    *
    * @param gVoice [in] GUID of the TTS mode to set for the site. If the mode does not exist, an error
    *   is returned and the mode is not changed.
    *
    * @return - NOERROR: The method successfully set the GUID of the current TTS mode for a voice text
    *   site. - VTXTERR_INVALIDMODE: The text-to-speech mode is invalid, or the application has not been
    *   registered to use the voice text on the site. - VTXTERR_INVALIDPARAM: A parameter is invalid. -
    *   VTXTERR_OUTOFMEM: There is not enough memory.
    *
    * The text-to-speech mode for a site is saved between uses of the site, even if the user shuts down
    * the computer in the meantime.
    *
    * If a voice-navigation application is installed on the user's computer, an application may not
    * need to set the mode.
    *
    * There is usually only one TTS mode.
    */
   STDMETHOD (TTSModeSet)        (THIS_ GUID) PURE;
};

typedef IVTxtAttributesA FAR * PIVTXTATTRIBUTESA;


#ifdef _S_UNICODE
 /**
  * This interface allows an application to control various aspects of the operation of a voice text
  * object.
  */
 #define IVTxtAttributes        IVTxtAttributesW
 #define IID_IVTxtAttributes    IID_IVTxtAttributesW
 #define PIVTXTATTRIBUTES       PIVTXTATTRIBUTESW

#else
 /**
  * This interface allows an application to control various aspects of the operation of a voice text
  * object.
  */
 #define IVTxtAttributes        IVTxtAttributesA
 #define IID_IVTxtAttributes    IID_IVTxtAttributesA
 #define PIVTXTATTRIBUTES       PIVTXTATTRIBUTESA

#endif // _S_UNICODE



/*
 *  IVTxtDialog
 */
#undef   INTERFACE
#define  INTERFACE   IVTxtDialogsW

// {D6469210-E095-11cd-A166-00AA004CD65C}
DEFINE_GUID(IID_IVTxtDialogsW, 0xd6469210, 0xe095, 0x11cd, 0xa1, 0x66, 0x0, 0xaa, 0x0, 0x4c, 0xd6, 0x5c);

DECLARE_INTERFACE_ (IVTxtDialogsW, IUnknown) {
   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // IVTxtDialogs members

   STDMETHOD (AboutDlg)       (THIS_ HWND, PCWSTR) PURE;
   STDMETHOD (LexiconDlg)     (THIS_ HWND, PCWSTR) PURE;
   STDMETHOD (GeneralDlg)     (THIS_ HWND, PCWSTR) PURE;
   STDMETHOD (TranslateDlg)   (THIS_ HWND, PCWSTR) PURE;
};

typedef IVTxtDialogsW FAR * PIVTXTDIALOGSW;


#undef   INTERFACE
#define  INTERFACE   IVTxtDialogsA

// {E8F6FA20-E095-11cd-A166-00AA004CD65C}
DEFINE_GUID(IID_IVTxtDialogsA, 0xe8f6fa20, 0xe095, 0x11cd, 0xa1, 0x66, 0x0, 0xaa, 0x0, 0x4c, 0xd6, 0x5c);

DECLARE_INTERFACE_ (IVTxtDialogsA, IUnknown) {
   // IUnknown members
   STDMETHOD(QueryInterface)  (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
   STDMETHOD_(ULONG,AddRef)   (THIS) PURE;
   STDMETHOD_(ULONG,Release)  (THIS) PURE;

   // IVTxtDialogs members
   STDMETHOD (AboutDlg)       (THIS_ HWND, PCSTR) PURE;
   STDMETHOD (LexiconDlg)     (THIS_ HWND, PCSTR) PURE;
   STDMETHOD (GeneralDlg)     (THIS_ HWND, PCSTR) PURE;
   STDMETHOD (TranslateDlg)   (THIS_ HWND, PCSTR) PURE;
};

typedef IVTxtDialogsA FAR * PIVTXTDIALOGSA;


#ifdef _S_UNICODE
 #define IVTxtDialogs       IVTxtDialogsW
 #define IID_IVTxtDialogs   IID_IVTxtDialogsW
 #define PIVTXTDIALOGS      PIVTXTDIALOGSW

#else
 #define IVTxtDialogs       IVTxtDialogsA
 #define IID_IVTxtDialogs   IID_IVTxtDialogsA
 #define PIVTXTDIALOGS      PIVTXTDIALOGSA

#endif // _S_UNICODE



/************************************************************************
class guids */

// {080EB9D0-E096-11cd-A166-00AA004CD65C}
// DEFINE_GUID(CLSID_VTxt, 0x80eb9d0, 0xe096, 0x11cd, 0xa1, 0x66, 0x0, 0xaa, 0x0, 0x4c, 0xd6, 0x5c);
// {F1DC95A0-0BA7-11ce-A166-00AA004CD65C}
DEFINE_GUID(CLSID_VTxt, 
0xf1dc95a0, 0xba7, 0x11ce, 0xa1, 0x66, 0x0, 0xaa, 0x0, 0x4c, 0xd6, 0x5c);



#endif    // _SPEECH_
