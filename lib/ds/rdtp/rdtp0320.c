/*
 *  FILE %ds/rdtp/rdtp0320.c
 *
 *  restructured dynamic text parser
 *  SGML declaration entities
 *
 *  written:       1996-09-15
 *  latest update: 1996-09-15 11:23:18
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/rdtp.h>
#include <gg/rdtp01.h>
#include <gg/rdtp03.h>

/* ------------------------------------------------------------------------ */
int sgml_par_ent_beg (struct RDTP_THREAD *thr, int ch)
{
  return sgml_decl_token_beg (thr, ch, SGML_tokt_par_ent);
}

/* ------------------------------------------------------------------------ */
int sgml_par_ent_end (struct RDTP_THREAD *thr, int ch)
{
#ifdef MSDOS
  ch;
#endif

  return sgml_decl_token_end (thr, (char) 0);
}

