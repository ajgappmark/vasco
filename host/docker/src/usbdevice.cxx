/*-------------------------------------------------------------------------
  usbdevice.cxx - docker USB classes

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
#include <exception>
#include <usb.h>
#include "config.h"
#include "DataBuffer.h"
#include "usbdevice.h"

#define EP_FLASH_OUT 1
#define EP_FLASH_IN  2

/* In millisecond. Note that with libusb 0.11 on Linux, a timeout of 0 results
 * in a immediate return... */
#define USB_TIMEOUT 5000

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

                c = usb_set_configuration(dh, 2);
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
            //cout << "get sections descriptors\n";
            get_section_descriptors();
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

void USBDevice::erase(void)
{
    for(RangeVector::iterator i = device_mmap.begin(); i != device_mmap.end(); i++)
    {
        if((*i)->flags & FLASH_SECTION_WRITE)
        {
            cout << "erasing section [" << hex << (*i)->begin <<", " << (*i)->end << "]" << endl;
            if((*i)->end - (*i)->begin < 64)
            {
                erase_block((*i)->begin);
            }
            else
            {
                for(long addr = (*i)->begin; addr <= (*i)->end - 63; addr += 64)
                {
                    erase_block(addr);
                }
            }
        }
    }
}

void USBDevice::write(DataBuffer& tab)
{
    for(RangeVector::iterator i = device_mmap.begin(); i != device_mmap.end(); i++)
    {
        if((*i)->flags & FLASH_SECTION_WRITE)
        {
            cout << "writing section [" << hex << (*i)->begin <<", " << (*i)->end << "]" << endl;
            if((*i)->end - (*i)->begin < 32)
            {
                write_block((*i)->begin, tab);
            }
            else
            {
                for(long addr = (*i)->begin; addr <= (*i)->end - 31; addr += 32)
                {
                    write_block(addr, tab);
                }
            }
        }
    }
}

void USBDevice::read(DataBuffer& tab)
{
    for(RangeVector::iterator i = device_mmap.begin(); i != device_mmap.end(); i++)
    {
        if((*i)->flags & FLASH_SECTION_READ)
        {
            cout << "reading section [" << hex << (*i)->begin <<", " << (*i)->end << "]" << endl;
            if((*i)->end - (*i)->begin < 64)
            {
                read_block((*i)->begin, tab);
            }
            else
            {
                for(long addr = (*i)->begin; addr <= (*i)->end - 63; addr += 64)
                {
                    read_block(addr, tab);
                }
            }
        }
    }
}

void USBDevice::reset(void)
{
    char cmd = READ_FLASH_CMD;
    int c;
    
    c = usb_bulk_write(dh, EP_FLASH_OUT, &cmd, sizeof(cmd), USB_TIMEOUT);
    if(c <= 0)
    {
        // Raise exception
        abort();
    }
}

void USBDevice::validate_application(void)
{
}

void USBDevice::erase_block(long address)
{
    int c;
    char erase_bytes[] = {ERASE_FLASH_CMD,0x00,0x00,0x00};

    erase_bytes[1] = address & 0xff;
    erase_bytes[2] = (address >> 8) & 0xff;
    erase_bytes[3] = (address >> 16) & 0xff;
    
//    cout << "erase block " << hex << address << endl;
    c = usb_bulk_write(dh, EP_FLASH_OUT, erase_bytes, sizeof(erase_bytes), USB_TIMEOUT);
    if(c <= 0)
    {
        // Raise exception
        abort();
    }
}

void USBDevice::write_block(long address, DataBuffer& tab)
{
    int c;
    char write_bytes[] = {WRITE_FLASH_CMD,0x00,0x00,0x00,
                          0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, // 8
                          0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, // 16
                          0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, // 24
                          0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff  // 32
                         };
                         
//    cout << "write block " << hex << address << endl;
    bool isBlank = true;

    for(long a = address; a < address + 32; a++)
    {
        if(!tab.isblank(a))
        {
            write_bytes[a - address + 4] = tab[a];
            isBlank = false;
        }
    }
    
    if(isBlank)
    {
        return;
    }
//    cout << " writing for real..." << endl;
    write_bytes[1] = address & 0xff;
    write_bytes[2] = (address >> 8) & 0xff;
    write_bytes[3] = (address >> 16) & 0xff;
    
    c = usb_bulk_write(dh, EP_FLASH_OUT, write_bytes, sizeof(write_bytes), USB_TIMEOUT);
    if(c <= 0)
    {
        // Raise exception
        abort();
    }
}

void USBDevice::read_block(long address, DataBuffer& tab)
{
    int c;
    unsigned char buffer[256];
    char read_bytes[]  = {READ_FLASH_CMD,0x00,0x00,0x00};
    
    read_bytes[1] = address & 0xff;
    read_bytes[2] = (address >> 8) & 0xff;
    read_bytes[3] = (address >> 16) & 0xff;

    c = usb_bulk_write(dh, EP_FLASH_OUT, read_bytes, sizeof(read_bytes), USB_TIMEOUT);
    if(c <= 0)
    {
        // Raise exception
        abort();
    }
    
    c=usb_bulk_read(dh, EP_FLASH_IN, (char*)buffer, sizeof(buffer), USB_TIMEOUT);
    if(c == 64)
    {
        for(long j = 0; j < 64; j++)
        {
            tab[address + j] = buffer[j];
        }
    }
    else
    {
        // Raise an exception
        abort();
    }
    
}

void USBDevice::get_section_descriptors(void)
{
    int c;
    unsigned char buffer[256];
    char cmd = SECTION_DESCRIPTOR_CMD;
    long begin, end;
    char flags;
    
    c = usb_bulk_write(dh, EP_FLASH_OUT, &cmd, sizeof(cmd), USB_TIMEOUT);
    if(c <= 0)
    {
        // Raise exception
        abort();
    }

    c = usb_bulk_read(dh, EP_FLASH_IN, (char*)buffer, sizeof(buffer), USB_TIMEOUT);

    for(int i = 0; i < buffer[0]; i++)
    {
        flags = buffer[i * SECTION_DESCRIPTOR_SIZE + 1];
        begin = buffer[i * SECTION_DESCRIPTOR_SIZE + 2] +
                (buffer[i * SECTION_DESCRIPTOR_SIZE + 3] << 8) +
                (buffer[i * SECTION_DESCRIPTOR_SIZE + 4] << 16);
        end   = buffer[i * SECTION_DESCRIPTOR_SIZE + 5] +
                (buffer[i * SECTION_DESCRIPTOR_SIZE + 6] << 8) +
                (buffer[i * SECTION_DESCRIPTOR_SIZE + 7] << 16);
                
//        cout << "section " << i << " begins at " << hex << begin << " and finish at " << end <<
//                ", flags = " << hex << (int)flags << endl;
        device_mmap.push_back(new Range(flags, begin, end));
    }
}

