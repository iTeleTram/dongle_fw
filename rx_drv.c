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
 * @file rx_drv.c
 * @author Sergey Sanders
 * @date 17 March 2017
 * @brief RX DCC for EFM32HG chip
 *
 * RX DCC low level routines implementation
 * EFM32HG chip
 * @see EFM32HG Datasheet
 */

#include "bsp.h"
#include "rx_drv.h"

void rx_init(void)
{
    GPIO->P[2].MODEL |= GPIO_P_MODEL_MODE0_INPUT; // Comparator input +
    // GPIO->P[2].MODEL |= GPIO_P_MODEL_MODE1_INPUT; // Comparator input -
    GPIO->P[4].MODEH |= GPIO_P_MODEH_MODE13_PUSHPULL; // Comparator output
    CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_ACMP0; // Enable comparator's clock
    ACMP0->INPUTSEL = ACMP_INPUTSEL_POSSEL_CH0 | ACMP_INPUTSEL_NEGSEL_CH1;
    ACMP0->ROUTE = ACMP_ROUTE_LOCATION_LOC0 | ACMP_ROUTE_ACMPPEN;
    ACMP0->CTRL = ACMP_CTRL_HYSTSEL_HYST7 | ACMP_CTRL_MUXEN | ACMP_CTRL_EN;    
}

void rx_enable(bool enable)
{
    if (enable)
    {
        GPIO->P[2].MODEL = (GPIO->P[2].MODEL & ~GPIO_P_MODEL_MODE1_PUSHPULLDRIVE)| GPIO_P_MODEL_MODE1_INPUT; // Comparator input -
    }
    else
    {
        GPIO->P[2].CTRL |=  GPIO_P_CTRL_DRIVEMODE_LOWEST;
        GPIO->P[2].MODEL |= GPIO_P_MODEL_MODE1_PUSHPULLDRIVE; //discharge capacitor on Comparator input -
        GPIO->P[2].DOUTCLR = 0x02; // pull pin to ground with 0.1 mA discharge
    }
}
