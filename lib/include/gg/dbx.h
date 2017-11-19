/*
 *  include FILE <gg/dbx.h>
 *
 *  methods
 *  data structures
 *  constants
 *  prototypes
 *
 *  written:       1996-11-26
 *  latest udpate: 1996-11-26 17:42:13
 *
 */

#ifndef __GG_dbx__
#define __GG_dbx__

#include <gg/array.h>
#include <gg/floskel.h>

/* methods: --------------------------------------------------------------- */

/* ------------------------------------------------------------------------ */
struct DBX_FIELD_DESCRIPTOR
{
  int type;
  char *name;
  int size;
} ;

#define DBX_Fty_undef   0
#define DBX_Fty_string  1
#define DBX_Fty_long    2

/* data structures: ------------------------------------------------------- */
struct DBX_SCHEMA
{
  char *name;
  int n_fields;
  struct DBX_FIELD_DESCRIPTOR *fields [2];      /* n_fields fields !!!      */
} ;

/* ------------------------------------------------------------------------ */
struct DBX_RECORD
{
  struct DBX_SCHEMA *schema;
  int n_fields;
  void *fields [2];                     /* n_fields fields !!!              */
} ;

/* ------------------------------------------------------------------------ */
struct DBX_FILE_DESCRIPTOR
{
  int type;
  char *fnm;

  void *fi1;                    /* stream descriptor 1 */

  struct DBX_SCHEMA *schema;

  int is_fixed_record_size;
  long record_size;
  long header_size;
} ;

/* ------------------------------------------------------------------------ */
/* specific for DBF Files: */
#define DBX_DBF_PFX_SIZE 32
#define DBX_DBF_FDESC_SIZE 32
#define DBX_DBF_NAME_SIZE 11
#define DBX_DBF_off_hdr_size 0x08
#define DBX_DBF_off_rec_size 0x0A

#define DBX_DBF_off_name     0x00
#define DBX_DBF_off_fld_type 0x0B
#define DBX_DBF_off_fld_size 0x10

#ifdef __COMMENT__
The DBF header consists of a 32 byte prefix followed by a series of
field descriptors.

The prefix contains at offset:

DBX_DBF_off_hdr_size    0x08 .. 0x09    header_size
DBX_DBF_off_rec_size    0x0A .. 0x0B    record_size

Each field descriptor is 32 byte long and contains at offset:

DBX_DBF_off_name        0x00 .. 0x0A    name
DBX_DBF_off_fld_type    0x0B            field_type_code
DBX_DBF_off_fld_size    0x10 .. 0x11    field_size

The number of fields is header_size/32 -1
Known field type codes are: C..character, N..numeric
The first data record starts at (header_size+1)

#endif /* __COMMENT__ */

/* ------------------------------------------------------------------------ */
#define dbx_new_field_descriptor()     \
  ((struct DBX_FIELD_DESCRIPTOR *)      \
   calloc (sizeof (struct DBX_FIELD_DESCRIPTOR), 1))

#define dbx_new_file_descriptor()     \
  ((struct DBX_FILE_DESCRIPTOR *)      \
   calloc (sizeof (struct DBX_FILE_DESCRIPTOR), 1))

/* prototypes: ------------------------------------------------------------ */
struct DBX_SCHEMA *dbx_new_schema (int n_fields, char *name);
struct DBX_FILE_DESCRIPTOR *dbx_open_dbf (char *fnm, char *name);

#endif /* __GG_dbx__ */
