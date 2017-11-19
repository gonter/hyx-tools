#
# <gg/window.h>
BEGIN {
  CLASS= "";
  con= "\\dev\\con";
}

$1=="#ifdef" {
  CLASS= $2;
  print "CLASS "CLASS >>con;
  next;
}

$1=="#endif" {
  CLASS= "";
  # print "CLASS "CLASS >>con;
  next;
}

CLASS=="" { next; }

$1=="#define" {
  SYMBOL[$2":"CLASS]= $3;
}

END {
  for (s in SYMBOL) printf ("%-32s -> %s\n", s, SYMBOL[s]);
}
