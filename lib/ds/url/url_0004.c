/*
 *  FILE %ds/url/url_0004.c
 *
 *  URL handling
 *
 *  written:       1995-12-25
 *  latest update: 1996-03-18  8:05:42
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
#include <gg/url.h>

#define TMP_SIZE 1024
#define MAX_TOKENS 10

/* ------------------------------------------------------------------------ */
char *url_read_object_name (
char *url_interface,
char *tmp_space,
int tmp_size)
{
  FILE *fi;
  int tmp_allocated= 0;
  int rc;
  int num_tokens;
  char *tokens [MAX_TOKENS];
  char *url_file= (char *) 0;

  if ((fi= fopen (url_interface, "r")) == (FILE *) 0) return (char *) 0;

  if (tmp_space == (char *) 0 || tmp_size <= 0)
  {
    if ((tmp_space= malloc (TMP_SIZE)) == (char *) 0) return (char *) 0;
    tmp_size= TMP_SIZE;
    tmp_allocated= 1;
  }

  for (;;)
  {
    rc= fread_line (fi, tmp_space, tmp_size);
    if (rc <= 0 && feof (fi)) break;

    num_tokens= isolate_tokens (tmp_space, tokens, MAX_TOKENS);
    if (num_tokens > MAX_TOKENS) num_tokens= MAX_TOKENS;

    if (num_tokens == 2)
    {
      if (strcmp ("object", tokens [0]) == 0)
      {
        url_file= strdup (tokens [1]);
        break;
      }
    }
  }

  if (tmp_allocated == -1) free (tmp_space);

  return url_file;
}
