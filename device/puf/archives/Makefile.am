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

EXTRA_DIST=odyssey-0.5.1.tar.gz sdcc-src-2.8.0.tar.bz2 gputils-0.13.6.tar.bz2

TOOLSDIR=$(shell dirname `pwd`)/tools

export PATH:=$(TOOLSDIR)/bin:$(PATH)

all: gputils odyssey sdcc

odyssey:
	if [ ! -x "$(TOOLSDIR)/bin/odyssey" ]; then \
	 tar xvjf odyssey-0.5.1.tar.bz2;\
	 mkdir -p $(TOOLSDIR);\
	 (cd odyssey-0.5.1 && \
	 ./configure --prefix=$(TOOLSDIR) && \
	 make && \
	 make install);\
	fi
	

sdcc: gputils
	if [ ! -x "$(TOOLSDIR)/bin/sdcc" ]; then \
	 tar xvjf sdcc-src-2.8.0.tar.bz2;\
	 mkdir -p $(TOOLSDIR);\
	 (cd sdcc && \
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
	 tar xvjf gputils-0.13.6.tar.bz2;\
	 mkdir -p $(TOOLSDIR);\
	 (cd gputils-0.13.6 && \
	 ./configure --prefix=$(TOOLSDIR) && \
	 make && \
	 make install);\
	fi
	
distclean clean:
	rm -fr $(TOOLSDIR)
	rm -fr gputils-0.13.6
	rm -fr sdcc
	rm -fr odyssey-0.5.1
	
.PHONY: all sdcc odyssey gputils
