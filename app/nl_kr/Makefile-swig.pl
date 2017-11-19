#!/usr/local/bin/perl
#
# $Id: Makefile-swig.pl,v 1.2 2002/07/04 18:08:49 gonter Exp $
#

my @MACH= grep m#/mach#, @INC;
my $MACH= shift @MACH;

print <<EOX;
# this file was generated!

INCL= -I.
INCL_PERL= -I$MACH/CORE
INCL_PYTHON= -I/usr/local/include/python1.6

PERL_OUT= tfb_perl_wrap.o tfb.so
all : \$(PERL_OUT)

clean :
	rm -f tfb_warp.c \$(PERL_OUT)

# Perl
tfb_perl_wrap.c : tfb.i
	swig -perl5 -o tfb_perl_wrap.c tfb.i

tfb_perl_wrap.o : tfb_perl_wrap.c
	cc -o \$@ \$(INCL) \$(INCL_PERL) -c tfb_perl_wrap.c

tfb.so : tfb_perl_wrap.o libgg.a
	ld -shared \$(LIB) tfb_perl_wrap.o -o tfb.so

# Python
tfb_python_wrap.c : tfb.i
	swig -python -o tfb_python_wrap.c tfb.i

tfb_python_wrap.o : tfb_python_wrap.c
	cc -o \$@ \$(INCL) \$(INCL_PYTHON) -c tfb_python_wrap.c

tfb_python.so : tfb_python_wrap.o libgg.a
	ld -shared libgg.a tfb_python_wrap.o -o tfb_python.so

EOX
