
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
      .gpio = GPIOA,
      .init =             {
        .Pin   = LL_GPIO_PIN_1,
        .Speed = LL_GPIO_SPEED_FREQ_LOW,
        .Mode  = LL_GPIO_MODE_OUTPUT,
        .OutputType = LL_GPIO_OUTPUT_PUSHPULL,
        .Pull  = LL_GPIO_PULL_NO
      },
    },
    .active_low         = false
  },
};

static const struct uvos_gpio_cfg uvos_led_cfg = {
  .gpios     = uvos_leds,
  .num_gpios = NELEMENTS( uvos_leds ),
};

#endif /* UVOS_INCLUDE_LED */

#include <uvos_usart_priv.h>

#ifdef UVOS_INCLUDE_COM_TELEM

/*
 * MAIN USART
 */
static const struct uvos_usart_cfg uvos_usart_main_cfg = {
  .regs  = USART1,
  .use_dma_tx = false,
  .init  = {
    .BaudRate            = 57600,
    .DataWidth           = LL_USART_DATAWIDTH_8B,
    .StopBits            = LL_USART_STOPBITS_1,
    .Parity              = LL_USART_PARITY_NONE,
    .TransferDirection   = LL_USART_DIRECTION_TX_RX,
    .HardwareFlowControl = LL_USART_HWCONTROL_NONE,
  },
  .irq                                       = {
    .init                                  = {
      .NVIC_IRQChannel    = USART1_IRQn,
      .NVIC_IRQChannelPreemptionPriority = UVOS_IRQ_PRIO_MID,
      .NVIC_IRQChannelSubPriority        = 0,
      .NVIC_IRQChannelCmd = ENABLE,
    },
  },
  .rx                                        = {
    .gpio = GPIOA,
    .init = {
      .Pin   = LL_GPIO_PIN_10,
      .Mode = LL_GPIO_MODE_ALTERNATE,
      .Speed = LL_GPIO_SPEED_FREQ_LOW,
      .OutputType = LL_GPIO_OUTPUT_PUSHPULL,
      .Pull = LL_GPIO_PULL_UP,
      .Alternate = LL_GPIO_AF_7,
    },
  },
  .tx                                        = {
    .gpio = GPIOA,
    .init = {
      .Pin   = LL_GPIO_PIN_9,
      .Mode = LL_GPIO_MODE_ALTERNATE,
      .Speed = LL_GPIO_SPEED_FREQ_LOW,
      .OutputType = LL_GPIO_OUTPUT_PUSHPULL,
      .Pull = LL_GPIO_PULL_UP,
      .Alternate = LL_GPIO_AF_7,
    },
  },
};
#endif /* UVOS_INCLUDE_COM_TELEM */

#ifdef UVOS_INCLUDE_COM_FLEXI
/*
 * FLEXI PORT
 */
static const struct uvos_usart_cfg uvos_usart_flexi_cfg = {
  .regs  = USART2,
  .use_dma_tx = false,
  .init  = {
    .BaudRate            = 57600,
    .DataWidth           = LL_USART_DATAWIDTH_8B,
    .StopBits            = LL_USART_STOPBITS_1,
    .Parity              = LL_USART_PARITY_NONE,
    .TransferDirection   = LL_USART_DIRECTION_TX_RX,
    .HardwareFlowControl = LL_USART_HWCONTROL_NONE,
  },
  .irq                                       = {
    .init                                  = {
      .NVIC_IRQChannel    = USART2_IRQn,
      .NVIC_IRQChannelPreemptionPriority = UVOS_IRQ_PRIO_MID,
      .NVIC_IRQChannelSubPriority        = 0,
      .NVIC_IRQChannelCmd = ENABLE,
    },
  },
  .rx                                        = {
    .gpio = GPIOA,
    .init = {
      .Pin   = LL_GPIO_PIN_3,
      .Mode = LL_GPIO_MODE_ALTERNATE,
      .Speed = LL_GPIO_SPEED_FREQ_LOW,
      .OutputType = LL_GPIO_OUTPUT_PUSHPULL,
      .Pull = LL_GPIO_PULL_UP,
      .Alternate = LL_GPIO_AF_7,
    },
  },
  .tx                                        = {
    .gpio = GPIOA,
    .init = {
      .Pin   = LL_GPIO_PIN_2,
      .Mode = LL_GPIO_MODE_ALTERNATE,
      .Speed = LL_GPIO_SPEED_FREQ_LOW,
      .OutputType = LL_GPIO_OUTPUT_PUSHPULL,
      .Pull = LL_GPIO_PULL_UP,
      .Alternate = LL_GPIO_AF_7,
    },
  },
};

#endif /* UVOS_INCLUDE_COM_FLEXI */

#ifdef UVOS_INCLUDE_DEBUG_CONSOLE
/*
 * DEBUG PORT
 */
void UVOS_USART_debug_dma_irq_handler( void );
void DMA1_Stream6_IRQHandler( void ) __attribute__( ( alias( "UVOS_USART_debug_dma_irq_handler" ) ) );
static const struct uvos_usart_cfg uvos_usart_debug_cfg = {
  .regs  = USART2,
  .use_dma_tx = true,
  .init  = {
    .BaudRate            = 115200,
    .DataWidth           = LL_USART_DATAWIDTH_8B,
    .StopBits            = LL_USART_STOPBITS_1,
    .Parity              = LL_USART_PARITY_NONE,
    .TransferDirection   = LL_USART_DIRECTION_TX_RX,
    .HardwareFlowControl = LL_USART_HWCONTROL_NONE,
  },
  .irq                                       = {
    .init                                  = {
      .NVIC_IRQChannel    = USART2_IRQn,
      .NVIC_IRQChannelPreemptionPriority = UVOS_IRQ_PRIO_MID,
      .NVIC_IRQChannelSubPriority        = 0,
      .NVIC_IRQChannelCmd = ENABLE,
    },
  },
  .dma_tx  = {
    .irq                                       = {
      // Note this is the Stream ID that triggers interrupts (in this case TX)
      .flags = ( DMA_HISR_TCIF6 | DMA_HISR_TEIF6 | DMA_HISR_HTIF6 ),
      .init  = {
        .NVIC_IRQChannel    = DMA1_Stream6_IRQn,
        .NVIC_IRQChannelPreemptionPriority = UVOS_IRQ_PRIO_MID,
        .NVIC_IRQChannelSubPriority        = 0,
        .NVIC_IRQChannelCmd = ENABLE,
      },
    },
    .tx                                        = {
      .DMAx = DMA1,
      .stream = LL_DMA_STREAM_6,
      .init    = {
        .PeriphRequest = LL_DMAMUX1_REQ_USART2_TX,
        .PeriphOrM2MSrcAddress = ( uint32_t ) & ( USART2->TDR ),
        .MemoryOrM2MDstAddress = ( uint32_t ) NULL,
        .Direction = LL_DMA_DIRECTION_MEMORY_TO_PERIPH,
        .Mode = LL_DMA_MODE_NORMAL,
        .PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT,
        .MemoryOrM2MDstIncMode = LL_DMA_MEMORY_INCREMENT,
        .PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE,
        .MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_BYTE,
        .NbData = ( uint32_t ) NULL,
        .Priority = LL_DMA_PRIORITY_MEDIUM,
        .FIFOMode = LL_DMA_FIFOMODE_DISABLE,
        .FIFOThreshold = LL_DMA_FIFOTHRESHOLD_FULL,
        .MemBurst = LL_DMA_MBURST_SINGLE,
        .PeriphBurst = LL_DMA_PBURST_SINGLE,
      },
    },
  },
  .rx                                        = {
    .gpio = GPIOA,
    .init = {
      .Pin   = LL_GPIO_PIN_3,
      .Mode = LL_GPIO_MODE_ALTERNATE,
      .Speed = LL_GPIO_SPEED_FREQ_LOW,
      .OutputType = LL_GPIO_OUTPUT_PUSHPULL,
      .Pull = LL_GPIO_PULL_UP,
      .Alternate = LL_GPIO_AF_7,
    },
  },
  .tx                                        = {
    .gpio = GPIOA,
    .init = {
      .Pin   = LL_GPIO_PIN_2,
      .Mode = LL_GPIO_MODE_ALTERNATE,
      .Speed = LL_GPIO_SPEED_FREQ_LOW,
      .OutputType = LL_GPIO_OUTPUT_PUSHPULL,
      .Pull = LL_GPIO_PULL_UP,
      .Alternate = LL_GPIO_AF_7,
    },
  },
};

static uint32_t uvos_dma_usart_debug_id;
void UVOS_USART_debug_dma_irq_handler( void )
{
  /* Call into the generic code to handle the DMAx IRQ for this specific device */
  UVOS_USART_generic_dma_irq_handler( uvos_dma_usart_debug_id );
}

#endif /* UVOS_INCLUDE_DEBUG_CONSOLE */
