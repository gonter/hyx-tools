/*
 *  FILE %ds/rdtp/rdtp0315.c
 *
 *  restructured dynamic text parser
 *  start of a token of a certain type
 *
 *  written:       1996-09-15
 *  latest update: 1996-09-15 18:46:52
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/rdtp.h>
#include <gg/rdtp01.h>
#include <gg/rdtp03.h>

/* ------------------------------------------------------------------------ */
int sgml_decl_token_beg (struct RDTP_THREAD *thr, int ch, int token_type)
{
  struct SGML_BUILDUP *sb;

#ifdef MSDOS
  ch;
#endif

  if (thr == (struct RDTP_THREAD *) 0
      || (sb= (struct SGML_BUILDUP *) thr->payload)
          == (struct SGML_BUILDUP *) 0
     )
  {
    rdtp_bad_thread ("rdtp0316");
    return -1;
  }

  sb->bl1 [0]= (char) ch;
  sb->bl1_cnt= 1;
  sb->token_type= token_type;

  return 0;
}

/* ------------------------------------------------------------------------ */
int sgml_decl_literal_beg (struct RDTP_THREAD *thr, int ch)
{
  return sgml_decl_token_beg (thr, ch, SGML_tokt_literal);
}

/* ------------------------------------------------------------------------ */
int sgml_decl_sqs_beg (struct RDTP_THREAD *thr, int ch)
{
  return sgml_decl_token_beg (thr, ch, SGML_tokt_sqs);
}

/* ------------------------------------------------------------------------ */
int sgml_decl_dqs_beg (struct RDTP_THREAD *thr, int ch)
{
  return sgml_decl_token_beg (thr, ch, SGML_tokt_dqs);
}

/* ------------------------------------------------------------------------ */
int sgml_decl_num_beg (struct RDTP_THREAD *thr, int ch)
{
  return sgml_decl_token_beg (thr, ch, SGML_tokt_number);
}
