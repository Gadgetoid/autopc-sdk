/***************************************************************************\
*																			*
* RECOG.H - Handwriting functions, types, and definitions					*
*																			*
*           Version 1.0                                                     *
*																			*
*			Copyright (c) 1992-1996 Microsoft Corp. All rights reserved.	*
*																			*
\***************************************************************************/

#ifndef _INC_RECOG
#define _INC_RECOG

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// @CESYSGEN IF CE_MODULES_HWXUSA

/* The constants below are used with HwxSetAlphabet */

// Enabled Alphabet:
#define ALC_DEFAULT          0x00000000L // nothing
#define ALC_LCALPHA          0x00000001L // a..z
#define ALC_UCALPHA          0x00000002L // A..Z
#define ALC_NUMERIC          0x00000004L // 0..9
#define ALC_PUNC             0x00000008L // !-;`"?()&.,; and backslash
#define ALC_MATH             0x00000010L // %^*()-+={}<>,/.
#define ALC_MONETARY         0x00000020L // ,.$ or local
#define ALC_OTHER            0x00000040L // @#|_~[]
#define ALC_ASCII            0x00000080L // restrict to 7-bit chars 20..7f
#define ALC_WHITE            0x00000100L // white space
#define ALC_NONPRINT         0x00000200L // sp tab ret ctrl glyphs
#define ALC_DBCS             0x00000400L // allow DBCS variety of SBCS
#define ALC_JIS1             0x00000800L // kanji JPN, ShiftJIS 1 only
#define	ALC_NUMERIC_PUNC	 0x00001000L // Non digit characters in numbers
#define ALC_GESTURE          0x00004000L // gestures
#define ALC_USEBITMAP        0x00008000L // use rc.rgbfAlc to enable chars
#define ALC_HIRAGANA         0x00010000L // hiragana JPN
#define ALC_KATAKANA         0x00020000L // katakana JPN
#define ALC_JIS2             0x00040000L // kanji JPN, ShiftJIS 2+3
#define ALC_GLOBALPRIORITY   0x10000000L
#define ALC_BEGINPUNC        0x20000000L // English: [ { ( " etc.
#define ALC_ENDPUNC          0x40000000L // English: ] } ) " etc.
#define ALC_OEM              0x0FF80000L // OEM recognizer-specific
#define ALC_RESERVED         0x80002000L // avail for future use
#define ALC_NOPRIORITY       0x00000000L // for alcPriority == none

#define ALC_ALPHA\
    (ALC_LCALPHA | ALC_UCALPHA)                                // 0x00000003L

#define ALC_ALPHANUMERIC\
    (ALC_ALPHA | ALC_NUMERIC)                                  // 0x00000007L

#define ALC_SYSMINIMUM\
    (ALC_ALPHANUMERIC | ALC_PUNC | ALC_WHITE)                  // 0x0000010FL

#define ALC_ALL\
    (ALC_SYSMINIMUM | ALC_MATH | ALC_MONETARY\
    | ALC_OTHER | ALC_NONPRINT)                                // 0x0000037FL

#define ALC_KANJISYSMINIMUM\
    (ALC_SYSMINIMUM | ALC_HIRAGANA | ALC_KATAKANA | ALC_JIS1)  // 0x0003090FL

#define ALC_KANJIALL\
    (ALC_ALL | ALC_HIRAGANA | ALC_KATAKANA | ALC_JIS1 | ALC_JIS2) // 0x00070B7FL

/* Special Symbol Values potentially returned by HwxGetResults. */

#define SYV_NULL                0x00000000L	// Filler when list is not full

/* Possible High Words of SYVs */

#define SYVHI_FIRST             0        // first valid value
#define SYVHI_SPECIAL           0
#define SYVHI_ANSI              1
#define SYVHI_GESTURE           2
#define SYVHI_KANJI             3	// This is the only one actually used
#define SYVHI_SHAPE             4
#define SYVHI_UNICODE           5
#define SYVHI_VKEY              6
#define SYVHI_LAST              6        // last valid value

#ifndef RC_INVOKED				// ... rest of file of no interest to rc compiler

/* Used in HwxInput in the STROKEINFO structure */

#define PDK_NULL                0x0000  // default to no flags set
#define PDK_UP                  0x0000  // PDK_NULL alias
#define PDK_DOWN                0x0001  // pentip switch ON due to contact
#define PDK_BARREL1             0x0002  // barrel1 switch depressed
#define PDK_BARREL2             0x0004  // ditto 2
#define PDK_BARREL3             0x0008  // ditto 3
#define PDK_SWITCHES            0x000f  // sum of down + barrels 1,2,3
#define PDK_TRANSITION          0x0010  // set by GetPenHwData
#define PDK_UNUSED10            0x0020
#define PDK_UNUSED20            0x0040
#define PDK_INVERTED            0x0080  // other end of pen used as tip
#define PDK_PENIDMASK           0x0F00  // bits 8..11 physical pen id (0..15)
#define PDK_UNUSED1000          0x1000
#define PDK_INKSTOPPED          0x2000  // Inking stopped
#define PDK_OUTOFRANGE          0x4000  // pen left range (OEM data invalid)
#define PDK_DRIVER              0x8000  // pen (not mouse) event

#define PDK_TIPMASK             0x0001  // mask for testing PDK_DOWN
#define PDK_EVENT               PDK_TRANSITION  // alias         /* ;Internal */

// General HRC API return values (HRCR_xx):
#define HRCR_COMPLETE           3       // finished recognition
#define HRCR_OK                 1       // success
#define HRCR_ERROR              (-1)    // invalid param or unspecified error
#define HRCR_MEMERR             (-2)    // memory error

// ProcessHRC time constants:
#define PH_MAX                  0xFFFFFFFFL   // recognize rest of ink

// SYV macros:
#define FIsSpecial(syv)         (HIWORD((syv))==SYVHI_SPECIAL)
#define FIsAnsi(syv)            (HIWORD((syv))==SYVHI_ANSI)
#define FIsGesture(syv)         (HIWORD((syv))==SYVHI_GESTURE)
#define FIsKanji(syv)           (HIWORD((syv))==SYVHI_KANJI)
#define FIsShape(syv)           (HIWORD((syv))==SYVHI_SHAPE)
#define FIsUniCode(syv)         (HIWORD((syv))==SYVHI_UNICODE)
#define FIsVKey(syv)            (HIWORD((syv))==SYVHI_VKEY)

#define ChSyvToAnsi(syv)        ((BYTE) (LOBYTE(LOWORD((syv)))))
#define WSyvToKanji(syv)        ((WORD) (LOWORD((syv))))
#define SyvCharacterToSymbol(c) ((LONG)(unsigned char)(c) | 0x00010000)
#define SyvKanjiToSymbol(c)     ((LONG)(UINT)(c) | 0x00030000)

// Simple typedefs
typedef LONG                    ALC;    // Enabled Alphabet
typedef LONG                    SYV;    // Symbol Value

#ifndef DECLARE_HANDLE32
#define	DECLARED_HANDLE32
#define DECLARE_HANDLE32(name)\
    struct name##__ { int unused; };\
    typedef const struct name##__ FAR* name
#endif //!DECLARE_HANDLE32

typedef ALC FAR*                PALC;        // ptr to ALC
typedef SYV FAR*                PSYV;        // ptr to SYV
typedef ALC FAR*                LPALC;       // ptr to ALC
typedef SYV FAR*                LPSYV;       // ptr to SYV

// This structure contains all the information about a stroke except the points

typedef struct tagSTROKEINFO    // 1.0 stroke header
{
    UINT cPnt;                   // count of points in stroke
    UINT cbPnts;                 // size of stroke in bytes
    UINT wPdk;                   // state of stroke
    DWORD dwTick;                // time at beginning of stroke
} STROKEINFO, *PSTROKEINFO, FAR *LPSTROKEINFO;

// Handwriting Recognizer:

DECLARE_HANDLE32(HRC);          // Handwriting Recognition Context
DECLARE_HANDLE(HINKSET);        // handle to an inkset

typedef HRC FAR* PHRC;
typedef HRC FAR* LPHRC;
typedef HINKSET FAR* LPHINKSET;

/* Returned from HwxGetResults */

typedef struct tagBOXRESULTS    // 2.0
{
    UINT indxBox;		// zero-based index in guide structure where char was written
    HINKSET hinksetBox;	// unused
	SYV rgSyv[1];		// variable-sized array of characters returned
} BOXRESULTS, *PBOXRESULTS, FAR *LPBOXRESULTS;

/* Passed in to HwxSetGuide.  Specifies where the boxes are on the screen */

typedef struct tagGUIDE         // 1.0 guide structure
{
	int xOrigin;                 // left edge of first box (screen coord)
	int yOrigin;                 // top edge of first box (screen coord)
	int cxBox;                   // width of a single box
	int cyBox;                   // height of a single box
	int cxBase;                  // in-box x-margin to guideline
	int cyBase;                  // in-box y offset from top to baseline
	int cHorzBox;                // count of boxed columns
	int cVertBox;                // count of boxed rows
	int cyMid;                   // 0 or distance from baseline to midline
} GUIDE, *PGUIDE, FAR *LPGUIDE;

/* Called once to initialize DLL */

BOOL      WINAPI HwxConfig();

/* Called to create an HRC before any ink is collected. You can pass in NULL
for the parameter, but if you pass in an old HRC, it copies the old settings (such
as alphabet, guide structure, previous context, etc.)  */

HRC       WINAPI HwxCreate(HRC);

/* Called to destroy an HRC after recognition is complete */

int       WINAPI HwxDestroy(HRC);

/* Tells the HRC where the boxes on the screen are. Third parameter is first visible
box.  (Should probably always be zero.) */

int       WINAPI HwxSetGuide(HRC, GUIDE *, UINT);

/* Limits the set of characters the recognizer can return.  (See ALC values above.) */

int       WINAPI HwxSetAlphabet(HRC, ALC);

/* Sets parameter for partial recognition */

int		  WINAPI HwxSetPartial(HRC, DWORD);

/* Sets abort address */

int		  WINAPI HwxSetAbort(HRC, DWORD *);

/* Adds ink to the HRC. */

int       WINAPI HwxInput(HRC, POINT *, STROKEINFO *);

/* Called after last ink is added.  You cannot add anymore ink
to the HRC after this has been called. */


int       WINAPI HwxEndInput(HRC);

/* Recognizes as much ink as it can */

int       WINAPI HwxProcess(HRC);

/* Retreives the results from an HRC. This may be called repeatedly. This allows you
to get restults from several characters at a time. The return value is the number of
characters actually returned. */

int WINAPI HwxGetResults(
	HRC hrc,	// HRC containing results
	UINT cAlt,	// Number of alternates
	UINT iSyv,	// index of first character to return
	UINT cBoxRes, // number of characters to return
	BOXRESULTS *rgBoxResults	// array of cBoxRes ranked lists
);

/* Tells the HRC what the previous character was for context purposes. */

int       WINAPI HwxSetContext(HRC, WCHAR);

/* Tells you how many results can be retrieved from HwxGetResults */

int       WINAPI HwxResultsAvailable(HRC);

/* Suggested sequence for using these APIs:

	HwxConfig (once only)
		HwxCreate (once per recognition panel)
		HwxSetGuide
		HwxSetAlphabet
		HwxSetContext	(if there is a previous character)
			HwxInput	(as the user writes)
            HwxProcess  (To Process the ink input)
            HwxResultsAvailable (Find out if new results are available)
                HwxGetResults   (every time there are any results available)
        HwxEndInput (When user is done inputting ink)
        HwxProcess  (To Process the ink input)
		HwxGetResults (to get the last characters)
		HwxDestroy
*/

#endif 

#ifdef DECLARED_HANDLE32
#undef DECLARE_HANDLE32
#undef DECLARED_HANDLE32
#endif

// @CESYSGEN ENDIF
 
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // #define _INC_RECOG
