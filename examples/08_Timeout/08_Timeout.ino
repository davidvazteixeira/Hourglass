/* Create timeout callbacks */

#include <Hourglass.h>
#include <HourglassGuard.h>

/* Hourglass object*/
Hourglass hourglass;

/* callbacks */
HourglassGuard guard1;
HourglassGuard guard2;

void alert_once() {
  Serial.println("Time out! I won't remeber you gain!");
}

void alert_every() {
  Serial.println("Time out!");
}

void setup() {
  Serial.begin(115200);

  /* Configure guard to call alert_once after 3 seconds, once */
  guard1.once(5, hourglass, alert_once);

  /* Configure guard to call alert_every every 3 seconds */
  guard2.every(3, hourglass, alert_every);
}

void loop() {
  /* Syncronize the hourglass */
  hourglass.sync();

  /* Check guards */
  guard1.check();
  guard2.check();

  /* Print ellapsed time in seconds */
  hourglass.println();

  /* do something ... */
  delay(100);
}
