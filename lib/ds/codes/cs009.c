/*
 *  File %dpp/codes/cs009.c
 *
 *  written:       1993-01-06: g.gonter@ieee.org
 *  latest update: 1995-12-10
 *
 */

#include <string.h>
#include <stdlib.h>
#include <gg/codes.h>

/* ------------------------------------------------------------------------ */
static struct CS_attribute_statistics *CSattr= (void *) 0;

/* ------------------------------------------------------------------------ */
int cs_count_attribute (char *attribute, int atype, int used)
{
  struct CS_attribute_statistics *csa;
  struct CS_attribute_statistics **CSa_app;
  int cmp;

  if (atype >= CSft_count || atype < 0) atype= 0;

  CSa_app= &CSattr;
  for (csa= CSattr; csa != (void *) 0; csa= csa->CSa_next)
  {
    cmp= strcmp (csa->CSa_name, attribute);
    if (cmp == 0) goto CNT;
    if (cmp > 0) break;
    CSa_app= &csa->CSa_next;
  }

  csa= calloc (sizeof (struct CS_attribute_statistics), 1);
  csa->CSa_name= strdup (attribute);
  csa->CSa_next= *CSa_app;
  *CSa_app= csa;

CNT:
  csa->CSa_tcnt [atype]++;
  if (used) csa->CSa_ucnt [atype]++;

  return 0;
}

/* ------------------------------------------------------------------------ */
struct CS_attribute_statistics *cs_get_attribute_statistics ()
{
  return CSattr;
}

/* ------------------------------------------------------------------------ */
void cs_reset_attribute_statistics ()
{
  CSattr= (void *) 0;
}
