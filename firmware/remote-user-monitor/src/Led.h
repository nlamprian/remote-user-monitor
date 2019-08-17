#ifndef __LED__
#define __LED__

#include <Adafruit_DotStar.h>

#include "Types.h"

class Led {
 public:
  Led(int data_pin, int clock_pin, unsigned long flash_period);
  void init();
  void update(const Message &msg);

 private:
  void setMode(const Message &msg);
  void setColor();

  const uint32_t colors_[3];

  Adafruit_DotStar led_;
  LedMode mode_;
  uint32_t color_;

  // Flash mode
  const unsigned long flash_half_period_;
  unsigned long last_flash_time_;
  bool flash_state_;
};

#endif  // __LED__
