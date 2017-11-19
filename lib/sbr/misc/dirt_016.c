/*
 *  FILE %sbr/dirt_016.c
 *
 *  print an array of integers in various formats
 *
 *  BUG: some sections always print 256 byte tables!
 *
 *  written:       1997-08-15
 *  latest update: 1997-08-15 22:23:22
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/dirty.h>

#define NUM_ENTRIES 16

#ifdef DTYPE_int
#define DTYPE int
#define FMT1 "/*0x%02X*/ 0x%08X%s"
#define fnc print_int_table2
#endif

#ifdef DTYPE_long
#define DTYPE long
#define FMT1 "/*0x%02X*/ 0x%08lX%s"
#define fnc print_long_table2
#endif

/* ------------------------------------------------------------------------ */
int fnc (FILE *ft, int write_mode, DTYPE *converter_table, int num)
{
  int i, j, code;

  if (ft == (FILE *) 0) return -1;

  switch (write_mode)
  {
    case WRITE_MODE_C:
      fprintf (ft, "{  \n");
      for (i= 0; i < num; i++)
      {
        fprintf (ft, FMT1,
                 i,
                 converter_table [i],
                 ((code == num) ? "" : ","));
        if ((i % 4) == 3) fputs ("\n  ", ft);
      }
      fputs ("}\n", ft);
      break;

      case WRITE_MODE_rexx:
        for (i= 0; i < 16; i++)
        {
          fprintf (ft, "  \'");
          for (j= 0; j < 16; j++)
          {
            code= i*16+j;
            fprintf (ft, "%02X", ((int) converter_table[code]) & 0x00FF);
          }
          if (i == 15)
               fprintf (ft, "\'x");
          else fprintf (ft, "\'x||,\n");
        }
        if (write_mode == WRITE_MODE_REXX) fprintf (ft, ")");
        fprintf (ft, ";\n");
        break;

      case WRITE_MODE_PERL:
        {
          int last_code= -1;
          int current_code;
          int range= 0;

          fprintf (ft, "tr(\\x00-\\xff)\n(\n");
          for (i= 0; i < 16; i++)
          {
            fprintf (ft, "  ");
            for (j= 0; j < 16; j++)
            {
              code= i*16+j;
              current_code= ((int) converter_table[code]) & 0x00FF;
              fprintf (ft, "\\x%02X", current_code);
            }
            fprintf (ft, "\n");
          }
          fprintf (ft, ");");
        }
        break;

      case WRITE_MODE_ASSEMBLE:
        for (i= 0; i < 16; i++)
        {
          fprintf (ft, "         DC   X\'");
          for (j= 0; j < 16; j++)
          {
            code= i*16+j;
            fprintf (ft, "%02X", ((int) converter_table[code]) & 0x00FF);
          }
          fprintf (ft, "\'\n");
        }
        break;

      case WRITE_MODE_binary:
        /* not implemented yet!!! ####*/
        break;

      default:
        return -1;
  }

  return 0;
}
