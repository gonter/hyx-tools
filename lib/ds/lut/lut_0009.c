/*
 *  FILE %ds/lut/lut_0009.c
 *
 *  Funktionen zum Durchsuchen von LUT-Woerterbuechern
 *
 *  written:       1989 06 11: aus WORDCR01.C isolierte Funktionen:
 *                             check_word       -> lookup_char
 *                             check_word_file  -> lookup_file
 *                 1990 01 20: zerlegt in Library-Module
 *                 1991 03 15: Revision; AIX
 *                 1994-07-31: isolated from lut_0008.c
 *  latest update: 2000-09-01 12:43:40
 *  $Id: lut_0009.c,v 1.4 2003/06/25 14:38:29 gonter Exp $
 *
 */

/* #define DEBUG_001 */
/* #define DEBUG_002 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <gg/lookup.h>
#include <gg/dpp.h>

/* ------------------------------------------------------------------------ */
int lut_process_block (
FILE *lut,                      /* Look Up Table                            */
int (*processor) (char *w, long i, void *client_data),
void *client_data)
{
  int idx= 0;                   /* untersuchte Stelle im Key (Suchwort)     */
  int cp;                       /* untersuchtes Zeichen aus LUT             */
  long retry_position;          /* resync position for another alternative  */
  long offset_value;            /* value of a offset code for skip entry    */
  struct LUT_STACK *lut_stack;  /* Suchpfad                                 */
  long info;                    /* info value from the found key entry      */
  int i;                        /* index for key string printout            */
  char lut_word_buffer [MAX_LUT_KEY_LENGTH];

  if ((lut_stack= malloc (sizeof (struct LUT_STACK)*MAX_LUT_KEY_LENGTH))
      == (struct LUT_STACK *) 0) return -1;
  lut_stack[0].offset= ftell (lut);

  retry_position= -1L;
  for (;;)
  {
    cp= fgetc (lut) & 0x00FF;
    if (feof (lut)) break;

    switch (cp)
    {
      case  0: /* Wortende gefunden */
        info= dpp_fread_long (lut, 4);

        for (i= 0; i < idx; i++) lut_word_buffer[i]= (char) lut_stack[i].key;
        lut_word_buffer[i]= 0;
        (*processor) (lut_word_buffer, info, client_data);

        while (lut_stack [idx].offset == 0L)
        {
          idx--;
          if (idx < 0) goto NOT_FOUND;
        }

        fseek (lut, lut_stack [idx].offset, 0);
        lut_stack [idx].offset= 0L;
        break;

      default:
        if (idx >= MAX_LUT_KEY_LENGTH) break;
        lut_stack [idx].key= cp;
        idx++;
        if (idx >= MAX_LUT_KEY_LENGTH)
        {
          fprintf (stderr, "LUT key length exceed; stopping\n");
          goto NOT_FOUND;
        }
        lut_stack [idx].offset= 0L;
        break;

      /* Offset Codes */
      case  1:
      case  2:
      case  3:
      case  4:
        offset_value= dpp_fread_long (lut, cp);
        retry_position= ftell (lut) + offset_value;
        lut_stack [idx].offset= retry_position;
/************
printf ("cp=0x%lx offset_value=0x%x retry_position=0x%lx\n",
cp, offset_value, retry_position);
************/
        break;
    }
  }

NOT_FOUND:
  free (lut_stack);

  return 0;
}
