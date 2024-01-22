#include <Hourglass.h>

class HourglassGuard {
  enum class TimerType { Once, Every };

  void (*function)(void);
  double initial_seconds;
  double seconds;
  double seconds_delta;
  bool keepStart;

  Hourglass* hourglass;
  bool waiting = false;
  TimerType type;

  public:

    void once(double targetSeconds, Hourglass &targetHourglass, void (&targetFunction)(void)) {
      hourglass = &targetHourglass;
      seconds = hourglass->elapsed() + targetSeconds;
      function = &targetFunction;
      waiting = true;
      type = TimerType::Once;
    }

    void onceFromZero(double targetSeconds, Hourglass &targetHourglass, void (&targetFunction)(void)) {
      hourglass = &targetHourglass;
      seconds = targetSeconds;
      function = &targetFunction;
      waiting = true;
      type = TimerType::Once;
    }

    void every(double targetSeconds, Hourglass &targetHourglass, void (&targetFunction)(void), bool keep = true) {
      hourglass = &targetHourglass;

      seconds = hourglass->elapsed() + targetSeconds;
      seconds_delta = seconds;

      function = &targetFunction;
      waiting = true;
      type = TimerType::Every;
      keepStart = keep;
    }

    void everyFromZero(double targetSeconds, Hourglass &targetHourglass, void (&targetFunction)(void), bool keep = true) {
      hourglass = &targetHourglass;

      seconds = targetSeconds;
      seconds_delta = seconds;

      function = &targetFunction;
      waiting = true;
      type = TimerType::Every;
      keepStart = keep;
    }

    void cancel() {
      waiting = false;
    }

    void check() {
      if(waiting) {
        switch(type) {
          case TimerType::Once:
            if(hourglass->elapsed() > seconds) {
              waiting = false;
              function();
            }
            break;
          case TimerType::Every:
            if(hourglass->elapsed() > seconds) {
              seconds = (keepStart ? seconds : hourglass->elapsed()) + seconds_delta;
              function();
            }
            break;
        }
      }
    }
};