/*
 * Some glue for trace input handling for Dinero IV's command interface.
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
 * $Header: /home/edler/dinero/d4/RCS/tracein.c,v 1.8 1997/12/12 20:36:39 edler Exp $
 */


/*
 * This file contains code to verify the trace input format specified
 * and set up to make the call.
 * Hopefully, this and tracein.h will be the only existing source files
 * you need to modify when adding a new input format to Dinero IV.
 * The bulk of the new format-specific code should go into a new source file.
 */

#include <stddef.h>
#include <stdio.h>
#include "d4.h"
#include "cmdd4.h"
#include "tracein.h"

d4memref (*input_function) (void);

/*
 * This function is called to get each trace record
 * We also take care of skipping records:f
 */
void
verify_trace_format()
{
	switch (informat) {
	default:  shorthelp ("unknown input format '%c'\n", informat);
	case 0:	  shorthelp ("no input format specified\n");
	case 'D':				/* extended "din" format */
		  input_function = tracein_xdin;
		  break;
	case 'd':				/* traditional "din" format */
		  input_function = tracein_din;
		  break;
	case 'p':				/* 32-bit pixie -idtrace format */
		  input_function = tracein_pixie32;
		  break;
	case 'P':				/* 64-bit pixie -idtrace format */
		  input_function = tracein_pixie64;
		  break;
	case 'b':				/* binary format, similar to din */
		  input_function = tracein_binary;
		  break;
	}
}


/* list the choices for -informat */
void
help_trace_format (int indent)
{
	printf ("\n %*s (D=extended din, d=traditional din, p=pixie32, P=pixie64,\n %*s b=binary)",
		indent, " ", indent, " ");
}
