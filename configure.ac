# Initialize AC: ACINIT( package_name, version, bug_report_address)
AC_INIT([SatelliteSimulator], [1.0])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])


# AM stands for Automake commands, AC stands for Autoconf commands
# We use libraries
AC_PROG_RANLIB

AC_LANG(C++)

AC_PROG_CXX

AC_SUBST([CC])

AC_CHECK_LIB([elf],[gelf_getshdr],[],[AC_MSG_ERROR([Package 'libelf-dev' is missing on this computer. Please install and try again!])])
AC_CHECK_HEADERS([libelf.h gelf.h])


AC_CONFIG_FILES([Makefile src/Makefile])
# Finally produce "configure" script
AC_OUTPUT

