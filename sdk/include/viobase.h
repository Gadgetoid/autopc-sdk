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
/**
 * This interface exposes information about a vehicle.
 */
DECLARE_INTERFACE_(IVIO_Vehicle, IUnknown)
{
  // Get an enumerator for the vehicle metrics
  /**
   * This method gets the enumeration interface that is used to access information that describes a
   * vehicle.
   *
   * @param ppMetric [out] Pointer to a pointer to an IVIO_EnumMetrics interface that is used to get
   *   and set vehicle attributes.
   *
   * @return S_OK indicates that the vehicle metrics enumerator was retrieved successfully. E_POINTER
   *   indicates that the ppMetrics pointer is invalid.
   *
   * The calling process must release the returned interface and its resources.
   */
  STDMETHOD(get_Metrics) (THIS_ IVIO_EnumMetrics **ppMetricsEnum) PURE;

  // Get an enumerator for the vehicle maintenance entries
  /**
   * This method gets the enumeration interface that is used to access maintenance information for a
   * vehicle.
   *
   * @param ppItems [out] Pointer to a pointer to an IVIO_EnumMaintenanceItems interface that is used
   *   to get and set maintenance information for a vehicle.
   *
   * @return S_OK indicates that the vehicle maintenance item enumerator was retrieved successfully.
   *   E_POINTER indicates that the ppItems pointer is invalid.
   *
   * The calling process must release the returned interface and its resources.
   */
  STDMETHOD(get_MaintenanceItems) 
                     (THIS_ IVIO_EnumMaintenanceItems **ppMaintItemsEnum) PURE;

  // Get an enumerator for the available componenents exposing the IVIO_Device 
  // interface on the vehicle.
  /**
   * This method gets the enumeration interface that is used to access available components that
   * expose the IVIO_Device interface in the vehicle.
   *
   * @param ppDevices [out] Pointer to the pointer to an IVIO_EnumDevices interface that is used to
   *   return the available devices for a vehicle.
   *
   * @return S_OK indicates that the vehicle's device enumerator was retrieved successfully. E_POINTER
   *   indicates that the ppDevices pointer is invalid.
   *
   * The calling process must release the returned interface and its resources.
   */
  STDMETHOD(get_Devices) (THIS_ IVIO_EnumDevices **ppDevicesEnum) PURE;
};


// IVIO_EnumMetrics interface declaration:
// This is an OLE enumeration interface that allows enumeration of all available
// vehicle attributes.  It is returned by the IVIO_Vehicle interface by the 
// get_Metrics() method.
/**
 * The IVIO_EnumMetrics interface is an enumeration interface that exposes information about a
 * vehicle.
 */
DECLARE_INTERFACE_(IVIO_EnumMetrics, IUnknown)
{
  // Reset the enumerator to the beginning of the enumeration list
  /**
   * This method resets the enumerator back to the beginning of the collection.
   *
   * @return S_OK indicates that the enumerator was set to the beginning of the collection. S_FALSE
   *   indicates that the enumerator was not set to the beginning of the collection.
   */
  STDMETHOD(Reset) (THIS_) PURE;

  // Skip the enumerator n items in the enumeration list
  /**
   * This method skips over the specified number of items in the vehicle metrics collection.
   *
   * @param cItems [in] Number of items to skip in the collection.
   *
   * @return One of the values described in the following table is returned. Value Description S_OK
   *   The number of elements skipped is equal to the value specified in cItems. S_FALSE The number of
   *   elements skipped is less than the value specified in cItems. E_OUTOFMEMORY The application is out
   *   of memory. E_INVALIDARG The value of cItems is invalid. E_UNEXPECTED An unexpected error
   *   occurred.
   */
  STDMETHOD(Skip) (THIS_ ULONG cMetrics) PURE;

  // Attempt to seek to a certain metric entry in the enumeration list
  /**
   * This method searches for a metrics item identifier in the vehicle metrics collection.
   *
   * @param nItemId [in] Identifier of the vehicle metrics collection member to search for. It is one
   *   of the following values: VIOVEHICLEMETRIC_CYLINDERCOUNT VIOVEHICLEMETRIC_DISPLACEMENT
   *   VIOVEHICLEMETRIC_FUELDELIVERY VIOVEHICLEMETRIC_FUELTYPE VIOVEHICLEMETRIC_MAKE
   *   VIOVEHICLEMETRIC_MANUFACTURER VIOVEHICLEMETRIC_MODEL VIOVEHICLEMETRIC_TRANSMISSION
   *   VIOVEHICLEMETRIC_TRANSMISSION_GEARS VIOVEHICLEMETRIC_VIN VIOVEHICLEMETRIC_YEAR
   *
   * @return S_OK indicates that the vehicle metrics item was retrieved successfully. The enumerator
   *   is set to the position of the specified metric. E_FAIL indicates that the application is unable
   *   to find the specified item identifier. The enumerator's position is unchanged.
   *
   * Use the IVIO_EnumMetrics::Next and IVIO_EnumMetrics::Set methods to read and write metrics data.
   */
  STDMETHOD(Seek) (THIS_ DWORD dwMetricsID) PURE;

  // Retrieve the next n vehicle metrics from the enumeration list
  /**
   * This method retrieves the specified number of items in the enumeration sequence.
   *
   * @param cItems [in] Number of items to retrieve.
   * @param rgItemsArray [out] Array of IVIO_DataValue pointers where retrieved maintenance entry
   *   items are stored.
   * @param pcItemsFetched [out] Pointer to a ULONG that contains the number of elements actually
   *   returned. If cItems is 1, this parameter can be NULL. If cItems is greater than 1, this parameter
   *   must be a valid pointer.
   *
   * @return One of the values described in the following table is returned. Value Description S_OK
   *   The application successfully retrieved the number of IVIO_DataValue interfaces specified in
   *   cItems. The value referenced by pcItemsFetched is set to cItems. S_FALSE The application returned
   *   fewer IVIO_DataValue interfaces than were specified in cItems. The value referenced by
   *   pcItemsFetched is set to the number of interfaces found. The members of rgItemsArray that were
   *   not set are set to NULL. E_OUTOFMEMORY The application is out of memory. E_UNEXPECTED An
   *   unexpected error occurred. E_INVALIDARG The value of cItems is invalid, or pcItemsFetched is NULL
   *   and cItems is greater than 1. E_POINTER Either the rgItemsArray pointer is invalid or the
   *   pcItemsFetched pointer is invalid.
   *
   * The application must release the interfaces returned in rgItemsArray when it is finished with
   * them.
   */
  STDMETHOD(Next) (THIS_ ULONG cMetrics, IVIO_DataValue **rgValueArray, 
                   ULONG *pcMetricsFetched) PURE;

  // Add a new vehicle metric to the collection
  /**
   * This method adds a new entry in the vehicle metrics collection. The new entry identifier matches
   * the value of nItemId.
   *
   * @param nItemId [in] Identifier of the vehicle metrics collection member to add. It is one of the
   *   following values: VIOVEHICLEMETRIC_CYLINDERCOUNT VIOVEHICLEMETRIC_DISPLACEMENT
   *   VIOVEHICLEMETRIC_FUELDELIVERY VIOVEHICLEMETRIC_FUELTYPE VIOVEHICLEMETRIC_MAKE
   *   VIOVEHICLEMETRIC_MANUFACTURER VIOVEHICLEMETRIC_MODEL VIOVEHICLEMETRIC_TRANSMISSION
   *   VIOVEHICLEMETRIC_TRANSMISSION_GEARS VIOVEHICLEMETRIC_VIN VIOVEHICLEMETRIC_YEAR
   *
   * @return One of the values described in the following table is returned. Value Description S_OK
   *   The vehicle item was added successfully. The enumerator is set to the position of the new metric.
   *   S_FALSE The item is already in the enumeration list. The enumeration position is unchanged.
   *   E_FAIL The application is unable to add the item to the enumeration list.
   *
   * The new entry identifier must match the metrics item identifier in nItemId.
   *
   * Call the IVIO_EnumMetrics::Set method after calling this method to set an initial value for the
   * new metric item.
   */
  STDMETHOD(Add) (THIS_ DWORD dwMetricsID) PURE;

  // Set the value of the current vehicle metric 
  /**
   * This method sets the value of the current item referenced by the enumerator.
   *
   * @param pValue [in] Pointer to the VARIANT that contains the new value. Use a VT_BSTR to set the
   *   following three values. A VT_BSTR is a 32-bit character string. - VIOVEHICLEMETRIC_MAKE:
   *   Specifies the make of the vehicle. - VIOVEHICLEMETRIC_MODEL: Specifies the model of the vehicle.
   *   - VIOVEHICLEMETRIC_VIN: Specifies the vehicle identification number (VIN) number. Use a VT_UI4 to
   *   set the following values. A VT_UI4 is an unsigned long integer. - VIOVEHICLEMETRIC_YEAR:
   *   Specifies the year of the vehicle. - VIOVEHICLEMETRIC_MANUFACTURER: Specifies the manufacturer
   *   enumeration. It is one of the following values: VIOMANUFACTURER_ALFA_LANCIA
   *   VIOMANUFACTURER_ASTON_MARTIN VIOMANUFACTURER_AUDI VIOMANUFACTURER_BERTONE VIOMANUFACTURER_BMW
   *   VIOMANUFACTURER_CHRYSLER VIOMANUFACTURER_DAIHATSU VIOMANUFACTURER_DIAMOND_STAR_MOTORS
   *   VIOMANUFACTURER_FERRARI VIOMANUFACTURER_FORD VIOMANUFACTURER_FUJI_HEAVY_INDUSTRIES
   *   VIOMANUFACTURER_GM_CARS VIOMANUFACTURER_GM_TRUCKS VIOMANUFACTURER_GM_SATURN VIOMANUFACTURER_HONDA
   *   VIOMANUFACTURER_HYUNDAI VIOMANUFACTURER_ISUZU VIOMANUFACTURER_JAGUAR VIOMANUFACTURER_KIA
   *   VIOMANUFACTURER_LAMBORGHINI VIOMANUFACTURER_LOTUS VIOMANUFACTURER_MASERATI VIOMANUFACTURER_MAZDA
   *   VIOMANUFACTURER_MERCEDES_BENZ VIOMANUFACTURER_MITSUBISHI VIOMANUFACTURER_MITSUBISHI_AMERICA
   *   VIOMANUFACTURER_NISSAN VIOMANUFACTURER_OPEL VIOMANUFACTURER_PEUGEOT VIOMANUFACTURER_PORSCHE
   *   VIOMANUFACTURER_RENAULT VIOMANUFACTURER_ROLLS_ROYCE VIOMANUFACTURER_ROVER VIOMANUFACTURER_SAAB
   *   VIOMANUFACTURER_SUZUKI VIOMANUFACTURER_TOYOTA VIOMANUFACTURER_VOLKSWAGEN VIOMANUFACTURER_VOLVO -
   *   VIOVEHICLEMETRIC_DISPLACEMENT: Specifies the displacement of the engine in 0.1 liter increments.
   *   - VIOVEHICLEMETRIC_CYLINDERCOUNT: Specifies the number of cylinders in engine if internal
   *   combustion type. - VIOVEHICLEMETRIC_FUELTYPE: Specifies the fuel type enumeration. The following
   *   table shows possible types and their values. Type Value VIOFUELTYPE_GAS 1 VIOFUELTYPE_DIESEL 2
   *   VIOFUELTYPE_ELECTRIC 3 VIOFUELTYPE_HYBRID 4 VIOFUELTYPE_OTHER 255 -
   *   VIOVEHICLEMETRIC_FUELDELIVERY: Specifies the fuel delivery system enumeration. The following
   *   table shows possible types and their values. Type Value VIOFUELDELIVERY_2_BBL_CARBURETOR 1
   *   VIOFUELDELIVERY_4_BBL_CARBURETOR 2 VIOFUELDELIVERY_THROTTLE_BODY-INJECTION 3
   *   VIOFUELDELIVERY_PORT_INJECTION 4 VIOFUELDELIVERY_LEAD_ACID_BATTERY 5
   *   VIOFUELDELIVERY_NICKEL_METAL_HYDRIDE_BATTERY 6 VIOFUELDELIVERY_OTHER 255 -
   *   VIOVEHICLEMETRIC_TRANSMISSION: Specifies the transmission type enumeration. The following table
   *   shows possible types and their values. Type Value VIOTRANSMISSION_MANUAL 1
   *   VIOTRANSMISSION_AUTOMATIC 2 VIOTRANSMISSION_CONTINUOUSLY_VARIABLE 3 VIOTRANSMISSION_OTHER 255 -
   *   VIOVEHICLEMETRIC_TRANSMISSION_GEARS: Transmission gear count. If the high bit (0x80000000) is set
   *   it means that an overdrive gear is available.
   *
   * @return One of the values described in the following table is returned. Value Description S_OK
   *   The value of the item currently referenced by the enumerator was set successfully. S_FALSE The
   *   enumerator is not positioned on a valid item. E_OUTOFMEMORY The application is out of memory.
   *   E_POINTER The pointer referenced by pValue is invalid.
   */
  STDMETHOD(Set) (THIS_ LPVARIANT pValue) PURE;

  // Clone the enumerator with the same state as the current one.
  /**
   * This method retrieves another enumerator that contains the same state information as the current
   * one.
   *
   * @param ppEnumClone [out] Pointer to a pointer to an IVIO_EnumMetrics interface.
   *
   * @return One of the values described in the following table is returned. Value Description S_OK
   *   The application cloned the enumeration interface. E_OUTOFMEMORY The application is out of memory.
   *   E_UNEXPECTED An unexpected error occurred. E_POINTER The ppEnumClone pointer is invalid.
   */
  STDMETHOD(Clone) (THIS_ IVIO_EnumMetrics **ppMetricsEnumerator) PURE;
};

// IVIO_EnumMaintenanceItems interface declaration:
// This is an OLE enumeration interface that allows enumeration of all available
// vehicle maintenance items .  It is returned by the IVIO_Vehicle interface by 
// the get_MaintenanceItems() method.
/**
 * This interface is an enumeration interface that exposes information about maintenance information
 * for a vehicle.
 */
DECLARE_INTERFACE_(IVIO_EnumMaintenanceItems, IUnknown)
{
  // Reset the enumerator to the beginning of the enumeration list
  /**
   * This method resets the enumerator back to the beginning of the collection.
   *
   * @return S_OK indicates that the enumerator was set to the beginning of the collection. S_FALSE
   *   indicates that the enumerator was not set to the beginning of the collection.
   */
  STDMETHOD(Reset) (THIS_) PURE;

  // Skip the enumerator n items in the enumeration list
  /**
   * This method skips over the specified number of items in the vehicle maintenance items collection.
   *
   * @param cItems [in] Number of elements to skip in the maintenance entry enumeration.
   *
   * @return One of the values described in the following table is returned. Value Description S_OK
   *   The number of elements skipped is equal to the value specified in cItems. S_FALSE The number of
   *   elements skipped is less than the value specified in cItems. E_OUTOFMEMORY The application is out
   *   of memory. E_INVALIDARG The value of cItems is invalid. E_UNEXPECTED An unexpected error
   *   occurred.
   */
  STDMETHOD(Skip) (THIS_ ULONG cItems) PURE;

  // Attempt to seek to a certain maintenance item in the enumeration list
  /**
   * This method seeks to the entry in the vehicle maintenance items collection that has the specified
   * item identifier.
   *
   * @param nItemId [in] Identifier of the vehicle maintenance collection member to seek. It is one of
   *   the following values: VIOMAINT_BRAKE_PAD_CHANGE VIOMAINT_CHASSIS_ALIGNMENT
   *   VIOMAINT_COOLANT_CHANGE VIOMAINT_ENGINE_BELT_REPLACE VIOMAINT_ENGINE_OIL_CHANGE
   *   VIOMAINT_ENGINE_TUNEUP VIOMAINT_FLUID_LEVEL_CHECK VIOMAINT_REPLACE_BATTERY VIOMAINT_REPLACE_TIRES
   *   VIOMAINT_ROTATE_TIRES VIOMAINT_SPARKPLUG_CHANGE VIOMAINT_SPARKPLUG_WIRE_CHANGE
   *   VIOMAINT_TRANSMISSION_OIL_CHANGE
   *
   * @return S_OK indicates that the application retrieved the vehicle maintenance collection item
   *   successfully. The enumerator is set to the position of the specified maintenance item. S_FALSE
   *   indicates that the application was unable to find the specified maintenance collection item. The
   *   enumerator position is unchanged.
   *
   * The information specified by the item value identifiers is exposed by a VT_UNKNOWN (IUnknown*)
   * interface. Query VT_UNKNOWN (IUnknown*) for IID_VIOEnumMaintenanceEntry to get the enumerator
   * interface.
   */
  STDMETHOD(Seek) (THIS_ DWORD dwItemID) PURE;

  // Retrieve the next n maintenance items from the enumeration list
  /**
   * This method retrieves the specified number of items in the enumeration sequence.
   *
   * @param cItems [in] Number of items to retrieve.
   * @param rgItemArray [out] Array of IVIO_DataValue pointers where the retrieved maintenance entry
   *   items are stored.
   * @param pcItemsFetched [out] Pointer to a ULONG that contains the number of elements actually
   *   returned. If cItems is 1, this parameter can be NULL. If cItems is greater than 1, this parameter
   *   must be a valid pointer.
   *
   * @return One of the values described in the following table is returned. Value Description S_OK
   *   The application successfully retrieved the number of IVIO_DataValue interfaces specified in
   *   cItems. The value referenced by pcItemsFetched is set to cItems. S_FALSE The application returned
   *   fewer IVIO_DataValue interfaces than were specified in cItems. The value referenced by
   *   pcItemsFetched is set to the number of interfaces. The members of rgItemArray that were not set
   *   are set to NULL. E_OUTOFMEMORY The application is out of memory. E_UNEXPECTED An unexpected error
   *   occurred. E_INVALIDARG The value of cItems is invalid, or pcItemsFetched is NULL and cItems is
   *   greater than 1. E_POINTER Either the rgItemArray pointer is invalid or the pcItemsFetched pointer
   *   is invalid.
   *
   * The application must release the interfaces returned in rgItemArray when it is finished with
   * them.
   */
  STDMETHOD(Next) (THIS_ ULONG cItems, IVIO_DataValue **rgValueArray, 
                   ULONG *pcItemsFetched) PURE;

  // Add a new maintenance item to the collection
  /**
   * This method adds a new entry in the vehicle maintenance items collection. The new item identifier
   * matches the value of nItemId.
   *
   * @param nItemId [in] Identifier of the vehicle maintenance collection member to add. It is one of
   *   the following values: VIOMAINT_BRAKE_PAD_CHANGE VIOMAINT_CHASSIS_ALIGNMENT
   *   VIOMAINT_COOLANT_CHANGE VIOMAINT_ENGINE_BELT_REPLACE VIOMAINT_ENGINE_OIL_CHANGE
   *   VIOMAINT_ENGINE_TUNEUP VIOMAINT_FLUID_LEVEL_CHECK VIOMAINT_REPLACE_BATTERY VIOMAINT_REPLACE_TIRES
   *   VIOMAINT_ROTATE_TIRES VIOMAINT_SPARKPLUG_CHANGE VIOMAINT_SPARKPLUG_WIRE_CHANGE
   *   VIOMAINT_TRANSMISSION_OIL_CHANGE
   *
   * @return S_OK indicates that the application added the vehicle maintenance item successfully. The
   *   enumerator is set to the position of the new item. S_FALSE indicates that the item is already in
   *   the enumeration list. The enumeration position is unchanged.
   *
   * The information specified by the item value identifiers is exposed by a VT_UNKNOWN (IUnknown*)
   * interface. Query VT_UNKNOWN (IUnknown*) for IID_VIOEnumMaintenanceEntry to get the enumerator
   * interface.
   *
   * If a new collection entry is desired, calling the IVIO_EnumMaintenanceItems::Next method after
   * making the call to IVIO_EnumMaintenanceItems::Add creates an IVIO_EnumMaintenanceEntry interface
   * for the new maintenance item identifier.
   */
  STDMETHOD(Add) (THIS_ DWORD dwItemID) PURE;

  // Clone the enumerator with the same state as the current one.
  /**
   * This method retrieves another enumerator that contains the same state information as the current
   * enumerator.
   *
   * @param ppEnumClone [out] Pointer to the pointer to an IVIO_EnumMaintenanceItems interface.
   *
   * @return One of the values described in the following table is returned. Value Description S_OK
   *   The application cloned the enumeration interface. E_OUTOFMEMORY The application is out of memory.
   *   E_UNEXPECTED An unexpected error occurred. E_POINTER The ppEnumClone pointer is invalid.
   */
  STDMETHOD(Clone) (THIS_ IVIO_EnumMaintenanceItems **ppItemsEnumerator) PURE;
};

// IVIO_EnumMaintenanceEntry interface declaration:
// This is an OLE enumeration interface that allows enumeration of the 
// attributes of a maintenance entry.  It is returned by the 
// IVIO_EnumMaintenanceItems interface's Next() method
/**
 * This interface is an enumeration interface that exposes information about maintenance entry
 * information for a vehicle.
 */
DECLARE_INTERFACE_(IVIO_EnumMaintenanceEntry, IUnknown)
{
  // Reset the enumerator to the beginning of the enumeration list
  /**
   * This method resets the enumerator back to the beginning of the collection.
   *
   * @return S_OK indicates that the enumerator was set to the beginning of the collection. S_FALSE
   *   indicates that the enumerator was not set to the beginning of the collection.
   */
  STDMETHOD(Reset) (THIS_) PURE;

  // Skip the enumerator n items in the enumeration list
  /**
   * This method skips over the specified number of items in the maintenance entry enumeration list.
   *
   * @param cItems [in] Number of items to skip in the maintenance entry enumeration.
   *
   * @return One of the values described in the following table is returned. Value Description S_OK
   *   The number of elements skipped is equal to the value specified in cItems. S_FALSE The number of
   *   elements skipped is less than the value specified in cItems. E_OUTOFMEMORY The application is out
   *   of memory. E_INVALIDARG The value of cItems is invalid. E_UNEXPECTED An unexpected error
   *   occurred.
   */
  STDMETHOD(Skip) (THIS_ ULONG cAttributes) PURE;

  // Attempt to seek to a certain maintenance entry attribute in the enumeration
  // list
  /**
   * This method seeks to the entry in the enumeration list that matches the maintenance entry item
   * identifier that is passed to the method in nItemId.
   *
   * @param nItemId [in] Identifier of the vehicle maintenance item entry collection member to seek.
   *   It is one of the following values: VIOMAINTENTRY_HIGH_INTERVAL VIOMAINTENTRY_INTERVAL_TYPE
   *   VIOMAINTENTRY_INTERVAL_UNITS VIOMAINTENTRY_LOW_INTERVAL VIOMAINTENTRY_NAME
   *   VIOMAINTENTRY_SECONDARY_INTERVAL VIOMAINTENTRY_SECONDARY_INTERVAL_TYPE
   *   VIOMAINTENTRY_SECONDARY_INTERVAL_UNITS
   *
   * @return S_OK indicates that the application retrieved the vehicle maintenance entry successfully.
   *   The enumerator is set to the position of the specified maintenance entry. S_FALSE indicates that
   *   the application was unable to find the specified maintenance entry. The enumerator position is
   *   unchanged.
   */
  STDMETHOD(Seek) (THIS_ DWORD dwItemID) PURE;

  // Retrieve the next n maintenance entry attributes from the enumeration list
  /**
   * This method retrieves the specified number of items in the enumeration sequence.
   *
   * @param cItems [in] Number of items to retrieve.
   * @param rgItemsArray [out] Array of IVIO_DataValue pointers where retrieved maintenance entry
   *   items are stored.
   * @param pcItemsFetched [out] Pointer to a ULONG that contains the number of elements actually
   *   returned. If cItems is 1, this parameter can be NULL. If cItems is greater than 1, this parameter
   *   must be a valid pointer.
   *
   * @return One of the values described in the following table is returned. Value Description S_OK
   *   The application successfully retrieved the number of IVIO_DataValue interfaces specified in
   *   cItems. The value referenced by pcItemsFetched is set to cItems. S_FALSE The application returned
   *   fewer IVIO_DataValue interfaces than were specified in cItems. The value referenced by
   *   pcItemsFetched is set to the number of interfaces. The members of rgItemsArray that were not set
   *   are set to NULL. E_OUTOFMEMORY The application is out of memory. E_UNEXPECTED An unexpected error
   *   occurred. E_INVALIDARG The value of cItems is invalid, or pcItemFetched is NULL and cItems is
   *   greater than 1. E_POINTER Either the rgItemsArray pointer is invalid or the pcItemsFetched
   *   pointer is invalid.
   *
   * The application must release the interfaces in rgItemArray when it is done with them.
   */
  STDMETHOD(Next) (THIS_ ULONG cAttributes, IVIO_DataValue **rgValueArray, 
                   ULONG *pcAttributesFetched) PURE;

  // Set the value of the current maintenance entry attribute
  /**
   * This method sets the value of the current item referenced by the enumerator.
   *
   * @param pValue [in] Pointer to the VARIANT that contains the new value. Use a VT_BSTR to set the
   *   following value. A VT_BSTR is a 32-bit character string. - VIOMAINTENTRY_NAME: Specifies the name
   *   of the maintenance item. Use a VT_UI4 to set the following values. A VT_UI4 is an unsigned long
   *   integer. - VIOMAINTENTRY_LOW_INTERVAL: Specifies the shortest maintenance interval, for example,
   *   4,800 km (3,000 miles) for an oil change. - VIOMAINTENTRY_HIGH_INTERVAL: Specifies the longest
   *   maintenance interval, for example, 12,000 km (7,500 miles) for an oil change. -
   *   VIOMAINTENTRY_INTERVAL_TYPE: Specifies the type of interval, for example, time or mileage. It is
   *   one of the following values: VIOMAINTINTERVALTYPE_CALENDAR_TIME VIOMAINTINTERVALTYPE_MILEAGE
   *   VIOMAINTINTERVALTYPE_RUNNING_TIME - VIOMAINTENTRY_INTERVAL_UNITS: Specifies the units used in the
   *   interval. It is one of the following values: VIOMAINTINTERVALUNITS_DAYS
   *   VIOMAINTINTERVALUNITS_HOURS VIOMAINTINTERVALUNITS_KILOMETERS VIOMAINTINTERVALUNITS_MILES
   *   VIOMAINTINTERVALUNITS_MONTHS - VIOMAINTENTRY_SECONDARY_INTERVAL: Specifies the secondary interval
   *   to use, for example, three months for an oil change. An application looks for either the low
   *   interval or the secondary interval to elapse in order to give a maintenance warning. -
   *   VIOMAINTENTRY_SECONDARY_INTERVAL_TYPE: Specifies the type of secondary interval. It can be one of
   *   the values listed for VIOMAINTENTRY_INTERVAL_TYPE. - VIOMAINTENTRY_SECONDARY_INTERVAL_UNITS:
   *   Specifies the unites used for the secondary interval. It can be one of the values listed for
   *   VIOMAINTENTRY_INTERVAL_UNITS.
   *
   * @return One of the values described in the following table is returned. Value Description S_OK
   *   The value of the item currently referenced by the enumerator was set successfully. S_FALSE The
   *   enumerator is not positioned on a valid item. E_OUTOFMEMORY The application is out of memory.
   *   E_POINTER The pointer referenced by pValue is invalid.
   */
  STDMETHOD(Set) (THIS_ LPVARIANT pValue) PURE;

  // Clone the enumerator with the same state as the current one.
  /**
   * This method retrieves another enumerator that contains the same state information as the current
   * enumerator.
   *
   * @param ppEnumClone [out] Pointer to a pointer to an IVIO_EnumMaintenanceEntry interface.
   *
   * @return One of the values described in the following table is returned. Value Description S_OK
   *   The application cloned the enumeration interface. E_OUTOFMEMORY The application is out of memory.
   *   E_UNEXPECTED An unexpected error occurred. E_POINTER The ppEnumClone pointer is invalid.
   */
  STDMETHOD(Clone) (THIS_ IVIO_EnumMaintenanceEntry **ppEntryEnumerator) PURE;
};

// IVIO_EnumDevices interface declaration:
// This is an OLE enumeration interface that allows enumeration of all available
// components that expose the IVIO_Device interface.  It is returned by the 
// IVIO_Vehicle interface using the get_Devices() method.
/**
 * This interface enumerates the available components in the vehicle that expose the IVIO_Device
 * interface.
 */
DECLARE_INTERFACE_(IVIO_EnumDevices, IUnknown)
{
  // Reset the enumerator to the beginning of the enumeration list
  /**
   * This method resets the enumerator back to the beginning of the collection.
   *
   * @return S_OK indicates that the enumerator was set to the beginning of the collection. S_FALSE
   *   indicates that the enumerator was not set to the beginning of the collection.
   */
  STDMETHOD(Reset) (THIS_) PURE;

  // Skip the enumerator n items in the enumeration list
  /**
   * This method skips over the specified number of items in the vehicle's device enumeration list.
   *
   * @param cDevices [in] Number of items in the device CLSID list to skip.
   *
   * @return One of the values described in the following table is returned. Value Description S_OK
   *   The number of elements skipped is equal to the value specified in cDevices. S_FALSE The number of
   *   elements skipped is less than the value specified in cDevices. E_OUTOFMEMORY The application is
   *   out of memory. E_INVALIDARG The value of cDevices is invalid. E_UNEXPECTED An unexpected error
   *   occurred.
   */
  STDMETHOD(Skip) (THIS_ ULONG cDevices) PURE;

  // Attempt to seek to a certain device in the enumeration list
  /**
   * This method seeks to the entry in the device component collection that matches the device CLSID
   * specified in rclsid.
   *
   * @param rclsid [in] CLSID to seek. It is one of the following values: CLSID_VIO_AUX_LIGHTS
   *   CLSID_VIO_BATTERY_VOLTAGE CLSID_VIO_COOLANT_TEMP CLSID_VIO_DIAGNOSTIC_CODES
   *   CLSID_VIO_DOOR_SWITCHES CLSID_VIO_ENGINE_LOAD CLSID_VIO_ENGINE_RPM CLSID_VIO_FUEL_PRESSURE
   *   CLSID_VIO_FUEL_SYSTEM_STATUS CLSID_VIO_FUEL_TRIM CLSID_VIO_HEADLIGHTS CLSID_VIO_IGNITION_SWITCH
   *   CLSID_VIO_INTAKE_TEMP CLSID_VIO_LATCH_CONTROL CLSID_VIO_LOCK_STATE
   *   CLSID_VIO_MANIFOLD_AIR_PRESSURE CLSID_VIO_MASS_AIR_FLOW_RATE CLSID_VIO_O2_SENSOR
   *   CLSID_VIO_ODOMETER CLSID_VIO_PARKING_BRAKE CLSID_VIO_THROTTLE_POSITION CLSID_VIO_TIMING_ADVANCE
   *   CLSID_VIO_TRANSMISSION_GEAR CLSID_VIO_VEHICLE_SPEED
   *
   * @return S_OK indicates that the application retrieved the vehicle device CLSID successfully. The
   *   enumerator is set to the position of the specified device. S_FALSE indicates that the application
   *   was unable to find the specified device CLSID. The enumerator position is unchanged.
   *
   * If S_FALSE is returned, this means that the requested component exposing the IVIO_Device
   * interface is not available on the vehicle.
   */
  STDMETHOD(Seek) (THIS_ REFCLSID rclsid) PURE;

  // Retrieve the next n devices from the enumeration list
  /**
   * This method retrieves the specified number of device class identifiers (CLSIDs) in the
   * enumeration sequence.
   *
   * @param cDevices, [in] Number of device CLSIDs to retrieve.
   * @param rgDevicesArray [out] Pointer to the array of CLSID pointers where retrieved device CLSIDs
   *   are stored.
   * @param pcDevicesFetched [out] Pointer to a ULONG that contains the number of elements actually
   *   returned. If cDevices is 1, this parameter can be NULL. If cDevices is greater than 1, this
   *   parameter must be a valid pointer.
   *
   * @return One of the values described in the following table is returned. Value Description S_OK
   *   The application successfully retrieved the number of device CLSIDs specified in cDevices. The
   *   value referenced by pcDevicesFetched is set to cDevices. S_FALSE The application returned fewer
   *   CLSIDs than specified in cDevices. The value referenced by pcDevicesFetched is set to the number
   *   of elements returned. The members of rgDevicesArray that were not set are set to NULL.
   *   E_OUTOFMEMORY The application is out of memory. E_UNEXPECTED An unexpected error occurred.
   *   E_INVALIDARG The value of cDevices is invalid, or pcDevicesFetched is NULL and cDevices is
   *   greater than 1. E_POINTER Either the rgDevicesArray pointer is invalid or the pcDevicesFetched
   *   pointer is invalid.
   *
   * The application must free each array element using the CoTaskMemFree call.
   */
  STDMETHOD(Next) (THIS_ ULONG cDevices, LPCLSID *rgDeviceArray, 
                   ULONG *pcDevicesFetched) PURE;

  // Clone the enumerator with the same state as the current one.
  /**
   * This method retrieves another enumerator that contains the same state information as the current
   * enumerator.
   *
   * @param ppEnumClone [out] Pointer to a pointer to an IVIO_EnumDevices interface.
   *
   * @return One of the values described in the following table is returned. Value Description S_OK
   *   The application cloned the enumeration interface. E_OUTOFMEMORY The application is out of memory.
   *   E_UNEXPECTED An unexpected error occurred. E_POINTER The ppEnumClone pointer is invalid.
   */
  STDMETHOD(Clone) (THIS_ IVIO_EnumDevices **ppDeviceEnumerator) PURE;
};

// IVIO_EnumDiagnosticItems interface declaration:
// This is an OLE enumeration interface that allows enumeration of all available
// diagnostic trouble codes from the CLSID_TROUBLE_CODES object's GetData() 
// method as the object IUnknown interface.
/**
 * This interface exposes information about diagnostic data from the vehicle.
 */
DECLARE_INTERFACE_(IVIO_EnumDiagnosticItems, IUnknown)
{
  // Reset the enumerator to the beginning of the enumeration list
  /**
   * This method resets the enumerator back to the beginning of the collection.
   *
   * @return S_OK indicates that the enumerator was set to the beginning of the collection. S_FALSE
   *   indicates that the enumerator was not set to the beginning of the collection.
   */
  STDMETHOD(Reset) (THIS_) PURE;

  // Skip the enumerator n items in the enumeration list
  /**
   * This method skips over the specified number of items in the vehicle diagnostic items.
   *
   * @param cItems [in] Number of elements in the vehicle diagnostic list to skip.
   *
   * @return One of the values described in the following table is returned. Value Description S_OK
   *   The number of elements skipped is equal to the value specified in cItems. S_FALSE The number of
   *   elements skipped is less than the value specified in cItems. E_OUTOFMEMORY The application is out
   *   of memory. E_INVALIDARG The value of cItems is invalid. E_UNEXPECTED An unexpected error
   *   occurred.
   */
  STDMETHOD(Skip) (THIS_ ULONG cItems) PURE;

  // Retrieve the next n diagnostic items from the enumeration list
  /**
   * This method retrieves the specified number of items in the enumeration sequence.
   *
   * @param cItems [in] Number of items to retrieve.
   * @param rgItemsArray [out] Array of IVIO_EnumDiagnosticEntry pointers where retrieved diagnostic
   *   entry items are stored.
   * @param pcItemsFetched [out] Pointer to a ULONG that contains the number of elements actually
   *   returned. If cItems is 1, this parameter can be NULL. If cItems is greater than 1, this parameter
   *   must be a valid pointer.
   *
   * @return One of the values described in the following table is returned. Value Description S_OK
   *   The application successfully retrieved the number of IVIO_EnumDiagnosticEntry interfaces
   *   specified in cItems. The value referenced by pcItemsFetched is set to cItems. S_FALSE The
   *   application returned fewer IVIO_EnumDiagnosticEntry interfaces than specified in Items. The value
   *   referenced by pcItemsFetched is set to the number of interfaces returned. The members of
   *   rgItemsArray that were not set are set to NULL. E_OUTOFMEMORY The application is out of memory.
   *   E_UNEXPECTED An unexpected error occurred. E_INVALIDARG The value of cItems is invalid, or
   *   pcItemsFetched is NULL and cItems is greater than 1. E_POINTER Either the rgItemsArray pointer is
   *   invalid or the pcItemsFetched pointer is invalid.
   *
   * The application must release the interfaces returned in rgItemsArray when it is done with them.
   */
  STDMETHOD(Next) (THIS_ ULONG cItems, IVIO_DataValue **rgValueArray,
                   ULONG *pcItemsFetched) PURE;

  // Clone the enumerator with the same state as the current one.
  /**
   * This method retrieves another enumerator that contains the same state information as the current
   * one.
   *
   * @param ppEnumClone [out] Pointer to a pointer to an IVIO_EnumDiagnosticItems interface.
   *
   * @return One of the values described in the following table is returned. Value Description S_OK
   *   The application cloned the enumeration interface. E_OUTOFMEMORY The application is out of memory.
   *   E_UNEXPECTED An unexpected error occurred. E_POINTER The ppEnumClone pointer is invalid.
   */
  STDMETHOD(Clone) (THIS_ IVIO_EnumDiagnosticItems **ppItemsEnumerator) PURE;
};

// IVIO_EnumDiagnosticEntry interface declaration:
// This is an OLE enumeration interface that allows enumeration of the 
// attributes of a diagnostic item.  An object that exposes this interface is
// returned by the Next() method in the IVIO_EnumDiagnosticItems interface.
/**
 * This interface exposes information about vehicle diagnostic data entries.
 */
DECLARE_INTERFACE_(IVIO_EnumDiagnosticEntry, IUnknown)
{
  // Reset the enumerator to the beginning of the enumeration list
  /**
   * This method resets the enumerator back to the beginning of the collection.
   *
   * @return S_OK indicates that the enumerator was set to the beginning of the collection. S_FALSE
   *   indicates that the enumerator was not set to the beginning of the collection.
   */
  STDMETHOD(Reset) (THIS_) PURE;

  // Skip the enumerator n items in the enumeration list
  /**
   * This method skips over the specified number of items in the diagnostic entry enumeration list.
   *
   * @param cItems [in] Number of elements in the diagnostic entry enumeration list to skip.
   *
   * @return One of the values described in the following table is returned. Value Description S_OK
   *   The number of elements skipped is equal to the value specified in cItems. S_FALSE The number of
   *   elements skipped is less than the value specified in cItems. E_OUTOFMEMORY The application is out
   *   of memory. E_INVALIDARG The value of cItems is invalid. E_UNEXPECTED An unexpected error
   *   occurred.
   */
  STDMETHOD(Skip) (THIS_ ULONG cAttributes) PURE;

  // Attempt to seek to a certain diagnostic entry attribute in the enumeration
  // list
  /**
   * This method seeks the entry in the diagnostic entry enumeration list with the identifier that
   * matches the value of nItem.
   *
   * @param nItemId [in] Identifier of the vehicle diagnostic entry collection member to seek. It is
   *   one of the following values: VIODIAGENTRY_LAMP_FLAG VIODIAGENTRY_SAE_CODE VIODIAGENTRY_SUBSYSTEM
   *   VIODIAGENTRY_SYSTEM
   *
   * @return S_OK indicates that the application retrieved the diagnostic entry successfully.
   *   Enumerator is set to position of given diagnostic entry. S_FALSE indicates that the enumerator
   *   position is unchanged.
   *
   * The information specified in the item value identifiers is contained in a VT_UI4 data type, which
   * is an unsigned long integer. The long integer contains information associated with one of the
   * following item value identifiers:
   *
   * - VIODIAGENTRY_SYSTEM: Specifies the vehicle system returning the diagnostic information. It is
   * one of the following values: VIOTC_SYS_BODY VIOTC_SYS_CHASSIS VIOTC_SYS_NETWORK
   * VIOTC_SYS_POWERTRAIN VIOTC_SYS_UNKNOWN
   *
   * - VIODIAGENTRY_SUBSYSTEM: Specifies the generic vehicle subsystem value. It can be one of the
   * following values: For power train subsystems: VIOTC_AUX_EMISSION_CONTROL VIOTC_FUEL_AIR_METERING
   * VIOTC_IGNITION_SYSTEM_OR_MISFIRE VIOTC_TRANSMISSION VIOTC_VEHSPEED_IDLE_AUXINPUTS For chassis
   * subsystems: VIOTC_ANTILOCK_BRAKES VIOTC_STEERING VIOTC_SUSPENSION VIOTC_TRACTION_CONTROL For body
   * subsystems: VIOTC_ANTI_THEFT VIOTC_CLIMATE_CONTROL VIOTC_INSTRUMENT_PANEL VIOTC_LIGHTING_CONTROL
   * VIOTC_MEMORY_SEATS_MIRROR VIOTC_SUPPLEMENTAL_RESTRAINTS VIOTC_TRIP_COMPUTER For an unknown
   * subsystem, use VIOTC_SUBSYSTEM_OTHER.
   *
   * - VIODIAGENTRY_SAE_CODE: Specifies the standard diagnostic trouble code value defined by the
   * Society of Automotive Engineers (SAE).
   *
   * - VIODIAGENTRY_LAMP_FLAG: Specifies the flag to show if this diagnostic code activated a
   * malfunction indicator lamp on the instrument panel.
   */
  STDMETHOD(Seek) (THIS_ DWORD dwItemID) PURE;

  // Retrieve the next n diagnostic entry attributes from the enumeration list
  /**
   * This method retrieves the specified number of items in the enumeration sequence.
   *
   * @param cItems [in] Number of items to retrieve.
   * @param rgItemsArray [out] Array of IVIO_DataValue pointers where retrieved diagnostic entry items
   *   are stored.
   * @param pcItemsFetched [out] Pointer to a ULONG that contains the number of elements actually
   *   returned. If cItems is 1, this parameter can be NULL. If cItems is greater than 1, this parameter
   *   must be a valid pointer.
   *
   * @return One of the values described in the following table is returned. Value Description S_OK
   *   The application successfully retrieved the number of IVIO_DataValue interfaces specified in
   *   cItems. The value referenced by pcItemsFetched is set to cItems. S_FALSE The application returned
   *   fewer IVIO_DataValue interfaces than specified in Items. The value referenced by pcItemsFetched
   *   is set to the number of interfaces returned. The members of rgItemsArray that were not set are
   *   set to NULL. E_OUTOFMEMORY The application is out of memory. E_UNEXPECTED An unexpected error
   *   occurred. E_INVALIDARG The value of cItems is invalid, or pcItemsFetched is NULL and cItems is
   *   greater than 1. E_POINTER Either the rgItemsArray pointer is invalid or the pcItemsFetched
   *   pointer is invalid.
   *
   * The application must release the interfaces returned in rgItemsArray when it is done with them.
   */
  STDMETHOD(Next) (THIS_ ULONG cAttributes, IVIO_DataValue **rgValueArray, 
                   ULONG *pcAttributesFetched) PURE;

  // Clone the enumerator with the same state as the current one.
  /**
   * This method retrieves another enumerator that contains the same state information as the current
   * one.
   *
   * @param ppEnumClone [out] Pointer to the pointer to an IVIO_EnumDiagnosticEntry interface.
   *
   * @return One of the values described in the following table is returned. Value Description S_OK
   *   The application cloned the enumeration interface. E_OUTOFMEMORY The application is out of memory.
   *   E_UNEXPECTED An unexpected error occurred. E_POINTER The ppEnumClone pointer is invalid.
   */
  STDMETHOD(Clone) (THIS_ IVIO_EnumDiagnosticEntry **ppEntryEnumerator) PURE;
};


// IVIO_DataValue interface declaration:
// This is the interface that is returned by the Next() methods in the 
// IVIO_EnumMetrics, IVIO_EnumMaintenanceItems, and IVIO_EnumMaintenanceEntry
// interfaces to return data back to the requesting application.  See the VIO
// API specification for details on the specific data values and their meanings
/**
 * Use this interface to return data values from the enumeration interfaces to the application.
 */
DECLARE_INTERFACE_(IVIO_DataValue, IUnknown)
{
  // Get the data item's ID
  /**
   * This method gets the item's identifier attribute.
   *
   * @param pItemID [out] Pointer to a DWORD to store the item identifier value. It is one of the
   *   following item identifier values: The following are IVIO_DATAVALUE properties from
   *   IVIO_EnumMetrics interface: VIOVEHICLEMETRIC_CYLINDERCOUNT VIOVEHICLEMETRIC_DISPLACEMENT
   *   VIOVEHICLEMETRIC_FUELDELIVERY VIOVEHICLEMETRIC_FUELTYPE VIOVEHICLEMETRIC_MAKE
   *   VIOVEHICLEMETRIC_MANUFACTURER VIOVEHICLEMETRIC_MODEL VIOVEHICLEMETRIC_TRANSMISSION
   *   VIOVEHICLEMETRIC_TRANSMISSION_GEARS VIOVEHICLEMETRIC_VIN VIOVEHICLEMETRIC_YEAR The following are
   *   IVIO_DATAVALUE properties from IVIO_EnumMaintenanceItems interface: VIOMAINT_BRAKE_PAD_CHANGE
   *   VIOMAINT_CHASSIS_ALIGNMENT VIOMAINT_COOLANT_CHANGE VIOMAINT_ENGINE_BELT_REPLACE
   *   VIOMAINT_ENGINE_OIL_CHANGE VIOMAINT_ENGINE_TUNEUP VIOMAINT_FLUID_LEVEL_CHECK
   *   VIOMAINT_REPLACE_BATTERY VIOMAINT_REPLACE_TIRES VIOMAINT_ROTATE_TIRES VIOMAINT_SPARKPLUG_CHANGE
   *   VIOMAINT_SPARKPLUG_WIRE_CHANGE VIOMAINT_TRANSMISSION_OIL_CHANGE The following are IVIO_DATAVALUE
   *   properties from IVIO_EnumMaintenanceEntry interface: VIOMAINTENTRY_HIGH_INTERVAL
   *   VIOMAINTENTRY_INTERVAL_TYPE VIOMAINTENTRY_INTERVAL_UNITS VIOMAINTENTRY_LOW_INTERVAL
   *   VIOMAINTENTRY_NAME VIOMAINTENTRY_SECONDARY_INTERVAL VIOMAINTENTRY_SECONDARY_INTERVAL_TYPE
   *   VIOMAINTENTRY_SECONDARY_INTERVAL_UNITS The following are IVIO_DATAVALUE properties from
   *   IVIO_EnumDiagnosticEntry interface: VIODIAGENTRY_LAMP_FLAG VIODIAGENTRY_SAE_CODE
   *   VIODIAGENTRY_SUBSYSTEM VIODIAGENTRY_SYSTEM
   *
   * @return S_OK indicates that the item identifier was returned successfully. E_POINTER indicates
   *   that the pointer is invalid.
   */
  STDMETHOD(get_ItemID)(THIS_ LPDWORD pItemID) PURE;

  // Get the value of the data item.
  // Note:  The calling application must call VariantClear() on the value set
  //        by this method in order to free up any resources in use by the 
  //        variant.
  /**
   * This method retrieves the data value for the item identified with the IVIO_DataValue::get_ItemID
   * method.
   *
   * @param pDataValue [out] Pointer to a VARIANT type.
   *
   * @return One of the values described in the following table is returned. Value Description S_OK
   *   The data value was returned successfully. E_OUTOFMEMORY The application is out of memory.
   *   E_POINTER The pDataValue pointer is invalid.
   */
  STDMETHOD(get_DataValue)(THIS_ LPVARIANT pDataValue) PURE;
};

// IVIO_EventSink class declaration:
// This is an abstract base class used to create notification
// objects that are called from an IVIO_Device instance when the 
// IVIO_Device->SetNotify() method is invoked
/**
 * This interface is used by IVIO_Device interface to notify an application.
 */
DECLARE_INTERFACE_(IVIO_EventSink, IUnknown)
{
  // Method that is called from the IVIO_Device instance
  // Need to determine specific parameters that are needed
  /**
   * This method is called from a component implementing the IVIO_Device interface's SetNotify method
   * when the notification period has elapsed.
   *
   * @param pData [in] Pointer to a VARIANT record returned by the device component. The contents of
   *   the VARIANT are described in the documentation for each component.
   * @param lParam [in] Value defined by the device component for additional information.
   *
   * @return S_OK indicates that the data was received successfully.
   *
   * This is the callback function used for the notification sink for the IVIO_Device interface.
   */
  STDMETHOD(ReceiveData) (THIS_ LPVARIANT pData, LPARAM lParam) PURE;
};

// IVIO_Device class declaration:
// This is the base class that all vehicle information is derived from
/**
 * Use this interface to access vehicle components. These components can be sensors that are
 * accessed by means of the vehicle's serial data bus, direct input from the vehicle's wiring
 * harness, vehicle electronic control units (ECU), or from the Auto PC device.
 */
DECLARE_INTERFACE_(IVIO_Device, IUnknown)
{
  //
  // Get Properties of a IVIO_Device instance
  //
  // Get the metrics of this IVIO_Device
  /**
   * This method retrieves the data that describes the format of the data being sent to and returned
   * from the interface's components.
   *
   * @param pVioDeviceMetrics [out] Pointer to a VIODEVICEMETRICS structure, the members of which are
   *   set if the method returns successfully.
   *
   * @return One of the values described in the following table is returned. Value Description S_OK
   *   Successfully retrieved the metrics for the component. E_POINTER The pVioDeviceMetrics pointer is
   *   invalid. E_UNEXPECTED An unexpected error occurred while retrieving the metrics.
   */
  STDMETHOD(get_Metrics) (THIS_ LPVIODEVICEMETRICS pVIODeviceMetrics) PURE;
  // Get the status of this IVIO_Device
  /**
   * The method retrieves the current availability of the device such as READY or BUSY.
   *
   * @param pStatus [out] Pointer to a DWORD that returns one of the following status values: -
   *   VIODEVSTATUS_READY: The device is ready to run. - VIODEVSTATUS_BUSY: The device is busy. -
   *   VIODEVSTATUS_UNAVAIL: The device is unavailable. - VIODEVSTATUS_SUSPENDED: The device is
   *   suspended. In other words, it is in low power operation.
   *
   * @return One of the values described in the following table is returned. Value Description S_OK
   *   Successfully retrieved the status of the device. E_POINTER The pStatus pointer is invalid.
   *   E_UNEXPECTED An unexpected error occurred while retrieving the status.
   */
  STDMETHOD(get_Status) (THIS_ DWORD *pStatus) PURE;
  // Get the access mode of this IVIO_Device (shared, exclusive)
  /**
   * This method retrieves the current access for a requested mode.
   *
   * @param dwMode [in] Specifies the type of mode that is requesting access. It is one of the
   *   following values: - VIODEVICEMODE_READ: This mode requests the device's read access. -
   *   VIODEVICEMODE_WRITE: This mode requests the device's write access.
   * @param pAccessMode [out] Address to store the requested access for the requested mode. The
   *   following table shows possible values for this parameter. Access Value Description
   *   VIODEVACCESS_SHARED 0x0000 The device is currently shareable. VIODEVACCESS_EXCLUSIVE 0x8000 The
   *   device currently has exclusive access. VIODEVACCESS_NONE 0xFFFF There is no access for the
   *   requested mode.
   *
   * @return One of the values described in the following table is returned. Value Description S_OK
   *   The access mode was successfully read. E_INVALID The dwMode parameter was invalid. E_POINTER The
   *   pAccessMode pointer is invalid. E_UNEXPECTED An unexpected error occurred while requesting
   *   access.
   */
  STDMETHOD(get_AccessMode) (THIS_ DWORD dwMode, DWORD *pAccessMode) PURE;
  // Set the access mode of this IVIO_Device (shared, exclusive)
  /**
   * This method sets the access mode-either shared or exclusive access-for the device. The mode is
   * used with a read or write mode.
   *
   * @param [in] dwMode Specifies the mode for which the access is to be set. It is one of the
   *   following values: - VIODEVICEMODE_READ: Sets the device's read access. - VIODEVICEMODE_WRITE:
   *   Sets the device's write access.
   * @param dwAccessMode [in] Specifies the type of access requested for the device's modes. The
   *   following table shows possible values for this parameter. Access Value Description
   *   VIODEVACCESS_SHARED 0x0000 Sets the device as a shareable device VIODEVACCESS_EXCLUSIVE 0x8000
   *   Sets the device as an exclusive device that cannot be shared
   *
   * @return One of the values described in the following table is returned. Value Description S_OK
   *   The access mode was successfully set. E_INVALID One of the parameters is invalid. E_ACCESSDENIED
   *   The application was unable to change the access mode because another process or thread has
   *   already set the access.
   */
  STDMETHOD(set_AccessMode) (THIS_ DWORD dwMode, DWORD dwAccessMode) PURE;
 
  // 
  // Send/Retrieve data from the device itself
  //
  // Read data from a IVIO_Device instance (read data from vehicle) 
  /**
   * This method retrieves the current data from the device.
   *
   * @param pData [in/out] Pointer to a VARIANT that contains the data from the device. When some
   *   vehicle I/O components implement the IVIO_Device interface, the VARIANT contains information to
   *   further define the requested data. For an example of this implementation, see the
   *   CLSID_VIO_FUEL_SYSTEM_STATUS component.
   * @param dwTimeOut [in] Specifies, in milliseconds, the amount of time to wait for a reply to the
   *   data request.
   *
   * @return One of the values described in the following table is returned. Value Description S_OK
   *   Successfully retrieved data from the device. E_NOTIMPL This device does not implement data reads.
   *   E_POINTER The pData pointer is invalid. E_ACCESSDENIED Access to this device is denied.
   *   E_UNEXPECTED An unexpected error occurred reading data from the device.
   *
   * For more information about the GetData method, see "CLSIDs for the Auto PC."
   */
  STDMETHOD(GetData) (THIS_ LPVARIANT pData, DWORD dwTimeout) PURE;
  // Send data to a IVIO_Device instance (send control data to vehicle)
  /**
   * This method sends control information to the vehicle.
   *
   * @param pData [in] Pointer to a VARIANT that contains the control information to be passed to the
   *   device component. The contents of the VARIANT vary according to which component is being used.
   * @param dwTimeOut [out] Specifies, in milliseconds, the amount of time to wait for a reply to the
   *   control request.
   *
   * @return One of the values described in the following table is returned. Value Description S_OK
   *   Successfully sent control data to the device. E_NOTIMPL The device does not implement control
   *   functionality. E_POINTER The pData pointer is invalid. E_ACCESSDENIED Access to this device is
   *   denied. E_UNEXPECTED An unexpected error occurred while sending information to the device
   *   component.
   */
  STDMETHOD(SetData) (THIS_ const LPVARIANT pData, DWORD dwTimeout) PURE;
  
  //
  // Add an event sink to a given device
  //
  // Add a notification sink to a IVIODevice instance
  /**
   * This method provides the means to add a notification sink to a specified device. Through this
   * sink, the device can send a notification to an application on a timed basis.
   *
   * @param pParameterData [in] Pointer to a VARIANT structure that contains additional information
   *   for starting the notification. This would be the same information that a device component would
   *   require for input on a call to the GetData method.
   * @param pEventSink [in] Pointer to an IVIO_EventSink interface. This interface's method is called
   *   by the device at notification time. If the value is NULL, then the event sink is removed from the
   *   device component.
   * @param dwFreq [out] Specifies, in milliseconds, the frequency at which the application should be
   *   notified by the device. This value should not be less than 500 milliseconds.
   *
   * @return One of the values described in the following table is returned. Value Description S_OK
   *   Notification sink was successfully added to the device. E_NOTIMPL The SetNotify method is not
   *   implemented for the device component. This may result if only write access is available on the
   *   device component. E_POINTER The pEventSink pointer is invalid. E_ACCESSDENIED A notification sink
   *   is already in place for the device component, or the device has exclusive read access.
   *   E_UNEXPECTED An unexpected error occurred while trying to add the notification sink to the device
   *   component.
   */
  STDMETHOD(SetNotify) (THIS_ const LPVARIANT pParameterData, 
                        IVIO_EventSink *pEventSink, DWORD dwFreq) PURE;  
};

// Low-level, straight to the device driver type of interface
// This facilitates applications sending device driver-specific commands
// to the VIO device driver
/**
 * This interface enables applications to communicate directly with the VIO device driver.
 */
DECLARE_INTERFACE_(IVIO_Ioctl, IUnknown)
{
  // Similar to the standard DeviceIoControl API
  /**
   * This method performs the direct communication with the device driver.
   *
   * @param dwCommandId [in] Specifies the device-driver command identifier. This information is
   *   furnished by the provider of the VIO hardware device driver.
   * @param pCommandData [in] Pointer to a buffer that contains driver-specific data for the given
   *   command specified in dwCommandId.
   * @param cb [in] Size of the buffer referenced by the pCommandData parameter.
   * @param pReply [out] Pointer to a buffer that stores information returned by the device driver.
   * @param dwOutPutSize [in] Specifies the size of the buffer referenced by the pReply parameter.
   * @param pReplySize [out] Pointer to a DWORD value that contains the size of the data set stored in
   *   the buffer referenced by pReply.
   *
   * @return One of the values described in the following table is returned. Value Description S_OK
   *   The function was executed successfully. Reply data from the device driver is stored in the pReply
   *   buffer. E_POINTER Either the pCommandData, pReply, or pReplySize pointer is invalid. E_INVALID
   *   The value in dwCommandId is invalid for the device driver or the value given in dwOutputSize is
   *   too small for the amount of data in the reply. The correct size is stored in the value referenced
   *   by pReplySize. E_UNEXPECTED An unexpected error occurred in the request to the device driver.
   */
  STDMETHOD(DoCommand) (THIS_ DWORD dwCommandId, const PVOID pCommandData, 
                        DWORD cb, PVOID pReply, DWORD dwOutputSize, 
                        DWORD *pReplySize) PURE;

};

#endif // include sentry
