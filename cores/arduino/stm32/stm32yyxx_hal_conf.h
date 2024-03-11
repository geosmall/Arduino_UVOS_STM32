#ifndef __STM32YYxx_HAL_CONF_H
#define __STM32YYxx_HAL_CONF_H

/*
 * Mandatory HAL modules
 */
#define HAL_MODULE_ENABLED
#define HAL_CORTEX_MODULE_ENABLED
#define HAL_DMA_MODULE_ENABLED /* Required by other modules */
#define HAL_FLASH_MODULE_ENABLED
#define HAL_GPIO_MODULE_ENABLED
// #define HAL_HSEM_MODULE_ENABLED
// #define HAL_IPCC_MODULE_ENABLED
// #define HAL_MDMA_MODULE_ENABLED /* Required by HAL QSPI module */
#define HAL_PWR_MODULE_ENABLED
#define HAL_RCC_MODULE_ENABLED

#endif /* __STM32YYxx_HAL_CONF_H */


