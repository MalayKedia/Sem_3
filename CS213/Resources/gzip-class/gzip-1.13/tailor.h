/* tailor.h -- target dependent definitions

   Copyright (C) 1997-1999, 2002, 2006, 2009-2023 Free Software Foundation,
   Inc.
   Copyright (C) 1992-1993 Jean-loup Gailly

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.  */

/* The target dependent definitions should be defined here only.
 * The target dependent functions should be defined in tailor.c.
 */

#if defined(__MSDOS__) && !defined(MSDOS)
#  define MSDOS
#endif

#if defined(__OS2__) && !defined(OS2)
#  define OS2
#endif

#if defined(OS2) && defined(MSDOS) /* MS C under OS/2 */
#  undef MSDOS
#endif

#ifdef MSDOS
#  ifdef __GNUC__
     /* DJGPP version 1.09+ on MS-DOS.
      * The DJGPP 1.09 stat() function must be upgraded before gzip will
      * fully work.
      */
#    define near
#  else
#    define MAXSEG_64K
#    ifdef __TURBOC__
#      define off_t long
#    else /* MSC */
#      define HAVE_SYS_UTIME_H
#    endif
#  endif
#  define MAX_PATH_LEN  128
#  define NO_MULTIPLE_DOTS
#  define MAX_EXT_CHARS 3
#  define Z_SUFFIX "z"
#  define NO_SIZE_CHECK
#  define UNLINK_READONLY_BUG
#  define casemap(c) tolow(c) /* Force file names to lower case */
#  include <io.h>
#  define OS_CODE  0x00
#  define SET_BINARY_MODE(fd) setmode(fd, O_BINARY)
#  if !defined(NO_ASM) && !defined(ASMV)
#    define ASMV
#  endif
#else
#  define near
#endif

#ifdef OS2
#  define MAX_PATH_LEN  260
#  ifdef OS2FAT
#    define NO_MULTIPLE_DOTS
#    define MAX_EXT_CHARS 3
#    define Z_SUFFIX "z"
#    define casemap(c) tolow(c)
#  endif
#  define UNLINK_READONLY_BUG
#  include <io.h>
#  define OS_CODE  0x06
#  define SET_BINARY_MODE(fd) setmode(fd, O_BINARY)
#  ifdef _MSC_VER
#    define HAVE_SYS_UTIME_H
#    define MAXSEG_64K
#    undef near
#    define near _near
#  endif
#  ifdef __EMX__
#    define HAVE_SYS_UTIME_H
#    define EXPAND(argc,argv) \
       {_response(&argc, &argv); _wildcard(&argc, &argv);}
#  endif
#  ifdef __ZTC__
#    define NO_DIR 1
#    include <dos.h>
#    define EXPAND(argc,argv) \
       {response_expand(&argc, &argv);}
#  endif
#endif

#if defined WIN32 || defined _WIN32
#  define HAVE_SYS_UTIME_H
#  define MAX_PATH_LEN  260
#  define SET_BINARY_MODE(fd) setmode(fd, O_BINARY)
#  define UNLINK_READONLY_BUG
#  include <io.h>
#  include <malloc.h>
#  ifdef NTFAT
#    define NO_MULTIPLE_DOTS
#    define MAX_EXT_CHARS 3
#    define Z_SUFFIX "z"
#    define casemap(c) tolow(c) /* Force file names to lower case */
#  endif
#  define OS_CODE  0x0b
#endif

#ifdef MSDOS
#  ifdef __TURBOC__
#    include <alloc.h>
#    define DYN_ALLOC
     /* Turbo C 2.0 does not accept static allocations of large arrays */
     void * fcalloc (unsigned items, unsigned size);
     void fcfree (void *ptr);
#  else /* MSC */
#    include <malloc.h>
#    define fcalloc(nitems,itemsize) halloc((long)(nitems),(itemsize))
#    define fcfree(ptr) hfree(ptr)
#  endif
#else
#  ifdef MAXSEG_64K
#    define fcalloc(items,size) calloc((items),(size))
#  else
#    define fcalloc(items,size) malloc((size_t)(items)*(size_t)(size))
#  endif
#  define fcfree(ptr) free(ptr)
#endif

#if defined(ATARI) || defined(atarist)
#  define OS_CODE  0x05
#  ifdef TOSFS
#    define MAX_PATH_LEN  128
#    define NO_MULTIPLE_DOTS
#    define MAX_EXT_CHARS 3
#    define Z_SUFFIX "z"
#    define casemap(c) tolow(c) /* Force file names to lower case */
#  endif
#endif

#ifdef TOPS20
#  define OS_CODE  0x0a
#endif

#ifndef SIGPIPE
# define SIGPIPE 0
#endif


        /* Common defaults */

#ifndef OS_CODE
#  define OS_CODE  0x03  /* assume Unix */
#endif

#ifndef casemap
#  define casemap(c) (c)
#endif

#ifndef OPTIONS_VAR
#  define OPTIONS_VAR "GZIP"
#endif

#ifndef Z_SUFFIX
#  define Z_SUFFIX ".gz"
#endif

#ifdef MAX_EXT_CHARS
#  define MAX_SUFFIX  MAX_EXT_CHARS
#else
#  define MAX_SUFFIX  30
#endif

#ifndef MAKE_LEGAL_NAME
#  ifdef NO_MULTIPLE_DOTS
#    define MAKE_LEGAL_NAME(name)   make_simple_name(name)
#  else
#    define MAKE_LEGAL_NAME(name)
#  endif
#endif

#ifndef MIN_PART
#  define MIN_PART 3
   /* keep at least MIN_PART chars between dots in a file name. */
#endif

#ifndef EXPAND
#  define EXPAND(argc,argv)
#endif

#ifndef SET_BINARY_MODE
#  define SET_BINARY_MODE(fd)
#endif

#ifndef FALLTHROUGH
# if __GNUC__ < 7
#  define FALLTHROUGH ((void) 0)
# else
#  define FALLTHROUGH __attribute__ ((__fallthrough__))
# endif
#endif
