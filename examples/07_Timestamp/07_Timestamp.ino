/* Create one hourglass in the simplest usage */
#include <Hourglass.h>

/* Hourglass object*/
Hourglass hourglass;

void setup() {
  Serial.begin(115200);
  hourglass.reset(1*DAY + 23*HOUR + 59*MINUTE + 50*SECOND);
}

void loop() {
  /* Syncronize the hourglass */
  hourglass.sync();

  /* Print ellapsed time in seconds */
  hourglass.timestampln();

  /* do something ... */
  delay(1000);
}