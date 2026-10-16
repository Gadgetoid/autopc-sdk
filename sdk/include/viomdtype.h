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
/**
 * This structure provides an extra attribute about a diagnostic code.
 */
typedef struct tagVIODIAGNOSTICFIELD
{
  /**
   * Size, in bytes, of the fixed diagnostic members in the structure.
   */
  DWORD    cbFixed;    // The size of the fixed data portion
  /**
   * Number of bytes in the vdfData member for this diagnostic item attribute.
   */
  DWORD    cbData;     // The size of the data array in bytes
  /**
   * Specifies the identifier of the attribute returned from IVIO_EnumDiagnosticEntry interface. It is
   * one of the values shown in the following table. Data value type Value VIODIAGENTRY_SYSTEM 0
   * VIODIAGENTRY_SUBSYSTEM 1 VIODIAGENTRY_SAE_CODE 2 VIODIAGENTRY_LAMP_FLAG 3
   */
  DWORD    vdfID;      // The ID of the extra data
  /**
   * Type of data represented in the vdfData member.
   */
  VARTYPE  vdfType;    // The type of the extra data
  /**
   * First byte of data for the diagnostic item attribute. Number of bytes in the array set in the
   * cbData member.
   */
  BYTE     vdfData[1]; // The first byte of the extra data
                       // Cast this to the appropriate type based on the vtType
} VIODIAGNOSTICFIELD;

typedef VIODIAGNOSTICFIELD *PVIODIAGNOSTICFIELD;
typedef const PVIODIAGNOSTICFIELD PCVIODIAGNOSTICFIELD;

//
// Structure passed back from the VIO diagnostic code minidriver that returns
// a diagnostic information entry
//
/**
 * This structure provides the data about a single code retrieved from the vehicle.
 */
typedef struct tagVIODIAGNOSTICINFO
{
  /**
   * Size, in bytes, of the fixed diagnostic members in the structure.
   */
  DWORD              cbFixed;         // The size of the fixed portion of the 
                                      // structure
  /**
   * Number of extra members provided for this diagnostic item.
   */
  DWORD              cExtraFields;    // The number of extra fields in the 
                                      // structure
  /**
   * Specifies the identifier of the system providing this diagnostic code. It is one of values shown
   * in the following table. Data value type Value VIOTC_SYS_UNKNOWN 0 VIOTC_SYS_POWERTRAIN 1
   * VIOTC_SYS_BODY 2 VIOTC_SYS_CHASSIS 3 VIOTC_SYS_NETWORK 4
   */
  DWORD              dwSystem;        // The system that returned the diagnostic
                                      // info
  /**
   * Specifies the identifier of the subsystem providing this diagnostic code. It is one of the values
   * shown in the following table. Data value type Value VIOTC_SUBSYS_UNKNOWN 0
   * VIOTC_FUEL_AIR_METERING 1 VIOTC_IGNITION_SYSTEM_OR_MISFIRE 2 VIOTC_AUX_EMISSION_CONTROL 3
   * VIOTC_VEHSPEED_IDLE_AUXINPUTS 4 VIOTC_COMPUTER_AUX_OUTPUTS 5 VIOTC_TRANSMISSION 6
   * VIOTC_ANTILOCK_BRAKES 32 VIOTC_TRACTION_CONTROL 33 VIOTC_STEERING 34 VIOTC_SUSPENSION 35
   * VIOTC_SUPPLEMENTAL_RESTRAINTS 64 VIOTC_CLIMATE_CONTROL 65 VIOTC_INSTRUMENT_PANEL 66
   * VIOTC_MEMORY_SEATS_MIRROR 67 VIOTC_LIGHTING_CONTROL 68 VIOTC_ANTI_THEFT 69 VIOTC_TRIP_COMPUTER 70
   * VIOTC_SUBSYSTEM_OTHER 255
   */
  DWORD              dwSubsystem;     // The subsystem that returned the 
                                      // diagnostic info
  /**
   * First VIODIAGNOSTICFIELD structure that contains extra attributes about the diagnostic code.
   */
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
