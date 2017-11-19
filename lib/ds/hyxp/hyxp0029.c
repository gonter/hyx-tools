/*
 *  FILE %ds/hyxp/hyxp0029.c
 *
 *  initialize a parser class
 *
 *  written:       1996-02-18  9:42:46
 *  latest update: 2001-02-18 17:43:56
 *  $Id: hyxp0029.c,v 1.3 2001/02/19 00:27:53 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <gg/parse.h>

/* ------------------------------------------------------------------------ */
struct HYX_PARSER_CLASS *hyx_init_parser_class (void)
{
  struct HYX_PARSER_CLASS *hpc;

  if ((hpc= hyx_new_parser_class ()) != (struct HYX_PARSER_CLASS *) 0)
  {
    hpc->HPC_tag_append= &hpc->HPC_tag_list;

    hpc->HPC_tag_open=           '<';
    hpc->HPC_tag_close=          '>';
    hpc->HPC_entity_open=        '&';
    hpc->HPC_entity_close=       ';';
    hpc->HPC_minimization_char=  '/';
    hpc->HPC_declaration_start=  '!';
    hpc->HPC_processing_start=   '?';

    hpc->HPC_entity_tag_open=    "lt";
    hpc->HPC_entity_tag_close=   "gt";
    hpc->HPC_entity_entity_open= "amp";

    hpc->HPC_next_tag_id= 0x100000L;

    hpc->HPC_po_id_tag= 1;
  }

  return hpc;
}
