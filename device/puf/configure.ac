#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.64)
AC_COPYRIGHT(Copyright (C) 2006-2009 Pierre Gaufillet)
AC_REVISION($Id$)
AC_INIT(puf, 1.2, vasco-project@lists.gforge.enseeiht.fr)
AM_INIT_AUTOMAKE([no-dependencies no-exeext dist-bzip2])
AC_CONFIG_SRCDIR([bootloader/boot_main.c])
AC_CONFIG_HEADER(bootloader/am_config.h)

AC_ARG_ENABLE([bootloader-debugging],
     [  --enable-bootloader-debugging      Turn on bootloader debugging],
     [case "${enableval}" in
       yes) debug_bootloader=true ;;
       no)  debug_bootloader=false ;;
       *) AC_MSG_ERROR([bad value ${enableval} for --enable-bootloader-debugging]) ;;
     esac],[debug_bootloader=false])
     AM_CONDITIONAL([DEBUG_BOOTLOADER], [test x$debug_bootloader = xtrue])

AC_MSG_CHECKING(if bootloader debugging mode is set)
if test x$debug_bootloader = xtrue; then
    AC_MSG_RESULT(yes)
else
    AC_MSG_RESULT(no)
fi

AC_CONFIG_FILES([Makefile
                 application/Makefile
                 archives/Makefile
                 include/Makefile
                 lib/Makefile
                 bootloader/Makefile
                 scripts/Makefile
                 udev/Makefile])
                 
AC_OUTPUT
