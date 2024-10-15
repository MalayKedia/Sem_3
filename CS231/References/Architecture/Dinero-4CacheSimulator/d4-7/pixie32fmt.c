/*
 * Code to read 32-bit pixie -idtrace output from IRIX systems
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
 * $Header: /home/edler/dinero/d4/RCS/pixie32fmt.c,v 1.4 1997/12/11 16:59:49 edler Exp $
 */

#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include "d4.h"
#include "cmdd4.h"
#include "tracein.h"

/*
 * Acknowledgements:
 * Mark Hill (markhill@cs.wisc.edu) wrote and documented the
 * din input format for dineroIII
 * Mike Smith (smith@eecs.harvard.edu) documented pixie,
 * including the trace format.
 * Mike Uhler (uhler@gmu.mti.sgi.com) and
 * Marty Itzkowitz (martyi@nubbins.engr.sgi.com)
 * provided updated information about the pixie trace output formats.
 */



/*
 * 32-bit pixie trace format consists of 32-bit words,
 * the most significant 4 bits is a count,
 * the next 4 bits are a reference type, and
 * the remaining 24 bits are the address.
 * The address for basic blocks is a word address (i.e., shifted right 2 bits),
 * while the addresses for loads and stores are byte addresses.
 * The count field for basic blocks tells how many sequential
 * instructions to fetch before doing something else.
 * The count field for loads and stores tells how many ifetches
 * to do after the load or store, before doing something else.
 */
#define LW	0	/* load word */
#define LD	1	/* load double */
#define SW	2	/* store word */
#define SD	3	/* store double */
#define SB	4	/* store byte */
#define SH	5	/* store half-word */
#define SWR	6	/* store word right */
#define SWL	7	/* store word left */
#define LWC1	8	/* load word coprocessor 1 */
#define LDC1	9	/* load double coprocessor 1 */
#define SWC1	10	/* store word coprocessor 1 */
#define SDC1	11	/* store double coprocessor 1 */
#define BB	12	/* enter basic block */
#define ANNUL	13	/* annul conditional delay slot */
#define SYSCALL	14	/* system call */

/* We need a way to keep deferred references */
static d4memref stack[16];	/* to store deferred references */
static d4memref *sptr = stack;	/* stack pointer */

#define push_ref(atype,addr,sz) do {					\
		assert (sptr < &stack[15]);				\
		sptr->accesstype = atype;				\
		sptr->address = addr;					\
		sptr++->size = sz;					\
	} while (0)	/* expect semicolon */

#define pop_ref()	*--sptr


d4memref
tracein_pixie32()
{
	static unsigned char inbuf[4096];
	static unsigned char *inptr = NULL;
	static unsigned char *endptr = NULL;
	static unsigned int iaddr = ~0;	/* current instr address */
	unsigned int addr;		/* address from pixie */
	unsigned int reftype, count;	/* from pixie */
	unsigned int c;			/* iterator for ifetching */
	int size;
	d4memref r;

	if (sptr > stack) {
		r = pop_ref();
		return r;
		/* return pop_ref(); this evoked a compiler bug on SGI/IRIX6.?, so avoid it */
	}
again:
	if (inptr == NULL) {	/* need to fill inbuf */
		int nread = read (0, inbuf, sizeof inbuf);
		if (nread < 0)
			die ("pixie32 input error: %s\n", strerror (errno));
		if (nread <= 0) {
			r.address = 0;
			r.size = 0;
			r.accesstype = D4TRACE_END;
			return r;
		}
		if ((nread % 4) != 0)
			die ("pixie32 trace input not word aligned\n");
		inptr = inbuf;
		endptr = inbuf + nread;
	}
#if PIXIE_SWAB /* maybe this will work for trace from little endian machine */
	count = reftype = inptr[3];
	count >>= 4;
	reftype &= 15;
	addr = (inptr[2]<<16)+(inptr[1]<<8)+(inptr[0]<<0);
#else
	count = reftype = inptr[0];
	count >>= 4;
	reftype &= 15;
	addr = (inptr[1]<<16)+(inptr[2]<<8)+(inptr[3]<<0);
#endif
	inptr += 4;
	if (inptr >= endptr)
		inptr = NULL;	/* cause refill on next call */

	if (reftype == BB) {
		iaddr = addr << 2;	/* convert word address to byte */
		if (count == 0)
			goto again;	/* 1st instr is load/store/whatever */
	}
	else {
		count++;	/* allow for current instruction */
	}

	/* push excess instructions onto stack in reverse order */
	for (c = count;  c > 1;  c--)
		push_ref (D4XINSTRN, iaddr + c*4 - 4, 4);

	switch (reftype) {
	default:
		fprintf (stderr,
			"%s: unknown pixie32 reftype=%u\n", progname, reftype);
		/* fall through */
	case SYSCALL:
	case LW:
	case LWC1:
	case SW:
	case SWC1:
	case ANNUL:	/* this one doesn't actually matter */
	case BB:	/* this one doesn't actually matter */
		size = 4;
		addr &= ~3;
		break;
	case LD:
	case LDC1:
	case SD:
	case SDC1:
		size = 8;
		addr &= ~7;
		break;
	case SH:
		size = 2;
		addr &= ~1;
		break;
	case SB:
		size = 1;
		break;
	case SWL:	/* assume big endian */
		size = (addr%4) + 1;
		addr &= ~3;
		break;
	case SWR:	/* assume big endian */
		size = 4 - (addr%4);
		break;
	}

	switch (reftype) {
	default:	/* warning already issued */
		/* fall through */
	case SYSCALL:
		push_ref (D4XMISC, addr, size);
		break;
	case LW:
	case LD:
	case LWC1:
	case LDC1:
		push_ref (D4XREAD, addr, size);
		break;
	case SWL:
	case SWR:
	case SW:
	case SD:
	case SB:
	case SH:
	case SWC1:
	case SDC1:
		push_ref (D4XWRITE, addr, size);
		break;
	case ANNUL:	/* annulled instruction; just do the ifetch */
	case BB:	/* leading instruction of basic block */
		break;
	}
	r.accesstype = D4XINSTRN;
	r.address = iaddr;
	r.size = 4;	/* MIPS instructions are all 4 bytes */
	iaddr += count*4;
	return r;
}
