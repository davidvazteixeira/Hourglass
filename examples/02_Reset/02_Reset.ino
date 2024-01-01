/* Create one hourglass and reset from serial */

#include <Hourglass.h>

Hourglass uptime;

void setup() {
  Serial.begin(115200);
}

/* Send anything to serial to reset the clock */
void serialEvent() {
  if (!Serial.available()) return;

  while (Serial.available()) Serial.read();
  uptime.reset();
  Serial.println("Reset hourglass.");
}

void loop() {
  /* Manually update the hourglass */
  uptime.update();

  /* Print ellapsed time in seconds */
  Serial.print(uptime.now());
  Serial.println(" s");

  /* do something ... */
  delay(1000);
}