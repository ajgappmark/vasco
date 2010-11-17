/*-------------------------------------------------------------------------
  flash.c - Program memory flashing process

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

#include "config.h"
#include "common_types.h"
#include <pic18fregs.h>
#include "debug.h"
#include "flash.h"

uint ep2_num_bytes_to_send;
uchar *ep2_source_data;

void write_block(__data uchar *src)
{
    static uchar i;
    debug("write_block\n");

    __asm

    tblrd*-

    __endasm;

    for(i = 0; i < 32; i++)
    {
        TABLAT = *src;
        debug("%uhx ", TABLAT);
        src++;
        __asm

        tblwt+*

        __endasm;
    }
    debug("\n");
    // Beware : when WR is set, TBLPTR have to be inside the 32 byte range to be written
    // so it should be decremented...

    __asm

    bsf     _EECON1, 7 // EEPGD
    bcf     _EECON1, 6 // CFGS
    bsf     _EECON1, 2 // WREN
    bcf     _INTCON, 7 // GIE

    // required erase sequence
    movlw   0x55
    movwf   _EECON2
    movlw   0xaa
    movwf   _EECON2
    bsf     _EECON1, 1 // WR

    // stall here for 2ms

    __endasm;
    debug("write finished\n");
}

void erase_block()
{
    // Erase a 64 bytes block
    __asm
    // address set by the caller

    // Point to flash program memory
    bsf     _EECON1, 7 // EEPGD
    bcf     _EECON1, 6 // CFGS
    bsf     _EECON1, 2 // WREN
    bsf     _EECON1, 4 // FREE
    bcf     _INTCON, 7 // GIE

    // required erase sequence
    movlw   0x55
    movwf   _EECON2
    movlw   0xaa
    movwf   _EECON2
    bsf     _EECON1, 1 // WR

    // stall here for 2ms

    __endasm;
}
