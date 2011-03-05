/*-------------------------------------------------------------------------
  debug.h - Debug functions and macros

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

#ifndef APPLICATION_DEBUG_H_
#define APPLICATION_DEBUG_H_

#ifdef _DEBUG

#include <stdio.h>

#define init_debug() {\
    stdout = STREAM_USER; \
}

#define debug(format, ...) printf(format, ## __VA_ARGS__)
#define toggle_A0() { PORTAbits.AN0 = !PORTAbits.AN0; }

uchar debug_eusart_send_char();
void debug_eusart_flush();

#else

#define init_debug()
#define debug(x, ...)
#define toggle_A0()
#define debug_eusart_send_char()
#define debug_eusart_flush()

#endif

#endif /*APPLICATION_DEBUG_H_*/
