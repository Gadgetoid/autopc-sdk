/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1997 - 1998 Microsoft Corporation

Module Name:

    IRSquirt.h

Abstract:

    Class ID and Interface IDs for using the IRSquirt COM object

-------------------------------------------------------------------*/

#ifndef _IRSQUIRT_H
#define _IRSQUIRT_H

// {DED1E976-DF14-11d1-BA0E-0000F8050ED3}
DEFINE_GUID(CLSID_IRSQUIRT,
    0xded1e976, 0xdf14, 0x11d1, 0xba, 0xe, 0x0, 0x0, 0xf8, 0x5, 0xe, 0xd3);

// {DED1E977-DF14-11d1-BA0E-0000F8050ED3}
DEFINE_GUID(IID_IRSQUIRT,
    0xded1e977, 0xdf14, 0x11d1, 0xba, 0xe, 0x0, 0x0, 0xf8, 0x5, 0xe, 0xd3);


#undef  INTERFACE
#define INTERFACE

DECLARE_INTERFACE_(IIRSquirt, IUnknown)
{
    STDMETHOD(Transfer)             (THIS_ IfmManage *pFrmMgr,  // caller's forms manager interface
                                        WORD wNum,              // number of OIDs to send, zero to receive
                                        CEOID *rgOID,           // array of OIDs to send
                                        BSTR bstrCaption) PURE; // NULL to use calling app caption, valid BSTR otherwise

    STDMETHOD(IRAvailable)          (THIS) PURE;
};


#endif //_IRSQUIRT_H
