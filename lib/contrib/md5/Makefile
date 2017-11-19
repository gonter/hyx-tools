#
# FILE %sbr/make-ux
#
# written:       1995-12-28
# latest update: 1999-05-08  9:36:36
#
# ----------------------------------------------------------------------------
CC=cc
OPTS=-I.
# OPTS=-I. -O -pedantic -Wall -Wuninitialized -Wunused -Wshadow
LIB=../../libgg.a
ccc=$(CC) $(OPTS) -c

all: lib
all.bin: fnmdef fndvfile

# ----------------------------------------------------------------------------
sbr_1= md5c.o md5d2s.o   md5s2d.o   md5chkb.o  md5chks.o  \
  md5chk2a.o md5chk2b.o

# ----------------------------------------------------------------------------
clean:
	rm -f *.o lib

# ----------------------------------------------------------------------------
lib: $(sbr_1)
	ar ru $(LIB) $?
	touch lib

.c.o:
	$(CC) $(OPTS) -c $?

# ----------------------------------------------------------------------------
dirt_012.o: dirt_012.c
	$(CC) $(OPTS) -o $@ -c dirt_012.c

dirt_i12.o: dirt_012.c
	$(CC) $(OPTS) -o $@ -c -DTLT_INT $?

dirt_l12.o: dirt_012.c
	$(CC) $(OPTS) -o $@ -c -DTLT_LONG $?

dirt_013.o: dirt_013.c
	$(CC) $(OPTS) -o $@ -c dirt_013.c

dirt_i13.o: dirt_013.c
	$(CC) $(OPTS) -o $@ -c -DTLT_INT $?

dirt_l13.o: dirt_013.c
	$(CC) $(OPTS) -o $@ -c -DTLT_LONG $?

dirt_i14.o: dirt_014.c
	$(CC) $(OPTS) -o $@ -c -DDTYPE_int $?

dirt_l14.o: dirt_014.c
	$(CC) $(OPTS) -o $@ -c -DDTYPE_long $?

dirt_i16.o: dirt_016.c
	$(CC) $(OPTS) -o $@ -c -DDTYPE_int $?

dirt_l16.o: dirt_016.c
	$(CC) $(OPTS) -o $@ -c -DDTYPE_long $?

frmaclin.o: freadlin.c
	$(CC) $(OPTS) -o $@ -c -DMAC_MODE $?

# ----------------------------------------------------------------------------
FNMDEF= _fnmdef.o _fnmreal.o _logicfnm.o
fnmdef : $(FNMDEF)
	cc -o fnmdef $(FNMDEF) $(LIB)

_fnmdef.o : fnmdef.c
	$(ccc) -o $@ -DDEBUG -DDEBUG_main fnmdef.c

_fnmreal.o : fnmreal.c
	$(ccc) -o $@ -DDEBUG fnmreal.c

_logicfnm.o : logicfnm.c
	$(ccc) -o $@ -DDEBUG logicfnm.c

# ----------------------------------------------------------------------------
FNDVFILE= _fndvfile.o
fndvfile : $(FNDVFILE)
	cc -o fndvfile $(FNDVFILE) $(LIB)

_fndvfile.o : fndvfile.c
	$(ccc) -o $@ -DDEBUG -DDEBUG_main fndvfile.c
