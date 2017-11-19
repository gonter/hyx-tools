#!/usr/local/bin/perl
# FILE .../CPAN/vdif/scripts/cookieflt.pl
#
# filter out old items from a cookie database
#
# written:       1998-09-01
# latest update: 1999-06-14 14:55:56
# $Id: cookieflt.pl,v 1.1 2004/08/19 02:12:36 gonter Exp $
#

use lib '.';
use VDIF;

$fnm_in= shift (@ARGV) || die "need input LDIF file";

$ldif= new VDIF::LDIF ('cookie-db');

@entries= $ldif->add_file ($fnm_in);
@filtered= ();

my $now= time;
foreach $entry (@entries)
{
  # $dn= $entry->value ('dn', 0);
  # print ">> dn: $dn\n";

  if ($entry->contains ('objectclass', 'cookie')
      && $entry->contains ('state', 'good')
      && $entry->value ('expires', 0) > $now
     )
  { # good cookie which expire sometime in the future!
    push (@filtered, $entry);
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

    push (@filtered, $entry);
  }
}

foreach $entry (@filtered)
{
  $entry->print_ldif (*STDOUT);
}


