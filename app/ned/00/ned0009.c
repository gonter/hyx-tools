/*
 *  FILE %ned/00/ned0009.c
 *
 *  Deklaration der primitiven Funktionen des Editors
 *
 *  Include File fuer ned0001.c, ned0002.c und ned0003.c
 *
 *                 1991 06 25: aus ned0001.c herausgeloest
 *  latest update: 2001-02-11 12:43:10
 *  $Id: ned0009.c,v 1.6 2002/06/15 04:35:20 gonter Exp $
 *
 */

#ifndef __NED_0009__
#define __NED_0009__

/* ------------------------------------------------------------------------ */
extern int
  p_ins (),       tabulate (),    p_split_join (),
  ned_cursor_left (),     ned_cursor_right (),
  ned_del_char_right (),     ned_del_char_left (),
  ned_delete_line (),    p_turn_line (),
  p_ctrlq (),     p_ctrlk (),     p_ctrlo (),
  p_ctrlu (),     p_ctrlw (),
  p_funct (),
  p_upscr (),     p_dnscr (),     ned_delete_word (),
  p_nl (),        p_nl2 (),       p_ax_lng (),
  p_refresh (),   p_refresh_all (),
  p_jmpwdw (),    p_pushpage (),  p_fget (),
  p_ofile1 (),    p_ofile2 (),    p_wdwqfile (),
  p_abandon (),   p_qabandon (),
  ned_rename_object (),    p_link (),      p_unlink (),    p_save (),
  p_ssave (),     ned_ssave_all (), p_sx (),        ned_pr_jump_to_line (),
  pq_up (),       pq_dn (),       ned_del2eoln (),
  p_aitoggle (),  p_rdsetup (),   p_edsetup (),
  p_blkbeg (),    p_blkend (),    
  p_hideblk (),   ned_blk_mode (),  p_ovins (),     p_ww (),
  p_clone_window (),
  p_colornxt (),  p_backcolnxt (),
  p_window_menu (), p_wdwfaecher (),
  p_open_jou_rd (), p_open_jou_wr (), p_close_jou (),
  p_wdwopen (),   ned_close_window (),  p_wdwsize (),
  p_wdwXup (),    p_wdwXdn (),    p_wdwXlt (),    p_wdwXrt (),
  p_wdwAup (),    p_wdwAdn (),    p_wdwAlt (),    p_wdwArt (),
  p_wdwBup (),    p_wdwBdn (),    p_wdwBlt (),    p_wdwBrt (),
  p_shell (),    p_insblk (),    QQdeb (),
  p_ultra_panic (), p_save_restart (), p_load_restart (),
  p_feature_next (), p_feature_prev (), p_feature_range (),
  p_feature_set (), p_feature_reset (), p_link_feature (),
  ned_show_author (),    p_XX_break (),  p_menue  (),
  p_find (),      p_replace (),   p_fr_next(),
  p_jmp_blkbeg (),p_jmp_blkend (),
  p_alt_minus (), p_alt_gleich (), p_alt_zero (),
  ned_eval_str (), ned_eval_block (), ned_eval_feature (),
  p_link_more (), p_logic_link_more (),
  p_activate_cl0 (),
  p_activate_cl1 (),  p_activate_cl2 (),  p_activate_cl3 (),
  p_activate_cl4 (),  p_activate_crf (),  ned_p_activate_cl_fr (),
  p_activate_fr_root (), p_activate_fr_notes (), p_activate_fr_help ();

extern int ned_ctrlp ();
extern int p_cross_ref (), ned_lookup_lexicon (), ned_lookup_lib ();
extern int ned_lookup_thesaurus ();
extern int ned_group_set_marker ();
extern int p_find_matching_bracket ();
extern int p_find_higher_bracket (), p_find_lower_bracket ();

extern int p_exit (), ned_pico_exit (), ned_rename_and_save ();
extern int ned_blk_copy (), ned_blk_copy_before ();
extern int ned_blk_move (), ned_blk_delete ();
extern int ned_blk_iconify (), ned_blk_read (), ned_blk_write ();
extern int ned_blk_append (), ned_blk_print ();
extern int ned_page_down (), ned_page_up ();
extern int ned_half_page_down (), ned_half_page_up ();
extern int ned_jmp_boln (), ned_jmp_eoln ();
extern int vi_jmp_boln (), vi_jmp_prev_boln (), vi_jmp_next_boln ();
extern int vi_digit ();
extern int p_word_left (), p_word_right_beg (),  p_word_right_end ();
extern int p_word_left_2 (), p_word_right_beg_2 (),  p_word_right_end_2 ();
extern int p_save_reload (),     p_show_tag_normally ();
extern int p_show_tag (),        p_show_full_tag ();
extern int ned_reload_ascii (), ned_reload_sgml ();
extern int p_logic_link_next (), p_logic_link_prev (), p_logic_link_menu ();
extern int p_logic_link_up (),   p_logic_link (),      p_logic_link_lang ();
extern int p_logic_link_sort (), p_logic_link_view ();
extern int ned_line_end_MAC (), ned_line_end_MSDOS (), ned_line_end_UNIX ();

extern int ned_set_marker_key (), ned_jmp_marker_key (), ned_jmp_marker_1 ();
extern int ned_jmp_marker_find ();
extern int
  ned_jmp_aktline_top (), ned_jmp_aktline_mid (), ned_jmp_aktline_bot ();

extern int
p_macro00 (), p_macro01 (), p_macro02 (), p_macro03 (), p_macro04 (),
p_macro05 (), p_macro06 (), p_macro07 (), p_macro08 (), p_macro09 (),
p_macro10 (), p_macro11 (), p_macro12 (), p_macro13 (), p_macro14 (),
p_macro15 (), p_macro16 (), p_macro17 (), p_macro18 (), p_macro19 (),
p_macro20 (), p_macro21 (), p_macro22 (), p_macro23 (), p_macro24 (),
p_macro25 (), p_macro26 (), p_macro27 (), p_macro28 (), p_macro29 (),
p_macro30 (), p_macro31 (), p_macro32 (), p_macro33 (), p_macro34 (),
p_macro35 (), p_macro36 (), p_macro37 (), p_macro38 (), p_macro39 (),
p_macro40 (), p_macro41 (), p_macro42 (), p_macro43 (), p_macro44 (),
p_macro45 (), p_macro46 (), p_macro47 (), p_macro48 (), p_macro49 ();

extern int p_mac_define (), p_mac ();
/* DEBUG only: */ extern int p_dump_macro ();

extern int ned_memorize_location ();
extern int p_pfile ();
extern int q_eval_tag ();

extern int p_extract ();
extern int vi_mode ();
extern int vi_on (), vi_ins (), vi_ovr (), vi_bell (), vi_ex (), vi_dkey ();
extern int vi_append (), vi_append_eol (), vi_insert_bol ();
extern int vi_insert_before_line (), vi_insert_after_line ();
extern int vi_repeat_last_command (), vi_join ();
extern int vi_substitute (), vi_change_line (), vi_change_2eoln ();
extern int vi_yank ();
extern int vi_find_forward (), vi_find_backward ();

extern int pico_mode (), pico_help (), wordstar_mode ();
extern int pico_find ();
extern int p_toggle_case ();

extern int ned_cursor_up (), ned_cursor_down ();
extern int ned_vi_cursor_top (), ned_vi_cursor_mid (), ned_vi_cursor_bot ();
extern int ned_ws_aw_find_str ();
extern int ned_vi_find_next (), ned_vi_find_next_rev ();

extern int ned_set_mark ();
extern int ned_set_lookup_tag (), ned_set_lookup_tag_fr ();
extern int ned_set_hyx_l ();
extern int ned_set_SGML_tag (), ned_set_SGML_entity ();
extern int ned_read_entity ();
extern int p_format_SGML (), p_format_ASCII ();
extern int ned_forget_location ();

extern int vi_jmp_2line (), vi_jmp_column ();
extern int ned_buffer_copy (), ned_buffer_copy_before ();
extern int ned_line_info ();

/* non-recasting */
extern int ned_paste_date (), ned_paste_seconds ();
extern int ned_paste_date_time ();
extern int ned_paste_date_string ();
extern int ned_paste_user ();
extern int ned_paste_renamed_object ();
extern int ned_paste_file_name ();
extern int ned_markup_block_prompt ();
extern int ned_ftr_shift_up (), ned_ftr_shift_down ();
extern int ned_set_lookup_tag_fr2 ();

#ifdef MSDOS
extern int p_switch_line_mode ();
#endif

#ifdef USE_TK
extern int ned_tk_import_selection ();
extern int ned_tk_aw_save_withdraw ();
extern int ned_tk_aw_withdraw ();
extern int ned_tk_aw_iconify ();
extern int ned_tk_aw_deiconify ();
extern int ned_tk_claim_selection ();
#endif /* USE_TK */

#endif /* __NED_0009__ */
