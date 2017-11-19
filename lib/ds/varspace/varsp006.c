/*
 *  FILE %ds/varspace/varsp006.c
 *
 *  variable space management
 *
 *  written:       1994-12-19
 *  latest update: 1996-01-21 23:39:56
 *  $Id: varsp006.c,v 1.2 2005/09/04 09:24:40 gonter Exp $
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
long vs_increment (
struct YTREE **yt_root,
char *var_name,                 /* variable name                            */
long value,                     /* increment value                          */
int pre_post,                   /* 1 -> return value before incrementing    */
int split_char)
{
  int nf;
  char *fields [MAX_VAR_SPACE_LEVELS];
  long rv= -1L;
  struct VAR_SPACE *vsp;

  if ((nf= split_string (var_name, split_char, fields, MAX_VAR_SPACE_LEVELS))
      > 0)
  {
    if (nf > MAX_VAR_SPACE_LEVELS) nf= MAX_VAR_SPACE_LEVELS;
    if ((vsp= vs_get_record (yt_root, fields, nf))
        == (struct VAR_SPACE *) 0) return -1L;

    rv= (long) vsp->VS_value;
    vsp->VS_type= ALty_long;
    value += rv;
    vsp->VS_value= (void *) value;
    if (pre_post == 0) rv= value;
  }

  return rv;
}
