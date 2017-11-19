#
# FILE %ds/mail/make-ux
#
# written:       1997-11-27
# latest update: 1999-05-08  9:50:34
#
# ----------------------------------------------------------------------------
CC=cc
OPTS=-I. -I/usr/local/include
# OPTS=-I. -O -pedantic -Wall -Wuninitialized -Wunused -Wshadow
LIB=../../libgg.a

all: lib

# ----------------------------------------------------------------------------
LIBOBJS0= \
  mail0001.o mail0002.o mail0003.o mail0004.o mail0005.o \
  mail0006.o mail0007.o mail0008.o mail0009.o mail0010.o \
  mail0011.o mail0012.o mail0013.o mail0014.o

# ----------------------------------------------------------------------------
lib: $(LIBOBJS0)
	ar ru $(LIB) $?
	touch lib

# ----------------------------------------------------------------------------
.c.o:
	$(CC) $(OPTS) -c $?

clean:
	rm -f *.o lib

# ----------------------------------------------------------------------------
MOD1= mail0011.o mail0012.o mail0013.o mail0014.o
mt1.o : mt1.c
	$(CC) $(OPTS) -c -DMT1 $?

mt1 : mt1.o $(MOD1)
	cc -o $@ mt1.o $(MOD1) $(LIB)

mt2.o : mt1.c
	$(CC) $(OPTS) -c -DMT2 $?

mt2 : mt2.o $(MOD1)
	cc -o $@ mt2.o $(MOD1) $(LIB)
