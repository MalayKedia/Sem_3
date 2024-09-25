## Process this file with automake to create Makefile.in
# Copyright 2010-2023 Free Software Foundation, Inc.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

TESTS =					\
  gzip-env				\
  helin-segv				\
  help-version				\
  hufts					\
  keep					\
  list					\
  list-big				\
  memcpy-abuse				\
  mixed					\
  null-suffix-clobber			\
  pipe-output				\
  reproducible				\
  stdin					\
  timestamp				\
  two-files				\
  trailing-nul				\
  unpack-invalid			\
  unpack-valid				\
  upper-suffix				\
  write-error				\
  z-suffix				\
  zdiff					\
  zgrep-f				\
  zgrep-abuse				\
  zgrep-binary				\
  zgrep-context				\
  zgrep-signal				\
  znew-k

EXTRA_DIST =				\
  $(TESTS)				\
  init.cfg				\
  init.sh				\
  hufts-segv.gz

if LESS
ZLESS_PROG = zless
else
ZLESS_PROG =
endif

built_programs = \
  gzip		\
  gunzip	\
  gzexe		\
  zcat		\
  zcmp		\
  zdiff		\
  zegrep	\
  zfgrep	\
  zforce	\
  zgrep		\
  $(ZLESS_PROG)	\
  zmore		\
  znew

TESTS_ENVIRONMENT =					\
  tmp__=$$TMPDIR; test -d "$$tmp__" || tmp__=.;		\
  TMPDIR=$$tmp__; export TMPDIR;			\
							\
  if test -n "$$BASH_VERSION" || (eval "export v=x") 2>/dev/null; then \
    export_with_values () { export "$$@"; };		\
  else							\
    export_with_values ()				\
    {							\
      sed_extract_var='s/=.*//';			\
      sed_quote_value="s/'/'\\\\''/g;s/=\\(.*\\)/='\\1'/";\
      for arg in "$$@"; do				\
        var=`echo "$$arg" | sed "$$sed_extract_var"`;	\
        arg=`echo "$$arg" | sed "$$sed_quote_value"`;	\
        eval "$$arg";					\
        export "$$var";					\
      done;						\
    };							\
  fi;							\
							\
  export_with_values					\
  LC_ALL=C						\
  VERSION=$(VERSION)					\
  abs_top_builddir='$(abs_top_builddir)'		\
  abs_top_srcdir='$(abs_top_srcdir)'			\
  abs_srcdir='$(abs_srcdir)'				\
  built_programs='$(built_programs)'			\
  srcdir='$(srcdir)'					\
  top_srcdir='$(top_srcdir)'				\
  CC='$(CC)'						\
  GREP='$(GREP)'					\
  GZIP_TEST_NAME=`echo $$tst|sed 's,^\./,,;s,/,-,g'`	\
  MAKE=$(MAKE)						\
  PACKAGE_BUGREPORT='$(PACKAGE_BUGREPORT)'		\
  PACKAGE_VERSION=$(PACKAGE_VERSION)			\
  PERL='$(PERL)'					\
  SHELL='$(SHELL)'					\
  PATH='$(abs_top_builddir)$(PATH_SEPARATOR)'"$$PATH"	\
  ; 9>&2

VERBOSE = yes
