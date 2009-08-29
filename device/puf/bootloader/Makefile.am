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
PIC_TYPE = PIC18F4550
sdcc_PIC_TYPE = 18f4550
TOOLSDIR = @abs_top_srcdir@/tools
CC = sdcc
AM_CFLAGS =-mpic16 -p$(sdcc_PIC_TYPE) --denable-peeps --obanksel=9\
 --opt-code-size --optimize-cmp --optimize-df $(DEBUG)
LNK = sdcc
AM_LDFLAGS = 
ODYSSEY = odyssey

if DEBUG_BOOTLOADER
DEBUG = -D_DEBUG
lkr_PIC_TYPE = bootloader-18f4550-debug
else
DEBUG =
lkr_PIC_TYPE = bootloader-18f4550
endif

export PATH:=$(TOOLSDIR)/bin:$(PATH)

COMPILE=$(CC) $(AM_CFLAGS) -Iinclude
LINK=$(LNK) -o $@ $(DEBUG) $(LDFLAGS) --use-crt=crt0.o -Wl-s$(lkr_PIC_TYPE).lkr,-m \
	-mpic16 -p$(sdcc_PIC_TYPE) -llibio$(sdcc_PIC_TYPE).lib -llibc18f.lib


bin_PROGRAMS = bootloader.hex
bootloader_hex_SOURCES = application_iface.c boot_main.c boot_iface.c \
                         usb.c usb_descriptors.c ep0.c ep1.c ep2.c flash.c \
                         config.c interrupt_iface.c usb.h usb_descriptors.h ep0.h \
                         ep1.h ep2.h application_iface.h \
                         usb_std_req.h common_types.h \
                         debug.h flash.h boot_iface.h config.h flashmap.c

EXTRA_DIST=bootloader-18f4550.lkr bootloader-18f4550-debug.lkr

CLEANFILES=*.o *.rel *.lst *.cod *.map *.asm

prog: bootloader.hex
	(echo "Blanking...";\
	$(ODYSSEY) $(PIC_TYPE) erase) && \
	(echo "Writing...";\
	$(ODYSSEY) $(PIC_TYPE) write $<)

# Dependencies as compilation side-effect, as recommanded by automake manual
.c.o:
	$(COMPILE) -c $<
	@if [ ! -d .deps ]; then mkdir -p .deps; fi
	@$(SHELL) -ec '$(COMPILE) -M $< > .deps/$*.d'

TDEPENDENCIES=$(filter %.c,$(bootloader_hex_SOURCES))
CDEPENDENCIES=$(TDEPENDENCIES:.c=.d)
DDEPENDENCIES=$(addprefix .deps/,$(CDEPENDENCIES))

-include $(DDEPENDENCIES)
