#!/usr/local/bin/perl
# FILE .../net-freedb/lib/Net/freedb/track.pm
#
# written:       2001-03-03
# re-issued as Net::freedb::* 2002-06-30
# $Id: track.pm,v 1.2 2002/07/01 06:56:30 gonter Exp $
#

use strict;
package Net::freedb::track;

# ----------------------------------------------------------------------------
my $VERSION= '0.02';

# ----------------------------------------------------------------------------
sub offset      { my $obj= shift; $obj->_field_ ('offset',      @_); }
sub title       { my $obj= shift; $obj->_field_ ('TTITLE',      @_); }
sub ext         { my $obj= shift; $obj->_field_ ('EXTT',        @_); }

# ----------------------------------------------------------------------------
sub new
{
  my $class= shift;
  my %pars= @_;
  my $obj=
  {
    'offset' => 0,
    'TITLE' => '',
    'EXTT' => '',
  };
  foreach (keys %pars) { $obj->{$_}= $pars{$_}; }
  bless $obj;
}

# ----------------------------------------------------------------------------
sub _field_
{
  my $obj= shift;
  my $field= shift;
  my $val= shift;
  my $old= $obj->{$field};
  $obj->{$field}= $val if ($val);
  $old;
}
