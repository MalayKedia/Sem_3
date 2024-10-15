/*
 * Convert pixie traditional 32-bit trace output to either
 * Dinero III's "din" format, or Dinero IV's "extended din" format (-4 arg).
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
 * $Header: /home/edler/dinero/d4/testing/RCS/p2d.c,v 1.5 1997/12/11 16:59:21 edler Exp $
 */

/*
 * Acknowledgements:
 * Mark Hill (markhill@cs.wisc.edu) wrote and documented the
 * input format for dineroIII
 * Mike Smith (smith@eecs.harvard.edu) documented pixie,
 * including the trace format.
 * Mike Uhler (uhler@gmu.mti.sgi.com) clarified some issues
 * in the pixie output format.
 */

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include "../d4.h"

#if UINT_MAX < 0xffffffff
#error "unsigned int is < 32 bits"
#endif
#if UCHAR_MAX != 255
#error "unsigned char not 8 bits"
#endif

/*
 * Thanks to Mike Smith (smith@eecs.harvard.edu) for info on the
 * pixie trace output.
 *
 * pixie input consists of 32-bit words,
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

unsigned char inbuf[8192];
char *progname = "p2d";
char usage[] = "Usage: %s [-4] [-b beginaddr] [-e endaddr]\n";

int flag4;	/* set if we are to produce extended din format */

char atypes[] = "012345";	/* din-style access types ("labels") */
char atype4[] = "rwimcv";	/* extended din access types */

int
main (int argc, char **argv)
{
	int i;
	int nread;
	unsigned int addr;		/* address from pixie */
	unsigned int reftype, count;	/* from pixie */
	unsigned int iaddr = ~0;	/* current instr address */
	unsigned int c;			/* iterator for ifetching */
	unsigned int beginaddr = 0;	/* discard before seeing this */
	unsigned int endaddr = 0;	/* discard after seeing this */
	unsigned int icnt, dcnt;
	int size = 0;
	int discard = 0;
	extern int optind;
	extern char *optarg;

	if (argc > 0)
		progname = argv[0];
	if (argc > 1) {
		while ((i=getopt(argc,argv,"4b:e:")) != EOF) {
			switch (i) {
			case '4': flag4 = 1;
				  strcpy (atypes, atype4);
				  break;
			case 'b': beginaddr = strtoul (optarg, NULL, 0);
				  break;
			case 'e': endaddr = strtoul (optarg, NULL, 0);
				  break;
			case '?':
				  fprintf (stderr, usage, progname);
				  return 1;
			}
		}
		if (optind < argc) {
			fprintf (stderr, usage, progname);
			return 1;
		}
		if (beginaddr != 0)
			discard = 1;
	}
	icnt = 1;
	dcnt = 1;
	while ((nread = read (0, inbuf, sizeof inbuf)) > 0) {
		if (nread % 4) {
			fprintf (stderr, "%s: trace input not word aligned\n",
					progname);
			return 1;
		}
		for (i = 0;  i < nread;  i += 4) {
#ifndef SWAB
			count = reftype = inbuf[i+0];
			count >>= 4;
			reftype &= 15;
			addr = (inbuf[i+1]<<16)+(inbuf[i+2]<<8)+(inbuf[i+3]<<0);
#else
			count = reftype = inbuf[i+3];
			count >>= 4;
			reftype &= 15;
			addr = (inbuf[i+2]<<16)+(inbuf[i+1]<<8)+(inbuf[i+0]<<0);
#endif
			/*
			 * Dinero input:
			 * one record per line, each consisting of a type
			 * and addr.  The types are as follows:
			 *	0 load
			 *	1 store
			 * 	2 ifetch
			 *	3 unknown
			 *	4 cache flush
			 * Anything else on the line is ignored.
			 */

			/* figure out size and possibly round address */
			switch (reftype) {
			default:
				fprintf (stderr,
					"%s: unknown pixie reftype=%u\n",
					progname, reftype);
				/* fall through */
			case SYSCALL:
			case LW:
			case LWC1:
			case SW:
			case SWC1:
			case ANNUL:	/* this one doesn't actually matter */
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
			case BB:
				/* handled below */
				break;
			}

			/* do the work */
			switch (reftype) {
			default:	/* warning already issued */
				if (addr == endaddr && addr != 0)
					discard = 1;
				else if (!discard) {
					printf ("%c %x 4\ti%u\n", atypes[D4XINSTRN], iaddr, icnt);
					printf ("%c %x %x\td%u\n", atypes[D4XMISC], addr, size, dcnt);
				}
				if (addr == beginaddr && addr != 0)
					discard = 0;
				dcnt++;
				break;
			case LW:
			case LD:
			case LWC1:
			case LDC1:
				if (addr == endaddr && addr != 0)
					discard = 1;
				else if (!discard) {
					printf ("%c %x 4\ti%u\n", atypes[D4XINSTRN], iaddr, icnt);
					printf ("%c %x %x\td%u\n", atypes[D4XREAD], addr, size, dcnt);
				}
				if (addr == beginaddr && addr != 0)
					discard = 0;
				dcnt++;
				break;
			case SW:
			case SD:
			case SB:
			case SH:
			case SWR:
			case SWL:
			case SWC1:
			case SDC1:
				if (addr == endaddr && addr != 0)
					discard = 1;
				else if (!discard) {
					printf ("%c %x 4\ti%u\n", atypes[D4XINSTRN], iaddr, icnt);
					printf ("%c %x %x\td%u\n", atypes[D4XWRITE], addr, size, dcnt);
				}
				if (addr == beginaddr && addr != 0)
					discard = 0;
				dcnt++;
				break;
			case BB:
				iaddr = addr << 2;
				/* compensate for below */
				iaddr -= 4;
				icnt--;
				break;
			case SYSCALL:
				if (!discard) {
					printf ("%c %x 4\ti%u\n", atypes[D4XINSTRN], iaddr, icnt);
					printf ("%c %x %x\tsyscall %u\n", atypes[D4XMISC], addr, size, size);
				}
				break;
			case ANNUL:
				if (!discard)
					printf ("%c %x 4\ti%u\tannul\n", atypes[D4XINSTRN], iaddr, icnt);
				break;
			}
			iaddr += 4;
			icnt++;
			for (c = count;  c > 0;  c--) {
				if (!discard)
					printf ("%c %x 4\ti%d\n", atypes[D4XINSTRN], iaddr, icnt);
				iaddr += 4;
				icnt++;
			}
		}
	}
	if (nread < 0) {
		perror (progname);
		return 1;
	}
	if (endaddr != 0 && !discard)
		fprintf (stderr, "%s: -e address not found in trace stream\n",
			progname);
	return 0;
}
