/*
 * Command line argument stuff for Dinero IV.
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
 * $Header: /home/edler/dinero/d4/RCS/cmdargs.c,v 1.11 1997/12/12 20:36:39 edler Exp $
 */

#include <stddef.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include "d4.h"
#include "cmdd4.h"
#include "cmdargs.h"
#include "tracein.h"


/*
 * The idea is to confine as much argument knowledge as possible to this file.
 * Generic argument handling functions are in cmdmain.c
 */

/*
 * Define the variables and arrays to receive command line argument values.
 * Those coresponding to arguments with -ln-idu prefixes are actually
 * 2-d arrays; for the 1st index 0=unified, 1=instruction, and 2=data.
 * The 2nd index is the level - 1.
 *
 * The basic strategy is to process all the command line args, fill in these
 * variables and arrays, check them for consistency, and then
 * allocate and initialize all necessary cache structures for simulation.
 *
 * For those options subject to customization, the customized version
 * of the array is defined elsewhere.
 */
#if D4CUSTOM
#define D4_EXT extern
#else
#define D4_EXT
#endif
D4_EXT int maxlevel;	/* the highest level actually used */
D4_EXT unsigned int level_blocksize[3][MAX_LEV];
D4_EXT unsigned int level_subblocksize[3][MAX_LEV];
D4_EXT unsigned int level_size[3][MAX_LEV];
D4_EXT unsigned int level_assoc[3][MAX_LEV];
D4_EXT int level_doccc[3][MAX_LEV];
D4_EXT int level_replacement[3][MAX_LEV];
D4_EXT int level_fetch[3][MAX_LEV];
D4_EXT int level_walloc[3][MAX_LEV];
D4_EXT int level_wback[3][MAX_LEV];
D4_EXT int level_prefetch_abortpercent[3][MAX_LEV];
int level_prefetch_distance[3][MAX_LEV];

/*
 * command line defaults.
 * Make sure the DEFVAL and DEFSTR versions match
 * We don't really have to use fancy macro stuff for this do we?
 */
#define DEFVAL_assoc 1
#define  DEFSTR_assoc "1"
#define DEFVAL_repl 'l'
#define  DEFSTR_repl "l"
#define DEFVAL_fetch 'd'
#define  DEFSTR_fetch "d"
#define DEFVAL_walloc 'a'
#define  DEFSTR_walloc "a"
#define DEFVAL_wback 'a'
#define  DEFSTR_wback "a"
#define DEFVAL_informat 'D'
#define  DEFSTR_informat "D"

double skipcount;
double flushcount;
double maxcount;
double stat_interval;
int informat = DEFVAL_informat;
long on_trigger;
long off_trigger;
int stat_idcombine;


/*
 * Other declarations local to this file
 */
extern void help_informat (const struct arglist *);
extern void phelp_replacement (const struct arglist *);
extern void phelp_fetch (const struct arglist *);
extern void phelp_walloc (const struct arglist *);
extern void phelp_wback (const struct arglist *);
extern void unspec (int, int, char *, void *, char *);


#if D4CUSTOM
#define CUST_MATCH(x)	match_bogus
#define CUST_X(x)	NULL
#else
#define CUST_MATCH(x)	x
#define CUST_X(x)	x
#endif

/* Initialize argument table to specify acceptable arguments */
struct arglist args[] = {
	{ "-help", 0, NULL, NULL,
	  NULL,
	  "Print this help message",
	  match_0arg, val_help, NULL,
	  NULL, help_0arg },
	{ "-copyright", 0, NULL, NULL,
	  NULL,
	  "Give details on copyright and lack of warranty",
	  match_0arg, val_helpcr, NULL,
	  NULL, help_0arg },
	{ "-contact", 0, NULL, NULL,
	  NULL,
	  "Where to get the latest version or contact the authors",
	  match_0arg, val_helpw, NULL,
	  NULL, help_0arg },
#if !D4CUSTOM
	{ "-dineroIII", 0, NULL, NULL,
	  NULL,
	  "Explain replacements for Dinero III options",
	  match_0arg, val_helpd3, NULL,
	  NULL, help_0arg },
	{ "-custom", 2, &customname, NULL,
	  NULL,
	  "Generate and run custom simulator named F",
	  match_1arg, val_string, custom_custom,
	  NULL, help_string },
#endif
	{ "size", 7, &level_size[0][0], NULL,
	  "level_size",
	  "Size",
	  CUST_MATCH(pmatch_1arg), pval_scale_pow2, CUST_X(pcustom_uint),
	  psummary_luint, CUST_X(phelp_scale_pow2) },
	{ "bsize", 7, &level_blocksize[0][0], NULL,
	  "level_blocksize",
	  "Block size",
	  CUST_MATCH(pmatch_1arg), pval_scale_pow2, CUST_X(pcustom_uint),
	  psummary_luint, CUST_X(phelp_scale_pow2) },
	{ "sbsize", 7, &level_subblocksize[0][0], "same as block size",
	  "level_subblocksize",
	  "Sub-block size",
	  CUST_MATCH(pmatch_1arg), pval_scale_pow2, CUST_X(pcustom_uint),
	  psummary_luint, CUST_X(phelp_scale_pow2) },
	{ "assoc", 7, &level_assoc[0][0], DEFSTR_assoc,
	  "level_assoc",
	  "Associativity",
	  CUST_MATCH(pmatch_1arg), pval_uint, CUST_X(pcustom_uint),
	  psummary_uint, CUST_X(phelp_uint) },
	{ "repl", 7, &level_replacement[0][0], DEFSTR_repl,
	  "level_replacement",
	  "Replacement policy",
	  CUST_MATCH(pmatch_1arg), pval_char, CUST_X(pcustom_char),
	  psummary_char, CUST_X(phelp_replacement) },
	{ "fetch", 7, &level_fetch[0][0], DEFSTR_fetch,
	  "level_fetch",
	  "Fetch policy",
	  CUST_MATCH(pmatch_1arg), pval_char, CUST_X(pcustom_char),
	  psummary_char, CUST_X(phelp_fetch) },
	{ "pfdist", 7, &level_prefetch_distance[0][0], "1",
	  NULL,
	  "Prefetch distance (in sub-blocks)",
	  pmatch_1arg, pval_uint, NULL,
	  psummary_uint, CUST_X(phelp_uint) },
	{ "pfabort", 7, &level_prefetch_abortpercent[0][0], "0",
	  "level_prefetch_abortpercent",
	  "Prefetch abort percentage (0-100)",
	  CUST_MATCH(pmatch_1arg), pval_uint, CUST_X(pcustom_uint),
	  psummary_uint, CUST_X(phelp_uint) },
	{ "walloc", 7, &level_walloc[0][0], DEFSTR_walloc,
	  "level_walloc",
	  "Write allocate policy",
	  CUST_MATCH(pmatch_1arg), pval_char, CUST_X(pcustom_char),
	  psummary_char, CUST_X(phelp_walloc) },
	{ "wback", 7, &level_wback[0][0], DEFSTR_wback,
	  "level_wback",
	  "Write back policy",
	  CUST_MATCH(pmatch_1arg), pval_char, CUST_X(pcustom_char),
	  psummary_char, CUST_X(phelp_wback) },
	{ "ccc", 5, &level_doccc[0][0], NULL,
	  "level_doccc",
	  "Compulsory/Capacity/Conflict miss statistics",
	  CUST_MATCH(pmatch_0arg), pval_0arg, CUST_X(pcustom_0arg),
	  psummary_0arg, CUST_X(phelp_0arg) },
	{ "-skipcount", 2, &skipcount, NULL,
	  NULL,
	  "Skip initial U references",
	  match_1arg, val_scale_uintd, NULL,
	  summary_uintd, help_scale_uintd },
	{ "-flushcount", 2, &flushcount, NULL,
	  NULL,
	  "Flush cache every U references",
	  match_1arg, val_scale_uintd, NULL,
	  summary_uintd, help_scale_uintd },
	{ "-maxcount", 2, &maxcount, NULL,
	  NULL,
	  "Stop simulation after U references",
	  match_1arg, val_scale_uintd, NULL,
	  summary_uintd, help_scale_uintd },
	{ "-stat-interval", 2, &stat_interval, NULL,
	  NULL,
	  "Show statistics after every U references",
	  match_1arg, val_scale_uintd, NULL,
	  summary_uintd, help_scale_uintd },
	{ "-informat", 2, &informat, DEFSTR_informat,
	  NULL,
	  "Input trace format",
	  match_1arg, val_char, NULL,
	  summary_char, help_informat },
	{ "-on-trigger", 2, &on_trigger, NULL,
	  NULL,
	  "Trigger address to start simulation",
	  match_1arg, val_addr, NULL,
	  summary_addr, help_addr },
	{ "-off-trigger", 2, &off_trigger, NULL,
	  NULL,
	  "Trigger address to stop simulation",
	  match_1arg, val_addr, NULL,
	  summary_addr, help_addr },
	{ "-stat-idcombine", 2, &stat_idcombine, NULL,
	  NULL,
	  "Combine I&D cache stats",
	  match_0arg, val_0arg, NULL,
	  summary_0arg, help_0arg },
	{ NULL, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }
};
int nargs = sizeof(args) / sizeof(args[0]);


/*
 * Special help routine for -informat.
 * List the choices on subsequent lines.
 */
void
help_informat (const struct arglist *adesc)
{
	help_char (adesc);
	help_trace_format (optstringmax);	/* look for this in tracein.c */
}


/*
 * Special help routine for -lN-Treplacement.
 * List the choices on subsequent lines.
 */
void
phelp_replacement (const struct arglist *adesc)
{
	phelp_char (adesc);
	printf ("\n %*s (l=LRU, f=FIFO, r=random)",
		optstringmax, " ");
}


/*
 * Special help routine for -lN-Tfetch.
 * List the choices on subsequent lines.
 */
void
phelp_fetch (const struct arglist *adesc)
{
	phelp_char (adesc);
	printf ("\n %*s (d=demand, a=always, m=miss, t=tagged,\n"
		" %*s  l=load forward, s=subblock)",
		optstringmax, " ", optstringmax, " ");
}


/*
 * Special help routine for -lN-Twalloc.
 * List the choices on subsequent lines.
 */
void
phelp_walloc (const struct arglist *adesc)
{
	phelp_char (adesc);
	printf ("\n %*s (a=always, n=never, f=nofetch)",
		optstringmax, " ");
}


/*
 * Special help routine for -lN-Twback.
 * List the choices on subsequent lines.
 */
void
phelp_wback (const struct arglist *adesc)
{
	phelp_char (adesc);
	printf ("\n %*s (a=always, n=never, f=nofetch)",
		optstringmax, " ");
}


/*
 * Complain about an unspecified option
 */
void
unspec (int lev, int idu, char *name, void *var, char *suggest)
{
	int iduchar = idu==0?'u':(idu==1?'i':'d');
	struct arglist *argl;

	for (argl = args;  argl->var != var;  argl++)
		if (argl->optstring == NULL)
			die ("internal problem with arglist table\n");
	
	fprintf (stderr, "level %d %ccache %s must be specified, "
		 "e.g., -l%d-%c%s %s\n",
		 lev+1, iduchar, name, lev+1, iduchar, argl->optstring, suggest);
}


/*
 * Called after all the options and args are consumed.
 * Check them for consistency and reasonableness.
 * Die with an error message if there are serious problems.
 */
void
verify_options()
{
	int lev, idu;

	/*
	 * Allow some default values
	 *	subblocksize (default to blocksize)
	 *	prefetch distance (default to 1)
	 *	other defaults defined as DEFVAL_xxx
	 */
	for (lev = 0;  lev < maxlevel;  lev++) {
		for (idu = 0;  idu < 3;  idu++) {
			if (level_blocksize[idu][lev]!=0 && level_subblocksize[idu][lev]==0)
				level_subblocksize[idu][lev] = level_blocksize[idu][lev];
			if (level_size[idu][lev]!=0 && level_assoc[idu][lev]==0)
				level_assoc[idu][lev] = DEFVAL_assoc;
			if (level_size[idu][lev]!=0 && level_replacement[idu][lev]==0)
				level_replacement[idu][lev] = DEFVAL_repl;
			if (level_size[idu][lev]!=0 && level_fetch[idu][lev]==0)
				level_fetch[idu][lev] = DEFVAL_fetch;
			if (level_size[idu][lev]!=0 &&
			    level_fetch[idu][lev]!='d' && level_prefetch_distance[idu][lev]==0)
				level_prefetch_distance[idu][lev] = 1;
			if (idu!=1 && level_size[idu][lev]!=0 && level_walloc[idu][lev]==0)
				level_walloc[idu][lev] = DEFVAL_walloc;
			if (idu!=1 && level_size[idu][lev]!=0 && level_wback[idu][lev]==0)
				level_wback[idu][lev] = DEFVAL_wback;
		}
	}

	/*
	 * check for missing required parameters
	 */
	if (maxlevel <= 0)
		shorthelp ("cache size and block size must be specified,\n"
			   "e.g.: -l1-isize 16k -l1-dsize 8192 "
				 "-l1-ibsize 32 -l1-dbsize 16\n");
	for (lev = 0;  lev < maxlevel;  lev++) {
		int nerr = 0, nidu = 0;
		for (idu = 0;  idu < 3;  idu++) {
			int nparams = (level_blocksize[idu][lev]!=0) +
				      (level_subblocksize[idu][lev]!=0) +
				      (level_size[idu][lev]!=0) +
				      (level_assoc[idu][lev]!=0) +
				      (level_replacement[idu][lev]!=0) +
				      (level_fetch[idu][lev]!=0) +
				      (level_walloc[idu][lev]!=0) +	/* only for u or d */
				      (level_wback[idu][lev]!=0);	/* only for u or d */
			int active = nparams != 0 || level_doccc[idu][lev] != 0;
			nidu += active;
			if (active && nparams != (6+2*(idu!=1))) {
				if (level_blocksize[idu][lev]==0)
					unspec (lev, idu, "block size", &level_blocksize[0][0], "16");
				if (level_size[idu][lev]==0)
					unspec (lev, idu, "size", &level_size[0][0], "16k");
				nerr++;
			}
		}
		if (nidu == 0)
			shorthelp ("no level %d cache specified\n", lev+1);
		else if (nerr != 0)
			shorthelp ("level %d cache parameters incomplete\n", lev+1);
	}

	verify_trace_format();	/* look for this in tracein.c */

	/* allowable replacement policies */
	for (lev = 0;  lev < maxlevel;  lev++) {
		for (idu = 0;  idu < 3;  idu++) {
			if (level_replacement[idu][lev]!=0 &&
			    level_replacement[idu][lev]!='l' &&	/* LRU */
			    level_replacement[idu][lev]!='f' &&	/* FIFO */
			    level_replacement[idu][lev]!='r')	/* random */
				shorthelp ("level %d %ccache replacement policy unrecognized\n",
					   lev+1, idu==0?'u':(idu==1?'i':'d'));
		}
	}

	/* allowable fetch policies and prefetch parameters */
	for (lev = 0;  lev < maxlevel;  lev++) {
		for (idu = 0;  idu < 3;  idu++) {
			if (level_fetch[idu][lev]!=0 &&
			    level_fetch[idu][lev]!='d' &&	/* demand fetch */
			    level_fetch[idu][lev]!='a' &&	/* always prefetch */
			    level_fetch[idu][lev]!='m' &&	/* miss prefetch */
			    level_fetch[idu][lev]!='t' &&	/* tagged prefetch */
			    level_fetch[idu][lev]!='l' &&	/* load forward prefetch */
			    level_fetch[idu][lev]!='s')		/* subblock prefetch */
				shorthelp ("level %d %ccache fetch policy unrecognized\n",
					   lev+1, idu==0?'u':(idu==1?'i':'d'));
			if ((level_fetch[idu][lev]=='l' || level_fetch[idu][lev]=='s') &&
			    level_prefetch_distance[idu][lev] >
			    level_blocksize[idu][lev]/(level_subblocksize[idu][lev]
			    ?level_subblocksize[idu][lev]:level_blocksize[idu][lev]))
				shorthelp ("level %d %ccache prefetch distance > block size\n",
					   lev+1, idu==0?'u':(idu==1?'i':'d'));
			if (level_fetch[idu][lev]=='d' &&
			    level_prefetch_abortpercent[idu][lev]!=0)
				shorthelp ("level %d %ccache abort %% not allowed "
					   "with demand fetch policy\n", lev+1,
					   idu==0?'u':(idu==1?'i':'d'));
			if (level_prefetch_abortpercent[idu][lev] < 0 ||
			    level_prefetch_abortpercent[idu][lev] > 100)
				shorthelp ("level %d %ccache abort %% out of range\n",
					   lev+1, idu==0?'u':(idu==1?'i':'d'));
		}
	}

	/* allowable walloc policies */
	for (lev = 0;  lev < maxlevel;  lev++) {
		if (level_walloc[1][lev]!=0)
			shorthelp ("level %d icache cannot have write allocate policy\n", lev+1);
		for (idu = 0;  idu < 3;  idu++) {
			if (level_walloc[idu][lev]!=0 &&
			    level_walloc[idu][lev]!='a' &&	/* always write allocate */
			    level_walloc[idu][lev]!='n' &&	/* never write allocate */
			    level_walloc[idu][lev]!='f')	/* walloc only w/o fetch */
				shorthelp ("level %d %ccache write allocate policy unrecognized\n",
					   lev+1, idu==0?'u':'d');
		}
	}

	/* allowable wback policies */
	for (lev = 0;  lev < maxlevel;  lev++) {
		if (level_wback[1][lev]!=0)
			shorthelp ("level %d icache cannot have write back policy\n", lev+1);
		for (idu = 0;  idu < 3;  idu++) {
			if (level_wback[idu][lev]!=0 &&
			    level_wback[idu][lev]!='a' &&	/* always write back */
			    level_wback[idu][lev]!='n' &&	/* never write back (i.e., write through) */
			    level_wback[idu][lev]!='f')		/* wback only w/o fetch */
				shorthelp ("level %d %ccache write back policy unrecognized\n",
					   lev+1, idu==0?'u':'d');
		}
	}

	/* the sub-block size is limited by size specified in memory reference */
	for (lev = 0;  lev < maxlevel;  lev++) {
		for (idu = 0;  idu < 3;  idu++) {
			d4memref x;
			/* put a 1 in MSB position; x.size is unsigned */
			x.size = ~0;
			x.size = ~(x.size >> 1);
			if (level_subblocksize[idu][lev] > x.size)
				shorthelp ("level %d %ccache sub-block size must be <= %u\n",
					   lev+1, idu==0?'u':(idu==1?'i':'d'), x.size);
		}
	}

	/* block size/sub-block size */
	for (lev = 0;  lev < maxlevel;  lev++) {
		for (idu = 0;  idu < 3;  idu++) {
			d4stacknode *xp;
			if (level_blocksize[idu][lev]!= 0 &&
			    level_subblocksize[idu][lev] > level_blocksize[idu][lev])
				shorthelp ("level %d %ccache has sub-blocksize > blocksize\n",
					   lev+1, idu==0?'u':(idu==1?'i':'d'));
			if (level_subblocksize[idu][lev] != 0 &&
			    level_blocksize[idu][lev] / level_subblocksize[idu][lev] > sizeof(xp->valid)*CHAR_BIT)
				shorthelp ("level %d %ccache must have no more than %u sub-blocks per block\n",
					   lev+1, idu==0?'u':(idu==1?'i':'d'), sizeof(xp->valid)*CHAR_BIT);
			if (level_subblocksize[idu][lev] != 0 && level_doccc[idu][lev] != 0 &&
			    D4_BITMAP_RSIZE < level_blocksize[idu][lev] / level_subblocksize[idu][lev])
				shorthelp ("level %d %ccache must have no more than %u sub-blocks per block for CCC\n",
					   lev+1, idu==0?'u':(idu==1?'i':'d'), D4_BITMAP_RSIZE);
		}
	}

	/* block and sub-block sizes must match for -stat-idcombine */
	if (stat_idcombine) {
		for (lev = 0;  lev < maxlevel;  lev++) {
			if (level_blocksize[1][lev] != level_blocksize[2][lev])
				shorthelp ("level %d i & d cache block sizes must match for -stat-idcombine\n", lev+1);
			if (level_subblocksize[1][lev] != level_subblocksize[2][lev])
				shorthelp ("level %d i & d cache sub-block sizes must match for -stat-idcombine\n", lev+1);
		}
	}

	/*
	 * Check for u and (i or d) at each level
	 */
	for (lev = 0;  lev < maxlevel;  lev++) {
		if (0 != (level_blocksize[0][lev]    |
			  level_subblocksize[0][lev] |
			  level_size[0][lev]         |
			  level_assoc[0][lev]        |
			  level_replacement[0][lev]  |
			  level_fetch[0][lev]        | 
			  level_walloc[0][lev]       |
			  level_wback[0][lev]        |
			  level_doccc[0][lev]         ) &&
		    0 != (level_blocksize[1][lev]    | level_blocksize[2][lev]    |
			  level_subblocksize[1][lev] | level_subblocksize[2][lev] |
			  level_size[1][lev]         | level_size[2][lev]         |
			  level_assoc[1][lev]        | level_assoc[2][lev]        |
			  level_replacement[1][lev]  | level_replacement[2][lev]  |
			  level_fetch[1][lev]        | level_fetch[2][lev]        |
			  level_walloc[1][lev]       | level_walloc[2][lev]       |
			  level_wback[1][lev]        | level_wback[2][lev]        |
			  level_doccc[1][lev]        | level_doccc[2][lev]         ))
			shorthelp ("level %d has i or d together with u cache parameters\n",
				   lev+1);
	}

	/* check consistency of sizes */
	for (lev = 0;  lev < maxlevel;  lev++) {
		for (idu = 0;  idu < 3;  idu++) {
			if (level_blocksize[idu][lev] != 0 &&
			    level_blocksize[idu][lev] * level_assoc[idu][lev] > level_size[idu][lev])
				shorthelp ("level %d %ccache size < blocksize * associativity\n",
					   lev+1, idu==0?'u':(idu==1?'i':'d'));
		}
	}

	/* check for no u->id split */
	for (lev = 1;  lev < maxlevel;  lev++) {
		if (level_blocksize[0][lev-1] != 0 &&
		    level_blocksize[0][lev] == 0)
			shorthelp ("level %d cache is unified, level %d is not\n", lev, lev+1);
	}
}


/*
 * Initialize one cache based on args
 * Die with an error message if there are serious problems.
 */
void
init_1cache (d4cache *c, int lev, int idu)
{
	c->name = malloc (30);
	if (c->name == NULL)
		die ("malloc failure initializing l%d%ccache\n", lev+1, idu==0?'u':(idu==1?'i':'d'));
	sprintf (c->name, "l%d-%ccache", lev+1, idu==0?'u':(idu==1?'i':'d'));

	c->flags |= level_doccc[idu][lev] ? D4F_CCC : 0;
	if (idu == 1)
		c->flags |= D4F_RO;
	c->lg2blocksize = clog2 (level_blocksize[idu][lev]);
	c->lg2subblocksize = clog2 (level_subblocksize[idu][lev]);
	c->lg2size = clog2 (level_size[idu][lev]);
	c->assoc = level_assoc[idu][lev];

	switch (level_replacement[idu][lev]) {
	default:  die ("replacement policy '%c' initialization botch\n", level_replacement[idu][lev]);
	case 'l': c->replacementf = d4rep_lru; c->name_replacement = "LRU"; break;
	case 'f': c->replacementf = d4rep_fifo; c->name_replacement = "FIFO"; break;
	case 'r': c->replacementf = d4rep_random; c->name_replacement = "random"; break;
	}

	switch (level_fetch[idu][lev]) {
	default:  die ("fetch policy '%c' initialization botch\n", level_fetch[idu][lev]);
	case 'd': c->prefetchf = d4prefetch_none; c->name_prefetch = "demand only"; break;
	case 'a': c->prefetchf = d4prefetch_always; c->name_prefetch = "always"; break;
	case 'm': c->prefetchf = d4prefetch_miss; c->name_prefetch = "miss"; break;
	case 't': c->prefetchf = d4prefetch_tagged; c->name_prefetch = "tagged"; break;
	case 'l': c->prefetchf = d4prefetch_loadforw; c->name_prefetch = "load forward"; break;
	case 's': c->prefetchf = d4prefetch_subblock; c->name_prefetch = "subblock"; break;
	}

	switch (level_walloc[idu][lev]) {
	default:  die ("write allocate policy '%c' initialization botch\n", level_walloc[idu][lev]);
	case 0:   c->wallocf = d4walloc_impossible; c->name_walloc = "impossible"; break;
	case 'a': c->wallocf = d4walloc_always; c->name_walloc = "always"; break;
	case 'n': c->wallocf = d4walloc_never; c->name_walloc = "never"; break;
	case 'f': c->wallocf = d4walloc_nofetch; c->name_walloc = "nofetch"; break;
	}

	switch (level_wback[idu][lev]) {
	default:  die ("write back policy '%c' initialization botch\n", level_wback[idu][lev]);
	case 0:   c->wbackf = d4wback_impossible; c->name_wback = "impossible"; break;
	case 'a': c->wbackf = d4wback_always; c->name_wback = "always"; break;
	case 'n': c->wbackf = d4wback_never; c->name_wback = "never"; break;
	case 'f': c->wbackf = d4wback_nofetch; c->name_wback = "nofetch"; break;
	}

	c->prefetch_distance = level_prefetch_distance[idu][lev] * level_subblocksize[idu][lev];
	c->prefetch_abortpercent = level_prefetch_abortpercent[idu][lev];
}
