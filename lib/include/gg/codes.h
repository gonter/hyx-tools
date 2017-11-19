/*
 *  include FILE <gg/codes.h>
 *
 *  data structures and functions to manipulate code sets
 *  - prototypes
 *
 *  written:       1992-12-25: <Gerhard.Gonter@wu-wien.ac.at>
 *  latest update: 1995-12-10
 *
 */

#ifndef __GG_codes__
#define __GG_codes__

#include <gg/floskel.h>

/* ------------------------------------------------------------------------ */
struct CS_field
{
  struct CS_field *CSf_next;            /* next field in the list           */
  char *CSf_name;                       /* name of the attribute            */
  void *CSf_info;                       /* hook for additional information  */
  long  CSf_type;                       /* type of the attribute value      */
#define CSft_undefined          0       /*   no value defined               */
#define CSft_number             1       /*   integer number                 */
#define CSft_string             2       /*   double quoted string           */
#define CSft_identifier         3       /*   identifier string              */
#define CSft_count              4       /* number of different types        */
  char *CSf_string;                     /* string value attribute           */
  long  CSf_number;                     /* integer value of attribute       */
} ;

/* ------------------------------------------------------------------------ */
struct CS_record
{
  struct CS_record *CSr_next;           /* next record in the list          */
  struct CS_field *CSr_fields;          /* list of fields in that record    */
  void *CSr_info;                       /* hook for additional information  */
  long CSr_count;                       /* number of fields in record       */
  long CSr_offset_dat;                  /* offset in data file              */
  long CSr_offset_str;                  /* offset in string file            */
} ;

/* ------------------------------------------------------------------------ */
struct CS_attribute_statistics
{
  struct CS_attribute_statistics *CSa_next;
  char *CSa_name;                       /* name of the attribute            */
  long CSa_tcnt [CSft_count];           /* total number of given type       */
  long CSa_ucnt [CSft_count];           /* number of used given type        */
} ;

/* ------------------------------------------------------------------------ */
struct CS_tlate_table                   /* string translation table         */
{
  char *CStt_table_name;                /* informal name of the table       */
  char *CStt_file_name;                 /* name of the file that holds data */
  char *CStt_table [256];               /* translation table                */
} ;

/* ------------------------------------------------------------------------ */
/* entity translation structure for translation of 8-bit coding blocks      */
struct CS_ET8
{
  long CS_et8_table_id;         /* numerical id of a given translation tbl  */
  int CS_et8_error_flag;        /* != 0 -> something terrible has happened  */

  char *CS_et8_lut_fnm;         /* name of file containing entity->code tbl */
  char *CS_et8_lut;             /* entity to code table                     */
  long CS_et8_lut_size;         /* size of the table                        */

  char *CS_et8_index_fnm;       /* name of the file containing offset tbl   */
  long *CS_et8_index;           /* offset into string buffer for given code */
                                /* this table has always 256 entries        */

  char *CS_et8_string_fnm;      /* name of the file containing strings      */
  char *CS_et8_string_buffer;   /* string buffer for the needed entities    */
  long CS_et8_string_size;      /* size of the buffer                       */
} ;

#ifdef MSDOS
#define MAX_CS_ET8_SIZE 0x00007FF0L
#else
#define MAX_CS_ET8_SIZE 0x10000000L
#endif

/* Code Set Field IDs: ---------------------------------------------------- */
#define CSfid_ascii     0x61736369L     /* ASCII code                       */
#define CSfid_pc        0x70630000L     /* standard pc code (--> 437)       */
#define CSfid_pc437     0x70630437L     /* standard code page               */
#define CSfid_pc850     0x70630850L     /* multilingual code page           */
#define CSfid_mac       0x6D163000L     /* macintosh codes                  */
#define CSfid_ebcdic    0xEBCD1C00L     /* standard ebcdic                  */
#define CSfid_ebcdic_gr 0xEBCD1C67L     /* german ebcdic                    */
#define CSfid_ebcdic_en 0xEBCD1C65L     /* english ebcdic                   */
#define CSfid_iso8859   0x00885900L
#define CSfid_iso8859_1 0x00885901L
#define CSfid_iso8859_2 0x00885902L
#define CSfid_iso10646  0x01064600L
#define CSfid_tex       0x74657800L     /* tex  ... plain TeX               */
#define CSfid_latex     0x7465786CL     /* texl ... LaTeX                   */
#define CSfid_amstex    0x74657861L     /* texa ... AMS-TeX                 */
#define CSfid_latex_gr  0x74657847L     /* texG ... german documentstyle    */
#define CSfid_tex_f     0x74657866L     /* texf ... TeX fonts               */

#define CSfid_entity    0x00887965L
#define CSfid_entityset 0x00887973L

#define CSfid_catn      0x6361746EL     /* catn ... category names          */
#define CSfid_catc      0x63617463L     /* catc ... category codes          */
#define CSfid_catf1     0x63617431L     /* cat1 ... category flags 1        */
#define CSfid_catf2     0x63617432L     /* cat2 ... category flags 2        */

/* filenames: ------------------------------------------------------------- */
#define CSF_TABLE               "codes/table"
#define CSF_PC_INDEX            "codes/entpc437.idx"
#define CSF_PC_STRINGS          "codes/entpc437.str"
#define CSF_PC_COMPACT_LUT      "codes/entpc437.lut"
#define CSF_8859_1_INDEX        "codes/ent88591.idx"
#define CSF_8859_1_STRINGS      "codes/ent88591.str"

/* prototypes: ------------------------------------------------------------ */
/* cs001 */ struct CS_record *cdecl cs_parse_code_table (char *fn,
              char *matching_field [], int field_cnt, int filter,
              int max_warnings);
/* cs001 */ long cdecl cs_tnum_records (void);
/* cs001 */ long cdecl cs_unum_records (void);
#ifdef _FILE_DEFINED
/* cs002 */ long cdecl cs_print_records (FILE *fo, struct CS_record *recs);
/* cs003 */ long cdecl cs_print_fields (FILE *fo, struct CS_field *fields);
#endif
/* cs004 */ int cdecl cs_records2ytree (struct CS_record *recs, char *field[],
              long tags[], int fields, char *lut_file, char *data_file,
              int verbose, int compact, int all);
/* cs005 */ int cdecl cs_records2index (struct CS_record *recs, char *field[],
              int fields, char *index_file, char *data_file, int verbose);
/* cs006 */ int cdecl cs_records2table (struct CS_record *recs,
              char *src_attr[], int src_attr_cnt, char *dst_attr[],
              int dst_attr_cnt, int table_type, long *table);
/* cs006 */ int cdecl set_common_base (int flag);
/* cs007 */ struct CS_field *cdecl cs_find_field (struct CS_record *first,
              char *f1_name, int f1_type, char *f1_string, long f1_number,
              char *f2_name);
/* cs008 */ int cdecl cs_free_fields (struct CS_field *csf,
              /* void (*free_info) (void *), */
              int free_names, int free_values);
/* cs009 */ int cdecl cs_count_attribute (char *attribute, int atype,
              int used);
/* cs009 */ struct CS_attribute_statistics
              *cdecl cs_get_attribute_statistics (void);
/* cs009 */ void cdecl cs_reset_attribute_statistics (void);
#ifdef _FILE_DEFINED
/* cs010 */ int cdecl cs_print_statistics (FILE *fo);
/* cs011 */ long cdecl cs_print_frames (FILE *fo, struct CS_record *recs);
/* cs012 */ long cdecl cs_print_frame (FILE *fo, struct CS_field *fields);
#endif

/* cs101 */ int cdecl INIT_get_sgml_entity (char *fnm_idx, char *fnm_str);
/* cs101 */ int cdecl KILL_get_sgml_entity (void);
/* cs101 */ char *cdecl get_sgml_entity (int ch);

/* cs102 */ int cdecl INIT_find_sgml_entity (char *fnm_lut);
/* cs102 */ int cdecl KILL_find_sgml_entity (void);
/* cs102 */ int cdecl find_sgml_entity (char *entity);

/* cs103 */ struct CS_ET8 *cdecl cs_et8_create_table (long table_id,
             char *fnm_dat, char *fnm_idx, char *fnm_lut);
/* cs104 */ int cdecl cs_et8_destroy_table (struct CS_ET8 *et8);
/* cs105 */ char *cs_et8_code2entity (struct CS_ET8 *et8, int ch);
/* cs106 */ int cdecl cs_et8_entity2code (struct CS_ET8 *et8, char *entity);
#ifdef _FILE_DEFINED
/* cs107 */ long cdecl cs_et8_fputc (struct CS_ET8 *et8, int ch, FILE *fo);
/* cs108 */ long cdecl cs_et8_fputs (struct CS_ET8 *et8, char *str, FILE *fo);
/* cs109 */ long cdecl cs_et8_ftransfer (struct CS_ET8 *et8,
              FILE *fi, FILE *fo, long cpy_size);
#endif /* _FILE_DEFINED */
/* cs110 */ long cdecl cs_et8_encode (struct CS_ET8 *et8,
              char *fni, char *fno, long cpy_size);

#ifdef _FILE_DEFINED
/* cs201 */ long cdecl cs_convert_stream (FILE *fi, FILE *fo,
              long *table, long limit);
#endif
/* cs202 */ int cdecl cs_convert_file (char *fni, char *fno, long *table);
/* cs203 */ long cdecl cs_convert_string (char *str, long *table);

/* cs204 */ int cs_string_tlate (char *dst, char *src, int dst_size,
              struct CS_tlate_table *tt);
/* cs205 */ struct CS_tlate_table *cs_load_tlate_table (
              char *file_name, char *table_name);
#ifdef _FILE_DEFINED
/* cs206 */ int cdecl cs_print_tlate_table (FILE *fo, char *file_name,
              char *table_name);
#endif

/* cs207 */ long cdecl cs_convert_block (char *str, long size, long *table);

#endif /* __GG_codes__ */
