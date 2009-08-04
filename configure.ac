dnl vim: set sw=4 sts=4 ts=4 noet ft=config foldmethod=marker foldmarker={{{,}}} :

dnl {{{ Program, version
AC_PREREQ(2.59)
AC_INIT([src/chess.c])

VERSION_MAJOR=0
VERSION_MINOR=1
VERSION_SUFFIX=_alpha
VERSION_FULL="$VERSION_MAJOR.$VERSION_MINOR$VERSION_SUFFIX"
VERSION="$VERSION_FULL"

AC_SUBST([VERSION_MAJOR])
AC_SUBST([VERSION_MINOR])
AC_SUBST([VERSION_FULL])

AM_INIT_AUTOMAKE(libchess, [$VERSION_FULL])

dnl {{{ Git revision
AC_MSG_CHECKING([for git head])
if test -d "${GIT_DIR:-${ac_top_srcdir:-./}/.git}" ; then
	GIT_HEAD=`git describe 2>/dev/null`
	if test -z ${GIT_HEAD} ; then
		GIT_HEAD=`git rev-parse --short HEAD`
	fi
	if test -n "`git diff-index -m --name-only HEAD`" ; then
		GIT_HEAD=${GIT_HEAD}-dirty
	fi
	if test -n "${GIT_HEAD}" ; then
		GIT_HEAD="-${GIT_HEAD}"
	fi
fi
AC_MSG_RESULT([$GIT_HEAD])
AC_SUBST([GIT_HEAD])
dnl }}}
dnl }}}

dnl {{{ Toolchain checks
AC_PROG_CC_C99
if test x"$ac_cv_prog_cc_c99" = x"no"; then
	AC_MSG_ERROR([emily requires a C compiler that supports ISO C99!])
fi
AC_PROG_INSTALL
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL
dnl }}}

dnl {{{ Extra CFLAGS
LIBCHESS_CFLAGS=
WANTED_CFLAGS="-pedantic -Wall -W -Wextra -Wvla -Wformat=2 -Wformat-security -Wformat-nonliteral -Wlogical-op -Winit-self -Wpointer-arith -Wfloat-equal -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls -Wmissing-noreturn -Wshadow -Wcast-align -Winline"
for flag in $WANTED_CFLAGS ; do
	AX_CHECK_COMPILER_FLAGS([$flag], [LIBCHESS_CFLAGS="$LIBCHESS_CFLAGS $flag"],)
done
AC_SUBST([LIBCHESS_CFLAGS])
dnl }}}

dnl {{{ Library checks
PKG_PROG_PKG_CONFIG([0.20.0])
PKG_CHECK_MODULES([check], [check >= 0.9.4],,)
dnl }}}

dnl {{{ Doxygen
AC_MSG_CHECKING([whether to enable doxygen])
AC_ARG_ENABLE([doxygen],
			  AS_HELP_STRING([--enable-doxygen], [Enable 'make doxygen' (developer docs)]),
			  [HAVE_DOXYGEN=$enableval
			   AC_MSG_RESULT([$enableval])],
			  [AC_MSG_RESULT([autodetect])
			   AC_CHECK_PROG(HAVE_DOXYGEN, [doxygen], [yes], [no])])
AC_SUBST([HAVE_DOXYGEN])
AM_CONDITIONAL([HAVE_DOXYGEN], test "x$HAVE_DOXYGEN" = "xyes")
dnl }}}

dnl {{{ Output
AM_CONFIG_HEADER(config.h)
AC_OUTPUT(
		  libchess.pc
		  Makefile
		  src/Makefile
		  tests/Makefile
		  doc/Makefile
		  doc/doxygen.conf
	)
dnl }}}
