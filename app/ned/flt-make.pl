#!/usr/local/bin/perl

use strict;

while (<>)
{
  s#\&#\&amp;#g;
  s#<#\&lt;#g;
  s#>#\&gt;#g;

  if (m#(.+):(\d+): (error|warning)#)
  {
    my ($fnm, $line, $type)= ($1, $2, $3);
    my $lng= length ($fnm) + length($line) + 1;

    $fnm= $1 .'/'.$fnm if ($fnm =~ /^ned(\d\d)/);

    $_= "<hyx.l file=\"$fnm\" ln=$line tdc=79 tdp=$lng>" . $_;
  }
  print $_;
}
