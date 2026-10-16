/*****************************************************************************\
*                                                                             *
* prsht.h - - Interface for the Windows Property Sheet Pages                  *
*                                                                             *
* Version 1.0                                                                 *
*                                                                             *
* Copyright (c) 1991-1997, Microsoft Corp.      All rights reserved.          *
*                                                                             *
\*****************************************************************************/

#ifndef _PRSHT_H_
#define _PRSHT_H_

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
#define DUMMYUNIONNAME   u
#define DUMMYUNIONNAME2  u2
#define DUMMYUNIONNAME3  u3
#else
#define DUMMYUNIONNAME
#define DUMMYUNIONNAME2
#define DUMMYUNIONNAME3
#endif
#endif // DUMMYUNIONNAME

#ifdef __cplusplus
extern "C" {
#endif


#ifndef SNDMSG
#ifdef __cplusplus
#define SNDMSG ::SendMessage
#else
#define SNDMSG SendMessage
#endif
#endif // ifndef SNDMSG

#define MAXPROPPAGES            100

struct _PSP;
typedef struct _PSP FAR* HPROPSHEETPAGE;

#ifndef MIDL_PASS
struct _PROPSHEETPAGEA;
struct _PROPSHEETPAGEW;
#endif

typedef UINT (CALLBACK FAR * LPFNPSPCALLBACKA)(HWND hwnd, UINT uMsg, struct _PROPSHEETPAGEA FAR *ppsp);
typedef UINT (CALLBACK FAR * LPFNPSPCALLBACKW)(HWND hwnd, UINT uMsg, struct _PROPSHEETPAGEW FAR *ppsp);

#ifdef UNICODE
#define LPFNPSPCALLBACK         LPFNPSPCALLBACKW
#else
#define LPFNPSPCALLBACK         LPFNPSPCALLBACKA
#endif

#define PSP_DEFAULT             0x0000
#define PSP_DLGINDIRECT         0x0001
#define PSP_USEHICON            0x0002
#define PSP_USEICONID           0x0004
#define PSP_USETITLE            0x0008
#define PSP_RTLREADING          0x0010

#define PSP_HASHELP             0x0020
#define PSP_USEREFPARENT        0x0040
#define PSP_USECALLBACK         0x0080
#define PSP_PREMATURE           0x0400


#define PSPCB_RELEASE           1
#define PSPCB_CREATE            2


/**
 * This structure defines a page in a property sheet.
 *
 * When the PropertySheet function creates the page, the dialog box procedure for the page receives
 * a WM_INITDIALOG message. The lParam parameter of this message points to the PROPSHEETPAGE
 * structure used to create the page.
 */
typedef struct _PROPSHEETPAGEA {
        /**
         * Specifies the size, in bytes, of the structure. The size includes any extra application-defined
         * data at the end of the structure.
         */
        DWORD           dwSize;
        /**
         * Specifies a bitmask of flags that enable optional attributes of the property sheet page, and
         * indicate the valid members of the PROPSHEETPAGE structure. This member can be any combination of
         * the following values: Value Description PSP_DEFAULT Uses the default meaning for all structure
         * members. PSP_DLGINDIRECT Creates the page from the dialog box template in memory pointed to by
         * the pResource member. The Win32 PropertySheet function assumes that the template is in writeable
         * memory; a read-only template will cause an exception on some versions of Windows. If this flag is
         * not set, the page loads the dialog box template from the resource identified by the pszTemplate
         * member. PSP_HASHELP Enables the property sheet Help button when this page is active.
         * PSP_USECALLBACK Calls the function specified by pfnCallback when creating or destroying the
         * property sheet page defined by this structure. PSP_HICON Not supported. PSP_PREMATURE The page is
         * created when the property sheet is created. Usually, the page is not created until the first time
         * it is selected. PSP_USEICONID Not supported. PSP__USEREFPARENT Maintains the reference count
         * specified by pcRefParent for the lifetime of the property sheet page created from this structure.
         * PSP_USETITLE Uses pszTitle as the title of the property sheet dialog box instead of the title
         * stored in the dialog box template. PSP_RTLREADING When this page is active, displays the text of
         * pszTitle using right-to-left reading order on Hebrew or Arabic systems.
         */
        DWORD           dwFlags;
        /**
         * Handle to the instance from which to load the dialog box template, icon, or title string
         * resource.
         */
        HINSTANCE       hInstance;
        union {
            /**
             * Pointer to a dialog box template to use to create the page. This member can specify either the
             * resource identifier of the template or the address of a string that specifies the name of the
             * template. If dwFlags includes the PSP_DLGINDIRECT value, this member is ignored.
             */
            LPCSTR          pszTemplate;
#ifdef _WIN32
            /**
             * Pointer to a dialog box template in memory. The Win32 PropertySheet function assumes that the
             * template is in writeable memory; a read-only template will cause an exception on some versions of
             * Windows. If dwFlags does not include the PSP_DLGINDIRECT value, this member is ignored.
             */
            LPCDLGTEMPLATE  pResource;
#else
            const VOID FAR *pResource;
#endif
        } DUMMYUNIONNAME;
        union {
            /**
             * Ignored. Must be NULL.
             */
            HICON       hIcon;
            /**
             * Ignored. Must be NULL.
             */
            LPCSTR      pszIcon;
        } DUMMYUNIONNAME2;
        /**
         * Pointer to the null-terminated string that contains the title of the property sheet dialog box.
         * This title overrides the title specified in the dialog box template. This member can specify
         * either the identifier of a string resource or the pointer to a string that specifies the title.
         * If dwFlags does not include the PSP_USETITLE value, this member is ignored.
         */
        LPCSTR          pszTitle;
        /**
         * Pointer to the dialog box procedure for the page. The dialog box procedure must not call the
         * Win32 EndDialog function.
         */
        DLGPROC         pfnDlgProc;
        /**
         * Application-defined data.
         */
        LPARAM          lParam;
        /**
         * Pointer to an application-defined callback function that is called when the page is created and
         * when it is about to be destroyed. For more information about the Win32 callback function, see
         * PropSheetPageProc. If dwFlags does not include the PSP_USECALLBACK value, this member is ignored.
         */
        LPFNPSPCALLBACKA pfnCallback;
        /**
         * Pointer to the reference count value. If dwFlags does not include the PSP_USERREFPARENT value,
         * this member is ignored.
         */
        UINT FAR * pcRefParent;
} PROPSHEETPAGEA, FAR *LPPROPSHEETPAGEA;
typedef const PROPSHEETPAGEA FAR *LPCPROPSHEETPAGEA;

/**
 * This structure defines a page in a property sheet.
 *
 * When the PropertySheet function creates the page, the dialog box procedure for the page receives
 * a WM_INITDIALOG message. The lParam parameter of this message points to the PROPSHEETPAGE
 * structure used to create the page.
 */
typedef struct _PROPSHEETPAGEW {
        /**
         * Specifies the size, in bytes, of the structure. The size includes any extra application-defined
         * data at the end of the structure.
         */
        DWORD           dwSize;
        /**
         * Specifies a bitmask of flags that enable optional attributes of the property sheet page, and
         * indicate the valid members of the PROPSHEETPAGE structure. This member can be any combination of
         * the following values: Value Description PSP_DEFAULT Uses the default meaning for all structure
         * members. PSP_DLGINDIRECT Creates the page from the dialog box template in memory pointed to by
         * the pResource member. The Win32 PropertySheet function assumes that the template is in writeable
         * memory; a read-only template will cause an exception on some versions of Windows. If this flag is
         * not set, the page loads the dialog box template from the resource identified by the pszTemplate
         * member. PSP_HASHELP Enables the property sheet Help button when this page is active.
         * PSP_USECALLBACK Calls the function specified by pfnCallback when creating or destroying the
         * property sheet page defined by this structure. PSP_HICON Not supported. PSP_PREMATURE The page is
         * created when the property sheet is created. Usually, the page is not created until the first time
         * it is selected. PSP_USEICONID Not supported. PSP__USEREFPARENT Maintains the reference count
         * specified by pcRefParent for the lifetime of the property sheet page created from this structure.
         * PSP_USETITLE Uses pszTitle as the title of the property sheet dialog box instead of the title
         * stored in the dialog box template. PSP_RTLREADING When this page is active, displays the text of
         * pszTitle using right-to-left reading order on Hebrew or Arabic systems.
         */
        DWORD           dwFlags;
        /**
         * Handle to the instance from which to load the dialog box template, icon, or title string
         * resource.
         */
        HINSTANCE       hInstance;
        union {
            /**
             * Pointer to a dialog box template to use to create the page. This member can specify either the
             * resource identifier of the template or the address of a string that specifies the name of the
             * template. If dwFlags includes the PSP_DLGINDIRECT value, this member is ignored.
             */
            LPCWSTR          pszTemplate;
#ifdef _WIN32
            /**
             * Pointer to a dialog box template in memory. The Win32 PropertySheet function assumes that the
             * template is in writeable memory; a read-only template will cause an exception on some versions of
             * Windows. If dwFlags does not include the PSP_DLGINDIRECT value, this member is ignored.
             */
            LPCDLGTEMPLATE  pResource;
#else
            const VOID FAR *pResource;
#endif
        }DUMMYUNIONNAME;
        union {
            /**
             * Ignored. Must be NULL.
             */
            HICON       hIcon;
            /**
             * Ignored. Must be NULL.
             */
            LPCWSTR      pszIcon;
        }DUMMYUNIONNAME2;
        /**
         * Pointer to the null-terminated string that contains the title of the property sheet dialog box.
         * This title overrides the title specified in the dialog box template. This member can specify
         * either the identifier of a string resource or the pointer to a string that specifies the title.
         * If dwFlags does not include the PSP_USETITLE value, this member is ignored.
         */
        LPCWSTR          pszTitle;
        /**
         * Pointer to the dialog box procedure for the page. The dialog box procedure must not call the
         * Win32 EndDialog function.
         */
        DLGPROC         pfnDlgProc;
        /**
         * Application-defined data.
         */
        LPARAM          lParam;
        /**
         * Pointer to an application-defined callback function that is called when the page is created and
         * when it is about to be destroyed. For more information about the Win32 callback function, see
         * PropSheetPageProc. If dwFlags does not include the PSP_USECALLBACK value, this member is ignored.
         */
        LPFNPSPCALLBACKW pfnCallback;
        /**
         * Pointer to the reference count value. If dwFlags does not include the PSP_USERREFPARENT value,
         * this member is ignored.
         */
        UINT FAR * pcRefParent;
} PROPSHEETPAGEW, FAR *LPPROPSHEETPAGEW;
typedef const PROPSHEETPAGEW FAR *LPCPROPSHEETPAGEW;

#ifdef UNICODE
#define PROPSHEETPAGE           PROPSHEETPAGEW
#define LPPROPSHEETPAGE         LPPROPSHEETPAGEW
#define LPCPROPSHEETPAGE        LPCPROPSHEETPAGEW
#else
#define PROPSHEETPAGE           PROPSHEETPAGEA
#define LPPROPSHEETPAGE         LPPROPSHEETPAGEA
#define LPCPROPSHEETPAGE        LPCPROPSHEETPAGEA
#endif


#define PSH_DEFAULT             0x0000
#define PSH_PROPTITLE           0x0001
#define PSH_USEHICON            0x0002
#define PSH_USEICONID           0x0004
#define PSH_PROPSHEETPAGE       0x0008
#define PSH_WIZARDHASFINISH     0x0010
#define PSH_WIZARD              0x0020
#define PSH_USEPSTARTPAGE       0x0040
#define PSH_NOAPPLYNOW          0x0080
#define PSH_USECALLBACK         0x0100
#define PSH_HASHELP             0x0200
#define PSH_MODELESS            0x0400
#define PSH_RTLREADING          0x0800
#define PSH_WIZARDCONTEXTHELP   0x1000

typedef int (CALLBACK *PFNPROPSHEETCALLBACK)(HWND, UINT, LPARAM);

/**
 * This structure defines the frame and pages of a property sheet.
 */
typedef struct _PROPSHEETHEADERA {
        /**
         * Specifies the size, in bytes, of this structure.
         */
        DWORD           dwSize;
        /**
         * Specifies a bitmask of flags that indicate which options to use when creating the property sheet
         * page. It can be a combination of the following values: Value Description PSH_DEFAULT Uses the
         * default meaning for all structure members. PSH_HASHELP Displays the property sheet Help button.
         * The Help button is enabled only when the PSP_HASHELP flag is set in the PROPSHEETAPGE structure
         * for the active page. If any of the initial property sheet pages set the PSP_HASHELP flag, the
         * Help button is automatically displayed regardless of the PSH_HASHELP flag. However, PSH_HASHELP
         * is useful when none of the initial pages set PSP_HASHELP, but pages added later might. PSH_HEADER
         * Version 4.71. Indicates that a header bitmap will be used. If this value does not include
         * PSH_USEHBMHEADER, the header bitmap is obtained from pszbmHeader. If this value includes
         * PSH_USEHBMHEADER, the header bitmap is obtained from hbmHeader. This flag is ignored if
         * PSH_WIZARD97 is not included. PSH_MODELESS Causes the PropertySheet function to create the
         * property sheet as a modeless dialog instead of as a modal dialog. When this flag is set,
         * PropertySheet returns immediately after the dialog is created, and the return value from
         * PropertySheet is the window handle to the property sheet dialog. PSH_NOAPPLYNOW Removes the Apply
         * Now button. PSH_PROPSHEETPAGE Uses ppsp and ignores phpage when creating the pages for the
         * property sheet. PSH_PROPTITLE Displays the string "Properties for", followed by the string
         * specified by pszCaption, in the title bar of the property sheet. PSH_RTLREADING Displays the
         * title of the property sheet dialog using right-to-left reading order on Hebrew or Arabic systems.
         * PSH_STRETCHWATERMARK Version 4.71. Stretches the bitmap to fit the background of the property
         * sheet instead of tiling the watermark and/or header bitmap. This flag is ignored if PSH_WIZARD97
         * and PSH_WATERMARK or PSH_HEADER are not included. PSH_USECALLBACK Calls the function specified by
         * pfnCallback when initializing the property sheet defined by this structure. PSH_USEHBMHEADER
         * Version 4.71. Obtains the header bitmap from hbmHeader instead of pszbmHeader. This flag is
         * ignored if PSH_WIZARD97 and PSH_HEADER are not included. PSH_USEHBMWATERMARK Version 4.71.
         * Obtains the watermark bitmap from hbmWatermark instead of pszbmWatermark. This flag is ignored if
         * PSH_WIZARD97 and PSH_WATERMARK are not included. PSH_USEHICON Not supported. PSH_USEHPLWATERMARK
         * Version 4.71. Obtains the HPALETTE for drawing the watermark bitmap and/or header bitmap from
         * hplWatermark instead of using the default palette. This flag is ignored if PSH_WIZARD97 and
         * PSH_WATERMARK or PSH_HEADER are not included. PSH_USEICONID Not supported. PSH_USEPAGELANG
         * Version 4.71. The language for the property sheet will be taken from the first page's resource.
         * PSH_USEPSTARTPAGE Uses pStartPage and ignores nStartPage when displaying the initial page of the
         * property sheet. PSH_WATERMARK Version 4.71. Specifies that a watermark bitmap will be used. If
         * this value does not include PSH_USEHBMWATERMARK, the watermark bitmap is obtained from
         * pszbmWatermark. If this value includes PSH_USEHBMWATERMARK, the header bitmap is obtained from
         * hbmWatermark. This flag is ignored if PSH_WIZARD97 is not included. PSH_WIZARD Creates a wizard
         * property sheet. PSH_WIZARD97 Creates a wizard property sheet that allows a header and/or
         * watermark bitmap to be displayed in the background. This and all Wizard 97-associated flags are
         * not currently implemented. PSH_WIZARDCONTEXTHELP Adds a system menu to the wizard property sheet.
         * This flag is ignored if PSH_WIZARD or PSH_WIZARD97 is not included. PSH_WIZARDHASFINISH Always
         * displays the Finish button on the wizard. This flag is ignored if PSH_WIZARD or PSH_WIZARD97 is
         * not included.
         */
        DWORD           dwFlags;
        /**
         * Handle to the property sheet's owner window.
         */
        HWND            hwndParent;
        /**
         * Handle to the instance from which to load the icon or title string resource. If pszIcon or
         * pszCaption identifies a resource to load, this member must be specified.
         */
        HINSTANCE       hInstance;
        union {
            /**
             * Handle to the icon to use as the small icon in the title bar of the property sheet dialog box. If
             * dwFlags does not include PSH_USEHICON, this member is ignored.
             */
            HICON       hIcon;
            /**
             * Pointer to an icon resource to use as the small icon in the title bar of the property sheet
             * dialog box. This member can specify either the identifier of the icon resource or the address of
             * the string that specifies the name of the icon resource. If dwFlags does not include
             * PSH_USEICONID, this member is ignored.
             */
            LPCSTR      pszIcon;
        }DUMMYUNIONNAME;
        /**
         * Pointer to the null-terminated string that contains the title of the property sheet dialog box.
         * This member can specify either the identifier of a string resource or the address of a string
         * that specifies the title. If dwFlags includes PSH_PROPTITLE, the string "Properties for" is
         * inserted at the beginning of the title.
         */
        LPCSTR          pszCaption;


        /**
         * Number of elements in the phpage array.
         */
        UINT            nPages;
        union {
            /**
             * Zero-based index of the initial page that appears when the property sheet dialog box is created.
             */
            UINT        nStartPage;
            /**
             * Pointer to the name of the initial page that appears when the property sheet dialog box is
             * created. This member can specify either the identifier of a string resource or the address of a
             * string that specifies the name.
             */
            LPCSTR      pStartPage;
        }DUMMYUNIONNAME2;
        union {
            /**
             * Pointer to an array of PROPSHEETPAGE structures that define the pages in the property sheet. If
             * dwFlags does not include PSH_PROPSHEETPAGE, this member is ignored.
             */
            LPCPROPSHEETPAGEA ppsp;
            /**
             * Pointer to an array of handles to the property sheet pages. Each handle must have been created by
             * a previous call to the CreatePropertySheetPage function. If dwFlags includes PSH_PROPSHEETPAGE,
             * this member is ignored.
             */
            HPROPSHEETPAGE FAR *phpage;
        }DUMMYUNIONNAME3;
        /**
         * Pointer to an application-defined callback function that is called when the property sheet is
         * initialized. For more information about the callback function, see the description of the
         * PropSheetProc function. If dwFlags does not include PSH_USECALLBACK, this member is ignored.
         */
        PFNPROPSHEETCALLBACK pfnCallback;
} PROPSHEETHEADERA, FAR *LPPROPSHEETHEADERA;
typedef const PROPSHEETHEADERA FAR *LPCPROPSHEETHEADERA;

/**
 * This structure defines the frame and pages of a property sheet.
 */
typedef struct _PROPSHEETHEADERW {
        /**
         * Specifies the size, in bytes, of this structure.
         */
        DWORD           dwSize;
        /**
         * Specifies a bitmask of flags that indicate which options to use when creating the property sheet
         * page. It can be a combination of the following values: Value Description PSH_DEFAULT Uses the
         * default meaning for all structure members. PSH_HASHELP Displays the property sheet Help button.
         * The Help button is enabled only when the PSP_HASHELP flag is set in the PROPSHEETAPGE structure
         * for the active page. If any of the initial property sheet pages set the PSP_HASHELP flag, the
         * Help button is automatically displayed regardless of the PSH_HASHELP flag. However, PSH_HASHELP
         * is useful when none of the initial pages set PSP_HASHELP, but pages added later might. PSH_HEADER
         * Version 4.71. Indicates that a header bitmap will be used. If this value does not include
         * PSH_USEHBMHEADER, the header bitmap is obtained from pszbmHeader. If this value includes
         * PSH_USEHBMHEADER, the header bitmap is obtained from hbmHeader. This flag is ignored if
         * PSH_WIZARD97 is not included. PSH_MODELESS Causes the PropertySheet function to create the
         * property sheet as a modeless dialog instead of as a modal dialog. When this flag is set,
         * PropertySheet returns immediately after the dialog is created, and the return value from
         * PropertySheet is the window handle to the property sheet dialog. PSH_NOAPPLYNOW Removes the Apply
         * Now button. PSH_PROPSHEETPAGE Uses ppsp and ignores phpage when creating the pages for the
         * property sheet. PSH_PROPTITLE Displays the string "Properties for", followed by the string
         * specified by pszCaption, in the title bar of the property sheet. PSH_RTLREADING Displays the
         * title of the property sheet dialog using right-to-left reading order on Hebrew or Arabic systems.
         * PSH_STRETCHWATERMARK Version 4.71. Stretches the bitmap to fit the background of the property
         * sheet instead of tiling the watermark and/or header bitmap. This flag is ignored if PSH_WIZARD97
         * and PSH_WATERMARK or PSH_HEADER are not included. PSH_USECALLBACK Calls the function specified by
         * pfnCallback when initializing the property sheet defined by this structure. PSH_USEHBMHEADER
         * Version 4.71. Obtains the header bitmap from hbmHeader instead of pszbmHeader. This flag is
         * ignored if PSH_WIZARD97 and PSH_HEADER are not included. PSH_USEHBMWATERMARK Version 4.71.
         * Obtains the watermark bitmap from hbmWatermark instead of pszbmWatermark. This flag is ignored if
         * PSH_WIZARD97 and PSH_WATERMARK are not included. PSH_USEHICON Not supported. PSH_USEHPLWATERMARK
         * Version 4.71. Obtains the HPALETTE for drawing the watermark bitmap and/or header bitmap from
         * hplWatermark instead of using the default palette. This flag is ignored if PSH_WIZARD97 and
         * PSH_WATERMARK or PSH_HEADER are not included. PSH_USEICONID Not supported. PSH_USEPAGELANG
         * Version 4.71. The language for the property sheet will be taken from the first page's resource.
         * PSH_USEPSTARTPAGE Uses pStartPage and ignores nStartPage when displaying the initial page of the
         * property sheet. PSH_WATERMARK Version 4.71. Specifies that a watermark bitmap will be used. If
         * this value does not include PSH_USEHBMWATERMARK, the watermark bitmap is obtained from
         * pszbmWatermark. If this value includes PSH_USEHBMWATERMARK, the header bitmap is obtained from
         * hbmWatermark. This flag is ignored if PSH_WIZARD97 is not included. PSH_WIZARD Creates a wizard
         * property sheet. PSH_WIZARD97 Creates a wizard property sheet that allows a header and/or
         * watermark bitmap to be displayed in the background. This and all Wizard 97-associated flags are
         * not currently implemented. PSH_WIZARDCONTEXTHELP Adds a system menu to the wizard property sheet.
         * This flag is ignored if PSH_WIZARD or PSH_WIZARD97 is not included. PSH_WIZARDHASFINISH Always
         * displays the Finish button on the wizard. This flag is ignored if PSH_WIZARD or PSH_WIZARD97 is
         * not included.
         */
        DWORD           dwFlags;
        /**
         * Handle to the property sheet's owner window.
         */
        HWND            hwndParent;
        /**
         * Handle to the instance from which to load the icon or title string resource. If pszIcon or
         * pszCaption identifies a resource to load, this member must be specified.
         */
        HINSTANCE       hInstance;
        union {
            /**
             * Handle to the icon to use as the small icon in the title bar of the property sheet dialog box. If
             * dwFlags does not include PSH_USEHICON, this member is ignored.
             */
            HICON       hIcon;
            /**
             * Pointer to an icon resource to use as the small icon in the title bar of the property sheet
             * dialog box. This member can specify either the identifier of the icon resource or the address of
             * the string that specifies the name of the icon resource. If dwFlags does not include
             * PSH_USEICONID, this member is ignored.
             */
            LPCWSTR     pszIcon;
        }DUMMYUNIONNAME;
        /**
         * Pointer to the null-terminated string that contains the title of the property sheet dialog box.
         * This member can specify either the identifier of a string resource or the address of a string
         * that specifies the title. If dwFlags includes PSH_PROPTITLE, the string "Properties for" is
         * inserted at the beginning of the title.
         */
        LPCWSTR         pszCaption;


        /**
         * Number of elements in the phpage array.
         */
        UINT            nPages;
        union {
            /**
             * Zero-based index of the initial page that appears when the property sheet dialog box is created.
             */
            UINT        nStartPage;
            /**
             * Pointer to the name of the initial page that appears when the property sheet dialog box is
             * created. This member can specify either the identifier of a string resource or the address of a
             * string that specifies the name.
             */
            LPCWSTR     pStartPage;
        }DUMMYUNIONNAME2;
        union {
            /**
             * Pointer to an array of PROPSHEETPAGE structures that define the pages in the property sheet. If
             * dwFlags does not include PSH_PROPSHEETPAGE, this member is ignored.
             */
            LPCPROPSHEETPAGEW ppsp;
            /**
             * Pointer to an array of handles to the property sheet pages. Each handle must have been created by
             * a previous call to the CreatePropertySheetPage function. If dwFlags includes PSH_PROPSHEETPAGE,
             * this member is ignored.
             */
            HPROPSHEETPAGE FAR *phpage;
        }DUMMYUNIONNAME3;
        /**
         * Pointer to an application-defined callback function that is called when the property sheet is
         * initialized. For more information about the callback function, see the description of the
         * PropSheetProc function. If dwFlags does not include PSH_USECALLBACK, this member is ignored.
         */
        PFNPROPSHEETCALLBACK pfnCallback;
} PROPSHEETHEADERW, FAR *LPPROPSHEETHEADERW;
typedef const PROPSHEETHEADERW FAR *LPCPROPSHEETHEADERW;

#ifdef UNICODE
#define PROPSHEETHEADER         PROPSHEETHEADERW
#define LPPROPSHEETHEADER       LPPROPSHEETHEADERW
#define LPCPROPSHEETHEADER      LPCPROPSHEETHEADERW
#else
#define PROPSHEETHEADER         PROPSHEETHEADERA
#define LPPROPSHEETHEADER       LPPROPSHEETHEADERA
#define LPCPROPSHEETHEADER      LPCPROPSHEETHEADERA
#endif


#define PSCB_INITIALIZED  1
#define PSCB_PRECREATE    2

/**
 * This function creates a new page for a property sheet.
 *
 * @param lppsp [in] Long pointer to a PROPSHEETPAGE structure that defines a page to be included in
 *   a property sheet.
 *
 * @return The handle to the new property sheet indicates success. NULL indicates failure.
 *
 * An application uses the PropertySheet function to create a property sheet that includes the new
 * page, or it uses the PSM_ADDPAGE message to add the new page to an existing property sheet.
 */
WINCOMMCTRLAPI HPROPSHEETPAGE WINAPI CreatePropertySheetPageA(LPCPROPSHEETPAGEA);
/**
 * This function creates a new page for a property sheet.
 *
 * @param lppsp [in] Long pointer to a PROPSHEETPAGE structure that defines a page to be included in
 *   a property sheet.
 *
 * @return The handle to the new property sheet indicates success. NULL indicates failure.
 *
 * An application uses the PropertySheet function to create a property sheet that includes the new
 * page, or it uses the PSM_ADDPAGE message to add the new page to an existing property sheet.
 */
WINCOMMCTRLAPI HPROPSHEETPAGE WINAPI CreatePropertySheetPageW(LPCPROPSHEETPAGEW);
/**
 * This function destroys a property sheet page for the handle returned from the
 * CreatePropertySheetPage function. An application must call this function for pages that have not
 * been passed to the PropertySheet function.
 *
 * @param hPSPage Handle to the property sheet page to delete.
 *
 * @return Nonzero indicates success. Zero indicates failure.
 */
WINCOMMCTRLAPI BOOL           WINAPI DestroyPropertySheetPage(HPROPSHEETPAGE);
/**
 * This function creates a property sheet and adds the pages defined in the specified property sheet
 * header structure.
 *
 * @param lppsph [in] Long pointer to a PROPSHEETHEADER structure that defines the frame and pages
 *   of a property sheet.
 *
 * @return A positive value indicates success. -1 indicates failure. If the dwFlags member of the
 *   PROPSHEETHEADER structure specifies the PSH_MODELESS flag, the successful return value is the
 *   window handle to the property sheet dialog. The return values described in the following table
 *   have a special meaning. Value Description ID_PSREBOOTSYSTEM A page sent the PSM_REBOOTSYSTEM
 *   message to the property sheet. The computer must be restarted for the user's changes to take
 *   effect. ID_PSRESTARTWINDOWS A page sent the PSM_RESTARTWINDOWS message to the property sheet.
 *   Windows must be restarted for the user's changes to take effect. To get extended error
 *   information, call GetLastError.
 *
 * By default, PropertySheet creates a modal dialog. If the dwFlags member of the PROPSHEETHEADER
 * structure specifies the PSH_MODELESS flag, PropertySheet creates a modeless dialog and returns
 * immediately after the dialog is created. In this case, the PropertySheet return value is the
 * window handle to the modeless dialog.
 *
 * For a modeless property sheet, your message loop should use PSM_ISDIALOGMESSAGE to pass messages
 * to the property sheet dialog. Your message loop should use PSM_GETCURRENTPAGEHWND to determine
 * when to destroy the dialog. When the user chooses the OK or Cancel button, PSM_GETCURRENTPAGEHWND
 * returns NULL, and you can then use the DestroyWindow function to destroy the dialog box.
 */
WINCOMMCTRLAPI int            WINAPI PropertySheetA(LPCPROPSHEETHEADERA);
/**
 * This function creates a property sheet and adds the pages defined in the specified property sheet
 * header structure.
 *
 * @param lppsph [in] Long pointer to a PROPSHEETHEADER structure that defines the frame and pages
 *   of a property sheet.
 *
 * @return A positive value indicates success. -1 indicates failure. If the dwFlags member of the
 *   PROPSHEETHEADER structure specifies the PSH_MODELESS flag, the successful return value is the
 *   window handle to the property sheet dialog. The return values described in the following table
 *   have a special meaning. Value Description ID_PSREBOOTSYSTEM A page sent the PSM_REBOOTSYSTEM
 *   message to the property sheet. The computer must be restarted for the user's changes to take
 *   effect. ID_PSRESTARTWINDOWS A page sent the PSM_RESTARTWINDOWS message to the property sheet.
 *   Windows must be restarted for the user's changes to take effect. To get extended error
 *   information, call GetLastError.
 *
 * By default, PropertySheet creates a modal dialog. If the dwFlags member of the PROPSHEETHEADER
 * structure specifies the PSH_MODELESS flag, PropertySheet creates a modeless dialog and returns
 * immediately after the dialog is created. In this case, the PropertySheet return value is the
 * window handle to the modeless dialog.
 *
 * For a modeless property sheet, your message loop should use PSM_ISDIALOGMESSAGE to pass messages
 * to the property sheet dialog. Your message loop should use PSM_GETCURRENTPAGEHWND to determine
 * when to destroy the dialog. When the user chooses the OK or Cancel button, PSM_GETCURRENTPAGEHWND
 * returns NULL, and you can then use the DestroyWindow function to destroy the dialog box.
 */
WINCOMMCTRLAPI int            WINAPI PropertySheetW(LPCPROPSHEETHEADERW);

#ifdef UNICODE
/**
 * This function creates a new page for a property sheet.
 *
 * @param lppsp [in] Long pointer to a PROPSHEETPAGE structure that defines a page to be included in
 *   a property sheet.
 *
 * @return The handle to the new property sheet indicates success. NULL indicates failure.
 *
 * An application uses the PropertySheet function to create a property sheet that includes the new
 * page, or it uses the PSM_ADDPAGE message to add the new page to an existing property sheet.
 */
#define CreatePropertySheetPage  CreatePropertySheetPageW
/**
 * This function creates a property sheet and adds the pages defined in the specified property sheet
 * header structure.
 *
 * @param lppsph [in] Long pointer to a PROPSHEETHEADER structure that defines the frame and pages
 *   of a property sheet.
 *
 * @return A positive value indicates success. -1 indicates failure. If the dwFlags member of the
 *   PROPSHEETHEADER structure specifies the PSH_MODELESS flag, the successful return value is the
 *   window handle to the property sheet dialog. The return values described in the following table
 *   have a special meaning. Value Description ID_PSREBOOTSYSTEM A page sent the PSM_REBOOTSYSTEM
 *   message to the property sheet. The computer must be restarted for the user's changes to take
 *   effect. ID_PSRESTARTWINDOWS A page sent the PSM_RESTARTWINDOWS message to the property sheet.
 *   Windows must be restarted for the user's changes to take effect. To get extended error
 *   information, call GetLastError.
 *
 * By default, PropertySheet creates a modal dialog. If the dwFlags member of the PROPSHEETHEADER
 * structure specifies the PSH_MODELESS flag, PropertySheet creates a modeless dialog and returns
 * immediately after the dialog is created. In this case, the PropertySheet return value is the
 * window handle to the modeless dialog.
 *
 * For a modeless property sheet, your message loop should use PSM_ISDIALOGMESSAGE to pass messages
 * to the property sheet dialog. Your message loop should use PSM_GETCURRENTPAGEHWND to determine
 * when to destroy the dialog. When the user chooses the OK or Cancel button, PSM_GETCURRENTPAGEHWND
 * returns NULL, and you can then use the DestroyWindow function to destroy the dialog box.
 */
#define PropertySheet            PropertySheetW
#else
/**
 * This function creates a new page for a property sheet.
 *
 * @param lppsp [in] Long pointer to a PROPSHEETPAGE structure that defines a page to be included in
 *   a property sheet.
 *
 * @return The handle to the new property sheet indicates success. NULL indicates failure.
 *
 * An application uses the PropertySheet function to create a property sheet that includes the new
 * page, or it uses the PSM_ADDPAGE message to add the new page to an existing property sheet.
 */
#define CreatePropertySheetPage  CreatePropertySheetPageA
/**
 * This function creates a property sheet and adds the pages defined in the specified property sheet
 * header structure.
 *
 * @param lppsph [in] Long pointer to a PROPSHEETHEADER structure that defines the frame and pages
 *   of a property sheet.
 *
 * @return A positive value indicates success. -1 indicates failure. If the dwFlags member of the
 *   PROPSHEETHEADER structure specifies the PSH_MODELESS flag, the successful return value is the
 *   window handle to the property sheet dialog. The return values described in the following table
 *   have a special meaning. Value Description ID_PSREBOOTSYSTEM A page sent the PSM_REBOOTSYSTEM
 *   message to the property sheet. The computer must be restarted for the user's changes to take
 *   effect. ID_PSRESTARTWINDOWS A page sent the PSM_RESTARTWINDOWS message to the property sheet.
 *   Windows must be restarted for the user's changes to take effect. To get extended error
 *   information, call GetLastError.
 *
 * By default, PropertySheet creates a modal dialog. If the dwFlags member of the PROPSHEETHEADER
 * structure specifies the PSH_MODELESS flag, PropertySheet creates a modeless dialog and returns
 * immediately after the dialog is created. In this case, the PropertySheet return value is the
 * window handle to the modeless dialog.
 *
 * For a modeless property sheet, your message loop should use PSM_ISDIALOGMESSAGE to pass messages
 * to the property sheet dialog. Your message loop should use PSM_GETCURRENTPAGEHWND to determine
 * when to destroy the dialog. When the user chooses the OK or Cancel button, PSM_GETCURRENTPAGEHWND
 * returns NULL, and you can then use the DestroyWindow function to destroy the dialog box.
 */
#define PropertySheet            PropertySheetA
#endif



typedef BOOL (CALLBACK FAR * LPFNADDPROPSHEETPAGE)(HPROPSHEETPAGE, LPARAM);
typedef BOOL (CALLBACK FAR * LPFNADDPROPSHEETPAGES)(LPVOID, LPFNADDPROPSHEETPAGE, LPARAM);


/**
 * This structure contains information for the PSN_APPLY and PSN_RESET notification messages.
 */
typedef struct _PSHNOTIFY
{
    /**
     * NMHDR structure that contains additional information about the notification.
     */
    NMHDR hdr;
    /**
     * Additional information about this notification. See the description of the particular
     * notification message to determine what, if any, information is contained in this member.
     */
    LPARAM lParam;
} PSHNOTIFY, FAR *LPPSHNOTIFY;


#define PSN_FIRST               (0U-200U)
#define PSN_LAST                (0U-299U)


/**
 * This notification message notifies a page that it is about to be activated. It is sent in the
 * form of a WM_NOTIFY message.
 *
 * @param lppsn Long pointer to a PSHNOTIFY structure that contains information about the
 *   notification. The lParam member of this structure does not contain any information. The hwndFrom
 *   member of the hdr member of this structure contains the handle to the property sheet.
 *
 * @return Returns zero to accept the activation, or -1 to activate the next or the previous page
 *   (depending on whether the user clicked the Next or Back button). To set the activation to a
 *   particular page, return the resource identifier of the page.
 *
 * The PSN_SETACTIVE notification message is sent before the page is visible. An application can use
 * this notification to initialize data in the page.
 *
 * To set the return value, the dialog box procedure for the page must use the SetWindowLong
 * function with the DWL_MSGRESULT value, and the dialog box procedure must return TRUE.
 */
#define PSN_SETACTIVE           (PSN_FIRST-0)
/**
 * This notification message notifies a page that it is about to lose the activation either because
 * another page is being activated or the user has chosen the OK button. It is sent in the form of a
 * WM_NOTIFY message.
 *
 * @param lppsn Long pointer to a PSHNOTIFY structure that contains information about the
 *   notification. The lParam member of this structure does not contain any information. The hwndFrom
 *   member of the hdr member of this structure contains the handle to the property sheet.
 *
 * @return TRUE to prevents the page from losing the activation. FALSE allows the page to lose
 *   activation.
 *
 * An application should validate the information the user has typed.
 *
 * To set the return value, the dialog box procedure for the page must use the SetWindowLong
 * function with the DWL_MSGRESULT value, and the dialog box procedure must return TRUE.
 */
#define PSN_KILLACTIVE          (PSN_FIRST-1)
// #define PSN_VALIDATE            (PSN_FIRST-1)
/**
 * This notification message indicates that the user chose the OK or Apply Now button and wants all
 * changes to take effect. It is sent in the form of a WM_NOTIFY message.
 *
 * @param lppsn Long pointer to a PSHNOTIFY structure that contains information about the
 *   notification. The lParam member of this structure does not contain any information. The hwndFrom
 *   member of the hdr member of this structure contains the handle to the property sheet.
 *
 * @return Returns the PSNRET_INVALID_NOCHANGEPAGE value to prevent the changes from taking effect
 *   and to return the focus to the page, or the PSNRET_NOERROR value to accept the changes and allow
 *   the property sheet to be destroyed.
 *
 * To set the return value, the dialog box procedure for the page must use the SetWindowLong
 * function with the DWL_MSGRESULT value, and the dialog box procedure must return TRUE.
 *
 * A page should not call the EndDialog function when processing this notification message.
 *
 * The property sheet is destroyed if the user clicks the OK button and the application returns the
 * PSNRET_NOERROR value in response to this notification.
 *
 * To receive this notification, a page must set the DWL_MSGRESULT value to FALSE in response the
 * PSN_KILLACTIVE notification message.
 */
#define PSN_APPLY               (PSN_FIRST-2)
/**
 * This notification message notifies a page that the user has chosen the Cancel button and the
 * property sheet is about to be destroyed. All changes made since the user last chose the Apply Now
 * button are canceled. It is sent in the form of a WM_NOTIFY message.
 *
 * @param lppsn Long pointer to a PSHNOTIFY structure that contains information about the
 *   notification. If this notification is in response to the Close button being pressed, the lParam
 *   member of this structure will contain a non-zero value. If this notification is in response to
 *   the Cancel button being pressed, the lParam member of this structure will contain zero. The
 *   hwndFrom member of the hdr member of this structure contains the handle to the property sheet.
 *
 * @return None.
 *
 * An application can use this notification message as an opportunity to perform cleanup operations.
 *
 * A page should not call the EndDialog function when processing this notification message.
 */
#define PSN_RESET               (PSN_FIRST-3)
// #define PSN_CANCEL              (PSN_FIRST-3)
/**
 * This notification message notifies a page that the user has chosen the Help button. It is sent in
 * the form of a WM_NOTIFY message.
 *
 * @param lppsn Long pointer to a PSHNOTIFY structure that contains information about the
 *   notification. The lParam member of this structure does not contain any information. The hwndFrom
 *   member of the hdr member of this structure contains the handle to the property sheet.
 *
 * @return None.
 */
#define PSN_HELP                (PSN_FIRST-5)
#define PSN_WIZBACK             (PSN_FIRST-6)
#define PSN_WIZNEXT             (PSN_FIRST-7)
#define PSN_WIZFINISH           (PSN_FIRST-8)
/**
 * This notification message indicates that the user chose the Cancel button. It is sent in the form
 * of a WM_NOTIFY message.
 *
 * @param lppsn Long pointer to a PSHNOTIFY structure that contains information about the
 *   notification. The lParam member of this structure does not contain any information. The i member
 *   of the hdr member of this structure contains the handle to the property sheet.
 *
 * @return TRUE prevents the cancel operation. FALSE allows the cancel operation.
 *
 * A property sheet page can use this notification message to ask the user to verify the cancel
 * operation.
 */
#define PSN_QUERYCANCEL         (PSN_FIRST-9)

#define PSNRET_NOERROR              0
#define PSNRET_INVALID              1
#define PSNRET_INVALID_NOCHANGEPAGE 2


/**
 * This message activates the specified page in a property sheet. You can send this message
 * explicitly or by using the PropSheet_SetCurSel macro.
 *
 * @param index Zero-based index of the page to activate.
 * @param hpage Handle of the page to activate.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * An application can specify the index or the handle, or both. If both are specified, hpage takes
 * precedence.
 */
#define PSM_SETCURSEL           (WM_USER + 101)
/**
 * This macro activates the specified page in a property sheet. You can use this macro or send the
 * PSM_SETCURSEL message explicitly.
 *
 * @param hPropSheetDlg Handle to the property sheet.
 * @param index Zero-based index of the page to activate.
 * @param hpage Handle to the page to activate.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * An application can specify the index or the handle, or both. If both are specified, hpage takes
 * precedence.
 *
 * The window that is losing the activation receives the PSN_KILLACTIVE notification message, and
 * the window that is gaining the activation receives the PSN_SETACTIVE notification message.
 */
#define PropSheet_SetCurSel(hDlg, hpage, index) \
        SNDMSG(hDlg, PSM_SETCURSEL, (WPARAM)index, (LPARAM)hpage)


/**
 * This message removes a page from a property sheet. You can send this message explicitly or by
 * using the PropSheet_RemovePage macro.
 *
 * @param index Zero-based index of the page to remove.
 * @param hpage Handle of the page to remove.
 *
 * @return None.
 *
 * An application can specify the index or the handle, or both. If both are specified, hpage takes
 * precedence.
 */
#define PSM_REMOVEPAGE          (WM_USER + 102)
/**
 * This macro removes a page from a property sheet. You can use this macro or send the
 * PSM_REMOVEPAGE message explicitly.
 *
 * @param hPropSheetDlg Handle to the property sheet.
 * @param index Zero-based index of the page to remove.
 * @param hpage Handle to the page to remove.
 *
 * @return None.
 *
 * An application can specify the index or the handle, or both. If both are specified, hpage takes
 * precedence.
 */
#define PropSheet_RemovePage(hDlg, index, hpage) \
        SNDMSG(hDlg, PSM_REMOVEPAGE, index, (LPARAM)hpage)


/**
 * This message adds a new page to the end of an existing property sheet. You can send this message
 * explicitly or by using the PropSheet_AddPage macro.
 *
 * @param hpage Handle to the page to add. The page must have been created by a previous call to the
 *   CreatePropertySheetPage function.
 *
 * @return None.
 */
#define PSM_ADDPAGE             (WM_USER + 103)
/**
 * This macro adds a new page to the end of an existing property sheet. You can use this macro or
 * send the PSM_ADDPAGE message explicitly.
 *
 * @param hPropSheetDlg Handle to the property sheet.
 * @param hpage Handle to the page to add. The page must have been created by a previous call to the
 *   CreatePropertySheetPage function.
 *
 * @return None.
 *
 * The new page should be no larger than the largest page currently in the property sheet because
 * the property sheet is not resized to fit the new page.
 */
#define PropSheet_AddPage(hDlg, hpage) \
        SNDMSG(hDlg, PSM_ADDPAGE, 0, (LPARAM)hpage)


/**
 * This message informs a property sheet that information in a page has changed. The property sheet
 * enables the Apply Now button. You can send this message explicitly or by using the
 * PropSheet_Changed macro.
 *
 * @param hwndPage Handle to the page that has changed.
 *
 * @return None.
 */
#define PSM_CHANGED             (WM_USER + 104)
/**
 * This macro informs a property sheet that information in a page has changed. The property sheet
 * enables the Apply Now button. You can use this macro or send the PSM_CHANGED message explicitly.
 *
 * @param hPropSheetDlg Handle to the property sheet.
 * @param hwndPage Handle to the page that has changed.
 *
 * @return None.
 */
#define PropSheet_Changed(hDlg, hwnd) \
        SNDMSG(hDlg, PSM_CHANGED, (WPARAM)hwnd, 0L)


/**
 * This message indicates that Windows needs to be restarted for the changes to take effect. An
 * application should send this message only in response to the PSN_APPLY or PSN_KILLACTIVE
 * notification message. You can send the PSM_RESTARTWINDOWS message explicitly or by using the
 * PropSheet_RestartWindows macro.
 *
 * @return None.
 */
#define PSM_RESTARTWINDOWS      (WM_USER + 105)
/**
 * This macro sends a PSM_RESTARTWINDOWS message indicating that Windows needs to be restarted for
 * changes to take effect. You can use this macro or send the PSM_RESTARTWINDOWS message explicitly.
 * An application should send the PSM_RESTARTWINDOWS message only in response to the PSN_APPLY or
 * PSN_KILLACTIVE notification message.
 *
 * @param hPropSheetDlg Handle to the property sheet.
 *
 * @return None.
 *
 * The PSM_RESTARTWINDOWS message causes the PropertySheet function to return the
 * ID_PSRESTARTWINDOWS value, but only if the user clicks the OK button to close the property sheet.
 * It is the application's responsibility to reboot the system.
 */
#define PropSheet_RestartWindows(hDlg) \
        SNDMSG(hDlg, PSM_RESTARTWINDOWS, 0, 0L)


/**
 * This message indicates that system needs to be restarted for the changes to take effect. An
 * application should send this message only in response to the PSN_APPLY or PSN_KILLACTIVE
 * notification message. You can send the PSM_REBOOTSYSTEM message explicitly or by using the
 * PropSheet_RebootSystem macro.
 *
 * @return None.
 *
 * This message causes the PropertySheet function to return the ID_PSREBOOTSYSTEM value, but only if
 * the user clicks the OK button to close the property sheet.
 */
#define PSM_REBOOTSYSTEM        (WM_USER + 106)
/**
 * This macro indicates that the system needs to be restarted for the changes to take effect. You
 * can use this macro or send the PSM_REBOOTSYSTEM message explicitly. An application should send
 * the PSM_REBOOTSYSTEM message only in response to the PSN_APPLY or PSN_KILLACTIVE notification
 * message.
 *
 * @param hPropSheetDlg Handle to the property sheet.
 *
 * @return None.
 *
 * This macro causes the PropertySheet function to return the ID_PSREBOOTSYSTEM value, but only if
 * the user clicks the OK button to close the property sheet. It is the application's responsibility
 * to reboot the system.
 *
 * This macro supersedes all PropSheet_RebootSystem macros that precede or follow it.
 */
#define PropSheet_RebootSystem(hDlg) \
        SNDMSG(hDlg, PSM_REBOOTSYSTEM, 0, 0L)


/**
 * This message disables the Cancel button and changes the text of the OK button to "Close." An
 * application sends this message after applying a change that cannot be canceled. You can send this
 * message explicitly or by using the PropSheet_CancelToClose macro.
 *
 * @return None.
 */
#define PSM_CANCELTOCLOSE       (WM_USER + 107)
/**
 * This macro disables the Cancel button and changes the text of the OK button to Close. An
 * application sends the PSM_CANCELTOCLOSE message after applying a change that cannot be canceled.
 * You can use this macro or send the PSM_CANCELTOCLOSE message explicitly.
 *
 * @param hPropSheetDlg Handle to the property sheet.
 *
 * @return None.
 */
#define PropSheet_CancelToClose(hDlg) \
        PostMessage(hDlg, PSM_CANCELTOCLOSE, 0, 0L)


/**
 * This message is sent to a property sheet, which then forwards the message to each of its pages.
 * If a page returns a nonzero value, the property sheet does not send the message to subsequent
 * pages. You can send this message explicitly or by using the PropSheet_QuerySiblings macro.
 *
 * @param param1 First application-defined parameter.
 * @param param2 Second application-defined parameter.
 *
 * @return Returns the nonzero value from a page in the property sheet, or zero if no page returns a
 *   nonzero value.
 */
#define PSM_QUERYSIBLINGS       (WM_USER + 108)
/**
 * This macro causes a property sheet to send the PSM_QUERYSIBLINGS message to each of its pages. If
 * a page returns a nonzero value, the property sheet does not send the message to subsequent pages.
 * You can use this macro or send the PSM_QUERYSIBLINGS message explicitly.
 *
 * @param hPropSheetDlg Handle to the property sheet.
 * @param param1 First application-defined parameter.
 * @param param2 Second application-defined parameter.
 *
 * @return Returns the nonzero value from a page in the property sheet, or zero if no page returns a
 *   nonzero value.
 */
#define PropSheet_QuerySiblings(hDlg, wParam, lParam) \
        SNDMSG(hDlg, PSM_QUERYSIBLINGS, wParam, lParam)


/**
 * This message informs a property sheet that information in a page has reverted to the previously
 * saved state. The property sheet disables the Apply Now button if no other pages have registered
 * changes with the property sheet. You can send this message explicitly or by using the
 * PropSheet_UnChanged macro.
 *
 * @param hwndPage Handle to the page that has reverted to the previously saved state.
 *
 * @return None.
 */
#define PSM_UNCHANGED           (WM_USER + 109)
/**
 * This macro informs a property sheet that informationin a page has reverted to the previously
 * saved state. The property sheet disables the Apply Now button if no other pages have registered
 * changes with the property sheet. You can use this macro or send the PSM_UNCHANGED message
 * explicitly.
 *
 * @param hPropSheetDlg Handle to the property sheet.
 * @param hwndPage Handle to the page that has reverted to the previously saved state.
 *
 * @return None.
 */
#define PropSheet_UnChanged(hDlg, hwnd) \
        SNDMSG(hDlg, PSM_UNCHANGED, (WPARAM)hwnd, 0L)


/**
 * This message simulates the choice of the Apply Now button, indicating that one or more pages have
 * changed and the changes need to be validated and recorded.
 *
 * @return TRUE indicates that all pages successfully applied the changes. FALSE indicates failure.
 *
 * The property sheet sends the PSN_KILLACTIVE notification message to the current page. If the
 * current page returns FALSE, the property sheet sends the PSN_APPLY notification message to all
 * pages. You can send the PSM_APPLY message explicitly or by using the PropSheet_Apply macro.
 */
#define PSM_APPLY               (WM_USER + 110)
/**
 * This macro simulates the choice of the Apply Now button, indicating that one or more pages have
 * changed and the changes need to be validated and recorded. The property sheet sends the
 * PSN_KILLACTIVE notification message to the current page. If the current page returns FALSE, the
 * property sheet sends the PSN_APPLY notification message to all pages. You can use this macro or
 * send the PSM_APPLY message explicitly.
 *
 * @param hPropSheetDlg Handle to the property sheet.
 *
 * @return TRUE indicates that all pages successfully applied the changes. FALSE indicates failure.
 */
#define PropSheet_Apply(hDlg) \
        SNDMSG(hDlg, PSM_APPLY, 0, 0L)


#define PSM_SETTITLEA           (WM_USER + 111)
#define PSM_SETTITLEW           (WM_USER + 120)

#ifdef UNICODE
/**
 * This message sets the title of a property sheet. You can send this message explicitly or by using
 * the PropSheet_SetTitle macro.
 *
 * @param dwStyle Indicates whether to include the prefix "Properties for" with the specified title
 *   string. If dwStyle is the PSH_PROPTITLE value, the prefix is included. Otherwise, the prefix is
 *   not used.
 * @param lpszText Long pointer to a buffer that contains the title string. If the high-order word
 *   of this parameter is NULL, the property sheet loads the string resource specified in the
 *   low-order word.
 *
 * @return None.
 */
#define PSM_SETTITLE            PSM_SETTITLEW
#else
/**
 * This message sets the title of a property sheet. You can send this message explicitly or by using
 * the PropSheet_SetTitle macro.
 *
 * @param dwStyle Indicates whether to include the prefix "Properties for" with the specified title
 *   string. If dwStyle is the PSH_PROPTITLE value, the prefix is included. Otherwise, the prefix is
 *   not used.
 * @param lpszText Long pointer to a buffer that contains the title string. If the high-order word
 *   of this parameter is NULL, the property sheet loads the string resource specified in the
 *   low-order word.
 *
 * @return None.
 */
#define PSM_SETTITLE            PSM_SETTITLEA
#endif

/**
 * This macro sets the title of a property sheet. You can use this macro or send the PSM_SETTITLE
 * message explicitly.
 *
 * @param hPropSheetDlg Handle to the property sheet.
 * @param dwStyle Indicates whether to include the prefix "Properties for" with the specified title
 *   string. If dwStyle is the PSH_PROPTITLE value, the prefix is included. Otherwise, the prefix is
 *   not used.
 * @param lpszText Long pointer to a buffer that contains the title string. If the high-order word
 *   of this parameter is NULL, the property sheet loads the string resource specified in the
 *   low-order word.
 *
 * @return None.
 */
#define PropSheet_SetTitle(hDlg, wStyle, lpszText)\
        SNDMSG(hDlg, PSM_SETTITLE, wStyle, (LPARAM)(LPCTSTR)lpszText)


#define PSM_SETWIZBUTTONS       (WM_USER + 112)
/**
 * This macro posts the PSM_SETWIZBUTTON message to a wizard property sheet. The PSM_SETWIZBUTTON
 * message enables or disables the Back, Next, and Finish buttons in a wizard property sheet. You
 * can use this macro or explicitly send or post the PSM_SETWIZBUTTON message.
 *
 * @param hPropSheetDlg Handle to the property sheet.
 * @param dwFlags Specifies the buttons to display and enable. It is one of the following flags:
 *   Value Description PSWIZB_BACK Enables the Back button. PSWIZB_NEXT Enables the Next button.
 *   PSWIZB_FINISH Displays an enabled Finish button in place of the Next button.
 *   PSWIZB_DISABLEDFINISH Displays a disabled Finish button in place of the Next button. A wizard
 *   property sheet displays the Back button and either the Next or Finish button, which means that
 *   the PSWIZB_BACK flag is coupled with one of the other three flags.
 *
 * @return None.
 */
#define PropSheet_SetWizButtons(hDlg, dwFlags) \
        PostMessage(hDlg, PSM_SETWIZBUTTONS, 0, (LPARAM)dwFlags)



#define PSWIZB_BACK             0x00000001
#define PSWIZB_NEXT             0x00000002
#define PSWIZB_FINISH           0x00000004
#define PSWIZB_DISABLEDFINISH   0x00000008


/**
 * This message simulates the choice of a property sheet button. You can send this message
 * explicitly or by using the PropSheet_PressButton macro.
 *
 * @param iButton Index of the button to select. It is one of the following values: Value
 *   Description PSBTN_APPLYNOW Selects the Apply Now button. PSBTN_BACK Selects the Back button.
 *   PSBTN_CANCEL Selects the Cancel button. PSBTN_FINISH Selects the Finish button. PSBTN_HELP
 *   Selects the Help button. PSBTN_NEXT Selects the Next button. PSBTN_OK Selects the OK button.
 *
 * @return None.
 */
#define PSM_PRESSBUTTON         (WM_USER + 113)
/**
 * This macro simulates the choice of a property sheet button. You can use this macro or send the
 * PSM_PRESSBUTTON message explicitly.
 *
 * @param hPropSheetDlg Handle to the property sheet.
 * @param iButton Index of the button to select. It is one of the following values: Value
 *   Description PSBTN_APPLYNOW Selects the Apply Now button. PSBTN_BACK Selects the Back button.
 *   PSBTN_CANCEL Selects the Cancel button. PSBTN_FINISH Selects the Finish button. PSBTN_HELP
 *   Selects the Help button. PSBTN_NEXT Selects the Next button. PSBTN_OK Selects the OK button.
 *
 * @return None.
 */
#define PropSheet_PressButton(hDlg, iButton) \
        PostMessage(hDlg, PSM_PRESSBUTTON, (WPARAM)iButton, 0)


#define PSBTN_BACK              0
#define PSBTN_NEXT              1
#define PSBTN_FINISH            2
#define PSBTN_OK                3
#define PSBTN_APPLYNOW          4
#define PSBTN_CANCEL            5
#define PSBTN_HELP              6
#define PSBTN_MAX               6



/**
 * This message activates the specified page in a property sheet based on the resource identifier of
 * the page. You can send this message explicitly or by using the PropSheet_SetCurSelByID macro.
 *
 * @param id Resource identifier of the page to activate.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 */
#define PSM_SETCURSELID         (WM_USER + 114)
/**
 * This macro activates the specified page in a property sheet based on the resource identifier of
 * the page. You can use this macro or send the PSM_SETCURSELID message explicitly.
 *
 * @param hPropSheetDlg Handle to the property sheet.
 * @param id Resource identifier of the page to activate.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * The window that is losing the activation receives the PSN_KILLACTIVE notification message, and
 * the window that is gaining the activation receives the PSN_SETACTIVE notification message.
 */
#define PropSheet_SetCurSelByID(hDlg, id) \
        SNDMSG(hDlg, PSM_SETCURSELID, 0, (LPARAM)id)


#define PSM_SETFINISHTEXTA      (WM_USER + 115)
#define PSM_SETFINISHTEXTW      (WM_USER + 121)

#ifdef UNICODE
/**
 * This message sets the text of the Finish button in a wizard property sheet, shows and enables the
 * button, and hides the Next and Back buttons. You can send this message explicitly or by using the
 * PropSheet_SetFinishText macro.
 *
 * @param lpszText Long pointer to the null-terminated string that contains the new text for the
 *   Finish button.
 *
 * @return None.
 */
#define PSM_SETFINISHTEXT       PSM_SETFINISHTEXTW
#else
/**
 * This message sets the text of the Finish button in a wizard property sheet, shows and enables the
 * button, and hides the Next and Back buttons. You can send this message explicitly or by using the
 * PropSheet_SetFinishText macro.
 *
 * @param lpszText Long pointer to the null-terminated string that contains the new text for the
 *   Finish button.
 *
 * @return None.
 */
#define PSM_SETFINISHTEXT       PSM_SETFINISHTEXTA
#endif

/**
 * This macro sets the text of the Finish button in a wizard property sheet, shows and enables the
 * button, and hides the Next and Back buttons. You can use this macro or explicitly send the
 * PSM_SETFINISHTEXT message.
 *
 * @param hPropSheetDlg Handle to the property sheet.
 * @param lpszText Long pointer to the new text for the Finish button.
 *
 * @return None.
 *
 * This macro causes the DM_SETDEFID message to be sent to the property sheet dialog box. The wParam
 * parameter specifies the identifier of the Finish button.
 */
#define PropSheet_SetFinishText(hDlg, lpszText) \
        SNDMSG(hDlg, PSM_SETFINISHTEXT, 0, (LPARAM)lpszText)


/**
 * This message retrieves the handle of the tab control of a property sheet. You can send this
 * message explicitly or by using the PropSheet_GetTabControl macro.
 *
 * @return Returns the handle to the tab control.
 */
#define PSM_GETTABCONTROL       (WM_USER + 116)
/**
 * This macro retrieves the handle to the tab control of a property sheet. You can use this macro or
 * send the PSM_GETTABCONTROL message explicitly.
 *
 * @param hPropSheetDlg Handle to the property sheet.
 *
 * @return The handle to the tab control indicates success.
 */
#define PropSheet_GetTabControl(hDlg) \
        (HWND)SNDMSG(hDlg, PSM_GETTABCONTROL, 0, 0)

/**
 * This message passes a message to a property sheet dialog box and indicates whether the dialog
 * processed the message. You can send this message explicitly or by using the
 * PropSheet_IsDialogMessage macro.
 *
 * @param pMsg Pointer to an MSG structure that contains the message to be checked.
 *
 * @return TRUE indicates that the message has been processed. FALSE indicates that the message has
 *   not been processed.
 *
 * Your message loop should use the PSM_ISDIALOGMESSAGE message with modeless property sheets to
 * pass messages to the property sheet dialog box.
 *
 * If the return value indicates that the message was processed, it must not be passed to the
 * DispatchMessage function.
 */
#define PSM_ISDIALOGMESSAGE     (WM_USER + 117)
/**
 * This macro passes a message to a property sheet dialog box and indicates whether the dialog
 * processed the message. You can use this macro or send the PSM_ISDIALOGMESSAGE message explicitly.
 *
 * @param hDlg Handle to the property sheet.
 * @param pMsg Pointer to an MSG structure that contains the message to be checked.
 *
 * @return TRUE indicates that the macro has been processed. FALSE indicates the macro has not been
 *   processed.
 *
 * Your message loop should use the PSM_ISDIALOGMESSAGE message with modeless property sheets to
 * pass messages to the property sheet dialog box.
 *
 * If the return value indicates that the PSM_ISDIALOGMESSAGE message was processed, it must not be
 * passed to the TranslateMessage or DispatchMessage function.
 */
#define PropSheet_IsDialogMessage(hDlg, pMsg) \
        (BOOL)SNDMSG(hDlg, PSM_ISDIALOGMESSAGE, 0, (LPARAM)pMsg)

/**
 * This message retrieves a handle to the window of the current page of a property sheet. You can
 * send this message explicitly or by using the PropSheet_GetCurrentPageHwnd macro.
 *
 * @return Returns a handle to the window of the current property sheet page. Use the
 *   PSM_GETCURRENTPAGEHWND message with modeless property sheets to determine when to destroy the
 *   dialog box. When the user clicks the OK or Cancel button, PSM_GETCURRENTPAGEHWND returns NULL,
 *   and you can then use the DestroyWindow function to destroy the dialog box.
 */
#define PSM_GETCURRENTPAGEHWND  (WM_USER + 118)
/**
 * This macro retrieves a handle to the window of the current page of a property sheet. You can use
 * this macro or send the PSM_GETCURRENTPAGEHWND message explicitly.
 *
 * @param hDlg Handle to the property sheet.
 *
 * @return A handle to the window of the current property sheet page indicates success.
 *
 * Use the PropSheet_GetCurrentPageHwnd macro with modeless property sheets to determine when to
 * destroy the dialog box. When the user clicks the OK or Cancel button,
 * PropSheet_GetCurrentPageHwnd returns NULL, and you can then use the DestroyWindow function to
 * destroy the dialog box.
 */
#define PropSheet_GetCurrentPageHwnd(hDlg) \
        (HWND)SNDMSG(hDlg, PSM_GETCURRENTPAGEHWND, 0, 0L)

#define ID_PSRESTARTWINDOWS     0x2
#define ID_PSREBOOTSYSTEM       (ID_PSRESTARTWINDOWS | 0x1)


#define WIZ_CXDLG               276
#define WIZ_CYDLG               140

#define WIZ_CXBMP               80

#define WIZ_BODYX               92
#define WIZ_BODYCX              184

#define PROP_SM_CXDLG           212
#define PROP_SM_CYDLG           188

#define PROP_MED_CXDLG          227
#define PROP_MED_CYDLG          215

#define PROP_LG_CXDLG           252
#define PROP_LG_CYDLG           218



#ifdef __cplusplus
}
#endif

#ifdef WINCEOEM
#include <pprsht.h>     // internal defines 
#endif

#endif  // _PRSHT_H_
