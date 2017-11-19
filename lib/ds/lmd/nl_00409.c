/*
 *  FILE ~/usr/nl_kr/lib/nl_00409.c
 *
 *  data
 *  - functions to create LUTs -- using YTREE
 *  - see also: wordcr05.c (word reference system)
 *
 *  written:       1990 06 04
 *                 1990 11 16: revision
 *                 1991 03 16: revision; AIX
 *                 1993-02-28: complete redesign of the refenece system
 *                 1994-12-19: isolated from wordcr04.c
 *  latest update: 1995-07-24
 *
 */

#include <stdio.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
void lmd_print_04statistics (
struct LMDC_CONTROL *lmdc,
FILE *fo)
{
  fprintf (fo, "sw_idx=%ld\n", lmdc->LMDC_cnt_sw_idx);
}
