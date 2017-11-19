/*
 *  FILE ~/usr/sgml/sgml0009.c
 *
 *  SGML -> LaTeX: process Characters
 *
 *  written:       1990 10 09
 *  latest update: 1999-04-25 16:40:42
 *
 */

# include <stdio.h>
# include <stdlib.h>
# include <gg/sgml.h>
# include <gg/ta.h>

# pragma check_stack(off)

/* ------------------------------------------------------------------------ */
/* processor codes:                                                         */
/* SGML_PROC_verbatim:  unprozessed                                         */
/* SGML_PROC_text:      normal Text                                         */
/* SGML_PROC_title_1:   titles -> Abteilungsschutz                          */
/* SGML_PROC_title_2:   titles -> wortweise mbox{}                          */

/* processing mode:                                                         */
/* bit 3: Italic Korrektur einsetzen                                        */

/* ------------------------------------------------------------------------ */
static int last_cat_code = -1;
static int italic_correction=0;

/* ------------------------------------------------------------------------ */
sgml_to_list (char *fnam)
{
  FILE *fi;
  int ch;

  sgml_0010_config_processor (1);
/*  if (initialized==0) initialize_sgml_0006 (); */
  last_cat_code = -1;
  italic_correction = 0;

  fi = fopen (fnam, "rb");
  for (;;)
  {
    ch = fgetc (fi) & 0x00FF;
    if (feof (fi)) break;
    sgml_filter (ch);
  }
  fclose (fi);
}

/* ------------------------------------------------------------------------ */
sgml_data_block (int proz, int mode, char *dat, int siz)
{
  if (mode & 0x04) italic_correction=1;
  while (siz-- > 0) _sgml_data_byte (proz, (*dat++) & 0x00FF);
}

/* ------------------------------------------------------------------------ */
sgml_data_byte (int proz, int mode, int ch)
{
  if (mode & 0x04) italic_correction=1;
  _sgml_data_byte (proz, ch);
}

/* ------------------------------------------------------------------------ */
_sgml_data_byte (int proz, int ch)
{
  int cat;

  /* QUICK HACK STARTS HERE !!!! */
  /* produce text, which can be used on a MAC for LaTeX !!!! */

  if (proz != 0) cat= get_cat_code (ch);

  if (proz == 2)      /* Title Text */
  {
    if ((last_cat_code == TA_CAT_small
         || last_cat_code == TA_CAT_capital
         || last_cat_code == TA_CAT_nat_small
         || last_cat_code == TA_CAT_nat_capital
        )
        && (cat == TA_CAT_space1 || cat == TA_CAT_space2)
       )
    { /* im Text Mode und Abteilungsschutz: Worte nicht abteilen lassen */
      sgml_fputs ("\\-");
    }
    last_cat_code= cat;
  }

  if (proz == 3)      /* Title Text: -> mbox */
  {
    if ((last_cat_code == TA_CAT_space1 || last_cat_code == TA_CAT_space2)
        && (cat == TA_CAT_small
            || cat == TA_CAT_capital
            || cat == TA_CAT_nat_small
            || cat == TA_CAT_nat_capital
           )
       )
    { /* im Text Mode und Abteilungsschutz: Worte nicht abteilen lassen */
      sgml_fputs ("\\mbox{");
    }

    if ((last_cat_code == TA_CAT_small
         || last_cat_code == TA_CAT_capital
         || last_cat_code == TA_CAT_nat_small
         || last_cat_code == TA_CAT_nat_capital
        )
        && (cat == TA_CAT_space1 || cat == TA_CAT_space2)
       )
    { /* im Text Mode und Abteilungsschutz: Worte nicht abteilen lassen */
      sgml_fputs ("}");
    }
  }

  if (proz != 0)
  {
    if (italic_correction
        && (last_cat_code == TA_CAT_small
            || last_cat_code == TA_CAT_capital
            || last_cat_code == TA_CAT_nat_small
            || last_cat_code == TA_CAT_nat_capital
           )
        && ((cat == TA_CAT_satz1 && (ch == '!' || ch == '?'))
            || cat == TA_CAT_small
            || cat == TA_CAT_capital
            || cat == TA_CAT_nat_small
            || cat == TA_CAT_nat_capital
            || cat == TA_CAT_digit
           )
       )
    { /* im Text Mode und Italic-Korrectur: kleiner Zwischenraum */
      sgml_fputs ("\\/");
    }
    italic_correction=0;
  }

  switch (proz)
  {
    case 0:
      switch (ch)
      {
        case 0x0D:    /* this passage is still rotten :-(( */
          break;
        case 0x0A:
          ch = 0x0D;
        default:
          sgml_fputc (ch);
          break;
      }
      break;
    case 1:
    case 2:
    case 3:
      switch (ch)
      {
        /* standard TeX translations */
        case '\\':
          sgml_fputs ("{\\backslash}");
          break;
        case '{':
          sgml_fputs ("\\{");
          break;
        case '}':
          sgml_fputs ("\\}");
          break;
        case '$':
          sgml_fputs ("\\$");
          break;
        case '&':
          sgml_fputs ("\\&");
          break;
        case '#':
          sgml_fputs ("\\#");
          break;
        case '^':
          sgml_fputs ("\\^ "); /* ????? */
          break;
        case '_':
          sgml_fputs ("\\_");
          break;
        case '%':
          sgml_fputs ("\\%");
          break;
        case '~':
          sgml_fputs ("\\~ "); /* ???? */
          break;
        case '\"':
          sgml_fputs ("\'\'");
          break;
    
        /* german TeX translations */
        case 'Ñ':
          sgml_fputs ("\"a");
          break;
        case 'é':
          sgml_fputs ("\"A");
          break;
        case 'î':
          sgml_fputs ("\"o");
          break;
        case 'ô':
          sgml_fputs ("\"O");
          break;
        case 'Å':
          sgml_fputs ("\"u");
          break;
        case 'ö':
          sgml_fputs ("\"U");
          break;
        case '·':
          sgml_fputs ("\"s");
          break;
        default:
          switch (ch)
          {
            case 0x0D:    /* this passage is still rotten :-(( */
              break;
            case 0x0A:
              ch = 0x0D;
            default:
              sgml_fputc (ch);
              break;
          }
          break;
        break;
    }
  }

  if (proz != 0) last_cat_code = cat;
}
