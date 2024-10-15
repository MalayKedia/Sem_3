/*
 * Code to read 64-bit pixie -idtrace_ext output from IRIX systems
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
 * $Header: /home/edler/dinero/d4/RCS/pixie64fmt.c,v 1.4 1997/12/11 16:59:49 edler Exp $
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
 * 64-bit pixie trace format consists of 64-bit words,
 * the most significant 8 bits is a count,
 * the next 8 bits are a reference type, and
 * the remaining 48 bits are the address.
 * The address for basic blocks is a word offset
 * from the beginning of the DSO (i.e., (address - dso start)/4).
 * The addresses for loads and stores are byte addresses.
 * The count field for basic blocks tells how many sequential
 * instructions to fetch before doing something else.
 * The count field for loads and stores tells how many ifetches
 * to do after the load or store, before doing something else.
 *
 * We currently assume the "n32" execution mode, and therefore
 * truncate all addresses to their low 32 bits (sizeof(int)==4).
 *
 * We currently only support nonshared executables, although the
 * format supports full use of DSOs.  Also, to be perfectly legitimate,
 * we should map data addresses to correspond to what they would have been
 * in the unpixified program (they may well have been displaced
 * in the pixified version); we don't do that either.
 *
 * We could automatically distinquish between 32-bit and 64-bit formats,
 * but we don't.
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
#define REF_UNDEF 15	/* undefined; can distinguish between 32 and 64 bit */
#define DSO_OPEN 16	/* DSO number */
#define DSO_MAP_HI 17	/* high part of DSO "quick start" address */
#define DSO_MAP_LO 18	/* low part of DSO "quick start" address */
#define DSO_NAME 19	/* 1 character of DSO name */
#define DSO_CLOSE 20	/* close DSO by number */
#define DSO_MAX_IOFFSET 25 /* max instruction offset from text start */
#define SEGMENT_MOVED_STATIC 26 /* amount pixie moved the data segment */
#define DSO_MOVED_DYNAMIC 27 /* amount rld moved the DSO */
#define NUM_DATA_SEGMENTS 28 /* number of data segments in the DSO */
#define SEGMENT_MAP_HI 29 /* high part of "quick start" address of segment */
#define SEGMENT_MAP_LO 30 /* low part */
#define SEGMENT_SIZE 31	/* size of data segment in bytes */

#define MIN(a,b)	((a)<(b)?(a):(b))

#ifndef PIXIE_SWAB
#define PIXIE_SWAB 0
#endif

/* We need a way to keep deferred references */
#define NSTACK 300
static d4memref stack[NSTACK];	/* to store deferred references */
static d4memref *sptr = stack;	/* stack pointer */

#define push_ref(atype,addr,sz) do {					\
		assert (sptr < &stack[NSTACK]);				\
		sptr->accesstype = atype;				\
		sptr->address = addr;					\
		sptr++->size = sz;					\
	} while (0)	/* expect semicolon */

#define pop_ref()	*--sptr

d4memref
tracein_pixie64()
{
	static char dynlib[] = "pixie64 input (reftype %d): dynamically linked executable not supported\n";
	static int once = 1;
	static unsigned char inbuf[4096];
	static unsigned char *inptr = NULL;
	static unsigned char *endptr = NULL;
	static unsigned int iaddr = ~0;	/* current instr address */
	static unsigned int textbase = 0;
	unsigned int addr;		/* address from pixie */
	int reftype, count;		/* from pixie */
	int c;				/* iterator for ifetching */
	int size;
	d4memref r;

	if (sptr > stack)
		return pop_ref();
again:
	if (inptr == NULL) {	/* need to fill inbuf */
		int nread = read (0, inbuf, sizeof inbuf);
		if (nread < 0)
			die ("pixie64 input error: %s\n", strerror (errno));
		if (nread <= 0) {
			r.address = 0;
			r.size = 0;
			r.accesstype = D4TRACE_END;
			return r;
		}
		if ((nread % 8) != 0)
			die ("pixie64 trace input not double word aligned\n");
		inptr = inbuf;
		endptr = inbuf + nread;
		if (once) {
			once = 0;
			if (inptr[PIXIE_SWAB ? 7 : 0] != REF_UNDEF)
				die ("pixie64 input: header format %d instead of %d\n",
				     inptr[PIXIE_SWAB ? 7 : 0], REF_UNDEF);
			inptr += 8;
			if (inptr >= endptr)
				inptr = NULL;
			goto again;
		}
	}
#if PIXIE_SWAB /* maybe this will work for trace from little endian machine */
	count = inptr[7];
	reftype = inptr[6];
	addr = 0;
	for (c = MIN(6,sizeof(addr))-1;  c >= 0;  c--)
		addr = (addr<<8) | inptr[c];
#else /* SGI MIPS-based machines are big-endian */
	count = inptr[0];
	reftype = inptr[1];
	addr = 0;
	for (c = MIN(6,sizeof(addr))-1;  c >= 0;  c--)
		addr = (addr<<8) | inptr[7-c];
#endif
	inptr += 8;
	if (inptr >= endptr)
		inptr = NULL;	/* cause refill on next call */

	switch (reftype) {
	case REF_UNDEF:	/* should not happen */
	default:
		fprintf (stderr,
			"%s: unknown pixie64 reftype=%u\n", progname, reftype);
		goto again;

	case DSO_OPEN:
	case DSO_NAME:
	case DSO_CLOSE:
	case DSO_MAX_IOFFSET:
	case SEGMENT_MOVED_STATIC:
	case SEGMENT_MAP_HI:
	case SEGMENT_MAP_LO:
	case SEGMENT_SIZE:
		goto again;	/* ignore these */

	case DSO_MAP_HI:
#if INT_MAX > 0x7fffffff
		textbase |= ((addr&0xffffffff)<<32);
#endif
		goto again;
	case DSO_MAP_LO:
		textbase |= (addr & 0xffffffff);
		goto again;
	case DSO_MOVED_DYNAMIC:
		if (addr != 0)
			die (dynlib, reftype);
		goto again;
	case NUM_DATA_SEGMENTS:
		if (addr != 1)
			die (dynlib, reftype);
		goto again;
	case BB:
		iaddr = addr << 2;	/* convert word address to byte */
		iaddr += textbase;	/* base address for DSO 0 */
		if (count == 0)
			goto again;	/* 1st instr is load/store/whatever */
		size = 4;
		count--;	/* counteract increment, below */
		break;
	case LD:
	case LDC1:
	case SD:
	case SDC1:
		size = 8;
		addr &= ~7;
		break;
	case SYSCALL:
	case LW:
	case LWC1:
	case SW:
	case SWC1:
	case ANNUL:
		size = 4;
		addr &= ~3;
		break;
	case SH:
		size = 2;
		addr &= ~1;
		break;
	case SB:
		size = 1;
		break;
	case SWR:	/* assume big endian */
		size = addr%4 + 1;
		addr &= ~3;
		break;
	case SWL:	/* assume big endian */
		size = 4 - (addr%4);
		break;
	}
	count++;	/* allow for current instruction */

	/* push excess instructions onto stack in reverse order */
	for (c = count;  c > 1;  c--)
		push_ref (D4XINSTRN, iaddr + c*4 - 4, 4);

	switch (reftype) {
	default:
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
