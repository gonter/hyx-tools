#!/usr/local/bin/perl
#
# FILE %ned/possig.pl
#
# written:       1996-05-26
# latest update: 1999-05-01 10:27:50
#
# ----------------------------------------------------------------------------

open (FO, ">\@fnd.sgm") || die;
print FO <<EOF;
searching [ possig.pl ] <hyx.l prc="perl possig.pl" tdc=hyx.l tdp=7>Search!
EOF

$do_unlink= 0;
@JOBS= ();

# vi_dkey
ARGUMENT: while ($arg= shift (@ARGV))
{
  print "arg= $arg\n";
  if ($arg =~ /^-(.*)/)
  {
    $opt= $1;
    if ($opt eq 'f') { &read_file_list (shift (@ARGV)); }
    elsif ($opt eq 'unlink') { $do_unlink= 1; }
    else
    {
      &usage;
      exit (0);
    }
  }
  else
  {
    push (@JOBS, $arg);
  }
}

if ($#JOBS == -1)
{
  $cnt= &scan_dir ('.');
  # print FO "found $cnt files to scan\n\n", '-'x72, "\n";
}

foreach $arg (@JOBS) { &scan_file ($arg); }

close (FO);
exit (0);

# ----------------------------------------------------------------------------
sub usage
{
  print <<EOX;
usage: $0 [-opts]

Options:
-f <fnm>        specify list of files to check
EOX
}

# ----------------------------------------------------------------------------
sub read_file_list
{
  my ($fnm)= @_;

  local (*LIST);
  open (LIST, $fnm) || return -1;
  while (<LIST>)
  {
    chop;
    ($f)= split;
    &scan_file ($f);
  }
  close (LIST);
}

# ----------------------------------------------------------------------------
sub scan_dir
{
  my $dir= shift;

  local (*DIR);
  opendir (DIR, $dir) || die "can't read directory '$dir'";
  my @files= readdir (DIR);
  closedir (DIR);

  my ($file, $cnt, @st, @dirs);
  foreach $file (@files)
  {
    next if ($file eq '.' || $file eq '..'
             || $file eq '_bak_ftr.ned'
             || $file eq 'CVS'
             || -l $file
            );

    # print ">>> '$file'\n";
    if (-d $file)
    {
      push (@dirs, "$dir/$file");
      next;
    }

    next unless ($file =~ /\.(c|h|fm)$/);
    push (@JOBS, "$dir/$file");
    $cnt++;
  }

  # print FO "scanning dir '$dir': $cnt files to scan\n";
  # print "scanning dir '$dir': $cnt files to scan\n";

  foreach $file (@dirs)
  {
    $cnt += &scan_dir ($file);
  }

  $cnt;
}

# ----------------------------------------------------------------------------
sub scan_file
{
  my $fnm= shift;
  my $line= 1;

  open (FI, $fnm) || return -1;

  $fnm=~ tr/A-Z/a-z/;
  $fnm=~ s/\\/\//g;
  # print "file: '$fnm'\n";

#define NIL (void *) 0
  while (<FI>)
  { # ned_eval_hlink ned_eval_string ex_tag_command
    # Search!
    if (
    # /(BUTTON_DESCRIPTOR)/ || /(locate_button)/
    # /(ned_mouse_event)/ || /(check_maus)/ || /(ned_tk_event_procedure)/
    /(MPflag)/
    # || /(NED_Widget)/
    # || /(ned_get_cx_pos)/
#       /(NED_field_editor_callback)/
#       || /(ned_prompt_string)/
#       || /(ned_tk_prompt_string)/
#       || /(ned_tk_cb_prompt_string)/

        # /((NED|W)_TEXT_MAX_(X|Y))/
        # /(curses_sig_winch)/||/(WINCH)/
        # /(ned_set_lookup_tag)/
        # /(curses_sig_winch)/||/(WINCH)/
        # /(p_ssave)/ || /(p_wdw(s|q)file)/
        # || /((vi|ned)_jmp_boln)/
        # || /((ned|ned_wc|q)_word_lr)/
        #
        # /(ned_line_2_string)/ ||
        # /(eval_(line|block|feature|str))/
        # /(ned_set_mark)/
        # /(eval_(str))/
        # || /(ned_tk_(current|widget_cmd))/

        # --------------------------------
        # /(ned_blk_(isolate|duplicate))/
        # /(ned_(shift|change)_markers)/
        # /(selection)/ || /(ned_tk_block_export_flag)/

        # /(b_(beg|end|first|last))/
        # /(ned_blk_isolate)/
        # /(del_char_(left|right))/

        # /(ned_activate_frame)/
        # /(default_template_frame)/
        # /(default_cross_ref_template)/
        # /(0x0*[Dd])/||/(13)/
        # /(default_tag_display_mode)/

        # /(wd_upscr)/||/(ned_w_page_down)/
        # /(line.*(locate|target|find))/ || /((locate|target|find).*line)/
        # /(FC_(next|prev|fnm))/
        # /(bookmark)/

        # !(/\wq_insert/||/q_insert\w/)&&/(q_insert)/
        # /(b_beg)/ || /(b_end)/
        # /(p_blk(beg|end|hide))/
        # /((memorize|restore)_window_mode)/
        # /(ned_get_cluster_list)/ # T2D: deactivate Cluster Control
        # /(q_cross_ref)/ || /(p_1cross_ref)/
        # /(NED_CTX)/ || /(NED_CONTEXT)/
        # /(NED_field_editor_callback)/
        # /(hyx_translate_special_frame)/
        # /(^#[ \t]*include[ \t]+.+array.h)/
        # /(_set(n|)char|_prntcol|_draw_string)/
        # || /(ned_(set|reset)_block_flags)/
        # /(cnt_line|cnt_total_lines|count_lines|cnt_aktline)/
       )
    {
      $fnd= $1;
      $cn=  length ($`);
      $tdp= length ($fnd);

      s/&/&amp;/g;
      s/</&lt;/g;
      s/>/&gt;/g;

      s/$fnd/<hyx.l file="$fnm" ln=$line cn=$cn tdc=79 tdp=$tdp>$fnd/gi;
      printf (FO "%-14s %5d: %s", $fnm, $line, $_);

      if ($do_unlink && $fnm =~ /(.+)\.c/)
      {
        $obj_file= $1 . '.obj';

        if (!defined ($UNLINKED{$obj_file}))
        {
          print ">> rm $obj_file\n";
          unlink $obj_file;
          $UNLINKED{$obj_file}= 1;
        }
      }
    }

    $line++;
  }
  close (FI);

}
