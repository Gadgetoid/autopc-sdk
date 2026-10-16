/*
    PNGEN.H

    General Position and Navigation system structure / type
    definition file.

    Copyright (c) 1996, 1997 Microsoft Corporation, All rights reserved.
*/

#ifndef _INC_PNGEN
#define _INC_PNGEN

#ifndef UNDER_CE
    #define PN_DT_START_c           10000   //Start of area for user defined data types.
    #define PN_DT_END_c             20000   //End of area for user defined data types.
#else
    #ifndef _TEXT
        #define _TEXT(x) TEXT(x)
    #endif //_TEXT
//    #define PN_NUM_RTCM1_PARITY_c   20      //Max number of parity data in RTCM type 1 or 2 messages.
//    #define PN_GPS1_I2P_c           100     //Comm port # signifying the 1st GPS I²P interface for AutoPC.
//    #define PN_GPS2_I2P_c           101     //Comm port # signifying the 2nd GPS I²P interface for AutoPC.
#endif //UNDER_CE

#define PN_MNFCT_SIZE_c         32      //Max. length of manufacturer string.
#define PN_MODEL_SIZE_c         100     //Max. length of model number string.
#define PN_COM_PORT_LEN_c       20      //Max. length of com port string (i.e. "COM1").
#define PN_NUM_SATS_c           32      //Number of GPS satellites currently.
#define PN_NUM_STATIONS_c       12      //Number of stations (satellites) used in PNSTATION structure.
const DWORD PN_REG_PATH_LEN_c = 512;    //Max length a registry path can be under PNAPI

#define PN_NUM_RTCM1_SATS_c     12      //Max number of satellites in RTCM type 1 or 2 messages.
#define PN_RTCM1_MAX_BYTE_LEN_c 83      //Max number of bytes needed to store a RTCM Type 1 or 2 messages.

//ADF was picked arbitarily so it will not conflict with any
//other HRESULTs.
#define PNAPI_E_MOREBUFFERSPACE         0x8ADF0000L
#define PNAPI_E_NOCALLSTARTED           0x8ADF0001L
#define PNAPI_E_STRUCTLOCKED            0x8ADF0002L
#define PNAPI_E_NOSUCHCALL              0x8ADF0003L
#define PNAPI_E_DATAUNAVAILABLE         0x8ADF0004L
#define PNAPI_E_MEMFREE                 0x8ADF0005L
#define PNAPI_E_DEVICEUNAVAILABLE       0x8ADF0006L
#define PNAPI_E_BADOS                   0x8ADF0007L
#define PNAPI_E_CREATETHREAD            0x8ADF0008L
#define PNAPI_E_ZERODIVIDE              0x8ADF0009L
#define PNAPI_E_REGDBCLOSEKEY           0x8ADF000AL
#define PNAPI_E_LOADDLL                 0x8ADF000BL
#define PNAPI_E_INVALIDREGDBVALUE       0x8ADF000CL
#define PNAPI_E_NOACCESS                0x8ADF000DL
#define PNAPI_E_NODATAYET               0x8ADF000EL
#define PNAPI_E_LOCATOROPEN             0x8ADF000FL
#define PNAPI_E_NOITEMSELECTED          0x8ADF0010L
#define PNAPI_E_LOCATORDEAD             0x8ADF0011L

#define PNAPI_S_CALLALREADYSTARTED      0x0ADF0000L
#define PNAPI_S_PERIODTOOSMALL          0x0ADF0001L
#define PNAPI_S_VERSIONEXPIRED          0x0ADF0002L
#define PNAPI_S_EOF                     0x0ADF0003L

typedef double          PNDouble;
typedef PNDouble*       pPNDouble;
typedef DWORD           PNBool;
typedef PNBool*         pPNBool;
typedef unsigned char   PNByte;
typedef PNByte*         pPNByte;
typedef DWORD*          pDWORD;

#ifndef _INC_PNAPI
    typedef LPVOID hPNDevice;
    typedef hPNDevice* phPNDevice;
#endif //INC_PNAPI

//nb.   These values MUST remain fixed for all versions of PNAPI
//      (as the registry uses these values in 'P&N Type').
#define MIN_PNRECEIVER_T 0
#define MAX_PNRECEIVER_T 6
typedef enum ePNReceiver_t
{   PN_RT_UNKNOWN   = MIN_PNRECEIVER_T,    //Unknown device connected
    PN_RT_GPS       = 1,    //GPS receiver connected
#ifndef UNDER_CE
    PN_RT_NAVSAT    = 2,    //NAVSAT receiver connected
    PN_RT_GLONASS   = 3,    //GLONASS receiver connected
    PN_RT_LORANC    = 4,    //Loran C receiver connected
    PN_RT_DECCA     = 5,    //DECCA receiver connected
#endif //UNDER_CE
    PN_RT_MISC      = MAX_PNRECEIVER_T //Miscellaneous receiver connected.
}PNReceiver_t;

#define MIN_DEVICESTATE_T  0
#define MAX_DEVICESTATE_T 13
typedef enum ePNDeviceState_t
{   PN_DS_INVALIDDS = -1000, //Device State is in invalid state.
    PN_DS_NOTPRESENT= MIN_DEVICESTATE_T,    //Device not present (i.e. been unplugged).
    PN_DS_ERROR     = 1,    //Error in device making it not operate at all.
    PN_DS_WARNING   = 2,    //Error with device, but can still operate.
    PN_DS_OK        = 3,    //Device 100% OK (but not yet searching).
    PN_DS_SEARCHING = 4,    //Searching for fix
    PN_DS_LEVEL1    = 5,    //Found level 1 accuracy data
    PN_DS_LEVEL2    = 6,    //Found level 2 accuracy data
    PN_DS_LEVEL3    = 7,    //Found level 3 accuracy data
    PN_DS_LEVEL4    = 8,    //Found level 4 accuracy data
    PN_DS_LEVEL5    = 9,    //Found level 5 accuracy data
    PN_DS_LEVEL6    = 10,   //Found level 6 accuracy data
    PN_DS_FOUND1SAT = 11,   //Found 1 satellite (GPS specific)
    PN_DS_FOUND2SATS= 12,   //Found 2 satellites (GPS specific)
    PN_DS_NOTIME    = MAX_DEVICESTATE_T    //No GPS time found (GPS specific)
}PNDeviceState_t;

//Predefined areas:
//101-200        :    RTCM internal message calls.
//10000-20000    :    OEM defined calls. 
#define MIN_PNDATA_T  0
#define MAX_PNDATA_T 16
typedef enum ePNData_t
{   PN_DT_ALL           = MIN_PNDATA_T,    //All PNData_ts
    PN_DT_POSITION      = 1,    //Long,lat,alt position data    PNPOSITION
    PN_DT_VELOCITY      = 2,    //Velocity data                 PNVELOCITY
    PN_DT_DEVICESTATE   = 3,    //Device state data             PNDEVSTATE
    PN_DT_TIME          = 4,    //Time data                     PNTIME
    PN_DT_TM            = 5,    //Time data                     PNTM
    PN_DT_ACCURACY      = 6,    //Accuracy data                 PNACCURACY
    PN_DT_STATION       = 7,    //Station data                  PNSTATION
    PN_DT_DEVICE        = 8,    //Device profile data           PNDEVICE
    PN_DT_CONFIG        = 9,    //Configuration data            PNCONFIG
    PN_DT_SETTINGS      = 10,   //Settings data                 PNSETTINGS
#ifndef UNDER_CE
    PN_DT_STATICREFPOS  = 11,   //Static ref position           PNPOSITION
#endif //UNDER_CE
    PN_DT_DGPSSTATUS    = 12,   //Diff GPS status data          PNDGPSSTATUS
//    PN_DT_RTCM          = 13,   //Unused
    PN_DT_ALMANAC       = 14,   //Almanac data                  PNALMANAC
#ifndef UNDER_CE
    PN_DT_STATUS        = 15,   //See PNSTATUS struct           PNSTATUS
#endif //UNDER_CE
    PN_DT_RESET         = MAX_PNDATA_T,
}PNData_t;

#define MIN_PNSTATIONSTATE_T 0
#define MAX_PNSTATIONSTATE_T 3
typedef enum ePNStationState_t
{   PN_CS_UNAVAILABLE   = MIN_PNSTATIONSTATE_T,    //Station unavailable
    PN_CS_IDLE          = 1,    //Station idle
    PN_CS_SEARCHING     = 2,    //Station searching for data
    PN_CS_TRACKING      = MAX_PNSTATIONSTATE_T     //Station finding good data
}PNStationState_t;

#define MIN_PNDATUM_T         0
#define MAX_PNDATUM_T       175
typedef enum ePNDatum_t
{   PN_DA_WGS84         = MIN_PNDATUM_T,    //World Geodetic System 1984
    PN_DA_ADINDAN       = 1,    //Adindan-Mean
    PN_DA_ADINDAN1      = 2,    //Adindan-Ethiopia
    PN_DA_ADINDAN2      = 3,    //Adindan-Mali
    PN_DA_ADINDAN3      = 4,    //Adindan-Senegal
    PN_DA_ADINDAN4      = 5,    //Adindan-Sudan
    PN_DA_AFGOOYE       = 6,    //Afgooye-Somalia
    PN_DA_AINELABD70    = 7,    //Ain El Abd Bahrain 1970
    PN_DA_ANNA1ASTRO65  = 8,    //Anna 1 Astro 1965
    PN_DA_ARC50         = 9,    //Arc 1950-Mean
    PN_DA_ARC50A        = 10,   //Arc 1950 Botswana
    PN_DA_ARC50B        = 11,   //Arc 1950 Lesotho
    PN_DA_ARC50C        = 12,   //Arc 1950 Malawi
    PN_DA_ARC50D        = 13,   //Arc 1950 Swaziland
    PN_DA_ARC50E        = 14,   //Arc 1950 Zaire
    PN_DA_ARC50F        = 15,   //Arc 1950 Zambia
    PN_DA_ARC50G        = 16,   //Arc 1950 Zimbabwe
    PN_DA_ARC60         = 17,   //Arc 1960-Mean
    PN_DA_ASCENSION58   = 18,   //Ascension Island 1958
    PN_DA_ASTROB4       = 19,   //Astro B4 Sorol Atoll
    PN_DA_ASTROBEACONE  = 20,   //Astro Beacon "E" 1945
    PN_DA_ASTRODOS714   = 21,   //Astro DOS 71/4
    PN_DA_ASTRONOMIC52  = 22,   //Astronomic Station 1952
    PN_DA_AUSTRALIAN66  = 23,   //Australian Geodetic 1966
    PN_DA_AUSTRALIAN84  = 24,   //Australian Geodetic 1984
    PN_DA_AUSTRIANS     = 25,   //Austria NS
    PN_DA_BELGIUM50     = 26,   //Belgium 1950
    PN_DA_BELLEVUE      = 27,   //Bellevue (IGN)
    PN_DA_BERMUDA57     = 28,   //Bermuda 1957
    PN_DA_BOGOTA        = 29,   //Bogota Observatory
    PN_DA_BUKITRIMPAH   = 30,   //Bukit Rimpah
    PN_DA_CAMPAREA      = 31,   //Camp Area Astro
    PN_DA_CAMPOINCH     = 32,   //Campo Inchauspe
    PN_DA_CANTON66      = 33,   //Canton Island 1966
    PN_DA_CAPE          = 34,   //Cape
    PN_DA_CAPECANAV     = 35,   //Cape Canveral Mean
    PN_DA_CARTHAGE      = 36,   //Carthage
    PN_DA_CHATHAM71     = 37,   //Chatham 1971
    PN_DA_CHUAASTRO     = 38,   //Chua Astro
    PN_DA_CORREGOALEGRE = 39,   //Corrego Alegre
    PN_DA_DANISH34      = 40,   //Danish Gi 1934
    PN_DA_DJAKARTA      = 41,   //Djakarta (Batavia)
    PN_DA_DOS68         = 42,   //DOS 1968
    PN_DA_EASTER67      = 43,   //Easter Island 1967
    PN_DA_EUROPEAN50    = 44,   //European 1950 Mean
    PN_DA_EUROPEAN50A   = 45,   //European 1950 Cyprus
    PN_DA_EUROPEAN50B   = 46,   //European 1950 Egypt
    PN_DA_EUROPEAN50C   = 47,   //European 1950 England / Scotland
    PN_DA_EUROPEAN50D   = 48,   //European 1950 England / Ireland
    PN_DA_EUROPEAN50E   = 49,   //European 1950 Greece
    PN_DA_EUROPEAN50F   = 50,   //European 1950 Iran
    PN_DA_EUROPEAN50G   = 51,   //European 1950 Sardinia
    PN_DA_EUROPEAN50H   = 52,   //European 1950 Sicily
    PN_DA_EUROPEAN50I   = 53,   //European 1950 Norway
    PN_DA_EUROPEAN50J   = 54,   //European 1950 Portugal / Spain
    PN_DA_EUROPEAN79    = 55,   //European 1979
    PN_DA_GANDAJIKA     = 56,   //Gandajika Base
    PN_DA_GEODETIC49    = 57,   //Geodetic Datum 1949
    PN_DA_GGRS87        = 58,   //GGRS 87
    PN_DA_GUAM63        = 59,   //Guam 1963
    PN_DA_GUNUNGSEGARA  = 60,   //Gunung Segara
    PN_DA_GUX1ASTRO     = 61,   //Gux 1 Astro
    PN_DA_HERATNORTH    = 62,   //Herat North
    PN_DA_HJORSEY55     = 63,   //Hjorsey 1955
    PN_DA_HONGKONG63    = 64,   //Hong Kong 1963
    PN_DA_HUTZUSHAN     = 65,   //Hu-Tzu-Shan
    PN_DA_INDIAN        = 66,   //Indian mean value
    PN_DA_INDIAN1       = 67,   //Indian - India / Nepal / Bangladesh
    PN_DA_INDIAN2       = 68,   //Indian - Thialand / Vietnam
    PN_DA_IRELAND65     = 69,   //Ireland 1965
    PN_DA_ISTSASTRO69   = 70,   //ISTS 073 Astro 1969
    PN_DA_JOHNSTON61    = 71,   //Johnston Island 1961
    PN_DA_KANDAWALA     = 72,   //Kandawala
    PN_DA_KERGUELAN     = 73,   //Kerguelan Island
    PN_DA_KERTAU48      = 74,   //Kertau 1948
    PN_DA_LAREUNION     = 75,   //La Reunion (Reunion)
    PN_DA_LC5ASTRO      = 76,   //L.C. 5 Astro
    PN_DA_LIBERIA64     = 77,   //Liberia 1964
    PN_DA_LUZON         = 78,   //Luzon mean value
    PN_DA_LUZON1        = 79,   //Luzon - Phillippines
    PN_DA_LUZON2        = 80,   //Luzon - Mindanao
    PN_DA_MAHE71        = 81,   //Mahe 1971
    PN_DA_MARCOASTRO    = 82,   //Marco Astro
    PN_DA_MASSAWA       = 83,   //Massawa
    PN_DA_MERCHICH      = 84,   //Merchich
    PN_DA_MIDWAY61      = 85,   //Midway Astro 1961
    PN_DA_MINNA         = 86,   //Minna
    PN_DA_NAD02         = 87,   //North American 1902
    PN_DA_NAD27         = 88,   //North American 1927 - Mean Value (CONUS)
    PN_DA_NAD27A        = 89,   //North American 1927 - Western US
    PN_DA_NAD27B        = 90,   //North American 1927 - Eastern US
    PN_DA_NAD27C        = 91,   //North American 1927 - Alaska
    PN_DA_NAD27D        = 92,   //North American 1927 - Canada
    PN_DA_NAD27E        = 93,   //North American 1927 - Alberta / BC
    PN_DA_NAD27F        = 94,   //North American 1927 - East Canada
    PN_DA_NAD27G        = 95,   //North American 1927 - Manitoba/Ontario
    PN_DA_NAD27H        = 96,   //North American 1927 - NW Ter/ Sask
    PN_DA_NAD27I        = 97,   //North American 1927 - Yukon
    PN_DA_NAD27J        = 98,   //North American 1927 - Greenland
    PN_DA_NAD27K        = 99,   //North American 1927 - Central America
    PN_DA_NAD27L        = 100,  //North American 1927 - Bahamas
    PN_DA_NAD27M        = 101,  //North American 1927 - Canal Zone
    PN_DA_NAD27N        = 102,  //North American 1927 - Caribbean
    PN_DA_NAD27O        = 103,  //North American 1927 - Cuba
    PN_DA_NAD27P        = 104,  //North American 1927 - Mexico
    PN_DA_NAD27Q        = 105,  //North American 1927 - San Salvador Isle
    PN_DA_NAD27R        = 106,  //North American 1927 - Alaska / Canada
    PN_DA_NAD83         = 107,  //North American 1983 - Mean
    PN_DA_NAHRWAN1      = 108,  //Nahrwan (Masirah Island)
    PN_DA_NAHRWAN2      = 109,  //Nahrwan (Saudi Arabia)
    PN_DA_NAHRWAN3      = 110,  //Nahrwan (United Arab Emirates)
    PN_DA_NAMIBIA       = 111,  //Namibia
    PN_DA_NAPARIMA      = 112,  //Naparima, BWI
    PN_DA_NETHTRI21     = 113,  //Netherland Tri 21
    PN_DA_NOUTRIAG1     = 114,  //Nou Triag France
    PN_DA_NOUTRIAG2     = 115,  //Nou Triag Luxembourg
    PN_DA_OBSERVATORIO66= 116,  //Observastorio 1966
    PN_DA_OLDEGYPT      = 117,  //Old Egyptian 1907
    PN_DA_OLDHAWAII     = 118,  //Old Hawaiian - Mean
    PN_DA_OLDHAWAII1    = 119,  //Old Hawaiian - Hawaii
    PN_DA_OLDHAWAII2    = 120,  //Old Hawaiian - Kauai
    PN_DA_OLDHAWAII3    = 121,  //Old Hawaiian - Maui
    PN_DA_OLDHAWAII4    = 122,  //Old Hawaiian - Oahu
    PN_DA_OMAN          = 123,  //Oman
    PN_DA_ORDNANCEGB36  = 124,  //Ordnance Survey of GB 1936 - Mean
    PN_DA_PICODELASNIEVES=125,  //Pico De Las Neives
    PN_DA_PITCAIRN67    = 126,  //Pitcairn Astro 1967
    PN_DA_PORTUGUESE73  = 127,  //Portuguese 1973
    PN_DA_POTSDAM       = 128,  //Potsdam
    PN_DA_PUERTORICO    = 129,  //Puerto Rico
    PN_DA_QATARNATIONAL = 130,  //Qatar National
    PN_DA_QORNOQ        = 131,  //Qornoq
    PN_DA_ROME40        = 132,  //Rome 1940
    PN_DA_SANTABRAZ     = 133,  //Sao Braz
    PN_DA_SANTODOS      = 134,  //Santo (DOS)
    PN_DA_SAPPERHILL43  = 135,  //Sapper Hill 1943
    PN_DA_SCHWARZECK    = 136,  //Schwarzeck (Namibia)
    PN_DA_PROVSAMERICA56= 137,  //Prov South American 1956 - Mean
    PN_DA_PROVSAMERICA56A=138,  //Prov South American 1956 - Bolivia
    PN_DA_PROVSAMERICA56B=139,  //Prov South American 1956 - N Chile
    PN_DA_PROVSAMERICA56C=140,  //Prov South American 1956 - S Chile
    PN_DA_PROVSAMERICA56D=141,  //Prov South American 1956 - Columbia
    PN_DA_PROVSAMERICA56E=142,  //Prov South American 1956 - Ecuador
    PN_DA_PROVSAMERICA56F=143,  //Prov South American 1956 - Guyana
    PN_DA_PROVSAMERICA56G=144,  //Prov South American 1956 - Peru
    PN_DA_PROVSAMERICA56H=145,  //Prov South American 1956 - Venezuela
    PN_DA_SAMERICA69    = 146,  //South American 1969 - Mean
    PN_DA_SAMERICA69A   = 147,  //South American 1969 - Argentina
    PN_DA_SAMERICA69B   = 148,  //South American 1969 - Bolivia
    PN_DA_SAMERICA69C   = 149,  //South American 1969 - Brazil
    PN_DA_SAMERICA69D   = 150,  //South American 1969 - Chile
    PN_DA_SAMERICA69E   = 151,  //South American 1969 - Colombia
    PN_DA_SAMERICA69F   = 152,  //South American 1969 - Ecuador
    PN_DA_SAMERICA69G   = 153,  //South American 1969 - Guyana
    PN_DA_SAMERICA69H   = 154,  //South American 1969 - Paraguay
    PN_DA_SAMERICA69I   = 155,  //South American 1969 - Peru
    PN_DA_SAMERICA69J   = 156,  //South American 1969 - Trinidad/Tobago
    PN_DA_SAMERICA69K   = 157,  //South American 1969 - Venezuela
    PN_DA_SOUTHASIA     = 158,  //South Asia
    PN_DA_PROVSCHILEAN63= 159,  //Prov So Chilean 1963
    PN_DA_SEBASE        = 160,  //Southeast Base
    PN_DA_SWBASE        = 161,  //Southwest Base
    PN_DA_TANANARIVE25  = 162,  //Tananarive Observatory 1925
    PN_DA_TIMBALAI48    = 163,  //Timbalai 1948
    PN_DA_TOKYO         = 164,  //Tokyo
    PN_DA_TOKYONEW      = 165,  //Tokyo - mean
    PN_DA_TOKYONEW1     = 166,  //Tokyo - Korea
    PN_DA_TOKYONEW2     = 167,  //Tokyo - Okinawa
    PN_DA_TOKYOGSI      = 168,  //Tokyo GSI coords
    PN_DA_TRISTAN68     = 169,  //Tristan Astro 1968
    PN_DA_VITILEVU16    = 170,  //Viti Levu 1916
    PN_DA_WAKEENIWETOK60= 171,  //Wake-Eniwetok 1960
    PN_DA_WGS72         = 172,  //World Geodetic System 1972
    PN_DA_YACARE        = 173,  //Yacare
    PN_DA_ZANDERIJ      = 174,  //Zanderij
    PN_DA_UNKNOWN       = MAX_PNDATUM_T
}PNDatum_t;
#define PN_NUM_AV_DATUMS_c  6   //PN_NUM_DATUMS_c / 32 and rounded up.

#define MIN_PN2DMODE_T 0
#define MAX_PN2DMODE_T 2
typedef enum ePN2DMode_t
{
    PN_MO_NOTAVAILABLE  = MIN_PN2DMODE_T,    //Do not give a 2D position for 3 satellites
    PN_MO_2DMANUAL      = 1,                 //Give a 2D position using supplied altitude
    PN_MO_2DAUTO        = MAX_PN2DMODE_T     //Use previous altitude (where available) to
}PN2DMode_t;

#define MIN_PNALTHOLD_T 0
#define MAX_PNALTHOLD_T 2
typedef enum ePNAltHold_t
{
    PN_AH_OFF       = MIN_PNALTHOLD_T,    //Alt hold off
    PN_AH_MANUAL    = 1,                  //Manual alt hold
    PN_AH_AUTO      = MAX_PNALTHOLD_T     //Automatic alt hold
}PNAltHold_t;

typedef enum ePNInit_t
{
    PN_IT_AVAILABLE = 1,    //Element is used by UniLocator.
    PN_IT_INITIALIZE= 2     //Element used in initialization of device.
}PNInit_t;

#define MIN_PNACCESS_T  0
#define MAX_PNACCESS_T  1
typedef enum ePNAccess_t
{
    PN_AS_READWRITE = MIN_PNACCESS_T,    //Device has full access rights.
    PN_AS_READ      = MAX_PNACCESS_T     //Device has partial access rights (cannot affect device)
}PNAccess_t;

#define MIN_PNRESET_T 0
#define MAX_PNRESET_T 1
typedef enum ePNReset_t
{
    PN_RS_HARD  = MIN_PNRESET_T,    //Hard reset.
    PN_RS_SOFT  = MAX_PNRESET_T     //Soft reset.
}PNReset_t;

#define MIN_PNPOWERSTATE_T 0
#define MAX_PNPOWERSTATE_T 5
typedef enum ePNPowerState_t
{
    PN_PW_OFF       = MIN_PNPOWERSTATE_T,
    PN_PW_SUSPENDED = 1,
    PN_PW_STANDBY   = 2,
    PN_PW_LOWPOWER  = 3,
    PN_PW_MIDPOWER  = 4,
    PN_PW_FULLPOWER = MAX_PNPOWERSTATE_T
}PNPowerState_t;

//Enumerated types
#define MIN_PNENV_T 0
#define MAX_PNENV_T 7
typedef enum ePNEnv_t
{
    PN_ET_STATIONARY    = MIN_PNENV_T,
    PN_ET_OPENROAD      = 1,
    PN_ET_URBANCANYON   = 2,
    PN_ET_FOREST        = 3,
    PN_ET_OPENOCEAN     = 4,
    PN_ET_AIRCRAFT      = 5,
    PN_ET_NONE          = 6,
    PN_ET_USER          = MAX_PNENV_T
}PNEnv_t;

#define MIN_PN3STATE_T 0
#define MAX_PN3STATE_T 2
typedef enum ePN3State_t
{
    PN_3S_FALSE = MIN_PNALTHOLD_T, //Off, or False position.
    PN_3S_TRUE  = 1,               //On, or True position.
    PN_3S_OTHER = MAX_PNALTHOLD_T  //Other, or Indeterminate position.
}PN3State_t;

typedef struct tagPNDEVICE
{
    DWORD           dwStructureSize;
    WCHAR           szManufacturer[PN_MNFCT_SIZE_c]; //Not used by WINCE
    WCHAR           szModel[PN_MODEL_SIZE_c];
    PNReceiver_t    rtReceiverType;     //Not used by WINCE
    DWORD           dwUseCount;         //# of applications that are using this device currently.
    DWORD           dwQuality;          //Quality of data this device can deliver (the lower the number the better it is).
    WCHAR           szComPort[PN_COM_PORT_LEN_c]; //Com port this device is currently on (in the format "COM?" where ? is a the port number). Not used by WINCE.
    WCHAR           szRegRoot[PN_REG_PATH_LEN_c]; //For PNAPI internal use.
    DWORD           dwComPort;          //Comm port in numerical format (see PN_I2P_GPS1_c and PN_I2P_GPS2Pc).
    DWORD           dwPNReserved;       //Reserved for future use by PNAPI
    struct tagPNDEVICE* pNext;
} PNDEVICE;
typedef PNDEVICE*   pPNDEVICE;
typedef PNDEVICE**  ppPNDEVICE;

typedef struct tagPNTM
{
    DWORD   dwMillisec;
    DWORD   dwDay;
} PNTM;
typedef PNTM* pPNTM;

#define PN_ATM_MILLISEC 0x00000001L
#define PN_ATM_DAY      0x00000002L

typedef struct tagPNAVTM
{
    DWORD   dwStructureSize;
    DWORD   dwAv1;
    DWORD   dwPNReserved;
} PNAVTM;
typedef PNAVTM* pPNAVTM;

typedef struct tagPNTIME
{
    PNTM    tmDevice;
    PNAVTM  tmAvDevice;
    PNTM    tmLeapDiffTime;     //Not used by WINCE.
    PNAVTM  tmAvLeapDiffTime;   //Not used by WINCE.
    PNTM    tmComputer;
    PNAVTM  tmAvComputer;
} PNTIME;
typedef PNTIME* pPNTIME;

typedef struct tagPNPOSLLA
{
    PNDouble    dLong;
    PNDouble    dLat;
    PNDouble    dAlt;
    PNBool      fRadians;
} PNPOSLLA;
typedef PNPOSLLA* pPNPOSLLA;

typedef struct tagPNPOSXYZ
{
    PNDouble    dX;
    PNDouble    dY;
    PNDouble    dZ;
} PNPOSXYZ;
typedef PNPOSXYZ* pPNPOSXYZ;

#define PN_APL_LONG     0x00000001L
#define PN_APL_LAT      0x00000002L
#define PN_APL_ALT      0x00000004L
#define PN_APL_RADIANS  0x00000008L

typedef struct tagPNAVPOSLLA
{
    DWORD   dwStructureSize;
    DWORD   dwAv1;
    DWORD   dwPNReserved;
} PNAVPOSLLA;
typedef PNAVPOSLLA* pPNAVPOSLLA;

typedef struct tagPNPOSITION
{
    DWORD       dwStructureSize;
    PNTIME      tiTime;
    PNPOSLLA    psPosition;
    PNAVPOSLLA  psAvPosition;
    DWORD       dwPNReserved;
} PNPOSITION;
typedef PNPOSITION* pPNPOSITION;

typedef struct tagPNVELENU
{
    PNDouble    dEast;  //meters/sec
    PNDouble    dNorth; //meters/sec
    PNDouble    dUp;    //meters/sec
} PNVELENU;
typedef PNVELENU* pPNVELENU;

typedef struct tagPNVELBEAR
{
    PNDouble    dBearing;
    PNDouble    dHorizSpeed;
    PNDouble    dVertSpeed;
} PNVELBEAR;
typedef PNVELBEAR* pPNVELBEAR;

#define PN_AVN_EAST     0x00000001L
#define PN_AVN_NORTH    0x00000002L
#define PN_AVN_UP       0x00000004L

typedef struct tagPNAVVELENU
{
    DWORD   dwStructureSize;
    DWORD   dwAv1;
    DWORD   dwPNReserved;
} PNAVVELENU;
typedef PNAVVELENU* pPNAVVELENU;

typedef struct tagPNVELOCITY
{
    DWORD       dwStructureSize;//For future use
    PNTIME      tiTime;
    PNVELENU    vlVelocity;
    PNAVVELENU  vlAvVelocity;
    DWORD       dwPNReserved;   //Reserved for future use by PNAPI
} PNVELOCITY;
typedef PNVELOCITY* pPNVELOCITY;

#define PN_ASI_STATE            0x00000001L
#define PN_ASI_STATIONIDNUM     0x00000002L
#define PN_ASI_USED             0x00000004L
#define PN_ASI_ELEVATION        0x00000008L
#define PN_ASI_SATAZIMUTH       0x00000010L
#define PN_ASI_SIGNALSTRENGTH   0x00000020L
#ifndef UNDER_CE
#define PN_ASI_COVERAGE         0x00000040L
#endif //UNDER_CE

typedef struct tagPNAVINDSTATION
{
    DWORD   dwStructureSize;
    DWORD   dwAv1;
    DWORD   dwPNReserved;
} PNAVINDSTATION;
typedef PNAVINDSTATION* pPNAVINDSTATION;

typedef struct tagPNINDSTATION
{
    DWORD           dwStructureSize;//For future use
    PNTIME          tiTime;         //Not used by WINCE.
    PNStationState_t ssState;       //State of this station
    DWORD           dwStationIDNum; //PRN#/SVID or unique station#
    PNBool          fUsed;          //Whether station is being used for calcns
    PNDouble        dSatElevation;  //Measured in radians (0-PI/2) GPS specific.
    PNDouble        dSatAzimuth;    //Measured in radians (0-2*PI) GPS specific.
    PNDouble        dSignalStrength;//Measured in dB.
    DWORD           dwCoverage;     //How often the station is serviced (in milliseconds). Not used by WINCE.
    PNAVINDSTATION  siAvIndStation;
    DWORD           dwPNReserved;   //Reserved for future use by PNAPI
} PNINDSTATION;
typedef PNINDSTATION* pPNINDSTATION;

#ifndef UNDER_CE
#define PN_ASN_NUMAVAILABLE 0x00000001L
#endif //UNDER_CE
#define PN_ASN_NUMUSED      0x00000002L

typedef struct tagPNAVSTATION
{
    DWORD   dwStructureSize;
    DWORD   dwAv1;
    DWORD   dwPNReserved;
} PNAVSTATION;
typedef PNAVSTATION* pPNAVSTATION;

typedef struct tagPNSTATION
{
    DWORD           dwStructureSize;//For future use
    PNTIME          tiTime;
    DWORD           dwNumAvailable; //Num stations that can be seen. Not used by WINCE.
    DWORD           dwNumUsed;      //Num stations being tracked by the device
    PNAVSTATION     snAvStation;    //Which PNSTATION elements are valid
    PNINDSTATION    siStations[PN_NUM_STATIONS_c]; //Individual station data
    DWORD           dwPNReserved;   //Reserved for future use by PNAPI
} PNSTATION;
typedef PNSTATION* pPNSTATION;
   
#ifndef UNDER_CE
#define PN_ASA_SETDATA                  0x00000001L
#endif //UNDER_CE
#define PN_ASA_PRN                      0x00000002L
#define PN_ASA_SATHEALTH                0x00000004L
#define PN_ASA_REFWEEKNUMBER            0x00000008L
#define PN_ASA_REFTIMEOFWEEK            0x00000010L
#define PN_ASA_ECCENTRICITY             0x00000020L
#define PN_ASA_ROOTSEMIMAJORAXIS        0x00000040L
#define PN_ASA_ARGUMENTOFPERIGEE        0x00000080L
#define PN_ASA_MEANANOMALYATREFTIME     0x00000100L
#define PN_ASA_RIGHTASCENSIONATREFTIME  0x00000200L
#define PN_ASA_RATERIGHTASCENSION       0x00000400L
#define PN_ASA_CORRECTTOINCLINATION     0x00000800L
#define PN_ASA_AF0CLOCKCORRECT          0x00001000L
#define PN_ASA_AF1CLOCKCORRECT          0x00002000L

typedef struct tagPNAVSATELLITE
{
    DWORD   dwStructureSize;
    DWORD   dwAv1;
    DWORD   dwPNReserved;
} PNAVSATELLITE;
typedef PNAVSATELLITE* pPNAVSATELLITE;

typedef struct tagPNSATELLITE
{
    DWORD       dwStructureSize;        //For future use
    PNTIME      tiTime;                 //Time data was collected. Not used by WINCE.
    PNBool      fSetData;               //Set data or not.         Not used by WINCE.
    DWORD       dwPRN;                  //Satellite PRN Number
    PNByte      bSatHealth;             //Health summary (binary)
    DWORD       dwRefWeekNumber;
    DWORD       dwRefTimeOfWeek;        //seconds
    PNDouble    dEccentricity;
    PNDouble    dRootSemiMajorAxis;     //Measures in meters^0.5
    PNDouble    dArgumentOfPerigee;     //Measured in radians
    PNDouble    dMeanAnomalyAtRefTime;  //Measured in radians
    PNDouble    dRightAscensionAtRefTime;//Measured in radians
    PNDouble    dRateRightAscension;    //Measured in radians/sec
    PNDouble    dCorrectToInclination;  //Measured in PI radians
    PNDouble    dAF0ClockCorrect;       //Measured in seconds
    PNDouble    dAF1ClockCorrect;       //Measured in sec/sec.
    PNAVSATELLITE saAvSatellite;        //Which elements are valid
    DWORD       dwPNReserved;           //Reserved for future use by PNAPI
} PNSATELLITE;
typedef PNSATELLITE* pPNSATELLITE;

typedef struct tagPNALMANAC
{
    DWORD       dwStructureSize;    //For future use
    PNTIME      tiTime;             //Time data was collected
    PNSATELLITE saSatellite[PN_NUM_SATS_c];//Satellite information 
    DWORD       dwPNReserved;       //Reserved for future use by PNAPI
} PNALMANAC;
typedef PNALMANAC* pPNALMANAC;

#ifndef UNDER_CE
#define PN_ASM_STATIONID    0x00000001L
#define PN_ASM_STATIONUSED  0x00000002L
#endif //UNDER_CE

//Structure not used by WINCE.
typedef struct tagPNAVSTATIONMODE
{
    DWORD   dwStructureSize;
    DWORD   dwAv1;
    DWORD   dwPNReserved;
} PNAVSTATIONMODE;

//Structure not used by WINCE.
typedef struct tagPNSTATIONMODE
{
    DWORD           dwStructureSize;//For future use
    DWORD           dwStationID;    //PRN#/SVID or unique station#
    PNBool          fStationUsed;   //TRUE if station used to calc a position
    PNAVSTATIONMODE smMode;         //Which elements are valid
    DWORD           dwPNReserved;   //Reserved for future use by PNAPI
} PNSTATIONMODE;
typedef PNSTATIONMODE* pPNSTATIONMODE;

#ifndef UNDER_CE
#define PN_ASE_MODE             0x00000001L
#endif //UNDER_CE
#define PN_ASE_DGPSENABLE       0x00000002L //Not implemented for V1.0 PNAPI.
#define PN_ASE_DRENABLE         0x00000004L
#define PN_ASE_DGPSTIMEOUT      0x00000008L //Not implemented for V1.0 PNAPI.
#ifndef UNDER_CE
#define PN_ASE_DGPS2DENABLE     0x00000010L //Not implemented for V1.0 PNAPI.
#define PN_ASE_DGPS2DTIMEOUT    0x00000020L //Not implemented for V1.0 PNAPI.
#endif //UNDER_CE
#define PN_ASE_DATUM            0x00000040L
#define PN_ASE_POWERSTATE       0x00000080L
#ifndef UNDER_CE
#define PN_ASE_ALTITUDEHOLD     0x00000100L
#define PN_ASE_AHALTITUDE       0x00000200L
#define PN_ASE_2DPOSMODE        0x00000400L
#define PN_ASE_2DALTITUDE       0x00000800L
#endif //UNDER_CE
#define PN_ASE_ENVIRONMENT      0x00001000L
#define PN_ASE_ACCESS           0x00002000L

typedef struct tagPNAVSETTINGS
{
    DWORD   dwStructureSize;
    DWORD   dwAv1;
    DWORD   dwPNReserved;
} PNAVSETTINGS;
typedef PNAVSETTINGS* pPNAVSETTINGS;

typedef struct tagPNSETTINGS
{
    DWORD           dwStructureSize;//For future use
    PNTIME          tiTime;
    PNSTATIONMODE   cmMode[PN_NUM_SATS_c]; //Current station mode. Not used by WINCE.
    PNBool          fDGPSEnable;    //Enables / disables DGPS functionality.
    PNBool          fDREnable;      //Enables / disables dead reckoning functionality (Not used in V1.0 or V1.1).
    DWORD           dwDGPSTimeOut;  //Sets / gets the DGPS time out (in milliseconds).
    PNBool          fDGPS2DEnable;  //Not implemented for V1.0 PNAPI. Not used by WINCE.
    DWORD           dwDGPS2DTimeOut;//Not implemented for V1.0 PNAPI. Not used by WINCE.
    PNDatum_t       daDatum;        //Datum receiver uses
    PNPowerState_t  pwPowerState;   //Power state of device.
    PNAltHold_t     ahAltitudeHold; //Set altitude hold. Not used by WINCE.
    PNDouble        dAHAltitude;    //Altitude value when AltHold is manual. Not used by WINCE.
    PN2DMode_t      mo2DPosMode;    //If TRUE, 2D positioning is available. Not used by WINCE.
    PNDouble        d2DAltitude;    //Altitude for mo2DPosMode. Not used by WINCE.
    PNAccess_t      asAccess;       //Access rights for device.
    PNEnv_t         etEnvironment;  //Environment for this device.
    PNAVSETTINGS    seAvSettings;   //Which elements are valid.
    DWORD           dwPNReserved;   //Reserved for future use by PNAPI
} PNSETTINGS;
typedef PNSETTINGS* pPNSETTINGS;

#ifndef UNDER_CE
#define PN_AAC_AHORIZERROR      0x00000001L
#define PN_AAC_AVERTICALERROR   0x00000002L
#endif //UNDER_CE
#define PN_AAC_EDOP             0x00000004L
#define PN_AAC_NDOP             0x00000008L
#define PN_AAC_VDOP             0x00000010L
#define PN_AAC_PDOP             0x00000020L
#define PN_AAC_TDOP             0x00000040L
#define PN_AAC_GDOP             0x00000080L

typedef struct tagPNAVACCURACY
{
    DWORD   dwStructureSize;
    DWORD   dwAv1;
    DWORD   dwPNReserved;
} PNAVACCURACY;

typedef PNAVACCURACY* pPNAVACCURACY;

typedef struct tagPNACCURACY
{
    DWORD       dwStructureSize;//For future use
    PNTIME      tiTime;
    PNDouble    dHorizError;    //meters. Not used by WINCE.
    PNDouble    dVerticalError; //meters. Not used by WINCE.
    PNDouble    dEDOP;          //GPS specific item
    PNDouble    dNDOP;          //GPS specific item
    PNDouble    dVDOP;          //GPS specific item
    PNDouble    dPDOP;          //GPS specific item
    PNDouble    dTDOP;          //GPS specific item
    PNDouble    dGDOP;          //GPS specific item
    PNAVACCURACY acAvAccuracy;
    DWORD       dwPNReserved;   //Reserved for future use by PNAPI
} PNACCURACY;
typedef PNACCURACY* pPNACCURACY;

typedef struct tagPNCONFIG
{
    DWORD       dwStructureSize;//For future use
    PNPOSITION  poPositionData; //Holds position & time it was found. Only PNPOSLLA portion used by WINCE.
    PNACCURACY  acAccuracy;     //Accuracy of above position. Not used by WINCE.
    PNPOSITION  poStaticRefPos; //Static reference position. Not used by WINCE.
    PNALMANAC   alAlmanac;      //Almanac data.
    PNSETTINGS  seSettings;     //Miscellaneous settings. Not used by WINCE.
    PNBool      fInitAlmanac;   //Whether almanac will be initialized on start up.
    PNBool      fInitPosition;  //Whether position will be initialised on start up.
    PNBool      fInitTime;      //Whether the time will be initialised on start up.
    DWORD       dwPNReserved;   //Reserved for future use by PNAPI
} PNCONFIG;
typedef PNCONFIG* pPNCONFIG;

#define PN_ADS_STATE    0x00000001L  

typedef struct tagPNAVDEVSTATE
{
    DWORD   dwStructureSize;
    DWORD   dwAv1;
    DWORD   dwPNReserved;
} PNAVDEVSTATE;

typedef struct tagPNDEVSTATE
{
    DWORD           dwStructureSize;//For future use
    PNTIME          tiTime;
    PNDeviceState_t dsState;
    PNAVDEVSTATE    dsAvState;
    DWORD           dwPNReserved;   //Reserved for future use by PNAPI
} PNDEVSTATE;
typedef PNDEVSTATE* pPNDEVSTATE;

//Structure not used by WINCE.
typedef struct tagPNSTATUS
{
    DWORD       dwStructureSize;//For future use
    PNTIME      tiFirstTime;    //Time first piece of data collected
    PNTIME      tiLastTime;     //Time last piece of data collected
    PNPOSITION  poPosition;     //Position data
    PNVELOCITY  veVelocity;     //Velocity data
    PNDEVSTATE  deDevState;     //Device state
    PNACCURACY  acAccuracy;     //Accuracy data
    DWORD       dwPNReserved;   //Reserved for future use by PNAPI
} PNSTATUS;
typedef PNSTATUS* pPNSTATUS;

#define PN_DU_MODE          0x00000001L  
#define PN_DU_OPMODE        0x00000002L
#define PN_DU_STATUS        0x00000004L
#define PN_DU_AGELIMIT      0x00000008L

typedef struct tagPNAVDGPSSTATUS
{
    DWORD   dwStructureSize;
    DWORD   dwAv1;
    DWORD   dwPNReserved;
} PNAVDGPSSTATUS;
typedef PNAVDGPSSTATUS* pPNAVDGPSSTATUS;

typedef struct tagPNDGPSSTATUS
{
    DWORD           dwStructureSize;//For future use
    PNTIME          tiTime;
    PN3State_t      DGPSMode;       //PN_3S_FALSE - DPGS Off, PN_3S_TRUE - DGPS On, PN_3S_OTHER - Auto selection.
    PN3State_t      OperatingMode;  //PN_3S_FALSE - 2D only, PN_3S_TRUE - 3D only, PN_3S_OTHER - Auto selection.
    PNBool          fDGPSStatus;    //TRUE - If outputting position, receiver using DGPS corrections, FALSE - Not using DGPS corrections.
    PNAVDGPSSTATUS  dpAvDGPSStatus;
    DWORD           dwPNReserved;   //Reserved for future use by PNAPI
    DWORD           dwDGPSAgeLimit; //Max. # of milliseconds to use DGPS correctional data
} PNDGPSSTATUS;
typedef PNDGPSSTATUS* pPNDGPSSTATUS;

typedef struct tagPNDR
{
    DWORD   dwStructureSize;
    PNBool  fDRActive;  //Whether dead reckoning service is available.
    PNBool  fDREnable;  //TRUE - Enable dead reckoning, FALSE - Disable dead reckoning.
    DWORD   dwPNReserved;
} PNDR;
typedef PNDR* pPNDR;

#endif //INC_PNGEN
