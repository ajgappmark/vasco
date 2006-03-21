/*-------------------------------------------------------------------------
  main.c - gamma-upload main function

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
#include <exception>
#include <usb.h>
#include <stdio.h>
#include <getopt.h>
#include <signal.h>
#include "config.h"
#include "DataBuffer.h"
#include "HexFile.h"
#include "usbdevice.h"

static USBDevice* device;

static int usage(void) {
    int i;

    cerr << 
        "Usage:\n" \
        "  " PACKAGE " [options] command [filename]\n"
        "\n" \
        "Options:\n" \
        "  -V            Print the version of Odyssey and exit\n" \
        "  -p hexnum     USB product id\n" \
        "  -v hexnum     USB vendor id\n" \
        "\n" \
        "Commands: blank, read, verify, write\n";
    return -1;
}

static void sighandler(int sig) {
    delete device;
    cerr << "Caught signal " << sig << ".\n";
    exit(-1);
}

int main(int argc, char**argv)
{    
    int c, i, a;
    long val;
    bool quiet;
    struct usb_bus *busses;
    string cmd;
    long product_id = 0x0001;
    long vendor_id = 0xa5a5;
    
    quiet = false;
    
    while((i = getopt(argc, argv, "v:p:qV")) > 0) {
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
        case '?':
        case ':':
        default:;
            return usage();
        }
    }

    if(optind == argc) {
        cerr << argv[0] << "not enough arguments.\n";
        return usage();
    }
    
    

    /* Catch some signals to properly shut down the hardware */
    signal(SIGHUP, sighandler);
    signal(SIGINT, sighandler);
    signal(SIGQUIT, sighandler);
    signal(SIGPIPE, sighandler);
    signal(SIGTERM, sighandler);
        
    usb_init();
    usb_find_busses();
    usb_find_devices();
    
//    cout << "init USB\n";
    busses = usb_get_busses();
//    cout << "init device\n";
    // Look for device
    device = new USBDevice(busses, vendor_id, product_id);

    if(!strcmp(argv[optind], "read"))
    {
        DataBuffer buf(8);
        HexFile *hf;

        optind++;
        if(optind == argc) {
            cerr << argv[0] << "not enough arguments.\n";
            return usage();
        }

        device->read(buf);
        
        try {
            /* Open the hex file */
            hf = new HexFile_ihx8(argv[optind]);
        } catch(std::exception& e) {
            cerr << argv[0] << " : " << e.what();
            return -1;
        }
    
        try {
            /* Get the device memory map so we know what parts of the buffer
             * are valid and save those parts to the hex file. */
            for(USBDevice::RangeVector::iterator n = device->device_mmap.begin(); n != device->device_mmap.end(); n++)
            {            
                if((*n)->flags & FLASH_SECTION_READ)
                {
                    hf->write(buf, (*n)->begin, ((*n)->end - (*n)->begin) + 1);
                }
            }
        } catch(std::exception& e) {
            delete hf;
            cerr << argv[0] << " : " << e.what();
            return 1;
        }
        delete hf;
    }
    else if(!strcmp(argv[optind], "write"))
    {
        optind++;
        if(optind == argc) {
            cerr << argv[0] << "not enough arguments.\n";
            return usage();
        }
        
        // Load the HEX file
        DataBuffer buf(8);
        try {
            /* Read the hex file into the data buffer */
            HexFile *hf = HexFile::load(argv[optind]);
    
            hf->read(buf);
            delete hf;
        } catch(std::exception& e) {
            cerr << argv[optind] << ": " << e.what() << endl;
            return -1;
        }
        device->erase();
        device->write(buf);
        //device->verify(buf);
    }
    else if(!strcmp(argv[optind], "erase"))
    {
        device->erase();
    }
    else if(!strcmp(argv[optind], "verify"))
    {
        optind++;
        if(optind == argc) {
            cerr << argv[0] << "not enough arguments.\n";
            return usage();
        }
        
        // Load the HEX file
        DataBuffer bufh(8);
        DataBuffer bufd(8);
        try {
            /* Read the hex file into the data buffer */
            HexFile *hf = HexFile::load(argv[optind]);
    
            hf->read(bufh);
            delete hf;
        } catch(std::exception& e) {
            cerr << argv[optind] << ": " << e.what() << endl;
            return -1;
        }
        device->read(bufd);
        for(USBDevice::RangeVector::iterator n = device->device_mmap.begin(); n != device->device_mmap.end(); n++)
        {            
            if((*n)->flags & FLASH_SECTION_READ)
            {
                for(long i = (*n)->begin; i<=(*n)->end; i++)
                {
                    if(bufd[i] != bufh[i])
                    {
                        cerr << "Bytes differs at " << hex << i << " : " << hex <<
                                bufd[i] << " != " << hex << bufh[i] << endl;
                    }
                }
            }
        }
    }
    else
    {
        cerr << "Unknown command" << endl;
    }

    if(optind == argc) {
        cerr << argv[0] << "not enough arguments.\n";
        return usage();
    }
    

    delete device;
}
