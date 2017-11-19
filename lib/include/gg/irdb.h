/*
 *  include FILE <gg/irdb.h>
 *
 *  irrelational database
 *  - prototypes
 *
 *  written:       1996-04-05
 *  latest update: 1996-11-26 17:46:46
 *
 */

#ifndef __GG_irdb__
#define __GG_irdb__

/* ------------------------------------------------------------------------ */
#include <stdio.h>
#include <gg/ytree.h>
#include <gg/floskel.h>

#define DEBUG0
/* #define IRDB_USE_CLASS_NAME ... used for what ??? */

/* ------------------------------------------------------------------------ */
#ifdef _FILE_DEFINED
struct IRDB_DUMP
{
  long type;
  FILE *fo;
  int indent;
} ;
#endif /* _FILE_DEFINED */

/* ------------------------------------------------------------------------ */
struct IRDB_HANDLE
{
  long IRDB_type;                       /* IRDBty_*                         */

  long IRDB_payload_size;               /* in bytes                         */
  long IRDB_payload;                    /* pointer or offset in bytes       */
  long IRDB_payload_type;               /* for array and struct IRDBty_*    */

#ifdef IRDB_USE_CLASS_NAME
  char *IRDB_class_name;
#endif /* IRDB_USE_CLASS_NAME */
} ;

/* ------------------------------------------------------------------------ */
#ifdef _FILE_DEFINED
struct IRDB_POS                         /* Persistant Objest Store          */
{
  struct IRDB_HANDLE *IRDB_handle;
  char *IRDB_file_name;
  FILE *IRDB_file;
  int IRDB_open_mode;                   /* see IRDBom_*                     */
  int IRDB_is_new;
} ;
#endif /* _FILE_DEFINED */

/* IRDBty_*: -------------------------------------------------------------- */
#define IRDBty_int              1
#define IRDBty_float            2
#define IRDBty_string           3
#define IRDBty_string_dumped    4       /* string dumped to file            */
#define IRDBty_struct           5
#define IRDBty_struct_dumped    6       /* structure dumped to file         */
#define IRDBty_array            7
#define IRDBty_array_dumped     8       /* array dumped to file             */
#define IRDBty_block            9
#define IRDBty_block_dumped    10

/* IRDBom_*: -------------------------------------------------------------- */
#define IRDBom_closed           1
#define IRDBom_read             2
#define IRDBom_write            3
#define IRDBom_overwrite        4

/* prototypes: ------------------------------------------------------------ */
/* 0001 */ long irdb_dump_to_file (char *filename,
             struct IRDB_HANDLE *handle);

#ifdef _FILE_DEFINED
/* 0002 */ long irdb_dump_to_stream (FILE *fo, struct IRDB_HANDLE *handle);
/* 0003 */ long irdb_dump_payload (FILE *fo, struct IRDB_HANDLE *handle);
/* 0004 */ long irdb_dump_string (FILE *fo, char *s);
#endif /* _FILE_DEFINED */

#ifdef _YTREE_DEFINED
/* 0005 */ int irdb_dump_struct (struct YTREE *yt, char *str, void *cd);
#endif /* _YTREE_DEFINED */

#ifdef _FILE_DEFINED
/* 0006 */ long irdb_commit (struct IRDB_POS *pos);
#endif /* _FILE_DEFINED */

/* 0007 */ long irdb_dumped_form (long type);
/* 0008 */ long irdb_core_form (long type);
/* 0009 */ struct IRDB_POS *irdb_new_pos (char *fnm, char *cln, int is_new);
/* 0010 */ struct IRDB_HANDLE *irdb_new_handle (long ty, char *cln);
/* 0011 */ struct IRDB_HANDLE *irdb_new_struct_handle (char *cln,
             long payload_type);
/* 0012 */ int irdb_store_to_struct (struct IRDB_HANDLE *hnd,
             char *slot, long value);
/* 0013 */ int irdb_strdup_to_struct (struct IRDB_HANDLE *hnd,
             char *slot, char *value);

#ifdef _FILE_DEFINED
/* 0014 */ long *irdb_locate_info (struct IRDB_POS *pos,
             char *slots[], int slot_cnt, int create, long ty);
/* 0015 */ int irdb_exists (struct IRDB_POS *pos,
             char *slots[], int slot_cnt);
/* 0016 */ int irdb_replace_string (struct IRDB_POS *pos,
             char *slots[], int slot_cnt, char *value);
/* 0017 */ struct IRDB_HANDLE *irdb_locate_handle (struct IRDB_POS *pos,
             char *slots[], int slot_cnt, int create, long ty);
/* 0018 */ long irdb_set_long (struct IRDB_POS *pos,
             char *slots[], int slot_cnt, long value);
/* 0019 */ long irdb_post_increment_long (struct IRDB_POS *pos,
             char *slots[], int slot_cnt, long value);
/* 0020 */ long irdb_pre_increment_long (struct IRDB_POS *pos,
              char *slots[], int slot_cnt, long value);
#endif /* _FILE_DEFINED */

/* 0021 */ long irdb_fixup_pos_header (char *filename,
             struct IRDB_HANDLE *handle);
/* 0022 */ struct IRDB_HANDLE *irdb_load_handle (FILE *fi);
/* 0023 */ char *irdb_load_string (FILE *fi, char *buffer, int bsize);

#ifdef _FILE_DEFINED
/* 0024 */ FILE *irdb_get_pos_file_pointer (struct IRDB_POS *pos,
             int open_mode);
/* 0025 */ int irdb_restore (struct IRDB_POS *pos, struct IRDB_HANDLE *hnd);
#endif /* _FILE_DEFINED */

/* 0026 */ int irdb_restore_handle (struct YTREE *yt_node, void *client_data);
/* 0027 */ int irdb_restore_strings (struct YTREE *yt_node,
             void *client_data);

#ifdef _FILE_DEFINED
/* 0028 */ long irdb_get_increment_long (struct IRDB_POS *pos,
             char *slots[], int slot_cnt);
/* 0101 */ long irdb_diag (FILE *fo, struct IRDB_HANDLE *handle);
/* 0102 */ long irdb_diag_to_stream (FILE *fo, struct IRDB_HANDLE *handle,
              int indent);
/* 0103 */ long irdb_diag_payload (FILE *fo, struct IRDB_HANDLE *handle,
             int indent);
/* 0104 */ long irdb_diag_string (FILE *fo, char *s);
/* 0105 */ int irdb_diag_struct (struct YTREE *yt, char *str, void *cd);
/* 0107 */ long irdb_dbg_show_slot_names (FILE *fo, char *slots[],
             int slot_cnt);
#endif /* _FILE_DEFINED */
/* 0106 */ char *irdb_type (long type);

/* 0112 */ int irdb_dbg_store_to_struct (struct IRDB_HANDLE *hnd,
             char *slot, long value);

#ifdef _FILE_DEFINED
/* 0116 */ int irdb_dbg_replace_string (struct IRDB_POS *pos,
             char *slots[], int slot_cnt, char *value);
/* 0118 */ long irdb_dbg_set_long (struct IRDB_POS *pos,
             char *slots[], int slot_cnt, long value);
/* 0119 */ long irdb_dbg_post_increment_long (struct IRDB_POS *pos,
             char *slots[], int slot_cnt, long value);
/* 0120 */ long irdb_dbg_pre_increment_long (struct IRDB_POS *pos,
              char *slots[], int slot_cnt, long value);
#endif /* _FILE_DEFINED */

#endif /* __GG_irdb__ */
