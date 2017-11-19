#
# $Id: Makefile,v 1.8 2007/06/10 21:10:15 gonter Exp $
#

all:
	(cd contrib/md5 && make)
	(cd ds          && make)
	(cd sbr/misc    && make)
	(cd window      && make)

all2: all
	(cd ds && make all.using-tcl)

clean:
	(cd contrib/md5 &&  make clean)
	(cd ds          &&  make clean)
	(cd sbr/misc    &&  make clean)
	(cd window      &&  make clean)
	rm -f libgg.a
