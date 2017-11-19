#
# FILE %ned/08/make-ux (Makefile)
#
# GG's Night(mare) Editor System
#
# latest update: 2000-08-24 14:45:49
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

objs1=ned0803.o ned0804.o ned0805.o ned0806.o ned0807.o ned0808.o \
      ned0809.o ned0811.o ned0813.o ned0814.o ned0821.o ned0822.o \
      ned0823.o ned0824.o ned0825.o ned0826.o ned0827.o ned0828.o \
      ned0829.o ned0830.o ned0831.o ned0832.o ned0833.o ned0834.o \
      ned0835.o ned0838.o ned0838a.o ned0839.o ned0840.o \
      ned0841.o ned0841b.o ned0842.o ned0842b.o ned0842c.o ned0843.o \
      ned0844.o ned0844b.o ned0845a.o

objs2=ned0846.o ned0847.o ned0848.o ned0849.o ned0850.o ned0850b.o \
      ned0853.o ned0854a.o ned0854b.o ned0854c.o ned0854d.o \
      ned0854e.o ned0854f.o ned0854g.o ned0854h.o ned0856.o ned0857.o \
      ned0857b.o ned0857c.o ned0858.o ned0858b.o \
      ned0859.o ned0860.o ned0861.o \
      ned0862.o ned0863.o ned0863b.o ned0864.o ned0865.o ned0866.o ned0867.o \
      ned0867b.o ned0868.o ned0869.o ned0869b.o ned0870.o \
      ned0871.o ned0873.o ned0875.o \
      ned0876.o ned0877.o ned0878.o \
      ned0879.o ned0879i.o ned0879l.o ned0879t.o \
      ned0880.o ned0882.o  ned0884.o ned0885.o ned0885b.o ned0886.o \
      ned0887.o

objs_cur= ned0836_cur.o ned0845_cur.o ned0851_cur.o
objs_tk= ned0836_tk.o ned0845_tk.o ned0851_tk.o

lib_cur= ../ned_cur.a
lib_tk=  ../ned_tk.a

all: lib_tk lib_cur
clean :
	rm -f *.o lib_cur lib_tk

lib_tk : $(objs_tk) $(objs1) $(objs2)
	ar ru $(lib_tk) $?
	touch lib_tk

lib_cur : $(objs_cur) $(objs1) $(objs2)
	ar ru $(lib_cur) $?
	touch lib_cur

.c.o: ../ed.h ../edhyx.h
	$(CC) $(OPTS) -c $*.c

# --- cur Modules ----------
ned0836_cur.o : ../ed.h ned0836.c
	$(CC) $(OPTS)  -o ned0836_cur.o ned0836.c

ned0845_cur.o : ../ed.h ned0845.c
	$(CC) $(OPTS)  -o ned0845_cur.o ned0845.c

ned0851_cur.o : ../ed.h ned0851.c
	$(CC) $(OPTS)  -o ned0851_cur.o ned0851.c

# --- tk Modules ----------
ned0836_tk.o : ../ed.h ned0836.c
	$(CC) $(OPTS) -DUSE_TK -o ned0836_tk.o ned0836.c

ned0845_tk.o : ../ed.h ned0845.c
	$(CC) $(OPTS) -DUSE_TK -o ned0845_tk.o ned0845.c

ned0851_tk.o : ../ed.h ned0851.c
	$(CC) $(OPTS) -DUSE_TK -o ned0851_tk.o ned0851.c
