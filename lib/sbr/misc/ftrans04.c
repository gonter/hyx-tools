/*
 *  FILE %sbr/ftrans04.c
 *
 *  Transfer some range of a file to another one as a SHAR file block
 *  see also %sbr/ftrans.c
 *
 *  written:       1994-07-23: extracted from %usr/utl/shar.c
 *  latest update: 1996-10-13 20:38:34
 *
 */

#include <stdio.h>
#include <gg/sbr.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
long ftransfer_to_shar (
FILE *fi,
FILE *SHAR,
char *fnm,
long cpy_size,
char *st_dat_buffer)
{
  int ch;
  long fsiz= 0L;
  int status= 0;

  fprintf (SHAR, "echo shar: extracting %s\n", fnm);
  fprintf (SHAR, "sed 's/^X//' << \\SHAR_EOF > %s\n", fnm);

  for (; cpy_size > 0L; cpy_size--)
  {
    ch= fgetc (fi) & 0x00FF;
    if (feof (fi)) break;
    if (status == 0) fputc ('X', SHAR);
    status= 1;
    fputc (ch, SHAR);
    fsiz++;
    if (ch == 0x0A) status= 0;
  }

  if (status != 0) fputc (0x0A, SHAR);

  fprintf (SHAR, "SHAR_EOF\n");

/*fprintf (SHAR, "echo shar: file %s expected size %ld byte\n", fnm, fsiz);*/
/*fprintf (SHAR, "if test %ld -ne \"\`wc -c %s\`\"\n", fsiz, fnm);*/

  if (st_dat_buffer != (char *) 0 && *st_dat_buffer)
  {
    fprintf (stderr, "[%s] ", st_dat_buffer);
    fprintf (SHAR, "touch -t%s %s\n", st_dat_buffer, fnm);
  }
  fprintf (SHAR, "if test %ld -ne \"`cat %s | wc -c`\"\n", fsiz, fnm);
  fprintf (SHAR, "then\n");
  fprintf (SHAR, "echo shar: error transmitting %s: %ld byte expected!\n",
                 fnm, fsiz);
  fprintf (SHAR, "fi\n");

  return fsiz;
}
