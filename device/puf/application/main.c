/*-------------------------------------------------------------------------
  main.c - Application main function

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

#include <pic18fregs.h>
#include "application_config.h"
#include "common_types.h"
#include "application_debug.h"
#include "boot_iface.h"
#include "usb.h"

#define ftoggle_A0() { PORTAbits.AN0 = !PORTAbits.AN0; }

static uchar T0Counter = 8;

/******************************************************************/

// beware : this is not a C main function, but the application
// entry point called from the boot.
// Nevertheless, static initialization is ensured by the
// bootloader.
void application_main(void)
{

    PORTA = 0x01;

    // Reset the Timer0 value
    TMR0H = 0;
    TMR0L = 0;

    // Configure the Timer0 and unmask ITs
    T0CON = 0x80 | 0x05; // TMR0ON, 16bits, CLKO, PSA on, 1:256
    INTCONbits.TMR0IE = 1;
    INTCONbits.GIE = 1;

    init_debug();
    debug("Init application\n");
	debug("Init USB\n");
	debug_eusart_flush();
	init_usb();

    while((GET_ACTIVE_CONFIGURATION() != FLASH_CONFIGURATION))
    {
        usb_sleep();
        dispatch_usb_event();
        debug_eusart_send_char();
   }
    debug_eusart_flush();
}

/* Interrupt vectors */
HIGH_PRIORITY_ISR_PRAGMA
void high_priority_isr(void) __interrupt
{
    if(INTCONbits.TMR0IF)
    {
    	T0Counter--;
    	if(T0Counter == 0)
		{
			ftoggle_A0();
			T0Counter = 8;
			debug("Toggle\n");
		}
    	else if(T0Counter == 7)
		{
			ftoggle_A0();
		}
		INTCONbits.TMR0IF = 0;
    }
}

LOW_PRIORITY_ISR_PRAGMA
void low_priority_isr(void) __interrupt
{
}

