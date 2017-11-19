/*
 *  FILE ~/usr/sgml/sgml0006.c
 *
 *  written:       1990 09 27
 *  latest update: 1999-04-25 16:40:12
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <gg/sgml.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
sgml_list_out () { int i; }     /* Hook fr Weiterleitung */
                                /* eines SGML Elementes   */

/* ------------------------------------------------------------------------ */
# define MAX_TRANS_STACK 100
static int trans_mode= 0;
static int trans_stack [MAX_TRANS_STACK];
static int trans_case  [MAX_TRANS_STACK];       /* switch: case match */
static int trans_sp=0;

/* ------------------------------------------------------------------------ */
sgml_transmit_segment (void *segment)
{
  struct SGML_TAG  *st;
  struct SGML_LIST *sl, *sl2;
  void *p1, *p2;
  int rc;

  sl = segment;

  switch (trans_mode)
  {
    case 0: /* no control structure              )                     */
    case 1: /* if-section when condition true    ) process information */
    case 4: /* else-section when condition false )                     */
      if (sl->sig == SIG_INFO_BYTE)
        sgml_list_out (segment);
      if (sl->sig==SIG_LIST)
      {
        st=sl->car;
        if (st->sig==SIG_TAG)
        {
          switch (st->sgml_tag_id)
          {
            case SGML_TAG_case:         /* SYNTAX ERROR !!! */
            case SGML_TAG_default:      /* SYNTAX ERROR !!! */
            case SGML_TAG_break:        /* SYNTAX ERROR !!! */
            case SGML_TAG_endswitch:    /* SYNTAX ERROR !!! */
              free_tag_list (sl);
              break;
            case SGML_TAG_else:
              if (trans_mode==1) trans_mode=3;
              free_tag_list (sl);
              break;
            case SGML_TAG_endif:
              if (trans_mode==1) trans_mode = trans_stack[--trans_sp];
              free_tag_list (sl);
              break;
            case SGML_TAG_set:          /* evaluate what to set         */
              sgml_set_variable (sl->cdr, 1);
              sl->cdr= (void *) 0;
              free_tag_list (sl);
              break;
            case SGML_TAG_if:           /* evaluate the condition       */
              trans_stack [trans_sp++]=trans_mode;
              rc= sgml_test_variable (sl->cdr);
              trans_mode= (rc) ? 1 : 2;
              free_tag_list (sl);
              break;
            case SGML_TAG_switch:       /* evaluate the selector        */
              free_tag_list (sl);
              break;
            case SGML_TAG_frame:        /* frame tags are deleted here */
            case SGML_TAG_endframe:
            case SGML_TAG_Sframe:
            case SGML_TAG_Sendframe:
              /* break; transmit tag segments to next processor !!! */
              /*        he will be happy about that :-)) */
            default:
              sgml_list_out (segment);
              break;
          }
        }
      }
      break;

    case 2: /* if-section when condition false  ) ignore information */
    case 3: /* else-section when condition true )                    */
    case 5: /* if construct, when already ignoring information */
      if (sl->sig==SIG_LIST)
      {
        st=sl->car;
        if (st->sig==SIG_TAG)
        {
          switch (st->sgml_tag_id)
          {
            case SGML_TAG_else:
              if (trans_mode==2) trans_mode=4;
              break;
            case SGML_TAG_endif:
              trans_mode = trans_stack[--trans_sp];
              break;
            case SGML_TAG_if:
              trans_stack [trans_sp++]=trans_mode;
              trans_mode=5;
              break;
          }
        }
      }
      free_tag_list ();
      break;
  }
}

/* ------------------------------------------------------------------------ */
free_tag_list (void *segment)
{
  struct SGML_LIST *sl, *sl2;

  if (segment == (void *) 0) return;
  sl = segment;
AGAIN:

  switch (sl->sig)
  {
    case SIG_LIST: /* follow the list */
      free_tag_list (sl->car);
      sl2=sl;
      sl = sl->cdr;
      free (sl2);
      if (sl != (struct SGML_LIST *) 0) goto AGAIN;
      break;
    case SIG_TAG: /* don't delete TAG records */
      break;
    default: /* other records can be deleted */
      free (sl);
      break;
  }
}
