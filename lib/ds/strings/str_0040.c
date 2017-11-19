/*
 *  FILE %ds/strings/str_0040.c
 *
 *  written:       1993-02-07
 *  latest update: 1997-11-09 11:12:53
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
struct OPERATION *get_operation (
struct OPERATION ops [],
int n_ops,
char *str)
{
  int i;

  for (i= 0; i<n_ops; i++)
    if (abbrev (ops[i].OP_name, str, ops[i].OP_minimal_length))
      return &ops[i];

  return (struct OPERATION *) 0;
}
