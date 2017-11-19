/*
 *  FILE %ned/00/ned0011.c
 *
 *  default values and setup
 *
 *  written:       1996-05-16
 *  latest update: 2001-02-11 22:09:02
 *  $Id: ned0011.c,v 1.6 2001/02/12 00:03:16 gonter Exp $
 *
 */

#include <stdio.h>
#include <string.h>
#include "ed.h"
#include "proto.h"

#ifdef MSDOS
#define _DEF_HORIZ_SCROLL 1
#define _DEF_VERT_SCROLL  1
#else
#define _DEF_HORIZ_SCROLL 1
#define _DEF_VERT_SCROLL  1
#endif

/* ------------------------------------------------------------------------ */
/* normal editing and everything                                            */
int default_edit_mode= 0x00;
int default_tag_display_mode= WCTDM_normal;

int global_file_format= FMT_ASCII;
int default_bin_eoln= 0x0A;             /* End-Of-Line Code bei binaer      */
int default_bin_llng= LINE_LNG_TXT;     /* Laenge von binaeren Zeilen       */
int default_cross_ref_fmt= FMT_SGML;
int default_cross_ref_local= 0;
char *default_cross_ref_template;
char *default_template_frame;
char *default_start_frame;
char *default_undef_frame;
char *default_cross_ref_prefix;
int default_cross_ref_to_lower= 1;

int GHYOPT_close_on_logic_link= 1;

/* HELP subsystem: -------------------------------------------------------- */
char *default_help_cluster;
char *default_help_open_file;
char *default_help_jump_to_line;
char *default_help_rename_frame;
char *default_help_cross_ref;
char *default_help_prompt_attrib;

/* HUH? What's that?? */
#define URXN 256
char default_urxn [URXN];
int urxn_size= URXN;

int word_wrap_count= LINE_LNG_TXT;      /* automatischer Zeilenumbruch      */

/* number of chars to scroll horizontally and vertically                    */
int ned_horizontal_scroll_count= _DEF_HORIZ_SCROLL;
int ned_vertical_scroll_count=   _DEF_VERT_SCROLL;
int ned_tabstop=             8; /* number of chars to expand one TAB max.   */

/* ------------------------------------------------------------------------ */
int ned_0011 ()
{
  int i;

  default_cross_ref_template=   strdup ("$$crf");
  default_template_frame=       strdup ("$$template");
  default_start_frame=          strdup ("$$root");
  default_undef_frame=          strdup ("$$undef");
  default_cross_ref_prefix=     strdup ("$");

  default_help_cluster=         strdup ("%cl1");
  default_help_open_file=       strdup ("open_file");
  default_help_jump_to_line=    strdup ("jump_to_line");
  default_help_rename_frame=    strdup ("rename_frame");
  default_help_cross_ref=       strdup ("cross_ref");
  default_help_prompt_attrib=   strdup ("attrib"); /* T2D */

  for (i= 0; i < URXN; i++) default_urxn[i]= 'x';

  return 0;
}

/* ------------------------------------------------------------------------ */
int check_urxn (char *id)
{
  int i, err=0;

  for (i= 0; i < URXN; i++)
  {
    if (default_urxn[i] != 'x') err++;
  }

  if (err > 0)
  {
    printf ("------------- fence '%s' err=%d --------\n", id, err);
    dump (stdout, &default_cross_ref_template, urxn_size+44);
    for (i= 0; i < URXN; i++) default_urxn[i]= 'x';
  }

  return err;
}

/* ------------------------------------------------------------------------ */
int ned_init_virtual_filename_table (void)
{
  _read_logic_filename_table ("/usr/local/lib/ned/ned.lp", (char *) 0, 1);
  read_logic_filename_table ((char *) 0, 1); /* get the entry from etc */
  /*************** ~/etc/ned.lp is read twice!!! ******************
  tmp_ptr= translate_logic_filename ("~/etc/ned.lp");
  _read_logic_filename_table (tmp_ptr, (char *) 0, 1);
  free (tmp_ptr);
  ****************************************************************/

  return 0;
}
