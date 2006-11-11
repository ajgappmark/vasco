/*-------------------------------------------------------------------------
  main.c - Application main function

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
-------------------------------------------------------------------------*/

#include <pic18fregs.h>
#include "common_types.h"
#include "debug.h"
#include "boot_iface.h"
#include "power_ep1.h"
#include "power_ep2.h"
#include <stdio.h>

#define ftoggle_A0() { PORTAbits.AN0 = !PORTAbits.AN0; }


/******************************************************************/

// beware : this is not a C main function, but the application
// entry point called from the boot.

static ulong counter;
const uchar picon_ep = 3; // picon EP

void application_main(void) 
{
    PORTAbits.AN0 = 1;
    stdout = STREAM_USER;
    counter = 0;
    debug("init power supply manager\n");  

    while(usb_active_cfg > 2)
    {
        counter++;
        if(counter == 0x4000) {
            ftoggle_A0();
        }
        if(counter == 0x10000) {
            ftoggle_A0();
            counter = 0;
            debug("Power manager is alive.\n");
        }
//        usb_sleep();
        dispatch_usb_event();
    }
    PORTAbits.AN0 = 0;
}

/* Interrupt vectors */
#pragma code high_priority_isr 0x2020
void high_priority_isr(void) interrupt
{
}

#pragma code low_priority_isr 0x4000
void low_priority_isr(void) interrupt
{
}

