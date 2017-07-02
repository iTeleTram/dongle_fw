/****************************************************************************
    This file is part of TeleTram DCC project.

    TeleTram DCC is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    TeleTram DCC is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with TeleTram DCC.  If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/
#ifndef BSP_H_INCLUDED
#define BSP_H_INCLUDED
#include "em_device.h"
#include "stdint.h"
#ifndef true
    typedef uint8_t bool;
    #define true    1
    #define false   0
#endif
#ifndef NULL
    #define NULL (void *)0
#endif


#define PERIPH_CLK  24000000U



#define led(x) {if (x) GPIO->P[1].DOUTSET = 0x01<<11 ; else GPIO->P[1].DOUTCLR = 0x01<<11;}
/*
typedef enum
{
    CLK_48MHZ=0,
    CLK_8MHZ,
    CLK_1MHZ
} sys_clocks_t;
*/
void bsp_init(void);

#endif //BSP_H_INCLUDED
