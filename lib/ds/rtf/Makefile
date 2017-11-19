#
# FILE %ds/viesos/make-ux
#
# written:       1995-03-19
# latest update: 1999-05-08  9:51:35
#
# ----------------------------------------------------------------------------
CC=cc
OPTS=-I. -I/usr/local/include
# OPTS=-I. -O -pedantic -Wall -Wuninitialized -Wunused -Wshadow

# ----------------------------------------------------------------------------
LIB=../../libgg.a

all:
	echo rtf is not ready yet
all.2: lib

# ----------------------------------------------------------------------------
clean:
	rm -f *.o lib

# ----------------------------------------------------------------------------
LIBOBJS0= \
  tclhyx01.o tclhyx02.o tclhyx03.o tclhyx04.o tclhyx05.o tclhyx06.o

# ----------------------------------------------------------------------------
lib: $(LIBOBJS0)
	ar ru $(LIB) $(LIBOBJS0)
	touch lib

.c.o:
	$(CC) $(OPTS) -c $*.c
