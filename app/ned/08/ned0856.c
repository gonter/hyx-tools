/*
 *  FILE %ned/08/ned0856.c
 *
 *  written:       1995-04-22
 *  latest update: 1997-01-15 14:29:25
 *  $Id: ned0856.c,v 1.2 2005/09/04 18:36:07 gonter Exp $
 *
 */

#ifdef MSDOS
/* #pragma check_stack(off) */
#endif

#include <sys/types.h>
#include <gg/strings.h>
#include <gg/filename.h>
#include <gg/tfb.h>
#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_lookup_current_feature (
char *token,                    /* string to be searched                    */
char *line_buffer,              /* string to hold feature buffer            */
char **feature_string,          /* pointer to feature string                */
char **feature_type,            /* type of the the feature string           */
int MAX_TOKEN,                  /* size of token string                     */
int MAX_BUFFER)                 /* size of line buffer                      */
{
  if (q_isolate_word (token, MAX_TOKEN, CHARSET_include, 1) == 0)
    return 2;

  return ned_lookup_feature (token, line_buffer, feature_string,
                             feature_type, MAX_BUFFER);
}
