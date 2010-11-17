/*-------------------------------------------------------------------------
  usb.c - Main USB functions

   Copyright 2005-2010 Pierre Gaufillet <pierre.gaufillet@magic.fr>

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

#include <pic18fregs.h>
#include "usb.h"

/* Buffer descriptors Table */
volatile BufferDescriptorTable __at (0x400) ep_bdt[32];

#pragma code dummy_function 0x500
void dummy_function(void)
{
    ep_bdt[0].Cnt; // makes the compiler happy !
}
