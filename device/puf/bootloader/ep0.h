/*-------------------------------------------------------------------------
  ep0.h - USB endpoint 0 callbacks

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

#ifndef EP0_H_
#define EP0_H_

#include "config.h"
#include "usb_std_req.h"

void ep0_init(void);
void ep0_in(void);
void ep0_setup(void);

#endif /*EP0_H_*/
