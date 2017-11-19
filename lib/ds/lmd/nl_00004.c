/*
 *  FILE ~/usr/nl_kr/lib/nl_00004.c
 *
 *  nl_get_token (fi, s, mode, push_back)
 *
 *  Token-String aus einem File lesen
 *
 *  written:       1990 01 21: Erweiterung von nl_get_str [NL_00004.C]
 *                 1993-03-02: latest update;  NOTE: CMS needs to be revised!
 *  latest update: 1995-04-01
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/lookup.h>

/* Control Vektor: -------------------------------------------------------- */
/* Bit 0: A..Z, a..z                            41 .. 5A, 61 .. 7A          */
/* Bit 1: 0..9                                  30 .. 39                    */
/* Bit 2: Nationale Sonderzeichen:              80 .. A8                    */
/* Bit 3: Symbole:                              E0, E2 .. FF                */
/* Bit 4: Graphische Characters:                B0 .. DF                    */
/* Bit 5: $ _                                   24 40 5F                    */
/* Bit 6: Satzzeichen: ! " ' , . : ; ? ` @      21,22,27,2C,2E,3A,3B,3F,60  */
/* Bit 7: sonstige Zeichen                                                  */

/* Ein Token einlesen: ---------------------------------------------------- */
int nl_get_token (
FILE *fi,               /* Input File                                       */
char *s,                /* gelesenes Token                                  */
int   mode,             /* Controlvektor                                    */
int  *push_back,        /* zuletzt gelesenes Zeichen                        */
long *filepos_beg)      /* Beginn des Wortes im File                        */
/* Return: Controlvektor ... Das Bit gibt an warum abgebrochen wurde;       */
/*         0 -> EOF                                                         */
{
  int ch;
  int rv= 0;
  int idx= 0;

  if (*push_back)               /* what was the last character ?? */
  {
    ch= *push_back;
    *push_back= 0;
    goto A;
  }

  /* Spaces ueberlesen */
  for (;;)
  {
    *filepos_beg= ftell (fi);
    ch= fgetc (fi) & 0x00FF;
    if (feof(fi))
    {
      *s= 0;
      return 0;
    }
A:
    if (ch > ' ') break;
  }

goto B;
  /* Wort einlesen */
  for (;;idx++)
  {
    if (idx == 0) *filepos_beg= ftell (fi);
    ch= fgetc (fi) & 0x00FF;
    if (feof(fi))
    {
      *s= 0;
      return rv;
    }
B:
    *s++= (char) ch;
    *s= 0;
    if ((mode & 0x0001) && (
#ifdef __CMS__
         (ch >= 'a' && ch <= 'i') ||
         (ch >= 'j' && ch <= 'r') ||
         (ch >= 's' && ch <= 'z') ||
         (ch >= 'A' && ch <= 'I') ||
         (ch >= 'J' && ch <= 'R') ||
         (ch >= 'S' && ch <= 'Z')
#else
         (ch >= 'a' && ch <= 'z') ||
         (ch >= 'A' && ch <= 'Z') 
#endif
                                 ))                { rv |= 0x0001; continue; }
    if ((mode & 0x0002) && ch >= '0' && ch <= '9') { rv |= 0x0002; continue; }
#ifndef __CMS__
    if ((mode & 0x0004) && ch>=0x80 && ch<=0xA8)   { rv |= 0x0004; continue; }
    if ((mode & 0x0004) && ch==0xE1)               { rv |= 0x0004; continue; }
    if ((mode & 0x0008) && ch>=0xE0 && ch<=0xEF)   { rv |= 0x0008; continue; }
    if ((mode & 0x0010) && ch>=0xB0 && ch<=0xDF)   { rv |= 0x0010; continue; }
#endif
    if ((mode & 0x0020) &&
        (ch=='_' || ch=='$'))                      { rv |= 0x0020; continue; }
    if ((mode & 0x0040) &&
        (ch=='!' || ch=='\"' || ch=='\'' ||
         ch=='`' || ch==','  || ch=='.'  ||
         ch=='@' ||
         ch==':' || ch==';'  || ch=='?'))          { rv |= 0x0040; continue; }
    break;
  }

  if (idx == 0)
  {
    if (
#ifdef __CMS__
         (ch >= 'a' && ch <= 'i') ||
         (ch >= 'j' && ch <= 'r') ||
         (ch >= 's' && ch <= 'z') ||
         (ch >= 'A' && ch <= 'I') ||
         (ch >= 'J' && ch <= 'R') ||
         (ch >= 'S' && ch <= 'Z')
#else
         (ch >= 'a' && ch <= 'z') ||
         (ch >= 'A' && ch <= 'Z') 
#endif
                                  )                { rv |= 0x0001; goto X;   }
    if (                   ch >= '0' && ch <= '9') { rv |= 0x0002; goto X;   }
#ifndef __CMS__
    if (                   ch>=0x80 && ch<=0xA8)   { rv |= 0x0004; goto X;   }
    if (                   ch==0xE1)               { rv |= 0x0004; goto X;   }
    if (                   ch>=0xE0 && ch<=0xEF)   { rv |= 0x0008; goto X;   }
    if (                   ch>=0xB0 && ch<=0xDF)   { rv |= 0x0010; goto X;   }
#endif
    if ( ch=='_' || ch=='$' )                      { rv |= 0x0020; goto X;   }
    if ( ch=='!' || ch=='\"' || ch=='\'' ||
         ch=='`' || ch==','  || ch=='.'  ||
         ch=='@' ||
         ch==':' || ch==';'  || ch=='?' )          { rv |= 0x0040; goto X;   }
    rv |= 0x0080;
  }
  else {
         --s;
         *s= 0;
         *push_back= ch;
       }
X:
  return rv;
}
