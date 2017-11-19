/*
 *  FILE %ds/rdtp/rdtp0319.c
 *
 *  restructured dynamic text parser
 *
 *  written:       1996-09-15
 *  latest update: 1996-09-15 10:10:49
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/rdtp.h>
#include <gg/rdtp01.h>
#include <gg/rdtp03.h>

/* ------------------------------------------------------------------------ */
int sgml_tokenize_symbol (struct RDTP_THREAD *thr, int ch, int token_type)
{
  struct SGML_BUILDUP *sb;
  char str [4];

  str [0]= (char) ch;
  str [1]= 0;

  if (thr == (struct RDTP_THREAD *) 0
      || (sb= (struct SGML_BUILDUP *) thr->payload)
          == (struct SGML_BUILDUP *) 0
     )
  {
    rdtp_bad_thread ("rdtp0319");
    return -1;
  }

  array_push (sb->tokens, (void *) sgml_tokenizer (str, token_type));
  return 0;
}

/* ------------------------------------------------------------------------ */
int sgml_decl_symbol (struct RDTP_THREAD *thr, int ch)
{
  int token_type;

  switch (ch)
  {
    case '(':
      token_type= SGML_tokt_begin_group;
      break;

    case ')':
      token_type= SGML_tokt_end_group;
      break;

    case '*':
      token_type= SGML_tokt_asterisk;
      break;

    case '+':
      token_type= SGML_tokt_plus;
      break;

    case ',':
      token_type= SGML_tokt_comma;
      break;

    case '-':
      token_type= SGML_tokt_dash;
      break;

    case '?':
      token_type= SGML_tokt_qm;
      break;

    case '%':
      token_type= SGML_tokt_pct;
      break;

    case '|':
      token_type= SGML_tokt_or;
      break;

    default:
      printf ("bad declaration symbol: 0x%02X\n", ch);
      return -1;
  }

  return sgml_tokenize_symbol (thr, ch, token_type);
}

/* ------------------------------------------------------------------------ */
int sgml_single_dash (struct RDTP_THREAD *thr, int ch)
{
#ifdef MSDOS
  ch;
#endif

  return sgml_decl_symbol (thr, '-');
}

/* ------------------------------------------------------------------------ */
int sgml_single_dash_gbeg (struct RDTP_THREAD *thr, int ch)
{
  sgml_decl_symbol (thr, '-');
  return sgml_decl_symbol (thr, ch);
}

/* ------------------------------------------------------------------------ */
int sgml_single_pct (struct RDTP_THREAD *thr, int ch)
{
#ifdef MSDOS
  ch;
#endif

  return sgml_decl_symbol (thr, '%');
}
