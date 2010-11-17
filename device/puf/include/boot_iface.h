/*-------------------------------------------------------------------------
  boot_iface.h - Boot API

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

#ifndef BOOT_H_
#define BOOT_H_

#include "common_types.h"

void boot_goto_table(void);

void dispatch_usb_event(void);
void init_usb(void);
void reset_usb(void);
void usb_sleep(void);
void fill_in_buffer(uchar EPnum,
                    uchar **source,
                    uint buffer_size,
                    uint *nb_byte);

void ep0_init(void);
void ep0_in(void);
void ep0_setup(void);

void ep1_init(void);
void ep1_out(void);

void ep2_init(void);
void ep2_in(void);

extern uchar __at(0x005f) usb_device_state;
extern uchar __at(0x005e) usb_active_cfg;
extern uchar __at(0x005d) usb_active_alt_setting;



#endif /*APPLICATION_H_*/
