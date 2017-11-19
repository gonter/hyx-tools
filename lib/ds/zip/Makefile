#
# FILE %ds/zip/make-ux
#
# written:       1995-12-26
# latest update: 1999-05-08  9:54:06
# $Id: Makefile,v 1.3 2009/10/13 12:59:25 gonter Exp $
#
# ----------------------------------------------------------------------------
CC=cc
OPTS=-I. -I/usr/local/include -g
# OPTS=-I. -O -pedantic -Wall -Wuninitialized -Wunused -Wshadow
LIB=../../libgg.a

# ----------------------------------------------------------------------------
LIBOBJS0= \
  zip_0001.o zip_0002.o zip_0003.o zip_0004.o zip_0005.o zip_0006.o \
  zip_0007.o zip_0008.o

all: lib zs
lib: $(LIBOBJS0)
	ar ru $(LIB) $?
	touch lib

.c.o:
	$(CC) $(OPTS) -c $?

zs.o : zs.c zip_0007.o
	$(CC) $(OPTS) -c zs.c

zs: zs.o $(LIB)
	$(CC) -o zs zs.o $(LIB)

# ----------------------------------------------------------------------------
clean:
	rm -f *.o lib
