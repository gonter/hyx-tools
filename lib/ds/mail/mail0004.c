/*
 *  FILE %usr/mail/mail0004.c
 *
 *  convert a date string into a filename
 *
 *  written:       1995-01-29: aus DISTMAIL.C extrahiert
 *  latest update: 1997-11-27 19:58:43
 *
 */

#include <stdio.h>
#include <string.h>
#include <gg/sbr.h>
#include <gg/strings.h>
#include <gg/convent.h>
#include <gg/rfc822.h>
#include <gg/dates.h>

/* ------------------------------------------------------------------------ */
static FILE *fo;
static int fo_open= 0;

#define LOG_MODE_distmail       0
#define LOG_MODE_dirinf         1
static int log_mode= LOG_MODE_dirinf;

#define FIELD_LENGTH 512
static char Addr [FIELD_LENGTH];
static char Date [FIELD_LENGTH];
static char Subject [FIELD_LENGTH];
static int cnt_lines= 0;

#define FNM_SIZE 80
static char fo_name [FNM_SIZE];
static char new_fnm [FNM_SIZE];

/* ------------------------------------------------------------------------ */
#define LINE_SIZE 512
static char LINE [LINE_SIZE];

/* ------------------------------------------------------------------------ */
int breakup (char *fn, struct BREAKUP_CONTROL *bc)
{
  FILE *fi;
  int rv, i;
  int remove_counter= 0;
  int in_header= 0;
  int header_field;

  if ((fi= fopen (fn, "rb")) == (FILE *) 0)
  {
    fprintf (stderr, "File %s not opened!\n", fn);
    return -1;
  }

  for (;;)
  {
    rv= fread_line (fi, LINE, LINE_SIZE);
    if (rv < 0 && feof (fi)) break;

    if (rv >= 20 && message_delimiter (LINE, bc->BC_delimiter_mode))
    { /* Grenze einer Message identifiziert ??? */
      close_current_file (bc);
      new_file (bc);
      for (i= 0; i < bc->BC_dummy_lines; i++)
         fprintf (fo, "DUMMY %d\r\n", i);
      remove_counter= bc->BC_remove_lines;
      in_header= 1;
      Addr [0]= 0;
      Date [0]= 0;
      Subject [0]= 0;
      cnt_lines= 0;
      continue;
    }

    if (remove_counter > 0)
    {
      remove_counter--;
      continue;
    }

    if (in_header)
    {
      header_field= (int) RFC822_chk_keyword (LINE, rv);
      switch (header_field)
      {
        case RFC822_blank:
          in_header= 0;
          break;
        case RFC822_From:
        case RFC822_To:
          if (bc->BC_use_addr == header_field && Addr [0] == 0)
            strnscpy (Addr, LINE, FIELD_LENGTH);
          break;
        case RFC822_Date:
          if (Date [0] == 0)
            strnscpy (Date, LINE, FIELD_LENGTH);
          break;
        case RFC822_Subject:
          if (Subject [0] == 0)
            strnscpy (Subject, LINE, FIELD_LENGTH);
          break;
      }
    }

    if (fo_open)
    {
      if (bc->BC_is_hyx)
           fputs_entity (LINE, fo, CONVENT_pc_text);
      else fputs (LINE, fo);
      fputc ('\n', fo);
      cnt_lines++;
    }
  }

  fclose (fi);
  close_current_file (bc);

  return 0;
}

/* ------------------------------------------------------------------------ */
int close_current_file (struct BREAKUP_CONTROL *bc)
{
  BC_REPORT_MAIL *report;

  if (bc->BC_is_hyx)
  {
    if (fo_open)
    {
      char *p_addr;
      char *p_subj;

      normalize_date (new_fnm, Date, 1);
      p_addr= locate_word (Addr, 1);
      p_subj= locate_word (Subject, 1);
      if ((report= bc->BC_report_mail) != (BC_REPORT_MAIL *) 0)
        (*report) (bc, fo_name, p_addr, new_fnm, p_subj, cnt_lines);
      fprintf (bc->BC_hyx, "</Frame>\n");
    }
  }
  else
  {
    if (fo_open) fclose (fo);

    if (bc->BC_f_rename_file && Date [0] != 0)
    {
      mk_fnm_from_date (new_fnm, Date, 1);
      unlink (new_fnm);
      rename (fo_name, new_fnm);
    }
  }

  fo_open= 0;

  return 0;
}

/* ------------------------------------------------------------------------ */
int new_file (struct BREAKUP_CONTROL *bc)
{
  sprintf (fo_name, bc->BC_format, bc->BC_counter);

  if (log_mode == LOG_MODE_distmail && bc->BC_log != (FILE *) 0)
  {
    fprintf (bc->BC_log,
             "%s 1 MAILER %04d M PUN 0 001 NONE xx/xx yy/yy/yy %s %s qqq\n",
             fo_name, bc->BC_counter, bc->BC_f_name, bc->BC_f_type);
  }

  bc->BC_counter++;

  if (bc->BC_is_hyx)
  {
    fo= bc->BC_hyx;
    fprintf (bc->BC_hyx, "<Frame %s>\n", fo_name);
  }
  else
  {
    if ((fo= fopen (fo_name, "wb")) == (FILE *) 0) return -1;
  }
  fo_open= 1;

  return 0;
}
