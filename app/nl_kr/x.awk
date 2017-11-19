# 1990 11 10
# Grobe Categorisierung der Character Tables fÅr den IBMPC
BEGIN {
  hex [ 0] = "0";
  hex [ 1] = "1";
  hex [ 2] = "2";
  hex [ 3] = "3";
  hex [ 4] = "4";
  hex [ 5] = "5";
  hex [ 6] = "6";
  hex [ 7] = "7";
  hex [ 8] = "8";
  hex [ 9] = "9";
  hex [10] = "A";
  hex [11] = "B";
  hex [12] = "C";
  hex [13] = "D";
  hex [14] = "E";
  hex [15] = "F";
  print "char TAG_CAT_IBMPC [256] =\n{";
  for (i=0; i<256; i++) {
    if ((i%16) == 0) hex1 = hex [i/16];
    cat = "control2";
    if (i >=  32) ch=i; else ch=46;
    if (i >=  48 && i <=  57) cat = "digit";
    if (i >=  65 && i <=  90) cat = "capital";
    if (i >=  97 && i <= 122) cat = "small";
    if (i >= 128 && i <= 167) cat = "nat_small";
    if (i >= 176 && i <= 223) cat = "graphic";
    if (i >= 224 && i <= 235) cat = "greek";
    if (i >= 236 && i <= 253) cat = "math2";
    printf ("  /* %3d 0x%s%s %c */ TA_CAT_%s,\n",
      i, hex1, hex[i%16], ch, cat);
  }
  print "} ;"
}




