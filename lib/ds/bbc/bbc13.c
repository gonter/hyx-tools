/*
 *  FILE %lexicon/bbc13.c
 *
 *  restructure text elements according to lexicon control
 *  see bbc07.c
 *
 *  written:       1995-08-19
 *  latest update: 1995-08-26
 *
 */

#include <stdio.h>
#include <gg/ggcrypt.h>
#include <gg/dyb.h>
#include <gg/parse.h>
#include <gg/bbch.h>

/* ------------------------------------------------------------------------ */
int bbc_transmit_text (
void *cd,
struct TEXT_ELEMENT *te)
{
  struct BBC_CONNECTION *bbcc;
  struct DYNAMIC_BLOCK *db;

  if ((bbcc= (struct BBC_CONNECTION *) cd) == (struct BBC_CONNECTION *) 0
      || (db= dyb_new_block (0)) == (struct DYNAMIC_BLOCK *) 0
     ) return -1;

  dyb_append_string (db, "<:>");
  hyx_unroll_text (db, te, 0, 0, 0);
  dyb_append_string (db, "<;>\n");

printf ("bbc13: sending lexicon entry accross the line\n");
printf ("----- BEGIN -------------------------\n");
dyb_write (1, db);
printf ("\n----- END ---------------------------\n");

  dyb_encrypt_cfb (&bbcc->BBCC_s_o2p, db);
  if (dyb_write (bbcc->BBCC_socket, db) != 0)
    bbcc->BBCC_t2d= BBCCt2d_shutdown;

  dyb_destroy_block (db);

  return 0;
}
