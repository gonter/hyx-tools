/*
 *  FILE %gg/work/gg/lib/ds/lutctl/lutctl02.c
 *
 *  written:       2001-11-20
 *  latest update: 2001-11-20 19:33:18
 *  $Id: lutctl02.c,v 1.1 2001/11/20 19:32:43 gonter Exp $
 *
 */

#include <stdlib.h>
#include <string.h>
#include <gg/lutctl.h>

/* ------------------------------------------------------------------------ */
int lutctl_set_filename (struct LUTCTL *p, char *fnm)
{
  if (p == (LUTCTL *) 0) return -1;
  if (p->filename != (char *) 0) free (p->filename);

  if ((p->filename= strdup (fnm)) == (char *) 0) return -1;

  return 0;
}

/* ------------------------------------------------------------------------ */
int lutctl_open (struct LUTCTL *p)
{
  FILE *fp;

  if (p == (LUTCTL *) 0
      || (fp= fopen (p->filename, "rb")) == (FILE *) 0
     ) return -1;

  p->state= LUTCTL_state_file;

  return 0;
}

/* ------------------------------------------------------------------------ */
int lutctl_close (struct LUTCTL *p)
{
  if (p == (LUTCTL *) 0) return -1;

  /* T2D: error, if fp == NULL ?? */
  if (p->fp != (FILE *) 0) { fclose (p->fp); p->fp= (FILE *) 0; }

  return 0;
}

/* ------------------------------------------------------------------------ */
int lutctl_load (struct LUTCTL *p, long limit)
{
  char *buffer= (char *) 0;
  long bytes;

  if (p == (LUTCTL *) 0
      || p->filename == (char *) 0
      /** || p->state != LUTCTL_state_file ??? */
     ) return -1;

  if (limit != 0L) p->limit= limit;

  if (p->mem != (char *) 0)
  {
    free (p->mem);
    p->mem= (char *) 0;
  }

  bytes= read_file2buffer (&buffer, p->filename, p->limit);
  if (bytes == -1)
  {
    if (buffer != (char *) 0) free (buffer);
    /* NOTE: read_file2buffer may allocate the buffer,  */
    /*       even if it returns an error.               */
    return -1;
  }
  p->mem= buffer;
  p->size= bytes;
  p->state= LUTCTL_state_mem;

  return 0;
}
