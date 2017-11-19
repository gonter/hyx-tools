/*
 *  FILE %ds/hyxp/hyxp0034.c
 *
 *  Verwaltung von TAG Defintionen
 *
 *  written:       1991 03 12
 *                 1996-02-18 extracted from parse027.c
 *  latest update: 2001-02-18 19:36:54
 *  $Id: hyxp0034.c,v 1.3 2001/02/19 00:27:54 gonter Exp $
 *
 */

#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/ytree.h>
#include <gg/parse.h>

/* ------------------------------------------------------------------------ */
struct TAG_DEFINITION *hyx_find_tag_definition (
struct HYX_PARSER_CLASS *hpc,
char *str)
{
  struct YTREE *yt;
  char *str_lookup;

  str_lookup= (*str == ':') ? ":" : str;        /* special frame start tag */

  if ((yt= ytree_lookup_word (hpc->HPC_tags, str_lookup)) != (struct YTREE *) 0
      && (yt->YT_flags & YTflag_EOW))
    return (struct TAG_DEFINITION *) yt->YT_info;

  return (struct TAG_DEFINITION *) 0;
}
