/*
 *  FILE %ds/hyxta/hyxtax01.c
 *
 *  written:       1990 11 11
 *                 1992 11 15: revision
 *  latest update: 1996-12-22 21:24:39
 *
 */

#include <stdio.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/parse.h>
#include <gg/ta.h>
#include <gg/hytxt.h>
#include <gg/dirty.h>

static int tm= 0;

/* ------------------------------------------------------------------------ */
void ta_transmit_mode (int mode)
{
  tm= mode;
}

/* ------------------------------------------------------------------------ */
int ta_transmit_node (
struct HYX_PARSER_STATUS *hps,
struct TEXT_ELEMENT *node)
{
  switch (tm)
  {
#ifdef __JUNK__
    case 1:
      printf ("--------------------------------------\n");
      printf ("Node; lng=%ld size=%ld cat_flags=0x%08lX\n",
             node->ta_data_lng,
             node->ta_data_size,
             node->ta_cat_flags);
      dump (stdout, node->ta_data, (int) node->ta_data_size);
      break;

    case 2:
/***************
      if (node->ta_cat_flags & 0x0300000)
      {
        fwrite (node->ta_data, (int) node->ta_data_size, 1, stdout);
        break;
      }
****************/
      fprintf (stdout, "<ta.n l=%ld c=0x%lx>",
               node->ta_data_lng, node->ta_cat_flags);
      sgml_write_data (stdout, "", "", node->ta_data, (int) node->ta_data_size);
      fprintf (stdout, "</ta.n>");
      break;

    case 3:
      fwrite (node->ta_data, (int) node->ta_data_size, 1, stdout);
      break;

    case 4711:
      fputc ('´', stdout);
      fwrite (node->ta_data, (int) node->ta_data_size, 1, stdout);
      fputc ('Ã', stdout);
      break;
#endif

    case 4:
      ta_collect_node (hps, node);
      break;

    case 5:
      display_markup (stdout, hps->HPS_hpc, node, 2, 0, 0, 1);
      hyx_frtx_elem_list (node);
      break;

    default:
      dump_text_element_list (stdout, node);
      hyx_frtx_elem_list (node);
      break;
  }


  return 0;
}
