//--------------------------------------------------------------------------------------------
//
//	Copyright (c) Microsoft Corporation, 1997 All Rights Reserved
//
//	Description:
//		AutoPC Simple Form and Control Interfaces
//
//	History: 
//		Umesh Madan	umeshm@microsoft.com	02/28/97 Created
//
//--------------------------------------------------------------------------------------------

#ifndef _ASDISP_H
#define _ASDISP_H
//--------------------------------------------------------------------------------------------
//
// DISPIDs
//
//--------------------------------------------------------------------------------------------
//
// Property DISPIDs common to all controls and forms
//
//
#define ASFC_DISPID_FIRST		    1000
//
// Identification properties
//
#define ASFC_DISPID_ID              1000            // the control's ID
#define ASFC_DISPID_NAME            1001            // the control's name
//
// Dimensions
//
#define ASFC_DISPID_LEFT			1005			// dimension: left
#define ASFC_DISPID_TOP			    1006			// dimension: top
#define ASFC_DISPID_WIDTH			1007			// dimension: width
#define ASFC_DISPID_HEIGHT			1008			// dimension: height
//
// Standard boolean properties
//
#define ASFC_DISPID_VISIBLE		    1010			// visibility
#define ASFC_DISPID_ENABLE			1011			// enabled or disabled
#define ASFC_DISPID_TABSTOP		    1012			// tab stop
#define ASFC_DISPID_HASUI			1013			// control has UI?
#define ASFC_DISPID_BORDER			1014			// control has border?
#define ASFC_DISPID_AUTOREDRAW		1015			// control auto-redraws itself, when props change
#define ASFC_DISPID_OPAQUE			1016			// is the control drawn opaque?
//
// Standard Graphics properties
//
#define ASFC_DISPID_FORECOLOR		1051			// forecolor used in drawing
#define ASFC_DISPID_BACKCOLOR		1052			// backcolor used to paint background
#define ASFC_DISPID_FONT            1053            // font used to draw text
#define ASFC_DISPID_AUTOSCALEFONT   1054
//
// Standard text properties
//
#define ASFC_DISPID_CAPTION		    1100			// the control's caption
//
// Standard pointer properties
//
#define ASFC_DISPID_CLASSMSGSINK    1120            // the control's class msg sink
#define ASFC_DISPID_PARENT          1121            // the control's parent
#define ASFC_DISPID_EVENTSINK       1122            // the control's event sink
#define ASFC_DISPID_USERDATA        1123            // any user defined data

#endif
