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
 * @file dcc_drv.c
 * @author Sergey Sanders
 * @date 3 December 2016
 * @brief DCC for EFM32HG chip
 *
 * DCC low level routines implementation
 * EFM32HG chip
 * @see EFM32HG Datasheet
 * @see http://www.nmra.org/sites/default/files/standards/sandrp/pdf/s-9.1_electrical_standards_2006.pdf
 */

#include "bsp.h"
#include "dcc_drv.h"

enum dcc_state_e
{
    DCC_STATE_IDLE=0,
    DCC_STATE_PREAMBLE,
    DCC_STATE_DATA,
    DCC_STATE_END,
};
// Ongoing packet sctructure
struct dcc_dp_s
{
    enum dcc_state_e state;
    uint8_t dPtr;
    uint8_t bitPtr;
    uint8_t size;
    uint8_t data[7]; // 6 bytes + checksum
};

struct dcc_dp_s dccDPack;

/**
 * @brief Init DCC driver for EFM32HG chip
 */
void dcc_init(void)
{
    /// Route CC0 to PB7
    DCC_GPIO_SETUP();
    
    CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_TIMER1 | CMU_HFPERCLKEN0_GPIO;
    DCC_REG_CTRL = TIMER_CTRL_PRESC_DIV1 | TIMER_CTRL_CLKSEL_PRESCHFPERCLK;
    DCC_CC_CTRL = TIMER_CC_CTRL_CMOA_SET | TIMER_CC_CTRL_COFOA_CLEAR | TIMER_CC_CTRL_OUTINV | TIMER_CC_CTRL_MODE_OUTPUTCOMPARE;
    DCC_REG_ROUTE = TIMER_ROUTE_CC0PEN | TIMER_ROUTE_LOCATION_LOC3;
    DCC_REG_IEN = TIMER_IEN_OF;
    NVIC_ClearPendingIRQ(DCC_TIMER_IRQ);
    NVIC_EnableIRQ(DCC_TIMER_IRQ);
}

/**
 * @brief Enable DCC signal output
 * @param stat - 0 disable, otherwise enable
 */
void dcc_enable(uint8_t stat)
{
   if (stat) GPIO->P[1].DOUTSET = DCC_PIN_EN; 
   else
       GPIO->P[1].DOUTCLR = DCC_PIN_EN;
}

/**
 * @brief Check DCC signal output status
 * @return true if enabled, otherwise false. 
 */
bool dcc_stat(void)
{
    return (GPIO->P[1].DOUT & DCC_PIN_EN) ? true:false;
}
/**
 * @brief Send DCC packet
 * @param pkt - DCC packet so send
 */
void dcc_send(dcc_pkt_t *pkt)
{
    if (!pkt->size || pkt->size>6) return;
    dccDPack.data[pkt->size] = 0; //clear EE byte
    for (uint8_t i=0;i<pkt->size;i++) 
        {
            dccDPack.data[i]=pkt->data[i];
            dccDPack.data[pkt->size] ^= pkt->data[i]; //calculate checksum
        }
    dccDPack.bitPtr = 14; // send preamble
    dccDPack.dPtr = 0;
    dccDPack.size = pkt->size+1; // add ee byte
    dccDPack.state = DCC_STATE_PREAMBLE;
    DCC_REG_PER = DCC_PERIOD_HIGH;
    DCC_REG_CCBUF = DCC_BIT_HIGH;
    DCC_REG_CMD = TIMER_CMD_START;
}

/**
 * @brief Check DCC driver for ongoing transfer
 * @return true - driver is ready for new packet,
 *         false - packet sending in process
 */
bool dcc_ready(void)
{
    return (dccDPack.state == DCC_STATE_IDLE)?true:false;
}

/**
 * @brief DCC IRQ handler.
 */
void DCC_TIMER_HNDLR(void)
{
    DCC_REG_IFC = TIMER_IFC_OF;// clear interrupt flag
    switch (dccDPack.state)
    {
    case DCC_STATE_PREAMBLE:
        if (!dccDPack.bitPtr--) // go to data state
        {
            DCC_REG_PER = DCC_PERIOD_LOW; // Send 'zero' start bit
            DCC_REG_CCBUF = DCC_BIT_LOW;
            dccDPack.bitPtr = 8;
            dccDPack.state = DCC_STATE_DATA;
        }
        break;
    case DCC_STATE_DATA:
        if (!dccDPack.bitPtr--) // start new byte or end packet
        {
            if (++dccDPack.dPtr == dccDPack.size) // end the packet transmission
            {
                DCC_REG_PER = DCC_PERIOD_HIGH;
                DCC_REG_CCBUF = DCC_BIT_HIGH;
                dccDPack.state = DCC_STATE_END;
            }
            else
            {
                DCC_REG_PER = DCC_PERIOD_LOW; // Send 'zero' start bit
                DCC_REG_CCBUF = DCC_BIT_LOW;
                dccDPack.bitPtr = 8;
            }
        }
        else // send bit
        {
            if (dccDPack.data[dccDPack.dPtr] & (0x01 << dccDPack.bitPtr))
            {
                DCC_REG_PER = DCC_PERIOD_HIGH;// Send 'one'
                DCC_REG_CCBUF = DCC_BIT_HIGH;
            }
            else
            {
                DCC_REG_PER = DCC_PERIOD_LOW; // Send 'zero'
                DCC_REG_CCBUF = DCC_BIT_LOW;
            }
        }
        break;
    case DCC_STATE_END:
        dccDPack.state = DCC_STATE_IDLE; // whole packet has been sent
        DCC_REG_CMD = TIMER_CMD_STOP;
        break;
    case DCC_STATE_IDLE:
        return;
    }
}
