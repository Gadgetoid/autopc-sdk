#ifndef _TAPIDEVICE_H_
#define _TAPIDEVICE_H_



// DeviceType defines -	Compatible w/ Unimodem device definitions but
//						extended to cover voice capable devices	
//
#define TD_NULL_MODEM						0
#define TD_EXTERNAL_MODEM					1
#define TD_INTERNAL_MODEM					2
#define TD_PCMCIA_MODEM						3
#define TD_PARALLEL_PORT					4
#define TD_PARALLEL_MODEM					5
#define TD_IRCOMM_MODEM						6
#define TD_EXTERNAL_VOICE_MODEM				7
#define TD_EXTERNAL_VOICE_AND_DATA_MODEM	8
#define TD_INVALID                      	9

// The following info is returned from the lineGetDevCaps call as the
// device specific data.  The wDeviceType indicates the type of device on
// the port, and the wActive field indicates if the port is currently active.
// This field will normally be 1 for all TAPi device except PCMCIA cards which
// have been removed from the system.

	typedef 
	struct
	{
		WORD        wDeviceType;
		WORD        wActive;

        //  Oem's may extend this structure with their own device specific
        //  data.  The recommended method would be to define a new structure
        //  that contains this structure as it's first element.  It is critical
        //  that the above fields retain their position in the structure in
        //  order for basic functionality to work.

        //  NOTE:   STRUCTURE ALIGNMENT AND PACKING IS VERY IMPORTANT BECAUSE
        //          THE APC BASE CODE RELIES ON THE ALIGNMENT OF THE TWO FIELDS
        //          LISTED ABOVE.  TAKE CARE TO PRESERVE THIS IN YOUR STRUCTURE.

	} TD_INFORMATION, *PTD_INFORMATION;









#endif