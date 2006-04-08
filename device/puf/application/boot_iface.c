/*---------------------------------------------------------------------------
  boot_iface.c - Boot API

             (c) 2006 Pierre Gaufillet <pierre.gaufillet@magic.fr> 

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
---------------------------------------------------------------------------*/

/* $Id$ */

#pragma code boot_goto_table 0x1fd2

// This dummy function is in fact a table of goto exported to
// the application

void boot_goto_table(void) __naked
{
    __asm
 
global _boot_version
global _dispatch_usb_event
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

_boot_version: res 2
_dispatch_usb_event: res 4
_reset_usb: res 4
_usb_sleep: res 4
_fill_in_buffer: res 4

_ep0_init: res 4
_ep0_in: res 4
_ep0_setup: res 4

_ep1_init: res 4
_ep1_out: res 4

_ep2_init: res 4
_ep2_in: res 4

    __endasm;

}
    