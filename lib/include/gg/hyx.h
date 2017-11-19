/*
 *  include FILE <gg/hyx.h>
 *
 *  HYX structure manipulation
 *
 *  written:       1993-03-07
 *  latest update: 1997-06-16 11:00:53
 *  $Id: hyx.h,v 1.2 2010/05/04 02:47:07 gonter Exp $
 *
 */

#ifndef __GG_hyx__
#define __GG_hyx__

#include <gg/floskel.h>

/* ------------------------------------------------------------------------ */
struct SGML_ATTRIBUTE
{
  struct SGML_ATTRIBUTE *next;
  int type;                             /* see note: SAt_*                  */
#define SAt_undef               0
#define SAt_NED                 1       /* like Frame names                 */
#define SAt_normal              2
/* Note: more types as specified in the SGML ref                            */
  int flags;                            /* bitfield: SAf_*                  */
#define SAf_name_malloced       0x01
#define SAf_value_malloced      0x02
#define SAf_value_squoted       0x10
#define SAf_value_dquoted       0x20
#define SAf_value_escaped       0x40
  char *name;
  char *value;
} ;

/* ------------------------------------------------------------------------ */
struct SGML_TAG2
{
  int type;                             /* STt_* */
  char *tag_name;
  void *tag_def;
  struct TAG_ATTRIUBTE *list;
  struct TAG_ATTRIUBTE **app;
} ;

/* prototypes for library functions of %usr/ds/hyx: ----------------------- */
/* 0001 */ char *cdecl find_attr_name (char *str, char *name);
/* 0002 */ int cdecl get_attr_value (char *src, char *dst, int dst_lng,
             int flags);
/* 0003 */ int cdecl find_attr_value (char *src, char *dst, int dst_size,
                                      char *name);

/* 0004 */ long hyx_identify_color_code (unsigned char *s);
           long hyx_set_color_code (unsigned char *name, long value);
#define identify_colour_code(colour_value) \
  ((int) hyx_identify_color_code((unsigned char *) colour_value))

/* 0101 */ int cdecl hyx_rule_calendar (const char *token,
             char **res_string, char **res_type, void *client_data);

#endif /* __GG_hyx__ */
