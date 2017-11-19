#
# FILE %ned/Readme.txt
#
# written:       1995-11-12
# latest update: 1999-04-10 18:21:16
# $Id: readme.txt,v 1.3 2000/08/24 15:10:10 gonter Exp $
#

This is the source for Ned, a SGML-ish hypertext editor with a default
key binding as a mixture of WordStar(tm) and vi.

These files currently need to be edited to adopted for a Unix compilation
run, e.g. with TK or Curses:

Everything is set up for the Tk version.

  --------------------------------------------------------------------------
  filename              Tags
  --------------------------------------------------------------------------
  ed.h                  #define USE_TK
  Makefile              select curses, ncurses, tcl, tk libs
  make-sbr              select W_MODEL_{CURSES,NCURSES,TK}
  09/Makefile           select objects
  unix/Makefile         select objects
  --------------------------------------------------------------------------

If this is going to be compiled on HP/UX, set the environment variable
CCOPTS to -Ae.

For more information, see also (dirinf).fm, NED hypertext information,
and the documentation cluster.
