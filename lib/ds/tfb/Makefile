#
# FILE %ds/tfb/make-ux
#
# written:       1995-03-19
# latest update: 1999-05-08  9:52:23
# $Id: Makefile,v 1.5 2005/09/04 09:24:40 gonter Exp $
#
# ----------------------------------------------------------------------------
CC=cc
OPTS=-I../../include -I/usr/local/include
# OPTS=-I. -O -pedantic -Wall -Wuninitialized -Wunused -Wshadow

# ----------------------------------------------------------------------------
LIB=../../libgg.a
BINS=
all: lib
all.bin: $(BINS)
	echo "no binaries here"

# ----------------------------------------------------------------------------
clean:
	rm -f *.o $(BINS)

# ----------------------------------------------------------------------------
LIBOBJS0= \
  tfb01.o tfb02.o tfb03.o tfb04.o tfb05.o tfb06.o tfb07.o tfb08.o \
  tfblut01.o

# ----------------------------------------------------------------------------
lib: $(LIBOBJS0)
	ar ru $(LIB) $(LIBOBJS0)
	touch lib

.c.o:
	$(CC) $(OPTS) -c $?
