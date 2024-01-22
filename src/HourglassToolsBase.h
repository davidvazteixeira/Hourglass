#include <Hourglass.h>

#ifndef Hourglass_Tools_Base_h
  #define Hourglass_Tools_Base_h

  namespace HourglassTools {
    class Serial {
        public:
          void reset(HourglassController &controller) {
            char cmd = ::Serial.read();
            while(::Serial.available()) ::Serial.read();

            if(cmd == 'a') {
              controller.reset_all();
              ::Serial.println("Reset all hourglasses");
            } else {
              short id = cmd - 48;
              if(id >=0 && id < controller.count() ) {
                controller.reset(id);
                ::Serial.print("Reset hourglass #");
                ::Serial.println(id);
              } else {
                ::Serial.print("Error: Out of range. ID is from 0 to ");
                ::Serial.println(controller.count() - 1);
              }
            }
          }
      };
  }
  #endif