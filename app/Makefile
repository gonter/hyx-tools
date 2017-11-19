#!/usr/local/bin/perl
# FILE .../app/Makefile
#
# written:       1999-04-25
# latest update: 1999-04-25 10:22:59
# $Id: Makefile,v 1.4 2002/12/24 07:02:27 gonter Exp $
#

all : all.utils

all.ned:
	(cd ned;make all.groups all)

all.utils:
	(cd sgml;    make)
	(cd nl_kr;   make)
	(cd lex;     make)
	(cd lexicon; make)

install: install.utils

install.utils:
	(cd sgml;    make install)
	(cd nl_kr;   make install)
	(cd lexicon; make install)

# do not install this yet!
install.broken:
	(cd lexicon; make install)

clean: clean.ned clean.utils

clean.ned:
	(cd ned;     make clean)

clean.utils:
	(cd sgml;    make clean)
	(cd nl_kr;   make clean)
	(cd lex;     make clean)
	(cd lexicon; make clean)

