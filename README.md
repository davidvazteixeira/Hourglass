# Description

Housglass is a time library that do not overlap.

This library was made with two things in mind:

* Strait forward to use in the simplest case (one hourglass)
* Tools to cover tipical demand, as print and conversions
* Optional tools to easy create, use and manipulate many hourgrasses

The time is tracked in seconds (double).

# Simplest Use

You will need 4 things:

* Include: `#include <Hourglass.h>`
* Initialize: `Hourglass hourglass`
* Sync: `hourglass.sync();`
* And show: `hourglass.println();`

you could check the included `01_Bare.ino` example:

```{c++}
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
```

The method `println()` is one of the extra tools of this library. If you want to get the value, use:

```{c++}
  double value = hourglass.elapsed();  // returns, by default, time in seconds as double;
```

`elapsed()` method has an optional argument to select the unit output, in minutes, hours or days;

# Boards

Tested in ESP32 and ESP32-S

# Docs

Hourglass has many methods and other features like:

* HourglassController
* HourglassTools
* HourglassGuard

Check the [Wiki](https://github.com/davidvazteixeira/Hourglass/wiki) or the [Docs](https://github.com/davidvazteixeira/Hourglass/tree/main/docs/docs.md).