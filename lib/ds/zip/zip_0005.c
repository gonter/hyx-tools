/*
 *  FILE %ds/zip/zs.c
 *
 *  ZIP Scanner; 
 *
 *  written:       1990 05 12
 *  latest update: 1995-12-25
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <gg/zip.h>

/* ------------------------------------------------------------------------ */
int zip_init_CFH (struct ZIP_CENTRAL_FILE_HEADER *cfh)
{
  cfh->ZIP_CFH_filename          = (char *) 0;
  cfh->ZIP_CFH_extra_field       = (char *) 0;
  cfh->ZIP_CFH_file_comment      = (char *) 0;

  cfh->ZIP_CFH_sig_PK  = ZIP_sig_PK;
  cfh->ZIP_CFH_sig_cfh = ZIP_sig_cfh;

  cfh->ZIP_CFH_next =
  cfh->ZIP_CFH_prev = (struct ZIP_CENTRAL_FILE_HEADER *) 0;

  return 0;
}
