#!/bin/awk
#
# FILE docdir.awk
#
# generate docdir entries for given file names
#
# 1993-03-07
# ----------------------------------------------------------------------------
BEGIN {
  docid=1001;
# def_sets=" set=\"nl_kr\"";
  def_sets="";
  n_xsets=0;
}
  { gsub ("\\\\","/"); } # don't ask my why my awk needs this!
  {
  pathc= split($1, path, "/");
  if (pathc > 1) {
    sets=" set=\""path[1]"\"";
    XSETS[path[1]]++;
    if (XSETS[path[1]]==1) n_xsets++;
  } else sets= def_sets;
  hdr=" name=\"C source file "$1"\"";
  printf ("<hyx.dd docid=\"%ld\" file=\"%s\"", docid, $1);
  printf ("%s%s>\n", hdr, sets);
  docid++;
}
END {
  if (n_xsets > 0) {
    printf ("# -------------------------------\n");
    printf ("# docs | set\n");
    printf ("# -------------------------------\n");
    for (s in XSETS) {
      printf ("# %4d | %s\n", XSETS[s], s);
    }
    printf ("# -------------------------------\n");
  }
}
