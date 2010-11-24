#
#   Copyright 2006-2010 Pierre Gaufillet <pierre.gaufillet@magic.fr> 
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
#    $Id$
#

OBJEXT=o
PIC_TYPE = PIC18F4550
sdcc_PIC_TYPE = 18f4550
TOOLSDIR = @abs_top_srcdir@/tools
CC = sdcc
AM_CFLAGS =--use-non-free -mpic16 -p$(sdcc_PIC_TYPE) --denable-peeps --obanksel=9\
 --opt-code-size --optimize-cmp --optimize-df $(DEBUG)
LNK = sdcc
AM_LDFLAGS = 
ODYSSEY = odyssey

if DEBUG_BOOTLOADER
DEBUG = -D_DEBUG
lkr_PIC_TYPE = bootloader-18f4550-debug
bootloader_hex_SOURCES = application_iface.c boot_main.c boot_iface.c \
                         usb.c usb_descriptors.c ep0.c ep1.c ep2.c flash.c \
                         config.c interrupt_iface.c usb.h usb_descriptors.h ep0.h \
                         ep1.h ep2.h application_iface.h \
                         usb_std_req.h common_types.h debug.c \
                         debug.h flash.h boot_iface.h config.h flashmap.c
else
DEBUG =
lkr_PIC_TYPE = bootloader-18f4550
bootloader_hex_SOURCES = application_iface.c boot_main.c boot_iface.c \
                         usb.c usb_descriptors.c ep0.c ep1.c ep2.c flash.c \
                         config.c interrupt_iface.c usb.h usb_descriptors.h ep0.h \
                         ep1.h ep2.h application_iface.h \
                         usb_std_req.h common_types.h \
                         debug.h flash.h boot_iface.h config.h flashmap.c
endif

export PATH:=$(TOOLSDIR)/bin:$(PATH)

COMPILE=$(CC) $(AM_CFLAGS)
LINK=$(LNK) -o $@ $(DEBUG) $(LDFLAGS) --use-crt=crt0.o -Wl-s$(lkr_PIC_TYPE).lkr,-m \
	--use-non-free -mpic16 -p$(sdcc_PIC_TYPE) -llibio$(sdcc_PIC_TYPE).lib -llibc18f.lib


bin_PROGRAMS = bootloader.hex

EXTRA_DIST=bootloader-18f4550.lkr bootloader-18f4550-debug.lkr

CLEANFILES=*.o *.rel *.lst *.cod *.map *.asm
DISTCLEANFILES=.deps

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
