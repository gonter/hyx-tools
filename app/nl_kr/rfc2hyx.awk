#
# FILE rfc2hyx.awk
#
# reformat a streamed RFC into HYX format
#
# written:       1994-04-15
# latest update: 1995-05-11
#
BEGIN {
  fnm_top= "tmp/@1.t";
  fnm_hyx= "tmp/@1.h";
  fnm_crf= "tmp/@1.c";

  print "<Frame $$root>">fnm_top;
  printf "">fnm_hyx;
  printf "">fnm_crf;

  st= 0;
  frame_open= 0;
  frame_counter= 0;
  frame_name= "";
  last_frame= "$$root";

# cross references
  server= "http://www.wu-wien.ac.at:8082/rfc/";
}

/^Status of [Tt]his [Mm]emo$/ \
  || /^Status of the Memo$/\
  || /^1./&&/Status of this Memo$/\
  || /^Status of [Tt]his [Dd]ocument$/ {
  st= 1;
}

  {
  gsub("\\\&", "\\&amp;");
  gsub("<", "\\&lt;");
  gsub(">", "\\&gt;");
}

st==0 {
  print >>fnm_top;
  next;
}

$0!="" && substr($0,1,1) != " " && substr($0,1,1) != "\t"\
  && !/--/ && !/^RFC-/\
  && substr($0,1,1) != "*"\
  && substr($0,1,1) != "\&" && substr($0,1,1) != "+" && substr($0,1,1) != "-"\
  && substr($0,1,1) != "\"" && substr($0,1,1) != "{" && substr($0,1,1) != "}"\
  && !/^Help: / && !/^Retrieve: / && !/^List: / \
  && !/^Record lease,/ \
  && substr($0,1,1) != "|" && substr($0,1,1) != "<" && substr($0,1,1) != "]" {

  # a new section means a new frame
  # find out which section this is and generate a new frame name
  section= $0;
  print "section: "section
  frame_name= FILENAME"."frame_counter++;
  for (i= 1; i<=NF; i++) frame_name= frame_name" "$(i);

  # print closing info into previous frame
  if (frame_open == 1) {
    printf ("<hyx.l fr=\"%s\" dir=next>", frame_name)>>fnm_hyx;
    print "</Frame>" >>fnm_hyx;
  }

  # print opening info into new frame
  printf "<Frame "frame_name">" >>fnm_hyx;
  printf "<hyx.l fr=\""last_frame"\" dir=prev>" >>fnm_hyx;
  print  "<hyx.l fr=\"$$root\" dir=up>" >>fnm_hyx;
  print  "<title>"section"</title>" >>fnm_hyx;
  print  "<h2>"section"</h2>" >>fnm_hyx;

  # print a link into the $$root frame
  printf "<hyx.l fr=\""frame_name"\" tdc=31">>fnm_top;
  if (frame_counter == 1) printf " dir=next">>fnm_top;
  print " tdp="length(section)">"section >>fnm_top;

  frame_open= 1;
  last_frame= frame_name;
  next;
}

  {
  print >>fnm_hyx;
}

END {
  if (frame_open == 1) {
    printf "<hyx.l fr=\"$$root\" dir=next>" >>fnm_hyx;
    print "</Frame>" >>fnm_hyx;
  }

  # write final links etc to the $$root frame
  print  "<hyx.l fr=\""last_frame"\" dir=prev>" >>fnm_top;
  print  "<hyx.l fr=\"$$index\" tdp=7>$$index">>fnm_top;
  # printf "<hyx.l fr=\"$$notes\" tdp=7>$$notes">>fnm_top;
  # print  ", e.g. bookmarks and annotations">>fnm_top;
  print  "</Frame>" >> fnm_top;

  # write a dummy $$notes frame
  print "<Frame $$notes>">>fnm_top;
  print "* latest stop">>fnm_top;
  print "</Frame>" >> fnm_top;
}
