/*
 *  FILE %ds/hyxp/hyxp0031.c
 *
 *  Verwaltung von TAG Defintionen
 *
 *  written:       1994-12-22
 *  latest update: 1997-11-02 23:21:34
 *
 */

#include <string.h>
#include <gg/strings.h>
#include <gg/parse.h>
#include <gg/dpp.h>

/* ------------------------------------------------------------------------ */
int hyx_process_tag_definition (struct HYX_PARSER_CLASS *hpc, char *line)
{
  long id;
  long weight;
  int mode;
  int ty;
  int n_fields;
#define N_FIELDS 7
  char *fields [N_FIELDS];

  if (line [0] == '#') return 0;

  n_fields= isolate_tokens (line, fields, N_FIELDS);

  if (strcmp (fields [0], "D") == 0)
  {
    if (n_fields  < N_FIELDS-1) return -1;
    if (n_fields  > N_FIELDS) n_fields= N_FIELDS;
    if (n_fields == N_FIELDS-1) fields [N_FIELDS-1]= (char *) 0;

    id=         get_parameter_value (fields [1]);
    mode= (int) get_parameter_value (fields [2]);
    ty=   (int) get_parameter_value (fields [3]);
    weight=     get_parameter_value (fields [4]);

    /* fscanf (fi, "%lx%d%d%ld%s", &id, &mode, &ty, &weight, temp); */
    hyx_make_tag_definition (hpc, fields [5], id, mode,
                            weight, ty, fields [6]);
  }

  return 0;
}
