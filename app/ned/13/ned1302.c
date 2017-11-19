/*
 *  FILE %ned/13/ned1302.c
 *
 *  written:       1997-08-04
 *  latest update: 1999-04-25 16:36:56
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <stdio.h>
#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_sgml_to_text (
char *fnm_txt,
char *fnm_ftr,
char *fnm_sgml)
{
  struct LINE *la, *lb;
  struct WINDOWCTRL wc;         /* temporary window */
  int flg2= 0;
  int rc;
  long la_offset;
  long lb_offset;

  wdw_rst (&wc);

  wc.file_format= FMT_SGML;
  rc= ned_f_read (&wc,
                  fnm_sgml, (char *) 0,
                  0, /* f_rd_ftr */
                  &la, &lb,
                  0L, 0x7FFFFFFFL);

  printf ("reading (%s): rc=%d\n", fnm_txt, rc);

  if (la == (struct LINE *) 0 || lb == (struct LINE *) 0)
  { /* READ ERROR */
    printf ("File not found! (ESC)");
    return -1;
  }

  wc.file_format= FMT_ASCII;
  rc= ned_f_write (&wc,
                   fnm_txt, fnm_ftr,
                   1, /* f_wr_ftr */
                   0, /* lz_flg */
                   la, lb,
                   &la_offset, &lb_offset,
                   flg2);

  printf ("writing (%s): rc=%d\n", fnm_sgml, rc);
  printf ("  begin=0x%08lX end=0x%08lX bytes=%ld\n",
          la_offset, lb_offset, lb_offset-la_offset+1);

  ned_lines_free (la);  /* T2D: more memory leaks?? */

  return 0;
}
