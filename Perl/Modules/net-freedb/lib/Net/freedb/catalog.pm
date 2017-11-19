#!/usr/local/bin/perl
# FILE .../net-freedb/lib/Net/freedb/catalog.pm
#
# manage a catalog of freedb database files
#
# written: 2001-09-02
# re-issued as Net::freedb::* 2002-06-30
# $Id: catalog.pm,v 1.2 2002/07/01 06:56:30 gonter Exp $
#

use strict;
package Net::freedb::catalog;
use Net::freedb::catalog_entry;

my $VERSION= '0.02';

# ----------------------------------------------------------------------------
sub new
{
  my $class= shift;
  my %pars= @_;

  my $cat=  $pars{'category'} or return undef;
  my $path= $pars{'path'} or return undef;

  print "new catalog: category=$cat\n";
  my $obj=
  {
    'category' => $cat,
    'path' => $path,
    'pars' => \%pars,
    'updates' => 0,     # > 0 if there are updates
    'highest_index' => 0,

    # list of catalog entries by ...
    'entries' => [],    # ... by position
    'keys' => {},       # ... by freedb id (or relative path?)
  };
  bless $obj;

  $obj->load ($pars{'catalog'}) if ($pars{'catalog'});
  $obj;
}

# ----------------------------------------------------------------------------
# reads a catalog file
# returns the number of entries read or 0 if the file did not exist
sub load
{
  my ($obj, $fnm)= @_;

  $obj->{'catalog'}= $fnm;  # save filename, it is needed for the save method

  local *FI;
  open (FI, $fnm) or return 0;

  print "reading: $fnm\n";
  my $array= $obj->{'entries'};
  my $table= $obj->{'keys'};
  my $highest_index= $obj->{'highest_index'};

  my $entries= undef;
  while (<FI>)
  {
    chop;
    if (/^#/)
    {
      push (@$array, $_);
      next;
    }

    my $entry= new Net::freedb::catalog_entry (split (':', $_, 6));
    push (@$array, $entry);
    my $key= $entry->key ();
    my $index= $entry->index ();
    $highest_index= $index if ($index > $highest_index);

    # print ">>> entry=$entry key='$key'\n";
    $table->{$key}= $entry;

    $entries++;
  }
  close (FI);

  $obj->{highest_index}= $highest_index;

  return $entries;
}

# ----------------------------------------------------------------------------
# writes a catalog file
# returns the number of entries written or 0 if the file could not be opened
sub save
{
  my $obj= shift;
  my $fnm= shift || $obj->{'catalog'};
  return undef unless ($fnm);

  local *FO;
  open (FO, ">$fnm") or return undef;

  print "saving $fnm\n";
  my $array= $obj->{'entries'};
  my $entries= 0;
  my $comments= 0;

  my $entry;
  foreach $entry (@$array)
  {
    my $r= ref ($entry);
    # print "entry= $entry, r= $r\n";
    if ($r eq '') { print FO $entry, "\n"; $comments++; }
    else { print FO join (':', @$entry), "\n"; $entries++; }
  }
  close (FO);

  ($entries, $comments);
}

# ----------------------------------------------------------------------------
# add comments to catalog file
sub comment
{
  my $obj= shift;
  my $array= $obj->{'entries'};
  foreach (@_)
  {
    push (@$array, '# '. $_);
  }
}

# ----------------------------------------------------------------------------
# locate all freedb database files that were updated relative to the
# timestamps given in the catalog file
sub updates
{
  my $obj= shift;
  my %opts= @_;

  my $path= $obj->{path} or return undef;

  my $check_lmd= 1;
  my $check_rcs= 1;
  my $opt;
  foreach $opt (keys %opts)
  {
    if ($opt eq 'lmd') { $check_lmd= $opts{$opt}; }
    elsif ($opt eq 'rcs') { $check_rcs= $opts{$opt}; }
  }

  return undef unless ($check_lmd || $check_rcs); # nothing to do???

  local *DIR;
  opendir (DIR, $path) or return undef;
  print "updating $path\n";

  my $table= $obj->{'keys'};
  my $array= $obj->{'entries'};
  my $highest_index= $obj->{'highest_index'};

  my (@res, $res, $e);
  while (defined ($e= readdir (DIR)))
  {
    next unless ($e =~ /^[0-9a-fA-F]{8}$/);

    my $f= "$path/$e";
    my @stat= stat ($f);
    my $mtime= $stat[9];

    my $entry= $table->{$f};

    $res= undef;

    if (!$entry)
    {
      # print "new: $e\n";
      $res= { 'x' => 'n' };

      $highest_index++;
      $entry= new Net::freedb::catalog_entry ($highest_index, $mtime, 0, 0, $f, 'unknown');

      # print ">>> entry=$entry key='$f'\n";
      push (@$array, $entry);
      $table->{$f}= $entry;

      if ($check_lmd) { $res->{'lmd'}= { 'x' => 'n' }; }
      if ($check_rcs) { $res->{'rcs'}= { 'x' => 'n' }; }

      $obj->{updates}++;
    }
    else
    {
      my $o_mtime= $entry->mtime ();
      my $t_diff= $mtime - $o_mtime;

      if ($t_diff != $0)
      { # file was modified
        # t_diff should be positive otherwise the file is now older than
        # it was last time; we do not care about this, it's updated...

        # print "e: t_diff=$t_diff\n";
        $res= { 'x' => 'u', 'old_mtime' => $o_mtime };
        $entry->mtime ($mtime);
        $obj->{updates}++;

        if ($check_lmd)
        {
          my $lmd_update= $entry->lmd_update ();
          if ($lmd_update == 0)
          {
            print "not in lmd!\n";
            $res->{'lmd'}= { 'x' => 'n' };
          }
          else
          {
            $res->{'lmd'}= { 'x' => 'u' };
          }
        }

        if ($check_rcs)
        {
          my $rcs_update= $entry->rcs_update ();
          if ($rcs_update == 0)
          {
            print "not in rcs!\n";
            $res->{'rcs'}= { 'x' => 'n' };
          }
          else
          {
            $res->{'rcs'}= { 'x' => 'u' };
          }
        }
      } # t_diff != 0
    } # entry exists

    if (defined ($res))
    {
      $res->{'f'}= $f;
      $res->{'e'}= $e;
      $res->{'t'}= $mtime;
      $res->{'r'}= $entry;

      # print ">>>> push\n";
      push (@res, $res);
    }
  }
  closedir (DIR);

  $obj->{highest_index}= $highest_index;

  (wantarray) ? @res : \@res;
}

1;
