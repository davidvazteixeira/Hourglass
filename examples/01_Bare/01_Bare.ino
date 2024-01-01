/* Create one hourglass in the simplest usage */

#include <Hourglass.h>

void setup() {
  Serial.begin(115200);
}

void loop() {
  /* Install the hourglass in loop() and create a new variable */
  LOOP_HOURGLASS(uptime);

  /* Print ellapsed time in seconds */
  Serial.print(uptime.now());
  Serial.println(" s");

  /* do something ... */
  delay(1000);
}
