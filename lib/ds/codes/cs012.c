/*
 *  File %ds/codes/cs012.c
 *
 *  written:       1996-02-24: g.gonter@ieee.org
 *  latest update: 1996-02-24 11:04:52
 *
 */

#include <stdio.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/codes.h>

static long x_cnt= 1;
static char tmp1 [512];
static char tmp2 [512];

/* ------------------------------------------------------------------------ */
long cs_print_frame (FILE *fo, struct CS_field *fields)
{
  long c= 0L;
  struct CS_field *f2;
  long iso_code= -1L;
  char *name;
  char *tag_name;
  char *attr_name;
  char *attr_value;
  int num_size= 2;
  char *eset= (char *) 0;
  char *entity= (char *) 0;

  f2= fields;

  for (; fields != (struct CS_field *) 0; fields= fields->CSf_next)
  {
    if (strcmp (fields->CSf_name, "iso10646") == 0
        && fields->CSf_type == CSft_number
       )
      iso_code= fields->CSf_number;

    if (strcmp (fields->CSf_name, "def") == 0) return 0;
  }
  
  if (iso_code != -1L)
  {
    fprintf (fo, "<Frame 0x%08lX>\n", iso_code);
  }
  else
  {
    fprintf (fo, "<Frame XX 0x%08lX>\n", x_cnt++);
  }

  for (fields= f2; fields != (struct CS_field *) 0; fields= fields->CSf_next)
  {
    /****************************************
    fprintf (fo, "  field[%ld]:", ++c);
    fprintf (fo, "  name=\'%s\'  type=%ld",
       fields->CSf_name, fields->CSf_type);
    ****************************************/
    name= fields->CSf_name;
    num_size= 2;
    attr_name= attr_value= (char *) 0;

    if (strcmp (name, "ascii") == 0
        || strcmp (name, "ebcdic") == 0
        || strcmp (name, "ebcdic") == 0
        || strcmp (name, "mac") == 0
        || strcmp (name, "pc") == 0
       )
    {
      tag_name= "c";
      attr_name= "n";
      attr_value= name;
      num_size= 1;
    }
    else
    if (strcmp (name, "iso8859") == 0
        || strcmp (name, "iso8859_1") == 0
       )
    {
      tag_name= "c";
      attr_name= "n";
      attr_value= "iso8859-1";
      num_size= 1;
    }
    else
    if (strcmp (name, "iso10646") == 0)
    {
      tag_name= "c";
      attr_name= "n";
      attr_value= "iso10646";
      num_size= 4;
    }
    else
    if (strcmp (name, "name") == 0)
    {
      tag_name= "n";
    }
    else
    if (strcmp (name, "name_en") == 0)
    {
      tag_name= "n";
      attr_name= "l";
      attr_value= "en";
    }
    else
    if (strcmp (name, "name_gr") == 0)
    {
      tag_name= "n";
      attr_name= "l";
      attr_value= "gr";
    }
    else
    if (strcmp (name, "name_iso") == 0)
    {
      tag_name= "n";
      attr_name= "l";
      attr_value= "iso";
    }
    else
    if (strcmp (name, "tex") == 0)
    {
      tag_name= "r";
      attr_name= "n";
      attr_value= "tex";
    }
    else
    if (strcmp (name, "eset") == 0)
    {
      eset= fields->CSf_string;
      continue;
    }
    else
    if (strcmp (name, "entity") == 0)
    {
      tag_name= "e";
      if (eset != (char *) 0)
      {
        attr_name= "s";
        attr_value= eset;
      }
    }
    else
    {
      tag_name= name;
    }

    fprintf (fo, "<%s", tag_name);
    if (attr_name != (char *) 0 && attr_value != (char *) 0)
      fprintf (fo, " %s=%s", attr_name, attr_value);
    fputc ('>', fo);

    if (fields->CSf_type == CSft_number)
    {
      switch (num_size)
      {
        case 1:
          fprintf (fo, "0x%02lX", fields->CSf_number);
          break;
        default:
        case 2:
          fprintf (fo, "0x%04lX", fields->CSf_number);
          break;
        case 4:
          fprintf (fo, "0x%08lX", fields->CSf_number);
          break;
      }
    }

    if (fields->CSf_type == CSft_string)
    {
      strcpy (tmp1, fields->CSf_string);
      sgml_encode (tmp1, tmp2, 510);
      fputs (tmp1, fo);
    }

    fputc ('\n', fo);
  }

  fprintf (fo, "</Frame>\n");

  return c;
}
