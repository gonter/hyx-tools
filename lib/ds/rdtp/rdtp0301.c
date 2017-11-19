/*
 *  FILE %ds/rdtp/rdtp0301.c
 *
 *  restructured dynamic text parser
 *  SGML concrete syntax
 *
 *  written:       1996-04-02
 *  latest update: 1997-01-15 10:55:48
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <stdlib.h>
#include <gg/rdtp.h>
#include <gg/rdtp01.h>
#include <gg/rdtp03.h>

/* ------------------------------------------------------------------------ */
static char
  _[]=                  "?",
  collect[]=            "collect",
  tagging[]=            "tagging",
  entity[]=             "entity",
  test_nonsense[]=      "nonsense";

/* ------------------------------------------------------------------------ */
static struct RDTP_STATIC_STATE_TABLE sgml_states [] =
{
/*.             .               .       .       .               .                       */
{ "START",      "START",        0x20,   0x7F,   collect,        sgml_collect            },
{ "START",      "START",        0x09,   0x0D,   collect,        sgml_collect            },
{ "START",      "TAGGING",      '<',    '<',    tagging,        sgml_new_element        },
{ "START",      "ENTITYBEG",    '&',    '&',    entity,         sgml_new_element        },

{ "TAGGING",    "START",        0x20,   0x20,   collect,        sgml_collect2           }, /* barely legal SGML */
{ "TAGGING",    "START",        0x09,   0x0D,   collect,        sgml_collect2           }, /* barely legal SGML */
{ "TAGGING",    "DEF",          '!',    '!',    _,              sgml_nop                },
{ "TAGGING",    "PI",           '?',    '?',    _,              sgml_nop                },
{ "TAGGING",    "TAG",  /*HYX*/ ':',    ';',    collect,        sgml_name_begin         },
{ "TAGGING",    "TAG",          'A',    'Z',    collect,        sgml_name_begin         },
{ "TAGGING",    "TAG",          'a',    'z',    collect,        sgml_name_begin         },
{ "TAGGING",    "TAGEND",       '/',    '/',    collect,        sgml_name_begin         },

{ "TAG",        "TAG",          'A',    'Z',    collect,        sgml_collect            },
{ "TAG",        "TAG",          'a',    'z',    collect,        sgml_collect            },
{ "TAG",        "TAG",          '0',    '9',    collect,        sgml_collect            },
{ "TAG",        "TAG",          '-',    '-',    collect,        sgml_collect            },
{ "TAG",        "TAG",          '.',    '.',    collect,        sgml_collect            },
{ "TAG",        "START",        '>',    '>',    collect,        sgml_element_name_end       },
{ "TAG",        "TAG-PAR",      ' ',    ' ',    collect,        sgml_element_name_end       },
{ "TAG",        "TAG-PAR",      0x09,   0x0D,   collect,        sgml_element_name_end       },
{ "TAG",        "minimized",    '/',    '/',    collect,        sgml_element_name_end       },
{ "TAG",        "TAGGING",      '<',    '<',    collect,        sgml_element_name_end       },

{ "TAG-PAR",    "TAG-PAR",      0x09,   0x0D,   collect,      sgml_collect     },
{ "TAG-PAR",    "TAG-PAR",      0x20,   0x7F,   collect,      sgml_collect     },
{ "TAG-PAR",    "minimized",    '/',    '/',    collect,      sgml_nop     },
{ "TAG-PAR",    "START",        '>',    '>',    collect,      sgml_nop     },

{ "PI",         "PI",           0x20,   0x7F,   collect,      sgml_collect     },
{ "PI",         "START",        '>',    '>',    collect,      sgml_nop     },

{ "TAGEND",     "TAGEND",       0x20,   0x7F,   collect,      sgml_collect     },
{ "TAGEND",     "START",        '>',    '>',    collect,      sgml_nop     },

{ "minimized",  "minimized",    0x00,   0x7F,   collect,      sgml_collect     },
{ "minimized",  "START",        '/',    '/',    collect,      sgml_nop     },

{ "DEF",        "DEF2",         0x09,   0x0D,   _,            sgml_nop     },
{ "DEF",        "DEF2",         0x20,   0x20,   _,            sgml_nop     },
{ "DEF",        "DEF-Br1",      '[',    '[',    _,            sgml_nop     },
{ "DEF",        "DEF3",         'A',    'Z',    collect,      sgml_name_begin     },
{ "DEF",        "DEF3",         'a',    'z',    collect,      sgml_name_begin     },
{ "DEF",        "START",        '>',    '>',    _,            sgml_nop     },
{ "DEF",        "COM1a",        '-',    '-',    _,            sgml_nop     },

{ "DEF2",       "DEF2",         0x00,   0x7F,   collect,      sgml_collect     },
{ "DEF2",       "COM1a",        '-',    '-',    _,            sgml_nop     },
{ "DEF2",       "START",        '>',    '>',    _,            sgml_nop     },

/* comment in declaration part */
{ "COM1a",      "DEF2",         0x00,   0x7F,   _,            sgml_nop          },
                /* NOTE: just a single - doesn't mean anything, ERROR!      */
{ "COM1a",      "COM1b",        '-',    '-',    _,            sgml_nop          },
{ "COM1b",      "COM1b",        0x00,   0x7F,   collect,      sgml_collect      },
{ "COM1b",      "COM1c",        '-',    '-',    _,            sgml_nop          },
{ "COM1c",      "COM1b",        0x00,   0x7F,   collect,      sgml_collect      },
{ "COM1c",      "DEF2",         '-',    '-',    _,            sgml_nop          },

/* definition name                                                          */
/* e.g SGML, DOCTYPE, ELEMENT, ATTLIST, ENTITY, SHORTREF, USEMAP,           */
/*     NOTATION, LINKTYPE, LINK, USELINK, IDLINK                            */
{ "DEF3",       "DEF3",         'A',    'Z',    collect,      sgml_collect              },
{ "DEF3",       "DEF3",         'a',    'z',    collect,      sgml_collect              },
{ "DEF3",       "DECL",         ' ',    ' ',    collect,      sgml_declaration          },
                /* end of the declaration name */

/* the body of any declaration part                                         */
{ "DECL",       "DECL",         0x09,   0x0D,   _,              sgml_nop                },
{ "DECL",       "DECL",         ' ',    ' ',    _,              sgml_nop                },
{ "DECL",       "START",        '[',    '[',    _,              sgml_declaration_done   },
                /* NOTE: PUSH META STATE */
{ "DECL",       "DECL-TOK",     'A',    'Z',    _,              sgml_decl_literal_beg   },
{ "DECL",       "DECL-TOK",     'a',    'z',    _,              sgml_decl_literal_beg   },
{ "DECL",       "DECL-TOK",     '#',    '#',    _,              sgml_decl_literal_beg   },
                /* NOTE: this may be wrong */
{ "DECL",       "DECL-NUM",     '0',    '9',    _,              sgml_decl_num_beg       },
{ "DECL",       "DECL-SQS",     '\'',   '\'',   _,              sgml_decl_sqs_beg       },
{ "DECL",       "DECL-DQS",     '\"',   '\"',   _,              sgml_decl_dqs_beg       },
{ "DECL",       "DECL",         '?',    '?',    _,              sgml_decl_symbol        },
{ "DECL",       "DECL",         '|',    '|',    _,              sgml_decl_symbol        },
{ "DECL",       "DECL",         '(',    ',',    _,              sgml_decl_symbol        },
                /* NOTE: this is: ()*+, */
{ "DECL",       "DECL-DASH",    '-',    '-',    _,              sgml_nop                },
{ "DECL",       "DECL-PCT",     '%',    '%',    _,              sgml_nop                },
{ "DECL",       "START",        '>',    '>',    _,              sgml_declaration_done   },

/* token in a definition */
{ "DECL-TOK",   "DECL-TOK",     'A',    'Z',    collect,        sgml_collect              },
{ "DECL-TOK",   "DECL-TOK",     'a',    'z',    collect,        sgml_collect              },
{ "DECL-TOK",   "DECL-TOK",     '0',    '9',    collect,        sgml_collect              },
{ "DECL-TOK",   "DECL-TOK",     '-',    '-',    collect,        sgml_collect              },
                /* NOTE: this may be wrong! */
{ "DECL-TOK",   "DECL-TOK",     '_',    '_',    collect,        sgml_collect              },
{ "DECL-TOK",   "DECL-TOK",     '.',    '.',    collect,        sgml_collect              },
{ "DECL-TOK",   "DECL",         ' ',    ' ',    _,              sgml_decl_token_end       },
{ "DECL-TOK",   "DECL",         0x09,   0x0D,   _,              sgml_decl_token_end       },
{ "DECL-TOK",   "DECL",         '?',    '?',    _,              sgml_decl_token_end       },
{ "DECL-TOK",   "DECL",         '|',    '|',    _,              sgml_decl_token_end       },
{ "DECL-TOK",   "DECL",         '(',    ',',    _,              sgml_decl_token_end       },
                /* NOTE: this is: ()*+, */
{ "DECL-TOK",   "START",        '>',    '>',    _,              sgml_declaration_done2    },

/* a regular decimal number; used for ranks (?!?) */
{ "DECL-NUM",   "DECL-NUM",     '0',    '9',    collect,        sgml_collect              },
{ "DECL-NUM",   "DECL",         ' ',    ' ',    _,              sgml_decl_token_end       },
{ "DECL-NUM",   "DECL",         0x09,   0x0D,   _,              sgml_decl_token_end       },
{ "DECL-NUM",   "DECL",         '?',    '?',    _,              sgml_decl_token_end       },
{ "DECL-NUM",   "DECL",         '|',    '|',    _,              sgml_decl_token_end       },
{ "DECL-NUM",   "DECL",         '(',    ',',    _,              sgml_decl_token_end       },
                /* NOTE: this is: ()*+, */
{ "DECL-NUM",   "START",        '>',    '>',    _,              sgml_declaration_done2  },

/* single quoted string inside a declaration */
{ "DECL-SQS",   "DECL-SQS",      0x00,   0xFF,   _,             sgml_collect            },
{ "DECL-SQS",   "DECL",          '\'',   '\'',   _,             sgml_decl_col_token_end },

/* double quoted string inside a declaration */
{ "DECL-DQS",   "DECL-DQS",     0x00,   0xFF,   _,              sgml_collect            },
{ "DECL-DQS",   "DECL",         '\"',   '\"',   _,              sgml_decl_col_token_end },
{ "DECL-DQS",   "DECL-DQSBS",   '\\',   '\\',   _,              sgml_collect            },

/* backslash within double quoted string */
{ "DECL-DQSBS", "DECL-DQS",     0x00,   0xFF,   _,              sgml_collect           },

/* comment in declaration part */
{ "DECL-DASH",  "DECL",         0x09,   0x0D,   _,              sgml_single_dash        },
{ "DECL-DASH",  "DECL",         ' ',    ' ',    _,              sgml_single_dash        },
{ "DECL-DASH",  "DECL",         '(',    '(',    _,              sgml_single_dash_gbeg   },
{ "DECL-DASH",  "COM2b",        '-',    '-',    _,              sgml_nop                },
{ "COM2b",      "COM2b",        0x00,   0x7F,   _,              sgml_nop                },
{ "COM2b",      "COM2c",        '-',    '-',    _,              sgml_nop                },
{ "COM2c",      "COM2b",        0x00,   0x7F,   _,              sgml_nop                },
{ "COM2c",      "DECL",         '-',    '-',    _,              sgml_nop                },

/* a percent sign may be the beginning of a declaration entity              */
/* or the definition of such a beast                                        */
{ "DECL-PCT",   "DECL-ENT",     'A',    'Z',    collect,        sgml_par_ent_beg          },
{ "DECL-PCT",   "DECL-ENT",     'a',    'z',    collect,        sgml_par_ent_beg          },
{ "DECL-PCT",   "DECL",         0x09,   0x0D,   _,              sgml_single_pct           },
{ "DECL-PCT",   "DECL",         ' ',    ' ',    _,              sgml_single_pct           },

/* declaration entity */
{ "DECL-ENT",   "DECL-ENT",     'A',    'Z',    collect,        sgml_collect              },
{ "DECL-ENT",   "DECL-ENT",     'a',    'z',    collect,        sgml_collect              },
{ "DECL-ENT",   "DECL-ENT",     '0',    '9',    collect,        sgml_collect              },
{ "DECL-ENT",   "DECL-ENT",     '-',    '-',    collect,        sgml_collect              },
{ "DECL-ENT",   "DECL-ENT",     '.',    '.',    collect,        sgml_collect              },
{ "DECL-ENT",   "DECL",         ';',    ';',    collect,        sgml_par_ent_end          },

/* bracketed definitions */
{ "DEF-Br1",    "DEF-Br1",      0x09,   0x0D,   _,              sgml_nop                },
{ "DEF-Br1",    "DEF-Br1",      ' ',    ' ',    _,              sgml_nop                },
{ "DEF-Br1",    "DEF-Br2",      'a',    'z',    _,              sgml_name_begin         },
{ "DEF-Br1",    "DEF-Br2",      'A',    'Z',    _,              sgml_name_begin         },
{ "DEF-Br2",    "DEF-Br2",      'a',    'z',    _,              sgml_collect            },
{ "DEF-Br2",    "DEF-Br2",      'A',    'Z',    _,              sgml_collect            },
{ "DEF-Br2",    "DEF-Br2b",     0x09,   0x0D,   _,              sgml_element_name_end       },
                /* NOTE: not a tag name! */
{ "DEF-Br2",    "DEF-Br2b",     ' ',    ' ',    _,              sgml_element_name_end       },
{ "DEF-Br2",    "DEF-Brack",    '[',    '[',    _,              sgml_element_name_end       },
{ "DEF-Br2b",   "DEF-Brack",    '[',    '[',    _,              sgml_nop                },
{ "DEF-Brack",  "DEF-Brack",    0x00,   0xFF,   _,              sgml_collect            },
{ "DEF-Brack",  "DEF-Br3",      ']',    ']',    _,              sgml_nop                },
{ "DEF-Br3",    "DEF-Brack",    0x00,   0xFF,   _,              sgml_collect3           },
{ "DEF-Br3",    "DEFEND",       ']',    ']',    _,              sgml_nop                },
{ "DEFEND",     "DEF-Brack",    0x00,   0xFF,   _,              sgml_collect3b          },
{ "DEFEND",     "START",        '>',    '>',    _,              sgml_new_element        },

{ "ENTITYBEG",  "START",        0x00,   0xFF,   _,              sgml_new_element        },
{ "ENTITYBEG",  "CHARREF",      '#',    '#',    _,              sgml_nop                },
{ "ENTITYBEG",  "ENTITY",       'A',    'Z',    _,              sgml_name_begin         },
{ "ENTITYBEG",  "ENTITY",       'a',    'z',    _,              sgml_name_begin         },

{ "ENTITY",     "START",        0x00,   0xFF,   _,              sgml_new_element        },
{ "ENTITY",     "ENTITY",       'A',    'Z',    _,            sgml_collect     },
{ "ENTITY",     "ENTITY",       'a',    'z',    _,            sgml_collect     },
{ "ENTITY",     "ENTITY",       '0',    '9',    _,            sgml_collect     },
{ "ENTITY",     "ENTITY",       '.',    '.',    _,            sgml_collect     },
{ "ENTITY",     "ENTITY",       '-',    '-',    _,            sgml_collect     },
{ "ENTITY",     "START",        ';',    ';',    _,            sgml_entity_name_end    },

{ "CHARREF",    "CHARREF2",     '0',    '9',    _,            sgml_collect     },
{ "CHARREF",    "TAGGING",      '<',    '<',    _,            sgml_collect4    },
{ "CHARREF2",   "CHARREF2",     '0',    '9',    _,            sgml_collect     },
{ "CHARREF2",   "START",        ';',    ';',    _,            sgml_nop     },

{ (char *) 0, (char *) 0, 0, 0, (char *) 0, (RDTP_state_transition *) 0                 }
} ;

/* ------------------------------------------------------------------------ */
struct RDTP_GENERATOR *sgml_setup_parser (char *name)
{
  struct RDTP_GENERATOR *gen= (struct RDTP_GENERATOR *) 0;

  if ((gen= calloc (sizeof (struct RDTP_GENERATOR), 1))
      != (struct RDTP_GENERATOR *) 0
     )
  {
    rdtp_load_static_table (gen, sgml_states);
    gen->generator_name= strdup (name);
    gen->start_state= strdup ("START");

    gen->method_for_undefined_state= sgml_error;
    gen->method_for_undefined_input= sgml_error;
  }

  return gen;
}
