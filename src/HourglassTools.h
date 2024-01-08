#ifndef Hourglass_Tools_h
  #define Hourglass_Tools_h

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