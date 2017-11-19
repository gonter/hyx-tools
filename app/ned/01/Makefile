#
# FILE %ned/01/make-ux (Makefile)
#
# GG's Night(mare) Editor System
#
# latest update: 2000-08-24 13:51:21
# $Id: Makefile,v 1.5 2000/12/09 17:29:46 gonter Exp $
#
# ============================================================================
# cf=-O -pedantic -Wall -Wuninitialized -Wunused -Wshadow
OPTS=-c -g -I.. $(cf)
CC=cc
o=
objs= \
  ned0101.o ned0102m.o ned0102p.o ned0102v.o \
  ned0103p.o ned0103v.o ned0104.o ned0105p.o\
  ned0106p.o ned0107.o ned0107b.o \
  ned0108a.o ned0108b.o ned0108c.o \
  ned0108d.o ned0110.o ned0110a.o ned0110b.o \
  ned0111.o ned0111a.o ned0111b.o ned0112.o ned0112w.o \
  ned0113.o ned0114.o ned0115b.o ned0116.o \
  ned0117.o ned0118.o ned0119.o \
  ned0120.o ned0121.o ned0122.o ned0123.o \
  ned0126.o ned0127.o ned0128.o ned0129.o \
  ned0132.o ned0134.o ned0138.o ned0138b.o ned0139.o \
  ned0140.o ned0141.o ned0142.o
objs_tk=  ned0102_tk.o   ned0103_tk.o   ned0105_tk.o  ned0105a_tk.o \
          ned0106_tk.o   ned0106a_tk.o  \
          ned0109_tk.o   ned0115_tk.o   ned0119a_tk.o ned0124_tk.o  ned0125c_tk.o
objs_cur= ned0102_cur.o  ned0103_cur.o  ned0105_cur.o ned0105a_cur.o \
          ned0106_cur.o  ned0106a_cur.o \
          ned0109_cur.o  ned0115_cur.o  ned0119a_cur.o ned0124_cur.o ned0125c_cur.o
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
	$(CC) $(OPTS) $*.c

# --- cur Modules ----------
ned0102_cur.o : ../ed.h ned0102.c
	$(CC) $(OPTS)  -o ned0102_cur.o ned0102.c

ned0103_cur.o : ../ed.h ned0103.c
	$(CC) $(OPTS)  -o ned0103_cur.o ned0103.c

ned0105_cur.o : ../ed.h ned0105.c
	$(CC) $(OPTS)  -o ned0105_cur.o ned0105.c

ned0105a_cur.o : ../ed.h ned0105a.c
	$(CC) $(OPTS)  -o ned0105a_cur.o ned0105a.c

ned0106_cur.o : ../ed.h ned0106.c
	$(CC) $(OPTS)  -o ned0106_cur.o ned0106.c

ned0106a_cur.o : ../ed.h ned0106a.c
	$(CC) $(OPTS)  -o ned0106a_cur.o ned0106a.c

ned0109_cur.o : ../ed.h ned0109.c
	$(CC) $(OPTS)  -o ned0109_cur.o ned0109.c

ned0115_cur.o : ../ed.h ned0115.c
	$(CC) $(OPTS)  -o ned0115_cur.o ned0115.c

ned0119a_cur.o : ../ed.h ned0119a.c
	$(CC) $(OPTS)  -o ned0119a_cur.o ned0119a.c

ned0124_cur.o : ../ed.h ned0124.c
	$(CC) $(OPTS)  -o ned0124_cur.o ned0124.c

ned0125c_cur.o : ../ed.h ned0125c.c
	$(CC) $(OPTS)  -o ned0125c_cur.o ned0125c.c

# --- tk Modules ----------
ned0102_tk.o : ../ed.h ned0102.c
	$(CC) $(OPTS) -DUSE_TK -o ned0102_tk.o ned0102.c

ned0103_tk.o : ../ed.h ned0103.c
	$(CC) $(OPTS) -DUSE_TK -o ned0103_tk.o ned0103.c

ned0105_tk.o : ../ed.h ned0105.c
	$(CC) $(OPTS) -DUSE_TK -o ned0105_tk.o ned0105.c

ned0105a_tk.o : ../ed.h ned0105a.c
	$(CC) $(OPTS) -DUSE_TK -o ned0105a_tk.o ned0105a.c

ned0106_tk.o : ../ed.h ned0106.c
	$(CC) $(OPTS) -DUSE_TK -o ned0106_tk.o ned0106.c

ned0106a_tk.o : ../ed.h ned0106a.c
	$(CC) $(OPTS) -DUSE_TK -o ned0106a_tk.o ned0106a.c

ned0109_tk.o : ../ed.h ned0109.c
	$(CC) $(OPTS) -DUSE_TK -o ned0109_tk.o ned0109.c

ned0115_tk.o : ../ed.h ned0115.c
	$(CC) $(OPTS) -DUSE_TK -o ned0115_tk.o ned0115.c

ned0119a_tk.o : ../ed.h ned0119a.c
	$(CC) $(OPTS) -DUSE_TK -o ned0119a_tk.o ned0119a.c

ned0124_tk.o : ../ed.h ned0124.c
	$(CC) $(OPTS) -DUSE_TK -o ned0124_tk.o ned0124.c

ned0125c_tk.o : ../ed.h ned0125c.c
	$(CC) $(OPTS) -DUSE_TK -o ned0125c_tk.o ned0125c.c
