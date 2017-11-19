#
# FILE %ned/11/make-ux (Makefile)
#
# GG's Night(mare) Editor System
#
# latest update: 1999-05-06 16:27:11
#
# ============================================================================
# cf=-O -pedantic -Wall -Wuninitialized -Wunused -Wshadow
OPTS=-c -g -I.. $(cf)
CC=cc
objs= ned1101.o ned1102.o ned1103.o ned1104.o ned1105.o \
      ned1106.o ned1107.o ned1108.o ned1109.o ned1110.o \
      ned1111.o ned1112.o ned1112w.o ned1113.o
objs_cur= ned1112v_cur.o
objs_tk= ned1112v_tk.o
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
ned1112v_cur.o : ../ed.h ned1112v.c
	$(CC) $(OPTS)  -o ned1112v_cur.o ned1112v.c

# --- tk Modules ----------
ned1112v_tk.o : ../ed.h ned1112v.c
	$(CC) $(OPTS) -DUSE_TK -o ned1112v_tk.o ned1112v.c
