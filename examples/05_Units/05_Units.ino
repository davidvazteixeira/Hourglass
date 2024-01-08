/* Show chronometer in many units */

#include <Hourglass.h>

Hourglass chronometer;

void setup() {
  Serial.begin(115200);

  /* Chronometer will start at 12 hours */
  chronometer.reset(12, 'h');
}

void loop() {
  /* Syncronize the hourglasses */
  chronometer.sync();

  /* Print ellapsed time in many units */
  chronometer.print('d'); Serial.print(" | ");
  chronometer.print('h'); Serial.print(" | ");
  chronometer.print('m'); Serial.print(" | ");
  chronometer.print('s'); Serial.println();

  /* Do something ... */
  delay(1000);
}