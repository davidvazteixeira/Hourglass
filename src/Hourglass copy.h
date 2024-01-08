/*
  hourglass.h - Library to track uptime without worrying about millis() and micros() overlap
  Created by David Vaz Teixeira. Rio de Janeiro/Brazil, 01/01/2023.
*/

/* TODO:
    The creation of the HourglassController and all the static method turns the static methods inside the Hourglass
    useless.

    - The Hourglass class must be responsible only for self.
    - All the static methods must be moved to HourglassController
    - All the static initializations must be moved to HourglassController instance initialization
    - In normal use, the user must use just the controller, not the Hourglass
    - The user can rename the default instance with a define:

      #define HOURGLASSES_CONTROLLER_NAME hg

      #ifdef HOURGLASS_CONTROLLER_NAME
        HourglassController HOURGLASS_CONTROLLER_NAME;
      #else
        HourglassController Hourglasses;
      #endif


*/

#ifndef Hourglass_h
  #define Hourglass_h

  #include "Arduino.h"
  #include <vector>

  class Hourglass {
    private:
      static bool global_unset_output;
      static Stream* global_output;

      Stream* output;
      bool unset_output = true;

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
      static short size;
      double seconds = 0;
      unsigned long t0;
      static std::vector<Hourglass> list;
      static bool neverCreated;

      static void create(short num = 1) {
        for(short i=0; i<num; i++) list.push_back(Hourglass());
        size = list.size();
        neverCreated = false;
      }

      static void remove(short id) {
        list.erase(list.begin() + id);
        size = list.size();
      }

      static size_t length() {
        return size;
      }

      static void summary(char unit = 's') {
        if (global_unset_output) return;

        for(short i = 0; i<size; i++) {
          if(list[i].name.length()) {
            global_output->print(list[i].name);
            global_output->print(": ");
          }
          global_output->print(list[i].elapsed(unit));
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

      static void reset(short id, double value = 0.0) {
        list[id].reset_instance(value);
      }

      static short find(String name) {
        for(int i=0; i<size; i++) {
          if(name == list[i].name) return i;
        }
        return -1;
      }

      static void reset(String name, double value = 0.0) {
        short id = find(name);
        if(id >= 0) list[id].reset_instance(value);
      }

      void reset_instance(double value = 0.0) {
        t0 = micros();
        seconds = (double) value;
      }

      static void sync() {
        unsigned long t1 = micros();
        for(short i = 0; i<size; i++) {
          list[i].seconds += (t1 - list[i].t0)/1000000.0;
          list[i].t0 = t1;
        }
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

  #ifdef HOURGLASS_START_WITHOUT_OUTPUT
    Stream* Hourglass::global_output;
    bool Hourglass::global_unset_output = true;
  #else
    Stream* Hourglass::global_output = &Serial;
    bool Hourglass::global_unset_output = false;
  #endif

  short Hourglass::size = 0;
  bool Hourglass::neverCreated = true;
  std::vector<Hourglass> Hourglass::list;

  class HourglassSerialTools {
    public:
      void resetTool() {
        short id = Serial.parseInt();
        float start = Serial.parseFloat();
        while(Serial.available()) Serial.read();

        Serial.print(">>> Chronometer ");
        Serial.print(id);
        Serial.print(" set to ");
        Serial.print(start);
        Serial.println(" s.");

        Hourglass::reset(id, start);
      }
  };
  HourglassSerialTools HourglassSerial;

#endif
