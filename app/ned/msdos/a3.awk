  {
  Gr=substr($0,7,2);
  Mm=substr($0,9,2);
  Mp=Mm-1;
  Mn=Mm+1;
  if ($2=="x") Mn=0;
  if ($2=="y") Mp=0;
  fout=sprintf ("%02d\\_bak_ftr.ned\\ned%02d%02d.ftr", Gr, Gr, Mm);
  printf ("%s\n", fout);
# fout="\\dev\\con";
  xout();
}
#
function xout() {
 printf ("0   0    1   0  10 1 1 32760\n")>fout;
 if (Mp > 0) {
 printf ("  1   1   1 <HLINK file=\"%%ned/%02d/ned%02d%02d.c\" dir=prev>\n",
   Gr, Gr, Mp)>>fout;
 }
 printf ("  2   1   1 <HLINK cl=\"%%ned/nedall.hyx\" fr=\"ned/%02d\" dir=up>\n",
   Gr)>>fout;
 if (Mn > 0) {
 printf ("  3   1   1 <HLINK file=\"%%ned/%02d/ned%02d%02d.c\" dir=next>\n",
   Gr, Gr, Mn)>>fout;
 }
 close(fout);
}
