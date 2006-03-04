/*-------------------------------------------------------------------------
  flash.h - Program memory flashing process

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

#ifndef FLASH_H_
#define FLASH_H_

#include "common_types.h"

#define ERASE_FLASH_CMD       0
#define WRITE_FLASH_CMD       1
#define READ_FLASH_CMD        2
#define VALID_APPLICATION_CMD 3
#define RESET_CMD             4

extern uint ep2_num_bytes_to_send;
extern uchar *ep2_source_data;

void erase_block(void);
void write_block(__data uchar *src);

#endif /*FLASH_H_*/
