BEGIN {
  ldn=-1;
  fo=0;
}
substr($0,1,3)=="ned" {
  dnn=substr($0,4,2)+0;
  sub ("\\.C ", ".c ");
  if (ldn != dnn) {
    if (fo) {
      printf "</Frame>\n"
      fo=0;
    }
    printf ("<Frame ned/%02d>", dnn);
    printf ("<HLINK fr=\"$$root\" dir=up>");
#   if (dnn >  1)
    printf ("<HLINK fr=\"ned/%02d\" dir=prev>", dnn-1);
    if (dnn < 11) printf ("<HLINK fr=\"ned/%02d\" dir=next>", dnn+1);
    printf "\n"
    printf ("-----------------------\n");
    printf ("NED module package # %02d\n", dnn);
    printf ("-----------------------\n\n");
    fo=1;
    ldn=dnn;
  }
  printf ("<HLINK file=\"%%ned/%02d/%s\">* %02d/%s\n", dnn, $1, dnn, $0);
}
