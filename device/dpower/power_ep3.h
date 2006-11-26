/*-------------------------------------------------------------------------
  power_ep3.h - USB endpoint 3 callbacks

             (c) 2006 Pierre Gaufillet <pierre.gaufillet@magic.fr> 

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
-------------------------------------------------------------------------*/

/* $Id$ */

#ifndef POWER_EP3_H_
#define POWER_EP3_H_

#include "common_types.h"

// Size of the power EP3 buffer
#define POWER_EP3_BUFFER_SIZE 2

extern uint power_ep3_num_bytes_to_send;
extern uchar *power_ep3_source_data;
extern uchar ep3_send_in_progress;     // TRUE when the buffer is being sent

void power_ep3_init(void);
void power_ep3_in(void);
void power_prepare_ep3_in(void);

#endif /*POWER_EP3_H_*/
