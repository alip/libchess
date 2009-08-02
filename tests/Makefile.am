TESTS= check_libchess
check_PROGRAMS= check_libchess
check_libchess_SOURCES= check_libchess.c \
			$(top_builddir)/src/chess.h $(top_builddir)/src/chess.c \
			$(top_builddir)/src/magicmoves.h $(top_builddir)/src/magicmoves.c
check_libchess_CFLAGS= -I$(top_builddir)/src -L$(top_builddir)/src/.libs \
		       $(check_CFLAGS) @LIBCHESS_CFLAGS@
check_libchess_LDADD= -lchess $(check_LIBS)
