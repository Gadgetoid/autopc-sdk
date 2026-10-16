/*******************************************************************************
 *
 *  File:
 *    VIOTYPE.H
 *
 *  Description:
 *    Type and constant declarations used by the VIO API
 *
 *  Original Author:
 *    Paul Horenberger
 *
 *  Modification History:
 *  $Log:   H:/ISLV/AutoPC/PVCS.arc/Develpr_Includes/viotype.h_v  $
 * 
 *    Rev 1.6   Jun 05 1998 16:45:44   PHorenberger
 * Fixed a couple of small syntactical screwups
 * 
 *    Rev 1.5   Jun 05 1998 11:27:48   PHorenberger
 * Changed constants to be consistent with documentation draft of 6/4/98
 * 
 *    Rev 1.4   May 28 1998 15:02:34   PHorenberger
 * Updated values relating to trouble codes returned from
 * the API
 * 
 *    Rev 1.3   Feb 13 1998 16:47:12   PHorenberger
 * Updated enumerations for the new diagnostic item
 * and diagnostic entry interfaces
 * 
 *    Rev 1.2   Nov 10 1997 11:48:24   PHorenberger
 * Removed structs that were used in the original pass at the IVIO_Vehicle
 * interface for the enumerated types that are used by the IVIO_Enumxxx 
 * interfaces now used to get metrics, available devices, and maintenance 
 * information for the vehicle
 * 
 * 
 *    Rev 1.1   Oct 08 1997 19:31:44   PHorenberger
 * Added in enumerations for vehicle manufacturers
 * 
 *    Rev 1.0   Sep 11 1997 15:55:30   PAULH
 * Initial revision.
 *
 *  Copyright (C) 1997 Vetronix Corp.
 ******************************************************************************/
#if (!defined __VIOTYPE_H)
#define __VIOTYPE_H 1
typedef enum tagVIOSTRINGSIZES
{
  VIOMETRICSTRINGSIZE  = 20,
  VIOMAINTNAMESIZE     = 32,
  VIODEVICENAMESIZE    = 24
} VIOSTRINGSIZES;

typedef enum tagVIOVEHICLEMETRIC
{
  VIOVEHICLEMETRIC_MAKE               = 1024,
  VIOVEHICLEMETRIC_MODEL              = 1025,
  VIOVEHICLEMETRIC_YEAR               = 1026,
  VIOVEHICLEMETRIC_VIN                = 1027,
  VIOVEHICLEMETRIC_MANUFACTURER       = 1028,
  VIOVEHICLEMETRIC_DISPLACEMENT       = 1029,
  VIOVEHICLEMETRIC_CYLINDERCOUNT      = 1030,
  VIOVEHICLEMETRIC_FUELTYPE           = 1031,
  VIOVEHICLEMETRIC_FUELDELIVERY       = 1032,
  VIOVEHICLEMETRIC_TRANSMISSION       = 1033,
  VIOVEHICLEMETRIC_TRANSMISSION_GEARS = 1034
} VIOVEHICLEMETRIC;

typedef enum tagVIOMANUFACTURER
{
  VIOMANUFACTURER_UNKNOWN                 = 0,
  VIOMANUFACTURER_ALFA_LANCIA             = 2048,
  VIOMANUFACTURER_ASTON_MARTIN            = 2049,
  VIOMANUFACTURER_AUDI                    = 2050,
  VIOMANUFACTURER_BERTONE                 = 2051,  
  VIOMANUFACTURER_BMW                     = 2052,
  VIOMANUFACTURER_CHRYSLER                = 2053,
  VIOMANUFACTURER_DAIHATSU                = 2054,
  VIOMANUFACTURER_DIAMOND_STAR_MOTORS     = 2055,
  VIOMANUFACTURER_FERRARI                 = 2056,
  VIOMANUFACTURER_FORD                    = 2057,
  VIOMANUFACTURER_FUJI_HEAVY_INDUSTRIES   = 2058,
  VIOMANUFACTURER_GM_CARS                 = 2059,
  VIOMANUFACTURER_GM_TRUCKS               = 2060,
  VIOMANUFACTURER_GM_SATURN               = 2061,
  VIOMANUFACTURER_HONDA                   = 2062,
  VIOMANUFACTURER_HYUNDAI                 = 2063,
  VIOMANUFACTURER_ISUZU                   = 2064,
  VIOMANUFACTURER_JAGUAR                  = 2065,
  VIOMANUFACTURER_KIA                     = 2066,
  VIOMANUFACTURER_LAMBORGHINI             = 2067,
  VIOMANUFACTURER_LAND_ROVER              = 2068,
  VIOMANUFACTURER_LOTUS                   = 2069,
  VIOMANUFACTURER_MASERATI                = 2070,
  VIOMANUFACTURER_MAZDA                   = 2071,
  VIOMANUFACTURER_MERCEDES_BENZ           = 2072,
  VIOMANUFACTURER_MITSUBISHI              = 2073,
  VIOMANUFACTURER_MITSUBISHI_AMERICA      = 2074,
  VIOMANUFACTURER_NISSAN                  = 2075,
  VIOMANUFACTURER_OPEL                    = 2076,
  VIOMANUFACTURER_PEUGEOT                 = 2077,
  VIOMANUFACTURER_PORSHCE                 = 2078,
  VIOMANUFACTURER_RENAULT                 = 2079,
  VIOMANUFACTURER_ROLLS_ROYCE             = 2080,
  VIOMANUFACTURER_ROVER                   = 2081,
  VIOMANUFACTURER_SAAB                    = 2082,
  VIOMANUFACTURER_SUZUKI                  = 2083,
  VIOMANUFACTURER_TOYOTA                  = 2084,
  VIOMANUFACTURER_VOLKSWAGEN              = 2085,
  VIOMANUFACTURER_VOLVO                   = 2086
} VIOMANUFACTURER;

typedef enum tagVIOCYLINDERS
{
  VIOCYLINDERS_NONE = 0,
  VIOCYLINDERS_MIN = 1,
  VIOCYLINDERS_MAX = 32
} VIOCYLINDERS;

typedef enum tagVIOFUELTYPE
{
  VIOFUELTYPE_GAS       = 1,
  VIOFUELTYPE_DIESEL    = 2,
  VIOFUELTYPE_ELECTRIC  = 3,
  VIOFUELTYPE_HYBRID    = 4,
  VIOFUELTYPE_OTHER     = 255
} VIOFUELTYPE;

typedef enum tagVIOFUELDELIVERY
{
  VIOFUELDELIVERY_2_BBL_CARBURETOR              = 1,
  VIOFUELDELIVERY_4_BBL_CARBURETOR              = 2,
  VIOFUELDELIVERY_THROTTLE_BODY_INJECTION       = 3,
  VIOFUELDELIVERY_PORT_INJECTION                = 4,
  VIOFUELDELIVERY_LEAD_ACID_BATTERY             = 5,
  VIOFUELDELIVERY_NICKEL_METAL_HYDRIDE_BATTERY  = 6,
  VIOFUELDELIVERY_OTHER                         = 255
} VIOFUELDELIVERY;

typedef enum tagVIOTRANSMISSION
{
  VIOTRANSMISSION_MANUAL                        = 1,
  VIOTRANSMISSION_AUTOMATIC                     = 2,
  VIOTRANSMISSION_CONTINUOUSLY_VARIABLE         = 3,
  VIOTRANSMISSION_OTHER                         = 255
} VIOTRANSMISSION;

typedef enum tagVIOTRANSMISSIONGEARS
{
  VIOTRANSMISSIONGEARS_LOW         = 1,
  VIOTRANSMISSIONGEARS_HIGH        = 256,
  VIOTRANSMISSIONGEARS_OVERDRIVE   = 0x8000
} VIOTRANSMISSIONGEARS;

typedef enum tagVIOMAINTITEMTYPE
{
  VIOMAINT_ENGINE_OIL_CHANGE       = 1,
  VIOMAINT_TRANSMISSION_OIL_CHANGE = 2,
  VIOMAINT_COOLANT_CHANGE          = 3,
  VIOMAINT_ENGINE_TUNEUP           = 4, 
  VIOMAINT_SPARKPLUG_CHANGE        = 5,
  VIOMAINT_SPARKPLUG_WIRE_CHANGE   = 6,
  VIOMAINT_ENGINE_BELT_REPLACE     = 7,
  VIOMAINT_ROTATE_TIRES            = 8,
  VIOMAINT_REPLACE_TIRES           = 9,
  VIOMAINT_BRAKE_PAD_CHANGE        = 10,
  VIOMAINT_FLUID_LEVEL_CHECK       = 11,
  VIOMAINT_CHASSIS_ALIGNMENT       = 12,
  VIOMAINT_REPLACE_BATTERY         = 13,
  VIOMAINT_USER                    = 256
} VIOMAINTITEMTYPE;

typedef enum tagVIOMAINTENTRYTYPE
{
  VIOMAINTENTRY_NAME                        = 1,
  VIOMAINTENTRY_LOW_INTERVAL                = 2,
  VIOMAINTENTRY_HIGH_INTERVAL               = 3,
  VIOMAINTENTRY_INTERVAL_TYPE               = 4,
  VIOMAINTENTRY_INTERVAL_UNITS              = 5,
  VIOMAINTENTRY_SECONDARY_INTERVAL          = 6,
  VIOMAINTENTRY_SECONDARY_INTERVAL_TYPE     = 7,
  VIOMAINTENTRY_SECONDARY_INTERVAL_UNITS    = 8
} VIOMAINTENTRYTYPE;

typedef enum tagVIOMAINTINTERVALTYPE
{
  VIOMAINTINTERVALTYPE_MILEAGE        = 1,
  VIOMAINTINTERVALTYPE_CALENDAR_TIME  = 2,
  VIOMAINTINTERVALTYPE_RUNNING_TIME   = 3
} VIOMAINTINTERVALTYPE;

typedef enum tagVIOMAINTINTERVALUNITS
{
  VIOMAINTINTERVALUNITS_MILES         = 1,
  VIOMAINTINTERVALUNITS_KILOMETERS    = 2,
  VIOMAINTINTERVALUNITS_MONTHS        = 3,
  VIOMAINTINTERVALUNITS_DAYS          = 4,
  VIOMAINTINTERVALUNITS_HOURS         = 5
} VIOMAINTINTERVALUNITS;

// Values used by IVIO_Device->get_AccessMode()/IVIO_Device->set_AccessMode()
// These are a bitmask of the modes that a IVIO_Device object can operate
typedef enum tagVIODEVICEMODE
{
  VIODEVICEMODE_READ        = 0x0001, // Device can be read
  VIODEVICEMODE_WRITE       = 0x0002 // Device can be written to
} VIODEVICEMODE;

typedef enum tagVIODEVICEACCESS
{
  VIODEVACCESS_SHARED       = 0x0000, // This device can be shared
  VIODEVACCESS_EXCLUSIVE    = 0x8000, // This device has exclusive access 
  VIODEVACCESS_NONE         = 0xFFFF  // The requested access is not available
} VIODEVICEACCESS;

typedef enum tagVIOACCESS
{
  VIODEVMODE_READ        = 0x0001, // Device can be read
  VIODEVMODE_WRITE       = 0x0002, // Device can be written to
} VIOACCESS;

// Values returned from IVIO_Device->get_Status()
typedef enum tagVIODEVSTATUS
{
  VIODEVSTATUS_READY        = 0,    // Device is ready to run
  VIODEVSTATUS_BUSY         = 1,    // Device is busy
  VIODEVSTATUS_UNAVAIL      = 2,    // Device status unavailable
  VIODEVSTATUS_SUSPENDED    = 3     // Device is suspended (low-power operation)
} VIODEVSTATUS;

// Types of measurements taken from a IVIO_Device interface.
typedef enum tagVIOMEASUREMENT
{
  VIOMEASUREMENT_STATE            =  0,
  VIOMEASUREMENT_ONOFF            =  1,
  VIOMEASUREMENT_PERCENTAGE       =  2,
  VIOMEASUREMENT_ROTATIONALSPEED  =  3,
  VIOMEASUREMENT_SPEED            =  4,
  VIOMEASUREMENT_TEMPERATURE      =  5,
  VIOMEASUREMENT_GAGEPRESSURE     =  6,
  VIOMEASUREMENT_ROTATION         =  7,
  VIOMEASUREMENT_VOLTAGE          =  8,
  VIOMEASUREMENT_ABSOLUTEPRESSURE =  9,
  VIOMEASUREMENT_FLOWRATE         = 10,
  VIOMEASUREMENT_DISCRETEMASK     = 11,
  VIOMEASUREMENT_DISTANCE         = 12,
  VIOMEASUREMENT_COLLECTION       = 13
} VIOMEASUREMENT;

// Units used for an IVIO_Device interface
typedef enum tagVIOUNITS
{
  VIOUNITS_ENUM                   =  0,
  VIOUNITS_BINARY                 =  1,
  VIOUNITS_PERCENT                =  2,
  VIOUNITS_RPM                    =  3,
  VIOUNITS_KILOMETERSPERHOUR      =  4,
  VIOUNITS_CELSIUS                =  5,
  VIOUNITS_KILOPASCALSGAGE        =  6,
  VIOUNITS_DEGREES                =  7,
  VIOUNITS_VOLTS                  =  8,
  VIOUNITS_KILOPASCALSABSOLUTE    =  9,
  VIOUNITS_GRAMSPERSECOND         = 10,
  VIOUNITS_BITMASK                = 11,
  VIOUNITS_KILOMETERS             = 12,
  VIOUNITS_DIAGNOSTICITEMS        = 13
} VIOUNITS;

//******************************************************************************
//
// Enumerated Values for the different IVIO_Device interface classes
//
//******************************************************************************

// Ignition Switch Bitmasks
typedef enum tagIGNITIONSWITCHMASK
{
  VIOIGNITIONSWITCH_OFF          = 0x00,
  VIOIGNITIONSWITCH_RUN          = 0x01,
  VIOIGNITIONSWITCH_START        = 0x02,
  VIOIGNITIONSWITCH_ACC          = 0x04
} IGNITIONSWITCHMASK;

// Headlight Switch Bitmasks
typedef enum tagVIOHEADLIGHTSMASK
{
  VIOHEADLIGHTS_OFF              = 0x00,
  VIOHEADLIGHTS_PARKINGLIGHTS    = 0x01,
  VIOHEADLIGHTS_HEADLIGHTS       = 0x02,
  VIOHEADLIGHTS_BRIGHTHEADLIGHTS = 0x04
} VIOHEADLIGHTSMASK;

// Parking Brake states
typedef enum tagVIOPARKINGBRAKEMASK
{
  VIOPARKINGBRAKE_OFF = 0,
  VIOPARKINGBRAKE_ON  = 1
} VIOPARKINGBRAKEMASK;


// PAH 5/29/98
// Updated enumerated values to match the API spec.
// Fuel System States
typedef enum tagVIOFUELSYSTEMSTATUS
{
  VIOFUELSYSTEM_NOT_PRESENT                 = 0,
  VIOFUELSYSTEM_OPENLOOP_NOT_READY_YET      = 1,
  VIOFUELSYSTEM_OPENLOOP_DRIVING_CONDITIONS = 2,
  VIOFUELSYSTEM_OPENLOOP_SYSTEM_FAULT       = 3,
  VIOFUELSYSTEM_CLOSEDLOOP_O2S              = 4,
  VIOFUELSYSTEM_CLOSEDLOOP_FAULT_FROM_O2S   = 5
} VIOFUELSYSTEMSTATUS;


// PAH 5/29/98
// Added explicit values to enumeration to match API spec.
// Type of fuel trim to read
// Used by CLSID_VIO_FUEL_TRIM
typedef enum tagVIOFUELTRIM
{
  VIOFUELTRIM_SHORTTERM = 0,
  VIOFUELTRIM_LONGTERM  = 1
} VIOFUELTRIM;

// Gear Position
typedef enum tagVIOGEAR
{
  VIOGEAR_NEUTRAL                = 0,
  VIOGEAR_FIRST                  = 1,   // Manual First Gear
  VIOGEAR_MAX                    = 253, // Manual Highest Gear
  VIOGEAR_OVERDRIVE              = 254, // Manual or Generic Overdrive
  VIOGEAR_REVERSE                = 255, // Reverse Gear (Automatic or Manual)
  VIOGEAR_DRIVE                  = 256, // Generic Drive gear
  VIOGEAR_DRIVE_1                = 257, // Same as VIOGEAR_FIRST + 256
  VIOGEAR_DRIVE_MAX              = 509, // Same as VIOGEAR_MAX + 256
  VIOGEAR_DRIVE_OVERDRIVE        = 510  // Same as VIOGEAR_OVERDRIVE + 256
} VIOGEAR;

// Bitmasks used for determining which door switches are active
typedef enum tagVIODOORSWITCHES
{
  VIODOOR_LEFT_FRONT     = 0x00000001,
  VIODOOR_LEFT_REAR      = 0x00000002,
  VIODOOR_LEFT_REAR2     = 0x00000004,
  VIODOOR_LEFT_REAR3     = 0x00000008,
  VIODOOR_LEFT_REAR4     = 0x00000010,
  VIODOOR_LEFT_REAR5     = 0x00000020,
  VIODOOR_LEFT_REAR6     = 0x00000040,
  VIODOOR_LEFT_REAR7     = 0x00000080,
  VIODOOR_RIGHT_FRONT    = 0x00000100,
  VIODOOR_RIGHT_REAR     = 0x00000200,
  VIODOOR_RIGHT_REAR2    = 0x00000400,
  VIODOOR_RIGHT_REAR3    = 0x00000800,
  VIODOOR_RIGHT_REAR4    = 0x00001000,
  VIODOOR_RIGHT_REAR5    = 0x00002000,
  VIODOOR_RIGHT_REAR6    = 0x00004000,
  VIODOOR_RIGHT_REAR7    = 0x00008000,
  VIODOOR_TRUNK          = 0x00010000,
  VIODOOR_LIFTGATE       = 0x00020000,
  VIODOOR_REAR           = 0x00040000,
  VIODOOR_REAR_LEFT      = 0x00080000,
  VIODOOR_REAR_RIGHT     = 0x00100000
} VIODOORSWITCHES;

// Bitmasks used for determining lock status
typedef enum tagVIOLOCKS
{
  VIOLOCKS_UNLOCKED = 0,
  VIOLOCKS_LOCKED   = 1,
  VIOLOCKS_TOGGLE   = 2
} VIOLOCKS;

// Enumerations for latches that can be released
typedef enum tagVIOLATCH
{
  VIOLATCH_HOOD     = 0x01,
  VIOLATCH_TRUNK    = 0x02,
  VIOLATCH_GAS_CAP  = 0x04
} VIOLATCH;

// Bitmasks for determining Light(s) status
typedef enum tagVIOLIGHTSTATUS
{
  VIOLIGHTS_DOME        = 0x0001,   // Dome lighting
  VIOLIGHTS_DASH        = 0x0002,   // Dash light (on/off only, no analog)
  VIOLIGHTS_DRIVING     = 0x0004,   // Driving lights (separate from headlights)
  VIOLIGHTS_LEFT_VISOR  = 0x0008,   // Left visor light
  VIOLIGHTS_RIGHT_VISOR = 0x0010,   // Right light
  VIOLIGHTS_LEFT_MAP    = 0x0020,   // Left map light
  VIOLIGHTS_RIGHT_MAP   = 0x0040,   // Right map light
  VIOLIGHTS_LEFT_REAR   = 0x0080,   // Left rear passenger lighting
  VIOLIGHTS_RIGHT_REAR  = 0x0100,   // right rear passenger lighting
  VIOLIGHTS_TRUNK       = 0x0200,   // Trunk lighting
} VIOLIGHTSTATUS;

// Trouble Codes
// Data value identifiers for data values returned by IVIO_EnumDiagnosticEntry
typedef enum tagVIODIAGNOSTICENTRYVALUES
{
  VIODIAGENTRY_SYSTEM     = 0,   // Data value is the major system originating 
                                 // the code
  VIODIAGENTRY_SUBSYSTEM  = 1,   // Data value is the subsystem originating the 
                                 // code
  VIODIAGENTRY_SAE_CODE   = 2,   // The SAE defined trouble code value (optional)
  VIODIAGENTRY_LAMP_FLAG  = 3    // Is the Malfunction Indicator Lamp (MIL) on
} VIODIAGNOSTICENTRYVALUES;

// Major system that a trouble code originated from
typedef enum tagVIOTROUBLECODESYSTEM
{
  VIOTC_SYS_UNKNOWN      = 0,
  VIOTC_SYS_POWERTRAIN   = 1,
  VIOTC_SYS_BODY         = 2,
  VIOTC_SYS_CHASSIS      = 3,
  VIOTC_SYS_NETWORK      = 4
} VIOTROUBLECODESYSTEM;

// Subsystems where trouble codes originate
// Note: Not all subsystems supported in all vehicles
typedef enum tagVIOTROUBLECODESUBSYSTEM
{
  VIOTC_SUBSYS_UNKNOWN               = 0,
  // Powertrain subsystems
  VIOTC_FUEL_AIR_METERING            = 1,  // Fuel and Air Metering DTCs
  VIOTC_IGNITION_SYSTEM_OR_MISFIRE   = 2,  // Ignition System or Misfire DTCs
  VIOTC_AUX_EMISSION_CONTROL         = 3,  // Auxiliary Emission Control DTCs
  VIOTC_VEHSPEED_IDLE_AUXINPUTS      = 4,  // Vehicle Speed, Idle Control, and
                                           // Auxiliary Inputs DTCs
  VIOTC_COMPUTER_AUXOUTPUTS          = 5,  // Computer and Auxiliary Outputs DTCs
  VIOTC_TRANSMISSION                 = 6,  // Transmission DTCs
  // Chassis subsystems
  VIOTC_ANTILOCK_BRAKES              = 32, // Antilock brake (ABS) DTCs
  VIOTC_TRACTION_CONTROL             = 33, // Traction Control DTCs
  VIOTC_STEERING                     = 34, // Steering related DTCs
  VIOTC_SUSPENSION                   = 35, // Suspension related (Active suspension) 
  // Body subsystems
  VIOTC_SUPPLEMENTAL_RESTRAINTS      = 64, // SIR (Airbag) DTCs
  VIOTC_CLIMATE_CONTROL              = 65, // Climate control DTCs
  VIOTC_INSTRUMENT_PANEL             = 66, // Instrument panel DTCs
  VIOTC_MEMORY_SEATS_MIRROR          = 67, // Automatic seat mirror DTCs
  VIOTC_LIGHTING_CONTROL             = 68, // Lighting control DTCs
  VIOTC_ANTI_THEFT                   = 69, // Anti-theft/alarm DTCs
  VIOTC_TRIP_COMPUTER                = 70, // Onboard trip computer DTCs
  // Unknown subsystem			
  VIOTC_SUBSYSTEM_OTHER              = 255 // Other undefined subsystem
} VIOTROUBLECODESUBSYSTEM;

// Device metrics structure used to identify a device and determine how data from
// the device is expressed device is expressed
/**
 * This structure provides details about a vehicle input/output (I/O) device.
 */
typedef struct tagVIODEVICEMETRICS
{
  /**
   * Class identifier (CLSID) of this particular device.
   */
  CLSID      clsidDevice;                     // The CLSID of this particular device
  /**
   * Null-terminated string that contains the name of the device.
   */
  TCHAR      szDeviceName[VIODEVICENAMESIZE]; // The name of the device
  /**
   * Group of flags reflecting a device's possible access modes. It is one of the values shown in the
   * following table. Access mode Value VIODEVICEMODE_READ 0x0001 VIODEVICEMODE_WRITE 0x0002
   */
  DWORD      grfModes;                        // Group of flags reflecting devices possible access modes (read, write, sharable)
  /**
   * Lower bound of the data value. For specific values, see "CLSIDs for the Auto PC." For example,
   * CLSID_VIO_VEHICLE_SPEED component's low value is 0.
   */
  VARIANT    vRangeLow;                       // Data value's lower bound
  /**
   * Upper bound of the data value. For specific values, see "CLSIDs for the Auto PC." For example,
   * the CLSID_VIO_VEHICLE_SPEED component's high value is 383.
   */
  VARIANT    vRangeHigh;                      // Data value's upper bound
  /**
   * Specifies the type of data value, such as distance, current, and voltage. It is one of the
   * following flags: Data value type Value VIOMEASUREMENT_STATE 0 VIOMEASUREMENT_ONOFF 1
   * VIOMEASUREMENT_PERCENTAGE 2 VIOMEASUREMENT_ROTATIONALSPEED 3 VIOMEASUREMENT_SPEED 4
   * VIOMEASUREMENT_TEMPERATURE 5 VIOMEASUREMENT_GAGEPESSURE 6 VIOMEASUREMENT_ROTATION 7
   * VIOMEASUREMENT_VOLTAGE 8 VIOMEASUREMENT_ABSOLUTEPRESSURE 9 VIOMEASUREMENT_FLOWRATE 10
   * VIOMEASUREMENT_DISCRETEMASK 11 VIOMEASUREMENT_DISTANCE 12 VIOMEASUREMENT_COLLECTION 13
   */
  DWORD      dwValueType;                     // Type of data value (distance, current, voltage, etc.)
  /**
   * Specifies the units in which data value is expressed, such as kilometers, volts, degrees. It is
   * one of the following flags: Units Value VIOUNITS_ENUM 0 VIOUNITS_BINARY 1 VIOUNITS_PERCENT 2
   * VIOUNITS_RPM 3 VIOUNITS_KILOMETERSPERHOUR 4 VIOUNITS_CELSIUS 5 VIOUNITS_KILOPASCALSGAGE 6
   * VIOUNITS_DEGREES 7 VIOUNITS_VOLTS 8 VIOUNITS_KILOPASCALSABSOLUTE 9 VIOUNITS_GRAMSPERSECOND 10
   * VIOUNITS_BITMASK 11 VIOUNITS_KILOMETERS 12 VIOUNITS_DIAGNOSTICITEMS 13
   */
  DWORD      dwValueUnits;                    // Units data value is expressed in
  /**
   * Long integer that contains the exponent used to determine number of digits to the right of the
   * decimal place.
   */
  LONG       lExponent;                       // Power of 10 to multiply data 
                                              // values by to get proper scale
                                              // (i.e. lPrecision = -3, then multiply by 0.001
                                              //       lPrecision = 0, then leave unchanged)
} VIODEVICEMETRICS, *LPVIODEVICEMETRICS;



#endif // include sentry
