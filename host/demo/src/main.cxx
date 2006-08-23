/*-------------------------------------------------------------------------
  main.c - demo
  
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

using namespace std;

#include <iostream>
#include <string>
#include <usb.h>
#include <getopt.h>
#include <signal.h>
#include "config.h"
#include "usbdevice.h"

static USBDevice* device;

int main(int argc, char**argv)
{    
    int c, i, a;
    long val;
    bool quiet;
    struct usb_bus *busses;
    long product_id = 0x0001;
    long vendor_id = 0xa5a5;
    int cfg_id = 3;
    struct usb_bus *bus;
    string device_id = "";
    
    quiet = false;
    
    while((i = getopt(argc, argv, "v:p:d:qVc:")) > 0) {
        switch(i) {
        case 'q':
            quiet = true;
            break;
        case 'V':
            cout << PACKAGE << " version " << VERSION << endl;
            return 0;
        case 'p':
            product_id = strtol(optarg, NULL, 16);
            break;
        case 'v':
            vendor_id = strtol(optarg, NULL, 16);
            break;
        case 'd':
            device_id = optarg;
            break;
        case 'c':
            cfg_id = strtol(optarg, NULL, 10);
            break;
        case '?':
        case ':':
        default:;
            return -1;
        }
    }

    usb_init();
    usb_find_busses();
    usb_find_devices();
    
    busses = usb_get_busses();
    
    for (bus = busses; bus; bus = bus->next) {
        struct usb_device *dev;

        for (dev = bus->devices; dev; dev = dev->next) {
            /* Look for Vasco devices */
            if ((dev->descriptor.idVendor == vendor_id) && 
                (dev->descriptor.idProduct == product_id)) 
            {
                // Got one !
                if((device_id == "") || (device_id == dev->filename))
                {
                    cout << "Device " << dev->filename << " matches.\n";
                }
            }
        }
    }
    
    //device = new USBDevice(busses, vendor_id, product_id, cfg_id);



    //delete device;
}
