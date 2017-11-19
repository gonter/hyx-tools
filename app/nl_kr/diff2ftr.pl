#
# FILE %ta/diff2ftr.pl
#
# rewrite diff listing into hyx format for cross ref reading
#
# written:       1995-05-25
# latest update: 1995-05-26
#

open (LEFT,  ">_bak_ftr.ned/@left.ftr");
open (RIGHT, ">_bak_ftr.ned/@right.ftr");
print LEFT  "0 6 9 0 10 1 1 32760\n";
print RIGHT "0 6 9 0 10 1 1 32760\n";

while (<>)
{
  next if (/^< /||/^> /||/^---/);
  chop;

  $l_r1= $l_r2= 0;
  $l_l1= $l_l2= 0;
  $l_l= '';
  $l_r= '';
  $c= '';

  if (/a/)
  {
    ($l_l, $l_r)= split ('a');
    ($l_r1, $l_r2)= split (',', $l_r);
    $c= 'a';
  }

  if (/d/)
  {
    ($l_l, $l_r)= split ('d');
    ($l_l1, $l_l2)= split (',', $l_l);
    $c= 'd';
  }

  if (/c/)
  {
    ($l_l, $l_r)= split ('c');
    ($l_l1, $l_l2)= split (',', $l_l);
    ($l_r1, $l_r2)= split (',', $l_r);
    $c= 'c';
  }

  # print "$_:  l=$l_l  r=$l_r  l1=$l_l1  l2=$l_l2  r1=$l_r1  r2=$l_r2\n";
  $l_l2= $l_l1 if ($l_l1 ne '' && $l_l2 eq '');
  $l_r2= $l_r1 if ($l_r1 ne '' && $l_r2 eq '');
  print "$_:  l=$l_l  r=$l_r  l1=$l_l1  l2=$l_l2  r1=$l_r1  r2=$l_r2\n";

  if ($l_r2 > 0)
  {
    for ($i= $l_r1; $i <= $l_r2; $i++)
    {
      print RIGHT "$i 0 1 <hyx.l tdc=12 tdp=78 name=\"$_\" file=\"@left\">\n";
    }
  }

  if ($l_l2 > 0)
  {
    for ($i= $l_l1; $i <= $l_l2; $i++)
    {
      print LEFT "$i 0 1 <hyx.l tdc=12 tdp=78 name=\"$_\" file=\"@right\">\n";
    }
  }

  print "$_\n" if ($c eq '');
}

close (LEFT);
close (RIGHT);
