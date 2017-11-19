/*
 *  FILE %ned/04/ned0403.c
 *
 *  File I/O: Save- /Load-File
 *
 *  written:       1987 04 08
 *                 1990 01 12: Isolation
 *                 1991 01 28: Revision
 *                 1991 09 18: use logic path names
 *  latest update: 2000-12-09 17:12:39
 *  $Id: ned0403.c,v 1.3 2000/12/09 17:33:10 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <gg/hytxt.h>
#include <gg/filename.h>
#include <gg/sbr.h>
#include <gg/convent.h>
#include <gg/strings.h>
#include "ed.h"
#include "edhyx.h"
#include "message.h"
#include "proto.h"

#define VARIANTE1

extern int ned_werr_dont_complain;
extern int block_mode;
extern struct MARKER b_beg, b_end;

/* ------------------------------------------------------------------------ */
static long cdecl WRITE_STR (char *s, FILE *ft);

static long WRITE_STR (char *s, FILE *ft)
{
  long cnt= 0;

  while (*s)
  {
    fputc (*s++, ft);
    cnt++;
  }
  return cnt;
}

/* ------------------------------------------------------------------------ */
int ned_f_write (
struct WINDOWCTRL *w,           /* betroffenes Window                       */
char *filenm_txt,               /* Text    File NAME                        */
char *filenm_ftr,               /* Feature File NAME                        */
int  f_wr_ftr,                  /* 1 -> getrenntes Feature File schreiben   */
int  lz_flag,                   /* 1 -> lzPtr nicht beachten                */
struct LINE *laptr,             /* 1. Zeile                                 */
struct LINE *lzptr,             /* letzte Zeile inklusiv                    */
long *la_offset,                /* begin of written file                    */
long *lz_offset,                /* end of written file                      */
int  flg2)                      /* various operation flags                  */
{
  FILE *ft;                     /* Text    File HANDLE                      */
  FILE *ff= (FILE *) 0;         /* Feature File HANDLE                      */
  int column_idx;               /* Spalte in der Zeile                      */
  int ll;                       /* Line Length                              */
  int lsl;                      /* Line Segment Length                      */
  int lcnt;                     /* Zeilenzaehler fuer FTR                   */
  int ccnt;                     /* column counter for feature               */
  int vfccnt;                   /* column counter for feature written to ff */
  int fccnt= -1;                /* column when feature was written last time*/
  int eoln;                     /* End-Of-Line Code                         */
  int write_mode;               /* Block oder normal BIN/ASCII/SGML         */
  int format;                   /* File Format: Binary/ASCII/SGML           */
  long actual_pos= 0L;          /* position in file                         */
  int repl_size= 0;             /* number of chars as replace text to kill  */
#ifdef VARIANTE2                /* write only necessary items as entity     */
  char *entity;                 /* SGML Entity string to write to file      */
#endif
  int f_wr_stamp= 0;/*1*/       /* write a timestamp after first tag        */
  char *adjusted_filename;      /* physical filename after logic conversion */
  char *adjusted_ftrname= (char *) 0;
  int f_adj_fnm= 0;
  int f_adj_ftr= 0;
  int rc= 0;

  register struct LINE *lp;
  register struct TXT  *tx;
  struct FEATURE *fp;
  char *used_ftr_name= (char *) 0;
  char *used_bak_name= (char *) 0;
  char *cp;

  if ((lp= laptr) == (struct LINE *) 0) return -1;      /* keine leeren Files */

  if ((adjusted_filename= translate_logic_filename (filenm_txt)) == (char *) 0)
       adjusted_filename= filenm_txt;
  else f_adj_fnm=1;

  format= w->file_format;
  if (flg2 & FLG2_format_change)
  {
    switch (format)
    {
      case FMT_ASCII:
        format= FMT_SGML;
        break;
      case FMT_SGML:
        format= FMT_ASCII;
        break;
    }
  }

  if (filenm_ftr == (char *) 0
      || *filenm_ftr == 0
      || (flg2 & (FLG2_append_mode | FLG2_block_mode))
      || format == FMT_BINARY
      || format == FMT_SGML
     ) f_wr_ftr= 0;

  if (f_wr_ftr)
  {
    if ((adjusted_ftrname= translate_logic_filename (filenm_ftr)) == (char *) 0)
         adjusted_ftrname= filenm_ftr;
    else f_adj_ftr= 1;
    used_ftr_name= generate_ned_name (adjusted_ftrname, ".ftr", 1);
    ned_message_4 ("Writing File ", adjusted_filename,
                   " and ", used_ftr_name);
  }
  else
  {
    ned_message_2 ("Writing File ", adjusted_filename);
  }
  eoln= w->bin_eoln;

  if (f_wr_ftr)   /* 1. altes Feature File killen */
  { 
    unlink (used_ftr_name);
    if ((ff= fopen (used_ftr_name, "w")) == (FILE *) 0)
      f_wr_ftr= 0;
    else
    { /* File- und Windowctrl-Features schreiben  */
      fprintf (ff, "0 %3d %4d %3d %3d %1d %1d %d\n",
               w->cx - w->ax + w->hv, w->znr, w->hv, w->attr_text,
               w->ins_flg, w->ai, w->wwc);
    }
  }
  free_or_what (used_ftr_name);

  if (flg2 & FLG2_append_mode)
  { /* Im Append Modus muss altes File erhalten bleiben !!!!! */
    /* Daher kein RENAME und kein UNLINK */
    ft= fopen (adjusted_filename, "ab");
  }
  else
  { /* neues File anlegen */
#ifndef MSDOS
    struct stat st;
#endif
    used_bak_name= generate_ned_name (adjusted_filename, ".bak", 1);
    unlink (used_bak_name);
    rename (adjusted_filename, used_bak_name);

    ft= fopen (adjusted_filename, "wb");
#ifndef MSDOS
    if (stat (used_bak_name, &st) == 0)
    { /* COPY_PERMISSIONS under Unix, copy permissions of old file! */
      chmod (adjusted_filename, st.st_mode);
    }
#endif /* MSDOS */
    free_or_what (used_bak_name);
  }

  if (ft == (FILE *) 0)
  {
    if (f_wr_ftr) fclose (ff);

    if (ned_werr_dont_complain == 0)    /* if flag set, this is OK!         */
    {
      char buff [80];
      sprintf (buff, "File %.40s not open!", filenm_txt);
      ned_error_message (buff);
      rc= -1;
    }

    goto STOP;
  }

  if (flg2 & FLG2_append_mode) /* APPEND: Leerzeile einfuegen */
  {
    if (lp->line_flg & LINE_CODE_0x0D) fputc (0x0D, ft);
    fputc (eoln, ft);
    fseek (ft, (long) 0, 1);
    actual_pos= ftell (ft);
  }
  *la_offset= *lz_offset= actual_pos;

  write_mode= (flg2 & FLG2_block_mode) ? block_mode /* 1..3 */ : 0;

  /* now, write all text lines */
  for (lcnt= 1;; lcnt++)
  { /* the beginning of a line */
    if ((tx= lp->txt) == (struct TXT *) 0)
    { /* empty lines */
      ll= 0;
      lsl= 0;
      cp= (char *) 0;
    }
    else
    {
      ll= lp->lng;
      lsl= tx->t_lng;
      cp= tx->t;
    }

    column_idx= 0;
    vfccnt= ccnt= 0;
    fp= lp->ftr;
    repl_size= 0;               /* replace text at the end of a line should */
                                /* not eat up characters in the next line.  */

    while (ll-- > 0)
    {
      if (lsl == 0)
      {
        if ((tx= tx->next) == (struct TXT *) 0) break;
        lsl= tx->t_lng;
        cp= tx->t;
      }

      switch (write_mode)
      {
        case 1:
          if (b_beg.ptr == lp && column_idx <  b_beg.offset) break;
          if (b_end.ptr == lp && column_idx >= b_end.offset) break;
          goto WRITE;
          break;
        case 3:
          if (column_idx <  b_beg.offset) break;
          if (column_idx >= b_end.offset) break;
          goto WRITE;
          break;
        case 0:
        case 2:
        default:
WRITE:
          if (format == FMT_SGML)
          { /* Im SGML Format ggf. Feature Segment als Tags schreiben */
            if (fp != (struct FEATURE *) 0)
            {
              repl_size += wr_sgml_tag (ft, fp, column_idx, &actual_pos);
              /* Replacement Array uebergehen!! (ANM: += ???) */
              if (f_wr_stamp)
              {
                actual_pos += hyx_write_stamp (ft, (char *) 0);
                f_wr_stamp= 0;
              }
            }

            if (repl_size == 0)
            {
#ifdef VARIANTE1 /* write only necessary items as entity */
              switch (*cp & 0x00FF)
              {
                case '&': actual_pos += WRITE_STR ("&amp;", ft); break;
                case '<': actual_pos += WRITE_STR ("&lt;",  ft); break;
                case '>': actual_pos += WRITE_STR ("&gt;",  ft); break;
                default:
                  fputc (*cp, ft);
                  actual_pos++;
                  break;
              }
#endif
#ifdef VARIANTE2 /* write everything as entity if possible */
              entity= get_pc_sgml_entity (*cp & 0x00FF);
              if (entity == (char *) 0)
              {
                fputc (*cp, ft);
                actual_pos++;
              }
              else
              {
                fputc ('&', ft);
                actual_pos += 2 + WRITE_STR (entity, ft);
                fputc (';', ft);
              }
#endif
            }
            else
            {
              repl_size--;
              if (repl_size < 0) repl_size= 0;
            }
            break;
          }

          if (f_wr_ftr
              && fp != (struct FEATURE *) 0
              && ccnt != fccnt
                 /* otherwise we would repeat writing the same feature      */
                 /* element with replace text for the rest of the line.     */
              && repl_size == 0
                 /* but don't try it while skipping replace chars           */
             )
          {
            repl_size += wr_ftr (ff, lcnt, fp, ccnt, vfccnt);
            fccnt= ccnt;
          }

          if (repl_size == 0)
          {
            fputc (*cp, ft);
            actual_pos++;
            ccnt++;
            vfccnt++;
          }
          else
          {
            repl_size--;
            ccnt++;             /* 1997-01-26 10:40:39 Test, BUG? */
            if (repl_size < 0) repl_size= 0;
          }
          break;
      }
      cp++;
      lsl--;
      column_idx++;
    }

    if (fp != (struct FEATURE *) 0)
    {
      if (format == FMT_SGML)   /* Im SGML Format ggf. Feature Segment am   */
      {                         /* Zeilenende als Tags schreiben            */
        wr_sgml_tag (ft, fp, column_idx, &actual_pos);
        if (f_wr_stamp)
        {
          actual_pos += hyx_write_stamp (ft, (char *) 0);
          f_wr_stamp= 0;
        }
      }
      else
      {
        if (f_wr_ftr && fp != (struct FEATURE *) 0)
          wr_ftr (ff, lcnt, fp, ccnt, vfccnt);
      }
    }

    if (!lz_flag && lzptr == lp) break;
    if (format != FMT_BINARY && lp->next != (struct LINE *) 0)
    {
      /* im Binaer Modus werden CR und LF nur geschrieben,             */
      /* wenn diese Zeichen in der Zeile abgespeichert sind !!!        */
      if (lp->line_flg & LINE_CODE_0x0D || (flg2 & FLG2_write_crlf))
      {
        fputc (0x0D, ft);
        actual_pos++;
      }  
      fputc (eoln, ft);
      actual_pos++;
    }
    if ((lp= lp->next) == (struct LINE *) 0) break;
  }

  *lz_offset= actual_pos -1L;
  fclose (ft);
  if (f_wr_ftr) fclose (ff);

STOP:
  if (f_adj_fnm) free (adjusted_filename);
  if (f_adj_ftr) free (adjusted_ftrname);

  return rc;
}
