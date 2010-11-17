/*-------------------------------------------------------------------------
  application.h - Application entry points

   Copyright 2005-2010 Pierre Gaufillet <pierre.gaufillet@magic.fr>

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

/* $Id$ */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "config.h"
#include "common_types.h"

typedef struct {
    uchar invalid;                   // != 0 when the application is not valid
    void* device_descriptor;
    const uchar * const *configuration_descriptor; // pointer to an array of pointer to configuration descriptors
    uchar** string_descriptor;       // pointer to an array of pointer to string descriptors
    void (*** ep_init)(void);
    void (*** ep_in)(void);
    void (*** ep_out)(void);
    void (*** ep_setup)(void);
    void (*main) (void);
} ApplicationData;

extern const ApplicationData __at(APPLICATION_DATA_ADDRESS) application_data;

#endif /*APPLICATION_H_*/
