#
# FILE %ds/codes/make-ux (Makefile)
#
# written:       1994-03-29
# latest update: 1999-05-08  9:38:03
#
# ============================================================================
CC=cc
OPTS= -I.
# OPTS= -I. -O -pedantic -Wall -Wuninitialized -Wunused -Wshadow
LIB=../../libgg.a
bin=

all : lib
all.bin: $(bin)codes $(bin)codeconv $(bin)codetbl
all.0 : ebcdic xmerge

# ----------------------------------------------------------------------------
obs= cs001.o cs002.o cs003.o cs004.o cs005.o cs006.o cs007.o cs008.o \
     cs009.o cs010.o cs011.o cs012.o \
     cs101.o cs102.o cs103.o cs104.o cs105.o cs106.o cs107.o cs108.o \
     cs109.o cs110.o \
     cs201.o cs202.o cs203.o cs204.o cs205.o \
     cs206.o cs207.o

lib : $(obs)
	ar ru $(LIB) $?
	touch lib

.c.o:
	$(CC) $(OPTS) -c $?

clean :
	rm -f *.o lib

# ----------------------------------------------------------------------------
$(bin)codes : codes.o $(LIB)
	$(CC) -o $@ codes.o $(LIB)

$(bin)codeconv : codeconv.o $(LIB)
	$(CC) -o $@ codeconv.o $(LIB)

$(bin)codetbl : codetbl.o $(LIB)
	$(CC) -o $@ codetbl.o $(LIB)

ebcdic : ebcdic.o
	$(CC) -o $@ ebcdic.o $(LIB)

xmerge : xmerge.o
	$(CC) -o $@ xmerge.o $(LIB)

# ----------------------------------------------------------------------------
cst006obj=cst006.o cs006.o cs001.o cs007.o
cst006 : $(cst006obj)
	$(CC) -o $@ $(cst006obj) $(LIB)
