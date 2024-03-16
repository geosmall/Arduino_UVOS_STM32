#ifndef __CLOCK_H
#define __CLOCK_H

#include "stm32_def.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Clock source selection */
typedef enum {
  LSI_CLOCK,
  HSI_CLOCK,
  LSE_CLOCK,
  HSE_CLOCK
} sourceClock_t;

uint32_t getCurrentMillis(void);
uint32_t getCurrentMicros(void);

void configPeriphClocks(void);
void enableClock(sourceClock_t source);
void configHSECapacitorTuning(void);

#ifdef __cplusplus
}
#endif

#endif /* __CLOCK_H */
