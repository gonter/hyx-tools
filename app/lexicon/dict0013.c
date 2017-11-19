/*
 *  FILE %lexicon/dict0013.c
 *
 *  written:       1995-08-04
 *  latest update: 1996-10-10  0:15:55
 *
 */

#include <stdio.h>
#include <contrib/md5gg.h>
#include <gg/hytxt.h>
#include <gg/parse.h>

/* ------------------------------------------------------------------------ */
char *dict_get_frame_name (
struct HYX_CLUSTER_CONTROL *hcc,
char *entry_key,
char *index_str)
{
  /* generate a frame name for the entry */
  switch (hcc->HCC_mode_frame_name)
  {
    case DAFNM_index:
      sprintf (index_str, "LX%08lx", hcc->HCC_next_index);
      return index_str;

    case DAFNM_entry_key:
      return entry_key;
  }

  return MD5check_string ((unsigned char *) entry_key);
}
