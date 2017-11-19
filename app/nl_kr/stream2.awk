#!/usr/bin/awk -f
# FILE stream2.awk
#
# 'deformat' a RFC and remove pagination lines
# ... a more general approach than stream.awk
#
# written:       1994-05-01
# latest update: 1995-05-11
# $Id: stream2.awk,v 1.2 2012/08/10 15:21:00 gonter Exp $
# -------------------------

BEGIN {
  lc= 0;
}

$0=="ISO Transport Services on Top of the TCP" { next; }
$0=="Bootstrap Protocol" { next; }

  {
  B[lc++]= $0;
}

substr($0,1,1)=="" {
  for (lb= 0; B[lb] == "" && lb < lc; lb++);
  if (substr(B[lb],1,3) == "RFC") { lb++; }
  for (; B[lb] == "" && lb < lc; lb++);

  le_strip= 0;
  for (le= lc-3; B[le] == "" && le >= 0; le--) le_strip++;

  lines_printed= 0;
  for (i= lb; i<= le; i++) {
    print B[i];
    lines_printed++;
  }
  if (le_strip > 3 && lines_printed > 0) print "";

  lc= 0;
}
