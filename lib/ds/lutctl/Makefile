#
# FILE %ds/lutctl/Makefile
#
# written:       2001-11-20
# latest update: 2001-11-20 19:23:30
# $Id: Makefile,v 1.1 2001/11/20 19:32:39 gonter Exp $
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
  lutctl01.o lutctl02.o # lutctl03.o lutctl04.o lutctl05.o lutctl06.o \
  # lutctl07.o lutctl08.o lutctl09.o lutctl10.o lutctl11.o lutctl12.o \
  # lutctl13.o lutctl14.o lutctl15.o lutctl16.o lutctl17.o lutctl18.o \
  # lutctl19.o lutctl20.o lutctl21.o lutctl22.o lutctl23.o

# ----------------------------------------------------------------------------
lib: $(LIBOBJS0)
	ar ru $(LIB) $?
	touch lib

.c.o:
	$(CC) $(OPTS) -c $?
