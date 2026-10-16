/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.
Copyright (c) 1995, 1996, 1997  Microsoft Corporation

Module Name:

winsock.h

Abstract:

Windows CE version of winsock.h.

Notes:


--*/
/*++

  This file includes parts which are Copyright (c) 1982-1986 Regents
  of the University of California.  All rights reserved.  The
  Berkeley Software License Agreement specifies the terms and
  conditions for redistribution.

Module Name: winsock.h-definitions to be used with the WINSOCK.DLL

Purpose: This header file corresponds to version 1.1 of the Windows Sockets
specification.

--*/

// @CESYSGEN IF CE_MODULES_WINSOCK

#ifndef _WINSOCKAPI_
#define _WINSOCKAPI_

#ifndef WINSOCKAPI
#ifdef UNDER_NT
#define WINSOCKAPI WINAPI
#else
#define WINSOCKAPI __cdecl
#endif
#endif

/*
 * Basic system type definitions, taken from the BSD file sys/types.h.
 */
typedef unsigned char   u_char;
typedef unsigned short  u_short;
typedef unsigned int    u_int;
typedef unsigned long   u_long;

/*
 * The new type to be used in all
 * instances which refer to sockets.
 */
typedef u_int           SOCKET;

/*
 * Select uses arrays of SOCKETs.  These macros manipulate such
 * arrays.  FD_SETSIZE may be defined by the user before including
 * this file, but the default here should be >= 64.
 *
 * CAVEAT IMPLEMENTOR and USER: THESE MACROS AND TYPES MUST BE
 * INCLUDED IN WINSOCK.H EXACTLY AS SHOWN HERE.
 */
#ifndef FD_SETSIZE
#define FD_SETSIZE      64
#endif /* FD_SETSIZE */

typedef struct fd_set {
        u_short fd_count;               /* how many are SET? */
        SOCKET  fd_array[FD_SETSIZE];   /* an array of SOCKETs */
} fd_set;

#ifdef __cplusplus
extern "C" {
#endif

extern int WINSOCKAPI __WSAFDIsSet(SOCKET, fd_set *);

#ifdef __cplusplus
}
#endif

#define FD_CLR(fd, set) do { \
    u_int __i; \
    for (__i = 0; __i < ((fd_set *)(set))->fd_count ; __i++) { \
        if (((fd_set *)(set))->fd_array[__i] == fd) { \
            while (__i < ((fd_set *)(set))->fd_count-1) { \
                ((fd_set *)(set))->fd_array[__i] = \
                    ((fd_set *)(set))->fd_array[__i+1]; \
                __i++; \
            } \
            ((fd_set *)(set))->fd_count--; \
            break; \
        } \
    } \
} while(0)

#define FD_SET(fd, set) do { \
    if ((! __WSAFDIsSet((SOCKET)fd, (fd_set *)set)) &&  \
        (((fd_set *)(set))->fd_count < FD_SETSIZE)) \
        ((fd_set *)(set))->fd_array[((fd_set *)(set))->fd_count++]=fd;\
} while(0)

#define FD_ZERO(set) (((fd_set *)(set))->fd_count=0)

#define FD_ISSET(fd, set) __WSAFDIsSet((SOCKET)fd, (fd_set *)set)

/*
 * Structure used in select() call, taken from the BSD file sys/time.h.
 */
struct timeval {
        long    tv_sec;         /* seconds */
        long    tv_usec;        /* and microseconds */
};

/*
 * Operations on timevals.
 *
 * NB: timercmp does not work for >= or <=.
 */
#define timerisset(tvp)         ((tvp)->tv_sec || (tvp)->tv_usec)
#define timercmp(tvp, uvp, cmp) \
        ((tvp)->tv_sec cmp (uvp)->tv_sec || \
         (tvp)->tv_sec == (uvp)->tv_sec && (tvp)->tv_usec cmp (uvp)->tv_usec)
#define timerclear(tvp)         (tvp)->tv_sec = (tvp)->tv_usec = 0

/*
 * Commands for ioctlsocket(),  taken from the BSD file fcntl.h.
 *
 *
 * Ioctl's have the command encoded in the lower word,
 * and the size of any in or out parameters in the upper
 * word.  The high 2 bits of the upper word are used
 * to encode the in/out status of the parameter; for now
 * we restrict parameters to at most 128 bytes.
 */
#define IOCPARM_MASK    0x7ff            /* parameters must be < 2k bytes */
#define	IOCGROUP(x)	(((x) >> 8) & 0xff)
#define IOC_VOID        0x20000000      /* no parameters */
#define IOC_OUT         0x40000000      /* copy out parameters */
#define IOC_IN          0x80000000      /* copy in parameters */
#define IOC_INOUT       (IOC_IN|IOC_OUT)
#define	_IOC(inout,group,num,len) \
	(inout | ((len & IOCPARM_MASK) << 16) | ((group) << 8) | (num))
#define	_IO(g,n)	_IOC(IOC_VOID,	(g), (n), 0)
#define	_IOR(g,n,t)	_IOC(IOC_OUT,	(g), (n), sizeof(t))
#define	_IOW(g,n,t)	_IOC(IOC_IN,	(g), (n), sizeof(t))
/* this should be _IORW, but stdio got there first */
#define	_IOWR(g,n,t)	_IOC(IOC_INOUT,	(g), (n), sizeof(t))


#define FIONREAD    _IOR('f', 127, u_long) /* get # bytes to read */
#define FIONBIO     _IOW('f', 126, u_long) /* set/clear non-blocking i/o */
#define FIOASYNC    _IOW('f', 125, u_long) /* set/clear async i/o */

/* Socket I/O Controls */
#define SIOCSHIWAT  _IOW('s',  0, u_long)  /* set high watermark */
#define SIOCGHIWAT  _IOR('s',  1, u_long)  /* get high watermark */
#define SIOCSLOWAT  _IOW('s',  2, u_long)  /* set low watermark */
#define SIOCGLOWAT  _IOR('s',  3, u_long)  /* get low watermark */
#define SIOCATMARK  _IOR('s',  7, u_long)  /* at oob mark? */

/*
 * Structures returned by network data base library, taken from the
 * BSD file netdb.h.  All addresses are supplied in host order, and
 * returned in network order (suitable for use in system calls).
 */

struct  hostent {
        char    * h_name;           /* official name of host */
        char    * * h_aliases;  /* alias list */
        short   h_addrtype;             /* host address type */
        short   h_length;               /* length of address */
        char    * * h_addr_list; /* list of addresses */
#define h_addr  h_addr_list[0]          /* address, for backward compat */
};

/*
 * It is assumed here that a network number
 * fits in 32 bits.
 */
struct  netent {
        char    * n_name;           /* official name of net */
        char    * * n_aliases;  /* alias list */
        short   n_addrtype;             /* net address type */
        u_long  n_net;                  /* network # */
};

struct  servent {
        char    * s_name;           /* official service name */
        char    * * s_aliases;  /* alias list */
        short   s_port;                 /* port # */
        char    * s_proto;          /* protocol to use */
};

struct  protoent {
        char    * p_name;           /* official protocol name */
        char    * * p_aliases;  /* alias list */
        short   p_proto;                /* protocol # */
};

/*
 * Constants and structures defined by the internet system,
 * Per RFC 790, September 1981, taken from the BSD file netinet/in.h.
 */

/*
 * Protocols
 */
#define IPPROTO_IP              0               /* dummy for IP */
#define IPPROTO_ICMP            1               /* control message protocol */
#define IPPROTO_GGP             2               /* gateway^2 (deprecated) */
#define IPPROTO_TCP             6               /* tcp */
#define IPPROTO_PUP             12              /* pup */
#define IPPROTO_UDP             17              /* user datagram protocol */
#define IPPROTO_IDP             22              /* xns idp */
#define IPPROTO_ND              77              /* UNOFFICIAL net disk proto */
#define IPPROTO_RAW             255             /* raw IP packet */
#define IPPROTO_MAX             256

/*
 * Port/socket numbers: network standard functions
 */
#define IPPORT_ECHO             7
#define IPPORT_DISCARD          9
#define IPPORT_SYSTAT           11
#define IPPORT_DAYTIME          13
#define IPPORT_NETSTAT          15
#define IPPORT_FTP              21
#define IPPORT_TELNET           23
#define IPPORT_SMTP             25
#define IPPORT_TIMESERVER       37
#define IPPORT_NAMESERVER       42
#define IPPORT_WHOIS            43
#define IPPORT_MTP              57

/*
 * Port/socket numbers: host specific functions
 */
#define IPPORT_TFTP             69
#define IPPORT_RJE              77
#define IPPORT_FINGER           79
#define IPPORT_TTYLINK          87
#define IPPORT_SUPDUP           95

/*
 * UNIX TCP sockets
 */
#define IPPORT_EXECSERVER       512
#define IPPORT_LOGINSERVER      513
#define IPPORT_CMDSERVER        514
#define IPPORT_EFSSERVER        520

/*
 * UNIX UDP sockets
 */
#define IPPORT_BIFFUDP          512
#define IPPORT_WHOSERVER        513
#define IPPORT_ROUTESERVER      520
                                        /* 520+1 also used */

/*
 * Ports < IPPORT_RESERVED are reserved for
 * privileged processes (e.g. root).
 */
#define IPPORT_RESERVED         1024

/*
 * Link numbers
 */
#define IMPLINK_IP              155
#define IMPLINK_LOWEXPER        156
#define IMPLINK_HIGHEXPER       158

/*
 * Internet address (old style... should be updated)
 */
struct in_addr {
        union {
                struct { u_char s_b1,s_b2,s_b3,s_b4; } S_un_b;
                struct { u_short s_w1,s_w2; } S_un_w;
                u_long S_addr;
        } S_un;
#define s_addr  S_un.S_addr
                                /* can be used for most tcp & ip code */
#define s_host  S_un.S_un_b.s_b2
                                /* host on imp */
#define s_net   S_un.S_un_b.s_b1
                                /* network */
#define s_imp   S_un.S_un_w.s_w2
                                /* imp */
#define s_impno S_un.S_un_b.s_b4
                                /* imp # */
#define s_lh    S_un.S_un_b.s_b3
                                /* logical host */
};

/*
 * Definitions of bits in internet address integers.
 * On subnets, the decomposition of addresses to host and net parts
 * is done according to subnet mask, not the masks here.
 */
#define IN_CLASSA(i)            (((long)(i) & 0x80000000) == 0)
#define IN_CLASSA_NET           0xff000000
#define IN_CLASSA_NSHIFT        24
#define IN_CLASSA_HOST          0x00ffffff
#define IN_CLASSA_MAX           128

#define IN_CLASSB(i)            (((long)(i) & 0xc0000000) == 0x80000000)
#define IN_CLASSB_NET           0xffff0000
#define IN_CLASSB_NSHIFT        16
#define IN_CLASSB_HOST          0x0000ffff
#define IN_CLASSB_MAX           65536

#define IN_CLASSC(i)            (((long)(i) & 0xe0000000) == 0xc0000000)
#define IN_CLASSC_NET           0xffffff00
#define IN_CLASSC_NSHIFT        8
#define IN_CLASSC_HOST          0x000000ff

#define INADDR_ANY              (u_long)0x00000000
#define INADDR_LOOPBACK         0x7f000001
#define INADDR_BROADCAST        (u_long)0xffffffff
#define INADDR_NONE             0xffffffff

/*
 * Socket address, internet style.
 */
struct sockaddr_in {
        short   sin_family;
        u_short sin_port;
        struct  in_addr sin_addr;
        char    sin_zero[8];
};

#define WSADESCRIPTION_LEN      256
#define WSASYS_STATUS_LEN       128

/**
 * This structure is used to store Windows Sockets initialization data returned by a call to
 * WSAStartup. It contains data about the Winsock.dll implementation.
 *
 * WSAStartup assigns the following values to the members of the WSADATA structure:
 *
 * WSADATA member Assigned value wVersion wVersionRequested parameter value wHighVersion
 * wVersionRequested parameter value szDescription NULL string szSystemStatus NULL string
 * iMaxSockets 20 iMaxUdpDg 0 lpVendorInfo NULL
 */
typedef struct WSAData {
        /**
         * Version of the Windows Sockets specification that the Windows Sockets DLL expects the caller to
         * use. The high-order word specifies the minor version (revision) number; and the low-order word
         * specifies the major version number.
         */
        WORD                    wVersion;
        /**
         * Highest version of the Windows Sockets specification that this DLL can support, usually the same
         * as wVersion.
         */
        WORD                    wHighVersion;
        /**
         * Null-terminated string into which the Windows Sockets DLL copies a description of the Windows
         * Sockets implementation, including vendor identification. The text-up to 256 characters in
         * length-can contain any characters, but vendors are cautioned against including control and
         * formatting characters. Typically, an application uses this description in a status message.
         */
        char                    szDescription[WSADESCRIPTION_LEN+1];
        /**
         * Null-terminated string into which the Windows Sockets DLL copies relevant status or configuration
         * data. The Windows Sockets DLL should use this member only if the data might be useful to the user
         * or support staff; it should not be considered as an extension of the szDescription member.
         */
        char                    szSystemStatus[WSASYS_STATUS_LEN+1];
        /**
         * Maximum number of sockets which a single process can potentially open. A Windows Sockets
         * implementation can provide a global pool of sockets for allocation to any process; alternatively
         * it can allocate per-process resources for sockets. The number can well reflect the way in which
         * the Windows Sockets DLL or the networking software was configured. Application writers can use
         * this number as a crude indication of whether the Windows Sockets implementation is usable by the
         * application. For example, an X Windows server might check iMaxSockets when first started: if it
         * is less than 8, the application would display an error message instructing the user to
         * reconfigure the networking software. (This is a situation in which the szSystemStatus text might
         * be used.) Obviously there is no guarantee that a particular application can actually allocate
         * iMaxSockets sockets, since there can be other Windows Sockets applications in use.
         */
        unsigned short          iMaxSockets;
        /**
         * Size, in bytes, of the largest User Datagram Protocol (UDP) datagram that can be sent or received
         * by a Windows Sockets application. If the implementation imposes no limit, iMaxUdpDg is zero. In
         * many implementations of Berkeley sockets, there is an implicit limit of 8192 bytes on UDP
         * datagrams, which are fragmented if necessary. A Windows Sockets implementation can impose a limit
         * based, for instance, on the allocation of fragment reassembly buffers. The minimum value of
         * iMaxUdpDg for a compliant Windows Sockets implementation is 512. Note that regardless of the
         * value of iMaxUdpDg, it is inadvisable to attempt to send a broadcast datagram which is larger
         * than the Maximum Transmission Unit (MTU) for the network.
         *
         * The Windows Sockets API does not provide a mechanism to discover the MTU, but it must be no less
         * than 512 bytes.
         */
        unsigned short          iMaxUdpDg;
        /**
         * Long pointer to a vendor-specific data structure. The definition of this structure (if supplied)
         * is beyond the scope of the Windows Sockets specification.
         */
        char FAR *              lpVendorInfo;
} WSADATA;

typedef WSADATA FAR *LPWSADATA;

/*
 * Options for use with [gs]etsockopt at the IP level.
 */
#define IP_OPTIONS      1               /* set/get IP per-packet options */
#define IP_MULTICAST_IF     2           /* set/get IP multicast interface   */
#define IP_MULTICAST_TTL    3           /* set/get IP multicast timetolive  */
#define IP_MULTICAST_LOOP   4           /* set/get IP multicast loopback    */
#define IP_ADD_MEMBERSHIP   5           /* add  an IP group membership      */
#define IP_DROP_MEMBERSHIP  6           /* drop an IP group membership      */

#define IP_DEFAULT_MULTICAST_TTL   1    /* normally limit m'casts to 1 hop  */
#define IP_DEFAULT_MULTICAST_LOOP  1    /* normally hear sends if a member  */
#define IP_MAX_MEMBERSHIPS         20   /* per socket; must fit in one mbuf */

/*
 * Argument structure for IP_ADD_MEMBERSHIP and IP_DROP_MEMBERSHIP.
 */
struct ip_mreq {
        struct in_addr  imr_multiaddr;  /* IP multicast address of group */
        struct in_addr  imr_interface;  /* local IP address of interface */
};

/*
 * Definitions related to sockets: types, address families, options,
 * taken from the BSD file sys/socket.h.
 */

/*
 * This is used instead of -1, since the
 * SOCKET type is unsigned.
 */
#define INVALID_SOCKET  (SOCKET)(~0)
#define SOCKET_ERROR            (-1)

/*
 * Types
 */
#define SOCK_STREAM     1               /* stream socket */
#define SOCK_DGRAM      2               /* datagram socket */
#define SOCK_RAW        3               /* raw-protocol interface */
#define SOCK_RDM        4               /* reliably-delivered message */
#define SOCK_SEQPACKET  5               /* sequenced packet stream */

/*
 * Option flags per-socket.
 */
#define SO_DEBUG        0x0001          /* turn on debugging info recording */
#define SO_ACCEPTCONN   0x0002          /* socket has had listen() */
#define SO_REUSEADDR    0x0004          /* allow local address reuse */
#define SO_KEEPALIVE    0x0008          /* keep connections alive */
#define SO_DONTROUTE    0x0010          /* just use interface addresses */
#define SO_BROADCAST    0x0020          /* permit sending of broadcast msgs */
#define SO_USELOOPBACK  0x0040          /* bypass hardware when possible */
#define SO_LINGER       0x0080          /* linger on close if data present */
#define SO_OOBINLINE    0x0100          /* leave received OOB data in line */

#define SO_DONTLINGER   (u_int)(~SO_LINGER)

/*
 * Additional options.
 */
#define SO_SNDBUF       0x1001          /* send buffer size */
#define SO_RCVBUF       0x1002          /* receive buffer size */
#define SO_SNDLOWAT     0x1003          /* send low-water mark */
#define SO_RCVLOWAT     0x1004          /* receive low-water mark */
#define SO_SNDTIMEO     0x1005          /* send timeout */
#define SO_RCVTIMEO     0x1006          /* receive timeout */
#define SO_ERROR        0x1007          /* get error status and clear */
#define SO_TYPE         0x1008          /* get socket type */

/*
 * Option for opening sockets for synchronous access.
 */
#define SO_OPENTYPE     0x7008

/*
 * Options and option values for creating a secure socket.
 */
#define SO_SECURE       0x2001          /* add security to socket */
#define SO_SEC_NONE     0x2002          /* security not used on socket */
#define SO_SEC_SSL      0x2004          /* use unified SSL/PCT for security */

/*
 * TCP options.
 */
#define TCP_NODELAY     0x0001
#define TCP_BSDURGENT   0x7000


/*
 * Address families.
 */
 //	NOTE: these AF_ types MUST match those in import\tdi.h TDI_ADDRESS_TYPE_ def's
 // otherwise will not be able to correctly match addresses.
#define AF_UNSPEC       0               /* unspecified */
#define AF_UNIX         1               /* local to host (pipes, portals) */
#define AF_INET         2               /* internetwork: UDP, TCP, etc. */
#define AF_IMPLINK      3               /* arpanet imp addresses */
#define AF_PUP          4               /* pup protocols: e.g. BSP */
#define AF_CHAOS        5               /* mit CHAOS protocols */
#define AF_NS           6               /* XEROX NS protocols */
#define AF_IPX          6               /* IPX and SPX */
#define AF_ISO          7               /* ISO protocols */
#define AF_OSI          AF_ISO          /* OSI is ISO */
#define AF_ECMA         8               /* european computer manufacturers */
#define AF_DATAKIT      9               /* datakit protocols */
#define AF_CCITT        10              /* CCITT protocols, X.25 etc */
#define AF_SNA          11              /* IBM SNA */
#define AF_DECnet       12              /* DECnet */
#define AF_DLI          13              /* Direct data link interface */
#define AF_LAT          14              /* LAT */
#define AF_HYLINK       15              /* NSC Hyperchannel */
#define AF_APPLETALK    16              /* AppleTalk */
#define AF_NETBIOS      17              /* NetBios-style addresses */
#define AF_PAGER		21				/* Pager addresses */	// WINCE this # to match TDI_ADDRESS types
#define AF_IRDA         22              /* IrDA */
#define AF_RBDS         23              /* RBDS */

#define AF_MAX          24

/*
 * Structure used by kernel to store most
 * addresses.
 */
struct sockaddr {
        u_short sa_family;              /* address family */
        char    sa_data[14];            /* up to 14 bytes of direct address */
};

/*
 * Structure used by kernel to pass protocol
 * information in raw sockets.
 */
struct sockproto {
        u_short sp_family;              /* address family */
        u_short sp_protocol;            /* protocol */
};

/*
 * Protocol families, same as address families for now.
 */
#define PF_UNSPEC       AF_UNSPEC
#define PF_UNIX         AF_UNIX
#define PF_INET         AF_INET
#define PF_IMPLINK      AF_IMPLINK
#define PF_PUP          AF_PUP
#define PF_CHAOS        AF_CHAOS
#define PF_NS           AF_NS
#define PF_IPX          AF_IPX
#define PF_ISO          AF_ISO
#define PF_OSI          AF_OSI
#define PF_ECMA         AF_ECMA
#define PF_DATAKIT      AF_DATAKIT
#define PF_CCITT        AF_CCITT
#define PF_SNA          AF_SNA
#define PF_DECnet       AF_DECnet
#define PF_DLI          AF_DLI
#define PF_LAT          AF_LAT
#define PF_HYLINK       AF_HYLINK
#define PF_APPLETALK    AF_APPLETALK

#define PF_MAX          AF_MAX

/*
 * Structure used for manipulating linger option.
 */
struct  linger {
        u_short l_onoff;                /* option on/off */
        u_short l_linger;               /* linger time */
};

/*
 * Level number for (get/set)sockopt() to apply to socket itself.
 */
#define SOL_SOCKET      0xffff          /* options for socket level */

/*
 * Maximum queue length specifiable by listen.
 */
#define SOMAXCONN       5

#define MSG_OOB         0x1             /* process out-of-band data */
#define MSG_PEEK        0x2             /* peek at incoming message */
#define MSG_DONTROUTE   0x4             /* send without using routing tables */

#define MSG_MAXIOVLEN   16

#define	MSG_PARTIAL     0x8000          /* partial send or recv for message xport */

/*
 * Define constant based on rfc883, used by gethostbyxxxx() calls.
 */
#define MAXGETHOSTSTRUCT        1024

/*
 * Define flags to be used with the WSAAsyncSelect() call.
 */
#define FD_READ         0x01
#define FD_WRITE        0x02
#define FD_OOB          0x04
#define FD_ACCEPT       0x08
#define FD_CONNECT      0x10
#define FD_CLOSE        0x20

/*
 * All Windows Sockets error constants are biased by WSABASEERR from
 * the "normal"
 */
#define WSABASEERR              10000
/*
 * Windows Sockets definitions of regular Microsoft C error constants
 */
#define WSAEINTR                (WSABASEERR+4)
#define WSAEBADF                (WSABASEERR+9)
#define WSAEACCES               (WSABASEERR+13)
#define WSAEFAULT               (WSABASEERR+14)
#define WSAEINVAL               (WSABASEERR+22)
#define WSAEMFILE               (WSABASEERR+24)

/*
 * Windows Sockets definitions of regular Berkeley error constants
 */
#define WSAEWOULDBLOCK          (WSABASEERR+35)
#define WSAEINPROGRESS          (WSABASEERR+36)
#define WSAEALREADY             (WSABASEERR+37)
#define WSAENOTSOCK             (WSABASEERR+38)
#define WSAEDESTADDRREQ         (WSABASEERR+39)
#define WSAEMSGSIZE             (WSABASEERR+40)
#define WSAEPROTOTYPE           (WSABASEERR+41)
#define WSAENOPROTOOPT          (WSABASEERR+42)
#define WSAEPROTONOSUPPORT      (WSABASEERR+43)
#define WSAESOCKTNOSUPPORT      (WSABASEERR+44)
#define WSAEOPNOTSUPP           (WSABASEERR+45)
#define WSAEPFNOSUPPORT         (WSABASEERR+46)
#define WSAEAFNOSUPPORT         (WSABASEERR+47)
#define WSAEADDRINUSE           (WSABASEERR+48)
#define WSAEADDRNOTAVAIL        (WSABASEERR+49)
#define WSAENETDOWN             (WSABASEERR+50)
#define WSAENETUNREACH          (WSABASEERR+51)
#define WSAENETRESET            (WSABASEERR+52)
#define WSAECONNABORTED         (WSABASEERR+53)
#define WSAECONNRESET           (WSABASEERR+54)
#define WSAENOBUFS              (WSABASEERR+55)
#define WSAEISCONN              (WSABASEERR+56)
#define WSAENOTCONN             (WSABASEERR+57)
#define WSAESHUTDOWN            (WSABASEERR+58)
#define WSAETOOMANYREFS         (WSABASEERR+59)
#define WSAETIMEDOUT            (WSABASEERR+60)
#define WSAECONNREFUSED         (WSABASEERR+61)
#define WSAELOOP                (WSABASEERR+62)
#define WSAENAMETOOLONG         (WSABASEERR+63)
#define WSAEHOSTDOWN            (WSABASEERR+64)
#define WSAEHOSTUNREACH         (WSABASEERR+65)
#define WSAENOTEMPTY            (WSABASEERR+66)
#define WSAEPROCLIM             (WSABASEERR+67)
#define WSAEUSERS               (WSABASEERR+68)
#define WSAEDQUOT               (WSABASEERR+69)
#define WSAESTALE               (WSABASEERR+70)
#define WSAEREMOTE              (WSABASEERR+71)

#define WSAEDISCON              (WSABASEERR+101)


/*
 * Extended Windows Sockets error constant definitions
 */
#define WSASYSNOTREADY			(WSABASEERR+91)
#define WSAVERNOTSUPPORTED      (WSABASEERR+92)
#define WSANOTINITIALISED       (WSABASEERR+93)


/*
 * Error return codes from gethostbyname() and gethostbyaddr()
 * (when using the resolver). Note that these errors are
 * retrieved via GetLastError() and must therefore follow
 * the rules for avoiding clashes with error numbers from
 * specific implementations or language run-time systems.
 * For this reason the codes are based at WSABASEERR+1001.
 * Note also that [WSA]NO_ADDRESS is defined only for
 * compatibility purposes.
 */

#define h_errno         GetLastError()

/* Authoritative Answer: Host not found */
#define WSAHOST_NOT_FOUND       (WSABASEERR+1001)
#define HOST_NOT_FOUND          WSAHOST_NOT_FOUND

/* Non-Authoritative: Host not found, or SERVERFAIL */
#define WSATRY_AGAIN            (WSABASEERR+1002)
#define TRY_AGAIN               WSATRY_AGAIN

/* Non recoverable errors, FORMERR, REFUSED, NOTIMP */
#define WSANO_RECOVERY          (WSABASEERR+1003)
#define NO_RECOVERY             WSANO_RECOVERY

/* Valid name, no data record of requested type */
#define WSANO_DATA              (WSABASEERR+1004)
#define NO_DATA                 WSANO_DATA

/* no address, look for MX record */
#define WSANO_ADDRESS           WSANO_DATA
#define NO_ADDRESS              WSANO_ADDRESS

/*
 * Windows Sockets errors redefined as regular Berkeley error constants
 */
#define EWOULDBLOCK             WSAEWOULDBLOCK
#define EINPROGRESS             WSAEINPROGRESS
#define EALREADY                WSAEALREADY
#define ENOTSOCK                WSAENOTSOCK
#define EDESTADDRREQ            WSAEDESTADDRREQ
#define EMSGSIZE                WSAEMSGSIZE
#define EPROTOTYPE              WSAEPROTOTYPE
#define ENOPROTOOPT             WSAENOPROTOOPT
#define EPROTONOSUPPORT         WSAEPROTONOSUPPORT
#define ESOCKTNOSUPPORT         WSAESOCKTNOSUPPORT
#define EOPNOTSUPP              WSAEOPNOTSUPP
#define EPFNOSUPPORT            WSAEPFNOSUPPORT
#define EAFNOSUPPORT            WSAEAFNOSUPPORT
#define EADDRINUSE              WSAEADDRINUSE
#define EADDRNOTAVAIL           WSAEADDRNOTAVAIL
#define ENETDOWN                WSAENETDOWN
#define ENETUNREACH             WSAENETUNREACH
#define ENETRESET               WSAENETRESET
#define ECONNABORTED            WSAECONNABORTED
#define ECONNRESET              WSAECONNRESET
#define ENOBUFS                 WSAENOBUFS
#define EISCONN                 WSAEISCONN
#define ENOTCONN                WSAENOTCONN
#define ESHUTDOWN               WSAESHUTDOWN
#define ETOOMANYREFS            WSAETOOMANYREFS
#define ETIMEDOUT               WSAETIMEDOUT
#define ECONNREFUSED            WSAECONNREFUSED
#define ELOOP                   WSAELOOP
#define ENAMETOOLONG            WSAENAMETOOLONG
#define EHOSTDOWN               WSAEHOSTDOWN
#define EHOSTUNREACH            WSAEHOSTUNREACH
#define ENOTEMPTY               WSAENOTEMPTY
#define EPROCLIM                WSAEPROCLIM
#define EUSERS                  WSAEUSERS
#define EDQUOT                  WSAEDQUOT
#define ESTALE                  WSAESTALE
#define EREMOTE                 WSAEREMOTE

/* Socket function prototypes */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * This function accepts a connection on a socket.
 *
 * @param s [in] Descriptor that identifies a socket that has been placed in a listening state with
 *   the listen function. The connection is actually made with the socket that is returned by accept.
 * @param addr [out] Optional pointer to a buffer that receives the address of the connecting
 *   entity, as known to the communications layer. The exact format of the addr parameter is
 *   determined by the address family established when the socket was created. Set to NULL for
 *   IrSocket implementation.
 * @param addrlen [out] Optional pointer to an integer that contains the length of the address addr.
 *   Set to NULL for IrSocket implementation.
 *
 * @return The return value is a handle for the socket on which the actual connection is made.
 *   INVALID_SOCKET indicates failure. To get a specific error value, call WSAGetLastError. The
 *   following table shows common error values. Value Description WSANOTINITIALISED A successful
 *   WSAStartup must occur before calling accept. WSAENETDOWN The network subsystem has failed.
 *   WSAEFAULT The addrlen parameter is too small or addr is not a valid part of the user address
 *   space. WSAEINPROGRESS A blocking Windows Sockets 1.1 call is in progress, or the service provider
 *   is still processing a callback function. WSAEINVAL The listen function was not invoked prior to
 *   accept. WSAEMFILE The queue is nonempty upon entry to accept and there are no descriptors
 *   available. WSAENOBUFS No buffer space is available. WSAENOTSOCK The descriptor is not a socket.
 *   WSAEOPNOTSUPP The referenced socket is not a type that supports connection-oriented service.
 *   WSAEWOULDBLOCK The socket is marked as nonblocking and no connections are present to be accepted.
 *   Windows CE does not support the WSAEINTR error value. The integer referred to by addrlen
 *   initially contains the amount of space pointed to by addr. On return it contains the actual
 *   length in bytes of the address returned.
 *
 * For Infrared Sockets (IrSock), set the addr and addrlen parameters to NULL.
 *
 * The accept function extracts the first connection on the queue of pending connections on socket
 * s. It then creates a new socket and returns a handle to the new socket. The newly created socket
 * is the socket that will handle the actual connection and has the same properties as socket s. The
 * newly created socket s does not have the listening socket's group identifier, if any was applied.
 *
 * The accept function can block the caller until a connection is present if no pending connections
 * are present on the queue, and the socket is marked as blocking. If the socket is marked
 * nonblocking and no pending connections are present on the queue, accept returns the
 * WSAEWOULDBLOCK error value. The socket handle returned from a successful accept call cannot be
 * used to accept further connections. The original socket remains open to listen for new connection
 * requests.
 *
 * The parameter addr is a result parameter that is filled in with the address of the connecting
 * entity, as known to the communications layer. The exact format of the addr parameter is
 * determined by the address family in which the communication is occurring. The addrlen is a
 * value-result parameter; it should initially contain the amount of space pointed to by addr; on
 * return it will contain the actual length (in bytes) of the address returned.
 *
 * The accept function is used with connection-oriented socket types such as SOCK_STREAM.
 *
 * If addr and/or addrlen are equal to NULL, then no information about the remote address of the
 * accepted socket is returned.
 */
SOCKET WINSOCKAPI accept (SOCKET s, struct sockaddr *addr,
                          int *addrlen);

/**
 * This function associates a local address with a socket.
 *
 * @param s [in] Descriptor that identifies an unbound socket.
 * @param name [in] Address to assign to the socket from the SOCKADDR structure.
 * @param namelen [in] Length of the name.
 *
 * @return Zero indicates that no error occurred. SOCKET_ERROR indicates failure. To get a specific
 *   error value, call WSAGetLastError.
 *
 * For Infrared Sockets (IrSock), this function has the following additional requirements and
 * behaviors:
 *
 * The Af_irda.h must be explicitly included.
 *
 * The sockaddr_irda structure is used in the addr parameter.
 *
 * The WSAENETDOWN error value is not supported.
 *
 * There is no wildcard address equivalent to INADDR_ANY.
 *
 * IrSockets clients must not call bind.
 *
 * If the service name is of the form "LSAP-SELXXX" where XXX is a decimal integer in the range
 * 1-127, the address indicates a specific LSAP-SEL. LSAP-SELXXX service names will cause no IAS
 * calls. The socket will be bound directly to the specified LSAP-SEL, bypassing IAS. Windows CE
 * reserves LSAP-SEL0 for IAS and LSAP-SEL3 for internal use.
 *
 * The bind function is used on an unconnected socket before subsequent calls to the connect or
 * listen functions. It is used to bind to either connection-oriented (stream) or connectionless
 * (datagram) sockets. When a socket is created with a call to the socket function, it exists in a
 * name space (address family), but it has no name assigned to it. Use the bind function to
 * establish the local association of the socket by assigning a local name to an unnamed socket.
 *
 * A name consists of three parts when using the Internet address family: the address family, a host
 * address, and a port number that identifies the application.
 *
 * If an application does not care what local address is assigned, specify the manifest constant
 * value ADDR_ANY for the sa_data member of the name parameter. This allows the underlying service
 * provider to use any appropriate network address, potentially simplifying application programming
 * in the presence of multihomed hosts (that is, hosts that have more than one network interface and
 * address).
 *
 * For TCP/IP, if the port is specified as zero, the service provider assigns a unique port to the
 * application with a value between 1024 and 5000. The application can use getsockname after calling
 * bind to learn the address and the port that has been assigned to it. If the Internet address is
 * equal to INADDR_ANY, getsockname may not necessarily supply the address until the socket is
 * connected, since several addresses can be valid if the host is multihomed. Binding to a specific
 * port number other than port 0 is discouraged for client applications, since there is a danger of
 * conflicting with another socket already using that port number.
 */
int WINSOCKAPI bind (SOCKET s, const struct sockaddr *addr, int namelen);

/**
 * This function closes a socket.
 *
 * @param s [in] Descriptor that identifies a socket to close.
 *
 * @return Zero indicates that no error occurred. SOCKET_ERROR indicates failure. To get a specific
 *   error value, call WSAGetLastError. Windows CE does not support the WSAEINTR error value.
 *
 * For Infrared Sockets (IrSock), this function has the following additional requirements and
 * behaviors:
 *
 * The Af_irda.h file must be explicitly included.
 *
 * The WSAENETDOWN error value is not supported.
 *
 * The standard linger options are supported.
 *
 * Although IrDA does not provide a graceful close, IrSock defers closing until the receive queues
 * are purged. Thus, an application can send data and immediately call the closesocket function
 * confident that the receiver will copy the data before receiving an FD_CLOSE message.
 *
 * The closesocket function closes a socket. Use it to release the socket descriptor s so that
 * further references to s will fail with the error WSAENOTSOCK. Any pending blocking or
 * asynchronous calls issued by any thread in this process are canceled without posting any
 * notification messages.
 *
 * An application should always have a matching call to closesocket for each successful call to
 * socket to return any socket resources to the system.
 *
 * The semantics of closesocket are affected by the socket options SO_LINGER and SO_DONTLINGER as
 * follows (SO_DONTLINGER is enabled by default; SO_LINGER is disabled).
 *
 * Option Interval Type of close Wait for close? SO_DONTLINGER Do not care Graceful No SO_LINGER
 * Zero Hard No SO_LINGER Nonzero Graceful Yes
 *
 * If SO_LINGER is set with a zero time-out interval (that is, the LINGER structure members l_onoff
 * is not zero and l_linger is zero), closesocket is not blocked even if queued data has not yet
 * been sent or acknowledged. This is called a hard or abortive close, because the socket's virtual
 * circuit is reset immediately, and any unsent data is lost. Any recv call on the remote side of
 * the circuit will fail with WSAECONNRESET.
 *
 * If SO_LINGER is set with a nonzero time-out interval on a blocking socket, the closesocket call
 * blocks on a blocking socket until the remaining data has been sent or until the time-out expires.
 * This is called a graceful disconnect. If the time-out expires before all data has been sent, the
 * Windows Sockets implementation terminates the connection before closesocket returns.
 *
 * Enabling SO_LINGER with a nonzero time-out interval on a nonblocking socket is not recommended.
 * In this case, the call to closesocket will fail with an error of WSAEWOULDBLOCK if the close
 * operation cannot be completed immediately. If closesocket fails with WSAEWOULDBLOCK the socket
 * handle is still valid, and a disconnect is not initiated. The application must call closesocket
 * again to close the socket. If SO_DONTLINGER is set on a stream socket by setting the l_onoff
 * member of the LINGER structure to zero, the closesocket call will return immediately and does not
 * receive WSAWOULDBLOCK whether the socket is blocking or nonblocking. However, any data queued for
 * transmission will be sent, if possible, before the underlying socket is closed. This is also
 * called a graceful disconnect. In this case, the Windows Sockets provider cannot release the
 * socket and other resources for an arbitrary period, thus affecting applications that expect to
 * use all available sockets. This is the default behavior (SO_DONTLINGER is set by default).
 *
 * Note To assure that all data is sent and received on a connection, an application should call
 * shutdown before calling closesocket. Also note, an FD_CLOSE network event is not posted after
 * closesocket is called.
 *
 * Here is a summary of closesocket behavior:
 *
 * If SO_DONTLINGER enabled (the default setting) it always returns immediately - connection is
 * gracefully closed in the background.
 *
 * If SO_LINGER enabled with a zero time-out: it always returns immediately - connection is
 * reset/terminated.
 *
 * If SO_LINGER enabled with nonzero time-out:
 *
 * with blocking socket it blocks until all data sent or time-out expires.
 *
 * with nonblocking socket it returns immediately that indicates failure.
 *
 * For additional information please see Graceful shutdown, linger options, and socket closure for
 * more information.
 */
int WINSOCKAPI closesocket (SOCKET s);

/**
 * This function establishes a connection to a peer.
 *
 * @param s [in] Descriptor that identifies an unconnected socket.
 * @param name [in] Name of the socket to connect to.
 * @param namelen [in] Length of the name parameter.
 *
 * @return Zero indicates that no error occurred. SOCKET_ERROR indicates failure. To get a specific
 *   error value, call WSAGetLastError. Windows CE does not support the WSAEINTR error value. On a
 *   blocking socket, the return value indicates success or failure of the connection attempt. With a
 *   nonblocking socket, the connection attempt cannot be completed immediately. In this case, connect
 *   will return SOCKET_ERROR, and WSAGetLastError will return WSAEWOULDBLOCK. In this case, use the
 *   select function to determine the completion of the connection request by checking to see if the
 *   socket is writeable. Until the connection attempt completes on a nonblocking socket, all
 *   subsequent calls to connect on the same socket will fail with the error value WSAEALREADY, and
 *   WSAEISCONN when the connection completes successfully. Due to ambiguities the Windows Sockets
 *   Specification 1.1, error values returned from connect while a connection is already pending may
 *   vary among implementations. As a result, it is not recommended that applications use multiple
 *   calls to connect to detect connection completion. If they do, they must be prepared to handle
 *   WSAEINVAL and WSAEWOULDBLOCK error values the same way that they handle WSAEALREADY, to assure
 *   robust execution. If the error value returned indicates the connection attempt failed (that is,
 *   WSAECONNREFUSED, WSAENETUNREACH, WSAETIMEDOUT) the application can call connect again for the
 *   same socket.
 *
 * For Infrared Sockets (IrSock), this function has the following additional requirements and
 * behaviors:
 *
 * The Af_irda.h file must be explicitly included.
 *
 * If WSAENETDOWN is returned, an existing IrDA connection was detected at the media access level.
 *
 * If WSAEADDRINUSE is returned, active connections to a device with a different address exist.
 *
 * If WSAEINPROGRESS is returned, IAS name resolution failed because another IAS query is in
 * progress. Retry the operation at one second intervals.
 *
 * If WSAEISCONN is returned, the socket is already connected or an exclusive/multiplexed mode
 * change failed.
 *
 * IrSock implements the connect function with addresses of the form sockaddr_irda. Typically, a
 * client application will create a socket with the socket function, scan the immediate vicinity for
 * IrDA devices with the IRLMP_ENUMDEVICES socket option, choose a device from the returned list,
 * form an address, and call connect. There is no difference in blocking and non-blocking semantics.
 *
 * The connect function is used to create a connection to the specified destination. If the socket,
 * s, is unbound, unique values are assigned to the local association by the system, and the socket
 * is marked as bound.
 *
 * For connection-oriented sockets (for example, type SOCK_STREAM), an active connection is
 * initiated to the foreign host using name (an address in the name space of the socket; for a
 * detailed description, please see bind and SOCKADDR). When the socket call completes successfully,
 * the socket is ready to send and receive data. If the address member of the structure specified by
 * the name parameter is all zeroes, connect will return the error WSAEADDRNOTAVAIL. Any attempt to
 * re-connect an active connection will fail with the error value WSAEISCONN.
 *
 * For connection-oriented, nonblocking sockets, it is often not possible to complete the connection
 * immediately. In such a case, this function returns the error WSAEWOULDBLOCK. However, the
 * operation proceeds. When the success or failure outcome becomes known and the client uses the
 * select function, success is reported in the writefds set and failure is reported in the exceptfds
 * set.
 *
 * For a connectionless socket (for example, type SOCK_DGRAM), the operation performed by connect is
 * merely to establish a default destination address that can be used on subsequent send and recv
 * calls. Any datagrams received from an address other than the destination address specified will
 * be discarded. If the address member of the structure specifed by name is all zeroes, the socket
 * will be disconnected. Then, the default remote address will be indeterminate, so send and recv
 * calls will return the error value WSAENOTCONN. However, sendto and recvfrom can still be used.
 * The default destination can be changed by simply calling connect again, even if the socket is
 * already connected. Any datagrams queued for receipt are discarded if name is different from the
 * previous connect.
 *
 * For connectionless sockets, name can indicate any valid address, including a broadcast address.
 * However, to connect to a broadcast address, a socket must use setsockopt to enable the
 * SO_BROADCAST option. Otherwise, connect will fail with the error value WSAEACCES.
 *
 * When a connection between sockets is broken, the sockets should be discarded and recreated. When
 * a problem develops on a connected socket, the application must discard and recreate the needed
 * sockets in order to return to a stable point.
 */
int WINSOCKAPI connect (SOCKET s, const struct sockaddr *name, int namelen);

/**
 * This function controls the mode of a socket.
 *
 * @param s [in] Descriptor that identifies a socket.
 * @param cmd [in] Command to perform on the socket s.
 * @param argp [in/out] Pointer to a parameter for cmd.
 *
 * @return Zero indicates success. SOCKET_ERROR indicates failure. To get a specific error value,
 *   call WSAGetLastError.
 *
 * The ioctlsocket function can be used on any socket in any state. It is used to set or retrieve
 * operating parameters associated with the socket, independent of the protocol and communications
 * subsystem. Here are the supported commands to use in the cmd parameter and their semantics:
 *
 * - FIONBIO: Use with a nonzero argp parameter to enable the nonblocking mode of socket s. The argp
 * parameter is zero if nonblocking is to be disabled. The argp parameter points to an unsigned long
 * value. When a socket is created, it operates in blocking mode by default (nonblocking mode is
 * disabled). This is consistent with BSD sockets.
 *
 * - FIONREAD: Use to determine the amount of data pending in the network's input buffer that can be
 * read from socket s. The argp parameter points to an unsigned long value in which ioctlsocket
 * stores the result. If s is stream oriented (for example, type SOCK_STREAM), FIONREAD returns the
 * amount of data that can be read in a single call to the recv function; this might not be the same
 * as the total amount of data queued on the socket. If s is message oriented (for example, type
 * SOCK_DGRAM), FIONREAD returns the size of the first datagram (message) queued on the socket.
 */
int WINSOCKAPI ioctlsocket (SOCKET s, long cmd, u_long *argp);

/**
 * This function gets the peer address to which a socket is connected.
 *
 * @param s [in] Descriptor that identifies a connected socket.
 * @param name [out] Structure that receives the peer name.
 * @param namelen [in/out] Pointer to the name structure size.
 *
 * @return Zero indicates no error occurred. SOCKET_ERROR indicates failure. To get a specific error
 *   value, call WSAGetLastError.
 *
 * The getpeername function retrieves the peer name connected to the socket s and stores it in the a
 * SOCKADDR structure identified by name. The getpeername function can be used only on a connected
 * socket. For datagram sockets, only the name of a peer specified in a previous connect call will
 * be returned-any name specified by a previous sendto call will not be returned by getpeername.
 *
 * On call, the namelen argument contains the name buffer size, in bytes. On return, the namelen
 * parameter contains the actual size, in bytes, of the name returned.
 */
int WINSOCKAPI getpeername (SOCKET s, struct sockaddr *name,
                            int * namelen);

/**
 * This function gets the local address for a socket.
 *
 * @param s [in] Descriptor that identifies a bound socket.
 * @param name [out] Receives the socket address (name).
 * @param namelen [in/out] name buffer size.
 *
 * @return Zero indicates no error occurred. SOCKET_ERROR indicates failure. To get a specific error
 *   value, call WSAGetLastError.
 *
 * The getsockname function retrieves the current name for the specified socket descriptor in name.
 * It is used on the bound or connected socket specified by the s parameter. The local association
 * is returned. This call is especially useful when a connect call has been made without doing a
 * bind first; the getsockname function provides the only way to determine the local association set
 * by the system.
 *
 * On call, the namelen argument contains the name buffer size, in bytes. On return, the namelen
 * parameter contains the actual name parameter size, in bytes.
 *
 * The getsockname function does not always return data about the host address when the socket has
 * been bound to an unspecified address, unless the socket has been connected with connect or accept
 * (for example, using ADDR_ANY). A Windows Sockets application must not assume that the address
 * will be specified unless the socket is connected. The address used for the socket is unknown
 * unless the socket is connected when used in a multihomed host. If the socket is using a
 * connectionless protocol, the address may not be available until I/O occurs on the socket.
 */
int WINSOCKAPI getsockname (SOCKET s, struct sockaddr *name,
                            int * namelen);

/**
 * This function retrieves a socket option.
 *
 * @param s [in] Descriptor that identifies a socket.
 * @param level [in] Level at which the option is defined; the supported levels include SOL_SOCKET,
 *   IPPROTO_TCP, and IPPROTO_IP. In Windows CE, the following level values are available when the
 *   level is IPPROTO_IP: Value Description IP_MULTICAST_TTL Time to Live for a multicast packet.
 *   Retrieves the number of hops for which a multicast message survives before it is discarded. Use
 *   int for optval. IP_MULTICAST_IF Address of the outgoing multicast-capable interface. This address
 *   is used for subsequent multicasts. Use unsigned long for optval. IP_MULTICAST_LOOP Status of the
 *   socket's loop behavior during multicast. Use unsigned long for optval.
 * @param optname [in] Socket option for which the value is to be retrieved.
 * @param optval [out] Pointer to the buffer in which the value for the requested option is to be
 *   returned.
 * @param optlen [in/out] Pointer to the optval buffer size.
 *
 * @return Zero indicates no error occurred. SOCKET_ERROR indicates failure. To get a specific error
 *   value, call WSAGetLastError.
 *
 * The getsockopt function retrieves the current value for a socket option associated with a socket
 * of any type, in any state, and stores the result in optval. Options can exist at multiple
 * protocol levels, but they are always present at the uppermost socket level. Options affect socket
 * operations, such as the packet routing and out-of-band data transfer.
 *
 * The value associated with the selected option is returned in the buffer optval. The integer
 * pointed to by optlen should originally contain the size of this buffer; on return, it will be set
 * to the size of the value returned. For SO_LINGER, this will be the size of a LINGER structure.
 * For most other options, it will be the size of an integer.
 *
 * The application is responsible for allocating memory space pointed to directly, or indirectly by
 * any parameters it specified.
 *
 * If the option was never set with setsockopt, then getsockopt returns the default value for the
 * option.
 *
 * The following options are supported for getsockopt. The Type column identifies the type of data
 * addressed by optval.
 *
 * level = SOL_SOCKET
 *
 * Value Type Description SO_ACCEPTCONN BOOL Socket is listening. SO_BROADCAST BOOL Socket is
 * configured for the transmission of broadcast messages. SO_DEBUG BOOL Debugging is enabled.
 * SO_DONTLINGER BOOL If TRUE, the SO_LINGER option is disabled. SO_DONTROUTE BOOL Routing is
 * disabled. SO_ERROR int Retrieves error status and clear. SO_GROUP_ID GROUP The group identifier
 * to which this socket belongs. SO_GROUP_PRIORITY int The relative priority for sockets that are
 * part of a socket group. SO_KEEPALIVE BOOL Keepalives are being sent. SO_LINGER struct LINGER
 * Returns the current linger options. SO_MAX_MSG_SIZE unsigned int Maximum size of a message for
 * message-oriented socket types (for example, SOCK_DGRAM). Has no meaning for stream oriented
 * sockets. SO_OOBINLINE BOOL Out-of-band data is being received in the normal data stream.
 * SO_RCVBUF int Buffer size for receives. SO_REUSEADDR BOOL The socket can be bound to an address
 * which is already in use. SO_SNDBUF int Buffer size for sends. SO_TYPE int The socket type (for
 * example, SOCK_STREAM). PVD_CONFIG Service Provider Dependent An opaque data structure object from
 * the service provider associated with socket s. This object stores the current service provider
 * configuration data. The exact format of this data structure is service provider specific.
 *
 * level = IPPROTO_TCP
 *
 * Value Type Description TCP_NODELAY BOOL Disables the Nagle algorithm for send coalescing.
 *
 * BSD options not supported for getsockopt are as follows.
 *
 * Value Type Meaning SO_RCVLOWAT int Receive low water mark. SO_RCVTIMEO int Receive time-out.
 * SO_SNDLOWAT int Send low water mark. SO_SNDTIMEO int Send time-out. TCP_MAXSEG int Get TCP
 * maximum segment size.
 *
 * Calling getsockopt with an unsupported option will result in an error value of WSAENOPROTOOPT
 * being returned by WSAGetLastError.
 *
 * - SO_DEBUG: Windows Sockets service providers are encouraged, but not required, to supply output
 * debug data if the SO_DEBUG option is set by an application. The mechanism for generating the
 * debug data and the form it takes are beyond the scope of this document.
 *
 * - SO_ERROR: The SO_ERROR option returns and resets the per socket based error value, which is
 * different from the per thread based error value that is handled using the WSAGetLastError and
 * WSASetLastError function calls. A successful call using the socket does not reset the socket
 * based error value returned by the SO_ERROR option.
 *
 * - SO_GROUP_ID: This option is reserved for future use with socket groups. This option is also
 * exclusive to getsockopt. It indicates the group identifier to which this socket belongs. Socket
 * group identifiers are unique across all processes for a given service provider. If this socket is
 * not a group socket, the value is NULL.
 *
 * - SO_GROUP_PRIORITY: This option is reserved for future use with socket groups. Group priority
 * indicates the priority of the specified socket relative to other sockets within the socket group.
 * Values are non-negative integers, with zero corresponding to the highest priority. Priority
 * values represent a hint to the underlying service provider about how potentially scarce resources
 * should be allocated. For example, when two or more sockets are ready to transmit data, the
 * highest priority socket (lowest value for SO_GROUP_PRIORITY) should be serviced first, with the
 * remainder serviced in turn according to their relative priorities. The WSAENOPROTOOPT error value
 * is indicated for non group sockets or for service providers that do not support group sockets.
 *
 * - SO_KEEPALIVE: An application can request that a TCP/IP service provider enable the use of
 * keep-alive packets on TCP connections by turning on the SO_KEEPALIVE socket option. A Windows
 * Sockets provider need not support the use of keep-alive: if it does, the precise semantics are
 * implementation-specific but should conform to section 4.2.3.6 of RFC 1122: Requirements for
 * Internet Host-Communication Layers. If a connection is dropped as the result of keep-alives, the
 * error value WSAENETRESET is returned to calls in progress on the socket, and subsequent calls
 * will fail with WSAENOTCONN.
 *
 * - SO_LINGER: SO_LINGER controls the action taken when unsent data is queued on a socket and a
 * closesocket is performed. See closesocket for a description of the way in which the SO_LINGER
 * settings affect the semantics of closesocket. The application gets the current behavior by
 * retrieving a LINGER structure (pointed to by the optval parameter).
 *
 * - SO_MAX_MSG_SIZE: This is a get-only socket option that indicates the maximum outbound (send)
 * size of a message for message-oriented socket types (for example, SOCK_DGRAM) as implemented by a
 * particular service provider. It has no meaning for byte stream oriented sockets. There is no
 * provision to find out the maximum inbound message size.
 *
 * - SO_SNDBUF: When a Windows Sockets implementation supports the SO_RCVBUF and SO_SNDBUF options,
 * an application can request different buffer sizes (larger or smaller). The call to setsockopt can
 * succeed even if the implementation did not provide the whole amount requested. An application
 * must call this function with the same option to check the buffer size actually provided.
 *
 * - SO_REUSEADDR: By default, a socket cannot be bound (see bind) to a local address already in
 * use. On occasion, however, it can be necessary to re-use an address in this way. Because every
 * connection is uniquely identified by the combination of local and remote addresses, there is no
 * problem with having two sockets bound to the same local address as long as the remote addresses
 * are different. To inform the Windows Sockets provider that a bind on a socket should not be
 * rejected because the desired address is already in use by another socket, the application should
 * set the SO_REUSEADDR socket option for the socket before issuing the bind. The option is
 * interpreted only at the time of the bind. It is therefore unnecessary, but harmless, to set the
 * option on a socket that is not to be bound to an existing address, and setting or resetting the
 * option after the bind has no effect on this or any other socket.
 *
 * - PVD_CONFIG: This option retrieves an opaque data structure object from the service provider
 * associated with socket s. This object stores the current service provider configuration data. The
 * exact data structure format is service provider-specific.
 *
 * - TCP_NODELAY
 *
 * The TCP_NODELAY option is specific to TCP/IP service providers. The Nagle algorithm is disabled
 * if the TCP_NODELAY option is enabled, and vice versa. The Nagle algorithm, as described in RFC
 * 896, is very effective in reducing the number of small packets sent by a host. The process
 * involves buffering send data when there is unacknowledged data already in route or buffering send
 * data until a full-size packet can be sent. It is highly recommended that Windows Sockets
 * implementations enable the Nagle Algorithm by default because, for the majority of application
 * protocols, the Nagle Algorithm can deliver significant performance enhancements. However, for
 * some applications this algorithm can impede performance, and setsockopt with the same option can
 * be used to turn it off. These are applications where many small messages are sent, and the time
 * delays between the messages are maintained.
 */
int WINSOCKAPI getsockopt (SOCKET s, int level, int optname,
                           char * optval, int *optlen);

/**
 * This function converts a u_long from host byte order to network byte order.
 *
 * @param hostlong [in] 32-bit number in host byte order.
 *
 * @return The value in TCP/IP's network byte order indicates success.
 *
 * The htonl function takes a 32-bit number in host byte order and returns a 32-bit number in the
 * network byte order used in TCP/IP networks.
 */
u_long WINSOCKAPI htonl (u_long hostlong);

/**
 * This function converts a u_short from host byte order to network byte order.
 *
 * @param hostshort [in] 16-bit number in host byte order.
 *
 * @return The value in TCP/IP network byte order indicates success.
 *
 * The htons function takes a 16-bit number in host byte order and returns a 16-bit number in
 * network byte order used in TCP/IP networks.
 */
u_short WINSOCKAPI htons (u_short hostshort);

/**
 * This function converts a string containing a dotted address into a network address in the format
 * of an IN_ADDR structure.
 *
 * @param cp [in] Null-terminated string that represents a number expressed in the Internet standard
 *   ".'' (dotted) notation.
 *
 * @return An unsigned long value containing a suitable binary representation of the specified
 *   Internet address indicates that no error occurred. INADDR_NONE indicates that the string in the
 *   cp parameter does not contain a legitimate Internet address, for example, if a portion of an
 *   "a.b.c.d" address exceeds 255.
 *
 * The inet_addr function interprets the character string specified by the cp parameter. This string
 * represents a numeric Internet address expressed in the Internet standard ".'' notation. The value
 * returned is a number suitable for use as an Internet address. All Internet addresses are returned
 * in IP's network order (bytes ordered from left to right).
 */
unsigned long WINSOCKAPI inet_addr (const char * cp);

/**
 * This function converts a network address into a string in dotted format.
 *
 * @param in [in] Structure that represents an Internet host address.
 *
 * @return A char pointer to a static buffer containing the text address in standard ".'' notation
 *   indicates that no error occurred. NULL indicates failure.
 *
 * The inet_ntoa function takes an Internet address structure specified by the in parameter and
 * returns an ASCII string representing the address in ".'' (dot) notation as in "a.b.c.d''. The
 * string returned by inet_ntoa resides in memory that is allocated by Windows Sockets. The
 * application should not make any assumptions about the way in which the memory is allocated. The
 * data is guaranteed to be valid until the next Windows Sockets function call within the same
 * thread, but no longer. Therefore, the data should be copied before another Windows Sockets call
 * is made.
 */
char * WINSOCKAPI inet_ntoa (struct in_addr in);

/**
 * This function prepares a socket to listen for incoming connections.
 *
 * @param s [in] Descriptor that identifies a bound, unconnected socket.
 * @param backlog [in] Maximum length of the queue of pending connections. If this value is
 *   SOMAXCONN, then the underlying service provider responsible for socket s will set the backlog to
 *   a maximum reasonable value. There is no standard provision to find out the actual backlog value.
 *
 * @return Zero indicates success. SOCKET_ERROR indicates failure. To get a specific error value,
 *   call WSAGetLastError. As in 4.3BSD, illegal values (less than 1 or greater than 5) are replaced
 *   by the nearest valid value.
 *
 * For Infrared Sockets (IrSock), this function has the following additional requirements and
 * behaviors:
 *
 * The Af_irda.h file must be explicitly included.
 *
 * The WSAENETDOWN return value is not supported.
 *
 * The backlog parameter is currently limited (silently) to 2.
 *
 * To accept connections, a socket is first created with the socket function and bound to a local
 * address with the bind function, a backlog for incoming connections is specified with listen, and
 * then the connections are accepted with the accept function. Sockets that are connection oriented,
 * those of type SOCK_STREAM for example, are used with listen. The socket s is put into "passive''
 * mode where incoming connection requests are acknowledged and queued pending acceptance by the
 * process.
 *
 * The listen function is typically used by servers that can have more than one connection request
 * at a time. If a connection request arrives and the queue is full, the client will receive an
 * error with an indication of WSAECONNREFUSED.
 *
 * If there are no available socket descriptors, listen attempts to continue to function. If
 * descriptors become available, a later call to listen or accept will refill the queue to the
 * current or most recent "backlog'', if possible, and resume listening for incoming connections.
 *
 * An application can call listen more than once on the same socket. This has the effect of updating
 * the current backlog for the listening socket. Should there be more pending connections than the
 * new backlog value, the excess pending connections will be reset and dropped.
 */
int WINSOCKAPI listen (SOCKET s, int backlog);

/**
 * This function converts a u_long from network byte order to host byte order.
 *
 * @param netlong [in] 32-bit number in TCP/IP network byte order.
 *
 * @return The ntohl function always returns a value in host byte order.
 *
 * The ntohl function takes a 32-bit number in TCP/IP network byte order and returns a 32-bit number
 * in host byte order.
 */
u_long WINSOCKAPI ntohl (u_long netlong);

/**
 * This function converts a u_short from network byte order to host byte order.
 *
 * @param netshort [in] 16-bit number in TCP/IP network byte order.
 *
 * @return The ntohs function returns the value in host byte order.
 *
 * The ntohs function takes a 16-bit number in TCP/IP network byte order and returns a 16-bit number
 * in host byte order.
 */
u_short WINSOCKAPI ntohs (u_short netshort);

/**
 * This function receives data from a socket.
 *
 * @param s [in] Descriptor that identifies a connected socket.
 * @param buf [out] Buffer for the incoming data.
 * @param len [in] Length of buf.
 * @param flags [in] Specifies the way in which the call is made.
 *
 * @return Zero indicates that the connection has been gracefully closed. SOCKET_ERROR indicates
 *   failure. To get a specific error value, call WSAGetLastError.
 *
 * The recv function is used to read incoming data on connection-oriented sockets, or connectionless
 * sockets. When using a connection-oriented protocol, the sockets must be connected before calling
 * recv. When using a connectionless protocol, the sockets must be bound and connect must be called
 * to associate the remote address before calling recv.
 *
 * The local address of the socket must be known. For server applications, use an explicit bind
 * function or an implicit accept function. Explicit binding is discouraged for client applications.
 * For client applications the socket can become bound implicitly to a local address using connect
 * or sendto.
 *
 * For connection-oriented or connectionless sockets, this function restricts the addresses from
 * which received messages are accepted. The function only returns messages from the remote address
 * specified in the connection. Messages from other addresses are (silently) discarded.
 *
 * For connection-oriented sockets (type SOCK_STREAM for example), calling recv will return as much
 * information as is currently available-up to the size of the buffer supplied. The application can
 * use the ioctlsocket or WSAIoctl SIOCATMARK command to determine whether any more out-of-band data
 * remains to be read.
 *
 * For connectionless sockets (type SOCK_DGRAM or other message-oriented sockets), data is extracted
 * from the first enqueued datagram (message) from the destination address specified by the connect
 * function.
 *
 * If the datagram or message is larger than the buffer supplied, the buffer is filled with the
 * first part of the datagram, and recv generates the error WSAEMSGSIZE. For unreliable protocols
 * (for example, UDP) the excess data is lost; for reliable protocols, the data is retained by the
 * service provider until it is successfully read by calling recv with a large enough buffer. For
 * TCP/IP, an application cannot receive from any multicast address until after becoming a group
 * member.
 *
 * If no incoming data is available at the socket, the recv call blocks and waits for data to
 * arrive. When the socket is nonblocking, a value of SOCKET_ERROR is returned with the error value
 * set to WSAEWOULDBLOCK. The select function can be used to determine when more data arrives.
 *
 * Any data that has already been received and buffered by the transport will be copied into the
 * supplied user buffers. In the case of a blocking socket with no data currently having been
 * received and buffered by the transport, the call will block until data is received. For protocols
 * acting as byte-stream protocols, the stack tries to return as much data as possible, subject to
 * the supplied buffer space and amount of received data available. However, receipt of a single
 * byte is sufficient to unblock the caller. There is no guarantee that more than a single byte will
 * be returned. For message-oriented protocols, a full message is required to unblock the caller.
 *
 * If the socket is connection oriented and the remote side has shut down the connection gracefully,
 * and all data has been received, a recv will complete immediately with zero bytes received. If the
 * connection has been reset, a recv will fail with the error WSAECONNRESET.
 *
 * The flags parameter can be used to influence the behavior of the function invocation beyond the
 * options specified for the associated socket. The semantics of this function are determined by the
 * socket options and the flags parameter. Windows CE supports the following flags parameter:
 *
 * - MSG_PEEK: Peek at the incoming data. The data is copied into the buffer but is not removed from
 * the input queue. The function then returns the number of bytes currently pending to receive.
 */
int WINSOCKAPI recv (SOCKET s, char * buf, int len, int flags);

/**
 * This function receives a datagram and stores the source address.
 *
 * @param s [in] Descriptor that identifies a bound socket.
 * @param buf [out] Buffer for the incoming data.
 * @param len [in] Length of buf.
 * @param flags [in] Specifies the way in which the call is made.
 * @param from [out] Optional pointer to a buffer that will hold the source address upon return.
 * @param fromlen [in/out] Optional pointer to the size of the from buffer.
 *
 * @return Zero indicates that the connection has been gracefully closed. SOCKET_ERROR indicates
 *   failure. To get a specific error value, call WSAGetLastError.
 *
 * The recvfrom function reads incoming data on both connected and unconnected sockets and captures
 * the address from which the data was sent. The socket must not be connected. The local address of
 * the socket must be known. For server applications, this is usually done explicitly through bind.
 * Explicit binding is discouraged for client applications. For client applications using this
 * function, the socket can become bound implicitly to a local address through sendto.
 *
 * For stream-oriented sockets such as those of type SOCK_STREAM, a call to recvfrom returns as much
 * information as is currently available-up to the size of the buffer supplied. The from and fromlen
 * parameters are ignored for connection-oriented sockets.
 *
 * For message-oriented sockets, data is extracted from the first queued message, up to the size of
 * the buffer supplied. If the datagram or message is larger than the buffer supplied, the buffer is
 * filled with the first part of the datagram, and recvfrom generates the error WSAEMSGSIZE. For
 * unreliable protocols (for example, UDP) the excess data is lost.
 *
 * If the from parameter is nonzero and the socket is not connection oriented, (type SOCK_DGRAM for
 * example), the network address of the peer that sent the data is copied to the corresponding
 * SOCKADDR structure. The value pointed to by fromlen is initialized to the size of this structure
 * and is modified, on return, to indicate the actual size of the address stored in the SOCKADDR
 * structure.
 *
 * If no incoming data is available at the socket, the recvfrom call blocks and waits for data to
 * arrive. When the socket is nonblocking, a value of SOCKET_ERROR is returned with the error value
 * set to WSAEWOULDBLOCK. The select function can be used to determine when more data arrives.
 *
 * Any data that has already been received and buffered by the transport will be copied into the
 * supplied user buffers. In the case of a blocking socket with no data currently having been
 * received and buffered by the transport, the call will block until data is received. For
 * byte-stream protocols, the stack tries to return as much data as possible, subject to the
 * supplied buffer space and amount of received data available. However, receipt of a single byte is
 * sufficient to unblock the caller. There is no guarantee that more than a single byte will be
 * returned. For message-oriented protocols, a full message is required to unblock the caller.
 *
 * If the socket is connection oriented and the remote side has shut down the connection gracefully,
 * the call to recvfrom will complete immediately with zero bytes received. If the connection has
 * been reset recvfrom will fail with the error WSAECONNRESET.
 *
 * The flags parameter can be used to influence the behavior of the function invocation beyond the
 * options specified for the associated socket. The semantics of this function are determined by the
 * socket options and the flags parameter. Windows CE supports the following flags parameter:
 *
 * - MSG_PEEK: Peek at the incoming data. The data is copied into the buffer but is not removed from
 * the input queue. The function then returns the number of bytes currently pending to receive.
 */
int WINSOCKAPI recvfrom (SOCKET s, char * buf, int len, int flags,
                         struct sockaddr *from, int * fromlen);

/**
 * This function determines the status of one or more sockets, waiting if necessary.
 *
 * @param nfds [in] Ignored; included only for compatibility with Berkeley sockets.
 * @param readfds [in/out] Optional pointer to a set of sockets to be checked for readability.
 * @param writefds [in/out] Optional pointer to a set of sockets to be checked for writability
 * @param exceptfds [in/out] Optional pointer to a set of sockets to be checked for errors.
 * @param timeout [in] Maximum time for select to wait. NULL blocks indefinitely.
 *
 * @return Zero indicates that the time limit expired. SOCKET_ERROR indicates failure. To get a
 *   specific error value, call WSAGetLastError.
 *
 * The select function is used to determine the status of one or more sockets. For each socket, the
 * caller can request information on read, write, or error status. The set of sockets for which a
 * given status is requested is indicated by an FD_SET structure. The sockets contained within the
 * FD_SET structures must be associated with a single service provider. The select function returns
 * the number of sockets meeting the conditions. A set of macros is provided for manipulating an
 * FD_SET structure. These macros are compatible with those used in the Berkeley software, but the
 * underlying representation is completely different.
 *
 * The parameter readfds identifies the sockets that are to be checked for readability. If the
 * socket is currently in the listen state, it will be marked as readable if an incoming connection
 * request has been received such that an accept is guaranteed to complete without blocking. For
 * other sockets, readability means that queued data is available for reading such that a call to
 * recv or recvfrom is guaranteed not to block.
 *
 * For connection-oriented sockets, readability can also indicate that a request to close the socket
 * has been received from the peer. If the virtual circuit was closed gracefully, and all data was
 * received, then a recv will return immediately with zero bytes read. If the virtual circuit was
 * reset, then a recv will complete immediately with an error value such as WSAECONNRESET.
 *
 * The parameter writefds identifies the sockets that are to be checked for writability. If a socket
 * is processing a connect call (nonblocking), a socket is writable if the connection establishment
 * successfully completes. If the socket is not processing a connect call, writability means a send
 * or sendto are guaranteed to succeed. However, they can block on a blocking socket if the len
 * parameter exceeds the amount of outgoing system buffer space available. It is not specified how
 * long these guarantees can be assumed to be valid, particularly in a multithreaded environment.
 *
 * The parameter exceptfds identifies the sockets that are to be checked for the presence of any
 * exceptional error conditions.
 *
 * Any two of the parameters, readfds, writefds, or exceptfds, can be given as NULL. At least one
 * must be non-NULL, and any non-NULL descriptor set must contain at least one handle to a socket.
 *
 * Summary: A socket will be identified in a particular set when select returns if:
 *
 * readfds:
 *
 * If listen has been called and a connection is pending, accept will succeed
 *
 * Connection has been closed/reset/terminated
 *
 * writefds:
 *
 * If processing a connect call (nonblocking), connection has succeeded
 *
 * Data can be sent
 *
 * exceptfds:
 *
 * If processing a connect call (nonblocking), connection attempt failed
 *
 * Four macros are defined in the header file Winsock.h for manipulating and checking the descriptor
 * sets. The variable FD_SETSIZE determines the maximum number of descriptors in a set. (The default
 * value of FD_SETSIZE is 64, which can be modified by defining FD_SETSIZE to another value before
 * including Winsock.h.) Internally, socket handles in an FD_SET structure are not represented as
 * bit flags as in Berkeley Unix. Their data representation is opaque. Use of these macros will
 * maintain software portability between different socket environments. The macros to manipulate and
 * check FD_SET contents are:
 *
 * - FD_CLR(s, *set): Removes the descriptor s from set.
 *
 * - FD_ISSET(s, *set): Nonzero if s is a member of the set. Otherwise, zero.
 *
 * - FD_SET(s, *set): Adds descriptor s to set.
 *
 * - FD_ZERO(*set): Initializes the set to the NULL set.
 *
 * The parameter time-out controls how long the select can take to complete. If time-out is a null
 * pointer, select will block indefinitely until at least one descriptor meets the specified
 * criteria. Otherwise, time-out points to a TIMEVAL structure that specifies the maximum time that
 * select should wait before returning. When select returns, the contents of the TIMEVAL structure
 * are not altered. If TIMEVAL is initialized to {0, 0}, select will return immediately; this is
 * used to poll the state of the selected sockets. If select returns immediately, then the select
 * call is considered nonblocking and the standard assumptions for nonblocking calls apply.
 */
int WINSOCKAPI select (int nfds, fd_set *readfds, fd_set *writefds,
                       fd_set *exceptfds, const struct timeval *timeout);

/**
 * This function sends data on a connected socket.
 *
 * @param s [in] Descriptor that identifies a connected socket.
 * @param buf [in] Buffer containing the data to be transmitted.
 * @param len [in] Length of the data in buf.
 * @param flags [in] Specifies the way in which the call is made.
 *
 * @return The total number of bytes sent, which can be less than the number indicated by len for
 *   nonblocking sockets, indicates that no errors occurred. SOCKET_ERROR indicates failure. To get a
 *   specific error value, call WSAGetLastError.
 *
 * For Infrared Sockets (IrSock), the Af_irda.h file must be explicitly included.
 *
 * The send function is used to write outgoing data on a connected socket. For message-oriented
 * sockets, care must be taken not to exceed the maximum packet size of the underlying provider,
 * which can be obtained by using getsockopt to retrieve the value of socket option SO_MAX_MSG_SIZE.
 * If the data is too long to pass atomically through the underlying protocol, the error WSAEMSGSIZE
 * is returned, and no data is transmitted.
 *
 * The successful completion of a send does not indicate that the data was successfully delivered.
 *
 * If no buffer space is available within the transport system to hold the data to be transmitted,
 * send will block unless the socket has been placed in a nonblocking mode. On nonblocking stream
 * oriented sockets, the number of bytes written can be between 1 and the requested length,
 * depending on buffer availability on both client and server machines. The select function can be
 * used to determine when it is possible to send more data.
 *
 * Calling send with a zero len parameter is permissible and will be treated by implementations as
 * successful. In such cases, send will return zero as a valid value. For message-oriented sockets,
 * a zero-length transport datagram is sent.
 *
 * The flags parameter can be used to influence the behavior of the function beyond the options
 * specified for the associated socket. The semantics of this function are determined by the socket
 * options and the flags parameter. Windows CE supports the following flags parameter:
 *
 * - MSG_DONTROUTE: Specifies that the data should not be subject to routing. A Windows Sockets
 * service provider can choose to ignore this flag.
 */
int WINSOCKAPI send (SOCKET s, const char * buf, int len, int flags);

/**
 * This function sends data to a specific destination.
 *
 * @param s [in] Descriptor that identifies a (possibly connected) socket.
 * @param buf [in] Buffer that contains the data to be transmitted.
 * @param len [in] Length of the data in buf.
 * @param flags [in] Specifies the way in which the call is made.
 * @param to [in] Optional pointer to the address of the target socket.
 * @param tolen [in] Size of the address in to.
 *
 * @return The total number of bytes sent, which can be less than the number indicated by len,
 *   indicates that no error occurred. SOCKET_ERROR indicates failure. To get a specific error value,
 *   call WSAGetLastError.
 *
 * The sendto function is used to write outgoing data on a socket. For message-oriented sockets,
 * care must be taken not to exceed the maximum packet size of the underlying subnets, which can be
 * obtained by using getsockopt to retrieve the value of socket option SO_MAX_MSG_SIZE. If the data
 * is too long to pass atomically through the underlying protocol, the error WSAEMSGSIZE is returned
 * and no data is transmitted.
 *
 * The to parameter can be any valid address in the socket's address family, including a broadcast
 * or any multicast address. To send to a broadcast address, an application must have used
 * setsockopt with SO_BROADCAST enabled. Otherwise, sendto will fail with the error value WSAEACCES.
 * For TCP/IP, an application can send to any multicast address (without becoming a group member).
 *
 * If the socket is unbound, unique values are assigned to the local association by the system, and
 * the socket is then marked as bound. An application can use getsockname to determine the local
 * socket name in this case.
 *
 * The successful completion of a sendto does not indicate that the data was successfully delivered.
 *
 * The sendto function is normally used on a connectionless socket to send a datagram to a specific
 * peer socket identified by the to parameter. Even if the connectionless socket has been previously
 * connected to a specific address, the to parameter overrides the destination address for that
 * particular datagram only. On a connection-oriented socket, the to and tolen parameters are
 * ignored, making sendto equivalent to send.
 *
 * For Sockets Using IP (Version 4)
 *
 * To send a broadcast (on a SOCK_DGRAM only), the address in the to parameter should be constructed
 * using the special IP address INADDR_BROADCAST (defined in Winsock.h), together with the intended
 * port number. It is generally inadvisable for a broadcast datagram to exceed the size at which
 * fragmentation can occur, which implies that the data portion of the datagram (excluding headers)
 * should not exceed 512 bytes.
 *
 * If no buffer space is available within the transport system to hold the data to be transmitted,
 * sendto will block unless the socket has been placed in a nonblocking mode. On nonblocking, stream
 * oriented sockets, the number of bytes written can be between 1 and the requested length,
 * depending on buffer availability on both the client and server systems. The select function can
 * be used to determine when it is possible to send more data.
 *
 * Calling sendto with a len of zero is permissible and will return zero as a valid value. For
 * message-oriented sockets, a zero-length transport datagram is sent.
 *
 * The flags parameter can be used to influence the behavior of the function invocation beyond the
 * options specified for the associated socket. The semantics of this function are determined by the
 * socket options and the flags parameter. Windows CE supports the following flags parameter:
 *
 * - MSG_DONTROUTE: Specifies that the data should not be subject to routing. A Windows Sockets
 * service provider can choose to ignore this flag.
 */
int WINSOCKAPI sendto (SOCKET s, const char * buf, int len, int flags,
                       const struct sockaddr *to, int tolen);

/**
 * This function sets a socket option.
 *
 * @param s [in] Descriptor that identifies a socket.
 * @param level [in] Level at which the option is defined; the supported levels include SOL_SOCKET,
 *   IPPROTO_TCP, and IPPROTO_IP. When the level is IPPROTO_IP, the following IP_OPTIONS values are
 *   available: Value Description IP_MULTICAST_TTL Time-to-live for a multicast packet. Specifies the
 *   maximum number of hops for which a multicast message survives before it is discarded. Use int for
 *   optval. IP_MULTICAST_IF Address of the outgoing multicast-capable interface. This address is used
 *   for subsequent multicasts. Use unsigned long for optval. IP_ADD_MEMBERSHIP The membership request
 *   structure used to request a particular multicast group's membership. Use struct ip_mreq for
 *   optval. IP_DROP_MEMBERSHIP The group whose membership is to be used. Use struct ip_mreq for
 *   optval.
 * @param optname [in] Socket option for which the value is to be set.
 * @param optval [in] Pointer to the buffer in which the value for the requested option is supplied.
 * @param optlen [in] Size of the optval buffer.
 *
 * @return Zero indicates that no error occurred. SOCKET_ERROR indicates failure. To get a specific
 *   error value, call WSAGetLastError. The setsockopt function can also return the following error
 *   values: - WSAENOBUFS: No buffer space available. An operation on a socket could not be performed
 *   because the system lacked sufficient buffer space or because a queue was full. - WSAEOPNOTSUPP:
 *   The option is not supported. - WSANOTINITIALISED: A successful WSAStartup call must occur before
 *   using this function. - WSAENETDOWN: The network subsystem has failed. This value is not supported
 *   for IrSockets. - WSAEFAULT: The optval parameter is not in a valid part of the process address
 *   space or the optlen parameter is too small. - WSAEISCONN: The socket could not switch to secure
 *   mode when it connected. - WSAEINPROGRESS: A blocking Windows Sockets 1.1 call is in progress, or
 *   the service provider is still processing a callback function. - WSAEINVAL: The level parameter is
 *   not valid, or the information in optval is not valid. - WSAENETRESET: The connection has timed
 *   out when SO_KEEPALIVE is set. - WSAENOPROTOOPT: The option is unknown or unsupported for the
 *   specified provider or socket (see SO_GROUP_PRIORITY limitations). When used in the context of
 *   SSL, this error value indicates that the option level is not equal to SO_SOCKET. - WSAENOTCONN:
 *   The connection has been reset when SO_KEEPALIVE is set. - WSAENOTSOCK: The descriptor is not a
 *   socket.
 *
 * The setsockopt function sets the current value for a socket option associated with a socket of
 * any type, in any state. Although options can exist at multiple protocol levels, they are always
 * present at the uppermost "socket" level. Options affect socket operations, such as whether
 * expedited data (OOB data for example) is received in the normal data stream, and whether
 * broadcast messages can be sent on the socket.
 *
 * There are two types of socket options: Boolean options that enable or disable a feature or
 * behavior, and options that require an integer value or structure. To enable a Boolean option,
 * optval points to a nonzero integer. To disable the option optval points to an integer equal to
 * zero. The optlen parameter should be equal to sizeof(int) for Boolean options. For other options,
 * optval points to the an integer or structure that contains the desired value for the option, and
 * optlen is the length of the integer or structure.
 *
 * The following options are supported for setsockopt. For default values of these options, see the
 * description. The Type identifies the type of data addressed by optval.
 *
 * level = SOL_SOCKET
 *
 * Value Type Description SO_BROADCAST BOOL Allow transmission of broadcast messages on the socket.
 * SO_DONTLINGER BOOL Do not block close waiting for unsent data to be sent. Setting this option is
 * equivalent to setting SO_LINGER with l_onoff set to zero. SO_DONTROUTE BOOL Do not route: send
 * directly to interface. SO_GROUP_PRIORITY int Reserved for future use with socket groups. Specify
 * the relative priority to be established for sockets that are part of a socket group. SO_KEEPALIVE
 * BOOL Send keepalives SO_LINGER struct LINGER Linger on close if unsent data is present.
 * SO_REUSEADDR BOOL Allow the socket to be bound to an address that is already in use. (See bind.)
 * SO_SNDBUF int Specify the total per-socket buffer space reserved for sends. This is unrelated to
 * SO_MAX_MSG_SIZE or the size of a TCP window.
 *
 * level = IPPROTO_TCP
 *
 * Value Type Description TCP_NODELAY BOOL Disables the Nagle algorithm for send coalescing.
 *
 * BSD options not supported for setsockopt are:
 *
 * Value Type Meaning SO_ACCEPTCONN BOOL Socket is listening SO_RCVLOWAT int Receive low water mark
 * SO_SNDLOWAT int Send low water mark SO_SNDTIMEO int Send time-out SO_TYPE int Type of the socket
 *
 * - SO_GROUP_PRIORITY: Reserved for future use with socket groups. Group priority indicates the
 * relative priority of the specified socket relative to other sockets within the socket group.
 * Values are non-negative integers, with zero corresponding to the highest priority. Priority
 * values represent a hint to the underlying service provider about how potentially scarce resources
 * should be allocated. For example, whenever two or more sockets are both ready to transmit data,
 * the highest priority socket (lowest value for SO_GROUP_PRIORITY) should be serviced first with
 * the remainder serviced in turn according to their relative priorities. The WSAENOPROTOOPT error
 * is indicated for nongroup sockets or for service providers that do not support group sockets.
 *
 * - SO_KEEPALIVE: An application can request that a TCP/IP provider enable the use of "keep-alive"
 * packets on TCP connections by turning on the SO_KEEPALIVE socket option. A Windows Sockets
 * provider need not support the use of keep-alives. If it does, the precise semantics are
 * implementation-specific but should conform to section 4.2.3.6 of RFC 1122: Requirements for
 * Internet Hosts-Communication Layers. If a connection is dropped as the result of "keep-alives"
 * the error value WSAENETRESET is returned to any calls in progress on the socket, and any
 * subsequent calls will fail with WSAENOTCONN.
 *
 * - SO_LINGER: The SO_LINGER option controls the action taken when unsent data is queued on a
 * socket and a closesocket is performed. See closesocket for a description of the way in which the
 * SO_LINGER settings affect the semantics of closesocket. The application sets the desired behavior
 * by creating a LINGER structure (pointed to by the optval parameter) with these members l_onoff
 * and l_linger set appropriately.
 *
 * - SO_REUSEADDR: By default, a socket cannot be bound (see bind) to a local address that is
 * already in use. On occasion, however, it can be necessary to "re-use" an address in this way.
 * Since every connection is uniquely identified by the combination of local and remote addresses,
 * there is no problem with having two sockets bound to the same local address as long as the remote
 * addresses are different. To inform the Windows Sockets provider that a bind on a socket should
 * not be disallowed because the desired address is already in use by another socket, the
 * application should set the SO_REUSEADDR socket option for the socket before issuing the bind. The
 * option is interpreted only at the time of the bind. It is therefore unnecessary and harmless to
 * set the option on a socket that is not to be bound to an existing address. Setting or resetting
 * the option after the bind has no effect on this or any other socket.
 *
 * - SO_SNDBUF: When a Windows Sockets implementation supports the SO_SNDBUF option, an application
 * can request different buffer sizes (larger or smaller). The call to setsockopt can succeed even
 * when the implementation did not provide the whole amount requested. An application must call
 * getsockopt with the same option to check the buffer size actually provided.
 *
 * - TCP_NODELAY: The TCP_NODELAY option is specific to TCP/IP service providers. The Nagle
 * algorithm is disabled if the TCP_NODELAY option is enabled (and vice versa). The process involves
 * buffering send data when there is unacknowledged data already "in flight" or buffering send data
 * until a full-size packet can be sent. It is highly recommended that TCP/IP service providers
 * enable the Nagle Algorithm by default, and for the vast majority of application protocols the
 * Nagle Algorithm can deliver significant performance enhancements. However, for some applications
 * this algorithm can impede performance, and TCP_NODELAY can be used to turn it off. These are
 * applications where many small messages are sent, and the time delays between the messages are
 * maintained. Application writers should not set TCP_NODELAY unless the impact of doing so is
 * well-understood and desired because setting TCP_NODELAY can have a significant negative impact on
 * network and application performance.
 *
 * To set a socket to secure mode, the option level parameter, level, must set to SO_SOCKET, the
 * option name, optname to SO_SECURE, and the option value, optval, must be a pointer to a DWORD
 * containing SO_SEC_SSL. These settings ensure that the Unified Secure Sockets Layer (SSL) package
 * be used. The following code example shows how to set a socket to secure mode.
 *
 *     DWORD optval = SO_SEC_SSL;
 *     err = setsockopt(
 *         Socket,
 *         SOL_SOCKET,
 *         SO_SECURE,
 *         &optval,
 *         sizeof(optval)
 *         );.
 *
 * For Infrared Sockets (IrSock), Af_irda.h must be explicitly included.
 *
 * IrSock provides two settable socket options:
 *
 * Value Type Meaning IRLMP_IAS_SET * IAS_SET Sets IAS attributes. IRLMP_IRLPT_MODE * int In
 * non-zero, enables IrLPT mode for printing to IrDA printers.
 *
 * The IRLMP_IAS_SET socket option allows the application to set a single attribute of a single
 * class in the local IAS. The application specifies the class to set and the attribute and
 * attribute type. The maximum length of an attribute name is 60 characters however, regardless of
 * the set value for characters beyond the 60th, Windows CE will set these to NULL. That is, these
 * two arrays will be truncated at 60 characters.
 *
 * The IRLMP_RAW_MODE socket option allows the application to switch between TinyTP mode and
 * unreliable IrLMP mode. If it is not set, IrSockets are assumed to use TinyTP. This option is only
 * available after issuing the socket function and before issuing any other Windows Sockets
 * function.
 *
 * Many SO_ level socket options are not meaningful to IrSockets. Only SO_LINGER is specifically
 * supported.
 */
int WINSOCKAPI setsockopt (SOCKET s, int level, int optname,
                           const char * optval, int optlen);

/**
 * This function disables send or receive operations on a socket. It does not release any system
 * resources used by the socket.
 *
 * @param s [in] Descriptor that identifies a socket.
 * @param how [in] Flag that describes what types of operation will no longer be allowed.
 *
 * @return Zero indicates that no error occurred. SOCKET_ERROR indicates failure. To get a specific
 *   error value, call WSAGetLastError.
 *
 * The shutdown function is used on all types of sockets to disable reception, transmission, or
 * both.
 *
 * If the how parameter is SD_RECEIVE, subsequent calls to the recv function on the socket will be
 * disallowed. This has no effect on the lower protocol layers. For TCP sockets, if there is still
 * data queued on the socket waiting to be received, or data arrives subsequently, the connection is
 * reset, since the data cannot be delivered to the user. For UDP sockets, incoming datagrams are
 * accepted and queued. In no case will an ICMP error packet be generated.
 *
 * If the how parameter is SD_SEND, subsequent calls to the send function are disallowed. For TCP
 * sockets, a FIN will be sent after all data is sent and acknowledged by the receiver.
 *
 * Setting how to SD_BOTH disables both sends and receives as described above.
 *
 * The shutdown function does not close the socket. Any resources attached to the socket will not be
 * freed until closesocket is invoked.
 *
 * Note The shutdown function does not block regardless of the SO_LINGER setting on the socket.
 *
 * An application should not rely on being able to re-use a socket after it has been shut down. In
 * particular, a Windows Sockets provider is not required to support the use of connect on a socket
 * that has been shutdown.
 */
int WINSOCKAPI shutdown (SOCKET s, int how);

/**
 * This function creates a socket.
 *
 * @param af [in] Address family specification.
 * @param type [in] Type specification for the new socket. The following are the only two type
 *   specifications supported for Windows Sockets 1.1: Value Description SOCK_STREAM Provides
 *   sequenced, reliable, two-way, connection-based byte streams with an out-of-band data transmission
 *   mechanism. Uses TCP for the Internet address family. SOCK_DGRAM Supports datagrams, which are
 *   connectionless, unreliable buffers of a fixed (typically small) maximum length. Uses UDP for the
 *   Internet address family.
 * @param protocol [in] Particular protocol to be used with the socket that is specific to the
 *   indicated address family.
 *
 * @return A descriptor referencing the new socket indicates that no error occurred. INVALID_SOCKET
 *   indicates failure. To get a specific error value, call WSAGetLastError.
 *
 * For Infrared Sockets (IrSock), this function has the following additional requirements:
 *
 * Af_irda.h must be explicitly included.
 *
 * Set the af parameter to AF_IRDA, and set the protocol parameter to NULL.
 *
 * The PF_INET and AF_IRDA ARPA Internet address formats are supported.
 *
 * The socket function causes a socket descriptor and any related resources to be allocated and
 * bound to a specific transport service provider. Windows Sockets will utilize the first available
 * service provider that supports the requested combination of address family, socket type and
 * protocol parameters.
 *
 * Connection-oriented sockets such as SOCK_STREAM provide full-duplex connections, and must be in a
 * connected state before any data can be sent or received on it. A connection to another socket is
 * created with a connect call. Once connected, data can be transferred using send and recv calls.
 * When a session has been completed, a closesocket must be performed.
 *
 * The communications protocols used to implement a reliable, connection-oriented socket ensure that
 * data is not lost or duplicated. If data for which the peer protocol has buffer space cannot be
 * successfully transmitted within a reasonable length of time, the connection is considered broken
 * and subsequent calls will fail with the error value set to WSAETIMEDOUT.
 *
 * Connectionless, message-oriented sockets allow sending and receiving of datagrams to and from
 * arbitrary peers using sendto and recvfrom. If such a socket is connected to a specific peer,
 * datagrams can be sent to that peer using send and can be received only from this peer using recv.
 */
SOCKET WINSOCKAPI socket (int af, int type, int protocol);

/* Database function prototypes */

/**
 * This function retrieves the host data corresponding to a network address.
 *
 * @param addr [in] Pointer to an address in network byte order.
 * @param len [in] Address length.
 * @param type [in] Address type.
 *
 * @return A pointer to the HOSTENT structure indicates no error occurred. A NULL pointer indicates
 *   failure. To get a specific error value, call the WSAGetLastError function.
 *
 * The gethostbyaddr function returns a pointer to the HOSTENT structure that contains the name and
 * address corresponding to the given network address. All strings are null-terminated.
 */
struct hostent * WINSOCKAPI gethostbyaddr(const char * addr,
                                              int len, int type);

/**
 * This function gets host data corresponding to a host name.
 *
 * @param name [out] Pointer to the null-terminated string that contains the host name to resolve.
 *
 * @return A pointer to the HOSTENT structure indicates no error occurred. A NULL pointer indicates
 *   failure. To get a specific error value, call WSAGetLastError.
 *
 * The gethostbyname function returns a pointer to a HOSTENT structure-a structure allocated by
 * Windows Sockets. The HOSTENT structure contains the results of a successful search for the host
 * specified in the name parameter.
 *
 * The application must never attempt to modify this structure, or to free any of its components.
 * Furthermore, only one copy of this structure is allocated per thread, so the application should
 * copy data it needs before issuing other Windows Sockets function calls.
 *
 * The gethostbyname function cannot resolve IP address strings passed to it. Such a request is
 * treated exactly as if an unknown host name were passed. Use inet_addr to convert an IP address
 * string the string to an actual IP address, then use another function, gethostbyaddr, to obtain
 * the contents of the HOSTENT structure.
 *
 * The gethostbyname function resolves the string returned by a successful call to gethostname.
 *
 * Note Japanese Version Winsock calls to get the machine IP address will fail if the machine name
 * is entered in Japanese characters.
 */
struct hostent * WINSOCKAPI gethostbyname(const char * name);

/**
 * This function returns the standard host name for the local computer.
 *
 * @param name [out] Pointer to a buffer that receives the local host name.
 * @param namelen [in] Buffer length.
 *
 * @return Zero indicates no error occurred. SOCKET_ERROR indicates failure. To get a specific error
 *   value, call WSAGetLastError.
 *
 * The gethostname function returns the local host name into the buffer specified by the name
 * parameter. The host name is returned as a null-terminated string. The host name form is dependent
 * on the Windows Sockets provider-it can be a simple host name, or it can be a fully qualified
 * domain name. However, it is guaranteed that the name returned will be successfully parsed by
 * gethostbyname.
 *
 * Note If no local host name has been configured, gethostname must succeed and return a token host
 * name that gethostbyname can resolve.
 */
int WINSOCKAPI gethostname (char * name, int namelen);

/* Microsoft Windows Extension function prototypes */
/**
 * This function initializes a WSADATA structure.
 *
 * @param wVersionRequested [in] Specifies the highest version of Windows Sockets support that the
 *   caller can use. The high order byte specifies the minor version (revision) number; the low-order
 *   byte specifies the major version number.
 * @param lpWSAData [out] Long pointer to the WSADATA data structure that is to receive details of
 *   the Windows Sockets implementation.
 *
 * @return Zero indicates success. To get a specific error value, call WSAGetLastError. The
 *   following table shows possible error values. Value Meaning WSASYSNOTREADY The underlying network
 *   subsystem is not ready for network communication. WSAVERNOTSUPPORTED The version of Windows
 *   Sockets support requested is not provided by this particular Windows Sockets implementation.
 *   WSAEINPROGRESS A blocking Windows Sockets 1.1 operation is in progress. WSAEPROCLIM The limit on
 *   the number of tasks supported by the Windows Sockets implementation has been reached. WSAEFAULT
 *   The lpWSAData is not a valid pointer. An application cannot call WSAGetLastError to determine the
 *   error value as is normally done in Windows Sockets is WSAStartup fails. The Winsock.dll will not
 *   have been loaded in the case of a failure so the client data area where the "last error"
 *   information is stored could not be established.
 *
 * The WSAStartup function must be the first Windows Sockets function called by an application or
 * DLL. It allows an application or DLL to specify the version of Windows Sockets required and to
 * retrieve details of the specific Windows Sockets implementation. The application or DLL can only
 * issue further Windows Sockets functions after a successfully calling WSAStartup.
 *
 * To support future Windows Sockets implementations and applications that can have functionality
 * differences from current version of Windows Sockets, a negotiation takes place in WSAStartup. The
 * caller of WSAStartup and the Winsock.dll indicate to each other the highest version that they can
 * support, and each confirms that the other's highest version is acceptable. Upon entry to
 * WSAStartup, the Winsock.dll examines the version requested by the application. If this version is
 * equal to or higher than the lowest version supported by the DLL, the call succeeds and the DLL
 * returns in wHighVersion the highest version it supports and in wVersion the minimum of its high
 * version and wVersionRequested. The Winsock.dll then assumes that the application will use
 * wVersion. If the wVersion field of the WSADATA structure is unacceptable to the caller, it should
 * call WSACleanup and either search for another Winsock.dll or fail to initialize.
 *
 * It is legal and possible for an application written to this version of the specification to
 * successfully negotiate a higher version number than the version of this specification. In such a
 * case, the application is only guaranteed access to higher-version functionality that fits within
 * the syntax defined in this version, such as new Ioctl codes and new behavior of existing
 * functions. New functions, for example, may be inaccessible. To be guaranteed full access to new
 * syntax of a future version, the application must fully conform to that future version, such as
 * compiling against a new header file, linking to a new library, or other special cases.
 *
 * This negotiation allows both a Winsock.dll and a Windows Sockets application to support a range
 * of Windows Sockets versions. An application can use Winsock.dll if there is any overlap in the
 * version ranges. The following chart gives examples of how WSAStartup works in conjunction with
 * different application and Winsock.dll versions:
 *
 * App versions DLL versions wVersion requested wVersion wHigh version End result 1.1 1.1 1.1 1.1
 * 1.1 use 1.1 1.0 1.1 1.0 1.1 1.0 1.0 use 1.0 1.0 1.0 1.1 1.0 1.0 1.1 use 1.0 1.1 1.0 1.1 1.1 1.1
 * 1.1 use 1.1 1.1 1.0 1.1 1.0 1.0 Application fails 1.0 1.1 1.0 --- --- WSAVERNOT SUPPORTED 1.0 1.1
 * 1.0 1.1 1.1 1.1 1.1 use 1.1 1.1 2.0 1.1 2.0 1.1 1.1 use 1.1
 *
 * The following code example demonstrates how an application that supports only version 1.1 of
 * Windows Sockets makes a WSAStartup call:
 *
 *     WORD wVersionRequested;
 *     WSADATA wsaData;
 *     int err;
 *
 *     wVersionRequested = MAKEWORD( 1, 1 );
 *
 *     err = WSAStartup( wVersionRequested, &wsaData );
 *     if ( err != 0 ) {
 *      / * Tell the user that we could not find a usable * /
 *      / * WinSock DLL.   * /
 *      return;
 *     }
 *
 *     / * Confirm that the WinSock DLL supports 1.1.* /
 *     / * Note that if the DLL supports versions greater * /
 *     / * than 1.1 in addition to 1.1, it will still return * /
 *     / * 1.1 in wVersion since that is the version we * /
 *     / * requested.   * /
 *
 *     if ( LOBYTE( wsaData.wVersion ) != 1 ||
 *      HIBYTE( wsaData.wVersion ) != 1 ) {
 *      / * Tell the user that we could not find a usable * /
 *      / * WinSock DLL.   * /
 *      WSACleanup( );
 *      return;
 *     }
 *
 *     / * The WinSock DLL is acceptable. Proceed. * /
 *
 * Once an application or DLL has made a successful WSAStartup call, it can proceed to make other
 * Windows Sockets calls as needed. When it has finished using the services of the Winsock.dll, the
 * application or DLL must call WSACleanup to allow the Winsock.dll to free any resources for the
 * application.
 *
 * Details of the actual Windows Sockets implementation are described in the WSADATA structure.
 *
 * An application or DLL can call WSAStartup more than once if it needs to obtain the WSAData
 * structure information more than once. On each such call the application can specify any version
 * number supported by the DLL.
 *
 * An application must call one WSACleanup call for every successful WSAStartup call to allow
 * third-party DLLs to make use of a Winsock.dllon behalf of an application. This means, for
 * example, that if an application calls WSAStartup three times, it must call WSACleanup three
 * times. The first two calls to WSACleanup do nothing except decrement an internal counter; the
 * final WSACleanup call for the task does all necessary resource deallocation for the task.
 */
#define WSAStartup(wVersionRequired,lpWSAData)	\
		((lpWSAData)->wVersion=wVersionRequired,\
		(lpWSAData)->wHighVersion=wVersionRequired,\
		(lpWSAData)->szDescription[0]='\0',\
		(lpWSAData)->szSystemStatus[0]='\0',\
		(lpWSAData)->iMaxSockets=10,\
		(lpWSAData)->iMaxUdpDg=0,\
		(lpWSAData)->lpVendorInfo=NULL,(0))

/**
 * This function terminates the use of Winsock.dll.
 *
 * @return Zero indicates success. SOCKET_ERROR indicates failure. To get a specific error value,
 *   call WSAGetLastError. In a multithreaded environment, WSACleanup terminates Windows Sockets
 *   operations for all threads.
 *
 * This function initiates no action and is provided only for compatibility reasons.
 *
 * An application or DLL is required to perform a successful WSAStartup call before it can use
 * Windows Sockets services. When it has completed the use of Windows Sockets, the application or
 * DLL must call WSACleanup to deregister itself from a Windows Sockets implementation and allow the
 * implementation to free any resources allocated on behalf of the application or DLL.
 *
 * Sockets that were open when WSACleanup was called are reset and automatically deallocated as if
 * closesocket were called; sockets that have been closed with closesocket but that still have
 * pending data to be sent can be affected-the pending data can be lost if the Winsock.dll is
 * unloaded from memory as the application exits. To insure that all pending data is sent, an
 * application should use shutdown to close the connection, then wait until the close completes
 * before calling closesocket and WSACleanup. All resources and internal state, such as queued
 * un-posted messages, must be deallocated so as to be available to the next user.
 *
 * There must be a call to WSACleanup for every successful call to WSAStartup made by a task. Only
 * the final WSACleanup for that task does the actual cleanup; the preceding calls simply decrement
 * an internal reference count in the Winsock.dll.
 */
#define WSACleanup()			(0)

/**
 * This function sets the error value that can be retrieved through the WSAGetLastError function.
 *
 * @param iError [in] Integer that specifies the error value to be returned by a subsequent
 *   WSAGetLastError call.
 *
 * @return None.
 *
 * The WSASetLastError function allows an application to set the error value to be returned by a
 * subsequent WSAGetLastError call for the current thread. Note that any subsequent Windows Sockets
 * routine called by the application will override the error value as set by this routine.
 *
 * The error value set by WSASetLastError is different from the error value reset by calling the
 * function getsockopt with SO_ERROR.
 */
#define WSASetLastError(iError)		SetLastError(iError)

/**
 * This function retrieves the error status for the last Windows Socket operation that failed.
 *
 * @return The return value indicates the error value for this thread's last Windows Sockets
 *   operation that failed.
 *
 * The WSAGetLastError function returns the last network error that occurred. When a particular
 * Windows Sockets function indicates that an error has occurred, this function should be called to
 * retrieve the appropriate error value. This error value can be different from the error value
 * obtained from getsockopt SO_ERROR, which is socket-specific since WSAGetLastError is for all
 * thread-specific sockets.
 *
 * A successful function call, or a call to WSAGetLastError, does not reset the error value. To
 * reset the error value, use the WSASetLastError function call with iError set to zero. A
 * getsockopt SO_ERROR also resets the error value to zero.
 */
#define WSAGetLastError()		GetLastError()

/**
 * This function controls the mode of a socket.
 *
 * @param s [in] Descriptor that identifies a socket.
 * @param dwIoControlCode [in] Specifies the control code of operation to perform.
 * @param lpvInBuffer [in] Long void pointer to the input buffer.
 * @param cbInBuffer [in] Number that indicates the size of the input buffer.
 * @param lpvOutBuffer [out] Long void pointer to the output buffer.
 * @param cbOutBuffer [in] Number that indicates the size of the output buffer.
 * @param lpcbBytesReturned [out] For secure sockets, long pointer to the number of bytes returned
 *   in the output buffer.
 * @param lpOverlapped [in] Unsupported; set to NULL.
 * @param lpCompletionRoutine [in] Unsupported; set to NULL.
 *
 * @return Zero indicates success. SOCKET_ERROR indicates failure. To get a specific error value,
 *   call WSAGetLastError.
 *
 * The WSAIoctl function is used to set or retrieve operating parameters associated with the socket,
 * the transport protocol, or the communications subsystem.
 *
 * It is possible to adopt an encoding scheme that preserves the currently defined ioctlsocket
 * opcodes while providing a convenient way to partition the opcode identifier space in as much as
 * the dwIoControlCode parameter is now a 32-bit entity. The dwIoControlCode parameter is designed
 * to allow for protocol and vendor independence when adding new control codes while retaining
 * backward compatibility with the Windows Sockets 1.1 and Unix control codes. The dwIoControlCode
 * parameter has the following form:
 *
 * 3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5
 * 4 3 2 1 0 I O V T Vendor/Address Family Code
 *
 * I is set if the input buffer is valid for the code, as with IOC_IN.
 *
 * O is set if the output buffer is valid for the code, as with IOC_OUT. Codes with both input and
 * output parameters set both I and O.
 *
 * V is set if there are no parameters for the code, as with IOC_VOID.
 *
 * T is a two-bit quantity that defines the type of ioctl. The following values are defined:
 *
 * 0 - The ioctl is a standard Unix ioctl code, as with FIONREAD and FIONBIO.
 *
 * 1 - Not currently supported in Windows CE.
 *
 * 2 - The ioctl applies only to a specific address family.
 *
 * 3 - The ioctl applies only to a specific vendor's provider. This type allows companies to be
 * assigned a vendor number that appears in the Vendor/Address family field. Then, the vendor can
 * define new ioctls specific to that vendor without having to register the ioctl with a
 * clearinghouse, thereby providing vendor flexibility and privacy.
 *
 * Vendor/Address family - An 11-bit quantity that defines the vendor who owns the code (if T == 3)
 * or that contains the address family to which the code applies (if T == 2). If this is a Unix
 * ioctl code (T == 0) then this field has the same value as the code on Unix.
 *
 * Code - The 16-bit quantity that contains the specific ioctl code for the operation.
 *
 * The following Unix ioctl codes (commands) are supported:
 *
 * - FIONBIO: Enable or disable nonblocking mode on socket s. lpvInBuffer points at an unsigned
 * long, which is nonzero if nonblocking mode is to be enabled and zero if it is to be disabled.
 * When a socket is created, it operates in blocking mode (that is, nonblocking mode is disabled).
 * This is consistent with BSD sockets.
 *
 * - FIONREAD: Determine the amount of data that can be read atomically from socket s. lpvOutBuffer
 * points at an unsigned long in which WSAIoctl stores the result. If s is stream oriented (for
 * example, type SOCK_STREAM), FIONREAD returns the total amount of data that can be read in a
 * single receive operation; this is normally the same as the total amount of data queued on the
 * socket (since data stream is byte-oriented, this is not guaranteed). If s is message oriented
 * (for example, type SOCK_DGRAM), FIONREAD returns the size of the first datagram (message) queued
 * on the socket.
 *
 * - SIOCATMARK: Determine whether or not all out-of-band data has been read. This applies only to a
 * socket of stream-style (for example, type SOCK_STREAM) that has been configured for inline
 * reception of any out-of-band data (SO_OOBINLINE). If no out-of-band data is waiting to be read,
 * the operation returns TRUE. Otherwise, it returns FALSE, and the next receive operation performed
 * on the socket will retrieve some or all of the data preceding the "mark"; the application should
 * use the SIOCATMARK operation to determine whether any remains. If there is any normal data
 * preceding the "urgent" (out of band) data, it will be received in order. (Note that receive
 * operations will never mix out-of-band and normal data in the same call.) lpvOutBuffer points at a
 * BOOL in which WSAIoctl stores the result. In addition to the ioctlsocket control codes (FIONBIO,
 * SIOCATMARK, FIONREAD), the dwIoControlCode parameter may also assume the following SSL-specific
 * control flags:
 *
 * - SO_SSL_GET_CAPABILITIES: Retrieves a set of flags describing the WinSock security provider's
 * capabilities. The output buffer must be a pointer to a DWORD bit field. At present, only the
 * SSL_CAP_CLIENT flag is defined.
 *
 * - SO_SSL_GET_FLAGS: Retrieves s-channel specific flags associated with a particular socket. The
 * output buffer must be a pointer to a DWORD bit field. See SO_SSL_SET_FLAGS for details on valid
 * flags.
 *
 * - SO_SSL_SET_FLAGS: Sets the sockets' current s-channel-specific flag values. The input buffer
 * must be a pointer to a DWORD bit field. Currently, only the SSL_FLAG_DEFER_HANDSHAKE flag is
 * defined to allow the application to send and receive plain text data before switching to cipher
 * text. It is required for setting up communication through proxy servers. Normally the WinSock
 * security provider performs the secure handshake in the WinSock connect API. However, if this flag
 * is set, the handshake is deferred until the application issues the SO_SSL_PERFORM_HANDSHAKE
 * control code. After the handshaking, this flag is reset.
 *
 * - SO_SSL_GET_PROTOCOLS: Retrieves a list of protocols that the provider currently supports on
 * this socket. The output buffer must be a pointer to a SSLPROTOCOLS structure as described below:
 * typedef struct _SSLPROTOCOL { DWORD dwProtocol; DWORD dwVersion; DWORD dwFlags; } SSLPROTOCOL,
 * *LPSSLPROTOCOL; typedef struct _SSLPROTOCOLS { DWORD dwCount; SSLPROTOCOL ProtocolList[1]; }
 * SSLPROTOCOLS, FAR *LPSSLPROTOCOLS; Valid protocols include SSL_PROTOCOL_SSL2, SSL_PROTOCOL_SSL3,
 * and SSL_PROTOCOL_PCT1.
 *
 * - SO_SSL_SET_PROTOCOLS: Specifies a list of protocols the provider is to support on this socket.
 * The input buffer must be a pointer to SSLPROTOCOLS structure described above.
 *
 * - SO_SSL_SET_VALIDATE_CERT_HOOK: Sets the pointer to the socket's certificate validation hook. It
 * is used to specify the callback function invoked by the WinSock security provider when a set of
 * credentials is received from the remote party. The input buffer must be a pointer to the
 * SSLVALIDEATECERTHOOK structure, described below: typedef struct { SSLVALIDATECERTFUNC HookFunc;
 * LPVOID pvArg; } SSLVALIDATEPROTOCOLCERTHOOK, *PSSLVALIDATECERTHOOK; where HookFunc is a pointer
 * to the certificate validation callback function (see "Certificate Validation Callback" below).
 * pvArg is a pointer to application specific data and may be used by the application for any
 * purpose.
 *
 * - SO_SSL_PERFORM_HANDSHAKE: Initiates the secure handshake sequence on a connected socket where
 * the SSL_FLAG_DEFER_HANDSHAKE flag has been set prior to the connection. Data buffers are not
 * required, but the SSL_FLAG_DEFER_HANDSHAKE flag will be reset. Certificate Validation Callback
 * The WinSock security provider invokes the certificate validation callback when the remote party
 * receives a certificate for server authentication. All the client applications must implement the
 * callback function to ensure that the certificate should meet the following minimum requirements:
 * The certificate has not expired; The identity contained within the certificate matches that of
 * the remote party. The certificate validation callback function is of the following type: typedef
 * int (CALLBACK *SSLVALIDATECERTFUNC){ DWORD dwType, // in LPVOID pvArg, // in DWORD dwChainLen, //
 * in LPBLOB pCertChain, // in DWORD dwFlags // in }; The parameters are defined in the following
 * table.
 *
 * - dwType: Specifies the type of data pointed to be pCertChain. This must be SSL_CERT_X59 to
 * specify that pCertChain be a pointer to an X509 style certificate.
 *
 * - PvArg: An application-defined context passed into the SSLVALIDATECERTHOOK structure.
 *
 * - DwChainLen: The number of certificates pointed to by pCertChain. In Windows CE this will always
 * be one.
 *
 * - PCertChain: Pointer to the remote party's certificate.
 *
 * - DwFlags: To be designed to indicate that the certificate issuer list has been checked with the
 * list of known certificate authorities and that the certificate is either trusted or not. This is
 * required since not all the certificate chain is passed to the application.
 *
 * The application-defined callback function will typically return one of the following error
 * values:
 *
 * Value Description SSL_ERR_OKAY The remote party's certificate is acceptable. SSL_ERR_BAD_DATA The
 * certificate is improperly formatted. SSL_ERR_BAD_SIG The signature check fails.
 * SSL_ERR_CERT_EXPIRED The certificate has expired. SSL_ERR_CERT_REVOKED The certificate has been
 * revoked by its issuer. SSL_ERR_CERT_UNKNOWN The issuer of the certificate is not recognized or
 * some unspecified issue arose in the processing of the certificate, rendering it unacceptable.
 *
 * If the output buffer is not large enough to return all the data, WSAIoctl returns SOCKET_ERROR.
 * The value for WSAGetLastError is WSAEFAULT and lpcbReturned contains the number of bytes required
 * to successfully complete the operation.
 */
int
WINSOCKAPI // WSAAPI
WSAIoctl(
    IN  SOCKET  s,
    IN  DWORD   dwIoControlCode,
    IN  LPVOID  lpvInBuffer OPTIONAL,
    IN  DWORD   cbInBuffer,
    OUT LPVOID  lpvOutBuffer OPTIONAL,
    IN  DWORD   cbOutBuffer,
    OUT LPDWORD lpcbBytesReturned OPTIONAL,
    IN  LPVOID lpOverlapped,
    IN  LPVOID lpCompletionRoutine
    );

#ifdef __cplusplus
}
#endif

/* Microsoft Windows Extended data types */
typedef struct sockaddr SOCKADDR;
typedef struct sockaddr *PSOCKADDR;
typedef struct sockaddr *LPSOCKADDR;

typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr_in *PSOCKADDR_IN;
typedef struct sockaddr_in *LPSOCKADDR_IN;

typedef struct linger LINGER;
typedef struct linger *PLINGER;
typedef struct linger *LPLINGER;

typedef struct in_addr IN_ADDR;
typedef struct in_addr *PIN_ADDR;
typedef struct in_addr *LPIN_ADDR;

typedef struct fd_set FD_SET;
typedef struct fd_set *PFD_SET;
typedef struct fd_set *LPFD_SET;

typedef struct hostent HOSTENT;
typedef struct hostent *PHOSTENT;
typedef struct hostent *LPHOSTENT;

typedef struct servent SERVENT;
typedef struct servent *PSERVENT;
typedef struct servent *LPSERVENT;

typedef struct protoent PROTOENT;
typedef struct protoent *PPROTOENT;
typedef struct protoent *LPPROTOENT;

typedef struct timeval TIMEVAL;
typedef struct timeval *PTIMEVAL;
typedef struct timeval *LPTIMEVAL;


#endif  /* _WINSOCKAPI_ */

// @CESYSGEN ENDIF
