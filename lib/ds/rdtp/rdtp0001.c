/*
 *  FILE %ds/rdtp/rdtp0001.c
 *
 *  restructured dynamic text parser
 *
 *  written:       1996-04-01
 *  latest update: 1997-01-15 10:45:49
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/strings.h>
#include <gg/rdtp.h>

#ifdef RDTP_DEBUG
#include <stdio.h>
#endif /* RDTP_DEBUG */

/* ------------------------------------------------------------------------ */
int rdtp_parse_char (
struct RDTP_THREAD *thread,
int ch)
{
  struct RDTP_CLASS *cl;
  struct RDTP_STATE *st, *new_state;
  RDTP_state_transition *method;
  int char_class;
  int rc= 0;

  if (thread == (struct RDTP_THREAD *) 0
      || ch < 0
      || ch > 255
      || (cl= thread->class) == (struct RDTP_CLASS *) 0
      || (char_class= cl->char_classes [ch]) < 0
      || char_class > cl->max_classes
     )
   return -1;

  if ((st= thread->current_state) == (struct RDTP_STATE *) 0)
  { /* current state is undefined; perform self correction, if possible */
    rc= -1;

    st=     cl->state_for_undefined_state;
    method= cl->method_for_undefined_state;
  }

  if (st != (struct RDTP_STATE *) 0)
  {
    rc= 0;

    new_state= st->new_states [char_class];

#ifdef RDTP_DEBUG
    printf ("0x%02X %c %4d %-10s -> %-10s %s\n",
            ch,
            (ch > 0x20 && ch < 0x7F) ? ch : '.',
            char_class,
            st->state_name,
            (new_state == (struct RDTP_STATE *) 0)
              ? "(undef)"
              : XSTR (new_state->state_name),
            XSTR (st->transition_info [char_class]));
#endif /* RDTP_DEBUG */

    if (new_state == (struct RDTP_STATE *) 0)
    { /* undefined input arrived */
      method= cl->method_for_undefined_input;
      
      if (cl->state_for_undefined_input != (struct RDTP_STATE *) 0)
      { /* next state is defined; use that */
        new_state= cl->state_for_undefined_input;
      }
      else
      { /* no method to deal with stuff */
#ifdef RDTP_DEBUG
        char *nm1;

        nm1= st->state_name;
        printf (
          "rdtp0001: state=%s char=0x%02X -> undef state; ignoring input\n",
          nm1, ch);
#endif /* RDTP_DEBUG */

      }
    }
    else
    {
      method= st->transitions [char_class];
    }

    if (method != (RDTP_state_transition *) 0)
      rc= (*method) ((void *) thread, ch);
    thread->current_state= new_state;
  }

  return rc;
}
