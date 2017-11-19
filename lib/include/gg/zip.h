/*
 *  include FILE <gg/zip.h>
 *
 *  Structures and Constants for PKZIP
 *  Version 1.01
 *
 *  written:       1990 02 04
 *                 1991 01 28: Revision
 *  latest update: 1994-07-28
 *
 */

#ifndef __GG_zip__
#define __GG_zip__

#include <gg/floskel.h>
#ifdef MSDOS
#pragma pack(1)
#endif

/* ------------------------------------------------------------------------ */
struct ZIP_local_file_header
{
  int   ZIP_LFH_vers_to_extract;
  int   ZIP_LFH_general_purpose_bit_flag;
  int   ZIP_LFH_compression_method;
  int   ZIP_LFH_last_mod_file_time;
  int   ZIP_LFH_last_mod_file_date;
  long  ZIP_LFH_crc32;
  long  ZIP_LFH_compressed_size;
  long  ZIP_LFH_uncompressed_size;
  int   ZIP_LFH_filename_length;
  int   ZIP_LFH_extra_field_length;
} ;

/* ------------------------------------------------------------------------ */
struct ZIP_LOCAL_FILE_HEADER
{
  struct ZIP_LOCAL_FILE_HEADER
        *ZIP_LFH_next,
        *ZIP_LFH_prev;
  int    ZIP_LFH_sig_PK;
  int    ZIP_LFH_sig_lfh;
  struct ZIP_local_file_header ZIP_LFH;
  char  *ZIP_LFH_filename;
  char  *ZIP_LFH_extra_field;
} ;

/* ------------------------------------------------------------------------ */
struct ZIP_central_file_header
{
  int   ZIP_CFH_version_made_by;
  int   ZIP_CFH_vers_to_extract;
  int   ZIP_CFH_general_purpose_bit_flag;
  int   ZIP_CFH_compression_method;
  int   ZIP_CFH_last_mod_file_time;
  int   ZIP_CFH_last_mod_file_date;
  long  ZIP_CFH_crc32;
  long  ZIP_CFH_compressed_size;
  long  ZIP_CFH_uncompressed_size;
  int   ZIP_CFH_filename_length;
  int   ZIP_CFH_extra_field_length;
  int   ZIP_CFH_file_comment_length;
  int   ZIP_CFH_disk_number_start;
  int   ZIP_CFH_internal_file_attributes;
  long  ZIP_CFH_external_file_attributes;
  long  ZIP_CFH_rel_off_local_header;
} ;

/* ------------------------------------------------------------------------ */
struct ZIP_CENTRAL_FILE_HEADER
{
  struct ZIP_CENTRAL_FILE_HEADER
        *ZIP_CFH_next,
        *ZIP_CFH_prev;
  int   ZIP_CFH_sig_PK;
  int   ZIP_CFH_sig_cfh;
  struct ZIP_central_file_header ZIP_CFH;
  char *ZIP_CFH_filename;
  char *ZIP_CFH_extra_field;
  char *ZIP_CFH_file_comment;
} ;

/* ------------------------------------------------------------------------ */
struct ZIP_central_dir_end
{
  int ZIP_CDE_disk_number;              /* Number of this disk              */
  int ZIP_CDE_cfh_start_disk;           /* Number of disk with beginning    */
                                        /* of the Central File Directory    */
  int ZIP_CDE_cfh_count_on_this_disk;   /* Number of entries in the         */
                                        /* Central File Directory           */
                                        /* on this disk                     */
  int ZIP_CDE_cfh_count;                /* Number of entries in the         */
                                        /* Central File Directory at all    */
  long ZIP_CDE_cfh_size;                /* Size of Central File Directory   */
  long ZIP_CDE_cfh_start_offset;
  int ZIP_CDE_zipfile_comment_length;
} ;

/* ------------------------------------------------------------------------ */
struct ZIP_CENTRAL_DIR_END
{
  int ZIP_CDE_sig_PK;
  int ZIP_CDE_sig_cde;
  struct ZIP_central_dir_end ZIP_CDE;
  char *ZIP_CDE_zipfile_comment;
} ;

/* structure to contral a ZIP-file ---------------------------------------- */
struct ZIP_CONTROL
{
  /* information about the ZIP file                                         */
  char *ZIPC_filename;                  /* name of the ZIP-file             */
  int   ZIPC_status;                    /* return value from ZIP scanner    */

  /* information from the ZIP file                                          */
  struct ZIP_LOCAL_FILE_HEADER
     *ZIPC_LFH,                         /* list of local file headers       */
    **ZIPC_LFH_app;                     /* append next file header          */
  struct ZIP_CENTRAL_FILE_HEADER
     *ZIPC_CFH,                         /* list of central file headers     */
    **ZIPC_CFH_app;                     /* append next central file header  */
  struct ZIP_CENTRAL_DIR_END
     *ZIPC_CDE;                         /* central directory end            */
} ;

/* signatures: ------------------------------------------------------------ */
#define ZIP_sig_PK              0x504B  /* == 'PK' -> this is a ZIP         */
#define ZIP_sig_lfh             0x0304  /* signature of local file header   */
#define ZIP_sig_lfh1            0x03
#define ZIP_sig_lfh2            0x04
#define ZIP_sig_cfh             0x0102  /* signature of central file header */
#define ZIP_sig_cfh1            0x01
#define ZIP_sig_cfh2            0x02
#define ZIP_sig_cde             0x0506  /* signature of central dir. end    */
#define ZIP_sig_cde1            0x05
#define ZIP_sig_cde2            0x06

/* prototypes: ------------------------------------------------------------ */
/* zip_0001.c */ int cdecl zip_quick_scan (char *fnm);
/* zip_0002.c */ long cdecl zip_find_cde_start (FILE *fi, long max_search);
/* zip_0003.c */ struct ZIP_CONTROL *cdecl zip_init_control (char *fnm);
/* zip_0004.c */ int cdecl zip_init_LFH (struct ZIP_LOCAL_FILE_HEADER *lfh);
/* zip_0005.c */ int cdecl zip_init_CFH (struct ZIP_CENTRAL_FILE_HEADER *cfh);
/* zip_0006.c */ int cdecl zip_init_CDE (struct ZIP_CENTRAL_DIR_END *cde);
/* zip_0007.c */ int cdecl zip_scan (struct ZIP_CONTROL *zc);

#endif
