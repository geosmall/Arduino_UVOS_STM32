#ifndef _BOARD_H_
#define _BOARD_H_

/*
 * Core and peripherals registers definitions
*/
#include "uvos_config.h"
#include "variant.h"

// ------------------------
// UVOS_LED
// ------------------------
#define UVOS_LED_HEARTBEAT 0
#define UVOS_LED_ALARM     1


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void board_init(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _BOARD_H_ */
