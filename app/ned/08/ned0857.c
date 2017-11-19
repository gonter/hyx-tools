/*
 *  FILE %ned/08/ned0857.c
 *
 *  see also ned_lookup_tag ()
 *
 *  written:       1995-04-22
 *  latest update: 1999-04-25 16:33:34
 *  $Id: ned0857.c,v 1.4 2010/05/04 02:47:07 gonter Exp $
 *
 */

#ifdef MSDOS
/* #pragma check_stack(off) */
#endif

#include <string.h>
#include <stdlib.h>
#include <gg/strings.h>
#include <gg/filename.h>
#include <gg/tfb.h>
#include <gg/array.h>
#include "ed.h"
#include "edctx.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
extern struct NED_CONTEXT *ned_main_context;

/* ------------------------------------------------------------------------ */
int ned_lookup_feature (
const char *token,              /* string to be searched                    */
char *line_buffer,              /* string to hold feature buffer            */
char **feature_string,          /* pointer to feature string                */
char **feature_type,            /* type of the the feature string           */
int MAX_BUFFER)                 /* size of line buffer                      */
{
  struct ARRAY_ELEMENT *e_crf;
  struct NED_TAG_RULE_DESCRIPTOR *trd;
  NED_tag_rule *tr;
  char *act_ftr_tfb= (char *) 0;
  char *act_ftr_lut= (char *) 0;
#define MAX_FIELDS 3
  char *fields [MAX_FIELDS];
  int n_fields;
  int rc;

  if (feature_string == (char **) 0 || feature_type == (char **) 0) return 1;

  *feature_string= *feature_type= (char *) 0;

  /* First: check the cache */
  if (ned_lookup_feature_cache (token, feature_string, feature_type) == 1)
    return 0;

  /* Second: check if there is an applicable rule */
  for (e_crf= array_top (ned_main_context->NED_CTX_tag_rules);
       e_crf != (struct ARRAY_ELEMENT *) 0;
       e_crf= e_crf->next)
  {
    if ((trd= (struct NED_TAG_RULE_DESCRIPTOR *) e_crf->payload)
                != (struct NED_TAG_RULE_DESCRIPTOR *) 0
        && (tr= trd->tr) != (NED_tag_rule *) 0
        && (*tr) (token, feature_string, feature_type, trd->client_data) == 1
       )
    { /* save the result for the next time */
      ned_store_feature_cache (token, *feature_string, *feature_type);
      return 0;
    }
  }

  /* Third: check each registered feature table */
  for (e_crf= array_top (ned_main_context->NED_CTX_feature_tables);
       e_crf != (struct ARRAY_ELEMENT *) 0;
       e_crf= e_crf->next)
  {
    act_ftr_tfb= translate_logic_filename ((char *) e_crf->payload);

    /* T2D: move that up to the context structure */
    act_ftr_lut= fnmcpy2 (act_ftr_tfb, ".lut");

    rc= tfb_get_entry (token, act_ftr_tfb, act_ftr_lut,
                       line_buffer, MAX_BUFFER);

    free_or_what (act_ftr_tfb);
    free_or_what (act_ftr_lut);

    if (rc == 1
        && (n_fields= split_string (line_buffer, ':', fields, MAX_FIELDS))>=3)
    {
      ned_store_feature_cache (token,
                               *feature_string= fields [2],
                               *feature_type= fields [1]);

      return 0;
    }
  }

  return 1;
}
