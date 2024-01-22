#ifndef Hourglass_Tools_h
  #define Hourglass_Tools_h

  #include <Hourglass.h>

  class HourglassToolsClass {
      public:
        void serialReset() {
          char cmd = Serial.read();
          while(Serial.available()) Serial.read();

          if(cmd == 'a') {
            HOURGLASS_CONTROLLER_NAME.reset_all();
            Serial.println("Reset all hourglasses");
          } else {
            short id = cmd - 48;
            if(id >=0 && id < HOURGLASS_CONTROLLER_NAME.count() ) {
              HOURGLASS_CONTROLLER_NAME.reset(id);
              Serial.print("Reset hourglass #");
              Serial.println(id);
            } else {
              Serial.println("Out of range");
              Serial.print("from 0 to ");
              Serial.println(HOURGLASS_CONTROLLER_NAME.count() - 1);
            }
          }
        }
    };

    #ifdef HOURGLASS_TOOLS_NAME
      HourglassToolsClass HOURGLASS_TOOLS_NAME;
    #else
      #define HOURGLASS_TOOLS_NAME HourglassTools
      HourglassToolsClass HOURGLASS_TOOLS_NAME;
    #endif

  #endif