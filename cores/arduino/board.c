#include "stm32_def.h"
#include "board.h"
#include "sys_clocks.h"
#if defined(USBCON) && defined(USBD_USE_CDC)
  #include "usb_device.h"
#endif

#include <uvos.h>

#include "board_hw_defs.c.inc"

#ifdef __cplusplus
extern "C" {
#endif

WEAK void board_init(void)
{
  configPeriphClocks();

#ifdef DWT_BASE
  dwt_init();
#endif /* DWT_BASE */

  /* Initialize the HAL */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

#if defined(USBCON) && defined(USBD_USE_CDC)
  USB_DEVICE_Init();
#endif

#if defined( UVOS_INCLUDE_LED )
  const struct uvos_gpio_cfg *led_cfg  = &uvos_led_cfg;
  UVOS_Assert( led_cfg );
  UVOS_LED_Init( led_cfg );
#endif /* UVOS_INCLUDE_LED */


} /* end void board_init(void) */

#ifdef __cplusplus
}
#endif
