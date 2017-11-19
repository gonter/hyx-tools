#!/usr/local/bin/perl
# FILE %gg/work/fbsd/gg/CPAN/vdif/scripts/cookiefilt2.pl
#
# written:       2003-03-06
# latest update: 2003-03-06 16:38:56
# $Id: cookiefilt2.pl,v 1.1 2004/08/19 02:12:36 gonter Exp $
#

use strict;

use lib '.';
use VDIF;

my $fnm_in= shift (@ARGV) || die "need input LDIF file";
my $fnm_out= shift (@ARGV) || '@cookiefilt-out.ldif';

my $now= time ();
my $count_analyzed= 0;
my $count_used= 0;

&perform_filtering ($fnm_in, $fnm_out);
printf ("filter: %6d %6d\n", $count_analyzed, $count_used);

exit (0);

sub perform_filtering
{
  my $fnm_in= shift;
  my $fnm_out= shift;

  local (*FI, *FO);
  open (FI, $fnm_in) || die;
  open (FO, ">$fnm_out") || die;

  &VDIF::LDIF::parse_stream2 (*FI, $fnm_in, '', sub { &filter_ldif_entry ($_[0], *FO); } );
  close (FI);
  close (FO);
}

sub filter_ldif_entry
{
  my $entry= shift;
  local *FO= shift;

  my $use= 0;
  $count_analyzed++;

  my ($dn, $vll);
  if ($entry->contains ('objectclass', 'cookie')
      && $entry->contains ('state', 'good')
      && $entry->value ('expires', 0) > $now
     )
  { # good cookie which expires sometime in the future!
    $use= 1;
  }
  elsif ($entry->contains ('objectclass', 'prefs')
         && ($dn= $entry->value ('dn', 0))
         && ($dn=~ /,cm=qdpop,/)
        )
  { # Preferences fuer den Web Popper
    unless (defined ($vll= $entry->values ('cm')))
    { # zusaetzliches Attribut einfuegen, falls nicht schon vorhanden
      $entry->add_attribute ('cm', 'qdpop');
    }
    $use= 1;
  }

  if ($use)
  {
    $entry->print_ldif (*FO);
    $count_used++;
  }

  printf ("filter: %6d %6d\n", $count_analyzed, $count_used)
          if (($count_analyzed % 100) == 0);
}



