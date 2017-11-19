#
# FILE %ds/hyxp/make-ux
#
# written:       1995-12-20
# latest update: 2001-02-18 17:40:11
# $Id: Makefile,v 1.3 2001/02/19 00:27:52 gonter Exp $
#
# ----------------------------------------------------------------------------
CC=cc
OPTS=-g -I. -I/usr/local/include
# OPTS=-I. -O -pedantic -Wall -Wuninitialized -Wunused -Wshadow

# ----------------------------------------------------------------------------
LIB=../../libgg.a

all: lib

# ----------------------------------------------------------------------------
clean:
	rm -f *.o lib

# ----------------------------------------------------------------------------
LIBOBJS0= \
  hyxp0001.o hyxp0002.o hyxp0003.o hyxp0004.o hyxp0005.o hyxp0006.o \
  hyxp0007.o hyxp0008.o hyxp0009.o hyxp0010.o hyxp0011.o hyxp0012.o \
  hyxp0013.o hyxp0014.o hyxp0015.o hyxp0016.o hyxp0017.o hyxp0018.o \
  hyxp0019.o hyxp0020.o hyxp0021.o hyxp0022.o hyxp0023.o hyxp0024.o \
  hyxp0025.o hyxp0026.o hyxp0027.o hyxp0028.o hyxp0029.o hyxp0030.o \
  hyxp0031.o hyxp0032.o hyxp0033.o hyxp0034.o hyxp0035.o

# ----------------------------------------------------------------------------
lib: $(LIBOBJS0)
	ar ru $(LIB) $?
	touch lib

.c.o:
	$(CC) $(OPTS) -c $?
