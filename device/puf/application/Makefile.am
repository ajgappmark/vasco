#
#             (c) 2006-2009 Pierre Gaufillet <pierre.gaufillet@magic.fr> 
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
sdcc_PIC_TYPE=18f4550
TOOLSDIR=@abs_top_srcdir@/tools
CC=sdcc
ASM=gpasm
GLNK=gplink
LNK=sdcc
ODYSSEY=odyssey
CRT0=$(TOOLSDIR)/share/sdcc/lib/pic16/crt0.o
LIBPUF=../lib/libpuf.lib
LIBIO=$(TOOLSDIR)/share/sdcc/lib/pic16/libio18f4550.lib
LIBC18F=$(TOOLSDIR)/share/sdcc/lib/pic16/libc18f.lib
AM_CFLAGS =-mpic16 -p$(sdcc_PIC_TYPE) --denable-peeps --obanksel=9\
 --opt-code-size --optimize-cmp --optimize-df $(DEBUG)

if DEBUG_BOOTLOADER
DEBUG = -D_DEBUG
lkr_PIC_TYPE = application-18f4550-debug
else
DEBUG =
lkr_PIC_TYPE = application-18f4550
endif

export PATH:=$(TOOLSDIR)/bin:$(PATH)

COMPILE=$(CC) $(AM_CFLAGS) -I../include -c
LINK=$(LNK) -o $@ $(DEBUG) $(LDFLAGS) --no-crt -Wl-s$(lkr_PIC_TYPE).lkr,-m \
	-mpic16 -p$(sdcc_PIC_TYPE) -l$(LIBPUF) -llibio$(sdcc_PIC_TYPE).lib -llibc18f.lib


bin_PROGRAMS = application.hex
application_hex_SOURCES = usb_descriptors.h  \
                          application_iface.c main.c \
                          usb_descriptors.c

EXTRA_DIST=application-18f4550.lkr application-18f4550-debug.lkr

CLEANFILES=*.o *.rel *.lst *.cod *.map *.asm
DISTCLEANFILES=.deps

# Dependencies as compilation side-effect, as recommanded by automake manual
.c.o:
	$(COMPILE) -c $<
	@if [ ! -d .deps ]; then mkdir -p .deps; fi
	@$(SHELL) -ec '$(COMPILE) -M $< > .deps/$*.d'

TDEPENDENCIES=$(filter %.c,$(bootloader_hex_SOURCES))
CDEPENDENCIES=$(TDEPENDENCIES:.c=.d)
DDEPENDENCIES=$(addprefix .deps/,$(CDEPENDENCIES))

-include $(DDEPENDENCIES)
