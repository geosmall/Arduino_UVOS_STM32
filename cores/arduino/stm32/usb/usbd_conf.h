#ifdef USBCON

#if defined(STM32F4xx)
  #include "stm32f4xx_usbd_conf.h"
#elif defined(STM32H7xx)
  #include "stm32h7xx_usbd_conf.h"
#else
  #error "STM32YYxx series not defined in usbd_conf.h"
#endif

#endif /* USBCON */
