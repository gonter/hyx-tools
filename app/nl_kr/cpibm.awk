# FILE cpibm.awk
# written:       1992-02-06
# latest update: 1994-08-01
# modify c source file for compiling on a CMS system
# ----------------------------------------------------------------------------
BEGIN {
  print "#include \"ggcms.h\""
}
/<gg\// {
  sub("<gg\/", "\"");
  sub(">", "\"");
  print
  next
}
/<contrib\// {
  sub("<contrib\/", "\"");
  sub(">", "\"");
  print
  next
}
/<malloc.h>/ {
#  print "void *malloc(unsigned int);";
#  print "void *calloc(unsigned int, int);";
#  print "void *free(void *);";
  print "#include <stdlib.h>";
  next;
}
  { print }
/<stdio.h>/ {
  print "#define _FILE_DEFINED"
  next;
}
