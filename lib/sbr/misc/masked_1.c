/*
 *  FILE c:/usr/sbr/masked_1.c
 *
 *  Nicht Magisfaehig !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 *
 *  1988 03 28
 *
 */

# include "masked_1.h"
# define  W_MODEL_CGA
# include <gg/window.h>
# include <gg/keys.h>

/* Daten fuer den Maskeneditor: ------------------------------------ */
static int afld,         /* aktuelles Feld in der Maske */
           err = 0,      /* 1 -> Fehlermeldung ausgeben */
           err_line;

static char *err_msg;    /* Fehlermeldung */

/* ======================================================================== */
int   msk_edit (men, ff, dss, sc, update)
int   men;               /* gewaehlte Menue Seite       */
struct MSK_FIELD ff [];  /* Feldbeschreibungsstrukturen */
char  *dss [];           /* Datenfelder                 */
int    sc,               /* Anzahl der Felder           */
      *update;           /* 1 -> Daten veraendert       */
/* RETURN: letzte nicht interpretierte Taste            */
{ int akt, i, oflg;

# ifdef JUNK
  menue (men); setcolon (ff, sc);
  if (err)
     { w_prntcol (0, 1, err_line, WV_ROT | W_BLINK,
                err_msg);
       if (err == 1) w_setnchar (0, 1, err_line, WV_GRUEN, 'Í', 78);
       err--;
     }
# endif

  for (i = 0; i < sc; i++)
      scan_str (dss [i], 0, 0x10, 0,
                ff [i].cx,  ff [i].cy,
                ff [i].lng, ff [i].attr2, &oflg);
  for (;;)
  { akt = scan_str (dss [afld], 0, 0, 0,
                    ff [afld].cx,  ff [afld].cy,
                    ff [afld].lng, ff [afld].attr1, &oflg);
    *update = (oflg & 0x01);
          scan_str (dss [afld], 0, 0x10, 0,
                    ff [afld].cx,  ff [afld].cy,
                    ff [afld].lng, ff [afld].attr2, &oflg);
    switch (akt)
    { case K_CUP      :
      case K_CDOWN    :
      case K_CLEFT    :
      case K_CRIGHT   :
      case K_CTRLLEFT :
      case K_CTRLRIGHT:
      case        0x09:
      case        0x0D:
      case        0x0A: jump (ff, sc, akt, &afld);
                        break;
      default: return akt;
    }
  }
}

/* ----------------------------------------------------------------- */
static jump (ff, sc, t, f)
struct MSK_FIELD ff [];
int  sc,
     t,
    *f;
{ int i, j, k, l;
  int axx, bxx, ayy, byy, fnum;
  bxx = ff [*f].cx; byy = ff [*f].cy;
  switch (t)
  { case 0x09:   /* Tabulator */
                if ((*f) + 1 < sc) (*f)++;
                else               (*f) = 0;
                break;
    case K_CUP: axx = -1; ayy = -1;
                for (i = 0; i < sc; i++)
                    if ((k = ff [i].cy) < byy && k > ayy)
                       ayy = k;
                if (ayy < 0) break;
                for (i = 0; i < sc; i++)
                    if (ff [i].cy == ayy &&
                        (k = ff [i].cx) <= bxx && k > axx)
                       { axx = k; fnum = i; }
                if (axx < 0)
                   { axx = 9999;
                     for (i = 0; i < sc; i++)
                       if (ff [i].cy == ayy &&
                           (k = ff [i].cx) > bxx && k < axx)
                       { axx = k; fnum = i; }
                    }
                if (axx > 9000) break;
                *f = fnum;
                break;
    case 0x0D:  case 0x0A:
    case K_CDOWN: axx = -1; ayy = 9999;
                for (i = 0; i < sc; i++)
                    if ((k = ff [i].cy) > byy && k < ayy)
                       ayy = k;
                if (ayy > 9000) break;
                for (i = 0; i < sc; i++)
                    if (ff [i].cy == ayy &&
                        (k = ff [i].cx) <= bxx && k > axx)
                       { axx = k; fnum = i; }
                if (axx < 0)
                   { axx = 9999;
                     for (i = 0; i < sc; i++)
                       if (ff [i].cy == ayy &&
                           (k = ff [i].cx) > bxx && k < axx)
                       { axx = k; fnum = i; }
                    }
                if (axx > 9000) break;
                *f = fnum;
                break;
    case K_CTRLRIGHT:
    case K_CRIGHT: axx = 9999;
                for (i = 0; i < sc; i++)
                    if (ff [i].cy == byy && i != *f &&
                        (k=ff [i].cx)  > bxx && k < axx)
                       { axx = k; fnum = i; }
                if (axx < 9999)
                   { *f = fnum;
                     break;
                   }
                for (i = 0; i < sc; i++)
                    if ((k = ff [i].cx) > bxx && k < axx)
                       { axx = k; fnum = i; }
                    else if (k > bxx && k == axx &&
                             delta (*f, fnum) > delta (*f, i))
                             fnum = i;
                if (axx > 9000) break;
                *f = fnum;
                break;
    case K_CTRLLEFT:
    case K_CLEFT: axx = -1;
                for (i = 0; i < sc; i++)
                    if (ff [i].cy == byy && i != *f &&
                        (k=ff [i].cx) < bxx && k > axx)
                       { axx = k; fnum = i; }
                if (axx >= 0)
                   { *f = fnum;
                     break;
                   }
                for (i = 0; i < sc; i++)
                    if ((k = ff [i].cx) < bxx && k > axx)
                       { axx = k; fnum = i; }
                    else if (k < bxx && k == axx &&
                             delta (*f, fnum) > delta (*f, i))
                             fnum = i;
                if (axx < 0) break;
                *f = fnum;
                break;
  }
}

/* ----------------------------------------------------------------- */
static setcolon (ff, sc)
struct MSK_FIELD ff [];
int  sc;
{ int i;
  for (i = 0; i < sc; i++)
  { w_setchar (0, ff [i].cx - 1,          ff [i].cy, WV_GELB, ':');
    w_setchar (0, ff [i].cx + ff [i].lng, ff [i].cy, WV_GELB, ':');
  }
}

/* ----------------------------------------------------------------- */
static int delta (a, b)
int a, b;
{ if (a - b < 0) return b - a;
  else           return a - b;
}

/* ----------------------------------------------------------------- */
void msk_set_fld (num) int   num; { afld = num;  }
int  msk_get_fld (   )            { return afld; }

void msk_set_err (ptr, el, en)
char *ptr;
int el, en;
{ err_msg  = ptr;
  err      =  en;
  err_line =  el;
}
