cd \usr\window\CGA
make -i >\usr\window\$CGA.mk
cd \usr\window\BIOS
make -i >\usr\window\$BIOS.mk
cd \usr\window\0
make -i >\usr\window\$0.mk
cd \usr\window\1
make -i >\usr\window\$1.mk
cd \usr\window\2
make -i >\usr\window\$2.mk
cd \usr\window\3
make -i >\usr\window\$3.mk
cd \usr\window\UTL
make -i >\usr\window\$UTL.mk
cd \usr\window
make >$window.mk
