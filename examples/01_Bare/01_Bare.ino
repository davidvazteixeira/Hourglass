/* Create one hourglass in the simplest usage */
#include <Hourglass.h>

/* Hourglass object*/
Hourglass hourglass;

void setup() {
  Serial.begin(115200);
}

void loop() {
  /* Syncronize the hourglass */
  hourglass.sync();

  /* Print ellapsed time in seconds */
  hourglass.println();

  /* do something ... */
  delay(1000);
}
