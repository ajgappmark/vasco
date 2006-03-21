/*-------------------------------------------------------------------------
  usbdevice.cxx - docker USB classes

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

using namespace std;

#include <iostream>
#include <usb.h>
#include "config.h"
#include "usbdevice.h"


USBDevice::USBDevice(struct usb_bus *busses, long vendor, long product)
{
    struct usb_bus *bus;
    int c;
    
    dh = NULL;
    for (bus = busses; bus; bus = bus->next) {
        struct usb_device *dev;

        for (dev = bus->devices; dev; dev = dev->next) {
            /* Look for Vasco devices */
            if ((dev->descriptor.idVendor == vendor) && 
                (dev->descriptor.idProduct == product)) 
            {
                // Got one !
//                cout << "device found\n";
                dh = usb_open(dev);
                if(!dh)
                {
                    // raise exception
                    abort();
                }

                c = usb_set_configuration(dh, 3);
                if(c)
                {
                    // raise exception
                    abort();
                }

                c = usb_claim_interface(dh, 0);
                if(c)
                {
                    // raise exception
                    abort();
                }

                break;
            }
        }
        if(dh)
        {
            break;
        }
    }
}

USBDevice::~USBDevice()
{
    if(dh)
    {
        usb_close(dh);
    }
}

