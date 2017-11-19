/*
 *  FILE %lexicon/bbc07.c
 *
 *  written:       1995-08-03
 *  latest update: 1996-10-10  0:13:35
 *  $Id: bbc07.c,v 1.5 2003/10/01 21:52:01 gonter Exp $
 *
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <gg/dirty.h>
#include <gg/sbr.h>
#include <gg/hytxt.h>
#include <gg/parse.h>
#include <gg/bbch.h>

/* ------------------------------------------------------------------------ */
int bbc_lexicon_processor (
void *client_data,
char *buffer,
int buffer_size) /* @@@ T2D ### buffer_size should be defined as long or so */
{
  struct BBC_CONNECTION *bbcc;
  struct LEX_SESSION *lexs;
  struct HYX_CLUSTER_CONTROL *hcc;
  struct HYX_PARSER_STATUS *hps;
  struct HYX_PARSER_CLASS *hpc;
  struct LEXICON_CONTROL *lcc;
  long chars_read;
  int rv= 0;
  int rc;

  if ((bbcc= (struct BBC_CONNECTION *) client_data)
        == (struct BBC_CONNECTION *) 0
      ||(lexs= (struct LEX_SESSION *) bbcc->BBCC_client_data1)
        == (struct LEX_SESSION *) 0
      ||(hcc= lexs->LEXS_hcc) == (struct HYX_CLUSTER_CONTROL *) 0
      || !hcc->HCC_dictadd1_inited
      ||(lcc= lexs->LEXS_lcc) == (struct LEXICON_CONTROL *) 0
      /** ||(hpc= hyx_init_parser_class ()) == (struct HYX_PARSER_CLASS *) 0 **/
      ||(hpc= lexs->LEXS_hpc) == (struct HYX_PARSER_CLASS *) 0
     )
  {
    fprintf (stdout, "lexicon system not initialized!!!\n");
    return -1;
  }

  /* T2D: debugging only? */
  hpc->HPC_meta_flags |= HPC_META_show_new_tags;

  while (buffer_size > 0 && rv == 0)
  {
/** fprintf (stderr, "bbc07: buffer_size=%d\n", buffer_size); **/
    if ((hps= lexs->LEXS_hps) == (struct HYX_PARSER_STATUS *) 0)
    {
      if ((hps= hyx_parser_reset (hpc)) == (struct HYX_PARSER_STATUS *) 0)
      {
        fprintf (stdout, "hps_parser_reset failed!\n");
        return -1;
      }
      lexs->LEXS_hps= hps;
    }

    /* parse incoming block */
    lexs->LEXS_tx_new_entry= (struct TEXT_ELEMENT *) 0;
    rc= hyx_parse2_block (hps, buffer, &lexs->LEXS_tx_new_entry,
                          lcc->LC_end_tags, lcc->LC_end_tag_count,
                          (long) buffer_size, &chars_read);
/** fprintf (stderr, "bbc07: hyx_parse2_block rc=%d chars_read=%ld\n", rc, chars_read); **/

    if (rc < 0 || chars_read == 0L)
    {
      fprintf (stdout,
        "note: bbc_lexicon_processor: rc=%d chars_read=%ld srv=%s/%s\n",
        rc, chars_read, bbcc->BBCC_peer_host, bbcc->BBCC_from);
      rv= -1;
      goto END;
    }

    if (rc == 0) break;         /* incomplete block, wait for rest */
    buffer_size -= (int) chars_read;
    buffer += (int) chars_read;

    /* if (strcmp (bbcc->BBCC_resource, "lookup") == 0) */
    hcc->HCC_dict_mode= DAMODE_LOOKUP; /* default*/
    if (strcmp (bbcc->BBCC_resource, "dictadd") == 0)
      hcc->HCC_dict_mode= DAMODE_MERGE;

    rc= dict_process_entry (hpc, hcc, lcc, lexs->LEXS_tx_new_entry,
                            bbcc->BBCC_op, (void *) bbcc, 0);
/** fprintf (stderr, "bbc07: dict_process_entry rc=%d\n", rc); **/

    if (rc == -1) rv= -1;
    if (rc == 0)
    {
      lexs->LEXS_record_counter++;
      if ((lexs->LEXS_record_counter % 0x00010000L) == 0)
        memory_statistics (stdout, lexs->LEXS_record_counter);
    }

END:
    free (hps);
    lexs->LEXS_hps= (struct HYX_PARSER_STATUS *) 0;
    lexs->LEXS_tx_new_entry= (struct TEXT_ELEMENT *) 0;
  }

  return 0;
}
