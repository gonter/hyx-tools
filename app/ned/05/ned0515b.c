/*
 *  FILE %ned/05/ned0515b.c
 *
 *  split a line into two new lines and links the results into
 *  the current line list
 *  see also: ned_split ()
 *
 *  written:       1991 01 27: extracted from ned0509.c
 *                 1991 10 13: revision: block flags
 *  latest update: 1999-04-25 16:31:26
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_split2 (                          /* split a line into two lines      */
struct LINE  *split_line,               /* line to be splitted              */
struct LINE **splitted_part,            /* line created after splitting     */
int split_position,                     /* position where splitting is done */
int auto_indent)                        /* 1 -> auto indent for new line    */
/* RETURN: -1 ... error                                                     */
/*         >= 0 ... number of padded blanks, when auto indent was done      */
{
  int rc;

  rc= ned_split (split_line, splitted_part, split_position, auto_indent);

  if (rc >= 0)
  {
    struct LINE *nl;
    struct LINE *nl2;

    nl= *splitted_part;

    nl->prev= split_line;
    nl->next= nl2= split_line->next;
    if (nl2 != (struct LINE *) 0) nl2->prev= nl;
    split_line->next= nl;
  }

  return rc;
}
