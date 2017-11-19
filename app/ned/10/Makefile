#
# FILE %ned/10/make-ux
#
# written:       1990 01 20
# latest update: 2000-08-24 14:49:19
# $Id: Makefile,v 1.4 2000/08/24 15:10:19 gonter Exp $
#
# ============================================================================
# cf=-O -pedantic -Wall -Wuninitialized -Wunused -Wshadow
OPTS=-c -g -I.. $(cf)
CC=cc
objs=ned1001.o ned1002.o ned1003.o ned1004.o ned1005.o \
     ned1006.o ned1008.o ned1010.o \
     ned1011.o ned1012.o ned1013.o ned1014.o ned1015.o \
     ned1016.o
objs_cur= ned1007_cur.o ned1009_cur.o ned1017_cur.o ned1018_cur.o ned1019_cur.o
objs_tk= ned1007_tk.o ned1009_tk.o ned1017_tk.o ned1018_tk.o ned1019_tk.o

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
ned1007_cur.o : ../ed.h ned1007.c
	$(CC) $(OPTS)  -o ned1007_cur.o ned1007.c

ned1009_cur.o : ../ed.h ned1009.c
	$(CC) $(OPTS)  -o ned1009_cur.o ned1009.c

ned1017_cur.o : ../ed.h ned1017.c
	$(CC) $(OPTS)  -o ned1017_cur.o ned1017.c

ned1018_cur.o : ../ed.h ned1018.c
	$(CC) $(OPTS)  -o ned1018_cur.o ned1018.c

ned1019_cur.o : ../ed.h ned1019.c
	$(CC) $(OPTS)  -o ned1019_cur.o ned1019.c

# --- tk Modules ----------
ned1007_tk.o : ../ed.h ned1007.c
	$(CC) $(OPTS) -DUSE_TK -o ned1007_tk.o ned1007.c

ned1009_tk.o : ../ed.h ned1009.c
	$(CC) $(OPTS) -DUSE_TK -o ned1009_tk.o ned1009.c

ned1017_tk.o : ../ed.h ned1017.c
	$(CC) $(OPTS) -DUSE_TK -o ned1017_tk.o ned1017.c

ned1018_tk.o : ../ed.h ned1018.c
	$(CC) $(OPTS) -DUSE_TK -o ned1018_tk.o ned1018.c

ned1019_tk.o : ../ed.h ned1019.c
	$(CC) $(OPTS) -DUSE_TK -o ned1019_tk.o ned1019.c
