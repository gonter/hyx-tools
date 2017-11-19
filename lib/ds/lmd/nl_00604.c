/*
 *  FILE ~/usr/nl_kr/lib/nl_00604.c
 *
 *  read and process a text file
 *
 *  written:       1995-03-08: extracted from lutmake.c
 *  latest update: 1995-07-31
 *
 */

#include <stdio.h>
#include <string.h>
#include <gg/lookup.h>
#include <gg/strings.h>
#include <gg/dpp.h>
#include <gg/sbr.h>
#include <gg/hyx.h>

/* ------------------------------------------------------------------------ */
static char *LEVEL [] = { "note", "warning", "error" };

/* ------------------------------------------------------------------------ */
long lmd_docdir_process (
struct LMDC_CONTROL *lmdc,
char *fn,
int match_c,
char *match_v [],
int verbosity)
{
  FILE *fb;
  long docid;
  long f_from;
  long f_to;
  long f_size;
  char *reason;
  int reason_level;
  long rv;
  char *str1, *str2;
  int MAX_STR;
  long word_count= 0L;
  char docid_str [10];

  if (lmdc == (struct LMDC_CONTROL *) 0
      || (str1= lmdc->LMDC_buffer1) == (char *) 0
      || (str2= lmdc->LMDC_buffer2) == (char *) 0) return -1L;

  MAX_STR= lmdc->LMDC_buffer_size;
  if ((fb= fopen (fn, "r")) == (FILE *) 0) return -1L;
  printf ("reading document directory from %s\n", fn);

  for (;;)
  {
    fread_line (fb, str1, MAX_STR);
    if (feof (fb)) break;

    if (str1 [0] == '#') continue;
    reason= "no hyx.dd tag";
    reason_level= 1;
    if (strncmp (str1, "<hyx.dd ", 8) != 0)
    {
REPORT:
      fprintf (stderr,
               "%s: didn\'t process %s, reason: %s\n",
               LEVEL [reason_level],
               str1, reason);
      continue;
    }

    reason= "no docid attribute";
    if (find_attr_value (str1, str2, MAX_STR, "docid") != 0) goto REPORT;
    docid= get_parameter_value (str2);
    long_to_hex (docid, docid_str);

    f_from= f_size= f_to= 0L;
    if (find_attr_value (str1, str2, MAX_STR, "from") == 0)
      f_from= get_parameter_value (str2);

    if (find_attr_value (str1, str2, MAX_STR, "size") == 0)
      f_size= get_parameter_value (str2);

    if (find_attr_value (str1, str2, MAX_STR, "to") == 0)
      f_to= get_parameter_value (str2);

    if (match_c > 0)
    {
      reason= "no set attribute, but sets are checked";
      if (find_attr_value (str1, str2, MAX_STR, "set") != 0) goto REPORT;
      reason_level= 0;
      reason= "not included in set";
      if (match_array (match_v, match_c, str2) < 0) goto REPORT;
    }

    reason= "no file attribute";
    if (find_attr_value (str1, str2, MAX_STR, "file") != 0) goto REPORT;

    if ((rv= lmd_read_tokens (lmdc, str2, docid, docid_str,
                              f_from, f_size, f_to, verbosity)) > 0L)
      word_count += rv;
  }
  fclose (fb);

  return word_count;
}
