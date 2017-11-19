/*
 *  FILE .../app/sgml/hyxeng02.c
 *
 *  HyperText Engine
 *
 *  written:       1990 04 13
 *  latest update: 1999-04-24 12:00:17
 *  $Id: hyxeng02.c,v 1.3 2002/05/02 06:48:29 gonter Exp $
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/hytxt.h>
#include "hyxeng.h"
#include "hyxeng01.h"          /* automatisch erzeugt aus HYXENG01.CMD */

#ifdef NIL
#undef NIL
#endif
#define NIL (char *) 0

#pragma check_stack(off)

/* Prototypes von externen Funktionen: ------------------------------------ */
void cdecl flip_int (int *);
void cdecl dump (FILE *fo, char *str, int lng);
void cdecl sgml_filter (int);
int  cdecl sgml_0010_config_processor (int code);

/* Prototypes von lokalen Funktionen: ------------------------------------- */
void cdecl assign_string (char **dest, char *source, int lng);
void cdecl get_list_parameters (char *s, int *par3);

/* ------------------------------------------------------------------------ */
static char *cluster=     NIL;
static char *frame=       NIL;
static char *new_frame=   NIL;
static char *new_cluster= NIL;
static char *out_file=    NIL;

static int agenda= 0;
static struct HYTXT_FRAME *hytxt_frame;
static int hytxt_frame_scanned= 0;

static int out_file_open= 0;
static FILE *out_file_ptr;

static int processor_code= -1;

/* ------------------------------------------------------------------------ */
static void out2_stdout  (int ch) { fputc (ch, stdout); }
static void out2_outfile (int ch) { fputc (ch, out_file_ptr); }

static void (*out_function)    (int ch) = out2_stdout;
static void (*export_function) (int ch) = out2_stdout;

void sgml_fputc (int ch) { (*out_function) (ch); }
void sgml_fputs (char *s) { for (; *s; s++) (*out_function) (*s); }

/* ------------------------------------------------------------------------ */
void hyx_engine_opcode (int *command)
{
  int rv;
  int cp= 1;
  int opcode;
  int lng;
  int par2;
  int par3;

  lng= command [0];
  flip_int (&lng);

/******************
  dump (stdout, (char *) command, lng);
******************/

  opcode = command [cp++];
  flip_int (&opcode);

  switch (opcode)
  {
    case HYXENG_cluster:
      assign_string (&cluster, (char *) &command [cp], lng-cp);
      hytxt_frame_scanned = 0;
      break;
    case HYXENG_frame:
      assign_string (&frame, (char *) &command [cp], lng-cp);
      break;
    case HYXENG_delete:
      agenda |= 0x01;
      break;
    case HYXENG_undelete:
      agenda |= 0x02;
      break;
    case HYXENG_rename:
      assign_string (&new_frame, (char *) &command [cp], lng-cp);
      break;
    case HYXENG_move:
      assign_string (&new_cluster, (char *) &command [cp], lng-cp);
      break;
    case HYXENG_output: /* output */
      assign_string (&out_file, (char *) &command [cp], lng-cp);
      if (out_file_open)
      {
        fclose (out_file_ptr);
        out_file_open=0;
        if (*out_function == *export_function)
           export_function = out2_stdout;
        out_function = out2_stdout;
      }
      if (out_file [0])
      {
        out_file_ptr = fopen (out_file, "ab");
        if (out_file_ptr != (FILE *) 0) out_file_open = 1;
        if (*out_function == *export_function)
           export_function = out2_outfile;
        out_function = out2_outfile;
      }
      break;

    case HYXENG_touch:
      agenda |= 0x04;
      break;
    case HYXENG_purge:
      agenda |= 0x08;
      break;
    case HYXENG_export: /* export */
/* printf (">> export\n"); */
      rv = hyx_engine_export (stdout, cluster, &hytxt_frame,
                              hytxt_frame_scanned, frame,
                              export_function);
      if (rv >= 0) hytxt_frame_scanned=1;
      break;

    case HYXENG_string:
      {
        char *_cp;
        int   _lng;
        int   _ch;

        _cp=(char *) &command [cp];
        _lng=lng-4;
        cp++;
        while (_lng > 0)
        {
          _lng--;
          switch (_ch = *_cp++)
          {
            case '\\':
              if (_lng <= 0) break;
              _lng--;
              switch (_ch = *_cp++)
              {
                case 'n':
                  sgml_fputc ('\n');
                  break;
                default:
                  sgml_fputc (_ch);
                  break;
              }
              break;
            default:
              sgml_fputc (_ch);
              break;
          }
        }
      }
      break;

    case HYXENG_processor:
      {
        char *_cp;
        int   _lng;

        _cp=(char *) &command [cp];
        _lng=lng-4;
        if (strncmp (_cp, "raw", _lng) == 0) processor_code = 0; else
        if (strncmp (_cp, "LaTeX", _lng) == 0) processor_code = 1; else break;
        switch (processor_code)
        {
          case 0:
            export_function = out_function;
            break;
          case 1:
            sgml_0010_config_processor (1);
            export_function = sgml_filter;
            break;
          default:
            break;
        }
      }
      break;

    case HYXENG_list: /* list */
      /* Parameter auswerten */
printf (">> list\n");
      par2= 2;
      par3= 0x0001;
      get_list_parameters ((char *) &command [cp], &par3);
      rv = hyx_engine_list ((out_file_open) ? out_file_ptr : (FILE *) stdout,
                            cluster, &hytxt_frame,
                            hytxt_frame_scanned,
                            0, par2, par3);
      if (rv >= 0) hytxt_frame_scanned=1;
      break;

    case HYXENG_new: /* new */
      hytxt_frame_scanned=0;
      if (cluster     != NIL) free (cluster);     cluster     = NIL;
      if (frame       != NIL) free (frame);       frame       = NIL;
      if (new_cluster != NIL) free (new_cluster); new_cluster = NIL;
      if (new_frame   != NIL) free (new_frame);   new_frame   = NIL;
      break;
  }

/******************
  printf ("<<< cluster=%s frame=%s agenda=%04X\n", cluster, frame, agenda);
******************/
}

/* ------------------------------------------------------------------------ */
void assign_string (
char **dest,
char *source,
int lng)
{
  char *cp;
  if (*dest != NIL) free (*dest);
  *dest = cp = malloc (lng+1);
  while (lng-- > 0) *cp++ = *source++;
  *cp = 0;
}

/* ------------------------------------------------------------------------ */
void get_list_parameters (
char *s,
int *par3)
{
  for (; *s; s++)
    switch (*s)
    {
      case 'a': /* print attributes */
        *par3 |= 0x0002;
        break;
      case '*': /* Print All Version */
        *par3 |= 0x4000;
        break;
      case 'p': /* Print Position of Frame */
        *par3 |= 0x8000;
        break;
    }
}
