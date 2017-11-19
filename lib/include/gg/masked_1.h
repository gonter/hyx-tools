/*
 *  include FILE <gg/masked_1.h>
 *
 *  written:       1988 03 28
 *                 1991 01 28: Revision
 *  latest update: 1994-11-11
 *
 */

#ifndef __GG_masked_1__
#define __GG_masked_1__

struct MSK_FIELD              /* Feldbeschreibung fuer Masken Editor */
{
  int  cx, cy,
       lng,
       attr1, attr2;
} ;

/* ------------------------------------------------------------------------ */
int cdecl msk_edit (int men, struct MSK_FIELD ff [], char *dss[],
                    int sc, int *update);

/* int   msk_edit (men, ff, dss, sc, update)            */
/* int   men;               gewaehlte Menue Seite       */
/* struct MSK_FIELD ff [];  Feldbeschreibungsstrukturen */
/* char  *dss [];           Datenfelder                 */
/* int    sc,               Anzahl der Felder           */
/*       *update;           1 -> Daten veraendert       */
/* RETURN: letzte nicht interpretierte Taste            */

void cdecl msk_set_fld (int);
int  cdecl msk_get_fld ();
void cdecl msk_set_err (char *, int, int);

#endif
