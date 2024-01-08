/* Create two hourglasses and set the second from serial */

#include <Hourglass.h>

Hourglass seconds;
Hourglass minutes;
Hourglass hours;
Hourglass days;

void setup() {
  Serial.begin(115200);
  seconds.name = "s";
  seconds.reset(0);

  minutes.name = "m";
  minutes.reset(1, 'm');

  hours.name = "h";
  hours.reset(1, 'h');

  days.name = "d";
  days.reset(1, 'd');
}

void loop() {
  /* Syncronize the hourglasses */
  seconds.sync();
  minutes.sync();
  hours.sync();
  days.sync();

  /* Print ellapsed time in the adequate unit using 'a' (auto) */
  seconds.print('a'); Serial.print(" | ");
  minutes.print('a'); Serial.print(" | ");
  hours.print('a');   Serial.print(" | ");
  days.print('a');    Serial.println();

  /* do something ... */
  delay(1000);
}