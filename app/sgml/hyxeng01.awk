# Kommandos fr die HyperText Engine in C Struktur umwandeln
# 1990 04 12
BEGIN {
  print "#ifndef __GG_hyxeng01_awk__" >>"$2";
  print "#define __GG_hyxeng01_awk__" >>"$2";
  
}
$1=="#" { next }

  {
  print $1, $2, $3 >>"$1";
  print "# define HYXENG_"$3" "$1 >>"$2";
}
END {
  print "#endif" >>"$2";
}