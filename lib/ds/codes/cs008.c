/*
 *  %dpp/codes/cs008.c
 *
 *  written:      1993-01-06: g.gonter@ieee.org
 *  latet update: 1995-12-10
 *
 */

#include <stdlib.h>
#include <gg/codes.h>

/* ------------------------------------------------------------------------ */
int cs_free_fields (
struct CS_field *csf,
/* void ((*free_info) (void *info)), */
int free_names,
int free_values)
{
  struct CS_field *csf2;

  while (csf != (struct CS_field *) 0)
  {
    if (free_names && csf->CSf_name != (char *) 0) free (csf->CSf_name);
    if (free_values && csf->CSf_string != (char *) 0) free (csf->CSf_string);
/*********
    if (free_info != (void (*free_info) (void *)) 0)
      (*free_info) (csf->CSf_info);
*********/

    csf2= csf;
    csf= csf->CSf_next;
    free (csf2);
  }

  return 0;
}
