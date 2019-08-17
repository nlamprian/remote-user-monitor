#ifndef __TYPES__
#define __TYPES__

#include <Arduino.h>

struct Message {
  Message() : ps(false), users(0), stamp(0) {}

  bool isStale() const { return (unsigned long)(millis() - stamp) >= 2000; }

  bool ps;
  uint8_t users;
  char names[10][30];
  unsigned long stamp;
};

enum class LedMode : uint8_t { STEADY = 0, FLASH = 1 };

#endif  // __TYPES__
