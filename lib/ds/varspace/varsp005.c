/*
 *  FILE %ds/varspace/varsp005.c
 *
 *  variable space management
 *
 *  written:       1994-12-19
 *  latest update: 1997-11-02 13:03:26
 *  $Id: varsp005.c,v 1.2 2005/09/04 09:24:40 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <sys/types.h>
#include <gg/strings.h>
#include <gg/varspace.h>
/** #include <gg/attlist.h> **/
/* #include <gg/ytree.h> ... included by <gg/varspace.h> */

/* ------------------------------------------------------------------------ */
int vs_assign (
struct YTREE **yt_root,
char *var_name,
long value,
long var_type,
int split_char)
{
  int nf;
  char *fields [MAX_VAR_SPACE_LEVELS];

  if ((nf= split_string (var_name, split_char, fields, MAX_VAR_SPACE_LEVELS))
      > 0)
  {
    if (nf > MAX_VAR_SPACE_LEVELS) nf= MAX_VAR_SPACE_LEVELS;
    if (vs_set (yt_root, fields, nf, var_type, value)
        == (struct VAR_SPACE *) 0) return -1;
  }

  return 0;
}
