/*
 *  include FILE <gg/mscdex01.h>
 *
 *  - prototypes
 *  - see also: cdcmd.c, <gg/mscdex.h>
 *
 *  written:       1997-08-24
 *  latest update: 1997-08-24  9:24:49
 *
 */

#ifndef __GG_mscdex01__
#define __GG_mscdex01__

#include <gg/floskel.h>

#define DEFAULT_PROMPT_BUFFER_SIZE 128

/* ------------------------------------------------------------------------ */
struct CD_CATALOG
{
  int format;
#define CD_FMT_HYX      0x0001  /* produce HYX frames                       */
#define CD_FMT_VERBOSE  0x0002  /* verbose information                      */

  int ask_mode;
#define CD_ask_dont     0       /* don't ask                                */
#define CD_ask_toc      1       /* prompt for contents information          */
#define CD_ask_hyx      2       /* like CD_ask_toc but use info to update   *
                                /* cluster                                  */

  char *cluster_name;
} ;

/* ------------------------------------------------------------------------ */
struct CD_TOC_PROMPT
{
  char *CDTP_bu1;
  char *CDTP_title;
  char *CDTP_sng;
  char *CDTP_grp;
  char *CDTP_class;
  int CDTP_buffer_size;
} ;

/* ------------------------------------------------------------------------ */
#ifdef _FILE_DEFINED
int cdecl cd_print_play_info (FILE *fo, int drive_num, int show);
int cdecl cd_print_upc_info (FILE *fo, int drive_num);
char *cdecl cd_get_upc (int drive);
int cdecl cd_print_track_info (FILE *fo, int drive_num,
  struct CD_CATALOG *cat, struct CD_TOC_PROMPT *cdtp);
#endif /* _FILE_DEFINED */

/* ------------------------------------------------------------------------ */
struct CD_TOC_PROMPT *cdecl cd_new_prompt_structure (int buffer_size);
struct CD_CATALOG *cdecl cd_new_catalog (void);

#endif /* __GG_mscdex01__ */
