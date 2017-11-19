#
# FILE %ds/ytree/make-ux
#
# written:       1995-12-12
# latest update: 1999-05-08  9:53:56
# $Id: Makefile,v 1.5 2003/06/25 15:02:49 gonter Exp $
#
# ----------------------------------------------------------------------------
CC=cc
OPTS=-g -I. -I/usr/local/include
# OPTS=-I. -O -pedantic -Wall -Wuninitialized -Wunused -Wshadow

# ----------------------------------------------------------------------------
LIB=../../libgg.a

all: lib

bin : ytt ytt2

# ----------------------------------------------------------------------------
clean:
	rm -f *.o lib

# ----------------------------------------------------------------------------
LIBOBJS0= \
  yt_00001.o yt_00002.o yt_00003.o yt_00004.o yt_00005.o yt_00006.o \
  yt_00007.o yt_00008.o yt_00009.o yt_00010.o yt_00011.o yt_00012.o \
  yt_00013.o yt_00014.o yt_00015.o yt_00016.o yt_00017.o yt_00018.o \
  yt_00019.o yt_00020.o yt_00021.o yt_00022.o yt_00023.o

LIBOBJS1= \
  yt_00101.o yt_00102.o

# ----------------------------------------------------------------------------
lib: $(LIBOBJS0)
	ar ru $(LIB) $?
	touch lib

.c.o:
	$(CC) $(OPTS) -c $?

ytt : ytt.o lib
	cc -o ytt ytt.o $(LIB)

ytt2 : ytt2.o lib
	cc -o ytt2 ytt2.o $(LIB)
