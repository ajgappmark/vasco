/*-------------------------------------------------------------------------
  flashmap.c - Flash memory mapping

             (c) 2008-2009 Pierre Gaufillet <pierre.gaufillet@magic.fr>

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

#include <pic18fregs.h>
#include "config.h"
#include "flash.h"

/* Memory sections for flash operations
 *
 * WARNING: if those descriptors are wrong, docker may not work correctly.
 *          It may even erase incorrect memory zones. So check what your are
 *          doing twice !
 *
 * These descriptors will allow docker to know the memory sections
 * of the microcontroller it is communicating with. It is provided
 * for several pic for normal and debugging modes. It has to be consistent with
 * pic configuration in config.c (__CONFIG6L and __CONFIG6H).
 *
 * The format of these descriptors is the following :
 *
 * const uchar section_descriptor [<size of the array in bytes>] =
 * 	          { <number of memory sections>,
 *               <memory section flags>,
 *               <start address, LSB first>,
 *               <end address, LSB first>,
 *               ...
 *            };
 *
 * <memory section flags> may be:
 *         - FLASH_SECTION_READ if the section is readable,
 *         - FLASH_SECTION_WRITE if the section is writable,
 *         - FLASH_SECTION_READ | FLASH_SECTION_WRITE if the section is
 *           readable and writable.
 */
#ifdef _DEBUG

	#if defined(pic18f4550) || defined(pic18f2550)

const uchar section_descriptor [22] = {3,
                                     FLASH_SECTION_READ,
                                     0x00, 0x00, 0x00,
                                     0xff, 0x5f, 0x00,
                                     FLASH_SECTION_READ | FLASH_SECTION_WRITE,
                                     0x00, 0x60, 0x00,
                                     0xff, 0x7f, 0x00,
                                     FLASH_SECTION_READ,
                                     0x00, 0x00, 0x30,
                                     0x0d, 0x00, 0x30};

	#elif defined(pic18f4450) || defined(pic18f2455)

const uchar section_descriptor [22] = {3,
                                     FLASH_SECTION_READ,
                                     0x00, 0x00, 0x00,
                                     0xff, 0x3f, 0x00,
                                     FLASH_SECTION_READ | FLASH_SECTION_WRITE,
                                     0x00, 0x40, 0x00,
                                     0xff, 0x5f, 0x00,
                                     FLASH_SECTION_READ,
                                     0x00, 0x00, 0x30,
                                     0x0d, 0x00, 0x30};
	#endif

#else

	#if defined(pic18f4550) || defined(pic18f2550)

const uchar section_descriptor [22] = {3,
                                     FLASH_SECTION_READ,
                                     0x00, 0x00, 0x00,
                                     0xff, 0x1f, 0x00,
                                     FLASH_SECTION_READ | FLASH_SECTION_WRITE,
                                     0x00, 0x20, 0x00,
                                     0xff, 0x7f, 0x00,
                                     FLASH_SECTION_READ,
                                     0x00, 0x00, 0x30,
                                     0x0d, 0x00, 0x30};

	#elif defined(pic18f4450) || defined(pic18f2455)

const uchar section_descriptor [22] = {3,
                                     FLASH_SECTION_READ,
                                     0x00, 0x00, 0x00,
                                     0xff, 0x1f, 0x00,
                                     FLASH_SECTION_READ | FLASH_SECTION_WRITE,
                                     0x00, 0x20, 0x00,
                                     0xff, 0x5f, 0x00,
                                     FLASH_SECTION_READ,
                                     0x00, 0x00, 0x30,
                                     0x0d, 0x00, 0x30};
	#endif

#endif
