/*
 *  FILE %ned/08/ned0839.c
 *
 *  Evaluieren eines Zeilen-Abschnitts
 *
 *  written:       1991 05 23
 *  latest update: 2001-02-11 12:36:12
 *  $Id: ned0839.c,v 1.3 2005/09/04 18:36:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include "ed.h"
#include "proto.h"

#define LINE_SIZE 2048
static char line [LINE_SIZE];

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
int ned_eval_line (
struct LINE *la,
int la_idx,
struct LINE *lz,
int lz_idx,
int option)
{
  if (ned_line_2_string (la, la_idx, lz, lz_idx, line, LINE_SIZE, 0L, 0x0000)
      == (char *) 0)
    return -1;

  return ned_eval_string (line, option);
}

/* ------------------------------------------------------------------------ */
int ned_eval_lookup_feature (const char *token, int option)
{
  char *feature_string= (char *) 0;
  char *feature_type= (char *) 0;
  int lng;

  if (ned_lookup_feature (token, line, &feature_string, &feature_type,
                          LINE_SIZE) == 0)
  {
    if (feature_string == (char *) 0 || feature_type == (char *) 0) return -1;

    if (strcmp (feature_type, "F") == 0)
    {
      if (*feature_string == '<') feature_string++;
      if ((lng= strlen (feature_string) -1) <= 0) return -1;
      if (feature_string [lng] == '>') feature_string [lng]= 0;

      ned_eval_string (feature_string, option);
    }

    if (strcmp (feature_type, "T") == 0) mac_call_tcl (feature_string);

    return 0;
  }

  return -1;
}

/* ------------------------------------------------------------------------ */
int ned_eval_tag_entry (const char *token)
{
  char *found_file= (char *) 0;
  char *found_loc= (char *) 0;

  if (ned_lookup_tag (token, line, &found_file, &found_loc, LINE_SIZE) == 0)
  {
    if (ned_open_file (found_file, (char *) 0, (char *) 0,
                       NED_OPENF_DEF1) == 0)
    {
      /* T2D: jump to the location */
      if (found_loc [0] == '/' || found_loc [0] == '?')
      {
        char *cp;
        cp= found_loc + strlen (found_loc) - 1;
        if (*cp == '/') *cp--= 0;

        ned_jmp_pattern (aw, ned_find_first_line (aw->first), found_loc+1,
                         (found_loc [0] == '?') ? OPT_backward : 0x0000);

      }
      return 0;
    }
  }

  return -1;
}
