/*
 *  FILE %ds/hyxta/hyxta102.c
 *
 *  textual analysis with TA_OBJECT
 *
 *  written:       1994-06-01
 *  latest update: 1999-11-28 13:29:21
 *
 */

#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <gg/parse.h>
#include <gg/ta.h>
#include <gg/dirty.h>

/* ------------------------------------------------------------------------ */
struct TA_OBJECT *tao_mk_string (char *str, int size)
{
  struct TA_OBJECT *tao;
  char *cp;

printf ("tao_mk_string: size=%d\n", size);
dump (stderr, str, size);

  if ((tao= (struct TA_OBJECT *) calloc (sizeof (struct TA_OBJECT), 1))
      == (struct TA_OBJECT *) 0
     || (cp= malloc (size+1)) == (char *) 0)
    return (struct TA_OBJECT *) 0;

  memcpy (cp, str, size);
  cp [size]= 0;
  tao->TAO_type= TAOT_string;
  tao->TAO_size= (int) size;
  tao->TAO_body= cp;

  return tao;
}
