# Customize maint.mk                           -*- makefile -*-
# Copyright (C) 2003-2023 Free Software Foundation, Inc.

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

# Don't include the translation project coordinator email address
# in announcement template.
translation_project_ =

# Used in maint.mk's web-manual rule
manual_title = gzip: the data compression program

# Use the direct link.  This is guaranteed to work immediately, while
# it can take a while for the faster mirror links to become usable.
url_dir_list = https://ftp.gnu.org/gnu/$(PACKAGE)

# Tests not to run as part of "make distcheck".
local-checks-to-skip =		\
  sc_bindtextdomain		\
  sc_error_message_period	\
  sc_error_message_uppercase	\
  sc_indent			\
  sc_program_name		\
  sc_texinfo_acronym

# Tools used to bootstrap this package, used for "announcement".
bootstrap-tools = autoconf,automake,gnulib

# Now that we have better tests, make this the default.
export VERBOSE = yes

old_NEWS_hash = 053f232e511b9a95079de114760117a7

sc_obs_header_regex = \
  \<(STDC_HEADERS|HAVE_(LIMITS|STRING|UNISTD|STDLIB)_H)\>
sc_prohibit_obsolete_HAVE_HEADER_H:
	@prohibit='^[	 ]*#[	 ]*(el)?if.*$(sc_obs_header_regex)' \
	halt='remove the above obsolete #if...HAVE_HEADER_H test(s)' \
	  $(_sc_search_regexp)

update-copyright-env = \
  UPDATE_COPYRIGHT_USE_INTERVALS=1 \
  UPDATE_COPYRIGHT_MAX_LINE_LENGTH=79

# Indent only with spaces.
sc_prohibit_tab_based_indentation:
	@prohibit='^ *	'						\
	halt='TAB in indentation; use only spaces'			\
	  $(_sc_search_regexp)

# Don't use "indent-tabs-mode: nil" anymore.  No longer needed.
sc_prohibit_emacs__indent_tabs_mode__setting:
	@prohibit='^( *[*#] *)?indent-tabs-mode:'			\
	halt='use of emacs indent-tabs-mode: setting'			\
	  $(_sc_search_regexp)

ifeq ($(srcdir),.)
  srcdirslash =
else
  srcdirslash = $(srcdir)/
endif

sc_gzip_copyright_check:
	@require='Copyright \(C\) '$$(date +%Y)' Free'			\
	in_vc_files='^$(srcdirslash)(gzip\.c|[^z].*\.in|z[^ef].*\.in|zf[^g].*\.in)$$'	\
	halt="out of date copyright in $$in_vc_files; update it"	\
	  $(_sc_search_regexp)

include $(srcdir)/dist-check.mk

exclude_file_name_regexp--sc_file_system = ^NEWS$$
exclude_file_name_regexp--sc_prohibit_tab_based_indentation = \
  (^|/)(GNU)?[Mm]akefile|(^|/)ChangeLog|\.(am|mk)$$
exclude_file_name_regexp--sc_require_config_h = ^lib/match\.c$$
exclude_file_name_regexp--sc_require_config_h_first = ^lib/match\.c$$
exclude_file_name_regexp--sc_prohibit_empty_lines_at_EOF = \
  ^tests/hufts-segv\.gz$$
exclude_file_name_regexp--sc_prohibit_strcmp = ^gzip\.c$$
exclude_file_name_regexp--sc_prohibit_always-defined_macros = ^tailor\.h$$
exclude_file_name_regexp--sc_prohibit_atoi_atof = ^(gzip|sample/sub)\.c$$
exclude_file_name_regexp--sc_space_tab = ^lib/match\.c$$
exclude_file_name_regexp--sc_useless_cpp_parens = ^(lib/match\.c|tailor\.h)$$

exclude_file_name_regexp--sc_prohibit_double_semicolon = ^lib/match\.c$$

# Tell the tight_scope rule that sources are in ".".
export _gl_TS_dir = .

# Tell the tight_scope rule that these variables are deliberately "extern".
export _gl_TS_unmarked_extern_vars = \
  block_start d_buf inbuf outbuf prev read_buf strstart window \
  match_start prev_length max_chain_length good_match nice_match

_gl_TS_extern = (?:_Noreturn )?extern

# Add an exemption for sc_makefile_at_at_check.
_makefile_at_at_check_exceptions = ' && !/MAKEINFO/'
