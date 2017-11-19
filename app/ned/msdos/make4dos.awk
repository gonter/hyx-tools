# MAKE4DOS.AWK                                                      1992-01-17
# makeup for MSDOS makefiles (zorland make)
# ----------------------------------------------------------------------------
BEGIN {
  st=0;         # 0 .. nothing; 1 .. target, makro or rule; 2 .. t2d */
}
substr($0,1,1)=="#" {
  print;
  next
}
substr($0,1,1)==" " {
  printf (" ");
  for (i=1;i<=NF;i++) printf (" %s", $(i));
  printf ("\n");
  next
}
substr($0,1,1)=="	" {   # UNIX
  printf ("	%s", $(1));
  for (i=2;i<=NF;i++) printf (" %s", $(i));
  printf ("\n");
  st=2;
  next
}
NF>0 {
  printf ("%s", $1);
  for (i=2;i<=NF;i++) printf (" %s", $(i));
  printf ("\n");
  st=1;
  next
}
NF==0 {
  print;
  st=0;
}
