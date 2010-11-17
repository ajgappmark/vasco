/*-------------------------------------------------------------------------
  config.h - Bootloader configuration

   Copyright 2006-2010 Pierre Gaufillet <pierre.gaufillet@magic.fr>

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

#ifndef CONFIG_H_
#define CONFIG_H_

#include "common_types.h"

/* BOOTLOADER VERSION */
# define BOOTLOADER_VERSION 0x0120

/* SAFEBOOT BUTTON */
#define SAFE_BOOT_BUTTON (PORTBbits.RB5)

/* EP0 buffer size */
#define EP0_BUFFER_SIZE 8

/* EP1 buffer size */
#define EP1_BUFFER_SIZE 64

/* EP2 buffer size */
#define EP2_BUFFER_SIZE 64

/* USART debug buffer size */
#define EUSART_BUFFER_SIZE 256

/* Application data address */
#ifdef _DEBUG
	#define APPLICATION_DATA_ADDRESS 0x6000
#else
	#define APPLICATION_DATA_ADDRESS 0x2000
#endif

/* Interrupt vectors */
#ifdef _DEBUG
	#define HIGH_PRIORITY_ISR_PRAGMA _Pragma ("code high_priority_isr 0x6020")
	#define LOW_PRIORITY_ISR_PRAGMA _Pragma ("code low_priority_isr 0x7000")
#else
	#define HIGH_PRIORITY_ISR_PRAGMA _Pragma ("code high_priority_isr 0x2020")
	#define LOW_PRIORITY_ISR_PRAGMA _Pragma ("code low_priority_isr 0x4000")
#endif

/* Stack size and address : see boot_main.c line 24 due to _Pragma limitations */

/* Memory sections for flash operations */
extern const uchar section_descriptor [22];

#endif /*CONFIG_H_*/
