/*-------------------------------------------------------------------------
  power_mgr.h - Power supply manager functions

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

#ifndef POWER_MGR_H_
#define POWER_MGR_H_

void power_supply_mgr(void);
void set_battery_tension_alert(unsigned int period, unsigned int threshold);
void shutdown_power_supply(unsigned int delay);
void start_read_tension(void);
void switch_power_supply_on(unsigned int delay);
void reset_power_supply(unsigned int delay);
void unset_battery_tension_alert(void);

#endif /*POWER_MGR_H_*/
