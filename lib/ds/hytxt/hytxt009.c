/*
 *  FILE ~/usr/sgml/hytxt009.c
 *
 *  Purge a hypertext cluster, given are the filenames of the
 *  input cluster, input index, output cluster and output index.
 *  The calling routing must/will take care to erase/rename these files.
 *
 *  written:       1991 07 18
 *                 1992 12 07: extra buffers as a compile time option
 *  latest update: 1995-07-09
 *
 */

#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <gg/sbr.h>
#include <gg/hytxt.h>
#include <gg/lookup.h>
#include <gg/dpp.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

extern int errno;
#define EXTRA_BUFFERS
#ifdef EXTRA_BUFFERS
#include <stdlib.h>
#define BUFFER_SIZE 4096
#endif

/* ------------------------------------------------------------------------ */
int hyx_purge2 (
char *fni,
char *fni_tmp,
char *fnh,
char *fnh_tmp,
int verbose_level)
{
  FILE *fi_idx;
  FILE *fo_idx;
  FILE *fi_hyx;
  FILE *fo_hyx;
  long next_index;
  long current_index;
  long idxi_beg;
  long idxi_end;
  long idxi_cln;
  long idxo_beg;
  long idxo_end;
  long idxo_cln;
  struct stat st;
  int rv= -2;
#ifdef EXTRA_BUFFERS
  int extra_buffers= 0;
  char *buf_iidx= (char *) 0;
  char *buf_oidx= (char *) 0;
  char *buf_ihyx= (char *) 0;
  char *buf_ohyx= (char *) 0;
#endif

  if (stat (fni, &st) && errno == ENOENT)
  {
    fprintf (stderr, "error: index file is empty; nothing to do...\n");
    return -2;
  }
  next_index= st.st_size / 12L;

  if ((fi_idx= fopen (fni,     "rb")) == (FILE *) 0) goto ERR1;
  if ((fo_idx= fopen (fni_tmp, "wb")) == (FILE *) 0) goto ERR2;
  if ((fi_hyx= fopen (fnh,     "rb")) == (FILE *) 0) goto ERR3;
  if ((fo_hyx= fopen (fnh_tmp, "wb")) == (FILE *) 0) goto ERR4;

  rv= 0;

#ifdef EXTRA_BUFFERS
  buf_iidx= malloc (BUFFER_SIZE);
  buf_oidx= malloc (BUFFER_SIZE);
  buf_ihyx= malloc (BUFFER_SIZE);
  buf_ohyx= malloc (BUFFER_SIZE);
  if (buf_iidx && buf_oidx && buf_ihyx && buf_ohyx)
  {
    extra_buffers= 1;
    setvbuf (fi_idx, buf_iidx, _IOFBF, BUFFER_SIZE);
    setvbuf (fo_idx, buf_oidx, _IOFBF, BUFFER_SIZE);
    setvbuf (fi_hyx, buf_ihyx, _IOFBF, BUFFER_SIZE);
    setvbuf (fo_hyx, buf_ohyx, _IOFBF, BUFFER_SIZE);
  }
#endif

  fprintf (fo_hyx, "<ned.sgml enc=\"HYX\" ed=\"ned:3.00.20\" cs=\"IBM-PC\">\n");
  hyx_write_stamp (fo_hyx, "pgm=\"hyxpurge\"");
  fputc ('\n', fo_hyx);

  for (current_index = 0L;
       current_index < next_index;
       current_index++)
  {
    idxi_beg= dpp_fread_long (fi_idx, 4);
    idxi_end= dpp_fread_long (fi_idx, 4);
    idxi_cln= dpp_fread_long (fi_idx, 4);

    if (idxi_beg == -1L || (idxi_beg == 0L && idxi_end == 0L))
    {
      if (verbose_level >= 1)
        fprintf (stderr,
          "[0x%08lX] *dummy* begin=0x%08lX end=0x%08lX cluster=0x%lX\n",
          current_index, idxi_beg, idxi_end, idxi_cln);

      dpp_fwrite_long (fo_idx, idxi_beg, 4);
      dpp_fwrite_long (fo_idx, idxi_end, 4);
      dpp_fwrite_long (fo_idx, idxi_cln, 4);
      continue;
    }

    fseek (fi_hyx, idxi_beg, 0);
    idxo_beg= ftell (fo_hyx);
    ftransfer (fi_hyx, fo_hyx, idxi_end-idxi_beg+1L);
    idxo_end= ftell (fo_hyx)-1L;
    idxo_cln= idxi_cln;
    fputc (0x0A, fo_hyx);

    dpp_fwrite_long (fo_idx, idxo_beg, 4);
    dpp_fwrite_long (fo_idx, idxo_end, 4);
    dpp_fwrite_long (fo_idx, idxo_cln, 4);
  }

  fclose (fo_hyx);
ERR4:
  fclose (fi_hyx);
ERR3:
  fclose (fo_idx);
ERR2:
  fclose (fi_idx);
ERR1:

#ifdef EXTRA_BUFFERS
  if (extra_buffers)
  {
    free (buf_iidx);
    free (buf_oidx);
    free (buf_ihyx);
    free (buf_ohyx);
  }
#endif

  return rv;
}
