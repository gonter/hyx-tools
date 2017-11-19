/*
 *  include FILE <gg/rdtp03.h>
 *
 *  restructured dynamic text parser: SGML runtime
 *  - methods
 *  - structures
 *  - prototypes
 *  see also: <gg/hyx.h>
 *
 *  written:       1996-04-02
 *  latest update: 1997-11-26 12:42:06
 *
 */

#ifndef __GG_rdtp03__
#define __GG_rdtp03__

#include <gg/ytree.h>
#include <gg/array.h>

#define SGML_DIAG

/* ------------------------------------------------------------------------ */
/* SGML_tokt_* SGML token types                                             */
#define SGML_tokt_undef         0
#define SGML_tokt_literal       1       /* literal token                    */
#define SGML_tokt_sqs           2       /* single quoted string             */
#define SGML_tokt_dqs           3       /* double quoted string             */
#define SGML_tokt_begin_group   4       /* (                                */
#define SGML_tokt_end_group     5       /* )                                */
#define SGML_tokt_asterisk      6       /* *                                */
#define SGML_tokt_plus          7       /* +                                */
#define SGML_tokt_comma         8       /* , seq connector                  */
#define SGML_tokt_dash          9       /* -                                */
#define SGML_tokt_qm           10       /* ? (question mark) optional par.  */
#define SGML_tokt_pct          11       /* %                                */
#define SGML_tokt_par_ent      12       /* parameter entity: %name;         */
#define SGML_tokt_or           13       /* | or connector                   */
#define SGML_tokt_and          14       /* & and connector                  */
#define SGML_tokt_number       15       /* decimal number                   */

/* SGML_DECLVAL_* declared value type codes; see The SGML Handbook p. 422   */
#define SGML_DECLVAL_undef      0
#define SGML_DECLVAL_CDATA      1
#define SGML_DECLVAL_ENTITY     2
#define SGML_DECLVAL_ENTITIES   3
#define SGML_DECLVAL_ID         4
#define SGML_DECLVAL_IDREF      5
#define SGML_DECLVAL_IDREFS     6
#define SGML_DECLVAL_NAME       7
#define SGML_DECLVAL_NAMES      8
#define SGML_DECLVAL_NMTOKEN    9
#define SGML_DECLVAL_NMTOKENS  10
#define SGML_DECLVAL_NUMBER    11
#define SGML_DECLVAL_NUMBERS   12
#define SGML_DECLVAL_NUTOKEN   13
#define SGML_DECLVAL_NUTOKENS  14
#define SGML_DECLVAL_notation  15
#define SGML_DECLVAL_name_tokg 16

/* SGML_DEFVAL_* default value type codes; see The SGML Handbook p. 425     */
#define SGML_DEFVAL_undef       0
#define SGML_DEFVAL_FIXED       1
#define SGML_DEFVAL_REQUIRED    2
#define SGML_DEFVAL_CURRENT     3
#define SGML_DEFVAL_CONREF      4
#define SGML_DEFVAL_IMPLIED     5

/* ------------------------------------------------------------------------ */
/* SGML_ENTITY_* entity class or type definitions                           */
#define SGML_ENTITY_undef       0
                                        /* parameter literals               */
#define SGML_ENTITY_litstring   1       /* single quoted literal string     */
#define SGML_ENTITY_litstring2  2       /* single quoted literal string     */

                                        /* data text                        */
#define SGML_ENTITY_CDATA       3       /* character data                   */
#define SGML_ENTITY_SDATA       4       /* specific character data          */
#define SGML_ENTITY_PI          5       /* processing instruction           */

                                        /* bracketed text                   */
#define SGML_ENTITY_STARTTAG    6
#define SGML_ENTITY_ENDTAG      7
#define SGML_ENTITY_MS          8
#define SGML_ENTITY_MD          9

                                        /* public and system identifier     */
#define SGML_ENTITY_SYSTEM     10
#define SGML_ENTITY_PUBLIC     11

                                        /* system; sub type                 */
#define SGML_ENTITY_SUBDOC     12
#define SGML_ENTITY_NDATA      13

/* ------------------------------------------------------------------------ */
struct SGML_TOKEN
{
  int type;                             /* see SGML_tokt_*                  */
  char *contents;                       /* contents of the token            */
} ;

/* ------------------------------------------------------------------------ */
struct SGML_ATTRIBUTE_SPEC_LIST         /* system or public notation        */
{                                       /* attribute specification list     */
  struct SGML_ATTRIBUTE_SPEC_LIST *next;
  char *name;                           /* name may be empty!!!             */
  char *value;                          /* attribute value                  */
} ;

/* ------------------------------------------------------------------------ */
struct SGML_ENTITY_SYSTEM_DECL          /* more definition data for         */
{                                       /* SYSTEM and PUBLIC entities       */
  int entity_class;                     /* same as in ENTITY_DECLARATION    */
                                        /* either SYSTEM or PUBLIC          */
  int entity_type;                      /* NONE, SUBDOC, (C|S|N)DATA        */

  char *public_id;
  char *system_id;
  char *notation_name;
  struct SGML_ATTRIBUTE_SPEC_LIST *att_specs; /* 0 or more attr. specs.     */
} ;

/* ------------------------------------------------------------------------ */
struct SGML_ENTITY_DECLARATION          /* DTD: entity definition           */
{                                       /* the same structure is used for   */
                                        /* normal and parameter entities,   */
                                        /* however, they are listed in      */
                                        /* separately from the DTD-struct.  */

  char *name;                           /* entity name                      */
  int entity_class;                     /* see SGML_ENTITY_*                */
  char *text;                           /* replacement text                 */
                                        /* not used for SYSTEM and PUBLIC   */

  struct SGML_ENTITY_SYSTEM_DECL *system_decl;  /* more details for         */
                                                /* SYSTEM and PUBLIC ent.   */
} ;

/* ------------------------------------------------------------------------ */
struct SGML_ATTRIBUTE_DECLARATION       /* DTD                              */
{
  struct SGML_ATTRIBUTE_DECLARATION *next;
  char *name;

  int declared_value;                   /* see SGML_DECLVAL_*               */
  void *declared_value_ptr;

  int default_value;                    /* see SGML_DEFVAL_*                */
  void *default_value_ptr;
} ;

/* ------------------------------------------------------------------------ */
struct SGML_ATTLIST_DECL                /* DTD                              */
{                                       /* can be referenced by several     */
                                        /* element declarations             */
  int ref_count;                        /* number of elements referencing   */
                                        /* to this attribute list decl.     */
  struct YTREE *attribute_declaration;
  struct SGML_ATTRIBUTE_DECLARATION *attributes;
} ;

/* ------------------------------------------------------------------------ */
struct SGML_CONTENT_MODEL               /* DTD                              */
{                                       /* element declarations             */
  int ref_count;                        /* number of elements referencing   */
                                        /* to this content model            */
  void *content;
  void *exclusions;
  void *inclusions;

  struct ARRAY_CONTROL *tmp;            /* temporary hack                   */
} ;

/* ------------------------------------------------------------------------ */
struct SGML_ELEMENT_DECLARATION         /* DTD                              */
{
  char *name;

  int minim_start;                      /* start tag minimization           */
  int minim_end;                        /* end tag minimization             */
  long rank;                            /* rank code, whatever that is      */

  struct SGML_CONTENT_MODEL *cont_mod;
  struct SGML_ATTLIST_DECL *attlist;
} ;

/* ------------------------------------------------------------------------ */
struct SGML_TAG_NAME                    /* document instance statistics     */
{
  struct SGML_ELEMENT_DECLARATION *tag_def;
  char *tag_name;
  long ref_counter;
} ;

/* ------------------------------------------------------------------------ */
struct SGML_ATTRIBUTE_LIST
{
  struct SGML_ATTRIBUTE_LIST *next;

  int attribute_type;                   /* see note: SAt_*                  */
#define SAt_undef               0
#define SAt_NED                 1       /* like Frame names                 */
#define SAt_normal              2
/* Note: more types as specified in the SGML ref                            */

  int flags;                            /* bitfield: SAf_*                  */
#define SAf_name_malloced       0x01
#define SAf_value_malloced      0x02
#define SAf_value_dyb           0x04    /* value is a DYNAMIC_BLOCK         */

#define SAf_value_squoted       0x10    /* single quote necessary           */
#define SAf_value_dquoted       0x20    /* double quote necessary           */
#define SAf_value_escaped       0x40    /* escape chars necessary           */
#define SAf_value_noquote       0x80    /* no quoting necessary             */
#define SAf_value_quote_mask    0xF0

  char *attribute_name;
  void *attribute_value;
} ;

/* ------------------------------------------------------------------------ */
struct SGML_OPENING_TAG                 /* document instance                */
{
  struct SGML_TAG_NAME *tag_name;
  struct SGML_ATTRIBUTE_LIST *attributes;
  struct SGML_ATTRIBUTE_LIST **attr_append;
} ;

/* ------------------------------------------------------------------------ */
struct SGML_CLOSING_TAG                 /* document instance                */
{
  struct SGML_TAG_NAME *tag_name;
  struct SGML_OPENING_TAG *open_tag;
} ;

/* ------------------------------------------------------------------------ */
struct SGML_NODE                        /* document instance: element       */
{
  int node_type;
  int status;
  int minimiziation;

  struct SGML_OPENING_TAG *opening_tag;
  void *content;
  struct SGML_CLOSING_TAG *closing_tag;
} ;

/* ------------------------------------------------------------------------ */
struct SGML_STACK
{
  struct SGML_STACK *prev;
  struct SGML_NODE **ptr;
} ;

/* ------------------------------------------------------------------------ */
struct SGML_BUILDUP
{
                                        /* temporary storage areas          */
  char bl1 [TMP_BL_SIZE];               /* tmp block                        */
  int bl1_cnt;

  struct ARRAY_CONTROL *tokens;         /* tmp tokens                       */
  int token_type;                       /* seek SGML_tokt_*                 */

  struct SGML_NODE *document;           /* begin of the currently           */
                                        /* parsed instance                  */

                                        /* parser meta status               */
  struct SGML_NODE **append;
  struct SGML_STACK *stack;
  int stack_size;

                                        /* document type definition         */
  struct YTREE *defined_element_names;  /* declared elements                */
  struct YTREE *defined_entity_names;   /* declared entities                */
  struct YTREE *defined_par_entity_names;/*declared parameter entities      */
  struct YTREE *defined_notation_names; /* declared notation names          */

                                        /* statistics                       */
  struct YTREE *element_names;
  struct YTREE *entity_names;
  struct YTREE *par_entity_names;
} ;

/* macros: ---------------------------------------------------------------- */
#define sgml_new_element_declaration() \
  ((struct SGML_ELEMENT_DECLARATION *) \
      calloc (sizeof (struct SGML_ELEMENT_DECLARATION), 1))

#define sgml_new_content_model() \
  ((struct SGML_CONTENT_MODEL *) \
      calloc (sizeof (struct SGML_CONTENT_MODEL), 1))

#define sgml_new_attlist_decl() \
  ((struct SGML_ATTLIST_DECL *) \
      calloc (sizeof (struct SGML_ATTLIST_DECL), 1))

#define sgml_new_attdecl() \
  ((struct SGML_ATTRIBUTE_DECLARATION *) \
      calloc (sizeof (struct SGML_ATTRIBUTE_DECLARATION), 1))

#define sgml_new_entity_declaration() \
  ((struct SGML_ENTITY_DECLARATION *) \
      calloc (sizeof (struct SGML_ENTITY_DECLARATION), 1))

#define sgml_new_attribute() \
  ((struct SGML_ATTRIBUTE_LIST *) \
      calloc (sizeof (struct SGML_ATTRIBUTE_LIST), 1))

/* prototypes: ------------------------------------------------------------ */
/* 0301 */ struct RDTP_GENERATOR *sgml_setup_parser (char *name);
/* 0302 */ int sgml_nop (struct RDTP_THREAD *thr, int ch);
/* 0303 */ int sgml_error (void *thrp, int ch);
/* 0304 */ int sgml_name_begin (void *thrp, int ch);
/* 0305 */ int sgml_collect (void *thrp, int ch);
           int sgml_collect2 (struct RDTP_THREAD *thr, int ch);
           int sgml_collect3 (struct RDTP_THREAD *thr, int ch);
           int sgml_collect3b (struct RDTP_THREAD *thr, int ch);
           int sgml_collect4 (struct RDTP_THREAD *thr, int ch);
           int sgml_collect5 (struct RDTP_THREAD *thr, int ch);
/* 0306 */ int sgml_name_end (struct SGML_BUILDUP *sgml_structure,
             int ch, struct YTREE **name_table);
/* 0307 */ int sgml_print_statistics (struct RDTP_THREAD *thr);
/* 0308 */ int sgml_print_name_statistics (long cmd_info, void *thr_info);
/* 0309 */ int sgml_element_name_end (void *thrp, int ch);
/* 0310 */ int sgml_entity_name_end (struct RDTP_THREAD *thr, int ch);
/* 0311 */ struct SGML_BUILDUP *sgml_initialize_buildup (void);
/* 0312 */ int sgml_flush_buffer (struct SGML_BUILDUP *rtf);
/* 0313 */ struct SGML_TAG_NAME *sgml_new_element_name (
             struct SGML_BUILDUP *ctx, char *name);
/* 0314 */ int sgml_new_element (struct RDTP_THREAD *thr, int ch);
/* 0315 */ int sgml_declaration (struct RDTP_THREAD *thr, int ch);
/* 0316 */ int sgml_decl_token_beg (struct RDTP_THREAD *thr, int ch,
             int token_type);
           int sgml_decl_literal_beg (struct RDTP_THREAD *thr, int ch);
           int sgml_decl_sqs_beg (struct RDTP_THREAD *thr, int ch);
           int sgml_decl_dqs_beg (struct RDTP_THREAD *thr, int ch);
           int sgml_decl_num_beg (struct RDTP_THREAD *thr, int ch);
/* 0317 */ int sgml_decl_token_end (struct RDTP_THREAD *thr, int ch);
           int sgml_decl_col_token_end (struct RDTP_THREAD *thr, int ch);
/* 0318 */ struct SGML_TOKEN *sgml_tokenizer (char *str, int type);
           void sgml_destroy_token (void *pl);
           void sgml_free_token (struct SGML_TOKEN *token);
/* 0319 */ int sgml_tokenize_symbol (struct RDTP_THREAD *thr, int ch,
             int token_type);
           int sgml_decl_symbol (struct RDTP_THREAD *thr, int ch);
           int sgml_single_dash (struct RDTP_THREAD *thr, int ch);
           int sgml_single_dash_gbeg (struct RDTP_THREAD *thr, int ch);
           int sgml_single_pct (struct RDTP_THREAD *thr, int ch);
/* 0320 */ int sgml_par_ent_beg (struct RDTP_THREAD *thr, int ch);
           int sgml_par_ent_end (struct RDTP_THREAD *thr, int ch);
/* 0321 */ int sgml_declaration_done (struct RDTP_THREAD *thr, int ch);
           int sgml_declaration_done2 (struct RDTP_THREAD *thr, int ch);
/* 0322 */ struct SGML_TAG_NAME *sgml_add_element (struct SGML_BUILDUP *sb,
             char *element);

/* 0341 */ struct SGML_OPENING_TAG *sgml_new_opening_tag (
             struct SGML_BUILDUP *sb, char *name);
/* 0342 */ struct SGML_ATTRIBUTE_LIST *sgml_add_attribute (
             struct SGML_OPENING_TAG *ot, char *name, char *value);
#ifdef _FILE_DEFINED
/* 0343 */ int sgml_diag_tag (FILE *fo, struct SGML_OPENING_TAG *ot);
#endif /* _FILE_DEFINED */
/* 0344 */ int sgml_destroy_attribute (struct SGML_ATTRIBUTE_LIST *av);
/* 0345 */ int sgml_destroy_tag (struct SGML_OPENING_TAG *ot);
/* 0346 */ char *sgml_tag_to_string (struct SGML_OPENING_TAG *ot,
             char *buffer, int max_size, int extra);
/* 0347 */ int sgml_space_required (struct SGML_OPENING_TAG *ot);
/* 0348 */ struct SGML_ATTRIBUTE_LIST *sgml_add_long_attribute (
             struct SGML_OPENING_TAG *ot, char *name, long value);

/* 0403 */ int sgml_can_be_minimized (char *str);
           int sgml_can_be_minimized_tok (struct SGML_TOKEN *tok);
           int sgml_element_declaration (struct SGML_BUILDUP *sb,
             struct ARRAY_CONTROL *token_list, int what);
#ifdef _FILE_DEFINED
/* 0413 */ int sgml_print_element_declaration (FILE *fo,
             struct SGML_ELEMENT_DECLARATION *ed);
           int sgml_print_attlist_declaration (FILE *fo,
             struct SGML_ATTLIST_DECL *attl);
           int sgml_print_attribute_declaration (FILE *fo,
             struct SGML_ATTRIBUTE_DECLARATION *attdecl);
#endif /* _FILE_DEFINED */

/* 0421 */ struct ARRAY_CONTROL *sgml_get_name_or_group (
             struct ARRAY_CONTROL *token_list, int group_required);
/* 0422 */ struct SGML_CONTENT_MODEL *sgml_get_content_model (
             struct ARRAY_CONTROL *token_list);
/* 0423 */ int sgml_get_declared_value_code (char *str);
           struct SGML_ATTLIST_DECL *sgml_get_attlist (
             struct ARRAY_CONTROL *token_list);

#endif /* __GG_rdtp03__ */
