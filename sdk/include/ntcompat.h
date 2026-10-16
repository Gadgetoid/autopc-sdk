#ifndef _NTCOMPAT_H_
#define _NTCOMPAT_H_

#include <windef.h>
#include <types.h>
#include <winbase.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef LONG NTSTATUS, *PNTSTATUS;

typedef CONST char *PCSZ;

typedef char CCHAR, *PCCHAR;
typedef short CSHORT, *PCSHORT;
typedef ULONG CLONG, *PCLONG;

typedef struct _STRING {
          USHORT        Length;
          USHORT        MaximumLength;
#ifdef MIDL_PASS
          [size_is(MaximumLength), length_is(Length)]
#endif
          PCHAR         Buffer;
        } STRING, *PSTRING;

typedef struct _CSTRING {
          USHORT        Length;
          USHORT        MaximumLength;
          CONST char    *Buffer;
        } CSTRING, *PCSTRING;

typedef struct _UNICODE_STRING {
          USHORT        Length;
          USHORT        MaximumLength;
#ifdef MIDL_PASS
          [size_is(MaximumLength / 2), length_is((Length) / 2)] USHORT *Buffer;
#else
          PWSTR         Buffer;
#endif
        } UNICODE_STRING, *PUNICODE_STRING;

typedef STRING ANSI_STRING, *PANSI_STRING;
typedef STRING OEM_STRING, *POEM_STRING;
typedef STRING CANSI_STRING;
typedef PSTRING PCANSI_STRING;

typedef LARGE_INTEGER PHYSICAL_ADDRESS, *PPHYSICAL_ADDRESS;

/* @@@ until we have it for real */
typedef VOID MDL, *PMDL;

/* I/O bus interface types */
typedef enum _INTERFACE_TYPE {
          InterfaceTypeUndefined = -1,
          Internal,
          Isa,
          Eisa,
          MicroChannel,
          TurboChannel,
          PCIBus,
          VMEBus,
          NuBus,
          PCMCIABus,
          CBus,
          MPIBus,
          MPSABus,
          ProcessorInternal,
          InternalPowerBus,
          PNPISABus,
          MaximumInterfaceType
        } INTERFACE_TYPE, *PINTERFACE_TYPE;

/* bus information types */
typedef enum _BUS_DATA_TYPE {
          ConfigurationSpaceUndefined = -1,
          Cmos,
          EisaConfiguration,
          Pos,
          CbusConfiguration,
          PCIConfiguration,
          VMEConfiguration,
          NuBusConfiguration,
          PCMCIAConfiguration,
          MPIConfiguration,
          MPSAConfiguration,
          PNPISAConfiguration,
          MaximumBusDataType
        } BUS_DATA_TYPE, *PBUS_DATA_TYPE;

/* DMA transfer widths */
typedef enum _DMA_WIDTH {
          Width8Bits,
          Width16Bits,
          Width32Bits,
          MaximumDmaWidth
        } DMA_WIDTH, *PDMA_WIDTH;

/* DMA transfer speeds */
typedef enum _DMA_SPEED {
          Compatible,
          TypeA,
          TypeB,
          TypeC,
          MaximumDmaSpeed
        } DMA_SPEED, *PDMA_SPEED;

/* PCI configuration */
typedef struct _PCI_SLOT_NUMBER {
          union {
            struct {
              ULONG     DeviceNumber:5;
              ULONG     FunctionNumber:3;
              ULONG     Reserved:24;
            } bits;
            ULONG       AsULONG;
          } u;
        } PCI_SLOT_NUMBER, *PPCI_SLOT_NUMBER;

#define PCI_TYPE0_ADDRESSES                     6
#define PCI_TYPE1_ADDRESSES                     2

typedef struct _PCI_COMMON_CONFIG {
          USHORT        VendorID;
          USHORT        DeviceID;
          USHORT        Command;
          USHORT        Status;
          UCHAR         RevisionID;
          UCHAR         ProgIf;
          UCHAR         SubClass;
          UCHAR         BaseClass;
          UCHAR         CacheLineSize;
          UCHAR         LatencyTimer;
          UCHAR         HeaderType;
          UCHAR         BIST;

          union {
            struct _PCI_HEADER_TYPE_0 {
              ULONG     BaseAddresses[PCI_TYPE0_ADDRESSES];
              ULONG     CIS;
              USHORT    SubVendorID;
              USHORT    SubSystemID;
              ULONG     ROMBaseAddress;
              ULONG     Reserved2[2];
              UCHAR     InterruptLine;
              UCHAR     InterruptPin;
              UCHAR     MinimumGrant;
              UCHAR     MaximumLatency;
            } type0;

            struct _PCI_HEADER_TYPE_1 {
              ULONG     BaseAddresses[PCI_TYPE1_ADDRESSES];
              UCHAR     PrimaryBus;
              UCHAR     SecondaryBus;
              UCHAR     SubordinateBus;
              UCHAR     SecondaryLatency;
              UCHAR     IOBase;
              UCHAR     IOLimit;
              USHORT    SecondaryStatus;
              USHORT    MemoryBase;
              USHORT    MemoryLimit;
              USHORT    PrefetchBase;
              USHORT    PrefetchLimit;
              ULONG     PrefetchBaseUpper32;
              ULONG     PrefetchLimitUpper32;
              USHORT    IOBaseUpper16;
              USHORT    IOLimitUpper16;
              ULONG     Reserved;
              ULONG     ROMBaseAddress;
              UCHAR     InterruptLine;
              UCHAR     InterruptPin;
              USHORT    BridgeControl;
            } type1;
          } u;

          UCHAR         DeviceSpecific[192];
       } PCI_COMMON_CONFIG, *PPCI_COMMON_CONFIG;

#define PCI_COMMON_HDR_LENGTH (FIELD_OFFSET(PCI_COMMON_CONFIG, DeviceSpecific))

#define PCI_MAX_DEVICES                         32
#define PCI_MAX_FUNCTION                        8

#define PCI_INVALID_VENDORID                    0xffff

/* bit encodings for PCI_COMMON_CONFIG.HeaderType */
#define PCI_MULTIFUNCTION                       0x80
#define PCI_DEVICE_TYPE                         0x00
#define PCI_BRIDGE_TYPE                         0x01

/* bit encodings for PCI_COMMON_CONFIG.Command */
#define PCI_ENABLE_IO_SPACE                     0x0001
#define PCI_ENABLE_MEMORY_SPACE                 0x0002
#define PCI_ENABLE_BUS_MASTER                   0x0004
#define PCI_ENABLE_SPECIAL_CYCLES               0x0008
#define PCI_ENABLE_WRITE_AND_INVALIDATE         0x0010
#define PCI_ENABLE_VGA_COMPATIBLE_PALETTE       0x0020
#define PCI_ENABLE_PARITY                       0x0040
#define PCI_ENABLE_WAIT_CYCLE                   0x0080
#define PCI_ENABLE_SERR                         0x0100
#define PCI_ENABLE_FAST_BACK_TO_BACK            0x0200

/* bit encodings for PCI_COMMON_CONFIG.Status */
#define PCI_STATUS_FAST_BACK_TO_BACK            0x0080
#define PCI_STATUS_DATA_PARITY_DETECTED         0x0100
#define PCI_STATUS_DEVSEL                       0x0600
#define PCI_STATUS_SIGNALED_TARGET_ABORT        0x0800
#define PCI_STATUS_RECEIVED_TARGET_ABORT        0x1000
#define PCI_STATUS_RECEIVED_MASTER_ABORT        0x2000
#define PCI_STATUS_SIGNALED_SYSTEM_ERROR        0x4000
#define PCI_STATUS_DETECTED_PARITY_ERROR        0x8000

/* bit encodings for PCI_COMMON_CONFIG.u.type0.BaseAddresses */
#define PCI_ADDRESS_IO_SPACE                    0x00000001
#define PCI_ADDRESS_MEMORY_TYPE_MASK            0x00000006
#define PCI_ADDRESS_MEMORY_PREFETCHABLE         0x00000008
#define PCI_TYPE_32BIT                          0
#define PCI_TYPE_20BIT                          2
#define PCI_TYPE_64BIT                          4

/* bit encodings for PCI_COMMON_CONFIG.u.type0.ROMBaseAddresses */
#define PCI_ROMADDRESS_ENABLED                  0x00000001

/* resources */
/* bit masks for Flags when type is CmResourceTypeInterrupt */
#define CM_RESOURCE_INTERRUPT_LEVEL_SENSITIVE   0
#define CM_RESOURCE_INTERRUPT_LATCHED           1

/* bit masks for Flags when type is CmResourceTypeMemory */
#define CM_RESOURCE_MEMORY_READ_WRITE           0x0000
#define CM_RESOURCE_MEMORY_READ_ONLY            0x0001
#define CM_RESOURCE_MEMORY_WRITE_ONLY           0x0002
#define CM_RESOURCE_MEMORY_PREFETCHABLE         0x0004
#define CM_RESOURCE_MEMORY_COMBINEDWRITE        0x0008
#define CM_RESOURCE_MEMORY_24                   0x0010

/* bit masks for Flags when type is CmResourceTypePort */
#define CM_RESOURCE_PORT_MEMORY                 0
#define CM_RESOURCE_PORT_IO                     1

/* bit masks for Flags when type is CmResourceTypeDma */
#define CM_RESOURCE_DMA_8                       0x0000
#define CM_RESOURCE_DMA_16                      0x0001
#define CM_RESOURCE_DMA_32                      0x0002

/* resource options */
#define IO_RESOURCE_PREFERRED                   0x01
#define IO_RESOURCE_DEFAULT                     0x02
#define IO_RESOURCE_ALTERNATIVE                 0x08

typedef enum _CM_RESOURCE_TYPE {
          CmResourceTypeNull = 0,
          CmResourceTypePort,
          CmResourceTypeInterrupt,
          CmResourceTypeMemory,
          CmResourceTypeDma,
          CmResourceTypeDeviceSpecific,
          CmResourceTypeMaximum
        } CM_RESOURCE_TYPE;

typedef enum _CM_SHARE_DISPOSITION {
          CmResourceShareUndetermined = 0,
          CmResourceShareDeviceExclusive,
          CmResourceShareDriverExclusive,
          CmResourceShareShared
        } CM_SHARE_DISPOSITION;

typedef struct _CM_PARTIAL_RESOURCE_DESCRIPTOR {
          UCHAR Type;
          UCHAR ShareDisposition;
          USHORT Flags;
          union {
            struct {
              PHYSICAL_ADDRESS  Start;
              ULONG             Length;
            } Port;

            struct {
              ULONG             Level;
              ULONG             Vector;
              ULONG             Affinity;
            } Interrupt;

            struct {
              PHYSICAL_ADDRESS  Start;
              ULONG             Length;
            } Memory;

            struct {
              ULONG             Channel;
              ULONG             Port;
              ULONG             Reserved1;
            } Dma;

            struct {
              ULONG             DataSize;
              ULONG             Reserved1;
              ULONG             Reserved2;
            } DeviceSpecificData;
          } u;
        } CM_PARTIAL_RESOURCE_DESCRIPTOR, *PCM_PARTIAL_RESOURCE_DESCRIPTOR;

typedef struct _CM_PARTIAL_RESOURCE_LIST {
          USHORT                Version;
          USHORT                Revision;
          ULONG                 Count;
          CM_PARTIAL_RESOURCE_DESCRIPTOR PartialDescriptors[1];
        } CM_PARTIAL_RESOURCE_LIST, *PCM_PARTIAL_RESOURCE_LIST;

typedef struct _CM_FULL_RESOURCE_DESCRIPTOR {
          INTERFACE_TYPE        InterfaceType;
          ULONG                 BusNumber;
          CM_PARTIAL_RESOURCE_LIST PartialResourceList;
        } CM_FULL_RESOURCE_DESCRIPTOR, *PCM_FULL_RESOURCE_DESCRIPTOR;

typedef struct _CM_RESOURCE_LIST {
          ULONG                 Count;
          CM_FULL_RESOURCE_DESCRIPTOR List[1];
        } CM_RESOURCE_LIST, *PCM_RESOURCE_LIST;

typedef struct _IO_RESOURCE_DESCRIPTOR {
          UCHAR                 Option;
          UCHAR                 Type;
          UCHAR                 ShareDisposition;
          UCHAR                 Spare1;
          USHORT                Flags;
          USHORT                Spare2;

          union {
            struct {
              ULONG             Length;
              ULONG             Alignment;
              PHYSICAL_ADDRESS  MinimumAddress;
              PHYSICAL_ADDRESS  MaximumAddress;
            } Port;

            struct {
              ULONG             Length;
              ULONG             Alignment;
              PHYSICAL_ADDRESS  MinimumAddress;
              PHYSICAL_ADDRESS  MaximumAddress;
            } Memory;

            struct {
              ULONG             MinimumVector;
              ULONG             MaximumVector;
            } Interrupt;

            struct {
              ULONG             MinimumChannel;
              ULONG             MaximumChannel;
            } Dma;

        } u;
      } IO_RESOURCE_DESCRIPTOR, *PIO_RESOURCE_DESCRIPTOR;

typedef struct _IO_RESOURCE_LIST {
          USHORT                Version;
          USHORT                Revision;
          ULONG                 Count;
          IO_RESOURCE_DESCRIPTOR Descriptors[1];
        } IO_RESOURCE_LIST, *PIO_RESOURCE_LIST;

typedef struct _IO_RESOURCE_REQUIREMENTS_LIST {
          ULONG                 ListSize;
          INTERFACE_TYPE        InterfaceType;
          ULONG                 BusNumber;
          ULONG                 SlotNumber;
          ULONG                 Reserved[3];
          ULONG                 AlternativeLists;
          IO_RESOURCE_LIST      List[1];
        } IO_RESOURCE_REQUIREMENTS_LIST, *PIO_RESOURCE_REQUIREMENTS_LIST;

typedef struct _DRIVER_OBJECT {
          HANDLE                ObjectHandle;
          UNICODE_STRING        DriverName;
          UNICODE_STRING        RegistryPath;
          UNICODE_STRING        ImagePath;
        } DRIVER_OBJECT, *PDRIVER_OBJECT;

typedef struct _DEVICE_OBJECT {
          CSHORT                Type;
          USHORT                Size;
          LONG                  ReferenceCount;
          PDRIVER_OBJECT        DriverObject;
          struct _DEVICE_OBJECT *NextDevice;
          struct _DEVICE_OBJECT *AttachedDevice;
        } DEVICE_OBJECT, *PDEVICE_OBJECT;

typedef
  VOID
  (*PWORKER_THREAD_ROUTINE)(
    IN PVOID Parameter
  );

typedef struct _WORK_QUEUE_ITEM {
          LIST_ENTRY    List;
          PWORKER_THREAD_ROUTINE WorkerRoutine;
          PVOID         Parameter;
        } WORK_QUEUE_ITEM, *PWORK_QUEUE_ITEM;

#define UNICODE_NULL ((WCHAR)0)

#define STATUS_BUFFER_OVERFLOW          ((NTSTATUS)0x80000005L)
#define STATUS_BUFFER_TOO_SMALL         ((NTSTATUS)0xC0000023L)
#define STATUS_INSUFFICIENT_RESOURCES   ((NTSTATUS)0xC000009AL)
#define STATUS_NOT_SUPPORTED            ((NTSTATUS)0xC00000BBL)
#define STATUS_REQUEST_NOT_ACCEPTED     ((NTSTATUS)0xC00000D0L)

#define RtlEqualMemory(_Destination, _Source, _Length) \
          (!memcmp(_Destination, _Source, _Length)
#define RtlMoveMemory(_Destination, _Source, _Length) \
          memmove(_Destination, _Source, _Length)
#define RtlCopyMemory(_Destination, _Source, _Length) \
          memcpy(_Destination, _Source, _Length)
#define RtlFillMemory(_Destination, _Length, _Fill) \
          memset(_Destination, _Fill, _Length)
#define RtlZeroMemory(_Destination, _Length) memset(_Destination, 0, _Length)

#if BINARY_COMPATIBLE && !defined(PopEntryList)
/* singly-linked list manipulation routines */
/*++
PSINGLE_LIST_ENTRY
PopEntryList(
  PSINGLE_LIST_ENTRY ListHead
)
--*/
#define PopEntryList(_ListHead) \
          (_ListHead)->Next; \
          { \
            PSINGLE_LIST_ENTRY _FirstEntry = (_ListHead)->Next; \
            if (_FirstEntry != NULL) \
              (_ListHead)->Next = _FirstEntry->Next; \
          }

/*++
VOID
PushEntryList(
  PSINGLE_LIST_ENTRY ListHead,
  PSINGLE_LIST_ENTRY Entry
)
--*/
#define PushEntryList(_ListHead, _Entry) \
        { \
          (_Entry)->Next = (_ListHead)->Next; \
          (_ListHead)->Next = _Entry; \
        }
#endif

#if BINARY_COMPATIBLE && !defined(InitializeListHead)
/* doubly-linked list manipulation routines */
/*++
VOID
InitializeListHead(
  PLIST_ENTRY ListHead
)
--*/
#define InitializeListHead(_ListHead) \
          ((_ListHead)->Flink = (_ListHead)->Blink = _ListHead)

/*++
BOOLEAN
IsListEmpty(
  PLIST_ENTRY ListHead
)
--*/
#define IsListEmpty(_ListHead)   ((_ListHead)->Flink == _ListHead)

/*++
PLIST_ENTRY
RemoveHeadList(
  PLIST_ENTRY ListHead
)
--*/
#define RemoveHeadList(_ListHead) \
          (_ListHead)->Flink; \
          RemoveEntryList((_ListHead)->Flink)

/*++
PLIST_ENTRY
RemoveTailList(
  PLIST_ENTRY ListHead
)
--*/
#define RemoveTailList(_ListHead) \
          (_ListHead)->Blink; \
          RemoveEntryList((_ListHead)->Blink)

/*++
VOID
RemoveEntryList(
  PLIST_ENTRY Entry
)
--*/
#define RemoveEntryList(_Entry) \
        { \
          PLIST_ENTRY _EX_Flink = (_Entry)->Flink; \
          PLIST_ENTRY _EX_Blink = (_Entry)->Blink; \
          _EX_Blink->Flink = _EX_Flink; \
          _EX_Flink->Blink = _EX_Blink; \
        }

/*++
VOID
InsertTailList(
  PLIST_ENTRY ListHead,
  PLIST_ENTRY Entry
)
--*/
#define InsertTailList(_ListHead, _Entry) \
        { \
          PLIST_ENTRY _EX_ListHead = _ListHead; \
          PLIST_ENTRY _EX_Blink = _EX_ListHead->Blink; \
          (_Entry)->Flink = _EX_ListHead; \
          (_Entry)->Blink = _EX_Blink; \
          _EX_Blink->Flink = _Entry; \
          _EX_ListHead->Blink = _Entry; \
        }

/*++
VOID
InsertHeadList(
  PLIST_ENTRY ListHead,
  PLIST_ENTRY Entry
)
--*/
#define InsertHeadList(_ListHead, _Entry) \
        { \
          PLIST_ENTRY _EX_ListHead = _ListHead; \
          PLIST_ENTRY _EX_Flink = _EX_ListHead->Flink; \
          (_Entry)->Flink = _EX_Flink; \
          (_Entry)->Blink = _EX_ListHead; \
          _EX_Flink->Blink = _Entry; \
          _EX_ListHead->Flink = _Entry; \
        }
#endif

/* hal.c */
BOOLEAN
HalTranslateBusAddress(
  IN INTERFACE_TYPE InterfaceType,
  IN ULONG BusNumber,
  IN PHYSICAL_ADDRESS BusAddress,
  IN OUT PULONG AddressSpace,
  OUT PPHYSICAL_ADDRESS TranslatedAddress
);

ULONG
HalGetBusDataByOffset(
  IN BUS_DATA_TYPE BusDataType,
  IN ULONG BusNumber,
  IN ULONG SlotNumber,
  IN PVOID Buffer,
  IN ULONG Offset,
  IN ULONG Length
);

ULONG
HalSetBusDataByOffset(
  IN BUS_DATA_TYPE BusDataType,
  IN ULONG BusNumber,
  IN ULONG SlotNumber,
  IN PVOID Buffer,
  IN ULONG Offset,
  IN ULONG Length
);

NTSTATUS
HalAssignSlotResources(
  IN PUNICODE_STRING RegistryPath,
  IN PUNICODE_STRING DriverClassName OPTIONAL,
  IN PDRIVER_OBJECT DriverObject,
  IN PDEVICE_OBJECT DeviceObject OPTIONAL,
  IN INTERFACE_TYPE BusType,
  IN ULONG BusNumber,
  IN ULONG SlotNumber,
  IN OUT PCM_RESOURCE_LIST *AllocatedResources
);

/* mm.c */
PVOID
MmMapIoSpace(
  IN PHYSICAL_ADDRESS PhysicalAddress,
  IN ULONG NumberOfBytes,
  IN BOOLEAN CacheEnable
);

VOID
MmUnmapIoSpace(
  IN PVOID BaseAddress,
  IN ULONG NumberOfBytes
);

/* io.c */
NTSTATUS
IoAssignResources(
  IN PUNICODE_STRING RegistryPath,
  IN PUNICODE_STRING DriverClassName OPTIONAL,
  IN PDRIVER_OBJECT DriverObject,
  IN PDEVICE_OBJECT DeviceObject OPTIONAL,
  IN PIO_RESOURCE_REQUIREMENTS_LIST RequestedResources,
  IN OUT PCM_RESOURCE_LIST *AllocatedResources
);

/* ke.c */
VOID
KeStallExecutionProcessor(
  ULONG MicroSecondsToStall
);

VOID
KeFlushWriteBuffer(
  VOID
);

/* debug.c */
VOID DbgBreakPoint(VOID);

/* this is a standard NT DDK function
   and should not be defined anywhere else */
#if defined(BINARY_COMPATIBLE) && defined(DbgPrint)
#undef DbgPrint
#endif

#if !defined(DbgPrint)
ULONG
DbgPrint(
  IN PCHAR DebugMessage,
  ...
);
#endif

/* rtl.c */
VOID
RtlInitString(
  OUT PSTRING DestinationString,
  IN PCSZ SourceString OPTIONAL
);

VOID
RtlInitAnsiString(
  OUT PANSI_STRING DestinationString,
  IN PCSZ SourceString OPTIONAL
);

VOID
RtlInitUnicodeString(
  OUT PUNICODE_STRING DestinationString,
  IN PCWSTR SourceString OPTIONAL
);

VOID
RtlFreeUnicodeString(
  IN PUNICODE_STRING UnicodeString
);

NTSTATUS
RtlAnsiStringToUnicodeString(
  OUT PUNICODE_STRING DestinationString,
  IN PANSI_STRING SourceString,
  IN BOOLEAN AllocateDestinationString
);

NTSTATUS
RtlUnicodeStringToAnsiString(
  IN OUT PANSI_STRING DestinationString,
  IN PUNICODE_STRING SourceString,
  IN BOOLEAN AllocateDestinationString
);

NTSTATUS
RtlUpcaseUnicodeString(
  OUT PUNICODE_STRING DestinationString,
  IN PUNICODE_STRING SourceString,
  IN BOOLEAN AllocateDestinationString
);

BOOLEAN
RtlEqualUnicodeString(
  IN PUNICODE_STRING String1,
  IN PUNICODE_STRING String2,
  IN BOOLEAN CaseInSensitive
);

VOID
RtlCopyUnicodeString(
  OUT PUNICODE_STRING DestinationString,
  IN PUNICODE_STRING SourceString OPTIONAL
);

NTSTATUS
RtlAppendUnicodeToString(
  IN PUNICODE_STRING Destination,
  IN PWSTR Source OPTIONAL
);

NTSTATUS
RtlAppendUnicodeStringToString(
  IN PUNICODE_STRING Destination,
  IN PUNICODE_STRING Source
);

#if defined(x86)
#define PAGE_SIZE       0x1000

#define HalGetDmaAlignmentRequirement() ((ULONG)1)
#define KeFlushIoBuffers(_Mdl, _ReadOperation, _DmaOperation)

/* rawio.c */
UCHAR
READ_PORT_UCHAR(
  IN PUCHAR Port
);

USHORT
READ_PORT_USHORT(
  IN PUSHORT Port
);

ULONG
READ_PORT_ULONG(
  IN PULONG Port
);

VOID
READ_PORT_BUFFER_UCHAR(
  IN PUCHAR Port,
  IN PUCHAR Buffer,
  IN ULONG Count
);

VOID
READ_PORT_BUFFER_USHORT(
  IN PUSHORT Port,
  IN PUSHORT Buffer,
  IN ULONG Count
);

VOID
READ_PORT_BUFFER_ULONG(
  IN PULONG Port,
  IN PULONG Buffer,
  IN ULONG Count
);

VOID
WRITE_PORT_UCHAR(
  IN PUCHAR Port,
  IN UCHAR Value
);

VOID
WRITE_PORT_USHORT(
  IN PUSHORT Port,
  IN USHORT Value
);

VOID
WRITE_PORT_ULONG(
  IN PULONG Port,
  IN ULONG Value
);

VOID
WRITE_PORT_BUFFER_UCHAR(
  IN PUCHAR Port,
  IN PUCHAR Buffer,
  IN ULONG Count
);

VOID
WRITE_PORT_BUFFER_USHORT(
  IN PUSHORT Port,
  IN PUSHORT Buffer,
  IN ULONG Count
);

VOID
WRITE_PORT_BUFFER_ULONG(
  IN PULONG Port,
  IN PULONG Buffer,
  IN ULONG Count
);

UCHAR
READ_REGISTER_UCHAR(
  IN PUCHAR Register
);

USHORT
READ_REGISTER_USHORT(
  IN PUSHORT Register
);

ULONG
READ_REGISTER_ULONG(
  IN PULONG Register
);

VOID
READ_REGISTER_BUFFER_UCHAR(
 IN PUCHAR Register,
 IN PUCHAR Buffer,
 IN ULONG Count
);

VOID
READ_REGISTER_BUFFER_USHORT(
 IN PUSHORT Register,
 IN PUSHORT Buffer,
 IN ULONG Count
);

VOID
READ_REGISTER_BUFFER_ULONG(
 IN PULONG Register,
 IN PULONG Buffer,
 IN ULONG Count
);

VOID
WRITE_REGISTER_UCHAR(
  IN PUCHAR Register,
  IN UCHAR Value
);

VOID
WRITE_REGISTER_USHORT(
  IN PUSHORT Register,
  IN USHORT Value
);

VOID
WRITE_REGISTER_ULONG(
  IN PULONG Register,
  IN ULONG Value
);

VOID
WRITE_REGISTER_BUFFER_UCHAR(
  IN PUCHAR Register,
  IN PUCHAR Buffer,
  IN ULONG Count
);

VOID
WRITE_REGISTER_BUFFER_USHORT(
  IN PUSHORT Register,
  IN PUSHORT Buffer,
  IN ULONG Count
);

VOID
WRITE_REGISTER_BUFFER_ULONG(
  IN PULONG Register,
  IN PULONG Buffer,
  IN ULONG Count
);
#endif /* x86 */

#if defined(MIPS)
#define PAGE_SIZE               0x1000
#define PHYS_ADDR_PCI_MEM_BASE  0x08000000
#define PHYS_ADDR_PCI_CFG_BASE  0x11000000
#define PHYS_ADDR_IO_SPACE_BASE 0x14000000

#define READ_PORT_UCHAR(_P) *(volatile UCHAR * const)(_P)

#define READ_PORT_USHORT(_P) *(volatile USHORT * const)(_P)

#define READ_PORT_ULONG(_P) *(volatile ULONG * const)(_P)

#define READ_PORT_BUFFER_UCHAR(_P, _B, _C) \
        { \
          PUCHAR _ReadBuffer = _B; \
          ULONG _ReadCount = _C; \
          ULONG _Index; \
          for (_Index=0; _Index<_ReadCount; _Index++) \
            *(_ReadBuffer++) = *(volatile UCHAR * const)(_P); \
        }

#define READ_PORT_BUFFER_USHORT(_P, _B, _C) \
        { \
          PUSHORT _ReadBuffer = _B; \
          ULONG _ReadCount = _C; \
          ULONG _Index; \
          for (_Index=0; _Index<_ReadCount; _Index++) \
            *(_ReadBuffer++) = *(volatile USHORT * const)(_P); \
        }

#define READ_PORT_BUFFER_ULONG(_P, _B, _C) \
        { \
          PULONG _ReadBuffer = _B; \
          ULONG _ReadCount = _C; \
          ULONG _Index; \
          for (_Index=0; _Index<_ReadCount; _Index++) \
            *(_ReadBuffer++) = *(volatile ULONG * const)(_P); \
        }

#define WRITE_PORT_UCHAR(_P, _V) \
        { \
          *(volatile UCHAR * const)(_P) = _V; \
          KeFlushWriteBuffer(); \
        }

#define WRITE_PORT_USHORT(_P, _V) \
        { \
          *(volatile USHORT * const)(_P) = _V; \
          KeFlushWriteBuffer(); \
        }

#define WRITE_PORT_ULONG(_P, _V) \
        { \
          *(volatile ULONG * const)(_P) = _V; \
          KeFlushWriteBuffer(); \
        }

#define WRITE_PORT_BUFFER_UCHAR(_P, _B, _C) \
        { \
          PUCHAR _WriteBuffer = _B; \
          ULONG _WriteCount = _C; \
          ULONG _Index; \
          for (_Index=0; _Index<_WriteCount; _Index++) { \
            *(volatile UCHAR * const)(_P) = *(_WriteBuffer++); \
            KeFlushWriteBuffer();  \
          } \
        }

#define WRITE_PORT_BUFFER_USHORT(_P, _B, _C) \
        { \
          PUSHORT _WriteBuffer = _B; \
          ULONG _WriteCount = _C; \
          ULONG _Index; \
          for (_Index=0; _Index<_WriteCount; _Index++) { \
            *(volatile USHORT * const)(_P) = *(_WriteBuffer++); \
            KeFlushWriteBuffer();  \
          } \
        }

#define WRITE_PORT_BUFFER_ULONG(_P, _B, _C) \
        { \
          PULONG _WriteBuffer = _B; \
          ULONG _WriteCount = _C; \
          ULONG _Index; \
          for (_Index=0; _Index<_WriteCount; _Index++) { \
            *(volatile ULONG * const)(_P) = *(_WriteBuffer++); \
            KeFlushWriteBuffer();  \
          } \
        }

#define READ_REGISTER_UCHAR(_R) *(volatile UCHAR * const)(_R)

#define READ_REGISTER_USHORT(_R) *(volatile USHORT * const)(_R)

#define READ_REGISTER_ULONG(_R) *(volatile ULONG * const)(_R)

#define READ_REGISTER_BUFFER_UCHAR(_R, _B, _C) \
        { \
          PUCHAR _RegisterBuffer = _R; \
          PUCHAR _ReadBuffer = _B; \
          ULONG _ReadCount = _C; \
          ULONG _Index; \
          for (_Index=0; _Index<_ReadCount; _Index++) \
            *(_ReadBuffer++) = *(volatile UCHAR * const)(_RegisterBuffer++); \
        }

#define READ_REGISTER_BUFFER_USHORT(_R, _B, _C) \
        { \
          PUSHORT _RegisterBuffer = _R; \
          PUSHORT _ReadBuffer = _B; \
          ULONG _ReadCount = _C; \
          ULONG _Index; \
          for (_Index=0; _Index<_ReadCount; _Index++) \
            *(_ReadBuffer++) = *(volatile USHORT * const)(_RegisterBuffer++); \
        }

#define READ_REGISTER_BUFFER_ULONG(_R, _B, _C) \
        { \
          PULONG _RegisterBuffer = _R; \
          PULONG _ReadBuffer = _B; \
          ULONG _ReadCount = _C; \
          ULONG _Index; \
          for (_Index=0; _Index<_ReadCount; _Index++) \
            *(_ReadBuffer++) = *(volatile ULONG * const)(_RegisterBuffer++); \
        }

#define WRITE_REGISTER_UCHAR(_R, _V) \
        { \
          *(volatile UCHAR * const)(_R) = _V; \
          KeFlushWriteBuffer(); \
        }

#define WRITE_REGISTER_USHORT(_R, _V) \
        { \
          *(volatile USHORT * const)(_R) = _V; \
          KeFlushWriteBuffer(); \
        }

#define WRITE_REGISTER_ULONG(_R, _V) \
        { \
          *(volatile ULONG * const)(_R) = _V; \
          KeFlushWriteBuffer(); \
        }

#define WRITE_REGISTER_BUFFER_UCHAR(_R, _B, _C) \
        { \
          PUCHAR _RegisterBuffer = _R; \
          PUCHAR _WriteBuffer = _B; \
          ULONG _WriteCount = _C; \
          ULONG _Index; \
          for (_Index=0; _Index<_WriteCount; _Index++) \
            *(volatile UCHAR * const)(_RegisterBuffer++) = *(_WriteBuffer++); \
          KeFlushWriteBuffer(); \
        }

#define WRITE_REGISTER_BUFFER_USHORT(_R, _B, _C) \
        { \
          PUSHORT _RegisterBuffer = _R; \
          PUSHORT _WriteBuffer = _B; \
          ULONG _WriteCount = _C; \
          ULONG _Index; \
          for (_Index=0; _Index<_WriteCount; _Index++) \
            *(volatile USHORT * const)(_RegisterBuffer++) = *(_WriteBuffer++); \
          KeFlushWriteBuffer(); \
        }

#define WRITE_REGISTER_BUFFER_ULONG(_R, _B, _C) \
        { \
          PULONG _RegisterBuffer = _R; \
          PULONG _WriteBuffer = _B; \
          ULONG _WriteCount = _C; \
          ULONG _Index; \
          for (_Index=0; _Index<_WriteCount; _Index++) \
            *(volatile ULONG * const)(_RegisterBuffer++) = *(_WriteBuffer++); \
          KeFlushWriteBuffer(); \
        }

ULONG
HalGetDmaAlignmentRequirement(
  VOID
);

VOID
KeFlushIoBuffers (
  IN PMDL Mdl,
  IN BOOLEAN ReadOperation,
  IN BOOLEAN DmaOperation
);
#endif /* MIPS */


#if defined(PPC) || defined(ARM)

#define PAGE_SIZE               0x1000

#define PHYS_ADDR_PCI_MEM_BASE  0xfacefeed
#define PHYS_ADDR_PCI_CFG_BASE  0xfacefeed
#define PHYS_ADDR_IO_SPACE_BASE 0xfacefeed

#define READ_PORT_UCHAR(_P) *(volatile UCHAR * const)(_P)

#define READ_PORT_USHORT(_P) *(volatile USHORT * const)(_P)

#define READ_PORT_ULONG(_P) *(volatile ULONG * const)(_P)

#define READ_PORT_BUFFER_UCHAR(_P, _B, _C) \
        { \
          PUCHAR _ReadBuffer = _B; \
          ULONG _ReadCount = _C; \
          ULONG _Index; \
          for (_Index=0; _Index<_ReadCount; _Index++) \
            *(_ReadBuffer++) = *(volatile UCHAR * const)(_P); \
        }

#define READ_PORT_BUFFER_USHORT(_P, _B, _C) \
        { \
          PUSHORT _ReadBuffer = _B; \
          ULONG _ReadCount = _C; \
          ULONG _Index; \
          for (_Index=0; _Index<_ReadCount; _Index++) \
            *(_ReadBuffer++) = *(volatile USHORT * const)(_P); \
        }

#define READ_PORT_BUFFER_ULONG(_P, _B, _C) \
        { \
          PULONG _ReadBuffer = _B; \
          ULONG _ReadCount = _C; \
          ULONG _Index; \
          for (_Index=0; _Index<_ReadCount; _Index++) \
            *(_ReadBuffer++) = *(volatile ULONG * const)(_P); \
        }

#define WRITE_PORT_UCHAR(_P, _V) \
        { \
          *(volatile UCHAR * const)(_P) = _V; \
          KeFlushWriteBuffer(); \
        }

#define WRITE_PORT_USHORT(_P, _V) \
        { \
          *(volatile USHORT * const)(_P) = _V; \
          KeFlushWriteBuffer(); \
        }

#define WRITE_PORT_ULONG(_P, _V) \
        { \
          *(volatile ULONG * const)(_P) = _V; \
          KeFlushWriteBuffer(); \
        }

#define WRITE_PORT_BUFFER_UCHAR(_P, _B, _C) \
        { \
          PUCHAR _WriteBuffer = _B; \
          ULONG _WriteCount = _C; \
          ULONG _Index; \
          for (_Index=0; _Index<_WriteCount; _Index++) { \
            *(volatile UCHAR * const)(_P) = *(_WriteBuffer++); \
            KeFlushWriteBuffer();  \
          } \
        }

#define WRITE_PORT_BUFFER_USHORT(_P, _B, _C) \
        { \
          PUSHORT _WriteBuffer = _B; \
          ULONG _WriteCount = _C; \
          ULONG _Index; \
          for (_Index=0; _Index<_WriteCount; _Index++) { \
            *(volatile USHORT * const)(_P) = *(_WriteBuffer++); \
            KeFlushWriteBuffer();  \
          } \
        }

#define WRITE_PORT_BUFFER_ULONG(_P, _B, _C) \
        { \
          PULONG _WriteBuffer = _B; \
          ULONG _WriteCount = _C; \
          ULONG _Index; \
          for (_Index=0; _Index<_WriteCount; _Index++) { \
            *(volatile ULONG * const)(_P) = *(_WriteBuffer++); \
            KeFlushWriteBuffer();  \
          } \
        }

#define READ_REGISTER_UCHAR(_R) *(volatile UCHAR * const)(_R)

#define READ_REGISTER_USHORT(_R) *(volatile USHORT * const)(_R)

#define READ_REGISTER_ULONG(_R) *(volatile ULONG * const)(_R)

#define READ_REGISTER_BUFFER_UCHAR(_R, _B, _C) \
        { \
          PUCHAR _RegisterBuffer = _R; \
          PUCHAR _ReadBuffer = _B; \
          ULONG _ReadCount = _C; \
          ULONG _Index; \
          for (_Index=0; _Index<_ReadCount; _Index++) \
            *(_ReadBuffer++) = *(volatile UCHAR * const)(_RegisterBuffer++); \
        }

#define READ_REGISTER_BUFFER_USHORT(_R, _B, _C) \
        { \
          PUSHORT _RegisterBuffer = _R; \
          PUSHORT _ReadBuffer = _B; \
          ULONG _ReadCount = _C; \
          ULONG _Index; \
          for (_Index=0; _Index<_ReadCount; _Index++) \
            *(_ReadBuffer++) = *(volatile USHORT * const)(_RegisterBuffer++); \
        }

#define READ_REGISTER_BUFFER_ULONG(_R, _B, _C) \
        { \
          PULONG _RegisterBuffer = _R; \
          PULONG _ReadBuffer = _B; \
          ULONG _ReadCount = _C; \
          ULONG _Index; \
          for (_Index=0; _Index<_ReadCount; _Index++) \
            *(_ReadBuffer++) = *(volatile ULONG * const)(_RegisterBuffer++); \
        }

#define WRITE_REGISTER_UCHAR(_R, _V) \
        { \
          *(volatile UCHAR * const)(_R) = _V; \
          KeFlushWriteBuffer(); \
        }

#define WRITE_REGISTER_USHORT(_R, _V) \
        { \
          *(volatile USHORT * const)(_R) = _V; \
          KeFlushWriteBuffer(); \
        }

#define WRITE_REGISTER_ULONG(_R, _V) \
        { \
          *(volatile ULONG * const)(_R) = _V; \
          KeFlushWriteBuffer(); \
        }

#define WRITE_REGISTER_BUFFER_UCHAR(_R, _B, _C) \
        { \
          PUCHAR _RegisterBuffer = _R; \
          PUCHAR _WriteBuffer = _B; \
          ULONG _WriteCount = _C; \
          ULONG _Index; \
          for (_Index=0; _Index<_WriteCount; _Index++) \
            *(volatile UCHAR * const)(_RegisterBuffer++) = *(_WriteBuffer++); \
          KeFlushWriteBuffer(); \
        }

#define WRITE_REGISTER_BUFFER_USHORT(_R, _B, _C) \
        { \
          PUSHORT _RegisterBuffer = _R; \
          PUSHORT _WriteBuffer = _B; \
          ULONG _WriteCount = _C; \
          ULONG _Index; \
          for (_Index=0; _Index<_WriteCount; _Index++) \
            *(volatile USHORT * const)(_RegisterBuffer++) = *(_WriteBuffer++); \
          KeFlushWriteBuffer(); \
        }

#define WRITE_REGISTER_BUFFER_ULONG(_R, _B, _C) \
        { \
          PULONG _RegisterBuffer = _R; \
          PULONG _WriteBuffer = _B; \
          ULONG _WriteCount = _C; \
          ULONG _Index; \
          for (_Index=0; _Index<_WriteCount; _Index++) \
            *(volatile ULONG * const)(_RegisterBuffer++) = *(_WriteBuffer++); \
          KeFlushWriteBuffer(); \
        }

ULONG
HalGetDmaAlignmentRequirement(
  VOID
);

VOID
KeFlushIoBuffers (
  IN PMDL Mdl,
  IN BOOLEAN ReadOperation,
  IN BOOLEAN DmaOperation
);
#endif /* PPC */


#if defined(SHx)
#define PAGE_SIZE               0x1000
#define PHYS_ADDR_PCI_MEM_BASE  0x04000000
#define PHYS_ADDR_PCI_CFG_BASE  0x12000000
#define PHYS_ADDR_IO_SPACE_BASE 0x10000000

#define READ_PORT_UCHAR(_P) *(volatile UCHAR * const)(_P)

#define READ_PORT_USHORT(_P) *(volatile USHORT * const)(_P)

#define READ_PORT_ULONG(_P) *(volatile ULONG * const)(_P)

#define READ_PORT_BUFFER_UCHAR(_P, _B, _C) \
        { \
          PUCHAR _ReadBuffer = _B; \
          ULONG _ReadCount = _C; \
          ULONG _Index; \
          for (_Index=0; _Index<_ReadCount; _Index++) \
            *(_ReadBuffer++) = *(volatile UCHAR * const)(_P); \
        }

#define READ_PORT_BUFFER_USHORT(_P, _B, _C) \
        { \
          PUSHORT _ReadBuffer = _B; \
          ULONG _ReadCount = _C; \
          ULONG _Index; \
          for (_Index=0; _Index<_ReadCount; _Index++) \
            *(_ReadBuffer++) = *(volatile USHORT * const)(_P); \
        }

#define READ_PORT_BUFFER_ULONG(_P, _B, _C) \
        { \
          PULONG _ReadBuffer = _B; \
          ULONG _ReadCount = _C; \
          ULONG _Index; \
          for (_Index=0; _Index<_ReadCount; _Index++) \
            *(_ReadBuffer++) = *(volatile ULONG * const)(_P); \
        }

#define WRITE_PORT_UCHAR(_P, _V) \
        { \
          *(volatile UCHAR * const)(_P) = _V; \
          KeFlushWriteBuffer(); \
        }

#define WRITE_PORT_USHORT(_P, _V) \
        { \
          *(volatile USHORT * const)(_P) = _V; \
          KeFlushWriteBuffer(); \
        }

#define WRITE_PORT_ULONG(_P, _V) \
        { \
          *(volatile ULONG * const)(_P) = _V; \
          KeFlushWriteBuffer(); \
        }

#define WRITE_PORT_BUFFER_UCHAR(_P, _B, _C) \
        { \
          PUCHAR _WriteBuffer = _B; \
          ULONG _WriteCount = _C; \
          ULONG _Index; \
          for (_Index=0; _Index<_WriteCount; _Index++) { \
            *(volatile UCHAR * const)(_P) = *(_WriteBuffer++); \
            KeFlushWriteBuffer();  \
          } \
        }

#define WRITE_PORT_BUFFER_USHORT(_P, _B, _C) \
        { \
          PUSHORT _WriteBuffer = _B; \
          ULONG _WriteCount = _C; \
          ULONG _Index; \
          for (_Index=0; _Index<_WriteCount; _Index++) { \
            *(volatile USHORT * const)(_P) = *(_WriteBuffer++); \
            KeFlushWriteBuffer();  \
          } \
        }

#define WRITE_PORT_BUFFER_ULONG(_P, _B, _C) \
        { \
          PULONG _WriteBuffer = _B; \
          ULONG _WriteCount = _C; \
          ULONG _Index; \
          for (_Index=0; _Index<_WriteCount; _Index++) { \
            *(volatile ULONG * const)(_P) = *(_WriteBuffer++); \
            KeFlushWriteBuffer();  \
          } \
        }

#define READ_REGISTER_UCHAR(_R) *(volatile UCHAR * const)(_R)

#define READ_REGISTER_USHORT(_R) *(volatile USHORT * const)(_R)

#define READ_REGISTER_ULONG(_R) *(volatile ULONG * const)(_R)

#define READ_REGISTER_BUFFER_UCHAR(_R, _B, _C) \
        { \
          PUCHAR _RegisterBuffer = _R; \
          PUCHAR _ReadBuffer = _B; \
          ULONG _ReadCount = _C; \
          ULONG _Index; \
          for (_Index=0; _Index<_ReadCount; _Index++) \
            *(_ReadBuffer++) = *(volatile UCHAR * const)(_RegisterBuffer++); \
        }

#define READ_REGISTER_BUFFER_USHORT(_R, _B, _C) \
        { \
          PUSHORT _RegisterBuffer = _R; \
          PUSHORT _ReadBuffer = _B; \
          ULONG _ReadCount = _C; \
          ULONG _Index; \
          for (_Index=0; _Index<_ReadCount; _Index++) \
            *(_ReadBuffer++) = *(volatile USHORT * const)(_RegisterBuffer++); \
        }

#define READ_REGISTER_BUFFER_ULONG(_R, _B, _C) \
        { \
          PULONG _RegisterBuffer = _R; \
          PULONG _ReadBuffer = _B; \
          ULONG _ReadCount = _C; \
          ULONG _Index; \
          for (_Index=0; _Index<_ReadCount; _Index++) \
            *(_ReadBuffer++) = *(volatile ULONG * const)(_RegisterBuffer++); \
        }

#define WRITE_REGISTER_UCHAR(_R, _V) \
        { \
          *(volatile UCHAR * const)(_R) = _V; \
          KeFlushWriteBuffer(); \
        }

#define WRITE_REGISTER_USHORT(_R, _V) \
        { \
          *(volatile USHORT * const)(_R) = _V; \
          KeFlushWriteBuffer(); \
        }

#define WRITE_REGISTER_ULONG(_R, _V) \
        { \
          *(volatile ULONG * const)(_R) = _V; \
          KeFlushWriteBuffer(); \
        }

#define WRITE_REGISTER_BUFFER_UCHAR(_R, _B, _C) \
        { \
          PUCHAR _RegisterBuffer = _R; \
          PUCHAR _WriteBuffer = _B; \
          ULONG _WriteCount = _C; \
          ULONG _Index; \
          for (_Index=0; _Index<_WriteCount; _Index++) \
            *(volatile UCHAR * const)(_RegisterBuffer++) = *(_WriteBuffer++); \
          KeFlushWriteBuffer(); \
        }

#define WRITE_REGISTER_BUFFER_USHORT(_R, _B, _C) \
        { \
          PUSHORT _RegisterBuffer = _R; \
          PUSHORT _WriteBuffer = _B; \
          ULONG _WriteCount = _C; \
          ULONG _Index; \
          for (_Index=0; _Index<_WriteCount; _Index++) \
            *(volatile USHORT * const)(_RegisterBuffer++) = *(_WriteBuffer++); \
          KeFlushWriteBuffer(); \
        }

#define WRITE_REGISTER_BUFFER_ULONG(_R, _B, _C) \
        { \
          PULONG _RegisterBuffer = _R; \
          PULONG _WriteBuffer = _B; \
          ULONG _WriteCount = _C; \
          ULONG _Index; \
          for (_Index=0; _Index<_WriteCount; _Index++) \
            *(volatile ULONG * const)(_RegisterBuffer++) = *(_WriteBuffer++); \
          KeFlushWriteBuffer(); \
        }

ULONG
HalGetDmaAlignmentRequirement(
  VOID
);

VOID
KeFlushIoBuffers (
  IN PMDL Mdl,
  IN BOOLEAN ReadOperation,
  IN BOOLEAN DmaOperation
);
#endif /* SHx */

#ifdef __cplusplus
}
#endif

#endif
