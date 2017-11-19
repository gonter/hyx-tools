#!/usr/local/bin/perl
# FILE /usr/home/gonter/work/fbsd/gg/app/ned/x3.pl
#
# written:       2000-12-09
# latest update: 2000-12-09 13:44:38
#

while (<>)
{
  chop;
  if (/^(ned.*)\.o:$/)
  {
    $fnm= $1;
    ($module, $env)= split ('_', $fnm);
    $env= 'all' unless ($env);
    # print "module='$module' env='$env'\n";
    $MOD{$module}->{$env}= 1;
  }
}

my ($mod, $env);
foreach $mod (sort keys %MOD)
{
  my $mr= $MOD{$mod};
  my @e= sort keys %$mr;
  my $comment;
  $comment .= ' check' if (exists ($mr->{all})
                           && (exists ($mr->{tk}) || exists ($mr->{cur})));
  print join (' ', $mod, @e, $comment), "\n";
}
