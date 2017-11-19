/*
 *  FILE c:/usr/sbr/masked_t.c
 *
 *  Test Modul fÅr MASKED_1.C - Masken Editor
 *
 *  1989 09 22
 *
 */

# include <stdlib.h>
# define  W_MODEL_CGA
# include <gg/window.h>
# include <gg/keys.h>
# include <gg/masked_1.h>

/* ------------------------------------------------------------------------ */
# define FIELDS_1 3
struct MSK_FIELD fields_1 [FIELDS_1] =
{
  {  1,  2, 10, WV_BLAU, WV_GELB },
  {  1,  4, 10, WV_BLAU, WV_GELB },
  { 60,  2, 10, WV_BLAU, WV_GELB }
} ;

static char *data_1 [FIELDS_1];

/* ------------------------------------------------------------------------ */
main ()
{
  int rv, i, upd;

  w_init (0x0001);
  for (i=0; i< FIELDS_1; i++) data_1 [i] = calloc (11, 1); 

  for (;;)
  {
    rv = msk_edit (0, fields_1, data_1, FIELDS_1, &upd);
    if (rv == K_PF7) break;
    sprintf (data_1 [2], "rv=0x%04X", rv);
  }
  printf ("over\n");
}
