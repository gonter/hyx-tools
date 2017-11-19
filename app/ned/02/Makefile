#
# FILE %ned/02/make-ux (Makefile)
#
# GG's Night(mare) Editor System
# see also: make-dos
#
# written:       1993-01-01
# latest update: 2000-08-30 20:56:30
# $Id: Makefile,v 1.11 2012/08/10 14:44:20 gonter Exp $
#
# ============================================================================
# cf=-O -pedantic -Wall -Wuninitialized -Wunused -Wshadow
PFX= /usr/local/include/
# TCL_VER=8.0
# TCL_VER=8.3
# TCL_VER=8.4
# OPTS2=-I/usr/X11R6/include -I$(PFX)tcl${TCL_VER} -I${PFX}tk${TCL_VER}
OPTS2=-I/usr/X11R6/include -I/usr/include/tcl8.4
OPTS=-c -g -I.. $(cf)
CC=cc
objs= \
  ned0204.o  ned0204b.o ned0204g.o \
  ned0206.o  ned0208.o  \
  ned0210.o  ned0211.o  ned0212.o  \
  ned0213c.o ned0213d.o ned0213e.o \
  ned0214.o  ned0215a.o ned0215b.o ned0215c.o ned0216.o  \
  ned0217.o  ned0218.o  ned0219.o  ned0220.o  \
  ned0221.o  ned0222.o  ned0223.o  ned0224.o  \
  ned0225.o  ned0226.o  ned0227.o  \
  ned0231.o  ned0232.o  \
  ned0240.o  ned0241.o  ned0242.o  \
  ned0246.o  ned0247.o  \
  ned0248.o  ned0249.o  ned0250.o  ned0251.o  \
  ned0252.o  ned0253.o  ned0253v.o ned0254.o  ned0254b.o \
  ned0255.o  ned0256.o  ned0256a.o ned0257.o \
  ned0258.o  ned0259.o  ned0260.o  ned0260b.o ned0260c.o ned0261.o \
  ned0262a.o ned0263.o
objs_cur= ned0202_cur.o ned0203_cur.o ned0204c_cur.o ned0207_cur.o \
          ned0209_cur.o ned0211b_cur.o ned0213a_cur.o ned0213b_cur.o ned0228_cur.o \
          ned0230_cur.o ned0243_cur.o ned0244_cur.o ned0245_cur.o
objs_tk=  ned0202_tk.o ned0203_tk.o ned0204c_tk.o ned0207_tk.o \
          ned0209_tk.o ned0211b_tk.o ned0213a_tk.o ned0213b_tk.o ned0228_tk.o \
          ned0230_tk.o ned0243_tk.o ned0244_tk.o ned0245_tk.o
lib_cur= ../ned_cur.a
lib_tk=  ../ned_tk.a

all: lib_cur lib_tk
clean :
	rm -f *.o lib_tk lib_cur

lib_tk : $(objs_tk) $(objs)
	ar ru $(lib_tk) $?
	touch lib_tk

lib_cur : $(objs_cur) $(objs)
	ar ru $(lib_cur) $?
	touch lib_cur

.c.o: ../ed.h
	$(CC) $(OPTS) $*.c

# --- cur Modules ----------
ned0202_cur.o : ../ed.h ned0202.c
	$(CC) $(OPTS)  -o ned0202_cur.o ned0202.c

ned0203_cur.o : ../ed.h ned0203.c
	$(CC) $(OPTS)  -o ned0203_cur.o ned0203.c

ned0204c_cur.o : ../ed.h ned0204c.c
	$(CC) $(OPTS)  -o ned0204c_cur.o ned0204c.c

ned0207_cur.o : ../ed.h ned0207.c
	$(CC) $(OPTS)  -o ned0207_cur.o ned0207.c

ned0209_cur.o : ../ed.h ned0209.c
	$(CC) $(OPTS)  -o ned0209_cur.o ned0209.c

ned0211b_cur.o : ../ed.h ned0211b.c
	$(CC) $(OPTS)  -o ned0211b_cur.o ned0211b.c

ned0213a_cur.o : ../ed.h ned0213a.c
	$(CC) $(OPTS)  -o ned0213a_cur.o ned0213a.c

ned0213b_cur.o : ../ed.h ned0213b.c
	$(CC) $(OPTS)  -o ned0213b_cur.o ned0213b.c

ned0228_cur.o : ../ed.h ned0228.c
	$(CC) $(OPTS)  -o ned0228_cur.o ned0228.c

ned0230_cur.o : ../ed.h ned0230.c
	$(CC) $(OPTS)  -o ned0230_cur.o ned0230.c

ned0243_cur.o : ../ed.h ned0243.c
	$(CC) $(OPTS)  -o ned0243_cur.o ned0243.c

ned0244_cur.o : ../ed.h ned0244.c
	$(CC) $(OPTS)  -o ned0244_cur.o ned0244.c

ned0245_cur.o : ../ed.h ned0245.c
	$(CC) $(OPTS)  -o ned0245_cur.o ned0245.c

# --- tk Modules ----------
ned0202_tk.o : ../ed.h ned0202.c
	$(CC) $(OPTS) $(OPTS2) -DUSE_TK -o ned0202_tk.o ned0202.c

ned0203_tk.o : ../ed.h ned0203.c
	$(CC) $(OPTS) $(OPTS2) -DUSE_TK -o ned0203_tk.o ned0203.c

ned0204c_tk.o : ../ed.h ned0204c.c
	$(CC) $(OPTS) -DUSE_TK -o ned0204c_tk.o ned0204c.c

ned0207_tk.o : ../ed.h ned0207.c
	$(CC) $(OPTS) -DUSE_TK -o ned0207_tk.o ned0207.c

ned0209_tk.o : ../ed.h ned0209.c
	$(CC) $(OPTS) -DUSE_TK -o ned0209_tk.o ned0209.c

ned0211b_tk.o : ../ed.h ned0211b.c
	$(CC) $(OPTS) -DUSE_TK -o ned0211b_tk.o ned0211b.c

ned0213a_tk.o : ../ed.h ned0213a.c
	$(CC) $(OPTS) -DUSE_TK -o ned0213a_tk.o ned0213a.c

ned0213b_tk.o : ../ed.h ned0213b.c
	$(CC) $(OPTS) -DUSE_TK -o ned0213b_tk.o ned0213b.c

ned0228_tk.o : ../ed.h ned0228.c
	$(CC) $(OPTS) -DUSE_TK -o ned0228_tk.o ned0228.c

ned0230_tk.o : ../ed.h ned0230.c
	$(CC) $(OPTS) -DUSE_TK -o ned0230_tk.o ned0230.c

ned0243_tk.o : ../ed.h ned0243.c
	$(CC) $(OPTS) -DUSE_TK -o ned0243_tk.o ned0243.c

ned0244_tk.o : ../ed.h ned0244.c
	$(CC) $(OPTS) -DUSE_TK -o ned0244_tk.o ned0244.c

ned0245_tk.o : ../ed.h ned0245.c
	$(CC) $(OPTS) -DUSE_TK -o ned0245_tk.o ned0245.c
