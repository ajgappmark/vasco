/*-------------------------------------------------------------------------
  config.c - PIC configuration words

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

#include <pic18fregs.h>
#include "config.h"

/* Set the PIC config words */
__code char __at __CONFIG1L _conf0  = _USBPLL_CLOCK_SRC_FROM_96MHZ_PLL_2_1L &
                                  _CPUDIV__OSC1_OSC2_SRC___1__96MHZ_PLL_SRC___2__1L &
                                  _PLLDIV_NO_DIVIDE__4MHZ_INPUT__1L;

__code char __at __CONFIG1H _conf1  = _IESO_OFF_1H &
                                  _FCMEN_OFF_1H &
                                  _OSC_HS__HS_PLL__USB_HS_1H;

__code char __at __CONFIG2L _conf2  = _VREGEN_ON_2L &
                                  _BODENV_2_0V_2L &
                                  _BODEN_OFF_2L &
                                  _PUT_ON_2L;

__code char __at __CONFIG2H _conf3  = _WDTPS_1_1_2H &
                                  _WDT_DISABLED_CONTROLLED_2H;

__code char __at __CONFIG3H _conf4  = _MCLRE_MCLR_ON_RE3_OFF_3H &
                                  _LPT1OSC_ON_3H &
                                  _PBADEN_PORTB_4_0__CONFIGURED_AS_DIGITAL_I_O_ON_RESET_3H &
                                  _CCP2MUX_RB3_3H;

__code char __at __CONFIG4L _conf5  = _BACKBUG_OFF_4L &
                                  _ENHCPU_OFF_4L &
                                  _ENICPORT_OFF_4L &
                                  _LVP_OFF_4L &
                                  _STVR_OFF_4L;

__code char __at __CONFIG5L _conf6  = _CP_0_OFF_5L &
                                  _CP_1_OFF_5L &
                                  _CP_2_OFF_5L &
// 4550 specific
                                  _CP_3_OFF_5L;

__code char __at __CONFIG5H _conf7  = _CPB_OFF_5H &
                                  _CPD_OFF_5H;

#ifdef _DEBUG

__code char __at __CONFIG6L _conf8  = _WRT_0_ON_6L &
                                  _WRT_1_ON_6L &
                                  _WRT_2_ON_6L &
// 4550 specific
                                  _WRT_3_OFF_6L;

#else
__code char __at __CONFIG6L _conf8  = _WRT_0_ON_6L &
                                  _WRT_1_OFF_6L &
                                  _WRT_2_OFF_6L &
// 4550 specific
                                  _WRT_3_OFF_6L;

#endif

__code char __at __CONFIG6H _conf9  = _WRTB_ON_6H &
                                  _WRTC_ON_6H &
                                  _WRTD_OFF_6H;

__code char __at __CONFIG7L _conf10 = _EBTR_0_OFF_7L &
                                  _EBTR_1_OFF_7L &
                                  _EBTR_2_OFF_7L &
// 4550 specific
                                  _EBTR_3_OFF_7L;

__code char __at __CONFIG7H _conf11 = _EBTRB_OFF_7H;
