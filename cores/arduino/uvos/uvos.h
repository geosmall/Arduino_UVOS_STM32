#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <uvos_helpers.h>
#include <uvos_math.h>
#include <uvos_constants.h>

/* C Lib includes */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

/* STM32 std lib */
#if defined(STM32F4xx)
#include "stm32f4xx_conf.h"
#elif defined(STM32H7xx)
#include "stm32h7xx_conf.h"
#else
#error "No Architecture defined"
#endif

/* UVOS Hardware Includes (Common) */
#include <uvos_heap.h>
#include <uvos_sensors.h>

/* UVOS board specific feature selection */
#include "uvos_config.h"

/* UVOS system functions */
#ifdef UVOS_INCLUDE_DELAY
#include <uvos_delay.h>
#endif

#ifdef UVOS_INCLUDE_SYS
#include <uvos_sys.h>
#endif

#ifdef UVOS_INCLUDE_GPIO
#include <uvos_gpio.h>
#endif

/* UVOS common peripherals */
#ifdef UVOS_INCLUDE_LED
#include <uvos_led.h>
#endif

#if 0 // gls

/* UVOS board specific feature selection */
#include "uvos_config.h"

/* UVOS board specific device configuration */
#include "uvos_board.h"

/* UVOS debug interface */
/* #define UVOS_INCLUDE_DEBUG_CONSOLE */
/* #define DEBUG_LEVEL 0 */
#include <uvos_debug.h>
#include <uvos_debuglog.h>

/* UVOS FreeRTOS support */
#ifdef UVOS_INCLUDE_FREERTOS
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#endif

/* UVOS scheduler support */
#ifdef UVOS_INCLUDE_SCHED
#include "uvos_sched.h"
#endif

#ifdef UVOS_INCLUDE_INITCALL
#include "uvos_initcall.h"
#endif

/* UVOS system functions */
#ifdef UVOS_INCLUDE_DELAY
#include <uvos_delay.h>
// #include <uvos_deltatime.h>
#endif

#ifdef UVOS_INCLUDE_SYS
#include <uvos_sys.h>
#endif

/* UVOS hardware peripherals */
#ifdef UVOS_INCLUDE_IRQ
#include <uvos_irq.h>
#endif

#ifdef UVOS_INCLUDE_RTC
#include <uvos_rtc.h>
#endif

#ifdef UVOS_INCLUDE_TIM
#include <uvos_tim.h>
#endif

#ifdef UVOS_INCLUDE_USART
#include <uvos_usart.h>
#endif

#ifdef UVOS_INCLUDE_I2C
#include <uvos_i2c.h>
#endif

#ifdef UVOS_INCLUDE_SPI
#include <uvos_spi.h>
#endif

#ifdef UVOS_INCLUDE_GPIO
#include <uvos_gpio.h>
#endif

#ifdef UVOS_INCLUDE_EXTI
#include <uvos_exti.h>
#endif

#ifdef UVOS_INCLUDE_IBUS
#include <uvos_ibus.h>
#endif

/* UVOS abstract receiver interface */
#ifdef UVOS_INCLUDE_RCVR
#include <uvos_rcvr.h>
#endif

/* UVOS common peripherals */
#ifdef UVOS_INCLUDE_LED
#include <uvos_led.h>
#endif

#ifdef UVOS_INCLUDE_SERVO
#include <uvos_servo.h>
#endif

#ifdef UVOS_INCLUDE_FS
#include <uvos_fs.h>
#include <ff.h>
#include <lfs.h>
#endif

#ifdef UVOS_INCLUDE_SDCARD
#define LOG_FILENAME "startup.log"
// #include <ff.h>
#include <uvos_sdcard_fatfs.h>
#endif

#ifdef UVOS_INCLUDE_FLASH
/* #define UVOS_INCLUDE_FLASH_LOGFS_SETTINGS */
/* #define FLASH_FREERTOS */
#include <uvos_flash.h>
// #include <lfs.h>
#include <uvos_spif_lfs.h>
#endif

/* UVOS abstract comms interface with options */
#ifdef UVOS_INCLUDE_COM
/* #define UVOS_INCLUDE_COM_MSG */
/* #define UVOS_INCLUDE_TELEMETRY_RF */
/* #define UVOS_INCLUDE_COM_TELEM */
/* #define UVOS_INCLUDE_COM_FLEXI */
/* #define UVOS_INCLUDE_COM_AUX */
/* #define UVOS_TELEM_PRIORITY_QUEUE */
/* #define UVOS_INCLUDE_GPS */
/* #define UVOS_GPS_MINIMAL */
/* #define UVOS_INCLUDE_GPS_NMEA_PARSER */
/* #define UVOS_INCLUDE_GPS_UBX_PARSER */
/* #define UVOS_GPS_SETS_HOMELOCATION */
#include <uvos_com.h>
#endif

#endif // gls

#ifdef __cplusplus
} // closing brace for extern "C"
#endif

