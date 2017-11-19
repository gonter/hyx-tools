#
# FILE %ned/12/make-ux (Makefile)
#
# GG's Night(mare) Editor System
#
# written:       1995-12-12
# latest update: 1999-05-06 16:27:04
#
# ============================================================================
# cf=-O -pedantic -Wall -Wuninitialized -Wunused -Wshadow
OPTS=-c -g -I.. $(cf)
CC=cc

objs= ned1201.o ned1202.o ned1203.o ned1204.o ned1204b.o ned1205.o \
      ned1206.o ned1207.o ned1208.o ned1299.o

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
	$(CC) $(OPTS) -c $*.c
