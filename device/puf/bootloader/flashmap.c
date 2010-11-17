/*-------------------------------------------------------------------------
  flashmap.c - Flash memory mapping

   Copyright 2008-2010 Pierre Gaufillet <pierre.gaufillet@magic.fr>

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
