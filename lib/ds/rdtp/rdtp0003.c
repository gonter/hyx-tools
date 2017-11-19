/*
 *  FILE %ds/rdtp/rdtp0003.c
 *
 *  restructured dynamic text parser
 *
 *  written:       1996-04-02
 *  latest update: 1996-04-02 15:26:58
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/rdtp.h>

/* ------------------------------------------------------------------------ */
long rdtp_parse_file (
struct RDTP_THREAD *thread,
char *fnm,
long beg,
long size)
{
  FILE *fi;
  long rc;

  if ((fi= fopen (fnm, "rb")) == (FILE *) 0) return -1L;

  fseek (fi, beg, 0L);
  rc= rdtp_parse_stream (thread, fi, size);
  fclose (fi);

  return rc;
}
