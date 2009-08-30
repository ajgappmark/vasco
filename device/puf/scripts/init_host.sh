#/bin/sh
# $Id$

# Stop cups that claims the parallel port
/etc/init.d/cups stop
# Unload the parallel printer module
modprobe -r lp
# Load the user parallel port module
modprobe ppdev

TOOLSDIR=`dirname \`pwd\``/tools

# Load USB debugging module
modprobe usbmon
# Mount /sys debug filesystem
mount -t debugfs none_debugs /sys/kernel/debug
# Give user read access to USB debug monitor
chmod a+r /sys/kernel/debug/usbmon/*

# Initialize odyssey
$TOOLSDIR/bin/odyssey init

echo Initialization done.
echo Now, you can use the pic programmer with $TOOLSDIR/bin/odyssey.
echo USB packets may be traced in /sys/kernel/debug/usbmon or using Wireshark.
