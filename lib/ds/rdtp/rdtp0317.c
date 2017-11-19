/*
 *  FILE %ds/rdtp/rdtp0317.c
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

#include <gg/rdtp.h>
#include <gg/rdtp01.h>
#include <gg/rdtp03.h>

/* ------------------------------------------------------------------------ */
int sgml_decl_token_end (struct RDTP_THREAD *thr, int ch)
{
  struct SGML_BUILDUP *sb;
  char *decl;

  if (thr == (struct RDTP_THREAD *) 0
      || (sb= (struct SGML_BUILDUP *) thr->payload)
          == (struct SGML_BUILDUP *) 0
     )
  {
    rdtp_bad_thread ("rdtp0317");
    return -1;
  }

  sb->bl1 [sb->bl1_cnt]= 0;
  sb->bl1_cnt= 0;
  decl= sb->bl1;

  array_push (sb->tokens, (void *) sgml_tokenizer (decl, sb->token_type));

  /* if the token was delimited by some valid declaration symbol,       */
  /* parse the symbol too!                                              */
  if (ch != ' '
      && !(ch >= 0x09 && ch <= 0x0D)
      && ch != '>' && ch != ']'
      && ch != (char) 0
     )
    sgml_decl_symbol (thr, ch);

  return 0;
}

/* ------------------------------------------------------------------------ */
int sgml_decl_col_token_end (struct RDTP_THREAD *thr, int ch)
{
  sgml_collect (thr, ch);
  return sgml_decl_token_end (thr, (char) 0);
}
