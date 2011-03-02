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

AC_INIT(puf, 1.2, vasco-project@lists.gforge.enseeiht.fr)
AC_PREREQ(2.67)
AC_COPYRIGHT(Copyright 2006-2011 Pierre Gaufillet)
AC_REVISION([$Id$])
AM_INIT_AUTOMAKE([no-dependencies no-exeext dist-bzip2])
AC_CONFIG_SRCDIR([bootloader/boot_main.c])
AC_CONFIG_HEADER(bootloader/am_config.h)

# PUF_CANONICAL_TARGET
# -------------------
# Re-using the standard --target option for puf purpose.
# The key here is $target_alias, receiving by default
# the --target value 
AC_DEFUN_ONCE([PUF_CANONICAL_TARGET],
[m4_divert_once([HELP_CANON],
[[
System types:
  --target=TARGET   configure for building compilers and puf for TARGET]])dnl
AC_CACHE_CHECK([target type], [puf_cv_target],
[puf_cv_target=`$SHELL "$ac_aux_dir/config.sub" $target_alias` ||
 AC_MSG_ERROR([$SHELL $ac_aux_dir/config.sub $target_alias failed])])dnl
])# PUF_CANONICAL_TARGET

PUF_CANONICAL_TARGET
#
# Transmit the target to Makefiles through 
# @PUF_TARGET@ (e.g. pic18f4553-microchip-none)
# @PUF_SDCC_TARGET@ (e.g. 18f4550)
# @PUF_ODYSSEY_TARGET@ (e.g. PIC18F4553)
# @PUF_LKR_TARGET@ (e.g. 18f4553)
#
AC_SUBST(PUF_TARGET, [$puf_cv_target])

puf_sdcc_target=`echo $puf_cv_target | sed 's/-.*$//' | sed 's/pic//'`
# Manage substitutions rules for SDCC
# Used as a work around for unsupported chips
# when they are close enough to already known ones
case $puf_sdcc_target in
	18f2458 )
		puf_sdcc_target=18f2455
		;;
	18f2553 )
		puf_sdcc_target=18f2550
		;;
	18f4458 )
		puf_sdcc_target=18f4455
		;;
	18f4553 )
		puf_sdcc_target=18f4550
		;;
esac
	
AC_SUBST(PUF_SDCC_TARGET, [$puf_sdcc_target])

puf_lkr_target=`echo $puf_cv_target | sed 's/-.*$//' | sed 's/pic//'`
# Manage substitutions rules for linker scripts
case $puf_lkr_target in
	18f2458 |\
	18f4455 |\
	18f4458)
		puf_lkr_target=18f2455
		;;
	18f2550 |\
	18f2553 |\
	18f4553 )
		puf_lkr_target=18f4550
		;;
esac
	
AC_SUBST(PUF_LKR_TARGET, [$puf_lkr_target])

puf_odyssey_target=`echo $puf_cv_target | sed 's/-.*$//' | tr [[:lower:]] [[:upper:]]`
AC_SUBST(PUF_ODYSSEY_TARGET, [$puf_odyssey_target])


AC_ARG_ENABLE([bootloader-debugging],
     [  --enable-bootloader-debugging      Turn on bootloader debugging],
     [case "${enableval}" in
       yes) debug_bootloader=true ;;
       no)  debug_bootloader=false ;;
       *) AC_MSG_ERROR([bad value ${enableval} for --enable-bootloader-debugging]) ;;
     esac],[debug_bootloader=false])
     AM_CONDITIONAL([DEBUG_BOOTLOADER], [test x$debug_bootloader = xtrue])

AC_MSG_CHECKING([if bootloader debugging mode is set])
if test x$debug_bootloader = xtrue; then
    AC_MSG_RESULT(yes)
else
    AC_MSG_RESULT(no)
fi

AC_ARG_WITH([crt0],
    AS_HELP_STRING([--with-bootloader-crt0=crt0|crt0i|crt0iz], [specify the runtime start code of the bootloader]),
    [case "${withval}" in
       crt0 | crt0i | crt0iz ) puf_cv_crt0=${withval}.o ;;
       *) AC_MSG_ERROR([bad value ${withval} for --with-crt0: only crt0, crt0i and crt0iz are supported.]) ;;
     esac],
    [puf_cv_crt0=crt0.o])
    
AC_MSG_CHECKING([which runtime start code to use for the bootloader])
AC_MSG_RESULT(${puf_cv_crt0})
AC_SUBST(PUF_CRT0, [$puf_cv_crt0])

AC_CONFIG_FILES([Makefile
                 application/Makefile
                 archives/Makefile
                 include/Makefile
                 lib/Makefile
                 bootloader/Makefile
                 scripts/Makefile
                 udev/Makefile
                 lkr/Makefile])
                 
AC_OUTPUT
