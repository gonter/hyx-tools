#!/usr/local/bin/perl
# FILE %usr/unixonly/hp200lx/CPAN/ldif-0.01/pl.pl
#
# written:       1998-08-09
# latest update: 1998-08-09 16:55:13
#

use strict;
use lib '.';
use VDIF;

# require MIME::Media_Types; # debugging
use MIME::Base64;

# configuration;
my $nick_attribute= 'xmozillanickname';

# init
my $aliases= shift || 'aliases.text';
my $in_format= 'elm';
my $out_fmt= 'mozilla';
my @mozilla_object_classes=
( 'top', 'person', 'organizationalPerson',
  'inetOrgPerson', 'mozillaAbPersonObsolete'
);

# &convert ('vcards-comp.out', 'out.ldif', 'vcard', 'ldif');
&convert ($aliases, 'out.ldif', $in_format, 'ldif');
# &convert ('addr.txt', 'out.ldif', 'casio', 'ldif');
exit (0);

# ----------------------------------------------------------------------------
sub convert
{
  my ($in_file, $out_file, $in_format, $out_format)= @_;

  my $ldif= new VDIF::LDIF ('abook');#, '-unique', $nick_attribute);

  if ($in_format eq 'elm' || $in_format eq 'pine')
  {
    &read_elm_aliases ($ldif, $aliases, $in_format);
  }
  elsif ($in_format eq 'casio')
  {
    &read_casio_addresses ($ldif, $in_file, $in_format);
  }
  elsif ($in_format eq 'vcard' || $in_format eq 'vcx')
  {
    &read_vcards ($ldif, $in_file);
  }
  else
  {
    die "Unknown input file format $in_format";
  }

  if ($out_format eq 'ldif')
  {
    local (*FH);
    open (FH, ">$out_file") || die;
    $ldif->print_all (*FH);
    close (FH);
  }
  else
  {
    die "Unknown ouput file format $out_format";
  }

  1;
}

# ----------------------------------------------------------------------------
sub read_vcards
{
  my $ldif= shift;
  my $fnm= shift;

  print "read_vcards: fnm=$fnm\n";
  my @list= &VDIF::parse_file ($fnm, 'vcx', 'news=comp');

  my $entry;
  foreach $entry (@list)
  {
    $ldif->add_entry ($entry);
  }
}

# ----------------------------------------------------------------------------
# read ELM aliases file or PINE addressbook
sub read_elm_aliases
{
  my $ldif= shift;
  my $fnm= shift;
  my $mode= shift || 'elm';     # maybe 'pine' ...

  open (FI, $fnm) || die "cant read $fnm";
  while (<FI>)
  {
    chop;
    my ($nick, $fullname, $address, $description);
    if ($mode eq 'pine')
    {
      ($nick, $fullname, $address)= split (/\t/);
    }
    else
    {
      ($nick, $fullname, $address)= split (/\s*=\s*/);
    }

    unless ($fullname)
    { # no fullname, fake something
      $fullname= $nick;
    }

    ($fullname, $description)= split (/, */, $fullname);
    my ($sn, $givenname)= split (/; */, $fullname);

    if ($givenname)
    {
      $fullname= "$givenname $sn";
    }
    else
    {
      $fullname= $givenname= $sn;
      $sn= '';
    }

    my $dn= "cn=$fullname,mail=$address";
    my $entry= new VDIF::Entry
            (
              $dn,
              'cn' => $fullname,
              'givenname' => $givenname,
              $nick_attribute => $nick,
              'objectclass' => \@mozilla_object_classes,
              'mail' => $address
            );
    $entry->add_attribute ('sn', $sn) if ($sn);
    $entry->add_attribute ('description', $description)
      if ($description);

    $ldif->add_entry ($entry);

    # print ">>> dump entry\n";
    # MIME::Media_Types::print_refs (*STDOUT, 'entry', $entry);

  }
  close (FI);
}

# ----------------------------------------------------------------------------
# read ELM aliases file or PINE addressbook
sub read_casio_addresses
{
  my $ldif= shift;
  my $fnm= shift;

  my $cnt= 0;
  my $entry_cnt= 0;
  my $entry= undef;
  my (@desc, $fullname);

  open (FI, $fnm) || die "cant read $fnm";
  while (<FI>)
  {
    chomp;
    $cnt++;

    s/ +$//;
    s/\x0d//g;
    tr/\x81\x84\x8E\x94\x99\x9A\xE1\xF1/\xDC\xE4\xC4\xF6\xD6\xDC\xDF\xB1/;
    # print "$cnt: $_\n";
    if ($cnt == 1)
    { # empty line used as separator
    }
    elsif ($cnt == 2)
    {
      $fullname= $_;

      my ($sn, $givenname)= split (' ', $fullname, 2);
      $entry_cnt++;
      my $dn= "cn=$fullname,num=$entry_cnt";
      $entry= new VDIF::Entry
              (
                $dn,
                'cn' => $fullname,
                'sn' => $sn,
                'objectclass' => \@mozilla_object_classes,
              );
      $entry->add_attribute ('givenname' => $givenname) if ($givenname);

      $entry_cnt++;
      @desc= ();
    }
    elsif ($cnt == 3 && $_)
    {
      $entry->add_attribute ('telephonenumber', $_);
    }
    elsif ($cnt == 4 && $_)
    {
      my @f= split (/\\/);
      my @g= ();
      my $f;
      foreach $f (@f)
      {
        if ($f =~ /[A-Z]\-\d+/)
        { # vermutlich Postleitzahl mit Stadt
          $entry->add_attribute ('locality', $f);
        }
        else { push (@g, $f); }
      }

      $entry->add_attribute ('streetaddress', join ('$', @g));
    }
    elsif ($_ =~ /\@/)
    {
      $entry->add_attribute ('mail', $_);
    }
    elsif ($_ =~ /nick: *(.*)/)
    {
      $entry->add_attribute ('xmozillanickname', $1)
    }
    elsif ($_)
    {
      push (@desc, $_);
    }

    if ($cnt == 10)
    {
      if ($#desc >= 0)
      {
        my $description= MIME::Base64::encode (join ("\n", @desc));
        $description=~ s/\n//g;

        $entry->add_attribute ('description', $description, 'base64');
      }
      $ldif->add_entry ($entry);

      # print ">>> dump entry\n";
      # MIME::Media_Types::print_refs (*STDOUT, 'entry', $entry);
      print "fullname=$fullname\n";

      $cnt= 0;
      $entry= undef;
    }
  }
  close (FI);
}
