/*
 *  FILE %ned/08/ned0844.c
 *
 *  search for a cluster control block, create it if not found
 *
 *  written:       1991 05 29
 *                 1991 09 18: logic pathnames for clusters
 *                 1993-01-18: dorothy object access method
 *                 1993-01-31: removed dorothy access and installed IOA
 *                             (indirect object access) instead
 *  latest update: 1999-04-25 16:33:05
 *  $Id: ned0844.c,v 1.3 2005/09/04 20:17:27 gonter Exp $
 *
 */

#ifdef MSDOS
/* #pragma check_stack(off) */
#endif

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <gg/dpp.h>
#include <gg/strings.h>
#include <gg/filename.h>
#include <gg/hytxt.h>
#include <gg/ytree.h>
#include "ed.h"
#include "edhyx.h"
#include "proto.h"

extern int errno;

/* ------------------------------------------------------------------------ */
/* list of active clusters */
static struct CLUSTERCTRL *clusters= (struct CLUSTERCTRL *) 0;
static struct CLUSTERCTRL **clusters_append= &clusters;

static struct YTREE             /* name lookup tables                       */
  *cluster_by_used_name= (struct YTREE *) 0,
  *cluster_by_real_name= (struct YTREE *) 0;

/* ------------------------------------------------------------------------ */
struct CLUSTERCTRL *ned_get_cluster_list ()
{
  return clusters;
}

/* ------------------------------------------------------------------------ */
struct CLUSTERCTRL *ned_activate_cluster (
const char *fn)                 /* name of the cluster file                 */
{
  struct CLUSTERCTRL *cl;
  char *idx_fnm;
  struct stat st;
  int rc;
  char *real_fnm;               /* physical name of the cluster file        */
  char *virtual_fnm;            /* virtual name of the cluster file         */

  if (fn == (char *) 0 || *fn == 0) return (struct CLUSTERCTRL *) 0;

  /* TEST: 1996-11-09 18:17:25 */
  if ((cl= (struct CLUSTERCTRL *)
           ytree_get_value (cluster_by_used_name, (unsigned char *) fn))
           != (struct CLUSTERCTRL *) 0
     )
    goto END;

  if (filename_definition (fn, &real_fnm, &virtual_fnm, (char *) 0) != 0)
    return (struct CLUSTERCTRL *) 0;

  /* TEST: 1996-11-09 18:17:25 */
  if ((cl= (struct CLUSTERCTRL *)
           ytree_get_value (cluster_by_real_name, (unsigned char *) real_fnm))
           != (struct CLUSTERCTRL *) 0
     )
  { /* real filename was used before, but not so the name that was          */
    /* used to activate the cluster, so store that info.                    */
    ytree_set_value (&cluster_by_used_name, (unsigned char *) fn, (long) cl);
    free_or_what (real_fnm);
    free_or_what (virtual_fnm);
    goto END;
  }

#ifdef __OLD__ /* 1996-11-09 18:17:36 */
  for (cl= clusters; cl != (struct CLUSTERCTRL *) 0; cl= cl->next)
  {
    if (strcmp_c (cl->cluster_name_hyx, real_fnm) == 0)
      goto END;                 /* cluster already activated */
  }
#endif /* __OLD__ 1996-11-09 18:17:36 */

  /* Note: control structure for the named cluster was not found in         */
  /*       the look-up tables, so create one and add it to the tables.      */

  if ((cl= (struct CLUSTERCTRL *) calloc (sizeof (struct CLUSTERCTRL), 1))
      == (struct CLUSTERCTRL *) 0) goto END;

  cl->cluster_name_logic= virtual_fnm;
  cl->cluster_name_hyx= real_fnm;

  cl->cluster_name_lut= fnmcpy2 (real_fnm, ".lut");
  cl->cluster_name_xfn= fnmcpy2 (real_fnm, ".xfn");
  cl->cluster_name_idx= idx_fnm= fnmcpy2 (real_fnm, ".idx");

  rc= stat (idx_fnm, &st); /* index file */
  if (rc == -1)
  { /* Cluster index does not exist yet, so create it unless this is the    */
    /* read-only version.                                                   */
#ifndef NED_READ_ONLY
    if (errno == ENOENT)
    { /* index file does not exist; create it. */
      FILE *f;
      int i;

      if ((f= fopen (idx_fnm, "wb")) == (FILE *) 0)
      {
RELEASE:
        ned_free_clusterctrl (cl);
        return (struct CLUSTERCTRL *) 0;
      }

      for (i= 0; i < IDX_REC_SIZE; i++) fputc (0x00FF, f);
      fclose (f);
      cl->next_index= cl->highest_index= 1L;
    }
    else goto RELEASE;
#else
RELEASE_RO:
    ned_free_clusterctrl (cl);
    return (struct CLUSTERCTRL *) 0;
#endif /* NED_READ_ONLY */
  }
  else
  {
    cl->next_index= cl->highest_index= st.st_size / IDX_REC_SIZE;
  }

  rc= stat (real_fnm, &st);
  if (rc == -1)
  { /* Cluster text does not exist yet, so create it unless this is the     */
    /* read-only version.                                                   */
#ifndef NED_READ_ONLY
    if (errno == ENOENT)
    {
      FILE *f;

      if ((f= fopen (real_fnm, "wb")) == (FILE *) 0) goto RELEASE;
      fputs ("<SGML enc=\"HYX\" ed=\"ned:3.00.20\" cs=\"cp437\">\n", f);
      hyx_write_stamp (f, (char *) 0);
      fclose (f);
    }
    else goto RELEASE;
#else
    goto RELEASE_RO;
#endif /* NED_READ_ONLY */
  }

  /* add to list of clusters only when everything is ok... */
  ytree_set_value (&cluster_by_used_name, (unsigned char *) fn, (long) cl);
  ytree_set_value (&cluster_by_real_name, (unsigned char *) real_fnm,
                   (long) cl);

  *clusters_append= cl;
   clusters_append= &cl->next;

END:
  return cl;
}
