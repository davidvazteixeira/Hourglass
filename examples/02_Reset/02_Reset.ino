/* Create one hourglass and reset from serial */

#include <Hourglass.h>

Hourglass hourglass(Serial);

void setup() {
  Serial.begin(115200);
}

/* Send anything to serial to reset the clock */
void serialEvent() {
  if (!Serial.available()) return;

  while (Serial.available()) Serial.read();
  hourglass.reset();
  Serial.println("Reset hourglass.");
}

void loop() {
  /* Manually update the hourglass */
  hourglass.sync();

  /* Print ellapsed time in seconds */
  hourglass.println();

  /* do something ... */
  delay(1000);
}