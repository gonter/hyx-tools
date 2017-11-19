BEGIN {
  fn="";
  fn2="";
  fp=0;
  print "0 0 0 0 10 1 1 0" >"@$.ftr"
  print "searching... [generated by possig.awk]" >"@$.pos"
  al=2;
}
FILENAME!=fn2 {
  print FILENAME
  fn2=FILENAME;
}

  { wflg=0; }

# include file checks --------------------------------------------------------
#/include/ {
#  x=$0;
#  s1 = gsub (/\"/, "\"", x);
#  s2 = gsub (/\\/, "/", x);
#  s2+= gsub (/\//, "/", x);
#  if (substr(x,1,1) == "#" && s1 > 0 && s2 > 0)  prt(" \"");
#}
# /ed.h/ { next }
# /edhyx.h/ { next }
# /proto.h/ { next }
# /window.h/ { next }
# /message.h/ { next }
# /stdio.h/ { next }
# /string.h/ { next }
# /strings.h/ { next }
# /maus.h/ { next }
# /keys.h/ { next }
#/<malloc.h>/ { next }
# /include/ { prt("include"); }
# ----------------------------------------------------------------------------

#/FTR_display_replarray/ { prt("FTR_display_replarray"); }
#/ftr_replarray_size/ { prt("ftr_replarray_size"); }
#/highest_index/ { prt("highest_index"); }
#/next_index/ { prt("next_index"); }
#/IDX_REC_SIZE/ { prt("IDX_REC_SIZE"); }
#/12/ { prt("12"); }
#/�/ { prt("�"); }
#/�/ { prt("�"); }
#/�/ { prt("�"); }
#/�/ { prt("�"); }
#/�/ { prt("�"); }
#/�/ { prt("�"); }
#/�/ { prt("�"); }
#/flclose_all/ { prt("flclose_all"); }
# /close_lexicon_filecache/ { prt("close_lexicon_filecache"); }
# /print_lexicon_filecache/ { prt("print_lexicon_filecache"); }
#/->/&&/next/ { prt("next"); }
#/index_file/ { prt("index_file"); }
#/s_p2o/ { prt("s_p2o"); }
#/s_o2p/ { prt("s_o2p"); }
#/dict_process_entry/ { prt("dict_process_entry"); }
# ------ Erweiterung um HYX_PARSER_CLASS
#/s_o2p/ { prt("s_o2p"); }
#/s_o2p/ { prt("s_o2p"); }
#/display_markup/ { prt("display_markup"); }
#/hyx_text_to_markup/ { prt("hyx_text_to_markup"); }
#/dict_restructure_new_entry/ { prt("dict_restructure_new_entry"); }
#/hyx_parse1_file/ { prt("hyx_parse1_file"); }
#/read_tag_definition/ { prt("read_tag_definition"); }
/DAMODE_DIVIDE/ { prt("DAMODE_DIVIDE"); }
# ------ Erweiterung um HYX_PARSER_CLASS II
#/dict_check_integrity/ { prt("dict_check_integrity"); }
#/find_tag_definition/ { prt("find_tag_definition "); }
#/new_tag_definition/ { prt("new_tag_definition"); }
#/process_tag_definition/ { prt("process_tag_definition"); }
#/find_tag_definition/ { prt("find_tag_definition"); }
#/dict_add_file/ { prt("dict_add_file"); }
#/dict_update_entry/ { prt("dict_update_entry"); }
#/dict_restructure2_entry/ { prt("dict_restructure2_entry"); }
#/process_markup/ { prt("process_markup"); }
#/hyx_parse_hyx_frame_file/ { prt("hyx_parse_hyx_frame_file"); }
#/hyx_text_to_markup/ { prt("hyx_text_to_markup"); }
# ------ Erweiterung um HYX_PARSER_CLASS III
#/identify_tag/ { prt("identify_tag"); }
#/dict_process_entry/ { prt("dict_process_entry"); }
#/hyx_parse_hyx_frame/ { prt("hyx_parse_hyx_frame"); }
#/hyx_ta_find_tag_definition/ { prt("hyx_ta_find_tag_definition"); }
# ------ Erweiterung um HYX_PARSER_CLASS IV
#/get_tag_definition/ { prt("get_tag_definition"); }
#/hyx_mktx_elem_and_segm/ { prt("hyx_mktx_elem_and_segm"); }
#/hyx_ta_store_node/ { prt("hyx_ta_store_node"); }
# ------ Erweiterung um HYX_PARSER_CLASS V
#/hyx_parse2_char/ { prt("hyx_parse2_char"); }
#/hyx_make_markup/ { prt("hyx_make_markup"); }
#/hyx_ta_parse_flush/ { prt("hyx_ta_parse_flush"); }
#/s_o2p/ { prt("s_o2p"); }
# -------------------------------------------
#/dict_restructure2_entry/ { prt("dict_restructure2_entry"); }
#/<gg\// { prt("<gg/"); }
#hyx.l/ { prt("hyx.l"); }

# ----------------------------------------------------------------------------
wflg!=0 {
  print  FILENAME" ("FNR"): ", $0 >>"@$.pos";
  al++;
}

function prt(t) {
# if (FILENAME != fn || fp != FNR) {
   cs=1;
   if (FNR >= 10) cs++;
   if (FNR >= 100) cs++;
   if (FNR >= 1000) cs++;
   if (FNR >= 10000) cs++;
   cl=length(t);
   for (cx=length($0);cx>0;cx--) if (substr($0,cx,cl) == t) {
     printf al" "cx+5+cs+length(FILENAME)" 1 " >>"@$.ftr";
     printf "<hyx.l file=\""FILENAME"\" ln="FNR" cn="cx-1 >>"@$.ftr";
     print  " tdc=79 tdp="cl">" >>"@$.ftr";
   }
   wflg=1;
# }
 fn = FILENAME;
 fp = FNR;
}