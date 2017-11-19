/*
 *  FILE %ds/ytree/yt_00011.c
 *
 *  LUT in YTREE einscannen;
 *  YTREE wird durch Einfuegen von vollstaendigen Worten aufgebaut.
 *
 *  written:       1989 06 11: aus WORDCR01.C isolierte Funktionen:
 *                             check_word       -> lookup_char
 *                             check_word_file  -> lookup_file
 *                 1990 01 20: zerlegt in Library-Module
 *                 1991 03 16: Revision; AIX
 *                 1991 04 26: Erweiterung durch kill-lists
 *                             Umbennennung von ytree_2scan in
 *                             ytree_full_scan, da diese Funktion jetzt
 *                             gegenueber ytree_scan eine echte
 *                             Daseinsberechtigung, ueber die Tatsache
 *                             hinausgehend, dass ytree_scan nicht immer
 *                             funktionierte, hat.
 *                 2003-06-25 vgl. lut_process_block ()
 *  latest update: 1996-08-08 16:33:29
 *  $Id: yt_00011.c,v 1.5 2003/06/25 14:38:29 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/ytree.h>
#include <gg/dpp.h>

/* ------------------------------------------------------------------------ */
#define BUFFER_SIZE 4096

/* ------------------------------------------------------------------------ */
int ytree_full_scan (
FILE *lut,                      /* Look Up Table                            */
struct YTREE **ytp,
long  kill_by_info [],          /* entries not to be included by info value */
int   kill_by_info_cnt,         /* number of ^^^^                           */
char *kill_by_str [],           /* entries not to be included by string     */
int   kill_by_str_cnt)          /* number of ^^^^                           */
{
  int idx= 0;                   /* untersuchte Stelle im Key (Suchwort)     */
  int rc= -1;                   /* return code of this function             */
  int cp;
  int i;                        /* loop index                               */
  long retry_position;          /* restart position                         */
  long skip;                    /* skip (offset) code                       */
  long info;                    /* info contents of node                    */
  struct YTREE *y;
  struct LUT_STACK *lut_stack= (struct LUT_STACK *) 0;   /* Suchpfad        */
  unsigned char lut_word_buffer [ZTREE_DEPTH_MAX];
  long cnt= 0L;

printf ("yt_00011: %d\n", __LINE__);

  if ((lut_stack= malloc (sizeof (struct LUT_STACK)*ZTREE_DEPTH_MAX))
       == (struct LUT_STACK *) 0
     ) return -1;

printf ("yt_00011: %d\n", __LINE__);

  lut_stack [0].offset= ftell (lut);

#ifdef DIAGNOSTIC
/*** BEGIN DIAGNOSTIC OUTPUT ************************************************/
printf ("kill_by_info_cnt=%d kill_by_str_cnt=%d\n",
  kill_by_info_cnt, kill_by_str_cnt);
for (i= 0; i < kill_by_info_cnt; i++)
  printf ("kill_by_info [%d]= 0x%lX\n", i, kill_by_info [i]);
for (i= 0; i < kill_by_str_cnt; i++)
  printf ("kill_by_str [%d]= '%s'\n", i, kill_by_str [i]);
/*** END DIAGNOSTIC OUTPUT **************************************************/
#endif /* DIAGNOSTIC */

  retry_position= -1L;
  for (;;)
  {
    cp= fgetc (lut) & 0x00FF;
    if (feof (lut))
    {
      long pos;
      pos= ftell (lut);
      printf ("yt_00011: %d pos=%ld\n", __LINE__, pos);
      break;
    }
    cnt++;

    switch (cp)
    {
      case  0: /* Wortende gefunden */
        info= dpp_fread_long (lut, 4);

        lut_word_buffer[idx]= 0;
        for (i= 0; i < kill_by_info_cnt; i++)
          if (info == kill_by_info [i]) goto BREAK;
        for (i= 0; i < kill_by_str_cnt; i++)
          if (strcmp ((char *) lut_word_buffer, kill_by_str [i]) == 0)
            goto BREAK;

/***
if (lut_word_buffer[0] == 'z')
printf ("idx=%d lut_word_buffer='%s'\n", idx, lut_word_buffer);
***/

        if ((y= ytree_insert_word (ytp, lut_word_buffer))
            == (struct YTREE *) 0)
        {
          fprintf (stderr, "ytree_scan: new word not in tree (memory?)\n");
          goto ERROR;
        }
        y->YT_flags |= YTflag_EOW;
        y->YT_info= info;

BREAK:
        while (lut_stack [idx].offset == 0L)
        {
          idx--;
          if (idx < 0)
          {
            printf ("idx=%d, OVER\n", idx);
            goto OVER;
          }
        }
        fseek (lut, lut_stack [idx].offset, 0);
        lut_stack [idx].offset= 0L;
        break;

      default:
        if (idx >= ZTREE_DEPTH_MAX)
        {
          fprintf (stderr, "LUT key length exceed; stopping %d\n", __LINE__);
          goto OVER;
        }

        lut_stack [idx].key= cp;
        lut_word_buffer [idx]= (unsigned char) cp;
        idx++;
        if (idx >= ZTREE_DEPTH_MAX)
        {
          fprintf (stderr, "LUT key length exceed; stopping %d\n", __LINE__);
          goto OVER;
        }
        lut_word_buffer [idx]= 0;
        lut_stack [idx].offset= 0L;
        break;

      /* Offset Codes */
      case  1:
      case  2:
      case  3:
      case  4:
        skip= dpp_fread_long (lut, cp);
        retry_position= ftell (lut) + skip;
        lut_stack [idx].offset= retry_position;
        break;
    }
  }

printf ("yt_00011: %d\n", __LINE__);

OVER:
  rc= 0;
printf ("yt_00011: %d cnt=%ld\n", __LINE__, cnt);

ERROR:
printf ("yt_00011: %d\n", __LINE__);
  free_or_what (lut_stack);

  return rc;
}
