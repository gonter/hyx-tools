#
# FILE %ds/entity/make-ux
#
# written:       1996-06-09
# latest update: 1999-05-08  9:38:48
#
# ----------------------------------------------------------------------------
CC=cc
OPTS=-I. -I/usr/local/include
# OPTS=-I. -O -pedantic -Wall -Wuninitialized -Wunused -Wshadow
LIB=../../libgg.a

all: lib

# ----------------------------------------------------------------------------
LIBOBJS0= \
  ent_0001.o ent_0002.o ent_0003.o ent_0004.o
# ent_0005.o ent_0006.o ent_0007.o ent_0008.o

# ----------------------------------------------------------------------------
lib: $(LIBOBJS0)
	ar ru $(LIB) $?
	touch lib

# ----------------------------------------------------------------------------
.c.o:
	$(CC) $(OPTS) -c $?

clean:
	rm -f *.o lib
