#!/usr/local/bin/perl
# FILE .../net-freedb/lib/Net/freedb/file.pm
#
# written:       2001-01-28
# re-issued as Net::freedb::* 2002-06-30
# $Id: file.pm,v 1.3 2012/08/12 16:30:13 gonter Exp $
#

=head1 NAME

Net::freedb::file - Perl module to handle freedb database files

=head1 SYNOPSIS

  use Net::freedb::file;

  $db= new Net::freedb::file;     create a new freedb object
  $db->read ($filename);          read a given freedb file into object
  $db->print (*FILEHANDLE);       print object in freedb file format
  $db->inc_revision;              increment revision counter

  Methods for field retrieval:
  $db->program ([<str>]);         retrieve or set program identifier
  $db->header ([<str>]);          retrieve or set freedb file header

  more functions
  discids                       all discids (ARRAY reference!)
  track (idx, <obj>)            track object at that position
  length                        length in seconds
  revision                      db file revision number
  title                         full title
  ext                           extended information
  playorder

  methods of a track object:
  offset                        start of track, counted in frames
  title                         full title
  ext                           extended information

=head1 DESCRIPTION

Net::freedb::file and it's sister-modules are used to handle text
files which represent freedb database files.

=cut

use strict;

package Net::freedb::file;

use Net::freedb::track;

# ----------------------------------------------------------------------------
my $VERSION= '0.03';
my $LLNG= 64;   # max. length of a line in the freedb file

my $default_header => <<EOX;
# xmcd CD database file
#
EOX

my %ESCAPE=
(
  'n' => "\n", 
  't' => "\t", 
);

# ----------------------------------------------------------------------------
sub new
{
  my $class= shift;
  my %pars= @_;

  my $obj=
  {
    'header' => $default_header,
    'revision' => 0,
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

# ----------------------------------------------------------------------------
sub read
{
  my $obj= shift;
  my $fnm= shift;

  local *FI;
  open (FI, $fnm) || return 0;
  my @lines= <FI>;
  close (FI);
  chop (@lines);

  $obj->{'_FILENAME_'}= $fnm;
  $obj->parse (\@lines);
}

sub parse
{
  my $obj= shift;
  my $lines= shift;

  my @lines= @$lines;

  my $state= 'header';
  my @tracks= ();
  $obj->{tracks}= \@tracks;
  $obj->{discid}= [];
  my $hdr= '';

  while (my $l= shift (@lines))
  {
    # print ">>> [$l]\n";

    if ($l =~ /^# Track frame offsets:/)
    {
      $state= 'track offsets';
    }
    elsif ($state eq 'header') { $hdr .= $l. "\n"; }
    elsif ($state eq 'track offsets' && $l =~ /^#\s*(\d+)/)
    {
      my $track= new Net::freedb::track
      (
        'offset' => $1,
      );
      push (@tracks, $track);
    }
    elsif ($l =~ /^#\s*$/) { $state= 'rest'; }
    elsif ($l =~ /^# Disc length: (\d+) seconds/)     { $obj->{length}= $1; }
    elsif ($l =~ /^# Revision: (\d+)/)                { $obj->{revision}= $1; }
    elsif ($l =~ /^# Submitted via: (.+)/)            { $obj->{program}= $1; }
    elsif ($l =~ /^DISCID=(.*)/)
    { # see the note about DISCID in the POD section below
      push (@{$obj->{discid}}, split (/,/, $1));
    }
    elsif ($l =~ /^(DTITLE|EXTD|PLAYORDER|DGENRE|DYEAR)=(.*)/)
    {
      my ($par, $val)= ($1, $2);
      $obj->{$par} .= $2;
    }
    elsif ($l =~ /^(TTITLE|EXTT)(\d+)=(.*)/)
    {
      my ($par, $idx, $val)= ($1, $2, $3);
      my $t= $obj->{tracks}->[$idx];
      $t->{$par} .= $3;
    }
  }
  $obj->{header}= $hdr;

  my ($xt, $xf);
  foreach $xf (qw(DTITLE EXTD PLAYORDER DGENRE DYEAR))
  {
    $obj->{$xf}= &decode ($obj->{$xf});
  }
  foreach $xt (@{$obj->{tracks}})
  {
    $xt->{TTITLE}= &decode ($xt->{TTITLE});
    $xt->{EXTT}= &decode ($xt->{EXTT});
  }

  1;
}

# ----------------------------------------------------------------------------
sub print
{
  my $obj= shift;
  local *FO= shift;

  print FO $obj->{header};
  print FO "# Track frame offsets:\n";
  my $track;
  foreach $track (@{$obj->{tracks}})
  {
    printf FO ("#\t%d\n", $track->{offset});
  }
  print FO "#\n# Disc length: ", $obj->{length}, " seconds\n#\n",
           "# Revision: ", $obj->{revision},
           "\n# Submitted via: ", $obj->{program}, "\n#\n";

  # print the DISCID
  # see the note about DISCID in the POD section below
  my @discids= @{$obj->{discid}};
  while ($#discids >= 7)
  {
    my @x= @discids[0..7];
    @discids= @discids[8..$#discids];
    print FO "DISCID=", join (',', @x), "\n";
  }
  print FO "DISCID=", join (',', @discids), "\n";

  &print_field (*FO, 'DTITLE', $obj->{DTITLE});
  &print_field (*FO, 'DYEAR',  $obj->{DYEAR});
  &print_field (*FO, 'DGENRE', $obj->{DGENRE});
  my $num= 0;
  foreach $track (@{$obj->{tracks}})
  {
    &print_field (*FO, "TTITLE$num", $track->{TTITLE});
    $num++;
  }
  &print_field (*FO, 'EXTD', $obj->{EXTD});
  $num= 0;
  foreach $track (@{$obj->{tracks}})
  {
    &print_field (*FO, "EXTT$num", $track->{EXTT});
    $num++;
  }
  &print_field (*FO, 'PLAYORDER', $obj->{PLAYORDER});
  1;
}

# ----------------------------------------------------------------------------
sub inc_revision
{
  my $obj= shift;
  $obj->{revision}++;
}

# ----------------------------------------------------------------------------
sub discids     { my $obj= shift; $obj->_field_ ('discid',      @_); }
sub ext         { my $obj= shift; $obj->_field_ ('EXTD',        @_); }
sub header      { my $obj= shift; $obj->_field_ ('header',      @_); }
sub length      { my $obj= shift; $obj->_field_ ('length',      @_); }
sub program     { my $obj= shift; $obj->_field_ ('program',     @_); }
sub playorder   { my $obj= shift; $obj->_field_ ('PLAYORDER',   @_); }
sub revision    { my $obj= shift; $obj->_field_ ('REVISION',    @_); }
sub title       { my $obj= shift; $obj->_field_ ('DTITLE',      @_); }
sub dyear       { my $obj= shift; $obj->_field_ ('DYEAR',       @_); }
sub dgenre      { my $obj= shift; $obj->_field_ ('DGENRE',      @_); }

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

# ----------------------------------------------------------------------------
sub track
{
  my $obj= shift;
  my $idx= shift;
  my $val= shift;

  my $tr= $obj->{tracks};
  my $old= $tr->[$idx];

  $tr->[$idx]= $val if ($val);
  $old;
}

# ----------------------------------------------------------------------------
sub track_count
{
  my $obj= shift;

  my $tr= $obj->{tracks};
  $#$tr+1;
}

# ----------------------------------------------------------------------------
sub ESCAPE
{
  my $c= shift;
  $c= $ESCAPE{$c} if (exists ($ESCAPE{$c}));
  $c;
}

# ----------------------------------------------------------------------------
sub decode
{
  my $str= shift;
  $str=~ s/\\(.)/&ESCAPE($1)/eg;
  $str;
}

# ----------------------------------------------------------------------------
sub print_field
{
  local *FO= shift;
  my $par= shift;
  my $val= shift;
  my $lines= 0;
  my $v1;

  while (1)
  {
    my $l1= length ($val);
    last if ($l1 <= 0);
    if ($l1 > $LLNG)
    {
      $v1= substr ($val, 0, $LLNG);
      $val= substr ($val, $LLNG);
    }
    else
    {
      $v1= $val;
      $val= undef;
    }

    $v1=~ s#\\#\\\\#g;
    $v1=~ s#\n#\\n#g;
    $v1=~ s#\t#\\t#g;
    print FO $par, '=', $v1, "\n";
    $lines++;
  }

  print FO $par, "=\n" unless ($lines);

  $lines;
}

# ============================================================================
1;
__END__
# POD Section

=head1 NOTES

=head2 DISCID

There are up to 8 discid codes in a DISCID line, each separated by commas.
If therer are more such codes, they need to be written into separate
lines.  There is no comma after the last code, even if there is another
line following!

  Example:
  DISCID=b10ca40e,b10ca70e,b00ca50e,ae0ca30e,ab0ca30e,aa0ca40e,a90ca50e,a90ca40e
  DISCID=a80ca50e
  DTITLE=Nirvana / Unplugged In New York

=head1 BUGS

This module is work in progres...

=head2 To-Do-List

  How to handle track information

=head1 Copyright

Copyright (c) 2001..2012 Gerhard Gonter.  All rights reserved.
This is free software; you can redistribute it and/or modify
it under the same terms as Perl itself.

=head1 AUTHOR

Gerhard Gonter, g.gonter@ieee.org

=head1 SEE ALSO

http://www.freedb.org/

=cut
