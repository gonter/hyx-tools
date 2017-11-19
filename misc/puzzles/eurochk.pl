#!/usr/bin/perl
# see http://www.wyae.de/docs/euroschein/

=head1 USAGE

test one serial number:

  ./eurochk.pl 'X30198131849'

test a pattern and find a valid serial number:

  ./eurochk.pl 'X30198?31849'
  ./eurochk.pl '?12345678901'

=cut

use strict;

use Data::Dumper;
$Data::Dumper::Indent= 1;

my $chatty= 1;

my %CC_Codes=
(
  'G' => 1, 'P' => 1, 'Y' => 1,
  'F' => 2, 'X' => 2,
  'E' => 3, 'N' => 3, 'W' => 3,
  'M' => 4, 'V' => 4,
  'L' => 5, 'U' => 5,
  'K' => 6, 'T' => 6,
  'J' => 7, 'S' => 7,
  'R' => 8,
  'H' => 9, 'Z' => 9,
);
my @CC_Codes= sort keys %CC_Codes;

unless (@ARGV)
{
  system ("perldoc $0");
  exit;
}

while (my $arg= shift (@ARGV))
{
  if ($arg =~ m#^[A-Z]\d{11}$#)
  {
    euro::checksum1 ($arg);
  }
  elsif ($arg =~ m#^[A-Z\?][\?\d]{11}$#)
  {
    $chatty= 0;
    euro::checksum_x (split ('|', $arg));
  }
  elsif ($arg eq 'valid:') {} # nop for feeding serial numbers back into script
  else
  {
    print "kein gueltiges Pattern [$arg]\n";
  }
}

sub test
{
  euro::checksum1 ('x30198131849');
}

package euro;

sub checksum_x
{
  my @num= @_;

  unless ($num[0] eq '?' || exists ($CC_Codes{$num[0]}))
  {
    print "invalid country code; allowd=", join (' ', @CC_Codes), "\n";
    return undef;
  }

  my @wildcards;
  my $num_wildcards= 0;

  for (my $i= 0; $i <= 11; $i++)
  {
    if ($num[$i] eq '?')
    {
      push (@wildcards, $i);
      $num_wildcards++;
    }
  }

  my $wc1= shift (@wildcards);

    if ($wc1 eq 0)
    {
      foreach my $j (@CC_Codes)
      {
        $num[$wc1]= $j;

        if (@wildcards)
        {
          checksum_x (@num);
        }
        else
        {
          my ($n, $v1, $v2)= checksum2 (@num);
  
          if ($v1 eq 'valid' && $v2 eq 'valid')
          {
            print "valid: $n\n";
          }
        }
      }
    }
    else
    {
      for (my $j= 0; $j <= 9; $j++)
      {
        $num[$wc1]= $j;
        if (@wildcards)
        {
          checksum_x (@num);
        }
        else
        {
          my ($n, $v1, $v2)= checksum2 (@num);
  
          if ($v1 eq 'valid' && $v2 eq 'valid')
          {
            print "valid: $n\n";
          }
        }
      }
    }
}

sub checksum1
{
  my $num= shift;

  my @num= split ('|', $num);
  $num[0]= chr(ord($num[0])-ord('a')+ord('A')) if ($num[0] gt 'a' && $num[0] <= 'z');

  unless (exists ($CC_Codes{$num[0]}))
  {
    print "invalid country code; allowd=", join (' ', @CC_Codes), "\n";
    return undef;
  }

  &checksum2 (@num);
}

sub checksum2
{
  my @num= @_;

  # print "num: ", join (' ', @num), "\n";
  my $num= join ('', @num);
  my ($xsum, $sum)= zsum (@num);
  my $sum_valid= ($sum == 8) ? 'valid' : 'invalid';
  print "num: ", join ('', @num, '=', $xsum, '=', $sum, '/', $sum_valid), "\n" if ($chatty);

  my $cc= shift (@num);
  my ($xsum, $sum)= zsum (@num);
  my $cc_valid= ($CC_Codes{$cc} == $sum) ? 'valid' : 'invalid';
  print "num: ", join ('', ' ', @num, '=', $xsum, '=', $sum, '/', $cc, '/', $cc_valid), "\n\n" if ($chatty);

  ($num, $sum_valid, $cc_valid);
}

sub zsum
{
  my @num= @_;

  my $sum= 0;
  for (my $i= 0; $i <= $#num; $i++)
  {
    my $n= $num[$i];
    if ($n ge 'A' && $n le 'Z') { $num[$i]= $n= ord ($n) - ord('A') + 1; }
    $sum += $n;
  }
  my $xsum= $sum;
  while ($sum >= 10)
  {
    $sum= ($sum%10) + int ($sum/10);
  }

  ($xsum, $sum);
}

