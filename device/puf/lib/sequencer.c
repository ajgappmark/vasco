/*-------------------------------------------------------------------------
  sequencer.c - Real Time sequencer

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

#include "common_types.h"
#include "rtjobs.h"


/******************************************************************/

void rt_sequencer(uint counter)
{
    rt_base_job();

    if(counter & 0x0001)
    {
        rt_basex2_job();
        return;
    }
    if(counter & 0x0002)
    {
        rt_basex4_job();
        return;
    }
    if(counter & 0x0004)
    {
        rt_basex8_job();
        return;
    }
    if(counter & 0x0008)
    {
        rt_basex16_job();
        return;
    }
    if(counter & 0x0010)
    {
        rt_basex32_job();
        return;
    }
    if(counter & 0x0020)
    {
        rt_basex64_job();
        return;
    }
    if(counter & 0x0040)
    {
        rt_basex128_job();
        return;
    }
    if(counter & 0x0080)
    {
        rt_basex256_job();
        return;
    }
    if(counter & 0x0100)
    {
        rt_basex512_job();
        return;
    }
    if(counter & 0x0200)
    {
        rt_basex1024_job();
        return;
    }
    if(counter & 0x0400)
    {
        rt_basex2048_job();
        return;
    }
    if(counter & 0x0800)
    {
        rt_basex4096_job();
        return;
    }
    if(counter & 0x1000)
    {
        rt_basex8192_job();
        return;
    }
    if(counter & 0x2000)
    {
        rt_basex16384_job();
        return;
    }
    if(counter & 0x4000)
    {
        rt_basex32768_job();
        return;
    }
    if(counter & 0x8000)
    {
        rt_basex65536_job();
        return;
    }
}
