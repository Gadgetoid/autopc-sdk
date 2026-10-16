/*******************************************************************************
 *
 *  File:
 *    VIOMDBASE.H
 *
 *  Description:
 *    Base interface and type declarations for the VIO mini-drivers
 *
 *  Original Author:
 *    Paul Horenberger
 *
 *  Modification History:
 *  $Log:   H:/AUTOPC/HOSTSW/PVCSARCH/INCLUDE/viomdbase.h_v  $
 * 
 *    Rev 1.2   May 28 1998 14:50:12   PHorenberger
 * Removed the IVIO_BufferMgr interface, and added the 
 * IVIO_MiniDriverManager and the IVIO_MiniDriverData interfaces
 * 
 *    Rev 1.1   Oct 08 1997 19:20:28   PHorenberger
 * Added in the IVIO_MiniDrvBufferMgr interface
 * 
 * 
 *    Rev 1.0   Sep 11 1997 15:54:16   PAULH
 * Initial revision.
 *
 *  Copyright (C) 1997 Vetronix Corp.
 ******************************************************************************/
#if (!defined __VIOMDBASE_H)
#define __VIOMDBASE_H 1

//------------------------------------------------------------------------------
//
// Declarations
//
//------------------------------------------------------------------------------
DECLARE_INTERFACE(IVIO_MiniDriverMgr);
DECLARE_INTERFACE(IVIO_MiniDriver);
DECLARE_INTERFACE(IVIO_MiniDriverData);
//------------------------------------------------------------------------------
//
// Interfaces
//
//------------------------------------------------------------------------------

// Minidriver manager interface
// This interface is used to allow the mindrivers to be initialized when the API 
// is started up.  
DECLARE_INTERFACE_(IVIO_MiniDriverMgr, IUnknown)
{
  // Start up the minidriver manager.
  STDMETHOD(StartManager)(PVOID pReserved) PURE;
};

// Base Mini-driver class. This is used to translate between the values that 
// are expected by a given IVIO_Device subclass and the raw information returned
// by the Vehicle Interface Hardware's device driver.  This is implemented by
// the vendor of the vehicle interface hardware for each device subclass that is 
// implemented in the API.
DECLARE_INTERFACE_(IVIO_MiniDriver, IUnknown)
{
  // Get data - corresponds to as IVIO_Device->GetData()
  STDMETHOD(GetData) (THIS_ IVIO_MiniDriverData *pInputData, 
                      IVIO_MiniDriverData **ppData, 
                      DWORD dwTimeout) PURE ;
  // Set data - same as IVIO_Device->SetData()
  STDMETHOD(SetData) (THIS_ IVIO_MiniDriverData *pInputData, 
                      DWORD dwTimeout) PURE;
  // Turn on/off notification by the minidriver
  STDMETHOD(SetNotify) (THIS_ HANDLE hNotifyEvent, 
                        IVIO_MiniDriverData *pInputData,
                        IVIO_MiniDriverData **ppReturnedData, DWORD dwFreq) PURE;
  // Generic IO control - for accessing mini-driver implementation specific functionality, can be NOP
  STDMETHOD(IOControl) (THIS_ DWORD dwCommandId, 
                          const PVOID pCommandData, DWORD cb, 
                          PVOID pReply, DWORD dwOutputSize, 
                          DWORD *pReplySize) PURE;
};

//
// Minidriver data interface.  This is what is used to communicate data between
// the minidrivers and the API objects.  A COM interface is used so that a user
// of the interface does not have to explicitly free the resources used by the
// object.  The resources will go be freed when the last reference is released,
// either by the creator of the object (generally the minidriver), or by the 
// consumer (generally the API object).
// WARNING: This interface is intended for use to move data from one layer to 
// another, copied, and then released.  No assumptions should be made about the 
// address of the data buffer remaining valid after the reference is released.
//
DECLARE_INTERFACE_(IVIO_MiniDriverData, IUnknown)
{
  // Get the address of the data buffer itself
  STDMETHOD(get_DataBuffer) (THIS_ PVOID *ppv) PURE;
  // Get the size of the buffer 
  STDMETHOD(get_DataBufferSize) (THIS_ DWORD *pcbDataBuffer) PURE;
};

#endif // inclue sentry
