/*
 *  FILE %ds/rdtp/rdtp0312.c
 *
 *  restructured dynamic text parser
 *
 *  written:       1996-06-23
 *  latest update: 1996-06-23 10:25:26
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <stdio.h>
#include <gg/rdtp.h>
#include <gg/rdtp03.h>

/* ------------------------------------------------------------------------ */
int sgml_flush_buffer (struct SGML_BUILDUP *rtf)
{
  rtf->bl1 [rtf->bl1_cnt++]= 0;

  printf ("T2D flushing buffer: '%s'\n", rtf->bl1);
  rtf->bl1_cnt= 0;

  return 0;
}
