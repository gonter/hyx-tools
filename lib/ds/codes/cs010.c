/*
 *  File %dpp/codes/cs010.c
 *
 *  written:       1993-01-06: g.gonter@ieee.org
 *  latest update: 1995-12-10
 *
 */

#include <stdio.h>
#include <gg/codes.h>

/* ------------------------------------------------------------------------ */
int cs_print_statistics (FILE *fo)
{
  struct CS_attribute_statistics *csa;
  long tnum_records;
  long unum_records;

  tnum_records= cs_tnum_records ();
  unum_records= cs_unum_records ();

  fprintf (fo, "number of records: %ld,  used: %ld,  ignored: %ld\n",
    tnum_records, unum_records, tnum_records-unum_records);

  fprintf (fo,
           "%-32s %12s %12s %12s\n",
           "attribute name",
           "strings", "numbers", "ids");

  for (csa= cs_get_attribute_statistics ();
       csa != (void *) 0;
       csa= csa->CSa_next)
  {
    fprintf (fo, "%-32s %5ld(%5ld) %5ld(%5ld) %5ld(%5ld)\n",
      csa->CSa_name,
      csa->CSa_tcnt [CSft_string],      csa->CSa_ucnt [CSft_string],
      csa->CSa_tcnt [CSft_number],      csa->CSa_ucnt [CSft_number],
      csa->CSa_tcnt [CSft_identifier],  csa->CSa_ucnt [CSft_identifier]);
  }

  return 0;
}
