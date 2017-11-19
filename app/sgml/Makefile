#
# FILE %sgml/make-ux (Makefile)
#
# written:       1992 12 14
# latest update: 1999-05-08 10:12:27
#
# ----------------------------------------------------------------------------
CC=cc
OPTS=-I.
# OPTS=-I. -O -pedantic -Wall -Wuninitialized -Wunused -Wshadow
BIN=/usr/local/bin
# BIN=/afs/.wu-wien.ac.at/rs_aix32/usr/afsws/local/bin
# BIN=/afs/.wu-wien.ac.at/pmax_ul43a/usr/afsws/local/bin

# ----------------------------------------------------------------------------
LIB=../../lib/libgg.a
ALL=chksgml msrv translit \
    hyxidx hyxadd hyxseq hyxpurge hyxd hyxscan http4hyx httpsf

all: lib $(ALL)

clean:
	rm -f *.o $(ALL)

install: $(ALL)
	cp $(ALL) $(BIN)

# ----------------------------------------------------------------------------
LIBOBJS0= \
  chksgml1.o chksgml2.o chksgml3.o chksgml4.o chksgml5.o chksgml6.o \
  hyxadd01.o \
  hyxd01.o   hyxd02.o   hyxd03.o   hyxd04.o   hyxd05.o   \
  hyxidx01.o \
  msrv01.o   msrv02.o   msrv03.o   msrv04.o   msrv05.o   msrv06.o   \
  msrv07.o   sf01.o     sf02.o     sf03.o     sf04.o     sf05.o

# ----------------------------------------------------------------------------
lib: $(LIBOBJS0) $(LIBOBJS1)
	ar ru $(LIB) $?
	touch lib

.c.o:
	$(CC) $(OPTS) -c $*.c

# ----------------------------------------------------------------------------
hyxd: hyxd.o $(LIB)
	$(CC) -o hyxd hyxd.o $(LIB)

http4hyx: http4hyx.o $(LIB)
	$(CC) -o http4hyx http4hyx.o $(LIB)

httpsf: httpsf.o $(LIB)
	$(CC) -o httpsf httpsf.o $(LIB)

chksgml: chksgml.o $(LIB)
	$(CC) -o chksgml chksgml.o $(LIB)

hyxidx: hyxidx.o $(LIB)
	$(CC) -o hyxidx hyxidx.o $(LIB)

hyxadd: hyxadd.o $(LIB)
	$(CC) -o hyxadd hyxadd.o $(LIB)

hyxseq: hyxseq.o $(LIB)
	$(CC) -o hyxseq hyxseq.o $(LIB)

hyxthr: hyxthr.o $(LIB)
	$(CC) -o hyxthr hyxthr.o $(LIB)

hyxscan: hyxscan.o $(LIB)
	$(CC) -o hyxscan hyxscan.o $(LIB)

hyxpurge: hyxpurge.o $(LIB)
	$(CC) -o hyxpurge hyxpurge.o $(LIB)

translit: translit.o $(LIB)
	$(CC) -o translit translit.o $(LIB)

# ----------------------------------------------------------------------------
ggcryp13.o: ggcryp13.c
	$(CC) $(OPTS) -DMODE_ECB -c $*.c

ggcryq13.o: ggcryp13.c
	$(CC) $(OPTS) -DMODE_CFB -o $@ -c ggcryp13.c

ggcryp15.o: ggcryp15.c
	$(CC) $(OPTS) -DMODE_ECB -c $*.c

ggcryq15.o: ggcryp15.c
	$(CC) $(OPTS) -DMODE_CFB -o $@ -c ggcryp15.c

dyb_0008.o: dyb_0008.c
	$(CC) $(OPTS) -DMODE_ECB -c $*.c

dyb_0009.o: dyb_0008.c
	$(CC) $(OPTS) -DMODE_CFB -o $@ -c dyb_0008.c

# ----------------------------------------------------------------------------
MSRV=msrv.o
msrv: ${MSRV} $(LIB)
	cc -o msrv ${MSRV} $(LIB)

