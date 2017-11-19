#
# FILE %ned/04/make-ux (Makefile)
#
# GG's Night(mare) Editor System
#
# latest update: 2000-08-24 14:37:39
# $Id: Makefile,v 1.4 2000/08/24 15:10:14 gonter Exp $
#
# ============================================================================
# cf=-O -pedantic -Wall -Wuninitialized -Wunused -Wshadow
OPTS=-c -g -I.. $(cf)
CC=cc
objs=ned0401.o ned0402.o ned0402b.o ned0403.o ned0404.o \
     ned0405.o ned0408.o ned0409.o ned0409b.o ned0409c.o \
     ned0410.o ned0411.o ned0412.o ned0413.o \
     ned0416.o ned0417.o \
     ned0418.o ned0421.o \
     ned0423.o ned0425.o ned0427.o \
     ned0428.o ned0429.o ned0430.o ned0431.o \
     ned0432.o ned0433.o ned0434.o

objs_cur= ned0417b_cur.o ned0422_cur.o ned0426_cur.o
objs_tk=  ned0417b_tk.o  ned0422_tk.o  ned0426_tk.o
lib_cur= ../ned_cur.a
lib_tk=  ../ned_tk.a

# delayed processing for these modules:
objs2=ned0420.o

all: lib_tk lib_cur
clean :
	rm -f *.o lib_cur lib_tk

lib_tk : $(objs_tk) $(objs) $(objs2)
	ar ru $(lib_tk) $?
	touch lib_tk

lib_cur : $(objs_cur) $(objs) $(objs2)
	ar ru $(lib_cur) $?
	touch lib_cur

.c.o: ../ed.h
	$(CC) $(OPTS) -c $*.c

# ----------------------------------------------------------------------------
ned04t1.exe : ned04t1.o ned0423.o ned0424.o ned0419.o
	link ned04t1 ned0423 ned0424 ned0419;

ned04t1.o : ned04t1.c
	$(CC) $(OPTS) ned04t1.c
# --- cur Modules ----------
ned0417b_cur.o : ../ed.h ned0417b.c
	$(CC) $(OPTS)  -o ned0417b_cur.o ned0417b.c

ned0422_cur.o : ../ed.h ned0422.c
	$(CC) $(OPTS)  -o ned0422_cur.o ned0422.c

ned0426_cur.o : ../ed.h ned0426.c
	$(CC) $(OPTS)  -o ned0426_cur.o ned0426.c

# --- tk Modules ----------
ned0417b_tk.o : ../ed.h ned0417b.c
	$(CC) $(OPTS) -DUSE_TK -o ned0417b_tk.o ned0417b.c

ned0422_tk.o : ../ed.h ned0422.c
	$(CC) $(OPTS) -DUSE_TK -o ned0422_tk.o ned0422.c

ned0426_tk.o : ../ed.h ned0426.c
	$(CC) $(OPTS) -DUSE_TK -o ned0426_tk.o ned0426.c
