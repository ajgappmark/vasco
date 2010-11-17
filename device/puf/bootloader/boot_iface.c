/*---------------------------------------------------------------------------
  boot_iface.c - Boot interface for applications

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

#include "config.h"
#pragma code boot_goto_table 0x1c

// This dummy function is in fact a table of goto exported to
// the application

void boot_goto_table(void) __naked
{
    __asm

    extern _dispatch_usb_event
    extern _init_usb
    extern _reset_usb
    extern _usb_sleep
    extern _fill_in_buffer

    extern _ep0_init
    extern _ep0_in
    extern _ep0_setup

    extern _ep1_init
    extern _ep1_out

    extern _ep2_init
    extern _ep2_in

    extern __mullong
    extern __mulint
    extern __gptrget1
    extern __gptrget2
    extern __gptrget3
    extern __gptrget4
    extern __gptrput1
    extern __gptrput2
    extern __gptrput3
    extern _delay10ktcy
    extern _delay1ktcy
    extern _delay10tcy

;--------------------------------

    DW BOOTLOADER_VERSION ; Boot Version in BCD format

    goto _dispatch_usb_event
    goto _init_usb
    goto _reset_usb
    goto _usb_sleep
    goto _fill_in_buffer

    goto _ep0_init
    goto _ep0_in
    goto _ep0_setup

    goto _ep1_init
    goto _ep1_out

    goto _ep2_init
    goto _ep2_in

    goto __mullong
    goto __mulint
    goto __gptrget1
    goto __gptrget2
    goto __gptrget3
    goto __gptrget4
    goto __gptrput1
    goto __gptrput2
    goto __gptrput3
    goto _delay10ktcy
    goto _delay1ktcy
    goto _delay10tcy

    __endasm;
}

