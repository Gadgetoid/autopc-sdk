/*******************************************************************************
 *
 *  File:
 *    VIOREG.H
 *
 *  Description:
 *    Declaration of functions that register objects with the VIO API
 *
 *  Original Author:
 *    Paul Horenberger
 *
 *  Modification History:
 *  $Log:   H:/AUTOPC/HOSTSW/PVCSARCH/INCLUDE/vioreg.h_v  $
 * 
 *    Rev 1.0   May 28 1998 15:07:32   PHorenberger
 * Prototypes for the VIO registration functions
 *
 *  Copyright (C) 1998 Vetronix Corp.
 ******************************************************************************/
#if (!defined __VIOREG_H)
#define __VIOREG_H 1

// Register a device with the API 
/**
 * This function enables support for a vehicle input/output (I/O) device by the vehicle I/O API.
 *
 * @param rclsid Class identifier of the vehicle I/O device.
 * @param bRegister Boolean that is set to TRUE to register the device, or to FALSE otherwise.
 *
 * @return One of the values described in the following table is returned. Value Description S_OK
 *   Object is registered or deregistered successfully. S_FALSE Object is already registered or
 *   deregistered. E_FAIL Failed to register or deregister object. E_OUTOFMEMORY Application is out of
 *   memory. E_UNEXPECTED An unexpected error occurred.
 *
 * This function informs the vehicle I/O API of which vehicle I/O CLSIDs are available in a
 * specified vehicle.
 */
STDAPI VIORegisterDevice(REFCLSID rclsidDevice, BOOL bRegister);
// Register the minidriver object with the device object that uses it
/**
 * This function associates a vehicle input/output (I/O) mini-driver object's class identifier
 * (CLSID) with the vehicle I/O API device object.
 *
 * @param rclsidDevice CLSID of the vehicle I/O API device object that the mini-driver is associated
 *   with.
 * @param rclsidMinidriver CLSID of the vehicle I/O mini-driver object.
 * @param bRegister Boolean that is set to TRUE to register the mini-driver, or to FALSE to
 *   deregister it.
 *
 * @return One of the values described in the following table is returned. Value Description S_OK
 *   Mini-driver is registered or deregistered successfully. S_FALSE Mini-driver is already registered
 *   or deregistered. E_FAIL Failed to register or deregister mini-driver. E_OUTOFMEMORY Application
 *   is out of memory. E_UNEXPECTED An unexpected error occurred.
 *
 * The vehicle I/O API device objects use mini-driver objects to convert vendor-specific data
 * retrieved from a vehicle I/O device to the format specified for the API device object. This
 * function is used to determine which mini-driver object a specified API device object uses for the
 * conversion.
 */
STDAPI VIORegisterMinidriver(REFCLSID rclsidDevice, REFCLSID rclsidMiniDriver,
                          BOOL bRegister);
// Register a minidriver management object with the API
STDAPI VIORegisterMiniDriverMgr(REFCLSID rclsidMiniDriverMgr, BOOL bRegister);

#endif // include sentry
