/*
 *  FILE ~/usr/sbr/fileio.c
 *
 *  written:       1987 12 15
 *  latest update: 1994-08-01
 *
 */

#include <stdio.h>
#include <string.h>
#include <io.h>
#include <gg/fileio.h>
#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
#define NSid 2

static char *Sid [NSid] =
{
  "write-empty",
  "no-write-empty"
} ;

/* ------------------------------------------------------------------------ */
static char **identifier;
static int Nid;
static int flg_write_empty= 0;  /* 1 -> leere Daten schreiben               */
static int Slng= 0;             /* Laenge der Bearbeiteten Strings          */

#define N_So  32
static FILE *ffi, *ffo;
static int last_type;
static char obj [100];
static char So  [N_So];

/* ------------------------------------------------------------------------ */
void set_filemode (
int num,
int nid,
char *ident [],
int slng)
{
#ifdef DEBUGx
  int i;

  printf ("\n\n&ident=%lx ident=%lx *ident=%lx\n",
         &ident, ident, *ident);

  for (i = 0; i < nid; i++)
      printf ("Identifier%d [%3d] = %s\n", num, i, ident [i]);
#else
#ifdef MSDOS
  num;
#endif
#endif

  Nid        =   nid;
  identifier = ident;
  Slng       =  slng;
}

/* ------------------------------------------------------------------------ */
int get_identifier (char *n)
{
  int i;
  to_lower (n);
  for (i = 0; i < Nid; i++)
#ifdef DEBUG
        if (strcmp (identifier [i], n) == 0)
           { printf ("Identifier %20s -> %3d\n",
                      identifier [i], i);
             return i;
           }
#else
        if (strcmp (identifier [i], n) == 0) return i;
#endif

  return -1;
}

/* ------------------------------------------------------------------------ */
int get_Sid ()
{
  int i;

  to_lower (So);
  for (i = 0; i < NSid; i++)
      if (strcmp (Sid [i], So) == 0) return i;
  return -1;
}

/* ------------------------------------------------------------------------ */
int f4fscan (
FILE *fi,
FILE *fo,
int  *objekttyp,     /* 0 -> undef; 1 -> Identifier; 2 -> Daten      */
char *objekt,
int flags)           /* Bit 0 -> Copy fi -> fo                       */
                     /*     1 -> Copy fi -> fo bis EOF ohne Analyse  */
                     /*     2 -> Copy fi -> fo Comment               */
/* RETURN: 0 .. OK, -1 .. EOF erreicht                               */
{
  int ch, off, state, Soff;

  if (last_type < 0) return -1;
  switch (last_type)
  { case  1: state = 3;
             break;
    case  3: state = 4;
             break;
    default: state = 0;
             break;
  }
  for (off = 0;;)
  { ch = fgetc (fi);
    if (((flags & 0x03) ||
        ((flags & 0x04) && state == 1)) && ch != -1)
       fputc (ch, fo);
#ifdef DEBUG2
    printf ("SCAN: last_type=%d state=%d off=%3d ch=%02x\n",
        last_type, state, off, ch);
#endif
#ifdef DEBUG2
    putchar (ch);
#endif
    if (flags & 0x02)
       { if (ch == -1)
            { last_type = -1;
              return -1;
            }
       }
    else
       switch (state)
       { case 0: /* noch nichts brauchbares vorgekommen */
                 if (ch == -1)
                    { *objekttyp = 0;
                      last_type = -1;
                      return -1;
                    }
                 if (ch == '#')
                    { state = 1;
                      if (flags & 0x04)
                         fputc ('#', fo);
                      break;
                    }
                 if (ch == '@')
                    {
                      state = 5;
                      So [0] = 0;
                      Soff = 0;
                      if (flags & 0x04)
                         fputc ('@', fo);
                      break;
                    }
                 if ((ch >= 'a' && ch <= 'z') || (ch == '_') ||
                     (ch >= 'A' && ch <= 'Z') || (ch == '-') ||
                     (ch >= '0' && ch <= '9'))
                    { objekt [off++] = (char) ch;
                      state = 2;
                    }
                 break;
         case 1: /* Kommentare ausfiltern */
                 if (ch == 0x0D || ch == 0x0A)
                    state = (last_type == 1) ? 3 : 0;
                 break;
         case 2: /* Identifier lesen */
                 if ((ch >= 'a' && ch <= 'z') ||
                     (ch >= 'A' && ch <= 'Z') || (ch == '-') ||
                     (ch >= '0' && ch <= '9'))
                      { if (off+1 < Slng)
                           objekt [off++] = (char) ch;
                      }
                 else if (ch == -1)
                      { *objekttyp = 1; last_type = -1;
                        objekt [off] = 0;
                        return 0;
                      }
                 else { *objekttyp = last_type = 1;
                        objekt [off] = 0;
                        if (ch == '=') last_type = 3;
                        else if (ch == 0x0A || ch == 0x0D)
                             last_type = 0;
                        return 0;
                      }
                 break;
         case 3: /* Datentrennzeichen erwarten */
                 if (ch == '=') state = 4;
                 else if (ch == 0x0A || ch == 0x0D) state = 0;
                 break;
         case 4: /* Datum lesen */
                 if (ch == 0x0A || ch == 0x0D)
                    { *objekttyp = last_type = 2;
                       objekt [off] = 0;
                       return 0;
                    } else
                 if (ch == -1)
                    { *objekttyp = 2; last_type = -1;
                       objekt [off] = 0;
                       return 0;
                    } else
                 if (off+1 < Slng)
                    objekt [off++] = (char) ch;
                 break;
         case 5: /* Modulsteuerung */
                 if (ch == 0x0D || ch == 0x0A)
                    { state = (last_type == 1) ? 3 : 0;
                      Soff = get_Sid ();
                      switch (Soff)
                      { case 0: flg_write_empty = 1; break;
                        case 1: flg_write_empty = 0; break;
                      }
                    }
                 else if (Soff+2 < N_So)
                         { So [Soff++] = (char) ch;
                           So [Soff  ] =  0;
                         }
                 break;
       }
     }
}

/* ------------------------------------------------------------------------ */
int f4f_read (
char *filename,
char *k_name,
int  *k_version,
int   flags,                   /* Bit 0: first static open */
                               /*     1: sequential read   */
char *daten1 [],
int   daten1_zahl,
char *daten2 [],
int   daten2_zahl,
char *daten3 [],
int   daten3_zahl,
char *daten4 [],
int   daten4_zahl)
/* RETURN: ERR_file_not_found    */
/*         ERR_name_not_found    */
/*         ERR_version_not_found */
/*         ERR_eof               ... bei sequentiellem lesen */
{ int obj_typ,
      sel_field,
      ret_val = ERR_name_not_found,
      vers    = -1,
      state   =  0;
  int g1, g2, g3, g4;

  if (filename [0] == 0)    return ERR_file_not_found;
  if (!(flags & 0x03))
     if (k_name   [0] == 0) return ERR_name_not_found;
  g1 =      daten1_zahl;
  g2 = g1 + daten2_zahl;
  g3 = g2 + daten3_zahl;
  g4 = g3 + daten4_zahl;

  if (access (filename, 0) != 0) return ERR_file_not_found;
  if ((flags & 0x03) == 0x01 ||
      (flags & 0x03) == 0x00)
     { ffi = fopen (filename, "rt");
       last_type = 0;
     }

  /* printf ("Filename=%s k_name=%s k_version=%d\n",   */
  /*         filename, k_name, *k_version); getch ();  */
  for (;;)
  { if (f4fscan (ffi, ffo, &obj_typ, obj, 0) == -1)
       { if (flags & 0x03) ret_val = ERR_eof;
         break;
       }
    to_lower (obj);
#ifdef DEBUG
    printf ("READ: state=%2d obj_typ=%3d obj=%s\n",
            state, obj_typ, obj);
#endif
    switch (state)
    { case 0: if (obj_typ == 1 && strcmp (obj, "kid") == 0)
                 state = 3;
              break;
      case 1: if (obj_typ   !=  2) break;
              state = 2;
              if (sel_field <   0) break;
              if (sel_field <  g1)
                 strcpy (daten1 [sel_field], obj); else
              if (sel_field < g2)
                 strcpy (daten2 [sel_field-g1], obj); else
              if (sel_field < g3)
                 strcpy (daten3 [sel_field-g2], obj); else
              if (sel_field < g4)
                 strcpy (daten4 [sel_field-g3], obj);
              break;
      case 2: /* naechsten Identifier erwarten */
              if (obj_typ != 1) break;
              if (strcmp (obj, "kid") == 0)
                 if (vers >= *k_version ||
                     (flags & 0x03))       goto READ_ENDE;
                 else state = 0;
              else { sel_field = get_identifier (obj);
                     state = 1;
                   }
              break;
      case 3: /* k_name erwarten */
              if (obj_typ == 2)
                 if (strcmp (obj, k_name) == 0)
                 { vers++;
                   state = 2;
                   ret_val = ERR_version_not_found;
                 } else
                 if (flags & 0x03)
                 { state = 2;
                   ret_val = 0;
                   strcpy (k_name, obj);
                 }
              else state = 0;
              else state = 0;
              break;
    }
  }
READ_ENDE:
  *k_version = vers;
  if (!(flags & 0x03) || ret_val == ERR_eof)
     fclose (ffi);
  return ret_val;
}

/* ------------------------------------------------------------------------ */
int f4f_write (
char *filename,
char *k_name,
int  *k_version,
int  flags,
char *daten1 [],
int   daten1_zahl,
char *daten2 [],
int   daten2_zahl,
char *daten3 [],
int   daten3_zahl,
char *daten4 [],
int   daten4_zahl)
{
  int obj_typ;
  int copyflgs;
  int f_create= 0;                      /* 1 -> File erst erzeugt           */
  int written= 0;                       /* 1 -> Daten gesichert             */
  int ret_val= ERR_name_not_found;
  int vers= -1;
  int state= 0;

#ifdef MSDOS
  flags;
#endif

  if (filename [0] == 0) return ERR_file_not_found;
  if (k_name   [0] == 0) return ERR_name_not_found;
  if (access (filename, 0) != 0)
     { ffo = fopen (filename, "wt");
       fprintf (ffo, "#\n# File %s\n#\nkid =%s\n", filename, k_name);
       f4f_wds (ffo, daten1, daten1_zahl,
                     daten2, daten2_zahl,
                     daten3, daten3_zahl,
                     daten4, daten4_zahl);
       fclose (ffo);
       return ERR_file_not_found;
     }
  ffo = fopen (TEMPFILE, "wt");
  ffi = fopen (filename, "rt");
  last_type = 0; copyflgs = 0x01;
#ifdef DEBUG
    w_col80mode ();
    menue (0);
#endif
  for (; state >= 0;)
  { if (f4fscan (ffi, ffo, &obj_typ, obj, copyflgs) == -1) break;
#ifdef DEBUG
    printf ("WRITE: %3d %s \n", obj_typ, obj);
#endif
    switch (state)
    { case 0: if (obj_typ == 1 && strcmp (to_lower (obj), "kid") == 0)
                 state = 3;
              break;
      case 1: /* Daten ueberlesen */
              state = 2;
              break;
      case 2: /* naechsten Identifier erwarten */
              if (obj_typ == 1)
                 if (strcmp (to_lower (obj), "kid") == 0)
                    { /* Rest uebertragen */
#ifdef DEBUG
    printf ("Skipping Record Obj=%s\n", obj);
#endif
                      fprintf (ffo, (last_type == 3) ? "kid=" : "kid");
                      f4fscan (ffi, ffo, &obj_typ, obj, 3); /* copy -> EOF */
                      state   = -1; /* -> Ende */
                    }
                 else state = 1;
              break;
      case 3: /* k_name erwarten */
              if (obj_typ == 2 &&
                  strcmp (obj, k_name) == 0)
                 { vers++;
                   ret_val = ERR_version_not_found;
                   if (vers >= *k_version)
                   { /* aktuelle Daten schreiben */
#ifdef DEBUG
    printf ("Writing Record Kid=%s Vers=%d\n", k_name, vers);
#endif
                     f4f_wds (ffo, daten1, daten1_zahl,
                                   daten2, daten2_zahl,
                                   daten3, daten3_zahl,
                                   daten4, daten4_zahl);
                     state    = 2; /* folgenden (alten) DS ueberlesen */
                     copyflgs = 4; /* nur Kommentare kopieren */
                     written  = 1;
                     ret_val  = 0;
                   }
                   else state = 0;
                 }
              else state = 0;
              break;
  } }
  *k_version = vers;
  if (!written)
     { fprintf (ffo, "# ------\nkid =%s\n", k_name);
       f4f_wds (ffo, daten1, daten1_zahl,
                     daten2, daten2_zahl,
                     daten3, daten3_zahl,
                     daten4, daten4_zahl);
     }
  fclose (ffi); fclose (ffo);
  unlink (filename);
  rename (TEMPFILE, filename);
#ifdef DEBUG
    printf ("Write Over: vers=%d ret_val=%d\n", vers, ret_val);
    getch ();
    menue (0);
#endif
  return ret_val;
}

/* ------------------------------------------------------------------------ */
void f4f_wds (
FILE *fo,
char *daten1 [],
int   daten1_zahl,
char *daten2 [],
int   daten2_zahl,
char *daten3 [],
int   daten3_zahl,
char *daten4 [],
int   daten4_zahl)
{
  int i;
  int j= 0;

  for (i = 0; i < daten1_zahl; i++,j++)
      if (daten1 [i][0] || flg_write_empty)
         fprintf (fo, "%s =%s\n", identifier [j], daten1 [i]);
  for (i = 0; i < daten2_zahl; i++,j++)
      if (daten2 [i][0] || flg_write_empty)
         fprintf (fo, "%s =%s\n", identifier [j], daten2 [i]);
  for (i = 0; i < daten3_zahl; i++,j++)
      if (daten3 [i][0] || flg_write_empty)
         fprintf (fo, "%s =%s\n", identifier [j], daten3 [i]);
  for (i = 0; i < daten4_zahl; i++,j++)
      if (daten4 [i][0] || flg_write_empty)
         fprintf (fo, "%s =%s\n", identifier [j], daten4 [i]);
}
