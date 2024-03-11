// Minimal blink sketch
#include <uvos.h>

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  UVOS_LED_Toggle(UVOS_LED_HEARTBEAT);
  delayMicroseconds(500000);
}