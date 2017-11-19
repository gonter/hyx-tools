/*
 *  FILE %ds/rdtp/rdtp0104.c
 *
 *  restructured dynamic text parser
 *
 *  written:       1996-04-01
 *  latest update: 1996-04-02  9:26:16
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/rdtp.h>
#include <gg/rdtp01.h>

/* ------------------------------------------------------------------------ */
int rdtp_print_generator (
struct RDTP_GENERATOR *gen,
FILE *fo)
{
  fprintf (fo, "name: %s\n", gen->generator_name);
  ytree_process (gen->state_names, rdtp_print_states, (void *) fo);

  return 0;
}
