#!/usr/local/bin/perl

@modules= qw(00/ned0001 00/ned0002 00/ned0009
  01/ned0102 01/ned0103 01/ned0105 01/ned0105a 01/ned0106 01/ned0106a
  01/ned0109 01/ned0119a 01/ned0124 01/ned0125c
  02/ned0202 02/ned0203
  02/ned0204c 02/ned0207 02/ned0209 02/ned0211b
  02/ned0213b 02/ned0228 02/ned0230 02/ned0244 04/ned0417b
  03/ned0309
  04/ned0426 
  05/ned0509 05/ned0510 05/ned0511
  06/ned0605 06/ned0613b 06/ned0614 06/ned0615 06/ned0618
  06/ned0621 06/ned0622 06/ned0626 06/ned0631
  07/ned0713 08/ned0836 08/ned0845 08/ned0851 09/ned0922 09/ned0939
  10/ned1007 10/ned1009 10/ned1017 10/ned1018 10/ned1019 11/ned1112v ned00
  unix/keyboard);

my $section= shift;

if (@ARGV)
{
  foreach $module (@ARGV) { $list{$module}++; }
}
else
{
foreach $module (@modules)
{
  ($sect, $name)= split (/\//, $module);

  if ($sect eq $section)
  {
    $list{$name}++;
  }
}
}

# print join (' ', sort keys %list), "\n";
%FLAGS= ('tk' => '-DUSE_TK', 'cur' => '');
foreach $mode (sort keys %FLAGS)
{
  $flags= $FLAGS{$mode};
  @lib= ();
  push (@rules, "# --- $mode Modules ----------");
  foreach $module (sort keys %list)
  {
    $obj= $module .'_'. $mode .'.o';

    push (@lib,  $obj);
    push (@rules, <<EOX);
$obj : ../ed.h $module.c
\t\$(CC) \$(OPTS) $flags -o $obj $module.c
EOX
  }
  print "objs_$mode= ", join (' ', @lib), "\n";
}

print <<EOX;
lib_cur= ../ned_cur.a
lib_tk=  ../ned_tk.a

all: lib_tk lib_cur
clean :
\trm -f *.o lib_cur lib_tk

lib_tk : \$(objs_tk) \$(objs)
\tar ru \$(lib_tk) \$?
\ttouch lib_tk

lib_cur : \$(objs_cur) \$(objs)
\tar ru \$(lib_cur) \$?
\ttouch lib_cur

EOX

print join ("\n", @rules);

