//+----------------------------------------------------------------------------
// 
// File:		cplalert.h
//
// Copyight:	(c) 1998, Microsoft Corporation
// 				All Rights Reserved
//				Infomation Contained Herein Is Propprietary and Confidential
//
// Contents: 	APC CPL Alert definitions
//
//-----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

// The main Control Panel application name. 
// Must be used for the Application Name when raising a control panel alert

#define APCCPL_CPLNAME  L"Setup"

// Control panel Alert Names implemented by the default Microsoft ControlPanel
// Should be passed in as the "AlertName" when raising alerts

#define APCCPL_ABOUTNAME    L"AboutAutoPC"

// Mask values wehn setting Alerts for the About ControlPanel applet

#define APCCPL_ABOUTMASK_POWER      0x0001

#ifdef __cplusplus
}
#endif

