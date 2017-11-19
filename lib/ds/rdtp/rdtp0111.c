/*
 *  FILE %ds/rdtp/rdtp0111.c
 *
 *  restructured dynamic text parser
 *  allocate memory for the runtime state transition tables
 *
 *  written:       1996-04-02
 *  latest update: 1996-04-02 21:43:28
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
int rdtp_process2_state_table (
struct RDTP_GENERATOR *gen,
struct RDTP_STATE_DEFINITION *st)
{
  struct RDTP_STATE *stt;               /* runtime form of the state table  */
  int defined_classes;

  if (gen == (struct RDTP_GENERATOR *) 0
      || st == (struct RDTP_STATE_DEFINITION *) 0
      || !(st->state_used) /* otherwise dont care */
      || (st->state= stt= (struct RDTP_STATE *)
           calloc (sizeof (struct RDTP_STATE), 1))
           == (struct RDTP_STATE *) 0
      || (defined_classes= gen->defined_classes) <= 0
      || (stt->new_states= (struct RDTP_STATE **)
           calloc (sizeof (struct RDTP_STATE *), defined_classes))
           == (struct RDTP_STATE **) 0
      || (stt->transitions= (RDTP_state_transition **)
           calloc (sizeof (RDTP_state_transition *), defined_classes))
           == (RDTP_state_transition **) 0
#ifdef RDTP_DEBUG
      || (stt->transition_info= (char **)
           calloc (sizeof (char *), defined_classes))
           == (char **) 0
#endif /* RDTP_DEBUG */
     )
    return 0;

#ifdef RDTP_DEBUG
  printf (">> GEN state: %s (pass 2)\n", st->state_name);
#endif /* RDTP_DEBUG */
  
  return 0;
}
