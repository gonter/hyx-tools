#
# FILE %ds/hytxt/make-ux
#
# written:       1996-01-01
# latest update: 1999-05-08  9:39:05
#
# ----------------------------------------------------------------------------
CC=cc
OPTS=-I. -I/usr/local/include
# OPTS=-I. -O -pedantic -Wall -Wuninitialized -Wunused -Wshadow
LIB=../../libgg.a

all: lib

# ----------------------------------------------------------------------------
LIBOBJS0= \
  hytxt001.o hytxt002.o hytxt005.o hytxt009.o hytxt010.o hytxt011.o \
  hytxt012.o hytxt013.o hytxt014.o hytxt015.o hytxt016.o hytxt017.o \
  hytxt018.o hytxt019.o hytxt020.o hytxt021.o hytxt022.o hytxt023.o \
  hytxt024.o hytxt025.o hytxt026.o hytxt027.o hytxt028.o hytxt029.o \
  hytxt030.o hytxt031.o hytxt032.o hytxt033.o hytxt034.o hytxt035.o \
  hytxt036.o hytxt037.o hytxt038.o

# ----------------------------------------------------------------------------
lib: $(LIBOBJS0)
	ar ru $(LIB) $?
	touch lib

# ----------------------------------------------------------------------------
.c.o:
	$(CC) $(OPTS) -c $?

clean:
	rm -f *.o lib
