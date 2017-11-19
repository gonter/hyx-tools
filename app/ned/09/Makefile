#
# FILE %ned/09/make-ux (Makefile)
#
# GG's Night(mare) Editor System
#
# latest update: 2000-08-24 14:48:59
# $Id: Makefile,v 1.9 2012/08/10 14:44:20 gonter Exp $
#
# ============================================================================
# cf=-O -pedantic -Wall -Wuninitialized -Wunused -Wshadow
PFX= /usr/local/include/
# TCL_VER=8.0
# TCL_VER=8.3
# TCL_VER=8.4
# OPTS2=-I/usr/X11R6/include -I$(PFX)tcl$(TCL_VER) -I${PFX}tk$(TCL_VER)
OPTS2=-I/usr/X11R6/include -I/usr/include/tcl8.4
OPTS=-c -g -I.. $(OPTS2) $(cf)
CC=cc
ccc=$(CC) $(OPTS)

# configuration
objects= $(o_1) $(o_mac) $(o_tcl) # $(o_tk)
# change if needed       ^^^^^^^^^^^^^^^^^^

o_tcl=ned0923.o  ned0924.o  ned0936.o  ned0937.o  ned0937b.o \
      ned0938.o  ned0940.o  ned0941.o  ned0942.o  ned0943.o \
      ned0944.o  ned0945.o  ned0946.o  ned0946b.o \
      ned0947.o  ned0948.o  ned0949.o \
      ned0950.o  ned0951a.o ned0951b.o
o_tk= ned0925.o  ned0926.o  ned0927.o  ned0928.o  ned0929.o  ned0929s.o \
      ned0930.o  ned0931.o  ned0932.o  ned0933.o  ned0934.o  ned0935.o  

o_1=  ned0901.o ned0902.o ned0903.o ned0908.o \
      ned0911.o ned0912.o ned0913.o ned0914.o ned0915.o \
      ned0916.o ned0917.o ned0918.o ned0919.o \
      ned0972.o ned0973.o ned0974.o \
      ned0975.o ned0976.o ned0977.o ned0978.o ned0979.o \
      ned0980.o ned0981.o

o_mac=ned09m00.o ned09m01.o ned09m02.o ned09m03.o \
      ned09m04.o ned09m05.o ned09m06.o ned09m07.o \
      ned09m08.o ned09m09.o ned09m10.o ned09m11.o \
      ned09m12.o ned09m13.o ned09m14.o ned09m15.o \
      ned09m16.o ned09m17.o ned09m18.o ned09m19.o \
      ned09m20.o ned09m21.o ned09m22.o ned09m23.o \
      ned09m24.o ned09m25.o ned09m26.o ned09m27.o \
      ned09m28.o ned09m29.o ned09m30.o ned09m31.o \
      ned09m32.o ned09m33.o ned09m34.o ned09m35.o \
      ned09m36.o ned09m37.o ned09m38.o ned09m39.o \
      ned09m40.o ned09m41.o ned09m42.o ned09m43.o \
      ned09m44.o ned09m45.o ned09m46.o ned09m47.o \
      ned09m48.o ned09m49.o ned09m50.o

objs_cur= ned0922_cur.o ned0939_cur.o
objs_tk= ned0922_tk.o ned0939_tk.o
lib_cur= ../ned_cur.a
lib_tk=  ../ned_tk.a

all: lib_cur lib_tk

clean :
	rm -f *.o lib_cur lib_tk

lib_tk : $(objs_tk) $(o_tk) $(o_1) $(o_mac) $(o_tcl)
	ar ru $(lib_tk) $?
	touch lib_tk

lib_cur : $(objs_cur) $(o_1) $(o_mac) $(o_tcl)
	ar ru $(lib_cur) $?
	touch lib_cur

.c.o: ../ed.h
	$(CC) $(OPTS) -c $*.c

# ----------------------------------------------------------------------------
# macros
ned09m00.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro00 -DMACRO_NUM=0 ned0921.c

ned09m01.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro01 -DMACRO_NUM=1 ned0921.c

ned09m02.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro02 -DMACRO_NUM=2 ned0921.c

ned09m03.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro03 -DMACRO_NUM=3 ned0921.c

ned09m04.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro04 -DMACRO_NUM=4 ned0921.c

ned09m05.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro05 -DMACRO_NUM=5 ned0921.c

ned09m06.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro06 -DMACRO_NUM=6 ned0921.c

ned09m07.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro07 -DMACRO_NUM=7 ned0921.c

ned09m08.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro08 -DMACRO_NUM=8 ned0921.c

ned09m09.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro09 -DMACRO_NUM=9 ned0921.c

ned09m10.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro10 -DMACRO_NUM=10 ned0921.c

ned09m11.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro11 -DMACRO_NUM=11 ned0921.c

ned09m12.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro12 -DMACRO_NUM=12 ned0921.c

ned09m13.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro13 -DMACRO_NUM=13 ned0921.c

ned09m14.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro14 -DMACRO_NUM=14 ned0921.c

ned09m15.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro15 -DMACRO_NUM=15 ned0921.c

ned09m16.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro16 -DMACRO_NUM=16 ned0921.c

ned09m17.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro17 -DMACRO_NUM=17 ned0921.c

ned09m18.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro18 -DMACRO_NUM=18 ned0921.c

ned09m19.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro19 -DMACRO_NUM=19 ned0921.c

ned09m20.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro20 -DMACRO_NUM=20 ned0921.c

ned09m21.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro21 -DMACRO_NUM=21 ned0921.c

ned09m22.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro22 -DMACRO_NUM=22 ned0921.c

ned09m23.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro23 -DMACRO_NUM=23 ned0921.c

ned09m24.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro24 -DMACRO_NUM=24 ned0921.c

ned09m25.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro25 -DMACRO_NUM=25 ned0921.c

ned09m26.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro26 -DMACRO_NUM=26 ned0921.c

ned09m27.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro27 -DMACRO_NUM=27 ned0921.c

ned09m28.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro28 -DMACRO_NUM=28 ned0921.c

ned09m29.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro29 -DMACRO_NUM=29 ned0921.c

ned09m30.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro30 -DMACRO_NUM=30 ned0921.c

ned09m31.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro31 -DMACRO_NUM=31 ned0921.c

ned09m32.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro32 -DMACRO_NUM=32 ned0921.c

ned09m33.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro33 -DMACRO_NUM=33 ned0921.c

ned09m34.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro34 -DMACRO_NUM=34 ned0921.c

ned09m35.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro35 -DMACRO_NUM=35 ned0921.c

ned09m36.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro36 -DMACRO_NUM=36 ned0921.c

ned09m37.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro37 -DMACRO_NUM=37 ned0921.c

ned09m38.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro38 -DMACRO_NUM=38 ned0921.c

ned09m39.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro39 -DMACRO_NUM=39 ned0921.c

ned09m40.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro40 -DMACRO_NUM=40 ned0921.c

ned09m41.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro41 -DMACRO_NUM=41 ned0921.c

ned09m42.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro42 -DMACRO_NUM=42 ned0921.c

ned09m43.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro43 -DMACRO_NUM=43 ned0921.c

ned09m44.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro44 -DMACRO_NUM=44 ned0921.c

ned09m45.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro45 -DMACRO_NUM=45 ned0921.c

ned09m46.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro46 -DMACRO_NUM=46 ned0921.c

ned09m47.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro47 -DMACRO_NUM=47 ned0921.c

ned09m48.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro48 -DMACRO_NUM=48 ned0921.c

ned09m49.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro49 -DMACRO_NUM=49 ned0921.c

ned09m50.o : ned0921.c
	$(ccc) -o $@ -DMACRO_PRIM=p_macro50 -DMACRO_NUM=50 ned0921.c
# --- cur Modules ----------
ned0922_cur.o : ../ed.h ned0922.c
	$(CC) $(OPTS)  -o ned0922_cur.o ned0922.c

ned0939_cur.o : ../ed.h ned0939.c
	$(CC) $(OPTS)  -o ned0939_cur.o ned0939.c

# --- tk Modules ----------
ned0922_tk.o : ../ed.h ned0922.c
	$(CC) $(OPTS) -DUSE_TK -o ned0922_tk.o ned0922.c

ned0939_tk.o : ../ed.h ned0939.c
	$(CC) $(OPTS) -DUSE_TK -o ned0939_tk.o ned0939.c
