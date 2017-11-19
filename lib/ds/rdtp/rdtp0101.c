/*
 *  FILE %ds/rdtp/rdtp0101.c
 *
 *  restructured dynamic text parser
 *
 *  written:       1996-04-01
 *  latest update: 1996-04-02 10:37:13
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <string.h>
#include <gg/rdtp.h>
#include <gg/rdtp01.h>

/* ------------------------------------------------------------------------ */
int rdtp_define_transition (
struct RDTP_GENERATOR *gen,
char *from,
char *to,
long begin,
long end,
RDTP_state_transition *method,
char *method_info)
{
  struct RDTP_STATE_DEFINITION *std;
  struct RDTP_STATE_TRANSITION *trans;

  if (gen == (struct RDTP_GENERATOR *) 0
      || from == (char *) 0
      || to == (char *) 0
      || (std= rdtp_find_state_definition (gen, from))
           == (struct RDTP_STATE_DEFINITION *) 0
      || (trans= (struct RDTP_STATE_TRANSITION *)
                 calloc (sizeof (struct RDTP_STATE_TRANSITION), 1))
           == (struct RDTP_STATE_TRANSITION *) 0
     )
    return -1;

  trans->state_to= strdup (to);
  if (method_info != (char *) 0) trans->method_info= strdup (method_info);
  trans->range_begin= begin;
  trans->range_end= end;
  trans->method= method;

  trans->next= std->trans;
  std->trans= trans;

  return 0;
}
