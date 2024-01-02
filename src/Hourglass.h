/*
  hourglass.h - Library to track uptime without worrying about millis() and micros() overlap
  Created by David Vaz Teixeira. Rio de Janeiro/Brazil, 01/01/2023.
*/

#ifndef Hourglass_h
#define Hourglass_h

#include "Arduino.h"
#include <vector>

#define HOURGLASS(var) static Hourglass var; Hourglass.update_all()
#define HOURGLASS_WITH_OUTPUT(var, x) static Hourglass var(x); Hourglass.update_all()

class Hourglass {
  private:
    // Static variables for counting and storing instances
    static size_t instanceCount;
    static std::vector<Hourglass*> instanceList;
    static bool global_unset_output;
    static Stream* global_output;

    bool unset_output = true;
    Stream* output;

    void print_unit(char unit) {
      if (unset_output) return;

      switch(unit) {
        case 's':
        case 'h':
        case 'd': output->print(unit); return;
        case 'm': output->print("min"); return;
        default:  return;
      }
    }

  public:
    String name;
    double seconds;
    unsigned long t0;

    Hourglass() {
      instanceCount++;
      instanceList.push_back(this);
    }

    Hourglass(Stream &stream) {
      instanceCount++;
      instanceList.push_back(this);

      setOutput(stream);
    }

    Hourglass(double start) {
      instanceCount++;
      instanceList.push_back(this);

      reset(start);
    }

    static size_t getCount() {
        return instanceCount;
    }

    static std::vector<Hourglass*> getList() {
      return instanceList;
    }

    static Hourglass *getHourglass(short n = 0) {
      return Hourglass::getList()[n];
    }

    static void summary(char unit = 's') {
      if (global_unset_output) return;

      Hourglass *hourglass;

      for(short i = 0; i<Hourglass::instanceCount; i++) {
        hourglass = getHourglass(i);

        global_output->print(hourglass->name);
        global_output->print(": ");
        global_output->print(hourglass->elapsed(unit));
        global_output->print(" | ");
      }
      global_output->print("Unit: ");
      global_output->print(unit);
      global_output->println();
    }

    static void setGlobalOutput(Stream &stream) {
      global_output = &stream;
      global_unset_output = false;
    }

    void setOutput(Stream &stream) {
      output = &stream;
      unset_output = false;
    }

    template <typename T>
    void reset(T value = 0.0) {
      t0 = micros();
      seconds = (double) value;
    }

    static void updateAll() {
      unsigned long t1 = micros();
      Hourglass *hourglass;

      for(short i = 0; i<Hourglass::instanceCount; i++) {
        hourglass = getHourglass(i);

        hourglass->seconds += (t1 - hourglass->t0)/1000000.0;
        hourglass->t0 = t1;
      }
    }

    void update() {
      unsigned long t1 = micros() + 4;
      seconds += (t1 - t0)/1000000.0;
      t0 = t1;
    }

    double elapsed(char unit = 's') {
      switch(unit) {
        case 's': return seconds;
        case 'm': return seconds/60.0;
        case 'h': return seconds/3600.0;
        case 'd': return seconds/(3600.0*24.0);
        default:  return NULL;
      }
    }

    void print(char unit = 's') {
      if (unset_output) return;

      output->print(elapsed(unit));
      print_unit(unit);
    }

    void println(char unit = 's') {
      if (unset_output) return;

      print(unit);
      output->println();
    }
};

#endif

size_t Hourglass::instanceCount = 0;
bool Hourglass::global_unset_output = true;
Stream* Hourglass::global_output;
std::vector<Hourglass*> Hourglass::instanceList;