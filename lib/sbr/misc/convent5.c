/*
 *  FILE %sbr/convent5.c
 *
 *  Convert Characters to SGML Entities
 *
 *  written:       1991-07-03: <Gerhard.Gonter@wu-wien.ac.at>
 *                 1995-01-29: extracted from convent1.c
 *  latest update: 1996-06-09 11:14:18
 *
 */

#include <stdio.h>

#define USE_CODE_TABLE
#ifdef  USE_CODE_TABLE
#include <gg/codes.h>
#endif

#include <gg/convent.h>

/* ------------------------------------------------------------------------ */
int fputc_entity (int ch, FILE *fo, int level)
{
  char *entity_name;

  switch (ch)
  {
    case '&':
      if (level & CONVENT_amp) fputs ("&amp;", fo);
      else fputc ('&', fo);
      break;

    case '<':
      if (level & CONVENT_lt_gt) fputs ("&lt;", fo);
      else fputc ('<', fo);
      break;

    case '>':
      if (level & CONVENT_lt_gt) fputs ("&gt;", fo);
      else fputc ('>', fo);
      break;

    case 0x0A:
    case 0x0D:
      goto NORMAL;

    default:
      if ((ch >= 0x80 && ch <= 0xFF)
        ||(ch >= 0x00 && ch <= 0x1F))
      {
#ifdef USE_CODE_TABLE
/* fprintf (stderr, "convert 0x%02X %c\n", ch, ch); **********/
        if (level & CONVENT_pc_8bit)
        {
/* fprintf (stderr, "convert 0x%02X %c (2)\n", ch, ch); */
          entity_name= get_sgml_entity (ch);
          if (entity_name == (char *) 0) goto NORMAL;
          fprintf (fo, "&%s;", entity_name);
        }
#else
        if (level & CONVENT_pc_8bit)
        {
          entity_name= get_pc_sgml_entity (ch);
          if (entity_name == (char *) 0) goto NORMAL;
          fprintf (fo, "&%s;", entity_name);
        }
#ifdef NOT_YET
        else
        if (level & CONVENT_mac_8bit)
        {
          entity_name= get_mac_sgml_entity (ch);
          if (entity_name == (char *) 0) goto NORMAL;
          fprintf (fo, "&%s;", entity_name);
        }
#endif
#endif
        else goto NORMAL;
      }
      else
      {
NORMAL:
        fputc (ch, fo);
      }
      break;
  }

  return 0;
}
