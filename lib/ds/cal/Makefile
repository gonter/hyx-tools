#
# FILE %ds/cal/make-ux
#
# written:       1995-12-20
# latest update: 1999-05-08  9:37:56
#
# ----------------------------------------------------------------------------
CC=cc
OPTS=-I. -I/usr/local/include
# OPTS=-I. -O -pedantic -Wall -Wuninitialized -Wunused -Wshadow
LIB=../../libgg.a

all: lib
all.bin : dt003b dt003c

# ----------------------------------------------------------------------------
LIBOBJS0= \
  cal01.o cal02.o cal03.o cal04.o cal05.o cal06.o cal07.o cal08.o cal09.o \
  cal10.o

LIBOBJS1= \
  dt001.o dt001b.o dt002.o dt002b.o dt003.o dt003b.o dt004.o dt006.o dt007.o \
  dt008.o dt010.o dt011.o dt014a.o dt014b.o dt015a.o \
  dt021.o dt022.o dt023.o dt024.o dt025.o \
  dt031.o dt032.o dt033.o dt034.o dt035.o dt036.o dt037.o dt038.o \
  dt041.o dt042.o

# ----------------------------------------------------------------------------
lib: $(LIBOBJS0) $(LIBOBJS1)
	ar ru $(LIB) $?
	touch lib

.c.o:
	$(CC) $(OPTS) -c $?

# ----------------------------------------------------------------------------
clean:
	rm -f *.o lib

dt003b: dt003b.c
	$(CC) -o $@ $(OPTS) -DMAIN $?

dt003c: dt003c.c
	$(CC) -o $@ $(OPTS) -DMAIN $?

