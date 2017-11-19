/*
 *  FILE cmsmake.rexx (CMSMAKE EXEC)
 *
 *  compile and link all modules
 *
 *  written:       1993-03-06
 *  latest update: 1994-09-05
 *
 */
 
parse upper arg what .
 
  /* modules: */
  lutmake1=     'lutmake';
  lutdump1=     'lutdump';
  luttest1=     'luttest';
  deref1=       'deref';
 
  wordcr=       'wordcr03 wordcr04 wordcr05';
  lut1=         'lut_0001 lut_0002 lut_0004 lut_0005 lut_0008';
  lut2=         'lut_0009';
  cmslib=       'cms_acce';
  string1=      'str_0004 str_0006 str_0008 str_0016 str_0020';
  string2=      'str_0021 str_0022 str_0026 str_0027 str_0028';
  string3=      'str_0204 str_0301';
  files1=       'fnmcpy   freadlin ftrans01 ftrans02 ftrans06 file2buf';
  dpp=          'param001 dpp_0001 dpp_0002 dpp_0003';
  hyx=          'hyxl0001 hyxl0002 hyxl0003';
  nl1=          'nl_00001 nl_00002 nl_00004';
  nl2=          'nl_00101 nl_00102 nl_00103 nl_00104 nl_00105';
  nl3=          'nl_00106 nl_00107 nl_00108 nl_00109 nl_00110';
  nl4=          'nl_00111 nl_00112 nl_00113 nl_00114 nl_00115';
  nl5=          'nl_00116 nl_00117 nl_00118 nl_00119 nl_00120';
  nl6=          'nl_00121 nl_00122 nl_00123 nl_00124 nl_00125';
  nl7=          'nl_00126 nl_00127 nl_00128 nl_00129 nl_00130'
  nl8=          'nl_00131 nl_00201';
  yt1=          'yt_00001 yt_00003 yt_00004 yt_00005 yt_00006';
  yt2=          'yt_00007 yt_00008 yt_00009 yt_00010 yt_00011';
  yt3=          'yt_00012';
 
  gglib= 'GGLIB';
 
select;
  when what='GEN' then do;
    rvg=cmpfuncs(lutmake1 lutdump1 luttest1 deref1, '');
  end;
  when what='' then do;
    /* compile the modules */
    say 'compiling: all modules'
    rvg=cmpfuncs(lutmake1 lutdump1 luttest1 deref1, '');
    rvg=rvg+cmpfuncs(wordcr, 'GEN');
    rvg=rvg+cmpfuncs(lut1, 'ADD');
    rvg=rvg+cmpfuncs(lut2, 'ADD');
    rvg=rvg+cmpfuncs(cmslib, 'ADD');
    rvg=rvg+cmpfuncs(string1, 'ADD');
    rvg=rvg+cmpfuncs(string2, 'ADD');
    rvg=rvg+cmpfuncs(string3, 'ADD');
    rvg=rvg+cmpfuncs(files1, 'ADD');
    rvg=rvg+cmpfuncs(dpp, 'ADD');
    rvg=rvg+cmpfuncs(hyx, 'ADD');
    rvg=rvg+cmpfuncs(nl1, 'ADD');
    rvg=rvg+cmpfuncs(nl2, 'ADD');
    rvg=rvg+cmpfuncs(nl3, 'ADD');
    rvg=rvg+cmpfuncs(nl4, 'ADD');
    rvg=rvg+cmpfuncs(nl5, 'ADD');
    rvg=rvg+cmpfuncs(nl6, 'ADD');
    rvg=rvg+cmpfuncs(nl7, 'ADD');
    rvg=rvg+cmpfuncs(nl8, 'ADD');
    rvg=rvg+cmpfuncs(yt1, 'ADD');
    rvg=rvg+cmpfuncs(yt2, 'ADD');
    rvg=rvg+cmpfuncs(yt3, 'ADD');
    if (rvg/=0) then say 'errors in modules ...'
  end;
  otherwise do;
    'TXTLIB DEL' gglib what
    rvg=cmpfuncs(what, 'ADD');
  end;
end/*select*/;
 
/* 'GLOBAL TXTLIB CLIB' gglib */
'GLOBAL TXTLIB  EDCBASE IBMLIB CMSLIB' gglib;
'GLOBAL LOADLIB EDCLINK';
 
/* link the resulting programs */
say 'now generating LUTMAKE MODULE'
'LOAD' lutmake1
if rc=0 then  do;
  'GENMOD LUTMAKE'
  'ERASE LUTMAKE MAP'
  'RENAME LOAD MAP * LUTMAKE = ='
  say 'LUTMAKE MODULE generated...'
end; else; do;
  say 'error generating LUTMAKE MODULE!'
end;
 
say 'now generating LUTDUMP MODULE'
'LOAD' lutdump1
if rc=0 then  do;
  'GENMOD LUTDUMP'
  'ERASE LUTDUMP MAP'
  'RENAME LOAD MAP * LUTDUMP = ='
  say 'LUTDUMP MODULE generated...'
end; else; do;
  say 'error generating LUTDUMP MODULE!'
end;
 
say 'now generating LUTTEST MODULE'
'LOAD' luttest1
if rc=0 then  do;
  'GENMOD LUTTEST'
  'ERASE LUTTEST MAP'
  'RENAME LOAD MAP * LUTTEST = ='
  say 'LUTTEST MODULE generated...'
end; else; do;
  say 'error generating LUTTEST MODULE!'
end;
 
say 'now generating DEREF MODULE'
'LOAD' deref1
if rc=0 then  do;
  'GENMOD DEREF'
  'ERASE DEREF MAP'
  'RENAME LOAD MAP * DEREF = ='
  say 'DEREF MODULE generated...'
end; else; do;
  say 'error generating DEREF MODULE!'
end;
 
exit(0);
 
/* ---------------------------------------------------------------- */
cmpfuncs: parse arg fns, libcmd
rv= 0;
xfns= '';
do while fns/='';
  parse var fns fn fns
  say 'compiling:' fn
  'CC' fn
  if rc=0 then xfns= xfns fn;
  if rc/=0 then rv= rv+1;
end;
if xfns/='' & libcmd/='' then do;
  say 'TXTLIB' libcmd gglib xfns '(FILENAME'
  'TXTLIB' libcmd gglib xfns '(FILENAME'
end;
return rv;
