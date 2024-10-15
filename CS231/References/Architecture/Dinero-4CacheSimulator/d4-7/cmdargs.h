/*
 * Declarations for argument handling for Dinero IV's command interface.
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
 * $Header: /home/edler/dinero/d4/RCS/cmdargs.h,v 1.5 1997/12/08 19:35:24 edler Exp $
 */


/*
 * This structure describes a command line arg for Dinero IV.
 * Some args require a cache attribute prefix, -ln-idu, where
 * 1 <= n <= MAX_LEV and idu is "i", "d", or "", coresponding to an instruction,
 * data, or unified cache; this is all handled by choice of match function.
 *
 * The arglist structure also supports the help message,
 * summary info, and option customization.
 */ 

#ifndef MAX_LEV
#define MAX_LEV	5		/* allow -ln prefix no larger than this */
#endif

struct arglist {
	const char *optstring;	  /* string to match, without -ln-idu if applicable */
	int pad;		  /* how many extra chars will help print? */
	void *var;		  /* scalar variable or array to modify */
	char *defstr;		  /* default value, as a string */
	const char *customstring; /* arg to use for custom version */
	const char *helpstring;	  /* string for help line */

				  /* function to recognize arg on command line */
	int (*match)(const char *opt, const struct arglist *);
				  /* valf is function to set value */
	void (*valf)(const char *opt, const char *arg, const struct arglist *);
				  /* customf produces definitions for custom version */
	void (*customf)(const struct arglist *, FILE *);
				  /* sumf prints summary line */
	void (*sumf)(const struct arglist *, FILE *);
				  /* help prints line for -help */
	void (*help)(const struct arglist *);
};

/* Some globals, defined in cmdargs.c */
extern struct arglist args[];	/* defined in cmdargs.c */
extern int nargs;		/* num entries in args[] */
extern int maxlevel;		/* largest cache level specified */
extern int optstringmax;	/* longest option string */

extern char *customname;	/* for -custom, name of executable */
extern double skipcount;	/* for -skipcount */
extern double flushcount;	/* for -flushcount */
extern double maxcount;		/* for -maxcount */
extern double stat_interval;	/* for -stat-interval */
extern long on_trigger;		/* for -on-trigger */
extern long off_trigger;	/* for -off-trigger */
extern int stat_idcombine;	/* for -stat-idcombine */

/*
 * The size of each cache is given by
 *	level_size[idu][level]
 * where idu=0 for ucache, 1 for icache, 2 for dcache,
 * and 0=closest to processor, MAX_LEV-1 = closest to memory)
 */
extern unsigned int level_size[3][MAX_LEV];


/*
 * Helper for match and value functions recognizing -ln-idu prefix
 */
extern char *level_idu (const char *opt, int *level, int *idu);

/*
 * Helpers for options with scaled arguments
 */
extern unsigned int argscale_uint (const char *arg, unsigned int *var);
extern double argscale_uintd (const char *arg, double *var);

/*
 * Match functions -- recognize the arg on the command line
 * Return the number of argv elements to be consumed.
 */
extern int match_0arg (const char *, const struct arglist *);
extern int pmatch_0arg (const char *, const struct arglist *);
extern int match_1arg (const char *, const struct arglist *);
extern int pmatch_1arg (const char *, const struct arglist *); /* with -ln-idu prefix */
#if D4CUSTOM
extern int match_bogus (const char *, const struct arglist *);
#endif

/*
 * value functions -- actually consume the option and argument(s).
 */
extern void val_help (const char *opt, const char *arg, const struct arglist *);
extern void val_helpcr (const char *opt, const char *arg, const struct arglist *);
extern void val_helpw (const char *opt, const char *arg, const struct arglist *);
#if !D4CUSTOM
extern void val_helpd3 (const char *opt, const char *arg, const struct arglist *);
#endif
extern void val_0arg (const char *opt, const char *arg, const struct arglist *);
extern void pval_0arg (const char *opt, const char *arg, const struct arglist *);
extern void val_uint (const char *opt, const char *arg, const struct arglist *);
extern void pval_uint (const char *opt, const char *arg, const struct arglist *);
extern void val_scale_uint (const char *opt, const char *arg, const struct arglist *);
extern void val_scale_uintd (const char *opt, const char *arg, const struct arglist *);
extern void pval_scale_uint (const char *opt, const char *arg, const struct arglist *);
extern void val_scale_pow2 (const char *opt, const char *arg, const struct arglist *);
extern void pval_scale_pow2 (const char *opt, const char *arg, const struct arglist *);
extern void val_char (const char *opt, const char *arg, const struct arglist *);
extern void pval_char (const char *opt, const char *arg, const struct arglist *);
extern void val_string (const char *opt, const char *arg, const struct arglist *);
extern void val_addr (const char *opt, const char *arg, const struct arglist *);

/*
 * custom functions -- help set up custom version of dineroIV.
 */
#if !D4CUSTOM
extern void custom_custom (const struct arglist *, FILE *);
extern void pcustom_0arg (const struct arglist *, FILE *);
extern void pcustom_uint (const struct arglist *, FILE *);
extern void pcustom_char (const struct arglist *, FILE *);
#endif

/*
 * summary functions -- produce summary of parameter setting
 */
extern void summary_0arg (const struct arglist *, FILE *);
extern void psummary_0arg (const struct arglist *, FILE *);
extern void summary_uint (const struct arglist *, FILE *);
extern void summary_uintd (const struct arglist *, FILE *);
extern void psummary_uint (const struct arglist *, FILE *);
extern void psummary_luint (const struct arglist *, FILE *);
extern void summary_char (const struct arglist *, FILE *);
extern void psummary_char (const struct arglist *, FILE *);
extern void summary_addr (const struct arglist *, FILE *);

/*
 * help functions -- support the -help arg
 */
extern void help_0arg (const struct arglist *);
extern void phelp_0arg (const struct arglist *);
extern void help_uint (const struct arglist *);
extern void help_scale_uintd (const struct arglist *);
extern void phelp_uint (const struct arglist *);
extern void phelp_scale_uint (const struct arglist *);
extern void phelp_scale_pow2 (const struct arglist *);
extern void help_char (const struct arglist *);
extern void phelp_char (const struct arglist *);
extern void help_string (const struct arglist *);
extern void help_addr (const struct arglist *);

/*
 * Set argument-related things up after seeing all args
 */
extern void verify_options (void);
extern void initialize_caches (d4cache **icachep, d4cache **dcachep);
extern void init_1cache (d4cache *, int, int);
