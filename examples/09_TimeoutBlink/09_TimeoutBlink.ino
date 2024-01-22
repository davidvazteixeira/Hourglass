/* Create timeout callbacks */

#include <Hourglass.h>
#include <HourglassGuard.h>

/* Hourglass object*/
Hourglass hourglass;

/* callback */
HourglassGuard guard;

void toogle() {
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  Serial.println("Toggle");
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  guard.every(1, hourglass, toogle);
}

void loop() {
  /* Syncronize the hourglass */
  hourglass.sync();
  guard.check();

  /* Print ellapsed time in seconds */
  hourglass.println();

  /* do something ... */
  delay(100);
}