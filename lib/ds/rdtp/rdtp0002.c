/*
 *  FILE %ds/rdtp/rdtp0002.c
 *
 *  restructured dynamic text parser
 *
 *  written:       1996-04-02
 *  latest update: 1996-04-02 15:07:54
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <gg/rdtp.h>

/* ------------------------------------------------------------------------ */
struct RDTP_THREAD *rdtp_new_thread (struct RDTP_CLASS *cl)
{
  struct RDTP_THREAD *thr= (struct RDTP_THREAD *) 0;

  if (cl != (struct RDTP_CLASS *) 0
      && (thr= (struct RDTP_THREAD *)
               calloc (sizeof (struct RDTP_THREAD), 1))
               != (struct RDTP_THREAD *) 0
     )
  {
    thr->class= cl;
    thr->current_state= cl->start_state;
  }

  return thr;
}
