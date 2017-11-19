/*
 *  FILE %ned/13/ned1392.c
 *
 *  blind definitions
 *  T2D: fix this !!!
 *
 *  written:       1997-08-03
 *  latest update: 1999-04-25 16:37:01
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <stdio.h>
#include <gg/convent.h>
#include "ed.h"
#include "proto.h"

extern int COL_UNKNOWN_FEATURE;
extern int CHR_UNKNOWN_FEATURE;

/* ------------------------------------------------------------------------ */
/* see also: */ int ned_identify_feature (
struct WINDOWCTRL *wc,          /* window where all that happens            */
struct LINE *lp,                /* line to which feature is attached        */
int offset,                     /* offset in line where                     */
int feature_type,               /* general class, such as Ftype_SGML_TAG    */
struct FEATURE *ft,             /* feature to be identified                 */
char *lin,                      /* buffer containing feature to identify    */
char *repl_array,               /* buffer to place replacement code into    */
int *repl_size,                 /* used space in that buffer                */
int repl_max)                   /* maximum size of that buffer              */
/* Return: -1 .. error;  0 .. ok;  1 .. feature not needed (but defined)    */
{
  int ev;
  int f_entity_valid;

#ifdef MSDOS
  wc; lp; offset; repl_max;
#endif /* MSDOS */

  switch (feature_type)
  {
    case Ftype_SGML_ENTITY:
      ev= find_pc_sgml_entity (lin);
      f_entity_valid= (ev >= 0x00 && ev <= 0xFF);
      ft->ftr_colour= (f_entity_valid)
                      ? COL_DEF_TEXT : COL_UNKNOWN_FEATURE;

      if (!f_entity_valid) ev= CHR_UNKNOWN_FEATURE;
      *repl_array= (char) ev;
      *repl_size= 1;
      ft->ftr_display_mode= FTR_display_replarray;
      ft->ftr_replarray_size= 1;
      return (f_entity_valid) ? 1 : 0;
      break;
  }

  return 0;
}
