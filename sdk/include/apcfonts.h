

#ifndef _APCFonts_H
#define _APCFonts_H


// This color definition system is designed in the spirit if GetSysColor
// GetSysColor was not modified to allow for the possiblity of standard 
// windows color schemes to co-exist with the AutoPC faceplace color schemes

// AutoPC System Colors

// generic defaults
#define AFNT_NORMAL                    0x0000
#define AFNT_LARGE                     0x0001

// power list and menu
#define AFNT_TITLEBAR                  0x0002

// power list 
#define AFNT_PLB_HILITE                0x0003
#define AFNT_PLB_NORMAL                0x0004

// power menu
#define AFNT_PMENU_HILITE              0x0005
#define AFNT_PMENU_NORMAL              0x0006

// editbox
#define AFNT_EDIT                      0x0007
#define AFNT_EDITLABEL                 0x0008


#define APCINVALIDFONT 0xffffffff

HRESULT APCGetSysFont(  OLE_HANDLE hFC, int nIndex, IFontDisp **ppFontDisp);

#endif



