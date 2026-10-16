/*******************************************************************************
 *
 *  File:
 *    VIOMDTYPE.H
 *
 *  Description:
 *    Type declarations for structures used by minidrivers to communicate with
 *    the API
 *
 *  Original Author:
 *    Paul Horenberger
 *
 *  Modification History:
 *  $Log:   H:/AUTOPC/HOSTSW/PVCSARCH/VIO_API/viomdtype.h_v  $
 * 
 *    Rev 1.0   May 28 1998 14:52:06   PHorenberger
 * Declarations of types used by the minidrivers.  This
 * is primarily used to define the structures used to move
 * trouble codes from the minidrivers to the API.
 *
 *  Copyright (C) 1998 Vetronix Corp.
 ******************************************************************************/
#if (!defined __VIOMDTYPE_H)
#define __VIOMDTYPE_H 1

//******************************************************************************
//
// Class for dealing with diagnostic code information
//
//******************************************************************************
//
// Information about an extra field in a given diagnostic information entry
// Used in VIODIAGNOSTICINFO structure below
//
typedef struct tagVIODIAGNOSTICFIELD
{
  DWORD    cbFixed;    // The size of the fixed data portion
  DWORD    cbData;     // The size of the data array in bytes
  DWORD    vdfID;      // The ID of the extra data
  VARTYPE  vdfType;    // The type of the extra data
  BYTE     vdfData[1]; // The first byte of the extra data
                       // Cast this to the appropriate type based on the vtType
} VIODIAGNOSTICFIELD;

typedef VIODIAGNOSTICFIELD *PVIODIAGNOSTICFIELD;
typedef const PVIODIAGNOSTICFIELD PCVIODIAGNOSTICFIELD;

//
// Structure passed back from the VIO diagnostic code minidriver that returns
// a diagnostic information entry
//
typedef struct tagVIODIAGNOSTICINFO
{
  DWORD              cbFixed;         // The size of the fixed portion of the 
                                      // structure
  DWORD              cExtraFields;    // The number of extra fields in the 
                                      // structure
  DWORD              dwSystem;        // The system that returned the diagnostic
                                      // info
  DWORD              dwSubsystem;     // The subsystem that returned the 
                                      // diagnostic info
  VIODIAGNOSTICFIELD vdiFields[1];
} VIODIAGNOSTICINFO;

typedef VIODIAGNOSTICINFO *PVIODIAGNOSTICINFO;
typedef const PVIODIAGNOSTICINFO PCVIODIAGNOSTICINFO;

//
// Structure that returns the array of diagnostic info structures
//
typedef struct tagVIODIAGNOSTICARRAY
{
  DWORD             cDiagnosticInfo;  // The number of diagnostic information
                                      // items that are present
  DWORD             cbDiagnosticInfo; // The size in bytes of the diagnostic
                                      // information being returned
  VIODIAGNOSTICINFO vdiItems[1];      // Address of the first diagnost 
                                      // information items being returned
} VIODIAGNOSTICARRAY;

typedef VIODIAGNOSTICARRAY *PVIODIAGNOSTICARRAY;
typedef const PVIODIAGNOSTICARRAY PCVIODIAGNOSTICARRAY;

#endif // include sentry
