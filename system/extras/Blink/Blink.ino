// Minimal blink sketch
#include "uvos.h"

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  UVOS_LED_Toggle(UVOS_LED_HEARTBEAT);
  UVOS_COM_SendString( UVOS_COM_DEBUG, "Test string,   Test string,   Test string,   Test string,   Test string.......\n" );

  delay(500);
}