#!/usr/local/bin/perl
# FILE .../net-freedb/lib/Net/freedb/file.pm
#
# written:       2001-01-28
# re-issued as Net::freedb::* 2002-06-30
# $Id: local.pm,v 1.1 2012/08/12 16:32:56 gonter Exp $
#

=head1 NAME

Net::freedb::cdex - Perl module to hande freedb database files

=head1 SYNOPSIS

  use Net::freedb::dex;

  $cdex= new Net::freedb::dex;     create a new freedb object
  $cdex->read ($filename);          read a given freedb file into object

=head1 DESCRIPTION

Net::freedb::cdex 
files which represent freedb database files.

=cut

use strict;

package Net::freedb::cdex::local;

use Net::freedb::file;

my $VERSION= '0.03';

my $do_parse= 1;

sub new
{
  my $class= shift;
  my %pars= @_;

  my $obj=
  {
  };
  bless $obj;

  foreach my $par (keys %pars)
  {
    if ($par eq 'read')
    {
      $obj->read ($pars{$par});
    }
    else
    {
      $obj->{$par}= $pars{$par};
    }
  }

  $obj;
}

=pod

=head2 $cdex->read ($fnm)

CDex stores multiple freedb files in one file, e.g. classical/aa12b90a
and classcial/aa11741c end up together in a file called classical/aatoaa .

=cut

# ----------------------------------------------------------------------------
sub read
{
  my $obj= shift;
  my $fnm= shift;

  local *FI;
  open (FI, $fnm) || return 0;

  my %items= ();
  $obj->{'items'}= \%items;
  my $lines= undef;
  my $x_filename= undef;
  my $cnt= 0;
  while (my $l= <FI>)
  {
    chop ($l);

    if ($l =~ m/^#FILENAME=([a-fA-F0-9]{8})$/)
    {
      $x_filename= $1;
      print ">> x_filename=[$x_filename]\n";
      $lines= [];
      $items{$x_filename}= { 'filename' => $x_filename, '_' => $lines };
      $cnt++;
    }
    elsif (defined ($lines))
    {
      push (@$lines, $l);
    }
    else
    {
      # TODO: garbage in the file?
    }
  }
  close (FI);

  if ($do_parse)
  {
    foreach my $item (sort keys %items)
    {
      my $x= $items{$item};
      my $lines= $x->{'_'};
  
      my $fdb= $x->{'freedb'}= new Net::freedb::file;
  
      # $fdb->{'_FILENAME_'}= $fnm;
      $fdb->parse ($lines);
    }
  }

  #\%items;
  $cnt;
}

1;
__END__
# POD Section

=head1 NOTES

=head1 BUGS

This module is work in progres...

=head2 To-Do-List

  How to handle track information

=head1 Copyright

Copyright (c) 2012 Gerhard Gonter.  All rights reserved.
This is free software; you can redistribute it and/or modify
it under the same terms as Perl itself.

=head1 AUTHOR

Gerhard Gonter, g.gonter@ieee.org

=head1 SEE ALSO

=cut

