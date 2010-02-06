AM_CFLAGS= -DGITHEAD=\"$(GITHEAD)\" @LIBCHESS_CFLAGS@

lib_LTLIBRARIES= libchess.la
libchess_la_SOURCES= chess.h chess.c \
		     magicmoves.h magicmoves.c
libchess_la_LDFLAGS= -version-info $(LT_VERSION_INFO)

include_HEADERS= chess.h
