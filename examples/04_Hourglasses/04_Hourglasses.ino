/* Create many hourglasses*/

#include <HourglassController.h>

/* Tools for easy debug. Check doc. */
#include <HourglassTools.h>

void setup() {
  Serial.begin(115200);
  Hourglasses.create(4);
}

void serialEvent() {
  /* Send a number (id) or 'a' (all) to reset the hourglass */
  HourglassSerial.reset(Hourglasses);
}

void loop() {
  /* Syncronize the hourglasses */
  Hourglasses.sync();

  /* Print hourglasses */
  Hourglasses.summary();

  /* do something ... */
  delay(1000);
}