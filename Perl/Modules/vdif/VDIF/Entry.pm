#!/usr/local/bin/perl
# FILE %usr/unixonly/CPAN/vdif-0.01/VDIF/Entry.pm
#
# written:       1998-09-13
# latest update: 1998-09-13 12:21:08
# $Id: Entry.pm,v 1.1 2004/08/19 02:12:36 gonter Exp $
#

package VDIF::Entry;

use strict;
use vars qw($VERSION @ISA @EXPORT_OK);

require Exporter;

@ISA = qw(Exporter);
@EXPORT_OK = qw();
$VERSION = '0.02';
my $MAX_LINE_SIZE= 71;

# ----------------------------------------------------------------------------
# create a new VDIF entry
sub new
{
  my $class= shift;
  my $dn= shift;
  my %attrs= @_;

  my $obj= {};
  bless $obj;

  $obj->add_attribute ('dn', $dn) if ($dn);

  my $attr;
  foreach $attr (keys %attrs)
  {
    $obj->add_attribute ($attr, $attrs{$attr});
  }

  $obj;
}

# ----------------------------------------------------------------------------
sub update
{
  my $obj= shift;
  my %attrs= @_;

  my $attr;
  foreach $attr (keys %attrs)
  {
    $obj->add_attribute ($attr, $attrs{$attr});
  }

  $obj;
}

# ----------------------------------------------------------------------------
sub add_attribute
{
  my ($entry, $name, $value_list, $type, $mod)= @_;

  $name=~ tr/A-Z/a-z/;
  my ($value, $aref, $vref);
  if (ref ($value_list) eq 'ARRAY')
  {
    $value= $value_list->[0];
  }
  else
  {
    $value= $value_list;
  }

  unless (defined ($aref= $entry->{$name}))
  {
    $aref= $entry->{$name}= { name => $name, value => $value, values => [] };
  }

  if (ref ($value_list) eq 'ARRAY')
  {
    foreach $value (@$value_list)
    {
      push (@{$aref->{values}}, $vref= { 'v' => $value });
    }
  }
  else
  {
    push (@{$aref->{values}}, $vref= { 'v' => $value_list });
  }

  $vref->{t}= $type if ($type);
  $vref->{'mod'}= $mod if (defined ($mod));
  $vref;
}

# ----------------------------------------------------------------------------
sub contains
{
  my ($entry, $aname, $avalue)= @_;
  my ($aref, $av);
  $aname=~ tr/A-Z/a-z/;

  return 0 unless (defined ($aref= $entry->{$aname}));
  return 0 unless (defined ($aref= $aref->{values}));
  foreach $av (@$aref)
  {
    return 1 if ($av->{v} eq $avalue);
  }
  return 0;
}

# ----------------------------------------------------------------------------
sub values
{
  my ($entry, $aname)= @_;
  my ($aref);
  $aname=~ tr/A-Z/a-z/;

  return undef unless (defined ($aref= $entry->{$aname}));
  return undef unless (defined ($aref= $aref->{values}));

  return $aref unless (wantarray);

  # calling function wants just the attribute values...
  my ($av, @values);
  foreach $av (@$aref)
  {
    push (@values, $av->{v});
  }
  @values;
}

# ----------------------------------------------------------------------------
sub value_ref
{
  my ($entry, $aname, $num)= @_;
  my ($aref);
  $aname=~ tr/A-Z/a-z/;

  return undef unless (defined ($aref= $entry->{$aname}));
  return undef unless (defined ($aref= $aref->{values}));
  $aref->[$num];
}

# ----------------------------------------------------------------------------
sub value
{
  my $vref= value_ref (@_);
  defined ($vref) ? $vref->{v} : undef;
}

# ----------------------------------------------------------------------------
# print an entry in LDIF format
sub print_ldif
{
  my $entry= shift;
  local *FO= shift || *STDOUT;
  my $id= shift;

  print FO $id, "\n" if ($id);
  &print_attribute_ldif (*FO, 'dn', ':', $entry->{dn}->{value});
  my ($an, $aref, $vref);
  foreach $an (sort keys %$entry)
  {
    next if ($an eq 'dn');
    $aref= $entry->{$an};
    foreach $vref (@{$aref->{values}})
    {
      if ($vref->{t} eq 'base64')
      {
        &print_attribute_ldif (*FO, $an, '::', $vref->{v});
      }
      else
      {
        &print_attribute_ldif (*FO, $an, ':', $vref->{v});
      }
    }
  }
  print FO "\n";
}

# ----------------------------------------------------------------------------
# print exactly one attribute name and value pair in LDIF format,
# wrap lines longer than $MAX_LINE_SIZE (72) characters as continuation records
sub print_attribute_ldif
{
  local (*FO)= shift;
  my ($an, $delimiter, $av)= @_;
  my ($lng, $ml);

  print FO $an, $delimiter;
  $lng= length ($an) + length ($delimiter);

  while ($av)
  {
    $ml= length ($av);
    if ($lng + $ml <= $MAX_LINE_SIZE)
    {
      print FO ' ', $av, "\n";
      last;
    }

    $ml= $MAX_LINE_SIZE - $lng;
    print FO ' ', substr ($av, 0, $ml), "\n";
    $av= substr ($av, $ml);
    $lng= 0;
  }
}

# ----------------------------------------------------------------------------
sub set_MAX_LINE_SIZE
{
  my $o= shift;
  my $n= shift;
  my $res= $MAX_LINE_SIZE;
  $MAX_LINE_SIZE= $n if ($n > 0);

  $res;
}

# ----------------------------------------------------------------------------
1;
