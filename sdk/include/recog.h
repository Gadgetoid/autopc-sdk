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

/**
 * This function initializes the handwriting recognition dynamic-link library (DLL).
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError.
 *
 * This function is called only once by an application to initialize the DLL. Call HwxConfig before
 * calling other handwriting functions, all of which fail when the DLL is not initialized.
 */
BOOL      WINAPI HwxConfig();

/* Called to create an HRC before any ink is collected. You can pass in NULL
for the parameter, but if you pass in an old HRC, it copies the old settings (such
as alphabet, guide structure, previous context, etc.)  */

/**
 * This function creates an handwriting recognition context (HRC) object. This object is used by a
 * handwriting recognition engine to obtain ink-information that describes what the user is
 * drawing-and to store the results of recognition processing.
 *
 * @param hrc [in] Handle to an existing handwriting recognition context (HRC) object that provides
 *   settings for the recognition context being created. If it is NULL, then default settings are
 *   used.
 *
 * @return The handle to the newly created HRC object indicates success. NULL indicates failure. To
 *   get extended error information, call GetLastError.
 *
 * To efficiently process handwriting, create a master HRC before collecting any ink. This master
 * HRC is a template that contains all the information that the handwriting recognition engine needs
 * to translate user input. First call HwxCreate, setting the hrc parameter to NULL. Call
 * HwxSetGuide to specify a HWXGUIDE structure, and call HwxALCValid to specify an alphabet code
 * (ALC) grouping. For each character or group of characters that an application collects from a
 * user, copy the master HRC to another HRC for collecting and processing ink. After all of the ink
 * in an HRC is processed, the HRC has served its purpose, so remove it with the HwxDestroy
 * function. For the next collection of user input, copy the master HRC again, and so on.
 *
 * The hrc parameter is used to copy settings from an old HRC into a new HRC object. These settings
 * include alphabet code (ALC) groupings , the HWXGUIDE structure, the character previously
 * processed, and ink that may be in the old context.
 */
HRC       WINAPI HwxCreate(HRC);

/* Called to destroy an HRC after recognition is complete */

/**
 * This function destroys a handwriting recognition context (HRC) object.
 *
 * @param hrc [in] Handle to the handwriting recognition context (HRC) object.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError.
 *
 * The handwriting recognition engine uses an HRC to process each character that a user draws.
 * Typically, before an application collects user input, it calls the HwxCreate function to create a
 * master HRC. Whenever a new HRC is needed to interpret another character, an application copies
 * the master HRC to an HRC used for processing. To conserve system resources, use HwxDestroy to
 * remove each HRC after calling HwxGetResults.
 *
 * After HwxDestroy returns TRUE, the handle hrc is no longer valid. An application should set hrc
 * to NULL to ensure it is not inadvertently used again.
 */
int       WINAPI HwxDestroy(HRC);

/* Tells the HRC where the boxes on the screen are. Third parameter is first visible
box.  (Should probably always be zero.) */

/**
 * This function points to a structure that specifies the size and position on a screen of input
 * boxes, which collect characters drawn by a user.
 *
 * @param hrc [in] Handle to the handwriting recognition context (HRC) object.
 * @param lpGuide [in] Long pointer to a HWXGUIDE structure.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError.
 *
 * Call HwxSetGuide after the HwxCreate function and before accepting user input to the HRC with
 * calls to the HwxInput function. The handwriting recognition engine requires that an application
 * specify a HWXGUIDE structure for HRC objects.
 *
 * The HWXGUIDE structure can define one input area, or box, or it can define many input areas. When
 * the guide contains multiple input boxes, HwxGetResults returns results for multiple characters.
 */
int       WINAPI HwxSetGuide(HRC, GUIDE *, UINT);

/* Limits the set of characters the recognizer can return.  (See ALC values above.) */

int       WINAPI HwxSetAlphabet(HRC, ALC);

/* Sets parameter for partial recognition */

/**
 * This function enables partial recognition for the handwriting recognition engine.
 *
 * @param hrc [in] Handle for the handwriting recognition context (HRC) object.
 * @param urecog [in] Value for the partial recognition parameter. It is one of the following
 *   values: Value Description HWX_PARTIAL_ALL All strokes are input before recognition occurs,
 *   effectively turning off partial recognition. HWX_PARTIAL_ORDER Partial recognition processing is
 *   based on the assumption that first strokes entered by the user are the beginning of the
 *   character, and the remaining strokes are drawn in their correct order. HWX_PARTIAL_FREE Partial
 *   recognition processing is based on the assumption that the user may draw the character strokes in
 *   random order.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError.
 *
 * When an application enables partial recognition, an application makes multiple calls to
 * HwxProcess for a single character. When partial recognition is not enabled, an application calls
 * HwxProcess once after an application collects all user input, or ink, for a character.
 *
 * Use HwxSetPartial to enable partial recognition before calling HwxInput and HwxProcess to process
 * ink.
 *
 * Partial recognition enables the handwriting recognition engine to return choices even when the
 * user incorrectly or partially writes a character or glyph. This benefits the user, who can enter
 * complex characters without having to remember the exact order or number of necessary strokes.
 * Partial recognition is available for processing complex characters, such as those used in the
 * Japanese, Chinese, and Korean languages. For languages that consist of simple characters, such as
 * European languages, partial recognition is not available.
 *
 * A complex character is made up of many strokes. A stroke consists of three events: stylus down on
 * the input panel, stylus movement, and stylus up. When a user starts drawing the first strokes of
 * a complex character and partial recognition is enabled, an application calls HwxInput to supply
 * ink to the HRC. A call to HwxProcess signals the handwriting recognition engine to start
 * processing ink. An application can then call HwxResultsAvailable to see if the recognition engine
 * has a possible match for the character. If results are available, an application calls
 * HwxGetResults and displays the result to the user. The user can confirm the character and begin
 * drawing the next character, or continue drawing the current character until it is correctly
 * identified by the recognition engine.
 *
 * Partial recognition works best in a multithreaded operating environment. This enables a single
 * application process to have one thread collecting ink and another thread processing ink, with
 * both threads sharing the same memory address space. When the collection thread has more ink for
 * the handwriting recognition engine, it can use HwxSetAbort to signal the thread that is
 * processing ink to stop recognition processing. After the additional information has been received
 * and HwxPartial has been used to assess the character, the recognition thread calls HwxProcess to
 * resume processing.
 */
int		  WINAPI HwxSetPartial(HRC, DWORD);

/* Sets abort address */

/**
 * This function sets an address that the handwriting recognition engine checks to determine if more
 * user input, or ink, is available. If the address, which is the number of stokes collected for a
 * character, indicates more ink is available, the handwriting recognition engine aborts. It can
 * then be called again to include the new ink in its processing. If the stroke counter indicates
 * that no new ink is available, the handwriting recognition engine continues processing.
 *
 * @param hrc [in] Handle of the handwriting recognition context (HRC) object.
 * @param pnumstrokes [in] Pointer to the number of strokes currently in the handwriting recognition
 *   context (HRC). A stroke consists of stylus down, stylus movement, and stylus lift.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError.
 *
 * Use this function after a call to the HwxSetPartial function. Partial recognition processing
 * works best in a multithreaded operating environment. This enables a single application process to
 * have one thread collecting user input, or ink, and another thread processing ink, with both
 * threads sharing the same memory address space. The thread that processes ink, or the recognition
 * thread, uses the address pointed to by pnumstrokes as a signal to stop recognition processing
 * when the collection thread has more ink for the recognition thread to work with. If the contents
 * of that address do not match the number of strokes that the handwriting recognition engine-the
 * recognition thread-is currently processing, then processing stops As long as pnumstrokes matches
 * the number of strokes that the handwriting recognition engine is processing, processing
 * continues.
 *
 * To resume processing after an abort, the recognition thread calls the HwxProcess function.
 *
 * Two stroke counters are maintained for the current character or glyph. One is in your application
 * and the other is an internal stroke count. The application counter must be incremented when the
 * stylus touches the input box, because it is starting a new stroke. When the stroke is done-that
 * is, when the stylus is raised from the input box-HwxInput is called. HwxInput adds the stroke
 * information to the character or glyph data and increments the internal stroke count for the
 * character or glyph. While the user is putting the stroke information in the input box, the two
 * counters are different..
 *
 * Set pnumstrokes to point to the application stroke count. When HwxSetPartial has been called for
 * this character or glyph and there is a new stroke in the input box, calling HwxSetAbort causes
 * the partial recognition process to stop. The application then includes the new data in the
 * information it is using for recognition.
 */
int		  WINAPI HwxSetAbort(HRC, DWORD *);

/* Adds ink to the HRC. */

/**
 * This function adds stroke information to the handwriting recognition context (HRC).
 *
 * @param hrc [in] Handle to the handwriting recognition context (HRC) object.
 * @param lppnt [in] Long pointer to an address of an array of POINT structures. The information in
 *   the POINT structures should be scaled to match the HWXGUIDE structure.
 * @param upoints [in] Number of POINT structures.
 * @param timestamp [in] Time stamp when a device, such as a stylus, started adding information to
 *   the input box. The time stamp should be taken directly from the MSG structure for the stylus down
 *   event.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError.
 *
 * As a user draws a character, an application calls this function to add user input, or ink, to the
 * HRC object one stroke at a time. A stroke consists of stylus down, stylus movement, and stylus
 * lift. HwxInput takes the array of points, the count of the points, and the time stamp of the
 * first stylus event in the stroke and adds it to the HRC object. When an application determines
 * that there is no more ink to receive for an HRC, it calls the HwxEndInput function.
 */
int       WINAPI HwxInput(HRC, POINT *, STROKEINFO *);

/* Called after last ink is added.  You cannot add anymore ink
to the HRC after this has been called. */


/**
 * This function notifies the handwriting recognition engine that no more ink should be added to the
 * handwriting recognition context (HRC) object.
 *
 * @param hrc [in] Handle to the handwriting recognition context (HRC) object that no longer
 *   receives ink.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError.
 *
 * An application calls this function after using the HwxInput function to add the last ink to the
 * HRC. The next call to HwxProcess completes recognition on all the input. Any calls to HwxInput on
 * this HRC fail after HwxEndInput is called.
 */
int       WINAPI HwxEndInput(HRC);

/* Recognizes as much ink as it can */

/**
 * This function signals the recognizer to analyze the information in the specified handwriting
 * recognition context (HRC) object.
 *
 * @param hrc [in] Handle to the handwriting recognition context (HRC) object to be analyzed.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError.
 *
 * This function processes the ink that has been received by the HRC object. Full recognition occurs
 * only after HwxEndInput is called. The application must then call HwxGetResults to obtain
 * recognition results.
 *
 * There is no support for timeouts.See Also
 *
 * HwxEndInput, HwxGetResults
 */
int       WINAPI HwxProcess(HRC);

/* Retreives the results from an HRC. This may be called repeatedly. This allows you
to get restults from several characters at a time. The return value is the number of
characters actually returned. */

/**
 * This function retrieves the handwriting recognition engine results from the specified handwriting
 * recognition context (HRC).
 *
 * @param hrc [in] Handle to the handwriting recognition context (HRC).
 * @param cAlt [in] Number of alternate results expected in the HWXRESULTS structure. If this
 *   parameter is 0, the function returns 0.
 * @param iFirst [in] Index of the first character to return.
 * @param cBoxRes [in] Number of characters to return.
 * @param rgBoxResults [out] Array of ranked lists, one list per returned character, that specify
 *   results.
 *
 * @return The number of characters actually returned indicates success. HRCR_ERROR indicates
 *   failure.
 *
 * Before calling HwxGetResults, an application can call the HwxResultsAvailable function to find
 * out how many characters are available from the handwriting recognition engine.
 *
 * When the HWXGUIDE structure defines multiple input boxes, HwxGetResults provides character
 * alternatives on a per-box basis in one call. The rgBoxResults buffer that was passed in contains
 * the results for the returned characters. While the user is still entering characters in the
 * current HRC, an application can use this function to display processed characters. An application
 * can call this function repeatedly.
 *
 * The following code example shows how to simultaneously retrieve results for 10 input boxes, with
 * five alternatives per box.
 *
 *     HANDLE hMem = GlobalAlloc(GHND, 10 * (sizeof(HWXRESULTS) + (5-1) * sizeof(WCHAR)) );
 *     HWXRESULTS * rgBoxR = (HWXRESULTS * ) GlobalLock( hMem);
 *
 *     do
 *     {
 *         int iRes = HwxGetResults ( hrc, 5, indx, 10, rgBoxR);
 *         .
 *         .                // check for errors and use rgBoxR
 *         .
 *         indx += (UINT) iRes;
 *     }
 *     while (iRes == 10);
 */
int WINAPI HwxGetResults(
	HRC hrc,	// HRC containing results
	UINT cAlt,	// Number of alternates
	UINT iSyv,	// index of first character to return
	UINT cBoxRes, // number of characters to return
	BOXRESULTS *rgBoxResults	// array of cBoxRes ranked lists
);

/* Tells the HRC what the previous character was for context purposes. */

/**
 * This function specifies to the handwriting recognition context (HRC) which character the user
 * previously entered. Using this character, the handwriting recognition engine can more accurately
 * determine the character it is currently processing.
 *
 * @param hrc [in] Handle to the handwriting recognition context (HRC) object.
 * @param wContext [in] Unicode value of the character input by the user prior to the character that
 *   is processed in hrc. If this parameter is 0, the recognition engine does not use context
 *   information when identifying the character.
 *
 * @return TRUE indicates success. FALSE indicates failure. To get extended error information, call
 *   GetLastError.
 *
 * Call this function before calling the HwxProcess function. If HwxSetContext is not called, the
 * handwriting recognition engine does not use context information to determine the character.
 * Having context information greatly improves the performance of the handwriting recognition
 * engine. Without context information, for example, it is difficult for the handwriting recognition
 * engine to distinguish a lowercase "l" from the numeral one ("1").
 */
int       WINAPI HwxSetContext(HRC, WCHAR);

/* Tells you how many results can be retrieved from HwxGetResults */

/**
 * This function returns the number of characters that have been processed by the handwriting
 * recognition engine and are available for HwxGetResults to retrieve.
 *
 * @param hrc [in] Handle to the handwriting recognition context (HRC) object.
 *
 * @return The number of characters in the HRC for HwxGetResults to retrieve indicates success. A
 *   value of -1 indicates an error. If the function fails, use GetLastError for error information.
 *
 * With this function, an application can check the progress of the handwriting recognition engine
 * and decide when to retrieve the results with HwxGetResults and display them to the user.
 */
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
