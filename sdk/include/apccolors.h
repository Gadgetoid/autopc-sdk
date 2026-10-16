

#ifndef _APCColors_H
#define _APCColors_H


// This color definition system is designed in the spirit if GetSysColor
// GetSysColor was not modified to allow for the possiblity of standard 
// windows color schemes to co-exist with the AutoPC faceplace color schemes

// AutoPC System Colors

// generic defaults
#define ASC_BACKGROUND                     1
#define ASC_FOREGROUND                     2
#define ASC_FOCUSBORDER                    3
#define ASC_BORDER                         4

// Label
#define ASC_LABEL_BACKGROUND              11
#define ASC_LABEL_FOREGROUND              12

// Editbox
#define ASC_EDIT_BACKGROUND               21
#define ASC_EDIT_FOREGROUND               22
#define ASC_EDIT_EDITMODE_BACKGROUND      23
#define ASC_EDIT_EDITMODE_FOREGROUND      24
#define ASC_EDIT_EDITMODE_ARROWS          25

// UserNavArrows
#define ASC_NAV_BACKGROUND                31
#define ASC_NAV_ARROW                     32
#define ASC_NAV_ENTER                     33
#define ASC_NAV_DISABLED                  34
#define ASC_NAV_FLASH                     35

// title bar
#define  ASC_TITLEBAR_BACKGROUND          41
#define  ASC_TITLEBAR_TEXT                42
#define  ASC_TITLEBAR_BORDER              43

// power list and menu
#define  ASC_PLB_BACKGROUND               51
#define  ASC_PLB_TEXT                     52
#define  ASC_PLB_CAPTION                  53
#define  ASC_PLB_HILITEBACKGROUND         54
#define  ASC_PLB_HILITETEXT               55
#define  ASC_PLB_HILITECAPTION            56

// Cross Hairs Default colors
#define  ASC_CROSS_AXIS                   61 
#define  ASC_CROSS_CROSSHAIR              62 
#define  ASC_CROSS_CROSSHAIR_HILITE       63
#define  ASC_CROSS_CROSSHAIR_BOX          64 
#define  ASC_CROSS_FOREGROUND             65 
#define  ASC_CROSS_FRAME                  66
#define  ASC_CROSS_BOXDOT                 67

// Image menu colors
#define ASC_IMAGEMENU_HILITECOLOR         71
#define ASC_IMAGEMENU_HILITEFORE          72
#define ASC_IMAGEMENU_HILITESHADOW        73
#define ASC_IMAGEMENU_BORDER              74

// Shell menu colors
#define ASC_SHELLMENU_LABELBACK           81
#define ASC_SHELLMENU_LABELTEXT           82

// Playlist colors
#define ASC_PLAYLIST_HILITE               91  
#define ASC_PLAYLIST_BORDER               92 
#define ASC_PLAYLIST_ITEMHILITE           93 

// Progress bar colors
#define ASC_PROGRESS_BORDER              101  
#define ASC_PROGRESS_FORE                102  
//#define ASC_PROGRESS_ALLBOXES             42  

// Tabber Control colors
#define ASC_TABBER_TAB                   111
#define ASC_TABBER_TEXT                  112
#define ASC_TABBER_HILITETAB             113
#define ASC_TABBER_HILITETEXT            114
#define ASC_TABBER_BORDER                115
#define ASC_TABBER_DISABLEDTEXT          116

// Character Spinner
#define ASC_CHARSPIN_BACKGROUND          121
#define ASC_CHARSPIN_TEXT                122
#define ASC_CHARSPIN_BORDERARROWS        123

// Progress bar colors
#define ASC_MEMORYSLIDER_BORDER          131  
#define ASC_MEMORYSLIDER_HILITE          132
#define ASC_MEMORYSLIDER_THUMBARROWS     133  

// VolumeProgress bar colors
#define ASC_VOLUME_FOREGROUND            140  

#define APCINVALIDCOLOR 0xffffffff

// APCGetSysColor
DWORD APCGetSysColor( OLE_HANDLE hFC, int nIndex);


BOOL APCSetSysColors( OLE_HANDLE hFC, int cElements,            // number of elements to change 
                    CONST INT *lpaElements,         // address of array of elements 
                    CONST COLORREF *lpaRgbValues);  // address of array of RGB values  
  

#endif



