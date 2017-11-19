/*
 *  FILE C:\usr\window\win1.arc [WIN_0117.C]
 *
 *  1989 08 16: aus WIN1.SAR Åbernommen
 *              Revision
 *
 */

#include <gg/window.h>

typedef char *strng;
static char p [400];

w_printf (a01, a02, a03, a04, a05, a06, a07, a08, a09, a10,
          a11, a12, a13, a14, a15, a16, a17, a18, a19, a20)
strng     a01, a02, a03, a04, a05, a06, a07, a08, a09, a10,
          a11, a12, a13, a14, a15, a16, a17, a18, a19, a20;
{ sprintf (p,
          a01, a02, a03, a04, a05, a06, a07, a08, a09, a10,
          a11, a12, a13, a14, a15, a16, a17, a18, a19, a20);
  w_puts  (p);
}

