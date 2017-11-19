/*
 *  FILE %ds/zip/zip_0003.c
 *
 *  ZIP Scanner; 
 *
 *  written:       1990 05 12
 *  latest update: 1995-12-25
 *  $Id: zip_0003.c,v 1.3 2009/10/13 12:59:25 gonter Exp $
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/zip.h>

/* initialze ZIP control structure ---------------------------------------- */
struct ZIP_CONTROL *zip_init_control (char *fnm)
{
  struct ZIP_CONTROL *zc= (struct ZIP_CONTROL *) 0;
  char *cp;

  if (fnm != (char *) 0
      && *fnm != 0
      && (zc= calloc (sizeof (struct ZIP_CONTROL), 1))
         != (struct ZIP_CONTROL *) 0
      && (cp= strdup (fnm)) != (char *) 0
     )
  {
    /* information about the ZIP file */
    zc->ZIPC_filename = cp;
    zc->ZIPC_status   = 0;

    /* information from the ZIP file */
    zc->ZIPC_LFH      = (struct ZIP_LOCAL_FILE_HEADER   *) 0;
    zc->ZIPC_LFH_app  = &zc->ZIPC_LFH;
    zc->ZIPC_CFH      = (struct ZIP_CENTRAL_FILE_HEADER *) 0;
    zc->ZIPC_CFH_app  = &zc->ZIPC_CFH;
    zc->ZIPC_CDE      = (struct ZIP_CENTRAL_DIR_END     *) 0;
  }

  return zc;
}
