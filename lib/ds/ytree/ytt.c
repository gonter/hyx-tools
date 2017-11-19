/*
 *  FILE %ds/ytree/ytt.c
 *
 *  written:       1994-12-08
 *  latest update: 1994-12-08
 *  $Id: ytt.c,v 1.2 2003/06/25 14:38:29 gonter Exp $
 *
 */

#include <stdio.h>
#include <gg/ytree.h>


/* ------------------------------------------------------------------------ */
static struct YTREE *yt= (struct YTREE *) 0;

/* ------------------------------------------------------------------------ */
int cdecl main (void);

int main ()
{
  ytree_operations (&yt, stdin, stdout);

  return 0;
}
