/*
 *  FILE %ned/04/ned0402.c
 *
 *  file I/O: load a file
 *
 *  written:       1987 04 08
 *                 1990 01 12: isolation
 *                 1991 02 03: revision
 *                 1991 09 18: use logic path names
 *  latest update: 2000-12-09 17:13:12
 *  $Id: ned0402.c,v 1.3 2000/12/09 17:33:09 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#endif

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <gg/strings.h>
#define STREAM_FILE
#include <gg/streams.h>
#include <gg/filename.h>
#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_f_read (
struct WINDOWCTRL *w,           /* betroffenes Window                       */
char *filenm_txt,               /* Text File Name                           */
char *filenm_ftr,               /* Feature File Name                        */
int   f_rd_ftr,                 /* 1 -> Feature File suchen und einlesen    */
struct LINE **laptr,            /* ^ erste eingelesene Zeile                */
struct LINE **lzptr,            /* ^ letzte eingelesene Zeile               */
long la_offset,                 /* Anfang im File                           */
long lz_offset)                 /* Ende im File                             */
{
  int flcnt;                    /* line number for next feature             */
  int fccnt;                    /* column number for next feature           */

  int format= FMT_ASCII;        /* Default: ASCII Files einlesen            */
  int ftr_read= 0;              /* 1 -> feature setup eingelesen            */
  FILE *ft;                     /* text file                                */
  FILE *ff= (FILE *) 0;         /* feature file                             */
  char *adjusted_filename;      /* physical filename after logic conversion */
  char *adjusted_ftrname= (char *) 0;
  char *used_ftr_name= (char *) 0;
  struct STREAM_OBJECT *so;     /* input stream                             */

#ifndef MSDOS
  struct stat st;
#endif

  if ((adjusted_filename= translate_logic_filename (filenm_txt))
      == (char *) 0) return -1;

  *laptr= *lzptr= (struct LINE *) 0;

  format= w->file_format;
  if (format == FMT_BINARY || format == FMT_SGML) f_rd_ftr= 0;

  if (f_rd_ftr)
  {
    if (filenm_ftr [0] == 0) f_rd_ftr= 0;
    else
    { 
      adjusted_ftrname= translate_logic_filename (filenm_ftr);
      used_ftr_name= generate_ned_name (adjusted_ftrname, ".ftr", 1);
      ned_message_4 ("Reading File ", adjusted_filename,
                      " and ", used_ftr_name);
    }
  }
  else
  {
    ned_message_2 ("Reading File ", adjusted_filename);
  }

#ifndef MSDOS
  if (stat (adjusted_filename, &st) == 0)
  { /* check for write permission and set to read-only mode if necessary */
    /* chmod (adjusted_filename, st.st_mode); */
  }
#endif /* MSDOS */

  if ((ft= fopen (adjusted_filename, "rb")) == (FILE *) 0)
  {
    free (adjusted_filename);
    return -1;
  }

  so= new_stream_file_object (ft);
  fseek (ft, la_offset, 0);
  so->position= ftell (ft);

  if (f_rd_ftr)
  {
    if ((ff= fopen (used_ftr_name, "rt")) != (FILE *) 0)
    {
      fscanf (ff, "%d", &flcnt);
      if (flcnt == 0)
      {
        fscanf (ff, "%d%d%d%d%d%d%d",
              &w->cx,      &w->znr, &w->hv,  &w->attr_text,
              &w->ins_flg, &w->ai,  &w->wwc);
        ftr_read= 1;
      }

      fscanf (ff, "%d%d", &flcnt, &fccnt);
      if (feof (ff))
      {
        fclose (ff);
        ff= (FILE *) 0;
      }
    }
  }

  free_or_what (used_ftr_name);

  ned_stream_read (w, laptr, lzptr, lz_offset, format,
                   so, ff, flcnt, fccnt);

  if (ff != (FILE *) 0) fclose (ff);
  fclose (ft);
  free (so);

  free (adjusted_filename);
  free_or_what (adjusted_ftrname);

  return ftr_read;
}
