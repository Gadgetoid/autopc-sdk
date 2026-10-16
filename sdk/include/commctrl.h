/*****************************************************************************\
*                                                                             *
* commctrl.h - - Interface for the Windows Common Controls                    *
*                                                                             *
* Version 1.2                                                                 *
*                                                                             *
* Copyright (c) 1991-1997, Microsoft Corp.      All rights reserved.          *
*                                                                             *
\*****************************************************************************/


#ifndef _INC_COMMCTRL
#define _INC_COMMCTRL

#ifndef _WIN32_IE
#define _WIN32_IE 0x0400
#else
#if (_WIN32_IE < 0x0400) && defined(_WIN32_WINNT) && (_WIN32_WINNT >= 0x0500)
#error _WIN32_IE setting conflicts with _WIN32_WINNT setting
#endif
#endif

#ifndef _HRESULT_DEFINED
#define _HRESULT_DEFINED
typedef LONG HRESULT;
#endif // _HRESULT_DEFINED

#ifndef NOUSER


//
// Define API decoration for direct importing of DLL references.
//
#ifndef WINCOMMCTRLAPI
#if !defined(_COMCTL32_) && defined(_WIN32)
#define WINCOMMCTRLAPI DECLSPEC_IMPORT
#else
#define WINCOMMCTRLAPI
#endif
#endif // WINCOMMCTRLAPI

//
// For compilers that don't support nameless unions
//
#ifndef DUMMYUNIONNAME
#ifdef NONAMELESSUNION
#define DUMMYUNIONNAME          u
#define DUMMYUNIONNAME2         u2
#define DUMMYUNIONNAME3         u3
#else
#define DUMMYUNIONNAME
#define DUMMYUNIONNAME2
#define DUMMYUNIONNAME3
#endif
#endif // DUMMYUNIONNAME

#ifndef UNDER_CE
#ifdef _WIN32
#include <pshpack1.h>
#endif
#endif // !UNDER_CE

#ifdef __cplusplus
extern "C" {
#endif

//
// Users of this header may define any number of these constants to avoid
// the definitions of each functional group.
//
//    NOTOOLBAR    Customizable bitmap-button toolbar control.
//    NOUPDOWN     Up and Down arrow increment/decrement control.
//    NOSTATUSBAR  Status bar control.
//    NOMENUHELP   APIs to help manage menus, especially with a status bar.
//    NOTRACKBAR   Customizable column-width tracking control.
//    NODRAGLIST   APIs to make a listbox source and sink drag&drop actions.
//    NOPROGRESS   Progress gas gauge.
//    NOHOTKEY     HotKey control
//    NOHEADER     Header bar control.
//    NOIMAGEAPIS  ImageList apis.
//    NOLISTVIEW   ListView control.
//    NOTREEVIEW   TreeView control.
//    NOTABCONTROL Tab control.
//    NOANIMATE    Animate control.
//
//=============================================================================

#include <prsht.h>

#ifndef UNDER_CE
#ifndef SNDMSG
#ifdef __cplusplus
#define SNDMSG ::SendMessage
#else
#define SNDMSG SendMessage
#endif
#endif // ifndef SNDMSG
#else // UNDER_CE
#ifndef SNDMSG
#define SNDMSG SendMessage
#endif
#endif // !UNDER_CE

#ifdef UNDER_CE // Moved from pcommctr.h.
#define LVIS_ALL                0xFFFF
#endif //UNDER_CE

/**
 * This function registers and initializes the common control window classes. This function is
 * obsolete. New applications should use the InitCommonControlsEx function.
 *
 * @return None.
 */
WINCOMMCTRLAPI void WINAPI InitCommonControls(void);

#if (_WIN32_IE >= 0x0300)
typedef struct tagINITCOMMONCONTROLSEX {
    DWORD dwSize;             // size of this structure
    DWORD dwICC;              // flags indicating which classes to be initialized
} INITCOMMONCONTROLSEX, *LPINITCOMMONCONTROLSEX;
#define ICC_LISTVIEW_CLASSES 0x00000001 // listview, header
#define ICC_TREEVIEW_CLASSES 0x00000002 // treeview, tooltips
#define ICC_BAR_CLASSES      0x00000004 // toolbar, statusbar, trackbar, tooltips
#define ICC_TAB_CLASSES      0x00000008 // tab, tooltips
#define ICC_UPDOWN_CLASS     0x00000010 // updown
#define ICC_PROGRESS_CLASS   0x00000020 // progress
#define ICC_WIN95_CLASSES    0x000000FF
#define ICC_DATE_CLASSES     0x00000100 // month picker, date picker, time picker, updown
#define ICC_COOL_CLASSES     0x00000400 // rebar (coolbar) control
/**
 * This function registers specific common controls classes from the common control dynamic-link
 * library (DLL).
 *
 * @param lpInitCtrls Long pointer to an INITCOMMONCONTROLSEX structure that contains information
 *   specifying which control classes are registered.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * The effect of each call to InitCommonControlsEx is cumulative. For example, if
 * InitCommonControlsEx is called with the ICC_UPDOWN_CLASS flag, then is later called with the
 * ICC_HOTKEY_CLASS flag, the result is that both the up-down and hot key common control classes are
 * registered and available to the application.
 */
WINCOMMCTRLAPI BOOL WINAPI InitCommonControlsEx(LPINITCOMMONCONTROLSEX);
#endif      // _WIN32_IE >= 0x0300

#define ODT_HEADER              100
#define ODT_TAB                 101
#define ODT_LISTVIEW            102


//====== Ranges for control message IDs =======================================

#define LVM_FIRST               0x1000      // ListView messages
#define TV_FIRST                0x1100      // TreeView messages
#define HDM_FIRST               0x1200      // Header messages

//====== WM_NOTIFY Macros =====================================================

/**
 * This macro calls a function that processes the WM_NOTIFY message.
 *
 * @param hwnd Handle to the window that received WM_NOTIFY.
 * @param wParam First parameter of WM_NOTIFY.
 * @param lParam Second parameter of WM_NOTIFY.
 * @param fn Function that is to process WM_NOTIFY.
 *
 * @return The meaning of the value depends on the fn parameter.
 *
 * The HANDLE_WM_NOTIFY macro is defined as follows:
 *
 *     #define HANDLE_WM_NOTIFY(hwnd, wParam, lParam, fn) \
 *         (fn)((hwnd), (int)(wParam), (NMHDR FAR*)(lParam))
 */
#define HANDLE_WM_NOTIFY(hwnd, wParam, lParam, fn) \
    (fn)((hwnd), (int)(wParam), (NMHDR FAR*)(lParam))
/**
 * This macro sends or posts the WM_NOTIFY message.
 *
 * @param hwnd Handle to the window that receives the WM_NOTIFY message.
 * @param idFrom Identifier of the control sending the message.
 * @param pnmhdr Pointer to an NMHDR structure that contains the notification code and additional
 *   information. For some notification messages, this parameter points to a larger structure that has
 *   the NMHDR structure as its first member.
 * @param fn Function that sends or posts the WM_NOTIFY message. It can be either the SendMessage or
 *   PostMessage function.
 *
 * @return The meaning of the value depends on the fn parameter.
 *
 * The FORWARD_WM_NOTIFY macro is defined as follows:
 *
 *     #define FORWARD_WM_NOTIFY(hwnd, idFrom, pnmhdr, fn) \
 *         (void)(fn)((hwnd), WM_NOTIFY, (WPARAM)(int)(id), \
 *         (LPARAM)(NMHDR FAR*)(pnmhdr))
 */
#define FORWARD_WM_NOTIFY(hwnd, idFrom, pnmhdr, fn) \
    (LRESULT)(fn)((hwnd), WM_NOTIFY, (WPARAM)(int)(idFrom), (LPARAM)(NMHDR FAR*)(pnmhdr))


//====== Generic WM_NOTIFY notification codes =================================

#define NM_OUTOFMEMORY          (NM_FIRST-1)
/**
 * This notification message is sent by a list view control when the user clicks an item with the
 * left mouse button. It is sent in the form of a WM_NOTIFY message.
 *
 * @param lpnmlv Long pointer to an NMLISTVIEW structure that contains additional information about
 *   this notification message. The iItem, iSubItem and ptAction members of this structure contain
 *   information about the item.
 *
 * @return The return value for this notification is not used.
 *
 * This notification is identical to the standard NM_CLICK notification except that the list view
 * supplies a NMLISTVIEW structure instead of an NMHDR structure for the lParam.
 */
#define NM_CLICK                (NM_FIRST-2)
#define NM_DBLCLK               (NM_FIRST-3)
#define NM_RETURN               (NM_FIRST-4)
#define NM_RCLICK               (NM_FIRST-5)
#define NM_RDBLCLK              (NM_FIRST-6)
#define NM_SETFOCUS             (NM_FIRST-7)
#define NM_KILLFOCUS            (NM_FIRST-8)
#if (_WIN32_IE >= 0x0300)
/**
 * This notification message is sent by some common controls to notify their parent windows about
 * drawing operations. It is sent in the form of a WM_NOTIFY message.
 *
 * @param lpNMCustomDraw Long pointer to a Custom Draw-related structure that contains information
 *   about the drawing operation. List view controls use the NMLVCUSTOMDRAW structure, and all other
 *   supported controls use the NMCUSTOMDRAW structure.
 *
 * @return The value your application can return depends on the current drawing stage. The
 *   dwDrawStage member of the associated NMCUSTOMDRAW structure holds a value that specifies the
 *   drawing stage. You must return one of the following values. When dwDrawStage equals
 *   CDDS_PREPAINT: - CDRF_DODEFAULT: The control will draw itself. It will not send any additional
 *   NM_CUSTOMDRAW messages for this paint cycle. - CDRF_NOTIFYITEMDRAW: The control will notify the
 *   parent of any item-related drawing operations. It will send NM_CUSTOMDRAW notification messages
 *   before and after drawing items. - CDRF_NOTIFYITEMERASE: The control will notify the parent when
 *   an item will be erased. It will send NM_CUSTOMDRAW notification messages before and after erasing
 *   items. - CDRF_NOTIFYPOSTERASE: The control will notify the parent after erasing an item. -
 *   CDRF_NOTIFYPOSTPAINT: The control will notify the parent after painting an item. When dwDrawStage
 *   equals CDDS_ITEMPREPAINT: - CDRF_NEWFONT: Your application specified a new font for the item; the
 *   control will use the new font. For more information on changing fonts, see Changing Fonts And
 *   Colors. - CDRF_SKIPDEFAULT: Your application drew the item manually. The control will not draw
 *   the item.
 *
 * Currently header, list view, rebar, toolbar, trackbar, and tree view controls support Custom Draw
 * functionality.
 */
#define NM_CUSTOMDRAW           (NM_FIRST-12)
#define NM_HOVER                (NM_FIRST-13)
#endif
#if (_WIN32_IE >= 0x0400)
#define NM_NCHITTEST            (NM_FIRST-14)
/**
 * This notification message is sent by a control when the control has the keyboard focus and the
 * user presses a key. It is sent in the form of a WM_NOTIFY message.
 *
 * @param lpnmk Long pointer to an NMKEY structure that contains additional information about the
 *   key that caused the notification message.
 *
 * @return Return nonzero to prevent the control from processing the key or zero otherwise.
 *
 * This notification is not sent by all controls. Currently, only the toolbar sends this
 * notification.
 */
#define NM_KEYDOWN              (NM_FIRST-15)
#endif

#if (_WIN32_IE >= 0x0400)
//====== Generic WM_NOTIFY notification structures ============================

/**
 * This structure contains information used with mouse notification messages.
 */
typedef struct tagNMMOUSE {
    /**
     * Handle to a NMHDR structure that contains additional information about this notification.
     */
    NMHDR   hdr;
    /**
     * Specifies the control-specific item identifier.
     */
    DWORD   dwItemSpec;
    /**
     * Specifies control-specific item data.
     */
    DWORD   dwItemData;
    /**
     * POINT structure that contains the screen coordinates of the mouse when the click occurred.
     */
    POINT   pt;
} NMMOUSE, FAR* LPNMMOUSE;

typedef NMMOUSE NMCLICK;
typedef LPNMMOUSE LPNMCLICK;

// Generic structure for a key

/**
 * This structure contains information used with key notification messages.
 */
typedef struct tagNMKEY
{
    /**
     * Handle to a NMHDR structure that contains additional information about this notification.
     */
    NMHDR hdr;
    /**
     * Virtual key code of the key that caused the event.
     */
    WORD wVKey;
    /**
     * Flags associated with the key. These are the same flags that are passed in the high-order word of
     * the lParam in the WM_KEYDOWN message.
     */
    UINT flags;
} NMKEY, FAR *LPNMKEY;

#endif           // _WIN32_IE >= 0x0400

//====== WM_NOTIFY codes (NMHDR.code values) ==================================

#define NM_FIRST                (0U-  0U)       // generic to all controls
#define NM_LAST                 (0U- 99U)

#define LVN_FIRST               (0U-100U)       // listview
#define LVN_LAST                (0U-199U)

#define HDN_FIRST               (0U-300U)       // header
#define HDN_LAST                (0U-399U)

#define TVN_FIRST               (0U-400U)       // treeview
#define TVN_LAST                (0U-499U)

#define TTN_FIRST               (0U-520U)       // tooltips
#define TTN_LAST                (0U-549U)

#define TCN_FIRST               (0U-550U)       // tab control
#define TCN_LAST                (0U-580U)

// Shell reserved               (0U-580U) -  (0U-589U)

#define CDN_FIRST               (0U-601U)       // common dialog (new)
#define CDN_LAST                (0U-699U)

#define TBN_FIRST               (0U-700U)       // toolbar
#define TBN_LAST                (0U-720U)

#define UDN_FIRST               (0U-721)        // updown
#define UDN_LAST                (0U-740)
#if (_WIN32_IE >= 0x0300)
#define MCN_FIRST               (0U-750U)       // monthcal
#define MCN_LAST                (0U-759U)

#define DTN_FIRST               (0U-760U)       // datetimepick
#define DTN_LAST                (0U-799U)

#define RBN_FIRST               (0U-831U)       // rebar
#define RBN_LAST                (0U-859U)
#endif

#if (_WIN32_IE >= 0x0400)
#define SBN_FIRST               (0U-880U)        // status bar
#define SBN_LAST                (0U-900U)       
#endif

#define MSGF_COMMCTRL_BEGINDRAG     0x4200
#define MSGF_COMMCTRL_SIZEHEADER    0x4201
#define MSGF_COMMCTRL_DRAGSELECT    0x4202

#if (_WIN32_IE >= 0x0300)
//==================== CUSTOM DRAW ==========================================


// custom draw return flags
// values under 0x00010000 are reserved for global custom draw values.
// above that are for specific controls
#define CDRF_DODEFAULT          0x00000000
#define CDRF_NEWFONT            0x00000002
#define CDRF_SKIPDEFAULT        0x00000004


#define CDRF_NOTIFYPOSTPAINT    0x00000010
#define CDRF_NOTIFYITEMDRAW     0x00000020
#if (_WIN32_IE >= 0x0400)
#define CDRF_NOTIFYSUBITEMDRAW  0x00000020  // flags are the same, we can distinguish by context
#endif
#define CDRF_NOTIFYPOSTERASE    0x00000040



// drawstage flags
// values under 0x00010000 are reserved for global custom draw values.
// above that are for specific controls
#define CDDS_PREPAINT           0x00000001
#define CDDS_POSTPAINT          0x00000002
#define CDDS_PREERASE           0x00000003
#define CDDS_POSTERASE          0x00000004
// the 0x000010000 bit means it's individual item specific
#define CDDS_ITEM               0x00010000
#define CDDS_ITEMPREPAINT       (CDDS_ITEM | CDDS_PREPAINT)
#define CDDS_ITEMPOSTPAINT      (CDDS_ITEM | CDDS_POSTPAINT)
#define CDDS_ITEMPREERASE       (CDDS_ITEM | CDDS_PREERASE)
#define CDDS_ITEMPOSTERASE      (CDDS_ITEM | CDDS_POSTERASE)
#if (_WIN32_IE >= 0x0400)
#define CDDS_SUBITEM            0x00020000
#endif


// itemState flags
#define CDIS_SELECTED    0x0001
#define CDIS_GRAYED      0x0002
#define CDIS_DISABLED    0x0004
#define CDIS_CHECKED     0x0008
#define CDIS_FOCUS       0x0010
#define CDIS_DEFAULT     0x0020
#define CDIS_HOT         0x0040

/**
 * This structure contains information specific to an NM_CUSTOMDRAW notification message.
 */
typedef struct tagNMCUSTOMDRAWINFO
{
    /**
     * - Handle to a NMHDR structure that contains information about this notification message.
     */
    NMHDR hdr;
    /**
     * Specifies the current drawing stage. It is one of the following values.
     *
     * Global Drawstage values: Value Description CDDS_POSTERASE After the erasing cycle is complete.
     * CDDS_POSTPAINT After the painting cycle is complete. CDDS_PREERASE Before the erasing cycle
     * begins. CDDS_PREPAINT Before the painting cycle begins.
     *
     * Item-Specific Drawstage values: Value Description CDDS_ITEM Indicates that the dwItemSpec,
     * uItemState, and lItemParam members are valid. CDDS_ITEMPOSTERASE After an item has been erased
     * CDDS_ITEMPOSTPAINT After an item has been drawn CDDS_ITEMPREERASE Before an item is erased
     * CDDS_ITEMPREPAINT Before an item is drawn
     */
    DWORD dwDrawStage;
    /**
     * Handle to the control's device context. Use this HDC to perform any GDI functions.
     */
    HDC hdc;
    /**
     * RECT structure that describes the bounding rectangle of the area being drawn.
     */
    RECT rc;
    /**
     * Specifies the item number. This value is control specific, using the item-referencing convention
     * for that control. Additionally, trackbar controls use the following values to identify portions
     * of control: Value Description TBCD_CHANNEL Identifies the channel that the trackbar control's
     * thumb marker slides along. TBCD_THUMB Identifies the trackbar control's thumb marker. This is the
     * portion of the control that the user moves. TBCD_TICS Identifies the increment tic marks that
     * appear along the edge of the trackbar control.
     */
    DWORD dwItemSpec;  // this is control specific, but it's how to specify an item.  valid only with CDDS_ITEM bit set
    /**
     * Specifies the current item state. It can be a combination of the following values: Value
     * Description CDIS_CHECKED The item is checked. CDIS_DEFAULT The item is in its default state.
     * CDIS_DISABLED The item is disabled. CDIS_FOCUS The item is in focus. CDIS_GRAYED The item is
     * grayed. CDIS_HOT The item is currently under the pointer ("hot"). CDIS_SELECTED The item is
     * selected.
     */
    UINT  uItemState;
    /**
     * Application-defined item data.
     */
    LPARAM lItemlParam;
} NMCUSTOMDRAW, FAR * LPNMCUSTOMDRAW;



// for tooltips

typedef struct tagNMTTCUSTOMDRAW
{
    NMCUSTOMDRAW nmcd;
    UINT uDrawFlags;
} NMTTCUSTOMDRAW, FAR * LPNMTTCUSTOMDRAW;

#endif      // _WIN32_IE >= 0x0300


//====== IMAGE APIS ===========================================================

#ifndef NOIMAGEAPIS

#define CLR_NONE                0xFFFFFFFFL
#define CLR_DEFAULT             0xFF000000L

struct _IMAGELIST;
typedef struct _IMAGELIST NEAR* HIMAGELIST;

#if (_WIN32_IE >= 0x0300)
/**
 * This structure contains information about an image list draw operation and is used with the
 * ImageList_DrawIndirect function.
 *
 * An overlay image is an image that is drawn on top of the primary image specified in the i member
 * of this structure. To specify an overlay image, logically OR the fStyle member with the
 * INDEXTOOVERLAYMASK macro, passing the one-based index of the overlay image in the macro. This
 * image must have been previously specified as an overlay image using the ImageList_SetOverlayImage
 * API.
 *
 * To extract the overlay image from the fStyle member, use the logical AND to combine fStyle with
 * the ILD_OVERLAYMASK value.
 */
typedef struct _IMAGELISTDRAWPARAMS {
    /**
     * Size of this structure, in bytes.
     */
    DWORD       cbSize;
    /**
     * Handle to the image list that contains the image to be drawn.
     */
    HIMAGELIST  himl;
    /**
     * Zero-based index of the image to be drawn.
     */
    int         i;
    /**
     * Handle to the destination device context.
     */
    HDC         hdcDst;
    int         x;
    int         y;
    int         cx;
    int         cy;
    int         xBitmap;        // x offest from the upperleft of bitmap
    int         yBitmap;        // y offset from the upperleft of bitmap
    /**
     * Image background color. It can be an application-defined RGB value or one of the following
     * values: Value Description CLR_DEFAULT Default background color. The image is drawn using the
     * image list background color. CLR_NONE No background color. The image is drawn transparently.
     *
     * This parameter is used only if the image list identified by himl was created with the ILC_MASK
     * value.
     */
    COLORREF    rgbBk;
    /**
     * Image foreground color. It is an application-defined RGB value or one of the following values:
     * Value Description CLR_DEFAULT Default foreground color. The image is drawn using the system
     * highlight color as the foreground color. CLR_NONE No blend color. The image is blended with the
     * color of the destination device context.
     *
     * This parameter is used only if fStyle includes the ILD_BLEND25 or ILD_BLEND50 flag.
     */
    COLORREF    rgbFg;
    /**
     * Flag that specifies the drawing style and, optionally, the overlay image. It can be a combination
     * of one or more of the following values: Value Description ILD_BLEND25 Draws the image, blending
     * 25 percent with the blend color specified by rgbFg. This value has no effect if the image list
     * does not contain a mask. ILD_FOCUS Same as ILD_BLEND25. ILD_BLEND50 Draws the image, blending 50
     * percent with the blend color specified by rgbFg. This value has no effect if the image list does
     * not contain a mask. ILD_SELECTED Same as ILD_BLEND50. ILD_BLEND Same as ILD_BLEND50. ILD_MASK
     * Draws the mask. ILD_NORMAL Draws the image using the background color for the image list. If the
     * background color is the CLR_NONE value, the image is drawn transparently using the mask. ILD_ROP
     * Draws the image using the raster-operation code specified by the dwRop member. ILD_TRANSPARENT
     * Draws the image transparently using the mask, regardless of the background color. This value has
     * no effect if the image list does not contain a mask.
     */
    UINT        fStyle;
    /**
     * Specifies a raster-operation code. These codes define how the color data for the source rectangle
     * will be combined with the color data for the destination rectangle to achieve the final color.
     * This member is ignored if the fStyle member does not include the ILD_ROP flag.
     *
     * Some common raster operation codes are listed below: Value Description BLACKNESS Fills the
     * destination rectangle using the color associated with index 0 in the physical palette. (This
     * color is black for the default physical palette.) DSTINVERT Inverts the destination rectangle.
     * MERGECOPY Merges the source rectangle colors with the specified pattern by using the Boolean AND
     * operator. MERGEPAINT Merges the inverted source rectangle colors with the destination rectangle
     * colors by using the Boolean OR operator. NOTSRCCOPY Copies the inverted source rectangle to the
     * destination. NOTSRCERASE Combines the source and destination rectangle colors by using the
     * Boolean OR operator. Inverts the resultant color. PATCOPY Copies the specified pattern into the
     * destination bitmap. PATINVERT Combines the specified pattern colors with the destination
     * rectangle colors by using the Boolean XOR operator. PATPAINT Combines the pattern colors with the
     * inverted source rectangle colors by using the Boolean OR operator. Combines the result with the
     * destination rectangle colors by using the Boolean OR operator. SRCAND Combines the source and
     * destination rectangle colors by using the Boolean AND operator. SRCCOPY Copies the source
     * rectangle directly to the destination rectangle. SRCERASE Combines the destination rectangle's
     * inverted colors with the source rectangle colors by using the Boolean AND operator. SRCINVERT
     * Combines the source and destination rectangle colors by using the Boolean XOR operator. SRCPAINT
     * Combines the source and destination rectangle colors by using the Boolean OR operator. WHITENESS
     * Fills the destination rectangle using the color associated with index 1 in the physical palette.
     * (This color is white for the default physical palette.)
     */
    DWORD       dwRop;
} IMAGELISTDRAWPARAMS, FAR * LPIMAGELISTDRAWPARAMS;
#endif      // _WIN32_IE >= 0x0300

#define ILC_MASK                0x0001
#define ILC_COLOR               0x0000
#define ILC_COLORDDB            0x00FE
#define ILC_PALETTE             0x0800      // (no longer supported...never worked anyway)


/**
 * This function creates a new image list.
 *
 * @param cx [in] Width, in pixels, of each image.
 * @param cy [in] Height, in pixels, of each image.
 * @param flags [in] Set of bit flags that specify the type of image list to create. This parameter
 *   can be a combination of the following values, but it can include only one of the ILC_COLOR
 *   values. Value Description ILC_COLOR Use the default behavior if none of the other ILC_COLOR*
 *   flags is specified. Typically, the default is ILC_COLOR4, but for older display drivers, the
 *   default is ILC_COLORDDB. ILC_COLORDDB Use a device-dependent bitmap. ILC_MASK Use a mask. The
 *   image list contains two bitmaps, one of which is a monochrome bitmap used as a mask. If this
 *   value is not included, the image list contains only one bitmap.
 * @param cInitial [in] Number of images that the image list initially contains.
 * @param cGrow [in] Number of images by which the image list can grow when the system needs to make
 *   room for new images. This parameter represents the number of new images that the resized image
 *   list can contain.
 *
 * @return The handle to the image list indicates success. NULL indicates failure.
 */
WINCOMMCTRLAPI HIMAGELIST  WINAPI ImageList_Create(int cx, int cy, UINT flags, int cInitial, int cGrow);
/**
 * This function destroys an image list.
 *
 * @param himl [in] Handle to the image list to destroy.
 *
 * @return Nonzero indicates success. Zero indicates failure.
 */
WINCOMMCTRLAPI BOOL        WINAPI ImageList_Destroy(HIMAGELIST himl);
/**
 * This function retrieves the number of images in an image list.
 *
 * @param himl [in] Handle to the image list.
 *
 * @return The number of images indicates success. NULL indicates failure.
 */
WINCOMMCTRLAPI int         WINAPI ImageList_GetImageCount(HIMAGELIST himl);
#if (_WIN32_IE >= 0x0300)
/**
 * This function resizes an existing image list.
 *
 * @param himl [in] Handle to the image list that is resized.
 * @param uNewCount [in] Value specifying the new size of the image list.
 *
 * @return Nonzero indicates success. Zero indicates failure.
 *
 * If you expand an image list using the ImageList_SetImageCount function, you must add new images
 * by using the ImageList_Replace function. If you do not add valid images at the new indexes, draw
 * operations that use the new indexes will be unpredictable.
 *
 * If you decrease the size of an image list by using this function, the truncated images are freed.
 */
WINCOMMCTRLAPI BOOL        WINAPI ImageList_SetImageCount(HIMAGELIST himl, UINT uNewCount);
#endif
/**
 * This function adds an image or images to an image list.
 *
 * @param himl [in] Handle to the image list.
 * @param hbmImage [in] Handle to the bitmap that contains the image or images. The number of images
 *   is inferred from the width of the bitmap.
 * @param hbmMask [in] Handle to the bitmap that contains the mask. If no mask is used with the
 *   image list, this parameter is ignored.
 *
 * @return The index of the first new image indicates success. -1 indicates failure.
 *
 * The ImageList_Add function copies the bitmap to an internal data structure. Be sure to use the
 * DeleteObject function to delete hbmImage and hbmMask after the function returns.
 */
WINCOMMCTRLAPI int         WINAPI ImageList_Add(HIMAGELIST himl, HBITMAP hbmImage, HBITMAP hbmMask);
/**
 * This function replaces an image with an icon.
 *
 * @param himl [in] Handle to the image list.
 * @param i [in] Index of the image to replace. If i is -1, the function appends the image to the
 *   end of the list.
 * @param hicon [in] Handle to the icon that contains the bitmap and mask for the new image.
 *
 * @return The index of the image indicates success. -1 indicates failure.
 *
 * Because the system does not save hicon, you can destroy it after the function returns if the icon
 * was created by the CreateIcon function. You do not need to destroy hicon if it was loaded by the
 * LoadIcon function; the system automatically frees an icon resource when it is no longer needed.
 *
 * You can only use the ImageList_ReplaceIcon function with icons, not cursors.
 */
WINCOMMCTRLAPI int         WINAPI ImageList_ReplaceIcon(HIMAGELIST himl, int i, HICON hicon);
/**
 * This function sets the background color for an image list.
 *
 * @param himl [in] Handle to the image list.
 * @param clrBk [in] Background color to set. This parameter can be the CLR_NONE value; in that
 *   case, images are drawn transparently using the mask.
 *
 * @return The previous background color indicates success. CLR_NONE indicates failure.
 */
WINCOMMCTRLAPI COLORREF    WINAPI ImageList_SetBkColor(HIMAGELIST himl, COLORREF clrBk);
/**
 * This function retrieves the current background color for an image list.
 *
 * @param himl [in] Handle to the image list.
 *
 * @return The background color indicates success. NULL indicates failure.
 */
WINCOMMCTRLAPI COLORREF    WINAPI ImageList_GetBkColor(HIMAGELIST himl);
/**
 * This function adds a specified image to the list of images to be used as overlay masks. An image
 * list can have up to four overlay masks. The function assigns an overlay mask index to the
 * specified image.
 *
 * @param himl [in] Handle to the image list.
 * @param iImage [in] Zero-based index of an image in the himl image list. This index identifies the
 *   image to use as an overlay mask.
 * @param iOverlay [in] One-based index of the overlay mask.
 *
 * @return Nonzero indicates success. Zero indicates failure.
 *
 * An overlay mask is an image drawn transparently over another image. To draw an overlay mask over
 * an image, call the ImageList_Draw or ImageList_DrawEx function. The fStyle parameter of these
 * functions can use the INDEXTOOVERLAYMASK macro to specify an overlay mask index.
 */
WINCOMMCTRLAPI BOOL        WINAPI ImageList_SetOverlayImage(HIMAGELIST himl, int iImage, int iOverlay);

/**
 * This macro adds an icon to an image list. ImageList_AddIcon calls the ImageList_ReplaceIcon
 * function.
 *
 * @param himl Handle to the image list. If this parameter identifies a masked image list, the macro
 *   copies both the image and mask bitmaps of the icon or cursor. If this parameter identifies a
 *   nonmasked image list, the macro copies only the image bitmap.
 * @param hicon Handle to the icon or cursor that contains the bitmap and mask for the new image.
 *
 * @return The index of the new image indicates success. -1 indicates failure.
 *
 * In Windows CE, you can only use this macro with icons, not cursors.
 *
 * Because the system does not save hicon, you can destroy it after the macro returns if the icon
 * was created by the CreateIcon function. You do not need to destroy hicon if it was loaded by the
 * LoadIcon function; the system automatically frees an icon resource when it is no longer needed.
 *
 * The ImageList_AddIcon macro is defined as follows:
 *
 *     #define ImageList_AddIcon(himl, hicon) ImageList_ReplaceIcon(himl, -1, hicon)
 */
#define     ImageList_AddIcon(himl, hicon) ImageList_ReplaceIcon(himl, -1, hicon)

#define ILD_NORMAL              0x0000
#define ILD_TRANSPARENT         0x0001
#define ILD_MASK                0x0010
#define ILD_IMAGE               0x0020
#if (_WIN32_IE >= 0x0300)
#define ILD_ROP                 0x0040
#endif
#define ILD_BLEND25             0x0002
#define ILD_BLEND50             0x0004
#define ILD_OVERLAYMASK         0x0F00
/**
 * This macro prepares the index of an overlay mask so that the ImageList_Draw or ImageList_DrawEx
 * function can use it.
 *
 * @param iOverlay Index of an overlay mask.
 *
 * The INDEXTOOVERLAYMASK macro is defined as follows:
 *
 *     #define INDEXTOOVERLAYMASK(i) ((i) << 8)
 */
#define INDEXTOOVERLAYMASK(i)   ((i) << 8)

#define ILD_SELECTED            ILD_BLEND50
#define ILD_FOCUS               ILD_BLEND25
#define ILD_BLEND               ILD_BLEND50
#define CLR_HILIGHT             CLR_DEFAULT

/**
 * This function draws an image list item in the specified device context (DC).
 *
 * @param himl [in] Handle to the image list.
 * @param i [in] Index of the image to draw.
 * @param hdcDst [in] Handle to the destination device context.
 * @param x [in] Specifies the x-coordinate at which to draw within the specified device context.
 * @param y [in] Specifies the y-coordinate at which to draw within the specified device context.
 * @param fStyle [in] Specifies the drawing style and, optionally, the overlay image. For
 *   information about specifying an overlay image index, see the comments section at the end of this
 *   topic. This parameter can be a combination of an overlay image index and one or more of the
 *   following values: Value Description ILD_BLEND25, ILD_FOCUS Draws the image, blending 25 percent
 *   with the system highlight color. This value has no effect if the image list does not contain a
 *   mask. ILD_BLEND50, ILD_SELECTED, ILD_BLEND Draws the image, blending 50 percent with the system
 *   highlight color. This value has no effect if the image list does not contain a mask. ILD_MASK
 *   Draws the mask. ILD_NORMAL Draws the image using the background color for the image list. If the
 *   background color is the CLR_NONE value, the image is drawn transparently using the mask.
 *   ILD_TRANSPARENT Draws the image transparently using the mask, regardless of the background color.
 *   This value has no effect if the image list does not contain a mask.
 *
 * @return Nonzero indicates success. Zero indicates failure.
 *
 * An overlay image is drawn transparently over the primary image specified in the i parameter. To
 * specify an overlay image in the fStyle parameter, use the INDEXTOOVERLAYMASK macro to shift the
 * one-based index of the overlay image. Use the OR operator to logically combine the return value
 * of the macro with the drawing style flags specified in the fStyle parameter. You must first
 * specify this image as an overlay image by using the ImageList_SetOverlayImage function.
 */
WINCOMMCTRLAPI BOOL WINAPI ImageList_Draw(HIMAGELIST himl, int i, HDC hdcDst, int x, int y, UINT fStyle);


#ifdef _WIN32

/**
 * This function replaces an image in an image list with a new image.
 *
 * @param himl [in] Handle to the image list.
 * @param i [in] Index of the image to replace.
 * @param hbmImage [in] Handle to the bitmap that contains the image.
 * @param hbmMask [in] Handle to the bitmap that contains the mask. If no mask is used with the
 *   image list, this parameter is ignored.
 *
 * @return Nonzero indicates success. Zero indicates failure.
 *
 * The ImageList_Replace function copies the bitmap to an internal data structure. Be sure to use
 * the DeleteObject function to delete hbmImage and hbmMask after the function returns.
 */
WINCOMMCTRLAPI BOOL        WINAPI ImageList_Replace(HIMAGELIST himl, int i, HBITMAP hbmImage, HBITMAP hbmMask);
/**
 * This function adds an image or images to an image list, generating a mask from the specified
 * bitmap.
 *
 * @param himl [in] Handle to the image list.
 * @param hbmImage [in] Handle to the bitmap that contains one or more images. The number of images
 *   is inferred from the width of the bitmap.
 * @param crMask [in] Color used to generate the mask. Each pixel of this color in the specified
 *   bitmap is changed to black, and the corresponding bit in the mask is set to 1.
 *
 * @return The index of the first new image indicates success. -1 indicates failure.
 *
 * The ImageList_AddMasked function copies the bitmap to an internal data structure. Be sure to use
 * the DeleteObject function to delete hbmImage and crMask after the function returns.
 */
WINCOMMCTRLAPI int         WINAPI ImageList_AddMasked(HIMAGELIST himl, HBITMAP hbmImage, COLORREF crMask);
/**
 * This function draws an image list item in the specified device context (DC). ImageList_DrawEx
 * uses the specified drawing style and blends the image with the specified color.
 *
 * @param himl [in] Handle to the image list.
 * @param i [in] Index of the image to draw.
 * @param hdcDst [in] Handle to the destination device context.
 * @param x [in] Specifies the x-coordinate at which to draw within the specified device context.
 * @param y [in] Specifies the y-coordinate at which to draw within the specified device context.
 * @param dx [in] Specifies the width of the portion of the image to draw relative to the upper-left
 *   corner of the image. If dx and dy are zero, the function draws the entire image. The function
 *   does not ensure that the parameters are valid.
 * @param dy [in] Specifies the height of the portion of the image to draw, relative to the
 *   upper-left corner of the image. If dx and dy are zero, the function draws the entire image. The
 *   function does not ensure that the parameters are valid.
 * @param rgbBk [in] Background color of the image. This parameter can be an application-defined RGB
 *   value or one of the following values: Value Description CLR_NONE No background color. The image
 *   is drawn transparently. CLR_DEFAULT Default background color. The image is drawn using the
 *   background color of the image list. This parameter is used only if the image list identified by
 *   himl was created with the ILC_MASK value.
 * @param rgbFg [in] Foreground color of the image. This parameter can be an application-defined RGB
 *   value or one of the following values: Value Description CLR_NONE No blend color. The image is
 *   blended with the color of the destination device context. CLR_DEFAULT Default foreground color.
 *   The image is drawn using the system highlight color as the foreground color. This parameter is
 *   used only if fStyle includes the ILD_BLEND25 or ILD_BLEND50 value.
 * @param fStyle [in] Specifies the drawing style and, optionally, the overlay image. For
 *   information about specifying an overlay image index, see the comments section at the end of this
 *   topic. This parameter can be a combination of an overlay image index and one or more of the
 *   following values: Value Description ILD_BLEND25, ILD_FOCUS Draws the image, blending 25 percent
 *   with the blend color specified by rgbFG. This value has no effect if the image list does not
 *   contain a mask. ILD_BLEND50, ILD_SELECTED, ILD_BLEND Draws the image, blending 50 percent with
 *   the blend color specified by rgbFG. This value has no effect if the image list does not contain a
 *   mask. ILD_MASK Draws the mask. ILD_NORMAL Draws the image using the background color for the
 *   image list. If the background color is the CLR_NONE value, the image is drawn transparently using
 *   the mask. ILD_TRANSPARENT Draws the image transparently using the mask, regardless of the
 *   background color. This value has no effect if the image list does not contain a mask.
 *
 * @return Nonzero indicates success. Zero indicates failure.
 *
 * An overlay image is drawn transparently over the primary image specified in the i parameter. To
 * specify an overlay image in the fStyle parameter, use the INDEXTOOVERLAYMASK macro to shift the
 * one-based index of the overlay image. Use the OR operator to logically combine the return value
 * of the macro with the drawing style flags specified in the fStyle parameter. You must first
 * specify this image as an overlay image by using the ImageList_SetOverlayImage function.
 */
WINCOMMCTRLAPI BOOL        WINAPI ImageList_DrawEx(HIMAGELIST himl, int i, HDC hdcDst, int x, int y, int dx, int dy, COLORREF rgbBk, COLORREF rgbFg, UINT fStyle);
#if (_WIN32_IE >= 0x0300)
/**
 * This function draws an image list image based on an IMAGELISTDRAWPARAMS structure.
 *
 * @param pimldp [in] Pointer to an IMAGELISTDRAWPARAMS structure that contains information about
 *   the draw operation.
 *
 * @return Nonzero indicates success. Zero indicates failure.
 */
WINCOMMCTRLAPI BOOL        WINAPI ImageList_DrawIndirect(IMAGELISTDRAWPARAMS* pimldp);
#endif
/**
 * This function removes an image from an image list.
 *
 * @param himl [in] Handle to the image list.
 * @param i [in] Index of the image to remove. If this parameter is -1, the function removes all
 *   images.
 *
 * @return Nonzero indicates success. Zero indicates failure.
 *
 * When an image is removed, the indexes of the remaining images are adjusted so that the image
 * indexes always range from zero to one less than the number of images in the image list. For
 * example, if you remove the image at index 0, then image 1 becomes image 0, image 2 becomes image
 * 1, and so on.
 */
WINCOMMCTRLAPI BOOL        WINAPI ImageList_Remove(HIMAGELIST himl, int i);
/**
 * This function creates an icon from an image and mask in an image list.
 *
 * @param himl [in] Handle to the image list.
 * @param i [in] Index of the image.
 * @param flags [in] Combination of flags that specify the drawing style. For a list of values, see
 *   the description of the ImageList_Draw function.
 *
 * @return The handle to the icon indicates success. NULL indicates failure.
 *
 * It is the responsibility of the calling application to destroy the icon returned from this
 * function using the DestroyIcon function.
 *
 * You can only use the ImageList_GetIcon function to create an icon, not a cursor.
 */
WINCOMMCTRLAPI HICON       WINAPI ImageList_GetIcon(HIMAGELIST himl, int i, UINT flags);

#ifndef UNDER_CE // The W&A versions of this function did not exist in previous versions.
                 // WinCE only supports the Unicode version.
/**
 * This function creates an image list from the specified bitmap or icon resource.
 *
 * @param hi [in] Handle to the instance of an application or DLL that contains an image.
 * @param lpbmp [in] Long pointer to the image to load. If the uFlags parameter includes
 *   LR_LOADFROMFILE, lpbmp is the address of a null-terminated string that names the file containing
 *   the image to load. If the hi parameter is non-NULL and LR_LOADFROMFILE is not specified, lpbmp is
 *   the address of a null-terminated string that contains the name of the image resource in the hi
 *   module. If hi is NULL and LR_LOADFROMFILE is not specified, the low-order word of this parameter
 *   must be the identifier of an OEM image to load. To create this value, use the MAKEINTRESOURCE
 *   macro with one of the OEM image identifiers defined in Winuser.h. These identifiers have the
 *   following prefixes: OBM_ for OEM bitmaps OIC_ for OEM icons
 * @param cx [in] Width of each image. The height of each image and the initial number of images are
 *   inferred by the dimensions of the specified resource.
 * @param cGrow [in] Number of images by which the image list can grow when the system needs to make
 *   room for new images. This parameter represents the number of new images that the resized image
 *   list can contain.
 * @param crMask [in] Color used to generate a mask. Each pixel of this color in the specified
 *   bitmap or icon is changed to black, and the corresponding bit in the mask is set to 1. If this
 *   parameter is the CLR_NONE value, no mask is generated. If this parameter is the CLR_DEFAULT
 *   value, the color of the pixel at the upper-left corner of the image is treated as the mask color.
 * @param uType [in] Flag that specifies the type of image to load. This parameter can be one of the
 *   following values: Value Description IMAGE_BITMAP Loads a bitmap. IMAGE_ICON Loads an icon.
 * @param uFlags [in] Unsupported; set to 0.
 *
 * @return The handle to the image list indicates success. NULL indicates failure.
 *
 * You can only use this function with icons, not cursors.
 */
WINCOMMCTRLAPI HIMAGELIST  WINAPI ImageList_LoadImageA(HINSTANCE hi, LPCSTR lpbmp, int cx, int cGrow, COLORREF crMask, UINT uType, UINT uFlags);
/**
 * This function creates an image list from the specified bitmap or icon resource.
 *
 * @param hi [in] Handle to the instance of an application or DLL that contains an image.
 * @param lpbmp [in] Long pointer to the image to load. If the uFlags parameter includes
 *   LR_LOADFROMFILE, lpbmp is the address of a null-terminated string that names the file containing
 *   the image to load. If the hi parameter is non-NULL and LR_LOADFROMFILE is not specified, lpbmp is
 *   the address of a null-terminated string that contains the name of the image resource in the hi
 *   module. If hi is NULL and LR_LOADFROMFILE is not specified, the low-order word of this parameter
 *   must be the identifier of an OEM image to load. To create this value, use the MAKEINTRESOURCE
 *   macro with one of the OEM image identifiers defined in Winuser.h. These identifiers have the
 *   following prefixes: OBM_ for OEM bitmaps OIC_ for OEM icons
 * @param cx [in] Width of each image. The height of each image and the initial number of images are
 *   inferred by the dimensions of the specified resource.
 * @param cGrow [in] Number of images by which the image list can grow when the system needs to make
 *   room for new images. This parameter represents the number of new images that the resized image
 *   list can contain.
 * @param crMask [in] Color used to generate a mask. Each pixel of this color in the specified
 *   bitmap or icon is changed to black, and the corresponding bit in the mask is set to 1. If this
 *   parameter is the CLR_NONE value, no mask is generated. If this parameter is the CLR_DEFAULT
 *   value, the color of the pixel at the upper-left corner of the image is treated as the mask color.
 * @param uType [in] Flag that specifies the type of image to load. This parameter can be one of the
 *   following values: Value Description IMAGE_BITMAP Loads a bitmap. IMAGE_ICON Loads an icon.
 * @param uFlags [in] Unsupported; set to 0.
 *
 * @return The handle to the image list indicates success. NULL indicates failure.
 *
 * You can only use this function with icons, not cursors.
 */
WINCOMMCTRLAPI HIMAGELIST  WINAPI ImageList_LoadImageW(HINSTANCE hi, LPCWSTR lpbmp, int cx, int cGrow, COLORREF crMask, UINT uType, UINT uFlags);

#ifdef UNICODE
/**
 * This function creates an image list from the specified bitmap or icon resource.
 *
 * @param hi [in] Handle to the instance of an application or DLL that contains an image.
 * @param lpbmp [in] Long pointer to the image to load. If the uFlags parameter includes
 *   LR_LOADFROMFILE, lpbmp is the address of a null-terminated string that names the file containing
 *   the image to load. If the hi parameter is non-NULL and LR_LOADFROMFILE is not specified, lpbmp is
 *   the address of a null-terminated string that contains the name of the image resource in the hi
 *   module. If hi is NULL and LR_LOADFROMFILE is not specified, the low-order word of this parameter
 *   must be the identifier of an OEM image to load. To create this value, use the MAKEINTRESOURCE
 *   macro with one of the OEM image identifiers defined in Winuser.h. These identifiers have the
 *   following prefixes: OBM_ for OEM bitmaps OIC_ for OEM icons
 * @param cx [in] Width of each image. The height of each image and the initial number of images are
 *   inferred by the dimensions of the specified resource.
 * @param cGrow [in] Number of images by which the image list can grow when the system needs to make
 *   room for new images. This parameter represents the number of new images that the resized image
 *   list can contain.
 * @param crMask [in] Color used to generate a mask. Each pixel of this color in the specified
 *   bitmap or icon is changed to black, and the corresponding bit in the mask is set to 1. If this
 *   parameter is the CLR_NONE value, no mask is generated. If this parameter is the CLR_DEFAULT
 *   value, the color of the pixel at the upper-left corner of the image is treated as the mask color.
 * @param uType [in] Flag that specifies the type of image to load. This parameter can be one of the
 *   following values: Value Description IMAGE_BITMAP Loads a bitmap. IMAGE_ICON Loads an icon.
 * @param uFlags [in] Unsupported; set to 0.
 *
 * @return The handle to the image list indicates success. NULL indicates failure.
 *
 * You can only use this function with icons, not cursors.
 */
#define ImageList_LoadImage     ImageList_LoadImageW
#else
/**
 * This function creates an image list from the specified bitmap or icon resource.
 *
 * @param hi [in] Handle to the instance of an application or DLL that contains an image.
 * @param lpbmp [in] Long pointer to the image to load. If the uFlags parameter includes
 *   LR_LOADFROMFILE, lpbmp is the address of a null-terminated string that names the file containing
 *   the image to load. If the hi parameter is non-NULL and LR_LOADFROMFILE is not specified, lpbmp is
 *   the address of a null-terminated string that contains the name of the image resource in the hi
 *   module. If hi is NULL and LR_LOADFROMFILE is not specified, the low-order word of this parameter
 *   must be the identifier of an OEM image to load. To create this value, use the MAKEINTRESOURCE
 *   macro with one of the OEM image identifiers defined in Winuser.h. These identifiers have the
 *   following prefixes: OBM_ for OEM bitmaps OIC_ for OEM icons
 * @param cx [in] Width of each image. The height of each image and the initial number of images are
 *   inferred by the dimensions of the specified resource.
 * @param cGrow [in] Number of images by which the image list can grow when the system needs to make
 *   room for new images. This parameter represents the number of new images that the resized image
 *   list can contain.
 * @param crMask [in] Color used to generate a mask. Each pixel of this color in the specified
 *   bitmap or icon is changed to black, and the corresponding bit in the mask is set to 1. If this
 *   parameter is the CLR_NONE value, no mask is generated. If this parameter is the CLR_DEFAULT
 *   value, the color of the pixel at the upper-left corner of the image is treated as the mask color.
 * @param uType [in] Flag that specifies the type of image to load. This parameter can be one of the
 *   following values: Value Description IMAGE_BITMAP Loads a bitmap. IMAGE_ICON Loads an icon.
 * @param uFlags [in] Unsupported; set to 0.
 *
 * @return The handle to the image list indicates success. NULL indicates failure.
 *
 * You can only use this function with icons, not cursors.
 */
#define ImageList_LoadImage     ImageList_LoadImageA
#endif

#else  // UNDER_CE
/**
 * This function creates an image list from the specified bitmap or icon resource.
 *
 * @param hi [in] Handle to the instance of an application or DLL that contains an image.
 * @param lpbmp [in] Long pointer to the image to load. If the uFlags parameter includes
 *   LR_LOADFROMFILE, lpbmp is the address of a null-terminated string that names the file containing
 *   the image to load. If the hi parameter is non-NULL and LR_LOADFROMFILE is not specified, lpbmp is
 *   the address of a null-terminated string that contains the name of the image resource in the hi
 *   module. If hi is NULL and LR_LOADFROMFILE is not specified, the low-order word of this parameter
 *   must be the identifier of an OEM image to load. To create this value, use the MAKEINTRESOURCE
 *   macro with one of the OEM image identifiers defined in Winuser.h. These identifiers have the
 *   following prefixes: OBM_ for OEM bitmaps OIC_ for OEM icons
 * @param cx [in] Width of each image. The height of each image and the initial number of images are
 *   inferred by the dimensions of the specified resource.
 * @param cGrow [in] Number of images by which the image list can grow when the system needs to make
 *   room for new images. This parameter represents the number of new images that the resized image
 *   list can contain.
 * @param crMask [in] Color used to generate a mask. Each pixel of this color in the specified
 *   bitmap or icon is changed to black, and the corresponding bit in the mask is set to 1. If this
 *   parameter is the CLR_NONE value, no mask is generated. If this parameter is the CLR_DEFAULT
 *   value, the color of the pixel at the upper-left corner of the image is treated as the mask color.
 * @param uType [in] Flag that specifies the type of image to load. This parameter can be one of the
 *   following values: Value Description IMAGE_BITMAP Loads a bitmap. IMAGE_ICON Loads an icon.
 * @param uFlags [in] Unsupported; set to 0.
 *
 * @return The handle to the image list indicates success. NULL indicates failure.
 *
 * You can only use this function with icons, not cursors.
 */
WINCOMMCTRLAPI HIMAGELIST  WINAPI ImageList_LoadImage(HINSTANCE hi, LPCTSTR lpbmp, int cx, int cGrow, COLORREF crMask, UINT uType, UINT uFlags);
#endif // !UNDER_CE

#if (_WIN32_IE >= 0x0300)
#define ILCF_MOVE   (0x00000000)
#define ILCF_SWAP   (0x00000001)
/**
 * This function copies images within a specified image list.
 *
 * @param himlDst and himlSrc [in] Handle to an image list that is the target of the copy operation.
 *   Both parameters must be identical.
 * @param iDst [in] Zero-based index of the image to be used as the destination of the copy
 *   operation.
 * @param iSrc [in] Zero-based index of the image to be used as the source of the copy operation.
 * @param uFlags [in] Bit flag value that specifies the type of copy operation to be made. This
 *   parameter can be one of the following values: Value Description ILCF_MOVE The source image is
 *   copied to the destination image's index. This operation results in multiple instances of a given
 *   image. ILCF_SWAP The source and destination images exchange positions within the image list.
 *
 * @return Nonzero indicates success. Zero indicates failure.
 */
WINCOMMCTRLAPI BOOL        WINAPI ImageList_Copy(HIMAGELIST himlDst, int iDst, HIMAGELIST himlSrc, int iSrc, UINT uFlags);
#endif

/**
 * This function begins dragging an image.
 *
 * @param himlTrack [in] Handle to the image list.
 * @param iTrack [in] Index of the image to drag.
 * @param dxHotspot and dyHotspot [in] Specifies the location of the drag position relative to the
 *   upper-left corner of the image.
 *
 * @return Nonzero indicates success. Zero indicates failure.
 *
 * This function creates a temporary image list that is used for dragging. In response to subsequent
 * WM_MOUSEMOVE messages, you can move the drag image by using the ImageList_DragMove function. To
 * end the drag operation, you can use the ImageList_EndDrag function.
 */
WINCOMMCTRLAPI BOOL        WINAPI ImageList_BeginDrag(HIMAGELIST himlTrack, int iTrack, int dxHotspot, int dyHotspot);
/**
 * This function ends a drag operation.
 *
 * @return Nonzero indicates success. Zero indicates failure.
 */
WINCOMMCTRLAPI void        WINAPI ImageList_EndDrag();
/**
 * This function locks updates to the specified window during a drag operation and displays the drag
 * image at the specified position within the window.
 *
 * @param hwndLock [in] Handle to the window that owns the drag image.
 * @param x [in] Specifies the x-coordinate at which to display the drag image. The coordinate is
 *   relative to the upper-left corner of the window, not the client area.
 * @param y [in] Specifies the y-coordinate at which to display the drag image. The coordinate is
 *   relative to the upper-left corner of the window, not the client area.
 *
 * @return Nonzero indicates success. Zero indicates failure.
 *
 * To begin a drag operation, use the ImageList_BeginDrag function.
 */
WINCOMMCTRLAPI BOOL        WINAPI ImageList_DragEnter(HWND hwndLock, int x, int y);
/**
 * This function unlocks the specified window and hides the drag image, allowing the window to be
 * updated.
 *
 * @param hwndLock [in] Handle to the window that owns the drag image.
 *
 * @return Nonzero indicates success. Zero indicates failure.
 */
WINCOMMCTRLAPI BOOL        WINAPI ImageList_DragLeave(HWND hwndLock);
/**
 * This function moves the image that is being dragged during a drag-and-drop operation.
 * ImageList_DragMove is typically called in response to a WM_MOUSEMOVE message.
 *
 * @param x [in] Specifies the x-coordinate at which to display the drag image. The coordinate is
 *   relative to the upper-left corner of the window, not the client area.
 * @param y [in] Specifies the y-coordinate at which to display the drag image. The coordinate is
 *   relative to the upper-left corner of the window, not the client area.
 *
 * @return Nonzero indicates success. Zero indicates failure.
 *
 * To begin a drag operation, use the ImageList_BeginDrag function.
 */
WINCOMMCTRLAPI BOOL        WINAPI ImageList_DragMove(int x, int y);
/**
 * This function creates a new drag image by combining the specified image with the current drag
 * image.
 *
 * @param himlDrag [in] Handle to the image list that contains the new image to combine with the
 *   drag image.
 * @param iDrag [in] Index of the new image to combine with the drag image.
 * @param dxHotspot and dyHotspot [in] Specifies the position of the hot spot within the new image.
 *
 * @return Nonzero indicates success. Zero indicates failure.
 */
WINCOMMCTRLAPI BOOL        WINAPI ImageList_SetDragCursorImage(HIMAGELIST himlDrag, int iDrag, int dxHotspot, int dyHotspot);

/**
 * This function shows or hides the image being dragged.
 *
 * @param fShow [in] Boolean that specifies whether to show or hide the image being dragged. Specify
 *   TRUE to show the image or FALSE to hide the image.
 *
 * @return Nonzero indicates success. Zero indicates failure.
 */
WINCOMMCTRLAPI BOOL        WINAPI ImageList_DragShowNolock(BOOL fShow);
/**
 * This function retrieves the temporary image list that is used for the drag image.
 * ImageList_GetDragImage also retrieves the current drag position and the offset of the drag image
 * relative to the drag position.
 *
 * @param ppt [out] Pointer to the pointer to a POINT structure that receives the current drag
 *   position. Can be NULL.
 * @param pptHotspot [out] Pointer to the pointer to a POINT structure that receives the offset of
 *   the drag image relative to the drag position. Can be NULL.
 *
 * @return The handle to the image list indicates success. NULL indicates failure.
 *
 * The temporary image list is destroyed when the ImageList_EngDrag function is called. To begin a
 * drag operation, use the ImageListBeginDrag function.
 */
WINCOMMCTRLAPI HIMAGELIST  WINAPI ImageList_GetDragImage(POINT FAR* ppt,POINT FAR* pptHotspot);

/**
 * This function removes an image from an image list. ImageList_RemoveAll is a function that calls
 * the ImageList_Remove function.
 *
 * @param himl [in] Handle to the image list, and the index of the image to remove.
 *
 * @return Nonzero indicates success. Zero indicates failure.
 */
#define     ImageList_RemoveAll(himl) ImageList_Remove(himl, -1)
/**
 * This macro calls the ImageList_GetIcon function to create an icon based on an image and mask in
 * an image list.
 *
 * @param hi [in] Not used; set to 0.
 * @param himl [in] Handle to the image list.
 * @param i [in] Index of the image.
 *
 * @return The handle of the icon indicates success. NULL indicates failure.
 *
 * In Windows CE, you can only use the ImageList_ExtractIcon macro to create an icon, not a cursor.
 *
 * ImageList_ExtractIcon is not supported for emulation.
 */
#define     ImageList_ExtractIcon(hi, himl, i) ImageList_GetIcon(himl, i, 0)
/**
 * This macro calls the ImageList_LoadImage function to create an image list from the specified
 * bitmap resource.
 *
 * @param hi [in] Handle to the instance that contains the bitmap resource. This parameter is NULL
 *   if you are loading an OEM bitmap.
 * @param lpbmp [in] Long pointer to the image to load. If the hi parameter is non-NULL, lpbmp is
 *   the address of a null-terminated string that contains the name of the image resource in the hi
 *   module. If hi is NULL, the low-order word of this parameter must be the identifier of an OEM
 *   bitmap to load. To create this value, use the MAKEINTRESOURCE macro with one of the OEM bitmap
 *   identifiers defined in WINUSER.H. These identifiers have the OBM_ prefix.
 * @param cx [in] Width of each image. The height of each image and the initial number of images are
 *   inferred by the dimensions of the specified bitmap.
 * @param cGrow [in] Number of images by which the image list can grow when the system needs to make
 *   room for new images. This parameter represents the number of new images that the resized image
 *   list can contain.
 * @param crMask [in] Color used to generate a mask. Each pixel of this color in the specified
 *   bitmap is changed to black, and the corresponding bit in the mask is set to 1. If this parameter
 *   is the CLR_NONE value, no mask is generated.
 *
 * @return The handle to the image list indicates success. NULL indicates failure.
 *
 * This macro is not supported for emulation.
 */
#define     ImageList_LoadBitmap(hi, lpbmp, cx, cGrow, crMask) ImageList_LoadImage(hi, lpbmp, cx, cGrow, crMask, IMAGE_BITMAP, 0)

/**
 * This structure contains information about an image in an image list. This structure is used with
 * the ImageList_GetImageInfo function.
 */
typedef struct _IMAGEINFO
{
    /**
     * Handle to the bitmap that contains the images.
     */
    HBITMAP hbmImage;
    /**
     * Handle to a monochrome bitmap that contains the masks for the images. If the image list does not
     * contain a mask, this member is NULL.
     */
    HBITMAP hbmMask;
    /**
     * Not used; set to zero.
     */
    int     Unused1;
    /**
     * Not used; set to zero.
     */
    int     Unused2;
    /**
     * Bounding rectangle of the specified image within the bitmap specified by hbmImage.
     */
    RECT    rcImage;
} IMAGEINFO, FAR *LPIMAGEINFO;

/**
 * This function retrieves the dimensions of images in an image list. All images in an image list
 * have the same dimensions.
 *
 * @param himl [in] Handle to the image list.
 * @param cx [in] Address of an integer variable that receives the width, in pixels, of each image.
 * @param cy [in] Address of an integer variable that receives the height, in pixels, of each image.
 *
 * @return Nonzero indicates success. Zero indicates failure.
 */
WINCOMMCTRLAPI BOOL        WINAPI ImageList_GetIconSize(HIMAGELIST himl, int FAR *cx, int FAR *cy);
/**
 * This function sets the dimensions of images in an image list and removes all images from the
 * list.
 *
 * @param himl [in] Handle to the image list.
 * @param cx [in] Width, in pixels, of the images in the image list. All images in an image list
 *   have the same dimensions.
 * @param cy [in] Height, in pixels, of the images in the image list. All images in an image list
 *   have the same dimensions.
 *
 * @return Nonzero indicates success. Zero indicates failure.
 */
WINCOMMCTRLAPI BOOL        WINAPI ImageList_SetIconSize(HIMAGELIST himl, int cx, int cy);
/**
 * This function retrieves information about an image.
 *
 * @param himl [in] Handle to the image list.
 * @param i [in] Index of the image.
 * @param pImageInfo [out] Pointer to an IMAGEINFO structure that receives information about the
 *   image. The information in this structure can be used to directly manipulate the bitmaps for the
 *   image.
 *
 * @return Nonzero indicates success. Zero indicates failure.
 */
WINCOMMCTRLAPI BOOL        WINAPI ImageList_GetImageInfo(HIMAGELIST himl, int i, IMAGEINFO FAR* pImageInfo);
/**
 * This function creates a new image by combining two existing images. ImageList_Merge also creates
 * a new image list to store the image.
 *
 * @param himl1 [in] Handle to the first image list.
 * @param i1 [in] Index of the first existing image.
 * @param himl2 [in] Handle to the second image list.
 * @param i2 [in] Index of the second existing image.
 * @param dx and dy [in] Offset of the second image relative to the first image.
 *
 * @return The handle to the new image list indicates success. NULL indicates failure.
 *
 * The new image consists of the second existing image drawn transparently over the first. The mask
 * for the new image is the result of performing a logical OR operation on the masks of the two
 * existing images.
 */
WINCOMMCTRLAPI HIMAGELIST  WINAPI ImageList_Merge(HIMAGELIST himl1, int i1, HIMAGELIST himl2, int i2, int dx, int dy);
#if (_WIN32_IE >= 0x0400)
/**
 * This function creates a duplicate of an existing image list.
 *
 * @param himl [in] Handle to the image list to be duplicated. All information contained in the
 *   original image list is copied to the new image list.
 *
 * @return The handle to the new duplicate image list indicates success. NULL indicates failure.
 *
 * The ImageList_Duplicate function is not supported for emulation.
 */
WINCOMMCTRLAPI HIMAGELIST  WINAPI ImageList_Duplicate(HIMAGELIST himl);
#endif

#ifdef UNDER_CE // Retaining for backward compatibility because this was in 1.0
HBITMAP CreateColorBitmap(int cx, int cy);
HBITMAP CreateMonoBitmap(int cx, int cy);
void WINAPI ImageList_CopyDitherImage (HIMAGELIST himlDest, WORD iDst, int xDst, int yDst, HIMAGELIST himlSrc,
        int iSrc, UINT fStyle);
#endif // UNDER_CE

#endif

#endif


//====== HEADER CONTROL =======================================================

#ifndef NOHEADER

#ifdef _WIN32
#define WC_HEADERA              "SysHeader32"
#define WC_HEADERW              L"SysHeader32"

#ifdef UNICODE
#define WC_HEADER               WC_HEADERW
#else
#define WC_HEADER               WC_HEADERA
#endif

#else
#define WC_HEADER               "SysHeader"
#endif

// begin_r_commctrl                     

#define HDS_HORZ                0x0000
#define HDS_BUTTONS             0x0002
#define HDS_HIDDEN              0x0008


#if (_WIN32_IE >= 0x0300)
#define HDS_DRAGDROP            0x0040
#define HDS_FULLDRAG            0x0080
#endif

// end_r_commctrl

#if (_WIN32_IE >= 0x0300)
#define HD_ITEMA HDITEMA
#define HD_ITEMW HDITEMW
#else
#define HDITEMW  HD_ITEMW
#define HDITEMA  HD_ITEMA
#endif
#define HD_ITEM HDITEM

/**
 * This structure contains information about an item in a header control. This structure has been
 * updated to support header item images and order values.
 *
 * The header control can display text, an image and a bitmap for an item all at the same time. The
 * alignment flags determine the order in which they appear. With HDF_LEFT or HDF_CENTER, the order
 * is image, text, and then bitmap. With HDF_RIGHT the order is bitmap, image and then text.
 */
typedef struct _HD_ITEMA
{
    /**
     * Specifies which other structure members contain valid data or must be filled in. It can be a
     * combination of the following values: Value Description HDI_BITMAP The hbm member is valid.
     * HDI_FORMAT The fmt member is valid. HDI_HEIGHT The cxy member is valid and specifies the item's
     * height. HDI_IMAGE The iImage member is valid and specifies the image to be displayed with the
     * item. HDI_LPARAM The lParam member is valid. HDI_ORDER The iOrder member is valid and specifies
     * the item's order value. HDI_TEXT The pszText and cchTextMax members are valid. HDI_WIDTH The cxy
     * member is valid and specifies the item's width.
     */
    UINT    mask;
    /**
     * Width or height of the item.
     */
    int     cxy;
    /**
     * Pointer to a null-terminated item string. If this member is set to LPSTR_TEXTCALLBACK, the
     * control will request text information for this item by using HDN_GETDISPINFO notification
     * messages.
     */
    LPSTR   pszText;
    /**
     * Handle to the item bitmap.
     */
    HBITMAP hbm;
    /**
     * Length of the item string, in characters.
     */
    int     cchTextMax;
    /**
     * Set of bit flags that specify the item's format.
     *
     * This member can include one of the following text justification or right-to-left reading order
     * bit flags. Value Description HDF_CENTER The item's contents are centered. HDF_LEFT The item's
     * contents are left-aligned. HDF_RIGHT The item's contents are right-aligned. HDF_RTLREADING
     * Windows 95 only: Text is displayed using right-to-left reading order for Hebrew or Arabic
     * systems.
     *
     * The preceding flag is combined with one of the following flags. Value Description HDF_BITMAP The
     * item displays a bitmap. HDF_BITMAP_ON_RIGHT The bitmap appears to the right of text. This does
     * not affect an image from an image list assigned to the header item. HDF_OWNERDRAW The header
     * control's owner draws the item. HDF_STRING The item displays a string.
     *
     * Additionally, the following flag can be combined with any of the preceding flags. Value
     * Description HDF_IMAGE The item displays an image from an image list. You can use the
     * HDF_JUSTIFYMASK mask to isolate the text justification portion of the fmt member.
     */
    int     fmt;
    /**
     * Application-defined item data.
     */
    LPARAM  lParam;
#if (_WIN32_IE >= 0x0300)
    /**
     * Zero-based index of an image within the image list. The specified image will be displayed in the
     * header item, in addition to any image specified in the hbm member. If iImage is set to
     * I_IMAGECALLBACK, the control requests text information for this item by using HDN_GETDISPINFO
     * notification messages.
     */
    int     iImage;        // index of bitmap in ImageList
    /**
     * Order in which the item appears within the header control, from left to right. That is, the value
     * for the far left item is 0. The value for the next item to the right is 1, and so on.
     */
    int     iOrder;        // where to draw this item
#endif
} HDITEMA, FAR * LPHDITEMA;


/**
 * This structure contains information about an item in a header control. This structure has been
 * updated to support header item images and order values.
 *
 * The header control can display text, an image and a bitmap for an item all at the same time. The
 * alignment flags determine the order in which they appear. With HDF_LEFT or HDF_CENTER, the order
 * is image, text, and then bitmap. With HDF_RIGHT the order is bitmap, image and then text.
 */
typedef struct _HD_ITEMW
{
    /**
     * Specifies which other structure members contain valid data or must be filled in. It can be a
     * combination of the following values: Value Description HDI_BITMAP The hbm member is valid.
     * HDI_FORMAT The fmt member is valid. HDI_HEIGHT The cxy member is valid and specifies the item's
     * height. HDI_IMAGE The iImage member is valid and specifies the image to be displayed with the
     * item. HDI_LPARAM The lParam member is valid. HDI_ORDER The iOrder member is valid and specifies
     * the item's order value. HDI_TEXT The pszText and cchTextMax members are valid. HDI_WIDTH The cxy
     * member is valid and specifies the item's width.
     */
    UINT    mask;
    /**
     * Width or height of the item.
     */
    int     cxy;
    /**
     * Pointer to a null-terminated item string. If this member is set to LPSTR_TEXTCALLBACK, the
     * control will request text information for this item by using HDN_GETDISPINFO notification
     * messages.
     */
    LPWSTR   pszText;
    /**
     * Handle to the item bitmap.
     */
    HBITMAP hbm;
    /**
     * Length of the item string, in characters.
     */
    int     cchTextMax;
    /**
     * Set of bit flags that specify the item's format.
     *
     * This member can include one of the following text justification or right-to-left reading order
     * bit flags. Value Description HDF_CENTER The item's contents are centered. HDF_LEFT The item's
     * contents are left-aligned. HDF_RIGHT The item's contents are right-aligned. HDF_RTLREADING
     * Windows 95 only: Text is displayed using right-to-left reading order for Hebrew or Arabic
     * systems.
     *
     * The preceding flag is combined with one of the following flags. Value Description HDF_BITMAP The
     * item displays a bitmap. HDF_BITMAP_ON_RIGHT The bitmap appears to the right of text. This does
     * not affect an image from an image list assigned to the header item. HDF_OWNERDRAW The header
     * control's owner draws the item. HDF_STRING The item displays a string.
     *
     * Additionally, the following flag can be combined with any of the preceding flags. Value
     * Description HDF_IMAGE The item displays an image from an image list. You can use the
     * HDF_JUSTIFYMASK mask to isolate the text justification portion of the fmt member.
     */
    int     fmt;
    /**
     * Application-defined item data.
     */
    LPARAM  lParam;
#if (_WIN32_IE >= 0x0300)
    /**
     * Zero-based index of an image within the image list. The specified image will be displayed in the
     * header item, in addition to any image specified in the hbm member. If iImage is set to
     * I_IMAGECALLBACK, the control requests text information for this item by using HDN_GETDISPINFO
     * notification messages.
     */
    int     iImage;        // index of bitmap in ImageList
    /**
     * Order in which the item appears within the header control, from left to right. That is, the value
     * for the far left item is 0. The value for the next item to the right is 1, and so on.
     */
    int     iOrder;
#endif
} HDITEMW, FAR * LPHDITEMW;

#ifdef UNICODE
#define HDITEM HDITEMW
#define LPHDITEM LPHDITEMW
#else
#define HDITEM HDITEMA
#define LPHDITEM LPHDITEMW
#endif


#define HDI_WIDTH               0x0001
#define HDI_HEIGHT              HDI_WIDTH
#define HDI_TEXT                0x0002
#define HDI_FORMAT              0x0004
#define HDI_LPARAM              0x0008
#define HDI_BITMAP              0x0010
#if (_WIN32_IE >= 0x0300)
#define HDI_IMAGE               0x0020
#define HDI_DI_SETITEM          0x0040
#define HDI_ORDER               0x0080
#endif

#define HDF_LEFT                0
#define HDF_RIGHT               1
#define HDF_CENTER              2
#define HDF_JUSTIFYMASK         0x0003
#define HDF_RTLREADING          4

#define HDF_OWNERDRAW           0x8000
#define HDF_STRING              0x4000
#define HDF_BITMAP              0x2000
#if (_WIN32_IE >= 0x0300)
#define HDF_BITMAP_ON_RIGHT     0x1000
#define HDF_IMAGE               0x0800
#endif

/**
 * This message retrieves a count of the items in a header control. You can send this message
 * explicitly or use the Header_GetItemCount macro.
 *
 * @return The number of items indicates success. -1 indicates failure.
 */
#define HDM_GETITEMCOUNT        (HDM_FIRST + 0)
/**
 * This macro retrieves a count of the items in a header control. You can use this macro or send the
 * HDM_GETITEMCOUNT message explicitly.
 *
 * @param hwndHD Handle to the header control.
 *
 * @return The number of items indicates success. -1 indicates failure.
 *
 * The Header_GetItemCount macro is defined as follows:
 *
 *     #define Header_GetItemCount(hwndHD)        \
 *             (int)SendMessage((hwndHD), HDM_GETITEMCOUNT, 0, 0L)
 */
#define Header_GetItemCount(hwndHD) \
    (int)SNDMSG((hwndHD), HDM_GETITEMCOUNT, 0, 0L)


#define HDM_INSERTITEMA         (HDM_FIRST + 1)
#define HDM_INSERTITEMW         (HDM_FIRST + 10)

#ifdef UNICODE
/**
 * This message inserts a new item into a header control. You can send this message explicitly or
 * use the Header_InsertItem macro.
 *
 * @param index Index of the item after which the new item is inserted. The new item is inserted at
 *   the end of the header control if index is greater than or equal to the number of items in the
 *   control. If index is zero, the new item is inserted at the beginning of the header control.
 * @param phdi Pointer to an HDITEM structure that contains data about the new item
 *
 * @return The index of the new item indicates success. -1 indicates failure.
 */
#define HDM_INSERTITEM          HDM_INSERTITEMW
#else
/**
 * This message inserts a new item into a header control. You can send this message explicitly or
 * use the Header_InsertItem macro.
 *
 * @param index Index of the item after which the new item is inserted. The new item is inserted at
 *   the end of the header control if index is greater than or equal to the number of items in the
 *   control. If index is zero, the new item is inserted at the beginning of the header control.
 * @param phdi Pointer to an HDITEM structure that contains data about the new item
 *
 * @return The index of the new item indicates success. -1 indicates failure.
 */
#define HDM_INSERTITEM          HDM_INSERTITEMA
#endif

/**
 * This macro inserts a new item into a header control. You can use this macro or send the
 * HDM_INSERTITEM message explicitly.
 *
 * @param hwndHD Handle to the header control.
 * @param index Index of the item after which the new item is to be inserted. The new item is
 *   inserted at the end of the header control if index is greater than or equal to the number of
 *   items in the control. If index is zero, the new item is inserted at the beginning of the header
 *   control.
 * @param phdi Pointer to an HDITEM structure that contains information about the new item.
 *
 * @return The index of the new item indicates success. -1 indicates failure.
 *
 * The Header_InsertItem macro is defined as follows:
 *
 *     #define Header_InsertItem(hwndHD, index, phdi)    \
 *         (int)SendMessage((hwndHD), HDM_INSERTITEM, (WPARAM)(int)(index), \
 *         (LPARAM)(const LPHDITEM)(phdi))
 */
#define Header_InsertItem(hwndHD, i, phdi) \
    (int)SNDMSG((hwndHD), HDM_INSERTITEM, (WPARAM)(int)(i), (LPARAM)(const HD_ITEM FAR*)(phdi))


/**
 * This message deletes an item from a header control. You can send this message explicitly or use
 * the Header_DeleteItem macro.
 *
 * @param index Index of the item to delete
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define HDM_DELETEITEM          (HDM_FIRST + 2)
/**
 * This macro deletes an item from a header control. You can use this macro or send the
 * HDM_DELETEITEM message explicitly.
 *
 * @param hwndHD Handle to the header control.
 * @param index Index of the item to delete.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * The Header_DeleteItem macro is defined as follows:
 *
 *     #define Header_DeleteItem(hwndHD, index)        \
 *         (BOOL)SendMessage((hwndHD), HDM_DELETEITEM, (WPARAM)(int)(index), 0L)
 */
#define Header_DeleteItem(hwndHD, i) \
    (BOOL)SNDMSG((hwndHD), HDM_DELETEITEM, (WPARAM)(int)(i), 0L)


#define HDM_GETITEMA            (HDM_FIRST + 3)
#define HDM_GETITEMW            (HDM_FIRST + 11)

#ifdef UNICODE
/**
 * This message retrieves data about an item in a header control. You can send this message
 * explicitly or use the Header_GetItem macro.
 *
 * @param index Index of the item for which data is retrieved
 * @param phdi Pointer to an HDITEM structure. When the message is sent, the mask member indicates
 *   the type of data requested. When the message returns, the other members receive the requested
 *   data. If the mask member specifies zero, the message returns TRUE, but copies no data to the
 *   structure.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define HDM_GETITEM             HDM_GETITEMW
#else
/**
 * This message retrieves data about an item in a header control. You can send this message
 * explicitly or use the Header_GetItem macro.
 *
 * @param index Index of the item for which data is retrieved
 * @param phdi Pointer to an HDITEM structure. When the message is sent, the mask member indicates
 *   the type of data requested. When the message returns, the other members receive the requested
 *   data. If the mask member specifies zero, the message returns TRUE, but copies no data to the
 *   structure.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define HDM_GETITEM             HDM_GETITEMA
#endif

/**
 * This macro retrieves information about an item in a header control. You can use this macro or
 * send the HDM_GETITEM message explicitly.
 *
 * @param hwndHD Handle to the header control.
 * @param index Index of the item for which information is to be retrieved.
 * @param phdi Pointer to an HDITEM structure. When the message is sent, the mask member indicates
 *   the type of information being requested. When the message returns, the other members receive the
 *   requested information. If the mask member specifies zero, the message returns TRUE but copies no
 *   information to the structure.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * The Header_GetItem macro is defined as follows:
 *
 *     #define Header_GetItem(hwndHD, index, phdi)        \
 *         (BOOL)SendMessage((hwndHD), HDM_GETITEM,        \
 *         (WPARAM)(int)(index), (LPARAM)(LPHDITEM)(phdi))
 */
#define Header_GetItem(hwndHD, i, phdi) \
    (BOOL)SNDMSG((hwndHD), HDM_GETITEM, (WPARAM)(int)(i), (LPARAM)(HD_ITEM FAR*)(phdi))


#define HDM_SETITEMA            (HDM_FIRST + 4)
#define HDM_SETITEMW            (HDM_FIRST + 12)

#ifdef UNICODE
/**
 * This message sets the specified item attributes in a header control. You can send this message
 * explicitly or use the Header_SetItem macro.
 *
 * @param iIndex Current index of the item whose attributes are changed
 * @param phdItem Pointer to an HDITEM structure that contains item data. When this message is sent,
 *   the mask member of the structure must be set to indicate which attributes are set.
 *
 * @return Nonzero indicates success. Zero indicates failure.
 */
#define HDM_SETITEM             HDM_SETITEMW
#else
/**
 * This message sets the specified item attributes in a header control. You can send this message
 * explicitly or use the Header_SetItem macro.
 *
 * @param iIndex Current index of the item whose attributes are changed
 * @param phdItem Pointer to an HDITEM structure that contains item data. When this message is sent,
 *   the mask member of the structure must be set to indicate which attributes are set.
 *
 * @return Nonzero indicates success. Zero indicates failure.
 */
#define HDM_SETITEM             HDM_SETITEMA
#endif

/**
 * This macro sets the attributes of the specified item in a header control. You can use this macro
 * or send the HDM_SETITEM message explicitly.
 *
 * @param hwndHD Handle to a header control.
 * @param iIndex Current index of the item for which attributes are to be changed.
 * @param phdItem Pointer to an HDITEM structure that contains item information. When this message
 *   is sent, the mask member of the structure must be set to indicate which attributes are being set.
 *
 * @return Nonzero indicates success. Zero indicates failure.
 *
 * In Windows CE version 2.0, this macro supports item order and image list information. By using
 * the iImage and iOrder members of the new HDITEM structure you pass in the phdi parameter, you can
 * control the order in which items are displayed and specify images to appear with items.
 *
 * The HDITEM structure that supports this macro supports item order and image list information. By
 * using these members, you can control the order in which items are displayed and specify images to
 * appear with items.
 */
#define Header_SetItem(hwndHD, i, phdi) \
    (BOOL)SNDMSG((hwndHD), HDM_SETITEM, (WPARAM)(int)(i), (LPARAM)(const HD_ITEM FAR*)(phdi))

#if (_WIN32_IE >= 0x0300)
#define HD_LAYOUT  HDLAYOUT
#else
#define HDLAYOUT   HD_LAYOUT
#endif

/**
 * This structure contains information used to set the size and position of a header control. This
 * structure is used with the HDM_LAYOUT message.
 */
typedef struct _HD_LAYOUT
{
    /**
     * Pointer to a RECT structure that contains the coordinates of a rectangle that the header control
     * will occupy.
     */
    RECT FAR* prc;
    /**
     * Pointer to a WINDOWPOS structure that receives information about the appropriate size and
     * position of the header control.
     */
    WINDOWPOS FAR* pwpos;
} HDLAYOUT, FAR *LPHDLAYOUT;


/**
 * Retrieves the correct header control size and position within the parent window. This message
 * retrieves the header control size and position within a specified rectangle. This message is used
 * to determine the appropriate dimensions for a new header control to occupy the specified
 * rectangle. You can send this message explicitly or use the Header_Layout macro.
 *
 * @param playout Pointer to an HDLAYOUT structure. The prc member specifies the rectangle
 *   coordinates, and the pwpos member receives the size and position for the header control within
 *   the rectangle.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define HDM_LAYOUT              (HDM_FIRST + 5)
/**
 * This macro retrieves the size and position of a header control within a specified rectangle. This
 * macro is used to determine the appropriate dimensions for a new header control that is to occupy
 * the specified rectangle. You can use this macro or send the HDM_LAYOUT message explicitly.
 *
 * @param hwndHD Handle to the header control.
 * @param playout Pointer to an HDLAYOUT structure. The prc member specifies the coordinates of a
 *   rectangle, and the pwpos member receives the size and position for the header control within the
 *   rectangle.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * The Header_Layout macro is defined as follows:
 *
 *     #define Header_Layout(hwndHD, playout) \
 *         (BOOL)SendMessage((hwndHD), HDM_LAYOUT, 0, \
 *         (LPARAM)(PLHDLAYOUT)(playout))
 */
#define Header_Layout(hwndHD, playout) \
    (BOOL)SNDMSG((hwndHD), HDM_LAYOUT, 0, (LPARAM)(HD_LAYOUT FAR*)(playout))


#define HHT_NOWHERE             0x0001
#define HHT_ONHEADER            0x0002
#define HHT_ONDIVIDER           0x0004
#define HHT_ONDIVOPEN           0x0008
#define HHT_ABOVE               0x0100
#define HHT_BELOW               0x0200
#define HHT_TORIGHT             0x0400
#define HHT_TOLEFT              0x0800

#if (_WIN32_IE >= 0x0300)
#define HD_HITTESTINFO HDHITTESTINFO
#else
#define HDHITTESTINFO  HD_HITTESTINFO
#endif

/**
 * This structure contains information about a hit test. This structure is used with the HDM_HITTEST
 * message.
 */
typedef struct _HD_HITTESTINFO
{
    /**
     * Points to test, in client coordinates.
     */
    POINT pt;
    /**
     * Receives information about the results of a hit test. It can be one or more of the following
     * values. Value Description HHT_NOWHERE The point is inside the header control's bounding rectangle
     * but is not over a header item. HHT_ONDIVIDER The point is on the divider between two header
     * items. HHT_ONDIVOPEN The point is on the divider of an item that has a width of zero. Dragging
     * the divider reveals the item instead of resizing the item to the left of the divider.
     * HHT_ONHEADER The point is inside the header control's bounding rectangle. HHT_TOLEFT The point is
     * to the left of the header control's bounding rectangle. HHT_TORIGHT The point is to the right of
     * the header control's bounding rectangle.
     *
     * Two of these values can be combined, such as when the position is above and to the left of the
     * client area.
     */
    UINT flags;
    /**
     * Receives the index of item at point, if any.
     */
    int iItem;
} HDHITTESTINFO, FAR *LPHDHITTESTINFO;


/**
 * This message tests a point to determine which header item, if any, is at the specified point.
 *
 * @param phdhti Pointer to an HDHITTESTINFO structure that contains the position to test and
 *   receive test result data.
 *
 * @return The index of the item at the specified position, if any, indicates success. -1 indicates
 *   failure.
 */
#define HDM_HITTEST             (HDM_FIRST + 6)

#if (_WIN32_IE >= 0x0300)

/**
 * This message retrieves the bounding rectangle for a specified item in a header control.
 *
 * @param iIndex Zero-based index of the header control item for which to retrieve the bounding
 *   rectangle
 * @param lpItemRect Long pointer to a RECT structure that receives the bounding rectangle data
 *
 * @return Nonzero indicates success. Zero indicates failure
 */
#define HDM_GETITEMRECT         (HDM_FIRST + 7)
/**
 * This macro retrieves the bounding rectangle for a specified item in a header control.
 *
 * @param hwndHD Handle to a header control.
 * @param iIndex Zero-based index of the header control item for which to retrieve the bounding
 *   rectangle.
 * @param lpItemRect Long pointer to a RECT structure that receives the bounding rectangle
 *   information.
 *
 * @return Nonzero indicates success. Zero indicates otherwise.
 */
#define Header_GetItemRect(hwnd, iItem, lprc) \
        (BOOL)SNDMSG((hwnd), HDM_GETITEMRECT, (WPARAM)iItem, (LPARAM)lprc)

/**
 * This message assigns an image list to an existing header control.
 *
 * @param himl Handle to an image list
 *
 * @return Returns the handle to the image list previously associated with the control. The message
 *   returns NULL upon failure, or if no image list was set previously.
 */
#define HDM_SETIMAGELIST        (HDM_FIRST + 8)
/**
 * This macro assigns an image list to an existing header control.
 *
 * @param hwndHD Handle to a header control.
 * @param himl Handle to an image list.
 *
 * @return Returns the handle to the image list previously assigned to the header control, or NULL
 *   if there is no previous image list.
 */
#define Header_SetImageList(hwnd, himl) \
        (HIMAGELIST)SNDMSG((hwnd), HDM_SETIMAGELIST, 0, (LPARAM)himl)

/**
 * This message retrieves the handle to the image list that has been set for an existing header
 * control.
 *
 * @return Returns a handle to the image list set for the header control
 */
#define HDM_GETIMAGELIST        (HDM_FIRST + 9)
/**
 * This macro retrieves the handle to the image list that has been set for an existing header
 * control.
 *
 * @param hwndHD Handle to a header control.
 *
 * @return Returns the handle to the image list that is set for the header control.
 */
#define Header_GetImageList(hwnd) \
        (HIMAGELIST)SNDMSG((hwnd), HDM_GETIMAGELIST, 0, 0)


/**
 * This message retrieves an index value for an item based on its order in the header control.
 *
 * @param iOrder Order in which the item appears within the header control, from left to right. For
 *   example, the index value of the item in the far left column would be 0. The value for the next
 *   item to the right would be 1, and so on.
 *
 * @return Returns INT that indicates the item index. If iOrder is invalid (negative or too large),
 *   the return value equals iOrder.
 */
#define HDM_ORDERTOINDEX        (HDM_FIRST + 15)
/**
 * This macro retrieves an index value for an item based on its order in the header control.
 *
 * @param hwndHD Handle to a header control.
 * @param iOrder Order that the item appears within the header control, from left to right. The
 *   index value of the item in the far left column would be 0, the next item to the right would be 1,
 *   and so on.
 *
 * @return Returns an INT that specifies the index of the item. If iOrder is invalid, (that is,
 *   negative or too large) the return value equals iOrder.
 */
#define Header_OrderToIndex(hwnd, i) \
        (int)SNDMSG((hwnd), HDM_ORDERTOINDEX, (WPARAM)i, 0)

/**
 * This message creates a transparent version of an item's image within an existing header control.
 *
 * @param iIndex Zero-based index of the item within the header control. The image assigned to this
 *   item is the basis for the transparent image.
 *
 * @return Returns a handle to an image list that contains the new image as its only element
 */
#define HDM_CREATEDRAGIMAGE     (HDM_FIRST + 16)  // wparam = which item (by index)
/**
 * This macro creates a transparent version of an item image within an existing header control.
 *
 * @param hwndHD Handle to a header control.
 * @param iIndex Zero-based index of the item within the header control. The image assigned to this
 *   item is used as the basis for the transparent image.
 *
 * @return Returns a handle to an image list that contains the new image as its only element.
 */
#define Header_CreateDragImage(hwnd, i) \
        (HIMAGELIST)SNDMSG((hwnd), HDM_CREATEDRAGIMAGE, (WPARAM)i, 0)

/**
 * This message retrieves the current left-to-right order of items in a header control.
 *
 * @param iSize Size of the buffer at lpiArray, in elements. This value must equal the value
 *   returned by HDM_GETITEMCOUNT.
 * @param lpiArray Long pointer to the buffer that receives the index values for items in the
 *   header. The buffer must be large enough to hold the total number of header items * sizeof(int).
 *   The following code example shows how to reserve enough memory to hold the index values.
 *
 * @return Returns nonzero if successful, and the buffer at lpiArray receives the item number for
 *   each item in the header control, in the order in which they appear from left to right. Otherwise,
 *   the message returns zero.
 */
#define HDM_GETORDERARRAY       (HDM_FIRST + 17)
/**
 * This macro retrieves the current left-to-right order of items in a header control.
 *
 * @param hwndHD Handle to a header control.
 * @param iSize Size of the buffer at lpiArray, in elements. This value must equal the value
 *   returned by HDM_GETITEMCOUNT.
 * @param lpiArray Long pointer to a buffer that receives the index values of the items in the
 *   header. The buffer should be big enough to hold the total number of items * sizeof(int). For
 *   example, the following code fragment will reserve enough memory to hold the index values.
 *
 * @return Returns nonzero if successful, and the buffer at lpiArray receives the item number of
 *   each item in the header control, in the order in which they appear from left to right. The macro
 *   returns zero otherwise.
 */
#define Header_GetOrderArray(hwnd, iCount, lpi) \
        (BOOL)SNDMSG((hwnd), HDM_GETORDERARRAY, (WPARAM)iCount, (LPARAM)lpi)

/**
 * This message sets the left-to-right order of header items.
 *
 * @param iSize Size of the buffer at lpiArray, in elements. This value must equal the value
 *   returned by HDM_GETITEMCOUNT.
 * @param lpiArray Long pointer to an array that specifies the order in which items should be
 *   displayed, from left to right. For example, if the contents of the array are {2,0,1}, the control
 *   displays item 2, item 0, and item 1 in that order, from left to right.
 *
 * @return Nonzero indicates success. Zero indicates otherwise.
 */
#define HDM_SETORDERARRAY       (HDM_FIRST + 18)
/**
 * This macro sets the left-to-right order of header items.
 *
 * @param hwndHD Handle to a header control.
 * @param iSize Size of the buffer at lpiArray, in elements. This value must equal the value
 *   returned by HDM_GETITEMCOUNT.
 * @param lpiArray Long pointer to an array that specifies the order in which items should be
 *   displayed, from left to right. For example, if the contents of the array are {2,0,1}, the control
 *   displays item 2, item 0, and item 1 in that order.
 *
 * @return Nonzero indicates success. Zero indicates otherwise.
 */
#define Header_SetOrderArray(hwnd, iCount, lpi) \
        (BOOL)SNDMSG((hwnd), HDM_SETORDERARRAY, (WPARAM)iCount, (LPARAM)lpi)
// lparam = int array of size HDM_GETITEMCOUNT
// the array specifies the order that all items should be displayed.
// e.g.  { 2, 0, 1}
// says the index 2 item should be shown in the 0ths position
//      index 0 should be shown in the 1st position
//      index 1 should be shown in the 2nd position


/**
 * This message changes the divider color between header items to indicate the destination of an
 * external drag-and-drop operation.
 *
 * @param flag Specifies the type of value represented by dwInputValue. It is one of the following
 *   values: Value Description TRUE Indicates that dwInputValue holds the client coordinates of the
 *   pointer FALSE Indicates that dwInputValue holds a divider index value
 * @param dwInputValue Value held in dwInputValue is interpreted based upon the value of flag. If
 *   flag is TRUE, dwInputValue represents the x- and y-coordinates of the pointer. The x-coordinate
 *   is in the low-order word, and the y-coordinate is in the high-order word. When the header control
 *   receives the message, it highlights the appropriate divider based on the dwInputValue
 *   coordinates. If flag is FALSE, dwInputValue represents the integer index of the divider
 *   highlighted.
 *
 * @return Returns a value equal to the index of the divider that the control highlighted
 *
 * This message creates an effect that a header control automatically produces when it has the
 * HDS_DRAGDROP style. The HDM_SETHOTDIVIDER message is intended for use when the owner of the
 * control manually handles drag-and-drop operations.
 */
#define HDM_SETHOTDIVIDER          (HDM_FIRST + 19)
/**
 * This macro changes the color of a divider between header items to indicate the destination of an
 * external drag-and-drop operation.
 *
 * @param hwndHD Handle to a header control.
 * @param flag Boolean value that specifies how dwInputValue is to be interpreted.
 * @param dwInputValue Value held here is interpreted depending on the value of flag. If flag is
 *   TRUE, then dwInputValue represents the x- and y- client coordinates of the pointer. The
 *   x-coordinate is in the low-order word, and the y-coordinate is in the high-order word. Upon
 *   receiving the message, the header control highlights the appropriate divider based on the
 *   dwInputValue coordinates. If flag is FALSE, then dwInputValue represents the integer index of the
 *   divider that will be highlighted.
 *
 * @return Returns the index of the divider that the control highlighted.
 *
 * A header control set to the HDS_DRAGDROP style produces this effect automatically. This message
 * is intended to be used when the owner of the control handles drag-and-drop operations manually.
 */
#define Header_SetHotDivider(hwnd, fPos, dw) \
        (int)SNDMSG((hwnd), HDM_SETHOTDIVIDER, (WPARAM)fPos, (LPARAM)dw)
// convenience message for external dragdrop
// wParam = BOOL  specifying whether the lParam is a dwPos of the cursor
//              position or the index of which divider to hotlight
// lParam = depends on wParam  (-1 and wParm = FALSE turns off hotlight)
#endif      // _WIN32_IE >= 0x0300

#define HDN_ITEMCHANGINGA       (HDN_FIRST-0)
#define HDN_ITEMCHANGINGW       (HDN_FIRST-20)
#define HDN_ITEMCHANGEDA        (HDN_FIRST-1)
#define HDN_ITEMCHANGEDW        (HDN_FIRST-21)
#define HDN_ITEMCLICKA          (HDN_FIRST-2)
#define HDN_ITEMCLICKW          (HDN_FIRST-22)
#define HDN_ITEMDBLCLICKA       (HDN_FIRST-3)
#define HDN_ITEMDBLCLICKW       (HDN_FIRST-23)
#define HDN_DIVIDERDBLCLICKA    (HDN_FIRST-5)
#define HDN_DIVIDERDBLCLICKW    (HDN_FIRST-25)
#define HDN_BEGINTRACKA         (HDN_FIRST-6)
#define HDN_BEGINTRACKW         (HDN_FIRST-26)
#define HDN_ENDTRACKA           (HDN_FIRST-7)
#define HDN_ENDTRACKW           (HDN_FIRST-27)
#define HDN_TRACKA              (HDN_FIRST-8)
#define HDN_TRACKW              (HDN_FIRST-28)
#if (_WIN32_IE >= 0x0300)
#define HDN_GETDISPINFOA        (HDN_FIRST-9)
#define HDN_GETDISPINFOW        (HDN_FIRST-29)
/**
 * This notification message is sent by a header control when a drag operation has begun on one of
 * its items. It is sent only by header controls set to the HDS_DRAGDROP style, and is sent as a
 * WM_NOTIFY message.
 *
 * @param pNMHeader Pointer to an NMHEADER structure that contains data about the header item
 *   dragged
 *
 * @return To enable the header control to automatically manage drag-and-drop operations, return
 *   FALSE. If the owner of the control is manually performing drag-and-drop reordering, return TRUE.
 *
 * A header control defaults to automatically managing drag-and-drop reordering. Returning TRUE to
 * indicate external (manual) drag-and-drop management enables the owner of the control to provide
 * custom services as part of the drag-and-drop process.
 */
#define HDN_BEGINDRAG           (HDN_FIRST-10)
/**
 * This notification message is sent by a header control when a drag operation has ended on one of
 * its items. It is sent only by header controls set to the HDS_DRAGDROP style, and is sent as a
 * WM_NOTIFY message.
 *
 * @param pNMHeader Pointer to an NMHEADER structure that contains data about the header item
 *   dragged
 *
 * @return To enable the control to automatically place and reorder the item, return FALSE. Return
 *   TRUE to prevent the item from being placed.
 *
 * If the owner is performing external (manual) drag-and-drop management, it must return FALSE. The
 * owner then must reorder header items manually by sending HDM_SETITEM or HDM_SETORDERARRAY.
 */
#define HDN_ENDDRAG             (HDN_FIRST-11)
#endif

#ifdef UNICODE
/**
 * This notification message notifies a header control parent window the header item attributes are
 * about to change. It is sent in the form of a WM_NOTIFY message.
 *
 * @param phdr Pointer to an NMHEADER structure that contains data about the header control and the
 *   header item, including the attributes about to change.
 *
 * @return TRUE prevents the changes. FALSE accepts the changes.
 */
#define HDN_ITEMCHANGING         HDN_ITEMCHANGINGW
/**
 * This notification message notifies a header control parent window the header item attributes have
 * changed. It is sent in the form of a WM_NOTIFY message.
 *
 * @param phdr Pointer to an NMHEADER structure that contains data about the header control,
 *   including attributes that have changed.
 *
 * @return None
 */
#define HDN_ITEMCHANGED          HDN_ITEMCHANGEDW
/**
 * This notification message notifies a header control parent window that the user tapped the
 * control. It is sent in the form of a WM_NOTIFY message.
 *
 * @param phdr Pointer to an NMHEADER structure that identifies the header control and specifies the
 *   index of the header item clicked and the mouse button used to click the item. The pItem member is
 *   set to NULL.
 *
 * @return None
 */
#define HDN_ITEMCLICK            HDN_ITEMCLICKW
/**
 * This notification message notifies a header control parent window that the user double-tapped the
 * control. It is sent in the form of a WM_NOTIFY message. Only header controls with the HDS_BUTTONS
 * style send this notification.
 *
 * @param pnmhdr Pointer to an NMHEADER structure that contains data about this notification.
 *
 * @return None
 */
#define HDN_ITEMDBLCLICK         HDN_ITEMDBLCLICKW
/**
 * This notification message notifies a header control's parent window that the user double-tapped
 * the divider area of the control. It is sent in the form of a WM_NOTIFY message.
 *
 * @param phdn Pointer to an NMHEADER structure that contains data about the header control and the
 *   item whose divider was double-clicked
 *
 * @return None
 */
#define HDN_DIVIDERDBLCLICK      HDN_DIVIDERDBLCLICKW
/**
 * This notification message notifies a header control parent window the user has begun dragging a
 * divider in the control; that is, the user has pressed the stylus to the touch screen over a
 * divider in the header control. It is sent in the form of a WM_NOTIFY message.
 *
 * @param phdn Pointer to an NMHEADER structure that contains data about the header control and the
 *   item whose divider is dragged.
 *
 * @return TRUE prevents tracking. FALSE enables tracking of the divider.
 */
#define HDN_BEGINTRACK           HDN_BEGINTRACKW
/**
 * This notification message notifies a header control parent window that the user has finished
 * dragging a divider. It sent in the form of a WM_NOTIFY message.
 *
 * @param phdn Pointer to an NMHEADER structure that contains data about the header control and the
 *   item whose divider was dragged
 *
 * @return None
 */
#define HDN_ENDTRACK             HDN_ENDTRACKW
/**
 * This notification message notifies a header control parent window the user is dragging a divider
 * in the header control. It is sent in the form of a WM_NOTIFY message.
 *
 * @param phdr Pointer to an NMHEADER structure that contains data about the header control and the
 *   item whose divider is dragged
 *
 * @return TRUE ends tracking. FALSE continues tracking.
 */
#define HDN_TRACK                HDN_TRACKW
#if (_WIN32_IE >= 0x0300)
/**
 * This notification message is sent to the owner of a header control when the control needs data
 * about a callback header item. It is sent as a WM_NOTIFY message.
 *
 * @param pDispInfo Pointer to an NMHDDISPINFO structure. On input, the members of the structure
 *   specify what data is required and the item of interest.
 *
 * Fill the appropriate members of the structure to return the requested data to the header control.
 * If your message handler sets the mask member of the NMHDDISPINFO structure to HDI_DI_SETITEM, the
 * header control stores the data and will not request it again.
 */
#define HDN_GETDISPINFO          HDN_GETDISPINFOW
#endif
#else
/**
 * This notification message notifies a header control parent window the header item attributes are
 * about to change. It is sent in the form of a WM_NOTIFY message.
 *
 * @param phdr Pointer to an NMHEADER structure that contains data about the header control and the
 *   header item, including the attributes about to change.
 *
 * @return TRUE prevents the changes. FALSE accepts the changes.
 */
#define HDN_ITEMCHANGING         HDN_ITEMCHANGINGA
/**
 * This notification message notifies a header control parent window the header item attributes have
 * changed. It is sent in the form of a WM_NOTIFY message.
 *
 * @param phdr Pointer to an NMHEADER structure that contains data about the header control,
 *   including attributes that have changed.
 *
 * @return None
 */
#define HDN_ITEMCHANGED          HDN_ITEMCHANGEDA
/**
 * This notification message notifies a header control parent window that the user tapped the
 * control. It is sent in the form of a WM_NOTIFY message.
 *
 * @param phdr Pointer to an NMHEADER structure that identifies the header control and specifies the
 *   index of the header item clicked and the mouse button used to click the item. The pItem member is
 *   set to NULL.
 *
 * @return None
 */
#define HDN_ITEMCLICK            HDN_ITEMCLICKA
/**
 * This notification message notifies a header control parent window that the user double-tapped the
 * control. It is sent in the form of a WM_NOTIFY message. Only header controls with the HDS_BUTTONS
 * style send this notification.
 *
 * @param pnmhdr Pointer to an NMHEADER structure that contains data about this notification.
 *
 * @return None
 */
#define HDN_ITEMDBLCLICK         HDN_ITEMDBLCLICKA
/**
 * This notification message notifies a header control's parent window that the user double-tapped
 * the divider area of the control. It is sent in the form of a WM_NOTIFY message.
 *
 * @param phdn Pointer to an NMHEADER structure that contains data about the header control and the
 *   item whose divider was double-clicked
 *
 * @return None
 */
#define HDN_DIVIDERDBLCLICK      HDN_DIVIDERDBLCLICKA
/**
 * This notification message notifies a header control parent window the user has begun dragging a
 * divider in the control; that is, the user has pressed the stylus to the touch screen over a
 * divider in the header control. It is sent in the form of a WM_NOTIFY message.
 *
 * @param phdn Pointer to an NMHEADER structure that contains data about the header control and the
 *   item whose divider is dragged.
 *
 * @return TRUE prevents tracking. FALSE enables tracking of the divider.
 */
#define HDN_BEGINTRACK           HDN_BEGINTRACKA
/**
 * This notification message notifies a header control parent window that the user has finished
 * dragging a divider. It sent in the form of a WM_NOTIFY message.
 *
 * @param phdn Pointer to an NMHEADER structure that contains data about the header control and the
 *   item whose divider was dragged
 *
 * @return None
 */
#define HDN_ENDTRACK             HDN_ENDTRACKA
/**
 * This notification message notifies a header control parent window the user is dragging a divider
 * in the header control. It is sent in the form of a WM_NOTIFY message.
 *
 * @param phdr Pointer to an NMHEADER structure that contains data about the header control and the
 *   item whose divider is dragged
 *
 * @return TRUE ends tracking. FALSE continues tracking.
 */
#define HDN_TRACK                HDN_TRACKA
#if (_WIN32_IE >= 0x0300)
/**
 * This notification message is sent to the owner of a header control when the control needs data
 * about a callback header item. It is sent as a WM_NOTIFY message.
 *
 * @param pDispInfo Pointer to an NMHDDISPINFO structure. On input, the members of the structure
 *   specify what data is required and the item of interest.
 *
 * Fill the appropriate members of the structure to return the requested data to the header control.
 * If your message handler sets the mask member of the NMHDDISPINFO structure to HDI_DI_SETITEM, the
 * header control stores the data and will not request it again.
 */
#define HDN_GETDISPINFO          HDN_GETDISPINFOA
#endif
#endif



#if (_WIN32_IE >= 0x0300)
#define HD_NOTIFYA              NMHEADERA
#define HD_NOTIFYW              NMHEADERW
#else
#define tagNMHEADERA            _HD_NOTIFY
#define NMHEADERA               HD_NOTIFYA
#define tagHMHEADERW            _HD_NOTIFYW
#define NMHEADERW               HD_NOTIFYW
#endif
#define HD_NOTIFY               NMHEADER

/**
 * This structure contains information about header control notification messages. This structure
 * supersedes the HD_NOTIFY structure.
 */
typedef struct tagNMHEADERA
{
    /**
     * NMHDR structure that contains information about the notification message.
     */
    NMHDR   hdr;
    /**
     * Zero-based index of the header item that is the focus of the notification message.
     */
    int     iItem;
    /**
     * Index of the mouse button used to generate the notification message. It is one of the following
     * values: Value Description 0 Left button 1 Right button 2 Middle button
     */
    int     iButton;
    HDITEMA FAR* pitem;
}  NMHEADERA, FAR* LPNMHEADERA;


/**
 * This structure contains information about header control notification messages. This structure
 * supersedes the HD_NOTIFY structure.
 */
typedef struct tagNMHEADERW
{
    /**
     * NMHDR structure that contains information about the notification message.
     */
    NMHDR   hdr;
    /**
     * Zero-based index of the header item that is the focus of the notification message.
     */
    int     iItem;
    /**
     * Index of the mouse button used to generate the notification message. It is one of the following
     * values: Value Description 0 Left button 1 Right button 2 Middle button
     */
    int     iButton;
    HDITEMW FAR* pitem;
} NMHEADERW, FAR* LPNMHEADERW;

#ifdef UNICODE
#define NMHEADER                NMHEADERW
#define LPNMHEADER              LPNMHEADERW
#else
#define NMHEADER                NMHEADERA
#define LPNMHEADER              LPNMHEADERA
#endif

/**
 * This structure contains information used in handling HDN_GETDISPINFO notification messages.
 */
typedef struct tagNMHDDISPINFOW
{
    /**
     * NMHDR structure containing information about this notification message.
     */
    NMHDR   hdr;
    /**
     * Zero-based index of the item in the header control.
     */
    int     iItem;
    /**
     * Specifies which members of the structure must be filled in by the owner of the header control. It
     * can be a combination of the following values: Value Description HDI_TEXT The pszText member must
     * be filled in. HDI_IMAGE The iImage member must be filled in. HDI_LPARAM The lParam member must be
     * filled in. HDI_DI_SETITEM A return value. Specifies that the header control should store the item
     * information and not ask for it again.
     */
    UINT    mask;
    /**
     * Pointer to a null-terminated string that contains the text to be displayed for the header item.
     */
    LPWSTR  pszText;
    /**
     * Size of the buffer that pszText points to.
     */
    int     cchTextMax;
    /**
     * Zero-based index of an image within the image list. The specified image will be displayed with
     * the header item, but does not take the place of the image specified in the hbm member. If iImage
     * is set to I_IMAGECALLBACK, the control requests image information for this item by using
     * HDN_GETDISPINFO notification messages.
     */
    int     iImage;
    LPARAM  lParam;
} NMHDDISPINFOW, FAR* LPNMHDDISPINFOW;

/**
 * This structure contains information used in handling HDN_GETDISPINFO notification messages.
 */
typedef struct tagNMHDDISPINFOA
{
    /**
     * NMHDR structure containing information about this notification message.
     */
    NMHDR   hdr;
    /**
     * Zero-based index of the item in the header control.
     */
    int     iItem;
    /**
     * Specifies which members of the structure must be filled in by the owner of the header control. It
     * can be a combination of the following values: Value Description HDI_TEXT The pszText member must
     * be filled in. HDI_IMAGE The iImage member must be filled in. HDI_LPARAM The lParam member must be
     * filled in. HDI_DI_SETITEM A return value. Specifies that the header control should store the item
     * information and not ask for it again.
     */
    UINT    mask;
    /**
     * Pointer to a null-terminated string that contains the text to be displayed for the header item.
     */
    LPSTR   pszText;
    /**
     * Size of the buffer that pszText points to.
     */
    int     cchTextMax;
    /**
     * Zero-based index of an image within the image list. The specified image will be displayed with
     * the header item, but does not take the place of the image specified in the hbm member. If iImage
     * is set to I_IMAGECALLBACK, the control requests image information for this item by using
     * HDN_GETDISPINFO notification messages.
     */
    int     iImage;
    LPARAM  lParam;
} NMHDDISPINFOA, FAR* LPNMHDDISPINFOA;


#ifdef UNICODE
#define NMHDDISPINFO            NMHDDISPINFOW
#define LPNMHDDISPINFO          LPNMHDDISPINFOW
#else
#define NMHDDISPINFO            NMHDDISPINFOA
#define LPNMHDDISPINFO          LPNMHDDISPINFOA
#endif

#endif      // NOHEADER


//====== TOOLBAR CONTROL ======================================================

#ifndef NOTOOLBAR

#ifdef _WIN32
#define TOOLBARCLASSNAMEW       L"ToolbarWindow32"
#define TOOLBARCLASSNAMEA       "ToolbarWindow32"

#ifdef  UNICODE
#define TOOLBARCLASSNAME        TOOLBARCLASSNAMEW
#else
#define TOOLBARCLASSNAME        TOOLBARCLASSNAMEA
#endif

#else
#define TOOLBARCLASSNAME        "ToolbarWindow"
#endif

/**
 * This structure contains information about a button in a toolbar.
 */
typedef struct _TBBUTTON {
    /**
     * Zero-based index of the button image.
     */
    int iBitmap;
    /**
     * Command identifier associated with the button. This identifier is used in a WM_COMMAND message
     * when the button is chosen.
     */
    int idCommand;
    /**
     * Button state flags. It can be a combination of the values listed in Toolbar Button States.
     */
    BYTE fsState;
    /**
     * Button style. It can be a combination of the button style values listed in Toolbar Control Button
     * Styles.
     */
    BYTE fsStyle;
#ifdef _WIN32
    BYTE bReserved[2];
#endif
    /**
     * Specifies an application-defined value.
     */
    DWORD dwData;
    /**
     * Zero-based index of the button string.
     */
    int iString;
} TBBUTTON, NEAR* PTBBUTTON, FAR* LPTBBUTTON;
typedef const TBBUTTON FAR* LPCTBBUTTON;

/**
 * This function creates a toolbar window and adds the specified buttons to the toolbar.
 *
 * @param hwnd Handle to the parent window for the toolbar.
 * @param ws Specifies the window styles for the toolbar. This parameter must specify at least the
 *   WS_CHILD style.
 * @param wID Control identifier for the toolbar.
 * @param nBitmaps Number of button images contained in the bitmap specified by hBMInst and wBMID.
 * @param hBMInst Handle to the module instance with the executable file that contains the bitmap
 *   resource.
 * @param wBMID Resource identifier for the bitmap resource. If hBMInst is NULL, this parameter must
 *   be a valid bitmap handle.
 * @param lpButtons Long pointer to an array of TBBUTTON structures that contain information about
 *   the buttons to add to the toolbar.
 * @param iNumButtons Number of buttons to add to the toolbar.
 * @param dxButton Specifies the width, in pixels, of the buttons to add to the toolbar.
 * @param dyButton Specifies the height, in pixels, of the buttons to add to the toolbar.
 * @param dxBitmap Specifies the width, in pixels, of the button images to add to the buttons in the
 *   toolbar.
 * @param dyBitmap Specifies the height, in pixels, of the button images to add to the buttons in
 *   the toolbar.
 * @param uStructSize Unsigned integer that contains the size of a TBBUTTON structure.
 *
 * @return The window handle to the toolbar indicates success. NULL indicates failure. To get
 *   extended error information, call GetLastError.
 */
WINCOMMCTRLAPI HWND WINAPI CreateToolbarEx(HWND hwnd, DWORD ws, UINT wID, int nBitmaps,
                        HINSTANCE hBMInst, UINT wBMID, LPCTBBUTTON lpButtons,
                        int iNumButtons, int dxButton, int dyButton,
                        int dxBitmap, int dyBitmap, UINT uStructSize);

#define TBSTATE_CHECKED         0x01
#define TBSTATE_PRESSED         0x02
#define TBSTATE_ENABLED         0x04
#define TBSTATE_HIDDEN          0x08
#define TBSTATE_INDETERMINATE   0x10
#define TBSTATE_WRAP            0x20
#if (_WIN32_IE >= 0x0300)
#define TBSTATE_ELLIPSES        0x40
#endif
#if (_WIN32_IE >= 0x0400)
#define TBSTATE_HIGHLIGHTED     0x80
#endif

#define TBSTYLE_BUTTON          0x0000
#define TBSTYLE_SEP             0x0001
#define TBSTYLE_CHECK           0x0002
#define TBSTYLE_GROUP           0x0004
#define TBSTYLE_CHECKGROUP      (TBSTYLE_GROUP | TBSTYLE_CHECK)
#if (_WIN32_IE >= 0x0300)
#define TBSTYLE_DROPDOWN        0x0008
#endif
#if (_WIN32_IE >= 0x0400)
#define TBSTYLE_AUTOSIZE        0x0010 // automatically calculate the cx of the button
#endif

#define TBSTYLE_TOOLTIPS        0x0100
#define TBSTYLE_WRAPABLE        0x0200
#define TBSTYLE_ALTDRAG         0x0400
#if (_WIN32_IE >= 0x0300)
#define TBSTYLE_FLAT            0x0800
#define TBSTYLE_LIST            0x1000
#define TBSTYLE_CUSTOMERASE     0x2000
#endif
#if (_WIN32_IE >= 0x0400)
#define TBSTYLE_TRANSPARENT     0x8000
#endif

/**
 * This message enables or disables the specified button in a toolbar.
 *
 * @param idButton Command identifier of the button to enable or disable.
 * @param fEnable Enable flag. If set to TRUE, the button is enabled. If set to FALSE, the button is
 *   disabled.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define TB_ENABLEBUTTON         (WM_USER + 1)
/**
 * This message checks or unchecks a specified button in a toolbar.
 *
 * @param idButton Command identifier of the button to check.
 * @param fCheck Check flag. If set to TRUE, the check is added. If set to FALSE, the check is
 *   removed.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define TB_CHECKBUTTON          (WM_USER + 2)
/**
 * This message releases the specified button in a toolbar.
 *
 * @param idButton Command identifier of the button to press or release.
 * @param fPress Press flag. If set to TRUE, the button is pressed. If set to FALSE, the button is
 *   released.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define TB_PRESSBUTTON          (WM_USER + 3)
/**
 * This message hides or shows the specified button in a toolbar.
 *
 * @param idButton Command identifier of the button to hide or show.
 * @param fShow Show flag. If set to TRUE, the button is hidden. If set to FALSE, the button is
 *   shown.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define TB_HIDEBUTTON           (WM_USER + 4)
/**
 * This message sets or clears the indeterminate state of the specified button in a toolbar.
 *
 * @param idButton Command identifier of the button for which indeterminate state is to be set or
 *   cleared.
 * @param fIndeterminate Indeterminate flag. If set to TRUE, the indeterminate state is set. If set
 *   to FALSE, the state is cleared.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define TB_INDETERMINATE        (WM_USER + 5)
#if (_WIN32_IE >= 0x0400)
/**
 * This message sets the highlight state of a specified button in a toolbar control.
 *
 * @param idButton Command identifier for a toolbar button.
 * @param fHighlight Boolean that specifies the highlight state to be set. If this value is TRUE,
 *   the button is highlighted; if FALSE, the button is set to its default state.
 *
 * @return Nonzero indicates success. Zero indicates otherwise.
 */
#define TB_HIGHLIGHTBUTTON      (WM_USER + 6)
#endif
/**
 * This message determines whether the specified button in a toolbar is enabled.
 *
 * @param idButton Command identifier of the button.
 *
 * @return Nonzero indicates that the button is enables. Zero indicates that the button is disabled.
 */
#define TB_ISBUTTONENABLED      (WM_USER + 9)
/**
 * This message determines whether the specified button in a toolbar is checked.
 *
 * @param idButton Command identifier of the button.
 *
 * @return Nonzero indicates that the button is checked. Zero indicates otherwise.
 */
#define TB_ISBUTTONCHECKED      (WM_USER + 10)
/**
 * This message determines whether the specified button in a toolbar is pressed.
 *
 * @param idButton Command identifier of the button.
 *
 * @return Nonzero indicates that the button is pressed. Zero indicates otherwise.
 */
#define TB_ISBUTTONPRESSED      (WM_USER + 11)
/**
 * This message determines whether the specified button in a toolbar is hidden.
 *
 * @param idButton Command identifier of the button.
 *
 * @return Nonzero indicates that the button is hidden. Zero indicates otherwise.
 */
#define TB_ISBUTTONHIDDEN       (WM_USER + 12)
/**
 * This message determines whether the specified button in a toolbar is indeterminate.
 *
 * @param idButton Command identifier of the button.
 *
 * @return Nonzero indicates that the button is indeterminate. Zero indicates otherwise.
 */
#define TB_ISBUTTONINDETERMINATE (WM_USER + 13)
#if (_WIN32_IE >= 0x0400)
/**
 * This message checks the highlight state of a toolbar button.
 *
 * @param idButton Command identifier for a toolbar button.
 *
 * @return Nonzero indicates that the button is highlighted. Zero indicates otherwise.
 */
#define TB_ISBUTTONHIGHLIGHTED  (WM_USER + 14)
#endif
/**
 * This message sets the state for the specified button in a toolbar.
 *
 * @param idButton Command identifier of the button.
 * @param fState State flags. This parameter can be a combination of values. For information about
 *   toolbar button state values, see the Windows CE User Interface Services Guide.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define TB_SETSTATE             (WM_USER + 17)
/**
 * This message retrieves information about the state of the specified button in a toolbar, such as
 * whether it is enabled, pressed, or checked.
 *
 * @param idButton Command identifier of the button for which to retrieve information.
 *
 * @return The button state information indicates success. -1 indicates failure. The button state
 *   information can be a combination of values. For information about toolbar button state values,
 *   see the Windows CE User Interface Services Guide.
 */
#define TB_GETSTATE             (WM_USER + 18)
/**
 * This message adds one or more images to the list of button images available for a toolbar.
 *
 * @param nButtons Number of button images in the bitmap. If lptbab specifies a system-defined
 *   bitmap, this parameter is ignored.
 * @param lptbab Long pointer to a TBADDBITMAP structure that contains the identifier of a bitmap
 *   resource and the handle to the module instance with the executable file that contains the bitmap
 *   resource.
 *
 * @return The index of the first new image indicates success. -1 indicates failure.
 *
 * The bitmap specified in the lptbab parameter can contain multiple images. The number of images in
 * the bitmap must be specified in the nButtons parameter.
 *
 * The bitmap width should be nButtons multiplied by the image width, and the bitmap height should
 * be equal to the image height.
 *
 * The default image width is 16 pixels and the default image height is 15 pixels. The default image
 * width and height can be changed using TB_SETBITMAPSIZE. If the size of the bitmap is not the
 * default or if you have multiple images in a bitmap, you must call TB_SETBITMAPSIZE to change the
 * default size settings.
 */
#define TB_ADDBITMAP            (WM_USER + 19)

#ifdef _WIN32
/**
 * This structure adds a bitmap that contains button images to a toolbar.
 *
 * The TBADDBITMAP structure is used with the TB_ADDBITMAP message.
 */
typedef struct tagTBADDBITMAP {
        /**
         * Handle to the module instance with the executable file that contains a bitmap resource. You can
         * add the system-defined button bitmaps to the list by specifying HINST_COMMCTRL as the hInst
         * member and one of the following values as the nID member: Value Description IDB_STD_LARGE_COLOR
         * Adds large, color standard bitmaps. IDB_STD_SMALL_COLOR Adds small, color standard bitmaps.
         * IDB_VIEW_LARGE_COLOR Adds large, color view bitmaps. IDB_VIEW_SMALL_COLOR Adds small, color view
         * bitmaps.
         */
        HINSTANCE       hInst;
        /**
         * Resource identifier of the bitmap resource that contains the button images. If hInst is NULL,
         * this parameter must be the handle to a bitmap that contains the button images.
         *
         * The Windows header files provide the following values to be used as indexes to the standard and
         * view bitmaps: Value Description STD_COPY Specifies the copy image. STD_CUT Specifies the cut
         * image. STD_DELETE Specifies the delete image. STD_FILENEW Specifies the new file image.
         * STD_FILEOPEN Specifies the open file image. STD_FILESAVE Specifies the save file image. STD_FIND
         * Specifies the find image. STD_HELP Specifies the help image. STD_PASTE Specifies the paste image.
         * STD_PRINT Specifies the print image. STD_PRINTPRE Specifies the print preview image.
         * STD_PROPERTIES Specifies the properties image. STD_REDOW Specifies the redo image. STD_REPLACE
         * Specifies the replace image. STD_UNDO Specifies the undo image. VIEW_DETAILS Specifies the view
         * details image. VIEW_LARGEICONS Specifies the view large icons image. VIEW_LIST Specifies the view
         * list image. VIEW_SMALLICONS Specifies the view small icons image. VIEW_SORTDATE Specifies the
         * sort by date image. VIEW_SORTNAME Specifies the sort by name image. VIEW_SORTSIZE Specifies the
         * sort by size image. VIEW_SORTTYPE Specifies the sort by type image.
         */
        UINT            nID;
} TBADDBITMAP, *LPTBADDBITMAP;

#define HINST_COMMCTRL          ((HINSTANCE)-1)
#define IDB_STD_SMALL_COLOR     0
#define IDB_STD_LARGE_COLOR     1
#define IDB_VIEW_SMALL_COLOR    4
#define IDB_VIEW_LARGE_COLOR    5

// icon indexes for standard bitmap

#define STD_CUT                 0
#define STD_COPY                1
#define STD_PASTE               2
#define STD_UNDO                3
#define STD_REDOW               4
#define STD_DELETE              5
#define STD_FILENEW             6
#define STD_FILEOPEN            7
#define STD_FILESAVE            8
#define STD_PRINTPRE            9
#define STD_PROPERTIES          10
#define STD_HELP                11
#define STD_FIND                12
#define STD_REPLACE             13
#define STD_PRINT               14

// icon indexes for standard view bitmap

#define VIEW_LARGEICONS         0
#define VIEW_SMALLICONS         1
#define VIEW_LIST               2
#define VIEW_DETAILS            3
#define VIEW_SORTNAME           4
#define VIEW_SORTSIZE           5
#define VIEW_SORTDATE           6
#define VIEW_SORTTYPE           7
#define VIEW_PARENTFOLDER       8
#define VIEW_NETCONNECT         9
#define VIEW_NETDISCONNECT      10
#define VIEW_NEWFOLDER          11

#endif

#if (_WIN32_IE >= 0x0400)
#define TB_ADDBUTTONSA          (WM_USER + 20)
#define TB_INSERTBUTTONA        (WM_USER + 21)
#else
/**
 * This message adds one or more buttons to a toolbar.
 *
 * @param uNumButtons Number of buttons to add.
 * @param lpButtons Long pointer to an array of TBBUTTON structures that contain information about
 *   the buttons to add. There must be the same number of elements in the array as buttons specified
 *   by uNumButtons.
 *
 * @return True indicates success. FALSE indicates failure.
 */
#define TB_ADDBUTTONS           (WM_USER + 20)
/**
 * This message inserts a button in a toolbar.
 *
 * @param iButton Zero-based index of a button. The message inserts the new button to the left of
 *   this button.
 * @param lpButton Long pointer to a TBBUTTON structure that contains information about the button
 *   to insert.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define TB_INSERTBUTTON         (WM_USER + 21)
#endif

/**
 * This message deletes a button from the toolbar.
 *
 * @param iButton Zero-based index of the button to delete.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define TB_DELETEBUTTON         (WM_USER + 22)
/**
 * This message retrieves information about the specified button in a toolbar.
 *
 * @param iButton Zero-based index of the button for which to retrieve information.
 * @param lpButton Long pointer to the TBBUTTON structure that receives the button information.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define TB_GETBUTTON            (WM_USER + 23)
/**
 * This message retrieves a count of the buttons currently in the toolbar.
 *
 * @return The count of the buttons indicates success.
 */
#define TB_BUTTONCOUNT          (WM_USER + 24)
/**
 * This message retrieves the zero-based index for the button associated with the specified command
 * identifier.
 *
 * @param idButton Command identifier associated with the button.
 *
 * @return The zero-based index for the button indicates success.
 */
#define TB_COMMANDTOINDEX       (WM_USER + 25)

#define TB_ADDSTRINGA           (WM_USER + 28)
#define TB_ADDSTRINGW           (WM_USER + 77)
/**
 * This message retrieves the bounding rectangle of a button in a toolbar.
 *
 * @param iButton Zero-based index of the button for which to retrieve information.
 * @param lprc Long pointer to a RECT structure that receives the coordinates of the bounding
 *   rectangle.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define TB_GETITEMRECT          (WM_USER + 29)
/**
 * This message specifies the size of the TBBUTTON structure.
 *
 * @param cb Size, in bytes, of the TBBUTTON structure.
 *
 * @return None.
 *
 * The system uses the size to determine which version of the common control dynamic-link library
 * (DLL) is being used.
 */
#define TB_BUTTONSTRUCTSIZE     (WM_USER + 30)
/**
 * This message sets the size of the buttons to be added to a toolbar.
 *
 * @param dxButton Specifies the width, in pixels, of the buttons.
 * @param dyButton Specifies the height, in pixels, of the buttons.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define TB_SETBUTTONSIZE        (WM_USER + 31)
/**
 * This message sets the size of the bitmapped images to be added to a toolbar.
 *
 * @param dxBitmap Specifies the width, in pixels, of the bitmapped images.
 * @param dyBitmap Specifies the height, in pixels, of the bitmapped images.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * The default image width is 16 pixels and the default image height is 15 pixels. If the size of
 * the bitmap is not the default or if you have multiple images in a bitmap, you must call
 * TB_SETBITMAPSIZE to change the default size settings. Otherwise, the bitmap or image is truncated
 * or is not displayed.
 */
#define TB_SETBITMAPSIZE        (WM_USER + 32)
/**
 * This message causes a toolbar to be resized.
 *
 * @return None.
 */
#define TB_AUTOSIZE             (WM_USER + 33)
/**
 * This message retrieves the handle to the ToolTip control, if any, associated with the toolbar.
 *
 * @return Returns the handle to the ToolTip control, or NULL if the toolbar has no associated
 *   ToolTip.
 */
#define TB_GETTOOLTIPS          (WM_USER + 35)
#ifndef UNDER_CE // TB_SETTOOLTIPS is used differently on WinCE, so its definition has changed
/**
 * This message adds an array of ToolTip strings to a toolbar.
 *
 * @param hwndToolTip Handle to the ToolTip control.
 *
 * @return None.
 *
 * The TB_SETTOOLTIPS message in Windows CE is different from the TB_SETTOOLTIPS message in Windows
 * 95 and Windows NT.
 *
 * Windows CE does not support ToolTip controls, so instead of taking a handle to a ToolTip control
 * as its sole parameter, the TB_SETTOOLTIPS message in Windows CE takes both a wParam and an
 * lParam. The wParam represents the number of ToolTip strings to associate with the toolbar, and
 * the lParam is the array of strings to be displayed as ToolTips.
 *
 * In Windows CE, only toolbar buttons can have ToolTip strings; menus and combo boxes cannot.
 *
 * The TB_SETTOOLTIPS message uses the memory address passed in the lpToolTips parameter. Do not
 * release the memory allocated for the ToolTip string array until the program exits.
 */
#define TB_SETTOOLTIPS          (WM_USER + 36)
#else
/**
 * This message adds an array of ToolTip strings to a toolbar.
 *
 * @param hwndToolTip Handle to the ToolTip control.
 *
 * @return None.
 *
 * The TB_SETTOOLTIPS message in Windows CE is different from the TB_SETTOOLTIPS message in Windows
 * 95 and Windows NT.
 *
 * Windows CE does not support ToolTip controls, so instead of taking a handle to a ToolTip control
 * as its sole parameter, the TB_SETTOOLTIPS message in Windows CE takes both a wParam and an
 * lParam. The wParam represents the number of ToolTip strings to associate with the toolbar, and
 * the lParam is the array of strings to be displayed as ToolTips.
 *
 * In Windows CE, only toolbar buttons can have ToolTip strings; menus and combo boxes cannot.
 *
 * The TB_SETTOOLTIPS message uses the memory address passed in the lpToolTips parameter. Do not
 * release the memory allocated for the ToolTip string array until the program exits.
 */
#define TB_SETTOOLTIPS          (WM_USER + 81)
#endif // !UNDER_CE
/**
 * This message sets the parent window for a toolbar.
 *
 * @param hwndParent Handle to the window to receive notification messages.
 *
 * @return The return value is a handle to the previous notification window, or NULL if there is no
 *   previous notification window.
 */
#define TB_SETPARENT            (WM_USER + 37)
/**
 * This message sets the number of rows of buttons in a toolbar.
 *
 * @param cRows Number of rows requested. The minimum number of rows is one, and the maximum number
 *   of rows is equal to the number of buttons in the toolbar.
 * @param fLarger Flag that indicates whether to create more rows than requested when the system
 *   cannot create the number of rows specified by cRows. If set to TRUE, the system creates more
 *   rows. If set to FALSE, the system creates fewer rows.
 * @param lprc Long pointer to a RECT structure that receives the bounding rectangle of the toolbar
 *   after the rows are set.
 *
 * @return None.
 */
#define TB_SETROWS              (WM_USER + 39)
/**
 * This message retrieves the number of rows of buttons in a toolbar with the TBSTYLE_WRAPABLE
 * style.
 *
 * @return The number of rows indicates success.
 */
#define TB_GETROWS              (WM_USER + 40)
/**
 * This message sets the command identifier of a toolbar button.
 *
 * @param index Zero-based index of the button for which the command identifier is to be set.
 * @param cmdId Command identifier.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define TB_SETCMDID             (WM_USER + 42)
/**
 * This message changes the bitmap for a button in a toolbar.
 *
 * @param idButton Command identifier of the button that is to receive a new bitmap.
 * @param iBitmap Zero-based index of an image in the toolbar's image list. The system displays the
 *   specified image in the button.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define TB_CHANGEBITMAP         (WM_USER + 43)
/**
 * This message retrieves the index of the bitmap associated with a button in a toolbar.
 *
 * @param idButton Command identifier of the button whose bitmap index is to be retrieved.
 *
 * @return The index of the bitmap indicates success. Zero indicates failure.
 */
#define TB_GETBITMAP            (WM_USER + 44)
#define TB_GETBUTTONTEXTA       (WM_USER + 45)
#define TB_GETBUTTONTEXTW       (WM_USER + 75)
/**
 * This message replaces an existing bitmap with a new bitmap.
 *
 * @param ptbrb Pointer to a TBREPLACEBITMAP structure that contains the information of the bitmap
 *   to be replaced and the new bitmap.
 *
 * @return Nonzero indicates success. Zero indicates otherwise.
 */
#define TB_REPLACEBITMAP        (WM_USER + 46)
#if (_WIN32_IE >= 0x0300)
/**
 * This message sets the indentation for the first button in a toolbar control.
 *
 * @param iIndent Specifies the indentation, in pixels.
 *
 * @return Nonzero indicates success. Zero indicates otherwise.
 */
#define TB_SETINDENT            (WM_USER + 47)
/**
 * This message sets the image list that the toolbar will use to display buttons that are in their
 * default state.
 *
 * @param himlNew Handle to the image list that will be set. If this parameter is NULL, no images
 *   are displayed in the buttons.
 *
 * @return Returns the handle to the image list previously used to display buttons in their default
 *   state, or NULL if no image list was previously set.
 *
 * A toolbar control uses himlNew to display buttons in their default state; that is, when they are
 * not hot or disabled.
 */
#define TB_SETIMAGELIST         (WM_USER + 48)
/**
 * This message retrieves the image list that a toolbar control uses to display buttons in their
 * default state. A toolbar control uses this image list to display buttons in their default state;
 * that is, when they are not hot or disabled.
 *
 * @return Returns the handle to the image list or NULL if no image list is set.
 */
#define TB_GETIMAGELIST         (WM_USER + 49)
/**
 * This message loads bitmaps into a toolbar control's image list.
 *
 * @param iBitmapID Identifier of a bitmap that contains the images to be loaded. If hinst is
 *   HINST_COMMCTRL, this parameter specifies a set of standard toolbar button bitmaps, shown in the
 *   following list. Otherwise, this parameter must be the identifier of a bitmap resource that will
 *   be added to the image list as a single image. Value Description IDB_STD_LARGE_COLOR Standard
 *   bitmaps in large size IDB_STD_SMALL_COLOR Standard bitmaps in small size IDB_VIEW_LARGE_COLOR
 *   View bitmaps in large size IDB_VIEW_SMALL_COLOR View bitmaps in small size
 * @param hinst Program instance handle to the calling application. This parameter can be
 *   HINST_COMMCTRL to load a standard image list.
 *
 * @return Returns an INT value that represents the count of images in the image list, not including
 *   the one just added. Returns zero if the toolbar has no image list or if the existing image list
 *   is empty.
 *
 * If your application specifies HINST_COMMCTRL, then you must use the proper image index values
 * when you prepare TBBUTTON structures prior to sending the TB_ADDBUTTONS message. For a list of
 * image index values for these preset bitmaps, see "Toolbar Standard Button Image Index Values."
 *
 * Windows CE does not support IDB_HIST_LARGE_COLOR and IDB_HIST_SMALL_COLOR values for the
 * iBitmapID parameter.
 */
#define TB_LOADIMAGES           (WM_USER + 50)
/**
 * This message retrieves the bounding rectangle for a specified toolbar button.
 *
 * @param iID Button identifier.
 * @param lprc Returns nonzero if successful, or zero otherwise. A RECT structure that receives the
 *   bounding rectangle information.
 *
 * @return Nonzero indicates success. Zero indicates otherwise.
 */
#define TB_GETRECT              (WM_USER + 51) // wParam is the Cmd instead of index
/**
 * This message sets the image list that the toolbar control will use to display disabled buttons.
 *
 * @param himlNewDisabled Handle to the image list to be set.
 *
 * @return Returns the handle to the image list previously used to display disabled buttons, or NULL
 *   if no image list was previously set.
 */
#define TB_SETDISABLEDIMAGELIST (WM_USER + 54)
/**
 * This message retrieves the image list that a toolbar control uses to display disabled buttons.
 *
 * @return Returns the handle to the disabled image list or NULL if no disabled image list is set.
 */
#define TB_GETDISABLEDIMAGELIST (WM_USER + 55)
/**
 * This message sets the style for a toolbar control.
 *
 * @param dwStyle Specifies the styles to be set for the control. It can be a combination of toolbar
 *   control styles.
 */
#define TB_SETSTYLE             (WM_USER + 56)
/**
 * This message retrieves the styles currently in use for a toolbar control.
 *
 * @return Returns a DWORD value that is a combination of toolbar control styles.
 */
#define TB_GETSTYLE             (WM_USER + 57)
/**
 * This message retrieves the current width and height of toolbar buttons, in pixels.
 *
 * @return Returns a DWORD value that contains the width and height values in the low-order word and
 *   high-order word, respectively.
 */
#define TB_GETBUTTONSIZE        (WM_USER + 58)
/**
 * This message sets the minimum and maximum button widths in the toolbar control.
 *
 * @param cxMin Minimum button width, in pixels. Toolbar buttons are never narrower than this value.
 * @param cxMax Maximum button width, in pixels. If button text is too wide, the control displays it
 *   with ellipsis points.
 *
 * @return Nonzero indicates success. Zero indicates otherwise.
 */
#define TB_SETBUTTONWIDTH       (WM_USER + 59)
/**
 * This message sets the maximum number of text rows displayed on a toolbar button.
 *
 * @param iMaxRows Maximum number of rows to be set.
 *
 * @return Nonzero indicates success. Zero indicates otherwise.
 */
#define TB_SETMAXTEXTROWS       (WM_USER + 60)
/**
 * This message retrieves the maximum number of text rows that can be displayed on a toolbar button.
 *
 * @return Returns an INT value representing the maximum number of text rows that the control
 *   displays for a button.
 */
#define TB_GETTEXTROWS          (WM_USER + 61)
#endif      // _WIN32_IE >= 0x0300

#ifdef UNICODE
/**
 * This message retrieves the text of a button in a toolbar.
 *
 * @param idButton Command identifier of the button for which to retrieve text.
 * @param lpszText Long pointer to a buffer that receives the button text.
 *
 * @return The length-in characters and not including the terminating null character-of the string
 *   copied to the specified buffer indicates success. -1 indicates failure.
 */
#define TB_GETBUTTONTEXT        TB_GETBUTTONTEXTW
#define TB_SAVERESTORE          TB_SAVERESTOREW
/**
 * This message adds a new string to the list of strings available for a toolbar.
 *
 * @param hinst Handle to the module instance with an executable file that contains the string
 *   resource. If idString points to one or more strings to add, this parameter is zero.
 * @param idString Resource identifier of the string resource, or the address of a buffer that
 *   contains one or more null-terminated strings to add to the list, depending on the value of hinst.
 *   The last string must be terminated with two null characters.
 *
 * @return The index of the first new string indicates success. -1 indicates failure.
 *
 * The resource identifier in the idString parameter has to reference a single string without
 * substrings or separators.
 */
#define TB_ADDSTRING            TB_ADDSTRINGW
#else
/**
 * This message retrieves the text of a button in a toolbar.
 *
 * @param idButton Command identifier of the button for which to retrieve text.
 * @param lpszText Long pointer to a buffer that receives the button text.
 *
 * @return The length-in characters and not including the terminating null character-of the string
 *   copied to the specified buffer indicates success. -1 indicates failure.
 */
#define TB_GETBUTTONTEXT        TB_GETBUTTONTEXTA
#define TB_SAVERESTORE          TB_SAVERESTOREA
/**
 * This message adds a new string to the list of strings available for a toolbar.
 *
 * @param hinst Handle to the module instance with an executable file that contains the string
 *   resource. If idString points to one or more strings to add, this parameter is zero.
 * @param idString Resource identifier of the string resource, or the address of a buffer that
 *   contains one or more null-terminated strings to add to the list, depending on the value of hinst.
 *   The last string must be terminated with two null characters.
 *
 * @return The index of the first new string indicates success. -1 indicates failure.
 *
 * The resource identifier in the idString parameter has to reference a single string without
 * substrings or separators.
 */
#define TB_ADDSTRING            TB_ADDSTRINGA
#endif

/**
 * This structure is used with the TB_REPLACEBITMAP message to replace one toolbar bitmap with
 * another.
 */
typedef struct {
    /**
     * Module instance handle of the bitmap resource being replaced.
     */
    HINSTANCE       hInstOld;
    /**
     * Resource identifier of the bitmap being replaced.
     */
    UINT            nIDOld;
    /**
     * Module instance handle that contains the new bitmap resource.
     */
    HINSTANCE       hInstNew;
    /**
     * Resource identifier of the new bitmap.
     */
    UINT            nIDNew;
    /**
     * Number of button images contained in the new bitmap.
     */
    int             nButtons;
} TBREPLACEBITMAP, *LPTBREPLACEBITMAP;

#ifdef _WIN32

#define TBBF_LARGE              0x0001

/**
 * This message retrieves the flags for the current bitmap.
 *
 * @return Returns a DWORD value that contains the bitmap flags. If this value is zero, the toolbar
 *   is using a small bitmap. If the TBBF_LARGE flag is set, the toolbar is using a large bitmap.
 */
#define TB_GETBITMAPFLAGS       (WM_USER + 41)

#if (_WIN32_IE >= 0x0400)
#define TBIF_IMAGE              0x00000001
#define TBIF_TEXT               0x00000002
#define TBIF_STATE              0x00000004
#define TBIF_STYLE              0x00000008
#define TBIF_LPARAM             0x00000010
#define TBIF_COMMAND            0x00000020
#define TBIF_SIZE               0x00000040

/**
 * This structure contains or receives information for a specific button in a toolbar.
 */
typedef struct {
    /**
     * Size of the structure, in bytes. This member must be filled in prior to sending the associated
     * message.
     */
    UINT cbSize;
    /**
     * Indicates which members contain valid information. This member must be filled in prior to sending
     * the associated message. This can be a combination of one or more of the following values: Value
     * Description TBIF_COMMAND The idCommand member contains valid information or is being requested.
     * TBIF_IMAGE The iImage member contains valid information or is being requested. TBIF_LPARAM The
     * lParam member contains valid information or is being requested. TBIF_SIZE The cx member contains
     * valid information or is being requested. TBIF_STATE The fsState member contains valid information
     * or is being requested. TBIF_STYLE The fsStyle member contains valid information or is being
     * requested. TBIF_TEXT The pszText member contains valid information or is being requested.
     */
    DWORD dwMask;
    /**
     * Command identifier of the button.
     */
    int idCommand;
    /**
     * Image index of the button.
     */
    int iImage;
    /**
     * State flags of the button. This is a combination of one or more of the toolbar button states.
     */
    BYTE fsState;
    /**
     * Style flags of the button. This is a combination of one or more of the toolbar button styles.
     */
    BYTE fsStyle;
    /**
     * Specifies the width of the button, in pixels.
     */
    WORD cx;
    /**
     * Specifies the application defined 32-bit value associated with the button.
     */
    DWORD lParam;
    /**
     * Pointer to a character buffer that contains or receives the button text.
     */
    LPSTR pszText;
    /**
     * Size of the buffer at pszText. If the button information is being set, this member is ignored.
     */
    int cchText;
} TBBUTTONINFOA, *LPTBBUTTONINFOA;

/**
 * This structure contains or receives information for a specific button in a toolbar.
 */
typedef struct {
    /**
     * Size of the structure, in bytes. This member must be filled in prior to sending the associated
     * message.
     */
    UINT cbSize;
    /**
     * Indicates which members contain valid information. This member must be filled in prior to sending
     * the associated message. This can be a combination of one or more of the following values: Value
     * Description TBIF_COMMAND The idCommand member contains valid information or is being requested.
     * TBIF_IMAGE The iImage member contains valid information or is being requested. TBIF_LPARAM The
     * lParam member contains valid information or is being requested. TBIF_SIZE The cx member contains
     * valid information or is being requested. TBIF_STATE The fsState member contains valid information
     * or is being requested. TBIF_STYLE The fsStyle member contains valid information or is being
     * requested. TBIF_TEXT The pszText member contains valid information or is being requested.
     */
    DWORD dwMask;
    /**
     * Command identifier of the button.
     */
    int idCommand;
    /**
     * Image index of the button.
     */
    int iImage;
    /**
     * State flags of the button. This is a combination of one or more of the toolbar button states.
     */
    BYTE fsState;
    /**
     * Style flags of the button. This is a combination of one or more of the toolbar button styles.
     */
    BYTE fsStyle;
    /**
     * Specifies the width of the button, in pixels.
     */
    WORD cx;
    /**
     * Specifies the application defined 32-bit value associated with the button.
     */
    DWORD lParam;
    /**
     * Pointer to a character buffer that contains or receives the button text.
     */
    LPWSTR pszText;
    /**
     * Size of the buffer at pszText. If the button information is being set, this member is ignored.
     */
    int cchText;
} TBBUTTONINFOW, *LPTBBUTTONINFOW;

#ifdef UNICODE
#define TBBUTTONINFO TBBUTTONINFOW
#define LPTBBUTTONINFO LPTBBUTTONINFOW
#else
#define TBBUTTONINFO TBBUTTONINFOA
#define LPTBBUTTONINFO LPTBBUTTONINFOA
#endif


// BUTTONINFO APIs do NOT support the string pool.
#define TB_GETBUTTONINFOW        (WM_USER + 63)
#define TB_SETBUTTONINFOW        (WM_USER + 64)
#define TB_GETBUTTONINFOA        (WM_USER + 65)
#define TB_SETBUTTONINFOA        (WM_USER + 66)
#ifdef UNICODE
/**
 * This message retrieves the information for a button in a toolbar.
 *
 * @param iID Button identifier.
 * @param lptbbi Long pointer to a TBBUTTONINFO structure that receives the button information. The
 *   cbSize and dwMask members of this structure must be filled in prior to sending this message.
 *
 * @return Nonzero indicates success. Zero indicates otherwise.
 */
#define TB_GETBUTTONINFO        TB_GETBUTTONINFOW
/**
 * This message sets the information for an existing button in a toolbar.
 *
 * @param iID Button identifier.
 * @param lptbbi Long pointer to a TBBUTTONINFO structure that contains the new button information.
 *   The cbSize and dwMask members of this structure must be filled in prior to sending this message.
 *
 * @return Nonzero indicates success. Zero indicates otherwise.
 */
#define TB_SETBUTTONINFO        TB_SETBUTTONINFOW
#else
/**
 * This message retrieves the information for a button in a toolbar.
 *
 * @param iID Button identifier.
 * @param lptbbi Long pointer to a TBBUTTONINFO structure that receives the button information. The
 *   cbSize and dwMask members of this structure must be filled in prior to sending this message.
 *
 * @return Nonzero indicates success. Zero indicates otherwise.
 */
#define TB_GETBUTTONINFO        TB_GETBUTTONINFOA
/**
 * This message sets the information for an existing button in a toolbar.
 *
 * @param iID Button identifier.
 * @param lptbbi Long pointer to a TBBUTTONINFO structure that contains the new button information.
 *   The cbSize and dwMask members of this structure must be filled in prior to sending this message.
 *
 * @return Nonzero indicates success. Zero indicates otherwise.
 */
#define TB_SETBUTTONINFO        TB_SETBUTTONINFOA
#endif


#define TB_INSERTBUTTONW        (WM_USER + 67)
#define TB_ADDBUTTONSW          (WM_USER + 68)

#define TB_HITTEST              (WM_USER + 69)


// New post Win95/NT4 for InsertButton and AddButton.  if iString member 
// is a pointer to a string, it will be handled as a string like listview
// (although LPSTR_TEXTCALLBACK is not supported).
#ifdef UNICODE
/**
 * This message inserts a button in a toolbar.
 *
 * @param iButton Zero-based index of a button. The message inserts the new button to the left of
 *   this button.
 * @param lpButton Long pointer to a TBBUTTON structure that contains information about the button
 *   to insert.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define TB_INSERTBUTTON         TB_INSERTBUTTONW
/**
 * This message adds one or more buttons to a toolbar.
 *
 * @param uNumButtons Number of buttons to add.
 * @param lpButtons Long pointer to an array of TBBUTTON structures that contain information about
 *   the buttons to add. There must be the same number of elements in the array as buttons specified
 *   by uNumButtons.
 *
 * @return True indicates success. FALSE indicates failure.
 */
#define TB_ADDBUTTONS           TB_ADDBUTTONSW
#else
/**
 * This message inserts a button in a toolbar.
 *
 * @param iButton Zero-based index of a button. The message inserts the new button to the left of
 *   this button.
 * @param lpButton Long pointer to a TBBUTTON structure that contains information about the button
 *   to insert.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define TB_INSERTBUTTON         TB_INSERTBUTTONA
/**
 * This message adds one or more buttons to a toolbar.
 *
 * @param uNumButtons Number of buttons to add.
 * @param lpButtons Long pointer to an array of TBBUTTON structures that contain information about
 *   the buttons to add. There must be the same number of elements in the array as buttons specified
 *   by uNumButtons.
 *
 * @return True indicates success. FALSE indicates failure.
 */
#define TB_ADDBUTTONS           TB_ADDBUTTONSA
#endif

/**
 * This message sets the text drawing flags for the toolbar.
 *
 * @param dwMask A combination of one or more of the DT_* flags, specified in DrawText, that
 *   specifies which bits in dwDTFlags are used when drawing the text.
 * @param dwDTFlags A combination of one or more of the DT_* flags, specified in DrawText, that
 *   specify how the button text will be drawn. This value is passed to DrawText when the button text
 *   is drawn.
 *
 * @return Returns the previous text drawing flags.
 *
 * The dwMask parameter allows you to specify which flags will be used when drawing the text, even
 * if these flags are turned off. For example, if you do not want the DT_CENTER flag used when
 * drawing text, you would add the DT_CENTER flag to dwMask and not specify the DT_CENTER flag in
 * dwDTFlags. This prevents the control from passing the DT_CENTER flag to DrawText.
 */
#define TB_SETDRAWTEXTFLAGS     (WM_USER + 70)  // wParam == mask lParam == bit values

#endif         // _WIN32_IE >= 0x0400

#define TBN_GETBUTTONINFOA      (TBN_FIRST-0)
#define TBN_GETBUTTONINFOW      (TBN_FIRST-20)
/**
 * This notification message notifies a toolbar's parent window that the user has begun dragging a
 * button in a toolbar. It is sent in the form of a WM_NOTIFY message.
 *
 * @param lpnmtb Long pointer to an NMTOOLBAR structure. The iItem member contains the command
 *   identifier of the button being dragged.
 *
 * @return None.
 */
#define TBN_BEGINDRAG           (TBN_FIRST-1)
/**
 * This notification message notifies the toolbar's parent window that the user has stopped dragging
 * a button in a toolbar. It is sent in the form of a WM_NOTIFY message.
 *
 * @param lpnmtb Long pointer to an NMTOOLBAR structure. The iItem member contains the command
 *   identifier of the button being dragged.
 *
 * @return None.
 */
#define TBN_ENDDRAG             (TBN_FIRST-2)
#if (_WIN32_IE >= 0x0300)
/**
 * This notification message sent by a toolbar control when the user clicks a button that uses the
 * TBSTYLE_DROPDOWN style. It is sent in the form of a WM_NOTIFY message.
 *
 * @param lpnmtb Long pointer to an NMTOOLBAR structure that contains information about this
 *   notification. For this notification message, only the hdr and iItem members of this structure are
 *   valid.
 *
 * @return Returns FALSE to allow the toolbar control to display the drop-down list; returns TRUE to
 *   prevent the control from displaying the list.
 */
#define TBN_DROPDOWN            (TBN_FIRST - 10)
#endif
#if (_WIN32_IE >= 0x0400)
#define TBN_DRAGOUT             (TBN_FIRST - 14) // this is sent when the user clicks down on a button then drags off the button
#endif

#ifdef UNICODE
/**
 * This notification message retrieves toolbar customization information and notifies the toolbar's
 * parent window of any changes being made to the toolbar. It is sent in the form of a WM_NOTIFY
 * message.
 *
 * @param lpnmtb Long pointer to an NMTOOLBAR structure. The iItem member specifies a zero-based
 *   index that provides a count of the buttons the Customize Toolbar dialog box displays as both
 *   available and present on the toolbar. The pszText member specifies the address of the current
 *   button text, and cchText specifies its length in characters. The application should fill the
 *   structure with information about the button.
 *
 * @return TRUE indicates that button information was copied to the specified structure. FALSE
 *   indicates otherwise.
 */
#define TBN_GETBUTTONINFO       TBN_GETBUTTONINFOW
#else
/**
 * This notification message retrieves toolbar customization information and notifies the toolbar's
 * parent window of any changes being made to the toolbar. It is sent in the form of a WM_NOTIFY
 * message.
 *
 * @param lpnmtb Long pointer to an NMTOOLBAR structure. The iItem member specifies a zero-based
 *   index that provides a count of the buttons the Customize Toolbar dialog box displays as both
 *   available and present on the toolbar. The pszText member specifies the address of the current
 *   button text, and cchText specifies its length in characters. The application should fill the
 *   structure with information about the button.
 *
 * @return TRUE indicates that button information was copied to the specified structure. FALSE
 *   indicates otherwise.
 */
#define TBN_GETBUTTONINFO       TBN_GETBUTTONINFOA
#endif

#if (_WIN32_IE >= 0x0300)
#define TBNOTIFYA NMTOOLBARA
#define TBNOTIFYW NMTOOLBARW
#define LPTBNOTIFYA LPNMTOOLBARA
#define LPTBNOTIFYW LPNMTOOLBARW
#else
#define tagNMTOOLBARA  tagTBNOTIFYA
#define NMTOOLBARA     TBNOTIFYA
#define LPNMTOOLBARA   LPTBNOTIFYA
#define tagNMTOOLBARW  tagTBNOTIFYW
#define NMTOOLBARW     TBNOTIFYW
#define LPNMTOOLBARW   LPTBNOTIFYW
#endif

#define TBNOTIFY       NMTOOLBAR
#define LPTBNOTIFY     LPNMTOOLBAR

/**
 * This structure contains information used to process toolbar notification messages. It is
 * identical to the TBNOTIFY structure.
 */
typedef struct tagNMTOOLBARA {
#if (_WIN32_IE >= 0x0300)
    /**
     * NMHDR structure that contains additional information about the notification message.
     */
    NMHDR   hdr;
#endif
    /**
     * Command identifier of the button associated with the notification.
     */
    int     iItem;
    /**
     * TBBUTTON structure that contains information about the toolbar button associated with the
     * notification. This member only contains valid information with the TBN_QUERYINSERT and
     * TBN_QUERYDELETE notifications.
     */
    TBBUTTON tbButton;
    /**
     * Count of characters in the button text.
     */
    int     cchText;
    /**
     * Pointer to a character buffer that contains the button text.
     */
    LPSTR   pszText;
} NMTOOLBARA, FAR* LPNMTOOLBARA;


/**
 * This structure contains information used to process toolbar notification messages. It is
 * identical to the TBNOTIFY structure.
 */
typedef struct tagNMTOOLBARW {
#if (_WIN32_IE >= 0x0300)
    /**
     * NMHDR structure that contains additional information about the notification message.
     */
    NMHDR   hdr;
#endif
    /**
     * Command identifier of the button associated with the notification.
     */
    int     iItem;
    /**
     * TBBUTTON structure that contains information about the toolbar button associated with the
     * notification. This member only contains valid information with the TBN_QUERYINSERT and
     * TBN_QUERYDELETE notifications.
     */
    TBBUTTON tbButton;
    /**
     * Count of characters in the button text.
     */
    int     cchText;
    /**
     * Pointer to a character buffer that contains the button text.
     */
    LPWSTR   pszText;
} NMTOOLBARW, FAR* LPNMTOOLBARW;


#ifdef UNICODE
#define NMTOOLBAR               NMTOOLBARW
#define LPNMTOOLBAR             LPNMTOOLBARW
#else
#define NMTOOLBAR               NMTOOLBARA
#define LPNMTOOLBAR             LPNMTOOLBARA
#endif

#endif

#endif      // NOTOOLBAR


#if (_WIN32_IE >= 0x0300)
//====== REBAR CONTROL ========================================================

#ifndef NOREBAR

#ifdef _WIN32
#define REBARCLASSNAMEW         L"ReBarWindow32"
#define REBARCLASSNAMEA         "ReBarWindow32"

#ifdef  UNICODE
#define REBARCLASSNAME          REBARCLASSNAMEW
#else
#define REBARCLASSNAME          REBARCLASSNAMEA
#endif

#else
#define REBARCLASSNAME          "ReBarWindow"
#endif

#define RBIM_IMAGELIST  0x00000001

#if (_WIN32_IE >= 0x0400)
#define RBS_VARHEIGHT       0x0200
#define RBS_BANDBORDERS     0x0400
#define RBS_FIXEDORDER      0x0800
#ifndef UNDER_CE // WinCE doesn't support RBS_REGISTERDROP
#define RBS_REGISTERDROP    0x1000
#else
#define RBS_SMARTLABELS     0x1000
#endif // UNDER_CE
#define RBS_AUTOSIZE        0x2000
#define RBS_VERTICALGRIPPER  0x4000  // this always has the vertical gripper (default for horizontal mode)
#else
#define RBS_VARHEIGHT       0x00000200
#define RBS_BANDBORDERS     0x00000400
#define RBS_FIXEDORDER      0x00000800
#endif      // _WIN32_IE >= 0x0400


/**
 * This structure contains information that describes rebar control characteristics.
 */
typedef struct tagREBARINFO
{
    /**
     * Size of this structure, in bytes. Your application must fill this member before sending any
     * messages that use the address of this structure as a parameter.
     */
    UINT        cbSize;
    /**
     * Flag values that describe characteristics of the rebar control. Currently, rebar controls support
     * only one value. Value Description RBIM_IMAGELIST The himl member is valid or must be filled.
     */
    UINT        fMask;
#ifndef NOIMAGEAPIS
    /**
     * Handle to an image list. The rebar control will use the specified image list to obtain images.
     */
    HIMAGELIST  himl;
#else
    HANDLE      himl;
#endif
}   REBARINFO, FAR *LPREBARINFO;

#define RBBS_BREAK          0x00000001  // break to new line
#define RBBS_FIXEDSIZE      0x00000002  // band can't be sized
#define RBBS_CHILDEDGE      0x00000004  // edge around top & bottom of child window
#define RBBS_HIDDEN         0x00000008  // don't show
#define RBBS_NOVERT         0x00000010  // don't show when vertical
#define RBBS_FIXEDBMP       0x00000020  // bitmap doesn't move during band resize
#if (_WIN32_IE >= 0x0400)
#define RBBS_VARIABLEHEIGHT 0x00000040  // allow autosizing of this child vertically
#define RBBS_GRIPPERALWAYS  0x00000080  // always show the gripper
#ifdef UNDER_CE
#define RBBS_NOGRIPPER      0x00000100  // never show gripper for this band
#endif // UNDER_CE
#endif

#define RBBIM_STYLE         0x00000001
#define RBBIM_COLORS        0x00000002
#define RBBIM_TEXT          0x00000004
#define RBBIM_IMAGE         0x00000008
#define RBBIM_CHILD         0x00000010
#define RBBIM_CHILDSIZE     0x00000020
#define RBBIM_SIZE          0x00000040
#define RBBIM_BACKGROUND    0x00000080
#define RBBIM_ID            0x00000100
#if (_WIN32_IE >= 0x0400)
#define RBBIM_IDEALSIZE     0x00000200
#define RBBIM_LPARAM        0x00000400
#endif

/**
 * This structure contains information that defines a band in a rebar control.
 *
 * The cxMinChild, cyMinChild, and cx members provide information on dimensions relative to the
 * orientation of the control. That is, for a horizontal rebar control, cxMinChild and cx are
 * horizontal measurements and cyMinChild is a vertical measurement. However, if the control uses
 * the CCS_VERT style, cxMinChild and cx are vertical measurements and cyMinChild is a horizontal
 * measurement.
 */
typedef struct tagREBARBANDINFOA
{
    /**
     * Size of this structure, in bytes. The application must fill this member before sending any
     * messages that use the address of this structure as a parameter.
     */
    UINT        cbSize;
    /**
     * Flags that indicate which members of this structure are valid or must be filled. It can be a
     * combination of the following values: Value Description RBBIM_BACKGROUND The hbmBack member is
     * valid or must be filled. RBBIM_CHILD The hwndChild member is valid or must be filled.
     * RBBIM_CHILDSIZE The cxMinChild and cyMinChild members are valid or must be filled. RBBIM_COLORS
     * The clrFore and clrBack members are valid or must be filled. RBBIM_IDEALSIZE The cxIdeal member
     * is valid or must be filled. RBBIM_ID The wID member is valid or must be filled. RBBIM_IMAGE The
     * iImage member is valid or must be filled. RBBIM_LPARAM The lParam member is valid or must be
     * filled. RBBIM_SIZE The cx member is valid or must be filled. RBBIM_STYLE The fStyle member is
     * valid or must be filled. RBBIM_TEXT The lpText member is valid or must be filled.
     */
    UINT        fMask;
    /**
     * Flags that specify the band style. It can be a combination of the following values: Value
     * Description RBBS_BREAK The band is on a new line. RBBS_CHILDEDGE The band has an edge at the top
     * and bottom of the child window. RBBS_FIXEDBMP The background bitmap does not move when the band
     * is resized. RBBS_FIXEDSIZE The band cannot be sized. With this style, the sizing grip is not
     * displayed on the band. RBBS_GRIPPERALWAYS The band will always have sizing grip, even if it is
     * the only band in the rebar. RBBS_HIDDEN The band will not be visible. RBBS_NOVERT The band is not
     * displayed when the rebar control uses the CCS_VERT style. RBBS_VARIABLEHEIGHT The band can be
     * resized by the rebar control. cyIntegral and cyMaxChild affect how the rebar will resize the
     * band.
     */
    UINT        fStyle;
    COLORREF    clrFore;
    COLORREF    clrBack;
    /**
     * Long pointer to a buffer that contains the display text for the band. If band information is
     * being requested from the control and RBBIM_TEXT is specified in fMask, this member must be
     * initialized to the address of the buffer that will receive the text.
     */
    LPSTR       lpText;
    /**
     * Size of the buffer at lpText, in bytes. If information is not being requested from the control,
     * this member is ignored.
     */
    UINT        cch;
    /**
     * Zero-based index of any image that should be displayed in the band, if any. The image list is set
     * using the RB_SETBARINFO message.
     */
    int         iImage;
    /**
     * Handle to the child window contained in the band, if any.
     */
    HWND        hwndChild;
    /**
     * Minimum length of the child window, in pixels. The band cannot be sized smaller than this value.
     */
    UINT        cxMinChild;
    /**
     * Minimum thickness of the child window, in pixels. The band cannot be sized smaller than this
     * value.
     */
    UINT        cyMinChild;
    /**
     * Length of the band, in pixels.
     */
    UINT        cx;
    /**
     * Handle to a bitmap that is used as the background for this band.
     */
    HBITMAP     hbmBack;
    /**
     * Unsigned integer that the control uses to identify this band for Custom Draw notification
     * messages. This value may be used for additional purposes in the future.
     */
    UINT        wID;
#if (_WIN32_IE >= 0x0400)
    /**
     * Initial height of the band, in pixels. This member is ignored unless the RBBS_VARIABLEHEIGHT
     * style is specified.
     */
    UINT        cyChild;
    /**
     * Maximum height of the band, in pixels. This member is ignored unless the RBBS_VARIABLEHEIGHT
     * style is specified.
     */
    UINT        cyMaxChild;
    /**
     * Specifies the step value by which the band can grow or shrink, in pixels. If the band is resized,
     * it will be resized in steps specified by this value. This member is ignored unless the
     * RBBS_VARIABLEHEIGHT style is specified.
     */
    UINT        cyIntegral;
    /**
     * Specifies the ideal width of the band, in pixels. If the band is maximized to the ideal width
     * (see RB_MAXIMIZEBAND), the rebar control will attempt to make the band this width.
     */
    UINT        cxIdeal;
    /**
     * Specifies a 32-bit application-defined value.
     */
    LPARAM      lParam;
#endif
}   REBARBANDINFOA, FAR *LPREBARBANDINFOA;
typedef REBARBANDINFOA CONST FAR *LPCREBARBANDINFOA;

/**
 * This structure contains information that defines a band in a rebar control.
 *
 * The cxMinChild, cyMinChild, and cx members provide information on dimensions relative to the
 * orientation of the control. That is, for a horizontal rebar control, cxMinChild and cx are
 * horizontal measurements and cyMinChild is a vertical measurement. However, if the control uses
 * the CCS_VERT style, cxMinChild and cx are vertical measurements and cyMinChild is a horizontal
 * measurement.
 */
typedef struct tagREBARBANDINFOW
{
    /**
     * Size of this structure, in bytes. The application must fill this member before sending any
     * messages that use the address of this structure as a parameter.
     */
    UINT        cbSize;
    /**
     * Flags that indicate which members of this structure are valid or must be filled. It can be a
     * combination of the following values: Value Description RBBIM_BACKGROUND The hbmBack member is
     * valid or must be filled. RBBIM_CHILD The hwndChild member is valid or must be filled.
     * RBBIM_CHILDSIZE The cxMinChild and cyMinChild members are valid or must be filled. RBBIM_COLORS
     * The clrFore and clrBack members are valid or must be filled. RBBIM_IDEALSIZE The cxIdeal member
     * is valid or must be filled. RBBIM_ID The wID member is valid or must be filled. RBBIM_IMAGE The
     * iImage member is valid or must be filled. RBBIM_LPARAM The lParam member is valid or must be
     * filled. RBBIM_SIZE The cx member is valid or must be filled. RBBIM_STYLE The fStyle member is
     * valid or must be filled. RBBIM_TEXT The lpText member is valid or must be filled.
     */
    UINT        fMask;
    /**
     * Flags that specify the band style. It can be a combination of the following values: Value
     * Description RBBS_BREAK The band is on a new line. RBBS_CHILDEDGE The band has an edge at the top
     * and bottom of the child window. RBBS_FIXEDBMP The background bitmap does not move when the band
     * is resized. RBBS_FIXEDSIZE The band cannot be sized. With this style, the sizing grip is not
     * displayed on the band. RBBS_GRIPPERALWAYS The band will always have sizing grip, even if it is
     * the only band in the rebar. RBBS_HIDDEN The band will not be visible. RBBS_NOVERT The band is not
     * displayed when the rebar control uses the CCS_VERT style. RBBS_VARIABLEHEIGHT The band can be
     * resized by the rebar control. cyIntegral and cyMaxChild affect how the rebar will resize the
     * band.
     */
    UINT        fStyle;
    COLORREF    clrFore;
    COLORREF    clrBack;
    /**
     * Long pointer to a buffer that contains the display text for the band. If band information is
     * being requested from the control and RBBIM_TEXT is specified in fMask, this member must be
     * initialized to the address of the buffer that will receive the text.
     */
    LPWSTR      lpText;
    /**
     * Size of the buffer at lpText, in bytes. If information is not being requested from the control,
     * this member is ignored.
     */
    UINT        cch;
    /**
     * Zero-based index of any image that should be displayed in the band, if any. The image list is set
     * using the RB_SETBARINFO message.
     */
    int         iImage;
    /**
     * Handle to the child window contained in the band, if any.
     */
    HWND        hwndChild;
    /**
     * Minimum length of the child window, in pixels. The band cannot be sized smaller than this value.
     */
    UINT        cxMinChild;
    /**
     * Minimum thickness of the child window, in pixels. The band cannot be sized smaller than this
     * value.
     */
    UINT        cyMinChild;
    /**
     * Length of the band, in pixels.
     */
    UINT        cx;
    /**
     * Handle to a bitmap that is used as the background for this band.
     */
    HBITMAP     hbmBack;
    /**
     * Unsigned integer that the control uses to identify this band for Custom Draw notification
     * messages. This value may be used for additional purposes in the future.
     */
    UINT        wID;
#if (_WIN32_IE >= 0x0400)
    /**
     * Initial height of the band, in pixels. This member is ignored unless the RBBS_VARIABLEHEIGHT
     * style is specified.
     */
    UINT        cyChild;
    /**
     * Maximum height of the band, in pixels. This member is ignored unless the RBBS_VARIABLEHEIGHT
     * style is specified.
     */
    UINT        cyMaxChild;
    /**
     * Specifies the step value by which the band can grow or shrink, in pixels. If the band is resized,
     * it will be resized in steps specified by this value. This member is ignored unless the
     * RBBS_VARIABLEHEIGHT style is specified.
     */
    UINT        cyIntegral;
    /**
     * Specifies the ideal width of the band, in pixels. If the band is maximized to the ideal width
     * (see RB_MAXIMIZEBAND), the rebar control will attempt to make the band this width.
     */
    UINT        cxIdeal;
    /**
     * Specifies a 32-bit application-defined value.
     */
    LPARAM      lParam;
#endif
}   REBARBANDINFOW, FAR *LPREBARBANDINFOW;
typedef REBARBANDINFOW CONST FAR *LPCREBARBANDINFOW;

#ifdef UNICODE
#define REBARBANDINFO       REBARBANDINFOW
#define LPREBARBANDINFO     LPREBARBANDINFOW
#define LPCREBARBANDINFO    LPCREBARBANDINFOW
#else
#define REBARBANDINFO       REBARBANDINFOA
#define LPREBARBANDINFO     LPREBARBANDINFOA
#define LPCREBARBANDINFO    LPCREBARBANDINFOA
#endif

#define RB_INSERTBANDA  (WM_USER +  1)
/**
 * This message deletes a band from a rebar control.
 *
 * @param uBand Zero-based index of the band to be deleted.
 *
 * @return Nonzero indicates success. Zero indicates otherwise.
 */
#define RB_DELETEBAND   (WM_USER +  2)
/**
 * This message retrieves information about the rebar control and the image list it uses.
 *
 * @param lprbi Long pointer to a REBARINFO structure that receives the rebar control information.
 *   Set the cbSize member of this structure to sizeof(REBARINFO) before sending this message.
 *
 * @return Nonzero indicates success. Zero indicates otherwise.
 */
#define RB_GETBARINFO   (WM_USER +  3)
/**
 * This message sets the characteristics of a rebar control.
 *
 * @param lprbi Long pointer to a REBARINFO structure that contains the information to be set. Set
 *   the cbSize member of this structure to sizeof(REBARINFO) before sending this message.
 *
 * @return Nonzero indicates success. Zero indicates otherwise.
 *
 * When the fMask member of the REBARINFO structure specifies an invalid value, this message returns
 * TRUE when it should return FALSE.
 */
#define RB_SETBARINFO   (WM_USER +  4)
#if (_WIN32_IE < 0x0400)
/**
 * This message retrieves information about a specified band in a rebar control.
 *
 * @param uBand Zero-based index of the band for which the information is retrieved.
 * @param lprbbi Long pointer to a REBARBANDINFO structure that receives the requested band
 *   information. Set the cbSize member of this structure to sizeof(REBARBANDINFO) and set the fMask
 *   parameter to the items you want to retrieve before sending this message.
 *
 * @return Nonzero indicates success. Zero indicates otherwise.
 */
#define RB_GETBANDINFO  (WM_USER +  5)
#endif
#define RB_SETBANDINFOA (WM_USER +  6)
/**
 * This message sets a rebar control's parent window.
 *
 * @param hwndParent Handle to the parent window to be set.
 *
 * @return Returns the handle to the previous parent window, or NULL if there is no previous parent.
 *
 * The rebar control sends notification messages to the window you specify with this message. This
 * message does not change the actual parent that was set when the control was created.
 */
#define RB_SETPARENT    (WM_USER +  7)
#if (_WIN32_IE >= 0x0400)
/**
 * This message determines which portion of a rebar band is at a specified point on the screen, if a
 * rebar band exists at that point.
 *
 * @param lprbht Long pointer to an RBHITTESTINFO structure. Before sending the message, the pt
 *   member of this structure must be initialized to the point that is hit tested, in client
 *   coordinates.
 *
 * @return Returns the zero-based index of the band at the specified point, or -1 if no rebar band
 *   was at the point.
 */
#define RB_HITTEST      (WM_USER +  8)
/**
 * This message retrieves the bounding rectangle for a specified band in a rebar control.
 *
 * @param iBand Zero-based index of a band in the rebar control.
 * @param lprc Long pointer to a RECT structure that receives the bounds of the rebar band.
 *
 * @return Nonzero indicates success. Zero indicates otherwise.
 */
#define RB_GETRECT      (WM_USER +  9)
#endif
#define RB_INSERTBANDW  (WM_USER +  10)
#define RB_SETBANDINFOW (WM_USER +  11)
/**
 * This message retrieves the count of bands currently in the rebar control.
 *
 * @return Returns a UINT value that represents the number of bands assigned to the control.
 */
#define RB_GETBANDCOUNT (WM_USER +  12)
/**
 * This message retrieves the number of band rows in a rebar control.
 *
 * @return Returns a UINT value that represents the number of band rows in the control.
 */
#define RB_GETROWCOUNT  (WM_USER +  13)
/**
 * This message retrieves the height of a specified row in a rebar control.
 *
 * @param uRow Zero-based index of a band. The height of the row that contains the specified band
 *   will be retrieved.
 *
 * @return Returns a UINT value that represents the row height, in pixels.
 *
 * To retrieve the number of rows in a rebar control, use the RB_GETROWCOUNT message.
 */
#define RB_GETROWHEIGHT (WM_USER +  14)
#if (_WIN32_IE >= 0x0400)
/**
 * This message converts a band identifier to a band index in a rebar control.
 *
 * @param uBandID Application-defined identifier of the band in question. This is the value that is
 *   passed in the wID member of the REBARBANDINFO structure when the band was inserted.
 *
 * @return Returns the zero-based band index if successful, or -1 otherwise. If duplicate band IDs
 *   exist, the first one is returned.
 */
#define RB_IDTOINDEX    (WM_USER +  16) // wParam == id
/**
 * This message sets a rebar control's default background color.
 *
 * @param clrBk COLORREF value that represents the new default background color.
 *
 * @return Returns a COLORREF value that represents the previous default background color.
 *
 * The rebar control's default background color is used to draw the background in a rebar control
 * and all bands that are added after this message has been sent. The default background color for a
 * particular band can be overridden by setting the RBBIM_COLORS flag in fMask and setting clrBack
 * in the REBARBANDINFO structure when a band is added or modified.
 */
#define RB_SETBKCOLOR   (WM_USER +  19) // sets the default BK color
/**
 * This message retrieves a rebar control's default background color.
 *
 * @return Returns a COLORREF value that represent the current default background color.
 */
#define RB_GETBKCOLOR   (WM_USER +  20) // defaults to CLR_NONE
/**
 * This message sets a rebar control's default text color.
 *
 * @param clrText COLORREF value that represents the new default text color.
 *
 * @return Returns a COLORREF value that represents the previous default text color.
 *
 * The rebar control's default text color is used to draw the text in a rebar control and all bands
 * that are added after this message has been sent. The default text color for a particular band can
 * be overridden by setting the RBBIM_COLORS flag in fMask and setting clrFore in the REBARBANDINFO
 * structure when a band is added or modified.
 */
#define RB_SETTEXTCOLOR (WM_USER +  21)
/**
 * This message retrieves a rebar control's default text color.
 *
 * @return Returns a COLORREF value that represent the current default text color.
 */
#define RB_GETTEXTCOLOR (WM_USER +  22) // defaults to 0x00000000
/**
 * This message tries to fit a rebar control to a specified rectangle.
 *
 * @param prc Pointer to a RECT structure that specifies the rectangle that the rebar control should
 *   be sized to.
 *
 * @return Returns nonzero if a layout change occurred, or zero otherwise.
 *
 * The rebar bands will be wrapped as necessary to fit the rectangle. Bands that have the
 * RBBS_VARIABLEHEIGHT style will be resized as evenly as possible to fit the rectangle.
 */
#define RB_SIZETORECT   (WM_USER +  23) // resize the rebar/break bands and such to this rect (lparam)
#endif      // _WIN32_IE >= 0x0400

#ifdef UNICODE
/**
 * This message inserts a new band in a rebar control.
 *
 * @param uIndex Zero-based index of the location where the band will be inserted. If you set this
 *   parameter to -1, the control will add the new band at the last location.
 * @param lprbbi Long pointer to a REBARBANDINFO structure that defines the band to be inserted. Set
 *   the cbSize member of this structure to sizeof(REBARBANDINFO) before sending this message.
 *
 * @return Nonzero indicates success. Zero indicates otherwise.
 */
#define RB_INSERTBAND   RB_INSERTBANDW
/**
 * This message sets characteristics of an existing band in a rebar control.
 *
 * @param uBand Zero-based index of the band to receive the new settings.
 * @param lprbbi Long pointer to a REBARBANDINFO structure that contains the new settings. Set the
 *   cbSize member of this structure to sizeof(REBARBANDINFO) before sending this message.
 *
 * @return Nonzero indicates success. Zero indicates otherwise.
 */
#define RB_SETBANDINFO   RB_SETBANDINFOW
#else
/**
 * This message inserts a new band in a rebar control.
 *
 * @param uIndex Zero-based index of the location where the band will be inserted. If you set this
 *   parameter to -1, the control will add the new band at the last location.
 * @param lprbbi Long pointer to a REBARBANDINFO structure that defines the band to be inserted. Set
 *   the cbSize member of this structure to sizeof(REBARBANDINFO) before sending this message.
 *
 * @return Nonzero indicates success. Zero indicates otherwise.
 */
#define RB_INSERTBAND   RB_INSERTBANDA
/**
 * This message sets characteristics of an existing band in a rebar control.
 *
 * @param uBand Zero-based index of the band to receive the new settings.
 * @param lprbbi Long pointer to a REBARBANDINFO structure that contains the new settings. Set the
 *   cbSize member of this structure to sizeof(REBARBANDINFO) before sending this message.
 *
 * @return Nonzero indicates success. Zero indicates otherwise.
 */
#define RB_SETBANDINFO   RB_SETBANDINFOA
#endif

#if (_WIN32_IE >= 0x0400)
// for manual drag control
// lparam == cursor pos
        // -1 means do it yourself.
        // -2 means use what you had saved before
#define RB_BEGINDRAG    (WM_USER + 24)
#define RB_ENDDRAG      (WM_USER + 25)
#define RB_DRAGMOVE     (WM_USER + 26)
/**
 * This message retrieves the height the rebar control.
 *
 * @return Returns a UINT value that represents the height, in pixels, of the control.
 */
#define RB_GETBARHEIGHT (WM_USER + 27)
#define RB_GETBANDINFOW (WM_USER + 28)
#define RB_GETBANDINFOA (WM_USER + 29)

#ifdef UNICODE
/**
 * This message retrieves information about a specified band in a rebar control.
 *
 * @param uBand Zero-based index of the band for which the information is retrieved.
 * @param lprbbi Long pointer to a REBARBANDINFO structure that receives the requested band
 *   information. Set the cbSize member of this structure to sizeof(REBARBANDINFO) and set the fMask
 *   parameter to the items you want to retrieve before sending this message.
 *
 * @return Nonzero indicates success. Zero indicates otherwise.
 */
#define RB_GETBANDINFO   RB_GETBANDINFOW
#else
/**
 * This message retrieves information about a specified band in a rebar control.
 *
 * @param uBand Zero-based index of the band for which the information is retrieved.
 * @param lprbbi Long pointer to a REBARBANDINFO structure that receives the requested band
 *   information. Set the cbSize member of this structure to sizeof(REBARBANDINFO) and set the fMask
 *   parameter to the items you want to retrieve before sending this message.
 *
 * @return Nonzero indicates success. Zero indicates otherwise.
 */
#define RB_GETBANDINFO   RB_GETBANDINFOA
#endif

/**
 * This message resizes a band in a rebar control to its smallest size.
 *
 * @param uBand Zero-based index of the band to be minimized.
 *
 * @return The return value is not used.
 */
#define RB_MINIMIZEBAND (WM_USER + 30)
/**
 * This message resizes a band in a rebar control to its ideal or largest size.
 *
 * @param uBand Zero-based index of the band to be maximized.
 * @param fIdeal Boolean that specifies whether the ideal width of the band should be used when the
 *   band is maximized. If this value is nonzero, the ideal width is used. If this value is zero, the
 *   band is made as large as possible.
 *
 * @return The return value is not used.
 */
#define RB_MAXIMIZEBAND (WM_USER + 31)

/**
 * This message retrieves the borders of a band. The result of this message can be used to calculate
 * the usable area in a band.
 *
 * @param uBand Zero-based index of the band for which the borders will be retrieved.
 * @param lprc Long pointer to a RECT structure that receives the band borders. If the rebar control
 *   has the RBS_BANDBORDERS style, each member of this structure will receive the number of pixels on
 *   the corresponding side of the band that are used by the band. If the rebar control does not have
 *   the RBS_BANDBORDERS style, only the left member of this structure receives valid information.
 *
 * @return The return value is not used.
 */
#define RB_GETBANDBORDERS (WM_USER + 34)  // returns in lparam = lprc the amount of edges added to band wparam

/**
 * This message shows or hides a specified band in a rebar control.
 *
 * @param iBand Zero-based index of a band in the rebar control.
 * @param fShow Boolean that indicates if the band should be shown or hidden. If this value is
 *   nonzero, the band is shown. Otherwise, the band is hidden.
 *
 * @return Nonzero indicates success. Zero indicates otherwise.
 */
#define RB_SHOWBAND     (WM_USER + 35)      // show/hide band

#endif      // _WIN32_IE >= 0x0400

/**
 * This notification message is sent by a rebar control when its height has changed. It is sent in
 * the form of a WM_NOTIFY message.
 *
 * @param lpnmhdr Long pointer to an NMHDR structure that contains additional information about this
 *   notification message.
 *
 * @return The return value for this notification is not used.
 *
 * Rebar controls that use the CCS_VERT style send this notification message when their width
 * changes.
 */
#define RBN_HEIGHTCHANGE    (RBN_FIRST - 0)

#if (_WIN32_IE >= 0x0400)
/**
 * This notification message is sent by a rebar control when you change the layout of the control's
 * bands. It is sent in the form of a WM_NOTIFY message.
 *
 * @param lpnmhdr Long pointer to an NMHDR structure that contains additional information about this
 *   notification message.
 *
 * @return The return value for this notification is not used.
 */
#define RBN_LAYOUTCHANGED   (RBN_FIRST - 2)
/**
 * This message is sent to the parent by a rebar control created with the RBS_AUTOSIZE style when
 * the rebar automatically resizes itself. It is sent in the form of a WM_NOTIFY message.
 *
 * @param lpnmas Long pointer to a NMRBAUTOSIZE structure that contains information about the resize
 *   operation.
 *
 * @return The return value for this notification is not used.
 */
#define RBN_AUTOSIZE        (RBN_FIRST - 3)
/**
 * This message is sent by a rebar control when the user begins dragging a band. It is sent in the
 * form of a WM_NOTIFY message.
 *
 * @param lpnmrb Long pointer to a NMREBAR structure that contains information about the
 *   notification.
 *
 * @return Return zero to allow the rebar to continue the drag operation or nonzero to abort the
 *   drag operation.
 */
#define RBN_BEGINDRAG       (RBN_FIRST - 4)
/**
 * This message is sent by a rebar control when the user stops dragging a band. It is sent in the
 * form of a WM_NOTIFY message.
 *
 * @param lpnmrb Long pointer to a NMREBAR structure that contains information about the
 *   notification.
 *
 * @return The return value for this notification is not used.
 */
#define RBN_ENDDRAG         (RBN_FIRST - 5)


typedef struct tagNMREBAR
{
        NMHDR hdr;
        UINT uBand;
        UINT wID;
        UINT cyChild;
        UINT cyBand;
} NMREBAR, *LPNMREBAR;

typedef struct tagNMRBAUTOSIZE
{
        NMHDR hdr;
        BOOL fChanged;
        RECT rcTarget;
        RECT rcActual;
} NMRBAUTOSIZE, *LPNMRBAUTOSIZE;

#define RBHT_NOWHERE    0x0001
#define RBHT_CAPTION    0x0002
#define RBHT_CLIENT     0x0003
#define RBHT_GRABBER    0x0004

/**
 * This structure contains information specific to a hit test operation. This structure is used with
 * the RB_HITTEST message.
 */
typedef struct _RB_HITTESTINFO
{
    /**
     * POINT structure that describes the point to be hit tested, in client coordinates.
     */
    POINT pt;
    /**
     * Receives a flag value indicating the rebar band's component located at the point described by pt.
     * It is one of the following values: Value Description RBHT_CAPTION The point was in the rebar
     * band's caption. RBHT_CLIENT The point was in the rebar band's client area. RBHT_GRABBER The point
     * was in the rebar band's grabber. RBHT_NOWHERE The point was not in a rebar band.
     */
    UINT flags;
    /**
     * Receives the rebar band's index at the point described by pt. This value is the zero-based index
     * of the band or -1 if no band was at the hit-tested point.
     */
    int iBand;
} RBHITTESTINFO, FAR *LPRBHITTESTINFO;

#endif      // _WIN32_IE >= 0x0400

#endif      // NOREBAR

#endif      // _WIN32_IE >= 0x0300

//====== COMMANDBAR CONTROL =================================================

#ifdef UNDER_CE
#ifndef NOCOMMANDBAR

// Command Bar API's

/**
 * This structure contains information necessary to restore a band to its current state.
 */
typedef struct tagCOMMANDBANDSRESTOREINFO
{
    UINT        cbSize;
    /**
     * Identifier of the band. This member corresponds to the wID member of the REBARBANDINFO structure,
     * and is filled in by the CommandBands_GetRestoreInformation function.
     */
    UINT        wID;
    /**
     * Flags that specify the band style. This member corresponds to the fStyle member of the
     * REBARBANDINFO structure, and is filled in by the CommandBands_GetRestoreInformation function. It
     * can be a combination of the following values: Value Description RBBS_BREAK The band is on a new
     * line. RBBS_CHILDEDGE The band has an edge at the top and bottom of the child window.
     * RBBS_FIXEDBMP The background bitmap does not move when the band is resized. RBBS_FIXEDSIZE The
     * band cannot be sized. With this style, the sizing grip is not displayed on the band.
     * RBBS_GRIPPERALWAYS The band will always have sizing grip, even if it is the only band in the
     * rebar. RBBS_HIDDEN The band will not be visible. RBBS_NOVERT The band is not displayed when the
     * rebar control uses the CCS_VERT style. RBBS_VARIABLEHEIGHT The band can be resized by the rebar
     * control. The cyIntegral and cyMaxChild members affect how the rebar will resize the band.
     */
    UINT        fStyle;
    /**
     * Restored width of the band, in pixels. The restored width is the width of the band after the user
     * has dragged it. If the user has never dragged it, it is the initial size of the band. This member
     * corresponds to the cx member of the REBARBANDINFO structure, and is filled in by the
     * CommandBands_GetRestoreInformation function.
     */
    UINT        cxRestored;
    /**
     * Indicates whether the band is maximized. Only one band in a row can be maximized at a time. This
     * member corresponds to the fStyle member of the REBARBANDINFO structure, and is filled in by the
     * CommandBands_GetRestoreInformation function.
     */
    BOOL        fMaximized;
} COMMANDBANDSRESTOREINFO, *LPCOMMANDBANDSRESTOREINFO;
typedef COMMANDBANDSRESTOREINFO CONST *LPCCOMMANDBANDSRESTOREINFO;
	
/**
 * This function instantiates a new command bar.
 *
 * @param hInst Handle to the application instance in which to create the command bar.
 * @param hwndParent Handle to the parent window for the command bar.
 * @param idCmdBar Identifier of the command bar.
 *
 * @return The window handle to the command bar indicates success. NULL indicates failure.
 *
 * The CommandBar_Create function creates an empty command bar.
 */
WINCOMMCTRLAPI HWND  WINAPI CommandBar_Create(HINSTANCE hInst, HWND hwndParent, int idCmdBar);
/**
 * This function shows or hides the command bar.
 *
 * @param hwndCB Handle to the command bar's window. This handle is returned by the
 *   CommandBar_Create function when the command bar is created.
 * @param fShow Boolean that specifies whether to show or hide the command bar. Set this parameter
 *   to TRUE to show the command bar, or FALSE to hide it.
 *
 * @return The previous show state of the command bar. This function returns TRUE if command bar was
 *   displayed, FALSE if it was hidden.
 *
 * Command bars are created with the show state set to TRUE. To hide the command bar before the
 * window is displayed call CommandBar_Show, with the fShow parameter set to false, before calling
 * ShowWindow for the parent window.
 */
WINCOMMCTRLAPI BOOL  WINAPI CommandBar_Show(HWND hwndCB, BOOL fShow);
/**
 * This function adds one or more images to the list of button images available for use in the
 * command bar.
 *
 * @param hwndCB Handle to the command bar's window. This handle is returned by the
 *   CommandBar_Create function when the command bar is created.
 * @param hInst Handle to an instance of the executable module that contains the bitmap resource.
 * @param idBitmap Identifier of the bitmap resource that contains the button images. If you specify
 *   HINST_COMMCTRL in the hInst parameter, you can use system-defined button bitmaps by specifying
 *   one of the following values. Value Description IDB_STD_SMALL_COLOR Adds small, color standard
 *   bitmaps. IDB_VIEW_SMALL_COLOR Adds small, color view bitmaps.
 * @param iNumImages Integer that contains the number of button images in the bitmap. This can be
 *   zero if the bitmap being added is one of the system defined bitmaps-standard or view.
 *
 * @return The index of the first new image indicates success. A value of -1 indicates failure.
 *
 * Each button image should be 16x16 pixels in size.
 *
 * The following values can be used as indexes to the standard and view bitmaps:
 *
 * STD_COPY STD_PROPERTIES STD_CUT STD_REDOW STD_DELETE STD_REPLACE STD_FIND STD_PASTE STD_FILENEW
 * STD_PRINT STD_FILEOPEN STD_PRINTPRE STD_FILESAVE STD_UNDO STD_HELP VIEW_DETAILS VIEW_SORTDATE
 * VIEW_LARGEICONS VIEW_SORTNAME VIEW_LIST VIEW_SORTSIZE VIEW_SMALLICONS VIEW_SORTTYPE
 *
 * Windows CE version 1.0 only supports 2 bits per pixel (2bp) gray scale, so the bitmaps is not
 * displayed in color.
 */
WINCOMMCTRLAPI int   WINAPI CommandBar_AddBitmap(HWND hwndCB, HINSTANCE hInst, int idBitmap,
								  int iNumImages, int iImageWidth,
								  int iImageHeight);
/**
 * This function inserts a combo box into the command bar.
 *
 * @param hwndCB Handle to the command bar's window. This handle is returned by the
 *   CommandBar_Create function when the command bar is created.
 * @param hInst Handle to the application instance.
 * @param iWidth Integer that contains the width, in pixels, of the combo box.
 * @param dwStyle Specifies the window styles to apply to the combo box. The WS_VISIBLE and WS_CHILD
 *   styles are applied automatically. For descriptions of other styles you can apply, see Window and
 *   Message Box Styles.
 * @param idComboBox Identifier of the combo box to insert.
 * @param iButton Zero-based index of a button in the command bar. CommandBar_InsertComboBox inserts
 *   the combo box to the left of this button.
 *
 * @return The window handle to the combo box indicates success. NULL indicates failure.
 */
WINCOMMCTRLAPI HWND  WINAPI CommandBar_InsertComboBox(HWND hwndCB, HINSTANCE hInstance,
									   int  iWidth, UINT dwStyle,
									   WORD idComboBox, WORD iButton);
/**
 * This function inserts a menu bar into the command bar.
 *
 * @param hwndCB Handle to the command bar's window. This handle is returned by the
 *   CommandBar_Create function when the command bar is created.
 * @param hInst Handle to the application instance.
 * @param idMenu Resource identifier of the menu bar to insert in the command bar.
 * @param iButton Zero-based index of a button. CommandBar_InsertMenubar inserts the menu bar to the
 *   left of this button.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * Use the same type of menu bar in the command bar of a Windows CE application that you use for the
 * main menu in an application running on a Windows desktop platform.
 */
WINCOMMCTRLAPI BOOL  WINAPI CommandBar_InsertMenubar(HWND hwndCB, HINSTANCE hInst,
									  WORD idMenu, WORD iButton);
/**
 * This function inserts a menu into a command bar. The menu can be specified as a resource name,
 * using MAKEINTRESORUCE, or as a menu handle.
 *
 * @param hwndCB Handle to the command bar's window. This handle is returned by the
 *   CommandBar_Create function when the command bar is created.
 * @param hInst Handle to the application instance. This parameter must be NULL if pszMenu contains
 *   a menu handle. If pszMenu contains a resource name, hinst must contain the instance handle.
 * @param pszMenu Pointer to the null-terminated string that contains the name of a menu resource or
 *   menu handle.
 * @param iButton Zero-based index of a button. CommandBar_InsertMenubarEx inserts the menu bar to
 *   the left of this button.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * Use the same type of menu bar in the command bar of a Windows CE application that you use for the
 * main menu in an application running on a Windows desktop platform.
 */
WINCOMMCTRLAPI BOOL WINAPI CommandBar_InsertMenubarEx(HWND hwndCB,
						               HINSTANCE hinst,
						               LPTSTR pszMenu,
						               WORD iButton);
/**
 * This function repositions and redraws the command bar after a menu in the command bar has been
 * modified.
 *
 * @param hwndCB Handle to the command bar's window. This handle is returned by the
 *   CommandBar_Create function when the command bar is created.
 * @param iButton Zero-based index of the menu bar within the command bar.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * You must always call CommandBar_DrawMenuBar after you modify a menu in a command bar. Do not call
 * DrawMenuBar.
 *
 * An application should not use 0xFFFFFFFF as the command identifier of a button or separator in
 * the command bar. This identifier is reserved for the command bar's use.
 */
WINCOMMCTRLAPI BOOL WINAPI CommandBar_DrawMenuBar(HWND hwndCB,
					                              WORD iButton);
/**
 * This function retrieves the handle to a menu on the command bar.
 *
 * @param hwndCB Handle to the command bar's window. This handle is returned by the
 *   CommandBar_Create function when the command bar is created.
 * @param iButton Zero-based index of the command bar separator button that holds the menu.
 *
 * @return The handle to the menu identified by the index in the iButton parameter indicates
 *   success. NULL indicates failure.
 *
 * If the separator button identified by the iButton parameter does not contain a menu bar, the
 * CommandBar_GetMenu function will fail.
 */
WINCOMMCTRLAPI HMENU WINAPI CommandBar_GetMenu(HWND hwndCB, WORD iButton);
/**
 * This function adds the Close button (X) to the command bar. You can also use it to add the Help
 * button (?) and the OK button.
 *
 * @param hwndCB Handle to the command bar's window. This handle is returned when the command bar is
 *   created by the CommandBar_Create function.
 * @param dwFlags Specifies the optional buttons to be added to the command bar. This parameter can
 *   be a combination of the following values, or zero if neither of the optional buttons are needed.
 *   Value Description Message CMDBAR_HELP Help button WM_HELP CMDBAR_OK OK button WM_COMMAND (with
 *   IDOK as the message identifier)
 * @param dwReserved Reserved; set to zero.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * When a user selects the Close, OK, or Help button, the message associated with that button is
 * placed in the application's message queue.
 *
 * Do not call the CommandBar_AddAdornments member function until after you have added all the other
 * elements (menus, buttons, combo boxes) to the command bar.
 */
WINCOMMCTRLAPI BOOL  WINAPI CommandBar_AddAdornments(HWND hwndCB,
													 DWORD dwFlags,
													 DWORD dwReserved);
/**
 * This function retrieves the height of the command bar in pixels.
 *
 * @param hwndCB Handle to the command bar's window. This handle is returned by the
 *   CommandBar_Create function when the command bar is created.
 *
 * @return The height, in pixels, of the of the command bar indicates success.
 *
 * Because the command bar occupies part of the client area of an application's main window, you
 * should call this function to determine the actual size of the client area.
 */
WINCOMMCTRLAPI int   WINAPI CommandBar_Height(HWND hwndCB);
WINCOMMCTRLAPI BOOL  WINAPI IsCommandBarMessage(HWND hwndCB, LPMSG lpMsg);


/**
 * This function instantiates a new command bands control.
 *
 * @param hinst Handle to the application instance in which to create the command bands control.
 * @param hwndParent Handle to the parent window for the command bands control.
 * @param wID Identifier of the command bands control. This is used in any rebar notifications that
 *   are sent to the parent window.
 * @param dwStyles Specifies the style of the command bands tool being created. This parameter can
 *   be any combination of the styles listed in Window and Message Box Styles and Control Styles.
 * @param himl Handle to the image list that contains the images to draw in each band of the
 *   control. Set this parameter to NULL if no images are to be drawn.
 *
 * @return The window handle to the command bands control indicates success. NULL indicates failure.
 */
WINCOMMCTRLAPI HWND WINAPI CommandBands_Create(HINSTANCE hinst, 
                                               HWND hwndParent, 
                                               UINT wID, 
                                               DWORD dwStyles, 
                                               HIMAGELIST himl);
/**
 * This function adds one or more bands to the command bands control.
 *
 * @param hwndCmdBands Handle to the command bands control's window. This handle is returned when
 *   the command bands control is created by the CommandBands_Create function.
 * @param hinst Handle to the application instance.
 * @param cBands Number of bands to add.
 * @param prbbi Pointer to an array of REBARBANDINFO structures that contain information about the
 *   bands to add. There must be the same number of elements in the array as specified in the cBands
 *   parameter.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * By default, each band is created with a command bar as its child window. The command bar can be
 * retrieved by using the CommandBands_GetCommandBar function. To create a different kind of child
 * control in a band, use the RBBIM_CHILD mask in the fMask field of the REBARBANDINFO structure,
 * and specify the child control's window handle in the REBARBANDINFO structure's hwndChild field.
 */
WINCOMMCTRLAPI BOOL WINAPI CommandBands_AddBands(HWND hwndCmdBands,  
                                                 HINSTANCE hinst,
                                                 UINT cBands, 
                                                 LPREBARBANDINFO prbbi);
/**
 * This function retrieves the handle to a command bar child control in a band of the command bands
 * control.
 *
 * @param hwndCmdBands Handle to the command bands control's window. This handle is returned when
 *   the command bands control is created by the CommandBands_Create function.
 * @param uBand Unsigned integer that contains the zero-based index of the band containing the
 *   command bar. If the user has had an opportunity to reposition the bands, use the RB_IDTOINDEX
 *   message to get the index of the band before passing the index to this function.
 *
 * @return The window handle to the command bar identified by the index in the wBandID parameter
 *   indicates success. NULL indicates failure.
 *
 * The index you pass in the wBandID parameter is the current position of the command bar band in
 * the command bands control. This index may have a different value than the order in which you
 * added the band to the control, because the user may have repositioned the band.
 */
WINCOMMCTRLAPI HWND WINAPI CommandBands_GetCommandBar(HWND hwndCmdBands, UINT uBand);
/**
 * This function adds the Close button (X) to the upper right corner of the command bands control.
 * You can also use it to add the Help button (?) and the OK button.
 *
 * @param hwndCmdBands Handle to the he command bands control's window. This handle is returned when
 *   the command bands control is created by the CommandBands_Create function.
 * @param hinst Handle to the application instance.
 * @param dwFlags Specifies the optional buttons to be added to the top band of the command bands
 *   control. This parameter can be a combination of the following values, or zero if neither of the
 *   optional buttons are needed. Value Description Message CMDBAR_HELP Help button WM_HELP CMDBAR_OK
 *   OK button WM_COMMAND (with IDOK as the message identifier)
 * @param prbbi Pointer to a REBARBANDINFO structure. Use this structure to customize the band that
 *   holds the adornments. This parameter can be NULL.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * By default the adornments band is created with an identifier of 0xFFFFFFFF. You can use the
 * REBARBANDINFO structure you pass in the prbbi parameter to override this identifier.
 */
WINCOMMCTRLAPI BOOL WINAPI CommandBands_AddAdornments(HWND hwndCmdBands, 
                                                      HINSTANCE hinst, 
                                                      DWORD dwFlags, 
                                                      LPREBARBANDINFO prbbi);
/**
 * This function shows or hides the command bands control.
 *
 * @param hwndCmdBands Handle to command bands control's window. This handle is returned when the
 *   command bands control is created by the CommandBands_Create function.
 * @param fShow Boolean that specifies whether to show or hide the command bands control. Set this
 *   parameter to TRUE to show the command bar, or FALSE to hide it.
 *
 * @return The previous state of the command bands control indicates success.
 */
WINCOMMCTRLAPI BOOL WINAPI CommandBands_Show(HWND hwndCmdBands, BOOL fShow);
/**
 * This function retrieves information necessary to restore a band's current state, and places it in
 * a COMMANDBANDSRESTOREINFO structure.
 *
 * @param hwndCmdBands [in] Handle to the command bands control's window. This handle is returned
 *   when the command bands control is created by the CommandBands_Create function.
 * @param uBand [in] Unsigned integer that contains the zero-based index of the band containing the
 *   command bar. Use RB_IDTOINDEX to get the index of the band before passing the index to this
 *   function.
 * @param pcbri [out] Pointer to an array of COMMANDBANDSRESTOREINFO structures that will receive
 *   information about the band's current state.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * Use CommandBands_GetRestoreInformation to save information about the bands in a command bands
 * control before you close the application window. Save the information in the registry, so the
 * bands can be restored to their current state the next time the application is opened. The next
 * time the application is opened, use the values returned in the fStyle and cxRestored fields of
 * the COMMANDBANDSRESTOREINFO structure for the fStyle and cx fields of the REBARBANDINFO structure
 * you pass to the CommandBands_AddBands function. After you've added all the bands to the control,
 * use the RB_MAXIMIZEBAND message to maximize any band whose fMaximized field in the
 * COMMANDBANDSRESTOREINFO structure is set to TRUE.
 */
WINCOMMCTRLAPI BOOL WINAPI CommandBands_GetRestoreInformation(HWND hwndCmdBands, 
                                               UINT uBand, 
                                               LPCOMMANDBANDSRESTOREINFO pcbri);

// Command Bar Helper Macros

/**
 * This macro destroys the command bar.
 *
 * @param hwndCB Handle to the command bar's window. This handle is returned by the
 *   CommandBar_Create function when the command bar is created.
 *
 * @return None.
 *
 * The CommandBar_Destroy function calls the DestroyWindow function to destroy the command bar. If
 * the command bar's parent window is being destroyed, it is not necessary to call
 * CommandBar_Destroy.
 */
#define CommandBar_Destroy(hwndCB) \
	DestroyWindow((hwndCB))

/**
 * This macro ascertains whether or not the command bar is visible.
 *
 * @param hwndCB Handle to the command bar's window. This handle is returned by the
 *   CommandBar_Create function when the command bar is created.
 *
 * @return TRUE indicates that the command bar's parent window has the WS_VISIBLE style. FALSE
 *   indicates that the command bar is hidden.
 *
 * Because this macro only determines whether the window has the WS_VISIBLE style, it may return
 * TRUE even if the window is obscured by other windows.
 */
#define CommandBar_IsVisible(hwndCB) \
    IsWindowVisible((hwndCB))	

/**
 * This macro adds one or more buttons to the command bar.
 *
 * @param hwndCB Handle to the command bar's window. This handle is returned by the
 *   CommandBar_Create function when the command bar is created.
 * @param uNumButtons Unsigned integer that contains the number of buttons to add.
 * @param lpButtons Long pointer to an array of TBBUTTON structures that contain information about
 *   the buttons to add. There must be the same number of elements in the array as specified in the
 *   uNumButtons parameter.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define CommandBar_AddButtons(hwndCB, cbButtons, lpButtons) \
	SendMessage((hwndCB), TB_ADDBUTTONS, (WPARAM)(cbButtons), \
				(LPARAM)(lpButtons))

/**
 * This macro inserts a button into the command bar.
 *
 * @param hwndCB Handle to the command bar's window. This handle is returned by the
 *   CommandBar_Create function when the command bar is created.
 * @param iButton Zero-based index of a button in the command bar. CommandBar_InsertButton inserts
 *   the new button to the left of this button.
 * @param lpButton Long pointer to a TBBUTTON structure that contains information about the button
 *   to insert.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define CommandBar_InsertButton(hwndCB, iButton, lpButton) \
    SendMessage((hwndCB), TB_INSERTBUTTON, (WPARAM)(iButton), \
	            (LPARAM)(lpButton))

/**
 * This macro adds ToolTip strings to the command bar. A ToolTip control is a small pop-up window
 * that displays a line of descriptive text giving the purpose of a button on the command bar.
 *
 * @param hwndCB Handle to the command bar's window. This handle is returned by the
 *   CommandBar_Create function when the command bar is created.
 * @param uNumToolTips Unsigned integer that contains the number of ToolTip strings in the array
 *   specified in the lpToolTips parameter.
 * @param lpToolTips Array of long pointers to strings that are displayed when the ToolTip control
 *   is active. The array must contain the same number of elements as specified in the uNumToolTips
 *   parameter.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * Only command-bar buttons can have ToolTip strings; menus and combo boxes cannot.
 *
 * CommandBar_AddtoolTips does not copy the array of ToolTip strings you pass to it. It uses the
 * memory address you pass in the lpToolTips parameter. Do not release the memory allocated for the
 * ToolTip string array until the program exits.
 */
#define CommandBar_AddToolTips(hwndCB, cbToolTips, lpToolTipsStrings) \
	SendMessage((hwndCB), TB_SETTOOLTIPS, (WPARAM)(cbToolTips), \
				(LPARAM)(lpToolTipsStrings))

/**
 * This macro retrieves the height in pixels of a command bands control.
 *
 * @param hwndCmdBand Window handle to the command bands control. This handle is returned when the
 *   command bands control is created by the CommandBands_Create function.
 *
 * @return The height, in pixels, of the command bands control.
 *
 * Because the command bar occupies part of the client area of an application's main window, you
 * should call this macro to determine the actual size of the client area.
 */
#define CommandBands_Height(hwndCmdBands)\
	((UINT) SendMessage((hwndCmdBands), RB_GETBARHEIGHT, 0, 0))

#define CommandBands_IsVisible(hwndCmdBands) \
    IsWindowVisible((hwndCmdBands))

#define CMDBAR_HELP     0x000b
#define CMDBAR_OK		0xf000

#endif // NOCOMMANDBAR
#endif // UNDER_CE

//====== STATUS BAR CONTROL ===================================================

#ifndef NOSTATUSBAR

// begin_r_commctrl

// end_r_commctrl

/**
 * This function draws the specified text in the style of a status window with borders.
 *
 * @param hdc Handle to the display context for the window.
 * @param lprc Long pointer to a RECT structure that contains the position, in client coordinates,
 *   of the rectangle in which the text is drawn. The function draws the borders just inside the edges
 *   of the specified rectangle.
 * @param pszText Pointer to a null-terminated string that specifies the text to display. Tab
 *   characters in the string determine whether the string is left-aligned, right-aligned, or
 *   centered.
 * @param uFlags Text drawing flags. This parameter can be a combination of these values: Value
 *   Description SBT_NOBORDERS Prevents borders from being drawn around the specified text. SBT_POPOUT
 *   Draws highlighted borders that make the text stand out. SBT_RTLREADING Displays text using
 *   right-to-left reading order on Hebrew or Arabic systems.
 *
 * @return None.
 */
WINCOMMCTRLAPI void WINAPI DrawStatusTextA(HDC hDC, LPRECT lprc, LPCSTR pszText, UINT uFlags);
/**
 * This function draws the specified text in the style of a status window with borders.
 *
 * @param hdc Handle to the display context for the window.
 * @param lprc Long pointer to a RECT structure that contains the position, in client coordinates,
 *   of the rectangle in which the text is drawn. The function draws the borders just inside the edges
 *   of the specified rectangle.
 * @param pszText Pointer to a null-terminated string that specifies the text to display. Tab
 *   characters in the string determine whether the string is left-aligned, right-aligned, or
 *   centered.
 * @param uFlags Text drawing flags. This parameter can be a combination of these values: Value
 *   Description SBT_NOBORDERS Prevents borders from being drawn around the specified text. SBT_POPOUT
 *   Draws highlighted borders that make the text stand out. SBT_RTLREADING Displays text using
 *   right-to-left reading order on Hebrew or Arabic systems.
 *
 * @return None.
 */
WINCOMMCTRLAPI void WINAPI DrawStatusTextW(HDC hDC, LPRECT lprc, LPCWSTR pszText, UINT uFlags);

/**
 * This function creates a status window, which is typically used to display the status of an
 * application. The window generally appears at the bottom of the parent window, and it contains the
 * specified text.
 *
 * @param style Window styles for the status window. This parameter must include the WS_CHILD style
 *   and should also include the WS_VISIBLE style.
 * @param lpszText Long pointer to a null-terminated string that contains the status text for the
 *   first part.
 * @param hwndParent Handle to the parent window.
 * @param wID Control identifier for the status window. The window procedure uses this value to
 *   identify messages it sends to the parent window.
 *
 * @return The handle for the status window indicates success. NULL indicates failure. To get
 *   extended error information, call GetLastError.
 *
 * The CreateStatusWindow function calls the CreateWindow function to create the window. It passes
 * the parameters to CreateWindow without modification and sets the position, width, and height
 * parameters to default values.
 */
WINCOMMCTRLAPI HWND WINAPI CreateStatusWindowA(LONG style, LPCSTR lpszText, HWND hwndParent, UINT wID);
/**
 * This function creates a status window, which is typically used to display the status of an
 * application. The window generally appears at the bottom of the parent window, and it contains the
 * specified text.
 *
 * @param style Window styles for the status window. This parameter must include the WS_CHILD style
 *   and should also include the WS_VISIBLE style.
 * @param lpszText Long pointer to a null-terminated string that contains the status text for the
 *   first part.
 * @param hwndParent Handle to the parent window.
 * @param wID Control identifier for the status window. The window procedure uses this value to
 *   identify messages it sends to the parent window.
 *
 * @return The handle for the status window indicates success. NULL indicates failure. To get
 *   extended error information, call GetLastError.
 *
 * The CreateStatusWindow function calls the CreateWindow function to create the window. It passes
 * the parameters to CreateWindow without modification and sets the position, width, and height
 * parameters to default values.
 */
WINCOMMCTRLAPI HWND WINAPI CreateStatusWindowW(LONG style, LPCWSTR lpszText, HWND hwndParent, UINT wID);

#ifdef UNICODE
/**
 * This function creates a status window, which is typically used to display the status of an
 * application. The window generally appears at the bottom of the parent window, and it contains the
 * specified text.
 *
 * @param style Window styles for the status window. This parameter must include the WS_CHILD style
 *   and should also include the WS_VISIBLE style.
 * @param lpszText Long pointer to a null-terminated string that contains the status text for the
 *   first part.
 * @param hwndParent Handle to the parent window.
 * @param wID Control identifier for the status window. The window procedure uses this value to
 *   identify messages it sends to the parent window.
 *
 * @return The handle for the status window indicates success. NULL indicates failure. To get
 *   extended error information, call GetLastError.
 *
 * The CreateStatusWindow function calls the CreateWindow function to create the window. It passes
 * the parameters to CreateWindow without modification and sets the position, width, and height
 * parameters to default values.
 */
#define CreateStatusWindow      CreateStatusWindowW
/**
 * This function draws the specified text in the style of a status window with borders.
 *
 * @param hdc Handle to the display context for the window.
 * @param lprc Long pointer to a RECT structure that contains the position, in client coordinates,
 *   of the rectangle in which the text is drawn. The function draws the borders just inside the edges
 *   of the specified rectangle.
 * @param pszText Pointer to a null-terminated string that specifies the text to display. Tab
 *   characters in the string determine whether the string is left-aligned, right-aligned, or
 *   centered.
 * @param uFlags Text drawing flags. This parameter can be a combination of these values: Value
 *   Description SBT_NOBORDERS Prevents borders from being drawn around the specified text. SBT_POPOUT
 *   Draws highlighted borders that make the text stand out. SBT_RTLREADING Displays text using
 *   right-to-left reading order on Hebrew or Arabic systems.
 *
 * @return None.
 */
#define DrawStatusText          DrawStatusTextW
#else
/**
 * This function creates a status window, which is typically used to display the status of an
 * application. The window generally appears at the bottom of the parent window, and it contains the
 * specified text.
 *
 * @param style Window styles for the status window. This parameter must include the WS_CHILD style
 *   and should also include the WS_VISIBLE style.
 * @param lpszText Long pointer to a null-terminated string that contains the status text for the
 *   first part.
 * @param hwndParent Handle to the parent window.
 * @param wID Control identifier for the status window. The window procedure uses this value to
 *   identify messages it sends to the parent window.
 *
 * @return The handle for the status window indicates success. NULL indicates failure. To get
 *   extended error information, call GetLastError.
 *
 * The CreateStatusWindow function calls the CreateWindow function to create the window. It passes
 * the parameters to CreateWindow without modification and sets the position, width, and height
 * parameters to default values.
 */
#define CreateStatusWindow      CreateStatusWindowA
/**
 * This function draws the specified text in the style of a status window with borders.
 *
 * @param hdc Handle to the display context for the window.
 * @param lprc Long pointer to a RECT structure that contains the position, in client coordinates,
 *   of the rectangle in which the text is drawn. The function draws the borders just inside the edges
 *   of the specified rectangle.
 * @param pszText Pointer to a null-terminated string that specifies the text to display. Tab
 *   characters in the string determine whether the string is left-aligned, right-aligned, or
 *   centered.
 * @param uFlags Text drawing flags. This parameter can be a combination of these values: Value
 *   Description SBT_NOBORDERS Prevents borders from being drawn around the specified text. SBT_POPOUT
 *   Draws highlighted borders that make the text stand out. SBT_RTLREADING Displays text using
 *   right-to-left reading order on Hebrew or Arabic systems.
 *
 * @return None.
 */
#define DrawStatusText          DrawStatusTextA
#endif

#ifdef _WIN32
#define STATUSCLASSNAMEW        L"msctls_statusbar32"
#define STATUSCLASSNAMEA        "msctls_statusbar32"

#ifdef UNICODE
#define STATUSCLASSNAME         STATUSCLASSNAMEW
#else
#define STATUSCLASSNAME         STATUSCLASSNAMEA
#endif

#else
#define STATUSCLASSNAME         "msctls_statusbar"
#endif

#define SB_SETTEXTA             (WM_USER+1)
#define SB_SETTEXTW             (WM_USER+11)
#define SB_GETTEXTA             (WM_USER+2)
#define SB_GETTEXTW             (WM_USER+13)
#define SB_GETTEXTLENGTHA       (WM_USER+3)
#define SB_GETTEXTLENGTHW       (WM_USER+12)

#ifdef UNICODE
/**
 * This message retrieves the text from the specified part of a status window.
 *
 * @param iPart Zero-based index of the part from which to retrieve text.
 * @param szText Address of the buffer that receives the text. This parameter is a null-terminated
 *   string.
 *
 * @return Returns a 32-bit value that consists of two 16-bit values. The low word specifies the
 *   length, in characters, of the text. The high word specifies the type of operation used to draw
 *   the text. The type can be one of the following values: Value Description 0 The text is drawn with
 *   a border to appear lower than the plane of the window. SBT_NOBORDERS The text is drawn without
 *   borders. SBT_POPOUT The text is drawn with a border to appear higher than the plane of the
 *   window. SBT_RTLREADING Displays text using right-to-left reading order on Hebrew or Arabic
 *   systems.
 */
#define SB_GETTEXT              SB_GETTEXTW
/**
 * This message sets the text in the specified part of a status window.
 *
 * @param iPart Zero-based index of the part to set. If this value is 255, the status window is
 *   assumed to be a simple window having only one part.
 * @param uType Type of drawing operation. It is one of the following values: Value Description 0
 *   The text is drawn with a border to appear lower than the plane of the window. SBT_NOBORDERS The
 *   text is drawn without borders. SBT_OWNERDRAW The text is drawn by the parent window. SBT_POPOUT
 *   The text is drawn with a border to appear higher than the plane of the window. SBT_RTLREADING
 *   Displays text using right-to-left reading order on Hebrew or Arabic systems.
 * @param szText Null-terminated string that specifies the text to set. If uType is SBT_OWNERDRAW,
 *   this parameter represents 32 bits of data. The parent window must interpret the data and draw the
 *   text when it receives the WM_DRAWITEM message. The text for each part is limited to 127
 *   characters.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define SB_SETTEXT              SB_SETTEXTW
/**
 * This message retrieves the length, in characters, of the text from the specified part of a status
 * window.
 *
 * @param iPart Zero-based index of the part from which to retrieve text.
 *
 * @return Returns a 32-bit value that consists of two 16-bit values. The low word specifies the
 *   length, in characters, of the text. The high word specifies the type of operation used to draw
 *   the text. The type can be one of the following values: Value Description 0 The text is drawn with
 *   a border to appear lower than the plane of the window. SBT_NOBORDERS The text is drawn without
 *   borders. SBT_OWNERDRAW The text is drawn by the parent window. SBT_POPOUT The text is drawn with
 *   a border to appear higher than the plane of the window. SBT_RTLREADING Displays text using
 *   right-to-left reading order on Hebrew or Arabic systems.
 */
#define SB_GETTEXTLENGTH        SB_GETTEXTLENGTHW
#else
/**
 * This message retrieves the text from the specified part of a status window.
 *
 * @param iPart Zero-based index of the part from which to retrieve text.
 * @param szText Address of the buffer that receives the text. This parameter is a null-terminated
 *   string.
 *
 * @return Returns a 32-bit value that consists of two 16-bit values. The low word specifies the
 *   length, in characters, of the text. The high word specifies the type of operation used to draw
 *   the text. The type can be one of the following values: Value Description 0 The text is drawn with
 *   a border to appear lower than the plane of the window. SBT_NOBORDERS The text is drawn without
 *   borders. SBT_POPOUT The text is drawn with a border to appear higher than the plane of the
 *   window. SBT_RTLREADING Displays text using right-to-left reading order on Hebrew or Arabic
 *   systems.
 */
#define SB_GETTEXT              SB_GETTEXTA
/**
 * This message sets the text in the specified part of a status window.
 *
 * @param iPart Zero-based index of the part to set. If this value is 255, the status window is
 *   assumed to be a simple window having only one part.
 * @param uType Type of drawing operation. It is one of the following values: Value Description 0
 *   The text is drawn with a border to appear lower than the plane of the window. SBT_NOBORDERS The
 *   text is drawn without borders. SBT_OWNERDRAW The text is drawn by the parent window. SBT_POPOUT
 *   The text is drawn with a border to appear higher than the plane of the window. SBT_RTLREADING
 *   Displays text using right-to-left reading order on Hebrew or Arabic systems.
 * @param szText Null-terminated string that specifies the text to set. If uType is SBT_OWNERDRAW,
 *   this parameter represents 32 bits of data. The parent window must interpret the data and draw the
 *   text when it receives the WM_DRAWITEM message. The text for each part is limited to 127
 *   characters.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define SB_SETTEXT              SB_SETTEXTA
/**
 * This message retrieves the length, in characters, of the text from the specified part of a status
 * window.
 *
 * @param iPart Zero-based index of the part from which to retrieve text.
 *
 * @return Returns a 32-bit value that consists of two 16-bit values. The low word specifies the
 *   length, in characters, of the text. The high word specifies the type of operation used to draw
 *   the text. The type can be one of the following values: Value Description 0 The text is drawn with
 *   a border to appear lower than the plane of the window. SBT_NOBORDERS The text is drawn without
 *   borders. SBT_OWNERDRAW The text is drawn by the parent window. SBT_POPOUT The text is drawn with
 *   a border to appear higher than the plane of the window. SBT_RTLREADING Displays text using
 *   right-to-left reading order on Hebrew or Arabic systems.
 */
#define SB_GETTEXTLENGTH        SB_GETTEXTLENGTHA
#endif


/**
 * This message sets the number of parts in a status window and the coordinate of the right edge of
 * each part.
 *
 * @param nParts Number of parts to set (cannot be greater than 255).
 * @param aWidths Address of an integer array that has the same number of elements as parts
 *   specified by nParts. Each element in the array specifies the position, in client coordinates, of
 *   the right edge of the corresponding part. If an element is -1, the position of the right edge for
 *   that part extends to the right edge of the window.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define SB_SETPARTS             (WM_USER+4)
/**
 * This message retrieves a count of the parts in a status window. The message also retrieves the
 * coordinate of the right edge of the specified number of parts.
 *
 * @param nParts Number of parts for which to retrieve coordinates. If this parameter is greater
 *   than the number of parts in the window, the message retrieves coordinates for existing parts
 *   only.
 * @param aRightCoord Address of an integer array that has the same number of elements as parts
 *   specified by nParts. Each element in the array receives the client coordinate of the right edge
 *   of the corresponding part. If an element is set to -1, the position of the right edge for that
 *   part extends to the right edge of the window. To retrieve the current number of parts, set this
 *   parameter to zero.
 *
 * @return The number of parts in the window indicates success. Zero indicates failure.
 */
#define SB_GETPARTS             (WM_USER+6)
/**
 * This message retrieves the current widths of the horizontal and vertical borders of a status
 * window.
 *
 * @param aBorders Address of an integer array that has three elements. The first element receives
 *   the width of the horizontal border, the second receives the width of the vertical border, and the
 *   third receives the width of the border between rectangles.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define SB_GETBORDERS           (WM_USER+7)
/**
 * This message sets the minimum height of a status window's drawing area.
 *
 * @param minHeight Minimum height, in pixels, of the window.
 *
 * @return None.
 */
#define SB_SETMINHEIGHT         (WM_USER+8)
/**
 * This message specifies whether a status window displays simple text or displays all window parts
 * set by a previous SB_SETPARTS message.
 *
 * @param fSimple Boolean value that is set to TRUE if the window displays simple text, or to FALSE
 *   if it displays multiple parts.
 *
 * @return FALSE indicates that an error has occurred.
 */
#define SB_SIMPLE               (WM_USER+9)
/**
 * This message retrieves the bounding rectangle of a part in a status window.
 *
 * @param iPart Zero-based index of the part whose bounding rectangle is to be retrieved.
 * @param lprc Long pointer to a RECT structure that receives the bounding rectangle.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define SB_GETRECT              (WM_USER+10)
#if (_WIN32_IE >= 0x0300)
/**
 * This message checks a status window control to determine if it is in simple mode.
 *
 * @return Returns nonzero if the status window control is in simple mode, or zero otherwise.
 */
#define SB_ISSIMPLE             (WM_USER+14)
#endif



#define SBT_OWNERDRAW            0x1000
#define SBT_NOBORDERS            0x0100
#define SBT_POPOUT               0x0200
#define SBT_RTLREADING           0x0400

/// status bar notifications
#if (_WIN32_IE >= 0x0400)
/**
 * This notification message sent by a status window control when the simple mode changes due to a
 * SB_SIMPLE message. The SBN_SIMPLEMODECHANGE notification message is sent in the form of a
 * WM_NOTIFY message.
 *
 * @param lpnmh Long pointer to an NMHDR structure that contains information about the notification.
 */
#define SBN_SIMPLEMODECHANGE    (SBN_FIRST - 0)
#endif

#endif      // NOSTATUSBAR

//====== TRACKBAR CONTROL =====================================================

#ifndef NOTRACKBAR

#ifdef _WIN32

#define TRACKBAR_CLASSA         "msctls_trackbar32"
#define TRACKBAR_CLASSW         L"msctls_trackbar32"

#ifdef UNICODE
#define  TRACKBAR_CLASS         TRACKBAR_CLASSW
#else
#define  TRACKBAR_CLASS         TRACKBAR_CLASSA
#endif

#else
#define TRACKBAR_CLASS          "msctls_trackbar"
#endif


// begin_r_commctrl

#define TBS_AUTOTICKS           0x0001
#define TBS_VERT                0x0002
#define TBS_HORZ                0x0000
#define TBS_TOP                 0x0004
#define TBS_BOTTOM              0x0000
#define TBS_LEFT                0x0004
#define TBS_RIGHT               0x0000
#define TBS_BOTH                0x0008
#define TBS_NOTICKS             0x0010
#define TBS_ENABLESELRANGE      0x0020
#define TBS_FIXEDLENGTH         0x0040
#define TBS_NOTHUMB             0x0080

// end_r_commctrl

/**
 * This message retrieves the current position of the slider in a trackbar.
 *
 * @return Returns a 32-bit value that specifies the current logical position of the trackbar's
 *   slider.
 */
#define TBM_GETPOS              (WM_USER)
/**
 * This message retrieves the minimum position for the slider in a trackbar.
 *
 * @return Returns a 32-bit value that specifies the minimum position in the trackbar's range of
 *   minimum to maximum slider positions.
 */
#define TBM_GETRANGEMIN         (WM_USER+1)
/**
 * This message retrieves the maximum position for the slider in a trackbar.
 *
 * @return Returns a 32-bit value that specifies the maximum position in the trackbar's range of
 *   minimum to maximum slider positions.
 */
#define TBM_GETRANGEMAX         (WM_USER+2)
/**
 * This message retrieves the position of a tick mark in a trackbar.
 *
 * @param iTic Zero-based index that identifies a tick mark. Valid indexes are in the range from
 *   zero to two less than the tick count returned by the TBM_GETNUMTICS message.
 *
 * @return The logical position of the specified tick mark indicates success. -1 indicates that iTic
 *   does not specify a valid index.
 */
#define TBM_GETTIC              (WM_USER+3)
/**
 * This message sets the position of a tick mark in a trackbar.
 *
 * @param lPosition Position of the tick mark. This parameter can be any of the integer values in
 *   the trackbar's range of minimum to maximum slider positions.
 *
 * @return TRUE indicates that the tick mark is set. FALSE indicates otherwise.
 *
 * A trackbar creates its own first and last tick marks. Do not use this message to set the first
 * and last tick marks.
 */
#define TBM_SETTIC              (WM_USER+4)
/**
 * This message sets the current position of the slider in a trackbar.
 *
 * @param fPosition Redraw flag. If set to TRUE, the message redraws the control with the slider at
 *   the position given by lPosition. If set to FALSE, the message does not redraw the slider at the
 *   new position. The message sets the value of the slider position (as returned by the TBM_GETPOS
 *   message) regardless of the fPosition parameter.
 * @param lPosition New logical position of the slider. Valid logical positions are the integer
 *   values in the trackbar's range of minimum to maximum slider positions. If this value is outside
 *   the control's maximum and minimum range, the position is set to the maximum or minimum value.
 *
 * @return None.
 */
#define TBM_SETPOS              (WM_USER+5)
/**
 * This message sets the range-minimum and maximum positions-for the slider in a trackbar.
 *
 * @param fRedraw Redraw flag. If set to TRUE, the trackbar is redrawn after the range is set. If
 *   set to FALSE, the message sets the range but does not redraw the trackbar.
 * @param lMinimum Minimum position for the slider.
 * @param lMaximum Maximum position for the slider.
 *
 * @return None.
 *
 * If the current slider position is outside the new range, the TBM_SETRANGE message sets the slider
 * position to the new maximum or minimum value.
 */
#define TBM_SETRANGE            (WM_USER+6)
/**
 * This message sets the minimum position for the slider in a trackbar.
 *
 * @param fRedraw Redraw flag. If set to TRUE, the message redraws the trackbar after the range is
 *   set. If set to FALSE, the message sets the range but does not redraw the trackbar.
 * @param lMinimum Minimum position for the slider.
 *
 * @return None.
 *
 * If the current slider position is less than the new minimum, the TBM_SETRANGEMIN message sets the
 * slider position to the new minimum value.
 */
#define TBM_SETRANGEMIN         (WM_USER+7)
/**
 * This message sets the maximum position for the slider in a trackbar.
 *
 * @param fRedraw Redraw flag. If set to TRUE, the trackbar is redrawn after the range is set. If
 *   set to FALSE, the message sets the range but does not redraw the trackbar.
 * @param lMaximum Maximum position for the slider.
 *
 * @return None.
 *
 * If the current slider position is greater than the new maximum, the TBM_SETRANGEMAX message sets
 * the slider position to the new maximum value.
 */
#define TBM_SETRANGEMAX         (WM_USER+8)
/**
 * This message removes the current tick marks from a trackbar. This message does not remove the
 * first and last tick marks, which are created automatically by the trackbar.
 *
 * @param fRedraw Redraw flag. If set to TRUE, the trackbar is redrawn after the tick marks are
 *   cleared. If set to FALSE, the message clears the tick marks but does not redraw the trackbar.
 *
 * @return None.
 */
#define TBM_CLEARTICS           (WM_USER+9)
/**
 * This message sets the starting and ending positions for the current selection in a trackbar. This
 * message is ignored if the trackbar does not have the TBS_ENABLESELRANGE style.
 *
 * @param fRedraw Redraw flag. If set to TRUE, the message redraws the trackbar after the selection
 *   range is set. If set to FALSE, the message sets the selection range but does not redraw the
 *   trackbar.
 * @param lMinimum Starting logical position for the selection range.
 * @param lMaximum Ending logical position for the selection range.
 *
 * @return None.
 */
#define TBM_SETSEL              (WM_USER+10)
/**
 * This message sets the starting position of the current selection in a trackbar. This message is
 * ignored if the trackbar does not have the TBS_ENABLESELRANGE style.
 *
 * @param fRedraw Redraw flag. If set to TRUE, the message redraws the trackbar after the selection
 *   range is set. If set to FALSE, the message sets the selection range but does not redraw the
 *   trackbar.
 * @param lStart Starting position of the selection range.
 *
 * @return None.
 */
#define TBM_SETSELSTART         (WM_USER+11)
/**
 * This message sets the ending position of the current selection in a trackbar. This message is
 * ignored if the trackbar does not have the TBS_ENABLESELRANGE style.
 *
 * @param fRedraw Redraw flag. If set to TRUE, the message redraws the trackbar after the selection
 *   range is set. If set to FALSE, the message sets the selection range but does not redraw the
 *   trackbar.
 * @param lEnd Ending logical position of the selection range.
 *
 * @return None.
 */
#define TBM_SETSELEND           (WM_USER+12)
/**
 * This message retrieves the address of the array that contains the positions of tick marks for a
 * trackbar.
 *
 * @return Returns the address of an array of DWORD values. The elements of the array specify the
 *   logical positions of the trackbar's tick marks, not including the first and last tick marks
 *   created by the trackbar. The logical positions can be any of the integer values in the trackbar's
 *   range of minimum to maximum slider positions.
 */
#define TBM_GETPTICS            (WM_USER+14)
/**
 * This message retrieves the current physical position of a tick mark in a trackbar.
 *
 * @param iTic Zero-based index that identifies a tick mark. Valid indexes are in the range from
 *   zero to two less than the tick count returned by the TBM_GETNUMTICS message.
 *
 * @return Returns the distance, in client coordinates, from the left or top of the trackbar's
 *   client area to the specified tick mark. The return value is the x-coordinate of the tick mark for
 *   a horizontal trackbar or the y-coordinate for a vertical trackbar. -1 indicates that iTic is not
 *   a valid index.
 */
#define TBM_GETTICPOS           (WM_USER+15)
/**
 * This message retrieves the number of tick marks in a trackbar.
 *
 * @return The number of tick marks indicates success.
 */
#define TBM_GETNUMTICS          (WM_USER+16)
/**
 * This message retrieves the starting position of the current selection in a trackbar.
 *
 * @return Returns a 32-bit value that specifies the starting position of the current selection
 *   range.
 *
 * A trackbar can have a selection range only if you specified the TBS_ENABLESELRANGE style when you
 * created it.
 */
#define TBM_GETSELSTART         (WM_USER+17)
/**
 * This message retrieves the ending position of the current selection in a trackbar.
 *
 * @return Returns a 32-bit value that specifies the ending position of the current selection range.
 *
 * A trackbar can have a selection range only if you specified the TBS_ENABLESELRANGE style when you
 * created it.
 */
#define TBM_GETSELEND           (WM_USER+18)
/**
 * This message clears the current selection in a trackbar.
 *
 * @param fRedraw Redraw flag. If set to TRUE, the trackbar is redrawn after the selection is
 *   cleared.
 *
 * @return None.
 *
 * A trackbar can have a selection range only if you specified the TBS_ENABLESELRANGE style when you
 * created it.
 */
#define TBM_CLEARSEL            (WM_USER+19)
/**
 * This message sets the interval frequency for tick marks in a trackbar. For example, if the
 * frequency is set to two, a tick mark is displayed for every other increment in the trackbar's
 * range. The default setting for the frequency is one; that is, every increment in the range is
 * associated with a tick mark.
 *
 * @param wFreq Frequency of the tick marks.
 *
 * @return None.
 */
#define TBM_SETTICFREQ          (WM_USER+20)
/**
 * This message sets the size of the page for a trackbar. The page size affects how much the slider
 * moves for the TB_PAGEUP and TB_PAGEDOWN notification messages.
 *
 * @param lPageSize New page size.
 *
 * @return Returns a 32-bit value that specifies the previous page size.
 *
 * The trackbar also sends the TB_PAGEUP and TB_PAGEDOWN notification messages to its parent window
 * when it receives keyboard or mouse input that scrolls the page.
 */
#define TBM_SETPAGESIZE         (WM_USER+21)
/**
 * This message retrieves the size of the page for a trackbar. The page size affects how much the
 * slider moves for the TB_PAGEUP and TB_PAGEDOWN notification messages.
 *
 * @return Returns a 32-bit value that specifies the page size for the trackbar.
 *
 * The trackbar also sends the TB_PAGEUP and TB_PAGEDOWN notification messages to its parent window
 * when it receives keyboard or mouse input that scrolls the page.
 */
#define TBM_GETPAGESIZE         (WM_USER+22)
/**
 * This message sets the size of the line for a trackbar. The line size affects how much the slider
 * moves for the TB_LINEUP and TB_LINEDOWN notification messages.
 *
 * @param lLineSize New line size.
 *
 * @return Returns a 32-bit value that specifies the previous line size.
 *
 * The default setting for the line size is 1.
 *
 * The trackbar also sends the TB_LINEUP and TB_LINEDOWN notification messages to its parent window
 * when the user presses the arrow keys.
 */
#define TBM_SETLINESIZE         (WM_USER+23)
/**
 * This message retrieves the size of the line for a trackbar. The line size affects how much the
 * slider moves for the TB_LINEUP and TB_LINEDOWN notification messages.
 *
 * @return Returns a 32-bit value that specifies the line size for the trackbar.
 *
 * The default setting for the line size is 1.
 *
 * The trackbar also sends the TB_LINEUP and TB_LINEDOWN notification messages to its parent window
 * when the user presses the arrow keys.
 */
#define TBM_GETLINESIZE         (WM_USER+24)
/**
 * This message retrieves the size and position of the bounding rectangle for the slider in a
 * trackbar.
 *
 * @param lprc Long pointer to a RECT structure. The message fills this structure with the bounding
 *   rectangle of the trackbar's slider, in client coordinates of the trackbar's window.
 *
 * @return None.
 */
#define TBM_GETTHUMBRECT        (WM_USER+25)
/**
 * This message retrieves the size and position of the bounding rectangle for a trackbar's channel.
 * The channel is the area over which the slider moves. It contains the highlight when a range is
 * selected.
 *
 * @param lprc Long pointer to a RECT structure. The message fills this structure with the channel's
 *   bounding rectangle, in client coordinates of the trackbar's window.
 *
 * @return None.
 */
#define TBM_GETCHANNELRECT      (WM_USER+26)
/**
 * This message sets the length of the slider in a trackbar. This message is ignored if the trackbar
 * does not have the TBS_FIXEDLENGTH style.
 *
 * @param iLength Length, in pixels, of the slider.
 *
 * @return None.
 */
#define TBM_SETTHUMBLENGTH      (WM_USER+27)
/**
 * This message retrieves the length of the slider in a trackbar.
 *
 * @return The length, in pixels, of the slider indicates success.
 */
#define TBM_GETTHUMBLENGTH      (WM_USER+28)
#if (_WIN32_IE >= 0x0300)
/**
 * This message assigns a window as the buddy window for a trackbar control. Trackbar buddy windows
 * are automatically displayed in a location relative to the control's orientation, horizontal or
 * vertical.
 *
 * @param fLocation Boolean that specifies the location at which to display the buddy window. It is
 *   one of the following values: Value Description TRUE The buddy appears to the left of the trackbar
 *   if the trackbar control uses the TBS_HORZ style. If the trackbar uses the TBS_VERT style, the
 *   buddy appears above the trackbar control. FALSE The buddy appears to the right of the trackbar if
 *   the trackbar control uses the TBS_HORZ style. If the trackbar uses the TBS_VERT style, the buddy
 *   appears below the trackbar control.
 * @param hwndBuddy Handle to the window to be set as the trackbar control's buddy.
 *
 * @return Returns the handle to the window that was previously assigned to the control at that
 *   location.
 *
 * Trackbar controls support up to two buddy windows. This can be useful when you must display text
 * or images at each end of the control.
 */
#define TBM_SETBUDDY            (WM_USER+32) // wparam = BOOL fLeft; (or right)
/**
 * This message retrieves the handle to a trackbar control buddy window at a specified location. The
 * specified location is relative to the control's orientation, horizontal or vertical.
 *
 * @param fLocation Boolean that specifies which buddy window handle is retrieved, by relative
 *   location. It is one of the following values: Value Description TRUE Retrieves the handle to the
 *   buddy to the left of the trackbar. If the trackbar control uses the TBS_VERT style, the message
 *   will retrieve the buddy above the trackbar. FALSE Retrieves the handle to the buddy to the right
 *   of the trackbar. If the trackbar control uses the TBS_VERT style, the message will retrieve the
 *   buddy below the trackbar.
 *
 * @return Returns the handle to the buddy window at the location specified by fLocation, or NULL if
 *   no buddy exists at that location.
 */
#define TBM_GETBUDDY            (WM_USER+33) // wparam = BOOL fLeft; (or right)
#endif


#define TB_LINEUP               0
#define TB_LINEDOWN             1
#define TB_PAGEUP               2
#define TB_PAGEDOWN             3
#define TB_THUMBPOSITION        4
#define TB_THUMBTRACK           5
#define TB_TOP                  6
#define TB_BOTTOM               7
#define TB_ENDTRACK             8


#if (_WIN32_IE >= 0x0300)
// custom draw item specs
#define TBCD_TICS    0x0001
#define TBCD_THUMB   0x0002
#define TBCD_CHANNEL 0x0003
#endif

#endif // trackbar

//====== UPDOWN CONTROL =======================================================

#ifndef NOUPDOWN

#ifdef _WIN32

#define UPDOWN_CLASSA           "msctls_updown32"
#define UPDOWN_CLASSW           L"msctls_updown32"

#ifdef UNICODE
#define  UPDOWN_CLASS           UPDOWN_CLASSW
#else
#define  UPDOWN_CLASS           UPDOWN_CLASSA
#endif

#else
#define UPDOWN_CLASS            "msctls_updown"
#endif


/**
 * This structure contains acceleration information for an up-down control.
 */
typedef struct _UDACCEL {
    /**
     * Amount of elapsed time, in seconds, before the position change increment specified by nInc is
     * used.
     */
    UINT nSec;
    /**
     * Position change increment to use after the time specified by nSec elapses.
     */
    UINT nInc;
} UDACCEL, FAR *LPUDACCEL;

#define UD_MAXVAL               0x7fff
#define UD_MINVAL               (-UD_MAXVAL)

// begin_r_commctrl

#define UDS_WRAP                0x0001
#define UDS_SETBUDDYINT         0x0002
#define UDS_ALIGNRIGHT          0x0004
#define UDS_ALIGNLEFT           0x0008
#define UDS_AUTOBUDDY           0x0010
#define UDS_ARROWKEYS           0x0020
#define UDS_HORZ                0x0040
#define UDS_NOTHOUSANDS         0x0080
#if (_WIN32_IE >= 0x0300)
#define UDS_HOTTRACK            0x0100
#endif

// end_r_commctrl

/**
 * This message sets the minimum and maximum positions, or the range, for a up-down control.
 *
 * @param nUpper and nLower Maximum position and minimum position for the up-down control. Neither
 *   position can be greater than the UD_MAXVAL value or less than the UD_MINVAL value. In addition,
 *   the difference between the two positions cannot exceed UD_MAXVAL.
 *
 * @return None
 */
#define UDM_SETRANGE            (WM_USER+101)
/**
 * This message retrieves the minimum and maximum positions, or the range, for an up-down control.
 *
 * @return The return value is a 32-bit value that contains the minimum and maximum positions. The
 *   low-order word is the maximum position for the control, and the high-order word is the minimum
 *   position.
 */
#define UDM_GETRANGE            (WM_USER+102)
/**
 * This message sets the current position for an up-down control.
 *
 * @param nPos New position for the up-down control. This parameter must be in the range specified
 *   by the upper and lower limits for the control.
 *
 * @return The previous position indicates success.
 */
#define UDM_SETPOS              (WM_USER+103)
/**
 * This message retrieves the current position of an up-down control.
 *
 * @return The return value is the current position in the low-order word. If an error occurred, the
 *   high-order word is nonzero.
 */
#define UDM_GETPOS              (WM_USER+104)
/**
 * This message sets the buddy window for an up-down control.
 *
 * @param hwndBuddy Handle to the new buddy window.
 *
 * @return The handle to the previous buddy window indicates success.
 *
 * If hwndBuddy is not NULL, it must specify an edit control because up/down controls can only be
 * buddied with edit controls.
 */
#define UDM_SETBUDDY            (WM_USER+105)
/**
 * This message retrieves the handle of the current buddy window.
 *
 * @return The handle to the current buddy window indicates success.
 */
#define UDM_GETBUDDY            (WM_USER+106)
/**
 * This message sets the acceleration for an up-down control.
 *
 * @param nAccels Number of UDACCEL structures specified by aAccels.
 * @param aAccels Pointer to an array of UDACCEL structures that contain acceleration information.
 *   Elements should be sorted in ascending order based on the nSec member.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define UDM_SETACCEL            (WM_USER+107)
/**
 * This message retrieves acceleration information for an up-down control.
 *
 * @param cAccels Number of elements in the array specified by paAccels.
 * @param paAccels Pointer to an array of UDACCEL structures that receive acceleration information.
 *
 * @return The return value is the number of accelerator structures retrieved. If the cAccels
 *   parameter is zero and the paAccels parameter is NULL, the return value is the number of
 *   accelerators currently set for the control.
 */
#define UDM_GETACCEL            (WM_USER+108)
/**
 * This message sets the radix base for an up-down control. The base value determines whether the
 * buddy window displays numbers in decimal or hexadecimal digits. Hexadecimal numbers are always
 * unsigned, and decimal numbers are signed.
 *
 * @param nBase New base value for the control. This parameter can be 10 for decimal or 16 for
 *   hexadecimal.
 *
 * @return The previous base value indicates success. Zero indicates that an invalid base was given.
 */
#define UDM_SETBASE             (WM_USER+109)
/**
 * The UDM_GETBASE message retrieves the current radix base-that is, either base 10 or 16-for an
 * up-down control.
 *
 * @return The current base value indicates success.
 */
#define UDM_GETBASE             (WM_USER+110)
#if (_WIN32_IE >= 0x0400)
/**
 * This message sets the 32-bit range of an up-down control.
 *
 * @param iLow Integer value that represents the new lower limit of the up-down control range.
 * @param iHigh Integer value that represents the new upper limit of the up-down control range.
 *
 * @return None
 */
#define UDM_SETRANGE32          (WM_USER+111)
/**
 * This message retrieves the 32-bit range of an up-down control.
 *
 * @param pLow Pointer to an integer that receives the lower limit of the up-down control range.
 *   This parameter may be NULL.
 * @param pHigh Pointer to an integer that receives the upper limit of the up-down control range.
 *   This parameter may be NULL.
 *
 * @return None
 */
#define UDM_GETRANGE32          (WM_USER+112) // wParam & lParam are LPINT
#endif

/**
 * This function creates an up-down control.
 *
 * @param dwStyle Specifies the window styles for the control. This parameter should include the
 *   WS_CHILD, WS_BORDER, and WS_VISIBLE styles, and it may include any of the window styles specific
 *   to the up-down control.
 * @param x Horizontal coordinate, in client coordinates, of the upper-left corner of the control.
 * @param y Vertical coordinate, in client coordinates, of the upper-left corner of the control.
 * @param cx Width, in pixels, of the up-down control.
 * @param cy Height, in pixels, of the up-down control.
 * @param hParent Handle to the parent window of the up-down control.
 * @param nID Identifier for the up-down control.
 * @param hInst Handle to the module instance of the application creating the up-down control.
 * @param hBuddy Handle to the window associated with the edit up-down control. An edit control is
 *   the only up-down control that has a buddy window. If this parameter is NULL, the control has no
 *   buddy window.
 * @param nUpper Upper limit (range) of the up-down control.
 * @param nLower Lower limit (range) of the up-down control.
 * @param nPos Position of the control.
 *
 * @return The window handle to the up-down control indicates success. NULL indicates failure.
 *
 * The only buddy window for up-down controls is an edit control.
 */
WINCOMMCTRLAPI HWND WINAPI CreateUpDownControl(DWORD dwStyle, int x, int y, int cx, int cy,
                                HWND hParent, int nID, HINSTANCE hInst,
                                HWND hBuddy,
                                int nUpper, int nLower, int nPos);

#if (_WIN32_IE >= 0x0300)
#define NM_UPDOWN      NMUPDOWN
#define LPNM_UPDOWN  LPNMUPDOWN
#else
#define NMUPDOWN      NM_UPDOWN
#define LPNMUPDOWN  LPNM_UPDOWN
#endif

/**
 * This structure contains information specific to up-down control notification messages. It is
 * identical to and replaces the NM_UPDOWN structure.
 *
 * The address of this structure is specified as the lParam parameter of the WM_NOTIFY message that
 * is used to send the UDN_DELTAPOS notification message.
 */
typedef struct _NM_UPDOWN
{
    /**
     * NMHDR structure that contains additional information about the notification message.
     */
    NMHDR hdr;
    /**
     * Signed integer value that represents the up-down control's current position.
     */
    int iPos;
    /**
     * Signed integer value that represents the proposed change in the up-down control's position.
     */
    int iDelta;
} NMUPDOWN, FAR *LPNMUPDOWN;

/**
 * This notification message is sent by the OS to the parent window of an up-down control when the
 * position of the control is about to change. This happens when the user requests a change in the
 * value by pressing the control's up or down arrow. It is sent in the form of a WM_NOTIFY message.
 *
 * @param lpnmud Long pointer to an NMUPDOWN structure that contains information about the position
 *   change. The iPos member of this structure contains the current position of the control. The
 *   iDelta member of the structure is a signed integer that contains the proposed change in position.
 *   If the user has clicked the up button, this is a positive value. If the user has clicked the down
 *   button, this is a negative value.
 *
 * @return Nonzero prevents the change in the control's position. Zero accepts the change.
 *
 * The UDN_DELTAPOS notification is sent before the WM_HSCROLL message, which actually changes the
 * control's position. This enables you to examine, accept, modify, or reject the change.
 */
#define UDN_DELTAPOS            (UDN_FIRST - 1)

#endif  // NOUPDOWN


//====== PROGRESS CONTROL =====================================================

#ifndef NOPROGRESS

#ifdef _WIN32

#define PROGRESS_CLASSA         "msctls_progress32"
#define PROGRESS_CLASSW         L"msctls_progress32"

#ifdef UNICODE
#define  PROGRESS_CLASS         PROGRESS_CLASSW
#else
#define  PROGRESS_CLASS         PROGRESS_CLASSA
#endif

#else
#define PROGRESS_CLASS          "msctls_progress"
#endif


#if (_WIN32_IE >= 0x0300)
#define PBS_SMOOTH              0x01
#define PBS_VERTICAL            0x04
#endif

/**
 * This message sets the minimum and maximum values for a progress bar and redraws the bar to
 * reflect the new range.
 *
 * @param nMinRange Minimum range value. By default, the minimum value is zero.
 * @param nMaxRange Maximum range value. By default, the maximum value is 100.
 *
 * @return The previous range values indicate success. Zero indicates otherwise. The low-order word
 *   specifies the previous minimum value, and the high-order word specifies the previous maximum
 *   value.
 */
#define PBM_SETRANGE            (WM_USER+1)
/**
 * This message sets the current position for a progress bar and redraws the bar to reflect the new
 * position.
 *
 * @param nNewPos Signed integer that becomes the new position.
 *
 * @return The previous position indicates success.
 */
#define PBM_SETPOS              (WM_USER+2)
/**
 * This message advances the current position of a progress bar by a specified increment and redraws
 * the bar to reflect the new position.
 *
 * @param nIncrement Amount to advance the position.
 *
 * @return The previous position indicates success.
 */
#define PBM_DELTAPOS            (WM_USER+3)
/**
 * This message specifies the step increment for a progress bar. The step increment is the amount by
 * which the progress bar increases its current position whenever it receives a PBM_STEPIT message.
 * By default, the step increment is set to 10.
 *
 * @param nStepInc New step increment.
 *
 * @return The previous step increment indicates success.
 */
#define PBM_SETSTEP             (WM_USER+4)
/**
 * This message advances the current position for a progress bar by the step increment and redraws
 * the bar to reflect the new position. An application sets the step increment by sending the
 * PBM_SETSTEP message.
 *
 * @return The previous position indicates success.
 */
#define PBM_STEPIT              (WM_USER+5)
#if (_WIN32_IE >= 0x0300)
/**
 * This message sets the range of a progress bar control to a 32-bit value.
 *
 * @param iLowLim Specifies a 32-bit value that represents the low limit to be set for the progress
 *   bar control.
 * @param iHighLim Specifies a 32-bit value that represents the high limit to be set for the
 *   progress bar control.
 *
 * @return Returns a DWORD that holds the previous 16-bit low limit in its low-order word, and the
 *   previous 16-bit high limit in its high-order word. If the previous ranges were 32-bit values, the
 *   return value consists of the low-order words of both 32-bit limits.
 *
 * To retrieve the entire high and low 32-bit values, use the PBM_GETRANGE message.
 */
#define PBM_SETRANGE32          (WM_USER+6)  // lParam = high, wParam = low
/**
 * This structure contains information about the high and low limits of a progress bar control. This
 * structure is used with the PBM_GETRANGE message.
 */
typedef struct
{
   /**
    * Specifies the current low limit for the progress bar control.
    */
   int iLow;
   /**
    * Specifies the current high limit for the progress bar control.
    */
   int iHigh;
} PBRANGE, *PPBRANGE;
/**
 * This message retrieves information about the current high and low limits of a specified progress
 * bar control.
 *
 * @param fWhichLimit Boolean that specifies which limit value is to be used as the message's return
 *   value. It is one of the following values: Value Description TRUE Return the low limit. FALSE
 *   Return the high limit.
 * @param ppBRange Pointer to a pointer to a PBRANGE structure that is to be filled with the high
 *   and low limits of the progress bar control. If this parameter is set to NULL, the control will
 *   return only the limit specified by fWhichLimit.
 *
 * @return Returns an INT that represents the limit value specified by fWhichLimit. If lParam is not
 *   NULL, lParam must point to a PBRANGE structure that is to be filled with both limit values.
 */
#define PBM_GETRANGE            (WM_USER+7)  // wParam = return (TRUE ? low : high). lParam = PPBRANGE or NULL
/**
 * This message retrieves the current position of the progress bar.
 *
 * @return Returns a UINT that represents the current position of the progress bar.
 */
#define PBM_GETPOS              (WM_USER+8)
#endif      // _WIN32_IE >= 0x0300

#endif  // NOPROGRESS

// begin_r_commctrl

//====== COMMON CONTROL STYLES ================================================

#define CCS_TOP                 0x00000001L
#define CCS_NOMOVEY             0x00000002L
#define CCS_BOTTOM              0x00000003L
#define CCS_NORESIZE            0x00000004L
#define CCS_NOPARENTALIGN       0x00000008L
#define CCS_ADJUSTABLE          0x00000020L
#define CCS_NODIVIDER           0x00000040L
#if (_WIN32_IE >= 0x0300)
#define CCS_VERT                0x00000080L
#define CCS_LEFT                (CCS_VERT | CCS_TOP)
#define CCS_RIGHT               (CCS_VERT | CCS_BOTTOM)
#define CCS_NOMOVEX             (CCS_VERT | CCS_NOMOVEY)
#endif

// end_r_commctrl

//====== LISTVIEW CONTROL =====================================================

#ifndef NOLISTVIEW

#ifdef _WIN32

#define WC_LISTVIEWA            "SysListView32"
#define WC_LISTVIEWW            L"SysListView32"

#ifdef UNICODE
#define WC_LISTVIEW             WC_LISTVIEWW
#else
#define WC_LISTVIEW             WC_LISTVIEWA
#endif

#else
#define WC_LISTVIEW             "SysListView"
#endif

// begin_r_commctrl

#define LVS_ICON                0x0000
#define LVS_REPORT              0x0001
#define LVS_SMALLICON           0x0002
#define LVS_LIST                0x0003
#define LVS_TYPEMASK            0x0003
#define LVS_SINGLESEL           0x0004
#define LVS_SHOWSELALWAYS       0x0008
#define LVS_SORTASCENDING       0x0010
#define LVS_SORTDESCENDING      0x0020
#define LVS_SHAREIMAGELISTS     0x0040
#define LVS_NOLABELWRAP         0x0080
#define LVS_AUTOARRANGE         0x0100
#define LVS_EDITLABELS          0x0200
#if (_WIN32_IE >= 0x0300)
#define LVS_OWNERDATA           0x1000
#endif
#define LVS_NOSCROLL            0x2000

#define LVS_TYPESTYLEMASK       0xfc00

#define LVS_ALIGNTOP            0x0000
#define LVS_ALIGNLEFT           0x0800
#define LVS_ALIGNMASK           0x0c00

#define LVS_OWNERDRAWFIXED      0x0400
#define LVS_NOCOLUMNHEADER      0x4000
#define LVS_NOSORTHEADER        0x8000

// end_r_commctrl

/**
 * This message retrieves the background color of a list view control. You can send this message
 * explicitly or by using the ListView_GetBkColor macro.
 *
 * @return The background color of the list view control indicates success.
 */
#define LVM_GETBKCOLOR          (LVM_FIRST + 0)
/**
 * This macro retrieves the background color of a list view control. You can use this macro or send
 * the LVM_GETBKCOLOR message explicitly.
 *
 * @param hwnd Handle to the list view control.
 *
 * @return Returns the background color of the list view control.
 */
#define ListView_GetBkColor(hwnd)  \
    (COLORREF)SNDMSG((hwnd), LVM_GETBKCOLOR, 0, 0L)

/**
 * This message sets the background color of a list view control. You can send this message
 * explicitly or by using the ListView_SetBkColor macro.
 *
 * @param clrBk Background color to set or the CLR_NONE value for no background color. List view
 *   controls with background colors redraw themselves significantly faster than those without
 *   background colors.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define LVM_SETBKCOLOR          (LVM_FIRST + 1)
/**
 * This macro sets the background color a list view control. You can use this macro or send the
 * LVM_SETBKCOLOR message explicitly.
 *
 * @param hwnd Handle to the list view control.
 * @param clrBk Background color to set or the CLR_NONE value for no background color. List view
 *   controls with background colors redraw themselves significantly faster than those without
 *   background colors.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define ListView_SetBkColor(hwnd, clrBk) \
    (BOOL)SNDMSG((hwnd), LVM_SETBKCOLOR, 0, (LPARAM)(COLORREF)(clrBk))

/**
 * This message retrieves the handle of an image list used for drawing list view items. You can send
 * this message explicitly or by using the ListView_GetImageList macro.
 *
 * @param iImageList Image list to retrieve. It is one of the following values: Value Description
 *   LVSIL_NORMAL Image list with large icons. LVSIL_SMALL Image list with small icons. LVSIL_STATE
 *   Image list with state images.
 *
 * @return The handle to the specified image list indicates success. NULL indicates otherwise.
 *
 * Windows CE supports a new value for the iImageList parameter (WPARAM). The LVSIL_HEADER constant
 * specifies that the image list to be retrieved is the image list displayed in the list view's
 * header control in report view.
 */
#define LVM_GETIMAGELIST        (LVM_FIRST + 2)
/**
 * This macro retrieves the handle to an image list used for drawing list view items. You can use
 * this macro or send the LVM_GETIMAGELIST message explicitly.
 *
 * @param hwnd Handle to the list view control.
 * @param iImageList Image list to retrieve. It is one of the following values: Value Description
 *   LVSIL_NORMAL Image list with large icons. LVSIL_SMALL Image list with small icons. LVSIL_STATE
 *   Image list with state images.
 *
 * @return The handle to the specified image list indicates success. NULL indicates failure.
 *
 * Windows CE supports a new value for the iImageList parameter. The LVSIL_HEADER constant specifies
 * that the image list to be retrieved is the image list displayed in the list view's header control
 * in report view.
 */
#define ListView_GetImageList(hwnd, iImageList) \
    (HIMAGELIST)SNDMSG((hwnd), LVM_GETIMAGELIST, (WPARAM)(INT)(iImageList), 0L)

#define LVSIL_NORMAL            0
#define LVSIL_SMALL             1
#define LVSIL_STATE             2
#ifdef UNDER_CE
#define LVSIL_HEADER            3
#endif // UNDER_CE

/**
 * This message assigns a new image list to a list view control. You can send this message
 * explicitly or by using the ListView_SetImageList macro.
 *
 * @param iImageList Type of image list. It is one of the following values: Value Description
 *   LVSIL_NORMAL Image list with large icons LVSIL_SMALL Image list with small icons LVSIL_STATE
 *   Image list with state images
 * @param himl Handle to the image list to assign
 *
 * @return The handle to the image list previously associated with the control indicates success.
 *   NULL indicates otherwise.
 *
 * Windows CE supports a new value for the iImageList parameter (WPARAM). The LVSIL_HEADER constant
 * specifies that, in report view, the image list will be displayed in the list view's header
 * control.
 */
#define LVM_SETIMAGELIST        (LVM_FIRST + 3)
/**
 * This macro assigns an image list to a list view control. You can use this macro or send the
 * LVM_SETIMAGELIST message explicitly.
 *
 * @param hwnd Handle to the list view control.
 * @param himl Handle to the image list to assign.
 * @param iImageList Type of image list. It is one of the following values: Value Description
 *   LVSIL_NORMAL Image list with large icons. LVSIL_SMALL Image list with small icons. LVSIL_STATE
 *   Image list with state images.
 *
 * @return The handle to the image list previously associated with the control indicates success.
 *   NULL indicates failure.
 *
 * Windows CE supports a new value for the iImageList parameter. The LVSIL_HEADER constant specifies
 * that, in report view, the image list will be displayed in the list view's header control.
 */
#define ListView_SetImageList(hwnd, himl, iImageList) \
    (HIMAGELIST)(UINT)SNDMSG((hwnd), LVM_SETIMAGELIST, (WPARAM)(iImageList), (LPARAM)(UINT)(HIMAGELIST)(himl))

/**
 * This message retrieves the number of items in a list view control. You can send this message
 * explicitly or by using the ListView_GetItemCount macro.
 *
 * @return The number of items indicates success.
 */
#define LVM_GETITEMCOUNT        (LVM_FIRST + 4)
/**
 * This macro retrieves the number of items in a list view control. You can use this macro or send
 * the LVM_GETITEMCOUNT message explicitly.
 *
 * @param hwnd Handle to the list view control.
 *
 * @return Returns the number of items.
 */
#define ListView_GetItemCount(hwnd) \
    (int)SNDMSG((hwnd), LVM_GETITEMCOUNT, 0, 0L)


#define LVIF_TEXT               0x0001
#define LVIF_IMAGE              0x0002
#define LVIF_PARAM              0x0004
#define LVIF_STATE              0x0008
#if (_WIN32_IE >= 0x0300)
#define LVIF_INDENT             0x0010
#define LVIF_NORECOMPUTE        0x0800
#endif

#define LVIS_FOCUSED            0x0001
#define LVIS_SELECTED           0x0002
#define LVIS_CUT                0x0004
#define LVIS_DROPHILITED        0x0008

#define LVIS_OVERLAYMASK        0x0F00
#define LVIS_STATEIMAGEMASK     0xF000

/**
 * This macro prepares the index of a state image so that a tree-view control or list-view control
 * can use the index to retrieve the state image for an item.
 *
 * @param i Index of a state image.
 *
 * The INDEXTOSTATEIMAGEMASK macro is defined as follows:
 *
 *     #define INDEXTOSTATEIMAGEMASK(i) ((i) << 12)
 */
#define INDEXTOSTATEIMAGEMASK(i) ((i) << 12)

#if (_WIN32_IE >= 0x0300)
#define I_INDENTCALLBACK        (-1)
#define LV_ITEMA LVITEMA
#define LV_ITEMW LVITEMW
#else
#define tagLVITEMA    _LV_ITEMA
#define LVITEMA       LV_ITEMA
#define tagLVITEMW    _LV_ITEMW
#define LVITEMW       LV_ITEMW
#endif

#define LV_ITEM LVITEM

/**
 * This structure that specifies or receives the attributes of a list view item. It has been updated
 * to support a new mask value (LVIF_INDENT) that enables item indenting.
 *
 * The LVITEM structure is used with a number of messages, including LVM_GETITEM, LVM_SETITEM,
 * LVM_INSERTITEM, and LVM_DELETEITEM.
 *
 * This structure supersedes the LV_ITEM structure.
 *
 * Size of the buffer pointed to by the pszText member if the structure is receiving item
 * attributes. This member is ignored if the structure specifies item attributes.
 */
typedef struct tagLVITEMA
{
    /**
     * Specifies which members of this structure contain data to be set or are being requested. It can
     * be a combination of one or more of the following flags: Value Description LVIF_TEXT The pszText
     * member is valid or must be filled in. LVIF_IMAGE The iImage member is valid or must be filled in.
     * LVIF_INDENT The iIndent member is valid or must be filled in. LVIF_NORECOMPUTE The control will
     * not generate a LVN_GETDISPINFO message to retrieve text information if it receives a LVM_GETITEM
     * message. Instead, the pszText member will contain LPSTR_TEXTCALLBACK. LVIF_PARAM The lParam
     * member is valid or must be filled in. LVIF_STATE The state member is valid or must be filled in.
     * LVIF_DI_SETITEM The operating system should store the requested list item information, and not
     * ask for it again. This flag is used only with the LVN_GETDISPINFO notification message.
     */
    UINT mask;
    /**
     * Zero-based index of the item to which this structure refers.
     */
    int iItem;
    /**
     * One-based index of the subitem to which this structure refers, or zero if this structure refers
     * to an item rather than a subitem.
     */
    int iSubItem;
    /**
     * Current state of the item if the item's state is being retrieved, or the new state if the item's
     * state is being set. The stateMask member specifies which bits of this member should be retrieved
     * or modified. Any bits in this member that are not set in stateMask will be ignored. This member
     * can be any valid combination of list view state values.
     */
    UINT state;
    /**
     * Specifies which bits of the state member will be retrieved or modified.
     *
     * If the item's state is being retrieved, this member enables you to specify which states will be
     * retrieved. For example, setting this member to LVIS_SELECTED will cause only the item's selection
     * state to be retrieved.
     *
     * If item's state is being modified, this member allows you to modify one or more states without
     * having to retrieve all of the states first. For example, setting this member to LVIS_SELECTED and
     * state to zero will cause the item's selection state to be cleared, but none of the other states
     * will be affected.
     *
     * To retrieve or modify all of the states, set this member to (UINT) -1.
     */
    UINT stateMask;
    /**
     * Pointer to a null-terminated string that contains the item text if the structure specifies item
     * attributes. If this member is the LPSTR_TEXTCALLBACK value, the item is a callback item. Do not
     * set the pszText member to LPSTR_TEXTCALLBACK if the list view control has LVS_SORTASCENDING or
     * LVS_SORTDESCENDING style.
     *
     * If the structure is receiving item attributes, this member is the Pointer to the buffer that
     * receives the item text.
     */
    LPSTR pszText;
    /**
     * Size of the buffer pointed to by the pszText member. If the structure is not receiving
     * information, this member is ignored.
     */
    int cchTextMax;
    /**
     * Index of the list view item's icon in the icon list and the small icon image list.
     *
     * If this member is the I_IMAGECALLBACK value, the parent window is responsible for storing the
     * index. In this case, the list view control sends the parent an LVN_GETDISPINFO notification
     * message to get the index when it needs to display the image.
     */
    int iImage;
    /**
     * Specifies the 32-bit value of the item. If you use the LVM_SORTITEMS message, the list view
     * control passes this value to the application-defined comparison function. You can also use the
     * LVM_FINDITEM message to search a list view control for an item with a specified lParam value.
     */
    LPARAM lParam;
#if (_WIN32_IE >= 0x0300)
    /**
     * Number of image widths to indent the item. A single indentation equals the width of an item
     * image. Therefore, the value 1 indents the item by the width of one image, the value 2 indents by
     * two images, and so on. Note that this member is supported only for items. Attempting to set
     * subitem indentation will cause the calling function to fail.
     */
    int iIndent;
#endif
} LVITEMA, FAR* LPLVITEMA;

/**
 * This structure that specifies or receives the attributes of a list view item. It has been updated
 * to support a new mask value (LVIF_INDENT) that enables item indenting.
 *
 * The LVITEM structure is used with a number of messages, including LVM_GETITEM, LVM_SETITEM,
 * LVM_INSERTITEM, and LVM_DELETEITEM.
 *
 * This structure supersedes the LV_ITEM structure.
 *
 * Size of the buffer pointed to by the pszText member if the structure is receiving item
 * attributes. This member is ignored if the structure specifies item attributes.
 */
typedef struct tagLVITEMW
{
    /**
     * Specifies which members of this structure contain data to be set or are being requested. It can
     * be a combination of one or more of the following flags: Value Description LVIF_TEXT The pszText
     * member is valid or must be filled in. LVIF_IMAGE The iImage member is valid or must be filled in.
     * LVIF_INDENT The iIndent member is valid or must be filled in. LVIF_NORECOMPUTE The control will
     * not generate a LVN_GETDISPINFO message to retrieve text information if it receives a LVM_GETITEM
     * message. Instead, the pszText member will contain LPSTR_TEXTCALLBACK. LVIF_PARAM The lParam
     * member is valid or must be filled in. LVIF_STATE The state member is valid or must be filled in.
     * LVIF_DI_SETITEM The operating system should store the requested list item information, and not
     * ask for it again. This flag is used only with the LVN_GETDISPINFO notification message.
     */
    UINT mask;
    /**
     * Zero-based index of the item to which this structure refers.
     */
    int iItem;
    /**
     * One-based index of the subitem to which this structure refers, or zero if this structure refers
     * to an item rather than a subitem.
     */
    int iSubItem;
    /**
     * Current state of the item if the item's state is being retrieved, or the new state if the item's
     * state is being set. The stateMask member specifies which bits of this member should be retrieved
     * or modified. Any bits in this member that are not set in stateMask will be ignored. This member
     * can be any valid combination of list view state values.
     */
    UINT state;
    /**
     * Specifies which bits of the state member will be retrieved or modified.
     *
     * If the item's state is being retrieved, this member enables you to specify which states will be
     * retrieved. For example, setting this member to LVIS_SELECTED will cause only the item's selection
     * state to be retrieved.
     *
     * If item's state is being modified, this member allows you to modify one or more states without
     * having to retrieve all of the states first. For example, setting this member to LVIS_SELECTED and
     * state to zero will cause the item's selection state to be cleared, but none of the other states
     * will be affected.
     *
     * To retrieve or modify all of the states, set this member to (UINT) -1.
     */
    UINT stateMask;
    /**
     * Pointer to a null-terminated string that contains the item text if the structure specifies item
     * attributes. If this member is the LPSTR_TEXTCALLBACK value, the item is a callback item. Do not
     * set the pszText member to LPSTR_TEXTCALLBACK if the list view control has LVS_SORTASCENDING or
     * LVS_SORTDESCENDING style.
     *
     * If the structure is receiving item attributes, this member is the Pointer to the buffer that
     * receives the item text.
     */
    LPWSTR pszText;
    /**
     * Size of the buffer pointed to by the pszText member. If the structure is not receiving
     * information, this member is ignored.
     */
    int cchTextMax;
    /**
     * Index of the list view item's icon in the icon list and the small icon image list.
     *
     * If this member is the I_IMAGECALLBACK value, the parent window is responsible for storing the
     * index. In this case, the list view control sends the parent an LVN_GETDISPINFO notification
     * message to get the index when it needs to display the image.
     */
    int iImage;
    /**
     * Specifies the 32-bit value of the item. If you use the LVM_SORTITEMS message, the list view
     * control passes this value to the application-defined comparison function. You can also use the
     * LVM_FINDITEM message to search a list view control for an item with a specified lParam value.
     */
    LPARAM lParam;
#if (_WIN32_IE >= 0x0300)
    /**
     * Number of image widths to indent the item. A single indentation equals the width of an item
     * image. Therefore, the value 1 indents the item by the width of one image, the value 2 indents by
     * two images, and so on. Note that this member is supported only for items. Attempting to set
     * subitem indentation will cause the calling function to fail.
     */
    int iIndent;
#endif
} LVITEMW, FAR* LPLVITEMW;


#ifdef UNICODE
#define LVITEM    LVITEMW
#define LPLVITEM  LPLVITEMW
#else
#define LVITEM    LVITEMA
#define LPLVITEM  LPLVITEMA
#endif


#define LPSTR_TEXTCALLBACKW     ((LPWSTR)-1L)
#define LPSTR_TEXTCALLBACKA     ((LPSTR)-1L)
#ifdef UNICODE
#define LPSTR_TEXTCALLBACK      LPSTR_TEXTCALLBACKW
#else
#define LPSTR_TEXTCALLBACK      LPSTR_TEXTCALLBACKA
#endif

#define I_IMAGECALLBACK         (-1)

#define LVM_GETITEMA            (LVM_FIRST + 5)
#define LVM_GETITEMW            (LVM_FIRST + 75)
#ifdef UNICODE
/**
 * This message retrieves some or all of a list view item's attributes. You can send this message
 * explicitly or by using the ListView_GetItem macro.
 *
 * @param pitem Pointer to an LVITEM structure that specifies the data to retrieve and receives data
 *   about the list view item. When the message is sent, the iItem and iSubItem members identify the
 *   item or subitem to retrieve data about, and the mask member specifies which attributes to
 *   retrieve. For a list of possible values, see the description of the LVITEM structure. If the mask
 *   member specifies the LVIF_TEXT value, the pszText member must contain the address of the buffer
 *   that receives the item text, and the cchTextMax member must specify the size of the buffer. If
 *   the mask member specifies the LVIF_STATE value, the stateMask member must specify the item state
 *   bits to retrieve. On output, the state member contains the values of the specified state bits.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define LVM_GETITEM             LVM_GETITEMW
#else
/**
 * This message retrieves some or all of a list view item's attributes. You can send this message
 * explicitly or by using the ListView_GetItem macro.
 *
 * @param pitem Pointer to an LVITEM structure that specifies the data to retrieve and receives data
 *   about the list view item. When the message is sent, the iItem and iSubItem members identify the
 *   item or subitem to retrieve data about, and the mask member specifies which attributes to
 *   retrieve. For a list of possible values, see the description of the LVITEM structure. If the mask
 *   member specifies the LVIF_TEXT value, the pszText member must contain the address of the buffer
 *   that receives the item text, and the cchTextMax member must specify the size of the buffer. If
 *   the mask member specifies the LVIF_STATE value, the stateMask member must specify the item state
 *   bits to retrieve. On output, the state member contains the values of the specified state bits.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define LVM_GETITEM             LVM_GETITEMA
#endif

/**
 * This macro retrieves some or all of a list view item's attributes. You can use this macro or send
 * the LVM_GETITEM message explicitly.
 *
 * @param hwnd Handle to the list view control.
 * @param pitem Pointer to an LVITEM structure that specifies the information to retrieve and
 *   receives information about the list view item. When the LVM_GETITEM message is sent, the iItem
 *   and iSubItem members identify the item or subitem to retrieve information about and the mask
 *   member specifies which attributes to retrieve. For a list of possible values, see the description
 *   of the LVITEM structure. If the mask member specifies the LVIF_TEXT value, the pszText member
 *   must contain the address of the buffer that receives the item text, and the cchTextMax member
 *   must specify the size of the buffer. If the mask member specifies the LVIF_STATE value, the
 *   stateMask member must specify the item state bits to retrieve. On output, the state member
 *   contains the values of the specified state bits.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define ListView_GetItem(hwnd, pitem) \
    (BOOL)SNDMSG((hwnd), LVM_GETITEM, 0, (LPARAM)(LV_ITEM FAR*)(pitem))


#define LVM_SETITEMA            (LVM_FIRST + 6)
#define LVM_SETITEMW            (LVM_FIRST + 76)
#ifdef UNICODE
/**
 * This message sets some or all of a list view item's attributes. You can send this message
 * explicitly or by using the ListView_SetItem macro.
 *
 * @param pitem Pointer to an LVITEM structure that contains the new item attributes. The iItem and
 *   iSubItem members identify the item or subitem, and the mask member specifies which attributes to
 *   set.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * If the mask member specifies the LVIF_TEXT value, the pszText member is the address of a
 * null-terminated string and the cchTextMax member is ignored.
 *
 * If the mask member specifies the LVIF_STATE value, the stateMask member specifies which item
 * states to change and the state member contains the values for those states.
 *
 * To set the attributes of a list view item, set the iItem member of the LVITEM structure to the
 * index of the item, and set the iSubItem member to zero. For an item, you can set the state,
 * pszText, iImage, and lParam members of the LVITEM structure.
 */
#define LVM_SETITEM             LVM_SETITEMW
#else
/**
 * This message sets some or all of a list view item's attributes. You can send this message
 * explicitly or by using the ListView_SetItem macro.
 *
 * @param pitem Pointer to an LVITEM structure that contains the new item attributes. The iItem and
 *   iSubItem members identify the item or subitem, and the mask member specifies which attributes to
 *   set.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * If the mask member specifies the LVIF_TEXT value, the pszText member is the address of a
 * null-terminated string and the cchTextMax member is ignored.
 *
 * If the mask member specifies the LVIF_STATE value, the stateMask member specifies which item
 * states to change and the state member contains the values for those states.
 *
 * To set the attributes of a list view item, set the iItem member of the LVITEM structure to the
 * index of the item, and set the iSubItem member to zero. For an item, you can set the state,
 * pszText, iImage, and lParam members of the LVITEM structure.
 */
#define LVM_SETITEM             LVM_SETITEMA
#endif

/**
 * This macro sets some or all of a list view item's attributes. You can also use ListView_SetItem
 * to set the text of a subitem. You can use this macro or send the LVM_SETITEM message explicitly.
 *
 * @param hwnd Handle to the list view control.
 * @param pitem Pointer to an LVITEM structure that contains the new item attributes. The iItem and
 *   iSubItem members identify the item or subitem, and the mask member specifies which attributes to
 *   set. If the mask member specifies the LVIF_TEXT value, the pszText member is the address of a
 *   null-terminated string and the cchTextMax member is ignored. If the mask member specifies the
 *   LVIF_STATE value, the stateMask member specifies which item states to change, and the state
 *   member contains the values for those states.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * To set the attributes of a list view item, set the iItem member of the LVITEM structure to the
 * index of the item, and set the iSubItem member to zero. For an item, you can use the state,
 * pszText, iImage, and lParam members of the LVITEM structure to modify these item parameters.
 *
 * To set the text of a subitem, set the iItem and iSubItem members to indicate the specific
 * subitem, and use the pszText member to specify the text. Alternatively, you can use the
 * ListView_SetItemText macro to set the text of a subitem. You cannot set the state or lParam
 * members for subitems because subitems do not have these attributes. In version 4.70 and later,
 * you can set the iImage member for subitems. The subitem image will be displayed if the list view
 * control has the LVS_EX_SUBITEMIMAGES extended style. Previous versions will ignore the subitem
 * image.
 */
#define ListView_SetItem(hwnd, pitem) \
    (BOOL)SNDMSG((hwnd), LVM_SETITEM, 0, (LPARAM)(const LV_ITEM FAR*)(pitem))


#define LVM_INSERTITEMA         (LVM_FIRST + 7)
#define LVM_INSERTITEMW         (LVM_FIRST + 77)
#ifdef UNICODE
/**
 * This message inserts a new item in a list view control. You can send this message explicitly or
 * by using the ListView_InsertItem macro.
 *
 * @param pitem Pointer to an LVITEM structure that specifies the attributes of the list view item.
 *   The iItem member specifies the index of the new item. You cannot use ListView_InsertItem or
 *   LVM_INSERTITEM to insert subitems; the iSubItem member of the LVITEM structure must be zero.
 *
 * @return The index of the new item indicates success. -1 indicates failure.
 */
#define LVM_INSERTITEM          LVM_INSERTITEMW
#else
/**
 * This message inserts a new item in a list view control. You can send this message explicitly or
 * by using the ListView_InsertItem macro.
 *
 * @param pitem Pointer to an LVITEM structure that specifies the attributes of the list view item.
 *   The iItem member specifies the index of the new item. You cannot use ListView_InsertItem or
 *   LVM_INSERTITEM to insert subitems; the iSubItem member of the LVITEM structure must be zero.
 *
 * @return The index of the new item indicates success. -1 indicates failure.
 */
#define LVM_INSERTITEM          LVM_INSERTITEMA
#endif
/**
 * This macro inserts a new item in a list view control. You can use this macro or send the
 * LVM_INSERTITEM message explicitly.
 *
 * @param hwnd Handle to the list view control.
 * @param pitem Pointer to an LVITEM structure that specifies the attributes of the list view item.
 *   The iItem member of the structure specifies the index of the new item. You cannot use
 *   ListView_InsertItem or LVM_INSERTITEM to insert subitems; the iSubItem member of the LVITEM
 *   structure must be zero.
 *
 * @return The index of the new item indicates success. -1 indicates failure.
 *
 * If a list view control has either the LVS_SORTASCENDING or LVS_SORTDESCENDING window style, an
 * LVM_INNSETITEM message will fail if you try to insert an item that has LPSTR_TEXTCALLBACK as the
 * pszText member of its LVITEM structure.
 */
#define ListView_InsertItem(hwnd, pitem)   \
    (int)SNDMSG((hwnd), LVM_INSERTITEM, 0, (LPARAM)(const LV_ITEM FAR*)(pitem))


/**
 * This message removes an item from a list view control. You can send this message explicitly or by
 * using the ListView_DeleteItem macro.
 *
 * @param iItem Index of the list view item to delete.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define LVM_DELETEITEM          (LVM_FIRST + 8)
/**
 * This macro removes an item from a list view control. You can use this macro or send the
 * LVM_DELETEITEM message explicitly.
 *
 * @param hwnd Handle to the list view control.
 * @param iItem Index of the list view item to delete.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define ListView_DeleteItem(hwnd, i) \
    (BOOL)SNDMSG((hwnd), LVM_DELETEITEM, (WPARAM)(int)(i), 0L)


/**
 * This message removes all items from a list view control. You can send this message explicitly or
 * by using the ListView_DeleteAllItems macro.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define LVM_DELETEALLITEMS      (LVM_FIRST + 9)
/**
 * This macro removes all items from a list view control. You can use this macro or send the
 * LVM_DELETEALLITEMS message explicitly.
 *
 * @param hwnd Handle to the list view control.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * When a list view control receives the LVM_DELETEALLITEMS message, it sends the LVN_DELETEALLITEMS
 * notification message to its parent window.
 */
#define ListView_DeleteAllItems(hwnd) \
    (BOOL)SNDMSG((hwnd), LVM_DELETEALLITEMS, 0, 0L)


/**
 * This message retrieves the callback mask for a list view control. You can send this message
 * explicitly or by using the ListView_GetCallbackMask macro.
 *
 * @return The callback mask indicates success.
 */
#define LVM_GETCALLBACKMASK     (LVM_FIRST + 10)
/**
 * This macro retrieves the callback mask for a list view control. You can use this macro or send
 * the LVM_GETCALLBACKMASK message explicitly.
 *
 * @param hwnd Handle to the list view control.
 *
 * @return Returns the callback mask.
 */
#define ListView_GetCallbackMask(hwnd) \
    (BOOL)SNDMSG((hwnd), LVM_GETCALLBACKMASK, 0, 0)


/**
 * This message sets the callback mask for a list view control. You can send this message explicitly
 * or by using the ListView_SetCallbackMask macro.
 *
 * @param mask Value of the callback mask. The bits of the mask indicate the item states or images
 *   for which the application stores the current state data. It can be any combination of the
 *   following constants: Constant Description LVIS_CUT The item is marked for a cut-and-paste
 *   operation. LVIS_DROPHILITED The item is highlighted as a drag-and-drop target. LVIS_FOCUSED The
 *   item has the focus. LVIS_SELECTED The item is selected. LVIS_OVERLAYMASK The application stores
 *   the image list index of the current overlay image for each item. LVIS_STATEIMAGEMASK The
 *   application stores the image list index of the current state image for each item. The callback
 *   mask of a list view control is a set of bit flags that specify the item states for which the
 *   application, rather than the control, stores the current data. The callback mask applies to all
 *   of the control items, unlike the callback item designation, which applies to a specific item. The
 *   callback mask is zero by default, meaning that the list view control stores all item state data.
 *   After creating a list view control and initializing its items, you can send the
 *   LVM_SETCALLBACKMASK message to change the callback mask. To get the current callback mask, send
 *   the LVM_GETCALLBACKMASK message. For more information about overlay images and state images, see
 *   List View Image Lists. For more information on overlay images, state images, and list view
 *   callbacks, see the Windows CE User Interface Services Guide.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define LVM_SETCALLBACKMASK     (LVM_FIRST + 11)
/**
 * This macro changes the callback mask for a list view control. You can use this macro or send the
 * LVM_SETCALLBACKMASK message explicitly.
 *
 * @param hwnd Handle to the list view control.
 * @param mask Value of the callback mask. The bits of the mask indicate the item states or images
 *   for which the application stores the current state data. It can be any combination of the
 *   following constants: Value Description LVIS_CUT The item is marked for a cut-and-paste operation.
 *   LVIS_DROPHILITED The item is highlighted as a drag-and-drop target. LVIS_FOCUSED The item has the
 *   focus. LVIS_SELECTED The item is selected. LVIS_OVERLAYMASK The application stores the image list
 *   index of the current overlay image for each item. LVIS_STATEIMAGEMASK The application stores the
 *   image list index of the current state image for each item.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * The callback mask of a list view control is a set of bit flags that specify the item states for
 * which the application, rather than the control, stores the current data. The callback mask
 * applies to all of the control's items, unlike the callback item designation, which applies to a
 * specific item. The callback mask is zero by default, meaning that the list view control stores
 * all item state information. After creating a list view control and initializing its items, you
 * can use the ListView_SetCallbackMask macro or LVM_SETCALLBACKMASK message to change the callback
 * mask. To get the current callback mask, send the LVM_GETCALLBACKMASK message.
 */
#define ListView_SetCallbackMask(hwnd, mask) \
    (BOOL)SNDMSG((hwnd), LVM_SETCALLBACKMASK, (WPARAM)(UINT)(mask), 0)


#define LVNI_ALL                0x0000
#define LVNI_FOCUSED            0x0001
#define LVNI_SELECTED           0x0002
#define LVNI_CUT                0x0004
#define LVNI_DROPHILITED        0x0008

#define LVNI_ABOVE              0x0100
#define LVNI_BELOW              0x0200
#define LVNI_TOLEFT             0x0400
#define LVNI_TORIGHT            0x0800


/**
 * This message searches for a list view item that has the specified properties and bears the
 * specified relationship to a specified item. You can send this message explicitly or by using the
 * ListView_GetNextItem macro.
 *
 * @param iStart Index of the item to begin the search with, or -1 to find the first item that
 *   matches the specified flags. The specified item itself is excluded from the search.
 * @param flags Specifies the relationship to the item specified in iStart. This is the following
 *   value: Value Description LVNI_ALL Searches for a subsequent item by index (the default value).
 *   The physical relationship to iStart is specified with one of the following values: Value
 *   Description LVNI_ABOVE Searches for an item that is above the specified item. LVNI_BELOW Searches
 *   for an item that is below the specified item. LVNI_TOLEFT Searches for an item to the left of the
 *   specified item. LVNI_TORIGHT Searches for an item to the right of the specified item. The state
 *   of the item to find is specified with one or a combination of the following values: Value
 *   Description LVNI_CUT The item has the LVIS_CUT state flag set. LVNI_DROPHILITED The item has the
 *   LVIS_DROPHILITED state flag set. LVNI_FOCUSED The item has the LVIS_FOCUSED state flag set.
 *   LVNI_SELECTED The item has the LVIS_SELECTED state flag set. If an item does not have all of the
 *   specified state flags set, the search continues with the next item.
 *
 * @return The index of the next item indicates success. -1 indicates failure.
 */
#define LVM_GETNEXTITEM         (LVM_FIRST + 12)
/**
 * This macro searches for a list view item that has the specified properties and bears the
 * specified relationship to a specified item. You can use this macro or send the LVM_GETNEXTITEM
 * message explicitly.
 *
 * @param hwnd Handle to the list view control.
 * @param iStart Index of the item with which to begin the search, or -1 to find the first item that
 *   matches the specified flags. The specified item itself is excluded from the search.
 * @param flags Geometric relation of the requested item to the specified item and, if specified,
 *   the state of the requested item. For a list of possible values, see the description of the flags
 *   parameter in the LVM_GETNEXTITEM message. If an item does not have all of the specified state
 *   flags set, the search continues with the next item.
 *
 * @return The index of the next item indicates success. -1 indicates failure.
 */
#define ListView_GetNextItem(hwnd, i, flags) \
    (int)SNDMSG((hwnd), LVM_GETNEXTITEM, (WPARAM)(int)(i), MAKELPARAM((flags), 0))


#define LVFI_PARAM              0x0001
#define LVFI_STRING             0x0002
#define LVFI_PARTIAL            0x0008
#define LVFI_WRAP               0x0020
#define LVFI_NEARESTXY          0x0040

#if (_WIN32_IE >= 0x0300)
#define LV_FINDINFOA    LVFINDINFOA
#define LV_FINDINFOW    LVFINDINFOW
#else
#define tagLVFINDINFOA  _LV_FINDINFOA
#define    LVFINDINFOA   LV_FINDINFOA
#define tagLVFINDINFOW  _LV_FINDINFOW
#define    LVFINDINFOW   LV_FINDINFOW
#endif

#define LV_FINDINFO  LVFINDINFO

/**
 * This structure that contains information used to search for a list view item.
 *
 * This structure supersedes the LV_FINDINFO structure.
 */
typedef struct tagLVFINDINFOA
{
    /**
     * Specifies the type of search to perform. It can be one or more of the following values: Value
     * Description LVFI_PARAM Searches based on the lParam member. The lParam member of the matching
     * item's LVITEM structure must match the lParam member of this structure. If this value is
     * specified, all other values are ignored. LVFI_PARTIAL Matches if the item text begins with the
     * string pointed to by the psz member. This value implies use of LVFI_STRING. LVFI_STRING Searches
     * based on the item text. Unless additional values are specified, the item text of the matching
     * item must exactly match the string pointed to by the psz member. LVFI_WRAP Continues the search
     * at the beginning if no match is found. LVFI_NEARESTXY Finds the item nearest to the position
     * specified in the pt member, in the direction specified by the vkDirection member.
     */
    UINT flags;
    /**
     * Pointer to a null-terminated string to compare with the item text if flags specifies LVFI_STRING
     * or LVFI_PARTIAL.
     */
    LPCSTR psz;
    /**
     * Value to compare with the lParam member of a list view item's LVITEM structure if the flags
     * member specifies LVFI_PARAM.
     */
    LPARAM lParam;
    /**
     * POINT structure that specifies the starting position to search from. This member is used only if
     * LVFI_NEARESTXY is specified in the flags member.
     */
    POINT pt;
    /**
     * Specifies the direction to search in by containing the virtual-key code of an arrow key that
     * specified the direction to search in. This member is used only if LVFI_NEARESTXY is specified in
     * the flags member.
     */
    UINT vkDirection;
} LVFINDINFOA, FAR* LPFINDINFOA;

/**
 * This structure that contains information used to search for a list view item.
 *
 * This structure supersedes the LV_FINDINFO structure.
 */
typedef struct tagLVFINDINFOW
{
    /**
     * Specifies the type of search to perform. It can be one or more of the following values: Value
     * Description LVFI_PARAM Searches based on the lParam member. The lParam member of the matching
     * item's LVITEM structure must match the lParam member of this structure. If this value is
     * specified, all other values are ignored. LVFI_PARTIAL Matches if the item text begins with the
     * string pointed to by the psz member. This value implies use of LVFI_STRING. LVFI_STRING Searches
     * based on the item text. Unless additional values are specified, the item text of the matching
     * item must exactly match the string pointed to by the psz member. LVFI_WRAP Continues the search
     * at the beginning if no match is found. LVFI_NEARESTXY Finds the item nearest to the position
     * specified in the pt member, in the direction specified by the vkDirection member.
     */
    UINT flags;
    /**
     * Pointer to a null-terminated string to compare with the item text if flags specifies LVFI_STRING
     * or LVFI_PARTIAL.
     */
    LPCWSTR psz;
    /**
     * Value to compare with the lParam member of a list view item's LVITEM structure if the flags
     * member specifies LVFI_PARAM.
     */
    LPARAM lParam;
    /**
     * POINT structure that specifies the starting position to search from. This member is used only if
     * LVFI_NEARESTXY is specified in the flags member.
     */
    POINT pt;
    /**
     * Specifies the direction to search in by containing the virtual-key code of an arrow key that
     * specified the direction to search in. This member is used only if LVFI_NEARESTXY is specified in
     * the flags member.
     */
    UINT vkDirection;
} LVFINDINFOW, FAR* LPFINDINFOW;

#ifdef UNICODE
#define  LVFINDINFO            LVFINDINFOW
#else
#define  LVFINDINFO            LVFINDINFOA
#endif

#define LVM_FINDITEMA           (LVM_FIRST + 13)
#define LVM_FINDITEMW           (LVM_FIRST + 83)
#ifdef UNICODE
/**
 * This message searches for a list view item with the specified characteristics. You can send this
 * message explicitly or by using the ListView_FindItem macro.
 *
 * @param iStart Index of the item to begin the search with or -1 to start from the beginning. The
 *   specified item is itself excluded from the search.
 * @param plvfi Pointer to an LVFINDINFO structure that contains data about what to search for.
 *
 * @return The index of the item indicates success. -1 indicates failure.
 */
#define  LVM_FINDITEM           LVM_FINDITEMW
#else
/**
 * This message searches for a list view item with the specified characteristics. You can send this
 * message explicitly or by using the ListView_FindItem macro.
 *
 * @param iStart Index of the item to begin the search with or -1 to start from the beginning. The
 *   specified item is itself excluded from the search.
 * @param plvfi Pointer to an LVFINDINFO structure that contains data about what to search for.
 *
 * @return The index of the item indicates success. -1 indicates failure.
 */
#define  LVM_FINDITEM           LVM_FINDITEMA
#endif

/**
 * This macro searches for a list view item with the specified characteristics. You can use this
 * macro or send the LVM_FINDITEM message explicitly.
 *
 * @param hwnd Handle to the list view control.
 * @param iStart Index of the item after which to begin the search, or -1 to start from the
 *   beginning.
 * @param plvfi Pointer to an LVFINDINFO structure that contains information about what to search
 *   for.
 *
 * @return The index of the item indicates success. -1 indicates failure.
 */
#define ListView_FindItem(hwnd, iStart, plvfi) \
    (int)SNDMSG((hwnd), LVM_FINDITEM, (WPARAM)(int)(iStart), (LPARAM)(const LV_FINDINFO FAR*)(plvfi))

#define LVIR_BOUNDS             0
#define LVIR_ICON               1
#define LVIR_LABEL              2
#define LVIR_SELECTBOUNDS       3


/**
 * This message retrieves the bounding rectangle for all or part of an item in the current view. You
 * can send this message explicitly or by using the ListView_GetItemRect macro.
 *
 * @param i Index of the list view item.
 * @param prc Pointer to a RECT structure that receives the bounding rectangle. When the message is
 *   sent, the left member of this structure is used to determine the portion of the list view item
 *   for which to retrieve the bounding rectangle. This will be one of the code values defined in
 *   ListView_GetItemRect.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define LVM_GETITEMRECT         (LVM_FIRST + 14)
/**
 * This macro retrieves the bounding rectangle for all or part of an item in the current view. You
 * can use this macro or send the LVM_GETITEMRECT message explicitly.
 *
 * @param hwnd Handle to the list view control.
 * @param i Index of the list view item.
 * @param prc Pointer to a RECT structure that receives the bounding rectangle. When the
 *   LVM_GETITEMRECT message is sent, the left member of this structure contains the value of the code
 *   parameter.
 * @param code Portion of the list view item for which to retrieve the bounding rectangle. It is one
 *   of the following values: Value Description LVIR_BOUNDS Returns the bounding rectangle of the
 *   entire item, including the icon and label. LVIR_ICON Returns the bounding rectangle of the icon
 *   or small icon. LVIR_LABEL Returns the bounding rectangle of the item text. LVIR_SELECTBOUNDS
 *   Returns the union of the LVIR_ICON and LVIR_LABEL rectangles, but excludes columns in details
 *   view.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define ListView_GetItemRect(hwnd, i, prc, code) \
     (BOOL)SNDMSG((hwnd), LVM_GETITEMRECT, (WPARAM)(int)(i), \
           ((prc) ? (((RECT FAR *)(prc))->left = (code),(LPARAM)(RECT FAR*)(prc)) : (LPARAM)(RECT FAR*)NULL))


/**
 * This message moves an item to a specified position in a list view control, which must be in icon
 * or small icon view. You can send this message explicitly or by using the ListView_SetItemPosition
 * macro.
 *
 * @param i Index of the list view item
 * @param x and y Specifies the new position of the item's upper-left corner, in view coordinates
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define LVM_SETITEMPOSITION     (LVM_FIRST + 15)
/**
 * This macro moves an item to a specified position in a list view control, which must be in icon or
 * small icon view. You can use this macro or send the LVM_SETITEMPOSITION message explicitly.
 *
 * @param hwnd Handle to the list view control.
 * @param i Index of the list view item.
 * @param x and y New position of the item's upper-left corner, in view coordinates.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * If the list view control has the LVS_AUTOARRANGE style, the list view control is arranged after
 * the position of the item is set.
 */
#define ListView_SetItemPosition(hwndLV, i, x, y) \
    (BOOL)SNDMSG((hwndLV), LVM_SETITEMPOSITION, (WPARAM)(int)(i), MAKELPARAM((x), (y)))


/**
 * This message retrieves the position of a list view item. You can send this message explicitly or
 * by using the ListView_GetItemPosition macro.
 *
 * @param i Index of the list view item.
 * @param ppt Pointer to a POINT structure that receives the position of the item's upper-left
 *   corner, in view coordinates.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define LVM_GETITEMPOSITION     (LVM_FIRST + 16)
/**
 * This macro retrieves the position of a list view item. You can use this macro or send the
 * LVM_GETITEMPOSITION message explicitly.
 *
 * @param hwnd Handle to the list view control.
 * @param i Index of the list view item.
 * @param ppt Pointer to a POINT structure that receives the position of the item's upper-left
 *   corner, in view coordinates.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define ListView_GetItemPosition(hwndLV, i, ppt) \
    (BOOL)SNDMSG((hwndLV), LVM_GETITEMPOSITION, (WPARAM)(int)(i), (LPARAM)(POINT FAR*)(ppt))


#define LVM_GETSTRINGWIDTHA     (LVM_FIRST + 17)
#define LVM_GETSTRINGWIDTHW     (LVM_FIRST + 87)
#ifdef UNICODE
/**
 * This message determines the width of a specified string, using the specified list view control's
 * current font. You can send this message explicitly or by using the ListView_GetStringWidth macro.
 *
 * @param psz Pointer to a null-terminated string
 *
 * @return The string width indicates success. Zero indicates failure.
 */
#define  LVM_GETSTRINGWIDTH     LVM_GETSTRINGWIDTHW
#else
/**
 * This message determines the width of a specified string, using the specified list view control's
 * current font. You can send this message explicitly or by using the ListView_GetStringWidth macro.
 *
 * @param psz Pointer to a null-terminated string
 *
 * @return The string width indicates success. Zero indicates failure.
 */
#define  LVM_GETSTRINGWIDTH     LVM_GETSTRINGWIDTHA
#endif

/**
 * This macro determines the width of a specified string, using the specified list view control's
 * current font. You can use this macro or send the LVM_GETSTRINGWIDTH message explicitly.
 *
 * @param hwnd Handle to the list view control.
 * @param psz Pointer to a null-terminated string.
 *
 * @return The string width indicates success. Zero indicates failure.
 *
 * The ListView_GetStringWidth macro returns the exact width, in pixels, of the specified string. If
 * you use the returned string width as the column width in a call to the ListView_SetColumnWidth
 * macro, the string will be truncated. To get the column width that can contain the string without
 * truncating it, you must add padding to the returned string width.
 */
#define ListView_GetStringWidth(hwndLV, psz) \
    (int)SNDMSG((hwndLV), LVM_GETSTRINGWIDTH, 0, (LPARAM)(LPCTSTR)(psz))


#define LVHT_NOWHERE            0x0001
#define LVHT_ONITEMICON         0x0002
#define LVHT_ONITEMLABEL        0x0004
#define LVHT_ONITEMSTATEICON    0x0008
#define LVHT_ONITEM             (LVHT_ONITEMICON | LVHT_ONITEMLABEL | LVHT_ONITEMSTATEICON)

#define LVHT_ABOVE              0x0008
#define LVHT_BELOW              0x0010
#define LVHT_TORIGHT            0x0020
#define LVHT_TOLEFT             0x0040

#if (_WIN32_IE >= 0x0300)
#define LV_HITTESTINFO LVHITTESTINFO
#else
#define tagLVHITTESTINFO  _LV_HITTESTINFO
#define    LVHITTESTINFO   LV_HITTESTINFO
#endif

/**
 * This structure has been extended to accommodate subitem hit-testing. The LVHITTESTINFO structure
 * contains information about a hit test. It is used in association with the LVM_HITTEST and
 * LVM_SUBITEMHITTEST messages and their related macros.
 *
 * This structure supersedes the LV_HITTESTINFO structure.
 */
typedef struct tagLVHITTESTINFO
{
    /**
     * Position to hit test, in client coordinates.
     */
    POINT pt;
    /**
     * Receives information about the results of a hit test. It can be one or more of the following
     * values. Value Description LVHT_ABOVE The position is above the control's client area. LVHT_BELOW
     * The position is below the control's client area. LVHT_NOWHERE The position is inside the list
     * view control's client window, but it is not over a list item. LVHT_ONITEMICON The position is
     * over a list view item's icon. LVHT_ONITEMLABEL The position is over a list view item's text.
     * LVHT_ONITEMSTATEICON The position is over the state image of a list view item. LVHT_TOLEFT The
     * position is to the left of the list view control's client area. LVHT_TORIGHT The position is to
     * the right of the list view control's client area.
     *
     * You can use LVHT_ABOVE, LVHT_BELOW, LVHT_TOLEFT, and LVHT_TORIGHT to determine whether to scroll
     * the contents of a list view control. Two of these values may be combined. For example, if the
     * position is above and to the left of the client area, you could use both LVHT_ABOVE and LVHT_TO
     * LEFT.
     *
     * You can test for LVHT_ONITEM to determine whether a specified position is over a list view item.
     * This value is a bitwise-OR operation on LVHT_ONITEMICON, LVHT_ONITEMLABEL, and
     * LVHT_ONITEMSTATEICON.
     */
    UINT flags;
    /**
     * Receives the index of the matching item. Or if hit-testing a subitem, this value represents the
     * subitem's parent item.
     */
    int iItem;
#if (_WIN32_IE >= 0x0300)
    /**
     * Receives the index of the matching subitem. When hit-testing an item, this member will be zero.
     */
    int iSubItem;    // this is was NOT in win95.  valid only for LVM_SUBITEMHITTEST
#endif
} LVHITTESTINFO, FAR* LPLVHITTESTINFO;

/**
 * This message determines which list view item, if any, is at a specified position. You can send
 * this message explicitly or by using the ListView_HitTest macro.
 *
 * @param pinfo Pointer to an LVHITTESTINFO structure that contains the position to hit test and
 *   receives hit test result data.
 *
 * @return The index of the item at the specified position, if any, indicates success. -1 indicates
 *   failure.
 */
#define LVM_HITTEST             (LVM_FIRST + 18)
/**
 * This macro determines which list view item, if any, is at a specified position. You can use this
 * macro or send the LVM_HITTEST message explicitly.
 *
 * @param hwnd Handle to the list view control.
 * @param pinfo Pointer to an LVHITTESTINFO structure that contains the position to hit test and
 *   receives information about the results of the hit test.
 *
 * @return The index of the item at the specified position, if any, indicates success. -1 indicates
 *   failure.
 */
#define ListView_HitTest(hwndLV, pinfo) \
    (int)SNDMSG((hwndLV), LVM_HITTEST, 0, (LPARAM)(LV_HITTESTINFO FAR*)(pinfo))


/**
 * This message ensures that a list view item is entirely or at least partially visible, scrolling
 * the list view control if necessary. You can send this message explicitly or by using the
 * ListView_EnsureVisible macro.
 *
 * @param i Index of the list view item.
 * @param fPartialOK Boolean that specifies whether the item must be entirely visible. If set to
 *   TRUE, no scrolling occurs if the item is at least partially visible.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define LVM_ENSUREVISIBLE       (LVM_FIRST + 19)
/**
 * This macro ensures that a list view item is either entirely or partially visible, scrolling the
 * list view control if necessary. You can use this macro or send the LVM_ENSUREVISIBLE message
 * explicitly.
 *
 * @param hwnd Handle to the list view control.
 * @param i Index of the list view item.
 * @param fPartialOK Boolean value that specifies whether the item must be entirely visible. If set
 *   to TRUE, no scrolling occurs if the item is at least partially visible.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define ListView_EnsureVisible(hwndLV, i, fPartialOK) \
    (BOOL)SNDMSG((hwndLV), LVM_ENSUREVISIBLE, (WPARAM)(int)(i), MAKELPARAM((fPartialOK), 0))


/**
 * This message scrolls the content of a list view control. You can send this message explicitly or
 * by using the ListView_Scroll macro.
 *
 * @param dx Specifies the amount of horizontal scrolling in pixels. If the list view control is in
 *   list view, this value specifies the number of columns to scroll.
 * @param dy Specifies the amount of vertical scrolling in pixels
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define LVM_SCROLL              (LVM_FIRST + 20)
/**
 * This macro scrolls the content of a list view control. You can use this macro or send the
 * LVM_SCROLL message explicitly.
 *
 * @param hwnd Handle to the list view control.
 * @param dx Specifies the amount of horizontal scrolling in pixels. If the list view control is in
 *   list view, this value specifies the number of columns to scroll.
 * @param dy Specifies the amount of vertical scrolling in pixels.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * When the list view control is in report view, the control can only be scrolled vertically in
 * whole line increments. Therefore, the dy parameter will be rounded to the nearest number of
 * pixels that form a whole line increment. For example, if the height of a line is 16 pixels and 8
 * is passed for dy, the list will be scrolled by 16 pixels (1 line). If 7 is passed for dy, the
 * list will be scrolled 0 pixels (0 lines).
 */
#define ListView_Scroll(hwndLV, dx, dy) \
    (BOOL)SNDMSG((hwndLV), LVM_SCROLL, (WPARAM)(int)dx, (LPARAM)(int)dy)


/**
 * This message forces a list view control to redraw a range of items. You can send this message
 * explicitly or by using the ListView_RedrawItems macro.
 *
 * @param iFirst Index of the first item to redraw
 * @param iLast Index of the last item to redraw
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define LVM_REDRAWITEMS         (LVM_FIRST + 21)
/**
 * This macro forces a list view control to redraw a range of items. You can use this macro or send
 * the LVM_REDRAWITEMS message explicitly.
 *
 * @param hwnd Handle to the list view control.
 * @param iFirst Index of the first item to redraw.
 * @param iLast Index of the last item to redraw.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * The specified items are not actually redrawn until the list view window receives a WM_PAINT
 * message to repaint. To repaint immediately, call the UpdateWindow function after using this
 * macro.
 */
#define ListView_RedrawItems(hwndLV, iFirst, iLast) \
    (BOOL)SNDMSG((hwndLV), LVM_REDRAWITEMS, (WPARAM)(int)iFirst, (LPARAM)(int)iLast)


#define LVA_DEFAULT             0x0000
#define LVA_ALIGNLEFT           0x0001
#define LVA_ALIGNTOP            0x0002
#define LVA_SNAPTOGRID          0x0005


/**
 * This message arranges items in icon view. You can send this message explicitly or by using the
 * ListView_Arrange macro.
 *
 * @param code Specifies alignment. It is one of the following values: Value Description
 *   LVA_ALIGNLEFT Not supported. LVA_ALIGNTOP Not supported. LVA_DEFAULT Aligns items according to
 *   the list view control current alignment styles (the default value). LVA_SNAPTOGRID Snaps all
 *   icons to the nearest grid position.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define LVM_ARRANGE             (LVM_FIRST + 22)
/**
 * This macro arranges items in icon view. You can use this macro or send the LVM_ARRANGE message
 * explicitly.
 *
 * @param hwnd Handle to the list view control.
 * @param code Specifies alignment. It is one of the following values: Value Description
 *   LVA_ALIGNLEFT Aligns items along the left edge of the window. LVA_ALIGNTOP Aligns items along the
 *   top edge of the window. LVA_DEFAULT Aligns items according to the list view control's current
 *   alignment styles (the default value). LVA_SNAPTOGRID Snaps all icons to the nearest grid
 *   position.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define ListView_Arrange(hwndLV, code) \
    (BOOL)SNDMSG((hwndLV), LVM_ARRANGE, (WPARAM)(UINT)(code), 0L)


#define LVM_EDITLABELA          (LVM_FIRST + 23)
#define LVM_EDITLABELW          (LVM_FIRST + 118)
#ifdef UNICODE
/**
 * This message begins in-place editing of the specified list view item's text. The message
 * implicitly selects and focuses the specified item. You can send this message explicitly or by
 * using the ListView_EditLabel macro.
 *
 * @param iItem Index of the list view item. To cancel editing, set iItem to -1.
 *
 * @return The handle to the edit control that is used to edit the item text indicates success. NULL
 *   indicates otherwise.
 *
 * When the user completes or cancels editing, the edit control is destroyed and the handle is no
 * longer valid. You can safely subclass the edit control, but you should not destroy it.
 *
 * The control must have the focus before you send this message to the control. Focus can be set
 * using the SetFocus function.
 */
#define LVM_EDITLABEL           LVM_EDITLABELW
#else
/**
 * This message begins in-place editing of the specified list view item's text. The message
 * implicitly selects and focuses the specified item. You can send this message explicitly or by
 * using the ListView_EditLabel macro.
 *
 * @param iItem Index of the list view item. To cancel editing, set iItem to -1.
 *
 * @return The handle to the edit control that is used to edit the item text indicates success. NULL
 *   indicates otherwise.
 *
 * When the user completes or cancels editing, the edit control is destroyed and the handle is no
 * longer valid. You can safely subclass the edit control, but you should not destroy it.
 *
 * The control must have the focus before you send this message to the control. Focus can be set
 * using the SetFocus function.
 */
#define LVM_EDITLABEL           LVM_EDITLABELA
#endif

/**
 * This macro begins in-place editing of the specified list view item's text. The message implicitly
 * selects and focuses the specified item. You can use this macro or send the LVM_EDITLABEL message
 * explicitly.
 *
 * @param hwnd Handle to the list view control.
 * @param iItem Index of the list view item. To cancel editing, set iItem to -1.
 *
 * @return The handle to the edit control that is used to edit the item text indicates success. NULL
 *   indicates failure.
 *
 * When the user completes or cancels editing, the edit control is destroyed and the handle is no
 * longer valid. You can safely subclass the edit control, but you should not destroy it.
 *
 * The control must have the focus before you send this message to the control. Focus can be set
 * using the SetFocus function.
 */
#define ListView_EditLabel(hwndLV, i) \
    (HWND)SNDMSG((hwndLV), LVM_EDITLABEL, (WPARAM)(int)(i), 0L)


/**
 * This message retrieves the handle of the edit control being used to edit a list view item's text.
 * You can send this message explicitly or by using the ListView_GetEditControl macro.
 *
 * @return The handle to the edit control indicates success. NULL indicates otherwise. If no label
 *   is being edited, the return value is NULL. The edit control is not created until after the
 *   LVN_BEGINLABELEDIT notification message is sent.
 *
 * When the user completes or cancels editing, the edit control is destroyed and the handle is no
 * longer valid. You can safely subclass the edit control, but you should not destroy it. To cancel
 * editing, you can send the list view control a WM_CANCELMODE message.
 */
#define LVM_GETEDITCONTROL      (LVM_FIRST + 24)
/**
 * This macro retrieves the handle to the edit control being used to edit a list view item's text.
 * You can use this macro or send the LVM_GETEDITCONTROL message explicitly.
 *
 * @param hwnd Handle to the list view control.
 *
 * @return The handle to the edit control indicates success. NULL indicates failure.
 *
 * If no label is being edited, the return value is NULL. The edit control is not created until
 * after the LVN_BEGINLABELEDIT notification message is sent.
 *
 * When the user completes or cancels editing, the edit control is destroyed and the handle is no
 * longer valid. You can safely subclass the edit control, but you should not destroy it. To cancel
 * editing, you can send the list view control a WM_CANCELMODE message.
 *
 * The list view item being edited is the currently focused item-that is, the item in the focused
 * state. To find an item based on its state, use the LVM_GETNEXTITEM message.
 */
#define ListView_GetEditControl(hwndLV) \
    (HWND)SNDMSG((hwndLV), LVM_GETEDITCONTROL, 0, 0L)


#if (_WIN32_IE >= 0x0300)
#define LV_COLUMNA      LVCOLUMNA
#define LV_COLUMNW      LVCOLUMNW
#else
#define tagLVCOLUMNA    _LV_COLUMNA
#define    LVCOLUMNA     LV_COLUMNA
#define tagLVCOLUMNW    _LV_COLUMNW
#define    LVCOLUMNW     LV_COLUMNW
#endif

#define LV_COLUMN       LVCOLUMN

/**
 * This structure contains information about a column in report view. This structure is used both
 * for creating columns and manipulating them using messages. The structure was extended to support
 * new mask values. Two new members, iOrder and iImage, were added to support the new mask values.
 *
 * This structure supersedes the LV_COLUMN structure.
 *
 * This structure is used with the LVM_GETCOLUMN, LVM_SETCOLUMN, LVM_INSERTCOLUMN, and
 * LVM_DELETECOLUMN messages.
 */
typedef struct tagLVCOLUMNA
{
    /**
     * Specifies which members contain valid information. It can be zero, or one or more of the
     * following values. Value Description LVCF_FMT The fmt member is valid. LVCF_IMAGE The iImage
     * member is valid. LVCF_ORDER The iOrder member is valid. LVCF_SUBITEM The iSubItem member is
     * valid. LVCF_TEXT The pszText member is valid. LVCF_WIDTH The cx member is valid.
     */
    UINT mask;
    /**
     * Alignment of the column heading and the subitem text in the column. It is one of the following
     * values: Value Description LVCFMT_BITMAP_ON_RIGHT The bitmap appears to the right of text. This
     * does not affect an image from an image list assigned to the header item. LVCFMT_CENTER Text is
     * centered. LVCFMT_IMAGE The item displays an image from an image list. LVCFMT_LEFT Text is
     * left-aligned. LVCFMT_RIGHT Text is right-aligned.
     *
     * The leftmost column in a list view control must be left aligned.
     */
    int fmt;
    /**
     * Width of the column, in pixels.
     */
    int cx;
    /**
     * If column information is being set, this member is the pointer to a null-terminated string that
     * contains the column heading text. If the structure is receiving information about a column, this
     * member specifies the address of the buffer that receives the column heading text.
     */
    LPSTR pszText;
    /**
     * Size of the buffer pointed to by the pszText member. If the structure is not receiving
     * information about a column, this member is ignored.
     */
    int cchTextMax;
    /**
     * Index of subitem associated with the column.
     */
    int iSubItem;
#if (_WIN32_IE >= 0x0300)
    /**
     * Zero-based index of an image within the image list. The specified image will appear within the
     * column.
     */
    int iImage;
    /**
     * Zero-based column offset. Column offset is with left-to-right order. For example, zero indicates
     * the leftmost column.
     */
    int iOrder;
#endif
} LVCOLUMNA, FAR* LPLVCOLUMNA;

/**
 * This structure contains information about a column in report view. This structure is used both
 * for creating columns and manipulating them using messages. The structure was extended to support
 * new mask values. Two new members, iOrder and iImage, were added to support the new mask values.
 *
 * This structure supersedes the LV_COLUMN structure.
 *
 * This structure is used with the LVM_GETCOLUMN, LVM_SETCOLUMN, LVM_INSERTCOLUMN, and
 * LVM_DELETECOLUMN messages.
 */
typedef struct tagLVCOLUMNW
{
    /**
     * Specifies which members contain valid information. It can be zero, or one or more of the
     * following values. Value Description LVCF_FMT The fmt member is valid. LVCF_IMAGE The iImage
     * member is valid. LVCF_ORDER The iOrder member is valid. LVCF_SUBITEM The iSubItem member is
     * valid. LVCF_TEXT The pszText member is valid. LVCF_WIDTH The cx member is valid.
     */
    UINT mask;
    /**
     * Alignment of the column heading and the subitem text in the column. It is one of the following
     * values: Value Description LVCFMT_BITMAP_ON_RIGHT The bitmap appears to the right of text. This
     * does not affect an image from an image list assigned to the header item. LVCFMT_CENTER Text is
     * centered. LVCFMT_IMAGE The item displays an image from an image list. LVCFMT_LEFT Text is
     * left-aligned. LVCFMT_RIGHT Text is right-aligned.
     *
     * The leftmost column in a list view control must be left aligned.
     */
    int fmt;
    /**
     * Width of the column, in pixels.
     */
    int cx;
    /**
     * If column information is being set, this member is the pointer to a null-terminated string that
     * contains the column heading text. If the structure is receiving information about a column, this
     * member specifies the address of the buffer that receives the column heading text.
     */
    LPWSTR pszText;
    /**
     * Size of the buffer pointed to by the pszText member. If the structure is not receiving
     * information about a column, this member is ignored.
     */
    int cchTextMax;
    /**
     * Index of subitem associated with the column.
     */
    int iSubItem;
#if (_WIN32_IE >= 0x0300)
    /**
     * Zero-based index of an image within the image list. The specified image will appear within the
     * column.
     */
    int iImage;
    /**
     * Zero-based column offset. Column offset is with left-to-right order. For example, zero indicates
     * the leftmost column.
     */
    int iOrder;
#endif
} LVCOLUMNW, FAR* LPLVCOLUMNW;

#ifdef UNICODE
#define  LVCOLUMN               LVCOLUMNW
#define  LPLVCOLUMN             LPLVCOLUMNW
#else
#define  LVCOLUMN               LVCOLUMNA
#define  LPLVCOLUMN             LPLVCOLUMNA
#endif


#define LVCF_FMT                0x0001
#define LVCF_WIDTH              0x0002
#define LVCF_TEXT               0x0004
#define LVCF_SUBITEM            0x0008
#if (_WIN32_IE >= 0x0300)
#define LVCF_IMAGE              0x0010
#define LVCF_ORDER              0x0020
#endif

#define LVCFMT_LEFT             0x0000
#define LVCFMT_RIGHT            0x0001
#define LVCFMT_CENTER           0x0002
#define LVCFMT_JUSTIFYMASK      0x0003
#if (_WIN32_IE >= 0x0300)
#define LVCFMT_IMAGE            0x0800
#define LVCFMT_BITMAP_ON_RIGHT  0x1000
#define LVCFMT_COL_HAS_IMAGES   0x8000
#endif

#define LVM_GETCOLUMNA          (LVM_FIRST + 25)
#define LVM_GETCOLUMNW          (LVM_FIRST + 95)
#ifdef UNICODE
/**
 * This message retrieves the attributes of a list view control column. You can send this message
 * explicitly or by using the ListView_GetColumn macro.
 *
 * @param iCol Index of the column.
 * @param pcol Pointer to an LVCOLUMN structure that specifies the data to retrieve and receives
 *   data about the column. The mask member specifies which column attributes to retrieve. If the mask
 *   member specifies the LVCF_TEXT value, the pszText member must contain the address of the buffer
 *   that receives the item text and the cchTextMax member must specify the size of the buffer.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define  LVM_GETCOLUMN          LVM_GETCOLUMNW
#else
/**
 * This message retrieves the attributes of a list view control column. You can send this message
 * explicitly or by using the ListView_GetColumn macro.
 *
 * @param iCol Index of the column.
 * @param pcol Pointer to an LVCOLUMN structure that specifies the data to retrieve and receives
 *   data about the column. The mask member specifies which column attributes to retrieve. If the mask
 *   member specifies the LVCF_TEXT value, the pszText member must contain the address of the buffer
 *   that receives the item text and the cchTextMax member must specify the size of the buffer.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define  LVM_GETCOLUMN          LVM_GETCOLUMNA
#endif

/**
 * This macro retrieves the attributes of a list view control's column. You can use this macro or
 * send the LVM_GETCOLUMN message explicitly.
 *
 * @param hwnd Handle to the list view control.
 * @param iCol Index of the column.
 * @param pcol Pointer to an LVCOLUMN structure that specifies the information to retrieve and
 *   receives information about the column. The mask member specifies which column attributes to
 *   retrieve. If the mask member specifies the LVCF_TEXT value, the pszText member must contain the
 *   address of the buffer that receives the item text, and the cchTextMax member must specify the
 *   size of the buffer.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define ListView_GetColumn(hwnd, iCol, pcol) \
    (BOOL)SNDMSG((hwnd), LVM_GETCOLUMN, (WPARAM)(int)(iCol), (LPARAM)(LV_COLUMN FAR*)(pcol))


#define LVM_SETCOLUMNA          (LVM_FIRST + 26)
#define LVM_SETCOLUMNW          (LVM_FIRST + 96)
#ifdef UNICODE
/**
 * This message sets the attributes of a list view column. You can send this message explicitly or
 * by using the ListView_SetColumn macro.
 *
 * @param iCol Index of the column
 * @param pcol Pointer to an LVCOLUMN structure that contains the new column attributes. The mask
 *   member specifies which column attributes to set. If the mask member specifies the LVCF_TEXT
 *   value, the pszText member is the address of a null-terminated string and the cchTextMax member is
 *   ignored.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define  LVM_SETCOLUMN          LVM_SETCOLUMNW
#else
/**
 * This message sets the attributes of a list view column. You can send this message explicitly or
 * by using the ListView_SetColumn macro.
 *
 * @param iCol Index of the column
 * @param pcol Pointer to an LVCOLUMN structure that contains the new column attributes. The mask
 *   member specifies which column attributes to set. If the mask member specifies the LVCF_TEXT
 *   value, the pszText member is the address of a null-terminated string and the cchTextMax member is
 *   ignored.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define  LVM_SETCOLUMN          LVM_SETCOLUMNA
#endif

/**
 * This macro sets the attributes of a list view column. You can use this macro or send the
 * LVM_SETCOLUMN message explicitly.
 *
 * @param hwnd Handle to the list view control.
 * @param iCol Index of the column.
 * @param pcol Pointer to an LVCOLUMN structure that contains the new column attributes. The mask
 *   member specifies which column attributes to set. If the mask member specifies the LVCF_TEXT
 *   value, the pszText member is the address of a null-terminated string and the cchTextMax member is
 *   ignored.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define ListView_SetColumn(hwnd, iCol, pcol) \
    (BOOL)SNDMSG((hwnd), LVM_SETCOLUMN, (WPARAM)(int)(iCol), (LPARAM)(const LV_COLUMN FAR*)(pcol))


#define LVM_INSERTCOLUMNA       (LVM_FIRST + 27)
#define LVM_INSERTCOLUMNW       (LVM_FIRST + 97)
#ifdef UNICODE
/**
 * This message inserts a new column in a list view control. You can send this message explicitly or
 * by using the ListView_InsertColumn macro.
 *
 * @param iCol Index of the new column
 * @param pcol Pointer to an LVCOLUMN structure that contains the attributes of the new column
 *
 * @return The index of the new column indicates success. -1 indicates failure.
 */
#   define  LVM_INSERTCOLUMN    LVM_INSERTCOLUMNW
#else
/**
 * This message inserts a new column in a list view control. You can send this message explicitly or
 * by using the ListView_InsertColumn macro.
 *
 * @param iCol Index of the new column
 * @param pcol Pointer to an LVCOLUMN structure that contains the attributes of the new column
 *
 * @return The index of the new column indicates success. -1 indicates failure.
 */
#   define  LVM_INSERTCOLUMN    LVM_INSERTCOLUMNA
#endif

/**
 * This macro inserts a new column in a list view control. You can use this macro or send the
 * LVM_INSERTCOLUMN message explicitly.
 *
 * @param hwnd Handle to the list view control.
 * @param iCol Index of the new column.
 * @param pcol Pointer to an LVCOLUMN structure that contains the attributes of the new column.
 *
 * @return The index of the new column indicates success. -1 indicates failure.
 */
#define ListView_InsertColumn(hwnd, iCol, pcol) \
    (int)SNDMSG((hwnd), LVM_INSERTCOLUMN, (WPARAM)(int)(iCol), (LPARAM)(const LV_COLUMN FAR*)(pcol))


/**
 * This message removes a column from a list view control. You can send this message explicitly or
 * by using the ListView_DeleteColumn macro.
 *
 * @param iCol Index of the column to delete.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define LVM_DELETECOLUMN        (LVM_FIRST + 28)
/**
 * This macro removes a column from a list view control. You can use this macro or send the
 * LVM_DELETECOLUMN message explicitly.
 *
 * @param hwnd Handle to the list view control.
 * @param iCol Index of the column to delete.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define ListView_DeleteColumn(hwnd, iCol) \
    (BOOL)SNDMSG((hwnd), LVM_DELETECOLUMN, (WPARAM)(int)(iCol), 0)


/**
 * This message retrieves the width of a column in report or list view. You can send this message
 * explicitly or by using the ListView_GetColumnWidth macro.
 *
 * @param iCol Index of the column. This parameter is ignored in list view.
 *
 * @return The column width indicates success. Zero indicates failure. If this message is sent to a
 *   list view control with the LVS_REPORT style and the specified column doesn't exist, the return
 *   value is undefined.
 */
#define LVM_GETCOLUMNWIDTH      (LVM_FIRST + 29)
/**
 * This macro retrieves the width of a column in report or list view. You can use this macro or send
 * the LVM_GETCOLUMNWIDTH message explicitly.
 *
 * @param hwnd Handle to the list view control.
 * @param iCol Index of the column. This parameter is ignored in list view.
 *
 * @return The column width indicates success. Zero indicates failure. If this macro is used on a
 *   list view control with the LVS_REPORT style and the specified column does not exist, the return
 *   value is undefined.
 */
#define ListView_GetColumnWidth(hwnd, iCol) \
    (int)SNDMSG((hwnd), LVM_GETCOLUMNWIDTH, (WPARAM)(int)(iCol), 0)


#define LVSCW_AUTOSIZE              -1
#define LVSCW_AUTOSIZE_USEHEADER    -2
/**
 * This message changes the width of a column in report or list view. You can send this message
 * explicitly or by using the ListView_SetColumnWidth macro.
 *
 * @param iCol Index of the column. In list view, the iCol parameter must be -1.
 * @param cx New width of the column, in list view coordinates, or one of the following values:
 *   Value Description LVSCW_AUTOSIZE Automatically sizes the column LVSCW_AUTOSIZE_USEHEADER
 *   Automatically sizes the column to fit the header text
 */
#define LVM_SETCOLUMNWIDTH          (LVM_FIRST + 30)

/**
 * This macro changes the width of a column in report or list view. You can use this macro or send
 * the LVM_SETCOLUMNWIDTH message explicitly.
 *
 * @param hwnd Handle to the list view control.
 * @param iCol Index of the column. In list view, the iCol parameter must be -1.
 * @param cx New width of the column, in list view coordinates, or one of the following values:
 *   Value Description LVSCW_AUTOSIZE Automatically sizes the column. LVSCW_AUTOSIZE_USEHEADER
 *   Automatically sizes the column to fit the header text.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * ListView_SetColumnWidth converts the cx parameter to a 16-bit value.
 */
#define ListView_SetColumnWidth(hwnd, iCol, cx) \
    (BOOL)SNDMSG((hwnd), LVM_SETCOLUMNWIDTH, (WPARAM)(int)(iCol), MAKELPARAM((cx), 0))

#if (_WIN32_IE >= 0x0300)
/**
 * This message retrieves the handle to the header control used by the list view control.
 *
 * @return Returns the handle to the header control.
 */
#define LVM_GETHEADER               (LVM_FIRST + 31)
/**
 * This macro retrieves the handle to the header control used by a list view control.
 *
 * @param hwndLV Handle to a list view control.
 *
 * @return Returns the handle to the header control.
 */
#define ListView_GetHeader(hwnd)\
    (HWND)SNDMSG((hwnd), LVM_GETHEADER, 0, 0L)
#endif

/**
 * This message creates a drag image list for the specified item. You can send this message
 * explicitly or by using the ListView_CreateDragImage macro.
 *
 * @param iItem Index of the item.
 * @param lpptUpLeft Long pointer to a POINT structure that receives the initial location of the
 *   upper-left corner of the image, in view coordinates.
 *
 * @return The handle to the drag image list indicates success. NULL indicates otherwise.
 */
#define LVM_CREATEDRAGIMAGE     (LVM_FIRST + 33)
/**
 * This macro creates a drag image list for the specified item. You can use this macro or send the
 * LVM_CREATEDRAGIMAGE message explicitly.
 *
 * @param hwnd Handle to the list view control.
 * @param iItem Index of the item.
 * @param lpptUpLeft Long pointer to a POINT structure that receives the initial location of the
 *   upper-left corner of the image, in view coordinates.
 *
 * @return The handle to the drag image list indicates success. NULL indicates failure.
 */
#define ListView_CreateDragImage(hwnd, i, lpptUpLeft) \
    (HIMAGELIST)SNDMSG((hwnd), LVM_CREATEDRAGIMAGE, (WPARAM)(int)(i), (LPARAM)(LPPOINT)(lpptUpLeft))


/**
 * This message retrieves the bounding rectangle of all items in the list view control. The list
 * view must be in icon or small icon view. You can send this message explicitly or by using the
 * ListView_GetViewRect macro.
 *
 * @param prc Pointer to a RECT structure that receives the bounding rectangle. All coordinates are
 *   relative to the visible area of the list view control.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define LVM_GETVIEWRECT         (LVM_FIRST + 34)
/**
 * This macro retrieves the bounding rectangle of all items in the list view control. The list view
 * must be in icon or small icon view. You can use this macro or send the LVM_GETVIEWRECT message
 * explicitly.
 *
 * @param hwnd Handle to the list view control.
 * @param prc Pointer to a RECT structure that receives the bounding rectangle. All coordinates are
 *   relative to the visible area of the list view control.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define ListView_GetViewRect(hwnd, prc) \
    (BOOL)SNDMSG((hwnd), LVM_GETVIEWRECT, 0, (LPARAM)(RECT FAR*)(prc))


/**
 * This message retrieves the text color of a list view control. You can send this message
 * explicitly or by using the ListView_GetTextColor macro.
 *
 * @return Returns the text color
 */
#define LVM_GETTEXTCOLOR        (LVM_FIRST + 35)
/**
 * This macro retrieves the text color of a list view control. You can use this macro or send the
 * LVM_GETTEXTCOLOR message explicitly.
 *
 * @param hwnd Handle to the list view control.
 *
 * @return Returns the text color.
 */
#define ListView_GetTextColor(hwnd)  \
    (COLORREF)SNDMSG((hwnd), LVM_GETTEXTCOLOR, 0, 0L)


/**
 * This message sets the text color of a list view control. You can send this message explicitly or
 * by using the ListView_SetTextColor macro.
 *
 * @param clrText New text color
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define LVM_SETTEXTCOLOR        (LVM_FIRST + 36)
/**
 * This macro sets the text color of a list view control. You can use this macro or send the
 * LVM_SETTEXTCOLOR message explicitly.
 *
 * @param hwnd Handle to the list view control.
 * @param clrText New text color.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define ListView_SetTextColor(hwnd, clrText) \
    (BOOL)SNDMSG((hwnd), LVM_SETTEXTCOLOR, 0, (LPARAM)(COLORREF)(clrText))


/**
 * This message retrieves the text background color of a list view control. You can send this
 * message explicitly or by using the ListView_GetTextBkColor macro.
 *
 * @return Returns the background color of the text
 */
#define LVM_GETTEXTBKCOLOR      (LVM_FIRST + 37)
/**
 * This macro retrieves the text background color of a list view control. You can use this macro or
 * send the LVM_GETTEXTBKCOLOR message explicitly.
 *
 * @param hwnd Handle to the list view control.
 *
 * @return Returns the background color of the text.
 */
#define ListView_GetTextBkColor(hwnd)  \
    (COLORREF)SNDMSG((hwnd), LVM_GETTEXTBKCOLOR, 0, 0L)


/**
 * This message sets the background color of text in a list view control. You can send this message
 * explicitly or by using the ListView_SetTextBkColor macro.
 *
 * @param clrText New text color
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define LVM_SETTEXTBKCOLOR      (LVM_FIRST + 38)
/**
 * This macro sets the background color of text in a list view control. You can use this macro or
 * send the LVM_SETTEXTBKCOLOR message explicitly.
 *
 * @param hwnd Handle to the list view control.
 * @param clrText New text color.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define ListView_SetTextBkColor(hwnd, clrTextBk) \
    (BOOL)SNDMSG((hwnd), LVM_SETTEXTBKCOLOR, 0, (LPARAM)(COLORREF)(clrTextBk))


/**
 * This message retrieves the index of the topmost visible item when in list or report view. You can
 * send this message explicitly or by using the ListView_GetTopIndex macro.
 *
 * @return The index of the item indicates success. Zero indicates the list view control is in icon
 *   or small icon view.
 */
#define LVM_GETTOPINDEX         (LVM_FIRST + 39)
/**
 * This macro retrieves the index of the topmost visible item when in list or report view. You can
 * use this macro or send the LVM_GETTOPINDEX message explicitly.
 *
 * @param hwnd Handle to the list view control.
 *
 * @return The index of the item indicates success. Zero indicates that the list view control is in
 *   icon or small icon view.
 */
#define ListView_GetTopIndex(hwndLV) \
    (int)SNDMSG((hwndLV), LVM_GETTOPINDEX, 0, 0)


/**
 * This message calculates the number of items that can fit vertically in the visible area of a list
 * view control when in list or report view. Only fully visible items are counted. You can send this
 * message explicitly or by using the ListView_GetCountPerPage macro.
 *
 * @return The number of fully visible items indicates success. If the current view is icon or small
 *   icon view, the return value is the total number of items in the list view control.
 */
#define LVM_GETCOUNTPERPAGE     (LVM_FIRST + 40)
/**
 * This macro calculates the number of items that can fit vertically in the visible area of a list
 * view control when in list or report view. Only fully visible items are counted. You can use this
 * macro or send the LVM_GETCOUNTPERPAGE message explicitly.
 *
 * @param hwnd Handle to the list view control.
 *
 * @return The number of fully visible items indicates success. The total number of items in the
 *   list view control indicates that the current view is icon or small icon view.
 */
#define ListView_GetCountPerPage(hwndLV) \
    (int)SNDMSG((hwndLV), LVM_GETCOUNTPERPAGE, 0, 0)


/**
 * This message retrieves the current view origin for a list view control. You can send this message
 * explicitly or by using the ListView_GetOrigin macro.
 *
 * @param lpptOrg Long pointer to a POINT structure that receives the view origin
 *
 * @return TRUE indicates success. FALSE indicates that the current view is list or report view.
 */
#define LVM_GETORIGIN           (LVM_FIRST + 41)
/**
 * This macro retrieves the current view origin for a list view control. You can use this macro or
 * send the LVM_GETORIGIN message explicitly.
 *
 * @param hwnd Handle to the list view control.
 * @param lpptOrg Long pointer to a POINT structure that receives the view origin.
 *
 * @return TRUE indicates success. FALSE indicates that the current view is list or report view.
 */
#define ListView_GetOrigin(hwndLV, ppt) \
    (BOOL)SNDMSG((hwndLV), LVM_GETORIGIN, (WPARAM)0, (LPARAM)(POINT FAR*)(ppt))


/**
 * This message updates a list view item. If the list view control has the LVS_AUTOARRANGE style,
 * this macro causes the list view control to be arranged. You can send this message explicitly or
 * by using the ListView_Update macro.
 *
 * @param iItem Index of the item to update
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define LVM_UPDATE              (LVM_FIRST + 42)
/**
 * This macro updates a list view item. If the list view control has the LVS_AUTOARRANGE style, this
 * macro causes the list view control to be arranged. You can use this macro or send the LVM_UPDATE
 * message explicitly.
 *
 * @param hwnd Handle to the list view control.
 * @param iItem
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define ListView_Update(hwndLV, i) \
    (BOOL)SNDMSG((hwndLV), LVM_UPDATE, (WPARAM)i, 0L)


/**
 * This message changes the state of an item in a list view control. You can send this message
 * explicitly or by using the ListView_SetItemState macro.
 *
 * @param i Index of the list view item. If this parameter is -1, then the state change is applied
 *   to all items.
 * @param pitem Pointer to an LVITEM structure. The stateMask member specifies which state bits to
 *   change, and the state member contains the new values for those bits. The other members are
 *   ignored.
 *
 * @return If you send this message explicitly, TRUE indicates success. FALSE indicates failure.
 */
#define LVM_SETITEMSTATE        (LVM_FIRST + 43)
/**
 * This macro changes the state of an item in a list view control. You can use this macro or send
 * the LVM_SETITEMSTATE message explicitly.
 *
 * @param hwnd Handle to the list view control.
 * @param i Index of the list view item. If this parameter is -1, then the state change is applied
 *   to all items.
 * @param state New state bits for the item. The mask parameter indicates the valid bits of the
 *   state parameter. The macro ignores bits in the state parameter if the corresponding bit is not
 *   set in the mask parameter. The low-order byte contains a set of bit flags that indicate the
 *   item's state. This byte can be a combination of the following values: Value Description LVIS_CUT
 *   The item is marked for a cut-and-paste operation. LVIS_DROPHILITED The item is highlighted as a
 *   drag-and-drop target. LVIS_FOCUSED The item has the focus, so it is surrounded by a standard
 *   focus rectangle. Although more than one item may be selected, only one item can have the focus.
 *   LVIS_SELECTED The item is selected. The appearance of a selected item depends on whether it has
 *   the focus and also on the system colors used for selection. Bits 8 through 11 of the state
 *   parameter specify the one-based index of an overlay image in the control's image lists. Both the
 *   full-sized icon image list and the small icon image list can have overlay images. The overlay
 *   image is superimposed over the item's icon image. If these bits are zero, the item has no overlay
 *   image. To isolate these bits, use the LVIS_OVERLAYMASK mask. To specify an overlay index, use the
 *   INDEXTOOVERLAYMASK macro. Bits 12 through 15 of the state parameter specify the one-based index
 *   of an image in the control's state image list. The state image is displayed next to an item's
 *   icon to indicate an application-defined state. If these bits are zero, the item has no state
 *   image. To isolate these bits, use the LVIS_STATEIMAGEMASK mask. To specify a state image index,
 *   use the INDEXTOSTATEIMAGEMASK macro.
 * @param mask Bits of the state parameter that you want to set or clear. You can use
 *   ListView_SetItemState both to set and to clear bits. To set an item's overlay image index, set
 *   the LVIS_OVERLAYMASK bits. To set an item's state image index, set the LVIS_STATEIMAGEMASK bits.
 *
 * @return None.
 *
 * An item's state value includes a set of bit flags that indicate the item's state. The state value
 * can also include image list indexes that indicate the item's state image and overlay image.
 *
 * The mask parameter specifies the state bits you want to modify, and the state parameter specifies
 * the new value for those bits. To set a bit in the item's internal state, set it in both the mask
 * and state parameters. To clear a bit in the item's internal state, set it in the mask parameter
 * and clear it in the state parameter. To leave a bit unchanged in the item's internal state, clear
 * it in the mask parameter.
 */
#define ListView_SetItemState(hwndLV, i, data, mask) \
{ LV_ITEM _ms_lvi;\
  _ms_lvi.stateMask = mask;\
  _ms_lvi.state = data;\
  SNDMSG((hwndLV), LVM_SETITEMSTATE, (WPARAM)i, (LPARAM)(LV_ITEM FAR *)&_ms_lvi);\
}


/**
 * This message retrieves the state of a list view item. You can send this message explicitly or by
 * using the ListView_GetItemState macro.
 *
 * @param i Index of the list view item.
 * @param mask State data to retrieve. It is a combination of the following values: Value
 *   Description LVIS_CUT The item is marked for a cut-and-paste operation. LVIS_DROPHILITED The item
 *   is highlighted as a drag-and-drop target. LVIS_FOCUSED The item has the focus, so it is
 *   surrounded by a standard focus rectangle. Although more than one item may be selected, only one
 *   item can have the focus. LVIS_SELECTED The item is selected. The appearance of a selected item
 *   depends on whether it has the focus and also on the system colors used for selection.
 *   LVIS_OVERLAYMASK Use this mask to retrieve the item's overlay image index. LVIS_STATEIMAGEMASK
 *   Use this mask to retrieve the item's state image index. An item's state data includes a set of
 *   bit flags as well as image list indexes that indicate the item's state image and overlay image.
 *
 * @return Returns the current state for the specified item. The only valid bits in the return value
 *   are those that correspond to the bits set in the mask parameter.
 */
#define LVM_GETITEMSTATE        (LVM_FIRST + 44)
/**
 * This macro retrieves the state of a list view item. You can use this macro or send the
 * LVM_GETITEMSTATE message explicitly.
 *
 * @param hwnd Handle to the list view control.
 * @param i Index of the list view item.
 * @param mask State information to retrieve. It can be a combination of the following values: Value
 *   Description LVIS_CUT The item is marked for a cut-and-paste operation. LVIS_DROPHILITED The item
 *   is highlighted as a drag-and-drop target. LVIS_FOCUSED The item has the focus, so it is
 *   surrounded by a standard focus rectangle. Although more than one item may be selected, only one
 *   item can have the focus. LVIS_SELECTED The item is selected. The appearance of a selected item
 *   depends on whether it has the focus and also on the system colors used for selection.
 *   LVIS_OVERLAYMASK Use this mask to retrieve the item's overlay image index. LVIS_STATEIMAGEMASK
 *   Use this mask to retrieve the item's state image index.
 *
 * @return Returns the current state for the specified item. The only valid bits in the return value
 *   are those that correspond to the bits set in the mask parameter.
 *
 * An item's state information includes a set of bit flags as well as image list indexes that
 * indicate the item's state image and overlay image.
 */
#define ListView_GetItemState(hwndLV, i, mask) \
   (UINT)SNDMSG((hwndLV), LVM_GETITEMSTATE, (WPARAM)i, (LPARAM)mask)

#if (_WIN32_IE >= 0x0300)
/**
 * This macro determines if an item in a list view control is selected. This should be used only for
 * list view controls that have the LVS_EX_CHECKBOXES style.
 *
 * @param hwndLV Handle to a list view control.
 * @param iIndex Index of the item for which to retrieve the check state.
 *
 * @return Returns nonzero if the specified item is selected, or zero otherwise. If this macro is
 *   applied to a list view control that does not have check boxes enabled, the return value is not
 *   reliable.
 */
#define ListView_GetCheckState(hwndLV, i) \
   ((((UINT)(SNDMSG((hwndLV), LVM_GETITEMSTATE, (WPARAM)i, LVIS_STATEIMAGEMASK))) >> 12) -1)
#endif

#define LVM_GETITEMTEXTA        (LVM_FIRST + 45)
#define LVM_GETITEMTEXTW        (LVM_FIRST + 115)

#ifdef UNICODE
/**
 * This message retrieves the text of a list view item or subitem. You can send this message
 * explicitly or by using the ListView_GetItemText macro.
 *
 * @param iItem Index of the list view item.
 * @param pitem Pointer to an LVITEM structure. The iSubItem member specifies the index of a
 *   subitem, or it can be zero to get the item label. The pszText member points to a buffer that
 *   receives the text, and the cchTextMax member specifies the size of the buffer.
 *
 * @return If you send this message explicitly, it returns the length of the retrieved string. If
 *   you can send this message implicitly by using the ListView_GetItemText macro, there is no return
 *   value.
 */
#define  LVM_GETITEMTEXT        LVM_GETITEMTEXTW
#else
/**
 * This message retrieves the text of a list view item or subitem. You can send this message
 * explicitly or by using the ListView_GetItemText macro.
 *
 * @param iItem Index of the list view item.
 * @param pitem Pointer to an LVITEM structure. The iSubItem member specifies the index of a
 *   subitem, or it can be zero to get the item label. The pszText member points to a buffer that
 *   receives the text, and the cchTextMax member specifies the size of the buffer.
 *
 * @return If you send this message explicitly, it returns the length of the retrieved string. If
 *   you can send this message implicitly by using the ListView_GetItemText macro, there is no return
 *   value.
 */
#define  LVM_GETITEMTEXT        LVM_GETITEMTEXTA
#endif

/**
 * This macro retrieves the text of a list view item or subitem. You can use this macro or send the
 * LVM_GETITEMTEXT message explicitly.
 *
 * @param hwnd Handle to the list view control.
 * @param iItem Index of the list view item.
 * @param iSubItem Index of the subitem, or zero to retrieve the item label.
 * @param pszText Pointer to the buffer that receives the item or subitem text.
 * @param cchTextMax Size of the buffer, in bytes.
 *
 * @return The ListView_GetItemText macro does not return a value. If you send the LVM_GETITEMNEXT
 *   message explicitly, it returns the length of the retrieved string.
 */
#define ListView_GetItemText(hwndLV, i, iSubItem_, pszText_, cchTextMax_) \
{ LV_ITEM _ms_lvi;\
  _ms_lvi.iSubItem = iSubItem_;\
  _ms_lvi.cchTextMax = cchTextMax_;\
  _ms_lvi.pszText = pszText_;\
  SNDMSG((hwndLV), LVM_GETITEMTEXT, (WPARAM)i, (LPARAM)(LV_ITEM FAR *)&_ms_lvi);\
}


#define LVM_SETITEMTEXTA        (LVM_FIRST + 46)
#define LVM_SETITEMTEXTW        (LVM_FIRST + 116)

#ifdef UNICODE
/**
 * This message changes the text of a list view item or subitem. You can send this message
 * explicitly or by using the ListView_SetItemText macro.
 *
 * @param i Index of the list view item
 * @param pitem Pointer to an LVITEM structure. The iSubItem member is the index of the subitem, or
 *   it can be zero to set the item label. The pszText member is the address of a null-terminated
 *   string containing the new text; it can also be NULL. The pszText member can also be
 *   LPSTR_TEXTCALLBACK to indicate a callback item for which the parent window stores the text. In
 *   this case, the list view control sends the parent an LVN_GETDISPINFO notification message when it
 *   needs the text.
 *
 * @return If you send this message explicitly, TRUE indicates success. FALSE indicates failure.
 */
#define  LVM_SETITEMTEXT        LVM_SETITEMTEXTW
#else
/**
 * This message changes the text of a list view item or subitem. You can send this message
 * explicitly or by using the ListView_SetItemText macro.
 *
 * @param i Index of the list view item
 * @param pitem Pointer to an LVITEM structure. The iSubItem member is the index of the subitem, or
 *   it can be zero to set the item label. The pszText member is the address of a null-terminated
 *   string containing the new text; it can also be NULL. The pszText member can also be
 *   LPSTR_TEXTCALLBACK to indicate a callback item for which the parent window stores the text. In
 *   this case, the list view control sends the parent an LVN_GETDISPINFO notification message when it
 *   needs the text.
 *
 * @return If you send this message explicitly, TRUE indicates success. FALSE indicates failure.
 */
#define  LVM_SETITEMTEXT        LVM_SETITEMTEXTA
#endif

/**
 * This macro changes the text of a list view item or subitem. You can use this macro or send the
 * LVM_SETITEMTEXT message explicitly.
 *
 * @param hwnd Handle to the list view control.
 * @param i Index of the list view item.
 * @param iSubItem Index of the subitem. To set the item label, set iSubItem to zero.
 * @param pszText Pointer to a null-terminated string that contains the new text. This parameter can
 *   be LPSTR_TEXTCALLBACK to indicate a callback item for which the parent window stores the text. In
 *   this case, the list view control sends the parent an LVN_GETDISPINFO notification message when it
 *   needs the text. This parameter can be NULL.
 *
 * @return None.
 */
#define ListView_SetItemText(hwndLV, i, iSubItem_, pszText_) \
{ LV_ITEM _ms_lvi;\
  _ms_lvi.iSubItem = iSubItem_;\
  _ms_lvi.pszText = pszText_;\
  SNDMSG((hwndLV), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)(LV_ITEM FAR *)&_ms_lvi);\
}

#if (_WIN32_IE >= 0x0300)
// these flags only apply to LVS_OWNERDATA listviews in report or list mode
#define LVSICF_NOINVALIDATEALL  0x00000001
#define LVSICF_NOSCROLL         0x00000002
#endif

/**
 * This message prepares a list view control for adding a large number of items. In a regular list
 * view control, it causes the control to allocate memory for the specified number of items. In a
 * virtual list view control, available in Windows CE versions 2.0 and later, it sets the number of
 * virtual items in the control. You can send this message explicitly or use the
 * ListView_SetItemCount or ListView_SetItemCountEx macros.
 *
 * @param cItems Number of items the list view control will ultimately contain
 * @param dwFlags Version 4.70. Specifies the behavior of the list view control after resetting the
 *   item count. It can be a combination of the following values: Value Description
 *   LVSICF_NOINVALIDATEALL The list view control will not repaint unless affected items are currently
 *   in view. LVSICF_NOSCROLL The list view control will not change the scroll position when the item
 *   count changes. If the list view control was created without the LVS_OWNERDATA style, sending this
 *   message causes the control to allocate its internal data structures for the specified number of
 *   items. This prevents the control from having to allocate the data structures every time an item
 *   is added. If the list view control was created with the LVS_OWNERDATA style (a virtual list
 *   view), sending this message sets the virtual number of items that the control contains.
 * @param cItems Number of items that the list view control will ultimately contain
 * @param dwFlags For Windows CE version 1.0, set this value to 0. For Windows CE versions 2.0 and
 *   later, this value specifies the behavior of the list view control after resetting the item count.
 *   This value can be a combination of the following: Value Description LVSICF_NOINVALIDATEALL The
 *   list view control will not repaint unless affected items are currently in view. LVSICF_NOSCROLL
 *   The list view control will not change the scroll position when the item count changes.
 *
 * @return In Windows CE version 1.0, this message has no return value. In Windows CE versions 2.0
 *   and later, nonzero indicates success. Zero indicates failure.
 *
 * Windows CE versions 2.0 and later support virtual list views, which you create using the
 * LVS_OWNERDATA style. In a virtual list view, this function sets the number of items in the
 * virtual list view, but does not allocate any memory.
 *
 * The dwFlags parameter is intended only for list view controls that use the LVS_OWNERDATA and
 * either LVS_REPORT or LVS_LIST styles.
 */
#define LVM_SETITEMCOUNT        (LVM_FIRST + 47)
/**
 * This macro prepares a list view control for adding a large number of items. You can use this
 * macro or send the LVM_SETITEMCOUNT message explicitly.
 *
 * @param hwndLV Handle to a list view control.
 * @param cItems Number of items for which the list view control should allocate memory.
 *
 * @return None.
 *
 * If the list view control was created without the LVS_OWNERDATA style, this macro causes the
 * control to allocate its internal data structures for the specified number of items. This prevents
 * the control from having to allocate the data structures every time an item is added.
 *
 * If the list view control was created with the LVS_OWNERDATA style , the ListView_SetItemCountEx
 * macro should be used.
 *
 * In Windows CE versions 2.0 and later, if the list view control is a virtual list view (has the
 * LVS_OWNERDATA style), use the ListView_SetItemCountEx macro instead.
 */
#define ListView_SetItemCount(hwndLV, cItems) \
  SNDMSG((hwndLV), LVM_SETITEMCOUNT, (WPARAM)cItems, 0)

#if (_WIN32_IE >= 0x0300)
/**
 * This macro sets the virtual number of items in a virtual list view control.
 *
 * @param hwndLV Handle to a virtual list view control.
 * @param cItems Number of items that the list view control will contain.
 * @param dwFlags Specifies the behavior of the list view control after resetting the item count. It
 *   can be one or a combination of the following values: Value Description LVSICF_NOINVALIDATEALL The
 *   list view control will not repaint unless affected items are currently in view. LVSICF_NOSCROLL
 *   The list view control will not change the scroll position when the item count changes.
 *
 * This macro is intended only for list view controls that use the LVS_OWNERDATA and LVS_REPORT or
 * LVS_LIST styles.
 *
 * If the list view control was created with the LVS_OWNERDATA style, this macro sets the virtual
 * number of items that the control contains.
 *
 * If the list view control was created without the LVS_OWNERDATA style, the ListView_SetItemCount
 * macro should be used.
 */
#define ListView_SetItemCountEx(hwndLV, cItems, dwFlags) \
  SNDMSG((hwndLV), LVM_SETITEMCOUNT, (WPARAM)cItems, (LPARAM)dwFlags)
#endif

typedef int (CALLBACK *PFNLVCOMPARE)(LPARAM, LPARAM, LPARAM);


/**
 * This message sorts list view items using an application-defined comparison function. The index of
 * each item changes to reflect the new sequence. You can send this message explicitly or by using
 * the ListView_SortItems macro.
 *
 * @param lParamSort Application-defined value passed to the comparison function.
 * @param pfnCompare Pointer to the application-defined comparison function. The comparison function
 *   is called during the sort operation each time the relative order of two list items needs to be
 *   compared.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * The comparison function has the following form:
 *
 *     int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2,
 *         LPARAM lParamSort);
 *
 * The lParam1 parameter is the 32-bit value associated with the first item being compared, and the
 * lParam2 parameter is the value associated with the second item. These are the values specified in
 * the lParam member of the items' LVITEM structure when they were inserted into the list. The
 * lParamSort parameter is the same value passed to the LVM_SORTITEMS message.
 */
#define LVM_SORTITEMS           (LVM_FIRST + 48)
/**
 * This macro uses an application-defined comparison function to sort the items of a list view
 * control. The index of each item changes to reflect the new sequence. You can use this macro or
 * send the LVM_SORTITEMS message explicitly.
 *
 * @param hwnd Handle to the list view control.
 * @param pfnCompare Pointer to the application-defined comparison function. The comparison function
 *   is called during the sort operation each time the relative order of two list items needs to be
 *   compared.
 * @param lParamSort Application-defined value that is passed to the comparison function.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * The comparison function has the following form:
 *
 *     int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2,
 *         LPARAM lParamSort);
 *
 * The lParam1 parameter is the 32-bit value associated with the first item being compared; and the
 * lParam2 parameter is the value associated with the second item. These are the values that were
 * specified in the lParam member of the items' LVITEM structure when they were inserted into the
 * list. The lParamSort parameter is the same value passed to the LVM_SORTITEMS message.
 *
 * The comparison function must return a negative value if the first item should precede the second,
 * a positive value if the first item should follow the second, or zero if the two items are
 * equivalent.
 */
#define ListView_SortItems(hwndLV, _pfnCompare, _lPrm) \
  (BOOL)SNDMSG((hwndLV), LVM_SORTITEMS, (WPARAM)(LPARAM)_lPrm, \
  (LPARAM)(PFNLVCOMPARE)_pfnCompare)


/**
 * This message moves an item to a specified position in a list view control, which must be in icon
 * or small icon view. This message differs from the LVM_SETITEMPOSITION message in that it uses
 * 32-bit coordinates. You can send this message explicitly or by using the
 * ListView_SetItemPosition32 macro.
 *
 * @param iItem Index of the list view item for which to set the position
 * @param lpptNewPos Long pointer a POINT structure that contains the new position of the item, in
 *   list view coordinates
 *
 * @return None
 */
#define LVM_SETITEMPOSITION32   (LVM_FIRST + 49)
/**
 * This macro moves an item to a specified position in a list view control, which must be in icon or
 * small icon view. This macro differs from the ListView_SetItemPosition macro in that it uses
 * 32-bit coordinates. You can use this macro or send the LVM_SETITEMPOSITION32 message explicitly.
 *
 * @param hwnd Handle to the list view control.
 * @param iItem Index of the list view item for which to set the position.
 * @param x and y New horizontal and vertical coordinates of the item.
 *
 * @return None.
 */
#define ListView_SetItemPosition32(hwndLV, i, x, y) \
{ POINT ptNewPos = {x,y}; \
    SNDMSG((hwndLV), LVM_SETITEMPOSITION32, (WPARAM)(int)(i), (LPARAM)&ptNewPos); \
}


/**
 * This message determines the number of selected items in a list view control. You can send this
 * message explicitly or by using the ListView_GetSelectedCount macro.
 *
 * @return Returns the number of selected items
 */
#define LVM_GETSELECTEDCOUNT    (LVM_FIRST + 50)
/**
 * This macro determines the number of selected items in a list view control. You can use this macro
 * or send the LVM_GETSELECTEDCOUNT message explicitly.
 *
 * @param hwnd Handle to the list view control.
 *
 * @return Returns the number of selected items.
 */
#define ListView_GetSelectedCount(hwndLV) \
    (UINT)SNDMSG((hwndLV), LVM_GETSELECTEDCOUNT, 0, 0L)


/**
 * This message determines the spacing between items in a list view control. You can send this
 * message explicitly or by using the ListView_GetItemSpacing macro.
 *
 * @param fSmall Boolean that specifies the view for which to retrieve the item spacing. Set to TRUE
 *   for small icon view, or to FALSE for icon view.
 *
 * @return Returns the amount of spacing between items. The horizontal spacing is contained in the
 *   low-order word and the vertical spacing is contained in the high-order word.
 */
#define LVM_GETITEMSPACING      (LVM_FIRST + 51)
/**
 * This macro determines the spacing between items in a list view control. You can use this macro or
 * send the LVM_GETITEMSPACING message explicitly.
 *
 * @param hwnd Handle to the list view control.
 * @param fSmall Boolean value that specifies the view for which to retrieve the item spacing. Set
 *   to TRUE for small icon view, or to FALSE for icon view.
 *
 * @return Returns the amount of spacing between items.
 */
#define ListView_GetItemSpacing(hwndLV, fSmall) \
        (DWORD)SNDMSG((hwndLV), LVM_GETITEMSPACING, fSmall, 0L)


#define LVM_GETISEARCHSTRINGA   (LVM_FIRST + 52)
#define LVM_GETISEARCHSTRINGW   (LVM_FIRST + 117)

#ifdef UNICODE
/**
 * This message retrieves the incremental search string of a list view control. You can send this
 * message explicitly or by using the ListView_GetISearchString macro.
 *
 * @param lpsz Long pointer to a buffer that receives the incremental search string. The incremental
 *   search string is the character sequence that the user types while the list view has the input
 *   focus. Each time the user types a character, the system appends the character to the search
 *   string and then searches for a matching item. If the system finds a match, it selects the item
 *   and, if necessary, scrolls it into view.
 *
 * @return The number of characters in the incremental search string indicates success. Zero
 *   indicates that the list view control is not in incremental search mode.
 */
#define LVM_GETISEARCHSTRING    LVM_GETISEARCHSTRINGW
#else
/**
 * This message retrieves the incremental search string of a list view control. You can send this
 * message explicitly or by using the ListView_GetISearchString macro.
 *
 * @param lpsz Long pointer to a buffer that receives the incremental search string. The incremental
 *   search string is the character sequence that the user types while the list view has the input
 *   focus. Each time the user types a character, the system appends the character to the search
 *   string and then searches for a matching item. If the system finds a match, it selects the item
 *   and, if necessary, scrolls it into view.
 *
 * @return The number of characters in the incremental search string indicates success. Zero
 *   indicates that the list view control is not in incremental search mode.
 */
#define LVM_GETISEARCHSTRING    LVM_GETISEARCHSTRINGA
#endif

/**
 * This macro retrieves the incremental search string of a list-view control. You can use this macro
 * or send the LVM_GETISEARCHSTRING message explicitly.
 *
 * @param hwnd Handle to the list view control.
 * @param lpsz Long pointer to a buffer that receives the incremental search string.
 *
 * @return Returns the number of characters in the incremental search string, or zero if the list
 *   view control is not in incremental search mode.
 *
 * The incremental search string is the character sequence that the user types while the list view
 * has the input focus. Each time the user types a character, the system appends the character to
 * the search string and then searches for a matching item. If the system finds a match, it selects
 * the item and, if necessary, scrolls it into view.
 *
 * A time-out period is associated with each character that the user types. If the time-out period
 * elapses before the user types another character, the incremental search string is reset.
 */
#define ListView_GetISearchString(hwndLV, lpsz) \
        (BOOL)SNDMSG((hwndLV), LVM_GETISEARCHSTRING, 0, (LPARAM)(LPTSTR)lpsz)

#if (_WIN32_IE >= 0x0300)
/**
 * This message sets the spacing between icons in list view controls that have the LVS_ICON style.
 *
 * @param cx Distance, in pixels, to set between icons on the x-axis. Setting this value to -1
 *   resets the cx parameter to default spacing.
 * @param cy Distance, in pixels, to set between icons on the y-axis. Setting this value to -1
 *   resets the cy parameter to default spacing.
 *
 * @return Returns a DWORD value that contains the previous cx in the low-order word, and the
 *   previous cy in the high-order word.
 *
 * Values for cx and cy are relative to the upper-left corner of an icon bitmap. Therefore, to set
 * spacing between icons that do not overlap, the cx or cy values must include the size of the icon,
 * plus the amount of empty space desired between icons. Values that do not include the width of the
 * icon will result in overlaps.
 */
#define LVM_SETICONSPACING      (LVM_FIRST + 53)
// -1 for cx and cy means we'll use the default (system settings)
// 0 for cx or cy means use the current setting (allows you to change just one param)
/**
 * This macro sets the spacing between icons in list view controls set to the LVS_ICON style.
 *
 * @param hwndLV Handle to a list view control.
 * @param cx Distance, in pixels, to set between icons on the x-axis.
 * @param cy Distance, in pixels, to set between icons on the y-axis.
 *
 * @return Returns a DWORD value that contains the previous cx in the low-order word, and the
 *   previous cy in the high-order word.
 *
 * The cx and cy parameters are relative to the upper-left corner of an icon bitmap. Therefore, to
 * set spacing between icons that do not overlap, the cx or cy values must include the size of the
 * icon, plus the amount of empty space desired between icons. Values that do not include the width
 * of the icon will result in overlaps.
 */
#define ListView_SetIconSpacing(hwndLV, cx, cy) \
        (DWORD)SNDMSG((hwndLV), LVM_SETICONSPACING, 0, MAKELONG(cx,cy))


/**
 * This message sets extended styles in list view controls. It does not return a value.
 *
 * @param dwExMask Specifies which styles in dwExStyle are to be affected. Only the extended styles
 *   in dwExMask will be changed. All other styles will be maintained as is. If this parameter is
 *   zero, then all of the styles in dwExStyle will be affected.
 * @param dwExStyle Specifies the extended list view control style. This parameter can be a
 *   combination of extended styles The dwExMask parameter allows you to modify one or more extended
 *   styles without having to retrieve the existing styles first. For example: if you pass
 *   LVS_EX_FULLROWSELECT for dwExMask and 0 for dwExStyle, the LVS_EX_FULLROWSELECT style will be
 *   cleared, but all other styles will remain the same.
 *
 * @return Returns a DWORD value that contains the previous extended list view control styles
 *
 * For backward compatibility reasons, the ListView_SetExtendedListViewStyle macro has not been
 * updated to use dwExMask.
 */
#define LVM_SETEXTENDEDLISTVIEWSTYLE (LVM_FIRST + 54)   // optional wParam == mask
/**
 * This macro sets extended styles for list view controls.
 *
 * @param hwndLV Handle to the list view control that will receive the style change.
 * @param dwExStyle Specifies the extended list view control style. This parameter can be a
 *   combination of extended styles.
 */
#define ListView_SetExtendedListViewStyle(hwndLV, dw)\
        (DWORD)SNDMSG((hwndLV), LVM_SETEXTENDEDLISTVIEWSTYLE, 0, dw)
#if (_WIN32_IE >= 0x0400)
#define ListView_SetExtendedListViewStyleEx(hwndLV, dwMask, dw)\
        (DWORD)SNDMSG((hwndLV), LVM_SETEXTENDEDLISTVIEWSTYLE, dwMask, dw)
#endif

/**
 * This message retrieves the extended styles that are currently in use for a specified list view
 * control.
 *
 * @return Returns a DWORD that represents the styles currently in use for a specified list view
 *   control. This value can be a combination of extended styles.
 */
#define LVM_GETEXTENDEDLISTVIEWSTYLE (LVM_FIRST + 55)
/**
 * This macro retrieves the extended styles that are currently in use for a specified list view
 * control.
 *
 * @param hwndLV Handle to a list view control.
 *
 * @return Returns a DWORD value that represents the styles currently in use for a specified list
 *   view control. This can be a combination of extended styles.
 */
#define ListView_GetExtendedListViewStyle(hwndLV)\
        (DWORD)SNDMSG((hwndLV), LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0)

#define LVS_EX_GRIDLINES        0x00000001
#define LVS_EX_SUBITEMIMAGES    0x00000002
#define LVS_EX_CHECKBOXES       0x00000004
#define LVS_EX_TRACKSELECT      0x00000008
#define LVS_EX_HEADERDRAGDROP   0x00000010
#define LVS_EX_FULLROWSELECT    0x00000020 // applies to report mode only

/**
 * This message retrieves data about the bounding rectangle for a subitem in a list view control.
 * This message is intended to be used only with list view controls that use the LVS_REPORT style.
 *
 * @param iItem Index of the subitem parent item
 * @param lpRect Long pointer to a RECT structure that receives the subitem bounding rectangle data.
 *   The members of RECT must be initialized according to the member and value relationships shown in
 *   the following table. Member Value top The one-based index of the subitem left Flag value (see
 *   following). Indicates the portion of the list view subitem for which to retrieve the bounding
 *   rectangle. Value Description LVIR_BOUNDS Returns the bounding rectangle of the entire item,
 *   including the icon and label. LVIR_ICON Returns the bounding rectangle of the icon or small icon
 *   LVIR_LABEL Returns the bounding rectangle of the entire item, including the icon and label. This
 *   is identical to LVIR_BOUNDS.
 *
 * @return Nonzero indicates success. Zero indicates otherwise.
 */
#define LVM_GETSUBITEMRECT      (LVM_FIRST + 56)
/**
 * This macro retrieves information about the rectangle that surrounds a subitem in a list view
 * control. This macro is intended to be used only on list view controls that use the LVS_REPORT
 * style.
 *
 * @param hwndLV Handle to a list view control.
 * @param iItem Index of the subitem's parent item.
 * @param iSubItem One-based index of the subitem.
 * @param code Portion of the list view subitem for which to retrieve the bounding rectangle
 *   information. It is one of the following values: Value Description LVIR_BOUNDS Returns the
 *   bounding rectangle of the entire item, including the icon and label. LVIR_ICON Returns the
 *   bounding rectangle of the icon or small icon. LVIR_LABEL Returns the bounding rectangle of the
 *   entire item, including the icon and label. This is identical to LVIR_BOUNDS.
 * @param lpRect Long pointer to a RECT structure that receives the subitem bounding rectangle
 *   information.
 *
 * @return Nonzero indicates success. Zero indicates otherwise.
 */
#define ListView_GetSubItemRect(hwnd, iItem, iSubItem, code, prc) \
        (BOOL)SNDMSG((hwnd), LVM_GETSUBITEMRECT, (WPARAM)(int)(iItem), \
                ((prc) ? ((((LPRECT)(prc))->top = iSubItem), (((LPRECT)(prc))->left = code), (LPARAM)(prc)) : (LPARAM)(LPRECT)NULL))

/**
 * This message determines which list view item or subitem is at a specified position.
 *
 * @param pInfo Pointer to an LVHITTESTINFO structure. The POINT structure within LVHITTESTINFO
 *   should be set to the client coordinates to be hit-tested.
 *
 * @return Returns the index of the item or subitem tested, if any, or -1 otherwise. If an item or
 *   subitem is at the specified coordinates, the members of the LVHITTESTINFO structure will be
 *   filled with the applicable hit data.
 */
#define LVM_SUBITEMHITTEST      (LVM_FIRST + 57)
/**
 * This macro determines which list view item or subitem is located at a specified position.
 *
 * @param hwndLV Handle to the list view control that will be hit-tested.
 * @param pInfo Pointer to an LVHITTESTINFO structure. The POINT structure within LVHITTESTINFO must
 *   be set to the client coordinates to be hit-tested.
 *
 * @return Returns the index of the item or subitem tested, if any, or -1 otherwise. If an item or
 *   subitem is at the specified coordinates, the fields of the LVHITTESTINFO structure will be filled
 *   with the applicable hit information.
 */
#define ListView_SubItemHitTest(hwnd, plvhti) \
        (int)SNDMSG((hwnd), LVM_SUBITEMHITTEST, 0, (LPARAM)(LPLVHITTESTINFO)(plvhti))

/**
 * This message sets the left-to-right order of columns in a list view control.
 *
 * @param iCount Size, in elements, of the buffer at lpiArray
 * @param lpiArray Long pointer to an array that specifies the order in which columns should be
 *   displayed, in left-to-right order. For example, if the contents of the array are {2,0,1}, the
 *   control displays column 2, column 0, and column 1 in that order.
 *
 * @return Nonzero indicates success. Zero indicates otherwise.
 */
#define LVM_SETCOLUMNORDERARRAY (LVM_FIRST + 58)
/**
 * This macro sets the left-to-right order of columns in a list view control.
 *
 * @param hwndLV Handle to a list view control.
 * @param iCount Number of columns in the list view control.
 * @param lpiArray Long pointer to an array that specifies the order in which columns should be
 *   displayed, in left-to-right order. For example, if the contents of the array are {2,0,1}, the
 *   control displays column 2, column 0, and column 1 in that order.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define ListView_SetColumnOrderArray(hwnd, iCount, pi) \
        (BOOL)SNDMSG((hwnd), LVM_SETCOLUMNORDERARRAY, (WPARAM)iCount, (LPARAM)(LPINT)pi)

/**
 * This message retrieves the current left-to-right order of columns in a list view control.
 *
 * @param iCount Number of columns in the list view control.
 * @param lpiArray Long pointer to a buffer that receives the index values of the columns in the
 *   list view control. The buffer must be large enough to hold the total number of columns *
 *   sizeof(int).
 *
 * @return If successful, returns nonzero and the buffer at lpiArray receives the column index of
 *   each column in the control, in the order they appear from left to right. Otherwise, the return
 *   value is zero.
 */
#define LVM_GETCOLUMNORDERARRAY (LVM_FIRST + 59)
/**
 * This macro retrieves the current left-to-right order of columns in a list view control.
 *
 * @param hwndLV Handle to a list view control.
 * @param iCount Number of columns in the list view control.
 * @param lpiArray Long pointer to a buffer that will receive the index values of the columns in the
 *   list view control. The buffer must be large enough to hold the total number of columns *
 *   sizeof(int).
 *
 * @return Returns nonzero and the buffer at lpiArray receives the column index of each column in
 *   the control, in the order they appear from left to right if successful. Otherwise, the return
 *   value is zero.
 */
#define ListView_GetColumnOrderArray(hwnd, iCount, pi) \
        (BOOL)SNDMSG((hwnd), LVM_GETCOLUMNORDERARRAY, (WPARAM)iCount, (LPARAM)(LPINT)pi)

/**
 * This message calculates the approximate width and height required to display a specified number
 * of items.
 *
 * @param iCount Number of items to be displayed in the control. If this parameter is set to -1, the
 *   message uses the total number of items in the control.
 * @param cx and cy Specify the proposed dimensions of the control, in pixels. Either parameter can
 *   beset to -1 to allow the message to use the current width or height value.
 *
 * @return Returns a DWORD value that holds the approximate width and height needed to display the
 *   items, in pixels.
 *
 * Setting the size of the list view control based on the dimensions provided by this message can
 * optimize redraw and reduce flicker.
 */
#define LVM_APPROXIMATEVIEWRECT (LVM_FIRST + 64)
/**
 * This macro calculates the approximate width and height required to display a specified number of
 * items.
 *
 * @param hwndLV Handle to a list view control.
 * @param iCount Number of items to be displayed in the control. If this parameter is -1, the
 *   message uses the total number of items in the control.
 * @param cx and cy Proposed dimensions of the control, in pixels. Either parameter can be -1 to
 *   allow the message to use the current width or height value.
 *
 * @return Returns a DWORD value that holds the approximate width and height needed to display the
 *   items, in pixels.
 */
#define ListView_ApproximateViewRect(hwnd, iWidth, iHeight, iCount) \
        (DWORD)SNDMSG((hwnd), LVM_APPROXIMATEVIEWRECT, iCount, MAKELPARAM(iWidth, iHeight))
#endif      // _WIN32_IE >= 0x0300

#if (_WIN32_IE >= 0x0400)
/**
 * This message retrieves the selection mark from a list view control.
 *
 * @return Returns the zero-based selection mark, or -1 if there is no selection mark.
 *
 * The selection mark is the item index from which a multiple selection starts.
 */
#define LVM_GETSELECTIONMARK    (LVM_FIRST + 66)
/**
 * This macro retrieves the selection mark from a list view control.
 *
 * @param hwndLV Handle to a list view control.
 *
 * @return Returns the zero-based selection mark, or -1 if there is no selection mark.
 *
 * The selection mark is the item index from which a multiple selection starts.
 */
#define ListView_GetSelectionMark(hwnd) \
    (int)SNDMSG((hwnd), LVM_GETSELECTIONMARK, 0, 0)

/**
 * This message sets the selection mark in a list view control.
 *
 * @param iIndex Zero-based index of the new selection mark The selection mark is the item index
 *   from which a multiple selection starts. This message does not affect the selection state of the
 *   item.
 *
 * @return Returns the previous selection mark, or -1 if there is no previous selection mark.
 */
#define LVM_SETSELECTIONMARK    (LVM_FIRST + 67)
/**
 * This macro sets the selection mark in a list view control.
 *
 * @param hwndLV Handle to a list view control.
 * @param iIndex Zero-based index of the list view item to be selected.
 *
 * @return Returns the previous selection mark, or -1 if there is no previous selection mark.
 *
 * The selection mark is the item index from which a multiple selection starts. This macro does not
 * affect the selection state of the item.
 */
#define ListView_SetSelectionMark(hwnd, i) \
    (int)SNDMSG((hwnd), LVM_GETSELECTIONMARK, 0, (LPARAM)i)
#endif      // _WIN32_IE >= 0x0400

#if (_WIN32_IE >= 0x0300)
#define LPNM_LISTVIEW   LPNMLISTVIEW
#define NM_LISTVIEW     NMLISTVIEW
#else
#define tagNMLISTVIEW   _NM_LISTVIEW
#define    NMLISTVIEW    NM_LISTVIEW
#define  LPNMLISTVIEW  LPNM_LISTVIEW
#endif

/**
 * This structure contains information about a list view notification message. This structure is the
 * same as the NM_LISTVIEW structure, but has been renamed to fit standard naming conventions.
 */
typedef struct tagNMLISTVIEW
{
    /**
     * NMHDR structure that contains information about this notification message.
     */
    NMHDR   hdr;
    /**
     * Identifier of the list view item, or ?1 if not used.
     */
    int     iItem;
    /**
     * Identifier of the subitem, or zero if none.
     */
    int     iSubItem;
    /**
     * Specifies the new item state. This member is zero for notification messages that do not use it.
     */
    UINT    uNewState;
    /**
     * Specifies the old item state. This member is zero for notification messages that do not use it.
     */
    UINT    uOldState;
    /**
     * Set of flags that indicate the item attributes that have changed. This member is zero for
     * notification messages that do not use it. Otherwise, it can have the same values as the mask
     * member of the LVITEM structure.
     */
    UINT    uChanged;
    /**
     * Specifies a POINT structure that indicates the location at which the event occurred. This member
     * is undefined for notification messages that do not use it.
     */
    POINT   ptAction;
    /**
     * Specifies the item's application-defined 32-bit value. This member is undefined for notification
     * messages that do not use it.
     */
    LPARAM  lParam;
} NMLISTVIEW, FAR *LPNMLISTVIEW;


#if (_WIN32_IE >= 0x0300)
/**
 * This structure contains information specific to an NM_CUSTOMDRAW notification message sent by a
 * list view control.
 */
typedef struct tagNMLVCUSTOMDRAW
{
    /**
     * NMCUSTOMDRAW structure that contains general Custom Draw information.
     */
    NMCUSTOMDRAW nmcd;
    /**
     * COLORREF value that represents the color that is used to display text foreground in the list view
     * control.
     */
    COLORREF clrText;
    /**
     * COLORREF value that represents the color that is used to display text background in the list view
     * control.
     */
    COLORREF clrTextBk;
#if (_WIN32_IE >= 0x0400)
    int iSubItem;
#endif
} NMLVCUSTOMDRAW, *LPNMLVCUSTOMDRAW;

/**
 * This structure contains information used to update the cached item information for use with a
 * virtual list view.
 */
typedef struct tagNMLVCACHEHINT
{
    /**
     * NMHDR structure that contains information about this notification message.
     */
    NMHDR   hdr;
    /**
     * Starting index of the requested range of items. This value is inclusive.
     */
    int     iFrom;
    /**
     * Ending index of the requested range of items. This value is inclusive.
     */
    int     iTo;
} NMLVCACHEHINT, FAR *LPNMLVCACHEHINT;

#define LPNM_CACHEHINT  LPNMLVCACHEHINT
#define PNM_CACHEHINT   LPNMLVCACHEHINT
#define NM_CACHEHINT    NMLVCACHEHINT

/**
 * This structure that contains information the owner needs to find items requested by a virtual
 * list view control. This structure is sent to the owner during notification using the
 * LVN_ODFINDITEM message.
 */
typedef struct tagNMLVFINDITEM
{
    /**
     * NMHDR structure that contains information on this notification message.
     */
    NMHDR   hdr;
    /**
     * Item index to act as the start of the search.
     */
    int     iStart;
    /**
     * LVFINDINFO structure that contains information necessary to perform a search.
     */
    LVFINDINFO lvfi;
} NMLVFINDITEM, FAR *LPNMLVFINDITEM;

#define PNM_FINDITEM    LPNMLVFINDITEM
#define LPNM_FINDITEM   LPNMLVFINDITEM
#define NM_FINDITEM     NMLVFINDITEM

/**
 * This structure that contains information for use in processing the LVN_ODSTATECHANGED
 * notification message.
 */
typedef struct tagNMLVODSTATECHANGE
{
    /**
     * NMHDR structure that contains additional information about the notification message.
     */
    NMHDR hdr;
    /**
     * Zero-based index of the first item in the range of items.
     */
    int iFrom;
    /**
     * Zero-based index of the last item in the range of items.
     */
    int iTo;
    UINT uNewState;
    UINT uOldState;
} NMLVODSTATECHANGE, FAR *LPNMLVODSTATECHANGE;

#define PNM_ODSTATECHANGE   LPNMLVODSTATECHANGE
#define LPNM_ODSTATECHANGE  LPNMLVODSTATECHANGE
#define NM_ODSTATECHANGE    NMLVODSTATECHANGE
#endif      // _WIN32_IE >= 0x0300


/**
 * This notification message notifies a list view control parent window that an item is changing. It
 * is sent in the form of a WM_NOTIFY message.
 *
 * @param pnmv Pointer to an NMLISTVIEW structure that identifies the item and specifies which of
 *   its attributes are changing.
 *
 * @return TRUE prevents the change. FALSE accepts the change.
 */
#define LVN_ITEMCHANGING        (LVN_FIRST-0)
/**
 * This notification message notifies a list view control parent window that an item has changed. It
 * is sent in the form of a WM_NOTIFY message.
 *
 * @param pnmv Pointer to an NMLISTVIEW structure that identifies the item and specifies which of
 *   its attributes have changed.
 *
 * @return None
 */
#define LVN_ITEMCHANGED         (LVN_FIRST-1)
/**
 * This notification message notifies a list view control parent window that a new item was
 * inserted. It is sent in the form of a WM_NOTIFY message.
 *
 * @param pnmv Pointer to an NMLISTVIEW structure. The iItem member identifies the new item, and the
 *   other members are zero.
 *
 * @return None
 */
#define LVN_INSERTITEM          (LVN_FIRST-2)
/**
 * This notification message notifies a list view control parent window that an item was deleted. It
 * is sent in the form of a WM_NOTIFY message.
 *
 * @param pnmv Pointer to an NMLISTVIEW structure. The iItem member identifies the item being
 *   deleted. All other members of this structure are zero.
 *
 * @return None
 */
#define LVN_DELETEITEM          (LVN_FIRST-3)
/**
 * This notification message notifies a list view control parent window that all items in the
 * control were deleted. It is sent in the form of a WM_NOTIFY message.
 *
 * @param pnmv Pointer to an NMLISTVIEW structure. The iItem member is -1, and the other members are
 *   zero. A list view control sends the LVN_DELETEALLITEMS notification message when it is destroyed
 *   or when it receives the LVM_DELETEALLITEMS message. If LVN_DELETEALLITEMS does not return TRUE,
 *   the control will also send an LVN_DELETEITEM notification message as each item is deleted.
 *
 * @return To suppress subsequent LVN_DELETEITEM notification messages, return TRUE. To receive
 *   subsequent LVN_DELETEITEM notification messages, return FALSE.
 */
#define LVN_DELETEALLITEMS      (LVN_FIRST-4)
#define LVN_BEGINLABELEDITA     (LVN_FIRST-5)
#define LVN_BEGINLABELEDITW     (LVN_FIRST-75)
#define LVN_ENDLABELEDITA       (LVN_FIRST-6)
#define LVN_ENDLABELEDITW       (LVN_FIRST-76)
/**
 * This notification message notifies a list view control parent window that a column was tapped. It
 * is sent in the form of a WM_NOTIFY message.
 *
 * @param pnmv Pointer to an NMLISTVIEW structure. The iItem member is -1, and the iSubItem member
 *   identifies the column. All other members are zero.
 *
 * @return None
 */
#define LVN_COLUMNCLICK         (LVN_FIRST-8)
/**
 * This notification message notifies a list view control parent window that a drag and drop
 * operation is being initiated. It is sent in the form of a WM_NOTIFY message.
 *
 * @param pnmv Pointer to an NMLISTVIEW structure. The iItem member identifies the item being
 *   dragged, and the other members are zero.
 *
 * @return None
 */
#define LVN_BEGINDRAG           (LVN_FIRST-9)
#define LVN_BEGINRDRAG          (LVN_FIRST-11)

#if (_WIN32_IE >= 0x0300)
/**
 * This notification message is sent by a virtual list view control when the contents of its display
 * area have changed. For example, a list view control sends this notification when the user scrolls
 * the control display. This message is sent in the form of a WM_NOTIFY message.
 *
 * @param pCachehint Pointer to an NMLVCACHEHINT structure that contains data about the range of
 *   items to be cached.
 *
 * @return The application receiving this notification must return zero.
 *
 * Handling this message allows the application to update the item data held in cache so that it is
 * readily available when an LVN_GETDISPINFO notification message is sent.
 *
 * Note that this message is not always an exact representation of the items that will be requested
 * by LVN_GETDISPINFO. Therefore, if the requested item is not cached while handling
 * LVN_GETDISPINFO, the application must be prepared to supply the requested data from a source
 * outside the cache.
 */
#define LVN_ODCACHEHINT         (LVN_FIRST-13)
#define LVN_ODFINDITEMA         (LVN_FIRST-52)
#define LVN_ODFINDITEMW         (LVN_FIRST-79)

/**
 * This notification message is sent by a list view control when the user activates an item. It is
 * sent in the form of a WM_NOTIFY message.
 *
 * @param lpnmlv Long pointer to an NMLISTVIEW structure that contains notification data. The iItem,
 *   iSubItem and ptAction members contain data about the activated item. If the item was activated
 *   from the keyboard, the ptAction member will contain -1 in its x and y members.
 *
 * @return The application receiving this notification must return zero.
 */
#define LVN_ITEMACTIVATE        (LVN_FIRST-14)
/**
 * This notification message is sent by a list view control when the state of an item or range of
 * items has changed. It is sent in the form of a WM_NOTIFY message.
 *
 * @param lpStateChange Long pointer to an NMLVODSTATECHANGE structure that contains data about the
 *   item or items that have changed
 *
 * @return The application receiving this notification must return zero.
 */
#define LVN_ODSTATECHANGED      (LVN_FIRST-15)

#ifdef UNICODE
/**
 * This notification message is sent by a virtual list view control when it needs the owner to find
 * a particular callback item. For example, the control will send this notification when the it
 * receives shortcut keyboard input, or when it receives an LVM_FINDITEM message.
 *
 * @param pFindInfo Pointer to an NMLVFINDITEM structure that includes data used for the search.
 *
 * @return Return the index of the item found, or -1 if no item is found
 *
 * Search data is sent in the form of an LVFINDINFO structure, which is a member of the NMLVFINDITEM
 * structure.
 */
#define LVN_ODFINDITEM          LVN_ODFINDITEMW
#else
/**
 * This notification message is sent by a virtual list view control when it needs the owner to find
 * a particular callback item. For example, the control will send this notification when the it
 * receives shortcut keyboard input, or when it receives an LVM_FINDITEM message.
 *
 * @param pFindInfo Pointer to an NMLVFINDITEM structure that includes data used for the search.
 *
 * @return Return the index of the item found, or -1 if no item is found
 *
 * Search data is sent in the form of an LVFINDINFO structure, which is a member of the NMLVFINDITEM
 * structure.
 */
#define LVN_ODFINDITEM          LVN_ODFINDITEMA
#endif
#endif      // _WIN32_IE >= 0x0300

#define LVN_GETDISPINFOA        (LVN_FIRST-50)
#define LVN_GETDISPINFOW        (LVN_FIRST-77)
#define LVN_SETDISPINFOA        (LVN_FIRST-51)
#define LVN_SETDISPINFOW        (LVN_FIRST-78)

#ifdef UNICODE
/**
 * This notification message notifies a list view control parent window about the start of label
 * editing for an item. It is sent in the form of a WM_NOTIFY message.
 *
 * @param pdi Pointer to an NMLVDISPINFO structure. The item member of this structure is an LVITEM
 *   structure whose iItem member identifies the item being edited.
 *
 * @return TRUE prevents the user from editing the label. FALSE enables the user to edit the label.
 */
#define LVN_BEGINLABELEDIT      LVN_BEGINLABELEDITW
/**
 * This notification message notifies a list view control parent window about the end of label
 * editing for an item. It is sent in the form of a WM_NOTIFY message.
 *
 * @param pdi Pointer to an NMLVDISPINFO structure. The item member of this structure is an LVITEM
 *   structure whose iItem member identifies the item being edited. The pszText member of item
 *   contains a valid value when the LVN_ENDLABELEDIT message is sent, regardless of whether the
 *   LVIF_TEXT flag is set in the mask member of the LVITEM structure. If the user cancels editing,
 *   the pszText member of the LVITEM structure is NULL; otherwise, pszText is the address of the
 *   edited text.
 *
 * @return If the pszText member of the LVITEM structure is non-NULL, return TRUE to set the item's
 *   label to the edited text. Return FALSE to reject the edited text and revert to the original
 *   label. If the pszText member of the LVITEM structure is NULL, the return value is ignored.
 */
#define LVN_ENDLABELEDIT        LVN_ENDLABELEDITW
/**
 * This notification message requests a list view control parent window to provide data needed to
 * display or sort an item. It is sent in the form of a WM_NOTIFY message.
 *
 * @param pnmv Pointer to an NMLVDISPINFO structure. On input, the LVITEM structure contained in
 *   this structure specifies the type of data required and identifies the item or subitem of
 *   interest. Use the LVITEM structure to return the requested data to the control. If your message
 *   handler sets the LVIF_DI_SETITEM flag in the mask member of the LVITEM structure, the list view
 *   control stores the requested data and will not ask for it again.
 *
 * @return None
 *
 * A list view control sends the LVN_GETDISPINFO notification to retrieve item data stored by the
 * application rather than the control. The data can be text or icon data for an item. It can also
 * be item state data. See the LVM_SETCALLBACKMASK message for more information on implementing item
 * state on a callback basis.
 *
 * For more information on list view callbacks, see the Windows CE User Interface Services Guide.
 */
#define LVN_GETDISPINFO         LVN_GETDISPINFOW
/**
 * This notification message notifies a list view control parent window that it must update the data
 * it maintains for an item. It is sent in the form of a WM_NOTIFY message.
 *
 * @param pnmv Pointer to an NMLVDISPINFO structure that specifies data for the changed item. The
 *   item member of this structure is an LVITEM structure that contains data about the item that was
 *   changed. The pszText member of item contains a valid value, regardless of whether the LVIF_TEXT
 *   flag is set in the mask member of this structure.
 *
 * @return None
 */
#define LVN_SETDISPINFO         LVN_SETDISPINFOW
#else
/**
 * This notification message notifies a list view control parent window about the start of label
 * editing for an item. It is sent in the form of a WM_NOTIFY message.
 *
 * @param pdi Pointer to an NMLVDISPINFO structure. The item member of this structure is an LVITEM
 *   structure whose iItem member identifies the item being edited.
 *
 * @return TRUE prevents the user from editing the label. FALSE enables the user to edit the label.
 */
#define LVN_BEGINLABELEDIT      LVN_BEGINLABELEDITA
/**
 * This notification message notifies a list view control parent window about the end of label
 * editing for an item. It is sent in the form of a WM_NOTIFY message.
 *
 * @param pdi Pointer to an NMLVDISPINFO structure. The item member of this structure is an LVITEM
 *   structure whose iItem member identifies the item being edited. The pszText member of item
 *   contains a valid value when the LVN_ENDLABELEDIT message is sent, regardless of whether the
 *   LVIF_TEXT flag is set in the mask member of the LVITEM structure. If the user cancels editing,
 *   the pszText member of the LVITEM structure is NULL; otherwise, pszText is the address of the
 *   edited text.
 *
 * @return If the pszText member of the LVITEM structure is non-NULL, return TRUE to set the item's
 *   label to the edited text. Return FALSE to reject the edited text and revert to the original
 *   label. If the pszText member of the LVITEM structure is NULL, the return value is ignored.
 */
#define LVN_ENDLABELEDIT        LVN_ENDLABELEDITA
/**
 * This notification message requests a list view control parent window to provide data needed to
 * display or sort an item. It is sent in the form of a WM_NOTIFY message.
 *
 * @param pnmv Pointer to an NMLVDISPINFO structure. On input, the LVITEM structure contained in
 *   this structure specifies the type of data required and identifies the item or subitem of
 *   interest. Use the LVITEM structure to return the requested data to the control. If your message
 *   handler sets the LVIF_DI_SETITEM flag in the mask member of the LVITEM structure, the list view
 *   control stores the requested data and will not ask for it again.
 *
 * @return None
 *
 * A list view control sends the LVN_GETDISPINFO notification to retrieve item data stored by the
 * application rather than the control. The data can be text or icon data for an item. It can also
 * be item state data. See the LVM_SETCALLBACKMASK message for more information on implementing item
 * state on a callback basis.
 *
 * For more information on list view callbacks, see the Windows CE User Interface Services Guide.
 */
#define LVN_GETDISPINFO         LVN_GETDISPINFOA
/**
 * This notification message notifies a list view control parent window that it must update the data
 * it maintains for an item. It is sent in the form of a WM_NOTIFY message.
 *
 * @param pnmv Pointer to an NMLVDISPINFO structure that specifies data for the changed item. The
 *   item member of this structure is an LVITEM structure that contains data about the item that was
 *   changed. The pszText member of item contains a valid value, regardless of whether the LVIF_TEXT
 *   flag is set in the mask member of this structure.
 *
 * @return None
 */
#define LVN_SETDISPINFO         LVN_SETDISPINFOA
#endif

#ifdef UNDER_CE
#define LVBD_DRAGSELECT         200
#endif // UNDER_CE

#define LVIF_DI_SETITEM         0x1000

#if (_WIN32_IE >= 0x0300)
#define LV_DISPINFOA    NMLVDISPINFOA
#define LV_DISPINFOW    NMLVDISPINFOW
#else
#define tagLVDISPINFO   _LV_DISPINFO
#define NMLVDISPINFOA    LV_DISPINFOA
#define tagLVDISPINFOW  _LV_DISPINFOW
#define NMLVDISPINFOW    LV_DISPINFOW
#endif

#define LV_DISPINFO     NMLVDISPINFO

typedef struct tagLVDISPINFO {
    NMHDR hdr;
    LVITEMA item;
} NMLVDISPINFOA, FAR *LPNMLVDISPINFOA;

typedef struct tagLVDISPINFOW {
    NMHDR hdr;
    LVITEMW item;
} NMLVDISPINFOW, FAR * LPNMLVDISPINFOW;

#ifdef UNICODE
#define  NMLVDISPINFO           NMLVDISPINFOW
#else
#define  NMLVDISPINFO           NMLVDISPINFOA
#endif

/**
 * This notification message notifies a list view control parent window that a key has been pressed.
 * It is sent in the form of a WM_NOTIFY message.
 *
 * @param pnkd Pointer to an NMLVKEYDOWN structure.
 *
 * @return None
 */
#define LVN_KEYDOWN             (LVN_FIRST-55)

#if (_WIN32_IE >= 0x0300)
#define LV_KEYDOWN              NMLVKEYDOWN
#else
#define tagLVKEYDOWN            _LV_KEYDOWN
#define NMLVKEYDOWN              LV_KEYDOWN
#endif

/**
 * This structure that contains information used in processing the LVN_KEYDOWN notification message.
 */
typedef struct tagLVKEYDOWN
{
    /**
     * NMHDR structure that contains additional information about the notification message.
     */
    NMHDR hdr;
    /**
     * Virtual-key code.
     */
    WORD wVKey;
    /**
     * Set to zero.
     */
    UINT flags;
} NMLVKEYDOWN, FAR *LPNMLVKEYDOWN;

#if (_WIN32_IE >= 0x0300)
/**
 * This message notifies a list view control parent window that a bounding box, or marquee,
 * selection has begun. It is sent in the form of a WM_NOTIFY message.
 *
 * @param pnmv Pointer to an NMHDR structure.
 *
 * @return To accept the notification message, return zero. To quit the bounding box selection,
 *   return nonzero.
 *
 * A "bounding box selection" is the process of clicking the list view window's client area and
 * dragging to select multiple items simultaneously.
 */
#define LVN_MARQUEEBEGIN        (LVN_FIRST-56)
#endif

#endif // NOLISTVIEW

//====== TREEVIEW CONTROL =====================================================

#ifndef NOTREEVIEW

#ifdef _WIN32
#define WC_TREEVIEWA            "SysTreeView32"
#define WC_TREEVIEWW            L"SysTreeView32"

#ifdef UNICODE
#define  WC_TREEVIEW            WC_TREEVIEWW
#else
#define  WC_TREEVIEW            WC_TREEVIEWA
#endif

#else
#define WC_TREEVIEW             "SysTreeView"
#endif

// begin_r_commctrl

#define TVS_HASBUTTONS          0x0001
#define TVS_HASLINES            0x0002
#define TVS_LINESATROOT         0x0004
#define TVS_EDITLABELS          0x0008
#define TVS_DISABLEDRAGDROP     0x0010
#define TVS_SHOWSELALWAYS       0x0020
#if (_WIN32_IE >= 0x0300)
#define TVS_RTLREADING          0x0040

#define TVS_NOTOOLTIPS          0x0080
#define TVS_CHECKBOXES          0x0100
#define TVS_TRACKSELECT         0x0200
#if (_WIN32_IE >= 0x0400)
#define TVS_SINGLEEXPAND        0x0400
#endif

#endif

// end_r_commctrl

typedef struct _TREEITEM FAR* HTREEITEM;

#define TVIF_TEXT               0x0001
#define TVIF_IMAGE              0x0002
#define TVIF_PARAM              0x0004
#define TVIF_STATE              0x0008
#define TVIF_HANDLE             0x0010
#define TVIF_SELECTEDIMAGE      0x0020
#define TVIF_CHILDREN           0x0040

#define TVIS_SELECTED           0x0002
#define TVIS_CUT                0x0004
#define TVIS_DROPHILITED        0x0008
#define TVIS_BOLD               0x0010
#define TVIS_EXPANDED           0x0020
#define TVIS_EXPANDEDONCE       0x0040
#if (_WIN32_IE >= 0x0300)
#define TVIS_EXPANDPARTIAL      0x0080
#endif

#define TVIS_OVERLAYMASK        0x0F00
#define TVIS_STATEIMAGEMASK     0xF000
#define TVIS_USERMASK           0xF000


#define I_CHILDRENCALLBACK  (-1)

#if (_WIN32_IE >= 0x0300)
#define LPTV_ITEMW              LPTVITEMW
#define LPTV_ITEMA              LPTVITEMA
#define TV_ITEMW                TVITEMW
#define TV_ITEMA                TVITEMA
#else
#define tagTVITEMA             _TV_ITEMA
#define    TVITEMA              TV_ITEMA
#define  LPTVITEMA            LPTV_ITEMA
#define tagTVITEMW             _TV_ITEMW
#define    TVITEMW              TV_ITEMW
#define  LPTVITEMW            LPTV_ITEMW
#endif

#define LPTV_ITEM               LPTVITEM
#define TV_ITEM                 TVITEM

typedef struct tagTVITEMA {
    UINT      mask;
    HTREEITEM hItem;
    UINT      state;
    UINT      stateMask;
    LPSTR     pszText;
    int       cchTextMax;
    int       iImage;
    int       iSelectedImage;
    int       cChildren;
    LPARAM    lParam;
} TVITEMA, FAR *LPTVITEMA;

typedef struct tagTVITEMW {
    UINT      mask;
    HTREEITEM hItem;
    UINT      state;
    UINT      stateMask;
    LPWSTR    pszText;
    int       cchTextMax;
    int       iImage;
    int       iSelectedImage;
    int       cChildren;
    LPARAM    lParam;
} TVITEMW, FAR *LPTVITEMW;

#ifdef UNICODE
#define  TVITEM                 TVITEMW
#define  LPTVITEM               LPTVITEMW
#else
#define  TVITEM                 TVITEMA
#define  LPTVITEM               LPTVITEMA
#endif


#define TVI_ROOT                ((HTREEITEM)0xFFFF0000)
#define TVI_FIRST               ((HTREEITEM)0xFFFF0001)
#define TVI_LAST                ((HTREEITEM)0xFFFF0002)
#define TVI_SORT                ((HTREEITEM)0xFFFF0003)

#if (_WIN32_IE >= 0x0300)
#define LPTV_INSERTSTRUCTA      LPTVINSERTSTRUCTA
#define LPTV_INSERTSTRUCTW      LPTVINSERTSTRUCTW
#define TV_INSERTSTRUCTA        TVINSERTSTRUCTA
#define TV_INSERTSTRUCTW        TVINSERTSTRUCTW
#else
#define tagTVINSERTSTRUCTA     _TV_INSERTSTRUCTA
#define    TVINSERTSTRUCTA      TV_INSERTSTRUCTA
#define  LPTVINSERTSTRUCTA    LPTV_INSERTSTRUCTA
#define tagTVINSERTSTRUCTW     _TV_INSERTSTRUCTW
#define    TVINSERTSTRUCTW      TV_INSERTSTRUCTW
#define  LPTVINSERTSTRUCTW    LPTV_INSERTSTRUCTW
#endif

#define TV_INSERTSTRUCT         TVINSERTSTRUCT
#define LPTV_INSERTSTRUCT       LPTVINSERTSTRUCT

typedef struct tagTVINSERTSTRUCTA {
    HTREEITEM hParent;
    HTREEITEM hInsertAfter;
    TV_ITEMA item;
} TVINSERTSTRUCTA, FAR *LPTVINSERTSTRUCTA;

typedef struct tagTVINSERTSTRUCTW {
    HTREEITEM hParent;
    HTREEITEM hInsertAfter;
    TV_ITEMW item;
} TVINSERTSTRUCTW, FAR *LPTVINSERTSTRUCTW;

#ifdef UNICODE
#define  TVINSERTSTRUCT         TVINSERTSTRUCTW
#define  LPTVINSERTSTRUCT       LPTVINSERTSTRUCTW
#else
#define  TVINSERTSTRUCT         TVINSERTSTRUCTA
#define  LPTVINSERTSTRUCT       LPTVINSERTSTRUCTA
#endif

#define TVM_INSERTITEMA         (TV_FIRST + 0)
#define TVM_INSERTITEMW         (TV_FIRST + 50)
#ifdef UNICODE
/**
 * This message inserts a new item in a tree view control. You can send this message explicitly or
 * by using the TreeView_InsertItem macro.
 *
 * @param lpis Long pointer to a TVINSERTSTRUCT structure that specifies the attributes of the tree
 *   view item.
 *
 * @return The handle to the new item indicates success. NULL indicates otherwise.
 */
#define  TVM_INSERTITEM         TVM_INSERTITEMW
#else
/**
 * This message inserts a new item in a tree view control. You can send this message explicitly or
 * by using the TreeView_InsertItem macro.
 *
 * @param lpis Long pointer to a TVINSERTSTRUCT structure that specifies the attributes of the tree
 *   view item.
 *
 * @return The handle to the new item indicates success. NULL indicates otherwise.
 */
#define  TVM_INSERTITEM         TVM_INSERTITEMA
#endif

/**
 * This macro inserts a new item in a tree-view control. You can use this macro or send the
 * TVM_INSERTITEM message explicitly.
 *
 * @param hwndTV Handle to the tree view control.
 * @param lpis Long pointer to a TVINSERTSTRUCT structure that specifies the attributes of the tree
 *   view item.
 *
 * @return The handle to the new item indicates success. NULL indicates failure.
 */
#define TreeView_InsertItem(hwnd, lpis) \
    (HTREEITEM)SNDMSG((hwnd), TVM_INSERTITEM, 0, (LPARAM)(LPTV_INSERTSTRUCT)(lpis))


/**
 * This message removes an item from a tree view control. You can send this message explicitly or by
 * using the TreeView_DeleteItem or TreeView_DeleteAllItems macro.
 *
 * @param hitem Handle to the item to delete. If hitem is the TVI_ROOT value, all items are deleted
 *   from the tree view control.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define TVM_DELETEITEM          (TV_FIRST + 1)
/**
 * This macro removes an item from a tree-view control. You can use this macro, the
 * TreeView_DeleteAllItems macro, or send the TVM_DELETEITEM message explicitly.
 *
 * @param hwndTV Handle to the tree view control.
 * @param hitem Handle to the item to delete. If hitem is the TVI_ROOT value, all items are deleted
 *   from the tree view control.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * If the item label is being edited, the edit operation is canceled and the parent window receives
 * the TVN_ENDLABELEDIT notification message. The parent window receives a TVN_DELETEITEM
 * notification message when the item is removed.
 */
#define TreeView_DeleteItem(hwnd, hitem) \
    (BOOL)SNDMSG((hwnd), TVM_DELETEITEM, 0, (LPARAM)(HTREEITEM)(hitem))


/**
 * This macro removes an item from a tree-view control. You can use this macro, the
 * TreeView_DeleteItem macro, or send the TVM_DELETEITEM message explicitly.
 *
 * @param hwndTV Handle to the tree view control.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * If the item label is being edited, the edit operation is canceled and the parent window receives
 * the TVN_ENDLABELEDIT notification message. The parent window receives a TVN_DELETEITEM
 * notification message when the item is removed.
 */
#define TreeView_DeleteAllItems(hwnd) \
    (BOOL)SNDMSG((hwnd), TVM_DELETEITEM, 0, (LPARAM)TVI_ROOT)


/**
 * This message expands or collapses the list of child items, if any, associated with the specified
 * parent item. You can send this message explicitly or by using the TreeView_Expand macro.
 *
 * @param flag Action flag. It is one or more of the following values: Value Description
 *   TVE_COLLAPSE Collapses the list. TVE_COLLAPSERESET Collapses the list and removes the child
 *   items. This flag must be used with the TVE_COLLAPSE flag. TVE_EXPAND Expands the list.
 *   TVE_EXPANDPARTIAL Version 4.70. Partially expands the list. In this state, the child items are
 *   visible and the parent item's plus symbol is displayed. This flag must be used in combination
 *   with the TVE_EXPAND flag. TVE_TOGGLE Collapses the list if it is expanded or expands it if it is
 *   collapsed.
 * @param hItem Handle to the parent item to expand or collapse.
 *
 * @return Nonzero indicates that a change took place. Zero indicates otherwise.
 *
 * In Windows CE versions 2.0 and later, you can use the new TVE_EXPANDPARTIAL flag in the flag
 * parameter.
 *
 * When the TVE_EXPANDPARTIAL flag is set, the child items are visible and parent item's plus symbol
 * is displayed. This flag must be used in combination with the TVE_EXPAND flag.
 *
 * The TVM_EXPAND message will cause the TVN_ITEMEXPANDING and TVN_ITEMEXPANDED notification
 * messages to be generated if the item being expanded does not have the TVIS_EXPANDEDONCE state bit
 * set. This state gets set when a parent item is expanded for the first time. Using TVE_COLLAPSE
 * and TVE_COLLAPSERESET with TVM_EXPAND will cause the TVIS_EXPANDEDONCE state to be reset.
 */
#define TVM_EXPAND              (TV_FIRST + 2)
/**
 * This macro expands or collapses the list of child items, if any, associated with the specified
 * parent item. You can use this macro or send the TVM_EXPAND message explicitly.
 *
 * @param hwndTV Handle to a tree view control.
 * @param hItem Handle to the parent item that will be expanded or collapsed.
 * @param flag Action flag. For a list of possible values, see the description of the flag parameter
 *   in TVM_EXPAND. Value Description TVE_EXPANDPARTIAL Child items are visible and parent item's plus
 *   symbol is displayed. This flag must be used in combination with the TVE_EXPAND flag.
 *
 * @return Nonzero indicates that a change took place. Zero indicates otherwise.
 *
 * The TreeView_Expand macro will cause the TVN_ITEMEXPANDING and TVN_ITEMEXPANDED notification
 * messages to be generated if the item being expanded does not have the TVIS_EXPANDEDONCE state bit
 * set. This state gets set when a parent item is expanded for the first time. Using TVE_COLLAPSE
 * and TVE_COLLAPSERESET with TreeView_Expand will cause the TVIS_EXPANDEDONCE state to be reset.
 *
 * If the item already has the TVIS_EXPANDEDONCE state set, the TreeView_Expand macro will not cause
 * the TVN_ITEMEXPANDING and TVN_ITEMEXPANDED notification messages to be generated.
 */
#define TreeView_Expand(hwnd, hitem, code) \
    (BOOL)SNDMSG((hwnd), TVM_EXPAND, (WPARAM)code, (LPARAM)(HTREEITEM)(hitem))


#define TVE_COLLAPSE            0x0001
#define TVE_EXPAND              0x0002
#define TVE_TOGGLE              0x0003
#if (_WIN32_IE >= 0x0300)
#define TVE_EXPANDPARTIAL       0x4000
#endif
#define TVE_COLLAPSERESET       0x8000


/**
 * This message retrieves the bounding rectangle for a tree view item and indicates whether the item
 * is visible. You can send this message explicitly or by using the TreeView_GetItemRect macro.
 *
 * @param fItemRect Boolean value that specifies the portion of the item for which to retrieve the
 *   bounding rectangle. If set to TRUE, the bounding rectangle includes only the text of the item. If
 *   set to FALSE, it includes the entire line that the item occupies in the tree view control.
 * @param prc Pointer to a RECT structure that, when sending the message, contains the handle of the
 *   item to retrieve the rectangle for. For more information on how to place the item handle in this
 *   parameter, see the Remarks section. After returning from the message, this parameter contains the
 *   bounding rectangle. The coordinates are relative to the upper-left corner of the tree view
 *   control.
 *
 * @return TRUE indicates that the item is visible and the bounding rectangle was successfully
 *   retrieved. Otherwise, the message returns FALSE and does not retrieve the bounding rectangle.
 *
 * When sending this message, the prc parameter contains the handle of the item that the rectangle
 * is being retrieved for. The handle is placed in prc as shown in the following code example:
 *
 *     RECT rc;
 *     *(HTREEITEM*)&rc = hTreeItem;
 *     SendMessage(hwndTreeView, TVM_GETITEMRECT, FALSE, (LPARAM)&rc);
 */
#define TVM_GETITEMRECT         (TV_FIRST + 4)
/**
 * This macro retrieves the bounding rectangle for a tree-view item and indicates whether the item
 * is visible. You can use this macro or send the TVM_GETITEMRECT message explicitly.
 *
 * @param hwndTV Handle to the tree view control.
 * @param hitem Handle to the tree view item.
 * @param prc Pointer to a RECT structure that receives the bounding rectangle. The coordinates are
 *   relative to the upper-left corner of the tree view control.
 * @param fItemRect Value that specifies the portion of the item for which to retrieve the bounding
 *   rectangle. If set to TRUE, the bounding rectangle includes only the text of the item. If set to
 *   FALSE, it includes the entire line that the item occupies in the tree view control.
 *
 * @return TRUE indicates that the item is visible and the bounding rectangle is successfully
 *   retrieved. FALSE indicates that the TVM_GETITEMRECT message does not retrieve the bounding
 *   rectangle.
 */
#define TreeView_GetItemRect(hwnd, hitem, prc, code) \
    (*(HTREEITEM FAR *)prc = (hitem), (BOOL)SNDMSG((hwnd), TVM_GETITEMRECT, (WPARAM)(code), (LPARAM)(RECT FAR*)(prc)))


/**
 * This message retrieves a count of the items in a tree view control. You can send this message
 * explicitly or by using the TreeView_GetCount macro.
 *
 * @return Returns the count of items.
 */
#define TVM_GETCOUNT            (TV_FIRST + 5)
/**
 * This macro retrieves a count of the items in a tree-view control. You can use this macro or send
 * the TVM_GETCOUNT message explicitly.
 *
 * @param hwndTV Handle to the tree view control.
 *
 * @return Returns the count of items.
 */
#define TreeView_GetCount(hwnd) \
    (UINT)SNDMSG((hwnd), TVM_GETCOUNT, 0, 0)


/**
 * This message retrieves the amount, in pixels, that child items are indented relative to their
 * parent items. You can send this message explicitly or by using the TreeView_GetIndent macro.
 *
 * @return Returns the amount of indentation.
 */
#define TVM_GETINDENT           (TV_FIRST + 6)
/**
 * This macro retrieves the amount, in pixels, that child items are indented relative to their
 * parent items. You can use this macro or send the TVM_GETINDENT message explicitly.
 *
 * @param hwndTV Handle to the tree view control.
 *
 * @return Returns the amount of indentation.
 */
#define TreeView_GetIndent(hwnd) \
    (UINT)SNDMSG((hwnd), TVM_GETINDENT, 0, 0)


/**
 * This message sets the width of indentation for a tree view control and redraws the control to
 * reflect the new width. You can send this message explicitly or by using the TreeView_SetIndent
 * macro.
 *
 * @param indent Width, in pixels, of the indentation. If this parameter is less than the
 *   system-defined minimum width, the new width is set to the system-defined minimum.
 *
 * @return The return value is not used.
 */
#define TVM_SETINDENT           (TV_FIRST + 7)
/**
 * This macro sets the width of indentation for a tree-view control and redraws the control to
 * reflect the new width. You can use this macro or send the TVM_SETINDENT message explicitly.
 *
 * @param hwndTV Handle to the tree view control.
 * @param indent Width, in pixels, of the indentation. If this parameter is less than the
 *   system-defined minimum width, the new width is set to the system-defined minimum.
 *
 * @return The return value is not used.
 */
#define TreeView_SetIndent(hwnd, indent) \
    (BOOL)SNDMSG((hwnd), TVM_SETINDENT, (WPARAM)indent, 0)


/**
 * This message retrieves the handle of the normal or state image list associated with a tree view
 * control. You can send this message explicitly or by using the TreeView_GetImageList macro.
 *
 * @param iImage Type of image list to retrieve. It is one of the following values: Value
 *   Description TVSIL_NORMAL Indicates the normal image list, which contains selected, nonselected,
 *   and overlay images for the items of a tree view control. TVSIL_STATE Indicates the state image
 *   list. You can use state images to indicate application-defined item states. A state image is
 *   displayed to the left of an item's selected or nonselected image.
 *
 * @return Returns an HIMAGELIST handle to the specified image list.
 */
#define TVM_GETIMAGELIST        (TV_FIRST + 8)
/**
 * This macro retrieves the handle to the normal or state image list associated with a tree-view
 * control. You can use this macro or send the TVM_GETIMAGELIST message explicitly.
 *
 * @param hwndTV Handle to the tree view control.
 * @param iImage Type of image list to retrieve. It is one of the following values: Value
 *   Description TVSIL_NORMAL Indicates the normal image list, which contains selected, nonselected,
 *   and overlay images for the items of a tree view control. TVSIL_STATE Indicates the state image
 *   list. You can use state images to indicate application-defined item states. A state image is
 *   displayed to the left of an item's selected or nonselected image.
 *
 * @return Returns an HIMAGELIST handle to the specified image list.
 */
#define TreeView_GetImageList(hwnd, iImage) \
    (HIMAGELIST)SNDMSG((hwnd), TVM_GETIMAGELIST, iImage, 0)


#define TVSIL_NORMAL            0
#define TVSIL_STATE             2


/**
 * This message sets the normal or state image list for a tree view control and redraws the control
 * using the new images. You can send this message explicitly or by using the TreeView_SetImageList
 * macro.
 *
 * @param iImage Type of image list to set. It is one of the following values: Value Description
 *   TVSIL_NORMAL Indicates the normal image list, which contains selected, nonselected, and overlay
 *   images for the items of a tree view control. TVSIL_STATE Indicates the state image list. You can
 *   use state images to indicate application-defined item states. A state image is displayed to the
 *   left of an item's selected or nonselected image.
 * @param himl Handle to the image list. If himl is NULL, the message removes the specified image
 *   list from the tree view control.
 *
 * @return The handle to the previous image list, if any, indicates success. NULL indicates
 *   otherwise.
 */
#define TVM_SETIMAGELIST        (TV_FIRST + 9)
/**
 * This macro sets the normal or state image list for a tree-view control and redraws the control
 * using the new images. You can use this macro or send the TVM_SETIMAGELIST message explicitly.
 *
 * @param hwndTV Handle to the tree view control.
 * @param himl Handle to the image list. If himl is NULL, the message removes the specified image
 *   list from the tree view control.
 * @param iImage Type of image list to set. It is one of the following values: Value Description
 *   TVSIL_NORMAL Indicates the normal image list, which contains selected, nonselected, and overlay
 *   images for the items of a tree view control. TVSIL_STATE Indicates the state image list. You can
 *   use state images to indicate application-defined item states. A state image is displayed to the
 *   left of an item's selected or nonselected image.
 *
 * @return The HIMAGELIST handle to the previous image list, if any, indicates success. NULL
 *   indicates failure.
 */
#define TreeView_SetImageList(hwnd, himl, iImage) \
    (HIMAGELIST)SNDMSG((hwnd), TVM_SETIMAGELIST, iImage, (LPARAM)(UINT)(HIMAGELIST)(himl))


/**
 * This message retrieves the tree view item that bears the specified relationship to a specified
 * item. You can send this message explicitly or by using the TreeView_GetNextItem macro or one of
 * the related macros.
 *
 * @param flag Specifies the item to retrieve. It is one of the following values: Value Description
 *   TVGN_CARET Retrieves the currently selected item. You can use the TreeView_GetSelection macro to
 *   send this message. TVGN_CHILD Retrieves the first child item of the item specified by the hitem
 *   parameter. You can use the TreeView_GetChild macro to send this message. TVGN_DROPHILITE
 *   Retrieves the item that is the target of a drag-and-drop operation. You can use the
 *   TreeView_GetDropHilight macro to send this message. TVGN_FIRSTVISIBLE Retrieves the first item
 *   that is visible in the tree view window. You can use the TreeView_GetFirstVisible macro to send
 *   this message. TVGN_LASTVISIBLE Version 4.71. Retrieves the last expanded item in the tree. This
 *   does not retrieve the last item visible in the tree view window. You can use the
 *   TreeView_GetLastVisible macro to send this message. TVGN_NEXT Retrieves the next sibling item.
 *   You can use the TreeView_GetNextSibling macro to send this message. TVGN_NEXTVISIBLE Retrieves
 *   the next visible item that follows the specified item. The specified item must be visible. Use
 *   the TVM_GETITEMRECT message to determine whether an item is visible. You can use the
 *   TreeView_GetNextVisible macro to send this message. TVGN_PARENT Retrieves the parent of the
 *   specified item. You can use the TreeView_GetParent macro to send this message. TVGN_PREVIOUS
 *   Retrieves the previous sibling item. You can use the TreeView_GetPrevSibling macro to send this
 *   message. TVGN_PREVIOUSVISIBLE Retrieves the first visible item that precedes the specified item.
 *   The specified item must be visible. Use the TVM_GETITEMRECT message to determine whether an item
 *   is visible. You can use the TreeView_GetPrevVisible macro to send this message. TVGN_ROOT
 *   Retrieves the topmost or very first item of the tree view control. You can use the
 *   TreeView_GetRoot macro to send this message.
 * @param hitem Handle to an item.
 *
 * @return The handle to the item indicates success. NULL indicates otherwise.
 */
#define TVM_GETNEXTITEM         (TV_FIRST + 10)
/**
 * This macro retrieves the tree-view item that bears the specified relationship to a specified
 * item. You can use this macro, use one of the TreeView_Get macros described below, or send the
 * TVM_GETNEXTITEM message explicitly.
 *
 * @param hwndTV Handle to the tree view control.
 * @param hitem Handle to an item.
 * @param flag Flag that specifies the item to retrieve. It is one of the following values: Value
 *   Description TVGN_CARET Retrieves the currently selected item. You can use the
 *   TreeView_GetSelection macro to send this message. TVGN_CHILD Retrieves the first child item of
 *   the item specified by the hitem parameter. You can use the TreeView_GetChild macro to send this
 *   message. TVGN_DROPHILITE Retrieves the item that is the target of a drag-and-drop operation. You
 *   can use the TreeView_GetDropHilight macro to send this message. TVGN_FIRSTVISIBLE Retrieves the
 *   first visible item. You can use the TreeView_GetFirstVisible macro to send this message.
 *   TVGN_NEXT Retrieves the next sibling item. You can use the TreeView_GetNextSibling macro to send
 *   this message. TVGN_NEXTVISIBLE Retrieves the next visible item that follows the specified item.
 *   The specified item must be visible. Use the TVM_GETITEMRECT message to determine whether an item
 *   is visible. You can use the TreeView_GetNextVisible macro to send this message. TVGN_PARENT
 *   Retrieves the parent of the specified item. You can use the TreeView_GetParent macro to send this
 *   message. TVGN_PREVIOUS Retrieves the previous sibling item. You can use the
 *   TreeVIew_GetPrevSibling macro to send this message. TVGN_PREVIOUSVISIBLE Retrieves the first
 *   visible item that precedes the specified item. The specified item must be visible. Use the
 *   TVM_GETITEMRECT message to determine whether an item is visible. You can use the
 *   TreeView_GetPrevVisible macro to send this message. TVGN_ROOT Retrieves the topmost or very first
 *   item of the tree view control. You can use the TreeView_GetRoot macro to send this message.
 *
 * @return The handle to the item indicates success. NULL indicates failure.
 */
#define TreeView_GetNextItem(hwnd, hitem, code) \
    (HTREEITEM)SNDMSG((hwnd), TVM_GETNEXTITEM, (WPARAM)code, (LPARAM)(HTREEITEM)(hitem))


#define TVGN_ROOT               0x0000
#define TVGN_NEXT               0x0001
#define TVGN_PREVIOUS           0x0002
#define TVGN_PARENT             0x0003
#define TVGN_CHILD              0x0004
#define TVGN_FIRSTVISIBLE       0x0005
#define TVGN_NEXTVISIBLE        0x0006
#define TVGN_PREVIOUSVISIBLE    0x0007
#define TVGN_DROPHILITE         0x0008
#define TVGN_CARET              0x0009

/**
 * This macro retrieves the first child item of the specified tree-view item. You can use this
 * macro, or you can explicitly send the TVM_GETNEXTITEM message with the TVGN_CHILD flag.
 *
 * @param hwndTV Handle to the tree view control.
 * @param hitem Handle to a tree view item.
 *
 * @return The handle to the item indicates success. NULL indicates failure.
 */
#define TreeView_GetChild(hwnd, hitem)          TreeView_GetNextItem(hwnd, hitem, TVGN_CHILD)
/**
 * This macro retrieves the next sibling item of a specified item in a tree-view control. You can
 * use this macro, or you can explicitly send the TVM_GETNEXTITEM message with the TVGN_NEXT flag.
 *
 * @param hwndTV Handle to the tree view control.
 * @param hitem Handle to an item.
 *
 * @return The handle to the item indicates success. NULL indicates failure.
 */
#define TreeView_GetNextSibling(hwnd, hitem)    TreeView_GetNextItem(hwnd, hitem, TVGN_NEXT)
/**
 * This macro retrieves the previous sibling item of a specified item in a tree-view control. You
 * can use this macro, or you can explicitly send the TVM_GETNEXTITEM message with the TVGN_PREVIOUS
 * flag.
 *
 * @param hwndTV Handle to the tree view control.
 * @param hitem Handle to an item.
 *
 * @return The handle to the item indicates success. NULL indicates failure.
 */
#define TreeView_GetPrevSibling(hwnd, hitem)    TreeView_GetNextItem(hwnd, hitem, TVGN_PREVIOUS)
/**
 * This macro retrieves the parent item of the specified tree-view item. You can use this macro, or
 * you can explicitly send the TVM_GETNEXTITEM message with the TVGN_PARENT flag.
 *
 * @param hwndTV Handle to the tree view control.
 * @param hitem Handle to an item.
 *
 * @return The handle to the item indicates success. NULL indicates failure.
 */
#define TreeView_GetParent(hwnd, hitem)         TreeView_GetNextItem(hwnd, hitem, TVGN_PARENT)
/**
 * This macro retrieves the first visible item in a tree-view control. You can use this macro, or
 * you can explicitly send the TVM_GETNEXTITEM message with the TVGN_FIRSTVISIBLE flag.
 *
 * @param hwndTV Handle to the tree view control.
 *
 * @return The handle to the item indicates success. NULL indicates failure.
 */
#define TreeView_GetFirstVisible(hwnd)          TreeView_GetNextItem(hwnd, NULL,  TVGN_FIRSTVISIBLE)
/**
 * This macro retrieves the next visible item that follows a specified item in a tree-view control.
 * You can use this macro, or you can explicitly send the TVM_GETNEXTITEM message with the
 * TVGN_NEXTVISIBLE flag.
 *
 * @param hwndTV Handle to the tree view control.
 * @param hitem Handle to an item. The specified item must be visible. Use the TVM_GETITEMRECT
 *   message to determine whether an item is visible.
 *
 * @return The handle to the item indicates success. NULL indicates failure.
 */
#define TreeView_GetNextVisible(hwnd, hitem)    TreeView_GetNextItem(hwnd, hitem, TVGN_NEXTVISIBLE)
/**
 * This macro retrieves the first visible item that precedes a specified item in a tree-view
 * control. You can use this macro, or you can explicitly send the TVM_GETNEXTITEM message with the
 * TVGN_PREVIOUSVISIBLE flag.
 *
 * @param hwndTV Handle to the tree view control.
 * @param hitem Handle to an item. The specified item must be visible. Use the TVM_GETITEMRECT
 *   message to determine whether an item is visible.
 *
 * @return The handle to the item indicates success. NULL indicates failure.
 */
#define TreeView_GetPrevVisible(hwnd, hitem)    TreeView_GetNextItem(hwnd, hitem, TVGN_PREVIOUSVISIBLE)
/**
 * This macro retrieves the currently selected item in a tree-view control. You can use this macro,
 * or you can explicitly send the TVM_GETNEXTITEM message with the TVGN_CARET flag.
 *
 * @param hwndTV Handle to the tree view control.
 *
 * @return The handle to the item indicates success. NULL indicates failure.
 */
#define TreeView_GetSelection(hwnd)             TreeView_GetNextItem(hwnd, NULL,  TVGN_CARET)
#define TreeView_GetDropHilight(hwnd)           TreeView_GetNextItem(hwnd, NULL,  TVGN_DROPHILITE)
/**
 * This macro retrieves the topmost or very first item of the tree-view control. You can use this
 * macro, or you can explicitly send the TVM_GETNEXTITEM message with the TVGN_ROOT flag.
 *
 * @param hwndTV Handle to the tree view control.
 *
 * @return The handle to the item indicates success. NULL indicates failure.
 */
#define TreeView_GetRoot(hwnd)                  TreeView_GetNextItem(hwnd, NULL,  TVGN_ROOT)


/**
 * This message selects the specified tree view item, scrolls the item into view, or redraws the
 * item in the style used to indicate the target of a drag and drop operation. You can send this
 * message explicitly or by using the TreeView_Select, TreeView_SelectItem, or
 * TreeView_SelectDropTarget macro.
 *
 * @param flag Action flag. It is one of the following values: Value Description TVGN_CARET Sets the
 *   selection to the specified item. The tree view control's parent window receives the
 *   TVN_SELCHANGING and TVN_SELCHANGED notification messages. TVGN_DROPHILITE Redraws the specified
 *   item in the style used to indicate the target of a drag-and-drop operation. TVGN_FIRSTVISIBLE
 *   Ensures that the specified item is visible, and, if possible, displays it at the top of the
 *   control's window. Tree view controls display as many items as will fit in the window. If the
 *   specified item is near the bottom of the control's hierarchy of items, it might not become the
 *   first visible item, depending on how many items fit in the window.
 * @param hitem Handle to an item. If hitem is NULL, the control is set to have no selected item.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * If the specified item is the child of a collapsed parent item, the parent's list of child items
 * is expanded to reveal the specified item. In this case, the control's parent window receives the
 * TVN_ITEMEXPANDING and TVN_ITEMEXPANDED notification messages.
 */
#define TVM_SELECTITEM          (TV_FIRST + 11)
/**
 * This macro selects the specified tree-view item, scrolls the item into the view, or redraws the
 * item in the style used to indicate the target of a drag-and-drop operation. You can use this
 * macro or the TreeView_SelectItem, TreeView_SelectSetFirstVisible, or treeView_SelectDropTarget
 * macros, or you can send the TVM_SELECTITEM message explicitly.
 *
 * @param hwndTV Handle to the tree view control.
 * @param hitem Handle to an item. If the hitem parameter is NULL, the control is set to have no
 *   selected item.
 * @param flag Action flag. It is one of the following values: Value Description TVGN_CARET Sets the
 *   selection to the Nonzero indicates success. Zero indicates otherwise. item. The control's parent
 *   window receives the TVN_SELCHANGING and TVN_SELCHANGED notification messages. TVGN_DROPHILITE
 *   Redraws the Nonzero indicates success. Zero indicates otherwise. item in the style used to
 *   indicate the target of a drag-and-drop operation. TVGN_FIRSTVISIBLE Ensures that the specified
 *   item is visible, and, if possible, displays it at the top of the control's window. Tree view
 *   controls display as many items as will fit in the window. If the specified item is near the
 *   bottom of the control's hierarchy of items, it might not become the first visible item, depending
 *   on how many items fit in the window.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * If the specified item is the child of a collapsed parent item, the parent's list of child items
 * is expanded to reveal the specified item. In this case, the parent window receives the
 * TVN_ITEMEXPANDING and TVN_ITEMEXPANDED notification messages.
 */
#define TreeView_Select(hwnd, hitem, code) \
    (BOOL)SNDMSG((hwnd), TVM_SELECTITEM, (WPARAM)code, (LPARAM)(HTREEITEM)(hitem))


/**
 * This macro selects the specified tree-view item. You can use this macro or the TreeView_Select
 * macro, or you can send the TVM_SELECTITEM message explicitly.
 *
 * @param hwndTV Handle to the tree view control.
 * @param hitem Handle to an item. If the hitem parameter is NULL, the control is set to have no
 *   selected item.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * When you call the TreeView_SelectItem macro, the control's parent window receives the
 * TVN_SELCHANGING and TVN_SELCHANGED notification messages. Also, if the specified item is the
 * child of a collapsed parent item, the parent's list of child items is expanded to reveal the
 * specified item. In this case, the parent window receives the TVN_ITEMEXPANDING and
 * TVN_ITEMEXPANDED notification messages.
 *
 * Using the TreeView_SelectItem macro is equivalent to sending the TVM_SELECTITEM message with its
 * flag parameter set to the TVGN_CARET value.
 */
#define TreeView_SelectItem(hwnd, hitem)            TreeView_Select(hwnd, hitem, TVGN_CARET)
/**
 * This macro redraws a specified tree-view control item in the style used to indicate the target of
 * a drag-and-drop operation. You can use this macro or the TreeView_Select macro, or you can send
 * the TVM_SELECTITM message explicitly.
 *
 * @param hwndTV Handle to the tree view control.
 * @param hitem Handle to an item. If the hitem parameter is NULL, the control is set to have no
 *   selected item.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * If the specified item is the child of a collapsed parent item, the parent's list of child items
 * is expanded to reveal the specified item. In this case, the parent window receives the
 * TVN_ITEMEXPANDING and TVN_ITEMEXPANDED notification messages.
 *
 * Using the TreeView_SelectDropTarget macro is equivalent to sending the TVM_SELECTITEM message
 * with its flag parameter set to the TVGN_DROPHILITE value.
 */
#define TreeView_SelectDropTarget(hwnd, hitem)      TreeView_Select(hwnd, hitem, TVGN_DROPHILITE)
/**
 * This macro scrolls the tree-view control vertically to ensure that the specified item is visible.
 * If possible, the specified item becomes the first visible item at the top of the control's
 * window. You can use this macro or the TreeView_Select macro, or you can send the TVM_SELECTITEM
 * message explicitly.
 *
 * @param hwndTV Handle to the tree view control.
 * @param hitem Handle to an item. If the hitem parameter is NULL, the control is set to have no
 *   selected item.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * Tree view controls display as many items as will fit in the window. If the specified item is near
 * the bottom of the control's hierarchy of items, it might not become the first visible item,
 * depending on how many items fit in the window.
 *
 * If the specified item is the child of a collapsed parent item, the parent's list of child items
 * is expanded to reveal the specified item. In this case, the parent window receives the
 * TVN_ITEMEXPANDING and TVN_ITEMEXPANDED notification messages.
 *
 * Using the TreeView_SelectSetFirstVisible macro is equivalent to sending the TVM_SELECTITEM
 * message with its flag parameter set to the TVGN_FIRSTVISIBLE value.
 */
#define TreeView_SelectSetFirstVisible(hwnd, hitem) TreeView_Select(hwnd, hitem, TVGN_FIRSTVISIBLE)


#define TVM_GETITEMA            (TV_FIRST + 12)
#define TVM_GETITEMW            (TV_FIRST + 62)

#ifdef UNICODE
/**
 * This message retrieves some or all of a tree view item's attributes. You can send this message
 * explicitly or by using the TreeView_GetItem macro.
 *
 * @param pitem Pointer to a TVITEM structure that specifies the information to retrieve and
 *   receives information about the item. When the message is sent, the hItem member identifies the
 *   item to retrieve information about and the mask member specifies the attributes to retrieve. If
 *   the mask member specifies the TVIF_TEXT value, the pszText member must contain the address of the
 *   buffer that receives the item text and the cchTextMax member must specify the size of the buffer.
 *   If the mask member specifies the TVIF_STATE value, the stateMask member must specify the item
 *   state bits to retrieve. On output, the state member contains the values of the specified state
 *   bits.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define  TVM_GETITEM            TVM_GETITEMW
#else
/**
 * This message retrieves some or all of a tree view item's attributes. You can send this message
 * explicitly or by using the TreeView_GetItem macro.
 *
 * @param pitem Pointer to a TVITEM structure that specifies the information to retrieve and
 *   receives information about the item. When the message is sent, the hItem member identifies the
 *   item to retrieve information about and the mask member specifies the attributes to retrieve. If
 *   the mask member specifies the TVIF_TEXT value, the pszText member must contain the address of the
 *   buffer that receives the item text and the cchTextMax member must specify the size of the buffer.
 *   If the mask member specifies the TVIF_STATE value, the stateMask member must specify the item
 *   state bits to retrieve. On output, the state member contains the values of the specified state
 *   bits.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define  TVM_GETITEM            TVM_GETITEMA
#endif

/**
 * This macro retrieves some or all of a tree-view item's attributes. You can use this macro or send
 * the TVM_GETITEM message explicitly.
 *
 * @param hwndTV Handle to the tree view control.
 * @param pitem Pointer to a TVITEM structure that specifies the information to retrieve and
 *   receives information about the item. When the TVM_GETITEM message is sent, the hItem member
 *   identifies the item to retrieve information about, and the mask member specifies the attributes
 *   to retrieve. If the mask member specifies the TVIF_TEXT value, the pszText member must contain
 *   the address of the buffer that receives the item text and the cchTextMax member must specify the
 *   size of the buffer. If the mask member specifies the TVIF_STATE value, the stateMask member must
 *   specify the item state bits to retrieve. On output, the state member contains the values of the
 *   specified state bits.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define TreeView_GetItem(hwnd, pitem) \
    (BOOL)SNDMSG((hwnd), TVM_GETITEM, 0, (LPARAM)(TV_ITEM FAR*)(pitem))


#define TVM_SETITEMA            (TV_FIRST + 13)
#define TVM_SETITEMW            (TV_FIRST + 63)

#ifdef UNICODE
/**
 * This message sets some or all of a tree view item's attributes. You can send this message
 * explicitly or by using the TreeView_SetItem macro.
 *
 * @param pitem Pointer to a TVITEM structure that contains the new item attributes. The hItem
 *   member identifies the item, and the mask member specifies which attributes to set. If mask
 *   specifies the TVIF_TEXT value, the pszText member is the address of a null-terminated string and
 *   the cchTextMax member is ignored. If mask specifies the TVIF_STATE value, the stateMask member
 *   indicates which item states to change and the state member contains the values for those states.
 *
 * @return TRUE indicates success. FALSE indicates success.
 */
#define  TVM_SETITEM            TVM_SETITEMW
#else
/**
 * This message sets some or all of a tree view item's attributes. You can send this message
 * explicitly or by using the TreeView_SetItem macro.
 *
 * @param pitem Pointer to a TVITEM structure that contains the new item attributes. The hItem
 *   member identifies the item, and the mask member specifies which attributes to set. If mask
 *   specifies the TVIF_TEXT value, the pszText member is the address of a null-terminated string and
 *   the cchTextMax member is ignored. If mask specifies the TVIF_STATE value, the stateMask member
 *   indicates which item states to change and the state member contains the values for those states.
 *
 * @return TRUE indicates success. FALSE indicates success.
 */
#define  TVM_SETITEM            TVM_SETITEMA
#endif

/**
 * This macro sets some or all of a tree-view item's attributes. You can use this macro or send the
 * TVM_SETITEM message explicitly.
 *
 * @param hwndTV Handle to the tree view control.
 * @param pitem Pointer to a TVITEM structure that contains the new item attributes. The hItem
 *   member identifies the item, and the mask member specifies which attributes to set. If mask
 *   specifies the TVIF_TEXT value, the pszText member is the address of a null-terminated string and
 *   the cchTextMax member is ignored. If mask specifies the TVIF_STATE value, the stateMask member
 *   indicates which item states to change and the state member contains the values for those states.
 *
 * @return Zero indicates success. -1 indicates failure.
 */
#define TreeView_SetItem(hwnd, pitem) \
    (BOOL)SNDMSG((hwnd), TVM_SETITEM, 0, (LPARAM)(const TV_ITEM FAR*)(pitem))


#define TVM_EDITLABELA          (TV_FIRST + 14)
#define TVM_EDITLABELW          (TV_FIRST + 65)
#ifdef UNICODE
/**
 * This message begins in-place editing of the specified item's text, replacing the text of the item
 * with a single-line edit control containing the text. This message implicitly selects and focuses
 * the specified item. You can send this message explicitly or by using the TreeView_EditLabel
 * macro.
 *
 * @param hitem Handle to the item to edit.
 *
 * @return The handle to the edit control used to edit the item text indicates success. NULL
 *   indicates otherwise.
 *
 * This message sends a TVN_BEGINLABELEDIT notification message to the parent of the tree view
 * control.
 *
 * When the user completes or cancels editing, the edit control is destroyed and the handle is no
 * longer valid. You can safely subclass the edit control, but do not destroy it.
 */
#define TVM_EDITLABEL           TVM_EDITLABELW
#else
/**
 * This message begins in-place editing of the specified item's text, replacing the text of the item
 * with a single-line edit control containing the text. This message implicitly selects and focuses
 * the specified item. You can send this message explicitly or by using the TreeView_EditLabel
 * macro.
 *
 * @param hitem Handle to the item to edit.
 *
 * @return The handle to the edit control used to edit the item text indicates success. NULL
 *   indicates otherwise.
 *
 * This message sends a TVN_BEGINLABELEDIT notification message to the parent of the tree view
 * control.
 *
 * When the user completes or cancels editing, the edit control is destroyed and the handle is no
 * longer valid. You can safely subclass the edit control, but do not destroy it.
 */
#define TVM_EDITLABEL           TVM_EDITLABELA
#endif

/**
 * This macro begins in-place editing of the specified item's text, replacing the text of the item
 * with a single-line edit control containing the text. This macro implicitly selects and focuses
 * the specified item. You can use this macro or send the TVM_EDITLABEL message explicitly.
 *
 * @param hwndTV Handle to the tree view control.
 * @param hitem Handle to the item to edit.
 *
 * @return The handle to the edit control used to edit the item text indicates success. NULL
 *   indicates failure.
 *
 * This macro sends a TVN_BEGINLABELEDIT notification message to the parent of the tree view
 * control.
 *
 * When the user completes or cancels editing, the edit control is destroyed and the handle is no
 * longer valid. You can safely subclass the edit control, but do not destroy it.
 *
 * The control must have the focus before you call this macro. Focus can be set using the SetFocus
 * function.
 */
#define TreeView_EditLabel(hwnd, hitem) \
    (HWND)SNDMSG((hwnd), TVM_EDITLABEL, 0, (LPARAM)(HTREEITEM)(hitem))


/**
 * This message retrieves the handle of the edit control being used to edit a tree view item's text.
 * You can send this message explicitly or by using the TreeView_GetEditControl macro.
 *
 * @return The handle to the edit control indicates success. NULL indicates otherwise.
 */
#define TVM_GETEDITCONTROL      (TV_FIRST + 15)
/**
 * This macro retrieves the handle to the edit control being used to edit a tree-view item's text.
 * You can use this macro or send the TVM_GETEDITCONTROL message explicitly.
 *
 * @param hwndTV Handle to the tree view control.
 *
 * @return The handle to the edit control indicates success. NULL indicates failure.
 */
#define TreeView_GetEditControl(hwnd) \
    (HWND)SNDMSG((hwnd), TVM_GETEDITCONTROL, 0, 0)


/**
 * This message retrieves the number of items that can be fully visible in the client window of the
 * tree-view control. You can send this message explicitly or by using the TreeView_GetVisibleCount
 * macro.
 *
 * @return Returns the number of items that can be fully visible in the client window of the tree
 *   view control.
 *
 * The number of items that can be fully visible may be greater than the number of items in the
 * control. The control calculates this value by dividing the height of the client window by the
 * height of an item.
 *
 * Note that the return value is the number of items that can be fully visible. If you can see all
 * of 20 items and part of one more item, the return value is 20.
 */
#define TVM_GETVISIBLECOUNT     (TV_FIRST + 16)
/**
 * This macro obtains the number of items that can be fully visible in the client window of a
 * tree-view control. You can use this macro or send the TVM_GETVISIBLECOUNT message explicitly.
 *
 * @param hwndTV Handle to the tree view control.
 *
 * @return Returns the number of items that can be fully visible in the client window of the tree
 *   view control.
 *
 * The number of items that can be fully visible may be greater than the number of items in the
 * control. The control calculates this value by dividing the height of the client window by the
 * height of an item.
 *
 * Note that the return value is the number of items that can be fully visible. If you can see all
 * of 20 items and part of one more item, the return value is 20.
 */
#define TreeView_GetVisibleCount(hwnd) \
    (UINT)SNDMSG((hwnd), TVM_GETVISIBLECOUNT, 0, 0)


/**
 * This message determines the location of the specified point relative to the client area of a tree
 * view control. You can send this message explicitly or by using the TreeView_HitTest macro.
 *
 * @param lpht Long pointer to a TVHITTESTINFO structure. When the message is sent, the pt member
 *   specifies the coordinates of the point to test. When the message returns, the hItem member is the
 *   handle to the item at the specified point or NULL if no item occupies the point. Also, when the
 *   message returns, the flags member is a hit test value that indicates the location of the
 *   specified point. For a list of hit test values, see the description of the TVHITTESTINFO
 *   structure.
 *
 * @return The handle to the tree view item that occupies the specified point indicates success.
 *   NULL indicates that no item occupies the point.
 */
#define TVM_HITTEST             (TV_FIRST + 17)
/**
 * This macro determines the location of the specified point relative to the client area of a
 * tree-view control. You can use this macro or send the TVM_HITTEST message explicitly.
 *
 * @param hwndTV Handle to the tree view control.
 * @param lpht Long pointer to a TVHITTESTINFO structure. When the message is sent, the pt member
 *   specifies the coordinates of the point to test. When the message returns, the hItem member is the
 *   handle to the item at the specified point or NULL if no item occupies the point. Also, when the
 *   message returns, the flags member is a hit test value that indicates the location of the
 *   specified point. For a list of hit test values, see the description of the TVHITTESTINFO
 *   structure.
 *
 * @return The handle to the tree view item that occupies the specified point indicates success.
 *   NULL indicates that no item occupies the point.
 */
#define TreeView_HitTest(hwnd, lpht) \
    (HTREEITEM)SNDMSG((hwnd), TVM_HITTEST, 0, (LPARAM)(LPTV_HITTESTINFO)(lpht))


#if (_WIN32_IE >= 0x0300)
#define LPTV_HITTESTINFO   LPTVHITTESTINFO
#define   TV_HITTESTINFO     TVHITTESTINFO
#else
#define tagTVHITTESTINFO    _TV_HITTESTINFO
#define    TVHITTESTINFO     TV_HITTESTINFO
#define  LPTVHITTESTINFO   LPTV_HITTESTINFO
#endif

typedef struct tagTVHITTESTINFO {
    POINT       pt;
    UINT        flags;
    HTREEITEM   hItem;
} TVHITTESTINFO, FAR *LPTVHITTESTINFO;

#define TVHT_NOWHERE            0x0001
#define TVHT_ONITEMICON         0x0002
#define TVHT_ONITEMLABEL        0x0004
#define TVHT_ONITEM             (TVHT_ONITEMICON | TVHT_ONITEMLABEL | TVHT_ONITEMSTATEICON)
#define TVHT_ONITEMINDENT       0x0008
#define TVHT_ONITEMBUTTON       0x0010
#define TVHT_ONITEMRIGHT        0x0020
#define TVHT_ONITEMSTATEICON    0x0040

#define TVHT_ABOVE              0x0100
#define TVHT_BELOW              0x0200
#define TVHT_TORIGHT            0x0400
#define TVHT_TOLEFT             0x0800


/**
 * This message creates a dragging bitmap for the specified item in a tree view control, creates an
 * image list for the bitmap, and adds the bitmap to the image list. An application can display the
 * image when dragging the item by using the image list functions. You can send this message
 * explicitly or by using the TreeView_CreateDragImage macro.
 *
 * @param hitem Handle to the item that receives the new dragging bitmap.
 *
 * @return The handle to the image list to which the dragging bitmap was added indicates success.
 *   NULL indicates otherwise.
 */
#define TVM_CREATEDRAGIMAGE     (TV_FIRST + 18)
/**
 * This macro creates a dragging bitmap for the specified item in a tree-view control, creates an
 * image list for the bitmap, and adds the bitmap to the image list. An application can display the
 * image when dragging the item by using the image list functions. You can use this macro or send
 * the TVM_CREATEDRAGIMAGE message explicitly.
 *
 * @param hwndTV Handle to the tree view control.
 * @param hitem Handle to the item that receives the new dragging bitmap.
 *
 * @return The handle to the image list to which the dragging bitmap was added indicates success.
 *   NULL indicates failure.
 *
 * If you create a tree view control without an associated image list, you cannot use the
 * TreeView_CreateDragImage macro to create the image to display during a drag operation. You must
 * implement your own method of creating a drag cursor.
 */
#define TreeView_CreateDragImage(hwnd, hitem) \
    (HIMAGELIST)SNDMSG((hwnd), TVM_CREATEDRAGIMAGE, 0, (LPARAM)(HTREEITEM)(hitem))


/**
 * This message sorts the child items of the specified parent item in a tree view control. You can
 * send this message explicitly or by using the TreeView_SortChildren macro.
 *
 * @param fRecurse Reserved for future use; set to zero.
 * @param hitem Handle to the parent item whose child items are to be sorted.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define TVM_SORTCHILDREN        (TV_FIRST + 19)
/**
 * This macro sorts the child items of the specified parent item in a tree-view control. You can use
 * this macro or send the TVM_SORTCHILDREN message explicitly.
 *
 * @param hwndTV Handle to the tree view control.
 * @param hitem Handle to the parent item whose child items are to be sorted.
 * @param fRecurse Reserved for future use; set to zero.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define TreeView_SortChildren(hwnd, hitem, recurse) \
    (BOOL)SNDMSG((hwnd), TVM_SORTCHILDREN, (WPARAM)recurse, (LPARAM)(HTREEITEM)(hitem))


/**
 * This message ensures that a tree view item is visible, expanding the parent item or scrolling the
 * tree view control, if necessary. You can send this message explicitly or by using the
 * TreeView_EnsureVisible macro.
 *
 * @param hitem Handle to the item.
 *
 * @return Nonzero indicates that the system scrolled the items in the tree view control and no
 *   items were expanded. Zero indicates otherwise.
 */
#define TVM_ENSUREVISIBLE       (TV_FIRST + 20)
/**
 * This macro ensures that a tree-view item is visible, expanding the parent item or scrolling the
 * tree-view control, if necessary. You can use this macro or send the TVM_ENSUREVISIBLE message
 * explicitly.
 *
 * @param hwndTV Handle to the tree view control.
 * @param hitem Handle to the item.
 *
 * @return Nonzero indicates that the system scrolled the items in the tree view control and no
 *   items were expanded. Zero indicates otherwise.
 *
 * If the TreeView_EnsureVisible macro expands the parent item, the parent window receives the
 * TVN_ITEMEXPANDING and TVN_ITEMEXPANDED notification messages.
 */
#define TreeView_EnsureVisible(hwnd, hitem) \
    (BOOL)SNDMSG((hwnd), TVM_ENSUREVISIBLE, 0, (LPARAM)(HTREEITEM)(hitem))


/**
 * This message sorts tree view items using an application-defined callback function that compares
 * the items. You can send this message explicitly or by using the TreeView_SortChildrenCB macro.
 *
 * @param fRecurse Reserved for future use; set to zero.
 * @param psort Pointer a TVSORTCB structure. The lpfnCompare member is the address of the
 *   application-defined callback function, which is called during the sort operation each time the
 *   relative order of two list items needs to be compared. For more information about the callback
 *   function, see the description of TVSORTCB.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define TVM_SORTCHILDRENCB      (TV_FIRST + 21)
/**
 * This macro sorts tree-view items using an application-defined callback function that compares the
 * items. You can use this macro or send the TVM_SORTCHILDRENCB message explicitly.
 *
 * @param hwndTV Handle to the tree view control.
 * @param psort Pointer to a TVSORTCB structure. The lpfnCompare member is the address of the
 *   application-defined callback function, which is called during the sort operation each time the
 *   relative order of two list items needs to be compared. For more information about the callback
 *   function, see the description of TVSORTCB.
 * @param fRecurse Reserved for future use; set to zero.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define TreeView_SortChildrenCB(hwnd, psort, recurse) \
    (BOOL)SNDMSG((hwnd), TVM_SORTCHILDRENCB, (WPARAM)recurse, \
    (LPARAM)(LPTV_SORTCB)(psort))


/**
 * This message ends the editing of a tree view item's label. You can send this message explicitly
 * or by using the TreeView_EndEditLabelNow macro.
 *
 * @param fCancel Boolean value that indicates whether the editing is canceled without being saved
 *   to the label. If set to TRUE, the system cancels editing without saving the changes. If set to
 *   FALSE, the system saves the changes to the label.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define TVM_ENDEDITLABELNOW     (TV_FIRST + 22)
/**
 * This macro ends the editing of a tree-view item's label. You can use this macro or send the
 * TVM_ENDEDITLABELNOW message explicitly.
 *
 * @param hwndTV Handle to the tree view control.
 * @param fCancel Variable that indicates whether the editing is canceled without being saved to the
 *   label. If set to is TRUE, the system cancels editing without saving the changes. If set to FALSE,
 *   the system saves the changes to the label.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * This macro causes the TVN_ENDLABELEDIT notification message to be sent to the parent window of
 * the tree view control.
 */
#define TreeView_EndEditLabelNow(hwnd, fCancel) \
    (BOOL)SNDMSG((hwnd), TVM_ENDEDITLABELNOW, (WPARAM)fCancel, 0)


#define TVM_GETISEARCHSTRINGA   (TV_FIRST + 23)
#define TVM_GETISEARCHSTRINGW   (TV_FIRST + 64)

#ifdef UNICODE
/**
 * This message retrieves the incremental search string for a tree view control. The tree view
 * control uses the incremental search string to select an item based on characters entered by the
 * user. You can send this message explicitly or by using the TreeView_GetISearchString macro.
 *
 * @param lpsz Long pointer to the buffer that receives the incremental search string.
 *
 * @return Returns the number of characters in the incremental search string.
 */
#define TVM_GETISEARCHSTRING     TVM_GETISEARCHSTRINGW
#else
/**
 * This message retrieves the incremental search string for a tree view control. The tree view
 * control uses the incremental search string to select an item based on characters entered by the
 * user. You can send this message explicitly or by using the TreeView_GetISearchString macro.
 *
 * @param lpsz Long pointer to the buffer that receives the incremental search string.
 *
 * @return Returns the number of characters in the incremental search string.
 */
#define TVM_GETISEARCHSTRING     TVM_GETISEARCHSTRINGA
#endif

/**
 * This macro retrieves the incremental search string for a tree-view control. The tree-view control
 * uses the incremental search string to select an item based on characters typed by the user. You
 * can use this macro or send the TVM_GETISEARCHSTRING message explicitly.
 *
 * @param hwndTV Handle to the tree view control.
 * @param lpsz Long pointer to the buffer that receives the incremental search string.
 *
 * @return Returns the number of characters in the incremental search string.
 *
 * If the tree view control is not in incremental search mode, the return value is zero.
 */
#define TreeView_GetISearchString(hwndTV, lpsz) \
        (BOOL)SNDMSG((hwndTV), TVM_GETISEARCHSTRING, 0, (LPARAM)(LPTSTR)lpsz)


typedef int (CALLBACK *PFNTVCOMPARE)(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

#if (_WIN32_IE >= 0x0300)
#define LPTV_SORTCB    LPTVSORTCB
#define   TV_SORTCB      TVSORTCB
#else
#define tagTVSORTCB    _TV_SORTCB
#define    TVSORTCB     TV_SORTCB
#define  LPTVSORTCB   LPTV_SORTCB
#endif

typedef struct tagTVSORTCB
{
        HTREEITEM       hParent;
        PFNTVCOMPARE    lpfnCompare;
        LPARAM          lParam;
} TVSORTCB, FAR *LPTVSORTCB;


#if (_WIN32_IE >= 0x0300)
#define LPNM_TREEVIEWA          LPNMTREEVIEWA
#define LPNM_TREEVIEWW          LPNMTREEVIEWW
#define NM_TREEVIEWW            NMTREEVIEWW
#define NM_TREEVIEWA            NMTREEVIEWA
#else
#define tagNMTREEVIEWA          _NM_TREEVIEWA
#define tagNMTREEVIEWW          _NM_TREEVIEWW
#define NMTREEVIEWA             NM_TREEVIEWA
#define NMTREEVIEWW             NM_TREEVIEWW
#define LPNMTREEVIEWA           LPNM_TREEVIEWA
#define LPNMTREEVIEWW           LPNM_TREEVIEWW
#endif

#define LPNM_TREEVIEW           LPNMTREEVIEW
#define NM_TREEVIEW             NMTREEVIEW

typedef struct tagNMTREEVIEWA {
    NMHDR       hdr;
    UINT        action;
    TVITEMA    itemOld;
    TVITEMA    itemNew;
    POINT       ptDrag;
} NMTREEVIEWA, FAR *LPNMTREEVIEWA;


typedef struct tagNMTREEVIEWW {
    NMHDR       hdr;
    UINT        action;
    TVITEMW    itemOld;
    TVITEMW    itemNew;
    POINT       ptDrag;
} NMTREEVIEWW, FAR *LPNMTREEVIEWW;


#ifdef UNICODE
#define  NMTREEVIEW             NMTREEVIEWW
#define  LPNMTREEVIEW           LPNMTREEVIEWW
#else
#define  NMTREEVIEW             NMTREEVIEWA
#define  LPNMTREEVIEW           LPNMTREEVIEWA
#endif


#define TVN_SELCHANGINGA        (TVN_FIRST-1)
#define TVN_SELCHANGINGW        (TVN_FIRST-50)
#define TVN_SELCHANGEDA         (TVN_FIRST-2)
#define TVN_SELCHANGEDW         (TVN_FIRST-51)

#define TVC_UNKNOWN             0x0000
#define TVC_BYMOUSE             0x0001
#define TVC_BYKEYBOARD          0x0002

#define TVN_GETDISPINFOA        (TVN_FIRST-3)
#define TVN_GETDISPINFOW        (TVN_FIRST-52)
#define TVN_SETDISPINFOA        (TVN_FIRST-4)
#define TVN_SETDISPINFOW        (TVN_FIRST-53)

#define TVIF_DI_SETITEM         0x1000

#if (_WIN32_IE >= 0x0300)
#define TV_DISPINFOA            NMTVDISPINFOA
#define TV_DISPINFOW            NMTVDISPINFOW
#else
#define tagTVDISPINFOA  _TV_DISPINFOA
#define NMTVDISPINFOA    TV_DISPINFOA
#define tagTVDISPINFOW  _TV_DISPINFOW
#define NMTVDISPINFOW    TV_DISPINFOW
#endif

#define TV_DISPINFO             NMTVDISPINFO

typedef struct tagTVDISPINFOA {
    NMHDR hdr;
    TVITEMA item;
} NMTVDISPINFOA, FAR *LPNMTVDISPINFOA;

typedef struct tagTVDISPINFOW {
    NMHDR hdr;
    TVITEMW item;
} NMTVDISPINFOW, FAR *LPNMTVDISPINFOW;


#ifdef UNICODE
#define NMTVDISPINFO            NMTVDISPINFOW
#define LPNMTVDISPINFO          LPNMTVDISPINFOW
#else
#define NMTVDISPINFO            NMTVDISPINFOA
#define LPNMTVDISPINFO          LPNMTVDISPINFOA
#endif

#define TVN_ITEMEXPANDINGA      (TVN_FIRST-5)
#define TVN_ITEMEXPANDINGW      (TVN_FIRST-54)
#define TVN_ITEMEXPANDEDA       (TVN_FIRST-6)
#define TVN_ITEMEXPANDEDW       (TVN_FIRST-55)
#define TVN_BEGINDRAGA          (TVN_FIRST-7)
#define TVN_BEGINDRAGW          (TVN_FIRST-56)
#define TVN_BEGINRDRAGA         (TVN_FIRST-8)
#define TVN_BEGINRDRAGW         (TVN_FIRST-57)
#define TVN_DELETEITEMA         (TVN_FIRST-9)
#define TVN_DELETEITEMW         (TVN_FIRST-58)
#define TVN_BEGINLABELEDITA     (TVN_FIRST-10)
#define TVN_BEGINLABELEDITW     (TVN_FIRST-59)
#define TVN_ENDLABELEDITA       (TVN_FIRST-11)
#define TVN_ENDLABELEDITW       (TVN_FIRST-60)
/**
 * This notification message notifies a tree view control's parent window that the user pressed a
 * key and the tree view control has the input focus. It is sent in the form of a WM_NOTIFY message.
 *
 * @param ptvkd Pointer to an NMTVKEYDOWN structure. The wVKey member specifies the virtual-key
 *   code.
 *
 * @return If the wVKey member of ptvkd is a character key code, the character will be used as part
 *   of an incremental search. Return nonzero to exclude the character from the incremental search, or
 *   zero to include the character in the search. For all other keys, the return value is ignored.
 */
#define TVN_KEYDOWN             (TVN_FIRST-12)

#if (_WIN32_IE >= 0x0300)
#define TV_KEYDOWN      NMTVKEYDOWN
#else
#define tagTVKEYDOWN    _TV_KEYDOWN
#define  NMTVKEYDOWN     TV_KEYDOWN
#endif

/**
 * This structure contains information about a keyboard event in a tree-view control. This structure
 * is used with the TVN_KEYDOWN notification message.
 */
typedef struct tagTVKEYDOWN {
    /**
     * NMHDR structure that contains information about this notification message.
     */
    NMHDR hdr;
    WORD wVKey;
    /**
     * Set to zero.
     */
    UINT flags;
} NMTVKEYDOWN, FAR *LPNMTVKEYDOWN;


#ifdef UNICODE
/**
 * This notification message notifies a tree view control's parent window that the selection is
 * about to change from one item to another. It is sent in the form of a WM_NOTIFY message.
 *
 * @param pnmtv Pointer to an NMTREEVIEW structure. The itemOld and itemNew members contain valid
 *   information about the currently selected item and the newly selected item. The action member
 *   indicates whether a mouse or keyboard action is causing the selection to change. For a list of
 *   possible values, see the description of the TVN_SELCHANGED notification message.
 *
 * @return TRUE prevents the selection from changing.
 */
#define TVN_SELCHANGING         TVN_SELCHANGINGW
/**
 * This notification message notifies a tree view control's parent window that the selection has
 * changed from one item to another. It is sent in the form of a WM_NOTIFY message.
 *
 * @param pnmtv Pointer to an NMTREEVIEW structure. The itemOld and itemNew members of the
 *   NMTREEVIEW structure are TVITEM structures that contain information about the previously selected
 *   item and the newly selected item. Only the mask, hItem, state, and lParam members of these
 *   structures are valid. The stateMask members of the TVITEM structures specified by itemOld and
 *   itemNew are undefined on input. The action member of the NMTREEVIEW structure indicates the type
 *   of action that caused the selection to change. It is one of the following values: Value
 *   Description TVC_BYKEYBOARD By a keystroke. TVC_BYMOUSE By a mouse click. TVC_UNKNOWN Unknown.
 *
 * @return The return value is ignored.
 */
#define TVN_SELCHANGED          TVN_SELCHANGEDW
/**
 * This notification message requests that a tree view control's parent window provide information
 * needed to display or sort an item. It is sent in the form of a WM_NOTIFY message.
 *
 * @param lptvdi Long pointer to an NMTVDISPINFO structure. The item member is a TVITEM structure
 *   whose mask, hItem, state, and lParam members specify the type of information required. You must
 *   fill the members of the structure with the appropriate information.
 *
 * @return The return value is ignored.
 *
 * This notification is sent under the following circumstances:
 *
 * If the pszText member of the item's TVITEM structure is the LPSTR_TEXTCALLBACK value, the control
 * sends this notification to retrieve the item's text. In this case, the mask member of lptvdi will
 * have the TVIF_TEXT flag set.
 *
 * If the iImage or iSelectedImage member of the item's TVITEM structure is the I_IMAGECALLBACK
 * value, the control sends this notification to retrieve the index of an item's icons in the
 * control's image list. In this case, if the item is selected, the mask member of lptvdi will have
 * the TVIF_SELECTEDIMAGE flag set. If the item is not selected, the mask member of lptvdi will have
 * the TVIF_IMAGE flag set.
 *
 * If the cChildren member of the item's TVITEM structure is the I_CHILDRENCALLBACK value, the
 * control sends this notification to retrieve a value that indicates whether the item has child
 * items. In this case, the mask member of lptvdi will have the TVIF_CHILDREN flag set.
 */
#define TVN_GETDISPINFO         TVN_GETDISPINFOW
/**
 * This notification message notifies a tree view control's parent window that it must update the
 * information it maintains about an item. It is sent in the form of a WM_NOTIFY message.
 *
 * @param lptvdi Long pointer to an NMTVDISPINFO structure. The itemOld and itemNew members contain
 *   valid information about the currently selected item and the newly selected item. The action
 *   member indicates whether a mouse or keyboard action is causing the selection to change. For a
 *   list of possible values, see the description of the TVN_SELCHANGED notification message.
 *
 * @return The return value is ignored.
 */
#define TVN_SETDISPINFO         TVN_SETDISPINFOW
/**
 * This notification message notifies a tree view control's parent window that a parent item's list
 * of child items is about to expand or collapse. It is sent in the form of a WM_NOTIFY message.
 *
 * @param pnmtv Pointer to an NMTREEVIEW structure. The itemNew member is a TVITEM structure that
 *   contains valid information about the parent item in the hItem, state, and lParam members. The
 *   action member indicates whether the list is to expand or collapse. For a list of possible values,
 *   see the description of the TVM_EXPAND message.
 *
 * @return TRUE prevents the list from expanding or collapsing.
 */
#define TVN_ITEMEXPANDING       TVN_ITEMEXPANDINGW
/**
 * This notification message notifies a tree view control's parent window that a parent item's list
 * of child items has expanded or collapsed. It is sent in the form of a WM_NOTIFY message.
 *
 * @param pnmtv Pointer to an NMTREEVIEW structure. The itemNew member is a TVITEM structure that
 *   contains valid information about the parent item in the hItem, state, and lParam members. The
 *   action member indicates whether the list expanded or collapsed. For a list of possible values,
 *   see the description of the TVM_EXPAND message.
 *
 * @return The return value is ignored.
 */
#define TVN_ITEMEXPANDED        TVN_ITEMEXPANDEDW
/**
 * This notification message notifies a tree view control's parent window that a drag-and-drop
 * operation is being initiated. It is sent in the form of a WM_NOTIFY message.
 *
 * @param pnmtv Pointer to an NMTREEVIEW structure. The itemNew member is a TVITEM structure that
 *   contains valid information about the item being dragged in the hItem, state, and lParam members.
 *   The ptDrag member specifies the current screen coordinates of the mouse.
 *
 * @return The return value is ignored.
 */
#define TVN_BEGINDRAG           TVN_BEGINDRAGW
#define TVN_BEGINRDRAG          TVN_BEGINRDRAGW
/**
 * This notification message notifies a tree view control's parent window that an item has been
 * deleted. It is sent in the form of a WM_NOTIFY message.
 *
 * @param pnmtv Pointer to an NMTREEVIEW structure. The itemOld member is a TVITEM structure whose
 *   hItem and lParam members contain valid information about the item being deleted.
 *
 * @return The return value is ignored.
 */
#define TVN_DELETEITEM          TVN_DELETEITEMW
/**
 * This notification message notifies a tree view control's parent window about the start of label
 * editing for an item. It is sent in the form of a WM_NOTIFY message.
 *
 * @param ptvdi Pointer to an NMTVDISPINFO structure. The item member is a TVITEM structure that
 *   contains valid information about the item being edited in the hItem, state, lParam, and pszText
 *   members.
 *
 * @return TRUE cancels label editing.
 */
#define TVN_BEGINLABELEDIT      TVN_BEGINLABELEDITW
/**
 * This notification message notifies a tree view control's parent window about the end of label
 * editing for an item. It is sent in the form of a WM_NOTIFY message.
 *
 * @param ptvdi Pointer to an NMTVDISPINFO structure. The item member of this structure is a TVITEM
 *   structure whose hItem, lParam, and pszText members contain valid information about the item that
 *   was edited. If label editing was canceled, the pszText member of the TVITEM structure is NULL;
 *   otherwise, pszText is the address of the edited text.
 *
 * @return If the pszText member is non-NULL, return TRUE to set the item's label to the edited
 *   text. Return FALSE to reject the edited text and revert to the original label.
 *
 * If the pszText member is NULL, the return value is ignored.
 */
#define TVN_ENDLABELEDIT        TVN_ENDLABELEDITW
#else
/**
 * This notification message notifies a tree view control's parent window that the selection is
 * about to change from one item to another. It is sent in the form of a WM_NOTIFY message.
 *
 * @param pnmtv Pointer to an NMTREEVIEW structure. The itemOld and itemNew members contain valid
 *   information about the currently selected item and the newly selected item. The action member
 *   indicates whether a mouse or keyboard action is causing the selection to change. For a list of
 *   possible values, see the description of the TVN_SELCHANGED notification message.
 *
 * @return TRUE prevents the selection from changing.
 */
#define TVN_SELCHANGING         TVN_SELCHANGINGA
/**
 * This notification message notifies a tree view control's parent window that the selection has
 * changed from one item to another. It is sent in the form of a WM_NOTIFY message.
 *
 * @param pnmtv Pointer to an NMTREEVIEW structure. The itemOld and itemNew members of the
 *   NMTREEVIEW structure are TVITEM structures that contain information about the previously selected
 *   item and the newly selected item. Only the mask, hItem, state, and lParam members of these
 *   structures are valid. The stateMask members of the TVITEM structures specified by itemOld and
 *   itemNew are undefined on input. The action member of the NMTREEVIEW structure indicates the type
 *   of action that caused the selection to change. It is one of the following values: Value
 *   Description TVC_BYKEYBOARD By a keystroke. TVC_BYMOUSE By a mouse click. TVC_UNKNOWN Unknown.
 *
 * @return The return value is ignored.
 */
#define TVN_SELCHANGED          TVN_SELCHANGEDA
/**
 * This notification message requests that a tree view control's parent window provide information
 * needed to display or sort an item. It is sent in the form of a WM_NOTIFY message.
 *
 * @param lptvdi Long pointer to an NMTVDISPINFO structure. The item member is a TVITEM structure
 *   whose mask, hItem, state, and lParam members specify the type of information required. You must
 *   fill the members of the structure with the appropriate information.
 *
 * @return The return value is ignored.
 *
 * This notification is sent under the following circumstances:
 *
 * If the pszText member of the item's TVITEM structure is the LPSTR_TEXTCALLBACK value, the control
 * sends this notification to retrieve the item's text. In this case, the mask member of lptvdi will
 * have the TVIF_TEXT flag set.
 *
 * If the iImage or iSelectedImage member of the item's TVITEM structure is the I_IMAGECALLBACK
 * value, the control sends this notification to retrieve the index of an item's icons in the
 * control's image list. In this case, if the item is selected, the mask member of lptvdi will have
 * the TVIF_SELECTEDIMAGE flag set. If the item is not selected, the mask member of lptvdi will have
 * the TVIF_IMAGE flag set.
 *
 * If the cChildren member of the item's TVITEM structure is the I_CHILDRENCALLBACK value, the
 * control sends this notification to retrieve a value that indicates whether the item has child
 * items. In this case, the mask member of lptvdi will have the TVIF_CHILDREN flag set.
 */
#define TVN_GETDISPINFO         TVN_GETDISPINFOA
/**
 * This notification message notifies a tree view control's parent window that it must update the
 * information it maintains about an item. It is sent in the form of a WM_NOTIFY message.
 *
 * @param lptvdi Long pointer to an NMTVDISPINFO structure. The itemOld and itemNew members contain
 *   valid information about the currently selected item and the newly selected item. The action
 *   member indicates whether a mouse or keyboard action is causing the selection to change. For a
 *   list of possible values, see the description of the TVN_SELCHANGED notification message.
 *
 * @return The return value is ignored.
 */
#define TVN_SETDISPINFO         TVN_SETDISPINFOA
/**
 * This notification message notifies a tree view control's parent window that a parent item's list
 * of child items is about to expand or collapse. It is sent in the form of a WM_NOTIFY message.
 *
 * @param pnmtv Pointer to an NMTREEVIEW structure. The itemNew member is a TVITEM structure that
 *   contains valid information about the parent item in the hItem, state, and lParam members. The
 *   action member indicates whether the list is to expand or collapse. For a list of possible values,
 *   see the description of the TVM_EXPAND message.
 *
 * @return TRUE prevents the list from expanding or collapsing.
 */
#define TVN_ITEMEXPANDING       TVN_ITEMEXPANDINGA
/**
 * This notification message notifies a tree view control's parent window that a parent item's list
 * of child items has expanded or collapsed. It is sent in the form of a WM_NOTIFY message.
 *
 * @param pnmtv Pointer to an NMTREEVIEW structure. The itemNew member is a TVITEM structure that
 *   contains valid information about the parent item in the hItem, state, and lParam members. The
 *   action member indicates whether the list expanded or collapsed. For a list of possible values,
 *   see the description of the TVM_EXPAND message.
 *
 * @return The return value is ignored.
 */
#define TVN_ITEMEXPANDED        TVN_ITEMEXPANDEDA
/**
 * This notification message notifies a tree view control's parent window that a drag-and-drop
 * operation is being initiated. It is sent in the form of a WM_NOTIFY message.
 *
 * @param pnmtv Pointer to an NMTREEVIEW structure. The itemNew member is a TVITEM structure that
 *   contains valid information about the item being dragged in the hItem, state, and lParam members.
 *   The ptDrag member specifies the current screen coordinates of the mouse.
 *
 * @return The return value is ignored.
 */
#define TVN_BEGINDRAG           TVN_BEGINDRAGA
#define TVN_BEGINRDRAG          TVN_BEGINRDRAGA
/**
 * This notification message notifies a tree view control's parent window that an item has been
 * deleted. It is sent in the form of a WM_NOTIFY message.
 *
 * @param pnmtv Pointer to an NMTREEVIEW structure. The itemOld member is a TVITEM structure whose
 *   hItem and lParam members contain valid information about the item being deleted.
 *
 * @return The return value is ignored.
 */
#define TVN_DELETEITEM          TVN_DELETEITEMA
/**
 * This notification message notifies a tree view control's parent window about the start of label
 * editing for an item. It is sent in the form of a WM_NOTIFY message.
 *
 * @param ptvdi Pointer to an NMTVDISPINFO structure. The item member is a TVITEM structure that
 *   contains valid information about the item being edited in the hItem, state, lParam, and pszText
 *   members.
 *
 * @return TRUE cancels label editing.
 */
#define TVN_BEGINLABELEDIT      TVN_BEGINLABELEDITA
/**
 * This notification message notifies a tree view control's parent window about the end of label
 * editing for an item. It is sent in the form of a WM_NOTIFY message.
 *
 * @param ptvdi Pointer to an NMTVDISPINFO structure. The item member of this structure is a TVITEM
 *   structure whose hItem, lParam, and pszText members contain valid information about the item that
 *   was edited. If label editing was canceled, the pszText member of the TVITEM structure is NULL;
 *   otherwise, pszText is the address of the edited text.
 *
 * @return If the pszText member is non-NULL, return TRUE to set the item's label to the edited
 *   text. Return FALSE to reject the edited text and revert to the original label.
 *
 * If the pszText member is NULL, the return value is ignored.
 */
#define TVN_ENDLABELEDIT        TVN_ENDLABELEDITA
#endif

#if (_WIN32_IE >= 0x0300)
/**
 * This structure contains information specific to an NM_CUSTOMDRAW notification message sent by a
 * tree view control.
 */
typedef struct tagNMTVCUSTOMDRAW
{
    /**
     * NMCUSTOMDRAW structure that contains general Custom Draw information.
     */
    NMCUSTOMDRAW nmcd;
    /**
     * COLORREF value that represents the color that is used to display text foreground in the list view
     * control.
     */
    COLORREF     clrText;
    /**
     * COLORREF value that represents the color that is used to display text background in the list view
     * control.
     */
    COLORREF     clrTextBk;
} NMTVCUSTOMDRAW, *LPNMTVCUSTOMDRAW;
#endif

#endif      // NOTREEVIEW

//====== TAB CONTROL ==========================================================

#ifndef NOTABCONTROL

#ifdef _WIN32

#define WC_TABCONTROLA          "SysTabControl32"
#define WC_TABCONTROLW          L"SysTabControl32"

#ifdef UNICODE
#define  WC_TABCONTROL          WC_TABCONTROLW
#else
#define  WC_TABCONTROL          WC_TABCONTROLA
#endif

#else
#define WC_TABCONTROL           "SysTabControl"
#endif

// begin_r_commctrl

#if (_WIN32_IE >= 0x0300)
#define TCS_SCROLLOPPOSITE      0x0001   // assumes multiline tab
#define TCS_BOTTOM              0x0002
#define TCS_RIGHT               0x0002
#define TCS_MULTISELECT         0x0004  // allow multi-select in button mode
#endif
#if (_WIN32_IE >= 0x0400)
#define TCS_FLATBUTTONS         0x0008
#endif
#define TCS_FORCEICONLEFT       0x0010
#define TCS_FORCELABELLEFT      0x0020
#if (_WIN32_IE >= 0x0300)
#define TCS_HOTTRACK            0x0040
#define TCS_VERTICAL            0x0080
#endif
#define TCS_TABS                0x0000
#define TCS_BUTTONS             0x0100
#define TCS_SINGLELINE          0x0000
#define TCS_MULTILINE           0x0200
#define TCS_RIGHTJUSTIFY        0x0000
#define TCS_FIXEDWIDTH          0x0400
#define TCS_RAGGEDRIGHT         0x0800
#define TCS_FOCUSONBUTTONDOWN   0x1000
#define TCS_OWNERDRAWFIXED      0x2000
#define TCS_FOCUSNEVER          0x8000

#if (_WIN32_IE >= 0x0400)
// EX styles for CreateWindowEx
#define TCS_EX_FLATSEPARATORS   0x00000001
#endif

// end_r_commctrl

#define TCM_FIRST               0x1300





/**
 * This message retrieves the image list associated with a tab control. You can send this message
 * explicitly or by using the TabCtrl_GetImageList macro.
 *
 * @return The handle to the image list indicates success. NULL indicates otherwise.
 */
#define TCM_GETIMAGELIST        (TCM_FIRST + 2)
/**
 * This macro retrieves the image list associated with a tab control. You can use this macro or send
 * the TCM_GETIMAGELIST message explicitly.
 *
 * @param hwnd Handle to the tab control.
 *
 * @return The handle to the image list indicates success. NULL indicates failure.
 */
#define TabCtrl_GetImageList(hwnd) \
    (HIMAGELIST)SNDMSG((hwnd), TCM_GETIMAGELIST, 0, 0L)


/**
 * This message assigns an image list to a tab control. You can send this message explicitly or by
 * using the TabCtrl_SetImageList macro.
 *
 * @param himl Handle to the image list to assign to the tab control.
 *
 * @return The handle to the previous image list indicates success. NULL indicates that there is no
 *   previous image list.
 */
#define TCM_SETIMAGELIST        (TCM_FIRST + 3)
/**
 * This macro assigns an image list to a tab control. You can use this macro or send the
 * TCM_SETIMAGELIST message explicitly.
 *
 * @param hwnd Handle to the tab control.
 * @param himl Handle to the image list to assign to the tab control.
 *
 * @return The handle to the previous image list indicates success. NULL indicates that there is no
 *   previous image list.
 */
#define TabCtrl_SetImageList(hwnd, himl) \
    (HIMAGELIST)SNDMSG((hwnd), TCM_SETIMAGELIST, 0, (LPARAM)(UINT)(HIMAGELIST)(himl))


/**
 * This message retrieves the number of tabs in the tab control. You can send this message
 * explicitly or by using the TabCtrl_GetItemCount macro.
 *
 * @return The number of items indicates success. Zero indicates otherwise.
 */
#define TCM_GETITEMCOUNT        (TCM_FIRST + 4)
/**
 * This macro retrieves the number of tabs in the tab control. You can use this macro or send the
 * TCM_GETITEMCOUNT message explicitly.
 *
 * @param hwnd Handle to the tab control.
 *
 * @return The number of tabs indicates success. Zero indicates failure.
 */
#define TabCtrl_GetItemCount(hwnd) \
    (int)SNDMSG((hwnd), TCM_GETITEMCOUNT, 0, 0L)


#define TCIF_TEXT               0x0001
#define TCIF_IMAGE              0x0002
#define TCIF_RTLREADING         0x0004
#define TCIF_PARAM              0x0008
#if (_WIN32_IE >= 0x0300)
#define TCIF_STATE              0x0010


#define TCIS_BUTTONPRESSED      0x0001
#endif
#if (_WIN32_IE >= 0x0400)
#define TCIS_HIGHLIGHTED        0x0002
#endif

#if (_WIN32_IE >= 0x0300)
#define TC_ITEMHEADERA         TCITEMHEADERA
#define TC_ITEMHEADERW         TCITEMHEADERW
#else
#define tagTCITEMHEADERA       _TC_ITEMHEADERA
#define    TCITEMHEADERA        TC_ITEMHEADERA
#define tagTCITEMHEADERW       _TC_ITEMHEADERW
#define    TCITEMHEADERW        TC_ITEMHEADERW
#endif
#define TC_ITEMHEADER          TCITEMHEADER

/**
 * This structure specifies or receives the attributes of a tab. It is used with the TCM_INSERTITEM,
 * TCM_GETITEM, and TCM_SETITEM messages.
 *
 * This structure supersedes the TC_ITEMHEADER structure.
 */
typedef struct tagTCITEMHEADERA
{
    /**
     * Specifies which members to retrieve or set. It can be a combination of the following values:
     * Value Description TCIF_IMAGE The iImage member is valid. TCIF_RTLREADING The text of pszText is
     * displayed using right-to-left reading order on Hebrew or Arabic systems. TCIF_TEXT The pszText
     * member is valid.
     */
    UINT mask;
    /**
     * Reserved; do not use.
     */
    UINT lpReserved1;
    /**
     * Reserved; do not use.
     */
    UINT lpReserved2;
    /**
     * Pointer to a null-terminated string that contains the tab text if item information is being set.
     * If item information is being retrieved, this member specifies the address of the buffer that
     * receives the tab text.
     */
    LPSTR pszText;
    /**
     * Size of the buffer pointed to by the pszText member. If the structure is not receiving
     * information, this member is ignored.
     */
    int cchTextMax;
    /**
     * Index into the tab control's image list, or -1 if there is no image for the tab.
     */
    int iImage;
} TCITEMHEADERA, FAR *LPTCITEMHEADERA;

/**
 * This structure specifies or receives the attributes of a tab. It is used with the TCM_INSERTITEM,
 * TCM_GETITEM, and TCM_SETITEM messages.
 *
 * This structure supersedes the TC_ITEMHEADER structure.
 */
typedef struct tagTCITEMHEADERW
{
    /**
     * Specifies which members to retrieve or set. It can be a combination of the following values:
     * Value Description TCIF_IMAGE The iImage member is valid. TCIF_RTLREADING The text of pszText is
     * displayed using right-to-left reading order on Hebrew or Arabic systems. TCIF_TEXT The pszText
     * member is valid.
     */
    UINT mask;
    /**
     * Reserved; do not use.
     */
    UINT lpReserved1;
    /**
     * Reserved; do not use.
     */
    UINT lpReserved2;
    /**
     * Pointer to a null-terminated string that contains the tab text if item information is being set.
     * If item information is being retrieved, this member specifies the address of the buffer that
     * receives the tab text.
     */
    LPWSTR pszText;
    /**
     * Size of the buffer pointed to by the pszText member. If the structure is not receiving
     * information, this member is ignored.
     */
    int cchTextMax;
    /**
     * Index into the tab control's image list, or -1 if there is no image for the tab.
     */
    int iImage;
} TCITEMHEADERW, FAR *LPTCITEMHEADERW;

#ifdef UNICODE
#define  TCITEMHEADER          TCITEMHEADERW
#define  LPTCITEMHEADER        LPTCITEMHEADERW
#else
#define  TCITEMHEADER          TCITEMHEADERA
#define  LPTCITEMHEADER        LPTCITEMHEADERA
#endif


#if (_WIN32_IE >= 0x0300)
#define TC_ITEMA                TCITEMA
#define TC_ITEMW                TCITEMW
#else
#define tagTCITEMA              _TC_ITEMA
#define    TCITEMA               TC_ITEMA
#define tagTCITEMW              _TC_ITEMW
#define    TCITEMW               TC_ITEMW
#endif
#define TC_ITEM                 TCITEM

/**
 * This structure specifies or receives the attributes of a tab item. It is used with the
 * TCM_INSERTITEM, TCM_GETITEM, and TCM_SETITEM messages.
 *
 * This structure supersedes the TC_ITEM structure.
 */
typedef struct tagTCITEMA
{
    /**
     * Specifies which members to retrieve or set. It can be a combination of the following values:
     * Value Description TCIF_IMAGE The iImage member is valid. TCIF_PARAM The lParam member is valid.
     * TCIF_RTLREADING The text of pszText is displayed using right-to-left reading order on Hebrew or
     * Arabic systems. TCIF_STATE The dwState member is valid. TCIF_TEXT The pszText member is valid.
     */
    UINT mask;
#if (_WIN32_IE >= 0x0300)
    /**
     * Specifies the item's current state if information is being retrieved. If item information is
     * being set, this member contains the state value to be set for the item. For a list of valid tab
     * control item states, see Tab Control Item States.
     */
    DWORD dwState;
    /**
     * Specifies which bits of the dwState member are valid.
     */
    DWORD dwStateMask;
#else
    UINT lpReserved1;
    UINT lpReserved2;
#endif
    /**
     * Pointer to a null-terminated string that contains the tab text when item information is being
     * set. If item information is being retrieved, this member specifies the address of the buffer that
     * receives the tab text.
     */
    LPSTR pszText;
    int cchTextMax;
    /**
     * Index into the tab control's image list, or -1 if there is no image for the tab.
     */
    int iImage;

    /**
     * Application-defined data associated with the tab control item. If more or less than 4 bytes of
     * application-defined data exist per tab, an application must define a structure and use it instead
     * of the TCITEM structure. The first member of the application-defined structure must be a
     * TCITEMHEADER structure.
     */
    LPARAM lParam;
} TCITEMA, FAR *LPTCITEMA;

/**
 * This structure specifies or receives the attributes of a tab item. It is used with the
 * TCM_INSERTITEM, TCM_GETITEM, and TCM_SETITEM messages.
 *
 * This structure supersedes the TC_ITEM structure.
 */
typedef struct tagTCITEMW
{
    /**
     * Specifies which members to retrieve or set. It can be a combination of the following values:
     * Value Description TCIF_IMAGE The iImage member is valid. TCIF_PARAM The lParam member is valid.
     * TCIF_RTLREADING The text of pszText is displayed using right-to-left reading order on Hebrew or
     * Arabic systems. TCIF_STATE The dwState member is valid. TCIF_TEXT The pszText member is valid.
     */
    UINT mask;
#if (_WIN32_IE >= 0x0300)
    /**
     * Specifies the item's current state if information is being retrieved. If item information is
     * being set, this member contains the state value to be set for the item. For a list of valid tab
     * control item states, see Tab Control Item States.
     */
    DWORD dwState;
    /**
     * Specifies which bits of the dwState member are valid.
     */
    DWORD dwStateMask;
#else
    UINT lpReserved1;
    UINT lpReserved2;
#endif
    /**
     * Pointer to a null-terminated string that contains the tab text when item information is being
     * set. If item information is being retrieved, this member specifies the address of the buffer that
     * receives the tab text.
     */
    LPWSTR pszText;
    int cchTextMax;
    /**
     * Index into the tab control's image list, or -1 if there is no image for the tab.
     */
    int iImage;

    /**
     * Application-defined data associated with the tab control item. If more or less than 4 bytes of
     * application-defined data exist per tab, an application must define a structure and use it instead
     * of the TCITEM structure. The first member of the application-defined structure must be a
     * TCITEMHEADER structure.
     */
    LPARAM lParam;
} TCITEMW, FAR *LPTCITEMW;

#ifdef UNICODE
#define  TCITEM                 TCITEMW
#define  LPTCITEM               LPTCITEMW
#else
#define  TCITEM                 TCITEMA
#define  LPTCITEM               LPTCITEMA
#endif


#define TCM_GETITEMA            (TCM_FIRST + 5)
#define TCM_GETITEMW            (TCM_FIRST + 60)

#ifdef UNICODE
/**
 * This message retrieves information about a tab in a tab control. You can send this message
 * explicitly or by using the TabCtrl_GetItem macro.
 *
 * @param iItem Index of the tab.
 * @param pitem Pointer to a TCITEM structure that specifies the information to retrieve and
 *   receives information about the tab. When the message is sent, the mask member specifies which
 *   attributes to return. If the mask member specifies the TCIF_TEXT value, the pszText member must
 *   contain the address of the buffer that receives the item text, and the cchTextMax member must
 *   specify the size of the buffer.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define TCM_GETITEM             TCM_GETITEMW
#else
/**
 * This message retrieves information about a tab in a tab control. You can send this message
 * explicitly or by using the TabCtrl_GetItem macro.
 *
 * @param iItem Index of the tab.
 * @param pitem Pointer to a TCITEM structure that specifies the information to retrieve and
 *   receives information about the tab. When the message is sent, the mask member specifies which
 *   attributes to return. If the mask member specifies the TCIF_TEXT value, the pszText member must
 *   contain the address of the buffer that receives the item text, and the cchTextMax member must
 *   specify the size of the buffer.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define TCM_GETITEM             TCM_GETITEMA
#endif

/**
 * This macro retrieves information about a tab in a tab control. You can use this macro or send the
 * TCM_GETITEM message explicitly.
 *
 * @param hwnd Handle to the tab control.
 * @param iItem Index of the tab.
 * @param pitem Pointer to a TCITEM structure that specifies the information to retrieve and
 *   receives information about the tab. When the message is sent, the mask member specifies which
 *   attributes to return. If the mask member specifies the TCIF_TEXT value, the pszText member must
 *   contain the address of the buffer that receives the item text, and the cchTextMax member must
 *   specify the size of the buffer.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define TabCtrl_GetItem(hwnd, iItem, pitem) \
    (BOOL)SNDMSG((hwnd), TCM_GETITEM, (WPARAM)(int)iItem, (LPARAM)(TC_ITEM FAR*)(pitem))


#define TCM_SETITEMA            (TCM_FIRST + 6)
#define TCM_SETITEMW            (TCM_FIRST + 61)

#ifdef UNICODE
/**
 * This message sets some or all of a tab's attributes. You can send this message explicitly or by
 * using the TabCtrl_SetItem macro.
 *
 * @param iItem Index of the item.
 * @param pitem Pointer to a TCITEM structure that contains the new item attributes. The mask member
 *   specifies which attributes to set. If the mask member specifies the LVIF_TEXT value, the pszText
 *   member is the address of a null-terminated string and the cchTextMax member is ignored.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define TCM_SETITEM             TCM_SETITEMW
#else
/**
 * This message sets some or all of a tab's attributes. You can send this message explicitly or by
 * using the TabCtrl_SetItem macro.
 *
 * @param iItem Index of the item.
 * @param pitem Pointer to a TCITEM structure that contains the new item attributes. The mask member
 *   specifies which attributes to set. If the mask member specifies the LVIF_TEXT value, the pszText
 *   member is the address of a null-terminated string and the cchTextMax member is ignored.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define TCM_SETITEM             TCM_SETITEMA
#endif

/**
 * This macro sets some or all of a tab's attributes. You can use this macro or send the TCM_SETITEM
 * message explicitly.
 *
 * @param hwnd Handle to the tab control.
 * @param iItem Index of the item.
 * @param pitem Pointer to a TCITEM structure that contains the new item attributes. The mask member
 *   specifies which attributes to set. If the mask member specifies the LVIF_TEXT value, the pszText
 *   member is the address of a null-terminated string and the cchTextMax member is ignored.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define TabCtrl_SetItem(hwnd, iItem, pitem) \
    (BOOL)SNDMSG((hwnd), TCM_SETITEM, (WPARAM)(int)iItem, (LPARAM)(TC_ITEM FAR*)(pitem))


#define TCM_INSERTITEMA         (TCM_FIRST + 7)
#define TCM_INSERTITEMW         (TCM_FIRST + 62)

#ifdef UNICODE
/**
 * This message inserts a new tab in a tab control. You can send this message explicitly or by using
 * the TabCtrl_InsertItem macro.
 *
 * @param iItem Index of the new tab.
 * @param pitem Pointer to a TCITEM structure that specifies the attributes of the tab. The dwState
 *   and dwStateMask members of this structure are ignored by this message.
 *
 * @return The index of the new tab indicates success. -1 indicates otherwise.
 */
#define TCM_INSERTITEM          TCM_INSERTITEMW
#else
/**
 * This message inserts a new tab in a tab control. You can send this message explicitly or by using
 * the TabCtrl_InsertItem macro.
 *
 * @param iItem Index of the new tab.
 * @param pitem Pointer to a TCITEM structure that specifies the attributes of the tab. The dwState
 *   and dwStateMask members of this structure are ignored by this message.
 *
 * @return The index of the new tab indicates success. -1 indicates otherwise.
 */
#define TCM_INSERTITEM          TCM_INSERTITEMA
#endif

/**
 * This macro inserts a new tab in a tab control. You can use this macro or send the TCM_INSERTITEM
 * message explicitly.
 *
 * @param hwnd Handle to the tab control.
 * @param iItem Index of the new tab.
 * @param pitem Pointer to a TCITEM structure that specifies the attributes of the tab. The dwState
 *   and dwStateMask members of this structure are ignored by this message.
 *
 * @return The index of the new tab indicates success. -1 indicates failure.
 */
#define TabCtrl_InsertItem(hwnd, iItem, pitem)   \
    (int)SNDMSG((hwnd), TCM_INSERTITEM, (WPARAM)(int)iItem, (LPARAM)(const TC_ITEM FAR*)(pitem))


/**
 * This message removes an item from a tab control. You can send this message explicitly or by using
 * the TabCtrl_DeleteItem macro.
 *
 * @param iItem Index of the item to delete.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define TCM_DELETEITEM          (TCM_FIRST + 8)
/**
 * This macro removes an item from a tab control. You can use this macro or send the TCM_DELETEITEM
 * message explicitly.
 *
 * @param hwnd Handle to the tab control.
 * @param iItem Index of the item to delete.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define TabCtrl_DeleteItem(hwnd, i) \
    (BOOL)SNDMSG((hwnd), TCM_DELETEITEM, (WPARAM)(int)(i), 0L)


/**
 * This message removes all items from a tab control. You can send this message explicitly or by
 * using the TabCtrl_DeleteAllItems macro.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define TCM_DELETEALLITEMS      (TCM_FIRST + 9)
/**
 * This macro removes all items from a tab control. You can use this macro or send the
 * TCM_DELETEALLITEMS message explicitly.
 *
 * @param hwnd Handle to the tab control.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define TabCtrl_DeleteAllItems(hwnd) \
    (BOOL)SNDMSG((hwnd), TCM_DELETEALLITEMS, 0, 0L)


/**
 * This message retrieves the bounding rectangle for a tab in a tab control. You can send this
 * message explicitly or by using the TabCtrl_GetItemRect macro.
 *
 * @param iItem Index of the tab.
 * @param prc Pointer to a RECT structure that receives the bounding rectangle of the tab, in
 *   viewport coordinates.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define TCM_GETITEMRECT         (TCM_FIRST + 10)
/**
 * This macro retrieves the bounding rectangle for a tab in a tab control. You can use this macro or
 * send the TCM_GETITEMRECT message explicitly.
 *
 * @param hwnd Handle to the tab control.
 * @param iItem Index of the tab.
 * @param prc Pointer to a RECT structure that receives the bounding rectangle of the tab, in
 *   viewport coordinates.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define TabCtrl_GetItemRect(hwnd, i, prc) \
    (BOOL)SNDMSG((hwnd), TCM_GETITEMRECT, (WPARAM)(int)(i), (LPARAM)(RECT FAR*)(prc))


/**
 * This message determines the currently selected tab in a tab control. You can send this message
 * explicitly or by using the TabCtrl_GetCurSel macro.
 *
 * @return The index of the selected tab indicates success. -1 indicates that no tab is selected.
 */
#define TCM_GETCURSEL           (TCM_FIRST + 11)
/**
 * This macro determines the currently selected tab in a tab control. You can use this macro or send
 * the TCM_GETCURSEL message explicitly.
 *
 * @param hwnd Handle to the tab control.
 *
 * @return The index of the selected tab indicates success. -1 indicates that no tab is selected.
 */
#define TabCtrl_GetCurSel(hwnd) \
    (int)SNDMSG((hwnd), TCM_GETCURSEL, 0, 0)


/**
 * This message selects a tab in a tab control. You can send this message explicitly or by using the
 * TabCtrl_SetCurSel macro.
 *
 * @param iItem Index of the tab to select.
 *
 * @return The index of the previously selected tab indicates success. -1 indicates otherwise.
 */
#define TCM_SETCURSEL           (TCM_FIRST + 12)
/**
 * This macro selects a tab in a tab control. You can use this macro or send the TCM_SETCURSEL
 * message explicitly.
 *
 * @param hwnd Handle to the tab control.
 * @param iItem Index of the tab to select.
 *
 * @return The index of the previously selected tab indicates success. -1 indicates failure.
 *
 * A tab control does not send a TCN_SELCHANGING or TCN_SELCHANGE notification message when a tab is
 * selected using the TCM_SETCUSEL message.
 */
#define TabCtrl_SetCurSel(hwnd, i) \
    (int)SNDMSG((hwnd), TCM_SETCURSEL, (WPARAM)i, 0)


#define TCHT_NOWHERE            0x0001
#define TCHT_ONITEMICON         0x0002
#define TCHT_ONITEMLABEL        0x0004
#define TCHT_ONITEM             (TCHT_ONITEMICON | TCHT_ONITEMLABEL)

#if (_WIN32_IE >= 0x0300)
#define LPTC_HITTESTINFO        LPTCHITTESTINFO
#define TC_HITTESTINFO          TCHITTESTINFO
#else
#define tagTCHITTESTINFO        _TC_HITTESTINFO
#define    TCHITTESTINFO         TC_HITTESTINFO
#define  LPTCHITTESTINFO       LPTC_HITTESTINFO
#endif

typedef struct tagTCHITTESTINFO
{
    POINT pt;
    UINT flags;
} TCHITTESTINFO, FAR * LPTCHITTESTINFO;

/**
 * This message determines which tab, if any, is at a specified screen position. You can send this
 * message explicitly or by using the TabCtrl_HitTest macro.
 *
 * @param pinfo Pointer to a TCHITTESTINFO structure that specifies the screen position to test.
 *
 * @return The index of the tab indicates success. -1 indicates that no tab is at the specified
 *   position.
 */
#define TCM_HITTEST             (TCM_FIRST + 13)
/**
 * This macro determines which tab, if any, is at a specified screen position. You can use this
 * macro or send the TCM_HITTEST message explicitly.
 *
 * @param hwnd Handle to the tab control.
 * @param pinfo Pointer to a TCHITTESTINFO structure that specifies the screen position to test.
 *
 * @return The index of the tab indicates success. -1 indicates that no tab is at the specified
 *   position.
 */
#define TabCtrl_HitTest(hwndTC, pinfo) \
    (int)SNDMSG((hwndTC), TCM_HITTEST, 0, (LPARAM)(TC_HITTESTINFO FAR*)(pinfo))


/**
 * This message sets the number of bytes per tab reserved for application-defined data in a tab
 * control. You can send this message explicitly or by using the TabCtrl_SetItemExtra macro.
 *
 * @param cb Number of extra bytes.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * By default, the number of extra bytes is four. An application that changes the number of extra
 * bytes cannot use the TCITEM structure to retrieve and set the application-defined data for a tab.
 * Instead, you must define a new structure that consists of the TCITEMHEADER structure followed by
 * application-defined members.
 */
#define TCM_SETITEMEXTRA        (TCM_FIRST + 14)
/**
 * This macro sets the number of bytes per tab reserved for application-defined data in a tab
 * control. You can use this macro or send the TCM_SETITEMEXTRA message explicitly.
 *
 * @param hwnd Handle to the tab control.
 * @param cb Number of extra bytes.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * By default, the number of extra bytes is four. An application that changes the number of extra
 * bytes cannot use the TCITEM structure to retrieve and set the application-defined data for a tab.
 * Instead, you must define a new structure that consists of the TCITEMHEADER structure followed by
 * application-defined members.
 *
 * An application should only change the number of extra bytes when a tab control does not contain
 * any tabs.
 */
#define TabCtrl_SetItemExtra(hwndTC, cb) \
    (BOOL)SNDMSG((hwndTC), TCM_SETITEMEXTRA, (WPARAM)(cb), 0L)


/**
 * This message calculates a tab control's display area specified a window rectangle or calculates
 * the window rectangle that would correspond to a specified display area. You can send this message
 * explicitly or by using the TabCtrl_AdjustRect macro.
 *
 * @param fLarger Operation to perform. If set to TRUE, prc specifies a display rectangle and
 *   receives the corresponding window rectangle. If set to FALSE, prc specifies a window rectangle
 *   and receives the corresponding display area.
 * @param prc Pointer to a RECT structure that specifies the specified rectangle and receives the
 *   calculated rectangle.
 *
 * @return None.
 */
#define TCM_ADJUSTRECT          (TCM_FIRST + 40)
/**
 * This macro calculates a tab control's display area Nonzero indicates success. Zero indicates
 * otherwise. a window rectangle, or calculates the window rectangle that would correspond to a
 * specified display area. You can use this macro or send the TCM_ADJUSTRECT message explicitly.
 *
 * @param hwnd Handle to the tab control.
 * @param fLarger Boolean value that specifies the operation to perform. If set to TRUE, prc
 *   specifies a display rectangle and receives the corresponding window rectangle. If set to FALSE,
 *   prc specifies a window rectangle and receives the corresponding display area.
 * @param prc Pointer to a RECT structure that specifies the Nonzero indicates success. Zero
 *   indicates otherwise. rectangle and receives the calculated rectangle.
 *
 * @return None.
 */
#define TabCtrl_AdjustRect(hwnd, bLarger, prc) \
    (int)SNDMSG(hwnd, TCM_ADJUSTRECT, (WPARAM)(BOOL)bLarger, (LPARAM)(RECT FAR *)prc)


/**
 * This message sets the width and height of tabs in a fixed-width or owner-drawn tab control. You
 * can send this message explicitly or by using the TabCtrl_SetItemSize macro.
 *
 * @param cx and cy New width and height, in pixels.
 *
 * @return Returns the old width and height. The width is in the low-order word of the return value,
 *   and the height is in the high-order word.
 */
#define TCM_SETITEMSIZE         (TCM_FIRST + 41)
/**
 * This macro sets the width and height of tabs in a fixed-width or owner-drawn tab control. You can
 * use this macro or send the TCM_SETITEMSIZE message explicitly.
 *
 * @param hwnd Handle to the tab control.
 * @param cx and cy New width and height, in pixels.
 *
 * @return Returns the old width and height. The width is in the low-order word of the return value,
 *   and the height is in the high-order word.
 */
#define TabCtrl_SetItemSize(hwnd, x, y) \
    (DWORD)SNDMSG((hwnd), TCM_SETITEMSIZE, 0, MAKELPARAM(x,y))


/**
 * This message removes an image from a tab control's image list. You can send this message
 * explicitly or by using the TabCtrl_RemoveImage macro.
 *
 * @param iImage Index of the image to remove.
 *
 * @return None.
 */
#define TCM_REMOVEIMAGE         (TCM_FIRST + 42)
/**
 * This macro removes an image from a tab control's image list. You can use this macro or send the
 * TCM_REMOVEIMAGE message explicitly.
 *
 * @param hwnd Handle to the tab control.
 * @param iImage Index of the image to remove.
 *
 * @return None.
 *
 * The tab control updates each tab's image index, so each tab remains associated with the same
 * image as before. If a tab is using the image being removed, the tab will be set to have no image.
 */
#define TabCtrl_RemoveImage(hwnd, i) \
        (void)SNDMSG((hwnd), TCM_REMOVEIMAGE, i, 0L)


/**
 * This message sets the amount of space (padding) around each tab's icon and label in a tab
 * control. You can send this message explicitly or by using the TabCtrl_SetPadding macro.
 *
 * @param cx and cy Amount of horizontal and vertical padding, in pixels.
 *
 * @return None.
 */
#define TCM_SETPADDING          (TCM_FIRST + 43)
/**
 * This macro sets the amount of space (padding) around each tab's icon and label in a tab control.
 * You can use this macro or send the TCM_SETPADDING message explicitly.
 *
 * @param hwnd Handle to the tab control.
 * @param cx and cy Amount of horizontal and vertical padding, in pixels.
 *
 * @return None.
 */
#define TabCtrl_SetPadding(hwnd,  cx, cy) \
        (void)SNDMSG((hwnd), TCM_SETPADDING, 0, MAKELPARAM(cx, cy))


/**
 * This message retrieves the current number of rows of tabs in a tab control. You can send this
 * message explicitly or by using the TabCtrl_GetRowCount macro.
 *
 * @return Returns the number of rows of tabs.
 */
#define TCM_GETROWCOUNT         (TCM_FIRST + 44)
/**
 * This macro retrieves the current number of rows of tabs in a tab control. You can use this macro
 * or send the TCM_GETROWCOUNT message explicitly.
 *
 * @param hwnd Handle to the tab control.
 *
 * @return Returns the number of rows of tabs.
 *
 * Only tab controls that have the TCS_MUTLILINE style can have multiple rows of tabs.
 */
#define TabCtrl_GetRowCount(hwnd) \
        (int)SNDMSG((hwnd), TCM_GETROWCOUNT, 0, 0L)

/**
 * This message returns the index of the item that has the focus in a tab control. You can send this
 * message explicitly or by using the TabCtrl_GetCurFocus macro.
 *
 * @return Returns the index of the tab item that has the focus.
 */
#define TCM_GETCURFOCUS         (TCM_FIRST + 47)
/**
 * This macro returns the index of the item that has the focus in a tab control. You can use this
 * macro or send the TCM_GETCURFOCUS message explicitly.
 *
 * @param hwnd Handle to the tab control.
 *
 * @return The index of the tab item that has the focus indicates success.
 *
 * The item that has the focus may be different from the selected item.
 */
#define TabCtrl_GetCurFocus(hwnd) \
    (int)SNDMSG((hwnd), TCM_GETCURFOCUS, 0, 0)

/**
 * This message sets the focus to a specified tab in a tab control. You can send this message
 * explicitly or by using the TabCtrl_SetCurFocus macro.
 *
 * @param iItem Index of the tab that gets the focus.
 *
 * @return None.
 *
 * If the tab control has the TCS_BUTTONS style (button mode), the tab with the focus may be
 * different from the selected tab. For example, when a tab is selected, the user can press the
 * arrow keys to set the focus to a different tab without changing the selected tab. In button mode,
 * TCM_SETCURFOCUS sets the input focus to the button associated with the specified tab, but it does
 * not change the selected tab.
 *
 * If the tab control does not have the TCS_BUTTONS style, changing the focus also changes the
 * selected tab. In this case, the tab control sends the TCN_SELCHANGING and TCN_SELCHANGE
 * notification messages to its parent window.
 */
#define TCM_SETCURFOCUS         (TCM_FIRST + 48)
/**
 * This macro sets the focus to a specified tab in a tab control. You can use this macro or send the
 * TCM_SETCURFOCUS message explicitly.
 *
 * @param hwnd Handle to the tab control.
 * @param iItem Zero-based index of the tab that gets the focus.
 *
 * @return None.
 *
 * If the tab control has the TCS_BUTTONS style (button mode), the tab with the focus may be
 * different from the selected tab. For example, when a tab is selected, the user can press the
 * arrow keys to set the focus to a different tab without changing the selected tab. In button mode,
 * the TabCtrl_SetCurFocus macro sets the input focus to the button associated with the specified
 * tab, but it does not change the selected tab.
 *
 * If the tab control does not have the TCS_BUTTONS style, changing the focus also changes the
 * selected tab. In this case, the tab control sends the TCN_SELCHANGING and TCN_SELCHANGE
 * notification messages to its parent window.
 */
#define TabCtrl_SetCurFocus(hwnd, i) \
    SNDMSG((hwnd),TCM_SETCURFOCUS, i, 0)

#if (_WIN32_IE >= 0x0300)
/**
 * This message sets the minimum width of items in a tab control.
 *
 * @param cx Minimum width to be set for a tab control item. If this parameter is set to -1, the
 *   control uses the default tab width.
 *
 * @return Returns an INT value that represents the previous minimum tab width.
 */
#define TCM_SETMINTABWIDTH      (TCM_FIRST + 49)
/**
 * This macro sets the minimum width of items in a tab control.
 *
 * @param hwndTab Handle to the tab control.
 * @param cx Minimum width to be set for a tab control item. If this parameter is set to -1, the
 *   control will use the default tab width.
 *
 * @return Integer that represents the previous minimum tab width.
 */
#define TabCtrl_SetMinTabWidth(hwnd, x) \
        (int)SNDMSG((hwnd), TCM_SETMINTABWIDTH, 0, x)


/**
 * This message resets items in a tab control, clearing any that were set to the TCIS_BUTTONPRESSED
 * state.
 *
 * @param fExcludeFocus Boolean that specifies the scope of the item deselection. If this parameter
 *   is set to FALSE, all tab buttons are reset. If it is set to TRUE, then all tab items except for
 *   the one currently selected are reset.
 *
 * @return The return value for this message is not used.
 */
#define TCM_DESELECTALL         (TCM_FIRST + 50)
/**
 * This macro resets items in a tab control, clearing any that were set to the TCIS_BUTTONPRESSED
 * state.
 *
 * @param hwndTab Handle to the tab control.
 * @param fExcludeFocus Value that specifies the scope of the item deselection. If set to FALSE, all
 *   tab items will be reset. If set to TRUE, all but the currently selected tab item will be reset.
 */
#define TabCtrl_DeselectAll(hwnd, fExcludeFocus)\
        (void)SNDMSG((hwnd), TCM_DESELECTALL, fExcludeFocus, 0)
#endif

#if (_WIN32_IE >= 0x0400)

/**
 * This message sets the highlight state of a tab item.
 *
 * @param idItem Zero-based index of a tab control item.
 * @param fHighlight Boolean that specifies whether the highlight state is to be set. If this value
 *   is TRUE, the tab is highlighted; if FALSE, the tab is set to its default state.
 *
 * @return Nonzero indicates success. Zero indicates otherwise.
 */
#define TCM_HIGHLIGHTITEM       (TCM_FIRST + 51)
/**
 * This macro sets the highlight state of a tab item.
 *
 * @param hwndTab Handle to the tab control.
 * @param idItem Zero-based index of a tab control item.
 * @param fHighlight Value that specifies the highlight state to be set. If this value is nonzero,
 *   the tab is highlighted. If this value is zero, the tab is set to its default state.
 *
 * @return Nonzero indicates success. Zero indicates otherwise.
 */
#define TabCtrl_HighlightItem(hwnd, i, fHighlight) \
    (BOOL)SNDMSG((hwnd), TCM_HIGHLIGHTITEM, (WPARAM)i, (LPARAM)MAKELONG (fHighlight, 0))

/**
 * This message sets the extended styles that the tab control will use.
 *
 * @param dwExMask Specifies which styles in dwExStyle are to be affected. Only the extended styles
 *   in dwExMask will be changed. All other styles will be maintained as is. If this parameter is
 *   zero, then all of the styles in dwExStyle will be affected.
 * @param dwExStyle Specifies the extended tab control styles. This value is a combination of Tab
 *   Control extended styles.
 * @param dwExMask Allows you to modify one or more extended styles without having to retrieve the
 *   existing styles first. For example: if you pass TCS_EX_FLATSEPARATORS for dwExMask and 0 for
 *   dwExStyle, the TCS_EX_FLATSEPARATORS style will be cleared, but all other styles will remain the
 *   same. For backward compatibility reasons, the TabCtrl_SetExtendedStyle macro has not been updated
 *   to use dwExMask.
 *
 * @return Returns a DWORD value that contains the previous tab control extended styles.
 */
#define TCM_SETEXTENDEDSTYLE    (TCM_FIRST + 52)  // optional wParam == mask
/**
 * This macro sets the extended styles that the tab control will use.
 *
 * @param hwndTab Handle to the tab control.
 * @param dwExStyle Contains the new tab control extended styles. It is a combination of tab control
 *   extended styles.
 *
 * @return DWORD that contains the previous tab control extended styles.
 */
#define TabCtrl_SetExtendedStyle(hwnd, dw)\
        (DWORD)SNDMSG((hwnd), TCM_SETEXTENDEDSTYLE, 0, dw)

/**
 * This message retrieves the extended styles that are currently in use for the tab control.
 *
 * @return Returns a DWORD value that represents the extended styles currently in use for the tab
 *   control. This value is a combination of tab control extended styles.
 */
#define TCM_GETEXTENDEDSTYLE    (TCM_FIRST + 53)
/**
 * This macro retrieves the extended styles that are currently in use for the tab control. You can
 * use this macro or send the TCM_GETEXTENDEDSTYLE message explicitly.
 *
 * @param hwndTab Handle to the tab control.
 *
 * @return Returns a DWORD that represents the extended styles currently in use for the tab control.
 *   This value is a combination of tab control extended styles.
 */
#define TabCtrl_GetExtendedStyle(hwnd)\
        (DWORD)SNDMSG((hwnd), TCM_GETEXTENDEDSTYLE, 0, 0)

#endif      // _WIN32_IE >= 0x0400

/**
 * This notification message notifies a tab control's parent window that a key has been pressed. It
 * is sent in the form of a WM_NOTIFY message.
 *
 * @param pnm Pointer to an NMTCKEYDOWN structure.
 *
 * @return None.
 */
#define TCN_KEYDOWN             (TCN_FIRST - 0)

#if (_WIN32_IE >= 0x0300)
#define TC_KEYDOWN              NMTCKEYDOWN
#else
#define tagTCKEYDOWN            _TC_KEYDOWN
#define  NMTCKEYDOWN             TC_KEYDOWN
#endif

/**
 * This structure contains information about a key press in a tab control. It is used with the
 * TCN_KEYDOWN notification message.
 */
typedef struct tagTCKEYDOWN
{
    /**
     * NMHDR structure that contains information about the notification message.
     */
    NMHDR hdr;
    /**
     * Virtual key code.
     */
    WORD wVKey;
    /**
     * Value that is identical to the lParam parameter of the WM_KEYDOWN message.
     */
    UINT flags;
} NMTCKEYDOWN;

/**
 * This notification message notifies a tab control's parent window that the currently selected tab
 * has changed. It is sent in the form of a WM_NOTIFY message.
 *
 * @param lpnmhdr Long pointer to an NMHDR structure. The hwndFrom member is the handle to the tab
 *   control. The idFrom member is the child window identifier of the tab control. The code member is
 *   TCN_SELCHANGE.
 *
 * @return None.
 *
 * To determine the currently selected tab, use the TabCtrl_GetCurSel macro.
 */
#define TCN_SELCHANGE           (TCN_FIRST - 1)
/**
 * This notification message notifies a tab control's parent window that the currently selected tab
 * is about to change. It is sent in the form of a WM_NOTIFY message.
 *
 * @param lpnmhdr Long pointer to an NMHDR structure. The hwndFrom member is the handle to the tab
 *   control. The idFrom member is the child window identifier of the tab control. The code member is
 *   TCN_SELCHANGING.
 *
 * @return TRUE prevents the selection from changing. FALSE allows the selection to change.
 *
 * To determine the currently selected tab, use the TabCtrl_GetCurSel macro.
 */
#define TCN_SELCHANGING         (TCN_FIRST - 2)

#endif      // NOTABCONTROL

#if (_WIN32_IE >= 0x0300)
//====== MONTHCAL CONTROL ======================================================

#ifndef NOMONTHCAL
#ifdef _WIN32

#define MONTHCAL_CLASSW          L"SysMonthCal32"
#define MONTHCAL_CLASSA          "SysMonthCal32"

#ifdef UNICODE
#define MONTHCAL_CLASS           MONTHCAL_CLASSW
#else
#define MONTHCAL_CLASS           MONTHCAL_CLASSA
#endif

// bit-packed array of "bold" info for a month
// if a bit is on, that day is drawn bold
typedef DWORD MONTHDAYSTATE, FAR * LPMONTHDAYSTATE;


#define MCM_FIRST           0x1000

// BOOL MonthCal_GetCurSel(HWND hmc, LPSYSTEMTIME pst)
//   returns FALSE if MCS_MULTISELECT
//   returns TRUE and sets *pst to the currently selected date otherwise
/**
 * This message retrieves the system time portrayed by the currently selected date.
 *
 * @param lpSysTime Long pointer to a SYSTEMTIME structure that receives the system time
 *   information. The time members of this structure are not modified.
 *
 * @return Nonzero indicates success. Zero indicates otherwise. This message always fails when
 *   applied to month calendar controls set to the MCS_MULTISELECT style.
 */
#define MCM_GETCURSEL       (MCM_FIRST + 1)
/**
 * This macro retrieves the system time portrayed by the currently selected date.
 *
 * @param hwndMC Handle to a month calendar control.
 * @param lpSysTime Long pointer to a SYSTEMTIME structure that will receive the system time
 *   information.
 *
 * @return Nonzero indicates success. Zero indicates otherwise. This macro will always fail when
 *   applied to month calendar controls that are set to the MCS_MULTISELECT style.
 */
#define MonthCal_GetCurSel(hmc, pst)    (BOOL)SNDMSG(hmc, MCM_GETCURSEL, 0, (LPARAM)(pst))

// BOOL MonthCal_SetCurSel(HWND hmc, LPSYSTEMTIME pst)
//   returns FALSE if MCS_MULTISELECT
//   returns TURE and sets the currently selected date to *pst otherwise
/**
 * This message sets the currently selected date for a month calendar control. If the specified date
 * is not in view, the control updates the display to bring it into view.
 *
 * @param lpSysTime Long pointer to a SYSTEMTIME structure that contains the date to be set as the
 *   current selection. The time members of this structure are ignored.
 *
 * @return Nonzero indicates success. Zero indicates otherwise. This message fails if applied to a
 *   month calendar control that uses the MCS_MULTISELECT style.
 */
#define MCM_SETCURSEL       (MCM_FIRST + 2)
/**
 * This macro sets the currently selected date for a month calendar control. If the specified date
 * is not in view, the control updates the display to bring it into view.
 *
 * @param hwndMC Handle to a month calendar control.
 * @param lpSysTime Long pointer to a SYSTEMTIME structure that contains the date to be set as the
 *   current selection. The time members of this structure are ignored.
 *
 * @return Nonzero indicates success. Zero indicates otherwise. This macro will fail if applied to a
 *   month calendar control that uses the MCS_MULTISELECT style.
 */
#define MonthCal_SetCurSel(hmc, pst)    (BOOL)SNDMSG(hmc, MCM_SETCURSEL, 0, (LPARAM)(pst))

// DWORD MonthCal_GetMaxSelCount(HWND hmc)
//   returns the maximum number of selectable days allowed
/**
 * This message retrieves the maximum selectable date range that is set for a month calendar
 * control.
 *
 * @return Returns an INT value that represents the total number of days that can be selected for
 *   the control.
 *
 * You can change the selectable date range using the MCM_SETMAXSELCOUNT message.
 */
#define MCM_GETMAXSELCOUNT  (MCM_FIRST + 3)
/**
 * This macro retrieves the maximum selectable date range that is set for a month calendar control.
 * You can use this macro or send the MCM_GETMAXSELCOUNT message explicitly.
 *
 * @param hwndMC Handle to a month calendar control.
 *
 * @return You can change the selectable date range using the MCM_SETMAXSELCOUNT message. Returns an
 *   INT value that represents the total number of days that can be selected for the control.
 */
#define MonthCal_GetMaxSelCount(hmc)    (DWORD)SNDMSG(hmc, MCM_GETMAXSELCOUNT, 0, 0L)

// BOOL MonthCal_SetMaxSelCount(HWND hmc, UINT n)
//   sets the max number days that can be selected iff MCS_MULTISELECT
/**
 * This message sets the maximum number of days that can be selected in a month calendar control.
 *
 * @param iMax INT value that is set to represent the maximum number of selectable days.
 *
 * @return Returns nonzero if successful, and returns zero otherwise. This message fails if applied
 *   to a month calendar control that does not use the MCS_MULTISELECT style.
 */
#define MCM_SETMAXSELCOUNT  (MCM_FIRST + 4)
/**
 * This macro sets the maximum number of days that can be selected in a month calendar control.
 *
 * @param hwndMC Handle to a month calendar control.
 * @param iMax INT value that will be set to represent the maximum number of selectable days.
 *
 * @return Nonzero indicates success. Zero indicates otherwise. This macro will fail if applied to a
 *   month calendar control that does not use the MCS_MULTISELECT style.
 */
#define MonthCal_SetMaxSelCount(hmc, n) (BOOL)SNDMSG(hmc, MCM_SETMAXSELCOUNT, (WPARAM)(n), 0L)

// BOOL MonthCal_GetSelRange(HWND hmc, LPSYSTEMTIME rgst)
//   sets rgst[0] to the first day of the selection range
//   sets rgst[1] to the last day of the selection range
/**
 * This message retrieves date information that represents the upper and lower limits of the date
 * range currently selected by the user
 *
 * @param lprgSysTimeArray Long pointer to a two-element array of SYSTEMTIME structures that
 *   receives the lower and upper limits of the user's selection. The lower and upper limits are
 *   placed in lprgSysTimeArray[0] and lprgSysTimeArray[1], respectively. The time members of these
 *   structures are not modified.
 *
 * @return Nonzero indicates success. Zero indicates otherwise. MCM_GETSELRANGE fails if applied to
 *   a month calendar control that does not use the MCS_MULTISELECT style.
 */
#define MCM_GETSELRANGE     (MCM_FIRST + 5)
/**
 * This macro retrieves date information that represents the upper and lower limits of the date
 * range currently selected by the user.
 *
 * @param hwndMC Handle to a month calendar control.
 * @param lprgSysTimeArray Long pointer to a two-element array of SYSTEMTIME structures that will
 *   receive the lower and upper limits of the user's selection. The lower and upper limits are placed
 *   in lprgSysTimeArray[0] and lprgSysTimeArray[1], respectively. The time members of these
 *   structures will not be modified.
 *
 * @return Nonzero indicates success. Zero indicates otherwise. MonthCal_GetSelRange will fail if
 *   applied to a month calendar control that does not use the MCS_MULTISELECT style.
 */
#define MonthCal_GetSelRange(hmc, rgst) SNDMSG(hmc, MCM_GETSELRANGE, 0, (LPARAM)(rgst))

// BOOL MonthCal_SetSelRange(HWND hmc, LPSYSTEMTIME rgst)
//   selects the range of days from rgst[0] to rgst[1]
/**
 * This message sets the selection for a month calendar control to a specified date range.
 *
 * @param lprgSysTimeArray Long pointer to a two-element array of SYSTEMTIME structures that
 *   contains date information representing the selection limits. The first selected date must be
 *   specified in lpSysTimeArray[0], and the last selected date must be specified in
 *   lpSysTimeArray[1]. The time members of these structures are ignored.
 *
 * @return Nonzero indicates success. Zero indicates otherwise. This message fails if applied to a
 *   month calendar control that does not use the MCS_MULTISELECT style.
 */
#define MCM_SETSELRANGE     (MCM_FIRST + 6)
/**
 * This macro sets the selection for a month calendar control to a specified date range.
 *
 * @param hwndMC Handle to a month calendar control.
 * @param lprgSysTimeArray Long pointer to a two-element array of SYSTEMTIME structures that
 *   contains date information representing the selection limits. The first selected date must be
 *   specified in lpSysTimeArray[0], and the last selected date must be specified in
 *   lpSysTimeArray[1]. The time members of these structures are ignored.
 *
 * @return Nonzero indicates success. Zero indicates otherwise. This macro will fail if applied to a
 *   month calendar control that does not use the MCS_MULTISELECT style.
 */
#define MonthCal_SetSelRange(hmc, rgst) SNDMSG(hmc, MCM_SETSELRANGE, 0, (LPARAM)(rgst))

// DWORD MonthCal_GetMonthRange(HWND hmc, DWORD gmr, LPSYSTEMTIME rgst)
//   if rgst specified, sets rgst[0] to the starting date and
//      and rgst[1] to the ending date of the the selectable (non-grayed)
//      days if GMR_VISIBLE or all the displayed days (including grayed)
//      if GMR_DAYSTATE.
//   returns the number of months spanned by the above range.
/**
 * This message, using SYSTEMTIME structures, retrieves date information that represents the high
 * and low limits of a month calendar control's display.
 *
 * @param dwFlag Specifies the scope of the range limits to be retrieved. It is one of the following
 *   values: Value Description GMR_DAYSTATE Includes preceding and trailing months of visible range
 *   that are only partially displayed. GMR_VISIBLE Includes only those months that are entirely
 *   displayed.
 * @param lprgSysTimeArray Long pointer to a two-element array of SYSTEMTIME structures that
 *   receives the lower and upper limits of the scope specified by dwFlag. The lower and upper limits
 *   are placed in lprgSysTimeArray[0] and lprgSysTimeArray[1], respectively. The time members of
 *   these structures are not modified.
 *
 * @return Returns an INT that represents the range, in months, spanned by the two limits returned
 *   at lprgSysTimeArray.
 */
#define MCM_GETMONTHRANGE   (MCM_FIRST + 7)
/**
 * This macro retrieves date information (using SYSTEMTIME structures) that represents the high and
 * low limits of a month calendar control's display.
 *
 * @param hwndMC Handle to a month calendar control.
 * @param dwFlag Specifies the scope of the range limits to be retrieved. It is one of the following
 *   values: Value Description GMR_DAYSTATE Include preceding and trailing months of visible range
 *   that are only partially displayed. GMR_VISIBLE Include only those months that are entirely
 *   displayed.
 * @param lprgSysTimeArray Long pointer to a two-element array of SYSTEMTIME structures that will
 *   receive the lower and upper limits of the scope specified by dwFlag. The lower and upper limits
 *   are placed in lprgSysTimeArray[0] and lprgSysTimeArray[1], respectively. The time members of
 *   these structure are not modified.
 *
 * @return Returns an INT that represents the range, in months, spanned by the two limits returned
 *   at lprgSysTimeArray.
 */
#define MonthCal_GetMonthRange(hmc, gmr, rgst)  (DWORD)SNDMSG(hmc, MCM_GETMONTHRANGE, (WPARAM)(gmr), (LPARAM)(rgst))

// BOOL MonthCal_SetDayState(HWND hmc, int cbds, DAYSTATE *rgds)
//   cbds is the count of DAYSTATE items in rgds and it must be equal
//   to the value returned from MonthCal_GetMonthRange(hmc, GMR_DAYSTATE, NULL)
//   This sets the DAYSTATE bits for each month (grayed and non-grayed
//   days) displayed in the calendar. The first bit in a month's DAYSTATE
//   corresponts to bolding day 1, the second bit affects day 2, etc.
/**
 * This message sets the display for days in all months that are currently visible within a month
 * calendar control.
 *
 * @param iMonths Indicates how many elements are in the array that lpDayStateArray points to.
 * @param lpDayStateArray Long pointer to an array of MONTHDAYSTATE values that define how the month
 *   calendar control will draw each day in its display. The array at lpDayStateArray must contain as
 *   many elements as the value returned by the following macro.
 *
 * @return Sets the month calendar's display and returns nonzero if successful. Otherwise it returns
 *   zero.
 *
 * Keep in mind that the array at lpDayStateArray must contain MONTHDAYSTATE values that correspond
 * with all months currently in the control's display, in chronological order. This includes the two
 * months only partially displayed before the first month and after the last month. For more
 * information about preparing your array, see "Preparing the MONTHDAYSTATE Array."
 */
#define MCM_SETDAYSTATE     (MCM_FIRST + 8)
/**
 * This macro sets the display for days in all months that are currently visible within a month
 * calendar control.
 *
 * @param hwndMC Handle to a month calendar control.
 * @param iMonths INT value that indicates how many elements are in the array that lpDayStateArray
 *   points to.
 * @param lpDayStateArray Long pointer to an array of MONTHDAYSTATE values that define how the month
 *   calendar control will draw each day in its display.
 *
 * @return Nonzero if successful. If the macro fails, it returns zero.
 *
 * The array at lpDayStateArray must contain as many elements as the value returned by the following
 * macro:
 *
 * MonthCal_GetMonthRange(hwndMC, GMR_DAYSTATE, NULL);
 *
 * The preceding macro returns the total number of months that are in complete or partial view
 * within the month calendar's display.
 *
 * Keep in mind that the array at lpDayStateArray must contain MONTHDAYSTATE values that correspond
 * with all months currently in the control's display, in chronological order. This includes the two
 * months only partially displayed before the first month and after the last month.
 */
#define MonthCal_SetDayState(hmc, cbds, rgds)   SNDMSG(hmc, MCM_SETDAYSTATE, (WPARAM)(cbds), (LPARAM)(rgds))

// BOOL MonthCal_GetMinReqRect(HWND hmc, LPRECT prc)
//   sets *prc the minimal size needed to display one month
//   To display two months, undo the AdjustWindowRect calculation already done to
//   this rect, double the width, and redo the AdjustWindowRect calculation --
//   the monthcal control will display two calendars in this window (if you also
//   double the vertical size, you will get 4 calendars)
//   NOTE: if you want to gurantee that the "Today" string is not clipped,
//   get the MCM_GETMAXTODAYWIDTH and use the max of that width and this width
/**
 * This message retrieves the minimum size required to display a full month in a month calendar
 * control. Size information is presented in the form of a RECT structure.
 *
 * @param lpRectInfo Long pointer to a RECT structure that receives bounding rectangle information.
 *
 * @return Returns nonzero and lpRectInfo receives the applicable bounding information if
 *   successful. The message returns zero upon failure.
 *
 * The top and left members of lpRectInfo will always be zero. The right and bottom members
 * represent the minimum cx and cy required for the control.
 *
 * The minimum required window size for a month calendar control depends on the currently selected
 * font.
 */
#define MCM_GETMINREQRECT   (MCM_FIRST + 9)
/**
 * This macro retrieves the minimum size required to display a full month in a month calendar
 * control. Size information is presented in the form of a RECT structure.
 *
 * @param hwndMC Handle to a month calendar control.
 * @param lpRectInfo Long pointer to a RECT structure that will receive bounding rectangle
 *   information.
 *
 * @return Returns nonzero and lpRectInfo receives the applicable bounding information if
 *   successful. Otherwise, the macro returns zero.
 *
 * The top and left members of the RECT structure specified by lpRectInfo will always be zero. The
 * right and i members represent the minimum cx and cy required for the control.
 *
 * The minimum required window size for a month calendar control depends on the currently selected
 * font.
 */
#define MonthCal_GetMinReqRect(hmc, prc)        SNDMSG(hmc, MCM_GETMINREQRECT, 0, (LPARAM)(prc))

// set colors to draw control with -- see MCSC_ bits below
/**
 * This message sets the color for a specified portion of a month calendar control.
 *
 * @param iColor Specifies which month calendar color to set. It is one of the following values:
 *   Value Description MCSC_BACKGROUND Retrieves the background color displayed between months.
 *   MCSC_MONTHBK Retrieves the background color displayed within the month. MCSC_TEXT Retrieves the
 *   color used to display text within a month. MCSC_TITLEBK Retrieves the background color displayed
 *   in the calendar's title. MCSC_TITLETEXT Retrieves the color used to display text within the
 *   calendar's title. MCSC_TRAILINGTEXT Retrieves the color used to display header and trailing-day
 *   text. Header and trailing days are the days from the previous and following months that appear on
 *   the current calendar.
 * @param clr COLORREF value that represents the color that is set for the specified area of the
 *   month calendar.
 *
 * @return Returns a COLORREF value that represents the previous color setting for the specified
 *   portion of the month calendar control if successful. Otherwise, this message returns -1.
 */
#define MCM_SETCOLOR            (MCM_FIRST + 10)
/**
 * This macro sets the color for a specified portion of a month calendar control.
 *
 * @param hwndMC Handle to a month calendar control.
 * @param iColor INT value that specifies which month calendar color to set. It is one of the
 *   following values: Value Description MCSC_BACKGROUND Retrieves the background color displayed
 *   between months. MCSC_MONTHBK Retrieves the background color displayed within the month. MCSC_TEXT
 *   Retrieves the color used to display text within a month. MCSC_TITLEBK Retrieves the background
 *   color displayed in the calendar's title. MCSC_TITLETEXT Retrieves the color used to display text
 *   within the calendar's title. MCSC_TRAILINGTEXT Retrieves the color used to display header and
 *   trailing-day text. Header and trailing days are the days from the previous and following months
 *   that appear on the current calendar.
 * @param clr COLORREF value that represents the color that will be set for the specified area of
 *   the month calendar.
 *
 * @return Returns a COLORREF value that represents the previous color setting for the specified
 *   portion of the month calendar control if successful. Otherwise, this macro returns -1.
 */
#define MonthCal_SetColor(hmc, iColor, clr) SNDMSG(hmc, MCM_SETCOLOR, iColor, clr)

/**
 * This message retrieves the color for a specified portion of a month calendar control.
 *
 * @param iColor Specifies which month calendar color to retrieve. It is one of the following
 *   values: Value Description MCSC_BACKGROUND Retrieves the background color displayed between
 *   months. MCSC_MONTHBK Retrieves the background color displayed within the month. MCSC_TEXT
 *   Retrieves the color used to display text within a month. MCSC_TITLEBK Retrieves the background
 *   color displayed in the calendar's title. MCSC_TITLETEXT Retrieves the color used to display text
 *   within the calendar's title. MCSC_TRAILINGTEXT Retrieves the color used to display header and
 *   trailing-day text. Header and trailing days are the days from the previous and following months
 *   that appear on the current calendar.
 *
 * @return Returns a COLORREF value that represents the color setting for the specified portion of
 *   the month calendar control if successful. Otherwise, this message returns -1.
 */
#define MCM_GETCOLOR            (MCM_FIRST + 11)
/**
 * This macro retrieves the color for a specified portion of a month calendar control.
 *
 * @param hwndMC Handle to a month calendar control.
 * @param iColor INT value that specifies which month calendar color to retrieve. It is one of the
 *   following values: Value Description MCSC_BACKGROUND Retrieves the background color displayed
 *   between months. MCSC_MONTHBK Retrieves the background color displayed within the month. MCSC_TEXT
 *   Retrieves the color used to display text within a month. MCSC_TITLEBK Retrieves the background
 *   color displayed in the calendar's title. MCSC_TITLETEXT Retrieves the color used to display text
 *   within the calendar's title. MCSC_TRAILINGTEXT Retrieves the color used to display header and
 *   trailing-day text. Header and trailing days are the days from the previous and following months
 *   that appear on the current calendar.
 *
 * @return Upon success, this macro returns a COLORREF value that represents the color setting for
 *   the specified portion of the month calendar control. The macro returns -1 upon failure.
 */
#define MonthCal_GetColor(hmc, iColor) SNDMSG(hmc, MCM_SETCOLOR, iColor, 0)

#define MCSC_BACKGROUND   0   // the background color (between months)
#define MCSC_TEXT         1   // the dates
#define MCSC_TITLEBK      2   // background of the title
#define MCSC_TITLETEXT    3
#define MCSC_MONTHBK      4   // background within the month cal
#define MCSC_TRAILINGTEXT 5   // the text color of header & trailing days

// set what day is "today"   send NULL to revert back to real date
/**
 * This message sets the "today" selection for a month calendar control.
 *
 * @param lpSysTime Long pointer to a SYSTEMTIME structure that contains the date to be set as the
 *   "today" selection for the control. If this parameter is set to NULL, the control returns to the
 *   default setting. The time members of this structure are ignored. If the "today" selection is set
 *   to any date other than the default, the following conditions apply.
 *
 * @return The return value for this message is not used.
 *
 * The control will not automatically update the "today" selection when the time passes midnight for
 * the current day.
 *
 * The control will not automatically update its display based on locale changes.
 */
#define MCM_SETTODAY    (MCM_FIRST + 12)
/**
 * This macro sets the "today" selection for a month calendar control, because the control does not
 * automatically update the "today" selection when the time passes midnight for the current day.
 *
 * @param hwndMC Handle to a month calendar control.
 * @param lpSysTime Long pointer to a SYSTEMTIME structure that contains the date to be set as the
 *   "today" selection for the control. If this parameter is set to NULL, the control returns to the
 *   default setting. The time members of this structure are ignored. If the "today" selection is set
 *   to any date other than the default, the following conditions apply.
 *
 * The control will not automatically update its display based on locale changes.
 */
#define MonthCal_SetToday(hmc, pst)             SNDMSG(hmc, MCM_SETTODAY, 0, (LPARAM)pst)

// get what day is "today"
// returns BOOL for success/failure
/**
 * This message retrieves the date information for the date specified as "today" for a month
 * calendar control.
 *
 * @param lpToday Long pointer to a SYSTEMTIME structure that receives the date information. The
 *   time members of this structure are not modified.
 *
 * @return Nonzero indicates success. Zero indicates otherwise.
 */
#define MCM_GETTODAY    (MCM_FIRST + 13)
/**
 * This macro retrieves the date information for the date specified as "today" for a month calendar
 * control.
 *
 * @param hwndMC Handle to a month calendar control.
 * @param lpToday Long pointer to a SYSTEMTIME structure that will receive the date information.
 *
 * @return Nonzero indicates success. Zero indicates otherwise.
 */
#define MonthCal_GetToday(hmc, pst)             (BOOL)SNDMSG(hmc, MCM_GETTODAY, 0, (LPARAM)pst)

// determine what pinfo->pt is over
/**
 * This message determines which portion of a month calendar control is at a specified point on the
 * screen.
 *
 * @param pMCHitTest Pointer to an MCHITTESTINFO structure. Upon sending the message, the cbSize
 *   member must equal sizeof(MCHITTESTINFO), and pt must be set to the point you want to hit test.
 *
 * @return Sets values in members of the MCHITTESTINFO structure at pMCHitTest and returns a DWORD
 *   value that is one of the following values: - MCHT_CALENDAR: The specified point was within the
 *   calendar. - MCHT_CALENDARBK: The specified point was in the calendar's background. -
 *   MCHT_CALENDARDATE: The specified point was on a particular date within the calendar. The
 *   SYSTEMTIME structure at lpMCHitTest->st is set to the date at the specified point. -
 *   MCHT_CALENDARDATENEXT: The specified point was over a date from the next month (partially
 *   displayed at the end of the currently displayed month). If the user clicks here, the month
 *   calendar will scroll its display to the next month or set of months. - MCHT_CALENDARDATEPREV: The
 *   specified point was over a date from the previous month (partially displayed at the end of the
 *   currently displayed month). If the user clicks here, the month calendar will scroll its display
 *   to the previous month or set of months. - MCHT_CALENDARDAY: The specified point was over a day
 *   abbreviation ("Fri"). The SYSTEMTIME structure at lpMCHitTest->st is set to the corresponding
 *   date in the top row. - MCHT_CALENDARWEEKNUM: The specified point was over a week number (The
 *   MCS_WEEKNUMBERS style only.) The SYSTEMTIME structure at lpMCHitTest->st is set to the
 *   corresponding date in the leftmost column. - MCHT_NEXT: The specified point was over the button
 *   at the top right corner of the control. If the user clicks here, the month calendar will scroll
 *   its display to the next month or set of months. - MCHT_NOWHERE: The specified point was either
 *   not on the month calendar control, or in an inactive portion of the control. - MCHT_PREV: The
 *   specified point was over the button at the top left corner of the control. If the user clicks
 *   here, the month calendar will scroll its display to the previous month or set of months. -
 *   MCHT_TITLE: The specified point was over a month's title. - MCHT_TITLEBK: The specified point was
 *   over the background of a month's title. - MCHT_TITLEBTNNEXT: The specified point was over the
 *   button at the top right corner of the control. If the user clicks here, the month calendar will
 *   scroll its display to the next month or set of months. - MCHT_TITLEBTNPREV: The specified point
 *   was over the button at the top left corner of the control. If the user clicks here, the month
 *   calendar will scroll its display to the previous month or set of months. - MCHT_TITLEMONTH: The
 *   specified point was in the a month's title bar, over a month name. - MCHT_TITLEYEAR: The
 *   specified point was in a month's title bar, over the year value. - MCHT_TODAYLINK: The specified
 *   point was on the "today" link at the bottom of the month calendar control.
 *
 * The uHit member of the MCHITTESTINFO structure at pMCHitTest will equal the return value.
 */
#define MCM_HITTEST          (MCM_FIRST + 14)
/**
 * This macro determines which portion of a month calendar control is at a specified point on the
 * screen.
 *
 * @param hwndMC Handle to a month calendar control.
 * @param pMCHitTest Pointer to an MCHITTESTINFO structure. Upon sending the macro, the cbSize
 *   member must equal sizeof(MCHITTESTINFO), and pt must be set to the point you want to hit test.
 *
 * @return Sets values in members of the MCHITTESTINFO structure at pMCHitTest and returns one of
 *   the following DWORD values: - MCHT_CALENDARBK: The specified point was in the calendar's
 *   background. - MCHT_CALENDARDATE: The specified point was on a particular date within the
 *   calendar. The SYSTEMTIME structure at lpMCHitTest->st is set to the date at the specified point.
 *   - MCHT_CALENDARDATENEXT: The specified point was over a date from the next month (partially
 *   displayed at the end of the currently displayed month). If the user clicks here, the month
 *   calendar will scroll its display to the next month or set of months. - MCHT_CALENDARDATEPREV: The
 *   specified point was over a date from the previous month (partially displayed at the end of the
 *   currently displayed month). If the user clicks here, the month calendar will scroll its display
 *   to the previous month or set of months. - MCHT_CALENDARDAY: The specified point was over a day
 *   abbreviation ("Fri"). The SYSTEMTIME structure at lpMCHitTest->st is set to the corresponding
 *   date in the top row. - MCHT_CALENDARWEEKNUM: The specified point was over a week number (the
 *   MCS_WEEKNUMBERS style only). The SYSTEMTIME structure at lpMCHitTest->st is set to the
 *   corresponding date in the leftmost column. - MCHT_NOWHERE: The specified point was either not on
 *   the month calendar control, or in an inactive portion of the control. - MCHT_TITLEBK: The
 *   specified point was over the background of a month's title. - MCHT_TITLEBTNNEXT: The specified
 *   point was over the button at the top right corner of the control. If the user clicks here, the
 *   month calendar will scroll its display to the next month or set of months. - MCHT_TITLEBTNPREV:
 *   The specified point was over the button at the top left corner of the control. If the user clicks
 *   here, the month calendar will scroll its display to the previous month or set of months. -
 *   MCHT_TITLEMONTH: The specified point was in a month's title bar, over a month name. -
 *   MCHT_TITLEYEAR: The specified point was in a month's title bar, over the year value. The uHit
 *   member of the MCHITTESTINFO structure at pMCHitTest will equal the return value.
 */
#define MonthCal_HitTest(hmc, pinfo) \
        SNDMSG(hmc, MCM_HITTEST, 0, (LPARAM)(PMCHITTESTINFO)pinfo)

/**
 * This structure carries information specific to hit-testing points for a month calendar control.
 * This structure is used with the MCM_HITTEST message and the corresponding MonthCal_HitTest macro.
 */
typedef struct {
        /**
         * Size of this structure, in bytes.
         */
        UINT cbSize;
        /**
         * POINT structure that contains information about the point to be hit-tested.
         */
        POINT pt;

        /**
         * Output member that receives a bit flag representing the result of the hit-test operation. It is
         * one of the following values: Value Description MCHT_CALENDARBK The specified point was in the
         * calendar's background. MCHT_CALENDARDATE The specified point was on a particular date within the
         * calendar. The SYSTEMTIME structure at lpMCHitTest->st is set to the date at the given point.
         * MCHT_CALENDARDATENEXT The specified point was over a date from the next month (partially
         * displayed at the end of the currently displayed month). If the user clicks here, the month
         * calendar will scroll its display to the next month or set of months. MCHT_CALENDARDATEPREV The
         * specified point was over a date from the previous month (partially displayed at the end of the
         * currently displayed month). If the user clicks here, the month calendar will scroll its display
         * to the previous month or set of months. MCHT_CALENDARDAY The specified point was over a day
         * abbreviation ("Fri"). The SYSTEMTIME structure at lpMCHitTest->st is set to the corresponding
         * date in the top row. MCHT_CALENDARWEEKNUM The specified point was over a week number
         * (MCS_WEEKNUMBERS only). The SYSTEMTIME structure at lpMCHitTest->st is set to the corresponding
         * date in the leftmost column. MCHT_NOWHERE The specified point was either not on the month
         * calendar control, or in an inactive portion of the control. MCHT_TITLEBK The specified point was
         * over the background of a month's title. MCHT_TITLEBTNNEXT The specified point was over the button
         * at the top right corner of the control. If the user clicks here, the month calendar will scroll
         * its display to the next month or set of months. MCHT_TITLEBTNPREV The specified point was over
         * the button at the top left corner of the control. If the user clicks here, the month calendar
         * will scroll its display to the previous month or set of months. MCHT_TITLEMONTH The specified
         * point was in a month's title bar, over a month name. MCHT_TITLEYEAR The specified point was in a
         * month's title bar, over the year value.
         */
        UINT uHit;   // out param
        /**
         * SYSTEMTIME structure that receives date and time information specific to the location that was
         * hit-tested.
         */
        SYSTEMTIME st;
} MCHITTESTINFO, *PMCHITTESTINFO;

#define MCHT_TITLE                      0x00010000
#define MCHT_CALENDAR                   0x00020000
#define MCHT_TODAYLINK                  0x00030000

#define MCHT_NEXT                       0x01000000   // these indicate that hitting
#define MCHT_PREV                       0x02000000  // here will go to the next/prev month

#define MCHT_NOWHERE                    0x00000000

#define MCHT_TITLEBK                    (MCHT_TITLE)
#define MCHT_TITLEMONTH                 (MCHT_TITLE | 0x0001)
#define MCHT_TITLEYEAR                  (MCHT_TITLE | 0x0002)
#define MCHT_TITLEBTNNEXT               (MCHT_TITLE | MCHT_NEXT | 0x0003)
#define MCHT_TITLEBTNPREV               (MCHT_TITLE | MCHT_PREV | 0x0003)

#define MCHT_CALENDARBK                 (MCHT_CALENDAR)
#define MCHT_CALENDARDATE               (MCHT_CALENDAR | 0x0001)
#define MCHT_CALENDARDATENEXT           (MCHT_CALENDARDATE | MCHT_NEXT)
#define MCHT_CALENDARDATEPREV           (MCHT_CALENDARDATE | MCHT_PREV)
#define MCHT_CALENDARDAY                (MCHT_CALENDAR | 0x0002)
#define MCHT_CALENDARWEEKNUM            (MCHT_CALENDAR | 0x0003)

// set first day of week to iDay:
// 0 for Monday, 1 for Tuesday, ..., 6 for Sunday
// -1 for means use locale info
/**
 * This message sets the first day of the week for a month calendar control.
 *
 * @param iDay INT value representing which day is to be set as the first day of the week. It is one
 *   of the following values: Value Day of the week 0 Sunday 1 Monday 2 Tuesday 3 Wednesday 4 Thursday
 *   5 Friday 6 Saturday
 *
 * @return Returns a DWORD value that contains two values. The high-order word is a BOOL that is
 *   nonzero if the previous first day of the week did not equal LOCALE_IFIRSTDAYOFWEEK, or zero
 *   otherwise. The low-order word is an INT value that represents the previous day of the week number
 *   (see list under iDay).
 *
 * If the first day of the week is set to anything other than the default (LOCALE_IFIRSTDAYOFWEEK),
 * the control will not automatically update first-day-of-the-week changes based on locale changes.
 */
#define MCM_SETFIRSTDAYOFWEEK (MCM_FIRST + 15)
/**
 * This macro sets the first day of the week for a month calendar control.
 *
 * @param hwndMC Handle to a month calendar control.
 * @param iDay INT value that specified which day is to be set as the first day of the week. It is
 *   one of the following values: Value Day 0 Monday 1 Tuesday 2 Wednesday 3 Thursday 4 Friday 5
 *   Saturday 6 Sunday
 *
 * @return Returns a DWORD value that contains two values. The high-order word is a BOOL that is
 *   nonzero if the previous first day of the week did not equal LOCALE_IFIRSTDAYOFWEEK, or zero
 *   otherwise. The low-order word is an INT value that represents the previous day-of-the-week number
 *   (see list under iDay).
 *
 * If the first day of the week is set to anything other than the default (LOCALE_IFIRSTDAYOFWEEK),
 * the control will not automatically update first-day-of-the-week changes based on locale changes.
 */
#define MonthCal_SetFirstDayOfWeek(hmc, iDay) \
        SNDMSG(hmc, MCM_SETFIRSTDAYOFWEEK, 0, iDay)

// DWORD result...  low word has the day.  high word is bool if this is app set
// or not (FALSE == using locale info)
/**
 * This message retrieves the first day of the week for a month calendar control.
 *
 * @return Returns a DWORD value that contains two values. The high-order word is a BOOL that is
 *   nonzero if the first day of the week is set to something other than LOCALE_IFIRSTDAYOFWEEK, or
 *   zero otherwise. The low-order word is an INT value that represents the first day of the week, as
 *   shown in the following table. Value Day of the week 0 Sunday 1 Monday 2 Tuesday 3 Wednesday 4
 *   Thursday 5 Friday 6 Saturday
 */
#define MCM_GETFIRSTDAYOFWEEK (MCM_FIRST + 16)
/**
 * This macro retrieves the first day of the week for a month calendar control.
 *
 * @param hwndMC Handle to a month calendar control.
 *
 * @return Returns a DWORD value that contains two values. The high-order word is a BOOL that is
 *   nonzero if the first day of the week is set to something other than LOCALE_IFIRSTDAYOFWEEK, or
 *   zero otherwise. The low-order word is an INT value that represents the first day of the week. The
 *   low-order word will be one of the values shown in the following table. Value Day 0 Monday 1
 *   Tuesday 2 Wednesday 3 Thursday 4 Friday 5 Saturday 6 Sunday
 */
#define MonthCal_GetFirstDayOfWeek(hmc) \
        (DWORD)SNDMSG(hmc, MCM_GETFIRSTDAYOFWEEK, 0, 0)

// DWORD MonthCal_GetRange(HWND hmc, LPSYSTEMTIME rgst)
//   modifies rgst[0] to be the minimum ALLOWABLE systemtime (or 0 if no minimum)
//   modifies rgst[1] to be the maximum ALLOWABLE systemtime (or 0 if no maximum)
//   returns GDTR_MIN|GDTR_MAX if there is a minimum|maximum limit
/**
 * This message retrieves the minimum and maximum allowable dates set for a month calendar control.
 *
 * @param lprgSysTimeArray Long pointer to a two-element array of SYSTEMTIME structures that
 *   receives the date limit information. The minimum limit is set in lprgSysTimeArray[0], and
 *   lprgSysTimeArray[1] receives the maximum limit. If either element is set to all zeros, then no
 *   corresponding limit is set for the month calendar control. The time members of these structures
 *   are not modified.
 *
 * @return Returns a DWORD that can be zero (no limits are set) or a combination of the following
 *   values that specify limit information: - GDTR_MAX: A maximum limit is set for the control;
 *   lprgSysTimeArray[0] is valid and contains the applicable date information. - GDTR_MIN: A minimum
 *   limit is set for the control; lprgSysTimeArray[1] is valid and contains the applicable date
 *   information.
 */
#define MCM_GETRANGE (MCM_FIRST + 17)
/**
 * This macro retrieves the minimum and maximum allowable dates set for a month calendar control.
 *
 * @param hwndMC Handle to a month calendar control.
 * @param lprgSysTimeArray Long pointer to a two-element array of SYSTEMTIME structures that will
 *   receive the date limit information. The minimum limit is set in lprgSysTimeArray[0], and
 *   lprgSysTimeArray[1] receives the maximum limit. If either element is set to all zeros, then no
 *   corresponding limit is set for the month calendar control. The time members of these structures
 *   are not modified.
 *
 * @return Returns a DWORD that can be zero (no limits are set) or a combination of the following
 *   values that specify limit information: - GDTR_MAX: There is a maximum limit set for the control;
 *   lprgSysTimeArray[0] is valid and contains the applicable date information. - GDTR_MIN: There is a
 *   minimum limit set for the control; lprgSysTimeArray[1] is valid and contains the applicable date
 *   information.
 */
#define MonthCal_GetRange(hmc, rgst) \
        (DWORD)SNDMSG(hmc, MCM_GETRANGE, 0, (LPARAM)(rgst))

// BOOL MonthCal_SetRange(HWND hmc, DWORD gdtr, LPSYSTEMTIME rgst)
//   if GDTR_MIN, sets the minimum ALLOWABLE systemtime to rgst[0], otherwise removes minimum
//   if GDTR_MAX, sets the maximum ALLOWABLE systemtime to rgst[1], otherwise removes maximum
//   returns TRUE on success, FALSE on error (such as invalid parameters)
/**
 * This message sets the minimum and maximum allowable dates for a month calendar control.
 *
 * @param fWhichLimit Specifies which limit dates are being set. It is one or both of the following
 *   values: Value Description GDTR_MAX The maximum allowable date is being set. The SYSTEMTIME
 *   structure at lprgSysTimeArray[1] must contain date information. GDTR_MIN The minimum allowable
 *   date is being set. The SYSTEMTIME structure at lprgSysTimeArray[0] must contain date information.
 * @param lprgSysTimeArray Long pointer to a two-element array of SYSTEMTIME structures that
 *   contains date limit information. The maximum limit must be in lpSysTimeArray[1] if GDTR_MAX is
 *   specified, and lpSysTimeArray[0] must contain the minimum limit if GDTR_MIN is specified. The
 *   time members of these structures are ignored.
 *
 * @return Nonzero indicates success. Zero indicates otherwise.
 */
#define MCM_SETRANGE (MCM_FIRST + 18)
/**
 * This macro sets the minimum and maximum allowable dates for a month calendar control.
 *
 * @param hwndMC Handle to a month calendar control.
 * @param fWhichLimit Values that specify which limit dates are being set. It is one or both of the
 *   following values: Value Description GDTR_MAX The maximum allowable date is being set. The
 *   SYSTEMTIME structure at lprgSysTimeArray[1] must contain date information. GDTR_MIN The minimum
 *   allowable date is being set. The SYSTEMTIME structure at lprgSysTimeArray[0] must contain date
 *   information.
 * @param lprgSysTimeArray Long pointer to a two-element array of SYSTEMTIME structures that
 *   contains date limit information. The maximum limit must be in lpSysTimeArray[1] if GDTR_MAX is
 *   specified, and lpSysTimeArray[0] must contain the minimum limit if GDTR_MIN is specified. The
 *   time members of these structure are ignored.
 *
 * @return Nonzero indicates success. Zero indicates otherwise.
 */
#define MonthCal_SetRange(hmc, gd, rgst) \
        (BOOL)SNDMSG(hmc, MCM_SETRANGE, (WPARAM)(gd), (LPARAM)(rgst))

// int MonthCal_GetMonthDelta(HWND hmc)
//   returns the number of months one click on a next/prev button moves by
/**
 * This message retrieves the "scroll rate" for a month calendar control. The scroll rate is the
 * number of months that the control moves its display when the user clicks a scroll button.
 *
 * @return If the month delta was previously set using the MCM_SETMONTHDELTA message, returns an INT
 *   value that represents the month calendar's current scroll rate. If the month delta was not
 *   previously set using the MCM_SETMONTHDELTA message or the month delta was reset to the default,
 *   returns an INT value that represents the current number of months visible.
 */
#define MCM_GETMONTHDELTA (MCM_FIRST + 19)
/**
 * This macro retrieves the "scroll rate" for a month calendar control. The scroll rate is the
 * number of months that the control moves its display when the user clicks a scroll button.
 *
 * @param hwndMC Handle to a month calendar control.
 *
 * @return If the month delta was previously set using the MonthCal_SetMonthDelta macro, returns an
 *   INT value that represents the month calendar's current scroll rate. If the month delta was not
 *   previously set using the MonthCal_SetMonthDelta macro or the month delta was reset to the
 *   default, returns an INT value that represents the current number of months visible.
 */
#define MonthCal_GetMonthDelta(hmc) \
        (int)SNDMSG(hmc, MCM_GETMONTHDELTA, 0, 0)

// int MonthCal_SetMonthDelta(HWND hmc, int n)
//   sets the month delta to n. n==0 reverts to moving by a page of months
//   returns the previous value of n.
/**
 * This message sets the "scroll rate" for a month calendar control. The scroll rate is the number
 * of months that a month calendar control moves its display when the user clicks a scroll button.
 *
 * @param iDelta Number of months to be set as the control's scroll rate. If this value is zero, the
 *   month delta is reset to the default, which is the number of months displayed in the control.
 *
 * @return Returns an INT value that represents the previous scroll rate. If the scroll rate has not
 *   been previously set, the return value is zero.
 */
#define MCM_SETMONTHDELTA (MCM_FIRST + 20)
/**
 * This macro sets the "scroll rate" for a month calendar control. The scroll rate is the number of
 * months that a month calendar control moves its display when the user clicks a scroll button.
 *
 * @param hwndMC Handle to a month calendar control.
 * @param iDelta Value representing the number of months to be set as the control's scroll rate. If
 *   this value is zero, the month delta is reset to the default, which is the number of months
 *   displayed in the control.
 *
 * @return Returns an INT value that represents the previous scroll rate. If the scroll rate has not
 *   been previously set, the return value is zero.
 */
#define MonthCal_SetMonthDelta(hmc, n) \
        (int)SNDMSG(hmc, MCM_SETMONTHDELTA, n, 0)

// DWORD MonthCal_GetMaxTodayWidth(HWND hmc, LPSIZE psz)
//   sets *psz to the maximum width/height of the "Today" string displayed
//   at the bottom of the calendar (as long as MCS_NOTODAY is not specified)
/**
 * This message retrieves the maximum width of the "Today" string in a month calendar control. This
 * includes the label text and the date text.
 *
 * @return Returns the width of the "Today" string, in pixels.
 */
#define MCM_GETMAXTODAYWIDTH (MCM_FIRST + 21)
/**
 * This macro retrieves the maximum width of the "Today" string in a month calendar control. This
 * includes the label text and the date text.
 *
 * @param hwndMC Handle to a month calendar control.
 *
 * @return Returns the width of the "Today" string, in pixels.
 */
#define MonthCal_GetMaxTodayWidth(hmc) \
        (DWORD)SNDMSG(hmc, MCM_GETMAXTODAYWIDTH, 0, 0)

// MCN_SELCHANGE is sent whenever the currently displayed date changes
// via month change, year change, keyboard navigation, prev/next button
//
/**
 * This structure carries information required to process the MCN_SELCHANGE notification message.
 */
typedef struct tagNMSELCHANGE
{
    /**
     * NMHDR structure that contains information about this notification message.
     */
    NMHDR           nmhdr;  // this must be first, so we don't break WM_NOTIFY

    /**
     * SYSTEMTIME structure that contains the date for the first day in the user's selection range.
     */
    SYSTEMTIME      stSelStart;
    /**
     * SYSTEMTIME structure that contains the date for the last day in the user's selection range.
     */
    SYSTEMTIME      stSelEnd;
} NMSELCHANGE, FAR * LPNMSELCHANGE;

/**
 * This notification message is sent by a month calendar control whenever the currently selected
 * date or range of dates changes. It is sent in the form of a WM_NOTIFY message.
 *
 * @param lpNMSelChange Long pointer to an NMSELCHANGE structure that contains information about the
 *   currently selected date range.
 *
 * This notification message is similar to MCN_SELECT, but is sent in response to any selection
 * change, whereas MCN_SELECT is sent only for an explicit date selection.
 */
#define MCN_SELCHANGE       (MCN_FIRST + 1)

// MCN_GETDAYSTATE is sent for MCS_DAYSTATE controls whenever new daystate
// information is needed (month or year scroll) to draw bolding information.
// The app must fill in cDayState months worth of information starting from
// stStart date. The app may fill in the array at prgDayState or change
// prgDayState to point to a different array out of which the information
// will be copied. (similar to tooltips)
//
/**
 * This structure carries information required to process the MCN_GETDAYSTATE notification message.
 * All members of this structure are for input, except prgDayState, which the user must set when
 * processing MCN_GETDAYSTATE.
 */
typedef struct tagNMDAYSTATE
{
    /**
     * NMHDR structure that contains information about this notification message.
     */
    NMHDR           nmhdr;  // this must be first, so we don't break WM_NOTIFY

    /**
     * SYSTEMTIME structure that contains the starting date.
     */
    SYSTEMTIME      stStart;
    /**
     * Value that specifies the total number of elements that must be in the array at prgDayState.
     */
    int             cDayState;

    /**
     * Pointer to an array of MONTHDAYSTATE values. This must be set to point to an array that contains
     * as many elements as specified in cDayState. The first element in the array corresponds to the
     * date in stStart.
     */
    LPMONTHDAYSTATE prgDayState; // points to cDayState MONTHDAYSTATEs
} NMDAYSTATE, FAR * LPNMDAYSTATE;

/**
 * This notification message is sent by a month calendar control to request information about how
 * individual days should be displayed. It is sent only by month calendar controls that use the
 * MCS_DAYSTATE style, and is sent in the form of a WM_NOTIFY message.
 *
 * @param lpNMDayState Long pointer to an NMDAYSTATE structure. The structure contains information
 *   about the time frame for which the control needs information, and receives the address of an
 *   array that provides such data.
 *
 * Handling this notification message allows your application to customize its display by specifying
 * that certain days be displayed in bold. For more information about processing this message, see
 * "Processing the MCN_GETDAYSTATE Notification Message."
 */
#define MCN_GETDAYSTATE     (MCN_FIRST + 3)

// MCN_SELECT is sent whenever a selection has occured (via mouse or keyboard)
//
typedef NMSELCHANGE NMSELECT, FAR * LPNMSELECT;


/**
 * This notification message is sent by a month calendar control whenever the user makes an explicit
 * date selection within a month calendar control. It is sent in the form of a WM_NOTIFY message.
 *
 * @param lpNMSelChange Long pointer to an NMSELCHANGE structure that contains information about the
 *   currently selected date range.
 *
 * This notification message is similar to MCN_SELCHANGE, but is sent only in response to a user's
 * explicit date selections, whereas MCN_SELCHANGE applies to any selection change.
 */
#define MCN_SELECT          (MCN_FIRST + 4)


#define MCS_DAYSTATE        0x0001
#define MCS_MULTISELECT     0x0002
#define MCS_WEEKNUMBERS     0x0004
#if (_WIN32_IE >= 0x0400)
#define MCS_NOTODAYCIRCLE   0x0008
#define MCS_NOTODAY         0x0010
#else
#define MCS_NOTODAY         0x0008
#endif      


#define GMR_VISIBLE     0       // visible portion of display
#define GMR_DAYSTATE    1       // above plus the grayed out parts of
                                // partially displayed months


#endif // _WIN32
#endif // NOMONTHCAL


//====== DATETIMEPICK CONTROL ==================================================

#ifndef NODATETIMEPICK
#ifdef _WIN32

#define DATETIMEPICK_CLASSW          L"SysDateTimePick32"
#define DATETIMEPICK_CLASSA          "SysDateTimePick32"

#ifdef UNICODE
#define DATETIMEPICK_CLASS           DATETIMEPICK_CLASSW
#else
#define DATETIMEPICK_CLASS           DATETIMEPICK_CLASSA
#endif

#define DTM_FIRST        0x1000

// DWORD DateTimePick_GetSystemtime(HWND hdp, LPSYSTEMTIME pst)
//   returns GDT_NONE if "none" is selected (DTS_SHOWNONE only)
//   returns GDT_VALID and modifies *pst to be the currently selected value
/**
 * This message retrieves the currently selected time from a date and time picker (DTP) control and
 * places it in a specified SYSTEMTIME structure.
 *
 * @param lpSysTime Long pointer to the SYSTEMTIME structure that receives the system time
 *   information. This parameter must be a valid address and cannot be NULL.
 *
 * @return Returns GDT_VALID if the time information was placed successfully in the specified
 *   structure; or the message can return GDT_NONE if the control was set to the DTS_SHOWNONE style
 *   and the control check box was not selected.
 */
#define DTM_GETSYSTEMTIME   (DTM_FIRST + 1)
/**
 * This macro retrieves the currently selected time from a date and time picker (DTP) control and
 * places it in a specified SYSTEMTIME structure.
 *
 * @param hwndDP Handle to a DTP control.
 * @param lpSysTime Long pointer to the SYSTEMTIME structure that receives the system time
 *   information.
 *
 * @return Returns a DWORD value that equals GDT_VALID if the time information was successfully
 *   placed in the specified structure; or the message can return GDT_NONE if the control was set to
 *   the DTS_SHOWNONE style and the control check box was not selected.
 */
#define DateTime_GetSystemtime(hdp, pst)    (DWORD)SNDMSG(hdp, DTM_GETSYSTEMTIME, 0, (LPARAM)(pst))

// BOOL DateTime_SetSystemtime(HWND hdp, DWORD gd, LPSYSTEMTIME pst)
//   if gd==GDT_NONE, sets datetimepick to None (DTS_SHOWNONE only)
//   if gd==GDT_VALID, sets datetimepick to *pst
//   returns TRUE on success, FALSE on error (such as bad params)
/**
 * This message sets the time in a date and time picker (DTP) control.
 *
 * @param flag Specifies the action that should be performed. It is one of the following values:
 *   Value Description GDT_VALID Sets the DTP control according to the data within the structure that
 *   lpSysTime points to. GDT_NONE Sets the DTP control to "no date" and clear its check box.
 *   lpSysTime is ignored when this flag is specified. This flag applies only to DTP controls that are
 *   set to the DTS_SHOWNONE style.
 * @param lpSysTime Long pointer to a SYSTEMTIME structure that contains the system time used to set
 *   the DTP control.
 *
 * @return Nonzero indicates success. Zero indicates otherwise.
 */
#define DTM_SETSYSTEMTIME   (DTM_FIRST + 2)
/**
 * This macro sets a date and time picker (DTP) control to a specified date and time.
 *
 * @param hwndDT Handle to a DTP control.
 * @param flag Value that specifies the action that should be performed. It is one of the following
 *   values: Value Description GDT_VALID Set the DTP control according to the data within the
 *   SYSTEMTIME structure pointed to by lpSysTime. GDT_NONE Set the DTP control to "no date" and clear
 *   its check box. lpSysTime is ignored when this flag is specified. This flag applies only to DTP
 *   controls that are set to the DTS_SHOWNONE style.
 * @param lpSysTime Long pointer to a SYSTEMTIME structure that contains the system time information
 *   by which to set the DTP control.
 *
 * @return Nonzero indicates success. Zero indicates otherwise.
 */
#define DateTime_SetSystemtime(hdp, gd, pst)    (BOOL)SNDMSG(hdp, DTM_SETSYSTEMTIME, (LPARAM)(gd), (LPARAM)(pst))

// DWORD DateTime_GetRange(HWND hdp, LPSYSTEMTIME rgst)
//   modifies rgst[0] to be the minimum ALLOWABLE systemtime (or 0 if no minimum)
//   modifies rgst[1] to be the maximum ALLOWABLE systemtime (or 0 if no maximum)
//   returns GDTR_MIN|GDTR_MAX if there is a minimum|maximum limit
/**
 * This message retrieves the current minimum and maximum allowable system times for a date and time
 * picker (DTP) control.
 *
 * @param lpSysTimeArray Long pointer to a two-element array of SYSTEMTIME structures.
 *
 * @return Returns a DWORD value that is a combination of GDTR_MIN or GDTR_MAX.
 *
 * The first element of the SYSTEMTIME array contains the minimum allowable time if GDTR_MIN is set.
 * The second element of the SYSTEMTIME array contains the maximum allowable time if GDTR_MAX is
 * set.
 */
#define DTM_GETRANGE (DTM_FIRST + 3)
/**
 * This macro retrieves the current minimum and maximum allowable system times for a date and time
 * picker (DTP) control.
 *
 * @param hwndDT Handle to a DTP control.
 * @param lpSysTimeArray Long pointer to a two-element array of SYSTEMTIME structures.
 *
 * @return Returns a DWORD value that is a combination of GDTR_MIN or GDTR_MAX. The first element of
 *   the SYSTEMTIME array contains the minimum allowable time. The second element of the SYSTEMTIME
 *   array contains the maximum allowable time.
 */
#define DateTime_GetRange(hdp, rgst)  (DWORD)SNDMSG(hdp, DTM_GETRANGE, 0, (LPARAM)(rgst))

// BOOL DateTime_SetRange(HWND hdp, DWORD gdtr, LPSYSTEMTIME rgst)
//   if GDTR_MIN, sets the minimum ALLOWABLE systemtime to rgst[0], otherwise removes minimum
//   if GDTR_MAX, sets the maximum ALLOWABLE systemtime to rgst[1], otherwise removes maximum
//   returns TRUE on success, FALSE on error (such as invalid parameters)
/**
 * This message sets the minimum and maximum allowable system times for a date and time picker (DTP)
 * control.
 *
 * @param flags Specifies which range values are valid. It can be a combination of the following
 *   values: Value Description GDTR_MIN The first element in the SYSTEMTIME structure array is valid
 *   and will be used to set the minimum allowable system time. GDTR_MAX The second element in the
 *   SYSTEMTIME structure array is valid and will be used to set the maximum allowable system time.
 * @param lpSysTimeArray Long pointer to a two-element array of SYSTEMTIME structures. The first
 *   element of the SYSTEMTIME array contains the minimum allowable time. The second element of the
 *   SYSTEMTIME array contains the maximum allowable time. It is not necessary to fill an array
 *   element that is not specified in the flags parameter.
 *
 * @return Nonzero indicates success. Zero indicates otherwise.
 */
#define DTM_SETRANGE (DTM_FIRST + 4)
/**
 * This macro sets the minimum and maximum allowable system times for a date and time picker (DTP)
 * control.
 *
 * @param hwndDT Handle to a DTP control.
 * @param flags Value that specifies which range values are valid. It can be a combination of the
 *   following values: Value Description GDTR_MIN The first element in the SYSTEMTIME structure array
 *   is valid and will be used to set the minimum allowable system time. GDTR_MAX The second element
 *   in the SYSTEMTIME structure array is valid and will be used to set the maximum allowable system
 *   time.
 * @param lpSysTimeArray Long pointer to a two-element array of SYSTEMTIME structures. The first
 *   element of the SYSTEMTIME array contains the minimum allowable time. The second element of the
 *   SYSTEMTIME array contains the maximum allowable time. It is not necessary to fill an array
 *   element that is not specified in the flags parameter.
 *
 * @return Nonzero indicates success. Zero indicates otherwise.
 */
#define DateTime_SetRange(hdp, gd, rgst)  (BOOL)SNDMSG(hdp, DTM_SETRANGE, (WPARAM)(gd), (LPARAM)(rgst))

// BOOL DateTime_SetFormat(HWND hdp, LPCTSTR sz)
//   sets the display formatting string to sz (see GetDateFormat and GetTimeFormat for valid formatting chars)
//   NOTE: 'X' is a valid formatting character which indicates that the application
//   will determine how to display information. Such apps must support DTN_WMKEYDOWN,
//   DTN_FORMAT, and DTN_FORMATQUERY.
#define DTM_SETFORMATA (DTM_FIRST + 5)
#define DTM_SETFORMATW (DTM_FIRST + 50)

#ifdef UNICODE
/**
 * This message sets the display of a date and time picker (DTP) control based on a specified format
 * string.
 *
 * @param lpszFormat Long pointer to a null-terminated format string that defines the desired
 *   display. Setting this parameter to NULL will reset the control to the default format string for
 *   the current style. The format string is a combination of string fragments. It is interpreted
 *   literally, with the exception of the following string fragments: Value Description "d" The one-
 *   or two-digit day. "dd" The two-digit day. Single-digit day values are preceded by a zero. "ddd"
 *   The three-character weekday abbreviation. "dddd" The full weekday name. "h" The one- or two-digit
 *   hour in 12-hour format. "hh" The two-digit hour in 12-hour format. Single-digit values are
 *   preceded by a zero. "H" The one- or two-digit hour in 24-hour format. "HH" The two-digit hour in
 *   24-hour format. Single-digit values are preceded by a zero. "m" The one- or two-digit minute.
 *   "mm" The two-digit minute. Single-digit values are preceded by a zero. "M" The one- or two-digit
 *   month number. "MM" The two-digit month number. Single-digit values are preceded by a zero. "MMM"
 *   The three-character month abbreviation. "MMMM" The full month name. "t" The one-letter AM/PM
 *   abbreviation; that is, "AM" is displayed as "A." "tt" The two-letter AM/PM abbreviation; that is,
 *   "AM" is displayed as "AM." "X" A callback field. The control still uses the other valid format
 *   characters, and queries the owner to fill in the "X" portion. Therefore, the owner must be
 *   prepared to handle the DTN_WMKEYDOWN, DTN_FORMAT, and DTN_FORMATQUERY notification messages.
 *   Multiple "X" characters can be used in series to signify unique callback fields. "y" The year is
 *   displayed as the last two digits, but with no leading zero for years less than 10. "yy" The last
 *   two digits of the year; that is, 1996 would be displayed as "96." "yyyy" The full year; that is,
 *   1996 would be displayed as "1996."
 *
 * @return Nonzero indicates success. Zero indicates otherwise.
 *
 * It is acceptable to include extra characters within the format string to produce a richer
 * display. However, any nonformat characters must be enclosed within single quotes. For example,
 * the format string "'Today is: 'hh':'m':'s ddddMMMdd', 'yyy" would produce output like "Today is:
 * 04:22:31 Tuesday Mar 23, 1996".
 *
 * No errors are returned for a bad format string. The function simply forms the best date string
 * that it can. For example, the only year pictures that are valid are L"yyyy" and L"yy" (the 'L'
 * indicates a Unicode (16-bit characters) string). If L"y" is passed in, the function assumes
 * L"yy". If L"yyy" is passed in, the function assumes L"yyyy". If more than 4 date (L"dddd") or 4
 * month (L"MMMM") pictures are passed in, then the function defaults to L"dddd" or L"MMMM".
 *
 * Any text that should remain in its exact form in the date string should be enclosed within single
 * quotation marks in the date format picture. The single quotation mark may also be used as an
 * escape character to allow the single quotation mark itself to be displayed in the date string.
 * However, the escape sequence must be enclosed within two single quotation marks. For example, to
 * display the date as "May '93", the format string would be: L"MMMM ''''yy" The first and last
 * single quotation marks are the enclosing quotation marks. The second and third single quotation
 * marks are the escape sequence to allow the single quotation mark to be displayed before the
 * century.
 *
 * Note A DTP control tracks locale changes when it is using the default format string. If you set a
 * custom format string, it will not be updated in response to locale changes.
 */
#define DTM_SETFORMAT       DTM_SETFORMATW
#else
/**
 * This message sets the display of a date and time picker (DTP) control based on a specified format
 * string.
 *
 * @param lpszFormat Long pointer to a null-terminated format string that defines the desired
 *   display. Setting this parameter to NULL will reset the control to the default format string for
 *   the current style. The format string is a combination of string fragments. It is interpreted
 *   literally, with the exception of the following string fragments: Value Description "d" The one-
 *   or two-digit day. "dd" The two-digit day. Single-digit day values are preceded by a zero. "ddd"
 *   The three-character weekday abbreviation. "dddd" The full weekday name. "h" The one- or two-digit
 *   hour in 12-hour format. "hh" The two-digit hour in 12-hour format. Single-digit values are
 *   preceded by a zero. "H" The one- or two-digit hour in 24-hour format. "HH" The two-digit hour in
 *   24-hour format. Single-digit values are preceded by a zero. "m" The one- or two-digit minute.
 *   "mm" The two-digit minute. Single-digit values are preceded by a zero. "M" The one- or two-digit
 *   month number. "MM" The two-digit month number. Single-digit values are preceded by a zero. "MMM"
 *   The three-character month abbreviation. "MMMM" The full month name. "t" The one-letter AM/PM
 *   abbreviation; that is, "AM" is displayed as "A." "tt" The two-letter AM/PM abbreviation; that is,
 *   "AM" is displayed as "AM." "X" A callback field. The control still uses the other valid format
 *   characters, and queries the owner to fill in the "X" portion. Therefore, the owner must be
 *   prepared to handle the DTN_WMKEYDOWN, DTN_FORMAT, and DTN_FORMATQUERY notification messages.
 *   Multiple "X" characters can be used in series to signify unique callback fields. "y" The year is
 *   displayed as the last two digits, but with no leading zero for years less than 10. "yy" The last
 *   two digits of the year; that is, 1996 would be displayed as "96." "yyyy" The full year; that is,
 *   1996 would be displayed as "1996."
 *
 * @return Nonzero indicates success. Zero indicates otherwise.
 *
 * It is acceptable to include extra characters within the format string to produce a richer
 * display. However, any nonformat characters must be enclosed within single quotes. For example,
 * the format string "'Today is: 'hh':'m':'s ddddMMMdd', 'yyy" would produce output like "Today is:
 * 04:22:31 Tuesday Mar 23, 1996".
 *
 * No errors are returned for a bad format string. The function simply forms the best date string
 * that it can. For example, the only year pictures that are valid are L"yyyy" and L"yy" (the 'L'
 * indicates a Unicode (16-bit characters) string). If L"y" is passed in, the function assumes
 * L"yy". If L"yyy" is passed in, the function assumes L"yyyy". If more than 4 date (L"dddd") or 4
 * month (L"MMMM") pictures are passed in, then the function defaults to L"dddd" or L"MMMM".
 *
 * Any text that should remain in its exact form in the date string should be enclosed within single
 * quotation marks in the date format picture. The single quotation mark may also be used as an
 * escape character to allow the single quotation mark itself to be displayed in the date string.
 * However, the escape sequence must be enclosed within two single quotation marks. For example, to
 * display the date as "May '93", the format string would be: L"MMMM ''''yy" The first and last
 * single quotation marks are the enclosing quotation marks. The second and third single quotation
 * marks are the escape sequence to allow the single quotation mark to be displayed before the
 * century.
 *
 * Note A DTP control tracks locale changes when it is using the default format string. If you set a
 * custom format string, it will not be updated in response to locale changes.
 */
#define DTM_SETFORMAT       DTM_SETFORMATA
#endif

/**
 * This macro sets the display of a date and time picker (DTP) control based on a specified format
 * string.
 *
 * @param hwndDT Handle to a DTP control.
 * @param lpszFormat Long pointer to a null-terminated format string that defines the desired
 *   display. Setting this parameter to NULL will reset the control to the default format string for
 *   the current style. The format string is a combination of string fragments. It is interpreted
 *   literally, with the exception of the following string fragments. Value Description "d" The one-
 *   or two-digit day. "dd" The two-digit day. Single-digit day values are preceded by a zero. "ddd"
 *   The three-character weekday abbreviation. "dddd" The full weekday name. "h" The one- or two-digit
 *   hour in 12-hour format. "hh" The two-digit hour in 12-hour format. Single-digit values are
 *   preceded by a zero. "H" The one- or two-digit hour in 24-hour format. "HH" The two-digit hour in
 *   24-hour format. Single-digit values are preceded by a zero. "m" The one- or two-digit minute.
 *   "mm" The two-digit minute. Single-digit values are preceded by a zero. "M" The one- or two-digit
 *   month number. "MM" The two-digit month number. Single-digit values are preceded by a zero. "MMM"
 *   The three-character month abbreviation. "MMMM" The full month name. "t" The one-letter AM/PM
 *   abbreviation (that is, "AM" is displayed as "A"). "tt" The two-letter AM/PM abbreviation (that
 *   is, "AM" is displayed as "AM"). "X" A callback field. The control still uses the other valid
 *   format characters, and queries the owner to fill in the "X" portion. Therefore, the owner must be
 *   prepared to handle the DTN_WMKEYDOWN, DTN_FORMAT, and DTN_FORMATQUERY notification messages.
 *   Multiple "X" characters can be used to signify unique callback fields. "y" The year is displayed
 *   as the last two digits, but with no leading zero for years less than 10. "yy" The last two digits
 *   of the year (that is, 1998 would be displayed as "98"). "yyy" The full year (that is, 1998 would
 *   be displayed as "1998").
 *
 * @return Returns TRUE if successful, or FALSE otherwise.
 *
 * It is acceptable to include extra characters within the format string to produce a richer
 * display. However, any nonformat characters must be enclosed within single quotes. For example,
 * the format string " 'Today is: 'hh':'m':'s ddddMMMdd', 'yyy" would produce output like "Today is:
 * 04:22:31 Tuesday Mar 23, 1996".
 *
 * No errors are returned for a bad format string. The function simply forms the best date string
 * that it can. For example, the only year pictures that are valid are L"yyyy" and L"yy" (the 'L'
 * indicates a Unicode (16-bit characters) string). If L"y" is passed in, the function assumes
 * L"yy". If L"yyy" is passed in, the function assumes L"yyyy". If more than 4 date ("dddd") or 4
 * month (L"MMMM") pictures are passed in, then the function defaults to L"dddd" or L"MMMM".
 *
 * Any text that should remain in its exact form in the date string should be enclosed within single
 * quotation marks in the date format picture. The single quotation mark may also be used as an
 * escape character to allow the single quotation mark itself to be displayed in the date string.
 * However, the escape sequence must be enclosed within two single quotation marks. For example, to
 * display the date as "May '93", the format string would be: L"MMMM ''''yy" The first and last
 * single quotation marks are the enclosing quotation marks. The second and third single quotation
 * marks are the escape sequence to allow the single quotation mark to be displayed before the
 * century.
 *
 * Note A DTP control tracks locale changes when it is using the default format string. If you set a
 * custom format string, it will not be updated in response to locale changes.
 */
#define DateTime_SetFormat(hdp, sz)  (BOOL)SNDMSG(hdp, DTM_SETFORMAT, 0, (LPARAM)(sz))


/**
 * This message sets the color for a specified portion of the month calendar within a date and time
 * picker (DTP) control.
 *
 * @param iColor Specifies which month calendar color to set. It is one of the following values:
 *   Value Description MCSC_BACKGROUND Sets the background color displayed between months.
 *   MCSC_MONTHBK Sets the background color displayed within the month. MCSC_TEXT Sets the color used
 *   to display text within a month. MCSC_TITLEBK Sets the background color displayed in the
 *   calendar's title. MCSC_TITLETEXT Sets the color used to display text within the calendar's title.
 *   MCSC_TRAILINGTEXT Sets the color used to display header and trailing-day text. Header and
 *   trailing days are the days from the previous and following months that appear on the current
 *   calendar.
 * @param clr COLORREF value that represents the color that is set for the specified area of the
 *   month calendar.
 *
 * @return Returns a COLORREF value that represents the previous color setting for the specified
 *   portion of the month calendar control if successful. Otherwise, the message returns -1.
 */
#define DTM_SETMCCOLOR    (DTM_FIRST + 6)
/**
 * This macro sets the color for a specified portion of the month calendar within a date and time
 * picker (DTP) control.
 *
 * @param hwndDP Handle to a DTP control.
 * @param iColor INT value that specifies which month calendar color to set. It is one of the
 *   following values: Value Description MCSC_BACKGROUND Sets the background color displayed between
 *   months. MCSC_MONTHBK Sets the background color displayed within the month. MCSC_TEXT Sets the
 *   color used to display text within a month. MCSC_TITLEBK Sets the background color displayed in
 *   the calendar's title. MCSC_TITLETEXT Sets the color used to display text within the calendar's
 *   title. MCSC_TRAILINGTEXT Sets the color used to display header and trailing-day text. Header and
 *   trailing days are the days from the previous and following months that appear on the current
 *   calendar.
 * @param clr COLORREF value that represents the color that will be set for the specified area of
 *   the month calendar.
 *
 * @return Returns a COLORREF value that represents the previous color setting for the specified
 *   portion of the month calendar control if successful. Otherwise, this message returns -1.
 */
#define DateTime_SetMonthCalColor(hdp, iColor, clr) SNDMSG(hdp, DTM_SETMCCOLOR, iColor, clr)

/**
 * This message retrieves the color for a specified portion of the month calendar within a date and
 * time picker (DTP) control.
 *
 * @param iColor Specifies which month calendar color to retrieve. It is one of the following
 *   values: Value Description MCSC_BACKGROUND Retrieves the background color displayed between
 *   months. MCSC_MONTHBK Retrieves the background color displayed within the month. MCSC_TEXT
 *   Retrieves the color used to display text within a month. MCSC_TITLEBK Retrieves the background
 *   color displayed in the calendar's title. MCSC_TITLETEXT Retrieves the color used to display text
 *   within the calendar's title. MCSC_TRAILINGTEXT Retrieves the color used to display header and
 *   trailing-day text. Header and trailing days are the days from the previous and following months
 *   that appear on the current calendar.
 *
 * @return Returns a COLORREF value that represents the color setting for the specified portion of
 *   the month calendar control if successful. The message returns -1 if unsuccessful.
 */
#define DTM_GETMCCOLOR    (DTM_FIRST + 7)
/**
 * This macro retrieves the color for a specified portion of the month calendar within a date and
 * time picker (DTP) control.
 *
 * @param hwndDP Handle to a DTP control.
 * @param iColor INT value that specifies which month calendar color to retrieve. It is one of the
 *   following values: Value Description MCSC_BACKGROUND Retrieves the background color displayed
 *   between months. MCSC_MONTHBK Retrieves the background color displayed within the month. MCSC_TEXT
 *   Retrieves the color used to display text within a month. MCSC_TITLEBK Retrieves the background
 *   color displayed in the calendar's title. MCSC_TITLETEXT Retrieves the color used to display text
 *   within the calendar's title. MCSC_TRAILINGTEXT Retrieves the color used to display header and
 *   trailing-day text. Header and trailing days are the days from the previous and following months
 *   that appear on the current calendar.
 *
 * @return Returns a COLORREF value that represents the color setting for the specified portion of
 *   the month calendar control if successful. Otherwise, the macro returns -1.
 */
#define DateTime_GetMonthCalColor(hdp, iColor) SNDMSG(hdp, DTM_GETMCCOLOR, iColor, 0)

// HWND DateTime_GetMonthCal(HWND hdp)
//   returns the HWND of the MonthCal popup window. Only valid
// between DTN_DROPDOWN and DTN_CLOSEUP notifications.
/**
 * This message retrieves the handle to a date and time picker's (DTP) child month calendar control.
 *
 * @return Returns the handle to a DTP control's child month calendar control upon success. The
 *   message returns NULL upon failure.
 *
 * DTP controls create a child month calendar control when the user clicks the drop-down arrow. When
 * the month calendar is no longer needed, it is destroyed. Therefore, your application must not
 * rely on a static handle to the DTP control's child month calendar.
 */
#define DTM_GETMONTHCAL   (DTM_FIRST + 8)
/**
 * This macro retrieves the handle to a date and time picker's (DTP) child month calendar control.
 *
 * @param hwndDP Handle to a DTP control.
 *
 * @return Returns the handle to a DTP control's child month calendar control.
 *
 * DTP controls create a child month calendar control when the user clicks the drop-down arrow. When
 * the month calendar is no longer needed, it is destroyed. Therefore, your application must not
 * rely on a static handle to the DTP's child month calendar.
 */
#define DateTime_GetMonthCal(hdp) (HWND)SNDMSG(hdp, DTM_GETMONTHCAL, 0, 0)

#if (_WIN32_IE >= 0x0400)

/**
 * This message sets the font to be used by the date and time picker (DTP) control's child month
 * calendar control.
 *
 * @param hFont Handle to the font to be set.
 * @param fRedraw Boolean that specifies whether the control should be redrawn immediately upon
 *   setting the font. Setting this parameter to TRUE causes the control to redraw itself.
 *
 * @return The return value for this message is not used.
 */
#define DTM_SETMCFONT     (DTM_FIRST + 9)
/**
 * This macro sets the font to be used by the date and time picker (DTP) control's child month
 * calendar control.
 *
 * @param hwndDP Handle to a DTP control.
 * @param hFont Handle to the font that will be set.
 * @param fRedraw Value that specifies whether the control should be redrawn immediately upon
 *   setting the font. If set to TRUE, the control redraws itself.
 */
#define DateTime_SetMonthCalFont(hdp, hfont, fRedraw) SNDMSG(hdp, DTM_SETMCFONT, (WPARAM)hfont, (LPARAM)fRedraw)

/**
 * This message retrieves the font that the date and time picker (DTP) control's child month
 * calendar control is currently using.
 *
 * @return Returns an HFONT value that is the handle to the current font.
 */
#define DTM_GETMCFONT     (DTM_FIRST + 10)
/**
 * This macro retrieves the font that the date and time picker (DTP) control's child month calendar
 * control is currently using.
 *
 * @param hwndDP Handle to a DTP control.
 *
 * @return Returns an HFONT value that is the handle to the current font.
 */
#define DateTime_GetMonthCalFont(hdp) SNDMSG(hdp, DTM_GETMCFONT, 0, 0)

#endif      // _WIN32_IE >= 0x0400

#define DTS_UPDOWN          0x0001 // use UPDOWN instead of MONTHCAL
#define DTS_SHOWNONE        0x0002 // allow a NONE selection
#define DTS_SHORTDATEFORMAT 0x0000 // use the short date format (app must forward WM_WININICHANGE messages)
#define DTS_LONGDATEFORMAT  0x0004 // use the long date format (app must forward WM_WININICHANGE messages)
#define DTS_TIMEFORMAT      0x0009 // use the time format (app must forward WM_WININICHANGE messages)
#define DTS_APPCANPARSE     0x0010 // allow user entered strings (app MUST respond to DTN_USERSTRING)
#define DTS_RIGHTALIGN      0x0020 // right-align popup instead of left-align it

/**
 * This notification message is sent by a date and time picker (DTP) control whenever a change
 * occurs. It is sent in the form of a WM_NOTIFY message.
 *
 * @param lpChange Long pointer to an NMDATETIMECHANGE structure that contains information about the
 *   change that took place in the control.
 *
 * @return The owner of the control must return zero.
 */
#define DTN_DATETIMECHANGE  (DTN_FIRST + 1) // the systemtime has changed
/**
 * This structure contains information about a change that has taken place in a date and time picker
 * (DTP) control. This structure is used with the DTN_DATETIMECHANGE notification message.
 */
typedef struct tagNMDATETIMECHANGE
{
    /**
     * NMHDR structure that contains information about the notification message.
     */
    NMHDR       nmhdr;
    /**
     * Specifies if the control was set to "no date" status (for DTS_SHOWNONE only). Also specifies
     * whether the contents of the st member are valid and contain current time information. It is one
     * of the following values: Value Description GDT_NONE The control is set to "no date" status. The
     * "no date" status applies only to controls that are set to the DTS_SHOWNONE style. GDT_VALID The
     * control is not set to the "no date" status. The st member contains the current date and time.
     */
    DWORD       dwFlags;    // GDT_VALID or GDT_NONE
    /**
     * SYSTEMTIME structure that contains information about the current system date and time.
     */
    SYSTEMTIME  st;         // valid iff dwFlags==GDT_VALID
} NMDATETIMECHANGE, FAR * LPNMDATETIMECHANGE;

#define DTN_USERSTRINGA  (DTN_FIRST + 2) // the user has entered a string
#define DTN_USERSTRINGW  (DTN_FIRST + 15)
/**
 * This structure contains information specific to an edit operation that has taken place in a date
 * and time picker (DTP) control. This message is used with the DTN_USERSTRING notification message.
 */
typedef struct tagNMDATETIMESTRINGA
{
    /**
     * NMHDR structure that contains information about this notification message.
     */
    NMHDR      nmhdr;
    /**
     * Pointer to the null-terminated string that the user entered.
     */
    LPCSTR     pszUserString;  // string user entered
    /**
     * SYSTEMTIME structure that must be filled in by the owner when handling the DTN_USERSTRING
     * notification message.
     */
    SYSTEMTIME st;             // app fills this in
    /**
     * Return member. Set this member to GDT_VALID to indicate that the st member is valid, or to
     * GDT_NONE to set the control to "no date" status (DTS_SHOWNONE style only).
     */
    DWORD      dwFlags;        // GDT_VALID or GDT_NONE
} NMDATETIMESTRINGA, FAR * LPNMDATETIMESTRINGA;

/**
 * This structure contains information specific to an edit operation that has taken place in a date
 * and time picker (DTP) control. This message is used with the DTN_USERSTRING notification message.
 */
typedef struct tagNMDATETIMESTRINGW
{
    /**
     * NMHDR structure that contains information about this notification message.
     */
    NMHDR      nmhdr;
    /**
     * Pointer to the null-terminated string that the user entered.
     */
    LPCWSTR    pszUserString;  // string user entered
    /**
     * SYSTEMTIME structure that must be filled in by the owner when handling the DTN_USERSTRING
     * notification message.
     */
    SYSTEMTIME st;             // app fills this in
    /**
     * Return member. Set this member to GDT_VALID to indicate that the st member is valid, or to
     * GDT_NONE to set the control to "no date" status (DTS_SHOWNONE style only).
     */
    DWORD      dwFlags;        // GDT_VALID or GDT_NONE
} NMDATETIMESTRINGW, FAR * LPNMDATETIMESTRINGW;

#ifdef UNICODE
/**
 * This notification message is sent by a date and time picker (DTP) control when a user completes
 * editing a string in the control. It is only sent by DTP controls that are set to the
 * DTS_APPCANPARSE style.
 *
 * @param lpDTstring Long pointer to an NMDATETIMESTRING structure that contains information about
 *   the instance of the notification message.
 *
 * This message is sent in the form of a WM_NOTIFY message.
 *
 * The owner of the control must return zero.
 *
 * Handling this message allows the owner to provide custom responses to strings entered into the
 * control by the user. The owner must be prepared to parse the input string and take action if
 * necessary.
 */
#define DTN_USERSTRING          DTN_USERSTRINGW
#define NMDATETIMESTRING        NMDATETIMESTRINGW
#define LPNMDATETIMESTRING      LPNMDATETIMESTRINGW
#else
/**
 * This notification message is sent by a date and time picker (DTP) control when a user completes
 * editing a string in the control. It is only sent by DTP controls that are set to the
 * DTS_APPCANPARSE style.
 *
 * @param lpDTstring Long pointer to an NMDATETIMESTRING structure that contains information about
 *   the instance of the notification message.
 *
 * This message is sent in the form of a WM_NOTIFY message.
 *
 * The owner of the control must return zero.
 *
 * Handling this message allows the owner to provide custom responses to strings entered into the
 * control by the user. The owner must be prepared to parse the input string and take action if
 * necessary.
 */
#define DTN_USERSTRING          DTN_USERSTRINGA
#define NMDATETIMESTRING        NMDATETIMESTRINGA
#define LPNMDATETIMESTRING      LPNMDATETIMESTRINGA
#endif


#define DTN_WMKEYDOWNA  (DTN_FIRST + 3) // modify keydown on app format field (X)
#define DTN_WMKEYDOWNW  (DTN_FIRST + 16)
/**
 * This structure carries information used to describe and handle a DTN_WMKEYDOWN notification
 * message.
 */
typedef struct tagNMDATETIMEWMKEYDOWNA
{
    /**
     * NMHDR structure that contains information about the notification message.
     */
    NMHDR      nmhdr;
    /**
     * Virtual key code that represents the key that the user pressed.
     */
    int        nVirtKey;  // virtual key code of WM_KEYDOWN which MODIFIES an X field
    /**
     * Pointer to a null-terminated substring, taken from the format string, that defines the callback
     * field.
     */
    LPCSTR     pszFormat; // format substring
    /**
     * SYSTEMTIME structure containing the current date and time from the DTP control. The owner of the
     * control must modify the time information based on the user's keystroke.
     */
    SYSTEMTIME st;        // current systemtime, app should modify based on key
} NMDATETIMEWMKEYDOWNA, FAR * LPNMDATETIMEWMKEYDOWNA;

/**
 * This structure carries information used to describe and handle a DTN_WMKEYDOWN notification
 * message.
 */
typedef struct tagNMDATETIMEWMKEYDOWNW
{
    /**
     * NMHDR structure that contains information about the notification message.
     */
    NMHDR      nmhdr;
    /**
     * Virtual key code that represents the key that the user pressed.
     */
    int        nVirtKey;  // virtual key code of WM_KEYDOWN which MODIFIES an X field
    /**
     * Pointer to a null-terminated substring, taken from the format string, that defines the callback
     * field.
     */
    LPCWSTR    pszFormat; // format substring
    /**
     * SYSTEMTIME structure containing the current date and time from the DTP control. The owner of the
     * control must modify the time information based on the user's keystroke.
     */
    SYSTEMTIME st;        // current systemtime, app should modify based on key
} NMDATETIMEWMKEYDOWNW, FAR * LPNMDATETIMEWMKEYDOWNW;

#ifdef UNICODE
/**
 * This message is sent by a date and time picker (DTP) control when the user types in a callback
 * field. It is sent in the form of a WM_NOTIFY message.
 *
 * @param lpDTKeystroke Long pointer to an NMDATETIMEWMKEYDOWN structure that contains information
 *   about this instance of the notification. The structure includes information about the key that
 *   the user typed, the substring that defines the callback field, and the current system date and
 *   time.
 *
 * @return The owner of the control must return zero.
 *
 * Handling this message allows the owner of the control to provide specific responses to keystrokes
 * within the callback fields of the control.
 */
#define DTN_WMKEYDOWN           DTN_WMKEYDOWNW
#define NMDATETIMEWMKEYDOWN     NMDATETIMEWMKEYDOWNW
#define LPNMDATETIMEWMKEYDOWN   LPNMDATETIMEWMKEYDOWNW
#else
/**
 * This message is sent by a date and time picker (DTP) control when the user types in a callback
 * field. It is sent in the form of a WM_NOTIFY message.
 *
 * @param lpDTKeystroke Long pointer to an NMDATETIMEWMKEYDOWN structure that contains information
 *   about this instance of the notification. The structure includes information about the key that
 *   the user typed, the substring that defines the callback field, and the current system date and
 *   time.
 *
 * @return The owner of the control must return zero.
 *
 * Handling this message allows the owner of the control to provide specific responses to keystrokes
 * within the callback fields of the control.
 */
#define DTN_WMKEYDOWN           DTN_WMKEYDOWNA
#define NMDATETIMEWMKEYDOWN     NMDATETIMEWMKEYDOWNA
#define LPNMDATETIMEWMKEYDOWN   LPNMDATETIMEWMKEYDOWNA
#endif


#define DTN_FORMATA  (DTN_FIRST + 4) // query display for app format field (X)
#define DTN_FORMATW  (DTN_FIRST + 17)
/**
 * This structure is used with the DTN_FORMAT notification message.
 *
 * The NMDATETIMEFORMAT structure contains information about a portion of the format string that
 * defines a callback field within a date and time picker (DTP) control. It carries the substring
 * that defines the callback field and contains a buffer to receive the string that will be
 * displayed in the callback field.
 */
typedef struct tagNMDATETIMEFORMATA
{
    /**
     * NMHDR structure that contains information about the notification message.
     */
    NMHDR nmhdr;
    /**
     * Pointer to the null-terminated substring that defines a DTP control callback field The substring
     * comprises one or more "X" characters, followed by a NULL character. For additional information
     * about callback fields, see Callback Fields.
     */
    LPCSTR  pszFormat;   // format substring
    /**
     * SYSTEMTIME structure that contains information about the current system date and time.
     */
    SYSTEMTIME st;       // current systemtime
    /**
     * Pointer to a null-terminated string. By default, this pointer is set to point at szDisplay by the
     * DTP control.
     *
     * It is legal to set this member to point at an existing string. If so, the application is not
     * required to place a string into the szDisplay member.
     */
    LPCSTR pszDisplay;   // string to display
    /**
     * Specifies the 64-character buffer that is to receive the null-terminated string that the DTP
     * control will display. It is not necessary that the application fill the entire buffer.
     */
    CHAR szDisplay[64];  // buffer pszDisplay originally points at
} NMDATETIMEFORMATA, FAR * LPNMDATETIMEFORMATA;

/**
 * This structure is used with the DTN_FORMAT notification message.
 *
 * The NMDATETIMEFORMAT structure contains information about a portion of the format string that
 * defines a callback field within a date and time picker (DTP) control. It carries the substring
 * that defines the callback field and contains a buffer to receive the string that will be
 * displayed in the callback field.
 */
typedef struct tagNMDATETIMEFORMATW
{
    /**
     * NMHDR structure that contains information about the notification message.
     */
    NMHDR nmhdr;
    /**
     * Pointer to the null-terminated substring that defines a DTP control callback field The substring
     * comprises one or more "X" characters, followed by a NULL character. For additional information
     * about callback fields, see Callback Fields.
     */
    LPCWSTR pszFormat;   // format substring
    /**
     * SYSTEMTIME structure that contains information about the current system date and time.
     */
    SYSTEMTIME st;       // current systemtime
    /**
     * Pointer to a null-terminated string. By default, this pointer is set to point at szDisplay by the
     * DTP control.
     *
     * It is legal to set this member to point at an existing string. If so, the application is not
     * required to place a string into the szDisplay member.
     */
    LPCWSTR pszDisplay;  // string to display
    /**
     * Specifies the 64-character buffer that is to receive the null-terminated string that the DTP
     * control will display. It is not necessary that the application fill the entire buffer.
     */
    WCHAR szDisplay[64]; // buffer pszDisplay originally points at
} NMDATETIMEFORMATW, FAR * LPNMDATETIMEFORMATW;

#ifdef UNICODE
/**
 * This notification message is sent by a date and time picker (DTP) control to request text to be
 * displayed in a callback field. It is sent in the form of a WM_NOTIFY message.
 *
 * @param lpNMFormat Long pointer to an NMDATETIMEFORMAT structure that contains information
 *   regarding this instance of the notification message. The structure contains the substring that
 *   defines the callback field and receives the formatted string that the control will display.
 *
 * @return The owner of the control must return zero.
 *
 * Handling this message allows the owner of the control to provide a custom string that the control
 * will display. For additional information about callback fields, see Callback Fields.
 */
#define DTN_FORMAT             DTN_FORMATW
#define NMDATETIMEFORMAT        NMDATETIMEFORMATW
#define LPNMDATETIMEFORMAT      LPNMDATETIMEFORMATW
#else
/**
 * This notification message is sent by a date and time picker (DTP) control to request text to be
 * displayed in a callback field. It is sent in the form of a WM_NOTIFY message.
 *
 * @param lpNMFormat Long pointer to an NMDATETIMEFORMAT structure that contains information
 *   regarding this instance of the notification message. The structure contains the substring that
 *   defines the callback field and receives the formatted string that the control will display.
 *
 * @return The owner of the control must return zero.
 *
 * Handling this message allows the owner of the control to provide a custom string that the control
 * will display. For additional information about callback fields, see Callback Fields.
 */
#define DTN_FORMAT             DTN_FORMATA
#define NMDATETIMEFORMAT        NMDATETIMEFORMATA
#define LPNMDATETIMEFORMAT      LPNMDATETIMEFORMATA
#endif


#define DTN_FORMATQUERYA  (DTN_FIRST + 5) // query formatting info for app format field (X)
#define DTN_FORMATQUERYW (DTN_FIRST + 18)
/**
 * This structure is used with the DTN_FORMATQUERY notification message.
 *
 * The NMDATETIMEFORMATQUERY structure contains information about a date and time picker (DTP)
 * control callback field. It contains a substring (taken from the control's format string) that
 * defines a callback field. The structure receives the maximum allowable size of the text that will
 * be displayed in the callback field.
 */
typedef struct tagNMDATETIMEFORMATQUERYA
{
    /**
     * NMHDR structure that contains information about this notification message.
     */
    NMHDR nmhdr;
    /**
     * Pointer to a null-terminated substring that defines a DTP control callback field. The substring
     * is one or more "X" characters followed by a NULL. For additional information about callback
     * fields, see Callback Fields.
     */
    LPCSTR pszFormat;  // format substring
    /**
     * SIZE structure that must be filled with the maximum size of the text to be displayed in the
     * callback field.
     */
    SIZE szMax;        // max bounding rectangle app will use for this format string
} NMDATETIMEFORMATQUERYA, FAR * LPNMDATETIMEFORMATQUERYA;

/**
 * This structure is used with the DTN_FORMATQUERY notification message.
 *
 * The NMDATETIMEFORMATQUERY structure contains information about a date and time picker (DTP)
 * control callback field. It contains a substring (taken from the control's format string) that
 * defines a callback field. The structure receives the maximum allowable size of the text that will
 * be displayed in the callback field.
 */
typedef struct tagNMDATETIMEFORMATQUERYW
{
    /**
     * NMHDR structure that contains information about this notification message.
     */
    NMHDR nmhdr;
    /**
     * Pointer to a null-terminated substring that defines a DTP control callback field. The substring
     * is one or more "X" characters followed by a NULL. For additional information about callback
     * fields, see Callback Fields.
     */
    LPCWSTR pszFormat; // format substring
    /**
     * SIZE structure that must be filled with the maximum size of the text to be displayed in the
     * callback field.
     */
    SIZE szMax;        // max bounding rectangle app will use for this format string
} NMDATETIMEFORMATQUERYW, FAR * LPNMDATETIMEFORMATQUERYW;

#ifdef UNICODE
/**
 * This notification message is sent by a date and time picker (DTP) control to retrieve the maximum
 * allowable size of the string that will be displayed in callback field. It is sent in the form of
 * a WM_NOTIFY message.
 *
 * @param lpDTFormatQuery Long pointer to an NMDATETIMEFORMATQUERY structure that contains
 *   information about the callback field. The structure contains a substring that defines a callback
 *   field and receives the maximum allowable size of the of string that will be displayed in the
 *   callback field.
 *
 * The owner of the control must calculate the maximum possible width of the text that will be
 * displayed in the callback field, set the szMax member of the NMDATETIMEFORMATQUERY structure, and
 * return zero.
 *
 * Handling this message prepares the control to adjust for the maximum size of the string that will
 * be displayed in a particular callback field. This enables the control to properly display output
 * at all times, reducing flicker within the control's display. For additional information about
 * callback fields, see Callback Fields.
 */
#define DTN_FORMATQUERY         DTN_FORMATQUERYW
#define NMDATETIMEFORMATQUERY   NMDATETIMEFORMATQUERYW
#define LPNMDATETIMEFORMATQUERY LPNMDATETIMEFORMATQUERYW
#else
/**
 * This notification message is sent by a date and time picker (DTP) control to retrieve the maximum
 * allowable size of the string that will be displayed in callback field. It is sent in the form of
 * a WM_NOTIFY message.
 *
 * @param lpDTFormatQuery Long pointer to an NMDATETIMEFORMATQUERY structure that contains
 *   information about the callback field. The structure contains a substring that defines a callback
 *   field and receives the maximum allowable size of the of string that will be displayed in the
 *   callback field.
 *
 * The owner of the control must calculate the maximum possible width of the text that will be
 * displayed in the callback field, set the szMax member of the NMDATETIMEFORMATQUERY structure, and
 * return zero.
 *
 * Handling this message prepares the control to adjust for the maximum size of the string that will
 * be displayed in a particular callback field. This enables the control to properly display output
 * at all times, reducing flicker within the control's display. For additional information about
 * callback fields, see Callback Fields.
 */
#define DTN_FORMATQUERY         DTN_FORMATQUERYA
#define NMDATETIMEFORMATQUERY   NMDATETIMEFORMATQUERYA
#define LPNMDATETIMEFORMATQUERY LPNMDATETIMEFORMATQUERYA
#endif


/**
 * This notification message is sent by a date and time picker (DTP) control when the user activates
 * the drop-down month calendar.
 *
 * @param lpNmhdr Long pointer to an NMHDR structure that contains information about the
 *   notification message.
 *
 * @return The return value for this notification is not used.
 *
 * DTP controls do not maintain a static child month calendar control. The DTP control creates a new
 * month calendar control before sending this notification message. Additionally, the DTP control
 * destroys the child control when it is not active (visible). Therefore, your application must not
 * rely on a static window handle for the control's child month calendar.
 */
#define DTN_DROPDOWN    (DTN_FIRST + 6) // MonthCal has dropped down
/**
 * This notification message is sent by a date and time picker (DTP) control when the user closes
 * the drop-down month calendar. The month calendar is closed when the user chooses a date from the
 * month calendar or clicks the drop-down arrow while the calendar is open.
 *
 * @param lpNmhdr Long pointer to an NMHDR structure that contains information about the
 *   notification message.
 *
 * @return The return value for this notification is not used.
 *
 * DTP controls do not maintain a static child month calendar control. The DTP control destroys the
 * child month calendar control prior to sending this notification. Therefore, your application must
 * not rely on a static window handle for the control's child month calendar.
 */
#define DTN_CLOSEUP     (DTN_FIRST + 7) // MonthCal is popping up


#define GDTR_MIN     0x0001
#define GDTR_MAX     0x0002

#define GDT_ERROR    -1
#define GDT_VALID    0
#define GDT_NONE     1


#endif // _WIN32
#endif // NODATETIMEPICK
#endif      // _WIN32_IE >= 0x0300

#ifdef __cplusplus
}
#endif

#ifndef UNDER_CE
#ifdef _WIN32
#include <poppack.h>
#endif
#endif // !UNDER_CE

#endif

#ifdef WINCEOEM // UNDER_CE
#include <pcommctr.h>
#ifndef UNDER_NT
#ifdef WINCEMACRO
#include <mcommctr.h>
#endif
#endif // !UNDER_NT
#endif

#endif  // _INC_COMMCTRL
