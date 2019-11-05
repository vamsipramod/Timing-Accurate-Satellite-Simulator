# Initialize AC: ACINIT( package_name, version, bug_report_address)
AC_INIT([SatSim], [1.0], [111601010@smail.iitpkd.ac.in, sandeepchandran@iitpkd.ac.in])
AM_INIT_AUTOMAKE


# AM stands for Automake commands, AC stands for Autoconf commands
# We use libraries
AC_PROG_RANLIB

AC_LANG(C++)

AC_PROG_CXX

AC_SUBST([CC])

AC_CHECK_LIB([elf],[gelf_getshdr],[],[AC_MSG_ERROR([Package 'libelf-dev' is missing on this computer. Please install and try again!])])
AC_CHECK_HEADERS([libelf.h gelf.h])


# Finally produce "configure" script
AC_OUTPUT(Makefile src/Makefile)

