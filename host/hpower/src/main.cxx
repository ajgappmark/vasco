/*-------------------------------------------------------------------------
  main.c - host side power manager
  
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
#include <pthread.h>
#include "config.h"
#include "usbdevice.h"

// device driver
USBDevice* device;
pthread_mutex_t mutex;
    
static void help_msg(void)
{
    cout << PACKAGE << " version " << VERSION << endl;
    cout << PACKAGE << " [options] [-c configuration_id]" << endl;
    cout << "Options :\n\t-v vendor_id       : process only devices with this vendor ID" << endl;
    cout <<            "\t-p product_id      : process only devices with this product ID" << endl;
    cout <<            "\t-d device_filename : process only this device" << endl;
    cout <<            "\t-h/V displays this message" << endl;
}

void* read_picon(void*nada)
{
    try 
    {
        string *str;
        while(device->bound())
        {
            str = device->str_interrupt_read(0);
            pthread_mutex_lock(&mutex);
            cout << *str;
            cout.flush();
            pthread_mutex_unlock(&mutex);
            delete str;
        }
    }
    catch (char const* msg)
    {
        cerr << msg << endl; 
    }
}

void* wait_alert(void*nada)
{
    try 
    {
        sleep(2);
        pthread_mutex_lock(&mutex);
        cout << "Setting low battery alert threshold : ";
        cout.flush();
        device->set_alert_threshold(1, (unsigned int) ((4.65 * 1024) / 5), 1);
        cout << "done" << endl << "Waiting now for low battery alert." << endl;
        pthread_mutex_unlock(&mutex);
    }
    catch (char const* msg)
    {
        cerr << msg << endl; 
    }
        while(device->bound())
        {
            try 
            {
                device->wait_alert(1);
                pthread_mutex_lock(&mutex);
                cout << "Low battery alert received." << endl;
                cout.flush();
                pthread_mutex_unlock(&mutex);
            }
            catch (char const* msg)
            {
                cerr << msg << endl; 
            }
        }
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
    
    // USB busses informations
    struct usb_bus *busses;
    
    while((i = getopt(argc, argv, "v:p:d:Vh")) > 0) {
        switch(i) {
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
                        cout << "Connected to device " << dev->filename << endl;
                    }
                    
                    try 
                    {
                        string *str;
                        
                        device = new USBDevice(dev);
                        device->find_interface(0, 1);
                        device->find_interface(1, 2);
                        pthread_mutex_init(&mutex, NULL);
                        pthread_create(new pthread_t(), NULL, read_picon, NULL);
                        pthread_create(new pthread_t(), NULL, wait_alert, NULL);
                        while(device->bound())
                        {
                            sleep(1);
                            pthread_mutex_lock(&mutex);
                            try 
                            {
                                cout << "Vbat=" << device->read_Vbat(1) << "V" << endl;
                                cout.flush();
                            }
                            catch (char const* msg)
                            {
                                cerr << msg << endl; 
                            }
                            pthread_mutex_unlock(&mutex);
                        }
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
