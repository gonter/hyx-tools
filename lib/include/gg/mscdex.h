/*
 *  include FILE <gg/mscdex.h>
 *
 *  - prototypes
 *  - see also: cdcmd.c
 *
 *  written:       1995-06-04
 *  latest update: 1997-08-24  9:32:12
 *
 */

#ifndef __GG_mscdex__
#define __GG_mscdex__

#include <gg/floskel.h>

#pragma pack(1)
#define _80MINUTES_ 360000L     /* 80*60*75 */

/* ------------------------------------------------------------------------ */
struct DDRV_REQ_HDR
{
  char DRH_length;
  char DRH_subunit_code;
  unsigned char DRH_command_code;
  int  DRH_status;
  char DRH_reserved [8];
} ;

/* ------------------------------------------------------------------------ */
struct DDRV_REQ_HDR_IOCTL
{
  struct DDRV_REQ_HDR DRH_DDRV;
  char DRH_mdb;                         /* 0 */
  char *DRH_ta;
  int DRH_size;
  int DRH_start;
  char *DRH_ptr;
} ;

/* ------------------------------------------------------------------------ */
struct DDRV_REQ_HDR_PLAYREQ
{
  struct DDRV_REQ_HDR DRH_DDRV;
  char DRH_addr_mode;
  long DRH_start;
  long DRH_number;
} ;

/* ------------------------------------------------------------------------ */
struct DDRV_AUDIO_DISK_INFO
{
  char DADI_code;
  char DADI_lowest_track;
  char DADI_highest_track;
  long DADI_lead_out;
} ;

/* ------------------------------------------------------------------------ */
struct DDRV_AUDIO_TRACK_INFO
{
  char DATI_code;
  char DATI_track;
  long DATI_start;
  char DATI_tci;                /* Track Control Information                */
                                /* ... interpreted according to the         */
                                /* Philips/Sony Red Book standard.          */
} ;

/* ------------------------------------------------------------------------ */
struct DDRV_AUDIO_Q_CHANNEL_INFO
{
  char DAQI_code;
  char DAQI_tci;
  char DAQI_track;
  char DAQI_index;
  char DAQI_track_min;          /* running time within track */
  char DAQI_track_sec;
  char DAQI_track_frame;
  char DAQI_track_zero;
  char DAQI_disk_min;           /* running time within disk */
  char DAQI_disk_sec;
  char DAQI_disk_frame;
} ;

/* ------------------------------------------------------------------------ */
struct DDRV_UPC                 /* universal product code */
{
  char DUPC_code;
  char DUPC_control;
  char DUPC_num [7];
  char DUPC_zero;
  char DUPC_aframe;
} ;

#pragma pack()
/* ------------------------------------------------------------------------ */
struct CD_TRACK_INFO
{
  int CDTI_tci;
  long CDTI_track_offset;
} ;

/* ------------------------------------------------------------------------ */
struct CD_DISK_INFO
{
  int CDDI_first_track;
  int CDDI_last_track;
  int CDDI_track_count;
  long CDDI_end_address;
  char *CDDI_id_code;                   /* MD5 code */
  int CDDI_ti_size;
  struct CD_TRACK_INFO *CDDI_ti;
} ;

/* ------------------------------------------------------------------------ */
#define MSCDEX_ERROR    0x8000
#define MSCDEX_BUSY     0x0200
#define MSCDEX_DONE     0x0100

/* prototypes: ------------------------------------------------------------ */
int cdecl mscdex_get_drives (void);
int cdecl mscdex_get_first_drive (void);
int cdecl mscdex_send_device_request (int drive, char *request_header);

char *cdecl cd_addr_to_time (long addr, int fmt);
char *cdecl cd_binary_to_time (long frames);
long cdecl cd_addr_to_binary (long addr);
struct CD_DISK_INFO *cd_read_track_info (int drive_num);

int cdecl cd_eject_close (int drive, int eject_close);
int cdecl cd_play (int drive, long first, long number);
int cdecl cd_stop_resume (int drive, int mode);
int cdecl cd_info (int drive, int *first_track, int *last_track,
                   long *address);
int cdecl cd_track_info (int drive, int track_number, long *start, int *tci);
int cdecl cd_upc (int drive, struct DDRV_UPC *req, int ctrl);
int cdecl cd_query (int drive, int *tci, int *track, int *index,
                    int *track_min, int *track_sec, int *track_fr,
                    int *disk_min, int *disk_sec, int *disk_fr);

int cdecl cd_is_playing (int drive_num);
int cdecl cd_play_track (int drive, char *s);

#endif /* __GG_mscdex__ */
