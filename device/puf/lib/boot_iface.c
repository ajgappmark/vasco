/*---------------------------------------------------------------------------
  boot_iface.c - Boot API

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
---------------------------------------------------------------------------*/

/* $Id$ */

#include "common_types.h"

#pragma udata access usb_device_state
uchar __at(0x005f) usb_device_state;
#pragma udata access usb_active_cfg
uchar __at(0x005e) usb_active_cfg;
#pragma udata access usb_active_alt_setting
uchar __at(0x005d) usb_active_alt_setting;

#pragma code boot_goto_table 0x1c

// This dummy function is in fact a table of goto exported to
// the application

void boot_goto_table(void) __naked
{
    __asm

global _boot_version
global _dispatch_usb_event
global _init_usb
global _reset_usb
global _usb_sleep
global _fill_in_buffer

global _ep0_init
global _ep0_in
global _ep0_setup

global _ep1_init
global _ep1_out

global _ep2_init
global _ep2_in

global __mullong
global __mulint
global __gptrget1
global __gptrget2
global __gptrget3
global __gptrget4
global __gptrput1
global __gptrput2
global __gptrput3
global _delay10ktcy
global _delay1ktcy
global _delay10tcy

	__endasm;

#ifdef _DEBUG
    __asm
global _debug_eusart_send_char
global _debug_eusart_flush
global _printf
	__endasm;
#endif

    __asm

_boot_version:       res 2
_dispatch_usb_event: res 4
_init_usb:           res 4
_reset_usb:          res 4
_usb_sleep:          res 4
_fill_in_buffer:     res 4

_ep0_init:           res 4
_ep0_in:             res 4
_ep0_setup:          res 4

_ep1_init:           res 4
_ep1_out:            res 4

_ep2_init:           res 4
_ep2_in:             res 4

__mullong:           res 4
__mulint:            res 4
__gptrget1:          res 4
__gptrget2:          res 4
__gptrget3:          res 4
__gptrget4:          res 4
__gptrput1:          res 4
__gptrput2:          res 4
__gptrput3:          res 4
_delay10ktcy:        res 4
_delay1ktcy:         res 4
_delay10tcy:         res 4

	__endasm;

#ifdef _DEBUG
	__asm
_debug_eusart_send_char: res 4
_debug_eusart_flush:     res 4
_printf:                 res 4
	__endasm;
#endif

}

