#include "sys_clocks.h"
#include "stm32yyxx_ll_gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

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

void noOsSystickHandler(void) { }

void osSystickHandler(void) __attribute__((weak, alias("noOsSystickHandler")));
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
  * @brief  This function enables clocks for system peripherals
  * @param  None
  * @retval None
  */
void configPeriphClocks(void)
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

#ifdef DWT_BASE

uint32_t dwt_init(void)
{

  /* Enable use of DWT */
  if (!(CoreDebug->DEMCR & CoreDebug_DEMCR_TRCENA_Msk)) {
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
  }

  /* Unlock */
  dwt_access(true);

  /* Reset the clock cycle counter value */
  DWT->CYCCNT = 0;

  /* Enable  clock cycle counter */
  DWT->CTRL |=  DWT_CTRL_CYCCNTENA_Msk;

  /* 3 NO OPERATION instructions */
  __asm volatile(" nop      \n\t"
                 " nop      \n\t"
                 " nop      \n\t");

  /* Check if clock cycle counter has started */
  return (DWT->CYCCNT) ? 0 : 1;
}

void dwt_access(bool ena)
{
#if (__CORTEX_M == 0x07U)
  /*
   * Define DWT LSR mask which is (currentuly) not defined by the CMSIS.
   * Same as ITM LSR one.
   */
#if !defined DWT_LSR_Present_Msk
#define DWT_LSR_Present_Msk ITM_LSR_Present_Msk
#endif
#if !defined DWT_LSR_Access_Msk
#define DWT_LSR_Access_Msk ITM_LSR_Access_Msk
#endif
  uint32_t lsr = DWT->LSR;

  if ((lsr & DWT_LSR_Present_Msk) != 0) {
    if (ena) {
      if ((lsr & DWT_LSR_Access_Msk) != 0) { //locked
        DWT->LAR = 0xC5ACCE55;
      }
    } else {
      if ((lsr & DWT_LSR_Access_Msk) == 0) { //unlocked
        DWT->LAR = 0;
      }
    }
  }
#else /* __CORTEX_M */
  UNUSED(ena);
#endif /* __CORTEX_M */
}

#endif /* DWT_BASE */

#ifdef __cplusplus
}
#endif
