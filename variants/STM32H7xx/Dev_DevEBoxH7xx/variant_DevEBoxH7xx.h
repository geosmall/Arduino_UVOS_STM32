#pragma once

#define OTG_FS_DM_PIN LL_GPIO_PIN_11
#define OTG_FS_DP_PIN LL_GPIO_PIN_12
#define OTG_FS_PORT GPIOA
#define USB_FS_GPIO_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE();
#define USB_FS_AF LL_GPIO_AF_10

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Power saving mode, MCU runs significantly cooler
 * SysClock 240 Mhz, bus clocks 120 Mhz
 */
void SysClkHalfSpeed(void);

/*
 * Full speed - sysclk from PLL1 P - 480 Mhz
 * SysClock 480 Mhz, bus clocks 240 Mhz
 */
void SysClkFullSpeed(void);

#ifdef __cplusplus
}
#endif