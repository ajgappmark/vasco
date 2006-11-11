/*-------------------------------------------------------------------------
  power_ep1.h - USB endpoint 1 callbacks

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

#ifndef POWER_EP1_H_
#define POWER_EP1_H_

// Size of the power EP1 buffer
#define POWER_EP1_BUFFER_SIZE 8

// Power manager commands
#define READ_BATTERY_TENSION_CMD        1
#define RESET_POWER_SUPPLY_CMD          2
#define SHUTDOWN_POWER_SUPPLY_CMD       3
#define SET_BATTERY_TENSION_ALERT_CMD   4
#define UNSET_BATTERY_TENSION_ALERT_CMD 5

void power_ep1_init(void);
void power_ep1_out(void);

#endif /*POWER_EP1_H_*/
