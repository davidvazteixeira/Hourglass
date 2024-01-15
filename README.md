# Description

An uptime library that do not overlap.

This library was made with two things in mind:

* Strait forward to use in the simplest usage (one hourglass)
* Tools to cover tipical demand, as print and conversions
* Extra optional tools to easy to create many hourgrasses


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

# Advanced Usage

You can use these methods in hourglass objects. For simplicity, the text is based on this instatiation:

```{c++}
  Hourglass hourglass;
```

## Hourglass properties

### String name

A hourglass can be named. Some methods optionally use this.

```{c++}
  hourglass.name = "clock";
```

## Hourglass methods


### void sync()

The most important method of the lib. It syncs the time using the Arduino STD lib micros().

```{c++}
  hourglass.sync();
```

Call this just before any other methods or, in fast loops, just at the beginning.

### double elapsed(char unit)

Get the elapsed time. Default is seconds.

```{c++}
  double seconds = hourglass.elapsed(); // or hourglass.elapsed('s');
  double minutes = hourglass.elapsed('m');
  double hours = hourglass.elapsed('h');
  double days = hourglass.elapsed('d');
```

### void reset(double value = 0.0, char unit = 's')

Reset (or set) the time. Default is zero.

```{c++}
  hourglass.reset();   // zero
  hourglass.reset(1);   // set to 1 second
  hourglass.reset(1, 's');   // set to 1 second
  hourglass.reset(1, 'm');   // set to 60 seconds (1 minute)
  hourglass.reset(1, 'h');   // set to 3600 seconds (1 hour)
  hourglass.reset(1, 'd');   // set to 86400 seconds (1 day)
```

For a total customization, just do a time calculation using the defined macros:

```{c++}
  hourglass.reset(1*DAY + 2*HOUR + 30*MINUTE + 10*SECOND);

  // SECOND is just equal 1, so you can ommit
  hourglass.reset(1*DAY + 2*HOUR + 30*MINUTE + 10);
```

### void setOutput(Stream &stream)

The default stream to be used in the print like methods. The default stream is Serial. Don't need to call this method in this case.

```{c++}
  String my_output;
  hourglass.setOutput(my_output);
```

Now, any print-like method will use my_output string and not Serial.

### void print(char unit = 's')

Tool to print the values with unit to stream.

```{c++}
  hourglass.print(); // print time in seconds with "s" unit
  hourglass.print('m'); // print time in minutes with "m" unit
  hourglass.print('h'); // print time in minutes with "h" unit
  hourglass.print('d'); // print time in minutes with "d" unit
```

print method has a special auto unit that selects the best representative unit for the value:

```{c++}
  hourglass.print('a'); // select the best unit based on the value.
```

### void println(char unit = 's')

Just call print with a newline. See print method.


### void timestamp()

Print the value in a timestamp format.

```{c++}
  hourglass.timstamp();
```

* Example 1:
    * Value 93784 seconds is equal 1 day, 2 hours, 3 minutes and 4 seconds. The timestamp will output "1d2h3m4s"
* Example 2:
    * Value 86584 seconds is equal  1 day, **0 hours**, 3 minutes and 4 seconds. The timestamp will output "1d3m4s"

### void timestampln()

Just call timestamp with a newline. See timestamp method.

### void info(char unit = 's')

Info method prints the name with time. Or just the time when hourglass do not has a name.

```{c++}
  hourglass.info();
```

The info method use the print method, so `unit' argument is the same. Without name, it's equal the print method.

Example: With a named hourglass "clock", the output should be:

```
  clock: 10s
```

### void infoln(char unit = 's')

Just call info with a newline. See info method.

## HourglassTools

To use the tools, you must include another file:

```{c++}
  #include <HourglassTools.h>
```

HourglassTools depends on Hourglass and will include that for you, so it's useless to explicitly include both.

The above include will instanciate an object for you for easy use:

```{c++}
  HourglassToolsClass HourglassTools;
```

### HourglassTools: void serialReset

A debug tool to use with HourglassController. It asks for an id (or 'a' for all) to reset a hourglass. Just call inside serialEvent method.

```{c++}
  void serialEvent() {
    /* Send a number (id) or 'a' (all) to reset the hourglass */
    HourglassTools.serialReset();
  }
```

Note: Safe. It checks for bounds. If `id` value do not exists, a friendly error message in Serial will be shown.

## HourglassController

### Use case

The primary use of this controller is to centralize all the hourglasses.

### Include

To use the controller, you must include another file:

```{c++}
  #include <HourglassController.h>
```

HourglassController depends on Hourglass and will include that for you, so it's useless to explicitly include both.

The above include will instanciate an object for you for easy use:

```{c++}
  HourglassController Hourglasses;
```

### Simple case

If the project needs 4 hourglasses:

```{c++}
  Hourglasses.create(4);  // Creates 4 hourglasses
```

The above method is almost equivalent to:

```{c++}
  Hourglass h1;
  Hourglass h2;
  Hourglass h3;
  Hourglass h4;

  // Or just inline:
  // Hourglass h1, h2, h3, h4;
```

However, the HourglassController instance 'Hourglasses` has many tools to manage your hourglasses!

> Note: Only hourglasses created with `create` method will be seen by the controller.

To simplify the doc, the next sections assumes that you call Hourglasses.create(N), with N at least 1 (default);

### HourglassController: void create(short num = 1)

Creates a hourglass (default is 1). Each hourglass has an ID.

```{c++}
  Hourglasses.create(4); // Create four in a row
  // IDS: 0, 1, 2 and 3
```

> Note: It's a dynamic creation! Take care with memory.

### HourglassController: void remove(short id)

Remove from memory the hourglass

```{c++}
  Hourglasses.remove(2); // removes the 3rd hourglass. Count starts from zero.
```

> Note: IDs are the position of the hourglass in a list. Removing will update the IDs.

### HourglassController: void setName(short id, String name)

Set the name of a hourglass;

```{c++}
  Hourglasses.serName(0, "clock1");
  Hourglasses.serName(1, "clock2");
```

### HourglassController: void sync()

Sync all hourglasses in a row.

```{c++}
  Hourglasses.sync();
```

It's the same as, without the controller:

```{c++}
  Hourglass h1;
  Hourglass h2;
  Hourglass h3;
  Hourglass h4;

  void loop() {
    h1.sync();
    h2.sync();
    h3.sync();
    h4.sync();
  }
```

### HourglassController: double elapsed(short id)

Get the elapsed time of a hourglass.

```{c++}
  double value = Hourglasses.elapsed(0); // get the first hourglass seconds
```

### HourglassController: void reset(short id, double value = 0.0)

Reset time by id. Default is zero.

```{c++}
  Hourglasses.reset(0, 10);   // reset hourglass 0 to 10 seconds
```

### HourglassController: void reset(String name, double value = 0.0)

Reset time by name. Default is zero.

```{c++}
  Hourglasses.reset("clock1", 10); // reset hourglass "clock1" to 10 seconds
```

### HourglassController: void reset_all(double value = 0.0)

Set all hourglasses to some value. Default is zero

```{c++}
  Hourglasses.reset_all(10); // reset hourglasses 10 seconds
```

### HourglassController: void print(short id, char unit = 's')

print by id.

```{c++}
  Hourglasses.print(0);
```

### HourglassController: void println(short id, char unit = 's')

Just call print with a newline. Check print method.

### HourglassController: void print(String name, char unit = 's')

print by name.

```{c++}
  Hourglasses.print("clock1");
```

### HourglassController: void println(String name, char unit = 's')

Just call print with a newline. Check print method.

### HourglassController: void print_all(char line = 'C')

print all hourglasses in columns (default) or in rows.

call print method for each hourglass.

```{c++}
  Hourglasses.print_all('R');
  // just print one on each line

  Hourglasses.print_all('C');
  // all in one line, separated with spaced pipes: " | "
```

### HourglassController: void summary()

Create a summary of all hourglasses. It's like print_all with names.

```{c++}
  Hourglasses.summary();
```

### HourglassController: short count()

Get the number of hourglasses.

```{c++}
  short count = Hourglasses.count();
```


### HourglassController: short find(String name)

Find the hourglass if by name

```{c++}
  short id = Hourglasses.find("clock1");
```

A better use is with dynamic names in String object.

### HourglassController: void setOutput(Stream &stream)

Set the output of the print-like functions.

```{c++}
  Hourglasses.setOutput(Serial2); // Set output to another Serial
```

> Note: create method use this. The new created hourglass will not be updated.

```{c++}
  Hourglasses.setOutput(Serial2);
  Hourglasses.create(4);  // 4 hourglasses with Serial2 as output
```

```{c++}
  Hourglasses.create(4);  // 4 hourglasses with Serial as output
  Hourglasses.setOutput(Serial2);
  // hourglass print-like will output to Serial 2
  // but all houtglasses print-like will still output to Serial
```

# Metrics

## Size

The ESP32 "Blink.ino" compiled is:

```
  Sketch uses 237061 bytes (18%) of program storage space. Maximum is 1310720 bytes.
  Global variables use 21048 bytes (6%) of dynamic memory, leaving 306632 bytes for local variables. Maximum is 327680 bytes.
```

Using `Serial.begin()` and `Serial.prinln()` is

```
  Sketch uses 262217 bytes (20%) of program storage space. Maximum is 1310720 bytes.
  Global variables use 21344 bytes (6%) of dynamic memory, leaving 306336 bytes for local variables. Maximum is 327680 bytes.
```

Now, with merged with `01_Bare.ino`, is:
```
  bBSketch uses 262957 bytes (20%) of program storage space. Maximum is 1310720 bytes.
  Global variables use 21384 bytes (6%) of dynamic memory, leaving 306296 bytes for local variables. Maximum is 327680 bytes.
```

It's +740 bytes in flash and and +40 bytes in dynamic memory.