#
# FILE %ned/06/make-ux (Makefile)
#
# GG's Night(mare) Editor System
#
# latest update: 2000-08-24 14:38:24
# $Id: Makefile,v 1.6 2001/11/13 19:14:16 gonter Exp $
#
# ============================================================================
# cf=-O -pedantic -Wall -Wuninitialized -Wunused -Wshadow
OPTS=-c -g -I.. $(cf)
CC=cc
objs=ned0606.o \
     ned0607.o ned0608.o ned0609.o ned0610.o \
     ned0610a.o ned0610b.o ned0610c.o ned0610d.o ned0610e.o \
     ned0612.o ned0613.o ned0616.o \
     ned0619.o ned0623.o ned0624.o ned0625.o \
     ned0627.o ned0628.o ned0629.o ned0630.o
objs_cur= ned0602_cur.o ned0603_cur.o ned0604_cur.o ned0605_cur.o ned0613b_cur.o \
          ned0614_cur.o ned0615_cur.o ned0618_cur.o ned0621_cur.o  \
          ned0622_cur.o ned0626_cur.o ned0631_cur.o
objs_tk=  ned0602_tk.o  ned0603_tk.o  ned0604_tk.o  ned0605_tk.o  ned0613b_tk.o  \
          ned0614_tk.o  ned0615_tk.o  ned0618_tk.o  ned0621_tk.o   \
          ned0622_tk.o  ned0626_tk.o  ned0631_tk.o
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

.c.o: ../ed.h
	$(CC) $(OPTS) -c $*.c

# --- cur Modules ----------
ned0602_cur.o : ../ed.h ned0602.c
	$(CC) $(OPTS)  -o ned0602_cur.o ned0602.c

ned0603_cur.o : ../ed.h ned0603.c
	$(CC) $(OPTS)  -o ned0603_cur.o ned0603.c

ned0604_cur.o : ../ed.h ned0604.c
	$(CC) $(OPTS)  -o ned0604_cur.o ned0604.c

ned0613b_cur.o : ../ed.h ned0613b.c
	$(CC) $(OPTS)  -o ned0613b_cur.o ned0613b.c

ned0614_cur.o : ../ed.h ned0614.c
	$(CC) $(OPTS)  -o ned0614_cur.o ned0614.c

ned0615_cur.o : ../ed.h ned0615.c
	$(CC) $(OPTS)  -o ned0615_cur.o ned0615.c

ned0618_cur.o : ../ed.h ned0618.c
	$(CC) $(OPTS)  -o ned0618_cur.o ned0618.c

ned0626_cur.o : ../ed.h ned0626.c
	$(CC) $(OPTS)  -o ned0626_cur.o ned0626.c

ned0631_cur.o : ../ed.h ned0631.c
	$(CC) $(OPTS)  -o ned0631_cur.o ned0631.c

# --- tk Modules ----------
ned0602_tk.o : ../ed.h ned0602.c
	$(CC) $(OPTS) -DUSE_TK -o ned0602_tk.o ned0602.c

ned0603_tk.o : ../ed.h ned0603.c
	$(CC) $(OPTS) -DUSE_TK -o ned0603_tk.o ned0603.c

ned0604_tk.o : ../ed.h ned0604.c
	$(CC) $(OPTS) -DUSE_TK -o ned0604_tk.o ned0604.c

ned0613b_tk.o : ../ed.h ned0613b.c
	$(CC) $(OPTS) -DUSE_TK -o ned0613b_tk.o ned0613b.c

ned0614_tk.o : ../ed.h ned0614.c
	$(CC) $(OPTS) -DUSE_TK -o ned0614_tk.o ned0614.c

ned0615_tk.o : ../ed.h ned0615.c
	$(CC) $(OPTS) -DUSE_TK -o ned0615_tk.o ned0615.c

ned0618_tk.o : ../ed.h ned0618.c
	$(CC) $(OPTS) -DUSE_TK -o ned0618_tk.o ned0618.c

ned0626_tk.o : ../ed.h ned0626.c
	$(CC) $(OPTS) -DUSE_TK -o ned0626_tk.o ned0626.c

ned0631_tk.o : ../ed.h ned0631.c
	$(CC) $(OPTS) -DUSE_TK -o ned0631_tk.o ned0631.c
# --- cur Modules ----------
ned0605_cur.o : ../ed.h ned0605.c
	$(CC) $(OPTS)  -o ned0605_cur.o ned0605.c

ned0621_cur.o : ../ed.h ned0621.c
	$(CC) $(OPTS)  -o ned0621_cur.o ned0621.c

ned0622_cur.o : ../ed.h ned0622.c
	$(CC) $(OPTS)  -o ned0622_cur.o ned0622.c

# --- tk Modules ----------
ned0605_tk.o : ../ed.h ned0605.c
	$(CC) $(OPTS) -DUSE_TK -o ned0605_tk.o ned0605.c

ned0621_tk.o : ../ed.h ned0621.c
	$(CC) $(OPTS) -DUSE_TK -o ned0621_tk.o ned0621.c

ned0622_tk.o : ../ed.h ned0622.c
	$(CC) $(OPTS) -DUSE_TK -o ned0622_tk.o ned0622.c
