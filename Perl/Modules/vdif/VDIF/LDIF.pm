#!/usr/local/bin/perl
# FILE %usr/unixonly/CPAN/vdif/VDIF/LDIF.pm
#
# written:       1998-09-13
# latest update: 1999-10-21 18:59:23
#
# $Id: LDIF.pm,v 1.3 2005/08/23 03:13:07 gonter Exp $
#

package VDIF::LDIF;

use strict;
use vars qw($VERSION @ISA @EXPORT_OK);
# use MIME::Media_Types qw(print_refs);
use VDIF::Entry;

require Exporter;

@ISA = qw(Exporter);
@EXPORT_OK = qw();
$VERSION = '0.01';

# ----------------------------------------------------------------------------
# create a new LDIF repository
# T2D: set up additional indexed, unique and not_null attributes
sub new
{
  my $class= shift;
  my $name= shift;      # just a name for the LDIF database

  my $obj=
  {
    name => $name,      # just a name
    not_null =>         # attributes which must be present
    {
      'dn' => {},
    },
    unique =>           # records indexed by unique attribute
    {
      'dn' => {},
    },
    indexed => {},      # records indexed by non-unique attribute
  };

  my ($mode, $arg);
  foreach $arg (@_)
  {
    if ($arg =~ /^-/)
    {
      if ($arg =~ /^-(indexed|unique|not_null)$/) { $mode= $1; }
      next;
    }
    $obj->{$mode}->{$arg}= {} if ($mode);
  }

  bless $obj, $class;
}

# ----------------------------------------------------------------------------
sub get_special_list
{
  my ($ldif, $where, $fld)= @_;

  my $index;

  return (defined ($index= %$ldif->{$where})
          && defined ($index= $index->{$fld})
         )
         ? $index : undef;
}

# ----------------------------------------------------------------------------
sub lookup_special_entry
{
  my ($ldif, $where, $fld, $value)= @_;

  my ($index, $ue);

  return (defined ($index= %$ldif->{$where})
          && defined ($index= $index->{$fld})
          && defined ($ue= $index->{$value})         # value present
         )
         ? $ue : undef;
}

# ----------------------------------------------------------------------------
sub lookup_unique
{
  my ($ldif, $fld, $value)= @_;
  &lookup_special_entry ($ldif, 'unique', $fld, $value);
}

# ----------------------------------------------------------------------------
sub lookup_dn
{
  my ($ldif, $fld, $value)= @_;
  &lookup_special_entry ($ldif, 'unique', 'dn', $value);
}

# ----------------------------------------------------------------------------
sub lookup_indexed
{
  my ($ldif, $fld, $value)= @_;
  &lookup_special_entry ($ldif, 'indexed', $fld, $value);
  # Note: returns an array reference!
}

# ----------------------------------------------------------------------------
# this one is cheap!
sub lookup_not_null
{
  my ($ldif, $fld, $value)= @_;
  &lookup_special_entry ($ldif, 'not_null', $fld, $value);
}

# ----------------------------------------------------------------------------
sub print_all
{
  my $ldif= shift;
  local (*FO)= shift;

  my $idx= $ldif->{not_null}; # just the first key will do
  my ($key)= keys (%$idx); # just the first key will do
  ### print ">> key=$key\n";
  
  my ($dn, $entry, $values);
  my $index= $idx->{$key};
  foreach $dn (keys %$index)
  {
    $values= $index->{$dn};
    foreach $entry (@$values)
    {
      ### print ">>> dn=$dn, entry=$entry\n"; &print_refs (*STDOUT, 'entry', $entry);
      $entry->print_ldif (*FO);
    }
  }
}

# ----------------------------------------------------------------------------
# add a LDIF entry to a LDIF database
sub add_entry
{
  my $ldif= shift;
  my $entry= shift;

  my ($fld, $index, $ue, $aref, $av);
  # check if required attributes are present and uniquenes is given
  my $errors= 0;
  foreach $fld (keys %{$ldif->{not_null}})
  {
    $index= $ldif->{not_null};
    unless (defined ($aref= $entry->{$fld})     # attribute is present
            && ($av= $aref->{value})            # value is defined
           )
    {
      print "ERROR: $ldif->{name} null value: $fld\n";
      $errors++;
    }
  }
  return undef if ($errors);

  $errors= 0;
  foreach $fld (keys %{$ldif->{unique}})
  {
    $index= $ldif->{unique};
    if (!defined ($aref= $entry->{$fld})        # attribute is present
        || $#{$aref->{values}} != 0             # only one value ...
        || !defined ($av= $aref->{value})       # ... is defined
        || defined ($ue= $index->{$av})         # value not already present
       )
    {
      print "ERROR: $ldif->{name} not unique: $fld=$av\n";
      $errors++;
    }
  }
  return undef if ($errors);

  # insert unique keys
  foreach $fld (keys %{$ldif->{unique}})
  {
    $index= $ldif->{unique}->{$fld};
    $aref= $entry->{$fld};         # attribute is present
    $av= $aref->{value};           # value is defined
    $index->{$av}= $entry;
  }

  &insert_index ($ldif, 'indexed',  $entry);
  &insert_index ($ldif, 'not_null', $entry);
  $entry;
}

# ----------------------------------------------------------------------------
sub insert_index
{
  my ($ldif, $what, $entry)= @_;

  # insert indexed keys
  my ($vref, $fld, $aref, $index, $av, $ue);
  foreach $fld (keys %{$ldif->{$what}})
  {
    next unless (defined ($aref= $entry->{$fld}));  # attribute is present
    $index= $ldif->{$what}->{$fld};
    foreach $vref (@{$aref->{values}})
    {
      $av= $vref->{v};
      $ue= $index->{$av}= [] unless (defined ($ue= $index->{$av}));
      push (@$ue, $entry);
    }
  }
}

# ----------------------------------------------------------------------------
# add the contents of LDIF stream to a LDIF database
sub add_file
{
  my $ldif= shift;
  my $fnm= shift;

  my @entries= &VDIF::parse_file ($fnm);
  my $entry;
  foreach $entry (@entries)
  {
    $ldif->add_entry ($entry);
  }

  @entries;
}

# ----------------------------------------------------------------------------
sub parse_stream
{
  local *FI= shift;             # already opened stream
  my $fnm= shift;               # used for error messages
  my $dn_suffix= shift;         # suffix for generated dn values

  my @entries;

  &parse_stream2 (*FI, $fnm, $dn_suffix, sub { push (@entries, @_); });

  return (wantarray) ? @entries : \@entries;
}

# ----------------------------------------------------------------------------
# T2D: options to limit number of lines, entries, bytes or such
sub parse_stream2
{
  local *FI= shift;             # already opened stream
  my $fnm= shift;               # used for error messages
  my $dn_suffix= shift;         # suffix for generated dn values
  my $cb= shift;                # callback to process entry

  $dn_suffix= ','.$dn_suffix if ($dn_suffix && !($dn_suffix =~ /^,/));

  print "parsing stream: cb='$cb'\n";

  my $line= 0;
  my @data= ();
  while (<FI>)
  {
    $line++;
    chomp;
    s/\015//g;

# print $line, " ", $_, "\n";
    next if (/^#/);     # comments are not defined in VDIF files!
    next if (/^\d+$/);  # optional ID line

    if (/^\s*$/)
    {
      my $entry= &parse_lines ($dn_suffix, \@data);
      if (defined ($entry))
      {
        &$cb ($entry);
      }
      $entry= undef;
      @data= ();
    }
    elsif (/^[ \t](.*)/)        # attribute value continuation
    {
      $data[$#data] .= $1;
    }
    elsif (/^\w+:/)
    {
      push (@data, $_);
    }
    else
    {
      print STDERR "LDIF error $fnm ($line): $_\n";
    }
  }

  if (@data)
  {
    my $entry= &parse_lines ($dn_suffix, \@data);
    &$cb ($entry) if (defined ($entry)); # process entry from last dn
  }

  $line;
}

sub parse_lines
{
  my $dn_suffix= shift;
  my $data= shift;

# print "parse_lines: dn_suffix=$dn_suffix data=$data ", $#$data, "\n";
  my $entry;
  local $_;
  foreach $_ (@$data)
  {
# print $_, "\n";
    if (/^(\w+)(\:\:?)[ \t]*(.*)/)     # attribute value in ascii format
    {
      my ($an, $ty, $av)= ($1, $2, $3); $an=~ tr/A-Z/a-z/;

      $ty= ($ty eq '::') ? 'base64' : undef;

      if ($an eq 'dn')
      {
        if ($ty eq 'base64')
        {
          print "ERROR: dn in base64 not supported! [$av]\n";
          return undef;
        }
        $av .= $dn_suffix if ($dn_suffix);
        $entry= new VDIF::Entry ($av, $ty);
        # push (@entries, $entry);
      }
      elsif (!$entry)
      {
	printf STDERR "WARNING: not a valid entry\n";
      }
      else
      {
        $entry->add_attribute ($an, $av, $ty);
      }
    }
    else
    {
      return undef;
    }
  }

  $entry;
}

1;
