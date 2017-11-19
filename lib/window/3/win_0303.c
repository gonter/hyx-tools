/*
 *  FILE ~/usr/window/3/win_0303.c
 *
 *  written:       1991 02 17
 *  latest update: 1994-08-20
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
static char *W_COLOR_NAMES [8] =
{
  "bla", "blu", "gre", "cob",
  "red", "man", "bro", "whi"
} ;

/* ------------------------------------------------------------------------ */
void report_attribute_value (int attr, char *s)
{
  char *cp;

  s [0] = 'F';
  s [1] = ':';
  s [2] = (attr & 0x08) ? 'H' : 'L';
  cp = W_COLOR_NAMES [attr & 0x07];
  s [3] = *cp++;
  s [4] = *cp++;
  s [5] = *cp;
  s [6] = '/';
  s [7] = 'B';
  s [8] = ':';
  s [9] = 'L';
  cp = W_COLOR_NAMES [(attr>>4) & 0x07];
  s [10] = *cp++;
  s [11] = *cp++;
  s [12] = *cp;
  s [13] = 0;
  if (attr & 0x0080)
  {
    s [14] = '/';
    s [15] = 'B';
    s [16] = 'L';
    s [17] = 0;
  }
}
