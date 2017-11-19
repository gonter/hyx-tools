/*
 *  FILE ~/usr/sgml/sgml0010.c
 *
 *  written:       1990 10 09: SGML processor configuration isolated
 *                             into this module
 *  latest update: 1999-04-25 16:40:51
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <gg/sgml.h>

/* ------------------------------------------------------------------------ */
static do_nothing () {}

/* ------------------------------------------------------------------------ */
int sgml_0010_config_processor (int processor_code)
{
  int sgml_filter_tag_beg (),  x_tag_beg ();
  int sgml_filter_tag_end (),  x_tag_end ();
  int sgml_filter_tag_chr (),  x_tag_chr ();
  int sgml_filter_com_beg ();
  int sgml_filter_com_end ();
  int sgml_filter_com_chr ();
  int sgml_filter_chr     (),  x_out_char ();
  int sgml_list_element   (),  sgml_transmit_segment ();
  int sgml_list_out       ();
#ifdef JUNK
  int sgml_transmit_2segment ();
#endif

  switch (processor_code)
  {
    case 1: /* SGML to LaTeX */
      /* we ignore comment completely here */
      patch (sgml_filter_com_beg, do_nothing);
      patch (sgml_filter_com_end, do_nothing);
      patch (sgml_filter_com_chr, do_nothing);

      /* tags will be processed */
      patch (sgml_filter_tag_beg, x_tag_beg);
      patch (sgml_filter_tag_end, x_tag_end);
      patch (sgml_filter_tag_chr, x_tag_chr);

      /* characters will be processed */
      patch (sgml_filter_chr,     x_out_char);

      sgml_filter_reset ();

      patch (sgml_list_element, sgml_transmit_segment);
      patch (sgml_list_out, sgml_transmit_2segment);
      break;

    default:
      return -1;
  }

  return 0;
}
