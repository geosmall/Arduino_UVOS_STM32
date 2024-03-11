
/* I/O mapping
 *      I/O |   PIN     |    Channel    |   Alternate function
 *      I1  |           |   TIM2_CH3    |   x
 *      I2  |           |   TIM3_CH4    |   ADC1_9
 *      I3  |           |   TIM3_CH3    |   ADC1_8
 *      I4  |           |   TIM3_CH2    |   SPI1_MOSI/ADC1_7
 *      I5  |           |   TIM3_CH1    |   SPI1_MISO/ADC1_6
 *      I6  |           |   TIM2_CH1    |   SPI1_SCK/ADC1_5
 *------------------------------------
 *      o1  |   PA8     |   TIM1_CH1    |
 *      o2  |   PA9     |   TIM1_CH2    |   USART1_TX
 *      o3  |   PA10    |   TIM1_CH3    |   USART1_RX
 *      o4  |   PB0     |   TIM3_CH3    |   ADC1_8
 *      o5  |   PB4     |   TIM3_CH1    |   SPI1_MISO
 *      o6  |   PB5     |   TIM3_CH2    |   SPI1_MOSI

Servo out 1: PA8  - TIM1_CH1 (29)
Servo out 2: PA9  - TIM1_CH2 (30)
Servo out 3: PA10 - TIM1_CH3 (31)
Servo out 4: PB0  - TIM3_CH3 (18)
Servo out 5: PB4  - TIM3_CH1 (40)
Servo out 6: PB5  - TIM3_CH2 (41)

 */
#define MAIN_USART_REGS                  USART2
#define MAIN_USART_REMAP                 GPIO_AF_USART2
#define MAIN_USART_IRQ                   USART2_IRQn
#define MAIN_USART_RX_GPIO               GPIOA
#define MAIN_USART_RX_PIN                GPIO_Pin_3
#define MAIN_USART_TX_GPIO               GPIOA
#define MAIN_USART_TX_PIN                GPIO_Pin_2
// Inverter for SBUS handling
#define MAIN_USART_INVERTER_GPIO         GPIOC
#define MAIN_USART_INVERTER_PIN          GPIO_Pin_15
#define MAIN_USART_INVERTER_CLOCK_FUNC   RCC_AHB1PeriphClockCmd
#define MAIN_USART_INVERTER_CLOCK_PERIPH RCC_AHB1Periph_GPIOC

#define FLEXI_USART_REGS                 USART1
#define FLEXI_USART_REMAP                GPIO_AF_USART1
#define FLEXI_USART_IRQ                  USART1_IRQn
#define FLEXI_USART_RX_GPIO              GPIOB
#define FLEXI_USART_RX_PIN               GPIO_Pin_7
#define FLEXI_USART_TX_GPIO              GPIOB
#define FLEXI_USART_TX_PIN               GPIO_Pin_6
// ReceiverPort pin 3
#define FLEXI_USART_DTR_GPIO             GPIOB
#define FLEXI_USART_DTR_PIN              GPIO_Pin_10

#if defined(UVOS_INCLUDE_LED)

#include <uvos_led_priv.h>
static const struct uvos_gpio uvos_leds[] = {
  [ UVOS_LED_HEARTBEAT ] = {
    .pin               =             {
      .gpio = GPIOC,
      .init =             {
        .Pin   = LL_GPIO_PIN_13,
        .Speed = LL_GPIO_SPEED_FREQ_LOW,
        .Mode  = LL_GPIO_MODE_OUTPUT,
        .OutputType = LL_GPIO_OUTPUT_PUSHPULL,
        .Pull  = LL_GPIO_PULL_NO
      },
    },
    .active_low         = true
  },
};

static const struct uvos_gpio_cfg uvos_led_cfg = {
  .gpios     = uvos_leds,
  .num_gpios = NELEMENTS( uvos_leds ),
};

#endif /* UVOS_INCLUDE_LED */
