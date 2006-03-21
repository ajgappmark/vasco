/*-------------------------------------------------------------------------
  main.c - Application main function

             (c) 2006 Pierre Gaufillet <pierre.gaufillet@magic.fr> 

   This library is free software; you can redistribute it and/or modify it
   under the terms of the GNU Library General Public License as published by the
   Free Software Foundation; either version 2, or (at your option) any
   later version.
   
   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Library General Public License for more details.
   
   You should have received a copy of the GNU Library General Public License
   along with this program; if not, write to the Free Software
   Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
-------------------------------------------------------------------------*/

#include <pic18fregs.h>
#include "common_types.h"
#include "debug.h"
#include "boot_iface.h"


/******************************************************************/

// beware : this is not a C main function, but the application
// entry point called from the boot.

void application_main(void) 
{
    static unsigned long count;
    
    PORTA = 0x01;
    init_debug();
    debug("init application\n");

    count = 100000;    

    while(1)
    {
        dispatch_usb_event();

        count--;
        if(!count)
        {
            toggle_A0();
            count = 100000;
        }
    }
}
