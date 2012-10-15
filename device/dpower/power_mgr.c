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
#include "power_ep3.h"
#include "usb.h"
#include "application_debug.h"
#include <pic18fregs.h>
#include <adc.h>
#include <stdio.h>

#define PMGR_DEFAULT          0
#define PMGR_READ_TENSION     1
#define PMGR_WAITING_RESET    2
#define PMGR_WAITING_SHUTDOWN 3
#define PMGR_SWITCH_ON        4

static char power_mgr_state;

// Used for shutdown and reset delays
static uint delay;
static uint counter;

// For tension monitoring
static uint tm_period;
static uint tm_counter;
static uint tm_threshold;
static uint tm_init_threshold;
static uchar tm_conv_flag;
static uint tm_measures[10];
static uchar tm_measure_num;
static uchar tm_measure_validity;

void init_power_mgr()
{
    tm_period = 0;
    tm_counter = 0;
    tm_threshold = 0;
    tm_conv_flag = FALSE;
    power_mgr_state = PMGR_DEFAULT;
}

static void pmgr_adc_open()
{
  /* setup channel */
  ADCON0 = 0x14;
  
  /* setup reference and pins. Beware : it disables also other
   * digital I/O (AN0 -> AN4) */
  ADCON1 = 0x09;

  /* setup fosc to RTC */
  ADCON2 = 0xff;
  
  /* enable the A/D module */
  ADCON0bits.ADON = 1;
}

static void pmgr_adc_close()
{
    adc_close();
    // Re-activate digital pins
    ADCON1 = 0x0f;
}

void start_read_tension(void)
{
    // Enable ADC module
    pmgr_adc_open();
    // Begin conversion
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
                int a;
                // Get the result and close the ADC module
                a = adc_read() & 0x3ff;
                pmgr_adc_close();
                
                // Send the result
                debug("send Vbat value\n");
                power_ep2_num_bytes_to_send = 2;
                power_ep2_source_data = (uchar __data *) &a;
                power_prepare_ep2_in();
                power_mgr_state = PMGR_DEFAULT;
            }
            break;
            
        case PMGR_WAITING_RESET:
            counter++;
            if(counter == delay)
            {
                // Shutdown and ask to switch on
                
                switch_power_supply_on(1);
            }
        case PMGR_WAITING_SHUTDOWN:
            counter++;
            if(counter == delay)
            {
                PORTBbits.RB3 = 1; 
                PORTBbits.RB4 = 0;
            }
        case PMGR_SWITCH_ON:
            counter++;
            if(counter == delay)
            {
                PORTBbits.RB3 = 0;
                PORTBbits.RB4 = 1;
            }
        case PMGR_DEFAULT:
            if(tm_period)
            {
                tm_counter++;
                if(tm_period == tm_counter)
                {
                    // Enable ADC module
                    pmgr_adc_open();
                    // Begin conversion
                    adc_conv();
                    tm_counter = 0;
                    tm_conv_flag = TRUE;
                    debug("begin Vbat monitoring\n");
                }
                if(tm_conv_flag && !ADCON0bits.GO)
                {
                    int a;
                    uchar i;
                    
                    // Get the result and close the ADC module
                    a = adc_read() & 0x3ff;
                    pmgr_adc_close();
                    tm_conv_flag = FALSE;

                    // measure filter (sliding window)
                    tm_measure_num++;
                    if(tm_measure_num == 10)
                    {
                        tm_measure_num = 0;
                        tm_measure_validity = TRUE;
                    }
                    tm_measures[tm_measure_num] = a;
                    
                    a = 0;
                    for(i = 0; i < 10; i++)
                    {
                        a += tm_measures[i];
                    }
                    
                    a /= 10;
                    debug(" a=%d\n", a);
                    
                    if(tm_measure_validity && !ep3_send_in_progress)
                    {
                        if(a <= tm_threshold)
                        {
                            uchar alert_msg = 1;
                            debug(" send alert\n");
                            
                            // Histeresys
                            tm_threshold = tm_init_threshold + 1;
                            
                            // Alert
                            power_ep3_num_bytes_to_send = 1;
                            power_ep3_source_data = (uchar __data *) &alert_msg;
                            power_prepare_ep3_in();
                        }
                        else
                        {
                            // Histeresys
                            tm_threshold = tm_init_threshold - 1;
                        }
                    }
                    debug("end Vbat monitoring\n");
                 }
            }
            break;
            
        default:
            power_mgr_state = PMGR_DEFAULT;
            break;
    }
}

void reset_power_supply(uint a_delay)
{
    power_mgr_state = PMGR_WAITING_RESET;
    delay = a_delay * 200;
    counter = 0;
}

void shutdown_power_supply(uint a_delay)
{
    power_mgr_state = PMGR_WAITING_SHUTDOWN;
    delay = a_delay * 200;
    counter = 0;    
}

// period in second
// threshold in (Vdd - Vss) / 1024
void set_battery_tension_alert(uint a_period, uint a_threshold)
{
    tm_period = 200 * a_period;
    tm_init_threshold = a_threshold;
    tm_threshold = tm_init_threshold - 1;
    tm_measure_validity = FALSE;
    tm_measure_num = 0;
    debug("tm_period=%d\n", tm_period);
    debug("tm_threshold=%d\n", tm_threshold);
}

void unset_battery_tension_alert(void)
{
    tm_period = 0;
}

void switch_power_supply_on(uint a_delay)
{
    power_mgr_state = PMGR_SWITCH_ON;
    delay = a_delay * 200;
    counter = 0;    
}
