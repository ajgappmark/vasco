/*-------------------------------------------------------------------------
  ep2.c - USB endpoint 2 callbacks

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

/* $Id$ */

#include "ep2.h"
#include "usb.h"
#include "debug.h"
#include "flash.h"
#include <pic18fregs.h>

static uchar last_send_was_null;

#pragma udata usb_buf ep2_InBuffer
volatile uchar ep2_InBuffer[EP2_BUFFER_SIZE];

void ep2_init(void)
{
    // Set DAT1 so that the first call to prepare_ep2_in
    // will switch to DAT0, which is correct for the first
    // message
    EP_IN_BD(2).Stat.uc = BDS_UCPU | BDS_DAT1 | BDS_DTSEN;
    UEP2 = EPHSHK_EN | EPINEN_EN | EPCONDIS_EN;       // Init EP2 as an IN EP
}

void prepare_ep2_in(void)
{
    last_send_was_null = (ep2_num_bytes_to_send < EP2_BUFFER_SIZE);
    EP_IN_BD(2).Cnt = ep2_num_bytes_to_send;
    EP_IN_BD(2).ADR = (uchar __data *)&ep2_InBuffer;
    fill_in_buffer(2, &ep2_source_data, EP2_BUFFER_SIZE, &ep2_num_bytes_to_send);
    if(EP_IN_BD(2).Stat.DTS == 0)
    {
        EP_IN_BD(2).Stat.uc = BDS_USIE | BDS_DAT1 | BDS_DTSEN;
    }
    else
    {
        EP_IN_BD(2).Stat.uc = BDS_USIE | BDS_DAT0 | BDS_DTSEN;
    }
}

void ep2_in(void)
{
    if((ep2_num_bytes_to_send == 0) && last_send_was_null)
    {
        // There is nothing more to send, so keep
        // the EP2 buffer under the CPU responsability
        return;
    }
    last_send_was_null = (ep2_num_bytes_to_send < EP2_BUFFER_SIZE);
    EP_IN_BD(2).Cnt = ep2_num_bytes_to_send;
    fill_in_buffer(2, &ep2_source_data, EP2_BUFFER_SIZE, &ep2_num_bytes_to_send);
    if(EP_IN_BD(2).Stat.DTS == 0)
    {
        EP_IN_BD(2).Stat.uc = BDS_USIE | BDS_DAT1 | BDS_DTSEN;
    }
    else
    {
        EP_IN_BD(2).Stat.uc = BDS_USIE | BDS_DAT0 | BDS_DTSEN;
    }
}
