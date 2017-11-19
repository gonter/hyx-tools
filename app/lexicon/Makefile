#
# FILE %lexicon/make-ux (Makefile)
#
# Makefile fuer Unix
# see also: makeshar.lst
#
# written:       1991-02-01
# latest update: 2001-02-18 22:07:06
# $Id: Makefile,v 1.8 2009/03/07 11:36:39 gonter Exp $
#
# ============================================================================
CC=cc
OPTS=-g -I.
# OPTS=-I. -O -pedantic -Wall -Wuninitialized -Wunused -Wshadow
BIN=/usr/local/bin
# BIN=/afs/.wu-wien.ac.at/rs_aix32/usr/afsws/local/bin
# BIN=/afs/.wu-wien.ac.at/pmax_ul43a/usr/afsws/local/bin
BINS=dictadd
BINS2=pt dictmod
BINS3=tst1
# Note: atag.c missing?
lib=../../lib/libgg.a
LIBS=
# For SINIX 5.41 you need also these:
# LIBS=-lnsl -lresolv -lsocket -lksocket

all : all.exe
all.exe : lib $(BINS) $(BINS2) $(BINS3)

install : ${BINS}
	cp ${BINS} ${BIN}

install2 : ${BINS2}
	cp ${BINS2} ${BIN}

clean :
	rm -f *.o lib $(BINS) $(BINS2)

distclean : clean
	rm -f alexicon.lut alexicon.hyx alexicon.idx

# ----------------------------------------------------------------------------
lib.old= lex00001.o
lib1=parse007.o parse008.o parse014.o parse016.o parse017.o \
     parse019.o parse021.o parse022.o parsd008.o parsd016.o \
     dictadd1.o dictadd2.o dictadd3.o dictadd4.o            dictadd6.o \
                dictadd8.o dictadd9.o \
     dict0001.o dict0002.o dict0003.o dict0004.o dict0005.o dict0006.o \
     dict0007.o dict0008.o dict0009.o dict0010.o dict0011.o dict0012.o \
     dict0013.o dict0014.o dict0015.o dict0016.o            dict0018.o \
     lexut001.o

lib : $(lib1)
	ar ru $(lib) $?
	touch lib
	ranlib $(lib)

.c.o:
	$(CC) $(OPTS) -c $?

all2:
	( cd bbc && make )
	( cd hyxp && make )
	( cd ytree && make )
	 make

all2cleanall:
	( cd bbc && make clean all )
	( cd hyxp && make clean all )
	( cd ytree && make clean all )
	 make clean all

# test programs: -------------------------------------------------------------
pt : pt.o parsd008.o parsd016.o $(lib)
	cc -o pt pt.o parsd008.o parsd016.o $(lib)

lex : lex.o $(lib)
	cc -o lex lex.o $(lib)

# production programs: -------------------------------------------------------
dictadd : dictadd.o $(lib)
	cc -o dictadd dictadd.o $(lib) $(LIBS)

dictmod : dictmod.o lexpr001.o $(lib)
	cc -o dictmod dictmod.o lexpr001.o $(lib)

atag : atag.o $(lib)
	cc -o atag atag.o $(lib)

tst1 : tst1.c $(lib)
	cc -I. -o tst1 tst1.c $(lib)

# ----------------------------------------------------------------------------
parsd008.o: parse008.c
	$(CC) $(OPTS) -c -DDIAGNOSTIC -o $@ parse008.c

parsd016.o: parse016.c
	$(CC) $(OPTS) -c -DDIAGNOSTIC -o $@ parse016.c
