#/bin/sh
# $Id$
# This script should be executed as root

# stop cups that claims the parallel port
/etc/init.d/cups stop

# unload the parallel printer module
modprobe -r lp

# load the user parallel port module
modprobe ppdev

echo Initialization done.
echo Now, you can initialize the parallel programmer with odyssey init.
