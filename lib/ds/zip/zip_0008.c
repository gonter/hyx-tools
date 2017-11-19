/*
 *  FILE %ds/zip/zip_0008.c
 *
 *  ZIP Scanner; 
 *
 *  written:       1995-12-26
 *  latest update: 1995-12-26
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <gg/strings.h>
#include <gg/zip.h>

/* ------------------------------------------------------------------------ */
int zip_delete_control (struct ZIP_CONTROL *zc)
{
  struct ZIP_LOCAL_FILE_HEADER *lfh1, *lfh2;
  struct ZIP_CENTRAL_FILE_HEADER *cfh1, *cfh2;

  if (zc == (struct ZIP_CONTROL *) 0) return -1;

  free_or_what (zc->ZIPC_filename);

  for (lfh1= zc->ZIPC_LFH;
       lfh1 != (struct ZIP_LOCAL_FILE_HEADER *) 0;
       lfh2= lfh1)
  {
    lfh2= lfh1->ZIP_LFH_next;
    free_or_what (lfh1->ZIP_LFH_filename);
    free_or_what (lfh1->ZIP_LFH_extra_field);
    free (lfh1);
  }

  for (cfh1= zc->ZIPC_CFH;
       cfh1 != (struct ZIP_CENTRAL_FILE_HEADER *) 0;
       cfh2= cfh1)
  {
    cfh2= cfh1->ZIP_CFH_next;
    free_or_what (cfh1->ZIP_CFH_filename);
    free_or_what (cfh1->ZIP_CFH_extra_field);
    free_or_what (cfh1->ZIP_CFH_file_comment);
    free (cfh1);
  }

  if (zc->ZIPC_CDE != (struct ZIP_CENTRAL_DIR_END *) 0)
  {
    free_or_what (zc->ZIPC_CDE->ZIP_CDE_zipfile_comment);
    free (zc->ZIPC_CDE);
  }

  free (zc);

  return 0;
}
