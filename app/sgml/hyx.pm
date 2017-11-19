#!/usr/local/bin/perl
# FILE %usr/unixonly/iris/hyx.pm
#
# This is hyx.pm which implements a hash tie for hyx clusters.
#
# The standard hash tie functions implemented are:
#   TIEHASH objectname, clustername     create a connection to a cluster
#   DESTROY this                        break the connection to the object
#   FETCH this, frame                   retrieve a particular frame
#   STORE this, frame, contents         store (add or update) a frame
#   DELETE this, frame                  delete a frame (NOTE 1)
#   EXISTS this, frame                  check the existence of a frame
#   FIRSTKEY this, frame                get the first frame name (NOTE 2)
#   NEXTKEY this (, frame)              get the next frame name (NOTE 3)
#
# Additonaly, these functions are available:
#   frames this                 return list of frames
#   last this                   return index of last frame
#   reindex this                recreate the lut
#   fullindex this              recreate the lut by scanning the cluster
#   purge this                  remove updated frames
#   check this                  run a check against the cluster
#   diag this                   run a diagnostic check against the cluster
#   execute this, command       execute a subcommand on the cluster
#   FETCH_vec this, frame       same as FETCH, result is an array
#   STORE_vec this, frame, @D   same as STORE, contents is an array
#
# Notes:
# 1. Frames are not really removed, just references to them.
#    To get rid of such frames permanently, it is necessary to issue:
#    hyx::purge ($cluster); hyx::reindex ($cluster);
# 2. The returned list is not necessaryly sorted.
# 3. The frame parameter is ignored.
#
# test: hyxtest.pl
#
# written:       1996-10-09
# latest update: 1996-10-14  0:12:10
#

package hyx;

use IPC::Open2;

# ----------------------------------------------------------------------------
sub TIEHASH
{
  local ($self, $hyx_name)= @_;
  local ($hyx_base)= $hyx_name;
  local ($pid);

  $hyx_base= $1 if ($hyx_base =~ /(.+)\.hyx$/);
  $pid= open2 (RD_HYXD, WR_HYXD, "hyxd $hyx_name");

  my $object =
  {
    'FNM_HYX'   => $hyx_name,
    'RD_HYXD'   => RD_HYXD,
    'WR_HYXD'   => WR_HYXD,
    'PID'       => PID,
    'FRAMES'    => []
  } ;

  return bless $object, $self;
}

# ----------------------------------------------------------------------------
sub DESTROY
{
  my $self= shift;
  my $frame= $self->{FNM_HYX};
  # print "DESTROY connection to $frame\n";
  print {$self->{WR_HYXD}} "quit\n";
  close ($self->{WR_HYXD});
  close ($self->{RD_HYXD});
}

# ----------------------------------------------------------------------------
sub FETCH
{
  my $self= shift;
  my $frame= shift;

  print {$self->{'WR_HYXD'}} "fetch $frame\n";
  return &read_hyxd ($self->{'RD_HYXD'}, 0);
}

# ----------------------------------------------------------------------------
sub STORE
{
  my $self= shift;
  my $frame= shift;
  my @contents= split ('\n', shift);

  &STORE_vec ($self, $frame, @contents);
}

# ----------------------------------------------------------------------------
sub DELETE
{
  my $self= shift;
  return shift (@{$self->{'FRAMES'}});
}

# ----------------------------------------------------------------------------
sub EXISTS
{
  my $self= shift;
  my $frame= shift;
  my $res;

  # print ">> EXISTS $frame\n";
  print {$self->{'WR_HYXD'}} "exists $frame\n";
  $res= &read_hyxd ($self->{'RD_HYXD'}, 0);
  # print ">> res='$res'\n";
  return $1 if ($res =~ /^OK (\d+)/);
  return 0;
}

# ----------------------------------------------------------------------------
sub FIRSTKEY
{
  my $self= shift;

  print {$self->{'WR_HYXD'}} "frames\n";
  @{$self->{'FRAMES'}}= &read_hyxd ($self->{'RD_HYXD'}, 2);
  return shift (@{$self->{'FRAMES'}});
}

# ----------------------------------------------------------------------------
sub NEXTKEY
{
  my $self= shift;
  return shift (@{$self->{'FRAMES'}});
}

# ----------------------------------------------------------------------------
sub frames      { &execute (shift, 'frames',    1); }
sub check       { &execute (shift, 'check',     0); }
sub diag        { &execute (shift, 'diag',      0); }
sub reindex     { &execute (shift, 'reindex',   0); }
sub fullindex   { &execute (shift, 'fullindex', 0); }
sub purge       { &execute (shift, 'purge',     0); }

# ----------------------------------------------------------------------------
sub last
{
  $res= &execute (shift, 'last', 0);
  return $1 if ($res =~ /^OK (\d+)/);
  return 0;
}

# ----------------------------------------------------------------------------
sub execute
{
  my $self=     shift;
  my $command=  shift;
  my $fmt=      shift;

  # print "cmd='$command'\n";
  print {$self->{'WR_HYXD'}} "$command\n";
  &read_hyxd ($self->{'RD_HYXD'}, $fmt);
}

# ----------------------------------------------------------------------------
sub FETCH_vec
{
  my $self= shift;
  my $frame= shift;

  print {$self->{'WR_HYXD'}} "fetch $frame\n";
  return &read_hyxd ($self->{'RD_HYXD'}, 1);
}

# ----------------------------------------------------------------------------
sub STORE_vec
{
  my $self= shift;
  my $frame= shift;
  my @contents= @_;
  local ($l);
  local ($fo);

  $fo= $self->{'WR_HYXD'};
  # print ">> store $frame\n";
  print $fo "store $frame\n";
  foreach $l (@contents)
  {
    # print ">>> '$l'\n";
    if ($l =~ /^\.+$/)
    {
      print $fo $l, ".\n";
    }
    else
    {
      print $fo $l, "\n";
    }
  }

  return &read_hyxd ($self->{'RD_HYXD'}, 1);;
}

# ----------------------------------------------------------------------------
sub read_hyxd
{
  local ($fi, $fmt)= @_;

  local ($l, $index, $frame);
  local (@res, $res);
  local ($data)= 0;
 
  while (1)
  {
    $l= <$fi>;
    chop ($l);
    # print ">> '$l'\n";

    return $l if ($l =~ /^ERROR/ || $l =~ /^OK/);

    if ($l eq '.')
    {
      return @res if ($fmt);
      return $res;
    }

    if ($l =~ /^DATA/)
    {
      $data= 1;
      next;
    }

    next unless ($data);
    $l= $1 if ($l =~ /\.(\.+)$/);       # reduce escaped dots

    if ($fmt == 1)                      # prepare result vector
    {
      push (@res, $l);
    }
    elsif ($fmt == 2)                   # prepare list of frames as result
    {
      ($index, $frame)= split (' ', $l, 2);
      push (@res, $frame);
    }
    else                                # result is one string
    {
      $res .= $l . "\n";
    }
  }
}

# ----------------------------------------------------------------------------
1;
