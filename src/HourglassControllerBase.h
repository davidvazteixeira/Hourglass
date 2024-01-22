#include "Arduino.h"
#include <Hourglass.h>
#include <vector>

#ifndef Hourglass_Controller_Base_h
  #define Hourglass_Controller_Base_h

  class HourglassController {
    public:
      void print(short id, char unit = 's') {
        list[id].print(unit);
      }

      void print(String name, char unit = 's') {
        short id = find(name);
        list[id].print(unit);
      }

      void println(short id, char unit = 's') {
        list[id].println(unit);
      }

      void println(String name, char unit = 's') {
        short id = find(name);
        list[id].println(unit);
      }

      void print_all(char line = 'C') {
        for(Hourglass &hourglass: list) {
          hourglass.print();
          line == 'R' ? output->println(): output->print(" | ");
        }
        if(line == 'C') output->println();
      }

      void setName(short id, String name) {
        list[id].name = name;
      }

      void create(short num = 1) {
        for(short i=0; i<num; i++) list.push_back(Hourglass(*output));
        size = list.size();
        neverCreated = false;
      }

      void sync() {
        if(neverCreated) create();
        for(Hourglass &hourglass: list) hourglass.sync();
      }

      void remove(short id) {
        list.erase(list.begin() + id);
        size = list.size();
      }

      double elapsed(short id) {
        return list[id].elapsed();
      }

      void summary() {
        if (unset_output) return;

        for(Hourglass &hourglass: list) {
          if(hourglass.name.length()) {
            output->print(hourglass.name);
            output->print(": ");
          }
          hourglass.print('a');
          output->print(" | ");
        }
        output->println();
      }

      void setGlobalOutput(Stream &stream) {
        output = &stream;
        unset_output = false;
      }

      void setOutput(Stream &stream) {
        output = &stream;
        unset_output = false;
      }

      short find(String name) {
        for(short id = 0; id<size; id++) {
          if(name == list[id].name) return id;
        }
        return -1;
      }

      void reset_all(double value = 0.0) {
        for(Hourglass &hourglass: list) hourglass.reset(value);
      }

      void reset(short id, double value = 0.0) {
        list[id].reset(value);
      }

      void reset(String name, double value = 0.0) {
        short id = find(name);
        if(id >= 0) list[id].reset(value);
      }

      short count() {
        return size;
      }

    private:

      #ifdef HOURGLASS_START_WITHOUT_OUTPUT
        Stream* output;
        bool unset_output = true;
      #else
        Stream* output = &Serial;
        bool unset_output = false;
      #endif

      short size;
      std::vector<Hourglass> list;
      bool neverCreated;
  };

#endif