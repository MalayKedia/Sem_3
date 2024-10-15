/*
 * Declarations for trace input handling for Dinero IV's command interface.
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
 * $Header: /home/edler/dinero/d4/RCS/tracein.h,v 1.4 1997/12/08 19:35:24 edler Exp $
 */


/* One of the following functions is called to generate each trace record */
extern d4memref tracein_xdin (void);
extern d4memref tracein_din (void);
extern d4memref tracein_pixie32 (void);
extern d4memref tracein_pixie64 (void);
extern d4memref tracein_binary (void);

/* A pointer to one of the above functions */
extern d4memref (*input_function) (void);

/* the accesstype returned by next_trace_item when the trace is exhausted */
#define D4TRACE_END	D4NUMACCESSTYPES

/* -informat arg */
extern int informat;

/* check that a recognized input format has been specified */
extern void verify_trace_format (void);

/* list valid choices for -informat */
extern void help_trace_format (int indent);
