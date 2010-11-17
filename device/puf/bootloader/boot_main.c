/*-------------------------------------------------------------------------
  boot_main.c - Pic boot main function

   Copyright 2005-2010 Pierre Gaufillet <pierre.gaufillet@magic.fr>

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

/* Reserve 255 bytes of stack at 0x200 */
#pragma stack 0x200 255

#include <pic18fregs.h>
#include "am_config.h"
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
    counter = 0x7000;

    // SAFEBOOT_BUTTON pin is used to force the bootloader only mode
    // SAFEBOOT_BUTTON is set in config.h
    safe_boot = (application_data.invalid != 0) || SAFE_BOOT_BUTTON;

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

void toggle_led()
{
    counter--;
    if(!counter)
    {
    	if(PORTAbits.RA0)
    	{
    		counter = 0x7000;
    	}
    	else
    	{
    		counter = 0x1000;
    	}
    	PORTAbits.RA0 = !PORTAbits.RA0;
    }
}

void main(void)
{
    init_debug();
    debug("Booting %s\n", PACKAGE_STRING);
    init_boot();

    if(safe_boot)
    {
    	debug("Safe boot mode\n");
    	debug("Init USB\n");
    	 // Flush here to save a few eusart buffer bytes before USB starts
    	debug_eusart_flush();
    	init_usb();

    	while(1)
        {
    		// In debug mode, we want the device to go on with USART
    		// So disable sleep mode when USB is suspended
#ifndef _DEBUG
    		usb_sleep();
#endif
            dispatch_usb_event();
            debug_eusart_send_char();
            toggle_led();
        }
    }

	// (void*) avoids sdcc crash when _DEBUG is defined
    debug("Starting application at %x\n", (void *)application_data.main);
	debug_eusart_flush();

    // init_usb() has to be called by the application
	application_data.main();

    INTCON = 0; // Forbid interrupts
    init_debug();
    debug("Switch back to bootloader\n");

	while(1)
    {
        if((application_data.invalid == 0) &&
           (GET_ACTIVE_CONFIGURATION() > FLASH_CONFIGURATION))
        {
        	// (void*) avoids sdcc crash when _DEBUG is defined
            debug("Starting application at %x\n", (void *)application_data.main);
        	debug_eusart_flush();

        	application_data.main();

            INTCON = 0; // Forbid interrupts
            debug("Switch back to bootloader\n");
        }
		// In debug mode, we want the device to go on with USART
		// So disable sleep mode when USB is suspended
#ifndef _DEBUG
        usb_sleep();
#endif
        dispatch_usb_event();
        debug_eusart_send_char();
        toggle_led();
    }
}
