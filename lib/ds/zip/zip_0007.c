/*
 *  FILE %ds/zip/zip_0007.c
 *
 *  ZIP Scanner; 
 *
 *  written:       1990 05 12
 *  latest update: 1995-12-25
 *  $Id: zip_0007.c,v 1.3 2009/10/13 12:59:25 gonter Exp $
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <gg/strings.h>
#include <gg/dpp.h>
#include <gg/zip.h>

/* ------------------------------------------------------------------------ */
int zip_scan (struct ZIP_CONTROL *zc)
/* RETURN:   0 ... OK                           */
/*          -1 ... unexpected EOF               */
/*          -2 ... unknonw ZIP-Substructure     */
/*          -3 ... this is not a ZIP-File       */
/*         -10 ... no more memory               */
/*        -100 ... ZIP control invalid          */
/*        -101 ... ZIP filename invalid         */
/*        -102 ... ZIP file could not be opened */
{
  FILE *fi;
  int return_value= 0;
  unsigned char sig_1, sig_2, sig_3, sig_4;
  struct ZIP_LOCAL_FILE_HEADER     *lfh;
  struct ZIP_CENTRAL_FILE_HEADER   *cfh;
  struct ZIP_CENTRAL_DIR_END       *cde;
#ifdef MAIN
  long pos;
#endif

  if (zc == (struct ZIP_CONTROL *) 0)    return -100;
  if (zc->ZIPC_filename == (char *) 0)
  {
    return_value = -101;
    goto OVER;
  }

  fi= fopen (zc->ZIPC_filename, "rb");
  if (fi == (FILE *) 0)
  {
#ifdef MAIN
  printf ("zip file %s NOT opened\n", zc->ZIPC_filename);
#endif
    return_value = -102;
    goto OVER;
  }
#ifdef MAIN
  printf ("zip file %s opened\n", zc->ZIPC_filename);
#endif

  for (;;)
  {
#ifdef MAIN
    pos= ftell (fi);
#endif
    sig_1= fgetc (fi) & 0x00FF;
    sig_2= fgetc (fi) & 0x00FF;
    sig_3= fgetc (fi) & 0x00FF;
    sig_4= fgetc (fi) & 0x00FF;
#ifdef MAIN
printf ("pos=%ld sig=[%02X %02X %02X %02X]\n", pos, sig_1, sig_2, sig_3, sig_4);
#endif
    if (feof (fi))
    {
#ifdef MAIN
      printf ("EOF at 0x%08lX\n", pos);
#endif
      return_value = -1;
      break;
    }

    if (sig_1 == 'P' && sig_2 == 'K')
    {
      if (sig_3 == ZIP_sig_lfh1 && sig_4 == ZIP_sig_lfh2)
      {
          *(zc->ZIPC_LFH_app)= lfh= malloc (sizeof (struct ZIP_LOCAL_FILE_HEADER));
          if (lfh == (struct ZIP_LOCAL_FILE_HEADER *) 0)
          {
            return_value = -10;
            goto OVER1;
          }

          zip_init_LFH (lfh);
          fread (&lfh->ZIP_LFH, 1, sizeof (struct ZIP_local_file_header), fi);
          lfh->ZIP_LFH_filename= read_string (fi, lfh->ZIP_LFH.ZIP_LFH_filename_length);
          lfh->ZIP_LFH_extra_field= read_string (fi, lfh->ZIP_LFH.ZIP_LFH_extra_field_length);
          fseek (fi, lfh->ZIP_LFH.ZIP_LFH_compressed_size, 1);
#ifdef MAIN
          printf ("LFH at 0x%08lX: %s %s (fnm_lng=0x%08lX)\n", pos,
                  lfh->ZIP_LFH_filename, lfh->ZIP_LFH_extra_field,
                  lfh->ZIP_LFH.ZIP_LFH_filename_length);
#endif
      }
      else if (sig_3 == ZIP_sig_cfh1 && sig_4 == ZIP_sig_cfh2)
      {
          *(zc->ZIPC_CFH_app)= cfh= malloc (sizeof (struct ZIP_CENTRAL_FILE_HEADER));
          if (cfh == (struct ZIP_CENTRAL_FILE_HEADER *) 0)
          {
            return_value = -10;
            goto OVER1;
          }

          zip_init_CFH (cfh);
          fread (&cfh->ZIP_CFH, 1, sizeof (struct ZIP_central_file_header), fi);
          cfh->ZIP_CFH_filename= read_string (fi, cfh->ZIP_CFH.ZIP_CFH_filename_length);
          cfh->ZIP_CFH_extra_field= read_string (fi, cfh->ZIP_CFH.ZIP_CFH_extra_field_length);
          cfh->ZIP_CFH_file_comment= read_string (fi, cfh->ZIP_CFH.ZIP_CFH_file_comment_length);
#ifdef MAIN
          printf ("CFH at 0x%08lX: %s %s %s\n", pos,
                  cfh->ZIP_CFH_filename, cfh->ZIP_CFH_extra_field,
                  cfh->ZIP_CFH_file_comment);
#endif
      }
      else if (sig_3 == ZIP_sig_cde1 && sig_4 == ZIP_sig_cde2)
      {
          zc->ZIPC_CDE= cde= malloc (sizeof (struct ZIP_CENTRAL_DIR_END));
          if (cde == (struct ZIP_CENTRAL_DIR_END *) 0)
          {
            return_value= -10;
            goto OVER1;
          }

          zip_init_CDE (cde);
          fread (&cde->ZIP_CDE, 1, sizeof (struct ZIP_central_dir_end), fi);
          cde->ZIP_CDE_zipfile_comment= read_string (fi, cde->ZIP_CDE.ZIP_CDE_zipfile_comment_length);
#ifdef MAIN
  printf ("CDE at 0x%08lX: %s\n", pos, cde->ZIP_CDE_zipfile_comment);
  printf ("              CFH-Start 0x%08lX with %d entries %ld bytes\n",
                         cde->ZIP_CDE.ZIP_CDE_cfh_start_offset,
                         cde->ZIP_CDE.ZIP_CDE_cfh_count,
                         cde->ZIP_CDE.ZIP_CDE_cfh_size);
#endif
      }
      else
      {
#ifdef MAIN
          printf ("Unknown ZIP sub structure 0x%02X 0x%02X at offset 0x%08lX\n",
                  sig_3, sig_4, pos);
#endif
          return_value = -2;
          goto OVER1;
      }
    }
    else
    {
      return_value = -3;
      goto OVER1;
    }
  }

OVER1:
  fclose (fi);
OVER:
  zc->ZIPC_status= return_value;

#ifdef MAIN
  printf ("zip file %s closed; return_value=%d\n", zc->ZIPC_filename, return_value);
#endif
  return return_value;
}
