goto %1

:ALL
find *.c *.h *.fm n*.sgm >@file.lst

:S
perl \usr\ned\possig.pl -f @file.lst
:: awk possig *.c *.h 00/*.c 01/*.c 02/*.c 03/*.c 04/*.c 05/*.c 06/*.c 07/*.c 08/*.c 09/*.c 10/*.c 11/*.c 12/*.c unix/*.?
:: copy @$.ftr _bak_ftr.ned
goto END

:HDR
find *.c *.h >@file.lst
find -p\c5\include >>@file.lst
goto S

:Q
find *.h *.fm n*.sgm >@file.lst
goto S

:QQ
find *.h >@file.lst
goto S

:UNLINK
rem perl possig.pl -unlink -f @file.lst

:END
