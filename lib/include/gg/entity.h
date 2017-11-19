/*
 *  include FILE <gg/entity.h>
 *
 *  entity definitions
 *
 *  written:       1991 06 21
 *                 1993-01-01: revision
 *  latest update: 1996-06-09 11:26:21
 *
 */

#ifndef __GG_entity__
#define __GG_entity__

#include <gg/ytree.h>
#include <gg/floskel.h>

/* structures: ------------------------------------------------------------ */
struct ENTITY_DESCRIPTOR
{
  int type;                     /* ED_TYPE_*                                */
  long code;                    /* character code, if defined               */
  char *name;                   /* Entity Name                              */
  char *string;                 /* Entity Declaration accoring to type      */

  void *system_data;
  void *application_data;
} ;

#define ED_TYPE_string       1  /* simple replacement string (PCDATA??)     */
#define ED_TYPE_CDATA        2  /* character data                           */
#define ED_TYPE_SDATA        3  /* specific data                            */
#define ED_TYPE_PI           4  /* processing instruction                   */
#define ED_TYPE_SYSTEM       5  /* system entity identifier                 */
#define ED_TYPE_PUBLIC       6  /* public entity identifier                 */
#define ED_TYPE_PARAM        7  /* parameter entity                         */
#define ED_TYPE_STARTTAG     8  /*                                          */
#define ED_TYPE_ENDTAG       9  /*                                          */
#define ED_TYPE_MS          10  /*                                          */
#define ED_TYPE_MD          11  /*                                          */

/* References:                                                              */
/* [2] The SGML Implementation Guide; p. 250 ff                             */

/* ------------------------------------------------------------------------ */
struct ENTITY_DESCRIPTOR_LIST
{
  struct ENTITY_DESCRIPTOR_LIST *next;
  struct ENTITY_DESCRIPTOR *ed;
} ;

/* ------------------------------------------------------------------------ */
struct ENTITY_CONTEXT
{
  char *ec_name;

  struct ENTITY_DESCRIPTOR_LIST *edl;
  struct ENTITY_DESCRIPTOR_LIST **edl_append;

  struct ENTITY_DESCRIPTOR *ec_tbl [256];
  struct YTREE *ec_names;
  struct YTREE *ec_codes;
} ;

/* prototypes: ------------------------------------------------------------ */
struct ENTITY_CONTEXT *cdecl entity_create_context (char *name);
int cdecl cdecl entity_destroy_context (struct ENTITY_CONTEXT *ec);
struct ENTITY_DESCRIPTOR *cdecl entity_find_by_name (
  struct ENTITY_CONTEXT *ctx, char *name);
struct ENTITY_DESCRIPTOR *cdecl entity_find_by_code (
  struct ENTITY_CONTEXT *ctx, long code);

/* ***** REVISION NEEDED BELOW THIS LINE (1996-06-09 11:22:47) ************ */
/* prototypes ------------------------------------------------------------- */
#define SE_N_char 8             /* number of def'ed character code families */

/* prototypes ------------------------------------------------------------- */
struct SGML_ENTITY
{
  int SE_group;                 /* Entity Group                             */
  char *SE_entity_name;         /* character string of entity               */
  long SE_char [SE_N_char];     /* character code in family                 */
} ;

/* prototypes ------------------------------------------------------------- */
#define SEG_undef       0       /* undefine entity group                    */
#define SEG_ISOlat1     1       /* entities for latin alphabetic characters */
                                /* used in western european languages       */
#define SEG_ISOlat2     2       /* aditional entities for latin alphabetic  */
                                /* characters                               */
#define SEG_ISOgrk1     3
#define SEG_ISOgrk2     4
#define SEG_ISOcyr1     5
#define SEG_ISOcyr2     6
#define SEG_ISOnum      7       /* numerical and special characters         */
#define SEG_ISOdia      8
#define SEG_ISOpub      9
#define SEG_ISObox     10
#define SEG_ISOtech    11
#define SEG_ISOgrk3    12
#define SEG_ISOgrk4    13
#define SEG_ISOamso    14
#define SEG_ISOamsb    15
#define SEG_ISOamsr    16
#define SEG_ISOamsn    17
#define SEG_ISOamsa    18
#define SEG_ISOamsc    19

/* IBM-PC character codes - - - - - - - - - - - - - - - - - - - - - - - - - */
#define SE_char_pc              SE_char[0]
#define SE_fam_pc               0

/* Apple Macintosh character codes  - - - - - - - - - - - - - - - - - - - - */
#define SE_char_mac             SE_char[1]
#define SE_fam_mac              1

/* character codes as defined with Donald Knuth's TeX - - - - - - - - - - - */
#define SE_char_tex             SE_char[2]
#define SE_fam_tex              2

/* character codes as defined with GG's fontdir system  - - - - - - - - - - */
#define SE_char_fontdir         SE_char[3]
#define SE_fam_fontdir          3

/* character codes in German EBCDIC - - - - - - - - - - - - - - - - - - - - */
#define SE_char_ebcdic_german   SE_char[4]
#define SE_fam_ebcdic_german    4

/* character codes in US EBCDIC - - - - - - - - - - - - - - - - - - - - - - */
#define SE_char_ebcdic_us       SE_char[5]
#define SE_fam_ebcdic_us        5

/* character codes in German EBCDIC (translated)  - - - - - - - - - - - - - */
#define SE_char_ebcdic_tgerman  SE_char[6]
#define SE_fam_ebcdic_tgerman   6

/* character codes in US EBCDIC (translated)  - - - - - - - - - - - - - - - */
#define SE_char_ebcdic_tus      SE_char[7]
#define SE_fam_ebcdic_tus       7

/* prototypes ------------------------------------------------------------- */
char *cdecl sgml_char_to_entity (long tchar, int tfam);
long cdecl sgml_entity_to_char (char *entity, int tfam);
int cdecl sgml_char_to_entity_group (long tchar, int tfam);
int cdecl sgml_entity_to_entity_group (char *entity);
long cdecl sgml_translit (long tchar_from, int tfam_from, int tfam_to);

#endif /* __GG_entity__ */
