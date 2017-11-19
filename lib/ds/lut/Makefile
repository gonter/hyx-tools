#
# FILE %ds/lut/make-ux
#
# written:       1995-12-20
# latest update: 2000-09-01 11:57:00
# $Id: Makefile,v 1.6 2003/06/25 14:38:29 gonter Exp $
#
# ----------------------------------------------------------------------------
CC=cc
cf=-g# -pedantic -Wall -Wuninitialized -Wunused -Wshadow
OPTS=-I. -I/usr/local/include -O $(cf)
LIB=../../libgg.a

all: lib

# ----------------------------------------------------------------------------
LIBOBJS0= \
  lut_0001.o lut_0002.o            lut_0004.o lut_0005.o            \
  lut_0007.o lut_0008.o lut_0009.o lut_0010.o lut_0011.o lut_0012.o \
  lut_0013.o lut_0014.o lut_0015.o

# ----------------------------------------------------------------------------
lib: $(LIBOBJS0) $(LIBOBJS1) $(LIBOBJS2)
	ar ru $(LIB) $?
	touch lib

.c.o:
	$(CC) $(OPTS) -c -g $?

# ----------------------------------------------------------------------------
clean:
	rm -f *.o lib
