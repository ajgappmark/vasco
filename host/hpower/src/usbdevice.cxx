/*-------------------------------------------------------------------------
  usbdevice.cxx - host side power manager USB classes

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
#include <usb.h>
#include "config.h"
#include "usbdevice.h"

void USBDevice::claim_interface(int int_num) 
{
    int c;
    // claim this interface
    c = usb_claim_interface(dh, interface[int_num]);
    if(c)
    {
        usb_close(dh);
        throw "Device interface unavailable.";
    }
}

bool USBDevice::find_interface(int int_num, int subclass_id)
{
    int c;
    unsigned char cfg_id;
    unsigned char number_of_interfaces;
    unsigned char buffer[65536];
    unsigned char *b;
    
    // get the current configuration
    c = usb_control_msg(dh, USB_ENDPOINT_IN | USB_TYPE_STANDARD | USB_RECIP_DEVICE,
                    USB_REQ_GET_CONFIGURATION, 
                    0,
                    0, 
                    (char*) &cfg_id, 
                    1, 
                    1000);
    if(c < 0)
    {
        usb_close(dh);
        throw "Unable to read current configuration id.";
    }
              
    // get the configuration descriptor and the number of interfaces
    c = usb_get_descriptor(dh, 
                           USB_DT_CONFIG,
                           cfg_id - 1,
                           &buffer,
                           9);
    if(c < 0)
    {
        usb_close(dh);
        throw "Unable to get configuration descriptors.";
    }
    
    c = usb_get_descriptor(dh, 
                           USB_DT_CONFIG,
                           cfg_id - 1,
                           &buffer,
                           buffer[2] + 256 * buffer[3]);
    if(c < 0)
    {
        usb_close(dh);
        throw "Unable to get configuration descriptors.";
    }
    
    number_of_interfaces = buffer[4];
    
    b = &(buffer[buffer[0]]);
       
    // extract interface and endpoints descriptors 
    // for each interface
    ep[int_num] = 0;
    for (unsigned char i = 0; i < number_of_interfaces; i++)
    {
        unsigned char nb_ep;
        
        // if interface type is power manager
        if((b[5] == 0xff) && (b[6] == subclass_id))
        {
            // This is a power manager interface
            // get ep number and interface number
            interface[int_num] = i;
            ep[int_num] = b[b[0] + 2] & 0x0f;
            claim_interface(int_num);
            
            cout << "Found interface type " << subclass_id << " at #" << (int)interface[int_num] << ", EP #" << (int) ep[int_num] << endl;            
            break;
        }
        // Go to next interface descriptor
        nb_ep = b[4];
        b = &(b[b[0]]);
        for(unsigned char j = 0; j < nb_ep; j++)
        {
            b = &(b[b[0]]);
        }
        
    }

    if (!ep[int_num])
    {
        throw "This device has no interface of this type.";
    }
}


USBDevice::USBDevice(struct usb_device *dev)
{
    int c;
    
    dh = usb_open(dev);
    if(!dh)
    {
        throw "Unable to open device.";
    } 
    
    c = usb_set_configuration(dh, 3);
    if(c)
    {
        usb_close(dh);
        throw "Impossible to change the device configuration.";
    }

}

USBDevice::~USBDevice()
{
    usb_close(dh);
}

string * USBDevice::str_interrupt_read(int ep_num)
{
    char tmp[255];
    int c;
    
    // No timeout (0) because if nothing is received, the device
    // is closed and picon aborts.
    c = usb_interrupt_read(dh, ep[ep_num], tmp, 255, 0);
    if(c >= 0)
    {    
        tmp[c] = '\0';
        return new string(tmp);
    }
    else
    {
        throw "Unable to read interrupt endpoint.";
    }
}

char* USBDevice::byte_interrupt_read(int ep_num)
{
    char tmp[255];
    int c;
    
    // No timeout (0) because if nothing is received, the device
    // is closed and picon aborts.
    c = usb_interrupt_read(dh, ep[ep_num], tmp, 255, 0);
    if(c > 0)
    {
        char *buf = new char[c];
        for(int i; i < c; i++) 
        {
            buf[i] = tmp[i];
        }
        
        return buf;
    }
    else if(c == 0)
    {
        return NULL;
    }
    else
    {
        throw "Unable to read interrupt endpoints.";
    }
}

void USBDevice::reset_power_supply(int ep_num, long delay)
{
    int c;
    char buffer[] = {RESET_POWER_SUPPLY_CMD,0x00,0x00,0x00,0x00};

    buffer[1] = delay & 0xff;
    buffer[2] = (delay >> 8) & 0xff;
    buffer[3] = (delay >> 16) & 0xff;
    buffer[4] = (delay >> 24) & 0xff;
    
    c = usb_bulk_write(dh, ep[ep_num], buffer, sizeof(buffer), USB_TIMEOUT);
    if(c <= 0)
    {
        // Raise exception
        throw "I/O error on device erase command.";
    }
}

void USBDevice::set_alert_threshold(unsigned int period, unsigned int threshold, int ep_num)
{
    int c;
    char buffer[] = {SET_BATTERY_TENSION_ALERT_CMD, period & 0xff, (period >> 8) & 0xff, threshold & 0xff, (threshold >> 8) & 0xff};

    c = usb_interrupt_write(dh, ep[ep_num], buffer, sizeof(buffer), USB_TIMEOUT);
    if(c < 0)
    {
        // Raise exception
        throw "I/O error on set battery threshold command.";
    }
}

float USBDevice::read_Vbat(int ep_num)
{
    int c;
    unsigned char tmp[2];
    char buffer[] = {READ_BATTERY_TENSION_CMD};

    c = usb_interrupt_write(dh, ep[ep_num], buffer, sizeof(buffer), 0/*USB_TIMEOUT*/);
    if(c <= 0)
    {
        cerr << endl << "c=" << c << endl << usb_strerror() << endl;
        // Raise exception
        throw "I/O error on read Vbat command.";
    }
    
    c = usb_interrupt_read(dh, ep[ep_num]+1, (char*)tmp, 2, 0);
    if(c > 0)
    {
        int a;
        
        a = tmp[0] + (tmp[1] << 8);
        return a * 5.0 / 1024.0;
    }
    else
    {
        throw "Unable to read Vbat.";
    }
}

void USBDevice::wait_alert(int ep_num)
{
    int c;
    unsigned char tmp[1];

    c = usb_interrupt_read(dh, ep[ep_num]+2, (char*)tmp, 1, 0);
    if(c > 0)
    {
        return;
    }
    else
    {
        throw "Error waiting for battery threshold alert.";
    }
    
}
