/*
 * Main header file for Dinero IV.
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
 * $Header: /home/edler/dinero/d4/RCS/d4.h,v 1.10 1998/02/06 21:04:14 edler Exp $
 */


/*
 * Miscellaneous definitions
 */

#include "config.h"
#define D4VERSION	"7"

#ifndef D4CUSTOM
#define D4CUSTOM 0
#endif

	/* Type of a simulated address */
#ifndef D4ADDR
#if SIZEOF_INT >= SIZEOF_VOIDP
#define D4ADDR unsigned int
#else
#define D4ADDR unsigned long
#endif
#endif
typedef D4ADDR d4addr;




	/*
	 * Full specification of a memory reference.
	 * 0 size is allowd for D4XCOPYB and D4XINVAL only,
	 * and indicated the operation applies to the whole cache.
	 */
typedef struct {
	d4addr		address;
	char		accesstype;
	unsigned short	size;		/* of memory referenced, in bytes */
} d4memref;




	/* Node for a stack of pending memrefs per cache */
typedef struct d4_pendstack {
	d4memref m;
	struct d4_pendstack *next;
} d4pendstack;




	/*
	 * The access types
	 * D4PREFETCH is or'ed for prefetch types
	 * D4_MULTIBLOCK is or'ed for split references
	 */
#define	D4XREAD		0
#define D4XWRITE	1
#define D4XINSTRN	2
#define D4XMISC		3
#define D4XCOPYB	4	/* copy back dirty line(s) - no invalidate */
#define D4XINVAL	5	/* invalidate line(s) - no copyback */
#define D4NUMACCESSTYPES 8	/* how many basic access types + padding */
#define D4PREFETCH	D4NUMACCESSTYPES
#define D4_MULTIBLOCK	(2*D4PREFETCH)
#if D4PREFETCH==0 || (D4PREFETCH&(D4PREFETCH-1)) != 0
#error "D4PREFETCH must be a power of 2"
#endif

#define D4BASIC_ATYPE(x)	((x)&(D4PREFETCH-1)) /* just the basic part */




	/*
	 * Stack node in simulated cache,
	 * Each stack is doubly linked, using up and down fields.
	 * The list is circular, so top->up is the bottom.
	 * Each stack always contains the full setsize nodes,
	 * + 1 for replacement.  The valid ones are always first.
	 * For caches with large associativity (>= D4HASH_THRESH),
	 * the valid nodes are also on a hash bucket chain.
	 */
typedef struct d4_stacknode_struct {
	d4addr		blockaddr;	    /* byte address of block */
	unsigned int	valid;		    /* bit for each subblock */
	unsigned int	referenced;	    /* bit for each subblock */
	unsigned int	dirty;		    /* bit for each subblock */
	int		onstack;	    /* which stack is node on? */
	struct d4_cache_struct *cachep;	    /* which cache is this a part of */
	struct d4_stacknode_struct *down;   /* ptr to less recently used node */
	struct d4_stacknode_struct *up;     /* ptr to more recently used node */
	struct d4_stacknode_struct *bucket; /* singly-linked for hash collisions */

#ifdef D4STACK_USERHOOK
	D4STACK_USERHOOK	/* allow additional stuff for user policies */
#endif
} d4stacknode;




	/*
	 * Head of a stack,
	 * top points to the most recently used node in the stack.
	 */
typedef struct d4_stackhead_struct {
	d4stacknode *top;	/* the "beginning" of the stack */
	int n;			/* size of stack (== 1 + assoc) */
} d4stackhead;




	/*
	 * Long stacks are indexed with a hash table
	 * One hash table takes care of everything.
	 * The hash key is based on the block address, stack number,
	 * and cacheid.  Collisions are resolved by chaining.
	 */
struct d4_stackhash_struct {
	int size;		/* size of the hash table */
	d4stacknode **table;	/* the table itself, malloced */
};

#define D4HASH_THRESH	8	/* stacks bigger than this size are hashed */
#define D4HASH(ba,sn,cid)	(((unsigned long)(ba)+(sn)+(cid)) %				\
				 ((D4_HASHSIZE>0) ? D4_HASHSIZE : d4stackhash.size))
#ifndef D4_HASHSIZE
#define D4_HASHSIZE 0	/* default is automatic */
#endif




	/*
	 * We support infinite caches for classification of misses into
	 * compulsory/capacity/conflict categories.
	 * An infinite cache is made up of address ranges, where each
	 * range has a bitmap showing which subblocks have been cached.
	 */
typedef struct {
	d4addr	addr;		/* start address of range */
	char	*bitmap;
} d4range;

#define D4_BITMAP_RSIZE	(8*1024*1024)	/* size of each range, in bits */
#if D4_BITMAP_RSIZE<=0 || (D4_BITMAP_RSIZE&(D4_BITMAP_RSIZE-1)) != 0
#error "D4_BITMAP_RSIZE must be a power of 2"
#endif




	/*
	 * full specification of a cache
	 */
typedef struct d4_cache_struct {
	char *name;		/* mostly for printing */
	int cacheid;		/* unique for each cache */
	int flags;
	d4stackhead *stack;	/* the priority stacks for this cache */
	d4pendstack *pending;	/* stack for prefetch etc. */
	struct d4_cache_struct *link; /* linked list of all caches */

	/*
	 * Cache parameters
	 */
	int lg2blocksize;	/* set by the user */
	int lg2subblocksize;	/* set by the user */
	int lg2size;		/* set by the user */
	int assoc;		/* set by the user */

	int numsets;		/* this one is derived, not set by the user */

	/*
	 * Interconnection of caches
	 * Caches must form a tree, with the root
	 * being memory and the leaves being closest
	 * to the processors.
	 */
	struct d4_cache_struct *downstream;
	void (*ref)(struct d4_cache_struct *, d4memref);	/* d4ref or custom version */

	/*
	 * Cache policy functions and data:
	 *	replacement, prefetch, write-alloc, write-back
	 * These must be set by the user
	 * (normally, each policy should have an initialization routine)
	 */
				/* adjust priority stack */
	d4stacknode	*(*replacementf) (struct d4_cache_struct *, int stacknum,
					  d4memref, d4stacknode *ptr);
				/* indicate a prefetch with prefetch_pending */
	d4pendstack	*(*prefetchf) (struct d4_cache_struct *, d4memref,
				       int miss, d4stacknode *ptr);
				/* walloc returns true for write-allocate */
	int		(*wallocf) (struct d4_cache_struct *, d4memref);
				/* wback returns true for write-back */
	int		(*wbackf) (struct d4_cache_struct *, d4memref, int,
				   d4stacknode *ptr, int);

	int		prefetch_distance;	/* specific to built-in prefetch policies */
	int		prefetch_abortpercent;
	char		*name_replacement;	/* for printing */
	char		*name_prefetch;
	char		*name_walloc;
	char		*name_wback;

#ifdef D4CACHE_USERHOOK
	D4CACHE_USERHOOK	/* allow additional stuff for user policies */
#endif

	/*
	 * Infinite cache for compulsory/capacity/conflict classification
	 */
	int		nranges;
	int		maxranges;
	d4range		*ranges;
	

	/*
	 * Cache statistics
	 * Doubles are used as big integers
	 * Index is accesstype + 0 or
	 *          accesstype + D4PREFETCH for prefetch
	 */
	double fetch	      [2 * D4NUMACCESSTYPES];
	double miss	      [2 * D4NUMACCESSTYPES];
	double blockmiss      [2 * D4NUMACCESSTYPES];
	double comp_miss      [2 * D4NUMACCESSTYPES];	/* compulsory misses */
	double comp_blockmiss [2 * D4NUMACCESSTYPES];
	double cap_miss	      [2 * D4NUMACCESSTYPES];	/* capacity misses */
	double cap_blockmiss  [2 * D4NUMACCESSTYPES];
	double conf_miss      [2 * D4NUMACCESSTYPES];	/* conflict misses */
	double conf_blockmiss [2 * D4NUMACCESSTYPES];

	double multiblock;
	double bytes_read;
	double bytes_written;
} d4cache;

/* flags for d4cache */
#define D4F_MEM			0x1	/* for simulated memory only */
#define D4F_CCC			0x2	/* compulsory/capacity/conflict classification */
#define D4F_RO			0x4	/* cache is read-only (e.g., an instruction cache) */
#define D4F_USERFLAG1		0x8	/* first available flag bit */




	/*
	 * This macro provides access to certain fields of the
	 * d4cache structure in a way that allows the references to be
	 * replaced by constants if D4CUSTOM is true.  With suitable
	 * definitions of D4_CACHE_* macros, partial evaluation in the
	 * compiler can simplify and speed up simulation.
	 */
#define D4VAL(cache,field)						      \
	((D4CUSTOM && D4_TRIGGER_FIELD(D4_CACHEID,field)) ?		      \
	 D4_VAL_(cache,D4_CACHEID,field) :				      \
         ((cache)->field))
	/* Some additional internal macros help get around ## wierdness */
#define D4_VAL__(cache,cacheid,field)	D4_CACHE_ ## cacheid ## _ ## field
#define D4_VAL_(cache,cacheid,field)	D4_VAL__(cache,cacheid,field)
#define D4_TRIGGER_FIELD_(cacheid,field)	D4_TRIGGER_ ## cacheid ## _ ## field
#define D4_TRIGGER_FIELD(cacheid,field)	D4_TRIGGER_FIELD_(cacheid,field)

	/* define something to avoid undeclared identifiers when !D4CUSTOM */ 
#define D4_CACHEID bogus
#define D4_CACHE_bogus_flags 0
#define D4_TRIGGER_bogus_flags 0
#define D4_CACHE_bogus_lg2blocksize 0
#define D4_TRIGGER_bogus_lg2blocksize 0
#define D4_CACHE_bogus_lg2subblocksize 0
#define D4_TRIGGER_bogus_lg2subblocksize 0
#define D4_CACHE_bogus_lg2size 0
#define D4_TRIGGER_bogus_lg2size 0
#define D4_CACHE_bogus_assoc 0
#define D4_TRIGGER_bogus_assoc 0
#define D4_CACHE_bogus_numsets 0
#define D4_TRIGGER_bogus_numsets 0
#define D4_CACHE_bogus_replacementf NULL
#define D4_TRIGGER_bogus_replacementf 0
#define D4_CACHE_bogus_prefetchf NULL
#define D4_TRIGGER_bogus_prefetchf 0
#define D4_CACHE_bogus_wallocf NULL
#define D4_TRIGGER_bogus_wallocf 0
#define D4_CACHE_bogus_wbackf NULL
#define D4_TRIGGER_bogus_wbackf 0
#define D4_CACHE_bogus_prefetch_abortpercent 0
#define D4_TRIGGER_bogus_prefetch_abortpercent 0

#define D4_OPTS_bogus_ccc 0
#define D4_OPTS_bogus_prefetch_none 0




/*
 * Miscellaneous pseudo-functions
 */
#define D4LG2MASK(n)		 /* make an n-bit mask */		      \
		((((d4addr)1)<<(n))-1)

#define D4ADDR2BLOCK(cache,addr) /* byte address of block containing ref */   \
		((addr) & ~D4LG2MASK(D4VAL(cache,lg2blocksize)))

#define D4ADDR2SUBBLOCK(cache,addr) /* byte addr of subblock for ref */   \
		((addr) & ~D4LG2MASK(D4VAL(cache,lg2subblocksize)))

#define D4ADDR2SET(cache,addr)	/* which set does addr go in? */	      \
		(((addr)>>D4VAL(cache,lg2blocksize)) % D4VAL(cache,numsets))

#define D4REFNSB(cache,mref) /* how many subblocks will mref touch? */	      \
	((((mref).address+(mref).size-1) >> D4VAL(cache,lg2subblocksize)) -   \
	 ((mref).address>>D4VAL(cache,lg2subblocksize)) + 1)

#define D4ADDR2SBMASK(cache,mref) /* produce subblock bit mask for mref */    \
	(D4LG2MASK(D4REFNSB(cache,mref)) <<				      \
	 (((mref).address-D4ADDR2BLOCK(cache,(mref).address)) >>	      \
	  D4VAL(cache,lg2subblocksize)))




/*
 * Compiler support
 */
#if D4CUSTOM && __GNUC__
#define D4_INLINE static inline
#else
#define D4_INLINE
#endif




/*
 * Global data declarations
 */

extern const int d4custom; /* how to tell if this program was customized */
extern struct d4_stackhash_struct d4stackhash; /* hash table for all caches */
extern d4stacknode d4freelist; /* free list for stack nodes of all caches */
extern int d4nnodes;	/* total number of stack nodes allocated */




/*
 * Global declarations for functions making up the Dinero IV
 * subroutine callable interface.
 */

/* top level user-callable functions */
extern d4cache	*d4new (d4cache *);
extern int	d4setup (void);
#if D4CUSTOM && !defined(d4ref)
#define		d4ref(c,m) (*(c)->ref)(c,m) /* call customized version */
#else
void		d4ref (d4cache *, d4memref); /* call generic version */
#endif
void		d4copyback (d4cache *, const d4memref *, int);
void		d4invalidate (d4cache *, const d4memref *, int);
void		d4customize (FILE *);

/* replacement policies */
extern d4stacknode *d4rep_lru (d4cache *, int stacknum, d4memref, d4stacknode *ptr);
extern d4stacknode *d4rep_fifo (d4cache *, int stacknum, d4memref, d4stacknode *ptr);
extern d4stacknode *d4rep_random (d4cache *, int stacknum, d4memref, d4stacknode *ptr);

/* prefetch policies */
extern d4pendstack *d4prefetch_none (d4cache *, d4memref, int miss, d4stacknode *);
extern d4pendstack *d4prefetch_always (d4cache *, d4memref, int miss, d4stacknode *);
extern d4pendstack *d4prefetch_loadforw (d4cache *, d4memref, int miss, d4stacknode *);
extern d4pendstack *d4prefetch_subblock (d4cache *, d4memref, int miss, d4stacknode *);
extern d4pendstack *d4prefetch_miss (d4cache *, d4memref, int miss, d4stacknode *);
extern d4pendstack *d4prefetch_tagged (d4cache *, d4memref, int miss, d4stacknode *);

/* write allocate policies */
extern int d4walloc_always (d4cache *, d4memref);
extern int d4walloc_never (d4cache *, d4memref);
extern int d4walloc_nofetch (d4cache *, d4memref);
extern int d4walloc_impossible (d4cache *, d4memref); /* for icaches */

/* write back/through policies */
extern int d4wback_always (d4cache *, d4memref, int, d4stacknode *, int);
extern int d4wback_never (d4cache *, d4memref, int, d4stacknode *, int);
extern int d4wback_nofetch (d4cache *, d4memref, int, d4stacknode *, int);
extern int d4wback_impossible (d4cache *, d4memref, int, d4stacknode *, int); /* for icaches */

/* initialization routines */
extern void d4init_rep_lru (d4cache *);
extern void d4init_rep_fifo (d4cache *);
extern void d4init_rep_random (d4cache *);

extern void d4init_prefetch_none (d4cache *);
extern void d4init_prefetch_always (d4cache *, int, int);
extern void d4init_prefetch_loadforw (d4cache *, int, int);
extern void d4init_prefetch_subblock (d4cache *, int, int);
extern void d4init_prefetch_miss (d4cache *, int, int);
extern void d4init_prefetch_tagged (d4cache *, int, int);

extern void d4init_walloc_always (d4cache *);
extern void d4init_walloc_never (d4cache *);
extern void d4init_walloc_nofetch (d4cache *);

extern void d4init_wback_always (d4cache *);
extern void d4init_wback_never (d4cache *);
extern void d4init_wback_nofetch (d4cache *);


/* Miscellaneous functions users may or may not need */
extern d4pendstack *d4get_mref(void);	/* allocate struct for pending mref */
extern void d4put_mref (d4pendstack *);	/* deallocate pending mref */
extern void d4init_prefetch_generic (d4cache *); /* helper routine for prefetch */

extern d4stacknode *d4findnth (d4cache *, int stacknum, int n);
extern void d4movetotop (d4cache *, int stacknum, d4stacknode *);
extern void d4movetobot (d4cache *, int stacknum, d4stacknode *);
extern void d4hash (d4cache *, int stacknum, d4stacknode *);




/*
 * Global declarations for internal Dinero IV use.
 */
extern int d4_infcache (d4cache *, d4memref);
extern d4memref d4_splitm (d4cache *, d4memref, d4addr);
extern void d4_dopending (d4cache *, d4pendstack *);
extern void d4_unhash (d4cache *c, int stacknum, d4stacknode *);
extern d4stacknode *d4_find (d4cache *, int stacknum, d4addr blockaddr);
extern void d4_wbblock (d4cache *, d4stacknode *, const int);
extern int d4_ncustom;
extern long *d4_cust_vals[];
