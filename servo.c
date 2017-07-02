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
*/
/**
 * @file servo.c
 * @author Sergey Sanders
 * @date 5 March 2017
 * @brief SERVO for EFM32HG chip
 *
 * Servo motor control implementation
 * EFM32HG chip
 * @see EFM32HG Datasheet
 */

#include "bsp.h"
#include "servo.h"

/**
 * @brief Init servo driver for EFM32HG chip
 */
void servo_init(void)
{
    /// Route CC2 to PE12
    SERVO_GPIO_SETUP();
    CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_TIMER1 | CMU_HFPERCLKEN0_GPIO;
    SERVO_REG_CTRL = TIMER_CTRL_PRESC_DIV8 | TIMER_CTRL_CLKSEL_PRESCHFPERCLK;
    SERVO_CC_CTRL = TIMER_CC_CTRL_CMOA_SET | TIMER_CC_CTRL_COFOA_CLEAR | TIMER_CC_CTRL_OUTINV | TIMER_CC_CTRL_MODE_OUTPUTCOMPARE;
    SERVO_REG_ROUTE = TIMER_ROUTE_CC2PEN | TIMER_ROUTE_LOCATION_LOC1;
    SERVO_REG_PER = SERVO_PERIOD_VAL;
}

void servo_set(uint8_t angle)
{
    if (angle>180) angle=180;
    SERVO_REG_CCBUF = SERVO_LOW_VAL + ((uint16_t)SERVO_ONE_DEGREE * angle);
   // SERVO_REG_CCBUF = SERVO_LOW_VAL/2 + (uint16_t)((SERVO_ONE_DEGREE * angle * (5/3.3))+0.5);
    if (!(SERVO_REG_STAT & TIMER_STATUS_RUNNING)) SERVO_REG_CMD = TIMER_CMD_START;
}

void servo_power(bool stat)
{
    if (stat)
    {
        SERVO_REG_CMD = TIMER_CMD_START;
    }
    else
    {
        SERVO_REG_CMD = TIMER_CMD_STOP;
    }
}
