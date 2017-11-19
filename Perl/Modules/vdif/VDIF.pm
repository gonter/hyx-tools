#!/usr/local/bin/perl
# FILE %usr/unixonly/hp200lx/VPAN/vdif/LDIF.pm
#
# implements packages VDIF::LDIF and VDIF::Entry;
# see POD Section
#
# written:       1998-08-09
# latest update: 1998-10-08 11:57:40
# $Id: VDIF.pm,v 1.3 2011/05/31 15:37:57 gonter Exp $
#

package VDIF;

use strict;
use vars qw($VERSION @ISA @EXPORT_OK);
# use MIME::Media_Types qw(print_refs);

require Exporter;

@ISA = qw(Exporter);
# Items to export into callers namespace by default. Note: do not export
# names by default without a very good reason. Use EXPORT_OK instead.
# Do not simply export all your public functions/methods/constants.
@EXPORT_OK = qw();
$VERSION = '0.03';

use VDIF::LDIF;
use VDIF::Entry;
use VDIF::vCx;
use VDIF::TopCall;

# ----------------------------------------------------------------------------
sub parse_file
{
  my $fnm= shift;
  my $fmt= shift || 'ldif';
  my $dn_suffix= shift;

  my @entries= ();
  local (*FI);
  unless (open (FI, $fnm))
  {
    print "can't parse $fnm\n";
    return ();
  }

  if ($fmt eq 'ldif')
  {
    @entries= &VDIF::LDIF::parse_stream (*FI, $fnm, $dn_suffix);
  }
  elsif ($fmt eq 'vcx' || $fmt eq 'vcard' || $fmt eq 'vcalendar')
  {
    @entries= &VDIF::vCx::parse_stream (*FI, $fnm, $dn_suffix);
  }
  elsif ($fmt eq 'TopCall')
  {
    @entries= &VDIF::TopCall::parse_stream (*FI, $fnm);
  }
  else
  {
    print "WARNING: VDIF::parse_file; unknown \$fmt='$fmt'\n";
  }

  close (FI);

  return (wantarray) ? @entries : \@entries;
}

# ----------------------------------------------------------------------------
# Autoload methods go after =cut, and are processed by the autosplit program.

1;
__END__
# Below is the stub of documentation for your module. You better edit it!
# POD Section

=head1 NAME

VDIF - Perl module to manipulate VDIF files and entries

  ** WARNING ** (1998-09-13 12:32:29)
  The information here may be inconsistent due to major restructuring

=head1 SYNOPSIS

  use VDIF;

VDIF::LDIF methods on DB level:
  These method operate on LDIF database which is held in memory
  $ldif= new VDIF::LDIF;
  $entry= $ldif->add_entry ($entry);
  @entries= $ldif->add_file ($file_name);
  @entries= $ldif->print_all (*FH);
  $entry= $ldif->lookup_dn ($dn);
  $entry= $ldif->lookup_unique ($attribute, $value);
  $entry= $ldif->lookup_indexed ($attribute, $value);
  $entry= $ldif->lookup_not_null ($attribute, $value);
  T2D: $entry= $ldif->get_entry_by_dn ($dn);

VDIF::Entry methods:
  These functions operate at the entry level.
  $entry= new LDIF::Entry ($dn, %attributes);
  $entry->update (%attributes);
  $attribute_ref= $entry->add_attribute ($name, $value [, $type [, $mod]]);
  $entry->print_ldif (*FH);

VDIF utility functions:
  @entries= VDIF::Entry::parse_file ($file_name);

VDIF::LDIF utitlity functions:
  @entries= VDIF::LDIF::parse_stream (*FH);

=head1 ENTRY STRUCTURE

 Entries are references to hashes consisting of named attributes.
 Each attribute is basically a name and a list of values.  Each
 value may have an optional scalar type and a optional reference
 to a hash of modifiers.

 *THIS* entry structure is used for LDIF as well as vCard, vCalendar
 data storage.

 Each attribute has the following structure:

 $attribute=
 {
   'name'       => $string,     # attribute name
   'value'      => $string,     # first attribute value, string only
   'values'     =>              # list of all attribute values
   [
     {
       'v'      => $value,      # actual attribute value
       't'      => $type,       # OPTIONAL attribute type, e.g. 'base64'
       'mod'    => {},          # OPTIONAL attribute modifiers,
     },                         # repeated 1..n times
   ]
   'group'      => {},          # OPTIONAL grouped properties
 };

 Modifiers are name value pairs and are mainly used to encode
 information about properties.

 $modifier=
 {
   'n'          => $name,       # modifier name
   'v'          => $value,      # modifier value
 },

 Grouped properties are defined in the vCard (section 2.1.4.2)
 specification and are used to capture items that belong together.
 The field 'group' is a reference to hash containing againg
 LDIF entry attributes, keyed by attribute name.  This definition
 is basically recursive, however, the vCard specification does
 not mention recursion.

=head1 DESCRIPTION

Stub documentation for LDIF was created by h2xs.

=head1 Internal Note

=head1 T2D

  encoding, decoding, checking of binary values

=head1 Copyright

  Copyright (c) 1998 Gerhard Gonter.  All rights reserved.
  This is free software; you can redistribute it and/or modify
  it under the same terms as Perl itself.

=head1 AUTHOR

  Gerhard Gonter, g.gonter@ieee.org or gonter@wu-wien.ac.at

=head1 SEE ALSO

  http://falbala.wu-wien.ac.at:8684/pub/english.cgi/0/24065
  perl(1).


=cut
