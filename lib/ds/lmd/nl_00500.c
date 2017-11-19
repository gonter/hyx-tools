/*
 *  FILE %ds/lmd/nl_00500.c
 *
 *  create LM/D construction control structor
 *
 *  written:       1994-12-18
 *  latest update: 1996-12-22 13:16:37
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
struct LMDC_CONTROL *lmd_create_control ()
{
  struct LMDC_CONTROL *lmdc;
  char *cp1;
  char *cp2;

  if ((lmdc= (struct LMDC_CONTROL *) calloc (sizeof (struct LMDC_CONTROL), 1))
      != (struct LMDC_CONTROL *) 0
     && (cp1= malloc (LMD_BUFFER_SIZE)) != (char *) 0
     && (cp2= malloc (LMD_BUFFER_SIZE)) != (char *) 0)
  {
    lmd_initialize_control (lmdc);

    lmdc->LMDC_buffer1= cp1;
    lmdc->LMDC_buffer2= cp2;
    lmdc->LMDC_buffer_size= LMD_BUFFER_SIZE;
  }

  return lmdc;
}
