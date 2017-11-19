#
# FILE %ned/00/make-ux (Makefile)
#
# latest update: 2000-08-24 13:45:14
# $Id: Makefile,v 1.6 2002/10/18 05:56:19 gonter Exp $
#
# ============================================================================
# cf=-O -pedantic -Wall -Wuninitialized -Wunused -Wshadow
OPTS=-c -g -I.. $(cf)
CC=cc
ccc=$(CC) $(OPTS)
objs=ned0003.o ned0004.o ned0005.o ned0006.o\
     ned0006b.o ned0007.o ned0010.o ned0011.o ned0015.o
objs_cur= ned0001_cur.o ned0002_cur.o
objs_tk=  ned0001_tk.o  ned0002_tk.o
lib_tk=  ../ned_tk.a
lib_cur= ../ned_cur.a

all: lib_tk lib_cur
clean :
	rm *.o lib_tk lib_cur

lib_tk : $(objs_tk) $(objs)
	ar ru $(lib_tk) $?
	touch lib_tk

lib_cur : $(objs_cur) $(objs)
	ar ru $(lib_cur) $?
	touch lib_cur

.c.o: ../ed.h
	$(ccc) $*.c

# --- Tk Version ------
ned0001_tk.o : ../ed.h ned0001.c ned0009.c \
  ned0001a.c ned0001c.c ned0001k.c ned0001o.c ned0001q.c ned0001x.c\
  ned0001u.c ned0001v.c ned0001t.c ned0016w.c ned0016v.c ned0016p.c
	$(ccc) -DUSE_TK -o ned0001_tk.o ned0001.c

ned0002_tk.o : ../ed.h ned0002.c ned0009.c
	$(ccc) -DUSE_TK -o ned0002_tk.o ned0002.c

# --- Curses Version ------
ned0001_cur.o : ../ed.h ned0001.c ned0009.c \
  ned0001a.c ned0001c.c ned0001k.c ned0001o.c ned0001q.c ned0001x.c\
  ned0001u.c ned0001t.c ned0016w.c ned0016v.c ned0016p.c
	$(ccc) -o ned0001_cur.o ned0001.c

ned0002_cur.o : ../ed.h ned0002.c ned0009.c
	$(ccc) -o ned0002_cur.o ned0002.c

# --- General Version ------
ned0003.o : ../ed.h ned0003.c ned0009.c
	$(ccc) ned0003.c

ned0008.o : ../ed.h ../edhyx.h ned0008.c
	$(ccc) ned0008.c
