/*
    IPOSNAV.H

    Definition of an IPosNav interface for a PosNav object.
    This custom interface is only supported from DLL-based objects.

    Copyright (c) 1996 Microsoft Corporation, All rights reserved.
*/

//We use the OLE 2.0 macro to define a new interface.

#ifndef _INC_IPOSNAV
#define _INC_IPOSNAV

#include "pngen.h"

#undef  INTERFACE
#define INTERFACE IPosNav

#ifndef LPLPVOID
    typedef LPVOID* LPLPVOID;
#endif

DECLARE_INTERFACE_(IPosNav, IUnknown)
{
    //IUnknown members.
    STDMETHOD(QueryInterface)   (THIS_ REFIID, LPLPVOID) PURE;
    STDMETHOD_(ULONG, AddRef)   (THIS) PURE;
    STDMETHOD_(ULONG, Release)  (THIS) PURE;

    //IPosNav members.
    STDMETHOD(FindDevices) (ppPNDEVICE,
                                 pDWORD) PURE;

    STDMETHOD(DeleteDeviceList)    (pPNDEVICE) PURE;

    STDMETHOD(OpenDevice)  (phPNDevice,
                                 pPNDEVICE) PURE;

    STDMETHOD(CloseDevice)      (hPNDevice) PURE;

//    STDMETHOD(ResetDevice)  (hPNDevice,
//                                 PNReset_t) PURE;

//    STDMETHOD(GetVersion)  (pDWORD,
//                                 pDWORD) PURE;

    STDMETHOD(SetData)     (hPNDevice,
                                 LPVOID,
                                 DWORD,
                                 PNData_t) PURE;

//    STDMETHOD(SetPosition) (hPNDevice,
//                                 pPNPOSLLA) PURE;

//    STDMETHOD(SetTime)     (hPNDevice,
//                                 pPNTM) PURE;

    STDMETHOD(GetData)     (hPNDevice,
                                 LPVOID,
                                 DWORD,
                                 PNData_t) PURE;

//    STDMETHOD(GetPosition) (hPNDevice,
//                                 pPNPOSITION) PURE;

//    STDMETHOD(GetVelocity) (hPNDevice,
//                                 pPNVELOCITY) PURE;

//    STDMETHOD(GetDeviceState)  (hPNDevice,
//                                     pPNDEVSTATE) PURE;

//    STDMETHOD(GetAccuracy) (hPNDevice,
//                                 pPNACCURACY) PURE;

    STDMETHOD(StartCall)   (hPNDevice,
                                 PNData_t,
                                 DWORD) PURE;

    STDMETHOD(StopCall)    (hPNDevice,
                                 PNData_t) PURE;

    STDMETHOD(StartDirectCall) (hPNDevice,
                                     PNData_t,
                                     DWORD,
                                     HWND) PURE;

    STDMETHOD(StopDirectCall)  (hPNDevice,
                                     PNData_t) PURE;

//    STDMETHOD(LLAToXYZ)    (pPNPOSXYZ,
//                                 const pPNPOSLLA,
//                                 PNDatum_t) PURE;

//    STDMETHOD(XYZToLLA)    (pPNPOSLLA,
//                                 const pPNPOSXYZ,
//                                 PNDatum_t) PURE;

//    STDMETHOD(DatumToDatum)    (pPNPOSLLA,
//                                     PNDatum_t,
//                                     PNDatum_t) PURE;

    STDMETHOD(DegreesToRadians)    (pPNPOSLLA) PURE;

    STDMETHOD(RadiansToDegrees)    (pPNPOSLLA) PURE;

    STDMETHOD(VelocityToBearing)   (pPNVELBEAR,
                                         const pPNVELENU) PURE;

    STDMETHOD(BearingToVelocity)   (pPNVELENU,
                                         const pPNVELBEAR) PURE;

    STDMETHOD(PNTMToWintm) ( SYSTEMTIME&,
                                  const PNTM& ) PURE;

    STDMETHOD(WintmToPNTM) ( PNTM&,
                                  const SYSTEMTIME& ) PURE;
};

typedef IPosNav *pIPosNav;

#endif
