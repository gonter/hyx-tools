/*
 *  FILE %nl_kr/lib/nl_00201.c
 *
 *  set location records in a DOCUMENT_INFO structure
 *
 *  written:       1994-08-05
 *  latest update: 1995-12-05
 *  $Id: nl_00201.c,v 1.2 2001/08/03 15:51:43 gonter Exp $
 *
 */

#include <stdio.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
int lmd_set_location_code (
struct DOCUMENT_INFO *di,
int loc_operator,
int loc_number,
long loc_code)
{
#ifdef LMD_EXTENDED_MODEL
  int i;

  switch (loc_operator)
  {
    case LOC_CODE_SET:
      if (loc_number >= 0 && loc_number < MAX_DI_POS)
      {
SETIT:
        di->DI_pos [loc_number]= loc_code;
        break;
      }

      if (loc_code == 0L) break;
      for (i= 0; i < MAX_DI_POS; i++)
        if (di->DI_pos [i] == 0L)
          goto SETIT;
      break;

    case LOC_CODE_ADD:
      if (loc_number < 0 || loc_number >= MAX_DI_POS) break;
      di->DI_pos [loc_number] += loc_code;
      break;

    case LOC_CODE_OR:
      if (loc_number < 0 || loc_number >= MAX_DI_POS) break;
      di->DI_pos [loc_number] |= loc_code;
      break;
  }

#else
#ifdef MSDOS
  di; loc_operator; loc_number; loc_code;
#endif /* MSDOS */
#endif /* !LMD_EXTENDED_MODEL */

  return 0;
}
