#!/bin/bash
# $Id$

stty 115200 -cstopb cs8 < /dev/ttyS0
cat /dev/ttyS0

