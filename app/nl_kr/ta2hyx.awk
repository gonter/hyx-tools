#
# FILE ~/usr/ta/ta2hyx.awk
#
# NOTE: The form of the output from "ta -m4 etc.." has changed,
#       as a result, this script will not work properly!
#
# written:       1994-03-13
# latest update: 1994-04-03
# ----------------------------------------------------------------------------
BEGIN {
  frame_open= 0;
  xtype= 0;
  pfx= "xx";
  frame_num= 1;
  toc_cnt= 0;
  sec_used= 0;
  tbl_used= 0;
  fig_used= 0;
  first_frame= "";
  print "<Frame @sec>">"@sec";
  print "<Frame @tbl>">"@tbl";
  print "<Frame @fig>">"@fig";
}

$0=="<ta.par.sec>" || $0=="<ta.par.tbl>" || $0=="<ta.par.fig>" {
  if ($0=="<ta.par.sec>") { toc_file= "@sec"; sec_used= 1; }
  if ($0=="<ta.par.tbl>") { toc_file= "@tbl"; tbl_used= 1; }
  if ($0=="<ta.par.fig>") { toc_file= "@fig"; fig_used= 1; }
  last_frame= "";
  if (frame_open) last_frame= frame_name;
  frame_name= pfx"."frame_num++;
  if (frame_open) {
    print "<hyx.l fr=\""frame_name"\" dir=next></Frame>";
  } else {
    first_frame= frame_name;
  }
  printf "<Frame "frame_name">";
  if (last_frame != "") printf "<hyx.l fr=\""last_frame"\" dir=prev>";
  print "";
  frame_open= 1;
  head= 1;
  print;
  next;
}

$0=="</ta.par.sec>" || $0=="</ta.par.tbl>" || $0=="</ta.par.fig>" {
  head= 0;
  print;
  next;
}

head==1 || head==2 {
  if (head==1) {
    print "<hyx.l fr=\""frame_name"\">* "$0>>toc_file;
    head= 2;
  } else {
    print "  "$0>>toc_file;
  }
}

  {print;}

END {
  if (frame_open) print "</Frame>";

  print "<Frame $$root><hyx.l fr=\""first_frame"\" dir=next>\n"
  print "Table of contents\n";
  if (sec_used == 1) print "<hyx.l fr=\"@sec\">* Sections";
  if (tbl_used == 1) print "<hyx.l fr=\"@tbl\">* Tables";
  if (fig_used == 1) print "<hyx.l fr=\"@fig\">* Figures";
  print "</Frame>";

  print "</Frame>">>"@sec";
  print "</Frame>">>"@tbl";
  print "</Frame>">>"@fig";
}
