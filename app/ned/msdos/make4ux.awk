# MAKE4UX.AWK                                                       1992-01-17
# prepare UNIX makefiles from MSDOS make (zorland make)
# ----------------------------------------------------------------------------
BEGIN {
  st=0;         # 0 .. nothing; 1 .. target, macro or rule; 2 .. t2d */
}
substr($0,1,1)=="#" {
  print;
  next;
}
substr($0,1,1)==" " {
  if (st==1) {
    printf (" ");
    for (i=1;i<NF;i++) printf (" %s", $(i));
  } else if (st==2) {
    printf ("	%s", $(1));
    for (i=2;i<NF;i++) printf (" %s", $(i));
  } else printf ("%s", $0);
  if (NF>1) {
    if ($(NF)=="!" || $(NF)=="\\") {
      printf (" \\");
    } else printf (" %s", $(NF));
  }
  printf ("\n");
  next;
}
substr($0,1,1)=="	" {   # UNIX
  printf ("	%s", $(1));
  for (i=2;i<=NF;i++) printf (" %s", $(i));
  printf ("\n");
  next;
}
NF>0 {
  st=2;
  printf ("%s", $1);
  for (i=2;i<NF;i++) printf (" %s", $(i));
  if (NF>1) {
    if ($(NF)=="!" || $(NF)=="\\") {
      printf (" \\");
      st=1;
    } else printf (" %s", $(NF));
  }
  printf ("\n");
  next;
}
NF==0 {
  print;
  st=0;
}
