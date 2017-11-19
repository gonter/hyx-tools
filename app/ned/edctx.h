/*
 *  FILE %ned/edctx.h
 *
 *  NED context datastructures and algorithms
 *
 *  written:       1996-11-10
 *  latest update: 1997-08-04  8:52:05
 *  $Id: edctx.h,v 1.4 2010/05/04 02:47:07 gonter Exp $
 *
 */

#ifndef __NED_edctx__
#define __NED_edctx__

#include <gg/array.h>

#ifndef MSDOS
#ifndef cdecl
#define cdecl
#endif
#endif

/* Meta Class Descriptor for all NED variables ---------------------------- */
#define NED_IH_SIZE     10      /* number of input redirections             */

struct NED_CONTEXT
{
  int NED_IH_TOS;                                       /* top of stack     */
  ned_input_handler *NED_input_stack [NED_IH_SIZE];     /* handlers         */
  void *NED_input_stack_cd [NED_IH_SIZE];               /* client data      */

  struct NED_MACRO *NED_macro_table [N_MACRO];
  char *NED_macro_pointer;

  /* lookup and cross reference tables of various kinds */
  struct ARRAY_CONTROL *NED_CTX_crf;
  struct ARRAY_CONTROL *NED_CTX_lib;
  struct ARRAY_CONTROL *NED_CTX_lex;
  struct ARRAY_CONTROL *NED_CTX_thes;
  struct ARRAY_CONTROL *NED_CTX_tag_files;
  struct ARRAY_CONTROL *NED_CTX_feature_tables;

  int NED_CTX_tag_length;

  /* methods */
  struct ARRAY_CONTROL *NED_CTX_tag_rules;
} ;

#define NED_CTXitem_crf                 1
#define NED_CTXitem_lib                 2
#define NED_CTXitem_tag_file            3
#define NED_CTXitem_feature_table       4
#define NED_CTXitem_lexicon             5
#define NED_CTXitem_thesaurus           6

/* ------------------------------------------------------------------------ */
/* Experimental, 1996-11-09 */
typedef int NED_tag_rule (const char *lookup,
                          char **res_string, char **res_type,
                          void *client_data);
/* NOTE: res_string, res_type must be malloced by the method! */

struct NED_TAG_RULE_DESCRIPTOR
{
  char *name;                   /* informal name of the rule                */
  NED_tag_rule *tr;
  void *client_data;
} ;

/* 12/ -------------------------------------------------------------------- */
/* 1201 */ struct NED_CONTEXT *cdecl ned_create_context (void);
/* 1202 */ int cdecl ned_default_context (struct NED_CONTEXT *ctx);
/* 1203 */ int cdecl ned_destroy_context (struct NED_CONTEXT *ctx);
/* 1204 */ int cdecl ned_add_context (struct NED_CONTEXT *ctx,
             int what, const char *file_name, int at_top);
/* 1204b */ int ned_add_context_list (struct NED_CONTEXT *ctx,
              const char *argv[], int argc);
/* 1205 */ int cdecl ned_add_tag_rule (struct NED_CONTEXT *ctx,
             const char *rule_name, NED_tag_rule *tr, void *client_data);
/* 1206 */ char *cdecl ned_get_context (struct NED_CONTEXT *ctx, int what);
/* 1207 */ int cdecl ned_push_input_handler (struct NED_CONTEXT *ctx,
             ned_input_handler *ih, void *client_data);
/* 1208 */ int cdecl ned_pop_input_handler (struct NED_CONTEXT *ctx,
             ned_input_handler **ih, void **client_data);
/* 1211 */ struct NED_FIELD_CONTEXT *ned_create_field_context (
             char *buffer, int buffer_size, int buffer_mode);

/* generalized modules */
/* 1209 */ int ned_add_tag_file (struct NED_CONTEXT *ctx, char *tag_name);
/* 1210 */ int ned_add_feature_table (struct NED_CONTEXT *ctx,
             char *feature_table);
#endif /* !__NED_edctx__ */
