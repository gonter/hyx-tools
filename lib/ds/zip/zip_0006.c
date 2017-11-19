/*
 *  FILE %ds/zip/zs.c
 *
 *  ZIP Scanner; 
 *
 *  written:       1990 05 12
 *  latest update: 1995-12-25
 *  $Id: zip_0006.c,v 1.3 2009/10/13 12:59:25 gonter Exp $
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <gg/zip.h>

/* ------------------------------------------------------------------------ */
int zip_init_CDE (struct ZIP_CENTRAL_DIR_END *cde)
{
  cde->ZIP_CDE_zipfile_comment   = (char *) 0;

  cde->ZIP_CDE_sig_PK  = ZIP_sig_PK;
  cde->ZIP_CDE_sig_cde = ZIP_sig_cde;

  return 0;
}
