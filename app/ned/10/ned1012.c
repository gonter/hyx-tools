/*
 *  FILE %ned/10/ned1012.c
 *
 *  setup button definiton
 *  format:
 *    x y colour type macro_num id text
 *
 *  written:       1992 04 04
 *  latest update: 1996-12-04 18:36:26
 *
 */

#ifdef MSDOS
/* #pragma check_stack(off) */
#endif

#include <stdio.h>
#include <string.h>
#include <gg/dpp.h>
#include <gg/sbr.h>
#include <gg/strings.h>
#include "ed.h"
#include "proto.h"

extern int W_TEXT_MAX_Y;
extern int NED_TEXT_MAX_Y;

/* ------------------------------------------------------------------------ */
int stp_button (FILE *fi, char *str, int max_str)
{
  int rc;
#define N_FIELDS 7
  char *fields [N_FIELDS];
  int n_fields;
  int bdx, bdy, bdc, bdt, bdm, bdi;

  for (;;)
  {
    rc= fread_line (fi, str, max_str);
    if (rc <= 0 && feof (fi)) break;
    if (str [0] == '#') continue;

    n_fields= isolate_tokens (str, fields, N_FIELDS);
    if (n_fields < 0) break;
    if (n_fields > N_FIELDS) n_fields= N_FIELDS;
    if (ned_what_stp_cmd (fields[0]) >= 0) break;

    bdx= (int) get_parameter_value (fields [0]);
    /* y: line where button text appears */
    bdy= (int) get_parameter_value (fields [1]);
    if (bdy < 0)
    { /* negative values: button is in the lower screen area ... */
      /* reduce the size of possible screen text if necessary */
      int t;
      
      t= W_TEXT_MAX_Y+bdy;
      if (t < NED_TEXT_MAX_Y) NED_TEXT_MAX_Y=t;
      bdy= W_TEXT_MAX_Y+bdy;
    }

    bdc= (int) get_parameter_value (fields [2]);
    bdt= (int) get_parameter_value (fields [3]);
    bdm= (int) get_parameter_value (fields [4]);
    bdi= (int) get_parameter_value (fields [5]);

    def_button (bdx, bdy, bdc, bdt, bdm, bdi, fields [6]);
  }

  return 0;
}
