/**************************************************************************//**
 * @file cdc.c
 * @brief USB Communication Device Class (CDC) driver.
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
#include "em_device.h"
#include "em_common.h"
#include "em_cmu.h"
#include "em_core.h"
//#include "em_dma.h"
#include "em_gpio.h"
#include "em_usb.h"
#include "bsp.h"
#include "string.h"
#include "descriptors.h"
#include "cdc.h"

int  CDC_SetupCmd(const USB_Setup_TypeDef *setup);
void CDC_StateChangeEvent( USBD_State_TypeDef oldState, USBD_State_TypeDef newState);

static const USBD_Callbacks_TypeDef callbacks =
{
  .usbReset        = NULL,
  .usbStateChange  = CDC_StateChangeEvent,//StateChange,
  .setupCmd        = CDC_SetupCmd,
  .isSelfPowered   = NULL,
  .sofInt          = NULL
};

static const USBD_Init_TypeDef usbInitStruct =
{
  .deviceDescriptor    = &USBDESC_deviceDesc,
  .configDescriptor    = USBDESC_configDesc,
  .stringDescriptors   = USBDESC_strings,
  .numberOfStrings     = sizeof(USBDESC_strings)/sizeof(void*),
  .callbacks           = &callbacks,
  .bufferingMultiplier = USBDESC_bufferingMultiplier,
  .reserved            = 0
};


/**************************************************************************//**
 * @addtogroup Cdc
 * @{ Implements USB Communication Device Class (CDC).

@section cdc_intro CDC implementation.

   The source code of the CDC implementation resides in
   kits/common/drivers/cdc.c and cdc.h. This driver implements a basic
   USB to RS232 bridge.

@section cdc_config CDC device configuration options.

  This section contains a description of the configuration options for
  the driver. The options are @htmlonly #define's @endhtmlonly which are
  expected to be found in the application "usbconfig.h" header file.
  The values shown below are from the Giant Gecko DK3750 CDC example.

  @verbatim
// USB interface numbers. Interfaces are numbered from zero to one less than
// the number of concurrent interfaces supported by the configuration. A CDC
// device is by itself a composite device and has two interfaces.
// The interface numbers must be 0 and 1 for a standalone CDC device, for a
// composite device which includes a CDC interface it must not be in conflict
// with other device interfaces.
#define CDC_CTRL_INTERFACE_NO ( 0 )
#define CDC_DATA_INTERFACE_NO ( 1 )

// Endpoint address for CDC data reception.
#define CDC_EP_DATA_OUT ( 0x01 )

// Endpoint address for CDC data transmission.
#define CDC_EP_DATA_IN ( 0x81 )

// Endpoint address for the notification endpoint (not used).
#define CDC_EP_NOTIFY ( 0x82 )

// Timer id, see USBTIMER in the USB device stack documentation.
// The CDC driver has a Rx timeout functionality which require a timer.
#define CDC_TIMER_ID ( 0 )


  @endverbatim
 ** @} ***********************************************************************/

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */

/*** Typedef's and defines. ***/

#define CDC_BULK_EP_SIZE  (USB_FS_BULK_EP_MAXSIZE) /* This is the max. ep size.    */
#define CDC_USB_RX_BUF_SIZ  CDC_BULK_EP_SIZE /* Packet size when receiving on USB. */
#define CDC_USB_TX_BUF_SIZ  64 //127    /* Packet size when transmitting on USB.  */

#define UART_BUFF_SIZE      64
#define UART_BUFF_PTR_MASK  0x3f
struct uart_buff_s
{
    char data[UART_BUFF_SIZE];
    uint8_t head;
    uint8_t tail;
};

struct uart_buff_s uartRxBuffer={.head=0,.tail=0};
//struct uart_buff_s uartTxBuffer;

/*** Function prototypes. ***/

static int  UsbDataReceived(USB_Status_TypeDef status, uint32_t xferred,
                            uint32_t remaining);
static int UsbDataTransmitted(USB_Status_TypeDef status,
                              uint32_t xferred,
                              uint32_t remaining);

/*** Variables ***/


__attribute__ ((aligned(4))) uint8_t usbRxBuffer[CDC_USB_RX_BUF_SIZ];
__attribute__ ((aligned(4))) uint8_t usbTxBuffer[CDC_USB_TX_BUF_SIZ];
bool usbTxReady=false;


/** @endcond */

/**************************************************************************//**
 * @brief CDC device initialization.
 *****************************************************************************/
void cdc_init( void )
{
    usbTxReady = true;
    USBD_Init(&usbInitStruct);
    //uartRxBuffer.head =uartRxBuffer.tail = 0;
}

/**************************************************************************//**
 * @brief
 *   Handle USB setup commands. Implements CDC class specific commands.
 *
 * @param[in] setup Pointer to the setup packet received.
 *
 * @return USB_STATUS_OK if command accepted.
 *         USB_STATUS_REQ_UNHANDLED when command is unknown, the USB device
 *         stack will handle the request.
 *****************************************************************************/
const uint8_t dummyCfg[8];
int CDC_SetupCmd(const USB_Setup_TypeDef *setup)
{
//    int retVal = USB_STATUS_REQ_UNHANDLED;

    if ( ( setup->Type      == USB_SETUP_TYPE_CLASS          ) &&
            ( setup->Recipient == USB_SETUP_RECIPIENT_INTERFACE )    )
    {

            if ( ( setup->wValue == 0) && ( setup->wIndex == CDC_CTRL_INTERFACE_NO ) &&  ( setup->wLength   == 7 ) && ( setup->Direction != USB_SETUP_DIR_IN))
            {
                /* Get new settings from USB host. */
                USBD_Read(0, (void*) dummyCfg, 7, NULL);
                return USB_STATUS_OK;
            }
    }
    return USB_STATUS_REQ_UNHANDLED;
}

/**************************************************************************//**
 * @brief
 *   Callback function called each time the USB device state is changed.
 *   Starts CDC operation when device has been configured by USB host.
 *
 * @param[in] oldState The device state the device has just left.
 * @param[in] newState The new device state.
 *****************************************************************************/
void CDC_StateChangeEvent( USBD_State_TypeDef oldState,
                           USBD_State_TypeDef newState)
{
    if (newState == USBD_STATE_CONFIGURED)
    {
        /* We have been configured, start CDC functionality ! */

        if (oldState == USBD_STATE_SUSPENDED)   /* Resume ?   */
        {
        }

        /* Start receiving data from USB host. */
        usbTxReady = true;
        uartRxBuffer.head =uartRxBuffer.tail = 0;
        USBD_Read(CDC_EP_DATA_OUT, (void*) usbRxBuffer,
                  CDC_USB_RX_BUF_SIZ, UsbDataReceived);

    }

    else if ((oldState == USBD_STATE_CONFIGURED) &&
             (newState != USBD_STATE_SUSPENDED))
    {
        /* We have been de-configured, stop CDC functionality. */
    }

    else if (newState == USBD_STATE_SUSPENDED)
    {
    }
}


void cdc_putc(char c)
{
    while(!usbTxReady) {};
    usbTxReady = false;
    usbTxBuffer[0]=c;
    USBD_Write(CDC_EP_DATA_IN, (void*) usbTxBuffer,1, UsbDataTransmitted);
}

void cdc_puts(char *str)
{
    uint16_t len = strlen(str);

    while(!usbTxReady) {};
    usbTxReady = false;
    memcpy(usbTxBuffer,str,(len < CDC_USB_TX_BUF_SIZ)?len:CDC_USB_TX_BUF_SIZ);
    USBD_Write(CDC_EP_DATA_IN, (void*) usbTxBuffer,len, UsbDataTransmitted);
}

uint8_t cdc_getch(char *c)
{
    if (uartRxBuffer.head != uartRxBuffer.tail)
    {
        *c = uartRxBuffer.data[uartRxBuffer.tail++];
        uartRxBuffer.tail &= UART_BUFF_PTR_MASK;
        return 1;
    }
    return 0;
}

void cdc_print_num(int val, uint8_t base,uint8_t padding)
{
    static char buff[16];
    buff[15] = '\0';
    int i = 14;
    int sign = val<0?-1:1;
    if (!val) buff[i--]='0';
    val *= sign;
    for(; val && i ; --i, val /= base)
        buff[i] = "0123456789ABCDEF"[val % base];
    if(padding>1 && padding < 14)
    {
        for (; i>(14-padding); i--) buff[i] = '0';
    }
    if (sign<0) buff[i--] = '-';
    cdc_puts(&buff[i+1]);
}
/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */

/**************************************************************************//**
 * @brief Callback function called whenever a new packet with data is received
 *        on USB.
 *
 * @param[in] status    Transfer status code.
 * @param[in] xferred   Number of bytes transferred.
 * @param[in] remaining Number of bytes not transferred.
 *
 * @return USB_STATUS_OK.
 *****************************************************************************/
static int UsbDataReceived(USB_Status_TypeDef status, uint32_t xferred, uint32_t remaining)
{
    if ((status == USB_STATUS_OK) && (xferred > 0))
    {
        for (uint8_t i=0; i<xferred; i++)
        {
            uartRxBuffer.data[uartRxBuffer.head++]=usbRxBuffer[i];
            uartRxBuffer.head &= UART_BUFF_PTR_MASK;
        }
        USBD_Read(CDC_EP_DATA_OUT, (void*) usbRxBuffer, CDC_USB_RX_BUF_SIZ, UsbDataReceived);
    }
    return USB_STATUS_OK;

}

/**************************************************************************//**
 * @brief Callback function called whenever a packet with data has been
 *        transmitted on USB
 *
 * @param[in] status    Transfer status code.
 * @param[in] xferred   Number of bytes transferred.
 * @param[in] remaining Number of bytes not transferred.
 *
 * @return USB_STATUS_OK.
 *****************************************************************************/
static int UsbDataTransmitted(USB_Status_TypeDef status, uint32_t xferred, uint32_t remaining)
{
    usbTxReady = true;
    return USB_STATUS_OK;
}

///@endcond
