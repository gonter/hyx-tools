/*
 *  FILE %ds/lmd/nl_00603.c
 *
 *  read a list of documents for indexing
 *
 *  written:       1995-03-08: extracted from lutmake.c
 *  latest update: 1995-07-31
 *  $Id: nl_00603.c,v 1.2 2001/08/26 23:26:04 gonter Exp $
 *
 */

#include <stdio.h>
#include <string.h>
#include <gg/lookup.h>
#include <gg/strings.h>
#include <gg/dpp.h>
#include <gg/sbr.h>

/* ------------------------------------------------------------------------ */
static char *batch_commands[] =
{
  "add",                /* add <docid> <filename>       */
  "del",                /* del <docid>                  */
  "upd"                 /* upd <docid> <filename>       */
#define BATCH_add 0
#define BATCH_del 1
#define BATCH_upd 2
} ;

/* ------------------------------------------------------------------------ */
long lmd_batch_process (struct LMDC_CONTROL *lmdc, char *fn, int verbosity)
{
  long docid;
  FILE *fb;
  int cmd_code;
  int rc;
  long rv;
  char *cmd_str;
  long word_count= 0L;
  int MAX_STR;
  char docid_str [10];

  if (lmdc == (struct LMDC_CONTROL *) 0
      || (cmd_str= lmdc->LMDC_buffer2) == (char *) 0) return -1L;

  if ((fb= fopen (fn, "r")) == (FILE *) 0) return -1L;
  printf ("reading batch from %s\n", fn);
  MAX_STR= lmdc->LMDC_buffer_size;

  for (;;)
  {
    rc= fread_line (fb, cmd_str, MAX_STR);
    if (rc <= 0 && feof (fb)) break;
    if (cmd_str [0] == '#'
        || (cmd_code= find_command (cmd_str, batch_commands, 0, BATCH_upd)) == -1
       )
      continue;

    docid= get_parameter_value (locate_word (cmd_str, 1));

    long_to_hex (docid, docid_str); /* T2D, Bug: see nl_00601.c */

    switch (cmd_code)
    {
      case BATCH_del:
      case BATCH_upd:
        lmd_discard_document_id (lmdc, docid);
        if (cmd_code == BATCH_del) break;
      case BATCH_add:
        if ((rv= lmd_read_tokens (lmdc, locate_word (cmd_str, 2),
                                  docid, docid_str, 0L,
                                  0L, 0x7FFFFFFFL, verbosity))
            > 0L) word_count += rv;
        break;
    }
  }
  fclose (fb);

  return word_count;
}
