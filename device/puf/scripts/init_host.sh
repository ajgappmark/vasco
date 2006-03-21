#/bin/sh
# $Id$

# stop cups that claims the parallel port
/etc/init.d/cupsys stop
# unload the parallel printer module
modprobe -r lp
# load the user parallel port module
modprobe ppdev

TOOLSDIR=`dirname \`pwd\``/tools

# give user read access to USB debug monitor
chmod a+r /sys/kernel/debug/usbmon/2t

echo Initialization done.
echo Now, you can initialize the parallel programmer with $TOOLSDIR/bin/odyssey init.
