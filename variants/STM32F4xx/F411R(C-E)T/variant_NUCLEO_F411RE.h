#pragma once

#define OTG_FS_DM_PIN LL_GPIO_PIN_11
#define OTG_FS_DP_PIN LL_GPIO_PIN_12
#define OTG_FS_PORT GPIOA
#define USB_FS_GPIO_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE();
#define USB_FS_AF LL_GPIO_AF_10

