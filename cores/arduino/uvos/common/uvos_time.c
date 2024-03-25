#include "uvos.h"

#ifdef __cplusplus
extern "C" {
#endif

uint32_t millis(void)
{
  // ToDo: ensure no interrupts
  return getCurrentMillis();
}

// Interrupt-compatible version of micros
uint32_t micros(void)
{
  return getCurrentMicros();
}

/**
 * Empty yield() hook.
 *
 * This function is intended to be used by library writers to build
 * libraries or sketches that supports cooperative threads.
 *
 * Its defined as a weak symbol and it can be redefined to implement a
 * real cooperative scheduler.
 */
static void __empty()
{
  // Empty
}
void yield(void) __attribute__((weak, alias("__empty")));


void delay(uint32_t ms)
{
  if (ms != 0) {
    uint32_t start = getCurrentMillis();
    do {
      yield();
    } while (getCurrentMillis() - start < ms);
  }
}

#ifdef __cplusplus
}
#endif
