#
#             (c) 2006 Pierre Gaufillet <pierre.gaufillet@magic.fr> 
#
#    This library is free software; you can redistribute it and/or
#    modify it under the terms of the GNU Lesser General Public
#    License as published by the Free Software Foundation; either
#    version 2.1 of the License, or (at your option) any later version.
#
#    This library is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#    Lesser General Public License for more details.
#
#    You should have received a copy of the GNU Lesser General Public
#    License along with this library; if not, write to the Free Software
#    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
#
#    $Id$
#

OBJEXT=o
PIC_TYPE=PIC18F4550
sdcc_PIC_TYPE=18f4455
lkr_PIC_TYPE=18f4550
TOOLSDIR=$(shell dirname `pwd`)/tools
CC=$(TOOLSDIR)/bin/sdcc
ASM=$(TOOLSDIR)/bin/gpasm
GLNK=$(TOOLSDIR)/bin/gplink
LNK=$(TOOLSDIR)/bin/sdcc
ODYSSEY=$(TOOLSDIR)/bin/odyssey
CRT0=$(TOOLSDIR)/share/sdcc/lib/pic16/crt0.o
LIBIO=$(TOOLSDIR)/share/sdcc/lib/pic16/libio18f4455.lib
LIBC18F=$(TOOLSDIR)/share/sdcc/lib/pic16/libc18f.lib
#DEBUG =--optimize-goto --denable-peeps --obanksel=9 --opt-code-size --optimize-cmp --optimize-df --fstack 
#DEBUG=-D_DEBUG
#DEBUG=--obanksel=2 --optimize-df --opt-code-size

COMPILE=$(CC) -mpic16 $(DEBUG) -p$(sdcc_PIC_TYPE) -Iinclude -c
LINK=$(LNK) -o $@ $(DEBUG) $(LDFLAGS) --no-crt -Wl-s$(lkr_PIC_TYPE).lkr,-m \
	-mpic16 -p$(sdcc_PIC_TYPE) -llibio$(sdcc_PIC_TYPE).lib -llibc18f.lib


bin_PROGRAMS = application.hex
application_hex_SOURCES = usb_descriptors.h application_iface.h \
                          common_types.h debug.h boot_iface.h \
                          application_iface.c boot_iface.c main.c \
                          usb_descriptors.c

EXTRA_DIST=$(lkr_PIC_TYPE).lkr

CLEANFILES=*.o *.rel *.lst *.cod *.map *.asm


application_iface.o main.o usb_descriptors.o boot_iface.o : usb_descriptors.h application_iface.h common_types.h debug.h boot_iface.h
