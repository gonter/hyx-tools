/*
 *  FILE %ds/varspace/vspt.c
 *
 *  written:       1994-12-26
 *  latest update: 1997-11-02 13:05:57
 *
 */

#include <stdio.h>
#include <gg/ytree.h>
#include <gg/varspace.h>

/* ------------------------------------------------------------------------ */
static struct YTREE *yt= (struct YTREE *) 0;

/* ------------------------------------------------------------------------ */
int cdecl main (void);

int main ()
{
  vs_operations (&yt, stdin, stdout);

  return 0;
}
