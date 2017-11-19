/*
 *  FILE %ds/rdtp/rdtp0315.c
 *
 *  restructured dynamic text parser
 *
 *  written:       1996-09-15
 *  latest update: 1996-09-15 12:40:33
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gg/rdtp.h>
#include <gg/rdtp01.h>
#include <gg/rdtp03.h>

/* ------------------------------------------------------------------------ */
int sgml_declaration (struct RDTP_THREAD *thr, int ch)
{
  struct SGML_BUILDUP *sb;
  char *decl;

#ifdef MSDOS
  ch;
#endif

  if (thr == (struct RDTP_THREAD *) 0
      || (sb= (struct SGML_BUILDUP *) thr->payload)
          == (struct SGML_BUILDUP *) 0
     )
  {
    rdtp_bad_thread ("rdtp0315");
    return -1;
  }

  sb->bl1 [sb->bl1_cnt]= 0;
  sb->bl1_cnt= 0;
  decl= sb->bl1;

  /***** printf ("declaration: '%s'\n", decl); ******/
  sb->tokens= array_new ();
  array_push (sb->tokens, (void *) sgml_tokenizer (decl, SGML_tokt_literal));

  return 0;
}
