#include "board.h"
#include "sys_clocks.h"
#if defined(USBCON) && defined(USBD_USE_CDC)
  #include "usb_device.h"
#endif

#include <uvos.h>

#include "board_hw_defs.c.inc"

/* One slot per selectable receiver group.
 *  eg. PWM, PPM, GCS, SPEKTRUM1, SPEKTRUM2, SBUS
 * NOTE: No slot in this map for NONE.
 */
// uint32_t uvos_rcvr_group_map[ UVOS_RCVR_CHANNELGROUPS_NONE ];

#define UVOS_COM_TELEM_RF_RX_BUF_LEN     512
#define UVOS_COM_TELEM_RF_TX_BUF_LEN     512

#define UVOS_COM_TELEM_USB_RX_BUF_LEN    65
#define UVOS_COM_TELEM_USB_TX_BUF_LEN    65

#define UVOS_COM_MAVLINK_RX_BUF_LEN      64
#define UVOS_COM_MAVLINK_TX_BUF_LEN      128

#if defined(UVOS_INCLUDE_DEBUG_CONSOLE)
#define UVOS_COM_DEBUGCONSOLE_RX_BUF_LEN 64
#define UVOS_COM_DEBUGCONSOLE_TX_BUF_LEN 64
uint32_t uvos_com_debug_id;
#endif /* UVOS_INCLUDE_DEBUG_CONSOLE */

// uint32_t uvos_com_gps_id       = 0;
// uint32_t uvos_com_telem_usb_id = 0;
uint32_t uvos_com_telem_rf_id  = 0;
uint32_t uvos_com_rf_id        = 0;
// uint32_t uvos_com_bridge_id    = 0;
// uint32_t uvos_com_overo_id     = 0;
// uint32_t uvos_com_hkosd_id     = 0;
// uint32_t uvos_com_vcp_id       = 0;
// uint32_t uvos_com_msp_id       = 0;
uint32_t uvos_com_mavlink_id   = 0;

/*
 * Setup a com port based on the passed cfg, driver and buffer sizes.
 * tx size = 0 make the port rx only
 * rx size = 0 make the port tx only
 * having both tx and rx size = 0 is not valid and will fail further down in UVOS_COM_Init()
 * if usart uses dma tx then a valid uvos_dma_usart_id pointer should be provided, else should be NULL
 */
static void UVOS_Board_configure_com( const struct uvos_usart_cfg *usart_port_cfg, uint16_t rx_buf_len, uint16_t tx_buf_len,
                                      const struct uvos_com_driver *com_driver, uint32_t *uvos_com_id, uint32_t *uvos_dma_usart_id )
{
  uint32_t uvos_usart_id;

  /* Code */
  if ( usart_port_cfg->use_dma_tx == true ) {
    UVOS_Assert( uvos_dma_usart_id );
  } else {
    UVOS_Assert( uvos_dma_usart_id == NULL );
  }

  if ( UVOS_USART_Init( &uvos_usart_id, usart_port_cfg ) ) {
    UVOS_Assert( 0 );
  }

  if ( uvos_dma_usart_id ) {
    *uvos_dma_usart_id = uvos_usart_id;
  }

  uint8_t *rx_buffer = 0, * tx_buffer = 0;

  if ( rx_buf_len > 0 ) {
    rx_buffer = ( uint8_t * )UVOS_malloc( rx_buf_len );
    UVOS_Assert( rx_buffer );
  }

  if ( tx_buf_len > 0 ) {
    tx_buffer = ( uint8_t * )UVOS_malloc( tx_buf_len );
    UVOS_Assert( tx_buffer );
  }

  if ( UVOS_COM_Init( uvos_com_id, com_driver, uvos_usart_id, rx_buffer, rx_buf_len, tx_buffer, tx_buf_len ) ) {
    UVOS_Assert( 0 );
  }
}

#ifdef __cplusplus
extern "C" {
#endif

WEAK void board_init(void)
{
  configPeriphClocks();

  /* Initialize the HAL */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Must come after SystemClock_Config() to
     properly calculate DWT uSec ticks */
#if defined(UVOS_INCLUDE_DELAY)
  UVOS_DELAY_Init();
#endif /* defined(UVOS_INCLUDE_DELAY) */

#if defined(USBCON) && defined(USBD_USE_CDC)
  USB_DEVICE_Init();
#endif

#if defined( UVOS_INCLUDE_LED )
  const struct uvos_gpio_cfg *led_cfg  = &uvos_led_cfg;
  UVOS_Assert( led_cfg );
  UVOS_LED_Init( led_cfg );
#endif /* UVOS_INCLUDE_LED */

#if defined( UVOS_INCLUDE_DEBUG_CONSOLE )

#if 0 // gls
  UVOS_Board_configure_com( &uvos_usart_flexi_cfg,
                            UVOS_COM_DEBUGCONSOLE_RX_BUF_LEN,
                            UVOS_COM_DEBUGCONSOLE_TX_BUF_LEN,
                            &uvos_usart_com_driver,
                            &uvos_com_debug_id,
                            NULL );
#else
  UVOS_Board_configure_com( &uvos_usart_debug_cfg,
                            UVOS_COM_DEBUGCONSOLE_RX_BUF_LEN,
                            UVOS_COM_DEBUGCONSOLE_TX_BUF_LEN,
                            &uvos_usart_com_driver,
                            &uvos_com_debug_id,
                            &uvos_dma_usart_debug_id );
#endif // gls

#endif /* UVOS_INCLUDE_DEBUG_CONSOLE */

} /* end void board_init(void) */

#ifdef __cplusplus
}
#endif
