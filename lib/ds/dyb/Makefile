#
# FILE %ds/dyb/make-ux
#
# written:       1995-12-20
# latest update: 1999-05-08  9:38:31
#
# ----------------------------------------------------------------------------
CC=cc
OPTS=-I. -I/usr/local/include
# OPTS=-I. -O -pedantic -Wall -Wuninitialized -Wunused -Wshadow
LIB=../../libgg.a

all: lib

# ----------------------------------------------------------------------------
clean:
	rm -f *.o lib

# ----------------------------------------------------------------------------
LIBOBJS0= \
  dyb_0001.o dyb_0002.o dyb_0003.o dyb_0004.o dyb_0005.o dyb_0006.o \
  dyb_0007.o dyb_0008.o dyb_0009.o dyb_0010.o dyb_0011.o

# ----------------------------------------------------------------------------
lib: $(LIBOBJS0)
	ar ru $(LIB) $?
	touch lib

.c.o:
	$(CC) $(OPTS) -c $?

dyb_0008.o : dyb_0008.c
	$(CC) $(OPTS) -DMODE_ECB -o $@ -c dyb_0008.c

dyb_0009.o : dyb_0008.c
	$(CC) $(OPTS) -DMODE_CFB -o $@ -c dyb_0008.c
