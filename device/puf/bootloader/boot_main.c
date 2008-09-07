/*-------------------------------------------------------------------------
  boot_main.c - Pic boot main function

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

/* $Id$ */

/* Reserve 255 bytes of stack at 0x200 */
#pragma stack 0x200 255

#include <pic18fregs.h>
#include "common_types.h"
#include "debug.h"
#include "usb.h"
#include "usb_descriptors.h"
#include "application_iface.h"

static uchar safe_boot;
static ulong counter;

void init_boot(void)
{
    ADCON1 = 0x0F;
    CMCON  = 0x07;
    TRISA  = 0xFE;
    PORTA  = 0x01;

    counter = 0x80000;
    while(counter)
    {
        counter--;
    }

    PORTA  = 0x00;
    counter = 0x60000;

    // The RA1 pin is used to force the bootloader only mode
    safe_boot = (application_data.invalid != 0) || PORTAbits.RA1;

    if(!safe_boot)
    {
        // use application descriptors
        debug("Use application descriptors\n");
        device_descriptor        = application_data.device_descriptor;
        configuration_descriptor = application_data.configuration_descriptor;
        string_descriptor        = application_data.string_descriptor;
    }
    else
    {
        // use boot descriptors
        debug("Use boot descriptors\n");
        device_descriptor        = &boot_device_descriptor;
        configuration_descriptor = boot_configuration_descriptor;
        string_descriptor        = boot_string_descriptor;
    }

    // By default always use the booloader vectors
    // because the device is started in configuration 0
    // vectors will be switched in ep0.c when the configuration
    // will become greater than 2
    ep_init  = boot_ep_init;
    ep_in    = boot_ep_in;
    ep_out   = boot_ep_out;
    ep_setup = boot_ep_setup;
}

void toggle_led(ulong* counter)
{
    *counter--;
    if(!*counter)
    {
    	if(PORTAbits.RA0)
    	{
    		*counter = 0x60000;
    	}
    	else
    	{
    		*counter = 0x20000;
    	}
    	PORTAbits.RA0 = !PORTAbits.RA0;
    }
}

void main(void)
{
    init_debug();
    debug("Init boot\n");
    init_boot();

    if(safe_boot)
    {
    	debug("Safe boot mode\n");
    	debug("Init USB\n");
    	init_usb();

    	while(1)
        {
            usb_sleep();
            dispatch_usb_event();
            toggle_led(&counter);
        }
    }

    // init_usb() has to be called by the application
    debug2("Starting application at %x\n", (void *)application_data.main);
    application_data.main();

    INTCON = 0; // Forbid interrupts
    debug("Switch back to bootloader\n");

    while(1)
    {
        if((application_data.invalid == 0) &&
           (GET_ACTIVE_CONFIGURATION() > FLASH_CONFIGURATION))
        {
        	// (void*) avoids sdcc crash when _DEBUG is defined
            debug2("Starting application at %x\n", (void *)application_data.main);
            application_data.main();

            INTCON = 0; // Forbid interrupts
            debug("Switch back to bootloader\n");
        }
        usb_sleep();
        dispatch_usb_event();
        toggle_led(&counter);
    }
}

