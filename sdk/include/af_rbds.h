/*******************************************************************************
Copyright (c) 1996 Microsoft Corporation

af_rbds.h

Public Header for RBDS Sock Address Family 

Author:

*******************************************************************************/
#ifndef _AF_RBDS_H_
#define _AF_RBDS_H_

struct sockaddr_rbds {
    short           srbds_family;
    unsigned char   srbds_tuner_id;                             // Tuner ID
    unsigned char   srbds_type;                                 // RBDS message types
    unsigned char   srbds_mbs_sysid;                            // MBS system ID
    unsigned char   empty[11];                                  // total len should be 16 to match other sockaddr's
};

typedef struct sockaddr_rbds SOCKADDR_RBDS, *PSOCKADDR_RBDS;

#define RBDSADDR_PS             ((unsigned char)0x00)           // Basic Tuning and Switching Information
#define RBDSADDR_PIN            ((unsigned char)0x01)           // Program item number and slow labelling codes
#define RBDSADDR_RT             ((unsigned char)0x02)           // Radio Text
#define RBDSADDR_LN             ((unsigned char)0x03)           // Location and Navigation
#define RBDSADDR_CT             ((unsigned char)0x04)           // Clock time and date
#define RBDSADDR_TDC            ((unsigned char)0x05)           // Transparent Data Channels
#define RBDSADDR_IH             ((unsigned char)0x06)           // In House Applications
#define RBDSADDR_RP             ((unsigned char)0x07)           // Radio Paging
#define RBDSADDR_TMC            ((unsigned char)0x08)           // TMC reserve
#define RBDSADDR_EWS            ((unsigned char)0x09)           // Emergency warning systems
#define RBDSADDR_PTYN           ((unsigned char)0x0A)           // Program Type name
//
// undefined 0x0B - 0x0D
//
#define RBDSADDR_EON            ((unsigned char)0x0E)           // Enhanced other networks information
#define RBDSADDR_FPS            ((unsigned char)0x0F)           // Fast basic tuning and switching information

#define RBDSADDR_ANY            ((unsigned char)0xff)           // all RBDS information
#define RBDSADDR_MBS            ((unsigned char)0xfE)           // MMBS packages


#define RBDSADDR_TUNERID_ANY    ((unsigned char)0x00)           // all tuner RBDS information

#define RBDSPROTO_NORM  0                                       // Non modified RBDS


#endif /* _AF_RBDS_H_ */
