/*
 *  FILE %ned/10/ned1016.c
 *
 *  setup menu definiton
 *
 *  format:
 *    x y macro_num text
 *
 *  written:       1992 07 12
 *  latest update: 1999-04-25 16:36:35
 *
 */

#ifdef MSDOS
/* #pragma check_stack(off) */
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gg/dpp.h>
#include <gg/sbr.h>
#include <gg/strings.h>
#include "ed.h"
#include "proto.h"
#include <gg/maus.h>

/* ------------------------------------------------------------------------ */
int stp_mm_item (FILE *fi, char *str, int max_str)
{
  int bdx, bdy;
  long bdm;
  int rc;
#define N_FIELDS 4
  char *fields [N_FIELDS];
  int n_fields;
  struct mm_item *mi= (void *) 0;

  for (;;)
  {
    rc= fread_line (fi, str, max_str);
    if (rc <= 0 && feof (fi)) break;
    if (str [0] == '#') continue;

    n_fields= isolate_tokens (str, fields, N_FIELDS);
    if (n_fields < 0) break;
    if (n_fields > N_FIELDS) n_fields= N_FIELDS;
    if (ned_what_stp_cmd (fields [0]) >= 0) break;

    bdx= (int) get_parameter_value (fields [0]);
    bdy= (int) get_parameter_value (fields [1]);
    bdm=       get_parameter_value (fields [2]);

    if (bdm >= 0L && bdm < (long) N_MACRO)
    {
      if ((mi= (struct mm_item *) calloc (sizeof (struct mm_item), 1))
          != (struct mm_item *) 0)
      {
        mi->MMI_type= MMI_macro;
        mi->MMI_value= bdm;
      }
    }

    mm_install_function (bdx, bdy, strdup (fields [3]), (long) mi, 0, 1);
  }

  return 0;
}
