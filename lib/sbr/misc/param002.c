/*
 *  FILE %sbr/param002.c
 *
 *  this function is also defined as macro in <gg/dpp.h>
 *
 *  written:       1993-04-06: cnt, renamed
 *  latest update: 1995-11-02
 *  $Id: param002.c,v 1.3 2005/09/04 20:27:37 gonter Exp $
 *
 */

#define NO_MACRO
#include <gg/dpp.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
long get_parameter_value (const char *s)
{
  return _get_parameter_value (s, 1024);
}
