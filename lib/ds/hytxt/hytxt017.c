/*
 *  FILE %ds/hytxt/hytxt017.c
 *
 *  written:       1994-02-04
 *  latest update: 1996-01-01
 *
 */

#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <gg/hytxt.h>

/* ------------------------------------------------------------------------ */
long hyx_get_last_index (char *fnm)
{
  struct stat st;
  int rc;

  rc= stat (fnm, &st); /* index file */
  if (rc == -1) return -1L;
  return (st.st_size / HYXIDX_REC_SIZE) -1L;
}
