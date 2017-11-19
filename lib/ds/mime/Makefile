#
# FILE %ds/mime/make-ux
#
# written:       1996-02-23
# latest update: 2001-12-24 12:45:29
# $Id: Makefile,v 1.4 2001/12/31 08:31:28 gonter Exp $
#
# ----------------------------------------------------------------------------
CC=cc
OPTS=-I. -I/usr/local/include
# OPTS=-I. -O -pedantic -Wall -Wuninitialized -Wunused -Wshadow
LIB=../../libgg.a

all: lib

# ----------------------------------------------------------------------------
LIBOBJS0= \
  mime0001.o mime0002.o mime0003.o # mime0004.o

# ----------------------------------------------------------------------------
lib: $(LIBOBJS0)
	ar ru $(LIB) $?
	touch lib

# ----------------------------------------------------------------------------
.c.o:
	$(CC) $(OPTS) -c $?

clean:
	rm -f *.o lib
