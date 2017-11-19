#
# FILE %ned/multi.awk
#
# find multiply defined symbols
#
# written:       1995-06-15
# latest update: 1995-06-15
#
# ----------------------------------------------------------------------------

/^<:/ {
  SYM= "";
  PUB= "";
}

/^<SYM>/ {
  if (SYM != "") print SYM;
  SYM= $0;
}

/^<PUB>/ {
  if (PUB != "") print PUB;
  PUB= $0;
}
