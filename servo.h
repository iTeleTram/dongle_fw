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
#ifndef SERVO_DRV_H_INCLUDED
#define SERVO_DRV_H_INCLUDED

#include "bsp.h"

#define SERVO_TIMER         TIMER1
#define SERVO_TIMER_IRQ     TIMER1_IRQn
#define SERVO_TIMER_HNDLR   TIMER1_IRQHandler
#define SERVO_PIN           PORT_PE12
#define SERVO_REG_CTRL      SERVO_TIMER->CTRL
#define SERVO_REG_STAT      SERVO_TIMER->STATUS
#define SERVO_REG_ROUTE     SERVO_TIMER->ROUTE 
#define SERVO_REG_IEN       SERVO_TIMER->IEN
#define SERVO_REG_IFC       SERVO_TIMER->IFC
#define SERVO_REG_PER       SERVO_TIMER->TOP
#define SERVO_CC_CTRL       SERVO_TIMER->CC[2].CTRL 
#define SERVO_REG_CCBUF     SERVO_TIMER->CC[2].CCVB
#define SERVO_REG_CMD       SERVO_TIMER->CMD 

#define SERVO_GPIO_SETUP() {GPIO->P[4].MODEH |= GPIO_P_MODEH_MODE12_PUSHPULL;}

#define SERVO_PERIOD_VAL ((uint16_t)(PERIPH_CLK / 8 * 20E-3))  // PERIFCLK / 8 * 2mSec = 60000 @24MHz
#define SERVO_LOW_VAL (SERVO_PERIOD_VAL/20)   // 1 msec
#define SERVO_HIGH_VAL (SERVO_LOW_VAL*2)   // 2 msec
#define SERVO_ONE_DEGREE  (SERVO_LOW_VAL/180.0)

void servo_init(void);
void servo_set(uint8_t angle);
void servo_power(bool stat);

#endif //SERVO_DRV_H_INCLUDED