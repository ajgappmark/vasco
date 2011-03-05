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

ODYSSEY=odyssey-0.6
SDCC=sdcc
SDCCARCH=$(SDCC)-src-3.0.0
GPUTILS=gputils-0.13.7
DOCKER=docker-1.2

EXTRA_DIST=$(ODYSSEY).tar.gz $(SDCCARCH).tar.bz2 $(GPUTILS).tar.bz2 $(DOCKER).tar.bz2

TOOLSDIR=@abs_top_srcdir@/tools

export PATH:=$(TOOLSDIR)/bin:$(PATH)

all: gputils odyssey sdcc docker

odyssey:
	if [ ! -x "$(TOOLSDIR)/bin/odyssey" ]; then \
	 tar xvjf $(ODYSSEY).tar.bz2;\
	 mkdir -p $(TOOLSDIR);\
	 (cd $(ODYSSEY) && \
	 ./configure --prefix=$(TOOLSDIR) && \
	 make && \
	 make install);\
	fi
	

sdcc: gputils
	if [ ! -x "$(TOOLSDIR)/bin/sdcc" ]; then \
	 tar xvjf $(SDCCARCH).tar.bz2;\
	 mkdir -p $(TOOLSDIR);\
	 (cd $(SDCC) && \
	 patch -p1 < ../ustatbits.diff && \
	 patch -p1 < ../pic_list.diff && \
	 (cd device/non-free/lib/pic16/libdev; ./mkmk.sh > Makefile.am) && \
	 cp device/non-free/lib/pic16/pics.all device/lib/pic16 && \
	 (cd device/lib/pic16/libio; ./mkmk.sh > Makefile.am) && \
	 ./configure --disable-z80-port --disable-mcs51-port \
	             --disable-gbz80-port --disable-avr-port \
	             --disable-ds390-port --disable-ds400-port \
	             --disable-pic-port --disable-xa51-port \
	             --disable-hc08-port --disable-ucsim \
	             --prefix=$(TOOLSDIR) && \
	 make && \
	 make install);\
	fi
	
gputils:
	if [ ! -x "$(TOOLSDIR)/bin/gpasm" ]; then \
	 tar xvjf $(GPUTILS).tar.bz2;\
	 mkdir -p $(TOOLSDIR);\
	 (cd $(GPUTILS) && \
	 ./configure --prefix=$(TOOLSDIR) && \
	 make && \
	 make install);\
	fi
	
docker:
	if [ ! -x "$(TOOLSDIR)/bin/docker" ]; then \
	 tar xvjf $(DOCKER).tar.bz2;\
	 mkdir -p $(TOOLSDIR);\
	 (cd $(DOCKER) && \
	 ./configure --prefix=$(TOOLSDIR) && \
	 make && \
	 make install);\
	fi
	
distclean clean:
	rm -fr $(TOOLSDIR)
	rm -fr $(GPUTILS)
	rm -fr $(SDCC)
	rm -fr $(ODYSSEY)
	rm -fr $(DOCKER)
	
.PHONY: all sdcc odyssey gputils docker
