#
# FILE ~/usr/ned/crf.awk
#
# Cross Reference Cluster Generator
#
# This script can be used for two purposes:
# 1. generating cross reference frame for the %crf cluster
# 2. generating lookup-tags for ALT-TAB markups
#
# The input can either be the output of a run of "crf" or a
# run of "objdec -a".  Objdec  will do if only lookup tags are
# generated, otherwise the output from crf would be more
# desireable.
#
# written:       1991 10 24
# latest update: 1995-06-15
#
# ----------------------------------------------------------------------------
BEGIN {
  # out_mode= "feature.tfb";
  out_mode= "crf.lex";
  # out_mode= "crf.hyx";

  fo= 0;
  xfilenm= "";
  pfx= ""
  yfilenm= "";
  frame= "";
}

FILENAME== "/etc/feature.mod"&&/^#/ { next; }
FILENAME== "/etc/feature.mod" {
  split ($0,xx,":");
  mods[xx[1]]= xx[2];
  next;
}

$1=="TITLE" {
  filenm($2);
  yfilenm= $2;
}

# definition of symbols
$1=="d"||$1=="D"||$1=="PUBLIC" {
  if (fo) print "</Frame>"
  fo= 0;

  if ($1=="PUBLIC") ss= substr($2,2); else ss= substr($3,2);
  if (substr(ss,1,4) == "cga_")  ss= "w_" substr(ss,5);
  if (substr(ss,1,5) == "bios_") ss= "w_" substr(ss,6);
  frame= ss;

  if (out_mode=="crf.hyx") {
    print "<Frame $"ss">"
    print "Symbol "ss
    fo= 1;
  }

  if ($1!="PUBLIC") {
    filenm($4);
    yfilenm= $4;
  }

  if (out_mode=="crf.hyx") {
    printf ("\ndefined in <hyx.l file=\"%s\">* %s\n", xfilenm, $4);
    print "used in:"
  }

  if (out_mode=="feature.tfb") {
    printf ("%s:F:<hyx.l file=\"%s\" mark=\"%s\" tdc=\"hyx.l\" tdp=%d>\n",
            ss, xfilenm, ss, length(ss));
  }

  if (out_mode=="crf.lex") {
    print "<:><LE>"ss"</LE><SYM>"ss"\n<PUB>"xfilenm"<;>";
    # print "<:><LE>@@fnc</LE><hyx.l fr=\""ss"\">"ss"<;>";
  }
}

#
$1=="EXTRN" && $2=="__acrtused" { next; }

$1=="g"||$1=="G"||$1=="EXTRN" {
  if (fo) print "</Frame>"
  fo= 0;
# print out info about symbol in an unknown module:

  if ($1=="EXTRN") ss= substr($2,2); else ss= substr($3,2);
  if (substr(ss,1,4) == "cga_")  ss= "w_" substr(ss,5);
  if (substr(ss,1,5) == "bios_") ss= "w_" substr(ss,6);

  if (out_mode=="crf.hyx") {
    print "<Frame $"ss">"
    print "Symbol "ss
    fo= 1;
    filenm($4);
    print "defined somewhere..."
    print "used in:"
  }

  if (out_mode=="crf.lex") {
    print "<:><LE>"ss"</LE><EXT>"xfilenm"<;>";
  }
}

#
($1=="u"||$1=="U")&&fo==1 {
  if (out_mode=="crf.hyx") {
    for (i=2; i<=NF;i++) if ($(i) != yfilenm) {
      filenm($(i));
      printf ("<hyx.l file=\"%s\">* %s\n", xfilenm, xfilenm);
    }
  }
}

END {
  if (fo) print "</Frame>"
}

#
function filenm(s) {
  xfilenm= "";
  if (substr(s,1,3) == "ned") {
    if (s == "ned00.c") xfilenm= "%ned/ned00.c"; else {
      xfilenm= "%ned/"substr(s,4,2)"/"s
    }
  } else if (substr(s,1,4) == "win_" || substr(s,1,4) == "WIN_") {
    lev= substr(s,6,1);
    if (lev=="0") {
      if (substr(frame,1,3)=="cga")   lev="cga"; else
      if (substr(frame,1,4)=="_cga")  lev="cga"; else
      if (substr(frame,1,4)=="bios")  lev="bios"; else
      if (substr(frame,1,5)=="_bios") lev="bios"; else
      lev="cga";   # hmmm....
    } else if (lev=="a") {
      lev="0";
    }
    xfilenm= "%win/"lev"/"s
  } else {
    for (mm in mods) {
      if (substr(s,1,length(mm))==mm) xfilenm= mods[mm]"/"s;
    }
  }
  if (xfilenm=="") xfilenm= "%sbr/"s;
}
