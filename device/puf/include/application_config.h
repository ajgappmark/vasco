/*-------------------------------------------------------------------------
  config.h - Application configuration

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

#ifndef APPLICATION_CONFIG_H_
#define APPLICATION_CONFIG_H_

#include "common_types.h"

/* Application data address */
#ifdef _DEBUG
	#define APPLICATION_DATA_ADDRESS 0x6000
#else
	#define APPLICATION_DATA_ADDRESS 0x2000
#endif

/* Interrupt vectors */
#ifdef _DEBUG
	#define HIGH_PRIORITY_ISR_PRAGMA _Pragma ("code high_priority_isr 0x6020")
	#define LOW_PRIORITY_ISR_PRAGMA _Pragma ("code high_priority_isr 0x7000")
#else
	#define HIGH_PRIORITY_ISR_PRAGMA _Pragma ("code high_priority_isr 0x2020")
	#define LOW_PRIORITY_ISR_PRAGMA _Pragma ("code high_priority_isr 0x4000")
#endif

#endif /*APPLICATION_CONFIG_H_*/
