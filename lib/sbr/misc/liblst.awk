# Print List of Modules from LIB-Cross Reference List
# Tylman Susato 1989 09 17
$2=="Offset:" { MN[$1]=1; }
END { i=1;
      for (x in MN) printf ("%3d: %s\n", i++, x);
    }
