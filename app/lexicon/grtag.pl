#
# FILE %lexicon/grtag.pl
#
# written:       1995-12-10
# latest update: 1995-12-10
#
# NOTES
# Anforderung und Wuensche an einen Wort Tagger:
# -  *bar$ -> absperrbar, Salatbar (N)
# -  Erkennung von Umlauten aus ae, oe, ue Konstruktionen
# -  Erkennung von &szlig; aus ss Konstruktionen
#

$mode= 'diag';          # report strange or difficult entries
# $mode= 'tag';         # normal tagging operation
# $mode= 'stat';        # print statistics only...

while (<>)
{
  chop;

  next if (/^#/);
  $found= 0;
  $total++;

  ($N_pos, $N_ty)= &identify_german_noun ($_);
  $found++ if ($N_pos ne '-');

  ($J_pos, $J_ty)= &identify_german_adjective ($_);
  $found++ if ($J_pos ne '-');

  ($A_pos, $A_ty)= &identify_german_adverb ($_);
  $found++ if ($A_pos ne '-');

  ($V_pos, $V_ty)= &identify_german_verb ($_);
  $found++ if ($V_pos ne '-');

  # statistics
  $CNT{'MULTI'}++ if ($found > 1);
  if ($found == 1)
  {
    $CNT{'N'}++ if ($N_pos ne '-');
    $CNT{'J'}++ if ($J_pos ne '-');
    $CNT{'V'}++ if ($V_pos ne '-');
    $CNT{'A'}++ if ($A_pos ne '-');
  }
  $CNT{'NONE'}++ if ($found == 0);

  if ($found > 1 && $mode eq 'diag')
  {
    print "$N_pos:$J_pos:$A_pos:$V_pos:$_\n";
    next;
  }

  if ($found == 1 && $mode eq 'tag')
  {
    if ($N_pos ne '')
    {
      if ($N_ty ne '') { $N_ty= " t=$N_ty"; }
      print "$_:<F f=$N_pos l=g$N_ty xt=gen>\n";
    }

    if ($J_pos ne '')
    {
      if ($J_ty ne '') { $J_ty= " t=$J_ty"; }
      print "$_:<F f=$J_pos l=g$J_ty xt=gen>\n";
    }

    if ($A_pos ne '')
    {
      if ($A_ty ne '') { $A_ty= " t=$A_ty"; }
      print "$_:<F f=$A_pos l=g$A_ty xt=gen>\n";
    }

    if ($V_pos ne '')
    {
      if ($V_ty ne '') { $V_ty= " t=$V_ty"; }
      print "$_:<F f=$V_pos l=g$V_ty xt=gen>\n";
    }

    next;
  }

  if ($mode eq 'tag')
  { # at this point, print everything that's not identifyable...
    print "$_:<F l=g>\n";
  }
}

foreach $cat (keys %CNT)
{
  $pct= int (100*$CNT{$cat}/$total);
  printf ("# %-8s %8s (%3s%%)\n", $cat, $CNT{$cat}, $pct);
}
printf ("# ------------------------\n", 'total', $total, '100');
printf ("# %-8s %8s (%3s%%)\n", 'total', $total, '100');

exit (0);

# ----------------------------------------------------------------------------
sub identify_german_noun
{
  local ($wort)= $_[0];

  # GG
  return ('N', 'f') if ($wort =~ /.bar$/);

  # Fleischer p. 198
  return ('N', 'n') if ($wort =~ /.zeug$/);
  return ('N', 'n') if ($wort =~ /.werk$/);
  return ('N', 'n') if ($wort =~ /.wesen$/);
  return ('N', 'n') if ($wort =~ /.gut$/);

  # Fleischer p. 152
  return ('N', 'f') if ($wort =~ /.igkeit$/);
  return ('N', 'f') if ($wort =~ /.keit$/);
  return ('N', 'f') if ($wort =~ /.heit$/);

  # Fleischer p. 154
  # return ('N', '') if ($wort =~ /.icht$/);
  # !! abricht

  # Fleischer p. 155
  return ('N', '') if ($wort =~ /ling$/);

  # Fleischer p. 157
  return ('N', '') if ($wort =~ /.nis$/);

  # Fleischer p. 159
  return ('N', 'n') if ($wort =~ /.sal$/);

  # Fleischer p. 160
  return ('N', '') if ($wort =~ /.sel$/);
  return ('N', 'f') if ($wort =~ /.schaft$/);

  # Fleischer p. 163
  return ('N', 'mn') if ($wort =~ /.tum$/); # m=Reichtum, n=Eigentum

  # Fleischer p. 164
  return ('N', 'f') if ($wort =~ /.ung$/);

  # Fleischer p. 178
  # return ('N', 'n') if ($wort =~ /.chen$/);
  # !! abgleichen
  return ('N', 'n') if ($wort =~ /.lein$/);

  # Fleischer p. 189, ff
  # return ('N', 'f') if ($wort =~ /.ade$/);
  # !! Ade
  # return ('N', 'f') if ($wort =~ /.age$/);
  # !! absage, Anlage
  return ('N', 'f') if ($wort =~ /.aille$/);
  # return ('N', 'f') if ($wort =~ /.elle$/);
  # !! Geselle, Stelle
  return ('N', 'f') if ($wort =~ /.enz$/);
  return ('N', 'f') if ($wort =~ /.anz$/);
  # return ('N', 'f') if ($wort =~ /esse$/);
  # !! abschliesse
  # return ('N', 'f') if ($wort =~ /iere$/);
  # !! abonniere
  return ('N', 'f') if ($wort =~ /.ik$/);
  return ('N', 'f') if ($wort =~ /.ion$/);
  return ('N', 'f') if ($wort =~ /.ose$/);
  return ('N', 'f') if ($wort =~ /.t&aauml;t$/);
  return ('N', 'f') if ($wort =~ /.taet$/);      # UML!!!
  # return ('N', 'f') if ($wort =~ /ur$/);
  # !! nur

  # Fleischer p. 194, ff
  return ('N', 'm') if ($wort =~ /.ant$/);
  # return ('N', 'm') if ($wort =~ /.ent$/);
  # !! abgedient
  return ('N', 'm') if ($wort =~ /.eur$/);
  return ('N', 'm') if ($wort =~ /.ismus$/);
  return ('N', 'm') if ($wort =~ /.asmus$/);
  return ('N', 'm') if ($wort =~ /.ist$/);
  # !! abgespeist
  # return ('N', 'm') if ($wort =~ /or$/);
  # !! sonor

  # Fleischer p. 196, ff
  # return ('N', 'mn') if ($wort =~ /ar$/);
  # !! absperrbar, sogar
  # return ('N', 'mn') if ($wort =~ /&auml;r$/);
  # !! elitaer
  # return ('N', 'mn') if ($wort =~ /at$/);
  # !! abtrat
  # return ('N', 'mn') if ($wort =~ /ier$/);
  # !! aasgeier
  # return ('N', 'mn') if ($wort =~ /it$/);
  # !! soweit

  # Fleischer p. 197, ff
  return ('N', 'n') if ($wort =~ /.arium$/);
  return ('N', 'n') if ($wort =~ /.ament$/);
  return ('N', 'n') if ($wort =~ /.ement$/);

  return ('-', '');
}

# ----------------------------------------------------------------------------
sub identify_german_adjective
{
  local ($wort)= $_[0];

  # GG: word stemmer
  if ($wort =~ /(.+)er$/) { $wort= $1; }
  if ($wort =~ /(.+)e$/)  { $wort= $1; }

  # Fleischer p. 251
  return ('J', '') if ($wort =~ /.bar$/);

  # Fleischer p. 253
  return ('J', '') if ($wort =~ /.lich$/);
  return ('J', '') if ($wort =~ /.sam$/);
  return ('J', '') if ($wort =~ /.faehig$/);             # UML !!!
  return ('J', '') if ($wort =~ /.f&auml;hig$/);

  # Fleischer p. 257
  return ('J', '') if ($wort =~ /.haft$/ && !($wort =~ /.schaft/));

  # Fleischer p. 259
  return ('J', '') if ($wort =~ /.isch$/);
  return ('J', '') if ($wort =~ /.los$/);

  # Fleischer p. 274
  return ('J', '') if ($wort =~ /.aessig$/);
  return ('J', '') if ($wort =~ /.&auml;ssig$/);        # UML !!!
  return ('J', '') if ($wort =~ /.&auml;$szlig;ig$/);   # UML !!!

  return ('-', '');
}


# ----------------------------------------------------------------------------
sub identify_german_adverb
{
  local ($wort)= $_[0];

  # Fleischer p. 297
  return ('A', '') if ($wort =~ /.her$/);
  return ('A', '') if ($wort =~ /.hin$/);


  return ('-', '');
}

# ----------------------------------------------------------------------------
sub identify_german_verb
{
  local ($wort)= $_[0];

  # Fleischer p. 322
  return ('V', '') if ($wort =~ /..ieren$/);
  # keine Nieren bitte...


  return ('-', '');
}

# ----------------------------------------------------------------------------
sub identify_whatever
{
  local ($wort)= $_[0];

  return ('-', '');
}
