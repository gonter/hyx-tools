#
# FILE %ds/window/1/make-ux
#
# written:       1999-04-10
# latest update: 2000-08-24 12:59:55
# $Id: Makefile,v 1.4 2000/08/24 16:26:44 gonter Exp $
#
# ----------------------------------------------------------------------------
CC=cc
OPTS=-I. -I/usr/local/include
# OPTS=-I. -O -pedantic -Wall -Wuninitialized -Wunused -Wshadow
LIB=../../libgg.a

all: $(LIB)

# ----------------------------------------------------------------------------
LIBOBJS_tk=  win_0102tk.o  win_0111tk.o  win_0112tk.o  win_0125tk.o
LIBOBJS_cur= win_0102cur.o win_0111cur.o win_0112cur.o win_0125cur.o

# ----------------------------------------------------------------------------
$(LIB): $(LIBOBJS_tk) $(LIBOBJS_cur)
	ar ru $(LIB) $?

# --- Tk Version -------------------------------------------------------------
win_0102tk.o : win_0102.c
	$(CC) $(OPTS) -DW_MODEL_TK -o win_0102tk.o -c win_0102.c

win_0111tk.o : win_0111.c
	$(CC) $(OPTS) -DW_MODEL_TK -o win_0111tk.o -c win_0111.c

win_0112tk.o : win_0112.c
	$(CC) $(OPTS) -DW_MODEL_TK -o win_0112tk.o -c win_0112.c

win_0125tk.o : win_0125.c
	$(CC) $(OPTS) -DW_MODEL_TK -o win_0125tk.o -c win_0125.c

# --- Curses Version ---------------------------------------------------------
win_0102cur.o : win_0102.c
	$(CC) $(OPTS) -DW_MODEL_CURSES -o win_0102cur.o -c win_0102.c

win_0111cur.o : win_0111.c
	$(CC) $(OPTS) -DW_MODEL_CURSES -o win_0111cur.o -c win_0111.c

win_0112cur.o : win_0112.c
	$(CC) $(OPTS) -DW_MODEL_CURSES -o win_0112cur.o -c win_0112.c

win_0125cur.o : win_0125.c
	$(CC) $(OPTS) -DW_MODEL_CURSES -o win_0125cur.o -c win_0125.c

# ----------------------------------------------------------------------------
.c.o:
	$(CC) $(OPTS) -c $?

clean:
	rm -f *.o
