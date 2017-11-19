#!/usr/local/bin/perl
# FILE %usr/unixonly/iris/hyxtest.pl
#
# written:       1996-10-09
# latest update: 1996-10-09 19:49:43
#

use hyx;

@TEST= ( '$$root', 'urxn444' );

$cluster= tie (%HYX, hyx, 'test.hyx');

print "cluster='$cluster'\n";
$last= hyx::last ($cluster);
print "last: $last\n";
$str= $HYX{'$$root'};
print "str='$str'\n";

foreach $frame (@TEST)
{
  $ex= exists ($HYX{$frame});
  $size= hyx::EXISTS ($cluster, $frame);
  print "exists: '$frame' -> $ex, $size\n";
}

$res= hyx::check ($cluster);
print "check: '$res'\n";

# $res= hyx::diag ($cluster);
$res= $cluster->diag;
print "diag: '$res'\n";

$HYX{'perl frame'}= <<EOF;
<Frame perl frame>
This is the PERL frame!
</Frame>
EOF
exit (0);

foreach $frame (sort keys %HYX)
{
  print "frame: '$frame'\n";
}

exit (0);
exit (0);




