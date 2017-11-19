/*
 *  FILE %sbr/file2buf.c
 *
 *  read a file to buffer
 *
 *  written:       1992-12-27: <Gerhard.Gonter@wu-wien.ac.at>
 *  latest update: 1995-12-10
 *  $Id: file2buf.c,v 1.3 2001/11/20 19:32:46 gonter Exp $
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <gg/diagnose.h>
#include <gg/fileio.h>

/* ------------------------------------------------------------------------ */
long read_file2buffer (char **buffer, char *fnm, long limit)
{
  FILE *fi;
  struct stat stat_buf;
  char *b;                      /* handle for *buffer */
  int rc;
  long bytes_read;

  if (fnm == (char *) 0 || *fnm == 0)
  {
    gg_diagnose= EF_not_found;
    return -1L;
  }

  if ((rc= stat (fnm, &stat_buf)) == -1)
  {
    gg_diagnose= EF_couldnt_stat;
    return -1L;
  }

  if (limit <= 0 || stat_buf.st_size > limit)
  {
    gg_diagnose= EB_size_exceeded;
    return -1L;
  }

  /* first: see if file can really be read, then allocate the buffer */
  if ((fi= fopen (fnm, "rb")) == (FILE *) 0)
  {
    gg_diagnose= EF_not_found;
    return -1L;
  }

  if ((b= *buffer) == (char *) 0)
  {
    limit= stat_buf.st_size+1;
    if ((b= malloc ((int) limit)) == (char *) 0)
    {
      gg_diagnose= EM_no_memory;
      fclose (fi);
      return -1L;
    }
    *buffer= b;
  }

  bytes_read= fread (b, 1, (int) stat_buf.st_size, fi);
  fclose (fi);

  if (bytes_read < limit) b [limit]= 0;

  return bytes_read;
}
