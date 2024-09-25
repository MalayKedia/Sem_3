# Configure template for gzip.

# Copyright (C) 1999-2002, 2006-2007, 2009-2023 Free Software Foundation, Inc.

# Copyright (C) 1992-1993 Jean-loup Gailly

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
# 02111-1307, USA.

AC_PREREQ([2.64])
AC_INIT([gzip],
        m4_esyscmd([build-aux/git-version-gen .tarball-version]),
        [bug-gzip@gnu.org])

AC_CONFIG_SRCDIR([gzip.c])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADERS([lib/config.h:lib/config.hin])
AM_INIT_AUTOMAKE([1.11 subdir-objects dist-xz dist-zip
                  color-tests parallel-tests])
AM_SILENT_RULES([yes]) # make --enable-silent-rules the default.

dnl POSIXCHECK is worthwhile for maintainers, but adds several seconds
dnl (more than 10% execution time) to ./configure, with no benefit for
dnl most users.  Using it to look for bugs requires:
dnl   GNULIB_POSIXCHECK=1 autoreconf -f
dnl   ./configure
dnl   make
dnl   make -C src clean
dnl   make CFLAGS=-DGNULIB_POSIXCHECK=1
dnl FIXME: Once we figure out how to avoid false positives, we should
dnl have 'make my-distcheck' in dist-check.mk exercise this.
m4_syscmd([test "${GNULIB_POSIXCHECK+set}" = set])
m4_if(m4_sysval, [0], [], [dnl
gl_ASSERT_NO_GNULIB_POSIXCHECK])

AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_CPP
AC_PROG_GREP
AC_CHECK_PROG([LESS], [less], [less])
AM_CONDITIONAL([LESS], [test "$LESS"])
AC_CHECK_TOOL([NM], [nm], [nm])
AC_PROG_LN_S
AC_PROG_RANLIB
AC_PROG_SHELL

gl_EARLY

gl_INIT

# Ensure VLAs are not used.
# Note -Wvla is implicitly added by gl_MANYWARN_ALL_GCC
AC_DEFINE([GNULIB_NO_VLA], [1], [Define to 1 to disable use of VLAs])

# gl_GCC_VERSION_IFELSE([major], [minor], [run-if-found], [run-if-not-found])
# ------------------------------------------------
# If $CPP is gcc-MAJOR.MINOR or newer, then run RUN-IF-FOUND.
# Otherwise, run RUN-IF-NOT-FOUND.
AC_DEFUN([gl_GCC_VERSION_IFELSE],
  [AC_PREPROC_IFELSE(
    [AC_LANG_PROGRAM(
      [[
#if ($1) < __GNUC__ || (($1) == __GNUC__ && ($2) <= __GNUC_MINOR__)
/* ok */
#else
# error "your version of gcc is older than $1.$2"
#endif
      ]]),
    ], [$3], [$4])
  ]
)

AC_ARG_ENABLE([gcc-warnings],
  [AS_HELP_STRING([--enable-gcc-warnings@<:@=TYPE@:>@],
    [control generation of GCC warnings.  The TYPE 'no' disables
     warnings (default for non-developer builds); 'yes' generates
     cheap warnings if available (default for developer builds);
     'expensive' in addition generates expensive-to-compute warnings
     if available.])],
  [case $enableval in
     no|yes|expensive) ;;
     *)      AC_MSG_ERROR([bad value $enableval for gcc-warnings option]) ;;
   esac
   gl_gcc_warnings=$enableval],
  [
   # GCC provides fine-grained control over diagnostics which
   # is used in gnulib for example to suppress warnings from
   # certain sections of code.  So if this is available and
   # we're running from a git repo, then auto enable the warnings.
   gl_gcc_warnings=no
   gl_GCC_VERSION_IFELSE([4], [6],
                         [test -d "$srcdir"/.git \
                          && ! test -f "$srcdir"/.tarball-version \
                          && gl_gcc_warnings=yes])]
)

AC_ARG_ENABLE([dfltcc],
  [AS_HELP_STRING([--enable-dfltcc],
     [use DEFLATE COMPRESSION CALL instruction on IBM Z])],
  [case $enableval in
     yes|no) gl_dfltcc=$enableval ;;
     *)      AC_MSG_ERROR([bad value $enableval for dfltcc option]) ;;
   esac],
  [gl_dfltcc=no]
)

if test "$gl_gcc_warnings" = yes; then
  gl_WARN_ADD([-Werror], [WERROR_CFLAGS])
  AC_SUBST([WERROR_CFLAGS])

  ew=
  AS_IF([test $gl_gcc_warnings != expensive],
    [# -fanalyzer and related options slow GCC considerably.
     ew="$ew -fanalyzer -Wno-analyzer-double-free -Wno-analyzer-malloc-leak"
     ew="$ew -Wno-analyzer-null-dereference -Wno-analyzer-use-after-free"])

  # This, $nw, is the list of warnings we disable.
  nw=$ew
  nw="$nw -Wdeclaration-after-statement" # too useful to forbid
  nw="$nw -Waggregate-return"       # anachronistic
  nw="$nw -Wlong-long"              # C90 is anachronistic (lib/gethrxtime.h)
  nw="$nw -Wc++-compat"             # We don't care about C++ compilers
  nw="$nw -Wundef"                  # Warns on '#if GNULIB_FOO' etc in gnulib
  nw="$nw -Wtraditional"            # Warns on #elif which we use often
  nw="$nw -Wcast-qual"              # Too many warnings for now
  nw="$nw -Wconversion"             # Too many warnings for now
  nw="$nw -Wduplicated-branches"    # Too many false alarms
  nw="$nw -Wsystem-headers"         # Don't let system headers trigger warnings
  nw="$nw -Wsign-conversion"        # Too many warnings for now
  nw="$nw -Wtraditional-conversion" # Too many warnings for now
  nw="$nw -Wpadded"                 # Our structs are not padded
  nw="$nw -Wredundant-decls"        # openat.h declares e.g., mkdirat
  nw="$nw -Wlogical-op"             # any use of fwrite provokes this
  nw="$nw -Wformat-nonliteral"      # who.c and pinky.c strftime uses
  nw="$nw -Wnested-externs"         # use of XARGMATCH/verify_function__
  nw="$nw -Wswitch-enum"            # Too many warnings for now
  nw="$nw -Wswitch-default"         # Too many warnings for now
  nw="$nw -Wstack-protector"        # not worth working around
  # things I might fix soon:
  nw="$nw -Wfloat-equal"            # sort.c, seq.c
  nw="$nw -Wmissing-format-attribute" # copy.c
  nw="$nw -Wunsafe-loop-optimizations" # a few src/*.c
  nw="$nw -Winline"                 # system.h's readdir_ignoring_dot_and_dotdot

  # Warnings that gzip runs afoul of but coreutils does not.
  nw="$nw -Wold-style-definition"
  nw="$nw -Wshadow"
  nw="$nw -Wstrict-overflow"

  # Using -Wstrict-overflow is a pain, but the alternative is worse.
  # For an example, see the code that provoked this report:
  # https://gcc.gnu.org/bugzilla/show_bug.cgi?id=33498
  # Code like that still infloops with gcc-4.6.0 and -O2.  Scary indeed.

  gl_MANYWARN_ALL_GCC([ws])
  gl_MANYWARN_COMPLEMENT([ws], [$ws], [$nw])
  for w in $ws; do
    gl_WARN_ADD([$w])
  done
  gl_WARN_ADD([-Wno-sign-compare])     # Too many warnings for now
  gl_WARN_ADD([-Wno-type-limits]) # false alarms if 32-bit long, 64-bit time_t
  gl_WARN_ADD([-Wno-unused-parameter]) # Too many warnings for now
  gl_WARN_ADD([-Wsuggest-attribute=const])
  gl_WARN_ADD([-Wsuggest-attribute=noreturn])
  gl_WARN_ADD([-Wno-format-nonliteral])

  # Enable this warning only with gcc-4.7 and newer.  With 4.6.2 20111027,
  # it suggests test.c's advance function may be pure, even though it
  # increments a global variable.  Oops.
  # Normally we'd write code to test for the precise failure, but that
  # requires a relatively large input to make gcc exhibit the failure.
  gl_GCC_VERSION_IFELSE([4], [7], [gl_WARN_ADD([-Wsuggest-attribute=pure])])

  # In spite of excluding -Wlogical-op above, it is enabled, as of
  # gcc 4.5.0 20090517, and it provokes warnings in cat.c, dd.c, truncate.c
  gl_WARN_ADD([-Wno-logical-op])

  gl_WARN_ADD([-fdiagnostics-show-option])
  gl_WARN_ADD([-funit-at-a-time])

  AC_SUBST([WARN_CFLAGS])

  AC_DEFINE([lint], [1], [Define to 1 if the compiler is checking for lint.])
  AH_VERBATIM([FORTIFY_SOURCE],
  [/* Enable compile-time and run-time bounds-checking, and some warnings,
      without upsetting glibc 2.15+. */
   #if !defined _FORTIFY_SOURCE && defined __OPTIMIZE__ && __OPTIMIZE__
   # define _FORTIFY_SOURCE 2
   #endif
  ])
  AC_DEFINE([GNULIB_PORTCHECK], [1], [enable some gnulib portability checks])

  # We use a slightly smaller set of warning options for lib/.
  # Remove the following and save the result in GNULIB_WARN_CFLAGS.
  nw=
  nw="$nw -Wstrict-overflow"
  nw="$nw -Wformat-truncation=2"
  nw="$nw -Wuninitialized"
  nw="$nw -Wunused-macros"
  nw="$nw -Wmissing-prototypes"
  nw="$nw -Wold-style-definition"
  gl_MANYWARN_COMPLEMENT([GNULIB_WARN_CFLAGS], [$WARN_CFLAGS], [$nw])
  AC_SUBST([GNULIB_WARN_CFLAGS])
fi

if test "$gl_dfltcc" = yes; then
  AC_DEFINE([IBM_Z_DFLTCC], ,
    [Use DEFLATE COMPRESSION CALL instruction on IBM Z machines.])
fi
AM_CONDITIONAL([IBM_Z_DFLTCC],  [test "$gl_dfltcc" = yes])

# cc -E produces incorrect asm files on SVR4, so postprocess it.
ASCPPPOST="sed '/^ *\\#/d; s,//.*,,; s/% /%/g; s/\\. /./g'"
AC_SUBST([ASCPPPOST])

AC_CACHE_CHECK([for underline in external names], [gzip_cv_underline],
  [gzip_cv_underline=yes
   AC_COMPILE_IFELSE(
     [AC_LANG_PROGRAM([[int foo() {return 0;}]], [[]])],
       [$NM conftest.$OBJEXT | grep _foo >/dev/null 2>&1 ||
        gzip_cv_underline=no])])
ASCPPFLAGS=
if test $gzip_cv_underline = no; then
  ASCPPFLAGS='-DNO_UNDERLINE'
fi
AC_SUBST([ASCPPFLAGS])
AC_OBJEXT

# Try to assemble match.S.
# "gcc -E match.s" ignores -E, so we must use _match.S.
AC_CACHE_CHECK([for an assembler syntax supported by this package],
  [gzip_cv_assembler],
  [gzip_cv_assembler=no
   case $DEFS in
   *NO_ASM*) ;;
   *)
     if cp $srcdir/lib/match.c _match.S &&
        eval "$CPP $CPPFLAGS $ASCPPFLAGS _match.S > _match.i" &&
        eval "$ASCPPPOST < _match.i > match_.s"; then
       if test ! -s match_.s || grep error < match_.s > /dev/null; then
         :
       elif eval "$CC $CPPFLAGS $CFLAGS -c match_.s >/dev/null" &&
            test -f match_.$OBJEXT; then
         rm -f match_.$OBJEXT
         gzip_cv_assembler=yes
         if echo 'void foo (void) {}' > conftest.c &&
            eval "$CC $CPPFLAGS $CFLAGS -S conftest.c >/dev/null" &&
            grep '\.note\.GNU-stack' conftest.s >/dev/null &&
            eval "$CC $CPPFLAGS $CFLAGS -c -Wa,--noexecstack match_.s >/dev/null" &&
            test -f match_.$OBJEXT; then
           gzip_cv_assembler='yes, with -Wa,--noexecstack'
         fi
       fi
     fi
     rm -f conftest* _match.i _match.S match_.s match_.$OBJEXT;;
   esac])
if test "$gzip_cv_assembler" != no; then
  AC_DEFINE([ASMV], ,
    [Define if an assembler version of longest_match is available.])
  AC_LIBOBJ(match)
fi
if test "$gzip_cv_assembler" = 'yes, with -Wa,--noexecstack'; then
  ASFLAGS_config='-Wa,--noexecstack'
else
  ASFLAGS_config=
fi
AC_SUBST([ASFLAGS_config])

GZIP_TRANSFORMED=` echo gzip  | sed "$program_transform_name"`
ZDIFF_TRANSFORMED=`echo zdiff | sed "$program_transform_name"`
ZGREP_TRANSFORMED=`echo zgrep | sed "$program_transform_name"`
AC_SUBST([GZIP_TRANSFORMED])
AC_SUBST([ZDIFF_TRANSFORMED])
AC_SUBST([ZGREP_TRANSFORMED])
AM_CONDITIONAL([GZIP_IS_TRANSFORMED],  [test "$GZIP_TRANSFORMED" != gzip])
AM_CONDITIONAL([ZDIFF_IS_TRANSFORMED],  [test "$ZDIFF_TRANSFORMED" != zdiff])
AM_CONDITIONAL([ZGREP_IS_TRANSFORMED],  [test "$ZGREP_TRANSFORMED" != zgrep])

AC_C_CONST
AC_CHECK_HEADERS_ONCE(fcntl.h limits.h memory.h time.h sys/sdt.h)
AC_CHECK_FUNCS_ONCE([chown fchmod fchown lstat siginterrupt])
AC_HEADER_DIRENT
AC_TYPE_SIZE_T
AC_TYPE_OFF_T

AC_CONFIG_FILES([Makefile doc/Makefile lib/Makefile tests/Makefile])
AC_OUTPUT
