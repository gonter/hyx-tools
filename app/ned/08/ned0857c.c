/*
 *  FILE %ned/08/ned0857c.c
 *
 *  implements the cache for ned_lookup_feature ()
 *
 *  written:       1996-11-03
 *  latest update: 1999-04-25 16:33:37
 *  $Id: ned0857c.c,v 1.4 2010/05/04 02:47:07 gonter Exp $
 *
 */

#ifdef MSDOS
/* #pragma check_stack(off) */
#endif

#include <stdlib.h>
#include <string.h>
#include <gg/ytree.h>
#include <gg/strings.h>
#include <gg/filename.h>
#include <gg/tfb.h>
#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
struct YTREE *features= (struct YTREE *) 0;

/* ------------------------------------------------------------------------ */
int ned_lookup_feature_cache (
const char *token,              /* string to be searched                    */
char **feature_string,          /* pointer to feature string                */
char **feature_type)            /* type of the the feature string           */
{
  struct NED_FLC *flc;

  if ((flc= (struct NED_FLC *)
            ytree_get_value (features, (unsigned char *) token))
        != (struct NED_FLC *) 0)
  {
    *feature_string= flc->str;
    *feature_type= flc->ty;

    return 1;
  }

  return 0;
}

/* ------------------------------------------------------------------------ */
int ned_store_feature_cache (
const char *token,              /* string to be searched                    */
const char *feature_string,     /* pointer to feature string                */
const char *feature_type)       /* type of the the feature string           */
{
  struct NED_FLC *flc;

  if ((flc= new_ned_flc ()) == (struct NED_FLC *) 0) return -1;

  flc->ty= strdup (feature_type);
  flc->str= strdup (feature_string);

  if ((flc= (struct NED_FLC *)
        ytree_set_value (&features, (unsigned char *) token, (long) flc))
      != (struct NED_FLC *) 0)
  { /* something else was stored before */
    free_or_what (flc->ty);
    free_or_what (flc->str);
    free_or_what (flc);
  }

  return 0;
}
