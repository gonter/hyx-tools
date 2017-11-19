#
# FILE %ned/03/make-ux (Makefile)
#
# GG's Night(mare) Editor System
#
# written:       1993-01-01
# latest update: 2000-08-24 15:16:05
# $Id: Makefile,v 1.5 2003/04/28 02:09:29 gonter Exp $
#
# ============================================================================
# cf=-O -pedantic -Wall -Wuninitialized -Wunused -Wshadow
OPTS=-c -g -I.. -I/usr/local/include $(cf)
CC=cc
objs=\
 ned0301.o  ned0302.o  ned0303.o  ned0304.o  ned0304b.o ned0305.o  \
 ned0306.o  ned0307.o  ned0308.o  ned0310.o  \
 ned0311.o  ned0312.o  ned0313.o  ned0314.o  ned0315.o  \
 ned0316.o                        ned0320.o  \
 ned0321.o  ned0322.o  ned0323.o                        \
 ned0327.o  ned0328.o  ned0329.o  ned0330.o  ned0331.o  \
 ned0332.o  ned0332b.o ned0333.o  ned0333b.o ned0333c.o ned0333d.o \
 ned0333e.o ned0334.o  ned0334b.o ned0335.o \
 ned0341a.o ned0341b.o ned0341c.o ned0342a.o ned0342b.o ned0342c.o

objs_cur= ned0309_cur.o ned0319_cur.o
objs_tk= ned0309_tk.o ned0319_tk.o

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
ned0309_cur.o : ../ed.h ned0309.c
	$(CC) $(OPTS)  -o ned0309_cur.o ned0309.c

ned0319_cur.o : ../ed.h ned0319.c
	$(CC) $(OPTS)  -o ned0319_cur.o ned0319.c

# --- tk Modules ----------
ned0309_tk.o : ../ed.h ned0309.c
	$(CC) $(OPTS) -DUSE_TK -o ned0309_tk.o ned0309.c

ned0319_tk.o : ../ed.h ned0319.c
	$(CC) $(OPTS) -DUSE_TK -o ned0319_tk.o ned0319.c
