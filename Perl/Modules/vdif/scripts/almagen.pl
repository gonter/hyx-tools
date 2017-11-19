#!/usr/local/bin/perl
# FILE .../CPAN/ldif/cookieflt.pl
#
# filter out old items from a cookie database
#
# written:       1998-09-01
# latest update: 1999-06-14 14:55:56
#

use lib '.';
use VDIF;

$fnm_in= shift (@ARGV) || die "need input LDIF file";
$domain= shift (@ARGV) || die "need domain name";

$ldif= new VDIF::LDIF ('cookie-db');

@entries= $ldif->add_file ($fnm_in);
@filtered= ();

my $now= time;
foreach $entry (@entries)
{
  # $entry->print_ldif (*STDOUT);

  my $oc= $entry->value ('objectclass', 0);
  next unless ($oc eq 'personalalias');
  my $lhs= $entry->value ('lhs', 0);
  my $rhs= $entry->value ('rhs', 0);
  print "$lhs\@$domain\t$rhs\n";
}

foreach $entry (@filtered)
{
}


