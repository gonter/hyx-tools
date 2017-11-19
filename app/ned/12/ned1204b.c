/*
 *  FILE %ned/12/ned1204b.c
 *
 *  written:       1997-08-04
 *  latest update: 1999-04-25 16:36:44
 *  $Id: ned1204b.c,v 1.4 2010/05/04 02:47:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>
#include "ed.h"
#include "edctx.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_add_context_list (
struct NED_CONTEXT *ctx,
const char *argv[],
const int argc)
{
  const char *sub_command;
  const char *arg;
  int at_top= 0;
  int item= -1;
  int i;

  if (argc <= 1
      || (sub_command= argv [0]) == (char *) 0
      || *sub_command == 0
     )
    return -1;

  if (strcmp ("crf", sub_command) == 0
      || abbrev ("cross_reference", sub_command, 3)
     )
  {
    item= NED_CTXitem_crf;
  }
  else
  if (abbrev ("library", sub_command, 3))
  {
    item= NED_CTXitem_lib;
  }
  else
  if (abbrev ("lexicon", sub_command, 3))
  {
    item= NED_CTXitem_lexicon;
  }
  else
  if (abbrev ("thesaurus", sub_command, 4))
  {
    item= NED_CTXitem_thesaurus;
  }
  else
  if (abbrev ("tags", sub_command, 3))
  {
    item= NED_CTXitem_tag_file;
  }
  else
  if (abbrev ("feature_table", sub_command, 4)
      || abbrev ("ftr_tbl", sub_command, 3)
     )
  {
    item= NED_CTXitem_feature_table;
  }
  else
  if (abbrev ("sgmltags", sub_command, 5))
  { /* not strictly a context element, but what the heck ... */
    for (i= 1; i < argc; i++)
      setup_sgml_tag_descriptors (argv [i]);
    return 99;
  }

  if (item < 0) return -1;

  for (i= 1; i < argc; i++)
  {
    arg= argv [i];

    if (strcmp (arg, "-top") == 0
        || strcmp (arg, "-unshift") == 0
       ) at_top= 1;
    else
    if (strcmp (arg, "-end") == 0
        || strcmp (arg, "-push") == 0
       ) at_top= 0;
    else
    ned_add_context (ctx, item, arg, at_top);
  }

  return item;
}
