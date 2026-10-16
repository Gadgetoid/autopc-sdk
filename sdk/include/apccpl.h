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

#define CPL_APCINQUIRE          0xFB01

typedef struct
{
    DWORD   dwSize;         //Size of this structure. Must be filled in by the applet.
    WCHAR   szTTSName[32];  //Text-to-speech name of this applet.
    WCHAR   szAlertName[32];	//Alert name name of this applet.
} APCCPLINFO;

#endif //APCCPL_H