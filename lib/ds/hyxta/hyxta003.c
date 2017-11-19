/*
 *  FILE ~/usr/ds/hyxta/hyxta003.c
 *
 *  textual analysis:
 *  break codes
 *
 *  written:       1990 11 11
 *  latest update: 1995-03-30: moved to %ds/hyxta
 *
 */

#include <stdio.h>
#include <gg/parse.h>
#include <gg/ta.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

#define MATRIX_SIZE 36

static int initialized= 0;
static int BREAK_TABLE [MATRIX_SIZE][MATRIX_SIZE];

/* ------------------------------------------------------------------------ */
#define OVERLAY1_size 34
static int BREAK_overlay1 [OVERLAY1_size] =
{
/*TA_CAT_space1,        TA_CAT_space2, */
/*TA_CAT_space2,        TA_CAT_space1, */

  TA_CAT_small,         TA_CAT_small,
  TA_CAT_small,         TA_CAT_capital,
  TA_CAT_small,         TA_CAT_nat_small,
  TA_CAT_small,         TA_CAT_nat_capital,
  TA_CAT_capital,       TA_CAT_small,
  TA_CAT_capital,       TA_CAT_capital,
  TA_CAT_capital,       TA_CAT_nat_small,
  TA_CAT_capital,       TA_CAT_nat_capital,
  TA_CAT_nat_small,     TA_CAT_small,
  TA_CAT_nat_small,     TA_CAT_capital,
  TA_CAT_nat_small,     TA_CAT_nat_small,
  TA_CAT_nat_small,     TA_CAT_nat_capital,
  TA_CAT_nat_capital,   TA_CAT_small,
  TA_CAT_nat_capital,   TA_CAT_capital,
  TA_CAT_nat_capital,   TA_CAT_nat_small,
  TA_CAT_nat_capital,   TA_CAT_nat_capital
} ;

/* ------------------------------------------------------------------------ */
int hyx_ta_get_break_code (int last_cat_code, int act_cat_code)
/* Return: -1 ... error                         */
/*          0 ... no break                      */
/*          1 ... break; 'phasechange'          */
{
  if (!initialized) hyx_ta_break_table_init (BREAK_DEFAULT_init);

  if (last_cat_code < 0 || act_cat_code < 0) return 1;
  if (last_cat_code >= MATRIX_SIZE
     || act_cat_code  >= MATRIX_SIZE)
    return (last_cat_code != act_cat_code);

  return BREAK_TABLE [last_cat_code][act_cat_code];

#ifdef STATIC_TABLE    /* not used any longer */
  return (last_cat_code == act_cat_code)
           ? 0
           : (((   last_cat_code == TA_CAT_small
                || last_cat_code == TA_CAT_capital
                || last_cat_code == TA_CAT_nat_small
                || last_cat_code == TA_CAT_nat_capital)
              &&(  act_cat_code == TA_CAT_small
                || act_cat_code == TA_CAT_capital
                || act_cat_code == TA_CAT_nat_small
                || act_cat_code == TA_CAT_nat_capital))
              ? 0 : 1);
#endif           
  
}

/* ------------------------------------------------------------------------ */
int hyx_ta_break_table_init (int mode)
{
  int i, j;
  int v1= 0;
  int v2= 0;

  switch (mode & 0x03)
  {
    case 0: v1= v2= 0;        break;
    case 1: v1= v2= 1;        break;
    case 2: v1= 0; v2= 1;     break;
    case 3: v1= 1; v2= 0;     break;
  }

  for (i= 0; i < MATRIX_SIZE; i++)
      for (j= 0; j < MATRIX_SIZE; j++)
          BREAK_TABLE [i][j]= (i==j) ? v1 : v2;

  initialized= 1;

  switch (mode & 0x0C)
  {
    case 4:
      hyx_ta_break_table_overlay (BREAK_overlay1, OVERLAY1_size, 0);
      break;
  }

  return 0;
}

/* ------------------------------------------------------------------------ */
void hyx_ta_break_table_dump (char *s)
{
  int i,j;

  printf ("break table: (%s)\n", s);
  for (i= 0; i < MATRIX_SIZE; i++)
  {
    printf ("[%2d] ", i);
    for (j= 0; j < MATRIX_SIZE; j++)
        printf (" %d", BREAK_TABLE [i][j]);
    printf ("\n");
  }
}

/* ------------------------------------------------------------------------ */
void hyx_ta_break_table_overlay (int pairs [], int cnt, int code)
{
  if (!initialized) hyx_ta_break_table_init (BREAK_DEFAULT_init);

  for (; cnt > 1; cnt -= 2)
  {
    hyx_ta_set_break_code (pairs [0], pairs [1], code);
    pairs += 2;
  }
}

/* ------------------------------------------------------------------------ */
int hyx_ta_set_break_code (int last_cat_code, int act_cat_code, int code)
{
  if (!initialized) hyx_ta_break_table_init (BREAK_DEFAULT_init);

  if (last_cat_code < 0 || act_cat_code < 0
      || last_cat_code >= MATRIX_SIZE
      || act_cat_code  >= MATRIX_SIZE) return -1;

  BREAK_TABLE [last_cat_code][act_cat_code] = code;

  return 0;
}
