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
#ifndef DCC_DRV_H_INCLUDED
#define DCC_DRV_H_INCLUDED

#include "bsp.h"

#define DCC_MAX_DATA_BYTES 6

#define DCC_TIMER       TIMER1
#define DCC_TIMER_IRQ   TIMER1_IRQn
#define DCC_TIMER_HNDLR TIMER1_IRQHandler
#define DCC_PIN_TXD     (0x01<<7)
#define DCC_PIN_EN      (0x01<<8)
#define DCC_REG_CTRL    DCC_TIMER->CTRL
#define DCC_REG_ROUTE   DCC_TIMER->ROUTE
#define DCC_REG_IEN     DCC_TIMER->IEN
#define DCC_REG_IFC     DCC_TIMER->IFC
#define DCC_REG_PER     DCC_TIMER->TOP
#define DCC_CC_CTRL     DCC_TIMER->CC[0].CTRL
#define DCC_REG_CCBUF   DCC_TIMER->CC[0].CCV
#define DCC_REG_CMD     DCC_TIMER->CMD

#define DCC_GPIO_SETUP() {GPIO->P[1].MODEL |= GPIO_P_MODEL_MODE7_PUSHPULL;\
        GPIO->P[1].MODEH |= GPIO_P_MODEH_MODE8_PUSHPULL;\
        GPIO->P[1].DOUTSET = DCC_PIN_EN;} //DCC output enable on PB8

#define DCC_PERIOD_HIGH 2762 // 116 uSec @24MHz
#define DCC_BIT_HIGH    1381 // 58
#define DCC_PERIOD_LOW  5524 // 232 uSec @24MHz
#define DCC_BIT_LOW     2762 // 116

typedef struct __attribute__ ((aligned(4)))
{
    uint8_t    data[DCC_MAX_DATA_BYTES];
    uint8_t    size;
}
dcc_pkt_t;

void dcc_init(void);
void dcc_enable(uint8_t stat);
bool dcc_stat(void);
void dcc_send(dcc_pkt_t *pkt);
bool dcc_ready(void);

#endif //DCC_DRV_H_INCLUDED
