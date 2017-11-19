# File TAGS.AWK
# Ausgabe von Tags, die in einen File vorkommen.
BEGIN {
  FS="<";
  fnm="" 
  aktframe="";
  aktfrprt=0;
}
/\\ref{/   { report("REF:   ") }
/\\label{/ { report("LABEL: ") }
/{figure}/ { report("FIGURE: ") }
/{table}/  { report("TABLE: ") }
/\\glqq/   { report("GLQQ: ") }
/\\grqq/   { report("GRQQ: ") }
# FILENAME!=fnm {
#   if (fnm!="") showtags();
#   print "** FILE " FILENAME " ***************"
#   fnm=FILENAME
# }
  {
  x=y=$0;
  if (sub("<","",y) != sub(">","",y))
  {
    print "* ACHTUNG: Tag open != Tag close in File "FILENAME" Zeile "FNR
    print "* "$0
  }
  for (i=1;i<=NF;i++) {
    x=y=$(i);
    if (x!="" && sub(">","",y)>0) {
      spi=split (x, sp, ">");
      if (spi >= 1) {
        if (substr(sp[1],1,1)==":") sp[1]=":...";
        if (substr(sp[1],1,2)=="--") sp[1]="--...--";
        if (substr(sp[1],1,6)=="Frame ") {
          aktframe=sp[1];
          aktfrprt=0;
          sp[1]="Frame ...";
        }
        if (substr(sp[1],1,6)=="stamp ") sp[1]="stamp ...";
        if (substr(sp[1],1,6)=="HLINK ") sp[1]="HLINK ...";
#        if (substr(sp[1],1,5)=="Link ") sp[1]="Link ...";
        tag[sp[1]]++;
      }
    }
  }
}
END { showtags() }

function showtags() {
  for (t in tag) printf ("%5d <%s>\n", tag[t], t);
}

function report(s) {
  if (aktfrprt==0) print "\n"s" ## <"aktframe">"
  aktfrprt=1;
  print s" -- " $0
}
