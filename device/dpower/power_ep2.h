/*-------------------------------------------------------------------------
  power_ep2.h - USB endpoint 2 callbacks

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

#ifndef POWER_EP2_H_
#define POWER_EP2_H_

#include "common_types.h"

// Size of the power EP2 buffer
#define POWER_EP2_BUFFER_SIZE 8

extern uint power_ep2_num_bytes_to_send;
extern uchar *power_ep2_source_data;

void power_ep2_init(void);
void power_ep2_in(void);
void power_prepare_ep2_in(void);

#endif /*POWER_EP2_H_*/
