/*******************************************************************************
 *
 *  File:
 *    VIOBASE.H
 *
 *  Description:
 *    Header file containing declarations of the base VIO COM Interfaces
 *    This file will then be included by the files that implement the 
 *    actual components used in the VIO API.
 *
 *  Original Author:
 *    Paul Horenberger
 *
 *  Modification History:
 *    $Log:   H:/AUTOPC/HOSTSW/PVCSARCH/INCLUDE/VIOBASE.H_V  $
 * 
 *    Rev 1.12   May 28 1998 14:39:34   PHorenberger
 * Changed  the type returned from the Next() method of IVIO_EnumDiagnosticEntries
 * to return an array of IVIO_DataValue objects
 * 
 *    Rev 1.11   Feb 13 1998 16:46:04   PHorenberger
 * Added the diagnostic item and 
 * diagnostic entry interfaces
 * 
 *    Rev 1.10   Nov 10 1997 11:41:46   PHorenberger
 * New interface declarations that incorporate changes made to the
 * IVIO_Vehicle interface specification.
 * 
 *    Rev 1.9   Oct 08 1997 19:16:52   PHorenberger
 * Changed the IVIO_Device and IVIO_EventSink interfaces
 * so that the functions that send or receive data to the vehicle
 * don't have to send byte counts
 * 
 *    Rev 1.8   Sep 23 1997 12:21:10   PAULH
 * Removed typedefs and enums from this file and 
 * added them to new file "viotype.h"
 * 
 *    Rev 1.7   Aug 05 1997 18:19:42   PAULH
 * Changes to correlate with the API Spec. submitted to Microsoft
 * 
 *    Rev 1.6   Jul 17 1997 09:47:00   PAULH
 * Changes to project to allow build of API with the WinCE 2.0 Beta SDK rather than straight Win32
 * 
 *    Rev 1.5   Jul 11 1997 18:51:52   PAULH
 * 
 *    Rev 1.4   Jul 08 1997 13:55:24   PAULH
 * Changed a few things as the API implementation has proceeded
 * 
 *    Rev 1.3   Jul 01 1997 17:39:34   PAULH
 * Baseline of final VIO API Header file.  This may be altered depending on the feedback from Microsoft
 * 
 *    Rev 1.2   Jun 16 1997 17:46:46   PAULH
 * Initial Implementation of the VIO API Server DLL.  This includes a stubbed out implementation of the IVIO_Ioctl interface and the framework for implementing the rest of the VIO API COM Interfaces
 * 
 *    Rev 1.1   Jun 12 1997 14:48:38   PAULH
 * Made the file heading consistent with all of the other source files
 * 
 *    Rev 1.0   Jun 09 1997 16:36:08   PAULH
 * Initial revision.
 * 
 *  Copyright (C) 1997 Vetronix Corp.
 ******************************************************************************/
#if (!defined __VIOBASE_H)
#define __VIOBASE_H 1

//------------------------------------------------------------------------------
//
// Declarations
//
//------------------------------------------------------------------------------
DECLARE_INTERFACE(IVIO_Vehicle);
DECLARE_INTERFACE(IVIO_EnumMetrics);
DECLARE_INTERFACE(IVIO_EnumMaintenanceItems);
DECLARE_INTERFACE(IVIO_EnumMaintenanceEntry);
DECLARE_INTERFACE(IVIO_EnumDevices);
DECLARE_INTERFACE(IVIO_EnumDiagnosticItems);
DECLARE_INTERFACE(IVIO_EnumDiagnosticEntry);
DECLARE_INTERFACE(IVIO_DataValue);
DECLARE_INTERFACE(IVIO_EventSink);
DECLARE_INTERFACE(IVIO_Device);
DECLARE_INTERFACE(IVIO_Ioctl);
DECLARE_INTERFACE(IVIO_MiniDriver);


//------------------------------------------------------------------------------
//
// Interfaces
//
//------------------------------------------------------------------------------
// Classes to define
// IVIO_Vehicle interface declaration:
// The purpose of this interface is to provide information about the vehicle
// as a whole.  Examples of this information are vehicle year, make, model,
// VIN Number, and other specifications (i.e. recommended tire pressure, fuel
// capacity, etc.)
// Other attributes of this class are a collection of maintenance information
// (oil change interval, tune-up interval, tire rotation, etc.)
DECLARE_INTERFACE_(IVIO_Vehicle, IUnknown)
{
  // Get an enumerator for the vehicle metrics
  STDMETHOD(get_Metrics) (THIS_ IVIO_EnumMetrics **ppMetricsEnum) PURE;

  // Get an enumerator for the vehicle maintenance entries
  STDMETHOD(get_MaintenanceItems) 
                     (THIS_ IVIO_EnumMaintenanceItems **ppMaintItemsEnum) PURE;

  // Get an enumerator for the available componenents exposing the IVIO_Device 
  // interface on the vehicle.
  STDMETHOD(get_Devices) (THIS_ IVIO_EnumDevices **ppDevicesEnum) PURE;
};


// IVIO_EnumMetrics interface declaration:
// This is an OLE enumeration interface that allows enumeration of all available
// vehicle attributes.  It is returned by the IVIO_Vehicle interface by the 
// get_Metrics() method.
DECLARE_INTERFACE_(IVIO_EnumMetrics, IUnknown)
{
  // Reset the enumerator to the beginning of the enumeration list
  STDMETHOD(Reset) (THIS_) PURE;

  // Skip the enumerator n items in the enumeration list
  STDMETHOD(Skip) (THIS_ ULONG cMetrics) PURE;

  // Attempt to seek to a certain metric entry in the enumeration list
  STDMETHOD(Seek) (THIS_ DWORD dwMetricsID) PURE;

  // Retrieve the next n vehicle metrics from the enumeration list
  STDMETHOD(Next) (THIS_ ULONG cMetrics, IVIO_DataValue **rgValueArray, 
                   ULONG *pcMetricsFetched) PURE;

  // Add a new vehicle metric to the collection
  STDMETHOD(Add) (THIS_ DWORD dwMetricsID) PURE;

  // Set the value of the current vehicle metric 
  STDMETHOD(Set) (THIS_ LPVARIANT pValue) PURE;

  // Clone the enumerator with the same state as the current one.
  STDMETHOD(Clone) (THIS_ IVIO_EnumMetrics **ppMetricsEnumerator) PURE;
};

// IVIO_EnumMaintenanceItems interface declaration:
// This is an OLE enumeration interface that allows enumeration of all available
// vehicle maintenance items .  It is returned by the IVIO_Vehicle interface by 
// the get_MaintenanceItems() method.
DECLARE_INTERFACE_(IVIO_EnumMaintenanceItems, IUnknown)
{
  // Reset the enumerator to the beginning of the enumeration list
  STDMETHOD(Reset) (THIS_) PURE;

  // Skip the enumerator n items in the enumeration list
  STDMETHOD(Skip) (THIS_ ULONG cItems) PURE;

  // Attempt to seek to a certain maintenance item in the enumeration list
  STDMETHOD(Seek) (THIS_ DWORD dwItemID) PURE;

  // Retrieve the next n maintenance items from the enumeration list
  STDMETHOD(Next) (THIS_ ULONG cItems, IVIO_DataValue **rgValueArray, 
                   ULONG *pcItemsFetched) PURE;

  // Add a new maintenance item to the collection
  STDMETHOD(Add) (THIS_ DWORD dwItemID) PURE;

  // Clone the enumerator with the same state as the current one.
  STDMETHOD(Clone) (THIS_ IVIO_EnumMaintenanceItems **ppItemsEnumerator) PURE;
};

// IVIO_EnumMaintenanceEntry interface declaration:
// This is an OLE enumeration interface that allows enumeration of the 
// attributes of a maintenance entry.  It is returned by the 
// IVIO_EnumMaintenanceItems interface's Next() method
DECLARE_INTERFACE_(IVIO_EnumMaintenanceEntry, IUnknown)
{
  // Reset the enumerator to the beginning of the enumeration list
  STDMETHOD(Reset) (THIS_) PURE;

  // Skip the enumerator n items in the enumeration list
  STDMETHOD(Skip) (THIS_ ULONG cAttributes) PURE;

  // Attempt to seek to a certain maintenance entry attribute in the enumeration
  // list
  STDMETHOD(Seek) (THIS_ DWORD dwItemID) PURE;

  // Retrieve the next n maintenance entry attributes from the enumeration list
  STDMETHOD(Next) (THIS_ ULONG cAttributes, IVIO_DataValue **rgValueArray, 
                   ULONG *pcAttributesFetched) PURE;

  // Set the value of the current maintenance entry attribute
  STDMETHOD(Set) (THIS_ LPVARIANT pValue) PURE;

  // Clone the enumerator with the same state as the current one.
  STDMETHOD(Clone) (THIS_ IVIO_EnumMaintenanceEntry **ppEntryEnumerator) PURE;
};

// IVIO_EnumDevices interface declaration:
// This is an OLE enumeration interface that allows enumeration of all available
// components that expose the IVIO_Device interface.  It is returned by the 
// IVIO_Vehicle interface using the get_Devices() method.
DECLARE_INTERFACE_(IVIO_EnumDevices, IUnknown)
{
  // Reset the enumerator to the beginning of the enumeration list
  STDMETHOD(Reset) (THIS_) PURE;

  // Skip the enumerator n items in the enumeration list
  STDMETHOD(Skip) (THIS_ ULONG cDevices) PURE;

  // Attempt to seek to a certain device in the enumeration list
  STDMETHOD(Seek) (THIS_ REFCLSID rclsid) PURE;

  // Retrieve the next n devices from the enumeration list
  STDMETHOD(Next) (THIS_ ULONG cDevices, LPCLSID *rgDeviceArray, 
                   ULONG *pcDevicesFetched) PURE;

  // Clone the enumerator with the same state as the current one.
  STDMETHOD(Clone) (THIS_ IVIO_EnumDevices **ppDeviceEnumerator) PURE;
};

// IVIO_EnumDiagnosticItems interface declaration:
// This is an OLE enumeration interface that allows enumeration of all available
// diagnostic trouble codes from the CLSID_TROUBLE_CODES object's GetData() 
// method as the object IUnknown interface.
DECLARE_INTERFACE_(IVIO_EnumDiagnosticItems, IUnknown)
{
  // Reset the enumerator to the beginning of the enumeration list
  STDMETHOD(Reset) (THIS_) PURE;

  // Skip the enumerator n items in the enumeration list
  STDMETHOD(Skip) (THIS_ ULONG cItems) PURE;

  // Retrieve the next n diagnostic items from the enumeration list
  STDMETHOD(Next) (THIS_ ULONG cItems, IVIO_DataValue **rgValueArray,
                   ULONG *pcItemsFetched) PURE;

  // Clone the enumerator with the same state as the current one.
  STDMETHOD(Clone) (THIS_ IVIO_EnumDiagnosticItems **ppItemsEnumerator) PURE;
};

// IVIO_EnumDiagnosticEntry interface declaration:
// This is an OLE enumeration interface that allows enumeration of the 
// attributes of a diagnostic item.  An object that exposes this interface is
// returned by the Next() method in the IVIO_EnumDiagnosticItems interface.
DECLARE_INTERFACE_(IVIO_EnumDiagnosticEntry, IUnknown)
{
  // Reset the enumerator to the beginning of the enumeration list
  STDMETHOD(Reset) (THIS_) PURE;

  // Skip the enumerator n items in the enumeration list
  STDMETHOD(Skip) (THIS_ ULONG cAttributes) PURE;

  // Attempt to seek to a certain diagnostic entry attribute in the enumeration
  // list
  STDMETHOD(Seek) (THIS_ DWORD dwItemID) PURE;

  // Retrieve the next n diagnostic entry attributes from the enumeration list
  STDMETHOD(Next) (THIS_ ULONG cAttributes, IVIO_DataValue **rgValueArray, 
                   ULONG *pcAttributesFetched) PURE;

  // Clone the enumerator with the same state as the current one.
  STDMETHOD(Clone) (THIS_ IVIO_EnumDiagnosticEntry **ppEntryEnumerator) PURE;
};


// IVIO_DataValue interface declaration:
// This is the interface that is returned by the Next() methods in the 
// IVIO_EnumMetrics, IVIO_EnumMaintenanceItems, and IVIO_EnumMaintenanceEntry
// interfaces to return data back to the requesting application.  See the VIO
// API specification for details on the specific data values and their meanings
DECLARE_INTERFACE_(IVIO_DataValue, IUnknown)
{
  // Get the data item's ID
  STDMETHOD(get_ItemID)(THIS_ LPDWORD pItemID) PURE;

  // Get the value of the data item.
  // Note:  The calling application must call VariantClear() on the value set
  //        by this method in order to free up any resources in use by the 
  //        variant.
  STDMETHOD(get_DataValue)(THIS_ LPVARIANT pDataValue) PURE;
};

// IVIO_EventSink class declaration:
// This is an abstract base class used to create notification
// objects that are called from an IVIO_Device instance when the 
// IVIO_Device->SetNotify() method is invoked
DECLARE_INTERFACE_(IVIO_EventSink, IUnknown)
{
  // Method that is called from the IVIO_Device instance
  // Need to determine specific parameters that are needed
  STDMETHOD(ReceiveData) (THIS_ LPVARIANT pData, LPARAM lParam) PURE;
};

// IVIO_Device class declaration:
// This is the base class that all vehicle information is derived from
DECLARE_INTERFACE_(IVIO_Device, IUnknown)
{
  //
  // Get Properties of a IVIO_Device instance
  //
  // Get the metrics of this IVIO_Device
  STDMETHOD(get_Metrics) (THIS_ LPVIODEVICEMETRICS pVIODeviceMetrics) PURE;
  // Get the status of this IVIO_Device
  STDMETHOD(get_Status) (THIS_ DWORD *pStatus) PURE;
  // Get the access mode of this IVIO_Device (shared, exclusive)
  STDMETHOD(get_AccessMode) (THIS_ DWORD dwMode, DWORD *pAccessMode) PURE;
  // Set the access mode of this IVIO_Device (shared, exclusive)
  STDMETHOD(set_AccessMode) (THIS_ DWORD dwMode, DWORD dwAccessMode) PURE;
 
  // 
  // Send/Retrieve data from the device itself
  //
  // Read data from a IVIO_Device instance (read data from vehicle) 
  STDMETHOD(GetData) (THIS_ LPVARIANT pData, DWORD dwTimeout) PURE;
  // Send data to a IVIO_Device instance (send control data to vehicle)
  STDMETHOD(SetData) (THIS_ const LPVARIANT pData, DWORD dwTimeout) PURE;
  
  //
  // Add an event sink to a given device
  //
  // Add a notification sink to a IVIODevice instance
  STDMETHOD(SetNotify) (THIS_ const LPVARIANT pParameterData, 
                        IVIO_EventSink *pEventSink, DWORD dwFreq) PURE;  
};

// Low-level, straight to the device driver type of interface
// This facilitates applications sending device driver-specific commands
// to the VIO device driver
DECLARE_INTERFACE_(IVIO_Ioctl, IUnknown)
{
  // Similar to the standard DeviceIoControl API
  STDMETHOD(DoCommand) (THIS_ DWORD dwCommandId, const PVOID pCommandData, 
                        DWORD cb, PVOID pReply, DWORD dwOutputSize, 
                        DWORD *pReplySize) PURE;

};

#endif // include sentry
