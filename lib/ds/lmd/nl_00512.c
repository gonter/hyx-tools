/*
 *  FILE %ds/lmd/nl_00512.c
 *
 *  manipulate word information data structures
 *
 *  written:       1995-07-18
 *  latest update: 1996-08-08 17:23:51
 *  $Id: nl_00512.c,v 1.2 2001/08/26 23:26:04 gonter Exp $
 *
 */

#include <stdio.h>
#include <gg/ytree.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
struct INTPR
{
  char *I_name;
  long I_code;
} ;

/* ------------------------------------------------------------------------ */
static struct YTREE *ytree= (struct YTREE *) 0;
static int initialized= 0;

/* ------------------------------------------------------------------------ */
static struct INTPR intpr [] =
{
  { "and",      WRint_logic_and } ,
  { "or",       WRint_logic_or  } ,
  { "und",      WRint_logic_and } ,
  { "oder",     WRint_logic_or  } ,
  { (char *) 0, 0L              }
} ;

/* ------------------------------------------------------------------------ */
long lmd_get_interpretation (char *s)
{
  struct YTREE *yt;
  int i;

  if (!initialized)
  {
#ifdef DEBUG
    printf ("lmd_get_interpretation: initializing lexicon\n");
#endif /* DEBUG */

    initialized= 1;
    for (i= 0; intpr [i].I_name != (char *) 0; i++)
    {
      if ((yt= ytree_insert_word (&ytree, (unsigned char *) intpr [i].I_name))
          != (struct YTREE *) 0)
      {
        yt->YT_info= intpr [i].I_code;
        yt->YT_flags |= YTflag_EOW;
      }
    }
  }

  if ((yt= ytree_lookup_word (ytree, (unsigned char *) s))
           != (struct YTREE *) 0
      && (yt->YT_flags & YTflag_EOW))
  {
#ifdef DEBUG
    printf ("lmd_get_interpretation: code=0x%08lX\n", yt->YT_info);
#endif /* DEBUG */
    return yt->YT_info;
  }

  return WRint_null;
}
