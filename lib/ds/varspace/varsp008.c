/*
 *  FILE %ds/varspace/varsp008.c
 *
 *  variable space management
 *
 *  written:       1994-12-26
 *  latest update: 1996-01-21 23:42:36
 *  $Id: varsp008.c,v 1.2 2005/09/04 09:24:40 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <sys/types.h>
#include <gg/strings.h>
#include <gg/varspace.h>
#include <gg/attlist.h>
/* #include <gg/ytree.h> ... included by <gg/varspace.h> */

/* ------------------------------------------------------------------------ */
struct VAR_SPACE *vs_query (
struct YTREE *yt_root,
char *var_name,
int split_char)
{
  int nf;
  char *fields [MAX_VAR_SPACE_LEVELS];

  if ((nf= split_string (var_name, split_char, fields, MAX_VAR_SPACE_LEVELS))
      > 0)
  {
    if (nf > MAX_VAR_SPACE_LEVELS) nf= MAX_VAR_SPACE_LEVELS;
    return vs_get (yt_root, fields, nf);
  }

  return (struct VAR_SPACE *) 0;
}
