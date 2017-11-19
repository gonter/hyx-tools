/*
 *  FILE ~/usr/sbr/copyfile.c
 *
 *  File Copy
 *  - see also: copyfil0.c
 *
 *  written:       1991 06 23
 *  latest update: 1994-07-17
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#include <io.h>
#endif

#include <stdio.h>
#include <gg/sbr.h>

static char *outmodes;

/* ------------------------------------------------------------------------ */
long copy_file (char *src, char *dst, int flags)
{
  FILE *fi;
  FILE *fo;
  int ch, ch2;
  long cnt= 0L;
  long write_pos;

  fi= fopen (src, (flags & COPY_FILE_in_text) ? "rt" : "rb");
  if (fi == (FILE *) 0) return -1L;

  if ((flags & COPY_FILE_dont_overwrite)
     && access (dst, 0) == 0) return -1L;

  fo= fopen (dst, 
        (flags & COPY_FILE_append)
        ? ((flags & COPY_FILE_out_text) ? "at" : "ab")
        : ((flags & COPY_FILE_out_text) ? "wt" : "wb"));

  if (fo == (FILE *) 0)
  {
ERR1:
    fclose (fi);
    return -1L;
  }

  fseek (fo, (long) 0, 2);
  write_pos= ftell (fo);

  for (;;)
  {
    ch= fgetc (fi) & 0x00FF;
    if (feof (fi)) break;
    fputc (ch, fo);
    cnt++;
  }

  fclose (fo);

  if (flags & COPY_FILE_verify)
  {
    fo= fopen (dst, (flags & COPY_FILE_out_text) ? "rt" : "rb");
    if (fo == (FILE *) 0) goto ERR1;
    fseek (fi, 0L, 0);
    fseek (fo, write_pos, 0);
    for (;;)
    {
      ch= fgetc (fi) & 0x00FF;
      ch2= fgetc (fi) & 0x00FF;
      if (feof (fi) && feof (fo)) break;
      if (feof (fi) || feof (fo) || ch != ch2)
      {
        fclose (fo);
        goto ERR1;
      }
    }
    fclose (fo);
  }

  fclose (fi);

  return cnt;
}
