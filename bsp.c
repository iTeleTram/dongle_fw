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
 * @file bsp.c
 * @author Sergey Sanders
 * @date 13 March 2016
 * @brief BSP for ATSAML21 EVK
 *
 * Board support peripherals configuration file.
 * ATSAML21 chip
 * @see ATSAML21 Datasheet
 */

#include "bsp.h"
#include "delay.h"
#include "dcc.h"
#include "uart.h"

void _init(void)
{
    /// *********** Clocks
/// set GEN0 to 48 MHz
//     REG_OSCCTRL_OSC16MCTRL = 0x8e; // enable 16 MHz on OSC16 clock
   /// REG_NVMCTRL_CTRLB |= NVMCTRL_CTRLB_RWS(2); // set  read wait state to 1 when main gclk operating frequency is more than 33 (31) MHz
    REG_NVMCTRL_CTRLB |= NVMCTRL_CTRLB_RWS(1); // set  read wait state to 1 when main gclk operating frequency is more than 33 (31) MHz
    
    PM->INTFLAG.reg = PM_INTFLAG_PLRDY; /// clear performance level status
    PM->PLCFG.reg = 2; /// Switch performance level
    while(!PM->INTFLAG.reg) {};
/// Force DFLL enable - errata 9905
    REG_OSCCTRL_DFLLCTRL = OSCCTRL_DFLLCTRL_ENABLE;
    while (!(REG_OSCCTRL_STATUS & OSCCTRL_STATUS_DFLLRDY)) {};
    
    REG_OSCCTRL_DFLLMUL = OSCCTRL_DFLLMUL_CSTEP(0x04) | OSCCTRL_DFLLMUL_FSTEP(0x01) | OSCCTRL_DFLLMUL_MUL(0x01);
    while (!(REG_OSCCTRL_STATUS & OSCCTRL_STATUS_DFLLRDY)) {};
/// Load calibration value to the COARSE register
    REG_OSCCTRL_DFLLVAL = ((*((uint32_t *) 0x00806020) >>16) & 0xfc00) | 0x200;//0x2aa;
   // REG_OSCCTRL_DFLLVAL = 0xcc00;
    while (!(REG_OSCCTRL_STATUS &  OSCCTRL_STATUS_DFLLRDY)) {};
    REG_OSCCTRL_DFLLCTRL  |= OSCCTRL_DFLLCTRL_BPLCKC; /// Enable the Bypass Coarse Lock
   while (!(REG_OSCCTRL_STATUS & OSCCTRL_STATUS_DFLLRDY)) {};
    REG_OSCCTRL_DFLLCTRL |= OSCCTRL_DFLLCTRL_MODE; /// Start DFLL close loop
    while (!(REG_OSCCTRL_STATUS & OSCCTRL_STATUS_DFLLRDY)) {};

/// Configure GEN0 and GCLK_MAIN as 48MHz
    REG_GCLK_GENCTRL0 = GCLK_GENCTRL_DIV(1) | GCLK_GENCTRL_SRC_DFLL48M | GCLK_GENCTRL_IDC | GCLK_GENCTRL_GENEN;// |  GCLK_GENCTRL_OE;
    while(REG_GCLK_SYNCBUSY & (0x04 << 0) ) {};

/// Set GEN1 to 8 MHz
    REG_GCLK_GENCTRL1 = GCLK_GENCTRL_DIV(6) | GCLK_GENCTRL_SRC_DFLL48M | GCLK_GENCTRL_IDC | GCLK_GENCTRL_GENEN;
    while(REG_GCLK_SYNCBUSY & (0x04 << 1) ) {};

/// Set GEN2 to 1 MHz
    REG_GCLK_GENCTRL2 = GCLK_GENCTRL_DIV(8) | GCLK_GENCTRL_SRC_GCLKGEN1 | GCLK_GENCTRL_IDC | GCLK_GENCTRL_GENEN;
    while(REG_GCLK_SYNCBUSY & (0x04 << 2) ) {};
}

/**
 * @brief Init board peripherals
 * All peripherals MUST be initialized here in order to prevent reinitialization.
 */
void bsp_init(void)
{
    // LED port
    REG_PORT_DIR1 |= PORT_PB10;
    REG_PORT_OUT1 &= ~PORT_PB10;
    //oled reset
    REG_PORT_DIR0 |= PORT_PA16;
    REG_PORT_OUT0 &= ~PORT_PA16;
    
    // Switch port
    REG_PORT_WRCONFIG0 =  PORT_WRCONFIG_PULLEN | PORT_WRCONFIG_INEN | PORT_PA02 | PORT_WRCONFIG_WRPINCFG; // enable input and pull up
    REG_PORT_OUT0 |= PORT_PA02; // pull UP!

   // oled_init(DRIVER_IC_SH1106);
///   SERCOM_UART_CONFIG;
    //usart_init(SERCOM_USART,115200,USART_TYPE_ASYNC);
    delay_init();
    uart_init(115200);
    dcc_init();
    delay_ms(50);
    REG_PORT_OUT0 |= PORT_PA16; // release oled reset
#define CLK_48MHZ_OUT   0
#if  CLK_48MHZ_OUT   
    REG_GCLK_GENCTRL0 |=   GCLK_GENCTRL_OE;
    REG_PORT_WRCONFIG1 = PORT_PB14 | PORT_WRCONFIG_PMUX(0x07) | PORT_WRCONFIG_WRPMUX | PORT_WRCONFIG_PMUXEN | PORT_WRCONFIG_WRPINCFG;
#endif
    //  lindrs_init();
}
