#!/usr/local/bin/perl

@FLAGS= @ARGV;
while (<>)
{
  ($fnm)= split (':');
  $F{$fnm}->{$ARGV}= 'X';
}

  printf ("%-32s", 'Module');
  foreach $arg (@FLAGS)
  {
    printf ("%-10s", $arg);
  }
  print "\n";

foreach $fnm (sort keys %F)
{
  printf ("%-32s", $fnm);
  foreach $arg (@FLAGS)
  {
    printf (" %-12s", $F{$fnm}->{$arg});
  }
  print "\n";
}
