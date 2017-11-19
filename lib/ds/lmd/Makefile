#
# FILE %ds/lmd/make-ux
#
# written:       1995-12-20
# latest update: 1999-05-08  9:49:31
# $Id: Makefile,v 1.6 2002/12/24 07:00:50 gonter Exp $
#
# ----------------------------------------------------------------------------
CC=cc
OPTS=-I. -I/usr/local/include # -DDEBUG
# OPTS=-I. -O -pedantic -Wall -Wuninitialized -Wunused -Wshadow
LIB=../../libgg.a

all: lib

# ----------------------------------------------------------------------------
LIBOBJS0= nl_00001.o nl_00002.o nl_00004.o
LIBOBJS1= nl_00102.o nl_00104.o nl_00105.o nl_00106.o nl_00107.o nl_00108.o \
          nl_00109.o nl_00111.o nl_00112.o nl_00113.o nl_00114.o nl_00115.o \
          nl_00116.o nl_00117.o nl_00118.o nl_00119.o nl_00120.o nl_00121.o \
          nl_00122.o nl_00123.o nl_00124.o nl_00125.o nl_00126.o nl_00127.o \
          nl_00128.o nl_00129.o nl_00130.o nl_00131.o nl_00132.o nl_00133.o \
          nl_00134.o nl_00135.o nl_00136.o nl_00137.o nl_00138.o nl_00139.o \
          nl_00140.o nl_00141.o nl_00142.o
LIBOBJS2= nl_00201.o
LIBOBJS3= nl_00301.o nl_00302.o nl_00303.o nl_00304.o nl_00305.o nl_00306.o
LIBOBJS4= nl_00401.o nl_00402.o nl_00403.o nl_00404.o nl_00405.o nl_00407.o \
          nl_00408.o nl_00409.o
LIBOBJS5= nl_00500.o nl_00501.o nl_00502.o nl_00503.o nl_00504.o nl_00510.o \
          nl_00511.o nl_00512.o nl_00514.o
LIBOBJS6= nl_00601.o nl_00602.o nl_00603.o nl_00604.o nl_00605.o nl_00606.o \
          nl_00607.o nl_00608.o nl_00609.o nl_00610.o
LIBOBJS9= nl_01001.o

# ----------------------------------------------------------------------------
lib: $(LIBOBJS0) $(LIBOBJS1) $(LIBOBJS2) $(LIBOBJS3) $(LIBOBJS4) $(LIBOBJS5) \
     $(LIBOBJS6) $(LIBOBJS9)
	ar ru $(LIB) $?
	touch lib

.c.o:
	$(CC) $(OPTS) -g -c $?

# ----------------------------------------------------------------------------
clean:
	rm -f *.o lib
