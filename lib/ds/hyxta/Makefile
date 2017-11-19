#
# FILE %ds/hyxta/make-ux
#
# written:       1995-12-20
# latest update: 1999-05-08  9:41:02
#
# ----------------------------------------------------------------------------
CC=cc
OPTS=-I. -I/usr/local/include
# OPTS=-I. -O -pedantic -Wall -Wuninitialized -Wunused -Wshadow
LIB=../../libgg.a

all: lib

# ----------------------------------------------------------------------------
LIBOBJS0= \
  hyxta001.o hyxta002.o hyxta003.o hyxta004.o hyxta005.o hyxta006.o \
  hyxta007.o hyxta008.o \
  hyxta012.o hyxta015.o hyxta020.o hyxta101.o hyxta102.o hyxtax01.o

# ----------------------------------------------------------------------------
lib: $(LIBOBJS0)
	ar ru $(LIB) $?
	touch lib

.c.o:
	$(CC) $(OPTS) -c $?

# ----------------------------------------------------------------------------
clean:
	rm -f *.o lib
