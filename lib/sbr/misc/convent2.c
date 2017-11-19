/*
 *  FILE %sbr/convent2.c
 *
 *  Convert PC characters to SGML entities
 *
 *  written:       1991 07 03
 *  latest update: 1997-03-31 10:55:27
 *  $Id: convent2.c,v 1.2 2005/09/04 20:27:37 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <gg/dpp.h>
#include <gg/convent.h>

/* ------------------------------------------------------------------------ */
struct XX
{
  int v;
  char *nm;
} ;

/* ------------------------------------------------------------------------ */
#define xx_siz 4
static struct XX PC_ENTITY_xx [xx_siz] =
{
  /* SGML meta characters */
  { 0x26, "amp" } ,
  { 0x3C, "lt" } ,
  { 0x3E, "gt" } ,

  { 0x15, "sect" }
};

/* ------------------------------------------------------------------------ */
static char *PC_ENTITY_a [] =
{
/* 0x80 */ "Ccedil",
/* 0x81 */ "uuml",
/* 0x82 */ "eacute",
/* 0x83 */ "acirc",
/* 0x84 */ "auml",
/* 0x85 */ "agrave",
/* 0x86 */ "adot",
/* 0x87 */ "ccedil",
/* 0x88 */ "ecirc",
/* 0x89 */ "euml",
/* 0x8A */ "egrave",
/* 0x8B */ "iuml",
/* 0x8C */ "icirc",
/* 0x8D */ "igrave",
/* 0x8E */ "Auml",
/* 0x8F */ "Acirc",

/* 0x90 */ "Eacute",
/* 0x91 */ "aelig",
/* 0x92 */ "AElig",
/* 0x93 */ "ocirc",
/* 0x94 */ "ouml",
/* 0x95 */ "ograve",
/* 0x96 */ "ucirc",
/* 0x97 */ "ugrave",
/* 0x98 */ "yuml",
/* 0x99 */ "Ouml",
/* 0x9A */ "Uuml",
/* 0x9B */ "cent",
/* 0x9C */ "pound",
/* 0x9D */ "yen",
/* 0x9E */ "Ptlig",             /* P und t zusammengezogen */
/* 0x9F */ "funnyf",            /* „hnlich wie ein kleines f */

/* 0xA0 */ "aacute",
/* 0xA1 */ "iacute",
/* 0xA2 */ "oacute",
/* 0xA3 */ "uacute",
/* 0xA4 */ "ntilde",
/* 0xA5 */ "Ntilde",
/* 0xA6 */ "aunderl",
/* 0xA7 */ "ounderl",
/* 0xA8 */ "iquest",
/* 0xA9 */ "inot",              /* inverses NOT ?? */
/* 0xAA */ "not",
/* 0xAB */ "frac12",
/* 0xAC */ "frac14",
/* 0xAD */ "iexcl",
/* 0xAE */ "laquo",
/* 0xAF */ "raquo"
} ;

/* ------------------------------------------------------------------------ */
static char *PC_ENTITY_b [] =
{
/* 0xE0 */ "agr",
/* 0xE1 */ "szlig",
/* 0xE2 */ "Ggr",
/* 0xE3 */ "pgr",
/* 0xE4 */ "Sgr",
/* 0xE5 */ "sgr",
/* 0xE6 */ "mgr",
/* 0xE7 */ "tgr",
/* 0xE8 */ "PHgr",
/* 0xE9 */ "THgr",
/* 0xEA */ "OHgr",
/* 0xEB */ "dgr",
/* 0xEC */ "infin",
/* 0xED */ "Oslash",            /* Durchschnitt ??? */
/* 0xEE */ "isin",
/* 0xEF */ "cap",

/* 0xF0 */ "equiv",
/* 0xF1 */ "plusmn",
/* 0xF2 */ "ge",
/* 0xF3 */ "le",
/* 0xF4 */ "intu",              /* obere  H„lfte des Integralzeichens!!     */
/* 0xF5 */ "intl",              /* untere H„lfte des Integralzeichens !!    */
/* 0xF6 */ "divide",
/* 0xF7 */ "sim",
/* 0xF8 */ "deg",
/* 0xF9 */ "bmiddot",
/* 0xFA */ "middot",
/* 0xFB */ "radic",
/* 0xFC */ "supn",
/* 0xFD */ "sup2"
} ;

/* ------------------------------------------------------------------------ */
char *get_pc_sgml_entity (int ch)
{
  int i;

  for (i= 0; i<xx_siz; i++)
    if (PC_ENTITY_xx[i].v == ch)
      return PC_ENTITY_xx[i].nm;

  if (ch >= 0x80 && ch <= 0xAF)
  {
    return PC_ENTITY_a [ch-0x80]; 
  }

  if (ch >= 0xE0 && ch <= 0xFD)
  {
    return PC_ENTITY_b [ch-0xE0]; 
  }
  return (char *) 0;
}

/* ------------------------------------------------------------------------ */
int find_pc_sgml_entity (const char *s)
{
  int i;

  if (s == (char *) 0 || *s == 0) return -1;

  if (*s == '#')
  {
    long v;

    s++;
    if (*s == 0) return -1;
    v= get_parameter_value (s);
    return (v < 0 || v > 255)  ? -1 : (int) v;
  }

  for (i= 0; i < xx_siz; i++)
    if (strcmp (PC_ENTITY_xx[i].nm, s) == 0)
      return PC_ENTITY_xx[i].v;

  for (i= 0x00; i <= 0x2F; i++)
  {
    if (PC_ENTITY_a [i] != (char *) 0
      && strcmp (PC_ENTITY_a [i], s) == 0) return i + 0x80;
  }

  for (i= 0x00; i <= 0x1D; i++)
  {
    if (PC_ENTITY_b [i] != (char *) 0
      && strcmp (PC_ENTITY_b [i], s) == 0) return i + 0xE0;
  }

  return -1;
}
