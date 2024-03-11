#include <uvos.h>

#ifdef UVOS_INCLUDE_SYS

/* Local Macros */
#define MEM8(addr)  (*((volatile uint8_t *)(addr)))
#define MEM16(addr) (*((volatile uint16_t *)(addr)))
#define MEM32(addr) (*((volatile uint32_t *)(addr)))

static volatile uint32_t timeout_tick_counter_g = 0;

/**
  * @brief Called from SysTick_Handler() in sys_clocks.c
  * @retval None
  */
void osSystickHandler( void )
{
  if ( timeout_tick_counter_g ) {
    timeout_tick_counter_g--;
  }
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