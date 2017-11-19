/*
 *  FILE %ds/attlist/attl0009.c
 *
 *  manipulation of attribute lists
 *  +  creation of new attribute lists
 *
 *  written:       2002-04-20
 *  latest update: 2002-04-20 18:37:36
 *  $Id: attl0009.c,v 1.1 2002/05/02 06:48:29 gonter Exp $
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/attlist.h>

/* ------------------------------------------------------------------------ */
ATTLIST *new_ATTLIST (void)
{
  ATTLIST *al;

  if ((al= (ATTLIST *) calloc (sizeof (ATTLIST), 1)) == (ATTLIST *) 0)
    return (ATTLIST *) 0;

  al->AL_append= &al->AL_start;

  return al;
}

