/*
 *  $Id: ned00.c,v 1.20 2003/04/28 02:09:28 gonter Exp $
 *  FILE %ned/ned00.c
 *
 *  ned ... 'new editor'; a Full Screen Editor
 *  ned - main file
 *
 *  hot spots in this file:
 *  -  version number
 *  -  HELP
 *  -  main
 *
 *  written:       1987 03 20: Uebernahme von med.c
 *                 1987 04 08: Modularisierung: ned.c: ned0.c - ned6.c
 *                 1990 01 20: weitere Modularisierung; Streamlining
 *                 1991 05 25: Revision; Streamlining
 *                 1994-10-16: viewer only configuration
 *  latest update: 2002-06-08 12:36:36
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include "ed.h"
#include "message.h"
#include <gg/window.h>
#include <gg/filename.h>
#include <gg/keys.h>
#include <gg/strings.h>
#include <gg/dpp.h>
#include <gg/hyx.h>
#include <contrib/md5gg.h>
#ifdef MSDOS
#include <dos.h>
#include <conio.h>
#include <gg/dirty.h>
#define PATH_LENGTH 128
#else
#define PATH_LENGTH 1024
#endif
#ifdef USE_MOUSE
#include <gg/maus.h>
#endif
#include "edctx.h"
#include "proto.h"

#ifdef MSDOS
#define MAKE_WINDOW_FRAMES
#endif

#define ETC(x) set_etc_filename ((char *) 0, (x))
/* NOTE: the returned string is malloc()'ed */

/* ------------------------------------------------------------------------ */
extern int W_TEXT_MAX_X;
extern int W_TEXT_MAX_Y;
extern int global_file_format;
extern int akt_buttons;
extern int akt_page;
extern int word_wrap_count;
extern int default_edit_mode;
extern int default_tag_display_mode;
extern int default_bin_eoln;
extern int default_bin_llng;
extern int default_cross_ref_fmt;
extern int default_cross_ref_local;
extern int ned_werr_dont_complain;
extern char *default_cross_ref_prefix;
extern int default_cross_ref_to_lower;
extern char *default_start_frame;
extern char *default_template_frame;
extern char *default_undef_frame;
extern char stp_fnm [];
extern struct WINDOWCTRL *aw, *windows;
extern struct FILECTRL *files;
extern int oper_level;
extern int NED_TEXT_MAX_X, NED_TEXT_MAX_Y;

/* ------------------------------------------------------------------------ */
int cdecl main (int argc, char *argv []);
void setup_screen (void);

/* ------------------------------------------------------------------------ */
#ifdef USE_TCL
#ifdef USE_TK
static char *tcl_rc_names []=
{
  "~/.ned/tk.rc",
  "/usr/local/lib/ned/tk.rc",
  (char *) 0
} ;
#else
static char *tcl_rc_names []=
{
  "~/.ned/tcl.rc",
  "/usr/local/lib/ned/tcl.rc",
  (char *) 0
} ;
#endif /* !USE_TK */
static char *tcl_glib= "/usr/local/lib/ned";
#endif /* USE_TCL */

extern struct NED_CONTEXT *ned_main_context;

/* ------------------------------------------------------------------------ */
#define STDHLP stdout
static char *HELP [] =
{
  "USAGE: ned ([-opt]* [<filename>]*)*\n",
  "hypertext: ned -hy <cluster>\n",
  "options:\n",
  "  +<n> ... line number in following file, overrides ftr info\n",
  "  :<str> ... activate tag\n",
  "  -- all remaining arguments are filenames\n",
  "  -h .. hypertext mode\n",
  "  -y .. SGML mode\n",
  "  -x<fr> .. define start frame (hypertext)\n",
  "  -m<fr> .. define start frame (hypertext) with MD5 transformation\n",
  "  -$[<crf>] .. cross reference activation (hypertext)\n",
  "  -s[<fnm>] .. define setup file [DEF: none; ned.stp]\n",
  "  -t .. text mode [DEF]\n",
  "  -b .. binary mode\n",
  "  -bl[<LLNG>] .. line length; [DEF: 70]\n",
  "  -bc[<EOLN>] .. EOLN-char; [DEF: none]\n",
  "  -D\"<num> <str>\" .. define key sequence macro\n",
#ifdef USE_TCL
  "  -e<str> .. evaluate Tcl string\n",
  "  -z<fnm> .. run Tcl File\n",
  "  -T\"<num> <str>\" .. define Tcl macro\n",
#ifdef USE_TK
  "  -S<fnm> .. read TCL setup file [DEF: ~/.ned/tk.rc]\n",
#else
  "  -S<fnm> .. read TCL setup file [DEF: ~/.ned/tcl.rc]\n",
#endif /* !USE_TK */
#endif /* USE_TCL */
  "  -C<clnm> ... add cross reference cluster name\n",
  "  -F<fnm>  ... add feature table name\n",
  "  -:<fnm>  ... add tags table name\n",
  "  -I<clnm> ... add library cluster name\n",
  "  -J<clnm> ... add thesaurus cluster name\n",
  "  -L<clnm> ... add lexicon cluster name\n",
  "  -1 ... context items following are added to the top of the list\n",
  "  -E .. edit mode [DEF]\n",
  "  -R .. read only mode\n",
  "  -v .. start in vi mode\n",
  "  -w<cnt> .. word wrap count [DEF: 32760]\n",
  "\n",
  "experimental features:\n",
  "  -Q ... show full tags\n",
  "  -c ... cross ref frames are processed as ASCII\n",
  "  -l ... create new cross ref frames locally\n",
  "  -V ... VKB mode, implies -Qclhy\n",  /* ??? virtual knowledge base ??? */
  "  -Z ... don\'t complain about unwritable files\n",
  "\n",
  "exotic features:\n",
  "  -p+ .. enable feature file [DEF]\n",
  "  -p- .. disable feature file\n",
  "  -f<fnm> .. name of feature file [DEF: extension .ftr]\n",
  "  -j .. generate journal file [DEF: don't make the journal]\n",
  "  -r .. recover using journal file\n",
  "  -o<level> .. define operation level [DEF: 0]\n",
#ifdef MSDOS
  "  -40 .. 40 char mode ) \n",
  "  -80 .. 80 char mode ) [DEF: 80 or actual text mode]\n",
#endif /* MSDOS */
  "\n",
  "(@)Aned 3.21.05 #D$2002-10-16  7:07:24\n",
  "\n",
#define REAL_AUTHOR
#include <gg/public.inc>
} ;
char NED_VERSION []= "3.21.05";

/* ------------------------------------------------------------------------ */
int main (int argc, char *argv [])
{
  int i, j;
  int argf= 0;                  /* 1 .. ? Files laut Argumentliste geladen  */
  int file_fmt= FMT_ASCII;      /* Festlegung von file_format               */
  int file_ty= FTY_PLAIN;       /* Normales File                            */
  int openf_flags= NED_OPENF_NO_REL_PATH;
  int filectrl_mode= 1;         /* 1 -> Default  Feature File               */
                                /* 2 -> selected Feature File               */
  int ffnum= 0;                 /* Adr. des Feature File Namens             */
  int jmp_line= -1;             /* directly jump to line number             */
  char *jmp_pattern= (char *) 0;/* pattern to search directly for           */
#ifdef __TRASH__
  struct WINDOWCTRL **wptr= &windows;
#endif /* __TRASH__ */
  int crf_flg= 0;               /* 1 -> cross reference mode                */
  char *tmp_ptr;                /* used for screen dimensions etc           */
  char *start_frame= default_start_frame;
  char *arg;
  int start_frame_search_mode= 0x0003;
  int do_load_start_frame= 1;
  int is_filename= 0;
  int ctx_at_top= 0;
  int special= 0;

#ifndef USE_TK
  signal (SIGINT, SIG_IGN);
#endif

  ned_0011 ();
  if ((ned_main_context= ned_create_context ())
         == (struct NED_CONTEXT *) 0
      || ned_default_context (ned_main_context) != 0
     )
  {
    fprintf (stderr, "can't create ned context!!\n");
    return 0;
  }
  ned_init_sym_bookmarks ();

  default_edit_mode= 0x00;      /* Festlegung von edit_mode                 */

  /* BEGIN initialize operational modes according to the program name ..... */
  arg= argv [0];
  if (strstr (arg, "hyxview") != (char *) 0
      || strstr (arg, "HYXVIEW") != (char *) 0
     )
  {
    file_ty= FTY_HYPER;
    file_fmt= FMT_SGML;
    openf_flags &= NED_OPENF_RST_FORMAT;
    openf_flags |= NED_OPENF_SGML | NED_OPENF_READ_ONLY;
    default_edit_mode |= /* EDIT_NOTOGGLE | */ EDIT_READ_ONLY;
  }
  else
  if (strstr (arg, "VIEW") != (char *) 0
      || strstr (arg, "view") != (char *) 0
     )
  {
    default_edit_mode |= EDIT_READ_ONLY;
    openf_flags |= NED_OPENF_READ_ONLY;
    vi_on ();
  }
  else
  if (strstr (arg, "VI") != (char *) 0
      || strstr (arg, "vi") != (char *) 0
     )
  {
    vi_on ();
    vi_mode ();
  }
  else
  if (strstr (arg, "PIN00") != (char *) 0
      || strstr (arg, "pin00") != (char *) 0
      || strstr (arg, "pico") != (char *) 0
     ) pico_mode ();
  /* END initialize operational modes according to the program name ....... */

  /* BEGIN interface initialization ....................................... */
#ifndef W_MODEL_TK
  w_init (0x0000);
  w_selpage (akt_page);
  w_cursoron ();
#endif /* !W_MODEL_TK */

#ifdef MSDOS
  set_cp (&tmp_ptr, 0, 0x40);
  W_TEXT_MAX_X= *((int *) (tmp_ptr+0x4A));
  W_TEXT_MAX_Y= (tmp_ptr [0x84] & 0x00FF)+1;
  /* Diese System Variable ist nur ab EGA aufwaerts definiert!            */
  /* daher werden unplausible Werte auf den Standard-Wert modifiziert.    */
  if (W_TEXT_MAX_Y < 20 || W_TEXT_MAX_Y > 61) W_TEXT_MAX_Y= 25;
  if (kbtype ()) { kbin_set_AT (); kbhit_set_AT (); }
#endif

  setup_screen ();
  save_message_line ();

#ifdef USE_MOUSE
  look1_for_maus ();
#endif
  /* END interface initialization ......................................... */

#ifndef MSDOS
  ned_init_virtual_filename_table ();

  /*** HUH? What's that?? */
  tmp_ptr= translate_logic_filename ("~/.ned/bookmarks/bmk");
  ned_load_bookmarks (tmp_ptr, "_default");
  free (tmp_ptr);
#endif /* !MSDOS */

  mac_clr ();                           /* Alle Makros loeschen             */
  setup_sgml_tag_descriptors (ETC ("sgmltags.def"));
  ned_read_setup (ETC ("nedglobl.stp"));
#ifdef USE_TCL
  ned_tcl_startup (tcl_rc_names, tcl_glib);
#endif /* USE_TCL */

  /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */
  for (i= 1; i < argc; i++)             /* evaluate command line arguments  */
  {
    arg= argv [i];

    if (is_filename) goto IS_FILENAME;

    if (arg [0] == '-')                 /* command line options             */
      switch (arg [1])
      {
        case 'R':                       /* Read Only Mode                   */
        case 'E':                       /* Edit Mode                        */
        case 't':                       /* Format Text                      */
        case 'y': case 'Y':             /* Format SGML                      */
        case 'h': case 'H':             /* Hypertext                        */
        case 'j':                       /* Jour File anlegen                */
        case 'r':                       /* Jour File lesen: RECOVER         */
        case 'Q':                       /* tag display full                 */
        case 'c':                       /* cross ref frames not in SGML     */
        case 'l':                       /* cross ref frames are local       */
        case 'v':                       /* VI mode                          */
        case 'V':                       /* VKB mode                         */
        case 'Z':                       /* dont complain about non-write    */
        case '1':                       /* add items to context at top      */

        for (j= 1; arg [j]; j++)
          switch (arg [j])
          {
            case 'R':                   /* Read Only Mode without toggle    */
              default_edit_mode |= EDIT_READ_ONLY;
              openf_flags |= NED_OPENF_READ_ONLY;
              break;
            case 'E':                   /* Edit Mode                        */
              default_edit_mode= 0x00;
              openf_flags &= ~NED_OPENF_READ_ONLY;
              break;
            case 't':                   /* file type is ASCII               */
              file_fmt= FMT_ASCII;
              openf_flags &= NED_OPENF_RST_FORMAT;
              break;
            case 'h': case 'H':         /* file type is Hypertext           */
              file_ty= FTY_HYPER;
              break;
            case 'y': case 'Y':         /* file format is SGML              */
              file_fmt= FMT_SGML;
              openf_flags &= NED_OPENF_RST_FORMAT;
              openf_flags |= NED_OPENF_SGML;
              break;
            case 'v':                   /* start in VI mode                 */
              vi_on ();
              break;
            case 'X':                   /* ignore, if in -hyx option        */
              start_frame_search_mode ^= 0x0002;
            case 'x':
              j++;
              goto FRAME_NAME;
            case 'j': case 'J':         /* Journal File anlegen             */
              p_open_jou_wr ();
              break;
            case 'r':                   /* Journal File lesen: RECOVER      */
              p_open_jou_rd ();
              break;
            case 'Q':
              default_tag_display_mode= WCTDM_show_full_tag;
              break;
            case 'Z':
              ned_werr_dont_complain= 1;
              break;
            case 'c':
              default_cross_ref_fmt= FMT_ASCII;
              break;
            case 'l':
              default_cross_ref_local= 1;
              break;
            case '1':
              ctx_at_top= 1;
              break;
            case 'V':                   /* VKB mode                         */
              file_ty= FTY_HYPER;
              file_fmt= FMT_SGML;
              openf_flags &= NED_OPENF_RST_FORMAT;
              openf_flags |= NED_OPENF_SGML;
              default_tag_display_mode= WCTDM_show_full_tag;
              default_cross_ref_fmt= FMT_ASCII;
              default_cross_ref_local= 1;
              default_cross_ref_prefix= (char *) 0;
              /** default_cross_ref_to_lower= 0; **/
              break;
            default: goto HLP;
          }
          break;

        case '-': /* all parameters after -- are file names */
          is_filename= 1;
          break;

        case 'p': case 'P': /* Pure Mode: Feature File ignored */
          filectrl_mode= (arg [2] == '+') ? 1 : 0;
          break;

        case 'f':               /* Feature File festlegen */
          if (arg [2] == 0) break;
          ffnum= i;
          filectrl_mode= 2;
          break;

#define ACTX(n) ned_add_context (ned_main_context, (n), arg+2, ctx_at_top)
        case 'C':
          ACTX (NED_CTXitem_crf);
          break;
        case 'F':
          ACTX (NED_CTXitem_feature_table);
          break;
        case ':':
          ACTX (NED_CTXitem_tag_file);
          break;
        case 'I':
          ACTX (NED_CTXitem_lib);
          break;
        case 'J':
          ACTX (NED_CTXitem_thesaurus);
          break;
        case 'L':
          ACTX (NED_CTXitem_lexicon);
          break;
#undef ACTX

        case 'D':
          mac_parse (arg+2, MPt_key_sequence);
          break;

#ifdef USE_TCL
        case 'T':
          mac_parse (arg+2, MPt_tcl);
          break;

        case 'e':
          mac_call_tcl (arg+2);
          break;

        case 'z':
          if (arg[2])
          {
            printf ("z: arg='%s'\n", arg+2);
            ned_tcl_run_file (arg+2);
          }
          else special= 1;
          break;
#endif /* USE_TCL */

#ifdef MSDOS
        case '4':
          w_init_mode (0x01, 0x0001);
          break;
        case '8':
          w_init_mode (0x03, 0x0001);
          break;
#endif

        case 'o': case 'O': /* Operation Level definieren  */
          if (arg [2] == 0) break;
          oper_level= (int) get_parameter_value (arg+2);
          break;

        case 'w': case 'W': /* word wrap */
          if (arg [2] == 0) break;
          word_wrap_count= (int) get_parameter_value (arg+2);
          break;

        case 's': case 'S': /* Setupfile einlesen */
          if (arg [2] != 0) strcpy (stp_fnm, arg+2);
          p_rdsetup ();
          break;

        case 'M':               /* define hypertext startframe as MD5 name  */
          start_frame_search_mode ^= 0x0002;

        case 'm':
          j= 2;
          if (arg [j] == 0) break;
          start_frame= MD5check_string ((unsigned char *) arg+j);
          break;

        case 'X':
          start_frame_search_mode ^= 0x0002;

        case 'x': /* define hypertext startframe */
          j= 2;
FRAME_NAME:
          if (arg [j] == 0) break;
          start_frame= arg+j;
          break;

        case '$':
          crf_flg= NED_CTXitem_crf;
          file_fmt= FMT_SGML;
          file_ty= FTY_HYPER;
          openf_flags &= NED_OPENF_RST_FORMAT;
          openf_flags |= NED_OPENF_SGML;
          ned_cross_ref (arg+1, 0, CRF_IN_CRF, CRF_GLOBAL_AND_LOCAL, 1);
          break;

        case 'b': case 'B':
          switch (arg [2])
          {
            case 'c': case 'C': /* Binaer: EOLN-Character */
              default_bin_eoln= (int) get_parameter_value (arg+3);
              break;
            case 'l': case 'L': /* Binaer: Zeilenlaenge */
              default_bin_llng= (int) get_parameter_value (arg+3);
              if (default_bin_llng <= 0) default_bin_llng= LINE_LNG_BIN;
              break;
            default:
              default_bin_eoln= 0;
              default_bin_llng= LINE_LNG_BIN;
              break;
          }
          file_fmt= FMT_BINARY;
          openf_flags &= NED_OPENF_RST_FORMAT;
          openf_flags |= NED_OPENF_BINARY;
          break;
          /* ANM: zur Verwendungsmoeglichkeit von -b und -t    */
          /*      siehe NEDNED.DOC unter 'ROTTEN' Tricks       */

HLP:
#include <gg/help.inc>
      }
    else
    if (arg [0] == '+')
    {
      switch (arg [1])
      {
        case 0:
        case '$':
          jmp_line= 32700;
          break;
        case '/':
        case '?':
          jmp_pattern= arg+1;
          break;
        default:
          jmp_line= (int) get_parameter_value (arg+1);
          break;
      }
    }
    else
    if (arg [0] == ':')
    {
      do_load_start_frame= 0;
      ex_tag_command (arg+1);
    }
    else
    { /* FILE NAME */
IS_FILENAME:
     switch (special)
     {
        case 1:
          ned_tcl_run_file (arg);
          argf++;
          break;
        default:
      if (file_ty == FTY_HYPER)
      { /* Hypertext Files */
        ned_activate_cluster (arg);
      }
      else
      { /* normale Files */ /* 06/ned0610e.c */

        if (ned_open_file_2 ((struct WINDOWCTRL *) 0, arg, openf_flags) == 0)
        {
          argf++;

          ned_jmp_complex (aw, jmp_line, jmp_pattern);

          jmp_pattern= (char *) 0;
          jmp_line= -1;
        }
#ifdef __TRASH__
        struct FILECTRL *fptr;
        struct WINDOWCTRL *w_new;
        char *r_fnm;
        char *v_fnm;

        if (find_file (arg, (char *) 0, &r_fnm, &v_fnm)== -1)
        {
          argf++;
          if ((w_new= ned_create_window_pair ()) == (struct WINDOWCTRL *) 0)
          {
            ned_error_message (ERR_OPEN_WDW);
            continue;
          }

#ifdef USE_TK
          ned_tk_associate_window (w_new);
#endif /* USE_TK */

          *wptr= w_new;
          w_new->prev= aw;
          aw= *wptr;
          wptr= &aw->next;

          if ((fptr= file_alloc ()) == (struct FILECTRL *) 0)
          {
            ned_error_message (ERR_OPEN_FILE);
            continue;
          }

          /* GET_FILENAME */
          fptr->FC_links= 1;
          aw->WC_title_short= FC_setup_filenames (fptr, r_fnm,
              (filectrl_mode == 2) ? &argv [ffnum][2] : (char *) 0);
#ifdef USE_TK
          ned_tk_set_window_name (aw, aw->WC_title_short);
#endif /* USE_TK */

          switch (filectrl_mode)
          {
            case 1:
              break;
            case 2:
              filectrl_mode= 0;
              break;
            default:
              fptr->FC_fnm_ftr [0]= 0; /* not so neat ... */
              break;
          }

          if (files != (struct FILECTRL *) 0)
          {
            files->FC_prev= fptr;
            fptr->FC_next= files;
          }

          aw->file_or_frame= files= fptr;
          aw->file_type= FTY_PLAIN;
          aw->WC_edit_mode= default_edit_mode;/* ggf. Read Only Flag          */
          aw->file_format= file_fmt;    /* Binary/ASCII/SGML...             */
          aw->bin_eoln= eoln;           /* End-Of-Line Code                 */
          aw->bin_llng= bin_x_llng;     /* Laenge von binaeren Zeilen       */

          s_fget (aw);
          winstack_push (aw);

          ned_jmp_complex (aw, jmp_line, jmp_pattern);

          jmp_pattern= (char *) 0;
          jmp_line= -1;

          take_history_notes (aw);
        }
#endif /* __TRASH__ */
       }
     }
     special= 0;
    } /* FILE NAME */
  }                                     /* Ende der Parameterauswertung     */

  global_file_format= file_fmt;
#ifdef MSDOS
  memorize_window_mode ();
#endif /* MSDOS */

  /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
  if (argf)
  {
#ifndef USE_TK
    if (argf == 2) q_wdwsize ('-');
#endif /* !USE_TK */
  }
  else
  {
    if ((!crf_flg || windows == (struct WINDOWCTRL *) 0)
        && do_load_start_frame
       )
    {
      struct CLUSTERCTRL *cl_list;
      int is_default= 0;

      if ((cl_list= ned_get_cluster_list ()) == (struct CLUSTERCTRL *) 0)
      {
        char *cl_name= (char *) 0;

        if (crf_flg)
          cl_name= ned_get_context (ned_main_context, crf_flg);
        if (cl_name == (char *) 0)
        {
          cl_name= "%cl0";
          is_default= 1;
        }

        cl_list= ned_activate_cluster (cl_name);
        file_fmt= FMT_SGML;
      }

      ned_activate_frame (cl_list, start_frame,
                          (struct WINDOWCTRL *) 0,
                          start_frame_search_mode, file_fmt,
                          default_template_frame,
                          default_undef_frame);

#ifdef USE_TK
      if (is_default) ned_tk_start_mode (aw);
#endif /* USE_TK */
    }
  }

  if ((aw= windows) == (struct WINDOWCTRL *) 0)
  {
    if (do_load_start_frame == 0) return 0;
    goto HLP;
  }

#ifdef USE_MOUSE
  look2_for_maus ();
#endif

  if (akt_page != aw->page) w_selpage (akt_page= aw->page);
  wda_setup ();
  show_buttons (aw);

#ifdef EXPER
  NEDa1_interpreter ();
#else
  NED_interpreter ();
#endif
  return 0;
}

/* ------------------------------------------------------------------------ */
void setup_screen (void)
{
  NED_TEXT_MAX_X= W_TEXT_MAX_X;
  NED_TEXT_MAX_Y= W_TEXT_MAX_Y;    /* ####### test: buttons ###### */
}
