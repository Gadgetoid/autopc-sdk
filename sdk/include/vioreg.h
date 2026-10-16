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
STDAPI VIORegisterDevice(REFCLSID rclsidDevice, BOOL bRegister);
// Register the minidriver object with the device object that uses it
STDAPI VIORegisterMinidriver(REFCLSID rclsidDevice, REFCLSID rclsidMiniDriver,
                          BOOL bRegister);
// Register a minidriver management object with the API
STDAPI VIORegisterMiniDriverMgr(REFCLSID rclsidMiniDriverMgr, BOOL bRegister);

#endif // include sentry
