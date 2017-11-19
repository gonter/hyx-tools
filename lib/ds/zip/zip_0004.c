/*
 *  FILE %ds/zip/zip_0004.c
 *
 *  ZIP Scanner; 
 *
 *  written:       1990 05 12
 *  latest update: 1995-12-25
 *  $Id: zip_0004.c,v 1.3 2009/10/13 12:59:25 gonter Exp $
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <gg/zip.h>

/* ------------------------------------------------------------------------ */
int zip_init_LFH (struct ZIP_LOCAL_FILE_HEADER *lfh)
{
  lfh->ZIP_LFH_filename          = (char *) 0;
  lfh->ZIP_LFH_extra_field       = (char *) 0;

  lfh->ZIP_LFH_sig_PK  = ZIP_sig_PK;
  lfh->ZIP_LFH_sig_lfh = ZIP_sig_lfh;

  lfh->ZIP_LFH_next =
  lfh->ZIP_LFH_prev = (struct ZIP_LOCAL_FILE_HEADER *) 0;

  return 0;
}
