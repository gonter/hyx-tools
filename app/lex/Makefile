#
# FILE ~/usr/lex/makefile.ux
#
# Makefile for the lex files under Unix
#
# written:       1993-07-05
# latest update: 1999-05-08 10:10:04
#

CC=cc
OPTS=-I.
lib=lsbr.a

all : lexcut

install:
	@echo nothing to install

clean :
	rm -f *.o lexcut

# --------
.c.o:
	$(CC) $(OPTS) -c $*.c

# --------
lexcut: lexcut.o lexcut01.o
	cc -o lexcut lexcut.o lexcut01.o
