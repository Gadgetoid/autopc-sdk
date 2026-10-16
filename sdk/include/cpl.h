/*****************************************************************************\
*                                                                             *
* cpl.h -       Control panel extension DLL definitions                       *
*                                                                             *
*               Version 3.10                                                  *
*                                                                             *
*               Copyright (c) 1992-1995, Microsoft Corp.  All rights reserved *
*                                                                             *
******************************************************************************/
/*
*  General rules for being installed in the Control Panel:
*
*      1) The DLL must export a function named CPlApplet which will handle
*         the messages discussed below.
*      2) If the applet needs to save information in CONTROL.INI minimize
*         clutter by using the application name [MMCPL.appletname].
*      2) If the applet is refrenced in CONTROL.INI under [MMCPL] use
*         the following form:
*              ...
*              [MMCPL]
*              uniqueName=c:\mydir\myapplet.dll
*              ...
*
*
*  The order applet DLL's are loaded by CONTROL.EXE is:
*
*      1) MAIN.CPL is loaded from the windows system directory.
*
*      2) Installable drivers that are loaded and export the
*         CplApplet() routine.
*
*      3) DLL's specified in the [MMCPL] section of CONTROL.INI.
*
*      4) DLL's named *.CPL from windows system directory.
*
*/
#ifndef _INC_CPL
#define _INC_CPL


#include "pshpack1.h"   /* Assume byte packing throughout */

#ifdef __cplusplus
extern "C" {            /* Assume C declarations for C++ */
#endif /* __cplusplus */

/*
 * CONTROL.EXE will answer this message and launch an applet
 *
 * WM_CPL_LAUNCH
 *
 *      wParam      - window handle of calling app
 *      lParam      - LPTSTR of name of applet to launch
 *
 * WM_CPL_LAUNCHED
 *
 *      wParam      - TRUE/FALSE if applet was launched
 *      lParam      - NULL
 *
 * CONTROL.EXE will post this message to the caller when the applet returns
 * (ie., when wParam is a valid window handle)
 *
 */
#define WM_CPL_LAUNCH   (WM_USER+1000)
#define WM_CPL_LAUNCHED (WM_USER+1001)

/* A function prototype for CPlApplet() */

//typedef LRESULT (APIENTRY *APPLET_PROC)(HWND hwndCpl, UINT msg, LPARAM lParam1, LPARAM lParam2);
typedef LONG (APIENTRY *APPLET_PROC)(HWND hwndCpl, UINT msg, LONG lParam1, LONG lParam2);

/* The data structure CPlApplet() must fill in. */

/**
 * This structure contains resource information and a user-defined value for a dialog box supported
 * by a Control Panel application.
 *
 * If the icon or display strings of the dialog box can change based on the state of the computer,
 * you can specify the CPL_DYNAMIC_RES value for the idIcon, idName, or idInfo members rather than
 * specifying a valid resource identifier. This causes the Control Panel to send the CPL_NEWINQUIRE
 * message each time it needs the icon and display strings. Using this technique is significantly
 * slower, however, because the Control Panel will need to load your application each time it sends
 * the CPL_NEWINQUIRE message.
 */
typedef struct tagCPLINFO
{
    /**
     * Resource identifier of the icon that represents the dialog box.
     */
    int     idIcon;     /* icon resource id, provided by CPlApplet() */
    /**
     * Resource identifier of the string that contains the short name for the dialog box. This name is
     * intended to be displayed below the icon.
     */
    int     idName;     /* name string res. id, provided by CPlApplet() */
    /**
     * Resource identifier of the string that contains the description for the dialog box that is
     * intended to be displayed when the application icon is selected.
     */
    int     idInfo;     /* info string res. id, provided by CPlApplet() */
    /**
     * Data defined by the application. When the Control Panel sends the CPL_DBCLK and CPL_STOP
     * messages, it passes this value back to your application.
     */
    LONG    lData;      /* user defined data */
} CPLINFO, *LPCPLINFO;

/**
 * This structure contains resource information and a user-defined value for a dialog box supported
 * by a Control Panel application.
 *
 * The dwHelpContext and szHelpSize members are not used by the control panel explorer in Windows CE
 * for the Handheld PC.
 *
 * For ldata, applications should return the icon resource ID for the control panel (same as hIcon,
 * but the resource ID instead of the icon handle.)
 */
typedef struct tagNEWCPLINFOA
{
    /**
     * Specifies the length of the structure, in bytes.
     */
    DWORD   dwSize;         /* similar to the commdlg */
    /**
     * Ignored.
     */
    DWORD   dwFlags;
    /**
     * Ignored.
     */
    DWORD   dwHelpContext;  /* help context to use */
    /**
     * Data defined by the application. When the Control Panel sends the CPL_DBCLK and CPL_STOP
     * messages, it passes this value back to your application.
     */
    LONG    lData;          /* user defined data */
    /**
     * Handle to the icon that represents the dialog box. This icon is intended to be displayed by the
     * application that controls the Control Panel application.
     */
    HICON   hIcon;          /* icon to use, this is owned by CONTROL.EXE (may be deleted) */
    /**
     * Null-terminated string that contains the dialog box name. The name is intended to be displayed
     * below the icon.
     */
    CHAR    szName[32];     /* short name */
    /**
     * Null-terminated string that contains the dialog box description. The description is intended to
     * be displayed when the icon for the dialog box is selected.
     */
    CHAR    szInfo[64];     /* long name (status line) */
    /**
     * Ignored.
     */
    CHAR    szHelpFile[128];/* path to help file to use */
} NEWCPLINFOA, *LPNEWCPLINFOA;
/**
 * This structure contains resource information and a user-defined value for a dialog box supported
 * by a Control Panel application.
 *
 * The dwHelpContext and szHelpSize members are not used by the control panel explorer in Windows CE
 * for the Handheld PC.
 *
 * For ldata, applications should return the icon resource ID for the control panel (same as hIcon,
 * but the resource ID instead of the icon handle.)
 */
typedef struct tagNEWCPLINFOW
{
    /**
     * Specifies the length of the structure, in bytes.
     */
    DWORD   dwSize;         /* similar to the commdlg */
    /**
     * Ignored.
     */
    DWORD   dwFlags;
    /**
     * Ignored.
     */
    DWORD   dwHelpContext;  /* help context to use */
    /**
     * Data defined by the application. When the Control Panel sends the CPL_DBCLK and CPL_STOP
     * messages, it passes this value back to your application.
     */
    LONG    lData;          /* user defined data */
    /**
     * Handle to the icon that represents the dialog box. This icon is intended to be displayed by the
     * application that controls the Control Panel application.
     */
    HICON   hIcon;          /* icon to use, this is owned by CONTROL.EXE (may be deleted) */
    /**
     * Null-terminated string that contains the dialog box name. The name is intended to be displayed
     * below the icon.
     */
    WCHAR   szName[32];     /* short name */
    /**
     * Null-terminated string that contains the dialog box description. The description is intended to
     * be displayed when the icon for the dialog box is selected.
     */
    WCHAR   szInfo[64];     /* long name (status line) */
    /**
     * Ignored.
     */
    WCHAR   szHelpFile[128];/* path to help file to use */
} NEWCPLINFOW, *LPNEWCPLINFOW;
#ifdef UNICODE
typedef NEWCPLINFOW NEWCPLINFO;
typedef LPNEWCPLINFOW LPNEWCPLINFO;
#else
typedef NEWCPLINFOA NEWCPLINFO;
typedef LPNEWCPLINFOA LPNEWCPLINFO;
#endif // UNICODE

/* The messages CPlApplet() must handle: */

#if(WINVER >= 0x0400)
#define CPL_DYNAMIC_RES 0
// This constant may be used in place of real resource IDs for the idIcon,
// idName or idInfo members of the CPLINFO structure.  Normally, the system
// uses these values to extract copies of the resources and store them in a
// cache.  Once the resource information is in the cache, the system does not
// need to load a CPL unless the user actually tries to use it.
// CPL_DYNAMIC_RES tells the system not to cache the resource, but instead to
// load the CPL every time it needs to display information about an item.  This
// allows a CPL to dynamically decide what information will be displayed, but
// is SIGNIFICANTLY SLOWER than displaying information from a cache.
// Typically, CPL_DYNAMIC_RES is used when a control panel must inspect the
// runtime status of some device in order to provide text or icons to display.

#endif /* WINVER >= 0x0400 */

/**
 * This message is sent to a Control Panel application to prompt it to perform global
 * initialization, especially memory allocation.
 *
 * @return If initialization succeeds, the CPlApplet function should return nonzero. Otherwise, it
 *   should return zero. If CPlApplet returns zero, the controlling application ends communication and
 *   releases the DLL that contains the Control Panel application.
 *
 * The return value is not checked by the control panel explorer.
 *
 * In Windows CE version 1.0, an error is recognized when the applet does not fill the NEWCPLINFO
 * structure properly in response to the CPL_NEWINQUIRE message.
 *
 * Because this is the only way a Control Panel application can signal an error condition, the
 * application should allocate memory in response to this message.
 *
 * This message is sent immediately after the DLL that contains the application is loaded.
 */
#define CPL_INIT        1
/*  This message is sent to indicate CPlApplet() was found. */
/*  lParam1 and lParam2 are not defined. */
/*  Return TRUE or FALSE indicating whether the control panel should proceed. */


/**
 * This message is sent to a Control Panel application to retrieve the number of dialog boxes
 * supported by the application.
 *
 * @return The CPlApplet function returns the number of dialog boxes that the Control Panel
 *   application supports.
 *
 * This message is sent immediately after the CPL_INIT message.
 */
#define CPL_GETCOUNT    2
/*  This message is sent to determine the number of applets to be displayed. */
/*  lParam1 and lParam2 are not defined. */
/*  Return the number of applets you wish to display in the control */
/*  panel window. */


#define CPL_INQUIRE     3
/*  This message is sent for information about each applet. */
/*  lParam1 is the applet number to register, a value from 0 to */
/*  (CPL_GETCOUNT - 1).  lParam2 is a far ptr to a CPLINFO structure. */
/*  Fill in CPL_INFO's idIcon, idName, idInfo and lData fields with */
/*  the resource id for an icon to display, name and description string ids, */
/*  and a long data item associated with applet #lParam1. */


#define CPL_SELECT      4
/*  This message is sent when the applet's icon has been clicked upon. */
/*  lParam1 is the applet number which was selected.  lParam2 is the */
/*  applet's lData value. */


/**
 * This message is sent to a Control Panel application when the user double-clicks the icon in the
 * control panel explorer.
 *
 * @param uAppNum Dialog box number. This number must be in the range zero through one less than the
 *   value returned in response to the CPL_GETCOUNT message (CPL_GETCOUNT -1).
 * @param lData Value that the Control Panel application loaded into the lData member of the CPLINFO
 *   or NEWCPLINFO structure for the dialog box. The application loads the lData member in response to
 *   the CPL_INQUIRE or CPL_NEWINQUIRE message.
 *
 * @return Zero indicates that the CPlApplet function processes this message successfully. Nonzero
 *   indicates otherwise.
 *
 * In response to this message, a Control Panel application must display the corresponding dialog
 * box.
 */
#define CPL_DBLCLK      5
/*  This message is sent when the applet's icon has been double-clicked */
/*  upon.  lParam1 is the applet number which was selected.  lParam2 is the */
/*  applet's lData value. */
/*  This message should initiate the applet's dialog box. */


/**
 * This message is sent once for each dialog box when the application controlling the Control Panel
 * application closes.
 *
 * @param uAppNum Dialog box number.
 * @param lData Value that the Control Panel application loaded into the lData member of the CPLINFO
 *   or NEWCPLINFO structure for the dialog box. The application loads the lData member in response to
 *   the CPL_INQUIRE or CPL_NEWINQUIRE message.
 *
 * @return Zero indicates that the CPlApplet function processes this message successfully.
 *
 * In response to this message, a Control Panel application must perform cleanup for the given
 * dialog box.
 */
#define CPL_STOP        6
/*  This message is sent for each applet when the control panel is exiting. */
/*  lParam1 is the applet number.  lParam2 is the applet's lData  value. */
/*  Do applet specific cleaning up here. */


/**
 * This message is sent once to a Control Panel application before the controlling application
 * releases the DLL that contains the application.
 *
 * @return Zero indicates that the CPlApplet function processes this message successfully.
 *
 * This message is sent after the last CPL_STOP message is sent.
 *
 * In response to this message, a Control Panel application must free any memory that it has
 * allocated and perform global-level cleanup.
 */
#define CPL_EXIT        7
/*  This message is sent just before the control panel calls FreeLibrary. */
/*  lParam1 and lParam2 are not defined. */
/*  Do non-applet specific cleaning up here. */


/**
 * This message is sent to a Control Panel application to request information about a dialog box
 * that the application supports.
 *
 * @param uAppNum Dialog box number. This number must be in the range zero through one less than the
 *   value returned in response to the CPL_GETCOUNT message (CPL_GETCOUNT -1).
 * @param lpncpli Long pointer to a NEWCPLINFO structure. The Control Panel application should fill
 *   this structure with information about the dialog box.
 *
 * @return Zero indicates that the CPlApplet function processes this message successfully.
 *
 * The Control Panel sends the CPL_NEWINQUIRE message once for each dialog box supported by your
 * application. The Control Panel also sends a CPL_INQUIRE message for each dialog box. These
 * messages are sent immediately after the CPL_GETCOUNT message. However, the system does not
 * guarantee the order in which the CPL_INQUIRE and CPL_NEWINQUIRE messages are sent.
 *
 * You can perform initialization for the dialog box when you receive CPL_INQUIRE. If you must
 * allocate memory, do so in response to the CPL_INIT message.
 *
 * The CPL_NEWINQUIRE message was introduced in Windows version 3.1 as a replacement for
 * CPL_INQUIRE. However, CPL_INQUIRE is the preferred message for Windows 95 and Windows NT version
 * 4.0. This is because CPL_NEWINQUIRE returns information in a form that the system cannot cache.
 * Consequently, applications that process CPL_NEWINQUIRE must be loaded each time the Control Panel
 * needs the information, resulting in a significant reduction in performance.
 *
 * The only applications that should use CPL_NEWINQUIRE are those that need to change their icon or
 * display strings based on the state of the computer. In this case, your CPL_INQUIRE handler should
 * specify the CPL_DYNAMIC_RES value for the idIcon, idName, or idInfo members of the CPLINFO
 * structure, rather than specifying a valid resource identifier. This causes the Control Panel to
 * send the CPL_NEWINQUIRE message each time it needs the icon and display strings, allowing you to
 * specify information based on the current state of the computer. Of course, this is significantly
 * slower than using cached information.
 */
#define CPL_NEWINQUIRE    8
/* this is the same as CPL_INQUIRE execpt lParam2 is a pointer to a */
/* NEWCPLINFO structure.  this will be sent before the CPL_INQUIRE */
/* and if it is responed to (return != 0) CPL_INQUIRE will not be sent */

#if(WINVER >= 0x0400)
#define CPL_STARTWPARMS 9
/* this message parallels CPL_DBLCLK in that the applet should initiate
** its dialog box.  where it differs is that this invocation is coming
** out of RUNDLL, and there may be some extra directions for execution.
** lParam1: the applet number.
** lParam2: an LPSTR to any extra directions that might exist.
** returns: TRUE if the message was handled; FALSE if not.
*/
#endif /* WINVER >= 0x0400 */


/* This message is internal to the Control Panel and MAIN applets.  */
/* It is only sent when an applet is invoked from the Command line  */
/* during system installation.                                      */
#define CPL_SETUP               200 

#ifdef __cplusplus
}
#endif    /* __cplusplus */

#include "poppack.h"

#endif  /* _INC_CPL */
