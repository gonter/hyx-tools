#
# FILE %ned/13/make-ux (Makefile)
#
# GG's Night(mare) Editor System
#
# written:       1997-08-03
# latest update: 2000-08-24 15:22:29
# $Id: Makefile,v 1.5 2000/12/09 17:31:07 gonter Exp $
#
# ============================================================================
# cf=-O -pedantic -Wall -Wuninitialized -Wunused -Wshadow
OPTS=-c -g -I.. $(cf)
CC=cc

objs1= ned1301.o ned1302.o ned1303.o
objs2= ned1391.o ned1392.o

lib_cur= ../ned_cur.a
lib_tk=  ../ned_tk.a

all: lib_cur lib_tk $(objs2)
clean :
	rm -f *.o lib_tk lib_cur

lib_tk : $(objs_tk) $(objs1)
	ar ru $(lib_tk) $?
	touch lib_tk

lib_cur : $(objs_cur) $(objs1)
	ar ru $(lib_cur) $?
	touch lib_cur

.c.o: ../ed.h
	$(CC) $(OPTS) -c $*.c
