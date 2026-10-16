/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.
Copyright (c) 1995, 1996, 1997  Microsoft Corporation

Module Name:  

af_irda.h

Abstract:

Support for the address family AF_IRDA for use with winsock.

Notes: 


--*/

// @CESYSGEN IF CE_MODULES_WINSOCK

#ifndef __AFIRDA__
#define __AFIRDA__

#include <winsock.h>

#define AF_IRDA	22              // see winsock.h
#define PF_IRDA AF_IRDA

#define SOL_IRLMP		        0x00FF

#define IRLMP_ENUMDEVICES       0x00000010
#define IRLMP_IAS_SET           0x00000011
#define IRLMP_IAS_QUERY         0x00000012
#define IRLMP_SEND_PDU_LEN      0x00000013
#define IRLMP_EXCLUSIVE_MODE    0x00000014
#define IRLMP_IRLPT_MODE        0x00000015
#define IRLMP_9WIRE_MODE        0x00000016
// Some Sharp Zaurus's will do a LAP disconnect without doing
// a LMP disconnect. This forces the IrDA stack to treat this
// as a graceful close.
#define IRLMP_SHARP_MODE        0x00000020


#define IAS_ATTRIB_NO_CLASS     0x00000010
#define IAS_ATTRIB_NO_ATTRIB    0x00000000
#define IAS_ATTRIB_INT          0x00000001
#define IAS_ATTRIB_OCTETSEQ     0x00000002
#define IAS_ATTRIB_STR          0x00000003

/**
 * This structure specifies an IrSocket address.
 */
typedef struct _SOCKADDR_IRDA
{
	/**
	 * Value for the address format member is AF_IRDA from the AF_IRDA.H header file.
	 */
	u_short	irdaAddressFamily;
	/**
	 * Device identifier returned by the SO_IRLMP_ENUMDEVICES option used in a getsockopt function call.
	 */
	u_char  irdaDeviceID[4];
	/**
	 * Null-terminated string of 25 characters that contains the service name of the application
	 * associated with this socket address. If the name is 25 characters or the string is not
	 * null-terminated, the connection fails. If the service name is of the form "LSAP-SELXXX" where XXX
	 * is a decimal integer in the range 1-127, the address indicates a specific LSAP-SELXXX rather than
	 * a service name.
	 */
	char	irdaServiceName[25];
} SOCKADDR_IRDA, *PSOCKADDR_IRDA;

typedef struct _IRDA_DEVICE_INFO
{
	u_char  irdaDeviceID[4];
	char	irdaDeviceName[22];
    u_char  Reserved[2];
} IRDA_DEVICE_INFO, *PIRDA_DEVICE_INFO, FAR *LPIRDA_DEVICE_INFO;

typedef struct _DEVICELIST
{
	ULONG               numDevice;
	IRDA_DEVICE_INFO	Device[1];
} DEVICELIST, *PDEVICELIST, FAR *LPDEVICELIST;

/**
 * This structure contains data for creating an Data Access Service (IAS) object.
 *
 * If either the octet sequence specified in OctetSeq or the user string specified in UsrStr is
 * associated with irdaAttribName, it is necessary to allocate additional buffer space.
 *
 * The Windows CE irdaClassName and irdaAttribName members have different maximum lengths than their
 * Windows counterparts. The irdaAttribType, Len, and irdaAttribInt members also have different
 * types.
 *
 * The IAS_SET structure does not contain the required buffer space for either the octet sequence
 * attributes or user string sequence attributes. To ensure that the buffer is large enough to query
 * all remote objects, the maximum required buffer is sizeof(IAS_SET) + 1024, which is the maximum
 * attribute value length for an octet sequence.
 */
typedef struct _IAS_SET
{
    /**
     * Null-terminated string that is the class name for an IAS object. Maximum of 60 characters.
     */
    char    irdaClassName[61];
    /**
     * Null-terminated string that is the attribute name for an IAS object. Maximum of 60 characters.
     */
    char    irdaAttribName[61];
    /**
     * Attribute type. It is one of the following values: Value Description IAS_ATTRIB_INT Identifies an
     * integer attribute value. IAS_ATTRIB_OCTETSEQ Identifies a binary, or octet, attribute value.
     * IAS_ATTRIB_STR Identifies a string attribute value.
     */
    u_short irdaAttribType;
    union
    {
        /**
         * 32-bit signed integer attribute value.
         */
        int irdaAttribInt;
        struct
        {
            int     Len;
            u_char  OctetSeq[1];
            /**
             * Used to DWORD-align the structure.
             */
            u_char  Reserved[3];
        } irdaAttribOctetSeq;
        struct
        {
            int     Len;
            u_char  CharSet;
            u_char  UsrStr[1];
            u_char  Reserved[2];
        } irdaAttribUsrStr;
    } irdaAttribute;
} IAS_SET, *PIAS_SET, FAR *LPIAS_SET;

/**
 * This structure contains data for an Data Access Service (IAS) object obtained from querying a
 * remote device.
 *
 * If either the octet sequence specified in OctetSeq, or the user string specified in UsrStr is
 * associated with irdaAttribName, it is necessary to allocate additional buffer space.
 *
 * The remote device is queried for the attributes of an IAS object with the specified irdaClassName
 * and irdaAttribName. If an attribute of the specified object is not found on the remote device,
 * then the irdaAttribType is set to IAS_ATTRIB_NO_ATTRIB to indicate that no attribute was found.
 *
 * The Windows CE irdaClassName and irdaAttribName members have different maximum lengths than their
 * Windows counterparts. The irdaAttribType, Len, and irdaAttribInt members also have different
 * types.
 *
 * The Windows CE IAS_SET structure does not contain the required buffer space for either the octet
 * sequence attributes or user string sequence attributes. To ensure that the buffer is large enough
 * to query all remote objects, the maximum required buffer is sizeof(IAS_SET) +1024, which is the
 * maximum attribute value length for an octet sequence.
 */
typedef struct _IAS_QUERY
{
	/**
	 * Device identifier of the remote device to query.
	 */
	u_char  irdaDeviceID[4];
    /**
     * Null-terminated string that is the class name for an IAS object. Maximum of 60 characters.
     */
    char    irdaClassName[61];
    /**
     * Null-terminated string that is the attribute name for an IAS object. Maximum of 60 characters.
     */
    char    irdaAttribName[61];
    /**
     * Attribute type. It is one of the following values: Value Description IAS_ATTRIB_INT Identifies an
     * integer attribute value. IAS_ATTRIB_OCTETSEQ Identifies a binary, or octet, attribute value.
     * IAS_ATTRIB_STR Identifies a string attribute value.
     */
    u_short irdaAttribType;
    union
    {
        /**
         * 32-bit signed integer attribute value.
         */
        int irdaAttribInt;
        struct
        {
            int     Len;
            u_char  OctetSeq[1];
            /**
             * Used to DWORD-align the structure.
             */
            u_char  Reserved[3];
        } irdaAttribOctetSeq;
        struct
        {
            int     Len;
            u_char  CharSet;
            u_char  UsrStr[1];
            u_char  Reserved[2];
        } irdaAttribUsrStr;
    } irdaAttribute;
} IAS_QUERY, *PIAS_QUERY, FAR *LPIAS_QUERY;

#endif // __AFIRDA__

// @CESYSGEN ENDIF
