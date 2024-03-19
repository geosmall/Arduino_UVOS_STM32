/* HAL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32F4xx
  #include "uvos_usart.c"
#elif STM32H7xx
  #include "uvos_usart.c"
#else
  #error "Architecture not supported in uvos_usart_xx.c"
#endif

#pragma GCC diagnostic pop
