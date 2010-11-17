/*-------------------------------------------------------------------------
  timer2.h - timer 2 functions

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

#ifndef TIMER2_H_
#define TIMER2_H_

#define TIMER2_PRESCALER_1  0
#define TIMER2_PRESCALER_4  1
#define TIMER2_PRESCALER_16 2

#define TIMER2_POSTSCALER(x) (x-1)

#define TIMER2_ON  1
#define TIMER2_OFF 0

#define timer2_set_period(p) { PR2 = p; }
#define timer2_set_control(prescaler, postscaler, state) { T2CON = prescaler | (state << 2) | (postscaler << 3); }
#define timer2_on() { T2CONbits.TMR2ON = 1;}
#define timer2_off() { T2CONbits.TMR2ON = 0;}



#endif /*TIMER2_H_*/
