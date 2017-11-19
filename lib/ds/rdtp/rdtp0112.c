/*
 *  FILE %ds/rdtp/rdtp0112.c
 *
 *  restructured dynamic text parser
 *  assign values to the runtime state transition tables
 *
 *  written:       1996-04-02
 *  latest update: 1997-01-15 10:48:04
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <gg/rdtp.h>
#include <gg/rdtp01.h>

/* ------------------------------------------------------------------------ */
int rdtp_process3_state_table (
struct RDTP_GENERATOR *gen,
struct RDTP_STATE_DEFINITION *st)
{
  struct RDTP_STATE_TRANSITION *t1;     /* setup form of a state transition */
  struct RDTP_STATE_DEFINITION *st2;
  struct RDTP_STATE *stt;               /* runtime form of the state table  */

  struct RDTP_STATE **new_states;
  RDTP_state_transition **transitions;
#ifdef RDTP_DEBUG
  char **transition_info;
#endif /* RDTP_DEBUG */

  int class;
  int ch;

  if (gen == (struct RDTP_GENERATOR *) 0
      || st == (struct RDTP_STATE_DEFINITION *) 0
      || !(st->state_used) /* otherwise dont care */
      || (stt= st->state) == (struct RDTP_STATE *) 0
      || (new_states= stt->new_states) == (struct RDTP_STATE **) 0
      || (transitions= stt->transitions) == (RDTP_state_transition **) 0
#ifdef RDTP_DEBUG
      || (transition_info= stt->transition_info) == (char **) 0
#endif /* RDTP_DEBUG */
     )
    return 0;

#ifdef RDTP_DEBUG
  printf (">> GEN state: %s (pass 3)\n", st->state_name);
  stt->state_name= st->state_name;
#endif /* RDTP_DEBUG */
  
  /* step 1: identify different classes in this state */
  for (t1= st->trans;
       t1 != (struct RDTP_STATE_TRANSITION *) 0;
       t1= t1->next)
  {
    for (ch= (int) t1->range_begin; ch <= (int) t1->range_end; ch++)
    {
      class= gen->class_table [ch];

      /* define values if not already defined */
      if (new_states [class] == (struct RDTP_STATE *) 0
          && transitions [class] == (RDTP_state_transition *) 0
         )
      {
        if ((st2= (struct RDTP_STATE_DEFINITION *)
                  ytree_get_value (gen->state_names,
                                   (unsigned char *) t1->state_to))
            != (struct RDTP_STATE_DEFINITION *) 0
           )
          new_states [class]= st2->state;

        transitions [class]= t1->method;

#ifdef RDTP_DEBUG
        transition_info [class]= t1->method_info;
#endif /* RDTP_DEBUG */
      }
    }
  }

  return 0;
}
