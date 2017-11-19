#
# FILE %ds/make-ux
#
# written:       1995-12-12
# latest update: 1999-04-10 11:53:49
# $Id: Makefile,v 1.9 2007/11/11 11:27:31 gonter Exp $
#
# ----------------------------------------------------------------------------

all: all.simple all.exp # all.using-tcl all.exp2

# things that should work
all.simple:
	(cd array      && make)
	(cd attlist    && make)
	(cd cal        && make)
	(cd codes      && make)
	(cd dyb        && make)
	(cd ggcrypt    && make)
	(cd hytxt      && make)
	(cd hyxl       && make)
	(cd irdb       && make)
	(cd lmd        && make)
	(cd lmd5       && make)
	(cd lut        && make)
	(cd mime       && make)
	(cd rdtp       && make)
	(cd streams    && make)
	(cd strings    && make)
	(cd tfb        && make)
	(cd url        && make)
	(cd varspace   && make)
	(cd ytree      && make)
	(cd zip        && make)

# things that use TCL
all.using-tcl:
	(cd tcl        && make)
	(cd vieos      && make)

# things that might work
all.exp:
	(cd bbc       && make)
	(cd hyxp      && make)
	(cd hyxta     && make)

# things that most certainly do not work!
all.exp2:
	(cd lxs       && make)
	(cd rtf       && make)

all.bin:
	(cd codes      && make all.bin)
	(cd tfb        && make all.bin)
	(cd lmd5       && make all.bin)
	(cd vieos      && make all.bin)

# ----------------------------------------------------------------------------
clean: clean.simple clean.exp # clean.using-tcl clean.exp2

clean.simple:
	(cd array      && make clean)
	(cd attlist    && make clean)
	(cd cal        && make clean)
	(cd codes      && make clean)
	(cd dyb        && make clean)
	(cd ggcrypt    && make clean)
	(cd hytxt      && make clean)
	(cd hyxl       && make clean)
	(cd irdb       && make clean)
	(cd lmd        && make clean)
	(cd lmd5       && make clean)
	(cd lut        && make clean)
	(cd rdtp       && make clean)
	(cd streams    && make clean)
	(cd strings    && make clean)
	(cd tfb        && make clean)
	(cd url        && make clean)
	(cd varspace   && make clean)
	(cd ytree      && make clean)
	(cd zip        && make clean)

clean.exp:
	(cd bbc        && make clean)
	(cd hyxp       && make clean)
	(cd hyxta      && make clean)

clean.exp2:
	(cd lxs        && make clean)
	(cd rtf        && make clean)

clean.using-tcl:
	(cd tcl        && make clean)
	(cd vieos      && make clean)

