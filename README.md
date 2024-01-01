An uptime library that do not overlap.

# Usage

Just two lines to make the library work:

```
#include <Hourglass.h>            // First: The include

void loop() {
  LOOP_HOURGLASS(my_hourglass);       // Second: The macro call

  ...
}
```

LOOP_HOURGLASS is a macro that:

1) Create the `my_hourglass` variable for you!
2) Update the clock

Check the library examples.

# Methods

## now()

Returns uptime in seconds in decimal form.

```
  float uptime = my_hourglass.now();
  Serial.println(uptime);
```

## set(value)

Set a value different then zero.

```
  my_hourglass.set(10);
```

## reset()

Clear the hourglass.

```
  my_hourglass.reset();
```

## update()

Update the hourglass.

```
  my_hourglass.reset();
```

# Advanced Usage

You do not need to use the macro LOOP_HOURGLASS. To work, you need to do two things:

Create a hourglass variable:

```
Hourglass hourglass;
```

and call the method `update`

```
hourglass.update();
```

The macro creates a **static variable** inside `loop()` to keep the time but you could use global variables.

## Multiple hourglass

Each instance of hourglass keep track of its time. you just need to update every hourglass.

```
Hourglass h1;
Hourglass h2;
Hourglass h3;

void loop() {
  h1.update();
  h2.update();
  h3.update();

  ...
}
```

> Note: As any method, `update` consumes some time to be called and executed. The three hourglass h1, h2 and h3 will differ in some microseconds (h3 > h2 > h1) so expect an error of order 10⁻⁵ s between each hourglass.