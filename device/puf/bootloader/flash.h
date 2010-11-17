/*-------------------------------------------------------------------------
  flash.h - Program memory flashing process

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

#ifndef FLASH_H_
#define FLASH_H_

#include "common_types.h"

#define ERASE_FLASH_CMD        0
#define WRITE_FLASH_CMD        1
#define READ_FLASH_CMD         2
#define VALID_APPLICATION_CMD  3
#define RESET_CMD              4
#define SECTION_DESCRIPTOR_CMD 5

/* Sections attributes */
#define FLASH_SECTION_READ     0x01
#define FLASH_SECTION_WRITE    0x02

extern uint ep2_num_bytes_to_send;
extern uchar *ep2_source_data;

void erase_block(void);
void write_block(__data uchar *src);

#endif /*FLASH_H_*/
