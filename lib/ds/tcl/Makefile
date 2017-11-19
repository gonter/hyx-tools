#
# FILE %ds/tcl/make-ux
#
# written:       1996-03-17
# latest update: 1999-05-08  9:52:08
#
# ----------------------------------------------------------------------------
CC=cc
# OPTS=-I. -I/usr/local/include/tcl8.0
# OPTS=-I. -I/usr/local/include/tcl8.3
OPTS=-I. -I/usr/include/tcl8.4
# OPTS=-I. -O -pedantic -Wall -Wuninitialized -Wunused -Wshadow
LIB=../../libgg.a

all: lib

# ----------------------------------------------------------------------------
LIBOBJS0= \
  tclreg00.o tclreg01.o tclreg02.o

LIBOBJS1= \
  tcl_0000.o tcl_0001.o tcl_0002.o tcl_0003.o tcl_0004.o tcl_0005.o \
  tcl_0006.o tcl_0007.o tcl_0008.o tcl_0009.o tcl_0010.o

LIBOBJS2= \
  tcl_0101.o

# ----------------------------------------------------------------------------
lib: $(LIBOBJS0) $(LIBOBJS1) $(LIBOBJS2)
	ar ru $(LIB) $?
	touch lib

# ----------------------------------------------------------------------------
.c.o:
	$(CC) $(OPTS) -c $?

clean:
	rm -f *.o lib
