/*---------------------------------------------------------------------------
  boot_iface.c - Boot interface for applications

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
    
    extern _dispatch_usb_event
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

;--------------------------------
    
    DW 0x0010 ; Boot Version in BCD format

    goto _dispatch_usb_event
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
    
    __endasm;
}
    