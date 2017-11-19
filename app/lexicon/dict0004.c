/*
 *  FILE %lexicon/dict0004.c
 *
 *  written:       1994-12-10: isolated from dictadd1.c
 *  latest update: 2000-08-26 15:16:48
 *  $Id: dict0004.c,v 1.6 2004/05/08 15:40:34 gonter Exp $
 *
 */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <gg/ytree.h>
#include <gg/hytxt.h>
#include <gg/parse.h>
#include <gg/lookup.h>
#include <gg/dpp.h>
#include <gg/sbr.h>

extern int errno;
static int add_to_ytree (char *w, long idx, void *client_data);

/* ------------------------------------------------------------------------ */
static char entry_key [ENTRY_KEY_SIZE];

#define MAX_KILL 32
static long  kill_by_id [MAX_KILL];
static int   kill_by_id_cnt= 0;
static char *kill_by_lx [MAX_KILL];
static int   kill_by_lx_cnt= 0;

/* ------------------------------------------------------------------------ */
static int add_to_ytree (char *w, long idx, void *client_data)
{
  ytree_set_value ((struct YTREE **) client_data,
                          (unsigned char *) w, idx);

  return 0;
}

/* ------------------------------------------------------------------------ */
int dict_add_init (struct HYX_CLUSTER_CONTROL *hcc)
{
  FILE *f;
  struct stat st;
  int rc;

  if (hcc->HCC_dictadd1_inited) return 0;

  printf ("dict_add_init  mode=%d\n", hcc->HCC_dict_mode);

  if (hcc->HCC_dict_mode != DAMODE_MERGE
      && hcc->HCC_dict_mode != DAMODE_REPLACE) goto SKIP1;

  /* read kill file for entries to be killed by ID code */
  kill_by_id_cnt= fread_integer_table_file (hcc->HCC_fnm_kill_by_id,
                    kill_by_id, MAX_KILL, entry_key, ENTRY_KEY_SIZE);

  /* read kill file for entries to be killed by entry string */
  kill_by_lx_cnt= fread_string_table_file (hcc->HCC_fnm_kill_by_lx,
                    kill_by_lx, MAX_KILL, entry_key, ENTRY_KEY_SIZE);

  if (hcc->HCC_lut_mode == HCC_lm_full_write)
  { /* Main LUT File einlesen */
    char *fnm_lut= hcc->HCC_fnm_lut;
    printf ("dict0004: scanning LUT %s ...", fnm_lut);

#define x_DOES_NOT_WORK
#ifdef DOES_NOT_WORK
    if ((f= fopen (fnm_lut, "rb")) != (FILE *) 0)
    {
/*********
printf (
"ytree_full_scan (f, &hcc->HCC_ytree, %d, kill_by_id, %d, kill_by_lx);\n",
kill_by_id_cnt, kill_by_lx_cnt);
*********/

/****
      ytree_full_scan (f, &hcc->HCC_ytree,
                       kill_by_id, kill_by_id_cnt,
                       kill_by_lx, kill_by_lx_cnt);
****/

/*****/
      ytree_scan (f, &hcc->HCC_ytree);
/*****/

      /*** lut_scan_file (f, &hcc->HCC_ytree, 0L); ****/
      fclose (f);
    }
#else
    hcc->HCC_ytree= lut_scan_ytree (fnm_lut, 0L);
#endif

    printf ("done; OK!\n");
/**** DEBUGGING ONLY *****/
      if ((f= fopen ("@@@.lut", "wb")) != (FILE *) 0)
      {
printf ("dumping ytree\n");
        ytree_size (hcc->HCC_ytree);
        ytree_dump (f, hcc->HCC_ytree);
        close (f);
        /*** exit (0); ****/
      }

    if (xfn_process (hcc->HCC_fnm_xfn, add_to_ytree,
                     (void *) &hcc->HCC_ytree, 0L) == 0)
      printf ("dict0004: scanning XFN %s ...done; OK", hcc->HCC_fnm_xfn);

    /* repack index information from YTREE into ENTRY_DESCRIPTOR structure */
    printf ("repacking YTREE ...");
    ytree_process (hcc->HCC_ytree, ytree_index_to_entry_descriptor,
                   (void *) 0);
    printf (" done\n");
  }

  if (hcc->HCC_lut_mode == HCC_lm_incremental)
  {
    hcc->HCC_f_lut= fopen (hcc->HCC_fnm_lut, "rb");
    hcc->HCC_f_xfn= fopen (hcc->HCC_fnm_xfn, "r");
  }

  /* naechsten moeglichen Index bestimmen */
  printf ("dict0004: checking index file %s;\n", hcc->HCC_fnm_idx);
  rc= stat (hcc->HCC_fnm_idx, &st);
  if (rc == -1 && errno == ENOENT)
  { /* Index File existiert noch nicht; anlegen */
    if ((f= fopen (hcc->HCC_fnm_idx, "wb")) != (FILE *) 0)
    {
      dpp_fwrite_long (f, -1L, 4);
      dpp_fwrite_long (f, -1L, 4);
      dpp_fwrite_long (f, -1L, 4);
      fclose (f);
      hcc->HCC_next_index= 1L;
      printf ("        : writing dummy index 0x00000000;\n");
    }
    else
    {
      fprintf (stdout, "ERROR: couldn't write dummy index %s!!\n",
               hcc->HCC_fnm_idx);
    }
  }
  else
  {
    hcc->HCC_next_index= st.st_size / sizeof (struct LEXICON_INDEX);
  }
  printf ("        : next index= 0x%lX; ... OK!\n", hcc->HCC_next_index);

  /* HYX File vorbehandeln, wenn nicht vorhanden */
  printf ("dictadd: checking lexicon file %s; ", hcc->HCC_fnm_hyx);
  rc= stat (hcc->HCC_fnm_hyx, &st);
  if (rc == -1 && errno == ENOENT)
  {
    printf ("writing signature; ");
    if ((f= fopen (hcc->HCC_fnm_hyx, "wb")) != (FILE *) 0)
    {
      fprintf (f, "<ned.sgml enc=\"LEX\">\n");
      hyx_write_stamp (f, "pgm=dictadd");
      fputc ('\n', f);
      fclose (f);
    }
  }

SKIP1:
  printf ("... OK!\n");

  hcc->HCC_dictadd1_inited= 1;

  return 0;
}
