/*
 *  FILE %ds/array/array013.c
 *
 *  processing of arrays (similar to perl)
 *
 *  written:       1997-03-30
 *  latest update: 1997-03-30  9:38:22
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <string.h>
#include <gg/array.h>

/* ------------------------------------------------------------------------ */
char *array_join (
struct ARRAY_CONTROL *ac,
char *out_str,
int out_size,
char *conc_str)
{
  struct ARRAY_ELEMENT *ae;
  int conc_size= 0;
  int pl_size;
  char *pl;
  char *out_ptr;

  if (ac == (struct ARRAY_CONTROL *) 0
      || (ae= array_top (ac)) == (struct ARRAY_ELEMENT *) 0
     ) return (char *) 0;

  if (conc_str != (char *) 0) conc_size= strlen (conc_str);
  if (out_size < 0) out_size= 0;

  if (out_str == (char *) 0)
  { /* output string is not allocated, calculate necessary size ! */
    int required_size= 1; /* one extra char for the null character */

    while (1)
    {
      if ((pl= ae->payload) != (char *) 0) required_size += strlen (pl);

      if ((ae= ae->next) == (struct ARRAY_ELEMENT *) 0) break;
      required_size += conc_size;
    }

    required_size += out_size; /* by convention, add this much extra space */

    if ((out_str= malloc (required_size)) == (char *) 0) return (char *) 0;
    out_size= required_size;
  }

  out_ptr= out_str;
  out_size--;           /* reserve for the null char */

  for (ae= array_top (ac); ae != (struct ARRAY_ELEMENT *) 0;)
  {
    if ((pl= (char *) ae->payload) != (char *) 0)
    {
      pl_size= strlen (pl);
      if (out_size < pl_size) break;    /* don't add element if it does     */
                                        /* not fit entirely                 */
      strcpy (out_ptr, pl);
      out_ptr  += pl_size;
      out_size -= pl_size;
    }

    if ((ae= ae->next) == (struct ARRAY_ELEMENT *) 0
        || out_size < conc_size
       ) break;

    if (conc_size > 0)
    {
      strcpy (out_ptr, conc_str);
      out_ptr  += conc_size;
      out_size -= conc_size;
    }
  }

  return out_str;
}
