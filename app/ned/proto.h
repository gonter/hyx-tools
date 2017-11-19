/*
 *  FILE %ned/proto.h
 *
 *  function prototyping
 *
 *  written:       1987 09 07
 *                 1991 01 31: revision
 *  latest update: 2001-02-11 11:43:19
 *  $Id: proto.h,v 1.10 2010/05/04 02:47:07 gonter Exp $
 *
 */

#ifndef __NED_proto__
#define __NED_proto__

#include <gg/floskel.h>

/* *** TEMP *** ----------------------------------------------------------- */
#ifdef LCB_standard             /* redefined from ed.h !! */

#undef LCB_standard
#undef LCB_line_split
#undef LCB_line_join
#undef LCB_chg_wdw

#define LCB_line_split  0x0004  /* line was splitted at column              */
#define LCB_line_join   0x0008  /* line was joined at column                */
#define LCB_chg_wdw     0x0010  /* window was changed                       */
#define LCB_standard    0x001F
#endif /* LCB_standard */

#define LCB_DEBUG               /* 1997-07-27 11:19:09 */

#define NED_TMARK_INSERT2 4

#define NED_MARKER_BEG  '('
#define NED_MARKER_END  ')'

/* ------------------------------------------------------------------------ */
struct NED_BUFFER
{
  struct WINDOWCTRL *wptr;      /* File in dem Marker gueltig ist           */
  struct LINE *l_beg;           /* Zeile mit Marker                         */
  struct LINE *l_end;           /* Zeile mit Marker                         */
  int c_beg;                    /* Spalte des Markers                       */
  int c_end;                    /* Spalte des Markers                       */
  int blk_mode;                 /* block mode for line and char oriented b. */
} ;

/* ------------------------------------------------------------------------ */
/* Experimental, 1996-11-04 */
struct NED_FLC                          /* feature lookup cache             */
{
  char *ty;                             /* feature type                     */
  char *str;                            /* feature text                     */
} ;

#define new_ned_flc() ((struct NED_FLC *) calloc (sizeof (struct NED_FLC), 1))

/* methods: --------------------------------------------------------------- */
typedef int NED_field_editor_callback (char *edited_string, void *callback_data);
typedef void ned_primitive_function (void);

struct NED_FIELD_CONTEXT
{
  char *label;                          /* message text                     */

  char *buffer;                         /* string edit buffer and default   */
  int buffer_size;
  int buffer_mode;                      /* type of *buffer storage  (1)     */
#define FCbm_allocate   0               /* allocate buffer yourself         */
#define FCbm_volatile   1               /* allocate and copy buffer         */
#define FCbm_static     2               /* buffer can be used, is static    */
#define FCbm_dynamic    3               /* buffer can be used, is malloc'ed */

  NED_field_editor_callback *callback;
  void *callback_data;

  char *help_cluster;
  char *help_frame;
  char *help_file;
} ;

/* NOTES:                                                                   */
/* (1) the buffer in the structure should only be static or dynamic,        */
/*     the other modes are only used during setting up of the buffer        */

/* ------------------------------------------------------------------------ */
#ifdef __HPUX__
char *strdup (char *);  /* for some reasons, not defined under HP/UX        */
#endif

/* searching a better place for that ... (1995-10-28) */
#define NED_TK_GC_cursedText   0x0100
#define NED_TK_GC_normalText   0x0101
#define NED_TK_GC_StatusLine   0x0102
#define NED_TK_GC_markedText   0x0103

#define NED_TK_CMD_MOUSE_B2     1
#define NED_TK_CMD_WINS         2
#define NED_TK_CMD_MENU         3

/* read only version: ----------------------------------------------------- */
#ifdef NED_READ_ONLY
#  define ned_eval_hlink            ned_ro_eval_hlink
#  define ned_activate_cluster      ned_ro_activate_cluster
#  define ned_get_cluster_list      ned_ro_get_cluster_list
#  define ned_activate_frame        ned_ro_activate_frame
#endif /* NED_READ_ONLY */

/* TK Version: ------------------------------------------------------------ */
#ifdef USE_TK
#define ned_show_display_range ned_tk_show_display_range
int tk_resetcup (void);
#else
#define ned_show_display_range ned_ch_show_display_range
#endif /* USE_TK */

/* machine specific definitions: ------------------------------------------ */
#ifdef __SINIX__
char *strdup (char *s);
#endif

/* usefull macros: -------------------------------------------------------- */
#define get_coln(wc) ((wc)->cx + (wc)->hv - (wc)->ax)
#define REPEAT ((repeat) ? repeat : 1)

/* ------------------------------------------------------------------------ */
/* NED00 */ int main (int argc, char *argv[]);
/* NEDT3 */ void maus_setup (void);

/* 00.. ------------------------------------------------------------------- */
/* 0003  */ void maus_setup (void);
/* 0011  */ int ned_0011 (void);

/* 01.. ------------------------------------------------------------------- */
/* 0101  */ void wdw_rst (struct WINDOWCTRL *w);
/* 0102  */ int ned_w_cursor_up (register struct WINDOWCTRL *w, int num);
/* 0102p */ void ned_cursor_up (void);
/* 0102m */ void ned_vi_cursor_mid (void);
/* 0102v */ void ned_vi_cursor_top (void);
/* 0103  */ int ned_w_cursor_down (register struct WINDOWCTRL *w, int num);
/* 0103p */ void ned_cursor_down (void);
/* 0103v */ void ned_vi_cursor_bot (void);
/* 0104  */ void chk_updown (struct WINDOWCTRL *wc);

/* 0105  */ int ned_w_cursor_left (register struct WINDOWCTRL *w, int num);
/* 0105a */ int ned_q_cursor_left (struct WINDOWCTRL *w, int df);
/* 0105p */ void ned_cursor_left (void);
/* 0106  */ int ned_w_cursor_right (register struct WINDOWCTRL *w, int num);
/* 0106a */ int ned_q_cursor_right (struct WINDOWCTRL *w, int df);
/* 0106p */ void ned_cursor_right (void);

/* 0107  */ void p_word_left (void);
/* 0107b */ void p_word_left_2 (void);
/* 0108a */ void p_word_right_beg (void);
/* 0108b */ void p_word_right_end (void);
/* 0108c */ void p_word_right_beg_2 (void);
/* 0108d */ void p_word_right_end_2 (void);
/* 0109  */ void ned_wc_word_lr (struct WINDOWCTRL *wc, int mode);
#define JMPWRD_left_beg         1
#define JMPWRD_right_beg        2
#define JMPWRD_right_end        3
#define JMPWRD_left_beg_2       4
#define JMPWRD_right_beg_2      5
#define JMPWRD_right_end_2      6

/* 0110  */  void ned_w_page_up (struct WINDOWCTRL *wc, int part);
/* 0110a */ void ned_page_up (void);
/* 0110b */ void ned_half_page_up (void);
/* 0111  */  void ned_w_page_down (struct WINDOWCTRL *wc, int part);
/* 0111a */ void ned_page_down (void);
/* 0111b */ void ned_half_page_down (void);
/* 0112  */ void p_ctrlq (void);
/* 0112w */ void p_ctrlw (void);
/* 0113  */ void p_ctrlk (void);
/* 0114  */ void p_ctrlo (void);
/* 0115  */ void ned_ctrlp (void);
/* 0115b */ void ned_insert_special_char (int insert);
/* 0116  */ void p_funct (void);
/* 0117  */ void p_nl2 (void);
/* 0118  */ void p_nl (void);
/* 0119  */ void p_ax_lng (void);
/* 0119a */ void ned_w_jmp_in_line (struct WINDOWCTRL *wc,
              int mode, int offset);
#define NEDJMP_BOLN   1
#define NEDJMP_EOLN   2
#define NEDJMP_AXLNG  3
/* 0120  */ void ned_jmp_boln (void);
/* 0121  */ void ned_jmp_eoln (void);
/* 0122  */ void ned_del_char_right (void);
/* 0123  */ void ned_del_char_left (void);
/* 0124  */ void background (void);
/* 0124  */ void window_status (register struct WINDOWCTRL *w);
/* 0124  */ void back2ground (void);
/* 0124  */ void QQdeb (void);
/* 0125  */ int ned_show_display_range (struct WINDOWCTRL *w);
/* 0126  */ int q_isolate_word (char *wp, int max_lng, int charset,
                                int go_left);
/* 0127  */ int qq_isolate_word (char *wp, int max_lng, int charset,
                                 struct LINE *lp, int off, int llng,
                                 int go_left);
/* 0128  */ void p_ctrlu (void);
/* 0129  */ void p_split_join (void);
#ifdef _THE_FUNCTION
/* 0131  */ struct LINE *alloc_line (void);
#else
#define alloc_line() ((struct LINE *) calloc (sizeof (struct LINE), 1))
#endif
/* 0132  */ struct TXT *txch_alloc (int size, int ch);
/* 0133  */ struct TXT *tx_alloc (int size);
/* 0134  */ void strfill (char *s, int cnt, int ch);
#ifdef _THE_FUNCTION
/* 0135  */ struct WINDOWCTRL *wdw_alloc (void);
#else
#define wdw_alloc() ((struct WINDOWCTRL *) calloc (sizeof (struct WINDOWCTRL), 1))
#endif
#ifdef _THE_FUNCTION
/* 0136 */ struct FILECTRL *file_alloc (void);
#else
#define file_alloc() ((struct FILECTRL *) calloc (sizeof (struct FILECTRL), 1))
#endif
#ifdef _THE_FUNCTION
/* 0137  */ struct FEATURE *ned_feature_alloc (void);
#else
#define ned_feature_alloc() ((struct FEATURE *) calloc (sizeof (struct FEATURE), 1))
#endif
/* 0138  */ void ned_lines_free (struct LINE *lp);
/* 0138b */ void ned_feature_free (register struct FEATURE *f);
/* 0139  */ void txt_adj (int lng, struct TXT **tp);
/* 0140  */ void tx_free (struct TXT *tp);
/* 0141  */ void file_free (struct FILECTRL *fc);
/* 0142  */ int in_charset (int ch, int charset);

/* 02.. ------------------------------------------------------------------- */
/* 0201  */ /* N/A */
/* 0202  */ void setcup (register struct WINDOWCTRL *w);
/* 0203  */ void wd_displine (struct WINDOWCTRL *w, struct LINE *l_ptr,
                              int l_num, int xa, int xb);
/* 0204  */ void ned_display_window (struct WINDOWCTRL *w);
/* 0204b */ void wd_2setup (struct WINDOWCTRL *w, int xa, int ya,
                                                        int xb, int yb);
/* 0204c */ void ned_decorate_window (struct WINDOWCTRL *w);
/* 0205  */ /* N/A: void wd_setup (void); ... renamed! */
/* 0206  */ void wda_setup (void);
/* 0207  */ int wd_upscr (struct WINDOWCTRL *wc);
/* 0208  */ void p_upscr (void);
/* 0209  */ void wd_dnscr (struct WINDOWCTRL *wc);
/* 0210  */ void p_dnscr (void);
/* 0211  */ void ned_close_window (void);
/* 0211b */ int ned_w_close_window (register struct WINDOWCTRL *wc);
/* 0212  */ int p_wdwopen (void);
/* 0213a */ void p_wdwsize (void);
/* 0213b */ void q_wdwsize (int k);
/* 0213c */ void q2_wdwsize (struct WINDOWCTRL *w, int pos);
/* 0214  */ int ned_window_size (struct WINDOWCTRL *wc, int p, int f);
/* 0214  */ int ned_window_size_preset (int pax, int pay,
                                             int pbx, int pby);
/* 0215a */ struct WINDOWCTRL *ned_create_editor_window (void);
/* 0215b */ struct WINDOWCTRL *ned_create_feature_window (void);
/* 0215c */ struct WINDOWCTRL *ned_create_window_pair (void);
/* 0216  */ void p_wdwXup (void);
/* 0217  */ void p_wdwXdn (void);
/* 0218  */ void p_wdwXlt (void);
/* 0219  */ void p_wdwXrt (void);
/* 0220  */ void p_wdwAup (void);
/* 0221  */ void p_wdwAdn (void);
/* 0222  */ void p_wdwAlt (void);
/* 0223  */ void p_wdwArt (void);
/* 0224  */ void p_wdwBup (void);
/* 0225  */ void p_wdwBdn (void);
/* 0226  */ void p_wdwBlt (void);
/* 0227  */ void p_wdwBrt (void);
/* 0228  */ void wd_show_wdnr (int p, int x, int y, int c, int n);
/* 0229  */ void p_wdwfaecher (void);
/* 0230  */ int q_wdwopen (struct WINDOWCTRL **wc, int *win_num);
/* 0231  */ void p_clone_window (void);
#ifdef MSDOS
/* 0232  */ void p_switch_line_mode (void);
#endif /* MSDOS */
/* 0232  */ void restore_window_mode (void);
/* 0232  */ void memorize_window_mode (void);
/* 0240  */ void vi_append (void);
/* 0241  */ void vi_append_eol (void);
/* 0242  */ void vi_insert_bol (void);
/* 0243  */ void vi_bell (void);
            void vi_set_bell_mode (int mode);
/* 0244  */ void vi_ex (void);
            int vi_ex_interp (char *buffer);
            int ex_set_command (char *buffer);
/* 0245  */ void vi_dkey (void);
/* 0246  */ void vi_insert_after_line (void);
/* 0247  */ void vi_insert_before_line (void);
/* 0248  */ void vi_repeat_last_command (void);
/* 0248  */ int set_repeat_command (void (*fnc)(void));
/* 0249  */ void vi_join (void);
/* 0250  */ int vi_change_text (struct WINDOWCTRL *w, int mode,
              int count);
#define VI_CHG_WORD     1
#define VI_CHG_CHAR     2
#define VI_CHG_2EOLN    3
#define VI_CHG_LINE     4
#define VI_CHG_2BOLN    5
#define VI_CHG_WORD3    6
#define VI_CHG_WORD4    7
/* 0251  */ void vi_substitute (void);
/* 0252  */ void pico_mode (void);
/* 0253  */ void wordstar_mode (void);
/* 0253v */ void vi_mode (void);
/* 0254  */ void vi_change_2eoln (void);
/* 0254b */ void vi_change_2boln (void);
/* 0255  */ void vi_change_line (void);
/* 0256  */ void vi_jmp_boln (void);
            void vi_wc_jmp_boln (struct WINDOWCTRL *wc);
/* 0256a */ void vi_jmp_column (void);
/* 0257  */ void vi_jmp_prev_boln (void);
/* 0258  */ void vi_jmp_next_boln (void);
/* 0259  */ int ex_tag_command (const char *str);
/* 0260  */ struct MARKER *ned_get_marker (int marker_id, int alloc);
            int ned_marker_callback (int event, void *line, void *cd,
              int column, void *op2);
            int ned_reset_markers (struct WINDOWCTRL *w);
            int ned_reset_a_marker (int marker_id);
            int ned_check_for_markers (struct LINE *lp, int all);

#define ned_marker_rel_cb(pl,mp) \
  ned_line_rel_cb ((pl), ned_marker_callback, LCB_standard, (mp))
#define ned_marker_reg_cb(pl,mp) \
  ned_line_reg_cb ((pl), ned_marker_callback, LCB_standard, (mp))

/* 0260b */ int ned_jmp_marker (int marker_id, int flg);
/* 0260c */ int ned_set_marker (struct WINDOWCTRL *wc, int marker_id);

/* 0261  */ void vi_digit (void);
/* 0262a */ void vi_jmp_2line (void);
/* 0263  */ int ned_yank_block (int add_mode);
            int ned_yank_marked (struct MARKER *mrk_beg,
              struct MARKER *mrk_end, int add_mode);

/* 03.. ------------------------------------------------------------------- */
/* 0301  */ void p_ovins (void);
/* 0302  */ void p_ww (void);
/* 0303  */ void p_ins (void);
#ifdef USE_ABBREVIATIONS
           int ned_check_abbrev (void);
           int ned_reset_abbrev (void);
           int ned_abbrev_reduce (void);
           int ned_define_abbrev (const char *lhs, const char *rhs);
           int ned_undefine_abbrev (const char *lhs);
#endif /* USE_ABBREVIATIONS */

/* 0304  */ void q_insert (int k, int df);
/* 0304b */ void q_insert_string (char *s, int  df);
/* 0305  */ void ned_wc_insert (register struct WINDOWCTRL *w, int k, int df);
/* 0306  */ void ned_wc_delete (struct WINDOWCTRL *w, int df);
/* 0307  */ void p_insblk (void);
/* 0308  */ int get_txt (struct LINE *lp, int coln);
            int get_txt_visible (struct LINE *lp, int coln);
/* 0309  */ void wd_coldis (struct WINDOWCTRL *w, int la, int lz,
              struct LINE *lp, int coln, int colpos);
/* 0310  */ void p_colornxt (void);
/* 0311  */ void p_backcolnxt (void);
/* 0312  */ int get_confirmation (char *message, int std);
/* 0313  */ void p_turn_line (void);
/* 0314  */ void p_fget (void);
/* 0315  */ void p_alt_minus (void);
/* 0316  */ void p_alt_gleich (void);
/* 0319  */ void NED_interpreter (void);
            void vi_on (void);
            void vi_ins (void);
            void ned_wc_ins_mode (struct WINDOWCTRL *wc, int mode);
            void vi_ovr (void);
/* 0320  */ void p_alt_zero (void);
/* 0321  */ void ned_line_end_MAC (void);
/* 0322  */ void ned_line_end_MSDOS (void);
/* 0323  */ void ned_line_end_UNIX (void);
/* 0324  */ void NEDa1_interpreter (void);
/* 0325  */ void NEDa2_interpreter (char *IP);
/* 0326  */ void wd_init (struct WINDOWCTRL *w);
/* 0327  */ int q_kbin (void);
/* 0328  */ int qq_insert (struct LINE *lp, int insert_idx, int character,
              int insert_flag);
/* 0329  */ int qq_delete (struct LINE *lp, int delete_idx, int delete_cnt);
/* 0330  */ void ned_delete_word (void);
            void ned_delete_word_2 (void);
            void ned_delete_word_3 (void);
            int ned_wc_delete_word (struct WINDOWCTRL *wc, int mode);
/* 0331  */ void ned_lp_delete_word (struct LINE *lp, int delete_idx, int mode);
/* 0332  */ int qq_insert_string (struct LINE *lp, int insert_idx,
              const char *str, int str_lng, int insert_flag);
/* 0332b */ int qq_insert_string_array (struct LINE *lp, int insert_idx,
              const char *ftxt[], int t_cnt, int insert_flag);
/* 0333  */ void ned_save_reload (struct WINDOWCTRL *wc,
              int change_tag_display_mode);
/* 0333b */ void p_save_reload (void);
/* 0333c */ void p_show_tag_normally (void);
/* 0333d */ void p_show_tag (void);
/* 0333e */ void p_show_full_tag (void);
            void ned_reload_ascii (void);
            void ned_reload_sgml (void);
/* 0334  */ void ned_read_entity (void);
/* 0334b */ int ned_enter_entity (const char *str);
/* 0335  */ void p_toggle_case (void);
/* 0341a */ int ned_line_trigger_change (struct LINE *lp,
              int column, int amount);
/* 0341b */ int ned_line_trigger_split_join (struct LINE *lp,
              struct LINE *lp2, int column, int action);
/* 0341c */ int ned_line_trigger_delete (struct LINE *lp,
              int destroy, int cycle);
/* 0342a */ int ned_line_reg_cb (struct LINE *lp, line_callback *fnc,
              int event_mask, void *cd);
/* 0342b */ int ned_line_rel_cb (struct LINE *lp, line_callback *fnc,
              int event_mask, void *cd);
/* 0342c */ int ned_line_test_cb (struct LINE *lp);

/* 04.. ------------------------------------------------------------------- */
/* 0401  */ void s_fget (struct WINDOWCTRL *w);
/* 0402  */ int ned_f_read (struct WINDOWCTRL *w, char *filenm_txt,
                             char *filenm_ftr, int flag,
                             struct LINE **laptr, struct LINE **lzptr,
                             long la_offset, long lz_offset);
#ifdef _FILE_DEFINED
#ifdef __GG_streams__
/* 0402b */ int ned_stream_read (struct WINDOWCTRL *w,
              struct LINE **laptr, struct LINE **lzptr,
              long lz_offset, int format,
              struct STREAM_OBJECT *so, FILE *ff, int flcnt, int fccnt);
#endif /* __GG_streams__ */
#endif /* _FILE_DEFINED */
/* 0403  */ int ned_f_write (struct WINDOWCTRL *w, char *filenm_txt,
                              char *filenm_ftr, int flag, int lz_flag,
                              struct LINE *laptr, struct LINE *lzptr,
                              long *la_offset, long *lz_offset, int flg2);
#define FLG2_none          0x00
#define FLG2_append_mode   0x01 /* Bit 0: Append Modus                      */
#define FLG2_block_mode    0x02 /*     1: Block Modus                       */
#define FLG2_format_change 0x04 /*     2: change file mode ASCII<->SGML     */
#define FLG2_write_crlf    0x08 /*     3: write CR LF Pairs                 */

/* 0404  */ int ned_w_save (struct WINDOWCTRL *w, int flg);
/* 0405  */ int q_allsave (int flg);
#ifdef _FILE_DEFINED
/* 0406  */ void fputc_code (int ch, FILE *fo);
/* 0406  */ int fgetc_code (FILE *fi);
/* 0406  */ void set_code (char *cp);
/* 0406  */ void flush_last (FILE *f);
#endif
/* 0407    gen_extension() -> fnmcpy() und fnmcpy2() (siehe sbr.h) */ 
/* 0408  */ void p_sx (void);
/* 0409  */ void p_save (void);
/* 0409b */ void ned_rename_and_save (void);
/* 0409c */ void ned_pico_exit (void);
/* 0410  */ void p_ssave (void);
            void ned_ssave_all (void);
/* 0411  */ void p_abandon (void);
/* 0412  */ void ned_wc_abandon (struct WINDOWCTRL *wc);
/* 0413  */ void p_qabandon (void);
/* 0414  */ void p_save_restart (void);
/* 0415  */ void p_load_restart (void);
/* 0416  */ void p_shell (void);
/* 0417  */ void p_link (void);
/* 0417b */ int q2_link (struct WINDOWCTRL *w_dest,
              struct WINDOWCTRL *w_src, int flags);
/* 0418  */ void p_unlink (void);
/* 0419  */
/* 0420  */ int editable_file (char *fnm);
/* 0421  */ void p_XX_break (void);
/* 0422  */ void ned_show_author (void);
/* 0423  */ void ned_show_version (void);
/* 0424  */
/* 0425  */ int find_file (char *fnm,
              char *current_path, char **real_fnm, char **virtual_fnm);
/* 0426  */ void q_shell (char *command_line);
/* 0427  */ void p_pfile (void);

/* ****  ** BEGIN mostly obsolete functions for access to networked objects */
/* 0428  */ int access_gopher (char *hlink, char *fil);
/* 0429  */ int q_extract (char *filename, char *message);
/* 0430  */ void p_extract (void);
/* 0431  */ int dorothy_rw (char *tmpfnm, char *server, long port,
              char *action, char *cl_or_file, char *fr);
/* 0432  */ int read_access_methods (char *fn);
/* 0432  */ int do_prompt (char *str);
/* 0432  */ int indirect_object_access (char *tmpfnm, int read_or_write,
              int file_or_cluster, char *location, char *cl_or_file,
              char *fr);
/* ****  ** END mostly obsolete functions for access to networked objects */

/* 0433  */ void enable_ned_history (void);
/* 0433  */ void disable_ned_history (void);
/* 0433  */ int setup_ned_history (void);
/* 0433  */ int ned_history (char *file_or_cluster, char *frame,
              char *comment, int f_type, int f_format);
/* 0434  */ char *ned_get_file_path (struct WINDOWCTRL *wc);

/* 05.. ------------------------------------------------------------------- */
/* 0501  */ void p_aitoggle (void);
/* 0502  */ void ned_del2eoln (void);
/* 0502b */ int ned_w_del2eoln (register struct WINDOWCTRL *w);
/* 0502c */ void ned_del2boln (void);
/* 0502d */ int ned_w_del2boln (register struct WINDOWCTRL *w,
              int opcode);
/* 0503  */ void ned_pr_jump_to_line (void);
            int ned_cb_jump_to_line (const char *str, void *cb_data);
/* 0504  */ struct LINE *ned_get_line_by_nr (register struct LINE *lp,
              int *lnr);
/* 0505  */ int ned_jmp_2line_by_nr (struct WINDOWCTRL *w,
              int lnr, int flg);
/* 0506a */ int ned_cnt_line_2beg (struct LINE *a);
/* 0506b */ int ned_cnt_line_2end (struct LINE *a);
/* 0506c */ int ned_cnt_total_lines (struct LINE *a);
/* 0506d */ void ned_cnt_act_line (void);
/* 0506e */ int ned_cnt_line_relative (register struct LINE *a,
              register struct LINE *b);
/* 0507  */ void ned_show_total_lines (void);
/* 0508  */ int ned_w_jmp_aktline (struct WINDOWCTRL *wc,
              int offset_mode, int offset, int flg);
#define NEDJMP_LINE_TOP         1
#define NEDJMP_LINE_3           2
#define NEDJMP_LINE_MID         3
#define NEDJMP_LINE_BOT         4
#define NEDJMP_FLAG_REDRAW   0x01
#define NEDJMP_FLAG_BOLN     0x02
#define NEDJMP_FLAG_NO_CNT   0x04       /* don't count current line number  */
#define NEDJMP_FLAG_STD (NEDJMP_FLAG_REDRAW|NEDJMP_FLAG_NO_CNT|NEDJMP_FLAG_BOLN)

/* 0508b */ void ned_jmp_aktline_bot (void);
/* 0508m */ void ned_jmp_aktline_mid (void);
/* 0508t */ void ned_jmp_aktline_top (void);
/* 0509  */ int ned_wc_ins_nl (struct WINDOWCTRL *wc);
/* 0510  */ void ned_delete_line (void);
            int ned_wc_delete_line (register struct WINDOWCTRL *w,
              int blk_save, int col_text);
/* 0510b */ int ned_delete_current_line (register struct WINDOWCTRL *w);
/* 0510c */ int ned_delete_a_line (register struct WINDOWCTRL *w,
                                     register struct LINE *lp);
/* 0511  */ void ned_join3 (struct WINDOWCTRL *wc);
/* 0512  */ void tabulate (void);
/* 0513  */ void pq_up (void);
/* 0514  */ void pq_dn (void);
/* 0515  */ int ned_split (struct LINE *split_line,
                              struct LINE **splitted_part,
                              int split_position, int auto_indent);
/* 0515b */ int ned_split2 (struct LINE *split_line,
                                struct LINE **splitted_part,
                                int split_position, int auto_indent);
/* 0516  */ int ned_join (struct LINE *lp1, struct LINE *lp2);
/* 0516b */ int ned_join2 (struct LINE *lp1, struct LINE *lp2);
/* 0517  */ int ned_copy_line (struct LINE **dl, struct LINE *sl);
/* 0518  */
/* 0519  */ int jmpline_relative (register struct WINDOWCTRL *w,
              double fraction);
/* 0520 */ int jmp2column (register struct WINDOWCTRL *w, int coln);
/* 0521 */ int ned_copy_feature_list (struct FEATURE **fd,
             struct FEATURE *fs);
/* 0522 */ int winstack_push (struct WINDOWCTRL *w);
/* 0522 */ struct WINDOWCTRL *winstack_pop (void);
/* 0522 */ int winstack_delete (struct WINDOWCTRL *w);
/* 0522 */ struct WINDOWCTRL *winstack_get (int num);

/* 06.. ------------------------------------------------------------------- */
/* 0602  */ void ned_clear_screen (void);
/* 0603  */ void p_refresh (void);
/* 0604  */ void p_refresh_all (void);
/* 0605  */ void p_jmpwdw (void);
/* 0606  */ struct WINDOWCTRL *q_jmpwdw (int i);
/* 0607  */ void p_pushpage (void);
/* 0608  */ void q_pushpage (struct WINDOWCTRL *w, int new_page);
/* 0609  */ int maus_jmpwdw (int x, int y);
/* 0610  */ int q_ofile (int flags);
/* 0610a */ void p_ofile1 (void);
/* 0610b */ void p_ofile2 (void);
/* 0610c */ int ned_open_file (const char *fnm,
              const char *help_cluster, const char *help_frame, int flags);
/* 0610d */ int ned_cb_open_file (char *str, void *cb_data);
/* 0610e */ int ned_open_file_2 (struct WINDOWCTRL *wc,
              char *fnm, int flags);
/* 0611  */ void p_wdwsfile (void);
/* 0612  */ void p_wdwqfile (void);
/* 0613  */ int rd_str (char *msg, char *str, int str_size);
/* 0613b */ int ned_rd_str2 (const char *msg, char *str, int str_lng,
              int msg_lin, int col_ask, int *last_key);
/* 0614  */ int ned_rename_file (char *fnm, int max_fnm);
/* 0615  */ int q_fnm (char *fnm);
/* 0616  */ int ned_rename_object (void);
/* 0617  */ /* void p_garbling_code (void); ... not used any more */
/* 0618  */ void p_exit (void);
/* 0619  */ void p_ultra_panic (void);
/* 0620  */ void debug (char *s);
/* 0621  */ int ned_error_message (char *s);
/* 0622  */ int ned_message_1 (const char *p1);
            int ned_message_2 (const char *p1, const char *p2);
            int ned_message_3 (const char *p1, const char *p2, const char *p3);
            int ned_message_4 (const char *p1, const char *p2,
                               const char *p3, const char *p4);
            int ned_message_X (int cnt, const char *s[]);
/* 0623  */ void correct_pathname (char *s);
/* 0624  */ void save_message_line (void);
/* 0624  */ void restore_message_line (void);
/* 0625  */ int q2_jmpwdw (struct WINDOWCTRL *wc);
/* 0626  */ void q0_jmpwdw (struct WINDOWCTRL *wc);
/* 0627  */ int open_file_and_window (char *filename);
/* 0628  */ int take_history_notes (struct WINDOWCTRL *w);
/* 0629  */ int get_window_number (struct WINDOWCTRL *w);
/* 0630  */ char *FC_setup_filenames (struct FILECTRL *fc,
              char *specified, char *ftr_name);
/* 0631  */ int ned_prompt_string (const char *msg, char *str, int str_lng,
              const char *help_cluster, const char *help_frame,
              NED_field_editor_callback *cb, void *client_data);

/* 07.. ------------------------------------------------------------------- */
/* 0701  */ int ned_set_marker2 (struct WINDOWCTRL *wc, struct LINE *lp,
              int offset, struct MARKER *b);
/* 0702  */ void ned_set_marker_key (void);
/* 0703  */ void ned_group_set_marker (void);
/* ....  */
/* 0705  */ struct NED_BUFFER *ned_get_buffer (int buffer_id, int alloc);
/* ....  */
/* 0711  */ void vi_yank (void);
/* 0712  */ void ned_blk_mode (void);
/* 0713  */ void ned_set_block_markers (struct WINDOWCTRL *wc,
              struct LINE *lp, int offset, int what, int mode);
/* 0714  */ void p_blkbeg (void);
/* 0715  */ void p_blkend (void);
/* 0716  */ void p_hideblk (void);
/* 0717  */ int ned_reset_block_flags (struct WINDOWCTRL *w);
/* 0718  */ void ned_blk_rst (void);
/* 0719  */ int ned_set_block_flags (void);
/* 0719b */ int ned_swap_markers (struct MARKER *m1, struct MARKER *m2);
/* 0719c */ int ned_copy_markers (struct MARKER *dst, struct MARKER *src);
/* 0720  */ int ned_blk_invalid (void);
/* 0721  */ void ned_blk_screen (void);
/* 0722  */ int ned_blk_orientation (struct LINE *p);
/* 0723  */ int ned_drop_buffer2 (struct NED_BUFFER *bu);
/* 0723a */ int ned_drop_buffer (int name);
/* 0723b */ int ned_store_line_to_buffer (int name,
              struct LINE *lp_b, struct LINE *lp_e, int add_mode);
            int ned_fresh_buffer (void);
/* 0724  */ int ned_blk_isolate (
              struct LINE  *s_start, struct LINE  *s_stop,
              struct LINE **d_start, struct LINE **d_stop,
              int sp1, int sp2, int copy_mode);
/* 0724a */ int ned_blk_isolate2 (struct MARKER *m1, struct MARKER *m2,
              int no_realign);
/* 0725  */ int ned_blk_insert (struct LINE *where,
              struct LINE *start, struct LINE *stop);
/* 0725b */ int ned_blk_insert2 (struct LINE *act_line, int xcx,
              struct LINE *la, struct LINE *lb);
/* 0725c */ int ned_blk_insert3 (struct WINDOWCTRL *wc,
              struct LINE *la, struct LINE *lb, int before);
/* 0726  */ int ned_blk_duplicate (
              register struct LINE  *s_start, struct LINE  *s_stop,
              struct LINE **d_start, struct LINE **d_stop,
              int sp1, int sp2, int copy_mode);
/* 0727  */ void ned_wc_blk_copy (struct WINDOWCTRL *wc, int before);
/* 0727a */ void ned_blk_copy (void);
/* 0727b */ void ned_blk_copy_before (void);
/* 0727c */ void ned_wc_buffer_copy (struct WINDOWCTRL *wc,
              int buffer_id, int before);
/* 0727d */ void ned_buffer_copy (void);
/* 0727e */ void ned_buffer_copy_before (void);
/* 0728  */ void ned_blk_move (void);
/* 0729  */ void ned_blk_delete (void);
/* 0730  */ void ned_blk_read (void);
/* 0731a */ void ned_blk_append (void);
/* 0731p */ void ned_blk_print (void);
/* 0731w */ void ned_blk_write (void);
/* 0732  */ void q_wablk (int mode);
/* 0733  */ void q_jmp_marker (struct MARKER *m);
/* 0734  */ void p_jmp_blkbeg (void);
/* 0735  */ void p_jmp_blkend (void);
/* 0736  */ void ned_jmp_marker_key (void);
/* 0737  */ void ned_jmp_marker_1 (void);
            void ned_jmp_marker_find (void);
/* 0738  */ char *ned_block_2_string (char *buffer, int maxBytes,
              long offset, int flags);
/* ....  */
/* 0747  */ int ned_blk_critical (void);
/* 0747b */ int ned_blk_realign_if_critical (struct LINE *new_line);
/* 0749  */ void ned_blk_iconify (void);
/* 0750  */ int ned_blk_mark_all (struct WINDOWCTRL *w);
/* 0751  */ struct LINE *ned_find_first_line (struct LINE *lc);
/* 0752  */ struct LINE *ned_find_last_line (struct LINE *lc);
/* 0753  */ int ned_paste_string (const char *buffer, int ai_mode,
              char *line_prefix, char *line_postfix);
/* 0754a */ int ned_paste_date (void);
/* 0754b */ int ned_paste_seconds (void);
/* 0754c */ int ned_paste_date_time (void);
/* 0754d */ int ned_paste_date_string (void);
/* 0756  */ int ned_paste_file_name (void);
/* 0758  */ int ned_paste_user (void);
/* 0759  */ int ned_markup_block (struct WINDOWCTRL *w,
              int start_tag_segments, const char *start_tag [],
              int stop_tag_segments, const char *stop_tag []);
/* 0760  */ int ned_markup_block_2 (struct WINDOWCTRL *w, const char *start_tag);
/* 0761  */ void ned_markup_block_prompt (void);
/* 0763  */ int ned_paste_renamed_object (void);

/* 08.. ------------------------------------------------------------------- */
/* 0803  */ void p_feature_next (void);
/* 0804  */ void p_feature_prev (void);
/* 0805  */ void p_feature_range (void);
/* 0806  */ void p_feature_set (void);
/* 0807  */ void p_feature_reset (void);
/* 0808  */ int ned_link_feature_lines (int ftr_types,
              int ftr_subtypes, int str_cnt, char *mstr[]);
/* 0809  */ int ned_setup_feature_window (int ftr_types,
              int ftr_subtypes, int str_cnt, char *mstr[]);
/* 0810  */ void q_save_restart (void);
#ifdef _FILE_DEFINED
/* 0811  */ void q_save_marker (FILE *fo, struct MARKER *m);
#endif
/* 0812  */ void q_load_restart (void);
#ifdef _FILE_DEFINED
/* 0812  */ void q_load_marker (FILE *fi, struct MARKER *m);
#endif
/* 0813  */ void p_link_feature (void);
/* 0814  */ struct WINDOWCTRL *active_feature_window (
              struct WINDOWCTRL *w);

#ifdef _FILE_DEFINED
/* 0821  */ int wr_ftr (FILE *ff, int ln, struct FEATURE *fp,
              int col, int vcol);
/* 0822  */ void wr_ftr_txt (FILE *ff, struct FEATURE *fp,
              long *position);
/* 0823  */ int rd_ftr (struct WINDOWCTRL *wc, struct LINE *lp, FILE *ff,
              struct FEATURE **fpp, int p, char *repl_array, int *repl_size,
              int repl_max);
/* 0824  */ int wr_sgml_tag (FILE *ff, struct FEATURE *fp, int col_idx,
              long *position);
#endif /* _FILE_DEFINED */

#ifdef __GG_streams__
/* 0825  */ int rd_sgml_tag (struct WINDOWCTRL *wc,
              struct LINE *lp, struct STREAM_OBJECT *so,
              struct FEATURE **pf, int idx, int feature_type,
              int delimiter1, int delimiter2, char *repl_array,
              int *repl_size, int repl_max);
#endif /* __GG_streams__ */

/* 0826  */ int find_feature (struct LINE *lp, int direction,
              char *feature_name, struct LINE **found_line,
              int *nr_found_line, struct FEATURE **found_feature);
/* 0827  */ int find_feature_with_attribute (struct LINE *lp,
              int direction, char *feature_name, char *attribute_name,
              char *attribute_value, struct LINE **found_line,
              int *nr_found_line, struct FEATURE **found_feature);
/* 0828  */ void copy_tag (char *dst, char *src, int max_dst, int mode);
/* 0828  */ int ned_identify_feature (struct WINDOWCTRL *wc,
              struct LINE *lp, int offset,
              int feature_type, struct FEATURE *ft, char *lin,
              char *repl_array, int *repl_size, int repl_max);
/* 0829  */ int ned_insert_feature (struct FEATURE **fp,
              struct FEATURE *f);

/* 0830  */ int setup_sgml_entity_descriptors (char *setup_file_name);
/* 0830  */ void reset_sgml_entity_descriptors (void);
/* 0830  */ struct SGML_ENTITY_DESCRIPTOR *get_sgml_entity_descriptor (
              int tag_id);
/* 0830  */ struct SGML_ENTITY_DESCRIPTOR *find_sgml_entity_descriptor (
              char *tag);
/* 0831  */ int setup_sgml_tag_descriptors (const char *setup_file_name);
/* 0831  */ void reset_sgml_tag_descriptors (void);
/* 0831  */ struct SGML_TAG_DESCRIPTOR *get_sgml_tag_descriptor (
              int tag_id);
/* 0831  */ struct SGML_TAG_DESCRIPTOR *find_sgml_tag_descriptor (
              char *tag);
/* 0832  */ void p_format_SGML (void);
/* 0833  */ void p_format_ASCII (void);
/* 0834  */ int ned_eval_string (char *str, int option);
/* 0835  */ void ned_eval_str (void);
/* 0836  */ int ned_eval_hlink (char *str, int option);
#ifdef __NOT_LONGER_USED__
/* 0837  */ int get_attr_value (char *src, char *dst, int dst_lng,
             int flags);
#endif
/* 0838  */ char *ned_line_2_string (struct LINE *la, int la_idx,
              struct LINE *lz, int lz_idz, char *dst, int dst_siz,
              long offset, int flags);
/* 0838a */ long ned_line_list_size (struct LINE *la, int la_idx,
              struct LINE *lz, int lz_idx, int flags);
/* 0839  */ int ned_eval_line (struct LINE *la, int la_idx,
                               struct LINE *lz, int lz_idx, int option);
            int ned_eval_lookup_feature (const char *token, int option);
            int ned_eval_tag_entry (const char *token);
/* 0840  */ void ned_eval_block (void);
/* 0841  */ void ned_eval_feature (void);
/* 0841b */ int q_eval_tag (void);
/* 0842  */ struct FEATURE **ned_feature_find3 (int range);
/* 0842b */ struct FEATURE **ned_feature_find (struct LINE *lp, int x,
              int range);
/* 0842c */ struct FEATURE **ned_feature_find2 (struct WINDOWCTRL *wc,
              int range);
/* 0843  */ int eval_ned_macro (char *str, int option);
/* 0844  */ struct CLUSTERCTRL *ned_get_cluster_list (void);
            struct CLUSTERCTRL *ned_activate_cluster (const char *fn);
/* 0844b */ int ned_free_clusterctrl (struct CLUSTERCTRL *cl);
/* 0845  */ struct FRAMECTRL *ned_activate_frame (struct CLUSTERCTRL *cl,
              const char *fr_name, struct WINDOWCTRL *w, int search_mode,
              int file_fmt, const char *template_frame,
              const char *alternative_frame);
/* 0845a */ int ned_deactivate_frame (struct FRAMECTRL *fr);
/* 0846  */ struct FRAMECTRL *find_frame (struct CLUSTERCTRL *cl,
              const char *fr_name, int search_mode);
/* 0847  */ struct FRAMECTRL *create_framectrl (struct CLUSTERCTRL *cl,
              const char *fr_name, long idx, int where);
/* 0848  */ int get_index (struct FRAMECTRL *fr);
/* 0849  */ int update_index (struct CLUSTERCTRL *cl,
              long idx, long off_beg, long off_end, long cl_nr);
/* 0850  */ struct FEATURE *q_feature_set (struct LINE *lp, int cpos,
              int feature_type, int t_cnt, const char *ftxt[]);
/* 0850b */ struct FEATURE *ned_new_feature (int cpos, int feature_type);
/* 0851  */ int eval_window_parameters (struct WINDOWCTRL *w, char *str);
#ifdef __NOT_LONGER_USED__
/* 0852  */ char *find_attr_name (char *str, char *name);
#endif
/* 0853  */ int eval_logic_link (struct WINDOWCTRL *w, char *direction);
/* 0854a */ void p_logic_link_next (void);
/* 0854b */ void p_logic_link_prev (void);
/* 0854c */ void p_logic_link_menu (void);
/* 0854d */ void p_logic_link_up (void);
/* 0854e */ void p_logic_link_lang (void);
/* 0854f */ void p_logic_link_sort (void);
/* 0854g */ void p_logic_link_view (void);
/* 0854h */ void p_logic_link (void);
/* 0856  */ int ned_lookup_current_feature (char *token,
              char *line_buffer, char **feature_string, char **feature_type,
              int MAX_TOKEN, int MAX_BUFFER);
/* 0857  */ int ned_lookup_feature (const char *token, char *line_buffer,
              char **feature_string, char **feature_type, int MAX_BUFFER);
/* 0857b */ int ned_lookup_tag (const char *token, char *line_buffer,
              char **field_fnm, char **field_location, int MAX_BUFFER);
/* 0857c */ int ned_lookup_feature_cache (const char *token,
              char **feature_string, char **feature_type);
            int ned_store_feature_cache (const char *token,
              const char *feature_string, const char *feature_type);
/* 0858  */ int ned_rename_frame (struct WINDOWCTRL *w, const char *fnm,
              int file_fmt);
/* 0858b */ int ned_cb_rename_frame (char *str, int size,
              int malloced, void *cb_data);
/* 0859  */ int eval_ned_parameter (char *str, int option);
/* 0860  */ int check_logic_links (struct WINDOWCTRL *w);
/* 0861  */ void ned_set_SGML_tag (void);
/* 0862  */ void ned_set_SGML_entity (void);
/* 0863  */ int ned_wc_feature_create (struct WINDOWCTRL *wc, int what,
              int ftr_edit_mode, char *attribute);
/* 0863b */ int ned_wc_simple_feature_create (struct WINDOWCTRL *wc,
              struct LINE *lp, int idx, int what, char *str);
/* 0864  */ int initialize_frame (struct WINDOWCTRL *w, const char *fr_name);
/* 0865  */ void ned_set_hyx_l (void);
/* 0866  */ int show_feature (struct FEATURE *fp);
/* 0867  */ void ned_wc_memorize_location (struct WINDOWCTRL *wc);
            void ned_forget_location (void);
/* 0867b */ void ned_memorize_location (void);
/* 0868  */ void p_logic_link_more (void);
/* 0868  */ void p_link_more (void);
/* 0869  */ struct FRAMECTRL *ned_activate_special (const char *cl_name,
              const char *fr_name, int cr_mode);
            int ned_set_create_special (int flg);
/* 0869b */ struct FRAMECTRL *ned_activate_cl_fr (const char *cl_name,
             const char *fr_name, int search_mode, int format,
             const char *template_frame, const char *alternative_frame);
/* 0870  */ void p_activate_cl0 (void);
            void p_activate_cl1 (void);
            void p_activate_cl2 (void);
            void p_activate_cl3 (void);
            void p_activate_cl4 (void);
            void pico_help (void);
            int ned_activate_note_cluster (char *buffer);
            int ned_find_note_cluster (const char *sym_cluster, const char *frame,
                  int create_mode, int memorize);
            int ned_define_note_cluster (const char *symbolic, const char *cluster,
                  int create_mode, int memorize);
            int ned_init_sym_bookmarks (void);
/* 0871  */ void p_activate_crf (void);
/* 0872  */
/* 0873  */ int ned_register_bookmark (char *symbolic_name,
              char *title, char *section, char *tag_string);
            int ned_load_bookmarks (char *filename, char *section);
            int ned_save_bookmarks (char *filename, char *section);
            int ned_symbolic_bookmark (char *name, int option);
/* 0874  */
/* 0875  */ void p_activate_fr_root (void);
/* 0876  */ void p_activate_fr_notes (void);
/* 0877  */ void p_activate_fr_help (void);
/* 0878  */ void ned_p_activate_cl_fr (void);
            int ned_set_create_special (int flg);
/* 0879  */ void p_cross_ref (void);
/* 0879i */ void ned_lookup_lib (void);
/* 0879l */ void ned_lookup_lexicon (void);
/* 0879t */ void ned_lookup_thesaurus (void);
/* 0880  */ void ned_activate_cross_ref (char *str, int flg_resize,
              int cluster_type, int local_or_global);
#define CRF_IN_CRF              0x01
#define CRF_IN_LIB              0x02
#define CRF_IN_LEX              0x04
#define CRF_IN_THES             0x08
#define CRF_EVERYWHERE          0x0F
#define CRF_LOCAL               0x01
#define CRF_GLOBAL              0x02
#define CRF_GLOBAL_AND_LOCAL    0x03

/* 0881  */ void p_2cross_ref (char *str, int MAX_STR); /* NOT USED */
/* 0882  */ int ned_cross_ref (const char *target, int prompt, int ty,
              int loc, int lower);
            int ned_cb_cross_ref (char *edited_string,
              int size, int malloced, void *callback_data);
/* 0883  */ struct CLUSTERCTRL *activate_remote_cluster (char *clus,
             char *server, long port);
/* 0884  */ void ned_set_mark (void);
/* 0885  */ void ned_set_lookup_tag (void);
/* 0885b */ void ned_set_lookup_tag_fr (void);
/* 0886  */ struct FEATURE *ned_feature_set (struct WINDOWCTRL *w,
              struct LINE *lp, int offset, int what,
              int ftr_segment_cnt, const char *ftr_segment []);
            struct FEATURE *ned_feature_set2 (struct WINDOWCTRL *w,
              int line, int offset, int what,
              int ftr_segment_cnt, const char *ftr_segment []);
/* 0887 */ void ned_ftr_shift_up (void);
           void ned_ftr_shift_down (void);

/* 09.. ------------------------------------------------------------------- */
/* 0901  */ void def_setupfnm (char *s);
/* 0902  */ void p_edsetup (void);
/* 0903  */ int ned_read_setup (char *fnm);
            int ned_what_stp_cmd (char *s);

/* 0905  */ int stp_whatprim (char *s);
#ifdef _FILE_DEFINED
/* 0906  */ void stp_rtbl (FILE *fi, int tn, int f);
/* 0907  */ void stp_func (FILE *fi, int tn, int f);
/* 0908  */ void stp_macro (FILE *fi, char *token, int max_token,
                                 int mac_type);
/* 0909  */ void stp_window (FILE *fi);
/* 0910  */ int stp_maus (FILE *fi);
#endif
/* 0911  */ int trans_str (const char *si, char *so, int size);
/* 0912  */ int p_rdsetup (void);
/* 0913  */ int kbin_jou (void);
/* 0914  */ int jou_in (void);
/* 0915  */ int p_open_jou_rd (void);
/* 0916  */ void p_open_jou_wr (void);
/* 0917  */ void p_close_jou (void);
/* 0918  */ int mac_expand (void);
/* 0919  */ void p_macro (int num);
            void ned_q_macro (struct NED_MACRO *mp);
/* 0921  */ /* void p_macro00 (); */
/* 0922  */ int ned_tcl_startup (char *rc_names [], char *tcl_glib);
            int ned_tcl_run_file (char *rc_name);
            int ned_paste_tcl (char *tcl_script);
            int ned_tcl_stop (void);
/*       */ int mac_call_tcl (char *tcl_script);
            int ned_tk_import_selection (void);
            int ned_tk_wc_window_action (struct WINDOWCTRL *wc, int what);
#define WC_action_deiconify     1
#define WC_action_iconify       2
#define WC_action_withdraw      3
/* 0923  .. int ned_tcl_register (Tcl_Interp *interp) */
/* 0933  */ int ned_tk_redraw_window2 (struct WINDOWCTRL *w);
           int ned_tk_associate_window (struct WINDOWCTRL *wc);
           int ned_tk_delete_association (struct WINDOWCTRL *wc);
           int ned_tk_set_window_name (struct WINDOWCTRL *wc, char *name);
/* 0934  */ int ned_tk_block_export_flag (int flag);
/* ....  .. .... ..... ......... ....... */
/* 0972  */ void p_mac_define (void);
/* 0973  */ int mac_clr (void);
/* 0974  */ int mac_undef (int num);
/* 0975  */ int mac_define (int num, int macro_type, const char *str, int lng);
/* 0976  */ int ned_submit_macro (const char *s);
/* 0977  */ int mac_parse (char *tokens, int mac_type);
/* 0978  */ int mac_definition (char *tok_num, const char *tok_text,
                                int mac_type);
/* 0979  */ void p_mac (void);
           int mac_bind (int n_ptbl_offset, int num);
           int mac_unbind (int n_ptbl_offset);
#ifdef _FILE_DEFINED
/* 0980  */ void p_dump_macro (void);
/* 0981  */ int stp_attr (FILE *fi, char *b, int max_b);
#endif

/* 10.. ------------------------------------------------------------------- */
/* 1001  */ int ned_check_mouse (void);
/* 1002  */ void look1_for_maus (void);
/* 1003  */ void look2_for_maus (void);
/* 1004  */ void maus_wdw (int where);
/* 1004  */ void p_menue (void);
/* 1006  */ void maus_menue (int mode);
/* 1007  */ int q_window_menu (void);
/* 1008  */ void p_window_menu (void);
/* 1009  */ void show_buttons (struct WINDOWCTRL *wc);
/* 1010  */ int test_maus (int left, int right, int left_right);
/* 1011  */ int rst_button (void);
#ifdef _FILE_DEFINED
/* 1012  */ int stp_button (FILE *fi, char *str, int max_str);
#endif
/* 1013  */ int def_button (int bdx, int bdy, int bdc, int bdt,
             int bdm, int bdi, char *bdtext);
/* 1014  */ struct BUTTON_DESCRIPTOR *locate_button (int bdx, int bdy);
/* 1015  */ int execute_mm_item (long fc);
#ifdef _FILE_DEFINED
/* 1016  */ int stp_mm_item (FILE *fi, char *str, int max_str);
#endif
/* 1017  */ int ned_mouse_set_cursor (int x, int t);
/* 1018  */ int ned_mouse_event (int x, int y, int t, int abs_x,
             int abs_y);
/* 1019  */ int ned_search_button_bar (int x, int y, int t);

/* 11/ -------------------------------------------------------------------- */
/* 1101  */ void p_fr_next (void);
/* 1102  */ void p_find (void);
            void vi_find_forward (void);
            void vi_find_backward (void);
            void pico_find (void);
/* 1103  */ void p_replace (void);
/* 1104  */ void ned_ws_find_replace_dialog (struct WINDOWCTRL *wc, int fr);
            char *ned_prompt_find (char *prompt);
            int ned_save_search_string (char *s);
            int ned_save_search_options (int opt);
/* 1105  */ int ned_str_match (struct LINE *z_start, int c_start,
              struct LINE *z_end, unsigned char *mtch, unsigned char *ignore,
              int matching_ignore_level,
              struct LINE **z_fnd, int *c_fnd, int *ml, int option);
/* 1106  */ int ned_is_bracket (int chx);
/* 1106  */ int ned_find_bracket (int mode);
/* 1107  */ void p_find_matching_bracket (void);
/* 1108  */ void p_find_higher_bracket (void);
/* 1109  */ void p_find_lower_bracket (void);
/* 1110  */ int ned_wc_find_replace (struct WINDOWCTRL *wc,
              struct LINE *z_start, int c_start, struct LINE *z_end, int c_end,
              int blck_mode, int option, int find_replace, char *find_str,
              char *repl_str, int repeat_within_line, int repeat_counter,
              struct MARKER *m_fnd);
/* 1111  */ int ned_all_lines (struct WINDOWCTRL *w, int use_matching_lines,
              int str_cnt,char *mstr[]);
/* 1112  */ int ned_lp_find_str (struct WINDOWCTRL *wc, struct LINE *lp,
              char *mstr, int option, int cnt, int skip);
/* 1112v */ int ned_vi_wc_find_str (struct WINDOWCTRL *wc, char *mstr,
              int cnt, int mode);
            void ned_vi_find_next (void);
            void ned_vi_find_next_rev (void);
/* 1112w */ void ned_ws_aw_find_str (void);
/* 1113  */ int ned_jmp_pattern (struct WINDOWCTRL *wc, struct LINE *lp,
              char *pattern, int options);
            int ned_jmp_complex (struct WINDOWCTRL *wc, int jmp_line,
              char *jmp_pattern);
            int vi_find (struct WINDOWCTRL *wc, int back);
            void ned_set_ic (int mode);
            void ned_set_wrapscan (int mode);

/* 13/ -------------------------------------------------------------------- */
/* 1301  */ int ned_text_to_sgml (char *fnm_txt, char *fnm_ftr,
              char *fnm_sgml, int f_append);
/* 1302  */ int ned_sgml_to_text (char *fnm_txt, char *fnm_ftr,
              char *fnm_sgml);

#endif /* __NED_proto__ */
