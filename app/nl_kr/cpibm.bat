::
:: FILE ~/usr/nl_kr/cpibm.bat
::
:: copy all necessary files onto temporary space
::
:: written:       1993-03-03
:: latest update: 1994-09-05
::
:: ---------------------------------------------------------------------------
goto %1
echo no destination specified!!!!!
goto END
:F
:G
:H
:I
:J
:K
awk cpibm lutmake.c                     >%1:lutmake.c
awk cpibm deref.c                       >%1:deref.c
awk cpibm lutdump.c                     >%1:lutdump.c
awk cpibm luttest.c                     >%1:luttest.c
awk cpibm c:\etc\lexicon\top200.wrd     >%1:top200.wrd
copy c:\c5\include\gg\ggcms.h            %1:
awk " {print}" lmd.tex                  >%1:lmd.tex
awk " {print}" lmd.hyx                  >%1:lmd.hyx
copy c:\usr\sbr\cms_acce.c               %1:
copy cmsmake.rex                         %1:
awk cpibm c:\c5\include\gg\sbr.h        >%1:sbr.h
awk cpibm c:\c5\include\gg\dpp.h        >%1:dpp.h
awk cpibm c:\c5\include\gg\strings.h    >%1:strings.h
awk cpibm c:\c5\include\gg\lookup.h     >%1:lookup.h
awk cpibm c:\c5\include\gg\hyx.h        >%1:hyx.h
awk cpibm c:\c5\include\gg\ytree.h      >%1:ytree.h
awk cpibm c:\c5\include\gg\ztree.h      >%1:ztree.h
awk cpibm c:\c5\include\gg\fileio.h     >%1:fileio.h
awk cpibm c:\c5\include\gg\filename.h   >%1:filename.h
awk cpibm c:\c5\include\gg\public.inc   >%1:public.inc
awk cpibm c:\c5\include\gg\help.inc     >%1:help.inc
awk cpibm c:\usr\sbr\param001.c         >%1:param001.c
awk cpibm c:\usr\sbr\ftrans01.c         >%1:ftrans01.c
awk cpibm c:\usr\sbr\ftrans02.c         >%1:ftrans02.c
awk cpibm c:\usr\sbr\ftrans06.c         >%1:ftrans06.c
awk cpibm c:\usr\sbr\freadlin.c         >%1:freadlin.c
awk cpibm c:\usr\sbr\file2buf.c         >%1:file2buf.c
awk cpibm c:\usr\sbr\fnmcpy.c           >%1:fnmcpy.c
awk cpibm c:\usr\sbr\dpp_0001.c         >%1:dpp_0001.c
awk cpibm c:\usr\sbr\dpp_0002.c         >%1:dpp_0002.c
awk cpibm c:\usr\sbr\dpp_0003.c         >%1:dpp_0003.c
awk cpibm c:\usr\sbr\str_0004.c         >%1:str_0004.c
awk cpibm c:\usr\sbr\str_0006.c         >%1:str_0006.c
awk cpibm c:\usr\sbr\str_0008.c         >%1:str_0008.c
awk cpibm c:\usr\sbr\str_0016.c         >%1:str_0016.c
awk cpibm c:\usr\sbr\str_0020.c         >%1:str_0020.c
awk cpibm c:\usr\sbr\str_0021.c         >%1:str_0021.c
awk cpibm c:\usr\sbr\str_0022.c         >%1:str_0022.c
awk cpibm c:\usr\sbr\str_0026.c         >%1:str_0026.c
awk cpibm c:\usr\sbr\str_0027.c         >%1:str_0027.c
awk cpibm c:\usr\sbr\str_0028.c         >%1:str_0028.c
awk cpibm c:\usr\sbr\str_0301.c         >%1:str_0301.c
awk cpibm c:\usr\sbr\str_0204.c         >%1:str_0204.c
awk cpibm wordcrea.h                    >%1:wordcrea.h
awk cpibm wordcr03.c                    >%1:wordcr03.c
awk cpibm wordcr04.c                    >%1:wordcr04.c
awk cpibm wordcr05.c                    >%1:wordcr05.c
awk cpibm lib\lut_0001.c                >%1:lut_0001.c
awk cpibm lib\lut_0002.c                >%1:lut_0002.c
awk cpibm lib\lut_0004.c                >%1:lut_0004.c
awk cpibm lib\lut_0005.c                >%1:lut_0005.c
awk cpibm lib\lut_0008.c                >%1:lut_0008.c
awk cpibm lib\lut_0009.c                >%1:lut_0009.c
awk cpibm lib\nl_00001.c                >%1:nl_00001.c
awk cpibm lib\nl_00002.c                >%1:nl_00002.c
awk cpibm lib\nl_00004.c                >%1:nl_00004.c
awk cpibm lib\nl_00101.c                >%1:nl_00101.c
awk cpibm lib\nl_00102.c                >%1:nl_00102.c
awk cpibm lib\nl_00103.c                >%1:nl_00103.c
awk cpibm lib\nl_00104.c                >%1:nl_00104.c
awk cpibm lib\nl_00105.c                >%1:nl_00105.c
awk cpibm lib\nl_00106.c                >%1:nl_00106.c
awk cpibm lib\nl_00107.c                >%1:nl_00107.c
awk cpibm lib\nl_00108.c                >%1:nl_00108.c
awk cpibm lib\nl_00109.c                >%1:nl_00109.c
awk cpibm lib\nl_00110.c                >%1:nl_00110.c
awk cpibm lib\nl_00111.c                >%1:nl_00111.c
awk cpibm lib\nl_00112.c                >%1:nl_00112.c
awk cpibm lib\nl_00113.c                >%1:nl_00113.c
awk cpibm lib\nl_00114.c                >%1:nl_00114.c
awk cpibm lib\nl_00115.c                >%1:nl_00115.c
awk cpibm lib\nl_00116.c                >%1:nl_00116.c
awk cpibm lib\nl_00117.c                >%1:nl_00117.c
awk cpibm lib\nl_00118.c                >%1:nl_00118.c
awk cpibm lib\nl_00119.c                >%1:nl_00119.c
awk cpibm lib\nl_00120.c                >%1:nl_00120.c
awk cpibm lib\nl_00121.c                >%1:nl_00121.c
awk cpibm lib\nl_00122.c                >%1:nl_00122.c
awk cpibm lib\nl_00123.c                >%1:nl_00123.c
awk cpibm lib\nl_00124.c                >%1:nl_00124.c
awk cpibm lib\nl_00125.c                >%1:nl_00125.c
awk cpibm lib\nl_00126.c                >%1:nl_00126.c
awk cpibm lib\nl_00127.c                >%1:nl_00127.c
awk cpibm lib\nl_00128.c                >%1:nl_00128.c
awk cpibm lib\nl_00129.c                >%1:nl_00129.c
awk cpibm lib\nl_00130.c                >%1:nl_00130.c
awk cpibm lib\nl_00131.c                >%1:nl_00131.c
awk cpibm lib\nl_00201.c                >%1:nl_00201.c
awk cpibm c:\usr\ds\ytree\yt_00001.c    >%1:yt_00001.c
awk cpibm c:\usr\ds\ytree\yt_00002.c    >%1:yt_00002.c
awk cpibm c:\usr\ds\ytree\yt_00003.c    >%1:yt_00003.c
awk cpibm c:\usr\ds\ytree\yt_00004.c    >%1:yt_00004.c
awk cpibm c:\usr\ds\ytree\yt_00005.c    >%1:yt_00005.c
awk cpibm c:\usr\ds\ytree\yt_00006.c    >%1:yt_00006.c
awk cpibm c:\usr\ds\ytree\yt_00007.c    >%1:yt_00007.c
awk cpibm c:\usr\ds\ytree\yt_00008.c    >%1:yt_00008.c
awk cpibm c:\usr\ds\ytree\yt_00009.c    >%1:yt_00009.c
awk cpibm c:\usr\ds\ytree\yt_00010.c    >%1:yt_00010.c
awk cpibm c:\usr\ds\ytree\yt_00011.c    >%1:yt_00011.c
awk cpibm c:\usr\ds\ytree\yt_00012.c    >%1:yt_00012.c
awk cpibm c:\usr\ds\hyx\hyxl0001.c      >%1:hyxl0001.c
awk cpibm c:\usr\ds\hyx\hyxl0002.c      >%1:hyxl0002.c
awk cpibm c:\usr\ds\hyx\hyxl0003.c      >%1:hyxl0003.c
goto END
:C
:D
:E
echo temporary space on %1 ? sure??
:END
