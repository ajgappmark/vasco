#                                               -*- Autoconf -*-
#   Process this file with autoconf to produce a configure script.
#
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
#
#    $Id$
#

AC_PREREQ(2.64)
AC_COPYRIGHT(Copyright 2006-2010 Pierre Gaufillet)
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
