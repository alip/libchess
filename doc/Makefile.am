EXTRA_DIST= doxygen.conf.in
MAINTAINERCLEANFILES = Makefile.in doxygen.conf
CLEANFILES= *~ api/* libchess.tag

if HAVE_DOXYGEN

doxygen: doxygen.conf
	doxygen doxygen.conf

else

doxygen:
	@echo "You don't have doxygen installed!"
	exit 1

endif
