/*
 *  FILE %ds/vieos/vieos202.c
 *
 *  execute vieos index object methods
 *
 *  written:       1995-12-14
 *  latest update: 1996-12-22 12:39:04
 *
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <tcl.h>
#include <gg/strings.h>
#include <gg/filename.h>
#include <gg/dpp.h>
#include <gg/lookup.h>
#include <gg/vieos.h>

/* ------------------------------------------------------------------------ */
int vieos_index_object (
ClientData clientData,
Tcl_Interp *interp,
int argc,
char *argv [])
{
  struct VIEOS_INDEX *idx;
  char *method;
  struct LMDC_CONTROL *lmdc;
  int i;

  if (interp == (Tcl_Interp *) 0) return TCL_ERROR;

  if ((idx= (struct VIEOS_INDEX *) clientData) == (struct VIEOS_INDEX *) 0
      || idx->VIEI_signature != SIG_VIEOS_INDEX
      || (lmdc= idx->VIEI_lmdc) == (struct LMDC_CONTROL *) 0
     )
  {
    Tcl_SetResult (interp, "unknown object", TCL_STATIC);
    return TCL_ERROR;
  }

  if (argc >= 2)
  {
    method= argv [1];

    /* BEGIN standard methods - - - - - - - - - - - - - - - */
    if (abbrev ("creator", method, 4))
    {
      struct VIEOS_CONTEXT *vc_up;      /* the creator of this object       */

      interp->result= ((vc_up= (struct VIEOS_CONTEXT *) idx->VIEI_context)
                      == (struct VIEOS_CONTEXT *) 0)
                      ? ""                /* the absolute creator           */
                      : vc_up->VC_name;
        
      return TCL_OK;
    }

    if (abbrev ("class", method, 3))
    {
      Tcl_SetResult (interp, "index", TCL_STATIC);
      return TCL_OK;
    }

    if (abbrev ("name", method, 3))
    {
      interp->result= idx->VIEI_name;
      return TCL_OK;
    }

    if (strcmp ("destroy", method) == 0)
    {
      Tcl_DeleteCommand (interp, idx->VIEI_name);
      /* T2D: get rid of the control structure properly ... */
      vieos_destroy_index (idx);

      Tcl_SetResult (interp, "index destroyed", TCL_STATIC);
      return TCL_OK;
    }
    /* END standard methods - - - - - - - - - - - - - - - */

    if (abbrev ("stream", method, 3))
    {
      for (i= 2; i < argc; i++)
        if (lmd_read_stream (lmdc, argv [i]) < 0L) return TCL_ERROR;

      return TCL_OK;
    }

    if (strcmp ("add", method) == 0)
    {
      if (argc > 3)
      {
        long docid;
        char *docid_str;

        docid= get_parameter_value (docid_str= argv [2]);

        for (i= 3; i < argc; i++)
          if (lmd_idx (lmdc, argv [i], docid, 0L, docid_str, 0, 0, 0L) != 0)
            return TCL_ERROR;
      }

      return TCL_OK;
    }

    if (strcmp ("write", method) == 0
        || strcmp ("read", method) == 0
       )
    {
      long word_cnt_unique;
      char *lut_file= (char *) 0;
      char *wr_file= (char *) 0;
      char *di_file= (char *) 0;

      if (argc > 2) lut_file= argv [2];
      if (argc > 3) wr_file=  strdup (argv [3]);
      if (argc > 4) di_file=  strdup (argv [4]);

      if (lut_file == (char *) 0) lut_file= "xxx.lt";
      if (wr_file == (char *) 0) wr_file= fnmcpy2 (lut_file, ".wr");
      if (di_file == (char *) 0) di_file= fnmcpy2 (lut_file, ".di");

      if (strcmp ("write", method) == 0)
      {
        lmd_write_tables (lmdc, wr_file, di_file, LMDD_mode_full);
        word_cnt_unique= lmd_PL (lmdc->LMDC_ytree, lut_file, (char *) 0);
      }
      else
      {
        lmd_RL4 (lmdc, lut_file);
        word_cnt_unique= lmd_read_tables (lmdc, wr_file, di_file);
      }

      sprintf (interp->result, "%ld", word_cnt_unique);
      free (wr_file);
      free (di_file);

      return TCL_OK;
    }

    if (strcmp ("dump", method) == 0)
    {
      return TCL_OK;
    }
  }

  Tcl_SetResult (interp, "unknown method", TCL_STATIC);
  return TCL_ERROR;
}
