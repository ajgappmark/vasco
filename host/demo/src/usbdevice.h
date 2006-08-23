/*-------------------------------------------------------------------------
  usbdevice.h - docker USB accesses

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

#ifndef USBDEVICE_H
#define USBDEVICE_H

using namespace std;

class USBDevice
{
    public:
        USBDevice(struct usb_device *dev, int cfg);
        ~USBDevice();
        
    private:
        struct usb_dev_handle* dh;
        
    };

    
#endif // USBDEVICE_H
