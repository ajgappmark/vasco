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

#
# BEWARE : SDCCLIB should not be used. sdcc seems to be compatible only with gplib !
#

OBJEXT=o
PIC_TYPE = PIC18F4550
sdcc_PIC_TYPE = 18f4550
lkr_PIC_TYPE = 18f4550
TOOLSDIR = @abs_top_srcdir@/tools
CC = sdcc
GPLIB = gplib
AM_CFLAGS =--use-non-free -mpic16 -p$(sdcc_PIC_TYPE) $(DEBUG) -I../include
AM_LDFLAGS = 
ODYSSEY = odyssey
DEBUG =--denable-peeps --obanksel=9 --opt-code-size --optimize-cmp --optimize-df 
#DEBUG = -D_DEBUG

export PATH:=$(TOOLSDIR)/bin:$(PATH)

COMPILE=$(CC) $(AM_CFLAGS) $(CFLAGS) -c


noinst_PROGRAMS = libpuf.lib
libpuf_lib_SOURCES = picon.c boot_iface.c usb.c sequencer.c 

libpuf.lib: picon.o sequencer.o usb.o boot_iface.o
	$(GPLIB) -c $@ $+

CLEANFILES=*.o *.rel *.lst *.cod *.map *.asm

# Dependencies as compilation side-effect, as recommanded by automake manual
.c.o:
	$(COMPILE) -c $<
	@if [ ! -d .deps ]; then mkdir -p .deps; fi
	@$(SHELL) -ec '$(COMPILE) -M $< > .deps/$*.d'

TDEPENDENCIES=$(filter %.c,$(bootloader_hex_SOURCES))
CDEPENDENCIES=$(TDEPENDENCIES:.c=.d)
DDEPENDENCIES=$(addprefix .deps/,$(CDEPENDENCIES))

-include $(DDEPENDENCIES)
