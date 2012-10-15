/*-------------------------------------------------------------------------
  power_ep3.c - USB endpoint 3 callbacks

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

#include "boot_iface.h"
#include "power_ep3.h"
#include "usb.h"
#include "application_debug.h"
#include <pic18fregs.h>

static uchar last_send_was_null;

#pragma udata usb_buf power_ep3_InBuffer
volatile uchar power_ep3_InBuffer[POWER_EP3_BUFFER_SIZE];

uint power_ep3_num_bytes_to_send;
uchar *power_ep3_source_data;
uchar ep3_send_in_progress;     // TRUE when the buffer is being sent

void power_ep3_init(void)
{
    debug("power_ep3_init\n");
    ep3_send_in_progress = FALSE;
    
    // Set DAT1 so that the first call to prepare_ep3_in
    // will switch to DAT0, which is correct for the first
    // message
    EP_IN_BD(3).Stat.uc = BDS_UCPU | BDS_DAT1 | BDS_DTSEN;
    UEP3 = EPHSHK_EN | EPINEN_EN | EPCONDIS_EN;       // Init EP3 as an IN EP
}

void power_prepare_ep3_in(void)
{
    debug("power_prepare_ep3_in\n");
    ep3_send_in_progress = TRUE;
    last_send_was_null = (power_ep3_num_bytes_to_send < POWER_EP3_BUFFER_SIZE);
    EP_IN_BD(3).Cnt = power_ep3_num_bytes_to_send;
    EP_IN_BD(3).ADR = (uchar __data *)&power_ep3_InBuffer;
    fill_in_buffer(3, &power_ep3_source_data, POWER_EP3_BUFFER_SIZE, &power_ep3_num_bytes_to_send);
    if(EP_IN_BD(3).Stat.DTS == 0)
    {
        EP_IN_BD(3).Stat.uc = BDS_USIE | BDS_DAT1 | BDS_DTSEN;
    }
    else
    {
        EP_IN_BD(3).Stat.uc = BDS_USIE | BDS_DAT0 | BDS_DTSEN;
    }
}

void power_ep3_in(void)
{
    debug("power_ep3_in %d\n", (uint) power_ep3_num_bytes_to_send);
    if((power_ep3_num_bytes_to_send == 0) && last_send_was_null)
    {
        // There is nothing more to send, so keep
        // the EP3 buffer under the CPU responsability
        debug("eof\n");
        ep3_send_in_progress = FALSE;
        return;
    }
    last_send_was_null = (power_ep3_num_bytes_to_send < POWER_EP3_BUFFER_SIZE);
    EP_IN_BD(3).Cnt = power_ep3_num_bytes_to_send;
    fill_in_buffer(3, &power_ep3_source_data, POWER_EP3_BUFFER_SIZE, &power_ep3_num_bytes_to_send);
    if(EP_IN_BD(3).Stat.DTS == 0)
    {
        EP_IN_BD(3).Stat.uc = BDS_USIE | BDS_DAT1 | BDS_DTSEN;
    }
    else
    {
        EP_IN_BD(3).Stat.uc = BDS_USIE | BDS_DAT0 | BDS_DTSEN;
    }
}
