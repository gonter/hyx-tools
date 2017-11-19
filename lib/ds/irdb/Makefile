#
# FILE %ds/irdb/make-ux
#
# written:       1996-04-01
# latest update: 1999-05-08  9:43:29
#
# ----------------------------------------------------------------------------
CC=cc
OPTS=-I. -I/usr/local/include
# OPTS=-I. -O -pedantic -Wall -Wuninitialized -Wunused -Wshadow
LIB=../../libgg.a

all : lib

all.00= \
  irdb0001.o irdb0002.o irdb0003.o irdb0004.o irdb0005.o \
  irdb0006.o irdb0007.o irdb0008.o irdb0009.o irdb0010.o \
  irdb0011.o irdb0012.o irdb0013.o irdb0014.o irdb0015.o \
  irdb0016.o irdb0017.o irdb0018.o irdb0019.o irdb0020.o \
  irdb0021.o irdb0022.o irdb0023.o irdb0024.o irdb0025.o \
  irdb0026.o irdb0027.o irdb0028.o

all.01= \
  irdb0101.o irdb0102.o irdb0103.o irdb0104.o irdb0105.o \
  irdb0106.o irdb0107.o \
             irdb0112.o \
  irdb0116.o            irdb0118.o irdb0119.o irdb0120.o

all.test : it1.exe

# ----------------------------------------------------------------------------
lib: $(all.00) $(all.01)
	ar ru $(LIB) $?
	touch lib

# ----------------------------------------------------------------------------
.c.o:
	$(CC) $(OPTS) -c $?

clean:
	rm -f *.o lib
