del $1
del $2
awk hyxeng01 hyxeng01.cmd
lutmake -mf $1
copy $2 hyxeng01.h
echo static unsigned char hyxeng_cmd [] = >hyxeng01.inc
dump xxx.lut >>hyxeng01.inc
