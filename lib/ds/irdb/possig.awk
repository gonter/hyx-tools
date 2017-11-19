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
# /irdb_new_handle/ { prt("irdb_new_handle"); }
# /irdb_new_struct_handle/ { prt("irdb_new_struct_handle"); }
/IRDB_data/ { prt("IRDB_data"); }
/IRDB_payload_position/ { prt("IRDB_payload_position"); }
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
