/*-------------------------------------------------------------------------
  usbdevice.h - docker USB accesses

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

#ifndef USBDEVICE_H
#define USBDEVICE_H

using namespace std;

class USBDevice
{
    public:
        USBDevice(struct usb_bus *busses, long vendor, long product);
        ~USBDevice();
        
    private:
        struct usb_dev_handle* dh;
        
    };

    
#endif // USBDEVICE_H
