# File /usr/ned/lpr03.awk
# process a NED source single file for line printing
BEGIN {
  fnm="";
  ver=0;
}
fnm=="" {
  print "\\subsection{\\tt "FILENAME"}";
  print "\\def\\LPtopC{\\tt "FILENAME"}";
  print "\\def\\LPtopD{~}";
  fnm=FILENAME;
}
$0=="" {
  if (ver) {
#    print "\\end{verbatim}";
    ver=0;
  }
  print;
  next;
}
substr($0,1,1)!=" "&&substr($3,1,1)=="("&&
  ($1=="void"||$1=="int"||$1=="char") {
# if (ver) {
#    printf "\\end{verbatim}";
#   ver=0;
# }
  xfunc=$2;
  xtype=$1" ";
  while (substr(xfunc,1,1)=="*") {
    xfunc=substr(xfunc,2);
    xtype=xtype"*";
  }
  printf "\\label{"xfunc"}\\marginpar{$\\leftarrow$}"
  printf "\\def\\LPtopD{"translit(xtype" "xfunc)"}"
  printf translit(xfunc)" \\> "translit(xtype)>>"nedsrc01.tex";
  print  "\\> \\pageref{"xfunc"}\\\\">>"nedsrc01.tex";
}
substr($0,1,1)!=" "&&substr($4,1,1)=="("&&$1=="struct" {
# if (ver) {
#    printf "\\end{verbatim}";
#   ver=0;
# }
  xfunc=$3;
  xtype=$1" "$2" ";
  while (substr(xfunc,1,1)=="*") {
    xfunc=substr(xfunc,2);
    xtype=xtype"*";
  }
  printf "\\label{"xfunc"}\\marginpar{$\\leftarrow$}"
  printf "\\def\\LPtopD{"translit(xtype" "xfunc)"}"
  printf translit(xfunc)" \\> "translit(xtype)>>"nedsrc01.tex";
  print  "\\> \\pageref{"xfunc"}\\\\">>"nedsrc01.tex";
}
ver==0 {
#  print "\\begin{verbatim}";
  ver=1;
}
  {
  str=$0;
  strip=0;
  while (substr(str,1,1)==" ") {
#    printf "\\rule{1ex}{0mm}";
    strip++;
    str=substr(str,2);
  }
  if (strip>0) { printf ("\\rule{%3.2fex}{0mm}", strip*1.22); }
  print "\\verb`"str"`\\\\";
}

END {
  if (ver) {
#    print "\\end{verbatim}";
    ver=0;
  }
}

function translit(x) {
  gsub ("\\","\\backslash",x);
  gsub ("#","\\#",x);
  gsub ("$","\\$",x);
  gsub ("&","\\\\&",x);
  gsub ("~","\\~",x);
  gsub ("_","\\_",x);
  gsub ("\\^","\\^",x); # bug in awk?
  gsub ("%","\\%",x);
  gsub ("{","\\{",x);
  gsub ("}","\\}",x);
  return x;
}
