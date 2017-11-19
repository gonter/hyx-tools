#
# FILE %ds/array/make-ux
#
# written:       1996-08-11
# latest update: 1999-04-10 12:23:03
#
# ----------------------------------------------------------------------------
CC=cc
OPTS=-I. -I/usr/local/include
# OPTS=-I. -O -pedantic -Wall -Wuninitialized -Wunused -Wshadow
LIB=../../libgg.a

all: lib

# ----------------------------------------------------------------------------
LIBOBJS0= \
  array001.o array002.o array003.o array004.o array005.o array006.o \
  array007.o array008.o array009.o array010.o array011.o array012.o \
  array013.o array014.o

# ----------------------------------------------------------------------------
lib: $(LIBOBJS0)
	ar ru $(LIB) $?
	touch lib

# ----------------------------------------------------------------------------
.c.o:
	$(CC) $(OPTS) -c $?

clean:
	rm -f *.o
