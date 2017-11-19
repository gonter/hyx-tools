#
# FILE %ds/dbx/make-ux
#
# written:       1996-11-26
# latest update: 1999-05-08  9:38:12
#
# ----------------------------------------------------------------------------
CC=cc
OPTS=-I. -I/usr/local/include
# OPTS=-I. -O -pedantic -Wall -Wuninitialized -Wunused -Wshadow
LIB=../../libgg.a

all: lib

# ----------------------------------------------------------------------------
LIBOBJS0= \
  dbx_0001.o dbx_0002.o dbx_0003.o dbx_0004.o dbx_0005.o dbx_0006.o \
  dbx_0007.o dbx_0008.o

# ----------------------------------------------------------------------------
lib: $(LIBOBJS0)
	ar ru $(LIB) $?
	touch lib

# ----------------------------------------------------------------------------
.c.o:
	$(CC) $(OPTS) -c $?

clean:
	rm -f *.o lib
