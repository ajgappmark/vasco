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
#include "power_mgr.h"
#include "sequencer.h"
#include "timer2.h"
#include <stdio.h>

#define ftoggle_A0() { PORTAbits.AN0 = !PORTAbits.AN0; }


/******************************************************************/

// beware : this is not a C main function, but the application
// entry point called from the boot.

// picon EP
const uchar picon_ep = 3;

// RT sequencer counter
static volatile uint counter;
// RT sequencer release point flag (raised when a period begins) 
static volatile uchar seq_flag;

void application_main(void) 
{
    PORTAbits.AN0 = 1;
    
    // Init picon
    init_debug();
    
    // Switch USB management to interrupt
    PIE2bits.USBIE = 1;

    // Prepare Analogic input
    CMCON  = 0x07;
    TRISE  = 0x07;
    
    // Program timer2 for 5ms period
    timer2_set_period(250);
    timer2_set_control(TIMER2_PRESCALER_16, TIMER2_POSTSCALER(15), TIMER2_ON);
    PIR1bits.TMR2IF = 0;
    PIE1bits.TMR2IE = 1;
    
    // Enable global and peripheral interrupts 
    INTCON = 0xc0;

    // Init sequencer counter
    counter = 0;
    
    debug("Power supply manager initialized\n");  

    while(usb_active_cfg > 2)
    {
        // Wait for event (timer2 or usb)
        usb_sleep();
        
        // Release point reached ?
        if(seq_flag)
        {
            seq_flag = 0;
            rt_sequencer(counter);
        }
    }
    
    // Interrupts are disabled in the bootloader
    // So no worry
    PORTAbits.AN0 = 0;
}

/* Interrupt vectors */
#pragma code high_priority_isr 0x2020
void high_priority_isr(void) interrupt
{
    // Process USB interrupts
    if(PIR2bits.USBIF)
    {
        dispatch_usb_event();
        UIRbits.SOFIF = 0;
        UIRbits.URSTIF = 0;
        PIR2bits.USBIF = 0;
        UEIR = 0;
    }
    
    // Process timer2 interrupts
    if(PIR1bits.TMR2IF)
    {
        PIR1bits.TMR2IF = 0;
        // Switch on interrupt tail and increment RT counter
        seq_flag = 1;
        counter++;
    }
}

#pragma code low_priority_isr 0x4000
void low_priority_isr(void) interrupt
{
}

