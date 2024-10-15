/*
 * Code to read the traditional ascii "din" format for Dinero IV.
 * Written by Jan Edler and Mark D. Hill
 * 
 * Copyright (C) 1997 NEC Research Institute, Inc. and Mark D. Hill.
 * All rights reserved.
 * Copyright (C) 1985, 1989 Mark D. Hill.  All rights reserved.
 * 
 * Permission to use, copy, modify, and distribute this software and
 * its associated documentation for non-commercial purposes is hereby
 * granted (for commercial purposes see below), provided that the above
 * copyright notice appears in all copies, derivative works or modified
 * versions of the software and any portions thereof, and that both the
 * copyright notice and this permission notice appear in the documentation.
 * NEC Research Institute Inc. and Mark D. Hill shall be given a copy of
 * any such derivative work or modified version of the software and NEC
 * Research Institute Inc.  and any of its affiliated companies (collectively
 * referred to as NECI) and Mark D. Hill shall be granted permission to use,
 * copy, modify, and distribute the software for internal use and research.
 * The name of NEC Research Institute Inc. and its affiliated companies
 * shall not be used in advertising or publicity related to the distribution
 * of the software, without the prior written consent of NECI.  All copies,
 * derivative works, or modified versions of the software shall be exported
 * or reexported in accordance with applicable laws and regulations relating
 * to export control.  This software is experimental.  NECI and Mark D. Hill
 * make no representations regarding the suitability of this software for
 * any purpose and neither NECI nor Mark D. Hill will support the software.
 * 
 * Use of this software for commercial purposes is also possible, but only
 * if, in addition to the above requirements for non-commercial use, written
 * permission for such use is obtained by the commercial user from NECI or
 * Mark D. Hill prior to the fabrication and distribution of the software.
 * 
 * THE SOFTWARE IS PROVIDED AS IS.  NECI AND MARK D. HILL DO NOT MAKE
 * ANY WARRANTEES EITHER EXPRESS OR IMPLIED WITH REGARD TO THE SOFTWARE.
 * NECI AND MARK D. HILL ALSO DISCLAIM ANY WARRANTY THAT THE SOFTWARE IS
 * FREE OF INFRINGEMENT OF ANY INTELLECTUAL PROPERTY RIGHTS OF OTHERS.
 * NO OTHER LICENSE EXPRESS OR IMPLIED IS HEREBY GRANTED.  NECI AND MARK
 * D. HILL SHALL NOT BE LIABLE FOR ANY DAMAGES, INCLUDING GENERAL, SPECIAL,
 * INCIDENTAL, OR CONSEQUENTIAL DAMAGES, ARISING OUT OF THE USE OR INABILITY
 * TO USE THE SOFTWARE.
 *
 * $Header: /home/edler/dinero/d4/RCS/dinfmt.c,v 1.2 1997/12/08 19:35:24 edler Exp $
 */

#include <stddef.h>
#include <stdio.h>
#include <ctype.h>
#include "d4.h"
#include "cmdd4.h"
#include "tracein.h"


/*
 * Read in ASCII from standard input
 * Expect ONE label and addr in hex per line.
 * Rest of data input line is ignored so it may
 * be used for comments.
 *
 * This version is a bit more forgiving than the
 * FAST_BUT_DANGEROUS_INPUT version in Dinero III.
 *
 * WARNING: If more than one tuple is put on a line,
 * all but the first tuple will be ignored.
 */

d4memref
tracein_din()
{
	static double tcount = 1;	/* double to increase range */
	static char badlabel[] = "din format error on trace record %.0f: non hex digit (code 0x%x) in label\n";
	static char badaddr[] = "din format error on trace record %.0f: non hex digit (code 0x%x) in address\n";
	static char shortline[] = "din format error on trace record %.0f: short line\n";
	d4addr addr = 0;
	int atype = 0;
	d4memref r;
	int c;

	/* skip initial whitespace */
	do {
		c = getchar();
	} while (c == ' ' || c == '\t');
	if (c == EOF) {
		r.address = 0;
		r.size = 0;
		r.accesstype = D4TRACE_END;
		return r;		/* this will trigger normal termination */
	}
	if (c == '\n')
		die (shortline, tcount);

	/* typically the label is just 1 char */
	if (!isxdigit(c))
		die (badlabel, tcount, c);
	atype = c - (isdigit(c) ? '0' : ((islower(c) ? 'a' : 'A') - 10));
	c = getchar();
	if (c != ' ' && c != '\t') {	/* rarely get rest of label */
		if ((c == 'x' || c == 'X') && atype == 0)
			c = getchar();	/* ignore leading 0x or 0X */
		if (c == '\n' || c == EOF)
			die (shortline, tcount);
		while (isxdigit(c)) {
			atype *= 16;
			atype += c - (isdigit(c) ? '0' : ((islower(c) ? 'a' : 'A') - 10));
			c = getchar();
		}
		if (c == '\n' || c == EOF)
			die (shortline, tcount);
		if (c != ' ' && c != '\t')
			die (badlabel, tcount, c);
	}

	/* skip whitespace between label and address */
	do {
		c = getchar();
	} while (c == ' ' || c == '\t');
	if (c == '\n' || c == EOF)
		die (shortline, tcount);

	/* now get the address */
	if (!isxdigit(c))
		die (badaddr, tcount, c);
	addr = c - (isdigit(c) ? '0' : ((islower(c) ? 'a' : 'A') - 10));
	c = getchar(); 
	if ((c == 'x' || c == 'X') && addr == 0)
		c = getchar();	/* ignore leading 0x or 0X */
	while (isxdigit(c)) {
		addr *= 16;
		addr += c - (isdigit(c) ? '0' : ((islower(c) ? 'a' : 'A') - 10));
		c = getchar();
	}
	if (c != EOF && c != '\n' && c != ' ' && c != '\t')
		die (badaddr, tcount, c);

	/* skip rest of line */
	while (c != '\n' && c != EOF)
		c = getchar();
	r.accesstype = atype;
	r.address = addr & ~3;	/* dineroIII is pretty much word-oriented */
	r.size = 4;
	tcount += 1;
	return r;
}
