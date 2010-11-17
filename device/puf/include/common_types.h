/*-------------------------------------------------------------------------
  common_types.h - Common declarations and types

   Copyright 2005-2010 Pierre Gaufillet <pierre.gaufillet@magic.fr>

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

#ifndef VASCO_H_
#define VASCO_H_

/* 8 bits */
typedef unsigned char uchar;
typedef signed char schar;
typedef union
{
    uchar uc;
    schar sc;
    struct
    {
        unsigned b0:1;
        unsigned b1:1;
        unsigned b2:1;
        unsigned b3:1;
        unsigned b4:1;
        unsigned b5:1;
        unsigned b6:1;
        unsigned b7:1;
    };
} Char;

/* 16 bits */
typedef unsigned int uint;
typedef signed int sint;
typedef union
{
    uint ui;
    sint si;
    Char c[2];
} Int;


/* 32 bits */
typedef unsigned long ulong;
typedef signed long slong;
typedef union
{
    ulong ul;
    slong sl;
    Int   i[2];
    Char  c[4];
} Long;

#define TRUE 1
#define FALSE 0
#define NULL 0

#endif /*VASCO_H_*/
