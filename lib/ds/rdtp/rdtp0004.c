/*
 *  FILE %ds/rdtp/rdtp0004.c
 *
 *  restructured dynamic text parser
 *
 *  written:       1996-04-02
 *  latest update: 1996-04-02 21:18:10
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/rdtp.h>

/* ------------------------------------------------------------------------ */
long rdtp_parse_stream (
struct RDTP_THREAD *thread,
FILE *fi,
long size)
{
  int ch;
  int rc;
  long cnt= 0L;
#ifdef RDTP_DEBUG
  long line_cnt= 1L;
#endif /* RDTP_DEBUG */

  if (thread == (struct RDTP_THREAD *) 0) return -1L;

#ifdef RDTP_DEBUG
  printf ("char ch  cl state      -> state      act\n");
#endif /* RDTP_DEBUG */

  while (size-- > 0L)
  {
    ch= fgetc (fi) & 0x00FF;
    if (feof (fi)) break;

#ifdef RDTP_DEBUG
    if (ch == 0x0A)
    {
      line_cnt++;
    }
    printf ("0x%08lX %5ld: ", cnt, line_cnt++);
#endif /* RDTP_DEBUG */

    rc= rdtp_parse_char (thread, ch);
    if (rc != 0) break;
    cnt++;
  }

  return cnt;
}
