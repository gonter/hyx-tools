#!/usr/local/bin/perl
#
# FILE rfc2hyx.awk
#
# reformat a streamed RFC into HYX format
#
# written:       1994-04-15
#                1995-07-14: rewritten from AWK to Perl
# latest update: 1995-07-14
# $Id: rfc2hyx.pl,v 1.2 2012/08/10 15:21:00 gonter Exp $
#
# ----------------------------------------------------------------------------

use strict;

# $fnm_top= 'tmp/@1.t';
# $fnm_hyx= 'tmp/@1.h';
# $fnm_crf= 'tmp/@1.c';


# cross references
my $server= 'http://www.wu-wien.ac.at:8082/rfc/';
my $server2= 'http://www.wu-wien.ac.at:8082/rfc/rfc';

my @RFCs;

while (my $arg= shift (@ARGV))
{
  if ($arg =~ /^-/)
  {
    &usage;
  }
  else
  {
    push (@RFCs, $arg);
  }
}

while (my $arg= shift (@RFCs))
{
  &convert_rfc ($arg);
}

exit(0);

sub convert_rfc
{
  my $fnm= shift;

  my $rfc_name;

  if ($fnm =~ /(RFC\d+)\.(txt|tmp)/i) { $rfc_name= $1; }

  unless ($rfc_name)
  {
    print "no RFC name dedected in [$fnm]\n";
  }

  print "converting RFC [$rfc_name]\n";

  my $fnm_top= $rfc_name .'.top';
  my $fnm_hyx= $rfc_name .'.hyx';

  open (FNM_TOP, '>' . $fnm_top);
  open (FNM_HYX, '>' . $fnm_hyx);
  # open (FNM_CRF, '>' . $rfc_name .'.crf');
  print FNM_TOP "<Frame \$\$root>\n";

  open (FI, $fnm) or die;

  # variables for the state engine
  my $st= 0;
  my $st2= 0;

  my $frame_open= 0;
  my $frame_counter= 0;
  my $frame_name= '';
  my $last_frame= '$$root';

line: while (<FI>)
{
  chop;

  $st= 1 if (/^Status of [Tt]his [Mm]emo$/
      || /^Status of the Memo$/
      || (/^Abstract/ && $rfc_name eq 'rfc1305')
      || /^1./ && /Status of this Memo$/i
      || /^Status of [Tt]his [Dd]ocument$/i);
  $st= 2 if (/^Appendix/);

  s/&/&amp;/g;
  s/</&lt;/g;
  s/>/&gt;/g;

  my @Fld= split(' ', $_, 9999);

  if ($st == 0)
  {
    s/(RFC[ \-]{0,1}(\d+))/<a href=$server2$2.hyx\/\$\$root>$1<\/a>/g;
    print FNM_TOP $_."\n";
    next line;
  }

  my $is_new_frame= 0;

  $is_new_frame= 1
    if ($_ ne ''
        && $st == 1
        && (!((substr($_, 0, 1) =~ /[ \t\*&\+\-\"\{\}\<>\[\]]/)
             || /\|/
             || /--/ || /^RFC-/
             || /^Help: / || /^Retrieve: / || /^List: / || /^Record lease,/)));

  if ($st == 1
      && ($rfc_name eq 'rfc1800' || $rfc_name eq 'rfc1035' || $rfc_name eq 'rfc1305'
          || $rfc_name eq 'rfc1034' || $rfc_name eq 'rfc1123'))
  {
    $is_new_frame= (/^[ ]*[\d\.]+\. /) ? 1 : 0;
  }

  if ($st == 1
      && ($rfc_name eq 'rfc1006' || $rfc_name eq 'rfc1801' || $rfc_name eq 'rfc1804'
          || $rfc_name eq 'rfc1738'))
  {
    $is_new_frame= (/^[\d\.]+\. /||/^[A-Z] /) ? 1 : 0;
  }

  if ($st == 1 && ($rfc_name eq 'rfc1807' || $rfc_name eq 'rfc1357'))
  {
    $st2= 1 if (/EXAMPLE$/);
    $st2= 0 if (/End of Example/);
    $is_new_frame= 0 if ($st2 == 1 || /^WITHDRAW/ || / -- /);
  }

  if ($st == 2)
  { # in the appendix only match on boundaries
    $is_new_frame= (/Appendix/) ? 1 : 0;
  }

  if ($is_new_frame == 1)
  { # a new section means a new frame
    # find out which section this is and generate a new frame name
    my $section= $_;
    print "section: [$section]\n";

    $frame_name= "$rfc_name.$frame_counter";
    $frame_counter++;
    for (my $i= 0; $i <= $#Fld; $i++)
    {
      $frame_name= $frame_name . ' ' . $Fld[$i];
    }

    # print closing info into previous frame
    if ($frame_open == 1)
    {
      print FNM_HYX "<hyx.l fr=\"$frame_name\" dir=next></Frame>\n";
    }

    # print opening info into new frame
    print FNM_HYX "<Frame $frame_name>";
    print FNM_HYX "<hyx.l fr=\"$last_frame\" dir=prev>";
    print FNM_HYX "<hyx.l fr=\"\$\$root\" dir=up>\n";
    print FNM_HYX "<title>$section</title>\n";
    print FNM_HYX "<h2>$section</h2>\n";

    # print a link into the $$root frame
    print FNM_TOP "<hyx.l fr=\"$frame_name\" tdc=31";
    print FNM_TOP ' dir=next' if ($frame_counter == 1);
    print FNM_TOP ' tdp='.length($section).'>'.$section."\n";

    $frame_open= 1;
    $last_frame= $frame_name;
    next line;
  } # End of processing new frame begin

  s/((ftp|http|gopher|news|mailto):[A-Za-z0-9@\/\-\$\?\.\%_:~]*[A-Za-z0-9@\/\-\$\?\%_:~])/<a href=$1>$1<\/a>/g;
  s/(RFC[ \-]{0,1}(\d+))/<a href=$server2$2.hyx\/\$\$root>$1<\/a>/g;

  print FNM_HYX $_, "\n";
} # end while(<FI>);
close (FI);

# END of input stream:
printf FNM_HYX "<hyx.l fr=\"\$\$root\" dir=next></Frame>\n"
  if ($frame_open == 1);

# write final links etc to the $$root frame
print FNM_TOP "<hyx.l fr=\"$last_frame\" dir=prev>\n";
print FNM_TOP "<hyx.l fr=\"\$\$index\" tdp=7>\$\$index\n";
# print FNM_TOP "<hyx.l fr=\"$$notes\" tdp=7>$$notes";
# print FNM_TOP ", e.g. bookmarks and annotations";
print FNM_TOP "</Frame>\n";

# write a dummy $$notes frame
print FNM_TOP "<Frame \$\$notes>\n";
print FNM_TOP "* latest stop\n";
print FNM_TOP "</Frame>\n";
  close (FNM_TOP);

  open (FNM_TOP, $fnm_top) or die;
  while (<FNM_TOP>)
  {
    print FNM_HYX $_;
  }
  close (FNM_TOP);
  close (FNM_HYX);
  # close (FNM_CRF);

  system ("chksgml $fnm_hyx");
  system ("hyxidx -i $fnm_hyx");
}

