/*-------------------------------------------------------------------------
  usbdevice.h - USB accesses

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

// Power manager commands
#define READ_BATTERY_TENSION_CMD        1
#define RESET_POWER_SUPPLY_CMD          2
#define SHUTDOWN_POWER_SUPPLY_CMD       3
#define SET_BATTERY_TENSION_ALERT_CMD   4
#define UNSET_BATTERY_TENSION_ALERT_CMD 5

#define USB_TIMEOUT 5000

class USBDevice
{
    public:
        USBDevice(struct usb_device *dev);
        ~USBDevice();
        string* str_interrupt_read(int ep_num);
        char*   byte_interrupt_read(int ep_num);
        bool    bound(void) { return dh != NULL; }
        void    claim_interface(int int_num);
        bool    find_interface(int int_num, int subclass_id);
        void    reset_power_supply(int ep_num, long delay);
        float   read_Vbat(int ep_num);
        void    wait_alert(int ep_num);
        void    set_alert_threshold(unsigned int period, unsigned int threshold, int ep_num);               
    private:
        struct usb_dev_handle* dh;
        unsigned char interface[16];
        unsigned char ep[16];
        
    };

    
#endif // USBDEVICE_H
