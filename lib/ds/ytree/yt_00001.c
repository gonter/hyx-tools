/*
 *  FILE %ds/ytree/yt_00001.c
 *
 *  ytree_alloc: create a new YTREE node
 *
 *  written:       1990 06 02
 *                 1991 03 16: Revision; AIX
 *  latest update: 1995-12-05
 *  $Id: yt_00001.c,v 1.3 2001/11/20 19:32:44 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/ytree.h>

long YTREE_ALLOCATED= 0L;
long YTREE_ALLOC_SIZE= 0L;

/* ------------------------------------------------------------------------ */
struct YTREE *ytree_alloc (
unsigned char *s,               /* String, fuer den der Knoten angelegt wird */
int lng_str)                    /* Laenge des Strings; <0 -> strlen ()       */
{
  struct YTREE *p;
  int lng_allocated;

  if (lng_str < 0) lng_str= strlen ((char *) s);

  lng_allocated= sizeof (struct YTREE) - 2 + lng_str;

  if ((p= (struct YTREE *) malloc (lng_allocated)) != (struct YTREE *) 0)
  {
    YTREE_ALLOCATED++;
    YTREE_ALLOC_SIZE += (long) lng_allocated;

    p->YT_next=
    p->YT_down=          (struct YTREE *) 0;
    p->YT_info=          0L;
    p->YT_lng_str=       lng_str;
#ifdef YTlng_all
    p->YT_lng_allocated= lng_allocated;
#endif
    p->YT_flags=          0x0000;
    p->YT_size=           0L;
    memcpy (p->YT_str, s, lng_str);
  }

  return p;
}

/* ------------------------------------------------------------------------ */
int ytree_free_node (struct YTREE *yt)
{
  int lng_allocated;

  lng_allocated= sizeof (struct YTREE) - 1 + yt->YT_lng_str;
  YTREE_ALLOC_SIZE -= (long) lng_allocated;
  YTREE_ALLOCATED--;

  free (yt);

  return 0;
}

/* ------------------------------------------------------------------------ */
/* Anmerkung:                                                               */
/* 1. YT_lng_str kann gegenueber dem Zeitpunkt des allocierens              */
/*    herabgesetzt werden, etwa in ytree_insert_word, wenn ein              */
/*    Knoten geteilt wird, und der Eintrag im urspruenglichen               */
/*    Knoten einfach nur in der Laenge angepasst wird.                      */
/* 2. Diese Laengeunterschiede sind abhaengig von der Reihenfolge, in der   */
/*    die Worte eingelesen werden.                                          */
/*    Dadurch kann ein Unterschied im Platzbedarf von erstmals gelesenen    */
/*    Worten und von einer LUT gescannten Worten erklaert werden.           */
