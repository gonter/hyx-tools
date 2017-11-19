/*
 *  FILE ~/usr/lexicon/lexut001.c
 *
 *  lexicon utility functions
 *  ISPELL derivation
 *
 *  written:       1991 04 27
 *  latest update: 1995-07-16
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <gg/lexutil.h>

/* ------------------------------------------------------------------------ */
int ISPELL_derive (
char *orig,             /* original word        */
int flag,               /* ISPELL flag          */
char *deriv)            /* derived word         */
{
  int last;
  int last_upper;
  int last1;
  int lng;

  if (orig == (char *) 0) return -1;
  strcpy (deriv, orig);
  lng= strlen (orig);
  if (lng <= 0) return 0;
  last= orig[lng-1];
  last_upper= (last >= 'A' && last <= 'Z');

  /* printf ("orig='%s' deriv='%s' flag=%c lng=%d last=%c last_upper=%d\n", */
  /* orig, deriv, flag, lng, last, last_upper); */

  switch (flag)
  {
    case 'O': case 'o':
      break;

    case 'V': case 'v':
      if (last == 'E' || last == 'e') lng--;
      strcpy (&deriv[lng], (last_upper) ? "IVE" : "ive");
      break;

    case 'N': case 'n':
      if (last == 'E' || last == 'e')
           strcpy (&deriv [lng-1], (last_upper) ? "ION" : "ion");
      else
      if (last == 'Y' || last == 'y')
           strcpy (&deriv [lng-1], (last_upper) ? "ICATION" : "ication");
      else strcpy (&deriv [lng], (last_upper) ? "EN" : "en");
      break;

    case 'X': case 'x':
      if (last == 'E' || last == 'e')
           strcpy (&deriv [lng-1], (last_upper) ? "IONS" : "ions");
      else if (last == 'Y' || last == 'y')
           strcpy (&deriv [lng-1], (last_upper) ? "ICATIONS" : "ications");
      else strcpy (&deriv [lng], (last_upper) ? "ENS" : "ens");
      break;

    case 'H': case 'h':
      if (last == 'Y' || last == 'y')
           strcpy (&deriv [lng-1], (last_upper) ? "IETH" : "ieth");
      else strcpy (&deriv [lng], (last_upper) ? "TH" : "th");
      break;

    case 'Y': case 'y':
      strcpy (&deriv [lng], (last_upper) ? "LY" : "ly");
      break;

    case 'G': case 'g':
      if (last == 'E' || last == 'e') lng--;
      strcpy (&deriv [lng], (last_upper) ? "ING" : "ing");
      break;

    case 'J': case 'j':
      if (last == 'E' || last == 'e') lng--;
      strcpy (&deriv [lng], (last_upper) ? "INGS" : "ings");
      break;

    case 'D': case 'd':
      if (last == 'E' || last == 'e')
           strcpy (&deriv [lng], (last_upper) ? "D" : "d");
      else
      {
        if (last == 'Y' || last == 'y')
        {
          last1= orig [lng-2];
          if (   last1 == 'A' || last1 == 'a'
              || last1 == 'E' || last1 == 'e'
              || last1 == 'I' || last1 == 'i'
              || last1 == 'O' || last1 == 'o'
              || last1 == 'U' || last1 == 'u')
            goto SPECIAL_D;
          else strcpy (&deriv [lng-1], (last_upper) ? "IED" : "ied");
        }
        else
        {
SPECIAL_D:
          strcpy (&deriv [lng], (last_upper) ? "ED" : "ed");
        }
      }
      break;

    case 'T': case 't':
      if (last == 'E' || last == 'e')
         strcpy (&deriv[lng], (last_upper) ? "ST" : "st");
      else
      {
        if (last == 'Y' || last == 'y')
        {
          last1= orig [lng-2];
          if (   last1 == 'A' || last1 == 'a'
              || last1 == 'E' || last1 == 'e'
              || last1 == 'I' || last1 == 'i'
              || last1 == 'O' || last1 == 'o'
              || last1 == 'U' || last1 == 'u')
            goto SPECIAL_T;
          else strcpy (&deriv [lng-1], (last_upper) ? "IEST" : "iest");
        }
        else
        {
SPECIAL_T:
          strcpy (&deriv [lng], (last_upper) ? "EST" : "est");
        }
      }
      break;

    case 'R': case 'r':
      if (last == 'E' || last == 'e')
        strcpy (&deriv[lng], (last_upper) ? "R" : "r");
      else
      {
        if (last == 'Y' || last == 'y')
        {
          last1= orig [lng-2];
          if (   last1 == 'A' || last1 == 'a'
              || last1 == 'E' || last1 == 'e'
              || last1 == 'I' || last1 == 'i'
              || last1 == 'O' || last1 == 'o'
              || last1 == 'U' || last1 == 'u')
            goto SPECIAL_R;
          else strcpy (&deriv [lng-1], (last_upper) ? "IER" : "ier");
        }
        else
        {
SPECIAL_R:
          strcpy (&deriv [lng], (last_upper) ? "ER" : "er");
        }
      }
      break;

    case 'Z': case 'z':
      if (last == 'E' || last == 'e')
           strcpy (&deriv[lng], (last_upper) ? "RS" : "rs");
      else
      {
        if (last == 'Y' || last == 'y')
        {
          last1= orig [lng-2];
          if (   last1 == 'A' || last1 == 'a'
              || last1 == 'E' || last1 == 'e'
              || last1 == 'I' || last1 == 'i'
              || last1 == 'O' || last1 == 'o'
              || last1 == 'U' || last1 == 'u')
            goto SPECIAL_Z;
          else strcpy (&deriv [lng-1], (last_upper) ? "IERS" : "iers");
        }
        else
        {
SPECIAL_Z:
          strcpy (&deriv [lng], (last_upper) ? "ERS" : "ers");
        }
      }
      break;

    case 'S': case 's':
      if (last == 'Y' || last == 'y')
      {
        last1 = orig [lng-2];
        if (   last1 == 'A' || last1 == 'a'
            || last1 == 'E' || last1 == 'e'
            || last1 == 'I' || last1 == 'i'
            || last1 == 'O' || last1 == 'o'
            || last1 == 'U' || last1 == 'u')
          goto SPECIAL_S;
        else strcpy (&deriv [lng-1], (last_upper) ? "IES" : "ies");
      }
      else
      if (   last == 'S' || last == 's'
          || last == 'X' || last == 'x'
          || last == 'Z' || last == 'z')
        strcpy (&deriv [lng], (last_upper) ? "ES" : "es");
      else
      {
SPECIAL_S:
        strcpy (&deriv[lng], (last_upper) ? "S" : "s");
      }
      break;

    case 'P': case 'p':
      if (last == 'Y' || last == 'y')
      {
        last1= orig [lng-2];
        if (   last1 == 'A' || last1 == 'a'
            || last1 == 'E' || last1 == 'e'
            || last1 == 'I' || last1 == 'i'
            || last1 == 'O' || last1 == 'o'
            || last1 == 'U' || last1 == 'u')
          goto SPECIAL_P;
        else strcpy (&deriv [lng-1], (last_upper) ? "INESS" : "iness");
      }
      else
      {
SPECIAL_P:
        strcpy (&deriv [lng], (last_upper) ? "NESS" : "ness");
      }
      break;

    case 'M': case 'm':
      strcpy (&deriv [lng], (last_upper) ? "'S" : "'s");
      break;

    default: return -1;
  }

  return 0;
}
