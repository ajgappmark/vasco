/*-------------------------------------------------------------------------
  debug.c - Debug functions

             (c) 2009 Pierre Gaufillet <pierre.gaufillet@magic.fr>

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

#ifdef _DEBUG

#include <pic18fregs.h>
#include <usart.h>
#include "debug.h"
#include "config.h"

static uchar* bottom;         // Point to the next char to be sent
static uchar* top;            // Point to the first free char in the buffer
static uint num_bytes;       // Number of bytes to be send (circular)
static const uint eusart_buffer_size = EUSART_BUFFER_SIZE;
static uchar eusart_in_buffer[EUSART_BUFFER_SIZE];

// EUSART clock configuration
// BRGH = low, BRG16 = 0
// 77 -> 9600, 5/6 -> 115200, 12 -> 57600
// 20 -> 38400
// BRGH = high, BRG16 = 1
// 103 -> 115200
// 51  -> 230400

void init_debug()
{
    usart_open(USART_ASYNCH_MODE &
               USART_EIGHT_BIT &
               USART_BRGH_HIGH &
               USART_TX_INT_ON &
               USART_RX_INT_OFF, 103);

    // usart_open does not know how to set BRG16 flag...
    BAUDCONbits.BRG16 = 1;

    num_bytes = 0;
    top       = eusart_in_buffer;
    bottom    = eusart_in_buffer;
    stdout = STREAM_USER;
}

uchar debug_eusart_send_char()
{
	if((num_bytes > 0) && PIR1bits.TXIF)
	{
    	TXREG = *bottom;

		bottom++;
		num_bytes--;

		if(bottom >= (eusart_in_buffer + eusart_buffer_size))
	    {
	        // cycling the buffer
	        bottom = eusart_in_buffer;
	    }
	}
	return num_bytes;
}

void debug_eusart_flush()
{
	while(debug_eusart_send_char());
}

void putchar(char c) __wparam
{
    if(top >= (eusart_in_buffer + eusart_buffer_size))
    {
        top = eusart_in_buffer;
    }

    if((top == bottom) && (num_bytes != 0))
    {
        // Buffer full

    	return;
    }

    *top = c;
    top++;
    num_bytes++;
}

#endif

