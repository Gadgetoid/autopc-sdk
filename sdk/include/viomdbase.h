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
/**
 * This interface is used to initialize the mini-drivers when the API is started.
 */
DECLARE_INTERFACE_(IVIO_MiniDriverMgr, IUnknown)
{
  // Start up the minidriver manager.
  /**
   * This method starts the mini-driver manager.
   *
   * @param pReserved [in] Reserved.
   *
   * @return An appropriate HRESULT value is returned.
   */
  STDMETHOD(StartManager)(PVOID pReserved) PURE;
};

// Base Mini-driver class. This is used to translate between the values that 
// are expected by a given IVIO_Device subclass and the raw information returned
// by the Vehicle Interface Hardware's device driver.  This is implemented by
// the vendor of the vehicle interface hardware for each device subclass that is 
// implemented in the API.
/**
 * Use this interface to translate between the values that are expected by a specified IVIO_Device
 * subclass and the raw information returned by the vehicle interface hardware's device driver. This
 * interface is created by the vendor of the vehicle interface hardware for each device subclass
 * that is implemented in the API.
 */
DECLARE_INTERFACE_(IVIO_MiniDriver, IUnknown)
{
  // Get data - corresponds to as IVIO_Device->GetData()
  /**
   * This method corresponds to IVIO_Device::GetData.
   *
   * @param pInputData [in] Pointer to an IVIO_MiniDriverData interface that contains the input data
   *   from the device.
   * @param ppData [out] Pointer to a pointer to an IVIO_MiniDriverData interface that contains the
   *   data from the device.
   * @param dwTimeout [in] Specifies, in milliseconds, the amount of time to wait for a reply to the
   *   request for data. This method retrieves the current data from the device.
   *
   * @return An appropriate HRESULT value is returned.
   */
  STDMETHOD(GetData) (THIS_ IVIO_MiniDriverData *pInputData, 
                      IVIO_MiniDriverData **ppData, 
                      DWORD dwTimeout) PURE ;
  // Set data - same as IVIO_Device->SetData()
  /**
   * This method corresponds to IVIO_Device::SetData.
   *
   * @param pInputData [in] Pointer to an IVIO_MiniDriverData interface that contains the input data
   *   from the device.
   * @param dwTimeout [in] Specifies, in milliseconds, the amount of time to wait for the request to
   *   complete.
   *
   * @return An appropriate HRESULT value is returned.
   */
  STDMETHOD(SetData) (THIS_ IVIO_MiniDriverData *pInputData, 
                      DWORD dwTimeout) PURE;
  // Turn on/off notification by the minidriver
  /**
   * This method begins timed notification of an API device component.
   *
   * @param hNotifyEvent [in] Handle to an event that is used by the mini-driver to notify the API
   *   that a new notification is ready from the mini-driver.
   * @param pInputData [in] Pointer to an IVIO_MiniDriverData interface that contains the input data
   *   from the device.
   * @param ppReturnedData [in] Pointer to a pointer to an IVIO_MiniDriverData interface that is
   *   stored when a notification is ready.
   * @param dwInterval [in] Specifies, in milliseconds, the amount of time to send notifications to
   *   the device component.
   *
   * @return An appropriate HRESULT value is returned.
   */
  STDMETHOD(SetNotify) (THIS_ HANDLE hNotifyEvent, 
                        IVIO_MiniDriverData *pInputData,
                        IVIO_MiniDriverData **ppReturnedData, DWORD dwFreq) PURE;
  // Generic IO control - for accessing mini-driver implementation specific functionality, can be NOP
  /**
   * This method accesses mini-driver implementation-specific functionality.
   *
   * @param dwCommandId [in] Specifies the device driver-specific command identifier. This information
   *   is furnished by the vendor of the vehicle interface hardware device driver.
   * @param pCommandData [in] Pointer to a buffer that contains driver-specific data for the specified
   *   command specified in dwCommandId.
   * @param cb [in] Size of the buffer referenced by the pCommandData parameter.
   * @param pReply [out] Pointer to a buffer to contain information returned by the device driver.
   * @param dwOutputSize [in] Specifies the size of the buffer referenced by the pReply parameter.
   * @param pReplySize [out] Pointer to a DWORD value that contains the size of the data set stored in
   *   the buffer referenced by pReply.
   *
   * @return One of the values described in the following table is returned. Value Description S_OK
   *   The function was executed successfully. Reply data from the device driver is stored in the pReply
   *   buffer. E_POINTER Either the pCommandData, the pReply, or the pReplySize pointer is invalid.
   *   E_INVALID The value in dwCommandId is invalid for the device driver or the value given in
   *   dwOutputSize is too small for the amount of data in the reply. The correct size is stored in the
   *   value referenced by pReplySize. E_UNEXPECTED An unexpected error occurred in the request to the
   *   device driver.
   */
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
/**
 * Use this interface to return data buffer information.
 */
DECLARE_INTERFACE_(IVIO_MiniDriverData, IUnknown)
{
  // Get the address of the data buffer itself
  /**
   * This method gets the address of a data buffer.
   *
   * @param ppv [in] Pointer to a void pointer to the buffer that contains driver-specific data.
   *
   * @return An appropriate HRESULT value is returned.
   */
  STDMETHOD(get_DataBuffer) (THIS_ PVOID *ppv) PURE;
  // Get the size of the buffer 
  /**
   * This method gets the size of the data buffer.
   *
   * @param pcbDataBuffer [in] Pointer to the size of the buffer that contains driver-specific data.
   *
   * @return An appropriate HRESULT value is returned.
   */
  STDMETHOD(get_DataBufferSize) (THIS_ DWORD *pcbDataBuffer) PURE;
};

#endif // inclue sentry
