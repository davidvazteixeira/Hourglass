/* Create two hourglasses and set the second from serial */

#include <Hourglass.h>

Hourglass chronometer;

void setup() {
  Serial.begin(115200);
}

/* Send anything to serial to reset the chronometer */
void serialEvent() {
  float start = Serial.parseFloat();
  while(Serial.available()) Serial.read();

  Serial.print("Chronometer set to ");
  Serial.print(start);
  Serial.println(" s.");
  chronometer.set(start);
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