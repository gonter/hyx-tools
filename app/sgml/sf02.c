/*
 *  FILE ~/usr/sgml/sf02.c
 *
 *  transform HYX tags into HTML tags
 *  processed are:
 *    HLINK and hyx.l into a (anchors)
 *    w3.*  strip w3. prefix off (also closing tags)
 *    Frame etc are removed
 *
 *  written:       1994-04-12
 *  latest update: 1995-06-23
 *
 */

#include <stdio.h>
#include <string.h>
#include <gg/dpp.h>
#include <gg/hyx.h>
#include <gg/hytxt.h>

#define AV_SIZ 256
static char av1 [AV_SIZ];
static char av2 [AV_SIZ];
static char url [AV_SIZ];
static char av3 [AV_SIZ];
static char av4 [AV_SIZ];

#define NUM_RELATIONAL_LINKS 10
static char *relational_link_dest [NUM_RELATIONAL_LINKS];
static char *relational_link_rel  [NUM_RELATIONAL_LINKS];
static char *relational_link_name [NUM_RELATIONAL_LINKS];
static int relational_link_count= 0;

/* ------------------------------------------------------------------------ */
long hytxt_hyx2html (FILE *fo, char *tag_buffer)
{
  int rc1;
  int rc2;
  int rc3;
  int rc4;

  if (strncmp (tag_buffer, "Frame ", 6) == 0
    ||strcmp (tag_buffer, "/Frame") == 0
    ||strncmp (tag_buffer, ":", 1) == 0
    ||strncmp (tag_buffer, ";", 1) == 0) return 0L;

  if (strncmp (tag_buffer, "HLINK ", 6) == 0
    ||strncmp (tag_buffer, "hyx.l ", 6) == 0)
  {
    rc1= find_attr_value (tag_buffer, av1, AV_SIZ, "dir");
    rc4= find_attr_value (tag_buffer, av4, AV_SIZ, "tdp");
    rc2= find_attr_value (tag_buffer, av2, AV_SIZ, "file");
    if (rc2 == 0)
    {
      fprintf (fo, "<a href=\"%s\">", av2);
    }
    else
    {
      rc2= find_attr_value (tag_buffer, av2, AV_SIZ, "fr");
      rc3= find_attr_value (tag_buffer, av3, AV_SIZ, "cl");
      if (rc2 == 0)
      {
        frame_name2url (av2, url, AV_SIZ);
      }
      else strcpy (url, "$$root");

      fprintf (fo, "<a href=\"");
      if (rc3 == 0) fprintf (fo, "/%s/", av3);
      fprintf (fo, "%s", url);
      fprintf (fo, "\">");
    }

    if (rc1 == 0        /* relational link found */
       && relational_link_count < NUM_RELATIONAL_LINKS)
    {
      relational_link_rel  [relational_link_count]= strdup (av1);
      relational_link_dest [relational_link_count]= strdup (url);
      relational_link_name [relational_link_count]= strdup (av2);
      relational_link_count++;
    }

    if (rc4 == 0) return get_parameter_value (av4);
    return 2L;
  }

  if (strncmp (tag_buffer, "db.", 3) == 0)
  {
    fprintf (fo, "%s: ", tag_buffer+3);
    return 0L;
  }

  if (strncmp (tag_buffer, "w3.", 3) == 0)
  {
    fputc ('<', fo);
    fputs (tag_buffer+3, fo);
    fputc ('>', fo);
    return 0L;
  }

  if (strncmp (tag_buffer, "/w3.", 4) == 0)
  {
    fputc ('<', fo);
    fputc ('/', fo);
    fputs (tag_buffer+4, fo);
    fputc ('>', fo);
    return 0L;
  }

  /* default: */
  fputc ('<', fo);
  fputs (tag_buffer, fo);
  fputc ('>', fo);

  return 0L;
}

/* ------------------------------------------------------------------------ */
int hyx_print_relational_links (FILE *fo)
{
  int i;

  if (relational_link_count <= 0) return 0;
  fprintf (fo, "<HR>\n");

  for (i= 0; i < relational_link_count; i++)
    fprintf (fo,
             "<a href=%s>[%s:%s]</a>\n",
             relational_link_dest [i],
             relational_link_rel  [i],
             relational_link_name [i]);

  fprintf (fo, "<HR>\n");

  return 0;
}
