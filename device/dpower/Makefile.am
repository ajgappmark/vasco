#
#             (c) 2006-2012 Pierre Gaufillet <pierre.gaufillet@magic.fr> 
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
TOOLSDIR=@PUF@/tools
CC=sdcc
ASM=gpasm
GLNK=gplink
LNK=sdcc
DOCKER=docker
LIBPUF=@PUF@/lib/libpuf.lib
LIBIO=$(TOOLSDIR)/share/sdcc/lib/pic16/libio@PUF_SDCC_TARGET@.lib
LIBC18F=$(TOOLSDIR)/share/sdcc/lib/pic16/libc18f.lib
AM_CFLAGS =--use-non-free -mpic16 -p@PUF_SDCC_TARGET@ --denable-peeps --obanksel=9\
 --opt-code-size --optimize-cmp --optimize-df $(DEBUG)

if PUF_DEBUG
lkr_PIC_TYPE = @PUF_LKR_TARGET@-application-debug
else
lkr_PIC_TYPE = @PUF_LKR_TARGET@-application
endif

if APPLICATION_DEBUG
DEBUG = -D_DEBUG
else
DEBUG =
endif

export PATH:=$(TOOLSDIR)/bin:$(PATH)

COMPILE=$(CC) $(AM_CFLAGS) -I@PUF@/include
LINK=$(LNK) -o $@ $(DEBUG) $(LDFLAGS) --no-crt -Wl-s@PUF@/lkr/$(lkr_PIC_TYPE).lkr,-m \
	--use-non-free -mpic16 -p@PUF_SDCC_TARGET@ -l$(LIBPUF) -llibio@PUF_SDCC_TARGET@.lib -llibc18f.lib

bin_PROGRAMS = dpower.hex
dpower_hex_SOURCES = usb_descriptors.h \
                          application_iface.c main.c \
                          usb_descriptors.c power_ep1.c \
                          power_ep1.h power_ep2.c power_ep2.h \
                          picon.h power_mgr.c power_mgr.h \
                          rtjobs.c power_ep3.h power_ep3.c

EXTRA_DIST=$(lkr_PIC_TYPE).lkr

CLEANFILES=*.o *.rel *.lst *.cod *.map *.asm
DISTCLEANFILES=.deps

prog: dpower.hex
	(echo "Writing...";\
	$(DOCKER) -v a5a5 write $<)

# Dependencies as compilation side-effect, as recommanded by automake manual
.c.o:
	$(COMPILE) -c $<
	@if [ ! -d .deps ]; then mkdir -p .deps; fi
	@$(SHELL) -ec '$(COMPILE) -M $< > .deps/$*.d'

TDEPENDENCIES=$(filter %.c,$(dpower_hex_SOURCES))
CDEPENDENCIES=$(TDEPENDENCIES:.c=.d)
DDEPENDENCIES=$(addprefix .deps/,$(CDEPENDENCIES))

-include $(DDEPENDENCIES)
