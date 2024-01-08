#ifndef Hourglass_Tools_h
  #define Hourglass_Tools_h

class HourglassToolsClass {
    public:
      void serialReset() {
        char cmd = Serial.read();
        while(Serial.available()) Serial.read();

        if(cmd == 'a') {
          Hourglasses.reset_all();
          Serial.println("Reset all hourglasses");
        } else {
          short id = cmd - 48;
          if(id >=0 && id < Hourglasses.count() ) {
            Hourglasses.reset(id);
            Serial.print("Reset hourglass #");
            Serial.println(id);
          } else {
            Serial.println("Out of range");
            Serial.print("from 0 to ");
            Serial.println(Hourglasses.count() - 1);
          }
        }
      }
  };
  HourglassToolsClass HourglassTools;

  #endif