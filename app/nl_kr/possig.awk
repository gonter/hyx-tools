BEGIN {
  fn="";
  fn2="";
  fp=0;
  print "0 0 0 0 10 1 1 0" >"@$.ftr"
  print "searching..." >"@$.pos"
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
# /malloc.h/ { next }
# /include/ { prt("include"); }
# ----------------------------------------------------------------------------

#/FTR_display_replarray/ { prt("FTR_display_replarray"); }
#/ftr_replarray_size/ { prt("ftr_replarray_size"); }
#/highest_index/ { prt("highest_index"); }
#/next_index/ { prt("next_index"); }
#/IDX_REC_SIZE/ { prt("IDX_REC_SIZE"); }
#/12/ { prt("12"); }
#/Ñ/ { prt("Ñ"); }
#/î/ { prt("î"); }
#/Å/ { prt("Å"); }
#/é/ { prt("é"); }
#/ô/ { prt("ô"); }
#/ö/ { prt("ö"); }
#/·/ { prt("·"); }
#/DI_pos/ { prt("DI_pos"); }
#/set_location_code/ { prt("set_location_code"); }
# ---
# /LMDC_word_index/ { prt("LMDC_word_index"); }
#/<malloc.h>/ {next}
# /lmd_create_word_ref_list/ { prt("lmd_create_word_ref_list"); }
# WORD_REF and WORD_REF_LIST
/WR_count/ { prt("WR_count"); }
#/WR_docinfo_count/ { prt("WR_docinfo_count"); }
#/WORD_REF_SIZE/ { prt("WORD_REF_SIZE"); }
#/DOCUMENT_INFO_LIST/ { prt("DOCUMENT_INFO_LIST"); }
#/bin_to_hex/ { prt("bin_to_hex"); }
#/lmd_discard_doc/ { prt("lmd_discard_doc"); }
# ------ 1995-12-05 14:44:51
# /MAX_DI_POS/ { prt("MAX_DI_POS"); }
# /DI_pos/ { prt("DI_pos"); }
#/LMDC_cnt_sw_idx/ { prt("LMDC_cnt_sw_idx"); }
# /lmd_insert_document_info/ { prt("lmd_insert_document_info"); }
# /lmd_set_location_code/ { prt("lmd_set_location_code"); }
# ------ 1995-12-05 14:44:51
# later:
#/LMDC_cnt/ { prt("LMDC_cnt"); }
#/DIL_next/ { prt("DIL_next"); }
# ---
#/lmd_get_word_ref/ { prt("lmd_get_word_ref"); }
#/set_new_word_index/ { prt("set_new_word_index"); }
#/print_04statistics/ { prt("print_04statistics"); }
#/read_document_info_list/ { prt("read_document_info_list"); }
#/DI_hit_count/ { prt("DI_hit_count"); }
#/DI_document_id/ { prt("DI_document_id"); }
#/design.h/ { prt("design.h"); }
#/lut_word_match/ { prt("lut_word_match"); }
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
