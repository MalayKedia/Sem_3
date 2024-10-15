/*
 * Code to read the extended ascii "din" format for Dinero IV.
 * Written by Jan Edler
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
 * $Header: /home/edler/dinero/d4/RCS/xdinfmt.c,v 1.4 1997/12/12 20:36:39 edler Exp $
 */

#include <stddef.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "d4.h"
#include "cmdd4.h"
#include "tracein.h"


/*
 * Read in ASCII from standard input
 * Expect 3 significant fields per line:
 *	accesstype address size
 * The rest of the data input line is ignored so it may be used for comments.
 *
 * Accesstype is
 *	r  read
 *	w  write
 *	i  instruction fetch
 *	m  miscellaneous (like a read but won't generate prefetch)
 *	c  copyback (no invalidate implied)
 *	v  invalidate (no copyback implied)
 * Address and size are hexadecimal, with optional 0x or 0X prefix.
 */

d4memref
tracein_xdin()
{
	static double tcount = 1;	/* double to increase range */
	static char badatype[] = "xdin format error on trace record %.0f: unknown atype: %s"
				 "Consider -informat d for Dinero III input format\n";
	static char badaddr[] = "xdin format error on trace record %.0f: non hex digit (code 0x%x) in address\n";
	static char shortline[] = "xdin format error on trace record %.0f: short line\n";
	static char badsize[] = "xdin format error on trace record %.0f: non hex digit (code 0x%x) in size\n";
	static char nosize[] = "xdin format error on trace record %.0f: missing size\n";
	char errline[128];
	d4addr addr;
	int size, atype;
	d4memref r;
	int c, cc;

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

	/* the accesstype is just 1 char */
	switch (c) {
	default:
		errline[0] = c;
		fgets (errline+1, sizeof(errline)-1, stdin);
		errline[strlen(errline)-1] = '\n'; /* ensure trailing \n */
		die (badatype, tcount, errline);
		/* no return */
	case 'r':
	case 'R':
		atype = D4XREAD;
		break;
	case 'w':
	case 'W':
		atype = D4XWRITE;
		break;
	case 'i':
	case 'I':
		atype = D4XINSTRN;
		break;
	case 'm':
	case 'M':
		atype = D4XMISC;
		break;
	case 'c':
	case 'C':
		atype = D4XCOPYB;
		break;
	case 'v':
	case 'V':
		atype = D4XINVAL;
		break;
	}
	cc = getchar();
	if (cc == '\n')
		die (shortline, tcount);
	if (cc != ' ' && cc != '\t') {
		errline[0] = c;
		errline[1] = cc;
		fgets (errline+2, sizeof(errline)-2, stdin);
		errline[strlen(errline)-1] = '\n'; /* ensure trailing \n */
		die (badatype, tcount, errline);
	}

	/* skip whitespace between atype and address */
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

	/* skip whitespace between addr and size */
	while (c == ' ' || c == '\t')
		c = getchar();
	if (c == EOF || c == '\n')
		die (nosize, tcount);
	
	/* now get the size */
	if (!isxdigit(c))
		die (badsize, tcount, c);
	size = c - (isdigit(c) ? '0' : ((islower(c) ? 'a' : 'A') - 10));
	c = getchar(); 
	if ((c == 'x' || c == 'X') && size == 0)
		c = getchar();	/* ignore leading 0x or 0X */
	while (isxdigit(c)) {
		size *= 16;
		size += c - (isdigit(c) ? '0' : ((islower(c) ? 'a' : 'A') - 10));
		c = getchar();
	}
	if (c != EOF && c != '\n' && c != ' ' && c != '\t')
		die (badsize, tcount, c);

	/* skip rest of line */
	while (c != '\n' && c != EOF)
		c = getchar();
	r.accesstype = atype;
	r.address = addr;
	r.size = size;
	tcount += 1;
	return r;
}
