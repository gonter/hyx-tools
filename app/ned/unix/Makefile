#
# FILE %ned/unix/make-ux (Makefile)
#
# GG's Night(mare) Editor System
#   translate a couple of library functions
#
# written:       1993-06-28
# latest update: 2000-08-24 12:55:36
# $Id: Makefile,v 1.10 2012/08/10 14:44:20 gonter Exp $
#
# ============================================================================
# cf=-O -pedantic -Wall -Wuninitialized -Wunused -Wshadow
PFX= /usr/local/include/
# TCL_VER=8.0
# TCL_VER=8.3
# TCL_VER=8.4
# OPTS2=-I/usr/X11R6/include -I$(PFX)tcl$(TCL_VER) -I${PFX}tk$(TCL_VER)
OPTS2=-I/usr/X11R6/include -I/usr/include/tcl
CC=cc -c -g -I.. $(OPTS) $(OPTS2) $(cf) #-I/usr/include/ncurses

src=      uxwindat.c nedelm.c harness.c
objs=     uxwindat.o harness.o
objs_cur= unix2.o keyboard_cur.o nedelm_cur.o
objs_tk=  tk2.o tk2_scr.o keyboard_tk.o

lib_cur= ../ned_cur.a
lib_tk=  ../ned_tk.a

all: lib_cur lib_tk
clean :
	rm -f *.o lib_cur lib_tk

.c.o:
	$(CC) $*.c

lib_tk : $(objs_tk) $(objs)
	ar ru $(lib_tk) $?
	touch lib_tk

lib_cur : $(objs_cur) $(objs)
	ar ru $(lib_cur) $?
	touch lib_cur

# --- cur Modules ----------
keyboard_cur.o : ../ed.h keyboard.c
	$(CC) $(OPTS)  -o keyboard_cur.o keyboard.c

nedelm_cur.o : ../ed.h nedelm.c
	$(CC) $(OPTS)  -o nedelm_cur.o nedelm.c

# --- tk Modules ----------
keyboard_tk.o : ../ed.h keyboard.c
	$(CC) $(OPTS) -DUSE_TK -o keyboard_tk.o keyboard.c
