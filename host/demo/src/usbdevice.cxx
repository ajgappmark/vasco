/*-------------------------------------------------------------------------
  usbdevice.cxx - USB device driver

             (c) 2006 Pierre Gaufillet <pierre.gaufillet@magic.fr> 

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
-------------------------------------------------------------------------*/

/* $Id$ */

using namespace std;

#include <iostream>
#include <usb.h>
#include "config.h"
#include "usbdevice.h"


USBDevice::USBDevice(struct usb_device *dev, int cfg)
{
    int c;
    
    dh = usb_open(dev);
    if(!dh)
    {
        throw "Unable to open device.";
    }

    c = usb_set_configuration(dh, cfg);
    if(c)
    {
        usb_close(dh);
        dh = NULL;
        throw "Impossible to change the device configuration.";
    }

    c = usb_claim_interface(dh, 0);
    if(c)
    {
        usb_close(dh);
        dh = NULL;
        throw "Device interface 0 unavailable.";
    }
}

USBDevice::~USBDevice()
{
    if(dh)
    {
        usb_close(dh);
        dh = NULL;
    }
}

