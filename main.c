/**************************************************************************//**
 * @file
 * @brief Simple LED Blink Demo for SLSTK3400A_EFM32HG
 * @version 5.0.0
 ******************************************************************************
 * @section License
 * <b>Copyright 2015 Silicon Labs, Inc. http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/

#include "FreeRTOS.h"
#include "task.h"
#include "bsp.h"
#include "chip.h"
#include "em_device.h"
#include "em_cmu.h"
#include "cdc.h"
#include "dcc_drv.h"
#include "dcc.h"
#include "parser.h"

void bsp_init(void)
{
    /* Chip errata */
  //  CHIP_Init();
    CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_GPIO;
#if _CLK0_OUT
    GPIO->P[5].MODEL |= GPIO_P_MODEL_MODE2_PUSHPULL;
    CMU->CTRL |= CMU_CTRL_CLKOUTSEL0_HFCLK2;
    CMU->ROUTE = CMU_ROUTE_CLKOUT0PEN | CMU_ROUTE_LOCATION_LOC3;
#endif
  //  GPIO->P[2].MODEH |= GPIO_P_MODEH_MODE9_INPUT | GPIO_P_MODEH_MODE10_INPUT; // pushbuttons
  //  GPIO->P[5].MODEL |= GPIO_P_MODEL_MODE4_PUSHPULL | GPIO_P_MODEL_MODE5_PUSHPULL; // leds
  //  GPIO->P[5].DOUTSET = 0x01<<4;
    GPIO->P[1].MODEH |= GPIO_P_MODEH_MODE11_PUSHPULL; // led
    /* Initialize the communication class device. */
    cdc_init();

}
/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/
int main(void)
{
    bsp_init();

    xTaskCreate( parse, "parse", 128, NULL, 3, NULL );
    xTaskCreate( dcc_scheduler, "DCC loop", 128, NULL, 3, NULL );

    /* Start the tasks and timer running. */
    vTaskStartScheduler();
    while (1);

}

void vApplicationMallocFailedHook( void )
{
    /* vApplicationMallocFailedHook() will only be called if
    configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
    function that will get called if a call to pvPortMalloc() fails.
    pvPortMalloc() is called internally by the kernel whenever a task, queue,
    timer or semaphore is created.  It is also called by various parts of the
    demo application.  If heap_1.c or heap_2.c are used, then the size of the
    heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
    FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
    to query the size of free heap space that remains (although it does not
    provide information on how the remaining heap might be fragmented). */
    taskDISABLE_INTERRUPTS();
    for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
    ( void ) pcTaskName;
    ( void ) pxTask;

    /* Run time stack overflow checking is performed if
    configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
    function is called if a stack overflow is detected. */
    taskDISABLE_INTERRUPTS();
    for( ;; );
}
