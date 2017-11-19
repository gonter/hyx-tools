#
# FILE %ds/hyxl/make-ux
#
# written:       1995-03-19
# latest update: 2001-02-18 18:00:01
# $Id: Makefile,v 1.5 2002/07/17 07:04:35 gonter Exp $
#
# ----------------------------------------------------------------------------
CC=cc
OPTS=-g -I.
# OPTS=-I. -O -pedantic -Wall -Wuninitialized -Wunused -Wshadow

# ----------------------------------------------------------------------------
LIB=../../libgg.a

all: lib

# ----------------------------------------------------------------------------
clean:
	rm -f *.o lib

# ----------------------------------------------------------------------------
LIBOBJS0= \
  hyxl0001.o hyxl0002.o hyxl0003.o hyxl0004.o hyxl0005.o hyxl0006.o \
  hyxl0007.o hyxl0008.o hyxl0009.o hyxl0010.o hyxl0011.o hyxl0012.o \
  hyxl0013.o hyxl0014.o \
  hyxl0101.o

# ----------------------------------------------------------------------------
lib: $(LIBOBJS0)
	ar ru $(LIB) $(LIBOBJS0)
	touch lib

.c.o:
	$(CC) $(OPTS) -c $*.c
