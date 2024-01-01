/*
  hourglass.h - Library to track uptime without worrying about millis() and micros() overlap
  Created by David Vaz Teixeira. Rio de Janeiro/Brazil, 01/01/2023.
*/

#ifndef Hourglass_h
#define Hourglass_h

#include "Arduino.h"
#define LOOP_HOURGLASS(var) static Hourglass var; var.update()

class Hourglass {
  public:
    double seconds;
    double reset_value = 0;
    unsigned long t0;
    bool never_updated = true;

    template <typename T>
    void set(T value) {
      reset_value = value;
      reset();
    }

    void update() {
      if(never_updated) {
        reset();
        never_updated = false;
      }

      unsigned long t1 = micros() + 4;

      seconds += (t1 - t0)/1000000.0;
      t0 = t1;
    }

    void reset() {
      t0 = micros();
      seconds = reset_value;
      reset_value = 0;
    }

    double now() {
      return seconds;
    }
};

#endif
