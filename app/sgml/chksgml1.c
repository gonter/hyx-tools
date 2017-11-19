/*
 *  FILE %sgml/chksgml1.c
 *
 *  Identify (analyze) tags and entities, count them and report
 *
 *  written:       1991 07 14
 *                 1992 12 08: revision
 *  latest update: 1999-04-24 11:59:19
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/hytxt.h>

/* ------------------------------------------------------------------------ */
static char *HOC_TEXT1 [] =
{
  "undef",
  "Tags",
  "Entities",
  "Tags (total)",
  "Entities (total)"
} ;

/* ------------------------------------------------------------------------ */
static char *HOC_TEXT2 [] =
{
  "undef",
  "tag",
  "entity",
  "tag",
  "entity"
} ;

/* ------------------------------------------------------------------------ */
int hoc_print_counter (FILE *fo, struct HYX_OBJECT_COUNTER *x, int what)
{
  if (what < 1 || what > 4) return -1;

  fprintf (fo, "------ %s:\n", HOC_TEXT1 [what]);
  for (; x != (struct HYX_OBJECT_COUNTER *) 0; x= x->HOC_next)
  {
    if (x->HOC_cnt1 && (what == 1 || what == 2))
    {
      fprintf (fo, "%6ld %s \'%s\'",
               x->HOC_cnt1, HOC_TEXT2 [what], x->HOC_str);
      if (x->HOC_cnt1b) fprintf (fo, " (%ld within tags)", x->HOC_cnt1b);
      fputc ('\n', fo);
    }

    if (x->HOC_cnt2 && (what == 3 || what == 4))
    {
      fprintf (fo, "%6ld %s \'%s\'",
               x->HOC_cnt2, HOC_TEXT2 [what], x->HOC_str);
      if (x->HOC_cnt2b) fprintf (fo, " (%ld within tags)", x->HOC_cnt2b);
      fputc ('\n', fo);
    }
  }

  return 0;
}
