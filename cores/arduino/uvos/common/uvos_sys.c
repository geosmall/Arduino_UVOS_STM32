#include <uvos.h>

#ifdef UVOS_INCLUDE_SYS

/* Local Macros */
#define MEM8(addr)  (*((volatile uint8_t *)(addr)))
#define MEM16(addr) (*((volatile uint16_t *)(addr)))
#define MEM32(addr) (*((volatile uint32_t *)(addr)))

static volatile uint32_t timeout_tick_counter_g = 0;

/**
  * @brief Called from SysTick_Handler()
  * @retval None
  */
void osSystickHandler( void )
{
  if ( timeout_tick_counter_g ) {
    timeout_tick_counter_g--;
  }
}

/**
  * @brief  Function called when the tick interruption falls
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  HAL_IncTick();
  osSystickHandler();
}

/**
  * @brief Set a timeout tick value in millisecond.
  * @retval tick value
  */
void UVOS_SYS_SetTimeoutTickCount( uint32_t ticks_Ms )
{
  timeout_tick_counter_g = ticks_Ms;
}

/**
  * @brief Set a timeout tick value in millisecond.
  * @retval tick value
  */
bool UVOS_SYS_IsTimedOut( void )
{
  return ( timeout_tick_counter_g ? false : true );
}

/**
  * @brief  Function called to read the current micro second
  * @param  None
  * @retval None
  */
uint32_t getCurrentMicros(void)
{
  uint32_t m0 = HAL_GetTick();
  __IO uint32_t u0 = SysTick->VAL;
  uint32_t m1 = HAL_GetTick();
  __IO uint32_t u1 = SysTick->VAL;
  const uint32_t tms = SysTick->LOAD + 1;

  if (m1 != m0) {
    return (m1 * 1000 + ((tms - u1) * 1000) / tms);
  } else {
    return (m0 * 1000 + ((tms - u0) * 1000) / tms);
  }
}

/**
  * @brief  Function called wto read the current millisecond
  * @param  None
  * @retval None
  */
uint32_t getCurrentMillis(void)
{
  return HAL_GetTick();
}

/**
  * @brief  This function enables clocks for system peripherals
  * @param  None
  * @retval None
  */
void UVOS_SYS_ConfigPeriphClocks(void)
{
#if defined(__HAL_RCC_PWR_CLK_ENABLE)
  /* Enable PWR clock, needed for example: voltage scaling, low power ... */
  __HAL_RCC_PWR_CLK_ENABLE();
#endif

#if defined(__HAL_RCC_SYSCFG_CLK_ENABLE)
  /* Enable SYSCFG clock, needed for example: Pin remap or Analog switch ... */
  __HAL_RCC_SYSCFG_CLK_ENABLE();
#endif

#ifdef HSEM_BASE
  __HAL_RCC_HSEM_CLK_ENABLE();
#endif

  /* >>> Start of common peripherals section */

  /* Enable GPIO Peripherals */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
#if defined(GPIOF)
  __HAL_RCC_GPIOF_CLK_ENABLE();
#endif
#if defined(GPIOG)
  __HAL_RCC_GPIOG_CLK_ENABLE();
#endif
#if defined(GPIOH)
  __HAL_RCC_GPIOH_CLK_ENABLE();
#endif
// #if defined(GPIOI)
//   __HAL_RCC_GPIOI_CLK_ENABLE();
// #endif
// #if defined(GPIOJ)
//   __HAL_RCC_GPIOJ_CLK_ENABLE();
// #endif
// #if defined(GPIOK)
//   __HAL_RCC_GPIOK_CLK_ENABLE();
// #endif

  /* Enable DMA Peripherals */
  __HAL_RCC_DMA1_CLK_ENABLE();
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* Enable TIMER Peripherals */
  __HAL_RCC_TIM1_CLK_ENABLE();
#if defined(TIM2)
  __HAL_RCC_TIM2_CLK_ENABLE();
#endif
#if defined(TIM3)
  __HAL_RCC_TIM3_CLK_ENABLE();
#endif
#if defined(TIM4)
  __HAL_RCC_TIM4_CLK_ENABLE();
#endif
#if defined(TIM5)
  __HAL_RCC_TIM5_CLK_ENABLE();
#endif
#if defined(TIM6)
  __HAL_RCC_TIM6_CLK_ENABLE();
#endif
#if defined(TIM7)
  __HAL_RCC_TIM7_CLK_ENABLE();
#endif
#if defined(TIM8)
  __HAL_RCC_TIM8_CLK_ENABLE();
#endif
#if defined(TIM9)
  __HAL_RCC_TIM9_CLK_ENABLE();
#endif
#if defined(TIM10)
  __HAL_RCC_TIM10_CLK_ENABLE();
#endif
#if defined(TIM11)
  __HAL_RCC_TIM11_CLK_ENABLE();
#endif
#if defined(TIM12)
  __HAL_RCC_TIM12_CLK_ENABLE();
#endif
#if defined(TIM13)
  __HAL_RCC_TIM13_CLK_ENABLE();
#endif
#if defined(TIM14)
  __HAL_RCC_TIM14_CLK_ENABLE();
#endif

  /* Enable Watchdog Peripherals */
  __HAL_RCC_WWDG_CLK_ENABLE();

  /* Enable SPI Peripherals */
  __HAL_RCC_SPI1_CLK_ENABLE();
  __HAL_RCC_SPI2_CLK_ENABLE();
  __HAL_RCC_SPI3_CLK_ENABLE();

  /* Enable U(S)ART Peripherals */
  __HAL_RCC_USART1_CLK_ENABLE();
  __HAL_RCC_USART2_CLK_ENABLE();
#if defined(USART3)
  __HAL_RCC_USART3_CLK_ENABLE();
#endif
#if defined(UART4)
  __HAL_RCC_UART4_CLK_ENABLE();
#endif
#if defined(UART5)
  __HAL_RCC_UART5_CLK_ENABLE();
#endif
#if defined(UART6)
  __HAL_RCC_UART6_CLK_ENABLE();
#endif

  /* Enable I2C Peripherals */
  __HAL_RCC_I2C1_CLK_ENABLE();
  __HAL_RCC_I2C2_CLK_ENABLE();
#if defined(I2C3)
  __HAL_RCC_I2C3_CLK_ENABLE();
#endif

  /* Enable SDIO Peripherals */
#if defined(SDIO)
  __HAL_RCC_SDIO_CLK_ENABLE();
#endif

  /* End of common peripherals section <<< */

#if defined(STM32F4xx)

#if defined(RCC_AHB1ENR_BKPSRAMEN)
  __HAL_RCC_BKPSRAM_CLK_ENABLE();
#endif
#if defined(RCC_AHB1ENR_CCMDATARAMEN)
  __HAL_RCC_CCMDATARAMEN_CLK_ENABLE();
#endif

#if defined(CAN1)
  __HAL_RCC_CAN1_CLK_ENABLE();
#endif
#if defined(CAN2)
  __HAL_RCC_CAN2_CLK_ENABLE();
#endif

  __HAL_RCC_PWR_CLK_ENABLE();

#if defined(DAC1)
  __HAL_RCC_DAC_CLK_ENABLE();
#endif /* DAC1 */

  __HAL_RCC_ADC1_CLK_ENABLE();
#if defined(ADC2)
  __HAL_RCC_ADC2_CLK_ENABLE();
#endif
#if defined(ADC3)
  __HAL_RCC_ADC3_CLK_ENABLE();
#endif

#elif defined(STM32H7xx)

#if defined(RCC_AHB4ENR_BKPRAMEN)
  __HAL_RCC_BKPRAM_CLK_ENABLE();
#endif
// #if defined(RCC_AHB1ENR_CCMDATARAMEN)
//   __HAL_RCC_CCMDATARAMEN_CLK_ENABLE();
// #endif

  __HAL_RCC_FDCAN_CLK_ENABLE();

#if defined(DAC1)
  __HAL_RCC_DAC12_CLK_ENABLE();
#endif /* DAC1 */

  __HAL_RCC_ADC12_CLK_ENABLE();
#if defined(ADC3)
  __HAL_RCC_ADC3_CLK_ENABLE();
#endif

#else
  #error "STM32YYxx series not defined in uvos_sys.c"
#endif

  /*
   * Configure all pins as input / pullup to avoid issues with
   * uncommitted pins, excepting special-function pins that we need to
   * remain as-is.
   */
  LL_GPIO_InitTypeDef GPIO_InitStructure;
  LL_GPIO_StructInit( &GPIO_InitStructure );
  GPIO_InitStructure.Pull = LL_GPIO_PULL_UP; // default is un-pulled input

  GPIO_InitStructure.Pin  = LL_GPIO_PIN_ALL;
#ifdef USBCON
  GPIO_InitStructure.Pin &= ~( LL_GPIO_PIN_11 | LL_GPIO_PIN_12 ); // leave USB D+/D- alone
#endif
  GPIO_InitStructure.Pin &= ~( LL_GPIO_PIN_13 | LL_GPIO_PIN_14 ); // leave JTAG pins alone
  LL_GPIO_Init( GPIOA, &GPIO_InitStructure );

  GPIO_InitStructure.Pin  = LL_GPIO_PIN_ALL;
  LL_GPIO_Init( GPIOB, &GPIO_InitStructure );

  GPIO_InitStructure.Pin  = LL_GPIO_PIN_ALL;
  LL_GPIO_Init( GPIOC, &GPIO_InitStructure );
  LL_GPIO_Init( GPIOD, &GPIO_InitStructure );
  LL_GPIO_Init( GPIOE, &GPIO_InitStructure );
#if defined(GPIOF)
  LL_GPIO_Init( GPIOF, &GPIO_InitStructure );
#endif
#if defined(GPIOG)
  LL_GPIO_Init( GPIOG, &GPIO_InitStructure );
#endif
#if defined(GPIOH)
  LL_GPIO_Init( GPIOH, &GPIO_InitStructure );
#endif
#if defined(GPIOI)
  LL_GPIO_Init( GPIOI, &GPIO_InitStructure );
#endif

}

/**
 * Returns the CPU's flash size (in bytes)
 */
uint32_t UVOS_SYS_getCPUFlashSize( void )
{
  return ( uint32_t )MEM16( FLASHSIZE_BASE ) * 1024; // it might be possible to locate in the OTP area, but haven't looked and not documented
}

/**
 * Returns the serial number as 12 byte array
 * param[out] array pointer to a fixed length string of len UVOS_SYS_SERIAL_NUM_BINARY_LEN
 * return 0 if feature not supported
 */
// int32_t UVOS_SYS_SerialNumberGetBinary( uint8_t *array )
int32_t UVOS_SYS_SerialNumberGetBinary( uint8_t array[UVOS_SYS_SERIAL_NUM_BINARY_LEN] )
{
  int i;

  /* Stored in the so called "electronic signature" */
  for ( i = 0; i < UVOS_SYS_SERIAL_NUM_BINARY_LEN; ++i ) {
    uint8_t b = MEM8( UID_BASE + i );
    array[i] = b;
  }

  /* No error */
  return 0;
}

/**
 * Returns the serial number as a string
 * param[out] str pointer to a string which can store at least 32 digits + zero terminator!
 * (24 digits returned for STM32)
 * return < 0 if feature not supported
 */
// int32_t UVOS_SYS_SerialNumberGet( char *str )
int32_t UVOS_SYS_SerialNumberGet( char str[UVOS_SYS_SERIAL_NUM_ASCII_LEN + 1] )
{
  int i;

  /* Stored in the so called "electronic signature" */
  for ( i = 0; i < UVOS_SYS_SERIAL_NUM_ASCII_LEN; ++i ) {
    uint8_t b = MEM8( UID_BASE + ( i / 2 ) );
    if ( !( i & 1 ) ) {
      b >>= 4;
    }
    b &= 0x0f;

    str[i] = ( ( b > 9 ) ? ( 'A' - 10 ) : '0' ) + b;
  }
  str[i] = '\0';

  /* No error */
  return 0;
}

#endif /* UVOS_INCLUDE_SYS */