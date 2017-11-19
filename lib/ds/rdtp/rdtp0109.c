/*
 *  FILE %ds/rdtp/rdtp0109.c
 *
 *  locate all used states and mark them accordingly
 *
 *  written:       1996-04-02
 *  latest update: 1997-01-15 10:47:02
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/rdtp.h>
#include <gg/rdtp01.h>

/* ------------------------------------------------------------------------ */
int rdtp_mark_states (
struct RDTP_GENERATOR *gen,
char *start,
int verbosity)
/* return codes:                                                            */
/* 0 .. invalid or incomplete information                                   */
/* 1 .. everything's ok                                                     */
{
  struct RDTP_STATE_DEFINITION *st;
  struct RDTP_STATE_TRANSITION *tr;
  struct YTREE *names;
  int rv= 1;                    /* assume thing's are ok */
  int rc;

  if (gen == (struct RDTP_GENERATOR *) 0
      || (names= gen->state_names) == (struct YTREE *) 0
      || start == (char *) 0
     )
  {
    printf ("rdtp0109: invalid state data!\n");
    return 0;
  }

  if ((st= (struct RDTP_STATE_DEFINITION *)
           ytree_get_value (names, (unsigned char *) start))
           == (struct RDTP_STATE_DEFINITION *) 0
     )
  {
    printf ("rdtp0109: state '%s' undefined!\n", start);
    return 0;
  }

  if (st->state_used) return 1; /* we have been here before                 */

#ifdef DEBUG
  printf ("\n-----------------------------------\n");
  printf (">> mark '%s' as used\n", start);
#endif /* DEBUG */

  st->state_used= 1;            /* this has been visited                    */
  rdtp_process1_state_table (gen, st);

  for (tr= st->trans; tr != (struct RDTP_STATE_TRANSITION *) 0; tr= tr->next)
  {
    rc= rdtp_mark_states (gen, tr->state_to, verbosity);
    if (rc != 1) rv= 0;  /* propagate an error back up */
  }

  return rv;
}
