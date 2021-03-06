/*-------------------------------------------------------------------------
  application_iface.c - Application data

   Copyright 2006-2012 Pierre Gaufillet <pierre.gaufillet@magic.fr>

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
-------------------------------------------------------------------------*/

#include "common_types.h"
#include "application_config.h"
#include "usb_descriptors.h"

void application_main(void);

typedef struct {
    uchar invalid;                   // != 0 when the application is not valid
    void* device_descriptor;
    const uchar __code * const *configuration_descriptor; // pointer to an array of pointer to configuration descriptors
    uchar** string_descriptor;       // pointer to an array of pointer to string descriptors
    void (*** ep_init)(void);
    void (*** ep_in)(void);
    void (*** ep_out)(void);
    void (*** ep_setup)(void);
    void (*main) (void);
    void *cinit;
} ApplicationData;

/* the cinit table will be filled by the linker */
extern __code struct
  {
    unsigned short num_init;
    struct
      {
        unsigned long from;
        unsigned long to;
        unsigned long size;
      } entries[1];
  } cinit;

// Dummy static variable to force the linker to generate cinit
// TODO: find an other way to deal with the absence of cinit.
// BTW, sdcc does it in the same way (see crt0i.c)
static char a = 0;

const ApplicationData __at(APPLICATION_DATA_ADDRESS) application_data = {
    0x00,                          // Application is valid
    &device_descriptor,            // device descriptor
    configuration_descriptor,      // configuration descriptor
    string_descriptor,             // string descriptor
    ep_init,                       // ep_init
    ep_in,                         // ep_in
    ep_out,                        // ep_out
    ep_setup,                      // ep_setup
    application_main,              // application main
    &cinit                         // static initialization table
};
