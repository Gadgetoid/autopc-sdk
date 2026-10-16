/*
    PNGUID.H

    Defines all GUIDs for the Position and Navigation API.

    Copyright (c) 1996, 1997 Microsoft Corporation, All rights reserved.

*/

#ifndef PNGUID_H
#define PNGUID_H

#ifdef INITGUIDS
#include <initguid.h>
#endif

#ifndef LPLPVOID
typedef LPVOID* LPLPVOID;
#endif

//GUID definition, uniquely created with GUIDGEN.
// {0EA8243A-E7AD-11ce-8CCD-00AA006BC0C9}
//extern "c" const GUID CDECL __based(__segname("_CODE")) CLSID_PosNav \= {0xea8243a, 0xe7ad, 0x11ce, {0x8c, 0xcd, 0x0, 0xaa, 0x0, 0x6b, 0xc0, 0xc9} }
DEFINE_GUID(CLSID_PosNav, 0xea8243a, 0xe7ad, 0x11ce, 0x8c, 0xcd, 0x0, 0xaa, 0x0, 0x6b, 0xc0, 0xc9);

//Interface for PNAPI V1.00 and V1.01 for Win32 - Summer 1996
//Also for V1.10 for WinCE - Autumn 1997.
// {A95CC110-1FA4-11cf-8CE0-00AA006BC0C9}
DEFINE_GUID(IID_IPosNav, 0xa95cc110, 0x1fa4, 0x11cf, 0x8c, 0xe0, 0x0, 0xaa, 0x0, 0x6b, 0xc0, 0xc9);

#endif
