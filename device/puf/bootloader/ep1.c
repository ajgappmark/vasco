/*-------------------------------------------------------------------------
  ep1.c - USB endpoint 1 callbacks

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

#include "ep1.h"
#include "ep2.h"
#include "usb.h"
#include "debug.h"
#include "flash.h"
#include <pic18fregs.h>
#include <delay.h>


#pragma udata usb_buf ep1_OutBuffer
volatile uchar ep1_OutBuffer[EP1_BUFFER_SIZE];

void ep1_init(void)
{
    EP_OUT_BD(1).Cnt = EP1_BUFFER_SIZE;
    EP_OUT_BD(1).ADR = (uchar __data *)&ep1_OutBuffer;
    EP_OUT_BD(1).Stat.uc = BDS_USIE | BDS_DAT0 | BDS_DTSEN;
    UEP1 = EPHSHK_EN | EPOUTEN_EN | EPCONDIS_EN;       // Init EP1 as an OUT EP
}

void ep1_out(void)
{
    if(EP_OUT_BD(1).Cnt >= 1)
    {
        switch(ep1_OutBuffer[0])
        {
            case ERASE_FLASH_CMD:
                debug("ERASE_FLASH_CMD\n");
                TBLPTRL = ep1_OutBuffer[1];
                TBLPTRH = ep1_OutBuffer[2];
                TBLPTRU = ep1_OutBuffer[3];
                erase_block();
                break;
            case WRITE_FLASH_CMD:
                debug("WRITE_FLASH_CMD\n");
                TBLPTRL = ep1_OutBuffer[1];
                TBLPTRH = ep1_OutBuffer[2];
                TBLPTRU = ep1_OutBuffer[3];
                write_block((__data uchar *)&(ep1_OutBuffer[4]));
                break;
            case READ_FLASH_CMD:
                debug("READ_FLASH_CMD\n");
                ep2_num_bytes_to_send = EP2_BUFFER_SIZE;
                // TODO: Use a Pointer union to set that
                ep2_source_data = (uchar __code *) (ep1_OutBuffer[1] +
                    ((long) ep1_OutBuffer[2] << 8) +
                    ((long) ep1_OutBuffer[3] << 16));
                prepare_ep2_in();
                break;
            case VALID_APPLICATION_CMD:
                debug("VALID_APPLICATION_CMD\n");
                break;
            case RESET_CMD:
                debug("RESET_CMD\n");
                delay10ktcy(10);
                Reset();
                break;
            case SECTION_DESCRIPTOR_CMD:
                debug("SECTION_DESCRIPTOR_CMD\n");
                ep2_num_bytes_to_send = sizeof(section_descriptor);
                ep2_source_data = (uchar __code *) section_descriptor;
                prepare_ep2_in();
                break;

            default:
                debug("unknown command\n");
                // Raise an error
                EP_OUT_BD(1).Cnt = EP1_BUFFER_SIZE;
                EP_OUT_BD(1).ADR = (uchar __data *)&ep1_OutBuffer;
                EP_OUT_BD(1).Stat.uc = BDS_USIE | BDS_BSTALL;
                break;
        }
        EP_OUT_BD(1).Cnt = EP1_BUFFER_SIZE;
        if(EP_OUT_BD(1).Stat.DTS == 0)
        {
            EP_OUT_BD(1).Stat.uc = BDS_USIE | BDS_DAT1 | BDS_DTSEN;
        }
        else
        {
            EP_OUT_BD(1).Stat.uc = BDS_USIE | BDS_DAT0 | BDS_DTSEN;
        }
    }
    else // Raise an error
    {
        EP_OUT_BD(1).Cnt = EP1_BUFFER_SIZE;
        EP_OUT_BD(1).ADR = (uchar __data *)&ep1_OutBuffer;
        EP_OUT_BD(1).Stat.uc = BDS_USIE | BDS_BSTALL;
    }
}
