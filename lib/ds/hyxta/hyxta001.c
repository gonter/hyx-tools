/*
 *  FILE %ds/hyxta/hyxta001.c
 *
 *  textual analysis:
 *  data stream segmentation
 *
 *  T2D:
 *  - if ch is '<', '>' or '&', something should be done with it...
 *    that should be taken care off now...
 *
 *  written:       1990 11 11
 *                 1994-12-24: isolated from ta003.c
 *                 1995-03-30: moved to %ds/hyxta
 *  latest udpate: 1997-11-02 23:43:20
 *
 */

#include <memory.h>
#include <stdlib.h>
#include <gg/strings.h>
#include <gg/parse.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif /* MSDOS */

/* ------------------------------------------------------------------------ */
int hyx_ta_parse_char (
struct HYX_PARSER_STATUS *hps,
int ch,
struct TEXT_ELEMENT **generated_node)
/* Return: -1 ... error                 */
/*          0 ... ok                    */
/*          1 ... node was generated    */
{
  int act_cat_code;
  long act_cat_flag;
  char *entity;
  int rv= 0;
  struct HYX_PARSER_CLASS *hpc;

  if (generated_node == (struct TEXT_ELEMENT **) 0) return -1;

  hpc= hps->HPS_hpc;

  act_cat_code= get_cat_code (ch);
  act_cat_flag= hyx_ta_get_cat_flags (act_cat_code);

  if (hps->HPS_segment_length == 0L)                 /* buffer is empty */
  {
XX:
    hps->HPS_segment_length= 0;
    hps->HPS_last_cat_code = act_cat_code;
    hps->HPS_cat_flags     = act_cat_flag;
    goto INSERT_CHARACTER;
  }

  switch (hyx_ta_get_break_code (hps->HPS_last_cat_code, act_cat_code))
  {
    case 0:     /* character can be combined with data in buffer            */
      hps->HPS_last_cat_code= act_cat_code;
      hps->HPS_cat_flags |= act_cat_flag;

INSERT_CHARACTER:
      switch (ch)
      {
        case 0:
          entity= "null";
          goto INSERT_ENTITY;
        case '<':
          entity= "lt";
          goto INSERT_ENTITY;
        case '>':
          entity= "gt";
          goto INSERT_ENTITY;
        case '&':
          entity= "amp";
INSERT_ENTITY:
          if (hps->HPS_segment_length+6 < MAX_SEGMENT_LENGTH)
          {
            hps->HPS_segment [hps->HPS_segment_length++]=
              (char) hpc->HPC_entity_open;
            while ((ch= *entity++ & 0x00FF) != 0)
              hps->HPS_segment [hps->HPS_segment_length++]= (char) ch;
            hps->HPS_segment [hps->HPS_segment_length++]=
              (char) hpc->HPC_entity_close;
          }
          break;
        default:
          hps->HPS_segment [hps->HPS_segment_length++]= (char) ch;
          break;
      }

      if (hps->HPS_segment_length+7 >= MAX_SEGMENT_LENGTH)
      { /* in reality, a new text segment should be created in this         */
        /* situation, not a whole text element!!! (1994-11-15)              */
        rv= hyx_ta_parse_flush (hps->HPS_hpc, hps, generated_node);
      }
      return rv;

    case 1:     /* character can't be combined with data in buffer          */
      rv= hyx_ta_parse_flush (hps->HPS_hpc, hps, generated_node);
      goto XX;

    default:
      return -1;
  }
}
