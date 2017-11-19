/*
 *  FILE %ds/hyxp/hyxp0032.c
 *
 *  Verwaltung von TAG Defintionen
 *
 *  written:       1994-12-22: isolated from parse002.c
 *  latest update: 1997-11-02 18:38:49
 *  $Id: hyxp0032.c,v 1.3 2004/05/08 15:40:21 gonter Exp $
 *
 */

#include <gg/parse.h>

#define MAX_TAG_STR 256 /* T2D: global constant! */

/* ------------------------------------------------------------------------ */
struct TAG_DEFINITION *hyx_identify_tag (
struct HYX_PARSER_CLASS *hpc,
char *str,
int append)                     /* 1 -> append, if not found */
{
  struct TAG_DEFINITION *t;
  char tag_str [MAX_TAG_STR];

#ifdef PARSER_DEBUG
printf ("hyxp0032.c: hyx_identify_tag (str='%s', append=%d')\n", str, append);
#endif /* PARSER_DEBUG */

  hyx_copy_tag (str, tag_str, MAX_TAG_STR, hpc->HPC_meta_flags & HPC_META_HTML);

  if ((t= hyx_find_tag_definition (hpc, tag_str))
       != (struct TAG_DEFINITION *) 0
      || !append /* if tag was not found and append is off, return NIL */
     )
    return t;

  t= hyx_make_tag_definition (hpc, tag_str, hpc->HPC_next_tag_id++, 0, 0L,
                              (str [0] == '/') ? TAG_TYPE_endtag
                                               : TAG_TYPE_nonrecursive,
                              (char *) 0);

  return t;
}

/* ------------------------------------------------------------------------ */
int hyx_copy_tag (
char *src,
char *dst,
int size,
int lower)
{
  int ch;
  int lng= 0;

  size--;
  for (;;)
  {
    ch= *src++;
    if (ch == 0
        || size <= 0
        || ch == ' '  || ch == '\t'
        || ch == '\r' || ch == '\n'
       ) break; /* T2D: space general! */
    *dst++= ch;
    lng++;
  }
  *dst= 0;

  return lng;
}
