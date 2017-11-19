/*
 *  FILE ~/usr/sbr/fmt.c
 *
 *  Formatierung von Zahlen usw.
 *
 *  written:       1988 04 09
 *  latest update: 1994-08-13
 *
 */

#include <stdio.h>
#include <gg/sbr.h>

#ifndef NIL
#define NIL (char *) 0
#endif

/* ------------------------------------------------------------------------ */
static double dc_max;           /* Maximum der  |betrachteten Zahlen|       */

static int dc_cnt= 0;           /* Zahl der betrachteten Zahlen             */
static int dc_chkflg= 0;        /* 1 -> Format schon erstellt               */
static int dc_doit= 1;          /* 1 -> wirklich formatieren                */
static int dc_komma;            /* Zeichen fuer Komma                       */
static int dc_punkt;            /* .       .    Punkt                       */

static int dc_rnd;              /* Schutzstelle fuer Rundung                */
static int dc_oo;               /* Pos. fuer 1. kopierte Ziffer             */
static int dc_pp;               /* .    des zu setzenden Punktes            */
static int dc_cp;               /* .    .   .  .         Kommas             */
static int dc_cs;               /* .    .   .  Skippenden Kommas            */
static int dc_st;               /* Laenge des formatierten Str.             */

/* ------------------------------------------------------------------------ */
static char *dc_faktor_string;
static char dc_xxxx [40];
static char *dc_value_string;
static char dc_value_string1 [40];
static char dc_value_string2 [40];
static char dc_value_string3 [40];
static int dc_v_c= 1;

/* ------------------------------------------------------------------------ */
void dc_reset ()
{
  dc_max= 0.0;
  dc_chkflg= dc_cnt= 0;
}

/* ------------------------------------------------------------------------ */
void dc_modus (int d)
{
  dc_doit= d;
}

/* ------------------------------------------------------------------------ */
void dc_cal (double v)
{
  if (v < 0.0) v= -v;
  if (v > dc_max) dc_max= v;
  dc_cnt++;
}

/* ------------------------------------------------------------------------ */
char *dc_chk (
int st,                 /* Gesamtstellenzahl mit VZ, Punkt, Komma           */
int sig,                /* Signifikante Ziffern                             */
int nk,                 /* max. erlaubte Nachkommastellen                   */
int faktor_st,          /* Anzahl der Stellen des Faktors                   */
                        /* z.B: 3 -> 1.000 | 1.000.000 | 1.000.000.000      */
                        /*      1 -> 1 | 10 | 100 | 1000 | 10000  ....      */
double *faktor,         /* Verwendeter Faktor                               */
char **cp2,             /* Faktor in Worten                                 */
int komma,              /* Zeichen fuer Komma                               */
int punkt)              /* .       .    Punkt                               */
/* RETURN: Faktor in Stringdarstellung (linksbuendig!!)                     */
{
  int i;
  int variante;

  if (faktor_st <=  0  ||
      st        <=  0  ||
      sig       >  st  ||
      nk        <   0  ||
      sig       <= nk)    return NIL;

  st= 8;
  sig= 5;
  nk= 2;
  faktor_st= 3;         /* ############## <<<<<<< */

  dc_st = st;
  dc_komma = komma; dc_punkt = punkt;
  sprintf (dc_xxxx, "%15.3f", dc_max);

  for (i = 0; dc_xxxx [i]; i++)
      { if (dc_xxxx [i] >= '0' &&
            dc_xxxx [i] <= '9') break;
        if (dc_xxxx [i] == '.') break;
      }
  dc_rnd = 0; dc_cs = 11; /* Komma Position == 11 */
  switch (dc_xxxx [i])
  { case   0:
    case '.': return NIL;
    default :
              if ((dc_rnd = i+sig) >= dc_cs) dc_rnd++;
              dc_oo = i-1; if (i > 8) dc_oo = 7;

              switch (i)
              { case 10:
                case  9:
                case  8: variante = 1;
                         dc_faktor_string =       "1.0";
                         *faktor          =        1.0 ;
                         *cp2 = "";
                         break;
                case  7: variante = 2;
                         dc_faktor_string =       "1.0";
                         *faktor          =        1.0 ;
                         *cp2 = "";
                         break;
                case  6: variante = 3;
                         dc_faktor_string =       "1.0";
                         *faktor          =        1.0 ;
                         *cp2 = "";
                         break;
                case  5: variante = 1;
                         dc_faktor_string =    "1000";
                         *faktor          =     1000.0 ;
                         *cp2 = "1000 ";
                         break;
                case  4: variante = 2;
                         dc_faktor_string =    "1000";
                         *faktor          =     1000.0 ;
                         *cp2 = "1000 ";
                         break;
                case  3: variante = 3;
                         dc_faktor_string =    "1000";
                         *faktor          =     1000.0 ;
                         *cp2 = "1000 ";
                         break;
                case  2: variante = 1;
                         dc_faktor_string = "1000000";
                         *faktor          =  1000000.0 ;
                         *cp2 = "Mio ";
                         break;
                case  1: variante = 2;
                         dc_faktor_string = "1000000";
                         *faktor          =  1000000.0 ;
                         *cp2 = "Mio ";
                         break;
                default: return NIL;
              } break;
  }

  switch (variante)
  { default:
    case 1:
            dc_pp = -1;
            dc_cp =  5;
            break;
    case 2:
            dc_pp =  2;
            dc_cp =  6;
            break;
    case 3:
            dc_pp =  4;
            dc_cp = -1;
            break;
  }
  if (dc_pp == -1 || dc_cp == -1) dc_oo--;

  dc_chkflg= 1;
  return dc_faktor_string;
}

/* ------------------------------------------------------------------------ */
char *dc_fmt (double v)
{
  double f;
  int i, j, c;
  int carry;
  char *cp;

  if (!dc_chkflg) dc_chk (8, 5, 2, 3, &f, &cp, ',', '.');
  sprintf (dc_xxxx, "%15.3f", v);
  /* printf ("CPY: %15.3f -> %s\n", v, dc_xxxx); */
  if (!dc_doit) return dc_xxxx;

  switch (dc_v_c) /* Speicherflaeche festlegen ---------------- */
  {
    case 1: dc_value_string = &dc_value_string1 [0]; dc_v_c = 2; break;
    case 2: dc_value_string = &dc_value_string2 [0]; dc_v_c = 3; break;
    case 3: dc_value_string = &dc_value_string3 [0]; dc_v_c = 1; break;
  }

  /* Zahlen setzen und runden */
  carry= (dc_xxxx [dc_rnd] >= '5' && dc_rnd) ? 1 : 0;

  for (i = dc_rnd-1, j = dc_st-1; i >= dc_oo; i--,j--)
  {
    if (j == dc_pp || j == dc_cp) j--;
      if (i >= dc_cs)
           if (i > dc_cs)
                c = dc_xxxx [i+1];
           else c = dc_xxxx [--i];
      else      c = dc_xxxx [i  ];

    if (carry)
      switch (c)
      {
        case '9':
          dc_value_string [j]= '0';
          break;
        case ' ':
          dc_value_string [j]= '1';
          carry= 0;
          break;
        default :
          dc_value_string [j]= (char) c+1;
          carry= 0;
          break;
      }
    else dc_value_string [j]= (char) c;
    /* printf ("CPY: %3d (%3d) %c -> %c\n",             */
    /*         i, j, dc_xxxx [i], dc_value_string [j]); */
  }

  /* Kommas und Punkte setzen */
  if (dc_pp >= 0)
     dc_value_string [dc_pp] =
         (dc_value_string [dc_pp-1] != ' ' &&
          dc_value_string [dc_pp-1] != '-' )
         ? (char) dc_punkt : ' ';

  if (dc_cp >= 0)
  {
    dc_value_string [dc_cp]= (char) dc_komma;
    switch (dc_value_string [dc_cp-1])
    {
      case ' ': dc_value_string [dc_cp-1] = '0'; break;
      case '-': dc_value_string [dc_cp-1] = '0';
                dc_value_string [dc_cp-2] = '-'; break;
    }
    for (i= dc_cp+1; i < dc_st; i++)
      if (dc_value_string [i] == ' ')
        dc_value_string [i]= '0';
  }

  dc_value_string [dc_st]= 0;
  return dc_value_string;
}

/* ------------------------------------------------------------------------ */
#ifdef  DEBUG

static double DD [] =
{
     123600.0,
     262900.0,
    1286460.0,
    1880380.0,
       7450.0
};

int cdecl main (void);

/* ------------------------------------------------------------------------ */
int main ()
{
  int i, j, k;
  double f;
  char *cp1, *cp2;

  sprintf (dc_xxxx, "%15.3f", 123456789.9876);
  printf  ("Fakt_str= :%s: len=%d\n", dc_xxxx, strlen (dc_xxxx));
  sprintf (dc_xxxx, "%15.3f", -123456789.9876);
  printf  ("Fakt_str= :%s: len=%d\n", dc_xxxx, strlen (dc_xxxx));

  k= sizeof (DD) / sizeof (double);
  dc_reset ();
  for (i = 0; i < k; i++) dc_cal (DD [i]);
  cp1= dc_chk (8, 5, 2, 3, &f, &cp2, ',', '.');

  printf ("dc_rnd=%d dc_oo=%d dc_pp=%d dc_cp=%d dc_cs=%d dc_st=%d\n",
          dc_rnd, dc_oo, dc_pp, dc_cp, dc_cs, dc_st);

  printf ("Max = %15.2f   In %s (%15.2f) Einheiten; %s\n",
          dc_max, cp1, f, cp2);

  for (i = 0; i < k; i++)
    printf ("Wert [%2d] = %15.3f :%s:\n", i, DD [i], dc_fmt (DD [i]));

  return 0;
}

#endif
