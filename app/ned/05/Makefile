#
# FILE %ned/05/make-ux (Makefile)
#
# GG's Night(mare) Editor System
#
# latest update: 1999-05-06 16:28:19
#
# ============================================================================
# cf=-O -pedantic -Wall -Wuninitialized -Wunused -Wshadow
OPTS=-c -g -I.. $(cf)
CC=cc
o=
objs=ned0501.o  ned0502.o  ned0502c.o ned0502d.o \
    ned0503.o  ned0503b.o ned0504.o  \
    ned0505.o  ned0506a.o ned0506b.o ned0506c.o ned0506d.o ned0506e.o \
    ned0507.o  ned0508.o  ned0508b.o ned0508m.o ned0508t.o \
    ned0510b.o ned0510c.o \
    ned0512.o  ned0513.o  ned0514.o ned0515.o \
    ned0515b.o ned0516.o  ned0516b.o \
    ned0517.o  ned0519.o ned0520.o \
    ned0521.o  ned0522.o
objs_cur= ned0509_cur.o ned0510_cur.o ned0511_cur.o
objs_tk= ned0509_tk.o ned0510_tk.o ned0511_tk.o
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
ned0509_cur.o : ../ed.h ned0509.c
	$(CC) $(OPTS)  -o ned0509_cur.o ned0509.c

ned0510_cur.o : ../ed.h ned0510.c
	$(CC) $(OPTS)  -o ned0510_cur.o ned0510.c

ned0511_cur.o : ../ed.h ned0511.c
	$(CC) $(OPTS)  -o ned0511_cur.o ned0511.c

# --- tk Modules ----------
ned0509_tk.o : ../ed.h ned0509.c
	$(CC) $(OPTS) -DUSE_TK -o ned0509_tk.o ned0509.c

ned0510_tk.o : ../ed.h ned0510.c
	$(CC) $(OPTS) -DUSE_TK -o ned0510_tk.o ned0510.c

ned0511_tk.o : ../ed.h ned0511.c
	$(CC) $(OPTS) -DUSE_TK -o ned0511_tk.o ned0511.c
