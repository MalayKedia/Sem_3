/*
 * Binary input format handling for Dinero IV.
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
 * $Header: /home/edler/dinero/d4/RCS/binaryfmt.c,v 1.4 1997/12/08 19:35:24 edler Exp $
 */

#include <stddef.h>
#include <limits.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "d4.h"
#include "cmdd4.h"
#include "tracein.h"


/*
 * This format is pretty similar to the traditional Dinero "din" format,
 * but it supplies the size as well as address and access type, and
 * requires no conversion from ascii strings on input.
 * Each record is 8 bytes: a little-endian 4-byte-int, containing an address,
 * followed by a 2-byte little-endian size, a 1-byte access type, and a byte of padding.
 */

#define RECORD_SIZE 8

#if CHAR_BIT != 8
#error "binary format code assumes 8 bit chars"
#endif

d4memref
tracein_binary()
{
	static unsigned char inbuf[RECORD_SIZE*1024];
	static int hiwater = 0;
	static int inptr = 0;
	d4memref r;

	if (inptr > hiwater - RECORD_SIZE) {	/* need to fill inbuf */
		int nread;
		if (hiwater > inptr) {
			memcpy (inbuf, &inbuf[inptr], hiwater-inptr);
			inptr = hiwater - inptr;
		}
		else
			inptr = 0;
		nread = read (0, &inbuf[inptr], sizeof(inbuf) - inptr);
		if (nread < 0)
			die ("binary input error: %s\n", strerror (errno));
		if (nread <= 0) {
			r.accesstype = D4TRACE_END;
			r.address = 0;
			r.size = 0;
			return r;
		}
		hiwater = inptr + nread;
		inptr = 0;
	}
	r.address = (inbuf[inptr+0]<<(0*CHAR_BIT)) |
		    (inbuf[inptr+1]<<(1*CHAR_BIT)) |
		    (inbuf[inptr+2]<<(2*CHAR_BIT)) |
		    (inbuf[inptr+3]<<(3*CHAR_BIT));
	inptr += 4;
	r.size = (inbuf[inptr+0]<<(0*CHAR_BIT)) |
		 (inbuf[inptr+1]<<(1*CHAR_BIT));
	inptr += 2;
	r.accesstype = inbuf[inptr++];
	inptr++;	/* skip padding */
	return r;
}
