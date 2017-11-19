/*
 *  FILE %ned/08/ned0846.c
 *
 *  search for frame control structure in currently active
 *  clusers, create it if the control structure was not found
 *  but only if the frame exists in any of the clusters.
 *
 *  written:       1991 05 29
 *                 1993-01-18: dorothy object access method
 *                 1993-01-31: removed dorothy and installed IOA
 *                             (indirect object access) instead
 *  latest update: 1999-04-25 16:33:18
 *  $Id: ned0846.c,v 1.3 2005/09/04 20:17:27 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/lookup.h>
#include <gg/dpp.h>
#include "ed.h"
#include "edhyx.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
struct FRAMECTRL *find_frame (
struct CLUSTERCTRL *xcl,
const char *fr_name,
int search_mode)                        /* Bit 0: search in all clusters    */
{
  struct FRAMECTRL *fc;
  struct CLUSTERCTRL *cl= (struct CLUSTERCTRL *) 0;
  FILE *lut;
  long w_info;
  int llng;
  int rc;
  int phase;

  for (phase= 1; phase <= 4; phase++)
  {
    if (phase >= 3 && !(search_mode & 0x01)) break;

    switch (phase)
    {
      case 1: case 2: cl= xcl; break;
      case 3: case 4: cl= ned_get_cluster_list (); break;
      default: return (struct FRAMECTRL *) 0;
    }

    switch (phase)
    {
      case 1: /* aktuellen Cluster-Cache durchsuchen                        */
      case 3: /* alle Cluster-Caches durchsuchen                            */
              /* d.h: alle bisher aufgelaufenen Informationen auswerten     */
        for (; cl != (struct CLUSTERCTRL *) 0; cl= cl->next)
        {
          if (phase == 3 && cl == xcl) continue;  /* war schon mal ... */
          for (fc= cl->frames; fc != (struct FRAMECTRL *) 0; fc= fc->next)
            if (strcmp (fc->frame_name, fr_name) == 0) return fc;

          if (phase == 1) break;
        }
        break;

      case 2: /* aktuellen Cluster durchsuchen und Frame in Cache eintragen */
      case 4: /* alle Cluster durchsuchen und Frame in Cache eintragen      */
              /* d.h: alle noch nicht benuetzten Informationen verwenden    */

        for (; cl != (struct CLUSTERCTRL *) 0; cl= cl->next)
        {
          if (phase == 4 && cl == xcl) continue;  /* war schon mal... */

          if (fr_name [0] == '$' && fr_name [1] == '#')
          {
            if ((w_info= get_parameter_value (fr_name+2))
                <= cl->highest_index)
              return create_framectrl (cl, fr_name, w_info,
              FRAME_in_LUT /* well, not really (T2D: 1995-12-05 19:22:03) */);
          }

          rc= LOOKUP_not_found;
          if ((lut= fopen (cl->cluster_name_lut, "rb")) != (FILE *) 0)
          {
            rc= lookup_file (lut, fr_name, &w_info, &llng);
            fclose (lut);
          }

          if (rc & LOOKUP_found)
            /* FRAMECTRL aufbauen und in CLUSTERCTRL einbauen */
            return create_framectrl (cl, fr_name, w_info, FRAME_in_LUT);

          if ((lut= fopen (cl->cluster_name_xfn, "rb")) != (FILE *) 0)
          {
            rc= lookup_file_xfn (lut, fr_name, &w_info);
            fclose (lut);
          }

          if (rc & LOOKUP_found)
            return create_framectrl (cl, fr_name, w_info, FRAME_in_XFN);

          if (phase == 2) break;
        }
        break;
    }
  }

  return (struct FRAMECTRL *) 0;
}
