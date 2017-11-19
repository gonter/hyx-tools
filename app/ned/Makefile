#
# FILE %ned/make-ux (Makefile)
#
# GG's Night(mare) Editor System
#
# latest update: 2001-02-11 10:07:49
# $Id: Makefile,v 1.18 2012/08/10 14:44:20 gonter Exp $
#
# ============================================================================
#
# ***FOR LINUX***: uncomment these defintitions!!!
# cf=-O -Wall -Wuninitialized -Wunused -pedantic -Wformat

# configure as needed
curseslibs=-lcurses -ltermcap -lncurses
PFX= /usr/local/include/

# === BEGIN Tcl/Tk ===
# Tcl an Tk Libraries, tested are version 8.0, 8.3, 8.4 and apparently sometime in history 7.5/4.1
# note: either use curseslibs or tklibs
# tcllibs=-ltcl7.5 -lm -lld
# tklibs=-ltk4.1 -lX11

# TCL_VER=8.0
# tcllibs=-ltcl80 -lm # -lld
# tklibs=-ltk80 -L/usr/X11R6/lib -lX11

# TCL_VER=8.3
# tcllibs=-ltcl83 -lm # -lld
# tklibs=-ltk83 -L/usr/X11R6/lib -lX11

TCL_VER=8.4
# tcllibs=-ltcl84 -lm # -lld
tcllibs=-ltcl -lm # -lld
# tklibs=-ltk84 -L/usr/X11R6/lib -lX11

# OPTS2=-I/usr/X11R6/include -I${PFX}tcl$(TCL_VER) -I${PFX}tk$(TCL_VER)
# === END Tcl/Tk ===


gglib=../../lib/libgg.a

CC=cc -c -g -I. $(cf)
all_libs=-L/usr/local/lib $(tcllibs) $(linuxlibs)

all  : n00_cur # n00_tk
all2 : all.lib n02_cur n02_tk
all0 : all.lib
# all0s : NOT WORKING sgmlflt

clean :
	rm -f *.o */*.o n0[02] n0[02]_{cur,tk}  ned_cur.a ned_tk.a

distclean : clean
	@echo same as clean

# NED - Hauptprogramm ========================================================
n00_cur : ned00_cur.o ned_cur.a all.lib_cur $(gglib)
	ranlib ned_cur.a
	cc -o $@ ned00_cur.o ned_cur.a $(gglib) $(all_libs) $(curseslibs)

n00_tk : ned00_tk.o ned_tk.a $(gglib)
	ranlib ned_tk.a
	cc -o $@ ned00_tk.o ned_tk.a $(gglib) $(all_libs) $(tklibs)

# AIX with libld.a
n02_cur : ned00_cur.o ned_cur.a
	ranlib ned_cur.a
	cc -o $@ ned00_cur.o ned_cur.a $(gglib) $(all_libs) $(curseslibs) -lld
	cp n02_cur n00_cur

n02_tk : ned00_tk.o ned_tk.a
	ranlib ned_tk.a
	cc -o $@ ned00_tk.o ned_tk.a $(gglib) ${all_libs} $(tklibs) -lld
	cp n02_tk n00_tk

ned00_cur.o : ed.h ned00.c
	$(CC) $(OPT_CUR) -o ned00_cur.o ned00.c

ned00_tk.o : ed.h ned00.c
	$(CC) $(OPT_TK) -DUSE_TK -o ned00_tk.o ned00.c

sgmlflt.o : sgmlflt.c
	$(CC) sgmlflt.c

sgmlflt : sgmlflt.o ned.a
	cc -o $@ sgmlflt.o ned.a $(gglib) ${all_libs}

# ----------------------------------------------------------------------------
all.lib : all.lib_cur all.lib_tk

all.lib_tk :
	( cd 00 && make lib_tk )
	( cd 01 && make lib_tk )
	( cd 02 && make TCL_VER=${TCL_VER} lib_tk )
	( cd 03 && make lib_tk )
	( cd 04 && make lib_tk )
	( cd 05 && make lib_tk )
	( cd 06 && make lib_tk )
	( cd 07 && make lib_tk )
	( cd 08 && make TCL_VER=${TCL_VER} lib_tk )
	( cd 09 && make TCL_VER=${TCL_VER} lib_tk )
	( cd 10 && make lib_tk )
	( cd 11 && make lib_tk )
	( cd 12 && make lib_tk )
	( cd 13 && make lib_tk )
	( cd unix && make TCL_VER=${TCL_VER} lib_tk )

ned_cur.a : all.lib_cur
all.lib_cur :
	( cd 00 && make lib_cur )
	( cd 01 && make lib_cur )
	( cd 02 && make lib_cur )
	( cd 03 && make lib_cur )
	( cd 04 && make lib_cur )
	( cd 05 && make lib_cur )
	( cd 06 && make lib_cur )
	( cd 07 && make lib_cur )
	( cd 08 && make lib_cur )
	( cd 09 && make TCL_VER=${TCL_VER} lib_cur )
	( cd 10 && make lib_cur )
	( cd 11 && make lib_cur )
	( cd 12 && make lib_cur )
	( cd 13 && make lib_cur )
	( cd unix && make TCL_VER=${TCL_VER} lib_cur )

# ----------------------------------------------------------------------------
all.test : fnmdef

T_FNMDEF=sbr/t_fnmdef.o sbr/t_fnmreal.o sbr/t_logicfnm.o
T_FLAG=-DDEBUG
fnmdef : $(T_FNMDEF)
	cc -o fnmdef $(T_FNMDEF) ned.a

sbr/t_fnmdef.o : sbr/fnmdef.c
	$(ccc) $(T_FLAG) -o sbr/t_fnmdef.o sbr/fnmdef.c

sbr/t_fnmreal.o : sbr/fnmreal.c
	$(ccc) $(T_FLAG) -o sbr/t_fnmreal.o sbr/fnmreal.c

sbr/t_logicfnm.o : sbr/logicfnm.c
	$(ccc) $(T_FLAG) -o sbr/t_logicfnm.o sbr/logicfnm.c

