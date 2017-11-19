#!/usr/local/bin/perl
# FILE .../net-freedb/lib/Net/freedb/tools.pm
#
# written:       2001-05-01
# re-issued as Net::freedb::* 2002-06-30
# $Id: tools.pm,v 1.2 2002/07/01 06:56:30 gonter Exp $
#

use strict;
use MD5;

package Net::freedb::tools;

my $VERSION= '0.02';

# ----------------------------------------------------------------------------
sub offset2time
{
  my $offset= shift;
  my $f= $offset % 75; $offset= int ($offset / 75);
  my $s= $offset % 60;
  my $m= int ($offset / 60);
  ($m, $s, $f);
}

# ----------------------------------------------------------------------------
# calculate an experimental alternative disc id
sub get_exp_id
{
  my $db= shift;

  my $cnt= $db->track_count;

  my $str= '';

  my ($i, $off0);
  for ($i= 0; $i < $cnt; $i++)
  {
    my $track= $db->track ($i); # returns a Net::freedb::track object
    my $off= $track->offset;
    $off0= $off if ($i == 0);
    $str .= $off . '+';
  }

  # unfortunately, we do not have disc length in frames!
  my $tt= 75 * $db->length + $off0;
  $str .= $tt;

  my $md5= MD5->hexhash ($str);

  $md5;
}

# ----------------------------------------------------------------------------
1;
