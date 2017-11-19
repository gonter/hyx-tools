#
# FILE %ds/varspace/make-ux
#
# written:       1995-03-19
# latest update: 1999-05-08  9:53:06
#
# ----------------------------------------------------------------------------
CC=cc
OPTS=-I. -I/usr/local/include
# OPTS=-I. -O -pedantic -Wall -Wuninitialized -Wunused -Wshadow

# ----------------------------------------------------------------------------
LIB=../../libgg.a

all: lib

# ----------------------------------------------------------------------------
clean:
	rm -f *.o lib

# ----------------------------------------------------------------------------
LIBOBJS0= \
  varsp001.o varsp002.o varsp003.o varsp004.o varsp005.o varsp006.o \
  varsp007.o varsp008.o

# ----------------------------------------------------------------------------
lib: $(LIBOBJS0)
	ar ru $(LIB) $(LIBOBJS0)
	touch lib

.c.o:
	$(CC) $(OPTS) -c $?

