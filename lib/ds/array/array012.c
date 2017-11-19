/*
 *  FILE %ds/array/array012.c
 *
 *  processing of arrays (similar to perl)
 *
 *  written:       1997-03-30
 *  latest update: 1997-11-02 13:43:38
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/array.h>

/* ------------------------------------------------------------------------ */
struct ARRAY_CONTROL *array_append_split_destructive (
struct ARRAY_CONTROL *ac,
char *str,
int split_char,
int max_fields)
{
  char *fields [MAX_ARRAY_SPLIT];
  int n_fields;
  int i;

  if (str == (char *) 0
      || (ac == (struct ARRAY_CONTROL *) 0
          && (ac= array_new ()) == (struct ARRAY_CONTROL *) 0
         )
     )
    return ac;

  if (max_fields > MAX_ARRAY_SPLIT) max_fields= MAX_ARRAY_SPLIT;

  n_fields= split_string (str, split_char, fields, max_fields);
  if (n_fields > max_fields) n_fields= max_fields;

  for (i= 0; i < n_fields; i++)
  {
    array_push (ac, strdup (fields [i]));
  }

  return ac;
}
