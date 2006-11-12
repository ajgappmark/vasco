/*-------------------------------------------------------------------------
  power_mgr.c - Power supply manager functions

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

#include "power_mgr.h"
#include "power_ep2.h"
#include "usb.h"
#include "debug.h"
#include <pic18fregs.h>
#include <adc.h>
#include <stdio.h>

static char power_mgr_state;
#define PMGR_DEFAULT          0
#define PMGR_READ_TENSION     1
#define PMGR_WAITING_RESET    2
#define PMGR_WAITING_SHUTDOWN 3

static void pmgr_adc_open()
{
  /* setup channel */
  ADCON0 = 0x14;
  /* setup reference and pins */
  ADCON1 = 0x09;

  /* setup fosc */
  ADCON2 = 0xff;
  
  /* enable the A/D module */
  ADCON0bits.ADON = 1;
}

void start_read_tension(void)
{
    pmgr_adc_open();
    adc_conv();
    power_mgr_state = PMGR_READ_TENSION;
}

void power_supply_mgr(void)
{
    switch(power_mgr_state)
    {
        case PMGR_READ_TENSION:
            if(!ADCON0bits.GO) // Is the current conversion finished ?
            {
                int a = adc_read() & 0x3ff;
                adc_close();
                power_ep2_num_bytes_to_send = 2;
                power_ep2_source_data = (uchar __data *) &a;
                power_prepare_ep2_in();
                power_mgr_state = PMGR_DEFAULT;
            }
            break;
            
        case PMGR_DEFAULT:
            break;
            
        default:
            power_mgr_state = PMGR_DEFAULT;
            break;
    }
}

void reset_power_supply(unsigned int delay)
{
    power_mgr_state = PMGR_WAITING_RESET;
    
}

void shutdown_power_supply(unsigned int delay)
{
    power_mgr_state = PMGR_WAITING_SHUTDOWN;
    
}

void set_battery_tension_alert(unsigned int period, unsigned int threshold)
{
}

void unset_battery_tension_alert(void)
{
}

void switch_power_supply_on(unsigned int delay)
{
}
