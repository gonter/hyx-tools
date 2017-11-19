/*
 *  FILE %ds/rdtp/rdtp0106.c
 *
 *  restructured dynamic text parser
 *
 *  written:       1996-04-02
 *  latest update: 1996-06-22 12:37:14
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <gg/rdtp.h>
#include <gg/rdtp01.h>

/* #define DEBUG */

/* ------------------------------------------------------------------------ */
int rdtp_generate_transition_table (struct RDTP_GENERATOR *gen)
{
  int i;
  int g;
  int rc;
  struct RDTP_CLASS *class;
  struct RDTP_STATE_DEFINITION *st_def;

  printf (">> GEN name: %s (reset)\n", gen->generator_name);

  if ((class= gen->class) == (struct RDTP_CLASS *) 0)
  {
    if ((class= gen->class= (struct RDTP_CLASS *)
                            calloc (sizeof (struct RDTP_CLASS), 1))
        == (struct RDTP_CLASS *) 0) return -1;
  }

  ytree_process (gen->state_names, rdtp_unmark_states, (void *) gen);

  printf (">> GEN name: %s (init)\n", gen->generator_name);
  gen->generator_ok= 0;
  gen->defined_classes= 1; /* in the beginning everything is in class 0     */
  for (i= 0; i < RDTP_MAX_CLASSES; i++)
    gen->class_table [i]= 0;

  printf (">> GEN name: %s (pass 1)\n", gen->generator_name);
  rc= rdtp_mark_states (gen, gen->start_state, 1);
  gen->generator_ok= rc;

  printf ("defined_classes: %d\n", gen->defined_classes);
  class->max_classes= gen->defined_classes;
  for (i= 0; i < 256; i++)
  {
    g= gen->class_table [i];
    class->char_classes [i]= g;
#ifdef DEBUG
    printf ("0x%02X: %c %4d\n", i, (i > 0x20 && i < 0x7f) ? i : '.', g);
#endif /* DEBUG */
  }

  if (rc != 1)
  {
    printf ("rdtp0106: WARNING, generator not ok, trying to proceed!\n");
  }

  printf (">> GEN name: %s (pass 2)\n", gen->generator_name);
  ytree_process (gen->state_names, rdtp_pass2_transformation, (void *) gen);

  printf (">> GEN name: %s (pass 3)\n", gen->generator_name);
  ytree_process (gen->state_names, rdtp_pass3_transformation, (void *) gen);

  /* brushing up the parser class record */
  if ((st_def= (struct RDTP_STATE_DEFINITION *)
               ytree_get_value (gen->state_names,
                                (unsigned char *) gen->start_state))
               != (struct RDTP_STATE_DEFINITION *) 0
     )
  {
    printf ("rdtp0106: start_state: %s\n", st_def->state_name);

    class->start_state= st_def->state;

    class->method_for_undefined_state= gen->method_for_undefined_state;
    class-> state_for_undefined_state= gen-> state_for_undefined_state;
    class->method_for_undefined_input= gen->method_for_undefined_input;
    class-> state_for_undefined_input= gen-> state_for_undefined_input;
  }

  return 0;
}
