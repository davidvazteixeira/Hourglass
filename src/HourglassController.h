#ifndef Hourglass_Controller_h
  #define Hourglass_Controller_h

  #include "Arduino.h"
  #include <Hourglass.h>
  #include <vector>

  #define eachHourglass(var) for(short var = 0; var<size; var++)

  class HourglassController {
    public:
      void print(short id, char unit = 's') {
        list[id].print(id, unit);
      }

      void print(String name, char unit = 's') {
        short id = find(name);
        list[id].printn(name, unit);
      }

      void println(short id, char unit = 's') {
        list[id].println(id, unit);
      }

      void println(String name, char unit = 's') {
        short id = find(name);
        list[id].println(name, unit);
      }

      void create(short num = 1) {
        for(short i=0; i<num; i++) list.push_back(Hourglass());
        size = list.size();
        neverCreated = false;
      }

      void sync() {
        if(Hourglass::neverCreated) create();
        eachHourglass(i) list[i].sync();
      }

      void summary() {
        Hourglass::summary();
      }

      // --- //

      void remove(short id) {
        list.erase(list.begin() + id);
        size = list.size();
      }

      size_t length() {
        return size;
      }

      void summary(char unit = 's') {
        if (global_unset_output) return;

        eachHourglass(i) {
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

      void setGlobalOutput(Stream &stream) {
        global_output = &stream;
        global_unset_output = false;
      }

      void setOutput(Stream &stream) {
        output = &stream;
        unset_output = false;
      }

      short find(String name) {
        eachHourglass(i) { if(name == list[i].name) return i; }
        return -1;
      }

      void reset(short id, double value = 0.0) {
        list[id].reset(value);
      }

      void reset(String name, double value = 0.0) {
        short id = find(name);
        if(id >= 0) list[id].reset(value);
      }

    private:
      static bool global_unset_output;
      static Stream* global_output;
      static short size;
      static std::vector<Hourglass> list;
      static bool neverCreated;

  };
  HourglassController Hourglasses;

#endif