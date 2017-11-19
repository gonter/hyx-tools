/*
 *  FILE %sgml/chksgml5.c
 *
 *  Identify (analyze) tags and entities, count them and report
 *
 *  written:       1991 07 14
 *                 1992 12 08: revision
 *  latest update: 1999-04-24 11:59:47
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/hytxt.h>

/* ------------------------------------------------------------------------ */
int analyze_entity (
char *entity,
int what,
struct HYX_OBJECT_COUNTER **x_app)
{
  struct HYX_OBJECT_COUNTER *x;
  int rc;

  for (; (x= *x_app) != (struct HYX_OBJECT_COUNTER *) 0; x_app= &x->HOC_next)
  {
    if ((rc= strcmp (x->HOC_str, entity)) == 0)
    {
      x->HOC_cnt1++;
      x->HOC_cnt2++;
      if (what == 2)
      {
        x->HOC_cnt1b++;
        x->HOC_cnt2b++;
      }
      return 1;
    }
    if (rc > 0) break;
  }

  if ((x= (struct HYX_OBJECT_COUNTER *)
          calloc (sizeof (struct HYX_OBJECT_COUNTER), 1))
      == (struct HYX_OBJECT_COUNTER *) 0) return -1;

  x->HOC_str= strdup (entity);
  x->HOC_cnt1= 1L;
  x->HOC_cnt2= 1L;
  if (what == 2)
  {
    x->HOC_cnt1b= 1L;
    x->HOC_cnt2b= 1L;
  }

  x->HOC_next= *x_app;
  *x_app= x;

  return 0;
}
