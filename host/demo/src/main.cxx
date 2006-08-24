/*-------------------------------------------------------------------------
  main.c - host side PUF demo (change USB device configuration)
  
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
#include <string>
#include <usb.h>
#include <getopt.h>
#include <signal.h>
#include "config.h"
#include "usbdevice.h"

static void help_msg(void)
{
    cout << PACKAGE << " version " << VERSION << endl;
    cout << PACKAGE << " [options] [-c configuration_id]" << endl;
    cout << "Options :\n\t-v vendor_id       : process only devices with this vendor ID" << endl;
    cout <<            "\t-p product_id      : process only devices with this product ID" << endl;
    cout <<            "\t-d device_filename : process only this device" << endl;
    cout <<            "\t-c cfg_id          : set the device configuration to cfg_id (default is 3)" << endl;
    cout <<            "\t-q for quiet operations" << endl;
    cout <<            "\t-h/V displays this message" << endl;
}

int main(int argc, char**argv)
{    
    // arg iterator
    int    i;
    
    // option flags and values
    bool   quiet        = false;
    long   product_id   = 0x0000;
    bool   product_flag = false;
    long   vendor_id    = 0x0000;
    bool   vendor_flag  = false;
    string device_id    = "";
    int    cfg_id       = 3;
    
    // USB busses informations
    struct usb_bus *busses;
    
    // device driver
    USBDevice* device;
    
    while((i = getopt(argc, argv, "v:p:d:qVhc:")) > 0) {
        switch(i) {
        case 'q':
            quiet = true;
            break;
            
        case 'V':
        case 'h':
            help_msg();
            return 0;
            
        case 'p':
            product_id = strtol(optarg, NULL, 16);
            product_flag = true;
            break;
            
        case 'v':
            vendor_id = strtol(optarg, NULL, 16);
            vendor_flag = true;
            break;
            
        case 'd':
            // The device id is in fact the device filename
            // i.e. something like 001, 023, etc. with linux
            device_id = optarg;
            break;
            
        case 'c':
            cfg_id = strtol(optarg, NULL, 10);
            break;
            
        default:
            // unknown option : return with an error
            help_msg();
            return -1;
        }
    }
    
    
    usb_init();
    usb_find_busses();
    usb_find_devices();
    busses = usb_get_busses();
    
    for (struct usb_bus *bus = busses; bus; bus = bus->next)
    {
        struct usb_device *dev;

        for (dev = bus->devices; dev; dev = dev->next)
        {
            /* Look for matching devices */
            if ((!vendor_flag  || (dev->descriptor.idVendor  == vendor_id)) && 
                (!product_flag || (dev->descriptor.idProduct == product_id))) 
            {
                if((device_id == "") || (device_id == dev->filename))
                {
                    // Got one !
                    if(!quiet)
                    {
                        cout << "Change configuration of device " << dev->filename << endl;
                    }
                    
                    try 
                    {
                        device = new USBDevice(dev, cfg_id);
                        delete device;
                    }
                    catch (char const* msg)
                    {
                        cerr << msg << endl; 
                    }
                }
            }
        }
    }
}
