/*
    IPOSNAV.H

    Definition of an IPosNav interface for a PosNav object.
    This custom interface is only supported from DLL-based objects.

    Copyright (c) 1996 Microsoft Corporation, All rights reserved.
*/

//We use the OLE 2.0 macro to define a new interface.

#ifndef _INC_IPOSNAV
#define _INC_IPOSNAV

#include "pngen.h"

#undef  INTERFACE
#define INTERFACE IPosNav

#ifndef LPLPVOID
    typedef LPVOID* LPLPVOID;
#endif

/**
 * This interface provides methods required to utilize Auto PC related Global Positioning System
 * (GPS) capabilities.
 *
 * The IPosNav interface handles most GPS-related tasks.
 *
 * The only supported Positioning and Navigation device is the GPS device.
 */
DECLARE_INTERFACE_(IPosNav, IUnknown)
{
    //IUnknown members.
    STDMETHOD(QueryInterface)   (THIS_ REFIID, LPLPVOID) PURE;
    STDMETHOD_(ULONG, AddRef)   (THIS) PURE;
    STDMETHOD_(ULONG, Release)  (THIS) PURE;

    //IPosNav members.
    /**
     * This method finds all connected Positioning and Navigation devices on the system.
     *
     * @param pDevArray Pointer to an array of PNDEVICE pointers. This parameter returns the first item
     *   in a linked list of PNDEVICE structures. Destroy this list with the DeleteDeviceList method.
     * @param pdwNumDev Pointer to the DWORD that contains the number of Positioning and Navigation
     *   devices found
     *
     * @return One of the values described in the following table is returned. Value Description S_OK
     *   Success E_FAIL An unspecified error occurred. E_INVALIDARG One or more arguments are invalid.
     *   TYPE_E_DLLFUNCTIONNOTFOUND The method was not defined in the specified DLL. REGDB_E_READREGDB A
     *   registry key could not be read. PNAPI_E_INVALIDREGDBVALUE There is an invalid value in the
     *   registry. PNAPI_E_REGDBCLOSEKEY A registry key cannot be closed. PNAPI_E_MEMFREE Memory or
     *   resource cannot be freed. PNAPI_E_BADOS There is an invalid operating system version.
     *   E_OUTOFMEMORY The position and navigation API (PNAPI) is out of memory.
     *
     * The IPosNav::FindDevices method returns data for Positioning and Navigation devices in an unknown
     * status, but does not return data for non-operational devices.
     */
    STDMETHOD(FindDevices) (ppPNDEVICE,
                                 pDWORD) PURE;

    /**
     * This method deletes a linked list of PNDEVICE structures.
     *
     * @param pPNDeviceHead Pointer to the first structure in the linked list.
     *
     * @return S_OK indicates success. If an error occurs, the appropriate HRESULT value is returned.
     *
     * After opening the selected Positioning and Navigation device, delete the linked list of PNDEVICE
     * structures that you retrieved with the FindDevices method by calling the DeleteDeviceList method.
     */
    STDMETHOD(DeleteDeviceList)    (pPNDEVICE) PURE;

    /**
     * This method opens a Positioning and Navigation device for communication.
     *
     * @param phPN Pointer to a Positioning and Navigation device handle. The phPNDevice type is
     *   declared as LPVOID. If successful, a valid Positioning and Navigation handle is returned.
     * @param pDevice Pointer to the PNDEVICE structure for the device to be opened. This structure is
     *   returned by FindDevices.
     *
     * @return One of the values described in the following table is returned. Value Description S_OK
     *   Success E_FAIL An unspecified error occurred. E_INVALIDARG One or more arguments are invalid.
     *   E_OUTOFMEMORY The position and navigation API (PNAPI) has run out of memory. REGDB_E_READREGDB A
     *   registry key could not be read. PNAPI_E_REGDBCLOSEKEY A registry key could not be closed.
     *   PNAPI_E_LOADDLL DLL could not be loaded. PNAPI_E_DEVICEUNAVAILABLE The Positioning and Navigation
     *   device is unavailable; it could be unplugged or dead.
     */
    STDMETHOD(OpenDevice)  (phPNDevice,
                                 pPNDEVICE) PURE;

    /**
     * This method closes a Positioning and Navigation device.
     *
     * @param hPN Handle to the Positioning and Navigation device to be closed
     *
     * @return One of the values described in the following table is returned. Value Description S_OK
     *   Success E_FAIL An unspecified error occurred. E_INVALIDARG One or more arguments are invalid.
     *   PNAPI_E_DEVICEUNAVAILABLE The Positioning and Navigation device is unavailable; it could be
     *   unplugged or dead. PNAPI_E_MEMFREE The memory or resource cannot be freed.
     *
     * If this method is not called upon exiting, position and navigation API (PNAPI) resources are not
     * deleted.
     *
     * This method must wait for pending calls to finish before stopping calls to a Positioning and
     * Navigation device. It may pause briefly before returning.
     */
    STDMETHOD(CloseDevice)      (hPNDevice) PURE;

//    STDMETHOD(ResetDevice)  (hPNDevice,
//                                 PNReset_t) PURE;

//    STDMETHOD(GetVersion)  (pDWORD,
//                                 pDWORD) PURE;

    /**
     * This method sends data to either the Positioning and Navigation device or the registry.
     *
     * @param hPN Handle to the Positioning and Navigation device to use
     * @param pBuffer Pointer to a buffer to hold the data. The format is determined by Data_Type.
     * @param dwSize Specifies, in bytes, the size of pBuffer
     * @param Data_Type The following Positioning and Navigation device data types can be set. Value
     *   Description Structure type PN_DT_ACCURACY Accuracy data PNACCURACY PN_DT_ALMANAC Almanac data
     *   PNALMANAC PN_DT_CONFIG Configuration data PNCONFIG PN_DT_DEVICE Device profile data PNDEVICE
     *   PN_DT_DEVICESTATE Device state data PNDEVSTATE PN_DT_POSITION Longitude, latitude, and altitude
     *   position data PNPOSITION PN_DT_SETTINGS Settings data PNSETTINGS PN_DT_STATION Station data
     *   PNSTATION PN_DT_TIME Time data PNTIME PN_DT_TM Time data PNTM
     *
     * @return One of the values described in the following table is returned. Value Description S_OK
     *   Success E_FAIL An unspecified error occurred. E_INVALIDARG One or more arguments are invalid.
     *   E_NOTIMPL Ability to set the specified data type, such as PN_DT_VELOCITY, is not implemented.
     *   PNAPI_E_DEVICEUNAVAILABLE The Positioning and Navigation device is unavailable; it could be
     *   unplugged or dead. PNAPI_E_NOACCESS The application has insufficient permissions.
     *
     * Position and time can be set to enable the Positioning and Navigation device to find its position
     * more quickly.
     *
     * The configuration data in the PNCONFIG structure is stored in the registry by this method. The
     * settings contained are also used to update the configuration of the Positioning and Navigation
     * device. If any parameters do not apply to the Positioning and Navigation device, they are ignored
     * by the position and navigation API (PNAPI).
     *
     * Almanac data is GPS-specific and is received from the Positioning and Navigation device by the
     * IPosNav::GetData method. The almanac details are stored in the registry only through the PNCONFIG
     * structure. The almanac data should not be altered. It provides accurate GPS satellite position
     * data. If almanac data is passed to this method, the system may acquire a GPS satellite position
     * faster.
     *
     * PNAPI enables various OEM-defined PNData_t enumerations to be passed through this method so that
     * specific features can be made available. OEM vendors should provide details about how they have
     * implemented their structures.
     *
     * All data is received from the Positioning and Navigation device except PNCONFIG data, which is
     * taken from the registry.
     *
     * Only applications with read/write permission can use this method, except when the user wishes to
     * change permissions.
     *
     * The PNTIME structure contains an accurate time in Universal Coordinated Time (UTC), also known as
     * Greenwich mean time (GMT).
     */
    STDMETHOD(SetData)     (hPNDevice,
                                 LPVOID,
                                 DWORD,
                                 PNData_t) PURE;

//    STDMETHOD(SetPosition) (hPNDevice,
//                                 pPNPOSLLA) PURE;

//    STDMETHOD(SetTime)     (hPNDevice,
//                                 pPNTM) PURE;

    /**
     * This method gets various types of data from a Positioning and Navigation device.
     *
     * @param hPN Handle to the Positioning and Navigation device to use
     * @param pBuffer Pointer to the buffer that receives the data
     * @param dwSize Specifies, in bytes, the size of pBuffer
     * @param DataType Type of data to get from the Positioning and Navigation device. The following
     *   types of data can be requested. Value Description Structure type PN_DT_ACCURACY Accuracy data
     *   PNACCURACY PN_DT_ALMANAC Almanac data PNALMANAC PN_DT_CONFIG Configuration data PNCONFIG
     *   PN_DT_DEVICE Device profile data PNDEVICE PN_DT_DEVICESTATE Device state data PNDEVSTATE
     *   PN_DT_POSITION Longitude, latitude, and altitude position data PNPOSITION PN_DT_SETTINGS Settings
     *   data PNSETTINGS PN_DT_STATION Station data PNSTATION PN_DT_TIME Time data PNTIME PN_DT_TM Time
     *   data PNTM PN_DT_VELOCITY Velocity data PNVELOCITY
     *
     * @return One of the values described in the following table is returned. Value Description S_OK
     *   Success E_FAIL An unspecified error occurred. E_INVALIDARG One or more arguments are invalid.
     *   PNAPI_E_DEVICEUNAVAILABLE The Positioning and Navigation device is unavailable; it could be
     *   unplugged or dead. PNAPI_E_NOCALLSTARTED No call has been started yet. PNAPI_E_NODATAYET No data
     *   has been received from the Positioning and Navigation device yet.
     *
     * PNAPI enables various OEM-defined PNData_t enumerations to be passed through this method so that
     * specific features can be made available. OEM vendors should provide details about how they have
     * implemented their structures.
     *
     * All data is received from the Positioning and Navigation device except PNCONFIG data, which is
     * taken from the registry.
     *
     * The almanac data is GPS-specific and provides system satellite position data.
     */
    STDMETHOD(GetData)     (hPNDevice,
                                 LPVOID,
                                 DWORD,
                                 PNData_t) PURE;

//    STDMETHOD(GetPosition) (hPNDevice,
//                                 pPNPOSITION) PURE;

//    STDMETHOD(GetVelocity) (hPNDevice,
//                                 pPNVELOCITY) PURE;

//    STDMETHOD(GetDeviceState)  (hPNDevice,
//                                     pPNDEVSTATE) PURE;

//    STDMETHOD(GetAccuracy) (hPNDevice,
//                                 pPNACCURACY) PURE;

    /**
     * This method starts a call to get data from the Positioning and Navigation device.
     *
     * @param hPN Handle to the Positioning and Navigation device to use.
     * @param Call Type of data to retrieve from Positioning and Navigation device. All PNData_t calls
     *   valid for the GetData function can be used for Call.
     * @param dwPeriod Specifies, in milliseconds, the time period between updates of data. If dwPeriod
     *   equals 0, only one call is made, and you do not need to stop the call with IPosNav::StopCall. If
     *   dwPeriod equals 1, the call can be made as rapidly as the device permits. If dwPeriod equals any
     *   other value, the StartCall method interprets that value as a period of time.
     *
     * @return One of the values described in the following table is returned. Value Description S_OK
     *   Success E_FAIL An unspecified error occurred. E_INVALIDARG One or more arguments are invalid.
     *   PNAPI_E_DEVICEUNAVAILABLE The Positioning and Navigation device is unavailable; it could be
     *   unplugged or dead. PNAPI_E_DATAUNAVAILABLE The data is unavailable. PNAPI_S_CALLALREADYSTARTED A
     *   warning that indicates a call was already started. PNAPI_S_PERIODTOOSMALL A Positioning and
     *   Navigation device is unable to support a call period at the requested speed.
     *
     * This method instructs the device to update its associated data structures at specified intervals.
     * Through the GetData method, a user can obtain current data from the Positioning and Navigation
     * device's data structures within the position and navigation API (PNAPI) as often as needed.
     */
    STDMETHOD(StartCall)   (hPNDevice,
                                 PNData_t,
                                 DWORD) PURE;

    /**
     * This method stops a call to the Positioning and Navigation device.
     *
     * @param hPN Handle to the Positioning and Navigation device in use.
     * @param Call Type of data to retrieve from the Positioning and Navigation device. All PNData_t
     *   calls valid for the GetData function can be used for Call.
     *
     * @return One of the values described in the following table is returned. Value Description S_OK
     *   Success E_FAIL An unspecified error occurred. E_INVALIDARG One or more arguments are invalid.
     *   PNAPI_E_DEVICEUNAVAILABLE The Positioning and Navigation device is unavailable; it could be
     *   unplugged or dead. PNAPI_E_NOCALLSTARTED No call has been started yet.
     *
     * If a call has been started using IPosNav::StartCall with the dwPeriod set to 0, then the call
     * does not need to be stopped with IPosNav::StopCall. A value of 0 indicates the call is made once,
     * and then stopped.
     */
    STDMETHOD(StopCall)    (hPNDevice,
                                 PNData_t) PURE;

    STDMETHOD(StartDirectCall) (hPNDevice,
                                     PNData_t,
                                     DWORD,
                                     HWND) PURE;

    STDMETHOD(StopDirectCall)  (hPNDevice,
                                     PNData_t) PURE;

//    STDMETHOD(LLAToXYZ)    (pPNPOSXYZ,
//                                 const pPNPOSLLA,
//                                 PNDatum_t) PURE;

//    STDMETHOD(XYZToLLA)    (pPNPOSLLA,
//                                 const pPNPOSXYZ,
//                                 PNDatum_t) PURE;

//    STDMETHOD(DatumToDatum)    (pPNPOSLLA,
//                                     PNDatum_t,
//                                     PNDatum_t) PURE;

    /**
     * This method converts latitude and longitude data from degrees to radians.
     *
     * @param pLLAPos Pointer to a PNPOSLLA structure that contains the latitude, longitude, and
     *   altitude data. The structure is returned with the same position in radians.
     *
     * @return S_OK indicates success. E_INVALIDARG indicates that one or more arguments are invalid.
     *
     * If the PNPOSLLA structure contains a latitude and a longitude expressed in degrees, as indicated
     * by a FALSE value for the PNSOLLA fRadians parameter, this method converts those values to radians
     * by multiplying those values by pi/180. This method converts those values in place, so that the
     * PNSOLLA structure contains latitude and longitude values expressed in radians after this method
     * returns.
     */
    STDMETHOD(DegreesToRadians)    (pPNPOSLLA) PURE;

    /**
     * This method converts latitude and longitude data from radians to degrees.
     *
     * @param pLLAPos Pointer to a PNPOSLLA structure that contains latitude, longitude, and altitude
     *   data. The structure is returned with the same position in degrees.
     *
     * @return S_OK indicates success. E_INVALIDARG indicates one or more arguments are invalid.
     *
     * If the PNPOSLLA structure contains a latitude and a longitude expressed in radians, as indicated
     * by a TRUE value for the PNSOLLA fRadians parameter, this method converts those values to degrees
     * by multiplying those values by 180/pi. This method converts those values in place, so that the
     * PNSOLLA structure contains latitude and longitude values expressed in degrees after this method
     * returns.
     */
    STDMETHOD(RadiansToDegrees)    (pPNPOSLLA) PURE;

    /**
     * This method converts east, north, and up velocity data to a bearing and two speeds.
     *
     * @param pBearVel Pointer to a PNVELBEAR structure to store bearing data.
     * @param pENUVel Pointer to a PNVELENU structure that contains velocity data.
     *
     * @return S_OK indicates success. E_INVALIDARG indicates one or more arguments are invalid.
     */
    STDMETHOD(VelocityToBearing)   (pPNVELBEAR,
                                         const pPNVELENU) PURE;

    /**
     * This method converts a bearing and two speeds to east, north, and up velocities.
     *
     * @param pENUVel Pointer to a PNVELENU structure that contains the velocity data
     * @param pBearVel Pointer to a PNVELBEAR structure to store the bearing data
     *
     * @return S_OK indicates success. E_INVALIDARG indicates that one or more arguments are invalid.
     *
     * The horizontal speed and bearing members of the PNVELBEAR structure define a velocity vector in
     * the plane defined by the north to south and east to west axes. This method resolves that vector
     * into northward and eastward components. A southward velocity is represented as a negative north
     * velocity, and an westward velocity is represented as a negative east velocity.
     */
    STDMETHOD(BearingToVelocity)   (pPNVELENU,
                                         const pPNVELBEAR) PURE;

    /**
     * This method converts a time in the format specified by the PNTM structure to the format specified
     * by the Windows CE SYSTEMTIME structure.
     *
     * @param pTime Pointer to a structure that receives the time in the format specified by the
     *   SYSTEMTIME structure.
     * @param pNTM Pointer to the time to be converted, in the format specified by the PNTM structure.
     *
     * @return S_OK indicates success. E_FAIL indicates that unspecified error occurred. E_INVALIDARG
     *   indicates one or more arguments are invalid.
     */
    STDMETHOD(PNTMToWintm) ( SYSTEMTIME&,
                                  const PNTM& ) PURE;

    /**
     * This method converts a time in the format specified by the Windows CE SYSTEMTIME structure to the
     * format specified by the PNTM structure.
     *
     * @param pNTM Pointer to a structure that receives the time in the format specified by the PNTM
     *   structure.
     * @param pTime Pointer to the time to be converted, in the format specified by the Windows CE
     *   SYSTEMTIME structure.
     *
     * @return S_OK indicates success. E_FAIL indicates that unspecified error occurred. E_INVALIDARG
     *   indicates one or more arguments are invalid.
     */
    STDMETHOD(WintmToPNTM) ( PNTM&,
                                  const SYSTEMTIME& ) PURE;
};

typedef IPosNav *pIPosNav;

#endif
