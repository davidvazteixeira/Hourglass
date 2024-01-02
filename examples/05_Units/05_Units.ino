/* Show chronometer in many units */

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
  chronometer.reset(start);
}

void loop() {
  /* Install a main hourglass in loop() and create a new variable */
  LOOP_HOURGLASS(uptime);

  /* Manually Update the secondary hourglass */
  chronometer.update();

  /* Print ellapsed time in seconds */
  chronometer.streamln(Serial);
  chronometer.streamln(Serial, 'm');
  chronometer.streamln(Serial, 'h');
  chronometer.streamln(Serial, 'd');
  Serial.println("---------");

  /* Do something ... */
  delay(1000);
}