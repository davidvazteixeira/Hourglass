/* Create two hourglasses and reset the second from serial */

#include <Hourglass.h>

Hourglass chronometer;

void setup() {
  Serial.begin(115200);
}

/* Send anything to serial to reset the chronometer */
void serialEvent() {
  if (!Serial.available()) return;

  while (Serial.available()) Serial.read();
  chronometer.reset();
  Serial.println("Reset chronometer.");
}

void loop() {
  /* Install a main hourglass in loop() and create a new variable */
  LOOP_HOURGLASS(uptime);

  /* Manually Update the secondary hourglass */
  chronometer.update();

  /* Print ellapsed time in seconds */
  Serial.print("Up: "); Serial.print("\t");
  Serial.print(uptime.now()); Serial.print("s\t");
  Serial.print("C: "); Serial.print("\t");
  Serial.print(chronometer.now()); Serial.println("s");

  /* do something ... */
  delay(1000);
}