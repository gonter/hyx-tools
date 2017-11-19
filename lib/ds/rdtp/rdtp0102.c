/*
 *  FILE %ds/rdtp/rdtp0102.c
 *
 *  restructured dynamic text parser
 *
 *  written:       1996-04-01
 *  latest update: 1996-05-07 13:34:07
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/rdtp.h>
#include <gg/rdtp01.h>

/* ------------------------------------------------------------------------ */
int rdtp_load_static_table (
struct RDTP_GENERATOR *gen,
struct RDTP_STATIC_STATE_TABLE state_table [])
{
  struct RDTP_STATIC_STATE_TABLE *entry;

  if (gen == (struct RDTP_GENERATOR *) 0
      || state_table == (struct RDTP_STATIC_STATE_TABLE *) 0
     )
    return -1;

  for (entry= &state_table [0];
       entry->state_from != (char *) 0;
       entry++)
  {
    rdtp_define_transition (gen,
                            entry->state_from,  entry->state_to,
                            entry->range_begin, entry->range_end,
                            entry->method,
                            entry->method_info);
  }

  return 0;
}
