/*
    APCCPL.H

    Include file for control panel applets on the AutoPC system.

    Copyright (c) 1997 Microsoft Corporation, All rights reserved.
*/

#ifndef APCCPL_H
#define APCCPL_H

#include <cpl.h>

/*Under AutoPC V1.00, the following rules apply:

    If only the faceplate is supported, the hWnd Parameter used by the
    CPlApplet function is not used.
    
    CPL_INIT
        As WinCE documentation.

    CPL_GETCOUNT
        As WinCE documentation.

    CPL_SELECT
        Supported by the AutoPC. This is not supported by WinCE.

    CPL_NEWINQUIRE
        As WinCE documentation, except:
        
        dwFlags - Set CPL_DISPLAY_FACEPLATE if this applet supports the
                  AutoPC faceplate. All V1.00 applets should support this.
                  Set CPL_DISPLAY_NOVGA is this aplet does NOT support the
                  VGA screen.
        szName  - This is the name displayed in the control panel icon view.

    CPL_APCINQUIRE
        New to AutoPC, this asks for AutoPC specific data from the applet.
        See the APCCPLINFO structure below.

    CPL_DBLCLK
        As WinCE documentation.

    CPL_STOP
        As WinCE documentation.

    CPL_EXIT        
        As WinCE documentation.

*/

#define CPL_DISPLAY_FACEPLATE   0x4000
#define CPL_DISPLAY_NOVGA       0x8000

/**
 * This message requests Auto PC specific data from a control panel application.
 *
 * @param lParam1 Unsigned integer that specifies the application number.
 * @param lParam2 Pointer to an APCCPLINFO structure that contains Auto PC-specific information
 *   about the control panel application.
 */
#define CPL_APCINQUIRE          0xFB01

/**
 * This structure provides information about a control panel application.
 */
typedef struct
{
    /**
     * DWORD that specifies the size of the structure. The control panel application must set this
     * value.
     */
    DWORD   dwSize;         //Size of this structure. Must be filled in by the applet.
    /**
     * Null-terminated string that contains the text-to-speech name of the control panel application.
     * The string must contain 32 characters or less.
     */
    WCHAR   szTTSName[32];  //Text-to-speech name of this applet.
    /**
     * Null-terminated string that contains the alert name of the control panel application. The string
     * must contain 32 characters or less.
     */
    WCHAR   szAlertName[32];	//Alert name name of this applet.
} APCCPLINFO;

#endif //APCCPL_H