/*
 *  include FILE <contrib/pcmcia.h>
 *
 *  from Dr. Dobb's Journal 94/06
 *
 *                 1994-09-01
 *  latest update: 1994-09-01
 *
 */

/****************************************************************************/
/** CARDINFO.H -- by Troy-Anthony Miles                                     */
/**                                                                         */
/****************************************************************************/

/** GENERAL DEFINITIONS*/

typedef unsigned char           BYTE;
typedef unsigned short int      WORD;
typedef unsigned long           DWORD;

#define LOBYTE(w)               ((BYTE)(w))
#define HIBYTE(w)               ((BYTE)(((WORD)(w) >> 8) & 0xFF))
#define LOWORD(l)               ((WORD)(DWORD)(l))
#define HIWORD(l)               ((WORD)((((DWORD)(l)) >> 16) & 0xFFFF))

#define  FALSE                  0
#define  TRUE                   1

#define CARD_INTERRUPT          0x1A
#define CARD_SUBFUNCTION        0xAF
#define SIGNATURE               'SC'

/** POSITIONS*/

#define D_LINES                 7
#define D_Y                     6
#define D_Y2                    (D_Y + 4)
#define D_X                     0

/**  FUNCTION CODES*/

#define GET_CARDSERVICES_INFO   0x0B
#define REGISTER_CLIENT         0x10
#define DEREGISTER_CLIENT       0x02
#define GET_STATUS              0x0C
#define RESET_CARD              0x11
#define SET_EVENT_MASK          0x31
#define GET_EVENT_MASK          0x2E

#define REQUEST_IO              0x1F
#define RELEASE_IO              0x1B
#define REQUEST_IRQ             0x20
#define RELEASE_IRQ             0x1C
#define REQUEST_WINDOW          0x21
#define RELEASE_WINDOW          0x1D
#define MODIFY_WINDOW           0x17
#define MAP_MEM_PAGE            0x14
#define REQUEST_SOCKET_MASK     0x22
#define RELEASE_SOCKET_MASK     0x2F
#define REQUEST_CONFIGURATION   0x30
#define GET_CONFIGURATION_INFO  0x04
#define MODIFY_CONFIGURATION    0x27
#define RELEASE_CONFIGURATION   0x1E

#define OPEN_MEMORY             0x18
#define READ_MEMORY             0x19
#define WRITE_MEMORY            0x24
#define COPY_MEMORY             0x01
#define REGISTER_ERASE_QUEUE    0x0F
#define CHECK_ERASE_QUEUE       0x26
#define DEREGISTER_ERASE_QUEUE  0x25
#define CLOSE_MEMORY            0x00

#define GET_FIRST_TUPLE         0x07
#define GET_NEXT_TUPLE          0x0A
#define GET_TUPLE_DATA          0x0D
#define GET_FIRST_REGION        0x06
#define GET_NEXT_REGION         0x09
#define GET_FIRST_PARTITION     0x05
#define GET_NEXT_PARTITION      0x08

#define RETURN_SS_ENTRY         0x23
#define MAP_LOG_SOCKET          0x12
#define MAP_PHY_SOCKET          0x15
#define MAP_LOG_WINDOW          0x13
#define MAP_PHY_WINDOW          0x16
#define REGISTER_MTD            0x1A
#define REGISTER_TIMER          0x28
#define SET_REGION              0x29
#define VALIDATE_CIS            0x2B
#define REQUEST_EXCLUSIVE       0x2C
#define RELEASE_EXCLUSIVE       0x2D
#define GET_FIRST_CLIENT        0x0E
#define GET_NEXT_CLIENT         0x2A
#define GET_CLIENT_INFO         0x03
#define ADD_SOCKET_SERVICES     0x32
#define REPLACE_SOCKET_SERVICES 0x33
#define VENDOR_SPECIFIC         0x34
#define ADJUST_RESOURCE_INFO    0x35

/** FLAGS*/

#define WRITE_PROTECT           0x01
#define BATTERY_DEAD_FLAG       0x10
#define BATTERY_LOW_FLAG        0x20
#define CARD_DETECT_FLAG        0x80

/** RETURN CODES*/

#define SUCCESS                 0x00
#define BAD_ADAPTER             0x01
#define BAD_ATTRIBUTE           0x02
#define BAD_BASE                0x03
#define BAD_EDC                 0x04

#define BAD_IRQ                 0x06
#define BAD_OFFSET              0x07
#define BAD_PAGE                0x08
#define READ_FAILURE            0x09
#define BAD_SIZE                0x0A
#define BAD_SOCKET              0x0B

#define BAD_TYPE                0x0D
#define BAD_VCC                 0x0E
#define BAD_VPP                 0x0F

#define BAD_WINDOW              0x11
#define WRITE_FAILURE           0x12

#define NO_CARD                 0x14
#define UNSUPPORTED_FUNCTION    0x15
#define UNSUPPORTED_MODE        0x16
#define BAD_SPEED               0x17
#define BUSY                    0x18
#define GENERAL_FAILURE         0x19
#define WRITE_PROTECTED         0x1A
#define BAD_ARGS_LENGTH         0x1B
#define BAD_ARGS                0x1C
#define CONFIGURATION_LOCKED    0x1D
#define IN_USE                  0x1E
#define NO_MORE_ITEMS           0x1F
#define OUT_OF_RESOURCE         0x20
#define BAD_HANDLE              0x21

/**  TUPLES*/

#define CISTPL_NULL             0x00
#define CISTPL_DEVICE           0x01
#define CISTPL_CHECKSUM         0x10
#define CISTPL_LONGLINK_A       0x11
#define CISTPL_LONGLINK_C       0x12
#define CISTPL_LINKTARGET       0x13
#define CISTPL_NO_LINK          0x14
#define CISTPL_VERS_1           0x15
#define CISTPL_ALTSTR           0x16
#define CISTPL_DEVICE_A         0x17
#define CISTPL_JEDEC_C          0x18
#define CISTPL_JEDEC_A          0x19
#define CISTPL_CONFIG           0x1A
#define CISTPL_CFTABLE_ENTRY    0x1B
#define CISTPL_DEVICE_OC        0x1C
#define CISTPL_DEVICE_OA        0x1D
#define CISTPL_VERS_2           0x40
#define CISTPL_FORMAT           0x41
#define CISTPL_GEOMETRY         0x42
#define CISTPL_BYTEORDER        0x43
#define CISTPL_DATE             0x44
#define CISTPL_BATTERY          0x45
#define CISTPL_ORG              0x46
#define CISTPL_END              0xFF

/**  DEVICE TYPES*/

#define  DTYPE_NULL             0x0
#define  DTYPE_ROM              0x1
#define  DTYPE_OTPROM           0x2
#define  DTYPE_EPROM            0x3
#define  DTYPE_EEPROM           0x4
#define  DTYPE_FLASH            0x5
#define  DTYPE_SRAM             0x6
#define  DTYPE_DRAM             0x7
#define  DTYPE_FUNCSPEC         0xD
#define  DTYPE_EXTEND           0xE

/**  EVENTS*/

#define PM_RESUME               0x0B
#define PM_SUSPEND              0x0C
#define BATTERY_DEAD            0x01
#define BATTERY_LOW             0x02
#define CARD_INSERTION          0x40
#define CARD_LOCK               0x03
#define CARD_READY              0x04
#define CARD_REMOVAL            0x05
#define CARD_RESET              0x11
#define CARD_UNLOCK             0x06
#define EJECTION_COMPLETE       0x07
#define EJECTION_REQUEST        0x08
#define ERASE_COMPLETE          0x81
#define EXCLUSIVE_COMPLETE      0x0D
#define EXCLUSIVE_REQUEST       0x0E
#define INSERTION_COMPLETE      0x09
#define INSERTION_REQUEST       0x0A
#define REGISTRATION_COMPLETE   0x82
#define RESET_COMPLETE          0x80
#define RESET_PHYSICAL          0x0F
#define RESET_REQUEST           0x10
#define MTD_REQUEST             0x12
#define CLIENT_INFO             0x14
#define TIMER_EXPIRED           0x15
#define SS_UPDATED              0x16

/**  STRUCTURES*/

typedef struct {
  WORD  InfoLen;
  WORD  Signature;
  WORD  Count;
  WORD  Revision;
  WORD  CSLevel;
  WORD  VStrOff;
  WORD  VStrLen;
  BYTE  VendorString[80];
}CS_INFO;

typedef struct{
  WORD  Socket;
  WORD  CardState;
  WORD  SocketState;
}STATUS_INFO;

typedef struct {
  WORD  Socket;
  WORD  Attributes;
  BYTE  DesiredTuple;
  BYTE  Reserved;
  WORD  Flags;
  DWORD LinkOffset;
  DWORD CISOffset;
  BYTE  TupleCode;
  BYTE  TupleLink;
}TUPLE_INFO;

typedef struct {
  WORD  Socket;
  WORD  Attributes;
  BYTE  DesiredTuple;
  BYTE  TupleOffset;
  WORD  Flags;
  DWORD LinkOffset;
  DWORD CISOffset;
  WORD  TupleDataMax;
  WORD  TupleDataLen;
  BYTE  TupleData[20]; /* GG  JUNK!!!! */
}TUPLE_DATA_INFO;

typedef struct {
  WORD  Attributes;
  WORD  EventMask;
  BYTE  ClientData[8];
  WORD  Version;
}REGISTER_CLIENT_INFO;

