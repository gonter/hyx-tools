/*
 *  FILE %ds/ggcrypt/ggcryp04.c
 *
 *  written:       1990 08 25: as %usr/inc/garbling.inc
 *                 1994-09-18: reorganized to %sbr/ggcryp04.c
 *  latest update: 1995-08-15
 *  $Id: ggcryp04.c,v 1.2 2007/12/02 11:58:08 gonter Exp $
 *
 */

#include <stdio.h>
#include <string.h>
#include <gg/ggcrypt.h>

/* ------------------------------------------------------------------------ */
static char G_CODE [30];
static int  G_PTR;
static int  G_LAST= -1;         /* last character run length encoded        */
static int  G_CNT;              /* run length counter                       */

/* ------------------------------------------------------------------------ */
int ggcrypt_set_code (char *cp)
{
  G_CODE [0]= 0;
  G_PTR= 0;
  G_LAST= -1;
  G_CNT= 0;
  if (cp == (char *) 0 || *cp == 0) return -1;
  strncpy (G_CODE, cp, 28);

  return 0;
}

/* ------------------------------------------------------------------------ */
int ggcrypt_fputc_code (int c, FILE *f)
{
  if (!G_CODE [0]) return fputc (c, f);
  if (G_LAST != c)
  {
    ggcrypt_flush_last (f);
    G_LAST= c;
    G_CNT= 1;
  }
  else G_CNT++;

  return 0;
}

/* ------------------------------------------------------------------------ */
int ggcrypt_fgetc_code (FILE *f)
{
  int c;

  if (!G_CODE [0]) return fgetc (f) & 0x00FF;
RE_DO:
  if (G_CNT > 0)
  {
    G_CNT--;
    return G_LAST;
  }

  c= ggcrypt_encode (fgetc (f) & 0x00FF);
  if (c == 0x01)
  {
    G_LAST= ggcrypt_encode (fgetc (f) & 0x00FF);
    G_CNT= ggcrypt_encode (fgetc (f) & 0x00FF);
    goto RE_DO;
  }
  else return c;
}

/* ------------------------------------------------------------------------ */
int ggcrypt_flush_last (FILE *f)
{
  switch (G_LAST)
  {
    default:
      if (G_CNT == 1)
      {
        fputc (ggcrypt_encode (G_LAST), f);
        break;
      }
    case 1:
      fputc (ggcrypt_encode (0x01),   f);
      fputc (ggcrypt_encode (G_LAST), f);
      fputc (ggcrypt_encode (G_CNT),  f);
    case -1:
      break;
  }

  return 0;
}

/* ------------------------------------------------------------------------ */
int ggcrypt_encode (int c)
{
  c= (c ^ (G_CODE [G_PTR++] & 0x00FF)) & 0x00FF;
  if (G_CODE [G_PTR] == 0) G_PTR= 0;
  return c;
}
