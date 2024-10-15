# Makefile for Dinero IV testing stuff
# Written by Jan Edler
#
# $Header: /home/edler/dinero/d4/testing/RCS/Makefile,v 1.6 1997/12/08 19:34:36 edler Exp $

ALL = p2d p2b

all: $(ALL)

p2d: p2d.c
	$(CC) $(CFLAGS) -o p2d p2d.c

p2b: p2b.c
	$(CC) $(CFLAGS) -o p2b p2b.c

clean:
	-rm -fr *.o core

clobber: clean
	-rm -fr $(ALL)

distclean: clobber
