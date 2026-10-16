//+---------------------------------------------------------------------------
//
//  Microsoft Windows
//  Copyright (C) Microsoft Corporation, 1992-1997. All rights reserved.
//
//  File:		shlguid.h
//
//	Purpose:
//		For shell-reserved GUID
//
//  The Win95 Shell has been allocated a block of 256 GUIDs,
// which follow the general format:
//
//  000214xx-0000-0000-C000-000000000046
//
#define DEFINE_SHLGUID(name, l, w1, w2) DEFINE_GUID(name, l, w1, w2, 0xC0,0,0,0,0,0,0,0x46)

//
// Class IDs        xx=00-DF
//
DEFINE_SHLGUID(CLSID_ShellDesktop,      0x00021400L, 0, 0);

//
// Interface IDs    xx=E0-FF
//
DEFINE_SHLGUID(IID_IContextMenu,    	0x000214E4L, 0, 0);
DEFINE_SHLGUID(IID_IShellFolder,    	0x000214E6L, 0, 0);
DEFINE_SHLGUID(IID_IEnumIDList,     	0x000214F2L, 0, 0);

DEFINE_SHLGUID(IID_IShellCommandUI,    	0x000214FEL, 0, 0);
DEFINE_SHLGUID(IID_IShellListView,    	0x000214FFL, 0, 0);
