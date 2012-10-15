#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
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
# $Id$
#

AC_INIT(application, 1.2, vasco-project@lists.gforge.enseeiht.fr)
AC_PREREQ(2.67)
AC_COPYRIGHT(Copyright 2006-2012 Pierre Gaufillet)
AC_REVISION([$Id$])
AM_INIT_AUTOMAKE([no-dependencies no-exeext dist-bzip2])
AC_CONFIG_SRCDIR([main.c])

AC_ARG_WITH(puf, 
  [  --with-puf=PATH        puf PATH (../ if you built puf in the parent directory
                          of application).],PUF="$withval",PUF="..")
AC_SUBST(PUF)
AC_MSG_CHECKING([puf is available])
if test -x $PUF/tools/bin/sdcc
then
	AC_MSG_RESULT([yes])
else
	AC_MSG_RESULT([no])
	AC_MSG_FAILURE([Perhaps you forgot to tell me where is PUF with
	--with-puf=<path> ?])
fi

AC_ARG_ENABLE([app-debug],
     [  --enable-app-debug      Turn on serial debugging (application)],
     [case "${enableval}" in
       yes) adebug=true ;;
       no)  adebug=false ;;
       *) AC_MSG_ERROR([bad value ${enableval} for --enable-app-debug]) ;;
     esac],[adebug=false])
     AM_CONDITIONAL([APPLICATION_DEBUG], [test x$adebug = xtrue])

AC_MSG_CHECKING([if application debugging mode is set])
if test x$adebug = xtrue; then
    AC_MSG_RESULT(yes)
else
    AC_MSG_RESULT(no)
fi

# Read PUF configuration 
. ${PUF}/puf.conf
AC_MSG_CHECKING([if PUF debugging mode is set])
if test x$puf_debug = x; then
    AC_MSG_RESULT(yes)
else
    AC_MSG_RESULT(no)
fi
AM_CONDITIONAL([PUF_DEBUG], [test x$puf_debug = x ])

AC_MSG_CHECKING([for which target PUF has been configured])
AC_MSG_RESULT([$puf_cv_target])
AC_SUBST(PUF_TARGET, [$puf_cv_target])

AC_SUBST(PUF_SDCC_TARGET, [$puf_sdcc_target])
AC_SUBST(PUF_LKR_TARGET, [$puf_lkr_target])


AC_CONFIG_FILES([Makefile])
AC_OUTPUT
