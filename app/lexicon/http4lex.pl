#!/usr/local/bin/perl
# FILE ~/usr/lexicon/http4lex.pl
#
# format frames from a lexicon as a filter stage of a HTTP4HYX server
# see also: lexicon.hyx
#
# written:       1995-01-18
# latest update: 1995-02-19
#
# ----------------------------------------------------------------------------

# $lex_path= '/afs/wu-wien.ac.at/public/usr/edvz/gonter/lexicon/';

# setup tag names (see "tags")
$tag_type{'DT'}= 'descriptive text';
$tag_type{'HP'}= 'hyphenation';
$tag_type{'TE'}= 'translation';
$tag_type{'WF'}= 'word form';
$tag_type{'CR'}= 'concept reference to';
$tag_type{'AE'}= 'alternative entry';

# setup langauage codes (see "language ID")
$lang{'e'}= ' (english)';
$lang{'g'}= ' (german)';
$lang{'d'}= ' (dutch)';
$lang{'s'}= ' (spanish)';
$lang{'f'}= ' (french)';
$lang{'i'}= ' (italian)';

# setup lexicon function codes (see "function codes")
$func_code{'a'}= ' archaic';
$func_code{'b'}= ' abbreviation';
$func_code{'c'}= ' capital';
$func_code{'d'}= ' dialectical';
$func_code{'e'}= ' erroneous';
$func_code{'f'}= ' alien';
$func_code{'h'}= ' rhetoric';
$func_code{'n'}= ' nonsense';
$func_code{'o'}= ' obsolete';
$func_code{'p'}= ' poetical';
$func_code{'q'}= ' colloquial';
$func_code{'r'}= ' rare';
$func_code{'s'}= ' standard';
$func_code{'w'}= ' nonce word';
$func_code{'x'}= ' specialised';
$func_code{'z'}= ' substandard';
$func_code{'A'}= ' adverb';
$func_code{'B'}= ' broken word';
$func_code{'C'}= ' conjunction';
$func_code{'D'}= ' name';
$func_code{'E'}= ' suffix';
$func_code{'F'}= ' prefix';
$func_code{'G'}= ' (appended)';
$func_code{'H'}= ' hyphenated';
$func_code{'I'}= ' interjection';
$func_code{'J'}= ' adjective';
$func_code{'K'}= ' *ENZYCLOPEDIC*';
$func_code{'L'}= ' phrase';
$func_code{'M'}= ' morpheme';
$func_code{'N'}= ' noun';
$func_code{'O'}= ' other';
$func_code{'P'}= ' past participle';
$func_code{'R'}= ' preposition';
$func_code{'S'}= ' syllable';
$func_code{'U'}= ' pronoun';
$func_code{'V'}= ' verb';
$func_code{'Y'}= ' *CONCEPT*';

# $req= <STDIN>;   # read request line
# print "Content-Type: text/html\n";
# print "";
# print "<PRE>\n";

alex_line: while (<STDIN>)
{
  chop;
  if (/<;/)
  {
    # print "\n";
    next alex_line;
  }

  if (/^<:/||/<;/||/<JF /)
  {
    next alex_line;
  }

  if (/^<IS /||/^<II /||/^<I /||/<SE>/)
  {
    next alex_line;
  }

  if (/^<LE>/)
  {
    $x= substr ($_, 4);
    ($word, $rest)= split (/</, $x);
    print "<title>MRLEX $word</title>\n";
    print "<h1>$word</h1>\n";
    next alex_line;
  }

  if (/^<F /)
  {
    $func= substr($_,1);
    ($func, $rest)= split ('>', $func);
    $func= &disp_F(substr($func,2));
    if ($func ne '' && $func ne ' ') { print "<dd>function: ".$func."\n"; }
    next alex_line;
  }

  if (/^<SL /)
  {
    ($inf, $ref)= split (/>/, $_);
    @p= split(' ',$inf);
    $refl= $ref;
    $refl=~ s/ /_b/g;
    $refl=~ y/A-Z/a-z/;
    print '<dd>see also ('.$p[1].'): <a href='.$refl.'>'.$ref.'</a>'."\n";
    next alex_line;
  }
  
  if (/^<DT /||/^<TE /||/^<HP>/||/^<WF /||/^<CR>/||/^<AE /)
  {
    ($func, $text)= split ('>', $_);
    ($text, $rest)= split ('<', $text);
    $pos= index($func, ' ');
    $tag= ($pos == -1) ? substr($func,1) : substr($func,1,$pos-1);
    $func= &disp_F($func,$pos+1);
    if ($tag eq 'TE' || $tag eq 'WF' || $tag eq 'CR' || $tag eq 'AE')
    {
      $refl= $text;
      $refl=~ s/ /_b/g;
      $refl=~ y/A-Z/a-z/;
      $text='<a href='.$refl.'>'.$text.'</a>'
    }
    print "<dd>$tag_type{$tag}$func: $text\n";
    next alex_line;
  }

  if (/^<xxM-/||/^<FJ /)
  {
    next alex_line;
  }

  $x= $_;
  $x=~ s/</&lt;/g;
  $x=~ s/>/&gt;/g;
  print '<dd>'.$x."\n";
}

# print "</PRE>\n";

exit (0);

sub disp_F
{
  local($code)= $_[0];  # contents of a tag, e.g. a <F> tag
  local($x);
  local($y);
  local($refl);
  local($rv)= '';
  local($pos);

func: while ($code ne '')
  {
# print "disp_F: begin code='$code'\n";
    if ($code =~ /^\?/
       || $code =~ /^s=/
       || $code =~ /^t=/)
    {
# print "disp_F: junk code='$code'\n";
      $pos= index($code,' ');
      $code= ($pos == -1) ? '' : substr($code, $pos+1);
      next func;
    }

    if ($code =~ /^cpt=/)
    {
      $pos= index($code,'" ');
      $x= ($pos == -1) ? substr($code,5,length($code)-6):substr($code,5, $pos-6);
# print "disp_F: cpt x='$x'\n";
      $x=~ s/\"//;
      $refl= $x;
      $refl=~ s/ /_b/g;
      $refl=~ y/A-Z/a-z/;
      $rv= $rv.' [referenced by concept: <a href='.$refl.'>'.$x.'</a>]';
      $code= ($pos == -1) ? '' : substr($code, $pos+2);
      next func;
    }

    if ($code =~ /^l=/)
    {
      $pos= index($code,' ');
      $x= ($pos == -1) ? $code : substr($code,0,$pos);
# print "disp_F: l x='$x'\n";
      $y= $x;
      $x= $lang{substr($x,2)};
      if ($x eq '') { $x= $y; }
      $code= ($pos == -1) ? '' : substr($code, $pos+1);
      $rv= $rv.$x;
      next func;
    }

    if ($code =~ /^f=/)
    {
      $pos= index($code,' ');
      $x= ($pos == -1) ? $code : substr($code,2,$pos-2);
# print "disp_F: f x='$x'\n";
      $rv= $rv.&disp_F_f($x);
      $code= ($pos == -1) ? '' : substr($code, $pos+1);
      next func;
    }

    if ($code =~ /^ /)
    {
      $code= substr($code, 1);
    }

    if ($code =~ /^=/)
    {
      $pos= index($code,' ');
      $x= $lang{substr($code,0,$pos)};
# print "disp_F: x='$x'\n";
      $rv= $rv.$x;
      $code= ($pos == -1) ? '' : substr($code, $pos);
      next func;
    }

    $pos= index($code,' ');
    $x= substr($code,0,$pos);
# print "disp_F: def x='$x'\n";
    $rv= $rv.&disp_F_f($x);
    $code= ($pos == -1) ? '' : substr($code, $pos+1);
  }
  return $rv;
}

sub disp_F_f
{
  local($in)= $_[0];
  local($i);
  local($c)= '';
# print "disp_F_f: in=$in\n";
  for ($i=0; $i<length($in); $i++)
  {
    # $c= $c . '['.substr($in,$i,1).']';
    $c= $c . $func_code{substr($in,$i,1)};
  }
  return $c;
}
