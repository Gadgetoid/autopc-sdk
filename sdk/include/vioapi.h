/*******************************************************************************
 *
 *  File:
 *    VIOAPI.H
 *
 *  Description:
 *    Header file includes all of the other header files used by the VIO API.
 *
 *  Original Author:
 *    Paul Horenberger
 *
 *  Modification History:
 *    $Log:   H:/AUTOPC/HOSTSW/PVCSARCH/INCLUDE/VIOAPI.H_V  $
 * 
 *    Rev 1.4   May 28 1998 15:07:06   PHorenberger
 * Added an include for the VIO registration functions.
 * 
 *    Rev 1.3   Oct 08 1997 19:14:42   PHorenberger
 * Added declarations for VIOInitialize and VIOUninitialize functions
 * 
 *    Rev 1.2   Sep 23 1997 12:19:26   PAULH
 * Added line to include "viotype.h"
 * 
 *    Rev 1.1   Aug 05 1997 18:19:40   PAULH
 * Changes to correlate with the API Spec. submitted to Microsoft
 * 
 *    Rev 1.0   Jun 09 1997 16:51:16   PAULH
 * Initial revision.
 * 
 *    Rev 1.0   Jun 09 1997 16:36:08   PAULH
 * Initial revision.
 * 
 *  Copyright (C) 1997 Vetronix Corp.
 ******************************************************************************/
#if (!defined __VIOAPI_H)
#define __VIOAPI_H 1

// VIO API Initialization function
/**
 * This function initializes the vehicle input/output (I/O) API for a process.
 *
 * @param pvReserved Reserved; set to NULL.
 *
 * @return One of the values described in the following table is returned. Value Description S_OK
 *   API was initialized successfully. CLASS_E_CLASSNOTAVAILABLE Vehicle I/O device manager is not
 *   registered. E_ABORT Startup of the API was aborted.
 *
 * VIOInitialize may be called multiple times by a process. However, if there are no corresponding
 * calls to VIOUninitialize, resources in use by the process may not be freed when the process ends.
 */
STDAPI VIOInitialize(PVOID pReserved);

// VIO API Uninitialize function
/**
 * This function uninitializes the vehicle input/output (I/O) API for a thread.
 *
 * @return None.
 *
 * A call to VIOUninitialize must be made for each call of VIOInitialize. If you do not call
 * VIOUninitialize for every call to VIOInitialize, resources in use by the process may not be freed
 * when the process ends.
 */
STDAPI_(VOID) VIOUninitialize(void);

#include "vioguid.h"
#include "viotype.h"
#include "viobase.h"
#include "vioreg.h"

#endif     // include sentry