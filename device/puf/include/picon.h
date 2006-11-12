/*-------------------------------------------------------------------------
  picon.h - USB endpoint callbacks

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

#ifndef PICON_H_
#define PICON_H_

// Size of the End point packets in bytes
#define PICON_PACKET_SIZE 8

// Size of the circular string buffer
// TODO Should be tunable in the application code
#define PICON_BUFFER_SIZE 128

void picon_init(void);
void picon_in(void);
void prepare_in(void);

#endif /*PICON_H_*/
