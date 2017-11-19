BEGIN {
  fo=0;
}
  {
  gsub ("\\\\", "/");
  gsub ("/usr/ned", "%ned");
# print
}
$1=="@h" && $3!="%ned" {
  if (fo) {
    printf ("</Frame>\n");
    fo=1;
  }
  sub ("%", "");
  split ($3, dn, "/");
  dnn=dn[2];
  printf ("<Frame ned/%d>", dnn);
  if (dnn >  1) printf ("<HLINK fr=\"ned/%d\" dir=prev>", dnn-1);
  if (dnn < 11) printf ("<HLINK fr=\"ned/%d\" dir=next>", dnn+1);
  printf "\n"
  fo=1;
}
$1=="@f" && fo==1 {
  printf ("<HLINK file=\"%s%s\"> * %s%s\n", $3, $4, $3, $4);
}
