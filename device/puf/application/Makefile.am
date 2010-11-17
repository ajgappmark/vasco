#
#    Copyright 2006-2010 Pierre Gaufillet <pierre.gaufillet@magic.fr> 
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
AM_CFLAGS =--use-non-free -mpic16 -p$(sdcc_PIC_TYPE) --denable-peeps --obanksel=9\
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
	--use-non-free -mpic16 -p$(sdcc_PIC_TYPE) -l$(LIBPUF) -llibio$(sdcc_PIC_TYPE).lib -llibc18f.lib


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
