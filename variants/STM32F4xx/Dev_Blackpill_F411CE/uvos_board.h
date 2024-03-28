#ifndef _BOARD_H_
#define _BOARD_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void UVOS_Board_Init(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

// -------------------------
// USB
// -------------------------
#define OTG_FS_DM_PIN LL_GPIO_PIN_11
#define OTG_FS_DP_PIN LL_GPIO_PIN_12
#define OTG_FS_PORT GPIOA
#define USB_FS_GPIO_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE();
#define USB_FS_AF LL_GPIO_AF_10

// ------------------------
// UVOS_LED
// ------------------------
#define UVOS_LED_HEARTBEAT 0
#define UVOS_LED_ALARM     1

// ------------------------
// UVOS_SPI
// See also uvos_board.c
// ------------------------
#define UVOS_SPI_MAX_DEVS      3

// ------------------------
// Max number of IMU reset tries
// ------------------------
#define UVOS_IMU_MAX_TRIES     5

// -------------------------
// UVOS_USART
//
// See also uvos_board.c
// -------------------------
#define UVOS_USART_MAX_DEVS 3

// -------------------------
// UVOS_COM
//
// See also board.c
// -------------------------
#define UVOS_COM_MAX_DEVS 4
extern uint32_t uvos_com_telem_rf_id;
extern uint32_t uvos_com_rf_id;
extern uint32_t uvos_com_gps_id;
extern uint32_t uvos_com_telem_usb_id;
extern uint32_t uvos_com_bridge_id;
extern uint32_t uvos_com_vcp_id;
extern uint32_t uvos_com_hkosd_id;
extern uint32_t uvos_com_msp_id;
extern uint32_t uvos_com_mavlink_id;

#define UVOS_COM_GPS       (uvos_com_gps_id)
#define UVOS_COM_TELEM_USB (uvos_com_telem_usb_id)
#define UVOS_COM_TELEM_RF  (uvos_com_telem_rf_id)
#define UVOS_COM_RF        (uvos_com_rf_id)
#define UVOS_COM_BRIDGE    (uvos_com_bridge_id)
#define UVOS_COM_VCP       (uvos_com_vcp_id)
#define UVOS_COM_OSDHK     (uvos_com_hkosd_id)
#define UVOS_COM_MSP       (uvos_com_msp_id)
#define UVOS_COM_MAVLINK   (uvos_com_mavlink_id)

#if defined(UVOS_INCLUDE_DEBUG_CONSOLE)
extern uint32_t uvos_com_debug_id;
#define UVOS_COM_DEBUG     (uvos_com_debug_id)
#endif /* UVOS_INCLUDE_DEBUG_CONSOLE */

// -------------------------
// Packet Handler
// -------------------------
#define RS_ECC_NPARITY          4
#define UVOS_PH_MAX_PACKET      255
#define UVOS_PH_WIN_SIZE        3
#define UVOS_PH_MAX_CONNECTIONS 1
extern uint32_t uvos_packet_handler;
#define UVOS_PACKET_HANDLER     (uvos_packet_handler)

// ------------------------
// TELEMETRY
// ------------------------
#define TELEM_QUEUE_SIZE        80
#define UVOS_TELEM_STACK_SIZE   800

// -------------------------
// System Settings
//
// See also System_stm32f4xx.c
// -------------------------
// These macros are deprecated
// please use UVOS_PERIPHERAL_APBx_CLOCK According to the table below
// #define UVOS_MASTER_CLOCK
// #define UVOS_PERIPHERAL_CLOCK
// #define UVOS_PERIPHERAL_CLOCK

#define UVOS_SYSCLK 96000000

// Peripherals that belongs to APB1 (PCLK1):
// DAC        |PWR          |CAN1,2
// I2C1,2,3   |UART4,5      |USART3,2
// I2S3Ext    |SPI3/I2S3    |SPI2/I2S2
// I2S2Ext    |IWDG         |WWDG
// RTC/BKP reg
// TIM2,3,4,5,6,7,12,13,14
//
// Calculated as SYSCLK / APBPresc * (APBPre == 1 ? 1 : 2)
// Default APB1 Prescaler = 2, APB1 Timer clock x2 multiplier
#define UVOS_PERIPHERAL_APB1_CLOCK          (UVOS_SYSCLK / 2)
#define UVOS_PERIPHERAL_APB1_TIMER_CLOCK     UVOS_SYSCLK

// Peripherals belonging to APB2 (PCLK2):
// SDIO       |EXTI         |SYSCFG
// SPI1       |ADC1,2,3     |USART1,6
// TIM1,8,9,10,11
//
// Default APB2 Prescaler = 1, APB1 Timer clock x1 multiplier
#define UVOS_PERIPHERAL_APB2_CLOCK           UVOS_SYSCLK
#define UVOS_PERIPHERAL_APB2_TIMER_CLOCK     UVOS_SYSCLK

// -------------------------
// Interrupt Priorities
// -------------------------
#define UVOS_IRQ_PRIO_LOW            12              // lower than RTOS
#define UVOS_IRQ_PRIO_MID            8               // higher than RTOS
#define UVOS_IRQ_PRIO_HIGH           5               // for SPI, ADC, I2C etc...
#define UVOS_IRQ_PRIO_HIGHEST        4               // for USART etc...

// -------------------------
// Scheduler defines
// -------------------------
#define UVOS_SCHED_UPDATE_HZ         UVOS_MAIN_LOOP_RATE

// The maximum number of tasks required at any one time
#define SCH_MAX_TASKS ( 5 )

// Usually set to 1, unless 'Long Tasks' are employed
#define SCH_TICK_COUNT_LIMIT ( 20 )

// ------------------------
// UVOS_RCVR
// See also board.c
// ------------------------
#define UVOS_RCVR_MAX_DEVS           3
#define UVOS_RCVR_MAX_CHANNELS       10
#define UVOS_GCSRCVR_TIMEOUT_MS      100
#define UVOS_RFM22B_RCVR_TIMEOUT_MS  200
#define UVOS_OPLINK_RCVR_TIMEOUT_MS  100

// -------------------------
// Receiver SPEKTRUM input
// -------------------------
#define UVOS_SPEKTRUM_MAX_DEVS       2
#define UVOS_SPEKTRUM_NUM_INPUTS     12

// -------------------------
// Receiver S.Bus input
// -------------------------
#define UVOS_SBUS_MAX_DEVS           1
#define UVOS_SBUS_NUM_INPUTS         (16 + 2)

// -------------------------
// Receiver DSM input
// -------------------------
#define UVOS_DSM_MAX_DEVS            2
#define UVOS_DSM_NUM_INPUTS          12

// -------------------------
// Receiver FlySky IBus input
// -------------------------
#define UVOS_IBUS_MAX_DEVS           1
#define UVOS_IBUS_NUM_INPUTS         10

// -------------------------
// Servo outputs
// -------------------------
#define UVOS_SERVO_UPDATE_HZ         50
#define UVOS_SERVOS_INITIAL_POSITION 0 /* dont want to start motors, have no pulse till settings loaded */
#define UVOS_SERVO_BANKS             2

// --------------------------
// Timer controller settings
// --------------------------
#define UVOS_TIM_MAX_DEVS            6

#endif /* _BOARD_H_ */
