/*
 *  FILE ~/usr/sbr/scan.c
 *
 *  written:       1987 12 13
 *  latest update: 1994-08-01
 *
 */

#include <string.h>
#include <stdio.h>
#include <conio.h>
#define W_MODEL_CGA
#include <gg/window.h>
#include <gg/keys.h>
#include <gg/dpp.h>
#include <gg/strings.h>
#include <gg/sbr.h>

#define T_CONST 200

#define POS(x) ((x)&0x00FF)

static int coff;        /* Cursor Offset im Feld                    */
static int insf= 1;     /* Insert Flag: 1 -> Insert Modus           */

/* ------------------------------------------------------------------------ */
/* Einlesen eines Strings via field_edit                                    */
int scan_str (
char field [],          /* editiertes Feld                                  */
int helpnum,            /* 1. Help Seite                                    */
int flag,               /* Bit 0: --> Field loeschen vor Edit               */
                        /*     1: --> Field terminieren nach Blank udgl.    */
                        /*     2: --> Default-Descriptor verwenden          */
                        /*     3: --> Editierung Ende nach 1 Input Char     */
                        /*            == Single Character Mode              */
                        /* Bit 4: --> Feld nur anzeigen                     */
int timeout1,
int x,
int y,
int l,
int attr,               /* Koordinaten, Laenge und Attribut                 */
int *oflg)              /* Bit 0: field veraendert                          */
/* RETURN: letzte nicht interpretierte Taste oder NULL                      */
{
  char Descriptor [14];
  int ret;
  int timeout;
  int loop;
  int i;
  int key;

  helpnum;

  for (i = 4; i < 14; i++) Descriptor [i] = 0;

  if (flag & 0x01) field [0] = 0;
  if (flag & 0x04)
  {
    Descriptor [0] = 1;
    Descriptor [1] = 22;
    Descriptor [2] = 78;
    Descriptor [3] = WV_BLAU | W_HELL;
  }
  else
  {
    Descriptor [0] = (char) x;
    Descriptor [1] = (char) y;
    Descriptor [2] = (char) l;
    Descriptor [3] = (char) attr;
  }

  Descriptor [10] |= flag;   /* Single Char Mode stellen */

  if (flag & 0x0010)
     { show_field (field, 1, Descriptor, 0);
       return 0;
     }
  for (loop = 0; loop == 0; )
    { timeout = timeout1;
      ret = field_edit (field, 1, Descriptor, &key, &timeout, oflg);
      switch (ret)
      { case 0: loop = 3;
                break;
        case 2: loop = 1;
           break;
      }
    }

    if (flag & 0x02)
       for (i = 0;;i++)
         { if (field [i] <= 0x20 || field [i] >= 0x7f ||
               field [i] == ','  || field [i] == ';')
              field [i] = 0;
           if (! field [i]) break;
         }

  if (loop == 3) return key; else return 0;
}

/* ------------------------------------------------------------------------ */
/* Ein Feld im Textmodus (40|80 Zeichen) editieren                          */
int field_edit (
char field [],                  /* Editiertes Feld (intern immer String)    */
int mode,                       /* 1 -> 80 Zeichen Mode                     */
char desc [],                   /* Field-Descriptor-Record                  */
unsigned int *key,              /* letzte uninterpretierte Taste            */
unsigned int *timeout,          /* (IN/OUT) Zeit Limit fuer Edit:           */
                                /* kann fuer ein ganzes Feld oder auch nur  */
                                /* fuer ein Zeichen verstanden werden       */
unsigned int *oflg)             /* Bit 0: field veraender                   */
/* RETURN: 0 -> keine Funktionstastenzuordnung                              */
/*           -> *key == uninterpretierter Tastenwert (mapped)               */
/*         1 -> Funktionstastenzuordnung gefunden                           */
/*           -> *key == Destination Frame Nummer (Bit 15 == 0)              */
/*         2 -> Timeout abgelaufen; *key ist undefiniert                    */
{
  int  strl,        /* Laenge des Editierten Strings                        */
       disp = 1,    /* 1 -> Feld muss angezeigt werden                      */
       retype = 0,  /* 1 -> Feld muss 2. asgegeben werden (XOR)             */
       retinc = 0,  /*                                                      */
       bx_flg = 0,  /* 1 -> Grafischer Modus                                */
       stop, i;
  char field_save [100];   /* gesicherter Feldinhalt                        */

  if (desc [10] & 0x40) field [0] = 0;
  strl = strlen (field);
  strcpy (field_save, field);
  if (coff > strl) coff = strl;

  w_cursoron ();

  /* Editorschleife */
  for (stop = 3; stop == 3;)
  { /* Cursor richtig positionieren */
    if (disp)
       show_field (field, mode, desc, 1 /* -> invers */);
    disp = 0; retype += retinc;
    w_setcup (0, POS (desc [0]) + coff, POS (desc [1]));
    switch (getkey (key, timeout))
       /* timeout fuer jeden Aufruf neu initialsieren oder nicht? */
    { case 0: /* Normale Taste eingegben;      */
              /* wird lokal weiterverarbeitet  */
        switch (*key)
        { case K_CLEFT:  if (coff) coff--;
                         break;
          case K_CRIGHT: if (coff < POS (desc [2])-1 && coff < strl)
                            coff++;
                         break;
          case K_HOME:
          case 0x01:     coff = 0;    break;
          case K_END:
          case 0x07:     coff = strl;
                         if (coff >= POS (desc [2]))
                            coff = POS (desc [2]) - 1;
                         break;
          case 0x04:     field [coff] = 0;
                         strl = strlen (field);
                         disp = 1;
                         break;
          case 0x08:     /* <- Taste; nach links loeschen */
                         if (coff) { delstr (field, --coff);
                                     strl--; disp = 1;
                                   }
                         break;
          case K_DEL:    /* Nach rechts loeschen */
                         delstr (field, coff);
                         strl = strlen (field);
                         disp = 1;
                         break;
          case K_INS:    /* Toggle Insert Modus   */
                         insf = (insf) ? 0: 1;
                         break;
          case 0x19:
          case 0x15:     /* CTRL-U    ==> Feld loeschen            */
                         strl = coff = 0;
                         field [0] = 0;
                         disp = 1;
                         break;
          case 0x12:
          case 0x1B:     /* ESC-Taste ==> Restore alten Feldinhalt */
                         strcpy (field, field_save);
                         strl = strlen (field);
                         if (coff > strl) coff = strl;
                         disp = 1;
                         break;
          default:  /* keine lokale Sonderfunktion */
             if (0x20 <= *key && *key <= 255 && *key != 127)
              { /* darstellbare Zeichen werden im Feld eingebaut */
                if ((insf || strl <= coff) && (strl+1) < POS (desc [2]))
                 { for (i = strl; i > coff; i--)
                       field [i] = field [i-1];
                   strl++;
                 }
                disp = 1;
                field [coff] = (char) *key;
                field [strl] = 0;
                if (coff+1 < POS (desc [2]))
                   /* Feldende  noch nicht erreicht */
                   coff++;
                else
                  /* Feldende erreicht */
                  if (desc [10] & 0x10)
                   { /* und Autoenter (Type Ahead enabled) */
                     stop = 0; /* -> Funktionstaste vortaeuschen */
                   } /* sonst keine Aktion */
                if (desc [10] & 0x08)
                   { /* Single Char Mode */
                     stop = 0;
                     *key = 0x0100;  /* Pseudo Funktion Key */
                     field [coff] = 0;
                   }
              }
             else stop = 0; /* sonstige CTRL- und Funktions-Tasten */
        }
        break;
      case 1: /* Funktions Taste */
              stop = 0; break;
      case 2: /* Time Out bei Zeichen */
              stop = 2; break;
  } }

  w_cursoroff ();
  show_field (field, mode, desc, 0 /* -> normal */);
  *oflg = (strcmp (field_save, field) == 0) ? 0 : 1;
  return stop;
}

/* ------------------------------------------------------------------------ */
void show_field (
char field [],                  /* Feldinhalt                               */
int mode,                       /* 1 -> 80 Zeichen                          */
char desc [],                   /* Beschreibung des Feldes                  */
int flag)                       /* 1 -> inverse Darstellung                 */
{
  int attr;                     /* ausgegebenes Attribut                    */
  int i;
  int strend= 0;                /* StringEnde Flag                          */

  mode;

  if (flag)
       attr =  (desc [3] & 0x88)          /* Hell u. Blink bleibt    */
            | ((desc [3] & 0x07) << 4)    /* Vordegrund --> Hinterg. */
            | ((desc [3] & 0x70) >> 4);   /* Hintergrund --> Voderg. */
  else attr = desc [3];

  for (i = 0; i < POS (desc [2]); i++)
    { if (!field [i])
       { w_setnchar (0, POS (desc [0]) + i,  /* Blank Field   */
                     POS (desc [1]), attr, ' ',
                     POS (desc [2]) - i);
         break;
       }
      w_setchar (0, POS (desc [0]) + i,
                 POS (desc [1]), attr, field [i]);
    }
}

/* ------------------------------------------------------------------------ */
/* Einlesen von genau einer Taste OHNE Ausgabe am Schirm          */
int getkey (
unsigned int *akt,
unsigned int *timeout)
/* RETURN: 0 -> keine Funktionstastenzuordnung                    */
/*           -> *akt == Tastenwert gemaess Mapkey                 */
/*         1 -> Funktionstastenzuordnung gefunden                 */
/*           -> *akt == Destination Frame Nummer (Bit 15 = 0)     */
/*              ANM: bei Special Frames werden diverse Aktionen   */
/*                   auf dem Stack vorbereitet !!!!               */
/*         2 -> Timeout abgelaufen; *akt ist undefiniert          */
{ int time;

  for (time = T_CONST;;)
  { if (kbhit ())
     { if (!(*akt = getch ())) *akt = getch () + 0x0100;
       return 0;
     }
    if (*timeout)
     { if (*timeout == 1) return 2;
       if (time) time--;
       else { time = T_CONST;
              (*timeout)--;
            }
     }
    /* war *timeout beim Funktionsaufruf == 0,                    */
    /* dann wird notfalls ewig gewartet                           */
  }
}

/* ------------------------------------------------------------------------ */
/* Einlesen eines Integers via field_edit                                   */
void scan_int (
int *field,             /* editiertes Feld                                  */
int helpnum,            /* 1. Help Seite                                    */
int flag,               /* Bit 0: --> Field loeschen vor Edit               */
                        /*     1: --> Field terminieren nach Blank udgl.    */
                        /*     2: --> Default-Descriptor verwenden          */
int timeout1,
int x,
int y,
int l,
int attr,               /* Koordinaten, Laenge und Attribut                 */
int *oflg)              /* Bit 0: field veraendert                          */
{
  char str [80], *strp;

  sprintf (str, "%d", *field);
  scan_str (str, helpnum, flag, timeout1, x, y, l, attr, oflg);
  strp = str;
  *field= (int) get_parameter_value (str);
}

/* ------------------------------------------------------------------------ */
/* Einlesen eines HEX-Integers via field_edit                               */
void scan_hex (
int *field,             /* editiertes Feld                                  */
int helpnum,            /* 1. Help Seite                                    */
int flag,               /* Bit 0: --> Field loeschen vor Edit               */
                        /*     1: --> Field terminieren nach Blank udgl.    */
                        /*     2: --> Default-Descriptor verwenden          */
int timeout1,
int x,
int y,
int l,
int attr,               /* Koordinaten, Laenge und Attribut                 */
int *oflg)              /* Bit 0: field veraendert                          */
{
  char str [80], *strp;

  sprintf (str, "0x%04x", *field);
  scan_str (str, helpnum, flag, timeout1, x, y, l, attr, oflg);
  strp= str;
  *field= (int) get_parameter_value (str);
}

/* ------------------------------------------------------------------------ */
void set_coff (int x)
{
  coff= x;
}
