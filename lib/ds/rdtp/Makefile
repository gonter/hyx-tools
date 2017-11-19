#
# FILE %ds/rdtp/make-ux
#
# written:       1996-04-01
# latest update: 1999-05-08  9:50:49
#
# ----------------------------------------------------------------------------
CC=cc
OPTS=-I. -I/usr/local/include -g
# OPTS=-I. -O -pedantic -Wall -Wuninitialized -Wunused -Wshadow
LIB=../../libgg.a

all: lib

# ----------------------------------------------------------------------------
all.00= \
  rdtp0001.o rdtp0002.o rdtp0003.o rdtp0004.o rdtp0005.o

all.01= \
  rdtp0101.o rdtp0102.o rdtp0103.o rdtp0104.o rdtp0105.o \
  rdtp0106.o rdtp0107.o rdtp0108.o rdtp0109.o rdtp0110.o \
  rdtp0111.o rdtp0112.o rdtp0113.o rdtp0114.o rdtp0115.o \
  rdtp0116.o

all.02= \
  rdtp0201.o rdtp0202.o rdtp0203.o rdtp0204.o rdtp0205.o \
  rdtp0206.o rdtp0207.o rdtp0208.o

all.03= \
  rdtp0301.o rdtp0302.o rdtp0303.o rdtp0304.o rdtp0305.o \
  rdtp0306.o rdtp0307.o rdtp0308.o rdtp0309.o rdtp0310.o \
  rdtp0311.o rdtp0312.o rdtp0313.o rdtp0314.o rdtp0315.o \
  rdtp0316.o rdtp0317.o rdtp0318.o rdtp0319.o rdtp0320.o \
  rdtp0321.o rdtp0322.o \
  rdtp0341.o rdtp0342.o rdtp0343.o rdtp0344.o rdtp0345.o \
  rdtp0346.o rdtp0347.o rdtp0348.o

all.04= \
  rdtp0403.o rdtp0413.o rdtp0421.o rdtp0422.o rdtp0423.o

all.test : rt1_rtf.exe rt1_sgml.exe

# ----------------------------------------------------------------------------
lib: $(all.00) $(all.01) $(all.02) $(all.03) $(all.04)
	ar ru $(LIB) $?
	touch lib

# ----------------------------------------------------------------------------
.c.o:
	$(CC) $(OPTS) -c $?

clean:
	rm -f *.o lib

# ----------------------------------------------------------------------------
rt1_rtf.o : rt1.c
	$(CC) $(OPTS) -DRTF -c $?

rt1_rtf : rt1_rtf.o $(all.00) $(all.01) $(all.02)
	$(CC) -o $@ $?

# ----------------------------------------------------------------------------
rt1_sgml.o : rt1.c
	$(CC) $(OPTS) -DRTF -c $?

rt1_sgml : rt1_sgml.o $(all.00) $(all.01) $(all.03)
	$(CC) -o $@ $?

