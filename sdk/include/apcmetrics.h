

#ifndef _APCMetrics_H
#define _APCMetrics_H


// This color definition system is designed in the spirit if GetSysColor
// GetSysColor was not modified to allow for the possiblity of standard 
// windows color schemes to co-exist with the AutoPC faceplace color schemes

// AutoPC System Colors

// generic defaults
#define ASM_CYTITLEBAR               0x0000  // height of titlebar
#define ASM_CYTABBER                 0x0001  // height of tabber
#define ASM_CXTITLEBARITEMGAP        0x0002  // horiz space between items in title bar
#define ASM_PLBMAXITEMSVISIBLE       0x0003  // maximum number of power listbox visible at one time
#define ASM_FSPLBNORMAL              0x0004  // font size - non select PLB items
#define ASM_FSPLBHILITE              0x0005  // font size - hilited PLB item
#define ASM_FSTITLEBAR               0x0006  // font size - titlebar

// description of the large UI arrows drawn (same as nav arrow)
// note these X and Y are relative to the left and right arrows 
// for up and down arrows rotate the X and Y (the arrows are rectangular
#define ASM_CXARROWLARGE             0x0007  // width of a large arrow image 
#define ASM_CYARROWLARGE             0x0008  // height of a large arrow image (same as nav arrow)
#define ASM_CXARROWLARGEBORDER       0x0009  // width between large arrow image other stuff
#define ASM_CYARROWLARGEBORDER       0x000a  // height between large arrow image other stuff

#define APCINVALIDMETRIC ((-1))

// APCGetSysColor
long APCGetSystemMetrics(  OLE_HANDLE hFC, int nIndex);


BOOL APCSetSystemMetrics( int cElements,            // number of elements to change 
                    CONST INT *lpaElements,        // address of array of elements 
                    CONST long *lpaMetricValues);    // address of array of metric values  
  

#endif



