#
# FILE %sbr/make-ux
#
# written:       1995-12-28
# latest update: 2000-08-28 12:27:57
# $Id: Makefile,v 1.12 2009/01/13 16:46:11 gonter Exp $
#
# ----------------------------------------------------------------------------
CC=cc
OPTS=-g -I. -I/usr/local/include
# OPTS=-I. -O -pedantic -Wall -Wuninitialized -Wunused -Wshadow
LIB=../../libgg.a
ccc=$(CC) $(OPTS) -c

BINS= fnmdef fndvfile

all: lib
all.bin: $(BINS)
test: t_getcwd

# ----------------------------------------------------------------------------
sbr_0= \
  bin2hex.o  bin2hexr.o cdromfnm.o \
  convent1.o convent2.o convent4.o convent5.o convent6.o \
  copyfil0.o dcd01.o    diagnose.o dirt_006.o \
  dirt_012.o dirt_i12.o dirt_l12.o \
  dirt_013.o dirt_i13.o dirt_l13.o \
  dirt_i14.o dirt_l14.o\
  dirt_i16.o dirt_l16.o\
  dpp_0001.o dpp_0002.o dpp_0003.o dpp_0005.o dpp_0006.o \
  dpp_0007.o dpp_0008.o \
  alt_seed.o \
  envfilsr.o fclosec.o  file2low.o file2upp.o \
  file2buf.o flopen.o   fndvfile.o fnmcpy.o   fnmcpy2.o  \
  fnmcpy3.o  fnmcpy4.o  fnmdef.o   fnmdestn.o fnmovwr.o  \
  fnmreal.o  fnmrenm.o  fnmsep1.o  fnmsep2.o  fnmsep3.o  fnmsep4.o  \
  fnmdpath.o freadit.o  freaditf.o freadlin.o frmaclin.o \
  freadst.o  freadstf.o \
  ftrans01.o ftrans02.o ftrans03.o ftrans04.o ftrans05.o ftrans06.o \
  ftrans07.o ftrans08.o ftrans09.o ftrans10.o \
  getcdir0.o getcdir1.o gennednm.o lng2hex.o  lng2nstr.o \
  makepath.o param001.o param002.o rndlong.o  rotfile.o  \
  setetcfn.o settmpfn.o tellext.o  \
  trasheol.o hex2bin.o  logicfnm.o logicfpt.o vshift01.o \
  wcrd_001.o wcrd_002.o wcrd_003.o wcrd_004.o wcrd_005.o \
  wcrd_006.o wcrd_007.o wcrd_008.o wcrd_009.o wildcrd2.o \
  xref01.o   xref02.o   xref03.o

sbr_2= sixelval.o
sbr_1= md5c.o md5d2s.o   md5s2d.o   md5chkb.o  md5chks.o  \
  md5chk2a.o md5chk2b.o

# ----------------------------------------------------------------------------
clean:
	rm -f *.o lib $(BINS)

# ----------------------------------------------------------------------------
lib: $(sbr_0) # $(sbr_1) $(sbr_2)
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

file2low.o: file2low.c
	$(CC) $(OPTS) -o $@ -DTO_LOWER -c file2low.c

file2upp.o: file2low.c
	$(CC) $(OPTS) -o $@ -DTO_UPPER -c file2low.c

frmaclin.o: freadlin.c
	$(CC) $(OPTS) -o $@ -c -DMAC_MODE $?

# ----------------------------------------------------------------------------
FNMDEF_DEBUG= #-DEBUG
FNMDEF= _fnmdef.o _fnmreal.o _logicfnm.o
fnmdef : $(FNMDEF)
	cc -o fnmdef $(FNMDEF) $(LIB)

_fnmdef.o : fnmdef.c
	$(ccc) -o $@ $(FNMDEF_DEBUG) -DDEBUG_main fnmdef.c

_fnmreal.o : fnmreal.c
	$(ccc) -o $@ $(FNMDEF_DEBUG) fnmreal.c

_logicfnm.o : logicfnm.c
	$(ccc) -o $@ $(FNMDEF_DEBUG) logicfnm.c

logicfnm.o : logicfnm.c
	$(ccc) -o $@ $(FNMDEF_DEBUG) logicfnm.c

# ----------------------------------------------------------------------------
FNDVFILE= _fndvfile.o
fndvfile : $(FNDVFILE)
	cc -o fndvfile $(FNDVFILE) $(LIB)

_fndvfile.o : fndvfile.c
	$(ccc) -o $@ $(FNMDEF_DEBUG) -DDEBUG_main fndvfile.c

# ----------------------------------------------------------------------------
t_getcwd : t_getcwd.c
	$(CC) $(OPTS) -o $@ $?
