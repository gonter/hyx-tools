/*
 *  FILE %lexicon/dictadd2.c
 *
 *  written:       1991 03 17
 *  latest update: 2001-02-18 18:24:54
 *  $Id: dictadd2.c,v 1.4 2002/01/22 03:07:27 gonter Exp $
 *
 */

#include <stdio.h>
#include <gg/parse.h>
#include <gg/ytree.h>
#include <gg/sgml.h>

/* ------------------------------------------------------------------------ */
long dict_restructure_new_entry (
struct HYX_PARSER_CLASS *hpc,
struct TEXT_ELEMENT **tx_list,
char *key_string,               /* key string found in <LE> markup          */
int key_string_length,          /* maximum length of the key_string         */
int do_strip,
struct TEXT_ELEMENT *insert_head,
struct TEXT_ELEMENT *insert_tail)
{
  struct TEXT_ELEMENT **tx, *t;
  struct TEXT_ELEMENT **last_tag= (struct TEXT_ELEMENT **) 0;
  struct TEXT_ELEMENT *t1, *t2, *t3, *t4, *t5;
  struct TAG_DEFINITION *td;
  long last_tag_id= -1L;
  int any_tag_seen= 0;
  int tags_counted= 0;
  int rc;
  int key_length;               /* tatsaechliche Laenge des key_strings     */

#ifdef PARSER_DEBUG_B
printf ("Restructuring entry\n");
diag_display_text_element (stdout, *tx_list, "");
#endif /* PARSER_DEBUG_B */

  if (tx_list == (struct TEXT_ELEMENT **) 0) return -1;
  if (key_string != (char *) 0) *key_string= 0;

  for (tx= tx_list;; tx= &(*tx)->TE_next)
  {
ONCE_MORE:
    if ((t= *tx) == (struct TEXT_ELEMENT *) 0)
    {
      if (insert_tail != (struct TEXT_ELEMENT *) 0)
         hyx_append_tx_elem_list (tx, insert_tail);
      break;
    }

#ifdef PARSER_DEBUG_B
printf ("dictadd2: level=%d last_tag_id=%d tag_name=%s\n",
  t->TE_level, last_tag_id, t->TE_tag_name);
print_text_segment_list (stdout, t->TE_text_segment);
fputc ('\n', stdout);
#endif /* PARSER_DEBUG_B */

    switch ((int) t->TE_level)
    {
      case 0: /* moeglicherweise getaggter Text */
        if (!any_tag_seen
            || (do_strip && hyx_strip_text_elem (t) == 1)
           ) goto DISCARD;

        switch ((int) last_tag_id)
        {
          case -1:
            break;
          /* hardcoded tags vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv */
          case LEX_sTAG_LE:
            key_length= hyx_copy_tx_segm_list (key_string,
                          key_string_length, t->TE_text_segment);

            /* key string untersuchen:                                      */
            /* Spezielle Codes: -> umwandeln, neues Tag erzeugen und        */
            /*   VOR das jeweilige Tag einhaengen. Altes Tag auf <Le>       */
            /*   und folgendes auf </Le> aendern.                           */
            /* Upper Case Chars: -> tolower, neues Tag erzeugen und         */
            /*   VOR das jeweilige Tag einhaengen. Altes Tag auf <le>       */
            /*   und folgendes auf </le> aendern.                           */

            rc= key_string_transform (key_string, key_length);
            switch (rc)
            {
              case  1: /* mixed case characters */
              case  2: /* special codes         */
                /* create new <LE>...</LE> structure and   */
                /* insert that before the acutal structure */
                t1= hyx_mktx_elem_and_segm (hpc, "LE", 2L, 1L, TEt_tag, 1, 1);
                t2= hyx_mktx_elem_and_segm (hpc, key_string, (long) key_length,
                                           0L, TEt_text, 0, 0);
                t3= hyx_mktx_elem_and_segm (hpc, "/LE", 3L, 1L, TEt_tag, 1, 1);

                if (t1 == (struct TEXT_ELEMENT *) 0
                    || t2 == (struct TEXT_ELEMENT *) 0
                    || t3 == (struct TEXT_ELEMENT *) 0
                   ) return -1;

                t1->TE_next= t2;
                t2->TE_next= t3;
                t3->TE_next= *last_tag;
                if (insert_head != (struct TEXT_ELEMENT *) 0)
                { /* insert information between newly created */
                  /* <LE> structure and the previous one.     */
                  t5= hyx_append_tx_elem_list (&t3->TE_next, insert_head);
                  if (t5 != (struct TEXT_ELEMENT *) 0) t5->TE_next= *last_tag;
                }
                t3= *last_tag; /* save pointer of previous structure */
                *last_tag= t1; /* make insertion complete */

                /* modify old <LE> structure to <LM> or <LX> respectively */
                t3->TE_text_segment->TSEG_text_array [0]= 'L';
                if (rc == 1)
                {
                  t3->TE_text_segment->TSEG_text_array [1] = 'M';
                  t3->TE_tag_definition= hyx_identify_tag (hpc, "LM", 1);
                } else
                {
                  t3->TE_text_segment->TSEG_text_array [1] = 'X';
                  t3->TE_tag_definition= hyx_identify_tag (hpc, "LX", 1);
                }

                t2= t->TE_next;
                if (t2 != (struct TEXT_ELEMENT *) 0
                    && t2->TE_level == 1L
                    && t2->TE_tag_definition->tag_id == (long) LEX_eTAG_LE)
                {
                  t2->TE_text_segment->TSEG_text_array [1] = 'L';
                  if (rc == 1)
                  {
                    t2->TE_text_segment->TSEG_text_array [2] = 'M';
                    t2->TE_tag_definition= hyx_identify_tag (hpc, "/LM", 1);
                  } else
                  {
                    t2->TE_text_segment->TSEG_text_array [2] = 'X';
                    t2->TE_tag_definition= hyx_identify_tag (hpc, "/LX", 1);
                  }
                }
                break;
              default: /* keine Aenderung */
                break;
            }
            break;
          /* hardcoded tags ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
          default:
            break;
        }
        last_tag= (struct TEXT_ELEMENT **) 0;
        last_tag_id= -1L;
        break;

      case 1: /* Tag */
        any_tag_seen= 1;
        td= t->TE_tag_definition;
        last_tag= tx;
        last_tag_id= (td == (struct TAG_DEFINITION *) 0) ? -1L : td->tag_id;

#ifdef PARSER_DEBUG_B
printf ("dictadd2: TAG: td=0x%08lX last_tag_id=%ld\n",
  td, last_tag_id);
#endif /* PARSER_DEBUG_B */

        if (last_tag_id == SGML_TAG_frame
            || last_tag_id == SGML_TAG_endframe
            || last_tag_id == SGML_TAG_ned_sgml
            || last_tag_id == SGML_TAG_hyx_stamp
           ) goto DISCARD;

        if (last_tag_id == LEX_eTAG_LE
            && insert_head != (struct TEXT_ELEMENT *) 0)
        { /* an dieser Stelle ev. Textliste einfuegen */
          t4= t->TE_next;
          t5= hyx_append_tx_elem_list (&t->TE_next, insert_head);
          if (t5 != (struct TEXT_ELEMENT *) 0)
          {
            if (t5->sig != SIG_TEXT_ELEMENT
                && t5->sig != SIG_MARKUP) return -1;
            tx= &t5->TE_next;
            t5->TE_next= t4;
            goto ONCE_MORE;
          }
        }

        if (last_tag_id >= LEX_sTAG_LE && last_tag_id <= LEX_eTAG_LX)
          break;

        tags_counted++; /* don't count discrded tags or LE tags */

        /* eventuell hier Tag umbauen */
        break;

      default:  /* anderer Tag-Level; z.B: <<xyz>>      */
                /* kommt in den Muell                   */
DISCARD:
        *tx= t->TE_next;
        t->TE_next= (struct TEXT_ELEMENT *) 0;
        hyx_frtx_elem_list (t);
        goto ONCE_MORE;
    }
  }

#ifdef PARSER_DEBUG_B
printf ("Restructuring entry; ... done\n");
#endif /* PARSER_DEBUG_B */
  return tags_counted;
}
