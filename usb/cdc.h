/***************************************************************************//**
 * @file  cdc.h
 * @brief USB Communication Device Class (CDC) driver.
 * @version 5.0.0
 *******************************************************************************
 * @section License
 * <b>Copyright 2015 Silicon Labs, Inc. http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/
#ifndef __CDC_H
#define __CDC_H

/***************************************************************************//**
 * @addtogroup kitdrv
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup Cdc
 * @{
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "em_usb.h"

void cdc_init( void );
uint8_t cdc_getch(char *c);
void cdc_putc(char c);
void cdc_puts(char *str);
void cdc_print_num(int val, uint8_t base,uint8_t padding);


#ifdef __cplusplus
}
#endif

/** @} (end group Cdc) */
/** @} (end group Drivers) */

#endif /* __CDC_H */
