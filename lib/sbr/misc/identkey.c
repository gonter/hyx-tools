/*
 *  FILE ~/usr/sbr/identkey.c
 *
 *  Ermitteln des Key Codes aus einer KEY-Bezeichnung
 *
 *  written:       1989 07 09: aus Filemanager (Modul FM2.C) ausgekoppelt
 *  latest update: 1995-06-15
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/keys.h>

static int cdecl getnum (char *s, int i);

/* Code Table fuer ALT-Codes: --------------------------------------------- */
static unsigned int CODE_TABLE [] =
{
  0x0181,  0x0178,  0x0179,  0x017A,  0x017B,  0x017C,  0x017D,  0x017E,
  0x017F,  0x0180,  0x0000,  0x0000,  0x0000,  0x0183,  0x0000,  0x0000,
  0x0000,  0x011E,  0x0130,  0x012E,  0x0120,  0x0112,  0x0121,  0x0122,
  0x0123,  0x0117,  0x0124,  0x0125,  0x0126,  0x0132,  0x0131,  0x0118,
  0x0119,  0x0110,  0x0113,  0x011F,  0x0114,  0x0116,  0x012F,  0x0111,
  0x012D,  0x0115,  0x012C
} ;

/* ------------------------------------------------------------------------ */
unsigned int identify_key (char *key_name)      /* Bezeichnung des Keys     */
/* RETURN: key_code laut ~/usr/g/keys.h                                     */
/*         0 ... Key nicht identifiziert                                    */
{
  register int k;
  register unsigned int knum=0;

  /*************************/
  /*  0x#### Hex Key Code  */
  /*************************/
  if (key_name [0] == '0' &&
      (key_name [1] == 'x' || key_name [1] == 'X'))
   {
     knum= 0;
     for (key_name += 2; k= *key_name++; )
          if (k >= '0' && k <= '9') knum = knum*16 + k - '0';
     else if (k >= 'a' && k <= 'f') knum = knum*16 + k - 'a' + 10;
     else if (k >= 'A' && k <= 'F') knum = knum*16 + k - 'A' + 10;
     else break;
     return knum;
   }

  /***********************/
  /*  F1 .. F10 F11 F12  */
  /***********************/
  if ((key_name [0] == 'f' || key_name [0] == 'F') && key_name [1])
  {
    switch (knum= getnum (key_name, 1))
    {
      case  0:                 return 0;
      case 11: case 12:        return 0x0185 + knum -11;
      default: if (knum>12)    return 0;
                                return 0x013A + knum; 
    }
  }

  /***************************/
  /*  SF1 .. SF10 SF11 SF12  */
  /*  CF1 .. CF10 CF11 CF12  */
  /*  AF1 .. AF10 AF11 AF12  */
  /***************************/
  if (key_name [1] == 'f' || key_name [1] == 'F')
  {
    k= 0;
    switch (key_name [0])
    {
      case 'a': case 'A': k += 10;
      case 'c': case 'C': k += 10;
      case 's': case 'S':
        switch (knum= getnum (key_name, 2))
        {
          case  0:
            return 0;
          case 11:
          case 12:
            switch (k)
            {
              case  0: k = 2; break;
              case 10: k = 4; break;
              case 20: k = 6; break;
            }
            return 0x0185+k + knum-11;
          default:
            if (knum > 12) return 0;
            return knum + k + 0x0153;
        }
        break;
    }
  }

  /***********/
  /*  ALT-?  */
  /***********/
  if ((key_name [0] == 'a' || key_name [0] == 'A') &&
      (key_name [1] == 'l' || key_name [1] == 'L') &&
      (key_name [2] == 't' || key_name [2] == 'T') &&
      (key_name [3] == '-'))
  {
    if ((k= key_name [4] & 0x00FF) >= 'a' && k <= 'z')
      return CODE_TABLE [k-'a'+17];
    if (k >= '0' && k <= 'Z') return CODE_TABLE [k-'0'];
    if (k == '-') return 0x0182;
    return 0;
  }

  /***************************/
  /*  Control CURSOR Tasten  */
  /***************************/
  if ((key_name [0] == 'c' || key_name [0] == 'C') && key_name [1])
  {
    switch (key_name [1])
    {                                                           /************/
      case 'u': case 'U': return K_CUP;                         /* CUp      */
      case 'd': case 'D': return K_CDOWN;                       /* CDown    */
      case 'l': case 'L': return K_CLEFT;                       /* CLeft    */
      case 'r': case 'R': return K_CRIGHT;                      /* CRight   */
      case 'h': case 'H': return K_CTRLHOME;                    /* CHome    */
      case 'e': case 'E': return K_CTRLEND;                     /* CEnd     */
                                                                /************/
      case 'c': case 'C':
        switch (key_name [2])
        {                                                       /************/
          case 'l': case 'L': return K_CTRLLEFT;                /* CCLeft   */
          case 'r': case 'R': return K_CTRLRIGHT;               /* CCRight  */
        }                                                       /************/
        break;

      case 'p': case 'P': 
        if (key_name [2] != 'G' && key_name [2] != 'g') break;
        switch (key_name [3])
        {                                                       /************/
          case 'u': case 'U': return K_CTRLPGUP;                /* CPGUp    */
          case 'd': case 'D': return K_CTRLPGDN;                /* CPGDn    */
        }                                                       /************/
        break;
    }
    return 0;
  }

  if ((key_name [0] == 'p' || key_name [0] == 'P') &&
      (key_name [1] == 'g' || key_name [1] == 'G'))
    switch (key_name [2])
    {                                                           /************/
      case 'u': case 'U': return K_PGUP;                        /* PGUp     */
      case 'd': case 'D': return K_PGDN;                        /* PGDn     */
    }                                                           /************/

  if (key_name [1] != 0)
     switch (key_name [0])
     {                                                          /************/
       case 'd': case 'D': return K_DEL;                        /* Delete   */
       case 'e': case 'E': return K_END;                        /* End      */
       case 'h': case 'H': return K_HOME;                       /* Home     */
       case 'i': case 'I': return K_INS;                        /* Insert   */
     }                                                          /************/

  /********************/
  /*  Control Tasten  */
  /********************/
  if (key_name [0] == '^')
  {
    k= key_name [1];                                            /************/
    if (k >= 'a' && k <= 'z') return k - 'a' + 1;               /* ^a .. ^z */
    if (k >= 'A' && k <= 'Z') return k - 'A' + 1;               /* ^A .. ^Z */
  }                                                             /************/

  /* Normale Tasten */
  if (key_name [1] == 0)
     return key_name [0];

  return 0;
}

/* ------------------------------------------------------------------------ */
static int getnum (char *s, int i)
{
  int rv= 0;
  int ss;

  for (; ss= s [i] & 0x00FF; i++)
      if (ss >= '0' && ss <= '9')
           rv = 10*rv + ss - '0';
      else break;

  return rv;
}
