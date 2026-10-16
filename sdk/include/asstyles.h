//--------------------------------------------------------------------------------------------
//
//	Copyright (c) Microsoft Corporation, 1997 All Rights Reserved
//
//	Description:
//		AutoPC Simple Common Controls style definitions
//
//--------------------------------------------------------------------------------------------

#ifndef _ASSTYLE_H
#define _ASSTYLE_H
//--------------------------------------------------------------------------------------------
//
// FLAGS
//
//--------------------------------------------------------------------------------------------
//
// Color definition for use in RC file
//
#define     BC_BLACK                0x0000                     
#define     BC_RED                  0x0001                    
#define     BC_GREEN                0x0002                  
#define     BC_BLUE                 0x0003                       
#define     BC_WHITE                0x0004                     
#define     BC_VIOLET			    0x0005                  
#define     BC_CYAN                 0x0006                     
#define     BC_YELLOW               0x0007                    

#define     FC_BLACK				0x0000                        
#define     FC_RED					0x0100                     
#define     FC_GREEN			    0x0200 
#define     FC_BLUE					0x0300                      
#define     FC_WHITE				0x0400                    
#define     FC_VIOLET				0x0500                 
#define     FC_CYAN					0x0600                    
#define     FC_YELLOW				0x0700                        

//
// Alignment for Text on Labels, buttons
//
#define ASFC_ALIGN_TOP          DT_TOP      	// draw top aligned
#define ASFC_ALIGN_LEFT         DT_LEFT      	// draw left aligned
#define ASFC_ALIGN_CENTER       DT_CENTER       // draw centered
#define ASFC_ALIGN_RIGHT        DT_RIGHT        // draw right aligned
#define ASFC_ALIGN_VCENTER      DT_VCENTER      // draw centered vertically
#define ASFC_ALIGN_BOTTOM       DT_BOTTOM       // draw bottom aligned
#define ASFC_ALIGN_WORDBREAK	DT_WORDBREAK	// draw with word break
#define ASFC_ALIGN_SINGLELINE   DT_SINGLELINE   // draw in a single line
#define ASFC_ALIGN_NOCLIP   	DT_NOCLIP		// draw the text without clipping

//
// Image alignment on buttons and image controls
//
#define ASFC_IMAGE_HCENTER  0x00          // image is horizontally centered
#define ASFC_IMAGE_LEFT     0x01          // image is flush with left boundary of control
#define ASFC_IMAGE_RIGHT    0x02          // image is flush with right boundary of control    

#define ASFC_IMAGE_VCENTER  0x00          // image is vertically centered
#define ASFC_IMAGE_TOP      0x01          // image is flush with top boundary of control
#define ASFC_IMAGE_BOTTOM   0x02          // image is flush with bottom boundary of control
//
// Caption alignment on buttons
//
#define ASFC_CAPTION_ALIGNNONE 0x00       // caption extends from top to bottom of the control
#define ASFC_CAPTION_ALIGNTOP 0x01        // caption aligns with the top of the image
#define ASFC_CAPTION_ALIGNBOTTOM 0x02     // caption is aligned with the bottom of the image
//
// Grouping
//
#define ASFC_BTNGROUP_IDNONE   0x0000      // a control marked thus is in no group
#define ASFC_BTNGROUP_IDMIN    0x0001      // groups must have an ID >= ASFC_GROUP_IDMIN/
//
// Button behaviour
//
#define ASFC_BTN_STICKY     0x00           // button sticks when pressed
#define ASFC_BTN_NOTSTICKY  0x01           // button doesn't stick when pressed, and bounces back
#define ASFC_BTN_NOUNPUSH   0x02             // button does't rebound when un-push  

// Power List Box Styles
#define PLBS_PRESERVESTATUSCOLUMNS     0x0001     // leave space for status images which are not displayed

// Power List Box item types
#define ASFC_PWRLB_TYPE_COMMAND 0x00
#define ASFC_PWRLB_TYPE_EDIT    0x01
#define ASFC_PWRLB_TYPE_STRINGSPINNER 0x02
#define ASFC_PWRLB_TYPE_INTSPINNER 0x03

// Power List Box Item Status Flags
#define PLBIS_USERDEFINED      0x0000ffff   // user must use one of these bits
#define PLBIS_ITEMHIDDEN       0x80000000   // not emplemented
#define PLBIS_ITEMBOLD         0x40000000   // not implemented

// Power List Box spinner notification
#define PLBN_SPINCHANGE  6
#define PLBN_BEGINEDIT   40
#define PLBN_ENDEDIT     41

// Tabber notification
#define TN_VSELCHANGE  0x6		// the tabber selection has change in response to a voice command

// Tab Styles - passed to put_Style on the tabber Control
#define ASTS_DISABLED           0x0001


// 
// CharSpinner Modes
//
#define ASFC_CHARSPIN_SEQUENTIAL 0x1
#define ASFC_CHARSPIN_DIRSHIFTED 0x2

// 
// EditBox Notification flags
//
#define ASFC_EDITNOTIFY_CHANGED 0x1
#define ASFC_EDITNOTIFY_COMMITTED 0x2



// Force leading plus on an Int Spinner PowerListBox Item
#define ASFC_PWRLB_FLAGS_DISPLAYSIGN 0x1

// TitleUpdate Mode flags - 
// some controls support updating the forms titlebar dynamicly
#define ASTUM_CAPTION       0x0001  // not yet defined
#define ASTUM_STATUS        0x0002  // set the TB status to that of the current item
#define ASTUM_SUBCAPTION    0x0004  // set the TB SubC to the "x of n" string
#define ASTUM_CAPTIONEDIT   0x0008  // set the TB caption to the edititem caption when editing
#define ASTUM_CAPTIONMENU   0x0010  // set the TB caption to the PLB caption on FM->put_Menu
#define ASTUM_EDITHIDENAV   0x0020  // hide the nav arrows when editing


// Shell Menu
#define ASFC_SHELLMENU_UNDERLINE 0x01

// Image Menu
#define ASFC_IMAGEMENU_OVERLAY 0x02

// Edit Box
#define ASFC_EDITBOX_CCHMAX 32000


//
// HTMLControl Style options
//
// at least one of the two following flags MUST be enabled to get TTS output 
#define ASFC_HTML_SPEAK_TITLE	0x01          // title included in the TTS output
#define ASFC_HTML_SPEAK_BODY	0x02          // all body text is included in the TTS output
#define ASFC_HTML_SHOW_HSCROLL	0x04          // display the horizontal scroll arrows when appropriate
#define ASFC_HTML_SHOW_VSCROLL	0x08          // display the verticle scroll arrows when appropriate
#define ASFC_HTML_SHOW_ANCHORS	0x10          // display/identify the anchors


#define ASFC_SPEAK_CAPTION      0x00
#define ASFC_SPEAK_FOCUSITEM    0x01
#define ASFC_SPEAK_ALLITEMS     0x02
#define ASFC_SPEAK_ASFORMFOCUS  0x03
#define ASFC_SPEAK_ITEMBYID     0x04    // item ID passen in dwReserved
#define ASFC_SPEAK_ITEMATINDEX  0x05    // item index passed in dwReserved


// Voice Menu id's for controls
#define IDVM_ASEDIT 0x8000

// Voice Command Id's for controls
#define VC_ONE		0x8001		
#define VC_TWO 		0x8002
#define VC_THREE	0x8003
#define VC_FOUR		0x8004
#define VC_FIVE		0x8005
#define VC_SIX		0x8006
#define VC_SEVEN	0x8007
#define VC_EIGHT	0x8008
#define VC_NINE		0x8009
#define VC_ZERO		0x8010
#define VC_REVIEW	0x8011
#define VC_DELETE	0x8012
#define VC_OK		0x8013
#define VC_CANCEL	0x8014

// Voice Menu States
#define VMS_NUMBERS 0x0001
#define VMS_LETTERS 0x0002
#define VMS_CANCEL  0x0004
#define VMS_OK		0x0008
#define VMS_REVIEW  0x0010
#define VMS_DELETE  0x0020

// combined states
#define VMS_NORMALEDIT VMS_NUMBERS | VMS_CANCEL | VMS_OK | VMS_REVIEW | VMS_DELETE

// constraint based layout
#define FA_NONE -1

#define FA_BASE  10000

// Align to edges of the form
#define FA_TOP_OF_FORM         (FA_BASE+1) // Top edge of control to top edge of form
#define FA_BOTTOM_OF_FORM      (FA_BASE+2) // Bottom edge of control to bottom edge of form
#define FA_LEFT_OF_FORM        (FA_BASE+3) // Left edge of control to left edge of form
#define FA_RIGHT_OF_FORM       (FA_BASE+4) // Right edge of control to right edge of form

// Center control within form
#define FA_HORIZONTAL_CENTER   (FA_BASE+5)
#define FA_VERTICAL_CENTER     (FA_BASE+6)

// Align to an edge of another control
#define FA_TOP_CONTROL         (FA_BASE+7)
#define FA_LEFT_CONTROL        (FA_BASE+8)
#define FA_BOTTOM_CONTROL      (FA_BASE+9)
#define FA_RIGHT_CONTROL       (FA_BASE+10)

// Align edge to opposite edge of control
#define FA_TOP_TO_BOTTOM_OF_CONTROL (FA_BASE+11)
#define FA_LEFT_TO_RIGHT_OF_CONTROL (FA_BASE+12)
#define FA_BOTTOM_TO_TOP_OF_CONTROL (FA_BASE+13)
#define FA_RIGHT_TO_LEFT_OF_CONTROL (FA_BASE+14)

// Fraction specification on parent form (percentage of width or height follows -- e.g. 25 for 25%)
#define FA_TOP_FRACTION             (FA_BASE+15)
#define FA_LEFT_FRACTION            (FA_BASE+16)
#define FA_BOTTOM_FRACTION          (FA_BASE+17)
#define FA_RIGHT_FRACTION           (FA_BASE+18)


// Offset ("fudge factors") in pixels
#define FA_TOP_OFFSET               (FA_BASE+19)
#define FA_LEFT_OFFSET              (FA_BASE+20)
#define FA_BOTTOM_OFFSET            (FA_BASE+21)
#define FA_RIGHT_OFFSET             (FA_BASE+22)

// Specify exact location in form
#define FA_HORIZONTAL_CENTER_OF_CONTROL       (FA_BASE+23)
#define FA_VERTICAL_CENTER_OF_CONTROL         (FA_BASE+24)
//#define FA_BOTTOM    (FA_BASE+25)
//#define FA_RIGHT     (FA_BASE+26)


// Fraction specification with respect to another control
#define FA_TOP_CONTROL_FRACTION             (FA_BASE+27)
#define FA_LEFT_CONTROL_FRACTION            (FA_BASE+28)
#define FA_BOTTOM_CONTROL_FRACTION          (FA_BASE+29)
#define FA_RIGHT_CONTROL_FRACTION           (FA_BASE+30)


// Make the width the same as the width of a control
#define FA_WIDTH_OF_CONTROL (FA_BASE+31)

// Make the height the same as the height of a control
#define FA_HEIGHT_OF_CONTROL (FA_BASE+32)

// Specify top of title bat
#define FA_TOP_OF_CAPTION (FA_BASE+33)

// Horizontal and vertical offsets
#define FA_HORIZONTAL_OFFSET (FA_BASE+34)
#define FA_VERTICAL_OFFSET   (FA_BASE+35)



#define NO_NATURAL_SIZE  (-1)

// Manditory application resource IDs

#define STR_APP_SHELL_NAME	1
#define ICON_APP_SHELL		1

#endif

