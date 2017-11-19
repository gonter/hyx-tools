/*
 *  FILE %ds/hyxl/hyxl0004.c
 *
 *  return the colour value of the code in the string
 *  T2D: this is closely related to DOS!
 *
 *  written:       1994-07-03
 *  latest update: 1997-01-15 11:20:39
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <gg/dpp.h>
#include <gg/ytree.h>
#include <gg/hyx.h>

/* ------------------------------------------------------------------------ */
struct HYXL0004_color_table
{
  unsigned char *name;
  long value;
} ;

/* ------------------------------------------------------------------------ */
struct YTREE *color_codes= (struct YTREE *) 0;

/* ------------------------------------------------------------------------ */
static unsigned char __default[]= "$$default";
static struct HYXL0004_color_table CT []=
{
  { "hyx.l",      31 },
  { "mark",      106 },
  { "index",      15 },

  /* programming, e.g. in C */
  { "incl",       13 },
  { "pgm.incl",   13 },
  { "pgm.data",   14 },
  { "pgm.struct", 15 },
  { "pgm.func",   31 },

  { "$$text",           0x0100  },      /* default text color               */
  { "$$ftr",            0x0200  },      /* default feature colour           */

  { __default,    12 },                 /* default color code               */

  { (unsigned char *) 0,    0 }
} ;

/* ------------------------------------------------------------------------ */
static int hyxl0004_init (void);
static int hyxl0004_init ()
{
  int i;

  for (i= 0;; i++)
  {
    if (CT[i].name == (unsigned char *) 0) break;
    ytree_set_value (&color_codes, CT[i].name, CT[i].value);
  }
  return 0;
}

/* ------------------------------------------------------------------------ */
long hyx_identify_color_code (unsigned char *s)
{
  long cv;

  if ((cv= get_parameter_value ((char *) s)) == 0L)
  { /* color code is not numeric, so look it up */
    if (color_codes == (struct YTREE *) 0) hyxl0004_init ();

    if ((cv= ytree_get_value (color_codes, s)) == 0L)
      cv= ytree_get_value (color_codes, __default);
  }

  return cv;
}

/* ------------------------------------------------------------------------ */
long hyx_set_color_code (unsigned char *name, long value)
{
  if (name == (unsigned char *) 0 || *name == (unsigned char) 0) return 0L;

  if (color_codes == (struct YTREE *) 0) hyxl0004_init ();

  return ytree_set_value (&color_codes, name, value);
}
