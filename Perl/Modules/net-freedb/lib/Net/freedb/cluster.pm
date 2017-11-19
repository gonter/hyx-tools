#!/usr/local/bin/perl
# FILE .../net-freedb/lib/Net/freedb/cluster.pm
#
# handle clusters of similar entries
# re-issued as Net::freedb::* 2002-06-30
#
# $Id: cluster.pm,v 1.2 2002/07/01 06:56:30 gonter Exp $

package Net::freedb::cluster;

my $VERSION= '0.02';
my $cluster_id= 1;

sub new
{
  my $class= shift;
  my $cat= shift;

  my $obj=
  {
    'id' => $cluster_id++,
    'cat' => $cat,
    'members' => {},
  };
  bless $obj;
}

# add an entry to a cluster
sub add
{
  my $obj= shift;
  my $id= shift;      # freedb id;
  my $data= shift;    # some data associated with it, e.g. a Net::freedb::file object

  $obj->{members}->{$id}= $data;
}

# merge the data of two clusters
sub merge
{
  my $obj1= shift;
  my $obj2= shift;
  my $mem;
  foreach $mem (keys %{$obj2->{members}})
  {
    $obj1->{members}->{$mem}= $obj2->{members}->{$mem};
  }
}

1;

