/*
 *  include FILE <gg/tfb.h>
 *
 *  written:       1993-10-19
 *  latest update: 1997-08-28 18:40:22
 *  $Id: tfb.h,v 1.4 2010/05/04 02:47:07 gonter Exp $
 *
 */

#ifndef __GG_tfb__
#define __GG_tfb__

#include <gg/floskel.h>

/* ------------------------------------------------------------------------ */
#ifdef _FILE_DEFINED
struct TFB_HANDLE
{
  char *TFBH_tfb_name;
  char *TFBH_lut_name;
  FILE *TFBH_tfb;
  FILE *TFBH_lut;
  char *TFBH_buffer;
  int TFBH_buffer_size;
} ;
typedef struct TFB_HANDLE TFB_HANDLE;
#define TFB_default_buffer_size 4096
#endif /* _FILE_DEFINED */

/* ------------------------------------------------------------------------ */
#define AK_complain     0x01
#define AK_last         0x02

#define MK_none         0
#define MK_toupper      1
#define MK_tolower      2

/* tfb01.c ---------------------------------------------------------------- */
int cdecl tfb_get_entry (const char *keyword,
                         const char *file_tfb, const char *file_lut,
                         char *line_buffer, int MAX_LINE_BUFFER);

/* tfb02.c ---------------------------------------------------------------- */
int cdecl tfb_get_2entry (char *keyword, char *file_tfb, char *lut_buffer,
                          char *line_buffer, int MAX_LINE_BUFFER);
#ifdef _FILE_DEFINED
struct TFB_HANDLE *cdecl tfb_create_handle (char *fn_tfb, char *fn_lut);
int cdecl tfb_transfer_entry (FILE *fo, struct TFB_HANDLE *handle,
                              char *key);
int tfb_close_handle (struct TFB_HANDLE *h);
int tfb_fetch_entry (struct TFB_HANDLE *handle, char *key,
                     char *buffer, int buffer_size);
char *tfb_fetch_entry2 (TFB_HANDLE *handle, char *key);
#endif /* _FILE_DEFINED */

/* tfb06.c ---------------------------------------------------------------- */
int cdecl tfb_get_tag_entry (const char *keyword,
                             const char *file_tfb, const char *file_lut,
                             char *line_buffer, char **field_fnm,
                             char **field_location, int MAX_LINE_BUFFER,
                             int kw_lng);

/* tfblut01.c ------------------------------------------------------------- */
int cdecl tfb_make_lut_file (char *tfb_file, char *lut_file,
                             int field_number, int field_delimiter,
                             int open_quote, int close_quote,
                             int escape_char, int ambigious_key,
                             int modification, int truncation,
                             int verbosity, int use_pos);

#endif /* __GG_tfb__ */
