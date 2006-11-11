#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
#
# $Id$
#

AC_PREREQ(2.59)
AC_INIT(dpower, 1.1, vasco-project@lists.gforge.enseeiht.fr)
AM_INIT_AUTOMAKE([no-dependencies no-exeext dist-bzip2])
AC_CONFIG_SRCDIR([main.c])

AC_ARG_WITH(puf, 
  [  --with-puf=PATH        puf PATH (../puf if you built puf in the same directory
                          than dpower).],PUF="$withval",PUF="../puf")
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

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
