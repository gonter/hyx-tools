/*
 *  FILE %ned/08/ned0882.c
 *
 *  select a name for the cross reference
 *
 *  written:       1991 10 23
 *  latest update: 1999-04-25 16:33:57
 *  $Id: ned0882.c,v 1.3 2005/09/04 18:36:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <stdlib.h>
#include <gg/strings.h>
#include "ed.h"
#include "proto.h"

#define MAX_STR 128

extern char *default_cross_ref_prefix;
extern int default_cross_ref_to_lower;
extern char *default_help_cluster;
extern char *default_help_cross_ref;

/* ------------------------------------------------------------------------ */
struct CB_DATA
{
  int ty;
  int loc;
  int lower;
} ;

/* ------------------------------------------------------------------------ */
int ned_cb_cross_ref (
char *edited_string,
int size,
int malloced,
void *callback_data)
{
  int ty= CRF_IN_CRF;
  int loc= CRF_GLOBAL_AND_LOCAL;
  int lower= 1;
  struct CB_DATA *cb;
#ifdef MSDOS
  size; malloced; callback_data;
#endif

  if ((cb= (struct CB_DATA *) callback_data) != (struct CB_DATA *) 0)
  {
    ty= cb->ty;
    loc= cb->loc;
    lower= cb->lower;
    free (cb);
  }

  if (lower && default_cross_ref_to_lower) to_lower (edited_string);
  ned_activate_cross_ref (edited_string, 1, ty, loc);

  return 0;
}

/* ------------------------------------------------------------------------ */
int ned_cross_ref (
const char *target,
int prompt,             /* -1 .. never prompt                               */
                        /*  0 .. dont prompt unless its necessary           */
                        /*  1 .. prompt in any case                         */
int ty,
int loc,
int lower)
{
  char str [MAX_STR];
  int lng= 0;
  int rv;

  if (ty == 0) ty= CRF_IN_CRF;
  if (loc == 0) loc= CRF_GLOBAL_AND_LOCAL;

  if (default_cross_ref_prefix != (char *) 0
      && *default_cross_ref_prefix != 0
      && ty == CRF_IN_CRF
     )
  {
    strcpy_max (str, default_cross_ref_prefix, MAX_STR);
    lng= strlen (default_cross_ref_prefix);
  }
  else str [0]= 0;

  if (target != (char *) 0)
  {
    if (*target == 0) { if (prompt == 0) prompt= 1; }
    else strcpy_max (str+lng, target, MAX_STR-lng);
  }
  else
  {
    if ((rv= q_isolate_word (str+lng, MAX_STR-lng, CHARSET_token, 1)) == 0
        && prompt == 0
       )
      prompt= 1;
  }

  if (prompt == 1)
  {
    struct CB_DATA *cb;

    if ((cb= (struct CB_DATA *) calloc (sizeof (struct CB_DATA), 1))
        != (struct CB_DATA *) 0)
    {
      cb->lower= lower;
      cb->ty= ty;
      cb->loc= loc;
    }

    ned_prompt_string ("lookup: ", str, MAX_STR,
                       default_help_cluster, default_help_cross_ref,
                       ned_cb_cross_ref, (void *) cb);
    return 0;
  }

  if (lower && default_cross_ref_to_lower) to_lower (str);
  ned_activate_cross_ref (str, 1, ty, loc);

  return 0;
}
