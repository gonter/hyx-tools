#
# FILE %nl_kr/make-ux
#
# Makefile for the NL-KR system under Unix
# depends on %sgml/makefile.ux
#
# written:       1991 03 19: for AIX
#                1993-03-07: full revision
# latest update: 2001-08-25 23:28:48
# $Id: Makefile,v 1.11 2005/03/11 23:41:43 gonter Exp $
#
# ----------------------------------------------------------------------------

CC=cc
OPTS= -I.
# OPTS=-I. -O -pedantic -Wall -Wuninitialized -Wunused -Wshadow
lib=../../lib/libgg.a

SYMS= new_TFB_HANDLE tfb_fetch_entry2 tfb_fetch_entry \
      new_HYX_CLUSTER_CONTROL \
      new_LMDQS lmd_deref1 lmd_print_doc_hit_list_stdout \
      lmd_print_document_info_list_stdout \
      WRL_string DIL_next

# installation directory, e.g. for AFS
bindir=/usr/local/bin

bins=deref lutmake lutdump luttest tfbget tfblut
bins2=ta tasgml

# ----------------------------------------------------------------------------
all : $(bins) $(bins2)

all.2 : lutprint

install : all
	cp $(bins) $(bindir)

clean :
	rm -f *.o $(bins) $(bins2)

distrib :
	sh -c "mkdir -p distrib/gg"
	sh -c "~/.ned/filelist.pl -dist distrib $(bins) -sym $(SYMS)"
	cp tfb.i Makefile-swig.pl README.lmd distrib

# ----------------------------------------------------------------------------
.c.o:
	$(CC) $(OPTS) -c $*.c

# ----------------------------------------------------------------------------
lutmake1=lutmake.o
lutdump1=lutdump.o
luttest1=luttest.o
lutprint1=lutprint.o
deref1=deref.o
ta1=ta.o
tasgml1=tasgml.o

# ----------------------------------------------------------------------------
lutmake : $(lutmake1) $(lib)
	$(CC) -o lutmake $(lutmake1) $(lib)

lutdump : $(lutdump1) $(lib)
	$(CC) -o lutdump $(lutdump1) $(lib)

luttest : $(luttest1) $(lib)
	$(CC) -o luttest $(luttest1) $(lib)

lutprint : $(lutprint1) $(lib)
	$(CC) -o lutprint $(lutprint1) $(lib)

deref : $(deref1) $(lib)
	$(CC) -o deref $(deref1) $(lib)

# ----------------------------------------------------------------------------
ta : $(ta1) $(lib)
	$(CC) -o ta $(ta1) $(lib)

tasgml : $(tasgml1) $(lib)
	$(CC) -o tasgml $(tasgml1) $(lib)

# ----------------------------------------------------------------------------
tfblut: tfblut.o $(lib)
	$(CC) -o tfblut tfblut.o $(lib)

tfbget: tfbget.o $(lib)
	$(CC) -o tfbget tfbget.o $(lib)

# ----------------------------------------------------------------------------
Makefile-swig : Makefile-swig.pl
	perl Makefile-swig.pl >Makefile-swig
all.3 : Makefile-swig
	make -f Makefile-swig

