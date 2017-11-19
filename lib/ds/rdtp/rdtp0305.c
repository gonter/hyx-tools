/*
 *  FILE %ds/rdtp/rdtp0305.c
 *
 *  restructured dynamic text parser
 *
 *  written:       1996-06-22
 *  latest update: 1997-01-15 10:56:28
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/rdtp.h>
#include <gg/rdtp01.h>
#include <gg/rdtp03.h>

/* ------------------------------------------------------------------------ */
int sgml_collect (void *thrp, int ch)
{
  struct SGML_BUILDUP *sb;
  struct RDTP_THREAD *thr;

  if ((thr= (struct RDTP_THREAD *) thrp) == (struct RDTP_THREAD *) 0
      || (sb= (struct SGML_BUILDUP *) thr->payload)
         == (struct SGML_BUILDUP *) 0
     )
  {
    fprintf (stderr, "rdtp0305: bad thread\n");
    return -1;
  }

  if (sb->bl1_cnt >= TMP_BL_SIZE -1) sgml_flush_buffer (sb);

  sb->bl1 [sb->bl1_cnt++]= (char) ch;

  return 0;
}

/* ------------------------------------------------------------------------ */
int sgml_collect2 (struct RDTP_THREAD *thr, int ch)
{
  sgml_collect (thr, '<');
  return sgml_collect (thr, ch);
}

/* ------------------------------------------------------------------------ */
int sgml_collect3 (struct RDTP_THREAD *thr, int ch)
{
  sgml_collect (thr, ']');
  return sgml_collect (thr, ch);
}

/* ------------------------------------------------------------------------ */
int sgml_collect3b (struct RDTP_THREAD *thr, int ch)
{
  sgml_collect (thr, ']');
  sgml_collect (thr, ']');
  return sgml_collect (thr, ch);
}

/* ------------------------------------------------------------------------ */
int sgml_collect4 (struct RDTP_THREAD *thr, int ch)
{
  sgml_collect (thr, '&');
  sgml_collect (thr, '#');
  return sgml_new_element (thr, ch);
}

/* ------------------------------------------------------------------------ */
int sgml_collect5 (struct RDTP_THREAD *thr, int ch)
{
  sgml_collect (thr, '-');
  return sgml_collect (thr, ch);
}
