/*
 *  FILE %ds/rdtp/rdtp0115.c
 *
 *  restructured dynamic text parser
 *  drop any old state table
 *
 *  written:       1996-04-02
 *  latest update: 1996-06-22 12:50:54
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <gg/strings.h>
#include <gg/rdtp.h>
#include <gg/rdtp01.h>

/* ------------------------------------------------------------------------ */
int rdtp_drop_state_table (
struct RDTP_GENERATOR *gen,
struct RDTP_STATE_DEFINITION *st)
{
  struct RDTP_STATE *stt;               /* runtime form of the state table  */
#ifdef NOT_USED
  struct RDTP_STATE **new_states;
  RDTP_state_transition **transitions;
#ifdef RDTP_DEBUG
  char **transition_info;
#endif /* RDTP_DEBUG */
#endif /* NOT_USED */

  if (gen == (struct RDTP_GENERATOR *) 0
      || st == (struct RDTP_STATE_DEFINITION *) 0
      || (stt= st->state) == (struct RDTP_STATE *) 0
     )
    return 0;

  /* NOTE: ignores st->state_used and drops even those tables */

  printf (">> GEN state: %s (drop tables)\n", st->state_name);
  
#ifdef NOT_USED
  if ((new_states= stt->new_states) != (struct RDTP_STATE **) 0)
    free (new_states);

  if ((transitions= stt->transitions) != (RDTP_state_transition **) 0)
    free (transitions);

#ifdef RDTP_DEBUG
  if ((transition_info= stt->transition_info) != (char **) 0)
    free (transition_info);
#endif /* RDTP_DEBUG */
#endif /* NOT_USED */

  free_or_what ((void *) stt->new_states);
  free_or_what ((void *) stt->transitions);
#ifdef RDTP_DEBUG
  free_or_what ((void *) stt->transition_info);
#endif /* RDTP_DEBUG */

  free (stt);
  st->state= (struct RDTP_STATE *) 0;

  return 0;
}
