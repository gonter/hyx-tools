#
# FILE %ds/vieos/make-ux
#
# written:       1995-03-19
# latest update: 1999-05-08  9:53:18
#
# ----------------------------------------------------------------------------
CC=cc
# OPTS=-I. -I/usr/local/include/tcl8.0
# OPTS=-I. -I/usr/local/include/tcl8.3
OPTS=-I. -I/usr/include/tcl8.4
# OPTS=-I. -O -pedantic -Wall -Wuninitialized -Wunused -Wshadow
LIB=../../libgg.a
lib_path=-L/usr/local/lib/tcl8.0
tcllibs=-ltcl -lm
tklibs=-ltk -lX11

BINS= vieos
all: lib
all.bin: $(BINS)

vieos : $(LIB) vieos.o
	cc -o vieos vieos.o $(lib_path) $(LIB) $(tcllibs)

# ----------------------------------------------------------------------------
vieos_0= \
  vieos001.o vieos002.o vieos003.o

vieos_1= \
  vieos101.o vieos102.o vieos103.o

vieos_2= \
  vieos201.o vieos202.o vieos203.o

vieos_3= \
  vieos301.o vieos302.o vieos303.o

vieos_4= \
  vieos401.o vieos402.o vieos403.o

vieos_g= \
  vieosg01.o vieosg02.o vieosg03.o

# ----------------------------------------------------------------------------
lib: $(vieos_0) $(vieos_1) $(vieos_2) $(vieos_3) $(vieos_4) $(vieos_g)
	ar ru $(LIB) $?
	touch lib

.c.o:
	$(CC) $(OPTS) -c $*.c

# ----------------------------------------------------------------------------
clean:
	rm -f *.o $(BINS)
