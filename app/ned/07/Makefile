#
# FILE %ned/07/make-ux (Makefile)
#
# GG's Night(mare) Editor System
#
# latest update: 1999-05-06 16:27:55
#
# ============================================================================
# cf=-O -pedantic -Wall -Wuninitialized -Wunused -Wshadow
OPTS=-c -g -I.. $(cf)
CC=cc
objs=ned0701.o ned0702.o ned0703.o ned0705.o ned0711.o ned0712.o \
     ned0714.o ned0715.o ned0716.o \
     ned0717.o ned0718.o ned0719.o ned0719b.o ned0719c.o ned0720.o \
     ned0721.o ned0722.o ned0723.o ned0723a.o ned0723b.o \
     ned0724.o ned0724a.o \
     ned0725.o ned0725b.o ned0725c.o ned0726.o \
     ned0727.o ned0727a.o ned0727b.o ned0727c.o ned0727d.o ned0727e.o \
     ned0728.o ned0729.o ned0730.o ned0731a.o ned0731w.o ned0731p.o \
     ned0732.o ned0733.o ned0734.o ned0735.o \
     ned0736.o ned0737.o ned0738.o \
     ned0747.o ned0747b.o ned0749.o ned0750.o ned0751.o \
     ned0752.o ned0753.o ned0754a.o ned0754b.o ned0754c.o ned0754d.o \
     ned0756.o ned0758.o ned0759.o ned0760.o ned0761.o \
     ned0763.o
objs_cur= ned0713_cur.o
objs_tk= ned0713_tk.o
lib_cur= ../ned_cur.a
lib_tk=  ../ned_tk.a

all: lib_tk lib_cur
clean :
	rm -f *.o lib_cur lib_tk

lib_tk : $(objs_tk) $(objs)
	ar ru $(lib_tk) $?
	touch lib_tk

lib_cur : $(objs_cur) $(objs)
	ar ru $(lib_cur) $?
	touch lib_cur

.c.o: ../ed.h ../edhyx.h
	$(CC) $(OPTS) -c $*.c

# --- cur Modules ----------
ned0713_cur.o : ../ed.h ned0713.c
	$(CC) $(OPTS)  -o ned0713_cur.o ned0713.c

# --- tk Modules ----------
ned0713_tk.o : ../ed.h ned0713.c
	$(CC) $(OPTS) -DUSE_TK -o ned0713_tk.o ned0713.c
