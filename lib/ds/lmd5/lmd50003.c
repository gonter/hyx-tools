/*
 *  FILE %ds/lmd5/lmd50003.c
 *
 *  LM/D Engine Version 5
 *
 *  written:       1996-04-14
 *  latest update: 1996-05-19 10:34:44
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/sbr.h>
#include <gg/dpp.h>
#include <gg/dates.h>
#include <gg/lmd5.h>

#define MAX_BUFFER 1024
#define PV(x) get_parameter_value(x)

/* ------------------------------------------------------------------------ */
int lmd5_process_stream (
struct LMD5_CONTROL *l5,
FILE *fi)
{
  char *buffer;
#define SECTION_commands        0
#define SECTION_data            1
#define SECTION_DATA            2
#define SECTION_datapoints      3
#define SECTION_DATAPOINTS      4
#define SECTION_INFO            5
  int section= SECTION_commands;
  int rc;
  int fc;
#define MAX_FIELDS 10
  char *fields [MAX_FIELDS];
  char *cmd;
  char *docid= (char *) 0;
  char date_string [40];
  long cnt;

  if (l5 == (struct LMD5_CONTROL *) 0
      || (buffer= malloc (MAX_BUFFER)) == (char *) 0
     )
    return -1;

  actual_datim (date_string, DATIMfmt_date_time);
  lmd5_set_info_attribute_value (l5, "latest_indexing", date_string);

  while (1)
  {
    rc= fread_line (fi, buffer, MAX_BUFFER);
    if (rc <= 0 && feof (fi)) break;
    if (*buffer == '#' || *buffer == 0) continue;

    switch (section)
    {
      case SECTION_commands:
        fc= isolate_tokens (buffer, fields, MAX_FIELDS);
        if (fc <= 0) continue;
        cmd= fields [0];

        if (strcmp (cmd, "DOCID") == 0)
        {
          if (fc >= 1)
          {
            char *fref_nam;
            long fref_beg;
            long fref_end;

            free_or_what (docid);
            docid= strdup (fields [1]);
            fref_nam= (fc < 2) ? (char *) 0  : fields [2];
            fref_beg= (fc < 3) ? 0L          : PV (fields [3]);
            fref_end= (fc < 4) ? 0x7FFFFFFFL : PV (fields [4]);

            lmd5_increment_document_count (l5, docid,
                                           fref_nam, fref_beg, fref_end,
                                           (char *) 0);
          }
        }
        else
        if (strcmp (cmd, "INFO") == 0) section= SECTION_INFO; else
        if (strcmp (cmd, "DATA") == 0) section= SECTION_DATA; else
        if (strcmp (cmd, "data") == 0) section= SECTION_data; else
        if (strcmp (cmd, "DATAPOINTS") == 0) section= SECTION_DATAPOINTS; else
        if (strcmp (cmd, "datapoints") == 0) section= SECTION_datapoints;
        break;

      case SECTION_data:
        to_lower (buffer);
      case SECTION_DATA:
        if (strcmp (buffer, ".") == 0)
        {
          section= SECTION_commands;
          break;
        }
        lmd5_increment_word_count (l5, buffer, docid, 1L);
        break;

      case SECTION_datapoints:
      case SECTION_DATAPOINTS:
        if (strcmp (buffer, ".") == 0)
        {
          section= SECTION_commands;
          break;
        }

        fc= isolate_tokens (buffer, fields, 2);
        if (fc < 2) continue;

        cnt= PV (fields [0]);
        cmd= fields [1];
        if (section == SECTION_datapoints) to_lower (cmd);
        lmd5_increment_word_count (l5, cmd, docid, cnt);
        break;

      case SECTION_INFO:
        if (strcmp (buffer, ".") == 0)
        {
          section= SECTION_commands;
          break;
        }

        fc= isolate_tokens (buffer, fields, 2);
        if (fc < 2) continue;

        lmd5_set_info_attribute_value (l5, fields [0], fields [1]);
        break;
    }

  }

  free (buffer);
  return 0;
}
