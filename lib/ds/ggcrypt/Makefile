#
# FILE %ds/ggcrypt/make-ux
#
# written:       1995-12-29
# latest update: 1999-05-08  9:38:53
# $Id: Makefile,v 1.4 2007/12/02 11:58:07 gonter Exp $
#
# ----------------------------------------------------------------------------
CC=cc
OPTS=-I. -g
# OPTS=-I. -O -pedantic -Wall -Wuninitialized -Wunused -Wshadow
LIB=../../libgg.a

all: lib

# ----------------------------------------------------------------------------
LIBOBJS0= \
 ggcryp02.o ggcryq02.o ggcryr02.o ggcryp04.o \
 ggcryp05.o ggcryp06.o ggcryp07.o ggcryp08.o \
 ggcryp09.o ggcryp10.o ggcryp11.o ggcryp12.o \
 ggcryp14.o ggcryp16.o ggcryp17.o ggcryp18.o ggcryp19.o \
 ggcryp21.o ggcryp22.o ggcryp24.o ggcryp25.o ggcryp26.o \
 ggcryp27.o

LIBOBJS1= \
 ggcryp13.o ggcryq13.o ggcryp15.o ggcryq15.o ggcryp20.o ggcryq20.o \
 ggcryp23.o ggcryq23.o ggcryq27.o

# ----------------------------------------------------------------------------
lib: $(LIBOBJS0) $(LIBOBJS1)
	ar ru $(LIB) $?
	touch lib

# ----------------------------------------------------------------------------
.c.o:
	$(CC) $(OPTS) -c $?

clean:
	rm -f *.o lib

# simple encryption routines -------------------------------------------------
cml=$(CC) $(OPTS) -o $@ -c

ggcryp02.o : ggcryp02.c
	$(cml) -DMODE_ENCRYPT ggcryp02.c

ggcryq02.o : ggcryp02.c
	$(cml) -DMODE_DECRYPT ggcryp02.c

ggcryr02.o : ggcryp02.c
	$(cml) -DMODE_SIMPLE ggcryp02.c

ggcryp13.o : ggcryp13.c
	$(cml) -DMODE_ECB ggcryp13.c

ggcryq13.o : ggcryp13.c
	$(cml) -DMODE_CFB ggcryp13.c

ggcryp15.o : ggcryp15.c
	$(cml) -DMODE_ECB ggcryp15.c

ggcryq15.o : ggcryp15.c
	$(cml) -DMODE_CFB ggcryp15.c

ggcryp20.o : ggcryp20.c
	$(cml) -DMODE_ECB ggcryp20.c

ggcryq20.o : ggcryp20.c
	$(cml) -DMODE_CFB ggcryp20.c

ggcryp21.o : ggcryp21.c
	$(cml) -DMODE_CFB ggcryp21.c

ggcryp22.o : ggcryp22.c
	$(cml) -DMODE_CFB ggcryp22.c

ggcryp23.o : ggcryp23.c
	$(cml) -DMODE_ECB ggcryp23.c

ggcryq23.o : ggcryp23.c
	$(cml) -DMODE_CFB ggcryp23.c

ggcryp26.o : ggcryp26.c
	$(cml) -DMODE_CFB ggcryp26.c

ggcryp27.o : ggcryp27.c
	$(cml) -DMODE_ECB ggcryp27.c

ggcryq27.o : ggcryp27.c
	$(cml) -DMODE_CFB ggcryp27.c
