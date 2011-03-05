#
#   Copyright 2006-2011 Pierre Gaufillet <pierre.gaufillet@magic.fr> 
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
TOOLSDIR = @abs_top_srcdir@/tools
CC = sdcc
AM_CFLAGS =--use-non-free -mpic16 -p@PUF_SDCC_TARGET@ --denable-peeps --obanksel=9\
 --opt-code-size --optimize-cmp --optimize-df $(DEBUG)
LNK = sdcc
AM_LDFLAGS = 
ODYSSEY = odyssey

if PUF_DEBUG
DEBUG = -D_DEBUG
lkr_PIC_TYPE = @PUF_LKR_TARGET@-bootloader-debug
bootloader_hex_SOURCES = application_iface.c boot_main.c boot_iface.c \
                         usb.c usb_descriptors.c ep0.c ep1.c ep2.c flash.c \
                         config.c interrupt_iface.c usb.h usb_descriptors.h ep0.h \
                         ep1.h ep2.h application_iface.h \
                         usb_std_req.h common_types.h debug.c \
                         debug.h flash.h boot_iface.h config.h flashmap.c
else
DEBUG =
lkr_PIC_TYPE = @PUF_LKR_TARGET@-bootloader
bootloader_hex_SOURCES = application_iface.c boot_main.c boot_iface.c \
                         usb.c usb_descriptors.c ep0.c ep1.c ep2.c flash.c \
                         config.c interrupt_iface.c usb.h usb_descriptors.h ep0.h \
                         ep1.h ep2.h application_iface.h \
                         usb_std_req.h common_types.h \
                         debug.h flash.h boot_iface.h config.h flashmap.c
endif

export PATH:=$(TOOLSDIR)/bin:$(PATH)

COMPILE=$(CC) $(AM_CFLAGS)
LINK=$(LNK) -o $@ $(DEBUG) $(LDFLAGS) --use-crt=@PUF_CRT0@ -Wl-s../lkr/$(lkr_PIC_TYPE).lkr,-m \
	--use-non-free -mpic16 -p@PUF_SDCC_TARGET@ -llibio@PUF_SDCC_TARGET@.lib -llibc18f.lib

bin_PROGRAMS = bootloader.hex

CLEANFILES=*.o *.rel *.lst *.cod *.map *.asm
DISTCLEANFILES=.deps

prog: bootloader.hex
	(echo "Blanking...";\
	$(ODYSSEY) @PUF_ODYSSEY_TARGET@ erase) && \
	(echo "Writing...";\
	$(ODYSSEY) @PUF_ODYSSEY_TARGET@ write $<)

# Dependencies as compilation side-effect, as recommanded by automake manual
.c.o:
	$(COMPILE) -c $<
	@if [ ! -d .deps ]; then mkdir -p .deps; fi
	@$(SHELL) -ec '$(COMPILE) -M $< > .deps/$*.d'


TDEPENDENCIES=$(filter %.c,$(bootloader_hex_SOURCES))
CDEPENDENCIES=$(TDEPENDENCIES:.c=.d)
DDEPENDENCIES=$(addprefix .deps/,$(CDEPENDENCIES))

-include $(DDEPENDENCIES)
