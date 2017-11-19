#
# FILE %ds/strings/make-ux
#
# string processing library
#
# written:       1995-12-12
# latest update: 1999-05-08  9:51:58
#
# ----------------------------------------------------------------------------
CC=cc
# CF=-pedantic -Wall -Wuninitialized -Wunused -Wshadow
OPTS=-g -I. -I/usr/local/include $(cf)
LIB=../../libgg.a

all: lib

# ----------------------------------------------------------------------------
LIBOBJS0= \
  str_0001.o str_0002.o str_0003.o str_0004.o str_0005.o str_0006.o \
  str_0007.o str_0008.o str_0009.o str_0010.o str_0011.o str_0012.o \
  str_0013.o str_0014.o str_0015.o str_0016.o str_0017.o str_0018.o \
  str_0019.o str_0020.o str_0021.o str_0022.o str_0023.o str_0024.o \
  str_0025.o str_0026.o str_0027.o str_0028.o str_0029.o str_0030.o \
  str_0031.o str_0032.o str_0033.o str_0034.o str_0035.o str_0036.o \
  str_0037.o str_0037.o str_0039.o str_0040.o str_0041.o str_0042.o \
  str_0043.o str_0044.o str_0045.o str_0046.o str_0047.o str_0048.o \
  str_0049.o str_0050.o str_0051.o str_0052.o str_0053.o

LIBOBJS1= \
  str_0107.o str_0108.o str_0109.o \
  str_0201.o str_0202.o str_0203.o str_0204.o \
  str_0302.o str_0303.o str_0304.o

# only needed on certain systems...
LIBOBJS99= str_0301.o

# ----------------------------------------------------------------------------
lib: $(LIBOBJS0) $(LIBOBJS1) $(LIBOBJS2)
	ar ru $(LIB) $(LIBOBJS0)
	ar ru $(LIB) $(LIBOBJS1)
	touch lib

.c.o:
	$(CC) $(OPTS) -c $?

# ----------------------------------------------------------------------------
TEST_OK= strndup-test-ok
TEST_FAIL= strndup-test-fail
clean:
	rm -f *.o lib

test-ok:  $(TEST_OK)
test-fail: $(TEST_FAIL)

strndup-test-fail : strndup-test.c
	$(CC) $(OPTS) -o $@ $?

strndup-test-ok : strndup-test.c str_0302.o
	$(CC) $(OPTS) -o $@ -DTEST_OK strndup-test.c str_0302.o
