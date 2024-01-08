/* Create two hourglasses and set the second from serial */

#include <Hourglass.h>

Hourglass uptime;
Hourglass chrono;

void setup() {
  Serial.begin(115200);
  uptime.name = "Uptime";
  chrono.name = "chrono";
}

/* Send anything to serial to reset the chronometer */
void serialEvent() {
  float start = Serial.parseFloat();
  while(Serial.available()) Serial.read();

  chrono.reset(start);

  Serial.print("> Set: ");
  chrono.infoln();
}

void loop() {
  /* Syncronize the hourglasses */
  uptime.sync();
  chrono.sync();

  /* Print ellapsed time in seconds */
  uptime.infoln();
  chrono.infoln();
  Serial.println("---");

  /* do something ... */
  delay(1000);
}