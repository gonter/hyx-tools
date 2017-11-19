#!/usr/local/bin/perl
# FILE %usr/unixonly/CPAN/vdif-0.01/VDIF/vCx.pm
#
# written:       1998-09-12
# latest update: 1998-10-08 12:00:49
#

package VDIF::vCx;

use vars qw($VERSION @ISA @EXPORT_OK);

require Exporter;

@ISA = qw(Exporter);
@EXPORT_OK = qw();
$VERSION = '0.01';

# ----------------------------------------------------------------------------
# T2D: options to limit number of lines, entries, bytes or such
sub parse_stream
{
  local (*FI)= shift;           # already opened stream
  my $fnm= shift;               # used for error messages
  my $dn_suffix= shift;         # suffix for generated dn values
  $dn_suffix= ','.$dn_suffix if ($dn_suffix && !($dn_suffix =~ /^,/));

  my ($p_n, $p_val, $p_mod, $vref);
  my $entry;            # current active entry
  my @entry_stack;      # vCalendar files define one level of nesting
  my $line;
  my %count;            # sequence counter for various object types
  my @entries;

  while (<FI>)
  {
    $line++;
    chomp;
    s/\015//g;
    next if (/^#/);     # comments are not defined in vCard, vCalendar files!

    if (/^(\w[\w\d\-\.]*):(.*)/)     # property without modifiers
    {
      $p_n= $1; $p_val= $2; $p_n=~ tr/A-Z/a-z/;

      if ($p_n eq 'begin')
      { # some object begins here
        $p_val=~ tr/A-Z/a-z/;    # normalize object type

        my $dn= sprintf ("%s=%d,class=vcx", $p_val, ++$count{$p_val});
        $dn .= $dn_suffix if ($dn_suffix);

        push (@entry_stack, $entry);
        $entry= new VDIF::Entry ($dn);
        $vref= $entry->add_attribute ($p_n, $p_val);
        push (@entries, $entry);
      }
      elsif ($p_n eq 'end')
      { # something ends here ...
        # $p_val=~ tr/A-Z/a-z/;    # normalize object type again
        $entry= pop (@entry_stack);
      }
      else
      {
        $vref= $entry->add_attribute ($p_n, $p_val);
      }
    }
    elsif ($entry
           && /^(\w[\w\d\-\.]*);([^:]*):(.*)/   # property with modifiers
          )
    {
      $p_n= $1; $p_mod= $2; $p_val= $3;
      $p_n=~ tr/A-Z/a-z/;

      # analyze properity parameters into modifier reference structure
      $p_mod= &normalize_property_parameters ($p_mod);

      $vref= $entry->add_attribute ($p_n, $p_val, '', $p_mod);
    }
    elsif ($entry
           && /^[ \t](.*)/      # attribute value continuation
          )                     # exactly one blank or TAB
    {                           # T2D: this is defined differently!
      $vref->{v} .= $1;
    }
    elsif ($entry)
    {
      $vref->{v} .= $_;
    }
    # else skip this, this does not belong to anything.
  }

  return (wantarray) ? @entries : \@entries;
}

# ----------------------------------------------------------------------------
sub normalize_property_parameters
{
  my $str= shift || return undef;

  # NOTE: property parameters are spearated by semi colons and
  # may also contain semi colons if they are escaped as \;
  # Thus we split the string and combine thos with the back slash.
  # ALSO NOTE: the vCard specification doesn't mention escaped colons!

  # return values:
  # + array context: unprocessed property parameter list
  # + scalar context: reference to modifier structure

  my @f= split (/;/, $str);
  my (@f2, $f);
  while (defined ($f= shift (@f)))
  {
    while ($#f >= 0 && $f =~ /\\$/) { $f= $f .';'. shift (@f); }
    @f2= push (@f2);
  }

  return @f2 if (wantarray);

  my ($pn, $pv);
  my %mod;
  while (defined ($f= shift (@f2)))
  {
    ($pn, $pv)= split ('=', $f, 2);
    $pn=~ tr/A-Z/a-z/;

    if ($pn eq 'quoted-printable' || $pn eq 'base64' || $pn eq '8-bit')
    { # Grrrr!!!!  This non-sense called "valid shorthand version"
      # is defined in vCalendar V1.0, section 2.1.2
      $pv= $pn;
      $pn= 'encoding';
    }

    $mod{$pn}= $pv;
  }

  \%mod;
}

1;
