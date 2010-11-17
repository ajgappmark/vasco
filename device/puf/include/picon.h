/*-------------------------------------------------------------------------
  picon.h - USB endpoint callbacks

   Copyright 2006-2010 Pierre Gaufillet <pierre.gaufillet@magic.fr>

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
-------------------------------------------------------------------------*/

/* $Id$ */

#ifndef PICON_H_
#define PICON_H_

// Size of the End point packets in bytes
#define PICON_PACKET_SIZE 8

/* EP USB buffer */
#define DEFINE_PICON_BUFFER(size) _Pragma("udata usb_buf Picon_InBuffer_tab") volatile uchar Picon_InBuffer_tab[size]; \
volatile uchar* const Picon_InBuffer = Picon_InBuffer_tab;\
const uint picon_buffer_size = size;

/* EP # */
#define DEFINE_PICON_EP(number) const uchar picon_ep = number;

void picon_init(void);
void picon_in(void);
void prepare_in(void);

#endif /*PICON_H_*/
