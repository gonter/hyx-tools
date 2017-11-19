#
# FILE %ds/bbc/make-ux (Makefile)
#
# Makefile fuer Unix
#
# written:       1996-03-25
# latest update: 1999-05-08  9:37:10
# $Id: Makefile,v 1.4 2003/10/01 21:52:01 gonter Exp $
#
# ============================================================================
CC=cc
OPTS=-I. -g #-DDEBUGG1 -DDIAGNOSTICS
# OPTS=-I. -O -pedantic -Wall -Wuninitialized -Wunused -Wshadow
# BIN=/usr/local/bin
DEST=/usr/local/bin
BINS=bbc# bbcinetd
lib=../../libgg.a
LIBS=
# For SINIX 5.41 you need also these:
# LIBS=-lnsl -lresolv -lsocket -lksocket

all : lib

all.exe : lib $(BINS) $(BINS2)

install : ${BINS}
	cp ${BINS} ${DEST}

clean :
	rm -f *.o lib

# ----------------------------------------------------------------------------
lib1=bbc01.o    bbc02.o    bbc03.o    bbc04.o    bbc05.o    bbc06.o    \
     bbc07.o    bbc08.o    bbc09.o    bbc10.o    bbc11.o    bbc12.o    \
     bbc13.o    bbc14.o    bbc15.o

lib : $(lib1)
	ar ru $(lib) $?
	touch lib

.c.o:
	$(CC) $(OPTS) -c $?

# production programs: -------------------------------------------------------
bbc: bbc.o ${lib}
	cc -o bbc bbc.o ${lib} ${LIBS}

bbct1: bbct1.o ${lib}
	cc -o bbct1 bbct1.o ${lib} ${LIBS}
