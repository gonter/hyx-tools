/*
 *  FILE %ds/rdtp/rdtp0201.c
 *
 *  restructured dynamic text parser: RTF processor
 *
 *  written:       1996-04-01
 *  latest update: 1997-01-15 10:52:37
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <stdlib.h>
#include <gg/rdtp.h>
#include <gg/rdtp01.h>
#include <gg/rdtp02.h>

/* ------------------------------------------------------------------------ */
static char
  _[]=                  "?",
  collect[]=            "collect",
  ignore[]=             "ignore",               /* uninterpreted chars      */
  literal[]=            "literal",
  new_group[]=          "new_group",
  new_control[]=        "new_control",
  close_group[]=        "close_group",
  cmd_name[]=           "cmd_name",
  hex[]=                "hex",
  par_end[]=            "par_end";

/* ------------------------------------------------------------------------ */
static struct RDTP_STATIC_STATE_TABLE rtf_states [] =
{
/*.             .               .       .       .               .           */
{ "START",      "START",        0x20,   0xFF,   collect,      rtf_nop     },
{ "START",      "START",        0x09,   0x09,   collect,      rtf_nop     },
{ "START",      "START",        0x0A,   0x0A,   ignore,       rtf_nop     },
{ "START",      "START",        0x0C,   0x0C,   ignore,       rtf_nop     },
{ "START",      "START",        0x0D,   0x0D,   ignore,       rtf_nop     },
{ "START",      "START",        '{',    '{',    new_group,    rtf_nop     },
{ "START",      "START",        '}',    '}',    close_group,  rtf_nop     },
{ "START",      "Ctrl",         '\\',   '\\',   new_control,  rtf_nop     },

{ "Ctrl",       "START",        '\\',   '\\',   literal,                rtf_nop                 },
{ "Ctrl",       "START",        '{',    '{',    literal,                rtf_nop                 },
{ "Ctrl",       "START",        '}',    '}',    literal,                rtf_nop                 },
{ "Ctrl",       "START",        '*',    '*',    "comment",              rtf_nop                 },
{ "Ctrl",       "START",        ':',    ':',    "index item?",          rtf_nop                 },
{ "Ctrl",       "START",        '~',    '~',    "fixed space",          rtf_nop                 },
{ "Ctrl",       "START",        '-',    '-',    "nonrquired hyphen",    rtf_nop                 },
{ "Ctrl",       "START",        '_',    '_',    "nobreaking hyphen",    rtf_nop                 },
{ "Ctrl",       "START",        '|',    '|',    "formula begin",        rtf_nop                 },
{ "Ctrl",       "HEX1",         '\'',   '\'',   hex,                    rtf_nop                 },
{ "Ctrl",       "Cmd",          'A',    'Z',    cmd_name,               rtf_cmd_name_begin      },
{ "Ctrl",       "Cmd",          'a',    'z',    cmd_name,               rtf_cmd_name_begin      },

{ "Cmd",        "Cmd",          'A',    'Z',    cmd_name,     rtf_cmd_name              },
{ "Cmd",        "Cmd",          'a',    'z',    cmd_name,     rtf_cmd_name              },
{ "Cmd",        "Par",          '0',    '9',    _,            rtf_cmd_name_end          },
{ "Cmd",        "Par",          '-',    '-',    _,            rtf_cmd_name_end          },
{ "Cmd",        "Ctrl",         '\\',   '\\',   new_control,  rtf_cmd_name_end          },
{ "Cmd",        "START",        '}',    '}',    close_group,  rtf_cmd_name_end          },
{ "Cmd",        "START",        '{',    '{',    new_group,    rtf_cmd_name_end          },
{ "Cmd",        "START",        '$',    '$',    _,            rtf_cmd_name_end          },
{ "Cmd",        "START",        ' ',    ' ',    _,            rtf_cmd_name_end          },
{ "Cmd",        "START",        '\t',   '\t',   _,            rtf_cmd_name_end          },
{ "Cmd",        "START",        0x0A,   0x0A,   _,            rtf_cmd_name_end          },
{ "Cmd",        "START",        0x0D,   0x0D,   _,            rtf_cmd_name_end          },
{ "Cmd",        "START",        ';',    ';',    _,            rtf_cmd_name_end          },

{ "Par",        "START",        0x20,   0x7F,   collect,      rtf_nop     },
{ "Par",        "Par",          '0',    '9',    _,            rtf_nop     },
{ "Par",        "Ctrl",         '\\',   '\\',   new_control,  rtf_nop     },
{ "Par",        "START",        '}',    '}',    close_group,  rtf_nop     },
{ "Par",        "START",        '{',    '{',    new_group,    rtf_nop     },
{ "Par",        "START",        ' ',    ' ',    par_end,      rtf_nop     },
{ "Par",        "START",        '\t',   '\t',   par_end,      rtf_nop     },
{ "Par",        "START",        0x0A,   0x0A,   par_end,      rtf_nop     },
{ "Par",        "START",        0x0D,   0x0D,   par_end,      rtf_nop     },
{ "Par",        "START",        ';',    ';',    par_end,      rtf_nop     },

{ "HEX1",       "HEX2",         '0',    '9',    _,            rtf_nop     },
{ "HEX1",       "HEX2",         'a',    'f',    _,            rtf_nop     },
{ "HEX1",       "HEX2",         'A',    'F',    _,            rtf_nop     },

{ "HEX2",       "START",        '0',    '9',    _,            rtf_nop     },
{ "HEX2",       "START",        'a',    'f',    _,            rtf_nop     },
{ "HEX2",       "START",        'A',    'F',    _,            rtf_nop     },

{ (char *) 0, (char *) 0, 0, 0, (char *) 0, (RDTP_state_transition *) 0     }
} ;

/* ------------------------------------------------------------------------ */
struct RDTP_GENERATOR *rtf_setup_parser (char *name)
{
  struct RDTP_GENERATOR *gen= (struct RDTP_GENERATOR *) 0;

  if ((gen= calloc (sizeof (struct RDTP_GENERATOR), 1))
      != (struct RDTP_GENERATOR *) 0
     )
  {
    rdtp_load_static_table (gen, rtf_states);
    gen->generator_name= strdup (name);
    gen->start_state= strdup ("START");

    gen->method_for_undefined_state= rtf_error;
    gen->method_for_undefined_input= rtf_error;
  }

  return gen;
}
