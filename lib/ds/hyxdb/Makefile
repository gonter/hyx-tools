#
# FILE %ds/hyxdb/make-ux
#
# written:       1997-11-09
# latest update: 1999-05-08  9:39:15
#
# ----------------------------------------------------------------------------
CC=cc
OPTS=-I. -I/usr/local/include
# OPTS=-I. -O -pedantic -Wall -Wuninitialized -Wunused -Wshadow
LIB=../../libgg.a

all: lib

# ----------------------------------------------------------------------------
LIBOBJS0= \
  hyxdb001.o hyxdb002.o hyxdb003.o hyxdb004.o hyxdb005.o hyxdb006.o \
  hyxdb007.o

# ----------------------------------------------------------------------------
lib: $(LIBOBJS0)
	ar ru $(LIB) $?
	touch lib

# ----------------------------------------------------------------------------
.c.o:
	$(CC) $(OPTS) -c $?

clean:
	rm -f *.o lib
