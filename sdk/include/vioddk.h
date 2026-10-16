/*******************************************************************************
 *
 *  File:
 *    VIODDK.H
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
 *    $Log:   H:/AUTOPC/HOSTSW/PVCSARCH/INCLUDE/VIODDK.H_V  $
 * 
 *    Rev 1.3   May 28 1998 14:43:06   PHorenberger
 * Changed the standard include files for the DDK types
 * to include VIOMDTYPE.H and VIOGUID.H.  Removed 
 * VIOMDGUID.H, the contents have been moved to VIOGUID.H
 * 
 *    Rev 1.2   Sep 23 1997 12:23:06   PAULH
 * Removed declarations from this file and put them 
 * into files "viomdbase.h" and "viomdguid.h" for 
 * declarations of interfaces and GUIDs respectively
 * 
 *    Rev 1.1   Jul 17 1997 09:46:02   PAULH
 * 
 *    Rev 1.0   Jul 14 1997 17:02:46   PAULH
 * Initial revision.
 * 
 *  Copyright (C) 1997 Vetronix Corp.
 ******************************************************************************/
#if (!defined __VIODDK_H)
#define __VIODDK_H 1
#include "vioguid.h"
#include "viomdtype.h"
#include "viomdbase.h"

#endif // include sentry
