#!/usr/local/bin/perl
# FILE %usr/unixonly/CPAN/vdif-0.01/VDIF/TopCall.pm
#
# written:       1998-10-08
# latest update: 1998-10-08 11:57:55
#

package VDIF::TopCall;

use strict;
use vars qw($VERSION @ISA @EXPORT_OK);
use VDIF::Entry;

require Exporter;

@ISA = qw(Exporter);
@EXPORT_OK = qw();
$VERSION = '0.01';

# ----------------------------------------------------------------------------
sub new
{
  my $class= shift;
  my $name= shift;

  my $obj=
  {
  };
  bless $obj, $class;
}

# ----------------------------------------------------------------------------
sub parse_stream
{
  local (*FI)= shift;           # already opened stream
  my $fnm= shift;               # used for error messages

  my @L;
  my $LP= \@L;     # pointer to current container
  my @Stack;       # stack of entry container pointers;
  my $line;

  my ($type, $name, $val);
  my (%TYPES, %NAMES);

  while (<FI>)
  {
    $line++;
    chomp;
    s/\015//g;
    next if (/^#/);     # comments are not defined

# print ">$_<\n";
    if (/^\s*(\S+)\s*=\s*\($/)
    { # new structured entry
      $name= $1;
      ($type, $name)= split ('/', $name);
      ($name, $type)= ($type, '__list__') unless ($name);

      # insert the new structure into the current container
      my $nx_entry= { 'type' => $type, 'name' => $name, 'list' => []};
      push (@$LP, $nx_entry);

      # push the current pointers to the stack
# print ">>> $_ $#Stack $line\n";# if ($#Stack == -1);
      push (@Stack, $LP);
      $LP= $nx_entry->{list};

      $TYPES{$type}++;
      $NAMES{$name}++;
    }
    elsif (/^\s*\)(,|)$/)
    { # structure is completed, pop pointers from the stacks
# print "<<< $_ $#Stack $line\n";# if ($#Stack == -1);
      $LP= pop (@Stack);
    }
    elsif (/^\s*(\S+)\/(\S+)\s*=\s*((-|)\d+)(,|)$/
           || /^\s*(\S+)\/(\S+)\s*=\s*\"([^\"]*)\"(,|)$/
          )
    {
      ($type, $name, $val)= ($1, $2, $3);
      my $nx_entry= { 'type' => $type, 'name' => $name, 'val' => $val };
      push (@$LP, $nx_entry);
      $TYPES{$type}++;
      $NAMES{$name}++;
    }
    elsif (/^\s*(\S+)\/(\S+)\s*=\s*\(\)(,|)$/)
    {
      ($type, $name, $val)= ($1, $2, []);
      my $nx_entry= { 'type' => $type, 'name' => $name, 'list' => $val };
      push (@$LP, $nx_entry);
      $TYPES{$type}++;
      $NAMES{$name}++;
    }
    elsif (/^\s*(\S+)\s*=\s*\(\)(,|)$/)
    {
      ($type, $name, $val)= ('__list__', $1, []);
      my $nx_entry= { 'type' => $type, 'name' => $name, 'list' => $val };
      push (@$LP, $nx_entry);
      $TYPES{$type}++;
      $NAMES{$name}++;
    }
    else
    {
      print ">>> $_\n";
    }
  }

  foreach $type (sort keys %TYPES)
  {
    printf ("type: %7d %s\n", $TYPES{$type}, $type);
  }

  foreach $name (sort keys %NAMES)
  {
    printf ("name: %7d %s\n", $NAMES{$name}, $name);
  }

  \@L;
}

# ----------------------------------------------------------------------------
1;
