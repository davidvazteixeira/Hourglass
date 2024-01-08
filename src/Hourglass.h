/*
  hourglass.h - Library to track uptime without worrying about millis() and micros() overlap
  Created by David Vaz Teixeira. Rio de Janeiro/Brazil, 01/01/2023.
*/

#ifndef Hourglass_h
  #define Hourglass_h

  #include "Arduino.h"
  #define RETURN_IF_NO_OUTPUT if (!has_output) return

  class Hourglass {
    public:
      String name;

      Hourglass() {
        #ifndef HOURGLASS_START_WITHOUT_OUTPUT
          setOutput(Serial);
        #endif
      }

      Hourglass(Stream &stream) {
        setOutput(stream);
      }

      void setOutput(Stream &stream) {
        output = &stream;
        has_output = true;
      }

      void reset(double value = 0.0, char unit = 's') {
        t0 = micros();
        switch(unit) {
          case 's': seconds = value; break;
          case 'm': seconds = value*60.0; break;
          case 'h': seconds = value*60.0*60.0; break;
          case 'd': seconds = value*60.0*60.0*24.0; break;
        }

      }

      double elapsed() {
        return seconds;
      }

      double elapsed(char unit) {
        switch(unit) {
          case 's': return seconds;
          case 'm': return seconds/60.0;
          case 'h': return seconds/3600.0;
          case 'd': return seconds/(3600.0*24.0);
          default:  return NULL;
        }
      }

      void print(char unit = 's') {
        RETURN_IF_NO_OUTPUT;

        if(unit == 'a') {
          if(seconds < 60.0) {  /* less than minute is second */
            unit = 's';
          } else if (seconds < 60*60.0) { /* less than hour is minute */
            unit = 'm';
          } else if (seconds < 60*60.0*24.0) { /* less than day is hour */
            unit = 'h';
          } else { /* anything alse is day */
            unit = 'd';
          }
        }

        output->print(elapsed(unit));
        print_unit(unit);
      }

      void println(char unit = 's') {
        RETURN_IF_NO_OUTPUT;

        print(unit);
        output->println();
      }

      void info(char unit = 's') {
        RETURN_IF_NO_OUTPUT;

        if(name.length()) {
          output->print(name);
          output->print(": ");
        }
        print(unit);
      }

      void infoln(char unit = 's') {
        info(unit);
        output->println();
      }

      void sync() {
        unsigned long t1 = micros();
        seconds += (t1 - t0)/1000000.0;
        t0 = t1;
      }


    private:
      double seconds = 0;
      Stream* output;
      bool has_output = false;
      unsigned long t0;

      void print_unit(char unit) {
        RETURN_IF_NO_OUTPUT;

        switch(unit) {
          case 's':
          case 'h':
          case 'd': output->print(unit); break;
          case 'm': output->print("min"); break;
        }
      }
  };

#endif
