//--------------------------------------------------------------------------------------------
//
//	Copyright (c) Microsoft Corporation, 1997 All Rights Reserved
//
//	Description:
//		AutoPC Simple Form Control extensions for control writers
//
//	History: 
//		Alec Barker  02/20/98 Created
//
//--------------------------------------------------------------------------------------------

#ifndef _ASFCCTLEXT_H
#define _ASFCCTLEXT_H

//--------------------------------------------------------------------------------------------
//
// Includes
//
//--------------------------------------------------------------------------------------------
#include <olectl.h>

//--------------------------------------------------------------------------------------------
//
// Declarations
//
//--------------------------------------------------------------------------------------------

DECLARE_INTERFACE(IASAccess);

//--------------------------------------------------------------------------------------------
//
// Guids
//
//--------------------------------------------------------------------------------------------

// The forms manager access interface

// {E1166208-AA0C-11d1-9B32-0000F8757D96}

DEFINE_GUID(IID_ASACCESS,
0xe1166208, 0xaa0c, 0x11d1, 0x9b, 0x32, 0x0, 0x0, 0xf8, 0x75, 0x7d, 0x96);

//--------------------------------------------------------------------------------------------
//
// Interfaces
//
//--------------------------------------------------------------------------------------------
//
// Interface for protected access into the forms manager objects
//
#undef	INTERFACE
#define	INTERFACE

DECLARE_INTERFACE_(IASAccess, IDispatch)
	{
    STDMETHOD(Enter) (THIS) PURE;
	STDMETHOD(Leave) (THIS) PURE;
	STDMETHOD(LeaveAll) (THIS_ long *pRef) PURE;
	STDMETHOD(ReEnter) (THIS_ long Ref) PURE;
	};

#endif

