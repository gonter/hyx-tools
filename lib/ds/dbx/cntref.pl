#!/usr/local/bin/perl
# FILE %ds/dbx/cntref.pl
#
# written:       1996-11-26
# latest update: 1996-11-26 22:15:27
#

while (<>)
{
  chop;
  s/\015//g;

  if (/<refnum>(\d+)/)
  {
    $refnum= $1;
    $refnum= "0$refnum" if ($refnum < 10);
    $refnum{$refnum}++; 
  }
}

foreach $refnum (sort keys %refnum)
{
  $val= $refnum{$refnum};
  next unless ($val);
  print "[$refnum] $val\n";
}
