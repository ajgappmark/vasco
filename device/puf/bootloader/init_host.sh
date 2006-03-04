#/bin/sh
/etc/init.d/cupsys stop
modprobe -r lp
modprobe ppdev

TOOLSDIR=`dirname \`pwd\``/tools

#$TOOLSDIR/bin/odyssey init
chmod a+r /sys/kernel/debug/usbmon/2t

echo Initialization done.

