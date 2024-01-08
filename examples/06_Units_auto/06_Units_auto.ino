/* Create two hourglasses and set the second from serial */

#include <Hourglass.h>

Hourglass seconds;
Hourglass minutes;
Hourglass hours;
Hourglass days;

void setup() {
  Serial.begin(115200);
  seconds.name = "s";
  seconds.reset(1);
  // Default is always seconds
  // Macro alternative: seconds.reset(0*SECOND);

  minutes.name = "m";
  minutes.reset(1, 'm');
  // Macro alternative: minutes.reset(1*MINUTE);

  hours.name = "h";
  hours.reset(1, 'h');
  // Macro alternative: hours.reset(1*HOUR);

  days.name = "d";
  days.reset(1, 'd');
  // Macro alternative: days.reset(1*DAY);
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