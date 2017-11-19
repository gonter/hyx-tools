#!/usr/local/bin/perl
# FILE .../net-freedb/lib/Net/freedb/catalog_entry.pm
#
# manage a catalog of freedb database files
#
# written: 2001-09-02
# re-issued as Net::freedb::* 2002-06-30
# $Id: catalog_entry.pm,v 1.1 2002/07/01 02:42:25 gonter Exp $
#

use strict;

package Net::freedb::catalog_entry;

# ----------------------------------------------------------------------------
sub new
{
  my $class= shift;
  my @fields= @_;
  my $entry= \@fields;
  bless $entry;
}

# ----------------------------------------------------------------------------
sub index       { &get_idx ($_[0], 0, $_[1]); }
sub mtime       { &get_idx ($_[0], 1, $_[1]); }
sub lmd_update  { &get_idx ($_[0], 2, $_[1]); }
sub rcs_update  { &get_idx ($_[0], 3, $_[1]); }
sub key         { &get_idx ($_[0], 4, $_[1]); }
sub title       { &get_idx ($_[0], 5, $_[1]); }

# ----------------------------------------------------------------------------
sub get_idx
{
  my $obj= shift;
  my $idx= shift;
  my $val= shift;

  my $res= $obj->[$idx];
  $obj->[$idx]= $val if (defined ($val));

  $res;
}

1;
