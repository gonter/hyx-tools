/*
 *  FILE %ds/rdtp/rdtp0116.c
 *
 *  restructured dynamic text parser
 *
 *  written:       1996-04-02
 *  latest update: 1996-04-02 18:48:38
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/rdtp.h>
#include <gg/rdtp01.h>

/* ------------------------------------------------------------------------ */
int rdtp_print_state_entry (
FILE *fo,
struct RDTP_STATE_TRANSITION *tr,
char *pfx)
{
  long beg;
  long end;

  beg= tr->range_begin;
  end= tr->range_end;

  fputs (pfx, fo);
  if (beg > 0x20 && beg < 0x7F && end > 0x20 && end < 0x7F)
  {
    if (beg == end)
      fprintf (fo, "[%c]", (int) beg);
    else
      fprintf (fo, "[%c..%c]", (int) beg, (int) end);
  }
  else
  {
    fprintf (fo, "[0x%02lX..0x%02lX]", beg, end);
  }

  fprintf (fo, " -> %s", tr->state_to);
  if (tr->method_info != (char *) 0)
    fprintf (fo, " (%s)", tr->method_info);
  fputc ('\n', fo);

  return 0;
}
