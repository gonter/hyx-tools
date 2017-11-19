/*
 *  FILE ~/usr/sgml/chksgml6.c
 *
 *  Identify (analyze) tags and entities, count them and report
 *
 *  written:       1991 07 14
 *                 1992 12 08: revision
 *  latest update: 1995-03-12
 *
 */

#include <gg/hytxt.h>

/* ------------------------------------------------------------------------ */
int hoc_reset_counter (struct HYX_OBJECT_COUNTER *x)
{
  for (; x != (struct HYX_OBJECT_COUNTER *) 0; x= x->HOC_next)
  {
    x->HOC_cnt1= 0L;
    x->HOC_cnt1b= 0L;
  }

  return 0;
}
